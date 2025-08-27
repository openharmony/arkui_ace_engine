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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_FRONTEND_DELEGATE_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_FRONTEND_DELEGATE_H

#include <vector>

#include "base/geometry/size.h"
#include "base/json/json_util.h"
#include "base/memory/ace_type.h"
#include "base/utils/measure_util.h"
#include "base/utils/noncopyable.h"
#include "core/common/router_recover_record.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/toast/toast_layout_property.h"
#include "core/components_ng/render/snapshot_param.h"
#include "core/event/ace_event_helper.h"
#include "core/pipeline/pipeline_base.h"
#include "frameworks/bridge/common/media_query/media_query_info.h"
#include "frameworks/bridge/common/utils/componentInfo.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract_bridge.h"
#include "frameworks/bridge/js_frontend/engine/common/group_js_bridge.h"
#include "frameworks/bridge/js_frontend/engine/common/js_constants.h"
#include "interfaces/inner_api/ace/constants.h"

namespace OHOS::Ace::Framework {
enum class AlertState { USER_CANCEL = 0, USER_CONFIRM, RECOVERY };

typedef struct RouterStateInfo {
    int32_t index = -1;
    std::string name;
    std::string path;
    std::string params;
} StateInfo;

class JsAcePage;

// A virtual interface which must be implemented as a backing for
// FrontendDelegateImpl instances.
//
// This is the primary interface by which the JsFrontend delegates
// FrontendDelegateImpl behavior out to QjsEngine for js to native calls.
class FrontendDelegate : public AceType {
    DECLARE_ACE_TYPE(FrontendDelegate, AceType);

public:
    FrontendDelegate() = default;
    ~FrontendDelegate() override = default;

    virtual void AttachPipelineContext(const RefPtr<PipelineBase>& context) = 0;
    ACE_EXPORT void SetAssetManager(const RefPtr<AssetManager>& assetManager)
    {
        assetManager_ = assetManager;
    }

    // ----------------
    // system.router
    // ----------------
    // Jump to the specified page.
    virtual void Push(const std::string& uri, const std::string& params) = 0;
    virtual void PushWithMode(const std::string& uri, const std::string& params, uint32_t routerMode) {}
    virtual void PushWithCallback(const std::string& uri, const std::string& params, bool recoverable,
        const std::function<void(const std::string&, int32_t)>& errorCallback, uint32_t routerMode = 0)
    {}
    virtual void PushNamedRoute(const std::string& uri, const std::string& params, bool recoverable,
        const std::function<void(const std::string&, int32_t)>& errorCallback, uint32_t routerMode = 0)
    {}
    // Jump to the specified page, but current page will be removed from the stack.
    virtual void Replace(const std::string& uri, const std::string& params) = 0;
    virtual void ReplaceWithMode(const std::string& uri, const std::string& params, uint32_t routerMode) {}
    virtual void ReplaceWithCallback(const std::string& uri, const std::string& params, bool recoverable,
        const std::function<void(const std::string&, int32_t)>& errorCallback, uint32_t routerMode = 0)
    {}
    virtual void ReplaceNamedRoute(const std::string& uri, const std::string& params, bool recoverable,
        const std::function<void(const std::string&, int32_t)>& errorCallback, uint32_t routerMode = 0)
    {}
    // Back to specified page or the previous page if url not set.
    virtual void Back(const std::string& uri, const std::string& params = "") = 0;
    // Back to specified page or the previous page if Index not set.
    virtual void BackToIndex(int32_t index, const std::string& params = "")
    {}
    // Postpone page transition after Begin called, usually to wait some async operation
    virtual void PostponePageTransition() = 0;
    // Begin page transition after Postpone called, usually to wait some async operation
    virtual void LaunchPageTransition() = 0;
    // Clear all the pages in stack except the top page, that is current page.
    virtual void Clear() = 0;
    // Gets the number of pages in the page stack.
    virtual int32_t GetStackSize() const = 0;
    // Gets the index of current page, only used for PagePattern::OnAttachToMainTree.
    virtual int32_t GetCurrentPageIndex() const
    {
        return GetStackSize();
    }
    // Gets current page's states
    virtual void GetState(int32_t& index, std::string& name, std::string& path) = 0;
    // Gets page's states by index.
    virtual void GetRouterStateByIndex(int32_t& index, std::string& name, std::string& path, std::string& params)
    {}
    // Gets page's states by url.
    virtual void GetRouterStateByUrl(std::string& url, std::vector<StateInfo>& stateArray)
    {}
    // Gets current page's components count
    virtual size_t GetComponentsCount() = 0;
    // Gets page's index by url
    virtual int32_t GetIndexByUrl(const std::string& url)
    {
        return -1;
    }
    // Gets current page's init params
    virtual std::string GetInitParams()
    {
        return "";
    }
    // Gets current page's params
    virtual std::string GetParams()
    {
        return "";
    }
    virtual void GetRectangleById(const std::string& key, NG::Rectangle& rectangle);

