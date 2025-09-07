# Post Predictor ML - Naive Bayes Text Classifier

A C++ implementation of a Naive Bayes classifier for sentiment analysis of text data, featuring custom data structures and efficient text processing algorithms.

## 🎯 Project Overview

This project implements a machine learning classifier that predicts sentiment (positive/negative) of text content using the Naive Bayes algorithm. The system includes custom implementations of fundamental data structures and demonstrates advanced C++ programming concepts including recursion, memory management, and template programming.

## 🏗️ Main Components

### 1. **Naive Bayes Classifier** (`main.cpp`)
- **Text Preprocessing**: Case-insensitive tokenization with punctuation removal
- **Probabilistic Classification**: Implements log-probability calculations for sentiment prediction
- **Training Pipeline**: Processes CSV data to build word frequency models
- **Performance Metrics**: Calculates and displays classification accuracy

### 2. **Binary Search Tree** (`BinarySearchTree.hpp`)
- **Template-based Implementation**: Generic BST supporting custom comparison functors
- **Recursive Algorithms**: All operations implemented using recursion (no iteration)
- **Memory Management**: RAII with proper copy semantics and destructors
- **Iterator Support**: STL-compatible bidirectional iterators
- **Tree Traversals**: In-order and pre-order traversal implementations

### 3. **Associative Map** (`Map.hpp`)
- **BST-based Implementation**: Built on top of the custom BinarySearchTree
- **Key-Value Storage**: Generic key-value pair storage with custom comparators
- **STL Interface**: Compatible with standard library map operations
- **Efficient Lookup**: O(log n) insertion, deletion, and search operations

### 4. **CSV Processing** (`csvstream.hpp`)
- **Robust CSV Parser**: Handles quoted fields, escaped characters, and various delimiters
- **Error Handling**: Comprehensive exception handling for malformed data
- **Stream Interface**: STL-compatible input stream operations

### 5. **Tree Visualization** (`TreePrint.hpp`)
- **ASCII Tree Display**: Human-readable tree structure visualization
- **Grid-based Layout**: Automatic spacing and alignment for tree nodes
- **Debug Support**: Visual debugging tool for tree structure analysis

## 🚀 Getting Started

### Prerequisites
- **C++17 compatible compiler** (GCC 7+, Clang 5+, or MSVC 2017+)
- **Make** (optional, for build automation)

### Installation & Compilation

1. **Clone or download the project files**
   ```bash
   # Ensure you have all required files:
   # - main.cpp
   # - BinarySearchTree.hpp
   # - Map.hpp
   # - csvstream.hpp
   # - TreePrint.hpp
   ```

2. **Compile the project**
   ```bash
   g++ -std=c++17 -Wall -Wextra -o sentiment_classifier main.cpp
   ```

3. **Verify compilation**
   ```bash
   # Should compile without errors (warnings about unused parameters are normal)
   ```

## 📊 Usage

### Basic Classification
```bash
./sentiment_classifier train.csv test.csv
```

### Debug Mode (Detailed Output)
```bash
./sentiment_classifier train.csv test.csv --debug
```

### Expected Output
```
trained on 20 examples

test data:
  correct = positive, predicted = positive, log-probability score = -8.5
  content = Wonderful film with great story and acting

  correct = negative, predicted = negative, log-probability score = -7.88
  content = Terrible movie waste of money and time

performance: 6 / 6 posts predicted correctly
```

## 📁 Data Format

### Training/Test CSV Format
```csv
n,tag,content
1,positive,"I love this movie it's amazing"
2,negative,"This film is terrible and boring"
3,positive,"Great acting and wonderful story"
```

**Required Columns:**
- `n`: Row identifier (integer)
- `tag`: Classification label (string)
- `content`: Text content to classify (string, supports quotes)

## 🔧 Technical Features

### Algorithm Implementation
- **Naive Bayes**: Probabilistic classification using word frequency analysis
- **Log-space Calculations**: Prevents numerical underflow in probability computations
- **Smoothing**: Handles unseen words with appropriate fallback probabilities

### Data Structures
- **Custom BST**: Recursive implementation with full STL compatibility
- **Template Programming**: Generic implementations supporting any comparable types
- **Memory Safety**: RAII patterns with proper resource management

### Text Processing
- **Tokenization**: Whitespace-based word extraction
- **Normalization**: Case-insensitive processing with punctuation removal
- **Vocabulary Building**: Efficient word frequency tracking

## 🧪 Testing

### Sample Data
The project includes sample training and test data:
- `train.csv`: 20 movie review examples (10 positive, 10 negative)
- `test.csv`: 6 test examples for validation

### Performance Validation
```bash
# Run with sample data
./sentiment_classifier train.csv test.csv

# Expected: 100% accuracy on provided test set
# Output: "performance: 6 / 6 posts predicted correctly"
```

### Custom Data Testing
1. Create your own CSV files following the required format
2. Ensure balanced training data for optimal performance
3. Use descriptive, varied vocabulary in your content

## 🏛️ Architecture

```
┌─────────────────┐    ┌──────────────────┐    ┌─────────────────┐
│   CSV Parser    │───▶│  Text Processor  │───▶│ Naive Bayes     │
│ (csvstream.hpp) │    │ (unique_words)   │    │ Classifier      │
└─────────────────┘    └──────────────────┘    └─────────────────┘
                                │                        │
                                ▼                        ▼
                       ┌──────────────────┐    ┌─────────────────┐
                       │  BST/Map Data    │    │  Classification │
                       │  Structures      │    │  Results        │
                       └──────────────────┘    └─────────────────┘
```

## 🎓 Learning Objectives

This project demonstrates:
- **Advanced C++**: Templates, RAII, STL compatibility
- **Data Structures**: Custom BST and Map implementations
- **Algorithms**: Recursive tree operations and probabilistic classification
- **Memory Management**: Proper resource handling and copy semantics
- **Text Processing**: Tokenization, normalization, and feature extraction

## 📈 Performance

- **Training Time**: O(n × m) where n = documents, m = average words per document
- **Classification Time**: O(k) where k = unique words in test document
- **Memory Usage**: O(v) where v = vocabulary size
- **Accuracy**: 100% on provided test set (varies with training data quality)

## 🔍 Debug Features

Enable debug mode to see:
- Complete training data processing
- Vocabulary statistics
- Class priors and word likelihoods
- Detailed classification parameters

## 📝 License

This project is for educational and demonstration purposes.

---

**Note**: This implementation prioritizes educational value and code clarity over production optimization. For production use, consider additional optimizations such as sparse matrix representations and parallel processing.
