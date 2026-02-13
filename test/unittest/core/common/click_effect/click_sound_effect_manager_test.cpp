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

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#define private public
#define protected public
#include "interfaces/inner_api/ace_kit/include/ui/event/click_sound_effect_policy.h"

#include "core/common/click_effect/click_sound_effect_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
class MockClickSoundEffectPolicy : public Kit::ClickSoundEffectPolicy {
public:
    MOCK_METHOD4(InteractiveSoundEffects, int32_t(int32_t type, int32_t index, int32_t abscissa, int32_t ordinate));
    static MockClickSoundEffectPolicy* GetClickSoundEffectPolicyInstance()
    {
        static MockClickSoundEffectPolicy instance;
        return &instance;
    }
};

class ClickSoundEffectManagerTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
    void SetUp()
    {
        OHOS::Ace::ClickSoundEffectManager::GetInstance().UnloadProductPolicy();
    }
    void TearDown() {}
};

/**
 * @tc.name: Close001
 * @tc.desc: Test Close function.
 * @tc.type: FUNC
 */
HWTEST_F(ClickSoundEffectManagerTest, Close001, TestSize.Level1)
{
    OHOS::Ace::ClickSoundEffectManager& manager = OHOS::Ace::ClickSoundEffectManager::GetInstance();
    manager.LoadProductPolicy();
    manager.Close();
    manager.libraryHandle_ = nullptr;
    manager.Close();
    EXPECT_EQ(manager.libraryHandle_, nullptr);
}
} // namespace OHOS::Ace