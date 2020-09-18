#include "vechicle_factory.hpp"

#define TYPE_TO_OBJ_NODE(class_name)                                    \
        {#class_name, [](){ return std::make_unique<class_name>(); }}

namespace Transport
{
    const std::unordered_map<std::string,
                             std::function<std::unique_ptr<Vechicle>()>
                             > VechicleFactory::s_typeToObj
    {
        TYPE_TO_OBJ_NODE(TestVechicle)
    };

    VechiclePtr VechicleFactory::operator()(const std::string& name) const
    {
        return s_typeToObj.at(name)();
    }

    VechiclePtr VechicleFactory::operator()(const nlohmann::json& json) const
    {
        //Get new instance of vechicle
        auto vecPtr = (*this)(json.at("type").get<std::string>());
        vecPtr->Parse(json);
        return vecPtr;
    }

}
