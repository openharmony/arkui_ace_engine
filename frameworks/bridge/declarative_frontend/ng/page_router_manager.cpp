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
            pipeline->Finish(false);
        },
        TaskExecutor::TaskType::UI);
}

} // namespace

void PageRouterManager::RunPage(const std::string& url, const std::string& params)
{
    CHECK_RUN_ON(JS);
    RouterPageInfo info { url };
    if (!info.url.empty()) {
        info.path = manifestParser_->GetRouter()->GetPagePath(url);
    } else {
        info.path = manifestParser_->GetRouter()->GetEntry();
        info.url = manifestParser_->GetRouter()->GetEntry("");
    }
    LOGD("router.Push pagePath = %{private}s", info.url.c_str());
    RouterOptScope scope(this);
    LoadPage(GenerateNextPageId(), info, params);
}

void PageRouterManager::RunCard(const std::string& url, const std::string& params, uint64_t cardId)
{
    CHECK_RUN_ON(JS);
    RouterPageInfo info { url };
    if (!info.url.empty()) {
        info.path = manifestParser_->GetRouter()->GetPagePath(url);
    } else {
        info.path = manifestParser_->GetRouter()->GetEntry();
        info.url = manifestParser_->GetRouter()->GetEntry("");
    }
    LoadCard(0, info, params, cardId);
}

void PageRouterManager::Push(const RouterPageInfo& target, const std::string& params, RouterMode mode)
{
    CHECK_RUN_ON(JS);
    if (inRouterOpt_) {
        LOGI("in router opt, post push router task");
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->PostAsyncEvent([weak = WeakClaim(this), target, params, mode]() {
            auto router = weak.Upgrade();
            CHECK_NULL_VOID(router);
            router->Push(target, params, mode);
        });
        return;
    }
    StartPush(target, params, mode);
}

void PageRouterManager::Replace(const RouterPageInfo& target, const std::string& params, RouterMode mode)
{
    CHECK_RUN_ON(JS);
    if (inRouterOpt_) {
        LOGI("in router opt, post replace router task");
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->PostAsyncEvent([weak = WeakClaim(this), target, params, mode]() {
            auto router = weak.Upgrade();
            CHECK_NULL_VOID(router);
            router->Replace(target, params, mode);
        });
        return;
    }
    StartReplace(target, params, mode);
}

void PageRouterManager::BackWithTarget(const RouterPageInfo& target, const std::string& params)
{
    CHECK_RUN_ON(JS);
    LOGD("router.Back path = %{private}s", target.url.c_str());
    if (inRouterOpt_) {
        LOGI("in router opt, post back router task");
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->PostAsyncEvent([weak = WeakClaim(this), target, params]() {
            auto router = weak.Upgrade();
            CHECK_NULL_VOID(router);
            router->BackWithTarget(target, params);
        });
        return;
    }
    BackCheckAlert(target, params);
}

void PageRouterManager::Clear()
{
    CHECK_RUN_ON(JS);
    if (inRouterOpt_) {
        LOGI("in router opt, post clear router task");
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->PostAsyncEvent([weak = WeakClaim(this)]() {
            auto router = weak.Upgrade();
            CHECK_NULL_VOID(router);
            router->Clear();
        });
        return;
    }
    StartClean();
}

