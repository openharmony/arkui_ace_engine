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

#include <future>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

#include "base/memory/ace_type.h"
#include "base/thread/task_executor.h"
#include "core/components/page/page_target.h"
#include "frameworks/bridge/common/manifest/manifest_parser.h"
#include "frameworks/bridge/js_frontend/js_ace_page.h"

namespace OHOS::Ace {

using LoadJsCallback = std::function<void(const std::string&, const RefPtr<Framework::JsAcePage>&, bool isMainPage)>;

enum class RouterAction {
    DEFAULT = 0,
    PUSH,
    REPLACE,
    BACK,
    CLEAR,
};

struct RouterTask {
    RouterAction action = RouterAction::PUSH;
    PageTarget target = PageTarget("");
    std::string params;
};

struct PageInfo {
    int32_t pageId = -1;
    std::string url;
    bool isRestore = false;
    bool isAlertBeforeBackPage = false;
    DialogProperties dialogProperties;
};

class PageRouterManager : public AceType {
public:
    explicit PageRouterManager(const RefPtr<TaskExecutor>& taskExecutor) : taskExecutor_(taskExecutor) {}
    ~PageRouterManager() override {}

    void RunPage(const std::string& url, const std::string& params);

    void SetManifestParser(const RefPtr<Framework::ManifestParser>& manifestParser)
    {
        manifestParser_ = manifestParser;
    }

    void SetLoadJsCallback(LoadJsCallback&& callback)
    {
        loadJs_ = std::move(callback);
    }

    // router operation
    void Push(const PageTarget& target, const std::string& params);
    void Replace(const PageTarget& target, const std::string& params);
    void BackWithTarget(const PageTarget& target, const std::string& params);
    void Clear();
    int32_t GetStackSize() const;
    void GetState(int32_t& index, std::string& name, std::string& path);
    std::string GetParams();
    RefPtr<Framework::JsAcePage> GetPage(int32_t pageId) const;
    int32_t GetRunningPageId() const;

private:
    // page id manage
    int32_t GenerateNextPageId();
    void RecyclePageId(int32_t pageId);

    // router tasks
    void AddRouterTask(const RouterTask& task);
    void ProcessRouterTask();
    void StartPush(const PageTarget& target, const std::string& params);
    void StartReplace(const PageTarget& target, const std::string& params);
    void StartBack(const PageTarget& target, const std::string& params);
    void BackCheckAlert(const PageTarget& target, const std::string& params);
    void ClearInvisiblePages();

    // page operations
    void LoadPage(
        int32_t pageId, const PageTarget& target, bool isMainPage, const std::string& params, bool isRestore = false);
    void LoadReplacePage(int32_t pageId, const PageTarget& url, const std::string& params);
    void ReplacePage(const RefPtr<Framework::JsAcePage>& page, const std::string& url);
    void PopPage();
    void PopToPage(const std::string& url);
    int32_t GetPageIdByUrl(const std::string& url, bool& isRestore);

    void OnPageReady(const RefPtr<Framework::JsAcePage>& page, bool isMainPage, bool isRestore);

    bool isRouteStackFull_ = false;
    bool isStagingPageExist_ = false;
    int32_t pageId_ = -1;
    RefPtr<TaskExecutor> taskExecutor_;
    RefPtr<Framework::ManifestParser> manifestParser_;

    LoadJsCallback loadJs_;

    std::unordered_map<int32_t, RefPtr<Framework::JsAcePage>> pageMap_;
    std::unordered_map<int32_t, std::string> pageParamMap_;
    std::atomic<uint64_t> pageIdPool_ = 0;
    std::queue<RouterTask> routerQueue_;
    std::vector<PageInfo> pageRouterStack_;
    mutable std::mutex mutex_;
    mutable std::mutex routerQueueMutex_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_PAGE_ROUTER_MANAGER_H
