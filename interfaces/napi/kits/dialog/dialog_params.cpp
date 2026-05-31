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

#include "dialog_params.h"

#include "base/error/error_code.h"
#include "base/log/log.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/common/utils/utils.h"
#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/components/common/properties/ui_material.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components_ng/event/click_event.h"
#include "core/components_ng/pattern/overlay/level_order.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "interfaces/napi/kits/utils/napi_utils.h"

namespace OHOS::Ace {
namespace {
using Napi::ParseNapiColor;
using Napi::ParseNapiDimension;
using Napi::ParseNapiDimensionNG;
using Napi::ParseShadowColorStrategy;
using Napi::ParseStyle;

constexpr int32_t DIALOG_BUTTON_NUM_MAX = 3;
constexpr int32_t CALLBACK_TYPE_SUCCESS = 0;
constexpr int32_t CALLBACK_TYPE_MOUNT_ERROR = 2;

const std::vector<DialogDisplayModeInSubWindow> DIALOG_DISPLAY_MODE_IN_SUBWINDOW = {
    DialogDisplayModeInSubWindow::SCREEN_BASED, DialogDisplayModeInSubWindow::WINDOW_BASED };
const std::vector<KeyboardAvoidMode> KEYBOARD_AVOID_MODE = { KeyboardAvoidMode::DEFAULT, KeyboardAvoidMode::NONE };
const std::vector<HoverModeAreaType> HOVER_MODE_AREA_TYPE = {
    HoverModeAreaType::TOP_SCREEN, HoverModeAreaType::BOTTOM_SCREEN };
const std::vector<LevelMode> DIALOG_LEVEL_MODE = { LevelMode::OVERLAY, LevelMode::EMBEDDED };
const std::vector<ImmersiveMode> DIALOG_IMMERSIVE_MODE = { ImmersiveMode::DEFAULT, ImmersiveMode::EXTEND };

void ResolvePromise(napi_env env, napi_deferred deferred, int32_t index)
{
    napi_value result = nullptr;
    napi_create_object(env, &result);
    napi_value indexValue = nullptr;
    napi_create_int32(env, index, &indexValue);
    napi_set_named_property(env, result, "index", indexValue);
    napi_resolve_deferred(env, deferred, result);
}

void ResolvePromiseWithId(napi_env env, napi_deferred deferred, int32_t dialogId)
{
    napi_value result = nullptr;
    napi_create_int32(env, dialogId, &result);
    napi_resolve_deferred(env, deferred, result);
}

void ResolvePromiseVoid(napi_env env, napi_deferred deferred)
{
    napi_value result = nullptr;
    napi_get_undefined(env, &result);
    napi_resolve_deferred(env, deferred, result);
}

void GetClickAction(napi_env env, napi_value obj, const char* propName, RefPtr<NG::ClickEvent>& action)
{
    std::function<void()> callback;
    if (Napi::GetVoidCallbackProperty(env, obj, propName, callback)) {
        auto gestureCallback = [cb = std::move(callback)](GestureEvent& info) mutable { cb(); };
        action = AceType::MakeRefPtr<NG::ClickEvent>(std::move(gestureCallback));
    }
}

void GetDialogButton(napi_env env, napi_value buttonObj, ButtonInfo& buttonInfo)
{
    Napi::GetStringProperty(env, buttonObj, "value", buttonInfo.text);
    GetClickAction(env, buttonObj, "action", buttonInfo.action);
    Napi::GetBoolProperty(env, buttonObj, "enabled", buttonInfo.enabled);
    Napi::GetBoolProperty(env, buttonObj, "defaultFocus", buttonInfo.defaultFocus);
    Napi::GetBoolProperty(env, buttonObj, "primary", buttonInfo.isPrimary);

    napi_value fontColorApi = nullptr;
    napi_get_named_property(env, buttonObj, "fontColor", &fontColorApi);
    Color fontColor;
    if (ParseNapiColor(env, fontColorApi, fontColor)) {
        buttonInfo.fontColor = fontColor;
    }

    napi_value bgColorApi = nullptr;
    napi_get_named_property(env, buttonObj, "backgroundColor", &bgColorApi);
    Color bgColor;
    if (ParseNapiColor(env, bgColorApi, bgColor)) {
        buttonInfo.backgroundColor = bgColor;
    }

    int32_t buttonStyle = 0;
    if (Napi::GetInt32Property(env, buttonObj, "style", buttonStyle)) {
        buttonInfo.dlgButtonStyle = static_cast<DialogButtonStyle>(buttonStyle);
    }
}

void GetDialogButtons(napi_env env, napi_value options, DialogProperties& dialogProps)
{
    napi_value buttonsNApi = nullptr;
    napi_valuetype valueType = napi_undefined;
    napi_get_named_property(env, options, "buttons", &buttonsNApi);
    napi_typeof(env, buttonsNApi, &valueType);
    if (valueType != napi_object) {
        return;
    }
    bool isArray = false;
    napi_is_array(env, buttonsNApi, &isArray);
    if (!isArray) {
        return;
    }
    uint32_t arrayLength = 0;
    napi_get_array_length(env, buttonsNApi, &arrayLength);
    if (arrayLength == 0 || arrayLength > static_cast<uint32_t>(DIALOG_BUTTON_NUM_MAX)) {
        return;
    }
    for (uint32_t i = 0; i < arrayLength; ++i) {
        napi_value buttonObj = nullptr;
        napi_get_element(env, buttonsNApi, i, &buttonObj);
        ButtonInfo buttonInfo;
        GetDialogButton(env, buttonObj, buttonInfo);
        dialogProps.buttons.push_back(buttonInfo);
    }
}

void GetDialogSheet(napi_env env, napi_value sheetObj, ActionSheetInfo& sheetInfo)
{
    Napi::GetStringProperty(env, sheetObj, "title", sheetInfo.title);
    Napi::GetStringProperty(env, sheetObj, "icon", sheetInfo.icon);
    GetClickAction(env, sheetObj, "action", sheetInfo.action);
}

void GetDialogSheets(napi_env env, napi_value options, DialogProperties& dialogProps)
{
    napi_value sheetsNApi = nullptr;
    napi_valuetype valueType = napi_undefined;
    napi_get_named_property(env, options, "sheets", &sheetsNApi);
    napi_typeof(env, sheetsNApi, &valueType);
    if (valueType != napi_object) {
        return;
    }
    bool isArray = false;
    napi_is_array(env, sheetsNApi, &isArray);
    if (!isArray) {
        return;
    }
    uint32_t arrayLength = 0;
    napi_get_array_length(env, sheetsNApi, &arrayLength);
    if (arrayLength == 0) {
        return;
    }
    for (uint32_t i = 0; i < arrayLength; ++i) {
        napi_value sheetObj = nullptr;
        napi_get_element(env, sheetsNApi, i, &sheetObj);
        ActionSheetInfo sheetInfo;
        GetDialogSheet(env, sheetObj, sheetInfo);
        dialogProps.sheetsInfo.push_back(sheetInfo);
    }
}

void GetDialogMessage(napi_env env, napi_value options, DialogProperties& dialogProps)
{
    napi_value messageNApi = nullptr;
    napi_valuetype valueType = napi_undefined;
    napi_get_named_property(env, options, "message", &messageNApi);
    napi_typeof(env, messageNApi, &valueType);
    if (valueType == napi_object) {
        Napi::GetStringProperty(env, messageNApi, "content", dialogProps.content);
        int32_t wordBreak = 0;
        if (Napi::GetInt32Property(env, messageNApi, "wordBreak", wordBreak)) {
            dialogProps.wordBreak = static_cast<WordBreak>(wordBreak);
        }
    }
}

void GetDialogButtonDirection(napi_env env, napi_value options, DialogProperties& dialogProps)
{
    int32_t buttonDir = 0;
    if (Napi::GetInt32Property(env, options, "buttonDirection", buttonDir)) {
        dialogProps.buttonDirection = static_cast<DialogButtonDirection>(buttonDir);
    }
}

void GetDialogAlignment(napi_env env, napi_value options, DialogProperties& dialogProps)
{
    int32_t alignment = 0;
    if (Napi::GetInt32Property(env, options, "alignment", alignment)) {
        dialogProps.alignment = static_cast<DialogAlignment>(alignment);
    }
}

napi_value JSRemoveDialog(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, &argv, &thisVar, &data);
    int32_t instanceId = Container::CurrentIdSafely();
    if (data) {
        int32_t* instanceIdPtr = reinterpret_cast<int32_t*>(data);
        instanceId = *instanceIdPtr;
    }
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (delegate) {
        delegate->RemoveCustomDialog(instanceId);
    }
    return nullptr;
}

void GetDialogOnWillDismiss(napi_env env, napi_value options, DialogProperties& dialogProps)
{
    napi_ref dismissRef = nullptr;
    if (Napi::GetFunctionProperty(env, options, "onWillDismiss", dismissRef)) {
        dialogProps.onWillDismiss = [env, dismissRef](const int32_t& info, const int32_t& instanceId) {
            if (!dismissRef) {
                return;
            }
            napi_handle_scope scope = nullptr;
            auto ret = napi_open_handle_scope(env, &scope);
            if ((ret != napi_ok) || (scope == nullptr)) {
                TAG_LOGE(AceLogTag::ACE_DIALOG,
                    "onWillDismiss of the dialog failed to open the scope of the handle.");
                return;
            }
            napi_value onWillDismissFunc = nullptr;
            napi_value reasonValue = nullptr;
            napi_value funcValue = nullptr;
            napi_value paramObj = nullptr;
            napi_create_object(env, &paramObj);

            int32_t* id = new int32_t(instanceId);
            auto createStatus = napi_create_function(env, "dismiss", strlen("dismiss"), JSRemoveDialog, id, &funcValue);
            if (createStatus != napi_ok || !funcValue) {
                TAG_LOGE(AceLogTag::ACE_DIALOG,
                    "onWillDismiss of the dialog failed to create dismiss function, status: %{public}d",
                    static_cast<int>(createStatus));
                delete id;
                napi_close_handle_scope(env, scope);
                return;
            }
            napi_set_named_property(env, paramObj, "dismiss", funcValue);
            napi_status status = napi_add_finalizer(
                env, funcValue, id,
                [](napi_env env, void* data, void* hint) {
                    int32_t* id = reinterpret_cast<int32_t*>(data);
                    CHECK_NULL_VOID(id);
                    delete id;
                },
                nullptr, nullptr);
            if (status != napi_ok) {
                delete id;
                TAG_LOGE(AceLogTag::ACE_DIALOG, "Fail to add the finalizer method for instanceId.");
                napi_close_handle_scope(env, scope);
                return;
            }
            napi_create_int32(env, info, &reasonValue);
            napi_set_named_property(env, paramObj, "reason", reasonValue);
            napi_get_reference_value(env, dismissRef, &onWillDismissFunc);
            if (onWillDismissFunc) {
                napi_call_function(env, nullptr, onWillDismissFunc, 1, &paramObj, nullptr);
            }
            napi_close_handle_scope(env, scope);
        };
    }
}

RefPtr<NG::ChainedTransitionEffect> GetTransitionEffect(napi_env env, napi_value transitionApi)
{
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, transitionApi, &valueType);
    if (valueType != napi_object) {
        return nullptr;
    }
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (delegate) {
        return delegate->GetTransitionEffect(transitionApi);
    }
    return nullptr;
}

