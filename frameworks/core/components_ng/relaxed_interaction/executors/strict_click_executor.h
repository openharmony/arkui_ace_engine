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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_STRICT_CLICK_EXECUTOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_STRICT_CLICK_EXECUTOR_H

#include <list>
#include <memory>

#include "base/geometry/ng/point_t.h"
#include "core/components_ng/relaxed_interaction/base_executor.h"

namespace OHOS::Ace::NG {

class PipelineContext;

class StrictClickExecutor : public BaseExecutor {
public:
    explicit StrictClickExecutor(WeakPtr<PipelineContext> context, const PointF& coordinates);
    ~StrictClickExecutor() override = default;

    ExecutorResult ExecuteStep() override;

    virtual std::string GetType() const override
    {
        return "strict_click";
    }

    virtual std::string GetDescription() const override
    {
        return BaseExecutor::GetDescription();
    }

    virtual bool IsSingleStep() const override
    {
        return true;
    }

private:
    PointF coordinates_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_STRICT_CLICK_EXECUTOR_H