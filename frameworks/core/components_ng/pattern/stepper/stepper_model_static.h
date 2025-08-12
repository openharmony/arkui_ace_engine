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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STEPPER_STEPPER_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STEPPER_STEPPER_MODEL_STATIC_H

#include "core/components/stepper/stepper_theme.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
using RoutineCallbackEvent = std::function<void()>;
using IndexCallbackEvent = std::function<void(int32_t, int32_t)>;
using IndexChangeEvent = std::function<void(int32_t)>;
class ACE_EXPORT StepperModelStatic {
public:
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetIndex(FrameNode* frameNode, const std::optional<int32_t>& index);
    static void SetOnFinish(FrameNode* frameNode, RoutineCallbackEvent&& eventOnFinish);
    static void SetOnSkip(FrameNode* frameNode, RoutineCallbackEvent&& eventOnSkip);
    static void SetOnChange(FrameNode* frameNode, IndexCallbackEvent&& eventOnChange);
    static void SetOnNext(FrameNode* frameNode, IndexCallbackEvent&& eventOnNext);
    static void SetOnPrevious(FrameNode* frameNode, IndexCallbackEvent&& eventOnPrevious);
    static void SetOnChangeEvent(FrameNode* frameNode, IndexChangeEvent&& onChangeEvent);

private:
    static RefPtr<FrameNode> CreateSwiperChild(int32_t id, uint32_t index);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STEPPER_STEPPER_MODEL_STATIC_H
