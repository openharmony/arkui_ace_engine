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

class WebDelegateMatchTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

protected:
    static constexpr int32_t TEST_PID = 100;
    static constexpr int32_t TEST_WEB_ID = 1;

    void RegisterTestRuleSet(bool reportOnRegister = false,
        int32_t minReportIntervalMs = 0, bool deduplicate = false);
    void ClearSingletonRules();
};

void WebDelegateMatchTest::SetUpTestCase() {}
void WebDelegateMatchTest::TearDownTestCase() {}
void WebDelegateMatchTest::SetUp() {}
void WebDelegateMatchTest::TearDown()
{
    ClearSingletonRules();
}

void WebDelegateMatchTest::RegisterTestRuleSet(bool reportOnRegister,
    int32_t minReportIntervalMs, bool deduplicate)
{
    std::string ruleJson = R"({"ruleSetId":"rs1",)"
        R"("sourceConfig":{"web":true},)"
        R"("webRules":[{"ruleId":"r1","sceneType":"TEXT_EDITOR","selector":{"nodeTypes":["input"]},)"
        R"("condition":{"operator":"COUNT_GTE","threshold":2},)"
        R"("report":{"eventName":"onTextInput"},)"
        R"("policy":{"reportOnRegister":)" + std::to_string(reportOnRegister ? 1 : 0) +
        R"(,"minReportIntervalMs":)" + std::to_string(minReportIntervalMs) +
        R"(,"deduplicate":)" + std::to_string(deduplicate ? 1 : 0) + R"(}}]})";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(TEST_PID, ruleJson);
}

void WebDelegateMatchTest::ClearSingletonRules()
{
    WebPageSceneManager::GetInstance().UnregisterPageSceneRules(TEST_PID);
}

/**
 * @tc.name: UpdateRuleState_TriggeredOnMatch
 * @tc.desc: Test that matched=true sets textEditorTriggered=true.
 * @tc.type: FUNC
 */
HWTEST_F(WebDelegateMatchTest, UpdateRuleState_TriggeredOnMatch, TestSize.Level0)
{
    RegisterTestRuleSet();
    WebPageSceneManager::GetInstance().UpdateRuleState(
        TEST_PID, TEST_WEB_ID, "r1", true, 3, true, {});
    auto rsOpt = WebPageSceneManager::GetInstance().GetPageSceneRules(TEST_PID);
    ASSERT_TRUE(rsOpt.has_value());
    auto compIt = rsOpt->componentRuleStates.find(TEST_WEB_ID);
    ASSERT_NE(compIt, rsOpt->componentRuleStates.end());
    auto& state = compIt->second["r1"];
    EXPECT_TRUE(state.textEditorTriggered);
    EXPECT_GT(state.lastReportTimeMs, 0);
    EXPECT_EQ(state.lastMatchedCount, 3);
}

/**
 * @tc.name: UpdateRuleState_ExitResetsTriggered
 * @tc.desc: Test that TEXT_EDITOR_EXIT resets textEditorTriggered to false.
 * @tc.type: FUNC
 */
HWTEST_F(WebDelegateMatchTest, UpdateRuleState_ExitResetsTriggered, TestSize.Level0)
{
    RegisterTestRuleSet();
    WebPageSceneManager::GetInstance().UpdateRuleState(
        TEST_PID, TEST_WEB_ID, "r1", true, 3, true, {});
    auto rsOpt = WebPageSceneManager::GetInstance().GetPageSceneRules(TEST_PID);
    ASSERT_TRUE(rsOpt.has_value());
    EXPECT_TRUE(rsOpt->componentRuleStates.at(TEST_WEB_ID).at("r1").textEditorTriggered);

    WebPageSceneManager::GetInstance().UpdateRuleState(
        TEST_PID, TEST_WEB_ID, "r1", false, 0, false, {});
    rsOpt = WebPageSceneManager::GetInstance().GetPageSceneRules(TEST_PID);
    ASSERT_TRUE(rsOpt.has_value());
    EXPECT_FALSE(rsOpt->componentRuleStates.at(TEST_WEB_ID).at("r1").textEditorTriggered);
}

/**
 * @tc.name: UpdateRuleState_NotTriggeredNoExit
 * @tc.desc: Test matched=false without prior trigger just updates dedup info.
 * @tc.type: FUNC
 */
HWTEST_F(WebDelegateMatchTest, UpdateRuleState_NotTriggeredNoExit, TestSize.Level0)
{
    RegisterTestRuleSet();
    PageSceneControlInfo c;
    c.nodeId = 10;
    WebPageSceneManager::GetInstance().UpdateRuleState(
        TEST_PID, TEST_WEB_ID, "r1", false, 1, false, {c});
    auto rsOpt = WebPageSceneManager::GetInstance().GetPageSceneRules(TEST_PID);
    ASSERT_TRUE(rsOpt.has_value());
    auto& state = rsOpt->componentRuleStates.at(TEST_WEB_ID).at("r1");
    EXPECT_FALSE(state.textEditorTriggered);
    EXPECT_EQ(state.lastMatchedCount, 1);
    EXPECT_EQ(state.lastMatchedNodeIds.count(10), 1u);
}

/**
 * @tc.name: Unregister_ClearsProcess
 * @tc.desc: Test that UnregisterPageSceneRules clears all rules for a process.
 * @tc.type: FUNC
 */
HWTEST_F(WebDelegateMatchTest, Unregister_ClearsProcess, TestSize.Level0)
{
    RegisterTestRuleSet();

    auto rulesBefore = WebPageSceneManager::GetInstance().GetPageSceneRules(TEST_PID);
    ASSERT_TRUE(rulesBefore.has_value());

    WebPageSceneManager::GetInstance().UnregisterPageSceneRules(TEST_PID);

    auto rulesAfter = WebPageSceneManager::GetInstance().GetPageSceneRules(TEST_PID);
    EXPECT_FALSE(rulesAfter.has_value());
}

} // namespace OHOS::Ace
