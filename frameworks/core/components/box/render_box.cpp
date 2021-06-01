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

#include "core/components/box/render_box.h"

#include <algorithm>

#include "base/geometry/offset.h"
#include "base/log/event_report.h"
#include "base/utils/utils.h"
#include "core/components/box/box_component.h"
#include "core/components/text_field/render_text_field.h"

namespace OHOS::Ace {
namespace {

constexpr int32_t HOVER_ANIMATION_DURATION = 250;

}; // namespace

Size RenderBox::GetBorderSize() const
{
    auto context = GetContext().Upgrade();
    if (backDecoration_ && context) {
        return backDecoration_->GetBorder().GetLayoutSize(context->GetDipScale());
    }
    return Size(0.0, 0.0);
}

Offset RenderBox::GetBorderOffset() const
{
    auto context = GetContext().Upgrade();
    if (backDecoration_ && context) {
        return backDecoration_->GetBorder().GetOffset(context->GetDipScale());
    }
    return Offset(0.0, 0.0);
}

void RenderBox::Update(const RefPtr<Component>& component)
{
    const RefPtr<BoxComponent> box = AceType::DynamicCast<BoxComponent>(component);
    if (box) {
        RenderBoxBase::Update(component);
        // When declarative animation is active for this renderbox,
        // the animatbale properties are set by PropertyAnimatable::SetProperty.
        // And currently declarative api allow only animating
        // PROPERTY_BACK_DECORATION_COLOR
        if (!IsDeclarativeAnimationActive()) {
            backDecoration_ = box->GetBackDecoration();
        }
        frontDecoration_ = box->GetFrontDecoration();
        overflow_ = box->GetOverflow();
        animationType_ = box->GetMouseAnimationType();

        MarkNeedLayout();
    }
}

void RenderBox::OnPaintFinish()
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    auto viewScale = context->GetViewScale();
    if (NearZero(viewScale)) {
        LOGE("Get viewScale is zero.");
        EventReport::SendRenderException(RenderExcepType::VIEW_SCALE_ERR);
        return;
    }
    auto node = GetAccessibilityNode().Upgrade();
    if (!node) {
        return;
    }
    if (!node->GetVisible()) { // Set 0 to item when whole outside of view port.
        node->SetWidth(0.0);
        node->SetHeight(0.0);
        node->SetTop(0.0);
        node->SetLeft(0.0);
        return;
    }
    if (node->IsValidRect()) {
        return; // Rect already clamp by viewport, no need to set again.
    }

#if !defined(WINDOWS_PLATFORM) && !defined(MAC_PLATFORM)
    Size size = GetLayoutSize() * viewScale;
    Offset globalOffset = GetGlobalOffset() * viewScale;
#else
    Size size = paintSize_;
    Offset globalOffset = GetGlobalOffset();
    globalOffset.SetX(globalOffset.GetX() + margin_.LeftPx());
    globalOffset.SetY(globalOffset.GetY() + margin_.TopPx());
    if (node->IsAnimationNode()) {
        CalculateScale(node, globalOffset, size);
        CalculateRotate(node, globalOffset, size);
        CalculateTranslate(node, globalOffset, size);
    }
    size = size * viewScale;
    globalOffset = globalOffset * viewScale;
    node->SetWidth(size.Width());
    node->SetHeight(size.Height());
    node->SetLeft(globalOffset.GetX());
    node->SetTop(globalOffset.GetY());
    if (node->GetTag() == "inspectDialog") {
        auto parent = node->GetParentNode();
        parent->SetTop(node->GetTop());
        parent->SetLeft(node->GetLeft());
        parent->SetWidth(node->GetWidth());
        parent->SetHeight(node->GetHeight());
        auto mananger = context->GetAccessibilityManager();
        mananger->RemoveAccessibilityNodes(node);
    }
    return;
#endif
    node->SetWidth(size.Width());
    node->SetHeight(size.Height());
    node->SetLeft(globalOffset.GetX());
    node->SetTop(globalOffset.GetY());
}

