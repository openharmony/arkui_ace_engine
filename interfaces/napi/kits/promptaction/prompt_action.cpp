/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "prompt_action.h"
#include "prompt_controller.h"

#include "interfaces/napi/kits/utils/napi_utils.h"
#include "base/subwindow/subwindow_manager.h"
#include "bridge/common/utils/engine_helper.h"
#include "core/common/ace_engine.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components/toast/toast_theme.h"
#include "core/components/button/button_theme.h"
#include "core/components_ng/pattern/overlay/level_order.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::Napi {
namespace {
const int32_t SHOW_DIALOG_BUTTON_NUM_MAX = -1;
const int32_t SHOW_ACTION_MENU_BUTTON_NUM_MAX = 6;
const int32_t CUSTOM_DIALOG_PARAM_NUM = 2;
const int32_t BG_BLUR_STYLE_MAX_INDEX = 13;
const int32_t PROMPTACTION_VALID_PRIMARY_BUTTON_NUM = 1;
const int32_t OPEN_CUSTOM_DIALOG_WITH_CONTROLLER_PARAM_TOTAL = 3;
const int32_t OPEN_CUSTOM_DIALOG_WITH_CONTROLLER_PARAM_MAND_COUNT = 2;
const int32_t OPEN_CUSTOM_DIALOG_WITH_CONTROLLER_PARAM_INDEX_CONTROLLER = 1;
const int32_t OPEN_CUSTOM_DIALOG_WITH_CONTROLLER_PARAM_INDEX_OPTIONS = 2;
const int32_t PRESENT_CUSTOM_DIALOG_PARAM_TOTAL = 3;
const int32_t PRESENT_CUSTOM_DIALOG_PARAM_MAND_COUNT = 1;
const int32_t PRESENT_CUSTOM_DIALOG_PARAM_INDEX_CONTROLLER = 1;
const int32_t PRESENT_CUSTOM_DIALOG_PARAM_INDEX_OPTIONS = 2;
constexpr char DEFAULT_FONT_COLOR_STRING_VALUE[] = "#ff007dff";
constexpr float DEFAULT_AVOID_DISTANCE = 16.0f;
const std::vector<DialogAlignment> DIALOG_ALIGNMENT = { DialogAlignment::TOP, DialogAlignment::CENTER,
    DialogAlignment::BOTTOM, DialogAlignment::DEFAULT, DialogAlignment::TOP_START, DialogAlignment::TOP_END,
    DialogAlignment::CENTER_START, DialogAlignment::CENTER_END, DialogAlignment::BOTTOM_START,
    DialogAlignment::BOTTOM_END };
const std::vector<KeyboardAvoidMode> KEYBOARD_AVOID_MODE = { KeyboardAvoidMode::DEFAULT, KeyboardAvoidMode::NONE };
const std::vector<HoverModeAreaType> HOVER_MODE_AREA_TYPE = { HoverModeAreaType::TOP_SCREEN,
    HoverModeAreaType::BOTTOM_SCREEN };
const std::vector<LevelMode> DIALOG_LEVEL_MODE = { LevelMode::OVERLAY, LevelMode::EMBEDDED };
const std::vector<ImmersiveMode> DIALOG_IMMERSIVE_MODE = { ImmersiveMode::DEFAULT, ImmersiveMode::EXTEND};

#ifdef OHOS_STANDARD_SYSTEM
bool ContainerIsService()
{
    auto containerId = Container::CurrentIdSafely();
    // Get active container when current instanceid is less than 0
    if (containerId < 0) {
        auto container = Container::GetActive();
        if (container) {
            containerId = container->GetInstanceId();
        }
    }
    // for pa service
    return containerId >= MIN_PA_SERVICE_ID || containerId < 0;
}

bool ContainerIsSceneBoard()
{
    auto container = Container::CurrentSafely();
    if (!container) {
        container = Container::GetActive();
    }

    return container && container->IsSceneBoardWindow();
}
#endif
} // namespace

bool GetToastMessage(napi_env env, napi_value messageNApi, std::string& messageString)
{
    size_t ret = 0;
    ResourceInfo recv;
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, messageNApi, &valueType);
    if (valueType == napi_string) {
        size_t messageLen = GetParamLen(env, messageNApi) + 1;
        std::unique_ptr<char[]> message = std::make_unique<char[]>(messageLen);
        napi_get_value_string_utf8(env, messageNApi, message.get(), messageLen, &ret);
        messageString = message.get();
    } else if (valueType == napi_object) {
        if (!ParseResourceParam(env, messageNApi, recv)) {
            NapiThrow(env, "Can not parse resource info from input params.", ERROR_CODE_INTERNAL_ERROR);
            return false;
        }
        if (!ParseString(recv, messageString)) {
            NapiThrow(env, "Can not get message from resource manager.", ERROR_CODE_INTERNAL_ERROR);
            return false;
        }
        if (messageString.size() == 0) {
            TAG_LOGE(AceLogTag::ACE_DIALOG, "Toast message is empty");
        }
    } else {
        NapiThrow(env, "The type of message is incorrect.", ERROR_CODE_PARAM_INVALID);
        return false;
    }
    return true;
}

bool GetToastDuration(napi_env env, napi_value durationNApi, int32_t& duration)
{
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, durationNApi, &valueType);
    ResourceInfo recv;
    std::string durationStr;
    if (valueType == napi_number) {
        napi_get_value_int32(env, durationNApi, &duration);
    } else if (valueType == napi_object) {
        recv = {};
        if (!ParseResourceParam(env, durationNApi, recv)) {
            NapiThrow(env, "Can not parse resource info from input params.", ERROR_CODE_INTERNAL_ERROR);
            return false;
        }
        if (!ParseString(recv, durationStr)) {
            NapiThrow(env, "Can not get message from resource manager.", ERROR_CODE_INTERNAL_ERROR);
            return false;
        }
        duration = StringUtils::StringToInt(durationStr);
    }
    return true;
}

bool GetToastBottom(napi_env env, napi_value bottomNApi, std::string& bottomString)
{
    size_t ret = 0;
    ResourceInfo recv;
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, bottomNApi, &valueType);
    if (valueType == napi_string) {
        size_t bottomLen = GetParamLen(env, bottomNApi) + 1;
        std::unique_ptr<char[]> bottom = std::make_unique<char[]>(bottomLen);
        napi_get_value_string_utf8(env, bottomNApi, bottom.get(), bottomLen, &ret);
        bottomString = bottom.get();
    } else if (valueType == napi_number) {
        double bottom = 0.0;
        napi_get_value_double(env, bottomNApi, &bottom);
        bottomString = std::to_string(bottom);
    } else if (valueType == napi_object) {
        recv = {};
        if (!ParseResourceParam(env, bottomNApi, recv)) {
            NapiThrow(env, "Can not parse resource info from input params.", ERROR_CODE_INTERNAL_ERROR);
            return false;
        }
        if (!ParseString(recv, bottomString)) {
            NapiThrow(env, "Can not get message from resource manager.", ERROR_CODE_INTERNAL_ERROR);
            return false;
        }
    }
    return true;
}

bool GetToastShowMode(napi_env env, napi_value showModeNApi, NG::ToastShowMode& showMode)
{
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, showModeNApi, &valueType);
    if (valueType == napi_number) {
        int32_t num = -1;
        napi_get_value_int32(env, showModeNApi, &num);
        if (num >= 0 && num <= static_cast<int32_t>(NG::ToastShowMode::SYSTEM_TOP_MOST)) {
            showMode = static_cast<NG::ToastShowMode>(num);
        }
    }
    return true;
}

bool GetToastAlignment(napi_env env, napi_value alignmentApi, int32_t& alignment)
{
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, alignmentApi, &valueType);
    if (valueType == napi_number) {
        napi_get_value_int32(env, alignmentApi, &alignment);
    }
    return true;
}

bool GetToastOffset(napi_env env, napi_value offsetApi, std::optional<DimensionOffset>& offset)
{
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, offsetApi, &valueType);
    if (valueType == napi_object) {
        napi_value dxApi = nullptr;
        napi_value dyApi = nullptr;
        napi_get_named_property(env, offsetApi, "dx", &dxApi);
        napi_get_named_property(env, offsetApi, "dy", &dyApi);
        CalcDimension dx;
        CalcDimension dy;
        ParseNapiDimension(env, dx, dxApi, DimensionUnit::VP);
        ParseNapiDimension(env, dy, dyApi, DimensionUnit::VP);
        offset = DimensionOffset { dx, dy };
    }
    return true;
}

void GetToastBackgroundColor(napi_env env, napi_value backgroundColorNApi, std::optional<Color>& backgroundColor)
{
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, backgroundColorNApi, &valueType);
    Color color;
    backgroundColor = std::nullopt;
    if (ParseNapiColor(env, backgroundColorNApi, color)) {
        backgroundColor = color;
    }
}

void GetToastTextColor(napi_env env, napi_value textColorNApi, std::optional<Color>& textColor)
{
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, textColorNApi, &valueType);
    Color color;
    textColor = std::nullopt;
    if (ParseNapiColor(env, textColorNApi, color)) {
        textColor = color;
    }
}

void GetToastBackgroundBlurStyle(napi_env env,
    napi_value backgroundBlurStyleNApi, std::optional<int32_t>& backgroundBlurStyle)
{
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, backgroundBlurStyleNApi, &valueType);
    if (valueType == napi_number) {
        int32_t num;
        napi_get_value_int32(env, backgroundBlurStyleNApi, &num);
        if (num >= 0 && num < BG_BLUR_STYLE_MAX_INDEX) {
            backgroundBlurStyle = num;
        }
    }
}

bool GetShadowFromTheme(ShadowStyle shadowStyle, Shadow& shadow)
{
    if (shadowStyle == ShadowStyle::None) {
        return true;
    }
    auto container = Container::CurrentSafelyWithCheck();
    CHECK_NULL_RETURN(container, false);
    auto colorMode = container->GetColorMode();
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto shadowTheme = pipelineContext->GetTheme<ShadowTheme>();
    if (!shadowTheme) {
        return false;
    }
    shadow = shadowTheme->GetShadow(shadowStyle, colorMode);
    return true;
}

bool ParseResource(const ResourceInfo resource, CalcDimension& result)
{
    auto resourceWrapper = CreateResourceWrapper(resource);
    CHECK_NULL_RETURN(resourceWrapper, false);
    if (resource.type == static_cast<uint32_t>(ResourceType::STRING)) {
        auto value = resourceWrapper->GetString(resource.resId);
        return StringUtils::StringToCalcDimensionNG(value, result, false);
    }
    if (resource.type == static_cast<uint32_t>(ResourceType::INTEGER)) {
        auto value = std::to_string(resourceWrapper->GetInt(resource.resId));
        StringUtils::StringToDimensionWithUnitNG(value, result);
        return true;
    }
    if (resource.type == static_cast<uint32_t>(ResourceType::FLOAT)) {
        result = resourceWrapper->GetDimension(resource.resId);
        return true;
    }
    return false;
}

void GetToastObjectShadow(napi_env env, napi_value shadowNApi, Shadow& shadowProps)
{
    napi_value radiusApi = nullptr;
    napi_value colorApi = nullptr;
    napi_value typeApi = nullptr;
    napi_value fillApi = nullptr;
    napi_get_named_property(env, shadowNApi, "radius", &radiusApi);
    napi_get_named_property(env, shadowNApi, "color", &colorApi);
    napi_get_named_property(env, shadowNApi, "type", &typeApi);
    napi_get_named_property(env, shadowNApi, "fill", &fillApi);
    ResourceInfo recv;
    double radiusValue = 0.0;
    if (ParseResourceParam(env, radiusApi, recv)) {
        CalcDimension radius;
        if (ParseResource(recv, radius)) {
            radiusValue = LessNotEqual(radius.Value(), 0.0) ? 0.0 : radius.Value();
        }
    } else {
        napi_get_value_double(env, radiusApi, &radiusValue);
        if (LessNotEqual(radiusValue, 0.0)) {
            radiusValue = 0.0;
        }
    }
    shadowProps.SetBlurRadius(radiusValue);
    Color color;
    ShadowColorStrategy shadowColorStrategy;
    if (ParseShadowColorStrategy(env, colorApi, shadowColorStrategy)) {
        shadowProps.SetShadowColorStrategy(shadowColorStrategy);
    } else if (ParseNapiColor(env, colorApi, color)) {
        shadowProps.SetColor(color);
    }
    napi_valuetype valueType = GetValueType(env, typeApi);
    int32_t shadowType = static_cast<int32_t>(ShadowType::COLOR);
    if (valueType == napi_number) {
        napi_get_value_int32(env, typeApi, &shadowType);
    }
    if (shadowType != static_cast<int32_t>(ShadowType::BLUR)) {
        shadowType = static_cast<int32_t>(ShadowType::COLOR);
    }
    shadowType =
        std::clamp(shadowType, static_cast<int32_t>(ShadowType::COLOR), static_cast<int32_t>(ShadowType::BLUR));
    shadowProps.SetShadowType(static_cast<ShadowType>(shadowType));
    valueType = GetValueType(env, fillApi);
    bool isFilled = false;
    if (valueType == napi_boolean) {
        napi_get_value_bool(env, fillApi, &isFilled);
    }
    shadowProps.SetIsFilled(isFilled);
}

ShadowStyle GetToastDefaultShadowStyle()
{
    auto shadowStyle = ShadowStyle::OuterDefaultMD;
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, shadowStyle);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, shadowStyle);
    auto toastTheme = pipelineContext->GetTheme<ToastTheme>();
    CHECK_NULL_RETURN(toastTheme, shadowStyle);
    return toastTheme->GetToastShadowStyle();
}

void GetToastShadow(napi_env env, napi_value shadowNApi, std::optional<Shadow>& shadow, bool& isTypeStyleShadow)
{
    Shadow shadowProps;
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, shadowNApi, &valueType);
    if (valueType == napi_number) {
        int32_t num = 0;
        napi_get_value_int32(env, shadowNApi, &num);
        auto style = static_cast<ShadowStyle>(num);
        CHECK_EQUAL_VOID(GetShadowFromTheme(style, shadowProps), false);
    } else if (valueType == napi_object) {
        napi_value offsetXApi = nullptr;
        napi_value offsetYApi = nullptr;
        napi_get_named_property(env, shadowNApi, "offsetX", &offsetXApi);
        napi_get_named_property(env, shadowNApi, "offsetY", &offsetYApi);
        ResourceInfo recv;
        bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
        if (ParseResourceParam(env, offsetXApi, recv)) {
            CalcDimension offsetX;
            if (ParseResource(recv, offsetX)) {
                double xValue = isRtl ? offsetX.Value() * (-1) : offsetX.Value();
                shadowProps.SetOffsetX(xValue);
            }
        } else {
            CalcDimension offsetX;
            if (ParseNapiDimension(env, offsetX, offsetXApi, DimensionUnit::VP)) {
                double xValue = isRtl ? offsetX.Value() * (-1) : offsetX.Value();
                shadowProps.SetOffsetX(xValue);
            }
        }
        if (ParseResourceParam(env, offsetYApi, recv)) {
            CalcDimension offsetY;
            if (ParseResource(recv, offsetY)) {
                shadowProps.SetOffsetY(offsetY.Value());
            }
        } else {
            CalcDimension offsetY;
            if (ParseNapiDimension(env, offsetY, offsetYApi, DimensionUnit::VP)) {
                shadowProps.SetOffsetY(offsetY.Value());
            }
        }
        GetToastObjectShadow(env, shadowNApi, shadowProps);
        isTypeStyleShadow = false;
    } else {
        auto shadowStyle = GetToastDefaultShadowStyle();
        CHECK_EQUAL_VOID(GetShadowFromTheme(shadowStyle, shadowProps), false);
    }
    shadow = shadowProps;
}

void GetToastEnableHoverMode(napi_env env, napi_value enableHoverModeNApi, bool& enableHoverMode)
{
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, enableHoverModeNApi, &valueType);
    if (valueType == napi_boolean) {
        napi_get_value_bool(env, enableHoverModeNApi, &enableHoverMode);
    }
}

void GetToastHoverModeArea(napi_env env, napi_value hoverModeAreaNApi, HoverModeAreaType& hoverModeArea)
{
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, hoverModeAreaNApi, &valueType);
    if (valueType == napi_number) {
        int32_t num = -1;
        napi_get_value_int32(env, hoverModeAreaNApi, &num);
        if (num >= 0 && num <= static_cast<int32_t>(HoverModeAreaType::BOTTOM_SCREEN)) {
            hoverModeArea = static_cast<HoverModeAreaType>(num);
        }
    }
}

void GetToastHoverModeParams(napi_env env, napi_value argv, NG::ToastInfo& toastInfo)
{
    napi_value enableHoverModeNApi = nullptr;
    napi_value hoverModeAreaNApi = nullptr;

    napi_get_named_property(env, argv, "enableHoverMode", &enableHoverModeNApi);
    napi_get_named_property(env, argv, "hoverModeArea", &hoverModeAreaNApi);

    GetToastEnableHoverMode(env, enableHoverModeNApi, toastInfo.enableHoverMode);
    GetToastHoverModeArea(env, hoverModeAreaNApi, toastInfo.hoverModeArea);
}

