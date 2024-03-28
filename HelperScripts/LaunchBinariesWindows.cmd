setlocal

set ReleaseMode=Debug
cd "C:\Users\Pho\repos\OpenEphys\plugin-GUI\Build\%ReleaseMode%"
start "C:\Users\Pho\repos\OpenEphys\plugin-GUI\Build\%ReleaseMode%\open-ephys.exe"


start "C:\ProgramData\Open Ephys\plugins" .

endlocal