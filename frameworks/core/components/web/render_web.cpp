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

#include "core/components/web/render_web.h"

#include <cinttypes>
#include <iomanip>
#include <sstream>

#include "base/log/log.h"
#include "core/common/manager_interface.h"
#include "core/components/positioned/positioned_component.h"
#include "core/components/web/resource/web_resource.h"
#include "core/event/ace_events.h"
#include "core/event/ace_event_helper.h"

namespace OHOS::Ace {

constexpr int32_t SINGLE_CLICK_NUM = 1;
constexpr int32_t DOUBLE_CLICK_NUM = 2;
constexpr int32_t DEFAULT_POINT_X = 0;
constexpr int32_t DEFAULT_POINT_Y = 50;
constexpr int32_t DEFAULT_NUMS_ONE = 1;
constexpr double DEFAULT_DBCLICK_INTERVAL = 0.5f;
RenderWeb::RenderWeb() : RenderNode(true)
{
#ifdef OHOS_STANDARD_SYSTEM
    Initialize();
#endif
}

void RenderWeb::OnAttachContext()
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("OnAttachContext context null");
        return;
    }
    if (delegate_) {
        // web component is displayed in full screen by default.
        drawSize_ = Size(pipelineContext->GetRootWidth(), pipelineContext->GetRootHeight());
        drawSizeCache_ = drawSize_;
        position_ = Offset(0, 0);
#ifdef OHOS_STANDARD_SYSTEM
        delegate_->InitOHOSWeb(context_);
#else
        delegate_->CreatePlatformResource(drawSize_, position_, context_);
#endif
    }
}

void RenderWeb::RegistVirtualKeyBoardListener()
{
    if (!needUpdateWeb_) {
        return;
    }
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        return;
    }
    pipelineContext->SetVirtualKeyBoardCallback(
        [weak = AceType::WeakClaim(this)](int32_t width, int32_t height, double keyboard) {
            auto renderWeb = weak.Upgrade();
            if (renderWeb) {
                return renderWeb->ProcessVirtualKeyBoard(width, height, keyboard);
            }
            return false;
        });
    needUpdateWeb_ = false;
}

void RenderWeb::Update(const RefPtr<Component>& component)
{
    const RefPtr<WebComponent> web = AceType::DynamicCast<WebComponent>(component);
    if (!web) {
        LOGE("WebComponent is null");
        return;
    }

    onMouse_ = web->GetOnMouseEventCallback();
    onKeyEvent_ = web->GetOnKeyEventCallback();
    RegistVirtualKeyBoardListener();
    web_ = web;
    if (delegate_) {
        delegate_->SetComponent(web);
        delegate_->UpdateJavaScriptEnabled(web->GetJsEnabled());
        delegate_->UpdateBlockNetworkImage(web->GetOnLineImageAccessEnabled());
        delegate_->UpdateAllowFileAccess(web->GetFileAccessEnabled());
        delegate_->UpdateLoadsImagesAutomatically(web->GetImageAccessEnabled());
        delegate_->UpdateMixedContentMode(web->GetMixedMode());
        delegate_->UpdateSupportZoom(web->GetZoomAccessEnabled());
        delegate_->UpdateDomStorageEnabled(web->GetDomStorageAccessEnabled());
        delegate_->UpdateGeolocationEnabled(web->GetGeolocationAccessEnabled());
        delegate_->UpdateCacheMode(web->GetCacheMode());
        delegate_->UpdateOverviewModeEnabled(web->GetOverviewModeAccessEnabled());
        delegate_->UpdateFileFromUrlEnabled(web->GetFileFromUrlAccessEnabled());
        delegate_->UpdateDatabaseEnabled(web->GetDatabaseAccessEnabled());
        delegate_->UpdateTextZoomRatio(web->GetTextZoomRatio());
        delegate_->UpdateWebDebuggingAccess(web->GetWebDebuggingAccessEnabled());
        delegate_->UpdateMediaPlayGestureAccess(web->IsMediaPlayGestureAccess());
        delegate_->UpdatePinchSmoothModeEnabled(web->GetPinchSmoothModeEnabled());
        auto userAgent = web->GetUserAgent();
        if (!userAgent.empty()) {
            delegate_->UpdateUserAgent(userAgent);
        }
        if (web->GetBackgroundColorEnabled()) {
            delegate_->UpdateBackgroundColor(web->GetBackgroundColor());
        }
        if (web->GetIsInitialScaleSet()) {
            delegate_->UpdateInitialScale(web->GetInitialScale());
        }
        delegate_->SetRenderWeb(AceType::WeakClaim(this));
        onDragStart_ = web->GetOnDragStartId();
        onDragEnter_ = web->GetOnDragEnterId();
        onDragMove_ = web->GetOnDragMoveId();
        onDragLeave_ = web->GetOnDragLeaveId();
        onDrop_ = web->GetOnDropId();
    }
    MarkNeedLayout();
}

