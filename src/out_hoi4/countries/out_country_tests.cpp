#include <filesystem>
#include <fstream>
#include <sstream>

#include "external/commonItems/OSCompatibilityLayer.h"
#include "external/commonItems/external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/commonItems/external/googletest/googletest/include/gtest/gtest.h"
#include "external/fmt/include/fmt/format.h"
#include "src/hoi4_world/countries/hoi4_country.h"
#include "src/out_hoi4/countries/out_country.h"



namespace out
{

TEST(Outhoi4CountriesOutcountryTests, CommonCountriesFileIsCreatedWithTagForName)
{
   commonItems::TryCreateFolder("output");
   commonItems::TryCreateFolder("output/CommonCountriesFileIsCreatedWithTagForName");
   commonItems::TryCreateFolder("output/CommonCountriesFileIsCreatedWithTagForName/common");
   commonItems::TryCreateFolder("output/CommonCountriesFileIsCreatedWithTagForName/common/countries");

   const hoi4::Country country({.tag = "TAG", .color = commonItems::Color(std::array{1, 2, 3})});
   const hoi4::Country country_two({.tag = "TWO", .color = commonItems::Color(std::array{2, 4, 6})});

   OutputCommonCountriesFile("CommonCountriesFileIsCreatedWithTagForName", country);
   OutputCommonCountriesFile("CommonCountriesFileIsCreatedWithTagForName", country_two);

   ASSERT_TRUE(
       commonItems::DoesFileExist("output/CommonCountriesFileIsCreatedWithTagForName/common/countries/TAG.txt"));
   std::ifstream country_file("output/CommonCountriesFileIsCreatedWithTagForName/common/countries/TAG.txt");
   ASSERT_TRUE(country_file.is_open());
   std::stringstream country_file_stream;
   std::copy(std::istreambuf_iterator<char>(country_file),
       std::istreambuf_iterator<char>(),
       std::ostreambuf_iterator<char>(country_file_stream));
   country_file.close();

   std::stringstream expected_one;
   expected_one << "graphical_culture = western_european_gfx\n";
   expected_one << "graphical_culture_2d = western_european_2d\n";
   expected_one << "color = rgb { 1 2 3 }";
   EXPECT_EQ(country_file_stream.str(), expected_one.str());

   ASSERT_TRUE(
       commonItems::DoesFileExist("output/CommonCountriesFileIsCreatedWithTagForName/common/countries/TWO.txt"));
   std::ifstream country_file_two("output/CommonCountriesFileIsCreatedWithTagForName/common/countries/TWO.txt");
   ASSERT_TRUE(country_file_two.is_open());
   std::stringstream country_file_two_stream;
   std::copy(std::istreambuf_iterator<char>(country_file_two),
       std::istreambuf_iterator<char>(),
       std::ostreambuf_iterator<char>(country_file_two_stream));
   country_file_two.close();

   std::stringstream expected_two;
   expected_two << "graphical_culture = western_european_gfx\n";
   expected_two << "graphical_culture_2d = western_european_2d\n";
   expected_two << "color = rgb { 2 4 6 }";
   EXPECT_EQ(country_file_two_stream.str(), expected_two.str());
}


TEST(Outhoi4CountriesOutcountryTests, ExceptionIfCountriesFileNotOpened)
{
   const hoi4::Country country({.tag = "TAG"});

   EXPECT_THROW(OutputCommonCountriesFile("/dev/null/COM", country), std::runtime_error);
}


TEST(Outhoi4CountriesOutcountryTests, DefaultsAreOutputToCommonCountriesFile)
{
   commonItems::TryCreateFolder("output");
   commonItems::TryCreateFolder("output/DefaultsAreOutputToCommonCountriesFile");
   commonItems::TryCreateFolder("output/DefaultsAreOutputToCommonCountriesFile/common");
   commonItems::TryCreateFolder("output/DefaultsAreOutputToCommonCountriesFile/common/countries");

   const hoi4::Country country({.tag = "TAG"});
   OutputCommonCountriesFile("DefaultsAreOutputToCommonCountriesFile", country);

   ASSERT_TRUE(commonItems::DoesFileExist("output/DefaultsAreOutputToCommonCountriesFile/common/countries/TAG.txt"));
   std::ifstream country_file("output/DefaultsAreOutputToCommonCountriesFile/common/countries/TAG.txt");
   ASSERT_TRUE(country_file.is_open());
   std::stringstream country_file_stream;
   std::copy(std::istreambuf_iterator<char>(country_file),
       std::istreambuf_iterator<char>(),
       std::ostreambuf_iterator<char>(country_file_stream));
   country_file.close();

   std::stringstream expected_one;
   expected_one << "graphical_culture = western_european_gfx\n";
   expected_one << "graphical_culture_2d = western_european_2d\n";
   expected_one << "color = rgb { 0 0 0 }";
   EXPECT_EQ(country_file_stream.str(), expected_one.str());
}


TEST(Outhoi4CountriesOutcountryTests, ColorCanBeSetInCommonCountriesFile)
{
   commonItems::TryCreateFolder("output");
   commonItems::TryCreateFolder("output/ColorCanBeSetInCommonCountriesFile");
   commonItems::TryCreateFolder("output/ColorCanBeSetInCommonCountriesFile/common");
   commonItems::TryCreateFolder("output/ColorCanBeSetInCommonCountriesFile/common/countries");

   const hoi4::Country country({.tag = "TAG", .color = commonItems::Color(std::array{1, 2, 3})});
   OutputCommonCountriesFile("ColorCanBeSetInCommonCountriesFile", country);

   ASSERT_TRUE(commonItems::DoesFileExist("output/ColorCanBeSetInCommonCountriesFile/common/countries/TAG.txt"));
   std::ifstream country_file("output/ColorCanBeSetInCommonCountriesFile/common/countries/TAG.txt");
   ASSERT_TRUE(country_file.is_open());
   std::stringstream country_file_stream;
   std::copy(std::istreambuf_iterator<char>(country_file),
       std::istreambuf_iterator<char>(),
       std::ostreambuf_iterator<char>(country_file_stream));
   country_file.close();

   std::stringstream expected_one;
   expected_one << "graphical_culture = western_european_gfx\n";
   expected_one << "graphical_culture_2d = western_european_2d\n";
   expected_one << "color = rgb { 1 2 3 }";
   EXPECT_EQ(country_file_stream.str(), expected_one.str());
}


TEST(Outhoi4CountriesOutcountryTests, TagsAreAddedToTagsFile)
{
   const hoi4::Country country({.tag = "TAG"});
   const hoi4::Country country_two({.tag = "TWO"});

   std::ofstream tags_file("tags_file.txt");
   ASSERT_TRUE(tags_file.is_open());

   OutputCommonCountryTag(country, tags_file);
   OutputCommonCountryTag(country_two, tags_file);

   tags_file.close();

   std::ifstream country_file("tags_file.txt");
   ASSERT_TRUE(country_file.is_open());
   std::stringstream country_file_stream;
   std::copy(std::istreambuf_iterator<char>(country_file),
       std::istreambuf_iterator<char>(),
       std::ostreambuf_iterator<char>(country_file_stream));
   country_file.close();
   EXPECT_EQ(country_file_stream.str(),
       "TAG = \"countries/TAG.txt\"\n"
       "TWO = \"countries/TWO.txt\"\n");
}


TEST(Outhoi4CountriesOutcountryTests, CountryHistoryFileIsCreatedWithTagForName)
{
   commonItems::TryCreateFolder("output");
   commonItems::TryCreateFolder("output/CountryHistoryFileIsCreatedWithTagForName");
   commonItems::TryCreateFolder("output/CountryHistoryFileIsCreatedWithTagForName/history");
   commonItems::TryCreateFolder("output/CountryHistoryFileIsCreatedWithTagForName/history/countries");

   const hoi4::Country country({.tag = "TAG"});
   const hoi4::Country country_two({.tag = "TWO"});

   OutputCountryHistory("CountryHistoryFileIsCreatedWithTagForName", country);
   OutputCountryHistory("CountryHistoryFileIsCreatedWithTagForName", country_two);

   ASSERT_TRUE(
       commonItems::DoesFileExist("output/CountryHistoryFileIsCreatedWithTagForName/history/countries/TAG.txt"));
   ASSERT_TRUE(
       commonItems::DoesFileExist("output/CountryHistoryFileIsCreatedWithTagForName/history/countries/TWO.txt"));
}


TEST(Outhoi4CountriesOutcountryTests, ExceptionIfHistoryFileNotOpened)
{
   const hoi4::Country country({.tag = "TAG"});

   EXPECT_THROW(OutputCountryHistory("/dev/null/COM", country), std::runtime_error);
}


TEST(Outhoi4CountriesOutcountryTests, DefaultsAreSetInCountryHistoryFile)
{
   commonItems::TryCreateFolder("output");
   commonItems::TryCreateFolder("output/DefaultsAreSetInCountryHistoryFile");
   commonItems::TryCreateFolder("output/DefaultsAreSetInCountryHistoryFile/history");
   commonItems::TryCreateFolder("output/DefaultsAreSetInCountryHistoryFile/history/countries");

   const hoi4::Country country({.tag = "TAG"});
   OutputCountryHistory("DefaultsAreSetInCountryHistoryFile", country);

   ASSERT_TRUE(commonItems::DoesFileExist("output/DefaultsAreSetInCountryHistoryFile/history/countries/TAG.txt"));
   std::ifstream country_file("output/DefaultsAreSetInCountryHistoryFile/history/countries/TAG.txt");
   ASSERT_TRUE(country_file.is_open());
   std::stringstream country_file_stream;
   std::copy(std::istreambuf_iterator<char>(country_file),
       std::istreambuf_iterator<char>(),
       std::ostreambuf_iterator<char>(country_file_stream));
   country_file.close();

   std::stringstream expected_one;
   expected_one << "\n";
   expected_one << "oob = \"TAG_1936\"\n";
   expected_one << "set_research_slots = 3\n";
   expected_one << "set_convoys = 0\n";
   expected_one << "\n";
   expected_one << "set_politics = {\n";
   expected_one << "\truling_party = neutrality\n";
   expected_one << "\tlast_election = \"1836.1.1\"\n";
   expected_one << "election_frequency = 48\n";
   expected_one << "elections_allowed = no\n";
   expected_one << "}\n";
   expected_one << "\n";
   expected_one << "set_popularities = {\n";
   expected_one << "\tneutrality = 100\n";
   expected_one << "}\n";
   expected_one << "\n";
   expected_one << "add_ideas = {\n";
   expected_one << "\tlimited_conscription\n";
   expected_one << "\tcivilian_economy\n";
   expected_one << "\texport_focus\n";
   expected_one << "}\n";
   expected_one << "set_stability = 0.60\n";
   expected_one << "set_war_support = 0.60\n";
   expected_one << "\n";
   expected_one << "# Starting tech\n";
   expected_one << "if = {\n";
   expected_one << "\tlimit = { not = { has_dlc = \"Man the Guns\" } }\n";
   expected_one << "}\n";
   expected_one << "if = {\n";
   expected_one << "\tlimit = { has_dlc = \"Man the Guns\" }\n";
   expected_one << "}\n";
   expected_one << "if = {\n";
   expected_one << "\tlimit = { has_dlc = \"By Blood Alone\" }\n";
   expected_one << "}\n";
   expected_one << "if = {\n";
   expected_one << "\tlimit = { has_dlc = \"No Step Back\" }\n";
   expected_one << "}\n";
   EXPECT_EQ(country_file_stream.str(), expected_one.str());
}


TEST(Outhoi4CountriesOutcountryTests, CapitalCanBeSetInCountryHistoryFile)
{
   commonItems::TryCreateFolder("output");
   commonItems::TryCreateFolder("output/CapitalCanBeSetInCountryHistoryFile");
   commonItems::TryCreateFolder("output/CapitalCanBeSetInCountryHistoryFile/history");
   commonItems::TryCreateFolder("output/CapitalCanBeSetInCountryHistoryFile/history/countries");

   const hoi4::Country country({.tag = "TAG", .capital_state = 42});
   OutputCountryHistory("CapitalCanBeSetInCountryHistoryFile", country);

   ASSERT_TRUE(commonItems::DoesFileExist("output/CapitalCanBeSetInCountryHistoryFile/history/countries/TAG.txt"));
   std::ifstream country_file("output/CapitalCanBeSetInCountryHistoryFile/history/countries/TAG.txt");
   ASSERT_TRUE(country_file.is_open());
   std::stringstream country_file_stream;
   std::copy(std::istreambuf_iterator<char>(country_file),
       std::istreambuf_iterator<char>(),
       std::ostreambuf_iterator<char>(country_file_stream));
   country_file.close();

   EXPECT_THAT(country_file_stream.str(), testing::HasSubstr("capital = 42\n"));
}


TEST(Outhoi4CountriesOutcountryTests, EquipmentVariantsAreOutput)
{
   commonItems::TryCreateFolder("output");
   commonItems::TryCreateFolder("output/EquipmentVariantsAreOutput");
   commonItems::TryCreateFolder("output/EquipmentVariantsAreOutput/history");
   commonItems::TryCreateFolder("output/EquipmentVariantsAreOutput/history/countries");

   const std::vector<hoi4::EquipmentVariant> legacy_ship_variants = {
       hoi4::EquipmentVariant({}, {}, {{"name", "= legacy_ship: variant_one"}}),
       hoi4::EquipmentVariant({}, {"blocking_tech_missing"}, {{"name", "= legacy_ship: variant_two"}}),
   };
   const std::vector<hoi4::EquipmentVariant> ship_variants = {
       hoi4::EquipmentVariant({}, {}, {{"name", "= ship: variant_one"}}),
       hoi4::EquipmentVariant({}, {"blocking_tech_missing"}, {{"name", "= ship: variant_two"}}),
   };
   const std::vector<hoi4::EquipmentVariant> plane_variants = {
       hoi4::EquipmentVariant({}, {}, {{"name", "= plane: variant_one"}}),
       hoi4::EquipmentVariant({}, {"blocking_tech_missing"}, {{"name", "= plane: variant_two"}}),
   };
   const std::vector<hoi4::EquipmentVariant> tank_variants = {
       hoi4::EquipmentVariant({}, {}, {{"name", "= tank: variant_one"}}),
       hoi4::EquipmentVariant({}, {"blocking_tech_missing"}, {{"name", "= tank: variant_two"}}),
   };

   const hoi4::Country country({.tag = "TAG",
       .legacy_ship_variants = legacy_ship_variants,
       .ship_variants = ship_variants,
       .plane_variants = plane_variants,
       .tank_variants = tank_variants});
   OutputCountryHistory("EquipmentVariantsAreOutput", country);

   ASSERT_TRUE(commonItems::DoesFileExist("output/EquipmentVariantsAreOutput/history/countries/TAG.txt"));
   std::ifstream country_file("output/EquipmentVariantsAreOutput/history/countries/TAG.txt");
   ASSERT_TRUE(country_file.is_open());
   std::stringstream country_file_stream;
   std::copy(std::istreambuf_iterator<char>(country_file),
       std::istreambuf_iterator<char>(),
       std::ostreambuf_iterator<char>(country_file_stream));
   country_file.close();

   const std::string expected_output =
       "if = {\n"
       "\tlimit = { not = { has_dlc = \"Man the Guns\" } }\n"
       "\tcreate_equipment_variant = {\n"
       "\t\tname = legacy_ship: variant_one\n"
       "\t}\n"
       "\tcreate_equipment_variant = {\n"
       "\t\tname = legacy_ship: variant_two\n"
       "\t}\n"
       "}\n"
       "if = {\n"
       "\tlimit = { has_dlc = \"Man the Guns\" }\n"
       "\tcreate_equipment_variant = {\n"
       "\t\tname = ship: variant_one\n"
       "\t}\n"
       "\tcreate_equipment_variant = {\n"
       "\t\tname = ship: variant_two\n"
       "\t}\n"
       "}\n"
       "if = {\n"
       "\tlimit = { has_dlc = \"By Blood Alone\" }\n"
       "\tcreate_equipment_variant = {\n"
       "\t\tname = plane: variant_one\n"
       "\t}\n"
       "\tcreate_equipment_variant = {\n"
       "\t\tname = plane: variant_two\n"
       "\t}\n"
       "}\n"
       "if = {\n"
       "\tlimit = { has_dlc = \"No Step Back\" }\n"
       "\tcreate_equipment_variant = {\n"
       "\t\tname = tank: variant_one\n"
       "\t}\n"
       "\tcreate_equipment_variant = {\n"
       "\t\tname = tank: variant_two\n"
       "\t}\n"
       "}\n";

   EXPECT_THAT(country_file_stream.str(), testing::HasSubstr(expected_output));
}

}  // namespace out