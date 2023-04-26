template <class T>
vt<Point<T>> getConvexHull(const vt<Point<T>>& pts) {
	auto cmp=[](const Point<T>& p1, const Point<T>& p2) {
		return p1.x<p2.x||p1.x==p2.x&&p1.y<p2.y;
	};
	sort(all(pts), cmp);
	vt<Point<T>> convexHull;
	int ptr=0, m;
	FOR(n) {
		while(ptr>=2&&(convexHull[ptr-1]-convexHull[ptr-2]).cross(pts[i]-convexHull[ptr-2])<0)
			convexHull.pop_back(), --ptr;
		convexHull.pb(pts[i]), ++ptr;
	}
	m=ptr+1;
	FOR(i, n-2, -1, -1) {
		while(ptr>=m&&(convexHull[ptr-1]-convexHull[ptr-2]).cross(pts[i]-convexHull[ptr-2])<0)
			convexHull.pop_back(), --ptr;
		convexHull.pb(pts[i]), ++ptr;
	}
	if(sz(convexHull)>1) convexHull.pop_back();
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
