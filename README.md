# SLog++

**Shitty Logging** in C++ (see [`slog`](https://github.com/LanaMirko04/slog))

## Features

- Logging messages with different log levels.
- Customizable log output.
- Color support.
- Clean text for piped output or files.

## Installation

```shell
$ git clone https://github.com/LanaMirko04/slog.git
$ cd slogpp
$ make
$ sudo make install
```

or

Copy files in src directory to your project

```shell
$ tree
.
├── LICENSE
├── Makefile
├── README.md
└── src
    ├── colors.h
    ├── main.cpp
    ├── slogpp.cpp
    └── slogpp.h
```

## Usage
#### Console logging
```c
#include <iostream>
#include <slogpp.h>

int main(void) {
  int log_level = SLog::Level::INFO | SLog::Level::DEBUG | SLog::Level::WARN | SLog::Level::ERROR;
  SLog::set_log_level(log_level);

  SLog::info("This is an info message");
  SLog::debug("This is a debug message");
  SLog::warn("This is a warning message");
  SLog::error("This is an error message");

  return 0;
}
```

#### File logging
```c
#include <iostream>
#include <slogpp.h>

int main(void) {
  int log_level = SLog::Level::INFO | SLog::Level::DEBUG | SLog::Level::WARN | SLog::Level::ERROR;
  SLog::set_log_file("example.log");
  SLog::set_log_level(log_level);

  SLog::info("This is an info message");
  SLog::debug("This is a debug message");
  SLog::warn("This is a warning message");
  SLog::error("This is an error message");

  return 0;
}
```

#### Compilation
```shell
g++ -o example example.cpp -lslogpp
```

## License
SLog++ is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

<!--
## Acknowledgements
- [VHS](https://github.com/charmbracelet/vhs)
-->
