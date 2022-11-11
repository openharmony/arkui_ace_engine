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

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
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
constexpr double DEFAULT_INDICATOR_OFFSET = 16.0;
constexpr int32_t DEFAULT_FRICTION_RATIO = 42;
constexpr int32_t DEFAULT_PARAM = 100;
const float CONTAINER_WIDTH = 300.0f;
const float CONTAINER_HEIGHT = 300.0f;
const SizeF CONTAINER_SIZE(CONTAINER_WIDTH, CONTAINER_HEIGHT);
} // namespace
class RefreshPatternTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: RefreshObjectTest001
 * @tc.desc: Create Rating.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshObjectTest001, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    modelNG.SetIsShowLastTime(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::REFRESH_ETS_TAG);
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
    eventHub->FireOnRefreshing();
    EXPECT_EQ(refreshingValue, true);
    eventHub->FireChangeEvent("true");
    EXPECT_EQ(changeEventValue, "true");
    eventHub->FireOnStateChange(0);
    EXPECT_EQ(stateChangeValue, 0);
}

/**
 * @tc.name: RefreshObjectTest002
 * @tc.desc: Test setting of object.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshObjectTest002, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    modelNG.SetIsShowLastTime(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::REFRESH_ETS_TAG);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty<RefreshLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<RefreshRenderProperty> paintProperty = frameNode->GetPaintProperty<RefreshRenderProperty>();
    EXPECT_NE(paintProperty, nullptr);
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
 * @tc.name: RefreshModelTest001
 * @tc.desc: Test setting of default.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshModelTest001, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    modelNG.SetIsShowLastTime(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    RefPtr<RefreshLayoutProperty> layoutProperty = frameNode->GetLayoutProperty<RefreshLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetIndicatorOffsetValue(), Dimension(DEFAULT_INDICATOR_OFFSET, DimensionUnit::VP));
    EXPECT_EQ(layoutProperty->GetFrictionValue(), DEFAULT_FRICTION_RATIO);
}

/**
 * @tc.name: RefreshModelTest002
 * @tc.desc: Test setting of refresh.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshModelTest002, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    modelNG.SetIsShowLastTime(false);
    Dimension refreshDistance = Dimension(DEFAULT_PARAM, DimensionUnit::VP);
    modelNG.SetRefreshDistance(refreshDistance);
    Dimension loadingDistance = Dimension(DEFAULT_PARAM, DimensionUnit::VP);
    modelNG.SetLoadingDistance(loadingDistance);
    Dimension progressDistance = Dimension(DEFAULT_PARAM, DimensionUnit::VP);
    modelNG.SetProgressDistance(progressDistance);
    Dimension progressDiameter = Dimension(DEFAULT_PARAM, DimensionUnit::VP);
    modelNG.SetProgressDiameter(progressDiameter);
    Dimension maxDistance = Dimension(DEFAULT_PARAM, DimensionUnit::VP);
    modelNG.SetMaxDistance(maxDistance);
    Dimension showTimeDistance = Dimension(DEFAULT_PARAM, DimensionUnit::VP);
    modelNG.SetShowTimeDistance(showTimeDistance);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    RefPtr<RefreshLayoutProperty> layoutProperty = frameNode->GetLayoutProperty<RefreshLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetLoadingDistanceValue(Dimension(0, DimensionUnit::VP)).ConvertToPx(),
        loadingDistance.ConvertToPx());
    EXPECT_EQ(layoutProperty->GetRefreshDistanceValue(Dimension(0, DimensionUnit::VP)).ConvertToPx(),
        refreshDistance.ConvertToPx());
    EXPECT_EQ(layoutProperty->GetProgressDistanceValue(Dimension(0, DimensionUnit::VP)).ConvertToPx(),
        progressDistance.ConvertToPx());
    EXPECT_EQ(layoutProperty->GetProgressDiameterValue(Dimension(0, DimensionUnit::VP)).ConvertToPx(),
        progressDiameter.ConvertToPx());
    EXPECT_EQ(
        layoutProperty->GetMaxDistanceValue(Dimension(0, DimensionUnit::VP)).ConvertToPx(), maxDistance.ConvertToPx());
    EXPECT_EQ(layoutProperty->GetShowTimeDistanceValue(Dimension(0, DimensionUnit::VP)).ConvertToPx(),
        showTimeDistance.ConvertToPx());
}

/**
 * @tc.name: RefreshModelTest003
 * @tc.desc: Test setting of refresh.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshModelTest003, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    modelNG.SetIsShowLastTime(false);
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
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::REFRESH_ETS_TAG);
    EXPECT_NE(frameNode, nullptr);

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
 * @tc.name: RefreshPatternTest001
 * @tc.desc: Test setting of refresh.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshPatternTest001, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    modelNG.SetIsShowLastTime(false);
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
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::REFRESH_ETS_TAG);
    EXPECT_NE(frameNode, nullptr);

    RefPtr<RefreshPattern> pattern = frameNode->GetPattern<RefreshPattern>();
    EXPECT_NE(pattern, nullptr);
    auto atomicNode = pattern->IsAtomicNode();
    EXPECT_EQ(atomicNode, false);
}

/**
 * @tc.name: RefreshPatternTest001
 * @tc.desc: Test setting of refresh.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshPatternTest002, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    modelNG.SetIsShowLastTime(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::REFRESH_ETS_TAG);

    // Create LayoutWrapper and set ratingLayoutAlgorithm.
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto refreshLayoutProperty = frameNode->GetLayoutProperty<RefreshLayoutProperty>();
    auto refreshPattern = frameNode->GetPattern<RefreshPattern>();
    EXPECT_FALSE(refreshPattern == nullptr);
    auto refreshLayoutAlgorithm = refreshPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(refreshLayoutAlgorithm == nullptr);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(refreshLayoutAlgorithm));

    // Refresh without setting height and width.
    const LayoutConstraintF layoutConstraint;
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    // Calculate the size and offset.
    refreshLayoutAlgorithm->Measure(&layoutWrapper);
    refreshLayoutAlgorithm->Layout(&layoutWrapper);
    // Test the default size set in theme and the offset.
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameSize(), SizeF(0, 0));
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameOffset(), OffsetF(0.0, 0.0));
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetSize(CONTAINER_SIZE);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraintSize);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    refreshLayoutAlgorithm->Measure(&layoutWrapper);
    // Test the size set by codes.
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameSize(), SizeF(CONTAINER_SIZE));
}
} // namespace OHOS::Ace::NG
