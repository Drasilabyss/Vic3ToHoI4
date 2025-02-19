#ifndef SRC_HOI4WORLD_COUNTRIES_HOI4COUNTRY_H
#define SRC_HOI4WORLD_COUNTRIES_HOI4COUNTRY_H



#include <string>

#include "external/commonItems/Color.h"
#include "src/hoi4_world/military/equipment_variant.h"
#include "src/hoi4_world/technology/technologies.h"
#include "src/mappers/country/country_mapper.h"



namespace hoi4
{

struct CountryOptions
{
   std::string tag;
   commonItems::Color color;
   std::optional<int> capital_state;
   Technologies technologies;
   std::vector<EquipmentVariant> legacy_ship_variants;
   std::vector<EquipmentVariant> ship_variants;
   std::vector<EquipmentVariant> plane_variants;
   std::vector<EquipmentVariant> tank_variants;
};


class Country
{
  public:
   explicit Country(CountryOptions country_options):
       tag_(std::move(country_options.tag)),
       color_(country_options.color),
       capital_state_(country_options.capital_state),
       technologies_(std::move(country_options.technologies)),
       legacy_ship_variants_(std::move(country_options.legacy_ship_variants)),
       ship_variants_(std::move(country_options.ship_variants)),
       plane_variants_(std::move(country_options.plane_variants)),
       tank_variants_(std::move(country_options.tank_variants))
   {
   }

   [[nodiscard]] const std::string& GetTag() const { return tag_; }
   [[nodiscard]] const commonItems::Color& GetColor() const { return color_; }
   [[nodiscard]] const std::optional<int>& GetCapitalState() const { return capital_state_; }
   [[nodiscard]] const Technologies& GetTechnologies() const { return technologies_; }
   [[nodiscard]] const std::vector<EquipmentVariant>& GetLegacyShipVariants() const { return legacy_ship_variants_; }
   [[nodiscard]] const std::vector<EquipmentVariant>& GetShipVariants() const { return ship_variants_; }
   [[nodiscard]] const std::vector<EquipmentVariant>& GetPlaneVariants() const { return plane_variants_; }
   [[nodiscard]] const std::vector<EquipmentVariant>& GetTankVariants() const { return tank_variants_; }

   std::partial_ordering operator<=>(const Country&) const = default;

  private:
   std::string tag_;
   commonItems::Color color_;
   std::optional<int> capital_state_;
   Technologies technologies_;
   std::vector<EquipmentVariant> legacy_ship_variants_;
   std::vector<EquipmentVariant> ship_variants_;
   std::vector<EquipmentVariant> plane_variants_;
   std::vector<EquipmentVariant> tank_variants_;
};

}  // namespace hoi4



#endif  // SRC_HOI4WORLD_COUNTRIES_HOI4COUNTRY_H