void PageRouterManager::EnableAlertBeforeBackPage(const std::string& message, std::function<void(int32_t)>&& callback)
{
    auto currentPage = pageRouterStack_.back().Upgrade();
    CHECK_NULL_VOID(currentPage);
    auto pagePattern = currentPage->GetPattern<PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    auto pageInfo = DynamicCast<EntryPageInfo>(pagePattern->GetPageInfo());
    CHECK_NULL_VOID(pageInfo);
    ClearAlertCallback(pageInfo);

    DialogProperties dialogProperties = {
        .content = message,
        .autoCancel = false,
        .buttons = { { .text = Localization::GetInstance()->GetEntryLetters("common.cancel"), .textColor = "" },
            { .text = Localization::GetInstance()->GetEntryLetters("common.ok"), .textColor = "" } },
        .onSuccess =
            [weak = AceType::WeakClaim(this), callback](int32_t successType, int32_t successIndex) {
                LOGI("showDialog successType: %{public}d, successIndex: %{public}d", successType, successIndex);
                if (!successType) {
                    callback(successIndex);
                    if (successIndex) {
                        auto router = weak.Upgrade();
                        CHECK_NULL_VOID(router);
                        router->StartBack(router->ngBackUri_, router->backParam_);
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
    ClearAlertCallback(pageInfo);
    pageInfo->SetAlertCallback(nullptr);
}

void PageRouterManager::ClearAlertCallback(const RefPtr<PageInfo>& pageInfo)
{
    if (pageInfo->GetAlertCallback()) {
        // notify to clear js reference
        auto alertCallback = pageInfo->GetAlertCallback();
        alertCallback(static_cast<int32_t>(Framework::AlertState::RECOVERY));
        pageInfo->SetAlertCallback(nullptr);
    }
}

void PageRouterManager::StartClean()
{
    RouterOptScope scope(this);
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
    return StartPop();
}

bool PageRouterManager::StartPop()
{
    CHECK_RUN_ON(JS);
    RouterOptScope scope(this);
    if (pageRouterStack_.size() <= 1) {
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
    return true;
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
    name = pageInfo->GetPageUrl();
    path = pageInfo->GetPagePath();
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
    if (Framework::GetAssetContentImpl(assetManager, entryPageInfo->GetPagePath() + ".map", jsSourceMap)) {
        auto pageMap = MakeRefPtr<Framework::RevSourceMap>();
        pageMap->Init(jsSourceMap);
        entryPageInfo->SetPageMap(pageMap);
        return pageMap;
    }
    LOGW("js source map load failed!");
    return nullptr;
}

int32_t PageRouterManager::GenerateNextPageId()
{
    return ++pageId_;
}

std::pair<int32_t, RefPtr<FrameNode>> PageRouterManager::FindPageInStack(const std::string& url)
{
    auto iter = std::find_if(pageRouterStack_.rbegin(), pageRouterStack_.rend(), [url](const WeakPtr<FrameNode>& item) {
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

void PageRouterManager::StartPush(const RouterPageInfo& target, const std::string& params, RouterMode mode)
{
    CHECK_RUN_ON(JS);
    RouterOptScope scope(this);
    if (target.url.empty()) {
        LOGE("router.Push uri is empty");
        return;
    }
    if (!manifestParser_) {
        LOGE("the router manifest parser is null.");
        return;
    }
    std::string url = target.url;
    std::string pagePath = manifestParser_->GetRouter()->GetPagePath(url);
    LOGD("router.Push pagePath = %{private}s", pagePath.c_str());
    if (pagePath.empty()) {
        LOGE("[Engine Log] this uri not support in route push.");
        return;
    }

    if (mode == RouterMode::SINGLE) {
        auto pageInfo = FindPageInStack(url);
        if (pageInfo.second) {
            // find page in stack, move postion and update params.
            MovePageToFront(pageInfo.first, pageInfo.second, params, false);
            return;
        }
    }

    RouterPageInfo info { url };
    info.path = pagePath;
    LoadPage(GenerateNextPageId(), info, params);
}

void PageRouterManager::StartReplace(const RouterPageInfo& target, const std::string& params, RouterMode mode)
{
    CHECK_RUN_ON(JS);
    RouterOptScope scope(this);
    if (target.url.empty()) {
        LOGE("router.Push uri is empty");
        return;
    }
    if (!manifestParser_) {
        LOGE("the router manifest parser is null.");
        return;
    }
    std::string url = target.url;
    std::string pagePath = manifestParser_->GetRouter()->GetPagePath(url);
    LOGD("router.Push pagePath = %{private}s", pagePath.c_str());
    if (pagePath.empty()) {
        LOGE("[Engine Log] this uri not support in route push.");
        return;
    }

    PopPage("", false, false);

    if (mode == RouterMode::SINGLE) {
        auto pageInfo = FindPageInStack(url);
        if (pageInfo.second) {
            // find page in stack, move postion and update params.
            MovePageToFront(pageInfo.first, pageInfo.second, params, false, true, false);
            return;
        }
    }

    RouterPageInfo info { url };
    info.path = pagePath;
    LoadPage(GenerateNextPageId(), info, params, false, false, false);
}

void PageRouterManager::StartBack(const RouterPageInfo& target, const std::string& params)
{
    if (target.url.empty()) {
        std::string pagePath;
        size_t pageRouteSize = pageRouterStack_.size();
        if (pageRouteSize < 2) {
            LOGI("router stack is only one, back to desktop");
            ExitToDesktop();
            return;
        }
        // TODO: restore page operation.
        PopPage(params, true, true);
        return;
    }

    if (!manifestParser_) {
        LOGE("the router manifest parser is null.");
        return;
    }
    std::string url = target.url;
    std::string pagePath = manifestParser_->GetRouter()->GetPagePath(url);
    LOGD("router.Push pagePath = %{private}s", pagePath.c_str());
    if (pagePath.empty()) {
        LOGE("[Engine Log] this uri not support in route push.");
        return;
    }
    auto pageInfo = FindPageInStack(url);
    if (pageInfo.second) {
        // find page in stack, pop to specified index.
        PopPageToIndex(pageInfo.first, params, true, true);
        return;
    }
    LOGI("fail to find specified page to pop");
    ExitToDesktop();
}

void PageRouterManager::BackCheckAlert(const RouterPageInfo& target, const std::string& params)
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
        ngBackUri_ = target;
        backParam_ = params;

        auto pipelineContext = PipelineContext::GetCurrentContext();
        auto overlayManager = pipelineContext ? pipelineContext->GetOverlayManager() : nullptr;
        CHECK_NULL_VOID(overlayManager);
        overlayManager->ShowDialog(
            pageInfo->GetDialogProperties(), nullptr, AceApplicationInfo::GetInstance().IsRightToLeft());
        return;
    }

    StartBack(target, params);
}

void PageRouterManager::LoadPage(int32_t pageId, const RouterPageInfo& target, const std::string& params,
    bool /*isRestore*/, bool needHideLast, bool needTransition)
{
    // TODO: isRestore function.
    CHECK_RUN_ON(JS);
    LOGI("PageRouterManager LoadPage[%{public}d]: %{public}s.", pageId, target.url.c_str());
    auto entryPageInfo = AceType::MakeRefPtr<EntryPageInfo>(pageId, target.url, target.path, params);
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(entryPageInfo);
    auto pageNode =
        FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), pagePattern);
    pageRouterStack_.emplace_back(pageNode);
    auto result = loadJs_(target.path);
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
    LOGI("PageRouterManager LoadPage[%{public}d]: %{public}s. success", pageId, target.url.c_str());
}

void PageRouterManager::LoadCard(int32_t pageId, const RouterPageInfo& target, const std::string& params,
    uint64_t cardId, bool /*isRestore*/, bool needHideLast)
{
    CHECK_RUN_ON(JS);
    auto entryPageInfo = AceType::MakeRefPtr<EntryPageInfo>(pageId, target.url, target.path, params);
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(entryPageInfo);
    auto pageNode =
        FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), pagePattern);
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

    if (!OnPageReady(pageNode, needHideLast, needHideLast, isCardRouter, cardId)) {
        LOGE("fail to mount page");
        pageRouterStack_.pop_back();
        return;
    }
}

void PageRouterManager::MovePageToFront(int32_t index, const RefPtr<FrameNode>& pageNode, const std::string& params,
    bool needHideLast, bool forceShowCurrent, bool needTransition)
{
    LOGD("MovePageToFront to index: %{public}d", index);
    // update param first.
    CHECK_NULL_VOID(pageNode);
    auto pagePattern = pageNode->GetPattern<PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    auto pageInfo = DynamicCast<EntryPageInfo>(pagePattern->GetPageInfo());
    CHECK_NULL_VOID(pageInfo);

    if (index == static_cast<int32_t>(pageRouterStack_.size() - 1)) {
        LOGD("already on the top");
        if (!params.empty()) {
            pageInfo->ReplacePageParams(params);
        }
        if (forceShowCurrent) {
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
    if (!params.empty()) {
        tempParam = pageInfo->ReplacePageParams(params);
    }
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
    if (params.empty()) {
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
        iter++;
    }
    if (params.empty()) {
        if (!OnPopPageToIndex(index, needShowNext, needTransition)) {
            LOGE("fail to pop page to index");
            std::swap(temp, pageRouterStack_);
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
    const RefPtr<FrameNode>& pageNode, bool needHideLast, bool needTransition, bool isCardRouter, uint64_t cardId)
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

} // namespace OHOS::Ace::NG
