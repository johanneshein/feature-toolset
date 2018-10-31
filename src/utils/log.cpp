#include "utils/log.h"
#include "utils/timing.h" /* getCurrentTimeString() */

Log::Log() :
    _LOG_OUTPUT_TARGET(stdout),
    _LOG_MIN_OUTPUT_LEVEL(LogLevel::DEBUG)
{
}

Log::~Log()
{
    if (_messageLevel >= _LOG_MIN_OUTPUT_LEVEL) {
        _os << std::endl;

        fprintf(_LOG_OUTPUT_TARGET, "%s", _os.str().c_str());
        fflush(_LOG_OUTPUT_TARGET);
    }
}

std::ostringstream& Log::Get(LogLevel level)
{
    _os << "+ " << getCurrentTimeString() << "  " << this->toString(level) << "\t";
    _messageLevel = level;
    return _os;
}

std::string Log::toString(LogLevel level)
{
    static const char* const buffer[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    return buffer[level];
}