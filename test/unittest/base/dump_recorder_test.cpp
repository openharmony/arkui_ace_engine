/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"

#define private public
#define protected public
#include "base/log/dump_recorder.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {} // namespace

class DumpRecorderTest : public testing::Test {
public:
    static std::unique_ptr<JsonValue> ParseJson(const std::string& jsonStr)
    {
        return JsonUtil::ParseJsonString(jsonStr);
    }
};

/**
 * @tc.name: CompareDumpParamTest001
 * @tc.desc: test CompareDumpParam when both empty objects
 * @tc.type: FUNC
 */
HWTEST_F(DumpRecorderTest, CompareDumpParamTest001, TestSize.Level1)
{
    auto curParams = ParseJson("{}");
    auto prevParams = ParseJson("{}");
    DumpRecorder recorder;
    EXPECT_TRUE(recorder.CompareDumpParam(curParams, prevParams));
}

/**
 * @tc.name: CompareDumpParamTest002
 * @tc.desc: test CompareDumpParam when skip keys only different values returnsTrue
 * @tc.type: FUNC
 */
HWTEST_F(DumpRecorderTest, CompareDumpParamTest002, TestSize.Level1)
{
    auto curParams = ParseJson(R"({"time": "now", "children": [1]})");
    auto prevParams = ParseJson(R"({"time": "then", "children": [2]})");
    DumpRecorder recorder;
    EXPECT_TRUE(recorder.CompareDumpParam(curParams, prevParams));
}

/**
 * @tc.name: CompareDumpParamTest003
 * @tc.desc: test CompareDumpParam when none skip keys match
 * @tc.type: FUNC
 */
HWTEST_F(DumpRecorderTest, CompareDumpParamTest003, TestSize.Level1)
{
    auto curParams = ParseJson(R"({"name": "Alice", "age": 30})");
    auto prevParams = ParseJson(R"({"name": "Alice", "age": 30})");
    DumpRecorder recorder;
    EXPECT_TRUE(recorder.CompareDumpParam(curParams, prevParams));
}

/**
 * @tc.name: CompareDumpParamTest004
 * @tc.desc: test CompareDumpParam when missing key in prev
 * @tc.type: FUNC
 */
HWTEST_F(DumpRecorderTest, CompareDumpParamTest004, TestSize.Level1)
{
    auto curParams = ParseJson(R"({"id": 123})");
    auto prevParams = ParseJson("{}");
    DumpRecorder recorder;
    EXPECT_FALSE(recorder.CompareDumpParam(curParams, prevParams));
}

/**
 * @tc.name: CompareDumpParamTest005
 * @tc.desc: test CompareDumpParam when value mismatch
 * @tc.type: FUNC
 */
HWTEST_F(DumpRecorderTest, CompareDumpParamTest005, TestSize.Level1)
{
    auto curParams = ParseJson(R"({"status": true})");
    auto prevParams = ParseJson(R"({"status": false})");
    DumpRecorder recorder;
    EXPECT_FALSE(recorder.CompareDumpParam(curParams, prevParams));
}

/**
 * @tc.name: CompareDumpParamTest006
 * @tc.desc: test CompareDumpParam when key empty
 * @tc.type: FUNC
 */
HWTEST_F(DumpRecorderTest, CompareDumpParamTest006, TestSize.Level1)
{
    auto curParams = ParseJson(R"({"": "invalid"})");
    auto prevParams = ParseJson(R"({"": "invalid"})");
    DumpRecorder recorder;
    EXPECT_FALSE(recorder.CompareDumpParam(curParams, prevParams));
}

/**
 * @tc.name: CompareDumpParamTest007
 * @tc.desc: test CompareDumpParam when mixed keys with none skip mismatch
 * @tc.type: FUNC
 */
HWTEST_F(DumpRecorderTest, CompareDumpParamTest007, TestSize.Level1)
{
    auto curParams = ParseJson(R"({"time": "now", "mode": "A"})");
    auto prevParams = ParseJson(R"({"time": "then", "mode": "B"})");
    DumpRecorder recorder;
    EXPECT_FALSE(recorder.CompareDumpParam(curParams, prevParams));
}

/**
 * @tc.name: CompareDumpParamTest008
 * @tc.desc: test CompareDumpParam when extra keys in prev ignores extra
 * @tc.type: FUNC
 */
HWTEST_F(DumpRecorderTest, CompareDumpParamTest008, TestSize.Level1)
{
    auto curParams = ParseJson(R"({"size": 10})");
    auto prevParams = ParseJson(R"({"size": 10, "color": "red"})");
    DumpRecorder recorder;
    EXPECT_TRUE(recorder.CompareDumpParam(curParams, prevParams));
}

/**
 * @tc.name: CompareDumpParamTest009
 * @tc.desc: test CompareDumpParam when different value types to string mismatch
 * @tc.type: FUNC
 */
HWTEST_F(DumpRecorderTest, CompareDumpParamTest009, TestSize.Level1)
{
    auto curParams = ParseJson(R"({"count": 5})");
    auto prevParams = ParseJson(R"({"count": "5"})");
    DumpRecorder recorder;
    EXPECT_FALSE(recorder.CompareDumpParam(curParams, prevParams));
}

