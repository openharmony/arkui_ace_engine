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

class PageSceneMatchTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

protected:
    static constexpr int32_t testPid = 100;
    static constexpr int32_t testWebId = 1;
    static constexpr int32_t defaultRuleThreshold = 2;
    void ClearSingletonRules();
    // Register a rule set with one enabled rule of given threshold (default 2).
    void RegisterRuleSet(const std::string& ruleSetId, int32_t threshold = defaultRuleThreshold);
    // Build the selector JSON that the registered rule's first rule expects.
    std::string GetExpectedSelector();
};

void PageSceneMatchTest::SetUpTestCase() {}
void PageSceneMatchTest::TearDownTestCase() {}
void PageSceneMatchTest::SetUp() {}
void PageSceneMatchTest::TearDown()
{
    ClearSingletonRules();
}

void PageSceneMatchTest::ClearSingletonRules()
{
    WebPageSceneManager::GetInstance().UnregisterPageSceneRules(testPid);
}

void PageSceneMatchTest::RegisterRuleSet(const std::string& ruleSetId, int32_t threshold)
{
    std::string ruleJson = R"({
        "ruleSetId": ")" + ruleSetId + R"(",
        "sourceConfig": { "web": true },
        "globalConfig": { "includeUnfocusableTextInput": false },
        "webRules": [{
            "ruleId": "r1", "sceneType": "TEXT_EDITOR", "enabled": true,
            "selector": { "nodeTypes": ["input"] },
            "condition": { "operator": "COUNT_GTE", "threshold":
)" + std::to_string(threshold) + R"(},
            "report": { "eventName": "onTextInput" }
        }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(testPid, ruleJson);
}

std::string PageSceneMatchTest::GetExpectedSelector()
{
    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(testPid);
    if (!rules.has_value() || rules->rules.empty()) {
        return "";
    }
    return WebPageSceneManager::GetInstance().BuildSelectorJson(
        rules->rules[0], rules->globalConfig);
}

// ===== ProcessQueryResultCore =====

/**
 * @tc.name: ProcessQueryResultCore_NoRulesReturnsEmpty
 * @tc.desc: Test ProcessQueryResultCore returns empty when no rules registered.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneMatchTest, ProcessQueryResultCore_NoRulesReturnsEmpty, TestSize.Level0)
{
    auto results = WebPageSceneManager::GetInstance().ProcessQueryResultCore(
        testPid, testWebId, "", R"({"errorCode":0,"controls":[]})", false);
    EXPECT_TRUE(results.empty());
}

/**
 * @tc.name: ProcessQueryResultCore_EmptyControlsNoPriorState
 * @tc.desc: Test ProcessQueryResultCore produces no result when no prior trigger state.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneMatchTest, ProcessQueryResultCore_EmptyControlsNoPriorState, TestSize.Level0)
{
    RegisterRuleSet("rs_pqrc1");
    std::string selector = GetExpectedSelector();
    auto results = WebPageSceneManager::GetInstance().ProcessQueryResultCore(
        testPid, testWebId, selector, R"({"errorCode":0,"controls":[]})", false);
    EXPECT_TRUE(results.empty());
}

/**
 * @tc.name: ProcessQueryResultCore_EmptyControlsWithPriorTrigger
 * @tc.desc: Test ProcessQueryResultCore produces EXIT result when prior trigger exists.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneMatchTest, ProcessQueryResultCore_EmptyControlsWithPriorTrigger, TestSize.Level0)
{
    RegisterRuleSet("rs_pqrc2");
    std::string selector = GetExpectedSelector();
    // Establish prior triggered state
    WebPageSceneManager::GetInstance().UpdateRuleState(
        testPid, testWebId, "r1", true, 2, false, {});
    auto results = WebPageSceneManager::GetInstance().ProcessQueryResultCore(
        testPid, testWebId, selector, R"({"errorCode":0,"controls":[]})", false);
    ASSERT_EQ(results.size(), 1u);
    auto parsed = JsonUtil::ParseJsonString(results[0]);
    ASSERT_NE(parsed, nullptr);
    EXPECT_EQ(parsed->GetString("eventName"), "TEXT_EDITOR_EXIT");
    EXPECT_EQ(parsed->GetString("ruleId"), "r1");
    EXPECT_FALSE(parsed->GetBool("matched", true));
    // After processing, triggered state should be reset
    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(testPid);
    ASSERT_TRUE(rules.has_value());
    EXPECT_FALSE(rules->componentRuleStates[testWebId]["r1"].textEditorTriggered);
}

/**
 * @tc.name: ProcessQueryResultCore_MatchedControlsConditionMet
 * @tc.desc: Test ProcessQueryResultCore produces TEXT_EDITOR when condition met.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneMatchTest, ProcessQueryResultCore_MatchedControlsConditionMet, TestSize.Level0)
{
    RegisterRuleSet("rs_pqrc3"); // threshold=2
    std::string selector = GetExpectedSelector();
    std::string rawResult = R"({
        "errorCode": 0,
        "controls": [
            { "nodeId": 1, "nodeType": "input" },
            { "nodeId": 2, "nodeType": "input" }
        ]
    })";
    auto results = WebPageSceneManager::GetInstance().ProcessQueryResultCore(
        testPid, testWebId, selector, rawResult, false);
    ASSERT_EQ(results.size(), 1u);
    auto parsed = JsonUtil::ParseJsonString(results[0]);
    ASSERT_NE(parsed, nullptr);
    EXPECT_EQ(parsed->GetString("eventName"), "TEXT_EDITOR");
    EXPECT_TRUE(parsed->GetBool("matched", false));
    EXPECT_EQ(parsed->GetInt("matchedCount", 0), 2);
}

/**
 * @tc.name: ProcessQueryResultCore_MatchedControlsConditionNotMet
 * @tc.desc: Test ProcessQueryResultCore produces no result when condition not met and no trigger.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneMatchTest, ProcessQueryResultCore_MatchedControlsConditionNotMet, TestSize.Level0)
{
    RegisterRuleSet("rs_pqrc4"); // threshold=2
    std::string selector = GetExpectedSelector();
    std::string rawResult = R"({
        "errorCode": 0,
        "controls": [
            { "nodeId": 1, "nodeType": "input" }
        ]
    })";
    auto results = WebPageSceneManager::GetInstance().ProcessQueryResultCore(
        testPid, testWebId, selector, rawResult, false);
    // matchedCount=1 < threshold=2, and no prior trigger -> DeriveSceneType returns ""
    EXPECT_TRUE(results.empty());
}

/**
 * @tc.name: ProcessQueryResultCore_MatchedControlsNotMetWithPriorTrigger
 * @tc.desc: Test ProcessQueryResultCore produces EXIT when condition not met but was triggered.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneMatchTest, ProcessQueryResultCore_MatchedControlsNotMetWithPriorTrigger, TestSize.Level0)
{
    RegisterRuleSet("rs_pqrc5"); // threshold=2
    std::string selector = GetExpectedSelector();
    WebPageSceneManager::GetInstance().UpdateRuleState(
        testPid, testWebId, "r1", true, 2, false, {});
    std::string rawResult = R"({
        "errorCode": 0,
        "controls": [
            { "nodeId": 1, "nodeType": "input" }
        ]
    })";
    auto results = WebPageSceneManager::GetInstance().ProcessQueryResultCore(
        testPid, testWebId, selector, rawResult, false);
    ASSERT_EQ(results.size(), 1u);
    auto parsed = JsonUtil::ParseJsonString(results[0]);
    ASSERT_NE(parsed, nullptr);
    EXPECT_EQ(parsed->GetString("eventName"), "TEXT_EDITOR_EXIT");
}

/**
 * @tc.name: ProcessQueryResultCore_IsGetResultUsesSceneType
 * @tc.desc: Test ProcessQueryResultCore with isGetResult uses rule.sceneType as eventName.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneMatchTest, ProcessQueryResultCore_IsGetResultUsesSceneType, TestSize.Level0)
{
    RegisterRuleSet("rs_pqrc6"); // threshold=2
    std::string selector = GetExpectedSelector();
    std::string rawResult = R"({
        "errorCode": 0,
        "controls": [{ "nodeId": 1, "nodeType": "input" }]
    })";
    auto results = WebPageSceneManager::GetInstance().ProcessQueryResultCore(
        testPid, testWebId, selector, rawResult, true);
    ASSERT_EQ(results.size(), 1u);
    auto parsed = JsonUtil::ParseJsonString(results[0]);
    ASSERT_NE(parsed, nullptr);
    // isGetResult path uses rule.sceneType as eventName (regardless of matched)
    EXPECT_EQ(parsed->GetString("eventName"), "TEXT_EDITOR");
    EXPECT_EQ(parsed->GetString("sceneType"), "TEXT_EDITOR");
}

/**
 * @tc.name: ProcessQueryResultCore_WrongSelectorNoResult
 * @tc.desc: Test ProcessQueryResultCore skips rules whose selector doesn't match.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneMatchTest, ProcessQueryResultCore_WrongSelectorNoResult, TestSize.Level0)
{
    RegisterRuleSet("rs_pqrc7");
    // Pass a selector that won't match the registered rule's expected selector
    std::string wrongSelector = R"({"nodeTypes":["textarea"],"includeUnfocusableTextInput":false})";
    std::string rawResult = R"({
        "errorCode": 0,
        "controls": [{ "nodeId": 1, "nodeType": "input" }]
    })";
    auto results = WebPageSceneManager::GetInstance().ProcessQueryResultCore(
        testPid, testWebId, wrongSelector, rawResult, false);
    EXPECT_TRUE(results.empty());
}

// ===== ProcessQueryResult =====

/**
 * @tc.name: ProcessQueryResult_NoRulesNoCrash
 * @tc.desc: Test ProcessQueryResult with no rules does not crash.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneMatchTest, ProcessQueryResult_NoRulesNoCrash, TestSize.Level0)
{
    WebPageSceneManager::GetInstance().ProcessQueryResult(
        testPid, testWebId, "", R"({"errorCode":0,"controls":[]})", false);
    // No crash expected
}

/**
 * @tc.name: ProcessQueryResult_ProducesResultsAndReports
 * @tc.desc: Test ProcessQueryResult produces results and forwards them via OnMatchResult.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneMatchTest, ProcessQueryResult_ProducesResultsAndReports, TestSize.Level0)
{
    RegisterRuleSet("rs_pqr1");
    std::string selector = GetExpectedSelector();
    WebPageSceneManager::GetInstance().UpdateRuleState(
        testPid, testWebId, "r1", true, 2, false, {});
    // ProcessQueryResult internally calls OnMatchResult (no-op in mock UiSessionManager)
    WebPageSceneManager::GetInstance().ProcessQueryResult(
        testPid, testWebId, selector, R"({"errorCode":0,"controls":[]})", false);
    // After processing, state should reflect the EXIT (triggered reset to false)
    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(testPid);
    ASSERT_TRUE(rules.has_value());
    EXPECT_FALSE(rules->componentRuleStates[testWebId]["r1"].textEditorTriggered);
}

// ===== FlushExitOnNavigate =====

/**
 * @tc.name: FlushExitOnNavigate_NoRulesNoCrash
 * @tc.desc: Test FlushExitOnNavigate with no rules does not crash.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneMatchTest, FlushExitOnNavigate_NoRulesNoCrash, TestSize.Level0)
{
    WebPageSceneManager::GetInstance().FlushExitOnNavigate(testPid, testWebId);
    // No crash expected
}

/**
 * @tc.name: FlushExitOnNavigate_NoComponentStateNoOp
 * @tc.desc: Test FlushExitOnNavigate with rules but no component state is a no-op.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneMatchTest, FlushExitOnNavigate_NoComponentStateNoOp, TestSize.Level0)
{
    RegisterRuleSet("rs_feon1");
    WebPageSceneManager::GetInstance().FlushExitOnNavigate(testPid, testWebId);
    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(testPid);
    ASSERT_TRUE(rules.has_value());
    EXPECT_TRUE(rules->componentRuleStates.empty());
}

/**
 * @tc.name: FlushExitOnNavigate_NoTriggeredStateNoReport
 * @tc.desc: Test FlushExitOnNavigate skips rules that were not triggered.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneMatchTest, FlushExitOnNavigate_NoTriggeredStateNoReport, TestSize.Level0)
{
    RegisterRuleSet("rs_feon2");
    // Establish state but without textEditorTriggered
    WebPageSceneManager::GetInstance().UpdateRuleState(
        testPid, testWebId, "r1", false, 0, false, {});
    WebPageSceneManager::GetInstance().FlushExitOnNavigate(testPid, testWebId);
    // No EXIT produced since textEditorTriggered was false
    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(testPid);
    ASSERT_TRUE(rules.has_value());
    // Component state entry was created by UpdateRuleState, FlushExitOnNavigate erases it
    EXPECT_TRUE(rules->componentRuleStates.find(testWebId) == rules->componentRuleStates.end());
}

/**
 * @tc.name: FlushExitOnNavigate_WithTriggeredProducesExit
 * @tc.desc: Test FlushExitOnNavigate produces EXIT and clears state when triggered.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneMatchTest, FlushExitOnNavigate_WithTriggeredProducesExit, TestSize.Level0)
{
    RegisterRuleSet("rs_feon3");
    WebPageSceneManager::GetInstance().UpdateRuleState(
        testPid, testWebId, "r1", true, 2, true, {});
    // Verify triggered state exists
    auto rulesBefore = WebPageSceneManager::GetInstance().GetPageSceneRules(testPid);
    ASSERT_TRUE(rulesBefore.has_value());
    EXPECT_TRUE(rulesBefore->componentRuleStates[testWebId]["r1"].textEditorTriggered);
    // OnMatchResult non-empty sceneJson is no-op in mock UiSessionManager
    WebPageSceneManager::GetInstance().FlushExitOnNavigate(testPid, testWebId);
    // After FlushExitOnNavigate, component state should be erased
    auto rulesAfter = WebPageSceneManager::GetInstance().GetPageSceneRules(testPid);
    ASSERT_TRUE(rulesAfter.has_value());
    EXPECT_TRUE(rulesAfter->componentRuleStates.find(testWebId) ==
        rulesAfter->componentRuleStates.end());
}

/**
 * @tc.name: FlushExitOnNavigate_OtherComponentUnaffected
 * @tc.desc: Test FlushExitOnNavigate only affects the specified webId.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneMatchTest, FlushExitOnNavigate_OtherComponentUnaffected, TestSize.Level0)
{
    RegisterRuleSet("rs_feon4");
    constexpr int32_t otherWebId = 2;
    // Both components have triggered state
    WebPageSceneManager::GetInstance().UpdateRuleState(
        testPid, testWebId, "r1", true, 2, true, {});
    WebPageSceneManager::GetInstance().UpdateRuleState(
        testPid, otherWebId, "r1", true, 2, true, {});
    // Flush only testWebId
    WebPageSceneManager::GetInstance().FlushExitOnNavigate(testPid, testWebId);
    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(testPid);
    ASSERT_TRUE(rules.has_value());
    // testWebId should be erased
    EXPECT_TRUE(rules->componentRuleStates.find(testWebId) == rules->componentRuleStates.end());
    // otherWebId should still have triggered state
    auto otherIt = rules->componentRuleStates.find(otherWebId);
    ASSERT_NE(otherIt, rules->componentRuleStates.end());
    EXPECT_TRUE(otherIt->second["r1"].textEditorTriggered);
}

} // namespace OHOS::Ace
