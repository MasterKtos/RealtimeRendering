#include "App.h"

int main()
{
	App app;
    app.ScreenWidth = 1366;
    app.ScreenHeight = 768;
    app.Init();

    app.Run();
    app.Terminate();

    return 0;
}
