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
#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_POPUPS_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_POPUPS_H
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
namespace OHOS::Ace::Framework {
class JSViewPopups {
public:
    using DoubleBindCallback = std::function<void(const std::string&)>;
#ifndef WEARABLE_PRODUCT
    static DoubleBindCallback ParseDoubleBindCallback(
        const JSCallbackInfo& info, const JSRef<JSObject>& callbackObj, const char* arrowFuncName);
#endif
    static std::vector<NG::OptionParam> ParseBindOptionParam(const JSCallbackInfo& info, size_t optionIndex);
    static void GetMenuShowInSubwindow(NG::MenuParam& menuParam);
    static void ParseMenuArrowParam(const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam);
    static void ParseLayoutRegionMargin(const JSRef<JSVal>& jsValue, std::optional<CalcDimension>& calcDimension);
    static void ParseMenuLayoutRegionMarginParam(const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam);
    static void ParseMenuBlurStyleOption(const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam);
    static void ParseMenuBorderRadius(const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam);
    static void ParseMenuEffectOption(const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam);
    static void ParseMenuParam(
        const JSCallbackInfo& info, const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam);
    static void ParseBindOptionParam(const JSCallbackInfo& info, NG::MenuParam& menuParam, size_t optionIndex);
    static void ParseMenuHapticFeedbackMode(const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam);
};
} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_POPUPS_H