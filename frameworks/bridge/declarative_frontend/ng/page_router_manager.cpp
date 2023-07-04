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

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <string>

#include "base/i18n/localization.h"
#include "base/memory/referenced.h"
#include "base/ressched/ressched_report.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/source_map.h"
#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/ng/entry_page_info.h"
#include "bridge/js_frontend/frontend_delegate.h"
#include "core/common/container.h"
#include "core/common/thread_checker.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/stage/stage_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {

constexpr int32_t MAX_ROUTER_STACK_SIZE = 32;

void ExitToDesktop()
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [] {
            auto pipeline = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            AccessibilityEvent event;
            event.type = AccessibilityEventType::PAGE_CHANGE;
            pipeline->SendEventToAccessibility(event);
            pipeline->Finish(false);
        },
        TaskExecutor::TaskType::UI);
}

} // namespace

void PageRouterManager::LoadOhmUrl(const RouterPageInfo& target)
{
    RouterPageInfo info = target;
    info.path = info.url + ".js";
    LOGD("router.Push pagePath = %{private}s", info.url.c_str());
    RouterOptScope scope(this);
    LoadPage(GenerateNextPageId(), info);
}

void PageRouterManager::RunPage(const std::string& url, const std::string& params)
{
    ACE_SCOPED_TRACE("PageRouterManager::RunPage");
    CHECK_RUN_ON(JS);
    RouterPageInfo info { url, params };
#if !defined(PREVIEW)
    if (info.url.substr(0, strlen(BUNDLE_TAG)) == BUNDLE_TAG) {
        auto container = Container::Current();
        CHECK_NULL_VOID(container);
        auto pageUrlChecker = container->GetPageUrlChecker();
        CHECK_NULL_VOID(pageUrlChecker);
        auto instanceId = container->GetInstanceId();
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        auto callback = [weak = AceType::WeakClaim(this), info, taskExecutor, instanceId]() {
            ContainerScope scope(instanceId);
            auto pageRouterManager = weak.Upgrade();
            CHECK_NULL_VOID(pageRouterManager);
            taskExecutor->PostTask(
                [pageRouterManager, info]() { pageRouterManager->LoadOhmUrl(info); }, TaskExecutor::TaskType::JS);
        };

        auto silentInstallErrorCallBack = [taskExecutor, instanceId](int32_t errorCode, const std::string& errorMsg) {
            ContainerScope scope(instanceId);
            taskExecutor->PostTask(
                [errorCode, errorMsg]() {
                    LOGE("Run page error = %{public}d, errorMsg = %{public}s", errorCode, errorMsg.c_str());
                },
                TaskExecutor::TaskType::JS);
        };

        pageUrlChecker->LoadPageUrl(url, callback, silentInstallErrorCallBack);
        return;
    }
#endif
    if (!info.url.empty()) {
        info.path = manifestParser_->GetRouter()->GetPagePath(url);
        if (info.path.empty()) {
            LOGE("[Engine Log] this uri not support in route push.");
            return;
        }
    } else {
        info.path = manifestParser_->GetRouter()->GetEntry();
        info.url = manifestParser_->GetRouter()->GetEntry("");
    }
    LOGD("router.Push pagePath = %{private}s", info.url.c_str());
    RouterOptScope scope(this);
    LoadPage(GenerateNextPageId(), info);
}

void PageRouterManager::RunCard(const std::string& url, const std::string& params, int64_t cardId)
{
    CHECK_RUN_ON(JS);
    RouterPageInfo info { url };
#ifndef PREVIEW
    if (!info.url.empty()) {
        info.path = manifestParser_->GetRouter()->GetPagePath(url);
    } else {
        info.path = manifestParser_->GetRouter()->GetEntry();
        info.url = manifestParser_->GetRouter()->GetEntry("");
    }
#endif
    LoadCard(0, info, params, cardId);
}

void PageRouterManager::Push(const RouterPageInfo& target)
{
    CHECK_RUN_ON(JS);
    if (inRouterOpt_) {
        LOGI("in router opt, post push router task");
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->PostAsyncEvent(
            [weak = WeakClaim(this), target]() {
                auto router = weak.Upgrade();
                CHECK_NULL_VOID(router);
                router->Push(target);
            },
            TaskExecutor::TaskType::JS);
        return;
    }
    RouterOptScope scope(this);
    StartPush(target);
}

void PageRouterManager::PushNamedRoute(const RouterPageInfo& target)
{
    CHECK_RUN_ON(JS);
    if (inRouterOpt_) {
        LOGI("in router opt, post push named route router task");
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->PostAsyncEvent(
            [weak = WeakClaim(this), target]() {
                auto router = weak.Upgrade();
                CHECK_NULL_VOID(router);
                router->PushNamedRoute(target);
            },
            TaskExecutor::TaskType::JS);
        return;
    }
    RouterOptScope scope(this);
    if (GetStackSize() >= MAX_ROUTER_STACK_SIZE) {
        LOGE("router stack size is larger than max size 32.");
        if (target.errorCallback != nullptr) {
            target.errorCallback("The pages are pushed too much.", Framework::ERROR_CODE_PAGE_STACK_FULL);
        }
        return;
    }
    CleanPageOverlay();
    if (target.routerMode == RouterMode::SINGLE) {
        auto pageInfo = FindPageInStack(target.url);
        if (pageInfo.second) {
            // find page in stack, move postion and update params.
            MovePageToFront(pageInfo.first, pageInfo.second, target, false);
            return;
        }
    }
    RouterPageInfo info = target;
    info.isNamedRouterMode = true;
    LoadPage(GenerateNextPageId(), info);
}

