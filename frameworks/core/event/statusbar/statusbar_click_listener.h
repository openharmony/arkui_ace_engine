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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_STATUSBAR_CLICK_LISTENER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_STATUSBAR_CLICK_LISTENER_H

#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"

namespace OHOS::Ace {
/**
 * @brief an interface for statusbar click listeners. Listeners need to register to StatusBarEventProxy to receive
 * statusbar clicked.
 */
class StatusBarClickListener : public virtual AceType {
public:
    StatusBarClickListener() = default;
    ~StatusBarClickListener() override = default;

    /**
     * @brief This function is called when the statusbar clicked.
     *
     * Subclasses should override this function to perform specific actions when the statusbar clicked.
     */
    virtual void OnStatusBarClick() = 0;

    ACE_DISALLOW_COPY_AND_MOVE(StatusBarClickListener);
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_STATUSBAR_CLICK_LISTENER_H
