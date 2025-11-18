/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include <cstddef>
#include <optional>
#include <string>
#include <utility>

#include "gtest/gtest.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/container_picker/container_picker_layout_property.h"
#include "core/components_ng/pattern/container_picker/container_picker_paint_method.h"
#include "core/components_ng/pattern/container_picker/container_picker_pattern.h"
#include "core/components_ng/pattern/container_picker/container_picker_theme.h"
#include "core/components_ng/pattern/container_picker/container_picker_utils.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/pipeline/base/element_register.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Testing;

namespace OHOS::Ace::NG {

class ContainerPickerPaintMethodTest : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    
    RefPtr<FrameNode> CreateContainerPickerNode();
    RefPtr<MockCanvas> CreateMockCanvas();
    RefPtr<PaintWrapper> CreateMockPaintWrapper(const RefPtr<FrameNode>& node);
    
    RefPtr<ContainerPickerPaintMethod> paintMethod_;
    RefPtr<PickerTheme> mockTheme_;
};

void ContainerPickerPaintMethodTest::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<ContainerPickerTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
}

void ContainerPickerPaintMethodTest::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    TestNG::TearDownTestSuite();
}

void ContainerPickerPaintMethodTest::SetUp()
{
    TestNG::SetUp();
    paintMethod_ = AceType::MakeRefPtr<ContainerPickerPaintMethod>();
    mockTheme_ = AceType::MakeRefPtr<PickerTheme>();
}

void ContainerPickerPaintMethodTest::TearDown()
{
    TestNG::TearDown();
    paintMethod_ = nullptr;
    mockTheme_ = nullptr;
}

RefPtr<FrameNode> ContainerPickerPaintMethodTest::CreateContainerPickerNode()
{
    ContainerPickerModel picker;
    picker.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_NE(frameNode, nullptr);

    return frameNode;
}

RefPtr<PaintWrapper> ContainerPickerPaintMethodTest::CreateMockPaintWrapper(const RefPtr<FrameNode>& node)
{
    EXPECT_NE(node, nullptr);
    auto paintProperty = node->GetPaintProperty<PaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
    auto geometryNode = node->GetGeometryNode();
    EXPECT_NE(geometryNode, nullptr);
    auto renderContext = node->GetRenderContext();
    EXPECT_NE(renderContext, nullptr);
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);
    EXPECT_NE(paintWrapper, nullptr);

    return paintWrapper;
}

