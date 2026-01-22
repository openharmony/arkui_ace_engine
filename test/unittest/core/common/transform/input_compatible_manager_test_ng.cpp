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
