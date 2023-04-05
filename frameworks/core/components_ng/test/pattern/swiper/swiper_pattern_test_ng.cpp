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
#include "core/animation/animator.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/swiper/swiper_model_ng.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float SWIPER_IDEAL_WIDTH = 720.0f;
constexpr float SWIPER_IDEAL_HEIGHT = 1200.0f;
constexpr int32_t CURRENT_INDEX = 1;
constexpr int32_t CACHED_COUNT = 1;
constexpr int32_t DISPLAY_COUNT = 3;
constexpr Dimension ITEM_SPACE = Dimension(20, DimensionUnit::PX);
constexpr Dimension PREVIOUS_MARGIN = Dimension(50, DimensionUnit::PX);
constexpr Dimension NEXT_MARGIN = Dimension(50, DimensionUnit::PX);
constexpr Dimension NEXT_MARGIN_EXTRA_LARGE = Dimension(600, DimensionUnit::PX);
} // namespace

class SwiperPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
    void CreateChildWrapperAppendToHostWrapper(
        int32_t startIndex, int32_t endIndex, const RefPtr<LayoutWrapper>& hostWrapper);
    RefPtr<FrameNode> CreateSwiperFrameNode();
};

RefPtr<FrameNode> SwiperPatternTestNg::CreateSwiperFrameNode()
{
    SwiperModelNG swiper;
    swiper.Create();
    return AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
}

void SwiperPatternTestNg::CreateChildWrapperAppendToHostWrapper(
    int32_t startIndex, int32_t endIndex, const RefPtr<LayoutWrapper>& hostWrapper)
{
    ASSERT_NE(hostWrapper, nullptr);
    for (int32_t index = startIndex; index <= endIndex; index++) {
        auto childPattern = AceType::MakeRefPtr<Pattern>();
        auto childFrameNode = FrameNode::CreateFrameNode(BOX_NAME, index, childPattern);
        ASSERT_NE(childFrameNode, nullptr);
        auto host = hostWrapper->GetHostNode();
        ASSERT_NE(host, nullptr);
        host->AddChild(childFrameNode);
        RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        ASSERT_NE(childGeometryNode, nullptr);
        RefPtr<LayoutProperty> childLayoutProperty = childFrameNode->GetLayoutProperty();
        ASSERT_NE(childLayoutProperty, nullptr);
        childLayoutProperty->UpdateAspectRatio(1.0f);
        RefPtr<LayoutWrapper> childLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapper>(childFrameNode, childGeometryNode, childLayoutProperty);
        auto layoutAlgorithm = childPattern->CreateLayoutAlgorithm();
        ASSERT_NE(layoutAlgorithm, nullptr);
        childLayoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
        hostWrapper->AppendChild(std::move(childLayoutWrapper));
    }
}

