/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#define protected public
#define private public
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/rosen/mock_canvas.h"

#include "base/geometry/dimension.h"
#include "core/common/ace_application_info.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components/toggle/toggle_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/toggle/switch_event_hub.h"
#include "core/components_ng/pattern/toggle/switch_modifier.h"
#include "core/components_ng/pattern/toggle/switch_paint_method.h"
#include "core/components_ng/pattern/toggle/switch_paint_property.h"
#include "core/components_ng/pattern/toggle/switch_pattern.h"
#include "core/components_ng/pattern/toggle/toggle_model.h"
#include "core/components_ng/pattern/toggle/toggle_model_ng.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr bool IS_ON = true;
constexpr float CONTAINER_WIDTH = 200.0f;
constexpr float CONTAINER_HEIGHT = 100.0f;
constexpr Dimension ZERO = 0.0_px;
constexpr Dimension TOGGLE_WIDTH = 60.0_px;
constexpr Dimension TOGGLE_HEIGHT = 20.0_px;
constexpr float SWITCH_WIDTH = 100.0f;
constexpr float SWITCH_HEIGHT = 50.0f;
const SizeF CONTAINER_SIZE(CONTAINER_WIDTH, CONTAINER_HEIGHT);
constexpr float POINT_RADIUS_LARGE = 30.0f;
constexpr float DEFAULT_POINT_SCALE = 1.0f;
constexpr float LOW_GRADE_SHRINK_SCALE = 0.78f;
constexpr float LOW_GRADE_EXPAND_SCALE = 1.56f;
constexpr float INITIAL_POINT_ALPHA = 1.0f;
constexpr float ZERO_ALPHA = 0.0f;
constexpr float DRAG_OFFSET_X_LEFT = 10.0f;
constexpr float DRAG_OFFSET_X_RIGHT = 90.0f;
constexpr float DRAG_OFFSET_X_MID = 50.0f;
constexpr float NUMBER_TWO = 2.0f;
constexpr float CONTENT_OFFSET_X = 0.0f;
constexpr float CONTENT_OFFSET_Y = 0.0f;
constexpr float CONTENT_WIDTH_NORMAL = 100.0f;
constexpr float CONTENT_HEIGHT_NORMAL = 50.0f;
constexpr float CONTENT_WIDTH_SMALL = 30.0f;
constexpr float CONTENT_HEIGHT_SMALL = 50.0f;
} // namespace

class ToggleSwitchMaterialTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    static RefPtr<FrameNode> CreateSwitchNode(bool isOn);
    static void SetupThemeManager();
    static RefPtr<SwitchPattern> GetPattern(const RefPtr<FrameNode>& node);

protected:
    static UiMaterialLevel savedMaterialLevel_;
};

UiMaterialLevel ToggleSwitchMaterialTestNg::savedMaterialLevel_ = UiMaterialLevel::DEFAULT;

void ToggleSwitchMaterialTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    savedMaterialLevel_ = g_uiMaterialLevel;
}

void ToggleSwitchMaterialTestNg::TearDownTestCase()
{
    g_uiMaterialLevel = savedMaterialLevel_;
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<FrameNode> ToggleSwitchMaterialTestNg::CreateSwitchNode(bool isOn)
{
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, isOn);
    toggleModelNG.SetWidth(Dimension(SWITCH_WIDTH));
    toggleModelNG.SetHeight(Dimension(SWITCH_HEIGHT));
    toggleModelNG.SetPointRadius(Dimension(POINT_RADIUS_LARGE));
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    if (switchFrameNode) {
        switchFrameNode->MarkModifyDone();
    }
    return switchFrameNode;
}

void ToggleSwitchMaterialTestNg::SetupThemeManager()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto switchTheme = AceType::MakeRefPtr<SwitchTheme>();
    switchTheme->width_ = TOGGLE_WIDTH;
    switchTheme->height_ = TOGGLE_HEIGHT;
    switchTheme->hotZoneHorizontalPadding_ = ZERO;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(switchTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(switchTheme));
}

RefPtr<SwitchPattern> ToggleSwitchMaterialTestNg::GetPattern(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, nullptr);
    return AceType::DynamicCast<SwitchPattern>(node->GetPattern());
}

// ============================================================
// IsHighGradeMaterial tests
// ============================================================

