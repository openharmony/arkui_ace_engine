/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_FRONTEND_DELEGATE_DECLARATIVE_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_FRONTEND_DELEGATE_DECLARATIVE_NG_H

#include "base/memory/ace_type.h"
#include "base/thread/cancelable_callback.h"
#include "base/utils/measure_util.h"
#include "core/components_ng/render/snapshot_param.h"
#include "frameworks/bridge/common/accessibility/accessibility_node_manager.h"
#include "frameworks/bridge/common/manifest/manifest_parser.h"
#include "frameworks/bridge/common/utils/pipeline_context_holder.h"
#include "frameworks/bridge/declarative_frontend/ng/page_router_manager.h"
#include "frameworks/bridge/js_frontend/engine/common/group_js_bridge.h"
#include "frameworks/bridge/js_frontend/engine/common/js_engine.h"
#include "frameworks/bridge/js_frontend/frontend_delegate.h"
#include "frameworks/bridge/js_frontend/frontend_delegate_impl.h"
#include "frameworks/bridge/js_frontend/js_ace_page.h"

namespace OHOS::Ace::Framework {

class FrontendDelegateDeclarativeNG : public FrontendDelegate {
    DECLARE_ACE_TYPE(FrontendDelegateDeclarativeNG, FrontendDelegate);

public:
    FrontendDelegateDeclarativeNG(const RefPtr<TaskExecutor>& taskExecutor);
    ~FrontendDelegateDeclarativeNG() override = default;

    void AttachPipelineContext(const RefPtr<PipelineBase>& context) override;
    void AttachSubPipelineContext(const RefPtr<PipelineBase>& context);
    // restore
    std::pair<RouterRecoverRecord, UIContentErrorCode> RestoreRouterStack(
        const std::string& contentInfo, ContentInfoType type) override
    {
        return std::make_pair(RouterRecoverRecord(), UIContentErrorCode::NO_ERRORS);
    }
    std::string GetContentInfo(ContentInfoType type) override;
    // JSFrontend delegate NG functions.
    void RunPage(const std::string& url, const std::string& params,
        const std::string& profile, bool isNamedRouter = false);
    void RunPage(const std::shared_ptr<std::vector<uint8_t>>& content,
        const std::string& params, const std::string& profile);
    void RunIntentPage();
    void SetRouterIntentInfo(const std::string& intentInfoSerialized, bool isColdStart,
        const std::function<void()>&& loadPageCallback);
    void OnConfigurationUpdated(const std::string& data);
    bool OnStartContinuation();
    void OnCompleteContinuation(int32_t code);
    void OnSaveData(std::string& data);
    bool OnRestoreData(const std::string& data);
    void OnRemoteTerminated();
    void SetColorMode(ColorMode colorMode);
    void CallPopPage();
    void OnApplicationDestroy(const std::string& packageName);
    void UpdateApplicationState(const std::string& packageName, Frontend::State state);
    void OnWindowDisplayModeChanged(bool isShownInMultiWindow, const std::string& data);
    void NotifyAppStorage(
        const WeakPtr<Framework::JsEngine>& jsEngineWeak, const std::string& key, const std::string& value);

    // set callback
    void SetMediaQueryCallback(MediaQueryCallback&& mediaQueryCallback);
    void SetLayoutInspectorCallback(const LayoutInspectorCallback& layoutInspectorCallback);
    void SetDrawInspectorCallback(const DrawInspectorCallback& drawInspectorCallback);
    void SetDrawChildrenInspectorCallback(const DrawChildrenInspectorCallback& drawChildrenInspectorCallback);
    void SetIsDrawChildrenCallbackFuncExistCallback(
        const IsDrawChildrenCallbackFuncExistCallback& IsDrawChildrenCallbackFuncExistCallback);
    void SetOnStartContinuationCallBack(OnStartContinuationCallBack&& onStartContinuationCallBack);
    void SetOnCompleteContinuationCallBack(OnCompleteContinuationCallBack&& onCompleteContinuationCallBack);
    void SetOnSaveDataCallBack(OnSaveDataCallBack&& onSaveDataCallBack);
    void SetOnRemoteTerminatedCallBack(OnRemoteTerminatedCallBack&& onRemoteTerminatedCallBack);
    void SetOnRestoreDataCallBack(OnRestoreDataCallBack&& onRestoreDataCallBack);
    void SetDestroyApplicationCallback(DestroyApplicationCallback&& destroyApplicationCallback);
    void SetUpdateApplicationStateCallback(UpdateApplicationStateCallback&& updateApplicationStateCallback);
    void SetOnWindowDisplayModeChangedCallback(
        OnWindowDisplayModeChangedCallBack&& onWindowDisplayModeChangedCallBack);
    void SetExternalEventCallback(ExternalEventCallback&& externalEventCallback);
    void SetTimerCallback(TimerCallback&& timerCallback);

