#include "App.h"
#include <windows.h>


int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    App app;
    app.run();

    return 0;
}