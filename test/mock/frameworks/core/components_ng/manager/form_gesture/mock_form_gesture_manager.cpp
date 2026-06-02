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

#include "base/mousestyle/mouse_style.h"
#include "core/components_ng/manager/form_gesture/form_gesture_manager.h"

namespace OHOS::Ace::NG {
void FormGestureManager::LinkGesture(const AxisEvent& event, PipelineContext* pipeline, const RefPtr<FrameNode>& node,
    std::unordered_map<size_t, TouchTestResult>& axisTouchTestResults, SerializedGesture& etsSerializedGesture,
    RefPtr<EventManager>& eventManager)
{
    (void)event;
    (void)pipeline;
    (void)node;
    (void)axisTouchTestResults;
    (void)etsSerializedGesture;
    (void)eventManager;
}
} // namespace OHOS::Ace::NG
