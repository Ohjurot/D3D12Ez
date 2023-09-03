#pragma once

#include <fmt/format.h>
#include <fmt/chrono.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <memory>
#include <string>
#include <ctime>
#include <filesystem>

namespace D3EZ
{
    class LoggingProvider
    {
        public:
            using Logger = std::shared_ptr<spdlog::logger>;

        public:
            LoggingProvider(const LoggingProvider&) = delete;
            LoggingProvider& operator=(const LoggingProvider&) = delete;

            static void Init();
            static Logger CreateLogger(const std::string& name);

        private:
            LoggingProvider() = default;
    };
}