void GetDialogOffset(napi_env env, napi_value options, DialogProperties& dialogProps)
{
    napi_value offsetApi = nullptr;
    napi_valuetype valueType = napi_undefined;
    napi_get_named_property(env, options, "offset", &offsetApi);
    napi_typeof(env, offsetApi, &valueType);
    if (valueType != napi_object) {
        return;
    }
    napi_value dxApi = nullptr;
    napi_value dyApi = nullptr;
    napi_get_named_property(env, offsetApi, "dx", &dxApi);
    napi_get_named_property(env, offsetApi, "dy", &dyApi);
    CalcDimension dx;
    CalcDimension dy;
    if (ParseNapiDimension(env, dx, dxApi, DimensionUnit::VP) &&
        ParseNapiDimension(env, dy, dyApi, DimensionUnit::VP)) {
        dialogProps.offset = DimensionOffset { dx, dy };
    }
}

void GetDialogMaskRect(napi_env env, napi_value options, DialogProperties& dialogProps)
{
    napi_value maskRectApi = nullptr;
    napi_valuetype valueType = napi_undefined;
    napi_get_named_property(env, options, "maskRect", &maskRectApi);
    napi_typeof(env, maskRectApi, &valueType);
    if (valueType != napi_object) {
        return;
    }
    napi_value xApi = nullptr;
    napi_value yApi = nullptr;
    napi_value widthApi = nullptr;
    napi_value heightApi = nullptr;
    napi_get_named_property(env, maskRectApi, "x", &xApi);
    napi_get_named_property(env, maskRectApi, "y", &yApi);
    napi_get_named_property(env, maskRectApi, "width", &widthApi);
    napi_get_named_property(env, maskRectApi, "height", &heightApi);
    CalcDimension x;
    CalcDimension y;
    CalcDimension width;
    CalcDimension height;
    ParseNapiDimension(env, x, xApi, DimensionUnit::VP);
    ParseNapiDimension(env, y, yApi, DimensionUnit::VP);
    ParseNapiDimension(env, width, widthApi, DimensionUnit::VP);
    ParseNapiDimension(env, height, heightApi, DimensionUnit::VP);
    DimensionOffset dimOffset(x, y);
    dialogProps.maskRect = DimensionRect { width, height, dimOffset };
}

