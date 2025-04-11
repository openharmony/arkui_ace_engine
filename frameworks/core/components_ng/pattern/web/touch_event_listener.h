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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WEB_TOUCH_EVENT_LISTENER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WEB_TOUCH_EVENT_LISTENER_H

#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/web/itouch_event_callback.h"

namespace OHOS::Ace::NG {
class TouchEventListener : public ITouchEventCallback {
public:
    TouchEventListener();
    ~TouchEventListener() override;

    void SetPatternToListener(WeakPtr<NG::Pattern> pattern)
    {
        pattern_ = pattern;
    }

    WeakPtr<NG::Pattern> GetPatternFromListener() override;

    void OnTouchEvent() override;
private:
    WeakPtr<NG::Pattern> pattern_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WEB_TOUCH_EVENT_LISTENER_H