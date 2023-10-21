/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_DRAG_STATUS_LISTENER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_DRAG_STATUS_LISTENER_H

#include "core/components_ng/event/drag_event.h"

namespace OHOS::Ace::NG {
class ListDragStatusListener : public DragStatusListener {
    DECLARE_ACE_TYPE(ListDragStatusListener, DragStatusListener);

public:
    ListDragStatusListener() = default;
    ~ListDragStatusListener() = default;
    void OnDragStarted(const RefPtr<NotifyDragEvent>& notifyDragEvent) override {};
    void OnDragEntered(const RefPtr<NotifyDragEvent>& notifyDragEvent) override {};
    void OnDragMoved(const RefPtr<NotifyDragEvent>& notifyDragEvent) override {};
    void OnDragLeaved(const RefPtr<NotifyDragEvent>& notifyDragEvent) override {};
    void OnDragEnded(const RefPtr<NotifyDragEvent>& notifyDragEvent) override {};
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_DRAG_STATUS_LISTENER_H
