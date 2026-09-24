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
#include "frameworks/core/event/event_info_convertor.h"

#include "adapter/ohos/entrance/ace_application_info.h"
#include "core/common/transform/input_compatible_manager.h"
#include "adapter/ohos/entrance/event_compatible/compatible_interface.h"
#include "base/log/log_wrapper.h"
#include "base/utils/feature_manager.h"
#include "base/json/json_util.h"
#include "base/utils/system_properties.h"
namespace OHOS::Ace::NG {
const int32_t COMPATIBLE_INPUT_MODE = 1;
const int32_t DISABLE_TRANSFORM = 8;
const char MOUSE_2_TOUCH_EVENT_MODE[] = "mouse2TouchEventMode";
const char MOUSE_2_TOUCH_EVENT_MODE_XCOMPONENT_AND_WEB_ONLY[] = "xcomponentAndWebOnly";
const char CONTEXT_MENU_OPTIONS[] = "contextMenuOptions";
const char RIGHT_MOUSE_2_LONG_PRESS[] = "rightMouse2LongPress";
const char NEED_TRANSFER_COMPONENT[] = "needTransferComponent";

EventInfoConvertor::Mouse2TouchEventModeResult EventInfoConvertor::IsCompatibleFromFeatureManager(
    const std::string& matchedMode)
{
    std::string config;
    auto ret = FeatureManager::GetInstance().GetFeatureParam(MOUSE_2_TOUCH_EVENT_MODE, config);
    if (ret == FeatureManager::INIT_FAILED) {
        return Mouse2TouchEventModeResult::INIT_FAILED;
    }
    if (ret != FeatureManager::SUCCESS) {
        return Mouse2TouchEventModeResult::NOT_FOUND;
    }
    if (config == matchedMode) {
        return Mouse2TouchEventModeResult::MATCHED;
    }
    return Mouse2TouchEventModeResult::UNMATCHED;
}

bool EventInfoConvertor::ConvertMouseToTouchIfNeeded(const MouseInfo& mouseInfo, TouchEventInfo& touchEventInfo)
{
    if (mouseInfo.GetButton() != MouseButton::LEFT_BUTTON) {
        return false;
    }

    auto convertControllByFeatureManager =
        EventInfoConvertor::IsCompatibleFromFeatureManager(MOUSE_2_TOUCH_EVENT_MODE_XCOMPONENT_AND_WEB_ONLY);
    if (convertControllByFeatureManager == Mouse2TouchEventModeResult::UNMATCHED ||
        convertControllByFeatureManager == Mouse2TouchEventModeResult::NOT_FOUND) {
        return false;
    }
    if (convertControllByFeatureManager == Mouse2TouchEventModeResult::INIT_FAILED) {
        auto condition = EventInfoConvertor::MatchCompatibleCondition();
        if (!condition) {
            return false;
        }
    }

    TouchLocationInfo touchLocationInfo(0);
    switch (mouseInfo.GetAction()) {
        case MouseAction::PRESS:
            touchLocationInfo.SetTouchType(TouchType::DOWN);
            break;
        case MouseAction::RELEASE:
            touchLocationInfo.SetTouchType(TouchType::UP);
            break;
        case MouseAction::MOVE:
            touchLocationInfo.SetTouchType(TouchType::MOVE);
            break;
        case MouseAction::CANCEL:
            touchLocationInfo.SetTouchType(TouchType::CANCEL);
            break;
        default:
            TAG_LOGW(AceLogTag::ACE_XCOMPONENT, "mouse's action is not match, result is false");
            return false;
    }
    touchLocationInfo.SetLocalLocation(mouseInfo.GetLocalLocation());
    touchLocationInfo.SetScreenLocation(mouseInfo.GetScreenLocation());
    touchLocationInfo.SetTimeStamp(mouseInfo.GetTimeStamp());
    TouchLocationInfo changedTouchLoactionInfo = touchLocationInfo;
    touchEventInfo.AddChangedTouchLocationInfo(std::move(changedTouchLoactionInfo));
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    touchEventInfo.SetSourceDevice(SourceType::TOUCH);
    touchEventInfo.SetTimeStamp(mouseInfo.GetTimeStamp());
    return true;
}

bool EventInfoConvertor::IsTouchEventNeedAbandoned(const TouchEventInfo& touchEventInfo)
{
    if (touchEventInfo.GetSourceDevice() == SourceType::MOUSE) {
        return EventInfoConvertor::MatchCompatibleCondition();
    }
    return false;
}

bool EventInfoConvertor::MatchCompatibleCondition()
{
    auto compatiable = DelayedSingleton<CompatibleInterface>::GetInstance();
    if (compatiable == nullptr) {
        TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "fail to get compatiable instance.");
        return false;
    }
    return compatiable->MatchCompatibleCondition();
}

