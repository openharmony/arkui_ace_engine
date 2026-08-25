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

#include "gtest/gtest.h"

#include "base/json/json_util.h"
#include "core/components/web/resource/web_delegate.h"
#include "core/components/web/resource/web_page_scene_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

class PageSceneReportTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

protected:
    static constexpr int32_t TEST_PID = 100;
    static constexpr int32_t TEST_WEB_ID = 1;
    void ClearSingletonRules();
};

void PageSceneReportTest::SetUpTestCase() {}
void PageSceneReportTest::TearDownTestCase() {}
void PageSceneReportTest::SetUp() {}
void PageSceneReportTest::TearDown()
{
    ClearSingletonRules();
}

void PageSceneReportTest::ClearSingletonRules()
{
    WebPageSceneManager::GetInstance().UnregisterPageSceneRules(TEST_PID);
}

/**
 * @tc.name: StateMachine_FullLifecycle
 * @tc.desc: Test TEXT_EDITOR state machine: IDLE->TRIGGERED->EXIT.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneReportTest, StateMachine_FullLifecycle, TestSize.Level0)
{
    std::string ruleJson = R"({
        "ruleSetId": "rs1",
        "sourceConfig": { "web": true },
        "webRules": [{ "ruleId": "r1", "sceneType": "TEXT_EDITOR", "enabled": true,
            "selector": { "nodeTypes": ["input"] },
            "condition": { "operator": "COUNT_GTE", "threshold": 2 },
            "report": { "eventName": "onTextInput", "includeNodeIds": true } }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(TEST_PID, ruleJson);

    // IDLE -> TRIGGERED (matched=true)
    WebPageSceneManager::GetInstance().UpdateRuleState(
        TEST_PID, TEST_WEB_ID, "r1", true, 2, true, {});
    auto rulesOpt = WebPageSceneManager::GetInstance().GetPageSceneRules(TEST_PID);
    ASSERT_TRUE(rulesOpt.has_value());
    EXPECT_TRUE(rulesOpt->componentRuleStates.at(TEST_WEB_ID).at("r1").textEditorTriggered);

    // TRIGGERED -> EXIT (matched=false with textEditorTriggered=true)
    WebPageSceneManager::GetInstance().UpdateRuleState(
        TEST_PID, TEST_WEB_ID, "r1", false, 0, false, {});
    rulesOpt = WebPageSceneManager::GetInstance().GetPageSceneRules(TEST_PID);
    ASSERT_TRUE(rulesOpt.has_value());
    EXPECT_FALSE(rulesOpt->componentRuleStates.at(TEST_WEB_ID).at("r1").textEditorTriggered);
}

} // namespace OHOS::Ace
