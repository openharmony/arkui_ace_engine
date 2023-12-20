/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/navigation/inner_navigation_controller.h"

#include "core/components_ng/pattern/navigation/navigation_pattern.h"

namespace OHOS {
namespace Ace {
namespace {
constexpr int32_t INVALID_HANDLE = 0;
}
InnerNavigationController::InnerNavigationController(const WeakPtr<NG::NavigationPattern>& pattern)
    : weakNavigationPattern_(pattern) {}

bool InnerNavigationController::IsNavDestinationInTopStack()
{
    return GetTopHandle() != INVALID_HANDLE;
}

int32_t InnerNavigationController::GetTopHandle()
{
    auto navigationPattern = weakNavigationPattern_.Upgrade();
    CHECK_NULL_RETURN(navigationPattern, INVALID_HANDLE);
    auto navigationStack = navigationPattern->GetNavigationStack();
    CHECK_NULL_RETURN(navigationStack, INVALID_HANDLE);
    auto topNavDestinationNode = navigationStack->GetTopNavPath();
    if (!topNavDestinationNode.has_value()) {
        return INVALID_HANDLE;
    }

    auto navDestinationNode = AceType::DynamicCast<NG::NavDestinationGroupNode>(
        NG::NavigationGroupNode::GetNavDestinationNode(topNavDestinationNode->second));
    CHECK_NULL_RETURN(navDestinationNode, INVALID_HANDLE);
    return topNavDestinationNode->second->GetId();
}

void InnerNavigationController::SetInPIPMode(int32_t handle)
{
    auto navigationPattern = weakNavigationPattern_.Upgrade();
    CHECK_NULL_VOID(navigationPattern);
    auto navigationStack = navigationPattern->GetNavigationStack();
    CHECK_NULL_VOID(navigationStack);
    auto cacheNode = navigationStack->GetFromCacheNode(handle);
    if (cacheNode.has_value()) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "The node has in cache");
        return;
    }

    const auto& navDestinationNodes = navigationStack->GetAllNavDestinationNodes();
    for (size_t i = 0; i != navDestinationNodes.size(); ++i) {
        const auto& childNode = navDestinationNodes[i];
        const auto& uiNode = childNode.second;
        if (uiNode && uiNode->GetId() == handle) {
            auto navDestination = AceType::DynamicCast<NG::NavDestinationGroupNode>(
            NG::NavigationGroupNode::GetNavDestinationNode(uiNode));
            if (navDestination == nullptr) {
                TAG_LOGI(AceLogTag::ACE_NAVIGATION, "The node is not navDestination node");
                return;
            }

            navigationStack->AddCacheNode(childNode.first, uiNode);
            return;
        }
    }
}

void InnerNavigationController::PopInPIP(bool destroy)
{
    auto navigationPattern = weakNavigationPattern_.Upgrade();
    CHECK_NULL_VOID(navigationPattern);
    auto navigationStack = navigationPattern->GetNavigationStack();
    CHECK_NULL_VOID(navigationStack);
    auto topNavDestinationNode = navigationStack->GetTopNavPath();
    if (!topNavDestinationNode.has_value()) {
        return;
    }

    if (destroy && topNavDestinationNode->second) {
        navigationStack->RemoveCacheNode(topNavDestinationNode->second->GetId());
    }

    navigationStack->Pop();
}

void InnerNavigationController::PushInPIP(int32_t handle)
{
    auto navigationPattern = weakNavigationPattern_.Upgrade();
    CHECK_NULL_VOID(navigationPattern);
    auto navigationStack = navigationPattern->GetNavigationStack();
    CHECK_NULL_VOID(navigationStack);
    auto topNavDestinationNode = navigationStack->GetTopNavPath();
    if (topNavDestinationNode.has_value()) {
        if (topNavDestinationNode->second && topNavDestinationNode->second->GetId() == handle) {
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "The node has in top stack");
            return;
        }
    }
    auto cacheNode = navigationStack->GetFromCacheNode(handle);
    if (!cacheNode.has_value()) {
        return;
    }

    navigationStack->ReOrderCache(cacheNode->first, cacheNode->second);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weakStack = AceType::WeakClaim(AceType::RawPtr(navigationStack)), name = cacheNode->first] {
            auto stack = weakStack.Upgrade();
            CHECK_NULL_VOID(stack);
            stack->Push(name);
        }, TaskExecutor::TaskType::UI);
}

void InnerNavigationController::DeletePIPMode(int32_t handle)
{
    auto navigationPattern = weakNavigationPattern_.Upgrade();
    CHECK_NULL_VOID(navigationPattern);
    auto navigationStack = navigationPattern->GetNavigationStack();
    CHECK_NULL_VOID(navigationStack);
    navigationStack->RemoveCacheNode(handle);
}
} // namespace Ace
} // namespace OHOS
