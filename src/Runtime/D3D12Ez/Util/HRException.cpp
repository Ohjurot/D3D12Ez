#include "HRException.h"

D3EZ::HRException::HRException(std::string_view function, int line, std::string_view what, HRESULT why)
{
    AddDetail_Description("Exception occurred");
    AddDetail_Description("WinApi call failed / HRESULT was successfully");
    AddDetail_Description(what);
    AddDetail_Location(function, line);
    AddDetail_Reason(WinErrorToString(why));
}

D3EZ::HRException::HRException(std::string_view function, int line, HRESULT why)
{
    AddDetail_Description("Exception occurred");
    AddDetail_Description("WinApi call failed / HRESULT was successfully");
    AddDetail_Location(function, line);
    AddDetail_Reason(WinErrorToString(why));
}

std::string D3EZ::HRException::WinErrorToString(HRESULT ec)
{
    std::string errorStringForCode = "Unknown";
    char* winmsg;
    if (
        FormatMessageA(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_MAX_WIDTH_MASK,
            nullptr, 
            ec, 
            0, 
            (LPSTR)&winmsg,
            0,
            nullptr
        ) != 0)
    {
        errorStringForCode = winmsg;
        LocalFree(winmsg);
    }

    return fmt::format("{} (0x{:x})", errorStringForCode, (uint32_t)ec);
}
