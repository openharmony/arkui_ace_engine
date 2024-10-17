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

#include "core/components/box/render_box.h"

#include "base/log/event_report.h"
#include "core/components/box/box_component_helper.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components/text_field/render_text_field.h"
#include "core/components_v2/list/render_list.h"
#include "core/gestures/parallel_recognizer.h"

namespace OHOS::Ace {
namespace {

constexpr int32_t HOVER_ANIMATION_DURATION = 250;

}; // namespace

void RenderBox::HandleAccessibilityFocusEvent(bool isAccessibilityFocus)
{
    isAccessibilityFocus_ = isAccessibilityFocus;
    std::string accessibilityEventType;
    if (isAccessibilityFocus) {
        accessibilityEventType = "accessibilityfocus";
    } else {
        accessibilityEventType = "accessibilityclearfocus";
    }
    SendAccessibilityEvent(accessibilityEventType);
    MarkNeedRender();
}

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

Radius RenderBox::GetBorderRadius() const
{
    if (backDecoration_) {
        return backDecoration_->GetBorder().TopLeftRadius();
    }
    return Radius();
}

void RenderBox::Update(const RefPtr<Component>& component)
{
    const RefPtr<BoxComponent> box = AceType::DynamicCast<BoxComponent>(component);
    if (box) {
        boxComponent_ = box;
        needMaterial_ |= box->GetNeedMaterial();
        inspectorDirection_ = box->GetInspectorDirection();
        RenderBoxBase::Update(component);
        UpdateBackDecoration(box->GetBackDecoration());
        needPaintDebugBoundary_ = box->GetEnableDebugBoundary();
        UpdateFrontDecoration(box->GetFrontDecoration());
        hoverColorBegin_ = box->GetColor();
        hoverAnimationType_ = box->GetMouseAnimationType();
        isZoom = hoverAnimationType_ == HoverAnimationType::SCALE;
        MarkNeedLayout();

        responseRegion_ = box->GetResponseRegion();
        isResponseRegion_ = box->IsResponseRegion();

        auto tapGesture = box->GetOnClick();
        if (tapGesture) {
            onClick_ = tapGesture->CreateRecognizer(context_);
            onClick_->SetIsExternalGesture(true);
            SetAccessibilityClickImpl();
        } else {
            onClick_ = nullptr;
        }
        if (!box->GetRemoteMessageEvent().IsEmpty() && !tapGesture) {
            onClick_ = AceType::MakeRefPtr<ClickRecognizer>();
        }
        auto clickRecognizer = AceType::DynamicCast<ClickRecognizer>(onClick_);
        if (clickRecognizer) {
            auto weak = AceType::WeakClaim(this);
            clickRecognizer->SetRemoteMessage([weak](const ClickInfo& info) {
                auto client = weak.Upgrade();
                if (client) {
                    client->HandleRemoteMessage(info);
                }
            });
        }
        auto longPressGesture = box->GetOnLongPress();
        if (longPressGesture) {
            onLongPress_ = longPressGesture->CreateRecognizer(context_);
            onLongPress_->SetIsExternalGesture(true);
        }

        onDragStart_ = box->GetOnDragStartId();
        onDragEnter_ = box->GetOnDragEnterId();
        onDragMove_ = box->GetOnDragMoveId();
        onDragLeave_ = box->GetOnDragLeaveId();
        onDrop_ = box->GetOnDropId();
        enableDragStart_ = box->GetEnableDragStart();
        if (onDragStart_) {
            CreateDragDropRecognizer(context_);
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
        if (!box->GetRemoteMessageEvent().IsEmpty()) {
            remoteMessageEvent_ =
                AceAsyncEvent<void(const std::shared_ptr<ClickInfo>&)>::Create(box->GetRemoteMessageEvent(), context_);
        }

        auto context = GetContext().Upgrade();
        if (onDragStart_ || onDrop_) {
            context->InitDragListener();
        }

        onHover_ = box->GetOnHoverId();
        onMouse_ = box->GetOnMouseId();
        onLongPressId_ = box->GetOnLongPress();

        auto gestures = box->GetGestures();
        UpdateGestureRecognizer(gestures);
        SetAccessibilityFocusImpl();

        if (box->HasStateAttributes()) {
            stateAttributeList_ = box->GetStateAttributes();
        }
        OnStatusStyleChanged(disabled_ ? VisualState::DISABLED : VisualState::NORMAL);

        onTouchUpId_ = box->GetOnTouchUpId();
        onTouchDownId_ = box->GetOnTouchDownId();
        onTouchMoveId_ = box->GetOnTouchMoveId();
        auto wp = AceType::WeakClaim(this);
        touchRecognizer_ = AceType::MakeRefPtr<RawRecognizer>();
        touchRecognizer_->SetOnTouchDown([wp](const TouchEventInfo& touchInfo) {
            auto box = wp.Upgrade();
            if (!box) {
                return;
            }
            box->HandleTouchEvent(true);
            if (box->onTouchDownId_) {
                box->onTouchDownId_(touchInfo);
            }
        });
        touchRecognizer_->SetOnTouchUp([wp](const TouchEventInfo& touchInfo) {
            auto box = wp.Upgrade();
            if (!box) {
                return;
            }
            box->HandleTouchEvent(false);
            if (box->onTouchUpId_) {
                box->onTouchUpId_(touchInfo);
            }
        });
        touchRecognizer_->SetOnTouchMove(onTouchMoveId_);
    }
    // In each update, the extensions will be updated with new one.
    if (eventExtensions_ && eventExtensions_->HasOnAreaChangeExtension()) {
        auto inspector = inspector_.Upgrade();
        if (inspector) {
            auto area = inspector->GetCurrentRectAndOrigin();
            auto lastArea = inspector->GetLastRectAndOrigin();
            if (area != lastArea) {
                eventExtensions_->GetOnAreaChangeExtension()->UpdateArea(
                    area.first, area.second, lastArea.first, lastArea.second);
                inspector->UpdateLastRectAndOrigin(area);
            }
        }
    }
}

void RenderBox::HandleTouchEvent(bool isTouchDown)
{
    if (isTouchDown) {
        OnStatusStyleChanged(VisualState::PRESSED);
    } else {
        OnStatusStyleChanged(VisualState::NORMAL);
    }
}

void RenderBox::SetAccessibilityFocusImpl()
{
    auto refNode = accessibilityNode_.Upgrade();
    if (!refNode) {
        return;
    }
    auto weakPtr = AceType::WeakClaim(this);
    refNode->SetActionAccessibilityFocusImpl([weakPtr](bool isFocus) {
        auto accessibilityFocus = weakPtr.Upgrade();
        if (accessibilityFocus) {
            accessibilityFocus->HandleAccessibilityFocusEvent(isFocus);
        }
    });
}

void RenderBox::SetAccessibilityClickImpl()
{
    if (AceType::InstanceOf<ClickRecognizer>(onClick_)) {
        auto clickRecognizer = AceType::DynamicCast<ClickRecognizer>(onClick_);
        SetAccessibilityClick(clickRecognizer);
    }
}

void RenderBox::AddDataToClipboard(const RefPtr<PipelineContext>& context, const std::string& extraInfo,
    const std::string& selectedText, const std::string& imageSrc)
{
    auto seleItemSizeStr = JsonUtil::Create(true);
    seleItemSizeStr->Put("width", selectedItemSize_.Width());
    seleItemSizeStr->Put("height", selectedItemSize_.Height());
    seleItemSizeStr->Put("selectedIndex", selectedIndex_);
    seleItemSizeStr->Put("customDragInfo", extraInfo.c_str());
    MergeClipboardData(context, seleItemSizeStr->ToString());
}

DragItemInfo RenderBox::GenerateDragItemInfo(const RefPtr<PipelineContext>& context, const GestureEvent& info)
{
    RefPtr<DragEvent> event = AceType::MakeRefPtr<DragEvent>();
    event->SetX(context->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetX(), DimensionUnit::PX)));
    event->SetY(context->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetY(), DimensionUnit::PX)));
    selectedItemSize_ = GetLayoutSize();
    auto extraParams = JsonUtil::Create(true);
    SetSelectedIndex(info);
    if (selectedIndex_ != DEFAULT_INDEX) {
        extraParams->Put("selectedIndex", selectedIndex_);
    }

    return onDragStart_(event, extraParams->ToString());
}

