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
#include "core/animation/property_animatable_helper.h"
#include "core/components/box/box_component.h"
#include "core/components/box/box_component_helper.h"
#include "core/components/root/root_element.h"
#include "core/components/text_field/render_text_field.h"
#include "core/components_v2/inspector/inspector_composed_element.h"
#include "core/gestures/long_press_recognizer.h"
#include "core/gestures/pan_recognizer.h"
#include "core/gestures/sequenced_recognizer.h"

namespace OHOS::Ace {
namespace {

constexpr int32_t HOVER_ANIMATION_DURATION = 250;
constexpr int32_t DEFAULT_FINGERS = 1;
constexpr int32_t DEFAULT_DURATION = 150;
constexpr int32_t DEFAULT_DISTANCE = 0;

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
        boxComponent_ = box;
        inspectorDirection_ = box->GetInspectorDirection();
        RenderBoxBase::Update(component);
        UpdateBackDecoration(box->GetBackDecoration());
        UpdateFrontDecoration(box->GetFrontDecoration());
        animationType_ = box->GetMouseAnimationType();
        hoverAnimationType_ = animationType_;
        isZoom = animationType_ == HoverAnimationType::SCALE;
        MarkNeedLayout();

        responseRegion_ = box->GetResponseRegion();
        isResponseRegion_ = box->IsResponseRegion();

        auto tapGesture = box->GetOnClick();
        if (tapGesture) {
            onClick_ = tapGesture->CreateRecognizer(context_);
            onClick_->SetIsExternalGesture(true);
        }

        onDrag_ = box->GetOnDragId();
        onDragEnter_ = box->GetOnDragEnterId();
        onDragMove_ = box->GetOnDragMoveId();
        onDragLeave_ = box->GetOnDragLeaveId();
        onDrop_ = box->GetOnDropId();
        if (onDrag_) {
            CreateDragDropRecognizer();
        }

        if (!box->GetOnDomDragEnter().IsEmpty()) {
            onDomDragEnter_ = AceAsyncEvent<void(const DragUpdateInfo&)>::Create(box->GetOnDomDragEnter(), context_);
        }
        if (!box->GetOnDomDragOver().IsEmpty()) {
            onDomDragOver_ = AceAsyncEvent<void(const DragUpdateInfo&)>::Create(box->GetOnDomDragOver(), context_);
        }
        if (!box->GetOnDomDragLeave().IsEmpty()) {
            onDomDragLeave_ = AceAsyncEvent<void(const DragUpdateInfo&)>::Create(box->GetOnDomDragLeave(), context_);
        }
        if (!box->GetOnDomDragDrop().IsEmpty()) {
            onDomDragDrop_ = AceAsyncEvent<void(const DragEndInfo&)>::Create(box->GetOnDomDragDrop(), context_);
        }

        auto context = GetContext().Upgrade();
        if (onDrag_ || onDrop_) {
            context->InitDragListener();
        }

        auto gestures = box->GetGestures();
        UpdateGestureRecognizer(gestures);
        if (box->HasStateAttributeList()) {
            stateAttributeList_ = box->GetStateAttributeList();
        }
        OnStatusStyleChanged(disabled_ ? StyleState::DISABLED : StyleState::NORMAL);
        auto wp = AceType::WeakClaim(this);
        touchRecognizer_ = AceType::MakeRefPtr<RawRecognizer>();
        touchRecognizer_->SetOnTouchDown([wp](const TouchEventInfo&) {
            auto box = wp.Upgrade();
            if (box) {
                box->HandleTouchEvent(true);
            }
        });
        touchRecognizer_->SetOnTouchUp([wp](const TouchEventInfo&) {
            auto box = wp.Upgrade();
            if (box) {
                box->HandleTouchEvent(false);
            }
        });
    }
    // In each update, the extensions will be updated with new one.
    if (eventExtensions_ && eventExtensions_->HasOnAreaChangeExtension()) {
        auto inspector = inspector_.Upgrade();
        if (inspector) {
            auto area = inspector->GetCurrentRectAndOrigin();
            eventExtensions_->GetOnAreaChangeExtension()->SetBase(area.first, area.second);
        }
    }
}

void RenderBox::HandleTouchEvent(bool isTouchDown)
{
    if (isTouchDown) {
        OnStatusStyleChanged(StyleState::PRESSED);
    } else {
        OnStatusStyleChanged(StyleState::NORMAL);
    }
}

