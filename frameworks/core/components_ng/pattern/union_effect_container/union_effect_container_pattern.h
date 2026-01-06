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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_UNION_EFFECT_CONTAINER_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_UNION_EFFECT_CONTAINER_PATTERN_H

#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/render/render_context.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT UnionEffectContainerPattern : public Pattern {
    DECLARE_ACE_TYPE(UnionEffectContainerPattern, Pattern);

public:
    UnionEffectContainerPattern() = default;
    ~UnionEffectContainerPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    bool IsSupportDrawModifier() const override
    {
        return false;
    }

    std::optional<RenderContext::ContextParam> GetContextParam() const override
    {
        return RenderContext::ContextParam { RenderContext::ContextType::UNION };
    }

    void SetSpacing(const float& spacing);

    float GetSpacing() const
    {
        return spacing_;
    }

private:
    float spacing_ { 0.0f };
    ACE_DISALLOW_COPY_AND_MOVE(UnionEffectContainerPattern);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_UNION_EFFECT_CONTAINER_PATTERN_H
