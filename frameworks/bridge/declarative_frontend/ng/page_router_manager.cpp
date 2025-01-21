/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "base/i18n/localization.h"
#include "base/ressched/ressched_report.h"
#include "base/perfmonitor/perf_monitor.h"
#include "bridge/js_frontend/engine/jsi/ark_js_runtime.h"
#include "core/common/recorder/node_data_cache.h"
#include "core/common/thread_checker.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_advanced_register.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/stage/stage_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.h"

namespace OHOS::Ace::NG {

namespace {

constexpr int32_t BUNDLE_START_POS = 8;
constexpr int32_t INVALID_PAGE_INDEX = -1;
constexpr int32_t MAX_ROUTER_STACK_SIZE = 32;
constexpr int32_t JS_FILE_EXTENSION_LENGTH = 3;
constexpr char ETS_PATH[] = "/src/main/ets/";
constexpr char DEBUG_PATH[] = "entry/build/default/cache/default/default@CompileArkTS/esmodule/debug/";
constexpr char NEW_PATH[] = "entry|entry|1.0.0|src/main/ets/";
constexpr char TS_SUFFIX[] = ".ts";
constexpr char ETS_SUFFIX[] = ".ets";

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
        TaskExecutor::TaskType::UI, "ArkUIPageRouterExitToDesktop",
        TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
}

} // namespace

void PageRouterManager::LoadOhmUrl(const RouterPageInfo& target)
{
    RouterPageInfo info = target;
    info.path = info.url + ".js";
    RouterOptScope scope(this);
    LoadPage(GenerateNextPageId(), info);
}

void PageRouterManager::RunPage(const std::string& url, const std::string& params)
{
    PerfMonitor::GetPerfMonitor()->SetAppStartStatus();
    ACE_SCOPED_TRACE("PageRouterManager::RunPage");
    CHECK_RUN_ON(JS);
    RouterPageInfo info;
    info.url = url;
    info.params = params;
#if !defined(PREVIEW)
    if (info.url.substr(0, strlen(BUNDLE_TAG)) == BUNDLE_TAG) {
        info.errorCallback = [](const std::string& errorMsg, int32_t errorCode) {
            TAG_LOGE(AceLogTag::ACE_ROUTER,
                "Router load ohmUrl failed, probably caused by invalid ohmUrl. code:%{public}d, msg:%{public}s",
                errorCode, errorMsg.c_str());
        };
        auto loadTask = [weak = AceType::WeakClaim(this), info]() {
                auto pageRouterManager = weak.Upgrade();
                CHECK_NULL_VOID(pageRouterManager);
                pageRouterManager->LoadOhmUrl(info);
            };
        auto errorCallback = [](const std::string& errorMsg, int32_t errorCode) {
                TAG_LOGW(AceLogTag::ACE_ROUTER, "RunPage error code:%{public}d, msg:%{public}s",
                    errorCode, errorMsg.c_str());
            };
        LoadOhmUrlPage(info.url, std::move(loadTask), errorCallback,
            "ArkUIPageRouterLoadOhmUrl", "ArkUIPageRouterErrorLog");
        return;
    }
#endif
    if (!info.url.empty()) {
        info.path = manifestParser_->GetRouter()->GetPagePath(url);
        if (info.path.empty()) {
            return;
        }
    } else {
        info.path = manifestParser_->GetRouter()->GetEntry();
        info.url = manifestParser_->GetRouter()->GetEntry("");
    }
    RouterOptScope scope(this);
    LoadPage(GenerateNextPageId(), info);
}

