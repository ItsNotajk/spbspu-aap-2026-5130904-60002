#include <iostream>

const int INPUT_ERROR_CODE = 1;
const int CALCULATION_ERROR_CODE = 2;

int main()
{
  int currElem = 0;
  int prevElem = 0;
  bool isFirstElem = true;

  bool seqFeatError = false;

  int maxDescLen = 0;
  int currDescLen = 0;

  int minCount = 0;

  while (true)
  {
    prevElem = currElem;

    std::cin >> currElem;
    if (std::cin.fail())
    {
      std::cerr << "ERROR: The given symbols are not a sequence\n";
      return INPUT_ERROR_CODE;
    }

    if (currElem == 0)
    {
      if (isFirstElem)
      {
        std::cerr << "[LOC-MIN] ERROR: The given sequence is empty\n";
	seqFeatError = true;
      }
      break;
    }

    if (isFirstElem)
    {
      currDescLen = 1;
      isFirstElem = false;
      continue;
    }

    if (currElem <= prevElem)
    {
      currDescLen++;
      if (currDescLen > maxDescLen)
      {
	maxDescLen = currDescLen;
      }
    }
    else
    {
      if (currDescLen > 1)
      {
	minCount++;
      }
      currDescLen = 1;
    }
  }

  std::cout << "[MON-DEC] Maximum descending order length: " << maxDescLen << "\n";

  if (seqFeatError)
  {
	return 2;
  }

  std::cout << "[LOC-MIN] Number of minimums: " << minCount << "\n";

  return 0;
}
