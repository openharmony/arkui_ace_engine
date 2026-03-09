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
#include "test/mock/base/mock_task_executor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
class StorageTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
    void SetUp() override
    {
        StorageProxy::GetInstance()->SetDelegate(nullptr);
        StorageProxy::GetInstance()->SetDistributedDelegate(nullptr);
    }
    void TearDown() override
    {
        StorageProxy::GetInstance()->SetDelegate(nullptr);
        StorageProxy::GetInstance()->SetDistributedDelegate(nullptr);
    }
};

namespace {
class TestStorage final : public Storage {
    DECLARE_ACE_TYPE(TestStorage, Storage);

public:
    explicit TestStorage(std::string getStringReturn) : getStringReturn_(std::move(getStringReturn)) {}
    ~TestStorage() override = default;

    void SetString(const std::string& key, const std::string& value) override
    {
        (void)key;
        (void)value;
    }

    std::string GetString(const std::string& key) override
    {
        (void)key;
        return getStringReturn_;
    }

    void SetDouble(const std::string& key, const double value) override
    {
        (void)key;
        (void)value;
    }

    bool GetDouble(const std::string& key, double& value) override
    {
        (void)key;
        (void)value;
        return false;
    }

    void SetBoolean(const std::string& key, const bool value) override
    {
        (void)key;
        (void)value;
    }

    bool GetBoolean(const std::string& key, bool& value) override
    {
        (void)key;
        (void)value;
        return false;
    }

    void Clear() override {}
    void Delete(const std::string& key) override
    {
        (void)key;
    }

private:
    std::string getStringReturn_;
};

class SpyStorageProxyImpl final : public StorageInterface {
public:
    explicit SpyStorageProxyImpl(std::string getStringReturn) : getStringReturn_(std::move(getStringReturn)) {}
    ~SpyStorageProxyImpl() override = default;

    RefPtr<Storage> GetStorage(int areaMode = AREA_MODE_FOR_MODULE_PATH, bool useStatic = false) const override
    {
        callCount_++;
        lastAreaMode_ = areaMode;
        lastUseStatic_ = useStatic;
        return AceType::MakeRefPtr<TestStorage>(getStringReturn_);
    }

    int32_t GetCallCount() const
    {
        return callCount_;
    }

    int32_t GetLastAreaMode() const
    {
        return lastAreaMode_;
    }

    bool GetLastUseStatic() const
    {
        return lastUseStatic_;
    }

private:
    std::string getStringReturn_;
    mutable int32_t callCount_ = 0;
    mutable int32_t lastAreaMode_ = 0;
    mutable bool lastUseStatic_ = false;
};

class SpyDistributedStorageProxyImpl final : public StorageInterface {
public:
    explicit SpyDistributedStorageProxyImpl(std::string getStringReturn)
        : getStringReturn_(std::move(getStringReturn))
    {}
    ~SpyDistributedStorageProxyImpl() override = default;

    RefPtr<Storage> GetStorage(const std::string& sessionId, std::function<void(const std::string&)>&& notifier,
        const RefPtr<TaskExecutor>& taskExecutor) const override
    {
        callCount_++;
        lastSessionId_ = sessionId;
        lastTaskExecutor_ = taskExecutor;
        notifier("connected");
        return AceType::MakeRefPtr<TestStorage>(getStringReturn_);
    }

    int32_t GetCallCount() const
    {
        return callCount_;
    }

    std::string GetLastSessionId() const
    {
        return lastSessionId_;
    }

    RefPtr<TaskExecutor> GetLastTaskExecutor() const
    {
        return lastTaskExecutor_;
    }

private:
    std::string getStringReturn_;
    mutable int32_t callCount_ = 0;
    mutable std::string lastSessionId_;
    mutable RefPtr<TaskExecutor> lastTaskExecutor_;
};

class DtorCountingStorageProxyImpl final : public StorageInterface {
public:
    DtorCountingStorageProxyImpl(int32_t* dtorCount, std::string getStringReturn)
        : dtorCount_(dtorCount), getStringReturn_(std::move(getStringReturn))
    {}

    ~DtorCountingStorageProxyImpl() override
    {
        if (dtorCount_) {
            (*dtorCount_)++;
        }
    }