void PageRouterManager::RunPage(const std::shared_ptr<std::vector<uint8_t>>& content, const std::string& params)
{
    CHECK_RUN_ON(JS);
    RouterPageInfo info;
    info.content = content;
    info.params = params;

#if !defined(PREVIEW)
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto instanceId = container->GetInstanceId();
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    ContainerScope scope(instanceId);
    auto pageRouterManager = AceType::Claim(this);
    CHECK_NULL_VOID(pageRouterManager);
    taskExecutor->PostTask(
        [pageRouterManager, info]() { pageRouterManager->LoadOhmUrl(info); },
        TaskExecutor::TaskType::JS, "ArkUIPageRouterLoadOhmUrlContent",
        TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
#endif
}

void PageRouterManager::RunPageByNamedRouter(const std::string& name, const std::string& params)
{
    auto callback = [weak = AceType::WeakClaim(this), name, params]() {
        auto pageRouterManager = weak.Upgrade();
        CHECK_NULL_VOID(pageRouterManager);
        pageRouterManager->RunPageByNamedRouterInner(name, params);
    };
    /**
     * Always check if the namedRoute page needs to be preloaded.
     * @sa PageRouterManager::RestoreRouterStack() & PageRouterManager::GetStackInfo()
     */
    if (TryPreloadNamedRouter(name, std::move(callback))) {
        return;
    }

    RunPageByNamedRouterInner(name, params);
}

void PageRouterManager::RunPageByNamedRouterInner(const std::string& name, const std::string& params)
{
    if (GetStackSize() >= MAX_ROUTER_STACK_SIZE) {
        TAG_LOGW(AceLogTag::ACE_ROUTER, "RunPageByNamedRouter exceeds maxStackSize.");
        return;
    }

    RouterPageInfo info;
    info.url = name;
    info.params = params;
    info.isNamedRouterMode = true;
    RouterOptScope scope(this);
    LoadPage(GenerateNextPageId(), info);
}

UIContentErrorCode PageRouterManager::RunCard(
    const std::string& url, const std::string& params, int64_t cardId, const std::string& entryPoint)
{
    CHECK_RUN_ON(JS);
    RouterPageInfo info;
    info.url = url;
#ifndef PREVIEW
    if (!info.url.empty()) {
        info.path = manifestParser_->GetRouter()->GetPagePath(url);
    } else {
        info.path = manifestParser_->GetRouter()->GetEntry();
        info.url = manifestParser_->GetRouter()->GetEntry("");
    }
#endif
    return LoadCard(0, info, params, cardId, false, true, entryPoint);
}

void PageRouterManager::Push(const RouterPageInfo& target)
{
    CHECK_RUN_ON(JS);
    if (inRouterOpt_) {
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->PostAsyncEvent(
            [weak = WeakClaim(this), target]() {
                auto router = weak.Upgrade();
                CHECK_NULL_VOID(router);
                router->Push(target);
            },
            "ArkUIPageRouterPush", TaskExecutor::TaskType::JS);
        return;
    }
    RouterOptScope scope(this);
    StartPush(target);
}

bool PageRouterManager::TryPreloadNamedRouter(const std::string& name, std::function<void()>&& finishCallback)
{
    /**
     * Before loading the namedRoute page, we need to check if it is necessary to preload the namedRoute
     * page code (equivalent to dynamic import in ets, eg: import('hsp'); ).
     * After preloading, pageGenerator will be filled, @sa JsiDeclarativeEngine::namedRouterRegisterMap_
     */
    if (!isNamedRouterNeedPreload_ || !isNamedRouterNeedPreload_(name)) {
        return false;
    }

    if (!preloadNamedRouter_) {
        TAG_LOGW(AceLogTag::ACE_ROUTER, "PreloadNamedRouter was not set!");
        return false;
    }

    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto instanceId = container->GetInstanceId();
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, false);
    auto preloadFinishCallback = [taskExecutor, instanceId, callback = std::move(finishCallback), name](bool success) {
        if (!success) {
            TAG_LOGW(AceLogTag::ACE_ROUTER, "failed to preload NamedRouter: %{public}s", name.c_str());
            return;
        }
        taskExecutor->PostTask(
            [instanceId, finishCallback = std::move(callback)]() {
                ContainerScope scope(instanceId);
                if (finishCallback) {
                    finishCallback();
                }
            }, TaskExecutor::TaskType::JS, "ArkUIPageRouterPreloadNamedRouterFinishCallback",
            TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
    };
    preloadNamedRouter_(name, std::move(preloadFinishCallback));
    return true;
}

void PageRouterManager::PushNamedRoute(const RouterPageInfo& target)
{
    auto callback = [weak = AceType::WeakClaim(this), target]() {
        auto pageRouterManager = weak.Upgrade();
        CHECK_NULL_VOID(pageRouterManager);
        pageRouterManager->PushNamedRouteInner(target);
    };
    /**
     * Always check if the namedRoute page needs to be preloaded.
     * @sa PageRouterManager::RestoreRouterStack() & PageRouterManager::GetStackInfo()
     */
    if (TryPreloadNamedRouter(target.url, std::move(callback))) {
        return;
    }

    PushNamedRouteInner(target);
}

void PageRouterManager::PushNamedRouteInner(const RouterPageInfo& target)
{
    CHECK_RUN_ON(JS);
    if (inRouterOpt_) {
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->PostAsyncEvent(
            [weak = WeakClaim(this), target]() {
                auto router = weak.Upgrade();
                CHECK_NULL_VOID(router);
                router->PushNamedRouteInner(target);
            },
            "ArkUIPageRouterPushNamedRoute", TaskExecutor::TaskType::JS);
        return;
    }
    RouterOptScope scope(this);
    if (GetStackSize() >= MAX_ROUTER_STACK_SIZE) {
        TAG_LOGW(AceLogTag::ACE_ROUTER, "PushNamedRoute exceeds maxStackSize.");
        if (target.errorCallback != nullptr) {
            target.errorCallback("The pages are pushed too much.", ERROR_CODE_PAGE_STACK_FULL);
        }
        return;
    }
    CleanPageOverlay();
    UpdateSrcPage();
    if (target.routerMode == RouterMode::SINGLE) {
        auto PageInfoByUrl = FindPageInStackByRouteName(target.url);
        if (PageInfoByUrl.second) {
            // find page in stack, move postion and update params.
            MovePageToFront(PageInfoByUrl.first, PageInfoByUrl.second, target, true);
            return;
        }
        auto index = FindPageInRestoreStack(target.url);
        if (index != INVALID_PAGE_INDEX) {
            // find page in restore page, create page, move position and update params.
            RestorePageWithTarget(index, false, target, RestorePageDestination::TOP);
            return;
        }
    }
    RouterPageInfo info = target;
    info.isNamedRouterMode = true;
    LoadPage(GenerateNextPageId(), info, true, true, true);
}

void PageRouterManager::Replace(const RouterPageInfo& target)
{
    CHECK_RUN_ON(JS);
    if (inRouterOpt_) {
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->PostAsyncEvent(
            [weak = WeakClaim(this), target]() {
                auto router = weak.Upgrade();
                CHECK_NULL_VOID(router);
                router->Replace(target);
            },
            "ArkUIPageRouterReplace", TaskExecutor::TaskType::JS);
        return;
    }
    RouterOptScope scope(this);
    StartReplace(target);
}

void PageRouterManager::ReplaceNamedRoute(const RouterPageInfo& target)
{
    auto callback = [weak = AceType::WeakClaim(this), target]() {
        auto pageRouterManager = weak.Upgrade();
        CHECK_NULL_VOID(pageRouterManager);
        pageRouterManager->ReplaceNamedRouteInner(target);
    };
    /**
     * Always check if the namedRoute page needs to be preloaded.
     * @sa PageRouterManager::RestoreRouterStack() & PageRouterManager::GetStackInfo()
     */
    if (TryPreloadNamedRouter(target.url, std::move(callback))) {
        return;
    }

    ReplaceNamedRouteInner(target);
}

void PageRouterManager::ReplaceNamedRouteInner(const RouterPageInfo& target)
{
    CHECK_RUN_ON(JS);
    if (inRouterOpt_) {
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->PostAsyncEvent(
            [weak = WeakClaim(this), target]() {
                auto router = weak.Upgrade();
                CHECK_NULL_VOID(router);
                router->ReplaceNamedRouteInner(target);
            },
            "ArkUIPageRouterReplaceNamedRoute", TaskExecutor::TaskType::JS);
        return;
    }
    RouterOptScope scope(this);
    CleanPageOverlay();
    UpdateSrcPage();
    RouterPageInfo info = target;
    info.isNamedRouterMode = true;
    DealReplacePage(info);
}

void PageRouterManager::BackWithTarget(const RouterPageInfo& target)
{
    CHECK_RUN_ON(JS);
    TAG_LOGI(AceLogTag::ACE_ROUTER, "Router back path:%{public}s", target.url.c_str());
    if (inRouterOpt_) {
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->PostAsyncEvent(
            [weak = WeakClaim(this), target]() {
                auto router = weak.Upgrade();
                CHECK_NULL_VOID(router);
                router->BackWithTarget(target);
            },
            "ArkUIPageRouterBackWithTarget", TaskExecutor::TaskType::JS);
        return;
    }
    RouterOptScope scope(this);
    BackCheckAlert(target);
}

void PageRouterManager::BackToIndexWithTarget(int32_t index, const std::string& params)
{
    CHECK_RUN_ON(JS);
    if (!CheckIndexValid(index)) {
        return;
    }
    if (inRouterOpt_) {
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->PostAsyncEvent(
            [weak = WeakClaim(this), index, params]() {
                auto router = weak.Upgrade();
                CHECK_NULL_VOID(router);
                router->BackToIndexWithTarget(index, params);
            },
            "ArkUIPageRouterBackToIndex", TaskExecutor::TaskType::JS);
        return;
    }
    RouterOptScope scope(this);
    BackToIndexCheckAlert(index, params);
}

void PageRouterManager::Clear()
{
    CHECK_RUN_ON(JS);
    if (inRouterOpt_) {
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->PostAsyncEvent(
            [weak = WeakClaim(this)]() {
                auto router = weak.Upgrade();
                CHECK_NULL_VOID(router);
                router->Clear();
            },
            "ArkUIPageRouterClear", TaskExecutor::TaskType::JS);
        return;
    }
    RouterOptScope scope(this);
    StartClean();
}

void PageRouterManager::EnableAlertBeforeBackPage(const std::string& message, std::function<void(int32_t)>&& callback)
{
    auto currentPage = GetCurrentPageNode();
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
    if (pageRouterStack_.empty()) {
        return;
    }
    auto currentPage = GetCurrentPageNode();
    CHECK_NULL_VOID(currentPage);
    auto pagePattern = currentPage->GetPattern<PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    auto pageInfo = DynamicCast<EntryPageInfo>(pagePattern->GetPageInfo());
    CHECK_NULL_VOID(pageInfo);
    pageInfo->SetAlertCallback(nullptr);
}

void PageRouterManager::StartClean()
{
    UpdateSrcPage();
    if (pageRouterStack_.size() > 1) {
        restorePageStack_.clear();
        std::list<WeakPtr<FrameNode>> temp;
        std::swap(temp, pageRouterStack_);
        pageRouterStack_.emplace_back(temp.back());
        if (!OnCleanPageStack()) {
            std::swap(temp, pageRouterStack_);
        } else {
            RefreshPageIndex(pageRouterStack_.begin(), 0);
        }
        return;
    }

    if (pageRouterStack_.size() == 1) {
        restorePageStack_.clear();
        return;
    }
}

bool PageRouterManager::Pop()
{
    CHECK_RUN_ON(JS);
    if (inRouterOpt_) {
        TAG_LOGI(AceLogTag::ACE_ROUTER, "router pop is in routeropt");
        return false;
    }
    RouterOptScope scope(this);
    return StartPop();
}

bool PageRouterManager::StartPop()
{
    CHECK_RUN_ON(JS);
    auto currentPage = GetCurrentPageNode();
    CHECK_NULL_RETURN(currentPage, false);
    auto pagePattern = currentPage->GetPattern<PagePattern>();
    CHECK_NULL_RETURN(pagePattern, false);
    auto pageInfo = DynamicCast<EntryPageInfo>(pagePattern->GetPageInfo());
    CHECK_NULL_RETURN(pageInfo, false);
    if (pageInfo->GetAlertCallback()) {
        TAG_LOGI(AceLogTag::ACE_ROUTER, "pop alert check start");
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
    UpdateSrcPage();
    // pop top page in page stack
    auto preWeakNode = pageRouterStack_.back();
    pageRouterStack_.pop_back();

    // clean prev top page params
    currentPage = GetCurrentPageNode();
    CHECK_NULL_RETURN(currentPage, false);
    pagePattern = currentPage->GetPattern<PagePattern>();
    CHECK_NULL_RETURN(pagePattern, false);
    pageInfo = DynamicCast<EntryPageInfo>(pagePattern->GetPageInfo());
    CHECK_NULL_RETURN(pageInfo, false);
    std::string params = pageInfo->GetPageParams();
    pageInfo->ReplacePageParams("");

    // do pop page
    if (!OnPopPage(true, true)) {
        pageRouterStack_.emplace_back(preWeakNode);
        pageInfo->ReplacePageParams(params);
        return false;
    }
    return true;
}

void PageRouterManager::StartRestore(const RouterPageInfo& target)
{
    RouterPageInfo info = target;
    auto tempStack = restorePageStack_;
    if (!target.url.empty()) {
        while (!tempStack.empty() && tempStack.back().url != info.url) {
            tempStack.pop_back();
        }
        if (tempStack.empty()) {
            return;
        }
    }
    info.url = tempStack.back().url;
    info.params = target.params;
    info.recoverable = true;
    info.isNamedRouterMode = tempStack.back().isNamedRouter;
    tempStack.pop_back();
    restorePageStack_ = tempStack;

    if (info.isNamedRouterMode) {
        if (manifestParser_) {
            if (manifestParser_->GetRouter()->GetPagePath(info.url).empty()) {
                manifestParser_->SetPagePath(info.url);
            }
        }
    }

    if (info.isNamedRouterMode) {
        auto callback = [weak = AceType::WeakClaim(this), info]() {
            auto pageRouterManager = weak.Upgrade();
            CHECK_NULL_VOID(pageRouterManager);
            pageRouterManager->RestorePageWithTargetInner(info, RestorePageDestination::BELLOW_TOP);
        };
        /**
         * Always check if the namedRoute page needs to be preloaded.
         * @sa PageRouterManager::RestoreRouterStack() & PageRouterManager::GetStackInfo()
         */
        if (TryPreloadNamedRouter(info.url, std::move(callback))) {
            return;
        }
    }

    RestorePageWithTargetInner(info, RestorePageDestination::BELLOW_TOP);
}

int32_t PageRouterManager::GetStackSize() const
{
    CHECK_RUN_ON(JS);
    auto stackSize = static_cast<int32_t>(pageRouterStack_.size() + restorePageStack_.size());
    if (isNewPageReplacing_) {
        stackSize--;
    }
    return stackSize;
}

int32_t PageRouterManager::GetCurrentPageIndex() const
{
    /**
     * In various page stack operations, pages may be inserted into different positions on the page stack,
     * and corresponding pages may also have different indexes.
     */
    CHECK_RUN_ON(JS);
    if (insertPageProcessingType_ == InsertPageProcessingType::INSERT_BELLOW_TOP) {
        // Page has been inserted into position bellow top page of pageRouterStack_.
        return static_cast<int32_t>(restorePageStack_.size() + pageRouterStack_.size()) - 1;
    } else if (insertPageProcessingType_ == InsertPageProcessingType::INSERT_BOTTOM) {
        // Page has been inserted into bottom position of pageRouterStack_.
        return static_cast<int32_t>(restorePageStack_.size()) + 1;
    } else {
        // Page has been inserted into top position of pageRouterStack_.
        auto index = static_cast<int32_t>(restorePageStack_.size() + pageRouterStack_.size());
        if (isNewPageReplacing_) {
            /**
             * example:
             *  stack bottom -> stack top
             *  [1]PageA -> [2]PageB
             *   call router.replace(PageC)
             *   then we need keep index of PageC same with PageB, that is 2
             */
            index--;
        }
        return index;
    }
}

RouterPageInfo PageRouterManager::GetPageInfoByIndex(int32_t index, const std::string& params)
{
    RouterPageInfo emptyForReturn;
    if (!CheckIndexValid(index) &&
        index != (GetStackSize() + 1) /* in case the page is on popping */) {
        return emptyForReturn;
    }

    if (index <= static_cast<int32_t>(restorePageStack_.size())) {
        auto it = restorePageStack_.begin();
        std::advance(it, index - 1);
        RouterPageInfo info;
        info.url = it->url;
        info.params = params;
        info.recoverable = true;
        info.isNamedRouterMode = it->isNamedRouter;
        return info;
    }

    auto createPageInfo = [&params](const RefPtr<NG::EntryPageInfo>& pageInfo) -> RouterPageInfo {
        RouterPageInfo info;
        info.url = pageInfo->GetPageUrl();
        info.params = params;
        info.recoverable = pageInfo->IsRecoverable();
        info.isNamedRouterMode = pageInfo->IsCreateByNamedRouter();
        return info;
    };
    if (index <= static_cast<int32_t>(restorePageStack_.size() + pageRouterStack_.size())) {
        auto it = pageRouterStack_.begin();
        std::advance(it, index - static_cast<int32_t>(restorePageStack_.size()) - 1);
        auto pageNode = it->Upgrade();
        CHECK_NULL_RETURN(pageNode, emptyForReturn);
        auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
        CHECK_NULL_RETURN(pagePattern, emptyForReturn);
        auto pageInfo = AceType::DynamicCast<NG::EntryPageInfo>(pagePattern->GetPageInfo());
        CHECK_NULL_RETURN(pageInfo, emptyForReturn);
        return createPageInfo(pageInfo);
    }

    // in case the page is on popping
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, emptyForReturn);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_RETURN(stageManager, emptyForReturn);
    auto popPage = stageManager->GetLastPage();
    CHECK_NULL_RETURN(popPage, emptyForReturn);
    auto pagePattern = popPage->GetPattern<NG::PagePattern>();
    CHECK_NULL_RETURN(pagePattern, emptyForReturn);
    auto pageInfo = AceType::DynamicCast<NG::EntryPageInfo>(pagePattern->GetPageInfo());
    // make sure the last page is the one with 'index'
    if (pageInfo && pageInfo->GetPageIndex() == index) {
        return createPageInfo(pageInfo);
    }

    return emptyForReturn;
}

void PageRouterManager::GetState(int32_t& index, std::string& name, std::string& path)
{
    CHECK_RUN_ON(JS);
    if (pageRouterStack_.empty()) {
        return;
    }
    index = static_cast<int32_t>(pageRouterStack_.size() + restorePageStack_.size());
    if (isNewPageReplacing_) {
        if (index <= 1) {
            TAG_LOGD(AceLogTag::ACE_ROUTER, "router stack size invalid while replacing");
        } else {
            index = index - 1;
        }
    }
    auto pageNode = GetCurrentPageNode();
    CHECK_NULL_VOID(pageNode);
    auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    auto pageInfo = pagePattern->GetPageInfo();
    CHECK_NULL_VOID(pageInfo);
    auto url = pageInfo->GetPageUrl();
    GetPageNameAndPath(url, name, path);
}

void PageRouterManager::GetStateByIndex(int32_t index, std::string& name, std::string& path, std::string& params)
{
    CHECK_RUN_ON(JS);
    if (!CheckIndexValid(index) &&
        index != (GetStackSize() + 1) /* in case the page is on popping */) {
        return;
    }

    if (index <= static_cast<int32_t>(restorePageStack_.size())) {
        auto it = restorePageStack_.begin();
        std::advance(it, index - 1);
        GetPageNameAndPath(it->url, name, path);
        params = it->params;
        return;
    }

    if (index <= static_cast<int32_t>(restorePageStack_.size() + pageRouterStack_.size())) {
        auto it = pageRouterStack_.begin();
        std::advance(it, index - static_cast<int32_t>(restorePageStack_.size()) - 1);
        auto pageNode = it->Upgrade();
        CHECK_NULL_VOID(pageNode);
        auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
        CHECK_NULL_VOID(pagePattern);
        auto pageInfo = AceType::DynamicCast<NG::EntryPageInfo>(pagePattern->GetPageInfo());
        CHECK_NULL_VOID(pageInfo);
        auto url = pageInfo->GetPageUrl();
        GetPageNameAndPath(url, name, path);
        params = pageInfo->GetPageParams();
        return;
    }

    // in case the page is on popping
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    auto popPage = stageManager->GetLastPage();
    CHECK_NULL_VOID(popPage);
    auto pagePattern = popPage->GetPattern<NG::PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    auto pageInfo = pagePattern->GetPageInfo();
    // make sure the last page is the one with 'index'
    if (pageInfo && pageInfo->GetPageIndex() == index) {
        auto url = pageInfo->GetPageUrl();
        GetPageNameAndPath(url, name, path);
        auto entryPageInfo = DynamicCast<NG::EntryPageInfo>(pageInfo);
        CHECK_NULL_VOID(entryPageInfo);
        params = entryPageInfo->GetPageParams();
    }
}

void PageRouterManager::GetStateByUrl(std::string& url, std::vector<Framework::StateInfo>& stateArray)
{
    CHECK_RUN_ON(JS);
    int32_t counter = 1;
    Framework::StateInfo stateInfo;
    GetPageNameAndPath(url, stateInfo.name, stateInfo.path);

    for (const auto& record : restorePageStack_) {
        if (record.url == url) {
            stateInfo.params = record.params;
            stateInfo.index = counter;
            stateArray.emplace_back(stateInfo);
        }
        counter++;
    }
    for (auto& iter : pageRouterStack_) {
        auto pageNode = iter.Upgrade();
        CHECK_NULL_VOID(pageNode);
        auto pagePattern = pageNode->GetPattern<PagePattern>();
        CHECK_NULL_VOID(pagePattern);
        auto pageInfo = DynamicCast<EntryPageInfo>(pagePattern->GetPageInfo());
        CHECK_NULL_VOID(pageInfo);
        if (pageInfo->GetPageUrl() == url) {
            stateInfo.params = pageInfo->GetPageParams();
            stateInfo.index = counter;
            stateArray.emplace_back(stateInfo);
        }
        counter++;
    }
}

void PageRouterManager::GetPageNameAndPath(const std::string& url, std::string& name, std::string& path)
{
    std::string tempUrl = url;
    auto pagePath = Framework::JsiDeclarativeEngine::GetPagePath(url);
    if (!pagePath.empty()) {
        tempUrl = pagePath;
    }
    auto pos = tempUrl.rfind(".js");
    if (pos == tempUrl.length() - JS_FILE_EXTENSION_LENGTH) {
        tempUrl = tempUrl.substr(0, pos);
    }
    pos = tempUrl.rfind("/");
    if (pos != std::string::npos) {
        name = tempUrl.substr(pos + 1);
        path = tempUrl.substr(0, pos + 1);
    }
    if (name.size() == 0) {
        name = "index";
    }
    if (path.size() == 0) {
        path = "/" + tempUrl;
    }
}

std::string PageRouterManager::GetParams() const
{
    CHECK_RUN_ON(JS);
    RefPtr<FrameNode> pageNode = nullptr;
    if (insertPageProcessingType_ == InsertPageProcessingType::INSERT_BELLOW_TOP) {
        constexpr size_t STACK_SIZE = 2;
        if (pageRouterStack_.size() < STACK_SIZE) {
            return "";
        }
        auto it = pageRouterStack_.rbegin();
        ++it;
        pageNode = it->Upgrade();
    } else if (insertPageProcessingType_ == InsertPageProcessingType::INSERT_BOTTOM) {
        if (pageRouterStack_.empty()) {
            return "";
        }
        pageNode = pageRouterStack_.front().Upgrade();
    } else {
        if (pageRouterStack_.empty()) {
            return "";
        }
        pageNode = GetCurrentPageNode();
    }

    CHECK_NULL_RETURN(pageNode, "");
    auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
    CHECK_NULL_RETURN(pagePattern, "");
    auto pageInfo = DynamicCast<EntryPageInfo>(pagePattern->GetPageInfo());
    CHECK_NULL_RETURN(pageInfo, "");
    return pageInfo->GetPageParams();
}

int32_t PageRouterManager::GetIndexByUrl(const std::string& url) const
{
    int32_t index = 0;
    for (auto iter : pageRouterStack_) {
        auto pageNode = iter.Upgrade();
        if (!pageNode) {
            continue;
        }
        auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
        auto localUrl = pagePattern->GetPageInfo()->GetPageUrl();
        if (localUrl == url) {
            return index;
        }
        ++index;
    }
    return INVALID_PAGE_INDEX;
}

std::string PageRouterManager::GetCurrentPageUrl()
{
    CHECK_RUN_ON(JS);
    if (pageRouterStack_.empty()) {
        return "";
    }
    auto pageNode = GetCurrentPageNode();
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
        return nullptr;
    }
    auto pageNode = GetCurrentPageNode();
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
        std::string judgePath = "";
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            judgePath = DEBUG_PATH + moduleName + ETS_PATH +
                        pagePath.substr(0, pagePath.size() - JS_FILE_EXTENSION_LENGTH) + TS_SUFFIX;
        } else {
            judgePath = moduleName + ETS_PATH +
                        pagePath.substr(0, pagePath.size() - JS_FILE_EXTENSION_LENGTH) + ETS_SUFFIX;
        }
        if (Framework::GetAssetContentImpl(assetManager, "sourceMaps.map", jsSourceMap)) {
            auto jsonPages = JsonUtil::ParseJsonString(jsSourceMap);
            auto child = jsonPages->GetChild();
            if (!child->GetValue("entry-package-info")->IsNull()) {
                judgePath = NEW_PATH + pagePath.substr(0, pagePath.size() - JS_FILE_EXTENSION_LENGTH) + TS_SUFFIX;
            }
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
    return nullptr;
}

