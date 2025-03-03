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

#include "bridge/cj_frontend/frontend/cj_page_router_abstract.h"

#include "bridge/cj_frontend/frontend/cj_frontend_abstract.h"

namespace OHOS::Ace {

int32_t CJPageRouterAbstract::GenerateNextPageId()
{
    return ++nextPageId_;
}

bool CJPageRouterAbstract::PopWithExitCheck()
{
    if (GetStackSize() == 1) {
        if (AllowPopLastPage()) {
            return false;
        }
    }
    return Pop();
}

void CJPageRouterAbstract::RunPage(const std::string& url, const std::string& params)
{
    LOGI("router.Push pagePath = %{private}s", url.c_str());
    RouterPageInfo info { url };
    ProcessGuard guard(this);
    LoadPage(GenerateNextPageId(), info, params);
}

void CJPageRouterAbstract::Push(const RouterPageInfo& target, const std::string& params, RouterMode mode)
{
    if (inRouterOpt_) {
        LOGI("in router opt, post push router task");
        auto frontend = frontend_.Upgrade();
        CHECK_NULL_VOID(frontend);
        auto context = frontend->pipelineContextHolder_.Get();
        CHECK_NULL_VOID(context);
        context->PostAsyncEvent(
            [weak = WeakClaim(this), target, params, mode]() {
                auto router = weak.Upgrade();
                CHECK_NULL_VOID(router);
                router->Push(target, params, mode);
            },
            "CJPageRouterAbstract::Push");
        return;
    }
    StartPush(target, params, mode);
}

bool CJPageRouterAbstract::Pop()
{
    if (inRouterOpt_) {
        LOGE("in router opt, post Pop router task failed");
        return false;
    }

    return StartPop();
}

void CJPageRouterAbstract::Replace(const RouterPageInfo& target, const std::string& params, RouterMode mode)
{
    if (inRouterOpt_) {
        LOGI("in router opt, post replace router task");
        auto frontend = frontend_.Upgrade();
        CHECK_NULL_VOID(frontend);
        auto context = frontend->pipelineContextHolder_.Get();
        CHECK_NULL_VOID(context);
        context->PostAsyncEvent(
            [weak = WeakClaim(this), target, params, mode]() {
                auto router = weak.Upgrade();
                CHECK_NULL_VOID(router);
                router->Replace(target, params, mode);
            },
            "CJPageRouterAbstract::Replace");
        return;
    }
    StartReplace(target, params, mode);
}

void CJPageRouterAbstract::BackWithTarget(const RouterPageInfo& target, const std::string& params)
{
    LOGD("router.Back path = %{private}s", target.url.c_str());
    if (inRouterOpt_) {
        LOGI("in router opt, post back router task");
        auto frontend = frontend_.Upgrade();
        CHECK_NULL_VOID(frontend);
        auto context = frontend->pipelineContextHolder_.Get();
        CHECK_NULL_VOID(context);
        context->PostAsyncEvent(
            [weak = WeakClaim(this), target, params]() {
                auto router = weak.Upgrade();
                CHECK_NULL_VOID(router);
                router->BackWithTarget(target, params);
            },
            "CJPageRouterAbstract::BackWithTarget");
        return;
    }
    BackCheckAlert(target, params);
}

void CJPageRouterAbstract::Clear()
{
    if (inRouterOpt_) {
        LOGI("in router opt, post clear router task");
        auto frontend = frontend_.Upgrade();
        CHECK_NULL_VOID(frontend);
        auto context = frontend->pipelineContextHolder_.Get();
        CHECK_NULL_VOID(context);
        context->PostAsyncEvent(
            [weak = WeakClaim(this)]() {
                auto router = weak.Upgrade();
                CHECK_NULL_VOID(router);
                router->Clear();
            },
            "CJPageRouterAbstract::Clear");
        return;
    }
    StartClean();
}

void CJPageRouterAbstract::BackWithIndex(int32_t index, const std::string& params)
{
    if (inRouterOpt_) {
        LOGI("in router opt, post clear router task");
        auto frontend = frontend_.Upgrade();
        CHECK_NULL_VOID(frontend);
        auto context = frontend->pipelineContextHolder_.Get();
        CHECK_NULL_VOID(context);
        context->PostAsyncEvent(
            [weak = WeakClaim(this), index, params]() {
                auto router = weak.Upgrade();
                CHECK_NULL_VOID(router);
                router->BackWithIndex(index, params);
            },
            "CJPageRouterAbstract::BackWithIndex");
        return;
    }
    BackCheckAlertIndex(index, params);
}

void CJPageRouterAbstract::PushPageWithCallback(const RouterPageInfo& target, const std::string& params)
{
    if (inRouterOpt_) {
        LOGI("in router opt, post clear router task");
        auto frontend = frontend_.Upgrade();
        CHECK_NULL_VOID(frontend);
        auto context = frontend->pipelineContextHolder_.Get();
        CHECK_NULL_VOID(context);
        context->PostAsyncEvent(
            [weak = WeakClaim(this), target, params]() {
                auto router = weak.Upgrade();
                CHECK_NULL_VOID(router);
                router->Replace(target, params);
            },
            "CJPageRouterAbstract::PushPageWithCallback");
        return;
    }
    StartPushPageWithCallback(target, params);
}

void CJPageRouterAbstract::ReplacePageWithCallback(const RouterPageInfo& target, const std::string& params)
{
    if (inRouterOpt_) {
        LOGI("in router opt, post clear router task");
        auto frontend = frontend_.Upgrade();
        CHECK_NULL_VOID(frontend);
        auto context = frontend->pipelineContextHolder_.Get();
        CHECK_NULL_VOID(context);
        context->PostAsyncEvent(
            [weak = WeakClaim(this), target, params]() {
                auto router = weak.Upgrade();
                CHECK_NULL_VOID(router);
                router->Replace(target, params);
            },
            "CJPageRouterAbstract::ReplacePageWithCallback");
        return;
    }
    StartReplacePageWithCallback(target, params);
}

RefPtr<NG::FrameNode> CJPageRouterAbstract::GetCurrentPageNode()
{
    return nullptr;
}
} // namespace OHOS::Ace