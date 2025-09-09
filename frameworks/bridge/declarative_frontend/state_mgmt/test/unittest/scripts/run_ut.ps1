
#  * Copyright (c) 2025 Huawei Device Co., Ltd.
#  * Licensed under the Apache License, Version 2.0 (the "License");
#  * you may not use this file except in compliance with the License.
#  * You may obtain a copy of the License at
#  *
#  *     http://www.apache.org/licenses/LICENSE-2.0
#  *
#  * Unless required by applicable law or agreed to in writing, software
#  * distributed under the License is distributed on an "AS IS" BASIS,
#  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  * See the License for the specific language governing permissions and
#  * limitations under the License.



# Use hdc from PATH
# Use debug option to show all logs.

$localHap = "./StateMgmtTest.hap"

# Resolve full paths for clarity (only if the file exists)
if (Test-Path $localHap) {
    $resolvedLocal = Resolve-Path $localHap
    Write-Host "Installing HAP from current directory: '$resolvedLocal'"
    hdc install -r $resolvedLocal
}
else {
    Write-Host "No .hap found in current folder."
    exit 1
}

Write-Host "Starting log capture to temporary file..."

# Start logging to temp file
$logFile = "temp_log.txt"
$proc = Start-Process hdc -ArgumentList 'hilog -r' -NoNewWindow -RedirectStandardOutput $logFile -PassThru
hdc shell aa start -a EntryAbility -b com.ohos.state_mgmt_ut
Write-Host "Logging started (PID $($proc.Id)), waiting 3 seconds..."
Start-Sleep -Seconds 3

Write-Host "Stopping log capture..."
Stop-Process -Id $proc.Id -Force

Write-Host "Processing captured log..."

# Check input args
if ($args.Count -eq 0 -or $args[0] -eq "simple") {
    Write-Host "Showing lines containing '__ut':"
    Get-Content $logFile | Select-String '__ut'
}
elseif ($args[0] -eq "debug") {
    Write-Host "Showing all log lines (debug mode):"
    Get-Content $logFile
}
else {
    Write-Host "Unknown argument. Use: simple, debug, or no argument."
}

# Clean up
Write-Host " Cleaning up temporary log file..."
Remove-Item $logFile

Write-Host "Done!"
