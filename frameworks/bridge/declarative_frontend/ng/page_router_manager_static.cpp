/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "base/thread/task_dependency_manager.h"
#include "base/ressched/ressched_report.h"
#include "base/perfmonitor/perf_monitor.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_advanced_register.h"
#include "core/components_ng/pattern/stage/page_node.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/stage/stage_manager.h"
#if !defined(PREVIEW)
#include "core/components_ng/syntax/static/detached_free_root_proxy_node.h"
#endif
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t INVALID_PAGE_INDEX = -1;
constexpr int32_t MAX_ROUTER_STACK_SIZE = 32;
void RegisterPageCallback(const RefPtr<FrameNode>& frameNode, void* jsViewNode)
{
    auto jsNode = AceType::Claim(reinterpret_cast<UINode*>(jsViewNode));
    CHECK_NULL_VOID(jsNode);
    auto curPageNode = AceType::DynamicCast<PageNode>(frameNode);
    CHECK_NULL_VOID(curPageNode);
    auto pagePattern = curPageNode->GetPattern<NG::PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    auto customNode = AceType::DynamicCast<CustomNode>(jsNode);
    CHECK_NULL_VOID(customNode);
    pagePattern->SetOnPageShow([weak = WeakPtr<CustomNode>(customNode)]() {
        auto view = weak.Upgrade();
        if (view) {
            view->FireOnPageShow();
        }
    });
    pagePattern->SetOnPageHide([weak = WeakPtr<CustomNode>(customNode)]() {
        auto view = weak.Upgrade();
        if (view) {
            view->FireOnPageHide();
        }
    });
    pagePattern->SetOnBackPressed([weak = WeakPtr<CustomNode>(customNode)]() {
        auto view = weak.Upgrade();
        if (view) {
            return view->FireOnBackPressed();
        }
        return false;
    });

    pagePattern->SetPageTransitionFunc(
        [weak = WeakPtr<CustomNode>(customNode), pageId = curPageNode->GetId(),
            weakPage = WeakPtr<FrameNode>(curPageNode)]() {
            auto custom = weak.Upgrade();
            auto page = weakPage.Upgrade();
            if (custom && page) {
                auto pattern = page->GetPattern<PagePattern>();
                CHECK_NULL_VOID(pattern);
                NG::ScopedViewStackProcessor scopedViewStackProcessor;
                NG::ViewStackProcessor::GetInstance()->SetPageNode(page);
                // clear pageTransition effects and execute js to get latest pageTransition effects.
                pattern->ClearPageTransitionEffect();
                custom->FirePageTransition();
                NG::ViewStackProcessor::GetInstance()->SetPageNode(nullptr);
            }
        });

    pagePattern->MarkRenderDone();
    
#if !defined(PREVIEW)
    auto instanceId = Container::Current()->GetInstanceId();
    auto proxyNode = AceType::MakeRefPtr<DetachedFreeRootProxyNode>(instanceId);
    CHECK_NULL_VOID(proxyNode);
    proxyNode->AddChild(jsNode);
    proxyNode->MountToParent(curPageNode);
#else
    jsNode->MountToParent(curPageNode);
#endif
    curPageNode->MarkDirtyNode();
}

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

