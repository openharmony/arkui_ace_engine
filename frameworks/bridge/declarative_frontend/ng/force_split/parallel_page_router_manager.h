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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_NG_PARALLEL_PAGE_ROUTER_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_NG_PARALLEL_PAGE_ROUTER_MANAGER_H

#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/pattern/stage/force_split/parallel_stage_manager.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/ng/page_router_manager.h"

namespace OHOS::Ace::NG {
class ParallelPageRouterManager : public PageRouterManager {
    DECLARE_ACE_TYPE(ParallelPageRouterManager, PageRouterManager);
public:
    ParallelPageRouterManager() = default;
    ~ParallelPageRouterManager() = default;

    int32_t GetLastPageIndex() override;

private:
    void LoadPage(int32_t pageId, const RouterPageInfo& target,
        bool needHideLast = true, bool needTransition = true, bool isPush = false) override;
    RefPtr<FrameNode> LoadPlaceHolderPage();
    RefPtr<ResourceWrapper> CreateResourceWrapper();
    bool DetectPrimaryPage(const RouterPageInfo& target, const RefPtr<FrameNode>& preLastPage);
    bool JudgePrimaryPage(const RouterPageInfo& target);
    bool ShouldDetectPrimaryPage(const RefPtr<PipelineContext>& context, const RefPtr<FrameNode>& preLastPage);
    void RefreshAllPageIndex();
    bool SetOnKeyEvent(const RefPtr<FrameNode> &pageNode);
    bool CheckSecondaryPageNeedClear(bool isPush);
    bool CheckStackSize(const RouterPageInfo& target, bool needClearSecondaryPage);

    ACE_DISALLOW_COPY_AND_MOVE(ParallelPageRouterManager);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_NG_PARALLEL_PAGE_ROUTER_MANAGER_H
