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

#include "base/utils/utils.h"
#include "bridge/common/utils/source_map.h"
#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/ng/entry_page_info.h"
#include "core/common/container.h"
#include "core/common/thread_checker.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void PageRouterManager::RunPage(const std::string& url, const std::string& params)
{
    CHECK_RUN_ON(JS);
    std::string pagePath;
    if (!url.empty()) {
        pagePath = manifestParser_->GetRouter()->GetPagePath(url);
    } else {
        pagePath = manifestParser_->GetRouter()->GetEntry();
    }
    LOGD("router.Push pagePath = %{private}s", pagePath.c_str());
    RouterPageInfo info { url };
    info.path = pagePath;
    LoadPage(GenerateNextPageId(), info, params);
}

void PageRouterManager::Push(const RouterPageInfo& target, const std::string& params)
{
    CHECK_RUN_ON(JS);
    StartPush(target, params);
}

void PageRouterManager::BackWithTarget(const RouterPageInfo& target, const std::string& params)
{
    LOGD("router.Back path = %{private}s", target.url.c_str());
    BackCheckAlert(target, params);
}

bool PageRouterManager::Pop()
{
    CHECK_RUN_ON(JS);
    if (pageRouterStack_.size() <= 1) {
        // the last page.
        return false;
    }
    if (OnPopPage()) {
        pageRouterStack_.pop();
        return true;
    }
    LOGE("fail to pop page");
    return false;
}

std::string PageRouterManager::GetCurrentPageUrl()
{
    CHECK_RUN_ON(JS);
    if (pageRouterStack_.empty()) {
        LOGW("current page stack is empty");
        return "";
    }
    auto pageNode = pageRouterStack_.top().Upgrade();
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
    auto pageNode = pageRouterStack_.top().Upgrade();
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

void PageRouterManager::StartPush(const RouterPageInfo& target, const std::string& params)
{
    CHECK_RUN_ON(JS);
    if (target.url.empty()) {
        LOGE("router.Push uri is empty");
        return;
    }
    if (!manifestParser_) {
        LOGE("the router manifest parser is null.");
        return;
    }

    std::string pagePath = manifestParser_->GetRouter()->GetPagePath(target.url);
    LOGD("router.Push pagePath = %{private}s", pagePath.c_str());
    if (!pagePath.empty()) {
        RouterPageInfo info { target.url };
        info.path = pagePath;
        LoadPage(GenerateNextPageId(), info, params);
    } else {
        LOGE("[Engine Log] this uri not support in route push.");
    }
}

void PageRouterManager::StartBack(const RouterPageInfo& target, const std::string& params)
{
    if (target.url.empty()) {
        std::string pagePath;
        size_t pageRouteSize = pageRouterStack_.size();
        if (pageRouteSize < 2) {
            LOGE("fail to back page due to page size is only one");
            return;
        }
        // TODO: restore page operation.
        PopPage();
        return;
    }
    // TODO: back to specified page.
}

void PageRouterManager::BackCheckAlert(const RouterPageInfo& target, const std::string& params)
{
    if (pageRouterStack_.empty()) {
        LOGI("page route stack is empty");
        return;
    }
    // TODO: popup back check alert
    StartBack(target, params);
}

void PageRouterManager::LoadPage(
    int32_t pageId, const RouterPageInfo& target, const std::string& params, bool /*isRestore*/)
{
    // TODO: isRestore function.
    CHECK_RUN_ON(JS);
    LOGI("PageRouterManager LoadPage[%{public}d]: %{public}s.", pageId, target.url.c_str());
    auto entryPageInfo = AceType::MakeRefPtr<EntryPageInfo>(pageId, target.url, params);
    entryPageInfo->SetPagePath(target.path);
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(entryPageInfo);
    auto pageNode =
        FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), pagePattern);
    pageRouterStack_.emplace(pageNode);
    auto result = loadJs_(target.path);
    if (!result) {
        LOGE("fail to load page file");
        pageRouterStack_.pop();
        return;
    }
    if (!OnPageReady(pageNode)) {
        LOGE("fail to mount page");
        pageRouterStack_.pop();
        return;
    }
    LOGI("PageRouterManager LoadPage[%{public}d]: %{public}s. success", pageId, target.url.c_str());
}

void PageRouterManager::PopPage()
{
    CHECK_RUN_ON(JS);
    if (pageRouterStack_.empty()) {
        LOGE("page router stack size is illegal");
        return;
    }
    if (!OnPopPage()) {
        LOGE("fail to pop page");
        return;
    }
    pageRouterStack_.pop();
}

bool PageRouterManager::OnPageReady(const RefPtr<FrameNode>& pageNode)
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto context = DynamicCast<NG::PipelineContext>(pipeline);
    auto stageManager = context ? context->GetStageManager() : nullptr;
    if (stageManager) {
        return stageManager->PushPage(pageNode);
    }
    LOGE("fail to push page due to stage manager is nullptr");
    return false;
}

bool PageRouterManager::OnPopPage()
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto context = DynamicCast<NG::PipelineContext>(pipeline);
    auto stageManager = context ? context->GetStageManager() : nullptr;
    if (stageManager) {
        return stageManager->PopPage();
    }
    LOGE("fail to pop page due to stage manager is nullptr");
    return false;
}

} // namespace OHOS::Ace::NG
