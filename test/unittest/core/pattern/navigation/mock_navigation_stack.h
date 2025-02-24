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

namespace OHOS::Ace::NG {
struct MockReplace {
    int32_t isReplace_ = 0;
};
constexpr char UNDEFINED_ID[] = "undefined";

class MockNavPathInfo : public NavPathInfo {
    DECLARE_ACE_TYPE(MockNavPathInfo, NavPathInfo)
public:
    MockNavPathInfo() = default;
    explicit MockNavPathInfo(const std::string& name) : NG::NavPathInfo(name) {}
    MockNavPathInfo(const std::string& name, bool isEntry) : NG::NavPathInfo(name, isEntry) {}
    ~MockNavPathInfo() = default;

    void SetOnPop(std::function<void()> onPop)
    {
        onPop_ = onPop;
    }

    std::function<void()> GetOnPop() const
    {
        return onPop_;
    }

    void SetNavDestinationId(const std::string& navDestinationId)
    {
        navDestinationId_ = navDestinationId;
    }

    std::string GetNavDestinationId() const
    {
        return navDestinationId_;
    }

    int32_t index = -1;
    bool needBuildNewInstance = false;
    bool fromRecovery = false;
    int32_t mode = 0; // 0 for standard and 1 for dialog

private:
    std::function<void()> onPop_;
    std::string navDestinationId_ = UNDEFINED_ID;
};

enum LaunchMode {
    STANDARD = 0,
    MOVE_TO_TOP_SINGLETON,
    POP_TO_TOP_SINGLETON,
    NEW_INSTANCE,
};

using NavigationInterceptionEvent = std::function<void(const RefPtr<NavDestinationContext>,
    const RefPtr<NavDestinationContext>, NavigationOperation, bool)>;
class MockNavigationStack : public NavigationStack {
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

    void SetInterceptionModeCallback(std::function<void(NavigationMode)> modeCallback)
    {
        modeCallback_ = modeCallback;
    }

    void FireNavigationModeChange(NavigationMode mode) override
    {
        if (modeCallback_) {
            modeCallback_(mode);
        }
    }

    void SetLifecycleIndex(int8_t index)
    {
        lifecycleIndex_ = index;
    }

    int8_t GetLifecycleIndex() const
    {
        return lifecycleIndex_;
    }

    NavPathList& GetPathList()
    {
        return navPathList_;
    }

    std::string GetNavDestinationId(int32_t index)
    {
        return mockPathArray_[index]->GetNavDestinationId();
    }

    MOCK_METHOD1(OnAttachToParent, void(RefPtr<NavigationStack>));
    MOCK_METHOD0(OnDetachFromParent, void());

    void FireNavigationInterception(bool isBefore, const RefPtr<NavDestinationContext>& from,
        const RefPtr<NavDestinationContext>& to, NavigationOperation operation, bool isAnimated) override;

    bool CreateNodeByIndex(int32_t index, const OHOS::Ace::WeakPtr<OHOS::Ace::NG::UINode>& customNode,
        OHOS::Ace::RefPtr<OHOS::Ace::NG::UINode>& node) override;

    void SetDestinationIdToJsStack(int32_t index, const std::string& navDestinationId) override;

    void InitNavPathIndex(const std::vector<std::string>& pathNames) override;

    bool NeedBuildNewInstance(int32_t index) override;

    void SetNeedBuildNewInstance(int32_t index, bool need) override;

    void SetPathArray(const std::vector<NavdestinationRecoveryInfo>& navdestinationsInfo);

    void SetFromRecovery(int32_t index, bool fromRecovery);

    bool IsFromRecovery(int32_t index);

    std::string GetNavDestinationIdByIndex(int32_t index);

    //  ============================ operation below is for mock NavPathStack in arkTS ============================
    /**
     * @brief simply mock push operation of NavPathStack(@arkTS)
     */
    void Push(const std::string& name, const RefPtr<RouteInfo>& routeInfo = nullptr) override;

    void Push(const std::string& name, int32_t index) override;

    // pushPath(info: NavPathInfo, animated?: boolean): void
    // pushPath(info: NavPathInof, options?: NavigationOptions): void
    void MockPushPath(const RefPtr<MockNavPathInfo>& info, bool animated = true,
        LaunchMode launchmode = LaunchMode::STANDARD);

    bool MockRemoveByNavDestinationId(const std::string& navDestinationId);

    int32_t MockRemoveByInexes(std::vector<int32_t> indexes);

    int32_t MockRemoveByName(const std::string& name);

    int32_t MockPopToName(const std::string& name);

    void MockPopToIndex(int32_t index);

    int32_t MockMoveToTop(const std::string& name);

    void Clear() override;

    void Pop() override;

    void PopToIndex(int32_t index);

    std::pair<int32_t, std::string> FindInPopArray(const std::string& name);

    int32_t Size() const
    {
        return static_cast<int32_t>(mockPathArray_.size());
    }

    std::vector<std::string> GetAllPathName() override;

    std::vector<int32_t> GetAllPathIndex() override;

    void SetIsEntryByIndex(int32_t index, bool isEntry) override;

    // ============================ operation above is for mock NavPathStack in arkTS ============================
private:
    int8_t lifecycleIndex_ = 0;
    std::function<void()> onStateChangedCallback_;
    NavigationInterceptionEvent beforeCallback_;
    NavigationInterceptionEvent afterCallback_;
    std::function<void(NavigationMode)> modeCallback_;
    MockReplace *mockReplace_ = new MockReplace();
    std::vector<RefPtr<MockNavPathInfo>> mockPathArray_;
    std::vector<RefPtr<MockNavPathInfo>> mockPopArray_;
    std::map<int32_t, bool> mockIsEntryMap_;
};
} // namespace NG
#endif