void RenderBox::CreateDragDropRecognizer()
{
    if (dragDropGesture_) {
        return;
    }

    auto context = GetContext();
    auto longPressRecognizer =
        AceType::MakeRefPtr<OHOS::Ace::LongPressRecognizer>(context, DEFAULT_DURATION, DEFAULT_FINGERS, false);
    PanDirection panDirection;
    auto panRecognizer =
        AceType::MakeRefPtr<OHOS::Ace::PanRecognizer>(context, DEFAULT_FINGERS, panDirection, DEFAULT_DISTANCE);
#if defined(WINDOWS_PLATFORM) || defined(MAC_PLATFORM)
    panRecognizer->SetOnActionStart([context, onDrag = onDrag_](const GestureEvent& info) {
        if (onDrag) {
            auto pipelineContext = context.Upgrade();
            RefPtr<DragEvent> event = AceType::MakeRefPtr<DragEvent>();
            RefPtr<PasteData> pasteData = AceType::MakeRefPtr<PasteData>();
            event->SetPasteData(pasteData);
            event->SetX(pipelineContext->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetX(), DimensionUnit::PX)));
            event->SetY(pipelineContext->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetY(), DimensionUnit::PX)));
            LOGW("[Engine Log] Unable to display drag events on the Previewer. Perform this operation on the "
                 "emulator or a real device instead.");
            onDrag(event);
        }
    });
    panRecognizer->SetOnActionUpdate(
        [weakRenderBox = AceType::WeakClaim<RenderBox>(this), context = context](const GestureEvent& info) {
            auto pipelineContext = context.Upgrade();
            RefPtr<DragEvent> event = AceType::MakeRefPtr<DragEvent>();
            RefPtr<PasteData> pasteData = AceType::MakeRefPtr<PasteData>();
            event->SetPasteData(pasteData);
            event->SetX(pipelineContext->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetX(), DimensionUnit::PX)));
            event->SetY(pipelineContext->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetY(), DimensionUnit::PX)));

            auto renderBox = weakRenderBox.Upgrade();
            if (!renderBox) {
                return;
            }
            auto targetRenderBox = renderBox->FindTargetRenderBox(context.Upgrade(), info);
            auto preTargetRenderBox = renderBox->GetPreTargetRenderBox();
            if (preTargetRenderBox == targetRenderBox) {
                if (targetRenderBox && targetRenderBox->GetOnDragMove()) {
                    (targetRenderBox->GetOnDragMove())(event);
                }
                return;
            }
            if (preTargetRenderBox && preTargetRenderBox->GetOnDragLeave()) {
                (preTargetRenderBox->GetOnDragLeave())(event);
            }
            if (targetRenderBox && targetRenderBox->GetOnDragEnter()) {
                (targetRenderBox->GetOnDragEnter())(event);
            }
            renderBox->SetPreTargetRenderBox(targetRenderBox);
        });
    panRecognizer->SetOnActionEnd(
        [weakRenderBox = AceType::WeakClaim<RenderBox>(this), context = context](const GestureEvent& info) {
            auto pipelineContext = context.Upgrade();
            RefPtr<DragEvent> event = AceType::MakeRefPtr<DragEvent>();
            RefPtr<PasteData> pasteData = AceType::MakeRefPtr<PasteData>();
            event->SetPasteData(pasteData);
            event->SetX(pipelineContext->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetX(), DimensionUnit::PX)));
            event->SetY(pipelineContext->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetY(), DimensionUnit::PX)));

            auto renderBox = weakRenderBox.Upgrade();
            if (!renderBox) {
                return;
            }
            ACE_DCHECK(renderBox->GetPreTargetRenderBox() == renderBox->FindTargetRenderBox(context.Upgrade(), info));
            auto targetRenderBox = renderBox->GetPreTargetRenderBox();
            if (!targetRenderBox) {
                return;
            }
            if (targetRenderBox->GetOnDrop()) {
                (targetRenderBox->GetOnDrop())(event);
            }
            renderBox->SetPreTargetRenderBox(nullptr);
        });
    panRecognizer->SetOnActionCancel([weakRenderBox = AceType::WeakClaim<RenderBox>(this)]() {
        auto renderBox = weakRenderBox.Upgrade();
        if (!renderBox) {
            return;
        }
        renderBox->SetPreTargetRenderBox(nullptr);
    });
#else
    panRecognizer->SetOnActionStart([context, onDrag = onDrag_](const GestureEvent& info) {
        if (onDrag) {
            auto pipelineContext = context.Upgrade();
            if (!pipelineContext) {
                LOGE("pipeline context is null!");
                return;
            }
            RefPtr<DragEvent> event = AceType::MakeRefPtr<DragEvent>();
            RefPtr<PasteData> pasteData = AceType::MakeRefPtr<PasteData>();
            event->SetPasteData(pasteData);
            event->SetX(pipelineContext->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetX(), DimensionUnit::PX)));
            event->SetY(pipelineContext->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetY(), DimensionUnit::PX)));
            onDrag(event);
            if (!event->GetPixmap()) {
                LOGE("pixmap is nullptr");
                return;
            }
            auto jsonResult = JsonUtil::Create(true);
            jsonResult->Put("description", event->GetDescription().c_str());
            jsonResult->Put("plainText", event->GetPasteData()->GetPlainText().c_str());
            jsonResult->Put("width", event->GetPixmap()->GetWidth());
            jsonResult->Put("height", event->GetPixmap()->GetHeight());
            pipelineContext->StartSystemDrag(jsonResult->ToString(), event->GetPixmap());
        }
    });
#endif

    std::vector<RefPtr<GestureRecognizer>> recognizers { longPressRecognizer, panRecognizer };
    dragDropGesture_ = AceType::MakeRefPtr<OHOS::Ace::SequencedRecognizer>(GetContext(), recognizers);
    dragDropGesture_->SetIsExternalGesture(true);
}

