#ifndef XYZRZ_H
#define XYZRZ_H

#include "CartVec.h"
#include "Drawable.h"
#include "MathDef.h"

#include <cmath>
#include <iostream>
#include <tuple>

/// Represents the combination of a position represented by a #Point
/// [x,y,z] and a rotation around de Z-axis #Rz in degrees.
/// 4 DOF: [[x, y, z], Rz].
class XYZrZ : public Drawable
{
   friend std::ostream &operator<<(std::ostream &os, const XYZrZ &rhs);
   /// Translation: XYZrZ1 = XYZrZ2 + v
   friend XYZrZ operator+(const XYZrZ &lhs, const CartVec &rhs);
   /// Translation: XYZrZ1 = XYZrZ2 - v
   friend XYZrZ operator-(const XYZrZ &lhs, const CartVec &rhs);
   /// Rotation: XYZrZ1 = XYZrZ2 + rZ
   /// [[x,y,z], rZ] + rhs => [[x,y,z], rZ + rhs]
   friend XYZrZ operator+(const XYZrZ &lhs, double rhs);
   /// Rotation: XYZrZ1 = XYZrZ2 - rZ
   /// [[x,y,z], rZ] - rhs => [[x,y,z], rZ - rhs]
   friend XYZrZ operator+(const XYZrZ &lhs, double rhs);

public:
   XYZrZ() = default;
   XYZrZ(double x, double y, double z, double Rz);
   XYZrZ(double x, double y, double z)
      : XYZrZ(x, y, z, 0.0)
   {
   }
   XYZrZ(const Point &xyz);
   XYZrZ(const Point &xyz, double Rz);

   /// Compound assignment operator [[x,y,z], Rz] += [a,b,c] =>
   /// [[x+a,y+b,z+c], Rz]
   XYZrZ &operator+=(const CartVec &rhs)
   {
      position += rhs;
      return *this;
   }
   /// [[x,y,z], Rz] -= [a,b,c] => [[x-a,y-b,z-c], Rz]
   XYZrZ &operator-=(const CartVec &rhs)
   {
      position -= rhs;
      return *this;
   }
   /// Compound assignment operator [[x,y,z], Rz] += rz =>
   /// [[x,y,z], Rz + rz]
   XYZrZ &operator+=(double rhs)
   {
      Rz += rhs;
      return *this;
   }
   /// Compound assignment operator [[x,y,z], Rz] -= rz =>
   /// [[x,y,z], Rz - rz]
   XYZrZ &operator-=(double rhs)
   {
      Rz -= rhs;
      return *this;
   }

   Point getPosition() const { return position; }
   double getRz() const { return Rz; }
   std::tuple<Point, double> getPositionRz() const { return {position, Rz}; }

   CartVec heading() const
   {
      return {cos(math::toRadians(Rz)), sin(math::toRadians(Rz))};
   }

   Point atDistance(double d) const
   {
      return {position.get_x() + d * cos(math::toRadians(Rz)),
              position.get_y() + d * sin(math::toRadians(Rz)),
              position.get_z()};
   }

   void draw() const override;

//private:
   Point position{Point::ORIGIN};
   /// In degrees
   double Rz{0.0};
};

#endif // XYZRZ_H
