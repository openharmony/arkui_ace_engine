/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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
#include "base/memory/referenced.h"
#include "base/thread/cancelable_callback.h"
#include "base/utils/measure_util.h"
#include "bridge/declarative_frontend/ng/page_router_manager.h"
#include "core/common/js_message_dispatcher.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/render/snapshot_param.h"
#include "core/pipeline/pipeline_context.h"
#include "frameworks/bridge/common/accessibility/accessibility_node_manager.h"
#include "frameworks/bridge/common/manifest/manifest_parser.h"
#include "frameworks/bridge/js_frontend/engine/common/group_js_bridge.h"
#include "frameworks/bridge/js_frontend/engine/common/js_engine.h"
#include "frameworks/bridge/js_frontend/frontend_delegate.h"
#include "frameworks/bridge/js_frontend/frontend_delegate_impl.h"
#include "frameworks/bridge/js_frontend/js_ace_page.h"

namespace OHOS::Ace::Framework {

using ExternalEventCallback = std::function<void(const std::string&, const uint32_t&, const bool&)>;

enum class RouterAction {
    PUSH = 0,
    REPLACE,
    BACK,
    CLEAR,
};

struct RouterTask {
    RouterAction action = RouterAction::PUSH;
    PageTarget target = PageTarget("");
    std::string params;
    std::function<void(const std::string&, int32_t)> errorCallback;
};

class FrontendDelegateDeclarative : public FrontendDelegate {
    DECLARE_ACE_TYPE(FrontendDelegateDeclarative, FrontendDelegate);

public:
    FrontendDelegateDeclarative(const RefPtr<TaskExecutor>& taskExecutor, const LoadJsCallback& loadCallback,
        const JsMessageDispatcherSetterCallback& transferCallback, const EventCallback& asyncEventCallback,
        const EventCallback& syncEventCallback, const UpdatePageCallback& updatePageCallback,
        const ResetStagingPageCallback& resetLoadingPageCallback, const DestroyPageCallback& destroyPageCallback,
        const DestroyApplicationCallback& destroyApplicationCallback,
        const UpdateApplicationStateCallback& updateApplicationStateCallback, const TimerCallback& timerCallback,
        const MediaQueryCallback& mediaQueryCallback, const LayoutInspectorCallback& layoutInpsectorCallback,
        const DrawInspectorCallback& drawInpsectorCallback, const RequestAnimationCallback& requestAnimationCallback,
        const JsCallback& jsCallback, const OnWindowDisplayModeChangedCallBack& onWindowDisplayModeChangedCallBack,
        const OnConfigurationUpdatedCallBack& onConfigurationUpdatedCallBack,
        const OnSaveAbilityStateCallBack& onSaveAbilityStateCallBack,
        const OnRestoreAbilityStateCallBack& onRestoreAbilityStateCallBack, const OnNewWantCallBack& onNewWantCallBack,
        const OnMemoryLevelCallBack& onMemoryLevelCallBack,
        const OnStartContinuationCallBack& onStartContinuationCallBack,
        const OnCompleteContinuationCallBack& onCompleteContinuationCallBack,
        const OnRemoteTerminatedCallBack& onRemoteTerminatedCallBack, const OnSaveDataCallBack& onSaveDataCallBack,
        const OnRestoreDataCallBack& onRestoreDataCallBack, const ExternalEventCallback& externalEventCallback);
    ~FrontendDelegateDeclarative() override;

    void AttachPipelineContext(const RefPtr<PipelineBase>& context) override;
    void AttachSubPipelineContext(const RefPtr<PipelineBase>& context);

