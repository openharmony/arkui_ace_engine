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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_PAGE_ROUTER_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_PAGE_ROUTER_MANAGER_H

#include <cstdint>
#include <list>
#include <string>
#include <utility>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/thread/task_executor.h"
#include "base/utils/noncopyable.h"
#include "bridge/declarative_frontend/ng/entry_page_info.h"
#include "core/components_ng/base/frame_node.h"
#include "frameworks/bridge/common/manifest/manifest_parser.h"

namespace OHOS::Ace::NG {

using LoadPageCallback = std::function<bool(const std::string&,
    const std::function<void(const std::string&, int32_t)>&)>;
using LoadCardCallback = std::function<bool(const std::string&, int64_t cardId)>;
using LoadNamedRouterCallback = std::function<bool(const std::string&, bool isTriggeredByJs)>;

enum class RouterMode {
    STANDARD = 0,
    SINGLE,
};

struct RouterPageInfo {
    std::string url;
    std::string params;
    RouterMode routerMode = RouterMode::STANDARD;
    std::function<void(const std::string&, int32_t)> errorCallback;
    std::string path;
    bool isNamedRouterMode = false;
};

class PageRouterManager : public AceType {
    DECLARE_ACE_TYPE(PageRouterManager, AceType)
public:
    PageRouterManager() = default;
    ~PageRouterManager() override = default;

    void RunPage(const std::string& url, const std::string& params);
    void RunCard(const std::string& url, const std::string& params, int64_t cardId);

    void SetManifestParser(const RefPtr<Framework::ManifestParser>& manifestParser)
    {
        manifestParser_ = manifestParser;
    }

    void SetLoadJsCallback(LoadPageCallback&& callback)
    {
        loadJs_ = std::move(callback);
    }

    void SetLoadCardCallback(const LoadCardCallback& callback)
    {
        loadCard_ = callback;
    }

    void SetLoadNamedRouterCallback(LoadNamedRouterCallback&& callback)
    {
        loadNamedRouter_ = callback;
    }

    void EnableAlertBeforeBackPage(const std::string& message, std::function<void(int32_t)>&& callback);

    void DisableAlertBeforeBackPage();

    // router operation
    void Push(const RouterPageInfo& target);
    void PushNamedRoute(const RouterPageInfo& target);
    bool Pop();
    void Replace(const RouterPageInfo& target);
    void ReplaceNamedRoute(const RouterPageInfo& target);
    void BackWithTarget(const RouterPageInfo& target);
    void Clear();
    int32_t GetStackSize() const;

    void GetState(int32_t& index, std::string& name, std::string& path);

    std::string GetParams() const;

    RefPtr<FrameNode> GetCurrentPageNode() const
    {
        if (pageRouterStack_.empty()) {
            LOGE("fail to get current page node due to page is null");
            return nullptr;
        }
        return pageRouterStack_.back().Upgrade();
    }

    std::string GetCurrentPageUrl();

    // Get the currently running JS page information in NG structure.
    RefPtr<Framework::RevSourceMap> GetCurrentPageSourceMap(const RefPtr<AssetManager>& assetManager);

    void SetIsCard()
    {
        isCardRouter_ = true;
    }

    void FlushFrontend();

    std::unique_ptr<JsonValue> GetStackInfo();

    std::string RestoreRouterStack(std::unique_ptr<JsonValue> stackInfo);

private:
    class RouterOptScope {
    public:
        explicit RouterOptScope(PageRouterManager* manager) : manager_(manager)
        {
            manager_->inRouterOpt_ = true;
        }
        ~RouterOptScope()
        {
            manager_->inRouterOpt_ = false;
        }

    private:
        PageRouterManager* manager_ = nullptr;
    };

    // page id manage
    int32_t GenerateNextPageId();

    std::pair<int32_t, RefPtr<FrameNode>> FindPageInStack(const std::string& url);

    void LoadOhmUrl(const RouterPageInfo& target);
    void PushOhmUrl(const RouterPageInfo& target);
    void ReplaceOhmUrl(const RouterPageInfo& target);
    void StartPush(const RouterPageInfo& target);
    void StartReplace(const RouterPageInfo& target);
    void StartBack(const RouterPageInfo& target);
    bool StartPop();
    void StartRestore(const RouterPageInfo& target);
    void BackCheckAlert(const RouterPageInfo& target);
    void StartClean();
    void CleanPageOverlay();

    // page operations
    void LoadPage(int32_t pageId, const RouterPageInfo& target, bool needHideLast = true, bool needTransition = true);
    void MovePageToFront(int32_t index, const RefPtr<FrameNode>& pageNode, const RouterPageInfo& target,
        bool needHideLast, bool forceShowCurrent = false, bool needTransition = true);
    void PopPage(const std::string& params, bool needShowNext, bool needTransition);
    void PopPageToIndex(int32_t index, const std::string& params, bool needShowNext, bool needTransition);

    static bool OnPageReady(const RefPtr<FrameNode>& pageNode, bool needHideLast, bool needTransition,
        bool isCardRouter = false, int64_t cardId = 0);
    static bool OnPopPage(bool needShowNext, bool needTransition);
    static bool OnPopPageToIndex(int32_t index, bool needShowNext, bool needTransition);
    static bool OnCleanPageStack();

    void LoadCard(int32_t pageId, const RouterPageInfo& target, const std::string& params, int64_t cardId,
        bool isRestore = false, bool needHideLast = true);

    RefPtr<Framework::ManifestParser> manifestParser_;

    bool inRouterOpt_ = false;
    LoadPageCallback loadJs_;
    LoadCardCallback loadCard_;
    LoadNamedRouterCallback loadNamedRouter_;
    bool isCardRouter_ = false;
    int32_t pageId_ = 0;
    std::list<WeakPtr<FrameNode>> pageRouterStack_;
    std::list<std::string> restorePageStack_;
    RouterPageInfo ngBackTarget_;

    ACE_DISALLOW_COPY_AND_MOVE(PageRouterManager);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_PAGE_ROUTER_MANAGER_H
