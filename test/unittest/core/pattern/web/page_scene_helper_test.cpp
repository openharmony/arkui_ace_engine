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

#include <chrono>

#include "base/json/json_util.h"
#include "core/components/web/resource/web_delegate.h"
#include "core/components/web/resource/web_page_scene_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

class PageSceneHelperTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

protected:
    static constexpr int32_t testPid = 100;
    static constexpr int32_t testWebId = 1;
    static constexpr int32_t defaultConditionThreshold = 2;
    void ClearSingletonRules();
    static WebRule MakeRule(const std::string& ruleId);
};

void PageSceneHelperTest::SetUpTestCase() {}
void PageSceneHelperTest::TearDownTestCase() {}
void PageSceneHelperTest::SetUp() {}
void PageSceneHelperTest::TearDown()
{
    ClearSingletonRules();
}

void PageSceneHelperTest::ClearSingletonRules()
{
    WebPageSceneManager::GetInstance().UnregisterPageSceneRules(testPid);
}

WebRule PageSceneHelperTest::MakeRule(const std::string& ruleId)
{
    WebRule rule;
    rule.ruleId = ruleId;
    rule.sceneType = "TEXT_EDITOR";
    rule.enabled = true;
    rule.selector.nodeTypes = { "input" };
    rule.condition.conditionOperator = "COUNT_GTE";
    rule.condition.threshold = defaultConditionThreshold;
    rule.report.eventName = "onTextInput";
    return rule;
}

// ===== ParseSingleControlItem =====

