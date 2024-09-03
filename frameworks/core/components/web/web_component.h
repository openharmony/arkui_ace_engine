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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_WEB_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_WEB_COMPONENT_H

#include <string>
#include <tuple>
#include <utility>

#include "base/geometry/size.h"
#include "base/log/log.h"
#include "base/utils/utils.h"
#include "core/components/box/drag_drop_event.h"
#include "core/components/declaration/common/declaration.h"
#include "core/components/declaration/web/web_client.h"
#include "core/components/declaration/web/web_declaration.h"
#include "core/components/web/resource/web_javascript_value.h"
#include "core/components/web/web_event.h"
#include "core/components/web/web_property.h"
#include "core/components_v2/common/common_def.h"
#include "core/event/key_event.h"
#include "core/focus/focus_node.h"
#include "core/pipeline/base/element.h"

namespace OHOS::Ace {

// A component can show HTML5 webpages.
class ACE_EXPORT WebComponent : public RenderComponent {
    DECLARE_ACE_TYPE(WebComponent, RenderComponent);

public:
    using CreatedCallback = std::function<void()>;
    using ReleasedCallback = std::function<void(bool)>;
    using ErrorCallback = std::function<void(const std::string&, const std::string&)>;
    using MethodCall = std::function<void(const std::string&)>;
    using Method = std::string;
    using SetWebIdCallback = std::function<void(int32_t)>;
    using SetHapPathCallback = std::function<void(const std::string&)>;
    using JsProxyCallback = std::function<void()>;
    using PreKeyEventCallback = std::function<bool(KeyEventInfo& keyEventInfo)>;

    WebComponent() = default;
    explicit WebComponent(const std::string& type);
    ~WebComponent() override = default;

    RefPtr<RenderNode> CreateRenderNode() override;
    RefPtr<Element> CreateElement() override;

    void SetType(const std::string& type)
    {
        type_ = type;
    }

    const std::string& GetType() const
    {
        return type_;
    }

    void SetIncognitoMode(const bool incognitoMode)
    {
        incognitoMode_ = incognitoMode;
    }

    bool GetIncognitoMode() const
    {
        return incognitoMode_;
    }

    void SetSrc(const std::string& src)
    {
        CHECK_NULL_VOID(declaration_);
        declaration_->SetWebSrc(src);
    }

    const std::string& GetSrc() const
    {
        return declaration_->GetWebSrc();
    }

    void SetPopup(bool popup)
    {
        isPopup_ = popup;
    }

    void SetParentNWebId(int32_t parentNWebId)
    {
        parentNWebId_ = parentNWebId;
    }

    void SetSharedRenderProcessToken(const std::string& sharedRenderProcessToken)
    {
        shared_render_process_token_ = sharedRenderProcessToken;
    }

    const std::string& GetSharedRenderProcessToken() const
    {
        return shared_render_process_token_;
    }

    void SetData(const std::string& data)
    {
        CHECK_NULL_VOID(declaration_);
        declaration_->SetWebData(data);
    }

    const std::string& GetData() const
    {
        return declaration_->GetWebData();
    }

    void SetPageStartedEventId(const EventMarker& pageStartedEventId)
    {
        CHECK_NULL_VOID(declaration_);
        declaration_->SetPageStartedEventId(pageStartedEventId);
    }

    const EventMarker& GetPageStartedEventId() const
    {
        return declaration_->GetPageStartedEventId();
    }

    void SetPageFinishedEventId(const EventMarker& pageFinishedEventId)
    {
        CHECK_NULL_VOID(declaration_);
        declaration_->SetPageFinishedEventId(pageFinishedEventId);
    }

    const EventMarker& GetPageFinishedEventId() const
    {
        return declaration_->GetPageFinishedEventId();
    }

    using OnProgressChangeImpl = std::function<void(const BaseEventInfo* info)>;
    void OnProgressChange(const BaseEventInfo* info) const
    {
        if (onProgressChangeImpl_) {
            onProgressChangeImpl_(info);
        }
    }
    void SetProgressChangeImpl(OnProgressChangeImpl&& onProgressChangeImpl)
    {
        if (onProgressChangeImpl == nullptr) {
            return;
        }
        onProgressChangeImpl_ = std::move(onProgressChangeImpl);
    }

    void SetTitleReceiveEventId(const EventMarker& titleReceiveEventId)
    {
        CHECK_NULL_VOID(declaration_);
        declaration_->SetTitleReceiveEventId(titleReceiveEventId);
    }

    const EventMarker& GetTitleReceiveEventId() const
    {
        return declaration_->GetTitleReceiveEventId();
    }

