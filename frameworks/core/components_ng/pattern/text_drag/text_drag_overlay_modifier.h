/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_DRAG_TEXT_DRAG_OVERLAY_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_DRAG_TEXT_DRAG_OVERLAY_MODIFIER_H

#include "base/memory/ace_type.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
constexpr int32_t TEXT_ANIMATION_DURATION = 300;
constexpr Dimension TEXT_DRAG_DEFAULT_OFFSET = 8.0_vp;
class TextDragOverlayModifier : public OverlayModifier {
    DECLARE_ACE_TYPE(TextDragOverlayModifier, OverlayModifier);

public:
    explicit TextDragOverlayModifier(const WeakPtr<OHOS::Ace::NG::Pattern>& pattern);
    ~TextDragOverlayModifier() override = default;

    virtual void StartFloatingAnimate()
    {
        isAnimating_ = true;
        backgroundOffset_->Set(0);
        AnimationOption option;
        option.SetDuration(TEXT_ANIMATION_DURATION);
        option.SetCurve(Curves::EASE_OUT);
        option.SetDelay(0);
        auto finishFuc = [weakModifier = WeakClaim(this)]() {
        auto modifier = weakModifier.Upgrade();
        CHECK_NULL_VOID(modifier);
        modifier->SetAnimateFlag(false);
        };
        option.SetOnFinishEvent(finishFuc);
        auto propertyCallback = [weakModifier = WeakClaim(this)]() {
            auto modifier = weakModifier.Upgrade();
            CHECK_NULL_VOID(modifier);
            modifier->SetBackgroundOffset(TEXT_DRAG_DEFAULT_OFFSET.ConvertToPx());
        };
        AnimationUtils::Animate(option, propertyCallback, option.GetOnFinishEvent());
    }

    virtual void StartFloatingCancelAnimate() {}

    bool IsHandlesShow()
    {
        return isHandlesShow_;
    }

    void UpdateHandlesShowFlag(bool isHandlesShow)
    {
        isHandlesShow_ = isHandlesShow;
    }

    void SetAnimateFlag(bool isAnimate)
    {
        isAnimating_ = isAnimate;
    }

    void onDraw(DrawingContext& context) override;
    void SetBackgroundOffset(float offset);
    void SetSelectedBackgroundOpacity(float opacity);

protected:
    WeakPtr<Pattern> pattern_;
    bool isAnimating_ = false;
    bool isHandlesShow_ = false;
    RefPtr<AnimatablePropertyFloat> backgroundOffset_;
    RefPtr<AnimatablePropertyFloat> selectedBackgroundOpacity_;

    ACE_DISALLOW_COPY_AND_MOVE(TextDragOverlayModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_DRAG_TEXT_DRAG_OVERLAY_MODIFIER_H