bool GetToastParams(napi_env env, napi_value argv, NG::ToastInfo& toastInfo)
{
    napi_value messageNApi = nullptr;
    napi_value durationNApi = nullptr;
    napi_value bottomNApi = nullptr;
    napi_value showModeNApi = nullptr;
    napi_value alignmentApi = nullptr;
    napi_value offsetApi = nullptr;
    napi_value backgroundColorNApi = nullptr;
    napi_value textColorNApi = nullptr;
    napi_value backgroundBlurStyleNApi = nullptr;
    napi_value shadowNApi = nullptr;

    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, argv, &valueType);
    if (valueType == napi_object) {
        // message can not be null
        if (!HasProperty(env, argv, "message")) {
            NapiThrow(env, "Required input parameters are missing.", ERROR_CODE_PARAM_INVALID);
            return false;
        }
        napi_get_named_property(env, argv, "message", &messageNApi);
        napi_get_named_property(env, argv, "duration", &durationNApi);
        napi_get_named_property(env, argv, "bottom", &bottomNApi);
        napi_get_named_property(env, argv, "showMode", &showModeNApi);
        napi_get_named_property(env, argv, "alignment", &alignmentApi);
        napi_get_named_property(env, argv, "offset", &offsetApi);
        napi_get_named_property(env, argv, "backgroundColor", &backgroundColorNApi);
        napi_get_named_property(env, argv, "textColor", &textColorNApi);
        napi_get_named_property(env, argv, "backgroundBlurStyle", &backgroundBlurStyleNApi);
        napi_get_named_property(env, argv, "shadow", &shadowNApi);
    } else {
        NapiThrow(env, "The type of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
        return false;
    }
    if (!GetToastMessage(env, messageNApi, toastInfo.message) ||
        !GetToastDuration(env, durationNApi, toastInfo.duration) ||
        !GetToastBottom(env, bottomNApi, toastInfo.bottom) ||
        !GetToastShowMode(env, showModeNApi, toastInfo.showMode) ||
        !GetToastAlignment(env, alignmentApi, toastInfo.alignment) ||
        !GetToastOffset(env, offsetApi, toastInfo.offset)) {
        return false;
    }
    GetToastHoverModeParams(env, argv, toastInfo);
    GetToastBackgroundColor(env, backgroundColorNApi, toastInfo.backgroundColor);
    GetToastTextColor(env, textColorNApi, toastInfo.textColor);
    GetToastBackgroundBlurStyle(env, backgroundBlurStyleNApi, toastInfo.backgroundBlurStyle);
    GetToastShadow(env, shadowNApi, toastInfo.shadow, toastInfo.isTypeStyleShadow);
    return true;
}

bool ShowToast(napi_env env, NG::ToastInfo& toastInfo, std::function<void(int32_t)>& toastCallback)
{
#ifdef OHOS_STANDARD_SYSTEM
    if ((SystemProperties::GetExtSurfaceEnabled() || !ContainerIsService()) && !ContainerIsSceneBoard() &&
        toastInfo.showMode == NG::ToastShowMode::DEFAULT) {
        auto delegate = EngineHelper::GetCurrentDelegateSafely();
        if (!delegate) {
            NapiThrow(env, "Can not get delegate.", ERROR_CODE_INTERNAL_ERROR);
            return false;
        }
        TAG_LOGD(AceLogTag::ACE_DIALOG, "before delegate show toast");
        delegate->ShowToast(toastInfo, std::move(toastCallback));
    } else if (SubwindowManager::GetInstance() != nullptr) {
        TAG_LOGD(AceLogTag::ACE_DIALOG, "before subwindow manager show toast");
        SubwindowManager::GetInstance()->ShowToast(toastInfo, std::move(toastCallback));
    }
#else
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        NapiThrow(env, "UI execution context not found.", ERROR_CODE_INTERNAL_ERROR);
        return false;
    }
    if (toastInfo.showMode == NG::ToastShowMode::DEFAULT) {
        TAG_LOGD(AceLogTag::ACE_DIALOG, "before delegate show toast");
        delegate->ShowToast(toastInfo, std::move(toastCallback));
    } else if (SubwindowManager::GetInstance() != nullptr) {
        TAG_LOGD(AceLogTag::ACE_DIALOG, "before subwindow manager show toast");
        SubwindowManager::GetInstance()->ShowToast(toastInfo, std::move(toastCallback));
    }
#endif
    return true;
}

napi_value JSPromptShowToast(napi_env env, napi_callback_info info)
{
    TAG_LOGD(AceLogTag::ACE_DIALOG, "show toast enter");
    size_t requireArgc = 1;
    size_t argc = 1;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, &argv, &thisVar, &data);
    if (argc != requireArgc) {
        NapiThrow(env, "The number of parameters must be equal to 1.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }
    int32_t alignment = -1;
    int32_t updateAlignment = 0;
    const int32_t steps = 2; // 2: alignment from theme
    auto pipelineContext = PipelineBase::GetCurrentContext();
    if (pipelineContext) {
        auto toastTheme = pipelineContext->GetTheme<ToastTheme>();
        updateAlignment = steps - 1;
        if (toastTheme) {
            alignment = toastTheme->GetAlign();
            updateAlignment = steps;
        }
    }
    auto toastInfo = NG::ToastInfo { .duration = -1, .showMode = NG::ToastShowMode::DEFAULT, .alignment = alignment };
    if (!GetToastParams(env, argv, toastInfo)) {
        return nullptr;
    }
    TAG_LOGD(AceLogTag::ACE_DIALOG, "The show toast process: parameters are prased successfully, "
        "updateAlignment is %{public}d", updateAlignment);
    std::function<void(int32_t)> toastCallback = nullptr;
    ShowToast(env, toastInfo, toastCallback);
    return nullptr;
}

napi_value JSPromptOpenToast(napi_env env, napi_callback_info info)
{
    TAG_LOGD(AceLogTag::ACE_DIALOG, "open toast enter");
    size_t requireArgc = 1;
    size_t argc = 1;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, &argv, &thisVar, &data);
    if (argc != requireArgc) {
        NapiThrow(env, "The number of parameters must be equal to 1.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }
    auto toastInfo = NG::ToastInfo { .duration = -1, .showMode = NG::ToastShowMode::DEFAULT, .alignment = -1 };
    if (!GetToastParams(env, argv, toastInfo)) {
        return nullptr;
    }
    napi_deferred deferred;
    napi_value result;
    napi_create_promise(env, &deferred, &result);
    std::function<void(int32_t)> toastCallback = nullptr;
    toastCallback = [env, deferred](int32_t toastId) mutable {
        napi_value napiToastId = nullptr;
        napi_create_int32(env, toastId, &napiToastId);
        napi_resolve_deferred(env, deferred, napiToastId);
    };
    if (ShowToast(env, toastInfo, toastCallback)) {
        return result;
    }
    return nullptr;
}

void CloseToast(napi_env env, int32_t toastId, NG::ToastShowMode showMode)
{
    std::function<void(int32_t)> toastCloseCallback = nullptr;
    toastCloseCallback = [env](int32_t errorCode) mutable {
        if (errorCode != ERROR_CODE_NO_ERROR) {
            NapiThrow(env, "", errorCode);
        }
    };
#ifdef OHOS_STANDARD_SYSTEM
    if ((SystemProperties::GetExtSurfaceEnabled() || !ContainerIsService()) && !ContainerIsSceneBoard() &&
        showMode == NG::ToastShowMode::DEFAULT) {
        auto delegate = EngineHelper::GetCurrentDelegateSafely();
        if (delegate) {
            delegate->CloseToast(toastId, std::move(toastCloseCallback));
        } else {
            NapiThrow(env, "Can not get delegate.", ERROR_CODE_INTERNAL_ERROR);
        }
    } else if (SubwindowManager::GetInstance() != nullptr) {
        SubwindowManager::GetInstance()->CloseToast(toastId, showMode, std::move(toastCloseCallback));
    }
#else
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        NapiThrow(env, "UI execution context not found.", ERROR_CODE_INTERNAL_ERROR);
    }
    if (showMode == NG::ToastShowMode::DEFAULT) {
        delegate->CloseToast(toastId, std::move(toastCloseCallback));
    } else if (SubwindowManager::GetInstance() != nullptr) {
        SubwindowManager::GetInstance()->CloseToast(toastId, showMode, std::move(toastCloseCallback));
    }
#endif
}

napi_value JSPromptCloseToast(napi_env env, napi_callback_info info)
{
    TAG_LOGD(AceLogTag::ACE_DIALOG, "closeToast enter");
    size_t argc = 1;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc != 1) {
        NapiThrow(env, "The number of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }
    int32_t id = -1;
    napi_get_value_int32(env, args[0], &id);
    if (id < 0 || id > INT32_MAX) {
        NapiThrow(env, "The toastId is invalid.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }
    int32_t showModeVal = static_cast<int32_t>(static_cast<uint32_t>(id) & 0b111);
    int32_t toastId =
        static_cast<int32_t>(static_cast<uint32_t>(id) >>
                             3); // 3 : Move 3 bits to the right to get toastId, and the last 3 bits are the showMode
    if (toastId < 0 || showModeVal < 0 || showModeVal > static_cast<int32_t>(NG::ToastShowMode::SYSTEM_TOP_MOST)) {
        NapiThrow(env, "", ERROR_CODE_TOAST_NOT_FOUND);
        return nullptr;
    }
    auto showMode = static_cast<NG::ToastShowMode>(showModeVal);
    CloseToast(env, toastId, showMode);
    return nullptr;
}

struct PromptAsyncContext {
    napi_env env = nullptr;
    napi_value titleNApi = nullptr;
    napi_value messageNApi = nullptr;
    napi_value buttonsNApi = nullptr;
    napi_value autoCancel = nullptr;
    napi_value showInSubWindow = nullptr;
    napi_value isModal = nullptr;
    napi_value alignmentApi = nullptr;
    napi_value offsetApi = nullptr;
    napi_value maskRectApi = nullptr;
    napi_value builder = nullptr;
    napi_value onWillDismiss = nullptr;
    napi_value backgroundColorApi = nullptr;
    napi_value backgroundBlurStyleApi = nullptr;
    napi_value blurStyleOptionApi = nullptr;
    napi_value effectOptionApi = nullptr;
    napi_value enableHoverMode = nullptr;
    napi_value hoverModeAreaApi = nullptr;
    napi_value borderWidthApi = nullptr;
    napi_value borderColorApi = nullptr;
    napi_value borderStyleApi = nullptr;
    napi_value borderRadiusApi = nullptr;
    napi_value shadowApi = nullptr;
    napi_value widthApi = nullptr;
    napi_value heightApi = nullptr;
    napi_value frameNodePtr = nullptr;
    napi_value maskColorApi = nullptr;
    napi_value onDidAppear = nullptr;
    napi_value onDidDisappear = nullptr;
    napi_value onWillAppear = nullptr;
    napi_value onWillDisappear = nullptr;
    napi_value transitionApi = nullptr;
    napi_value dialogTransitionApi = nullptr;
    napi_value maskTransitionApi = nullptr;
    napi_ref callbackSuccess = nullptr;
    napi_ref callbackCancel = nullptr;
    napi_ref callbackComplete = nullptr;
    std::string titleString;
    std::string messageString;
    std::vector<ButtonInfo> buttons;
    bool autoCancelBool = true;
    bool showInSubWindowBool = false;
    bool isModalBool = true;
    std::set<std::string> callbacks;
    std::string callbackSuccessString;
    std::string callbackCancelString;
    std::string callbackCompleteString;
    napi_deferred deferred = nullptr;
    napi_ref callbackRef = nullptr;
    napi_ref builderRef = nullptr;
    napi_ref onWillDismissRef = nullptr;
    int32_t callbackType = -1;
    int32_t successType = -1;
    bool valid = true;
    int32_t instanceId = -1;
    void* nativePtr = nullptr;
    napi_ref onDidAppearRef = nullptr;
    napi_ref onDidDisappearRef = nullptr;
    napi_ref onWillAppearRef = nullptr;
    napi_ref onWillDisappearRef = nullptr;
    napi_value keyboardAvoidModeApi = nullptr;
    napi_value keyboardAvoidDistanceApi = nullptr;
    napi_value levelOrderApi = nullptr;
    napi_value dialogLevelModeApi = nullptr;
    napi_value dialogLevelUniqueId = nullptr;
    napi_value dialogImmersiveModeApi = nullptr;
    napi_value focusableApi = nullptr;
};

void DeleteContextAndThrowError(
    napi_env env, std::shared_ptr<PromptAsyncContext>& context, const std::string& errorMessage)
{
    if (!context) {
        // context is null, no need to delete
        return;
    }
    NapiThrow(env, errorMessage, ERROR_CODE_PARAM_INVALID);
}

int32_t GetButtonArraryLen(napi_env env, std::shared_ptr<PromptAsyncContext>& context,
    int32_t maxButtonNum)
{
    uint32_t buttonsLen = 0;
    napi_get_array_length(env, context->buttonsNApi, &buttonsLen);
    int32_t buttonsLenInt = static_cast<int32_t>(buttonsLen);
    if (buttonsLenInt > maxButtonNum && maxButtonNum != -1) {
        buttonsLenInt = maxButtonNum;
    }
    return buttonsLenInt;
}

void GetPrimaryButtonNum(napi_env env, std::shared_ptr<PromptAsyncContext>& context,
    int32_t buttonsLenInt, int32_t& primaryButtonNum)
{
    napi_value buttonArray = nullptr;
    napi_value primaryButtonNApi = nullptr;
    napi_valuetype valueType = napi_undefined;
    for (int32_t index = 0; index < buttonsLenInt; index++) {
        napi_get_element(env, context->buttonsNApi, index, &buttonArray);
        bool isPrimaryButtonSet = false;
        napi_get_named_property(env, buttonArray, "primary", &primaryButtonNApi);
        napi_typeof(env, primaryButtonNApi, &valueType);
        if (valueType == napi_boolean) {
            napi_get_value_bool(env, primaryButtonNApi, &isPrimaryButtonSet);
        }
        if (isPrimaryButtonSet) {
            primaryButtonNum++;
        }
    }
}

bool ParseButtons(napi_env env, std::shared_ptr<PromptAsyncContext>& context,
    int32_t maxButtonNum, int32_t& primaryButtonNum)
{
    napi_value buttonArray = nullptr;
    napi_value textNApi = nullptr;
    napi_value colorNApi = nullptr;
    napi_value primaryButtonNApi = nullptr;
    napi_valuetype valueType = napi_undefined;
    int32_t buttonsLenInt = GetButtonArraryLen(env, context, maxButtonNum);
    GetPrimaryButtonNum(env, context, buttonsLenInt, primaryButtonNum);
    for (int32_t index = 0; index < buttonsLenInt; index++) {
        napi_get_element(env, context->buttonsNApi, index, &buttonArray);
        if (!HasProperty(env, buttonArray, "text")) {
            DeleteContextAndThrowError(env, context, "Required input parameters are missing.");
            return false;
        }
        std::string textString;
        napi_get_named_property(env, buttonArray, "text", &textNApi);
        if (!GetNapiString(env, textNApi, textString, valueType)) {
            DeleteContextAndThrowError(env, context, "The type of parameters is incorrect.");
            return false;
        }
        if (!HasProperty(env, buttonArray, "color")) {
            DeleteContextAndThrowError(env, context, "Required input parameters are missing.");
            return false;
        }
        std::string colorString;
        napi_get_named_property(env, buttonArray, "color", &colorNApi);
        if (!GetNapiString(env, colorNApi, colorString, valueType)) {
            if (valueType == napi_undefined) {
                colorString = DEFAULT_FONT_COLOR_STRING_VALUE;
            } else {
                DeleteContextAndThrowError(env, context, "The type of parameters is incorrect.");
                return false;
            }
        }
        ButtonInfo buttonInfo = { .text = textString, .textColor = colorString };
        if (primaryButtonNum <= PROMPTACTION_VALID_PRIMARY_BUTTON_NUM) {
            napi_get_named_property(env, buttonArray, "primary", &primaryButtonNApi);
            napi_typeof(env, primaryButtonNApi, &valueType);
            if (valueType == napi_boolean) {
                napi_get_value_bool(env, primaryButtonNApi, &buttonInfo.isPrimary);
            }
        }
        context->buttons.emplace_back(buttonInfo);
    }
    return true;
}

bool ParseButtonsPara(napi_env env, std::shared_ptr<PromptAsyncContext>& context,
    int32_t maxButtonNum, bool isShowActionMenu)
{
    bool isBool = false;
    napi_valuetype valueType = napi_undefined;
    int32_t primaryButtonNum = 0;
    napi_is_array(env, context->buttonsNApi, &isBool);
    napi_typeof(env, context->buttonsNApi, &valueType);
    if (valueType == napi_object && isBool) {
        if (!ParseButtons(env, context, SHOW_DIALOG_BUTTON_NUM_MAX, primaryButtonNum)) {
            return false;
        }
    } else if (isShowActionMenu) {
        DeleteContextAndThrowError(env, context, "The type of the button parameters is incorrect.");
        return false;
    }
    if (isShowActionMenu) {
        std::string buttonCancelText = "Cancel";
        auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
        if (pipeline) {
            auto theme = pipeline->GetTheme<ButtonTheme>();
            if (theme) {
                buttonCancelText = theme->GetCancelText();
            }
        }
        ButtonInfo buttonInfo = { .text = buttonCancelText,
            .textColor = "", .isPrimary = primaryButtonNum == 0 ? true : false};
        context->buttons.emplace_back(buttonInfo);
    }
    return true;
}

void GetNapiDialogProps(napi_env env, const std::shared_ptr<PromptAsyncContext>& asyncContext,
    std::optional<DialogAlignment>& alignment, std::optional<DimensionOffset>& offset,
    std::optional<DimensionRect>& maskRect)
{
    TAG_LOGD(AceLogTag::ACE_DIALOG, "get napi dialog props enter");
    napi_valuetype valueType = napi_undefined;
    // parse alignment
    napi_typeof(env, asyncContext->alignmentApi, &valueType);
    if (valueType == napi_number) {
        int32_t num;
        napi_get_value_int32(env, asyncContext->alignmentApi, &num);
        if (num >= 0 && num < static_cast<int32_t>(DIALOG_ALIGNMENT.size())) {
            alignment = DIALOG_ALIGNMENT[num];
        }
    }

    // parse offset
    napi_typeof(env, asyncContext->offsetApi, &valueType);
    if (valueType == napi_object) {
        napi_value dxApi = nullptr;
        napi_value dyApi = nullptr;
        napi_get_named_property(env, asyncContext->offsetApi, "dx", &dxApi);
        napi_get_named_property(env, asyncContext->offsetApi, "dy", &dyApi);
        CalcDimension dx;
        CalcDimension dy;
        ParseNapiDimension(env, dx, dxApi, DimensionUnit::VP);
        ParseNapiDimension(env, dy, dyApi, DimensionUnit::VP);
        offset = DimensionOffset { dx, dy };
    }

    // parse maskRect
    DimensionRect rect;
    rect.SetOffset(DimensionOffset(CalcDimension(0, DimensionUnit::VP), CalcDimension(0, DimensionUnit::VP)));
    rect.SetSize(DimensionSize(CalcDimension(1, DimensionUnit::PERCENT), CalcDimension(1, DimensionUnit::PERCENT)));
    maskRect = rect;
    napi_typeof(env, asyncContext->maskRectApi, &valueType);
    if (valueType == napi_object) {
        napi_value xApi = nullptr;
        napi_value yApi = nullptr;
        napi_value widthApi = nullptr;
        napi_value heightApi = nullptr;
        napi_get_named_property(env, asyncContext->maskRectApi, "x", &xApi);
        napi_get_named_property(env, asyncContext->maskRectApi, "y", &yApi);
        napi_get_named_property(env, asyncContext->maskRectApi, "width", &widthApi);
        napi_get_named_property(env, asyncContext->maskRectApi, "height", &heightApi);
        CalcDimension x;
        CalcDimension y;
        CalcDimension width;
        CalcDimension height;
        ParseNapiDimension(env, x, xApi, DimensionUnit::VP);
        ParseNapiDimension(env, y, yApi, DimensionUnit::VP);
        ParseNapiDimension(env, width, widthApi, DimensionUnit::VP);
        ParseNapiDimension(env, height, heightApi, DimensionUnit::VP);
        DimensionOffset dimensionOffset = { x, y };
        maskRect = DimensionRect { width, height, dimensionOffset };
    }
}

void GetNapiBlurStyleAndHoverModeProps(napi_env env, const std::shared_ptr<PromptAsyncContext>& asyncContext,
    std::optional<int32_t>& backgroundBlurStyle, std::optional<HoverModeAreaType>& hoverModeArea,
    std::optional<bool>& enableHoverMode)
{
    TAG_LOGD(AceLogTag::ACE_DIALOG, "get napi dialog backgroundBlurStyle and hoverModeArea props enter");
    napi_valuetype blurStyleValueType = napi_undefined;

    napi_typeof(env, asyncContext->backgroundBlurStyleApi, &blurStyleValueType);
    if (blurStyleValueType == napi_number) {
        int32_t num = 0;
        napi_get_value_int32(env, asyncContext->backgroundBlurStyleApi, &num);
        if (num >= 0 && num < BG_BLUR_STYLE_MAX_INDEX) {
            backgroundBlurStyle = num;
        }
    }

    napi_valuetype enableHoverModeValueType = napi_undefined;
    napi_typeof(env, asyncContext->enableHoverMode, &enableHoverModeValueType);
    if (enableHoverModeValueType == napi_boolean) {
        bool enableHoverModeBool = false;
        napi_get_value_bool(env, asyncContext->enableHoverMode, &enableHoverModeBool);
        enableHoverMode = enableHoverModeBool;
    }

    napi_valuetype hoverModeValueType = napi_undefined;
    napi_typeof(env, asyncContext->hoverModeAreaApi, &hoverModeValueType);
    if (hoverModeValueType == napi_number) {
        int32_t num = 0;
        napi_get_value_int32(env, asyncContext->hoverModeAreaApi, &num);
        if (num >= 0 && num < static_cast<int32_t>(HOVER_MODE_AREA_TYPE.size())) {
            hoverModeArea = HOVER_MODE_AREA_TYPE[num];
        }
    }
}

void GetBackgroundBlurStyleOption(napi_env env, const std::shared_ptr<PromptAsyncContext>& asyncContext,
    std::optional<BlurStyleOption>& blurStyleOption)
{
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, asyncContext->blurStyleOptionApi, &valueType);
    if (valueType == napi_object) {
        BlurStyleOption styleOption;
        auto delegate = EngineHelper::GetCurrentDelegateSafely();
        if (delegate) {
            delegate->GetBackgroundBlurStyleOption(asyncContext->blurStyleOptionApi, styleOption);
        }
        if (!blurStyleOption.has_value()) {
            blurStyleOption.emplace();
        }
        blurStyleOption.value() = styleOption;
    }
}

void GetBackgroundEffect(
    napi_env env, const std::shared_ptr<PromptAsyncContext>& asyncContext, std::optional<EffectOption>& effectOption)
{
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, asyncContext->effectOptionApi, &valueType);
    if (valueType == napi_object) {
        EffectOption styleOption;
        auto delegate = EngineHelper::GetCurrentDelegateSafely();
        if (delegate) {
            delegate->GetBackgroundEffect(asyncContext->effectOptionApi, styleOption);
        }
        if (!effectOption.has_value()) {
            effectOption.emplace();
        }
        effectOption.value() = styleOption;
    }
}

void CheckNapiDimension(CalcDimension value)
{
    if (value.IsNegative()) {
        value.Reset();
    }
}

std::optional<NG::BorderColorProperty> GetBorderColorProps(
    napi_env env, const std::shared_ptr<PromptAsyncContext>& asyncContext)
{
    napi_valuetype valueType = napi_undefined;
    NG::BorderColorProperty colorProperty;
    napi_typeof(env, asyncContext->borderColorApi, &valueType);
    if (valueType != napi_number && valueType != napi_string && valueType != napi_object) {
        return std::nullopt;
    }
    Color borderColor;
    if (ParseNapiColor(env, asyncContext->borderColorApi, borderColor)) {
        colorProperty.SetColor(borderColor);
        return colorProperty;
    } else if (valueType == napi_object) {
        napi_value leftApi = nullptr;
        napi_value rightApi = nullptr;
        napi_value topApi = nullptr;
        napi_value bottomApi = nullptr;
        napi_get_named_property(env, asyncContext->borderColorApi, "left", &leftApi);
        napi_get_named_property(env, asyncContext->borderColorApi, "right", &rightApi);
        napi_get_named_property(env, asyncContext->borderColorApi, "top", &topApi);
        napi_get_named_property(env, asyncContext->borderColorApi, "bottom", &bottomApi);
        Color leftColor;
        Color rightColor;
        Color topColor;
        Color bottomColor;
        if (ParseNapiColor(env, leftApi, leftColor)) {
            colorProperty.leftColor = leftColor;
        }
        if (ParseNapiColor(env, rightApi, rightColor)) {
            colorProperty.rightColor = rightColor;
        }
        if (ParseNapiColor(env, topApi, topColor)) {
            colorProperty.topColor = topColor;
        }
        if (ParseNapiColor(env, bottomApi, bottomColor)) {
            colorProperty.bottomColor = bottomColor;
        }
        colorProperty.multiValued = true;
        return colorProperty;
    }
    return std::nullopt;
}

std::optional<NG::BorderWidthProperty> GetBorderWidthProps(
    napi_env env, const std::shared_ptr<PromptAsyncContext>& asyncContext)
{
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, asyncContext->borderWidthApi, &valueType);
    if (valueType != napi_number && valueType != napi_string && valueType != napi_object) {
        return std::nullopt;
    }
    NG::BorderWidthProperty borderWidthProps;
    CalcDimension borderWidth;
    if (ParseNapiDimensionNG(env, borderWidth, asyncContext->borderWidthApi, DimensionUnit::VP, true)) {
        CheckNapiDimension(borderWidth);
        borderWidthProps = NG::BorderWidthProperty({ borderWidth, borderWidth, borderWidth, borderWidth });
        return borderWidthProps;
    } else if (valueType == napi_object) {
        napi_value leftApi = nullptr;
        napi_value rightApi = nullptr;
        napi_value topApi = nullptr;
        napi_value bottomApi = nullptr;
        napi_get_named_property(env, asyncContext->borderWidthApi, "left", &leftApi);
        napi_get_named_property(env, asyncContext->borderWidthApi, "right", &rightApi);
        napi_get_named_property(env, asyncContext->borderWidthApi, "top", &topApi);
        napi_get_named_property(env, asyncContext->borderWidthApi, "bottom", &bottomApi);
        CalcDimension leftDimen;
        CalcDimension rightDimen;
        CalcDimension topDimen;
        CalcDimension bottomDimen;
        if (ParseNapiDimensionNG(env, leftDimen, leftApi, DimensionUnit::VP, true)) {
            CheckNapiDimension(leftDimen);
            borderWidthProps.leftDimen = leftDimen;
        }
        if (ParseNapiDimensionNG(env, rightDimen, rightApi, DimensionUnit::VP, true)) {
            CheckNapiDimension(rightDimen);
            borderWidthProps.rightDimen = rightDimen;
        }
        if (ParseNapiDimensionNG(env, topDimen, topApi, DimensionUnit::VP, true)) {
            CheckNapiDimension(topDimen);
            borderWidthProps.topDimen = topDimen;
        }
        if (ParseNapiDimensionNG(env, bottomDimen, bottomApi, DimensionUnit::VP, true)) {
            CheckNapiDimension(bottomDimen);
            borderWidthProps.bottomDimen = bottomDimen;
        }
        borderWidthProps.multiValued = true;
        return borderWidthProps;
    }
    return std::nullopt;
}

std::optional<NG::BorderRadiusProperty> GetBorderRadiusProps(
    napi_env env, const std::shared_ptr<PromptAsyncContext>& asyncContext)
{
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, asyncContext->borderRadiusApi, &valueType);
    if (valueType != napi_number && valueType != napi_object && valueType != napi_string) {
        return std::nullopt;
    }
    CalcDimension borderRadius;
    if (ParseNapiDimensionNG(env, borderRadius, asyncContext->borderRadiusApi, DimensionUnit::VP, true)) {
        CheckNapiDimension(borderRadius);
        return NG::BorderRadiusProperty(borderRadius);
    } else if (valueType == napi_object) {
        NG::BorderRadiusProperty radiusProps;
        napi_value topLeft = nullptr;
        napi_value topRight = nullptr;
        napi_value bottomLeft = nullptr;
        napi_value bottomRight = nullptr;
        napi_get_named_property(env, asyncContext->borderRadiusApi, "topLeft", &topLeft);
        napi_get_named_property(env, asyncContext->borderRadiusApi, "topRight", &topRight);
        napi_get_named_property(env, asyncContext->borderRadiusApi, "bottomLeft", &bottomLeft);
        napi_get_named_property(env, asyncContext->borderRadiusApi, "bottomRight", &bottomRight);
        CalcDimension radiusTopLeft;
        CalcDimension radiusTopRight;
        CalcDimension radiusBottomLeft;
        CalcDimension radiusBottomRight;
        if (ParseNapiDimensionNG(env, radiusTopLeft, topLeft, DimensionUnit::VP, true)) {
            CheckNapiDimension(radiusTopLeft);
            radiusProps.radiusTopLeft = radiusTopLeft;
        }
        if (ParseNapiDimensionNG(env, radiusTopRight, topRight, DimensionUnit::VP, true)) {
            CheckNapiDimension(radiusTopRight);
            radiusProps.radiusTopRight = radiusTopRight;
        }
        if (ParseNapiDimensionNG(env, radiusBottomLeft, bottomLeft, DimensionUnit::VP, true)) {
            CheckNapiDimension(radiusBottomLeft);
            radiusProps.radiusBottomLeft = radiusBottomLeft;
        }
        if (ParseNapiDimensionNG(env, radiusBottomRight, bottomRight, DimensionUnit::VP, true)) {
            CheckNapiDimension(radiusBottomRight);
            radiusProps.radiusBottomRight = radiusBottomRight;
        }
        radiusProps.multiValued = true;
        return radiusProps;
    }
    return std::nullopt;
}

