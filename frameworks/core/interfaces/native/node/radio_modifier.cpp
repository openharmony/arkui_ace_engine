/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/radio_modifier.h"

#include "core/pipeline/base/element_register.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components/common/layout/constants.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/pattern/radio/radio_model_ng.h"

namespace OHOS::Ace::NG {
constexpr bool DEFAULT_CHECKED = false;
void SetRadioChecked(NodeHandle node, bool isCheck)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RadioModelNG::SetChecked(frameNode, isCheck);
}

void ResetRadioChecked(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RadioModelNG::SetChecked(frameNode, DEFAULT_CHECKED);
}

void SetRadioStyle(NodeHandle node,
    uint32_t checkedBackgroundColor, uint32_t uncheckedBorderColor, uint32_t indicatorColor)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    RadioModelNG::SetCheckedBackgroundColor(frameNode, Color(checkedBackgroundColor));
    RadioModelNG::SetUncheckedBorderColor(frameNode, Color(uncheckedBorderColor));
    RadioModelNG::SetIndicatorColor(frameNode, Color(indicatorColor));
}

void ResetRadioStyle(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto theme = themeManager->GetTheme<RadioTheme>();
    CHECK_NULL_VOID(theme);

    RadioModelNG::SetCheckedBackgroundColor(frameNode, theme->GetActiveColor());
    RadioModelNG::SetUncheckedBorderColor(frameNode, theme->GetInactiveColor());
    RadioModelNG::SetIndicatorColor(frameNode, theme->GetPointColor());
}

ArkUIRadioModifierAPI GetRadioModifier()
{
    static const ArkUIRadioModifierAPI modifier = {SetRadioChecked, ResetRadioChecked, SetRadioStyle, ResetRadioStyle};

    return modifier;
}
}