bool RenderWeb::ProcessVirtualKeyBoard(int32_t width, int32_t height, double keyboard)
{
    double offsetFix = (height - globlePointPosition_.GetY()) > 100.0 ?
        keyboard - (height - globlePointPosition_.GetY()) / 2.0 : keyboard;
    LOGI("Web ProcessVirtualKeyBoard width=%{public}d height=%{public}d keyboard=%{public}f offsetFix=%{public}f",
        width, height, keyboard, offsetFix);
    if (globlePointPosition_.GetY() <= (height - keyboard) || offsetFix <= 0.0) {
        offsetFix = 0.0;
    }
    if (delegate_) {
        offsetFix_ = offsetFix;
        if (!isFocus_) {
            if (isVirtualKeyBoardShow_ == VkState::VK_SHOW) {
                drawSize_.SetSize(drawSizeCache_);
                delegate_->Resize(drawSize_.Width(), drawSize_.Height());
                SyncGeometryProperties();
                SetRootView(width, height, 0);
                isVirtualKeyBoardShow_ = VkState::VK_HIDE;
            }
            return false;
        }
        if (NearZero(keyboard)) {
            drawSize_.SetSize(drawSizeCache_);
            delegate_->Resize(drawSize_.Width(), drawSize_.Height());
            SyncGeometryProperties();
            SetRootView(width, height, 0);
            isVirtualKeyBoardShow_ = VkState::VK_HIDE;
        } else if (isVirtualKeyBoardShow_ != VkState::VK_SHOW) {
            drawSizeCache_.SetSize(drawSize_);
            if (drawSize_.Height() <= (height - keyboard - GetCoordinatePoint().GetY() + offsetFix)) {
                SetRootView(width, height, -offsetFix);
                isVirtualKeyBoardShow_ = VkState::VK_SHOW;
                return true;
            }
            drawSize_.SetHeight(height - keyboard - GetCoordinatePoint().GetY() + offsetFix);
            delegate_->Resize(drawSize_.Width(), drawSize_.Height());
            SyncGeometryProperties();
            SetRootView(width, height, (NearZero(offsetFix)) ? DEFAULT_NUMS_ONE : -offsetFix);
            isVirtualKeyBoardShow_ = VkState::VK_SHOW;
        }
    }
    return true;
}

void RenderWeb::SetRootView(int32_t width, int32_t height, int32_t offset)
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        return;
    }
    pipelineContext->SetRootRect(width, height, offset);
}

void RenderWeb::SendDoubleClickEvent(const MouseClickInfo& info)
{
    if (!delegate_) {
        LOGE("Touch cancel delegate_ is nullptr");
        return;
    }
    delegate_->OnMouseEvent(info.x,
        info.y, MouseButton::LEFT_BUTTON, MouseAction::PRESS, DOUBLE_CLICK_NUM);
}

bool RenderWeb::HandleDoubleClickEvent(const MouseEvent& event)
{
    if (event.button != MouseButton::LEFT_BUTTON || event.action != MouseAction::PRESS) {
        return false;
    }
    auto localLocation = event.GetOffset() - Offset(GetCoordinatePoint().GetX(), GetCoordinatePoint().GetY());
    MouseClickInfo info;
    info.x = localLocation.GetX();
    info.y = localLocation.GetY();
    info.start = event.time;
    if (doubleClickQueue_.empty()) {
        doubleClickQueue_.push(info);
        return false;
    }
    std::chrono::duration<float> timeout_ = info.start - doubleClickQueue_.back().start;
    if (timeout_.count() < DEFAULT_DBCLICK_INTERVAL) {
        SendDoubleClickEvent(info);
        std::queue<MouseClickInfo> empty;
        swap(empty, doubleClickQueue_);
        return true;
    }
    if (doubleClickQueue_.size() == 1) {
        doubleClickQueue_.push(info);
        return false;
    }
    doubleClickQueue_.pop();
    doubleClickQueue_.push(info);
    return false;
}

void RenderWeb::OnMouseEvent(const MouseEvent& event)
{
    if (!delegate_) {
        LOGE("Delegate_ is nullptr");
        return;
    }

    if (web_ && event.action == MouseAction::RELEASE) {
        LOGI("mouse event request focus");
        web_->RequestFocus();
    }

    auto localLocation = event.GetOffset() - Offset(GetCoordinatePoint().GetX(), GetCoordinatePoint().GetY());
    if (!HandleDoubleClickEvent(event)) { 
        delegate_->OnMouseEvent(localLocation.GetX(), localLocation.GetY(), event.button, event.action, SINGLE_CLICK_NUM);
    }

    // clear the recording position, for not move content when virtual keyboard popup when web get focused.
    if (GetCoordinatePoint().GetY() > 0) {
        webPoint_ = Offset(DEFAULT_POINT_X, DEFAULT_POINT_Y) +
            Offset(GetCoordinatePoint().GetX(), GetCoordinatePoint().GetY());
    }
    auto context = GetContext().Upgrade();
    if (context && context->GetTextFieldManager()) {
        context->GetTextFieldManager()->SetClickPosition(Offset());
        globlePointPosition_ = localLocation + webPoint_;
    }
}

