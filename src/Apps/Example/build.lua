mox_project("Example")
mox_cpp("C++20")
mox_console()

includedirs {
    "%{wks.location}/src/Runtime/D3D12Ez",
}

links { 
    "D3D12Ez", 
}

links {
    "d3d12.lib",
    "dxgi.lib",
    "dxguid.lib"
}
