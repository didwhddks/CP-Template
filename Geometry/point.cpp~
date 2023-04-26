template <class T>
struct Point {
	T x, y;
	Point(const T& x, const T& y):x(x), y(y) {}
	Point operator+(const Point& p) const {
		return Point(x+p.x, y+p.y);
	}
	Point operator-(const Point& p) const {
		return Point(x-p.x, y-p.y);
	}
	Point operator*(const Point& p) const {
		return Point(x*p.x, y*p.y);
	}
	Point operator/(const Point& p) const {
		return Point(x/p.x, y/p.y);
	}
	bool operator==(const Point& p) const {
		return x==p.x&&y==p.y;
	}
	T dot(const Point& p) const {
		return x*p.x+y*p.y;
	}
	T cross(const Point& p) const {
		return x*p.y-y*p.x;
	}
	Point normal() const {
		return Point(-y, x);
	}
	T abs2() const {
		return dot(*this);
	}
	T rad(const Point& p) const {
		return fabs(atan2(fabs(cross(p)), dot(p)));
	}
};