    void SetOnFullScreenExitEventId(const EventMarker& fullScreenExitEventId)
    {
        CHECK_NULL_VOID(declaration_);
        declaration_->SetOnFullScreenExitEventId(fullScreenExitEventId);
    }

    const EventMarker& GetOnFullScreenExitEventId() const
    {
        return declaration_->GetOnFullScreenExitEventId();
    }

    void SetGeolocationHideEventId(const EventMarker& geolocationHideEventId)
    {
        CHECK_NULL_VOID(declaration_);
        declaration_->SetGeolocationHideEventId(geolocationHideEventId);
    }

    const EventMarker& GetGeolocationHideEventId() const
    {
        return declaration_->GetGeolocationHideEventId();
    }

    void SetGeolocationShowEventId(const EventMarker& geolocationShowEventId)
    {
        CHECK_NULL_VOID(declaration_);
        declaration_->SetGeolocationShowEventId(geolocationShowEventId);
    }

    const EventMarker& GetGeolocationShowEventId() const
    {
        return declaration_->GetGeolocationShowEventId();
    }

    void SetRequestFocusEventId(const EventMarker& requestFocusEventId)
    {
        CHECK_NULL_VOID(declaration_);
        declaration_->SetRequestFocusEventId(requestFocusEventId);
    }

    const EventMarker& GetRequestFocusEventId() const
    {
        return declaration_->GetRequestFocusEventId();
    }

    void SetDownloadStartEventId(const EventMarker& downloadStartEventId)
    {
        CHECK_NULL_VOID(declaration_);
        declaration_->SetDownloadStartEventId(downloadStartEventId);
    }

    const EventMarker& GetDownloadStartEventId() const
    {
        return declaration_->GetDownloadStartEventId();
    }

    void SetPageErrorEventId(const EventMarker& pageErrorEventId)
    {
        CHECK_NULL_VOID(declaration_);
        declaration_->SetPageErrorEventId(pageErrorEventId);
    }

    const EventMarker& GetPageErrorEventId() const
    {
        return declaration_->GetPageErrorEventId();
    }

    void SetHttpErrorEventId(const EventMarker& httpErrorEventId)
    {
        CHECK_NULL_VOID(declaration_);
        declaration_->SetHttpErrorEventId(httpErrorEventId);
    }

    const EventMarker& GetHttpErrorEventId() const
    {
        return declaration_->GetHttpErrorEventId();
    }

    void SetMessageEventId(const EventMarker& messageEventId)
    {
        CHECK_NULL_VOID(declaration_);
        declaration_->SetMessageEventId(messageEventId);
    }

    const EventMarker& GetMessageEventId() const
    {
        return declaration_->GetMessageEventId();
    }

    void SetRenderExitedId(const EventMarker& renderExitedId)
    {
        CHECK_NULL_VOID(declaration_);
        declaration_->SetRenderExitedId(renderExitedId);
    }

    const EventMarker& GetRenderExitedId() const
    {
        return declaration_->GetRenderExitedId();
    }

    void SetRefreshAccessedHistoryId(const EventMarker& refreshAccessedHistoryId)
    {
        CHECK_NULL_VOID(declaration_);
        declaration_->SetRefreshAccessedHistoryId(refreshAccessedHistoryId);
    }

    const EventMarker& GetRefreshAccessedHistoryId() const
    {
        return declaration_->GetRefreshAccessedHistoryId();
    }

    void SetResourceLoadId(const EventMarker& resourceLoadId)
    {
        CHECK_NULL_VOID(declaration_);
        declaration_->SetResourceLoadId(resourceLoadId);
    }

    const EventMarker& GetResourceLoadId() const
    {
        return declaration_->GetResourceLoadId();
    }

    void SetScaleChangeId(const EventMarker& scaleChangeId)
    {
        CHECK_NULL_VOID(declaration_);
        declaration_->SetScaleChangeId(scaleChangeId);
    }

    const EventMarker& GetScaleChangeId() const
    {
        return declaration_->GetScaleChangeId();
    }

    void SetScrollId(const EventMarker& scrollId)
    {
        CHECK_NULL_VOID(declaration_);
        declaration_->SetScrollId(scrollId);
    }

    const EventMarker& GetScrollId() const
    {
        return declaration_->GetScrollId();
    }

    void SetPermissionRequestEventId(const EventMarker& permissionRequestEventId)
    {
        CHECK_NULL_VOID(declaration_);
        declaration_->SetPermissionRequestEventId(permissionRequestEventId);
    }

    const EventMarker& GetPermissionRequestEventId() const
    {
        return declaration_->GetPermissionRequestEventId();
    }

