#include <iostream>

#include <Support/WinInclude.h>
#include <Support/ComPointer.h>
#include <Support/Window.h>

#include <Debug/DXDebugLayer.h>

#include <D3D/DXContext.h>

int main()
{
    DXDebugLayer::Get().Init();
    if (DXContext::Get().Init() && DXWindow::Get().Init())
    {
        DXWindow::Get().SetFullscreen(true);
        while (!DXWindow::Get().ShouldClose())
        {
            // Process pending window message
            DXWindow::Get().Update();
            
            // Handle resizing
            if (DXWindow::Get().ShouldResize())
            {
                DXContext::Get().Flush(DXWindow::GetFrameCount());
                DXWindow::Get().Resize();
            }
            
            // Begin drawing
            auto* cmdList = DXContext::Get().InitCommandList();
            
            // Draw to window
            DXWindow::Get().BeginFrame(cmdList);
            // TODO: Draw
            DXWindow::Get().EndFrame(cmdList);

            // Finish drawing and present
            DXContext::Get().ExecuteCommandList();
            DXWindow::Get().Preset();
        }

        // Flushing
        DXContext::Get().Flush(DXWindow::GetFrameCount());

        DXWindow::Get().Shutdown();
        DXContext::Get().Shutdown();
    }
    DXDebugLayer::Get().Shutdown();
}
