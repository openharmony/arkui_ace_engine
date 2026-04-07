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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_FALLBACK_EXECUTOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_FALLBACK_EXECUTOR_H

#include <variant>

#include "core/components_ng/relaxed_interaction/base_executor.h"

namespace OHOS::Ace::NG {

class PipelineContext;

class FallbackExecutor : public BaseExecutor {
public:
    explicit FallbackExecutor(WeakPtr<PipelineContext> context, const std::string& identity, const std::string& body);
    explicit FallbackExecutor(WeakPtr<PipelineContext> context, const int32_t identity, const std::string& body);
    ~FallbackExecutor() override = default;

    ExecutorResult ExecuteStep() override;

    std::string GetType() const override
    {
        return FALLBACK;
    }

    std::string GetDescription() const override
    {
        return BaseExecutor::GetDescription();
    }
    
    bool IsSingleStep() const override
    {
        return true;
    }

private:
    std::variant<std::string, int32_t> identity_;
    std::string body_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_FALLBACK_EXECUTOR_H
