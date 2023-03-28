/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t SWIPER_ERROR = -1;
constexpr int32_t SWIPER_RANGE_MAX_ERROR = -2;
constexpr int32_t INDEX_NUM = 10;
} // namespace
class SwiperAccessibilityPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
    void SetUp() override;
    void TearDown() override;
    bool InitSwiperTestNg();
    RefPtr<FrameNode> frameNode_;
    RefPtr<SwiperPattern> swiperPattern_;
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty_;
    RefPtr<SwiperAccessibilityProperty> swiperAccessibilityProperty_;
};

void SwiperAccessibilityPropertyTestNg::SetUp()
{
    ASSERT_TRUE(InitSwiperTestNg());
}

void SwiperAccessibilityPropertyTestNg::TearDown()
{
    frameNode_ = nullptr;
    swiperPattern_ = nullptr;
    swiperLayoutProperty_ = nullptr;
    swiperAccessibilityProperty_ = nullptr;
}

bool SwiperAccessibilityPropertyTestNg::InitSwiperTestNg()
{
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    CHECK_NULL_RETURN(frameNode_, false);
    swiperPattern_ = frameNode_->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern_, false);

    swiperLayoutProperty_ = frameNode_->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty_, false);

    swiperAccessibilityProperty_ = frameNode_->GetAccessibilityProperty<SwiperAccessibilityProperty>();
    CHECK_NULL_RETURN(swiperAccessibilityProperty_, false);

    return true;
}

/**
 * @tc.name: SwiperAccessibilityPropertyGetCurrentIndex001
 * @tc.desc: Test GetCurrentIndex of swiper.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAccessibilityPropertyTestNg, SwiperAccessibilityPropertyGetCurrentIndex001, TestSize.Level1)
{
    EXPECT_EQ(swiperAccessibilityProperty_->GetCurrentIndex(), 0);

    swiperPattern_->currentIndex_ = INDEX_NUM;

    EXPECT_EQ(swiperAccessibilityProperty_->GetCurrentIndex(), INDEX_NUM);
}

/**
 * @tc.name: SwiperAccessibilityPropertyGetBeginIndex001
 * @tc.desc: Test GetBeginIndex of swiper.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAccessibilityPropertyTestNg, SwiperAccessibilityPropertyGetBeginIndex001, TestSize.Level1)
{
    EXPECT_EQ(swiperAccessibilityProperty_->GetBeginIndex(), 0);

    swiperPattern_->startIndex_ = INDEX_NUM;

    EXPECT_EQ(swiperAccessibilityProperty_->GetBeginIndex(), INDEX_NUM);
}

/**
 * @tc.name: SwiperAccessibilityPropertyGetEndIndex001
 * @tc.desc: Test GetEndIndex of swiper.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAccessibilityPropertyTestNg, SwiperAccessibilityPropertyGetEndIndex001, TestSize.Level1)
{
    EXPECT_EQ(swiperAccessibilityProperty_->GetEndIndex(), 0);

    swiperPattern_->endIndex_ = INDEX_NUM;

    EXPECT_EQ(swiperAccessibilityProperty_->GetEndIndex(), INDEX_NUM);
}

/**
 * @tc.name: SwiperAccessibilityPropertyGetAccessibilityValue001
 * @tc.desc: Test GetAccessibilityValue of swiper.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAccessibilityPropertyTestNg, SwiperAccessibilityPropertyGetAccessibilityValue001, TestSize.Level1)
{
    EXPECT_TRUE(swiperAccessibilityProperty_->HasRange());
    AccessibilityValue result = swiperAccessibilityProperty_->GetAccessibilityValue();
    EXPECT_EQ(result.min, 0);
    EXPECT_EQ(result.max, SWIPER_RANGE_MAX_ERROR);
    EXPECT_EQ(result.current, 0);

    swiperLayoutProperty_->propShowIndicator_ = false;
    RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    swiperPattern_->currentIndex_ = INDEX_NUM;

    result = swiperAccessibilityProperty_->GetAccessibilityValue();
    EXPECT_EQ(result.min, 0);
    EXPECT_EQ(result.max, 0);
    EXPECT_EQ(result.current, INDEX_NUM);
}

/**
 * @tc.name: SwiperAccessibilityPropertyIsScrollable001
 * @tc.desc: Test IsScrollable of swiper.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAccessibilityPropertyTestNg, SwiperAccessibilityPropertyIsScrollable001, TestSize.Level1)
{
    ASSERT_TRUE(InitSwiperTestNg());
    EXPECT_EQ(swiperAccessibilityProperty_->IsScrollable(), false);

    swiperLayoutProperty_->propShowIndicator_ = false;
    RefPtr<FrameNode> indicatorNodeOne = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    RefPtr<FrameNode> indicatorNodeTwo = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNodeOne);
    frameNode_->AddChild(indicatorNodeTwo);

    EXPECT_EQ(swiperAccessibilityProperty_->IsScrollable(), true);
}

/**
 * @tc.name: SwiperAccessibilityPropertyGetCollectionItemCounts001
 * @tc.desc: Test GetCollectionItemCounts of swiper.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAccessibilityPropertyTestNg, SwiperAccessibilityPropertyGetCollectionItemCounts001, TestSize.Level1)
{
    ASSERT_TRUE(InitSwiperTestNg());
    EXPECT_EQ(swiperAccessibilityProperty_->GetCollectionItemCounts(), SWIPER_ERROR);

    swiperLayoutProperty_->propShowIndicator_ = false;
    RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);

    EXPECT_EQ(swiperAccessibilityProperty_->GetCollectionItemCounts(), 1);
}

/**
 * @tc.name: SwiperAccessibilityPropertyGetSupportAction001
 * @tc.desc: Test GetSupportAction of swiper.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAccessibilityPropertyTestNg, SwiperAccessibilityPropertyGetSupportAction001, TestSize.Level1)
{
    ASSERT_TRUE(InitSwiperTestNg());
    auto gestureEventHub = frameNode_->GetOrCreateGestureEventHub();
    gestureEventHub->longPressEventActuator_ =
        AceType::MakeRefPtr<LongPressEventActuator>(WeakPtr<GestureEventHub>(gestureEventHub));
    gestureEventHub->CheckClickActuator();

    auto focusHub = frameNode_->GetOrCreateFocusHub();
    frameNode_->eventHub_->enabled_ = true;
    focusHub->focusable_ = true;
    focusHub->focusType_ = FocusType::NODE;
    swiperAccessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = swiperAccessibilityProperty_->GetSupportAction();
    uint64_t actions = 0, exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_FOCUS);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_CLICK);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_LONG_CLICK);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SELECT);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, exptectActions);
}
} // namespace OHOS::Ace::NG
