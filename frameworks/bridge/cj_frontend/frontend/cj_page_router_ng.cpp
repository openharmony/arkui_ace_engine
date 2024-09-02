/*
* Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "bridge/cj_frontend/frontend/cj_page_router_ng.h"

#include "base/i18n/localization.h"
#include "bridge/cj_frontend/runtime/cj_runtime_delegate.h"
#include "bridge/cj_frontend/frontend/cj_frontend_abstract.h"
#include "bridge/cj_frontend/frontend/cj_page_loader.h"
#include "core/components_ng/pattern/stage/page_pattern.h"

using namespace OHOS::Ace::NG;

namespace OHOS::Ace::Framework {
constexpr int PAGE_SIZE_TWO = 2;

void UpdateCjPageLifeCycleFuncs(
    RefPtr<NG::PagePattern> pagePattern, OHOS::wptr<NativeView> weakView, RefPtr<NG::FrameNode> pageNode)
{
    CHECK_NULL_VOID(pagePattern);
    pagePattern->SetOnPageShow([weakView]() {
        auto view = weakView.promote();
        CHECK_NULL_VOID(view);
        view->FireOnShow();
    });
    pagePattern->SetOnPageHide([weakView]() {
        auto view = weakView.promote();
        CHECK_NULL_VOID(view);
        view->FireOnHide();
    });
    pagePattern->SetOnBackPressed([weakView]() {
        auto view = weakView.promote();
        CHECK_NULL_RETURN(view, false);
        return view->FireOnBackPress();
    });
    pagePattern->SetPageTransitionFunc([weakView, weakPage = WeakPtr<NG::FrameNode>(pageNode)]() {
        auto view = weakView.promote();
        CHECK_NULL_VOID(view);
        NG::ScopedViewStackProcessor scopedViewStackProcessor;
        NG::ViewStackProcessor::GetInstance()->SetPageNode(weakPage.Upgrade());
        view->FireOnTransition();
        NG::ViewStackProcessor::GetInstance()->SetPageNode(nullptr);
    });
}

bool LoadNativeViewNG(NativeView* view)
{
    LOGI("LoadNativeView start");
    auto currentObj = Container::Current();
    if (!currentObj) {
        LOGE("loadCJView fail, Container is null");
        return false;
    }
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(currentObj->GetFrontend());
    if (!frontend) {
        LOGE("loadCJView fail, frontend is not CJFrontendAbstract");
        return false;
    }
    auto pageRouterManager = AceType::DynamicCast<CJPageRouterNG>(frontend->GetPageRouterManager());
    if (!pageRouterManager) {
        LOGE("loadCJView fail, pageRouter not exist");
        return false;
    }
    auto pageNode = pageRouterManager->GetCurrentPageNode();
    if (!pageNode) {
        LOGE("loadCJView fail, page node not exist");
        return false;
    }
    Container::SetCurrentUsePartialUpdate(!view->IsFullUpdate());
    if (!pageNode->GetChildren().empty()) {
        LOGI("the page has view already, start cleanup");
        auto oldChild = AceType::DynamicCast<NG::CustomNode>(pageNode->GetChildren().front());
        if (oldChild) {
            oldChild->Reset();
        }
        pageNode->Clean();
    }
    auto pageRootNode = AceType::DynamicCast<NG::UINode>(view->CreateUI());
    if (!pageRootNode) {
        LOGE("loadCJView fail, created rootNode is null");
        return false;
    }
    pageRootNode->MountToParent(pageNode);
    auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
    CHECK_NULL_RETURN(pagePattern, false);
    OHOS::wptr<NativeView> weak = view;
    view->SetRenderDoneCallback([pagePattern] {
        pagePattern->MarkRenderDone();
    });
    UpdateCjPageLifeCycleFuncs(pagePattern, weak, pageNode);
    pageRouterManager->AddView(view->GetID());
    LOGI("OHOSAceFrameworkNGLoadCJView end.");
    return true;
}

namespace {
void ExitToDesktop()
{
    auto currentObj = Container::Current();
    CHECK_NULL_VOID(currentObj);
    auto taskExecutor = currentObj->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [] {
            auto pipeline = NG::PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            pipeline->Finish(false);
        },
        TaskExecutor::TaskType::UI, "CJExitToDesktop");
}
} // namespace

void CJPageRouterNG::OnShowCurrent()
{
    auto pageNode = GetCurrentPageNode();
    if (!pageNode) {
        LOGE("CJFrontendNG::OnShow no current page");
        return;
    }
    auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
    if (!pagePattern) {
        LOGE("CJFrontendNG::OnShow current page has no pattern");
        return;
    }
    pagePattern->OnShow();
}

void CJPageRouterNG::OnHideCurrent()
{
    auto pageNode = GetCurrentPageNode();
    if (!pageNode) {
        LOGE("CJFrontendNG::OnHide no current page");
        return;
    }
    auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
    if (!pagePattern) {
        LOGE("CJFrontendNG::OnHide current page has no pattern");
        return;
    }
    pagePattern->OnHide();
}

bool CJPageRouterNG::PopWithExitCheck()
{
    auto pageNode = GetCurrentPageNode();
    CHECK_NULL_RETURN(pageNode, false);
    auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
    CHECK_NULL_RETURN(pagePattern, false);
    if (pagePattern->OnBackPressed()) {
        return true;
    }
    return Pop();
}

bool CJPageRouterNG::AllowPopLastPage()
{
    auto currentPage = pageRouterStack_.back().Upgrade();
    CHECK_NULL_RETURN(currentPage, true);
    auto pagePattern = currentPage->GetPattern<PagePattern>();
    CHECK_NULL_RETURN(pagePattern, true);
    auto pageInfo = DynamicCast<EntryPageInfo>(pagePattern->GetPageInfo());
    CHECK_NULL_RETURN(pageInfo, true);
    if (pageInfo->GetAlertCallback()) {
        auto pipelineContext = NG::PipelineContext::GetCurrentContext();
        auto overlayManager = pipelineContext ? pipelineContext->GetOverlayManager() : nullptr;
        CHECK_NULL_RETURN(overlayManager, true);
        overlayManager->ShowDialog(
            pageInfo->GetDialogProperties(), nullptr, AceApplicationInfo::GetInstance().IsRightToLeft());
        return false;
    }

    return true;
}

void CJPageRouterNG::EnableAlertBeforeBackPage(const std::string& message, std::function<void(int32_t)> callback)
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

void CJPageRouterNG::DisableAlertBeforeBackPage()
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

void CJPageRouterNG::ClearAlertCallback(const RefPtr<PageInfo>& pageInfo)
{
    if (pageInfo->GetAlertCallback()) {
        // notify to clear js reference
        auto alertCallback = pageInfo->GetAlertCallback();
        alertCallback(static_cast<int32_t>(Framework::AlertState::RECOVERY));
        pageInfo->SetAlertCallback(nullptr);
    }
}

void CJPageRouterNG::StartClean()
{
    ProcessGuard guard(this);
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

bool CJPageRouterNG::StartPop()
{
    ProcessGuard guard(this);
    if (pageRouterStack_.size() <= 1 || viewStack_.size() <= 1) {
        // the last page.
        return false;
    }
    auto topNode = pageRouterStack_.back();
    auto topView = viewStack_.back();
    pageRouterStack_.pop_back();
    viewStack_.pop_back();
    if (!OnPopPage(true, true)) {
        LOGE("fail to pop page.");
        pageRouterStack_.emplace_back(topNode);
        viewStack_.emplace_back(topView);
        return false;
    }
    return true;
}

int32_t CJPageRouterNG::GetStackSize() const
{
    return static_cast<int32_t>(pageRouterStack_.size());
}

void CJPageRouterNG::GetState(int32_t& index, std::string& name, std::string& path)
{
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

std::string CJPageRouterNG::GetParams() const
{
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

std::string CJPageRouterNG::GetCurrentPageUrl()
{
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

std::pair<int32_t, RefPtr<FrameNode>> CJPageRouterNG::FindPageInStack(const std::string& url)
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

void CJPageRouterNG::StartPush(const RouterPageInfo& target, const std::string& params, RouterMode mode)
{
    ProcessGuard guard(this);
    if (target.url.empty()) {
        LOGE("router.Push uri is empty");
        return;
    }

    if (mode == RouterMode::SINGLE) {
        auto pageInfo = FindPageInStack(target.url);
        if (pageInfo.second) {
            // find page in stack, move postion and update params.
            MovePageToFront(pageInfo.first, pageInfo.second, params, false);
            return;
        }
    }

    LoadPage(GenerateNextPageId(), target, params);
}

void CJPageRouterNG::StartReplace(const RouterPageInfo& target, const std::string& params, RouterMode mode)
{
    ProcessGuard guard(this);
    if (target.url.empty()) {
        LOGE("router.Push uri is empty");
        return;
    }
    std::string url = target.url;

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
    LoadPage(GenerateNextPageId(), info, params, false, false, false);
}

void CJPageRouterNG::StartBack(const RouterPageInfo& target, const std::string& params)
{
    if (target.url.empty()) {
        std::string pagePath;
        size_t pageRouteSize = pageRouterStack_.size();
        if (pageRouteSize < PAGE_SIZE_TWO) {
            LOGI("router stack is only one, back to desktop");
            ExitToDesktop();
            return;
        }
        PopPage(params, true, true);
        return;
    }
    std::string url = target.url;
    auto pageInfo = FindPageInStack(url);
    if (pageInfo.second) {
        // find page in stack, pop to specified index.
        PopPageToIndex(pageInfo.first, params, true, true);
        return;
    }
    LOGI("fail to find specified page to pop");
}

void CJPageRouterNG::BackCheckAlert(const RouterPageInfo& target, const std::string& params)
{
    ProcessGuard guard(this);
    if (pageRouterStack_.empty()) {
        LOGI("page route stack is empty");
        return;
    }
    auto currentPage = pageRouterStack_.back().Upgrade();
    CHECK_NULL_VOID(currentPage);
    auto pagePattern = currentPage->GetPattern<PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    if (pagePattern->OnBackPressed()) {
        return;
    }
    
    auto pageInfo = DynamicCast<EntryPageInfo>(pagePattern->GetPageInfo());
    CHECK_NULL_VOID(pageInfo);
    if (pageInfo->GetAlertCallback()) {
        ngBackUri_ = target;
        backParam_ = params;

        auto pipelineContext = NG::PipelineContext::GetCurrentContext();
        auto overlayManager = pipelineContext ? pipelineContext->GetOverlayManager() : nullptr;
        CHECK_NULL_VOID(overlayManager);
        overlayManager->ShowDialog(
            pageInfo->GetDialogProperties(), nullptr, AceApplicationInfo::GetInstance().IsRightToLeft());
        return;
    }

    StartBack(target, params);
}

void CJPageRouterNG::LoadPage(int32_t pageId, const RouterPageInfo& target, const std::string& params, bool isRestore,
    bool needHideLast, bool needTransition)
{
    LOGI("PageRouterManager LoadPage[%{public}d]: %{public}s.", pageId, target.url.c_str());

    auto pipeline = GetCurrentPipeline(false);
    CHECK_NULL_VOID(pipeline);
    if (!pipeline->GetStageManager()) {
        LOGE("StageManager is null, waiting...");
        auto frontend = frontend_.Upgrade();
        CHECK_NULL_VOID(frontend);
        auto taskExecutor = frontend->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask([weak = WeakClaim(this), pageId, target, params, isRestore,
            needHideLast, needTransition] {
                auto self = weak.Upgrade();
                CHECK_NULL_VOID(self);
                self->LoadPage(pageId, target, params, isRestore, needHideLast, needTransition);
            }, TaskExecutor::TaskType::UI, "CJLoadPage");
        return;
    }

    auto entryPageInfo = AceType::MakeRefPtr<NG::EntryPageInfo>(pageId, target.url, target.path, params);
    auto pagePattern = AceType::MakeRefPtr<NG::PagePattern>(entryPageInfo);
    auto pageNode =
        NG::FrameNode::CreateFrameNode("page", ElementRegister::GetInstance()->MakeUniqueId(), pagePattern);
    pageNode->SetHostPageId(pageId);

    pageRouterStack_.emplace_back(pageNode);

    if (!CJRuntimeDelegate::GetInstance()->LoadAppEntry(target.url)) {
        LOGE("Run CJ Page fail: %{public}s", target.url.c_str());
        pageRouterStack_.pop_back();
        return;
    }

    if (!OnPageReady(pageNode, needHideLast, needTransition)) {
        LOGE("fail to mount page");
        pageRouterStack_.pop_back();
        return;
    }
    LOGI("CJPageRouter LoadPage[%{public}d]: %{public}s. success", pageId, target.url.c_str());
}

void CJPageRouterNG::MovePageToFront(int32_t index, const RefPtr<FrameNode>& pageNode, const std::string& params,
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
    auto currentObj = Container::Current();
    CHECK_NULL_VOID(currentObj);
    auto pipeline = currentObj->GetPipelineContext();
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

void CJPageRouterNG::PopPage(const std::string& params, bool needShowNext, bool needTransition)
{
    if (pageRouterStack_.empty() || viewStack_.empty()) {
        LOGE("page router stack size is illegal.");
        return;
    }
    if (needShowNext && (pageRouterStack_.size() == 1)) {
        LOGE("page router stack size is only one, can not show next.");
        return;
    }
    auto topNode = pageRouterStack_.back();
    auto topView = viewStack_.back();
    pageRouterStack_.pop_back();
    viewStack_.pop_back();
    if (params.empty()) {
        if (!OnPopPage(needShowNext, needTransition)) {
            LOGE("fail to pop page.");
            pageRouterStack_.emplace_back(topNode);
            viewStack_.emplace_back(topView);
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
    viewStack_.emplace_back(topView);
    pageInfo->ReplacePageParams(temp);
}

void CJPageRouterNG::PopPageToIndex(int32_t index, const std::string& params, bool needShowNext, bool needTransition)
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
            LOGE("fail to pop page to index.");
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

RefPtr<NG::PipelineContext> CJPageRouterNG::GetCurrentPipeline(bool isCardRouter, uint64_t cardId)
{
    auto currentObj = Container::Current();
    CHECK_NULL_RETURN(currentObj, nullptr);
    RefPtr<PipelineBase> pipeline;
    if (isCardRouter) {
        auto weak = currentObj->GetCardPipeline(cardId);
        pipeline = weak.Upgrade();
        CHECK_NULL_RETURN(pipeline, nullptr);
    } else {
        pipeline = currentObj->GetPipelineContext();
        CHECK_NULL_RETURN(pipeline, nullptr);
    }

    return DynamicCast<NG::PipelineContext>(pipeline);
}

bool CJPageRouterNG::OnPageReady(
    const RefPtr<FrameNode>& pageNode, bool needHideLast, bool needTransition, bool isCardRouter, uint64_t cardId)
{
    auto context = GetCurrentPipeline(isCardRouter, cardId);
    if (!context) {
        LOGE("fail to push page due to pipeline context is not NG");
        return false;
    }
    auto stageManager = context->GetStageManager();
    if (!stageManager) {
        LOGE("fail to push page due to stage manager is nullptr");
        return false;
    }
    return stageManager->PushPage(pageNode, needHideLast, needTransition);
}

bool CJPageRouterNG::OnPopPage(bool needShowNext, bool needTransition)
{
    auto currentObj = Container::Current();
    CHECK_NULL_RETURN(currentObj, false);
    auto pipeline = currentObj->GetPipelineContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto context = DynamicCast<NG::PipelineContext>(pipeline);
    auto stageManager = context ? context->GetStageManager() : nullptr;
    if (stageManager) {
        return stageManager->PopPage(needShowNext, needTransition);
    }
    LOGE("fail to pop page due to stage manager is nullptr");
    return false;
}

bool CJPageRouterNG::OnPopPageToIndex(int32_t index, bool needShowNext, bool needTransition)
{
    auto currentObj = Container::Current();
    CHECK_NULL_RETURN(currentObj, false);
    auto pipeline = currentObj->GetPipelineContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto context = DynamicCast<NG::PipelineContext>(pipeline);
    auto stageManager = context ? context->GetStageManager() : nullptr;
    if (stageManager) {
        return stageManager->PopPageToIndex(index, needShowNext, needTransition);
    }
    LOGE("fail to pop page to index due to stage manager is nullptr");
    return false;
}

bool CJPageRouterNG::OnCleanPageStack()
{
    auto currentObj = Container::Current();
    CHECK_NULL_RETURN(currentObj, false);
    auto pipeline = currentObj->GetPipelineContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto context = DynamicCast<NG::PipelineContext>(pipeline);
    auto stageManager = context ? context->GetStageManager() : nullptr;
    if (stageManager) {
        return stageManager->CleanPageStack();
    }
    LOGE("fail to pop page to index due to stage manager is nullptr");
    return false;
}

void CJPageRouterNG::FlushReload()
{
    for (const auto& viewId : viewStack_) {
        auto view = FFI::FFIData::GetData<NativeView>(viewId);
        if (view == nullptr) {
            continue;
        }
        view->MarkNeedUpdate();
    }
}
} // namespace OHOS::Ace::Framework
