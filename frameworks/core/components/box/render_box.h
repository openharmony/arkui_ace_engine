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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BOX_RENDER_BOX_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BOX_RENDER_BOX_H

#include "core/animation/animator.h"
#include "core/animation/keyframe_animation.h"
#include "core/components/box/box_component.h"
#include "core/components/box/render_box_base.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/decoration.h"
#include "core/components/image/render_image.h"

namespace OHOS::Ace {

class RenderBox : public RenderBoxBase {
    DECLARE_ACE_TYPE(RenderBox, RenderBoxBase);

public:
    static RefPtr<RenderNode> Create();
    void Update(const RefPtr<Component>& component) override;
    void OnPaintFinish() override;

    const Color& GetColor() const override
    {
        if (backDecoration_) {
            return backDecoration_->GetBackgroundColor();
        }
        return Color::TRANSPARENT;
    }

    RefPtr<Decoration> GetBackDecoration() const
    {
        return backDecoration_;
    }

    RefPtr<Decoration> GetFrontDecoration() const
    {
        return frontDecoration_;
    }

    void SetColor(const Color& color, bool isBackground) // add for animation
    {
        // create decoration automatically while user had not defined
        if (isBackground) {
            if (!backDecoration_) {
                backDecoration_ = AceType::MakeRefPtr<Decoration>();
                LOGD("[BOX][Dep:%{public}d][LAYOUT]Add backDecoration automatically.", this->GetDepth());
            }
            backDecoration_->SetBackgroundColor(color);
        } else {
            if (!frontDecoration_) {
                frontDecoration_ = AceType::MakeRefPtr<Decoration>();
                LOGD("[BOX][Dep:%{public}d][LAYOUT]Add frontDecoration automatically.", this->GetDepth());
            }
            frontDecoration_->SetBackgroundColor(color);
        }
        MarkNeedRender();
    }

    void SetBackDecoration(const RefPtr<Decoration>& decoration) // add for list, do not use to update background image
    {
        backDecoration_ = decoration;
        MarkNeedRender();
    }

    void SetFrontDecoration(const RefPtr<Decoration>& decoration) // add for list
    {
        frontDecoration_ = decoration;
        MarkNeedRender();
    }

    void OnMouseHoverEnterAnimation() override;
    void OnMouseHoverExitAnimation() override;
    void StopMouseHoverAnimation() override;

    Size GetBorderSize() const override;
    ColorPropertyAnimatable::SetterMap GetColorPropertySetterMap() override;
    ColorPropertyAnimatable::GetterMap GetColorPropertyGetterMap() override;
    BackgroundPositionPropertyAnimatable::SetterMap GetBackgroundPositionPropertySetterMap() override;
    BackgroundPositionPropertyAnimatable::GetterMap GetBackgroundPositionPropertyGetterMap() override;

protected:
    void ClearRenderObject() override;

    Offset GetBorderOffset() const override;

    void SetBackgroundPosition(const BackgroundImagePosition& position);
    BackgroundImagePosition GetBackgroundPosition() const;

    RefPtr<Decoration> backDecoration_;
    RefPtr<Decoration> frontDecoration_;
    Overflow overflow_ = Overflow::OBSERVABLE;
    RefPtr<RenderImage> renderImage_;
    RefPtr<Animator> controllerEnter_;
    RefPtr<Animator> controllerExit_;
    RefPtr<KeyframeAnimation<Color>> colorAnimationEnter_;
    RefPtr<KeyframeAnimation<Color>> colorAnimationExit_;
    HoverAnimationType animationType_ = HoverAnimationType::NONE;
    Color hoverColor_ = Color::TRANSPARENT;

private:
    void ResetController(RefPtr<Animator>& controller);
    void CreateColorAnimation(RefPtr<KeyframeAnimation<Color>>& colorAnimation, const Color& beginValue,
        const Color& endValue);

#if defined(WINDOWS_PLATFORM) || defined(MAC_PLATFORM)
    void CalculateScale(RefPtr<AccessibilityNode> node, Offset& globalOffset, Size& size);
    void CalculateRotate(RefPtr<AccessibilityNode> node, Offset& globalOffset, Size& size);
    void CalculateTranslate(RefPtr<AccessibilityNode> node, Offset& globalOffset, Size& size);
#endif
}; // class RenderBox

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BOX_RENDER_BOX_H