bool RenderWeb::HandleMouseEvent(const MouseEvent& event)
{
    OnMouseEvent(event);
    if (!onMouse_) {
        LOGW("RenderWeb::HandleMouseEvent, Mouse Event is null");
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
    LOGD("RenderWeb::HandleMouseEvent: Do mouse callback with mouse event{ Global(%{public}f,%{public}f), "
         "Local(%{public}f,%{public}f)}, Button(%{public}d), Action(%{public}d), Time(%{public}lld), "
         "DeviceId(%{public}" PRId64 ", SourceType(%{public}d) }. Return: %{public}d",
        info.GetGlobalLocation().GetX(), info.GetGlobalLocation().GetY(), info.GetLocalLocation().GetX(),
        info.GetLocalLocation().GetY(), info.GetButton(), info.GetAction(),
        info.GetTimeStamp().time_since_epoch().count(), info.GetDeviceId(), info.GetSourceDevice(),
        info.IsStopPropagation());
    onMouse_(info);
    return info.IsStopPropagation();
}

void RenderWeb::HandleKeyEvent(const KeyEvent& keyEvent)
{
    if (!onKeyEvent_) {
        LOGW("RenderWeb::HandleKeyEvent, key event callback is null");
        return;
    }
    KeyEventInfo info(keyEvent);
    onKeyEvent_(info);
}

void RenderWeb::PerformLayout()
{
    if (!NeedLayout()) {
        LOGI("RenderWeb::PerformLayout No Need to Layout");
        return;
    }

    // render web do not support child.
    drawSize_ = Size(GetLayoutParam().GetMaxSize().Width(), GetLayoutParam().GetMaxSize().Height());

    SetLayoutSize(drawSize_);
    SetNeedLayout(false);
    MarkNeedRender();
}

#ifdef OHOS_STANDARD_SYSTEM
void RenderWeb::OnAppShow()
{
    RenderNode::OnAppShow();
    if (delegate_) {
        delegate_->ShowWebView();
    }
}

void RenderWeb::OnAppHide()
{
    RenderNode::OnAppHide();
    if (delegate_) {
        delegate_->HideWebView();
    }
}

void RenderWeb::OnPositionChanged()
{
    PopTextOverlay();
}

void RenderWeb::OnSizeChanged()
{
    PopTextOverlay();
}

void RenderWeb::Initialize()
{
    touchRecognizer_ = AceType::MakeRefPtr<RawRecognizer>();
    touchRecognizer_->SetOnTouchDown([weakItem = AceType::WeakClaim(this)](const TouchEventInfo& info) {
        auto item = weakItem.Upgrade();
        if (item) {
            item->HandleTouchDown(info, false);
        }
    });
    touchRecognizer_->SetOnTouchUp([weakItem = AceType::WeakClaim(this)](const TouchEventInfo& info) {
        auto item = weakItem.Upgrade();
        if (item) {
            item->HandleTouchUp(info, false);
        }
    });
    touchRecognizer_->SetOnTouchMove([weakItem = AceType::WeakClaim(this)](const TouchEventInfo& info) {
        auto item = weakItem.Upgrade();
        if (item) {
            item->HandleTouchMove(info, false);
        }
    });
    touchRecognizer_->SetOnTouchCancel([weakItem = AceType::WeakClaim(this)](const TouchEventInfo& info) {
        auto item = weakItem.Upgrade();
        if (item) {
            item->HandleTouchCancel(info);
        }
    });
}

void RenderWeb::HandleTouchDown(const TouchEventInfo& info, bool fromOverlay)
{
    if (!delegate_) {
        LOGE("Touch down delegate_ is nullptr");
        return;
    }
    Offset touchOffset = Offset(0, 0);
    std::list<TouchInfo> touchInfos;
    if (!ParseTouchInfo(info, touchInfos, TouchType::DOWN)) {
        LOGE("Touch down error");
        return;
    }
    for (auto& touchPoint : touchInfos) {
        if (fromOverlay) {
            touchPoint.x -= GetGlobalOffset().GetX();
            touchPoint.y -= GetGlobalOffset().GetY() + offsetFix_;
        }
        touchOffset = Offset(touchPoint.x, touchPoint.y);
        delegate_->HandleTouchDown(touchPoint.id, touchPoint.x, touchPoint.y);
    }
    // clear the recording position, for not move content when virtual keyboard popup when web get focused.
    if (GetCoordinatePoint().GetY() > 0) {
        webPoint_ = Offset(DEFAULT_POINT_X, DEFAULT_POINT_Y) +
            Offset(GetCoordinatePoint().GetX(), GetCoordinatePoint().GetY());
    }
    auto context = GetContext().Upgrade();
    if (context && context->GetTextFieldManager()) {
        context->GetTextFieldManager()->SetClickPosition(Offset());
        globlePointPosition_ = touchOffset + webPoint_;
    }
}

void RenderWeb::HandleTouchUp(const TouchEventInfo& info, bool fromOverlay)
{
    if (!delegate_) {
        LOGE("Touch up delegate_ is nullptr");
        return;
    }
    std::list<TouchInfo> touchInfos;
    if (!ParseTouchInfo(info, touchInfos, TouchType::UP)) {
        LOGE("Touch up error");
        return;
    }
    for (auto& touchPoint : touchInfos) {
        if (fromOverlay) {
            touchPoint.x -= GetGlobalOffset().GetX();
            touchPoint.y -= GetGlobalOffset().GetY() + offsetFix_;
        }
        delegate_->HandleTouchUp(touchPoint.id, touchPoint.x, touchPoint.y);
    }
    if (web_ && !touchInfos.empty()) {
        web_->RequestFocus();
    }
}

void RenderWeb::HandleTouchMove(const TouchEventInfo& info, bool fromOverlay)
{
    if (isDragging_) {
        return;
    }

    if (!delegate_) {
        LOGE("Touch move delegate_ is nullptr");
        return;
    }
    std::list<TouchInfo> touchInfos;
    if (!ParseTouchInfo(info, touchInfos, TouchType::MOVE)) {
        LOGE("Touch move error");
        return;
    }
    for (auto& touchPoint : touchInfos) {
        if (fromOverlay) {
            touchPoint.x -= GetGlobalOffset().GetX();
            touchPoint.y -= GetGlobalOffset().GetY() + offsetFix_;
        }
        delegate_->HandleTouchMove(touchPoint.id, touchPoint.x, touchPoint.y);
    }
}

void RenderWeb::HandleTouchCancel(const TouchEventInfo& info)
{
    if (!delegate_) {
        LOGE("Touch cancel delegate_ is nullptr");
        return;
    }
    delegate_->HandleTouchCancel();
}

bool RenderWeb::ParseTouchInfo(const TouchEventInfo& info, std::list<TouchInfo>& touchInfos, const TouchType& touchType)
{
    auto context = context_.Upgrade();
    if (!context) {
        return false;
    }
    auto viewScale = context->GetViewScale();
    if (touchType == TouchType::DOWN) {
        if (!info.GetTouches().empty()) {
            for (auto& point : info.GetTouches()) {
                TouchInfo touchInfo;
                touchInfo.id = point.GetFingerId();
                Offset location = point.GetLocalLocation();
                touchInfo.x = location.GetX() * viewScale;
                touchInfo.y = location.GetY() * viewScale;
                touchInfos.emplace_back(touchInfo);
            }
        } else {
            return false;
        }
    } else if (touchType == TouchType::MOVE) {
        if (!info.GetChangedTouches().empty()) {
            for (auto& point : info.GetChangedTouches()) {
                TouchInfo touchInfo;
                touchInfo.id = point.GetFingerId();
                Offset location = point.GetLocalLocation();
                touchInfo.x = location.GetX() * viewScale;
                touchInfo.y = location.GetY() * viewScale;
                touchInfos.emplace_back(touchInfo);
            }
        } else {
            return false;
        }
    } else if (touchType == TouchType::UP) {
        if (!info.GetChangedTouches().empty()) {
            for (auto& point : info.GetChangedTouches()) {
                TouchInfo touchInfo;
                touchInfo.id = point.GetFingerId();
                Offset location = point.GetLocalLocation();
                touchInfo.x = location.GetX() * viewScale;
                touchInfo.y = location.GetY() * viewScale;
                touchInfos.emplace_back(touchInfo);
            }
        } else {
            return false;
        }
    }
    return true;
}

void RenderWeb::SetUpdateHandlePosition(
    const std::function<void(const OverlayShowOption&, float, float)>& updateHandlePosition)
{
    updateHandlePosition_ = updateHandlePosition;
}

void RenderWeb::OnTouchTestHit(const Offset& coordinateOffset, const TouchRestrict& touchRestrict,
    TouchTestResult& result)
{
    if (dragDropGesture_) {
        dragDropGesture_->SetCoordinateOffset(coordinateOffset);
        result.emplace_back(dragDropGesture_);
        MarkIsNotSiblingAddRecognizerToResult(true);
    }

    if (!touchRecognizer_) {
        LOGE("TouchTestHit touchRecognizer_ is nullptr");
        return;
    }

    if (touchRestrict.sourceType != SourceType::TOUCH) {
        LOGI("TouchTestHit got invalid source type: %{public}d", touchRestrict.sourceType);
        return;
    }
    touchRecognizer_->SetCoordinateOffset(coordinateOffset);
    result.emplace_back(touchRecognizer_);
}

bool RenderWeb::IsAxisScrollable(AxisDirection direction)
{
    return true;
}

void RenderWeb::HandleAxisEvent(const AxisEvent& event)
{
    if (!delegate_) {
        LOGE("Delegate_ is nullptr");
        return;
    }
    auto localLocation = Offset(event.x, event.y) - Offset(GetCoordinatePoint().GetX(), GetCoordinatePoint().GetY());
    delegate_->HandleAxisEvent(localLocation.GetX(), localLocation.GetY(), event.horizontalAxis, event.verticalAxis);
}

WeakPtr<RenderNode> RenderWeb::CheckAxisNode()
{
    return AceType::WeakClaim<RenderNode>(this);
}

void RenderWeb::PushTextOverlayToStack()
{
    if (!textOverlay_) {
        LOGE("TextOverlay is null");
        return;
    }

    auto context = context_.Upgrade();
    if (!context) {
        LOGE("Context is nullptr");
        return;
    }
    auto lastStack = context->GetLastStack();
    if (!lastStack) {
        LOGE("LastStack is null");
        return;
    }
    lastStack->PushComponent(textOverlay_, false);
    stackElement_ = WeakClaim(RawPtr(lastStack));
}

bool RenderWeb::TextOverlayMenuShouldShow() const
{
    return showTextOveralyMenu_;
}

bool RenderWeb::GetShowStartTouchHandle() const
{
    return showStartTouchHandle_;
}

bool RenderWeb::GetShowEndTouchHandle() const
{
    return showEndTouchHandle_;
}

bool RenderWeb::RunQuickMenu(
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params,
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuCallback> callback)
{
    auto context = context_.Upgrade();
    if (!context || !params || !callback) {
        return false;
    }

    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertTouchHandle =
        params->GetTouchHandleState(OHOS::NWeb::NWebTouchHandleState::TouchHandleType::INSERT_HANDLE);
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> beginTouchHandle =
        params->GetTouchHandleState(OHOS::NWeb::NWebTouchHandleState::TouchHandleType::SELECTION_BEGIN_HANDLE);
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endTouchHandle =
        params->GetTouchHandleState(OHOS::NWeb::NWebTouchHandleState::TouchHandleType::SELECTION_END_HANDLE);
    WebOverlayType overlayType = GetTouchHandleOverlayType(insertTouchHandle,
                                                           beginTouchHandle,
                                                           endTouchHandle);

    if (textOverlay_ || overlayType == INVALID_OVERLAY) {
        PopTextOverlay();
    }
    textOverlay_ = CreateTextOverlay(insertTouchHandle, beginTouchHandle, endTouchHandle);
    if (!textOverlay_) {
        return false;
    }

    showTextOveralyMenu_ = true;
    showStartTouchHandle_ = (overlayType == INSERT_OVERLAY) ?
        IsTouchHandleShow(insertTouchHandle) : IsTouchHandleShow(beginTouchHandle);
    showEndTouchHandle_ = (overlayType == INSERT_OVERLAY) ?
        IsTouchHandleShow(insertTouchHandle) : IsTouchHandleShow(endTouchHandle);

    RegisterTextOverlayCallback(params->GetEditStateFlags(), callback);
    PushTextOverlayToStack();
    return true;
}

void RenderWeb::OnQuickMenuDismissed()
{
    PopTextOverlay();
}

void RenderWeb::PopTextOverlay()
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }

    if (!textOverlay_) {
        LOGE("no need to hide web overlay");
        return;
    }

    const auto& stackElement = stackElement_.Upgrade();
    if (stackElement) {
        stackElement->PopTextOverlay();
    }

    textOverlay_ = nullptr;
    showTextOveralyMenu_ = false;
    showStartTouchHandle_ = false;
    showEndTouchHandle_ = false;
}

