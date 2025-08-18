/*
 * Copyright (c) 2025 iSoftStone Information Technology (Group) Co.,Ltd.
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

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#define private public
#define protected public
#include "interfaces/inner_api/ace_kit/include/ui/event/input_compatible_policy.h"
#include "test/mock/base/mock_system_properties.h"

#include "frameworks/core/common/transform/input_compatible_manager.h"
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
class MockInputCompatiblePolicy : public Kit::InputCompatiblePolicy {
public:
    MOCK_METHOD1(IsInputCompatibleConvertingNeeded, bool(Kit::InputCompatibleSource source));
    static MockInputCompatiblePolicy* GetInputCompatiblePolicyInstance()
    {
        static MockInputCompatiblePolicy instance;
        return &instance;
    }
};

extern "C" {
void* dlopen(const char* filename, int flag)
{
    return reinterpret_cast<void*>(1);
}

void* dlsym(void* handle, const char* symbol)
{
    return reinterpret_cast<void*>(MockInputCompatiblePolicy::GetInputCompatiblePolicyInstance);
}
}

class InputCompatibleManagerTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
    void SetUp()
    {
        OHOS::Ace::InputCompatibleManager::GetInstance().UnloadProductCompatiblePolicy();
        MockSystemProperties::g_isCompatibleInputTransEnabled = false;
        MockSystemProperties::g_isTransformEnabled = false;
    }
    void TearDown() {}
};

/**
 * @tc.name: InputCompatibleManagerTest001
 * @tc.desc: Test LoadProductCompatiblePolicy function.
 * @tc.type: FUNC
 */
HWTEST_F(InputCompatibleManagerTest, LoadProductCompatiblePolicy001, TestSize.Level1)
{
    OHOS::Ace::InputCompatibleManager& manager = OHOS::Ace::InputCompatibleManager::GetInstance();
    manager.LoadProductCompatiblePolicy();
    EXPECT_NE(manager.productPolicy_, nullptr);
    EXPECT_TRUE(manager.transformSoLoaded_);

    manager.libraryHandle_ = nullptr;
    manager.LoadProductCompatiblePolicy();
    EXPECT_NE(manager.libraryHandle_, nullptr);

    manager.productPolicy_ = nullptr;
    manager.LoadProductCompatiblePolicy();
    EXPECT_NE(manager.productPolicy_, nullptr);
}

/**
 * @tc.name: InputCompatibleManagerTest002
 * @tc.desc: Test UnloadProductCompatiblePolicy function.
 * @tc.type: FUNC
 */
HWTEST_F(InputCompatibleManagerTest, UnloadProductCompatiblePolicy001, TestSize.Level1)
{
    OHOS::Ace::InputCompatibleManager& manager = OHOS::Ace::InputCompatibleManager::GetInstance();
    manager.LoadProductCompatiblePolicy();
    EXPECT_NE(manager.productPolicy_, nullptr);
    EXPECT_TRUE(manager.transformSoLoaded_);

    manager.UnloadProductCompatiblePolicy();
    EXPECT_EQ(manager.productPolicy_, nullptr);
    EXPECT_FALSE(manager.transformSoLoaded_);
}

/**
 * @tc.name: InputCompatibleManagerTest003
 * @tc.desc: Test IsCompatibleConvertingEnabledFor function.
 * @tc.type: FUNC
 */
HWTEST_F(InputCompatibleManagerTest, IsCompatibleConvertingEnabledFor001, TestSize.Level1)
{
    OHOS::Ace::InputCompatibleManager& manager = OHOS::Ace::InputCompatibleManager::GetInstance();
    MockInputCompatiblePolicy* instance = MockInputCompatiblePolicy::GetInputCompatiblePolicyInstance();
    EXPECT_CALL(*instance, IsInputCompatibleConvertingNeeded(_)).Times(1).WillOnce(Return(true));
    manager.LoadProductCompatiblePolicy();
    MockSystemProperties::g_isCompatibleInputTransEnabled = true;
    MockSystemProperties::g_isTransformEnabled = true;
    EXPECT_TRUE(manager.IsCompatibleConvertingEnabledFor(Kit::InputCompatibleSource::LEFT_PRESS));
    manager.UnloadProductCompatiblePolicy();
    MockSystemProperties::g_isCompatibleInputTransEnabled = true;
    MockSystemProperties::g_isTransformEnabled = false;
    EXPECT_FALSE(manager.IsCompatibleConvertingEnabledFor(Kit::InputCompatibleSource::SCROLL_AXIS_EVENT));
}

/**
 * @tc.name: InputCompatibleManagerTest004
 * @tc.desc: Test Close function.
 * @tc.type: FUNC
 */
HWTEST_F(InputCompatibleManagerTest, Close001, TestSize.Level1)
{
    OHOS::Ace::InputCompatibleManager& manager = OHOS::Ace::InputCompatibleManager::GetInstance();
    manager.LoadProductCompatiblePolicy();
    manager.Close();
    manager.libraryHandle_ = nullptr;
    manager.Close();
    ASSERT_EQ(manager.libraryHandle_, nullptr);
}
}; // namespace OHOS::Ace
