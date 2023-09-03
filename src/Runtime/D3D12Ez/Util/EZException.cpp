#include "EZException.h"

std::atomic_size_t D3EZ::EZException::s_eid_count;

D3EZ::EZException::EZException(std::string_view function, int line)
{
    AddDetail_Description("Exception occurred");
    AddDetail_Location(function, line);
}

D3EZ::EZException::EZException(std::string_view function, int line, std::string_view what)
{
    AddDetail_Description("Exception occurred");
    AddDetail_Description(what);
    AddDetail_Location(function, line);
}

D3EZ::EZException::EZException(std::string_view function, int line, std::string_view what, std::string_view why)
{
    AddDetail_Description("Exception occurred");
    AddDetail_Description(what);
    AddDetail_Location(function, line);
    AddDetail_Reason(why);
}

void D3EZ::EZException::AddDetail_Location(std::string_view function, int line)
{
    AppendMessage(fmt::format("In function {} on line {}", function, line));
}

void D3EZ::EZException::AddDetail_Description(std::string_view desc)
{
    AppendMessage(desc);
}

void D3EZ::EZException::AddDetail_Reason(std::string_view desc)
{
    AppendMessage(fmt::format("Cause by: {}", desc));
}

void D3EZ::EZException::AppendMessage(std::string_view msg)
{
    if (m_msg.empty())
    {
        m_msg = msg;
    }
    else
    {
        m_msg += "\n";
        m_msg += msg;
    }

    spdlog::error("[Exception] [{}] {}", m_eid, msg);
}

char const* D3EZ::EZException::what() const
{
    return m_msg.c_str();
}
