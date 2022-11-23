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
#define private public
#include "gtest/gtest.h"

#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/refresh/refresh_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/refresh/refresh_event_hub.h"
#include "core/components_ng/pattern/refresh/refresh_layout_property.h"
#include "core/components_ng/pattern/refresh/refresh_model_ng.h"
#include "core/components_ng/pattern/refresh/refresh_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;


namespace OHOS::Ace::NG {
namespace {
constexpr double DEFAULT_INDICATOR_OFFSET = 16.0f;
constexpr int32_t DEFAULT_FRICTION_RATIO = 42;
constexpr int32_t DEFAULT_PARAM = 100;
constexpr float CONTAINER_WIDTH = 300.0f;
constexpr float CONTAINER_HEIGHT = 300.0f;
const SizeF CONTAINER_SIZE(CONTAINER_WIDTH, CONTAINER_HEIGHT);

constexpr float IDEAL_WIDTH = 300.0f;
constexpr float IDEAL_HEIGHT = 300.0f;
const SizeF IDEAL_SIZE(IDEAL_WIDTH, IDEAL_HEIGHT);

constexpr float MAX_WIDTH = 400.0f;
constexpr float MAX_HEIGHT = 400.0f;
const SizeF MAX_SIZE(MAX_WIDTH, MAX_HEIGHT);

constexpr Color COLOR_VALUE = Color(0xf0000000);
const TextStyle TEXT_VALUE = TextStyle();
constexpr Dimension refreshDistance = Dimension(DEFAULT_PARAM, DimensionUnit::PX);
constexpr Dimension loadingDistance = Dimension(DEFAULT_PARAM, DimensionUnit::PX);
constexpr Dimension progressDistance = Dimension(DEFAULT_PARAM, DimensionUnit::PX);
constexpr Dimension progressDiameter = Dimension(DEFAULT_PARAM, DimensionUnit::PX);
constexpr Dimension maxDistance = Dimension(DEFAULT_PARAM, DimensionUnit::PX);
constexpr Dimension showTimeDistance = Dimension(DEFAULT_PARAM, DimensionUnit::PX);
} // namespace
class RefreshPatternTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};

protected:
    static RefPtr<FrameNode> CreateRefreshNode();
    static RefPtr<FrameNode> CreateRefreshNodeAndInitParam();
};

RefPtr<FrameNode> RefreshPatternTestNg::CreateRefreshNode()
{
    RefreshModelNG modelNG;
    modelNG.Create();
    modelNG.SetIsShowLastTime(false);
    modelNG.Pop();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    return frameNode;
}

RefPtr<FrameNode> RefreshPatternTestNg::CreateRefreshNodeAndInitParam()
{
    RefreshModelNG modelNG;
    modelNG.Create();
    modelNG.SetIsShowLastTime(false);
    modelNG.SetRefreshDistance(refreshDistance);
    modelNG.SetLoadingDistance(loadingDistance);
    modelNG.SetProgressDistance(progressDistance);
    modelNG.SetProgressDiameter(progressDiameter);
    modelNG.SetMaxDistance(maxDistance);
    modelNG.SetShowTimeDistance(showTimeDistance);
    modelNG.SetProgressColor(COLOR_VALUE);
    modelNG.SetProgressBackgroundColor(COLOR_VALUE);
    modelNG.SetTextStyle(TEXT_VALUE);
    modelNG.Pop();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    return frameNode;
}

