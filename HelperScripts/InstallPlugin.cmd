@echo off
@REM cp "C:\Users\Pho\repos\OpenEphys\OEPlugins\PrecisionTimestampedOutputFile\Build\RelWithDebInfo\PrecisionTimestampedOutputFile.dll" "C:\ProgramData\Open Ephys\plugins\PrecisionTimestampedOutputFile.dll"


set PLUGIN_DIR=C:\Users\Pho\repos\OpenEphys\OEPlugins\PrecisionTimestampedOutputFile\Build\Debug
@REM Official Release
set PROGRAM_PLUGINS_PATH=C:\ProgramData\Open Ephys\plugins
@REM Debug
set PROGRAM_PLUGINS_PATH=C:\Users\Pho\repos\OpenEphys\plugin-GUI\Build\Debug\plugins

@REM cp "C:\Users\Pho\repos\OpenEphys\OEPlugins\PrecisionTimestampedOutputFile\Build\Debug\PrecisionTimestampedOutputFile.pdb" "C:\ProgramData\Open Ephys\plugins\PrecisionTimestampedOutputFile.dll"

echo Installing to %PROGRAM_PLUGINS_PATH%
copy "C:\Users\Pho\repos\OpenEphys\OEPlugins\PrecisionTimestampedOutputFile\Build\Debug\PrecisionTimestampedOutputFile.dll" "%PROGRAM_PLUGINS_PATH%\PrecisionTimestampedOutputFile.dll"
copy "C:\Users\Pho\repos\OpenEphys\OEPlugins\PrecisionTimestampedOutputFile\Build\Debug\PrecisionTimestampedOutputFile.pdb" "%PROGRAM_PLUGINS_PATH%\PrecisionTimestampedOutputFile.pdb"

echo Done

pause


