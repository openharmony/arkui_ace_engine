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

#ifndef OHOS_ACE_COMPONENT_TEST_RESULT_RECORDER_H
#define OHOS_ACE_COMPONENT_TEST_RESULT_RECORDER_H

#include <string>
#include <vector>

#include "core/common/task_runner_adapter.h"

namespace OHOS::Ace::ComponentTest {
enum Result : int {
    PASS = 0,
    FAIL,
    ERROR,
};

const std::string TEST_CASE_RESULTS[] = {
    "Pass",
    "Fail",
    "Error",
};

enum TestCaseType : int {
    FUNCTION = 0,
    PERFORMANCE,
    POWER,
    RELIABILITY,
    SECURITY,
    GLOBAL,
    COMPATIBILITY,
    USER,
    STANDARD,
    SAFETY,
    RESILIENCE,
    INVALID_TYPE,
};

const std::string TEST_CASE_TYPE_STRINGS[] = {
    "FUNCTION",
    "PERFORMANCE",
    "POWER",
    "RELIABILITY",
    "SECURITY",
    "GLOBAL",
    "COMPATIBILITY",
    "USER",
    "STANDARD",
    "SAFETY",
    "RESILIENCE",
};

enum TestCaseSize : int {
    SMALLTEST = 0,
    MEDIUMTEST,
    LARGETEST,
    INVALID_SIZE,
};

const std::string TEST_CASE_SIZE_STRINGS[] = {
    "SMALLTEST",
    "MEDIUMTEST",
    "LARGETEST",
};

enum TestCaseLevel : int {
    LEVEL0 = 0,
    LEVEL1,
    LEVEL2,
    LEVEL3,
    LEVEL4,
    INVALID_LEVEL,
};

const std::string TEST_CASE_LEVEL_STRINGS[] = {
    "LEVEL0",
    "LEVEL1",
    "LEVEL2",
    "LEVEL3",
    "LEVEL4",
};

class TestCaseAttribute {
public:
    TestCaseAttribute() = default;
    TestCaseAttribute(
        std::string testCaseName, TestCaseType testCaseType, TestCaseSize testCaseSize, TestCaseLevel testCaseLevel)
        : testCaseName_(testCaseName), testCaseType_(testCaseType), testCaseSize_(testCaseSize),
          testCaseLevel_(testCaseLevel)
    {}

    std::string GetTestCaseName() const
    {
        return testCaseName_;
    }

    std::string GetTestCaseTypeString() const
    {
        return TEST_CASE_TYPE_STRINGS[testCaseType_];
    }

    std::string GetTestCaseSizeString() const
    {
        return TEST_CASE_SIZE_STRINGS[testCaseSize_];
    }

    std::string GetTestCaseLevelString() const
    {
        return TEST_CASE_LEVEL_STRINGS[testCaseLevel_];
    }

private:
    std::string testCaseName_;
    TestCaseType testCaseType_;
    TestCaseSize testCaseSize_;
    TestCaseLevel testCaseLevel_;
};

class AssertResult {
public:
    std::string position;
    Result result;
    std::string info;
    std::string GetTestCaseResultString() const
    {
        return TEST_CASE_RESULTS[result];
    }
};

class TestRecordParam {
public:
    std::string info;
    AssertResult assertResult;
};

class TestRecord {
public:
    std::string info;
    Result result;
    std::string position;
    std::vector<AssertResult> assertResults;
};

class TestResultRecorder {
public:
    void Initialize(const std::string& out);
    void Record(const std::string& info, const std::string& position, Result result);
    void Finish();
    void SetTestCaseAttribute(TestCaseAttribute attribute)
    {
        attr_ = attribute;
        WriteJson();
    }

private:
    TestCaseAttribute attr_;
    TestRecord testRecord_;
    std::string outPath_;
    void WriteJson();
};
} // namespace OHOS::Ace::ComponentTest

#endif // OHOS_ACE_COMPONENT_TEST_RESULT_RECORDER_H
