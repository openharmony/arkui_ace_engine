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
#include "base/ressched/ressched_report.h"
#include "base/perfmonitor/perf_monitor.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_advanced_register.h"
#include "core/components_ng/pattern/stage/page_node.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/stage/stage_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t INVALID_PAGE_INDEX = -1;
constexpr int32_t MAX_ROUTER_STACK_SIZE = 32;
} // namespace

RefPtr<FrameNode> PageRouterManager::PushExtender(const RouterPageInfo& target)
{
    CHECK_RUN_ON(JS);
    if (inRouterOpt_) {
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(context, nullptr);
        context->PostAsyncEvent(
            [weak = WeakClaim(this), target]() {
                auto router = weak.Upgrade();
                CHECK_NULL_VOID(router);
                router->Push(target);
            },
            "ArkUIPageRouterPush", TaskExecutor::TaskType::JS);
        return nullptr;
    }
    RouterOptScope scope(this);
    if (target.url.empty()) {
        TAG_LOGE(AceLogTag::ACE_ROUTER, "push url is empty");
        return nullptr;
    }
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, nullptr);
    auto stageManager = context->GetStageManager();
    CHECK_NULL_RETURN(stageManager, nullptr);
    if (GetStackSize() >= MAX_ROUTER_STACK_SIZE && !stageManager->GetForceSplitEnable()) {
        TAG_LOGW(AceLogTag::ACE_ROUTER, "StartPush exceeds maxStackSize.");
        if (target.errorCallback != nullptr) {
            target.errorCallback("The pages are pushed too much.", ERROR_CODE_PAGE_STACK_FULL);
        }
        return nullptr;
    }
    RouterPageInfo info = target;
    info.path = info.url + ".js";
    if (info.path.empty()) {
        TAG_LOGW(AceLogTag::ACE_ROUTER, "empty path found in StartPush with url: %{public}s", info.url.c_str());
        if (info.errorCallback != nullptr) {
            info.errorCallback("The uri of router is not exist.", ERROR_CODE_URI_ERROR);
        }
        return nullptr;
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
            return pagePattern->GetHost();
        }
        auto index = FindPageInRestoreStack(info.url);
        if (index != INVALID_PAGE_INDEX) {
            // find page in restore page, create page, move position and update params.
            RestorePageWithTarget(index, false, info, RestorePageDestination::TOP);
            return pageInfo.second;
        }
    }
    auto loadPageSuccess = LoadPageExtender(GenerateNextPageId(), info, true, true, true);
    if (!loadPageSuccess) {
        return nullptr;
    }
    auto pageNode = pageRouterStack_.back().Upgrade();
    return pageNode;
}

RefPtr<FrameNode> PageRouterManager::ReplaceExtender(const RouterPageInfo& target,
    std::function<void()>&& enterFinishCallback)
{
    CHECK_RUN_ON(JS);
    if (inRouterOpt_) {
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(context, nullptr);
        context->PostAsyncEvent(
            [weak = WeakClaim(this), target]() {
                auto router = weak.Upgrade();
                CHECK_NULL_VOID(router);
                router->Replace(target);
            },
            "ArkUIPageRouterReplace", TaskExecutor::TaskType::JS);
        return nullptr;
    }
    RouterOptScope scope(this);
    CleanPageOverlay();
    if (target.url.empty()) {
        return nullptr;
    }

    RouterPageInfo info = target;
    info.path = info.url + ".js";
    if (info.path.empty()) {
        TAG_LOGW(AceLogTag::ACE_ROUTER, "empty path found in StartReplace with url: %{public}s", info.url.c_str());
        if (info.errorCallback != nullptr) {
            info.errorCallback("The uri of router is not exist.", ERROR_CODE_URI_ERROR_LITE);
        }
        return nullptr;
    }
    UpdateSrcPage();

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
#if defined(ENABLE_SPLIT_MODE)
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_RETURN(stageManager, nullptr);
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
            CHECK_NULL_RETURN(replacePageNode, nullptr);
            auto pagePattern = pageInfo.second->GetPattern<PagePattern>();
            if (pagePattern) {
                pagePattern->FireOnNewParam(info.params);
            }
            return replacePageNode;
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
                return replacePageNode;
            }
        }
    }
    RefPtr<FrameNode> pageNode = nullptr;
    if (!findPage) {
        isNewPageReplacing_ = true;
#if defined(ENABLE_SPLIT_MODE)
        stageManager->SetIsNewPageReplacing(true);
#endif
        bool loadPageSuccess = LoadPageExtender(GenerateNextPageId(), info, false, false);
        if (loadPageSuccess) {
            pageNode = pageRouterStack_.back().Upgrade();
        }
#if defined(ENABLE_SPLIT_MODE)
        stageManager->SetIsNewPageReplacing(false);
#endif
        isNewPageReplacing_ = false;
    }
    if (popIndex < 0 || popNode == GetCurrentPageNode()) {
        return pageNode;
    }
    CHECK_NULL_RETURN(popNode, nullptr);
    auto pagePattern = popNode->GetPattern<PagePattern>();
    CHECK_NULL_RETURN(pagePattern, nullptr);
    pagePattern->SetOnNodeDisposeCallback(std::move(enterFinishCallback));
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
    return pageNode;
}

RefPtr<FrameNode> PageRouterManager::RunPageExtender(
    const RouterPageInfo& target)
{
    PerfMonitor::GetPerfMonitor()->SetAppStartStatus();
    ACE_SCOPED_TRACE("PageRouterManager::RunPage");
    CHECK_RUN_ON(JS);
    RouterPageInfo info = target;
    info.path = info.url + ".js";
    auto loadPageSuccess = LoadPageExtender(GenerateNextPageId(), info);
    if (!loadPageSuccess) {
        return nullptr;
    }
    auto pageNode = pageRouterStack_.back().Upgrade();
    return pageNode;
}

bool PageRouterManager::LoadPageExtender(
    int32_t pageId, const RouterPageInfo& target, bool needHideLast, bool needTransition, bool /*isPush*/)
{
    ACE_SCOPED_TRACE_COMMERCIAL("load page: %s(id:%d)", target.url.c_str(), pageId);
    CHECK_RUN_ON(JS);
    auto pageNode = CreatePageExtender(pageId, target);

    if (!pageNode) {
        TAG_LOGE(AceLogTag::ACE_ROUTER, "failed to create page in LoadPage");
        return false;
    }

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
} // namespace OHOS::Ace::NG