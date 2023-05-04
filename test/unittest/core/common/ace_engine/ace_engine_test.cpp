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

#include <csignal>

#include "gtest/gtest.h"
#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"
#include "core/common/ace_engine.h"
#include "core/common/watch_dog.h"
#include "core/pipeline/pipeline_context.h"
#include "base/test/mock/mock_task_executor.h"
#include "base/memory/referenced.h"
#include "base/memory/ace_type.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
using ::testing::_;

namespace OHOS::Ace {
namespace {
const int32_t CONTAINER_INSTANCE_ID = 777;
RefPtr<MockTaskExecutor> MOCK_TASK_EXECUTOR;

} // namespace
class AceEngineTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() {}
    void TearDown() {}
};
void AceEngineTest::SetUpTestCase()
{
    MockContainer::SetUp();
    MockContainer::Current()->pipelineContext_ = nullptr;
    MOCK_TASK_EXECUTOR = AceType::MakeRefPtr<MockTaskExecutor>();
}
void AceEngineTest::TearDownTestCase()
{
    MockContainer::TearDown();
}

HWTEST_F(AceEngineTest, AddContainer01, TestSize.Level1)
{
    AceEngine& aceEngine = AceEngine::Get();

    aceEngine.AddContainer(CONTAINER_INSTANCE_ID, MockContainer::container_);
    EXPECT_TRUE(aceEngine.GetContainer(CONTAINER_INSTANCE_ID) != nullptr);
    aceEngine.RemoveContainer(CONTAINER_INSTANCE_ID);
    EXPECT_TRUE(aceEngine.GetContainer(CONTAINER_INSTANCE_ID) == nullptr);
}

HWTEST_F(AceEngineTest, InitJsDumpHeadSignal01, TestSize.Level1)
{
    AceEngine& aceEngine = AceEngine::Get();

    aceEngine.AddContainer(CONTAINER_INSTANCE_ID, MockContainer::container_);
    EXPECT_CALL(*(MockContainer::container_), DumpHeapSnapshot(_))
        .Times(2);
    AceEngine::InitJsDumpHeadSignal();
    raise(39);
    raise(40);
}

HWTEST_F(AceEngineTest, TriggerGarbageCollection01, TestSize.Level1)
{
    AceEngine& aceEngine = AceEngine::Get();
    aceEngine.AddContainer(CONTAINER_INSTANCE_ID, MockContainer::container_);
    
    EXPECT_CALL(*(MockContainer::container_), GetTaskExecutor())
        .Times(1)
        .WillRepeatedly(Return(MOCK_TASK_EXECUTOR));
    EXPECT_CALL(*(MockContainer::container_), TriggerGarbageCollection())
        .Times(1);
    aceEngine.TriggerGarbageCollection();
}

} // namespace OHOS::Ace
