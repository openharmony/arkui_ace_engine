/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/web/web_pattern.h"

#include "base/geometry/ng/offset_t.h"
#include "base/utils/utils.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components/web/resource/web_delegate.h"
#include "core/components/web/web_property.h"
#include "core/components_ng/pattern/web/web_event_hub.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
constexpr int32_t SINGLE_CLICK_NUM = 1;
constexpr int32_t DOUBLE_CLICK_NUM = 2;
constexpr double DEFAULT_DBCLICK_INTERVAL = 0.5f;

WebPattern::WebPattern() = default;

WebPattern::WebPattern(std::string webSrc, const RefPtr<WebController>& webController)
    : webSrc_(std::move(webSrc)), webController_(webController)
{}

WebPattern::WebPattern(std::string webSrc, const SetWebIdCallback& setWebIdCallback)
    : webSrc_(std::move(webSrc)), setWebIdCallback_(setWebIdCallback)
{}

void WebPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
    host->GetRenderContext()->UpdateBackgroundColor(Color::WHITE);
    host->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);

    InitEvent();
}

void WebPattern::InitEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(eventHub);

    auto gestureHub = eventHub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    InitTouchEvent(gestureHub);

    auto inputHub = eventHub->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    InitMouseEvent(inputHub);

    auto focusHub = eventHub->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    InitFocusEvent(focusHub);

    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto langTask = [weak = AceType::WeakClaim(this)]() {
        auto WebPattern = weak.Upgrade();
        if (WebPattern) {
            WebPattern->UpdateLocale();
        }
    }
    context.SetConfigChangedCallback(std::move(langTask));
}

void WebPattern::InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    auto touchTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (info.GetChangedTouches().empty()) {
            LOGE("touch point is null");
            return;
        }

        // only handle touch event
        if (info.GetSourceDevice() != SourceType::TOUCH) {
            return;
        }

        const auto& changedPoint = info.GetChangedTouches().front();
        if (changedPoint.GetTouchType() == TouchType::DOWN) {
            pattern->HandleTouchDown(info, false);
            return;
        }
        if (changedPoint.GetTouchType() == TouchType::MOVE) {
            pattern->HandleTouchMove(info, false);
            return;
        }
        if (changedPoint.GetTouchType() == TouchType::UP) {
            pattern->HandleTouchUp(info, false);
            return;
        }
        if (changedPoint.GetTouchType() == TouchType::CANCEL) {
            pattern->HandleTouchCancel(info);
            return;
        }
    };
    touchEvent_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gestureHub->AddTouchEvent(touchEvent_);
}

void WebPattern::InitMouseEvent(const RefPtr<InputEventHub>& inputHub)
{
    if (mouseEvent_) {
        return;
    }

    auto mouseTask = [weak = WeakClaim(this)](MouseInfo& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleMouseEvent(info);
        }
    };

    mouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputHub->AddOnMouseEvent(mouseEvent_);

    auto axisTask = [weak = WeakClaim(this)](AxisInfo& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleAxisEvent(info);
        }
    };
    axisEvent_ = MakeRefPtr<InputEvent>(std::move(axisTask));
    inputHub->AddOnAxisEvent(axisEvent_);
}

void WebPattern::HandleMouseEvent(MouseInfo& info)
{
    WebOnMouseEvent(info);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto mouseEventCallback = eventHub->GetOnMouseEvent();
    CHECK_NULL_VOID(mouseEventCallback);
    mouseEventCallback(info);
}

void WebPattern::HandleAxisEvent(AxisInfo& info)
{
    if (!delegate_) {
        LOGE("Delegate_ is nullptr");
        return;
    }
    auto localLocation = info.GetLocalLocation();
    delegate_->HandleAxisEvent(
        localLocation.GetX(), localLocation.GetY(), info.GetHorizontalAxis(), info.GetVerticalAxis());
}

void WebPattern::WebOnMouseEvent(const MouseInfo& info)
{
    if (!delegate_) {
        LOGE("delegate_ is nullptr");
        return;
    }

    if (info.GetAction() == MouseAction::RELEASE) {
        WebRequestFocus();
    }

    auto localLocation = info.GetLocalLocation();
    if (!HandleDoubleClickEvent(info)) {
        delegate_->OnMouseEvent(
            localLocation.GetX(), localLocation.GetY(), info.GetButton(), info.GetAction(), SINGLE_CLICK_NUM);
    }
}