    using OnWindowNewImpl = std::function<void(const std::shared_ptr<BaseEventInfo>& info)>;
    void SetWindowNewEvent(OnWindowNewImpl && onWindowNewImpl)
    {
        if (onWindowNewImpl == nullptr) {
            return;
        }
        onWindowNewImpl_ = std::move(onWindowNewImpl);
    }

    void OnWindowNewEvent(const std::shared_ptr<BaseEventInfo>& info) const
    {
        if (onWindowNewImpl_) {
            onWindowNewImpl_(info);
        }
    }

    void SetWindowExitEventId(const EventMarker& windowExitEventId)
    {
        CHECK_NULL_VOID(declaration_);
        declaration_->SetWindowExitEventId(windowExitEventId);
    }

    const EventMarker& GetWindowExitEventId() const
    {
        return declaration_->GetWindowExitEventId();
    }

    void SetDeclaration(const RefPtr<WebDeclaration>& declaration)
    {
        if (declaration) {
            declaration_ = declaration;
        }
    }

    RefPtr<WebController> GetController() const
    {
        return webController_;
    }

    void SetWebController(const RefPtr<WebController>& webController)
    {
        webController_ = webController;
    }

    void SetSetWebIdCallback(SetWebIdCallback&& SetIdCallback)
    {
        setWebIdCallback_ = std::move(SetIdCallback);
    }

    SetWebIdCallback GetSetWebIdCallback() const
    {
        return setWebIdCallback_;
    }

    void SetSetHapPathCallback(SetHapPathCallback&& callback)
    {
        setHapPathCallback_ = std::move(callback);
    }

    SetHapPathCallback GetSetHapPathCallback() const
    {
        return setHapPathCallback_;
    }

    bool GetJsEnabled() const
    {
        return isJsEnabled_;
    }

    void SetJsEnabled(bool isEnabled)
    {
        isJsEnabled_ = isEnabled;
    }

    std::string GetUserAgent() const
    {
        return userAgent_;
    }

    void SetUserAgent(std::string userAgent)
    {
        userAgent_ = std::move(userAgent);
    }

    std::string GetCustomScheme() const
    {
        return customScheme_;
    }

    void SetCustomScheme(std::string cmdLine)
    {
        customScheme_ = std::move(cmdLine);
    }

    bool GetContentAccessEnabled() const
    {
        return isContentAccessEnabled_;
    }

    void SetContentAccessEnabled(bool isEnabled)
    {
        isContentAccessEnabled_ = isEnabled;
    }

    bool GetFileAccessEnabled() const
    {
        return isFileAccessEnabled_;
    }

    void SetFileAccessEnabled(bool isEnabled)
    {
        isFileAccessEnabled_ = isEnabled;
    }
    bool GetOnLineImageAccessEnabled() const
    {
        return isOnLineImageAccessEnabled_;
    }

    void SetOnLineImageAccessEnabled(bool isEnabled)
    {
        isOnLineImageAccessEnabled_ = isEnabled;
    }

    bool GetDomStorageAccessEnabled() const
    {
        return isDomStorageAccessEnabled_;
    }

    void SetDomStorageAccessEnabled(bool isEnabled)
    {
        isDomStorageAccessEnabled_ = isEnabled;
    }

    bool GetImageAccessEnabled() const
    {
        return isImageAccessEnabled_;
    }

    void SetImageAccessEnabled(bool isEnabled)
    {
        isImageAccessEnabled_ = isEnabled;
    }

    MixedModeContent GetMixedMode() const
    {
        return mixedContentMode_;
    }

    void SetMixedMode(MixedModeContent mixedModeNum)
    {
        mixedContentMode_ = mixedModeNum;
    }

    bool GetZoomAccessEnabled() const
    {
        return isZoomAccessEnabled_;
    }

    void SetZoomAccessEnabled(bool isEnabled)
    {
        isZoomAccessEnabled_ = isEnabled;
    }

    bool GetGeolocationAccessEnabled() const
    {
        return isGeolocationAccessEnabled_;
    }

    void SetGeolocationAccessEnabled(bool isEnabled)
    {
        isGeolocationAccessEnabled_ = isEnabled;
    }

    WebCacheMode GetCacheMode()
    {
        return cacheMode_;
    }

    void SetCacheMode(WebCacheMode mode)
    {
        cacheMode_ = mode;
    }

    OverScrollMode GetOverScrollMode() const
    {
        return OverScrollMode_;
    }

    void SetOverScrollMode(OverScrollMode mode)
    {
        OverScrollMode_ = mode;
    }

    CopyOptions GetCopyOptionMode() const
    {
        return CopyOptionMode_;
    }

