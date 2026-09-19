@echo off
rem This script builds a project using either GCC or Visual Studio Community.

where gcc >nul 2>&1

if %errorlevel%==0 (
    echo Using GCC...

    premake5 gmake

    if "%1"=="test" (
        make config=debug tests
        bin\tests\tests.exe
    ) else (
        make config=debug prj1
        bin\prj1\prj1.exe
    )
) else (
    echo GCC not found. Using Visual Studio Community...

    premake5 vs2022

    if "%1"=="test" (
        msbuild prj.sln /p:Configuration=Debug
        bin\tests\tests.exe
    ) else (
        msbuild prj.sln /p:Configuration=Debug
        bin\prj1\prj1.exe
    )
)

where gcc >nul 2>&1

if %errorlevel%==0 (
    echo Using GCC...

    premake5 gmake

    if "%1"=="test" (
        make config=debug tests
        bin\tests\tests.exe
    ) else (
        make config=debug prj1
        bin\prj1\prj1.exe
    )
) else (
    echo GCC not found. Using Visual Studio Community...

    premake5 vs2026

    if "%1"=="test" (
        msbuild prj.sln /p:Configuration=Debug
        bin\tests\tests.exe
    ) else (
        msbuild prj.sln /p:Configuration=Debug
        bin\prj1\prj1.exe
    )
)