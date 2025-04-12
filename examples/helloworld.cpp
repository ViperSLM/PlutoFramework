#include "../src/PlutoFramework.h"

class TestApp : public Pluto::Application {
public:
    void Init(void) override { GetRunningFramework()->PrintLn("Hello World!"); }
    void PostInit(void) override {}
    void Update(void) override { Quit(); }
    void PreRender(void) override {}
    void Render(void) override {}
    void Cleanup(void) override {}
};

PLUTO_MAIN {
    TestApp *app = new TestApp();
    int returnCode = app->Run(&argc, argv);
    delete app;
    return returnCode;
}
