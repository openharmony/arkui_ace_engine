/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MODIFIERS_MODIFY_TASK_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MODIFIERS_MODIFY_TASK_H

#include <list>
#include <memory>

#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/modifier/modifier.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/render/render_property.h"

namespace OHOS::Ace::NG {
constexpr int VISUAL_STATE_COUNT = 4;

enum class VisualState {
    FOCUSED,
    PRESSED,
    DISABLED,
    HOVER,
};

class ModifyTask : public virtual Referenced {
public:
    ModifyTask() = default;
    ~ModifyTask() override = default;

    std::list<Modifier<LayoutProperty>>& GetLayoutTask()
    {
        return layoutTask_;
    }

    std::list<Modifier<RenderProperty>>& GetRenderTask()
    {
        return renderTask_;
    }

    std::list<Modifier<RenderContext>>& GetRenderContext()
    {
        return renderContext_;
    }

    const std::list<Modifier<LayoutProperty>>& GetLayoutTask() const
    {
        return layoutTask_;
    }

    const std::list<Modifier<RenderProperty>>& GetRenderTask() const
    {
        return renderTask_;
    }

    const std::list<Modifier<RenderContext>>& GetRenderContext() const
    {
        return renderContext_;
    }

    std::list<Modifier<RenderContext>> MoveRenderContext()
    {
        return std::move(renderContext_);
    }

private:
    std::list<Modifier<LayoutProperty>> layoutTask_;
    std::list<Modifier<RenderProperty>> renderTask_;
    std::list<Modifier<RenderContext>> renderContext_;
};

// ModifyTask are mainly used to save refresh tasks such as calculations, layout, renderings, and events
class StateModifyTask : public ModifyTask {
public:
    StateModifyTask() = default;
    ~StateModifyTask() override = default;

private:
    // stateTask is an array with every entry pointing to
    // vector of stateTask for one of the states.
    // array[0] -> vector of attributes for state "focused"
    // array[1] -> vector of attributes for state "pressed"
    // ...
    std::unique_ptr<std::array<ModifyTask, VISUAL_STATE_COUNT>> stateTask_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MODIFIERS_MODIFY_TASK_H