    // JSFrontend delegate functions.
    UIContentErrorCode RunPage(
        const std::string& url, const std::string& params, const std::string& profile, bool isNamedRouter = false);
    void RunPage(const std::shared_ptr<std::vector<uint8_t>>& content,
        const std::string& params, const std::string& profile);
    void SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& dispatcher) const;
    void TransferComponentResponseData(int32_t callbackId, int32_t code, std::vector<uint8_t>&& data);
    void TransferJsResponseData(int32_t callbackId, int32_t code, std::vector<uint8_t>&& data) const;
#if defined(PREVIEW)
    void TransferJsResponseDataPreview(int32_t callbackId, int32_t code, ResponseData responseData) const;
#endif
    void TransferJsPluginGetError(int32_t callbackId, int32_t errorCode, std::string&& errorMessage) const;
    void TransferJsEventData(int32_t callbackId, int32_t code, std::vector<uint8_t>&& data) const;
    void LoadPluginJsCode(std::string&& jsCode) const;
    void LoadPluginJsByteCode(std::vector<uint8_t>&& jsCode, std::vector<int32_t>&& jsCodeLen) const;
    void OnJSCallback(const std::string& callbackId, const std::string& data);
    bool OnPageBackPress();
    void OnBackGround();
    void OnForeground();
    void OnConfigurationUpdated(const std::string& data);
    void OnSaveAbilityState(std::string& data);
    void OnRestoreAbilityState(const std::string& data);
    void OnNewWant(const std::string& data);
    bool OnStartContinuation();
    void OnCompleteContinuation(int32_t code);
    void OnMemoryLevel(int32_t level);
    void OnSaveData(std::string& data);
    void GetPluginsUsed(std::string& data);
    bool OnRestoreData(const std::string& data);
    void OnRemoteTerminated();
    void OnNewRequest(const std::string& data);
    void SetColorMode(ColorMode colorMode);
    void CallPopPage();
    void OnApplicationDestroy(const std::string& packageName);
    void UpdateApplicationState(const std::string& packageName, Frontend::State state);
    void OnWindowDisplayModeChanged(bool isShownInMultiWindow, const std::string& data);
    void NotifyAppStorage(
        const WeakPtr<Framework::JsEngine>& jsEngineWeak, const std::string& key, const std::string& value);

    // restore
    std::pair<RouterRecoverRecord, UIContentErrorCode> RestoreRouterStack(
        const std::string& contentInfo, ContentInfoType type) override;
    std::string GetContentInfo(ContentInfoType type) override;

    // Accessibility delegate functions.
    RefPtr<Framework::AccessibilityNodeManager> GetJSAccessibilityManager() const
    {
        return jsAccessibilityManager_;
    }
    void FireAccessibilityEvent(const AccessibilityEvent& accessibilityEvent);
    void InitializeAccessibilityCallback();

    void OnMediaQueryUpdate(bool isSynchronous = false) override;
    void OnSurfaceChanged();
    void OnLayoutCompleted(const std::string& componentId);
    void OnDrawCompleted(const std::string& componentId);
    // JSEventHandler delegate functions.
    void FireAsyncEvent(const std::string& eventId, const std::string& param, const std::string& jsonArgs);
    bool FireSyncEvent(const std::string& eventId, const std::string& param, const std::string& jsonArgs);
    void FireSyncEvent(
        const std::string& eventId, const std::string& param, const std::string& jsonArgs, std::string& result);
    void FireExternalEvent(const std::string& eventId, const std::string& componentId, uint32_t nodeId, bool isDestroy);

    // FrontendDelegate overrides.
    void Push(const PageTarget& target, const std::string& params,
        const std::function<void(const std::string&, int32_t)>& errorCallback = nullptr);
    void Replace(const PageTarget& target, const std::string& params,
        const std::function<void(const std::string&, int32_t)>& errorCallback = nullptr);
    void BackWithTarget(const PageTarget& target, const std::string& params);

    void Push(const std::string& uri, const std::string& params) override;
    void PushWithMode(const std::string& uri, const std::string& params, uint32_t routerMode) override;
    void PushWithCallback(const std::string& uri, const std::string& params, bool recoverable,
        const std::function<void(const std::string&, int32_t)>& errorCallback, uint32_t routerMode = 0) override;
    void PushNamedRoute(const std::string& uri, const std::string& params, bool recoverable,
        const std::function<void(const std::string&, int32_t)>& errorCallback, uint32_t routerMode = 0) override;
    void Replace(const std::string& uri, const std::string& params) override;
    void ReplaceWithMode(const std::string& uri, const std::string& params, uint32_t routerMode) override;
    void ReplaceWithCallback(const std::string& uri, const std::string& params, bool recoverable,
        const std::function<void(const std::string&, int32_t)>& errorCallback, uint32_t routerMode = 0) override;
    void ReplaceNamedRoute(const std::string& uri, const std::string& params, bool recoverable,
        const std::function<void(const std::string&, int32_t)>& errorCallback, uint32_t routerMode = 0) override;
    void Back(const std::string& uri, const std::string& params) override;
    void BackToIndex(int32_t index, const std::string& params) override;
    void Clear() override;
    int32_t GetStackSize() const override;
    int32_t GetCurrentPageIndex() const override;
    void GetState(int32_t& index, std::string& name, std::string& path) override;
    void GetRouterStateByIndex(int32_t& index, std::string& name, std::string& path, std::string& params) override;
    bool IsUnrestoreByIndex(int32_t index);
    void GetRouterStateByUrl(std::string& url, std::vector<StateInfo>& stateArray) override;
    std::string GetParams() override;
    int32_t GetIndexByUrl(const std::string& url) override;

