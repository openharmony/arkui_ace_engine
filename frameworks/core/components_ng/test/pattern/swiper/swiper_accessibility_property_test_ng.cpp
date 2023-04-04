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
constexpr int32_t INDEX_NUM = 10;
} // namespace
class SwiperAccessibilityPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
    void SetUp() override;
    void TearDown() override;
    void InitSwiperTestNg();
    RefPtr<FrameNode> frameNode_;
    RefPtr<SwiperPattern> swiperPattern_;
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty_;
    RefPtr<SwiperAccessibilityProperty> swiperAccessibilityProperty_;
};

void SwiperAccessibilityPropertyTestNg::SetUp() {}

void SwiperAccessibilityPropertyTestNg::TearDown()
{
    frameNode_ = nullptr;
    swiperPattern_ = nullptr;
    swiperLayoutProperty_ = nullptr;
    swiperAccessibilityProperty_ = nullptr;
}

void SwiperAccessibilityPropertyTestNg::InitSwiperTestNg()
{
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    ASSERT_NE(frameNode_, nullptr);
    swiperPattern_ = frameNode_->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern_, nullptr);

    swiperLayoutProperty_ = frameNode_->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty_, nullptr);

    swiperAccessibilityProperty_ = frameNode_->GetAccessibilityProperty<SwiperAccessibilityProperty>();
    ASSERT_NE(swiperAccessibilityProperty_, nullptr);

    swiperLayoutProperty_->UpdateShowIndicator(false);
}

/**
 * @tc.name: SwiperAccessibilityPropertyGetCurrentIndex001
 * @tc.desc: Test GetCurrentIndex of swiper.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAccessibilityPropertyTestNg, SwiperAccessibilityPropertyGetCurrentIndex001, TestSize.Level1)
{
    InitSwiperTestNg();

    EXPECT_EQ(swiperAccessibilityProperty_->GetCurrentIndex(), SWIPER_ERROR);

    RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode_->AddChild(indicatorNode);
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
    InitSwiperTestNg();

    EXPECT_EQ(swiperAccessibilityProperty_->GetBeginIndex(), SWIPER_ERROR);

    RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode_->AddChild(indicatorNode);
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
    InitSwiperTestNg();

    EXPECT_EQ(swiperAccessibilityProperty_->GetEndIndex(), SWIPER_ERROR);

    RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode_->AddChild(indicatorNode);
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
    InitSwiperTestNg();

    EXPECT_TRUE(swiperAccessibilityProperty_->HasRange());
    AccessibilityValue result = swiperAccessibilityProperty_->GetAccessibilityValue();
    EXPECT_EQ(result.min, 0);
    EXPECT_EQ(result.max, 0);
    EXPECT_EQ(result.current, 0);

    for (int index = 0; index <= INDEX_NUM; index++) {
        RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
        ASSERT_NE(indicatorNode, nullptr);
        frameNode_->AddChild(indicatorNode);
    }
    swiperPattern_->currentIndex_ = INDEX_NUM;

    result = swiperAccessibilityProperty_->GetAccessibilityValue();
    EXPECT_EQ(result.min, 0);
    EXPECT_EQ(result.max, INDEX_NUM);
    EXPECT_EQ(result.current, INDEX_NUM);
}

/**
 * @tc.name: SwiperAccessibilityPropertyIsScrollable001
 * @tc.desc: Test IsScrollable of swiper.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAccessibilityPropertyTestNg, SwiperAccessibilityPropertyIsScrollable001, TestSize.Level1)
{
    InitSwiperTestNg();

    auto swiperPaintProperty = frameNode_->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);
    swiperPaintProperty->UpdateLoop(false);
    EXPECT_FALSE(swiperAccessibilityProperty_->IsScrollable());

    for (int index = 0; index <= INDEX_NUM; index++) {
        RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
        ASSERT_NE(indicatorNode, nullptr);
        frameNode_->AddChild(indicatorNode);
    }
    swiperPattern_->OnModifyDone();
    EXPECT_TRUE(swiperAccessibilityProperty_->IsScrollable());
}

/**
 * @tc.name: SwiperAccessibilityPropertyGetCollectionItemCounts001
 * @tc.desc: Test GetCollectionItemCounts of swiper.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAccessibilityPropertyTestNg, SwiperAccessibilityPropertyGetCollectionItemCounts001, TestSize.Level1)
{
    InitSwiperTestNg();

    EXPECT_EQ(swiperAccessibilityProperty_->GetCollectionItemCounts(), 0);

    for (int index = 0; index <= INDEX_NUM; index++) {
        RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
        ASSERT_NE(indicatorNode, nullptr);
        frameNode_->AddChild(indicatorNode);
    }
    swiperPattern_->OnModifyDone();
    EXPECT_EQ(swiperAccessibilityProperty_->GetCollectionItemCounts(), INDEX_NUM);
}

/**
 * @tc.name: SwiperAccessibilityPropertyGetSupportAction001
 * @tc.desc: Test GetSupportAction of swiper.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAccessibilityPropertyTestNg, SwiperAccessibilityPropertyGetSupportAction001, TestSize.Level1)
{
    InitSwiperTestNg();

    auto swiperPaintProperty = frameNode_->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);
    swiperPaintProperty->UpdateLoop(false);
    for (int index = 0; index <= INDEX_NUM; index++) {
        RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
        ASSERT_NE(indicatorNode, nullptr);
        frameNode_->AddChild(indicatorNode);
    }
    swiperPattern_->currentIndex_ = 1;
    swiperPattern_->OnModifyDone();
    swiperAccessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = swiperAccessibilityProperty_->GetSupportAction();
    uint64_t actions = 0, expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SELECT);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_CLEAR_SELECTION);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, expectActions);

    swiperPaintProperty->UpdateLoop(true);
    swiperAccessibilityProperty_->ResetSupportAction();
    supportAceActions = swiperAccessibilityProperty_->GetSupportAction();
    actions = 0;
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, expectActions);
}
} // namespace OHOS::Ace::NG
