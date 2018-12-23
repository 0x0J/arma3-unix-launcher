#ifndef STRING_UTILS_HPP_
#define STRING_UTILS_HPP_

#include <filesystem>
#include <type_traits>
#include <string>
#include <string_view>
#include <vector>

namespace StringUtils
{
    std::string_view RemoveElementsFromPath(const std::string &text, bool remove_slash = true, int count = 1);
    std::string Replace(std::string text, const std::string &from, const std::string &to);

    bool EndsWith(const std::string &text, const std::string &find);
    bool StartsWith(const std::string &text, const std::string &find);

    std::vector<std::string_view> Split(const std::string &text_to_split, const std::string &delimiters);

    std::string Lowercase(std::string text);

    std::filesystem::path ToWindowsPath(std::filesystem::path const &path);

    template<typename ret_type = std::string_view, typename argument = std::string>
    ret_type TrimLeft(const argument &text, std::string const &to_trim = " \n\r\t")
    {
        size_t startpos = text.find_first_not_of(to_trim);
        if constexpr(std::is_same_v<ret_type, std::string_view> &&std::is_same_v<argument, std::string>)
            return (startpos == std::string::npos) ? std::string_view() : std::string_view(text.c_str() + startpos, text.size() - startpos);
        else //std::string ret_type
            return (startpos == std::string::npos) ? "" : text.substr(startpos);
    }

    template<typename ret_type = std::string_view, typename argument = std::string>
    ret_type TrimRight(const argument &text, std::string const &to_trim = " \n\r\t")
    {
        size_t endpos = text.find_last_not_of(to_trim);
        if constexpr(std::is_same_v<ret_type, std::string_view> &&std::is_same_v<argument, std::string>)
            return (endpos == std::string::npos) ? std::string_view() : std::string_view(text.c_str(), endpos + 1);
        else //std::string ret_type
            return (endpos == std::string::npos) ? "" : text.substr(0, endpos + 1);
    }

    template<typename ret_type = std::string_view, typename argument = std::string>
    ret_type Trim(const argument &text, std::string const &to_trim = " \n\r\t")
    {
        return TrimLeft<ret_type, ret_type>(TrimRight<ret_type, argument>(text, to_trim));
    }
}

#endif