std::optional<Color> GetColorProps(napi_env env, napi_value value)
{
    Color color;
    if (ParseNapiColor(env, value, color)) {
        return color;
    }
    return std::nullopt;
}

std::optional<NG::BorderStyleProperty> GetBorderStyleProps(
    napi_env env, const std::shared_ptr<PromptAsyncContext>& asyncContext)
{
    NG::BorderStyleProperty styleProps;
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, asyncContext->borderStyleApi, &valueType);
    if (valueType != napi_number && valueType != napi_object) {
        return std::nullopt;
    } else if (valueType == napi_object) {
        napi_value leftApi = nullptr;
        napi_value rightApi = nullptr;
        napi_value topApi = nullptr;
        napi_value bottomApi = nullptr;
        napi_get_named_property(env, asyncContext->borderStyleApi, "left", &leftApi);
        napi_get_named_property(env, asyncContext->borderStyleApi, "right", &rightApi);
        napi_get_named_property(env, asyncContext->borderStyleApi, "top", &topApi);
        napi_get_named_property(env, asyncContext->borderStyleApi, "bottom", &bottomApi);
        std::optional<BorderStyle> styleLeft;
        std::optional<BorderStyle> styleRight;
        std::optional<BorderStyle> styleTop;
        std::optional<BorderStyle> styleBottom;
        if (ParseStyle(env, leftApi, styleLeft)) {
            styleProps.styleLeft = styleLeft;
        }
        if (ParseStyle(env, rightApi, styleRight)) {
            styleProps.styleRight = styleRight;
        }
        if (ParseStyle(env, topApi, styleTop)) {
            styleProps.styleTop = styleTop;
        }
        if (ParseStyle(env, bottomApi, styleBottom)) {
            styleProps.styleBottom = styleBottom;
        }
        styleProps.multiValued = true;
        return styleProps;
    }
    std::optional<BorderStyle> borderStyle;
    if (ParseStyle(env, asyncContext->borderStyleApi, borderStyle)) {
        styleProps = NG::BorderStyleProperty({ borderStyle, borderStyle, borderStyle, borderStyle });
        return styleProps;
    }
    return std::nullopt;
}

void GetNapiObjectShadow(napi_env env, const std::shared_ptr<PromptAsyncContext>& asyncContext, Shadow& shadow)
{
    napi_value radiusApi = nullptr;
    napi_value colorApi = nullptr;
    napi_value typeApi = nullptr;
    napi_value fillApi = nullptr;
    napi_get_named_property(env, asyncContext->shadowApi, "radius", &radiusApi);
    napi_get_named_property(env, asyncContext->shadowApi, "color", &colorApi);
    napi_get_named_property(env, asyncContext->shadowApi, "type", &typeApi);
    napi_get_named_property(env, asyncContext->shadowApi, "fill", &fillApi);
    double radius = 0.0;
    napi_get_value_double(env, radiusApi, &radius);
    if (LessNotEqual(radius, 0.0)) {
        radius = 0.0;
    }
    shadow.SetBlurRadius(radius);
    Color color;
    ShadowColorStrategy shadowColorStrategy;
    if (ParseShadowColorStrategy(env, colorApi, shadowColorStrategy)) {
        shadow.SetShadowColorStrategy(shadowColorStrategy);
    } else if (ParseNapiColor(env, colorApi, color)) {
        shadow.SetColor(color);
    }
    napi_valuetype valueType = GetValueType(env, typeApi);
    int32_t shadowType = static_cast<int32_t>(ShadowType::COLOR);
    if (valueType == napi_number) {
        napi_get_value_int32(env, typeApi, &shadowType);
    }
    if (shadowType != static_cast<int32_t>(ShadowType::BLUR)) {
        shadowType = static_cast<int32_t>(ShadowType::COLOR);
    }
    shadowType =
        std::clamp(shadowType, static_cast<int32_t>(ShadowType::COLOR), static_cast<int32_t>(ShadowType::BLUR));
    shadow.SetShadowType(static_cast<ShadowType>(shadowType));
    valueType = GetValueType(env, fillApi);
    bool isFilled = false;
    if (valueType == napi_boolean) {
        napi_get_value_bool(env, fillApi, &isFilled);
    }
    shadow.SetIsFilled(isFilled);
}