/**
 * @tc.name: RefreshTest001
 * @tc.desc: Test event function of refresh eventHub.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and get frameNode of refresh.
     */
    auto frameNode = CreateRefreshNode();
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::REFRESH_ETS_TAG);
    /**
     * @tc.steps: step2. set callback function by eventHub
     */
    RefPtr<RefreshEventHub> eventHub = frameNode->GetEventHub<RefreshEventHub>();
    EXPECT_NE(eventHub, nullptr);
    std::string changeEventValue;
    auto onChangeEvent = [&changeEventValue](const std::string& param) { changeEventValue = param; };
    eventHub->SetChangeEvent(std::move(onChangeEvent));
    int32_t stateChangeValue = -1;
    auto onStateChangeEvent = [&stateChangeValue](const int32_t param) { stateChangeValue = param; };
    eventHub->SetOnStateChange(std::move(onStateChangeEvent));
    bool refreshingValue = false;
    auto onRefreshingEvent = [&refreshingValue]() { refreshingValue = true; };
    eventHub->SetOnRefreshing(std::move(onRefreshingEvent));
    /**
     * @tc.steps: step3. test callback function by eventHub
     */
    eventHub->FireOnRefreshing();
    EXPECT_EQ(refreshingValue, true);
    eventHub->FireChangeEvent("true");
    EXPECT_EQ(changeEventValue, "true");
    eventHub->FireChangeEvent("false");
    EXPECT_EQ(changeEventValue, "false");
    eventHub->FireOnStateChange(static_cast<int>(RefreshStatus::INACTIVE));
    EXPECT_EQ(stateChangeValue, static_cast<int>(RefreshStatus::INACTIVE));
    eventHub->FireOnStateChange(static_cast<int>(RefreshStatus::REFRESH));
    EXPECT_EQ(stateChangeValue, static_cast<int>(RefreshStatus::REFRESH));
    eventHub->FireOnStateChange(static_cast<int>(RefreshStatus::DRAG));
    EXPECT_EQ(stateChangeValue, static_cast<int>(RefreshStatus::DRAG));
    eventHub->FireOnStateChange(static_cast<int>(RefreshStatus::OVER_DRAG));
    EXPECT_EQ(stateChangeValue, static_cast<int>(RefreshStatus::OVER_DRAG));
    eventHub->FireOnStateChange(static_cast<int>(RefreshStatus::DONE));
    EXPECT_EQ(stateChangeValue, static_cast<int>(RefreshStatus::DONE));
}

/**
 * @tc.name: RefreshTest002
 * @tc.desc: Test event function of refresh pattern.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and get frameNode of refresh.
     */
    auto frameNode = CreateRefreshNode();
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::REFRESH_ETS_TAG);
    RefPtr<RefreshLayoutProperty> layoutProperty = frameNode->GetLayoutProperty<RefreshLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step2. set callback function by eventHub
     */
    RefPtr<RefreshEventHub> eventHub = frameNode->GetEventHub<RefreshEventHub>();
    EXPECT_NE(eventHub, nullptr);
    std::string changeEventValue;
    auto onChangeEvent = [&changeEventValue](const std::string& param) { changeEventValue = param; };
    eventHub->SetChangeEvent(std::move(onChangeEvent));
    int32_t stateChangeValue = -1;
    auto onStateChangeEvent = [&stateChangeValue](const int32_t param) { stateChangeValue = param; };
    eventHub->SetOnStateChange(std::move(onStateChangeEvent));
    bool refreshingValue = false;
    auto onRefreshingEvent = [&refreshingValue]() { refreshingValue = true; };
    eventHub->SetOnRefreshing(std::move(onRefreshingEvent));
    /**
     * @tc.steps: step3. test pattern event function
     */
    RefPtr<RefreshPattern> pattern = frameNode->GetPattern<RefreshPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->FireRefreshing();
    EXPECT_EQ(refreshingValue, true);
    pattern->FireChangeEvent("false");
    EXPECT_EQ(changeEventValue, "false");
    pattern->FireChangeEvent("true");
    EXPECT_EQ(changeEventValue, "true");
    pattern->FireStateChange(static_cast<int>(RefreshStatus::INACTIVE));
    EXPECT_EQ(stateChangeValue, static_cast<int>(RefreshStatus::INACTIVE));
    pattern->FireStateChange(static_cast<int>(RefreshStatus::REFRESH));
    EXPECT_EQ(stateChangeValue, static_cast<int>(RefreshStatus::REFRESH));
    pattern->FireStateChange(static_cast<int>(RefreshStatus::DRAG));
    EXPECT_EQ(stateChangeValue, static_cast<int>(RefreshStatus::DRAG));
    pattern->FireStateChange(static_cast<int>(RefreshStatus::OVER_DRAG));
    EXPECT_EQ(stateChangeValue, static_cast<int>(RefreshStatus::OVER_DRAG));
    pattern->FireStateChange(static_cast<int>(RefreshStatus::DONE));
    EXPECT_EQ(stateChangeValue, static_cast<int>(RefreshStatus::DONE));
    /**
     * @tc.steps: step4. test pattern active function
     */
    pattern->OnInActive();
    EXPECT_EQ(changeEventValue, "false");
    pattern->OnModifyDone();
    EXPECT_EQ(layoutProperty->GetLoadingProcessOffsetValue(OffsetF(0.0f, 0.0f)).GetY(),
        layoutProperty->GetIndicatorOffsetValue().ConvertToPx());
    /**
     * @tc.steps: step5. test pattern drag function
     */
    pattern->HandleDragStart();
    EXPECT_EQ(stateChangeValue, static_cast<int>(RefreshStatus::DRAG));
    pattern->HandleDragUpdate(100.0f);
    pattern->HandleDragEnd();
    EXPECT_EQ(stateChangeValue, static_cast<int>(RefreshStatus::INACTIVE));
    pattern->HandleDragCancel();
    EXPECT_EQ(layoutProperty->GetScrollableOffsetValue().GetY(), 0.0f);
}

