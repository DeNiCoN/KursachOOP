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
            return type_to_obj_.at(name)();
        }

        TypePtr operator()(const nlohmann::json& json) const
        {
            //Get new instance of vechicle
            auto vec_ptr = (*this)(json.at("type").get<std::string>());
            vec_ptr->Parse(json);
            return vec_ptr;
        }
    protected:
        static const std::unordered_map<std::string,
                                        std::function<TypePtr()>
                                        > type_to_obj_;
    };
}
