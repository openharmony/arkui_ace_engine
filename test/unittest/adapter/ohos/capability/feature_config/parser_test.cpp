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
#include "adapter/ohos/capability/feature_config/feature_param_manager.h"
#include "adapter/ohos/capability/feature_config/features/sync_load_parser.h"
#include "adapter/ohos/capability/feature_config/features/ui_node_gc_params_parser.h"
#undef private
#undef protected
using namespace testing;
using namespace testing::ext;

class ParserTest : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
    void SetUp() {};
    void TearDown() {};

    OHOS::Ace::SyncloadParser syncLoadParser;
    OHOS::Ace::UINodeGcParamParser uiNodeGcParamParser;
};

/**
 * @tc.name  : IsValidDigits_ShouldReturnTrue_WhenStringIsValidDigits
 * @tc.number: ParserTest_001
 * @tc.desc  : 测试字符串全部由数字组成时,但是超出预期范围,函数应返回 false
 */
HWTEST_F(ParserTest, ATC_IsValidDigits_ShouldReturnTrue_WhenStringIsValidDigits, TestSize.Level0)
{
    std::string str = "123456";
    EXPECT_FALSE(syncLoadParser.IsValidDigits(str));
}

/**
 * @tc.name  : IsValidDigits_ShouldReturnFalse_WhenStringIsNotAllDigits
 * @tc.number: ParserTest_002
 * @tc.desc  : 测试字符串包含非数字字符时,函数应返回 false
 */
HWTEST_F(ParserTest, ATC_IsValidDigits_ShouldReturnFalse_WhenStringIsNotAllDigits, TestSize.Level0)
{
    std::string str = "45a";
    EXPECT_FALSE(syncLoadParser.IsValidDigits(str));
}

/**
 * @tc.name  : IsValidDigits_ShouldReturnTrue_WhenStringIsEmpty
 * @tc.number: ParserTest_003
 * @tc.desc  : 测试空字符串时,函数应返回 false
 */
HWTEST_F(ParserTest, ATC_IsValidDigits_ShouldReturnTrue_WhenStringIsEmpty, TestSize.Level0)
{
    std::string str = "";
    EXPECT_FALSE(syncLoadParser.IsValidDigits(str));
}

/**
 * @tc.name  : IsValidDigits_ShouldReturnFalse_WhenStringHasOnlyOneDigit
 * @tc.number: ParserTest_004
 * @tc.desc  : 测试字符串只有一个数字时,函数应返回 true
 */
HWTEST_F(ParserTest, ATC_IsValidDigits_ShouldReturnFalse_WhenStringHasOnlyOneDigit, TestSize.Level0)
{
    std::string str = "7";
    EXPECT_TRUE(syncLoadParser.IsValidDigits(str));
}

/**
 * @tc.name  : IsValidDigits_ShouldReturnTrue_WhenStringHasMultipleDigits
 * @tc.number: ParserTest_005
 * @tc.desc  : 测试字符串包含多个数字时,在合法范围0-999内,函数应返回 true
 */
HWTEST_F(ParserTest, ATC_IsValidDigits_ShouldReturnTrue_WhenStringHasMultipleDigits, TestSize.Level0)
{
    std::string str = "888";
    EXPECT_TRUE(syncLoadParser.IsValidDigits(str));
}

/**
 * @tc.name: STATIC_VALUE
 * @tc.desc: IsSyncLoadEnabled GetSyncloadResponseDeadline
 * @tc.type: FUNC
 */
HWTEST_F(ParserTest, STATIC_VALUE, TestSize.Level1)
{
    auto& instance = OHOS::Ace::FeatureParamManager::GetInstance();
    instance.SetSyncLoadEnableParam(true, 80);
    auto enable = instance.IsSyncLoadEnabled();
    auto time = instance.GetSyncloadResponseDeadline();
    EXPECT_EQ(enable, true);
    EXPECT_EQ(time, 80);

    instance.SetUINodeGcEnabled(true);
    enable = instance.IsUINodeGcEnabled();
    EXPECT_EQ(enable, true);
}

/**
 * @tc.name: ParseFeatureParam
 * @tc.desc: ParseFeatureParam
 * @tc.type: FUNC
 */
HWTEST_F(ParserTest, ParseFeatureParam, TestSize.Level1)
{
    xmlNode node;
    auto ret = syncLoadParser.ParseFeatureParam(node);
    EXPECT_EQ(ret, OHOS::Ace::PARSE_TYPE_ERROR);
    EXPECT_EQ(OHOS::Ace::FeatureParamManager::GetInstance().IsSyncLoadEnabled(), false);
    uiNodeGcParamParser.ParseFeatureParam(node);
    EXPECT_EQ(OHOS::Ace::FeatureParamManager::GetInstance().IsUINodeGcEnabled(), false);
}