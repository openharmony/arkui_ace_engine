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

#include "bridge/cj_frontend/frontend/cj_page_router.h"

#include "bridge/cj_frontend/frontend/cj_frontend_abstract.h"
#include "bridge/cj_frontend/frontend/cj_page_loader.h"
#include "bridge/cj_frontend/runtime/cj_runtime_delegate.h"
#include "bridge/common/accessibility/accessibility_node_manager.h"
#include "bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
void SetCjPageCallbackClassic(RefPtr<Framework::JsAcePage> page, NativeView* view)
{
    CHECK_NULL_VOID(view);
    wptr<NativeView> weak = view;
    CHECK_NULL_VOID(page);
    page->SetDeclarativeOnPageAppearCallback([weak]() {
        auto view = weak.promote();
        if (view) {
            view->FireOnShow();
        }
    });
    page->SetDeclarativeOnPageDisAppearCallback([weak]() {
        auto view = weak.promote();
        if (view) {
            view->FireOnHide();
        }
    });
    page->SetDeclarativeOnBackPressCallback([weak]() {
        auto view = weak.promote();
        if (view) {
            return view->FireOnBackPress();
        }
        return false;
    });
    page->SetDeclarativeOnPageRefreshCallback([weak]() {
        auto view = weak.promote();
        if (view) {
            view->MarkNeedUpdate();
        }
    });
    page->SetDeclarativeOnUpdateWithValueParamsCallback([weak](const std::string& params) {
        auto view = weak.promote();
        if (view && !params.empty()) {
            view->ExecuteUpdateWithValueParams(params);
        }
    });
}

bool LoadNativeViewClassic(NativeView* view)
{
    auto currentObj = Container::Current();
    if (!currentObj) {
        LOGE("LoadNativeView container is null");
        return false;
    }

    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(currentObj->GetFrontend());
    if (!frontend) {
        LOGE("LoadNativeView frontend is null or not CJFrontend");
        return false;
    }
    auto router = AceType::DynamicCast<CJPageRouter>(frontend->GetPageRouterManager());
    if (!router) {
        LOGE("LoadNativeView router is not CJPageRouter");
        return false;
    }
    auto page = router->GetLoadingPage();
    auto rootComponent = AceType::DynamicCast<Component>(view->CreateUI());
    std::list<RefPtr<Component>> stackChildren;
    stackChildren.emplace_back(rootComponent);
    auto rootStackComponent = AceType::MakeRefPtr<StackComponent>(
        Alignment::TOP_LEFT, StackFit::INHERIT, Overflow::OBSERVABLE, stackChildren);
    rootStackComponent->SetMainStackSize(MainStackSize::MAX);
    auto rootComposed = AceType::MakeRefPtr<ComposedComponent>("0", "root");
    rootComposed->SetChild(rootStackComponent);
    page->SetRootComponent(rootComposed);
    auto pageTransitionComponent = ViewStackProcessor::GetInstance()->GetPageTransitionComponent();
    ViewStackProcessor::GetInstance()->ClearPageTransitionComponent();
    page->SetPageTransition(pageTransitionComponent);

    // We are done, tell to the JSAgePage
    page->SetPageCreated();
    SetCjPageCallbackClassic(page, view);
    return true;
}

void CJPageRouter::PushLoadingPage(const RefPtr<JsAcePage>& page)
{
    loadingPage_ = page;
}

void CJPageRouter::OnShowCurrent()
{
    auto topPage = GetTopPage();
    CHECK_NULL_VOID(topPage);
    topPage->FireDeclarativeOnPageAppearCallback();
}

void CJPageRouter::OnHideCurrent()
{
    auto topPage = GetTopPage();
    CHECK_NULL_VOID(topPage);
    topPage->FireDeclarativeOnPageDisAppearCallback();
}

bool CJPageRouter::AllowPopLastPage()
{
    return true;
}