void GetDialogBackgroundColor(napi_env env, napi_value options, DialogProperties& dialogProps)
{
    napi_value bgColorApi = nullptr;
    napi_valuetype valueType = napi_undefined;
    napi_get_named_property(env, options, "backgroundColor", &bgColorApi);
    napi_typeof(env, bgColorApi, &valueType);
    if (valueType == napi_undefined) {
        return;
    }
    Color bgColor;
    RefPtr<ResourceObject> resObj;
    if (ParseNapiColor(env, bgColorApi, bgColor, resObj)) {
        dialogProps.backgroundColor = bgColor;
        dialogProps.backgroundColorResObj = resObj;
    }
}

void GetDialogBackgroundBlurStyle(napi_env env, napi_value options, DialogProperties& dialogProps)
{
    napi_value blurStyleApi = nullptr;
    napi_valuetype valueType = napi_undefined;
    napi_get_named_property(env, options, "backgroundBlurStyle", &blurStyleApi);
    napi_typeof(env, blurStyleApi, &valueType);
    if (valueType == napi_number) {
        int32_t num = 0;
        napi_get_value_int32(env, blurStyleApi, &num);
        dialogProps.backgroundBlurStyle = num;
    }
}

void GetDialogBackgroundBlurStyleOptions(napi_env env, napi_value options, DialogProperties& dialogProps)
{
    napi_value blurStyleOptionApi = nullptr;
    napi_valuetype valueType = napi_undefined;
    napi_get_named_property(env, options, "backgroundBlurStyleOptions", &blurStyleOptionApi);
    napi_typeof(env, blurStyleOptionApi, &valueType);
    if (valueType != napi_object) {
        return;
    }
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (delegate) {
        BlurStyleOption styleOption;
        bool hasBlurStyleOptionInactiveColor = false;
        delegate->GetBackgroundBlurStyleOption(blurStyleOptionApi, styleOption, hasBlurStyleOptionInactiveColor);
        dialogProps.blurStyleOption = styleOption;
    }
}

void GetDialogBackgroundEffect(napi_env env, napi_value options, DialogProperties& dialogProps)
{
    napi_value effectOptionApi = nullptr;
    napi_valuetype valueType = napi_undefined;
    napi_get_named_property(env, options, "backgroundEffect", &effectOptionApi);
    napi_typeof(env, effectOptionApi, &valueType);
    if (valueType != napi_object) {
        return;
    }
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (delegate) {
        EffectOption effectOption;
        bool hasEffectOptionColor = false;
        bool hasEffectOptionInactiveColor = false;
        delegate->GetBackgroundEffect(
            effectOptionApi, effectOption, hasEffectOptionColor, hasEffectOptionInactiveColor);
        dialogProps.effectOption = effectOption;
    }
}

void GetDialogBorderWidth(napi_env env, napi_value options, DialogProperties& dialogProps)
{
    napi_value borderWidthApi = nullptr;
    napi_valuetype valueType = napi_undefined;
    napi_get_named_property(env, options, "borderWidth", &borderWidthApi);
    napi_typeof(env, borderWidthApi, &valueType);
    if (valueType != napi_number && valueType != napi_string && valueType != napi_object) {
        return;
    }
    CalcDimension borderWidth;
    if (ParseNapiDimensionNG(env, borderWidth, borderWidthApi, DimensionUnit::VP, true)) {
        dialogProps.borderWidth =
            NG::BorderWidthProperty({ borderWidth, borderWidth, borderWidth, borderWidth });
    } else if (valueType == napi_object) {
        NG::BorderWidthProperty borderWidthProps;
        napi_value leftApi = nullptr;
        napi_value rightApi = nullptr;
        napi_value topApi = nullptr;
        napi_value bottomApi = nullptr;
        napi_get_named_property(env, borderWidthApi, "left", &leftApi);
        napi_get_named_property(env, borderWidthApi, "right", &rightApi);
        napi_get_named_property(env, borderWidthApi, "top", &topApi);
        napi_get_named_property(env, borderWidthApi, "bottom", &bottomApi);
        CalcDimension leftDimen;
        CalcDimension rightDimen;
        CalcDimension topDimen;
        CalcDimension bottomDimen;
        if (ParseNapiDimensionNG(env, leftDimen, leftApi, DimensionUnit::VP, true)) {
            borderWidthProps.leftDimen = leftDimen;
        }
        if (ParseNapiDimensionNG(env, rightDimen, rightApi, DimensionUnit::VP, true)) {
            borderWidthProps.rightDimen = rightDimen;
        }
        if (ParseNapiDimensionNG(env, topDimen, topApi, DimensionUnit::VP, true)) {
            borderWidthProps.topDimen = topDimen;
        }
        if (ParseNapiDimensionNG(env, bottomDimen, bottomApi, DimensionUnit::VP, true)) {
            borderWidthProps.bottomDimen = bottomDimen;
        }
        borderWidthProps.multiValued = true;
        dialogProps.borderWidth = borderWidthProps;
    }
}

