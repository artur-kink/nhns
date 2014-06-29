#ifndef _UTILITIES_
#define _UTILITIES_

/**
 * List of all utilities.
 * Utilities are general purpose classes and tools
 * used by many areas of the engine.
 */

//Timing utilities
#include "Time.hpp"
#include "Timer.hpp"
#include "AccumulativeTimer.hpp"
#include "CalendarTime.hpp"
#include "IntervalCounter.hpp"
#include "TandemTimer.hpp"

//Logging utilities
#include "Logger.hpp"
#include "LogManager.hpp"
#include "ConsoleLogger.hpp"
#include "FileLogger.hpp"

//I/O
#include "Serializable.hpp"
#include "FileHandler.hpp"
#include "MemoryPool.hpp"

//Helpers
#include "MathHelper.hpp"
#include "StringHelper.hpp"

//Misc
#include "KeyValuePair.hpp"
#include "ResourceManager.hpp"
#include "InputHandler.hpp"
#include "TimedTween.hpp"
#include "OscillatingTween.hpp"

#endif