void PageRouterManager::Replace(const RouterPageInfo& target)
{
    CHECK_RUN_ON(JS);
    if (inRouterOpt_) {
        LOGI("in router opt, post replace router task");
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->PostAsyncEvent(
            [weak = WeakClaim(this), target]() {
                auto router = weak.Upgrade();
                CHECK_NULL_VOID(router);
                router->Replace(target);
            },
            TaskExecutor::TaskType::JS);
        return;
    }
    RouterOptScope scope(this);
    StartReplace(target);
}

void PageRouterManager::ReplaceNamedRoute(const RouterPageInfo& target)
{
    CHECK_RUN_ON(JS);
    if (inRouterOpt_) {
        LOGI("in router opt, post replace named route router task");
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->PostAsyncEvent(
            [weak = WeakClaim(this), target]() {
                auto router = weak.Upgrade();
                CHECK_NULL_VOID(router);
                router->ReplaceNamedRoute(target);
            },
            TaskExecutor::TaskType::JS);
        return;
    }
    RouterOptScope scope(this);
    CleanPageOverlay();
    PopPage("", false, false);
    if (target.routerMode == RouterMode::SINGLE) {
        auto pageInfo = FindPageInStack(target.url);
        if (pageInfo.second) {
            // find page in stack, move postion and update params.
            MovePageToFront(pageInfo.first, pageInfo.second, target, false);
            return;
        }
    }
    RouterPageInfo info = target;
    info.isNamedRouterMode = true;
    LoadPage(GenerateNextPageId(), info, false, false);
}

void PageRouterManager::BackWithTarget(const RouterPageInfo& target)
{
    CHECK_RUN_ON(JS);
    LOGD("router.Back path = %{private}s", target.url.c_str());
    if (inRouterOpt_) {
        LOGI("in router opt, post back router task");
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->PostAsyncEvent(
            [weak = WeakClaim(this), target]() {
                auto router = weak.Upgrade();
                CHECK_NULL_VOID(router);
                router->BackWithTarget(target);
            },
            TaskExecutor::TaskType::JS);
        return;
    }
    RouterOptScope scope(this);
    BackCheckAlert(target);
}

void PageRouterManager::Clear()
{
    CHECK_RUN_ON(JS);
    if (inRouterOpt_) {
        LOGI("in router opt, post clear router task");
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->PostAsyncEvent(
            [weak = WeakClaim(this)]() {
                auto router = weak.Upgrade();
                CHECK_NULL_VOID(router);
                router->Clear();
            },
            TaskExecutor::TaskType::JS);
        return;
    }
    RouterOptScope scope(this);
    StartClean();
}

void PageRouterManager::EnableAlertBeforeBackPage(const std::string& message, std::function<void(int32_t)>&& callback)
{
    auto currentPage = pageRouterStack_.back().Upgrade();
    CHECK_NULL_VOID(currentPage);
    auto pagePattern = currentPage->GetPattern<PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    auto pageInfo = pagePattern->GetPageInfo();
    CHECK_NULL_VOID(pageInfo);

    DialogProperties dialogProperties = {
        .content = message,
        .autoCancel = false,
        .buttons = { { .text = Localization::GetInstance()->GetEntryLetters("common.cancel"), .textColor = "" },
            { .text = Localization::GetInstance()->GetEntryLetters("common.ok"), .textColor = "" } },
        .onSuccess =
            [weak = AceType::WeakClaim(this), weakPageInfo = AceType::WeakClaim(AceType::RawPtr(pageInfo))](
                int32_t successType, int32_t successIndex) {
                LOGI("showDialog successType: %{public}d, successIndex: %{public}d", successType, successIndex);
                auto pageInfo = weakPageInfo.Upgrade();
                if (pageInfo && pageInfo->GetAlertCallback() && !successType) {
                    pageInfo->GetAlertCallback()(successIndex);
                    if (successIndex) {
                        auto router = weak.Upgrade();
                        CHECK_NULL_VOID(router);
                        router->StartBack(router->ngBackTarget_);
                    }
                }
            },
    };

    pageInfo->SetDialogProperties(dialogProperties);
    pageInfo->SetAlertCallback(std::move(callback));
}

void PageRouterManager::DisableAlertBeforeBackPage()
{
    auto currentPage = pageRouterStack_.back().Upgrade();
    CHECK_NULL_VOID(currentPage);
    auto pagePattern = currentPage->GetPattern<PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    auto pageInfo = DynamicCast<EntryPageInfo>(pagePattern->GetPageInfo());
    CHECK_NULL_VOID(pageInfo);
    pageInfo->SetAlertCallback(nullptr);
}