void GetDialogBorderColor(napi_env env, napi_value options, DialogProperties& dialogProps)
{
    napi_value borderColorApi = nullptr;
    napi_valuetype valueType = napi_undefined;
    napi_get_named_property(env, options, "borderColor", &borderColorApi);
    napi_typeof(env, borderColorApi, &valueType);
    if (valueType == napi_undefined) {
        return;
    }
    Color borderColor;
    if (ParseNapiColor(env, borderColorApi, borderColor)) {
        NG::BorderColorProperty borderColors;
        borderColors.SetColor(borderColor);
        dialogProps.borderColor = borderColors;
        return;
    }
    if (valueType == napi_object) {
        napi_value leftApi = nullptr;
        napi_value rightApi = nullptr;
        napi_value topApi = nullptr;
        napi_value bottomApi = nullptr;
        napi_get_named_property(env, borderColorApi, "left", &leftApi);
        napi_get_named_property(env, borderColorApi, "right", &rightApi);
        napi_get_named_property(env, borderColorApi, "top", &topApi);
        napi_get_named_property(env, borderColorApi, "bottom", &bottomApi);
        NG::BorderColorProperty borderColors;
        Color leftColor;
        Color rightColor;
        Color topColor;
        Color bottomColor;
        if (ParseNapiColor(env, leftApi, leftColor)) {
            borderColors.leftColor = leftColor;
        }
        if (ParseNapiColor(env, rightApi, rightColor)) {
            borderColors.rightColor = rightColor;
        }
        if (ParseNapiColor(env, topApi, topColor)) {
            borderColors.topColor = topColor;
        }
        if (ParseNapiColor(env, bottomApi, bottomColor)) {
            borderColors.bottomColor = bottomColor;
        }
        borderColors.multiValued = true;
        dialogProps.borderColor = borderColors;
    }
}

void GetDialogBorderStyle(napi_env env, napi_value options, DialogProperties& dialogProps)
{
    napi_value borderStyleApi = nullptr;
    napi_valuetype valueType = napi_undefined;
    napi_get_named_property(env, options, "borderStyle", &borderStyleApi);
    napi_typeof(env, borderStyleApi, &valueType);
    if (valueType == napi_undefined) {
        return;
    }
    std::optional<BorderStyle> style;
    if (ParseStyle(env, borderStyleApi, style)) {
        if (style.has_value()) {
            NG::BorderStyleProperty borderStyles;
            borderStyles.SetBorderStyle(style.value());
            dialogProps.borderStyle = borderStyles;
        }
        return;
    }
    if (valueType == napi_object) {
        napi_value leftApi = nullptr;
        napi_value rightApi = nullptr;
        napi_value topApi = nullptr;
        napi_value bottomApi = nullptr;
        napi_get_named_property(env, borderStyleApi, "left", &leftApi);
        napi_get_named_property(env, borderStyleApi, "right", &rightApi);
        napi_get_named_property(env, borderStyleApi, "top", &topApi);
        napi_get_named_property(env, borderStyleApi, "bottom", &bottomApi);
        NG::BorderStyleProperty borderStyles;
        std::optional<BorderStyle> leftStyle;
        std::optional<BorderStyle> rightStyle;
        std::optional<BorderStyle> topStyle;
        std::optional<BorderStyle> bottomStyle;
        if (ParseStyle(env, leftApi, leftStyle) && leftStyle.has_value()) {
            borderStyles.styleLeft = leftStyle.value();
        }
        if (ParseStyle(env, rightApi, rightStyle) && rightStyle.has_value()) {
            borderStyles.styleRight = rightStyle.value();
        }
        if (ParseStyle(env, topApi, topStyle) && topStyle.has_value()) {
            borderStyles.styleTop = topStyle.value();
        }
        if (ParseStyle(env, bottomApi, bottomStyle) && bottomStyle.has_value()) {
            borderStyles.styleBottom = bottomStyle.value();
        }
        borderStyles.multiValued = true;
        dialogProps.borderStyle = borderStyles;
    }
}

void GetDialogBorderRadius(napi_env env, napi_value options, DialogProperties& dialogProps)
{
    napi_value borderRadiusApi = nullptr;
    napi_valuetype valueType = napi_undefined;
    napi_get_named_property(env, options, "borderRadius", &borderRadiusApi);
    napi_typeof(env, borderRadiusApi, &valueType);
    if (valueType != napi_number && valueType != napi_object && valueType != napi_string) {
        return;
    }
    CalcDimension borderRadius;
    if (ParseNapiDimensionNG(env, borderRadius, borderRadiusApi, DimensionUnit::VP, true)) {
        dialogProps.borderRadius = NG::BorderRadiusProperty(borderRadius);
    } else if (valueType == napi_object) {
        NG::BorderRadiusProperty radiusProps;
        napi_value topLeft = nullptr;
        napi_value topRight = nullptr;
        napi_value bottomLeft = nullptr;
        napi_value bottomRight = nullptr;
        napi_get_named_property(env, borderRadiusApi, "topLeft", &topLeft);
        napi_get_named_property(env, borderRadiusApi, "topRight", &topRight);
        napi_get_named_property(env, borderRadiusApi, "bottomLeft", &bottomLeft);
        napi_get_named_property(env, borderRadiusApi, "bottomRight", &bottomRight);
        CalcDimension radiusTopLeft;
        CalcDimension radiusTopRight;
        CalcDimension radiusBottomLeft;
        CalcDimension radiusBottomRight;
        if (ParseNapiDimensionNG(env, radiusTopLeft, topLeft, DimensionUnit::VP, true)) {
            radiusProps.radiusTopLeft = radiusTopLeft;
        }
        if (ParseNapiDimensionNG(env, radiusTopRight, topRight, DimensionUnit::VP, true)) {
            radiusProps.radiusTopRight = radiusTopRight;
        }
        if (ParseNapiDimensionNG(env, radiusBottomLeft, bottomLeft, DimensionUnit::VP, true)) {
            radiusProps.radiusBottomLeft = radiusBottomLeft;
        }
        if (ParseNapiDimensionNG(env, radiusBottomRight, bottomRight, DimensionUnit::VP, true)) {
            radiusProps.radiusBottomRight = radiusBottomRight;
        }
        radiusProps.multiValued = true;
        dialogProps.borderRadius = radiusProps;
    }
}

