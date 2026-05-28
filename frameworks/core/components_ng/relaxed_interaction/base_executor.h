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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_BASE_EXECUTOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_BASE_EXECUTOR_H

#include <string>

#include "base/geometry/ng/point_t.h"
#include "base/memory/referenced.h"
#include "core/components_ng/relaxed_interaction/relaxed_interaction_types.h"

namespace OHOS::Ace::NG {

class PipelineContext;
class Component;
class Window;

class BaseExecutor {
public:
    explicit BaseExecutor(WeakPtr<PipelineContext> context) : context_(context) {}
    virtual ~BaseExecutor() = default;

    virtual ExecutorResult ExecuteStep() = 0;

    virtual std::string GetType() const = 0;

    virtual std::string GetDescription() const = 0;

    virtual bool IsSingleStep() const = 0;

protected:
    WeakPtr<PipelineContext> context_;

    Component* QueryComponentAt(float x, float y);
    Component* GetPrimaryActionTarget();
    Window* GetWindow();
    void* GetSmartGesture();
    PointF GetWindowCenter();
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_BASE_EXECUTOR_H
