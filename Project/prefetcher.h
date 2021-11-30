// Mohamed Rayyan
// mrayy002
// 862037325

#ifndef PREFETCHER_H
#define PREFETCHER_H

#include <sys/types.h>
#include <iostream>
#include <bitset>
#include <queue>
#include <vector>
#include <map>

#include "mem-sim.h"
struct Request;

using namespace std;

class Prefetcher {
  private:
	bool _ready;
	queue<u_int32_t> _req_queue;
	vector<u_int32_t> _history;
  public:
	Prefetcher();
	~Prefetcher();

	int getIndex(vector<u_int32_t> v, int e) {
		vector<u_int32_t> indexes;
		for(int i =0; i <v.size(); i++) {
			if(v[i] ==e) {
				indexes.push_back(i);
			}
		}
		if(indexes.size() ==0) {
			return -1;
		}

		return indexes[indexes.size() -1];
	}

	// should return true if a request is ready for this cycle
	bool hasRequest(u_int32_t cycle);

	// request a desired address be brought in
	Request getRequest(u_int32_t cycle);

	// this function is called whenever the last prefetcher request was successfully sent to the L2
	void completeRequest(u_int32_t cycle);

	/*
	 * This function is called whenever the CPU references memory.
	 * Note that only the addr, pc, load, issuedAt, and HitL1 should be considered valid data
	 */
	void cpuRequest(Request req);
};

#endif