void RenderBox::PanOnActionStart(const GestureEvent& info)
{
    if (!enableDragStart_) {
        LOGI("drag start is disabled.");
        return;
    }

    if (!onDragStart_) {
        return;
    }

    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("Context is null.");
        return;
    }

    GestureEvent newInfo = info;
    Point newPoint = UpdatePoint(pipelineContext, startPoint_);
    newInfo.SetGlobalPoint(newPoint);
    auto dragItemInfo = GenerateDragItemInfo(pipelineContext, newInfo);
#if !defined(PREVIEW)
    if (dragItemInfo.pixelMap) {
        auto initRenderNode = AceType::Claim(this);
        isDragDropNode_  = true;
        pipelineContext->SetInitRenderNode(initRenderNode);

        AddDataToClipboard(pipelineContext, dragItemInfo.extraInfo, "", "");
        if (!dragWindow_) {
            auto rect = pipelineContext->GetCurrentWindowRect();
            dragWindow_ = DragWindow::CreateDragWindow("APP_DRAG_WINDOW",
                static_cast<int32_t>(info.GetGlobalPoint().GetX()) + rect.Left(),
                static_cast<int32_t>(info.GetGlobalPoint().GetY()) + rect.Top(), dragItemInfo.pixelMap->GetWidth(),
                dragItemInfo.pixelMap->GetHeight());
            dragWindow_->SetOffset(rect.Left(), rect.Top());
            dragWindow_->DrawPixelMap(dragItemInfo.pixelMap);
        }
        return;
    }
