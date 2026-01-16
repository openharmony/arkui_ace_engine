/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FOUNDATION_ACE_CAPI_TEST_SECURITY_COMPONENT_METHOD_H
#define FOUNDATION_ACE_CAPI_TEST_SECURITY_COMPONENT_METHOD_H

#include <gtest/gtest.h>

#include "generated/test_fixtures.h"
#include "generated/type_helpers.h"
#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/components_ng/pattern/security_component/save_button/save_button_model_ng.h"
#include "core/components_ng/pattern/security_component/security_component_model_ng.h"
#include "core/components_ng/pattern/security_component/security_component_pattern.h"
#include "core/components_ng/pattern/security_component/security_component_theme.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG {
using namespace Converter;
using namespace TypeHelper;

namespace TestConst::SecurityComponentMethod {
const auto ATTRIBUTE_POSITION_NAME = "position";
const auto ATTRIBUTE_MARK_ANCHOR_NAME = "markAnchor";
const auto ATTRIBUTE_SIZE_NAME = "size";
const auto ATTRIBUTE_CONSTRAINT_SIZE_NAME = "constraintSize";
const auto ATTRIBUTE_ICON_SIZE_NAME = "iconSize";
const auto ATTRIBUTE_ICON_SIZE_DEFAULT_VALUE = "16.00vp";
const auto ATTRIBUTE_LAYOUT_DIRECTION_NAME = "layoutDirection";
const auto ATTRIBUTE_LAYOUT_DIRECTION_DEFAULT_VALUE = SecurityComponentLayoutDirection::HORIZONTAL;
const auto ATTRIBUTE_POSITION_X_NAME = "x";
const auto ATTRIBUTE_POSITION_X_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_POSITION_Y_NAME = "y";
const auto ATTRIBUTE_POSITION_Y_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_FONT_SIZE_NAME = "fontSize";
const auto ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE = "16.00fp";
const auto ATTRIBUTE_FONT_STYLE_NAME = "fontStyle";
const auto ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE = Ace::FontStyle::NORMAL;
const auto ATTRIBUTE_FONT_WEIGHT_NAME = "fontWeight";
const auto ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE = "FontWeight.Medium";
const auto ATTRIBUTE_FONT_COLOR_NAME = "fontColor";
const auto ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE = "#FFFFFFA0";
const auto ATTRIBUTE_ICON_COLOR_NAME = "iconColor";
const auto ATTRIBUTE_ICON_COLOR_DEFAULT_VALUE = "#FFFFFFA1";
const auto ATTRIBUTE_BACKGROUND_COLOR_NAME = "backgroundColor";
const auto ATTRIBUTE_BACKGROUND_COLOR_DEFAULT_VALUE = "#FFFFFFA2";
const auto ATTRIBUTE_BORDER_STYLE_NAME = "borderStyle";
const auto ATTRIBUTE_BORDER_STYLE_DEFAULT_VALUE = BorderStyle::NONE;
const auto ATTRIBUTE_BORDER_WIDTH_NAME = "borderWidth";
const auto ATTRIBUTE_BORDER_WIDTH_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_BORDER_COLOR_NAME = "borderColor";
const auto ATTRIBUTE_BORDER_COLOR_DEFAULT_VALUE = "#FFFFFFA3";
const auto ATTRIBUTE_BORDER_RADIUS_NAME = "borderRadius";
const auto ATTRIBUTE_BORDER_RADIUS_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_TEXT_ICON_SPACE_NAME = "textIconSpace";
const auto ATTRIBUTE_TEXT_ICON_SPACE_DEFAULT_VALUE = "4vp";
const auto ATTRIBUTE_KEY_NAME = "id";
const auto ATTRIBUTE_KEY_DEFAULT_VALUE = "";
const auto ATTRIBUTE_WIDTH_NAME = "width";
const auto ATTRIBUTE_WIDTH_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_HEIGHT_NAME = "height";
const auto ATTRIBUTE_HEIGHT_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_CONSTRAINT_SIZE_MIN_WIDTH_NAME = "minWidth";
const auto ATTRIBUTE_CONSTRAINT_SIZE_MIN_WIDTH_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_CONSTRAINT_SIZE_MAX_WIDTH_NAME = "maxWidth";
const auto ATTRIBUTE_CONSTRAINT_SIZE_MAX_WIDTH_DEFAULT_VALUE = "Infinityvp";
const auto ATTRIBUTE_CONSTRAINT_SIZE_MIN_HEIGHT_NAME = "minHeight";
const auto ATTRIBUTE_CONSTRAINT_SIZE_MIN_HEIGHT_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_CONSTRAINT_SIZE_MAX_HEIGHT_NAME = "maxHeight";
const auto ATTRIBUTE_CONSTRAINT_SIZE_MAX_HEIGHT_DEFAULT_VALUE = "Infinityvp";

const auto ATTRIBUTE_MARK_ANCHOR_X_NAME = "x";
const auto ATTRIBUTE_MARK_ANCHOR_X_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_MARK_ANCHOR_Y_NAME = "y";
const auto ATTRIBUTE_MARK_ANCHOR_Y_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_SIZE_HEIGHT_NAME = "height";
const auto ATTRIBUTE_SIZE_HEIGHT_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_SIZE_WIDTH_NAME = "width";
const auto ATTRIBUTE_SIZE_WIDTH_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_PADDING_NAME = "padding";
const auto ATTRIBUTE_PADDING_LEFT_NAME = "left";
const auto ATTRIBUTE_PADDING_LEFT_DEFAULT_VALUE = "24.00vp";
const auto ATTRIBUTE_PADDING_RIGHT_NAME = "right";
const auto ATTRIBUTE_PADDING_RIGHT_DEFAULT_VALUE = "24.00vp";
const auto ATTRIBUTE_PADDING_TOP_NAME = "top";
const auto ATTRIBUTE_PADDING_TOP_DEFAULT_VALUE = "12.00vp";
const auto ATTRIBUTE_PADDING_BOTTOM_NAME = "bottom";
const auto ATTRIBUTE_PADDING_BOTTOM_DEFAULT_VALUE = "12.00vp";
const auto ATTRIBUTE_FONT_FAMILY_NAME = "fontFamily";
const auto ATTRIBUTE_LEFT_NAME = "left";
const auto ATTRIBUTE_TOP_NAME = "top";
const auto ATTRIBUTE_RIGHT_NAME = "right";
const auto ATTRIBUTE_BOTTOM_NAME = "bottom";
const auto ATTRIBUTE_OFFSET_NAME = "offset";
const auto ATTRIBUTE_OFFSET_X_NAME = "x";
const auto ATTRIBUTE_OFFSET_X_DEFAULT_VALUE = "";
const auto ATTRIBUTE_OFFSET_Y_NAME = "y";
const auto ATTRIBUTE_OFFSET_Y_DEFAULT_VALUE = "";
const auto ATTRIBUTE_OFFSET_LEFT_NAME = "left";
const auto ATTRIBUTE_OFFSET_TOP_NAME = "top";
const auto ATTRIBUTE_OFFSET_RIGHT_NAME = "right";
const auto ATTRIBUTE_OFFSET_BOTTOM_NAME = "bottom";

const auto THEME_BACKGROUND_COLOR = Color(0xFFFFFFA2);
const auto THEME_BORDER_COLOR = Color(0xFFFFFFA3);
const auto THEME_FONT_COLOR = Color(0xFFFFFFA0);
const auto THEME_FONT_SIZE = Dimension(16., DimensionUnit::FP);
const auto THEME_ICON_COLOR = Color(0xFFFFFFA1);
const auto THEME_ICON_SIZE = Dimension(16., DimensionUnit::VP);
const auto THEME_TEXT_ICON_SPACE = Dimension(4., DimensionUnit::VP);

const auto DEFAULT_JSON_INT = -1;

const int64_t FLOAT_RES_0_ID = 1000;
const float FLOAT_RES_0_VALUE = 70.5f;
const auto FLOAT_RES_0_STORED_VALUE = Dimension(FLOAT_RES_0_VALUE, DimensionUnit::PX);
const Ark_Resource FLOAT_RES_0 = CreateResource(FLOAT_RES_0_ID, ResourceType::FLOAT);

const int64_t FLOAT_RES_1_ID = 1001;
const float FLOAT_RES_1_VALUE = 19.5f;
const auto FLOAT_RES_1_STORED_VALUE = Dimension(FLOAT_RES_1_VALUE, DimensionUnit::FP);
const Ark_Resource FLOAT_RES_1 = CreateResource(FLOAT_RES_1_ID, ResourceType::FLOAT);

const int64_t STRARRAY_RES_2_ID = 1002;
const std::string STRARRAY_RES_2_VALUE = "ResourceFontFamily";
const Ark_Resource STRARRAY_RES_2 = CreateResource(STRARRAY_RES_2_ID, ResourceType::STRARRAY);

class SecurityComponentMethodModifierTest : public ModifierTestBase<GENERATED_ArkUISecurityComponentMethodModifier,
    &GENERATED_ArkUINodeModifiers::getSecurityComponentMethodModifier, GENERATED_ARKUI_SAVE_BUTTON> {
public:
    void *CreateNodeImpl() override
    {
        return nodeModifiers_->getSaveButtonModifier()->construct(GetId(), 0);
    }

    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        // set test values to Theme Pattern as data for the Theme building
        auto themeStyle = SetupThemeStyle(THEME_PATTERN_SECURITY_COMPONENT);
        themeStyle->SetAttr("background_color", { .value = THEME_BACKGROUND_COLOR });
        themeStyle->SetAttr("border_color", { .value = THEME_BORDER_COLOR });
        themeStyle->SetAttr("icon_color", { .value = THEME_ICON_COLOR });
        themeStyle->SetAttr("icon_size", { .value = THEME_ICON_SIZE });
        themeStyle->SetAttr("font_color", { .value = THEME_FONT_COLOR });
        themeStyle->SetAttr("font_size", { .value = THEME_FONT_SIZE });
        themeStyle->SetAttr("text_icon_padding", { .value = THEME_TEXT_ICON_SPACE });

        SetupTheme<SecurityComponentTheme>();

        for (const auto &[resId, resName, value] : Fixtures::resourceInitTable) {
            AddResource(resId, value);
            AddResource(resName, value);
        }

        AddResource(FLOAT_RES_0_ID, FLOAT_RES_0_STORED_VALUE);
        AddResource(FLOAT_RES_1_ID, FLOAT_RES_1_STORED_VALUE);
        AddResource(STRARRAY_RES_2_ID, STRARRAY_RES_2_VALUE);
    }

    void SetUp(void) override
    {
        ModifierTestBase::SetUp();

        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        SaveButtonModelNG::InitSaveButton(frameNode, SaveButtonStyle(), false);

        OnModifyDone();
    }

    void OnModifyDone()
    {
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto pattern = frameNode->GetPattern();
        ASSERT_TRUE(pattern);
        pattern->OnModifyDone();
    }
};
} // namespace TestConst::SecurityComponentMethod
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_CAPI_TEST_SECURITY_COMPONENT_METHOD_H
