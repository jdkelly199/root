#include <ROOT/RDataFrame.hxx>
#include "gtest/gtest.h"
using namespace ROOT::RDF;

class Dummy {
};

TEST(RResultPtr, DefCtor)
{
   RResultPtr<Dummy> p1, p2;
   EXPECT_TRUE(p1 == nullptr);
   EXPECT_TRUE(nullptr == p1);
   EXPECT_TRUE(p1 == p2);
   EXPECT_TRUE(p2 == p1);
}

TEST(RResultPtr, CopyCtor)
{
   ROOT::RDataFrame d(1);
   auto hasRun = false;
   auto m = d.Define("i", [&hasRun]() {
                hasRun = true;
                return (int)1;
             }).Mean<int>("i");
   auto mc = m;
   EXPECT_TRUE(mc == m);
   EXPECT_TRUE(m == mc);

   EXPECT_FALSE(hasRun);

   EXPECT_EQ(*mc, *m);

   EXPECT_TRUE(hasRun);
}

TEST(RResultPtr, ImplConv)
{
   RResultPtr<Dummy> p1;
   EXPECT_FALSE(p1);

   ROOT::RDataFrame d(1);
   auto hasRun = false;
   auto m = d.Define("i", [&hasRun]() {
                hasRun = true;
                return (int)1;
             }).Histo1D<int>("i");

   EXPECT_TRUE(m);
   EXPECT_FALSE(hasRun);

   *m;

   EXPECT_TRUE(m);
   EXPECT_TRUE(hasRun);
}
