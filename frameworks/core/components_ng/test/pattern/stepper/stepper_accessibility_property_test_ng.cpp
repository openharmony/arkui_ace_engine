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

#include "core/components_v2/inspector/inspector_constants.h"

#define private public
#define protected public
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/stepper/stepper_node.h"
#include "core/components_ng/pattern/stepper/stepper_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t STEPPER_ERROR = -1;
constexpr int32_t INDEX_NUM = 10;
} // namespace
class StepperAccessibilityPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
    void SetUp() override;
    void TearDown() override;
    void InitStepperTestNg();
    RefPtr<StepperNode> frameNode_;
    RefPtr<StepperPattern> stepperPattern_;
    RefPtr<StepperAccessibilityProperty> stepperAccessibilityProperty_;
    RefPtr<FrameNode> swiperNode_;
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty_;
};

void StepperAccessibilityPropertyTestNg::SetUp() {}

void StepperAccessibilityPropertyTestNg::TearDown()
{
    frameNode_ = nullptr;
    stepperPattern_ = nullptr;
    stepperAccessibilityProperty_ = nullptr;
    swiperNode_ = nullptr;
    swiperLayoutProperty_ = nullptr;
}

void StepperAccessibilityPropertyTestNg::InitStepperTestNg()
{
    frameNode_ = StepperNode::GetOrCreateStepperNode(V2::STEPPER_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(frameNode_, nullptr);

    stepperPattern_ = frameNode_->GetPattern<StepperPattern>();
    ASSERT_NE(stepperPattern_, nullptr);

    stepperAccessibilityProperty_ = frameNode_->GetAccessibilityProperty<StepperAccessibilityProperty>();
    ASSERT_NE(stepperAccessibilityProperty_, nullptr);

    swiperNode_ = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_ETS_TAG, frameNode_->GetSwiperId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    ASSERT_NE(swiperNode_, nullptr);
    swiperNode_->MountToParent(frameNode_);

    swiperLayoutProperty_ = swiperNode_->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty_, nullptr);
}

/**
 * @tc.name: StepperAccessibilityPropertyGetCurrentIndex001
 * @tc.desc: Test GetCurrentIndex of stepper.
 * @tc.type: FUNC
 */
HWTEST_F(StepperAccessibilityPropertyTestNg, StepperAccessibilityPropertyGetCurrentIndex001, TestSize.Level1)
{
    InitStepperTestNg();

    EXPECT_EQ(stepperAccessibilityProperty_->GetCurrentIndex(), STEPPER_ERROR);

    for (int i = 0; i <= INDEX_NUM; i++) {
        auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
        ASSERT_NE(indicatorNode, nullptr);
        swiperNode_->AddChild(indicatorNode);
    }
    stepperPattern_->index_ = INDEX_NUM;
    swiperLayoutProperty_->UpdateShowIndicator(false);
    EXPECT_EQ(stepperAccessibilityProperty_->GetCurrentIndex(), INDEX_NUM);
}

/**
 * @tc.name: StepperAccessibilityPropertyGetBeginIndex001
 * @tc.desc: Test GetBeginIndex of stepper.
 * @tc.type: FUNC
 */
HWTEST_F(StepperAccessibilityPropertyTestNg, StepperAccessibilityPropertyGetBeginIndex001, TestSize.Level1)
{
    InitStepperTestNg();

    EXPECT_EQ(stepperAccessibilityProperty_->GetBeginIndex(), STEPPER_ERROR);

    for (int i = 0; i <= INDEX_NUM; i++) {
        auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
        ASSERT_NE(indicatorNode, nullptr);
        swiperNode_->AddChild(indicatorNode);
    }
    swiperLayoutProperty_->UpdateShowIndicator(false);
    EXPECT_EQ(stepperAccessibilityProperty_->GetBeginIndex(), 0);
}