void PageRouterManager::StartClean()
{
    if (pageRouterStack_.size() <= 1) {
        LOGW("current page stack can not clean, %{public}d", static_cast<int32_t>(pageRouterStack_.size()));
        return;
    }
    std::list<WeakPtr<FrameNode>> temp;
    std::swap(temp, pageRouterStack_);
    pageRouterStack_.emplace_back(temp.back());
    if (!OnCleanPageStack()) {
        LOGE("fail to clean page");
        std::swap(temp, pageRouterStack_);
    }
}

bool PageRouterManager::Pop()
{
    CHECK_RUN_ON(JS);
    if (inRouterOpt_) {
        LOGE("in router opt, post Pop router task failed");
        return false;
    }
    RouterOptScope scope(this);
    return StartPop();
}

bool PageRouterManager::StartPop()
{
    CHECK_RUN_ON(JS);
    auto currentPage = pageRouterStack_.empty() ? nullptr : pageRouterStack_.back().Upgrade();
    CHECK_NULL_RETURN(currentPage, false);
    auto pagePattern = currentPage->GetPattern<PagePattern>();
    CHECK_NULL_RETURN(pagePattern, false);
    auto pageInfo = DynamicCast<EntryPageInfo>(pagePattern->GetPageInfo());
    CHECK_NULL_RETURN(pageInfo, false);
    if (pageInfo->GetAlertCallback()) {
        BackCheckAlert(RouterPageInfo());
        return true;
    }

    if (pageRouterStack_.size() <= 1) {
        if (!restorePageStack_.empty()) {
            StartRestore(RouterPageInfo());
            return true;
        }
        // the last page.
        return false;
    }

    auto topNode = pageRouterStack_.back();
    pageRouterStack_.pop_back();
    if (!OnPopPage(true, true)) {
        LOGE("fail to pop page");
        pageRouterStack_.emplace_back(topNode);
        return false;
    }
    currentPage = pageRouterStack_.empty() ? nullptr : pageRouterStack_.back().Upgrade();
    CHECK_NULL_RETURN(currentPage, false);
    pagePattern = currentPage->GetPattern<PagePattern>();
    CHECK_NULL_RETURN(pagePattern, false);
    pageInfo = DynamicCast<EntryPageInfo>(pagePattern->GetPageInfo());
    CHECK_NULL_RETURN(pageInfo, false);
    pageInfo->ReplacePageParams("");
    return true;
}

void PageRouterManager::StartRestore(const RouterPageInfo& target)
{
    RouterPageInfo info = target;
    auto tempStack = restorePageStack_;
    if (target.url.empty()) {
        info.url = tempStack.back();
        tempStack.pop_back();
    } else {
        info.url = target.url;
        while (!tempStack.empty() && tempStack.back() != info.url) {
            tempStack.pop_back();
        }
        if (tempStack.empty()) {
            LOGW("this url not find in current restore stack");
            return;
        }
        tempStack.pop_back();
    }

    restorePageStack_ = tempStack;
    PopPage("", false, false);
    StartPush(info);
}

int32_t PageRouterManager::GetStackSize() const
{
    CHECK_RUN_ON(JS);
    return static_cast<int32_t>(pageRouterStack_.size());
}