bool WebPattern::HandleDoubleClickEvent(const MouseInfo& info)
{
    if (info.GetButton() != MouseButton::LEFT_BUTTON || info.GetAction() != MouseAction::PRESS) {
        return false;
    }
    auto localLocation = info.GetLocalLocation();
    MouseClickInfo clickInfo;
    clickInfo.x = localLocation.GetX();
    clickInfo.y = localLocation.GetY();
    clickInfo.start = info.GetTimeStamp();
    if (doubleClickQueue_.empty()) {
        doubleClickQueue_.push(clickInfo);
        return false;
    }
    std::chrono::duration<float> timeout_ = clickInfo.start - doubleClickQueue_.back().start;
    if (timeout_.count() < DEFAULT_DBCLICK_INTERVAL) {
        SendDoubleClickEvent(clickInfo);
        std::queue<MouseClickInfo> empty;
        swap(empty, doubleClickQueue_);
        return true;
    }
    if (doubleClickQueue_.size() == 1) {
        doubleClickQueue_.push(clickInfo);
        return false;
    }
    doubleClickQueue_.pop();
    doubleClickQueue_.push(clickInfo);
    return false;
}

void WebPattern::SendDoubleClickEvent(const MouseClickInfo& info)
{
    if (!delegate_) {
        LOGE("Touch cancel delegate_ is nullptr");
        return;
    }
    delegate_->OnMouseEvent(info.x, info.y, MouseButton::LEFT_BUTTON, MouseAction::PRESS, DOUBLE_CLICK_NUM);
}

void WebPattern::InitFocusEvent(const RefPtr<FocusHub>& focusHub)
{
    auto focusTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleFocusEvent();
        }
    };
    focusHub->SetOnFocusInternal(focusTask);

    auto blurTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleBlurEvent();
        }
    };
    focusHub->SetOnBlurInternal(blurTask);

    auto keyTask = [weak = WeakClaim(this)](const KeyEvent& keyEvent) -> bool {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->HandleKeyEvent(keyEvent);
    };
    focusHub->SetOnKeyEventInternal(keyTask);
}

void WebPattern::HandleFocusEvent()
{
    if (!delegate_) {
        LOGE("handle focus delegate_ is nullptr");
        return;
    }
    delegate_->OnFocus();
}

void WebPattern::HandleBlurEvent()
{
    if (!delegate_) {
        LOGE("handle blur delegate_ is nullptr");
        return;
    }
    delegate_->OnBlur();
    OnQuickMenuDismissed();
}

bool WebPattern::HandleKeyEvent(const KeyEvent& keyEvent)
{
    bool ret = WebOnKeyEvent(keyEvent);

    auto host = GetHost();
    CHECK_NULL_RETURN(host, ret);
    auto eventHub = host->GetEventHub<WebEventHub>();
    CHECK_NULL_RETURN(eventHub, ret);
    auto keyEventCallback = eventHub->GetOnKeyEvent();
    CHECK_NULL_RETURN(keyEventCallback, ret);

    KeyEventInfo info(keyEvent);
    keyEventCallback(info);

    return ret;
}

bool WebPattern::WebOnKeyEvent(const KeyEvent& keyEvent)
{
    if (!delegate_) {
        LOGE("OnKeyEvent delegate_ is nullptr");
        return false;
    }
    return delegate_->OnKeyEvent(static_cast<int32_t>(keyEvent.code), static_cast<int32_t>(keyEvent.action));
}

void WebPattern::WebRequestFocus()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto focusHub = eventHub->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);

    focusHub->RequestFocusImmediately();
}

bool WebPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (!config.contentSizeChange) {
        return false;
    }
    CHECK_NULL_RETURN(delegate_, false);
    CHECK_NULL_RETURN(dirty, false);
    auto geometryNode = dirty->GetGeometryNode();
    auto drawSize = geometryNode->GetContentSize();
    delegate_->Resize(drawSize.Width(), drawSize.Height());
    // first update size to load url.
    if (!isUrlLoaded_) {
        isUrlLoaded_ = true;
        if (webSrc_) {
            delegate_->LoadUrl();
        } else if (webData_) {
            delegate_->LoadDataWithRichText();
        }
    }
    return false;
}

void WebPattern::OnWebSrcUpdate()
{
    if (delegate_ && isUrlLoaded_) {
        delegate_->LoadUrl();
    }
}

void WebPattern::OnWebDataUpdate()
{
    if (delegate_ && isUrlLoaded_) {
        delegate_->LoadDataWithRichText();
    }
}

void WebPattern::OnJsEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateJavaScriptEnabled(value);
    }
}

