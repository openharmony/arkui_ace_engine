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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_MARQUEE_RENDER_MARQUEE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_MARQUEE_RENDER_MARQUEE_H

#include <functional>

#include "core/animation/animator.h"
#include "core/animation/curve_animation.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace {

class RenderMarquee : public RenderNode {
    DECLARE_ACE_TYPE(RenderMarquee, RenderNode);

public:
    static RefPtr<RenderNode> Create();
    void Update(const RefPtr<Component>& component) override;
    void PerformLayout() override;
    void OnHiddenChanged(bool hidden) override;
    void Start();
    void Stop();

protected:
    virtual TextDirection GetTextDirection(const std::string& text) const = 0;

private:
    void UpdateAnimation();
    void UpdateChildPosition(double position);
    void OnAnimationStart();
    void OnAnimationStop();

    RefPtr<RenderNode> childText_;
    RefPtr<Animator> controller_;
    RefPtr<CurveAnimation<double>> translate_;
    Offset childPosition_ = Offset::ErrorOffset();

    bool startAfterLayout_ = true;
    bool startAfterShowed_ = false;
    bool isHidden_ = false;
    double scrollAmount_ = 0.0;
    int32_t loop_ = ANIMATION_REPEAT_INFINITE;
    int32_t currentLoop_ = 0;
    MarqueeDirection direction_ = MarqueeDirection::LEFT;
    std::function<void()> bounceEvent_;
    std::function<void()> finishEvent_;
    std::function<void()> startEvent_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_MARQUEE_RENDER_MARQUEE_H
