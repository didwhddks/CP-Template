vector<Point> getConvexHull(vector<Point> pts) {
	int n=pts.size();
	auto cmp=[](const Point& p1, const Point& p2) {
		return p1.x<p2.x||p1.x==p2.x&&p1.y<p2.y;
	};
	sort(pts.begin(), pts.end(), cmp);
	vector<Point> convexHull;
	int ptr=0, m=1;
	for(int i=0; i<n; ++i) {
		while(ptr>m&&(convexHull[ptr-1]-convexHull[ptr-2]).cross(pts[i]-convexHull[ptr-2])<=0)
			convexHull.pop_back(), --ptr;
		convexHull.push_back(pts[i]), ++ptr;
	}
	m=ptr;
	for(int i=n-2; ~i; --i) {
		while(ptr>m&&(convexHull[ptr-1]-convexHull[ptr-2]).cross(pts[i]-convexHull[ptr-2])<=0)
			convexHull.pop_back(), --ptr;
		convexHull.push_back(pts[i]), ++ptr;
	}
	if((int)convexHull.size()>1) convexHull.pop_back();
	return convexHull;
}

template <class T>
T rotatingClaiper(const vt<Point<T>>& ConvexHull) { // 計算最遠點對距離的平方
	int n=sz(ConvexHull), t=1;
	T ans=0;
	ConvexHull.pb(ConvexHull[0]); // 起點放在後面可以省略特判
	FOR(n) {
		Point<T> now=ConvexHull[i+1]-ConvexHull[i]; // 當前這條線的方向向量
		// 找出距離邊 (i,i+1) 最遠的點 t
		while(now.cross(ConvexHull[t+1]-ConvexHull[i])>now.cross(ConvexHull[t]-ConvexHull[i]))
			t=(t+1)%n;
		ans=max(ans, (ConvexHull[i]-ConvexHull[t]).abs2());
		// 其實可以簡化成： ans = max(ans, (ConvexHull[i]-ConvexHull[t]).abs2() );
	}
	return ans;
}