void PageRouterManager::GetState(int32_t& index, std::string& name, std::string& path)
{
    CHECK_RUN_ON(JS);
    if (pageRouterStack_.empty()) {
        LOGE("fail to get page state due to stack is null");
        return;
    }
    index = static_cast<int32_t>(pageRouterStack_.size());
    auto pageNode = pageRouterStack_.back().Upgrade();
    CHECK_NULL_VOID(pageNode);
    auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    auto pageInfo = pagePattern->GetPageInfo();
    CHECK_NULL_VOID(pageInfo);
    auto url = pageInfo->GetPageUrl();
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

std::string PageRouterManager::GetParams() const
{
    CHECK_RUN_ON(JS);
    if (pageRouterStack_.empty()) {
        LOGE("fail to get page param due to stack is null");
        return "";
    }
    auto pageNode = pageRouterStack_.back().Upgrade();
    CHECK_NULL_RETURN(pageNode, "");
    auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
    CHECK_NULL_RETURN(pagePattern, "");
    auto pageInfo = DynamicCast<EntryPageInfo>(pagePattern->GetPageInfo());
    CHECK_NULL_RETURN(pageInfo, "");
    return pageInfo->GetPageParams();
}

std::string PageRouterManager::GetCurrentPageUrl()
{
    CHECK_RUN_ON(JS);
    if (pageRouterStack_.empty()) {
        LOGW("current page stack is empty");
        return "";
    }
    auto pageNode = pageRouterStack_.back().Upgrade();
    CHECK_NULL_RETURN(pageNode, "");
    auto pagePattern = pageNode->GetPattern<PagePattern>();
    CHECK_NULL_RETURN(pagePattern, "");
    auto entryPageInfo = DynamicCast<EntryPageInfo>(pagePattern->GetPageInfo());
    CHECK_NULL_RETURN(entryPageInfo, "");
    return entryPageInfo->GetPagePath();
}

// Get the currently running JS page information in NG structure.
RefPtr<Framework::RevSourceMap> PageRouterManager::GetCurrentPageSourceMap(const RefPtr<AssetManager>& assetManager)
{
    CHECK_RUN_ON(JS);
    if (pageRouterStack_.empty()) {
        LOGW("current page stack is empty");
        return nullptr;
    }
    auto pageNode = pageRouterStack_.back().Upgrade();
    CHECK_NULL_RETURN(pageNode, nullptr);
    auto pagePattern = pageNode->GetPattern<PagePattern>();
    CHECK_NULL_RETURN(pagePattern, nullptr);
    auto entryPageInfo = DynamicCast<EntryPageInfo>(pagePattern->GetPageInfo());
    CHECK_NULL_RETURN(entryPageInfo, nullptr);
    auto pageMap = entryPageInfo->GetPageMap();
    if (pageMap) {
        return pageMap;
    }
    // initialize page map.
    std::string jsSourceMap;
    // stage mode
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    if (container->IsUseStageModel()) {
        auto pagePath = entryPageInfo->GetPagePath();
        auto moduleName = container->GetModuleName();
        auto judgePath = moduleName + "/src/main/ets/" + pagePath.substr(0, pagePath.size() - 3) + ".ets";
        if (Framework::GetAssetContentImpl(assetManager, "sourceMaps.map", jsSourceMap)) {
            auto jsonPages = JsonUtil::ParseJsonString(jsSourceMap);
            auto jsonPage = jsonPages->GetValue(judgePath)->ToString();
            auto stagePageMap = MakeRefPtr<Framework::RevSourceMap>();
            stagePageMap->Init(jsonPage);
            entryPageInfo->SetPageMap(stagePageMap);
            return stagePageMap;
        }
    } else {
        if (Framework::GetAssetContentImpl(assetManager, entryPageInfo->GetPagePath() + ".map", jsSourceMap)) {
            auto faPageMap = MakeRefPtr<Framework::RevSourceMap>();
            faPageMap->Init(jsSourceMap);
            entryPageInfo->SetPageMap(faPageMap);
            return faPageMap;
        }
    }
    LOGW("js source map load failed!");
    return nullptr;
}

std::unique_ptr<JsonValue> PageRouterManager::GetStackInfo()
{
    auto jsonRouterStack = JsonUtil::CreateArray(false);
    auto iter = pageRouterStack_.begin();
    while (iter != pageRouterStack_.end()) {
        auto pageNode = iter->Upgrade();
        CHECK_NULL_RETURN(pageNode, jsonRouterStack);
        auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
        CHECK_NULL_RETURN(pagePattern, jsonRouterStack);
        auto pageInfo = pagePattern->GetPageInfo();
        CHECK_NULL_RETURN(pageInfo, jsonRouterStack);
        auto url = pageInfo->GetPageUrl();
        auto jsonItem = JsonUtil::Create(false);
        jsonItem->Put("url", url.c_str());
        jsonRouterStack->Put(jsonItem);
        ++iter;
    }
    return jsonRouterStack;
}

std::string PageRouterManager::RestoreRouterStack(std::unique_ptr<JsonValue> stackInfo)
{
    if (!stackInfo->IsValid() || !stackInfo->IsArray()) {
        LOGW("restore contentInfo is invalid");
        return "";
    }
    int32_t stackSize = stackInfo->GetArraySize();
    if (stackSize < 1) {
        LOGW("restore stack size is invalid");
        return "";
    }

    auto container = Container::Current();
    CHECK_NULL_RETURN(container, "");
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipeline, "");
    auto context = DynamicCast<NG::PipelineContext>(pipeline);
    auto stageManager = context ? context->GetStageManager() : nullptr;
    CHECK_NULL_RETURN(stageManager, "");

    for (int32_t index = 0; index < stackSize - 1; ++index) {
        std::string url = stackInfo->GetArrayItem(index)->GetValue("url")->ToString();
        // remove 2 useless character, as "XXX" to XXX
        url = url.substr(1, url.size() - 2);
        restorePageStack_.emplace_back(url);
    }
    std::string startUrl = stackInfo->GetArrayItem(stackSize - 1)->GetValue("url")->ToString();
    // remove 2 useless character, as "XXX" to XXX
    return startUrl.substr(1, startUrl.size() - 2);
}

int32_t PageRouterManager::GenerateNextPageId()
{
    return ++pageId_;
}

std::pair<int32_t, RefPtr<FrameNode>> PageRouterManager::FindPageInStack(const std::string& url)
{
    auto iter = std::find_if(++pageRouterStack_.rbegin(), pageRouterStack_.rend(),
        [url](const WeakPtr<FrameNode>& item) {
        auto pageNode = item.Upgrade();
        CHECK_NULL_RETURN(pageNode, false);
        auto pagePattern = pageNode->GetPattern<PagePattern>();
        CHECK_NULL_RETURN(pagePattern, false);
        auto entryPageInfo = DynamicCast<EntryPageInfo>(pagePattern->GetPageInfo());
        CHECK_NULL_RETURN(entryPageInfo, false);
        return entryPageInfo->GetPageUrl() == url;
    });
    if (iter == pageRouterStack_.rend()) {
        return { -1, nullptr };
    }
    // Returns to the forward position.
    return { std::distance(iter, pageRouterStack_.rend()) - 1, iter->Upgrade() };
}