void RenderWeb::RegisterTextOverlayCallback(int32_t flags,
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuCallback> callback)
{
    if (!callback || !textOverlay_) {
        return;
    }

    if (flags & OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_CUT) {
        textOverlay_->SetOnCut([weak = AceType::WeakClaim(this), callback] {
            if (callback) {
                callback->Continue(OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_CUT,
                    OHOS::NWeb::MenuEventFlags::EF_LEFT_MOUSE_BUTTON);
            }
        });
    }
    if (flags & OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_COPY) {
        textOverlay_->SetOnCopy([weak = AceType::WeakClaim(this), callback] {
            if (callback) {
                callback->Continue(OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_COPY,
                    OHOS::NWeb::MenuEventFlags::EF_LEFT_MOUSE_BUTTON);
            }
        });
    }
    if (flags & OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_PASTE) {
        textOverlay_->SetOnPaste([weak = AceType::WeakClaim(this), callback] {
            if (callback) {
                callback->Continue(OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_PASTE,
                    OHOS::NWeb::MenuEventFlags::EF_LEFT_MOUSE_BUTTON);
            }
        });
    }
    if (flags & OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_SELECT_ALL) {
        textOverlay_->SetOnCopyAll(
            [weak = AceType::WeakClaim(this), callback]
            (const std::function<void(const Offset&, const Offset&)>& temp) {
                callback->Continue(OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_SELECT_ALL,
                    OHOS::NWeb::MenuEventFlags::EF_LEFT_MOUSE_BUTTON);
            });
    }
}


