#include "cppjson/json.hpp"

namespace cppjson{
    namespace{
        struct ParseResult
        {
            JsonValue value;
            std::string::const_iterator the_last_pos;
        };

        std::string parseKey(std::string::const_iterator it_key)
        {
            std::string key = "";
            while(*it_key!='"')    it_key--;  //  ensure the begin of it_key is "
            it_key--;
            while(*it_key!='"')    key = *it_key-- + key;   //  fill key
            return key;
        }
    
        ParseResult parseNumberVal(std::string::const_iterator current)
        {
            ParseResult result;
            // cout << "*current = " << *current << endl;
            std::string val = "";
            while(
                *current!='}' &&
                *current!=']' &&
                *current!=',' &&
                *current!='\n' &&
                *current!='\r' &&
                *current!=' '
            )
            {
                val += *current++;
                // cout << (int)*current << endl;
            }
    
            // cout << (val=="") << endl;
            // cout << "'" << val  << "'" << endl;
            if(
                val.find('.')!=std::string::npos ||
                val.find('e')!=std::string::npos ||
                val.find('E')!=std::string::npos
            ){
                result.value.type = JsonType::Float;
                result.value.float_val = std::stod(val);
            }
            else{
                result.value.type = JsonType::Int;
                result.value.int_val = std::stoi(val);
            }
            result.the_last_pos = current;
            return result;
        }
    
        ParseResult parseStrVal(std::string::const_iterator current)
        {
            ParseResult result;
    
            std::string val = "";
            current++; //  ensure current points to the next char of "(front)
            while(*current!='"')   val += *current++;
    
            result.value.str_val = val;
            result.the_last_pos = current;
            return result;
        }
    
        ParseResult parseBoolVal(std::string::const_iterator current)
        {
            ParseResult result;
    
            std::string val = "";
            while(
                *current!=',' &&
                *current!='}' &&
                *current!=']' &&
                *current!='\n' &&
                *current!='\r' &&
                *current!=' '
            )
                val += *current++;
            bool real_val = val=="true" ? true : false;
    
            result.value.bool_val = real_val;
            result.the_last_pos = current;
            return result;
        }
    
        ParseResult parseNullVal(std::string::const_iterator current)
        {
            ParseResult result;
    
            while(
                *current!=',' &&
                *current!='}' &&
                *current!=']' &&
                *current!='\n' &&
                *current!='\r' &&
                *current!=' '
            )
                current++;
            
            result.the_last_pos = current;
            return result;
        }
        
        ParseResult parseArray(std::string::const_iterator current);
        ParseResult parseObject(std::string::const_iterator current);
        ParseResult parseJsonValue(std::string::const_iterator current)
        {
            JsonValue val;
            ParseResult result_;
            switch(*current)
            {
                case '{':
                    result_ = parseObject(current);
                    val.type = JsonType::Object;
                    val.object_val = result_.value.object_val;
                    break;
                case '[':
                    result_ = parseArray(current);
                    val.type = JsonType::Array;
                    val.array_val = result_.value.array_val;
                    break;
                case '"':
                    result_ = parseStrVal(current);
                    val.type = JsonType::String;
                    val.str_val = result_.value.str_val;
                    break;
                case 't':
                case 'f':
                    result_ = parseBoolVal(current);
                    val.type = JsonType::Bool;
                    val.bool_val = result_.value.bool_val;
                    break;
                case 'n':
                    val.type = JsonType::Null;
                    current = parseNullVal(current).the_last_pos;
                    break;
                case ']':
                    result_.the_last_pos = current;
                    break;
                case '}':
                    result_.the_last_pos = current;
                    break;
                default:
                    result_ = parseNumberVal(current);
                    val.type = result_.value.type;
                    if(val.type == JsonType::Int)
                        val.int_val = result_.value.int_val;
                    else
                        val.float_val = result_.value.float_val;
                    break;
            }
            ParseResult result;
            result.the_last_pos = result_.the_last_pos;
            result.value = val;
            return result;
        }
        ParseResult parseArray(std::string::const_iterator current)
        {
            ParseResult result;
            Array array = {};
    
            // int count = 1;
            while(*current!=']')
            {
                // cout << "parsing the " << count++ << " val:";
                current++;
    
                // if(*current==',')  current++;
                // while(*current==' ')   current++; //  ensure that *current isn't space
                
                while(
                    *current==' ' ||
                    *current==',' ||
                    *current=='\r' ||
                    *current=='\n'
                )
                    current++;
                // if(*current==']')
                //     break;
    
                // cout << *current << endl;
                ParseResult result_ = parseJsonValue(current);
                JsonValue val = result_.value;
                current = result_.the_last_pos;
    
                if(!val.isEmpty())
                    array.push_back(val);
            }
    
            result.value.array_val = array;
            result.the_last_pos = current+1;
            return result;
        }
    
        ParseResult parseObject(std::string::const_iterator current)
        {
            ParseResult result;
            Object object = {};
    
            while(*current != '}')
            {
                current++;
                if(*current == ':')
                {
                    std::string::const_iterator it_key = current-1, it_val = current+1;
                    std::string key = "";
                    
                    key = parseKey(it_key);
                    // std::cout << "parsing " << key << std::endl;
                    
                    while(*it_val==' ')    it_val++;  //  ensure that *it_val isn't space
                    
                    ParseResult result_ = parseJsonValue(it_val);
                    JsonValue val = result_.value;
                    current = result_.the_last_pos;

                    if(!key.empty() && !val.isEmpty())
                        object.insert({key, val});
                }
            }
    
            result.value.object_val = object;
            result.the_last_pos = current+1;
            return result;
        }
    }

    Object parse(const std::string& path)
    {
        Object result = {};
        std::ifstream file(path);
        if(!file)
        {
            std::cout << "!!!------------Error-----------!!!\nFile: " << path << " doesn't exist!" << std::endl;
            return result;
        }
        const std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        if(!content.empty())
            result = parseObject(content.cbegin()).value.object_val;
        return result;
    }
}
