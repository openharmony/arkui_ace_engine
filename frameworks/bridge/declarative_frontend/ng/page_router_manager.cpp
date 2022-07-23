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

#include "frameworks/bridge/declarative_frontend/ng/page_router_manager.h"

#include "core/common/container.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {

namespace {

constexpr int32_t INVALID_PAGE_ID = -1;
constexpr int32_t MAX_ROUTER_STACK = 32;
constexpr int32_t MAX_PAGE_ID_SIZE = sizeof(uint64_t) * 8;

} // namespace

void PageRouterManager::RunPage(const std::string& url, const std::string& params)
{
    AddRouterTask(RouterTask { RouterAction::PUSH, PageTarget(url), params });
    LoadPage(GenerateNextPageId(), PageTarget(url), true, params);
}

void PageRouterManager::Push(const PageTarget& target, const std::string& params)
{
    {
        std::lock_guard<std::mutex> lock(routerQueueMutex_);
        if (!routerQueue_.empty()) {
            AddRouterTask(RouterTask { RouterAction::PUSH, target, params });
            return;
        }
        AddRouterTask(RouterTask { RouterAction::PUSH, target, params });
    }
    StartPush(target, params);
}

void PageRouterManager::Replace(const PageTarget& target, const std::string& params)
{
    {
        std::lock_guard<std::mutex> lock(routerQueueMutex_);
        if (!routerQueue_.empty()) {
            AddRouterTask(RouterTask { RouterAction::REPLACE, target, params });
            return;
        }
        AddRouterTask(RouterTask { RouterAction::REPLACE, target, params });
    }
    StartReplace(target, params);
}

void PageRouterManager::BackWithTarget(const PageTarget& target, const std::string& params)
{
    LOGD("router.Back path = %{private}s", target.url.c_str());
    {
        std::lock_guard<std::mutex> lock(routerQueueMutex_);
        if (!routerQueue_.empty()) {
            AddRouterTask(RouterTask { RouterAction::BACK, target, params });
            return;
        }
        AddRouterTask(RouterTask { RouterAction::BACK, target, params });
    }
    BackCheckAlert(target, params);
}

void PageRouterManager::Clear()
{
    {
        std::lock_guard<std::mutex> lock(routerQueueMutex_);
        if (!routerQueue_.empty()) {
            AddRouterTask(RouterTask { RouterAction::CLEAR });
            return;
        }
        AddRouterTask(RouterTask { RouterAction::CLEAR });
    }
    ClearInvisiblePages();
}

int32_t PageRouterManager::GetStackSize() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return static_cast<int32_t>(pageRouterStack_.size());
}

void PageRouterManager::GetState(int32_t& index, std::string& name, std::string& path)
{
    std::string url;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (pageRouterStack_.empty()) {
            return;
        }
        index = static_cast<int32_t>(pageRouterStack_.size());
        url = pageRouterStack_.back().url;
    }
    auto pos = url.rfind(".js");
    if (pos == url.length() - 3) {
        url = url.substr(0, pos);
    }
    pos = url.rfind("/");
    if (pos != std::string::npos) {
        name = url.substr(pos + 1);
        path = url.substr(0, pos + 1);
    }
}

std::string PageRouterManager::GetParams()
{
    if (pageParamMap_.find(pageId_) != pageParamMap_.end()) {
        return pageParamMap_.find(pageId_)->second;
    } else {
        return "";
    }
}

RefPtr<Framework::JsAcePage> PageRouterManager::GetPage(int32_t pageId) const
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto itPage = pageMap_.find(pageId);
    if (itPage == pageMap_.end()) {
        LOGE("the page is not in the map");
        return nullptr;
    }
    return itPage->second;
}

int32_t PageRouterManager::GetRunningPageId() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (pageRouterStack_.empty()) {
        return INVALID_PAGE_ID;
    }
    return pageRouterStack_.back().pageId;
}

int32_t PageRouterManager::GenerateNextPageId()
{
    for (int32_t idx = 0; idx < MAX_PAGE_ID_SIZE; ++idx) {
        uint64_t bitMask = (1ULL << idx);
        if ((bitMask & pageIdPool_.fetch_or(bitMask, std::memory_order_relaxed)) == 0) {
            return idx;
        }
    }
    return INVALID_PAGE_ID;
}

void PageRouterManager::RecyclePageId(int32_t pageId)
{
    if (pageId < 0 || pageId >= MAX_PAGE_ID_SIZE) {
        return;
    }
    uint64_t bitMask = (1ULL << pageId);
    pageIdPool_.fetch_and(~bitMask, std::memory_order_relaxed);
}