    void PostponePageTransition() override;
    void LaunchPageTransition() override;
    size_t GetComponentsCount() override;
    void TriggerPageUpdate(int32_t pageId, bool directExecute = false) override;

    void PostJsTask(std::function<void()>&& task, const std::string& name) override;

    const std::string& GetAppID() const override;
    const std::string& GetAppName() const override;
    const std::string& GetVersionName() const override;
    int32_t GetVersionCode() const override;
    WindowConfig& GetWindowConfig()
    {
        return manifestParser_->GetWindowConfig();
    }

    double MeasureText(MeasureContext context) override;
    Size MeasureTextSize(MeasureContext context) override;

    void ShowToast(const NG::ToastInfo& toastInfo, std::function<void(int32_t)>&& callback = nullptr) override;
    void CloseToast(const int32_t toastId, std::function<void(int32_t)>&& callback = nullptr) override;
    void SetToastStopListenerCallback(std::function<void()>&& stopCallback) override;
    void ShowDialog(const std::string& title, const std::string& message, const std::vector<ButtonInfo>& buttons,
        bool autoCancel, std::function<void(int32_t, int32_t)>&& callback,
        const std::set<std::string>& callbacks) override;
    void ShowDialog(const std::string& title, const std::string& message, const std::vector<ButtonInfo>& buttons,
        bool autoCancel, std::function<void(int32_t, int32_t)>&& callback,
        const std::set<std::string>& callbacks, std::function<void(bool)>&& onStatusChanged) override;
    void ShowDialog(const PromptDialogAttr &dialogAttr, const std::vector<ButtonInfo> &buttons,
        std::function<void(int32_t, int32_t)> &&callback, const std::set<std::string> &callbacks) override;
    void ShowDialog(const PromptDialogAttr &dialogAttr, const std::vector<ButtonInfo> &buttons,
        std::function<void(int32_t, int32_t)> &&callback, const std::set<std::string> &callbacks,
        std::function<void(bool)>&& onStatusChanged) override;
    void ShowDialogInner(DialogProperties& dialogProperties, std::function<void(int32_t, int32_t)>&& callback,
        const std::set<std::string>& callbacks);
    void RemoveCustomDialog(int32_t instanceId) override;
    void OpenCustomDialog(const PromptDialogAttr &dialogAttr, std::function<void(int32_t)> &&callback) override;
    void CloseCustomDialog(const int32_t dialogId) override;
    void CloseCustomDialog(const WeakPtr<NG::UINode>& node, std::function<void(int32_t)> &&callback) override;
    void UpdateCustomDialog(const WeakPtr<NG::UINode>& node, const PromptDialogAttr &dialogAttr,
        std::function<void(int32_t)> &&callback) override;

    RefPtr<NG::ChainedTransitionEffect> GetTransitionEffect(void* value) override;

    void EnableAlertBeforeBackPage(const std::string& message, std::function<void(int32_t)>&& callback) override;

    void DisableAlertBeforeBackPage() override;

