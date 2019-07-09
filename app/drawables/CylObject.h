#ifndef CYLOBJECT_H
#define CYLOBJECT_H

#include "Drawable.h"
#include "MathDef.h"
#include "XYZrZ.h"

#include <iosfwd>

/// Cylindrical shaped object (e.g. chair and table legs).
class CylObject : public Drawable
{
   /// Input format: R H x y z Rz
   friend std::istream &operator>>(std::istream &is, CylObject &rhs);

public:
   CylObject(double R, double H, const XYZrZ &xyzRz);
   CylObject(const CylObject &cylobj);
   CylObject &operator=(const CylObject &cylobj);
   ~CylObject() override;

   void draw() const override;
   math::circle_t getCollisionShape() const
   {
      return {_XYZrZ.position, _R};
   }
// private:
   double _R;
   double _H;
   XYZrZ _XYZrZ;
   GLUquadricObj *_pBody;
};

#endif // CYLOBJECT_H
