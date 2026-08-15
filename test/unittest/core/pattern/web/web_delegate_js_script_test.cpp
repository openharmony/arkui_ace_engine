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

class WebDelegateJsScriptTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void WebDelegateJsScriptTest::SetUpTestCase() {}
void WebDelegateJsScriptTest::TearDownTestCase() {}
void WebDelegateJsScriptTest::SetUp() {}
void WebDelegateJsScriptTest::TearDown() {}

/**
 * @tc.name: ParseControlsJson_SuccessResponse
 * @tc.desc: Test ParseControlsJson with valid errorCode=0 and controls array.
 * @tc.type: FUNC
 */
HWTEST_F(WebDelegateJsScriptTest, ParseControlsJson_SuccessResponse, TestSize.Level0)
{
    std::string resultJson = R"({
        "errorCode": 0,
        "controls": [{
            "nodeId": 42,
            "nodeType": "input",
            "focusable": true,
            "editable": true,
            "rect": { "x": 10.5, "y": 20.0, "width": 100.0, "height": 40.0 },
            "text": "hello"
        }]
    })";
    auto controls = WebPageSceneManager::GetInstance().ParseControlsJson(resultJson);
    ASSERT_EQ(controls.size(), 1u);
    EXPECT_EQ(controls[0].nodeId, 42);
    EXPECT_EQ(controls[0].nodeType, "input");
    EXPECT_TRUE(controls[0].focusable);
    EXPECT_TRUE(controls[0].editable);
    EXPECT_FLOAT_EQ(controls[0].rectX, 10.5f);
    EXPECT_FLOAT_EQ(controls[0].rectY, 20.0f);
    EXPECT_EQ(controls[0].text, "hello");
}

/**
 * @tc.name: ParseControlsJson_ErrorResponse
 * @tc.desc: Test ParseControlsJson with errorCode!=0 returns empty.
 * @tc.type: FUNC
 */
HWTEST_F(WebDelegateJsScriptTest, ParseControlsJson_ErrorResponse, TestSize.Level0)
{
    std::string resultJson = R"({"errorCode": 2, "controls": []})";
    auto controls = WebPageSceneManager::GetInstance().ParseControlsJson(resultJson);
    EXPECT_TRUE(controls.empty());
}

/**
 * @tc.name: ParseControlsJson_EmptyControls
 * @tc.desc: Test ParseControlsJson with errorCode=0 but empty controls.
 * @tc.type: FUNC
 */
HWTEST_F(WebDelegateJsScriptTest, ParseControlsJson_EmptyControls, TestSize.Level0)
{
    std::string resultJson = R"({"errorCode": 0, "controls": []})";
    auto controls = WebPageSceneManager::GetInstance().ParseControlsJson(resultJson);
    EXPECT_TRUE(controls.empty());
}

/**
 * @tc.name: ParseControlsJson_InvalidJson
 * @tc.desc: Test ParseControlsJson with invalid JSON returns empty.
 * @tc.type: FUNC
 */
HWTEST_F(WebDelegateJsScriptTest, ParseControlsJson_InvalidJson, TestSize.Level0)
{
    auto controls = WebPageSceneManager::GetInstance().ParseControlsJson("not json");
    EXPECT_TRUE(controls.empty());
}

/**
 * @tc.name: ParseControlsJson_PendingResponse
 * @tc.desc: Test ParseControlsJson with errorCode=3 (pending) returns empty.
 * @tc.type: FUNC
 */
HWTEST_F(WebDelegateJsScriptTest, ParseControlsJson_PendingResponse, TestSize.Level0)
{
    std::string resultJson = R"({"errorCode": 3, "controls": []})";
    auto controls = WebPageSceneManager::GetInstance().ParseControlsJson(resultJson);
    EXPECT_TRUE(controls.empty());
}

} // namespace OHOS::Ace
