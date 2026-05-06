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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_SMART_GESTURE_EXECUTOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_SMART_GESTURE_EXECUTOR_H

#include "core/components_ng/manager/smart_gesture/smart_gesture_manager.h"
#include "core/components_ng/relaxed_interaction/base_executor.h"

namespace OHOS::Ace::NG {

class PipelineContext;

class SmartGestureExecutor : public BaseExecutor {
public:
    SmartGestureExecutor(WeakPtr<PipelineContext> context, SmartGestureTrigger trigger);
    ~SmartGestureExecutor() override = default;

    ExecutorResult ExecuteStep() override;

    std::string GetType() const override;

    std::string GetDescription() const override;

    bool IsSingleStep() const override;

private:
    SmartGestureTrigger trigger_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_SMART_GESTURE_EXECUTOR_H