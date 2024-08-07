rem Matrix-driven Appveyor CI script for synfig
rem Currently only does MSYS2 builds.
rem https://www.appveyor.com/docs/installed-software#mingw-msys-cygwin
rem Needs the following vars:
rem    MSYSTEM: MINGW64 or MINGW32

rem Set the paths appropriately
PATH C:\msys64\%MSYSTEM%\bin;C:\msys64\usr\bin;%PATH%

cd %APPVEYOR_BUILD_FOLDER%
echo %APPVEYOR_BUILD_FOLDER%
pwd

bash --login -c "$APPVEYOR_BUILD_FOLDER/1-setup-windows-msys2.sh"
bash --login -c "cd ${APPVEYOR_BUILD_FOLDER} && ./2-build-cmake.sh"
