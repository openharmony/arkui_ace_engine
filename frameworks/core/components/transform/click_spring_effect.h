/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TRANSFORM_CLICK_SPRING_EFFECT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TRANSFORM_CLICK_SPRING_EFFECT_H

#include <functional>

#include "base/memory/ace_type.h"
#include "ui/event/event_constants.h"

namespace OHOS::Ace {

// Forward declarations
class Animator;
class RenderNode;
class PipelineContext;

enum class ClickSpringEffectType {
    NONE,
    SMALL,
    MEDIUM,
    LARGE
};

class ClickSpringEffect : public AceType {
    DECLARE_ACE_TYPE(ClickSpringEffect, AceType);

public:
    explicit ClickSpringEffect(const WeakPtr<PipelineContext>& context);
    virtual ~ClickSpringEffect() = default;

    void ShowAnimation(TouchType touchType, ClickSpringEffectType type);

    void MarkRender();

    void SetRenderNode(const WeakPtr<RenderNode>& renderNode);
    double GetScale() const;
    void SetScale(double scale);
    void SetController(const RefPtr<Animator>& controller);

private:
    void FinishPreviousAnimation();

    double scale_ { 1.0 };
    RefPtr<Animator> controller_;
    WeakPtr<RenderNode> renderNode_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TRANSFORM_CLICK_SPRING_EFFECT_H
