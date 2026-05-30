/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except on compliance with the License.
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

#include <algorithm>
#include <cstddef>
#include <optional>
#include <utility>

#include "gtest/gtest.h"
#include "ui/base/utils/utils.h"

#define protected public
#define private public
#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/system_properties.h"
#include "core/common/ace_engine.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/security_component/location_button/location_button_common.h"
#include "core/components_ng/pattern/security_component/location_button/location_button_model_ng.h"
#include "core/components_ng/pattern/security_component/paste_button/paste_button_common.h"
#include "core/components_ng/pattern/security_component/paste_button/paste_button_model_ng.h"
#include "core/components_ng/pattern/security_component/save_button/save_button_common.h"
#include "core/components_ng/pattern/security_component/save_button/save_button_model_ng.h"
#include "core/components_ng/pattern/security_component/security_component_handler.h"
#include "core/components_ng/pattern/security_component/security_component_pattern.h"
#include "core/components_ng/pattern/security_component/security_component_paint_property.h"
#include "core/components_ng/pattern/security_component/security_component_layout_property.h"
#include "core/components_ng/pattern/security_component/security_component_theme.h"
#include "core/components_ng/pattern/symbol/constants.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "security_component_test_ng.h"
#undef protected
#undef private

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
const InspectorFilter filter;
constexpr float MIN_SIZE = 1.0f;
constexpr float ENLARGE_SIZE = 50.0f;
constexpr float DEFAULT_ICON_MIN_SIZE = 12.0f;
constexpr float TEST_FONT_SCALE = 2.0f;
constexpr int32_t TEST_MAX_LINES = 5;
constexpr float TEST_ADAPT_FONT_SIZE = 14.0f;
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLayoutAlgorithmCircleTest001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CIRCLE), V2::LOCATION_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SecurityComponentPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnModifyDone();

    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    property->UpdateMarginSelfIdealSize(SizeF(ENLARGE_SIZE, MIN_SIZE));
    property->UpdateContentConstraint();

    auto layoutAlgo = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgo, nullptr);

    auto layoutWrapper = CreateSecurityComponentLayoutWrapper(frameNode);
    ASSERT_NE(layoutWrapper, nullptr);
    layoutAlgo->Measure(layoutWrapper.rawPtr_);
    layoutAlgo->Layout(layoutWrapper.rawPtr_);

    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameSize().Height(), DEFAULT_ICON_MIN_SIZE);
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameSize().Width(), DEFAULT_ICON_MIN_SIZE);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLayoutAlgorithmCircleTest002, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CIRCLE), V2::SAVE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SecurityComponentPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnModifyDone();

    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    property->UpdateMarginSelfIdealSize(SizeF(MIN_SIZE, ENLARGE_SIZE));
    property->UpdateContentConstraint();

    auto layoutAlgo = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgo, nullptr);

    auto layoutWrapper = CreateSecurityComponentLayoutWrapper(frameNode);
    ASSERT_NE(layoutWrapper, nullptr);
    layoutAlgo->Measure(layoutWrapper.rawPtr_);
    layoutAlgo->Layout(layoutWrapper.rawPtr_);

    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameSize().Height(), DEFAULT_ICON_MIN_SIZE);
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameSize().Width(), DEFAULT_ICON_MIN_SIZE);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLayoutAlgorithmNormalTest001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::NORMAL), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SecurityComponentPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnModifyDone();

    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    property->UpdateMarginSelfIdealSize(SizeF(ENLARGE_SIZE, ENLARGE_SIZE));
    property->UpdateContentConstraint();

    auto layoutAlgo = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgo, nullptr);

    auto layoutWrapper = CreateSecurityComponentLayoutWrapper(frameNode);
    ASSERT_NE(layoutWrapper, nullptr);
    layoutAlgo->Measure(layoutWrapper.rawPtr_);
    layoutAlgo->Layout(layoutWrapper.rawPtr_);

    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameSize().Height(), ENLARGE_SIZE);
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameSize().Width(), ENLARGE_SIZE);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentOnDirtyLayoutWrapperSwapTest001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::LOCATION_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SecurityComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    auto layoutWrapper = CreateSecurityComponentLayoutWrapper(frameNode);
    ASSERT_NE(layoutWrapper, nullptr);
    DirtySwapConfig config;
    config.skipMeasure = true;
    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);

    config.skipMeasure = false;
    layoutWrapper->skipMeasureContent_ = true;
    result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentGetFocusPatternTest001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::SAVE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SecurityComponentPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnModifyDone();

    auto focusPattern = pattern->GetFocusPattern();
    EXPECT_EQ(focusPattern.focusType_, FocusType::NODE);
    EXPECT_TRUE(focusPattern.focusable_);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentGetFocusPatternTest002, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SecurityComponentPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnModifyDone();

    auto focusPattern = pattern->GetFocusPattern();
    EXPECT_EQ(focusPattern.focusType_, FocusType::NODE);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentSetNodeHitTestModeTest001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::LOCATION_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SecurityComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    auto iconNode = GetSecCompChildNode(frameNode, V2::IMAGE_ETS_TAG);
    ASSERT_NE(iconNode, nullptr);
    pattern->SetNodeHitTestMode(iconNode, HitTestMode::HTMTRANSPARENT);
    auto gestureHub = iconNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    EXPECT_EQ(gestureHub->GetHitTestMode(), HitTestMode::HTMTRANSPARENT);

    pattern->SetNodeHitTestMode(iconNode, HitTestMode::HTMDEFAULT);
    EXPECT_EQ(gestureHub->GetHitTestMode(), HitTestMode::HTMDEFAULT);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentSetFontScaleTest001, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::SAVE_BUTTON_ETS_TAG);
    SaveButtonModelNG saveSc;
    saveSc.SetMaxFontScale(TEST_FONT_SCALE);
    saveSc.SetMinFontScale(0.5f);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetMaxFontScale().value_or(1.0f), TEST_FONT_SCALE);
    EXPECT_EQ(property->GetMinFontScale().value_or(1.0f), 0.5f);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentSetFontScaleTest002, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::LOCATION_BUTTON_ETS_TAG);
    LocationButtonModelNG locationSc;
    locationSc.SetMaxFontScale(TEST_FONT_SCALE);
    locationSc.SetMinFontScale(0.5f);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetMaxFontScale().value_or(1.0f), TEST_FONT_SCALE);
    EXPECT_EQ(property->GetMinFontScale().value_or(1.0f), 0.5f);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentSetFontScaleTest003, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    PasteButtonModelNG pasteSc;
    pasteSc.SetMaxFontScale(TEST_FONT_SCALE);
    pasteSc.SetMinFontScale(0.5f);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetMaxFontScale().value_or(1.0f), TEST_FONT_SCALE);
    EXPECT_EQ(property->GetMinFontScale().value_or(1.0f), 0.5f);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentSetMaxLinesTest001, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::SAVE_BUTTON_ETS_TAG);
    SaveButtonModelNG saveSc;
    saveSc.SetMaxLines(TEST_MAX_LINES);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetMaxLines().value_or(1), TEST_MAX_LINES);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentSetMaxLinesTest002, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::LOCATION_BUTTON_ETS_TAG);
    LocationButtonModelNG locationSc;
    locationSc.SetMaxLines(TEST_MAX_LINES);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetMaxLines().value_or(1), TEST_MAX_LINES);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentSetAdaptFontSizeTest001, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::SAVE_BUTTON_ETS_TAG);
    SaveButtonModelNG saveSc;
    saveSc.SetAdaptMaxFontSize(Dimension(TEST_ADAPT_FONT_SIZE));
    saveSc.SetAdaptMinFontSize(Dimension(TEST_ADAPT_FONT_SIZE - 2.0f));

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetAdaptMaxFontSize().value_or(Dimension(0.0)).ConvertToVp(), TEST_ADAPT_FONT_SIZE);
    EXPECT_EQ(property->GetAdaptMinFontSize().value_or(Dimension(0.0)).ConvertToVp(), TEST_ADAPT_FONT_SIZE - 2.0f);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentSetAdaptFontSizeTest002, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::LOCATION_BUTTON_ETS_TAG);
    LocationButtonModelNG locationSc;
    locationSc.SetAdaptMaxFontSize(Dimension(TEST_ADAPT_FONT_SIZE));
    locationSc.SetAdaptMinFontSize(Dimension(TEST_ADAPT_FONT_SIZE - 2.0f));

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetAdaptMaxFontSize().value_or(Dimension(0.0)).ConvertToVp(), TEST_ADAPT_FONT_SIZE);
    EXPECT_EQ(property->GetAdaptMinFontSize().value_or(Dimension(0.0)).ConvertToVp(), TEST_ADAPT_FONT_SIZE - 2.0f);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentSetHeightAdaptivePolicyTest001, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::SAVE_BUTTON_ETS_TAG);
    SaveButtonModelNG saveSc;
    saveSc.SetHeightAdaptivePolicy(TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetHeightAdaptivePolicy().value_or(TextHeightAdaptivePolicy::MAX_LINES_FIRST),
        TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentSetHeightAdaptivePolicyTest002, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    PasteButtonModelNG pasteSc;
    pasteSc.SetHeightAdaptivePolicy(TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetHeightAdaptivePolicy().value_or(TextHeightAdaptivePolicy::MAX_LINES_FIRST),
        TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentPaintPropertyTest001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::SAVE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SecurityComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    auto scPaintProperty = AceType::DynamicCast<SecurityComponentPaintProperty>(paintProperty);
    ASSERT_NE(scPaintProperty, nullptr);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentPaintPropertyTest002, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::LOCATION_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SecurityComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    auto paintProperty = frameNode->GetPaintProperty<SecurityComponentPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentPaintPropertyTest003, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    PasteButtonModelNG pasteSc;
    pasteSc.SetIconColor(Color::RED);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<SecurityComponentPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetIconColor().value_or(Color()), Color::RED);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentIsParentMenuTest001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::SAVE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SecurityComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    EXPECT_FALSE(pattern->IsParentMenu(frameNode));
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentSetAlignTest001, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::SAVE_BUTTON_ETS_TAG);
    SaveButtonModelNG saveSc;
    saveSc.SetAlign(Alignment::TOP_LEFT);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetAlignment().value_or(Alignment::CENTER), Alignment::TOP_LEFT);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentSetAlignTest002, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::LOCATION_BUTTON_ETS_TAG);
    LocationButtonModelNG locationSc;
    locationSc.SetAlign(Alignment::BOTTOM_RIGHT);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetAlignment().value_or(Alignment::CENTER), Alignment::BOTTOM_RIGHT);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentSetAlignTest003, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    PasteButtonModelNG pasteSc;
    pasteSc.SetAlign(Alignment::CENTER);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetAlignment().value_or(Alignment::TOP_LEFT), Alignment::CENTER);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLayoutPropertyCloneTest001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::SAVE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);

    auto clonedProperty = property->Clone();
    ASSERT_NE(clonedProperty, nullptr);
    auto clonedScProperty = AceType::DynamicCast<SecurityComponentLayoutProperty>(clonedProperty);
    ASSERT_NE(clonedScProperty, nullptr);

    EXPECT_EQ(clonedScProperty->GetBackgroundType().value_or(-1),
        property->GetBackgroundType().value_or(-1));
    EXPECT_EQ(clonedScProperty->GetIconStyle().value_or(-1),
        property->GetIconStyle().value_or(-1));
    EXPECT_EQ(clonedScProperty->GetSecurityComponentDescription().value_or(-1),
        property->GetSecurityComponentDescription().value_or(-1));
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLayoutPropertyResetTest001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::LOCATION_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);

    property->UpdateBackgroundType(static_cast<int32_t>(ButtonType::CIRCLE));
    property->UpdateIconStyle(1);
    property->UpdateTextIconSpace(Dimension(25.0f));

    property->Reset();
    EXPECT_FALSE(property->GetBackgroundType().has_value());
    EXPECT_FALSE(property->GetIconStyle().has_value());
    EXPECT_FALSE(property->GetTextIconSpace().has_value());
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentInitOnClickTest001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::SAVE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SecurityComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    auto iconNode = GetSecCompChildNode(frameNode, V2::IMAGE_ETS_TAG);
    auto textNode = GetSecCompChildNode(frameNode, V2::TEXT_ETS_TAG);
    auto buttonNode = GetSecCompChildNode(frameNode, V2::BUTTON_ETS_TAG);

    ASSERT_NE(iconNode, nullptr);
    ASSERT_NE(textNode, nullptr);
    ASSERT_NE(buttonNode, nullptr);

    pattern->InitOnClick(frameNode, iconNode, textNode, buttonNode);
    EXPECT_NE(pattern->clickListener_, nullptr);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentInitOnKeyEventTest001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::LOCATION_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SecurityComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->isSetOnKeyEvent = false;
    EXPECT_FALSE(pattern->isSetOnKeyEvent);
    pattern->InitOnKeyEvent(frameNode);
    EXPECT_TRUE(pattern->isSetOnKeyEvent);

    pattern->InitOnKeyEvent(frameNode);
    EXPECT_TRUE(pattern->isSetOnKeyEvent);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentSetUserCancelEventTest001, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::SAVE_BUTTON_ETS_TAG);
    SaveButtonModelNG saveSc;
    saveSc.SetUserCancelEvent(true);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_TRUE(property->GetUserCancelEvent().value_or(false));
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentSetUserCancelEventTest002, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::LOCATION_BUTTON_ETS_TAG);
    LocationButtonModelNG locationSc;
    locationSc.SetUserCancelEvent(false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_FALSE(property->GetUserCancelEvent().value_or(true));
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentSetTipPositionTest001, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::SAVE_BUTTON_ETS_TAG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    property->UpdateHasCustomPermissionForSecComp(true);
    SaveButtonModelNG saveSc;
    saveSc.SetTipPosition(TipPosition::BELOW_TOP);

    EXPECT_EQ(property->GetTipPosition().value_or(TipPosition::ABOVE_BOTTOM), TipPosition::BELOW_TOP);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentSetTipPositionTest002, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::SAVE_BUTTON_ETS_TAG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    property->UpdateHasCustomPermissionForSecComp(true);
    SaveButtonModelNG saveSc;
    saveSc.SetTipPosition(TipPosition::ABOVE_BOTTOM);

    EXPECT_EQ(property->GetTipPosition().value_or(TipPosition::BELOW_TOP), TipPosition::ABOVE_BOTTOM);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentIsClickResultSuccessTest001, TestSize.Level0)
{
    LocationButtonModelNG locationSc;
    GestureEvent info;
    EXPECT_TRUE(locationSc.IsClickResultSuccess(info));
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentIsClickResultSuccessTest002, TestSize.Level0)
{
    SaveButtonModelNG saveSc;
    GestureEvent info;
    EXPECT_TRUE(saveSc.IsClickResultSuccess(info));
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentIsClickResultSuccessTest003, TestSize.Level0)
{
    PasteButtonModelNG pasteSc;
    GestureEvent info;
    EXPECT_TRUE(pasteSc.IsClickResultSuccess(info));
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentSetStateEffectTest001, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::SAVE_BUTTON_ETS_TAG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    property->UpdateHasCustomPermissionForSecComp(true);
    SaveButtonModelNG saveSc;
    saveSc.SetStateEffect(false);

    EXPECT_FALSE(property->GetStateEffect().value_or(true));
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentSetStateEffectTest002, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::LOCATION_BUTTON_ETS_TAG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    property->UpdateHasCustomPermissionForSecComp(true);
    LocationButtonModelNG locationSc;
    locationSc.SetStateEffect(true);

    EXPECT_TRUE(property->GetStateEffect().value_or(false));
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentCreateNodeTest001, TestSize.Level0)
{
    auto frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::SAVE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::SAVE_BUTTON_ETS_TAG);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentCreateNodeTest002, TestSize.Level0)
{
    auto frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::LOCATION_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::LOCATION_BUTTON_ETS_TAG);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentCreateNodeTest003, TestSize.Level0)
{
    auto frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::PASTE_BUTTON_ETS_TAG);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentVerticalLayoutTest001, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::SAVE_BUTTON_ETS_TAG);
    SaveButtonModelNG saveSc;
    saveSc.SetTextIconLayoutDirection(SecurityComponentLayoutDirection::VERTICAL);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetTextIconLayoutDirection().value_or(SecurityComponentLayoutDirection::HORIZONTAL),
        SecurityComponentLayoutDirection::VERTICAL);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentVerticalLayoutTest002, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::LOCATION_BUTTON_ETS_TAG);
    LocationButtonModelNG locationSc;
    locationSc.SetTextIconLayoutDirection(SecurityComponentLayoutDirection::VERTICAL);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetTextIconLayoutDirection().value_or(SecurityComponentLayoutDirection::HORIZONTAL),
        SecurityComponentLayoutDirection::VERTICAL);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentNoTextTest001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(-1, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::SAVE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);

    auto textNode = GetSecCompChildNode(frameNode, V2::TEXT_ETS_TAG);
    ASSERT_EQ(textNode, nullptr);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentNoTextTest002, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(-1, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::LOCATION_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);

    auto textNode = GetSecCompChildNode(frameNode, V2::TEXT_ETS_TAG);
    ASSERT_EQ(textNode, nullptr);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentNoTextTest003, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(-1, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);

    auto textNode = GetSecCompChildNode(frameNode, V2::TEXT_ETS_TAG);
    ASSERT_EQ(textNode, nullptr);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentBackgroundPaddingTest001, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::SAVE_BUTTON_ETS_TAG);
    SaveButtonModelNG saveSc;
    saveSc.SetBackgroundPadding(Dimension(20.0f), Dimension(20.0f), Dimension(20.0f), Dimension(20.0f));

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetBackgroundLeftPadding().value_or(Dimension(0.0)).ConvertToVp(), 20.0f);
    EXPECT_EQ(property->GetBackgroundRightPadding().value_or(Dimension(0.0)).ConvertToVp(), 20.0f);
    EXPECT_EQ(property->GetBackgroundTopPadding().value_or(Dimension(0.0)).ConvertToVp(), 20.0f);
    EXPECT_EQ(property->GetBackgroundBottomPadding().value_or(Dimension(0.0)).ConvertToVp(), 20.0f);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentBackgroundPaddingTest002, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::LOCATION_BUTTON_ETS_TAG);
    LocationButtonModelNG locationSc;
    locationSc.SetBackgroundPadding(Dimension(15.0f));

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetBackgroundLeftPadding().value_or(Dimension(0.0)).ConvertToVp(), 15.0f);
    EXPECT_EQ(property->GetBackgroundRightPadding().value_or(Dimension(0.0)).ConvertToVp(), 15.0f);
    EXPECT_EQ(property->GetBackgroundTopPadding().value_or(Dimension(0.0)).ConvertToVp(), 15.0f);
    EXPECT_EQ(property->GetBackgroundBottomPadding().value_or(Dimension(0.0)).ConvertToVp(), 15.0f);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentIsFontColorSetTest001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::SAVE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SecurityComponentPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnModifyDone();

    EXPECT_FALSE(pattern->IsFontColorSet());
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentIsFontColorSetTest002, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::LOCATION_BUTTON_ETS_TAG);
    LocationButtonModelNG locationSc;
    locationSc.SetFontColor(Color::RED);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<SecurityComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    EXPECT_TRUE(pattern->IsFontColorSet());
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentSymbolIconColorTest001, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::SAVE_BUTTON_ETS_TAG);
    SaveButtonModelNG saveSc;
    std::vector<Color> colors = {Color::RED, Color::GREEN};
    saveSc.SetSymbolIconColor(colors);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<SecurityComponentPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentSymbolIconSizeTest001, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::LOCATION_BUTTON_ETS_TAG);
    LocationButtonModelNG locationSc;
    locationSc.SetSymbolIconSize(Dimension(24.0f));

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetSymbolIconSize().value_or(Dimension(0.0)).ConvertToVp(), 24.0f);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentMultipleFontFamilyTest001, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::SAVE_BUTTON_ETS_TAG);
    SaveButtonModelNG saveSc;
    std::vector<std::string> fontFamilies = {"Font1", "Font2", "Font3"};
    saveSc.SetFontFamily(fontFamilies);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    auto result = property->GetFontFamily().value_or(std::vector<std::string>());
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], "Font1");
    EXPECT_EQ(result[1], "Font2");
    EXPECT_EQ(result[2], "Font3");
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentBorderRadiusPropertyTest001, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::LOCATION_BUTTON_ETS_TAG);
    LocationButtonModelNG locationSc;
    locationSc.SetBackgroundBorderRadius(
        Dimension(5.0f), Dimension(10.0f), Dimension(15.0f), Dimension(20.0f));

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    auto borderRadius = property->GetBackgroundBorderRadius();
    ASSERT_TRUE(borderRadius.has_value());
    EXPECT_EQ(borderRadius->radiusTopLeft.value_or(Dimension(0.0)).ConvertToVp(), 5.0f);
    EXPECT_EQ(borderRadius->radiusTopRight.value_or(Dimension(0.0)).ConvertToVp(), 10.0f);
    EXPECT_EQ(borderRadius->radiusBottomLeft.value_or(Dimension(0.0)).ConvertToVp(), 15.0f);
    EXPECT_EQ(borderRadius->radiusBottomRight.value_or(Dimension(0.0)).ConvertToVp(), 20.0f);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentIconBorderRadiusPropertyTest001, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::SAVE_BUTTON_ETS_TAG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    property->UpdateHasCustomPermissionForSecComp(true);
    SaveButtonModelNG saveSc;
    saveSc.SetIconBorderRadius(
        Dimension(3.0f), Dimension(4.0f), Dimension(5.0f), Dimension(6.0f));

    auto iconBorderRadius = property->GetIconBorderRadius();
    ASSERT_TRUE(iconBorderRadius.has_value());
    EXPECT_EQ(iconBorderRadius->radiusTopLeft.value_or(Dimension(0.0)).ConvertToVp(), 3.0f);
    EXPECT_EQ(iconBorderRadius->radiusTopRight.value_or(Dimension(0.0)).ConvertToVp(), 4.0f);
    EXPECT_EQ(iconBorderRadius->radiusBottomLeft.value_or(Dimension(0.0)).ConvertToVp(), 5.0f);
    EXPECT_EQ(iconBorderRadius->radiusBottomRight.value_or(Dimension(0.0)).ConvertToVp(), 6.0f);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentCalcIconSizeTest001, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    PasteButtonModelNG pasteSc;
    std::optional<NG::CalcLength> width(Dimension(18.0f));
    std::optional<NG::CalcLength> height(Dimension(18.0f));
    pasteSc.SetIconSize(NG::CalcSize(width, height));

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    auto iconCalcSize = property->GetIconCalcSize();
    ASSERT_TRUE(iconCalcSize.has_value());
    EXPECT_TRUE(iconCalcSize->Width().has_value());
    EXPECT_TRUE(iconCalcSize->Height().has_value());
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentAccessibilityPropertyTest001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::SAVE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SecurityComponentPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnModifyDone();

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<SecurityComponentAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
}

HWTEST_F(SecurityComponentModelTestNg, SecurityComponentAccessibilityPropertyTest002, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::LOCATION_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SecurityComponentPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnModifyDone();

    auto accessibilityProperty = pattern->CreateAccessibilityProperty();
    ASSERT_NE(accessibilityProperty, nullptr);
    auto scAccessibility = AceType::DynamicCast<SecurityComponentAccessibilityProperty>(accessibilityProperty);
    ASSERT_NE(scAccessibility, nullptr);
}

} // namespace OHOS::Ace::NG