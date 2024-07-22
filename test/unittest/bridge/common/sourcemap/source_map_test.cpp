/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "base/memory/ace_type.h"
#include "frameworks/bridge/common/utils/source_map.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::Framework {
class SourceMapTest : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
};

/**
 * @tc.name: SourceMapTest001
 * @tc.desc: Find()
 * @tc.type: FUNC
 */
HWTEST_F(SourceMapTest, SourceMapTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a revSourceMap.
     */
    RevSourceMap revSourceMap;
    int32_t row = 0;
    int32_t col = 0;
    bool isColPrecise = false;
    revSourceMap.files_.emplace_back("files");

    /**
     * @tc.steps: step2. Testing values.
     * @tc.expected: return mappingInfo.
     */
    auto mappingInfo = revSourceMap.Find(row, col, isColPrecise); // 47line if 1、1、1
    EXPECT_EQ(mappingInfo.col, 0);
    row = 5;
    mappingInfo = revSourceMap.Find(row, col, isColPrecise); // 47line if 0、1、1
    EXPECT_EQ(mappingInfo.col, 0);
    col = 1;
    mappingInfo = revSourceMap.Find(row, col, isColPrecise); // 47line if 0、0、1
    EXPECT_EQ(mappingInfo.col, 0);
    SourceMapInfo sourceMapInfo;
    revSourceMap.afterPos_.emplace_back(sourceMapInfo);
    mappingInfo = revSourceMap.Find(row, col, isColPrecise); // 47line if 0、0、0 57line if 1
    EXPECT_EQ(mappingInfo.col, 1);
    revSourceMap.afterPos_.emplace_back(SourceMapInfo { 0, 0, 5, 0, 0, 0 });
    mappingInfo = revSourceMap.Find(row, col, isColPrecise); // 47line if 0、0、0 57line if 0 62line 0、0、0
    EXPECT_EQ(mappingInfo.col, 0);
    revSourceMap.afterPos_.clear();
    revSourceMap.afterPos_.emplace_back(SourceMapInfo { 0, 0, 5, 1, 0, 0 }); // 62line 0、1、1
    mappingInfo = revSourceMap.Find(row, col, isColPrecise);
    EXPECT_EQ(mappingInfo.col, 0);
    revSourceMap.afterPos_.clear();
    revSourceMap.afterPos_.emplace_back(SourceMapInfo { 0, 0, 4, 1, 0, 0 }); // 62line 1、1、0
    mappingInfo = revSourceMap.Find(row, col, isColPrecise);
    EXPECT_EQ(mappingInfo.col, 0);
}

/**
 * @tc.name: SourceMapTest002
 * @tc.desc: Find()
 * @tc.type: FUNC
 */
HWTEST_F(SourceMapTest, SourceMapTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a revSourceMap.
     */
    RevSourceMap revSourceMap;
    int32_t row = 0;
    int32_t col = 0;
    bool isColPrecise = true;
    revSourceMap.files_.emplace_back("files");

    /**
     * @tc.steps: step2. Testing values.
     * @tc.expected: return mappingInfo.
     */
    row = 5;
    col = 5;
    revSourceMap.afterPos_.emplace_back(SourceMapInfo { 0, 0, 5, 1, 0, 0 });
    revSourceMap.afterPos_.emplace_back(SourceMapInfo { 0, 0, 3, 1, 0, 0 });
    revSourceMap.afterPos_.emplace_back(SourceMapInfo { 0, 0, 4, 1, 0, 0 });
    auto mappingInfo = revSourceMap.Find(row, col, isColPrecise); // 79line 0、0、 1、0
    EXPECT_EQ(mappingInfo.col, 0);
    isColPrecise = false;
    mappingInfo = revSourceMap.Find(row, col, isColPrecise); // 79line 1、0、 1、0
    EXPECT_EQ(mappingInfo.col, 0);
    col = 1;
    mappingInfo = revSourceMap.Find(row, col, isColPrecise); // 79line 1、1、 1、 1 83line 0、1
    EXPECT_EQ(mappingInfo.col, 0);
    revSourceMap.afterPos_[2].sourcesVal = -1;
    mappingInfo = revSourceMap.Find(row, col, isColPrecise); // 83line 1、0
    EXPECT_EQ(mappingInfo.col, 0);
    revSourceMap.afterPos_[2].sourcesVal = 0;
    revSourceMap.sources_.emplace_back("0");
    revSourceMap.sources_.emplace_back("1");
    mappingInfo = revSourceMap.Find(row, col, isColPrecise); // 89line 0
    EXPECT_EQ(mappingInfo.col, 1);
    revSourceMap.sources_[0] = ("webpack:///111");
    mappingInfo = revSourceMap.Find(row, col, isColPrecise); // 89line 1
    EXPECT_EQ(mappingInfo.col, 1);
}

/**
 * @tc.name: SourceMapTest003
 * @tc.desc: GetOriginalNames()
 * @tc.type: FUNC
 */
