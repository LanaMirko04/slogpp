/*
 * SLog++ (Shitty Logging for C++) - slogpp.h
 * (c) 2023 Lana Mirko
 *
 */

#ifndef __SLOGPP_H__
#define __SLOGPP_H__

#include <cstdio>
#include <string>
#include <stdarg.h>

using namespace std;

class SLog {
  /*
   * Enum class for log levels
   */
public:
  enum class Level {
    INFO  = 0x01,
    DEBUG = 0x02,
    WARN  = 0x04,
    ERROR = 0x08,
  };

  /*
   * Method to set log level
   *
   * Parameters:
   *   - lv: log level as integer
   */
  static void set_log_level(int lv);

  /*
   * Method to set log level
   *
   * Parameters:
   *   - lv: log level as enum
   */
  static void set_log_level(Level lv);
  
  /*
   * Method to set log file
   *
   * Parameters:
   *   - filename: log file name
   */
  static bool set_log_file(const char * filename);
  
  /*
   * Method to set log file
   *
   * Parameters:
   *   - filename: log file name
   */
  static bool set_log_file(const string & filename);
  
  /*
   * Method to close log file
   */
  static void close_log_file();

  /*
   * Method to log message with info level
   *
   * Parameters:
   *   - lv: log level
   *   - fmt: format string
   *   - ...: format arguments
   */
  static void info(const char * fmt...);

  /*
   * Method to log message with debug level
   *
   * Parameters:
   *   - lv: log level
   *   - fmt: format string
   *   - ...: format arguments
   */
  static void debug(const char * fmt...);

  /*
   * Method to log message with warn level
   *
   * Parameters:
   *   - lv: log level
   *   - fmt: format string
   *   - ...: format arguments
   */
  static void warn(const char * fmt...);

  /*
   * Method to log message with error level
   *
   * Parameters:
   *   - lv: log level
   *   - fmt: format string
   *   - ...: format arguments
   */
  static void error(const char * fmt...);

  /* friend functions */
  friend int operator & (int lhs, Level rhs);
  friend int operator | (Level lhs, Level rhs);
  friend int operator | (int lhs, Level rhs);

private:
  /* static variables */
  static int    log_level;
  static FILE * log_file;

  /*
   * Method to log message
   *
   * Parameters:
   *   - lv: log level
   *   - fmt: format string
   *   - args: format arguments
   */
  static void log(Level lv,
    const char * fmt, va_list args);
};

#endif // __SLOGPP_H__
