#include "CartVec.h"
#include "catch.hpp"

#include <sstream>

// Catch has two natural expression assertion macro's:
// - REQUIRE() stops at first failure.
// - CHECK() continues after failure.

// There are two variants to support decomposing negated expressions:
// - REQUIRE_FALSE() stops at first failure.
// - CHECK_FALSE() continues after failure.

TEST_CASE("math::CartVec class")
{
   SECTION("Constants")
   {
      REQUIRE(math::CartVec::ZERO.get_x() == Approx(0.0));
      REQUIRE(math::CartVec::ZERO.get_y() == Approx(0.0));
      REQUIRE(math::CartVec::ZERO.get_z() == Approx(0.0));

      REQUIRE(math::CartVec::UNIT_X.get_x() == Approx(1.0));
      REQUIRE(math::CartVec::UNIT_X.get_y() == Approx(0.0));
      REQUIRE(math::CartVec::UNIT_X.get_z() == Approx(0.0));

      REQUIRE(math::CartVec::UNIT_Y.get_x() == Approx(0.0));
      REQUIRE(math::CartVec::UNIT_Y.get_y() == Approx(1.0));
      REQUIRE(math::CartVec::UNIT_Y.get_z() == Approx(0.0));

      REQUIRE(math::CartVec::UNIT_Z.get_x() == Approx(0.0));
      REQUIRE(math::CartVec::UNIT_Z.get_y() == Approx(0.0));
      REQUIRE(math::CartVec::UNIT_Z.get_z() == Approx(1.0));
   }

   SECTION("Ctors")
   {
      math::CartVec cv1; // default initialisation

      REQUIRE(cv1.get_x() == Approx(0.0));
      REQUIRE(cv1.get_y() == Approx(0.0));
      REQUIRE(cv1.get_z() == Approx(0.0));

      math::CartVec cv2{1.1, 2.2};  // z is default 0.0

      REQUIRE(cv2.get_x() == Approx(1.1));
      REQUIRE(cv2.get_y() == Approx(2.2));
      REQUIRE(cv2.get_z() == Approx(0.0));

      math::CartVec cv3{cv1}; // copy ctor

      REQUIRE(cv3.get_x() == Approx(0.0));
      REQUIRE(cv3.get_y() == Approx(0.0));
      REQUIRE(cv3.get_z() == Approx(0.0));
   }

   SECTION("Operators")
   {
      math::CartVec cv1{1.0, 0.0, 0.5};
      math::CartVec cv2{1.0, 1.0, 0.5};
      math::CartVec cv3;

      cv3 = cv1;
      REQUIRE(cv3.get_x() == Approx(1.0));
      REQUIRE(cv3.get_y() == Approx(0.0));
      REQUIRE(cv3.get_z() == Approx(0.5));

      cv3 = cv1 + cv2;
      REQUIRE(cv3.get_x() == Approx(2.0));
      REQUIRE(cv3.get_y() == Approx(1.0));
      REQUIRE(cv3.get_z() == Approx(1.0));

      cv3 = cv1 - cv2;
      REQUIRE(cv3.get_x() == Approx(0.0));
      REQUIRE(cv3.get_y() == Approx(-1.0));
      REQUIRE(cv3.get_z() == Approx(0.0));

      cv3 = 3 * cv1;
      REQUIRE(cv3.get_x() == Approx(3.0));
      REQUIRE(cv3.get_y() == Approx(0.0));
      REQUIRE(cv3.get_z() == Approx(1.5));

      cv3 = cv1 * 3;
      REQUIRE(cv3.get_x() == Approx(3.0));
      REQUIRE(cv3.get_y() == Approx(0.0));
      REQUIRE(cv3.get_z() == Approx(1.5));

      REQUIRE(cv1 == cv1);
      REQUIRE_FALSE(cv1 == cv2);

      REQUIRE_FALSE(cv1 != cv1);
      REQUIRE(cv1 != cv2);
   }

   SECTION("Inner (dot) product")
   {
      math::CartVec cv1{1.0, 1.0, 1.0};
      math::CartVec cv2{-1.0, 1.0, 0.0};

      REQUIRE(cv1.dot(cv2) == Approx(0.0));
   }

   SECTION("Cross product")
   {
      math::CartVec cv1{1.0, 0.0, 0.0};
      math::CartVec cv2{0.0, 1.0, 0.0};

      REQUIRE(cv1.cross(cv2) == math::CartVec{0, 0, 1});
   }

   SECTION("Length")
   {
      REQUIRE(math::CartVec::UNIT_X.length() == Approx(1.0));
      REQUIRE(math::CartVec::UNIT_Y.length() == Approx(1.0));
      REQUIRE(math::CartVec::UNIT_Z.length() == Approx(1.0));
      REQUIRE(math::CartVec::ZERO.length() == Approx(0.0));
   }

   SECTION("Input and output streams")
   {
      std::stringstream ss;
      math::CartVec cv1;
      ss << "[10.11, 20.22, 30.33]" << std::ends;
      ss >> cv1;
      REQUIRE(cv1 == math::CartVec{10.11, 20.22, 30.33});

      // Syntax error in input stream
      ss << "[10.11, 20.22 30.33]" << std::ends;
      math::CartVec cv2{-1.0, -2.0, -3.0};
      math::CartVec cv3{cv2};
      ss >> cv2;
      REQUIRE(cv2 == cv3);

      math::CartVec cv4{1.1, -2.2, 3.3};
      ss = std::stringstream{};
      ss << cv4;
      REQUIRE(ss.str() == std::string("[1.100,-2.200,3.300]"));
   }

   SECTION("get()")
   {
      math::CartVec cv{1.1, -2.2, 3.3};
      auto [x, y, z] = cv.get_xyz();  // structured bindings

      REQUIRE(x == Approx(1.1));
      REQUIRE(y == Approx(-2.2));
      REQUIRE(z == Approx(3.3));
   }
}
