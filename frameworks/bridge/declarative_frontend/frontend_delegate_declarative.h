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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_FRONTEND_DELEGATE_DECLARATIVE_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_FRONTEND_DELEGATE_DECLARATIVE_H

#include <future>
#include <mutex>
#include <unordered_map>

#include "base/memory/ace_type.h"
#include "base/thread/cancelable_callback.h"
#include "core/common/js_message_dispatcher.h"
#include "core/pipeline/pipeline_context.h"
#include "frameworks/bridge/common/accessibility/accessibility_node_manager.h"
#if !defined(WINDOWS_PLATFORM) and !defined(MAC_PLATFORM)
#include "frameworks/bridge/common/accessibility/js_accessibility_manager.h"
#else
#include "frameworks/bridge/common/inspector/js_inspector_manager.h"
#endif
#include "frameworks/bridge/common/manifest/manifest_parser.h"
#include "frameworks/bridge/js_frontend/engine/common/group_js_bridge.h"
#include "frameworks/bridge/js_frontend/frontend_delegate.h"
#include "frameworks/bridge/js_frontend/frontend_delegate_impl.h"
#include "frameworks/bridge/js_frontend/js_ace_page.h"

namespace OHOS::Ace::Framework {

class FrontendDelegateDeclarative : public FrontendDelegate {
    DECLARE_ACE_TYPE(FrontendDelegateDeclarative, FrontendDelegate);

public:
    FrontendDelegateDeclarative(const RefPtr<TaskExecutor>& taskExecutor, const LoadJsCallback& loadCallback,
        const JsMessageDispatcherSetterCallback& transferCallback, const EventCallback& asyncEventCallback,
        const EventCallback& syncEventCallback, const UpdatePageCallback& updatePageCallback,
        const ResetStagingPageCallback& resetLoadingPageCallback, const DestroyPageCallback& destroyPageCallback,
        const DestroyApplicationCallback& destroyApplicationCallback, const TimerCallback& timerCallback,
        const MediaQueryCallback& mediaQueryCallback, const RequestAnimationCallback& requestAnimationCallback,
        const JsCallback& jsCallback);
    ~FrontendDelegateDeclarative() override = default;

    void AttachPipelineContext(const RefPtr<PipelineContext>& context) override;
    void SetAssetManager(const RefPtr<AssetManager>& assetManager) override;

    // JSFrontend delegate functions.
    void RunPage(const std::string& url, const std::string& params);
    void SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& dispatcher) const;
    void TransferComponentResponseData(int32_t callbackId, int32_t code, std::vector<uint8_t>&& data);
    void TransferJsResponseData(int32_t callbackId, int32_t code, std::vector<uint8_t>&& data) const;
    void TransferJsPluginGetError(int32_t callbackId, int32_t errorCode, std::string&& errorMessage) const;
    void TransferJsEventData(int32_t callbackId, int32_t code, std::vector<uint8_t>&& data) const;
    void LoadPluginJsCode(std::string&& jsCode) const;
    void OnJSCallback(const std::string& callbackId, const std::string& data);
    bool OnPageBackPress();
    void OnBackGround();
    void OnForground();
    void OnSuspended();
    bool OnStartContinuation();
    void OnCompleteContinuation(int32_t code);
    void OnSaveData(std::string& data);
    bool OnRestoreData(const std::string& data);
    void OnNewRequest(const std::string& data);
    void CallPopPage();
    void OnApplicationDestroy(const std::string& packageName);

    // Accessibility delegate functions.
    RefPtr<Framework::AccessibilityNodeManager> GetJSAccessibilityManager() const
    {
        return jsAccessibilityManager_;
    }
    void FireAccessibilityEvent(const AccessibilityEvent& accessibilityEvent);
    void InitializeAccessibilityCallback();

    void OnMediaQueryUpdate() override;
    void OnSurfaceChanged();
    // JSEventHandler delegate functions.
    void FireAsyncEvent(const std::string& eventId, const std::string& param, const std::string& jsonArgs);
    bool FireSyncEvent(const std::string& eventId, const std::string& param, const std::string& jsonArgs);
    void FireSyncEvent(
        const std::string& eventId, const std::string& param, const std::string& jsonArgs, std::string& result);

    // FrontendDelegate overrides.
    void Push(const std::string& uri, const std::string& params) override;
    void Replace(const std::string& uri, const std::string& params) override;
    void Back(const std::string& uri) override;
    void Clear() override;
    int32_t GetStackSize() const override;
    void GetState(int32_t& index, std::string& name, std::string& path) override;
    void TriggerPageUpdate(int32_t pageId, bool directExecute = false) override;

    void PostJsTask(std::function<void()>&& task) override;

    const std::string& GetAppID() const override;
    const std::string& GetAppName() const override;
    const std::string& GetVersionName() const override;
    int32_t GetVersionCode() const override;
    const WindowConfig& GetWindowConfig() const;

    void ShowToast(const std::string& message, int32_t duration, const std::string& bottom) override;
    void ShowDialog(const std::string& title, const std::string& message,
        const std::vector<std::pair<std::string, std::string>>& buttons, bool autoCancel,
        std::function<void(int32_t, int32_t)>&& callback, const std::set<std::string>& callbacks) override;

    Rect GetBoundingRectData(NodeId nodeId) override;
    // For async event.
    void SetCallBackResult(const std::string& callBackId, const std::string& result) override;

    void WaitTimer(const std::string& callbackId, const std::string& delay, bool isInterval, bool isFirst) override;
    void ClearTimer(const std::string& callbackId) override;

