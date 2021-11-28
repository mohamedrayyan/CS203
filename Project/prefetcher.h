#ifndef PREFETCHER_H
#define PREFETCHER_H

#include <sys/types.h>
#include <iostream>
#include <queue>
#include <vector>
#include <map>

#include "mem-sim.h"
// struct Request;

using namespace std;

struct details {
	u_int32_t lastAddr;
	u_int32_t pc;
	u_int32_t lastPrefetch;
	vector<u_int32_t> deltas;
};

class Prefetcher {
  private:
	bool _ready;
	bool _pattern;
	queue<u_int32_t> _req_queue;
	vector<u_int32_t> _history;
	vector<u_int32_t> candidates;
	vector<u_int32_t> prefetches;
	vector<u_int32_t> reqqueue;
	vector<u_int32_t> inFlight;
	map<u_int32_t, details> table;
	map<u_int32_t, bool> mshr;
  public:
	Prefetcher();
	~Prefetcher();

	int getIndex(vector<u_int32_t> v, int e) {
		for(int i =0; i <v.size(); i++) {
			if(v[i] ==e) {
				return i;
			}
		}
		return -1;
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

	vector<u_int32_t> deltaCorrelation(details entry);
	vector<u_int32_t> prefetchFilter(details entry, vector<u_int32_t> candids);
	void issuePrefetches(vector<u_int32_t> prefets);
};

#endif
