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
    RefPtr<RefreshPattern> pattern = frameNode->GetPattern<RefreshPattern>();
    EXPECT_NE(pattern, nullptr);
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
HWTEST_F(RefreshPatternTestNg, RefreshModelTest003, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    modelNG.SetIsShowLastTime(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    RefPtr<RefreshLayoutProperty> layoutProperty = frameNode->GetLayoutProperty<RefreshLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    Dimension loadingDistance = Dimension(DEFAULT_PARAM, DimensionUnit::VP);
    modelNG.SetLoadingDistance(loadingDistance);
    EXPECT_EQ(layoutProperty->GetLoadingDistanceValue(Dimension(0, DimensionUnit::VP)).ConvertToPx(),
        loadingDistance.ConvertToPx());

    Dimension refreshDistance = Dimension(DEFAULT_PARAM, DimensionUnit::VP);
    modelNG.SetRefreshDistance(refreshDistance);
    EXPECT_EQ(layoutProperty->GetRefreshDistanceValue(Dimension(0, DimensionUnit::VP)).ConvertToPx(),
        refreshDistance.ConvertToPx());

    Dimension progressDistance = Dimension(DEFAULT_PARAM, DimensionUnit::VP);
    modelNG.SetProgressDistance(progressDistance);
    EXPECT_EQ(layoutProperty->GetProgressDistanceValue(Dimension(0, DimensionUnit::VP)).ConvertToPx(),
        progressDistance.ConvertToPx());

    Dimension progressDiameter = Dimension(DEFAULT_PARAM, DimensionUnit::VP);
    modelNG.SetProgressDiameter(progressDiameter);
    EXPECT_EQ(layoutProperty->GetProgressDiameterValue(Dimension(0, DimensionUnit::VP)).ConvertToPx(),
        progressDiameter.ConvertToPx());

    Dimension maxDistance = Dimension(DEFAULT_PARAM, DimensionUnit::VP);
    modelNG.SetMaxDistance(maxDistance);
    EXPECT_EQ(
        layoutProperty->GetMaxDistanceValue(Dimension(0, DimensionUnit::VP)).ConvertToPx(), maxDistance.ConvertToPx());

    Dimension showTimeDistance = Dimension(DEFAULT_PARAM, DimensionUnit::VP);
    modelNG.SetShowTimeDistance(showTimeDistance);
    EXPECT_EQ(layoutProperty->GetShowTimeDistanceValue(Dimension(0, DimensionUnit::VP)).ConvertToPx(),
        showTimeDistance.ConvertToPx());
}
} // namespace OHOS::Ace::NG
