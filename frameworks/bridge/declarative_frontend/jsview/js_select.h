/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SELECT_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SELECT_H

#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {
enum class SelectFontType {
    SELECT = 0,
    OPTION,
    SELECTED_OPTION,
};
class JSSelect : public JSViewAbstract {
public:
    static void Create(const JSCallbackInfo& info);
    static void JSBind(BindingTarget globalObj);
    static bool IsPercentStr(std::string& percent);

    static void Selected(const JSCallbackInfo& info);
    static void Value(const JSCallbackInfo& info);
    static void Font(const JSCallbackInfo& info);
    static void FontColor(const JSCallbackInfo& info);
    static void SelectedOptionBgColor(const JSCallbackInfo& info);
    static void SelectedOptionFont(const JSCallbackInfo& info);
    static void SelectedOptionFontColor(const JSCallbackInfo& info);
    static void OptionBgColor(const JSCallbackInfo& info);
    static void OptionFont(const JSCallbackInfo& info);
    static void OptionFontColor(const JSCallbackInfo& info);
    static void OnSelected(const JSCallbackInfo& info);
    static void JsWidth(const JSCallbackInfo& info);
    static void JsHeight(const JSCallbackInfo& info);
    static void JsSize(const JSCallbackInfo& info);
    static void JsPadding(const JSCallbackInfo& info);
    static void SetPaddingTop(const JSCallbackInfo& info);
    static void SetPaddingBottom(const JSCallbackInfo& info);
    static void SetPaddingLeft(const JSCallbackInfo& info);
    static void SetPaddingRight(const JSCallbackInfo& info);
    static void SetSpace(const JSCallbackInfo& info);
    static void SetArrowPosition(const JSCallbackInfo& info);
    static void SetMenuAlign(const JSCallbackInfo& info);
    static void SetAvoidance(const JSCallbackInfo& info);
    static void SetOptionWidth(const JSCallbackInfo& info);
    static void SetOptionHeight(const JSCallbackInfo& info);
    static void SetOptionWidthFitTrigger(const JSCallbackInfo& info);
    static void SetMenuBackgroundColor(const JSCallbackInfo& info);
    static void SetMenuBackgroundBlurStyle(const JSCallbackInfo& info);
    static void SetDivider(const JSCallbackInfo& info);
    static bool CheckDividerValue(const Dimension &dimension);
    static void SetControlSize(const JSCallbackInfo& info);
    static void SetDirection(const std::string& dir);
    static void BackgroundColor(const JSCallbackInfo& info);
    static void SetDividerStyle(const JSCallbackInfo& info);
    static void SetMenuOutline(const JSCallbackInfo& info);

    static void ParseFontSize(const JSRef<JSVal>& jsValue, SelectFontType type);
    static void ParseFontWeight(const JSRef<JSVal>& jsValue, SelectFontType type);
    static void ParseFontFamily(const JSRef<JSVal>& jsValue, SelectFontType type);
    static void ParseFontStyle(const JSRef<JSVal>& jsValue, SelectFontType type);
    static void ResetFontSize(SelectFontType type);
    static void ResetFontWeight(SelectFontType type);
    static void ResetFontFamily(SelectFontType type);
    static void ResetFontStyle(SelectFontType type);
    static void ResetFont(SelectFontType type);
};
} // namespace OHOS::Ace::Framework
#endif
