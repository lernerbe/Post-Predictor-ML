# Makefile for Post Predictor ML - Naive Bayes Text Classifier

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = sentiment_classifier
SOURCE = main.cpp

# Default target
all: $(TARGET)

# Build the main executable
$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

# Clean build artifacts
clean:
	rm -f $(TARGET)

# Run with sample data
test: $(TARGET)
	./$(TARGET) train.csv test.csv

# Run with debug output
debug: $(TARGET)
	./$(TARGET) train.csv test.csv --debug

# Install (copy to /usr/local/bin)
install: $(TARGET)
	sudo cp $(TARGET) /usr/local/bin/

# Uninstall
uninstall:
	sudo rm -f /usr/local/bin/$(TARGET)

# Help target
help:
	@echo "Available targets:"
	@echo "  all      - Build the sentiment classifier (default)"
	@echo "  clean    - Remove build artifacts"
	@echo "  test     - Build and run with sample data"
	@echo "  debug    - Build and run with debug output"
	@echo "  install  - Install to /usr/local/bin"
	@echo "  uninstall- Remove from /usr/local/bin"
	@echo "  help     - Show this help message"

# Phony targets
.PHONY: all clean test debug install uninstall help