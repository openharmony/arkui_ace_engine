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
#include "base/memory/ace_type.h"

#define private public
#define protected public
#include "core/components_ng/base/frame_node.h"
#undef private
#undef protected

#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/manager/page_scene/page_scene_rule_manager.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/frameworks/core/components_ng/render/mock_render_context.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t PAGE_SCENE_NO_ERROR = 0;
constexpr int32_t PAGE_SCENE_PARAM_INVALID = 4;
constexpr int32_t PAGE_SCENE_LAST_UNFINISH = 5;
constexpr int32_t TEST_PROCESS_ID = 1001;
constexpr int32_t SECOND_PROCESS_ID = 1002;
constexpr int32_t TEST_ROOT_ID = 2000;
constexpr int32_t TEST_TEXT_INPUT_ID = 2001;
constexpr int32_t TEST_TEXT_AREA_ID = 2002;
constexpr int32_t TEST_SEARCH_ID = 2003;
constexpr int32_t TEST_SEARCH_FIELD_ID = 2004;
constexpr int32_t TEST_RICH_EDITOR_ID = 2005;
constexpr int32_t MATCH_THRESHOLD = 2;
constexpr int32_t INVALID_THRESHOLD = 0;
constexpr int32_t DEFAULT_MIN_REPORT_INTERVAL_MS = 500;
constexpr int32_t ONE_MATCHED_NODE = 1;
constexpr int32_t TWO_MATCHED_NODES = 2;
constexpr float ROOT_X = 0.0f;
constexpr float ROOT_Y = 0.0f;
constexpr float ROOT_WIDTH = 720.0f;
constexpr float ROOT_HEIGHT = 1280.0f;
constexpr float FIRST_NODE_X = 10.0f;
constexpr float FIRST_NODE_Y = 20.0f;
constexpr float SECOND_NODE_X = 30.0f;
constexpr float SECOND_NODE_Y = 80.0f;
constexpr float THIRD_NODE_X = 50.0f;
constexpr float THIRD_NODE_Y = 140.0f;
constexpr float INPUT_WIDTH = 200.0f;
constexpr float INPUT_HEIGHT = 40.0f;
const std::string TEST_PAGE_NAME = "pages/Index";
const std::string TEST_RULE_SET_ID = "default_scene_rules";
const std::string TEST_RULE_ID = "text_editor_rule_001";
const std::string FIRST_INPUT_TEXT = "account";
const std::string SECOND_INPUT_TEXT = "password";
const std::string FIRST_PLACEHOLDER_TEXT = "input account";
const std::u16string FIRST_PLACEHOLDER_TEXT_U16 = u"input account";

std::string BuildRuleJson(bool includeUnfocusable = false, bool includeText = false,
    bool deduplicate = true, int32_t minReportIntervalMs = DEFAULT_MIN_REPORT_INTERVAL_MS)
{
    return std::string(R"({
        "ruleSetId": "default_scene_rules",
        "globalConfig": {
            "includeUnfocusableTextInput": )") + (includeUnfocusable ? "true" : "false") + R"(
        },
        "sourceConfig": {
            "arkui": true,
            "web": false,
            "uiExtension": false
        },
        "webRules": {
            "reserved": true
        },
        "rules": [
            {
                "ruleId": "text_editor_rule_001",
                "sceneType": "TEXT_EDITOR",
                "enabled": true,
                "scope": {
                    "onlyVisible": true
                },
                "selector": {
                    "nodeTypes": ["TextInput", "TextArea", "Search", "RichEditor"]
                },
                "condition": {
                    "operator": "COUNT_GTE",
                    "threshold": )" + std::to_string(MATCH_THRESHOLD) + R"(
                },
                "report": {
                    "includeNodeIds": true,
                    "includeNodeTypes": true,
                    "includeRect": true,
                    "includeFocusable": true,
                    "includeText": )" + (includeText ? "true" : "false") + R"(
                },
                "policy": {
                    "reportOnRegister": true,
                    "reportOnTextInputAttached": true,
                    "deduplicate": )" + (deduplicate ? "true" : "false") + R"(,
                    "minReportIntervalMs": )" + std::to_string(minReportIntervalMs) + R"(
                }
            }
        ]
    })";
}

