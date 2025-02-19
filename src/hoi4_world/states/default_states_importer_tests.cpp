#include <sstream>

#include "external/commonItems/external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/commonItems/external/googletest/googletest/include/gtest/gtest.h"
#include "src/hoi4_world/states/default_state.h"
#include "src/hoi4_world/states/default_states_importer.h"



TEST(Hoi4worldStatesDefaultstatesimporterTests, NoStateFilesMeansNoStates)
{
   commonItems::ModFilesystem filesystem("test_files/hoi4_world/NoStateFilesMeansNoStates", {});
   const auto default_states = hoi4::ImportDefaultStates(filesystem);

   EXPECT_TRUE(default_states.empty());
}


TEST(Hoi4worldStatesDefaultstatesimporterTests, DefaultStatesCanBeImported)
{
   commonItems::ModFilesystem filesystem("test_files/hoi4_world/DefaultStatesCanBeImported", {});
   const auto default_states = hoi4::ImportDefaultStates(filesystem);

   EXPECT_THAT(default_states,
       testing::UnorderedElementsAre(testing::Pair(1,
                                         hoi4::DefaultState({.impassable = true,
                                             .owner_tag = "FRA",
                                             .provinces = {3838, 9851, 11804},
                                             .civilian_factories = 1,
                                             .military_factories = 0,
                                             .dockyards = 2,
                                             .resources = {{"steel", 5}, {"test_resource", 42}}})),
           testing::Pair(2,
               hoi4::DefaultState({.impassable = false,
                   .owner_tag = "ITA",
                   .provinces = {923, 6862, 9794, 9904, 11751, 11846, 11882},
                   .civilian_factories = 4,
                   .military_factories = 1,
                   .dockyards = 0,
                   .resources = {}}))));
}