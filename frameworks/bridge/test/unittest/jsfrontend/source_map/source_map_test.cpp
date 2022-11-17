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
const std::string FILESTR = "./pages/dfxtest.js";
const std::string SOURCESTR = "source.json";
const std::string NULLSTR = "";
const std::string ORIGINAL_NAME_ONE = "SourceCode:\n   RedjieRedjie002^";
const std::string ORIGINAL_NAME_TWO = "SourceCode:\n001001Wau^002";
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
 * @tc.desc: Test get original names from sourceCode which has "SourceCode:\n".
 * @tc.type: FUNC
 * @tc.require: issueI5IZXS
 */
HWTEST_F(SourceMapTest, GetOriginalNames002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Input a string which has "SourceCode:\n" as sourceCode to get original names.
     * NameMap has one elements.
     * @tc.expected: step1. Output is the same as the input string.
     */
    std::string pagemapStr = "{\"version\":3,"
                             "\"file\":\"./pages/dfxtest.js\","
                             "\"mappings\":\";\","
                             "\"sources\":[],"
                             "\"nameMap\":\"Redjie\","
                             "\"names\":[\"_ohos_router_1\",\"router\",\"_ohos_process_1\",\"process\"]}";
    std::string sourceCode = "SourceCode:\n";
    uint32_t errorPos = 0;

    RevSourceMap pageMap;
    pageMap.Init(pagemapStr);
    std::string result = pageMap.GetOriginalNames(sourceCode, errorPos);
    ASSERT_EQ(result, sourceCode);
}

/**
 * @tc.name: GetOriginalNames003
 * @tc.desc: Test get original names from sourceCode which has "SourceCode:\n".
 * @tc.type: FUNC
 */
HWTEST_F(SourceMapTest, GetOriginalNames003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Input a string which has "SourceCode:\n" as sourceCode to get original names.
     * NameMap has two elements.
     * @tc.expected: step1. Output is the same as the input string.
     */
    std::string pagemapStr = "{\"version\":3,"
                             "\"file\":\"./pages/dfxtest.js\","
                             "\"mappings\":\";\","
                             "\"sources\":[],"
                             "\"nameMap\":[\"001\",\"Redjie\"],"
                             "\"names\":[\"_ohos_router_1\",\"router\",\"_ohos_process_1\",\"process\"]}";
    std::string sourceCode = "SourceCode:\n001Redjie002^";
    uint32_t errorPos = 16;

    RevSourceMap pageMap;
    pageMap.Init(pagemapStr);
    std::string result = pageMap.GetOriginalNames(sourceCode, errorPos);
    ASSERT_EQ(result, ORIGINAL_NAME_ONE);
}

/**
 * @tc.name: GetOriginalNames004
 * @tc.desc: Test get original names from sourceCode which has "SourceCode:\n".
 * @tc.type: FUNC
 */
HWTEST_F(SourceMapTest, GetOriginalNames004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Input a string which has "SourceCode:\n" as sourceCode to get original names.
     * NameMap has two elements.
     * @tc.expected: step1. Get the original names as expected.
     */
    std::string pagemapStr = "{\"version\":3,"
                             "\"file\":\"./pages/dfxtest.js\","
                             "\"mappings\":\";\","
                             "\"sources\":[],"
                             "\"nameMap\":[\"Redjie\",\"001\"],"
                             "\"names\":[\"_ohos_router_1\",\"router\",\"_ohos_process_1\",\"process\"]}";
    std::string sourceCode = "SourceCode:\nRedjie001Wangwu^002";
    uint32_t errorPos = 13;

    RevSourceMap pageMap;
    pageMap.Init(pagemapStr);
    std::string result = pageMap.GetOriginalNames(sourceCode, errorPos);
    ASSERT_EQ(result, ORIGINAL_NAME_TWO);
}

/**
 * @tc.name: FindSourcesString001
 * @tc.desc: Test get file content when input pos is 2,2
 * @tc.type: FUNC
 */
