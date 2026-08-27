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
#include "base/utils/utf_helper.h"

#define private public
#define protected public
#include "core/components_ng/base/frame_node.h"
#undef private
#undef protected

#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/manager/page_scene/page_scene_rule_manager.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_layout_property.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
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
constexpr int32_t TEST_PIPELINE_ROOT_ID = 2006;
constexpr int32_t TEST_STAGE_ID = 2007;
constexpr int32_t TEST_DIALOG_ID = 2008;
constexpr int32_t TEST_OVERLAY_ID = 2009;
constexpr int32_t TEST_DIALOG_INPUT_ID = 2010;
constexpr int32_t TEST_OVERLAY_INPUT_ID = 2011;
constexpr int32_t TEST_ATOMIC_NODE_ID = 2012;
constexpr int32_t TEST_ATOMIC_ROOT_ID = 2013;
constexpr int32_t TEST_STAGE_WRAPPER_ID = 2014;
constexpr int32_t TEST_MENU_BAR_ID = 2015;
constexpr int32_t TEST_MENU_INPUT_ID = 2016;
constexpr int32_t MATCH_THRESHOLD = 2;
constexpr int32_t INVALID_THRESHOLD = 0;
constexpr int32_t DEFAULT_MIN_REPORT_INTERVAL_MS = 500;
constexpr int32_t ONE_MATCHED_NODE = 1;
constexpr int32_t TWO_MATCHED_NODES = 2;
constexpr int32_t THREE_MATCHED_NODES = 3;
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
constexpr float OFFSCREEN_NODE_Y = ROOT_HEIGHT + INPUT_HEIGHT;
constexpr float MOVED_NODE_OFFSET = 100.0f;
const std::string TEST_PAGE_NAME = "pages/Index";
const std::string TEST_RULE_SET_ID = "default_scene_rules";
const std::string TEST_RULE_ID = "text_editor_rule_001";
const std::string TEXT_EDITOR_EVENT = "TEXT_EDITOR";
const std::string TEXT_EDITOR_EXIT_EVENT = "TEXT_EDITOR_EXIT";
const std::string FIRST_INPUT_TEXT = "account";
const std::string SECOND_INPUT_TEXT = "password";
const std::string FIRST_PLACEHOLDER_TEXT = "input account";
const std::u16string FIRST_PLACEHOLDER_TEXT_U16 = u"input account";
const std::string EMPTY_RULES_JSON = R"({
    "version": 1,
    "ruleSetId": "empty_scene_rules",
    "rules": []
})";