std::unique_ptr<JsonValue> PageRouterManager::GetStackInfo(ContentInfoType type)
{
    auto jsonRouterStack = JsonUtil::CreateArray(true);
    auto restoreIter = restorePageStack_.begin();
    while (restoreIter != restorePageStack_.end()) {
        auto jsonItem = JsonUtil::Create(true);
        jsonItem->Put("url", restoreIter->url.c_str());
        if (type == ContentInfoType::RESOURCESCHEDULE_RECOVERY) {
            jsonItem->Put("params", restoreIter->params.c_str());
            jsonItem->Put("isNamedRoute", restoreIter->isNamedRouter);
        }
        jsonRouterStack->Put(jsonItem);
        ++restoreIter;
    }
    auto iter = pageRouterStack_.begin();
    while (iter != pageRouterStack_.end()) {
        auto pageNode = iter->Upgrade();
        CHECK_NULL_RETURN(pageNode, jsonRouterStack);
        auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
        CHECK_NULL_RETURN(pagePattern, jsonRouterStack);
        auto pageInfo = AceType::DynamicCast<EntryPageInfo>(pagePattern->GetPageInfo());
        CHECK_NULL_RETURN(pageInfo, jsonRouterStack);
        if (type == ContentInfoType::RESOURCESCHEDULE_RECOVERY && !pageInfo->IsRecoverable()) {
            ++iter;
            continue;
        }
        auto url = pageInfo->GetPageUrl();
        auto jsonItem = JsonUtil::Create(true);
        jsonItem->Put("url", url.c_str());
        if (type == ContentInfoType::RESOURCESCHEDULE_RECOVERY) {
            jsonItem->Put("params", pageInfo->GetPageParams().c_str());
            jsonItem->Put("isNamedRoute", pageInfo->IsCreateByNamedRouter());
        }
        jsonRouterStack->Put(jsonItem);
        ++iter;
    }
    return jsonRouterStack;
}

