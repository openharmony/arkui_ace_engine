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
 * @tc.name: BuildQueryControlsScript_ContainsAllFilters
 * @tc.desc: Test BuildQueryControlsScript generates script with all filter levels.
 * @tc.type: FUNC
 */
HWTEST_F(WebDelegateJsScriptTest, BuildQueryControlsScript_ContainsAllFilters, TestSize.Level0)
{
    std::string selectorJson = R"({
        "nodeTypes": ["input"],
        "typeAttrRules": { "input": [{ "attr": "type", "value": ["text"] }] },
        "onlyVisible": true,
        "includeUnfocusableTextInput": false
    })";
    std::string script = WebDelegate::BuildQueryControlsScript(selectorJson, "r1",
        std::vector<std::string>{});

    EXPECT_NE(script.find("querySelectorAll"), std::string::npos);
    EXPECT_NE(script.find("typeAttrRules"), std::string::npos);
    EXPECT_NE(script.find("onlyVisible"), std::string::npos);
    EXPECT_NE(script.find("includeUnfocusableTextInput"), std::string::npos);
    EXPECT_NE(script.find("getArkWebDomNodeId"), std::string::npos);
    EXPECT_NE(script.find("devicePixelRatio"), std::string::npos);
    EXPECT_NE(script.find("errorCode"), std::string::npos);
    EXPECT_NE(script.find("controls"), std::string::npos);
}

/**
 * @tc.name: BuildQueryControlsScript_EmptySelectorJson
 * @tc.desc: Test BuildQueryControlsScript with empty selectorJson still produces valid script.
 * @tc.type: FUNC
 */
HWTEST_F(WebDelegateJsScriptTest, BuildQueryControlsScript_EmptySelectorJson, TestSize.Level0)
{
    std::string selectorJson = "{}";
    std::string script = WebDelegate::BuildQueryControlsScript(selectorJson, "r1",
        std::vector<std::string>{});
    EXPECT_FALSE(script.empty());
    EXPECT_NE(script.find("selectorConfig"), std::string::npos);
}

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
 * @tc.name: BuildQueryControlsScript_NodeIdMethod
 * @tc.desc: Test that JS script contains getArkWebDomNodeId for nodeId retrieval.
 * @tc.type: FUNC
 */
HWTEST_F(WebDelegateJsScriptTest, BuildQueryControlsScript_NodeIdMethod, TestSize.Level0)
{
    std::string selectorJson = R"({"nodeTypes": ["input"], "onlyVisible": false, "includeUnfocusableTextInput": true})";
    std::string script = WebDelegate::BuildQueryControlsScript(selectorJson, "r1",
        std::vector<std::string>{});
    EXPECT_NE(script.find("getArkWebDomNodeId"), std::string::npos);
    EXPECT_NE(script.find("devicePixelRatio"), std::string::npos);
}

/**
 * @tc.name: BuildQueryControlsScript_DomReadyCheck
 * @tc.desc: Test that JS script contains document.readyState and DOMContentLoaded check.
 * @tc.type: FUNC
 */
HWTEST_F(WebDelegateJsScriptTest, BuildQueryControlsScript_DomReadyCheck, TestSize.Level0)
{
    std::string selectorJson = R"({"nodeTypes": ["input"]})";
    std::string script = WebDelegate::BuildQueryControlsScript(selectorJson, "r1",
        std::vector<std::string>{});
    EXPECT_NE(script.find("document.readyState"), std::string::npos);
    EXPECT_NE(script.find("DOMContentLoaded"), std::string::npos);
}

/**
 * @tc.name: BuildQueryControlsScript_PendingErrorCode
 * @tc.desc: Test that JS script returns errorCode=3 when DOM is not ready.
 * @tc.type: FUNC
 */
HWTEST_F(WebDelegateJsScriptTest, BuildQueryControlsScript_PendingErrorCode, TestSize.Level0)
{
    std::string selectorJson = R"({"nodeTypes": ["input"]})";
    std::string script = WebDelegate::BuildQueryControlsScript(selectorJson, "r1",
        std::vector<std::string>{});
    EXPECT_NE(script.find("errorCode:3"), std::string::npos);
}

/**
 * @tc.name: BuildQueryControlsScript_AsyncProxyCall
 * @tc.desc: Test that JS script calls ArkWebPageSceneReady.onDomReady in DOMContentLoaded callback.
 * @tc.type: FUNC
 */