    virtual void ResetFocus();

    virtual bool RequestFocus(const std::string& value, bool isSyncRequest);

    virtual void SetRequestFocusCallback(std::function<void(NG::RequestFocusResult result)> callback);

    virtual void ResetRequestFocusCallback();

    virtual bool Activate(bool isActive, bool autoInactive = true);

    virtual bool GetFocusActive();

    virtual void SetAutoFocusTransfer(bool autoFocusTransfer);

    virtual void SetKeyProcessingMode(int32_t keyProcessingMode);

    virtual bool ConfigWindowMask(bool enable);

    // restore
    virtual std::pair<RouterRecoverRecord, UIContentErrorCode> RestoreRouterStack(
        const std::string& contentInfo, ContentInfoType type)
    {
        return std::make_pair(RouterRecoverRecord(), UIContentErrorCode::NO_ERRORS);
    }
    virtual std::string GetContentInfo(ContentInfoType type)
    {
        return "";
    }

    virtual void TriggerPageUpdate(int32_t pageId, bool directExecute = false) = 0;

    // posting js task from jsengine
    virtual void PostJsTask(std::function<void()>&& task, const std::string& name) = 0;
    virtual void PostUITask(std::function<void()>&& task, const std::string& name) {}

    // ----------------
    // system.app
    // ----------------
    virtual const std::string& GetAppID() const = 0;
    virtual const std::string& GetAppName() const = 0;
    virtual const std::string& GetVersionName() const = 0;
    virtual int32_t GetVersionCode() const = 0;

    // ----------------
    // system.measure
    // ----------------
    virtual double MeasureText(MeasureContext context) = 0;
    virtual Size MeasureTextSize(MeasureContext context) = 0;

    // ----------------
    // system.prompt
    // ----------------
    virtual void ShowToast(const NG::ToastInfo& toastInfo, std::function<void(int32_t)>&& callback) = 0;
    virtual void CloseToast(const int32_t toastId, std::function<void(int32_t)>&& callback) {};
    virtual void SetToastStopListenerCallback(std::function<void()>&& stopCallback) {};
    virtual void ShowDialog(const std::string& title, const std::string& message,
        const std::vector<ButtonInfo>& buttons, bool autoCancel, std::function<void(int32_t, int32_t)>&& callback,
        const std::set<std::string>& callbacks) = 0;
    virtual void ShowDialog(const PromptDialogAttr& dialogAttr, const std::vector<ButtonInfo>& buttons,
        std::function<void(int32_t, int32_t)>&& callback, const std::set<std::string>& callbacks) {};
    virtual void ShowDialog(const std::string& title, const std::string& message,
        const std::vector<ButtonInfo>& buttons, bool autoCancel, std::function<void(int32_t, int32_t)>&& callback,
        const std::set<std::string>& callbacks, std::function<void(bool)>&& onStatusChanged) {};
    virtual void ShowDialog(const PromptDialogAttr& dialogAttr, const std::vector<ButtonInfo>& buttons,
        std::function<void(int32_t, int32_t)>&& callback, const std::set<std::string>& callbacks,
        std::function<void(bool)>&& onStatusChanged) {};
    virtual void RemoveCustomDialog(int32_t instanceId) {};
    virtual void OpenCustomDialog(const PromptDialogAttr &dialogAttr, std::function<void(int32_t)> &&callback) {};
    virtual void CloseCustomDialog(const int32_t dialogId) {};
    virtual void CloseCustomDialog(const WeakPtr<NG::UINode>& node, std::function<void(int32_t)> &&callback) {};
    virtual void UpdateCustomDialog(const WeakPtr<NG::UINode>& node, const PromptDialogAttr &dialogAttr,
        std::function<void(int32_t)> &&callback) {};