std::optional<Shadow> GetShadowProps(napi_env env, const std::shared_ptr<PromptAsyncContext>& asyncContext)
{
    Shadow shadow;
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, asyncContext->shadowApi, &valueType);
    if (valueType != napi_object && valueType != napi_number) {
        return std::nullopt;
    }
    if (valueType == napi_number) {
        int32_t num = 0;
        if (napi_get_value_int32(env, asyncContext->shadowApi, &num) == napi_ok) {
            auto style = static_cast<ShadowStyle>(num);
            GetShadowFromTheme(style, shadow);
            return shadow;
        }
    } else if (valueType == napi_object) {
        napi_value offsetXApi = nullptr;
        napi_value offsetYApi = nullptr;
        napi_get_named_property(env, asyncContext->shadowApi, "offsetX", &offsetXApi);
        napi_get_named_property(env, asyncContext->shadowApi, "offsetY", &offsetYApi);
        ResourceInfo recv;
        bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
        if (ParseResourceParam(env, offsetXApi, recv)) {
            auto resourceWrapper = CreateResourceWrapper(recv);
            auto offsetX = resourceWrapper->GetDimension(recv.resId);
            double xValue = isRtl ? offsetX.Value() * (-1) : offsetX.Value();
            shadow.SetOffsetX(xValue);
        } else {
            CalcDimension offsetX;
            if (ParseNapiDimension(env, offsetX, offsetXApi, DimensionUnit::VP)) {
                double xValue = isRtl ? offsetX.Value() * (-1) : offsetX.Value();
                shadow.SetOffsetX(xValue);
            }
        }
        if (ParseResourceParam(env, offsetYApi, recv)) {
            auto resourceWrapper = CreateResourceWrapper(recv);
            auto offsetY = resourceWrapper->GetDimension(recv.resId);
            shadow.SetOffsetY(offsetY.Value());
        } else {
            CalcDimension offsetY;
            if (ParseNapiDimension(env, offsetY, offsetYApi, DimensionUnit::VP)) {
                shadow.SetOffsetY(offsetY.Value());
            }
        }
        GetNapiObjectShadow(env, asyncContext, shadow);
        return shadow;
    }
    return std::nullopt;
}

std::optional<CalcDimension> GetNapiDialogWidthProps(
    napi_env env, const std::shared_ptr<PromptAsyncContext>& asyncContext)
{
    std::optional<CalcDimension> widthProperty;
    CalcDimension width;
    if (ParseNapiDimensionNG(env, width, asyncContext->widthApi, DimensionUnit::VP, true)) {
        widthProperty = width;
    }
    return widthProperty;
}

std::optional<CalcDimension> GetKeyboardAvoidDistanceProps(
    napi_env env, const std::shared_ptr<PromptAsyncContext>& asyncContext)
{
    std::optional<CalcDimension> keyboardAvoidDistanceProperty;
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, asyncContext->keyboardAvoidDistanceApi, &valueType);
    if (valueType != napi_object) {
        return keyboardAvoidDistanceProperty;
    }
    if (valueType == napi_object) {
        napi_value avoidDistance = nullptr;
        napi_value avoidDistanceUnit = nullptr;
        napi_get_named_property(env, asyncContext->keyboardAvoidDistanceApi, "value", &avoidDistance);
        napi_get_named_property(env, asyncContext->keyboardAvoidDistanceApi, "unit", &avoidDistanceUnit);
        napi_valuetype distanceType = napi_undefined;
        napi_valuetype distanceUnitType = napi_undefined;
        napi_typeof(env, avoidDistance, &distanceType);
        napi_typeof(env, avoidDistanceUnit, &distanceUnitType);
        double avoidDistanceValue = 0.0;
        int32_t avoidDistanceUnitValue = 0;
        if (distanceType == napi_number && distanceUnitType == napi_number) {
            napi_get_value_double(env, avoidDistance, &avoidDistanceValue);
            napi_get_value_int32(env, avoidDistanceUnit, &avoidDistanceUnitValue);
            auto avoidDistanceUnitValueType = static_cast<DimensionUnit>(avoidDistanceUnitValue);
            if (avoidDistanceValue >= 0.0 && avoidDistanceUnitValueType >= DimensionUnit::PX &&
                avoidDistanceUnitValueType <= DimensionUnit::CALC &&
                avoidDistanceUnitValueType != DimensionUnit::PERCENT) {
                Dimension dimension(avoidDistanceValue, avoidDistanceUnitValueType);
                keyboardAvoidDistanceProperty = dimension;
            } else {
                Dimension dimension(DEFAULT_AVOID_DISTANCE, DimensionUnit::VP);
                keyboardAvoidDistanceProperty = dimension;
            }
        }
    }
    return keyboardAvoidDistanceProperty;
}

std::optional<CalcDimension> GetNapiDialogHeightProps(
    napi_env env, const std::shared_ptr<PromptAsyncContext>& asyncContext)
{
    std::optional<CalcDimension> heightProperty;
    CalcDimension height;
    if (ParseNapiDimensionNG(env, height, asyncContext->heightApi, DimensionUnit::VP, true)) {
        heightProperty = height;
    }
    return heightProperty;
}

int32_t GetDialogKeyboardAvoidMode(napi_env env, napi_value keyboardAvoidModeApi)
{
    int32_t mode = 0;
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, keyboardAvoidModeApi, &valueType);
    if (valueType == napi_number) {
        napi_get_value_int32(env, keyboardAvoidModeApi, &mode);
    }
    if (mode >= 0 && mode < static_cast<int32_t>(KEYBOARD_AVOID_MODE.size())) {
        return mode;
    }
    return 0;
}

void GetDialogLevelModeAndUniqueId(napi_env env, const std::shared_ptr<PromptAsyncContext>& asyncContext,
    LevelMode& dialogLevelMode, int32_t& dialogLevelUniqueId, ImmersiveMode& dialogImmersiveMode)
{
    int32_t mode = 0;
    int32_t immersiveMode = 0;
    napi_valuetype levelModeValueType = napi_undefined;
    napi_typeof(env, asyncContext->dialogLevelModeApi, &levelModeValueType);
    if (levelModeValueType == napi_number) {
        napi_get_value_int32(env, asyncContext->dialogLevelModeApi, &mode);
    }
    if (!asyncContext->showInSubWindowBool && mode >= 0 && mode < static_cast<int32_t>(DIALOG_LEVEL_MODE.size())) {
        dialogLevelMode = DIALOG_LEVEL_MODE[mode];
    }
    napi_valuetype levelUniquedIdValueType = napi_undefined;
    napi_typeof(env, asyncContext->dialogLevelUniqueId, &levelUniquedIdValueType);
    if (levelUniquedIdValueType == napi_number) {
        napi_get_value_int32(env, asyncContext->dialogLevelUniqueId, &dialogLevelUniqueId);
    }
    napi_valuetype immersiveModeValueType = napi_undefined;
    napi_typeof(env, asyncContext->dialogImmersiveModeApi, &immersiveModeValueType);
    if (immersiveModeValueType == napi_number) {
        napi_get_value_int32(env, asyncContext->dialogImmersiveModeApi, &immersiveMode);
    }
    if (immersiveMode >= 0 && immersiveMode < static_cast<int32_t>(DIALOG_IMMERSIVE_MODE.size())) {
        dialogImmersiveMode = DIALOG_IMMERSIVE_MODE[immersiveMode];
    }
}

void GetNapiNamedBoolProperties(napi_env env, std::shared_ptr<PromptAsyncContext>& asyncContext)
{
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, asyncContext->autoCancel, &valueType);
    if (valueType == napi_boolean) {
        napi_get_value_bool(env, asyncContext->autoCancel, &asyncContext->autoCancelBool);
    }
    napi_typeof(env, asyncContext->showInSubWindow, &valueType);
    if (valueType == napi_boolean) {
        napi_get_value_bool(env, asyncContext->showInSubWindow, &asyncContext->showInSubWindowBool);
    }
    napi_typeof(env, asyncContext->isModal, &valueType);
    if (valueType == napi_boolean) {
        napi_get_value_bool(env, asyncContext->isModal, &asyncContext->isModalBool);
    }
}

void GetNapiNamedProperties(napi_env env, napi_value* argv, size_t index,
    std::shared_ptr<PromptAsyncContext>& asyncContext)
{
    napi_valuetype valueType = napi_undefined;

    if (index == 0) {
        napi_get_named_property(env, argv[index], "builder", &asyncContext->builder);
        napi_get_named_property(env, argv[index], "backgroundColor", &asyncContext->backgroundColorApi);
        napi_get_named_property(env, argv[index], "backgroundBlurStyle", &asyncContext->backgroundBlurStyleApi);
        napi_get_named_property(env, argv[index], "backgroundBlurStyleOptions", &asyncContext->blurStyleOptionApi);
        napi_get_named_property(env, argv[index], "backgroundEffect", &asyncContext->effectOptionApi);
        napi_get_named_property(env, argv[index], "hoverModeArea", &asyncContext->hoverModeAreaApi);
        napi_get_named_property(env, argv[index], "cornerRadius", &asyncContext->borderRadiusApi);
        napi_get_named_property(env, argv[index], "borderWidth", &asyncContext->borderWidthApi);
        napi_get_named_property(env, argv[index], "borderColor", &asyncContext->borderColorApi);
        napi_get_named_property(env, argv[index], "borderStyle", &asyncContext->borderStyleApi);
        napi_get_named_property(env, argv[index], "shadow", &asyncContext->shadowApi);
        napi_get_named_property(env, argv[index], "width", &asyncContext->widthApi);
        napi_get_named_property(env, argv[index], "height", &asyncContext->heightApi);

        napi_typeof(env, asyncContext->builder, &valueType);
        if (valueType == napi_function) {
            napi_create_reference(env, asyncContext->builder, 1, &asyncContext->builderRef);
        }
    }
    napi_get_named_property(env, argv[index], "enableHoverMode", &asyncContext->enableHoverMode);
    napi_get_named_property(env, argv[index], "showInSubWindow", &asyncContext->showInSubWindow);
    napi_get_named_property(env, argv[index], "isModal", &asyncContext->isModal);
    napi_get_named_property(env, argv[index], "alignment", &asyncContext->alignmentApi);
    napi_get_named_property(env, argv[index], "offset", &asyncContext->offsetApi);
    napi_get_named_property(env, argv[index], "maskRect", &asyncContext->maskRectApi);
    napi_get_named_property(env, argv[index], "autoCancel", &asyncContext->autoCancel);
    napi_get_named_property(env, argv[index], "maskColor", &asyncContext->maskColorApi);
    napi_get_named_property(env, argv[index], "transition", &asyncContext->transitionApi);
    napi_get_named_property(env, argv[index], "dialogTransition", &asyncContext->dialogTransitionApi);
    napi_get_named_property(env, argv[index], "maskTransition", &asyncContext->maskTransitionApi);
    napi_get_named_property(env, argv[index], "onWillDismiss", &asyncContext->onWillDismiss);
    napi_get_named_property(env, argv[index], "onDidAppear", &asyncContext->onDidAppear);
    napi_get_named_property(env, argv[index], "onDidDisappear", &asyncContext->onDidDisappear);
    napi_get_named_property(env, argv[index], "onWillAppear", &asyncContext->onWillAppear);
    napi_get_named_property(env, argv[index], "onWillDisappear", &asyncContext->onWillDisappear);
    napi_get_named_property(env, argv[index], "keyboardAvoidMode", &asyncContext->keyboardAvoidModeApi);
    napi_get_named_property(env, argv[index], "keyboardAvoidDistance", &asyncContext->keyboardAvoidDistanceApi);
    napi_get_named_property(env, argv[index], "levelOrder", &asyncContext->levelOrderApi);
    napi_get_named_property(env, argv[index], "levelMode", &asyncContext->dialogLevelModeApi);
    napi_get_named_property(env, argv[index], "levelUniqueId", &asyncContext->dialogLevelUniqueId);
    napi_get_named_property(env, argv[index], "immersiveMode", &asyncContext->dialogImmersiveModeApi);
    napi_get_named_property(env, argv[index], "focusable", &asyncContext->focusableApi);

    GetNapiNamedBoolProperties(env, asyncContext);
}

bool JSPromptParseParam(napi_env env, size_t argc, napi_value* argv, std::shared_ptr<PromptAsyncContext>& asyncContext)
{
    for (size_t i = 0; i < argc; i++) {
        napi_valuetype valueType = napi_undefined;
        napi_typeof(env, argv[i], &valueType);
        if (i == 0 || i == 1) {
            if (valueType != napi_object) {
                DeleteContextAndThrowError(env, asyncContext, "The type of parameters is incorrect.");
                return false;
            }
            GetNapiNamedProperties(env, argv, i, asyncContext);
            auto result = napi_get_named_property(env, argv[0], "nodePtr_", &asyncContext->frameNodePtr);
            if (result == napi_ok) {
                napi_get_value_external(env, asyncContext->frameNodePtr, &asyncContext->nativePtr);
            }

            napi_typeof(env, asyncContext->onWillDismiss, &valueType);
            if (valueType == napi_function) {
                napi_create_reference(env, asyncContext->onWillDismiss, 1, &asyncContext->onWillDismissRef);
            }
            napi_typeof(env, asyncContext->onDidAppear, &valueType);
            if (valueType == napi_function) {
                napi_create_reference(env, asyncContext->onDidAppear, 1, &asyncContext->onDidAppearRef);
            }
            napi_typeof(env, asyncContext->onDidDisappear, &valueType);
            if (valueType == napi_function) {
                napi_create_reference(env, asyncContext->onDidDisappear, 1, &asyncContext->onDidDisappearRef);
            }
            napi_typeof(env, asyncContext->onWillAppear, &valueType);
            if (valueType == napi_function) {
                napi_create_reference(env, asyncContext->onWillAppear, 1, &asyncContext->onWillAppearRef);
            }
            napi_typeof(env, asyncContext->onWillDisappear, &valueType);
            if (valueType == napi_function) {
                napi_create_reference(env, asyncContext->onWillDisappear, 1, &asyncContext->onWillDisappearRef);
            }
        } else {
            DeleteContextAndThrowError(env, asyncContext, "The type of parameters is incorrect.");
            return false;
        }
    }
    return true;
}

void JSPromptThrowInterError(napi_env env, std::shared_ptr<PromptAsyncContext>& asyncContext, std::string& strMsg)
{
    napi_value code = nullptr;
    std::string strCode = std::to_string(ERROR_CODE_INTERNAL_ERROR);
    napi_create_string_utf8(env, strCode.c_str(), strCode.length(), &code);
    napi_value msg = nullptr;
    napi_create_string_utf8(env, strMsg.c_str(), strMsg.length(), &msg);
    napi_value error = nullptr;
    napi_create_error(env, code, msg, &error);

    if (asyncContext->deferred) {
        napi_reject_deferred(env, asyncContext->deferred, error);
    }
}

void UpdatePromptAlignment(DialogAlignment& alignment)
{
    bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
    if (alignment == DialogAlignment::TOP_START) {
        if (isRtl) {
            alignment = DialogAlignment::TOP_END;
        }
    } else if (alignment == DialogAlignment::TOP_END) {
        if (isRtl) {
            alignment = DialogAlignment::TOP_START;
        }
    } else if (alignment == DialogAlignment::CENTER_START) {
        if (isRtl) {
            alignment = DialogAlignment::CENTER_END;
        }
    } else if (alignment == DialogAlignment::CENTER_END) {
        if (isRtl) {
            alignment = DialogAlignment::CENTER_START;
        }
    } else if (alignment == DialogAlignment::BOTTOM_START) {
        if (isRtl) {
            alignment = DialogAlignment::BOTTOM_END;
        }
    } else if (alignment == DialogAlignment::BOTTOM_END) {
        if (isRtl) {
            alignment = DialogAlignment::BOTTOM_START;
        }
    }
}

std::optional<double> GetLevelOrderParam(napi_env env, const std::shared_ptr<PromptAsyncContext>& asyncContext)
{
    if (asyncContext->showInSubWindowBool) {
        return std::nullopt;
    }

    napi_value levelOrderApi = asyncContext->levelOrderApi;
    NG::LevelOrder* levelOrder = nullptr;
    if (levelOrderApi) {
        napi_unwrap(env, levelOrderApi, reinterpret_cast<void**>(&levelOrder));
    }

    if (levelOrder) {
        return std::make_optional(levelOrder->GetOrder());
    }
    return std::nullopt;
}

