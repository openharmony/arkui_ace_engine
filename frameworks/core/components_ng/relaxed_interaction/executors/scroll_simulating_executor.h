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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_SCROLL_SIM_EXECUTOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_SCROLL_SIM_EXECUTOR_H

#include <queue>

#include "core/components_ng/relaxed_interaction/base_executor.h"
#include "core/event/touch_event.h"

namespace OHOS::Ace::NG {

class PipelineContext;

class ScrollSimulatingExecutor : public BaseExecutor {
public:
    class TouchEventBuilder {
    public:
        std::queue<TouchEvent> Build(const Coordinates& coordinates);

    private:
        void MoveBySteps(double x1, double y1, double x2, double y2);

        int32_t SumSteps(double x1, double y1, double x2, double y2, double speed);

    private:
        std::queue<TouchEvent> touchEvents_;
    };

    explicit ScrollSimulatingExecutor(WeakPtr<PipelineContext> context, const Command& cmd);
    ~ScrollSimulatingExecutor() override = default;

    ExecutorResult ExecuteStep() override;

    virtual std::string GetType() const override
    {
        return "scroll_simulating";
    }

    virtual std::string GetDescription() const override
    {
        return BaseExecutor::GetDescription();
    }

    virtual bool IsSingleStep() const override
    {
        return false;
    }

private:
    Command cmd_;

    std::queue<TouchEvent> touchEvents_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_SCROLL_SIM_EXECUTOR_H