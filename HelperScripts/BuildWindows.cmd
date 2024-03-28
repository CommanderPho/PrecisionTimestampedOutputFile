@REM cd "C:\Users\Pho\repos\OpenEphys\plugin-GUI\Build"
cd "C:\Users\pho\repos\OpenEphys\plugin-GUI\Build"

cmake -G "Visual Studio 17 2022" -A x64 ..
start open-ephys-GUI.sln
"%ProgramFiles%\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" "open-ephys-GUI.sln" -target:ALL_BUILD -t:Rebuild -p:Configuration=Release

@REM cd "C:\Users\Pho\repos\OpenEphys\OEPlugins\PrecisionTimestampedOutputFile\Build"
@REM cd "OEPlugins\PrecisionTimestampedOutputFile\Build"


set GUI_BASE_DIR=C:\Users\pho\repos\OpenEphys\plugin-GUI

@REM cd "C:\Users\Pho\repos\OpenEphys\OEPlugins\PrecisionTimestampedOutputFile\Build"
cd "C:\Users\pho\repos\OpenEphys\OEPlugins\PrecisionTimestampedOutputFile\Build"
cmake -G "Visual Studio 17 2022" -A x64 ..
start OE_PLUGIN_PrecisionTimestampedOutputFile.sln

"%ProgramFiles%\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" "OE_PLUGIN_PrecisionTimestampedOutputFile.sln" -target:ALL_BUILD -t:Rebuild -p:Configuration=Release
@REM msbuild "OE_PLUGIN_PrecisionTimestampedOutputFile.sln" -target:ALL_BUILD:Rebuild;


@REM NEW 2024-03-28 
cd "C:\Users\pho\repos\OpenEphys\OEPlugins\PrecisionTimestampedOutputFileNew\Build"
cmake -G "Visual Studio 17 2022" -A x64 ..
start "OE_PLUGIN_PrecisionTimestampedOutputFileNew.sln"
"%ProgramFiles%\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" "OE_PLUGIN_PrecisionTimestampedOutputFileNew.sln" -target:ALL_BUILD -t:Rebuild -p:Configuration=Release