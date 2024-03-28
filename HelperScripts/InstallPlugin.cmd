@echo off

setlocal

@REM set ReleaseMode=Debug
set ReleaseMode=Release

@REM cp "C:\Users\Pho\repos\OpenEphys\OEPlugins\PrecisionTimestampedOutputFile\Build\RelWithDebInfo\PrecisionTimestampedOutputFile.dll" "C:\ProgramData\Open Ephys\plugins\PrecisionTimestampedOutputFile.dll"


@REM set PLUGIN_DIR=C:\Users\Pho\repos\OpenEphys\OEPlugins\PrecisionTimestampedOutputFile\Build\Debug
set PLUGIN_DIR=C:\Users\Pho\repos\OpenEphys\OEPlugins\PrecisionTimestampedOutputFile\Build\%ReleaseMode%


@REM Official Release
set OFFICIAL_PROGRAM_PLUGINS_PATH=C:\ProgramData\Open Ephys\plugins
@REM Debug
set PROGRAM_PLUGINS_PATH=C:\Users\Pho\repos\OpenEphys\plugin-GUI\Build\%ReleaseMode%\plugins

@REM cp "C:\Users\Pho\repos\OpenEphys\OEPlugins\PrecisionTimestampedOutputFile\Build\%ReleaseMode%\PrecisionTimestampedOutputFile.pdb" "C:\ProgramData\Open Ephys\plugins\PrecisionTimestampedOutputFile.dll"

echo Installing to %PROGRAM_PLUGINS_PATH%
copy "%PLUGIN_DIR%\PrecisionTimestampedOutputFile.dll" "%PROGRAM_PLUGINS_PATH%\PrecisionTimestampedOutputFile.dll"
@REM copy "%PLUGIN_DIR%\PrecisionTimestampedOutputFile.pdb" "%PROGRAM_PLUGINS_PATH%\PrecisionTimestampedOutputFile.pdb"
echo Done


echo Installing to %OFFICIAL_PROGRAM_PLUGINS_PATH%
copy "%PLUGIN_DIR%\PrecisionTimestampedOutputFile.dll" "%OFFICIAL_PROGRAM_PLUGINS_PATH%\PrecisionTimestampedOutputFile.dll"
@REM copy "%PLUGIN_DIR%\PrecisionTimestampedOutputFile.pdb" "%OFFICIAL_PROGRAM_PLUGINS_PATH%\PrecisionTimestampedOutputFile.pdb"
echo Done

endlocal

@REM pause


