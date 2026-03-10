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
namespace OHOS::Ace::NG {
const int32_t COMPATIBLE_INPUT_MODE = 1;
const int32_t DISABLE_TRANSFORM = 8;

bool EventInfoConvertor::ConvertMouseToTouchIfNeeded(const MouseInfo& mouseInfo, TouchEventInfo& touchEventInfo)
{
    if (mouseInfo.GetButton() != MouseButton::LEFT_BUTTON) {
        return false;
    }
    auto condition = EventInfoConvertor::MatchCompatibleCondition();
    if (!condition) {
        return false;
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
} // namespace OHOS::Ace::NG
