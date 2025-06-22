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
#include "core/components_ng/pattern/select/select_model.h"
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
    static void ParseMenuShowInSubWindowParam(
        const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam, bool isCheckThemeValue = true);
    static void ParseLayoutRegionMargin(const JSRef<JSVal>& jsValue, std::optional<CalcDimension>& calcDimension);
    static void ParseLayoutRegionMargin(const JSRef<JSVal>& jsValue, std::optional<CalcDimension>& calcDimension,
        RefPtr<ResourceObject>& resObj);
    static void ParseResLayoutRegionMargin(const RefPtr<ResourceObject>& resObj,
        std::optional<CalcDimension>& calcDimension);
    static void ParseMenuLayoutRegionMarginParam(const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam);
    static void ParseMenuBlurStyleOption(const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam);
    static void ParseMenuBorderRadius(const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam);
    static void ParseMenuEffectOption(const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam);
    static void ParseMenuParam(
        const JSCallbackInfo& info, const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam);
    static void ParseMenuAppearLifeCycleParam(
        const JSCallbackInfo& info, const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam);
    static void ParseMenuDisappearLifeCycleParam(
        const JSCallbackInfo& info, const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam);
    static void ParseBindOptionParam(const JSCallbackInfo& info, NG::MenuParam& menuParam, size_t optionIndex);
    static void ParseMenuHapticFeedbackMode(const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam);
    static void ParseMenuOutlineWidth(const JSRef<JSVal>& outlineWidthValue, NG::MenuParam& menuParam);
    static void ParseMenuOutlineColor(const JSRef<JSVal>& outlineColorValue, NG::MenuParam& menuParam);
    static void ParseMenuPreviewScaleMode(const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam);
    static void ParseMenuAvailableLayoutArea(const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam);
    static void ParseMenuMaskType(const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam);
    static void ParseMenuModalMode(const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam);
    static void ParseMenuoffsetParam(const JSRef<JSObject>& offsetObj, NG::MenuParam& menuParam);
private:
    static void ParseMenuOutlineColorObject(const JSRef<JSVal>& outlineColorValue, NG::MenuParam& menuParam,
        NG::BorderColorProperty& outlineColor);
    static void ParseMenuOutlineColorWithResourceObj(const RefPtr<ResourceObject>& leftColorResObj,
        const RefPtr<ResourceObject>& rightColorResObj, const RefPtr<ResourceObject>& topColorResObj,
        const RefPtr<ResourceObject>& bottomColorResObj, NG::BorderColorProperty& outlineColor);
    static void ParseMenuOutlineColorWithResourceObj(const RefPtr<ResourceObject>& borderColorResObj,
        NG::BorderColorProperty& outlineColor);
    static void ParseMenuOutlineWidthObject(const JSRef<JSVal>& outlineWidthValue, NG::MenuParam& menuParam,
        NG::BorderWidthProperty& outlineWidth);
    static void ParseMenuOutlineWidthWithResourceObj(const RefPtr<ResourceObject>& borderWidthResObj,
        NG::BorderWidthProperty& outlineWidth);
    static void ParseMenuOutlineWidthWithResourceObj(const RefPtr<ResourceObject>& leftResObj,
        const RefPtr<ResourceObject>& rightResObj, const RefPtr<ResourceObject>& topResObj,
        const RefPtr<ResourceObject>& bottomResObj, NG::BorderWidthProperty& outlineWidth);
    static void ParseMenuBorderRadiusWithResourceObj(const RefPtr<ResourceObject>& borderRadiusResObj,
        NG::BorderRadiusProperty& menuBorderRadius);
};
} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_POPUPS_H