HWTEST_F(WebDelegateJsScriptTest, BuildQueryControlsScript_AsyncProxyCall, TestSize.Level0)
{
    std::string selectorJson = R"({"nodeTypes": ["input"]})";
    std::string script = WebDelegate::BuildQueryControlsScript(selectorJson, "r1",
        std::vector<std::string>{});
    EXPECT_NE(script.find("ArkWebPageSceneReady"), std::string::npos);
    EXPECT_NE(script.find("onDomReady"), std::string::npos);
    EXPECT_NE(script.find("__psQuery"), std::string::npos);
}

/**
 * @tc.name: BuildQueryControlsScript_MultipleAttrRules
 * @tc.desc: Test that JS script iterates all attrRules (not just [0]).
 * @tc.type: FUNC
 */
HWTEST_F(WebDelegateJsScriptTest, BuildQueryControlsScript_MultipleAttrRules, TestSize.Level0)
{
    std::string selectorJson = R"({
        "nodeTypes": ["input", "div"],
        "typeAttrRules": {
            "input": [{ "attr": "type", "value": ["text", "password"] }],
            "div": [{ "attr": "contenteditable", "value": ["true"] }]
        }
    })";
    std::string script = WebDelegate::BuildQueryControlsScript(selectorJson, "r1",
        std::vector<std::string>{});
    // Verify the script uses a loop over attrRules instead of hard-coded [0]
    EXPECT_NE(script.find("attrRules.length"), std::string::npos);
    EXPECT_NE(script.find("ruleMatched"), std::string::npos);
    EXPECT_EQ(script.find("attrRules[0]"), std::string::npos);
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

/**
 * @tc.name: BuildQueryControlsScript_ContainsObserverNodeTypes
 * @tc.desc: Test that merged script contains observer with provided nodeTypes union.
 * @tc.type: FUNC
 */
HWTEST_F(WebDelegateJsScriptTest, BuildQueryControlsScript_ContainsObserverNodeTypes, TestSize.Level0)
{
    std::string selectorJson = R"({"nodeTypes": ["input"]})";
    std::vector<std::string> nodeTypes = {"input", "textarea", "div"};
    std::string script = WebDelegate::BuildQueryControlsScript(selectorJson, "r1", nodeTypes);
    EXPECT_NE(script.find("MutationObserver"), std::string::npos);
    EXPECT_NE(script.find("ArkWebPageSceneReady"), std::string::npos);
    EXPECT_NE(script.find("onDomReady"), std::string::npos);
    EXPECT_NE(script.find("__pageSceneObservers"), std::string::npos);
    EXPECT_NE(script.find("input"), std::string::npos);
    EXPECT_NE(script.find("textarea"), std::string::npos);
    EXPECT_NE(script.find("div"), std::string::npos);
}

/**
 * @tc.name: BuildQueryControlsScript_ObserverDebounceAndTimeout
 * @tc.desc: Test that merged script has debounce and timeout mechanisms.
 * @tc.type: FUNC
 */
HWTEST_F(WebDelegateJsScriptTest, BuildQueryControlsScript_ObserverDebounceAndTimeout, TestSize.Level0)
{
    std::string selectorJson = R"({"nodeTypes": ["input"]})";
    std::vector<std::string> nodeTypes = {"input"};
    std::string script = WebDelegate::BuildQueryControlsScript(selectorJson, "r1", nodeTypes);
    EXPECT_NE(script.find("__psDebounceTimer"), std::string::npos);
    EXPECT_NE(script.find("__psTimeoutId"), std::string::npos);
    EXPECT_NE(script.find("disconnect"), std::string::npos);
}

/**
 * @tc.name: BuildQueryControlsScript_ContainsAutocompleteAndXpath
 * @tc.desc: Test that JS script contains autocomplete and xpath extraction logic.
 * @tc.type: FUNC
 */
HWTEST_F(WebDelegateJsScriptTest, BuildQueryControlsScript_ContainsAutocompleteAndXpath, TestSize.Level0)
{
    std::string selectorJson = R"({
        "nodeTypes": ["input"],
        "includeAutocomplete": true,
        "includeXpath": true
    })";
    std::string script = WebDelegate::BuildQueryControlsScript(selectorJson, "r1",
        std::vector<std::string>{});
    EXPECT_NE(script.find("includeAutocomplete"), std::string::npos);
    EXPECT_NE(script.find("includeXpath"), std::string::npos);
    EXPECT_NE(script.find("autocomplete"), std::string::npos);
}

