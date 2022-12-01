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

#include "core/components_ng/pattern/navigation/bar_item_pattern.h"
#include "core/components_ng/base/view_stack_processor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string TOAST_ETS_TAG = "Toast";
} // namespace

class BarItemPatternTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
    void SetUp() override;
    void TearDown() override;
};

void BarItemPatternTestNg::SetUp() {}
void BarItemPatternTestNg::TearDown() {}

/**
 * @tc.name: CreateLayoutProperty001
 * @tc.desc: Test CreateLayoutProperty interface.
 * @tc.type: FUNC
 */
HWTEST_F(BarItemPatternTestNg, CreateLayoutProperty001, TestSize.Level1)
{
    auto barItemPattern = AceType::MakeRefPtr<BarItemPattern>();
    auto ret = barItemPattern->CreateLayoutProperty();
    EXPECT_NE(ret, nullptr);
}

/**
 * @tc.name: CreateLayoutAlgorithm001
 * @tc.desc: Test CreateLayoutAlgorithm interface.
 * @tc.type: FUNC
 */
HWTEST_F(BarItemPatternTestNg, CreateLayoutAlgorithm001, TestSize.Level1)
{
    auto barItemPattern = AceType::MakeRefPtr<BarItemPattern>();
    auto ret = barItemPattern->CreateLayoutAlgorithm();
    EXPECT_NE(ret, nullptr);
}

/**
 * @tc.name: CreateEventHub001
 * @tc.desc: Test CreateEventHub interface.
 * @tc.type: FUNC
 */
HWTEST_F(BarItemPatternTestNg, CreateEventHub001, TestSize.Level1)
{
    auto barItemPattern = AceType::MakeRefPtr<BarItemPattern>();
    auto ret = barItemPattern->CreateEventHub();
    EXPECT_NE(ret, nullptr);
}

/**
 * @tc.name: IsAtomicNode001
 * @tc.desc: Test IsAtomicNode interface.
 * @tc.type: FUNC
 */
HWTEST_F(BarItemPatternTestNg, IsAtomicNode001, TestSize.Level1)
{
    auto barItemPattern = AceType::MakeRefPtr<BarItemPattern>();
    auto ret = barItemPattern->IsAtomicNode();
    EXPECT_NE(ret, true);
}

/**
 * @tc.name: OnModifyDone001
 * @tc.desc: Test OnModifyDone interface.
 * @tc.type: FUNC
 */
HWTEST_F(BarItemPatternTestNg, OnModifyDone001, TestSize.Level1)
{
    auto itemNode = FrameNode::CreateFrameNode(TOAST_ETS_TAG, 0, AceType::MakeRefPtr<BarItemPattern>());
    EXPECT_TRUE(itemNode != nullptr);
    auto barItemPattern = AceType::MakeRefPtr<BarItemPattern>();
    barItemPattern->clickListener_ = nullptr;
    barItemPattern->AttachToFrameNode(itemNode);
    barItemPattern->OnModifyDone();
}

/**
 * @tc.name: OnModifyDone002
 * @tc.desc: Test OnModifyDone interface.
 * @tc.type: FUNC
 */
HWTEST_F(BarItemPatternTestNg, OnModifyDone002, TestSize.Level1)
{
    auto itemNode = FrameNode::CreateFrameNode(TOAST_ETS_TAG, 0, AceType::MakeRefPtr<BarItemPattern>());
    EXPECT_TRUE(itemNode != nullptr);
    auto barItemPattern = AceType::MakeRefPtr<BarItemPattern>();
    barItemPattern->clickListener_ = AceType::MakeRefPtr<ClickEvent>(nullptr);
    barItemPattern->AttachToFrameNode(itemNode);
    barItemPattern->OnModifyDone();
}
} // namespace OHOS::Ace::NG
