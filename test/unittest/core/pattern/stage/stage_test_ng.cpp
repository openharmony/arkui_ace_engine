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

#define private public
#define protected public

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_pattern.h"
#include "core/components_ng/pattern/radio/radio_pattern.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"
#include "core/pipeline/base/element_register.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string CHECK_STRING = "check";
const std::string TEST_GROUP_NAME = "testGroup";
const std::string ERROR_GROUP_NAME = "errorGroup";
const std::string FRAME_NODE_TAG = "testFrameNode";
constexpr int32_t RADIO_ID_FIRST = 1;
constexpr int32_t RADIO_ID_SECOND = 2;
constexpr int32_t RADIO_ID_THIRD = 3;
constexpr int32_t CHECK_BOX_ID_FIRST = 4;
constexpr int32_t CHECK_BOX_ID_SECOND = 5;
constexpr int32_t CHECK_BOX_ID_THIRD = 6;
constexpr int32_t CHECK_BOX_ID_FOURTH = 6;
} // namespace

class StageTestNg : public testing::Test {};

/**
 * @tc.name: PageEventHubTest001
 * @tc.desc: Testing Radio Correlation Functions of PageEventHub work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, PageEventHubTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a PageEventHub.
     */
    PageEventHub pageEventHub;
    pageEventHub.UpdateRadioGroupValue(TEST_GROUP_NAME, RADIO_ID_FIRST);

    /**
     * @tc.steps: step2. Add radio to group.
     * @tc.expected: step2. The HasRadioId function of PageEventHub meets expectations .
     */
    pageEventHub.AddRadioToGroup(TEST_GROUP_NAME, RADIO_ID_FIRST);
    EXPECT_TRUE(pageEventHub.HasRadioId(TEST_GROUP_NAME, RADIO_ID_FIRST));
    EXPECT_FALSE(pageEventHub.HasRadioId(ERROR_GROUP_NAME, RADIO_ID_FIRST));

    /**
     * @tc.steps: step3. Add another two radio to group.
     * @tc.expected: step3. The HasRadioId function of PageEventHub meets expectations .
     */
    pageEventHub.AddRadioToGroup(TEST_GROUP_NAME, RADIO_ID_SECOND);
    pageEventHub.AddRadioToGroup(TEST_GROUP_NAME, RADIO_ID_THIRD);

    /**
     * @tc.steps: step4. Create real node and fake node to ElementRegister.
     */
    auto radioPattern = AceType::MakeRefPtr<RadioPattern>();
    auto radioNode = FrameNode::CreateFrameNode(FRAME_NODE_TAG, RADIO_ID_FIRST, radioPattern);
    ElementRegister::GetInstance()->AddReferenced(RADIO_ID_FIRST, radioNode);
    auto checkBoxGroup = AceType::MakeRefPtr<CheckBoxGroupPattern>();
    auto checkBoxGroupNode = FrameNode::CreateFrameNode(FRAME_NODE_TAG, RADIO_ID_SECOND, checkBoxGroup);
    ElementRegister::GetInstance()->AddReferenced(RADIO_ID_SECOND, checkBoxGroupNode);

    /**
     * @tc.steps: step5. UpdateRadioGroupValue.
     */
    pageEventHub.UpdateRadioGroupValue(TEST_GROUP_NAME, RADIO_ID_FIRST);
    pageEventHub.UpdateRadioGroupValue(TEST_GROUP_NAME, RADIO_ID_SECOND);

    /**
     * @tc.steps: step6. RemoveRadioFromGroup.
     * @tc.expected: step6. The radio remove successful .
     */
    pageEventHub.RemoveRadioFromGroup(TEST_GROUP_NAME, RADIO_ID_FIRST);
    EXPECT_FALSE(pageEventHub.HasRadioId(TEST_GROUP_NAME, RADIO_ID_FIRST));
}

