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

class PageSceneTriggerTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

protected:
    static constexpr int32_t TEST_PID = 100;
    void ClearSingletonRules();
};

void PageSceneTriggerTest::SetUpTestCase() {}
void PageSceneTriggerTest::TearDownTestCase() {}
void PageSceneTriggerTest::SetUp() {}
void PageSceneTriggerTest::TearDown()
{
    ClearSingletonRules();
}

void PageSceneTriggerTest::ClearSingletonRules()
{
    WebPageSceneManager::GetInstance().UnregisterPageSceneRules(TEST_PID);
}

void RegisterSimpleRule(int32_t pid, const std::string& ruleSetId)
{
    std::string ruleJson = R"({
        "ruleSetId": ")" + ruleSetId + R"(",
        "sourceConfig": { "web": true },
        "webRules": [{ "ruleId": "r1", "sceneType": "TEXT_EDITOR", "enabled": true,
            "selector": { "nodeTypes": ["input"] },
            "condition": { "operator": "COUNT_GTE", "threshold": 2 },
            "report": { "eventName": "evt" } }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(pid, ruleJson);
}

/**
 * @tc.name: SAProcessDeath_ClearsProcess
 * @tc.desc: Test SA process death cleanup: UnregisterPageSceneRules clears the process.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneTriggerTest, SAProcessDeath_ClearsProcess, TestSize.Level0)
{
    RegisterSimpleRule(TEST_PID, "rs1");

    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(TEST_PID);
    ASSERT_TRUE(rules.has_value());

    WebPageSceneManager::GetInstance().UnregisterPageSceneRules(TEST_PID);

    auto rulesAfter = WebPageSceneManager::GetInstance().GetPageSceneRules(TEST_PID);
    EXPECT_FALSE(rulesAfter.has_value());
}

/**
 * @tc.name: RegisterAndUnregister_FullCycle
 * @tc.desc: Test register, verify, unregister, verify empty cycle.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneTriggerTest, RegisterAndUnregister_FullCycle, TestSize.Level0)
{
    auto rulesBefore = WebPageSceneManager::GetInstance().GetPageSceneRules(TEST_PID);
    EXPECT_FALSE(rulesBefore.has_value());

    RegisterSimpleRule(TEST_PID, "rs_cycle");

    auto rulesAfter = WebPageSceneManager::GetInstance().GetPageSceneRules(TEST_PID);
    ASSERT_TRUE(rulesAfter.has_value());
    EXPECT_EQ(rulesAfter->ruleSetId, "rs_cycle");

    WebPageSceneManager::GetInstance().UnregisterPageSceneRules(TEST_PID);

    auto rulesFinal = WebPageSceneManager::GetInstance().GetPageSceneRules(TEST_PID);
    EXPECT_FALSE(rulesFinal.has_value());
}

} // namespace OHOS::Ace
