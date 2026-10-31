#include "cppjson/json.hpp"

namespace cppjson{
    bool JsonValue::isEmpty() const
    {
        return this->type == JsonType::Empty;
    }
    JsonValue::operator int() const
    {
        switch (this->type)
        {
        case JsonType::Int:
            return this->int_val;
        case JsonType::Float:
            return static_cast<int>(this->float_val);
        case JsonType::Bool:
            return this->bool_val ? 1 : 0;
        case JsonType::Empty:
            throw std::runtime_error("JsonValue is Empty!");
        default:
            throw std::runtime_error("JsonValue is not int or something can be transferred to int");
        }
    }
    JsonValue::operator double() const
    {
        switch (this->type)
        {
        case JsonType::Float:
            return this->float_val;
        case JsonType::Int:
            return static_cast<double>(this->int_val);
        case JsonType::Bool:
            return this->bool_val ? 1.0 : 0.0;
        case JsonType::Empty:
            throw std::runtime_error("JsonValue is Empty!");
        default:
            throw std::runtime_error("JsonValue is not float or something can be transferred to float");
        }
    }
    JsonValue::operator bool() const
    {
        switch (this->type)
        {
        case JsonType::Bool:
            return this->bool_val;
        case JsonType::Int:
            return static_cast<bool>(this->int_val);
        case JsonType::Float:
            return static_cast<bool>(this->float_val);
        case JsonType::String:
            return this->str_val!="" ? 1 : 0;
        case JsonType::Null:
            return 0;
        default:
            throw std::runtime_error("JsonValue is not bool or something can be transferred to bool");
        }
    }
    JsonValue::operator std::string() const
    {
        switch (this->type)
        {
        case JsonType::String:
            return this->str_val;
        case JsonType::Int:
            return std::to_string(this->int_val);
        case JsonType::Float:
            return std::to_string(this->float_val);
        case JsonType::Bool:
            return this->bool_val ? "true" : "false";
        case JsonType::Null:
            return "null";
        case JsonType::Array:
            return printArray(this->array_val);
        case JsonType::Object:
            return printObject(this->object_val);
        case JsonType::Empty:
            throw std::runtime_error("JsonValue is Empty!");
        default:
            throw std::runtime_error("JsonValue is not string or something can be transferred to string");
        }
    }
    JsonValue::operator Array() const
    {
        if(this->type!=JsonType::Array)
            throw std::runtime_error("JsonValue is not Array!");
        return this->array_val;
    }
    JsonValue::operator Object() const
    {
        if(this->type!=JsonType::Object)
            throw std::runtime_error("JsonValue is not Object");
        return this->object_val;
    }
    int& JsonValue::to_int()
    {
        return this->int_val;
    }
    double& JsonValue::to_double()
    {
        return this->float_val;
    }
    std::string& JsonValue::to_string()
    {
        return this->str_val;
    }
    bool& JsonValue::to_bool()
    {
        return this->bool_val;
    }
    Array& JsonValue::to_array()
    {
        return this->array_val;
    }
    Object& JsonValue::to_object()
    {
        return this->object_val;
    }
    JsonValue& JsonValue::operator[](const std::string& key)
    {
        return this->object_val[key];
    }
    const JsonValue& JsonValue::operator[](const std::string& key) const
    {
        return this->object_val[key];
    }
    JsonValue& JsonValue::operator[](const std::size_t& pos)
    {
        return this->array_val[pos];
    }
    const JsonValue& JsonValue::operator[](const std::size_t& pos) const
    {
        return this->array_val[pos];
    }
}