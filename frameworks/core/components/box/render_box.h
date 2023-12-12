/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "base/image/pixel_map.h"
#include "core/animation/animator.h"
#include "core/animation/keyframe_animation.h"
#include "core/components/box/box_component.h"
#include "core/components/box/render_box_base.h"
#include "core/components/common/properties/clip_path.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/decoration.h"
#include "core/components/image/render_image.h"
#include "core/gestures/click_recognizer.h"
#include "core/event/axis_event.h"
#include "core/gestures/raw_recognizer.h"
#include "base/window/drag_window.h"
#include "core/pipeline/base/constants.h"

namespace OHOS::Ace {

constexpr int32_t MAX_GESTURE_SIZE = 3;
constexpr int32_t DEFAULT_INDEX_VALUE = -1;

class ACE_EXPORT RenderBox : public RenderBoxBase, public DragDropEvent {
    DECLARE_ACE_TYPE(RenderBox, RenderBoxBase, DragDropEvent);

public:
    static RefPtr<RenderNode> Create();
    void Update(const RefPtr<Component>& component) override;
    void OnPaintFinish() override;

    void HandleAccessibilityFocusEvent(bool isAccessibilityFocus);

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

    void OnStatusStyleChanged(VisualState state) override;
    void UpdateStyleFromRenderNode(PropertyAnimatableType type) override;

    const Color& GetColor() const override
    {
        if (backDecoration_) {
            return backDecoration_->GetBackgroundColor();
        }
        return Color::TRANSPARENT;
    }

    TextDirection GetInspectorDirection() const
    {
        return inspectorDirection_;
    }

    RefPtr<Decoration> GetBackDecoration()
    {
        if (!backDecoration_) {
            backDecoration_ = AceType::MakeRefPtr<Decoration>();
        }
        return backDecoration_;
    }

    RefPtr<Decoration> GetFrontDecoration() const
    {
        return frontDecoration_;
    }

    virtual void NeedFocusBorder(bool needFocusBorder)
    {
        needFocusBorder_ = needFocusBorder;
        MarkNeedRender();
    }
    
