/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_PROXY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_PROXY_H

#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "core/gestures/gesture_info.h"

namespace OHOS::Ace::NG {
class FrameNode;

enum class DragEventType {
    ENTER,
    LEAVE,
    MOVE,
    DROP,
};

class ACE_EXPORT DragDropProxy : public virtual AceType {
    DECLARE_ACE_TYPE(DragDropProxy, AceType);

public:
    DragDropProxy() = default;
    ~DragDropProxy() override = default;

    void OnDragStart(const GestureEvent& info, const std::string& extraInfo);
    void OnDragMove(const GestureEvent& info);
    void OnDragEnd(const GestureEvent& info);
    void onDragCancel();
    void OnItemDragStart(const GestureEvent& info);
    void OnItemDragMove(const GestureEvent& info, int32_t draggedIndex);
    void OnItemDragEnd(const GestureEvent& info, int32_t draggedIndex);
    void onItemDragCancel();
    void DestroyDragWindow();

private:
    ACE_DISALLOW_COPY_AND_MOVE(DragDropProxy);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_PROXY_H