PromptDialogAttr GetDialogLifeCycleCallback(napi_env env, const std::shared_ptr<PromptAsyncContext>& asyncContext)
{
    auto onDidAppear = [env = asyncContext->env, onDidAppearRef = asyncContext->onDidAppearRef]() {
        if (onDidAppearRef) {
            napi_handle_scope scope = nullptr;
            napi_open_handle_scope(env, &scope);
            napi_value onDidAppearFunc = nullptr;
            napi_get_reference_value(env, onDidAppearRef, &onDidAppearFunc);
            napi_call_function(env, nullptr, onDidAppearFunc, 0, nullptr, nullptr);
            napi_delete_reference(env, onDidAppearRef);
            napi_close_handle_scope(env, scope);
        }
    };
    auto onDidDisappear = [env = asyncContext->env, onDidDisappearRef = asyncContext->onDidDisappearRef]() {
        if (onDidDisappearRef) {
            napi_handle_scope scope = nullptr;
            napi_open_handle_scope(env, &scope);
            napi_value onDidDisappearFunc = nullptr;
            napi_get_reference_value(env, onDidDisappearRef, &onDidDisappearFunc);
            napi_call_function(env, nullptr, onDidDisappearFunc, 0, nullptr, nullptr);
            napi_delete_reference(env, onDidDisappearRef);
            napi_close_handle_scope(env, scope);
        }
    };
    auto onWillAppear = [env = asyncContext->env, onWillAppearRef = asyncContext->onWillAppearRef]() {
        if (onWillAppearRef) {
            napi_handle_scope scope = nullptr;
            napi_open_handle_scope(env, &scope);
            napi_value onWillAppearFunc = nullptr;
            napi_get_reference_value(env, onWillAppearRef, &onWillAppearFunc);
            napi_call_function(env, nullptr, onWillAppearFunc, 0, nullptr, nullptr);
            napi_delete_reference(env, onWillAppearRef);
            napi_close_handle_scope(env, scope);
        }
    };
    auto onWillDisappear = [env = asyncContext->env, onWillDisappearRef = asyncContext->onWillDisappearRef]() {
        if (onWillDisappearRef) {
            napi_handle_scope scope = nullptr;
            napi_open_handle_scope(env, &scope);
            napi_value onWillDisappearFunc = nullptr;
            napi_get_reference_value(env, onWillDisappearRef, &onWillDisappearFunc);
            napi_call_function(env, nullptr, onWillDisappearFunc, 0, nullptr, nullptr);
            napi_delete_reference(env, onWillDisappearRef);
            napi_close_handle_scope(env, scope);
        }
    };
    PromptDialogAttr promptDialogAttr = {
        .onDidAppear =  std::move(onDidAppear),
        .onDidDisappear = std::move(onDidDisappear),
        .onWillAppear = std::move(onWillAppear),
        .onWillDisappear = std::move(onWillDisappear) };
    return promptDialogAttr;
}

napi_value JSPromptShowDialog(napi_env env, napi_callback_info info)
{
    TAG_LOGD(AceLogTag::ACE_DIALOG, "js prompt show dialog enter");
    size_t requireArgc = 1;
    size_t argc = 2;
    napi_value argv[3] = { 0 };
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, argv, &thisVar, &data);
    if (argc < requireArgc) {
        NapiThrow(
            env, "The number of parameters must be greater than or equal to 1.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }
    if (thisVar == nullptr) {
        return nullptr;
    }
    napi_valuetype valueTypeOfThis = napi_undefined;
    napi_typeof(env, thisVar, &valueTypeOfThis);
    if (valueTypeOfThis == napi_undefined) {
        return nullptr;
    }
    
    auto asyncContext = std::make_shared<PromptAsyncContext>();
    asyncContext->env = env;
    asyncContext->instanceId = Container::CurrentIdSafely();

    std::optional<DialogAlignment> alignment;
    std::optional<DimensionOffset> offset;
    std::optional<DimensionRect> maskRect;
    std::optional<Shadow> shadowProps;
    std::optional<Color> backgroundColor;
    std::optional<int32_t> backgroundBlurStyle;
    std::optional<BlurStyleOption> blurStyleOption;
    std::optional<EffectOption> effectOption;
    std::optional<HoverModeAreaType> hoverModeArea;
    std::optional<bool> enableHoverMode;
    LevelMode dialogLevelMode = LevelMode::OVERLAY;
    int32_t dialogLevelUniqueId = -1;
    ImmersiveMode dialogImmersiveMode = ImmersiveMode::DEFAULT;
    PromptDialogAttr lifeCycleAttr = {};
    for (size_t i = 0; i < argc; i++) {
        napi_valuetype valueType = napi_undefined;
        napi_typeof(env, argv[i], &valueType);
        if (i == 0) {
            if (valueType != napi_object) {
                DeleteContextAndThrowError(env, asyncContext, "The type of parameters is incorrect.");
                return nullptr;
            }
            napi_get_named_property(env, argv[0], "title", &asyncContext->titleNApi);
            napi_get_named_property(env, argv[0], "message", &asyncContext->messageNApi);
            napi_get_named_property(env, argv[0], "buttons", &asyncContext->buttonsNApi);
            napi_get_named_property(env, argv[0], "autoCancel", &asyncContext->autoCancel);
            napi_get_named_property(env, argv[0], "showInSubWindow", &asyncContext->showInSubWindow);
            napi_get_named_property(env, argv[0], "isModal", &asyncContext->isModal);
            napi_get_named_property(env, argv[0], "alignment", &asyncContext->alignmentApi);
            napi_get_named_property(env, argv[0], "offset", &asyncContext->offsetApi);
            napi_get_named_property(env, argv[0], "maskRect", &asyncContext->maskRectApi);
            napi_get_named_property(env, argv[0], "shadow", &asyncContext->shadowApi);
            napi_get_named_property(env, argv[0], "backgroundColor", &asyncContext->backgroundColorApi);
            napi_get_named_property(env, argv[0], "backgroundBlurStyle", &asyncContext->backgroundBlurStyleApi);
            napi_get_named_property(env, argv[0], "backgroundBlurStyleOptions", &asyncContext->blurStyleOptionApi);
            napi_get_named_property(env, argv[0], "backgroundEffect", &asyncContext->effectOptionApi);
            napi_get_named_property(env, argv[0], "enableHoverMode", &asyncContext->enableHoverMode);
            napi_get_named_property(env, argv[0], "hoverModeArea", &asyncContext->hoverModeAreaApi);
            napi_get_named_property(env, argv[0], "levelOrder", &asyncContext->levelOrderApi);
            napi_get_named_property(env, argv[0], "levelMode", &asyncContext->dialogLevelModeApi);
            napi_get_named_property(env, argv[0], "levelUniqueId", &asyncContext->dialogLevelUniqueId);
            napi_get_named_property(env, argv[0], "immersiveMode", &asyncContext->dialogImmersiveModeApi);
            napi_get_named_property(env, argv[0], "onDidAppear", &asyncContext->onDidAppear);
            napi_get_named_property(env, argv[0], "onDidDisappear", &asyncContext->onDidDisappear);
            napi_get_named_property(env, argv[0], "onWillAppear", &asyncContext->onWillAppear);
            napi_get_named_property(env, argv[0], "onWillDisappear", &asyncContext->onWillDisappear);
            GetNapiString(env, asyncContext->titleNApi, asyncContext->titleString, valueType);
            GetNapiString(env, asyncContext->messageNApi, asyncContext->messageString, valueType);
            GetNapiDialogProps(env, asyncContext, alignment, offset, maskRect);
            backgroundColor = GetColorProps(env, asyncContext->backgroundColorApi);
            shadowProps = GetShadowProps(env, asyncContext);
            GetNapiBlurStyleAndHoverModeProps(env, asyncContext, backgroundBlurStyle, hoverModeArea, enableHoverMode);
            GetBackgroundBlurStyleOption(env, asyncContext, blurStyleOption);
            GetBackgroundEffect(env, asyncContext, effectOption);
            if (!ParseButtonsPara(env, asyncContext, SHOW_DIALOG_BUTTON_NUM_MAX, false)) {
                return nullptr;
            }
            napi_typeof(env, asyncContext->autoCancel, &valueType);
            if (valueType == napi_boolean) {
                napi_get_value_bool(env, asyncContext->autoCancel, &asyncContext->autoCancelBool);
            }
            napi_typeof(env, asyncContext->showInSubWindow, &valueType);
            if (valueType == napi_boolean) {
                napi_get_value_bool(env, asyncContext->showInSubWindow, &asyncContext->showInSubWindowBool);
            }
            napi_typeof(env, asyncContext->isModal, &valueType);
            if (valueType == napi_boolean) {
                napi_get_value_bool(env, asyncContext->isModal, &asyncContext->isModalBool);
            }
            GetDialogLevelModeAndUniqueId(env, asyncContext, dialogLevelMode, dialogLevelUniqueId, dialogImmersiveMode);
            napi_typeof(env, asyncContext->onDidAppear, &valueType);
            if (valueType == napi_function) {
                napi_create_reference(env, asyncContext->onDidAppear, 1, &asyncContext->onDidAppearRef);
            }
            napi_typeof(env, asyncContext->onDidDisappear, &valueType);
            if (valueType == napi_function) {
                napi_create_reference(env, asyncContext->onDidDisappear, 1, &asyncContext->onDidDisappearRef);
            }
            napi_typeof(env, asyncContext->onWillAppear, &valueType);
            if (valueType == napi_function) {
                napi_create_reference(env, asyncContext->onWillAppear, 1, &asyncContext->onWillAppearRef);
            }
            napi_typeof(env, asyncContext->onWillDisappear, &valueType);
            if (valueType == napi_function) {
                napi_create_reference(env, asyncContext->onWillDisappear, 1, &asyncContext->onWillDisappearRef);
            }
            lifeCycleAttr = GetDialogLifeCycleCallback(env, asyncContext);
        } else if (valueType == napi_function) {
            napi_create_reference(env, argv[i], 1, &asyncContext->callbackRef);
        } else {
            DeleteContextAndThrowError(env, asyncContext, "The type of parameters is incorrect.");
            return nullptr;
        }
    }
    auto onLanguageChange = [shadowProps, alignment, offset, maskRect,
        updateAlignment = UpdatePromptAlignment](DialogProperties& dialogProps) {
        bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
        if (shadowProps.has_value()) {
            std::optional<Shadow> shadow = shadowProps.value();
            double offsetX = isRtl ? shadow->GetOffset().GetX() * (-1) : shadow->GetOffset().GetX();
            shadow->SetOffsetX(offsetX);
            dialogProps.shadow = shadow.value();
        }
        if (alignment.has_value()) {
            std::optional<DialogAlignment> pmAlign = alignment.value();
            updateAlignment(pmAlign.value());
            dialogProps.alignment = pmAlign.value();
        }
        if (offset.has_value()) {
            std::optional<DimensionOffset> pmOffset = offset.value();
            Dimension offsetX = isRtl ? pmOffset->GetX() * (-1) : pmOffset->GetX();
            pmOffset->SetX(offsetX);
            dialogProps.offset = pmOffset.value();
        }
        if (maskRect.has_value()) {
            std::optional<DimensionRect> pmMaskRect = maskRect.value();
            auto offset = pmMaskRect->GetOffset();
            Dimension offsetX = isRtl ? offset.GetX() * (-1) : offset.GetX();
            offset.SetX(offsetX);
            pmMaskRect->SetOffset(offset);
            dialogProps.maskRect = pmMaskRect.value();
        }
    };
    napi_value result = nullptr;
    if (asyncContext->callbackRef == nullptr) {
        napi_create_promise(env, &asyncContext->deferred, &result);
    } else {
        napi_get_undefined(env, &result);
    }
    asyncContext->callbacks.emplace("success");
    asyncContext->callbacks.emplace("cancel");

    auto callBack = [asyncContext](int32_t callbackType, int32_t successType) mutable {
        if (asyncContext == nullptr) {
            return;
        }

        asyncContext->callbackType = callbackType;
        asyncContext->successType = successType;
        auto container = AceEngine::Get().GetContainer(asyncContext->instanceId);
        if (!container) {
            return;
        }

        auto taskExecutor = container->GetTaskExecutor();
        if (!taskExecutor) {
            return;
        }
        taskExecutor->PostTask(
            [asyncContext]() {
                if (asyncContext == nullptr) {
                    return;
                }

                if (!asyncContext->valid) {
                    return;
                }

                napi_handle_scope scope = nullptr;
                napi_open_handle_scope(asyncContext->env, &scope);
                if (scope == nullptr) {
                    return;
                }

                napi_value ret;
                napi_value successIndex = nullptr;
                napi_create_int32(asyncContext->env, asyncContext->successType, &successIndex);
                napi_value indexObj = nullptr;
                napi_create_object(asyncContext->env, &indexObj);
                napi_set_named_property(asyncContext->env, indexObj, "index", successIndex);
                napi_value result[2] = { 0 };
                napi_create_object(asyncContext->env, &result[1]);
                napi_set_named_property(asyncContext->env, result[1], "index", successIndex);
                bool dialogResult = true;
                switch (asyncContext->callbackType) {
                    case 0:
                        napi_get_undefined(asyncContext->env, &result[0]);
                        dialogResult = true;
                        break;
                    case 1:
                        napi_value message = nullptr;
                        napi_create_string_utf8(asyncContext->env, "cancel", strlen("cancel"), &message);
                        napi_create_error(asyncContext->env, nullptr, message, &result[0]);
                        dialogResult = false;
                        break;
                }
                if (asyncContext->deferred) {
                    if (dialogResult) {
                        napi_resolve_deferred(asyncContext->env, asyncContext->deferred, result[1]);
                    } else {
                        napi_reject_deferred(asyncContext->env, asyncContext->deferred, result[0]);
                    }
                } else {
                    napi_value callback = nullptr;
                    napi_get_reference_value(asyncContext->env, asyncContext->callbackRef, &callback);
                    napi_call_function(
                        asyncContext->env, nullptr, callback, sizeof(result) / sizeof(result[0]), result, &ret);
                    napi_delete_reference(asyncContext->env, asyncContext->callbackRef);
                }
                napi_close_handle_scope(asyncContext->env, scope);
            },
            TaskExecutor::TaskType::JS, "ArkUIDialogParseDialogCallback");
        asyncContext = nullptr;
    };

    PromptDialogAttr promptDialogAttr = {
        .title = asyncContext->titleString,
        .message = asyncContext->messageString,
        .autoCancel = asyncContext->autoCancelBool,
        .showInSubWindow = asyncContext->showInSubWindowBool,
        .isModal = asyncContext->isModalBool,
        .enableHoverMode = enableHoverMode,
        .alignment = alignment,
        .offset = offset,
        .maskRect = maskRect,
        .backgroundColor = backgroundColor,
        .backgroundBlurStyle = backgroundBlurStyle,
        .blurStyleOption = blurStyleOption,
        .effectOption = effectOption,
        .shadow = shadowProps,
        .hoverModeArea = hoverModeArea,
        .onLanguageChange = onLanguageChange,
        .levelOrder = GetLevelOrderParam(asyncContext->env, asyncContext),
        .dialogLevelMode = dialogLevelMode,
        .dialogLevelUniqueId = dialogLevelUniqueId,
        .dialogImmersiveMode = dialogImmersiveMode,
        .onDidAppear = lifeCycleAttr.onDidAppear,
        .onDidDisappear = lifeCycleAttr.onDidDisappear,
        .onWillAppear = lifeCycleAttr.onWillAppear,
        .onWillDisappear = lifeCycleAttr.onWillDisappear,
    };

#ifdef OHOS_STANDARD_SYSTEM
    // NG
    if (SystemProperties::GetExtSurfaceEnabled() || !ContainerIsService()) {
        auto delegate = EngineHelper::GetCurrentDelegateSafely();
        if (delegate) {
            delegate->ShowDialog(promptDialogAttr, asyncContext->buttons, std::move(callBack), asyncContext->callbacks);
        } else {
            // throw internal error
            napi_value code = nullptr;
            std::string strCode = std::to_string(ERROR_CODE_INTERNAL_ERROR);
            napi_create_string_utf8(env, strCode.c_str(), strCode.length(), &code);
            napi_value msg = nullptr;
            std::string strMsg = ErrorToMessage(ERROR_CODE_INTERNAL_ERROR) + "Can not get delegate.";
            napi_create_string_utf8(env, strMsg.c_str(), strMsg.length(), &msg);
            napi_value error = nullptr;
            napi_create_error(env, code, msg, &error);

            if (asyncContext->deferred) {
                napi_reject_deferred(env, asyncContext->deferred, error);
            } else {
                napi_value ret1;
                napi_value callback = nullptr;
                napi_get_reference_value(env, asyncContext->callbackRef, &callback);
                napi_call_function(env, nullptr, callback, 1, &error, &ret1);
                napi_delete_reference(env, asyncContext->callbackRef);
            }
        }
    } else if (SubwindowManager::GetInstance() != nullptr) {
        SubwindowManager::GetInstance()->ShowDialog(
            promptDialogAttr, asyncContext->buttons, std::move(callBack), asyncContext->callbacks);
    }
#else
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (delegate) {
        delegate->ShowDialog(promptDialogAttr, asyncContext->buttons, std::move(callBack), asyncContext->callbacks);
    } else {
        // throw internal error
        napi_value code = nullptr;
        std::string strCode = std::to_string(ERROR_CODE_INTERNAL_ERROR);
        napi_create_string_utf8(env, strCode.c_str(), strCode.length(), &code);
        napi_value msg = nullptr;
        std::string strMsg = ErrorToMessage(ERROR_CODE_INTERNAL_ERROR) + "UI execution context not found.";
        napi_create_string_utf8(env, strMsg.c_str(), strMsg.length(), &msg);
        napi_value error = nullptr;
        napi_create_error(env, code, msg, &error);

        if (asyncContext->deferred) {
            napi_reject_deferred(env, asyncContext->deferred, error);
        } else {
            napi_value ret1;
            napi_value callback = nullptr;
            napi_get_reference_value(env, asyncContext->callbackRef, &callback);
            napi_call_function(env, nullptr, callback, 1, &error, &ret1);
            napi_delete_reference(env, asyncContext->callbackRef);
        }
    }
#endif
    return result;
}

void CreateActionMenuLifeCycleCallback(napi_env env, const std::shared_ptr<PromptAsyncContext>& asyncContext)
{
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, asyncContext->onDidAppear, &valueType);
    if (valueType == napi_function) {
        napi_create_reference(env, asyncContext->onDidAppear, 1, &asyncContext->onDidAppearRef);
    }
    napi_typeof(env, asyncContext->onDidDisappear, &valueType);
    if (valueType == napi_function) {
        napi_create_reference(env, asyncContext->onDidDisappear, 1, &asyncContext->onDidDisappearRef);
    }
    napi_typeof(env, asyncContext->onWillAppear, &valueType);
    if (valueType == napi_function) {
        napi_create_reference(env, asyncContext->onWillAppear, 1, &asyncContext->onWillAppearRef);
    }
    napi_typeof(env, asyncContext->onWillDisappear, &valueType);
    if (valueType == napi_function) {
        napi_create_reference(env, asyncContext->onWillDisappear, 1, &asyncContext->onWillDisappearRef);
    }
}