HWTEST_F(SourceMapTest, SourceMapTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a revSourceMap.
     */
    RevSourceMap revSourceMap;
    std::string sourceCode;
    uint32_t errorPos = 0;
    /**
     * @tc.steps: step2. Testing values.
     * @tc.expected: return sourceCode.
     */
    EXPECT_EQ(revSourceMap.GetOriginalNames(sourceCode, errorPos), sourceCode);
    sourceCode = "test";
    EXPECT_EQ(revSourceMap.GetOriginalNames(sourceCode, errorPos), sourceCode);
    sourceCode = "SourceCode:\n test";
    EXPECT_EQ(revSourceMap.GetOriginalNames(sourceCode, errorPos), sourceCode);
    revSourceMap.nameMap_.emplace_back("0");
    EXPECT_EQ(revSourceMap.GetOriginalNames(sourceCode, errorPos), sourceCode);
    revSourceMap.nameMap_.emplace_back("test");
    revSourceMap.nameMap_.emplace_back("SourceCode");
    revSourceMap.nameMap_.emplace_back("Code");
    EXPECT_EQ(revSourceMap.GetOriginalNames(sourceCode, errorPos), "Code:\n test");
    errorPos = 10;
    EXPECT_EQ(revSourceMap.GetOriginalNames(sourceCode, errorPos), "Code:\n test");
    sourceCode = "SourceCode:\n";
    EXPECT_EQ(revSourceMap.GetOriginalNames(sourceCode, errorPos), "Code:\n");
}

/**
 * @tc.name: SourceMapTest004
 * @tc.desc: ExtractKeyInfo() and Init()
 * @tc.type: FUNC
 */
HWTEST_F(SourceMapTest, SourceMapTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a revSourceMap.
     */
    RevSourceMap revSourceMap;
    std::string sourceMap;
    revSourceMap.Init(sourceMap);
    EXPECT_TRUE(revSourceMap.mappings_.empty());
    /**
     * @tc.steps: step2. Testing values.
     * @tc.expected: return revSourceMap.mappings_.size() = 0.
     */
    sourceMap = "\"test\"\"sources\"\"./pag\\es\""
                "\"names\"\"dfxtest\""
                "\"mappings\"\"test123AB+B,B;test2BBBB,test3B\""
                "\"file\"\"dfxtest.js\""
                "\"nameMap\"\"testMap\""
                "\"sourceContent\"\"conent\""
                "\"sourceRoot\"\"root\"";
    revSourceMap.Init(sourceMap);
    EXPECT_EQ(revSourceMap.mappings_.size(), 0);
}

/**
 * @tc.name: SourceMapTest005
 * @tc.desc: ExtractKeyInfo() and Init()
 * @tc.type: FUNC
 */
HWTEST_F(SourceMapTest, SourceMapTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a revSourceMap.
     */
    RevSourceMap revSourceMap;
    std::string sourceMap;
    revSourceMap.Init(sourceMap);
    EXPECT_TRUE(revSourceMap.mappings_.empty());
    /**
     * @tc.steps: step2. Testing values.
     * @tc.expected: return revSourceMap.mappings_.size() = 1.
     */
    sourceMap = "\"test\"\"sources\"\"./pag\\es\""
                "\"names\"\"dfxtest\""
                "\"mappings\"\"test123AB+\""
                "\"file\"\"dfxtest.js\""
                "\"nameMap\"\"testMap\""
                "\"sourceContent\"\"conent\""
                "\"sourceRoot\"\"root\"";
    revSourceMap.Init(sourceMap);
    EXPECT_EQ(revSourceMap.mappings_.size(), 1);
}

/**
 * @tc.name: SourceMapTest006
 * @tc.desc: ExtractKeyInfo() and MergeInit()
 * @tc.type: FUNC
 */
HWTEST_F(SourceMapTest, SourceMapTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a revSourceMap.
     */
    RevSourceMap revSourceMap;
    std::string sourceMap;
    RefPtr<RevSourceMap> curMapData = AceType::MakeRefPtr<RevSourceMap>();
    revSourceMap.MergeInit(sourceMap, curMapData);
    EXPECT_TRUE(curMapData->mappings_.empty());
    /**
     * @tc.steps: step2. Testing values.
     * @tc.expected: return curMapData.mappings_.size() = 1.
     */
    sourceMap = "\"test\"\"sources\"\"./pag\\es\""
                "\"names\"\"dfxtest\""
                "\"mappings\"\"test123AB+B,B;test2BBBB,test3B\""
                "\"file\"\"dfxtest.js\""
                "\"nameMap\"\"testMap\""
                "\"sourceContent\"\"conent\""
                "\"sourceRoot\"\"root\"";
    revSourceMap.MergeInit(sourceMap, curMapData);
    EXPECT_EQ(curMapData->mappings_.size(), 0);
}

/**
 * @tc.name: SourceMapTest007
 * @tc.desc: ExtractKeyInfo() and MergeInit()
 * @tc.type: FUNC
 */