    void SetCopyOptionMode(CopyOptions mode)
    {
        CopyOptionMode_ = mode;
    }

    bool GetOverviewModeAccessEnabled() const
    {
        return isOverviewModeAccessEnabled_;
    }

    void SetOverviewModeAccessEnabled(bool isEnabled)
    {
        isOverviewModeAccessEnabled_ = isEnabled;
    }

    bool GetFileFromUrlAccessEnabled() const
    {
        return isFileFromUrlAccessEnabled_;
    }

    void SetFileFromUrlAccessEnabled(bool isEnabled)
    {
        isFileFromUrlAccessEnabled_ = isEnabled;
    }

    bool GetDatabaseAccessEnabled() const
    {
        return isDatabaseAccessEnabled_;
    }

    void SetDatabaseAccessEnabled(bool isEnabled)
    {
        isDatabaseAccessEnabled_ = isEnabled;
    }

    bool GetWebDebuggingAccessEnabled() const
    {
        return isWebDebuggingAccessEnabled_;
    }

    void SetWebDebuggingAccessEnabled(bool isEnabled)
    {
        isWebDebuggingAccessEnabled_ = isEnabled;
    }

    bool GetPinchSmoothModeEnabled() const
    {
        return isPinchSmoothModeEnabled_;
    }

    void SetPinchSmoothModeEnabled(bool isEnabled)
    {
        isPinchSmoothModeEnabled_ = isEnabled;
    }

    bool GetMultiWindowAccessEnabled() const
    {
        return isMultiWindowAccessEnabled_;
    }

    void SetMultiWindowAccessEnabled(bool isEnabled)
    {
        isMultiWindowAccessEnabled_ = isEnabled;
    }

    bool GetAllowWindowOpenMethod() const
    {
        return isAllowWindowOpenMethod_;
    }

    void SetAllowWindowOpenMethod(bool isEnabled)
    {
        isAllowWindowOpenMethod_ = isEnabled;
    }

    bool GetIsInitialScaleSet() const
    {
        return isInitialScaleSet_;
    }

    float GetInitialScale() const
    {
        return initialScale_;
    }

    void SetInitialScale(float scale)
    {
        initialScale_ = scale;
        isInitialScaleSet_ = true;
    }

    bool GetBackgroundColorEnabled() const
    {
        return isBackgroundColor_;
    }

    int32_t GetBackgroundColor() const
    {
        return backgroundColor_;
    }

    void SetBackgroundColor(int32_t backgroundColor)
    {
        backgroundColor_ = backgroundColor;
        isBackgroundColor_ = true;
    }

    int32_t GetTextZoomRatio() const
    {
        return textZoomRatioNum_;
    }

    void SetTextZoomRatio(int32_t ratio)
    {
        textZoomRatioNum_ = ratio;
    }

    void SetNativeEmbedModeEnabled(bool isEnabled)
    {
        isNativeEmbedMode_ = isEnabled;
    }

    const std::tuple<bool, bool>& GetNativeVideoPlayerConfig() const
    {
        return native_video_player_config_;
    }

    void SetNativeVideoPlayerConfig(bool enable, bool shouldOverlay)
    {
        native_video_player_config_ = std::make_tuple(enable, shouldOverlay);
    }

    void RegisterNativeEmbedRule(const std::string& tag, const std::string& type)
    {
        tag_ = tag;
        tag_type_ = type;
    }

    void SetSmoothDragResizeEnabled(bool isEnabled)
    {
        isSmoothDragResizeEnabled_ = isEnabled;
    }

    using OnCommonDialogImpl = std::function<bool(const BaseEventInfo* info)>;
    bool OnCommonDialog(const BaseEventInfo* info, DialogEventType dialogEventType) const
    {
        if (dialogEventType == DialogEventType::DIALOG_EVENT_ALERT && onAlertImpl_) {
            return onAlertImpl_(info);
        }
        if (dialogEventType == DialogEventType::DIALOG_EVENT_CONFIRM && onConfirmImpl_) {
            return onConfirmImpl_(info);
        }
        if (dialogEventType == DialogEventType::DIALOG_EVENT_PROMPT && onPromptImpl_) {
            return onPromptImpl_(info);
        }
        if (dialogEventType == DialogEventType::DIALOG_EVENT_BEFORE_UNLOAD && onBeforeUnloadImpl_) {
            return onBeforeUnloadImpl_(info);
        }
        return false;
    }
    void SetOnCommonDialogImpl(OnCommonDialogImpl&& onCommonDialogImpl, DialogEventType dialogEventType)
    {
        if (onCommonDialogImpl == nullptr) {
            return;
        }

        switch (dialogEventType) {
            case DialogEventType::DIALOG_EVENT_ALERT:
                onAlertImpl_ = std::move(onCommonDialogImpl);
                break;
            case DialogEventType::DIALOG_EVENT_CONFIRM:
                onConfirmImpl_ = std::move(onCommonDialogImpl);
                break;
            case DialogEventType::DIALOG_EVENT_PROMPT:
                onPromptImpl_ = std::move(onCommonDialogImpl);
                break;
            case DialogEventType::DIALOG_EVENT_BEFORE_UNLOAD:
                onBeforeUnloadImpl_ = std::move(onCommonDialogImpl);
                break;
            default:
                break;
        }
    }