void GetActionMenuAppearLifeCycleCallback(napi_env env,
    const std::shared_ptr<PromptAsyncContext>& asyncContext, PromptDialogAttr& promptDialogAttr)
{
    auto onDidAppear = [env = asyncContext->env, onDidAppearRef = asyncContext->onDidAppearRef]() {
        if (onDidAppearRef) {
            napi_handle_scope scope = nullptr;
            napi_open_handle_scope(env, &scope);
            napi_value onDidAppearFunc = nullptr;
            napi_get_reference_value(env, onDidAppearRef, &onDidAppearFunc);
            napi_call_function(env, nullptr, onDidAppearFunc, 0, nullptr, nullptr);
            napi_delete_reference(env, onDidAppearRef);
            napi_close_handle_scope(env, scope);
        }
    };
    auto onWillAppear = [env = asyncContext->env, onWillAppearRef = asyncContext->onWillAppearRef]() {
        if (onWillAppearRef) {
            napi_handle_scope scope = nullptr;
            napi_open_handle_scope(env, &scope);
            napi_value onWillAppearFunc = nullptr;
            napi_get_reference_value(env, onWillAppearRef, &onWillAppearFunc);
            napi_call_function(env, nullptr, onWillAppearFunc, 0, nullptr, nullptr);
            napi_delete_reference(env, onWillAppearRef);
            napi_close_handle_scope(env, scope);
        }
    };
    promptDialogAttr.onDidAppear = std::move(onDidAppear);
    promptDialogAttr.onWillAppear = std::move(onWillAppear);
}

void GetActionMenuDisappearLifeCycleCallback(napi_env env,
    const std::shared_ptr<PromptAsyncContext>& asyncContext, PromptDialogAttr& promptDialogAttr)
{
    auto onDidDisappear = [env = asyncContext->env, onDidDisappearRef = asyncContext->onDidDisappearRef]() {
        if (onDidDisappearRef) {
            napi_handle_scope scope = nullptr;
            napi_open_handle_scope(env, &scope);
            napi_value onDidDisappearFunc = nullptr;
            napi_get_reference_value(env, onDidDisappearRef, &onDidDisappearFunc);
            napi_call_function(env, nullptr, onDidDisappearFunc, 0, nullptr, nullptr);
            napi_delete_reference(env, onDidDisappearRef);
            napi_close_handle_scope(env, scope);
        }
    };
    auto onWillDisappear = [env = asyncContext->env, onWillDisappearRef = asyncContext->onWillDisappearRef]() {
        if (onWillDisappearRef) {
            napi_handle_scope scope = nullptr;
            napi_open_handle_scope(env, &scope);
            napi_value onWillDisappearFunc = nullptr;
            napi_get_reference_value(env, onWillDisappearRef, &onWillDisappearFunc);
            napi_call_function(env, nullptr, onWillDisappearFunc, 0, nullptr, nullptr);
            napi_delete_reference(env, onWillDisappearRef);
            napi_close_handle_scope(env, scope);
        }
    };
    promptDialogAttr.onDidDisappear = std::move(onDidDisappear);
    promptDialogAttr.onWillDisappear = std::move(onWillDisappear);
}

napi_value JSPromptShowActionMenu(napi_env env, napi_callback_info info)
{
    TAG_LOGD(AceLogTag::ACE_DIALOG, "js prompt show action menu enter");
    size_t requireArgc = 1;
    size_t argc = 2;
    napi_value argv[3] = { 0 };
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, argv, &thisVar, &data);
    if (argc < requireArgc) {
        NapiThrow(
            env, "The number of parameters must be greater than or equal to 1.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }
    if (thisVar == nullptr) {
        return nullptr;
    }
    napi_valuetype valueTypeOfThis = napi_undefined;
    napi_typeof(env, thisVar, &valueTypeOfThis);
    if (valueTypeOfThis == napi_undefined) {
        return nullptr;
    }

    auto asyncContext = std::make_shared<PromptAsyncContext>();
    asyncContext->env = env;
    asyncContext->instanceId = Container::CurrentIdSafely();
    LevelMode dialogLevelMode = LevelMode::OVERLAY;
    int32_t dialogLevelUniqueId = -1;
    ImmersiveMode dialogImmersiveMode = ImmersiveMode::DEFAULT;

    PromptDialogAttr lifeCycleAttr;
    for (size_t i = 0; i < argc; i++) {
        napi_valuetype valueType = napi_undefined;
        napi_typeof(env, argv[i], &valueType);
        if (i == 0) {
            if (valueType != napi_object) {
                DeleteContextAndThrowError(env, asyncContext, "The type of parameters is incorrect.");
                return nullptr;
            }

            napi_get_named_property(env, argv[0], "onDidAppear", &asyncContext->onDidAppear);
            napi_get_named_property(env, argv[0], "onDidDisappear", &asyncContext->onDidDisappear);
            napi_get_named_property(env, argv[0], "onWillAppear", &asyncContext->onWillAppear);
            napi_get_named_property(env, argv[0], "onWillDisappear", &asyncContext->onWillDisappear);
            CreateActionMenuLifeCycleCallback(env, asyncContext);
            GetActionMenuAppearLifeCycleCallback(env, asyncContext, lifeCycleAttr);
            GetActionMenuDisappearLifeCycleCallback(env, asyncContext, lifeCycleAttr);
            napi_get_named_property(env, argv[0], "title", &asyncContext->titleNApi);
            napi_get_named_property(env, argv[0], "showInSubWindow", &asyncContext->showInSubWindow);
            napi_get_named_property(env, argv[0], "isModal", &asyncContext->isModal);
            napi_get_named_property(env, argv[0], "levelMode", &asyncContext->dialogLevelModeApi);
            napi_get_named_property(env, argv[0], "levelUniqueId", &asyncContext->dialogLevelUniqueId);
            napi_get_named_property(env, argv[0], "immersiveMode", &asyncContext->dialogImmersiveModeApi);
            GetNapiString(env, asyncContext->titleNApi, asyncContext->titleString, valueType);
            if (!HasProperty(env, argv[0], "buttons")) {
                DeleteContextAndThrowError(env, asyncContext, "Required input parameters are missing.");
                return nullptr;
            }
            napi_get_named_property(env, argv[0], "buttons", &asyncContext->buttonsNApi);
            if (!ParseButtonsPara(env, asyncContext, SHOW_ACTION_MENU_BUTTON_NUM_MAX, true)) {
                return nullptr;
            }
            napi_typeof(env, asyncContext->showInSubWindow, &valueType);
            if (valueType == napi_boolean) {
                napi_get_value_bool(env, asyncContext->showInSubWindow, &asyncContext->showInSubWindowBool);
            }
            napi_typeof(env, asyncContext->isModal, &valueType);
            if (valueType == napi_boolean) {
                napi_get_value_bool(env, asyncContext->isModal, &asyncContext->isModalBool);
            }
            GetDialogLevelModeAndUniqueId(env, asyncContext, dialogLevelMode, dialogLevelUniqueId, dialogImmersiveMode);
        } else if (valueType == napi_function) {
            napi_create_reference(env, argv[i], 1, &asyncContext->callbackRef);
        } else {
            DeleteContextAndThrowError(env, asyncContext, "The type of parameters is incorrect.");
            return nullptr;
        }
    }
    napi_value result = nullptr;
    if (asyncContext->callbackRef == nullptr) {
        napi_create_promise(env, &asyncContext->deferred, &result);
    } else {
        napi_get_undefined(env, &result);
    }

    auto callBack = [asyncContext](int32_t callbackType, int32_t successType) mutable {
        if (asyncContext == nullptr) {
            return;
        }

        asyncContext->callbackType = callbackType;
        asyncContext->successType = successType;
        auto container = AceEngine::Get().GetContainer(asyncContext->instanceId);
        if (!container) {
            return;
        }

        auto taskExecutor = container->GetTaskExecutor();
        if (!taskExecutor) {
            return;
        }
        taskExecutor->PostTask(
            [asyncContext]() {
                if (asyncContext == nullptr) {
                    return;
                }

                if (!asyncContext->valid) {
                    return;
                }

                napi_handle_scope scope = nullptr;
                napi_open_handle_scope(asyncContext->env, &scope);
                if (scope == nullptr) {
                    return;
                }

                napi_value ret;
                napi_value successIndex = nullptr;
                napi_create_int32(asyncContext->env, asyncContext->successType, &successIndex);
                asyncContext->callbackSuccessString = "showActionMenu:ok";
                napi_value indexObj = GetReturnObject(asyncContext->env, asyncContext->callbackSuccessString);
                napi_set_named_property(asyncContext->env, indexObj, "index", successIndex);
                napi_value result[2] = { 0 };
                napi_create_object(asyncContext->env, &result[1]);
                napi_set_named_property(asyncContext->env, result[1], "index", successIndex);
                bool dialogResult = true;
                switch (asyncContext->callbackType) {
                    case 0:
                        napi_get_undefined(asyncContext->env, &result[0]);
                        dialogResult = true;
                        break;
                    case 1:
                        napi_value message = nullptr;
                        napi_create_string_utf8(asyncContext->env, "cancel", strlen("cancel"), &message);
                        napi_create_error(asyncContext->env, nullptr, message, &result[0]);
                        dialogResult = false;
                        break;
                }
                if (asyncContext->deferred) {
                    if (dialogResult) {
                        napi_resolve_deferred(asyncContext->env, asyncContext->deferred, result[1]);
                    } else {
                        napi_reject_deferred(asyncContext->env, asyncContext->deferred, result[0]);
                    }
                } else {
                    napi_value callback = nullptr;
                    napi_get_reference_value(asyncContext->env, asyncContext->callbackRef, &callback);
                    napi_call_function(
                        asyncContext->env, nullptr, callback, sizeof(result) / sizeof(result[0]), result, &ret);
                    napi_delete_reference(asyncContext->env, asyncContext->callbackRef);
                }
                napi_close_handle_scope(asyncContext->env, scope);
            },
            TaskExecutor::TaskType::JS, "ArkUIDialogParseActionMenuCallback");
        asyncContext = nullptr;
    };

    DimensionRect rect;
    rect.SetOffset(DimensionOffset(CalcDimension(0, DimensionUnit::VP), CalcDimension(0, DimensionUnit::VP)));
    rect.SetSize(DimensionSize(CalcDimension(1, DimensionUnit::PERCENT), CalcDimension(1, DimensionUnit::PERCENT)));

    PromptDialogAttr promptDialogAttr = {
        .onDidAppear = std::move(lifeCycleAttr.onDidAppear),
        .onDidDisappear = std::move(lifeCycleAttr.onDidDisappear),
        .onWillAppear = std::move(lifeCycleAttr.onWillAppear),
        .onWillDisappear = std::move(lifeCycleAttr.onWillDisappear),
        .title = asyncContext->titleString,
        .showInSubWindow = asyncContext->showInSubWindowBool,
        .isModal = asyncContext->isModalBool,
        .maskRect = rect,
        .dialogLevelMode = dialogLevelMode,
        .dialogLevelUniqueId = dialogLevelUniqueId,
        .dialogImmersiveMode = dialogImmersiveMode,
    };
#ifdef OHOS_STANDARD_SYSTEM
    if (SystemProperties::GetExtSurfaceEnabled() || !ContainerIsService()) {
        auto delegate = EngineHelper::GetCurrentDelegateSafely();
        if (delegate) {
            delegate->ShowActionMenu(promptDialogAttr, asyncContext->buttons, std::move(callBack));
        } else {
            napi_value code = nullptr;
            std::string strCode = std::to_string(ERROR_CODE_INTERNAL_ERROR);
            napi_create_string_utf8(env, strCode.c_str(), strCode.length(), &code);
            napi_value msg = nullptr;
            std::string strMsg = ErrorToMessage(ERROR_CODE_INTERNAL_ERROR) + "Can not get delegate.";
            napi_create_string_utf8(env, strMsg.c_str(), strMsg.length(), &msg);
            napi_value error = nullptr;
            napi_create_error(env, code, msg, &error);

            if (asyncContext->deferred) {
                napi_reject_deferred(env, asyncContext->deferred, error);
            } else {
                napi_value ret1;
                napi_value callback = nullptr;
                napi_get_reference_value(env, asyncContext->callbackRef, &callback);
                napi_call_function(env, nullptr, callback, 1, &error, &ret1);
                napi_delete_reference(env, asyncContext->callbackRef);
            }
        }
    } else if (SubwindowManager::GetInstance() != nullptr) {
        SubwindowManager::GetInstance()->ShowActionMenu(
            asyncContext->titleString, asyncContext->buttons, std::move(callBack));
    }
#else
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (delegate) {
        delegate->ShowActionMenu(promptDialogAttr, asyncContext->buttons, std::move(callBack));
    } else {
        napi_value code = nullptr;
        std::string strCode = std::to_string(ERROR_CODE_INTERNAL_ERROR);
        napi_create_string_utf8(env, strCode.c_str(), strCode.length(), &code);
        napi_value msg = nullptr;
        std::string strMsg = ErrorToMessage(ERROR_CODE_INTERNAL_ERROR) + "UI execution context not found.";
        napi_create_string_utf8(env, strMsg.c_str(), strMsg.length(), &msg);
        napi_value error = nullptr;
        napi_create_error(env, code, msg, &error);

        if (asyncContext->deferred) {
            napi_reject_deferred(env, asyncContext->deferred, error);
        } else {
            napi_value ret1;
            napi_value callback = nullptr;
            napi_get_reference_value(env, asyncContext->callbackRef, &callback);
            napi_call_function(env, nullptr, callback, 1, &error, &ret1);
            napi_delete_reference(env, asyncContext->callbackRef);
        }
    }
#endif
    return result;
}

napi_value JSRemoveCustomDialog(napi_env env, napi_callback_info info)
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

void ParseDialogCallback(std::shared_ptr<PromptAsyncContext>& asyncContext,
    std::function<void(const int32_t& info, const int32_t& instanceId)>& onWillDismiss)
{
    onWillDismiss = [env = asyncContext->env, onWillDismissRef = asyncContext->onWillDismissRef]
        (const int32_t& info, const int32_t& instanceId) {
        if (onWillDismissRef) {
            napi_handle_scope scope = nullptr;
            napi_open_handle_scope(env, &scope);
            napi_value onWillDismissFunc = nullptr;
            napi_value value = nullptr;
            napi_value funcValue = nullptr;
            napi_value paramObj = nullptr;
            napi_create_object(env, &paramObj);

            napi_value id = nullptr;
            napi_create_int32(env, instanceId, &id);
            napi_create_function(env, "dismiss", strlen("dismiss"), JSRemoveCustomDialog, id, &funcValue);
            napi_set_named_property(env, paramObj, "dismiss", funcValue);

            napi_create_int32(env, info, &value);
            napi_set_named_property(env, paramObj, "reason", value);
            napi_get_reference_value(env, onWillDismissRef, &onWillDismissFunc);
            napi_call_function(env, nullptr, onWillDismissFunc, 1, &paramObj, nullptr);
            napi_close_handle_scope(env, scope);
        }
    };
}

void ParseBorderColorAndStyle(napi_env env, const std::shared_ptr<PromptAsyncContext>& asyncContext,
    std::optional<NG::BorderWidthProperty>& borderWidthProps, std::optional<NG::BorderColorProperty>& borderColorProps,
    std::optional<NG::BorderStyleProperty>& borderStyleProps)
{
    if (borderWidthProps.has_value()) {
        borderColorProps = GetBorderColorProps(env, asyncContext);
        if (!borderColorProps.has_value()) {
            NG::BorderColorProperty borderColor;
            borderColor.SetColor(Color::BLACK);
            borderColorProps = borderColor;
        }
        borderStyleProps = GetBorderStyleProps(env, asyncContext);
        if (!borderStyleProps.has_value()) {
            borderStyleProps = NG::BorderStyleProperty(
                { BorderStyle::SOLID, BorderStyle::SOLID, BorderStyle::SOLID, BorderStyle::SOLID });
        }
    }
}

RefPtr<NG::ChainedTransitionEffect> GetTransitionProps(
    napi_env env, const std::shared_ptr<PromptAsyncContext>& asyncContext)
{
    RefPtr<NG::ChainedTransitionEffect> transitionEffect = nullptr;
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (delegate) {
        napi_valuetype valueType = napi_undefined;
        napi_typeof(env, asyncContext->transitionApi, &valueType);
        if (valueType == napi_object) {
            transitionEffect = delegate->GetTransitionEffect(asyncContext->transitionApi);
        }
    }
    return transitionEffect;
}

RefPtr<NG::ChainedTransitionEffect> GetDialogTransitionProps(
    napi_env env, const std::shared_ptr<PromptAsyncContext>& asyncContext)
{
    RefPtr<NG::ChainedTransitionEffect> dialogTransitionEffect = nullptr;
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (delegate) {
        napi_valuetype valueType = napi_undefined;
        napi_typeof(env, asyncContext->dialogTransitionApi, &valueType);
        if (valueType == napi_object) {
            dialogTransitionEffect = delegate->GetTransitionEffect(asyncContext->dialogTransitionApi);
        }
    }
    return dialogTransitionEffect;
}

RefPtr<NG::ChainedTransitionEffect> GetMaskTransitionProps(
    napi_env env, const std::shared_ptr<PromptAsyncContext>& asyncContext)
{
    RefPtr<NG::ChainedTransitionEffect> maskTransitionEffect = nullptr;
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (delegate) {
        napi_valuetype valueType = napi_undefined;
        napi_typeof(env, asyncContext->maskTransitionApi, &valueType);
        if (valueType == napi_object) {
            maskTransitionEffect = delegate->GetTransitionEffect(asyncContext->maskTransitionApi);
        }
    }
    return maskTransitionEffect;
}

std::function<void()> GetCustomBuilder(napi_env env, const std::shared_ptr<PromptAsyncContext>& asyncContext)
{
    auto builder = [env = asyncContext->env, builderRef = asyncContext->builderRef]() {
        if (builderRef) {
            napi_value builderFunc = nullptr;
            napi_get_reference_value(env, builderRef, &builderFunc);
            napi_call_function(env, nullptr, builderFunc, 0, nullptr, nullptr);
            napi_delete_reference(env, builderRef);
        }
    };
    return builder;
}

std::function<void(const int32_t& dialogId)> GetCustomBuilderWithId(
    napi_env env, const std::shared_ptr<PromptAsyncContext>& asyncContext)
{
    auto builder = [env = asyncContext->env, builderRef = asyncContext->builderRef](const int32_t dialogId) {
        if (builderRef) {
            napi_value builderFunc = nullptr;
            napi_get_reference_value(env, builderRef, &builderFunc);
            napi_value dialogIdArg = nullptr;
            napi_create_int32(env, dialogId, &dialogIdArg);
            napi_call_function(env, nullptr, builderFunc, 1, &dialogIdArg, nullptr);
            napi_delete_reference(env, builderRef);
        }
    };
    return builder;
}

bool GetFocusableParam(napi_env env, const std::shared_ptr<PromptAsyncContext>& asyncContext)
{
    bool focusable = true;
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, asyncContext->focusableApi, &valueType);
    if (valueType != napi_boolean) {
        return focusable;
    }

    napi_get_value_bool(env, asyncContext->focusableApi, &focusable);
    return focusable;
}

