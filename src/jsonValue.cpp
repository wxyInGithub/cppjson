#include "cppjson/json.hpp"

namespace cppjson{
    JsonValue::JsonValue(int& int_val)
    {
        this->type = JsonType::Int;
        this->int_val = int_val;
    }
    JsonValue::JsonValue(double& float_val)
    {
        this->type = JsonType::Float;
        this->float_val = float_val;
    }
    JsonValue::JsonValue(std::string& str_val)
    {
        this->type = JsonType::String;
        this->str_val = str_val;
    }
    JsonValue::JsonValue(const char* str_val)
    {

        this->type = JsonType::String;
        this->str_val = std::string(str_val);
    }
    JsonValue::JsonValue(bool& bool_val)
    {
        this->type = JsonType::Bool;
        this->bool_val = bool_val;
    }
    JsonValue::JsonValue(Array& array_val)
    {
        this->type = JsonType::Array;
        this->array_val = array_val;
    }
    JsonValue::JsonValue(Object& object_val)
    {
        this->type = JsonType::Object;
        this->object_val = object_val;
    }
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
            throw std::runtime_error("FROM jsonValue.cpp JsonValue::operator int() const\nJsonValue is Empty!");
        default:
            throw std::runtime_error("FROM jsonValue.cpp JsonValue::operator int() const\nJsonValue is not int or something can be transferred to int");
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
            throw std::runtime_error("FROM jsonValue.cpp JsonValue::operator double() const\nJsonValue is Empty!");
        default:
            throw std::runtime_error("FROM jsonValue.cpp JsonValue::operator double() const\nJsonValue is not float or something can be transferred to float");
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
            throw std::runtime_error("FROM jsonValue.cpp JsonValue::operator bool() const\nJsonValue is not bool or something can be transferred to bool");
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
            throw std::runtime_error("FROM jsonValue.cpp JsonValue::operator string() const\nJsonValue is Empty!");
        default:
            throw std::runtime_error("FROM jsonValue.cpp JsonValue::operator string() const\nJsonValue is not string or something can be transferred to string");
        }
    }
    JsonValue::operator Array() const
    {
        if(this->type!=JsonType::Array)
            throw std::runtime_error("FROM jsonValue.cpp JsonValue::operator Array() const\nJsonValue is not Array!");
        return this->array_val;
    }
    JsonValue::operator Object() const
    {
        if(this->type!=JsonType::Object)
            throw std::runtime_error("FROM jsonValue.cpp JsonValue::operator Object() const\nJsonValue is not Object");
        return this->object_val;
    }
    int JsonValue::to_int() const
    {
        switch (this->type)
        {
        case JsonType::Int:     return this->int_val;
        case JsonType::Float:   return this->float_val;
        case JsonType::Bool:    return this->bool_val;
        default:
            std::string error = "FROM jsonValue.cpp int JsonValue::to_int() const\nTrying to shift a " + JSONTYPE_HASH_.at(this->type) + " value to an Int value";  
            throw std::runtime_error(error);
        }
    }
    double JsonValue::to_double() const
    {
        switch (this->type)
        {
        case JsonType::Int:     return this->int_val;
        case JsonType::Float:   return this->float_val;
        case JsonType::Bool:    return this->bool_val;
        default:
            std::string error = "FROM jsonValue.cpp double JsonValue::to_double() const\nTrying to shift a " + JSONTYPE_HASH_.at(this->type) + " value to an Int value";  
            throw std::runtime_error(error);
        }
    }
    std::string JsonValue::to_string(bool strict_json) const
    {
        switch (this->type)
        {
        case JsonType::String:  return this->str_val;
        case JsonType::Int:     return std::to_string(this->int_val);
        case JsonType::Float:   return std::to_string(this->float_val);
        case JsonType::Bool:    return this->bool_val ? "true" : "false";
        case JsonType::Null:    return "null";
        case JsonType::Array:   return printArray(this->array_val);
        case JsonType::Object:  return (strict_json ? stringify(this->object_val) : printObject(this->object_val));
        case JsonType::Empty:   throw std::runtime_error("FROM jsonValue.cpp std::string JsonValue::to_string() const\nJsonValue is Empty!");
        default:                throw std::runtime_error("FROM jsonValue.cpp std::string JsonValue::to_string() const\nJsonValue is not string or something can be transformed to string");
        }
    }
    bool JsonValue::to_bool() const
    {
        switch (this->type)
        {
        case JsonType::Bool:    return this->bool_val;
        case JsonType::Int:     return this->int_val;
        case JsonType::Float:   return this->float_val;
        case JsonType::String:  return this->str_val.empty() ? false : true;
        case JsonType::Null:    return false;
        case JsonType::Array:   return this->array_val.is_empty() ? false : true;
        case JsonType::Object:  return this->object_val.is_empty() ? false : true;
        case JsonType::Empty:   return false;
        default:                throw std::runtime_error("FROM jsonValue.cpp bool JsonValue::to_bool() const\nJsonValue is not string or something can be transformed to bool");
        }
    }
    Array JsonValue::to_array() const
    {
        if(this->type == JsonType::Array)
            return this->array_val;
        else
            throw std::runtime_error("FROM jsonValue.cpp Array JsonValue::to_array() const\nJsonValue is not string or something can be transformed to Array");
    }
    Object JsonValue::to_object() const
    {
        if(this->type == JsonType::Object)
            return this->object_val;
        else
            throw std::runtime_error("FROM jsonValue.cpp Object JsonValue::to_object() const\nJsonValue is not string or something can be transformed to Object");
    }
    JsonValue& JsonValue::operator[](const std::string& key)
    {
        return this->object_val[key];
    }
    JsonValue& JsonValue::operator[](const char* key)
    {
        return this->object_val[key];
    }
    const JsonValue& JsonValue::operator[](const std::string& key) const
    {
        return this->object_val[key];
    }
    const JsonValue& JsonValue::operator[](const char* key) const
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