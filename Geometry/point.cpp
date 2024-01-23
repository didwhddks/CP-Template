template <typename T>
struct Point {
	T x, y;
	Point(const T& x, const T& y) {
		this->x = x;
		this->y = y;
	}

	Point operator+(const Point<T>& p) const {
		return Point<T>(x + p.x, y + p.y);
	}

	Point operator-(const Point<T>& p) const {
		return Point<T>(x - p.x, y - p.y);
	}

	Point operator*(const Point<T>& p) const {
		return Point<T>(x * p.x, y * p.y);
	}

	Point operator/(const Point<T>& p) const {
		return Point<T>(x / p.x, y / p.y);
	}

	bool operator==(const Point<T>& p) const {
		return x == p.x && y == p.y;
	}

	T dot(const Point<T>& p) const {
		return x * p.x + y * p.y;
	}

	T cross(const Point<T>& p) const {
		return x * p.y - y * p.x;
	}

	Point normal() const {
		return Point<T>(-y, x);
	}

	friend ostream& operator<<(ostream& os, const Point<T>& p) {
        os << p.x << " " << p.y;
        return os;
    }
};

template <typename T>
vector<Point<T>> getConvexHull(vector<Point<T>> pts) {
	int n = pts.size();
	if (n <= 2) {
		return vector<Point<T>>();
	}
	sort(pts.begin(), pts.end(), [&](const Point<T>& a, const Point<T>& b) {
		return (a.x < b.x) || (a.x == b.x && a.y < b.y);
	});

	vector<Point<T>> convexHull;
	int ptr = 0, mn = 1;
	for (int i = 0; i < n; ++i) {
		while (ptr > mn && (convexHull[ptr - 1] - convexHull[ptr - 2]).cross(
			pts[i] - convexHull[ptr - 2]) <= 0) {
			convexHull.pop_back();
			--ptr;
		}
		convexHull.push_back(pts[i]);
		++ptr;
	}
	mn = ptr;
	for (int i = n - 2; ~i; --i) {
		while (ptr > mn && (convexHull[ptr - 1] - convexHull[ptr - 2]).cross(
			pts[i] - convexHull[ptr - 2]) <= 0) {
			convexHull.pop_back();
			--ptr;
		}
		convexHull.push_back(pts[i]);
		++ptr;
	}
	if (int(convexHull.size()) > 1) {
		convexHull.pop_back();
	}
	return convexHull;
}