#ifndef DIRT_H
#define DIRT_H

#include "Drawable.h"
#include "XYZrZ.h"

class Dirt : public Drawable
{
public:
   Dirt(double R, const XYZrZ &xyzRz);
   Dirt(const Dirt &dirt);
   Dirt &operator=(const Dirt &dirt);
   ~Dirt() override;

   void draw() const override;
   XYZrZ getXYZrZ() const { return _XYZrZ; }
   double getR() const { return _R; }

private:
   double _R;
   XYZrZ _XYZrZ;
   GLUquadricObj *_pBody;
};

#endif // DIRT_H