void PageRouterManager::PushOhmUrl(const RouterPageInfo& target)
{
    RouterOptScope scope(this);
    if (GetStackSize() >= MAX_ROUTER_STACK_SIZE) {
        LOGE("router stack size is larger than max size 32.");
        if (target.errorCallback != nullptr) {
            target.errorCallback("The pages are pushed too much.", Framework::ERROR_CODE_PAGE_STACK_FULL);
        }
        return;
    }
    RouterPageInfo info = target;
    info.path = info.url + ".js";
    LOGD("router.Push pagePath = %{private}s", info.path.c_str());

    if (target.routerMode == RouterMode::SINGLE) {
        auto pageInfo = FindPageInStack(info.url);
        if (pageInfo.second) {
            // find page in stack, move postion and update params.
            MovePageToFront(pageInfo.first, pageInfo.second, info, false);
            return;
        }
    }

    LoadPage(GenerateNextPageId(), info);
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pageUrlChecker = container->GetPageUrlChecker();
    CHECK_NULL_VOID(pageUrlChecker);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [pageUrlChecker, target]() { pageUrlChecker->CheckPreload(target.url); }, TaskExecutor::TaskType::BACKGROUND);
}

void PageRouterManager::StartPush(const RouterPageInfo& target)
{
    CHECK_RUN_ON(JS);
    RouterOptScope scope(this);
    if (target.url.empty()) {
        LOGE("router.Push uri is empty");
        return;
    }
#if !defined(PREVIEW)
    if (target.url.substr(0, strlen(BUNDLE_TAG)) == BUNDLE_TAG) {
        auto container = Container::Current();
        CHECK_NULL_VOID(container);
        auto pageUrlChecker = container->GetPageUrlChecker();
        CHECK_NULL_VOID(pageUrlChecker);
        auto instanceId = container->GetInstanceId();
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        auto callback = [weak = AceType::WeakClaim(this), target, taskExecutor, instanceId]() {
            ContainerScope scope(instanceId);
            auto pageRouterManager = weak.Upgrade();
            CHECK_NULL_VOID(pageRouterManager);
            taskExecutor->PostTask(
                [pageRouterManager, target]() { pageRouterManager->PushOhmUrl(target); }, TaskExecutor::TaskType::JS);
        };

        auto silentInstallErrorCallBack = [errorCallback = target.errorCallback, taskExecutor, instanceId](
                                              int32_t errorCode, const std::string& errorMsg) {
            ContainerScope scope(instanceId);
            taskExecutor->PostTask([errorCallback, errorCode, errorMsg]() { errorCallback(errorMsg, errorCode); },
                TaskExecutor::TaskType::JS);
        };

        pageUrlChecker->LoadPageUrl(target.url, callback, silentInstallErrorCallBack);
        return;
    }
#endif
    if (!manifestParser_) {
        LOGE("the router manifest parser is null.");
        return;
    }
    if (GetStackSize() >= MAX_ROUTER_STACK_SIZE) {
        LOGE("router stack size is larger than max size 32.");
        if (target.errorCallback != nullptr) {
            target.errorCallback("The pages are pushed too much.", Framework::ERROR_CODE_PAGE_STACK_FULL);
        }
        return;
    }
    RouterPageInfo info = target;
    info.path = manifestParser_->GetRouter()->GetPagePath(info.url);
    LOGD("router.Push pagePath = %{private}s", info.path.c_str());
    if (info.path.empty()) {
        LOGE("[Engine Log] this uri not support in route push.");
        if (info.errorCallback != nullptr) {
            info.errorCallback("The uri of router is not exist.", Framework::ERROR_CODE_URI_ERROR);
        }
        return;
    }

    CleanPageOverlay();

    if (info.routerMode == RouterMode::SINGLE) {
        auto pageInfo = FindPageInStack(info.url);
        if (pageInfo.second) {
            // find page in stack, move postion and update params.
            MovePageToFront(pageInfo.first, pageInfo.second, info, false);
            return;
        }
    }

    LoadPage(GenerateNextPageId(), info);
}

void PageRouterManager::ReplaceOhmUrl(const RouterPageInfo& target)
{
    RouterOptScope scope(this);
    RouterPageInfo info = target;
    info.path = info.url + ".js";
    LOGD("router.Push pagePath = %{private}s", info.path.c_str());

    PopPage("", false, false);

    if (info.routerMode == RouterMode::SINGLE) {
        auto pageInfo = FindPageInStack(info.url);
        if (pageInfo.second) {
            // find page in stack, move postion and update params.
            MovePageToFront(pageInfo.first, pageInfo.second, info, false, true, false);
            return;
        }
    }

    LoadPage(GenerateNextPageId(), info, false, false);
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pageUrlChecker = container->GetPageUrlChecker();
    CHECK_NULL_VOID(pageUrlChecker);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [pageUrlChecker, target]() { pageUrlChecker->CheckPreload(target.url); }, TaskExecutor::TaskType::BACKGROUND);
}

