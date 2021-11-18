// /*
//  *
//  * File: prefetcher.C
//  * Author: Sat Garcia (sat@cs)
//  * Description: This simple prefetcher waits until there is a D-cache miss then 
//  * requests location (addr + 16), where addr is the address that just missed 
//  * in the cache.
//  *
//  */

#include "prefetcher.h"
#include <stdio.h>
#include <iostream>

Prefetcher::Prefetcher() {
	_ready = false;
}

bool Prefetcher::hasRequest(u_int32_t cycle) {
	return _ready;
}

Request Prefetcher::getRequest(u_int32_t cycle) {
	return _nextReq;
}

void Prefetcher::completeRequest(u_int32_t cycle) {
	if(!_req_queue.empty()) {
		_nextReq.addr =_req_queue.front();
		_req_queue.pop();
		_ready =true;
	}
	else {
		_ready = false;
	}
}

void Prefetcher::cpuRequest(Request req) { 
	if(!_ready && !req.HitL1) {
		std::cout <<req.addr <<std::endl;
		for(int i =1; i <=4; i++) {
			_req_queue.push(req.addr +(16*i));
		}
		_ready = true;
	}
}

/*
 *
 * File: prefetcher.C
 * Author: Sat Garcia (sat@cs)
 * Description: This simple prefetcher waits until there is a D-cache miss then 
 * requests location (addr + 16), where addr is the address that just missed 
 * in the cache.
 *
 */


// Prefetcher::Prefetcher() { _ready = false; }

// bool Prefetcher::hasRequest(u_int32_t cycle) { return _ready; }

// Request Prefetcher::getRequest(u_int32_t cycle) { return _nextReq; }

// void Prefetcher::completeRequest(u_int32_t cycle) { _ready = false; }

// void Prefetcher::cpuRequest(Request req) { 
// 	if(!_ready && !req.HitL1) {
// 		_nextReq.addr = req.addr + 16;
// 		_ready = true;
// 	}
// }