std::unique_ptr<JsonValue> PageRouterManager::GetNamedRouterInfo()
{
    if (getNamedRouterInfo_) {
        return getNamedRouterInfo_();
    }
    return nullptr;
}

std::pair<RouterRecoverRecord, UIContentErrorCode> PageRouterManager::RestoreRouterStack(
    std::unique_ptr<JsonValue> stackInfo, ContentInfoType type)
{
    if (!stackInfo->IsValid() || !stackInfo->IsArray()) {
        return std::make_pair(RouterRecoverRecord(), UIContentErrorCode::WRONG_PAGE_ROUTER);
    }
    int32_t stackSize = stackInfo->GetArraySize();
    if (stackSize < 1) {
        return std::make_pair(RouterRecoverRecord(), UIContentErrorCode::WRONG_PAGE_ROUTER);
    }

    auto container = Container::Current();
    CHECK_NULL_RETURN(container,
        std::make_pair(RouterRecoverRecord(), UIContentErrorCode::NULL_POINTER));
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipeline,
        std::make_pair(RouterRecoverRecord(), UIContentErrorCode::WRONG_PAGE_ROUTER));
    auto context = DynamicCast<NG::PipelineContext>(pipeline);
    auto stageManager = context ? context->GetStageManager() : nullptr;
    CHECK_NULL_RETURN(stageManager,
        std::make_pair(RouterRecoverRecord(), UIContentErrorCode::WRONG_PAGE_ROUTER));

    RouterRecoverRecord topRecord;
    for (int32_t index = 0; index < stackSize; ++index) {
        auto item = stackInfo->GetArrayItem(index);
        bool isNamedRoute = false;
        std::string params;
        if (type == ContentInfoType::RESOURCESCHEDULE_RECOVERY) {
            auto isNamedRouteJson = item->GetValue("isNamedRoute");
            if (isNamedRouteJson && isNamedRouteJson->IsBool()) {
                isNamedRoute = isNamedRouteJson->GetBool();
            }
            auto paramsJson = item->GetValue("params");
            if (paramsJson && paramsJson->IsString()) {
                params = paramsJson->GetString();
            }
        }

        std::string url = item->GetValue("url")->ToString();
        // remove 2 useless character, as "XXX" to XXX
        url = url.substr(1, url.size() - 2);
        if (index < stackSize - 1) {
            restorePageStack_.emplace_back(url, params, isNamedRoute);
        } else {
            topRecord = RouterRecoverRecord(url, params, isNamedRoute);
        }
    }
    return std::make_pair(topRecord, UIContentErrorCode::NO_ERRORS);
}

void PageRouterManager::RestoreNamedRouterInfo(std::unique_ptr<JsonValue> namedRouterInfo)
{
    if (restoreNamedRouterInfo_) {
        restoreNamedRouterInfo_(std::move(namedRouterInfo));
    }
}

std::unique_ptr<JsonValue> PageRouterManager::GetFullPathInfo()
{
    if (getFullPathInfo_) {
        return getFullPathInfo_();
    }
    return nullptr;
}

void PageRouterManager::RestoreFullPathInfo(std::unique_ptr<JsonValue> fullPathInfo)
{
    if (restoreFullPathInfo_) {
        restoreFullPathInfo_(std::move(fullPathInfo));
    }
}

bool PageRouterManager::IsUnrestoreByIndex(int32_t index)
{
    return index > 0 && index <= static_cast<int32_t>(restorePageStack_.size());
}

int32_t PageRouterManager::GenerateNextPageId()
{
    return ++pageId_;
}

std::pair<int32_t, RefPtr<FrameNode>> PageRouterManager::FindPageInStack(const std::string& url, bool needIgnoreBegin)
{
    auto iter = std::find_if(needIgnoreBegin ? ++pageRouterStack_.rbegin() : pageRouterStack_.rbegin(),
        pageRouterStack_.rend(), [url](const WeakPtr<FrameNode>& item) {
            auto pageNode = item.Upgrade();
            CHECK_NULL_RETURN(pageNode, false);
            auto pagePattern = pageNode->GetPattern<PagePattern>();
            CHECK_NULL_RETURN(pagePattern, false);
            auto entryPageInfo = DynamicCast<EntryPageInfo>(pagePattern->GetPageInfo());
            CHECK_NULL_RETURN(entryPageInfo, false);
            return entryPageInfo->GetPageUrl() == url;
        });
    if (iter == pageRouterStack_.rend()) {
        return { INVALID_PAGE_INDEX, nullptr };
    }
    // Returns to the forward position.
    return { std::distance(iter, pageRouterStack_.rend()) - 1, iter->Upgrade() };
}

std::pair<int32_t, RefPtr<FrameNode>> PageRouterManager::FindPageInStackByRouteName(
    const std::string& name, bool needIgnoreBegin)
{
    auto iter = std::find_if(needIgnoreBegin ? ++pageRouterStack_.rbegin() : pageRouterStack_.rbegin(),
        pageRouterStack_.rend(), [name](const WeakPtr<FrameNode>& item) {
            auto pageNode = item.Upgrade();
            CHECK_NULL_RETURN(pageNode, false);
            auto pagePattern = pageNode->GetPattern<PagePattern>();
            CHECK_NULL_RETURN(pagePattern, false);
            auto entryPageInfo = DynamicCast<EntryPageInfo>(pagePattern->GetPageInfo());
            CHECK_NULL_RETURN(entryPageInfo, false);
            return entryPageInfo->GetRouteName() == name;
        });
    if (iter == pageRouterStack_.rend()) {
        return { INVALID_PAGE_INDEX, nullptr };
    }
    // Returns to the forward position.
    return { std::distance(iter, pageRouterStack_.rend()) - 1, iter->Upgrade() };
}

int32_t PageRouterManager::FindPageInRestoreStack(const std::string& url)
{
    auto iter = std::find_if(restorePageStack_.rbegin(), restorePageStack_.rend(),
        [&url](const RouterRecoverRecord& record) {
            return record.url == url;
        });
    if (iter == restorePageStack_.rend()) {
        return INVALID_PAGE_INDEX;
    }

    return std::distance(iter, restorePageStack_.rend()) - 1;
}

void PageRouterManager::PushOhmUrl(const RouterPageInfo& target)
{
    RouterOptScope scope(this);
    if (GetStackSize() >= MAX_ROUTER_STACK_SIZE) {
        TAG_LOGW(AceLogTag::ACE_ROUTER, "PushOhmUrl exceeds maxStackSize.");
        if (target.errorCallback != nullptr) {
            target.errorCallback("The pages are pushed too much.", ERROR_CODE_PAGE_STACK_FULL);
        }
        return;
    }
    RouterPageInfo info = target;
    info.path = info.url + ".js";

    if (target.routerMode == RouterMode::SINGLE) {
        auto pageInfo = FindPageInStack(info.url);
        if (pageInfo.second) {
            // find page in stack, move postion and update params.
            MovePageToFront(pageInfo.first, pageInfo.second, info, true);
            return;
        }
        auto index = FindPageInRestoreStack(info.url);
        if (index != INVALID_PAGE_INDEX) {
            // find page in restore page, create page, move position and update params.
            RestorePageWithTarget(index, false, info, RestorePageDestination::TOP);
            return;
        }
    }

    LoadPage(GenerateNextPageId(), info, true, true, true);
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pageUrlChecker = container->GetPageUrlChecker();
    CHECK_NULL_VOID(pageUrlChecker);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask([pageUrlChecker, url = target.url]() { pageUrlChecker->CheckPreload(url); },
        TaskExecutor::TaskType::BACKGROUND, "ArkUIPageRouterPushOhmUrl",
        TaskExecutor::GetPriorityTypeWithCheck(PriorityType::HIGH));
}