/**
 * @tc.name: GetForegroundDrawFunctionTest001
 * @tc.desc: Test ContainerPickerPaintMethod GetForegroundDrawFunction
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPaintMethodTest, GetForegroundDrawFunctionTest001, TestSize.Level1)
{
    auto node = CreateContainerPickerNode();
    auto paintWrapper = CreateMockPaintWrapper(node);
    Testing::MockCanvas rsCanvas;
    
    // Set indicator type to divider
    auto layoutProperty = node->GetLayoutProperty<ContainerPickerLayoutProperty>();
    layoutProperty->UpdateIndicatorType(static_cast<int32_t>(PickerIndicatorType::DIVIDER));
    
    auto drawFunction = paintMethod_->GetForegroundDrawFunction(AceType::RawPtr(paintWrapper));
    ASSERT_NE(drawFunction, nullptr);
    
    // Test with valid canvas
    drawFunction(rsCanvas);
}

/**
 * @tc.name: ClipPaddingTest001
 * @tc.desc: Test ContainerPickerPaintMethod ClipPadding
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPaintMethodTest, ClipPaddingTest001, TestSize.Level1)
{
    auto node = CreateContainerPickerNode();
    auto paintWrapper = CreateMockPaintWrapper(node);
    Testing::MockCanvas rsCanvas;
    
    EXPECT_CALL(rsCanvas, ClipRect(_, _, _)).Times(1);
    
    paintMethod_->ClipPadding(AceType::RawPtr(paintWrapper), rsCanvas);
}

/**
 * @tc.name: ClipPaddingTest002
 * @tc.desc: Test ContainerPickerPaintMethod ClipPadding with safe area padding
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPaintMethodTest, ClipPaddingTest002, TestSize.Level1)
{
    auto node = CreateContainerPickerNode();
    auto paintWrapper = CreateMockPaintWrapper(node);
    Testing::MockCanvas rsCanvas;
    
    // Set safe area padding
    PaddingPropertyF safeAreaPadding;
    safeAreaPadding.left = 20.0f;
    safeAreaPadding.right = 20.0f;
    paintMethod_->SetSafeAreaPadding(safeAreaPadding);
    
    EXPECT_CALL(rsCanvas, ClipRect(_, _, _)).Times(1);
    
    paintMethod_->ClipPadding(AceType::RawPtr(paintWrapper), rsCanvas);
}

/**
 * @tc.name: PaintSelectionIndicatorBackgroundTest001
 * @tc.desc: Test ContainerPickerPaintMethod PaintSelectionIndicatorBackground with wrong indicator type
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPaintMethodTest, PaintSelectionIndicatorBackgroundTest001, TestSize.Level1)
{
    auto node = CreateContainerPickerNode();
    auto paintWrapper = CreateMockPaintWrapper(node);
    Testing::MockCanvas rsCanvas;
    
    // Set indicator type to divider
    auto layoutProperty = node->GetLayoutProperty<ContainerPickerLayoutProperty>();
    layoutProperty->UpdateIndicatorType(static_cast<int32_t>(PickerIndicatorType::DIVIDER));
    
    // Should not call any canvas methods
    EXPECT_CALL(rsCanvas, Save()).Times(0);
    EXPECT_CALL(rsCanvas, DrawRoundRect(_)).Times(0);
    
    paintMethod_->PaintSelectionIndicatorBackground(AceType::RawPtr(paintWrapper), rsCanvas);
}

/**
 * @tc.name: PaintSelectionIndicatorDividerTest001
 * @tc.desc: Test ContainerPickerPaintMethod PaintSelectionIndicatorDivider with wrong indicator type
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPaintMethodTest, PaintSelectionIndicatorDividerTest001, TestSize.Level1)
{
    auto node = CreateContainerPickerNode();
    auto paintWrapper = CreateMockPaintWrapper(node);
    Testing::MockCanvas rsCanvas;
    
    // Set indicator type to background
    auto layoutProperty = node->GetLayoutProperty<ContainerPickerLayoutProperty>();
    layoutProperty->UpdateIndicatorType(static_cast<int32_t>(PickerIndicatorType::BACKGROUND));
    
    // Should not call DrawLine
    EXPECT_CALL(rsCanvas, DrawLine(_, _)).Times(0);
    
    paintMethod_->PaintSelectionIndicatorDivider(AceType::RawPtr(paintWrapper), rsCanvas);
}

/**
 * @tc.name: CheckMarginAndLengthTest001
 * @tc.desc: Test ContainerPickerPaintMethod CheckMarginAndLength with normal margins
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPaintMethodTest, CheckMarginAndLengthTest001, TestSize.Level1)
{
    float length = 100.0f;
    double startMargin = 10.0f;
    double endMargin = 10.0f;
    
    paintMethod_->CheckMarginAndLength(length, startMargin, endMargin);
    
    EXPECT_FLOAT_EQ(length, 80.0f);
    EXPECT_FLOAT_EQ(startMargin, 10.0f);
    EXPECT_FLOAT_EQ(endMargin, 10.0f);
}

/**
 * @tc.name: CheckMarginAndLengthTest002
 * @tc.desc: Test ContainerPickerPaintMethod CheckMarginAndLength with margins exceeding length
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPaintMethodTest, CheckMarginAndLengthTest002, TestSize.Level1)
{
    float length = 100.0f;
    double startMargin = 60.0f;
    double endMargin = 60.0f;
    
    paintMethod_->CheckMarginAndLength(length, startMargin, endMargin);
    
    // Margins should be reset to default
    EXPECT_FLOAT_EQ(startMargin, 0.0);
    EXPECT_FLOAT_EQ(endMargin, 0.0);
    EXPECT_FLOAT_EQ(length, 100.0f);
}

/**
 * @tc.name: CheckMarginAndLengthTest003
 * @tc.desc: Test ContainerPickerPaintMethod CheckMarginAndLength with RTL mode
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPaintMethodTest, CheckMarginAndLengthTest003, TestSize.Level1)
{
    // Save original RTL setting
    bool originalRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
    
    // Set RTL mode
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    
    float length = 100.0f;
    double startMargin = 10.0f;
    double endMargin = 20.0f;
    
    paintMethod_->CheckMarginAndLength(length, startMargin, endMargin);
    
    // Margins should be swapped in RTL mode
    EXPECT_FLOAT_EQ(startMargin, 20.0f);
    EXPECT_FLOAT_EQ(endMargin, 10.0f);
    EXPECT_FLOAT_EQ(length, 70.0f);
    
    // Restore original RTL setting
    AceApplicationInfo::GetInstance().isRightToLeft_ = originalRtl;
}

/**
 * @tc.name: PaintSelectionIndicatorDividerTest002
 * @tc.desc: Test ContainerPickerPaintMethod PaintSelectionIndicatorDivider with stroke width limitation
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPaintMethodTest, PaintSelectionIndicatorDividerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ContainerPicker
     */
    auto node = CreateContainerPickerNode();
    auto paintWrapper = CreateMockPaintWrapper(node);
    Testing::MockCanvas rsCanvas;

    // Set indicator type to divider
    auto layoutProperty = node->GetLayoutProperty<ContainerPickerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateIndicatorType(static_cast<int32_t>(PickerIndicatorType::DIVIDER));

    // Mock pipeline context and theme
    auto pipelineContext = MockPipelineContext::GetCurrent();
    float defaultThickness = 2.0f;
    mockTheme_->dividerThickness_ = Dimension(defaultThickness);

    /**
     * @tc.steps: step2. Test with stroke width equal to half of item height
     * @tc.expected: step2. Stroke width should remain as set, not be reset to default
     */
    float itemHeightHalf = PICKER_ITEM_HEIGHT.ConvertToPx() / HALF;
    layoutProperty->UpdateIndicatorDividerWidth(Dimension(itemHeightHalf));
    EXPECT_CALL(rsCanvas, DrawRect(_)).Times(AnyNumber());
    EXPECT_CALL(rsCanvas, DetachBrush()).Times(AnyNumber());
    paintMethod_->PaintSelectionIndicatorDivider(AceType::RawPtr(paintWrapper), rsCanvas);

    /**
     * @tc.steps: step3. Test with stroke width greater than half of item height
     * @tc.expected: step3. Stroke width should be reset to default
     */
    float excessiveWidth = itemHeightHalf + 1.0f;
    layoutProperty->UpdateIndicatorDividerWidth(Dimension(excessiveWidth));
    paintMethod_->PaintSelectionIndicatorDivider(AceType::RawPtr(paintWrapper), rsCanvas);
}

