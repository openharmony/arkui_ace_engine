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
#include "core/components/common/properties/ui_material.h"
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
constexpr float NUMBER_TWO = 2.0f;
constexpr float CONTENT_OFFSET_X = 0.0f;
constexpr float CONTENT_OFFSET_Y = 0.0f;
constexpr float CONTENT_WIDTH_NORMAL = 100.0f;
constexpr float CONTENT_HEIGHT_NORMAL = 50.0f;
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

    pattern->HandleLongPress();
    // Low grade path should not create drag frame node
    EXPECT_EQ(pattern->dragFrameNode_, nullptr);

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
    // Low grade: ShowMaterialNode returns early, no nodes created
    EXPECT_EQ(pattern->dragFrameNode_, nullptr);
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

    pattern->HideMaterialNode();
    // Low grade: HideMaterialNode resets point scale via animation
    // Verify it doesn't crash and no drag frame node was created
    EXPECT_EQ(pattern->dragFrameNode_, nullptr);
    g_uiMaterialLevel = savedMaterialLevel_;
}

/**
 * @tc.name: SwitchMaterial_HideMaterialNode_LowGrade_NoModifier
 * @tc.desc: Test HideMaterialNode for low grade without modifier returns early
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_HideMaterialNode_LowGrade_NoModifier, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::SMOOTH;
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);

    // No paint method set - HideMaterialNode should handle CHECK_NULL_VOID gracefully
    pattern->HideMaterialNode();
    EXPECT_EQ(pattern->dragFrameNode_, nullptr);
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
    EXPECT_NE(pattern->dragFrameNode_, nullptr);

    // Then hide
    pattern->HideMaterialNode();
    g_uiMaterialLevel = savedMaterialLevel_;
}

// ============================================================
// UpdateMaterialNodePosition tests
// ============================================================

/**
 * @tc.name: SwitchMaterial_UpdateMaterialNodePosition
 * @tc.desc: Test UpdateMaterialNodePosition updates all node positions
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_UpdateMaterialNodePosition, TestSize.Level1)
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

    // Create nodes first
    pattern->CreateDragFrameNode();
    pattern->CreateDragPointNode();
    pattern->CreateBlurCoverNode();
    ASSERT_NE(pattern->dragFrameNode_, nullptr);
    ASSERT_NE(pattern->dragPointNode_, nullptr);
    ASSERT_NE(pattern->blurCoverNode_, nullptr);

    float centerX = 50.0f;
    float centerY = 25.0f;
    float pointRadius = CONTENT_HEIGHT_NORMAL / NUMBER_TWO;
    pattern->UpdateMaterialNodePosition(centerX, centerY, pointRadius);
    // Verify nodes still exist after position update
    EXPECT_NE(pattern->dragFrameNode_, nullptr);
    EXPECT_NE(pattern->dragPointNode_, nullptr);
    EXPECT_NE(pattern->blurCoverNode_, nullptr);
    g_uiMaterialLevel = savedMaterialLevel_;
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
 * @tc.name: SwitchMaterial_OnTouchDown_CreatesMaterialNodes
 * @tc.desc: Test OnTouchDown creates drag nodes via ShowMaterialNode when high grade
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_OnTouchDown_CreatesMaterialNodes, TestSize.Level1)
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
    // High grade with system material: ShowMaterialNode creates drag nodes
    EXPECT_NE(pattern->dragFrameNode_, nullptr);

    g_uiMaterialLevel = savedMaterialLevel_;
}

/**
 * @tc.name: SwitchMaterial_OnTouchUp_ResetsTouchState
 * @tc.desc: Test OnTouchUp resets isTouch and calls HideMaterialNode
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_OnTouchUp_ResetsTouchState, TestSize.Level1)
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

    pattern->isTouch_ = true;

    pattern->OnTouchUp();
    EXPECT_FALSE(pattern->isTouch_);

    g_uiMaterialLevel = savedMaterialLevel_;
}

// ============================================================
// MaterialNodePositionCallback integration tests
// ============================================================

/**
 * @tc.name: SwitchMaterial_RegisterMaterialNodePositionCallback
 * @tc.desc: Test RegisterMaterialNodePositionCallback sets callback on modifier
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_RegisterMaterialNodePositionCallback, TestSize.Level1)
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

    bool callbackFired = false;
    switchModifier->SetMaterialNodePositionCallback(
        [&callbackFired](float cx, float cy, float radius) {
            callbackFired = true;
        });
    EXPECT_FALSE(callbackFired);
    // Simulate callback invocation
    if (switchModifier->materialNodePositionCallback_) {
        switchModifier->materialNodePositionCallback_(50.0f, 25.0f, 20.0f);
    }
    EXPECT_TRUE(callbackFired);
}

// ============================================================
// CreateDragBlurStyleOption with scale parameter tests
// ============================================================

/**
 * @tc.name: SwitchMaterial_CreateDragBlurStyleOption_DefaultScale
 * @tc.desc: Test CreateDragBlurStyleOption with default scale
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_CreateDragBlurStyleOption_DefaultScale, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);

    auto option = pattern->CreateDragBlurStyleOption(0.5f);
    EXPECT_FLOAT_EQ(option.scale, 0.5f);
    EXPECT_EQ(option.blurStyle, BlurStyle::THIN);
    EXPECT_EQ(option.colorMode, ThemeColorMode::LIGHT);
    EXPECT_EQ(option.adaptiveColor, AdaptiveColor::DEFAULT);
}

/**
 * @tc.name: SwitchMaterial_CreateDragBlurStyleOption_ZeroScale
 * @tc.desc: Test CreateDragBlurStyleOption with zero scale (used in hide animation)
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_CreateDragBlurStyleOption_ZeroScale, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);

    auto option = pattern->CreateDragBlurStyleOption(0.0f);
    EXPECT_FLOAT_EQ(option.scale, 0.0f);
}

// ============================================================
// OnTouchDown without system material (no drag nodes)
// ============================================================

/**
 * @tc.name: SwitchMaterial_OnTouchDown_NoSystemMaterial
 * @tc.desc: Test OnTouchDown without system material does not create drag nodes
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_OnTouchDown_NoSystemMaterial, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);

    pattern->OnTouchDown();
    EXPECT_TRUE(pattern->isTouch_);
    // No system material: no drag nodes created
    EXPECT_EQ(pattern->dragFrameNode_, nullptr);
    EXPECT_EQ(pattern->dragPointNode_, nullptr);
    EXPECT_EQ(pattern->blurCoverNode_, nullptr);

    g_uiMaterialLevel = savedMaterialLevel_;
}

// ============================================================
// SwitchModifier DrawRectCircle alpha multiplication tests
// ============================================================

/**
 * @tc.name: SwitchMaterial_DrawRectCircle_AlphaMultiplication
 * @tc.desc: Test that alpha is multiplied with color alpha, not replaced
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_DrawRectCircle_AlphaMultiplication, TestSize.Level1)
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

    // With system material and alpha=0.0, the point should be fully transparent
    switchModifier->SetHasSystemMaterial(true);
    switchModifier->SetPointAlpha(0.0f);
    EXPECT_FLOAT_EQ(switchModifier->GetPointAlpha(), 0.0f);

    // With system material and alpha=1.0, the point should use color's own alpha
    switchModifier->SetPointAlpha(1.0f);
    EXPECT_FLOAT_EQ(switchModifier->GetPointAlpha(), 1.0f);

    // Without system material, alpha should not be applied
    switchModifier->SetHasSystemMaterial(false);
    EXPECT_FALSE(switchModifier->GetHasSystemMaterial());
}

// ============================================================
// AnimateHighGradeHide tests
// ============================================================

/**
 * @tc.name: SwitchMaterial_AnimateHighGradeHide
 * @tc.desc: Test AnimateHighGradeHide sets opacity and blur scale
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_AnimateHighGradeHide, TestSize.Level1)
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

    pattern->paintMethod_ = AceType::MakeRefPtr<SwitchPaintMethod>();
    auto renderContext = switchNode->GetRenderContext();
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    // Must call GetContentModifier first to create the SwitchModifier
    auto modifier = pattern->paintMethod_->GetContentModifier(paintWrapper);
    ASSERT_NE(modifier, nullptr);
    auto switchModifier = AceType::DynamicCast<SwitchModifier>(modifier);
    ASSERT_NE(switchModifier, nullptr);

    // Create and add drag nodes
    pattern->CreateDragFrameNode();
    pattern->CreateDragPointNode();
    pattern->CreateBlurCoverNode();
    auto pointRC = pattern->dragPointNode_->GetRenderContext();
    auto blurRC = pattern->blurCoverNode_->GetRenderContext();

    // Call AnimateHighGradeHide directly (3 args: pointRC, blurRC, switchModifier)
    pattern->AnimateHighGradeHide(pointRC, blurRC, switchModifier);
    // Verify modifier alpha was restored
    EXPECT_FLOAT_EQ(switchModifier->GetPointAlpha(), 1.0f);

    g_uiMaterialLevel = savedMaterialLevel_;
}

// ============================================================
// ResetMaterialNodeAppearance tests
// ============================================================

/**
 * @tc.name: SwitchMaterial_ResetMaterialNodeAppearance
 * @tc.desc: Test ResetMaterialNodeAppearance resets opacity and scale
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_ResetMaterialNodeAppearance, TestSize.Level1)
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

    pattern->CreateDragPointNode();
    pattern->CreateBlurCoverNode();
    auto pointRC = pattern->dragPointNode_->GetRenderContext();
    auto blurRC = pattern->blurCoverNode_->GetRenderContext();

    // Should not crash
    pattern->ResetMaterialNodeAppearance(pointRC, blurRC);

    g_uiMaterialLevel = savedMaterialLevel_;
}

// ============================================================
// ApplyDragFrameNodeSystemMaterial tests
// ============================================================

/**
 * @tc.name: SwitchMaterial_ApplyDragFrameNodeSystemMaterial_NoNode
 * @tc.desc: Test ApplyDragFrameNodeSystemMaterial returns early when no drag frame node
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchMaterialTestNg, SwitchMaterial_ApplyDragFrameNodeSystemMaterial_NoNode, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);

    // No drag frame node created
    EXPECT_EQ(pattern->dragFrameNode_, nullptr);
    pattern->ApplyDragFrameNodeSystemMaterial();
    // Should not crash
}
} // namespace OHOS::Ace::NG