void PageRouterManager::StartPush(const RouterPageInfo& target)
{
    CHECK_RUN_ON(JS);
    RouterOptScope scope(this);
    if (target.url.empty()) {
        TAG_LOGE(AceLogTag::ACE_ROUTER, "push url is empty");
        return;
    }
#if !defined(PREVIEW)
    if (target.url.substr(0, strlen(BUNDLE_TAG)) == BUNDLE_TAG) {
        auto loadTask = [weak = AceType::WeakClaim(this), target]() {
                auto pageRouterManager = weak.Upgrade();
                CHECK_NULL_VOID(pageRouterManager);
                pageRouterManager->UpdateSrcPage();
                pageRouterManager->PushOhmUrl(target);
            };
        LoadOhmUrlPage(target.url, std::move(loadTask), target.errorCallback,
            "ArkUIPageRouterPushOhmUrl", "ArkUIPageRouterPushErrorCallback");
        return;
    }
#endif
    if (!manifestParser_) {
        return;
    }
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    if (GetStackSize() >= MAX_ROUTER_STACK_SIZE && !context->GetForceSplitEnable()) {
        TAG_LOGW(AceLogTag::ACE_ROUTER, "StartPush exceeds maxStackSize.");
        if (target.errorCallback != nullptr) {
            target.errorCallback("The pages are pushed too much.", ERROR_CODE_PAGE_STACK_FULL);
        }
        return;
    }
    RouterPageInfo info = target;
    info.path = manifestParser_->GetRouter()->GetPagePath(info.url);
    if (info.path.empty()) {
        TAG_LOGW(AceLogTag::ACE_ROUTER, "empty path found in StartPush with url: %{public}s", info.url.c_str());
        if (info.errorCallback != nullptr) {
            info.errorCallback("The uri of router is not exist.", ERROR_CODE_URI_ERROR);
        }
        return;
    }

    CleanPageOverlay();
    UpdateSrcPage();

    if (info.routerMode == RouterMode::SINGLE) {
        auto pageInfo = FindPageInStack(info.url);
        if (pageInfo.second) {
            // find page in stack, move postion and update params.
            MovePageToFront(pageInfo.first, pageInfo.second, info, true);
            return;
        }
        auto index = FindPageInRestoreStack(info.url);
        if (index != INVALID_PAGE_INDEX) {
            // find page in restore page, create page, move position and update params.
            RestorePageWithTarget(index, false, info, RestorePageDestination::TOP);
            return;
        }
    }

    LoadPage(GenerateNextPageId(), info, true, true, true);
}

void PageRouterManager::ReplaceOhmUrl(const RouterPageInfo& target)
{
    RouterOptScope scope(this);
    RouterPageInfo info = target;
    info.path = info.url + ".js";

    PopPage("", false, false);

    if (info.routerMode == RouterMode::SINGLE) {
        auto pageInfo = FindPageInStack(info.url);
        if (pageInfo.second) {
            // find page in stack, move postion and update params.
            MovePageToFront(pageInfo.first, pageInfo.second, info, false, true, false);
            return;
        }
        auto index = FindPageInRestoreStack(info.url);
        if (index != INVALID_PAGE_INDEX) {
            // find page in restore page, create page, move position and update params.
            RestorePageWithTarget(index, false, info, RestorePageDestination::TOP, false);
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
    taskExecutor->PostTask([pageUrlChecker, url = target.url]() { pageUrlChecker->CheckPreload(url); },
        TaskExecutor::TaskType::BACKGROUND, "ArkUIPageRouterReplaceOhmUrl",
        TaskExecutor::GetPriorityTypeWithCheck(PriorityType::HIGH));
}

void PageRouterManager::StartReplace(const RouterPageInfo& target)
{
    CHECK_RUN_ON(JS);
    CleanPageOverlay();
    RouterOptScope scope(this);
    if (target.url.empty()) {
        return;
    }
#if !defined(PREVIEW)
    if (target.url.substr(0, strlen(BUNDLE_TAG)) == BUNDLE_TAG) {
        auto loadTask = [weak = AceType::WeakClaim(this), target]() {
                auto pageRouterManager = weak.Upgrade();
                CHECK_NULL_VOID(pageRouterManager);
                pageRouterManager->UpdateSrcPage();
                pageRouterManager->ReplaceOhmUrl(target);
            };
        LoadOhmUrlPage(target.url, std::move(loadTask), target.errorCallback,
            "ArkUIPageRouterReplaceOhmUrl", "ArkUIPageRouterReplaceErrorCallback");
        return;
    }
#endif
    if (!manifestParser_) {
        return;
    }
    RouterPageInfo info = target;
    info.path = manifestParser_->GetRouter()->GetPagePath(info.url);
    if (info.path.empty()) {
        TAG_LOGW(AceLogTag::ACE_ROUTER, "empty path found in StartReplace with url: %{public}s", info.url.c_str());
        if (info.errorCallback != nullptr) {
            info.errorCallback("The uri of router is not exist.", ERROR_CODE_URI_ERROR_LITE);
        }
        return;
    }
    UpdateSrcPage();
    DealReplacePage(info);
}

void PageRouterManager::StartBack(const RouterPageInfo& target)
{
    CleanPageOverlay();
    UpdateSrcPage();
    if (target.url.empty()) {
        size_t pageRouteSize = pageRouterStack_.size();
        if (pageRouteSize <= 1) {
            if (!restorePageStack_.empty()) {
                auto newInfo = RouterPageInfo();
                newInfo.params = target.params;
                StartRestore(newInfo);
                return;
            }
            TAG_LOGI(AceLogTag::ACE_ROUTER, "Router back start ExitToDesktop");
            ExitToDesktop();
            return;
        }
        TAG_LOGI(AceLogTag::ACE_ROUTER, "Router back start PopPage");
        PopPage(target.params, true, true);
        return;
    }

    auto pageInfo = FindPageInStack(target.url, true);
    if (pageInfo.second) {
        // find page in stack, pop to specified index.
        RouterPageInfo info = target;
#if !defined(PREVIEW)
        if (info.url.substr(0, strlen(BUNDLE_TAG)) == BUNDLE_TAG) {
            info.path = info.url + ".js";
            PopPageToIndex(pageInfo.first, info.params, true, true);
            return;
        }
#endif
        if (!manifestParser_) {
            return;
        }

        info.path = manifestParser_->GetRouter()->GetPagePath(info.url);
        if (info.path.empty()) {
            TAG_LOGW(AceLogTag::ACE_ROUTER, "empty path found in StartBack with url: %{public}s", info.url.c_str());
            return;
        }
        PopPageToIndex(pageInfo.first, info.params, true, true);
        return;
    }

    auto index = FindPageInRestoreStack(target.url);
    if (index == INVALID_PAGE_INDEX) {
        return;
    }

    RestorePageWithTarget(index, true, target, RestorePageDestination::BOTTOM);
}

void PageRouterManager::StartBackToIndex(int32_t index, const std::string& params)
{
    CleanPageOverlay();
    if (!manifestParser_) {
        return;
    }

    if (index > static_cast<int32_t>(restorePageStack_.size())) {
        PopPageToIndex(index - static_cast<int32_t>(restorePageStack_.size()) - 1, params, true, true);
        return;
    }

    RouterPageInfo info;
    info.params = params;
    RestorePageWithTarget(index - 1, true, info, RestorePageDestination::BOTTOM);
}

void PageRouterManager::BackCheckAlert(const RouterPageInfo& target)
{
    RouterOptScope scope(this);
    if (pageRouterStack_.empty()) {
        TAG_LOGW(AceLogTag::ACE_ROUTER, "Page router stack size is zero, can not back");
        return;
    }
    auto currentPage = GetCurrentPageNode();
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

void PageRouterManager::BackToIndexCheckAlert(int32_t index, const std::string& params)
{
    RouterOptScope scope(this);
    if (pageRouterStack_.empty()) {
        return;
    }
    RouterPageInfo target = GetPageInfoByIndex(index, params);
    auto currentPage = GetCurrentPageNode();
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
    UpdateSrcPage();
    StartBackToIndex(index, params);
}

void PageRouterManager::LoadPage(int32_t pageId, const RouterPageInfo& target, bool needHideLast, bool needTransition,
    bool  /*isPush*/)
{
    ACE_SCOPED_TRACE_COMMERCIAL("load page: %s(id:%d)", target.url.c_str(), pageId);
    CHECK_RUN_ON(JS);
    auto pageNode = CreatePage(pageId, target);
    if (!pageNode) {
        TAG_LOGE(AceLogTag::ACE_ROUTER, "failed to create page in LoadPage");
        return;
    }

    pageRouterStack_.emplace_back(pageNode);
    if (!OnPageReady(pageNode, needHideLast, needTransition)) {
        pageRouterStack_.pop_back();
        TAG_LOGW(AceLogTag::ACE_ROUTER, "LoadPage OnPageReady Failed");
        return;
    }
    AccessibilityEventType type = AccessibilityEventType::CHANGE;
    pageNode->OnAccessibilityEvent(type);
    TAG_LOGI(AceLogTag::ACE_ROUTER, "LoadPage Success");
}

RefPtr<FrameNode> PageRouterManager::CreatePage(int32_t pageId, const RouterPageInfo& target)
{
    ACE_SCOPED_TRACE("PageRouterManager::CreatePage");
    CHECK_RUN_ON(JS);
    TAG_LOGI(AceLogTag::ACE_ROUTER, "Page router manager is creating page[%{public}d]: url: %{public}s path: "
        "%{public}s, recoverable: %{public}s, namedRouter: %{public}s", pageId, target.url.c_str(),
        target.path.c_str(), (target.recoverable ? "yes" : "no"), (target.isNamedRouterMode ? "yes" : "no"));
    auto entryPageInfo = AceType::MakeRefPtr<EntryPageInfo>(
        pageId, target.url, target.path, target.params, target.recoverable, target.isNamedRouterMode);
    auto pagePattern = ViewAdvancedRegister::GetInstance()->CreatePagePattern(entryPageInfo);
    std::unordered_map<std::string, std::string> reportData { { "pageUrl", target.url } };
    ResSchedReportScope reportScope("push_page", reportData);
    auto pageNode =
        FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), pagePattern);
    pageNode->SetHostPageId(pageId);
    // !!! must push_back first for UpdateRootComponent
    pageRouterStack_.emplace_back(pageNode);

    if (target.content && !target.content->empty()) {
        loadJsByBuffer_(target.content, target.errorCallback, target.params);
    } else {
        loadJs_(target.path, target.errorCallback);
    }
    // record full path info of every pageNode
    auto pageInfo = pagePattern->GetPageInfo();
    if (!pageInfo) {
        pageRouterStack_.pop_back();
        return nullptr;
    }
    auto keyInfo = target.url;
    if (keyInfo.empty() && manifestParser_) {
        auto router = manifestParser_->GetRouter();
        if (router) {
            keyInfo = router->GetEntry("");
        }
    }
#if !defined(PREVIEW)
    if (keyInfo.substr(0, strlen(BUNDLE_TAG)) == BUNDLE_TAG) {
        // deal with @bundle url
        // @bundle format: @bundle:bundleName/moduleName/pagePath/fileName(without file extension)
        // @bundle example: @bundle:com.example.applicationHsp/hsp/ets/pages/Index
        // only moduleName and lastPagePath/fileName is needed: hsppages/Index
        size_t bundleEndPos = keyInfo.find('/');
        size_t moduleStartPos = bundleEndPos + 1;
        size_t moduleEndPos = keyInfo.find('/', moduleStartPos);
        std::string moduleName = keyInfo.substr(moduleStartPos, moduleEndPos - moduleStartPos);
        size_t fileNameStartPos = keyInfo.rfind('/');
        size_t pageInfoStartPos = keyInfo.rfind('/', fileNameStartPos - 1);
        keyInfo = keyInfo.substr(pageInfoStartPos + 1);
        keyInfo = moduleName + keyInfo;
    }
#endif
    SetPageInfoRouteName(entryPageInfo);
    auto pagePath = Framework::JsiDeclarativeEngine::GetFullPathInfo(keyInfo);
    if (pagePath.empty()) {
        auto container = Container::Current();
        if (!container) {
            pageRouterStack_.pop_back();
            return nullptr;
        }
        auto moduleName = container->GetModuleName();
        keyInfo = moduleName + keyInfo;
        pagePath = Framework::JsiDeclarativeEngine::GetFullPathInfo(keyInfo);
    }
    pageInfo->SetFullPath(pagePath);

#if defined(PREVIEW)
    if (!isComponentPreview_()) {
#endif
    auto result = loadNamedRouter_(target.url, target.isNamedRouterMode);
    if (!result) {
        if (!target.isNamedRouterMode) {
            result = updateRootComponent_();
        } else if (target.errorCallback) {
            target.errorCallback("The named route is not exist.", ERROR_CODE_NAMED_ROUTE_ERROR);
        }
    }

    if (!result) {
        TAG_LOGE(AceLogTag::ACE_ROUTER, "Update RootComponent Failed or LoadNamedRouter Failed");
#if !defined(PREVIEW)
        if (!target.isNamedRouterMode && target.url.substr(0, strlen(BUNDLE_TAG)) != BUNDLE_TAG) {
            ThrowError("Load Page Failed: " + target.url, ERROR_CODE_LOAD_PAGE_ERROR);
        }
#endif
        pageRouterStack_.pop_back();
        return nullptr;
    }

    if (target.isNamedRouterMode) {
        if (manifestParser_) {
            manifestParser_->SetPagePath(target.url);
        } else {
            TAG_LOGE(AceLogTag::ACE_ROUTER, "set routeName in manifest failed, manifestParser is null!");
        }
    }

    if (target.errorCallback != nullptr) {
        target.errorCallback("", ERROR_CODE_NO_ERROR);
    }
#if defined(PREVIEW)
    }
#endif

    pageRouterStack_.pop_back();
    return pageNode;
}

UIContentErrorCode PageRouterManager::LoadCard(int32_t pageId, const RouterPageInfo& target, const std::string& params,
    int64_t cardId, bool /* isRestore */, bool needHideLast, const std::string& entryPoint)
{
    CHECK_RUN_ON(JS);
    auto entryPageInfo = AceType::MakeRefPtr<EntryPageInfo>(pageId, target.url, target.path, params);
    auto pagePattern = ViewAdvancedRegister::GetInstance()->CreatePagePattern(entryPageInfo);
    auto pageNode =
        FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), pagePattern);
    pageNode->SetHostPageId(pageId);
    pageRouterStack_.emplace_back(pageNode);

    if (!loadCard_) {
        return UIContentErrorCode::NULL_CARD_CALLBACK;
    }
    auto result = loadCard_(target.url, cardId, entryPoint);
    if (!result) {
        pageRouterStack_.pop_back();
        return UIContentErrorCode::NULL_CARD_RES;
    }

    if (!OnPageReady(pageNode, needHideLast, false, isCardRouter_, cardId)) {
        TAG_LOGE(AceLogTag::ACE_ROUTER, "LoadCard OnPageReady Failed");
        pageRouterStack_.pop_back();
        return UIContentErrorCode::CARD_PAGE_NOT_READY;
    }
    TAG_LOGI(AceLogTag::ACE_ROUTER, "LoadCard Success");
    return UIContentErrorCode::NO_ERRORS;
}

