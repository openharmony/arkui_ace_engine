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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_SPRING_LOADING_STATE_BASE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_SPRING_LOADING_STATE_BASE_H

#include <string_view>

#include "core/components_ng/base/frame_node.h"
#include "core/gestures/drag_event.h"

namespace OHOS::Ace::NG {
enum class DragDropSpringLoadingState : uint8_t {
    IDLE = 0,
    BEGIN = 1,
    UPDATE = 2,
    END = 3,
    CANCEL = 4,
};

const std::string DRAG_GROP_SPRING_LOADING_TASK_NAME("ArkUIDragDropSpringLoadingTimer");

class DragDropSpringLoadingStateMachine;
class DragDropSpringLoadingStateBase : public AceType {
    DECLARE_ACE_TYPE(DragDropSpringLoadingStateBase, AceType);

public:
    DragDropSpringLoadingStateBase(const WeakPtr<DragDropSpringLoadingStateMachine>& machine)
        : stateMachine_(machine) {};
    virtual ~DragDropSpringLoadingStateBase() = default;
    virtual void OnEnter(std::string_view extraInfo) {};

protected:
    RefPtr<DragDropSpringLoadingStateMachine> GetStateMachine()
    {
        return stateMachine_.Upgrade();
    }

    DragSpringLoadingState ConvertDragSpringLoadingState(DragDropSpringLoadingState state) const;

    void UpdateDragSpringLoadingContext(
        RefPtr<OHOS::Ace::DragSpringLoadingContext>& context, std::string_view extraInfo);

private:
    WeakPtr<DragDropSpringLoadingStateMachine> stateMachine_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_SPRING_LOADING_STATE_BASE_H