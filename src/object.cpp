#include "cppjson/json.hpp"

namespace cppjson{
    JsonValue& Object::operator[](const std::string& key)
    {
        return this->content[key];
    }
    const JsonValue& Object::operator[](const std::string& key) const
    {
        return this->content.at(key);
    }
    Object::iterator Object::begin()
    {
        return this->content.begin();
    }
    Object::iterator Object::end()
    {
        return this->content.end();
    }
    Object::const_iterator Object::begin() const
    {
        return this->content.begin();
    }
    Object::const_iterator Object::end() const
    {
        return this->content.end();
    }
    Object::const_iterator Object::cbegin() const
    {
        return this->content.cbegin();
    }
    Object::const_iterator Object::cend() const
    {
        return this->content.cend();
    }
    std::size_t Object::size() const
    {
        return this->content.size();
    }
    void Object::insert(std::pair<std::string, JsonValue> kv)
    {
        this->content.insert(kv);
    }
}