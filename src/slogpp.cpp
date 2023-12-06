/*
 * SLog++ (Shitty Logging for C++) - slogpp.cpp
 * (c) 2023 Lana Mirko
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <unistd.h>
#include "slogpp.h"
#include "colors.h"

using namespace std;

/*
 * Static variables
 */
int SLog::log_level = 0;
FILE * SLog::log_file = nullptr;

/*
 * Method to set log level
 *
 * Parameters:
 *   - lv: log level as integer
 */
void SLog::set_log_level(int lv) {
  log_level = lv;
}

/*
 * Method to set log level
 *
 * Parameters:
 *   - lv: log level as enum
 */
void SLog::set_log_level(SLog::Level lv) {
  log_level = static_cast < int > (lv);
}

/*
 * Method to set log file
 *
 * Parameters:
 *   - filename: log file name
 */
bool SLog::set_log_file(const char * filename) {
  if (log_file == nullptr) {
    log_file = fopen(filename, "w");
    if (log_file == nullptr) {
      cerr << "Error: i can not open " << filename << endl;
      return false;
    }

    atexit(SLog::close_log_file);
  }

  return true;
}

/*
 * Method to set log file
 *
 * Parameters:
 *   - filename: log file name
 */
bool SLog::set_log_file(const string & filename) {
  if (log_file == nullptr) {
    log_file = fopen(filename.c_str(), "w");
    if (log_file == nullptr) {
      cerr << "Error: i can not open " << filename << endl;
      return false;
    }

    atexit(SLog::close_log_file);
  }

  return true;
}

/*
 * Method to close log file
 */
void SLog::close_log_file() {
  if (log_file != nullptr) {
    fclose(log_file);
    log_file = nullptr;
  }
}

/*
 * Method to log message with info level
 *
 * Parameters:
 *   - lv: log level
 *   - fmt: format string
 *   - ...: format arguments
 */
void SLog::info(const char * fmt...) {
  if (log_level & SLog::Level::INFO) {
    va_list args;
    va_start(args, fmt);

    SLog::log(SLog::Level::INFO, fmt, args);

    va_end(args);
  }
}

/*
 * Method to log message with debug level
 *
 * Parameters:
 *   - lv: log level
 *   - fmt: format string
 *   - ...: format arguments
 */
void SLog::debug(const char * fmt...) {
  if (log_level & SLog::Level::DEBUG) {
    va_list args;
    va_start(args, fmt);

    SLog::log(SLog::Level::DEBUG, fmt, args);

    va_end(args);
  }
}

/*
 * Method to log message with warn level
 *
 * Parameters:
 *   - lv: log level
 *   - fmt: format string
 *   - ...: format arguments
 */
void SLog::warn(const char * fmt...) {
  if (log_level & SLog::Level::WARN) {
    va_list args;
    va_start(args, fmt);

    SLog::log(SLog::Level::WARN, fmt, args);

    va_end(args);
  }
}

/*
 * Method to log message with error level
 *
 * Parameters:
 *   - lv: log level
 *   - fmt: format string
 *   - ...: format arguments
 */
void SLog::error(const char * fmt...) {
  if (log_level & SLog::Level::ERROR) {
    va_list args;
    va_start(args, fmt);

    SLog::log(SLog::Level::ERROR, fmt, args);

    va_end(args);
  }
}

/*
 * Method to log message
 *
 * Parameters:
 *   - lv: log level
 *   - fmt: format string
 *   - args: format arguments
 */
void SLog::log(SLog::Level lv,
  const char * fmt, va_list args) {
  bool use_color = isatty(fileno(stdout)) || log_file;

  switch (lv) {
  case SLog::Level::INFO:
    if (use_color) {
      printf("%s%s[INFO]%s ", BOLD, GREEN, RESET);
    } else {
      printf("[INFO] ");
    }

    vfprintf(log_file ? log_file : stdout, fmt, args);
    fprintf(log_file ? log_file : stdout, "\n");
    break;

  case SLog::Level::DEBUG:
    if (use_color) {
      printf("%s%s[DEBUG]%s ", BOLD, CYAN, RESET);
    } else {
      printf("[DEBUG] ");
    }

    vfprintf(log_file ? log_file : stdout, fmt, args);
    fprintf(log_file ? log_file : stdout, "\n");
    break;

  case SLog::Level::WARN:
    if (use_color) {
      printf("%s%s[WARNING]%s ", BOLD, YELLOW, RESET);
    } else {
      printf("[WARNING] ");
    }

    vfprintf(log_file ? log_file : stdout, fmt, args);
    fprintf(log_file ? log_file : stdout, "\n");
    break;

  case SLog::Level::ERROR:
    if (use_color) {
      printf("%s%s[ERROR]%s ", BOLD, RED, RESET);
    } else {
      printf("[ERROR] ");
    }

    vfprintf(log_file ? log_file : stderr, fmt, args);
    fprintf(log_file ? log_file : stderr, "\n");
    break;
  }

}

/*
 * AND operator overloading
 */
int operator & (int lhs, SLog::Level rhs) {
  return lhs & static_cast < int > (rhs);
}

/*
 * OR operator overloading
 */
int operator | (SLog::Level lhs, SLog::Level rhs) {
  return static_cast < int > (lhs) | static_cast < int > (rhs);
}