    void ShowActionMenu(const std::string& title, const std::vector<ButtonInfo>& button,
        std::function<void(int32_t, int32_t)>&& callback) override;
    void ShowActionMenu(const std::string& title, const std::vector<ButtonInfo>& button,
        std::function<void(int32_t, int32_t)>&& callback, std::function<void(bool)>&& onStatusChanged) override;
    void ShowActionMenu(const PromptDialogAttr& dialogAttr, const std::vector<ButtonInfo>& buttons,
        std::function<void(int32_t, int32_t)>&& callback) override;
    void ShowActionMenuInner(DialogProperties& dialogProperties, const std::vector<ButtonInfo>& button,
        std::function<void(int32_t, int32_t)>&& callback);
    void ShowActionMenuInnerNG(DialogProperties& dialogProperties, const std::vector<ButtonInfo>& button,
        std::function<void(int32_t, int32_t)>&& callback);

    Rect GetBoundingRectData(NodeId nodeId) override;

    std::string GetInspector(NodeId nodeId) override;

    void PushJsCallbackToRenderNode(NodeId id, double ratio, std::function<void(bool, double)>&& callback) override;
    // For async event.
    void SetCallBackResult(const std::string& callBackId, const std::string& result) override;

    void WaitTimer(const std::string& callbackId, const std::string& delay, bool isInterval, bool isFirst) override;
    void ClearTimer(const std::string& callbackId) override;

    void PostSyncTaskToPage(std::function<void()>&& task, const std::string& name) override;
    void AddTaskObserver(std::function<void()>&& task) override;
    void RemoveTaskObserver() override;

    bool GetAssetContent(const std::string& url, std::string& content) override;
    bool GetAssetContent(const std::string& url, std::vector<uint8_t>& content) override;
    std::string GetAssetPath(const std::string& url) override;

    // i18n
    void GetI18nData(std::unique_ptr<JsonValue>& json) override;

    void GetResourceConfiguration(std::unique_ptr<JsonValue>& json) override;

    void GetConfigurationCommon(const std::string& filePath, std::unique_ptr<JsonValue>& data) override;

    int32_t GetMinPlatformVersion() override;

    void LoadResourceConfiguration(std::map<std::string, std::string>& mediaResourceFileMap,
        std::unique_ptr<JsonValue>& currentResourceData) override;

    void ChangeLocale(const std::string& language, const std::string& countryOrRegion) override;

    void RegisterFont(const std::string& familyName, const std::string& familySrc, const std::string& bundleName = "",
        const std::string& moduleName = "") override;

    void GetSystemFontList(std::vector<std::string>& fontList) override;

    bool GetSystemFont(const std::string& fontName, FontInfo& fontInfo) override;

    void GetUIFontConfig(FontConfigJsonInfo& fontConfigJsonInfo) override;

    void HandleImage(const std::string& src, std::function<void(bool, int32_t, int32_t)>&& callback) override;

    void GetSnapshot(const std::string& componentId,
        std::function<void(std::shared_ptr<Media::PixelMap>, int32_t, std::function<void()>)>&& callback,
        const NG::SnapshotOptions& options) override;
    void CreateSnapshot(std::function<void()>&& customBuilder,
        std::function<void(std::shared_ptr<Media::PixelMap>, int32_t, std::function<void()>)>&& callback,
        bool enableInspector, const NG::SnapshotParam& param) override;

    std::pair<int32_t, std::shared_ptr<Media::PixelMap>> GetSyncSnapshot(const std::string& componentId,
        const NG::SnapshotOptions& options) override;

    void GetSnapshotByUniqueId(int32_t uniqueId,
        std::function<void(std::shared_ptr<Media::PixelMap>, int32_t, std::function<void()>)>&& callback,
        const NG::SnapshotOptions& options) override;

    std::pair<int32_t, std::shared_ptr<Media::PixelMap>> GetSyncSnapshotByUniqueId(int32_t uniqueId,
        const NG::SnapshotOptions& options) override;

    void AddFrameNodeToOverlay(
        const RefPtr<NG::FrameNode>& node, std::optional<int32_t> index = std::nullopt) override;
    void RemoveFrameNodeOnOverlay(const RefPtr<NG::FrameNode>& node) override;
    void ShowNodeOnOverlay(const RefPtr<NG::FrameNode>& node) override;
    void HideNodeOnOverlay(const RefPtr<NG::FrameNode>& node) override;
    void ShowAllNodesOnOverlay() override;
    void HideAllNodesOnOverlay() override;
    bool SetOverlayManagerOptions(const NG::OverlayManagerInfo& overlayInfo) override;
    std::optional<NG::OverlayManagerInfo> GetOverlayManagerOptions() override;

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

#if defined(PREVIEW)
    void SetPagePath(const std::string& pagePath)
    {
        if (manifestParser_) {
            manifestParser_->SetPagePath(pagePath);
        }
    }
#endif