void PageRouterManager::MovePageToFront(int32_t index, const RefPtr<FrameNode>& pageNode, const RouterPageInfo& target,
    bool needHideLast, bool forceShowCurrent, bool needTransition)
{
    TAG_LOGI(AceLogTag::ACE_ROUTER, "Move page to front to index: %{public}d", index);
    if (target.errorCallback != nullptr) {
        target.errorCallback("", ERROR_CODE_NO_ERROR);
    }

    // update param first.
    CHECK_NULL_VOID(pageNode);
    auto pagePattern = pageNode->GetPattern<PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    auto pageInfo = DynamicCast<EntryPageInfo>(pagePattern->GetPageInfo());
    CHECK_NULL_VOID(pageInfo);

    if (index == static_cast<int32_t>(pageRouterStack_.size()) - 1) {
        pageInfo->ReplacePageParams(target.params);
        pageInfo->ReplaceRecoverable(target.recoverable);
        if (forceShowCurrent) {
            pagePattern->ResetPageTransitionEffect();
            StageManager::FirePageShow(pageNode, PageTransitionType::NONE);
        }
        return;
    }

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
    std::string tempParam = pageInfo->ReplacePageParams(target.params);
    bool tempRecoverable = pageInfo->ReplaceRecoverable(target.recoverable);
    if (!stageManager->MovePageToFront(pageNode, needHideLast, needTransition)) {
        // restore position and param.
        pageRouterStack_.pop_back();
        pageRouterStack_.insert(last, pageNode);
        if (!tempParam.empty()) {
            pageInfo->ReplacePageParams(tempParam);
        }
        pageInfo->ReplaceRecoverable(tempRecoverable);
    }

    // update index in pageInfo
    int32_t restorePageNumber = static_cast<int32_t>(restorePageStack_.size());
    RefreshPageIndex(last, index + restorePageNumber);
}

void PageRouterManager::RefreshPageIndex(std::list<WeakPtr<FrameNode>>::iterator startIter, int32_t startIndex)
{
    for (; startIter != pageRouterStack_.end(); ++startIter, ++startIndex) {
        auto pageNode = startIter->Upgrade();
        if (!pageNode) {
            continue;
        }
        auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
        if (pagePattern) {
            pagePattern->GetPageInfo()->SetPageIndex(startIndex + 1);
        }
    }
}

void PageRouterManager::RefreshAllPageIndex()
{
    int32_t restorePageNumber = static_cast<int32_t>(restorePageStack_.size());
    RefreshPageIndex(pageRouterStack_.begin(), restorePageNumber);
}

void PageRouterManager::RestorePageWithTarget(int32_t index, bool removeRestorePages,
    const RouterPageInfo& target, RestorePageDestination dest, bool needTransition)
{
    TAG_LOGI(AceLogTag::ACE_ROUTER, "restore page with target, index: %{public}d, removeRestorePages: %{public}s, "
        "target.url: %{public}s, dest: %{public}d", index, removeRestorePages ? "yes" : "no", target.url.c_str(), dest);
    RouterPageInfo info = target;
    auto iter = restorePageStack_.begin();
    std::advance(iter, index);
    info.url = iter->url;
    info.isNamedRouterMode = iter->isNamedRouter;
    info.recoverable = true;
    if (!info.errorCallback) {
        info.errorCallback = [](const std::string& errorMsg, int32_t errorCode) {
            TAG_LOGE(AceLogTag::ACE_ROUTER, "restore page with target error: %{public}d, msg: %{public}s",
                errorCode, errorMsg.c_str());
        };
    }
    if (removeRestorePages) {
        restorePageStack_.erase(iter, restorePageStack_.end());
    } else {
        restorePageStack_.erase(iter);
    }

    if (info.isNamedRouterMode) {
        if (manifestParser_) {
            if (manifestParser_->GetRouter()->GetPagePath(info.url).empty()) {
                manifestParser_->SetPagePath(info.url);
            }
        }
    }

    if (info.isNamedRouterMode) {
        auto callback = [weak = AceType::WeakClaim(this), info, dest, needTransition]() {
            auto pageRouterManager = weak.Upgrade();
            CHECK_NULL_VOID(pageRouterManager);
            pageRouterManager->RestorePageWithTargetInner(info, dest, needTransition);
        };
        /**
         * Always check if the namedRoute page needs to be preloaded.
         * @sa PageRouterManager::RestoreRouterStack() & PageRouterManager::GetStackInfo()
         */
        if (TryPreloadNamedRouter(info.url, std::move(callback))) {
            return;
        }
    }

    RestorePageWithTargetInner(info, dest, needTransition);
}