#endif
    if (!dragItemInfo.customComponent) {
        LOGW("the drag custom component is null");
        return;
    }
    hasDragItem_ = true;
    auto positionedComponent = AceType::MakeRefPtr<PositionedComponent>(dragItemInfo.customComponent);
    positionedComponent->SetTop(Dimension(GetGlobalOffset().GetY()));
    positionedComponent->SetLeft(Dimension(GetGlobalOffset().GetX()));
    SetLocalPoint(startPoint_ - GetGlobalOffset());
    auto updatePosition = [renderBox = AceType::Claim(this)](
                                const std::function<void(const Dimension&, const Dimension&)>& func) {
        if (!renderBox) {
            return;
        }
        renderBox->SetUpdateBuilderFuncId(func);
    };
    positionedComponent->SetUpdatePositionFuncId(updatePosition);
    auto stackElement = pipelineContext->GetLastStack();
    stackElement->PushComponent(positionedComponent);
}

void RenderBox::PanOnActionUpdate(const GestureEvent& info)
{
#if !defined(PREVIEW)
    if (isDragDropNode_  && dragWindow_) {
        int32_t x = static_cast<int32_t>(info.GetGlobalPoint().GetX());
        int32_t y = static_cast<int32_t>(info.GetGlobalPoint().GetY());
        if (dragWindow_) {
            dragWindow_->MoveTo(x, y);
        }
        return;
    }
#endif
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("Context is null.");
        return;
    }
    RefPtr<DragEvent> event = AceType::MakeRefPtr<DragEvent>();
    auto isContainerModal = pipelineContext->GetWindowModal() == WindowModal::CONTAINER_MODAL &&
        pipelineContext->GetWindowManager()->GetWindowMode() == WindowMode::WINDOW_MODE_FLOATING;
    if (isContainerModal) {
        auto floatOffset =
            info.GetGlobalPoint() + Offset(-(CONTAINER_BORDER_WIDTH.ConvertToPx() + CONTENT_PADDING.ConvertToPx()),
            -CONTAINER_TITLE_HEIGHT.ConvertToPx());
        event->SetX(pipelineContext->ConvertPxToVp(Dimension(floatOffset.GetX(), DimensionUnit::PX)));
        event->SetY(pipelineContext->ConvertPxToVp(Dimension(floatOffset.GetY(), DimensionUnit::PX)));
    } else {
        event->SetX(pipelineContext->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetX(), DimensionUnit::PX)));
        event->SetY(pipelineContext->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetY(), DimensionUnit::PX)));
    }
    Offset offset = info.GetGlobalPoint() - GetLocalPoint();
    if (GetUpdateBuilderFuncId()) {
        GetUpdateBuilderFuncId()(Dimension(offset.GetX()), Dimension(offset.GetY()));
    }

    auto extraParams = JsonUtil::Create(true);
    auto targetDragDropNode = FindDragDropNode(pipelineContext, info);
    auto preDragDropNode = GetPreDragDropNode();
    GestureEvent newInfo = info;
    Point newPoint = UpdatePoint(pipelineContext, info.GetGlobalPoint());
    newInfo.SetGlobalPoint(newPoint);
    SetInsertIndex(targetDragDropNode, newInfo);
    if (targetDragDropNode != initialDragDropNode_) {
        extraParams->Put("selectedIndex", DEFAULT_INDEX_VALUE);
    } else {
        extraParams->Put("selectedIndex", selectedIndex_);
    }
    extraParams->Put("insertIndex", insertIndex_);
    if (preDragDropNode == targetDragDropNode) {
        if (targetDragDropNode && targetDragDropNode->GetOnDragMove()) {
            (targetDragDropNode->GetOnDragMove())(event, extraParams->ToString());
        }
        return;
    }
    if (preDragDropNode && preDragDropNode->GetOnDragLeave()) {
        (preDragDropNode->GetOnDragLeave())(event, extraParams->ToString());
    }
    if (targetDragDropNode && targetDragDropNode->GetOnDragEnter()) {
        (targetDragDropNode->GetOnDragEnter())(event, extraParams->ToString());
    }
    SetPreDragDropNode(targetDragDropNode);
}

