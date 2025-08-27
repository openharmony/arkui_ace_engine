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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CJ_FRONTEND_CJ_PAGE_ROUTER_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CJ_FRONTEND_CJ_PAGE_ROUTER_NG_H

#include "bridge/cj_frontend/frontend/cj_page_router_abstract.h"
#include "bridge/declarative_frontend/ng/page_router_manager.h"
#include "core/components_ng/base/frame_node.h"
#include <string>

namespace OHOS::Ace::Framework {
class CJPageRouterNG final : public CJPageRouterAbstract {
    DECLARE_ACE_TYPE(CJPageRouterNG, CJPageRouterAbstract);
public:
    explicit CJPageRouterNG(WeakPtr<CJFrontendAbstract> frontend) : CJPageRouterAbstract(std::move(frontend)) {}

    void EnableAlertBeforeBackPage(const std::string& message, std::function<void(int32_t)> callback) override;

    void ClearAlertCallback(const RefPtr<NG::PageInfo>& pageInfo);

    void DisableAlertBeforeBackPage() override;

    bool PopWithExitCheck() override;

    void FlushReload() override;

    // router operation
    int32_t GetStackSize() const override;
    void GetState(int32_t& index, std::string& name, std::string& path, std::string& params) override;
    std::string GetParams() const override;

    RefPtr<NG::FrameNode> GetCurrentPageNode() override
    {
        if (pageRouterStack_.empty()) {
            LOGE("fail to get current page node due to page is null");
            return nullptr;
        }
        return pageRouterStack_.back().Upgrade();
    }

    std::string GetCurrentPageUrl() override;
    void GetStateByIndex(int32_t& index, std::string& name, std::string& path, std::string& params) override;
    std::vector<CJPageRouterAbstract::RouterState> GetStateByUrl(const std::string& url) override;
    void StartPushPageWithCallback(const RouterPageInfo& target, const std::string& params) override;
    void StartReplacePageWithCallback(const RouterPageInfo& target, const std::string& params) override;
    void BackCheckAlertIndex(int32_t index, const std::string& params) override;

protected:
    std::pair<int32_t, RefPtr<NG::FrameNode>> FindPageInStack(const std::string& url);

    void OnShowCurrent() override;
    void OnHideCurrent() override;
    bool AllowPopLastPage() override;
    void StartPush(const RouterPageInfo& target, const std::string& params, RouterMode mode) override;
    void StartBack(const RouterPageInfo& target, const std::string& params);
    void StartBackIndex(int32_t& index, const std::string& params);
    bool StartPop() override;
    void StartReplace(const RouterPageInfo& target, const std::string& params, RouterMode mode) override;
    void BackCheckAlert(const RouterPageInfo& target, const std::string& params) override;
    void StartClean() override;
    RefPtr<NG::FrameNode> FindPageByIndex(int32_t& index);

    // page operations
    void LoadPage(int32_t pageId, const RouterPageInfo& target, const std::string& params, bool isRestore = false,
        bool needHideLast = true, bool needTransition = true) override;
    void MovePageToFront(int32_t index, const RefPtr<NG::FrameNode>& pageNode, const std::string& params,
        bool needHideLast, bool forceShowCurrent = false, bool needTransition = true);
    void PopPage(const std::string& params, bool needShowNext, bool needTransition) override;
    void PopPageToIndex(int32_t index, const std::string& params, bool needShowNext, bool needTransition) override;

    RefPtr<NG::PipelineContext> GetCurrentPipeline(bool isCardRouter, uint64_t cardId = 0);

    bool OnPageReady(const RefPtr<NG::FrameNode>& pageNode, bool needHideLast, bool needTransition,
        bool isCardRouter = false, uint64_t cardId = 0);
    bool OnPopPage(bool needShowNext, bool needTransition);
    static bool OnPopPageToIndex(int32_t index, bool needShowNext, bool needTransition);
    static bool OnCleanPageStack();
    void UpdateSrcPage();

    std::list<WeakPtr<NG::FrameNode>> pageRouterStack_;

    ACE_DISALLOW_COPY_AND_MOVE(CJPageRouterNG);
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CJ_FRONTEND_CJ_PAGE_ROUTER_NG_H