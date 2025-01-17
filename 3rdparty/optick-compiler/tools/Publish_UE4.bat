@echo off
setlocal enabledelayedexpansion

cd ..

rem call generate_projects.gpu.bat

rem MsBuild build/vs2017/Optick.sln /t:OptickCore:Rebuild /p:Configuration=Debug /p:Platform=x64
rem MsBuild build/vs2017/Optick.sln /t:Samples\ConsoleApp:Rebuild /p:Configuration=Release /p:Platform=x64
rem MsBuild gui/OptickApp_vs2017.sln /t:Rebuild /p:Configuration=Release /p:Platform=x64

for /f %%i in ('powershell "(Get-Item -path Bin\Release\x64\Optick.exe).VersionInfo.ProductVersion"') do set VERSION=%%i

set UNREAL_VERSION=4.23
set VERSION_NAME=%VERSION:~0,-2%_UE4Plugin%UNREAL_VERSION%

xcopy /Y Bin\Release\x64\Optick.exe samples\UnrealEnginePlugin\GUI\*

call "C:\Program Files\Epic Games\UE_%UNREAL_VERSION%\Engine\Build\BatchFiles\RunUAT.bat" BuildPlugin -Plugin="%CD%\samples\UnrealEnginePlugin\OptickPlugin.uplugin" -Package="%CD%\publish\Optick_%VERSION_NAME%\OptickPlugin" -Rocket

rem Process Copyright
cd %CD%\publish\Optick_%VERSION_NAME%\OptickPlugin\Source\Private\OptickCore\

if not exist "tmp" mkdir tmp

for %%f in (*.cpp *.h) do (
   (Echo "%%f" | FIND /I "miniz" 1>NUL) || (
	   echo // Copyright(c^) 2019 Vadim Slyusarev > "tmp\%%f"
       more +21 "%%f" >> "tmp\%%f"
   )
)

xcopy /Y tmp\*.* *

del /Q tmp\*.*
rmdir tmp

cd ..\..\..\..\..\..

rem Compress Archive
powershell "Compress-Archive -Path \"%CD%\publish\Optick_%VERSION_NAME%\*\" -DestinationPath \"%CD%\publish\Optick_%VERSION_NAME%.zip\""

cd tools