    RefPtr<PipelineBase> GetPipelineContext() override;

    void SetGroupJsBridge(const RefPtr<GroupJsBridge>& groupJsBridge)
    {
        groupJsBridge_ = groupJsBridge;
    }

    RefPtr<JsAcePage> GetPage(int32_t pageId) const override;

    void RebuildAllPages();

    std::string GetCurrentPageUrl();

    // Get the currently running JS page information in NG structure.
    RefPtr<RevSourceMap> GetCurrentPageSourceMap();

    // Get the currently running JS page information in NG structure.
    RefPtr<RevSourceMap> GetFaAppSourceMap();

    void GetStageSourceMap(
        std::unordered_map<std::string, RefPtr<Framework::RevSourceMap>>& sourceMap);

#if defined(PREVIEW)
    void SetIsComponentPreview(NG::IsComponentPreviewCallback&& callback);
#endif

    void SetPageRouterManager(const RefPtr<NG::PageRouterManager>& routerMgr)
    {
        pageRouterManager_ = routerMgr;
    }
    const RefPtr<NG::PageRouterManager>& GetPageRouterManager() const
    {
        return pageRouterManager_;
    }

    const RefPtr<TaskExecutor>& GetTaskExecutor() const
    {
        return taskExecutor_;
    }

    const RefPtr<Framework::ManifestParser>& GetManifestParser() const
    {
        return manifestParser_;
    }

protected:
    bool isCardDelegate_ = false;

private:
    int32_t GenerateNextPageId();
    void RecyclePageId(int32_t pageId);

    UIContentErrorCode LoadPage(
        int32_t pageId, const PageTarget& target, bool isMainPage, const std::string& params, bool isRestore = false);
    void OnPageReady(const RefPtr<Framework::JsAcePage>& page, const std::string& url, bool isMainPage, bool isRestore);
    void FlushPageCommand(
        const RefPtr<Framework::JsAcePage>& page, const std::string& url, bool isMainPage, bool isRestore);
    void AddPageLocked(const RefPtr<JsAcePage>& page);
    void OnPrePageChange(const RefPtr<JsAcePage>& page);
    void SetCurrentPage(int32_t pageId);

    void OnPushPageSuccess(const RefPtr<JsAcePage>& page, const std::string& url);
    void OnPopToPageSuccess(const std::string& url);
    void PopToPage(const std::string& url);
    int32_t OnPopPageSuccess();
    void PopPage();
    void RestorePopPage(const RefPtr<JsAcePage>& page, const std::string& url);

    void PushPageTransitionListener(const TransitionEvent& event, const RefPtr<JsAcePage>& page);

    void PopPageTransitionListener(const TransitionEvent& event, int32_t destroyPageId);

    void PopToPageTransitionListener(const TransitionEvent& event, const std::string& url, int32_t pageId);

    void RestorePageTransitionListener(
        const TransitionEvent& event, const std::string& url, const RefPtr<JsAcePage>& page);

    int32_t OnClearInvisiblePagesSuccess();
    void ClearInvisiblePages();

    void OnReplacePageSuccess(const RefPtr<JsAcePage>& page, const std::string& url);
    void ReplacePage(const RefPtr<JsAcePage>& page, const std::string& url);
    void LoadReplacePage(int32_t pageId, const PageTarget& url, const std::string& params);

    void ReplacePageInSubStage(const RefPtr<JsAcePage>& page, const std::string& url);
    std::optional<int32_t> GetEffectiveContainerId() const;

    uint64_t GetSystemRealTime();

    // Page lifecycle
    void OnPageShow();
    void OnPageHide();
    void OnPageDestroy(int32_t pageId);

    int32_t GetRunningPageId() const;
    std::string GetRunningPageUrl() const;
    int32_t GetPageIdByUrl(const std::string& url, bool& isRestore);
    int32_t GetPageIdByUrl(const std::string& url)
    {
        bool tmp = false;
        return GetPageIdByUrl(url, tmp);
    }