void WebPattern::OnMediaPlayGestureAccessUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateMediaPlayGestureAccess(value);
    }
}

void WebPattern::OnFileAccessEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateAllowFileAccess(value);
    }
}

void WebPattern::OnOnLineImageAccessEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateBlockNetworkImage(!value);
    }
}

void WebPattern::OnDomStorageAccessEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateDomStorageEnabled(value);
    }
}

void WebPattern::OnImageAccessEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateLoadsImagesAutomatically(value);
    }
}

void WebPattern::OnMixedModeUpdate(MixedModeContent value)
{
    if (delegate_) {
        delegate_->UpdateMixedContentMode(value);
    }
}

void WebPattern::OnZoomAccessEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateSupportZoom(value);
    }
}

void WebPattern::OnGeolocationAccessEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateGeolocationEnabled(value);
    }
}

void WebPattern::OnUserAgentUpdate(const std::string& value)
{
    if (delegate_) {
        delegate_->UpdateUserAgent(value);
    }
}

void WebPattern::OnCacheModeUpdate(WebCacheMode value)
{
    if (delegate_) {
        delegate_->UpdateCacheMode(value);
    }
}

void WebPattern::OnOverviewModeAccessEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateOverviewModeEnabled(value);
    }
}

void WebPattern::OnFileFromUrlAccessEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateFileFromUrlEnabled(value);
    }
}

void WebPattern::OnDatabaseAccessEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateDatabaseEnabled(value);
    }
}

void WebPattern::OnTextZoomRatioUpdate(int32_t value)
{
    if (delegate_) {
        delegate_->UpdateTextZoomRatio(value);
    }
}

void WebPattern::OnWebDebuggingAccessEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateWebDebuggingAccess(value);
    }
}

void WebPattern::OnPinchSmoothModeEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdatePinchSmoothModeEnabled(value);
    }
}

void WebPattern::OnBackgroundColorUpdate(int32_t value)
{
    if (delegate_) {
        delegate_->UpdateBackgroundColor(value);
    }
}

void WebPattern::OnInitialScaleUpdate(float value)
{
    if (delegate_) {
        delegate_->UpdateInitialScale(value);
    }
}

void WebPattern::OnMultiWindowAccessEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateMultiWindowAccess(value);
    }
}

void WebPattern::OnModifyDone()
{
    // called in each update function.
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (!delegate_) {
        // first create case,
        delegate_ = AceType::MakeRefPtr<WebDelegate>(PipelineContext::GetCurrentContext(), nullptr, "");
        delegate_->SetNGWebPattern(Claim(this));
        renderSurface_->SetRenderContext(host->GetRenderContext());
        renderSurface_->InitSurface();
        delegate_->InitOHOSWeb(PipelineContext::GetCurrentContext(), renderSurface_);
        delegate_->UpdateBackgroundColor(
            static_cast<int32_t>(renderContext->GetBackgroundColor().value_or(Color::WHITE).GetValue()));
        delegate_->UpdateJavaScriptEnabled(GetJsEnabledValue(true));
        delegate_->UpdateBlockNetworkImage(!GetOnLineImageAccessEnabledValue(true));
        delegate_->UpdateAllowFileAccess(GetFileAccessEnabledValue(true));
        delegate_->UpdateLoadsImagesAutomatically(GetImageAccessEnabledValue(true));
        delegate_->UpdateMixedContentMode(GetMixedModeValue(MixedModeContent::MIXED_CONTENT_NEVER_ALLOW));
        delegate_->UpdateSupportZoom(GetZoomAccessEnabledValue(true));
        delegate_->UpdateDomStorageEnabled(GetDomStorageAccessEnabledValue(false));
        delegate_->UpdateGeolocationEnabled(GetGeolocationAccessEnabledValue(true));
        delegate_->UpdateCacheMode(GetCacheModeValue(WebCacheMode::DEFAULT));
        delegate_->UpdateOverviewModeEnabled(GetOverviewModeAccessEnabledValue(true));
        delegate_->UpdateFileFromUrlEnabled(GetFileFromUrlAccessEnabledValue(false));
        delegate_->UpdateDatabaseEnabled(GetDatabaseAccessEnabledValue(false));
        delegate_->UpdateTextZoomRatio(GetTextZoomRatioValue(DEFAULT_TEXT_ZOOM_RATIO));
        delegate_->UpdateWebDebuggingAccess(GetWebDebuggingAccessEnabledValue(false));
        delegate_->UpdateMediaPlayGestureAccess(GetMediaPlayGestureAccessValue(true));
        delegate_->UpdatePinchSmoothModeEnabled(GetPinchSmoothModeEnabledValue(false));
        delegate_->UpdateMultiWindowAccess(GetMultiWindowAccessEnabledValue(false));
        if (GetUserAgent()) {
            delegate_->UpdateUserAgent(GetUserAgent().value());
        }
        if (GetInitialScale()) {
            delegate_->UpdateInitialScale(GetInitialScale().value());
        }
    }

    // update bgcolor.
    if (renderContext->HasBackgroundColor()) {
        delegate_->UpdateBackgroundColor(static_cast<int32_t>(renderContext->GetBackgroundColor()->GetValue()));
    }
}