/**
 * @tc.name: StepperAccessibilityPropertyGetEndIndex001
 * @tc.desc: Test GetEndIndex of stepper.
 * @tc.type: FUNC
 */
HWTEST_F(StepperAccessibilityPropertyTestNg, StepperAccessibilityPropertyGetEndIndex001, TestSize.Level1)
{
    InitStepperTestNg();

    EXPECT_EQ(stepperAccessibilityProperty_->GetEndIndex(), STEPPER_ERROR);

    for (int i = 0; i <= INDEX_NUM; i++) {
        auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
        ASSERT_NE(indicatorNode, nullptr);
        swiperNode_->AddChild(indicatorNode);
    }
    swiperLayoutProperty_->UpdateShowIndicator(false);

    EXPECT_EQ(stepperAccessibilityProperty_->GetEndIndex(), INDEX_NUM);
}

/**
 * @tc.name: StepperAccessibilityPropertyIsScrollable001
 * @tc.desc: Test IsScrollable of stepper.
 * @tc.type: FUNC
 */
HWTEST_F(StepperAccessibilityPropertyTestNg, StepperAccessibilityPropertyIsScrollable001, TestSize.Level1)
{
    InitStepperTestNg();

    auto swiperPaintProperty = swiperNode_->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);
    swiperPaintProperty->UpdateLoop(false);
    EXPECT_FALSE(stepperAccessibilityProperty_->IsScrollable());

    for (int i = 0; i <= INDEX_NUM; i++) {
        auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
        ASSERT_NE(indicatorNode, nullptr);
        swiperNode_->AddChild(indicatorNode);
    }
    swiperLayoutProperty_->UpdateShowIndicator(false);
    auto swiperPattern = swiperNode_->GetPattern<SwiperPattern>();
    EXPECT_TRUE(stepperAccessibilityProperty_->IsScrollable());
}

/**
 * @tc.name: StepperAccessibilityPropertyGetCollectionItemCounts001
 * @tc.desc: Test GetCollectionItemCounts of stepper.
 * @tc.type: FUNC
 */
HWTEST_F(StepperAccessibilityPropertyTestNg, StepperAccessibilityPropertyGetCollectionItemCounts001, TestSize.Level1)
{
    InitStepperTestNg();

    EXPECT_EQ(stepperAccessibilityProperty_->GetCollectionItemCounts(), STEPPER_ERROR);

    for (int i = 0; i < INDEX_NUM; i++) {
        auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
        ASSERT_NE(indicatorNode, nullptr);
        swiperNode_->AddChild(indicatorNode);
    }
    swiperLayoutProperty_->UpdateShowIndicator(false);
    EXPECT_EQ(stepperAccessibilityProperty_->GetCollectionItemCounts(), INDEX_NUM);
}

/**
 * @tc.name: StepperAccessibilityPropertyGetSupportAction001
 * @tc.desc: Test GetSupportAction of stepper.
 * @tc.type: FUNC
 */
HWTEST_F(StepperAccessibilityPropertyTestNg, StepperAccessibilityPropertyGetSupportAction001, TestSize.Level1)
{
    InitStepperTestNg();

    auto swiperPaintProperty = swiperNode_->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);
    swiperPaintProperty->UpdateLoop(false);
    swiperLayoutProperty_->UpdateShowIndicator(false);
    for (int index = 0; index <= INDEX_NUM; index++) {
        RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
        ASSERT_NE(indicatorNode, nullptr);
        swiperNode_->AddChild(indicatorNode);
    }
    stepperPattern_->index_ = 1;

    stepperAccessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = stepperAccessibilityProperty_->GetSupportAction();
    uint64_t actions = 0, expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, expectActions);

    swiperPaintProperty->UpdateLoop(true);
    stepperAccessibilityProperty_->ResetSupportAction();
    supportAceActions = stepperAccessibilityProperty_->GetSupportAction();
    actions = 0;
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, expectActions);
}
} // namespace OHOS::Ace::NG