bool RenderWeb::IsTouchHandleValid(
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> handle)
{
    return (handle != nullptr) && (handle->IsEnable());
}

bool RenderWeb::IsTouchHandleShow(
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> handle)
{
    if (handle->GetAlpha() > 0 &&
        handle->GetY() >= handle->GetEdgeHeight()) {
        return true;
    }
    return false;
}

WebOverlayType RenderWeb::GetTouchHandleOverlayType(
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertHandle,
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> startSelectionHandle,
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endSelectionHandle)
{
    if (IsTouchHandleValid(insertHandle) &&
        !IsTouchHandleValid(startSelectionHandle) &&
        !IsTouchHandleValid(endSelectionHandle)) {
        return INSERT_OVERLAY;
    }

    if (!IsTouchHandleValid(insertHandle) &&
        IsTouchHandleValid(startSelectionHandle) &&
        IsTouchHandleValid(endSelectionHandle)) {
        return SELECTION_OVERLAY;
    }

    return INVALID_OVERLAY;
}

RefPtr<TextOverlayComponent> RenderWeb::CreateTextOverlay(
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertHandle,
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> startSelectionHandle,
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endSelectionHandle)
{
    auto context = context_.Upgrade();
    if (!context) {
        return nullptr;
    }

    WebOverlayType overlayType = GetTouchHandleOverlayType(insertHandle,
                                                           startSelectionHandle,
                                                           endSelectionHandle);
    if (overlayType == INVALID_OVERLAY) {
        return nullptr;
    }

    RefPtr<TextOverlayComponent> textOverlay =
        AceType::MakeRefPtr<TextOverlayComponent>(context->GetThemeManager(), context->GetAccessibilityManager());
    if (!textOverlay) {
        LOGE("textOverlay_ not null or is showing");
        return nullptr;
    }

    Offset startOffset;
    Offset endOffset;
    float startEdgeHeight;
    float endEdgeHeight;
    if (overlayType == INSERT_OVERLAY) {
        float lineHeight = GreatNotEqual(insertHandle->GetEdgeHeight(), insertHandle->GetY()) ?
            insertHandle->GetY() : insertHandle->GetEdgeHeight();
        startOffset = NormalizeTouchHandleOffset(insertHandle->GetX()+1, insertHandle->GetY());
        endOffset = startOffset;
        startEdgeHeight = lineHeight;
        endEdgeHeight = lineHeight;
    } else {
        startOffset = NormalizeTouchHandleOffset(startSelectionHandle->GetX(), startSelectionHandle->GetY());
        endOffset = NormalizeTouchHandleOffset(endSelectionHandle->GetX(), endSelectionHandle->GetY());
        startEdgeHeight = startSelectionHandle->GetEdgeHeight();
        endEdgeHeight = endSelectionHandle->GetEdgeHeight();
    }
    textOverlay->SetWeakWeb(WeakClaim(this));
    textOverlay->SetIsSingleHandle(false);
    Rect clipRect(0.0, 0.0, Size::INFINITE_SIZE, Size::INFINITE_SIZE);
    textOverlay->SetLineHeight(startEdgeHeight);
    textOverlay->SetStartHandleHeight(startEdgeHeight);
    textOverlay->SetEndHandleHeight(endEdgeHeight);
    textOverlay->SetClipRect(clipRect);
    textOverlay->SetNeedCilpRect(false);
    textOverlay->SetStartHandleOffset(startOffset);
    textOverlay->SetEndHandleOffset(endOffset);
    textOverlay->SetTextDirection(TextDirection::LTR);
    textOverlay->SetRealTextDirection(TextDirection::LTR);
    textOverlay->SetContext(context_);
    textOverlay->SetIsUsingMouse(false);
    return textOverlay;
}

