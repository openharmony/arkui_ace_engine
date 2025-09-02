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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_EVENT_HUB_H

#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/event/event_hub.h"

#define ACE_WEB_EVENT_PROPERTY(name, type)                                                                     \
public:                                                                                                        \
    void Set##name##Event(std::function<type(const std::shared_ptr<BaseEventInfo>& info)>&& prop##name##Event) \
    {                                                                                                          \
        prop##name##Event_ = std::move(prop##name##Event);                                                     \
    }                                                                                                          \
                                                                                                               \
    const std::function<type(const std::shared_ptr<BaseEventInfo>& info)>& Get##name##Event() const            \
    {                                                                                                          \
        return prop##name##Event_;                                                                             \
    }                                                                                                          \
                                                                                                               \
    void Fire##name##Event(const std::shared_ptr<BaseEventInfo>& info) const                                   \
    {                                                                                                          \
        if (prop##name##Event_) {                                                                              \
            prop##name##Event_(info);                                                                          \
        }                                                                                                      \
    }                                                                                                          \
                                                                                                               \
private:                                                                                                       \
    std::function<type(const std::shared_ptr<BaseEventInfo>& info)> prop##name##Event_

namespace OHOS::Ace::NG {
class WebEventHub : public EventHub {
    DECLARE_ACE_TYPE(WebEventHub, EventHub);

public:
    WebEventHub() = default;
    ~WebEventHub() override = default;

