/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/common/utils/source_map.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::Framework {
namespace {
} // namespace

class SourceMapTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void SourceMapTest::SetUpTestCase() {}
void SourceMapTest::TearDownTestCase() {}
void SourceMapTest::SetUp() {}
void SourceMapTest::TearDown() {}

/**
 * @tc.name: GetOriginalNames001
 * @tc.desc: Test get original names from sourceCode which is empty string.
 * @tc.type: FUNC
 * @tc.require: issueI5IZXS
 */
HWTEST_F(SourceMapTest, GetOriginalNames001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Input an empty string as sourceCode to get original names.
     * @tc.expected: step1. Output is still an empty string.
     */
    std::string pagemapStr = "{\"version\":3,"
                             "\"file\":\"./pages/dfxtest.js\","
                             "\"mappings\":\";\","
                             "\"sources\":[],"
                             "\"names\":[\"_ohos_router_1\",\"router\",\"_ohos_process_1\",\"process\"]}";
    std::string sourceCode = "";
    uint32_t errorPos = 0;

    RevSourceMap pageMap;
    pageMap.Init(pagemapStr);
    std::string result = pageMap.GetOriginalNames(sourceCode, errorPos);
    ASSERT_EQ(result, sourceCode);
}

/**
 * @tc.name: GetOriginalNames002
 * @tc.desc: Test get original names from sourceCode which doesn't have "SourceCode:\n".
 * @tc.type: FUNC
 * @tc.require: issueI5IZXS
 */
HWTEST_F(SourceMapTest, GetOriginalNames002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Input a string which doesn't have "SourceCode:\n" as sourceCode to get original names.
     * @tc.expected: step1. Output is the same as the input string.
     */
    std::string pagemapStr = "{\"version\":3,"
                             "\"file\":\"./pages/dfxtest.js\","
                             "\"mappings\":\";\","
                             "\"sources\":[],"
                             "\"names\":[\"_ohos_router_1\",\"router\",\"_ohos_process_1\",\"process\"]}";
    std::string sourceCode = "sourceCode";
    uint32_t errorPos = 0;

    RevSourceMap pageMap;
    pageMap.Init(pagemapStr);
    std::string result = pageMap.GetOriginalNames(sourceCode, errorPos);
    ASSERT_EQ(result, sourceCode);
}
} // namespace OHOS::Ace::Framework