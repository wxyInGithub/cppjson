#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <any>

namespace cppjson{
    enum class JsonType{
        Empty, 
        Int, 
        String, 
        Float, 
        Bool, 
        Null, 
        Array, 
        Object
    };
    inline const std::map<JsonType, std::string> JSONTYPE_HASH_ = {
        {JsonType::Empty, "Empty"}, 
        {JsonType::Int, "Int"}, 
        {JsonType::String, "String"}, 
        {JsonType::Float, "Float"}, 
        {JsonType::Bool, "Bool"}, 
        {JsonType::Null, "Null"}, 
        {JsonType::Array, "Array"}, 
        {JsonType::Object, "Object"}
    };

    class JsonValue;    //  declare JsonValue ahead

    class Array{
    private:
        std::vector<JsonValue> content;
    public:
        using iterator = std::vector<JsonValue>::iterator;
        using const_iterator = std::vector<JsonValue>::const_iterator;

        JsonValue& operator[](const std::size_t& pos);
        const JsonValue& operator[](const std::size_t& pos) const;
        iterator begin();
        iterator end();
        const_iterator begin()  const;
        const_iterator end()    const;
        const_iterator cbegin() const;
        const_iterator cend()   const;
        std::size_t size()      const;
        void push_back(const JsonValue& val);
        void erase(const size_t& pos);
        void pop();
        void clear();
        bool is_empty() const;
        const std::string to_string() const;
    };

    class Object{
        private:
        std::map<std::string, JsonValue> content;
        public:
        using iterator = std::map<std::string, JsonValue>::iterator;
        using const_iterator = std::map<std::string, JsonValue>::const_iterator;
        
        JsonValue& operator[](const std::string& key);
        const JsonValue& operator[](const std::string& key) const;
        iterator begin();
        iterator end();
        const_iterator begin()  const;
        const_iterator end()    const;
        const_iterator cbegin() const;
        const_iterator cend()   const;
        std::size_t size()      const;
        void insert(const std::string& key, const JsonValue& val);
        void erase(const std::string& key);
        void clear();
        bool is_empty() const;
        const std::string to_string(bool strict_json=false) const;
    };
    
    class JsonValue{
    public:
        JsonType    type=JsonType::Empty;
        int         int_val=0;
        double      float_val=0.0;
        std::string str_val="";
        bool        bool_val=false;
        Array       array_val={};
        Object      object_val={};

        JsonValue()=default;
        JsonValue(int&          int_val);
        JsonValue(double&       float_val);
        JsonValue(std::string&  str_val);
        JsonValue(const char*   str_val);
        JsonValue(bool&         bool_val);
        JsonValue(Array&        array_val);
        JsonValue(Object&       object_val);
        bool isEmpty()          const;
        operator int()          const;
        operator double()       const;
        operator bool()         const;
        operator std::string()  const;
        operator Array()        const;
        operator Object()       const;
        int to_int()            const;
        double to_double()      const;
        std::string to_string(bool strict_json=false) const;
        bool to_bool()          const;
        Array to_array()        const;
        Object to_object()      const;
        JsonValue& operator[](const std::string& key);
        JsonValue& operator[](const char* key);
        const JsonValue& operator[](const std::string& key) const;
        const JsonValue& operator[](const char* key) const;
        JsonValue& operator[](const std::size_t& pos);
        const JsonValue& operator[](const std::size_t& pos) const;
    };


    //  parser.cpp
    Object parse(const std::string& path);

    //  writer.cpp
    bool dump(const std::string& path, const Object& object);
    bool dump(const char* path, const Object& object);
    bool dump(const std::string& path, const JsonValue& value);
    bool dump(const char* path, const JsonValue& value);
    bool dump_str(const std::string& path, const std::string& content);
    
    //  print.cpp
    std::string printArray(const Array& array, int layer=1);
    std::string printObject(const Object& json, int layer=1);
    std::string stringify(const Object& json, int layer=1);
    std::ostream& operator<<(std::ostream& os, const Object& object);
    std::ostream& operator<<(std::ostream& os, const Array& array);
    std::ostream& operator<<(std::ostream& os, const JsonValue& val);
    std::ostream& operator<<(std::ostream& os, const JsonType& type);
}