/**
 * @tc.name: RefreshTest003
 * @tc.desc: Test setting of default.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and get frameNode of refresh.
     */
    auto frameNode = CreateRefreshNode();
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::REFRESH_ETS_TAG);
    /**
     * @tc.steps: step2. get property object and test default param of refresh.
     */
    RefPtr<RefreshLayoutProperty> layoutProperty = frameNode->GetLayoutProperty<RefreshLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetIndicatorOffsetValue(), Dimension(DEFAULT_INDICATOR_OFFSET, DimensionUnit::VP));
    EXPECT_EQ(layoutProperty->GetFrictionValue(), DEFAULT_FRICTION_RATIO);
}

/**
 * @tc.name: RefreshTest004
 * @tc.desc: Test setting of refresh.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and get frameNode of refresh.
     */
    auto frameNode = CreateRefreshNodeAndInitParam();
    EXPECT_NE(frameNode, nullptr);
    RefPtr<RefreshLayoutProperty> layoutProperty = frameNode->GetLayoutProperty<RefreshLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step3. test param model interface of refresh.
     */
    EXPECT_EQ(layoutProperty->GetLoadingDistanceValue(Dimension(0, DimensionUnit::PX)), loadingDistance);
    EXPECT_EQ(layoutProperty->GetRefreshDistanceValue(Dimension(0, DimensionUnit::PX)), refreshDistance);
    EXPECT_EQ(layoutProperty->GetProgressDistanceValue(Dimension(0, DimensionUnit::PX)), progressDistance);
    EXPECT_EQ(layoutProperty->GetProgressDiameterValue(Dimension(0, DimensionUnit::PX)), progressDiameter);
    EXPECT_EQ(layoutProperty->GetMaxDistanceValue(Dimension(0, DimensionUnit::PX)), maxDistance);
    EXPECT_EQ(layoutProperty->GetShowTimeDistanceValue(Dimension(0, DimensionUnit::PX)), showTimeDistance);
    EXPECT_EQ(layoutProperty->GetMaxDistanceValue(Dimension(0, DimensionUnit::PX)), maxDistance);
    EXPECT_EQ(layoutProperty->GetProgressColorValue(Color::TRANSPARENT), COLOR_VALUE);
    EXPECT_EQ(layoutProperty->GetProgressColorValue(Color::TRANSPARENT), COLOR_VALUE);
}

/**
 * @tc.name: RefreshTest005
 * @tc.desc: Test setting of refresh.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and get model object of refresh.
     */
    RefreshModelNG modelNG;
    modelNG.Create();
    modelNG.SetIsShowLastTime(false);
    modelNG.Pop();
    modelNG.Pop();
    /**
     * @tc.steps: step2. set callback object by  model object of refresh.
     */
    std::string changeEventValue;
    auto onChangeEvent = [&changeEventValue](const std::string& param) { changeEventValue = param; };
    modelNG.SetChangeEvent(std::move(onChangeEvent));
    int32_t stateChangeValue = -1;
    auto onStateChangeEvent = [&stateChangeValue](const int32_t param) { stateChangeValue = param; };
    modelNG.SetOnStateChange(std::move(onStateChangeEvent));
    bool refreshingValue = false;
    auto onRefreshingEvent = [&refreshingValue]() { refreshingValue = true; };
    modelNG.SetOnRefreshing(std::move(onRefreshingEvent));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step3. test event function with pattern
     */
    RefPtr<RefreshPattern> pattern = frameNode->GetPattern<RefreshPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->FireRefreshing();
    EXPECT_EQ(refreshingValue, true);
    pattern->FireChangeEvent("true");
    EXPECT_EQ(changeEventValue, "true");
    pattern->FireStateChange(0);
    EXPECT_EQ(stateChangeValue, 0);
}

