#include "DXContext.h"

bool DXContext::Init()
{
    if (FAILED(CreateDXGIFactory2(0, IID_PPV_ARGS(&m_dxgiFactory))))
    {
        return false;
    }

    if (FAILED(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_device))))
    {
        return false;
    }

    D3D12_COMMAND_QUEUE_DESC cmdQueueDesc{};
    cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_HIGH;
    cmdQueueDesc.NodeMask = 0;
    cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    if (FAILED(m_device->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(&m_cmdQueue))))
    {
        return false;
    }

    if (FAILED(m_device->CreateFence(m_fenceValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence))))
    {
        return false;
    }

    m_fenceEvent = CreateEvent(nullptr, false, false, nullptr);
    if (!m_fenceEvent)
    {
        return false;
    }

    if (FAILED(m_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_cmdAllocator))))
    {
        return false;
    }

    if (FAILED(m_device->CreateCommandList1(0, D3D12_COMMAND_LIST_TYPE_DIRECT, D3D12_COMMAND_LIST_FLAG_NONE, IID_PPV_ARGS(&m_cmdList))))
    {
        return false;
    }

    return true;
}

void DXContext::Shutdown()
{
    m_cmdList.Release();
    m_cmdAllocator.Release();
    if (m_fenceEvent)
    {
        CloseHandle(m_fenceEvent);
    }
    m_fence.Release();
    m_cmdQueue.Release();
    m_device.Release();

    m_dxgiFactory.Release();
}

void DXContext::SignalAndWait()
{
    m_cmdQueue->Signal(m_fence, ++m_fenceValue);
    if (SUCCEEDED(m_fence->SetEventOnCompletion(m_fenceValue, m_fenceEvent)))
    {
        if (WaitForSingleObject(m_fenceEvent, 20000) != WAIT_OBJECT_0)
        {
            std::exit(-1);
        }
    }
    else
    {
        std::exit(-1);
    }
}

ID3D12GraphicsCommandList7* DXContext::InitCommandList()
{
    m_cmdAllocator->Reset();
    m_cmdList->Reset(m_cmdAllocator, nullptr);
    return m_cmdList;
}

void DXContext::ExecuteCommandList()
{
    if (SUCCEEDED(m_cmdList->Close()))
    {
        ID3D12CommandList* lists[] = { m_cmdList };
        m_cmdQueue->ExecuteCommandLists(1, lists);
        SignalAndWait();
    }
}