void GetDialogShadow(napi_env env, napi_value options, DialogProperties& dialogProps)
{
    napi_value shadowApi = nullptr;
    napi_valuetype valueType = napi_undefined;
    napi_get_named_property(env, options, "shadow", &shadowApi);
    napi_typeof(env, shadowApi, &valueType);
    if (valueType == napi_undefined) {
        return;
    }
    if (valueType == napi_number) {
        int32_t shadowStyleNum = 0;
        napi_get_value_int32(env, shadowApi, &shadowStyleNum);
        auto shadowStyle = static_cast<ShadowStyle>(shadowStyleNum);
        Shadow shadow;
        auto pipeline = NG::PipelineContext::GetCurrentContext();
        if (pipeline) {
            auto shadowTheme = pipeline->GetTheme<ShadowTheme>();
            if (shadowTheme) {
                auto colorMode = pipeline->GetColorMode();
                shadow = shadowTheme->GetShadow(shadowStyle, colorMode);
            }
        }
        dialogProps.shadow = shadow;
        return;
    }
    if (valueType == napi_object) {
        Shadow shadowProps;
        napi_value radiusApi = nullptr;
        napi_value colorApi = nullptr;
        napi_value typeApi = nullptr;
        napi_value fillApi = nullptr;
        napi_get_named_property(env, shadowApi, "radius", &radiusApi);
        napi_get_named_property(env, shadowApi, "color", &colorApi);
        napi_get_named_property(env, shadowApi, "type", &typeApi);
        napi_get_named_property(env, shadowApi, "fill", &fillApi);
        napi_valuetype radiusType = napi_undefined;
        napi_typeof(env, radiusApi, &radiusType);
        if (radiusType == napi_number) {
            double radiusValue = 0.0;
            napi_get_value_double(env, radiusApi, &radiusValue);
            shadowProps.SetBlurRadius(radiusValue);
        }
        Color color;
        ShadowColorStrategy shadowColorStrategy;
        if (ParseShadowColorStrategy(env, colorApi, shadowColorStrategy)) {
            shadowProps.SetShadowColorStrategy(shadowColorStrategy);
        } else if (ParseNapiColor(env, colorApi, color)) {
            shadowProps.SetColor(color);
        }
        napi_valuetype typeType = napi_undefined;
        napi_typeof(env, typeApi, &typeType);
        if (typeType == napi_number) {
            int32_t shadowType = static_cast<int32_t>(ShadowType::COLOR);
            napi_get_value_int32(env, typeApi, &shadowType);
            if (shadowType != static_cast<int32_t>(ShadowType::BLUR)) {
                shadowType = static_cast<int32_t>(ShadowType::COLOR);
            }
            shadowProps.SetShadowType(static_cast<ShadowType>(shadowType));
        }
        napi_valuetype fillType = napi_undefined;
        napi_typeof(env, fillApi, &fillType);
        if (fillType == napi_boolean) {
            bool isFilled = false;
            napi_get_value_bool(env, fillApi, &isFilled);
            shadowProps.SetIsFilled(isFilled);
        }
        napi_value offsetXApi = nullptr;
        napi_value offsetYApi = nullptr;
        napi_get_named_property(env, shadowApi, "offsetX", &offsetXApi);
        napi_get_named_property(env, shadowApi, "offsetY", &offsetYApi);
        CalcDimension offsetX;
        CalcDimension offsetY;
        if (ParseNapiDimension(env, offsetX, offsetXApi, DimensionUnit::VP)) {
            shadowProps.SetOffsetX(offsetX.Value());
        }
        if (ParseNapiDimension(env, offsetY, offsetYApi, DimensionUnit::VP)) {
            shadowProps.SetOffsetY(offsetY.Value());
        }
        dialogProps.shadow = shadowProps;
    }
}

void GetDialogWidthAndHeight(napi_env env, napi_value options, DialogProperties& dialogProps)
{
    napi_value widthApi = nullptr;
    napi_valuetype widthType = napi_undefined;
    napi_get_named_property(env, options, "width", &widthApi);
    napi_typeof(env, widthApi, &widthType);
    if (widthType == napi_number || widthType == napi_string || widthType == napi_object) {
        CalcDimension width;
        if (ParseNapiDimensionNG(env, width, widthApi, DimensionUnit::VP, true)) {
            dialogProps.width = width;
        }
    }

    napi_value heightApi = nullptr;
    napi_valuetype heightType = napi_undefined;
    napi_get_named_property(env, options, "height", &heightApi);
    napi_typeof(env, heightApi, &heightType);
    if (heightType == napi_number || heightType == napi_string || heightType == napi_object) {
        CalcDimension height;
        if (ParseNapiDimensionNG(env, height, heightApi, DimensionUnit::VP, true)) {
            dialogProps.height = height;
        }
    }
}

void GetDialogMaskColor(napi_env env, napi_value options, DialogProperties& dialogProps)
{
    napi_value maskColorApi = nullptr;
    napi_valuetype valueType = napi_undefined;
    napi_get_named_property(env, options, "maskColor", &maskColorApi);
    napi_typeof(env, maskColorApi, &valueType);
    if (valueType == napi_undefined) {
        return;
    }
    Color maskColor;
    RefPtr<ResourceObject> resObj;
    if (ParseNapiColor(env, maskColorApi, maskColor, resObj)) {
        dialogProps.maskColor = maskColor;
        dialogProps.maskColorResObj = resObj;
    }
}
} // namespace

void RejectPromise(napi_env env, napi_deferred deferred, const std::string& message, int32_t errorCode)
{
    napi_value code = nullptr;
    std::string strCode = std::to_string(errorCode);
    napi_create_string_utf8(env, strCode.c_str(), strCode.length(), &code);
    napi_value msg = nullptr;
    std::string strMsg = Napi::ErrorToMessage(errorCode) + message;
    napi_create_string_utf8(env, strMsg.c_str(), strMsg.length(), &msg);
    napi_value error = nullptr;
    napi_create_error(env, code, msg, &error);
    napi_reject_deferred(env, deferred, error);
}

