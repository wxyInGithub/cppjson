#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <variant>

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
        const_iterator begin() const;
        const_iterator end() const;
        const_iterator cbegin() const;
        const_iterator cend() const;
        std::size_t size() const;
        void push_back(const JsonValue& val);
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
        const_iterator begin() const;
        const_iterator end() const;
        const_iterator cbegin() const;
        const_iterator cend() const;
        std::size_t size() const;
        void insert(std::pair<std::string, JsonValue> kv);
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

        bool isEmpty() const;
        operator int() const;
        operator double() const;
        operator bool() const;
        operator std::string() const;
        operator Array() const;
        operator Object() const;
        int& to_int();
        double& to_double();
        std::string& to_string();
        bool& to_bool();
        Array& to_array();
        Object& to_object();
        JsonValue& operator[](const std::string& key);
        const JsonValue& operator[](const std::string& key) const;
        JsonValue& operator[](const std::size_t& pos);
        const JsonValue& operator[](const std::size_t& pos) const;
    };


    //  parser.cpp
    Object parse(const std::string& path);
    
    //  print.cpp
    std::string printArray(const Array& array, int layer=1);
    std::string printObject(const Object& json, int layer=1);
    std::ostream& operator<<(std::ostream& os, const Object& object);
    std::ostream& operator<<(std::ostream& os, const Array& array);
    std::ostream& operator<<(std::ostream& os, const JsonValue& val);
}