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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_SPRING_LOADING_STATE_UPDATE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_SPRING_LOADING_STATE_UPDATE_H

#include "core/components_ng/manager/drag_drop/drag_drop_spring_loading/drag_drop_spring_loading_state_base.h"

namespace OHOS::Ace::NG {

class DragDropSpringLoadingStateUpdate : public DragDropSpringLoadingStateBase {
    DECLARE_ACE_TYPE(DragDropSpringLoadingStateUpdate, DragDropSpringLoadingStateBase);

public:
    DragDropSpringLoadingStateUpdate(const WeakPtr<DragDropSpringLoadingStateMachine>& machine)
        : DragDropSpringLoadingStateBase(machine) {};

    virtual ~DragDropSpringLoadingStateUpdate() = default;
    void OnEnter(std::string_view extraInfo) override;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_SPRING_LOADING_STATE_UPDATE_H