#if defined(WINDOWS_PLATFORM) || defined(MAC_PLATFORM)
void RenderBox::CalculateScale(RefPtr<AccessibilityNode> node, Offset& globalOffset, Size& size)
{
    double scaleFactor = node->GetScale();
    Offset scaleCenter = node->GetScaleCenter();
    if (!NearEqual(scaleFactor, 1.0)) {
        if (NearEqual(scaleFactor, 0.0)) {
            scaleFactor = 0.01;
        }
        // parent and children are scaled by the center point of parent.
        auto currentOffset = globalOffset;
        auto currentSize = size;
        auto boxCenter = Offset(currentOffset.GetX() + currentSize.Width() / 2.0,
                                currentOffset.GetY() + currentSize.Height() / 2.0);
        if (boxCenter == scaleCenter) {
            globalOffset = Offset(currentSize.Width() * (1 - scaleFactor) / 2.0 + currentOffset.GetX(),
                                  currentSize.Height() * (1 - scaleFactor) / 2.0 + currentOffset.GetY());
        } else {
            auto center = scaleCenter;
            globalOffset = Offset(scaleFactor * currentOffset.GetX() + (1 - scaleFactor) * center.GetX(),
                                  scaleFactor * currentOffset.GetY() + (1 - scaleFactor) * center.GetY());
        }
        size = size * scaleFactor;
    }
}

void RenderBox::CalculateRotate(RefPtr<AccessibilityNode> node, Offset& globalOffset, Size& size)
{
    double angle = node->GetRotateAngle();
    if (!NearEqual(angle, 0.0)) {
        Point leftTop;
        Point rightTop;
        Point leftBottom;
        Point rightBottom;
        Point center = Point(node->GetScaleCenter().GetX(), node->GetScaleCenter().GetY());
        leftTop.SetX(globalOffset.GetX());
        leftTop.SetY(globalOffset.GetY());

        rightTop.SetX(globalOffset.GetX() + size.Width());
        rightTop.SetY(globalOffset.GetY());

        leftBottom.SetX(globalOffset.GetX());
        leftBottom.SetY(globalOffset.GetY() + size.Height());

        rightBottom.SetX(globalOffset.GetX() + size.Width());
        rightBottom.SetY(globalOffset.GetY() + size.Height());
        const double pi = std::acos(-1);
        double RotateAngle = angle * pi / 180;

        leftTop.Rotate(center, RotateAngle);
        rightTop.Rotate(center, RotateAngle);
        leftBottom.Rotate(center, RotateAngle);
        rightBottom.Rotate(center, RotateAngle);


        double min_X = std::min({leftTop.GetX(), rightTop.GetX(), leftBottom.GetX(), rightBottom.GetX()});
        double max_X = std::max({leftTop.GetX(), rightTop.GetX(), leftBottom.GetX(), rightBottom.GetX()});
        double min_Y = std::min({leftTop.GetY(), rightTop.GetY(), leftBottom.GetY(), rightBottom.GetY()});
        double max_Y = std::max({leftTop.GetY(), rightTop.GetY(), leftBottom.GetY(), rightBottom.GetY()});
        globalOffset.SetX(min_X);
        globalOffset.SetY(min_Y);
        size.SetWidth(max_X - min_X);
        size.SetHeight(max_Y - min_Y);
    }
}

void RenderBox::CalculateTranslate(RefPtr<AccessibilityNode> node, Offset& globalOffset, Size& size)
{
    // calculate translate
    Offset translateOffset = node->GetTranslateOffset();
    globalOffset = globalOffset + translateOffset;
}
#endif

void RenderBox::SetBackgroundPosition(const BackgroundImagePosition& position)
{
    RefPtr<BackgroundImage> backgroundImage = backDecoration_->GetImage();
    if (!backgroundImage) {
        // Suppress error logs when do animation.
        LOGD("set background position failed. no background image.");
        return;
    }
    if (backgroundImage->GetImagePosition() == position) {
        return;
    }
    backgroundImage->SetImagePosition(position);
    if (renderImage_) {
        renderImage_->SetBgImagePosition(backgroundImage->GetImagePosition());
    }
    MarkNeedLayout();
}

