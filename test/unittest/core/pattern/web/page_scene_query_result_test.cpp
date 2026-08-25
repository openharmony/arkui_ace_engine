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

class PageSceneQueryResultTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

protected:
    static constexpr int32_t TEST_PID = 700;
    static constexpr int32_t TEST_WEB_ID = 10;
    static constexpr int32_t testNodeIdBase = 100;
    static constexpr double testRectX = 10.0;
    static constexpr double testRectY = 20.0;
    static constexpr double testRectWidth = 200.0;
    static constexpr double testRectHeight = 40.0;
    static constexpr int32_t testErrorCodeSuccess = 0;
    void RegisterRuleSet();
    void ClearRules();
    std::string BuildSelectorJsonForRule();
    std::string MakeControlsJson(int32_t count);
};

void PageSceneQueryResultTest::SetUpTestCase() {}
void PageSceneQueryResultTest::TearDownTestCase() {}
void PageSceneQueryResultTest::SetUp() {}
void PageSceneQueryResultTest::TearDown() { ClearRules(); }

void PageSceneQueryResultTest::RegisterRuleSet()
{
    std::string ruleJson = R"({
        "ruleSetId": "rs_result",
        "sourceConfig": { "web": true },
        "webRules": [{ "ruleId": "r1", "sceneType": "TEXT_EDITOR",
            "selector": { "nodeTypes": ["input"] },
            "condition": { "operator": "COUNT_GTE", "threshold": 2 },
            "report": { "eventName": "onTextInput" },
            "policy": { "reportOnRegister": false, "deduplicate": false, "minReportIntervalMs": 0 } }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(TEST_PID, ruleJson);
}

void PageSceneQueryResultTest::ClearRules()
{
    WebPageSceneManager::GetInstance().UnregisterPageSceneRules(TEST_PID);
}

std::string PageSceneQueryResultTest::BuildSelectorJsonForRule()
{
    WebRule rule;
    rule.ruleId = "r1";
    rule.sceneType = "TEXT_EDITOR";
    rule.selector.nodeTypes = {"input"};
    rule.scope.onlyVisible = true;
    PageSceneGlobalConfig globalConfig;
    return WebPageSceneManager::GetInstance().BuildSelectorJson(rule, globalConfig);
}

std::string PageSceneQueryResultTest::MakeControlsJson(int32_t count)
{
    auto root = JsonUtil::Create(true);
    root->Put("errorCode", testErrorCodeSuccess);
    auto arr = JsonUtil::CreateArray(true);
    for (int32_t i = 0; i < count; ++i) {
        auto item = JsonUtil::Create(true);
        item->Put("nodeId", testNodeIdBase + i);
        item->Put("nodeType", "input");
        item->Put("focusable", true);
        item->Put("editable", true);
        auto rect = JsonUtil::Create(true);
        rect->Put("x", testRectX);
        rect->Put("y", testRectY);
        rect->Put("width", testRectWidth);
        rect->Put("height", testRectHeight);
        item->Put("rect", rect);
        item->Put("text", "");
        arr->Put(item);
    }
    root->Put("controls", arr);
    return root->ToString();
}

// ===== ProcessQueryResultCore =====

HWTEST_F(PageSceneQueryResultTest, ProcessQueryResultCore_MatchedProducesSceneJson, TestSize.Level0)
{
    RegisterRuleSet();
    std::string selectorJson = BuildSelectorJsonForRule();
    // 3 controls >= threshold 2 → matched
    std::string rawResult = MakeControlsJson(3);
    auto results = WebPageSceneManager::GetInstance().ProcessQueryResultCore(
        TEST_PID, TEST_WEB_ID, selectorJson, rawResult, false);
    ASSERT_EQ(results.size(), 1u);
    auto parsed = JsonUtil::ParseJsonString(results[0]);
    ASSERT_NE(parsed, nullptr);
    EXPECT_EQ(parsed->GetString("ruleSetId"), "rs_result");
    EXPECT_EQ(parsed->GetString("ruleId"), "r1");
    EXPECT_EQ(parsed->GetString("eventName"), "TEXT_EDITOR");
    EXPECT_TRUE(parsed->GetBool("matched", false));
    EXPECT_EQ(parsed->GetInt("matchedCount", 0), 3);
}

HWTEST_F(PageSceneQueryResultTest, ProcessQueryResultCore_NotMatchedNoPriorTrigger_Empty, TestSize.Level0)
{
    RegisterRuleSet();
    std::string selectorJson = BuildSelectorJsonForRule();
    // 1 control < threshold 2, no prior trigger → no result
    std::string rawResult = MakeControlsJson(1);
    auto results = WebPageSceneManager::GetInstance().ProcessQueryResultCore(
        TEST_PID, TEST_WEB_ID, selectorJson, rawResult, false);
    EXPECT_TRUE(results.empty());
}

HWTEST_F(PageSceneQueryResultTest, ProcessQueryResultCore_EmptyControlsNoPriorTrigger_Empty, TestSize.Level0)
{
    RegisterRuleSet();
    std::string selectorJson = BuildSelectorJsonForRule();
    // Empty controls with errorCode=0 but no controls
    std::string rawResult = R"({"errorCode":0,"controls":[]})";
    auto results = WebPageSceneManager::GetInstance().ProcessQueryResultCore(
        TEST_PID, TEST_WEB_ID, selectorJson, rawResult, false);
    // No prior trigger, so EXIT not derived, no results
    EXPECT_TRUE(results.empty());
}

HWTEST_F(PageSceneQueryResultTest, ProcessQueryResultCore_UnregisteredProcess_Empty, TestSize.Level0)
{
    std::string selectorJson = R"({"nodeTypes":["input"]})";
    std::string rawResult = MakeControlsJson(3);
    auto results = WebPageSceneManager::GetInstance().ProcessQueryResultCore(
        9999, TEST_WEB_ID, selectorJson, rawResult, false);
    EXPECT_TRUE(results.empty());
}

HWTEST_F(PageSceneQueryResultTest, ProcessQueryResultCore_ErrorErrorCode_Empty, TestSize.Level0)
{
    RegisterRuleSet();
    std::string selectorJson = BuildSelectorJsonForRule();
    std::string rawResult = R"({"errorCode":2})";
    auto results = WebPageSceneManager::GetInstance().ProcessQueryResultCore(
        TEST_PID, TEST_WEB_ID, selectorJson, rawResult, false);
    EXPECT_TRUE(results.empty());
}

HWTEST_F(PageSceneQueryResultTest, ProcessQueryResultCore_GetResultAlwaysReports, TestSize.Level0)
{
    RegisterRuleSet();
    std::string selectorJson = BuildSelectorJsonForRule();
    // isGetResult=true → reports even with 1 control (below threshold)
    std::string rawResult = MakeControlsJson(1);
    auto results = WebPageSceneManager::GetInstance().ProcessQueryResultCore(
        TEST_PID, TEST_WEB_ID, selectorJson, rawResult, true);
    ASSERT_EQ(results.size(), 1u);
    auto parsed = JsonUtil::ParseJsonString(results[0]);
    ASSERT_NE(parsed, nullptr);
    // Not matched but isGetResult so eventName = sceneType
    EXPECT_FALSE(parsed->GetBool("matched", true));
    EXPECT_EQ(parsed->GetInt("matchedCount", 0), 1);
}

HWTEST_F(PageSceneQueryResultTest, ProcessQueryResultCore_SceneJsonIncludesNodes, TestSize.Level0)
{
    RegisterRuleSet();
    std::string selectorJson = BuildSelectorJsonForRule();
    std::string rawResult = MakeControlsJson(2);
    auto results = WebPageSceneManager::GetInstance().ProcessQueryResultCore(
        TEST_PID, TEST_WEB_ID, selectorJson, rawResult, false);
    ASSERT_EQ(results.size(), 1u);
    auto parsed = JsonUtil::ParseJsonString(results[0]);
    ASSERT_NE(parsed, nullptr);
    auto nodes = parsed->GetValue("nodes");
    ASSERT_NE(nodes, nullptr);
    // Default includeNodeIds=true, includeNodeTypes=true, includeRect=true
    EXPECT_EQ(nodes->GetArraySize(), 2);
    auto node0 = nodes->GetArrayItem(0);
    ASSERT_NE(node0, nullptr);
    EXPECT_EQ(node0->GetInt("nodeId", -1), testNodeIdBase);
    EXPECT_EQ(node0->GetString("nodeType"), "input");
    EXPECT_TRUE(node0->GetBool("focusable", false));
    auto rect = node0->GetValue("rect");
    ASSERT_NE(rect, nullptr);
}

// ===== FlushExitOnNavigate =====

HWTEST_F(PageSceneQueryResultTest, FlushExitOnNavigate_TriggeredRuleProducesEXIT, TestSize.Level0)
{
    RegisterRuleSet();
    // First: trigger a matched state
    WebPageSceneManager::GetInstance().UpdateRuleState(
        TEST_PID, TEST_WEB_ID, "r1", true, 3, true, {});
    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(TEST_PID);
    ASSERT_TRUE(rules.has_value());
    EXPECT_TRUE(rules->componentRuleStates[TEST_WEB_ID]["r1"].textEditorTriggered);

    // Flush → should produce EXIT and clear state
    WebPageSceneManager::GetInstance().FlushExitOnNavigate(TEST_PID, TEST_WEB_ID);
    rules = WebPageSceneManager::GetInstance().GetPageSceneRules(TEST_PID);
    ASSERT_TRUE(rules.has_value());
    // componentRuleStates for this webId should be erased
    EXPECT_EQ(rules->componentRuleStates.count(TEST_WEB_ID), 0u);
}

HWTEST_F(PageSceneQueryResultTest, FlushExitOnNavigate_NoTriggeredRule_NoEffect, TestSize.Level0)
{
    RegisterRuleSet();
    // No UpdateRuleState called → nothing triggered
    WebPageSceneManager::GetInstance().FlushExitOnNavigate(TEST_PID, TEST_WEB_ID);
    auto rules = WebPageSceneManager::GetInstance().GetPageSceneRules(TEST_PID);
    ASSERT_TRUE(rules.has_value());
    // No component states at all, still valid
    EXPECT_TRUE(rules->componentRuleStates.empty());
}

HWTEST_F(PageSceneQueryResultTest, FlushExitOnNavigate_UnregisteredProcess_NoCrash, TestSize.Level0)
{
    // Should not crash on unregistered process
    WebPageSceneManager::GetInstance().FlushExitOnNavigate(9999, TEST_WEB_ID);
}

// ===== OnMatchResult =====

HWTEST_F(PageSceneQueryResultTest, OnMatchResult_EmptySceneJson_NoCrash, TestSize.Level0)
{
    // Empty sceneJson → early return, no crash
    WebPageSceneManager::GetInstance().OnMatchResult(TEST_PID, "", false);
}

HWTEST_F(PageSceneQueryResultTest, OnMatchResult_ValidSceneJson_NoCrash, TestSize.Level0)
{
    // Should forward to UiSessionManager without crash
    WebPageSceneManager::GetInstance().OnMatchResult(
        TEST_PID, R"({"ruleSetId":"rs","ruleId":"r1"})", false);
}

// ===== ProcessQueryResult (with OnMatchResult forwarding) =====

HWTEST_F(PageSceneQueryResultTest, ProcessQueryResult_Matched_NoCrash, TestSize.Level0)
{
    RegisterRuleSet();
    std::string selectorJson = BuildSelectorJsonForRule();
    std::string rawResult = MakeControlsJson(3);
    // This calls ProcessQueryResultCore + OnMatchResult per result
    WebPageSceneManager::GetInstance().ProcessQueryResult(
        TEST_PID, TEST_WEB_ID, selectorJson, rawResult, false);
    // If we get here without crash, the full pipeline works
}

} // namespace OHOS::Ace
