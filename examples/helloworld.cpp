#include <PlutoFramework.h>

class TestApp : public Pluto::Application {
public:
    void Init(void) override { hw.Set("Hello World!"); }
    void PostInit(void) override {}
    void Update(void) override { 
        Pluto::GetFramework()->PrintLn("%s\n", hw.Get());
        Pluto::GetFramework()->MessageBox("Test", hw, Pluto::PLUTO_MSGBOX_INFORMATION, Pluto::PLUTO_MSGBOXBTN_OK);
        Quit();
    }
    void PreRender(void) override {}
    void Render(void) override {}
    void Cleanup(void) override {}
private:
    Pluto::String hw;  
};

PLUTO_MAIN {
    TestApp *app = new TestApp();
    int returnCode = app->Run(&argc, argv);
    delete app;
    return returnCode;
}