PromptDialogAttr GetPromptActionDialog(napi_env env, const std::shared_ptr<PromptAsyncContext>& asyncContext,
    std::function<void(const int32_t& info, const int32_t& instanceId)> onWillDismiss)
{
    std::optional<DialogAlignment> alignment;
    std::optional<DimensionOffset> offset;
    std::optional<DimensionRect> maskRect;
    std::optional<int32_t> backgroundBlurStyle;
    std::optional<HoverModeAreaType> hoverModeArea;
    std::optional<BlurStyleOption> blurStyleOption;
    std::optional<EffectOption> effectOption;
    std::optional<bool> enableHoverMode;
    GetNapiDialogProps(env, asyncContext, alignment, offset, maskRect);
    GetNapiBlurStyleAndHoverModeProps(env, asyncContext, backgroundBlurStyle, hoverModeArea, enableHoverMode);
    GetBackgroundBlurStyleOption(env, asyncContext, blurStyleOption);
    GetBackgroundEffect(env, asyncContext, effectOption);
    auto borderWidthProps = GetBorderWidthProps(env, asyncContext);
    std::optional<NG::BorderColorProperty> borderColorProps;
    std::optional<NG::BorderStyleProperty> borderStyleProps;
    ParseBorderColorAndStyle(env, asyncContext, borderWidthProps, borderColorProps, borderStyleProps);
    auto backgroundColorProps = GetColorProps(env, asyncContext->backgroundColorApi);
    auto builder = GetCustomBuilder(env, asyncContext);
    auto* nodePtr = reinterpret_cast<OHOS::Ace::NG::UINode*>(asyncContext->nativePtr);
    auto maskColorProps = GetColorProps(env, asyncContext->maskColorApi);
    auto transitionEffectProps = GetTransitionProps(env, asyncContext);
    auto dialogTransitionEffectProps = GetDialogTransitionProps(env, asyncContext);
    auto maskTransitionEffectProps = GetMaskTransitionProps(env, asyncContext);
    PromptDialogAttr lifeCycleAttr = GetDialogLifeCycleCallback(env, asyncContext);
    int32_t mode = GetDialogKeyboardAvoidMode(env, asyncContext->keyboardAvoidModeApi);
    LevelMode dialogLevelMode = LevelMode::OVERLAY;
    int32_t dialogLevelUniqueId = -1;
    ImmersiveMode dialogImmersiveMode = ImmersiveMode::DEFAULT;
    GetDialogLevelModeAndUniqueId(env, asyncContext, dialogLevelMode, dialogLevelUniqueId, dialogImmersiveMode);
    PromptDialogAttr promptDialogAttr = { .autoCancel = asyncContext->autoCancelBool,
        .showInSubWindow = asyncContext->showInSubWindowBool,
        .isModal = asyncContext->isModalBool,
        .enableHoverMode = enableHoverMode,
        .customBuilder = std::move(builder),
        .customOnWillDismiss = std::move(onWillDismiss),
        .alignment = alignment,
        .offset = offset,
        .maskRect = maskRect,
        .backgroundColor = backgroundColorProps,
        .backgroundBlurStyle = backgroundBlurStyle,
        .blurStyleOption = blurStyleOption,
        .effectOption = effectOption,
        .borderWidth = borderWidthProps,
        .borderColor = borderColorProps,
        .borderStyle = borderStyleProps,
        .borderRadius = GetBorderRadiusProps(env, asyncContext),
        .shadow = GetShadowProps(env, asyncContext),
        .width = GetNapiDialogWidthProps(env, asyncContext),
        .height = GetNapiDialogHeightProps(env, asyncContext),
        .hoverModeArea = hoverModeArea,
        .contentNode = AceType::WeakClaim(nodePtr),
        .maskColor = maskColorProps,
        .transitionEffect = transitionEffectProps,
        .dialogTransitionEffect = dialogTransitionEffectProps,
        .maskTransitionEffect = maskTransitionEffectProps,
        .onDidAppear = lifeCycleAttr.onDidAppear,
        .onDidDisappear = lifeCycleAttr.onDidDisappear,
        .onWillAppear = lifeCycleAttr.onWillAppear,
        .onWillDisappear = lifeCycleAttr.onWillDisappear,
        .keyboardAvoidMode = KEYBOARD_AVOID_MODE[mode],
        .keyboardAvoidDistance = GetKeyboardAvoidDistanceProps(env, asyncContext),
        .levelOrder = GetLevelOrderParam(env, asyncContext),
        .focusable = GetFocusableParam(env, asyncContext),
        .dialogLevelMode = dialogLevelMode,
        .dialogLevelUniqueId = dialogLevelUniqueId,
        .dialogImmersiveMode = dialogImmersiveMode,
    };
    return promptDialogAttr;
}

std::string GetErrorMsg(int32_t errorCode)
{
    std::string strMsg;
    if (errorCode == ERROR_CODE_DIALOG_CONTENT_ERROR) {
        strMsg = ErrorToMessage(ERROR_CODE_DIALOG_CONTENT_ERROR) + "The ComponentContent is incorrect.";
    } else if (errorCode == ERROR_CODE_DIALOG_CONTENT_ALREADY_EXIST) {
        strMsg = ErrorToMessage(ERROR_CODE_DIALOG_CONTENT_ALREADY_EXIST) +
            "The ComponentContent has already been opened.";
    } else if (errorCode == ERROR_CODE_DIALOG_CONTENT_NOT_FOUND) {
        strMsg = ErrorToMessage(ERROR_CODE_DIALOG_CONTENT_NOT_FOUND) + "The ComponentContent cannot be found.";
    } else {
        strMsg = ErrorToMessage(ERROR_CODE_INTERNAL_ERROR) + "Build custom dialog failed.";
    }
    return strMsg;
}

std::string GetErrorCode(int32_t errorCode)
{
    std::string strCode;
    if (errorCode == ERROR_CODE_DIALOG_CONTENT_ERROR) {
        strCode = std::to_string(ERROR_CODE_DIALOG_CONTENT_ERROR);
    } else if (errorCode == ERROR_CODE_DIALOG_CONTENT_ALREADY_EXIST) {
        strCode = std::to_string(ERROR_CODE_DIALOG_CONTENT_ALREADY_EXIST);
    } else if (errorCode == ERROR_CODE_DIALOG_CONTENT_NOT_FOUND) {
        strCode = std::to_string(ERROR_CODE_DIALOG_CONTENT_NOT_FOUND);
    } else {
        strCode = std::to_string(ERROR_CODE_INTERNAL_ERROR);
    }
    return strCode;
}

void ParseCustomDialogContentCallback(std::shared_ptr<PromptAsyncContext>& asyncContext,
    std::function<void(int32_t)>& callBack)
{
    callBack = [asyncContext](int32_t errorCode) mutable {
        if (!asyncContext) {
            return;
        }
        auto container = AceEngine::Get().GetContainer(asyncContext->instanceId);
        if (!container) {
            return;
        }
        auto taskExecutor = container->GetTaskExecutor();
        if (!taskExecutor) {
            return;
        }
        taskExecutor->PostTask(
            [asyncContext, errorCode]() {
                if (asyncContext == nullptr || !asyncContext->valid) {
                    return;
                }
                napi_handle_scope scope = nullptr;
                napi_open_handle_scope(asyncContext->env, &scope);
                if (scope == nullptr) {
                    return;
                }
                if (!asyncContext->deferred) {
                    return;
                }
                if (errorCode == ERROR_CODE_NO_ERROR) {
                    napi_value result = nullptr;
                    napi_get_undefined(asyncContext->env, &result);
                    napi_resolve_deferred(asyncContext->env, asyncContext->deferred, result);
                } else {
                    std::string strMsg = GetErrorMsg(errorCode);
                    std::string strCode = GetErrorCode(errorCode);
                    napi_value code = nullptr;
                    napi_create_string_utf8(asyncContext->env, strCode.c_str(), strCode.length(), &code);
                    napi_value msg = nullptr;
                    napi_create_string_utf8(asyncContext->env, strMsg.c_str(), strMsg.length(), &msg);
                    napi_value error = nullptr;
                    napi_create_error(asyncContext->env, code, msg, &error);
                    napi_reject_deferred(asyncContext->env, asyncContext->deferred, error);
                }
                napi_close_handle_scope(asyncContext->env, scope);
            },
            TaskExecutor::TaskType::JS, "ArkUIDialogParseCustomDialogContentCallback");
        asyncContext = nullptr;
    };
}

void ParseCustomDialogIdCallback(std::shared_ptr<PromptAsyncContext>& asyncContext,
    std::function<void(int32_t)>& callBack)
{
    callBack = [asyncContext](int32_t dialogId) mutable {
        if (!asyncContext) {
            return;
        }
        auto container = AceEngine::Get().GetContainer(asyncContext->instanceId);
        if (!container) {
            return;
        }
        auto taskExecutor = container->GetTaskExecutor();
        if (!taskExecutor) {
            return;
        }
        taskExecutor->PostTask(
            [asyncContext, dialogId]() {
                if (asyncContext == nullptr || !asyncContext->valid) {
                    return;
                }

                napi_handle_scope scope = nullptr;
                napi_open_handle_scope(asyncContext->env, &scope);
                if (scope == nullptr) {
                    return;
                }

                napi_value ret = nullptr;
                if (!asyncContext->deferred) {
                    return;
                }
                if (dialogId > 0) {
                    napi_create_int32(asyncContext->env, dialogId, &ret);
                    napi_resolve_deferred(asyncContext->env, asyncContext->deferred, ret);
                } else {
                    std::string strMsg = GetErrorMsg(dialogId);
                    std::string strCode = GetErrorCode(dialogId);
                    napi_value code = nullptr;
                    napi_create_string_utf8(asyncContext->env, strCode.c_str(), strCode.length(), &code);
                    napi_value msg = nullptr;
                    napi_create_string_utf8(asyncContext->env, strMsg.c_str(), strMsg.length(), &msg);
                    napi_value error = nullptr;
                    napi_create_error(asyncContext->env, code, msg, &error);
                    napi_reject_deferred(asyncContext->env, asyncContext->deferred, error);
                }
                napi_close_handle_scope(asyncContext->env, scope);
            },
            TaskExecutor::TaskType::JS, "ArkUIDialogParseCustomDialogIdCallback");
        asyncContext = nullptr;
    };
}

void OpenCustomDialog(napi_env env, std::shared_ptr<PromptAsyncContext>& asyncContext,
    PromptDialogAttr& promptDialogAttr, std::function<void(int32_t)>& openCallback)
{
    promptDialogAttr.isUserCreatedDialog = true;
#ifdef OHOS_STANDARD_SYSTEM
    // NG
    if (SystemProperties::GetExtSurfaceEnabled() || !ContainerIsService()) {
        auto delegate = EngineHelper::GetCurrentDelegateSafely();
        if (delegate) {
            delegate->OpenCustomDialog(promptDialogAttr, std::move(openCallback));
        } else {
            // throw internal error
            std::string strMsg = ErrorToMessage(ERROR_CODE_INTERNAL_ERROR) + "Can not get delegate.";
            JSPromptThrowInterError(env, asyncContext, strMsg);
        }
    } else if (SubwindowManager::GetInstance() != nullptr) {
        SubwindowManager::GetInstance()->OpenCustomDialog(promptDialogAttr, std::move(openCallback));
    }
#else
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (delegate) {
        delegate->OpenCustomDialog(promptDialogAttr, std::move(openCallback));
    } else {
        // throw internal error
        std::string strMsg = ErrorToMessage(ERROR_CODE_INTERNAL_ERROR) + "UI execution context not found.";
        JSPromptThrowInterError(env, asyncContext, strMsg);
    }
#endif
}

napi_value JSPromptOpenCustomDialog(napi_env env, napi_callback_info info)
{
    TAG_LOGD(AceLogTag::ACE_DIALOG, "openCustomDialog enter");
    size_t argc = 2;
    napi_value argv[2] = { nullptr };
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    if (argc < 1) {
        NapiThrow(
            env, "The number of parameters must be greater than or equal to 1.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }

    auto asyncContext = std::make_shared<PromptAsyncContext>();
    asyncContext->env = env;
    asyncContext->instanceId = Container::CurrentIdSafely();
    bool parseOK = JSPromptParseParam(env, argc, argv, asyncContext);
    if (!parseOK) {
        return nullptr;
    }
    napi_value result = nullptr;
    napi_create_promise(env, &asyncContext->deferred, &result);

    std::function<void(const int32_t& info, const int32_t& instanceId)> onWillDismiss = nullptr;
    if (asyncContext->onWillDismissRef) {
        ParseDialogCallback(asyncContext, onWillDismiss);
    }
    std::function<void(int32_t)> openCallback = nullptr;
    PromptDialogAttr promptDialogAttr = GetPromptActionDialog(env, asyncContext, onWillDismiss);
    if (!asyncContext->builderRef) {
        ParseCustomDialogContentCallback(asyncContext, openCallback);
        promptDialogAttr.customStyle = true;
        promptDialogAttr.customBuilder = nullptr;
    } else {
        ParseCustomDialogIdCallback(asyncContext, openCallback);
    }

    OpenCustomDialog(env, asyncContext, promptDialogAttr, openCallback);

    return result;
}

void ParseBaseDialogOptionsEvent(napi_env env, napi_value arg, std::shared_ptr<PromptAsyncContext>& asyncContext)
{
    napi_get_named_property(env, arg, "onWillDismiss", &asyncContext->onWillDismiss);
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, asyncContext->onWillDismiss, &valueType);
    if (valueType == napi_function) {
        napi_create_reference(env, asyncContext->onWillDismiss, 1, &asyncContext->onWillDismissRef);
    }
    napi_get_named_property(env, arg, "onDidAppear", &asyncContext->onDidAppear);
    napi_typeof(env, asyncContext->onDidAppear, &valueType);
    if (valueType == napi_function) {
        napi_create_reference(env, asyncContext->onDidAppear, 1, &asyncContext->onDidAppearRef);
    }
    napi_get_named_property(env, arg, "onDidDisappear", &asyncContext->onDidDisappear);
    napi_typeof(env, asyncContext->onDidDisappear, &valueType);
    if (valueType == napi_function) {
        napi_create_reference(env, asyncContext->onDidDisappear, 1, &asyncContext->onDidDisappearRef);
    }
    napi_get_named_property(env, arg, "onWillAppear", &asyncContext->onWillAppear);
    napi_typeof(env, asyncContext->onWillAppear, &valueType);
    if (valueType == napi_function) {
        napi_create_reference(env, asyncContext->onWillAppear, 1, &asyncContext->onWillAppearRef);
    }
    napi_get_named_property(env, arg, "onWillDisappear", &asyncContext->onWillDisappear);
    napi_typeof(env, asyncContext->onWillDisappear, &valueType);
    if (valueType == napi_function) {
        napi_create_reference(env, asyncContext->onWillDisappear, 1, &asyncContext->onWillDisappearRef);
    }
}

void ParseBaseDialogOptions(napi_env env, napi_value arg, std::shared_ptr<PromptAsyncContext>& asyncContext)
{
    napi_get_named_property(env, arg, "maskRect", &asyncContext->maskRectApi);
    napi_get_named_property(env, arg, "alignment", &asyncContext->alignmentApi);
    napi_get_named_property(env, arg, "offset", &asyncContext->offsetApi);
    napi_get_named_property(env, arg, "showInSubWindow", &asyncContext->showInSubWindow);
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, asyncContext->showInSubWindow, &valueType);
    if (valueType == napi_boolean) {
        napi_get_value_bool(env, asyncContext->showInSubWindow, &asyncContext->showInSubWindowBool);
    }
    napi_get_named_property(env, arg, "isModal", &asyncContext->isModal);
    napi_typeof(env, asyncContext->isModal, &valueType);
    if (valueType == napi_boolean) {
        napi_get_value_bool(env, asyncContext->isModal, &asyncContext->isModalBool);
    }
    napi_get_named_property(env, arg, "autoCancel", &asyncContext->autoCancel);
    napi_typeof(env, asyncContext->autoCancel, &valueType);
    if (valueType == napi_boolean) {
        napi_get_value_bool(env, asyncContext->autoCancel, &asyncContext->autoCancelBool);
    }
    napi_get_named_property(env, arg, "transition", &asyncContext->transitionApi);
    napi_get_named_property(env, arg, "dialogTransition", &asyncContext->dialogTransitionApi);
    napi_get_named_property(env, arg, "maskTransition", &asyncContext->maskTransitionApi);
    napi_get_named_property(env, arg, "maskColor", &asyncContext->maskColorApi);
    napi_get_named_property(env, arg, "keyboardAvoidMode", &asyncContext->keyboardAvoidModeApi);
    napi_get_named_property(env, arg, "keyboardAvoidDistance", &asyncContext->keyboardAvoidDistanceApi);
    napi_get_named_property(env, arg, "enableHoverMode", &asyncContext->enableHoverMode);
    napi_get_named_property(env, arg, "hoverModeArea", &asyncContext->hoverModeAreaApi);
    napi_get_named_property(env, arg, "levelOrder", &asyncContext->levelOrderApi);
    napi_get_named_property(env, arg, "backgroundBlurStyleOptions", &asyncContext->blurStyleOptionApi);
    napi_get_named_property(env, arg, "backgroundEffect", &asyncContext->effectOptionApi);
    napi_get_named_property(env, arg, "levelMode", &asyncContext->dialogLevelModeApi);
    napi_get_named_property(env, arg, "levelUniqueId", &asyncContext->dialogLevelUniqueId);
    napi_get_named_property(env, arg, "immersiveMode", &asyncContext->dialogImmersiveModeApi);
    napi_get_named_property(env, arg, "focusable", &asyncContext->focusableApi);

    ParseBaseDialogOptionsEvent(env, arg, asyncContext);
}

