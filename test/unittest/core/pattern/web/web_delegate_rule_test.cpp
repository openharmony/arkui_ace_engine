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

class WebDelegateRuleTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

protected:
    static constexpr int32_t TEST_PID = 100;
    void ClearSingletonRules();
};

void WebDelegateRuleTest::SetUpTestCase() {}
void WebDelegateRuleTest::TearDownTestCase() {}
void WebDelegateRuleTest::SetUp() {}
void WebDelegateRuleTest::TearDown()
{
    ClearSingletonRules();
}

void WebDelegateRuleTest::ClearSingletonRules()
{
    WebPageSceneManager::GetInstance().UnregisterPageSceneRules(TEST_PID);
}

// Helper: get a copy of a rule set from singleton (safe with copy-on-read API)
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
 * @tc.name: ParseWebRulesFromRuleJson_NormalWebRules
 * @tc.desc: Test parsing ruleJson with valid webRules array via Register.
 * @tc.type: FUNC
 */
HWTEST_F(WebDelegateRuleTest, ParseWebRulesFromRuleJson_NormalWebRules, TestSize.Level0)
{
    std::string ruleJson = R"({
        "ruleSetId": "rs1",
        "sourceConfig": { "web": true },
        "globalConfig": { "includeUnfocusableTextInput": true },
        "webRules": [{
            "ruleId": "r1",
            "sceneType": "TEXT_EDITOR",
            "enabled": true,
            "scope": { "onlyVisible": true },
            "selector": { "nodeTypes": ["input", "textarea"] },
            "condition": { "operator": "COUNT_GTE", "threshold": 2 },
            "report": { "eventName": "onTextInput", "includeNodeIds": true },
            "policy": { "reportOnRegister": false, "minReportIntervalMs": 1000, "deduplicate": true }
        }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(TEST_PID, ruleJson);
    auto rsOpt = GetRuleSetCopy(TEST_PID, "rs1");
    ASSERT_TRUE(rsOpt.has_value());
    auto& rs = *rsOpt;
    EXPECT_EQ(rs.ruleSetId, "rs1");
    EXPECT_TRUE(rs.globalConfig.includeUnfocusableTextInput);
    ASSERT_EQ(rs.rules.size(), 1u);
    EXPECT_EQ(rs.rules[0].ruleId, "r1");
    EXPECT_EQ(rs.rules[0].sceneType, "TEXT_EDITOR");
    EXPECT_TRUE(rs.rules[0].enabled);
    EXPECT_TRUE(rs.rules[0].scope.onlyVisible);
    EXPECT_EQ(rs.rules[0].selector.nodeTypes.size(), 2u);
    EXPECT_EQ(rs.rules[0].condition.conditionOperator, "COUNT_GTE");
    EXPECT_EQ(rs.rules[0].condition.threshold, 2);
    EXPECT_EQ(rs.rules[0].report.eventName, "onTextInput");
    EXPECT_TRUE(rs.rules[0].report.includeNodeIds);
    EXPECT_EQ(rs.rules[0].policy.minReportIntervalMs, 1000);
    EXPECT_TRUE(rs.rules[0].policy.deduplicate);
}

/**
 * @tc.name: ParseWebRulesFromRuleJson_SourceConfigWebFalse
 * @tc.desc: Test that sourceConfig.web=false does not register.
 * @tc.type: FUNC
 */
HWTEST_F(WebDelegateRuleTest, ParseWebRulesFromRuleJson_SourceConfigWebFalse, TestSize.Level0)
{
    std::string ruleJson = R"({
        "ruleSetId": "rs3",
        "sourceConfig": { "web": false },
        "webRules": [{ "ruleId": "r1" }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(TEST_PID, ruleJson);
    auto rsOpt = GetRuleSetCopy(TEST_PID, "rs3");
    EXPECT_FALSE(rsOpt.has_value());
}

/**
 * @tc.name: ParseWebRulesFromRuleJson_EmptyRuleSetId
 * @tc.desc: Test that empty ruleSetId does not register.
 * @tc.type: FUNC
 */
HWTEST_F(WebDelegateRuleTest, ParseWebRulesFromRuleJson_EmptyRuleSetId, TestSize.Level0)
{
    std::string ruleJson = R"({
        "ruleSetId": "",
        "sourceConfig": { "web": true },
        "webRules": [{ "ruleId": "r1" }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(TEST_PID, ruleJson);
    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(TEST_PID);
    EXPECT_FALSE(rules.has_value());
}

/**
 * @tc.name: ParseWebRulesFromRuleJson_EmptyWebRulesNoFallback
 * @tc.desc: Test that empty webRules does not register.
 * @tc.type: FUNC
 */
HWTEST_F(WebDelegateRuleTest, ParseWebRulesFromRuleJson_EmptyWebRulesNoFallback, TestSize.Level0)
{
    std::string ruleJson = R"({
        "ruleSetId": "rs4",
        "sourceConfig": { "web": true }
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(TEST_PID, ruleJson);
    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(TEST_PID);
    EXPECT_FALSE(rules.has_value());
}

/**
 * @tc.name: ParseWebRulesFromRuleJson_PartialRuleFailureSkipped
 * @tc.desc: Test that partial webRules parse failure is skipped, valid rules kept.
 * @tc.type: FUNC
 */
HWTEST_F(WebDelegateRuleTest, ParseWebRulesFromRuleJson_PartialRuleFailureSkipped, TestSize.Level0)
{
    std::string ruleJson = R"({
        "ruleSetId": "rs5",
        "sourceConfig": { "web": true },
        "webRules": [
            { "ruleId": "r_valid", "sceneType": "TEXT_EDITOR", "selector": { "nodeTypes": ["input"] },
                "condition": { "operator": "COUNT_GTE", "threshold": 2 } },
            { "sceneType": "TEXT_EDITOR" }
        ]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(TEST_PID, ruleJson);
    auto rsOpt = GetRuleSetCopy(TEST_PID, "rs5");
    ASSERT_TRUE(rsOpt.has_value());
    ASSERT_EQ(rsOpt->rules.size(), 1u);
    EXPECT_EQ(rsOpt->rules[0].ruleId, "r_valid");
}

/**
 * @tc.name: ParseWebRulesFromRuleJson_TypeAttrRulesParsing
 * @tc.desc: Test ParseTypeAttrRulesFromJson correctly parses typeAttrRules.
 * @tc.type: FUNC
 */
HWTEST_F(WebDelegateRuleTest, ParseWebRulesFromRuleJson_TypeAttrRulesParsing, TestSize.Level0)
{
    std::string ruleJson = R"({
        "ruleSetId": "rs_attr",
        "sourceConfig": { "web": true },
        "webRules": [{
            "ruleId": "r_attr", "sceneType": "TEXT_EDITOR",
            "selector": {
                "nodeTypes": ["input"],
                "typeAttrRules": {
                    "input": [{ "attr": "type", "value": ["text", "email"] }]
                }
            },
            "condition": { "operator": "COUNT_GTE", "threshold": 2 },
            "report": { "eventName": "evt" }
        }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(TEST_PID, ruleJson);
    auto rsOpt = GetRuleSetCopy(TEST_PID, "rs_attr");
    ASSERT_TRUE(rsOpt.has_value());
    ASSERT_EQ(rsOpt->rules.size(), 1u);
    auto& rule = rsOpt->rules[0];
    EXPECT_EQ(rule.ruleId, "r_attr");
    EXPECT_EQ(rule.selector.nodeTypes.size(), 1u);
    EXPECT_EQ(rule.selector.typeAttrRules.size(), 1u);
    ASSERT_EQ(rule.selector.typeAttrRules.count("input"), 1u);
    EXPECT_EQ(rule.selector.typeAttrRules.at("input").size(), 1u);
    EXPECT_EQ(rule.selector.typeAttrRules.at("input")[0].attr, "type");
    EXPECT_EQ(rule.selector.typeAttrRules.at("input")[0].value.size(), 2u);
}

} // namespace OHOS::Ace