void RenderBox::PanOnActionEnd(const GestureEvent& info)
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("Context is null.");
        return;
    }
#if !defined(PREVIEW)
    if (isDragDropNode_) {
        isDragDropNode_  = false;
        RestoreCilpboardData(pipelineContext);

        if (GetOnDrop()) {
            RefPtr<DragEvent> event = AceType::MakeRefPtr<DragEvent>();
            RefPtr<PasteData> pasteData = AceType::MakeRefPtr<PasteData>();
            event->SetPasteData(pasteData);
            event->SetX(pipelineContext->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetX(), DimensionUnit::PX)));
            event->SetY(pipelineContext->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetY(), DimensionUnit::PX)));

            auto extraParams = JsonUtil::Create(true);
            extraParams->Put("selectedIndex", selectedIndex_);
            extraParams->Put("insertIndex", insertIndex_);
            (GetOnDrop())(event, extraParams->ToString());
            pipelineContext->SetInitRenderNode(nullptr);
        }
    }

    if (dragWindow_) {
        dragWindow_->Destroy();
        dragWindow_ = nullptr;
        return;
    }
#endif
    RefPtr<DragEvent> event = AceType::MakeRefPtr<DragEvent>();
    RefPtr<PasteData> pasteData = AceType::MakeRefPtr<PasteData>();
    event->SetPasteData(pasteData);
    event->SetX(pipelineContext->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetX(), DimensionUnit::PX)));
    event->SetY(pipelineContext->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetY(), DimensionUnit::PX)));

    Offset offset = info.GetGlobalPoint() - GetLocalPoint();
    if (GetUpdateBuilderFuncId()) {
        GetUpdateBuilderFuncId()(Dimension(offset.GetX()), Dimension(offset.GetY()));
    }
    if (hasDragItem_) {
        auto stackElement = pipelineContext->GetLastStack();
        stackElement->PopComponent();
    }
    hasDragItem_ = false;

    ACE_DCHECK(GetPreDragDropNode() == FindTargetRenderNode<RenderBox>(pipelineContext, info));
    auto targetDragDropNode = GetPreDragDropNode();
    if (!targetDragDropNode) {
        return;
    }
    if (targetDragDropNode->GetOnDrop()) {
        auto extraParams = JsonUtil::Create(true);
        GestureEvent newInfo = info;
        Point newPoint = UpdatePoint(pipelineContext, info.GetGlobalPoint());
        newInfo.SetGlobalPoint(newPoint);
        SetInsertIndex(targetDragDropNode, newInfo);
        if (insertIndex_ == DEFAULT_INDEX_VALUE) {
            (targetDragDropNode->GetOnDrop())(event, extraParams->ToString());
            SetPreDragDropNode(nullptr);
            return;
        }
        if (targetDragDropNode != initialDragDropNode_) {
            extraParams->Put("selectedIndex", DEFAULT_INDEX_VALUE);
        } else {
            extraParams->Put("selectedIndex", selectedIndex_);
        }
        extraParams->Put("insertIndex", insertIndex_);
        (targetDragDropNode->GetOnDrop())(event, extraParams->ToString());
    }
    SetPreDragDropNode(nullptr);
}

