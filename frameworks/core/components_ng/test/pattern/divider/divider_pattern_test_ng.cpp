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

#include "core/components/common/properties/color.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/divider/divider_layout_algorithm.h"
#include "core/components_ng/pattern/divider/divider_layout_property.h"
#include "core/components_ng/pattern/divider/divider_model_ng.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/divider/divider_render_property.h"
#include "core/components_ng/test/pattern/divider/mock/mock_layout_wrapper.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const bool VERTICAL = true;
const Color DIVIDER_COLOR = Color(0xff000000);
const Dimension STROKE_WIDTH = Dimension(1.0, DimensionUnit::VP);
const Ace::LineCap LINE_CAP = Ace::LineCap::BUTT;
const OptionalSize<float> SELF_IDEAL_SIZE = OptionalSize(100.0f, 100.0f);
const SizeT<float> MAX_SIZE = SizeT<float>(1000.0f, 1000.0f);
} // namespace

struct TestProperty {
    std::optional<bool> vertical = std::nullopt;
    std::optional<Color> dividerColor = std::nullopt;
    std::optional<Dimension> strokeWidth = std::nullopt;
    std::optional<Ace::LineCap> lineCap = std::nullopt;
};

class DividerPatternTestNg : public testing::Test {
public:
protected:
    static RefPtr<FrameNode> CreateDividerNode(TestProperty& testProperty);
};

RefPtr<FrameNode> DividerPatternTestNg::CreateDividerNode(TestProperty& testProperty)
{
    DividerModelNG().Create();
    if (testProperty.vertical.has_value()) {
        DividerModelNG().Vertical(testProperty.vertical.value());
    }
    if (testProperty.dividerColor.has_value()) {
        DividerModelNG().DividerColor(testProperty.dividerColor.value());
    }
    if (testProperty.strokeWidth.has_value()) {
        DividerModelNG().StrokeWidth(testProperty.strokeWidth.value());
    }
    if (testProperty.lineCap.has_value()) {
        DividerModelNG().LineCap(testProperty.lineCap.value());
    }

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish(); // TextView pop
    return AceType::DynamicCast<FrameNode>(element);
}

/**
 * @tc.name: DividerFrameNodeCreator001
 * @tc.desc: Test all the property of divider.
 * @tc.type: FUNC
 */
HWTEST_F(DividerPatternTestNg, DividerFrameNodeCreator001, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.vertical = VERTICAL;
    testProperty.dividerColor = DIVIDER_COLOR;
    testProperty.strokeWidth = STROKE_WIDTH;
    testProperty.lineCap = LINE_CAP;

    RefPtr<FrameNode> frameNode = CreateDividerNode(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<DividerLayoutProperty> layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetVerticalValue(), VERTICAL);
    EXPECT_EQ(layoutProperty->GetStrokeWidthValue(), STROKE_WIDTH);
    RefPtr<DividerRenderProperty> paintProperty = frameNode->GetPaintProperty<DividerRenderProperty>();
    EXPECT_EQ(paintProperty->GetDividerColorValue(), DIVIDER_COLOR);
    EXPECT_EQ(paintProperty->GetLineCapValue(), LINE_CAP);
}

/**
 * @tc.name: DividerFrameNodeCreator002
 * @tc.desc: Test all the layoutAlgorithm of divider.
 * @tc.type: FUNC
 */
HWTEST_F(DividerPatternTestNg, DividerFrameNodeCreator002, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.vertical = VERTICAL;
    testProperty.strokeWidth = STROKE_WIDTH;

    RefPtr<FrameNode> frameNode = CreateDividerNode(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<DividerLayoutProperty> layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, layoutProperty);
    RefPtr<DividerLayoutAlgorithm> dividerLayoutAlgorithm = AceType::MakeRefPtr<DividerLayoutAlgorithm>();
    LayoutConstraintF layoutConstraintF;
    layoutConstraintF.selfIdealSize = SELF_IDEAL_SIZE;
    layoutConstraintF.maxSize = MAX_SIZE;
    std::optional<SizeF> constrainSize = dividerLayoutAlgorithm->MeasureContent(layoutConstraintF, &layoutWrapper);
    EXPECT_NE(constrainSize, std::nullopt);

    RefPtr<MockLayoutAlgorithmWrapper> mockLayoutAlgorithmWrapper = AceType::MakeRefPtr<MockLayoutAlgorithmWrapper>();
    EXPECT_CALL(*mockLayoutAlgorithmWrapper, GetLayoutAlgorithm())
        .WillRepeatedly(testing::Return(dividerLayoutAlgorithm));
    RefPtr<MockLayoutWrapper> mockLayoutWrapper = AceType::MakeRefPtr<MockLayoutWrapper>();
    EXPECT_CALL(*mockLayoutWrapper, SkipMeasureContent()).WillRepeatedly(testing::Return(false));
    EXPECT_CALL(*mockLayoutWrapper, GetLayoutAlgorithm()).WillRepeatedly(testing::Return(mockLayoutAlgorithmWrapper));
    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    RefPtr<DividerPattern> dividerPattern = frameNode->GetPattern<DividerPattern>();
    EXPECT_NE(dividerPattern, nullptr);
    bool OnDirtyLayoutWrapperSwapFlag = dividerPattern->OnDirtyLayoutWrapperSwap(mockLayoutWrapper, dirtySwapConfig);
    EXPECT_EQ(OnDirtyLayoutWrapperSwapFlag, true);
    EXPECT_EQ(dividerPattern->vertical_, VERTICAL);
}
} // namespace OHOS::Ace::NG