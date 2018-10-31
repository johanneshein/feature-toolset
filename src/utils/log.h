#ifndef SDK_FEATURE_TOOLSET_UTILS_LOG_H_
#define SDK_FEATURE_TOOLSET_UTILS_LOG_H_

#include <cstdio> /* FILE */
#include <sstream> /* std::ostringstream */

enum LogLevel {
    DEBUG = 0,
    INFO = 1,
    WARNING = 2,
    ERROR = 3
};

class Log {
    public:
        /**
         * Creates an Log object.
         */
        Log();

        /**
         * The destructor prints out the log lines.
         */
        ~Log();

        /**
         * \brief Get an output stream for inserting a log message.
         *
         * \return A stream object to print out. Adds first important
         * infoormation before the actual log line.
         */
        std::ostringstream& Get(LogLevel level = DEBUG);

        /**
         * Convert a constant LogLevel to an LogLevel output string.
         */
        static std::string toString(LogLevel level);

    private:
        /**
         * A private copy constructor for access protection issues.
         */
        Log(const Log&);

        /**
         * A private assignment constructor for access protection issues.
         */
        Log& operator= (const Log&);

        /**
         * A stream object to remember the message to be outputted.
         */
        std::ostringstream _os;

        /**
         * Stores the given log level for this log message at the time
         * of call.
         */
        LogLevel _messageLevel;

        FILE* const _LOG_OUTPUT_TARGET;

        const LogLevel _LOG_MIN_OUTPUT_LEVEL;
};

#endif // SDK_FEATURE_TOOLSET_UTILS_LOG_H_