void WebPattern::HandleTouchDown(const TouchEventInfo& info, bool fromOverlay)
{
    CHECK_NULL_VOID(delegate_);
    Offset touchOffset = Offset(0, 0);
    std::list<TouchInfo> touchInfos;
    if (!ParseTouchInfo(info, touchInfos)) {
        LOGE("handle touch down error");
        return;
    }
    for (auto& touchPoint : touchInfos) {
        delegate_->HandleTouchDown(touchPoint.id, touchPoint.x, touchPoint.y);
    }
}

void WebPattern::HandleTouchUp(const TouchEventInfo& info, bool fromOverlay)
{
    CHECK_NULL_VOID(delegate_);
    std::list<TouchInfo> touchInfos;
    if (!ParseTouchInfo(info, touchInfos)) {
        LOGE("handle touch up error");
        return;
    }
    for (auto& touchPoint : touchInfos) {
        delegate_->HandleTouchUp(touchPoint.id, touchPoint.x, touchPoint.y);
    }
    if (!touchInfos.empty()) {
        WebRequestFocus();
    }
}

void WebPattern::HandleTouchMove(const TouchEventInfo& info, bool fromOverlay)
{
    CHECK_NULL_VOID(delegate_);
    std::list<TouchInfo> touchInfos;
    if (!ParseTouchInfo(info, touchInfos)) {
        LOGE("handle touch move error");
        return;
    }
    for (auto& touchPoint : touchInfos) {
        delegate_->HandleTouchMove(touchPoint.id, touchPoint.x, touchPoint.y);
    }
}

void WebPattern::HandleTouchCancel(const TouchEventInfo& /*info*/)
{
    CHECK_NULL_VOID(delegate_);
    delegate_->HandleTouchCancel();
}

bool WebPattern::ParseTouchInfo(const TouchEventInfo& info, std::list<TouchInfo>& touchInfos)
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, false);
    auto viewScale = context->GetViewScale();
    if (info.GetTouches().empty()) {
        return false;
    }
    for (const auto& point : info.GetTouches()) {
        TouchInfo touchInfo;
        touchInfo.id = point.GetFingerId();
        const Offset& location = point.GetLocalLocation();
        touchInfo.x = static_cast<float>(location.GetX() * viewScale);
        touchInfo.y = static_cast<float>(location.GetY() * viewScale);
        touchInfos.emplace_back(touchInfo);
    }
    return true;
}

void WebPattern::RequestFullScreen()
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto fullScreenManager = context->GetFullScreenManager();
    CHECK_NULL_VOID(fullScreenManager);
    fullScreenManager->RequestFullScreen(host);
}

void WebPattern::ExitFullScreen()
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto fullScreenManager = context->GetFullScreenManager();
    CHECK_NULL_VOID(fullScreenManager);
    fullScreenManager->ExitFullScreen(host);
}

bool WebPattern::IsTouchHandleValid(
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> handle)
{
    return (handle != nullptr) && (handle->IsEnable());
}

bool WebPattern::IsTouchHandleShow(
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> handle)
{
    if (!handle) {
        return false;
    }
    if (handle->GetAlpha() > 0 &&
        GreatOrEqual(handle->GetY(), handle->GetEdgeHeight()) &&
        GreatNotEqual(GetHostFrameSize().value_or(SizeF()).Height(), handle->GetY())) {
        return true;
    }
    return false;
}