    using OnFullScreenEnterImpl = std::function<void(const BaseEventInfo* info)>;
    void OnFullScreenEnter(const BaseEventInfo* info) const
    {
        if (onFullScreenEnterImpl_) {
            onFullScreenEnterImpl_(info);
        }
    }
    void SetOnFullScreenEnterImpl(OnFullScreenEnterImpl&& onFullScreenEnterImpl)
    {
        onFullScreenEnterImpl_ = std::move(onFullScreenEnterImpl);
    }

    using OnHttpAuthRequestImpl = std::function<bool(const BaseEventInfo* info)>;
    bool OnHttpAuthRequest(const BaseEventInfo* info) const
    {
        if (onHttpAuthRequestImpl_) {
            return onHttpAuthRequestImpl_(info);
        }
        return false;
    }
    void SetOnHttpAuthRequestImpl(OnHttpAuthRequestImpl&& onHttpAuthRequestImpl)
    {
        if (onHttpAuthRequestImpl == nullptr) {
            return;
        }
        onHttpAuthRequestImpl_ = std::move(onHttpAuthRequestImpl);
    }

    using OnSslErrorRequestImpl = std::function<bool(const BaseEventInfo* info)>;
    bool OnSslErrorRequest(const BaseEventInfo* info) const
    {
        if (onSslErrorRequestImpl_) {
            return onSslErrorRequestImpl_(info);
        }
        return false;
    }
    void SetOnSslErrorRequestImpl(OnSslErrorRequestImpl && onSslErrorRequestImpl)
    {
        if (onSslErrorRequestImpl == nullptr) {
            return;
        }
        onSslErrorRequestImpl_ = std::move(onSslErrorRequestImpl);
    }

    using OnAllSslErrorRequestImpl = std::function<bool(const BaseEventInfo* info)>;
    bool OnAllSslErrorRequest(const BaseEventInfo* info) const
    {
        if (onAllSslErrorRequestImpl_) {
            return onAllSslErrorRequestImpl_(info);
        }
        return false;
    }

    void SetOnAllSslErrorRequestImpl(OnAllSslErrorRequestImpl && onAllSslErrorRequestImpl)
    {
        if (onAllSslErrorRequestImpl == nullptr) {
            return;
        }
        onAllSslErrorRequestImpl_ = std::move(onAllSslErrorRequestImpl);
    }

    using OnSslSelectCertRequestImpl = std::function<bool(const BaseEventInfo* info)>;
    bool OnSslSelectCertRequest(const BaseEventInfo* info) const
    {
        if (onSslSelectCertRequestImpl_) {
            return onSslSelectCertRequestImpl_(info);
        }
        return false;
    }
    void SetOnSslSelectCertRequestImpl(OnSslSelectCertRequestImpl && impl)
    {
        if (!impl) {
            return;
        }
        onSslSelectCertRequestImpl_ = std::move(impl);
    }

    bool RequestFocus();

    using OnConsoleImpl = std::function<bool(const BaseEventInfo* info)>;
    bool OnConsole(const BaseEventInfo* info) const
    {
        if (consoleImpl_) {
            return consoleImpl_(info);
        }
        return false;
    }

    void SetOnConsoleImpl(OnConsoleImpl&& consoleImpl)
    {
        consoleImpl_ = std::move(consoleImpl);
    }

    void SetFocusElement(const WeakPtr<FocusNode>& focusElement)
    {
        focusElement_ = focusElement;
    }

    using OnFileSelectorShowImpl = std::function<bool(const BaseEventInfo* info)>;
    bool OnFileSelectorShow(const BaseEventInfo* info) const
    {
        if (onFileSelectorShowImpl_) {
            return onFileSelectorShowImpl_(info);
        }
        return false;
    }
    void SetOnFileSelectorShow(OnFileSelectorShowImpl&& onFileSelectorShowImpl)
    {
        if (onFileSelectorShowImpl == nullptr) {
            return;
        }

        onFileSelectorShowImpl_ = onFileSelectorShowImpl;
    }

