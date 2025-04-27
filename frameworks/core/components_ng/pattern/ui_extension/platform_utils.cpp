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

#include "platform_utils.h"

namespace OHOS::Ace::NG {
std::shared_ptr<MMI::PointerEvent> PlatformUtils::CopyPointerEventWithExtraProperty(
    const std::shared_ptr<MMI::PointerEvent>& pointerEvent, const AceLogTag aceLogTag)
{
    if (!pointerEvent) {
        TAG_LOGW(aceLogTag, "The PointerEvent is null");
        return nullptr;
    }
    std::shared_ptr<MMI::PointerEvent> newPointerEvent = std::make_shared<MMI::PointerEvent>(*pointerEvent);
    CHECK_NULL_RETURN(newPointerEvent, nullptr);

#ifdef OHOS_BUILD_ENABLE_SECURITY_COMPONENT
    newPointerEvent->SetEnhanceData(pointerEvent->GetEnhanceData());
#endif //OHOS_BUILD_ENABLE_SECURITY_COMPONENT
#ifdef OHOS_BUILD_ENABLE_ANCO
    newPointerEvent->SetAncoDeal(pointerEvent->GetAncoDeal());
#endif //OHOS_BUILD_ENABLE_ANCO

    newPointerEvent->SetHandlerEventType(pointerEvent->GetHandlerEventType());
    // Copy extra property
    std::shared_ptr<const uint8_t[]> raw;
    uint32_t length = 0;
    pointerEvent->GetExtraData(raw, length);
    if (length == 0 || !raw) {
        TAG_LOGW(aceLogTag, "The PointerEvent has no extra data.");
    } else {
        newPointerEvent->SetExtraData(raw, length);
    }
    newPointerEvent->SetSensorInputTime(pointerEvent->GetSensorInputTime());

    return newPointerEvent;
}
} // namespace OHOS::Ace::NG