void RenderBox::ClearRenderObject()
{
    RenderBoxBase::ClearRenderObject();
    renderImage_ = nullptr;
    backDecoration_ = nullptr;
    frontDecoration_ = nullptr;
}

BackgroundImagePosition RenderBox::GetBackgroundPosition() const
{
    RefPtr<BackgroundImage> backgroundImage = backDecoration_->GetImage();
    if (!backgroundImage) {
        LOGE("get background position failed. no background image.");
        return BackgroundImagePosition();
    }
    return backgroundImage->GetImagePosition();
}

void RenderBox::OnMouseHoverEnterAnimation()
{
    // stop the exit animation being played.
    ResetController(controllerExit_);
    if (!controllerEnter_) {
        controllerEnter_ = AceType::MakeRefPtr<Animator>(context_);
    }
    colorAnimationEnter_ = AceType::MakeRefPtr<KeyframeAnimation<Color>>();
    colorAnimationEnter_->SetEvaluator(AceType::MakeRefPtr<ColorEvaluator>());
    if (animationType_ == HoverAnimationType::OPACITY) {
        if (!backDecoration_) {
            backDecoration_ = AceType::MakeRefPtr<Decoration>();
        }
        CreateColorAnimation(colorAnimationEnter_, hoverColor_, Color::FromRGBO(0, 0, 0, 0.05));
        colorAnimationEnter_->SetCurve(Curves::FRICTION);
    }
    controllerEnter_->AddInterpolator(colorAnimationEnter_);
    controllerEnter_->SetDuration(HOVER_ANIMATION_DURATION);
    controllerEnter_->Play();
    controllerEnter_->SetFillMode(FillMode::FORWARDS);
}

void RenderBox::OnMouseHoverExitAnimation()
{
    // stop the enter animation being played.
    ResetController(controllerEnter_);
    if (!controllerExit_) {
        controllerExit_ = AceType::MakeRefPtr<Animator>(context_);
    }
    colorAnimationExit_ = AceType::MakeRefPtr<KeyframeAnimation<Color>>();
    colorAnimationExit_->SetEvaluator(AceType::MakeRefPtr<ColorEvaluator>());
    if (animationType_ == HoverAnimationType::OPACITY) {
        if (!backDecoration_) {
            backDecoration_ = AceType::MakeRefPtr<Decoration>();
        }
        // The exit animation plays from the current background color.
        CreateColorAnimation(colorAnimationExit_, hoverColor_, Color::FromRGBO(0, 0, 0, 0.0));
        if (hoverColor_ == Color::FromRGBO(0, 0, 0, 0.05)) {
            colorAnimationExit_->SetCurve(Curves::FRICTION);
        } else {
            colorAnimationExit_->SetCurve(Curves::FAST_OUT_SLOW_IN);
        }
    }
    controllerExit_->AddInterpolator(colorAnimationExit_);
    controllerExit_->SetDuration(HOVER_ANIMATION_DURATION);
    controllerExit_->Play();
    controllerExit_->SetFillMode(FillMode::FORWARDS);
}

void RenderBox::CreateColorAnimation(
    RefPtr<KeyframeAnimation<Color>>& colorAnimation, const Color& beginValue, const Color& endValue)
{
    if (!colorAnimation) {
        return;
    }
    auto keyframeBegin = AceType::MakeRefPtr<Keyframe<Color>>(0.0, beginValue);
    auto keyframeEnd = AceType::MakeRefPtr<Keyframe<Color>>(1.0, endValue);
    colorAnimation->AddKeyframe(keyframeBegin);
    colorAnimation->AddKeyframe(keyframeEnd);
    WeakPtr<Decoration> weakDecoration = WeakPtr<Decoration>(backDecoration_);
    colorAnimation->AddListener([weakBox = AceType::WeakClaim(this), weakDecoration](const Color& value) {
        auto box = weakBox.Upgrade();
        if (!box) {
            return;
        }
        box->hoverColor_ = value;
        auto decoration = weakDecoration.Upgrade();
        if (decoration) {
            decoration->SetAnimationColor(box->hoverColor_);
        }
        box->MarkNeedRender();
    });
}

