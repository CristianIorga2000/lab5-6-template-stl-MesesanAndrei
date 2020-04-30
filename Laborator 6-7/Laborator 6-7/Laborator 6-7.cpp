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

    //Repository<RezervareCamera> repository{};
    FileRepository<RezervareCamera> repository("C:\\Users\\Andrei\\source\\repos\\lab5-6-template-stl-MesesanAndrei\\Laborator 6-7\\Laborator 6-7\\date.txt");
    Service service{ repository };
    Console console{ service };
    console.run();
    return 0;
}
