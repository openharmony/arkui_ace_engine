/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPLEMENTATION_GESTURE_TRIGGER_INFO_PEER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPLEMENTATION_GESTURE_TRIGGER_INFO_PEER_H

#include "core/gestures/gesture_event.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"

namespace OHOS::Ace::NG {

// Struct to bundle all gesture trigger information
// This is passed directly to the global gesture listener callbacks
// NOTE: This definition is duplicated in reverse_converter.h to avoid circular dependencies
// If you modify this struct, make sure to update reverse_converter.h as well
struct GestureTriggerInfo {
    GestureEvent event;                      // The gesture event information
    void* current;                           // GestureRecognizer pointer (opaque)
    int32_t currentPhase;                    // Current phase of the gesture
    RefPtr<NG::FrameNode> node;              // The frame node associated with the gesture
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPLEMENTATION_GESTURE_TRIGGER_INFO_PEER_H
