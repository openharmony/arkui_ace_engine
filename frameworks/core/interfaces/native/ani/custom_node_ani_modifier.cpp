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

#include "custom_node_ani_modifier.h"
 
#include <memory>
 
#include "base/log/log.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/custom/custom_node_static.h"
#include "core/components_ng/pattern/navigation/navigation_stack.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/interfaces/native/implementation/nav_path_stack_peer_impl.h"
#include "core/interfaces/native/implementation/navigation_context.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

ani_long ConstructCustomNode(ani_int id, ArkUICustomNodeInfo&& customNodeInfo)
{
    std::string key = NG::ViewStackProcessor::GetInstance()->ProcessViewId(std::to_string(id));
    auto customNode = NG::CustomNode::CreateCustomNode(id, key);
    customNode->IncRefCount();

    customNode->SetOnPageShowFunc(std::move(customNodeInfo.onPageShowFunc));
    customNode->SetOnPageHideFunc(std::move(customNodeInfo.onPageHideFunc));
    customNode->SetOnBackPressedFunc(std::move(customNodeInfo.onBackPressedFunc));
    customNode->SetPageTransitionFunc(std::move(customNodeInfo.pageTransitionFunc));
    customNode->SetOnCleanupFunc(std::move(customNodeInfo.onCleanupFunc));
    customNode->SetOnDumpInspectorFunc(std::move(customNodeInfo.onDumpInspectorFunc));
    customNode->SetSetActiveFunc(std::move(customNodeInfo.setActiveFunc));

    if (customNode) {
        return reinterpret_cast<ani_long>(AceType::RawPtr(customNode));
    }
    return 0;
}

void RequestFrame()
{
    auto context = NG::PipelineContext::GetCurrentContextSafely();
    if (context == nullptr) {
        TAG_LOGE(AceLogTag::ACE_STATE_MGMT, "RequestFrame-ani can not get current context.");
        return;
    }
    context->RequestFrame();
}

RefPtr<UINode> GetTargetNode(const RefPtr<AceType>& node, const std::string& tag, bool isInner, bool needCheckParent)
{
    // needChcekParent flag is intended to maintain the original logic unchanged, when tag is
    // V2::NAVDESTINATION_VIEW_ETS_TAG.
    auto current = AceType::DynamicCast<UINode>(node);
    while (current) {
        if (current->GetTag() == tag) {
            if (!needCheckParent) {
                break;
            }
            if (current->GetParent() && current->GetParent()->GetTag() == V2::NAVIGATION_CONTENT_ETS_TAG) {
                break;
            }
        }
        current = isInner ? current->GetFirstChild() : current->GetParent();
    }
    return current;
}

void QueryNavigationInfo(ani_long node, ArkUINavigationInfo& info)
{
    auto customNode = reinterpret_cast<CustomNode*>(node);
    CHECK_NULL_VOID(customNode);
    auto pipeline = customNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto navigationMgr = pipeline->GetNavigationManager();
    CHECK_NULL_VOID(navigationMgr);
    auto result = navigationMgr->GetNavigationInfo(AceType::Claim(customNode));
    CHECK_NULL_VOID(result);
    auto stack = result->pathStack.Upgrade();
    CHECK_NULL_VOID(stack);
    NavPathStackPeer* ptr = new NavPathStackPeer(stack);

    info.navigationId = result->navigationId;
    info.navPathStack = reinterpret_cast<ani_ref>(ptr);
    return;
}

void QueryRouterPageInfo(ani_long node, ArkUIRouterPageInfo& info)
{
    auto customNode = reinterpret_cast<CustomNode*>(node);
    CHECK_NULL_VOID(customNode);
    
    auto curNode = GetTargetNode(AceType::Claim(customNode), V2::PAGE_ETS_TAG, false, false);
    auto pageNode = AceType::DynamicCast<FrameNode>(curNode);
    CHECK_NULL_VOID(pageNode);
    auto pattern = pageNode->GetPattern<PagePattern>();
    CHECK_NULL_VOID(pattern);
    auto pageInfo = pattern->GetPageInfo();

    info.index = pageInfo->GetPageIndex();
    info.name = pageInfo->GetPageUrl();
    info.pageId = std::to_string(pageInfo->GetPageId());
    info.path = pageInfo->GetPagePath();
    info.state = static_cast<ani_size>(pattern->GetPageState());
    return;
}

bool QueryRouterPageInfo1(ArkUI_Int32 uniqueId, ArkUIRouterPageInfo& info)
{
    auto nodePtr =  AceType::DynamicCast<NG::UINode>(OHOS::Ace::ElementRegister::GetInstance()->GetNodeById(uniqueId));
    auto routerPageResult = OHOS::Ace::NG::UIObserverHandler::GetInstance().GetRouterPageState(nodePtr);
    CHECK_NULL_RETURN(routerPageResult, false);
    info.index = routerPageResult->index;
    info.name = routerPageResult->name;
    info.path = routerPageResult->path;
    info.state = static_cast<ani_size>(routerPageResult->state);
    info.pageId = routerPageResult->pageId;
    return true;
}

