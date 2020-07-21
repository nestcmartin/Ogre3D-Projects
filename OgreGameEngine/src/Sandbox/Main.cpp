#include "TestApplication.h"

int main(int argc, char *argv[])
{
    TestApplication app;
    app.setup();
    app.run();
    app.shutdown();

    return 0;
}