void CJPageRouter::LoadPage(int32_t pageId, const OHOS::Ace::CJPageRouterAbstract::RouterPageInfo& target,
    const std::string& params, bool isRestore, bool needHideLast, bool needTransition)
{
    LOGI("LoadPage[%{public}d]: %{public}s.", pageId, target.url.c_str());
    if (pageId < 0) {
        LOGE("FrontendDelegateDeclarative, invalid page id");
        return;
    }
    auto document = AceType::MakeRefPtr<DOMDocument>(pageId);
    auto page = AceType::MakeRefPtr<JsAcePage>(pageId, document, target.url, nullptr);
    page->SetPageParams(params);
    PushLoadingPage(page);
    pageRouterStack_.emplace_back(page);

    page->SetFlushCallback([weak = AceType::WeakClaim(this), url = target.url](const RefPtr<JsAcePage>& acePage) {
        CHECK_NULL_VOID(acePage);
        auto delegate = weak.Upgrade();
        CHECK_NULL_VOID(delegate);
        delegate->FlushPage(acePage, url);
    });
    auto frontend = frontend_.Upgrade();
    CHECK_NULL_VOID(frontend);
    if (!CJRuntimeDelegate::GetInstance()->LoadAppEntry(target.url)) {
        LOGE("Run CJ Page fail: %{public}s", target.url.c_str());
        pageRouterStack_.pop_back();
        return;
    }
    page->FlushCommands();
    auto pipeline = AceType::DynamicCast<PipelineContext>(frontend->GetPipelineContext());
    CHECK_NULL_VOID(pipeline);
    pipeline->FlushFocus();
    document->HandlePageLoadFinish();
}

void CJPageRouter::EnableAlertBeforeBackPage(const std::string& message, std::function<void(int32_t)> callback) {}

int32_t CJPageRouter::GetStackSize() const
{
    return pageRouterStack_.size();
}

std::string CJPageRouter::GetParams() const
{
    auto topPage = GetTopPage();
    if (!topPage) {
        return "";
    }
    return topPage->GetPageParams();
}

std::string CJPageRouter::GetCurrentPageUrl()
{
    auto topPage = GetTopPage();
    if (!topPage) {
        return "";
    }
    return topPage->GetUrl();
}

void CJPageRouter::StartPush(const OHOS::Ace::CJPageRouterAbstract::RouterPageInfo& target, const std::string& params,
    OHOS::Ace::CJPageRouterAbstract::RouterMode mode)
{
    ProcessGuard guard(this);
    if (target.url.empty()) {
        LOGE("router.Push uri is empty");
        return;
    }

    LoadPage(GenerateNextPageId(), target, params);
}