void RenderBox::PanOnActionCancel()
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("Context is null.");
        return;
    }

#if !defined(PREVIEW)
    if (isDragDropNode_) {
        RestoreCilpboardData(pipelineContext);
        isDragDropNode_ = false;
    }

    if (dragWindow_) {
        dragWindow_->Destroy();
        dragWindow_ = nullptr;
    }
#endif
    if (hasDragItem_) {
        auto stackElement = pipelineContext->GetLastStack();
        stackElement->PopComponent();
        hasDragItem_ = false;
    }
    SetPreDragDropNode(nullptr);
}

void RenderBox::SetSelectedIndex(const GestureEvent& info)
{
    auto renderList = FindTargetRenderNode<V2::RenderList>(context_.Upgrade(), info);
    if (renderList) {
        selectedIndex_ = renderList->CalculateSelectedIndex(renderList, info, selectedItemSize_);
        initialDragDropNode_ = FindDragDropNode(context_.Upgrade(), info);
    }
}

void RenderBox::SetInsertIndex(const RefPtr<DragDropEvent>& targetDragDropNode, const GestureEvent& info)
{
    auto renderNode = AceType::DynamicCast<RenderNode>(targetDragDropNode);
    if (!renderNode) {
        insertIndex_ = DEFAULT_INDEX_VALUE;
        return;
    }
    auto renderList = renderNode->FindTargetRenderNode<V2::RenderList>(context_.Upgrade(), info);
    if (renderList) {
        insertIndex_ = renderList->CalculateInsertIndex(renderList, info, selectedItemSize_);
    }
}

void RenderBox::UpdateBackDecoration(const RefPtr<Decoration>& newDecoration)
{
    if (!newDecoration) {
        backDecoration_ = newDecoration;
        OnAttachContext();
        return;
    }

    if (!backDecoration_) {
        backDecoration_ = AceType::MakeRefPtr<Decoration>();
    }
    OnAttachContext();

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
    backDecoration_->SetBorderImageGradient(newDecoration->GetBorderImageGradient());
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
    backDecoration_->SetGrayScale(newDecoration->GetGrayScale());
    backDecoration_->SetBrightness(newDecoration->GetBrightness());
    backDecoration_->SetContrast(newDecoration->GetContrast());
    backDecoration_->SetSaturate(newDecoration->GetSaturate());
    backDecoration_->SetInvert(newDecoration->GetInvert());
    backDecoration_->SetColorBlend(newDecoration->GetColorBlend());
    backDecoration_->SetSepia(newDecoration->GetSepia());
    backDecoration_->SetBackgroundColor(newDecoration->GetBackgroundColor());
    backDecoration_->SetBlurStyle(newDecoration->GetBlurStyle());
}

void RenderBox::UpdateFrontDecoration(const RefPtr<Decoration>& newDecoration)
{
    if (!newDecoration) {
        frontDecoration_ = newDecoration;
        return;
    }

    if (!frontDecoration_) {
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
            auto lastArea = inspector->GetLastRectAndOrigin();
            if (area != lastArea) {
                eventExtensions_->GetOnAreaChangeExtension()->UpdateArea(
                    area.first, area.second, lastArea.first, lastArea.second);
                inspector->UpdateLastRectAndOrigin(area);
            }
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
        EventReport::SendRenderException(RenderExcepType::VIEW_SCALE_ERR);
        return;
    }
#if !defined(PREVIEW)
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
#endif
}

Offset RenderBox::GetGlobalOffsetExternal() const
{
    auto renderNode = GetParent().Upgrade();
    auto offset = renderNode ? GetPosition() + renderNode->GetGlobalOffsetExternal() : GetPosition();
    offset += alignOffset_;
    return offset;
}