void PageRouterManager::ProcessRouterTask()
{
    std::lock_guard<std::mutex> lock(routerQueueMutex_);
    if (!routerQueue_.empty()) {
        routerQueue_.pop();
    }
    if (routerQueue_.empty()) {
        return;
    }
    RouterTask currentTask = routerQueue_.front();
    LOGI("ProcessRouterTask current size = %{public}zu, action = %{public}d, url = %{public}s", routerQueue_.size(),
        static_cast<uint32_t>(currentTask.action), currentTask.target.url.c_str());
    taskExecutor_->PostTask(
        [weak = AceType::WeakClaim(this), currentTask] {
            auto routerMgr = weak.Upgrade();
            if (!routerMgr) {
                return;
            }
            switch (currentTask.action) {
                case RouterAction::PUSH:
                    routerMgr->StartPush(currentTask.target, currentTask.params);
                    break;
                case RouterAction::REPLACE:
                    routerMgr->StartReplace(currentTask.target, currentTask.params);
                    break;
                case RouterAction::BACK:
                    routerMgr->BackCheckAlert(currentTask.target, currentTask.params);
                    break;
                case RouterAction::CLEAR:
                    routerMgr->ClearInvisiblePages();
                    break;
                default:
                    break;
            }
        },
        TaskExecutor::TaskType::JS);
}

void PageRouterManager::AddRouterTask(const RouterTask& task)
{
    if (routerQueue_.size() < MAX_ROUTER_STACK) {
        routerQueue_.emplace(task);
        LOGI("router queue's size = %{public}zu, action = %{public}d, url = %{public}s", routerQueue_.size(),
            static_cast<uint32_t>(task.action), task.target.url.c_str());
    } else {
        LOGW("router queue is full");
    }
}

void PageRouterManager::StartPush(const PageTarget& target, const std::string& params)
{
    if (target.url.empty()) {
        LOGE("router.Push uri is empty");
        ProcessRouterTask();
        return;
    }
    if (isRouteStackFull_) {
        LOGE("the router stack has reached its max size, you can't push any more pages.");
        ProcessRouterTask();
        return;
    }
    if (!manifestParser_) {
        LOGE("the router manifest parser is null.");
        ProcessRouterTask();
        return;
    }

    std::string pagePath = manifestParser_->GetRouter()->GetPagePath(target.url);
    LOGD("router.Push pagePath = %{private}s", pagePath.c_str());
    if (!pagePath.empty()) {
        LoadPage(GenerateNextPageId(), PageTarget(target, pagePath), false, params);
    } else {
        LOGW("[Engine Log] this uri not support in route push.");
        ProcessRouterTask();
    }
}

void PageRouterManager::StartReplace(const PageTarget& target, const std::string& params)
{
    if (target.url.empty()) {
        LOGE("router.Replace uri is empty");
        ProcessRouterTask();
        return;
    }
    if (!manifestParser_) {
        LOGE("the router manifest parser is null.");
        ProcessRouterTask();
        return;
    }

    std::string pagePath = manifestParser_->GetRouter()->GetPagePath(target.url);
    LOGD("router.Replace pagePath = %{private}s", pagePath.c_str());
    if (!pagePath.empty()) {
        LoadReplacePage(GenerateNextPageId(), PageTarget(target, pagePath), params);
    } else {
        LOGW("[Engine Log] this uri not support in route replace.");
        ProcessRouterTask();
    }
}

void PageRouterManager::StartBack(const PageTarget& target, const std::string& params)
{
    if (target.url.empty()) {
        std::string pagePath;
        {
            std::lock_guard<std::mutex> lock(mutex_);
            size_t pageRouteSize = pageRouterStack_.size();
            if (pageRouteSize > 1) {
                pageId_ = pageRouterStack_[pageRouteSize - 2].pageId;
                if (!params.empty()) {
                    pageParamMap_[pageId_] = params;
                }
                // determine whether the previous page needs to be loaded
                if (pageRouterStack_[pageRouteSize - 2].isRestore && manifestParser_) {
                    pagePath = manifestParser_->GetRouter()->GetPagePath(pageRouterStack_[pageRouteSize - 2].url);
                }
            }
        }
        if (!pagePath.empty()) {
            LOGI("restore to load page");
            LoadPage(pageId_, PageTarget(target, pagePath), false, params, true);
            return;
        }
        LOGI("run in normal back");
        PopPage();
    } else {
        std::string pagePath = manifestParser_->GetRouter()->GetPagePath(target.url);
        LOGD("router.Back pagePath = %{private}s", pagePath.c_str());
        if (!pagePath.empty()) {
            bool isRestore = false;
            pageId_ = GetPageIdByUrl(pagePath, isRestore);
            if (isRestore) {
                LoadPage(pageId_, PageTarget(target, pagePath), false, params, true);
                return;
            }
            if (!params.empty()) {
                std::lock_guard<std::mutex> lock(mutex_);
                pageParamMap_[pageId_] = params;
            }
            PopToPage(pagePath);
        } else {
            LOGW("[Engine Log] this uri not support in route Back.");
            ProcessRouterTask();
        }
    }
}

void PageRouterManager::BackCheckAlert(const PageTarget& target, const std::string& params)
{
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (pageRouterStack_.empty()) {
            LOGI("page route stack is empty");
            ProcessRouterTask();
            return;
        }
        // TODO: popup back check alert
    }
    StartBack(target, params);
}