bool CJPageRouter::StartPop()
{
    ProcessGuard guard(this);
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

void CJPageRouter::StartReplace(const OHOS::Ace::CJPageRouterAbstract::RouterPageInfo& target,
    const std::string& params, OHOS::Ace::CJPageRouterAbstract::RouterMode mode)
{
    ProcessGuard guard(this);
    if (target.url.empty()) {
        LOGE("router.Push uri is empty");
        return;
    }
    std::string url = target.url;

    PopPage("", false, false);

    RouterPageInfo info { url };
    LoadPage(GenerateNextPageId(), info, params, false, false, false);
}

void CJPageRouter::BackCheckAlert(const RouterPageInfo& target, const std::string& params)
{
    {
        ProcessGuard guard(this);
        if (pageRouterStack_.empty()) {
            LOGI("page route stack is empty");
            return;
        }
        auto topPage = GetTopPage();
        CHECK_NULL_VOID(topPage);

        if (!topPage->FireDeclarativeOnBackPressCallback()) {
            return;
        }
    }

    StartPop();
}

void CJPageRouter::StartClean()
{
    ProcessGuard guard(this);
    if (pageRouterStack_.size() <= 1) {
        LOGW("current page stack can not clean, %{public}d", static_cast<int32_t>(pageRouterStack_.size()));
        return;
    }
    std::list<RefPtr<JsAcePage>> temp;
    std::swap(temp, pageRouterStack_);
    pageRouterStack_.emplace_back(temp.back());
    if (!OnCleanPageStack()) {
        LOGE("fail to clean page");
        std::swap(temp, pageRouterStack_);
    }
}

void CJPageRouter::PopPage(const std::string& params, bool needShowNext, bool needTransition)
{
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

    if (OnPopPage(needShowNext, needTransition)) {
        return;
    }
    LOGE("fail to pop page");
    // restore stack and pageParam.
    pageRouterStack_.emplace_back(topNode);
}

void CJPageRouter::PopPageToIndex(int32_t index, const std::string& params, bool needShowNext, bool needTransition)
{
    LOGD("PopPageToIndex to index: %{public}d", index);
    std::list<RefPtr<JsAcePage>> temp;
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

    if (OnPopPageToIndex(index, needShowNext, needTransition)) {
        return;
    }
    LOGE("fail to pop page to index");
    // restore stack and pageParam.
    std::swap(temp, pageRouterStack_);
}

bool CJPageRouter::OnPopPage(bool needShowNext, bool needTransition)
{
    auto frontend = frontend_.Upgrade();
    CHECK_NULL_RETURN(frontend, false);
    auto pipeline = AceType::DynamicCast<PipelineContext>(frontend->GetPipelineContext());
    CHECK_NULL_RETURN(pipeline, false);
    if (GetStackSize() == 1) {
        if (!AllowPopLastPage()) {
            return false;
        }
        OnHideCurrent();
        return true;
    }
    if (!pipeline->CanPopPage()) {
        return false;
    }
    OnHideCurrent();
    pipeline->RemovePageTransitionListener(lastTransitionListener_);
    lastTransitionListener_ = pipeline->AddPageTransitionListener(
        [weak = WeakClaim(this), pageId = GetTopPage()->GetPageId()](
            const TransitionEvent& event, const WeakPtr<PageElement>& in, const WeakPtr<PageElement>& out) {
            auto delegate = weak.Upgrade();
            if (delegate) {
                if (event == TransitionEvent::PUSH_END) {
                    delegate->OnPopSuccess();
                }
            }
        });
    return true;
}

bool CJPageRouter::OnPopPageToIndex(int32_t index, bool needShowNext, bool needTransition)
{
    return false;
}

bool CJPageRouter::OnCleanPageStack()
{
    return true;
}

void CJPageRouter::OnPopSuccess()
{
    SetCurrentPage();
    OnShowCurrent();
}

void CJPageRouter::SetCurrentPage()
{
    auto page = GetTopPage();
    CHECK_NULL_VOID(page);
    auto frontend = frontend_.Upgrade();
    CHECK_NULL_VOID(frontend);
    auto accessManager = frontend->GetAccessibilityManager();
    CHECK_NULL_VOID(accessManager);
    accessManager->SetVersion(AccessibilityVersion::JS_DECLARATIVE_VERSION);
    auto nodeManager = DynamicCast<AccessibilityNodeManager>(accessManager);
    nodeManager->SetRunningPage(page);
    OnPageUpdate(page, false);
}

void CJPageRouter::FlushPage(const RefPtr<OHOS::Ace::Framework::JsAcePage>& page, const std::string& url)
{
    if (page->FragmentCount() == 1) {
        OnPageReady(page, url, pageRouterStack_.size() > 1);
    } else {
        OnPageUpdate(page, true);
    }
}

void CJPageRouter::PostTask(std::function<void()> callback, bool isUI)
{
    auto frontend = frontend_.Upgrade();
    CHECK_NULL_VOID(frontend);
    auto executor = frontend->GetTaskExecutor();
    CHECK_NULL_VOID(executor);
    executor->PostTask(
        std::move(callback), isUI ? TaskExecutor::TaskType::UI : TaskExecutor::TaskType::JS, "CJPageRouterPostTask");
}

void CJPageRouter::OnPageReady(const RefPtr<JsAcePage>& page, const std::string& url, bool needHideLast)
{
    loadingPage_ = nullptr;
    auto frontend = frontend_.Upgrade();
    CHECK_NULL_VOID(frontend);
    auto jsCommands = std::make_shared<std::vector<RefPtr<JsCommand>>>();
    page->PopAllCommands(*jsCommands);

    auto pipelineContext = AceType::DynamicCast<PipelineContext>(frontend->GetPipelineContext());
    CHECK_NULL_VOID(pipelineContext);

    page->SetPipelineContext(pipelineContext);

    PostTask([weak = WeakClaim(this), jsCommands, url, page, pipelineContext, needHideLast] {
        auto self = weak.Upgrade();
        CHECK_NULL_VOID(self);
        // Flush all JS commands.
        for (const auto& command : *jsCommands) {
            command->Execute(page);
        }
        // Just clear all dirty nodes.
        page->ClearAllDirtyNodes();
        if (page->GetDomDocument()) {
            page->GetDomDocument()->HandleComponentPostBinding();
        }
        if (pipelineContext->GetAccessibilityManager()) {
            pipelineContext->GetAccessibilityManager()->HandleComponentPostBinding();
        }

        if (!pipelineContext->CanPushPage()) {
            LOGW("router push run in unexpected process");
            return;
        }
        self->OnPrePageChange(page);
        pipelineContext->RemovePageTransitionListener(self->lastTransitionListener_);
        self->lastTransitionListener_ = pipelineContext->AddPageTransitionListener(
            [weak, page](
                const TransitionEvent& event, const WeakPtr<PageElement>& in, const WeakPtr<PageElement>& out) {
                auto delegate = weak.Upgrade();
                if (event == TransitionEvent::PUSH_END) {
                    delegate->OnPopSuccess();
                }
            });
        pipelineContext->PushPage(page->BuildPage(url), page->GetStageElement());
    });
}

void CJPageRouter::OnPageUpdate(const RefPtr<OHOS::Ace::Framework::JsAcePage>& page, bool directExecute)
{
    auto frontend = frontend_.Upgrade();
    CHECK_NULL_VOID(frontend);
    auto pipeline = AceType::DynamicCast<PipelineContext>(frontend->GetPipelineContext());
    CHECK_NULL_VOID(pipeline);

    auto jsCommands = std::make_shared<std::vector<RefPtr<JsCommand>>>();
    page->PopAllCommands(*jsCommands);
    WeakPtr<JsAcePage> weakPage = page;
    WeakPtr<PipelineContext> weakContext = pipeline;
    pipeline->AddPageUpdateTask(
        [weakPage = std::move(weakPage), weakContext = std::move(weakContext), jsCommands] {
            auto jsPage = weakPage.Upgrade();
            auto context = weakContext.Upgrade();
            if (!jsPage || !context) {
                LOGE("Page update failed. page or context is null.");
                return;
            }
            // Flush all JS commands.
            for (const auto& command : *jsCommands) {
                command->Execute(jsPage);
            }
            if (jsPage->GetDomDocument()) {
                jsPage->GetDomDocument()->HandleComponentPostBinding();
            }
            auto accessibilityManager = context->GetAccessibilityManager();
            if (accessibilityManager) {
                accessibilityManager->HandleComponentPostBinding();
            }

            jsPage->ClearShowCommand();
            std::vector<NodeId> dirtyNodes;
            jsPage->PopAllDirtyNodes(dirtyNodes);
            for (auto nodeId : dirtyNodes) {
                auto patchComponent = jsPage->BuildPagePatch(nodeId);
                if (patchComponent) {
                    context->ScheduleUpdate(patchComponent);
                }
            }
        },
        directExecute);
}

void CJPageRouter::OnPrePageChange(const RefPtr<OHOS::Ace::Framework::JsAcePage>& page)
{
    CHECK_NULL_VOID(page);
    auto document = page->GetDomDocument();
    CHECK_NULL_VOID(document);
    auto frontend = frontend_.Upgrade();
    CHECK_NULL_VOID(frontend);
    auto accessManager = frontend->GetAccessibilityManager();
    CHECK_NULL_VOID(accessManager);
    accessManager->SetRootNodeId(document->GetRootNodeId());
}
void CJPageRouter::GetState(int32_t& index, std::string& name, std::string& path, std::string& params) {}
void CJPageRouter::GetStateByIndex(int32_t& index, std::string& name, std::string& path, std::string& params) {}
std::vector<CJPageRouterAbstract::RouterState> CJPageRouter::GetStateByUrl(const std::string& url)
{
    return {};
}
void CJPageRouter::StartPushPageWithCallback(const RouterPageInfo& target, const std::string& params) {}
void CJPageRouter::StartReplacePageWithCallback(const RouterPageInfo& target, const std::string& params) {}
void CJPageRouter::BackCheckAlertIndex(int32_t index, const std::string& params) {}
void CJPageRouter::DisableAlertBeforeBackPage() {}
} // namespace OHOS::Ace::Framework