RefPtr<RenderBox> RenderBox::FindTargetRenderBox(const RefPtr<PipelineContext> context, const GestureEvent& info)
{
    if (!context) {
        return nullptr;
    }

    auto pageRenderNode = context->GetLastPageRender();
    if (!pageRenderNode) {
        return nullptr;
    }

    auto targetRenderNode = pageRenderNode->FindDropChild(info.GetGlobalPoint(), info.GetGlobalPoint());
    if (!targetRenderNode) {
        return nullptr;
    }
    return AceType::DynamicCast<RenderBox>(targetRenderNode);
}

void RenderBox::UpdateBackDecoration(const RefPtr<Decoration>& newDecoration)
{
    if (!newDecoration) {
        backDecoration_ = newDecoration;
        return;
    }

    if (!backDecoration_) {
        LOGD("backDecoration_ is null.");
        backDecoration_ = AceType::MakeRefPtr<Decoration>();
    }

    backDecoration_->SetAnimationColor(newDecoration->GetAnimationColor());
    backDecoration_->SetArcBackground(newDecoration->GetArcBackground());
    backDecoration_->SetBlurRadius(newDecoration->GetBlurRadius());
    backDecoration_->SetBorder(newDecoration->GetBorder());
    backDecoration_->SetGradient(newDecoration->GetGradient(), context_, [weak = WeakClaim(this)] {
        auto renderBox = weak.Upgrade();
        if (renderBox) {
            renderBox->OnAnimationCallback();
        }
    });
    backDecoration_->SetGradientBorderImage(newDecoration->GetGradientBorderImage());
    backDecoration_->SetHasBorderImageSource(newDecoration->GetHasBorderImageSource());
    backDecoration_->SetHasBorderImageSlice(newDecoration->GetHasBorderImageSlice());
    backDecoration_->SetHasBorderImageWidth(newDecoration->GetHasBorderImageWidth());
    backDecoration_->SetHasBorderImageOutset(newDecoration->GetHasBorderImageOutset());
    backDecoration_->SetHasBorderImageRepeat(newDecoration->GetHasBorderImageRepeat());
    backDecoration_->SetHasBorderImageGradient(newDecoration->GetHasBorderImageGradient());
    backDecoration_->SetImage(newDecoration->GetImage());
    backDecoration_->SetBorderImage(newDecoration->GetBorderImage());
    backDecoration_->SetPadding(newDecoration->GetPadding());
    backDecoration_->SetWindowBlurProgress(newDecoration->GetWindowBlurProgress());
    backDecoration_->SetWindowBlurStyle(newDecoration->GetWindowBlurStyle());
    backDecoration_->SetShadows(newDecoration->GetShadows());
    backDecoration_->SetBackgroundColor(newDecoration->GetBackgroundColor());
    backDecoration_->SetGrayScale(newDecoration->GetGrayScale());
    backDecoration_->SetBrightness(newDecoration->GetBrightness());
    backDecoration_->SetContrast(newDecoration->GetContrast());
    backDecoration_->SetSaturate(newDecoration->GetSaturate());
    backDecoration_->SetInvert(newDecoration->GetInvert());
    backDecoration_->SetColorBlend(newDecoration->GetColorBlend());
    backDecoration_->SetSepia(newDecoration->GetSepia());
}

void RenderBox::UpdateFrontDecoration(const RefPtr<Decoration>& newDecoration)
{
    if (!newDecoration) {
        frontDecoration_ = newDecoration;
        return;
    }

    if (!frontDecoration_) {
        LOGD("frontDecoration_ is null.");
        frontDecoration_ = AceType::MakeRefPtr<Decoration>();
    }
    frontDecoration_->SetBlurRadius(newDecoration->GetBlurRadius());
    frontDecoration_->SetBorder(newDecoration->GetBorder());
    frontDecoration_->SetImage(newDecoration->GetImage());
    frontDecoration_->SetShadows(newDecoration->GetShadows());
    frontDecoration_->SetBackgroundColor(newDecoration->GetBackgroundColor());
    frontDecoration_->SetGrayScale(newDecoration->GetGrayScale());
    frontDecoration_->SetBrightness(newDecoration->GetBrightness());
    frontDecoration_->SetContrast(newDecoration->GetContrast());
    frontDecoration_->SetSaturate(newDecoration->GetSaturate());
    frontDecoration_->SetInvert(newDecoration->GetInvert());
    frontDecoration_->SetColorBlend(newDecoration->GetColorBlend());
    frontDecoration_->SetSepia(newDecoration->GetSepia());
    frontDecoration_->SetHueRotate(newDecoration->GetHueRotate());
}

// TODO: OLEG align with state attributes
void RenderBox::UpdateStyleFromRenderNode(PropertyAnimatableType type)
{
    // Operator map for styles
    static const std::unordered_map<PropertyAnimatableType, void (*)(RenderBox&)> operators = {
        // Set width and height
        { PropertyAnimatableType::PROPERTY_WIDTH,
            [](RenderBox& node) {
                auto box = node.boxComponent_.Upgrade();
                if (box) {
                    box->SetWidth(node.width_);
                }
            } },
        { PropertyAnimatableType::PROPERTY_HEIGHT,
            [](RenderBox& node) {
                auto box = node.boxComponent_.Upgrade();
                if (box) {
                    box->SetHeight(node.height_);
                }
            } },
        { PropertyAnimatableType::PROPERTY_BACK_DECORATION_COLOR,
            [](RenderBox& node) {
                auto box = node.boxComponent_.Upgrade();
                if (box) {
                    box->SetColor(node.GetColor());
                }
            } },
    };
    auto operatorIter = operators.find(type);
    if (operatorIter != operators.end()) {
        operatorIter->second(*this);
    }
}