void PageRouterManager::RestorePageWithTargetInner(
    const RouterPageInfo& target, RestorePageDestination dest, bool needTransition)
{
    /**
     * use 'A' to represent pages in restorePageStack_, use 'B' to represent pages in pageRouterStack_
     *
     * Case1(RestorePageDestination::TOP), eg: router.pushUrl(options, RouterMode.SINGLE)
     *  +---+---+---+---+---+        +---+---+---+
     *  | A | A | A | A | A |        | B | B |   |
     *  +---+---+---+---+---+        +---+---+ ^ +
     *            |                            |
     *            +----------------------------+
     *
     * Case2(RestorePageDestination::BELLOW_TOP), eg:
     *  router.back()
     *  +---+---+---+---+---+    +---+---+
     *  | A | A | A | A | A |    |   | B |
     *  +---+---+---+---+---+    + ^ +---+
     *                    |        |
     *                    +--------+
     *
     *  router.replacePath({url: 'page/Index'}, RouterMode.SINGLE) (newLifeCycle)
     *  +---+---+---+---+---+        +---+---+
     *  | A | A | A | A | A |        | B | B |
     *  +---+---+---+---+---+        +---+---+
     *            |                      ^
     *            |                      |
     *            +----------------------+
     *
     * Case3(RestorePageDestination::BOTTOM), eg: router.back(3), router.back({url: 'page/Index'})
     *  +---+---+---+---+---+    +---+---+---+
     *  | A | A | A | A | A |    |   | B | B |
     *  +---+---+---+---+---+    + ^ +---+---+
     *            |                |
     *            +----------------+
     *
     * Router page restore steps:
     * 1. create page
     * 2. insert page
     * 3. pop page (optional)
     * 4. refresh all page's index (optional)
     */
    std::function<void()> callback = nullptr;
    // step3 & step4 pop page, refresh all page's index
    if (dest == RestorePageDestination::TOP) {
        callback = [weak = WeakClaim(this)] {
            auto mgr = weak.Upgrade();
            CHECK_NULL_VOID(mgr);
            mgr->RefreshAllPageIndex();
        };
    } else if (dest == RestorePageDestination::BELLOW_TOP) {
        callback = [weak = WeakClaim(this), needTransition] {
            auto mgr = weak.Upgrade();
            CHECK_NULL_VOID(mgr);
            mgr->PopPage("", true, needTransition, false);
        };
    } else if (dest == RestorePageDestination::BOTTOM) {
        callback = [weak = WeakClaim(this), params = target.params] {
            auto mgr = weak.Upgrade();
            CHECK_NULL_VOID(mgr);
            mgr->PopPageToIndex(0, params, true, true);
            mgr->RefreshAllPageIndex();
        };
    }

    StartRestorePageWithTarget(target, std::move(callback), dest, needTransition);
}

void PageRouterManager::StartRestorePageWithTarget(const RouterPageInfo& target,
    std::function<void()>&& finishCallback, RestorePageDestination dest, bool needTransition)
{
    if (target.url.empty()) {
        return;
    }

    CHECK_RUN_ON(JS);
    if (inRouterOpt_) {
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->PostAsyncEvent(
            [weak = WeakClaim(this), target, callback = std::move(finishCallback), dest, needTransition]() mutable {
                auto router = weak.Upgrade();
                CHECK_NULL_VOID(router);
                router->StartRestorePageWithTarget(target, std::move(callback), dest, needTransition);
            }, "ArkUIPageRouterRestorePageWithTarget", TaskExecutor::TaskType::JS);
        return;
    }

    RouterOptScope scope(this);
    RefPtr<FrameNode> pageNode = nullptr;
    // step1: create page
    if (target.isNamedRouterMode) {
        CleanPageOverlay();
        pageNode = CreatePage(GenerateNextPageId(), target);
    } else {
#if !defined(PREVIEW)
        if (target.url.substr(0, strlen(BUNDLE_TAG)) == BUNDLE_TAG) {
            auto restoreTask = [weak = AceType::WeakClaim(this), target, finishCb = std::move(finishCallback),
                dest, needTransition]() mutable {
                    auto pageRouterManager = weak.Upgrade();
                    CHECK_NULL_VOID(pageRouterManager);
                    pageRouterManager->RestoreOhmUrl(target, std::move(finishCb), dest, needTransition);
                };
            LoadOhmUrlPage(target.url, std::move(restoreTask), target.errorCallback,
                "ArkUIPageRouterRestoreOhmUrl", "ArkUIPageRouterRestoreErrorCallback");
            return;
        }
#endif
        if (!manifestParser_) {
            return;
        }

        RouterPageInfo info = target;
        info.path = manifestParser_->GetRouter()->GetPagePath(info.url);
        if (info.path.empty()) {
            TAG_LOGW(AceLogTag::ACE_ROUTER,
                "empty path found in StartRestorePageWithTarget with url: %{public}s", info.url.c_str());
            if (info.errorCallback != nullptr) {
                info.errorCallback("The uri of router is not exist.", ERROR_CODE_URI_ERROR);
            }
            return;
        }

        CleanPageOverlay();
        pageNode = CreatePage(GenerateNextPageId(), info);
    }
    if (!pageNode) {
        return;
    }

    // step2: insert page
    if (dest == RestorePageDestination::TOP) {
        PushPageToTop(pageNode, std::move(finishCallback), needTransition);
    } else if (dest == RestorePageDestination::BELLOW_TOP) {
        InsertPageBellowTop(pageNode, std::move(finishCallback));
    } else if (dest == RestorePageDestination::BOTTOM) {
        InsertPageToBottom(pageNode, std::move(finishCallback));
    }
}

void PageRouterManager::FlushFrontend()
{
    auto currentPage = GetCurrentPageNode();
    CHECK_NULL_VOID(currentPage);
    auto customNode = DynamicCast<CustomNode>(currentPage->GetFirstChild());
    CHECK_NULL_VOID(customNode);
    customNode->FlushReload();
}

void PageRouterManager::PopPage(
    const std::string& params, bool needShowNext, bool needTransition, bool needReplaceParams)
{
    CHECK_RUN_ON(JS);
    if (pageRouterStack_.empty()) {
        TAG_LOGW(AceLogTag::ACE_ROUTER, "Page router stack size is zero, can not pop");
        return;
    }
    if (needShowNext && (pageRouterStack_.size() == 1)) {
        TAG_LOGW(AceLogTag::ACE_ROUTER, "Page router stack size is only one, can not show next");
        return;
    }
    auto topNode = pageRouterStack_.back();
    pageRouterStack_.pop_back();
    if (!needShowNext) {
        if (!OnPopPage(needShowNext, needTransition)) {
            pageRouterStack_.emplace_back(topNode);
        }
        return;
    }

    // update param first.
    auto nextNode = GetCurrentPageNode();
    CHECK_NULL_VOID(nextNode);
    auto pagePattern = nextNode->GetPattern<PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    auto pageInfo = DynamicCast<EntryPageInfo>(pagePattern->GetPageInfo());
    CHECK_NULL_VOID(pageInfo);
    std::string oldParams;
    if (needReplaceParams) {
        oldParams = pageInfo->ReplacePageParams(params);
    }

    if (OnPopPage(needShowNext, needTransition)) {
        return;
    }
    // restore stack and pageParam.
    pageRouterStack_.emplace_back(topNode);
    if (needReplaceParams) {
        pageInfo->ReplacePageParams(oldParams);
    }
}

void PageRouterManager::PopPageToIndex(int32_t index, const std::string& params, bool needShowNext, bool needTransition)
{
    TAG_LOGI(AceLogTag::ACE_ROUTER, "pop page to %{public}d", index);
    std::list<WeakPtr<FrameNode>> temp;
    std::swap(temp, pageRouterStack_);
    auto iter = temp.begin();
    for (int32_t current = 0; current <= index; ++current) {
        pageRouterStack_.emplace_back(*iter);
        ++iter;
    }

    // update param first.
    auto nextNode = GetCurrentPageNode();
    CHECK_NULL_VOID(nextNode);
    auto pagePattern = nextNode->GetPattern<PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    auto pageInfo = DynamicCast<EntryPageInfo>(pagePattern->GetPageInfo());
    CHECK_NULL_VOID(pageInfo);
    auto tempParam = pageInfo->ReplacePageParams(params);
    if (OnPopPageToIndex(index, needShowNext, needTransition)) {
        return;
    }

    // restore stack and pageParam.
    std::swap(temp, pageRouterStack_);
    pageInfo->ReplacePageParams(tempParam);
}

bool PageRouterManager::OnPageReady(const RefPtr<FrameNode>& pageNode, bool needHideLast, bool needTransition,
    bool isCardRouter, int64_t cardId)
{
    Recorder::NodeDataCache::Get().OnPageReady();
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
        Recorder::NodeDataCache::Get().OnBeforePagePop();
        return stageManager->PopPage(GetCurrentPageNode(), needShowNext, needTransition);
    }
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
        Recorder::NodeDataCache::Get().OnBeforePagePop();
        return stageManager->PopPageToIndex(index, needShowNext, needTransition);
    }
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
    CHECK_NULL_VOID(taskExecutor);
    auto sharedManager = context->GetSharedOverlayManager();
    if (sharedManager) {
        sharedManager->StopSharedTransition();
    }

    overlayManager->RemoveOverlay(true, true);
}

void PageRouterManager::DealReplacePage(const RouterPageInfo& info)
{
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        ReplacePageInNewLifecycle(info);
        return;
    }
    TAG_LOGI(AceLogTag::ACE_ROUTER,
        "router replace in old lifecycle(API version < 12), replace mode: %{public}d, url: %{public}s",
        static_cast<int32_t>(info.routerMode), info.url.c_str());
    PopPage("", false, false);
    if (info.routerMode == RouterMode::SINGLE) {
        auto pageInfo = FindPageInStack(info.url);
        if (pageInfo.second) {
            // find page in stack, move position and update params.
            MovePageToFront(pageInfo.first, pageInfo.second, info, false, true, false);
            return;
        }
        auto index = FindPageInRestoreStack(info.url);
        if (index != INVALID_PAGE_INDEX) {
            // find page in restore page, create page, move position and update params.
            RestorePageWithTarget(index, false, info, RestorePageDestination::TOP, false);
            return;
        }
    }
    LoadPage(GenerateNextPageId(), info, false, false);
}

bool PageRouterManager::CheckIndexValid(int32_t index) const
{
    if (index > GetStackSize() || index <= 0) {
        TAG_LOGW(AceLogTag::ACE_ROUTER,
            "The index is less than or equal to zero or exceeds the maximum length of the page stack");
        return false;
    }
    return true;
}

bool PageRouterManager::CheckOhmUrlValid(const std::string& ohmUrl)
{
    size_t bundleEndPos = ohmUrl.find('/');
    std::string bundleName = ohmUrl.substr(BUNDLE_START_POS, bundleEndPos - BUNDLE_START_POS);
    size_t moduleStartPos = bundleEndPos + 1;
    size_t moduleEndPos = ohmUrl.find('/', moduleStartPos);
    std::string moduleName = ohmUrl.substr(moduleStartPos, moduleEndPos - moduleStartPos);
    auto runtime = std::static_pointer_cast<Framework::ArkJSRuntime>(
        Framework::JsiDeclarativeEngineInstance::GetCurrentRuntime());
    return runtime->IsExecuteModuleInAbcFile(bundleName, moduleName, ohmUrl);
}