    void ResetStagingPage();
    void FlushAnimationTasks();

    void StartPush(const PageTarget& target, const std::string& params,
        const std::function<void(const std::string&, int32_t)>& errorCallback);
    void StartReplace(const PageTarget& target, const std::string& params,
        const std::function<void(const std::string&, int32_t)>& errorCallback);
    void StartBack(const PageTarget& target, const std::string& params);
    void BackCheckAlert(const PageTarget& target, const std::string& params);
    void ProcessRouterTask();
    void AddRouterTask(const RouterTask& task);
    bool IsNavigationStage(const PageTarget& target);
    void RecycleSinglePage();
    void ClearAlertCallback(PageInfo pageInfo);
    bool CheckIndexValid(int32_t index) const;

    DialogProperties ParsePropertiesFromAttr(const PromptDialogAttr &dialogAttr);

    std::unique_ptr<JsonValue> GetNavigationJsonInfo();

    std::atomic<uint64_t> pageIdPool_ = 0;
    int32_t callbackCnt_ = 0;
    int32_t pageId_ = -1;
    bool isRouteStackFull_ = false;
    bool isStagingPageExist_ = false;
    int32_t singlePageId_ = -1;
    std::string mainPagePath_;
    PageTarget backUri_ = PageTarget("");
    std::string backParam_;
    std::vector<PageInfo> pageRouteStack_;
    std::unordered_map<int32_t, RefPtr<JsAcePage>> pageMap_;
    std::unordered_map<int32_t, std::string> pageParamMap_;
    std::unordered_map<int32_t, std::string> jsCallBackResult_;

    LoadJsCallback loadJs_;
    ExternalEventCallback externalEvent_;
    JsMessageDispatcherSetterCallback dispatcherCallback_;
    EventCallback asyncEvent_;
    EventCallback syncEvent_;
    UpdatePageCallback updatePage_;
    ResetStagingPageCallback resetStagingPage_;
    DestroyPageCallback destroyPage_;
    DestroyApplicationCallback destroyApplication_;
    UpdateApplicationStateCallback updateApplicationState_;
    TimerCallback timer_;
    std::unordered_map<std::string, CancelableCallback<void()>> timeoutTaskMap_;
    MediaQueryCallback mediaQueryCallback_;
    LayoutInspectorCallback layoutInspectorCallback_;
    DrawInspectorCallback drawInspectorCallback_;
    RequestAnimationCallback requestAnimationCallback_;
    JsCallback jsCallback_;
    OnWindowDisplayModeChangedCallBack onWindowDisplayModeChanged_;
    OnConfigurationUpdatedCallBack onConfigurationUpdated_;
    OnSaveAbilityStateCallBack onSaveAbilityState_;
    OnRestoreAbilityStateCallBack onRestoreAbilityState_;
    OnNewWantCallBack onNewWant_;
    OnMemoryLevelCallBack onMemoryLevel_;
    OnStartContinuationCallBack onStartContinuationCallBack_;
    OnCompleteContinuationCallBack onCompleteContinuationCallBack_;
    OnRemoteTerminatedCallBack onRemoteTerminatedCallBack_;
    OnSaveDataCallBack onSaveDataCallBack_;
    OnRestoreDataCallBack onRestoreDataCallBack_;
    RefPtr<Framework::ManifestParser> manifestParser_;
    RefPtr<Framework::AccessibilityNodeManager> jsAccessibilityManager_;
    RefPtr<MediaQueryInfo> mediaQueryInfo_;
    RefPtr<GroupJsBridge> groupJsBridge_;

    RefPtr<TaskExecutor> taskExecutor_;

    PipelineContextHolder pipelineContextHolder_;

    BaseId::IdType pageTransitionListenerId_ = 0L;
    std::queue<std::string> animationFrameTaskIds_;
    std::unordered_map<std::string, CancelableCallback<void()>> animationFrameTaskMap_;

    mutable std::mutex mutex_;

    std::queue<RouterTask> routerQueue_;
    mutable std::mutex routerQueueMutex_;

    RefPtr<RevSourceMap> appSourceMap_;
    RefPtr<NG::PageRouterManager> pageRouterManager_;
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_FRONTEND_DELEGATE_DECLARATIVE_H