Offset RenderWeb::NormalizeTouchHandleOffset(float x, float y)
{
    Offset renderWebOffset = GetGlobalOffset();
    Size renderWebSize = GetLayoutSize();
    float resultX;
    float resultY;
    if (x < 0) {
        resultX = x;
    } else if (x > renderWebSize.Width()) {
        resultX = renderWebOffset.GetX() + renderWebSize.Width();
    } else {
        resultX = x + renderWebOffset.GetX();
    }

    if (y < 0) {
        resultY = renderWebOffset.GetY();
    } else if (y > renderWebSize.Height()) {
        resultY = renderWebOffset.GetY() + renderWebSize.Height();
    } else {
        resultY = y + renderWebOffset.GetY();
    }
    resultY += offsetFix_;
    return {resultX, resultY};
}

void RenderWeb::OnTouchSelectionChanged(
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertHandle,
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> startSelectionHandle,
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endSelectionHandle)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }

    WebOverlayType overlayType = GetTouchHandleOverlayType(insertHandle,
                                                           startSelectionHandle,
                                                           endSelectionHandle);
    if (overlayType == INVALID_OVERLAY) {
        PopTextOverlay();
        return;
    }

    if (!textOverlay_) {
        if (overlayType == INSERT_OVERLAY) {
            showTextOveralyMenu_ = false;
            showStartTouchHandle_ = IsTouchHandleShow(insertHandle);
            showEndTouchHandle_ = IsTouchHandleShow(insertHandle);
            textOverlay_ = CreateTextOverlay(insertHandle, startSelectionHandle, endSelectionHandle);
            PushTextOverlayToStack();
        }
        return;
    }

    if (overlayType == INSERT_OVERLAY) {
        showStartTouchHandle_ = IsTouchHandleShow(insertHandle);
        showEndTouchHandle_ = IsTouchHandleShow(insertHandle);
        float lineHeight = GreatNotEqual(insertHandle->GetEdgeHeight(), insertHandle->GetY()) ?
            insertHandle->GetY() : insertHandle->GetEdgeHeight();
        textOverlay_->SetStartHandleHeight(lineHeight);
        showTextOveralyMenu_ = false;
        OverlayShowOption option {
            .showMenu = showTextOveralyMenu_,
            .isSingleHandle = true,
            .startHandleOffset = NormalizeTouchHandleOffset(insertHandle->GetX() + 1, insertHandle->GetY()),
            .endHandleOffset = NormalizeTouchHandleOffset(insertHandle->GetX() + 1, insertHandle->GetY()),
            .showStartHandle = showStartTouchHandle_,
            .showEndHandle = showEndTouchHandle_,
        };
        if (updateHandlePosition_) {
            updateHandlePosition_(option, lineHeight, lineHeight);
        }
    } else {
        showStartTouchHandle_ = IsTouchHandleShow(startSelectionHandle);
        showEndTouchHandle_ = IsTouchHandleShow(endSelectionHandle);
        textOverlay_->SetStartHandleHeight(startSelectionHandle->GetEdgeHeight());
        textOverlay_->SetEndHandleHeight(endSelectionHandle->GetEdgeHeight());
        OverlayShowOption option {
            .showMenu = true,
            .isSingleHandle = false,
            .startHandleOffset = NormalizeTouchHandleOffset(startSelectionHandle->GetX(), startSelectionHandle->GetY()),
            .endHandleOffset = NormalizeTouchHandleOffset(endSelectionHandle->GetX(), endSelectionHandle->GetY()),
            .showStartHandle = showStartTouchHandle_,
            .showEndHandle = showEndTouchHandle_,
        };
        if (updateHandlePosition_) {
            updateHandlePosition_(option, startSelectionHandle->GetEdgeHeight(), endSelectionHandle->GetEdgeHeight());
        }
    }
}

