#ifndef POINT_H
#define POINT_H

#include <tuple>

class CartVec;

/// Represents a point in 3D Cartesian coordinates.
/// Can be translated by a vector (CartVec).
class Point
{
   friend bool operator==(const Point &lhs, const Point &rhs);
   friend bool operator!=(const Point &lhs, const Point &rhs);
   /// cv = p1 - p2
   friend CartVec operator-(const Point &lhs, const Point &rhs);
   /// Translation: p1 = p2 + cv
   friend Point operator+(const Point &lhs, const CartVec &rhs);
   /// Translation: p1 = p2 - cv
   friend Point operator-(const Point &lhs, const CartVec &rhs);

public:
   static const Point ORIGIN;
   static double eps;

   Point() = default;
   Point(double x, double y, double z = 0.0);

   double get_x() const { return x_; }
   double get_y() const { return y_; }
   double get_z() const { return z_; }
   std::tuple<double, double, double> get() const { return {x_, y_, z_}; }
   void set_x(double x) { x_ = x; }
   void set_y(double y) { y_ = y; }
   void set_z(double z) { z_ = z; }

   /// Translation p += cv
   Point &operator+=(const CartVec &rhs);
   /// Translation p -= cv
   Point &operator-=(const CartVec &rhs);

private:
   double x_{0.0};
   double y_{0.0};
   double z_{0.0};
};

#endif // POINT_H
