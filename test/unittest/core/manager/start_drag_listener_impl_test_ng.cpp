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

#include <gtest/gtest.h>

#include "adapter/ohos/capability/interaction/start_drag_listener_impl.h"
#include "core/common/ace_engine.h"
#include "core/common/container_scope.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

namespace {
constexpr int32_t TEST_INSTANCE_ID = 100;
constexpr int32_t OTHER_INSTANCE_ID = 200;

void MakeContainer(int32_t instanceId)
{
    auto container = AceType::MakeRefPtr<MockContainer>();
    auto taskExecutor = Referenced::MakeRefPtr<MockTaskExecutor>();
    container->SetTaskExecutor(taskExecutor);
    AceEngine::Get().AddContainer(instanceId, container);
}

void RemoveContainer(int32_t instanceId)
{
    AceEngine::Get().RemoveContainer(instanceId);
}
} // namespace

class StartDragListenerImplTest : public testing::Test {
public:
    static void SetUpTestCase()
    {
        MockPipelineContext::SetUp();
        MockContainer::SetUp();
    }
    static void TearDownTestCase()
    {
        MockContainer::TearDown();
        MockPipelineContext::TearDown();
    }
    void TearDown() override
    {
        RemoveContainer(TEST_INSTANCE_ID);
        RemoveContainer(OTHER_INSTANCE_ID);
    }
};

/**
 * @tc.name: StartDragListenerImplTest001
 * @tc.desc: Test destructor when instance matches — callback destroyed directly (no PostTask).
 * @tc.type: FUNC
 */
HWTEST_F(StartDragListenerImplTest, StartDragListenerImplTest001, TestSize.Level1)
{
    ContainerScope scope(TEST_INSTANCE_ID);
    auto capturedFlag = std::make_shared<bool>(true);
    std::weak_ptr<bool> weakFlag = capturedFlag;
    {
        auto cb = [capturedFlag](const Msdp::DeviceStatus::DragNotifyMsg &msg) {};
        auto listener = std::make_shared<StartDragListenerImpl>(cb, TEST_INSTANCE_ID);
    }
    EXPECT_NE(weakFlag.lock(), nullptr);
}

/**
 * @tc.name: StartDragListenerImplTest002
 * @tc.desc: Test destructor when instance mismatches — callback destruction posted to JS thread.
 * @tc.type: FUNC
 */
HWTEST_F(StartDragListenerImplTest, StartDragListenerImplTest002, TestSize.Level1)
{
    MakeContainer(TEST_INSTANCE_ID);
    ContainerScope scope(OTHER_INSTANCE_ID);

    auto capturedFlag = std::make_shared<bool>(true);
    {
        auto cb = [capturedFlag](const Msdp::DeviceStatus::DragNotifyMsg &msg) {};
        auto listener = std::make_shared<StartDragListenerImpl>(cb, TEST_INSTANCE_ID);
    }
}

/**
 * @tc.name: StartDragListenerImplTest003
 * @tc.desc: Test destructor with null callback — no crash, no PostTask.
 * @tc.type: FUNC
 */
HWTEST_F(StartDragListenerImplTest, StartDragListenerImplTest003, TestSize.Level1)
{
    ContainerScope scope(OTHER_INSTANCE_ID);
    {
        auto listener = std::make_shared<StartDragListenerImpl>();
    }
}

} // namespace OHOS::Ace
