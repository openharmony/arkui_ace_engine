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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PLATFORM_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PLATFORM_UTILS_H

#include "adapter/ohos/entrance/mmi_event_convertor.h"
#include "base/utils/macros.h"
#include "base/utils/utils.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT PlatformUtils {
public:
    PlatformUtils() {}
    ~PlatformUtils() {};
    static std::shared_ptr<MMI::PointerEvent> CopyPointerEventWithExtraProperty(
        const std::shared_ptr<MMI::PointerEvent>& pointerEvent, const AceLogTag aceLogTag);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PLATFORM_UTILS_H
