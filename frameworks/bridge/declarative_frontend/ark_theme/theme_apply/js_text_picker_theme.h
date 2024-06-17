/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_THEME_JS_TEXTPICKER_THEME_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_THEME_JS_TEXTPICKER_THEME_H

#include "bridge/declarative_frontend/ark_theme/theme_apply/js_theme_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/text_picker/textpicker_model.h"

namespace OHOS::Ace::Framework {
class JSTextPickerTheme {
public:
    static void ApplyTheme()
    {
        auto themePicker = JSViewAbstract::GetTheme<PickerTheme>();
        CHECK_NULL_VOID(themePicker);
        auto themeColors = JSThemeUtils::GetThemeColors();
        if (!themeColors) {
            return;
        }
        NG::PickerTextStyle textStyle;
        auto selectedStyle = themePicker->GetOptionStyle(true, false);
        textStyle.textColor = themeColors.value().FontEmphasize();
        textStyle.fontSize = selectedStyle.GetFontSize();
        textStyle.fontWeight = selectedStyle.GetFontWeight();
        TextPickerModel::GetInstance()->SetSelectedTextStyle(themePicker, textStyle);

        auto disappearStyle = themePicker->GetDisappearOptionStyle();
        textStyle.textColor = themeColors.value().FontPrimary();
        textStyle.fontSize = disappearStyle.GetFontSize();
        textStyle.fontWeight = disappearStyle.GetFontWeight();
        TextPickerModel::GetInstance()->SetDisappearTextStyle(themePicker, textStyle);

        auto normalStyle = themePicker->GetOptionStyle(false, false);
        textStyle.textColor = themeColors.value().FontPrimary();
        textStyle.fontSize = normalStyle.GetFontSize();
        textStyle.fontWeight = normalStyle.GetFontWeight();
        TextPickerModel::GetInstance()->SetNormalTextStyle(themePicker, textStyle);

        auto targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
        CHECK_NULL_VOID(targetNode);
        targetNode->MarkModifyDone();
    }

    static bool ObtainSelectedTextStyle(NG::PickerTextStyle& textStyle)
    {
        if (auto themeColors = JSThemeUtils::GetThemeColors(); themeColors.has_value()) {
            textStyle.textColor = themeColors.value().FontEmphasize();
            return true;
        }
        return false;
    }

    static bool ObtainTextStyle(NG::PickerTextStyle& textStyle)
    {
        if (auto themeColors = JSThemeUtils::GetThemeColors(); themeColors.has_value()) {
            textStyle.textColor = themeColors.value().FontPrimary();
            return true;
        }
        return false;
    }
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_THEME_JS_TEXTPICKER_THEME_H