/**
 * @tc.name: PageEventHubTest002
 * @tc.desc: Testing CheckBox Correlation Functions of PageEventHub work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, PageEventHubTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a PageEventHub.
     * @tc.expected: step1. The CheckBoxGroupMap size meets expectations .
     */
    PageEventHub pageEventHub;
    EXPECT_EQ(pageEventHub.GetCheckBoxGroupMap().size(), 0);

    /**
     * @tc.steps: step2. build error pattern and add to the group.
     * @tc.expected: step2. The CheckBoxGroupMap[TEST_GROUP_NAME] has the error pattern.
     */
    auto errorPattern = AceType::MakeRefPtr<RadioPattern>();
    auto errorNode = FrameNode::CreateFrameNode(V2::CHECKBOXGROUP_ETS_TAG, CHECK_BOX_ID_FIRST, errorPattern);
    ElementRegister::GetInstance()->AddReferenced(CHECK_BOX_ID_FIRST, errorNode);
    pageEventHub.RemoveCheckBoxFromGroup(TEST_GROUP_NAME, CHECK_BOX_ID_FIRST);
    pageEventHub.AddCheckBoxGroupToGroup(TEST_GROUP_NAME, CHECK_BOX_ID_FIRST);
    EXPECT_EQ(pageEventHub.GetCheckBoxGroupMap()[TEST_GROUP_NAME].size(), 1);

    /**
     * @tc.steps: step3. remove error pattern.
     * @tc.expected: step3. The CheckBoxGroupMap[TEST_GROUP_NAME] has the error pattern.
     */
    ElementRegister::GetInstance()->RemoveItem(CHECK_BOX_ID_FIRST);
    pageEventHub.RemoveCheckBoxFromGroup(TEST_GROUP_NAME, CHECK_BOX_ID_FIRST);
    EXPECT_EQ(pageEventHub.GetCheckBoxGroupMap()[TEST_GROUP_NAME].size(), 0);

    /**
     * @tc.steps: step4. add real checkBoxGroup and add to the group.
     * @tc.expected: step4. add success.
     */
    auto checkBoxGroup = AceType::MakeRefPtr<CheckBoxGroupPattern>();
    auto checkBoxGroupNode = FrameNode::CreateFrameNode(V2::CHECKBOXGROUP_ETS_TAG, CHECK_BOX_ID_THIRD, checkBoxGroup);
    ElementRegister::GetInstance()->AddReferenced(CHECK_BOX_ID_THIRD, checkBoxGroupNode);
    pageEventHub.AddCheckBoxGroupToGroup(TEST_GROUP_NAME, CHECK_BOX_ID_THIRD);
    EXPECT_EQ(pageEventHub.GetCheckBoxGroupMap()[TEST_GROUP_NAME].size(), 1);

    /**
     * @tc.steps: step5. add checkBox to group
     * @tc.expected: step5. add success.
     */
    pageEventHub.AddCheckBoxToGroup(TEST_GROUP_NAME, CHECK_BOX_ID_SECOND);
    EXPECT_EQ(pageEventHub.GetCheckBoxGroupMap()[TEST_GROUP_NAME].size(), 2);

    /**
     * @tc.steps: step6. remove the checkBoxGroup from group.
     * @tc.expected: step6. remove success.
     */
    ElementRegister::GetInstance()->RemoveItem(CHECK_BOX_ID_THIRD);
    pageEventHub.RemoveCheckBoxFromGroup(TEST_GROUP_NAME, CHECK_BOX_ID_THIRD);
    EXPECT_EQ(pageEventHub.GetCheckBoxGroupMap()[TEST_GROUP_NAME].size(), 1);

    /**
     * @tc.steps: step7. add checkBoxGroup to group again.
     * @tc.expected: step7. add success.
     */
    ElementRegister::GetInstance()->AddReferenced(CHECK_BOX_ID_THIRD, checkBoxGroupNode);
    pageEventHub.AddCheckBoxGroupToGroup(TEST_GROUP_NAME, CHECK_BOX_ID_THIRD);
    EXPECT_EQ(pageEventHub.GetCheckBoxGroupMap()[TEST_GROUP_NAME].size(), 2);

    /**
     * @tc.steps: step8. build second checkBoxGroup to group.
     * @tc.expected: step8. add fail.
     */
    auto checkBoxGroup2 = AceType::MakeRefPtr<CheckBoxGroupPattern>();
    auto checkBoxGroupNode2 =
        FrameNode::CreateFrameNode(V2::CHECKBOXGROUP_ETS_TAG, CHECK_BOX_ID_FOURTH, checkBoxGroup2);
    ElementRegister::GetInstance()->AddReferenced(CHECK_BOX_ID_FOURTH, checkBoxGroupNode2);
    pageEventHub.RemoveCheckBoxFromGroup(TEST_GROUP_NAME, CHECK_BOX_ID_FIRST);
    EXPECT_EQ(pageEventHub.GetCheckBoxGroupMap()[TEST_GROUP_NAME].size(), 2);
}
} // namespace OHOS::Ace::NG