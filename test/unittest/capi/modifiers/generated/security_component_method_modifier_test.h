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

#ifndef GENERATED_FOUNDATION_ACE_CAPI_TEST_SECURITY_COMPONENT_METHOD_H
#define GENERATED_FOUNDATION_ACE_CAPI_TEST_SECURITY_COMPONENT_METHOD_H
#include <gtest/gtest.h>

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "test_fixtures.h"
#include "type_helpers.h"

#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;
namespace TestConst::SecurityComponentMethod {
const auto ATTRIBUTE_POSITION_NAME = "position";
const auto ATTRIBUTE_MARK_ANCHOR_NAME = "markAnchor";
const auto ATTRIBUTE_OFFSET_NAME = "offset";
const auto ATTRIBUTE_PADDING_NAME = "padding";
const auto ATTRIBUTE_SIZE_NAME = "size";
const auto ATTRIBUTE_ALIGN_RULES_NAME = "alignRules";
const auto ATTRIBUTE_ALIGN_RULES_I_LEFT_NAME = "left";
const auto ATTRIBUTE_ALIGN_RULES_I_RIGHT_NAME = "right";
const auto ATTRIBUTE_ALIGN_RULES_I_MIDDLE_NAME = "middle";
const auto ATTRIBUTE_ALIGN_RULES_I_TOP_NAME = "top";
const auto ATTRIBUTE_ALIGN_RULES_I_BOTTOM_NAME = "bottom";
const auto ATTRIBUTE_ALIGN_RULES_I_CENTER_NAME = "center";
const auto ATTRIBUTE_ALIGN_RULES_I_BIAS_NAME = "bias";
const auto ATTRIBUTE_ALIGN_RULES_I_START_NAME = "start";
const auto ATTRIBUTE_ALIGN_RULES_I_END_NAME = "end";
const auto ATTRIBUTE_POSITION_I_X_NAME = "x";
const auto ATTRIBUTE_POSITION_I_X_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_POSITION_I_Y_NAME = "y";
const auto ATTRIBUTE_POSITION_I_Y_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_MARK_ANCHOR_I_X_NAME = "x";
const auto ATTRIBUTE_MARK_ANCHOR_I_X_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_MARK_ANCHOR_I_Y_NAME = "y";
const auto ATTRIBUTE_MARK_ANCHOR_I_Y_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_OFFSET_I_X_NAME = "x";
const auto ATTRIBUTE_OFFSET_I_X_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_OFFSET_I_Y_NAME = "y";
const auto ATTRIBUTE_OFFSET_I_Y_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_OFFSET_I_TOP_NAME = "top";
const auto ATTRIBUTE_OFFSET_I_TOP_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_OFFSET_I_LEFT_NAME = "left";
const auto ATTRIBUTE_OFFSET_I_LEFT_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_OFFSET_I_BOTTOM_NAME = "bottom";
const auto ATTRIBUTE_OFFSET_I_BOTTOM_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_OFFSET_I_RIGHT_NAME = "right";
const auto ATTRIBUTE_OFFSET_I_RIGHT_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_OFFSET_I_START_NAME = "start";
const auto ATTRIBUTE_OFFSET_I_START_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_OFFSET_I_END_NAME = "end";
const auto ATTRIBUTE_OFFSET_I_END_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_PADDING_I_TOP_NAME = "top";
const auto ATTRIBUTE_PADDING_I_TOP_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_PADDING_I_RIGHT_NAME = "right";
const auto ATTRIBUTE_PADDING_I_RIGHT_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_PADDING_I_BOTTOM_NAME = "bottom";
const auto ATTRIBUTE_PADDING_I_BOTTOM_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_PADDING_I_LEFT_NAME = "left";
const auto ATTRIBUTE_PADDING_I_LEFT_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_TEXT_ICON_SPACE_NAME = "textIconSpace";
const auto ATTRIBUTE_TEXT_ICON_SPACE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_WIDTH_NAME = "width";
const auto ATTRIBUTE_WIDTH_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_SIZE_I_WIDTH_NAME = "width";
const auto ATTRIBUTE_SIZE_I_WIDTH_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_SIZE_I_HEIGHT_NAME = "height";
const auto ATTRIBUTE_SIZE_I_HEIGHT_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_ALIGN_RULES_I_LEFT_I_ANCHOR_NAME = "anchor";
const auto ATTRIBUTE_ALIGN_RULES_I_LEFT_I_ANCHOR_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_ALIGN_RULES_I_LEFT_I_ALIGN_NAME = "align";
const auto ATTRIBUTE_ALIGN_RULES_I_LEFT_I_ALIGN_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_ALIGN_RULES_I_RIGHT_I_ANCHOR_NAME = "anchor";
const auto ATTRIBUTE_ALIGN_RULES_I_RIGHT_I_ANCHOR_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_ALIGN_RULES_I_RIGHT_I_ALIGN_NAME = "align";
const auto ATTRIBUTE_ALIGN_RULES_I_RIGHT_I_ALIGN_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_ALIGN_RULES_I_MIDDLE_I_ANCHOR_NAME = "anchor";
const auto ATTRIBUTE_ALIGN_RULES_I_MIDDLE_I_ANCHOR_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_ALIGN_RULES_I_MIDDLE_I_ALIGN_NAME = "align";
const auto ATTRIBUTE_ALIGN_RULES_I_MIDDLE_I_ALIGN_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_ALIGN_RULES_I_TOP_I_ANCHOR_NAME = "anchor";
const auto ATTRIBUTE_ALIGN_RULES_I_TOP_I_ANCHOR_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_ALIGN_RULES_I_TOP_I_ALIGN_NAME = "align";
const auto ATTRIBUTE_ALIGN_RULES_I_TOP_I_ALIGN_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_ALIGN_RULES_I_BOTTOM_I_ANCHOR_NAME = "anchor";
const auto ATTRIBUTE_ALIGN_RULES_I_BOTTOM_I_ANCHOR_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_ALIGN_RULES_I_BOTTOM_I_ALIGN_NAME = "align";
const auto ATTRIBUTE_ALIGN_RULES_I_BOTTOM_I_ALIGN_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_ALIGN_RULES_I_CENTER_I_ANCHOR_NAME = "anchor";
const auto ATTRIBUTE_ALIGN_RULES_I_CENTER_I_ANCHOR_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_ALIGN_RULES_I_CENTER_I_ALIGN_NAME = "align";
const auto ATTRIBUTE_ALIGN_RULES_I_CENTER_I_ALIGN_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_ALIGN_RULES_I_BIAS_I_HORIZONTAL_NAME = "horizontal";
const auto ATTRIBUTE_ALIGN_RULES_I_BIAS_I_HORIZONTAL_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_ALIGN_RULES_I_BIAS_I_VERTICAL_NAME = "vertical";
const auto ATTRIBUTE_ALIGN_RULES_I_BIAS_I_VERTICAL_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_ALIGN_RULES_I_START_I_ANCHOR_NAME = "anchor";
const auto ATTRIBUTE_ALIGN_RULES_I_START_I_ANCHOR_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_ALIGN_RULES_I_START_I_ALIGN_NAME = "align";
const auto ATTRIBUTE_ALIGN_RULES_I_START_I_ALIGN_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_ALIGN_RULES_I_END_I_ANCHOR_NAME = "anchor";
const auto ATTRIBUTE_ALIGN_RULES_I_END_I_ANCHOR_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_ALIGN_RULES_I_END_I_ALIGN_NAME = "align";
const auto ATTRIBUTE_ALIGN_RULES_I_END_I_ALIGN_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_ID_NAME = "id";
const auto ATTRIBUTE_ID_DEFAULT_VALUE = "";
const auto ATTRIBUTE_MIN_FONT_SCALE_NAME = "minFontScale";
const auto ATTRIBUTE_MIN_FONT_SCALE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_MAX_FONT_SCALE_NAME = "maxFontScale";
const auto ATTRIBUTE_MAX_FONT_SCALE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_MAX_LINES_NAME = "maxLines";
const auto ATTRIBUTE_MAX_LINES_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_MIN_FONT_SIZE_NAME = "minFontSize";
const auto ATTRIBUTE_MIN_FONT_SIZE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_MAX_FONT_SIZE_NAME = "maxFontSize";
const auto ATTRIBUTE_MAX_FONT_SIZE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_ENABLED_NAME = "enabled";
const auto ATTRIBUTE_ENABLED_DEFAULT_VALUE = "true";
} // namespace TestConst::SecurityComponentMethod

class SecurityComponentMethodModifierTest
    : public ModifierTestBase<GENERATED_ArkUISecurityComponentMethodModifier,
          &GENERATED_ArkUINodeModifiers::getSecurityComponentMethodModifier, GENERATED_ARKUI_SECURITY_COMPONENT_METHOD>,
      public testing::WithParamInterface<int> {
public:
    void* CreateNodeImpl() override
    {
        typedef void* (*ConstructFunc)(Ark_Int32, Ark_Int32);
        const ConstructFunc constructors[] = {
            nodeModifiers_->getSaveButtonModifier()->construct,
        };
        if (GetParam() < std::size(constructors)) {
            return constructors[GetParam()](GetId(), 0);
        }
        return nullptr;
    }

    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        for (auto& [id, strid, res] : Fixtures::resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
    }
};

} // namespace OHOS::Ace::NG

#endif // GENERATED_FOUNDATION_ACE_CAPI_TEST_SECURITY_COMPONENT_METHOD_H