    RefPtr<Framework::AccessibilityNodeManager> GetJSAccessibilityManager() const
    {
        return jsAccessibilityManager_;
    }
    void FireAccessibilityEvent(const AccessibilityEvent& accessibilityEvent);
    void InitializeAccessibilityCallback();

    void OnSurfaceChanged();
    void OnMediaQueryUpdate(bool isSynchronous = false) override;
    void OnLayoutCompleted(const std::string& componentId);
    void OnDrawCompleted(const std::string& componentId);
    void OnDrawChildrenCompleted(const std::string& componentId);
    bool IsDrawChildrenCallbackFuncExist(const std::string& componentId);
    void FireExternalEvent(const std::string& eventId, const std::string& componentId, uint32_t nodeId, bool isDestroy);

    // FrontendDelegate overrides.
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
    void PostponePageTransition() override;
    void LaunchPageTransition() override;
    void Clear() override;
    int32_t GetStackSize() const override;
    void GetState(int32_t& index, std::string& name, std::string& path) override;
    void GetRouterStateByIndex(int32_t& index, std::string& name, std::string& path, std::string& params) override;
    void GetRouterStateByUrl(std::string& url, std::vector<StateInfo>& stateArray) override;
    RefPtr<JsAcePage> GetPage(int32_t pageId) const override
    {
        return nullptr;
    }
    size_t GetComponentsCount() override;
    std::string GetParams() override;
    void NavigatePage(uint8_t type, const PageTarget& target, const std::string& params);

    void TriggerPageUpdate(int32_t pageId, bool directExecute = false) override {}

    void PostJsTask(std::function<void()>&& task, const std::string& name) override;
    const std::string& GetAppID() const override;
    const std::string& GetAppName() const override;
    const std::string& GetVersionName() const override;
    int32_t GetVersionCode() const override;

    double MeasureText(MeasureContext context) override;
    Size MeasureTextSize(MeasureContext context) override;
    void ShowToast(const NG::ToastInfo& toastInfo, std::function<void(int32_t)>&& callback = nullptr) override;
    void CloseToast(const int32_t toastId, std::function<void(int32_t)>&& callback = nullptr) override;
    void ShowDialog(const std::string& title, const std::string& message, const std::vector<ButtonInfo>& buttons,
        bool autoCancel, std::function<void(int32_t, int32_t)>&& callback,
        const std::set<std::string>& callbacks) override;
    void ShowDialog(const std::string& title, const std::string& message, const std::vector<ButtonInfo>& buttons,
        bool autoCancel, std::function<void(int32_t, int32_t)>&& callback, const std::set<std::string>& callbacks,
        std::function<void(bool)>&& onStatusChanged) override;
    void ShowDialog(const PromptDialogAttr &dialogAttr, const std::vector<ButtonInfo> &buttons,
        std::function<void(int32_t, int32_t)> &&callback, const std::set<std::string> &callbacks) override;
    void ShowDialog(const PromptDialogAttr &dialogAttr, const std::vector<ButtonInfo> &buttons,
        std::function<void(int32_t, int32_t)> &&callback, const std::set<std::string> &callbacks,
        std::function<void(bool)>&& onStatusChanged) override;
    void RemoveCustomDialog(int32_t instanceId) override;
    void OpenCustomDialog(const PromptDialogAttr &dialogAttr, std::function<void(int32_t)> &&callback) override;
    void CloseCustomDialog(const int32_t dialogId) override;
    void CloseCustomDialog(const WeakPtr<NG::UINode>& node, std::function<void(int32_t)> &&callback) override;
    void UpdateCustomDialog(const WeakPtr<NG::UINode>& node, const PromptDialogAttr &dialogAttr,
        std::function<void(int32_t)> &&callback) override;
    std::optional<double> GetTopOrder() override;
    std::optional<double> GetBottomOrder() override;

    void EnableAlertBeforeBackPage(const std::string& message, std::function<void(int32_t)>&& callback) override;

    void DisableAlertBeforeBackPage() override;

    void ShowActionMenu(const std::string& title, const std::vector<ButtonInfo>& button,
        std::function<void(int32_t, int32_t)>&& callback) override;

