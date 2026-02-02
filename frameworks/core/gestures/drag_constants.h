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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_DRAG_CONSTANTS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_DRAG_CONSTANTS_H

namespace OHOS::Ace {

enum class PreDragStatus {
    ACTION_DETECTING_STATUS = 0,
    READY_TO_TRIGGER_DRAG_ACTION,
    PREVIEW_LIFT_STARTED,
    PREVIEW_LIFT_FINISHED,
    PREVIEW_LANDING_STARTED,
    PREVIEW_LANDING_FINISHED,
    ACTION_CANCELED_BEFORE_DRAG,
    PREPARING_FOR_DRAG_DETECTION,
};

namespace NG {
enum class DragEventType {
    ENTER,
    LEAVE,
    MOVE,
    DROP,
    START,
    PULL_CANCEL,
};
}

} // namespace OHOS::Ace
#endif