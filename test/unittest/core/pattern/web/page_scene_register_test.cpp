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

class PageSceneRegisterTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

protected:
    static constexpr int32_t TEST_PID = 100;
    void ClearSingletonRules();
};

void PageSceneRegisterTest::SetUpTestCase() {}
void PageSceneRegisterTest::TearDownTestCase() {}
void PageSceneRegisterTest::SetUp() {}
void PageSceneRegisterTest::TearDown()
{
    ClearSingletonRules();
}

void PageSceneRegisterTest::ClearSingletonRules()
{
    WebPageSceneManager::GetInstance().UnregisterPageSceneRules(TEST_PID);
}

static std::optional<WebPageSceneRuleSet> GetRuleSetCopy(int32_t pid, const std::string& ruleSetId)
{
    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(pid);
    if (!rules.has_value()) {
        return std::nullopt;
    }
    if (rules->ruleSetId != ruleSetId) {
        return std::nullopt;
    }
    return rules;
}

/**
 * @tc.name: ExecuteReportOnRegisterMatch_WebEnabled
 * @tc.desc: Test register with sourceConfig.web=true succeeds.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneRegisterTest, ExecuteReportOnRegisterMatch_WebEnabled, TestSize.Level0)
{
    std::string ruleJson = R"({
        "ruleSetId": "rs1",
        "sourceConfig": { "web": true },
        "globalConfig": { "includeUnfocusableTextInput": false },
        "webRules": [{ "ruleId": "r1", "sceneType": "TEXT_EDITOR", "selector": { "nodeTypes": ["input"] },
            "condition": { "operator": "COUNT_GTE", "threshold": 2 },
            "report": { "eventName": "onTextInput" } }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(TEST_PID, ruleJson);
    auto rsOpt = GetRuleSetCopy(TEST_PID, "rs1");
    ASSERT_TRUE(rsOpt.has_value());
    EXPECT_EQ(rsOpt->rules.size(), 1u);
}

/**
 * @tc.name: ExecuteReportOnRegisterMatch_WebDisabled
 * @tc.desc: Test register with sourceConfig.web=false does not add rules.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneRegisterTest, ExecuteReportOnRegisterMatch_WebDisabled, TestSize.Level0)
{
    std::string ruleJson = R"({
        "ruleSetId": "rs2",
        "sourceConfig": { "web": false },
        "webRules": [{ "ruleId": "r1" }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(TEST_PID, ruleJson);
    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(TEST_PID);
    EXPECT_FALSE(rules.has_value());
}

/**
 * @tc.name: ExecuteReportOnRegisterMatch_ReportOnRegister
 * @tc.desc: Test that reportOnRegister=true is parsed and stored correctly.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneRegisterTest, ExecuteReportOnRegisterMatch_ReportOnRegister, TestSize.Level0)
{
    std::string ruleJson = R"({
        "ruleSetId": "rs3",
        "sourceConfig": { "web": true },
        "webRules": [{ "ruleId": "r1", "sceneType": "TEXT_EDITOR", "selector": { "nodeTypes": ["input"] },
            "condition": { "operator": "COUNT_GTE", "threshold": 2 },
            "report": { "eventName": "onTextInput" },
            "policy": { "reportOnRegister": true } }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(TEST_PID, ruleJson);
    auto rsOpt = GetRuleSetCopy(TEST_PID, "rs3");
    ASSERT_TRUE(rsOpt.has_value());
    ASSERT_EQ(rsOpt->rules.size(), 1u);
    EXPECT_TRUE(rsOpt->rules[0].policy.reportOnRegister);
}

/**
 * @tc.name: ExecuteReportOnRegisterMatch_SameRuleSetIdReplace
 * @tc.desc: Test that re-registering same ruleSetId is skipped (singleton dedup).
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneRegisterTest, ExecuteReportOnRegisterMatch_SameRuleSetIdReplace, TestSize.Level0)
{
    std::string ruleJson1 = R"({
        "ruleSetId": "rs4",
        "sourceConfig": { "web": true },
        "webRules": [{ "ruleId": "r1", "sceneType": "TEXT_EDITOR", "selector": { "nodeTypes": ["input"] },
            "condition": { "operator": "COUNT_GTE", "threshold": 2 },
            "report": { "eventName": "evt1" } }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(TEST_PID, ruleJson1);
    auto rsOpt = GetRuleSetCopy(TEST_PID, "rs4");
    ASSERT_TRUE(rsOpt.has_value());
    WebPageSceneManager::GetInstance().UpdateRuleState(
        TEST_PID, 1, "r1", true, 1, true, {});

    std::string ruleJson2 = R"({
        "ruleSetId": "rs4",
        "sourceConfig": { "web": true },
        "webRules": [{ "ruleId": "r1", "sceneType": "TEXT_EDITOR", "selector": { "nodeTypes": ["textarea"] },
            "condition": { "operator": "COUNT_GTE", "threshold": 3 },
            "report": { "eventName": "evt2" } }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(TEST_PID, ruleJson2);

    // Singleton skips duplicate ruleSetId — original state and rules unchanged
    rsOpt = GetRuleSetCopy(TEST_PID, "rs4");
    ASSERT_TRUE(rsOpt.has_value());
    ASSERT_EQ(rsOpt->rules.size(), 1u);
    EXPECT_EQ(rsOpt->rules[0].report.eventName, "evt1");
}

/**
 * @tc.name: ExecuteReportOnRegisterMatch_ParseFailureNoSideEffect
 * @tc.desc: Test that parse failure does not modify existing rules.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneRegisterTest, ExecuteReportOnRegisterMatch_ParseFailureNoSideEffect, TestSize.Level0)
{
    std::string validJson = R"({
        "ruleSetId": "rs5",
        "sourceConfig": { "web": true },
        "webRules": [{ "ruleId": "r1", "sceneType": "TEXT_EDITOR", "selector": { "nodeTypes": ["input"] },
            "condition": { "operator": "COUNT_GTE", "threshold": 2 },
            "report": { "eventName": "evt" } }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(TEST_PID, validJson);
    ASSERT_TRUE(GetRuleSetCopy(TEST_PID, "rs5").has_value());

    std::string invalidJson = "{ invalid }";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(TEST_PID, invalidJson);
    // Original rules unchanged
    ASSERT_TRUE(GetRuleSetCopy(TEST_PID, "rs5").has_value());
}

} // namespace OHOS::Ace
