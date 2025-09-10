@echo off
TITLE DayzServer
COLOR 0A
:: DEFINE variables
SET SteamLogin= BuffaGunz Queensland95
SET DayZBranch=223350
SET DayZServerPath="C:\DayZServer"
SET SteamCMDPath="C:\SteamCMD"
:: DayZ Mod Parameters
set DayZModList=(C:\DayZServer\ModClient.txt)
set DayZServerModList=(C:\DayZServer\ModServer.txt)
set SteamCMDWorkshopPath="C:\SteamCMD\steamapps\workshop\content\221100"
set SteamCMDDelay=5
setlocal EnableDelayedExpansion

:: Set choice default
set skipUpd=0

goto choice

pause


:choice
cls
echo Press S to skip checking for updates.
echo Will continue to updates check momentarily... 
choice /t 6 /c su /d u
if %errorlevel% EQU 2 goto checkServer
if %errorlevel% EQU 1 goto skipUpdates

:skipUpdates
set skipUpd=1
goto loadMods

:checkServer
@tasklist /fi "imagename eq DayZServer_x64.exe" 2>NUL | findstr /i /r /c:"^DayZServer_x64.exe" >NUL
if "%ERRORLEVEL%"=="0" (
    goto loopServer
)
cls
echo Server is not running, taking care of it..
goto updateServer

:loopServer
FOR /L %%s IN (20,-1,0) DO (
	cls
	echo Server is running. Checking again in %%s seconds..
	timeout 1 >nul
)
goto checkServer

:updateServer
cls
echo Updating DayZServer  .
timeout 1 >nul
cls
echo Updating DayZServer  ..
timeout 1 >nul
cls
echo Updating DayZServer  ...
cd "%SteamCMDPath%"
steamcmd.exe +force_install_dir "%DayZServerPath%" +login %SteamLogin% +"app_update %DayZBranch%" +quit
goto updateMods

:startServer
cls
echo Starting DayZServer  .
timeout 1 >nul
cls
echo Starting DayZServer  ..
timeout 1 >nul
cls
echo Starting DayZServer  ...
cd "%DayZServerPath%"
start "" DayZServer_x64.exe -instanceId=1 -config=serverDZ.cfg -profiles=Profiles -port=2402 "-mod=" "-servermod=" -cpuCount=4 -noFilePatching -dologs -adminlog -freezecheck

goto loopServer

:updateMods
cls
for /L %%s in (%SteamCMDDelay%,-1,0) do (
    cls
    echo Checking for mod updates in %%s seconds..
    timeout 1 >nul
)
echo Updating Steam Workshop Mods...
timeout 1 >nul
(
echo login %SteamLogin%
for /f "tokens=1,2 delims=," %%g in %DayZModList% do echo workshop_download_item 221100 %%g
for /f "tokens=1,2 delims=," %%g in %DayZServerModList% do echo workshop_download_item 221100 %%g
echo quit
)>"%DayZServerPath%\steam_script.txt"
cd %SteamCMDPath%
steamcmd.exe +runscript "%DayZServerPath%\steam_script.txt"

echo Steam Workshop files are up-to-date! Syncing Workshop source with server destination...
timeout 2 >nul
cls
for /f "tokens=1,2 delims=," %%g in %DayZModList% do robocopy "%SteamCMDWorkshopPath%\%%g" "%DayZServerPath%\%%h" *.* /mir
for /f "tokens=1,2 delims=," %%g in %DayZModList% do forfiles /p "%DayZServerPath%\%%h" /m *.bikey /s /c "cmd /c copy @path %DayZServerPath%\keys"
for /f "tokens=1,2 delims=," %%g in %DayZServerModList% do robocopy "%SteamCMDWorkshopPath%\%%g" "%DayZServerPath%\%%h" *.* /mir
for /f "tokens=1,2 delims=," %%g in %DayZServerModList% do forfiles /p "%DayZServerPath%\%%h" /m *.bikey /s /c "cmd /c copy @path %DayZServerPath%\keys"
cls
echo Sync complete!
timeout 3 >nul
goto loadMods

:loadMods
cls
set "MODS_TO_LOAD="
for /f "tokens=1,2 delims=," %%g in %DayZModList% do (
    set "MODS_TO_LOAD=!MODS_TO_LOAD!%%h;"
)
set "MODS_TO_LOAD=!MODS_TO_LOAD:~0,-1!"
set "SERVERMODS_TO_LOAD="
for /f "tokens=1,2 delims=," %%g in %DayZServerModList% do (
    set "SERVERMODS_TO_LOAD=!SERVERMODS_TO_LOAD!%%h;"
)
set "SERVERMODS_TO_LOAD=!SERVERMODS_TO_LOAD:~0,-1!"
echo Will start DayZ with the following mods: !MODS_TO_LOAD!%
timeout 3 >nul
goto startServer
