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

#ifndef FOUNDATION_ACE_TEST_MOCK_CORE_COMMON_MOCK_CONTAINER_H
#define FOUNDATION_ACE_TEST_MOCK_CORE_COMMON_MOCK_CONTAINER_H

#include "gmock/gmock.h"

#include "core/common/ace_view.h"
#include "core/common/container.h"

namespace OHOS::Ace {
class MockContainer final : public Container {
    DECLARE_ACE_TYPE(MockContainer, Container);

public:
    explicit MockContainer(RefPtr<PipelineBase> pipelineContext = nullptr) : pipelineContext_(pipelineContext) {}

    RefPtr<PipelineBase> GetPipelineContext() const override
    {
        return pipelineContext_;
    }

    RefPtr<TaskExecutor> GetTaskExecutor() const override
    {
        return taskExecutor_;
    }

    RefPtr<DisplayInfo> GetMockDisplayInfo()
    {
        return displayInfo_;
    }

    static void SetUp();
    static void TearDown();
    static RefPtr<MockContainer> Current();
    static RefPtr<MockContainer> GetContainer(int32_t containerId);
    void SetDisplayInfo(RefPtr<DisplayInfo> displayInfo);

    void SetIsFormRender(bool isFormRender) override
    {
        isFormRender_ = isFormRender;
    }

    bool IsFormRender() const override
    {
        return isFormRender_;
    }

    bool IsUIExtensionWindow() override
    {
        return isUIExtensionWindow_;
    }

    void SetIsUIExtensionWindow(bool isUIExtensionWindow)
    {
        isUIExtensionWindow_ = isUIExtensionWindow;
    }

    bool IsScenceBoardWindow() override
    {
        return isScenceBoardWindow_;
    }

    void SetIsScenceBoardWindow(bool isScenceBoardWindow)
    {
        isScenceBoardWindow_ = isScenceBoardWindow;
    }

    bool IsCrossAxisWindow()
    {
        return isCrossAxisWindow_;
    }

    int32_t RequestAutoFill(const RefPtr<NG::FrameNode>& node, AceAutoFillType autoFillType, bool isNewPassWord,
        bool& isPopup, uint32_t& autoFillSessionId, bool isNative = true,
        const std::function<void()>& onFinish = nullptr,
        const std::function<void()>& onUIExtNodeBindingCompleted = nullptr) override;

    ResourceConfiguration GetResourceConfiguration() const override
    {
        return ResourceConfiguration();
    }

    static bool IsNodeInKeyGuardWindow(const RefPtr<NG::FrameNode>& node);

    MOCK_METHOD(void, Initialize, (), (override));
    MOCK_METHOD(void, Destroy, (), (override));
    MOCK_METHOD(int32_t, GetInstanceId, (), (const, override));
    MOCK_METHOD(std::string, GetHostClassName, (), (const, override));

    MOCK_METHOD(RefPtr<Frontend>, GetFrontend, (), (const, override));
    MOCK_METHOD(RefPtr<AssetManager>, GetAssetManager, (), (const, override));
    MOCK_METHOD(RefPtr<PlatformResRegister>, GetPlatformResRegister, (), (const, override));
    MOCK_METHOD(int32_t, GetViewWidth, (), (const, override));
    MOCK_METHOD(int32_t, GetViewHeight, (), (const, override));
    MOCK_METHOD(int32_t, GetViewPosX, (), (const, override));
    MOCK_METHOD(int32_t, GetViewPosY, (), (const, override));
    MOCK_METHOD(uint32_t, GetWindowId, (), (const, override));
    MOCK_METHOD(void*, GetView, (), (const, override));
    MOCK_METHOD(RefPtr<AceView>, GetAceView, (), (const, override));

    MOCK_METHOD(void, DumpHeapSnapshot, (bool isPrivate), (override));
    MOCK_METHOD(void, TriggerGarbageCollection, (), (override));
    MOCK_METHOD(bool, WindowIsShow, (), (const, override));
    static RefPtr<MockContainer> container_;

private:
    RefPtr<TaskExecutor> taskExecutor_;
    RefPtr<PipelineBase> pipelineContext_;
    bool isFormRender_ = false;
    bool isUIExtensionWindow_ = false;
    bool isScenceBoardWindow_ = false;
    bool isCrossAxisWindow_ = false;
    RefPtr<DisplayInfo> displayInfo_ = MakeRefPtr<DisplayInfo>();
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_TEST_MOCK_CORE_COMMON_MOCK_CONTAINER_H