void PageRouterManager::StartReplace(const RouterPageInfo& target)
{
    CHECK_RUN_ON(JS);
    CleanPageOverlay();
    RouterOptScope scope(this);
    if (target.url.empty()) {
        LOGE("router.Push uri is empty");
        return;
    }
#if !defined(PREVIEW)
    if (target.url.substr(0, strlen(BUNDLE_TAG)) == BUNDLE_TAG) {
        auto container = Container::Current();
        CHECK_NULL_VOID(container);
        auto pageUrlChecker = container->GetPageUrlChecker();
        CHECK_NULL_VOID(pageUrlChecker);
        auto instanceId = container->GetInstanceId();
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        auto callback = [weak = AceType::WeakClaim(this), target, taskExecutor, instanceId]() {
            ContainerScope scope(instanceId);
            auto pageRouterManager = weak.Upgrade();
            CHECK_NULL_VOID(pageRouterManager);
            taskExecutor->PostTask([pageRouterManager, target]() { pageRouterManager->ReplaceOhmUrl(target); },
                TaskExecutor::TaskType::JS);
        };

        auto silentInstallErrorCallBack = [errorCallback = target.errorCallback, taskExecutor, instanceId](
                                              int32_t errorCode, const std::string& errorMsg) {
            ContainerScope scope(instanceId);
            taskExecutor->PostTask([errorCallback, errorCode, errorMsg]() { errorCallback(errorMsg, errorCode); },
                TaskExecutor::TaskType::JS);
        };

        pageUrlChecker->LoadPageUrl(target.url, callback, silentInstallErrorCallBack);
        return;
    }
#endif
    if (!manifestParser_) {
        LOGE("the router manifest parser is null.");
        return;
    }
    RouterPageInfo info = target;
    info.path = manifestParser_->GetRouter()->GetPagePath(info.url);
    LOGD("router.Push pagePath = %{private}s", info.path.c_str());
    if (info.path.empty()) {
        LOGE("[Engine Log] this uri not support in route push.");
        if (info.errorCallback != nullptr) {
            info.errorCallback("The uri of router is not exist.", Framework::ERROR_CODE_URI_ERROR_LITE);
        }
        return;
    }

    PopPage("", false, false);

    if (info.routerMode == RouterMode::SINGLE) {
        auto pageInfo = FindPageInStack(info.url);
        if (pageInfo.second) {
            // find page in stack, move position and update params.
            MovePageToFront(pageInfo.first, pageInfo.second, info, false, true, false);
            return;
        }
    }

    LoadPage(GenerateNextPageId(), info, false, false);
}

void PageRouterManager::StartBack(const RouterPageInfo& target)
{
    CleanPageOverlay();
    if (target.url.empty()) {
        size_t pageRouteSize = pageRouterStack_.size();
        if (pageRouteSize <= 1) {
            if (!restorePageStack_.empty()) {
                StartRestore(RouterPageInfo());
                return;
            }
            LOGI("router stack is only one, back to desktop");
            ExitToDesktop();
            return;
        }
        PopPage(target.params, true, true);
        return;
    }

    auto pageInfo = FindPageInStack(target.url);
    if (pageInfo.second) {
        // find page in stack, pop to specified index.
        RouterPageInfo info = target;
#if !defined(PREVIEW)
        if (info.url.substr(0, strlen(BUNDLE_TAG)) == BUNDLE_TAG) {
            info.path = info.url + ".js";
            LOGD("router.Push pagePath = %{private}s", info.path.c_str());
            PopPageToIndex(pageInfo.first, info.params, true, true);
            return;
        }
#endif
        if (!manifestParser_) {
            LOGE("the router manifest parser is null.");
            return;
        }

        info.path = manifestParser_->GetRouter()->GetPagePath(info.url);
        LOGD("router.Push pagePath = %{private}s", info.path.c_str());
        if (info.path.empty()) {
            LOGE("[Engine Log] this uri not support in route push.");
            return;
        }
        PopPageToIndex(pageInfo.first, info.params, true, true);
        return;
    }
    LOGW("fail to find specified page to pop");
    if (!restorePageStack_.empty()) {
        StartRestore(target);
    }
}

void PageRouterManager::BackCheckAlert(const RouterPageInfo& target)
{
    RouterOptScope scope(this);
    if (pageRouterStack_.empty()) {
        LOGI("page route stack is empty");
        return;
    }
    auto currentPage = pageRouterStack_.back().Upgrade();
    CHECK_NULL_VOID(currentPage);
    auto pagePattern = currentPage->GetPattern<PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    auto pageInfo = DynamicCast<EntryPageInfo>(pagePattern->GetPageInfo());
    CHECK_NULL_VOID(pageInfo);
    if (pageInfo->GetAlertCallback()) {
        ngBackTarget_ = target;
        auto pipelineContext = PipelineContext::GetCurrentContext();
        auto overlayManager = pipelineContext ? pipelineContext->GetOverlayManager() : nullptr;
        CHECK_NULL_VOID(overlayManager);
        overlayManager->ShowDialog(
            pageInfo->GetDialogProperties(), nullptr, AceApplicationInfo::GetInstance().IsRightToLeft());
        return;
    }
    StartBack(target);
}

