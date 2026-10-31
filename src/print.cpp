#include "cppjson/json.hpp"

namespace cppjson{
    namespace{
        struct ToStringResult
        {
            std::string val_tostring="";
            bool has_inner_array=false;
        };
        
        const ToStringResult JsonValueToString(const JsonValue& val, int layer=1)
        {
            ToStringResult result;
            std::ostringstream val_tostring;
            switch(val.type)
            {
                case JsonType::Empty:
                    throw std::runtime_error("Trying to get an empty JsonValue!");
                case JsonType::Object:
                    // if(layer!=1)
                    //     val_tostring << '\n' << std::string(layer, '\t');
                    val_tostring << printObject(val.object_val, layer);
                    break;
                case JsonType::Array:
                    result.has_inner_array = true;
                    // if(layer!=1)
                    //     val_tostring << '\n' << std::string(layer, '\t');
                    val_tostring << printArray(val.array_val, layer+1);
                    break;
                case JsonType::String:
                    val_tostring << '"' << val.str_val << "\"";
                    break;
                case JsonType::Bool:
                    val_tostring << (val.bool_val ? "true" : "false");
                    break;
                case JsonType::Null:
                    val_tostring << "null";
                    break;
                case JsonType::Int:
                    val_tostring << val.int_val;
                    break;
                case JsonType::Float:
                    val_tostring << val.float_val;
                    break;
                default:
                    break;
            }
            result.val_tostring = val_tostring.str();
            return result;
        }
    }

    std::string printArray(const Array& array, int layer)
    {
        std::ostringstream result;
        result << "[ ";
        size_t final_pos = array.size()-1;
        size_t current_pos = 0;
        bool has_inner_array_ = false;
        for(const auto& item : array)
        {
            const ToStringResult tostring_result = JsonValueToString(item, layer);
            has_inner_array_ = tostring_result.has_inner_array;
            result << tostring_result.val_tostring;
            result << (current_pos++ < final_pos ? ", " : " ");
        }
        
        result << (has_inner_array_ ? "\n"+std::string(layer-1, '\t')+"]" : "]");
        return result.str();
    }

    std::string printObject(const Object& json, int layer)
    {
        std::ostringstream result;
        result << "{\n";
        size_t final_pos = json.size()-1;
        size_t current_pos = 0;
        for(const auto& item : json)
        {
            result << std::string(layer, '\t') << item.first << ": ";
            const ToStringResult tostring_result = JsonValueToString(item.second, layer+1);
            result << tostring_result.val_tostring;
            result << (current_pos++ < final_pos ? ", \n" : "\n");
        }
        result << std::string(layer-1, '\t') << "}";

        return result.str();
    }

    std::ostream& operator<<(std::ostream& os, const Object& object)
    {
        os << printObject(object);
        return os;
    }
    std::ostream& operator<<(std::ostream& os, const Array& array)
    {
        os << printArray(array);
        return os;
    }
    std::ostream& operator<<(std::ostream& os, const JsonValue& val)
    {
        os << JsonValueToString(val).val_tostring;
        return os;
    }
}