HWTEST_F(SourceMapTest, SourceMapTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a revSourceMap.
     */
    RevSourceMap revSourceMap;
    std::string sourceMap;
    RefPtr<RevSourceMap> curMapData = AceType::MakeRefPtr<RevSourceMap>();
    /**
     * @tc.steps: step2. Testing values.
     * @tc.expected: return curMapData.mappings_.size() = 1.
     */
    sourceMap = "\"test\"\"sources\"\"./pag\\es\""
                "\"names\"\"dfxtest\""
                "\"mappings\"\"test123AB+\""
                "\"file\"\"dfxtest.js\""
                "\"nameMap\"\"testMap\""
                "\"sourceContent\"\"conent\""
                "\"sourceRoot\"\"root\"";
    revSourceMap.MergeInit(sourceMap, curMapData);
    EXPECT_EQ(curMapData->mappings_.size(), 1);
}

/**
 * @tc.name: SourceMapTest008
 * @tc.desc: StageModeSourceMapSplit()
 * @tc.type: FUNC
 */
HWTEST_F(SourceMapTest, SourceMapTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a revSourceMap.
     */
    RevSourceMap revSourceMap;
    std::string sourceMap;
    std::unordered_map<std::string, RefPtr<RevSourceMap>> sourceMaps;
    /**
     * @tc.steps: step2. Testing values.
     * @tc.expected: return curMapData.mappings_.size() = 1.
     */
    sourceMap = "\"test\": {\"sources\": [test],[test1]}\"./pag\\es\""
                "\"names\"\"dfxtest\""
                "\"mappings\"\"test123AB+\""
                "\"file\"\"dfxtest.js\""
                "\"nameMap\"\"testMap\""
                "\"sourceContent\"\"conent\""
                "\"sourceRoot\"\"root\"";
    revSourceMap.StageModeSourceMapSplit(sourceMap, sourceMaps);
    EXPECT_EQ(sourceMaps.size(), 1);
}

/**
 * @tc.name: SourceMapTest009
 * @tc.desc: GetOriginalNames()
 * @tc.type: FUNC
 */
HWTEST_F(SourceMapTest, SourceMapTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct posDiff > 0,lineBreakPos + 1 < jsCode.length() - 1 is true
     */
    RevSourceMap revSourceMap;
    revSourceMap.nameMap_.push_back("param1");
    revSourceMap.nameMap_.push_back("param111");
    revSourceMap.nameMap_.push_back("param2");
    revSourceMap.nameMap_.push_back("param222");
    std::string sourceCode = "SourceCode:\nvar param1 = 1;\nvar param2 = 2;\n";
    uint32_t errorPos = 20;
    std::string result = revSourceMap.GetOriginalNames(sourceCode, errorPos);
    EXPECT_EQ(result, "SourceCode:\nvar param111 = 1;\n  var param222 = 2;\n");

    /**
     * @tc.steps: step2. construct posDiff < 0,flagPos < jsCode.length() false
     */
    sourceCode = "SourceCode:\nvar param111 = 1;\nvar param222 = 2;\n";
    revSourceMap.nameMap_.clear();
    revSourceMap.nameMap_.push_back("param111");
    revSourceMap.nameMap_.push_back("param1");
    revSourceMap.nameMap_.push_back("param222");
    revSourceMap.nameMap_.push_back("param2");
    std::string result2 = revSourceMap.GetOriginalNames(sourceCode, errorPos);
    EXPECT_EQ(result2, "SourceCode:\nvar param1 = 1;\nvar param2 = 2;\n");
    // flagPos < jsCode.length() true, false
    sourceCode = "SourceCode:\nvar param111 = 1;var param222 = 2;\n";
    std::string result3 = revSourceMap.GetOriginalNames(sourceCode, errorPos);
    EXPECT_EQ(result3, "SourceCode:\nvar param1 = 1;var param2 = 2;\n");
    // flagPos < jsCode.length() true, true,true
    sourceCode = "SourceCode:\nvar param111 = 1;var^param222 = 2;\n";
    uint32_t errorPos2 = 19;
    std::string result4 = revSourceMap.GetOriginalNames(sourceCode, errorPos2);
    EXPECT_EQ(result4, "SourceCode:\nvar param1 = 1;r^param2 = 2;\n");
}

/**
 * @tc.name: SourceMapTest010
 * @tc.desc: VlqRevCode()
 * @tc.type: FUNC
 */
HWTEST_F(SourceMapTest, SourceMapTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. VlqRevCode vStr.size() == 0
     */
    RevSourceMap revSourceMap;
    std::string vStr = "";
    std::vector<int32_t> ans;
    bool ret = revSourceMap.VlqRevCode(vStr, ans);
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step2. VlqRevCode vStr.size() != 0,include invalid char
     */
    std::string vStr2 = "abc/&";
    bool ret2 = revSourceMap.VlqRevCode(vStr2, ans);
    EXPECT_FALSE(ret2);

    /**
     * @tc.steps: step3. HandleMappings mapping = ""
     */
    std::string mapping;
    std::vector<std::string> ret3 = revSourceMap.HandleMappings(mapping);
    EXPECT_EQ(ret3.size(), 0);

    /**
     * @tc.steps: step4. HandleMappings mapping contain ';'
     */
    std::string mapping2 = ";";
    std::vector<std::string> ret4 = revSourceMap.HandleMappings(mapping2);
    EXPECT_EQ(ret4.size(), 1);
}
} // namespace OHOS::Ace::Framework