void PageRouterManager::LoadPage(int32_t pageId, const RouterPageInfo& target, bool needHideLast, bool needTransition)
{
    ACE_SCOPED_TRACE("PageRouterManager::LoadPage");
    CHECK_RUN_ON(JS);
    LOGI("PageRouterManager LoadPage[%{public}d]: %{public}s.", pageId, target.url.c_str());
    auto entryPageInfo = AceType::MakeRefPtr<EntryPageInfo>(pageId, target.url, target.path, target.params);
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(entryPageInfo);
    std::unordered_map<std::string, std::string> reportData { { "pageUrl", target.url } };
    ResSchedReportScope reportScope("push_page", reportData);
    auto pageNode =
        FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), pagePattern);
    pageNode->SetHostPageId(pageId);
    pageRouterStack_.emplace_back(pageNode);
    auto result = loadJs_(target.path, target.errorCallback);
    if (pageNode->GetChildren().empty()) {
        // try to load named route
        result = loadNamedRouter_(target.url, target.isNamedRouterMode);
        if (!result && target.isNamedRouterMode && target.errorCallback) {
            target.errorCallback("The named route is not exist.", Framework::ERROR_CODE_NAMED_ROUTE_ERROR);
        }
    }
    if (target.errorCallback != nullptr) {
        target.errorCallback("", Framework::ERROR_CODE_NO_ERROR);
    }
    if (!result) {
        LOGE("fail to load page file");
        pageRouterStack_.pop_back();
        return;
    }
    if (!OnPageReady(pageNode, needHideLast, needTransition)) {
        LOGE("fail to mount page");
        pageRouterStack_.pop_back();
        return;
    }
    AccessibilityEventType type = AccessibilityEventType::CHANGE;
    pageNode->OnAccessibilityEvent(type);
    LOGI("PageRouterManager LoadPage[%{public}d]: %{public}s. success", pageId, target.url.c_str());
}

void PageRouterManager::LoadCard(int32_t pageId, const RouterPageInfo& target, const std::string& params,
    int64_t cardId, bool /*isRestore*/, bool needHideLast)
{
    CHECK_RUN_ON(JS);
    auto entryPageInfo = AceType::MakeRefPtr<EntryPageInfo>(pageId, target.url, target.path, params);
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(entryPageInfo);
    auto pageNode =
        FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), pagePattern);
    pageNode->SetHostPageId(pageId);
    pageRouterStack_.emplace_back(pageNode);

    if (!loadCard_) {
        LOGE("PageRouterManager loadCard_ is nullptr");
        return;
    }
    auto result = loadCard_(target.url, cardId);
    if (!result) {
        LOGE("fail to load page file");
        pageRouterStack_.pop_back();
        return;
    }

    if (!OnPageReady(pageNode, needHideLast, false, isCardRouter_, cardId)) {
        LOGE("fail to mount page");
        pageRouterStack_.pop_back();
        return;
    }
}

void PageRouterManager::MovePageToFront(int32_t index, const RefPtr<FrameNode>& pageNode, const RouterPageInfo& target,
    bool needHideLast, bool forceShowCurrent, bool needTransition)
{
    LOGD("MovePageToFront to index: %{public}d", index);
    if (target.errorCallback != nullptr) {
        target.errorCallback("", Framework::ERROR_CODE_NO_ERROR);
    }

    // update param first.
    CHECK_NULL_VOID(pageNode);
    auto pagePattern = pageNode->GetPattern<PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    auto pageInfo = DynamicCast<EntryPageInfo>(pagePattern->GetPageInfo());
    CHECK_NULL_VOID(pageInfo);

    if (index == static_cast<int32_t>(pageRouterStack_.size() - 1)) {
        LOGD("already on the top");
        pageInfo->ReplacePageParams(target.params);
        if (forceShowCurrent) {
            pageNode->GetRenderContext()->ResetPageTransitionEffect();
            StageManager::FirePageShow(pageNode, PageTransitionType::NONE);
        }
        return;
    }
    CHECK_NULL_VOID(pageNode);
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_VOID(pipeline);
    auto context = DynamicCast<NG::PipelineContext>(pipeline);
    auto stageManager = context ? context->GetStageManager() : nullptr;
    CHECK_NULL_VOID(stageManager);

    // clean pageNode on index position.
    auto iter = pageRouterStack_.begin();
    std::advance(iter, index);
    auto last = pageRouterStack_.erase(iter);
    // push pageNode to top.
    pageRouterStack_.emplace_back(pageNode);
    std::string tempParam;
    tempParam = pageInfo->ReplacePageParams(target.params);
    if (!stageManager->MovePageToFront(pageNode, needHideLast, needTransition)) {
        LOGE("fail to move page to front");
        // restore position and param.
        pageRouterStack_.pop_back();
        pageRouterStack_.insert(last, pageNode);
        if (!tempParam.empty()) {
            pageInfo->ReplacePageParams(tempParam);
        }
    }
}

void PageRouterManager::FlushFrontend()
{
    auto currentPage = pageRouterStack_.back().Upgrade();
    CHECK_NULL_VOID(currentPage);
    auto customNode = DynamicCast<CustomNode>(currentPage->GetFirstChild());
    CHECK_NULL_VOID(customNode);
    customNode->FlushReload();
}

