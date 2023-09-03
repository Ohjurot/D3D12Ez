#pragma once

#include <Util/Win.h>
#include <Util/Helper.h>
#include <Util/EZException.h>

#define D3EZ_HR_EXCEPTION(ec)               ::D3EZ::HRException(__FUNCTION__, __LINE__, ec)
#define D3EZ_HR_EXCEPTION_W(ec, what)       ::D3EZ::HRException(__FUNCTION__, __LINE__, what, ec)

#define D3EZ_CHECK_HR(expr) D3EZ_MACRO_CODE_BLOCK( \
    HRESULT __d3ez_check_hr = (expr); \
    if(FAILED(__d3ez_check_hr)) \
    { \
        throw D3EZ_HR_EXCEPTION(__d3ez_check_hr); \
    } \
)

#define D3EZ_CHECK_HR_D(expr, desc) D3EZ_MACRO_CODE_BLOCK( \
    HRESULT __d3ez_check_hr = (expr); \
    if(FAILED(__d3ez_check_hr)) \
    { \
        throw D3EZ_HR_EXCEPTION(__d3ez_check_hr, desc); \
    } \
)

#define D3EZ_CHECK_HR_F(expr, fstr, ...) D3EZ_MACRO_CODE_BLOCK( \
    HRESULT __d3ez_check_hr = (expr); \
    if(FAILED(__d3ez_check_hr)) \
    { \
        throw D3EZ_HR_EXCEPTION(__d3ez_check_hr, fmt::format(fstr, __VA_ARGS__)); \
    } \
)

namespace D3EZ
{
    class HRException : public EZException
    {
        public:
            HRException() = delete;
            HRException(std::string_view function, int line, HRESULT why);
            HRException(std::string_view function, int line, std::string_view what, HRESULT why);

        protected:
            std::string WinErrorToString(HRESULT ec);
    };
}