DragItemInfo RenderWeb::GenerateDragItemInfo(const RefPtr<PipelineContext>& context, const GestureEvent& info)
{
    DragItemInfo itemInfo;
    if (delegate_) {
        itemInfo.pixelMap =  delegate_->GetDragPixelMap();
    }

    if (itemInfo.pixelMap) {
        LOGI("get w3c drag info");
        isW3cDragEvent_ = true;
        return itemInfo;
    }

    if (onDragStart_) {
        LOGI("user has set onDragStart");
        isW3cDragEvent_ = false;
        RefPtr<DragEvent> event = AceType::MakeRefPtr<DragEvent>();
        event->SetX(context->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetX(), DimensionUnit::PX)));
        event->SetY(context->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetY(), DimensionUnit::PX)));
        selectedItemSize_ = GetLayoutSize();
        auto extraParams = JsonUtil::Create(true);
        return onDragStart_(event, extraParams->ToString());
    }

    return itemInfo;
}

void RenderWeb::OnDragWindowStartEvent(RefPtr<PipelineContext> pipelineContext, const GestureEvent& info,
    const DragItemInfo& dragItemInfo)
{
    LOGI("create drag window");
    auto rect = pipelineContext->GetCurrentWindowRect();
    int32_t globalX = static_cast<int32_t>(info.GetGlobalPoint().GetX());
    int32_t globalY = static_cast<int32_t>(info.GetGlobalPoint().GetY());
    dragWindow_ = DragWindow::CreateDragWindow("APP_DRAG_WINDOW", globalX + rect.Left(), globalY + rect.Top(),
        dragItemInfo.pixelMap->GetWidth(), dragItemInfo.pixelMap->GetHeight());
    dragWindow_->SetOffset(rect.Left(), rect.Top());
    dragWindow_->DrawPixelMap(dragItemInfo.pixelMap);
    if (isW3cDragEvent_ && delegate_) {
        LOGI("w3c drag start");
        auto viewScale = pipelineContext->GetViewScale();
        int32_t localX = static_cast<int32_t>(globalX - GetCoordinatePoint().GetX());
        int32_t localY = static_cast<int32_t>(globalY - GetCoordinatePoint().GetY());
        delegate_->HandleDragEvent(localX * viewScale, localY * viewScale, DragAction::DRAG_ENTER);
    }
}

void RenderWeb::PanOnActionStart(const GestureEvent& info)
{
    LOGI("web drag action start");
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("Context is null.");
        return;
    }

    isDragging_ = true;
    GestureEvent newInfo = info;
    newInfo.SetGlobalPoint(startPoint_);
    auto dragItemInfo = GenerateDragItemInfo(pipelineContext, newInfo);
#if !defined(WINDOWS_PLATFORM) and !defined(MAC_PLATFORM)
    if (dragItemInfo.pixelMap) {
        auto initRenderNode = AceType::Claim(this);
        isDragDropNode_  = true;
        pipelineContext->SetInitRenderNode(initRenderNode);
        AddDataToClipboard(pipelineContext, dragItemInfo.extraInfo, "", "");
        if (!dragWindow_) {
            OnDragWindowStartEvent(pipelineContext, info, dragItemInfo);
        }
        return;
    }
#endif
    if (!dragItemInfo.customComponent) {
        LOGW("the drag custom component is null");
        isDragging_ = false;
        return;
    }

    hasDragItem_ = true;
    auto positionedComponent = AceType::MakeRefPtr<PositionedComponent>(dragItemInfo.customComponent);
    positionedComponent->SetTop(Dimension(GetGlobalOffset().GetY()));
    positionedComponent->SetLeft(Dimension(GetGlobalOffset().GetX()));
    SetLocalPoint(info.GetGlobalPoint() - GetGlobalOffset());
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

