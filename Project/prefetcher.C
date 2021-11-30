// Mohamed Rayyan
// mrayy002
// 862037325

#include "prefetcher.h"
#include "mem-sim.h"

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
	if(!_req_queue.empty()) {
		_nextReq.addr =_req_queue.front();
		_req_queue.pop();
		_ready =true;
	}
	if(_req_queue.empty()) {
		_ready = false;
	}
	return _nextReq;
}

void Prefetcher::completeRequest(u_int32_t cycle) {
}

void Prefetcher::cpuRequest(Request req) {
	if(!req.HitL1) {
		int index =getIndex(_history, req.addr);

		if(_history.size() >93) {
			_history.erase(_history.begin());
		}

		_history.push_back(req.addr);

		if(index ==-1) {
			for(int i =1; i <=4; i++) {
				_req_queue.push(req.addr +(32 *i));
			}
		}
		else {
			_req_queue =queue<u_int32_t>();
			index +=1;
			int num =(_history.size() -index) /2;

			for(int i =index; i <num; i++) {
				if(_req_queue.size() >32) {
					_req_queue.pop();
				}
				_req_queue.push(_history[i]);
			}
		}
		_ready =true;
	}
}


// bool Prefetcher::hasRequest(u_int32_t cycle) {
// 	return false;
// }

// Request Prefetcher::getRequest(u_int32_t cycle) {
// 	Request req;
// 	return req;
// }

// void Prefetcher::completeRequest(u_int32_t cycle) { return; }

// void Prefetcher::cpuRequest(Request req) { return; }