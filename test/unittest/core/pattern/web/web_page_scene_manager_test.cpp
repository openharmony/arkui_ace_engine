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
#include "core/components/web/resource/web_page_scene_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

class WebPageSceneManagerTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

protected:
    static constexpr int32_t testPid = 100;
    static constexpr int32_t testPidAlt = 200;
    void RegisterValidRuleSet(const std::string& ruleSetId, int32_t pid = testPid);
    void ClearAllRules();
};

void WebPageSceneManagerTest::SetUpTestCase() {}
void WebPageSceneManagerTest::TearDownTestCase() {}
void WebPageSceneManagerTest::SetUp() {}
void WebPageSceneManagerTest::TearDown()
{
    ClearAllRules();
}

void WebPageSceneManagerTest::RegisterValidRuleSet(const std::string& ruleSetId, int32_t pid)
{
    std::string ruleJson = R"({
        "ruleSetId": ")" + ruleSetId + R"(",
        "sourceConfig": { "web": true },
        "globalConfig": { "includeUnfocusableTextInput": false },
        "webRules": [{ "ruleId": "r1", "sceneType": "TEXT_EDITOR", "selector": { "nodeTypes": ["input"] },
            "condition": { "operator": "COUNT_GTE", "threshold": 2 },
            "report": { "eventName": "onTextInput" } }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(pid, ruleJson);
}

void WebPageSceneManagerTest::ClearAllRules()
{
    WebPageSceneManager::GetInstance().UnregisterPageSceneRules(testPid);
    WebPageSceneManager::GetInstance().UnregisterPageSceneRules(testPidAlt);
}

// ===== ParseWebRulesFromRuleJson =====

HWTEST_F(WebPageSceneManagerTest, ParseWebRulesFromRuleJson_NormalWebRules, TestSize.Level0)
{
    std::string ruleJson = R"({
        "ruleSetId": "rs1",
        "sourceConfig": { "web": true },
        "globalConfig": { "includeUnfocusableTextInput": true },
        "webRules": [{
            "ruleId": "r1", "sceneType": "TEXT_EDITOR", "enabled": true,
            "scope": { "onlyVisible": true },
            "selector": { "nodeTypes": ["input", "textarea"] },
            "condition": { "operator": "COUNT_GTE", "threshold": 2 },
            "report": { "eventName": "onTextInput", "includeNodeIds": true },
            "policy": { "reportOnRegister": false, "minReportIntervalMs": 1000, "deduplicate": true }
        }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(testPid, ruleJson);
    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(testPid);
    ASSERT_TRUE(rules.has_value());
    EXPECT_EQ(rules->ruleSetId, "rs1");
    EXPECT_TRUE(rules->globalConfig.includeUnfocusableTextInput);
    ASSERT_EQ(rules->rules.size(), 1u);
    EXPECT_EQ(rules->rules[0].ruleId, "r1");
    EXPECT_EQ(rules->rules[0].sceneType, "TEXT_EDITOR");
    EXPECT_TRUE(rules->rules[0].enabled);
    EXPECT_TRUE(rules->rules[0].scope.onlyVisible);
    EXPECT_EQ(rules->rules[0].selector.nodeTypes.size(), 2u);
    EXPECT_EQ(rules->rules[0].condition.conditionOperator, "COUNT_GTE");
    EXPECT_EQ(rules->rules[0].condition.threshold, 2);
    EXPECT_EQ(rules->rules[0].report.eventName, "onTextInput");
    EXPECT_TRUE(rules->rules[0].report.includeNodeIds);
    EXPECT_EQ(rules->rules[0].policy.minReportIntervalMs, 1000);
    EXPECT_TRUE(rules->rules[0].policy.deduplicate);
}

HWTEST_F(WebPageSceneManagerTest, ParseWebRulesFromRuleJson_WebDisabled, TestSize.Level0)
{
    std::string ruleJson = R"({
        "ruleSetId": "rs2",
        "sourceConfig": { "web": false },
        "webRules": [{ "ruleId": "r1" }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(testPid, ruleJson);
    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(testPid);
    EXPECT_FALSE(rules.has_value());
}

HWTEST_F(WebPageSceneManagerTest, ParseWebRulesFromRuleJson_EmptyRuleSetId, TestSize.Level0)
{
    std::string ruleJson = R"({
        "ruleSetId": "",
        "sourceConfig": { "web": true },
        "webRules": [{ "ruleId": "r1" }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(testPid, ruleJson);
    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(testPid);
    EXPECT_FALSE(rules.has_value());
}

HWTEST_F(WebPageSceneManagerTest, ParseWebRulesFromRuleJson_InvalidJson, TestSize.Level0)
{
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(testPid, "{ invalid }");
    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(testPid);
    EXPECT_FALSE(rules.has_value());
}

HWTEST_F(WebPageSceneManagerTest, ParseWebRulesFromRuleJson_EmptyWebRules, TestSize.Level0)
{
    std::string ruleJson = R"({
        "ruleSetId": "rs3",
        "sourceConfig": { "web": true }
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(testPid, ruleJson);
    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(testPid);
    EXPECT_FALSE(rules.has_value());
}

HWTEST_F(WebPageSceneManagerTest, ParseWebRulesFromRuleJson_PartialFailureSkipped, TestSize.Level0)
{
    std::string ruleJson = R"({
        "ruleSetId": "rs4",
        "sourceConfig": { "web": true },
        "webRules": [
            { "ruleId": "r_valid", "sceneType": "TEXT_EDITOR", "selector": { "nodeTypes": ["input"] },
                "condition": { "operator": "COUNT_GTE", "threshold": 2 } },
            { "sceneType": "TEXT_EDITOR" }
        ]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(testPid, ruleJson);
    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(testPid);
    ASSERT_TRUE(rules.has_value());
    ASSERT_EQ(rules->rules.size(), 1u);
    EXPECT_EQ(rules->rules[0].ruleId, "r_valid");
}

HWTEST_F(WebPageSceneManagerTest, ParseWebRulesFromRuleJson_GlobalConfig, TestSize.Level0)
{
    std::string ruleJson = R"({
        "ruleSetId": "rs5",
        "sourceConfig": { "web": true },
        "globalConfig": { "includeUnfocusableTextInput": true },
        "webRules": [{ "ruleId": "r1", "sceneType": "TEXT_EDITOR", "selector": { "nodeTypes": ["input"] },
            "condition": { "operator": "COUNT_GTE", "threshold": 2 },
            "report": { "eventName": "evt" } }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(testPid, ruleJson);
    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(testPid);
    ASSERT_TRUE(rules.has_value());
    EXPECT_TRUE(rules->globalConfig.includeUnfocusableTextInput);
}

// ===== ParseWebRuleItem (via Register) =====

HWTEST_F(WebPageSceneManagerTest, ParseWebRuleItem_CompleteRule, TestSize.Level0)
{
    std::string ruleJson = R"({
        "ruleSetId": "rs_item",
        "sourceConfig": { "web": true },
        "webRules": [{
            "ruleId": "r_full",
            "sceneType": "TEXT_EDITOR",
            "enabled": false,
            "scope": { "onlyVisible": true },
            "selector": { "nodeTypes": ["input", "textarea"],
                "typeAttrRules": { "input": [{ "attr": "type", "value": ["text", "password"] }] } },
            "condition": { "operator": "COUNT_GTE", "threshold": 3 },
            "report": { "eventName": "onFull", "includeNodeIds": true, "includeNodeTypes": true,
                "includeRect": true, "includeFocusable": true, "includeText": true, "includeEditable": true },
            "policy": { "reportOnRegister": true, "minReportIntervalMs": 500, "deduplicate": true }
        }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(testPid, ruleJson);
    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(testPid);
    ASSERT_TRUE(rules.has_value());
    ASSERT_EQ(rules->rules.size(), 1u);
    auto& rule = rules->rules[0];
    EXPECT_EQ(rule.ruleId, "r_full");
    EXPECT_FALSE(rule.enabled);
    EXPECT_TRUE(rule.scope.onlyVisible);
    EXPECT_EQ(rule.selector.typeAttrRules.size(), 1u);
    EXPECT_EQ(rule.selector.typeAttrRules.at("input")[0].attr, "type");
    EXPECT_EQ(rule.selector.typeAttrRules.at("input")[0].value.size(), 2u);
    EXPECT_EQ(rule.condition.threshold, 3);
    EXPECT_EQ(rule.report.eventName, "onFull");
    EXPECT_TRUE(rule.report.includeEditable);
    EXPECT_TRUE(rule.policy.reportOnRegister);
}

HWTEST_F(WebPageSceneManagerTest, ParseWebRuleItem_EmptyRuleId, TestSize.Level0)
{
    std::string ruleJson = R"({
        "ruleSetId": "rs_noid",
        "sourceConfig": { "web": true },
        "webRules": [{ "sceneType": "TEXT_EDITOR" }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(testPid, ruleJson);
    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(testPid);
    EXPECT_FALSE(rules.has_value());
}

// ===== ParseSelectorFromJson (via Register) =====

HWTEST_F(WebPageSceneManagerTest, ParseSelectorFromJson_NodeTypesOnly, TestSize.Level0)
{
    std::string ruleJson = R"({
        "ruleSetId": "rs_sel1",
        "sourceConfig": { "web": true },
        "webRules": [{ "ruleId": "r1", "sceneType": "TEXT_EDITOR", "selector": { "nodeTypes": ["input", "textarea"] },
            "condition": { "operator": "COUNT_GTE", "threshold": 2 },
            "report": { "eventName": "evt" } }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(testPid, ruleJson);
    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(testPid);
    ASSERT_TRUE(rules.has_value());
    ASSERT_EQ(rules->rules.size(), 1u);
    auto& selector = rules->rules[0].selector;
    EXPECT_EQ(selector.nodeTypes.size(), 2u);
    EXPECT_TRUE(selector.typeAttrRules.empty());
}

HWTEST_F(WebPageSceneManagerTest, ParseSelectorFromJson_WithTypeAttrRules, TestSize.Level0)
{
    std::string ruleJson = R"({
        "ruleSetId": "rs_sel2",
        "sourceConfig": { "web": true },
        "webRules": [{ "ruleId": "r1", "sceneType": "TEXT_EDITOR",
            "selector": {
                "nodeTypes": ["input", "textarea"],
                "typeAttrRules": {
                    "input": [{ "attr": "type", "value": ["text", "email"] }],
                    "textarea": [{ "attr": "name", "value": ["comment"] }]
                }
            },
            "condition": { "operator": "COUNT_GTE", "threshold": 2 },
            "report": { "eventName": "evt" } }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(testPid, ruleJson);
    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(testPid);
    ASSERT_TRUE(rules.has_value());
    ASSERT_EQ(rules->rules.size(), 1u);
    auto& selector = rules->rules[0].selector;
    EXPECT_EQ(selector.typeAttrRules.size(), 2u);
    EXPECT_EQ(selector.typeAttrRules.count("input"), 1u);
    EXPECT_EQ(selector.typeAttrRules.count("textarea"), 1u);
}

// ===== ParseTypeAttrRulesFromJson (via Register) =====

HWTEST_F(WebPageSceneManagerTest, ParseTypeAttrRulesFromJson_MultipleNodeTypes, TestSize.Level0)
{
    std::string ruleJson = R"({
        "ruleSetId": "rs_tattr",
        "sourceConfig": { "web": true },
        "webRules": [{ "ruleId": "r1", "sceneType": "TEXT_EDITOR",
            "selector": {
                "nodeTypes": ["input"],
                "typeAttrRules": {
                    "input": [
                        { "attr": "type", "value": ["text", "password", "tel"] },
                        { "attr": "name", "value": ["username"] }
                    ]
                }
            },
            "condition": { "operator": "COUNT_GTE", "threshold": 2 },
            "report": { "eventName": "evt" } }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(testPid, ruleJson);
    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(testPid);
    ASSERT_TRUE(rules.has_value());
    ASSERT_EQ(rules->rules.size(), 1u);
    auto& tar = rules->rules[0].selector.typeAttrRules;
    ASSERT_EQ(tar.count("input"), 1u);
    EXPECT_EQ(tar.at("input").size(), 2u);
    EXPECT_EQ(tar.at("input")[0].attr, "type");
    EXPECT_EQ(tar.at("input")[0].value.size(), 3u);
    EXPECT_EQ(tar.at("input")[1].attr, "name");
    EXPECT_EQ(tar.at("input")[1].value.size(), 1u);
}

HWTEST_F(WebPageSceneManagerTest, ParseTypeAttrRulesFromJson_EmptyObject, TestSize.Level0)
{
    std::string ruleJson = R"({
        "ruleSetId": "rs_tattr_empty",
        "sourceConfig": { "web": true },
        "webRules": [{ "ruleId": "r1", "sceneType": "TEXT_EDITOR",
            "selector": { "nodeTypes": ["input"] },
            "condition": { "operator": "COUNT_GTE", "threshold": 2 },
            "report": { "eventName": "evt" } }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(testPid, ruleJson);
    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(testPid);
    ASSERT_TRUE(rules.has_value());
    ASSERT_EQ(rules->rules.size(), 1u);
    auto& tar = rules->rules[0].selector.typeAttrRules;
    EXPECT_TRUE(tar.empty());
}

// ===== ParseConditionFromJson (via Register) =====

HWTEST_F(WebPageSceneManagerTest, ParseConditionFromJson_CountGte, TestSize.Level0)
{
    std::string ruleJson = R"({
        "ruleSetId": "rs_cond",
        "sourceConfig": { "web": true },
        "webRules": [{ "ruleId": "r1", "sceneType": "TEXT_EDITOR",
            "selector": { "nodeTypes": ["input"] },
            "condition": { "operator": "COUNT_GTE", "threshold": 5 },
            "report": { "eventName": "evt" } }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(testPid, ruleJson);
    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(testPid);
    ASSERT_TRUE(rules.has_value());
    ASSERT_EQ(rules->rules.size(), 1u);
    auto& cond = rules->rules[0].condition;
    EXPECT_EQ(cond.conditionOperator, "COUNT_GTE");
    EXPECT_EQ(cond.threshold, 5);
}

// ===== ParseReportFromJson (via Register) =====

HWTEST_F(WebPageSceneManagerTest, ParseReportFromJson_AllFields, TestSize.Level0)
{
    std::string ruleJson = R"({
        "ruleSetId": "rs_rep",
        "sourceConfig": { "web": true },
        "webRules": [{ "ruleId": "r1", "sceneType": "TEXT_EDITOR",
            "selector": { "nodeTypes": ["input"] },
            "condition": { "operator": "COUNT_GTE", "threshold": 2 },
            "report": { "eventName": "onAll", "includeNodeIds": true, "includeNodeTypes": true,
                "includeRect": true, "includeFocusable": true, "includeText": true, "includeEditable": true } }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(testPid, ruleJson);
    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(testPid);
    ASSERT_TRUE(rules.has_value());
    ASSERT_EQ(rules->rules.size(), 1u);
    auto& report = rules->rules[0].report;
    EXPECT_EQ(report.eventName, "onAll");
    EXPECT_TRUE(report.includeNodeIds);
}

// ===== ParsePolicyFromJson (via Register) =====

HWTEST_F(WebPageSceneManagerTest, ParsePolicyFromJson_AllFields, TestSize.Level0)
{
    std::string ruleJson = R"({
        "ruleSetId": "rs_pol",
        "sourceConfig": { "web": true },
        "webRules": [{ "ruleId": "r1", "sceneType": "TEXT_EDITOR",
            "selector": { "nodeTypes": ["input"] },
            "condition": { "operator": "COUNT_GTE", "threshold": 2 },
            "policy": { "reportOnRegister": true, "minReportIntervalMs": 2000, "deduplicate": true },
            "report": { "eventName": "evt" } }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(testPid, ruleJson);
    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(testPid);
    ASSERT_TRUE(rules.has_value());
    ASSERT_EQ(rules->rules.size(), 1u);
    auto& policy = rules->rules[0].policy;
    EXPECT_TRUE(policy.reportOnRegister);
    EXPECT_EQ(policy.minReportIntervalMs, 2000);
    EXPECT_TRUE(policy.deduplicate);
}

// ===== RegisterPageSceneRules =====

HWTEST_F(WebPageSceneManagerTest, RegisterPageSceneRules_NewProcess, TestSize.Level0)
{
    RegisterValidRuleSet("rs_new");
    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(testPid);
    ASSERT_TRUE(rules.has_value());
    EXPECT_EQ(rules->ruleSetId, "rs_new");
}

HWTEST_F(WebPageSceneManagerTest, RegisterPageSceneRules_SameProcessIdRejected, TestSize.Level0)
{
    RegisterValidRuleSet("rs_first");
    // Second registration with same processId should be rejected (1:1 mapping)
    bool result = WebPageSceneManager::GetInstance().RegisterPageSceneRules(testPid, R"({
        "ruleSetId": "rs_second",
        "sourceConfig": { "web": true },
        "webRules": [{ "ruleId": "r1", "sceneType": "TEXT_EDITOR", "selector": { "nodeTypes": ["input"] },
            "condition": { "operator": "COUNT_GTE", "threshold": 2 },
            "report": { "eventName": "evt" } }]
    })");
    EXPECT_FALSE(result);
    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(testPid);
    ASSERT_TRUE(rules.has_value());
    EXPECT_EQ(rules->ruleSetId, "rs_first");
}

HWTEST_F(WebPageSceneManagerTest, RegisterPageSceneRules_DifferentProcessId, TestSize.Level0)
{
    RegisterValidRuleSet("rs_multi", testPid);
    RegisterValidRuleSet("rs_multi", testPidAlt);
    auto rules1 = WebPageSceneManager::GetInstance().GetPageSceneRules(testPid);
    auto rules2 = WebPageSceneManager::GetInstance().GetPageSceneRules(testPidAlt);
    ASSERT_TRUE(rules1.has_value());
    ASSERT_TRUE(rules2.has_value());
}

// ===== UnregisterPageSceneRules =====

HWTEST_F(WebPageSceneManagerTest, UnregisterPageSceneRules_ClearsProcess, TestSize.Level0)
{
    RegisterValidRuleSet("rs_a");
    WebPageSceneManager::GetInstance().UnregisterPageSceneRules(testPid);
    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(testPid);
    EXPECT_FALSE(rules.has_value());
}

HWTEST_F(WebPageSceneManagerTest, UnregisterPageSceneRules_OtherProcessUnaffected, TestSize.Level0)
{
    RegisterValidRuleSet("rs_a", testPid);
    RegisterValidRuleSet("rs_b", testPidAlt);
    WebPageSceneManager::GetInstance().UnregisterPageSceneRules(testPid);
    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(testPid);
    EXPECT_FALSE(rules.has_value());
    auto rulesAlt = WebPageSceneManager::GetInstance().GetPageSceneRules(testPidAlt);
    ASSERT_TRUE(rulesAlt.has_value());
}

// ===== GetPageSceneRules =====

HWTEST_F(WebPageSceneManagerTest, GetPageSceneRules_ReturnsRegistered, TestSize.Level0)
{
    RegisterValidRuleSet("rs_get");
    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(testPid);
    ASSERT_TRUE(rules.has_value());
    EXPECT_EQ(rules->ruleSetId, "rs_get");
}

HWTEST_F(WebPageSceneManagerTest, GetPageSceneRules_UnregisteredReturnsNullopt, TestSize.Level0)
{
    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(999);
    EXPECT_EQ(rules.has_value(), false);
}

// ===== GetRegisteredProcessId =====

HWTEST_F(WebPageSceneManagerTest, GetRegisteredProcessId_WithRules, TestSize.Level0)
{
    RegisterValidRuleSet("rs_pid");
    int32_t pid = WebPageSceneManager::GetInstance().GetRegisteredProcessId();
    EXPECT_EQ(pid, testPid);
}

HWTEST_F(WebPageSceneManagerTest, GetRegisteredProcessId_NoRules, TestSize.Level0)
{
    int32_t pid = WebPageSceneManager::GetInstance().GetRegisteredProcessId();
    EXPECT_EQ(pid, -1);
}

// ===== UpdateRuleState =====

HWTEST_F(WebPageSceneManagerTest, UpdateRuleState_MatchedSetsTriggered, TestSize.Level0)
{
    RegisterValidRuleSet("rs_upd");
    WebPageSceneManager::GetInstance().UpdateRuleState(
        testPid, 1, "r1", true, 2, true, {});
    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(testPid);
    ASSERT_TRUE(rules.has_value());
    auto& state = rules->componentRuleStates[1]["r1"];
    EXPECT_TRUE(state.textEditorTriggered);
    EXPECT_GT(state.lastReportTimeMs, 0);
}

} // namespace OHOS::Ace