void PageRouterManager::PopPage(const std::string& params, bool needShowNext, bool needTransition)
{
    CHECK_RUN_ON(JS);
    if (pageRouterStack_.empty()) {
        LOGE("page router stack size is illegal");
        return;
    }
    if (needShowNext && (pageRouterStack_.size() == 1)) {
        LOGE("page router stack size is only one, can not show next");
        return;
    }
    auto topNode = pageRouterStack_.back();
    pageRouterStack_.pop_back();
    if (!needShowNext) {
        if (!OnPopPage(needShowNext, needTransition)) {
            LOGE("fail to pop page");
            pageRouterStack_.emplace_back(topNode);
        }
        return;
    }

    // update param first.
    auto nextNode = pageRouterStack_.back().Upgrade();
    CHECK_NULL_VOID(nextNode);
    auto pagePattern = nextNode->GetPattern<PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    auto pageInfo = DynamicCast<EntryPageInfo>(pagePattern->GetPageInfo());
    CHECK_NULL_VOID(pageInfo);
    auto temp = pageInfo->ReplacePageParams(params);

    if (OnPopPage(needShowNext, needTransition)) {
        return;
    }
    LOGE("fail to pop page");
    // restore stack and pageParam.
    pageRouterStack_.emplace_back(topNode);
    pageInfo->ReplacePageParams(temp);
}

void PageRouterManager::PopPageToIndex(int32_t index, const std::string& params, bool needShowNext, bool needTransition)
{
    LOGD("PopPageToIndex to index: %{public}d", index);
    std::list<WeakPtr<FrameNode>> temp;
    std::swap(temp, pageRouterStack_);
    auto iter = temp.begin();
    for (int32_t current = 0; current <= index; ++current) {
        pageRouterStack_.emplace_back(*iter);
        ++iter;
    }

    // update param first.
    auto nextNode = pageRouterStack_.back().Upgrade();
    CHECK_NULL_VOID(nextNode);
    auto pagePattern = nextNode->GetPattern<PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    auto pageInfo = DynamicCast<EntryPageInfo>(pagePattern->GetPageInfo());
    CHECK_NULL_VOID(pageInfo);
    auto tempParam = pageInfo->ReplacePageParams(params);

    if (OnPopPageToIndex(index, needShowNext, needTransition)) {
        return;
    }
    LOGE("fail to pop page to index");
    // restore stack and pageParam.
    std::swap(temp, pageRouterStack_);
    pageInfo->ReplacePageParams(tempParam);
}

bool PageRouterManager::OnPageReady(
    const RefPtr<FrameNode>& pageNode, bool needHideLast, bool needTransition, bool isCardRouter, int64_t cardId)
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    RefPtr<PipelineBase> pipeline;
    if (isCardRouter) {
        auto weak = container->GetCardPipeline(cardId);
        pipeline = weak.Upgrade();
        CHECK_NULL_RETURN(pipeline, false);
    } else {
        pipeline = container->GetPipelineContext();
        CHECK_NULL_RETURN(pipeline, false);
    }

    auto context = DynamicCast<NG::PipelineContext>(pipeline);
    auto stageManager = context ? context->GetStageManager() : nullptr;
    if (stageManager) {
        return stageManager->PushPage(pageNode, needHideLast, needTransition);
    }
    LOGE("fail to push page due to stage manager is nullptr");
    return false;
}

bool PageRouterManager::OnPopPage(bool needShowNext, bool needTransition)
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto context = DynamicCast<NG::PipelineContext>(pipeline);
    auto stageManager = context ? context->GetStageManager() : nullptr;
    if (stageManager) {
        return stageManager->PopPage(needShowNext, needTransition);
    }
    LOGE("fail to pop page due to stage manager is nullptr");
    return false;
}

bool PageRouterManager::OnPopPageToIndex(int32_t index, bool needShowNext, bool needTransition)
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto context = DynamicCast<NG::PipelineContext>(pipeline);
    auto stageManager = context ? context->GetStageManager() : nullptr;
    if (stageManager) {
        return stageManager->PopPageToIndex(index, needShowNext, needTransition);
    }
    LOGE("fail to pop page to index due to stage manager is nullptr");
    return false;
}

bool PageRouterManager::OnCleanPageStack()
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto context = DynamicCast<NG::PipelineContext>(pipeline);
    auto stageManager = context ? context->GetStageManager() : nullptr;
    if (stageManager) {
        return stageManager->CleanPageStack();
    }
    LOGE("fail to pop page to index due to stage manager is nullptr");
    return false;
}

void PageRouterManager::CleanPageOverlay()
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_VOID(pipeline);
    auto context = DynamicCast<NG::PipelineContext>(pipeline);
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID_NOLOG(taskExecutor);
    auto sharedManager = context->GetSharedOverlayManager();
    if (sharedManager) {
        sharedManager->StopSharedTransition();
    }

    if (overlayManager->RemoveOverlay(true)) {
        LOGI("clean page overlay.");
    }
}
} // namespace OHOS::Ace::NG
