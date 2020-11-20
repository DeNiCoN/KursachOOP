#pragma once
#include <nlohmann/json.hpp>
#include <unordered_map>

#define TYPE_TO_OBJ_NODE(class_name)                                \
    {#class_name, [](){ return std::make_unique<class_name>(); }}

namespace transport
{
    template <typename T>
    class FactoryBase
    {
    public:
        using TypePtr = std::unique_ptr<T>;
        TypePtr operator()(const std::string& name) const
        {
            return s_typeToObj.at(name)();
        }

        TypePtr operator()(const nlohmann::json& json) const
        {
            //Get new instance of vechicle
            auto vecPtr = (*this)(json.at("type").get<std::string>());
            vecPtr->parse(json);
            return vecPtr;
        }
    protected:
        static const std::unordered_map<std::string,
                                        std::function<TypePtr()>
                                        > s_typeToObj;
    };
}
