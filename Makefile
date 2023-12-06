CXX := g++
CXXFLAGS := -Wall -Wextra -pedantic -std=c++11
LDFLAGS := -pthread
TARGET := libslog.a
SRCDIR := src
BUILDDIR := build
SOURCES := $(wildcard $(SRCDIR)/*.cpp)  # Change the file extension to .cpp
OBJECTS := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))  # Change the file extension to .cpp

.PHONY: all clean install remove

all: $(TARGET)

$(TARGET): $(OBJECTS)
	ar rcs $@ $(OBJECTS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c $< -o $@

install: $(TARGET)
	cp $(TARGET) /usr/lib/
	cp $(SRCDIR)/slog.h /usr/include/
	cp $(SRCDIR)/colors.h /usr/include/

remove:
	rm -f /usr/lib/$(TARGET)
	rm -f /usr/include/slog.h
	rm -f /usr/include/colors.h

clean:
	rm -rf $(BUILDDIR) $(TARGET)