std::function<void(RefPtr<NG::FrameNode> dialogNode)> GetDialogCallback(PromptDialogController* controller)
{
    auto builder = [controller](RefPtr<NG::FrameNode> dialogNode) {
        if (controller) {
            controller->SetNode(dialogNode);
        }
    };
    return builder;
}

napi_value JSPromptOpenCustomDialogWithController(napi_env env, napi_callback_info info)
{
    TAG_LOGD(AceLogTag::ACE_DIALOG, "openCustomDialogWithController enter");
    size_t argc = OPEN_CUSTOM_DIALOG_WITH_CONTROLLER_PARAM_TOTAL;
    napi_value argv[OPEN_CUSTOM_DIALOG_WITH_CONTROLLER_PARAM_TOTAL] = { nullptr };
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    if (argc < OPEN_CUSTOM_DIALOG_WITH_CONTROLLER_PARAM_MAND_COUNT
        || argc > OPEN_CUSTOM_DIALOG_WITH_CONTROLLER_PARAM_TOTAL) {
        NapiThrow(env, "The number of parameters must be between 2 and 3.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }

    for (size_t i = 0; i < argc; i++) {
        napi_valuetype valueType = napi_undefined;
        napi_typeof(env, argv[i], &valueType);
        if (valueType != napi_object) {
            NapiThrow(env, "The type of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
            return nullptr;
        }
    }

    auto asyncContext = std::make_shared<PromptAsyncContext>();
    asyncContext->env = env;
    asyncContext->instanceId = Container::CurrentIdSafely();
    auto nodeResult = napi_get_named_property(env, argv[0], "nodePtr_", &asyncContext->frameNodePtr);
    if (nodeResult != napi_ok) {
        NapiThrow(env, "The type of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }
    napi_get_value_external(env, asyncContext->frameNodePtr, &asyncContext->nativePtr);

    PromptDialogController* controller = nullptr;
    napi_unwrap(env, argv[OPEN_CUSTOM_DIALOG_WITH_CONTROLLER_PARAM_INDEX_CONTROLLER], (void**)&controller);
    if (!controller) {
        NapiThrow(env, "The type of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }

    if (argc > OPEN_CUSTOM_DIALOG_WITH_CONTROLLER_PARAM_INDEX_OPTIONS) {
        ParseBaseDialogOptions(env, argv[OPEN_CUSTOM_DIALOG_WITH_CONTROLLER_PARAM_INDEX_OPTIONS], asyncContext);
    }

    napi_value result = nullptr;
    napi_create_promise(env, &asyncContext->deferred, &result);

    std::function<void(const int32_t& info, const int32_t& instanceId)> onWillDismiss = nullptr;
    if (asyncContext->onWillDismissRef) {
        ParseDialogCallback(asyncContext, onWillDismiss);
    }

    PromptDialogAttr promptDialogAttr = GetPromptActionDialog(env, asyncContext, onWillDismiss);
    promptDialogAttr.customStyle = true;
    promptDialogAttr.customBuilder = nullptr;
    promptDialogAttr.dialogCallback = GetDialogCallback(controller);

    std::function<void(int32_t)> openCallback = nullptr;
    ParseCustomDialogContentCallback(asyncContext, openCallback);
    OpenCustomDialog(env, asyncContext, promptDialogAttr, openCallback);
    return result;
}

void ParseDialogOptions(napi_env env, napi_value arg, std::shared_ptr<PromptAsyncContext>& asyncContext)
{
    ParseBaseDialogOptions(env, arg, asyncContext);
    napi_get_named_property(env, arg, "backgroundColor", &asyncContext->backgroundColorApi);
    napi_get_named_property(env, arg, "cornerRadius", &asyncContext->borderRadiusApi);
    napi_get_named_property(env, arg, "width", &asyncContext->widthApi);
    napi_get_named_property(env, arg, "height", &asyncContext->heightApi);
    napi_get_named_property(env, arg, "borderWidth", &asyncContext->borderWidthApi);
    napi_get_named_property(env, arg, "borderColor", &asyncContext->borderColorApi);
    napi_get_named_property(env, arg, "borderStyle", &asyncContext->borderStyleApi);
    napi_get_named_property(env, arg, "shadow", &asyncContext->shadowApi);
    napi_get_named_property(env, arg, "backgroundBlurStyle", &asyncContext->backgroundBlurStyleApi);
}

napi_value JSPromptPresentCustomDialog(napi_env env, napi_callback_info info)
{
    TAG_LOGD(AceLogTag::ACE_DIALOG, "presentCustomDialog enter");
    size_t argc = PRESENT_CUSTOM_DIALOG_PARAM_TOTAL;
    napi_value argv[PRESENT_CUSTOM_DIALOG_PARAM_TOTAL] = { nullptr };
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    if (argc < PRESENT_CUSTOM_DIALOG_PARAM_MAND_COUNT || argc > PRESENT_CUSTOM_DIALOG_PARAM_TOTAL) {
        NapiThrow(env, "The number of parameters must be between 1 and 3.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }

    napi_valuetype paramTypes[PRESENT_CUSTOM_DIALOG_PARAM_TOTAL] = { napi_function, napi_object, napi_object };
    for (size_t i = 0; i < argc; i++) {
        napi_valuetype valueType = napi_undefined;
        napi_typeof(env, argv[i], &valueType);
        if (valueType != paramTypes[i]) {
            NapiThrow(env, "The type of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
            return nullptr;
        }
    }

    auto asyncContext = std::make_shared<PromptAsyncContext>();
    asyncContext->env = env;
    asyncContext->instanceId = Container::CurrentIdSafely();
    napi_create_reference(env, argv[0], 1, &asyncContext->builderRef);

    PromptDialogController* controller = nullptr;
    if (argc > PRESENT_CUSTOM_DIALOG_PARAM_INDEX_CONTROLLER) {
        napi_unwrap(env, argv[PRESENT_CUSTOM_DIALOG_PARAM_INDEX_CONTROLLER], (void**)&controller);
    }

    if (argc > PRESENT_CUSTOM_DIALOG_PARAM_INDEX_OPTIONS) {
        ParseDialogOptions(env, argv[PRESENT_CUSTOM_DIALOG_PARAM_INDEX_OPTIONS], asyncContext);
    }

    napi_value result = nullptr;
    napi_create_promise(env, &asyncContext->deferred, &result);

    std::function<void(const int32_t& info, const int32_t& instanceId)> onWillDismiss = nullptr;
    if (asyncContext->onWillDismissRef) {
        ParseDialogCallback(asyncContext, onWillDismiss);
    }

    PromptDialogAttr promptDialogAttr = GetPromptActionDialog(env, asyncContext, onWillDismiss);
    auto builder = GetCustomBuilderWithId(env, asyncContext);
    promptDialogAttr.customBuilderWithId = std::move(builder);
    if (controller) {
        promptDialogAttr.dialogCallback = GetDialogCallback(controller);
    }

    std::function<void(int32_t)> openCallback = nullptr;
    ParseCustomDialogIdCallback(asyncContext, openCallback);
    OpenCustomDialog(env, asyncContext, promptDialogAttr, openCallback);
    return result;
}

void CloseCustomDialog(napi_env env, std::shared_ptr<PromptAsyncContext>& asyncContext, bool useDialogId,
    int32_t dialogId, const WeakPtr<NG::UINode>& nodeWk, std::function<void(int32_t)>& contentCallback)
{
#ifdef OHOS_STANDARD_SYSTEM
    // NG
    if (SystemProperties::GetExtSurfaceEnabled() || !ContainerIsService()) {
        auto delegate = EngineHelper::GetCurrentDelegateSafely();
        if (delegate) {
            if (useDialogId) {
                delegate->CloseCustomDialog(dialogId);
            } else {
                delegate->CloseCustomDialog(nodeWk, std::move(contentCallback));
            }
        } else {
            // throw internal error
            napi_create_promise(env, &asyncContext->deferred, nullptr);
            std::string strMsg = ErrorToMessage(ERROR_CODE_INTERNAL_ERROR) + "Can not get delegate.";
            JSPromptThrowInterError(env, asyncContext, strMsg);
        }
    } else if (SubwindowManager::GetInstance() != nullptr) {
        if (useDialogId) {
            SubwindowManager::GetInstance()->CloseCustomDialogNG(dialogId);
        } else {
            SubwindowManager::GetInstance()->CloseCustomDialogNG(nodeWk, std::move(contentCallback));
        }
    }
#else
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (delegate) {
        if (useDialogId) {
            delegate->CloseCustomDialog(dialogId);
        } else {
            delegate->CloseCustomDialog(nodeWk, std::move(contentCallback));
        }
    } else {
        // throw internal error
        napi_create_promise(env, &asyncContext->deferred, nullptr);
        std::string strMsg = ErrorToMessage(ERROR_CODE_INTERNAL_ERROR) + "UI execution context not found.";
        JSPromptThrowInterError(env, asyncContext, strMsg);
    }
#endif
}

napi_value JSPromptCloseCustomDialog(napi_env env, napi_callback_info info)
{
    TAG_LOGD(AceLogTag::ACE_DIALOG, "closeCustomDialog enter");
    size_t argc = 1;
    napi_value argv[1] = { 0 };
    int32_t dialogId = -1;
    WeakPtr<NG::UINode> nodeWk;
    bool useDialogId = true;
    std::function<void(int32_t)> contentCallback = nullptr;
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    auto asyncContext = std::make_shared<PromptAsyncContext>();
    asyncContext->env = env;
    asyncContext->instanceId = Container::CurrentIdSafely();
    napi_value ret = nullptr;
    if (argc > 1) {
        NapiThrow(env, "The number of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    } else if (argc == 0) {
        dialogId = -1;
    } else {
        napi_valuetype valueType = napi_undefined;
        napi_typeof(env, argv[0], &valueType);
        if (valueType == napi_number) {
            napi_get_value_int32(env, argv[0], &dialogId);
        } else if (valueType == napi_object) {
            napi_value frameNodePtr = nullptr;
            auto result = napi_get_named_property(env, argv[0], "nodePtr_", &frameNodePtr);
            if (result != napi_ok) {
                NapiThrow(env, "The type of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
                return nullptr;
            }
            void* nativePtr = nullptr;
            result = napi_get_value_external(env, frameNodePtr, &nativePtr);
            if (result != napi_ok) {
                NapiThrow(env, "The type of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
                return nullptr;
            }
            auto* uiNodePtr = reinterpret_cast<OHOS::Ace::NG::UINode*>(nativePtr);
            nodeWk = AceType::WeakClaim(uiNodePtr);
            useDialogId = false;
            napi_create_promise(env, &asyncContext->deferred, &ret);
            ParseCustomDialogContentCallback(asyncContext, contentCallback);
        } else {
            NapiThrow(env, "The type of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
            return nullptr;
        }
    }

    CloseCustomDialog(env, asyncContext, useDialogId, dialogId, nodeWk, contentCallback);

    return ret;
}

void UpdateCustomDialog(napi_env env, std::shared_ptr<PromptAsyncContext>& asyncContext,
    PromptDialogAttr& promptDialogAttr, const WeakPtr<NG::UINode>& nodeWk,
    std::function<void(int32_t)>& contentCallback)
{
#ifdef OHOS_STANDARD_SYSTEM
    // NG
    if (SystemProperties::GetExtSurfaceEnabled() || !ContainerIsService()) {
        auto delegate = EngineHelper::GetCurrentDelegateSafely();
        if (delegate) {
            delegate->UpdateCustomDialog(nodeWk, promptDialogAttr, std::move(contentCallback));
        } else {
            // throw internal error
            napi_create_promise(env, &asyncContext->deferred, nullptr);
            std::string strMsg = ErrorToMessage(ERROR_CODE_INTERNAL_ERROR) + "Can not get delegate.";
            JSPromptThrowInterError(env, asyncContext, strMsg);
        }
    } else if (SubwindowManager::GetInstance() != nullptr) {
        SubwindowManager::GetInstance()->UpdateCustomDialogNG(nodeWk, promptDialogAttr, std::move(contentCallback));
    }
#else
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (delegate) {
        delegate->UpdateCustomDialog(nodeWk, promptDialogAttr, std::move(contentCallback));
    } else {
        // throw internal error
        napi_create_promise(env, &asyncContext->deferred, nullptr);
        std::string strMsg = ErrorToMessage(ERROR_CODE_INTERNAL_ERROR) + "UI execution context not found.";
        JSPromptThrowInterError(env, asyncContext, strMsg);
    }
#endif
}

napi_value JSPromptUpdateCustomDialog(napi_env env, napi_callback_info info)
{
    TAG_LOGD(AceLogTag::ACE_DIALOG, "updateCustomDialog enter");
    size_t argc = CUSTOM_DIALOG_PARAM_NUM;
    napi_value argv[CUSTOM_DIALOG_PARAM_NUM] = { nullptr };
    WeakPtr<NG::UINode> nodeWk;
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    if (argc != CUSTOM_DIALOG_PARAM_NUM) {
        NapiThrow(env, "The number of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }
    auto asyncContext = std::make_shared<PromptAsyncContext>();
    asyncContext->env = env;
    asyncContext->instanceId = Container::CurrentIdSafely();
    napi_value ret = nullptr;

    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, argv[0], &valueType);
    if (valueType == napi_object) {
        napi_value frameNodePtr = nullptr;
        auto result = napi_get_named_property(env, argv[0], "nodePtr_", &frameNodePtr);
        if (result != napi_ok) {
            NapiThrow(env, "The type of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
            return nullptr;
        }
        void* nativePtr = nullptr;
        result = napi_get_value_external(env, frameNodePtr, &nativePtr);
        if (result != napi_ok) {
            NapiThrow(env, "The type of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
            return nullptr;
        }
        auto* uiNodePtr = reinterpret_cast<OHOS::Ace::NG::UINode*>(nativePtr);
        nodeWk = AceType::WeakClaim(uiNodePtr);
    } else {
        NapiThrow(env, "The type of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }

    napi_typeof(env, argv[1], &valueType);
    if (valueType != napi_object) {
        NapiThrow(env, "The type of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }
    GetNapiNamedProperties(env, argv, 1, asyncContext);

    napi_create_promise(env, &asyncContext->deferred, &ret);
    std::function<void(int32_t)> contentCallback = nullptr;
    ParseCustomDialogContentCallback(asyncContext, contentCallback);
    PromptDialogAttr promptDialogAttr = GetPromptActionDialog(env, asyncContext, nullptr);

    UpdateCustomDialog(env, asyncContext, promptDialogAttr, nodeWk, contentCallback);

    return ret;
}

} // namespace OHOS::Ace::Napi
