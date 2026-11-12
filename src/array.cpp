#include "cppjson/json.hpp"

namespace cppjson{
    JsonValue& Array::operator[](const std::size_t& pos)
    {
        return this->content[pos];
    }
    const JsonValue& Array::operator[](const std::size_t& pos) const
    {
        return this->content[pos];
    }
    Array::iterator Array::begin()
    {
        return this->content.begin();
    }
    Array::iterator Array::end()
    {
        return this->content.end();
    }
    Array::const_iterator Array::begin() const
    {
        return this->content.begin();
    }
    Array::const_iterator Array::end() const
    {
        return this->content.end();
    }
    Array::const_iterator Array::cbegin() const
    {
        return this->content.cbegin();
    }
    Array::const_iterator Array::cend() const
    {
        return this->content.cend();
    }
    std::size_t Array::size() const
    {
        return this->content.size();
    }
    void Array::push_back(const JsonValue& val)
    {
        this->content.push_back(val);
    }
    void Array::erase(const size_t& pos)
    {
        this->content.erase(this->content.begin()+pos);
    }
    void Array::pop()
    {
        this->content.pop_back();
    }
    void Array::clear()
    {
        this->content.clear();
    }
    bool Array::is_empty() const
    {
        return this->content.empty();
    }
    const std::string Array::to_string() const
    {
        return printArray(*this);
    }
}