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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_FRONTEND_DELEGATE_DECLARATIVE_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_FRONTEND_DELEGATE_DECLARATIVE_NG_H

#include "base/memory/ace_type.h"
#include "base/thread/cancelable_callback.h"
#include "frameworks/bridge/common/accessibility/accessibility_node_manager.h"
#include "frameworks/bridge/common/manifest/manifest_parser.h"
#include "frameworks/bridge/common/utils/pipeline_context_holder.h"
#include "frameworks/bridge/declarative_frontend/ng/page_router_manager.h"
#include "frameworks/bridge/js_frontend/engine/common/group_js_bridge.h"
#include "frameworks/bridge/js_frontend/engine/common/js_engine.h"
#include "frameworks/bridge/js_frontend/frontend_delegate.h"
#include "frameworks/bridge/js_frontend/js_ace_page.h"

namespace OHOS::Ace::Framework {

class FrontendDelegateDeclarativeNG : public FrontendDelegate {
    DECLARE_ACE_TYPE(FrontendDelegateDeclarativeNG, FrontendDelegate);

public:
    explicit FrontendDelegateDeclarativeNG(const RefPtr<TaskExecutor>& taskExecutor)
        : taskExecutor_(taskExecutor), manifestParser_(AceType::MakeRefPtr<Framework::ManifestParser>())
    {}
    ~FrontendDelegateDeclarativeNG() override = default;

    void AttachPipelineContext(const RefPtr<PipelineBase>& context) override;

    // distribute
    std::string RestoreRouterStack(const std::string& contentInfo) override
    {
        return "";
    }

    void OnMediaQueryUpdate() override {}

    void RunPage(const std::string& url, const std::string& params, const std::string& profile);

    // FrontendDelegate overrides.
    void Push(const std::string& uri, const std::string& params) override;
    void PushWithMode(const std::string& uri, const std::string& params, uint32_t routerMode) override;
    void Replace(const std::string& uri, const std::string& params) override;
    void ReplaceWithMode(const std::string& uri, const std::string& params, uint32_t routerMode) override;
    void Back(const std::string& uri, const std::string& params) override;
    void PostponePageTransition() override {}
    void LaunchPageTransition() override {}
    void Clear() override;
    int32_t GetStackSize() const override;
    void GetState(int32_t& index, std::string& name, std::string& path) override;
    RefPtr<JsAcePage> GetPage(int32_t pageId) const override;
    size_t GetComponentsCount() override
    {
        return 0;
    }
    std::string GetParams() override;
    void NavigatePage(uint8_t type, const PageTarget& target, const std::string& params);

    void TriggerPageUpdate(int32_t pageId, bool directExecute = false) override {}

    void PostJsTask(std::function<void()>&& task) override;

    const std::string& GetAppID() const override;
    const std::string& GetAppName() const override;
    const std::string& GetVersionName() const override;
    int32_t GetVersionCode() const override;

    void ShowToast(const std::string& message, int32_t duration, const std::string& bottom) override {}
    void ShowDialog(const std::string& title, const std::string& message, const std::vector<ButtonInfo>& buttons,
        bool autoCancel, std::function<void(int32_t, int32_t)>&& callback,
        const std::set<std::string>& callbacks) override
    {}

    void EnableAlertBeforeBackPage(const std::string& message, std::function<void(int32_t)>&& callback) override {}

    void DisableAlertBeforeBackPage() override {}

    void ShowActionMenu(const std::string& title, const std::vector<ButtonInfo>& button,
        std::function<void(int32_t, int32_t)>&& callback) override
    {}

    Rect GetBoundingRectData(NodeId nodeId) override
    {
        return Rect();
    }

    std::string GetInspector(NodeId nodeId) override
    {
        return "";
    }

    void PushJsCallbackToRenderNode(NodeId id, double ratio, std::function<void(bool, double)>&& callback) override {}
    void RemoveVisibleChangeNode(NodeId id) override {}
    // For async event.
    void SetCallBackResult(const std::string& callBackId, const std::string& result) override {}

    void WaitTimer(const std::string& callbackId, const std::string& delay, bool isInterval, bool isFirst) override {}
    void ClearTimer(const std::string& callbackId) override {}

    void PostSyncTaskToPage(std::function<void()>&& task) override;
    void AddTaskObserver(std::function<void()>&& task) override {}
    void RemoveTaskObserver() override {}

    bool GetAssetContent(const std::string& url, std::string& content) override;
    bool GetAssetContent(const std::string& url, std::vector<uint8_t>& content) override;
    std::string GetAssetPath(const std::string& url) override;

    // i18n
    void GetI18nData(std::unique_ptr<JsonValue>& json) override {}

    void GetResourceConfiguration(std::unique_ptr<JsonValue>& json) override {}

    void GetConfigurationCommon(const std::string& filePath, std::unique_ptr<JsonValue>& data) override {}

    int32_t GetMinPlatformVersion() override
    {
        return manifestParser_->GetMinPlatformVersion();
    }

    void LoadResourceConfiguration(std::map<std::string, std::string>& mediaResourceFileMap,
        std::unique_ptr<JsonValue>& currentResourceData) override
    {}

    void ChangeLocale(const std::string& language, const std::string& countryOrRegion) override;

    void RegisterFont(const std::string& familyName, const std::string& familySrc) override;

    void HandleImage(const std::string& src, std::function<void(bool, int32_t, int32_t)>&& callback) override {}

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

    bool OnPageBackPress();

private:
    PipelineContextHolder pipelineContextHolder_;
    RefPtr<TaskExecutor> taskExecutor_;
    RefPtr<NG::PageRouterManager> pageRouterManager_;
    RefPtr<Framework::ManifestParser> manifestParser_;
    RefPtr<MediaQueryInfo> mediaQueryInfo_;
    RefPtr<GroupJsBridge> groupJsBridge_;
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_FRONTEND_DELEGATE_DECLARATIVE_NG_H