    using OnContextMenuImpl = std::function<bool(const BaseEventInfo* info)>;
    bool OnContextMenuShow(const BaseEventInfo* info) const
    {
        if (onContextMenuImpl_) {
            return onContextMenuImpl_(info);
        }
        return false;
    }
    void SetOnContextMenuShow(OnContextMenuImpl&& onContextMenuImpl)
    {
        if (onContextMenuImpl == nullptr) {
            return;
        }
        onContextMenuImpl_ = std::move(onContextMenuImpl);
    }

    using OnContextMenuHideImpl = std::function<void(const BaseEventInfo* info)>;
    void OnContextMenuHide(const BaseEventInfo* info) const
    {
        if (onContextMenuHideImpl_) {
            onContextMenuHideImpl_(info);
        }
    }
    void SetOnContextMenuHide(OnContextMenuHideImpl&& onContextMenuHideImpl)
    {
        if (onContextMenuHideImpl == nullptr) {
            return;
        }
        onContextMenuHideImpl_ = std::move(onContextMenuHideImpl);
    }

    using OnUrlLoadInterceptImpl = std::function<bool(const BaseEventInfo* info)>;
    bool OnUrlLoadIntercept(const BaseEventInfo* info) const
    {
        if (onUrlLoadInterceptImpl_) {
            return onUrlLoadInterceptImpl_(info);
        }
        return false;
    }
    void SetOnUrlLoadIntercept(OnUrlLoadInterceptImpl&& onUrlLoadInterceptImpl)
    {
        if (onUrlLoadInterceptImpl == nullptr) {
            return;
        }

        onUrlLoadInterceptImpl_ = onUrlLoadInterceptImpl;
    }

    using OnLoadInterceptImpl = std::function<bool(const BaseEventInfo* info)>;
    bool OnLoadIntercept(const BaseEventInfo* info) const
    {
        if (onLoadInterceptImpl_) {
            return onLoadInterceptImpl_(info);
        }
        return false;
    }
    void SetOnLoadIntercept(OnLoadInterceptImpl&& onLoadInterceptImpl)
    {
        if (onLoadInterceptImpl == nullptr) {
            return;
        }

        onLoadInterceptImpl_ = onLoadInterceptImpl;
    }

    using OnOverrideUrlLoadingImpl = std::function<bool(const BaseEventInfo* info)>;
    bool OnOverrideUrlLoading(const BaseEventInfo* info) const
    {
        if (onOverrideUrlLoadingImpl_) {
            return onOverrideUrlLoadingImpl_(info);
        }
        return false;
    }
    void SetOnOverrideUrlLoading(OnOverrideUrlLoadingImpl&& onOverrideUrlLoadingImpl)
    {
        if (onOverrideUrlLoadingImpl == nullptr) {
            return;
        }

        onOverrideUrlLoadingImpl_ = onOverrideUrlLoadingImpl;
    }

    using OnInterceptRequestImpl = std::function<RefPtr<WebResponse>(const BaseEventInfo* info)>;
    RefPtr<WebResponse> OnInterceptRequest(const BaseEventInfo* info) const
    {
        if (onInterceptRequestImpl_) {
            return onInterceptRequestImpl_(info);
        }
        return nullptr;
    }

    bool IsEmptyOnInterceptRequest() const
    {
        return onInterceptRequestImpl_ == nullptr;
    }

    void SetOnInterceptRequest(OnInterceptRequestImpl&& onInterceptRequestImpl)
    {
        if (onInterceptRequestImpl == nullptr) {
            return;
        }
        onInterceptRequestImpl_ = std::move(onInterceptRequestImpl);
    }

    void SetOnMouseEventCallback(const OnMouseCallback& onMouseId)
    {
        onMouseEvent_ = onMouseId;
    }

    OnMouseCallback GetOnMouseEventCallback() const
    {
        return onMouseEvent_;
    }

    void SetOnKeyEventCallback(const OnKeyEventCallback& onKeyEventId)
    {
        onKeyEvent_ = onKeyEventId;
    }

    OnKeyEventCallback GetOnKeyEventCallback() const
    {
        return onKeyEvent_;
    }

    void SetSearchResultReceiveEventId(const EventMarker& searchResultReceiveEventId)
    {
        CHECK_NULL_VOID(declaration_);
        declaration_->SetSearchResultReceiveEventId(searchResultReceiveEventId);
    }

    const EventMarker& GetSearchResultReceiveEventId() const
    {
        return declaration_->GetSearchResultReceiveEventId();
    }

