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

#include "mock_navigation_stack.h"

namespace OHOS::Ace::NG {

namespace {
bool CheckIndexValid(int32_t index, size_t maxSize)
{
    return index >= 0 && index < static_cast<int32_t>(maxSize);
}
} // namespace

std::pair<int32_t, std::string> MockNavigationStack::FindInPopArray(const std::string& name)
{
    for (int32_t index = int(mockPopArray_.size()) - 1; index >= 0; --index) {
        auto info = mockPopArray_[index];
        if (info.name == name) {
            auto ret = std::make_pair(info.index, info.navDestinationId);
            auto iter = mockPopArray_.begin();
            std::advance(iter, index);
            mockPopArray_.erase(iter);
            return ret;
        }
    }
    return std::make_pair(-1, UNDEFINED_ID);
}

void MockNavigationStack::FireNavigationInterception(bool isBefore, const RefPtr<NavDestinationContext>& from,
    const RefPtr<NavDestinationContext>& to, NavigationOperation operation, bool isAnimated)
{
    if (isBefore) {
        if (beforeCallback_) {
            beforeCallback_(from, to, operation, isAnimated);
        }
    } else {
        if (afterCallback_) {
            afterCallback_(from, to, operation, isAnimated);
        }
    }
}

RefPtr<UINode> MockNavigationStack::CreateNodeByIndex(int32_t index, const WeakPtr<UINode>& customNode)
{
    auto* stack = ViewStackProcessor::GetInstance();
    // navDestination node
    int32_t nodeId = stack->ClaimNodeId();
    auto frameNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    auto name = mockPathArray_[index].name;
    auto container = MockContainer::Current();
    auto navigationRoute = container->GetNavigationRoute();
    if (!navigationRoute) {
        return nullptr;
    }
    if (!navigationRoute->HasLoaded(name)) {
        int32_t res = navigationRoute->LoadPage(name);
        if (res != 0) {
            return frameNode;
        }
    }
    auto pattern = AceType::DynamicCast<NavDestinationPattern>(frameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->SetName(name);
    return frameNode;
}

void MockNavigationStack::Push(const std::string& name, const RefPtr<RouteInfo>& routeInfo)
{
    MockPushPath(MockNavPathInfo(name));
}

void MockNavigationStack::Push(const std::string& name, int32_t index)
{
    MockPushPath(MockNavPathInfo(name));
}

std::vector<std::string> MockNavigationStack::GetAllPathName()
{
    std::vector<std::string> pathNames;
    for (int32_t i = 0; i < static_cast<int32_t>(mockPathArray_.size()); i++) {
        pathNames.emplace_back(mockPathArray_[i].name);
    }
    return pathNames;
}

std::vector<int32_t> MockNavigationStack::GetAllPathIndex()
{
    if (mockPathArray_.empty()) {
        return {};
    }
    std::vector<int32_t> pathIndex;
    for (int32_t i = 0; i < static_cast<int32_t>(mockPathArray_.size()); i++) {
        pathIndex.emplace_back(i);
    }
    return pathIndex;
}

void MockNavigationStack::Clear()
{
    NavigationStack::Clear();
    mockPathArray_.clear();
}

void MockNavigationStack::Pop()
{
    mockPopArray_.emplace_back(mockPathArray_.back());
    mockPathArray_.pop_back();
}

void MockNavigationStack::PopToIndex(int32_t index)
{
    auto iter = mockPathArray_.begin();
    std::advance(iter, index + 1);
    mockPathArray_.erase(iter, mockPathArray_.end());
}

void MockNavigationStack::InitNavPathIndex(const std::vector<std::string>& pathNames)
{
    mockPopArray_.clear();
    for (size_t index = 0; index < mockPathArray_.size() && index < pathNames.size(); index++) {
        if (pathNames[index] == mockPathArray_[index].name && GetReplaceValue() != 1) {
            mockPathArray_[index].index = index;
        }
    }
}

void MockNavigationStack::SetDestinationIdToJsStack(int32_t index, const std::string& navDestinationId)
{
    if (index < 0 || index >= static_cast<int32_t>(mockPathArray_.size())) {
        return;
    }
    mockPathArray_[index].navDestinationId = navDestinationId;
}

void MockNavigationStack::MockPushPath(MockNavPathInfo info, bool animated, LaunchMode launchmode)
{
    if (launchmode == LaunchMode::NEW_INSTANCE) {
        info.needBuildNewInstance = true;
    }
    auto indexAndId = FindInPopArray(info.name);
    if (indexAndId.first != -1 && indexAndId.second != UNDEFINED_ID) {
        info.index = indexAndId.first;
        info.navDestinationId = indexAndId.second;
    }
    animated_ = animated;
    mockPathArray_.push_back(info);
}

bool MockNavigationStack::NeedBuildNewInstance(int32_t index)
{
    if (!CheckIndexValid(index, mockPathArray_.size())) {
        return false;
    }
    return mockPathArray_[index].needBuildNewInstance;
}

void MockNavigationStack::SetNeedBuildNewInstance(int32_t index, bool need)
{
    if (!CheckIndexValid(index, mockPathArray_.size())) {
        return;
    }
    mockPathArray_[index].needBuildNewInstance = need;
}
} // namespace OHOS::Ace::NG