/**
 * @tc.name: RefreshTest006
 * @tc.desc: Test refresh object create by pattern.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest006, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    modelNG.SetIsShowLastTime(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::REFRESH_ETS_TAG);
    EXPECT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step3. test callback object by pattern object of refresh.
     */
    RefPtr<RefreshPattern> pattern = frameNode->GetPattern<RefreshPattern>();
    EXPECT_NE(pattern, nullptr);
    auto atomicNode = pattern->IsAtomicNode();
    EXPECT_EQ(atomicNode, false);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    EXPECT_NE(layoutAlgorithm, nullptr);
    auto layoutProperty = pattern->CreateLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    auto paintProperty = pattern->CreatePaintProperty();
    EXPECT_NE(paintProperty, nullptr);
    auto eventHub = pattern->CreateEventHub();
    EXPECT_NE(eventHub, nullptr);
}

/**
 * @tc.name: RefreshTest007
 * @tc.desc: Test measure and Layout of refresh.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and get frameNode of refresh.
     */
    auto frameNode = CreateRefreshNode();
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::REFRESH_ETS_TAG);
    /**
     * @tc.steps: step2. Create LayoutWrapper and set ratingLayoutAlgorithm.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto refreshLayoutProperty = frameNode->GetLayoutProperty<RefreshLayoutProperty>();
    EXPECT_NE(refreshLayoutProperty, nullptr);
    auto refreshPattern = frameNode->GetPattern<RefreshPattern>();
    EXPECT_NE(refreshPattern, nullptr);
    auto refreshLayoutAlgorithm = refreshPattern->CreateLayoutAlgorithm();
    EXPECT_NE(refreshLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(refreshLayoutAlgorithm));
    /**
     * @tc.steps: step3. Refresh without setting height and width.
     */
    const LayoutConstraintF layoutConstraint;
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    /**
     * @tc.steps: step4. Calculate the size and offset.
     */
    refreshLayoutAlgorithm->Measure(&layoutWrapper);
    refreshLayoutAlgorithm->Layout(&layoutWrapper);
    /**
     * @tc.steps: step5. Test the default size set in theme and the offset.
     */
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameSize(), SizeF(0.0f, 0.0f));
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameOffset(), OffsetF(0.0f, 0.0f));
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetSize(CONTAINER_SIZE);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraintSize);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    refreshLayoutAlgorithm->Measure(&layoutWrapper);
    /**
     * @tc.steps: step6. Test the size set by codes.
     */
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameSize(), SizeF(CONTAINER_SIZE));
}

/**
 * @tc.name: RefreshTest008
 * @tc.desc: Test MeasureContent of refresh.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and get frameNode of refresh.
     */
    auto frameNode = CreateRefreshNode();
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::REFRESH_ETS_TAG);
    /**
     * @tc.steps: step2. test some object of refresh.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto refreshPattern = frameNode->GetPattern<RefreshPattern>();
    EXPECT_NE(refreshPattern, nullptr);
    auto refreshLayoutAlgorithm = refreshPattern->CreateLayoutAlgorithm();
    EXPECT_NE(refreshLayoutAlgorithm, nullptr);
    auto layoutAlgorithm = refreshPattern->CreateLayoutAlgorithm();
    EXPECT_NE(layoutAlgorithm, nullptr);
    /**
     * @tc.steps: step3. build the layoutWrapper of refresh.
     */
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    EXPECT_NE(layoutWrapper.GetLayoutProperty(), nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = MAX_SIZE;
    /**
     * @tc.steps: step4. test MeasureContent of refresh.
     */
    auto refreshSize = layoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper);
    EXPECT_EQ(refreshSize.value_or(SizeF(0.0f, 0.0f)), MAX_SIZE);

    layoutConstraint.selfIdealSize.SetSize(IDEAL_SIZE);
    refreshSize = layoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper);
    EXPECT_EQ(refreshSize.value_or(SizeF(0.0f, 0.0f)), IDEAL_SIZE);
}

