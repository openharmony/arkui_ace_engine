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

#include <gtest/gtest.h>

#define private public
#define protected public
#include "ace_form_ability.h"
#undef private
#undef protected

using namespace testing::ext;
using namespace OHOS::AAFwk;
namespace OHOS::Ace {
class AceFormAbilityTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void AceFormAbilityTest::SetUpTestCase() {}

void AceFormAbilityTest::TearDownTestCase() {}

void AceFormAbilityTest::SetUp() {}

void AceFormAbilityTest::TearDown() {}

/**
 * @tc.name: AceFormAbilityTest_001
 * @tc.desc: Verify whether the function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceFormAbilityTest, AceFormAbilityTest_001, TestSize.Level1)
{
    std::unique_ptr<AceFormAbility> formAbility = std::make_unique<AceFormAbility>();
    EXPECT_NE(formAbility, nullptr);
    Want want;
    want.SetParam("testParam", 1);
    formAbility->LoadFormEnv(want);
}

/**
 * @tc.name: AceFormAbilityTest_002
 * @tc.desc: Verify whether the function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceFormAbilityTest, AceFormAbilityTest_002, TestSize.Level1)
{
    std::unique_ptr<AceFormAbility> formAbility = std::make_unique<AceFormAbility>();
    EXPECT_NE(formAbility, nullptr);
    Want want;
    want.SetParam("url", 1);
    formAbility->LoadFormEnv(want);
}

/**
 * @tc.name: AceFormAbilityTest_003
 * @tc.desc: Verify whether the function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceFormAbilityTest, AceFormAbilityTest_003, TestSize.Level1)
{
    std::unique_ptr<AceFormAbility> formAbility = std::make_unique<AceFormAbility>();
    EXPECT_NE(formAbility, nullptr);
    Want want;
    want.SetParam("url", 1);
    formAbility->OnCreate(want);
}

/**
 * @tc.name: AceFormAbilityTest_004
 * @tc.desc: Verify whether the function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceFormAbilityTest, AceFormAbilityTest_004, TestSize.Level1)
{
    std::unique_ptr<AceFormAbility> formAbility = std::make_unique<AceFormAbility>();
    EXPECT_NE(formAbility, nullptr);
    formAbility->OnDelete(1);
}


/**
 * @tc.name: AceFormAbilityTest_005
 * @tc.desc: Verify whether the function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceFormAbilityTest, AceFormAbilityTest_005, TestSize.Level1)
{
    std::unique_ptr<AceFormAbility> formAbility = std::make_unique<AceFormAbility>();
    EXPECT_NE(formAbility, nullptr);
    std::string message = "formID";
    formAbility->OnTriggerEvent(1, message);
}

/**
 * @tc.name: AceFormAbilityTest_006
 * @tc.desc: Verify whether the function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceFormAbilityTest, AceFormAbilityTest_006, TestSize.Level1)
{
    std::unique_ptr<AceFormAbility> formAbility = std::make_unique<AceFormAbility>();
    EXPECT_NE(formAbility, nullptr);
    Want want;
    want.SetParam("url", 1);
    auto state = formAbility->OnAcquireFormState(want);
    EXPECT_TRUE(state == AppExecFwk::FormState::UNKNOWN);
}

/**
 * @tc.name: AceFormAbilityTest_007
 * @tc.desc: Verify whether the function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceFormAbilityTest, AceFormAbilityTest_007, TestSize.Level1)
{
    std::unique_ptr<AceFormAbility> formAbility = std::make_unique<AceFormAbility>();
    EXPECT_NE(formAbility, nullptr);
    Want want;
    want.SetParam("url", 1);
    formAbility->OnUpdate(1);
}

/**
 * @tc.name: AceFormAbilityTest_008
 * @tc.desc: Verify whether the function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceFormAbilityTest, AceFormAbilityTest_008, TestSize.Level1)
{
    std::unique_ptr<AceFormAbility> formAbility = std::make_unique<AceFormAbility>();
    EXPECT_NE(formAbility, nullptr);
    Want want;
    want.SetParam("url", 1);
    formAbility->OnCastTemptoNormal(1);
}

/**
 * @tc.name: AceFormAbilityTest_009
 * @tc.desc: Verify whether the function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceFormAbilityTest, AceFormAbilityTest_009, TestSize.Level1)
{
    std::unique_ptr<AceFormAbility> formAbility = std::make_unique<AceFormAbility>();
    EXPECT_NE(formAbility, nullptr);
    Want want;
    want.SetParam("url", 1);
    std::map<int64_t, int32_t> formEventsMap;
    formAbility->OnVisibilityChanged(formEventsMap);
}

/**
 * @tc.name: AceFormAbilityTest_010
 * @tc.desc: Verify whether the function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceFormAbilityTest, AceFormAbilityTest_010, TestSize.Level1)
{
    std::unique_ptr<AceFormAbility> formAbility = std::make_unique<AceFormAbility>();
    EXPECT_NE(formAbility, nullptr);
    WantParams wantParams;
    formAbility->OnShare(1, wantParams);
}

/**
 * @tc.name: AceFormAbilityTest_011
 * @tc.desc: Verify whether the function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceFormAbilityTest, AceFormAbilityTest_011, TestSize.Level1)
{
    std::unique_ptr<AceFormAbility> formAbility = std::make_unique<AceFormAbility>();
    EXPECT_NE(formAbility, nullptr);
    Want want;
    want.SetParam("url", 1);
    formAbility->OnStart(want);
}

/**
 * @tc.name: AceFormAbilityTest_012
 * @tc.desc: Verify whether the function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceFormAbilityTest, AceFormAbilityTest_012, TestSize.Level1)
{
    std::unique_ptr<AceFormAbility> formAbility = std::make_unique<AceFormAbility>();
    EXPECT_NE(formAbility, nullptr);
    formAbility->OnStop();
}

/**
 * @tc.name: AceFormAbilityTest_013
 * @tc.desc: Verify whether the function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceFormAbilityTest, AceFormAbilityTest_013, TestSize.Level1)
{
    std::unique_ptr<AceFormAbility> formAbility = std::make_unique<AceFormAbility>();
    EXPECT_NE(formAbility, nullptr);
    Want want;
    want.SetParam("url", 1);
    formAbility->OnDisconnect(want);
}
}