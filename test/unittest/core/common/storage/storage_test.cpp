/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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

#include "gtest/gtest.h"
#include "mock_storage.h"

#include "base/utils/utils.h"
#include "core/common/storage/storage_proxy.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
class StorageTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
    void SetUp() {}
    void TearDown() {}
};

/**
 * @tc.name: CastToStorageTest001
 * @tc.desc: Test cast to storage.
 * @tc.type: FUNC
 */
HWTEST_F(StorageTest, CastToStorageTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call the GetInstance first.
     * @tc.expected: step1. the return value is null.
     */
    StorageProxy* firstTestGetInstance;
    firstTestGetInstance = StorageProxy::GetInstance();
    EXPECT_NE(firstTestGetInstance, nullptr);

    /**
     * @tc.steps: step2. call the GetInstance second.
     * @tc.expected: step2. the return value is the same as first.
     */
    StorageProxy* secondTestGetInstance;
    secondTestGetInstance = StorageProxy::GetInstance();
    EXPECT_EQ(secondTestGetInstance, firstTestGetInstance);
}

/**
 * @tc.name: CastToStorageTest002
 * @tc.desc: Test cast to storage.
 * @tc.type: FUNC
 */
HWTEST_F(StorageTest, CastToStorageTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call the SetDelegate with null.
     * @tc.steps: step2. call the GetStorage and take the return value with delegate.
     * @tc.expected: step2. the return stroage is null.
     */
    StorageProxy::GetInstance()->SetDelegate(nullptr);

    RefPtr<Storage> stroage = StorageProxy::GetInstance()->GetStorage();

    EXPECT_EQ(stroage, nullptr);
}

/**
 * @tc.name: CastToStorageTest003
 * @tc.desc: Test cast to storage.
 * @tc.type: FUNC
 */
HWTEST_F(StorageTest, CastToStorageTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call the SetDistributedDelegate with null.
     * @tc.steps: step2. call the GetStorage and take the return value with delegate.
     * @tc.expected: step2. the return stroage is null.
     */
    StorageProxy::GetInstance()->SetDistributedDelegate(nullptr);

    auto notifier = [](const std::string& onlineStatus) { return; };
    RefPtr<TaskExecutor> taskExecutor;
    std::string testSessionId = "testGetStorage";
    RefPtr<Storage> distributedStorage = StorageProxy::GetInstance()->GetStorage(testSessionId, notifier, taskExecutor);

    EXPECT_EQ(distributedStorage, nullptr);
}

/**
 * @tc.name: CastToStorageTest004
 * @tc.desc: Test cast to storage.
 * @tc.type: FUNC
 */
HWTEST_F(StorageTest, CastToStorageTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call the SetDelegate with not null.
     * @tc.steps: step2. call the GetStorage and take the return value with delegate.
     * @tc.expected: step2. the return storage is not null, and the GetString function is ok.
     */
    StorageProxy::GetInstance()->SetDelegate(std::make_unique<MockStorageProxyImpl>());

    RefPtr<Storage> stroage = StorageProxy::GetInstance()->GetStorage();
    EXPECT_NE(stroage, nullptr);

    std::string testString = stroage->GetString("test");
    EXPECT_EQ(testString, FALSE_TEST);
}

/**
 * @tc.name: CastToStorageTest005
 * @tc.desc: Test cast to storage.
 * @tc.type: FUNC
 */
HWTEST_F(StorageTest, CastToStorageTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call the SetDistributedDelegate with not null.
     * @tc.steps: step2. call the GetStorage and take the return value with delegate.
     * @tc.expected: step2. the return storage is not null, and the GetString function is ok.
     */
    StorageProxy::GetInstance()->SetDistributedDelegate(std::make_unique<MockDistributedStorageProxyImpl>());

    auto notifier = [](const std::string& onlineStatus) { return; };
    RefPtr<TaskExecutor> taskExecutor;
    std::string testSessionId = "testGetStorage";
    RefPtr<Storage> distributedStorage = StorageProxy::GetInstance()->GetStorage(testSessionId, notifier, taskExecutor);
    EXPECT_NE(distributedStorage, nullptr);

    std::string testString = distributedStorage->GetString("test");
    EXPECT_EQ(testString, FALSE_TEST);
}
} // namespace OHOS::Ace