    void SetOnCommonDialogEvent(std::function<bool(const std::shared_ptr<BaseEventInfo>& info)>&& onCommonDialogImpl,
        DialogEventType dialogEventType)
    {
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

    bool FireOnCommonDialogEvent(const std::shared_ptr<BaseEventInfo>& info, DialogEventType dialogEventType) const
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

    void SetOnKeyEvent(std::function<void(KeyEventInfo& keyEventInfo)>&& propOnKeyEvent)
    {
        propOnKeyEvent_ = propOnKeyEvent;
    }

    const std::function<void(KeyEventInfo& keyEventInfo)>& GetOnKeyEvent() const
    {
        return propOnKeyEvent_;
    }

    void SetOnMouseEvent(std::function<void(MouseInfo& info)>&& propOnMouseEvent)
    {
        propOnMouseEvent_ = propOnMouseEvent;
    }

    const std::function<void(MouseInfo& info)>& GetOnMouseEvent() const
    {
        return propOnMouseEvent_;
    }

    void SetOnPreKeyEvent(std::function<bool(KeyEventInfo& keyEventInfo)>&& propOnPreKeyEvent)
    {
        propOnPreKeyEvent_ = propOnPreKeyEvent;
    }

    const std::function<bool(KeyEventInfo& keyEventInfo)>& GetOnPreKeyEvent() const
    {
        return propOnPreKeyEvent_;
    }

    ACE_WEB_EVENT_PROPERTY(OnAudioStateChanged, void);
    ACE_WEB_EVENT_PROPERTY(OnPageStarted, void);
    ACE_WEB_EVENT_PROPERTY(OnPageFinished, void);
    ACE_WEB_EVENT_PROPERTY(OnHttpErrorReceive, void);
    ACE_WEB_EVENT_PROPERTY(OnErrorReceive, void);
    ACE_WEB_EVENT_PROPERTY(OnConsole, bool);
    ACE_WEB_EVENT_PROPERTY(OnProgressChange, void);
    ACE_WEB_EVENT_PROPERTY(OnTitleReceive, void);
    ACE_WEB_EVENT_PROPERTY(OnFullScreenExit, void);
    ACE_WEB_EVENT_PROPERTY(OnGeolocationHide, void);
    ACE_WEB_EVENT_PROPERTY(OnGeolocationShow, void);
    ACE_WEB_EVENT_PROPERTY(OnRequestFocus, void);
    ACE_WEB_EVENT_PROPERTY(OnDownloadStart, void);
    ACE_WEB_EVENT_PROPERTY(OnFullScreenEnter, void);
    ACE_WEB_EVENT_PROPERTY(OnHttpAuthRequest, bool);
    ACE_WEB_EVENT_PROPERTY(OnSslErrorRequest, bool);
    ACE_WEB_EVENT_PROPERTY(OnAllSslErrorRequest, bool);
    ACE_WEB_EVENT_PROPERTY(OnSslSelectCertRequest, bool);
    ACE_WEB_EVENT_PROPERTY(OnInterceptRequest, RefPtr<WebResponse>);
    ACE_WEB_EVENT_PROPERTY(OnOverrideErrorPage, std::string);
    ACE_WEB_EVENT_PROPERTY(OnUrlLoadIntercept, bool);
    ACE_WEB_EVENT_PROPERTY(OnLoadIntercept, bool);
    ACE_WEB_EVENT_PROPERTY(OnOverrideUrlLoading, bool);
    ACE_WEB_EVENT_PROPERTY(OnFileSelectorShow, bool);
    ACE_WEB_EVENT_PROPERTY(OnContextMenuShow, bool);
    ACE_WEB_EVENT_PROPERTY(OnContextMenuHide, void);
    ACE_WEB_EVENT_PROPERTY(OnRenderExited, void);
    ACE_WEB_EVENT_PROPERTY(OnRefreshAccessedHistory, void);
    ACE_WEB_EVENT_PROPERTY(OnResourceLoad, void);
    ACE_WEB_EVENT_PROPERTY(OnScaleChange, void);
    ACE_WEB_EVENT_PROPERTY(OnScroll, void);
    ACE_WEB_EVENT_PROPERTY(OnPermissionRequest, void);
    ACE_WEB_EVENT_PROPERTY(OnScreenCaptureRequest, void);
    ACE_WEB_EVENT_PROPERTY(OnSearchResultReceive, void);
    ACE_WEB_EVENT_PROPERTY(OnWindowNew, void);
    ACE_WEB_EVENT_PROPERTY(OnActivateContent, void);
    ACE_WEB_EVENT_PROPERTY(OnWindowExit, void);
    ACE_WEB_EVENT_PROPERTY(OnPageVisible, void);
    ACE_WEB_EVENT_PROPERTY(OnDataResubmitted, void);
    ACE_WEB_EVENT_PROPERTY(OnFaviconReceived, void);
    ACE_WEB_EVENT_PROPERTY(OnFirstContentfulPaint, void);
    ACE_WEB_EVENT_PROPERTY(OnFirstMeaningfulPaint, void);
    ACE_WEB_EVENT_PROPERTY(OnLargestContentfulPaint, void);
    ACE_WEB_EVENT_PROPERTY(OnTouchIconUrl, void);
    ACE_WEB_EVENT_PROPERTY(OnOverScroll, void);
    ACE_WEB_EVENT_PROPERTY(OnNavigationEntryCommitted, void);
    ACE_WEB_EVENT_PROPERTY(OnSafeBrowsingCheckResult, void);
    ACE_WEB_EVENT_PROPERTY(OnNativeEmbedLifecycleChange, void);
    ACE_WEB_EVENT_PROPERTY(OnNativeEmbedVisibilityChange, void);
    ACE_WEB_EVENT_PROPERTY(OnNativeEmbedGesture, void);
    ACE_WEB_EVENT_PROPERTY(OnNativeEmbedMouse, void);
    ACE_WEB_EVENT_PROPERTY(OnNativeEmbedObjectParamChange, void);
    ACE_WEB_EVENT_PROPERTY(OnIntelligentTrackingPreventionResult, void);
    ACE_WEB_EVENT_PROPERTY(OnRenderProcessNotResponding, void);
    ACE_WEB_EVENT_PROPERTY(OnRenderProcessResponding, void);
    ACE_WEB_EVENT_PROPERTY(OnViewportFitChanged, void);
    ACE_WEB_EVENT_PROPERTY(OnInterceptKeyboardAttach,  WebKeyboardOption);
    ACE_WEB_EVENT_PROPERTY(OnAdsBlocked, void);
    ACE_WEB_EVENT_PROPERTY(OnLoadStarted, void);
    ACE_WEB_EVENT_PROPERTY(OnLoadFinished, void);
    ACE_WEB_EVENT_PROPERTY(OnPdfScrollAtBottom, void);
    ACE_WEB_EVENT_PROPERTY(OnPdfLoad, void);

private:
    std::function<void(KeyEventInfo& keyEventInfo)> propOnKeyEvent_;
    std::function<void(MouseInfo& info)> propOnMouseEvent_;
    OnDragFunc propOnDragStartEvent_;
    OnDropFunc propOnDragEnterEvent_;
    OnDropFunc propOnDragMoveEvent_;
    OnDropFunc propOnDragLeaveEvent_;
    OnDropFunc propOnDropEvent_;
    std::function<bool(const std::shared_ptr<BaseEventInfo>& info)> onAlertImpl_;
    std::function<bool(const std::shared_ptr<BaseEventInfo>& info)> onConfirmImpl_;
    std::function<bool(const std::shared_ptr<BaseEventInfo>& info)> onPromptImpl_;
    std::function<bool(const std::shared_ptr<BaseEventInfo>& info)> onBeforeUnloadImpl_;
    std::function<bool(KeyEventInfo& keyEventInfo)> propOnPreKeyEvent_;

    ACE_DISALLOW_COPY_AND_MOVE(WebEventHub);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_EVENT_HUB_H