    void ShowActionMenu(const std::string& title, const std::vector<ButtonInfo>& button,
        std::function<void(int32_t, int32_t)>&& callback, std::function<void(bool)>&& onStatusChanged) override;

    void ShowActionMenuInner(DialogProperties& dialogProperties, const std::vector<ButtonInfo>& button,
        std::function<void(int32_t, int32_t)>&& callback);

    void WaitTimer(const std::string& callbackId, const std::string& delay, bool isInterval, bool isFirst) override;
    void ClearTimer(const std::string& callbackId) override;
    void AddTaskObserver(std::function<void()>&& task) override {}
    void RemoveTaskObserver() override {}
    void PushJsCallbackToRenderNode(NodeId id, double ratio, std::function<void(bool, double)>&& callback) override {}
    void PostSyncTaskToPage(std::function<void()>&& task, const std::string& name) override;
    void SetCallBackResult(const std::string& callBackId, const std::string& result) override {}
    bool GetAssetContent(const std::string& url, std::string& content) override;
    bool GetAssetContent(const std::string& url, std::vector<uint8_t>& content) override;
    std::string GetAssetPath(const std::string& url) override;
    // i18n
    void GetI18nData(std::unique_ptr<JsonValue>& json) override {}

    void GetResourceConfiguration(std::unique_ptr<JsonValue>& json) override {}

    void GetConfigurationCommon(const std::string& filePath, std::unique_ptr<JsonValue>& data) override {}
    Rect GetBoundingRectData(NodeId nodeId) override
    {
        return Rect();
    }

    std::string GetInspector(NodeId nodeId) override
    {
        return "";
    }
    int32_t GetMinPlatformVersion() override
    {
        return manifestParser_->GetMinPlatformVersion();
    }

    void LoadResourceConfiguration(std::map<std::string, std::string>& mediaResourceFileMap,
        std::unique_ptr<JsonValue>& currentResourceData) override
    {}

    void ChangeLocale(const std::string& language, const std::string& countryOrRegion) override;

    void RegisterFont(const std::string& familyName, const std::string& familySrc, const std::string& bundleName = "",
        const std::string& moduleName = "") override;

    void GetSystemFontList(std::vector<std::string>& fontList) override;

    bool GetSystemFont(const std::string& fontName, FontInfo& fontInfo) override;

    void GetUIFontConfig(FontConfigJsonInfo& fontConfigJsonInfo) override;

    void HandleImage(const std::string& src, std::function<void(bool, int32_t, int32_t)>&& callback) override {}

    void GetSnapshot(const std::string& componentId,
        std::function<void(std::shared_ptr<Media::PixelMap>, int32_t, std::function<void()>)>&& callback,
        const NG::SnapshotOptions& options) override;

    void CreateSnapshot(std::function<void()>&& customBuilder,
        std::function<void(std::shared_ptr<Media::PixelMap>, int32_t, std::function<void()>)>&& callback,
        bool enableInspector, const NG::SnapshotParam& param) override;

    std::pair<int32_t, std::shared_ptr<Media::PixelMap>> GetSyncSnapshot(
        RefPtr<NG::FrameNode>& node, const NG::SnapshotOptions& options) override;
        
    std::pair<int32_t, std::shared_ptr<Media::PixelMap>> GetSyncSnapshot(const std::string& componentId,
        const NG::SnapshotOptions& options) override;

    void GetSnapshotByUniqueId(int32_t uniqueId,
        std::function<void(std::shared_ptr<Media::PixelMap>, int32_t, std::function<void()>)>&& callback,
        const NG::SnapshotOptions& options) override;

    std::pair<int32_t, std::shared_ptr<Media::PixelMap>> GetSyncSnapshotByUniqueId(int32_t uniqueId,
        const NG::SnapshotOptions& options) override;

    void CreateSnapshotFromComponent(const RefPtr<NG::UINode>& nodeWk,
        std::function<void(std::shared_ptr<Media::PixelMap>, int32_t, std::function<void()>)>&& callback,
        bool enableInspector, const NG::SnapshotParam& param) override;

    void AddFrameNodeToOverlay(
        const RefPtr<NG::FrameNode>& node, std::optional<int32_t> index = std::nullopt) override;
    void AddFrameNodeWithOrder(const RefPtr<NG::FrameNode>& node, std::optional<double> levelOrder) override;
    void RemoveFrameNodeOnOverlay(const RefPtr<NG::FrameNode>& node) override;
    void ShowNodeOnOverlay(const RefPtr<NG::FrameNode>& node) override;
    void HideNodeOnOverlay(const RefPtr<NG::FrameNode>& node) override;
    void ShowAllNodesOnOverlay() override;
    void HideAllNodesOnOverlay() override;
    bool SetOverlayManagerOptions(const NG::OverlayManagerInfo& overlayInfo) override;
    std::optional<NG::OverlayManagerInfo> GetOverlayManagerOptions() override;

