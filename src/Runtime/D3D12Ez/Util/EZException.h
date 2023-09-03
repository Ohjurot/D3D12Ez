#pragma once

#include <Util/Helper.h>

#include <fmt/format.h>
#include <spdlog/spdlog.h>

#include <string>
#include <atomic>
#include <exception>
#include <string_view>

#define D3EZ_EXCEPTION()               ::D3EZ::EZException(__FUNCTION__, __LINE__)
#define D3EZ_EXCEPTION_W(what)         ::D3EZ::EZException(__FUNCTION__, __LINE__, what)
#define D3EZ_EXCEPTION_WW(what, why)   ::D3EZ::EZException(__FUNCTION__, __LINE__, what, why)

#define D3EZ_CHECK(expr) D3EZ_MACRO_CODE_BLOCK( \
    if(!(expr)) \
    { \
        throw D3EZ_EXCEPTION_W("Macro check Failed!"); \
    } \
)
#define D3EZ_CHECK_D(expr, desc) D3EZ_MACRO_CODE_BLOCK( \
    if(!(expr)) \
    { \
        throw D3EZ_EXCEPTION_W(desc); \
    } \
)
#define D3EZ_CHECK_F(expr, fstr, ...) D3EZ_MACRO_CODE_BLOCK( \
    if(!(expr)) \
    { \
        throw D3EZ_EXCEPTION_W(fmt::format(fstr, __VA_ARGS__)); \
    } \
)

namespace D3EZ
{
    class EZException : public std::exception
    {
        public:
            EZException() = default;
            EZException(std::string_view function, int line);
            EZException(std::string_view function, int line, std::string_view what);
            EZException(std::string_view function, int line, std::string_view what, std::string_view why);
            EZException(const EZException&) = default;
            EZException(EZException&&) noexcept = default;

            EZException& operator=(const EZException&) = default;
            EZException& operator=(EZException&&) noexcept = default;

            char const* what() const override;

        protected:
            void AddDetail_Location(std::string_view function, int line);
            void AddDetail_Description(std::string_view desc);
            void AddDetail_Reason(std::string_view desc);
            void AppendMessage(std::string_view msg);

        private:
            std::string m_msg;
            size_t m_eid = s_eid_count++;

            static std::atomic_size_t s_eid_count;
    };
}