napi_value CreateDialogPromise(napi_env env, std::shared_ptr<DialogAsyncContext>& context)
{
    napi_value result = nullptr;
    napi_create_promise(env, &context->deferred, &result);
    return result;
}

std::function<void(int32_t, int32_t)> CreatePresentFinishCallback(
    std::shared_ptr<DialogAsyncContext> context)
{
    return [context](int32_t callbackType, int32_t successType) mutable {
        auto container = AceEngine::Get().GetContainer(context->instanceId);
        CHECK_NULL_VOID(container);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [context, callbackType, successType]() {
                if (context == nullptr) {
                    return;
                }
                napi_handle_scope scope = nullptr;
                napi_open_handle_scope(context->env, &scope);
                if (context->deferred) {
                    if (callbackType == CALLBACK_TYPE_SUCCESS) {
                        ResolvePromise(context->env, context->deferred, successType);
                    } else if (callbackType == CALLBACK_TYPE_MOUNT_ERROR) {
                        RejectPromise(context->env, context->deferred, "Dialog mount failed.", successType);
                    } else {
                        ResolvePromise(context->env, context->deferred, -1);
                    }
                    context->deferred = nullptr;
                }
                napi_close_handle_scope(context->env, scope);
            },
            TaskExecutor::TaskType::JS, "ArkUIDialogPresentCallback");
        context = nullptr;
    };
}

std::function<void(int32_t errorCode, int32_t dialogId)> CreatePresentCustomFinishCallback(
    std::shared_ptr<DialogAsyncContext> context)
{
    return [context](int32_t errorCode, int32_t dialogId) mutable {
        auto container = AceEngine::Get().GetContainer(context->instanceId);
        CHECK_NULL_VOID(container);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [context, errorCode, dialogId]() {
                if (context == nullptr) {
                    return;
                }
                napi_handle_scope scope = nullptr;
                napi_open_handle_scope(context->env, &scope);
                if (context->deferred) {
                    if (errorCode == ERROR_CODE_NO_ERROR) {
                        ResolvePromiseWithId(context->env, context->deferred, dialogId);
                    } else {
                        RejectPromise(context->env, context->deferred, "Dialog open failed.", errorCode);
                    }
                    context->deferred = nullptr;
                }
                napi_close_handle_scope(context->env, scope);
            },
            TaskExecutor::TaskType::JS, "ArkUIDialogPresentCustomCallback");
        context = nullptr;
    };
}

std::function<void(int32_t)> CreateUpdateFinishCallback(
    std::shared_ptr<DialogAsyncContext> context)
{
    return [context](int32_t errorCode) mutable {
        auto container = AceEngine::Get().GetContainer(context->instanceId);
        CHECK_NULL_VOID(container);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [context, errorCode]() {
                if (context == nullptr) {
                    return;
                }
                napi_handle_scope scope = nullptr;
                napi_open_handle_scope(context->env, &scope);
                if (context->deferred) {
                    if (errorCode == 0) {
                        ResolvePromiseVoid(context->env, context->deferred);
                    } else {
                        RejectPromise(context->env, context->deferred, "Update dialog failed.", errorCode);
                    }
                    context->deferred = nullptr;
                }
                napi_close_handle_scope(context->env, scope);
            },
            TaskExecutor::TaskType::JS, "ArkUIDialogUpdateCallback");
        context = nullptr;
    };
}

std::function<void(int32_t)> CreateDismissFinishCallback(
    std::shared_ptr<DialogAsyncContext> context)
{
    return [context](int32_t errorCode) mutable {
        auto container = AceEngine::Get().GetContainer(context->instanceId);
        CHECK_NULL_VOID(container);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [context, errorCode]() {
                if (context == nullptr) {
                    return;
                }
                napi_handle_scope scope = nullptr;
                napi_open_handle_scope(context->env, &scope);
                if (context->deferred) {
                    if (errorCode == 0) {
                        ResolvePromiseVoid(context->env, context->deferred);
                    } else {
                        RejectPromise(context->env, context->deferred, "Dismiss dialog failed.", errorCode);
                    }
                    context->deferred = nullptr;
                }
                napi_close_handle_scope(context->env, scope);
            },
            TaskExecutor::TaskType::JS, "ArkUIDialogDismissCallback");
        context = nullptr;
    };
}

void GetCustomBuilder(napi_env env, napi_value content, DialogProperties& dialogProps)
{
    napi_valuetype contentType = napi_undefined;
    napi_typeof(env, content, &contentType);
    if (contentType != napi_function) {
        return;
    }

    napi_ref builderRef = nullptr;
    napi_create_reference(env, content, 1, &builderRef);
    dialogProps.customBuilder = [env, builderRef]() {
        if (!builderRef) {
            return;
        }
        napi_handle_scope scope = nullptr;
        auto status = napi_open_handle_scope(env, &scope);
        if ((status != napi_ok) || (scope == nullptr)) {
            TAG_LOGE(AceLogTag::ACE_DIALOG,
                "customBuilder of the dialog failed to open the scope of the handle.");
            napi_delete_reference(env, builderRef);
            return;
        }
        napi_value builderFunc = nullptr;
        napi_get_reference_value(env, builderRef, &builderFunc);
        if (builderFunc) {
            napi_call_function(env, nullptr, builderFunc, 0, nullptr, nullptr);
        }
        napi_delete_reference(env, builderRef);
        napi_close_handle_scope(env, scope);
    };
    dialogProps.customBuilderWithId = [env, builderRef](const int32_t dialogId) {
        if (!builderRef) {
            return;
        }
        napi_handle_scope scope = nullptr;
        auto status = napi_open_handle_scope(env, &scope);
        if ((status != napi_ok) || (scope == nullptr)) {
            TAG_LOGE(AceLogTag::ACE_DIALOG,
                "customBuilderWithId of the dialog failed to open the scope of the handle.");
            napi_delete_reference(env, builderRef);
            return;
        }
        napi_value builderFunc = nullptr;
        napi_get_reference_value(env, builderRef, &builderFunc);
        if (builderFunc) {
            napi_value dialogIdArg = nullptr;
            napi_create_int32(env, dialogId, &dialogIdArg);
            napi_call_function(env, nullptr, builderFunc, 1, &dialogIdArg, nullptr);
        }
        napi_delete_reference(env, builderRef);
        napi_close_handle_scope(env, scope);
    };
}