    virtual std::optional<double> GetTopOrder()
    {
        return std::nullopt;
    }

    virtual std::optional<double> GetBottomOrder()
    {
        return std::nullopt;
    }

    virtual RefPtr<NG::ChainedTransitionEffect> GetTransitionEffect(void* value)
    {
        return nullptr;
    }

    virtual void EnableAlertBeforeBackPage(const std::string& message, std::function<void(int32_t)>&& callback) = 0;
    virtual void DisableAlertBeforeBackPage() = 0;

    virtual void ShowActionMenu(const std::string& title, const std::vector<ButtonInfo>& button,
        std::function<void(int32_t, int32_t)>&& callback) = 0;
    virtual void ShowActionMenu(const std::string& title, const std::vector<ButtonInfo>& button,
        std::function<void(int32_t, int32_t)>&& callback, std::function<void(bool)>&& onStatusChanged) {};
    virtual void ShowActionMenu(const PromptDialogAttr& dialogAttr, const std::vector<ButtonInfo>& buttons,
        std::function<void(int32_t, int32_t)>&& callback) {};
    virtual Rect GetBoundingRectData(NodeId nodeId) = 0;

    virtual std::string GetInspector(NodeId nodeId) = 0;

    virtual void PushJsCallbackToRenderNode(NodeId id, double ratio, std::function<void(bool, double)>&& callback) = 0;

    // ----------------
    // system.configuration
    // ----------------
    virtual void ChangeLocale(const std::string& language, const std::string& countryOrRegion) = 0;

    // ----------------
    // system.image
    // ----------------
    virtual void HandleImage(const std::string& src, std::function<void(bool, int32_t, int32_t)>&& callback) = 0;
    // ----------------
    // internal.jsResult
    // ----------------
    virtual void SetCallBackResult(const std::string& callBackId, const std::string& result) = 0;

    // ----------------
    // system.animation
    // ----------------
    virtual void RequestAnimationFrame(const std::string& callbackId) = 0;
    virtual void CancelAnimationFrame(const std::string& callbackId) = 0;

    virtual void GetSnapshot(const std::string& componentId,
        std::function<void(std::shared_ptr<Media::PixelMap>, int32_t, std::function<void()>)>&& callback,
        const NG::SnapshotOptions& options)
    {}
    virtual void CreateSnapshot(std::function<void()>&& customBuilder,
        std::function<void(std::shared_ptr<Media::PixelMap>, int32_t, std::function<void()>)>&& callback,
        bool enableInspector, const NG::SnapshotParam& param)
    {}

    virtual std::pair<int32_t, std::shared_ptr<Media::PixelMap>> GetSyncSnapshot(
        RefPtr<NG::FrameNode>& node, const NG::SnapshotOptions& options)
    {
        return {};
    }

    virtual std::pair<int32_t, std::shared_ptr<Media::PixelMap>> GetSyncSnapshot(const std::string& componentId,
        const NG::SnapshotOptions& options)
    {
        return {};
    }

    virtual void GetSnapshotByUniqueId(int32_t uniqueId,
        std::function<void(std::shared_ptr<Media::PixelMap>, int32_t, std::function<void()>)>&& callback,
        const NG::SnapshotOptions& options)
    {}

    virtual std::pair<int32_t, std::shared_ptr<Media::PixelMap>> GetSyncSnapshotByUniqueId(int32_t uniqueId,
        const NG::SnapshotOptions& options)
    {
        return {};
    }

    virtual void GetSnapshotWithRange(const NG::NodeIdentity& startID, const NG::NodeIdentity& endID,
        const bool isStartRect,
        std::function<void(std::shared_ptr<Media::PixelMap>, int32_t, std::function<void()>)>&& callback,
        const NG::SnapshotOptions& options)
    {}

    virtual void CreateSnapshotFromComponent(const RefPtr<NG::UINode>& nodeWk,
        std::function<void(std::shared_ptr<Media::PixelMap>, int32_t, std::function<void()>)>&& callback,
        bool enableInspector, const NG::SnapshotParam& param)
    {}

    virtual bool GetAssetContent(const std::string& url, std::string& content) = 0;
    virtual bool GetAssetContent(const std::string& url, std::vector<uint8_t>& content) = 0;
    virtual std::string GetAssetPath(const std::string& url) = 0;

