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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_NAVIGATION_STACK_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_NAVIGATION_STACK_H

#include "gmock/gmock.h"

#define protected public
#define private public
#include "core/components_ng/pattern/navigation/navigation_stack.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_model_ng.h"
#include "test/mock/core/common/mock_container.h"
struct MockReplace {
    int32_t isReplace_ = 0;
};

struct MockNavPathInfo {
    std::string name = "";
    std::string navDestinationId = "undefined";

    explicit MockNavPathInfo(std::string name) : name(std::move(name)) {}
};

using NavigationInterceptionEvent = std::function<void(const OHOS::Ace::RefPtr<OHOS::Ace::NG::NavDestinationContext>,
    const OHOS::Ace::RefPtr<OHOS::Ace::NG::NavDestinationContext>, OHOS::Ace::NG::NavigationOperation, bool)>;
class MockNavigationStack : public OHOS::Ace::NG::NavigationStack {
    DECLARE_ACE_TYPE(MockNavigationStack, NavigationStack);
public:
    void UpdateReplaceValue(int32_t isReplace) const override
    {
        mockReplace_->isReplace_ = isReplace;
    }

    int32_t GetReplaceValue() const override
    {
        return mockReplace_->isReplace_;
    }

    bool GetDisableAnimation() const override
    {
        return false;
    }

    void SetOnStateChangedCallback(std::function<void()> callback) override
    {
        onStateChangedCallback_ = callback;
    }

    std::function<void()> GetOnStateChangedCallback() const
    {
        return onStateChangedCallback_;
    }

    void SetInterceptionBeforeCallback(NavigationInterceptionEvent callback)
    {
        beforeCallback_ = callback;
    }

    void SetInterceptionAfterCallback(NavigationInterceptionEvent afterCallback)
    {
        afterCallback_ = afterCallback;
    }

    void SetInterceptionModeCallback(std::function<void(OHOS::Ace::NG::NavigationMode)> modeCallback)
    {
        modeCallback_ = modeCallback;
    }

    void FireNavigationModeChange(OHOS::Ace::NG::NavigationMode mode) override
    {
        if (modeCallback_) {
            modeCallback_(mode);
        }
    }

    void FireNavigationInterception(bool isBefore, const OHOS::Ace::RefPtr<OHOS::Ace::NG::NavDestinationContext>& from,
        const OHOS::Ace::RefPtr<OHOS::Ace::NG::NavDestinationContext>& to, OHOS::Ace::NG::NavigationOperation operation,
        bool isAnimated) override
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

    MOCK_METHOD1(OnAttachToParent, void(OHOS::Ace::RefPtr<OHOS::Ace::NG::NavigationStack>));
    MOCK_METHOD0(OnDetachFromParent, void());

    OHOS::Ace::RefPtr<OHOS::Ace::NG::UINode> CreateNodeByIndex(int32_t index,
        const OHOS::Ace::WeakPtr<OHOS::Ace::NG::UINode>& customNode) override
    {
        auto* stack = OHOS::Ace::NG::ViewStackProcessor::GetInstance();
        // navDestination node
        int32_t nodeId = stack->ClaimNodeId();
        auto frameNode = OHOS::Ace::NG::NavDestinationGroupNode::GetOrCreateGroupNode(
            OHOS::Ace::V2::NAVDESTINATION_VIEW_ETS_TAG, nodeId, []() {
                return OHOS::Ace::AceType::MakeRefPtr<OHOS::Ace::NG::NavDestinationPattern>();
            });
        EXPECT_NE(frameNode, nullptr);
        auto name = mockPathArray_[index].name;
        auto container = OHOS::Ace::MockContainer::Current();
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
        auto pattern = OHOS::Ace::AceType::DynamicCast<OHOS::Ace::NG::NavDestinationPattern>(frameNode->GetPattern());
        EXPECT_NE(pattern, nullptr);
        pattern->SetName(name);
        return frameNode;
    }

    void Push(const std::string& name, int32_t index) override
    {
        mockPathArray_.push_back(MockNavPathInfo(name));
    }

    void Push(const std::string& name, const OHOS::Ace::RefPtr<OHOS::Ace::NG::RouteInfo>& routeInfo = nullptr) override
    {
        mockPathArray_.push_back(MockNavPathInfo(name));
    }

    std::vector<std::string> GetAllPathName() override
    {
        std::vector<std::string> pathNames;
        for (int32_t i = 0; i < static_cast<int32_t>(mockPathArray_.size()); i++) {
            pathNames.emplace_back(mockPathArray_[i].name);
        }
        return pathNames;
    }

    std::vector<int32_t> GetAllPathIndex() override
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

    void Clear() override
    {
        OHOS::Ace::NG::NavigationStack::Clear();
        mockPathArray_.clear();
    }

    void Pop() override
    {
        mockPathArray_.pop_back();
    }

    void SetLifecycleIndex(int8_t index)
    {
        lifecycleIndex_ = index;
    }

    int8_t GetLifecycleIndex() const
    {
        return lifecycleIndex_;
    }

    OHOS::Ace::NG::NavPathList& GetPathList()
    {
        return navPathList_;
    }

    void SetDestinationIdToJsStack(int32_t index, const std::string& navDestinationId) override
    {
        if (index < 0 || index >= static_cast<int32_t>(mockPathArray_.size())) {
            return;
        }
        mockPathArray_[index].navDestinationId = navDestinationId;
    }

    std::string GetNavPathId(int32_t index)
    {
        return mockPathArray_[index].navDestinationId;
    }

private:
    int8_t lifecycleIndex_ = 0;
    std::function<void()> onStateChangedCallback_;
    NavigationInterceptionEvent beforeCallback_;
    NavigationInterceptionEvent afterCallback_;
    std::function<void(OHOS::Ace::NG::NavigationMode)> modeCallback_;
    MockReplace *mockReplace_ = new MockReplace();
    std::vector<MockNavPathInfo> mockPathArray_;
};
#endif