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

echo.
echo Please enter the window ID which is to be dumped.
hdc shell "hidumper -s WindowManagerService -a '-a'"

echo.
set /p "windowId=please enter the window ID: "

echo UI dump generate...
hdc shell "hidumper -s WindowManagerService -a '-w %windowId% -event -c'" > %windowId%_event.txt

if exist .\%windowId%_event.txt (
    echo file saved as: %cd%\%windowId%_event.txt
    echo .\%windowId%_event.txt > generated_file_path.txt
) else (
    echo err: failed
)
goto :success

echo Error
exit /b 1

:success
echo.
echo done!