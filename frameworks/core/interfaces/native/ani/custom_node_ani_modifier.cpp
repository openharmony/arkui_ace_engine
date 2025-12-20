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
#include "core/components_ng/base/observer_handler.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/custom/custom_node_static.h"
#include "core/components_ng/pattern/navigation/navigation_stack.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
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
    customNode->SetDestroyFunction(std::move(customNodeInfo.onCleanupFunc));

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
    auto pageInfo = NG::UIObserverHandler::GetInstance().GetRouterPageState(
        AceType::WeakClaim(customNode).Upgrade());
    CHECK_NULL_VOID(pageInfo);
    info.index = pageInfo->index;
    info.name = pageInfo->name;
    info.path = pageInfo->path;
    info.state = static_cast<ani_size>(pageInfo->state);
    info.pageId = pageInfo->pageId;
    if (pageInfo->size.has_value()) {
        info.width = pageInfo->size.value().Width();
        info.height = pageInfo->size.value().Height();
    }
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
    if (routerPageResult->size.has_value()) {
        info.width = routerPageResult->size.value().Width();
        info.height = routerPageResult->size.value().Height();
    }
    return true;
}

void QueryNavDestinationInfo(ani_long node, ArkUINavDestinationInfo& info)
{
    auto customNode = reinterpret_cast<CustomNode*>(node);
    CHECK_NULL_VOID(customNode);
    auto destInfo = NG::UIObserverHandler::GetInstance().GetNavigationState(
        AceType::WeakClaim(customNode).Upgrade());
    CHECK_NULL_VOID(destInfo);
    info.uniqueId = destInfo->uniqueId;
    info.index = destInfo->index;
    info.name = destInfo->name;
    info.navDestinationId = destInfo->navDestinationId;
    info.navigationId = destInfo->navigationId;
    info.state = static_cast<ani_size>(destInfo->state);
    info.mode = static_cast<ani_size>(destInfo->mode);
    if (destInfo->size.has_value()) {
        info.width = destInfo->size.value().Width();
        info.height = destInfo->size.value().Height();
    }
    return;
}

void QueryNavDestinationInfo0(ani_long node, ArkUINavDestinationInfo& info, ani_int isInner)
{
    auto customNode = reinterpret_cast<CustomNode*>(node);
    CHECK_NULL_VOID(customNode);
    std::shared_ptr<NG::NavDestinationInfo> destInfo = nullptr;
    if (isInner) {
        destInfo = OHOS::Ace::NG::UIObserverHandler::GetInstance()
            .GetNavigationInnerState(AceType::WeakClaim(customNode).Upgrade());
    } else {
        destInfo = OHOS::Ace::NG::UIObserverHandler::GetInstance()
            .GetNavigationOuterState(AceType::WeakClaim(customNode).Upgrade());
    }
    CHECK_NULL_VOID(destInfo);
    info.uniqueId = destInfo->uniqueId;
    info.index = destInfo->index;
    info.name = destInfo->name;
    info.navDestinationId = destInfo->navDestinationId;
    info.navigationId = destInfo->navigationId;
    info.state = static_cast<ani_size>(destInfo->state);
    info.mode = static_cast<ani_size>(destInfo->mode);
    if (destInfo->size.has_value()) {
        info.width = destInfo->size.value().Width();
        info.height = destInfo->size.value().Height();
    }
    return;
}

bool QueryNavDestinationInfo1(ArkUI_Int32 uniqueId, ArkUINavDestinationInfo& info)
{
    auto nodePtr = AceType::DynamicCast<NG::UINode>(OHOS::Ace::ElementRegister::GetInstance()->GetNodeById(uniqueId));
    auto navDestinationResult = OHOS::Ace::NG::UIObserverHandler::GetInstance().GetNavigationState(nodePtr);
    CHECK_NULL_RETURN(navDestinationResult, false);
    info.uniqueId = static_cast<ani_int>(navDestinationResult->uniqueId);
    info.index = navDestinationResult->index;
    info.name = navDestinationResult->name;
    info.navDestinationId = navDestinationResult->navDestinationId;
    info.navigationId = navDestinationResult->navigationId;
    info.state = static_cast<ani_size>(navDestinationResult->state);
    info.mode = static_cast<ani_size>(navDestinationResult->mode);
    if (navDestinationResult->size.has_value()) {
        info.width = navDestinationResult->size.value().Width();
        info.height = navDestinationResult->size.value().Height();
    }
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