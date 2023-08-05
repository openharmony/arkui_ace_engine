/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License" << std::endl;
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
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/scroll_bar/scroll_bar_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
constexpr float CURRENT_DISTANCE = 5.0f;
constexpr float MIN_DISTANCE = 0.0f;
constexpr float SCROLLABLE_DISTANCE = 10.0f;
} // namespace
class ScrollBarAccessibilityPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
    void SetUp() override;
    void TearDown() override;
    void InitScrollBarTestNg();
    RefPtr<FrameNode> frameNode_;
    RefPtr<ScrollBarPattern> scrollBarPattern_;
    RefPtr<ScrollBarAccessibilityProperty> scrollBarAccessibilityProperty_;
};

void ScrollBarAccessibilityPropertyTestNg::SetUp()
{
    MockPipelineBase::SetUp();
}

void ScrollBarAccessibilityPropertyTestNg::TearDown()
{
    frameNode_ = nullptr;
    scrollBarPattern_ = nullptr;
    scrollBarAccessibilityProperty_ = nullptr;
    MockPipelineBase::TearDown();
}

void ScrollBarAccessibilityPropertyTestNg::InitScrollBarTestNg()
{
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::SCROLL_BAR_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<ScrollBarPattern>(); });
    ASSERT_NE(frameNode_, nullptr);

    scrollBarPattern_ = frameNode_->GetPattern<ScrollBarPattern>();
    ASSERT_NE(scrollBarPattern_, nullptr);

    scrollBarAccessibilityProperty_ = frameNode_->GetAccessibilityProperty<ScrollBarAccessibilityProperty>();
    ASSERT_NE(scrollBarAccessibilityProperty_, nullptr);
}

/**
 * @tc.name: ScrollBarAccessibilityPropertyIsScrollable001
 * @tc.desc: Test IsScrollable of scrollBar.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarAccessibilityPropertyTestNg, ScrollBarAccessibilityPropertyIsScrollable001, TestSize.Level1)
{
    InitScrollBarTestNg();

    EXPECT_FALSE(scrollBarAccessibilityProperty_->IsScrollable());

    scrollBarPattern_->axis_ = Axis::VERTICAL;
    scrollBarPattern_->controlDistance_ = SCROLLABLE_DISTANCE;
    EXPECT_TRUE(scrollBarAccessibilityProperty_->IsScrollable());
}

/**
 * @tc.name: ScrollBarAccessibilityPropertyGetAccessibilityValue001
 * @tc.desc: Test GetAccessibilityValue of scrollBar.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarAccessibilityPropertyTestNg, ScrollBarAccessibilityPropertyGetAccessibilityValue001, TestSize.Level1)
{
    InitScrollBarTestNg();

    EXPECT_TRUE(scrollBarAccessibilityProperty_->HasRange());
    AccessibilityValue result = scrollBarAccessibilityProperty_->GetAccessibilityValue();
    EXPECT_EQ(result.min, MIN_DISTANCE);
    EXPECT_EQ(result.max, MIN_DISTANCE);
    EXPECT_EQ(result.current, MIN_DISTANCE);

    scrollBarPattern_->currentOffset_ = CURRENT_DISTANCE;
    scrollBarPattern_->scrollableDistance_ = SCROLLABLE_DISTANCE;
    result = scrollBarAccessibilityProperty_->GetAccessibilityValue();
    EXPECT_EQ(result.min, MIN_DISTANCE);
    EXPECT_EQ(result.max, SCROLLABLE_DISTANCE);
    EXPECT_EQ(result.current, CURRENT_DISTANCE);
}

/**
 * @tc.name: ScrollBarAccessibilityPropertyGetSupportAction001
 * @tc.desc: Test GetSupportAction of scrollBar.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarAccessibilityPropertyTestNg, ScrollBarAccessibilityPropertyGetSupportAction001, TestSize.Level1)
{
    InitScrollBarTestNg();

    scrollBarPattern_->axis_ = Axis::VERTICAL;
    scrollBarPattern_->controlDistance_ = SCROLLABLE_DISTANCE;
    scrollBarPattern_->currentOffset_ = CURRENT_DISTANCE;
    scrollBarPattern_->scrollableDistance_ = SCROLLABLE_DISTANCE;

    scrollBarAccessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = scrollBarAccessibilityProperty_->GetSupportAction();
    uint64_t actions = 0, expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, expectActions);
}
} // namespace OHOS::Ace::NG