std::string BuildInvalidRuleJson(const std::string& sceneType, const std::string& operatorName, int32_t threshold)
{
    return std::string(R"({
        "ruleSetId": "default_scene_rules",
        "rules": [
            {
                "ruleId": "text_editor_rule_001",
                "sceneType": ")") + sceneType + R"(",
                "selector": {
                    "nodeTypes": ["TextInput"]
                },
                "condition": {
                    "operator": ")" + operatorName + R"(",
                    "threshold": )" + std::to_string(threshold) + R"(
                }
            }
        ]
    })";
}

RefPtr<FrameNode> CreateTestNodeWithPattern(
    const std::string& tag, int32_t nodeId, const RectF& paintRect, const RefPtr<Pattern>& pattern,
    bool focusable = true)
{
    auto node = FrameNode::CreateFrameNode(tag, nodeId, pattern);
    if (!node) {
        return nullptr;
    }
    node->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
    node->SetActive(true);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameOffset(OffsetF(paintRect.GetX(), paintRect.GetY()));
    geometryNode->SetFrameSize(SizeF(paintRect.Width(), paintRect.Height()));
    node->SetGeometryNode(geometryNode);
    auto renderContext = AceType::MakeRefPtr<MockRenderContext>();
    renderContext->SetPaintRectWithTransform(paintRect);
    node->renderContext_ = renderContext;

    auto focusHub = node->GetOrCreateFocusHub();
    focusHub->SetFocusType(FocusType::NODE);
    focusHub->SetFocusable(focusable);
    return node;
}

RefPtr<FrameNode> CreateTestNode(
    const std::string& tag, int32_t nodeId, const RectF& paintRect, bool focusable = true)
{
    return CreateTestNodeWithPattern(tag, nodeId, paintRect, AceType::MakeRefPtr<Pattern>(), focusable);
}

RefPtr<FrameNode> CreatePageRoot()
{
    return CreateTestNode(V2::PAGE_ETS_TAG, TEST_ROOT_ID, RectF(ROOT_X, ROOT_Y, ROOT_WIDTH, ROOT_HEIGHT));
}

RefPtr<FrameNode> CreateTextInputNode(int32_t nodeId, const RectF& paintRect, bool focusable = true)
{
    return CreateTestNode(V2::TEXTINPUT_ETS_TAG, nodeId, paintRect, focusable);
}

RefPtr<FrameNode> CreateTextFieldNode(
    const std::string& tag, int32_t nodeId, const RectF& paintRect, const std::string& text, bool focusable = true,
    const std::u16string& placeholder = u"")
{
    auto node = CreateTestNodeWithPattern(tag, nodeId, paintRect, AceType::MakeRefPtr<TextFieldPattern>(), focusable);
    if (node) {
        auto pattern = node->GetPattern<TextFieldPattern>();
        if (pattern) {
            pattern->UpdateEditingValue(text, static_cast<int32_t>(text.length()));
        }
        auto layoutProperty = node->GetLayoutProperty<TextFieldLayoutProperty>();
        if (layoutProperty) {
            layoutProperty->UpdatePlaceholder(placeholder);
        }
    }
    return node;
}

void AddChild(const RefPtr<FrameNode>& parent, const RefPtr<FrameNode>& child)
{
    ASSERT_NE(parent, nullptr);
    ASSERT_NE(child, nullptr);
    child->MountToParent(parent);
}
} // namespace

class PageSceneRuleManagerTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void PageSceneRuleManagerTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void PageSceneRuleManagerTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: PageSceneRuleManager_RegisterRuleSet001
 * @tc.desc: Test valid rule registration, duplicate registration, includeText rule, and invalid rules.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneRuleManagerTestNg, PageSceneRuleManager_RegisterRuleSet001, TestSize.Level1)
{
    PageSceneRuleManager manager;
    EXPECT_EQ(manager.RegisterRuleSet(TEST_PROCESS_ID, "invalid json"), PAGE_SCENE_PARAM_INVALID);
    EXPECT_EQ(manager.RegisterRuleSet(TEST_PROCESS_ID, BuildRuleJson()), PAGE_SCENE_NO_ERROR);
    EXPECT_EQ(manager.RegisterRuleSet(TEST_PROCESS_ID, BuildRuleJson()), PAGE_SCENE_LAST_UNFINISH);

    EXPECT_EQ(manager.RegisterRuleSet(SECOND_PROCESS_ID, BuildRuleJson(false, true)), PAGE_SCENE_NO_ERROR);
    manager.ClearProcess(SECOND_PROCESS_ID);
    EXPECT_EQ(manager.RegisterRuleSet(
        SECOND_PROCESS_ID, BuildInvalidRuleJson("TEXT_EDITOR", "COUNT_GT", MATCH_THRESHOLD)), PAGE_SCENE_PARAM_INVALID);
    EXPECT_EQ(manager.RegisterRuleSet(
        SECOND_PROCESS_ID, BuildInvalidRuleJson("UNKNOWN_SCENE", "COUNT_GTE", MATCH_THRESHOLD)),
        PAGE_SCENE_PARAM_INVALID);
    EXPECT_EQ(manager.RegisterRuleSet(
        SECOND_PROCESS_ID, BuildInvalidRuleJson("TEXT_EDITOR", "COUNT_GTE", INVALID_THRESHOLD)),
        PAGE_SCENE_PARAM_INVALID);
}