void GetNavDestinationInfo(RefPtr<UINode> node, ArkUINavDestinationInfo& info)
{
    auto nav = AceType::DynamicCast<FrameNode>(node);
    CHECK_NULL_VOID(nav);
    auto pattern = nav->GetPattern<NavDestinationPattern>();
    CHECK_NULL_VOID(pattern);
    auto host = AceType::DynamicCast<NavDestinationGroupNode>(pattern->GetHost());
    CHECK_NULL_VOID(host);
    auto pathInfo = pattern->GetNavPathInfo();
    CHECK_NULL_VOID(pathInfo);
    NavDestinationState state = NavDestinationState::NONE;
    NavDestinationMode mode = host->GetNavDestinationMode();
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        state = pattern->GetNavDestinationState();
        if (state == NavDestinationState::NONE) {
            return;
        }
    } else {
        state = pattern->GetIsOnShow() ? NavDestinationState::ON_SHOWN : NavDestinationState::ON_HIDDEN;
    }

    info.uniqueId = static_cast<ani_double>(host->GetId());
    info.index = static_cast<ani_int>(host->GetIndex());
    info.name = pattern->GetName();
    info.navDestinationId = std::to_string(pattern->GetNavDestinationId());
    info.navigationId = pattern->GetNavigationId();
    info.state = static_cast<ani_size>(state);
    info.mode = static_cast<ani_size>(mode);
    return;
}

void QueryNavDestinationInfo(ani_long node, ArkUINavDestinationInfo& info)
{
    auto customNode = reinterpret_cast<CustomNode*>(node);
    CHECK_NULL_VOID(customNode);
    
    // get navdestination node
    auto current = GetTargetNode(AceType::Claim(customNode), V2::NAVDESTINATION_VIEW_ETS_TAG, false, false);
    CHECK_NULL_VOID(current);

    GetNavDestinationInfo(current, info);
    return;
}

void QueryNavDestinationInfo0(ani_long node, ArkUINavDestinationInfo& info, ani_int isInner)
{
    auto customNode = reinterpret_cast<CustomNode*>(node);
    CHECK_NULL_VOID(customNode);
    auto current =
        GetTargetNode(AceType::Claim(customNode), V2::NAVDESTINATION_VIEW_ETS_TAG, static_cast<bool>(isInner), true);
    CHECK_NULL_VOID(current);

    GetNavDestinationInfo(current, info);
    return;
}

bool QueryNavDestinationInfo1(ArkUI_Int32 uniqueId, ArkUINavDestinationInfo& info)
{
    auto nodePtr = AceType::DynamicCast<NG::UINode>(OHOS::Ace::ElementRegister::GetInstance()->GetNodeById(uniqueId));
    auto navDestinationResult = OHOS::Ace::NG::UIObserverHandler::GetInstance().GetNavigationState(nodePtr);
    CHECK_NULL_RETURN(navDestinationResult, false);
    info.uniqueId = static_cast<ani_double>(navDestinationResult->uniqueId);
    info.index = navDestinationResult->index;
    info.name = navDestinationResult->name;
    info.navDestinationId = navDestinationResult->navDestinationId;
    info.navigationId = navDestinationResult->navigationId;
    info.state = static_cast<ani_size>(navDestinationResult->state);
    info.mode = static_cast<ani_size>(navDestinationResult->mode);
    return true;
}

void OnReuse(ani_long node)
{
    auto customNode = reinterpret_cast<CustomNode*>(node);
    CHECK_NULL_VOID(customNode);
    customNode->OnReuse();
}

void OnRecycle(ani_long node)
{
    auto customNode = reinterpret_cast<CustomNode*>(node);
    CHECK_NULL_VOID(customNode);
    customNode->OnRecycle();
}

const ArkUIAniCustomNodeModifier* GetCustomNodeAniModifier()
{
    static const ArkUIAniCustomNodeModifier impl = {
        .constructCustomNode = OHOS::Ace::NG::ConstructCustomNode,
        .requestFrame = OHOS::Ace::NG::RequestFrame,
        .queryNavigationInfo = OHOS::Ace::NG::QueryNavigationInfo,
        .queryNavDestinationInfo = OHOS::Ace::NG::QueryNavDestinationInfo,
        .queryNavDestinationInfo0 = OHOS::Ace::NG::QueryNavDestinationInfo0,
        .queryRouterPageInfo = OHOS::Ace::NG::QueryRouterPageInfo,
        .queryNavDestinationInfo1 = OHOS::Ace::NG::QueryNavDestinationInfo1,
        .queryRouterPageInfo1 = OHOS::Ace::NG::QueryRouterPageInfo1,
        .onReuse = OHOS::Ace::NG::OnReuse,
        .onRecycle = OHOS::Ace::NG::OnRecycle,
    };
    return &impl;
}

} // namespace OHOS::Ace::NG