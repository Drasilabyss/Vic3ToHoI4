#ifndef SRC_VIC3WORLD_COUNTRIES_VIC3COUNTRY_H
#define SRC_VIC3WORLD_COUNTRIES_VIC3COUNTRY_H



#include <string>

#include "external/commonItems/Color.h"



namespace vic3
{

struct CountryOptions
{
   std::string tag;
   commonItems::Color color;
   std::optional<int> capital_state;
};


class Country
{
  public:
   Country() = default;
   explicit Country(CountryOptions options):
       tag_(std::move(options.tag)),
       color_(std::move(options.color)),
       capital_state_(options.capital_state)
   {
   }

   [[nodiscard]] const std::string& GetTag() const { return tag_; }
   [[nodiscard]] const commonItems::Color& GetColor() const { return color_; }
   [[nodiscard]] const std::optional<int>& GetCapitalState() const { return capital_state_; }

   bool operator==(const Country&) const = default;

  private:
   std::string tag_;
   commonItems::Color color_;
   std::optional<int> capital_state_;
};

}  // namespace vic3



#endif  // SRC_VIC3WORLD_COUNTRIES_VIC3COUNTRY_H