void RenderBox::OnPaintFinish()
{
    if (eventExtensions_ && eventExtensions_->HasOnAreaChangeExtension()) {
        auto inspector = inspector_.Upgrade();
        if (inspector) {
            auto area = inspector->GetCurrentRectAndOrigin();
            eventExtensions_->GetOnAreaChangeExtension()->UpdateArea(area.first, area.second);
        }
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
#if !defined(WINDOWS_PLATFORM) && !defined(MAC_PLATFORM)
    Size size = GetPaintSize() * viewScale;
    Offset globalOffset = (GetGlobalOffsetExternal() + margin_.GetOffset()) * viewScale;
    node->SetMarginSize(margin_.GetLayoutSize() * viewScale);
    node->SetWidth(size.Width());
    node->SetHeight(size.Height());
    node->SetLeft(globalOffset.GetX());
    node->SetTop(globalOffset.GetY());
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
    }
#endif
}

Offset RenderBox::GetGlobalOffsetExternal() const
{
    auto renderNode = GetParent().Upgrade();
    auto offset = renderNode ? GetPosition() + renderNode->GetGlobalOffsetExternal() : GetPosition();
    offset += alignOffset_;
    return offset;
}

Offset RenderBox::GetGlobalOffset() const
{
    auto renderNode = GetParent().Upgrade();
    auto offset = renderNode ? GetPosition() + renderNode->GetGlobalOffset() : GetPosition();
    offset += alignOffset_;
    return offset;
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
        auto boxCenter =
            Offset(currentOffset.GetX() + currentSize.Width() / 2.0, currentOffset.GetY() + currentSize.Height() / 2.0);
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

        double min_X = std::min({ leftTop.GetX(), rightTop.GetX(), leftBottom.GetX(), rightBottom.GetX() });
        double max_X = std::max({ leftTop.GetX(), rightTop.GetX(), leftBottom.GetX(), rightBottom.GetX() });
        double min_Y = std::min({ leftTop.GetY(), rightTop.GetY(), leftBottom.GetY(), rightBottom.GetY() });
        double max_Y = std::max({ leftTop.GetY(), rightTop.GetY(), leftBottom.GetY(), rightBottom.GetY() });
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
    if (backDecoration_ == nullptr) {
        backDecoration_ = AceType::MakeRefPtr<Decoration>();
    }
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
    controllerEnter_ = nullptr;
    controllerExit_ = nullptr;
    colorAnimationEnter_ = nullptr;
    colorAnimationExit_ = nullptr;
    animationType_ = HoverAnimationType::NONE;
    hoverColor_ = Color::TRANSPARENT;
    for (size_t i = 0; i < recognizers_.size(); i++) {
        recognizers_[i] = nullptr;
    }

    dragDropGesture_ = nullptr;
#if defined(WINDOWS_PLATFORM) || defined(MAC_PLATFORM)
    preTargetRenderBox_ = nullptr;
#endif
    onDrag_ = nullptr;
    onDragEnter_ = nullptr;
    onDragMove_ = nullptr;
    onDragLeave_ = nullptr;
    onDrop_ = nullptr;
    onClick_ = nullptr;
}

BackgroundImagePosition RenderBox::GetBackgroundPosition() const
{
    if (backDecoration_ == nullptr) {
        return BackgroundImagePosition();
    }
    RefPtr<BackgroundImage> backgroundImage = backDecoration_->GetImage();
    if (!backgroundImage) {
        LOGE("get background position failed. no background image.");
        return BackgroundImagePosition();
    }
    return backgroundImage->GetImagePosition();
}

void RenderBox::SetBackgroundSize(const BackgroundImageSize& size)
{
    if (backDecoration_ == nullptr) {
        backDecoration_ = AceType::MakeRefPtr<Decoration>();
    }
    RefPtr<BackgroundImage> backgroundImage = backDecoration_->GetImage();
    if (!backgroundImage) {
        // Suppress error logs when do animation.
        LOGE("set background size failed. no background image.");
        return;
    }
    if (backgroundImage->GetImageSize() == size) {
        return;
    }
    backgroundImage->SetImageSize(size);
    if (renderImage_) {
        // x direction
        renderImage_->SetBgImageSize(size.GetSizeTypeX(), size.GetSizeValueX(), true);
        // y direction
        renderImage_->SetBgImageSize(size.GetSizeTypeY(), size.GetSizeValueY(), false);
    }
    MarkNeedLayout();
}

BackgroundImageSize RenderBox::GetBackgroundSize() const
{
    if (backDecoration_ == nullptr) {
        return BackgroundImageSize();
    }
    RefPtr<BackgroundImage> backgroundImage = backDecoration_->GetImage();
    if (!backgroundImage) {
        LOGE("get background size failed. no background image.");
        return BackgroundImageSize();
    }
    return backgroundImage->GetImageSize();
}

