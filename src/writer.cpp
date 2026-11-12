#include "cppjson/json.hpp"

namespace cppjson{
    bool dump(const std::string& path, const Object& object)
    {
        std::ofstream file(path);
        if(file.is_open()){
            file << stringify(object);
            return true;
        } else{
            std::string error = "FROM writer.cpp bool dump(const std::string& path, const Object& object):\nFailed to open file " + path;
            throw std::runtime_error(error);
        }
    }
    bool dump(const char* path, const Object& object)
    {
        std::ofstream file(path);
        if(file.is_open()){
            file << stringify(object);
            return true;
        } else{
            std::string error = "FROM writer.cpp bool dump(const char* path, const Object& object)\nFailed to open file " + std::string(path);
            throw std::runtime_error(error);
        }
    }

    bool dump(const std::string& path, const JsonValue& value)
    {
        std::ofstream file(path);
        if(file.is_open()){
            switch (value.type)
            {
            case JsonType::Object:
                file << stringify(value.object_val);
                break;
            case JsonType::Array:
                file << value.to_string();
                break;
            default:
                std::string error = "FROM writer.cpp bool dump(const std::string& path, const JsonValue& value)\n" + JSONTYPE_HASH_.at(value.type) + " cannot serve as json's first layer. Object or Array is expected.";
                throw std::runtime_error(error);
            }
        } else{
            std::string error = "FROM writer.cpp bool dump(const std::string& path, const JsonValue& value)\nFailed to open file " + path;
            throw std::runtime_error(error);
        }
        return true;
    }
    bool dump(const char* path, const JsonValue& value)
    {
        std::ofstream file(path);
        if(file.is_open()){
            switch (value.type)
            {
            case JsonType::Object:
                file << stringify(value.object_val);
                break;
            case JsonType::Array:
                file << value.to_string();
                break;
            default:
                std::string error = "FROM writer.cpp bool dump(const char* path, const JsonValue& value)\n" + JSONTYPE_HASH_.at(value.type) + " cannot serve as json's first layer. Object or Array is expected.";
                throw std::runtime_error(error);
            }
        } else{
            std::string error = "FROM writer.cpp bool dump(const char* path, const JsonValue& value)\nFailed to open file " + std::string(path);
            throw std::runtime_error(error);
        }
        return true;
    }
}