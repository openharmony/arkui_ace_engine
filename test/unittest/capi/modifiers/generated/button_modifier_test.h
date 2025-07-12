/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#ifndef GENERATED_FOUNDATION_ACE_CAPI_TEST_BUTTON_H
#define GENERATED_FOUNDATION_ACE_CAPI_TEST_BUTTON_H
#include <gtest/gtest.h>

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "test_fixtures.h"
#include "type_helpers.h"

#include "core/components/button/button_theme.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;
namespace TestConst::Button {
const auto ATTRIBUTE_LABEL_STYLE_NAME = "labelStyle";
const auto ATTRIBUTE_LABEL_STYLE_I_FONT_NAME = "font";
const auto ATTRIBUTE_TYPE_NAME = "type";
const auto ATTRIBUTE_TYPE_DEFAULT_VALUE = "ButtonType.Capsule";
const auto ATTRIBUTE_STATE_EFFECT_NAME = "stateEffect";
const auto ATTRIBUTE_STATE_EFFECT_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_BUTTON_STYLE_NAME = "buttonStyle";
const auto ATTRIBUTE_BUTTON_STYLE_DEFAULT_VALUE = "ButtonStyleMode.EMPHASIZED";
const auto ATTRIBUTE_CONTROL_SIZE_NAME = "controlSize";
const auto ATTRIBUTE_CONTROL_SIZE_DEFAULT_VALUE = "ControlSize.NORMAL";
const auto ATTRIBUTE_ROLE_NAME = "role";
const auto ATTRIBUTE_ROLE_DEFAULT_VALUE = "ButtonRole.NORMAL";
const auto ATTRIBUTE_LABEL_NAME = "label";
const auto ATTRIBUTE_LABEL_DEFAULT_VALUE = "";
const auto ATTRIBUTE_FONT_COLOR_NAME = "fontColor";
const auto ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_FONT_SIZE_NAME = "fontSize";
const auto ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_FONT_WEIGHT_NAME = "fontWeight";
const auto ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE = "FontWeight.Medium";
const auto ATTRIBUTE_FONT_STYLE_NAME = "fontStyle";
const auto ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE = "FontStyle.Normal";
const auto ATTRIBUTE_FONT_FAMILY_NAME = "fontFamily";
const auto ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE = "Harmony"
                                                 "OS Sans";
const auto ATTRIBUTE_LABEL_STYLE_I_OVERFLOW_NAME = "overflow";
const auto ATTRIBUTE_LABEL_STYLE_I_OVERFLOW_DEFAULT_VALUE = "TextOverflow.Ellipsis";
const auto ATTRIBUTE_LABEL_STYLE_I_MAX_LINES_NAME = "maxLines";
const auto ATTRIBUTE_LABEL_STYLE_I_MAX_LINES_DEFAULT_VALUE = "1";
const auto ATTRIBUTE_LABEL_STYLE_I_MIN_FONT_SIZE_NAME = "minFontSize";
const auto ATTRIBUTE_LABEL_STYLE_I_MIN_FONT_SIZE_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_LABEL_STYLE_I_MAX_FONT_SIZE_NAME = "maxFontSize";
const auto ATTRIBUTE_LABEL_STYLE_I_MAX_FONT_SIZE_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_LABEL_STYLE_I_HEIGHT_ADAPTIVE_POLICY_NAME = "heightAdaptivePolicy";
const auto ATTRIBUTE_LABEL_STYLE_I_HEIGHT_ADAPTIVE_POLICY_DEFAULT_VALUE = "TextHeightAdaptivePolicy.MAX_LINES_FIRST";
const auto ATTRIBUTE_LABEL_STYLE_I_FONT_I_SIZE_NAME = "size";
const auto ATTRIBUTE_LABEL_STYLE_I_FONT_I_SIZE_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_LABEL_STYLE_I_FONT_I_WEIGHT_NAME = "weight";
const auto ATTRIBUTE_LABEL_STYLE_I_FONT_I_WEIGHT_DEFAULT_VALUE = "FontWeight.Medium";
const auto ATTRIBUTE_LABEL_STYLE_I_FONT_I_FAMILY_NAME = "family";
const auto ATTRIBUTE_LABEL_STYLE_I_FONT_I_FAMILY_DEFAULT_VALUE = "Harmony"
                                                                 "OS Sans";
const auto ATTRIBUTE_LABEL_STYLE_I_FONT_I_STYLE_NAME = "style";
const auto ATTRIBUTE_LABEL_STYLE_I_FONT_I_STYLE_DEFAULT_VALUE = "FontStyle.Normal";
const auto ATTRIBUTE_MIN_FONT_SCALE_NAME = "minFontScale";
const auto ATTRIBUTE_MIN_FONT_SCALE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_MAX_FONT_SCALE_NAME = "maxFontScale";
const auto ATTRIBUTE_MAX_FONT_SCALE_DEFAULT_VALUE = "!NOT-DEFINED!";
} // namespace TestConst::Button

class ButtonModifierTest : public ModifierTestBase<GENERATED_ArkUIButtonModifier,
                               &GENERATED_ArkUINodeModifiers::getButtonModifier, GENERATED_ARKUI_BUTTON> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<ButtonTheme>();

        for (auto& [id, strid, res] : Fixtures::resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
    }
};

} // namespace OHOS::Ace::NG

#endif // GENERATED_FOUNDATION_ACE_CAPI_TEST_BUTTON_H
