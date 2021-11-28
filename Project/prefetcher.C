#include "prefetcher.h"
// #include "mem-sim.h"

Prefetcher::Prefetcher() {
	_ready =false;
}

Prefetcher::~Prefetcher() {
}

bool Prefetcher::hasRequest(u_int32_t cycle) {
	return _ready;
}

Request Prefetcher::getRequest(u_int32_t cycle) {
	Request _nextReq;
	if(reqqueue.size() !=0) {
		_nextReq.addr =reqqueue[0];
		reqqueue.erase(reqqueue.begin());
		_ready =true;
	}
	if(reqqueue.size() ==0) {
		_ready =false;
	}
	return _nextReq;
}

void Prefetcher::completeRequest(u_int32_t cycle) {
}

void Prefetcher::cpuRequest(Request req) {
	if(!req.HitL1) {
		mshr[req.addr] =true;
		details entry;
		
		if(table.count(req.pc) >0) {
			entry =table[req.pc];
		}

		if(entry.pc !=req.pc) {
			entry.pc =req.pc;
			entry.lastAddr =req.addr;
			entry.lastPrefetch =0;
		}
		else if((req.addr -entry.lastAddr) !=0) {
			entry.deltas.push_back(req.addr -entry.lastAddr);
			entry.lastAddr =req.addr;

			candidates =deltaCorrelation(entry);
			prefetches =prefetchFilter(entry, candidates);
			issuePrefetches(prefetches);
		}

		table[entry.pc] =entry;
		_ready =true;
	}
}

vector<u_int32_t> Prefetcher::deltaCorrelation(details entry) {
	vector<u_int32_t> candids;
	int size =entry.deltas.size();
	u_int32_t d1 =entry.deltas[size -1];
	u_int32_t d2 =entry.deltas[size -2];
	u_int32_t addr =entry.lastAddr;

	// for(int i =size -1; i >=0; i -=2) {
	// 	if((d2 ==entry.deltas[i +1]) &&(d1 ==entry.deltas[i])) {
	// 		for(int k =i +1; k <size; k++) {
	// 			addr +=entry.deltas[k];
	// 			candids.push_back(addr);
	// 		}
	// 	}
	// }

	for(int i =1; i <size; i +=2) {
		if((d1 ==entry.deltas[i -1]) &&(d2 ==entry.deltas[i])) {
			for(int k =i +1; k <size; k++) {
				addr +=entry.deltas[k];
				candids.push_back(addr);
			}
		}
	}

	return candids;
}

vector<u_int32_t> Prefetcher::prefetchFilter(details entry, vector<u_int32_t> candids) {
	vector<u_int32_t> prefets;

	for(int i =0; i <candids.size(); i++) {
		if((getIndex(inFlight, candids[i]) ==-1) &&(mshr.count(candids[i]) ==-1) &&(getIndex(reqqueue, candids[i]) ==-1)) {
			prefets.push_back(candids[i]);
			inFlight.push_back(candids[i]);
			entry.lastPrefetch =candids[i];

			table[entry.pc] =entry;
		}
		if(candids[i] ==entry.lastPrefetch) {
			prefets =vector<u_int32_t>();
		}
	}

	return prefets;
}

void Prefetcher::issuePrefetches(vector<u_int32_t> prefets) {
	for(int i =0; i <prefets.size(); i++) {
		if(reqqueue.size() <=32) {
			reqqueue.push_back(prefets[i]);
		}
		else {
			reqqueue.erase(reqqueue.begin());
			reqqueue.push_back(prefets[i]);
		}
	}
}

// Prefetcher::Prefetcher() {
// 	_ready =false;
// }

// Prefetcher::~Prefetcher() {
// }

// bool Prefetcher::hasRequest(u_int32_t cycle) {
// 	return _ready;
// }

// Request Prefetcher::getRequest(u_int32_t cycle) {
// 	Request _nextReq;
// 	if(!_req_queue.empty()) {
// 		_nextReq.addr =_req_queue.front();
// 		_req_queue.pop();
// 		_ready =true;
// 	}
// 	else {
// 		_ready = false;
// 	}
// 	return _nextReq;
// }

// void Prefetcher::completeRequest(u_int32_t cycle) {
// }

// void Prefetcher::cpuRequest(Request req) {
// 	if(!req.HitL1) {
// 		int index =getIndex(_history, req.addr);
// 		_history.push_back(req.addr);

// 		if(index ==-1) {
// 			for(int i =1; i <=4; i++) {
// 				_req_queue.push(req.addr +(32 *i));
// 			}
// 		}
// 		else {
// 			_req_queue =queue<u_int32_t>();
// 			index +=1;
// 			int num =(_history.size() -index) /2;
// 			for(int i =index; i <num; i++) {
// 				_req_queue.push(_history[i]);
// 			}
// 		}
// 		_ready =true;
// 	}
// }


// bool Prefetcher::hasRequest(u_int32_t cycle) {
// 	return false;
// }

// Request Prefetcher::getRequest(u_int32_t cycle) {
// 	Request req;
// 	return req;
// }

// void Prefetcher::completeRequest(u_int32_t cycle) { return; }

// void Prefetcher::cpuRequest(Request req) { return; }