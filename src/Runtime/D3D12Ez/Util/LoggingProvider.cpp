#include "LoggingProvider.h"

void D3EZ::LoggingProvider::Init()
{
    auto logger = spdlog::default_logger()->clone("D3EZ");

    // Logfile path
    std::time_t time = std::time(nullptr);
    auto logfile = std::filesystem::current_path();
    logfile /= "log";
    logfile /= fmt::format("ezlog_{:%d%m%Y_%H%M%S}.log", fmt::localtime(time));

    // Sinks
    logger->sinks().clear();
    logger->sinks().push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
    logger->sinks().push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(logfile.string()));

    // Pattern
    logger->set_pattern("[%^%l%$] [%d.%m.%Y %H:%M:%S'%e] [%n] %v");

    // Flushing
    logger->flush_on(spdlog::level::warn);

    // Level
#if defined(D3EZ_DEBUG)
    logger->set_level(spdlog::level::trace);
#elif defined(D3EZ_DEVELOPMENT)
    logger->set_level(spdlog::level::debug);
#else
    logger->set_level(spdlog::level::info);
#endif

    spdlog::set_default_logger(logger);
}

D3EZ::LoggingProvider::Logger D3EZ::LoggingProvider::CreateLogger(const std::string& name)
{
    return spdlog::default_logger()->clone(name);
}
