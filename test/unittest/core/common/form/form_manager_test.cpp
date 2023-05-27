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

#include "gtest/gtest.h"
#include "core/pipeline/pipeline_base.h"

#define private public
#define protected public
#include "test/unittest/core/common/form/mock_form_utils.h"

#include "core/common/form_manager.h"
#include "core/components/form/sub_container.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
const int64_t CARD_ID = 10000;
} // namespace
class FormManagerTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
    void SetUp() {}
    void TearDown() {}
};

/**
 * @tc.name: AddSubContainer001
 * @tc.desc: Verify the AddSubContainer Interface of FormManager work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(FormManagerTest, AddSubContainer001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a FormManager.
     */
    FormManager formManager;

    /**
     * @tc.steps: step2. Add Sub Container.
     * @tc.expected: step2. Add Sub Container success.
     */
    WeakPtr<PipelineBase> context = WeakPtr<PipelineBase>();
    RefPtr<SubContainer> subContainer = AceType::MakeRefPtr<SubContainer>(context.Upgrade());
    EXPECT_NE(subContainer, nullptr);
    formManager.AddSubContainer(CARD_ID, subContainer);
    EXPECT_NE(formManager.GetSubContainer(CARD_ID), nullptr);
    formManager.RemoveSubContainer(CARD_ID);
    EXPECT_EQ(formManager.GetSubContainer(CARD_ID), nullptr);

    /**
     * @tc.steps: step3. Add Sub Container.
     * @tc.expected: step3. When Sub Container id is exsits ,try to replace it.
     */
    RefPtr<SubContainer> secondSubContainer = AceType::MakeRefPtr<SubContainer>(context.Upgrade());
    EXPECT_NE(secondSubContainer, nullptr);
    formManager.AddSubContainer(CARD_ID, subContainer);
    EXPECT_EQ(formManager.GetSubContainer(CARD_ID), subContainer);
    formManager.AddSubContainer(CARD_ID, secondSubContainer);
    EXPECT_EQ(formManager.GetSubContainer(CARD_ID), secondSubContainer);
}

/**
 * @tc.name: StartAbility001
 * @tc.desc: Verify the StartAbility Interface of PluginManager work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(FormManagerTest, StartAbility001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a FormManager.
     */
    FormManager formManager;

    /**
     * @tc.steps: step2. SetFormUtils.
     * @tc.expected: step2. GetFormUtils equals to formUtils.
     */
    formManager.SetFormUtils(nullptr);
    EXPECT_EQ(formManager.GetFormUtils(), nullptr);
    
    auto formUtils = std::make_shared<MockFormUtils>();
    formManager.SetFormUtils(formUtils);
    EXPECT_EQ(formManager.formUtils_, formUtils);
    EXPECT_EQ(formManager.GetFormUtils(), formUtils);
}
} // namespace OHOS::Ace