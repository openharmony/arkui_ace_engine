/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "component_test/test_result_recorder.h"

#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <vector>

#include "base/json/json_util.h"
#include "base/log/log.h"
#include "core/common/task_runner_adapter_factory.h"

namespace OHOS::Ace::ComponentTest {

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
const std::string file_sep = "\\";
#else
const std::string file_sep = "/";
#endif

int CreateDirectories(const std::string& filePath)
{
    int result = 0;
#ifdef _WIN32
    result = mkdir(filePath.data());
#else
    result = mkdir(filePath.data(), S_IRUSR | S_IWUSR | S_IXUSR);
#endif
    return result;
}

int FileExists(const std::string& path)
{
    std::ofstream outFile(path);
    if (!outFile.is_open()) {
        return 1;
    }
    return 0;
}

std::vector<std::string> SplitString(const std::string& outPath)
{
    auto p = file_sep + file_sep;
    std::regex delimiter(p);
    std::sregex_token_iterator iter(outPath.begin(), outPath.end(), delimiter, -1);
    std::sregex_token_iterator end;
    std::vector<std::string> tokens;
    while (iter != end) {
        tokens.push_back(*iter++);
    }
    return tokens;
}

std::string GetCurrentTime()
{
    std::chrono::time_point<std::chrono::system_clock, std::chrono::microseconds> tpMicro =
        std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now());
    time_t totalMicroSeconds = tpMicro.time_since_epoch().count();
    return std::to_string(totalMicroSeconds);
}

std::string HandleRelativeFolder(std::string& folderPath)
{
    std::string resultPath;
    std::string relativePath;
    std::string currentPath;
    char tmp[PATH_MAX];
    if (getcwd(tmp, sizeof(tmp)) == NULL) {
        LOGE("get current directory failed!");
    } else {
        currentPath = std::string(tmp);
    }
    auto pos = folderPath.rfind("..");
    if (pos != std::string::npos) {
        std::string currentPathAfterSplit;
        std::vector<std::string> splitInputResult = SplitString(folderPath);
        int count = 0;
        for (const auto& i : splitInputResult) {
            if (i == "..") {
                count++;
            } else {
                relativePath += file_sep + i;
            }
        }
        std::vector<std::string> splitCurrentPathResult = SplitString(currentPath);
        for (std::size_t i = 0; i < splitCurrentPathResult.size() - count; i++) {
            currentPathAfterSplit += splitCurrentPathResult[i] + file_sep;
        }
        resultPath = currentPathAfterSplit + relativePath.substr(1, relativePath.size() - 1);
    } else {
        auto beginWithDot = folderPath.find(".") == 0;
        if (!beginWithDot) {
            resultPath = currentPath + file_sep + folderPath;
        } else {
            auto path = folderPath.substr(1, folderPath.size() - 1);
            resultPath = currentPath + file_sep + path;
        }
    }
    return resultPath;
}

std::string HandleAbsoluteFolder(std::string& folderPath)
{
    std::string disk;
    std::string resultPath;
    size_t pos = folderPath.find(file_sep);
    if (pos != std::string::npos) {
        disk = folderPath.substr(0, pos);
    }
    resultPath = disk;
    std::vector<std::string> result = SplitString(folderPath);
    for (std::size_t i = 1; i < result.size(); i++) {
        resultPath += file_sep + result[i];
    }
    return resultPath;
}

void TestResultRecorder::Initialize(const std::string& out)
{
    testRecord_.result = Result::ERROR;
    testRecord_.info = "Component test terminated unexpectedly";
    testRecord_.position = "Unknown";
    outPath_ = out;
    if (outPath_ == "") {
        return;
    }
    std::string absolutePath;
    std::string resultPath;
    auto isAbsolute = outPath_.find(":") == std::string::npos;
    if (!isAbsolute) {
        absolutePath = HandleAbsoluteFolder(outPath_);
    } else {
        absolutePath = HandleRelativeFolder(outPath_);
    }
    std::string disk;
    size_t pos = absolutePath.find(file_sep);
    if (pos != std::string::npos) {
        disk = absolutePath.substr(0, pos);
    }
    resultPath = disk;
    std::vector<std::string> result = SplitString(absolutePath);
    for (std::size_t i = 1; i < result.size(); i++) {
        resultPath += file_sep + result[i];
        bool isDir = resultPath.find(".json") == std::string::npos;
        if (isDir) {
            CreateDirectories(resultPath);
            if (i == (result.size() - 1)) {
                const std::string fileName = GetCurrentTime();
                resultPath += file_sep + fileName + ".json";
            }
        }
        if (FileExists(resultPath) != 0) {
            LOGE("File \"%{public}s\" not exist", resultPath.c_str());
        }
    }
    outPath_ = resultPath;
}

void TestResultRecorder::WriteJson()
{
    auto jsonNode = JsonUtil::Create(true);
    auto jsonDetail = JsonUtil::Create(true);
    for (auto i : testRecord_.assertResults) {
        auto jSingle = JsonUtil::Create(true);
        jSingle->Put("position", i.position.c_str());
        jSingle->Put("result", i.GetTestCaseResultString().c_str());
        jSingle->Put("message", i.info.c_str());
        jsonDetail->Put(jSingle);
    }
    jsonNode->Put("test_case_name", attr_.GetTestCaseName().c_str());
    jsonNode->Put("test_case_type", attr_.GetTestCaseTypeString().c_str());
    jsonNode->Put("test_case_size", attr_.GetTestCaseSizeString().c_str());
    jsonNode->Put("test_case_level", attr_.GetTestCaseLevelString().c_str());
    jsonNode->Put("message", testRecord_.info.c_str());
    jsonNode->Put("result", testRecord_.result);
    if (testRecord_.result > 0) {
        jsonNode->Put("error_position", testRecord_.position.c_str());
    }
    jsonNode->Put("details", jsonDetail);
    std::string str = jsonNode->ToString();
    if (outPath_ != "") {
        std::fstream file;
        file.open(outPath_, std::ios::in | std::ios::out | std::ios::trunc);
        if (file.is_open()) {
            file << str << std::endl;
            file.close();
        } else {
            LOGE("open file failed");
        }
    } else {
        LOGI("Json Result: %{public}s", str.c_str());
    }
}

void TestResultRecorder::Record(const std::string& info, const std::string& position, Result result)
{
    if (result != Result::PASS) {
        testRecord_.info = info;
        testRecord_.result = result;
        testRecord_.position = position;
    }
    testRecord_.assertResults.emplace_back(AssertResult { position, result, info });
    WriteJson();
}

void TestResultRecorder::Finish()
{
    if (testRecord_.assertResults.empty()) {
        testRecord_.result = Result::PASS;
        testRecord_.info = "";
        testRecord_.position = "";
    } else {
        auto last = testRecord_.assertResults.back();
        if (last.result == Result::PASS) {
            testRecord_.info = "";
            testRecord_.position = "";
        } else {
            testRecord_.info = last.info;
            testRecord_.position = last.position;
        }
        testRecord_.result = last.result;
    }
    WriteJson();
}
} // namespace OHOS::Ace::ComponentTest
