#include "ImageLoader.h"

const std::vector<ImageLoader::GUID_to_DXGI> ImageLoader::s_lookupTable =
{
    { GUID_WICPixelFormat32bppBGRA , DXGI_FORMAT_B8G8R8A8_UNORM },
    { GUID_WICPixelFormat32bppRGBA , DXGI_FORMAT_R8G8B8A8_UNORM },
};

bool ImageLoader::LoadImageFromDisk(const std::filesystem::path& imagePath, ImageData& data)
{
    // Factory
    ComPointer<IWICImagingFactory> wicFactory;
    __ImageLoader_CAR(
        CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&wicFactory))
    );

    // Load the image
    ComPointer<IWICStream> wicFileStream;
    __ImageLoader_CAR(
        wicFactory->CreateStream(&wicFileStream)
    );
    __ImageLoader_CAR(
        wicFileStream->InitializeFromFilename(imagePath.wstring().c_str(), GENERIC_READ)
    );

    ComPointer<IWICBitmapDecoder> wicDecoder;
    __ImageLoader_CAR(
        wicFactory->CreateDecoderFromStream(wicFileStream, nullptr, WICDecodeMetadataCacheOnDemand, &wicDecoder)
    );
    ComPointer<IWICBitmapFrameDecode> wicFrameDecoder;
    __ImageLoader_CAR(
        wicDecoder->GetFrame(0, &wicFrameDecoder)
    );

    // Trivial metadata
    __ImageLoader_CAR(
        wicFrameDecoder->GetSize(&data.width, &data.height)
    );
    __ImageLoader_CAR(
        wicFrameDecoder->GetPixelFormat(&data.wicPixelFormat)
    );

    // Metadata of pixel format
    ComPointer<IWICComponentInfo> wicComponentInfo;
    __ImageLoader_CAR(
        wicFactory->CreateComponentInfo(data.wicPixelFormat, &wicComponentInfo)
    );
    ComPointer<IWICPixelFormatInfo> wicPixelFormatInfo;
    __ImageLoader_CAR(
        wicComponentInfo->QueryInterface(&wicPixelFormatInfo)
    );
    __ImageLoader_CAR(
        wicPixelFormatInfo->GetBitsPerPixel(&data.bpp)
    );
    __ImageLoader_CAR(
        wicPixelFormatInfo->GetChannelCount(&data.cc)
    );

    // DXGI Pixel format
    auto findIt = std::find_if(s_lookupTable.begin(), s_lookupTable.end(), 
        [&](const GUID_to_DXGI& entry) 
        {
            return memcmp(&entry.wic, &data.wicPixelFormat, sizeof(GUID)) == 0;
        }
    );
    if (findIt == s_lookupTable.end())
    {
        return false;
    }
    data.giPixelFormat = findIt->gi;

    // Image loading
    uint32_t stride = ((data.bpp + 7) / 8) * data.width;
    uint32_t size = stride * data.height;
    data.data.resize(size);

    WICRect copyRect;
    copyRect.X = copyRect.Y = 0;
    copyRect.Width = data.width;
    copyRect.Height = data.height;

    __ImageLoader_CAR(
        wicFrameDecoder->CopyPixels(&copyRect, stride, size, (BYTE*)data.data.data())
    );

    return true;
}