    void SetMediaPlayGestureAccess(bool isNeedGestureAccess)
    {
        isNeedGestureAccess_ = isNeedGestureAccess;
    }

    bool IsMediaPlayGestureAccess() const
    {
        return isNeedGestureAccess_;
    }

    const OnDragFunc& GetOnDragStartId() const
    {
        return onDragStartId_;
    }

    void SetOnDragStartId(const OnDragFunc& onDragStartId)
    {
        onDragStartId_ = onDragStartId;
    }

    const OnDropFunc& GetOnDragEnterId() const
    {
        return onDragEnterId_;
    }

    void SetOnDragEnterId(const OnDropFunc& onDragEnterId)
    {
        onDragEnterId_ = onDragEnterId;
    }

    const OnDropFunc& GetOnDragMoveId() const
    {
        return onDragMoveId_;
    }

    void SetOnDragMoveId(const OnDropFunc& onDragMoveId)
    {
        onDragMoveId_ = onDragMoveId;
    }

    const OnDropFunc& GetOnDragLeaveId() const
    {
        return onDragLeaveId_;
    }

    void SetOnDragLeaveId(const OnDropFunc& onDragLeaveId)
    {
        onDragLeaveId_ = onDragLeaveId;
    }

    const OnDropFunc& GetOnDropId() const
    {
        return onDropId_;
    }

    void SetOnDropId(const OnDropFunc& onDropId)
    {
        onDropId_ = onDropId;
    }

    void SetJsProxyCallback(JsProxyCallback&& jsProxyCallback)
    {
        jsProxyCallback_ = std::move(jsProxyCallback);
    }

    void CallJsProxyCallback()
    {
        if (jsProxyCallback_) {
            jsProxyCallback_();
        }
    }

    void SetOnInterceptKeyEventCallback(const PreKeyEventCallback& onPreKeyEventId)
    {
        onPreKeyEvent_ = onPreKeyEventId;
    }

    PreKeyEventCallback GetOnInterceptKeyEventCallback() const
    {
        return onPreKeyEvent_;
    }

    void SetOverScrollId(const EventMarker& overScrollId)
    {
        CHECK_NULL_VOID(declaration_);
        declaration_->SetOverScrollId(overScrollId);
    }

    const EventMarker& GetOverScrollId() const
    {
        return declaration_->GetOverScrollId();
    }

    void SetNativeEmbedLifecycleChangeId(const EventMarker& embedLifecycleChangeId)
    {
        CHECK_NULL_VOID(declaration_);
        declaration_->SetNativeEmbedLifecycleChangeId(embedLifecycleChangeId);
    }

    const EventMarker& GetNativeEmbedLifecycleChangeId() const
    {
        return declaration_->GetNativeEmbedLifecycleChangeId();
    }

    void SetNativeEmbedVisibilityChangeId(const EventMarker& embedVisibilityChangeId)
    {
        CHECK_NULL_VOID(declaration_);
        declaration_->SetNativeEmbedVisibilityChangeId(embedVisibilityChangeId);
    }

    const EventMarker& GetNativeEmbedVisibilityChangeId() const
    {
        return declaration_->GetNativeEmbedVisibilityChangeId();
    }

    void SetNativeEmbedGestureEventId(const EventMarker& embedGestureEventId)
    {
        CHECK_NULL_VOID(declaration_);
        declaration_->SetNativeEmbedGestureEventId(embedGestureEventId);
    }

    const EventMarker& GetNativeEmbedGestureEventId() const
    {
        return declaration_->GetNativeEmbedGestureEventId();
    }

    void SetRenderProcessNotRespondingId(const EventMarker& renderNotRespondingId)
    {
        CHECK_NULL_VOID(declaration_);
        declaration_->SetRenderProcessNotRespondingId(renderNotRespondingId);
    }

    const EventMarker& GetRenderProcessNotRespondingId() const
    {
        return declaration_->GetRenderProcessNotRespondingId();
    }

    void SetRenderProcessRespondingId(const EventMarker& renderRespondingId)
    {
        CHECK_NULL_VOID(declaration_);
        declaration_->SetRenderProcessRespondingId(renderRespondingId);
    }

    const EventMarker& GetRenderProcessRespondingId() const
    {
        return declaration_->GetRenderProcessRespondingId();
    }

    void SetViewportFitChangedId(const EventMarker& viewportFitId)
    {
        CHECK_NULL_VOID(declaration_);
        declaration_->SetViewportFitChangedId(viewportFitId);
    }

    const EventMarker& GetViewportFitChangedId() const
    {
        return declaration_->GetViewportFitChangedId();
    }

