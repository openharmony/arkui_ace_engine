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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CJ_FRONTEND_CJ_PAGE_ROUTER_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CJ_FRONTEND_CJ_PAGE_ROUTER_H

#include <mutex>

#include "base/utils/base_id.h"
#include "bridge/cj_frontend/frontend/cj_page_router_abstract.h"
#include "bridge/js_frontend/js_ace_page.h"

namespace OHOS::Ace::Framework {
class CJPageRouter final : public CJPageRouterAbstract {
    DECLARE_ACE_TYPE(CJPageRouter, CJPageRouterAbstract)
public:
    explicit CJPageRouter(WeakPtr<CJFrontendAbstract> frontend) : CJPageRouterAbstract(std::move(frontend)) {}

    void OnShowCurrent() override;
    void OnHideCurrent() override;
    bool AllowPopLastPage() override;

    void EnableAlertBeforeBackPage(const std::string& message, std::function<void(int32_t)> callback) override;
    int32_t GetStackSize() const override;
    void GetState(int32_t& index, std::string& name, std::string& path, std::string& params) override;
    void GetStateByIndex(int32_t& index, std::string& name, std::string& path, std::string& params) override;
    std::vector<CJPageRouterAbstract::RouterState> GetStateByUrl(const std::string& url) override;
    void StartPushPageWithCallback(const RouterPageInfo& target, const std::string& params) override;
    void StartReplacePageWithCallback(const RouterPageInfo& target, const std::string& params) override;
    void BackCheckAlertIndex(int32_t index, const std::string& params) override;
    void DisableAlertBeforeBackPage() override;
    std::string GetParams() const override;
    std::string GetCurrentPageUrl() override;
    RefPtr<JsAcePage> GetLoadingPage()
    {
        return loadingPage_;
    }
    void FlushReload() override
    {
        LOGE("not support in old pipeline");
    }

protected:
    void StartPush(const RouterPageInfo& target, const std::string& params, RouterMode mode) override;
    bool StartPop() override;
    void StartReplace(const RouterPageInfo& target, const std::string& params, RouterMode mode) override;
    void BackCheckAlert(const RouterPageInfo& target, const std::string& params) override;
    void StartClean() override;
    void LoadPage(int32_t pageId, const RouterPageInfo& target, const std::string& params, bool isRestore = false,
        bool needHideLast = true, bool needTransition = true) override;
    void PopPage(const std::string& params, bool needShowNext, bool needTransition) override;
    void PopPageToIndex(int32_t index, const std::string& params, bool needShowNext, bool needTransition) override;

    void FlushPage(const RefPtr<JsAcePage>& page, const std::string& url);
    void OnPageReady(const RefPtr<JsAcePage>& page, const std::string& url, bool needHideLast);
    void OnPageUpdate(const RefPtr<JsAcePage>& page, bool directExecute);
    bool OnPopPage(bool needShowNext, bool needTransition);
    void OnPopSuccess();
    void SetCurrentPage();
    bool OnPopPageToIndex(int32_t index, bool needShowNext, bool needTransition);
    bool OnCleanPageStack();

private:
    void PushLoadingPage(const RefPtr<JsAcePage>& page);
    RefPtr<JsAcePage> GetTopPage() const
    {
        if (pageRouterStack_.empty()) {
            LOGE("fail to get current page node due to page is null");
            return nullptr;
        }
        return pageRouterStack_.back();
    }

    void PostTask(std::function<void()> callback, bool isUI = true);
    void OnPrePageChange(const RefPtr<JsAcePage>&);

    BaseId::IdType lastTransitionListener_ = 0;
    std::list<RefPtr<JsAcePage>> pageRouterStack_;
    RefPtr<JsAcePage> loadingPage_;

    ACE_DISALLOW_COPY_AND_MOVE(CJPageRouter);
};
} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CJ_FRONTEND_CJ_PAGE_ROUTER_H
