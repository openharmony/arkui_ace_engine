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

bool MockNavigationStack::CreateNodeByIndex(int32_t index, const OHOS::Ace::WeakPtr<OHOS::Ace::NG::UINode>& customNode,
    OHOS::Ace::RefPtr<OHOS::Ace::NG::UINode>& node)
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
        return false;
    }
    if (!navigationRoute->HasLoaded(name)) {
        int32_t res = navigationRoute->LoadPage(name);
        if (res != 0) {
            node = frameNode;
            return true;
        }
    }
    node = frameNode;
    auto pattern = AceType::DynamicCast<NavDestinationPattern>(frameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->SetName(name);
    return true;
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

void MockNavigationStack::SetPathArray(const std::vector<NavdestinationRecoveryInfo>& navdestinationsInfo)
{
    std::vector<MockNavPathInfo> newPathArray;
    for (auto recoveryInfo : navdestinationsInfo) {
        MockNavPathInfo navPathInfo(recoveryInfo.name);
        navPathInfo.mode = recoveryInfo.mode;
        navPathInfo.fromRecovery = true;
        newPathArray.push_back(navPathInfo);
    }
    mockPathArray_ = newPathArray;
}

void MockNavigationStack::SetFromRecovery(int32_t index, bool fromRecovery)
{
    if (!CheckIndexValid(index, mockPathArray_.size())) {
        return;
    }
    mockPathArray_[index].fromRecovery = fromRecovery;
}

bool MockNavigationStack::IsFromRecovery(int32_t index)
{
    if (!CheckIndexValid(index, mockPathArray_.size())) {
        return false;
    }
    return mockPathArray_[index].fromRecovery;
}

bool MockNavigationStack::MockRemoveByNavDestinationId(const std::string& navDestinationId)
{
    for (auto it = mockPathArray_.begin(); it != mockPathArray_.end(); ++ it) {
        if (it->navDestinationId == navDestinationId) {
            mockPathArray_.erase(it);
            return true;
        }
    }
    return false;
}

int32_t MockNavigationStack::MockRemoveByInexes(std::vector<int32_t> indexes)
{
    int32_t deleteCount = 0;
    for (auto it = mockPathArray_.begin(); it != mockPathArray_.end();) {
        if (std::find(indexes.begin(), indexes.end(), it->index) != indexes.end()) {
            mockPathArray_.erase(it);
            deleteCount++;
            continue;
        }
        it++;
    }
    return deleteCount;
}

int32_t MockNavigationStack::MockRemoveByName(const std::string& name)
{
    int32_t deleteCount = 0;
    for (auto it = mockPathArray_.begin(); it != mockPathArray_.end();) {
        if (it->name == name) {
            mockPathArray_.erase(it);
            deleteCount++;
            continue;
        }
        it++;
    }
    return deleteCount;
}

std::string MockNavigationStack::GetNavDestinationIdByIndex(int32_t index)
{
    if (!CheckIndexValid(index, mockPathArray_.size())) {
        return "";
    }
    return mockPathArray_[index].navDestinationId;
}

int32_t MockNavigationStack::MockPopToName(const std::string& name)
{
    int32_t candidateIndex = -1;
    for (int32_t index = 0; index < static_cast<int32_t>(mockPathArray_.size()); ++index) {
        if (mockPathArray_[index].name == name) {
            candidateIndex = index;
            break;
        }
    }
    if (candidateIndex != -1) {
        auto preStackSize = Size();
        for (int32_t index = candidateIndex + 1; index < preStackSize; ++index) {
            mockPathArray_.pop_back();
        }
    }
    return candidateIndex;
}

void MockNavigationStack::MockPopToIndex(int32_t index)
{
    if (!CheckIndexValid(index, mockPathArray_.size())) {
        return;
    }
    auto preStackSize = Size();
    for (int32_t removeCount = index + 1; removeCount < preStackSize; ++removeCount) {
        mockPathArray_.pop_back();
    }
}

int32_t MockNavigationStack::MockMoveToTop(const std::string& name)
{
    int32_t candidateIndex = -1;
    for (int32_t index = 0; index < static_cast<int32_t>(mockPathArray_.size()); ++index) {
        if (mockPathArray_[index].name == name) {
            candidateIndex = index;
            break;
        }
    }
    if (candidateIndex != -1) {
        auto movedInfo = mockPathArray_[candidateIndex];
        auto it = mockPathArray_.begin();
        std::advance(it, candidateIndex);
        mockPathArray_.erase(it);
        mockPathArray_.push_back(movedInfo);
    }
    return candidateIndex;
}
} // namespace OHOS::Ace::NG