/**
 * @tc.name: ParseSingleControlItem_FullFields
 * @tc.desc: Test ParseSingleControlItem with all fields populated including rect.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneHelperTest, ParseSingleControlItem_FullFields, TestSize.Level0)
{
    auto item = JsonUtil::ParseJsonString(R"({
        "nodeId": 42, "nodeType": "input", "focusable": true, "editable": true,
        "rect": { "x": 1.5, "y": 2.5, "width": 100.0, "height": 40.0 },
        "text": "hello"
    })");
    ASSERT_NE(item, nullptr);
    auto info = WebPageSceneManager::GetInstance().ParseSingleControlItem(item);
    EXPECT_EQ(info.nodeId, 42);
    EXPECT_EQ(info.nodeType, "input");
    EXPECT_TRUE(info.focusable);
    EXPECT_TRUE(info.editable);
    EXPECT_EQ(info.text, "hello");
    EXPECT_FLOAT_EQ(info.rectX, 1.5f);
    EXPECT_FLOAT_EQ(info.rectY, 2.5f);
    EXPECT_FLOAT_EQ(info.rectWidth, 100.0f);
    EXPECT_FLOAT_EQ(info.rectHeight, 40.0f);
}

/**
 * @tc.name: ParseSingleControlItem_NoRect
 * @tc.desc: Test ParseSingleControlItem without rect keeps rect fields at 0.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneHelperTest, ParseSingleControlItem_NoRect, TestSize.Level0)
{
    auto item = JsonUtil::ParseJsonString(R"({"nodeId": 7, "nodeType": "textarea"})");
    ASSERT_NE(item, nullptr);
    auto info = WebPageSceneManager::GetInstance().ParseSingleControlItem(item);
    EXPECT_EQ(info.nodeId, 7);
    EXPECT_EQ(info.nodeType, "textarea");
    EXPECT_FALSE(info.focusable);
    EXPECT_FALSE(info.editable);
    EXPECT_TRUE(info.text.empty());
    EXPECT_FLOAT_EQ(info.rectX, 0.0f);
    EXPECT_FLOAT_EQ(info.rectY, 0.0f);
    EXPECT_FLOAT_EQ(info.rectWidth, 0.0f);
    EXPECT_FLOAT_EQ(info.rectHeight, 0.0f);
}

/**
 * @tc.name: ParseSingleControlItem_DefaultsOnMissing
 * @tc.desc: Test ParseSingleControlItem returns defaults for missing numeric/bool fields.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneHelperTest, ParseSingleControlItem_DefaultsOnMissing, TestSize.Level0)
{
    auto item = JsonUtil::ParseJsonString(R"({"nodeType": "input"})");
    ASSERT_NE(item, nullptr);
    auto info = WebPageSceneManager::GetInstance().ParseSingleControlItem(item);
    EXPECT_EQ(info.nodeId, 0);
    EXPECT_EQ(info.nodeType, "input");
    EXPECT_FALSE(info.focusable);
    EXPECT_FALSE(info.editable);
}

// ===== EvaluateCondition =====

/**
 * @tc.name: EvaluateCondition_CountGteMet
 * @tc.desc: Test COUNT_GTE returns true when matchedCount >= threshold.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneHelperTest, EvaluateCondition_CountGteMet, TestSize.Level0)
{
    PageSceneCondition cond;
    cond.conditionOperator = "COUNT_GTE";
    cond.threshold = defaultConditionThreshold;
    EXPECT_TRUE(WebPageSceneManager::GetInstance().EvaluateCondition(cond, defaultConditionThreshold));
    EXPECT_TRUE(WebPageSceneManager::GetInstance().EvaluateCondition(cond, defaultConditionThreshold + 3));
}

/**
 * @tc.name: EvaluateCondition_CountGteNotMet
 * @tc.desc: Test COUNT_GTE returns false when matchedCount < threshold.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneHelperTest, EvaluateCondition_CountGteNotMet, TestSize.Level0)
{
    PageSceneCondition cond;
    cond.conditionOperator = "COUNT_GTE";
    cond.threshold = defaultConditionThreshold;
    EXPECT_FALSE(WebPageSceneManager::GetInstance().EvaluateCondition(cond, 1));
    EXPECT_FALSE(WebPageSceneManager::GetInstance().EvaluateCondition(cond, 0));
}

/**
 * @tc.name: EvaluateCondition_UnknownOperator
 * @tc.desc: Test unknown operator always returns false.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneHelperTest, EvaluateCondition_UnknownOperator, TestSize.Level0)
{
    PageSceneCondition cond;
    cond.conditionOperator = "UNKNOWN";
    cond.threshold = 1;
    EXPECT_FALSE(WebPageSceneManager::GetInstance().EvaluateCondition(cond, 100));
}

// ===== BuildSelectorJson =====

/**
 * @tc.name: BuildSelectorJson_NodeTypesOnly
 * @tc.desc: Test BuildSelectorJson with only nodeTypes and global config.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneHelperTest, BuildSelectorJson_NodeTypesOnly, TestSize.Level0)
{
    auto rule = MakeRule("r1");
    PageSceneGlobalConfig globalConfig;
    globalConfig.includeUnfocusableTextInput = false;
    std::string result = WebPageSceneManager::GetInstance().BuildSelectorJson(rule, globalConfig);
    auto parsed = JsonUtil::ParseJsonString(result);
    ASSERT_NE(parsed, nullptr);
    auto nodeTypes = parsed->GetValue("nodeTypes");
    ASSERT_NE(nodeTypes, nullptr);
    EXPECT_EQ(nodeTypes->GetArraySize(), 1);
    auto item = nodeTypes->GetArrayItem(0);
    ASSERT_NE(item, nullptr);
    EXPECT_EQ(item->GetString(), "input");
    EXPECT_FALSE(parsed->GetBool("includeUnfocusableTextInput", true));
    EXPECT_TRUE(parsed->GetBool("onlyVisible", false));
    EXPECT_FALSE(parsed->Contains("typeAttrRules"));
}

/**
 * @tc.name: BuildSelectorJson_WithOnlyVisible
 * @tc.desc: Test BuildSelectorJson includes onlyVisible when scope.onlyVisible=true.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneHelperTest, BuildSelectorJson_WithOnlyVisible, TestSize.Level0)
{
    auto rule = MakeRule("r1");
    rule.scope.onlyVisible = true;
    PageSceneGlobalConfig globalConfig;
    std::string result = WebPageSceneManager::GetInstance().BuildSelectorJson(rule, globalConfig);
    auto parsed = JsonUtil::ParseJsonString(result);
    ASSERT_NE(parsed, nullptr);
    EXPECT_TRUE(parsed->GetBool("onlyVisible", false));
}

/**
 * @tc.name: BuildSelectorJson_WithTypeAttrRules
 * @tc.desc: Test BuildSelectorJson includes typeAttrRules when present.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneHelperTest, BuildSelectorJson_WithTypeAttrRules, TestSize.Level0)
{
    auto rule = MakeRule("r1");
    PageSceneTypeAttrRule tar;
    tar.attr = "type";
    tar.value = { "text", "email" };
    rule.selector.typeAttrRules["input"] = { tar };
    PageSceneGlobalConfig globalConfig;
    std::string result = WebPageSceneManager::GetInstance().BuildSelectorJson(rule, globalConfig);
    auto parsed = JsonUtil::ParseJsonString(result);
    ASSERT_NE(parsed, nullptr);
    auto tarObj = parsed->GetValue("typeAttrRules");
    ASSERT_NE(tarObj, nullptr);
    auto inputArr = tarObj->GetValue("input");
    ASSERT_NE(inputArr, nullptr);
    EXPECT_EQ(inputArr->GetArraySize(), 1);
}

/**
 * @tc.name: BuildSelectorJson_GlobalConfigFlag
 * @tc.desc: Test BuildSelectorJson reflects includeUnfocusableTextInput from global config.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneHelperTest, BuildSelectorJson_GlobalConfigFlag, TestSize.Level0)
{
    auto rule = MakeRule("r1");
    PageSceneGlobalConfig globalConfig;
    globalConfig.includeUnfocusableTextInput = true;
    std::string result = WebPageSceneManager::GetInstance().BuildSelectorJson(rule, globalConfig);
    auto parsed = JsonUtil::ParseJsonString(result);
    ASSERT_NE(parsed, nullptr);
    EXPECT_TRUE(parsed->GetBool("includeUnfocusableTextInput", false));
}

// ===== BuildTypeAttrRulesJson =====

/**
 * @tc.name: BuildTypeAttrRulesJson_EmptySelector
 * @tc.desc: Test BuildTypeAttrRulesJson with empty typeAttrRules returns empty object.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneHelperTest, BuildTypeAttrRulesJson_EmptySelector, TestSize.Level0)
{
    PageSceneSelector selector;
    auto obj = WebPageSceneManager::GetInstance().BuildTypeAttrRulesJson(selector);
    ASSERT_NE(obj, nullptr);
    EXPECT_TRUE(obj->GetChild()->GetKey().empty());
}

/**
 * @tc.name: BuildTypeAttrRulesJson_MultipleEntries
 * @tc.desc: Test BuildTypeAttrRulesJson with multiple nodeTypes and rules.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneHelperTest, BuildTypeAttrRulesJson_MultipleEntries, TestSize.Level0)
{
    PageSceneSelector selector;
    PageSceneTypeAttrRule tar1;
    tar1.attr = "type";
    tar1.value = { "text", "password" };
    PageSceneTypeAttrRule tar2;
    tar2.attr = "name";
    tar2.value = { "username" };
    selector.typeAttrRules["input"] = { tar1, tar2 };
    selector.typeAttrRules["textarea"] = { tar1 };
    auto obj = WebPageSceneManager::GetInstance().BuildTypeAttrRulesJson(selector);
    ASSERT_NE(obj, nullptr);
    auto inputArr = obj->GetValue("input");
    ASSERT_NE(inputArr, nullptr);
    EXPECT_EQ(inputArr->GetArraySize(), 2);
    auto textareaArr = obj->GetValue("textarea");
    ASSERT_NE(textareaArr, nullptr);
    EXPECT_EQ(textareaArr->GetArraySize(), 1);
}

// ===== IsDuplicatedEvent =====

/**
 * @tc.name: IsDuplicatedEvent_DeduplicateFalse
 * @tc.desc: Test IsDuplicatedEvent returns false when deduplicate is disabled.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneHelperTest, IsDuplicatedEvent_DeduplicateFalse, TestSize.Level0)
{
    auto rule = MakeRule("r1");
    rule.policy.deduplicate = false;
    RuleMatchState state;
    state.lastMatchedCount = 2;
    state.lastMatchedNodeIds = { 1, 2 };
    PageSceneControlInfo c1;
    c1.nodeId = 1;
    PageSceneControlInfo c2;
    c2.nodeId = 2;
    EXPECT_FALSE(WebPageSceneManager::GetInstance().IsDuplicatedEvent(rule, 2, { c1, c2 }, state));
}

/**
 * @tc.name: IsDuplicatedEvent_SameIdsAndCount
 * @tc.desc: Test IsDuplicatedEvent returns true when nodeIds and count match.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneHelperTest, IsDuplicatedEvent_SameIdsAndCount, TestSize.Level0)
{
    auto rule = MakeRule("r1");
    rule.policy.deduplicate = true;
    RuleMatchState state;
    state.lastMatchedCount = 2;
    state.lastMatchedNodeIds = { 1, 2 };
    PageSceneControlInfo c1;
    c1.nodeId = 1;
    PageSceneControlInfo c2;
    c2.nodeId = 2;
    EXPECT_TRUE(WebPageSceneManager::GetInstance().IsDuplicatedEvent(rule, 2, { c1, c2 }, state));
}

/**
 * @tc.name: IsDuplicatedEvent_DifferentIds
 * @tc.desc: Test IsDuplicatedEvent returns false when nodeIds differ.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneHelperTest, IsDuplicatedEvent_DifferentIds, TestSize.Level0)
{
    auto rule = MakeRule("r1");
    rule.policy.deduplicate = true;
    RuleMatchState state;
    state.lastMatchedCount = 2;
    state.lastMatchedNodeIds = { 1, 2 };
    PageSceneControlInfo c;
    c.nodeId = 9;
    EXPECT_FALSE(WebPageSceneManager::GetInstance().IsDuplicatedEvent(rule, 1, { c }, state));
}

/**
 * @tc.name: IsDuplicatedEvent_SameIdsDifferentCount
 * @tc.desc: Test IsDuplicatedEvent returns false when count differs even with same ids.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneHelperTest, IsDuplicatedEvent_SameIdsDifferentCount, TestSize.Level0)
{
    auto rule = MakeRule("r1");
    rule.policy.deduplicate = true;
    RuleMatchState state;
    state.lastMatchedCount = 1;
    state.lastMatchedNodeIds = { 1 };
    PageSceneControlInfo c;
    c.nodeId = 1;
    EXPECT_FALSE(WebPageSceneManager::GetInstance().IsDuplicatedEvent(rule, 99, { c }, state));
}

// ===== IsWithinMinInterval =====

/**
 * @tc.name: IsWithinMinInterval_ZeroInterval
 * @tc.desc: Test IsWithinMinInterval returns false when minReportIntervalMs <= 0.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneHelperTest, IsWithinMinInterval_ZeroInterval, TestSize.Level0)
{
    auto rule = MakeRule("r1");
    rule.policy.minReportIntervalMs = 0;
    RuleMatchState state;
    state.lastReportTimeMs = 1000;
    EXPECT_FALSE(WebPageSceneManager::GetInstance().IsWithinMinInterval(rule, state));
}

/**
 * @tc.name: IsWithinMinInterval_ZeroLastReport
 * @tc.desc: Test IsWithinMinInterval returns false when lastReportTimeMs <= 0.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneHelperTest, IsWithinMinInterval_ZeroLastReport, TestSize.Level0)
{
    auto rule = MakeRule("r1");
    rule.policy.minReportIntervalMs = 1000;
    RuleMatchState state;
    state.lastReportTimeMs = 0;
    EXPECT_FALSE(WebPageSceneManager::GetInstance().IsWithinMinInterval(rule, state));
}

/**
 * @tc.name: IsWithinMinInterval_WithinWindow
 * @tc.desc: Test IsWithinMinInterval returns true when now - last < interval.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneHelperTest, IsWithinMinInterval_WithinWindow, TestSize.Level0)
{
    auto rule = MakeRule("r1");
    rule.policy.minReportIntervalMs = 60000; // 60s, large enough for test latency
    RuleMatchState state;
    state.lastReportTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count();
    EXPECT_TRUE(WebPageSceneManager::GetInstance().IsWithinMinInterval(rule, state));
}

/**
 * @tc.name: IsWithinMinInterval_OutsideWindow
 * @tc.desc: Test IsWithinMinInterval returns false when now - last >= interval.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneHelperTest, IsWithinMinInterval_OutsideWindow, TestSize.Level0)
{
    auto rule = MakeRule("r1");
    rule.policy.minReportIntervalMs = 1; // 1ms
    RuleMatchState state;
    state.lastReportTimeMs = 1; // very old timestamp
    EXPECT_FALSE(WebPageSceneManager::GetInstance().IsWithinMinInterval(rule, state));
}

// ===== DeriveSceneType =====

/**
 * @tc.name: DeriveSceneType_MatchedReturnsTextEditor
 * @tc.desc: Test DeriveSceneType returns "TEXT_EDITOR" when matched=true regardless of state.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneHelperTest, DeriveSceneType_MatchedReturnsTextEditor, TestSize.Level0)
{
    EXPECT_EQ(WebPageSceneManager::GetInstance().DeriveSceneType(testPid, testWebId, "r1", true),
        "TEXT_EDITOR");
}

/**
 * @tc.name: DeriveSceneType_NotMatchedNoProcess
 * @tc.desc: Test DeriveSceneType returns "" when no process registered.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneHelperTest, DeriveSceneType_NotMatchedNoProcess, TestSize.Level0)
{
    EXPECT_EQ(WebPageSceneManager::GetInstance().DeriveSceneType(testPid, testWebId, "r1", false), "");
}

/**
 * @tc.name: DeriveSceneType_NotMatchedNoComponentState
 * @tc.desc: Test DeriveSceneType returns "" when process has no state for webId.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneHelperTest, DeriveSceneType_NotMatchedNoComponentState, TestSize.Level0)
{
    std::string ruleJson = R"({
        "ruleSetId": "rs_derive", "sourceConfig": { "web": true },
        "webRules": [{ "ruleId": "r1", "sceneType": "TEXT_EDITOR", "selector": { "nodeTypes": ["input"] },
            "condition": { "operator": "COUNT_GTE", "threshold": 2 },
            "report": { "eventName": "evt" } }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(testPid, ruleJson);
    EXPECT_EQ(WebPageSceneManager::GetInstance().DeriveSceneType(testPid, testWebId, "r1", false), "");
}

/**
 * @tc.name: DeriveSceneType_NotMatchedTriggeredReturnsExit
 * @tc.desc: Test DeriveSceneType returns "TEXT_EDITOR_EXIT" when state has triggered=true.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneHelperTest, DeriveSceneType_NotMatchedTriggeredReturnsExit, TestSize.Level0)
{
    std::string ruleJson = R"({
        "ruleSetId": "rs_exit", "sourceConfig": { "web": true },
        "webRules": [{ "ruleId": "r1", "sceneType": "TEXT_EDITOR", "selector": { "nodeTypes": ["input"] },
            "condition": { "operator": "COUNT_GTE", "threshold": 2 },
            "report": { "eventName": "evt" } }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(testPid, ruleJson);
    WebPageSceneManager::GetInstance().UpdateRuleState(
        testPid, testWebId, "r1", true, 2, false, {});
    EXPECT_EQ(WebPageSceneManager::GetInstance().DeriveSceneType(testPid, testWebId, "r1", false),
        "TEXT_EDITOR_EXIT");
}

// ===== ShouldReportEvent =====

/**
 * @tc.name: ShouldReportEvent_NoRulesReturnsFalse
 * @tc.desc: Test ShouldReportEvent returns false when no rules registered.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneHelperTest, ShouldReportEvent_NoRulesReturnsFalse, TestSize.Level0)
{
    EXPECT_FALSE(WebPageSceneManager::GetInstance().ShouldReportEvent(
        testPid, testWebId, "r1", "TEXT_EDITOR", 2, {}));
}

/**
 * @tc.name: ShouldReportEvent_NoComponentStateReturnsTrue
 * @tc.desc: Test ShouldReportEvent returns true when no prior state for component.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneHelperTest, ShouldReportEvent_NoComponentStateReturnsTrue, TestSize.Level0)
{
    std::string ruleJson = R"({
        "ruleSetId": "rs_sre", "sourceConfig": { "web": true },
        "webRules": [{ "ruleId": "r1", "sceneType": "TEXT_EDITOR", "selector": { "nodeTypes": ["input"] },
            "condition": { "operator": "COUNT_GTE", "threshold": 2 },
            "report": { "eventName": "evt" } }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(testPid, ruleJson);
    EXPECT_TRUE(WebPageSceneManager::GetInstance().ShouldReportEvent(
        testPid, testWebId, "r1", "TEXT_EDITOR", 2, {}));
}

/**
 * @tc.name: ShouldReportEvent_ExitWithoutTriggeredReturnsFalse
 * @tc.desc: Test ShouldReportEvent returns false for TEXT_EDITOR_EXIT without prior trigger.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneHelperTest, ShouldReportEvent_ExitWithoutTriggeredReturnsFalse, TestSize.Level0)
{
    std::string ruleJson = R"({
        "ruleSetId": "rs_exit", "sourceConfig": { "web": true },
        "webRules": [{ "ruleId": "r1", "sceneType": "TEXT_EDITOR", "selector": { "nodeTypes": ["input"] },
            "condition": { "operator": "COUNT_GTE", "threshold": 2 },
            "report": { "eventName": "evt" } }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(testPid, ruleJson);
    // First establish component state but without textEditorTriggered
    WebPageSceneManager::GetInstance().UpdateRuleState(
        testPid, testWebId, "r1", false, 0, false, {});
    EXPECT_FALSE(WebPageSceneManager::GetInstance().ShouldReportEvent(
        testPid, testWebId, "r1", "TEXT_EDITOR_EXIT", 0, {}));
}

/**
 * @tc.name: ShouldReportEvent_ExitWithTriggeredReturnsTrue
 * @tc.desc: Test ShouldReportEvent returns true for TEXT_EDITOR_EXIT after prior trigger.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneHelperTest, ShouldReportEvent_ExitWithTriggeredReturnsTrue, TestSize.Level0)
{
    std::string ruleJson = R"({
        "ruleSetId": "rs_exit2", "sourceConfig": { "web": true },
        "webRules": [{ "ruleId": "r1", "sceneType": "TEXT_EDITOR", "selector": { "nodeTypes": ["input"] },
            "condition": { "operator": "COUNT_GTE", "threshold": 2 },
            "report": { "eventName": "evt" } }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(testPid, ruleJson);
    WebPageSceneManager::GetInstance().UpdateRuleState(
        testPid, testWebId, "r1", true, 2, false, {});
    EXPECT_TRUE(WebPageSceneManager::GetInstance().ShouldReportEvent(
        testPid, testWebId, "r1", "TEXT_EDITOR_EXIT", 0, {}));
}

/**
 * @tc.name: ShouldReportEvent_DuplicatedReturnsFalse
 * @tc.desc: Test ShouldReportEvent returns false when event is duplicated.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneHelperTest, ShouldReportEvent_DuplicatedReturnsFalse, TestSize.Level0)
{
    std::string ruleJson = R"({
        "ruleSetId": "rs_dup", "sourceConfig": { "web": true },
        "webRules": [{ "ruleId": "r1", "sceneType": "TEXT_EDITOR", "selector": { "nodeTypes": ["input"] },
            "condition": { "operator": "COUNT_GTE", "threshold": 2 },
            "report": { "eventName": "evt" }, "policy": { "deduplicate": true } }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(testPid, ruleJson);
    PageSceneControlInfo c1;
    c1.nodeId = 1;
    PageSceneControlInfo c2;
    c2.nodeId = 2;
    // First report establishes state with ids {1,2} and count 2
    WebPageSceneManager::GetInstance().UpdateRuleState(
        testPid, testWebId, "r1", true, 2, false, { c1, c2 });
    // Second identical report should be considered duplicated
    EXPECT_FALSE(WebPageSceneManager::GetInstance().ShouldReportEvent(
        testPid, testWebId, "r1", "TEXT_EDITOR", 2, { c1, c2 }));
}

/**
 * @tc.name: ShouldReportEvent_WithinMinIntervalReturnsFalse
 * @tc.desc: Test ShouldReportEvent returns false when within min report interval.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneHelperTest, ShouldReportEvent_WithinMinIntervalReturnsFalse, TestSize.Level0)
{
    std::string ruleJson = R"({
        "ruleSetId": "rs_int", "sourceConfig": { "web": true },
        "webRules": [{ "ruleId": "r1", "sceneType": "TEXT_EDITOR", "selector": { "nodeTypes": ["input"] },
            "condition": { "operator": "COUNT_GTE", "threshold": 2 },
            "report": { "eventName": "evt" },
            "policy": { "minReportIntervalMs": 60000 } }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(testPid, ruleJson);
    // Establish triggered state with reported=true (sets lastReportTimeMs to now)
    WebPageSceneManager::GetInstance().UpdateRuleState(
        testPid, testWebId, "r1", true, 2, true, {});
    // Subsequent report should be suppressed due to min interval
    EXPECT_FALSE(WebPageSceneManager::GetInstance().ShouldReportEvent(
        testPid, testWebId, "r1", "TEXT_EDITOR", 2, {}));
}

/**
 * @tc.name: ShouldReportEvent_UnknownRuleReturnsFalse
 * @tc.desc: Test ShouldReportEvent returns false when ruleId not found in rule set.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneHelperTest, ShouldReportEvent_UnknownRuleReturnsFalse, TestSize.Level0)
{
    std::string ruleJson = R"({
        "ruleSetId": "rs_unknown", "sourceConfig": { "web": true },
        "webRules": [{ "ruleId": "r1", "sceneType": "TEXT_EDITOR", "selector": { "nodeTypes": ["input"] },
            "condition": { "operator": "COUNT_GTE", "threshold": 2 },
            "report": { "eventName": "evt" } }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(testPid, ruleJson);
    EXPECT_FALSE(WebPageSceneManager::GetInstance().ShouldReportEvent(
        testPid, testWebId, "nonexistent_rule", "TEXT_EDITOR", 2, {}));
}

} // namespace OHOS::Ace