    void SetAdsBlockedEventId(const EventMarker& adsBlockedEventId)
    {
        CHECK_NULL_VOID(declaration_);
        declaration_->SetAdsBlockedEventId(adsBlockedEventId);
    }

    const EventMarker& GetAdsBlockedEventId() const
    {
        return declaration_->GetAdsBlockedEventId();
    }

private:
    RefPtr<WebDeclaration> declaration_;
    CreatedCallback createdCallback_ = nullptr;
    ReleasedCallback releasedCallback_ = nullptr;
    ErrorCallback errorCallback_ = nullptr;
    SetWebIdCallback setWebIdCallback_ = nullptr;
    SetHapPathCallback setHapPathCallback_ = nullptr;
    JsProxyCallback jsProxyCallback_ = nullptr;
    RefPtr<WebDelegate> delegate_;
    RefPtr<WebController> webController_;
    OnCommonDialogImpl onAlertImpl_;
    OnCommonDialogImpl onConfirmImpl_;
    OnCommonDialogImpl onPromptImpl_;
    OnCommonDialogImpl onBeforeUnloadImpl_;
    OnConsoleImpl consoleImpl_;
    OnFileSelectorShowImpl onFileSelectorShowImpl_;
    OnFullScreenEnterImpl onFullScreenEnterImpl_;
    OnUrlLoadInterceptImpl onUrlLoadInterceptImpl_;
    OnLoadInterceptImpl onLoadInterceptImpl_;
    OnOverrideUrlLoadingImpl onOverrideUrlLoadingImpl_;
    OnHttpAuthRequestImpl onHttpAuthRequestImpl_;
    OnSslErrorRequestImpl onSslErrorRequestImpl_;
    OnAllSslErrorRequestImpl onAllSslErrorRequestImpl_;
    OnSslSelectCertRequestImpl onSslSelectCertRequestImpl_;
    OnContextMenuImpl onContextMenuImpl_;
    OnContextMenuHideImpl onContextMenuHideImpl_;
    OnInterceptRequestImpl onInterceptRequestImpl_ = nullptr;
    OnProgressChangeImpl onProgressChangeImpl_ = nullptr;
    OnWindowNewImpl onWindowNewImpl_ = nullptr;

    std::string type_;
    bool incognitoMode_ = false;
    bool isJsEnabled_ = true;
    bool isContentAccessEnabled_ = true;
    bool isFileAccessEnabled_ = true;
    std::string userAgent_;
    std::string customScheme_;
    WeakPtr<FocusNode> focusElement_;
    bool isOnLineImageAccessEnabled_ = false;
    bool isDomStorageAccessEnabled_ = false;
    bool isImageAccessEnabled_ = true;
    MixedModeContent mixedContentMode_ = MixedModeContent::MIXED_CONTENT_NEVER_ALLOW;
    bool isZoomAccessEnabled_ = true;
    bool isGeolocationAccessEnabled_ = true;
    bool isOverviewModeAccessEnabled_ = true;
    bool isFileFromUrlAccessEnabled_ = false;
    bool isDatabaseAccessEnabled_ = false;
    int32_t textZoomRatioNum_ = DEFAULT_TEXT_ZOOM_RATIO;
    WebCacheMode cacheMode_ = WebCacheMode::DEFAULT;
    bool isWebDebuggingAccessEnabled_ = false;
    bool isMultiWindowAccessEnabled_ = false;
    bool isAllowWindowOpenMethod_ = false;
    OnMouseCallback onMouseEvent_;
    OnKeyEventCallback onKeyEvent_;
    float initialScale_ = 0;
    bool isInitialScaleSet_ = false;
    int32_t backgroundColor_ = 0;
    bool isBackgroundColor_ = false;
    bool isNeedGestureAccess_ = true;
    bool isNativeEmbedMode_ = false;
    bool isSmoothDragResizeEnabled_ = false;
    std::string tag_;
    std::string tag_type_;
    OnDragFunc onDragStartId_;
    OnDropFunc onDragEnterId_;
    OnDropFunc onDragMoveId_;
    OnDropFunc onDragLeaveId_;
    OnDropFunc onDropId_;
    bool isPinchSmoothModeEnabled_ = false;
    PreKeyEventCallback onPreKeyEvent_;
    bool isPopup_ = false;
    int32_t parentNWebId_ = -1;
    OverScrollMode OverScrollMode_ = OverScrollMode::NEVER;
    CopyOptions CopyOptionMode_ = CopyOptions::Distributed;
    std::tuple<bool, bool> native_video_player_config_{false, false};
    std::string shared_render_process_token_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_WEB_COMPONENT_H