/**
 * @tc.name: SwitchMaterial_IsHighGradeMaterial_Exquisite
 * @tc.desc: Test IsHighGradeMaterial returns true when material level is EXQUISITE
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_IsHighGradeMaterial_Exquisite, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    EXPECT_TRUE(pattern->IsHighGradeMaterial());
    g_uiMaterialLevel = savedMaterialLevel_;
}

/**
 * @tc.name: SwitchMaterial_IsHighGradeMaterial_Gentle
 * @tc.desc: Test IsHighGradeMaterial returns true when material level is GENTLE
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_IsHighGradeMaterial_Gentle, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::GENTLE;
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    EXPECT_TRUE(pattern->IsHighGradeMaterial());
    g_uiMaterialLevel = savedMaterialLevel_;
}

/**
 * @tc.name: SwitchMaterial_IsHighGradeMaterial_Smooth
 * @tc.desc: Test IsHighGradeMaterial returns false when material level is SMOOTH
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_IsHighGradeMaterial_Smooth, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::SMOOTH;
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    EXPECT_FALSE(pattern->IsHighGradeMaterial());
    g_uiMaterialLevel = savedMaterialLevel_;
}

// ============================================================
// HasSystemMaterial tests
// ============================================================

/**
 * @tc.name: SwitchMaterial_HasSystemMaterial_NoMaterial
 * @tc.desc: Test HasSystemMaterial returns false when no system material is set
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_HasSystemMaterial_NoMaterial, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    auto renderContext = switchNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    // Default render context has no system material
    EXPECT_FALSE(pattern->HasSystemMaterial());
}

// ============================================================
// HandleLongPress branch tests
// ============================================================

/**
 * @tc.name: SwitchMaterial_HandleLongPress_NoSystemMaterial
 * @tc.desc: Test HandleLongPress returns early when no system material
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_HandleLongPress_NoSystemMaterial, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    // No system material set - HandleLongPress should return early
    pattern->HandleLongPress();
    // Verify no drag nodes were created
    EXPECT_EQ(pattern->dragFrameNode_, nullptr);
    EXPECT_FALSE(pattern->isDragActive_);
    g_uiMaterialLevel = savedMaterialLevel_;
}

/**
 * @tc.name: SwitchMaterial_HandleLongPress_HighGrade
 * @tc.desc: Test HandleLongPress delegates to HandleHighGradeLongPress for EXQUISITE
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_HandleLongPress_HighGrade, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    SetupThemeManager();

    // Set up geometry for position calculations
    auto geometryNode = switchNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(CONTENT_WIDTH_NORMAL, CONTENT_HEIGHT_NORMAL));
    geometryNode->SetContentOffset(OffsetF(CONTENT_OFFSET_X, CONTENT_OFFSET_Y));
    pattern->size_ = SizeF(CONTENT_WIDTH_NORMAL, CONTENT_HEIGHT_NORMAL);
    pattern->offset_ = OffsetF(CONTENT_OFFSET_X, CONTENT_OFFSET_Y);
    pattern->width_ = CONTENT_WIDTH_NORMAL;
    pattern->height_ = CONTENT_HEIGHT_NORMAL;

    // Mark drag active to pass the check in HandleLongPress
    pattern->isDragActive_ = true;

    // Need system material on host to pass HasSystemMaterial check
    auto renderContext = switchNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto material = AceType::MakeRefPtr<UiMaterial>();
    renderContext->SetSystemMaterial(material);

    pattern->HandleLongPress();
    // After HandleHighGradeLongPress, dragFrameNode should be created and visible
    EXPECT_NE(pattern->dragFrameNode_, nullptr);
    EXPECT_TRUE(pattern->isFrameNodeVisible_);

    g_uiMaterialLevel = savedMaterialLevel_;
}

/**
 * @tc.name: SwitchMaterial_HandleLongPress_LowGrade
 * @tc.desc: Test HandleLongPress delegates to HandleLowGradeLongPress for SMOOTH
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_HandleLongPress_LowGrade, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::SMOOTH;
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    SetupThemeManager();

    // Need paint method with modifier for low grade
    pattern->paintMethod_ = AceType::MakeRefPtr<SwitchPaintMethod>();

    auto renderContext = switchNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = switchNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);

    // Create modifier through GetContentModifier
    auto modifier = pattern->paintMethod_->GetContentModifier(paintWrapper);
    ASSERT_NE(modifier, nullptr);

    // Need system material on host
    auto material = AceType::MakeRefPtr<UiMaterial>();
    renderContext->SetSystemMaterial(material);

    pattern->isDragActive_ = true;

    pattern->HandleLongPress();
    // Low grade path should not create drag frame node
    EXPECT_EQ(pattern->dragFrameNode_, nullptr);
    EXPECT_TRUE(pattern->isDragActive_);

    g_uiMaterialLevel = savedMaterialLevel_;
}

// ============================================================
// ShowMaterialNode branch tests
// ============================================================

/**
 * @tc.name: SwitchMaterial_ShowMaterialNode_NoSystemMaterial
 * @tc.desc: Test ShowMaterialNode returns early when no system material
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_ShowMaterialNode_NoSystemMaterial, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    // No system material - should return early
    pattern->ShowMaterialNode();
    EXPECT_FALSE(pattern->isDragActive_);
    EXPECT_EQ(pattern->dragPointNode_, nullptr);
    g_uiMaterialLevel = savedMaterialLevel_;
}

/**
 * @tc.name: SwitchMaterial_ShowMaterialNode_LowGrade
 * @tc.desc: Test ShowMaterialNode returns early for low grade material
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_ShowMaterialNode_LowGrade, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::SMOOTH;
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);

    auto renderContext = switchNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto material = AceType::MakeRefPtr<UiMaterial>();
    renderContext->SetSystemMaterial(material);

    pattern->ShowMaterialNode();
    EXPECT_FALSE(pattern->isDragActive_);
    g_uiMaterialLevel = savedMaterialLevel_;
}

/**
 * @tc.name: SwitchMaterial_ShowMaterialNode_HighGrade
 * @tc.desc: Test ShowMaterialNode creates all nodes for high grade material
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_ShowMaterialNode_HighGrade, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    SetupThemeManager();

    auto renderContext = switchNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto material = AceType::MakeRefPtr<UiMaterial>();
    renderContext->SetSystemMaterial(material);

    // Set up geometry
    auto geometryNode = switchNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(CONTENT_WIDTH_NORMAL, CONTENT_HEIGHT_NORMAL));
    geometryNode->SetContentOffset(OffsetF(CONTENT_OFFSET_X, CONTENT_OFFSET_Y));
    pattern->size_ = SizeF(CONTENT_WIDTH_NORMAL, CONTENT_HEIGHT_NORMAL);
    pattern->offset_ = OffsetF(CONTENT_OFFSET_X, CONTENT_OFFSET_Y);
    pattern->width_ = CONTENT_WIDTH_NORMAL;
    pattern->height_ = CONTENT_HEIGHT_NORMAL;

    pattern->paintMethod_ = AceType::MakeRefPtr<SwitchPaintMethod>();

    pattern->ShowMaterialNode();
    EXPECT_TRUE(pattern->isDragActive_);
    EXPECT_NE(pattern->dragFrameNode_, nullptr);
    EXPECT_NE(pattern->dragPointNode_, nullptr);
    EXPECT_NE(pattern->blurCoverNode_, nullptr);
    g_uiMaterialLevel = savedMaterialLevel_;
}

// ============================================================
// HideMaterialNode branch tests
// ============================================================

/**
 * @tc.name: SwitchMaterial_HideMaterialNode_LowGrade_Active
 * @tc.desc: Test HideMaterialNode for low grade when drag is active
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_HideMaterialNode_LowGrade_Active, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::SMOOTH;
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    SetupThemeManager();

    pattern->paintMethod_ = AceType::MakeRefPtr<SwitchPaintMethod>();

    auto renderContext = switchNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = switchNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    auto modifier = pattern->paintMethod_->GetContentModifier(paintWrapper);
    ASSERT_NE(modifier, nullptr);

    pattern->isDragActive_ = true;
    pattern->HideMaterialNode();
    EXPECT_FALSE(pattern->isDragActive_);
    g_uiMaterialLevel = savedMaterialLevel_;
}

/**
 * @tc.name: SwitchMaterial_HideMaterialNode_LowGrade_NotActive
 * @tc.desc: Test HideMaterialNode for low grade when drag is not active (early return)
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_HideMaterialNode_LowGrade_NotActive, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::SMOOTH;
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);

    pattern->isDragActive_ = false;
    pattern->HideMaterialNode();
    EXPECT_FALSE(pattern->isDragActive_);
    g_uiMaterialLevel = savedMaterialLevel_;
}

/**
 * @tc.name: SwitchMaterial_HideMaterialNode_HighGrade
 * @tc.desc: Test HideMaterialNode for high grade material hides all nodes
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_HideMaterialNode_HighGrade, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    SetupThemeManager();

    auto renderContext = switchNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto material = AceType::MakeRefPtr<UiMaterial>();
    renderContext->SetSystemMaterial(material);

    auto geometryNode = switchNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(CONTENT_WIDTH_NORMAL, CONTENT_HEIGHT_NORMAL));
    geometryNode->SetContentOffset(OffsetF(CONTENT_OFFSET_X, CONTENT_OFFSET_Y));
    pattern->size_ = SizeF(CONTENT_WIDTH_NORMAL, CONTENT_HEIGHT_NORMAL);
    pattern->offset_ = OffsetF(CONTENT_OFFSET_X, CONTENT_OFFSET_Y);
    pattern->width_ = CONTENT_WIDTH_NORMAL;
    pattern->height_ = CONTENT_HEIGHT_NORMAL;

    pattern->paintMethod_ = AceType::MakeRefPtr<SwitchPaintMethod>();
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    pattern->paintMethod_->GetContentModifier(paintWrapper);

    // First show to create nodes
    pattern->ShowMaterialNode();
    EXPECT_TRUE(pattern->isDragActive_);

    // Then hide
    pattern->HideMaterialNode();
    EXPECT_FALSE(pattern->isDragActive_);
    g_uiMaterialLevel = savedMaterialLevel_;
}

// ============================================================
// PredictFinalToggleState tests
// ============================================================

/**
 * @tc.name: SwitchMaterial_PredictFinalToggleState_NoDrag
 * @tc.desc: Test PredictFinalToggleState returns current state when not dragging
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_PredictFinalToggleState_NoDrag, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    SetupThemeManager();

    auto geometryNode = switchNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(CONTENT_WIDTH_NORMAL, CONTENT_HEIGHT_NORMAL));
    geometryNode->SetContentOffset(OffsetF(CONTENT_OFFSET_X, CONTENT_OFFSET_Y));

    pattern->isDragEvent_ = false;
    pattern->isOn_ = true;
    EXPECT_TRUE(pattern->PredictFinalToggleState());

    pattern->isOn_ = false;
    EXPECT_FALSE(pattern->PredictFinalToggleState());
}

/**
 * @tc.name: SwitchMaterial_PredictFinalToggleState_DragToggleLTR
 * @tc.desc: Test PredictFinalToggleState during drag in LTR direction
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_PredictFinalToggleState_DragToggleLTR, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    SetupThemeManager();

    auto geometryNode = switchNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(CONTENT_WIDTH_NORMAL, CONTENT_HEIGHT_NORMAL));
    geometryNode->SetContentOffset(OffsetF(CONTENT_OFFSET_X, CONTENT_OFFSET_Y));

    pattern->isDragEvent_ = true;
    pattern->direction_ = TextDirection::LTR;
    pattern->isOn_ = true;

    // Drag to left side (dragOffsetX < mainSize/2) - should toggle
    pattern->dragOffsetX_ = DRAG_OFFSET_X_LEFT;
    EXPECT_FALSE(pattern->PredictFinalToggleState());

    // Drag to right side (dragOffsetX >= mainSize/2) - should not toggle
    pattern->dragOffsetX_ = DRAG_OFFSET_X_RIGHT;
    EXPECT_TRUE(pattern->PredictFinalToggleState());
}

/**
 * @tc.name: SwitchMaterial_PredictFinalToggleState_DragToggleRTL
 * @tc.desc: Test PredictFinalToggleState during drag in RTL direction
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_PredictFinalToggleState_DragToggleRTL, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    SetupThemeManager();

    auto geometryNode = switchNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(CONTENT_WIDTH_NORMAL, CONTENT_HEIGHT_NORMAL));
    geometryNode->SetContentOffset(OffsetF(CONTENT_OFFSET_X, CONTENT_OFFSET_Y));

    pattern->isDragEvent_ = true;
    pattern->direction_ = TextDirection::RTL;
    pattern->isOn_ = true;

    // RTL: drag to right (dragOffsetX > mainSize/2) - should toggle
    pattern->dragOffsetX_ = DRAG_OFFSET_X_RIGHT;
    EXPECT_FALSE(pattern->PredictFinalToggleState());

    // RTL: drag to left (dragOffsetX <= mainSize/2) - should not toggle
    pattern->dragOffsetX_ = DRAG_OFFSET_X_LEFT;
    EXPECT_TRUE(pattern->PredictFinalToggleState());
}

// ============================================================
// CalculatePointCenterX tests
// ============================================================

/**
 * @tc.name: SwitchMaterial_CalculatePointCenterX_NoDragLTR
 * @tc.desc: Test CalculatePointCenterX when not dragging in LTR direction
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_CalculatePointCenterX_NoDragLTR, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    SetupThemeManager();

    auto geometryNode = switchNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(CONTENT_WIDTH_NORMAL, CONTENT_HEIGHT_NORMAL));
    geometryNode->SetContentOffset(OffsetF(CONTENT_OFFSET_X, CONTENT_OFFSET_Y));
    pattern->size_ = SizeF(CONTENT_WIDTH_NORMAL, CONTENT_HEIGHT_NORMAL);
    pattern->offset_ = OffsetF(CONTENT_OFFSET_X, CONTENT_OFFSET_Y);

    float pointRadius = CONTENT_HEIGHT_NORMAL / NUMBER_TWO;
    float actualGap = 0.0f;
    pattern->isDragEvent_ = false;
    pattern->direction_ = TextDirection::LTR;

    // isOn=true, LTR: point should be at right (width - height)
    pattern->isOn_ = true;
    float centerX = pattern->CalculatePointCenterX(pointRadius, actualGap);
    float expectedX = CONTENT_OFFSET_X + actualGap + pointRadius + (CONTENT_WIDTH_NORMAL - CONTENT_HEIGHT_NORMAL);
    EXPECT_FLOAT_EQ(centerX, expectedX);

    // isOn=false, LTR: point should be at left (0)
    pattern->isOn_ = false;
    centerX = pattern->CalculatePointCenterX(pointRadius, actualGap);
    expectedX = CONTENT_OFFSET_X + actualGap + pointRadius;
    EXPECT_FLOAT_EQ(centerX, expectedX);
}

/**
 * @tc.name: SwitchMaterial_CalculatePointCenterX_NoDragRTL
 * @tc.desc: Test CalculatePointCenterX when not dragging in RTL direction
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_CalculatePointCenterX_NoDragRTL, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    SetupThemeManager();

    auto geometryNode = switchNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(CONTENT_WIDTH_NORMAL, CONTENT_HEIGHT_NORMAL));
    geometryNode->SetContentOffset(OffsetF(CONTENT_OFFSET_X, CONTENT_OFFSET_Y));
    pattern->size_ = SizeF(CONTENT_WIDTH_NORMAL, CONTENT_HEIGHT_NORMAL);
    pattern->offset_ = OffsetF(CONTENT_OFFSET_X, CONTENT_OFFSET_Y);

    float pointRadius = CONTENT_HEIGHT_NORMAL / NUMBER_TWO;
    float actualGap = 0.0f;
    pattern->isDragEvent_ = false;
    pattern->direction_ = TextDirection::RTL;

    // isOn=true, RTL: point should be at left (0)
    pattern->isOn_ = true;
    float centerX = pattern->CalculatePointCenterX(pointRadius, actualGap);
    float expectedX = CONTENT_OFFSET_X + actualGap + pointRadius;
    EXPECT_FLOAT_EQ(centerX, expectedX);

    // isOn=false, RTL: point should be at right (width - height)
    pattern->isOn_ = false;
    centerX = pattern->CalculatePointCenterX(pointRadius, actualGap);
    expectedX = CONTENT_OFFSET_X + actualGap + pointRadius + (CONTENT_WIDTH_NORMAL - CONTENT_HEIGHT_NORMAL);
    EXPECT_FLOAT_EQ(centerX, expectedX);
}

/**
 * @tc.name: SwitchMaterial_CalculatePointCenterX_DragEvent
 * @tc.desc: Test CalculatePointCenterX during drag event
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_CalculatePointCenterX_DragEvent, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    SetupThemeManager();

    auto geometryNode = switchNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(CONTENT_WIDTH_NORMAL, CONTENT_HEIGHT_NORMAL));
    geometryNode->SetContentOffset(OffsetF(CONTENT_OFFSET_X, CONTENT_OFFSET_Y));
    pattern->size_ = SizeF(CONTENT_WIDTH_NORMAL, CONTENT_HEIGHT_NORMAL);
    pattern->offset_ = OffsetF(CONTENT_OFFSET_X, CONTENT_OFFSET_Y);

    float pointRadius = CONTENT_HEIGHT_NORMAL / NUMBER_TWO;
    float actualGap = 0.0f;
    pattern->isDragEvent_ = true;
    pattern->dragOffsetX_ = DRAG_OFFSET_X_MID;

    float centerX = pattern->CalculatePointCenterX(pointRadius, actualGap);
    float expectedX = CONTENT_OFFSET_X + actualGap + pointRadius + DRAG_OFFSET_X_MID;
    EXPECT_FLOAT_EQ(centerX, expectedX);
}

/**
 * @tc.name: SwitchMaterial_CalculatePointCenterX_WidthLessThanHeight
 * @tc.desc: Test CalculatePointCenterX when width < height (centered)
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_CalculatePointCenterX_WidthLessThanHeight, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    SetupThemeManager();

    auto geometryNode = switchNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(CONTENT_WIDTH_SMALL, CONTENT_HEIGHT_SMALL));
    geometryNode->SetContentOffset(OffsetF(CONTENT_OFFSET_X, CONTENT_OFFSET_Y));
    pattern->size_ = SizeF(CONTENT_WIDTH_SMALL, CONTENT_HEIGHT_SMALL);
    pattern->offset_ = OffsetF(CONTENT_OFFSET_X, CONTENT_OFFSET_Y);

    float pointRadius = CONTENT_HEIGHT_SMALL / NUMBER_TWO;
    float actualGap = 0.0f;
    pattern->isDragEvent_ = false;

    float centerX = pattern->CalculatePointCenterX(pointRadius, actualGap);
    float expectedX = CONTENT_OFFSET_X + CONTENT_WIDTH_SMALL / NUMBER_TWO;
    EXPECT_FLOAT_EQ(centerX, expectedX);
}

// ============================================================
// SwitchModifier material branch tests
// ============================================================

/**
 * @tc.name: SwitchMaterial_Modifier_PointAlphaDefault
 * @tc.desc: Test SwitchModifier default pointAlpha is 1.0
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_Modifier_PointAlphaDefault, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    SetupThemeManager();

    pattern->paintMethod_ = AceType::MakeRefPtr<SwitchPaintMethod>();
    auto renderContext = switchNode->GetRenderContext();
    auto geometryNode = switchNode->GetGeometryNode();
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    auto modifier = pattern->paintMethod_->GetContentModifier(paintWrapper);
    ASSERT_NE(modifier, nullptr);

    auto switchModifier = AceType::DynamicCast<SwitchModifier>(modifier);
    ASSERT_NE(switchModifier, nullptr);
    EXPECT_FLOAT_EQ(switchModifier->GetPointAlpha(), INITIAL_POINT_ALPHA);
}

/**
 * @tc.name: SwitchMaterial_Modifier_SetPointAlpha
 * @tc.desc: Test SwitchModifier SetPointAlpha and GetPointAlpha
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_Modifier_SetPointAlpha, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    SetupThemeManager();

    pattern->paintMethod_ = AceType::MakeRefPtr<SwitchPaintMethod>();
    auto renderContext = switchNode->GetRenderContext();
    auto geometryNode = switchNode->GetGeometryNode();
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    auto modifier = pattern->paintMethod_->GetContentModifier(paintWrapper);
    ASSERT_NE(modifier, nullptr);

    auto switchModifier = AceType::DynamicCast<SwitchModifier>(modifier);
    ASSERT_NE(switchModifier, nullptr);
    switchModifier->SetPointAlpha(ZERO_ALPHA);
    EXPECT_FLOAT_EQ(switchModifier->GetPointAlpha(), ZERO_ALPHA);

    switchModifier->SetPointAlpha(INITIAL_POINT_ALPHA);
    EXPECT_FLOAT_EQ(switchModifier->GetPointAlpha(), INITIAL_POINT_ALPHA);
}

/**
 * @tc.name: SwitchMaterial_Modifier_PointScaleDefault
 * @tc.desc: Test SwitchModifier default pointScale is 1.0
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_Modifier_PointScaleDefault, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    SetupThemeManager();

    pattern->paintMethod_ = AceType::MakeRefPtr<SwitchPaintMethod>();
    auto renderContext = switchNode->GetRenderContext();
    auto geometryNode = switchNode->GetGeometryNode();
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    auto modifier = pattern->paintMethod_->GetContentModifier(paintWrapper);
    ASSERT_NE(modifier, nullptr);

    auto switchModifier = AceType::DynamicCast<SwitchModifier>(modifier);
    ASSERT_NE(switchModifier, nullptr);
    EXPECT_FLOAT_EQ(switchModifier->GetPointScale(), DEFAULT_POINT_SCALE);
}

/**
 * @tc.name: SwitchMaterial_Modifier_SetPointScale
 * @tc.desc: Test SwitchModifier SetPointScale changes the value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_Modifier_SetPointScale, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    SetupThemeManager();

    pattern->paintMethod_ = AceType::MakeRefPtr<SwitchPaintMethod>();
    auto renderContext = switchNode->GetRenderContext();
    auto geometryNode = switchNode->GetGeometryNode();
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    auto modifier = pattern->paintMethod_->GetContentModifier(paintWrapper);
    ASSERT_NE(modifier, nullptr);

    auto switchModifier = AceType::DynamicCast<SwitchModifier>(modifier);
    ASSERT_NE(switchModifier, nullptr);
    switchModifier->SetPointScale(LOW_GRADE_SHRINK_SCALE);
    EXPECT_FLOAT_EQ(switchModifier->GetPointScale(), LOW_GRADE_SHRINK_SCALE);

    switchModifier->SetPointScale(LOW_GRADE_EXPAND_SCALE);
    EXPECT_FLOAT_EQ(switchModifier->GetPointScale(), LOW_GRADE_EXPAND_SCALE);
}

/**
 * @tc.name: SwitchMaterial_Modifier_HasSystemMaterial
 * @tc.desc: Test SwitchModifier SetHasSystemMaterial and GetHasSystemMaterial
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_Modifier_HasSystemMaterial, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    SetupThemeManager();

    pattern->paintMethod_ = AceType::MakeRefPtr<SwitchPaintMethod>();
    auto renderContext = switchNode->GetRenderContext();
    auto geometryNode = switchNode->GetGeometryNode();
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    auto modifier = pattern->paintMethod_->GetContentModifier(paintWrapper);
    ASSERT_NE(modifier, nullptr);

    auto switchModifier = AceType::DynamicCast<SwitchModifier>(modifier);
    ASSERT_NE(switchModifier, nullptr);

    EXPECT_FALSE(switchModifier->GetHasSystemMaterial());
    switchModifier->SetHasSystemMaterial(true);
    EXPECT_TRUE(switchModifier->GetHasSystemMaterial());
    switchModifier->SetHasSystemMaterial(false);
    EXPECT_FALSE(switchModifier->GetHasSystemMaterial());
}

// ============================================================
// DrawRectCircle with hasSystemMaterial branch tests
// ============================================================

/**
 * @tc.name: SwitchMaterial_DrawRectCircle_NoSystemMaterial
 * @tc.desc: Test DrawRectCircle without system material uses normal radius
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_DrawRectCircle_NoSystemMaterial, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    SetupThemeManager();

    pattern->paintMethod_ = AceType::MakeRefPtr<SwitchPaintMethod>();
    auto renderContext = switchNode->GetRenderContext();
    auto geometryNode = switchNode->GetGeometryNode();
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);

    auto modifier = pattern->paintMethod_->GetContentModifier(paintWrapper);
    ASSERT_NE(modifier, nullptr);
    auto switchModifier = AceType::DynamicCast<SwitchModifier>(modifier);
    ASSERT_NE(switchModifier, nullptr);

    // No system material - hasSystemMaterial_ is false by default
    EXPECT_FALSE(switchModifier->hasSystemMaterial_);
    // pointAlpha should be default 1.0
    EXPECT_FLOAT_EQ(switchModifier->pointAlpha_, INITIAL_POINT_ALPHA);
}

/**
 * @tc.name: SwitchMaterial_DrawRectCircle_WithSystemMaterial
 * @tc.desc: Test DrawRectCircle with system material applies alpha and scale
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_DrawRectCircle_WithSystemMaterial, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    SetupThemeManager();

    pattern->paintMethod_ = AceType::MakeRefPtr<SwitchPaintMethod>();
    auto renderContext = switchNode->GetRenderContext();
    auto geometryNode = switchNode->GetGeometryNode();
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);

    auto modifier = pattern->paintMethod_->GetContentModifier(paintWrapper);
    ASSERT_NE(modifier, nullptr);
    auto switchModifier = AceType::DynamicCast<SwitchModifier>(modifier);
    ASSERT_NE(switchModifier, nullptr);

    // Set system material and verify state
    switchModifier->SetHasSystemMaterial(true);
    EXPECT_TRUE(switchModifier->hasSystemMaterial_);

    // Set alpha to zero (simulating material node showing)
    switchModifier->SetPointAlpha(ZERO_ALPHA);
    EXPECT_FLOAT_EQ(switchModifier->GetPointAlpha(), ZERO_ALPHA);

    // Set scale to shrink (simulating low grade long press)
    switchModifier->SetPointScale(LOW_GRADE_SHRINK_SCALE);
    EXPECT_FLOAT_EQ(switchModifier->GetPointScale(), LOW_GRADE_SHRINK_SCALE);
}

// ============================================================
// CreateDragFrameNode / CreateDragPointNode / CreateBlurCoverNode tests
// ============================================================

/**
 * @tc.name: SwitchMaterial_CreateDragFrameNode
 * @tc.desc: Test CreateDragFrameNode creates node with correct properties
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_CreateDragFrameNode, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    SetupThemeManager();

    auto geometryNode = switchNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(CONTENT_WIDTH_NORMAL, CONTENT_HEIGHT_NORMAL));
    geometryNode->SetContentOffset(OffsetF(CONTENT_OFFSET_X, CONTENT_OFFSET_Y));
    pattern->size_ = SizeF(CONTENT_WIDTH_NORMAL, CONTENT_HEIGHT_NORMAL);
    pattern->offset_ = OffsetF(CONTENT_OFFSET_X, CONTENT_OFFSET_Y);

    EXPECT_EQ(pattern->dragFrameNode_, nullptr);
    pattern->CreateDragFrameNode();
    EXPECT_NE(pattern->dragFrameNode_, nullptr);

    // Verify node has correct size (pointDiameter * 2.0)
    auto layoutProp = pattern->dragFrameNode_->GetLayoutProperty();
    ASSERT_NE(layoutProp, nullptr);
    auto& calcSize = layoutProp->GetCalcLayoutConstraint();
    ASSERT_TRUE(calcSize != nullptr);
    EXPECT_TRUE(calcSize->selfIdealSize.has_value());

    // Second call should not create new node (already exists)
    auto firstNode = pattern->dragFrameNode_;
    pattern->CreateDragFrameNode();
    EXPECT_EQ(pattern->dragFrameNode_, firstNode);
}

/**
 * @tc.name: SwitchMaterial_CreateDragPointNode
 * @tc.desc: Test CreateDragPointNode creates node with correct properties
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_CreateDragPointNode, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    SetupThemeManager();

    auto geometryNode = switchNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(CONTENT_WIDTH_NORMAL, CONTENT_HEIGHT_NORMAL));
    geometryNode->SetContentOffset(OffsetF(CONTENT_OFFSET_X, CONTENT_OFFSET_Y));
    pattern->size_ = SizeF(CONTENT_WIDTH_NORMAL, CONTENT_HEIGHT_NORMAL);
    pattern->offset_ = OffsetF(CONTENT_OFFSET_X, CONTENT_OFFSET_Y);

    EXPECT_EQ(pattern->dragPointNode_, nullptr);
    pattern->CreateDragPointNode();
    EXPECT_NE(pattern->dragPointNode_, nullptr);

    // Second call should reuse existing node
    auto firstNode = pattern->dragPointNode_;
    pattern->CreateDragPointNode();
    EXPECT_EQ(pattern->dragPointNode_, firstNode);
}

/**
 * @tc.name: SwitchMaterial_CreateBlurCoverNode
 * @tc.desc: Test CreateBlurCoverNode creates node with correct properties
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_CreateBlurCoverNode, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    SetupThemeManager();

    auto geometryNode = switchNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(CONTENT_WIDTH_NORMAL, CONTENT_HEIGHT_NORMAL));
    geometryNode->SetContentOffset(OffsetF(CONTENT_OFFSET_X, CONTENT_OFFSET_Y));
    pattern->size_ = SizeF(CONTENT_WIDTH_NORMAL, CONTENT_HEIGHT_NORMAL);
    pattern->offset_ = OffsetF(CONTENT_OFFSET_X, CONTENT_OFFSET_Y);

    EXPECT_EQ(pattern->blurCoverNode_, nullptr);
    pattern->CreateBlurCoverNode();
    EXPECT_NE(pattern->blurCoverNode_, nullptr);

    // Second call should reuse existing node
    auto firstNode = pattern->blurCoverNode_;
    pattern->CreateBlurCoverNode();
    EXPECT_EQ(pattern->blurCoverNode_, firstNode);
}

// ============================================================
// HideMaterialNodes tests
// ============================================================

/**
 * @tc.name: SwitchMaterial_HideMaterialNodes
 * @tc.desc: Test HideMaterialNodes removes all child nodes from host
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_HideMaterialNodes, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    SetupThemeManager();

    auto geometryNode = switchNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(CONTENT_WIDTH_NORMAL, CONTENT_HEIGHT_NORMAL));
    geometryNode->SetContentOffset(OffsetF(CONTENT_OFFSET_X, CONTENT_OFFSET_Y));
    pattern->size_ = SizeF(CONTENT_WIDTH_NORMAL, CONTENT_HEIGHT_NORMAL);
    pattern->offset_ = OffsetF(CONTENT_OFFSET_X, CONTENT_OFFSET_Y);
    pattern->width_ = CONTENT_WIDTH_NORMAL;
    pattern->height_ = CONTENT_HEIGHT_NORMAL;

    // Create nodes manually
    pattern->CreateDragFrameNode();
    pattern->CreateDragPointNode();
    pattern->CreateBlurCoverNode();

    // Add them as children
    switchNode->AddChild(pattern->dragFrameNode_);
    pattern->isFrameNodeVisible_ = true;
    switchNode->AddChild(pattern->dragPointNode_);
    switchNode->AddChild(pattern->blurCoverNode_);

    pattern->HideMaterialNodes();
    EXPECT_FALSE(pattern->isFrameNodeVisible_);
    g_uiMaterialLevel = savedMaterialLevel_;
}

// ============================================================
// AnimateToDragState tests
// ============================================================

/**
 * @tc.name: SwitchMaterial_AnimateToDragState_LowGrade
 * @tc.desc: Test AnimateToDragState returns early for low grade material
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_AnimateToDragState_LowGrade, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::SMOOTH;
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);

    // Should not crash or create nodes
    pattern->AnimateToDragState();
    EXPECT_EQ(pattern->dragFrameNode_, nullptr);
    g_uiMaterialLevel = savedMaterialLevel_;
}

/**
 * @tc.name: SwitchMaterial_AnimateToDragState_HighGrade_NoNodes
 * @tc.desc: Test AnimateToDragState with high grade but no frame node
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_AnimateToDragState_HighGrade_NoNodes, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::GENTLE;
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    SetupThemeManager();

    auto geometryNode = switchNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(CONTENT_WIDTH_NORMAL, CONTENT_HEIGHT_NORMAL));
    geometryNode->SetContentOffset(OffsetF(CONTENT_OFFSET_X, CONTENT_OFFSET_Y));
    pattern->size_ = SizeF(CONTENT_WIDTH_NORMAL, CONTENT_HEIGHT_NORMAL);
    pattern->offset_ = OffsetF(CONTENT_OFFSET_X, CONTENT_OFFSET_Y);

    // Create blur cover node but not drag frame node
    pattern->CreateBlurCoverNode();
    pattern->isFrameNodeVisible_ = false;

    // Should handle gracefully with only blurCoverNode
    pattern->AnimateToDragState();
    EXPECT_NE(pattern->blurCoverNode_, nullptr);
    g_uiMaterialLevel = savedMaterialLevel_;
}

// ============================================================
// ResetHostMaterialEffects tests
// ============================================================

/**
 * @tc.name: SwitchMaterial_ResetHostMaterialEffects_NoMaterial
 * @tc.desc: Test ResetHostMaterialEffects when no system material is set
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_ResetHostMaterialEffects_NoMaterial, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    SetupThemeManager();

    auto renderContext = switchNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    // No system material set - should return early (CHECK_NULL_VOID(material))
    // Does not crash
    pattern->ResetHostMaterialEffects();
}

/**
 * @tc.name: SwitchMaterial_ResetHostMaterialEffects_WithMaterial
 * @tc.desc: Test ResetHostMaterialEffects resets visual properties when material is present
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_ResetHostMaterialEffects_WithMaterial, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    SetupThemeManager();

    auto renderContext = switchNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    // Set system material so the method proceeds past CHECK_NULL_VOID(material)
    auto material = AceType::MakeRefPtr<UiMaterial>();
    renderContext->SetSystemMaterial(material);

    pattern->ResetHostMaterialEffects();
    // uiMaterial_ is NOT cleared (by design), but visual properties are reset
    EXPECT_NE(renderContext->GetSystemMaterial(), nullptr);
}

// ============================================================
// GetPointRadius and GetActualGap tests
// ============================================================

/**
 * @tc.name: SwitchMaterial_GetPointRadius
 * @tc.desc: Test GetPointRadius calculates correct radius
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_GetPointRadius, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    SetupThemeManager();

    auto geometryNode = switchNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(CONTENT_WIDTH_NORMAL, CONTENT_HEIGHT_NORMAL));
    pattern->size_ = SizeF(CONTENT_WIDTH_NORMAL, CONTENT_HEIGHT_NORMAL);

    float radius = pattern->GetPointRadius();
    // radius should be height/2 - actualGap
    EXPECT_GT(radius, 0.0f);
    EXPECT_LT(radius, CONTENT_HEIGHT_NORMAL / NUMBER_TWO);
}

/**
 * @tc.name: SwitchMaterial_GetActualGap
 * @tc.desc: Test GetActualGap returns positive gap value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_GetActualGap, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    SetupThemeManager();

    auto geometryNode = switchNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(CONTENT_WIDTH_NORMAL, CONTENT_HEIGHT_NORMAL));
    pattern->size_ = SizeF(CONTENT_WIDTH_NORMAL, CONTENT_HEIGHT_NORMAL);

    float gap = pattern->GetActualGap();
    EXPECT_GT(gap, 0.0f);
}

// ============================================================
// CreateNodePaintMethod with HasSystemMaterial
// ============================================================

/**
 * @tc.name: SwitchMaterial_CreateNodePaintMethod_NoSystemMaterial
 * @tc.desc: Test CreateNodePaintMethod sets hasSystemMaterial to false by default
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_CreateNodePaintMethod_NoSystemMaterial, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);

    auto paintMethod = pattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod, nullptr);
    auto switchPaintMethod = AceType::DynamicCast<SwitchPaintMethod>(paintMethod);
    ASSERT_NE(switchPaintMethod, nullptr);
    EXPECT_FALSE(switchPaintMethod->hasSystemMaterial_);
}

/**
 * @tc.name: SwitchMaterial_CreateNodePaintMethod_WithSystemMaterial
 * @tc.desc: Test CreateNodePaintMethod sets hasSystemMaterial to true when material present
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_CreateNodePaintMethod_WithSystemMaterial, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);

    auto renderContext = switchNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto material = AceType::MakeRefPtr<UiMaterial>();
    renderContext->SetSystemMaterial(material);

    auto paintMethod = pattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod, nullptr);
    auto switchPaintMethod = AceType::DynamicCast<SwitchPaintMethod>(paintMethod);
    ASSERT_NE(switchPaintMethod, nullptr);
    EXPECT_TRUE(switchPaintMethod->hasSystemMaterial_);
}

// ============================================================
// OnTouchDown/OnTouchUp with material integration
// ============================================================

/**
 * @tc.name: SwitchMaterial_OnTouchDown_SetsDragState
 * @tc.desc: Test OnTouchDown sets isDragActive via ShowMaterialNode when high grade
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_OnTouchDown_SetsDragState, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    SetupThemeManager();

    auto renderContext = switchNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto material = AceType::MakeRefPtr<UiMaterial>();
    renderContext->SetSystemMaterial(material);

    auto geometryNode = switchNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(CONTENT_WIDTH_NORMAL, CONTENT_HEIGHT_NORMAL));
    geometryNode->SetContentOffset(OffsetF(CONTENT_OFFSET_X, CONTENT_OFFSET_Y));
    pattern->size_ = SizeF(CONTENT_WIDTH_NORMAL, CONTENT_HEIGHT_NORMAL);
    pattern->offset_ = OffsetF(CONTENT_OFFSET_X, CONTENT_OFFSET_Y);
    pattern->width_ = CONTENT_WIDTH_NORMAL;
    pattern->height_ = CONTENT_HEIGHT_NORMAL;
    pattern->paintMethod_ = AceType::MakeRefPtr<SwitchPaintMethod>();

    pattern->OnTouchDown();
    EXPECT_TRUE(pattern->isTouch_);
    EXPECT_TRUE(pattern->isDragActive_);

    g_uiMaterialLevel = savedMaterialLevel_;
}

/**
 * @tc.name: SwitchMaterial_OnTouchUp_ResetsDragState
 * @tc.desc: Test OnTouchUp resets isDragActive via HideMaterialNode
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_OnTouchUp_ResetsDragState, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::SMOOTH;
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    SetupThemeManager();

    pattern->paintMethod_ = AceType::MakeRefPtr<SwitchPaintMethod>();
    auto renderContext = switchNode->GetRenderContext();
    auto geometryNode = switchNode->GetGeometryNode();
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    pattern->paintMethod_->GetContentModifier(paintWrapper);

    pattern->isDragActive_ = true;
    pattern->isTouch_ = true;

    pattern->OnTouchUp();
    EXPECT_FALSE(pattern->isTouch_);
    EXPECT_FALSE(pattern->isDragActive_);

    g_uiMaterialLevel = savedMaterialLevel_;
}
} // namespace OHOS::Ace::NG