    void PostSyncTaskToPage(std::function<void()>&& task) override;
    void AddTaskObserver(std::function<void()>&& task) override;
    void RemoveTaskObserver() override;

    bool GetAssetContent(const std::string& url, std::string& content) override;
    bool GetAssetContent(const std::string& url, std::vector<uint8_t>& content) override;

    // i18n
    void GetI18nData(std::unique_ptr<JsonValue>& json) override;

    void GetResourceConfiguration(std::unique_ptr<JsonValue>& json) override;

    void GetConfigurationCommon(const std::string& filePath, std::unique_ptr<JsonValue>& data) override;

    void ChangeLocale(const std::string& language, const std::string& countryOrRegion) override;

    void RegisterFont(const std::string& familyName, const std::string& familySrc) override;

    void HandleImage(const std::string& src, std::function<void(int32_t)>&& callback,
        const std::set<std::string>& callbacks) override;

    void RequestAnimationFrame(const std::string& callbackId) override;

    void CancelAnimationFrame(const std::string& callbackId) override;

    SingleTaskExecutor GetAnimationJsTask() override;

    SingleTaskExecutor GetUiTask() override;

    const RefPtr<MediaQueryInfo>& GetMediaQueryInfoInstance() override
    {
        return mediaQueryInfo_;
    }

    const RefPtr<GroupJsBridge>& GetGroupJsBridge() override
    {
        return groupJsBridge_;
    }

    RefPtr<PipelineContext> GetPipelineContext() override;

    void SetGroupJsBridge(const RefPtr<GroupJsBridge>& groupJsBridge)
    {
        groupJsBridge_ = groupJsBridge;
    }

    RefPtr<JsAcePage> GetPage(int32_t pageId) const override;

    void RebuildAllPages();

    virtual void* GetAbility() override
    {
        return ability_;
    }

    void SetAbility(void* ability)
    {
        ability_ = ability;
    }

private:
    int32_t GenerateNextPageId();
    void RecyclePageId(int32_t pageId);

    void LoadPage(int32_t pageId, const std::string& url, bool isMainPage, const std::string& params);
    void OnPageReady(const RefPtr<Framework::JsAcePage>& page, const std::string& url, bool isMainPage);
    void FlushPageCommand(const RefPtr<Framework::JsAcePage>& page, const std::string& url, bool isMainPage);
    void AddPageLocked(const RefPtr<JsAcePage>& page);
    void SetCurrentPage(int32_t pageId);

    void OnPushPageSuccess(const RefPtr<JsAcePage>& page, const std::string& url);
    void OnPopToPageSuccess(const std::string& url);
    void PopToPage(const std::string& url);
    int32_t OnPopPageSuccess();
    void PopPage();

    void PopPageTransitionListener(const TransitionEvent& event, int32_t destroyPageId);

    void PopToPageTransitionListener(const TransitionEvent& event, const std::string& url, int32_t pageId);

    int32_t OnClearInvisiblePagesSuccess();
    void ClearInvisiblePages();

    void OnReplacePageSuccess(const RefPtr<JsAcePage>& page, const std::string& url);
    void ReplacePage(const RefPtr<JsAcePage>& page, const std::string& url);
    void LoadReplacePage(int32_t pageId, const std::string& url, const std::string& params);

    uint64_t GetSystemRealTime();

    // Page lifecycle
    void OnPageShow();
    void OnPageHide();
    void OnPageDestroy(int32_t pageId);

    int32_t GetRunningPageId() const;
    std::string GetRunningPageUrl() const;
    int32_t GetPageIdByUrl(const std::string& url);

    void ResetStagingPage();
    void FlushAnimationTasks();

    std::atomic<uint64_t> pageIdPool_ = 0;
    int32_t callbackCnt_ = 0;
    bool isRouteStackFull_ = false;
    bool isStagingPageExist_ = false;
    std::string mainPagePath_;
    std::vector<PageInfo> pageRouteStack_;
    std::unordered_map<int32_t, RefPtr<JsAcePage>> pageMap_;
    std::unordered_map<int32_t, std::string> jsCallBackResult_;

    LoadJsCallback loadJs_;
    JsMessageDispatcherSetterCallback dispatcherCallback_;
    EventCallback asyncEvent_;
    EventCallback syncEvent_;
    UpdatePageCallback updatePage_;
    ResetStagingPageCallback resetStagingPage_;
    DestroyPageCallback destroyPage_;
    DestroyApplicationCallback destroyApplication_;
    TimerCallback timer_;
    std::unordered_map<std::string, CancelableCallback<void()>> timeoutTaskMap_;
    MediaQueryCallback mediaQueryCallback_;
    RequestAnimationCallback requestAnimationCallback_;
    JsCallback jsCallback_;
    RefPtr<Framework::ManifestParser> manifestParser_;
    RefPtr<Framework::AccessibilityNodeManager> jsAccessibilityManager_;
    RefPtr<MediaQueryInfo> mediaQueryInfo_;
    RefPtr<GroupJsBridge> groupJsBridge_;

    RefPtr<TaskExecutor> taskExecutor_;
    RefPtr<AssetManager> assetManager_;

    PipelineContextHolder pipelineContextHolder_;

    BaseId::IdType pageTransitionListenerId_ = 0L;
    std::queue<std::string> animationFrameTaskIds_;
    std::unordered_map<std::string, CancelableCallback<void()>> animationFrameTaskMap_;

    mutable std::mutex mutex_;
    void* ability_ = nullptr;
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_FRONTEND_DELEGATE_DECLARATIVE_H