/**
 * @tc.name: PaintLineWithNormalParametersTest
 * @tc.desc: Test ContainerPickerPaintMethod PaintLine with normal parameters
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPaintMethodTest, PaintLineWithNormalParametersTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create mock canvas and set up PaintLine parameters
     */
    Testing::MockCanvas rsCanvas;
    OffsetF offset(10.0f, 20.0f);
    PickerDividerPaintInfo dividerInfo;
    dividerInfo.dividerLength = 100.0f;
    dividerInfo.strokeWidth = 2.0f;
    dividerInfo.dividerColor = Color::RED;

    /**
     * @tc.steps: step2. Mock canvas operations
     */
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Save()).Times(1);
    EXPECT_CALL(rsCanvas, DrawRect(_)).Times(1);

    /**
     * @tc.steps: step3. Call PaintLine method
     * @tc.expected: step3. Canvas methods should be called with correct parameters
     */
    paintMethod_->PaintLine(offset, dividerInfo, rsCanvas);
}

/**
 * @tc.name: PaintSelectionIndicatorBackgroundWithPaddingTest
 * @tc.desc: Test ContainerPickerPaintMethod PaintSelectionIndicatorBackground with padding
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPaintMethodTest, PaintSelectionIndicatorBackgroundWithPaddingTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ContainerPicker with background indicator type and padding
     */
    auto node = CreateContainerPickerNode();
    auto paintWrapper = CreateMockPaintWrapper(node);
    Testing::MockCanvas rsCanvas;

    auto layoutProperty = node->GetLayoutProperty<ContainerPickerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateIndicatorType(static_cast<int32_t>(PickerIndicatorType::BACKGROUND));

    PaddingProperty padding;
    padding.left = CalcLength(20.0f);
    padding.right = CalcLength(20.0f);
    padding.top = CalcLength(10.0f);
    padding.bottom = CalcLength(10.0f);
    layoutProperty->UpdatePadding(padding);

    auto geometryNode = node->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(300.0f, 500.0f));

    /**
     * @tc.steps: step2. Mock canvas operations
     */
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Save()).Times(1);
    EXPECT_CALL(rsCanvas, DrawRoundRect(_)).Times(1);
    EXPECT_CALL(rsCanvas, Restore()).Times(1);

    /**
     * @tc.steps: step3. Call PaintSelectionIndicatorBackground method
     * @tc.expected: step3. Should use contentRect with padding applied
     */
    paintMethod_->PaintSelectionIndicatorBackground(AceType::RawPtr(paintWrapper), rsCanvas);
}

} // namespace OHOS::Ace::NG
