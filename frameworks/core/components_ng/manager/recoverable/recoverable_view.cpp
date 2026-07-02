/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/manager/recoverable/recoverable_view.h"

#include "core/components_ng/manager/recoverable/recoverable_manager.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void RecoverableView::GenerateGlobalComponentId(const std::string& customId)
{
    auto hostNode = hostNode_.Upgrade();
    CHECK_NULL_VOID(hostNode);
    auto parent = hostNode->GetParentFrameNode();
    globalComponentId_ = hostNode->GetTag();
    if (!customId.empty()) {
        globalComponentId_ += "-" + customId;
    }
    while (parent) {
        auto pattern = parent->GetPattern();
        if (pattern) {
            auto recoverableView = AceType::DynamicCast<RecoverableView>(pattern);
            if (recoverableView) {
                globalComponentId_ = recoverableView->GetGlobalComponentId() + "-" + globalComponentId_;
                return;
            }
        }
        parent = parent->GetParentFrameNode();
    }
}

bool RecoverableView::IsRecoverableNavDestination(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, false);
    auto tag = node->GetTag();
    if (tag != V2::NAVDESTINATION_VIEW_ETS_TAG) {
        return false;
    }
    auto parent = node->GetParent();
    CHECK_NULL_RETURN(parent, false);
    const auto& parentTag = parent->GetTag();
    // NavDestination in stack or home NavDestination in forceSplit mode.
    if (parentTag == V2::NAVIGATION_CONTENT_ETS_TAG || parentTag == V2::NAVIGATION_FULL_SCREEN_OVERLAY_ETS_TAG ||
        parentTag == V2::PRIMARY_CONTENT_NODE_ETS_TAG) {
        return true;
    }
    if (parentTag != V2::NAVIGATION_VIEW_ETS_TAG) {
        return false;
    }
    auto destNode = AceType::DynamicCast<NavDestinationGroupNode>(node);
    CHECK_NULL_RETURN(destNode, false);
    // related NavDestination in forceSplit mode.
    if (destNode->GetNavDestinationType() == NavDestinationType::RELATED) {
        return true;
    }
    auto parentNav = AceType::DynamicCast<NavigationGroupNode>(parent);
    CHECK_NULL_RETURN(parentNav, false);
    const auto& useHome = parentNav->GetUseHomeDestination();
    const auto& homeDest = parentNav->GetHomeDestinationNode();
    return useHome.has_value() && useHome.value() && node == homeDest;
}

void RecoverableView::RegisterRecoverable(const std::string& customId)
{
    auto hostNode = hostNode_.Upgrade();
    CHECK_NULL_VOID(hostNode);
    auto parent = hostNode->GetParentFrameNode();
    auto isNavigationType = false;
    int32_t pageId = -1;
    std::string globalComponentId = hostNode->GetTag();
    if (!customId.empty()) {
        globalComponentId += "-" + customId;
    }
    bool preRecoverableViewHasFound = false;
    for (auto current = hostNode->GetParentFrameNode(); current; current = current->GetParentFrameNode()) {
        const auto& tag = current->GetTag();
        if (tag == V2::PAGE_ETS_TAG) {
            pageId = current->GetId();
            isNavigationType = false;
            break;
        }
        if (tag == V2::NAVBAR_ETS_TAG) {
            pageId = current->GetId();
            isNavigationType = true;
            break;
        }
        if (IsRecoverableNavDestination(current)) {
            pageId = current->GetId();
            isNavigationType = true;
            break;
        }
        auto pattern = current->GetPattern();
        if (!preRecoverableViewHasFound && pattern) {
            auto recoverableView = AceType::DynamicCast<RecoverableView>(pattern);
            if (recoverableView) {
                preRecoverableViewHasFound = true;
                globalComponentId = recoverableView->GetGlobalComponentId() + "-" + globalComponentId;
            }
        }
    }
    if (pageId == -1) {
        return;
    }
    auto context = hostNode->GetContext();
    CHECK_NULL_VOID(context);
    auto recoverableMgr = context->GetRecoverableManager();
    CHECK_NULL_VOID(recoverableMgr);
    pageId_ = pageId;
    isNavigationType_ = isNavigationType;
    hostNode_ = WeakPtr(hostNode);
    globalComponentId_ = globalComponentId;
    auto saveCallback = [weakView = WeakClaim(this)]() -> std::string {
        auto view = weakView.Upgrade();
        CHECK_NULL_RETURN(view, "");
        std::string data;
        if (view->OnSaveData(data)) {
            return data;
        }
        return "";
    };
    callbackId_ = recoverableMgr->AddRestoreComponent(
        isNavigationType, pageId_, globalComponentId_, std::move(saveCallback));
}

void RecoverableView::UnregisterRecoverable()
{
    if (pageId_ == -1 || callbackId_ == -1) {
        return;
    }
    auto hostNode = hostNode_.Upgrade();
    CHECK_NULL_VOID(hostNode);
    auto context = hostNode->GetContext();
    CHECK_NULL_VOID(context);
    auto recoverableMgr = context->GetRecoverableManager();
    CHECK_NULL_VOID(recoverableMgr);
    recoverableMgr->RemoveRestoreComponent(isNavigationType_, pageId_, callbackId_);
}

bool RecoverableView::GetRestoreInfo(std::string& restoreInfo)
{
    if (pageId_ == -1 || callbackId_ == -1) {
        return false;
    }
    auto hostNode = hostNode_.Upgrade();
    CHECK_NULL_RETURN(hostNode, false);
    auto context = hostNode->GetContext();
    CHECK_NULL_RETURN(context, false);
    auto recoverableMgr = context->GetRecoverableManager();
    CHECK_NULL_RETURN(recoverableMgr, false);
    auto ret = recoverableMgr->GetRestoreByComponent(isNavigationType_, pageId_, globalComponentId_, restoreInfo);
    return ret;
}

} // namespace OHOS::Ace::NG
