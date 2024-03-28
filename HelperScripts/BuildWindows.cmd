cd "C:\Users\Pho\repos\OpenEphys\plugin-GUI\Build"
cmake -G "Visual Studio 17 2022" -A x64 ..


@REM cd "C:\Users\Pho\repos\OpenEphys\OEPlugins\PrecisionTimestampedOutputFile\Build"
@REM cd "OEPlugins\PrecisionTimestampedOutputFile\Build"

cd "C:\Users\Pho\repos\OpenEphys\OEPlugins\PrecisionTimestampedOutputFile\Build"
cmake -G "Visual Studio 17 2022" -A x64 ..
start OE_PLUGIN_PrecisionTimestampedOutputFile.sln
msbuild "OE_PLUGIN_PrecisionTimestampedOutputFile.sln" -target:ALL_BUILD:Rebuild;