    virtual void SetColor(const Color& color, bool isBackground) // add for animation
    {
        // create decoration automatically while user had not defined
        if (isBackground) {
            if (!backDecoration_) {
                backDecoration_ = AceType::MakeRefPtr<Decoration>();
            }
            backDecoration_->SetBackgroundColor(color);
        } else {
            if (!frontDecoration_) {
                frontDecoration_ = AceType::MakeRefPtr<Decoration>();
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

    void NeedMaterial(bool needMaterial)
    {
        needMaterial_ = needMaterial;
    }

    bool GetNeedMaterial() const
    {
        return needMaterial_;
    }
    void OnMouseHoverEnterAnimation() override;
    void OnMouseHoverExitAnimation() override;
    void StopMouseHoverAnimation() override;

    // add for animation
    virtual void SetBackgroundSize(const BackgroundImageSize& size);
    BackgroundImagePosition GetBackgroundPosition() const;
    virtual void SetBackgroundPosition(const BackgroundImagePosition& position);
    BackgroundImageSize GetBackgroundSize() const;
    virtual void SetShadow(const Shadow& shadow);
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
    virtual void SetBorderWidth(double width, const BorderEdgeHelper& helper);
    double GetBorderWidth(const BorderEdgeHelper& helper) const;
    virtual void SetBorderColor(const Color& color, const BorderEdgeHelper& helper);
    Color GetBorderColor(const BorderEdgeHelper& helper) const;
    virtual void SetBorderStyle(BorderStyle borderStyle, const BorderEdgeHelper& helper);
    BorderStyle GetBorderStyle(const BorderEdgeHelper& helper) const;
    virtual void SetBorderRadius(double radius, const BorderRadiusHelper& helper);
    double GetBorderRadius(const BorderRadiusHelper& helper) const;
    virtual void SetBlurRadius(const AnimatableDimension& radius);
    AnimatableDimension GetBlurRadius() const;
    virtual void SetBackdropRadius(const AnimatableDimension& radius);
    AnimatableDimension GetBackdropRadius() const;
    virtual void SetWindowBlurProgress(double progress);
    double GetWindowBlurProgress() const;
    void CreateFloatAnimation(RefPtr<KeyframeAnimation<float>>& floatAnimation, float beginValue, float endValue);

    Size GetBorderSize() const override;
    ColorPropertyAnimatable::SetterMap GetColorPropertySetterMap() override;
    ColorPropertyAnimatable::GetterMap GetColorPropertyGetterMap() override;
    Offset GetGlobalOffsetExternal() const override;
    void MouseHoverEnterTest() override;
    void MouseHoverExitTest() override;
    void AnimateMouseHoverEnter() override;
    void AnimateMouseHoverExit() override;
    bool HandleMouseEvent(const MouseEvent& event) override;
    void HandleMouseHoverEvent(MouseState mouseState) override;

    void OnTouchTestHit(
        const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result) override;

    void AddRecognizerToResult(
        const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result);

    const OnMouseCallback& GetOnMouseId() const
    {
        return onMouse_;
    }

    RefPtr<Gesture> GetOnLongPress() const
    {
        return onLongPressId_;
    }

    DragItemInfo GenerateDragItemInfo(const RefPtr<PipelineContext>& context, const GestureEvent& info) override;
    void AddDataToClipboard(const RefPtr<PipelineContext>& context, const std::string& extraInfo,
        const std::string& selectedText, const std::string& imageSrc) override;

    void ResetController(RefPtr<Animator>& controller);
    void CreateColorAnimation(
        RefPtr<KeyframeAnimation<Color>>& colorAnimation, const Color& beginValue, const Color& endValue);

protected:
    void ClearRenderObject() override;

    Offset GetBorderOffset() const override;
    Radius GetBorderRadius() const override;
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
    RefPtr<KeyframeAnimation<float>> scaleAnimationEnter_;
    RefPtr<KeyframeAnimation<float>> scaleAnimationExit_;
    Color hoverColorBegin_ = Color::TRANSPARENT;
    Color hoverColor_ = Color::TRANSPARENT;
    float scale_ = 1.0f;
    bool isZoom = false;
    bool isHoveredBoard_ = false;
    bool isHoveredScale_ = false;
    bool isAccessibilityFocus_ = false;
    bool needFocusBorder_ = false;
    bool needPaintDebugBoundary_ = false;

private:
    void UpdateBackDecoration(const RefPtr<Decoration>& newDecoration);
    void UpdateFrontDecoration(const RefPtr<Decoration>& newDecoration);
    void HandleRemoteMessage(const ClickInfo& clickInfo);
#if defined(PREVIEW)
    void CalculateScale(RefPtr<AccessibilityNode> node, Offset& globalOffset, Size& size);
    void CalculateRotate(RefPtr<AccessibilityNode> node, Offset& globalOffset, Size& size);
    void CalculateTranslate(RefPtr<AccessibilityNode> node, Offset& globalOffset, Size& size);
#endif
    void HandleTouchEvent(bool isTouchDown);

    void SetAccessibilityFocusImpl();
    void SetAccessibilityClickImpl();

    // 0 - low priority gesture, 1 - high priority gesture, 2 - parallel priority gesture
    std::array<RefPtr<GestureRecognizer>, MAX_GESTURE_SIZE> recognizers_;

    RefPtr<GestureRecognizer> onClick_;
    RefPtr<GestureRecognizer> onLongPress_;
    RefPtr<GestureRecognizer> parallelRecognizer_;
    RefPtr<RawRecognizer> touchRecognizer_;
    RefPtr<StateAttributes<BoxStateAttribute>> stateAttributeList_;
    OnHoverCallback onHover_;
    OnMouseCallback onMouse_;
    RefPtr<Gesture> onLongPressId_;
    TextDirection inspectorDirection_ { TextDirection::LTR };

    // Drag event
    void PanOnActionStart(const GestureEvent& info) override;
    void PanOnActionUpdate(const GestureEvent& info) override;
    void PanOnActionEnd(const GestureEvent& info) override;
    void PanOnActionCancel() override;
    void SetSelectedIndex(const GestureEvent& info);
    void SetInsertIndex(const RefPtr<DragDropEvent>& targetDragDropNode, const GestureEvent& info);
    OnTouchEventCallback onTouchUpId_;
    OnTouchEventCallback onTouchDownId_;
    OnTouchEventCallback onTouchMoveId_;
    size_t selectedIndex_ = DEFAULT_INDEX;
    int32_t insertIndex_ = DEFAULT_INDEX_VALUE;
    std::function<void(const std::shared_ptr<ClickInfo>&)> remoteMessageEvent_;
    bool enableDragStart_ = true;
    bool needMaterial_ = false;
}; // class RenderBox
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BOX_RENDER_BOX_H