WebOverlayType WebPattern::GetTouchHandleOverlayType(
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

RectF WebPattern::ComputeTouchHandleRect(std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> touchHandle)
{
    RectF paintRect;
    auto offset = GetHostFrameGlobalOffset().value_or(OffsetF());
    auto size = GetHostFrameSize().value_or(SizeF());
    float edgeHeight = touchHandle->GetEdgeHeight();
    float x = touchHandle->GetX();
    float y = touchHandle->GetY();
    if (x > size.Width()) {
        x = offset.GetX() + size.Width();
    } else {
        x = x + offset.GetX();
    }

    if (y < 0) {
        y = offset.GetY();
    } else if (y > size.Height()) {
        y = offset.GetY() + size.Height();
    } else {
        y = y + offset.GetY();
        y = y - edgeHeight;
    }

    x = x - SelectHandleInfo::GetDefaultLineWidth().ConvertToPx() / 2;
    paintRect.SetOffset({ x, y });
    paintRect.SetSize({ SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), edgeHeight });
    return paintRect;
}

void WebPattern::CloseSelectOverlay()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    if (selectOverlayProxy_) {
        selectOverlayProxy_->Close();
        pipeline->GetSelectOverlayManager()->DestroySelectOverlay(selectOverlayProxy_);
        selectOverlayProxy_ = nullptr;
    }
}

void WebPattern::RegisterSelectOverlayCallback(SelectOverlayInfo& selectInfo,
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params,
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuCallback> callback)
{
    int32_t flags = params->GetEditStateFlags();
    if (flags & OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_CUT) {
        selectInfo.menuCallback.onCut = [weak = AceType::WeakClaim(this), callback]() {
            if (callback) {
                callback->Continue(OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_CUT,
                    OHOS::NWeb::MenuEventFlags::EF_LEFT_MOUSE_BUTTON);
            }
        };
    } else {
        selectInfo.menuInfo.showCut = false;
    }
    if (flags & OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_COPY) {
        selectInfo.menuCallback.onCopy = [weak = AceType::WeakClaim(this), callback]() {
            if (callback) {
                callback->Continue(OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_COPY,
                    OHOS::NWeb::MenuEventFlags::EF_LEFT_MOUSE_BUTTON);
            }
        };
    } else {
        selectInfo.menuInfo.showCopy = false;
    }
    if (flags & OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_PASTE) {
        selectInfo.menuCallback.onPaste = [weak = AceType::WeakClaim(this), callback]() {
            if (callback) {
                callback->Continue(OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_PASTE,
                    OHOS::NWeb::MenuEventFlags::EF_LEFT_MOUSE_BUTTON);
            }
        };
    } else {
        selectInfo.menuInfo.showPaste = false;
    }
    if (flags & OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_SELECT_ALL) {
        selectInfo.menuCallback.onSelectAll = [weak = AceType::WeakClaim(this), callback]() {
            if (callback) {
                callback->Continue(OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_SELECT_ALL,
                    OHOS::NWeb::MenuEventFlags::EF_LEFT_MOUSE_BUTTON);
            }
        };
    } else {
        selectInfo.menuInfo.showCopyAll = false;
    }
    selectInfo.onHandleMoveDone = [weak = AceType::WeakClaim(this)](const RectF& rectF, bool isFirst) {
        auto webPattern = weak.Upgrade();
        CHECK_NULL_VOID(webPattern);
        webPattern->UpdateTouchHandleForOverlay();
    };
}