#if defined(PREVIEW)
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
    hoverAnimationType_ = HoverAnimationType::UNKNOWN;
    hoverColor_ = Color::TRANSPARENT;
    for (size_t i = 0; i < recognizers_.size(); i++) {
        recognizers_[i] = nullptr;
    }

    dragDropGesture_ = nullptr;
    parallelRecognizer_ = nullptr;
    preDragDropNode_  = nullptr;
    initialDragDropNode_ = nullptr;
    updateBuilder_ = nullptr;
    onDragStart_ = nullptr;
    onDragEnter_ = nullptr;
    onDragMove_ = nullptr;
    onDragLeave_ = nullptr;
    onDrop_ = nullptr;
    onClick_ = nullptr;
    onLongPress_ = nullptr;
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
        controllerEnter_ = CREATE_ANIMATOR(context_);
    }
    colorAnimationEnter_ = AceType::MakeRefPtr<KeyframeAnimation<Color>>();
    if (hoverAnimationType_ == HoverAnimationType::OPACITY) {
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
        controllerExit_ = CREATE_ANIMATOR(context_);
    }
    colorAnimationExit_ = AceType::MakeRefPtr<KeyframeAnimation<Color>>();
    if (hoverAnimationType_ == HoverAnimationType::OPACITY) {
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
    floatAnimation->AddListener([weakBox = AceType::WeakClaim(this)](float value) {
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
    if (!backDecoration_) {
        backDecoration_ = AceType::MakeRefPtr<Decoration>();
    }
    colorAnimation->AddListener([weakBox = AceType::WeakClaim(this)](const Color& value) {
        auto box = weakBox.Upgrade();
        if (!box) {
            return;
        }
        box->hoverColor_ = value;
        if (box->GetBackDecoration()) {
            box->GetBackDecoration()->SetBackgroundColor(box->hoverColor_);
            box->GetBackDecoration()->SetAnimationColor(box->hoverColor_);
        }
        box->MarkNeedRender();
    });
}

void RenderBox::AnimateMouseHoverEnter()
{
    MouseHoverEnterTest();
}

void RenderBox::MouseHoverEnterTest()
{
    ResetController(controllerExit_);
    if (!controllerEnter_) {
        controllerEnter_ = CREATE_ANIMATOR(context_);
    }
    if (hoverAnimationType_ == HoverAnimationType::SCALE) {
        if (!scaleAnimationEnter_) {
            scaleAnimationEnter_ = AceType::MakeRefPtr<KeyframeAnimation<float>>();
        }
        CreateFloatAnimation(scaleAnimationEnter_, 1.0, 1.05);
        controllerEnter_->ClearInterpolators();
        controllerEnter_->AddInterpolator(scaleAnimationEnter_);
        isHoveredScale_ = true;
    } else if (hoverAnimationType_ == HoverAnimationType::BOARD) {
        if (!backDecoration_) {
            backDecoration_ = AceType::MakeRefPtr<Decoration>();
        }
        if (!colorAnimationEnter_) {
            colorAnimationEnter_ = AceType::MakeRefPtr<KeyframeAnimation<Color>>();
        }
        CreateColorAnimation(colorAnimationEnter_, hoverColorBegin_, Color::FromRGBO(0, 0, 0, 0.05));
        controllerEnter_->ClearInterpolators();
        controllerEnter_->AddInterpolator(colorAnimationEnter_);
        isHoveredBoard_ = true;
    } else {
        return;
    }
    controllerEnter_->SetDuration(HOVER_ANIMATION_DURATION);
    controllerEnter_->SetFillMode(FillMode::FORWARDS);
    controllerEnter_->Play();
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

void RenderBox::AnimateMouseHoverExit()
{
    MouseHoverExitTest();
}

void RenderBox::MouseHoverExitTest()
{
    ResetController(controllerEnter_);
    if (!controllerExit_) {
        controllerExit_ = CREATE_ANIMATOR(context_);
    }
    if (hoverAnimationType_ == HoverAnimationType::SCALE) {
        scaleAnimationExit_ = AceType::MakeRefPtr<KeyframeAnimation<float>>();
        auto begin = scale_;
        CreateFloatAnimation(scaleAnimationExit_, begin, 1.0);
        controllerExit_->ClearInterpolators();
        controllerExit_->AddInterpolator(scaleAnimationExit_);
        isHoveredScale_ = false;
    } else if (hoverAnimationType_ == HoverAnimationType::BOARD) {
        if (!backDecoration_) {
            backDecoration_ = AceType::MakeRefPtr<Decoration>();
        }
        if (!colorAnimationExit_) {
            colorAnimationExit_ = AceType::MakeRefPtr<KeyframeAnimation<Color>>();
        }
        CreateColorAnimation(colorAnimationExit_, hoverColor_, hoverColorBegin_);
        controllerExit_->ClearInterpolators();
        controllerExit_->AddInterpolator(colorAnimationExit_);
        isHoveredBoard_ = false;
    } else {
        return;
    }
    controllerExit_->SetDuration(HOVER_ANIMATION_DURATION);
    controllerExit_->Play();
    controllerExit_->SetFillMode(FillMode::FORWARDS);
}

void RenderBox::HandleMouseHoverEvent(MouseState mouseState)
{
    HoverInfo info = HoverInfo();
    std::string accessibilityEventType;
    if (mouseState == MouseState::HOVER) {
        accessibilityEventType = "mousehoverenter";
    } else {
        accessibilityEventType = "mousehoverexit";
    }
    SendAccessibilityEvent(accessibilityEventType);

    if (onHover_) {
        onHover_(mouseState == MouseState::HOVER, info);
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

bool RenderBox::HandleMouseEvent(const MouseEvent& event)
{
    if (!onMouse_) {
        return false;
    }

    MouseInfo info;
    info.SetButton(event.button);
    info.SetAction(event.action);
    info.SetGlobalLocation(event.GetOffset());
    info.SetLocalLocation(event.GetOffset() - Offset(GetCoordinatePoint().GetX(), GetCoordinatePoint().GetY()));
    info.SetScreenLocation(event.GetScreenOffset());
    info.SetTimeStamp(event.time);
    info.SetDeviceId(event.deviceId);
    info.SetSourceDevice(event.sourceType);
#ifdef LINUX_PLATFORM
    LOGI("RenderBox::HandleMouseEvent: Do mouse callback with mouse event{ Global(%{public}f,%{public}f), "
         "Local(%{public}f,%{public}f)}, Button(%{public}d), Action(%{public}d), "
         "DeviceId(%{public}" PRId64 ", SourceType(%{public}d) }. Return: %{public}d",
        info.GetGlobalLocation().GetX(), info.GetGlobalLocation().GetY(), info.GetLocalLocation().GetX(),
        info.GetLocalLocation().GetY(), info.GetButton(), info.GetAction(),
        info.GetDeviceId(), info.GetSourceDevice(), info.IsStopPropagation());
#else
    LOGI("RenderBox::HandleMouseEvent: Do mouse callback with mouse event{ Global(%{public}f,%{public}f), "
         "Local(%{public}f,%{public}f)}, Button(%{public}d), Action(%{public}d), Time(%{public}lld), "
         ", SourceType(%{public}d) }. Return: %{public}d",
        info.GetGlobalLocation().GetX(), info.GetGlobalLocation().GetY(), info.GetLocalLocation().GetX(),
        info.GetLocalLocation().GetY(), info.GetButton(), info.GetAction(),
        info.GetTimeStamp().time_since_epoch().count(), info.GetSourceDevice(), info.IsStopPropagation());
#endif
    onMouse_(info);
    return info.IsStopPropagation();
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
            recognizers_[i]->SetCoordinateOffset(coordinateOffset);
            result.emplace_back(recognizers_[i]);
        }
    }
}

void RenderBox::OnTouchTestHit(
    const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    AddRecognizerToResult(coordinateOffset, touchRestrict, result);
    if (touchRecognizer_) {
        touchRecognizer_->SetCoordinateOffset(coordinateOffset);
        result.emplace_back(touchRecognizer_);
        MarkIsNotSiblingAddRecognizerToResult(false);
    }
    if (onClick_) {
        onClick_->SetCoordinateOffset(coordinateOffset);
        result.emplace_back(onClick_);
        MarkIsNotSiblingAddRecognizerToResult(true);
    }
    if (onLongPress_ && dragDropGesture_) {
        std::vector<RefPtr<GestureRecognizer>> recognizers { onLongPress_, dragDropGesture_ };
        parallelRecognizer_ = AceType::MakeRefPtr<OHOS::Ace::ParallelRecognizer>(recognizers);
        parallelRecognizer_->SetCoordinateOffset(coordinateOffset);
        result.emplace_back(parallelRecognizer_);
        MarkIsNotSiblingAddRecognizerToResult(true);
        return;
    }
    if (onLongPress_) {
        onLongPress_->SetCoordinateOffset(coordinateOffset);
        result.emplace_back(onLongPress_);
        MarkIsNotSiblingAddRecognizerToResult(true);
    }
    if (dragDropGesture_) {
        dragDropGesture_->SetCoordinateOffset(coordinateOffset);
        result.emplace_back(dragDropGesture_);
        MarkIsNotSiblingAddRecognizerToResult(true);
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

void RenderBox::HandleRemoteMessage(const ClickInfo& clickInfo)
{
    if (remoteMessageEvent_) {
        remoteMessageEvent_(std::make_shared<ClickInfo>(clickInfo));
    }
}

void RenderBox::OnStatusStyleChanged(const VisualState state)
{
    RenderBoxBase::OnStatusStyleChanged(state);

    if (stateAttributeList_ == nullptr) {
        return;
    }

    bool updated = false;
    for (auto& attribute : stateAttributeList_->GetAttributesForState(state)) {
        updated = true;
        switch (attribute->id_) {
            case BoxStateAttribute::COLOR: {
                auto colorState =
                    AceType::DynamicCast<StateAttributeValue<BoxStateAttribute, AnimatableColor>>(attribute);
                GetBackDecoration()->SetBackgroundColor(colorState->value_);
                break;
            }

            case BoxStateAttribute::BORDER_COLOR: {
                auto colorState =
                    AceType::DynamicCast<StateAttributeValue<BoxStateAttribute, AnimatableColor>>(attribute);
                BoxComponentHelper::SetBorderColor(GetBackDecoration(), colorState->value_);
                break;
            }

            case BoxStateAttribute::BORDER_RADIUS: {
                auto radiusState =
                    AceType::DynamicCast<StateAttributeValue<BoxStateAttribute, AnimatableDimension>>(attribute);
                BoxComponentHelper::SetBorderRadius(GetBackDecoration(), radiusState->value_);
                break;
            }

            case BoxStateAttribute::BORDER_STYLE: {
                auto attributeStateValue =
                    AceType::DynamicCast<StateAttributeValue<BoxStateAttribute, BorderStyle>>(attribute);
                BoxComponentHelper::SetBorderStyle(GetBackDecoration(), attributeStateValue->value_);
                break;
            }

            case BoxStateAttribute::BORDER_WIDTH: {
                auto widthState =
                    AceType::DynamicCast<StateAttributeValue<BoxStateAttribute, AnimatableDimension>>(attribute);
                BoxComponentHelper::SetBorderWidth(GetBackDecoration(), widthState->value_);
                break;
            }

            case BoxStateAttribute::HEIGHT: {
                auto valueState = AceType::DynamicCast<StateAttributeValue<BoxStateAttribute, Dimension>>(attribute);
                height_ = valueState->value_;
                break;
            }

            case BoxStateAttribute::WIDTH: {
                auto valueState =
                    AceType::DynamicCast<StateAttributeValue<BoxStateAttribute, AnimatableDimension>>(attribute);
                width_ = valueState->value_;
                break;
            }

            case BoxStateAttribute::ASPECT_RATIO: {
                auto valueState =
                    AceType::DynamicCast<StateAttributeValue<BoxStateAttribute, AnimatableDimension>>(attribute);
                SetAspectRatio(valueState->value_);
                break;
            }

            case BoxStateAttribute::BORDER: {
                // We replace support for border object with updates to border components:
                // color, style, width, radius
                // The reason - developer does not have to provide all border properties
                // when border is set.
                // See JSViewAbstract::JsBorder for details
                break;
            }

            case BoxStateAttribute::GRADIENT: {
                auto gradientState = AceType::DynamicCast<StateAttributeValue<BoxStateAttribute, Gradient>>(attribute);
                GetBackDecoration()->SetGradient(gradientState->value_);
                break;
            }
            default:
                break;
        }
    }
    if (updated) {
        MarkNeedLayout();
    }
};

} // namespace OHOS::Ace