void PageRouterManager::PushExtender(
    const RouterPageInfo& target, const std::function<void()>&& finishCallback, void* jsNode)
{
    CHECK_RUN_ON(JS);
    if (inRouterOpt_) {
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->PostAsyncEvent(
            [weak = WeakClaim(this), pageCallback = std::move(finishCallback), jsNode, target]() {
                auto router = weak.Upgrade();
                CHECK_NULL_VOID(router);
                auto nonConstCallback = const_cast<std::function<void()>&&>(pageCallback);
                router->PushExtender(target, std::move(nonConstCallback), jsNode);
            },
            "ArkUIPageRouterPush", TaskExecutor::TaskType::JS);
        return;
    }
    RouterOptScope scope(this);
    if (target.url.empty()) {
        TAG_LOGE(AceLogTag::ACE_ROUTER, "push url is empty");
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
    info.path = info.url + ".js";
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
            auto pagePattern = pageInfo.second->GetPattern<PagePattern>();
            if (pagePattern) {
                pagePattern->FireOnNewParam(info.params);
            }
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
    auto loadPageSuccess = LoadPageExtender(GenerateNextPageId(), info, jsNode, true, true);
    if (!loadPageSuccess) {
        return;
    }
    auto pageNode = pageRouterStack_.back().Upgrade();
    CHECK_NULL_VOID(pageNode);
    auto pagePattern = pageNode->GetPattern<PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    pagePattern->SetOnNodeDisposeCallback(std::move(finishCallback));
}

void PageRouterManager::PushNamedRouteExtender(
    const RouterPageInfo& target, const std::function<void()>&& finishCallback, void* jsNode)
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
            target.errorCallback("Page stack error. Too many pages are pushed.", ERROR_CODE_PAGE_STACK_FULL);
        }
        return;
    }
    CleanPageOverlay();
    UpdateSrcPage();
    if (target.routerMode == RouterMode::SINGLE) {
        auto pageInfoByUrl = FindPageInStackByRouteName(target.url);
        if (pageInfoByUrl.second) {
            // find page in stack, move postion and update params.
            auto pagePattern = pageInfoByUrl.second->GetPattern<PagePattern>();
            if (pagePattern) {
                pagePattern->FireOnNewParam(target.params);
            }
            MovePageToFront(pageInfoByUrl.first, pageInfoByUrl.second, target, true);
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
    auto loadPageSuccess = LoadPageExtender(GenerateNextPageId(), info, jsNode, true, true);
    if (!loadPageSuccess) {
        return;
    }
    auto pageNode = pageRouterStack_.back().Upgrade();
    CHECK_NULL_VOID(pageNode);
    auto pagePattern = pageNode->GetPattern<PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    pagePattern->SetOnNodeDisposeCallback(std::move(finishCallback));
}

void PageRouterManager::ReplaceExtender(const RouterPageInfo& target,
    const std::function<void()>&& enterFinishCallback, void* jsNode)
{
    CHECK_RUN_ON(JS);
    if (inRouterOpt_) {
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->PostAsyncEvent(
            [weak = WeakClaim(this), pageCallback = std::move(enterFinishCallback), jsNode, target]() {
                auto router = weak.Upgrade();
                CHECK_NULL_VOID(router);
                auto nonConstCallback = const_cast<std::function<void()>&&>(pageCallback);
                router->ReplaceExtender(target, std::move(nonConstCallback), jsNode);
            },
            "ArkUIPageRouterReplace", TaskExecutor::TaskType::JS);
        return;
    }
    RouterOptScope scope(this);
    CleanPageOverlay();
    if (target.url.empty()) {
        return;
    }

    RouterPageInfo info = target;
    info.path = info.url + ".js";
    if (info.path.empty()) {
        TAG_LOGW(AceLogTag::ACE_ROUTER, "empty path found in StartReplace with url: %{public}s", info.url.c_str());
        if (info.errorCallback != nullptr) {
            info.errorCallback("The uri of router is not exist.", ERROR_CODE_URI_ERROR_LITE);
        }
        return;
    }
    UpdateSrcPage();

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
#if defined(ENABLE_SPLIT_MODE)
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_VOID(stageManager);
#endif
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
        auto replacePageNode = pageInfo.second;
        if (pageInfo.first == popIndex) {
            // replace top self in SINGLE mode, do nothing.
            CHECK_NULL_VOID(replacePageNode);
            auto pagePattern = pageInfo.second->GetPattern<PagePattern>();
            if (pagePattern) {
                pagePattern->FireOnNewParam(info.params);
            }
            return;
        }
        if (replacePageNode) {
            // find page in stack, move position and update params.
#if defined(ENABLE_SPLIT_MODE)
            stageManager->SetIsNewPageReplacing(true);
#endif
            MovePageToFront(pageInfo.first, replacePageNode, info, false, true, false);
#if defined(ENABLE_SPLIT_MODE)
            stageManager->SetIsNewPageReplacing(false);
#endif
            popIndex = popIndex - 1;
            findPage = true;
            auto pagePattern = replacePageNode->GetPattern<PagePattern>();
            if (pagePattern) {
                pagePattern->FireOnNewParam(info.params);
            }
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
        bool loadPageSuccess = LoadPageExtender(GenerateNextPageId(), info, jsNode, false, false);
        if (loadPageSuccess) {
            auto pageNode = pageRouterStack_.back().Upgrade();
            CHECK_NULL_VOID(pageNode);
            auto pagePattern = pageNode->GetPattern<PagePattern>();
            CHECK_NULL_VOID(pagePattern);
            pagePattern->SetOnNodeDisposeCallback(std::move(enterFinishCallback));
        }
#if defined(ENABLE_SPLIT_MODE)
        stageManager->SetIsNewPageReplacing(false);
#endif
        isNewPageReplacing_ = false;
    }
    if (popIndex < 0 || popNode == GetCurrentPageNode()) {
        return;
    }
    CHECK_NULL_VOID(popNode);
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

void PageRouterManager::ReplaceNamedRouteExtender(
    const RouterPageInfo& target, const std::function<void()>&& enterFinishCallback, void* jsNode)
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
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
#if defined(ENABLE_SPLIT_MODE)
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_VOID(stageManager);
#endif
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
            CHECK_NULL_VOID(pageInfo.second);
            auto pagePattern = pageInfo.second->GetPattern<PagePattern>();
            if (pagePattern) {
                pagePattern->FireOnNewParam(info.params);
            }
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
            auto pagePattern = pageInfo.second->GetPattern<PagePattern>();
            if (pagePattern) {
                pagePattern->FireOnNewParam(info.params);
            }
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
        bool loadPageSuccess = LoadPageExtender(GenerateNextPageId(), info, jsNode, true, false);
        if (loadPageSuccess) {
            auto pageNode = pageRouterStack_.back().Upgrade();
            CHECK_NULL_VOID(pageNode);
            auto pagePattern = pageNode->GetPattern<PagePattern>();
            CHECK_NULL_VOID(pagePattern);
            pagePattern->SetOnNodeDisposeCallback(std::move(enterFinishCallback));
        }
#if defined(ENABLE_SPLIT_MODE)
        stageManager->SetIsNewPageReplacing(false);
#endif
        isNewPageReplacing_ = false;
    }
    if (popIndex < 0 || popNode == GetCurrentPageNode()) {
        return;
    }
    CHECK_NULL_VOID(popNode);
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

void PageRouterManager::RunPageExtender(
    const RouterPageInfo& target, const std::function<void()>&& finishCallback, void* jsNode)
{
    PerfMonitor::GetPerfMonitor()->SetAppStartStatus();
    ACE_SCOPED_TRACE("PageRouterManager::RunPage");
    CHECK_RUN_ON(JS);
    RouterPageInfo info = target;
    info.path = info.url + ".js";
    auto loadPageSuccess = LoadPageExtender(GenerateNextPageId(), info, jsNode);
    if (!loadPageSuccess) {
        return;
    }
    auto pageNode = pageRouterStack_.back().Upgrade();
    CHECK_NULL_VOID(pageNode);
    auto pagePattern = pageNode->GetPattern<PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    pagePattern->SetOnNodeDisposeCallback(std::move(finishCallback));
}

bool PageRouterManager::LoadPageExtender(
    int32_t pageId, const RouterPageInfo& target, void* jsNode, bool needHideLast, bool needTransition)
{
    ACE_SCOPED_TRACE_COMMERCIAL("load page: %s(id:%d)", target.url.c_str(), pageId);
    CHECK_RUN_ON(JS);
    auto pageNode = CreatePageExtender(pageId, target);

    TaskDependencyManager::GetInstance()->Sync();

    if (!pageNode) {
        TAG_LOGE(AceLogTag::ACE_ROUTER, "failed to create page in LoadPage");
        return false;
    }

    RegisterPageCallback(pageNode, jsNode);

    pageRouterStack_.emplace_back(pageNode);
    if (!OnPageReady(pageNode, needHideLast, needTransition)) {
        pageRouterStack_.pop_back();
        TAG_LOGW(AceLogTag::ACE_ROUTER, "LoadPage OnPageReady Failed");
        return false;
    }
    AccessibilityEventType type = AccessibilityEventType::CHANGE;
    pageNode->OnAccessibilityEvent(type);
    TAG_LOGI(AceLogTag::ACE_ROUTER, "LoadPage Success");
    return true;
}

RefPtr<FrameNode> PageRouterManager::CreatePageExtender(int32_t pageId, const RouterPageInfo& target)
{
    ACE_SCOPED_TRACE("PageRouterManager::CreatePage");
    CHECK_RUN_ON(JS);
    TAG_LOGI(AceLogTag::ACE_ROUTER,
        "Page router manager is creating page[%{public}d]: url: %{public}s path: "
        "%{public}s, recoverable: %{public}s, namedRouter: %{public}s",
        pageId, target.url.c_str(), target.path.c_str(), (target.recoverable ? "yes" : "no"),
        (target.isNamedRouterMode ? "yes" : "no"));
    auto entryPageInfo = AceType::MakeRefPtr<EntryPageInfo>(
        pageId, target.url, target.path, target.params, target.recoverable, target.isNamedRouterMode);
    auto pagePattern = ViewAdvancedRegister::GetInstance()->CreatePagePattern(entryPageInfo);
    std::unordered_map<std::string, std::string> reportData { { "pageUrl", target.url } };
    ResSchedReportScope reportScope("push_page", reportData);
    auto pageNode = PageNode::CreatePageNode(ElementRegister::GetInstance()->MakeUniqueId(), pagePattern);
    pageNode->SetHostPageId(pageId);
    // !!! must push_back first for UpdateRootComponent
    pageRouterStack_.emplace_back(pageNode);

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
        // @bundle example: @bundle:com.example.applicationHsp/hsp/ets/mylib/pages/Index
        // only moduleName and pagePath/fileName is needed: hspmylib/pages/Index
        size_t bundleEndPos = keyInfo.find('/');
        size_t moduleStartPos = bundleEndPos + 1;
        size_t moduleEndPos = keyInfo.find('/', moduleStartPos);
        std::string moduleName = keyInfo.substr(moduleStartPos, moduleEndPos - moduleStartPos);
        size_t pageInfoStartPos = keyInfo.find('/', moduleEndPos + 1);
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

void PageRouterManager::StartBackExtender(const RouterPageInfo& target)
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
        PopPageToIndex(pageInfo.first, info.params, true, true);
        return;
    }

    auto index = FindPageInRestoreStack(target.url);
    if (index == INVALID_PAGE_INDEX) {
        return;
    }

    RestorePageWithTarget(index, true, target, RestorePageDestination::BOTTOM);
}

void PageRouterManager::BackWithTargetExtender(const RouterPageInfo& target)
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
    StartBackExtender(target);
}

void PageRouterManager::BackToIndexWithTargetExtender(int32_t index, const std::string& params)
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
    CleanPageOverlay();
    if (index > static_cast<int32_t>(restorePageStack_.size())) {
        PopPageToIndex(index - static_cast<int32_t>(restorePageStack_.size()) - 1, params, true, true);
        return;
    }

    RouterPageInfo info;
    info.params = params;
    RestorePageWithTarget(index - 1, true, info, RestorePageDestination::BOTTOM);
}
} // namespace OHOS::Ace::NG