    RefPtr<Storage> GetStorage(int areaMode = AREA_MODE_FOR_MODULE_PATH, bool useStatic = false) const override
    {
        (void)areaMode;
        (void)useStatic;
        return AceType::MakeRefPtr<TestStorage>(getStringReturn_);
    }

private:
    int32_t* dtorCount_ = nullptr;
    std::string getStringReturn_;
};

class DtorCountingDistributedStorageProxyImpl final : public StorageInterface {
public:
    DtorCountingDistributedStorageProxyImpl(int32_t* dtorCount, std::string getStringReturn)
        : dtorCount_(dtorCount), getStringReturn_(std::move(getStringReturn))
    {}

    ~DtorCountingDistributedStorageProxyImpl() override
    {
        if (dtorCount_) {
            (*dtorCount_)++;
        }
    }

    RefPtr<Storage> GetStorage(const std::string& sessionId, std::function<void(const std::string&)>&& notifier,
        const RefPtr<TaskExecutor>& taskExecutor) const override
    {
        (void)sessionId;
        (void)notifier;
        (void)taskExecutor;
        return AceType::MakeRefPtr<TestStorage>(getStringReturn_);
    }

private:
    int32_t* dtorCount_ = nullptr;
    std::string getStringReturn_;
};

class NullStorageProxyImpl final : public StorageInterface {
public:
    ~NullStorageProxyImpl() override = default;

    RefPtr<Storage> GetStorage(int areaMode = AREA_MODE_FOR_MODULE_PATH, bool useStatic = false) const override
    {
        (void)areaMode;
        (void)useStatic;
        return nullptr;
    }
};

class NullDistributedStorageProxyImpl final : public StorageInterface {
public:
    ~NullDistributedStorageProxyImpl() override = default;

    RefPtr<Storage> GetStorage(const std::string& sessionId, std::function<void(const std::string&)>&& notifier,
        const RefPtr<TaskExecutor>& taskExecutor) const override
    {
        (void)sessionId;
        (void)notifier;
        (void)taskExecutor;
        return nullptr;
    }
};
} // namespace

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

/**
 * @tc.name: CastToStorageTest006
 * @tc.desc: Test GetStorage forwards parameters.
 * @tc.type: FUNC
 */
HWTEST_F(StorageTest, CastToStorageTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set delegate with spy implementation.
     * @tc.expected: step1. Spy receives default parameters.
     */
    auto spyDelegate = std::make_unique<SpyStorageProxyImpl>("spy");
    auto* spyDelegateRaw = spyDelegate.get();
    StorageProxy::GetInstance()->SetDelegate(std::move(spyDelegate));

    auto storageDefault = StorageProxy::GetInstance()->GetStorage();
    EXPECT_NE(storageDefault, nullptr);
    EXPECT_EQ(storageDefault->GetString("k"), "spy");
    EXPECT_EQ(spyDelegateRaw->GetCallCount(), 1);
    EXPECT_EQ(spyDelegateRaw->GetLastAreaMode(), AREA_MODE_FOR_MODULE_PATH);
    EXPECT_FALSE(spyDelegateRaw->GetLastUseStatic());

    /**
     * @tc.steps: step2. Call GetStorage with non-default parameters.
     * @tc.expected: step2. Spy receives the same parameters.
     */
    auto storageCustom = StorageProxy::GetInstance()->GetStorage(123, true);
    EXPECT_NE(storageCustom, nullptr);
    EXPECT_EQ(storageCustom->GetString("k"), "spy");
    EXPECT_EQ(spyDelegateRaw->GetCallCount(), 2);
    EXPECT_EQ(spyDelegateRaw->GetLastAreaMode(), 123);
    EXPECT_TRUE(spyDelegateRaw->GetLastUseStatic());
}

/**
 * @tc.name: CastToStorageTest007
 * @tc.desc: Test distributed GetStorage forwards sessionId, notifier and taskExecutor.
 * @tc.type: FUNC
 */
HWTEST_F(StorageTest, CastToStorageTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set distributed delegate with spy implementation.
     */
    auto spyDelegate = std::make_unique<SpyDistributedStorageProxyImpl>("distributed");
    auto* spyDelegateRaw = spyDelegate.get();
    StorageProxy::GetInstance()->SetDistributedDelegate(std::move(spyDelegate));

    int32_t notifierCalls = 0;
    std::string lastStatus;
    std::function<void(const std::string&)> notifier = [&notifierCalls, &lastStatus](const std::string& status) {
        notifierCalls++;
        lastStatus = status;
    };

    RefPtr<TaskExecutor> taskExecutor = AceType::MakeRefPtr<MockTaskExecutor>(false);
    std::string sessionId = "sessionId";
    auto storage = StorageProxy::GetInstance()->GetStorage(sessionId, std::move(notifier), taskExecutor);
    EXPECT_NE(storage, nullptr);

    EXPECT_EQ(spyDelegateRaw->GetCallCount(), 1);
    EXPECT_EQ(spyDelegateRaw->GetLastSessionId(), sessionId);
    EXPECT_EQ(spyDelegateRaw->GetLastTaskExecutor(), taskExecutor);

    EXPECT_EQ(notifierCalls, 1);
    EXPECT_EQ(lastStatus, "connected");
}

