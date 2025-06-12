# Coding Standards

This document outlines the coding standards and best practices to be followed in this repository.

## C++ Coding Standards

### Naming Conventions
- **Classes**: PascalCase
  ```cpp
  class MyClass { ... };
  ```
- **Functions**: camelCase
  ```cpp
  void calculateTotal() { ... }
  ```
- **Variables**: camelCase
  ```cpp
  int userCount = 0;
  ```
- **Constants**: UPPER_SNAKE_CASE
  ```cpp
  const int MAX_SIZE = 100;
  ```
- **Member Variables**: m_camelCase
  ```cpp
  class MyClass {
      int m_count;
  };
  ```

### File Organization
- One class per header file
- Header files use `.hpp` extension
- Implementation files use `.cpp` extension
- Include guards in header files
  ```cpp
  #ifndef MY_CLASS_HPP
  #define MY_CLASS_HPP
  // ... code ...
  #endif
  ```

### Code Formatting
- Use 4 spaces for indentation
- Maximum line length: 100 characters
- Braces on new lines for functions and classes
- Braces on same line for control structures
  ```cpp
  class MyClass
  {
  public:
      void myFunction()
      {
          if (condition) {
              // code
          }
      }
  };
  ```

### Documentation
- Use Doxygen-style comments for classes and functions
  ```cpp
  /**
   * @brief Brief description
   * @param param1 Description of param1
   * @return Description of return value
   */
  ```

## Python Coding Standards

### Naming Conventions
- **Classes**: PascalCase
  ```python
  class MyClass:
      pass
  ```
- **Functions and Variables**: snake_case
  ```python
  def calculate_total():
      user_count = 0
  ```
- **Constants**: UPPER_SNAKE_CASE
  ```python
  MAX_SIZE = 100
  ```

### Code Formatting
- Follow PEP 8 guidelines
- Use 4 spaces for indentation
- Maximum line length: 88 characters
- Use type hints where appropriate
  ```python
  def process_data(data: List[int]) -> int:
      return sum(data)
  ```

### Documentation
- Use docstrings for all public functions and classes
  ```python
  def my_function(param1: int) -> bool:
      """
      Brief description of the function.

      Args:
          param1: Description of param1

      Returns:
          Description of return value
      """
      pass
  ```

## General Best Practices

### Version Control
- Write clear, descriptive commit messages
- Use feature branches for new development
- Keep commits focused and atomic

### Error Handling
- Use appropriate error handling mechanisms
- Provide meaningful error messages
- Log errors appropriately

### Testing
- Write unit tests for new functionality
- Maintain test coverage
- Use appropriate testing frameworks

### Security
- Never commit sensitive information
- Validate all input
- Use secure coding practices

### Performance
- Profile code when necessary
- Optimize critical paths
- Document performance considerations 
