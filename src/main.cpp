#include <iostream>

#include <Support/WinInclude.h>
#include <Support/ComPointer.h>

#include <Debug/DXDebugLayer.h>

#include <D3D/DXContext.h>

int main()
{
    DXDebugLayer::Get().Init();
    if (DXContext::Get().Init())
    {
        while (true)
        {
            auto* cmdList = DXContext::Get().InitCommandList();
            

            
            DXContext::Get().ExecuteCommandList();
        }

        DXContext::Get().Shutdown();
    }
    DXDebugLayer::Get().Shutdown();
}