void RenderBox::ResetController(RefPtr<Animator>& controller)
{
    if (controller) {
        if (!controller->IsStopped()) {
            controller->Stop();
        }
        controller->ClearInterpolators();
    }
}

void RenderBox::StopMouseHoverAnimation()
{
    if (controllerExit_) {
        if (!controllerExit_->IsStopped()) {
            controllerExit_->Stop();
        }
        controllerExit_->ClearInterpolators();
    }
}

ColorPropertyAnimatable::SetterMap RenderBox::GetColorPropertySetterMap()
{
    ColorPropertyAnimatable::SetterMap map;
    auto weak = AceType::WeakClaim(this);
    const RefPtr<RenderTextField> renderTextField = AceType::DynamicCast<RenderTextField>(GetFirstChild());
    if (renderTextField) {
        WeakPtr<RenderTextField> textWeak = renderTextField;
        map[PropertyAnimatableType::PROPERTY_BACK_DECORATION_COLOR] = [textWeak](Color value) {
            auto renderTextField = textWeak.Upgrade();
            if (!renderTextField) {
                return;
            }
            renderTextField->SetColor(value);
        };
    } else {
        map[PropertyAnimatableType::PROPERTY_BACK_DECORATION_COLOR] = [weak](Color value) {
            auto box = weak.Upgrade();
            if (!box) {
                return;
            }
            box->SetColor(value, true);
        };
    }
    map[PropertyAnimatableType::PROPERTY_FRONT_DECORATION_COLOR] = [weak](Color value) {
        auto box = weak.Upgrade();
        if (!box) {
            return;
        }
        box->SetColor(value, false);
    };
    return map;
}

ColorPropertyAnimatable::GetterMap RenderBox::GetColorPropertyGetterMap()
{
    ColorPropertyAnimatable::GetterMap map;
    auto weak = AceType::WeakClaim(this);
    map[PropertyAnimatableType::PROPERTY_FRONT_DECORATION_COLOR] = [weak]() -> Color {
        auto box = weak.Upgrade();
        if (!box) {
            return Color();
        }
        auto frontDecoration = box->GetFrontDecoration();
        if (frontDecoration) {
            return frontDecoration->GetBackgroundColor();
        }
        return Color::TRANSPARENT;
    };
    const RefPtr<RenderTextField> renderTextField = AceType::DynamicCast<RenderTextField>(GetFirstChild());
    if (renderTextField) {
        WeakPtr<RenderTextField> textWeak = renderTextField;
        map[PropertyAnimatableType::PROPERTY_BACK_DECORATION_COLOR] = [textWeak]() -> Color {
            auto renderTextField = textWeak.Upgrade();
            if (!renderTextField) {
                return Color();
            }
            return renderTextField->GetColor();
        };
    } else {
        map[PropertyAnimatableType::PROPERTY_BACK_DECORATION_COLOR] = [weak]() -> Color {
            auto box = weak.Upgrade();
            if (!box) {
                return Color();
            }
            return box->GetColor();
        };
    }
    return map;
}

BackgroundPositionPropertyAnimatable::SetterMap RenderBox::GetBackgroundPositionPropertySetterMap()
{
    BackgroundPositionPropertyAnimatable::SetterMap map;
    auto weak = AceType::WeakClaim(this);
    map[PropertyAnimatableType::PROPERTY_BACKGROUND_POSITION] = [weak](BackgroundImagePosition position) {
        auto box = weak.Upgrade();
        if (!box) {
            LOGE("Set background position failed. box is null.");
            return;
        }
        return box->SetBackgroundPosition(position);
    };
    return map;
}

BackgroundPositionPropertyAnimatable::GetterMap RenderBox::GetBackgroundPositionPropertyGetterMap()
{
    BackgroundPositionPropertyAnimatable::GetterMap map;
    auto weak = AceType::WeakClaim(this);
    map[PropertyAnimatableType::PROPERTY_BACKGROUND_POSITION] = [weak]() -> BackgroundImagePosition {
        auto box = weak.Upgrade();
        if (!box) {
            LOGE("Get background position failed. box is null.");
            return BackgroundImagePosition();
        }
        return box->GetBackgroundPosition();
    };
    return map;
}

} // namespace OHOS::Ace