/**
 * @tc.name: CompareDumpParamTest010
 * @tc.desc: test CompareDumpParam when null prev param value
 * @tc.type: FUNC
 */
HWTEST_F(DumpRecorderTest, CompareDumpParamTest010, TestSize.Level1)
{
    auto curParams = ParseJson(R"({"valid": true})");
    auto prevParams = ParseJson("{}");
    DumpRecorder recorder;
    EXPECT_FALSE(recorder.CompareDumpParam(curParams, prevParams));
}

/**
 * @tc.name: CompareDumpParamTest011
 * @tc.desc: test CompareDumpParam when same unicode characters
 * @tc.type: FUNC
 */
HWTEST_F(DumpRecorderTest, CompareDumpParamTest011, TestSize.Level1)
{
    auto curParams = ParseJson(R"({"text": "中文 Español Français 🌍"})");
    auto prevParams = ParseJson(R"({"text": "中文 Español Français 🌍"})");
    DumpRecorder recorder;
    EXPECT_TRUE(recorder.CompareDumpParam(curParams, prevParams));
}

/**
 * @tc.name: CompareDumpParamTest012
 * @tc.desc: test CompareDumpParam when different unicode characters
 * @tc.type: FUNC
 */
HWTEST_F(DumpRecorderTest, CompareDumpParamTest012, TestSize.Level1)
{
    auto curParams = ParseJson(R"({"text": "中文 Español Français 🌍     "})");
    auto prevParams = ParseJson(R"({"text": "中文 Español Français 🌍"})");
    DumpRecorder recorder;
    EXPECT_FALSE(recorder.CompareDumpParam(curParams, prevParams));
}

/**
 * @tc.name: CompareDumpParamTest013
 * @tc.desc: test CompareDumpParam when special characters
 * @tc.type: FUNC
 */
HWTEST_F(DumpRecorderTest, CompareDumpParamTest013, TestSize.Level1)
{
    auto curParams = ParseJson(R"({"key!@#$%^&*": "value"})");
    auto prevParams = ParseJson(R"({"key!@#$%^&*": "value"})");
    DumpRecorder recorder;
    EXPECT_TRUE(recorder.CompareDumpParam(curParams, prevParams));
}

/**
 * @tc.name: CompareDumpParamTest014
 * @tc.desc: test CompareDumpParam when same complex nested structures
 * @tc.type: FUNC
 */
HWTEST_F(DumpRecorderTest, CompareDumpParamTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create cur JsonValue with complex nested structures
     */
    auto curParams = ParseJson(R"({
        "user": {
            "id": 123,
            "name": "Alice",
            "preferences": {
                "theme": "dark",
                "notifications": true
            },
            "children": ["Bob", "Charlie"]
        },
        "timestamp": 1620000000
    })");
    
    /**
     * @tc.steps: step2. Create prev JsonValue with same complex nested structures
     */
    auto prevParams = ParseJson(R"({
        "user": {
            "id": 123,
            "name": "Alice",
            "preferences": {
                "theme": "dark",
                "notifications": true
            },
            "children": ["Bob", "Charlie"]
        },
        "timestamp": 1620000000
    })");
    
    /**
     * @tc.steps: step3. Test CompareDumpParam with cur JsonValue and prev JsonValue.
     */
    DumpRecorder recorder;
    EXPECT_TRUE(recorder.CompareDumpParam(curParams, prevParams));
}

/**
 * @tc.name: CompareDumpParamTest015
 * @tc.desc: test CompareDumpParam when different complex nested structures
 * @tc.type: FUNC
 */
HWTEST_F(DumpRecorderTest, CompareDumpParamTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create cur JsonValue with complex nested structures
     */
    auto curParams = ParseJson(R"({
        "config": {
            "version": 1,
            "settings": {
                "timeout": 30,
                "retries": 3
            }
        }
    })");
    
    /**
     * @tc.steps: step2. Create prev JsonValue with retries different
     */
    auto prevParams = ParseJson(R"({
        "config": {
            "version": 1,
            "settings": {
                "timeout": 30,
                "retries": 5
            }
        }
    })");
    
    /**
     * @tc.steps: step3. Test CompareDumpParam with cur JsonValue and prev JsonValue.
     */
    DumpRecorder recorder;
    EXPECT_FALSE(recorder.CompareDumpParam(curParams, prevParams));
}

/**
 * @tc.name: CompareDumpParamTest016
 * @tc.desc: test CompareDumpParam when different key order but same values
 * @tc.type: FUNC
 */
HWTEST_F(DumpRecorderTest, CompareDumpParamTest016, TestSize.Level1)
{
    auto curParams = ParseJson(R"({"a": 1, "b": 2, "c": 3})");
    auto prevParams = ParseJson(R"({"c": 3, "b": 2, "a": 1})");
    DumpRecorder recorder;
    EXPECT_TRUE(recorder.CompareDumpParam(curParams, prevParams));
}
} // namespace OHOS::Ace