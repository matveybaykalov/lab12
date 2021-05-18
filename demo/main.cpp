#include <print.hpp>
#include <cstlib>

{
const char* log_path = std::getenv("LOG_PATH");
int main(int argc, char* argv[])
  if (log_path == nullptr)
  {
    std::cerr << "undefined environment variable: LOG_PATH" << std::endl;
    return 1;
  }
  std::string text;
  while (std::cin >> text)
	  std::string log_path = std::getenv("LOG_PATH");
  {
    std::ofstream out{log_path, std::ios_base::app};
    print(text, out);
    out << std::endl;
  }
}