/**
 * @tc.name: CastToStorageTest008
 * @tc.desc: Test delegate replacement and destruction.
 * @tc.type: FUNC
 */
HWTEST_F(StorageTest, CastToStorageTest008, TestSize.Level1)
{
    int32_t dtorCount = 0;

    StorageProxy::GetInstance()->SetDelegate(std::make_unique<DtorCountingStorageProxyImpl>(&dtorCount, "first"));
    auto storage1 = StorageProxy::GetInstance()->GetStorage();
    EXPECT_NE(storage1, nullptr);
    EXPECT_EQ(storage1->GetString("k"), "first");
    EXPECT_EQ(dtorCount, 0);

    StorageProxy::GetInstance()->SetDelegate(std::make_unique<DtorCountingStorageProxyImpl>(&dtorCount, "second"));
    EXPECT_EQ(dtorCount, 1);
    auto storage2 = StorageProxy::GetInstance()->GetStorage();
    EXPECT_NE(storage2, nullptr);
    EXPECT_EQ(storage2->GetString("k"), "second");

    StorageProxy::GetInstance()->SetDelegate(nullptr);
    EXPECT_EQ(dtorCount, 2);
}

/**
 * @tc.name: CastToStorageTest009
 * @tc.desc: Test distributed delegate replacement and destruction.
 * @tc.type: FUNC
 */
HWTEST_F(StorageTest, CastToStorageTest009, TestSize.Level1)
{
    int32_t dtorCount = 0;
    RefPtr<TaskExecutor> taskExecutor = AceType::MakeRefPtr<MockTaskExecutor>(false);
    std::string sessionId = "sessionId";
    std::function<void(const std::string&)> notifier = [](const std::string& status) { (void)status; };

    StorageProxy::GetInstance()->SetDistributedDelegate(
        std::make_unique<DtorCountingDistributedStorageProxyImpl>(&dtorCount, "first"));
    auto storage1 = StorageProxy::GetInstance()->GetStorage(sessionId, std::move(notifier), taskExecutor);
    EXPECT_NE(storage1, nullptr);
    EXPECT_EQ(storage1->GetString("k"), "first");
    EXPECT_EQ(dtorCount, 0);

    std::function<void(const std::string&)> notifier2 = [](const std::string& status) { (void)status; };
    StorageProxy::GetInstance()->SetDistributedDelegate(
        std::make_unique<DtorCountingDistributedStorageProxyImpl>(&dtorCount, "second"));
    EXPECT_EQ(dtorCount, 1);
    auto storage2 = StorageProxy::GetInstance()->GetStorage(sessionId, std::move(notifier2), taskExecutor);
    EXPECT_NE(storage2, nullptr);
    EXPECT_EQ(storage2->GetString("k"), "second");

    StorageProxy::GetInstance()->SetDistributedDelegate(nullptr);
    EXPECT_EQ(dtorCount, 2);
}

/**
 * @tc.name: CastToStorageTest010
 * @tc.desc: Test non-null delegate returning nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(StorageTest, CastToStorageTest010, TestSize.Level1)
{
    StorageProxy::GetInstance()->SetDelegate(std::make_unique<NullStorageProxyImpl>());
    EXPECT_EQ(StorageProxy::GetInstance()->GetStorage(), nullptr);

    StorageProxy::GetInstance()->SetDistributedDelegate(std::make_unique<NullDistributedStorageProxyImpl>());
    RefPtr<TaskExecutor> taskExecutor = AceType::MakeRefPtr<MockTaskExecutor>(false);
    std::function<void(const std::string&)> notifier = [](const std::string& status) { (void)status; };
    EXPECT_EQ(StorageProxy::GetInstance()->GetStorage("sessionId", std::move(notifier), taskExecutor), nullptr);
}
} // namespace OHOS::Ace
