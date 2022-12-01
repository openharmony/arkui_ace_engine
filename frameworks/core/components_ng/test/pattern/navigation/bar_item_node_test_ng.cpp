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

#define protected public
#define private public

#include "core/components_ng/pattern/navigation/bar_item_node.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string BAR_ITEM_ETS_TAG = "BarItem";
const std::string EMPTY_STRING = "";
const int32_t RET_OK = 0;
} // namespace

class BarItemNodeTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
    void SetUp() override;
    void TearDown() override;
};

void BarItemNodeTestNg::SetUp() {}
void BarItemNodeTestNg::TearDown() {}

/**
 * @tc.name: OnIconSrcUpdate001
 * @tc.desc: Test OnIconSrcUpdate interface.
 * @tc.type: FUNC
 */
HWTEST_F(BarItemNodeTestNg, OnIconSrcUpdate001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barItemNode = AceType::MakeRefPtr<BarItemNode>(barTag, nodeId);
    std::string value = EMPTY_STRING;
    int32_t ret = RET_OK;
    barItemNode->OnIconSrcUpdate(value);
    EXPECT_EQ(ret, RET_OK);
}

/**
 * @tc.name: OnTextUpdate001
 * @tc.desc: Test OnTextUpdate interface.
 * @tc.type: FUNC
 */
HWTEST_F(BarItemNodeTestNg, OnTextUpdate001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barItemNode = AceType::MakeRefPtr<BarItemNode>(barTag, nodeId);
    std::string value = EMPTY_STRING;
    int32_t ret = RET_OK;
    barItemNode->OnTextUpdate(value);
    EXPECT_EQ(ret, RET_OK);
}

/**
 * @tc.name: IsAtomicNode001
 * @tc.desc: Test IsAtomicNode interface.
 * @tc.type: FUNC
 */
HWTEST_F(BarItemNodeTestNg, IsAtomicNode001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barItemNode = AceType::MakeRefPtr<BarItemNode>(barTag, nodeId);
    auto ret = barItemNode->IsAtomicNode();
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: SetTextNode001
 * @tc.desc: Test SetTextNode interface.
 * @tc.type: FUNC
 */
HWTEST_F(BarItemNodeTestNg, SetTextNode001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barItemNode = AceType::MakeRefPtr<BarItemNode>(barTag, nodeId);
    barItemNode->SetTextNode(nullptr);
    EXPECT_EQ(barItemNode->text_, nullptr);
}

/**
 * @tc.name: GetTextNode001
 * @tc.desc: Test GetTextNode interface.
 * @tc.type: FUNC
 */
HWTEST_F(BarItemNodeTestNg, GetTextNode001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barItemNode = AceType::MakeRefPtr<BarItemNode>(barTag, nodeId);
    auto ret = barItemNode->GetTextNode();
    EXPECT_EQ(ret, nullptr);
}

/**
 * @tc.name: SetIconNode001
 * @tc.desc: Test SetIconNode interface.
 * @tc.type: FUNC
 */
HWTEST_F(BarItemNodeTestNg, SetIconNode001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barItemNode = AceType::MakeRefPtr<BarItemNode>(barTag, nodeId);
    barItemNode->SetIconNode(nullptr);
    EXPECT_EQ(barItemNode->icon_, nullptr);
}

/**
 * @tc.name: GetIconNode001
 * @tc.desc: Test GetIconNode interface.
 * @tc.type: FUNC
 */
HWTEST_F(BarItemNodeTestNg, GetIconNode001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barItemNode = AceType::MakeRefPtr<BarItemNode>(barTag, nodeId);
    auto ret = barItemNode->GetIconNode();
    EXPECT_EQ(ret, nullptr);
}
} // namespace OHOS::Ace::NG