void RenderWeb::OnDragWindowMoveEvent(RefPtr<PipelineContext> pipelineContext, const GestureEvent& info)
{
    int32_t globalX = static_cast<int32_t>(info.GetGlobalPoint().GetX());
    int32_t globalY = static_cast<int32_t>(info.GetGlobalPoint().GetY());
    LOGD("drag window position update, x = %{public}d, y = %{public}d", globalX, globalY);
    dragWindow_->MoveTo(globalX, globalY);
    if (isW3cDragEvent_ && delegate_) {
        LOGD("w3c drag update");
        auto viewScale = pipelineContext->GetViewScale();
        int32_t localX = static_cast<int32_t>(globalX - GetCoordinatePoint().GetX());
        int32_t localY = static_cast<int32_t>(globalY - GetCoordinatePoint().GetY());
        delegate_->HandleDragEvent(localX * viewScale, localY * viewScale, DragAction::DRAG_OVER);
    }
}

void RenderWeb::PanOnActionUpdate(const GestureEvent& info)
{
    LOGD("web drag action update");
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("Context is null.");
        return;
    }

#if !defined(WINDOWS_PLATFORM) and !defined(MAC_PLATFORM)
    if (isDragDropNode_  && dragWindow_) {
        OnDragWindowMoveEvent(pipelineContext, info);
        return;
    }
#endif

    RefPtr<DragEvent> event = AceType::MakeRefPtr<DragEvent>();
    event->SetX(pipelineContext->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetX(), DimensionUnit::PX)));
    event->SetY(pipelineContext->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetY(), DimensionUnit::PX)));

    Offset offset = info.GetGlobalPoint() - GetLocalPoint();
    if (GetUpdateBuilderFuncId()) {
        GetUpdateBuilderFuncId()(Dimension(offset.GetX()), Dimension(offset.GetY()));
    }

    auto extraParams = JsonUtil::Create(true);
    auto targetDragDropNode = FindDragDropNode(pipelineContext, info);
    auto preDragDropNode = GetPreDragDropNode();
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

void RenderWeb::OnDragWindowDropEvent(RefPtr<PipelineContext> pipelineContext, const GestureEvent& info)
{
    if (GetOnDrop()) {
        RefPtr<DragEvent> event = AceType::MakeRefPtr<DragEvent>();
        RefPtr<PasteData> pasteData = AceType::MakeRefPtr<PasteData>();
        event->SetPasteData(pasteData);
        event->SetX(pipelineContext->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetX(), DimensionUnit::PX)));
        event->SetY(pipelineContext->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetY(), DimensionUnit::PX)));

        auto extraParams = JsonUtil::Create(true);
        (GetOnDrop())(event, extraParams->ToString());
        pipelineContext->SetInitRenderNode(nullptr);
    }

    if (isW3cDragEvent_ && delegate_) {
        LOGI("w3c drag end");
        auto viewScale = pipelineContext->GetViewScale();
        int32_t localX = static_cast<int32_t>(info.GetGlobalPoint().GetX() - GetCoordinatePoint().GetX());
        int32_t localY = static_cast<int32_t>(info.GetGlobalPoint().GetY() - GetCoordinatePoint().GetY());
        delegate_->HandleDragEvent(localX * viewScale, localY * viewScale, DragAction::DRAG_DROP);
        delegate_->HandleDragEvent(localX * viewScale, localY * viewScale, DragAction::DRAG_END);
    }
}

void RenderWeb::PanOnActionEnd(const GestureEvent& info)
{
    LOGI("web drag action end");
    isDragging_ = false;
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("Context is null.");
        return;
    }
#if !defined(WINDOWS_PLATFORM) and !defined(MAC_PLATFORM)
    if (isDragDropNode_) {
        isDragDropNode_  = false;
        RestoreCilpboardData(pipelineContext);
        OnDragWindowDropEvent(pipelineContext, info);
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

    ACE_DCHECK(GetPreDragDropNode() == FindTargetRenderNode<DragDropEvent>(pipelineContext, info));
    auto targetDragDropNode = GetPreDragDropNode();
    if (!targetDragDropNode) {
        return;
    }
    if (targetDragDropNode->GetOnDrop()) {
        auto extraParams = JsonUtil::Create(true);
        (targetDragDropNode->GetOnDrop())(event, extraParams->ToString());
    }
    SetPreDragDropNode(nullptr);
}

void RenderWeb::PanOnActionCancel()
{
    LOGI("drag cancel");
    isDragging_ = false;
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("Context is null.");
        return;
    }

#if !defined(WINDOWS_PLATFORM) and !defined(MAC_PLATFORM)
    if (isDragDropNode_) {
        RestoreCilpboardData(pipelineContext);
        isDragDropNode_ = false;
        if (isW3cDragEvent_ && delegate_) {
            LOGI("w3c drag cancel");
            delegate_->HandleDragEvent(0, 0, DragAction::DRAG_CANCEL);
        }
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
#endif
} // namespace OHOS::Ace
