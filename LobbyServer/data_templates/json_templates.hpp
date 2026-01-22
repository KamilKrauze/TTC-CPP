#ifndef JSON_TEMPLATES_HPP
#define JSON_TEMPLATES_HPP

#include <nlohmann/json.hpp>

namespace tmplts
{
    struct CharacterAttribs
    {
        CharacterAttribs()
        {
            strength = 0;
            dexterity = 0;
            constitution = 0;
            intelligence = 0;
            wisdom = 0;
            charisma = 0;
        }
        CharacterAttribs(
            int _strength, int _dexterity, int _constitution, 
            int _intelligence, int _wisdom, int _charisma) :
            strength(_strength), dexterity(_dexterity), constitution(_constitution), 
            intelligence(_intelligence), wisdom(_wisdom), charisma(_charisma) {}

        int strength, dexterity, constitution, intelligence, wisdom, charisma;
    };

    namespace json
    {
        static nlohmann::ordered_json make_character_attribs(const CharacterAttribs& attribs)
        {
            nlohmann::ordered_json attribs_json;
            attribs_json["strength"] = attribs.strength;
            attribs_json["dexterity"] = attribs.dexterity;
            attribs_json["constitution"] = attribs.constitution;
            attribs_json["intelligence"] = attribs.intelligence;
            attribs_json["wisdom"] = attribs.wisdom;
            attribs_json["charisma"] = attribs.charisma;
            
            return attribs_json;
        }
    }
}

#endif // !JSON_TEMPLATES_HPP