/**
 * @tc.name: SwiperEvent001
 * @tc.desc: HandleTouchDown
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperEvent001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode = FrameNode::GetOrCreateFrameNode(
        "Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    std::list<TouchLocationInfo> infoList;
    infoList.emplace_back(touchLocationInfo);
    TouchEventInfo touchEventInfo("down");
    touchEventInfo.touches_ = infoList;
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    pattern->HandleTouchEvent(touchEventInfo);
    EXPECT_FALSE(pattern->indicatorDoingAnimation_);
    const char* name = "HandleTouchDown";
    pattern->controller_ = AceType::MakeRefPtr<Animator>(name);
    pattern->controller_->status_ = Animator::Status::RUNNING;
    pattern->springController_ = AceType::MakeRefPtr<Animator>(name);
    pattern->springController_->status_ = Animator::Status::RUNNING;
    pattern->HandleTouchEvent(touchEventInfo);
    EXPECT_FALSE(pattern->indicatorDoingAnimation_);

    touchLocationInfo.SetTouchType(TouchType::UP);
    pattern->HandleTouchEvent(touchEventInfo);
    pattern->controller_ = nullptr;
    pattern->springController_ = nullptr;
    touchLocationInfo.SetTouchType(TouchType::CANCEL);
    pattern->HandleTouchEvent(touchEventInfo);
    EXPECT_FALSE(pattern->indicatorDoingAnimation_);
}

/**
 * @tc.name: SwiperEvent002
 * @tc.desc: HandleTouchDown
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperEvent002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode = FrameNode::GetOrCreateFrameNode(
        "Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    pattern->InitPanEvent(gestureEventHub);
    EXPECT_EQ(pattern->direction_, Axis::HORIZONTAL);
}

/**
 * @tc.name: SwiperUtilsTest001
 * @tc.desc: Test Swiper measure and layout function, set prevMargin and nextMargin property is 50_px.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperUtilsTest001, TestSize.Level1)
{
    auto swiperFrameNode = CreateSwiperFrameNode();
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    auto swiperPaintProperty = swiperFrameNode->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);
    RefPtr<GeometryNode> swiperGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(swiperGeometryNode, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.Reset();
    layoutConstraint.selfIdealSize = OptionalSize(SizeF(SWIPER_IDEAL_WIDTH, SWIPER_IDEAL_HEIGHT));
    swiperLayoutProperty->UpdateLayoutConstraint(layoutConstraint);
    swiperLayoutProperty->UpdateContentConstraint();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(swiperFrameNode, swiperGeometryNode, swiperLayoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    int32_t displaycount = 3;
    swiperLayoutProperty->UpdateItemSpace(ITEM_SPACE);
    swiperLayoutProperty->UpdateCachedCount(CACHED_COUNT);
    swiperLayoutProperty->UpdateDirection(Axis::HORIZONTAL);
    swiperLayoutProperty->UpdateDisplayCount(displaycount);
    swiperLayoutProperty->UpdatePrevMargin(PREVIOUS_MARGIN);
    swiperLayoutProperty->UpdateNextMargin(NEXT_MARGIN);
    swiperLayoutProperty->UpdateShowIndicator(false);
    swiperPaintProperty->UpdateLoop(false);
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(swiperPattern->CreateLayoutAlgorithm());
    ASSERT_NE(swiperLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(swiperLayoutAlgorithm));
    int32_t startIndex = 0;
    int32_t endIndex = 4;
    swiperLayoutAlgorithm->startIndex_ = startIndex;
    swiperLayoutAlgorithm->endIndex_ = endIndex;
    swiperLayoutAlgorithm->currentIndex_ = 1;
    swiperLayoutAlgorithm->SetTotalCount(endIndex - startIndex);
    CreateChildWrapperAppendToHostWrapper(startIndex, endIndex, layoutWrapper);
    swiperLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    swiperLayoutAlgorithm->Layout(AceType::RawPtr(layoutWrapper));
    auto calcIdealLength = (SWIPER_IDEAL_WIDTH - PREVIOUS_MARGIN.Value() - NEXT_MARGIN.Value() -
                            ITEM_SPACE.Value() * (displaycount + 1)) / displaycount;
    for (int32_t index = startIndex; index <= endIndex; index++) {
        auto childLayout = layoutWrapper->GetOrCreateChildByIndex(index);
        ASSERT_NE(childLayout, nullptr);
        auto mainDirectionOffset = (PREVIOUS_MARGIN.Value() - calcIdealLength) +
            index * (calcIdealLength + ITEM_SPACE.Value());
        EXPECT_EQ(childLayout->GetGeometryNode()->GetFrameSize(), SizeF(calcIdealLength, calcIdealLength));
        EXPECT_EQ(childLayout->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(mainDirectionOffset, 0.0f));
    }
}

/**
 * @tc.name: SwiperUtilsTest002
 * @tc.desc: Verify the CreateChildConstraint function when DisplayCount is -1.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperUtilsTest002, TestSize.Level2)
{
    auto swiperFrameNode = CreateSwiperFrameNode();
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateDisplayCount(-1);

    OptionalSizeF setSize = OptionalSize(SizeF(SWIPER_IDEAL_WIDTH, SWIPER_IDEAL_HEIGHT));
    auto result = SwiperUtils::CreateChildConstraint(swiperLayoutProperty, setSize);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest003
 * @tc.desc: Verify the CreateChildConstraint function when DisplayMode is AUTO_LINEAR.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperUtilsTest003, TestSize.Level2)
{
    auto swiperFrameNode = CreateSwiperFrameNode();
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);

    OptionalSizeF setSize = OptionalSize(SizeF(SWIPER_IDEAL_WIDTH, SWIPER_IDEAL_HEIGHT));
    auto result = SwiperUtils::CreateChildConstraint(swiperLayoutProperty, setSize);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest004
 * @tc.desc: Verify the CreateChildConstraint function when NextMargin is normal and abnormal.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperUtilsTest004, TestSize.Level1)
{
    auto swiperFrameNode = CreateSwiperFrameNode();
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateIndex(CURRENT_INDEX);
    swiperLayoutProperty->UpdateItemSpace(ITEM_SPACE);
    swiperLayoutProperty->UpdateCachedCount(CACHED_COUNT);
    swiperLayoutProperty->UpdateDirection(Axis::HORIZONTAL);
    swiperLayoutProperty->UpdateDisplayCount(DISPLAY_COUNT);
    swiperLayoutProperty->UpdatePrevMargin(PREVIOUS_MARGIN);
    swiperLayoutProperty->UpdateNextMargin(NEXT_MARGIN);

    OptionalSizeF setSize = OptionalSize(SizeF(SWIPER_IDEAL_WIDTH, SWIPER_IDEAL_HEIGHT));
    auto result = SwiperUtils::CreateChildConstraint(swiperLayoutProperty, setSize);
    EXPECT_EQ(result.parentIdealSize, setSize);

    swiperLayoutProperty->UpdateNextMargin(NEXT_MARGIN_EXTRA_LARGE);
    result = SwiperUtils::CreateChildConstraint(swiperLayoutProperty, setSize);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest005
 * @tc.desc: Verify the CreateChildConstraint function does not set a value for setSize.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperUtilsTest005, TestSize.Level2)
{
    auto swiperFrameNode = CreateSwiperFrameNode();
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateIndex(CURRENT_INDEX);
    swiperLayoutProperty->UpdateItemSpace(ITEM_SPACE);
    swiperLayoutProperty->UpdateCachedCount(CACHED_COUNT);
    swiperLayoutProperty->UpdateDirection(Axis::HORIZONTAL);
    swiperLayoutProperty->UpdateDisplayCount(DISPLAY_COUNT);
    swiperLayoutProperty->UpdatePrevMargin(PREVIOUS_MARGIN);
    swiperLayoutProperty->UpdateNextMargin(NEXT_MARGIN);

    OptionalSizeF setSize;
    auto result = SwiperUtils::CreateChildConstraint(swiperLayoutProperty, setSize);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest006
 * @tc.desc: Verify the CreateChildConstraint function when Direction is VERTICAL.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperUtilsTest006, TestSize.Level1)
{
    auto swiperFrameNode = CreateSwiperFrameNode();
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateIndex(CURRENT_INDEX);
    swiperLayoutProperty->UpdateItemSpace(ITEM_SPACE);
    swiperLayoutProperty->UpdateCachedCount(CACHED_COUNT);
    swiperLayoutProperty->UpdateDirection(Axis::VERTICAL);
    swiperLayoutProperty->UpdateDisplayCount(DISPLAY_COUNT);
    swiperLayoutProperty->UpdatePrevMargin(PREVIOUS_MARGIN);
    swiperLayoutProperty->UpdateNextMargin(NEXT_MARGIN);

    OptionalSizeF setSize = OptionalSize(SizeF(SWIPER_IDEAL_WIDTH, SWIPER_IDEAL_HEIGHT));
    auto result = SwiperUtils::CreateChildConstraint(swiperLayoutProperty, setSize);
    EXPECT_EQ(result.parentIdealSize, setSize);

    swiperLayoutProperty->UpdateNextMargin(NEXT_MARGIN_EXTRA_LARGE);
    result = SwiperUtils::CreateChildConstraint(swiperLayoutProperty, setSize);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest007
 * @tc.desc: Verify the CreateChildConstraint function when Direction is VERTICAL and does not set value for setSize.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperUtilsTest007, TestSize.Level2)
{
    auto swiperFrameNode = CreateSwiperFrameNode();
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateIndex(CURRENT_INDEX);
    swiperLayoutProperty->UpdateItemSpace(ITEM_SPACE);
    swiperLayoutProperty->UpdateCachedCount(CACHED_COUNT);
    swiperLayoutProperty->UpdateDirection(Axis::VERTICAL);
    swiperLayoutProperty->UpdateDisplayCount(DISPLAY_COUNT);
    swiperLayoutProperty->UpdatePrevMargin(PREVIOUS_MARGIN);
    swiperLayoutProperty->UpdateNextMargin(NEXT_MARGIN);

    OptionalSizeF setSize;
    auto result = SwiperUtils::CreateChildConstraint(swiperLayoutProperty, setSize);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest008
 * @tc.desc: Verify the CreateChildConstraint function when Direction is FREE.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperUtilsTest008, TestSize.Level1)
{
    auto swiperFrameNode = CreateSwiperFrameNode();
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateIndex(CURRENT_INDEX);
    swiperLayoutProperty->UpdateItemSpace(ITEM_SPACE);
    swiperLayoutProperty->UpdateCachedCount(CACHED_COUNT);
    swiperLayoutProperty->UpdateDirection(Axis::FREE);
    swiperLayoutProperty->UpdateDisplayCount(DISPLAY_COUNT);
    swiperLayoutProperty->UpdatePrevMargin(PREVIOUS_MARGIN);
    swiperLayoutProperty->UpdateNextMargin(NEXT_MARGIN);

    OptionalSizeF setSize = OptionalSize(SizeF(SWIPER_IDEAL_WIDTH, SWIPER_IDEAL_HEIGHT));
    auto result = SwiperUtils::CreateChildConstraint(swiperLayoutProperty, setSize);
    EXPECT_EQ(result.parentIdealSize, setSize);
}
} // namespace OHOS::Ace::NG