/**
 * @tc.name: ParseControlsJson_AutocompleteAndXpath
 * @tc.desc: Test ParseControlsJson parses autocomplete and xpath fields.
 * @tc.type: FUNC
 */
HWTEST_F(WebDelegateJsScriptTest, ParseControlsJson_AutocompleteAndXpath, TestSize.Level0)
{
    std::string resultJson = R"({
        "errorCode": 0,
        "controls": [{
            "nodeId": 1,
            "nodeType": "input",
            "focusable": true,
            "editable": true,
            "rect": { "x": 0, "y": 0, "width": 100, "height": 30 },
            "text": "",
            "autocomplete": "email",
            "xpath": "/html/body/div/input"
        }]
    })";
    auto controls = WebPageSceneManager::GetInstance().ParseControlsJson(resultJson);
    ASSERT_EQ(controls.size(), 1u);
    EXPECT_EQ(controls[0].autocomplete, "email");
    EXPECT_EQ(controls[0].xpath, "/html/body/div/input");
}

// ===== EscapeSelectorJson =====

/**
 * @tc.name: EscapeSelectorJson_NoSpecialChars
 * @tc.desc: Test EscapeSelectorJson returns unchanged string when no special chars.
 * @tc.type: FUNC
 */
HWTEST_F(WebDelegateJsScriptTest, EscapeSelectorJson_NoSpecialChars, TestSize.Level0)
{
    std::string input = R"({"nodeTypes":["input"]})";
    std::string result = WebDelegate::EscapeSelectorJson(input);
    EXPECT_EQ(result, input);
}

/**
 * @tc.name: EscapeSelectorJson_EscapesBackslash
 * @tc.desc: Test EscapeSelectorJson escapes backslash.
 * @tc.type: FUNC
 */
HWTEST_F(WebDelegateJsScriptTest, EscapeSelectorJson_EscapesBackslash, TestSize.Level0)
{
    std::string input = R"(path\\to\\node)";
    std::string result = WebDelegate::EscapeSelectorJson(input);
    EXPECT_EQ(result, R"(path\\\\to\\\\node)");
}

/**
 * @tc.name: EscapeSelectorJson_EscapesSingleQuote
 * @tc.desc: Test EscapeSelectorJson escapes single quote.
 * @tc.type: FUNC
 */
HWTEST_F(WebDelegateJsScriptTest, EscapeSelectorJson_EscapesSingleQuote, TestSize.Level0)
{
    std::string input = "it's a test";
    std::string result = WebDelegate::EscapeSelectorJson(input);
    EXPECT_EQ(result, "it\\'s a test");
}

/**
 * @tc.name: EscapeSelectorJson_EscapesNewlineAndCarriageReturn
 * @tc.desc: Test EscapeSelectorJson escapes \n and \r.
 * @tc.type: FUNC
 */
HWTEST_F(WebDelegateJsScriptTest, EscapeSelectorJson_EscapesNewlineAndCarriageReturn, TestSize.Level0)
{
    std::string input = "line1\nline2\rline3";
    std::string result = WebDelegate::EscapeSelectorJson(input);
    EXPECT_EQ(result, "line1\\nline2\\rline3");
}

/**
 * @tc.name: EscapeSelectorJson_AllSpecialCharsTogether
 * @tc.desc: Test EscapeSelectorJson handles all special chars together.
 * @tc.type: FUNC
 */
HWTEST_F(WebDelegateJsScriptTest, EscapeSelectorJson_AllSpecialCharsTogether, TestSize.Level0)
{
    std::string input = "a\\b'c\nd\re";
    std::string result = WebDelegate::EscapeSelectorJson(input);
    EXPECT_EQ(result, "a\\\\b\\'c\\nd\\re");
}

/**
 * @tc.name: EscapeSelectorJson_EmptyString
 * @tc.desc: Test EscapeSelectorJson handles empty string.
 * @tc.type: FUNC
 */
HWTEST_F(WebDelegateJsScriptTest, EscapeSelectorJson_EmptyString, TestSize.Level0)
{
    std::string input = "";
    std::string result = WebDelegate::EscapeSelectorJson(input);
    EXPECT_EQ(result, "");
}

} // namespace OHOS::Ace
