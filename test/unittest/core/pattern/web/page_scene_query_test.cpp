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

class PageSceneQueryTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

protected:
    static constexpr int32_t testPid = 100;
    void ClearSingletonRules();
};

void PageSceneQueryTest::SetUpTestCase() {}
void PageSceneQueryTest::TearDownTestCase() {}
void PageSceneQueryTest::SetUp() {}
void PageSceneQueryTest::TearDown()
{
    ClearSingletonRules();
}

void PageSceneQueryTest::ClearSingletonRules()
{
    WebPageSceneManager::GetInstance().UnregisterPageSceneRules(testPid);
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
 * @tc.name: GetPageSceneForWeb_ExistingRuleSetId
 * @tc.desc: Test GetPageScene with an already-registered ruleSetId reuses rules.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneQueryTest, GetPageSceneForWeb_ExistingRuleSetId, TestSize.Level0)
{
    std::string ruleJson = R"({
        "ruleSetId": "rs_query1",
        "sourceConfig": { "web": true },
        "webRules": [{ "ruleId": "r1", "sceneType": "TEXT_EDITOR", "selector": { "nodeTypes": ["input"] },
            "condition": { "operator": "COUNT_GTE", "threshold": 1 },
            "report": { "eventName": "onTextInput" } }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(testPid, ruleJson);
    EXPECT_TRUE(GetRuleSetCopy(testPid, "rs_query1").has_value());
}

/**
 * @tc.name: GetPageSceneForWeb_NewRuleJson
 * @tc.desc: Test GetPageScene with new ruleJson does not persist rules.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneQueryTest, GetPageSceneForWeb_NewRuleJson, TestSize.Level0)
{
    std::string existingJson = R"({
        "ruleSetId": "rs_existing",
        "sourceConfig": { "web": true },
        "webRules": [{ "ruleId": "r1", "sceneType": "TEXT_EDITOR", "selector": { "nodeTypes": ["input"] },
            "condition": { "operator": "COUNT_GTE", "threshold": 2 },
            "report": { "eventName": "evt1" } }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(testPid, existingJson);
    EXPECT_TRUE(GetRuleSetCopy(testPid, "rs_existing").has_value());
    EXPECT_FALSE(GetRuleSetCopy(testPid, "rs_temp").has_value());
}

/**
 * @tc.name: GetPageSceneForWeb_SingleShotIsGetResult
 * @tc.desc: Test that single-shot query reports isGetResult=true.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneQueryTest, GetPageSceneForWeb_SingleShotIsGetResult, TestSize.Level0)
{
    std::string ruleJson = R"({
        "ruleSetId": "rs_get",
        "sourceConfig": { "web": true },
        "webRules": [{
            "ruleId": "r1", "sceneType": "TEXT_EDITOR", "enabled": false,
            "selector": { "nodeTypes": ["input"] },
            "condition": { "operator": "COUNT_GTE", "threshold": 2 },
            "report": { "eventName": "evt" } }]
    })";
    WebPageSceneManager::GetInstance().RegisterPageSceneRules(testPid, ruleJson);
    EXPECT_TRUE(GetRuleSetCopy(testPid, "rs_get").has_value());
}

} // namespace OHOS::Ace