/**
 * @tc.name: RefreshTest009
 * @tc.desc: test status change of refresh.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and get frameNode of refresh.
     */
    auto frameNode = CreateRefreshNodeAndInitParam();
    EXPECT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. set callback function by eventHub
     */
    RefPtr<RefreshEventHub> eventHub = frameNode->GetEventHub<RefreshEventHub>();
    EXPECT_NE(eventHub, nullptr);
    int32_t stateChangeValue = -1;
    auto onStateChangeEvent = [&stateChangeValue](const int32_t param) { stateChangeValue = param; };
    eventHub->SetOnStateChange(std::move(onStateChangeEvent));
    bool refreshingValue = false;
    auto onRefreshingEvent = [&refreshingValue]() { refreshingValue = true; };
    eventHub->SetOnRefreshing(std::move(onRefreshingEvent));
    /**
     * @tc.steps: step3. test refresh status
     */
    RefPtr<RefreshPattern> pattern = frameNode->GetPattern<RefreshPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->OnModifyDone();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    EXPECT_NE(layoutWrapper, nullptr);
    RefPtr<RefreshLayoutProperty> layoutProperty = frameNode->GetLayoutProperty<RefreshLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step4. test refresh status for default
     */
    pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, true);
    EXPECT_EQ(stateChangeValue, static_cast<int>(RefreshStatus::INACTIVE));
    /**
     * @tc.steps: step4. test refresh status for DRAG
     */
    pattern->HandleDragStart();
    pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, true);
    EXPECT_EQ(stateChangeValue, static_cast<int>(RefreshStatus::INACTIVE));
    pattern->HandleDragStart();
    layoutProperty->UpdateScrollableOffset(
        OffsetF(0.0f, static_cast<float>(layoutProperty->GetTriggerRefreshDistanceValue().ConvertToPx() - 1)));
    pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, true);
    EXPECT_EQ(stateChangeValue, static_cast<int>(RefreshStatus::DRAG));
}

/**
 * @tc.name: RefreshTest010
 * @tc.desc: test status change of refresh.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and get frameNode of refresh.
     */
    auto frameNode = CreateRefreshNodeAndInitParam();
    EXPECT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. set callback function by eventHub
     */
    RefPtr<RefreshEventHub> eventHub = frameNode->GetEventHub<RefreshEventHub>();
    EXPECT_NE(eventHub, nullptr);
    int32_t stateChangeValue = -1;
    auto onStateChangeEvent = [&stateChangeValue](const int32_t param) { stateChangeValue = param; };
    eventHub->SetOnStateChange(std::move(onStateChangeEvent));
    bool refreshingValue = false;
    auto onRefreshingEvent = [&refreshingValue]() { refreshingValue = true; };
    eventHub->SetOnRefreshing(std::move(onRefreshingEvent));
    /**
     * @tc.steps: step3. test refresh status
     */
    RefPtr<RefreshPattern> pattern = frameNode->GetPattern<RefreshPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->OnModifyDone();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    EXPECT_NE(layoutWrapper, nullptr);
    RefPtr<RefreshLayoutProperty> layoutProperty = frameNode->GetLayoutProperty<RefreshLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    pattern->HandleDragStart();
    layoutProperty->UpdateScrollableOffset(
        OffsetF(0.0f, static_cast<float>(layoutProperty->GetTriggerRefreshDistanceValue().ConvertToPx())));
    pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, true);
    EXPECT_EQ(stateChangeValue, static_cast<int>(RefreshStatus::OVER_DRAG));
    /**
     * @tc.steps: step4. test refresh status for OVER_DRAG
     */
    pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, true);
    EXPECT_EQ(stateChangeValue, static_cast<int>(RefreshStatus::OVER_DRAG));
    layoutProperty->UpdateScrollableOffset(
        OffsetF(0.0f, static_cast<float>(layoutProperty->GetTriggerRefreshDistanceValue().ConvertToPx() - 1)));
    pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, true);
    EXPECT_EQ(stateChangeValue, static_cast<int>(RefreshStatus::DRAG));
    layoutProperty->UpdateScrollableOffset(
        OffsetF(0.0f, static_cast<float>(layoutProperty->GetTriggerRefreshDistanceValue().ConvertToPx())));
    pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, true);
    EXPECT_EQ(stateChangeValue, static_cast<int>(RefreshStatus::OVER_DRAG));
    layoutProperty->UpdateScrollableOffset(OffsetF(0.0f, 0.0f));
    pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, true);
    EXPECT_EQ(stateChangeValue, static_cast<int>(RefreshStatus::INACTIVE));
}
} // namespace OHOS::Ace::NG
