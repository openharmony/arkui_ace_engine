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

#include <iomanip>
#include <sstream>

#include "base/log/log.h"
#include "base/mousestyle/mouse_style.h"
#include "base/utils/linear_map.h"
#include "base/utils/utils.h"
#include "core/common/manager_interface.h"
#include "core/components/positioned/positioned_component.h"
#include "core/components/web/resource/web_resource.h"
#include "core/event/ace_events.h"
#include "core/event/ace_event_helper.h"

namespace OHOS::Ace {
namespace {
const LinearEnumMapNode<OHOS::NWeb::CursorType, MouseFormat> g_cursorTypeMap[] = {
    { OHOS::NWeb::CursorType::CT_CROSS, MouseFormat::CROSS },
    { OHOS::NWeb::CursorType::CT_HAND, MouseFormat::HAND_POINTING },
    { OHOS::NWeb::CursorType::CT_IBEAM, MouseFormat::TEXT_CURSOR },
    { OHOS::NWeb::CursorType::CT_HELP, MouseFormat::HELP },
    { OHOS::NWeb::CursorType::CT_EASTRESIZE, MouseFormat::WEST_EAST },
    { OHOS::NWeb::CursorType::CT_NORTHRESIZE, MouseFormat::NORTH_SOUTH },
    { OHOS::NWeb::CursorType::CT_NORTHEASTRESIZE, MouseFormat::NORTH_EAST_SOUTH_WEST },
    { OHOS::NWeb::CursorType::CT_NORTHWESTRESIZE, MouseFormat::NORTH_WEST_SOUTH_EAST },
    { OHOS::NWeb::CursorType::CT_SOUTHRESIZE, MouseFormat::NORTH_SOUTH },
    { OHOS::NWeb::CursorType::CT_SOUTHEASTRESIZE, MouseFormat::NORTH_WEST_SOUTH_EAST },
    { OHOS::NWeb::CursorType::CT_SOUTHWESTRESIZE, MouseFormat::NORTH_EAST_SOUTH_WEST },
    { OHOS::NWeb::CursorType::CT_WESTRESIZE, MouseFormat::WEST_EAST },
    { OHOS::NWeb::CursorType::CT_NORTHSOUTHRESIZE, MouseFormat::NORTH_SOUTH },
    { OHOS::NWeb::CursorType::CT_EASTWESTRESIZE, MouseFormat::WEST_EAST },
    { OHOS::NWeb::CursorType::CT_NORTHEASTSOUTHWESTRESIZE, MouseFormat::NORTH_EAST_SOUTH_WEST },
    { OHOS::NWeb::CursorType::CT_NORTHWESTSOUTHEASTRESIZE, MouseFormat::NORTH_WEST_SOUTH_EAST },
    { OHOS::NWeb::CursorType::CT_COLUMNRESIZE, MouseFormat::RESIZE_LEFT_RIGHT },
    { OHOS::NWeb::CursorType::CT_ROWRESIZE, MouseFormat::RESIZE_UP_DOWN },
    { OHOS::NWeb::CursorType::CT_MIDDLEPANNING, MouseFormat::MIDDLE_BTN_NORTH_SOUTH_WEST_EAST },
    { OHOS::NWeb::CursorType::CT_EASTPANNING, MouseFormat::MIDDLE_BTN_EAST },
    { OHOS::NWeb::CursorType::CT_NORTHPANNING, MouseFormat::MIDDLE_BTN_NORTH },
    { OHOS::NWeb::CursorType::CT_NORTHEASTPANNING, MouseFormat::MIDDLE_BTN_NORTH_EAST },
    { OHOS::NWeb::CursorType::CT_NORTHWESTPANNING, MouseFormat::MIDDLE_BTN_NORTH_WEST },
    { OHOS::NWeb::CursorType::CT_SOUTHPANNING, MouseFormat::MIDDLE_BTN_SOUTH },
    { OHOS::NWeb::CursorType::CT_SOUTHEASTPANNING, MouseFormat::MIDDLE_BTN_SOUTH_EAST },
    { OHOS::NWeb::CursorType::CT_SOUTHWESTPANNING, MouseFormat::MIDDLE_BTN_SOUTH_WEST },
    { OHOS::NWeb::CursorType::CT_WESTPANNING, MouseFormat::MIDDLE_BTN_WEST },
    { OHOS::NWeb::CursorType::CT_MOVE, MouseFormat::CURSOR_MOVE },
    { OHOS::NWeb::CursorType::CT_NODROP, MouseFormat::CURSOR_FORBID },
    { OHOS::NWeb::CursorType::CT_COPY, MouseFormat::CURSOR_COPY },
    { OHOS::NWeb::CursorType::CT_NOTALLOWED, MouseFormat::CURSOR_FORBID },
    { OHOS::NWeb::CursorType::CT_ZOOMIN, MouseFormat::ZOOM_IN },
    { OHOS::NWeb::CursorType::CT_ZOOMOUT, MouseFormat::ZOOM_OUT },
    { OHOS::NWeb::CursorType::CT_GRAB, MouseFormat::HAND_OPEN },
    { OHOS::NWeb::CursorType::CT_GRABBING, MouseFormat::HAND_GRABBING },
    { OHOS::NWeb::CursorType::CT_MIDDLE_PANNING_VERTICAL, MouseFormat::MIDDLE_BTN_NORTH_SOUTH },
    { OHOS::NWeb::CursorType::CT_MIDDLE_PANNING_HORIZONTAL, MouseFormat::MIDDLE_BTN_NORTH_SOUTH_WEST_EAST },
};
} // namespace

constexpr int32_t SINGLE_CLICK_NUM = 1;
constexpr int32_t DOUBLE_CLICK_NUM = 2;
constexpr int32_t DEFAULT_NUMS_ONE = 1;
constexpr double DEFAULT_DBCLICK_INTERVAL = 0.5f;
constexpr double DEFAULT_AXIS_RATIO = -0.06f;

RenderWeb::RenderWeb() : RenderNode(true)
{
#ifdef OHOS_STANDARD_SYSTEM
    InitEnhanceSurfaceFlag();
    Initialize();
#endif
}

void RenderWeb::InitEnhanceSurfaceFlag()
{
    if (SystemProperties::GetExtSurfaceEnabled()) {
        isEnhanceSurface_ = true;
    } else {
        isEnhanceSurface_ = false;
    }
}

void RenderWeb::OnAttachContext()
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        return;
    }
    if (delegate_) {
        // web component is displayed in full screen by default.
        drawSize_ = Size(pipelineContext->GetRootWidth(), pipelineContext->GetRootHeight());
        drawSizeCache_ = drawSize_;
        position_ = Offset(0, 0);
        delegate_->SetEnhanceSurfaceFlag(isEnhanceSurface_);
        delegate_->SetDrawSize(drawSize_);
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
        [weak = AceType::WeakClaim(this)](int32_t width, int32_t height, double keyboard, bool isCustomKeyboard) {
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
        return;
    }

    onMouse_ = web->GetOnMouseEventCallback();
    onKeyEvent_ = web->GetOnKeyEventCallback();
    onPreKeyEvent_ = web->GetOnInterceptKeyEventCallback();
    RegistVirtualKeyBoardListener();
#ifdef OHOS_STANDARD_SYSTEM
    InitPanEvent();
#endif
    web_ = web;
    if (delegate_) {
        delegate_->SetComponent(web);
        UpdateDelegate();
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

void RenderWeb::UpdateDelegate()
{
    delegate_->UpdateJavaScriptEnabled(web_->GetJsEnabled());
    delegate_->UpdateBlockNetworkImage(web_->GetOnLineImageAccessEnabled());
    delegate_->UpdateAllowFileAccess(web_->GetFileAccessEnabled());
    delegate_->UpdateLoadsImagesAutomatically(web_->GetImageAccessEnabled());
    delegate_->UpdateMixedContentMode(web_->GetMixedMode());
    delegate_->UpdateSupportZoom(web_->GetZoomAccessEnabled());
    delegate_->UpdateDomStorageEnabled(web_->GetDomStorageAccessEnabled());
    delegate_->UpdateGeolocationEnabled(web_->GetGeolocationAccessEnabled());
    delegate_->UpdateCacheMode(web_->GetCacheMode());
    delegate_->UpdateOverviewModeEnabled(web_->GetOverviewModeAccessEnabled());
    delegate_->UpdateFileFromUrlEnabled(web_->GetFileFromUrlAccessEnabled());
    delegate_->UpdateDatabaseEnabled(web_->GetDatabaseAccessEnabled());
    delegate_->UpdateTextZoomRatio(web_->GetTextZoomRatio());
    delegate_->UpdateWebDebuggingAccess(web_->GetWebDebuggingAccessEnabled());
    delegate_->UpdateMediaPlayGestureAccess(web_->IsMediaPlayGestureAccess());
    delegate_->UpdatePinchSmoothModeEnabled(web_->GetPinchSmoothModeEnabled());
    delegate_->UpdateMultiWindowAccess(web_->GetMultiWindowAccessEnabled());
    delegate_->UpdateAllowWindowOpenMethod(web_->GetAllowWindowOpenMethod());
    delegate_->UpdateNativeVideoPlayerConfig(
        std::get<0>(web_->GetNativeVideoPlayerConfig()),
        std::get<1>(web_->GetNativeVideoPlayerConfig()));
}

bool RenderWeb::ProcessVirtualKeyBoard(int32_t width, int32_t height, double keyboard)
{
    if (delegate_) {
        offsetFix_ = 0;
        if (!isFocus_) {
            if (isVirtualKeyBoardShow_ == VkState::VK_SHOW) {
                drawSize_.SetSize(drawSizeCache_);
                delegate_->SetBoundsOrResize(drawSize_, GetGlobalOffset());
                SyncGeometryProperties();
                SetRootView(width, height, 0);
                isVirtualKeyBoardShow_ = VkState::VK_HIDE;
            }
            return false;
        }
        if (NearZero(keyboard)) {
            drawSize_.SetSize(drawSizeCache_);
            delegate_->SetBoundsOrResize(drawSize_, GetGlobalOffset());
            SyncGeometryProperties();
            SetRootView(width, height, 0);
            isVirtualKeyBoardShow_ = VkState::VK_HIDE;
        } else if (isVirtualKeyBoardShow_ != VkState::VK_SHOW) {
            drawSizeCache_.SetSize(drawSize_);
            if (drawSize_.Height() <= (height - keyboard - GetCoordinatePoint().GetY())) {
                SetRootView(width, height, 0);
                isVirtualKeyBoardShow_ = VkState::VK_SHOW;
                return true;
            }
            if (height - GetCoordinatePoint().GetY() < keyboard) {
                return true;
            }
            drawSize_.SetHeight(height - keyboard - GetCoordinatePoint().GetY());
            delegate_->SetBoundsOrResize(drawSize_, GetGlobalOffset());
            SyncGeometryProperties();
            SetRootView(width, height, DEFAULT_NUMS_ONE);
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
        return;
    }

    if (web_ && event.action == MouseAction::RELEASE) {
        web_->RequestFocus();
    }

    auto localLocation = event.GetOffset() - Offset(GetCoordinatePoint().GetX(), GetCoordinatePoint().GetY());
    if (!HandleDoubleClickEvent(event)) {
        delegate_->OnMouseEvent(localLocation.GetX(),
            localLocation.GetY(), event.button, event.action, SINGLE_CLICK_NUM);
    }

    // clear the recording position, for not move content when virtual keyboard popup when web get focused.
    auto context = GetContext().Upgrade();
    if (context && context->GetTextFieldManager()) {
        context->GetTextFieldManager()->SetClickPosition(Offset());
    }
}

bool RenderWeb::HandleMouseEvent(const MouseEvent& event)
{
    OnMouseEvent(event);
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
    onMouse_(info);
    return info.IsStopPropagation();
}

bool RenderWeb::HandleKeyEvent(const KeyEvent& keyEvent)
{
    KeyEventInfo info(keyEvent);
    if (onKeyEvent_) {
        onKeyEvent_(info);
    }
    if (onPreKeyEvent_) {
        return onPreKeyEvent_(info);
    }
    return false;
}

void RenderWeb::PerformLayout()
{
    if (!NeedLayout()) {
        return;
    }

    // render web do not support child.
    drawSize_ = Size(GetLayoutParam().GetMaxSize().Width(), GetLayoutParam().GetMaxSize().Height());
    drawSizeCache_ = drawSize_;
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
    needOnFocus_ = false;
    if (delegate_) {
        delegate_->HideWebView();
    }
}

void RenderWeb::OnGlobalPositionChanged()
{
    UpdateGlobalPos();
    if (!textOverlay_ || !updateHandlePosition_) {
        return;
    }
    OnTouchSelectionChanged(insertHandle_, startSelectionHandle_, endSelectionHandle_);
}

void RenderWeb::OnPositionChanged()
{
    PopTextOverlay();
}

void RenderWeb::OnSizeChanged()
{
    if (drawSize_.IsWidthInfinite() || drawSize_.IsHeightInfinite() ||
        drawSize_.Width() == 0 || drawSize_.Height() == 0) {
        return;
    }
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    UpdateGlobalPos();
    if (delegate_ && !isUrlLoaded_) {
        delegate_->SetBoundsOrResize(drawSize_, GetGlobalOffset());
        if (!delegate_->LoadDataWithRichText()) {
            delegate_->LoadUrl();
        }
        isUrlLoaded_ = true;
    }
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

void RenderWeb::InitPanEvent()
{
    auto context = context_.Upgrade();
    if (panRecognizer_ || !context) {
        return;
    }
    PanDirection panDirection;
    panDirection.type = PanDirection::VERTICAL;
    panRecognizer_ = AceType::MakeRefPtr<PanRecognizer>(
        context, DEFAULT_PAN_FINGER, panDirection, DEFAULT_PAN_DISTANCE.ConvertToPx());
    panRecognizer_->SetOnActionUpdate([weakItem = AceType::WeakClaim(this)](const GestureEvent& event) {
        auto item = weakItem.Upgrade();
        if (item) {
            item->HandleDragMove(event);
        }
    });
}

void RenderWeb::HandleDragMove(const GestureEvent& event)
{
    if (event.GetInputEventType() == InputEventType::AXIS) {
        if (!delegate_) {
            return;
        }
        auto localLocation = event.GetLocalLocation();
        delegate_->HandleAxisEvent(
            localLocation.GetX(), localLocation.GetY(),
            event.GetDelta().GetX() * DEFAULT_AXIS_RATIO,
            event.GetDelta().GetY() * DEFAULT_AXIS_RATIO);
    }
}

void RenderWeb::HandleTouchDown(const TouchEventInfo& info, bool fromOverlay)
{
    if (!delegate_) {
        return;
    }
    Offset touchOffset = Offset(0, 0);
    std::list<TouchInfo> touchInfos;
    if (!ParseTouchInfo(info, touchInfos, TouchType::DOWN)) {
        TAG_LOGW(AceLogTag::ACE_WEB, "Parse touch event down failed, This event will not be handled.");
        return;
    }
    for (auto& touchPoint : touchInfos) {
        if (fromOverlay) {
            touchPoint.x -= GetGlobalOffset().GetX();
            touchPoint.y -= GetGlobalOffset().GetY() + offsetFix_;
        }
        touchOffset = Offset(touchPoint.x, touchPoint.y);
        delegate_->HandleTouchDown(touchPoint.id, touchPoint.x, touchPoint.y, fromOverlay);
    }
    // clear the recording position, for not move content when virtual keyboard popup when web get focused.
    auto context = GetContext().Upgrade();
    if (context && context->GetTextFieldManager()) {
        context->GetTextFieldManager()->SetClickPosition(Offset());
    }
}

void RenderWeb::HandleTouchUp(const TouchEventInfo& info, bool fromOverlay)
{
    if (!delegate_) {
        return;
    }
    std::list<TouchInfo> touchInfos;
    if (!ParseTouchInfo(info, touchInfos, TouchType::UP)) {
        TAG_LOGW(AceLogTag::ACE_WEB, "Parse touch event up failed, This event will not be handled.");
        return;
    }
    for (auto& touchPoint : touchInfos) {
        if (fromOverlay) {
            touchPoint.x -= GetGlobalOffset().GetX();
            touchPoint.y -= GetGlobalOffset().GetY() + offsetFix_;
        }
        delegate_->HandleTouchUp(touchPoint.id, touchPoint.x, touchPoint.y, fromOverlay);
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
        return;
    }
    std::list<TouchInfo> touchInfos;
    if (!ParseTouchInfo(info, touchInfos, TouchType::MOVE)) {
        return;
    }
    for (auto& touchPoint : touchInfos) {
        if (fromOverlay) {
            touchPoint.x -= GetGlobalOffset().GetX();
            touchPoint.y -= GetGlobalOffset().GetY() + offsetFix_;
        }
        delegate_->HandleTouchMove(touchPoint.id, touchPoint.x, touchPoint.y, fromOverlay);
    }
}

void RenderWeb::HandleTouchCancel(const TouchEventInfo& info)
{
    if (!delegate_) {
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

    if (panRecognizer_) {
        panRecognizer_->SetCoordinateOffset(coordinateOffset);
        result.emplace_back(panRecognizer_);
    }

    if (!touchRecognizer_) {
        return;
    }

    if (touchRestrict.sourceType != SourceType::TOUCH) {
        return;
    }
    touchRecognizer_->SetCoordinateOffset(coordinateOffset);
    result.emplace_back(touchRecognizer_);
}

bool RenderWeb::IsAxisScrollable(AxisDirection direction)
{
    return true;
}

WeakPtr<RenderNode> RenderWeb::CheckAxisNode()
{
    return AceType::WeakClaim<RenderNode>(this);
}

void RenderWeb::PushTextOverlayToStack()
{
    if (!textOverlay_) {
        return;
    }

    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    auto lastStack = context->GetLastStack();
    if (!lastStack) {
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
    insertHandle_ = insertTouchHandle;
    startSelectionHandle_ = beginTouchHandle;
    endSelectionHandle_ = endTouchHandle;
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
        GreatOrEqual(handle->GetY(), static_cast<int32_t>(handle->GetEdgeHeight())) &&
        GreatNotEqual(GetLayoutSize().Height(), handle->GetY())) {
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
    insertHandle_ = insertHandle;
    startSelectionHandle_ = startSelectionHandle;
    endSelectionHandle_ = endSelectionHandle;
    if (overlayType == INVALID_OVERLAY) {
        PopTextOverlay();
        return;
    }

    if (!textOverlay_) {
        if (overlayType == INSERT_OVERLAY) {
            showTextOveralyMenu_ = false;
            showStartTouchHandle_ = IsTouchHandleShow(insertHandle);
            showEndTouchHandle_ = IsTouchHandleShow(insertHandle);
            if (!showStartTouchHandle_) {
                return;
            }
            textOverlay_ = CreateTextOverlay(insertHandle, startSelectionHandle, endSelectionHandle);
            PushTextOverlayToStack();
        }
        return;
    }

    if (overlayType == INSERT_OVERLAY) {
        showStartTouchHandle_ = IsTouchHandleShow(insertHandle);
        showEndTouchHandle_ = IsTouchHandleShow(insertHandle);
        if (!showStartTouchHandle_) {
            PopTextOverlay();
            return;
        }
        float lineHeight = GreatNotEqual(insertHandle->GetEdgeHeight(), insertHandle->GetY()) ?
            insertHandle->GetY() : insertHandle->GetEdgeHeight();
        textOverlay_->SetStartHandleHeight(lineHeight);
        showTextOveralyMenu_ = false;
        OverlayShowOption option {
            .showMenu = showTextOveralyMenu_,
            .showStartHandle = showStartTouchHandle_,
            .showEndHandle = showEndTouchHandle_,
            .isSingleHandle = true,
            .startHandleOffset = NormalizeTouchHandleOffset(insertHandle->GetX() + 1, insertHandle->GetY()),
            .endHandleOffset = NormalizeTouchHandleOffset(insertHandle->GetX() + 1, insertHandle->GetY()),
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
            .showStartHandle = showStartTouchHandle_,
            .showEndHandle = showEndTouchHandle_,
            .isSingleHandle = false,
            .startHandleOffset = NormalizeTouchHandleOffset(startSelectionHandle->GetX(), startSelectionHandle->GetY()),
            .endHandleOffset = NormalizeTouchHandleOffset(endSelectionHandle->GetX(), endSelectionHandle->GetY()),
        };
        if (updateHandlePosition_) {
            updateHandlePosition_(option, startSelectionHandle->GetEdgeHeight(), endSelectionHandle->GetEdgeHeight());
        }
    }
}

bool RenderWeb::OnCursorChange(const OHOS::NWeb::CursorType& type, std::shared_ptr<OHOS::NWeb::NWebCursorInfo> info)
{
    (void)info;
    auto context = GetContext().Upgrade();
    if (!context) {
        return false;
    }
    auto windowId = context->GetWindowId();
    auto mouseStyle = MouseStyle::CreateMouseStyle();
    int32_t curPointerStyle = 0;
    if (mouseStyle->GetPointerStyle(windowId, curPointerStyle) == -1) {
        return false;
    }
    MouseFormat pointStyle = MouseFormat::DEFAULT;
    int64_t idx = BinarySearchFindIndex(g_cursorTypeMap, ArraySize(g_cursorTypeMap), type);
    if (idx >= 0) {
        pointStyle = g_cursorTypeMap[idx].value;
    }
    if ((int32_t)pointStyle != curPointerStyle) {
        mouseStyle->SetPointerStyle(windowId, pointStyle);
    }
    return true;
}

DragItemInfo RenderWeb::GenerateDragItemInfo(const RefPtr<PipelineContext>& context, const GestureEvent& info)
{
    DragItemInfo itemInfo;
    if (delegate_) {
        itemInfo.pixelMap =  delegate_->GetDragPixelMap();
    }

    if (itemInfo.pixelMap) {
        isW3cDragEvent_ = true;
        return itemInfo;
    }

    if (onDragStart_) {
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
    auto rect = pipelineContext->GetCurrentWindowRect();
    int32_t globalX = static_cast<int32_t>(info.GetGlobalPoint().GetX());
    int32_t globalY = static_cast<int32_t>(info.GetGlobalPoint().GetY());
    dragWindow_ = DragWindow::CreateDragWindow("APP_DRAG_WINDOW", globalX + rect.Left(), globalY + rect.Top(),
        dragItemInfo.pixelMap->GetWidth(), dragItemInfo.pixelMap->GetHeight());
    dragWindow_->SetOffset(rect.Left(), rect.Top());
    dragWindow_->DrawPixelMap(dragItemInfo.pixelMap);
    if (isW3cDragEvent_ && delegate_) {
        auto viewScale = pipelineContext->GetViewScale();
        int32_t localX = static_cast<int32_t>(globalX - GetCoordinatePoint().GetX());
        int32_t localY = static_cast<int32_t>(globalY - GetCoordinatePoint().GetY());
        delegate_->HandleDragEvent(localX * viewScale, localY * viewScale, DragAction::DRAG_ENTER);
    }
}

void RenderWeb::PanOnActionStart(const GestureEvent& info)
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
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
    dragWindow_->MoveTo(globalX, globalY);
    if (isW3cDragEvent_ && delegate_) {
        auto viewScale = pipelineContext->GetViewScale();
        int32_t localX = static_cast<int32_t>(globalX - GetCoordinatePoint().GetX());
        int32_t localY = static_cast<int32_t>(globalY - GetCoordinatePoint().GetY());
        delegate_->HandleDragEvent(localX * viewScale, localY * viewScale, DragAction::DRAG_OVER);
    }
}

void RenderWeb::PanOnActionUpdate(const GestureEvent& info)
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
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
        auto viewScale = pipelineContext->GetViewScale();
        int32_t localX = static_cast<int32_t>(info.GetGlobalPoint().GetX() - GetCoordinatePoint().GetX());
        int32_t localY = static_cast<int32_t>(info.GetGlobalPoint().GetY() - GetCoordinatePoint().GetY());
        delegate_->HandleDragEvent(localX * viewScale, localY * viewScale, DragAction::DRAG_DROP);
        delegate_->HandleDragEvent(localX * viewScale, localY * viewScale, DragAction::DRAG_END);
    }
}

void RenderWeb::PanOnActionEnd(const GestureEvent& info)
{
    isDragging_ = false;
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
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

void RenderWeb::PanOnActionCancel(const GestureEvent& info)
{
    isDragging_ = false;
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        return;
    }

#if !defined(WINDOWS_PLATFORM) and !defined(MAC_PLATFORM)
    if (isDragDropNode_) {
        RestoreCilpboardData(pipelineContext);
        isDragDropNode_ = false;
        if (isW3cDragEvent_ && delegate_) {
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

void RenderWeb::UpdateGlobalPos()
{
    auto position = GetGlobalOffset();
    if (delegate_) {
        delegate_->SetWebRendeGlobalPos(position);
    }
}

RefPtr<OptionComponent> RenderWeb::BuildSelectMenu(const std::string& value)
{
    auto context = context_.Upgrade();
    if (!context) {
        return nullptr;
    }
    if (!themeManager_) {
        themeManager_ = context->GetThemeManager();
    }
    if (!accessibilityManager_) {
        accessibilityManager_ = context->GetAccessibilityManager();
    }
    auto optionComponent = AceType::MakeRefPtr<OptionComponent>();
    if (!optionComponent) {
        return nullptr;
    }
    optionComponent->SetNeedDrawDividerLine(false);
    auto textComponent = AceType::MakeRefPtr<TextComponent>(value);
    optionComponent->SetText(textComponent);
    optionComponent->SetValue(value);
    optionComponent->InitTheme(themeManager_);
    optionComponent->Initialize(accessibilityManager_);
    return optionComponent;
}

void RenderWeb::OnSelectPopupMenu(
    std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuParam> params,
    std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuCallback> callback)
{
    auto context = context_.Upgrade();
    if (!context || !params || !callback) {
        return;
    }
    const auto pipeline = context_.Upgrade();
    if (!pipeline) {
        return;
    }
    auto stackElement = pipeline->GetLastStack();
    if (!stackElement) {
        return;
    }
    popup_ = AceType::MakeRefPtr<SelectPopupComponent>();
    auto themeManager = context->GetThemeManager();
    popup_->InitTheme(themeManager);
    std::vector<std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuItem>> menuItems = params->GetMenuItems();
    for (size_t index = 0; index < menuItems.size(); index++) {
        RefPtr<OptionComponent> option = BuildSelectMenu(menuItems[index]->GetLabel());
        if (!option) {
            continue;
        }
        popup_->AppendSelectOption(option);
        if (index == static_cast<uint32_t>(params->GetSelectedItem())) {
            option->SetSelected(true);
        }
    }
    popup_->SetOptionClickedCallback([callback](std::size_t index) {
        std::vector<int32_t> indices { static_cast<int32_t>(index) };
        callback->Continue(indices);
    });
    popup_->SetPopupCanceledCallback([callback]() {
        callback->Cancel();
    });

    std::shared_ptr<OHOS::NWeb::NWebSelectMenuBound> bound = params->GetSelectMenuBound();
    if (bound) {
        Offset leftTop = { bound->GetX() + GetGlobalOffset().GetX(),
                           bound->GetY() + GetGlobalOffset().GetY() };
        Offset rightBottom = { bound->GetX() + GetGlobalOffset().GetX() + bound->GetWidth(),
                               bound->GetY() + GetGlobalOffset().GetY() + bound->GetHeight() };
        popup_->ShowDialog(stackElement, leftTop, rightBottom, false);
    } else {
        Offset leftTop = { GetGlobalOffset().GetX(), GetGlobalOffset().GetY() };
        Offset rightBottom = { GetGlobalOffset().GetX(), GetGlobalOffset().GetY() };
        popup_->ShowDialog(stackElement, leftTop, rightBottom, false);
    }
}
#endif
} // namespace OHOS::Ace