HWTEST_F(SourceMapTest, FindSourcesString001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set row > afterRow, input a string in mappings
     * @tc.expected: step1. Get the content of file
     */
    std::string pagemapStr = "{\"version\":3,"
                             "\"file\":\"./pages/dfxtest.js\","
                             "\"mappings\":\"/A+b,\\0VAL;\","
                             "\"sources\":\"webpack:///source.json\","
                             "\"names\":[\"_ohos_router_1\",\"router\",\"_ohos_process_1\",\"process\"]}";
    int32_t row = 2;
    int32_t col = 2;

    RevSourceMap pageMap;
    pageMap.Init(pagemapStr);
    auto pageMapInfo = pageMap.Find(row, col);
    ASSERT_EQ(pageMapInfo.row, row);
    ASSERT_EQ(pageMapInfo.col, col);
    ASSERT_EQ(pageMapInfo.sources, FILESTR);

    /**
     * @tc.steps: step2. Initialize a refPtr to find the content of string
     * @tc.expected: step2. Get the content of file
     */
    auto curMapData = Referenced::MakeRefPtr<RevSourceMap>();
    pageMap.MergeInit(pagemapStr, curMapData);
    pageMapInfo = curMapData->Find(row, col);
    ASSERT_EQ(pageMapInfo.row, row);
    ASSERT_EQ(pageMapInfo.col, col);
    ASSERT_EQ(pageMapInfo.sources, FILESTR);
}

/**
 * @tc.name: FindSourcesString002
 * @tc.desc: Test get sources content when input pos is 1,1
 * @tc.type: FUNC
 */
HWTEST_F(SourceMapTest, FindSourcesString002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set row <= afterRow, input a string in mappings
     * @tc.expected: step1. Get the content of source
     */
    std::string pagemapStr = "{\"version\":3,"
                             "\"file\":\"./pages/dfxtest.js\","
                             "\"mappings\":\"V,B;QAABC,QAABC;\","
                             "\"sources\":\"webpack:///source.json\","
                             "\"names\":[\"_ohos_router_1\",\"router\",\"_ohos_process_1\",\"process\"]}";
    int32_t row = 1;
    int32_t col = 1;

    RevSourceMap pageMap;
    pageMap.Init(pagemapStr);
    auto pageMapInfo = pageMap.Find(row, col);
    ASSERT_EQ(pageMapInfo.row, row);
    ASSERT_EQ(pageMapInfo.col, col);
    ASSERT_EQ(pageMapInfo.sources, SOURCESTR);

    /**
     * @tc.steps: step2. Initialize a refPtr to find the content of string
     * @tc.expected: step2. Get the content of source
     */
    auto curMapData = Referenced::MakeRefPtr<RevSourceMap>();
    pageMap.MergeInit(pagemapStr, curMapData);
    pageMapInfo = curMapData->Find(row, col);
    ASSERT_EQ(pageMapInfo.row, row);
    ASSERT_EQ(pageMapInfo.col, col);
    ASSERT_EQ(pageMapInfo.sources, SOURCESTR);
}

/**
 * @tc.name: FindSourcesString003
 * @tc.desc: Test the input pos is wrong
 * @tc.type: FUNC
 */
HWTEST_F(SourceMapTest, FindSourcesString003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Input a wrong pos
     * @tc.expected: step1. Output is the default MappingInfo
     */
    std::string pagemapStr = "{\"version\":3,"
                             "\"file\":\"./pages/dfxtest.js\","
                             "\"mappings\":\"QAABC,QAABC;\","
                             "\"sources\":\"webpack:///source.json\","
                             "\"names\":[\"_ohos_router_1\",\"router\",\"_ohos_process_1\",\"process\"]}";
    int32_t row = 0;
    int32_t col = 0;

    RevSourceMap pageMap;
    pageMap.Init(pagemapStr);
    auto pageMapInfo = pageMap.Find(row, col);
    ASSERT_EQ(pageMapInfo.row, row);
    ASSERT_EQ(pageMapInfo.col, col);
    ASSERT_EQ(pageMapInfo.sources, NULLSTR);
}
} // namespace OHOS::Ace::Framework