bool EventInfoConvertor::IfNeedMouseTransform()
{
    static bool enable = false;
    static CompatibleInfo info;
    static bool isAppDevelopedForPC = false;

    auto compatiable = DelayedSingleton<CompatibleInterface>::GetInstance();
    if (compatiable == nullptr) {
        TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "fail to get compatiable instance.");
        return false;
    }

    isAppDevelopedForPC = compatiable->IsAppDevelopedForPC();
    if (isAppDevelopedForPC) {
        enable = false;
        AceApplicationInfo::GetInstance().SetMouseTransformEnable(enable);
        TAG_LOGI(AceLogTag::ACE_XCOMPONENT,
            "IfNeedMouseTransform get result successfully \n "
            "isAppDevelopedForPC is %{public}d, result is %{public}d.",
            isAppDevelopedForPC, enable);
        return enable;
    }

    info = compatiable->MatchMouseTransformState();
    if (info.mode == DISABLE_TRANSFORM || info.inputMode == COMPATIBLE_INPUT_MODE || !info.mouseTransform) {
        enable = false;
    } else {
        enable = true;
    }
    AceApplicationInfo::GetInstance().SetMouseTransformEnable(enable);
    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGI(AceLogTag::ACE_XCOMPONENT,
            "IfNeedMouseTransform get result successfully \n "
            "mode is %{public}d, inputMode is %{public}d, mouseTransform is %{public}d \n"
            "isAppDevelopedForPC is %{public}d, result is %{public}d.",
            info.mode, info.inputMode, info.mouseTransform, isAppDevelopedForPC, enable);
    }
    return enable;
}

bool EventInfoConvertor::IsAppDevelopedForPC()
{
    static bool isAppDevelopedForPC = false;

    auto compatiable = DelayedSingleton<CompatibleInterface>::GetInstance();
    if (compatiable == nullptr) {
        TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "fail to get compatiable instance.");
        return false;
    }

    isAppDevelopedForPC = compatiable->IsAppDevelopedForPC();
    if (isAppDevelopedForPC) {
        TAG_LOGI(AceLogTag::ACE_XCOMPONENT,
            "IsAppDevelopedForPC get result successfully \n "
            "isAppDevelopedForPC is %{public}d.", isAppDevelopedForPC);
    }

    return isAppDevelopedForPC;
}

EventInfoConvertor::Mouse2TouchEventModeResult EventInfoConvertor::GetRightMouse2LongPressConfig(
    bool& outEnabled, std::vector<std::string>& outComponents)
{
    std::string config;
    auto ret = FeatureManager::GetInstance().GetFeatureParam(CONTEXT_MENU_OPTIONS, config);
    if (ret == FeatureManager::INIT_FAILED) {
        TAG_LOGW(AceLogTag::ACE_UIEVENT,
            "key contextMenuOptions, FeatureManager init failed");
        return Mouse2TouchEventModeResult::INIT_FAILED;
    }
    if (ret != FeatureManager::SUCCESS) {
        return Mouse2TouchEventModeResult::NOT_FOUND;
    }

    auto configJson = JsonUtil::ParseJsonString(config);
    if (!configJson || configJson->IsNull() || !configJson->IsObject()) {
        TAG_LOGE(AceLogTag::ACE_UIEVENT,
            "key contextMenuOptions, value is not valid json string: %{public}s", config.c_str());
        return Mouse2TouchEventModeResult::NOT_FOUND;
    }

    outEnabled = configJson->GetBool(RIGHT_MOUSE_2_LONG_PRESS, false);
    if (!outEnabled) {
        return Mouse2TouchEventModeResult::UNMATCHED;
    }

    auto componentsArray = configJson->GetValue(NEED_TRANSFER_COMPONENT);
    if (!componentsArray || componentsArray->IsNull() || componentsArray->GetArraySize() <= 0) {
        outEnabled = false;
        return Mouse2TouchEventModeResult::UNMATCHED;
    }
    for (int32_t i = 0; i < componentsArray->GetArraySize(); ++i) {
        auto item = componentsArray->GetArrayItem(i);
        if (item && !item->IsNull()) {
            std::string value = item->GetString();
            if (value == "All") {
                outComponents.clear();
                return Mouse2TouchEventModeResult::MATCHED;
            }
            outComponents.push_back(std::move(value));
        }
    }
    return Mouse2TouchEventModeResult::MATCHED;
}

bool EventInfoConvertor::IsRightMouseMappingEnabled(bool& outEnabled, std::vector<std::string>& outComponents)
{
    auto configResult = GetRightMouse2LongPressConfig(outEnabled, outComponents);
    return configResult == Mouse2TouchEventModeResult::MATCHED && outEnabled;
}

} // namespace OHOS::Ace::NG