void RenderBox::OnMouseHoverEnterAnimation()
{
    // stop the exit animation being played.
    ResetController(controllerExit_);
    if (!controllerEnter_) {
        controllerEnter_ = AceType::MakeRefPtr<Animator>(context_);
    }
    colorAnimationEnter_ = AceType::MakeRefPtr<KeyframeAnimation<Color>>();
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

void RenderBox::CreateFloatAnimation(RefPtr<KeyframeAnimation<float>>& floatAnimation, float beginValue, float endValue)
{
    if (!floatAnimation) {
        return;
    }
    auto keyframeBegin = AceType::MakeRefPtr<Keyframe<float>>(0.0, beginValue);
    auto keyframeEnd = AceType::MakeRefPtr<Keyframe<float>>(1.0, endValue);
    floatAnimation->AddKeyframe(keyframeBegin);
    floatAnimation->AddKeyframe(keyframeEnd);
    WeakPtr<Decoration> weakDecoration = WeakPtr<Decoration>(backDecoration_);
    floatAnimation->AddListener([weakBox = AceType::WeakClaim(this), weakDecoration](float value) {
        auto box = weakBox.Upgrade();
        if (box) {
            box->scale_ = value;
            box->MarkNeedRender();
        }
    });
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

void RenderBox::MouseHoverEnterTest()
{
    ResetController(controllerExit_);
    if (!controllerEnter_) {
        controllerEnter_ = AceType::MakeRefPtr<Animator>(context_);
    }
    if (animationType_ == HoverAnimationType::SCALE) {
        scaleAnimationEnter_ = AceType::MakeRefPtr<KeyframeAnimation<float>>();
        CreateFloatAnimation(scaleAnimationEnter_, 1.0, 1.05);
        controllerEnter_->AddInterpolator(scaleAnimationEnter_);
    } else if (animationType_ == HoverAnimationType::BOARD) {
        colorAnimationEnter_ = AceType::MakeRefPtr<KeyframeAnimation<Color>>();
        CreateColorAnimation(colorAnimationEnter_, hoverColor_, Color::FromRGBO(0, 0, 0, 0.05));
        controllerEnter_->AddInterpolator(colorAnimationEnter_);
    } else {
        return;
    }
    controllerEnter_->SetDuration(HOVER_ANIMATION_DURATION);
    controllerEnter_->Play();
    controllerEnter_->SetFillMode(FillMode::FORWARDS);
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

void RenderBox::MouseHoverExitTest()
{
    ResetController(controllerEnter_);
    if (!controllerExit_) {
        controllerExit_ = AceType::MakeRefPtr<Animator>(context_);
    }
    if (animationType_ == HoverAnimationType::SCALE) {
        scaleAnimationExit_ = AceType::MakeRefPtr<KeyframeAnimation<float>>();
        auto begin = scale_;
        CreateFloatAnimation(scaleAnimationExit_, begin, 1.0);
        controllerExit_->AddInterpolator(scaleAnimationExit_);
    } else if (animationType_ == HoverAnimationType::BOARD) {
        colorAnimationExit_ = AceType::MakeRefPtr<KeyframeAnimation<Color>>();
        CreateColorAnimation(colorAnimationExit_, hoverColor_, Color::FromRGBO(0, 0, 0, 0.0));
        controllerExit_->AddInterpolator(colorAnimationExit_);
    } else {
        return;
    }
    controllerExit_->SetDuration(HOVER_ANIMATION_DURATION);
    controllerExit_->Play();
    controllerExit_->SetFillMode(FillMode::FORWARDS);
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

void RenderBox::SetShadow(const Shadow& value)
{
    if (backDecoration_ == nullptr) {
        backDecoration_ = AceType::MakeRefPtr<Decoration>();
    }

    auto shadows = backDecoration_->GetShadows();
    Shadow shadow;

    if (!shadows.empty()) {
        shadow = shadows.front();
    }

    if (shadow != value) {
        backDecoration_->ClearAllShadow();
        backDecoration_->AddShadow(value);
        MarkNeedLayout();
    }
}

Shadow RenderBox::GetShadow() const
{
    if (backDecoration_ != nullptr) {
        const auto& shadows = backDecoration_->GetShadows();
        if (!shadows.empty()) {
            return shadows.front();
        }
    }
    return {};
}

void RenderBox::SetGrayScale(double scale)
{
    if (frontDecoration_ == nullptr) {
        frontDecoration_ = AceType::MakeRefPtr<Decoration>();
    }

    double _scale = frontDecoration_->GetGrayScale().Value();

    if (!NearEqual(_scale, scale)) {
        frontDecoration_->SetGrayScale(Dimension(_scale));
        MarkNeedRender();
    }
}

double RenderBox::GetGrayScale(void) const
{
    if (frontDecoration_ != nullptr) {
        return frontDecoration_->GetGrayScale().Value();
    }

    return 0.0;
}

void RenderBox::SetBrightness(double ness)
{
    if (frontDecoration_ == nullptr) {
        frontDecoration_ = AceType::MakeRefPtr<Decoration>();
    }

    double brightness = frontDecoration_->GetBrightness().Value();

    if (!NearEqual(brightness, ness)) {
        frontDecoration_->SetBrightness(Dimension(brightness));
        MarkNeedRender();
    }
}

double RenderBox::GetBrightness(void) const
{
    if (frontDecoration_ != nullptr) {
        return frontDecoration_->GetBrightness().Value();
    }
    return 0.0;
}

void RenderBox::SetContrast(double trast)
{
    if (frontDecoration_ == nullptr) {
        frontDecoration_ = AceType::MakeRefPtr<Decoration>();
    }
    double contrast = frontDecoration_->GetContrast().Value();
    if (!NearEqual(contrast, trast)) {
        frontDecoration_->SetContrast(Dimension(contrast));
        MarkNeedRender();
    }
}

double RenderBox::GetContrast(void) const
{
    if (frontDecoration_ != nullptr) {
        return frontDecoration_->GetContrast().Value();
    }
    return 0.0;
}

void RenderBox::SetColorBlend(const Color& color)
{
    if (frontDecoration_ == nullptr) {
        frontDecoration_ = AceType::MakeRefPtr<Decoration>();
    }
    if (!NearEqual(frontDecoration_->GetColorBlend().GetValue(), color.GetValue())) {
        frontDecoration_->SetColorBlend(color);
        MarkNeedRender();
    }
}

Color RenderBox::GetColorBlend() const
{
    if (frontDecoration_) {
        return frontDecoration_->GetColorBlend();
    }
    return {};
}

void RenderBox::SetSaturate(double rate)
{
    if (frontDecoration_ == nullptr) {
        frontDecoration_ = AceType::MakeRefPtr<Decoration>();
    }
    double saturate = frontDecoration_->GetSaturate().Value();
    if (!NearEqual(saturate, rate)) {
        frontDecoration_->SetSaturate(Dimension(saturate));
        MarkNeedRender();
    }
}

double RenderBox::GetSaturate(void) const
{
    if (frontDecoration_ != nullptr) {
        return frontDecoration_->GetSaturate().Value();
    }
    return 0.0;
}

void RenderBox::SetSepia(double pia)
{
    if (frontDecoration_ == nullptr) {
        frontDecoration_ = AceType::MakeRefPtr<Decoration>();
    }
    double pias = frontDecoration_->GetSepia().Value();
    if (!NearEqual(pias, pia)) {
        frontDecoration_->SetSepia(Dimension(pias));
        MarkNeedRender();
    }
}

double RenderBox::GetSepia(void) const
{
    if (frontDecoration_ != nullptr) {
        return frontDecoration_->GetSepia().Value();
    }
    return 0.0;
}

void RenderBox::SetInvert(double invert)
{
    if (frontDecoration_ == nullptr) {
        frontDecoration_ = AceType::MakeRefPtr<Decoration>();
    }
    double inverts = frontDecoration_->GetInvert().Value();
    if (!NearEqual(inverts, invert)) {
        frontDecoration_->SetInvert(Dimension(inverts));
        MarkNeedRender();
    }
}

double RenderBox::GetInvert(void) const
{
    if (frontDecoration_ != nullptr) {
        return frontDecoration_->GetInvert().Value();
    }
    return 0.0;
}

void RenderBox::SetHueRotate(float deg)
{
    if (frontDecoration_ == nullptr) {
        frontDecoration_ = AceType::MakeRefPtr<Decoration>();
    }
    float degs = frontDecoration_->GetHueRotate();
    if (!NearEqual(degs, deg)) {
        frontDecoration_->SetHueRotate(degs);
        MarkNeedRender();
    }
}

float RenderBox::GetHueRotate(void) const
{
    if (frontDecoration_ != nullptr) {
        return frontDecoration_->GetHueRotate();
    }
    return 0.0;
}

void RenderBox::SetBorderWidth(double width, const BorderEdgeHelper& helper)
{
    if (backDecoration_ == nullptr) {
        backDecoration_ = AceType::MakeRefPtr<Decoration>();
    }
    Border border = backDecoration_->GetBorder();
    if (helper.Set(width, &border)) {
        backDecoration_->SetBorder(border);
        MarkNeedLayout();
    }
}

double RenderBox::GetBorderWidth(const BorderEdgeHelper& helper) const
{
    if (backDecoration_ != nullptr) {
        return helper.Get(backDecoration_->GetBorder()).GetWidth().Value();
    }
    return 0.0;
}

void RenderBox::SetBorderColor(const Color& color, const BorderEdgeHelper& helper)
{
    if (backDecoration_ == nullptr) {
        backDecoration_ = AceType::MakeRefPtr<Decoration>();
    }
    Border border = backDecoration_->GetBorder();
    if (helper.Set(color, &border)) {
        backDecoration_->SetBorder(border);
        MarkNeedLayout();
    }
}

Color RenderBox::GetBorderColor(const BorderEdgeHelper& helper) const
{
    if (backDecoration_) {
        return helper.Get(backDecoration_->GetBorder()).GetColor();
    }
    return {};
}

void RenderBox::SetBorderStyle(BorderStyle borderStyle, const BorderEdgeHelper& helper)
{
    if (backDecoration_ == nullptr) {
        backDecoration_ = AceType::MakeRefPtr<Decoration>();
    }
    Border border = backDecoration_->GetBorder();
    if (helper.Set(borderStyle, &border)) {
        backDecoration_->SetBorder(border);
        MarkNeedLayout();
    }
}

BorderStyle RenderBox::GetBorderStyle(const BorderEdgeHelper& helper) const
{
    if (backDecoration_) {
        return helper.Get(backDecoration_->GetBorder()).GetBorderStyle();
    }
    return BorderStyle::NONE;
}

void RenderBox::SetBorderRadius(double radius, const BorderRadiusHelper& helper)
{
    if (backDecoration_ == nullptr) {
        backDecoration_ = AceType::MakeRefPtr<Decoration>();
    }
    Border border = backDecoration_->GetBorder();
    if (helper.Set(radius, &border)) {
        backDecoration_->SetBorder(border);
        MarkNeedLayout();
    }
}

double RenderBox::GetBorderRadius(const BorderRadiusHelper& helper) const
{
    if (backDecoration_) {
        return helper.Get(backDecoration_->GetBorder());
    }
    return 0.0;
}

void RenderBox::SetBlurRadius(const AnimatableDimension& radius)
{
    if (frontDecoration_ == nullptr) {
        frontDecoration_ = AceType::MakeRefPtr<Decoration>();
    }
    if (!NearEqual(frontDecoration_->GetBlurRadius().Value(), radius.Value())) {
        frontDecoration_->SetBlurRadius(radius);
        MarkNeedRender();
    }
}

AnimatableDimension RenderBox::GetBlurRadius() const
{
    if (frontDecoration_) {
        return frontDecoration_->GetBlurRadius();
    }
    return AnimatableDimension(0.0, DimensionUnit::PX);
}

void RenderBox::SetBackdropRadius(const AnimatableDimension& radius)
{
    if (backDecoration_ == nullptr) {
        backDecoration_ = AceType::MakeRefPtr<Decoration>();
    }
    if (!NearEqual(backDecoration_->GetBlurRadius().Value(), radius.Value())) {
        backDecoration_->SetBlurRadius(radius);
        MarkNeedRender();
    }
}

AnimatableDimension RenderBox::GetBackdropRadius() const
{
    if (backDecoration_) {
        return backDecoration_->GetBlurRadius();
    }
    return AnimatableDimension(0.0, DimensionUnit::PX);
}

void RenderBox::SetWindowBlurProgress(double progress)
{
    if (backDecoration_ == nullptr) {
        backDecoration_ = AceType::MakeRefPtr<Decoration>();
    }
    if (!NearEqual(backDecoration_->GetWindowBlurProgress(), progress)) {
        backDecoration_->SetWindowBlurProgress(progress);
        MarkNeedRender();
    }
}

double RenderBox::GetWindowBlurProgress() const
{
    if (backDecoration_) {
        return backDecoration_->GetWindowBlurProgress();
    }
    return 0.0;
}

void RenderBox::AddRecognizerToResult(
    const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    if (!ExistGestureRecognizer()) {
        return;
    }

    bool ignoreInternal = false;
    for (int i = MAX_GESTURE_SIZE - 1; i >= 0; i--) {
        if (recognizers_[i]) {
            ignoreInternal = recognizers_[i]->GetPriorityMask() == GestureMask::IgnoreInternal;
            if (ignoreInternal) {
                break;
            }
        }
    }

    if (ignoreInternal) {
        auto iter = result.begin();
        while (iter != result.end()) {
            auto recognizer = AceType::DynamicCast<GestureRecognizer>(*iter);
            if (!recognizer) {
                iter++;
                continue;
            }

            if (!recognizer->GetIsExternalGesture()) {
                iter++;
                continue;
            }
            iter = result.erase(iter);
        }
    }

    for (int i = MAX_GESTURE_SIZE - 1; i >= 0; i--) {
        if (recognizers_[i]) {
            LOGD("OnTouchTestHit add recognizer to result %{public}s", AceType::TypeName(recognizers_[i]));
            recognizers_[i]->SetCoordinateOffset(coordinateOffset);
            result.emplace_back(recognizers_[i]);
        }
    }
}

void RenderBox::OnTouchTestHit(
    const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    AddRecognizerToResult(coordinateOffset, touchRestrict, result);

    if (onClick_) {
        result.emplace_back(onClick_);
    }
    if (dragDropGesture_) {
        result.emplace_back(dragDropGesture_);
    }
    if (touchRecognizer_) {
        result.emplace_back(touchRecognizer_);
    }
}

void RenderBox::UpdateGestureRecognizer(const std::array<RefPtr<Gesture>, MAX_GESTURE_SIZE>& gestures)
{
    // Considering 4 cases:
    // 1. new gesture == null && old recognizer == null  -->  do nothing
    // 2. new gesture != null && old recognizer == null  -->  create new recognizer configured with new gesture
    // 3. new gesture == null && old recognizer != null  -->  remove old recognizer
    // 4. new gesture != null && old recognizer != null  -->  update old recognizer with new configuration if
    // possible(determined by[GestureRecognizer::ReconcileFrom]), or remove the old recognizer and create new
    // one configured with new gesture.
    for (size_t i = 0; i < gestures.size(); i++) {
        if (!gestures[i]) {
            recognizers_[i] = nullptr;
            continue;
        }
        auto recognizer = gestures[i]->CreateRecognizer(context_);
        if (recognizer) {
            recognizer->SetIsExternalGesture(true);
            if (!recognizers_[i] || !recognizers_[i]->ReconcileFrom(recognizer)) {
                recognizers_[i] = recognizer;
            }
        }
    }
}

bool RenderBox::ExistGestureRecognizer()
{
    for (size_t i = 0; i < recognizers_.size(); i++) {
        if (recognizers_[i]) {
            return true;
        }
    }

    return false;
}

void RenderBox::OnStatusStyleChanged(StyleState componentState)
{
    RenderBoxBase::OnStatusStyleChanged(componentState);

    if (stateAttributeList_ == nullptr) {
        return;
    }

    LOGD("state %{public}d  attr count %{public}llu", componentState.c_str(), stateAttributeList_->size());
    bool updated = false;
    for (const auto& attribute : *stateAttributeList_) {
        if (attribute->stateName_ != componentState) {
            continue;
        }

        updated = true;
        switch (attribute->id_) {
            case BoxStateAttribute::COLOR: {
                LOGD("Setting COLOR for state %s", attribute->stateName_);
                auto colorState =
                    AceType::DynamicCast<StateAttributeValue<BoxStateAttribute, AnimatableColor>>(attribute);
                GetBackDecoration()->SetBackgroundColor(colorState->value_);
            } break;

            case BoxStateAttribute::BORDER_COLOR: {
                LOGD("Setting BORDER_COLOR for state %{public}d", attribute->stateName_);
                auto colorState =
                    AceType::DynamicCast<StateAttributeValue<BoxStateAttribute, AnimatableColor>>(attribute);
                BoxComponentHelper::SetBorderColor(GetBackDecoration(), colorState->value_);
            } break;

            case BoxStateAttribute::BORDER_RADIUS: {
                LOGD("Setting BORDER_RADIUS for state %{public}d", attribute->stateName_);
                auto radiusState =
                    AceType::DynamicCast<StateAttributeValue<BoxStateAttribute, AnimatableDimension>>(attribute);
                BoxComponentHelper::SetBorderRadius(GetBackDecoration(), radiusState->value_);
            } break;

            case BoxStateAttribute::BORDER_STYLE: {
                LOGD("Setting BORDER_STYLE for state %{public}d", attribute->stateName_);
                auto attributeStateValue =
                    AceType::DynamicCast<StateAttributeValue<BoxStateAttribute, BorderStyle>>(attribute);
                BoxComponentHelper::SetBorderStyle(GetBackDecoration(), attributeStateValue->value_);
            } break;

            case BoxStateAttribute::BORDER_WIDTH: {
                auto widthState =
                    AceType::DynamicCast<StateAttributeValue<BoxStateAttribute, AnimatableDimension>>(attribute);
                LOGD("Setting BORDER_WIDTH for state %{public}d to %{public}lf",
                    attribute->stateName_, widthState->value_.Value());
                BoxComponentHelper::SetBorderWidth(GetBackDecoration(), widthState->value_);
            } break;

            case BoxStateAttribute::HEIGHT: {
                auto valueState =
                    AceType::DynamicCast<StateAttributeValue<BoxStateAttribute, Dimension>>(attribute);
                LOGD("Setting BORDER_WIDTH for state %{public}d to %{public}lf",
                    attribute->stateName_, valueState->value_.Value());
                height_ = valueState->value_;
            } break;

            case BoxStateAttribute::WIDTH: {
                auto valueState =
                    AceType::DynamicCast<StateAttributeValue<BoxStateAttribute, Dimension>>(attribute);
                LOGD("Setting BORDER_WIDTH for state %{public}d to %{public}lf",
                    attribute->stateName_, valueState->value_.Value());
                width_ = valueState->value_;
            } break;

            case BoxStateAttribute::ASPECT_RATIO: {
                LOGD("Setting ASPECT Ration state %{public}d", attribute->stateName_);
                auto valueState =
                    AceType::DynamicCast<StateAttributeValue<BoxStateAttribute, AnimatableDimension>>(attribute);
                SetAspectRatio(valueState->value_);
            } break;

            case BoxStateAttribute::BORDER: {
                // We replace support for border object with updates to border components:
                // color, style, width, radius
                // The reason - developer does not have to provide all border properties
                // when border is set.
                // See JSViewAbstract::JsBorder for details
            } break;

            case BoxStateAttribute::GRADIENT: {
                auto gradientState = AceType::DynamicCast<StateAttributeValue<BoxStateAttribute, Gradient>>(attribute);
                LOGD("Setting Gradient state %{public}d", attribute->stateName_);
                GetBackDecoration()->SetGradient(gradientState->value_);
            } break;
        }
    }
    if (updated) {
        MarkNeedLayout();
    }
};

} // namespace OHOS::Ace