bool GetFrameNodePtr(napi_env env, napi_value content, WeakPtr<NG::UINode>& nodeWk)
{
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, content, &valueType);
    if (valueType != napi_object) {
        return false;
    }

    napi_value frameNodePtr = nullptr;
    auto result = napi_get_named_property(env, content, "nodePtr_", &frameNodePtr);
    if (result != napi_ok) {
        return false;
    }

    void* nativePtr = nullptr;
    result = napi_get_value_external(env, frameNodePtr, &nativePtr);
    if (result != napi_ok || nativePtr == nullptr) {
        return false;
    }

    auto* uiNodePtr = reinterpret_cast<NG::UINode*>(nativePtr);
    nodeWk = AceType::WeakClaim(uiNodePtr);
    return true;
}

bool GetDialogOptions(napi_env env, napi_value options, DialogProperties& dialogProps)
{
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, options, &valueType);
    if (valueType != napi_object) {
        return false;
    }

    Napi::GetStringProperty(env, options, "title", dialogProps.title);
    Napi::GetStringProperty(env, options, "subtitle", dialogProps.subtitle);
    GetDialogMessage(env, options, dialogProps);
    GetDialogButtons(env, options, dialogProps);
    GetDialogSheets(env, options, dialogProps);
    GetDialogButtonDirection(env, options, dialogProps);
    Napi::GetInt32Property(env, options, "gridCount", dialogProps.gridCount);

    dialogProps.type = dialogProps.sheetsInfo.empty() ? DialogType::ALERT_DIALOG : DialogType::ACTION_SHEET;
    GetDialogBaseOptions(env, options, dialogProps);

    return true;
}

