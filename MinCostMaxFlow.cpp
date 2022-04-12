struct MinCostFlow {
	const int inf = 0x3f3f3f3f;
	int n;
	vector<array<int, 3>> e;
	vector<vector<int>> mp;
	vector<int> h, dist, pre;
	MinCostFlow(int n) : n(n), mp(n) {}
	bool dijkstra(int S, int T) {
		dist.assign(n, inf);
		pre.assign(n, -1);
		priority_queue<pii, vector<pii>, greater<>> q;
		dist[S] = 0;
		q.push({0, S});
		while (!q.empty()) {
			auto [dis, u] = q.top();
			q.pop();
			if (dis > dist[u])
				continue;
			for (int i : mp[u]) {
				auto [v, f, c] = e[i];
				if (f > 0 && dist[v] > dist[u] + h[u] - h[v] + c) {
					dist[v] = dist[u] + h[u] - h[v] + c;
					pre[v] = i;
					q.push({dist[v], v});
				}
			}
		}
		return dist[T] != inf;
	}
	void add(int u, int v, int f, int c) {
		mp[u].push_back(e.size());
		e.push_back({v, f, c});
		mp[v].push_back(e.size());
		e.push_back({u, 0, -c});
	}
	pii minCostMaxFlow(int S, int T) {
		int flow = 0, cost = 0;
		h.assign(n, 0);
		while (dijkstra(S, T)) {
			for (int i = 0; i < n; i++)
				if (dist[i] < inf)
					h[i] += dist[i];
			int t = INF;
			for (int i = T; i != S; i = e[pre[i] ^ 1][0])
				t = min(t, e[pre[i]][1]);
			for (int i = T; i != S; i = e[pre[i] ^ 1][0]) {
				e[pre[i]][1] -= t, e[pre[i] ^ 1][1] += t;
			}
			flow += t, cost += t * h[T];
		}
		return make_pair(flow, cost);
	}
};
