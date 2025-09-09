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

    OHOS::Ace::SyncLoadParser syncLoadParser;
    OHOS::Ace::UINodeGcParamParser uiNodeGcParamParser;
};

/**
 * @tc.name  : IsValidDigits_ShouldReturnTrue_WhenStringIsValidDigits
 * @tc.number: ParserTest_001
 */
HWTEST_F(ParserTest, ATC_IsValidDigits_ShouldReturnTrue_WhenStringIsValidDigits, TestSize.Level0)
{
    // @tc.desc  : 测试字符串全部由数字组成时,但是超出预期范围,函数应返回 false
    EXPECT_FALSE(syncLoadParser.IsValidDigits("123456"));
    // @tc.desc  : 测试字符串包含非数字字符时,函数应返回 false
    EXPECT_FALSE(syncLoadParser.IsValidDigits("45a"));
    // @tc.desc  : 测试空字符串时,函数应返回 false
    EXPECT_FALSE(syncLoadParser.IsValidDigits(""));
    // @tc.desc  : 测试字符串只有一个数字时,函数应返回 true
    EXPECT_TRUE(syncLoadParser.IsValidDigits("7"));
    // @tc.desc  : 测试字符串包含多个数字时,在合法范围0-999内,函数应返回 true
    EXPECT_TRUE(syncLoadParser.IsValidDigits("888"));
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

    node.type = xmlElementType::XML_ELEMENT_NODE;
    const std::string valueKeyStr = "value";
    const std::string valueValStr = "50";
    xmlSetProp(&node, (const xmlChar*)(valueKeyStr.c_str()), (const xmlChar*)(valueValStr.c_str()));
    ret = syncLoadParser.ParseFeatureParam(node);
    EXPECT_EQ(ret, OHOS::Ace::PARSE_EXEC_SUCCESS);

    ret = uiNodeGcParamParser.ParseFeatureParam(node);
    EXPECT_EQ(ret, OHOS::Ace::PARSE_EXEC_SUCCESS);
}