bool GetDialogBaseOptions(napi_env env, napi_value options, DialogProperties& dialogProps)
{
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, options, &valueType);
    if (valueType != napi_object) {
        return false;
    }

    Napi::GetBoolProperty(env, options, "autoCancel", dialogProps.autoCancel);
    Napi::GetBoolProperty(env, options, "isModal", dialogProps.isModal);
    Napi::GetBoolProperty(env, options, "showInSubWindow", dialogProps.isShowInSubWindow);
    Napi::GetBoolProperty(env, options, "focusable", dialogProps.focusable);
    GetDialogAlignment(env, options, dialogProps);

    // Visual properties
    GetDialogWidthAndHeight(env, options, dialogProps);
    GetDialogBackgroundColor(env, options, dialogProps);
    GetDialogBackgroundBlurStyle(env, options, dialogProps);
    GetDialogBackgroundBlurStyleOptions(env, options, dialogProps);
    GetDialogBackgroundEffect(env, options, dialogProps);
    GetDialogBorderRadius(env, options, dialogProps);
    GetDialogBorderWidth(env, options, dialogProps);
    GetDialogBorderColor(env, options, dialogProps);
    GetDialogBorderStyle(env, options, dialogProps);
    GetDialogShadow(env, options, dialogProps);

    // Position and mask
    GetDialogOffset(env, options, dialogProps);
    GetDialogMaskRect(env, options, dialogProps);
    GetDialogMaskColor(env, options, dialogProps);

    // Display mode
    {
        napi_value displayModeApi = nullptr;
        napi_valuetype dmType = napi_undefined;
        napi_get_named_property(env, options, "displayModeInSubWindow", &displayModeApi);
        napi_typeof(env, displayModeApi, &dmType);
        if (dmType == napi_number) {
            int32_t displayMode = 0;
            napi_get_value_int32(env, displayModeApi, &displayMode);
            if (displayMode >= 0 && displayMode < static_cast<int32_t>(DIALOG_DISPLAY_MODE_IN_SUBWINDOW.size())) {
                dialogProps.displayModeInSubWindow = DIALOG_DISPLAY_MODE_IN_SUBWINDOW[displayMode];
            }
        }
    }

    // Transition effects
    {
        napi_value dialogTransitionApi = nullptr;
        napi_get_named_property(env, options, "dialogTransition", &dialogTransitionApi);
        dialogProps.dialogTransitionEffect = GetTransitionEffect(env, dialogTransitionApi);

        napi_value maskTransitionApi = nullptr;
        napi_get_named_property(env, options, "maskTransition", &maskTransitionApi);
        dialogProps.maskTransitionEffect = GetTransitionEffect(env, maskTransitionApi);
    }

    // Keyboard
    {
        napi_value keyboardAvoidModeApi = nullptr;
        napi_valuetype kamType = napi_undefined;
        napi_get_named_property(env, options, "keyboardAvoidMode", &keyboardAvoidModeApi);
        napi_typeof(env, keyboardAvoidModeApi, &kamType);
        if (kamType == napi_number) {
            int32_t mode = 0;
            napi_get_value_int32(env, keyboardAvoidModeApi, &mode);
            if (mode >= 0 && mode < static_cast<int32_t>(KEYBOARD_AVOID_MODE.size())) {
                dialogProps.keyboardAvoidMode = KEYBOARD_AVOID_MODE[mode];
            }
        }
    }
    {
        napi_value keyboardAvoidDistanceApi = nullptr;
        napi_valuetype kadType = napi_undefined;
        napi_get_named_property(env, options, "keyboardAvoidDistance", &keyboardAvoidDistanceApi);
        napi_typeof(env, keyboardAvoidDistanceApi, &kadType);
        if (kadType == napi_object) {
            napi_value avoidDistance = nullptr;
            napi_value avoidDistanceUnit = nullptr;
            napi_get_named_property(env, keyboardAvoidDistanceApi, "value", &avoidDistance);
            napi_get_named_property(env, keyboardAvoidDistanceApi, "unit", &avoidDistanceUnit);
            napi_valuetype distValueType = napi_undefined;
            napi_valuetype unitValueType = napi_undefined;
            napi_typeof(env, avoidDistance, &distValueType);
            napi_typeof(env, avoidDistanceUnit, &unitValueType);
            if (distValueType == napi_number && unitValueType == napi_number) {
                double avoidDistanceValue = 0.0;
                int32_t avoidDistanceUnitValue = 0;
                napi_get_value_double(env, avoidDistance, &avoidDistanceValue);
                napi_get_value_int32(env, avoidDistanceUnit, &avoidDistanceUnitValue);
                auto unit = static_cast<DimensionUnit>(avoidDistanceUnitValue);
                if (avoidDistanceValue >= 0.0 && unit >= DimensionUnit::PX &&
                    unit <= DimensionUnit::CALC && unit != DimensionUnit::PERCENT) {
                    dialogProps.keyboardAvoidDistance = Dimension(avoidDistanceValue, unit);
                }
            }
        }
    }

    // Hover mode
    {
        napi_value enableHoverModeApi = nullptr;
        napi_valuetype ehType = napi_undefined;
        napi_get_named_property(env, options, "enableHoverMode", &enableHoverModeApi);
        napi_typeof(env, enableHoverModeApi, &ehType);
        if (ehType == napi_boolean) {
            bool enableHoverMode = false;
            napi_get_value_bool(env, enableHoverModeApi, &enableHoverMode);
            dialogProps.enableHoverMode = enableHoverMode;
        }
    }
    {
        napi_value hoverModeAreaApi = nullptr;
        napi_valuetype hmaType = napi_undefined;
        napi_get_named_property(env, options, "hoverModeArea", &hoverModeAreaApi);
        napi_typeof(env, hoverModeAreaApi, &hmaType);
        if (hmaType == napi_number) {
            int32_t hoverModeArea = 0;
            napi_get_value_int32(env, hoverModeAreaApi, &hoverModeArea);
            if (hoverModeArea >= 0 && hoverModeArea < static_cast<int32_t>(HOVER_MODE_AREA_TYPE.size())) {
                dialogProps.hoverModeArea = HOVER_MODE_AREA_TYPE[hoverModeArea];
            }
        }
    }

    // Level mode
    {
        napi_value levelModeApi = nullptr;
        napi_valuetype lmType = napi_undefined;
        napi_get_named_property(env, options, "levelMode", &levelModeApi);
        napi_typeof(env, levelModeApi, &lmType);
        if (lmType == napi_number) {
            int32_t mode = 0;
            napi_get_value_int32(env, levelModeApi, &mode);
            if (!dialogProps.isShowInSubWindow && mode >= 0 && mode < static_cast<int32_t>(DIALOG_LEVEL_MODE.size())) {
                dialogProps.dialogLevelMode = DIALOG_LEVEL_MODE[mode];
            }
        }
    }
    Napi::GetInt32Property(env, options, "levelUniqueId", dialogProps.dialogLevelUniqueId);
    {
        napi_value immersiveModeApi = nullptr;
        napi_valuetype imType = napi_undefined;
        napi_get_named_property(env, options, "immersiveMode", &immersiveModeApi);
        napi_typeof(env, immersiveModeApi, &imType);
        if (imType == napi_number) {
            int32_t immersiveMode = 0;
            napi_get_value_int32(env, immersiveModeApi, &immersiveMode);
            if (immersiveMode >= 0 && immersiveMode < static_cast<int32_t>(DIALOG_IMMERSIVE_MODE.size())) {
                dialogProps.dialogImmersiveMode = DIALOG_IMMERSIVE_MODE[immersiveMode];
            }
        }
    }
    {
        napi_value levelOrderApi = nullptr;
        napi_valuetype loType = napi_undefined;
        napi_get_named_property(env, options, "levelOrder", &levelOrderApi);
        napi_typeof(env, levelOrderApi, &loType);
        if (loType == napi_number) {
            double levelOrder = 0.0;
            napi_get_value_double(env, levelOrderApi, &levelOrder);
            dialogProps.levelOrder = levelOrder;
        }
    }

    // System material
    {
        napi_value systemMaterialApi = nullptr;
        napi_valuetype smType = napi_undefined;
        napi_get_named_property(env, options, "systemMaterial", &systemMaterialApi);
        napi_typeof(env, systemMaterialApi, &smType);
        if (smType == napi_object) {
            UiMaterial* material = nullptr;
            napi_unwrap(env, systemMaterialApi, reinterpret_cast<void**>(&material));
            if (material) {
                dialogProps.systemMaterial = material->Copy();
            }
        }
    }

    // Distortion mode (systemapi)
    {
        napi_value distortionModeApi = nullptr;
        napi_valuetype dmType = napi_undefined;
        napi_get_named_property(env, options, "distortionMode", &distortionModeApi);
        napi_typeof(env, distortionModeApi, &dmType);
        if (dmType == napi_number) {
            int32_t distortionMode = 0;
            napi_get_value_int32(env, distortionModeApi, &distortionMode);
            dialogProps.distortionMode = static_cast<DistortionMode>(distortionMode);
        }
    }

    // Edge light mode (systemapi)
    {
        napi_value edgeLightModeApi = nullptr;
        napi_valuetype elmType = napi_undefined;
        napi_get_named_property(env, options, "edgeLightMode", &edgeLightModeApi);
        napi_typeof(env, edgeLightModeApi, &elmType);
        if (elmType == napi_number) {
            int32_t edgeLightMode = 0;
            napi_get_value_int32(env, edgeLightModeApi, &edgeLightMode);
            dialogProps.edgeLightMode = static_cast<EdgeLightMode>(edgeLightMode);
        }
    }

    // Life cycle callbacks
    Napi::GetVoidCallbackProperty(env, options, "onWillAppear", dialogProps.onWillAppear);
    Napi::GetVoidCallbackProperty(env, options, "onDidAppear", dialogProps.onDidAppear);
    Napi::GetVoidCallbackProperty(env, options, "onWillDisappear", dialogProps.onWillDisappear);
    Napi::GetVoidCallbackProperty(env, options, "onDidDisappear", dialogProps.onDidDisappear);
    GetDialogOnWillDismiss(env, options, dialogProps);

    return true;
}

bool GetCustomDialogOptions(napi_env env, napi_value options, DialogProperties& dialogProps)
{
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, options, &valueType);
    if (valueType != napi_object) {
        return false;
    }

    Napi::GetBoolProperty(env, options, "customStyle", dialogProps.customStyle);
    GetDialogBaseOptions(env, options, dialogProps);
    return true;
}

} // namespace OHOS::Ace
