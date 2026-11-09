#include<iostream>
#include<cstddef>
#include<cctype>
#include<cstring>

namespace budakov
{
  const int START_SIZE = 10;
  const int INVALID_INPUT_CODE = 1;

  void convertToLower(char * const str) noexcept
  {
    for (std::size_t i = 0; str[i] != '\0'; i++)
    {
      const char symbol = str[i];
      if (std::isupper(str[i]))
      {
        str[i] = std::tolower(symbol);
      }
    }
  }

  void missingLatinSequence(char * const src, char * dest) noexcept
  {
    bool latin_symbols[26] { false };
    for (std::size_t i = 0; src[i] != '\0'; i++)
    {
      if ('a' <= src[i] && src[i] <= 'z')
      {
        latin_symbols[src[i] - 'a'] = true;
      }
    }
    std::size_t i = 0;
    for (char c = 'a'; c < 'z'; c++)
    {
      if (latin_symbols[c-'a'] == 0)
      {
        dest[i++] = c;
      }
    }
    dest[i] = '\0';
  }

  char * readSequence()
  {
    char * str = new char[START_SIZE];
    int current_size = START_SIZE;
    int index = 0;
    char current_symbol = '\0';

    try
    {
      while (std::cin.get(current_symbol) && current_symbol != '\n')
      {
        if (index < current_size - 1)
        {
          str[index] = current_symbol;
        }
        else
        {
          current_size *= 2;
          char * new_str = new char[current_size];
          for (std::size_t i = 0; i < index; i++)
          {
            new_str[i] = str[i];
          }
          delete[] str;
          str = new_str;
          new_str = nullptr;
          str[index] = current_symbol;
        }
        if (!(std::isalpha(str[index]) || str[index] == ' '))
        {
          throw std::invalid_argument("argument is not a number\n");
        }
        index++;
        str[index] = '\0';
      }
    }
    catch (...)
    {
      delete[] str;
      str = nullptr;
      throw;
    }

    if (index == 0)
    {
      delete[] str;
      str = nullptr;
      throw std::invalid_argument("sequence is empty\n");
    }

    return str;
  }

  char * copySequence(char * str)
  {
    char * res = nullptr;
    const int size = strlen(str) + 1;
    try
    {
      res = new char[size];
      strcpy(res, str);
    }
    catch(...)
    {
      delete[] res;
      res = nullptr;
      throw;
    }
    return res;
  }

  void printSequence(const char * const str)
  {
    size_t size = strlen(str);
    for (std::size_t i = 0; i < size; i++)
    {
      std::cout << str[i];
    }
    std::cout << "\n";
  }
}

int main()
{
  char * str = nullptr;
  char * lower_case = nullptr;

  try
  {
    str = budakov::readSequence();
    lower_case = budakov::copySequence(str);
    budakov::convertToLower(lower_case);
    budakov::printSequence(lower_case);

    char result_buffer[27] { '\0' };
    budakov::missingLatinSequence(lower_case, result_buffer);
    budakov::printSequence(result_buffer);
  }
  catch (std::exception& e)
  {
    std::cerr << "ERROR:  " << e.what() << '\n';
    delete[] str;
    str = nullptr;
    delete[] lower_case;
    lower_case = nullptr;
    return budakov::INVALID_INPUT_CODE;
  }

  delete[] str;
  str = nullptr;
  delete[] lower_case;
  lower_case = nullptr;

  return 0;
}
