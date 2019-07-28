#include "Point.h"
#include "Polygon.h"
#include "catch.hpp"

TEST_CASE("Polygon class")
{
   SECTION("Is inside")
   {
      math::Polygon p1{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}};

      REQUIRE(p1.isInside({0.5, 0.25}));
      REQUIRE_FALSE(p1.isInside({-0.5, 0.25}));

      math::Polygon p2{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.5, 0.5}};

      REQUIRE(p2.isInside({0.25, 0.25}));
      REQUIRE_FALSE(p2.isInside({-0.25, -0.25}));

      std::vector<Point> points1{{0.5, 0.25}, {0.25, 0.25}};
      REQUIRE(p2.isInside(points1));
      std::vector<Point> points2{{0.5, 0.25}, {-5.0, 5.0}, {0.25, 0.25}};
      REQUIRE_FALSE(p2.isInside(points2));
   }

   SECTION("Normal")
   {
      math::Polygon p1{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}};

      REQUIRE(p1.getNormal() == CartVec::UNIT_Z);

      math::Polygon p2{{0.1, 0.0}, {1.1, 0.0}, {1.0, 1.0}, {0.5, 0.6}};

      REQUIRE(p2.getNormal() == CartVec::UNIT_Z);
   }

   //  bool isFacing(const Point &point) const;
   // /// Get edge (pair of two vertices) by its index, starts at index 0.

   SECTION("Get closest point to edge")
   {
      math::Polygon p{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.5, 0.75}};
      math::Edge edge{p.getEdge(0)};

      REQUIRE(edge.getStart() == Point{0.0, 0.0});
      REQUIRE(edge.getEnd() == Point{1.0, 0.0});

      edge = p.getEdge(0);
      REQUIRE(edge.getStart() == Point{0.0, 0.0});
      REQUIRE(edge.getEnd() == Point{1.0, 0.0});

      edge = p.getEdge(1);
      REQUIRE(edge.getStart() == Point{1.0, 0.0});
      REQUIRE(edge.getEnd() == Point{1.0, 1.0});

      edge = p.getEdge(2);
      REQUIRE(edge.getStart() == Point{1.0, 1.0});
      REQUIRE(edge.getEnd() == Point{0.5, 0.75});

      edge = p.getEdge(3);
      REQUIRE(edge.getStart() == Point{0.5, 0.75});
      REQUIRE(edge.getEnd() == Point{0.0, 0.0});

      REQUIRE(p.getClosestPointToEdge(0, Point{-1.0, 0.0}) == Point{0.0, 0.0});
      REQUIRE(p.getClosestPointToEdge(0, Point{0.0, -1.0}) == Point{0.0, 0.0});

      REQUIRE(p.getClosestPointToEdge(1, Point{-1.0, 0.0}) == Point{1.0, 0.0});
      REQUIRE(p.getClosestPointToEdge(1, Point{0.0, -1.0}) == Point{1.0, 0.0});

      CHECK(p.getClosestPointToEdge(2, Point{-1.0, 0.0}) == Point{0.5, 0.75});
      CHECK(p.getClosestPointToEdge(2, Point{0.0, -1.0}) == Point{0.5, 0.75});

      CHECK(p.getClosestPointToEdge(3, Point{-1.0, 0.0}) == Point{0.0, 0.0});
      CHECK(p.getClosestPointToEdge(3, Point{0.0, -1.0}) == Point{0.0, 0.0});
   }
}
