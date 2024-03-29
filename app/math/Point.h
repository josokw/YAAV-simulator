#ifndef POINT_H
#define POINT_H

#include <tuple>

namespace math {

class CartVec;

/// Represents a point in 3D Cartesian coordinates.
/// A point has no dimensions, only position.
/// Can be translated by a vector (CartVec).
class Point
{
   /// Output format: [x,y,z]
   friend std::ostream &operator<<(std::ostream &os, const Point &rhs);
   /// Input format: [x,y,z]  extra whitespaces are allowed.
   friend std::istream &operator>>(std::istream &is, Point &rhs);
   friend bool operator==(const Point &lhs, const Point &rhs);
   friend bool operator!=(const Point &lhs, const Point &rhs);
   /// cv = p1 - p2
   friend math::CartVec operator-(const Point &lhs, const Point &rhs);
   /// Translation: p1 = p2 + cv
   friend Point operator+(const Point &lhs, const math::CartVec &rhs);
   /// Translation: p1 = p2 - cv
   friend Point operator-(const Point &lhs, const math::CartVec &rhs);

public:
   static const Point ORIGIN;
   static double eps;

   Point() = default;
   Point(double x, double y, double z = 0.0);
   // Point(const Point &) = default;
   // Point &operator=(const Point &) = default;
   // Point(Point &&) = default;
   // Point &operator=(Point &&) = default;
   // ~Point() = default;

   double get_x() const { return x_; }
   double get_y() const { return y_; }
   double get_z() const { return z_; }
   std::tuple<double, double, double> get_xyz() const { return {x_, y_, z_}; }
   void set_x(double x) { x_ = x; }
   void set_y(double y) { y_ = y; }
   void set_z(double z) { z_ = z; }

   /// Translation p += cv
   Point &operator+=(const math::CartVec &rhs);
   /// Translation p -= cv
   Point &operator-=(const math::CartVec &rhs);
   /// Rotates around z.
   void rotateAroundZ(double cosPhi, double sinPhi);
   /// Rotates around y.
   void rotateAroundY(double cosPhi, double sinPhi);
   /// Rotates around x.
   void rotateAroundX(double cosPhi, double sinPhi);
   /// Rotates around an arbitrarily rotation axis.
   // void rotateAround(const CartVec &axis, double cosPhi, double sinPhi);
   /// Calculates distance to other point.
   double distance(const Point &pnt) const;

private:
   double x_{0.0};
   double y_{0.0};
   double z_{0.0};
};

} // namespace math

#endif // POINT_H
