#include <iostream>
#include "Tests.h"
#include "RezervareCamera.h"
#include "Repository.h"
#include "Service.h"
#include "Console.h"

using namespace std;

int main()
{
    testDomain();
    testRepository();
    testService();

    Repository<RezervareCamera> repository{};
    Service service{ repository };
    Console console{ service };
    console.run();
    return 0;
}
