:: Copyright (c) 2024 Huawei Device Co., Ltd.
:: Licensed under the Apache License, Version 2.0 (the "License");
:: you may not use this file except in compliance with the License.
:: You may obtain a copy of the License at
::
::  http://www.apache.org/licenses/LICENSE-2.0
::
:: Unless required by applicable law or agreed to in writing, software
:: distributed under the License is distributed on an "AS IS" BASIS,
:: WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
:: See the License for the specific language governing permissions and
:: limitations under the License.

@echo off

@rem Set local scope for the variables with windows NT shell
if "%OS%"=="Windows_NT" setlocal

set DIRNAME=%~dp0
if "%DIRNAME%" == "" set DIRNAME=.
set APP_BASE_NAME=%~n0
set APP_HOME=%DIRNAME%

goto start

:start
adb devices | findstr /i "device" > nul
if %errorlevel%==0 (
    goto execute
) else (
    echo.
    echo Error: No device found.
    echo.
    goto fail
)

:execute
@echo off
@rem Replace here with hdc command
adb devices

echo.
echo Please enter the window ID which is to be dumped.
echo.
set /p userInput="please enter the window ID:"

adb shell "dumpsys window windows | grep -E %userInput%" > window_id.txt

:fail
exit /b 1