bool WebPattern::RunQuickMenu(std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params,
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuCallback> callback)
{
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertTouchHandle =
        params->GetTouchHandleState(OHOS::NWeb::NWebTouchHandleState::TouchHandleType::INSERT_HANDLE);
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> beginTouchHandle =
        params->GetTouchHandleState(OHOS::NWeb::NWebTouchHandleState::TouchHandleType::SELECTION_BEGIN_HANDLE);
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endTouchHandle =
        params->GetTouchHandleState(OHOS::NWeb::NWebTouchHandleState::TouchHandleType::SELECTION_END_HANDLE);
    WebOverlayType overlayType = GetTouchHandleOverlayType(insertTouchHandle,
                                                           beginTouchHandle,
                                                           endTouchHandle);
    if (overlayType == INVALID_OVERLAY) {
        return false;
    }
    if (selectOverlayProxy_) {
        CloseSelectOverlay();
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto theme = pipeline->GetThemeManager()->GetTheme<TextOverlayTheme>();
    CHECK_NULL_RETURN(theme, false);
    selectHotZone_ = theme->GetHandleHotZoneRadius().ConvertToPx();
    SelectOverlayInfo selectInfo;
    selectInfo.isSingleHandle = (overlayType == INSERT_OVERLAY);
    if (selectInfo.isSingleHandle) {
        selectInfo.firstHandle.isShow = IsTouchHandleShow(insertTouchHandle);
        selectInfo.firstHandle.paintRect = ComputeTouchHandleRect(insertTouchHandle);
    } else {
        selectInfo.firstHandle.isShow = IsTouchHandleShow(beginTouchHandle);
        selectInfo.firstHandle.paintRect = ComputeTouchHandleRect(beginTouchHandle);
        selectInfo.secondHandle.isShow = IsTouchHandleShow(endTouchHandle);
        selectInfo.secondHandle.paintRect = ComputeTouchHandleRect(endTouchHandle);
    }
    selectInfo.menuInfo.menuIsShow = true;
    RegisterSelectOverlayCallback(selectInfo, params, callback);
    selectOverlayProxy_ = pipeline->GetSelectOverlayManager()->CreateAndShowSelectOverlay(selectInfo);
    insertHandle_ = insertTouchHandle;
    startSelectionHandle_ = beginTouchHandle;
    endSelectionHandle_ = endTouchHandle;
    return selectOverlayProxy_ ? true : false;
}

void WebPattern::OnQuickMenuDismissed()
{
    CloseSelectOverlay();
}

void WebPattern::OnTouchSelectionChanged(std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertHandle,
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> startSelectionHandle,
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endSelectionHandle)
{
    WebOverlayType overlayType = GetTouchHandleOverlayType(insertHandle,
                                                           startSelectionHandle,
                                                           endSelectionHandle);
    if (overlayType == INVALID_OVERLAY) {
        CloseSelectOverlay();
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetThemeManager()->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(theme);
    selectHotZone_ = theme->GetHandleHotZoneRadius().ConvertToPx();
    insertHandle_ = insertHandle;
    startSelectionHandle_ = startSelectionHandle;
    endSelectionHandle_ = endSelectionHandle;
    if (!selectOverlayProxy_) {
        if (overlayType == INSERT_OVERLAY) {
            SelectOverlayInfo selectInfo;
            selectInfo.isSingleHandle = true;
            selectInfo.firstHandle.isShow = IsTouchHandleShow(insertHandle_);
            selectInfo.firstHandle.paintRect = ComputeTouchHandleRect(insertHandle_);
            selectInfo.menuInfo.menuDisable = false;
            selectInfo.menuInfo.menuIsShow = false;
            selectInfo.onHandleMoveDone = [weak = AceType::WeakClaim(this)](const RectF& rectF, bool isFirst) {
                auto webPattern = weak.Upgrade();
                CHECK_NULL_VOID(webPattern);
                webPattern->UpdateTouchHandleForOverlay();
            };
            selectOverlayProxy_ = pipeline->GetSelectOverlayManager()->CreateAndShowSelectOverlay(selectInfo);
        }
    } else {
        if (overlayType == INSERT_OVERLAY) {
            UpdateTouchHandleForOverlay();
        }
    }
}

void WebPattern::UpdateTouchHandleForOverlay()
{
    WebOverlayType overlayType = GetTouchHandleOverlayType(insertHandle_,
                                                           startSelectionHandle_,
                                                           endSelectionHandle_);
    if (!selectOverlayProxy_) {
        return;
    }
    if (overlayType == INVALID_OVERLAY) {
        CloseSelectOverlay();
        return;
    }
    SelectHandleInfo firstHandleInfo;
    SelectHandleInfo secondHandleInfo;
    SelectMenuInfo menuInfo;
    if (overlayType == INSERT_OVERLAY) {
        firstHandleInfo.isShow = IsTouchHandleShow(insertHandle_);
        firstHandleInfo.paintRect = ComputeTouchHandleRect(insertHandle_);
        menuInfo.menuIsShow = false;
        selectOverlayProxy_->UpdateFirstSelectHandleInfo(firstHandleInfo);
        selectOverlayProxy_->UpdateSelectMenuInfo(menuInfo);
    } else {
        firstHandleInfo.isShow = IsTouchHandleShow(startSelectionHandle_);
        firstHandleInfo.paintRect = ComputeTouchHandleRect(startSelectionHandle_);
        secondHandleInfo.isShow = IsTouchHandleShow(endSelectionHandle_);
        secondHandleInfo.paintRect = ComputeTouchHandleRect(endSelectionHandle_);
        selectOverlayProxy_->UpdateFirstSelectHandleInfo(firstHandleInfo);
        selectOverlayProxy_->UpdateSecondSelectHandleInfo(secondHandleInfo);
    }
}

void WebPattern::UpdateLocale()
{
    CHECK_NULL_VOID(delegate_);
    delegate_->UpdateLocale();
}
} // namespace OHOS::Ace::NG
