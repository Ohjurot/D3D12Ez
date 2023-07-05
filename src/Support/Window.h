#pragma once

#include <Support/WinInclude.h>
#include <Support/ComPointer.h>
#include <D3D/DXContext.h>

class DXWindow
{
    public:
        bool Init();
        void Update();
        void Preset();
        void Shutdown();
        void Resize();
        void SetFullscreen(bool enabled);

        inline bool ShouldClose() const
        {
            return m_shouldClose;
        }

        inline bool ShouldResize() const
        {
            return m_shouldResize;
        }

        inline bool IsFullscreen() const
        {
            return m_isFullscreen;
        }

        static constexpr size_t FrameCount = 2;
        static constexpr size_t GetFrameCount()
        {
            return FrameCount;
        }

    private:
        bool GetBuffers();
        void ReleaseBuffers();

        static LRESULT CALLBACK OnWindowMessage(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);

    private:
        ATOM m_wndClass = 0;
        HWND m_window = nullptr;
        bool m_shouldClose = false;

        bool m_shouldResize = false;
        UINT m_width = 1920;
        UINT m_height = 1080;

        bool m_isFullscreen = false;
        
        ComPointer<IDXGISwapChain3> m_swapChain;
        ComPointer<ID3D12Resource2> m_buffers[FrameCount];

    // singleton
    public:
        DXWindow(const DXWindow&) = delete;
        DXWindow& operator=(const DXWindow&) = delete;

        inline static DXWindow& Get()
        {
            static DXWindow instance;
            return instance;
        }
    private:
        DXWindow() = default;
};