    void RequestAnimationFrame(const std::string& callbackId) override {}

    void CancelAnimationFrame(const std::string& callbackId) override {}
    SingleTaskExecutor GetAnimationJsTask() override;

    SingleTaskExecutor GetUiTask() override;

    const RefPtr<MediaQueryInfo>& GetMediaQueryInfoInstance() override
    {
        return mediaQueryInfo_;
    }

    void SetGroupJsBridge(const RefPtr<GroupJsBridge>& groupJsBridge)
    {
        groupJsBridge_ = groupJsBridge;
    }
    const RefPtr<GroupJsBridge>& GetGroupJsBridge() override
    {
        return groupJsBridge_;
    }

    RefPtr<PipelineBase> GetPipelineContext() override;

    void SetPageRouterManager(const RefPtr<NG::PageRouterManager>& routerMgr)
    {
        pageRouterManager_ = routerMgr;
    }
    const RefPtr<NG::PageRouterManager>& GetPageRouterManager() const
    {
        return pageRouterManager_;
    }

    WindowConfig& GetWindowConfig()
    {
        return manifestParser_->GetWindowConfig();
    }

    const RefPtr<Framework::ManifestParser>& GetManifestParser() const
    {
        return manifestParser_;
    }

    const RefPtr<TaskExecutor>& GetTaskExecutor() const
    {
        return taskExecutor_;
    }

    bool OnPageBackPress();

    void OnPageShow();

    void OnPageHide();
    void OnForeground();

    std::string GetCurrentPageUrl();

    // Get the currently running JS page information in NG structure.
    RefPtr<RevSourceMap> GetCurrentPageSourceMap();

    // Get the currently running JS page information in NG structure.
    RefPtr<RevSourceMap> GetFaAppSourceMap();

    void GetStageSourceMap(std::unordered_map<std::string, RefPtr<Framework::RevSourceMap>>& sourceMap);
    void ShowDialogInner(DialogProperties& dialogProperties, std::function<void(int32_t, int32_t)>&& callback,
        const std::set<std::string>& callbacks);

    void RebuildAllPages();

private:
    void ParsePartialPropertiesFromAttr(DialogProperties& dialogProperties, const PromptDialogAttr& dialogAttr);
    DialogProperties ParsePropertiesFromAttr(const PromptDialogAttr &dialogAttr);

    PipelineContextHolder pipelineContextHolder_;
    RefPtr<TaskExecutor> taskExecutor_;
    RefPtr<NG::PageRouterManager> pageRouterManager_;
    RefPtr<Framework::ManifestParser> manifestParser_;
    RefPtr<MediaQueryInfo> mediaQueryInfo_;
    RefPtr<GroupJsBridge> groupJsBridge_;

    RefPtr<Framework::AccessibilityNodeManager> jsAccessibilityManager_;
    RefPtr<RevSourceMap> appSourceMap_;
    std::queue<std::string> animationFrameTaskIds_;
    std::unordered_map<std::string, CancelableCallback<void()>> animationFrameTaskMap_;

    std::unordered_map<std::string, CancelableCallback<void()>> timeoutTaskMap_;

    MediaQueryCallback mediaQueryCallback_;
    LayoutInspectorCallback layoutInspectorCallback_;
    DrawInspectorCallback drawInspectorCallback_;
    DrawChildrenInspectorCallback drawChildrenInspectorCallback_;
    IsDrawChildrenCallbackFuncExistCallback isDrawChildrenCallbackFuncExistCallback_;
    OnStartContinuationCallBack onStartContinuationCallBack_;
    OnCompleteContinuationCallBack onCompleteContinuationCallBack_;
    OnSaveDataCallBack onSaveDataCallBack_;
    OnRemoteTerminatedCallBack onRemoteTerminatedCallBack_;
    OnRestoreDataCallBack onRestoreDataCallBack_;
    DestroyApplicationCallback destroyApplication_;
    UpdateApplicationStateCallback updateApplicationState_;
    OnWindowDisplayModeChangedCallBack onWindowDisplayModeChanged_;
    ExternalEventCallback externalEvent_;
    TimerCallback timer_;

    mutable std::mutex mutex_;
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_FRONTEND_DELEGATE_DECLARATIVE_NG_H