    virtual void WaitTimer(const std::string& callbackId, const std::string& delay, bool isInterval, bool isFirst) = 0;
    virtual void ClearTimer(const std::string& callbackId) = 0;

    virtual void PostSyncTaskToPage(std::function<void()>&& task, const std::string& name) = 0;

    virtual void AddTaskObserver(std::function<void()>&& task) = 0;

    virtual void RemoveTaskObserver() = 0;

    virtual void GetI18nData(std::unique_ptr<JsonValue>& json) = 0;

    virtual void GetResourceConfiguration(std::unique_ptr<JsonValue>& json) = 0;

    virtual void GetConfigurationCommon(const std::string& filePath, std::unique_ptr<JsonValue>& data) = 0;

    virtual const RefPtr<MediaQueryInfo>& GetMediaQueryInfoInstance() = 0;

    virtual void OnMediaQueryUpdate(bool isSynchronous = false) = 0;

    virtual void RegisterFont(const std::string& familyName, const std::string& familySrc,
        const std::string& bundleName = "", const std::string& moduleName = "") = 0;

    virtual void GetSystemFontList(std::vector<std::string>& fontList) = 0;

    virtual bool GetSystemFont(const std::string& fontName, FontInfo& fontInfo) = 0;

    virtual void GetUIFontConfig(FontConfigJsonInfo& fontConfigJsonInfo) {}

    virtual void AddFrameNodeToOverlay(
        const RefPtr<NG::FrameNode>& node, std::optional<int32_t> index = std::nullopt) {}
    virtual void AddFrameNodeWithOrder(const RefPtr<NG::FrameNode>& node, std::optional<double> levelOrder) {}
    virtual void RemoveFrameNodeOnOverlay(const RefPtr<NG::FrameNode>& node) {}
    virtual void ShowNodeOnOverlay(const RefPtr<NG::FrameNode>& node) {}
    virtual void HideNodeOnOverlay(const RefPtr<NG::FrameNode>& node) {}
    virtual void ShowAllNodesOnOverlay() {}
    virtual void HideAllNodesOnOverlay() {}
    virtual bool SetOverlayManagerOptions(const NG::OverlayManagerInfo& overlayInfo)
    {
        return false;
    }
    virtual std::optional<NG::OverlayManagerInfo> GetOverlayManagerOptions()
    {
        return std::nullopt;
    }

    virtual SingleTaskExecutor GetAnimationJsTask() = 0;

    virtual SingleTaskExecutor GetUiTask() = 0;

    virtual RefPtr<PipelineBase> GetPipelineContext() = 0;

    virtual const RefPtr<GroupJsBridge>& GetGroupJsBridge() = 0;

    virtual RefPtr<JsAcePage> GetPage(int32_t pageId) const = 0;

    virtual int32_t GetMinPlatformVersion() = 0;

    template<typename T>
    bool ACE_EXPORT GetResourceData(const std::string& fileUri, T& content);

    template<typename T>
    bool ACE_EXPORT GetResourceData(const std::string& fileUri, T& content, std::string& ami);

    template<typename T>
    ACE_EXPORT static bool GetResourceData(const std::string& fileUri, const RefPtr<AssetManager>& assetManager,
        T& content);

    ACE_EXPORT RefPtr<AssetManager> GetAssetManager() const
    {
        return assetManager_;
    }

    virtual void LoadResourceConfiguration(std::map<std::string, std::string>& sortedResourcePath,
        std::unique_ptr<JsonValue>& currentResourceData) = 0;

    void DisallowPopLastPage()
    {
        disallowPopLastPage_ = true;
    }

    virtual void CallNativeHandler(const std::string& event, const std::string& params) {}

    virtual void GetBackgroundBlurStyleOption(napi_value value, BlurStyleOption& styleOption)
    {
        JSViewAbstractBridge::GetBackgroundBlurStyleOption(value, styleOption);
    }
    virtual void GetBackgroundEffect(napi_value value, EffectOption& styleOption)
    {
        JSViewAbstractBridge::GetBackgroundEffect(value, styleOption);
    }

protected:
    RefPtr<AssetManager> assetManager_;
    bool disallowPopLastPage_ = false;
    bool isFirstNotifyShow_ = true;

    ACE_DISALLOW_COPY_AND_MOVE(FrontendDelegate);
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_FRONTEND_DELEGATE_H