void PageRouterManager::LoadPage(
    int32_t pageId, const PageTarget& target, bool isMainPage, const std::string& params, bool isRestore)
{
    LOGI("PageRouterManager LoadPage[%{public}d]: %{public}s.", pageId, target.url.c_str());
    if (pageId == INVALID_PAGE_ID) {
        LOGE("PageRouterManager, invalid page id");
        ProcessRouterTask();
        return;
    }
    {
        std::lock_guard<std::mutex> lock(mutex_);
        pageId_ = pageId;
        pageParamMap_[pageId] = params;
    }
    if (isStagingPageExist_) {
        LOGE("FrontendrouterMgrDeclarative, load page failed, waiting for current page loading finish.");
        RecyclePageId(pageId);
        ProcessRouterTask();
        return;
    }
    isStagingPageExist_ = true;

    auto page = AceType::MakeRefPtr<Framework::JsAcePage>(pageId, target.url);
    page->SetPageParams(params);
    page->SetFlushCallback(
        [weak = AceType::WeakClaim(this), isMainPage, isRestore](const RefPtr<Framework::JsAcePage>& acePage) {
            auto routerMgr = weak.Upgrade();
            CHECK_NULL_VOID(routerMgr);
            routerMgr->OnPageReady(acePage, isMainPage, isRestore);
        });
    taskExecutor_->PostTask(
        [page, isMainPage, weak = AceType::WeakClaim(this)] {
            auto routerMgr = weak.Upgrade();
            CHECK_NULL_VOID(routerMgr);
            routerMgr->loadJs_(page->GetUrl(), page, isMainPage);
            page->FlushCommands();
        },
        TaskExecutor::TaskType::JS);
}

void PageRouterManager::LoadReplacePage(int32_t pageId, const PageTarget& target, const std::string& params)
{
    LOGI("PageRouterManager LoadReplacePage[%{private}d]: %{private}s.", pageId, target.url.c_str());
    if (pageId == INVALID_PAGE_ID) {
        LOGW("PageRouterManager, invalid page id");
        ProcessRouterTask();
        return;
    }
    {
        std::lock_guard<std::mutex> lock(mutex_);
        pageId_ = pageId;
        pageParamMap_[pageId] = params;
    }

    auto page = AceType::MakeRefPtr<Framework::JsAcePage>(pageId, target.url);
    page->SetSubStage(target.useSubStage);
    if (isStagingPageExist_ && !page->GetSubStageFlag()) {
        LOGW("replace page failed, waiting for current page loading finish.");
        ProcessRouterTask();
        return;
    }

    isStagingPageExist_ = true;
    page->SetPageParams(params);
    taskExecutor_->PostTask(
        [page, weak = AceType::WeakClaim(this)] {
            auto routerMgr = weak.Upgrade();
            if (routerMgr) {
                routerMgr->loadJs_(page->GetUrl(), page, false);
                // TODO: process sub stage
                routerMgr->ReplacePage(page, page->GetUrl());
            }
        },
        TaskExecutor::TaskType::JS);
}

void PageRouterManager::ReplacePage(const RefPtr<Framework::JsAcePage>& page, const std::string& url)
{
    LOGE("NG verison not implemented ReplacePage");
}

void PageRouterManager::PopPage()
{
    LOGE("NG verison not implemented PopPage");
}

void PageRouterManager::PopToPage(const std::string& url)
{
    LOGE("NG verison not implemented PopToPage, url = %{private}s", url.c_str());
}

void PageRouterManager::ClearInvisiblePages()
{
    LOGE("NG verison not implemented ClearInvisiblePages");
}

int32_t PageRouterManager::GetPageIdByUrl(const std::string& url, bool& isRestore)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto pageIter = std::find_if(std::rbegin(pageRouterStack_), std::rend(pageRouterStack_),
        [&url](const PageInfo& pageRoute) { return url == pageRoute.url; });
    if (pageIter != std::rend(pageRouterStack_)) {
        LOGD("GetPageIdByUrl pageId=%{private}d url=%{private}s", pageIter->pageId, url.c_str());
        isRestore = pageIter->isRestore;
        return pageIter->pageId;
    }
    return INVALID_PAGE_ID;
}

void PageRouterManager::OnPageReady(const RefPtr<Framework::JsAcePage>& page, bool isMainPage, bool isRestore)
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_VOID(pipeline);
    LOGI("PageRouterManager OnPageReady %{private}s", page->GetUrl().c_str());
    page->SetPipelineContext(pipeline);
    auto context = DynamicCast<NG::PipelineContext>(pipeline);
    auto stageManager = context ? context->GetStageManager() : nullptr;
    if (stageManager) {
        stageManager->PushPage(page->GetRootNode());
    } else {
        LOGE("fail to push page due to stage manager is nullptr");
    }
    isStagingPageExist_ = false;
}

} // namespace OHOS::Ace