/**
 * @tc.name: PageSceneRuleManager_BeginGetPageScene001
 * @tc.desc: Test registered ruleSet Get, one-shot ruleJson Get, pending busy, and unregister cleanup.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneRuleManagerTestNg, PageSceneRuleManager_BeginGetPageScene001, TestSize.Level1)
{
    PageSceneRuleManager manager;
    std::string ruleJson;

    EXPECT_EQ(manager.BeginGetPageScene(TEST_PROCESS_ID, "", ruleJson), PAGE_SCENE_PARAM_INVALID);
    EXPECT_EQ(manager.RegisterRuleSet(TEST_PROCESS_ID, BuildRuleJson()), PAGE_SCENE_NO_ERROR);
    EXPECT_EQ(manager.BeginGetPageScene(TEST_PROCESS_ID, TEST_RULE_SET_ID, ruleJson), PAGE_SCENE_NO_ERROR);
    EXPECT_EQ(ruleJson, BuildRuleJson());
    EXPECT_EQ(manager.BeginGetPageScene(TEST_PROCESS_ID, TEST_RULE_SET_ID, ruleJson), PAGE_SCENE_LAST_UNFINISH);

    manager.CompleteGetPageScene(TEST_PROCESS_ID);
    ruleJson.clear();
    EXPECT_EQ(manager.BeginGetPageScene(TEST_PROCESS_ID, BuildRuleJson(), ruleJson), PAGE_SCENE_NO_ERROR);
    EXPECT_EQ(ruleJson, BuildRuleJson());
    manager.CompleteGetPageScene(TEST_PROCESS_ID);

    EXPECT_EQ(manager.UnregisterRuleSet(TEST_PROCESS_ID, TEST_RULE_SET_ID), PAGE_SCENE_NO_ERROR);
    EXPECT_EQ(manager.BeginGetPageScene(TEST_PROCESS_ID, TEST_RULE_SET_ID, ruleJson), PAGE_SCENE_PARAM_INVALID);
}

/**
 * @tc.name: PageSceneRuleManager_MatchPageScene001
 * @tc.desc: Test TEXT_EDITOR matching JSON includes currentPageName, rect, focusable and no text payload by default.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneRuleManagerTestNg, PageSceneRuleManager_MatchPageScene001, TestSize.Level1)
{
    auto pageRoot = CreatePageRoot();
    AddChild(pageRoot, CreateTextInputNode(
        TEST_TEXT_INPUT_ID, RectF(FIRST_NODE_X, FIRST_NODE_Y, INPUT_WIDTH, INPUT_HEIGHT)));
    AddChild(pageRoot, CreateTestNode(
        V2::TEXTAREA_ETS_TAG, TEST_TEXT_AREA_ID, RectF(SECOND_NODE_X, SECOND_NODE_Y, INPUT_WIDTH, INPUT_HEIGHT)));

    PageSceneRuleManager manager;
    auto result = manager.MatchPageScene(TEST_PROCESS_ID, BuildRuleJson(), pageRoot, TEST_PAGE_NAME, false);

    ASSERT_TRUE(result.has_value());
    EXPECT_TRUE(result->matched);
    EXPECT_EQ(result->matchedCount, TWO_MATCHED_NODES);
    EXPECT_EQ(result->ruleSetId, TEST_RULE_SET_ID);
    EXPECT_EQ(result->ruleId, TEST_RULE_ID);
    EXPECT_EQ(result->sceneType, "TEXT_EDITOR");
    EXPECT_EQ(result->eventName, "TEXT_EDITOR");
    EXPECT_EQ(result->pageName, TEST_PAGE_NAME);

    auto sceneJson = JsonUtil::ParseJsonString(result->sceneJson);
    ASSERT_TRUE(sceneJson);
    EXPECT_EQ(sceneJson->GetString("currentPageName"), TEST_PAGE_NAME);
    EXPECT_TRUE(sceneJson->GetBool("matched"));
    EXPECT_EQ(sceneJson->GetInt("matchedCount"), TWO_MATCHED_NODES);
    EXPECT_EQ(sceneJson->GetValue("source")->GetString("type"), "ARKUI");
    EXPECT_TRUE(sceneJson->GetValue("text")->IsNull());
    EXPECT_TRUE(sceneJson->GetValue("tree")->IsNull());

    auto nodesJson = sceneJson->GetValue("nodes");
    ASSERT_TRUE(nodesJson);
    ASSERT_TRUE(nodesJson->IsArray());
    ASSERT_EQ(nodesJson->GetArraySize(), TWO_MATCHED_NODES);
    auto firstNode = nodesJson->GetArrayItem(0);
    ASSERT_TRUE(firstNode);
    EXPECT_EQ(firstNode->GetInt("nodeId"), TEST_TEXT_INPUT_ID);
    EXPECT_EQ(firstNode->GetString("nodeType"), "TextInput");
    EXPECT_TRUE(firstNode->GetBool("focusable"));
    EXPECT_TRUE(firstNode->GetValue("text")->IsNull());
    auto rectJson = firstNode->GetValue("rect");
    ASSERT_TRUE(rectJson);
    EXPECT_EQ(rectJson->GetDouble("x"), FIRST_NODE_X);
    EXPECT_EQ(rectJson->GetDouble("y"), FIRST_NODE_Y);
    EXPECT_EQ(rectJson->GetDouble("width"), INPUT_WIDTH);
    EXPECT_EQ(rectJson->GetDouble("height"), INPUT_HEIGHT);
}

/**
 * @tc.name: PageSceneRuleManager_MatchPageScene002
 * @tc.desc: Test unfocusable text input filtering and includeUnfocusableTextInput configuration.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneRuleManagerTestNg, PageSceneRuleManager_MatchPageScene002, TestSize.Level1)
{
    auto pageRoot = CreatePageRoot();
    AddChild(pageRoot, CreateTextInputNode(
        TEST_TEXT_INPUT_ID, RectF(FIRST_NODE_X, FIRST_NODE_Y, INPUT_WIDTH, INPUT_HEIGHT)));
    AddChild(pageRoot, CreateTextInputNode(
        TEST_TEXT_AREA_ID, RectF(SECOND_NODE_X, SECOND_NODE_Y, INPUT_WIDTH, INPUT_HEIGHT), false));

    PageSceneRuleManager manager;
    auto unmatchedResult = manager.MatchPageScene(TEST_PROCESS_ID, BuildRuleJson(), pageRoot, TEST_PAGE_NAME, true);
    ASSERT_TRUE(unmatchedResult.has_value());
    EXPECT_FALSE(unmatchedResult->matched);
    EXPECT_EQ(unmatchedResult->matchedCount, ONE_MATCHED_NODE);

    auto matchedResult = manager.MatchPageScene(TEST_PROCESS_ID, BuildRuleJson(true), pageRoot, TEST_PAGE_NAME, false);
    ASSERT_TRUE(matchedResult.has_value());
    EXPECT_TRUE(matchedResult->matched);
    EXPECT_EQ(matchedResult->matchedCount, TWO_MATCHED_NODES);

    auto sceneJson = JsonUtil::ParseJsonString(matchedResult->sceneJson);
    ASSERT_TRUE(sceneJson);
    auto nodesJson = sceneJson->GetValue("nodes");
    ASSERT_TRUE(nodesJson);
    ASSERT_EQ(nodesJson->GetArraySize(), TWO_MATCHED_NODES);
    auto secondNode = nodesJson->GetArrayItem(1);
    ASSERT_TRUE(secondNode);
    EXPECT_FALSE(secondNode->GetBool("focusable"));
}

/**
 * @tc.name: PageSceneRuleManager_MatchPageScene003
 * @tc.desc: Test Search with inner SearchField, RichEditor matching,
 * duplicate report suppression, and ClearProcess reset.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneRuleManagerTestNg, PageSceneRuleManager_MatchPageScene003, TestSize.Level1)
{
    auto pageRoot = CreatePageRoot();
    auto searchNode = CreateTestNode(
        V2::SEARCH_ETS_TAG, TEST_SEARCH_ID, RectF(FIRST_NODE_X, FIRST_NODE_Y, INPUT_WIDTH, INPUT_HEIGHT));
    AddChild(searchNode, CreateTestNode(
        V2::SEARCH_Field_ETS_TAG, TEST_SEARCH_FIELD_ID, RectF(FIRST_NODE_X, FIRST_NODE_Y, INPUT_WIDTH, INPUT_HEIGHT)));
    AddChild(pageRoot, searchNode);
    AddChild(pageRoot, CreateTestNode(
        V2::RICH_EDITOR_ETS_TAG, TEST_RICH_EDITOR_ID, RectF(THIRD_NODE_X, THIRD_NODE_Y, INPUT_WIDTH, INPUT_HEIGHT)));

    PageSceneRuleManager manager;
    EXPECT_TRUE(manager.IsTextInputNodeType(V2::SEARCH_Field_ETS_TAG));
    EXPECT_TRUE(manager.IsTextInputNodeType(V2::RICH_EDITOR_ETS_TAG));
    EXPECT_FALSE(manager.IsTextInputNodeType(V2::TEXT_ETS_TAG));

    auto result = manager.MatchPageScene(TEST_PROCESS_ID, BuildRuleJson(), pageRoot, TEST_PAGE_NAME, false);
    ASSERT_TRUE(result.has_value());
    EXPECT_TRUE(result->matched);
    EXPECT_EQ(result->matchedCount, TWO_MATCHED_NODES);

    auto sceneJson = JsonUtil::ParseJsonString(result->sceneJson);
    ASSERT_TRUE(sceneJson);
    auto firstNode = sceneJson->GetValue("nodes")->GetArrayItem(0);
    ASSERT_TRUE(firstNode);
    EXPECT_EQ(firstNode->GetInt("nodeId"), TEST_SEARCH_ID);
    EXPECT_EQ(firstNode->GetString("nodeType"), "Search");

    EXPECT_TRUE(manager.ShouldReport(TEST_PROCESS_ID, result.value()));
    EXPECT_FALSE(manager.ShouldReport(TEST_PROCESS_ID, result.value()));
    manager.ClearProcess(TEST_PROCESS_ID);
    EXPECT_TRUE(manager.ShouldReport(TEST_PROCESS_ID, result.value()));
}

/**
 * @tc.name: PageSceneRuleManager_MatchPageScene004
 * @tc.desc: Test inner SearchField is not counted as another input control under Search.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneRuleManagerTestNg, PageSceneRuleManager_MatchPageScene004, TestSize.Level1)
{
    auto pageRoot = CreatePageRoot();
    auto searchNode = CreateTestNode(
        V2::SEARCH_ETS_TAG, TEST_SEARCH_ID, RectF(FIRST_NODE_X, FIRST_NODE_Y, INPUT_WIDTH, INPUT_HEIGHT));
    AddChild(searchNode, CreateTestNode(
        V2::SEARCH_Field_ETS_TAG, TEST_SEARCH_FIELD_ID, RectF(FIRST_NODE_X, FIRST_NODE_Y, INPUT_WIDTH, INPUT_HEIGHT)));
    AddChild(pageRoot, searchNode);

    PageSceneRuleManager manager;
    auto result = manager.MatchPageScene(TEST_PROCESS_ID, BuildRuleJson(), pageRoot, TEST_PAGE_NAME, true);
    ASSERT_TRUE(result.has_value());
    EXPECT_FALSE(result->matched);
    EXPECT_EQ(result->matchedCount, ONE_MATCHED_NODE);

    auto sceneJson = JsonUtil::ParseJsonString(result->sceneJson);
    ASSERT_TRUE(sceneJson);
    auto nodesJson = sceneJson->GetValue("nodes");
    ASSERT_TRUE(nodesJson);
    ASSERT_EQ(nodesJson->GetArraySize(), ONE_MATCHED_NODE);
    auto firstNode = nodesJson->GetArrayItem(0);
    ASSERT_TRUE(firstNode);
    EXPECT_EQ(firstNode->GetInt("nodeId"), TEST_SEARCH_ID);
    EXPECT_EQ(firstNode->GetString("nodeType"), "Search");
}

/**
 * @tc.name: PageSceneRuleManager_MatchPageScene005
 * @tc.desc: Test TEXT_EDITOR matching JSON includes placeholder or input text when includeText is true.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneRuleManagerTestNg, PageSceneRuleManager_MatchPageScene005, TestSize.Level1)
{
    auto pageRoot = CreatePageRoot();
    AddChild(pageRoot, CreateTextFieldNode(
        V2::TEXTINPUT_ETS_TAG, TEST_TEXT_INPUT_ID, RectF(FIRST_NODE_X, FIRST_NODE_Y, INPUT_WIDTH, INPUT_HEIGHT),
        "", true, FIRST_PLACEHOLDER_TEXT_U16));
    AddChild(pageRoot, CreateTextFieldNode(
        V2::TEXTAREA_ETS_TAG, TEST_TEXT_AREA_ID, RectF(SECOND_NODE_X, SECOND_NODE_Y, INPUT_WIDTH, INPUT_HEIGHT),
        SECOND_INPUT_TEXT));

    PageSceneRuleManager manager;
    auto result = manager.MatchPageScene(TEST_PROCESS_ID, BuildRuleJson(false, true), pageRoot, TEST_PAGE_NAME, false);

    ASSERT_TRUE(result.has_value());
    EXPECT_TRUE(result->matched);
    EXPECT_EQ(result->matchedCount, TWO_MATCHED_NODES);

    auto sceneJson = JsonUtil::ParseJsonString(result->sceneJson);
    ASSERT_TRUE(sceneJson);
    EXPECT_TRUE(sceneJson->GetValue("tree")->IsNull());
    auto nodesJson = sceneJson->GetValue("nodes");
    ASSERT_TRUE(nodesJson);
    ASSERT_TRUE(nodesJson->IsArray());
    ASSERT_EQ(nodesJson->GetArraySize(), TWO_MATCHED_NODES);
    auto firstNode = nodesJson->GetArrayItem(0);
    auto secondNode = nodesJson->GetArrayItem(1);
    ASSERT_TRUE(firstNode);
    ASSERT_TRUE(secondNode);
    EXPECT_EQ(firstNode->GetString("text"), FIRST_PLACEHOLDER_TEXT);
    EXPECT_EQ(secondNode->GetString("text"), SECOND_INPUT_TEXT);
}
} // namespace OHOS::Ace::NG