std::string BuildRuleJson(bool includeUnfocusable = false, bool includeText = false,
    bool deduplicate = true, int32_t minReportIntervalMs = DEFAULT_MIN_REPORT_INTERVAL_MS,
    bool onlyVisible = true, bool rectCulling = false, bool includeRect = true)
{
    return std::string(R"({
        "version": 1,
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
                    "onlyVisible":)" + (onlyVisible ? "true" : "false") + R"(,
                    "rectCulling":)" + (rectCulling ? "true" : "false") + R"(
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
                    "includeRect": )" + (includeRect ? "true" : "false") + R"(,
                    "includeFocusable": true,
                    "includeText": )" + (includeText ? "true" : "false") + R"(
                },
                "policy": {
                    "reportOnRegister": true,
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
        "version": 1,
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

std::string BuildUnsupportedVersionRuleJson()
{
    return R"({
        "version": 2,
        "ruleSetId": "default_scene_rules",
        "rules": [
            {
                "ruleId": "text_editor_rule_001",
                "sceneType": "TEXT_EDITOR",
                "selector": {
                    "nodeTypes": ["TextInput"]
                },
                "condition": {
                    "operator": "COUNT_GTE",
                    "threshold": 2
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

DumpStartNodeSet BuildStartNodes(const RefPtr<FrameNode>& root)
{
    DumpStartNodeSet set;
    set.dumpBeginNode = root;
    if (root) {
        set.pageStartNodes.push_back(root);
    }
    return set;
}

RefPtr<FrameNode> CreateTextInputNode(int32_t nodeId, const RectF& paintRect, bool focusable = true)
{
    return CreateTestNode(V2::TEXTINPUT_ETS_TAG, nodeId, paintRect, focusable);
}

RefPtr<FrameNode> CreateTextFieldNode(
    const std::string& tag, int32_t nodeId, const RectF& paintRect, const std::string& text, bool focusable = true,
    const std::u16string& placeholder = u"", TextInputType inputType = TextInputType::UNSPECIFIED,
    TextContentType contentType = TextContentType::UNSPECIFIED)
{
    auto node = CreateTestNodeWithPattern(tag, nodeId, paintRect, AceType::MakeRefPtr<TextFieldPattern>(), focusable);
    if (node) {
        auto pattern = node->GetPattern<TextFieldPattern>();
        if (pattern) {
            pattern->SetTextInputFlag(tag != V2::TEXTAREA_ETS_TAG);
            pattern->UpdateEditingValue(text, static_cast<int32_t>(text.length()));
        }
        auto layoutProperty = node->GetLayoutProperty<TextFieldLayoutProperty>();
        if (layoutProperty) {
            layoutProperty->UpdatePlaceholder(placeholder);
            if (tag != V2::TEXTAREA_ETS_TAG) {
                layoutProperty->UpdateMaxLines(1);
            }
            layoutProperty->UpdateTextInputType(inputType);
            layoutProperty->UpdateTextContentType(contentType);
        }
    }
    return node;
}

RefPtr<FrameNode> CreateRichEditorNode(int32_t nodeId, const RectF& paintRect, const std::string& placeholder)
{
    auto node = CreateTestNodeWithPattern(
        V2::RICH_EDITOR_ETS_TAG, nodeId, paintRect, AceType::MakeRefPtr<RichEditorPattern>());
    if (node) {
        auto layoutProperty = node->GetLayoutProperty<RichEditorLayoutProperty>();
        if (layoutProperty) {
            layoutProperty->UpdatePlaceholder(UtfUtils::Str8ToStr16(placeholder));
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

void UpdateNodeRect(const RefPtr<FrameNode>& node, const RectF& paintRect)
{
    ASSERT_NE(node, nullptr);
    auto geometryNode = node->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameOffset(OffsetF(paintRect.GetX(), paintRect.GetY()));
    geometryNode->SetFrameSize(SizeF(paintRect.Width(), paintRect.Height()));
    auto renderContext = AceType::DynamicCast<MockRenderContext>(node->GetRenderContext());
    ASSERT_NE(renderContext, nullptr);
    renderContext->SetPaintRectWithTransform(paintRect);
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
    EXPECT_EQ(manager.RegisterRuleSet(TEST_PROCESS_ID, EMPTY_RULES_JSON), PAGE_SCENE_PARAM_INVALID);
    EXPECT_EQ(manager.RegisterRuleSet(TEST_PROCESS_ID, BuildRuleJson()), PAGE_SCENE_NO_ERROR);
    EXPECT_EQ(manager.RegisterRuleSet(TEST_PROCESS_ID, BuildRuleJson()), PAGE_SCENE_LAST_UNFINISH);

    EXPECT_EQ(manager.RegisterRuleSet(SECOND_PROCESS_ID, BuildRuleJson(false, true)), PAGE_SCENE_NO_ERROR);
    manager.ClearProcess(SECOND_PROCESS_ID);
    EXPECT_EQ(manager.RegisterRuleSet(SECOND_PROCESS_ID, BuildUnsupportedVersionRuleJson()), PAGE_SCENE_PARAM_INVALID);
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
    auto result = manager.MatchPageScene(
        TEST_PROCESS_ID, BuildRuleJson(), BuildStartNodes(pageRoot), TEST_PAGE_NAME, false);

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
    auto unmatchedResult = manager.MatchPageScene(
        TEST_PROCESS_ID, BuildRuleJson(), BuildStartNodes(pageRoot), TEST_PAGE_NAME, true);
    ASSERT_TRUE(unmatchedResult.has_value());
    EXPECT_FALSE(unmatchedResult->matched);
    EXPECT_EQ(unmatchedResult->matchedCount, ONE_MATCHED_NODE);

    auto matchedResult = manager.MatchPageScene(
        TEST_PROCESS_ID, BuildRuleJson(true), BuildStartNodes(pageRoot), TEST_PAGE_NAME, false);
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
    AddChild(searchNode, CreateTextFieldNode(V2::SEARCH_Field_ETS_TAG, TEST_SEARCH_FIELD_ID,
        RectF(FIRST_NODE_X, FIRST_NODE_Y, INPUT_WIDTH, INPUT_HEIGHT), FIRST_INPUT_TEXT, true,
        FIRST_PLACEHOLDER_TEXT_U16, TextInputType::PHONE, TextContentType::PHONE_NUMBER));
    AddChild(pageRoot, searchNode);
    AddChild(pageRoot, CreateRichEditorNode(
        TEST_RICH_EDITOR_ID, RectF(THIRD_NODE_X, THIRD_NODE_Y, INPUT_WIDTH, INPUT_HEIGHT), "rich placeholder"));

    PageSceneRuleManager manager;
    EXPECT_FALSE(manager.IsTextInputNodeType(V2::SEARCH_Field_ETS_TAG));
    EXPECT_TRUE(manager.IsTextInputNodeType(V2::RICH_EDITOR_ETS_TAG));
    EXPECT_FALSE(manager.IsTextInputNodeType(V2::TEXT_ETS_TAG));

    auto result = manager.MatchPageScene(
        TEST_PROCESS_ID, BuildRuleJson(false, true), BuildStartNodes(pageRoot), TEST_PAGE_NAME, false);
    ASSERT_TRUE(result.has_value());
    EXPECT_TRUE(result->matched);
    EXPECT_EQ(result->matchedCount, TWO_MATCHED_NODES);

    auto sceneJson = JsonUtil::ParseJsonString(result->sceneJson);
    ASSERT_TRUE(sceneJson);
    auto nodesJson = sceneJson->GetValue("nodes");
    ASSERT_TRUE(nodesJson);
    auto firstNode = nodesJson->GetArrayItem(0);
    ASSERT_TRUE(firstNode);
    EXPECT_EQ(firstNode->GetInt("nodeId"), TEST_SEARCH_ID);
    EXPECT_EQ(firstNode->GetString("nodeType"), "Search");
    EXPECT_EQ(firstNode->GetString("text"), FIRST_INPUT_TEXT);
    EXPECT_EQ(firstNode->GetString("placeholder"), FIRST_PLACEHOLDER_TEXT);
    EXPECT_EQ(firstNode->GetString("contentType"), "PHONE_NUMBER");
    EXPECT_EQ(firstNode->GetString("inputType"), "PhoneNumber");

    auto secondNode = nodesJson->GetArrayItem(1);
    ASSERT_TRUE(secondNode);
    EXPECT_EQ(secondNode->GetString("nodeType"), "RichEditor");
    EXPECT_EQ(secondNode->GetString("text"), "");
    EXPECT_EQ(secondNode->GetString("placeholder"), "rich placeholder");
    EXPECT_EQ(secondNode->GetString("contentType"), "");
    EXPECT_EQ(secondNode->GetString("inputType"), "");

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
    auto result = manager.MatchPageScene(
        TEST_PROCESS_ID, BuildRuleJson(), BuildStartNodes(pageRoot), TEST_PAGE_NAME, true);
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
        "", true, FIRST_PLACEHOLDER_TEXT_U16, TextInputType::EMAIL_ADDRESS, TextContentType::EMAIL_ADDRESS));
    AddChild(pageRoot, CreateTextFieldNode(
        V2::TEXTAREA_ETS_TAG, TEST_TEXT_AREA_ID, RectF(SECOND_NODE_X, SECOND_NODE_Y, INPUT_WIDTH, INPUT_HEIGHT),
        SECOND_INPUT_TEXT, true, u"", TextInputType::NUMBER, TextContentType::PHONE_NUMBER));

    PageSceneRuleManager manager;
    auto result = manager.MatchPageScene(
        TEST_PROCESS_ID, BuildRuleJson(false, true), BuildStartNodes(pageRoot), TEST_PAGE_NAME, false);

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
    EXPECT_EQ(firstNode->GetString("text"), "");
    EXPECT_EQ(firstNode->GetString("placeholder"), FIRST_PLACEHOLDER_TEXT);
    EXPECT_EQ(firstNode->GetString("contentType"), "EMAIL_ADDRESS");
    EXPECT_EQ(firstNode->GetString("inputType"), "Email");
    EXPECT_EQ(secondNode->GetString("text"), SECOND_INPUT_TEXT);
    EXPECT_EQ(secondNode->GetString("placeholder"), "");
    EXPECT_EQ(secondNode->GetString("contentType"), "PHONE_NUMBER");
    EXPECT_EQ(secondNode->GetString("inputType"), "NUMBER");
}

/**
 * @tc.name: PageSceneRuleManager_MatchPageScene006
 * @tc.desc: Test exit event is reported once after a reported TEXT_EDITOR scene becomes unmatched.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneRuleManagerTestNg, PageSceneRuleManager_MatchPageScene006, TestSize.Level1)
{
    auto unmatchedRoot = CreatePageRoot();
    AddChild(unmatchedRoot, CreateTextInputNode(
        TEST_TEXT_INPUT_ID, RectF(FIRST_NODE_X, FIRST_NODE_Y, INPUT_WIDTH, INPUT_HEIGHT)));

    PageSceneRuleManager manager;
    auto initialUnmatchedResult = manager.MatchPageScene(
        TEST_PROCESS_ID, BuildRuleJson(), BuildStartNodes(unmatchedRoot), TEST_PAGE_NAME, false);
    ASSERT_TRUE(initialUnmatchedResult.has_value());
    EXPECT_FALSE(initialUnmatchedResult->matched);
    EXPECT_EQ(initialUnmatchedResult->eventName, TEXT_EDITOR_EXIT_EVENT);
    EXPECT_FALSE(manager.ShouldReport(TEST_PROCESS_ID, initialUnmatchedResult.value()));

    auto matchedRoot = CreatePageRoot();
    AddChild(matchedRoot, CreateTextInputNode(
        TEST_TEXT_INPUT_ID, RectF(FIRST_NODE_X, FIRST_NODE_Y, INPUT_WIDTH, INPUT_HEIGHT)));
    AddChild(matchedRoot, CreateTextInputNode(
        TEST_TEXT_AREA_ID, RectF(SECOND_NODE_X, SECOND_NODE_Y, INPUT_WIDTH, INPUT_HEIGHT)));
    auto matchedResult = manager.MatchPageScene(
        TEST_PROCESS_ID, BuildRuleJson(), BuildStartNodes(matchedRoot), TEST_PAGE_NAME, false);
    ASSERT_TRUE(matchedResult.has_value());
    EXPECT_TRUE(matchedResult->matched);
    EXPECT_EQ(matchedResult->eventName, TEXT_EDITOR_EVENT);
    EXPECT_TRUE(manager.ShouldReport(TEST_PROCESS_ID, matchedResult.value()));

    auto exitResult = manager.MatchPageScene(
        TEST_PROCESS_ID, BuildRuleJson(), BuildStartNodes(unmatchedRoot), TEST_PAGE_NAME, false);
    ASSERT_TRUE(exitResult.has_value());
    EXPECT_FALSE(exitResult->matched);
    EXPECT_EQ(exitResult->matchedCount, ONE_MATCHED_NODE);
    EXPECT_EQ(exitResult->eventName, TEXT_EDITOR_EXIT_EVENT);
    auto exitJson = JsonUtil::ParseJsonString(exitResult->sceneJson);
    ASSERT_TRUE(exitJson);
    EXPECT_FALSE(exitJson->GetBool("matched"));
    EXPECT_EQ(exitJson->GetString("eventName"), TEXT_EDITOR_EXIT_EVENT);
    EXPECT_EQ(exitJson->GetInt("matchedCount"), ONE_MATCHED_NODE);
    EXPECT_TRUE(manager.ShouldReport(TEST_PROCESS_ID, exitResult.value()));
    EXPECT_FALSE(manager.ShouldReport(TEST_PROCESS_ID, exitResult.value()));

    auto getResult = manager.MatchPageScene(
        TEST_PROCESS_ID, BuildRuleJson(), BuildStartNodes(unmatchedRoot), TEST_PAGE_NAME, true);
    ASSERT_TRUE(getResult.has_value());
    EXPECT_FALSE(getResult->matched);
    EXPECT_EQ(getResult->eventName, TEXT_EDITOR_EVENT);

    auto reenterResult = manager.MatchPageScene(
        TEST_PROCESS_ID, BuildRuleJson(), BuildStartNodes(matchedRoot), TEST_PAGE_NAME, false);
    ASSERT_TRUE(reenterResult.has_value());
    EXPECT_TRUE(reenterResult->matched);
    EXPECT_TRUE(manager.ShouldReport(TEST_PROCESS_ID, reenterResult.value()));
}

/**
 * @tc.name: PageSceneRuleManager_MatchPageScene007
 * @tc.desc: Test rectCulling filters inputs outside the page viewport independently of onlyVisible.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneRuleManagerTestNg, PageSceneRuleManager_MatchPageScene007, TestSize.Level1)
{
    auto pageRoot = CreatePageRoot();
    AddChild(pageRoot, CreateTextInputNode(
        TEST_TEXT_INPUT_ID, RectF(FIRST_NODE_X, FIRST_NODE_Y, INPUT_WIDTH, INPUT_HEIGHT)));
    AddChild(pageRoot, CreateTextInputNode(
        TEST_TEXT_AREA_ID, RectF(SECOND_NODE_X, OFFSCREEN_NODE_Y, INPUT_WIDTH, INPUT_HEIGHT)));

    PageSceneRuleManager manager;
    auto visibleOnlyResult = manager.MatchPageScene(
        TEST_PROCESS_ID, BuildRuleJson(false, false, true, DEFAULT_MIN_REPORT_INTERVAL_MS, true, true),
        BuildStartNodes(pageRoot), TEST_PAGE_NAME, true);
    ASSERT_TRUE(visibleOnlyResult.has_value());
    EXPECT_FALSE(visibleOnlyResult->matched);
    EXPECT_EQ(visibleOnlyResult->matchedCount, ONE_MATCHED_NODE);
    ASSERT_EQ(visibleOnlyResult->nodeIds.size(), ONE_MATCHED_NODE);
    EXPECT_EQ(visibleOnlyResult->nodeIds.front(), TEST_TEXT_INPUT_ID);

    auto componentVisibleResult = manager.MatchPageScene(
        TEST_PROCESS_ID, BuildRuleJson(false, false, true, DEFAULT_MIN_REPORT_INTERVAL_MS, true, false),
        BuildStartNodes(pageRoot), TEST_PAGE_NAME, false);
    ASSERT_TRUE(componentVisibleResult.has_value());
    EXPECT_TRUE(componentVisibleResult->matched);
    EXPECT_EQ(componentVisibleResult->matchedCount, TWO_MATCHED_NODES);

    auto allNodesResult = manager.MatchPageScene(
        TEST_PROCESS_ID, BuildRuleJson(false, false, true, DEFAULT_MIN_REPORT_INTERVAL_MS, false, false),
        BuildStartNodes(pageRoot), TEST_PAGE_NAME, false);
    ASSERT_TRUE(allNodesResult.has_value());
    EXPECT_TRUE(allNodesResult->matched);
    EXPECT_EQ(allNodesResult->matchedCount, TWO_MATCHED_NODES);
}

/**
 * @tc.name: PageSceneRuleManager_MatchPageScene014
 * @tc.desc: Test onlyVisible filters a node when its own opacity or an ancestor opacity is zero.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneRuleManagerTestNg, PageSceneRuleManager_MatchPageScene014, TestSize.Level1)
{
    auto pageRoot = CreatePageRoot();
    auto transparentNode = CreateTextInputNode(
        TEST_TEXT_INPUT_ID, RectF(FIRST_NODE_X, FIRST_NODE_Y, INPUT_WIDTH, INPUT_HEIGHT));
    auto visibleNode = CreateTextInputNode(
        TEST_TEXT_AREA_ID, RectF(SECOND_NODE_X, SECOND_NODE_Y, INPUT_WIDTH, INPUT_HEIGHT));
    AddChild(pageRoot, transparentNode);
    AddChild(pageRoot, visibleNode);
    transparentNode->GetRenderContext()->UpdateOpacity(0.0);

    PageSceneRuleManager manager;
    auto onlyVisibleResult = manager.MatchPageScene(
        TEST_PROCESS_ID, BuildRuleJson(), BuildStartNodes(pageRoot), TEST_PAGE_NAME, true);
    ASSERT_TRUE(onlyVisibleResult.has_value());
    EXPECT_FALSE(onlyVisibleResult->matched);
    EXPECT_EQ(onlyVisibleResult->matchedCount, ONE_MATCHED_NODE);

    auto rectOnlyResult = manager.MatchPageScene(
        TEST_PROCESS_ID, BuildRuleJson(false, false, true, DEFAULT_MIN_REPORT_INTERVAL_MS, false, true),
        BuildStartNodes(pageRoot), TEST_PAGE_NAME, true);
    ASSERT_TRUE(rectOnlyResult.has_value());
    EXPECT_TRUE(rectOnlyResult->matched);
    EXPECT_EQ(rectOnlyResult->matchedCount, TWO_MATCHED_NODES);
}

/**
 * @tc.name: PageSceneRuleManager_MatchPageScene008
 * @tc.desc: Test coordinate-only changes are deduplicated when the matched node ID list is unchanged.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneRuleManagerTestNg, PageSceneRuleManager_MatchPageScene008, TestSize.Level1)
{
    auto pageRoot = CreatePageRoot();
    auto textInputNode = CreateTextInputNode(
        TEST_TEXT_INPUT_ID, RectF(FIRST_NODE_X, FIRST_NODE_Y, INPUT_WIDTH, INPUT_HEIGHT));
    auto textAreaNode = CreateTextInputNode(
        TEST_TEXT_AREA_ID, RectF(SECOND_NODE_X, SECOND_NODE_Y, INPUT_WIDTH, INPUT_HEIGHT));
    AddChild(pageRoot, textInputNode);
    AddChild(pageRoot, textAreaNode);

    PageSceneRuleManager manager;
    auto initialResult = manager.MatchPageScene(TEST_PROCESS_ID,
        BuildRuleJson(false, false, true, 0), BuildStartNodes(pageRoot), TEST_PAGE_NAME, false);
    ASSERT_TRUE(initialResult.has_value());
    EXPECT_TRUE(manager.ShouldReport(TEST_PROCESS_ID, initialResult.value()));

    UpdateNodeRect(textInputNode, RectF(
        FIRST_NODE_X + MOVED_NODE_OFFSET, FIRST_NODE_Y + MOVED_NODE_OFFSET, INPUT_WIDTH, INPUT_HEIGHT));
    UpdateNodeRect(textAreaNode, RectF(
        SECOND_NODE_X + MOVED_NODE_OFFSET, SECOND_NODE_Y + MOVED_NODE_OFFSET, INPUT_WIDTH, INPUT_HEIGHT));
    auto movedResult = manager.MatchPageScene(TEST_PROCESS_ID,
        BuildRuleJson(false, false, true, 0), BuildStartNodes(pageRoot), TEST_PAGE_NAME, false);

    ASSERT_TRUE(movedResult.has_value());
    EXPECT_EQ(movedResult->nodeIds, initialResult->nodeIds);
    EXPECT_FALSE(manager.ShouldReport(TEST_PROCESS_ID, movedResult.value()));
}

/**
 * @tc.name: PageSceneRuleManager_MatchPageScene009
 * @tc.desc: Test leaving the viewport or replacing an attached input changes node IDs and produces a new state.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneRuleManagerTestNg, PageSceneRuleManager_MatchPageScene009, TestSize.Level1)
{
    auto matchedRoot = CreatePageRoot();
    AddChild(matchedRoot, CreateTextInputNode(
        TEST_TEXT_INPUT_ID, RectF(FIRST_NODE_X, FIRST_NODE_Y, INPUT_WIDTH, INPUT_HEIGHT)));
    auto textAreaNode = CreateTextInputNode(
        TEST_TEXT_AREA_ID, RectF(SECOND_NODE_X, SECOND_NODE_Y, INPUT_WIDTH, INPUT_HEIGHT));
    AddChild(matchedRoot, textAreaNode);

    PageSceneRuleManager manager;
    auto initialResult = manager.MatchPageScene(TEST_PROCESS_ID,
        BuildRuleJson(false, false, true, 0, true, true), BuildStartNodes(matchedRoot), TEST_PAGE_NAME, false);
    ASSERT_TRUE(initialResult.has_value());
    EXPECT_TRUE(manager.ShouldReport(TEST_PROCESS_ID, initialResult.value()));

    UpdateNodeRect(textAreaNode, RectF(SECOND_NODE_X, OFFSCREEN_NODE_Y, INPUT_WIDTH, INPUT_HEIGHT));
    auto offscreenResult = manager.MatchPageScene(TEST_PROCESS_ID,
        BuildRuleJson(false, false, true, 0, true, true), BuildStartNodes(matchedRoot), TEST_PAGE_NAME, false);
    ASSERT_TRUE(offscreenResult.has_value());
    EXPECT_FALSE(offscreenResult->matched);
    EXPECT_TRUE(manager.ShouldReport(TEST_PROCESS_ID, offscreenResult.value()));

    auto replacedRoot = CreatePageRoot();
    AddChild(replacedRoot, CreateTextInputNode(
        TEST_TEXT_INPUT_ID, RectF(FIRST_NODE_X, FIRST_NODE_Y, INPUT_WIDTH, INPUT_HEIGHT)));
    AddChild(replacedRoot, CreateTextInputNode(
        TEST_SEARCH_ID, RectF(SECOND_NODE_X, SECOND_NODE_Y, INPUT_WIDTH, INPUT_HEIGHT)));
    auto replacedResult = manager.MatchPageScene(TEST_PROCESS_ID,
        BuildRuleJson(false, false, true, 0, true, true), BuildStartNodes(replacedRoot), TEST_PAGE_NAME, false);
    ASSERT_TRUE(replacedResult.has_value());
    EXPECT_TRUE(replacedResult->matched);
    EXPECT_EQ(replacedResult->nodeIds, (std::vector<int32_t> { TEST_TEXT_INPUT_ID, TEST_SEARCH_ID }));
    EXPECT_TRUE(manager.ShouldReport(TEST_PROCESS_ID, replacedResult.value()));
}

/**
 * @tc.name: PageSceneRuleManager_MatchPageScene010
 * @tc.desc: Test traversal from pipeline root includes inputs under page, dialog and overlay branches.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneRuleManagerTestNg, PageSceneRuleManager_MatchPageScene010, TestSize.Level1)
{
    auto rootNode = CreateTestNode(
        V2::ROOT_ETS_TAG, TEST_PIPELINE_ROOT_ID, RectF(ROOT_X, ROOT_Y, ROOT_WIDTH, ROOT_HEIGHT));
    auto stageNode = CreateTestNode(
        V2::STAGE_ETS_TAG, TEST_STAGE_ID, RectF(ROOT_X, ROOT_Y, ROOT_WIDTH, ROOT_HEIGHT));
    auto pageRoot = CreatePageRoot();
    auto dialogNode = CreateTestNode(
        V2::DIALOG_ETS_TAG, TEST_DIALOG_ID, RectF(ROOT_X, ROOT_Y, ROOT_WIDTH, ROOT_HEIGHT));
    auto overlayNode = CreateTestNode(
        V2::OVERLAY_ETS_TAG, TEST_OVERLAY_ID, RectF(ROOT_X, ROOT_Y, ROOT_WIDTH, ROOT_HEIGHT));

    AddChild(rootNode, stageNode);
    AddChild(stageNode, pageRoot);
    AddChild(rootNode, dialogNode);
    AddChild(rootNode, overlayNode);
    AddChild(pageRoot, CreateTextInputNode(
        TEST_TEXT_INPUT_ID, RectF(FIRST_NODE_X, FIRST_NODE_Y, INPUT_WIDTH, INPUT_HEIGHT)));
    AddChild(dialogNode, CreateTestNode(
        V2::TEXTAREA_ETS_TAG, TEST_DIALOG_INPUT_ID,
        RectF(SECOND_NODE_X, SECOND_NODE_Y, INPUT_WIDTH, INPUT_HEIGHT)));
    AddChild(overlayNode, CreateTestNode(
        V2::SEARCH_ETS_TAG, TEST_OVERLAY_INPUT_ID,
        RectF(THIRD_NODE_X, THIRD_NODE_Y, INPUT_WIDTH, INPUT_HEIGHT)));

    PageSceneRuleManager manager;
    auto pageResult = manager.MatchPageScene(
        TEST_PROCESS_ID, BuildRuleJson(), BuildStartNodes(pageRoot), TEST_PAGE_NAME, true);
    ASSERT_TRUE(pageResult.has_value());
    EXPECT_FALSE(pageResult->matched);
    EXPECT_EQ(pageResult->matchedCount, ONE_MATCHED_NODE);
    EXPECT_EQ(pageResult->nodeIds, (std::vector<int32_t> { TEST_TEXT_INPUT_ID }));

    // Production-style start nodes: page branch (pageRoot) + overlay branches
    // (dialog, overlay). This mirrors GetDumpStartNodes output and avoids the
    // double count that would occur if rootNode were both a page start node
    // and an overlay parent.
    DumpStartNodeSet branchStartNodes;
    branchStartNodes.dumpBeginNode = rootNode;
    branchStartNodes.pageStartNodes.push_back(pageRoot);
    branchStartNodes.overlayNodes.push_back(dialogNode);
    branchStartNodes.overlayNodes.push_back(overlayNode);
    auto rootResult = manager.MatchPageScene(
        TEST_PROCESS_ID, BuildRuleJson(), branchStartNodes, TEST_PAGE_NAME, true);
    ASSERT_TRUE(rootResult.has_value());
    EXPECT_TRUE(rootResult->matched);
    EXPECT_EQ(rootResult->matchedCount, THREE_MATCHED_NODES);
    EXPECT_EQ(rootResult->nodeIds,
        (std::vector<int32_t> { TEST_TEXT_INPUT_ID, TEST_DIALOG_INPUT_ID, TEST_OVERLAY_INPUT_ID }));

    auto sceneJson = JsonUtil::ParseJsonString(rootResult->sceneJson);
    ASSERT_TRUE(sceneJson);
    EXPECT_EQ(sceneJson->GetInt("matchedCount"), THREE_MATCHED_NODES);
    auto nodesJson = sceneJson->GetValue("nodes");
    ASSERT_TRUE(nodesJson);
    ASSERT_EQ(nodesJson->GetArraySize(), THREE_MATCHED_NODES);
    EXPECT_EQ(nodesJson->GetArrayItem(0)->GetInt("nodeId"), TEST_TEXT_INPUT_ID);
    EXPECT_EQ(nodesJson->GetArrayItem(1)->GetInt("nodeId"), TEST_DIALOG_INPUT_ID);
    EXPECT_EQ(nodesJson->GetArrayItem(2)->GetInt("nodeId"), TEST_OVERLAY_INPUT_ID);
}

/**
 * @tc.name: PageSceneRuleManager_MatchPageScene011
 * @tc.desc: Test empty traversal roots preserve the historical nullopt result.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneRuleManagerTestNg, PageSceneRuleManager_MatchPageScene011, TestSize.Level1)
{
    PageSceneRuleManager manager;
    DumpStartNodeSet emptyStartNodes;
    emptyStartNodes.dumpBeginNode = CreatePageRoot();
    emptyStartNodes.atomicServiceRoot = CreateTestNode(
        V2::COLUMN_ETS_TAG, TEST_ATOMIC_ROOT_ID, RectF(ROOT_X, ROOT_Y, ROOT_WIDTH, ROOT_HEIGHT));
    emptyStartNodes.pageStartNodes.push_back(nullptr);
    emptyStartNodes.overlayNodes.push_back(nullptr);

    auto result = manager.MatchPageScene(
        TEST_PROCESS_ID, BuildRuleJson(), emptyStartNodes, TEST_PAGE_NAME, true);
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: PageSceneRuleManager_MatchPageScene012
 * @tc.desc: Test AtomicService page is counted once and its menu bar is outside PageScene scope.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneRuleManagerTestNg, PageSceneRuleManager_MatchPageScene012, TestSize.Level1)
{
    auto rootNode = CreateTestNode(
        V2::ROOT_ETS_TAG, TEST_PIPELINE_ROOT_ID, RectF(ROOT_X, ROOT_Y, ROOT_WIDTH, ROOT_HEIGHT));
    auto atomicNode = CreateTestNode(
        V2::ATOMIC_SERVICE_ETS_TAG, TEST_ATOMIC_NODE_ID, RectF(ROOT_X, ROOT_Y, ROOT_WIDTH, ROOT_HEIGHT));
    auto atomicRoot = CreateTestNode(
        V2::COLUMN_ETS_TAG, TEST_ATOMIC_ROOT_ID, RectF(ROOT_X, ROOT_Y, ROOT_WIDTH, ROOT_HEIGHT));
    auto stageWrapper = CreateTestNode(
        V2::COLUMN_ETS_TAG, TEST_STAGE_WRAPPER_ID, RectF(ROOT_X, ROOT_Y, ROOT_WIDTH, ROOT_HEIGHT));
    auto stageNode = CreateTestNode(
        V2::STAGE_ETS_TAG, TEST_STAGE_ID, RectF(ROOT_X, ROOT_Y, ROOT_WIDTH, ROOT_HEIGHT));
    auto pageRoot = CreatePageRoot();
    auto menuBar = CreateTestNode(
        V2::ROW_ETS_TAG, TEST_MENU_BAR_ID, RectF(ROOT_X, ROOT_Y, ROOT_WIDTH, ROOT_HEIGHT));
    atomicRoot->UpdateInspectorId("AtomicServiceContainerId");
    menuBar->UpdateInspectorId("AtomicServiceMenubarRowId");
    AddChild(rootNode, atomicNode);
    AddChild(atomicNode, atomicRoot);
    AddChild(atomicRoot, stageWrapper);
    AddChild(stageWrapper, stageNode);
    AddChild(stageNode, pageRoot);
    AddChild(atomicRoot, menuBar);
    AddChild(pageRoot, CreateTextInputNode(
        TEST_TEXT_INPUT_ID, RectF(FIRST_NODE_X, FIRST_NODE_Y, INPUT_WIDTH, INPUT_HEIGHT)));
    AddChild(menuBar, CreateTextInputNode(
        TEST_MENU_INPUT_ID, RectF(SECOND_NODE_X, SECOND_NODE_Y, INPUT_WIDTH, INPUT_HEIGHT)));
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto startNodes =
        DumpUtil::CollectInspectorStartNodes(rootNode, nullptr, pageRoot, overlayManager);

    PageSceneRuleManager manager;
    auto result = manager.MatchPageScene(
        TEST_PROCESS_ID, BuildRuleJson(), startNodes, TEST_PAGE_NAME, true);

    ASSERT_TRUE(result.has_value());
    EXPECT_FALSE(result->matched);
    EXPECT_EQ(result->matchedCount, ONE_MATCHED_NODE);
    EXPECT_EQ(result->nodeIds, (std::vector<int32_t> { TEST_TEXT_INPUT_ID }));
}

/**
 * @tc.name: PageSceneRuleManager_MatchPageScene013
 * @tc.desc: Test rect is omitted and not required when onlyVisible and includeRect are false.
 * @tc.type: FUNC
 */
HWTEST_F(PageSceneRuleManagerTestNg, PageSceneRuleManager_MatchPageScene013, TestSize.Level1)
{
    auto pageRoot = CreatePageRoot();
    AddChild(pageRoot, CreateTextInputNode(
        TEST_TEXT_INPUT_ID, RectF(FIRST_NODE_X, OFFSCREEN_NODE_Y, INPUT_WIDTH, INPUT_HEIGHT)));

    PageSceneRuleManager manager;
    auto result = manager.MatchPageScene(TEST_PROCESS_ID,
        BuildRuleJson(false, false, true, DEFAULT_MIN_REPORT_INTERVAL_MS, false, false, false),
        BuildStartNodes(pageRoot), TEST_PAGE_NAME, true);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->matchedCount, ONE_MATCHED_NODE);
    auto sceneJson = JsonUtil::ParseJsonString(result->sceneJson);
    ASSERT_TRUE(sceneJson);
    auto nodeJson = sceneJson->GetValue("nodes")->GetArrayItem(0);
    ASSERT_TRUE(nodeJson);
    EXPECT_TRUE(nodeJson->GetValue("rect")->IsNull());
}
} // namespace OHOS::Ace::NG
