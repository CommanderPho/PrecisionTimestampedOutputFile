@REM cd "C:\Users\Pho\repos\OpenEphys\plugin-GUI\Build"


@REM This should affect the global environment variables
set GUI_BASE_DIR=C:\Users\pho\repos\OpenEphys\plugin-GUI

setlocal

set VS_VERSION="Visual Studio 17 2022"
@REM set VS_VERSION="Visual Studio 16 2019"
set MSBUILD_PATH="%ProgramFiles%\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe"

cd "C:\Users\pho\repos\OpenEphys\plugin-GUI\Build"
cmake -G %VS_VERSION% -A x64 ..
start open-ephys-GUI.sln
%MSBUILD_PATH% -target:ALL_BUILD -t:Rebuild -p:Configuration=Release


cd "C:\Users\pho\repos\OpenEphys\OEPlugins\PrecisionTimestampedOutputFile\Build"
cmake -G %VS_VERSION% -A x64 ..
start OE_PLUGIN_PrecisionTimestampedOutputFile.sln

%MSBUILD_PATH% "OE_PLUGIN_PrecisionTimestampedOutputFile.sln" -target:ALL_BUILD -t:Rebuild -p:Configuration=Release
@REM msbuild "OE_PLUGIN_PrecisionTimestampedOutputFile.sln" -target:ALL_BUILD:Rebuild;


@REM NEW 2024-03-28 
cd "C:\Users\pho\repos\OpenEphys\OEPlugins\PrecisionTimestampedOutputFileNew\Build"
cmake -G %VS_VERSION% -A x64 ..
start "OE_PLUGIN_PrecisionTimestampedOutputFileNew.sln"
%MSBUILD_PATH% "OE_PLUGIN_PrecisionTimestampedOutputFileNew.sln" -target:ALL_BUILD -t:Rebuild -p:Configuration=Release

endlocal