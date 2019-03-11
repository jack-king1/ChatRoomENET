#include <memory>
#include "Server.h"

int main()
{
  std::unique_ptr<Server> server =
          std::make_unique<Server>();

  server->initialise();
  server->run();
  return 0;
}