void PageRouterManager::ThrowError(const std::string& msg, int32_t code)
{
    auto runtime = std::static_pointer_cast<Framework::ArkJSRuntime>(
        Framework::JsiDeclarativeEngineInstance::GetCurrentRuntime());
    runtime->ThrowError(msg, code);
}

int32_t PageRouterManager::GetPageIndex(const WeakPtr<FrameNode>& page)
{
    auto pageNode = page.Upgrade();
    CHECK_NULL_RETURN(pageNode, INVALID_PAGE_INDEX);
    auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
    CHECK_NULL_RETURN(pagePattern, INVALID_PAGE_INDEX);
    auto ret = pagePattern->GetPageInfo()->GetPageIndex();
    // frontend index counts from 1, so need -1 for backend use
    return ret == INVALID_PAGE_INDEX ? INVALID_PAGE_INDEX : ret - 1;
}

void PageRouterManager::ReplacePageInNewLifecycle(const RouterPageInfo& info)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    TAG_LOGI(AceLogTag::ACE_ROUTER,
        "router replace in new lifecycle(API version > 11), replace mode: %{public}d, url: %{public}s",
        static_cast<int32_t>(info.routerMode), info.url.c_str());
    auto popNode = GetCurrentPageNode();
    int32_t popIndex = static_cast<int32_t>(pageRouterStack_.size()) - 1;
    bool findPage = false;
    if (info.routerMode == RouterMode::SINGLE) {
        auto pageInfo = FindPageInStack(info.url);
        // haven't find page by named route's name. Try again with its page path.
        if (pageInfo.second == nullptr && info.isNamedRouterMode) {
            std::string pagePath = Framework::JsiDeclarativeEngine::GetPagePath(info.url);
            pageInfo = FindPageInStack(pagePath);
        }
        if (pageInfo.first == popIndex) {
            // replace top self in SINGLE mode, do nothing.
            return;
        }
        if (pageInfo.second) {
            // find page in stack, move position and update params.
#if defined(ENABLE_SPLIT_MODE)
            stageManager->SetIsNewPageReplacing(true);
#endif
            MovePageToFront(pageInfo.first, pageInfo.second, info, false, true, false);
#if defined(ENABLE_SPLIT_MODE)
            stageManager->SetIsNewPageReplacing(false);
#endif
            popIndex = popIndex - 1;
            findPage = true;
        } else {
            auto index = FindPageInRestoreStack(info.url);
            if (index != INVALID_PAGE_INDEX) {
                // find page in restore page, create page, move position and update params.
                RestorePageWithTarget(index, false, info, RestorePageDestination::BELLOW_TOP, false);
                return;
            }
        }
    }
    if (!findPage) {
        isNewPageReplacing_ = true;
#if defined(ENABLE_SPLIT_MODE)
        stageManager->SetIsNewPageReplacing(true);
#endif
        LoadPage(GenerateNextPageId(), info, true, false);
#if defined(ENABLE_SPLIT_MODE)
        stageManager->SetIsNewPageReplacing(false);
#endif
        isNewPageReplacing_ = false;
    }
    if (popIndex < 0 || popNode == GetCurrentPageNode() || GetPageIndex(popNode) != popIndex) {
        return;
    }
    auto iter = pageRouterStack_.begin();
    std::advance(iter, popIndex);
    auto lastIter = pageRouterStack_.erase(iter);
    pageRouterStack_.emplace_back(WeakPtr<FrameNode>(AceType::DynamicCast<FrameNode>(popNode)));
    popNode->MovePosition(GetLastPageIndex());
    for (auto iter = lastIter; iter != pageRouterStack_.end(); ++iter, ++popIndex) {
        auto page = iter->Upgrade();
        if (!page) {
            continue;
        }
        if (page == popNode) {
            // do not change index of page that will be replaced.
            continue;
        }
        auto pagePattern = page->GetPattern<NG::PagePattern>();
        pagePattern->GetPageInfo()->SetPageIndex(popIndex + 1);
    }
#if defined(ENABLE_SPLIT_MODE)
    stageManager->SetIsNewPageReplacing(true);
#endif
    PopPage("", false, false);
#if defined(ENABLE_SPLIT_MODE)
    stageManager->SetIsNewPageReplacing(false);
#endif
}

void PageRouterManager::RestoreOhmUrl(const RouterPageInfo& target, std::function<void()>&& finishCallback,
    RestorePageDestination dest, bool needTransition)
{
    RouterPageInfo info = target;
    info.path = info.url + ".js";
    auto pageNode = CreatePage(GenerateNextPageId(), info);
    if (!pageNode) {
        return;
    }

    if (dest == RestorePageDestination::TOP) {
        PushPageToTop(pageNode, std::move(finishCallback), needTransition);
    } else if (dest == RestorePageDestination::BELLOW_TOP) {
        InsertPageBellowTop(pageNode, std::move(finishCallback));
    } else if (dest == RestorePageDestination::BOTTOM) {
        InsertPageToBottom(pageNode, std::move(finishCallback));
    }
}

void PageRouterManager::InsertPageBellowTop(RefPtr<FrameNode>& pageNode, std::function<void()>&& finishCallback)
{
    auto context = DynamicCast<NG::PipelineContext>(PipelineContext::GetCurrentContext());
    auto stageManager = context ? context->GetStageManager() : nullptr;
    if (!stageManager) {
        return;
    }

    if (pageRouterStack_.empty()) {
        TAG_LOGE(AceLogTag::ACE_ROUTER, "empty stack when insert page bellow top");
        return;
    }
    auto backupStack = pageRouterStack_;
    auto it = pageRouterStack_.end();
    --it;
    pageRouterStack_.insert(it, WeakPtr<FrameNode>(pageNode));

    insertPageProcessingType_ = InsertPageProcessingType::INSERT_BELLOW_TOP;
    if (!stageManager->InsertPage(pageNode, true)) {
        insertPageProcessingType_ = InsertPageProcessingType::NONE;
        std::swap(backupStack, pageRouterStack_);
        return;
    }
    insertPageProcessingType_ = InsertPageProcessingType::NONE;

    if (finishCallback) {
        finishCallback();
    }
}

void PageRouterManager::PushPageToTop(
    RefPtr<FrameNode>& pageNode, std::function<void()>&& finishCallback, bool needTransition)
{
    pageRouterStack_.emplace_back(pageNode);
    if (!OnPageReady(pageNode, true, needTransition)) {
        pageRouterStack_.pop_back();
    }

    if (finishCallback) {
        finishCallback();
    }
}

void PageRouterManager::InsertPageToBottom(RefPtr<FrameNode>& pageNode, std::function<void()>&& finishCallback)
{
    auto context = DynamicCast<NG::PipelineContext>(PipelineContext::GetCurrentContext());
    auto stageManager = context ? context->GetStageManager() : nullptr;
    if (!stageManager) {
        return;
    }

    if (pageRouterStack_.empty()) {
        TAG_LOGW(AceLogTag::ACE_ROUTER, "empty stack when insert page to bottom");
        return;
    }
    pageRouterStack_.insert(pageRouterStack_.begin(), WeakPtr<FrameNode>(pageNode));

    insertPageProcessingType_ = InsertPageProcessingType::INSERT_BOTTOM;
    if (!stageManager->InsertPage(pageNode, false)) {
        insertPageProcessingType_ = InsertPageProcessingType::NONE;
        if (!pageRouterStack_.empty()) {
            pageRouterStack_.pop_front();
        }
        return;
    }
    insertPageProcessingType_ = InsertPageProcessingType::NONE;

    if (finishCallback) {
        finishCallback();
    }
}

void PageRouterManager::LoadOhmUrlPage(const std::string& url, std::function<void()>&& finishCallback,
    const std::function<void(const std::string& errorMsg, int32_t errorCode)>& errorCallback,
    const std::string& finishCallbackTaskName, const std::string& errorCallbackTaskName)
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pageUrlChecker = container->GetPageUrlChecker();
    CHECK_NULL_VOID(pageUrlChecker);
    auto instanceId = container->GetInstanceId();
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto callback = [taskExecutor, instanceId, task = std::move(finishCallback), finishCallbackTaskName]() {
            ContainerScope scope(instanceId);
            taskExecutor->PostTask(task, TaskExecutor::TaskType::JS, finishCallbackTaskName,
                TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
        };

    auto silentInstallErrorCallBack = [errorCb = errorCallback, taskExecutor, instanceId, errorCallbackTaskName](
        int32_t errorCode, const std::string& errorMsg) {
        if (!errorCb) {
            TAG_LOGW(AceLogTag::ACE_ROUTER, "errorCallback is null");
            return;
        }
        ContainerScope scope(instanceId);
        taskExecutor->PostTask([errorCb, errorCode, errorMsg]() { errorCb(errorMsg, errorCode); },
            TaskExecutor::TaskType::JS, errorCallbackTaskName,
            TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
    };
    pageUrlChecker->LoadPageUrl(url, callback, silentInstallErrorCallBack);
}

void PageRouterManager::SetPageInfoRouteName(const RefPtr<EntryPageInfo>& info)
{
    std::optional<std::string> routeName = std::nullopt;
    if (info->IsCreateByNamedRouter()) {
        // info->GetPageUrl() represents the name of namedRoute
        routeName = info->GetPageUrl();
    } else {
        auto container = Container::Current();
        CHECK_NULL_VOID(container);
        // info->GetPageUrl() represents the url of destination page
        routeName = Framework::JsiDeclarativeEngine::GetRouteNameByUrl(
            info->GetPageUrl(), container->GetBundleName(), container->GetModuleName());
    }
    info->SetRouteName(routeName);
}

void PageRouterManager::UpdateSrcPage()
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    stageManager->SetSrcPage(GetCurrentPageNode());
}
} // namespace OHOS::Ace::NG
