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
#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/gestures/gesture_event.h"

namespace OHOS::Ace::NG {
class FrameNode;

enum class DragEventType {
    ENTER,
    LEAVE,
    MOVE,
    DROP,
    START,
};

enum class DragType {
    COMMON,
    GRID,
    LIST,
    TEXT,
};

class ACE_EXPORT DragDropProxy : public virtual AceType {
    DECLARE_ACE_TYPE(DragDropProxy, AceType);

public:
    explicit DragDropProxy(int64_t id) : id_(id) {}
    ~DragDropProxy() override = default;

    void OnTextDragStart(const std::string& extraInfo);
    void OnDragStart(const GestureEvent& info, const std::string& extraInfo, const RefPtr<FrameNode>& frameNode);
    void OnDragMove(const GestureEvent& info);
    void OnDragEnd(const GestureEvent& info, bool isTextDragEnd = false);
    void onDragCancel();
    void OnItemDragStart(const GestureEvent& info, const RefPtr<FrameNode>& frameNode);
    void OnItemDragMove(const GestureEvent& info, int32_t draggedIndex, DragType dragType);
    void OnItemDragEnd(const GestureEvent& info, int32_t draggedIndex, DragType dragType);
    void onItemDragCancel();
    void DestroyDragWindow();

private:
    int64_t id_ = -1;

    ACE_DISALLOW_COPY_AND_MOVE(DragDropProxy);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_PROXY_H
