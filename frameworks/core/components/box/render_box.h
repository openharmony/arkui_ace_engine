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
#include "core/components/common/properties/clip_path.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/decoration.h"
#include "core/components/image/render_image.h"
#include "base/image/pixel_map.h"

namespace OHOS::Ace {

constexpr int32_t MAX_GESTURE_SIZE = 3;

class ACE_EXPORT RenderBox : public RenderBoxBase {
    DECLARE_ACE_TYPE(RenderBox, RenderBoxBase);

public:
    static RefPtr<RenderNode> Create();
    void Update(const RefPtr<Component>& component) override;
    void OnPaintFinish() override;

    void OnAttachContext() override
    {
        RenderBoxBase::OnAttachContext();
        if (!backDecoration_) {
            backDecoration_ = AceType::MakeRefPtr<Decoration>();
        }
        backDecoration_->SetContextAndCallback(context_, [weak = WeakClaim(this)] {
            auto renderBox = weak.Upgrade();
            if (renderBox) {
                renderBox->OnAnimationCallback();
            }
        });
        if (!frontDecoration_) {
            frontDecoration_ = AceType::MakeRefPtr<Decoration>();
        }
        frontDecoration_->SetContextAndCallback(context_, [weak = WeakClaim(this)] {
            auto renderBox = weak.Upgrade();
            if (renderBox) {
                renderBox->OnAnimationCallback();
            }
        });
    }

    void UpdateStyleFromRenderNode(PropertyAnimatableType type) override;

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

    // add for animation
    void SetBackgroundSize(const BackgroundImageSize& size);
    BackgroundImagePosition GetBackgroundPosition() const;
    void SetBackgroundPosition(const BackgroundImagePosition& position);
    BackgroundImageSize GetBackgroundSize() const;
    void SetShadow(const Shadow& shadow);
    Shadow GetShadow() const;
    void SetGrayScale(double scale);
    double GetGrayScale(void) const;
    void SetBrightness(double ness);
    double GetBrightness(void) const;
    void SetContrast(double trast);
    double GetContrast(void) const;
    void SetColorBlend(const Color& color);
    Color GetColorBlend(void) const;
    void SetSaturate(double rate);
    double GetSaturate(void) const;
    void SetSepia(double pia);
    double GetSepia(void) const;
    void SetInvert(double invert);
    double GetInvert(void) const;
    void SetHueRotate(float deg);
    float GetHueRotate(void) const;
    void SetBorderWidth(double width, const BorderEdgeHelper& helper);
    double GetBorderWidth(const BorderEdgeHelper& helper) const;
    void SetBorderColor(const Color& color, const BorderEdgeHelper& helper);
    Color GetBorderColor(const BorderEdgeHelper& helper) const;
    void SetBorderStyle(BorderStyle borderStyle, const BorderEdgeHelper& helper);
    BorderStyle GetBorderStyle(const BorderEdgeHelper& helper) const;
    void SetBorderRadius(double radius, const BorderRadiusHelper& helper);
    double GetBorderRadius(const BorderRadiusHelper& helper) const;
    void SetBlurRadius(const AnimatableDimension& radius);
    AnimatableDimension GetBlurRadius() const;
    void SetBackdropRadius(const AnimatableDimension& radius);
    AnimatableDimension GetBackdropRadius() const;
    void SetWindowBlurProgress(double progress);
    double GetWindowBlurProgress() const;

    Size GetBorderSize() const override;
    ColorPropertyAnimatable::SetterMap GetColorPropertySetterMap() override;
    ColorPropertyAnimatable::GetterMap GetColorPropertyGetterMap() override;
    Offset GetGlobalOffsetExternal() const override;
    Offset GetGlobalOffset() const override;

    void OnTouchTestHit(
        const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result) override;

    const OnDragFunc& GetOnDragEnter() const
    {
        return onDragEnter_;
    }

    const OnDragFunc& GetOnDragMove() const
    {
        return onDragMove_;
    }

    const OnDragFunc& GetOnDragLeave() const
    {
        return onDragLeave_;
    }

    const OnDragFunc& GetOnDrop() const
    {
        return onDrop_;
    }

    RefPtr<RenderBox> FindTargetRenderBox(const RefPtr<PipelineContext> context, const GestureEvent& info);

    void AddRecognizerToResult(const Offset& coordinateOffset, const TouchRestrict& touchRestrict,
        TouchTestResult& result);

protected:
    void ClearRenderObject() override;

    Offset GetBorderOffset() const override;
    void UpdateGestureRecognizer(const std::array<RefPtr<Gesture>, MAX_GESTURE_SIZE>& gestures);
    bool ExistGestureRecognizer();

    // Remember clear all below members in ClearRenderObject().
    RefPtr<Decoration> backDecoration_;
    RefPtr<Decoration> frontDecoration_;
    RefPtr<RenderImage> renderImage_;
    RefPtr<Animator> controllerEnter_;
    RefPtr<Animator> controllerExit_;
    RefPtr<KeyframeAnimation<Color>> colorAnimationEnter_;
    RefPtr<KeyframeAnimation<Color>> colorAnimationExit_;
    HoverAnimationType animationType_ = HoverAnimationType::NONE;
    Color hoverColor_ = Color::TRANSPARENT;

private:
    void ResetController(RefPtr<Animator>& controller);
    void CreateColorAnimation(
        RefPtr<KeyframeAnimation<Color>>& colorAnimation, const Color& beginValue, const Color& endValue);
    void UpdateBackDecoration(const RefPtr<Decoration>& newDecoration);
    void UpdateFrontDecoration(const RefPtr<Decoration>& newDecoration);
    void CreateDragDropRecognizer();

#if defined(WINDOWS_PLATFORM) || defined(MAC_PLATFORM)
    void CalculateScale(RefPtr<AccessibilityNode> node, Offset& globalOffset, Size& size);
    void CalculateRotate(RefPtr<AccessibilityNode> node, Offset& globalOffset, Size& size);
    void CalculateTranslate(RefPtr<AccessibilityNode> node, Offset& globalOffset, Size& size);
#endif

    // 0 - low priority gesture, 1 - high priority gesture, 2 - parallel priority gesture
    std::array<RefPtr<GestureRecognizer>, MAX_GESTURE_SIZE> recognizers_;

    RefPtr<GestureRecognizer> dragDropGesture_;
    OnDragFunc onDrag_;
    OnDragFunc onDragEnter_;
    OnDragFunc onDragMove_;
    OnDragFunc onDragLeave_;
    OnDragFunc onDrop_;
    RefPtr<GestureRecognizer> onClick_;
}; // class RenderBox

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BOX_RENDER_BOX_H
