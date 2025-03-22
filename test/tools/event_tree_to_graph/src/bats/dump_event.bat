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
setlocal enabledelayedexpansion

hdc shell param set persist.ace.debug.enabled 1

set "ERROR_MSG=[Fail]"

for /f "delims=" %%a in ('hdc shell "hidumper -s WindowManagerService -a '-a'" 2^>^&1') do (
    hdc shell "rm %%i" > nul
)

for /f "delims=" %%a in ('hdc shell "hidumper -s WindowManagerService -a '-a'" 2^>^&1') do (
    echo %%a
    set "OUTPUT=!OUTPUT!%%a\n"
)

echo %OUTPUT% | findstr /C:"%ERROR_MSG%" >nul
if %errorlevel% equ 0 (
    exit /b 1
)

@set /p windowId=input WindowId :

for /F %%i in ('hdc shell "find data/ -name arkui.dump"') do (
    hdc shell "rm %%i"
)

hdc shell "hidumper -s WindowManagerService -a '-w %windowId% -event'" > dump_temp.txt
