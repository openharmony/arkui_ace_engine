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
#include "core/components/web/resource/web_resource.h"
#include "core/event/ace_events.h"
#include "core/event/ace_event_helper.h"

namespace OHOS::Ace {

constexpr int32_t DEFAULT_POINT_X = 0;
constexpr int32_t DEFAULT_POINT_Y = 50;
constexpr int32_t DEFAULT_NUMS_ONE = 1;

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
        delegate_->UpdateTextZoomAtio(web->GetTextZoomAtio());
        delegate_->UpdateWebDebuggingAccess(web->GetWebDebuggingAccessEnabled());
        delegate_->UpdateMediaPlayGestureAccess(web->IsMediaPlayGestureAccess());
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

void RenderWeb::OnMouseEvent(const MouseEvent& event)
{
    if (!delegate_) {
        LOGE("Delegate_ is nullptr");
        return;
    }

    auto localLocation = event.GetOffset() - Offset(GetCoordinatePoint().GetX(), GetCoordinatePoint().GetY());
    delegate_->OnMouseEvent(localLocation.GetX(), localLocation.GetY(), event.button, event.action);

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
void RenderWeb::Initialize()
{
    touchRecognizer_ = AceType::MakeRefPtr<RawRecognizer>();
    touchRecognizer_->SetOnTouchDown([weakItem = AceType::WeakClaim(this)](const TouchEventInfo& info) {
        auto item = weakItem.Upgrade();
        if (item) {
            item->HandleTouchDown(info);
        }
    });
    touchRecognizer_->SetOnTouchUp([weakItem = AceType::WeakClaim(this)](const TouchEventInfo& info) {
        auto item = weakItem.Upgrade();
        if (item) {
            item->HandleTouchUp(info);
        }
    });
    touchRecognizer_->SetOnTouchMove([weakItem = AceType::WeakClaim(this)](const TouchEventInfo& info) {
        auto item = weakItem.Upgrade();
        if (item) {
            item->HandleTouchMove(info);
        }
    });
    touchRecognizer_->SetOnTouchCancel([weakItem = AceType::WeakClaim(this)](const TouchEventInfo& info) {
        auto item = weakItem.Upgrade();
        if (item) {
            item->HandleTouchCancel(info);
        }
    });
}

void RenderWeb::HandleTouchDown(const TouchEventInfo& info)
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
        touchPoint.x -= GetGlobalOffset().GetX();
        touchPoint.y -= GetGlobalOffset().GetY();
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

void RenderWeb::HandleTouchUp(const TouchEventInfo& info)
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
        delegate_->HandleTouchUp(touchPoint.id, touchPoint.x, touchPoint.y);
    }
    if (web_ && !touchInfos.empty()) {
        web_->RequestFocus();
    }
}

void RenderWeb::HandleTouchMove(const TouchEventInfo& info)
{
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

void RenderWeb::OnTouchTestHit(const Offset& coordinateOffset, const TouchRestrict& touchRestrict,
    TouchTestResult& result)
{
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
#endif
} // namespace OHOS::Ace
