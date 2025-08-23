/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "test/unittest/core/base/frame_node_test_ng.h"

#include "core/common/recorder/event_definition.h"
#include "core/components_ng/property/grid_property.h"
#include "core/common/recorder/event_recorder.h"
#include "core/common/recorder/node_data_cache.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/render/mock_canvas_image.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {} // namespace

/**
 * @tc.name: FrameNodeGetIsLayoutNode01
 * @tc.desc: Test the function GetIsLayoutNode
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetIsLayoutNode01, TestSize.Level1)
{
    /**
     * @tc.steps1: call the function GetIsLayoutNode.
     * @tc.expected: Value returned as expected.
     */
    RefPtr<FrameNode> node = FrameNode::CreateCommonNode("node", 1, false, AceType::MakeRefPtr<Pattern>());
    EXPECT_FALSE(node->GetIsLayoutNode());
}

/**
 * @tc.name: FrameNodeGetIsLayoutNode02
 * @tc.desc: Test the function GetIsLayoutNode
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetIsLayoutNode02, TestSize.Level1)
{
    /**
     * @tc.steps1: call the function GetIsLayoutNode.
     * @tc.expected: Value returned as expected.
     */
    RefPtr<FrameNode> node = FrameNode::CreateCommonNode("node", 1, true, AceType::MakeRefPtr<Pattern>());
    EXPECT_TRUE(node->GetIsLayoutNode());
}

/**
 * @tc.name: FrameNodeSetIsFindGetIsFind01
 * @tc.desc: Test the function SetIsFind GetIsFind
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeSetIsFindGetIsFind01, TestSize.Level1)
{
    /**
     * @tc.steps1: call the function SetIsFind GetIsFind.
     * @tc.expected: Value returned as expected.
     */
    RefPtr<FrameNode> node = FrameNode::CreateFrameNode("node", 1, AceType::MakeRefPtr<Pattern>());
    node->SetIsFind(true);
    EXPECT_TRUE(node->GetIsFind());
}

/**
 * @tc.name: FrameNodeSetIsFindGetIsFind02
 * @tc.desc: Test the function SetIsFind GetIsFind
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeSetIsFindGetIsFind02, TestSize.Level1)
{
    /**
     * @tc.steps1: call the function SetIsFind GetIsFind.
     * @tc.expected: Value returned as expected.
     */
    RefPtr<FrameNode> node = FrameNode::CreateFrameNode("node", 1, AceType::MakeRefPtr<Pattern>());
    node->SetIsFind(false);
    EXPECT_FALSE(node->GetIsFind());
}

/**
 * @tc.name: FrameNodeGetOneDepthVisibleFrame01
 * @tc.desc: Test the function GetOneDepthVisibleFrame
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetOneDepthVisibleFrame01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode ,childNode and overlayNode.
     */
    auto node = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto childNode =
        FrameNode::CreateFrameNode("main", 2, AceType::MakeRefPtr<Pattern>(), true); // 2 is id of childNode
    auto overlayNode =
        FrameNode::CreateFrameNode("main", 3, AceType::MakeRefPtr<Pattern>(), true); // 3 is id of overlayNode

    /**
     * @tc.steps: step2. add childnode to the childnode list
     */
    std::list<RefPtr<FrameNode>> children;
    children.push_back(childNode);
    node->frameChildren_ = { children.begin(), children.end() };

    /**
     * @tc.steps: step3. call the function GetOneDepthVisibleFrame.
     */
    node->SetOverlayNode(overlayNode);
    node->GetOneDepthVisibleFrame(children);
    EXPECT_NE(node->overlayNode_, nullptr);
}

/**
 * @tc.name: FrameNodeGetOneDepthVisibleFrame02
 * @tc.desc: Test the function GetOneDepthVisibleFrame
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetOneDepthVisibleFrame02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode ,childNode and overlayNode.
     */
    auto node = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto childNode =
        FrameNode::CreateFrameNode("main", 2, AceType::MakeRefPtr<Pattern>(), true); // 2 is id of childNode
    auto overlayNode = nullptr;

    /**
     * @tc.steps: step2. add childnode to the childnode list
     */
    std::list<RefPtr<FrameNode>> children;
    children.push_back(childNode);
    node->frameChildren_ = { children.begin(), children.end() };

    /**
     * @tc.steps: step3. call the function GetOneDepthVisibleFrame.
     */
    node->SetOverlayNode(overlayNode);
    node->GetOneDepthVisibleFrame(children);
    EXPECT_EQ(node->overlayNode_, nullptr);
}

/**
 * @tc.name: FrameNodeGetOneDepthVisibleFrameWithOffset01
 * @tc.desc: Test the function GetOneDepthVisibleFrameWithOffset
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetOneDepthVisibleFrameWithOffset01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode ,childNode and overlayNode.
     */
    auto node = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto childNode =
        FrameNode::CreateFrameNode("main", 2, AceType::MakeRefPtr<Pattern>(), true); // 2 is id of childNode
    auto overlayNode =
        FrameNode::CreateFrameNode("main", 3, AceType::MakeRefPtr<Pattern>(), true); // 3 is id of overlayNode

    /**
     * @tc.steps: step2. add childnode to the childnode list
     */
    std::list<RefPtr<FrameNode>> children;
    children.push_back(childNode);
    node->frameChildren_ = { children.begin(), children.end() };

    /**
     * @tc.steps: step3. call the function GetOneDepthVisibleFrameWithOffset.
     */
    OffsetF Offset = { 0, 0 };
    node->SetOverlayNode(overlayNode);
    node->GetOneDepthVisibleFrameWithOffset(children, Offset);
    EXPECT_NE(node->overlayNode_, nullptr);
}

/**
 * @tc.name: FrameNodeGetOneDepthVisibleFrameWithOffset02
 * @tc.desc: Test the function GetOneDepthVisibleFrameWithOffset
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetOneDepthVisibleFrameWithOffset02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode ,childNode and overlayNode.
     */
    auto node = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto childNode =
        FrameNode::CreateFrameNode("main", 2, AceType::MakeRefPtr<Pattern>(), true); // 2 is id of childNode
    auto overlayNode = nullptr;

    /**
     * @tc.steps: step2. add childnode to the childnode list
     */
    std::list<RefPtr<FrameNode>> children;
    children.push_back(childNode);
    node->frameChildren_ = { children.begin(), children.end() };

    /**
     * @tc.steps: step3. call the function GetOneDepthVisibleFrameWithOffset.
     */
    OffsetF Offset = { 0, 0 };
    node->SetOverlayNode(overlayNode);
    node->GetOneDepthVisibleFrameWithOffset(children, Offset);
    EXPECT_EQ(node->overlayNode_, nullptr);
}

/**
 * @tc.name: FrameNodeGetOrCreateCommonNode01
 * @tc.desc: Test the function GetOrCreateCommonNode
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetOrCreateCommonNode01, TestSize.Level1)
{
    /**
     * @tc.steps: step1: create commonNode.
     */
    RefPtr<FrameNode> commonNode = FrameNode::CreateCommonNode("commonNode", 1, true, AceType::MakeRefPtr<Pattern>());
    EXPECT_TRUE(commonNode->GetIsLayoutNode());
    /**
     * @tc.steps: step2: call the function GetOrCreateCommonNode.
     * @tc.expected: Value returned as expected.
     */
    auto blankNode =
        FrameNode::GetOrCreateCommonNode("commonNode", 1, false, []() { return AceType::MakeRefPtr<Pattern>(); });
    EXPECT_EQ(strcmp(blankNode->GetTag().c_str(), "commonNode"), 0);
    EXPECT_FALSE(blankNode->GetIsLayoutNode());
}

/**
 * @tc.name: FrameNodeProcessOffscreenNode01
 * @tc.desc: Test the function ProcessOffscreenNode
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeProcessOffscreenNode01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and childNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto node = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto childNodeOne =
        FrameNode::CreateFrameNode("main", 2, AceType::MakeRefPtr<Pattern>(), true); // 2 is id of childNodeOne
    auto childNodeTwo = nullptr;

    /**
     * @tc.steps: step2. add childnode to the predictLayoutNode list
     */
    node->AddPredictLayoutNode(childNodeOne);
    node->AddPredictLayoutNode(childNodeTwo);

    /**
     * @tc.steps: step3. call the function ProcessOffscreenNode.
     */
    frameNode->ProcessOffscreenNode(node);
    EXPECT_NE(frameNode, nullptr);
}

/**
 * @tc.name: FrameNodeDumpAlignRulesInfo01
 * @tc.desc: Test the function DumpAlignRulesInfo
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeDumpAlignRulesInfo01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. create layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->flexItemProperty_ = std::make_unique<FlexItemProperty>();
    std::map<AlignDirection, AlignRule> firstItemAlignRules;
    AlignRule alignRule;
    alignRule.anchor = "test";
    alignRule.horizontal = HorizontalAlign::START;
    firstItemAlignRules[AlignDirection::LEFT] = alignRule;

    layoutProperty->UpdateAlignRules(firstItemAlignRules);
    layoutProperty->flexItemProperty_->propFlexGrow = 1.0f;

    /**
     * @tc.steps: step3. call the function DumpAlignRulesInfo.
     */
    frameNode->SetLayoutProperty(layoutProperty);
    frameNode->DumpAlignRulesInfo();
    EXPECT_NE(frameNode, nullptr);
    EXPECT_NE(frameNode->layoutProperty_, nullptr);
}

/**
 * @tc.name: FrameNodeDumpSafeAreaInfo01
 * @tc.desc: Test the function DumpSafeAreaInfo
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeDumpSafeAreaInfo01, TestSize.Level1)
{
    SafeAreaExpandOpts opts;
    SafeAreaInsets safeArea;
    SafeAreaExpandOpts expandOpts = {
        .edges = SAFE_AREA_TYPE_SYSTEM,
        .type = SAFE_AREA_EDGE_TOP,
    };
    SafeAreaInsets::Inset inset = {
        .start = 0,
        .end = 1,
    };

    SafeAreaInsets safeAreaInset(inset, inset, inset, inset);
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. create layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->safeAreaExpandOpts_ = std::make_unique<SafeAreaExpandOpts>(opts);
    layoutProperty->safeAreaInsets_ = std::make_unique<SafeAreaInsets>(safeArea);
    layoutProperty->UpdateSafeAreaExpandOpts(expandOpts);
    layoutProperty->UpdateSafeAreaInsets(safeAreaInset);
    EXPECT_EQ(layoutProperty->safeAreaExpandOpts_->edges, SAFE_AREA_TYPE_SYSTEM);
    EXPECT_EQ(layoutProperty->safeAreaExpandOpts_->type, SAFE_AREA_EDGE_TOP);

    /**
     * @tc.steps: step3. call the function DumpSafeAreaInfo.
     */
    frameNode->SetLayoutProperty(layoutProperty);
    frameNode->DumpSafeAreaInfo();
}

/**
 * @tc.name: FrameNodeDumpCommonInfo01
 * @tc.desc: Test the function DumpCommonInfo
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeDumpCommonInfo01, TestSize.Level1)
{
    LayoutConstraintF layoutConstraintF = {
        .minSize = { 1, 1 },
        .maxSize = { 10, 10 },        // 10 is the maxSize of width and height
        .percentReference = { 5, 5 }, // 5 is the percentReference of width and height
        .parentIdealSize = { 2, 2 },  // 2 is the parentIdealSize of width and height
    };

    NG::RectF testRect = { 10.0f, 10.0f, 10.0f, 10.0f }; // 10.0f is the x, y, width and height of rect

    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->AddChild(FRAME_NODE);
    EXPECT_EQ(frameNode->GetTotalChildCount(), 1);

    /**
     * @tc.steps: step2. create layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->propVisibility_ = VisibleType::INVISIBLE;
    layoutProperty->SetLayoutRect(testRect);
    layoutProperty->layoutConstraint_ = layoutConstraintF;
    layoutProperty->contentConstraint_ = layoutConstraintF;

    /**
     * @tc.steps: step3. call the function DumpCommonInfo.
     */
    frameNode->SetLayoutProperty(layoutProperty);
    frameNode->DumpCommonInfo();
}

/**
 * @tc.name: FrameNodeDumpCommonInfo02
 * @tc.desc: Test frameNode DumpCommonInfo
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeDumpCommonInfo02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);

    /**
     * @tc.steps: step2. call DumpCommonInfo.
     * @tc.expected: expect description_[12] is BorderRadius.
     */
    frameNode->geometryNode_->frame_.rect_ = { 10.0f, 10.0f, 10.0f, 10.0f };
    LayoutConstraintF parentLayoutConstraint;
    frameNode->geometryNode_->parentLayoutConstraint_ = parentLayoutConstraint;
    frameNode->isFreeze_ = true;
    frameNode->userFreeze_ = true;
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->propVisibility_ = VisibleType::INVISIBLE;
    layoutProperty->padding_ = std::make_unique<PaddingProperty>();
    layoutProperty->safeAreaPadding_ = std::make_unique<PaddingProperty>();
    layoutProperty->borderWidth_ = std::make_unique<BorderWidthProperty>();
    frameNode->layoutProperty_ = layoutProperty;
    Dimension radius(10.0f);
    BorderRadiusProperty borderRadiusProperty { radius, radius, radius, radius };
    frameNode->renderContext_->UpdateBorderRadius(borderRadiusProperty);
    DumpLog::GetInstance().description_.clear();
    frameNode->DumpCommonInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_[11],
        "BorderRadius: radiusTopLeft: [10.00px]radiusTopRight: "
        "[10.00px]radiusBottomLeft: [10.00px]radiusBottomRight: [10.00px]\n");
}

/**
 * @tc.name: FrameNodeDumpOnSizeChangeInfo01
 * @tc.desc: Test the function DumpOnSizeChangeInfo
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeDumpOnSizeChangeInfo01, TestSize.Level1)
{
    NG::RectF testLastFrameRect = { 10.0f, 10.0f, 10.0f, 10.0f }; // 10.0f is the x, y, width and height of rect
    NG::RectF testCurrFrameRect = { 10.0f, 10.0f, 10.0f, 10.0f }; // 10.0f is the x, y, width and height of rect
    FrameNode::onSizeChangeDumpInfo dumpInfo1 { 1, testLastFrameRect,
        testCurrFrameRect }; // 1 is the onSizeChangeTimeStamp
    FrameNode::onSizeChangeDumpInfo dumpInfo2 { 2, testLastFrameRect,
        testCurrFrameRect }; // 2 is the onSizeChangeTimeStamp

    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. add onSizeChangeDumpInfos.
     */
    frameNode->onSizeChangeDumpInfos.push_back(dumpInfo1);
    frameNode->onSizeChangeDumpInfos.push_back(dumpInfo2);

    /**
     * @tc.steps: step3. call the function DumpOnSizeChangeInfo.
     */
    frameNode->DumpOnSizeChangeInfo();
    EXPECT_NE(frameNode, nullptr);
}

/**
 * @tc.name: FrameNodeDumpInfo01
 * @tc.desc: Test the function DumpInfo DumpAdvanceInfo CheckAutoSave
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeDumpInfo01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);

    /**
     * @tc.steps: step2. update pattern_.
     */
    auto pattern = frameNode->pattern_;
    frameNode->pattern_ = nullptr;

    /**
     * @tc.steps: step3. call the function DumpOnSizeChangeInfo DumpAdvanceInfo CheckAutoSave.
     */
    auto viewDataWrap = ViewDataWrap::CreateViewDataWrap();
    frameNode->DumpInfo();
    frameNode->DumpAdvanceInfo();
    frameNode->DumpViewDataPageNode(viewDataWrap);
    EXPECT_FALSE(frameNode->CheckAutoSave());
    frameNode->pattern_ = pattern;
}

/**
 * @tc.name: FrameNodeMouseToJsonValue01
 * @tc.desc: Test the function MouseToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeMouseToJsonValue01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);

    /**
     * @tc.steps: step2. call the function MouseToJsonValue.
     */
    InspectorFilter testFilter;
    auto jsonValue = std::make_unique<JsonValue>();
    testFilter.AddFilterAttr("focusable");
    frameNode->MouseToJsonValue(jsonValue, testFilter);
    EXPECT_FALSE(jsonValue->GetBool("enabled", false));
}

/**
 * @tc.name: FrameNodeTouchToJsonValue01
 * @tc.desc: Test the function TouchToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTouchToJsonValue01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);

    /**
     * @tc.steps: step2. call the function TouchToJsonValue.
     */
    InspectorFilter testFilter;
    auto jsonValue = std::make_unique<JsonValue>();
    testFilter.AddFilterAttr("focusable");
    frameNode->TouchToJsonValue(jsonValue, testFilter);
    EXPECT_FALSE(jsonValue->GetBool("enabled", false));
}

/**
 * @tc.name: FrameNodeTouchToJsonValue02
 * @tc.desc: Test the function TouchToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTouchToJsonValue02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);
    frameNode->isActive_ = true;
    frameNode->GetEventHub<EventHub>()->SetEnabled(true);

    /**
     * @tc.steps: step2. update the mouseResponseRegion.
     */
    DimensionRect responseRect(Dimension(0), Dimension(0), DimensionOffset(OFFSETF));
    std::vector<DimensionRect> mouseResponseRegion;
    mouseResponseRegion.emplace_back(responseRect);
    auto gestureEventHub = frameNode->GetEventHub<EventHub>()->GetOrCreateGestureEventHub();
    gestureEventHub->SetMouseResponseRegion(mouseResponseRegion);

    /**
     * @tc.steps: step3. call the function TouchToJsonValue.
     */
    InspectorFilter testFilter;
    auto jsonValue = std::make_unique<JsonValue>();
    frameNode->TouchToJsonValue(jsonValue, testFilter);
    EXPECT_FALSE(jsonValue->GetBool("enabled", false));
}

/**
 * @tc.name: FrameNodeToTreeJson01
 * @tc.desc: Test the function ToTreeJson
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeToTreeJson01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);

    /**
     * @tc.steps: step2. call the function ToTreeJson.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    frameNode->SetLayoutProperty(layoutProperty);

    InspectorConfig testConfig;
    auto jsonValue = std::make_unique<JsonValue>();
    testConfig.contentOnly = true;
    frameNode->ToTreeJson(jsonValue, testConfig);
}

/**
 * @tc.name: FrameNodeToTreeJson02
 * @tc.desc: Test the function ToTreeJson
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeToTreeJson02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);

    /**
     * @tc.steps: step2. call the function ToTreeJson.
     */
    frameNode->paintProperty_ = nullptr;
    frameNode->propInspectorId_ = "123";
    frameNode->accessibilityProperty_ = nullptr;
    frameNode->GetEventHub<EventHub>()->GetOrCreateFocusHub();

    InspectorConfig testConfig;
    auto jsonValue = std::make_unique<JsonValue>();
    testConfig.contentOnly = false;
    frameNode->ToTreeJson(jsonValue, testConfig);
}

/**
 * @tc.name: FrameNodeToTreeJson03
 * @tc.desc: Test the function ToTreeJson
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeToTreeJson03, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);

    /**
     * @tc.steps: step2. call the function ToTreeJson.
     */
    auto pattern = frameNode->pattern_;
    frameNode->pattern_ = nullptr;
    frameNode->paintProperty_ = nullptr;
    frameNode->accessibilityProperty_->accessibilityText_ = "test";
    frameNode->layoutProperty_ = nullptr;

    InspectorConfig testConfig;
    auto jsonValue = std::make_unique<JsonValue>();
    testConfig.contentOnly = false;
    frameNode->ToTreeJson(jsonValue, testConfig);
    frameNode->pattern_ = pattern;
}

/**
 * @tc.name: FrameNodeFromJson01
 * @tc.desc: Test the function FromJson
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeFromJson01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);

    /**
     * @tc.steps: step2. call the function FromJson.
     */
    auto eventHub = frameNode->eventHub_;
    frameNode->eventHub_ = nullptr;
    InspectorFilter testFilter;
    auto jsonValue = std::make_unique<JsonValue>();
    testFilter.AddFilterAttr("focusable");
    frameNode->FromJson(jsonValue);
    EXPECT_FALSE(jsonValue->GetBool("enabled", false));
    frameNode->eventHub_ = eventHub;
}

/**
 * @tc.name: FrameNodeUpdateGeometryTransition01
 * @tc.desc: Test the function UpdateGeometryTransition
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeUpdateGeometryTransition01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("parent", 0, AceType::MakeRefPtr<Pattern>(), true);
    auto child = FrameNode::CreateFrameNode("childNode", 1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(frameNode->pattern_, nullptr);
    frameNode->AddChild(child);
    EXPECT_EQ(frameNode->GetTotalChildCount(), 1);

    /**
     * @tc.steps: step2. update geometryTransition.
     */
    frameNode->GetLayoutProperty()->UpdateGeometryTransition("parent", true);
    child->GetLayoutProperty()->UpdateGeometryTransition("child", false);
    LayoutProperty::UpdateAllGeometryTransition(frameNode);

    /**
     * @tc.steps: step3. call the function UpdateGeometryTransition.
     */
    frameNode->UpdateGeometryTransition();
}

/**
 * @tc.name: FrameNodeOnAttachToMainTree01
 * @tc.desc: Test the function OnAttachToMainTree
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeOnAttachToMainTree01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto childNodeOne =
        FrameNode::CreateFrameNode("main", 2, AceType::MakeRefPtr<Pattern>(), false); // 2 is id of childNodeOne
    auto childNodeTwo = nullptr;
    auto childNodeThree =
        FrameNode::CreateFrameNode("main", 3, AceType::MakeRefPtr<Pattern>(), false); // 3 is id of childNodeThree
    EXPECT_NE(frameNode->pattern_, nullptr);

    /**
     * @tc.steps: step2. update node.
     */
    childNodeOne->isLayoutDirtyMarked_ = true;
    childNodeThree->isLayoutDirtyMarked_ = false;
    frameNode->AddPredictLayoutNode(childNodeOne);
    frameNode->AddPredictLayoutNode(childNodeTwo);
    frameNode->AddPredictLayoutNode(childNodeThree);
    frameNode->useOffscreenProcess_ = true;
    frameNode->isPropertyDiffMarked_ = true;

    /**
     * @tc.steps: step3. call the function OnAttachToMainTree.
     */
    frameNode->OnAttachToMainTree(true);
}

/**
 * @tc.name: FrameNodeOnAttachToMainTree02
 * @tc.desc: Test the function OnAttachToMainTree
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeOnAttachToMainTree02, TestSize.Level1)
{
    LayoutConstraintF layoutConstraintF = {
        .minSize = { 1, 1 },
        .maxSize = { 10, 10 },        // 10 is the maxSize of width and height
        .percentReference = { 5, 5 }, // 5 is the percentReference of width and height
        .parentIdealSize = { 2, 2 },  // 2 is the parentIdealSize of width and height
    };
    /**
     * @tc.steps: step1. create node.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 0, AceType::MakeRefPtr<Pattern>(), true);
    auto childNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), false);

    /**
     * @tc.steps: step2. update node.
     */
    childNode->isLayoutDirtyMarked_ = true;
    frameNode->AddPredictLayoutNode(childNode);
    frameNode->useOffscreenProcess_ = false;
    frameNode->isPropertyDiffMarked_ = true;
    frameNode->geometryNode_->SetParentLayoutConstraint(layoutConstraintF);

    /**
     * @tc.steps: step3. call the function OnAttachToMainTree.
     */
    frameNode->OnAttachToMainTree(true);
    EXPECT_TRUE(childNode->isLayoutDirtyMarked_);
    EXPECT_FALSE(frameNode->useOffscreenProcess_);
    EXPECT_TRUE(frameNode->isPropertyDiffMarked_);
    auto context = frameNode->GetContext();
    bool hasDirtyPropertyNodes = context->dirtyPropertyNodes_.find(frameNode) != context->dirtyPropertyNodes_.end();
    EXPECT_TRUE(hasDirtyPropertyNodes);
}

/**
 * @tc.name: FrameNodeOnAttachToBuilderNode01
 * @tc.desc: Test the function OnAttachToBuilderNode
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeOnAttachToBuilderNode01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 0, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. call the function OnAttachToBuilderNode.
     */
    frameNode->OnAttachToBuilderNode(NodeStatus::BUILDER_NODE_ON_MAINTREE);
    EXPECT_NE(frameNode->pattern_, nullptr);
}

/**
 * @tc.name: FrameNodeOnConfigurationUpdate01
 * @tc.desc: Test the function OnConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeOnConfigurationUpdate01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 0, AceType::MakeRefPtr<Pattern>(), true);
    auto callback = []() {};
    frameNode->SetColorModeUpdateCallback(std::move(callback));

    /**
     * @tc.steps: step2. call the function OnConfigurationUpdate.
     */
    ConfigurationChange configurationChange;
    configurationChange.colorModeUpdate = true;
    configurationChange.fontUpdate = false;
    configurationChange.iconUpdate = false;
    configurationChange.skinUpdate = false;
    frameNode->OnConfigurationUpdate(configurationChange);
    EXPECT_TRUE(configurationChange.colorModeUpdate);
    EXPECT_FALSE(configurationChange.fontUpdate);
    EXPECT_FALSE(configurationChange.iconUpdate);
    EXPECT_FALSE(configurationChange.skinUpdate);
}

/**
 * @tc.name: FrameNodeSwapDirtyLayoutWrapperOnMainThread01
 * @tc.desc: Test the function SwapDirtyLayoutWrapperOnMainThread
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeSwapDirtyLayoutWrapperOnMainThread01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->isActive_ = false;
    /**
     * @tc.steps: step2. create layoutProperty.
     */
    BorderWidthProperty borderWidth = { 1.0_vp, 1.0_vp, 1.0_vp, 1.0_vp };
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->UpdateBorderWidth(borderWidth);

    RefPtr<LayoutWrapper> layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    layoutWrapper->SetActive(true);

    auto builderFunc = []() -> RefPtr<UINode> {
        auto node = FrameNode::CreateFrameNode("node", 0, AceType::MakeRefPtr<Pattern>(), true);
        auto childNode = FrameNode::CreateFrameNode("child", 1, AceType::MakeRefPtr<Pattern>(), true);
        node->AddChild(childNode);
        return node;
    };

    /**
     * @tc.steps: step3. call the function DumpCommonInfo.
     */
    frameNode->SetBackgroundFunction(builderFunc);
    frameNode->SetLayoutProperty(layoutProperty);
    frameNode->SwapDirtyLayoutWrapperOnMainThread(layoutWrapper);
    EXPECT_TRUE(frameNode->isActive_);
}

/**
 * @tc.name: FrameNodeSwapDirtyLayoutWrapperOnMainThread02
 * @tc.desc: Test the function SwapDirtyLayoutWrapperOnMainThread
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeSwapDirtyLayoutWrapperOnMainThread02, TestSize.Level1)
{
    LayoutConstraintF layoutConstraintF = {
        .minSize = { 1, 1 },
        .maxSize = { 10, 10 },        // 10 is the maxSize of width and height
        .percentReference = { 5, 5 }, // 5 is the percentReference of width and height
        .parentIdealSize = { 2, 2 },  // 2 is the parentIdealSize of width and height
    };
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->isActive_ = false;
    /**
     * @tc.steps: step2. create layoutProperty.
     */
    BorderWidthProperty borderWidth = { 1.0_vp, 1.0_vp, 1.0_vp, 1.0_vp };
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->UpdateBorderWidth(borderWidth);
    layoutProperty->layoutConstraint_ = layoutConstraintF;
    layoutProperty->contentConstraint_ = layoutConstraintF;
    frameNode->GetOrCreateFocusHub()->currentFocus_ = true;

    RefPtr<LayoutWrapper> layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    layoutWrapper->SetActive(true);

    auto builderFunc = []() -> RefPtr<UINode> { return nullptr; };

    /**
     * @tc.steps: step3. update renderContext_.
     */
    BorderColorProperty borderColorProperty;
    borderColorProperty.SetColor(Color::BLUE);
    frameNode->renderContext_->UpdateBorderColor(borderColorProperty);
    BorderStyleProperty borderStyleProperty;
    borderStyleProperty.SetBorderStyle(BorderStyle::SOLID);
    frameNode->renderContext_->UpdateBorderStyle(borderStyleProperty);
    BorderWidthProperty dashGapProperty;
    dashGapProperty.SetBorderWidth(Dimension(1));
    frameNode->renderContext_->UpdateDashGap(dashGapProperty);
    BorderWidthProperty dashWidthProperty;
    dashWidthProperty.SetBorderWidth(Dimension(1));
    frameNode->renderContext_->UpdateDashWidth(dashWidthProperty);

    /**
     * @tc.steps: step4. call the function DumpCommonInfo.
     */
    frameNode->SetBackgroundFunction(builderFunc);
    frameNode->SetLayoutProperty(layoutProperty);
    frameNode->SwapDirtyLayoutWrapperOnMainThread(layoutWrapper);
    EXPECT_NE(frameNode->pattern_, nullptr);
    EXPECT_NE(frameNode->layoutProperty_, nullptr);
}

/**
 * @tc.name: FrameNodeAdjustGridOffset01
 * @tc.desc: Test the function AdjustGridOffset
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeAdjustGridOffset01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->isActive_ = true;

    /**
     * @tc.steps: step2. create layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->gridProperty_ = std::make_unique<GridProperty>();
    layoutProperty->UpdateGridProperty(1, 0, GridSizeType::UNDEFINED);

    layoutProperty->gridProperty_ = std::make_unique<GridProperty>();
    frameNode->SetParent(FRAME_NODE);
    frameNode->NotifyVisibleChange(VisibleType::INVISIBLE, VisibleType::VISIBLE);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameOffset(OffsetF(1.0f, 0.0f));
    frameNode->geometryNode_ = geometryNode;
    layoutProperty->BuildGridProperty(frameNode);

    /**
     * @tc.steps: step4. call the function DumpCommonInfo.
     */
    frameNode->SetLayoutProperty(layoutProperty);
    frameNode->AdjustGridOffset();
    EXPECT_NE(frameNode->pattern_, nullptr);
    EXPECT_NE(frameNode->layoutProperty_, nullptr);
}

/**
 * @tc.name: FrameNodeClearUserOnAreaChange01
 * @tc.desc: Test the function ClearUserOnAreaChange
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeClearUserOnAreaChange01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);

    /**
     * @tc.steps: step2. call the function ClearUserOnAreaChange.
     */
    auto eventHub = frameNode->eventHub_;
    frameNode->eventHub_ = nullptr;
    frameNode->ClearUserOnAreaChange();
    frameNode->eventHub_ = eventHub;
}

/**
 * @tc.name: FrameNodeTriggerOnAreaChangeCallback01
 * @tc.desc: Test the function TriggerOnAreaChangeCallback
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTriggerOnAreaChangeCallback01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);
    frameNode->isActive_ = true;
    bool flag = false;
    OnAreaChangedFunc onAreaChanged = [&flag](const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect,
                                          const OffsetF& origin) { flag = !flag; };
    frameNode->GetEventHub<EventHub>()->SetOnAreaChanged(std::move(onAreaChanged));
    frameNode->GetEventHub<EventHub>()->AddInnerOnAreaChangedCallback(1, std::move(onAreaChanged));
    frameNode->lastParentOffsetToWindow_ = std::make_unique<OffsetF>(OffsetF(50.0f, 50.0f)); // 50.0f is the offset
    frameNode->lastFrameRect_ =
        std::make_unique<RectF>(RectF(OffsetF(50.0f, 50.0f), SizeF(50.0f, 50.0f))); // 50.0f is ths offset and size

    auto& posProperty = frameNode->renderContext_->GetOrCreatePositionProperty();
    posProperty->UpdatePosition(OffsetT<Dimension>(Dimension(1), Dimension(1)));
    /**
     * @tc.steps: step3. call the function TriggerOnAreaChangeCallback.
     */
    frameNode->TriggerOnAreaChangeCallback(TIMESTAMP_1);
}

/**
 * @tc.name: FrameNodeTriggerOnAreaChangeCallback02
 * @tc.desc: Test the function TriggerOnAreaChangeCallback
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTriggerOnAreaChangeCallback02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);
    frameNode->isActive_ = true;
    bool flag = false;
    OnAreaChangedFunc onAreaChanged = [&flag](const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect,
                                          const OffsetF& origin) { flag = !flag; };
    frameNode->GetEventHub<EventHub>()->SetOnAreaChanged(std::move(onAreaChanged));
    frameNode->lastParentOffsetToWindow_ = std::make_unique<OffsetF>(OffsetF(50.0f, 50.0f)); // 50.0f is the offset
    frameNode->lastFrameRect_ =
        std::make_unique<RectF>(RectF(OffsetF(50.0f, 50.0f), SizeF(50.0f, 50.0f))); // 50.0f is ths offset and size

    auto& posProperty = frameNode->renderContext_->GetOrCreatePositionProperty();
    posProperty->UpdateOffset(OffsetT<Dimension>(Dimension(1), Dimension(1)));
    /**
     * @tc.steps: step3. call the function TriggerOnAreaChangeCallback.
     */
    frameNode->TriggerOnAreaChangeCallback(TIMESTAMP_1);
}

/**
 * @tc.name: FrameNodeTriggerOnAreaChangeCallback03
 * @tc.desc: Test the function TriggerOnAreaChangeCallback
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTriggerOnAreaChangeCallback03, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);
    frameNode->isActive_ = true;
    bool flag = false;
    OnAreaChangedFunc onAreaChanged = [&flag](const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect,
                                          const OffsetF& origin) { flag = !flag; };
    frameNode->GetEventHub<EventHub>()->AddInnerOnAreaChangedCallback(1, std::move(onAreaChanged));
    frameNode->lastParentOffsetToWindow_ = std::make_unique<OffsetF>(OffsetF(50.0f, 50.0f)); // 50.0f is the offset
    frameNode->lastFrameRect_ =
        std::make_unique<RectF>(RectF(OffsetF(50.0f, 50.0f), SizeF(50.0f, 50.0f))); // 50.0f is ths offset and size

    auto& posProperty = frameNode->renderContext_->GetOrCreatePositionProperty();
    posProperty->UpdatePosition(OffsetT<Dimension>(Dimension(1), Dimension(1)));
    /**
     * @tc.steps: step3. call the function TriggerOnAreaChangeCallback.
     */
    frameNode->TriggerOnAreaChangeCallback(TIMESTAMP_1);
}

/**
 * @tc.name: FrameNodeAddInnerOnSizeChangeCallback01
 * @tc.desc: Test the function AddInnerOnSizeChangeCallback
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeAddInnerOnSizeChangeCallback01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);
    OnSizeChangedFunc callback = [](const RectF& oldRect, const RectF& rect) {};
    frameNode->lastFrameNodeRect_ = std::make_unique<RectF>(RectF(OffsetF(1.0f, 1.0f), SizeF(1.0f, 1.0f)));
    /**
     * @tc.steps: step3. call the function TriggerOnAreaChangeCallback.
     */
    frameNode->AddInnerOnSizeChangeCallback(1, std::move(callback));
}

/**
 * @tc.name: FrameNodeAddInnerOnSizeChangeCallback02
 * @tc.desc: Test the function AddInnerOnSizeChangeCallback
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeAddInnerOnSizeChangeCallback02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);
    OnSizeChangedFunc callback = [](const RectF& oldRect, const RectF& rect) {};
    /**
     * @tc.steps: step3. call the function TriggerOnAreaChangeCallback.
     */
    frameNode->AddInnerOnSizeChangeCallback(1, std::move(callback));
}

/**
 * @tc.name: FrameNodeSetJSFrameNodeOnSizeChangeCallback01
 * @tc.desc: Test the function SetJSFrameNodeOnSizeChangeCallback
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeSetJSFrameNodeOnSizeChangeCallback01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);
    OnSizeChangedFunc callback = [](const RectF& oldRect, const RectF& rect) {};
    frameNode->lastFrameNodeRect_ = std::make_unique<RectF>(RectF(OffsetF(1.0f, 1.0f), SizeF(1.0f, 1.0f)));
    /**
     * @tc.steps: step3. call the function SetJSFrameNodeOnSizeChangeCallback.
     */
    frameNode->SetJSFrameNodeOnSizeChangeCallback(std::move(callback));
}

/**
 * @tc.name: FrameNodeSetJSFrameNodeOnSizeChangeCallback02
 * @tc.desc: Test the function SetJSFrameNodeOnSizeChangeCallback
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeSetJSFrameNodeOnSizeChangeCallback02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);
    OnSizeChangedFunc callback = [](const RectF& oldRect, const RectF& rect) {};
    /**
     * @tc.steps: step3. call the function SetJSFrameNodeOnSizeChangeCallback.
     */
    frameNode->SetJSFrameNodeOnSizeChangeCallback(std::move(callback));
}

/**
 * @tc.name: FrameNodeGetRectWithRender01
 * @tc.desc: Test the function GetRectWithRender
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetRectWithRender01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);
    frameNode->isActive_ = true;

    auto& posProperty = frameNode->renderContext_->GetOrCreatePositionProperty();
    posProperty->UpdatePosition(OffsetT<Dimension>(Dimension(1), Dimension(1)));
    /**
     * @tc.steps: step3. call the function GetRectWithRender.
     */
    frameNode->GetRectWithRender();
}

/**
 * @tc.name: FrameNodeGetRectWithRender02
 * @tc.desc: Test the function GetRectWithRender
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetRectWithRender02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);
    frameNode->isActive_ = true;

    auto& posProperty = frameNode->renderContext_->GetOrCreatePositionProperty();
    posProperty->UpdateOffset(OffsetT<Dimension>(Dimension(1), Dimension(1)));
    /**
     * @tc.steps: step3. call the function GetRectWithRender.
     */
    frameNode->GetRectWithRender();
}

/**
 * @tc.name: FrameNodeTriggerOnSizeChangeCallback01
 * @tc.desc: Test the function TriggerOnSizeChangeCallback
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTriggerOnSizeChangeCallback01, TestSize.Level1)
{
    NG::RectF testLastFrameRect = { 10.0f, 10.0f, 10.0f, 10.0f }; // 10.0f is the x, y, width and height of rect
    NG::RectF testCurrFrameRect = { 10.0f, 10.0f, 10.0f, 10.0f }; // 10.0f is the x, y, width and height of rect
    FrameNode::onSizeChangeDumpInfo dumpInfoOne { 1, testLastFrameRect,
        testCurrFrameRect }; // 1 is the onSizeChangeTimeStamp
    FrameNode::onSizeChangeDumpInfo dumpInfoTwo { 2, testLastFrameRect,
        testCurrFrameRect }; // 2 is the onSizeChangeTimeStamp
    FrameNode::onSizeChangeDumpInfo dumpInfoThree { 3, testLastFrameRect,
        testCurrFrameRect }; // 3 is the onSizeChangeTimeStamp
    FrameNode::onSizeChangeDumpInfo dumpInfoFour { 4, testLastFrameRect,
        testCurrFrameRect }; // 4 is the onSizeChangeTimeStamp
    FrameNode::onSizeChangeDumpInfo dumpInfoFive { 5, testLastFrameRect,
        testCurrFrameRect }; // 5 is the onSizeChangeTimeStamp
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("page", 1, AceType::MakeRefPtr<PagePattern>(nullptr), true);
    EXPECT_NE(frameNode->pattern_, nullptr);
    frameNode->isActive_ = true;
    auto pattern = frameNode->GetPattern<PagePattern>();
    pattern->isOnShow_ = true;
    bool flag = false;
    OnSizeChangedFunc onSizeChanged = [&flag](const RectF& oldRect, const RectF& rect) { flag = !flag; };
    frameNode->GetEventHub<EventHub>()->SetOnSizeChanged(std::move(onSizeChanged));
    frameNode->GetEventHub<EventHub>()->AddInnerOnSizeChanged(1, std::move(onSizeChanged));
    frameNode->lastFrameNodeRect_ =
        std::make_unique<RectF>(RectF(OffsetF(50.0f, 50.0f), SizeF(50.0f, 50.0f))); // 50.0f is ths offset and size
    frameNode->onSizeChangeDumpInfos.push_back(dumpInfoOne);
    frameNode->onSizeChangeDumpInfos.push_back(dumpInfoTwo);
    frameNode->onSizeChangeDumpInfos.push_back(dumpInfoThree);
    frameNode->onSizeChangeDumpInfos.push_back(dumpInfoFour);
    frameNode->onSizeChangeDumpInfos.push_back(dumpInfoFive);
    /**
     * @tc.steps: step3. call the function TriggerOnSizeChangeCallback.
     */
    frameNode->TriggerOnSizeChangeCallback();
}

/**
 * @tc.name: FrameNodeTriggerOnSizeChangeCallback02
 * @tc.desc: Test the function TriggerOnSizeChangeCallback
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTriggerOnSizeChangeCallback02, TestSize.Level1)
{
    NG::RectF testLastFrameRect = { 10.0f, 10.0f, 10.0f, 10.0f }; // 10.0f is the x, y, width and height of rect
    NG::RectF testCurrFrameRect = { 10.0f, 10.0f, 10.0f, 10.0f }; // 10.0f is the x, y, width and height of rect
    FrameNode::onSizeChangeDumpInfo dumpInfoOne { 1, testLastFrameRect, testCurrFrameRect };
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("page", 1, AceType::MakeRefPtr<PagePattern>(nullptr), true);
    EXPECT_NE(frameNode->pattern_, nullptr);
    frameNode->isActive_ = true;
    auto pattern = frameNode->GetPattern<PagePattern>();
    pattern->isOnShow_ = true;
    bool flag = false;
    OnSizeChangedFunc onSizeChanged = [&flag](const RectF& oldRect, const RectF& rect) { flag = !flag; };
    frameNode->GetEventHub<EventHub>()->SetOnSizeChanged(std::move(onSizeChanged));
    frameNode->lastFrameNodeRect_ =
        std::make_unique<RectF>(RectF(OffsetF(50.0f, 50.0f), SizeF(50.0f, 50.0f))); // 50.0f is ths offset and size
    frameNode->onSizeChangeDumpInfos.push_back(dumpInfoOne);
    /**
     * @tc.steps: step3. call the function TriggerOnSizeChangeCallback.
     */
    frameNode->TriggerOnSizeChangeCallback();
}

/**
 * @tc.name: FrameNodeTriggerOnSizeChangeCallback03
 * @tc.desc: Test the function TriggerOnSizeChangeCallback
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTriggerOnSizeChangeCallback03, TestSize.Level1)
{
    NG::RectF testLastFrameRect = { 10.0f, 10.0f, 10.0f, 10.0f }; // 10.0f is the x, y, width and height of rect
    NG::RectF testCurrFrameRect = { 10.0f, 10.0f, 10.0f, 10.0f }; // 10.0f is the x, y, width and height of rect
    FrameNode::onSizeChangeDumpInfo dumpInfoOne { 1, testLastFrameRect, testCurrFrameRect };
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("page", 1, AceType::MakeRefPtr<PagePattern>(nullptr), true);
    EXPECT_NE(frameNode->pattern_, nullptr);
    frameNode->isActive_ = true;
    auto pattern = frameNode->GetPattern<PagePattern>();
    pattern->isOnShow_ = true;
    bool flag = false;
    OnSizeChangedFunc onSizeChanged = [&flag](const RectF& oldRect, const RectF& rect) { flag = !flag; };
    frameNode->GetEventHub<EventHub>()->AddInnerOnSizeChanged(1, std::move(onSizeChanged));
    frameNode->lastFrameNodeRect_ =
        std::make_unique<RectF>(RectF(OffsetF(50.0f, 50.0f), SizeF(50.0f, 50.0f))); // 50.0f is ths offset and size
    frameNode->onSizeChangeDumpInfos.push_back(dumpInfoOne);
    /**
     * @tc.steps: step3. call the function TriggerOnSizeChangeCallback.
     */
    frameNode->TriggerOnSizeChangeCallback();
}

/**
 * @tc.name: FrameNodIsFrameDisappear01
 * @tc.desc: Test the function IsFrameDisappear.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeIsFrameDisappear01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto parentNode = FrameNode::CreateFrameNode("parentNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    parentNode->isActive_ = false;
    frameNode->onMainTree_ = true;
    auto context = frameNode->GetContext();
    context->onShow_ = true;
    frameNode->SetParent(AceType::WeakClaim(AceType::RawPtr(parentNode)));

    /**
     * @tc.steps: step2. create layoutProperty.
     */
    auto parentLayoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    parentLayoutProperty->propVisibility_ = VisibleType::INVISIBLE;
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->propVisibility_ = VisibleType::VISIBLE;

    /**
     * @tc.steps: step3. call the function IsFrameDisappear.
     */
    parentNode->SetLayoutProperty(parentLayoutProperty);
    frameNode->SetLayoutProperty(layoutProperty);
    frameNode->IsFrameDisappear();
    EXPECT_FALSE(parentNode->isActive_);
    EXPECT_TRUE(frameNode->onMainTree_);
    EXPECT_NE(frameNode->pattern_, nullptr);
    EXPECT_NE(frameNode->layoutProperty_, nullptr);
}

/**
 * @tc.name: FrameNodIsFrameDisappear02
 * @tc.desc: Test the function IsFrameDisappear
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeIsFrameDisappear02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto parentNode = FrameNode::CreateFrameNode("parentNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    parentNode->isActive_ = true;
    frameNode->onMainTree_ = true;
    auto context = frameNode->GetContext();
    context->onShow_ = true;
    frameNode->SetParent(AceType::WeakClaim(AceType::RawPtr(parentNode)));

    /**
     * @tc.steps: step2. create layoutProperty.
     */
    auto parentLayoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    parentLayoutProperty->propVisibility_ = VisibleType::INVISIBLE;
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->propVisibility_ = VisibleType::VISIBLE;

    /**
     * @tc.steps: step3. call the function IsFrameDisappear.
     */
    parentNode->SetLayoutProperty(parentLayoutProperty);
    frameNode->SetLayoutProperty(layoutProperty);
    frameNode->IsFrameDisappear();
    EXPECT_TRUE(parentNode->isActive_);
    EXPECT_TRUE(frameNode->onMainTree_);
    EXPECT_NE(frameNode->pattern_, nullptr);
    EXPECT_NE(frameNode->layoutProperty_, nullptr);
}

/**
 * @tc.name: FrameNodIsFrameDisappear03
 * @tc.desc: Test the function IsFrameDisappear
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeIsFrameDisappear03, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto parentNode = FrameNode::CreateFrameNode("parentNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    parentNode->isActive_ = true;
    frameNode->isActive_ = false;
    frameNode->onMainTree_ = true;
    auto context = frameNode->GetContext();
    context->onShow_ = true;
    frameNode->SetParent(AceType::WeakClaim(AceType::RawPtr(parentNode)));

    /**
     * @tc.steps: step2. create layoutProperty.
     */
    auto parentLayoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    parentLayoutProperty->propVisibility_ = VisibleType::INVISIBLE;
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->propVisibility_ = VisibleType::VISIBLE;

    /**
     * @tc.steps: step3. call the function IsFrameDisappear.
     */
    parentNode->SetLayoutProperty(parentLayoutProperty);
    frameNode->SetLayoutProperty(layoutProperty);
    frameNode->IsFrameDisappear(TIMESTAMP_1);
    EXPECT_TRUE(parentNode->isActive_);
    EXPECT_TRUE(frameNode->onMainTree_);
    EXPECT_NE(frameNode->pattern_, nullptr);
    EXPECT_NE(frameNode->layoutProperty_, nullptr);
}

/**
 * @tc.name: FrameNodIsFrameDisappear04
 * @tc.desc: Test the function IsFrameDisappear
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeIsFrameDisappear04, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto parentNode = FrameNode::CreateFrameNode("parentNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto frameNode2 = FrameNode::CreateFrameNode("frameNode2", 2, AceType::MakeRefPtr<Pattern>(), true);
    parentNode->SetDepth(1);
    frameNode->SetDepth(2);
    frameNode2->SetDepth(3);
    parentNode->isActive_ = true;
    frameNode->isActive_ = true;
    frameNode2->onMainTree_ = true;
    frameNode2->isActive_ = true;
    auto context = frameNode2->GetContext();
    context->onShow_ = true;
    frameNode->SetParent(AceType::WeakClaim(AceType::RawPtr(parentNode)));
    frameNode2->SetParent(AceType::WeakClaim(AceType::RawPtr(frameNode)));

    /**
     * @tc.steps: step2. create layoutProperty.
     */
    auto parentLayoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    parentLayoutProperty->propVisibility_ = VisibleType::VISIBLE;
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->propVisibility_ = VisibleType::VISIBLE;
    auto layoutProperty2 = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty2->propVisibility_ = VisibleType::VISIBLE;

    /**
     * @tc.steps: step3. call the function IsFrameDisappear and create TIMESTAMP_1 cache.
     * @tc.expected: expect res is false
     */
    parentNode->SetLayoutProperty(parentLayoutProperty);
    frameNode->SetLayoutProperty(layoutProperty);
    frameNode2->SetLayoutProperty(layoutProperty2);
    EXPECT_FALSE(frameNode2->IsFrameDisappear(TIMESTAMP_1));

    /**
     * @tc.steps: step4. call the function IsFrameDisappear and use TIMESTAMP_1 cache.
     * @tc.expected: expect res is false
     */
    parentLayoutProperty->propVisibility_ = VisibleType::INVISIBLE;
    EXPECT_FALSE(frameNode2->IsFrameDisappear(TIMESTAMP_2, 0));

    /**
     * @tc.steps: step5. call the function IsFrameDisappear and no use TIMESTAMP_1 cache.
     * @tc.expected: expect res is true
     */
    EXPECT_TRUE(frameNode2->IsFrameDisappear(TIMESTAMP_3));
}

/**
 * @tc.name: FrameNodIsFrameDisappear05
 * @tc.desc: Test the function IsFrameDisappear
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeIsFrameDisappear05, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto parentNode = FrameNode::CreateFrameNode("parentNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto frameNode2 = FrameNode::CreateFrameNode("frameNode2", 2, AceType::MakeRefPtr<Pattern>(), true);
    parentNode->SetDepth(1);
    frameNode->SetDepth(2);
    frameNode2->SetDepth(3);
    parentNode->isActive_ = true;
    frameNode->isActive_ = true;
    frameNode2->onMainTree_ = true;
    frameNode2->isActive_ = true;
    auto context = frameNode2->GetContext();
    context->onShow_ = true;
    frameNode->SetParent(AceType::WeakClaim(AceType::RawPtr(parentNode)));
    frameNode2->SetParent(AceType::WeakClaim(AceType::RawPtr(frameNode)));

    /**
     * @tc.steps: step2. create layoutProperty.
     */
    auto parentLayoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    parentLayoutProperty->propVisibility_ = VisibleType::VISIBLE;
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->propVisibility_ = VisibleType::VISIBLE;
    auto layoutProperty2 = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty2->propVisibility_ = VisibleType::VISIBLE;

    /**
     * @tc.steps: step3. call the function IsFrameDisappear and create TIMESTAMP_1 cache.
     * @tc.expected: expect res is false
     */
    parentNode->SetLayoutProperty(parentLayoutProperty);
    frameNode->SetLayoutProperty(layoutProperty);
    frameNode2->SetLayoutProperty(layoutProperty2);
    EXPECT_FALSE(frameNode2->IsFrameDisappear(TIMESTAMP_1));

    /**
     * @tc.steps: step4. call the function IsFrameDisappear and use TIMESTAMP_1 cache.
     * @tc.expected: expect res is false
     */
    parentLayoutProperty->propVisibility_ = VisibleType::INVISIBLE;
    EXPECT_FALSE(frameNode2->IsFrameDisappear(TIMESTAMP_2, 3));

    /**
     * @tc.steps: step5. call the function IsFrameDisappear and no use TIMESTAMP_1 cache.
     * @tc.expected: expect res is true
     */
    EXPECT_TRUE(frameNode2->IsFrameDisappear(TIMESTAMP_3, 1));
}

/**
 * @tc.name: FrameNodIsFrameDisappear06
 * @tc.desc: Test the function IsFrameDisappear OnShow branch
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeIsFrameDisappear06, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto parentNode = FrameNode::CreateFrameNode("parentNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto frameNode2 = FrameNode::CreateFrameNode("frameNode2", 2, AceType::MakeRefPtr<Pattern>(), true);
    parentNode->SetDepth(1);
    frameNode->SetDepth(2);
    frameNode2->SetDepth(3);
    parentNode->isActive_ = true;
    frameNode->isActive_ = true;
    frameNode2->onMainTree_ = true;
    frameNode2->isActive_ = true;
    auto context = frameNode2->GetContext();
    context->onShow_ = true;
    frameNode->SetParent(AceType::WeakClaim(AceType::RawPtr(parentNode)));
    frameNode2->SetParent(AceType::WeakClaim(AceType::RawPtr(frameNode)));

    /**
     * @tc.steps: step2. create layoutProperty.
     */
    auto parentLayoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    parentLayoutProperty->propVisibility_ = VisibleType::INVISIBLE;
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->propVisibility_ = VisibleType::VISIBLE;
    auto layoutProperty2 = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty2->propVisibility_ = VisibleType::VISIBLE;

    /**
     * @tc.steps: step3. call the function IsFrameDisappear and create TIMESTAMP_1 cache.
     * @tc.expected: expect res is true
     */
    parentNode->SetLayoutProperty(parentLayoutProperty);
    frameNode->SetLayoutProperty(layoutProperty);
    frameNode2->SetLayoutProperty(layoutProperty2);
    EXPECT_TRUE(frameNode2->IsFrameDisappear(TIMESTAMP_1));

    /**
     * @tc.steps: step4. set onshow false and call the function IsFrameDisappear.
     * @tc.expected: expect res is true
     */
    parentLayoutProperty->propVisibility_ = VisibleType::VISIBLE;
    context->onShow_ = false;
    EXPECT_TRUE(frameNode2->IsFrameDisappear(TIMESTAMP_2, 1));

    /**
     * @tc.steps: step5. call the function IsFrameDisappear and no use TIMESTAMP_1 cache.
     * @tc.expected: expect res is true
     */
    context->onShow_ = true;
    EXPECT_FALSE(frameNode2->IsFrameDisappear(TIMESTAMP_3, 0));
}

/**
 * @tc.name: FrameNodIsFrameDisappear07
 * @tc.desc: Test the function IsFrameDisappear result true branch
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeIsFrameDisappear07, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto parentNode = FrameNode::CreateFrameNode("parentNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto frameNode2 = FrameNode::CreateFrameNode("frameNode2", 2, AceType::MakeRefPtr<Pattern>(), true);
    parentNode->SetDepth(1);
    frameNode->SetDepth(2);
    frameNode2->SetDepth(3);
    parentNode->isActive_ = true;
    frameNode->isActive_ = true;
    frameNode2->onMainTree_ = true;
    frameNode2->isActive_ = true;
    auto context = frameNode2->GetContext();
    context->onShow_ = true;
    frameNode->SetParent(AceType::WeakClaim(AceType::RawPtr(parentNode)));
    frameNode2->SetParent(AceType::WeakClaim(AceType::RawPtr(frameNode)));

    /**
     * @tc.steps: step2. create layoutProperty.
     */
    auto parentLayoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    parentLayoutProperty->propVisibility_ = VisibleType::VISIBLE;
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->propVisibility_ = VisibleType::VISIBLE;
    auto layoutProperty2 = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty2->propVisibility_ = VisibleType::VISIBLE;

    /**
     * @tc.steps: step3. call the function IsFrameDisappear and create TIMESTAMP_1 cache.
     * @tc.expected: expect res is false
     */
    parentNode->SetLayoutProperty(parentLayoutProperty);
    frameNode->SetLayoutProperty(layoutProperty);
    frameNode2->SetLayoutProperty(layoutProperty2);
    EXPECT_FALSE(frameNode2->IsFrameDisappear(TIMESTAMP_1));

    /**
     * @tc.steps: step4. set frameNode2 INVISIBLE and call the function IsFrameDisappear.
     * @tc.expected: expect res is false
     */
    parentLayoutProperty->propVisibility_ = VisibleType::INVISIBLE;
    layoutProperty2->propVisibility_ = VisibleType::INVISIBLE;
    EXPECT_TRUE(frameNode2->IsFrameDisappear(TIMESTAMP_2, 1));

    /**
     * @tc.steps: step5. call the function IsFrameDisappear and no use TIMESTAMP_1 cache.
     * @tc.expected: expect res is true
     */
    layoutProperty2->propVisibility_ = VisibleType::VISIBLE;
    EXPECT_TRUE(frameNode2->IsFrameDisappear(TIMESTAMP_3, 3));
}

/**
 * @tc.name: FrameNodeCalculateOffsetRelativeToWindow01
 * @tc.desc: Test the function CalculateOffsetRelativeToWindow
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeCalculateOffsetRelativeToWindow01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto parentNode = FrameNode::CreateFrameNode("parentNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto frameNode2 = FrameNode::CreateFrameNode("frameNode2", 2, AceType::MakeRefPtr<Pattern>(), true);
    parentNode->SetDepth(1);
    frameNode->SetDepth(2);
    frameNode2->SetDepth(3);
    frameNode->SetParent(AceType::WeakClaim(AceType::RawPtr(parentNode)));
    frameNode2->SetParent(AceType::WeakClaim(AceType::RawPtr(frameNode)));

    /**
     * @tc.steps: step2. set Offset.
     */
    parentNode->GetGeometryNode()->SetFrameOffset(OffsetF(1.1, 2.3));
    frameNode->GetGeometryNode()->SetSelfAdjust(RectF(1.0, 1.0, 0.0, 0.0));
    frameNode->GetGeometryNode()->SetFrameOffset(OffsetF(3.2, 4.1));
    frameNode2->GetGeometryNode()->SetFrameOffset(OffsetF(5.3, 6.3));

    /**
     * @tc.steps: step3. call the function CalculateOffsetRelativeToWindow and create TIMESTAMP_1 cache.
     * @tc.expected: expect res is frameNode offset + parentNode offset
     */
    EXPECT_EQ(frameNode->CalculateOffsetRelativeToWindow(TIMESTAMP_1), OffsetF(5.3, 7.4));
 
    /**
     * @tc.steps: step4. call the function CalculateOffsetRelativeToWindow and create TIMESTAMP_1 cache.
     * @tc.expected: expect res is frameNode2 offset + framenode cache offset
     */

    parentNode->GetGeometryNode()->SetFrameOffset(OffsetF(2.1, 3.3));
    EXPECT_EQ(frameNode2->CalculateOffsetRelativeToWindow(TIMESTAMP_1), OffsetF(10.6, 13.7));


    /**
     * @tc.steps: step5. call the function CalculateOffsetRelativeToWindow TIMESTAMP_2.
     * @tc.expected: expect res is frameNode2 offset + framenode offset + parentNode offset
     */
    EXPECT_EQ(frameNode2->CalculateOffsetRelativeToWindow(TIMESTAMP_2), OffsetF(11.6, 14.7));
}

/**
 * @tc.name: FrameNodeCalculateOffsetRelativeToWindow02
 * @tc.desc: Test the function CalculateOffsetRelativeToWindow
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeCalculateOffsetRelativeToWindow02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto parentNode = FrameNode::CreateFrameNode("parentNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto frameNode2 = FrameNode::CreateFrameNode("frameNode2", 2, AceType::MakeRefPtr<Pattern>(), true);
    parentNode->SetDepth(1);
    frameNode->SetDepth(2);
    frameNode2->SetDepth(3);
    frameNode->SetParent(AceType::WeakClaim(AceType::RawPtr(parentNode)));
    frameNode2->SetParent(AceType::WeakClaim(AceType::RawPtr(frameNode)));

    /**
     * @tc.steps: step2. set Offset.
     */
    parentNode->GetGeometryNode()->SetFrameOffset(OffsetF(1.1, 2.3));
    frameNode->GetGeometryNode()->SetFrameOffset(OffsetF(3.2, 4.1));
    frameNode2->GetGeometryNode()->SetFrameOffset(OffsetF(5.3, 6.3));

    /**
     * @tc.steps: step3. call the function CalculateOffsetRelativeToWindow and create TIMESTAMP_1 cache.
     * @tc.expected: expect res is frameNode2 offset + frameNode offset + parentNode offset
     */
    EXPECT_EQ(frameNode2->CalculateOffsetRelativeToWindow(TIMESTAMP_1), OffsetF(9.6, 12.7));

    /**
     * @tc.steps: step4. call the function CalculateOffsetRelativeToWindow and use TIMESTAMP_1 cache.
     * @tc.expected: expect res is frameNode2 offset + framenode cache offset
     */

    parentNode->GetGeometryNode()->SetFrameOffset(OffsetF(2.1, 3.3));
    EXPECT_EQ(frameNode2->CalculateOffsetRelativeToWindow(TIMESTAMP_2, false, 0), OffsetF(9.6, 12.7));


    /**
     * @tc.steps: step5. call the function CalculateOffsetRelativeToWindow TIMESTAMP_2.
     * @tc.expected: expect res is frameNode2 offset + framenode offset + parentNode offset
     */
    EXPECT_EQ(frameNode2->CalculateOffsetRelativeToWindow(TIMESTAMP_3), OffsetF(10.6, 13.7));
}

/**
 * @tc.name: FrameNodeCalculateOffsetRelativeToWindow03
 * @tc.desc: Test the function CalculateOffsetRelativeToWindow
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeCalculateOffsetRelativeToWindow03, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto parentNode = FrameNode::CreateFrameNode("parentNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto frameNode2 = FrameNode::CreateFrameNode("frameNode2", 2, AceType::MakeRefPtr<Pattern>(), true);
    parentNode->SetDepth(1);
    frameNode->SetDepth(2);
    frameNode2->SetDepth(3);
    frameNode->SetParent(AceType::WeakClaim(AceType::RawPtr(parentNode)));
    frameNode2->SetParent(AceType::WeakClaim(AceType::RawPtr(frameNode)));

    /**
     * @tc.steps: step2. set Offset.
     */
    parentNode->GetGeometryNode()->SetFrameOffset(OffsetF(1.1, 2.3));
    frameNode->GetGeometryNode()->SetFrameOffset(OffsetF(3.2, 4.1));
    frameNode2->GetGeometryNode()->SetFrameOffset(OffsetF(5.3, 6.3));

    /**
     * @tc.steps: step3. call the function CalculateOffsetRelativeToWindow and create TIMESTAMP_1 cache.
     * @tc.expected: expect res is frameNode offset + frameNode2 + parentNode offset
     */
    EXPECT_EQ(frameNode2->CalculateOffsetRelativeToWindow(TIMESTAMP_1), OffsetF(9.6, 12.7));

    /**
     * @tc.steps: step4. call the function CalculateOffsetRelativeToWindow and use TIMESTAMP_1 cache.
     * @tc.expected: expect res is frameNode2 offset + framenode cache offset
     */

    parentNode->GetGeometryNode()->SetFrameOffset(OffsetF(2.1, 3.3));
    EXPECT_EQ(frameNode2->CalculateOffsetRelativeToWindow(TIMESTAMP_2, false, 2), OffsetF(9.6, 12.7));


    /**
     * @tc.steps: step5. call the function CalculateOffsetRelativeToWindow TIMESTAMP_3.
     * @tc.expected: expect res is frameNode2 offset + framenode offset + parentNode offset
     */
    EXPECT_EQ(frameNode2->CalculateOffsetRelativeToWindow(TIMESTAMP_3), OffsetF(10.6, 13.7));
}

/**
 * @tc.name: FrameNodeTriggerVisibleAreaChangeCallback01
 * @tc.desc: Test the function TriggerVisibleAreaChangeCallback
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTriggerVisibleAreaChangeCallback01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->onMainTree_ = true;
    frameNode->isActive_ = true;
    frameNode->isWindowBoundary_ = false;
    auto context = frameNode->GetContext();
    context->onShow_ = true;
    VisibleCallbackInfo callbackInfo;
    int32_t flag = 0;
    const std::function<void(bool, double)>&& jsCallback = [&flag](bool isVisible, double radio) { flag++; };
    callbackInfo.callback = jsCallback;
    callbackInfo.period = 1;
    frameNode->GetEventHub<EventHub>()->visibleAreaUserCallback_ = callbackInfo;
    frameNode->TriggerVisibleAreaChangeCallback(0, false);
    frameNode->GetEventHub<EventHub>()->visibleAreaUserCallback_.callback = nullptr;
    frameNode->GetEventHub<EventHub>()->visibleAreaInnerCallback_ = callbackInfo;
    frameNode->TriggerVisibleAreaChangeCallback(0, false);
    EXPECT_NE(frameNode->GetEventHub<EventHub>(), nullptr);
    frameNode->isCalculateInnerVisibleRectClip_ = true;
    frameNode->lastInnerVisibleRatio_ = 10.0;
    frameNode->lastVisibleRatio_ = 10.0;
    frameNode->TriggerVisibleAreaChangeCallback(0, true);
    frameNode->GetEventHub<EventHub>()->visibleAreaUserCallback_ = callbackInfo;
    /**
     * @tc.steps: step2. create layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->propVisibility_ = VisibleType::VISIBLE;

    /**
     * @tc.steps: step3. call the function TriggerVisibleAreaChangeCallback.
     */
    std::vector<double> ratios = { 0, 1.0 };
    frameNode->SetLayoutProperty(layoutProperty);
    frameNode->TriggerVisibleAreaChangeCallback(false);
    frameNode->ProcessAllVisibleCallback(ratios, callbackInfo, 1.0, 0.0, true);
    EXPECT_NE(frameNode->GetEventHub<EventHub>(), nullptr);
}

/**
 * @tc.name: FrameNodeThrottledVisibleTask01
 * @tc.desc: Test the function ThrottledVisibleTask
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeThrottledVisibleTask01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->throttledCallbackOnTheWay_ = true;
    frameNode->lastThrottledVisibleRatio_ = 0.0;
    frameNode->isActive_ = true;
    auto context = frameNode->GetContext();
    context->onShow_ = false;
    VisibleCallbackInfo callbackInfo;
    int32_t flag = 0;
    const std::function<void(bool, double)>&& jsCallback = [&flag](bool isVisible, double radio) { flag++; };
    callbackInfo.callback = jsCallback;
    callbackInfo.period = 1;
    frameNode->GetEventHub<EventHub>()->throttledVisibleAreaCallback_ = callbackInfo;

    /**
     * @tc.steps: step2. create layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->propVisibility_ = VisibleType::VISIBLE;

    /**
     * @tc.steps: step3. call the function ThrottledVisibleTask.
     */
    frameNode->SetLayoutProperty(layoutProperty);
    frameNode->ThrottledVisibleTask();
    EXPECT_NE(frameNode, nullptr);
    EXPECT_FALSE(frameNode->throttledCallbackOnTheWay_);
}

/**
 * @tc.name: FrameNodeThrottledVisibleTask02
 * @tc.desc: Test the function ThrottledVisibleTask
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeThrottledVisibleTask02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->throttledCallbackOnTheWay_ = true;
    frameNode->lastThrottledVisibleRatio_ = 1.0;
    frameNode->isActive_ = true;
    auto context = frameNode->GetContext();
    context->onShow_ = false;
    VisibleCallbackInfo callbackInfo;
    int32_t flag = 0;
    const std::function<void(bool, double)>&& jsCallback = [&flag](bool isVisible, double radio) { flag++; };
    callbackInfo.callback = jsCallback;
    callbackInfo.period = 1;
    frameNode->GetEventHub<EventHub>()->throttledVisibleAreaCallback_ = callbackInfo;

    /**
     * @tc.steps: step2. create layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->propVisibility_ = VisibleType::VISIBLE;

    /**
     * @tc.steps: step3. call the function ThrottledVisibleTask.
     */
    frameNode->SetLayoutProperty(layoutProperty);
    frameNode->ThrottledVisibleTask();
    EXPECT_NE(frameNode, nullptr);
    EXPECT_FALSE(frameNode->throttledCallbackOnTheWay_);
    EXPECT_TRUE(frameNode->isActive_);
    EXPECT_EQ(frameNode->GetEventHub<EventHub>()->throttledVisibleAreaCallback_.period, 1);
}

/**
 * @tc.name: FrameNodeThrottledVisibleTask03
 * @tc.desc: Test the function ThrottledVisibleTask
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeThrottledVisibleTask03, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->throttledCallbackOnTheWay_ = false;
    VisibleCallbackInfo callbackInfo;
    int32_t flag = 0;
    const std::function<void(bool, double)>&& jsCallback = [&flag](bool isVisible, double radio) { flag++; };
    callbackInfo.callback = jsCallback;
    callbackInfo.period = 1;
    frameNode->GetEventHub<EventHub>()->throttledVisibleAreaCallback_ = callbackInfo;

    /**
     * @tc.steps: step2. call the function ThrottledVisibleTask.
     */
    frameNode->ThrottledVisibleTask();
    EXPECT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetEventHub<EventHub>()->throttledVisibleAreaCallback_.period, 1);
}

/**
 * @tc.name: FrameNodeCreateLayoutTask01
 * @tc.desc: Test the function CreateLayoutTask
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeCreateLayoutTask01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->isLayoutDirtyMarked_ = true;

    /**
     * @tc.steps: step2. create layoutProperty.
     */
    NG::RectF testRect = { 10.0f, 10.0f, 10.0f, 10.0f }; // 10.0f is the x, y, width and height of rect
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->SetLayoutRect(testRect);
    layoutProperty->propVisibility_ = VisibleType::VISIBLE;

    /**
     * @tc.steps: step3. call the function CreateLayoutTask.
     */
    frameNode->SetLayoutProperty(layoutProperty);
    frameNode->CreateLayoutTask(true);
    EXPECT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->layoutProperty_->propVisibility_, VisibleType::VISIBLE);
}

/**
 * @tc.name: FrameNodeCreateRenderTask01
 * @tc.desc: Test the function CreateRenderTask
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeCreateRenderTask01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->isRenderDirtyMarked_ = true;
    frameNode->UpdateInspectorId("123");
    frameNode->renderContext_->UpdateAccessibilityFocus(true);
    /**
     * @tc.steps: step2. create layoutProperty.
     */
    NG::RectF testRect = { 10.0f, 10.0f, 10.0f, 10.0f }; // 10.0f is the x, y, width and height of rect
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->SetLayoutRect(testRect);
    layoutProperty->propVisibility_ = VisibleType::VISIBLE;

    /**
     * @tc.steps: step3. call the function CreateRenderTask.
     */
    frameNode->SetLayoutProperty(layoutProperty);
    frameNode->CreateRenderTask(true).value()();
    EXPECT_NE(frameNode, nullptr);
    EXPECT_NE(frameNode->layoutProperty_, nullptr);
    EXPECT_EQ(frameNode->layoutProperty_->propVisibility_, VisibleType::VISIBLE);
}

/**
 * @tc.name: FrameNodeCreateRenderTask02
 * @tc.desc: Test the function CreateRenderTask
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeCreateRenderTask02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->isRenderDirtyMarked_ = true;
    frameNode->renderContext_->UpdateAccessibilityFocus(true);
    /**
     * @tc.steps: step2. create layoutProperty.
     */
    NG::RectF testRect = { 10.0f, 10.0f, 10.0f, 10.0f }; // 10.0f is the x, y, width and height of rect
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->SetLayoutRect(testRect);
    layoutProperty->propVisibility_ = VisibleType::VISIBLE;

    /**
     * @tc.steps: step3. call the function CreateRenderTask.
     */
    frameNode->SetLayoutProperty(layoutProperty);
    frameNode->CreateRenderTask(false).value()();
    EXPECT_NE(frameNode, nullptr);
    EXPECT_NE(frameNode->layoutProperty_, nullptr);
    EXPECT_EQ(frameNode->layoutProperty_->propVisibility_, VisibleType::VISIBLE);
}

/**
 * @tc.name: FrameNodeUpdateLayoutWrapper01
 * @tc.desc: Test the function UpdateLayoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeUpdateLayoutWrapper01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto testNode = FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(testNode, geometryNode, testNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. create layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->propVisibility_ = VisibleType::GONE;
    layoutProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_LAYOUT);

    /**
     * @tc.steps: step3. call the function UpdateLayoutWrapper.
     */
    frameNode->SetLayoutProperty(layoutProperty);
    frameNode->UpdateLayoutWrapper(layoutWrapper, false, true);
    EXPECT_NE(frameNode, nullptr);
    EXPECT_NE(frameNode->layoutProperty_, nullptr);
    EXPECT_EQ(frameNode->layoutProperty_->propVisibility_, VisibleType::GONE);
}

/**
 * @tc.name: FrameNodeUpdateLayoutWrapper02
 * @tc.desc: Test the function UpdateLayoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeUpdateLayoutWrapper02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. create layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->propVisibility_ = VisibleType::VISIBLE;
    layoutProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_LAYOUT);

    /**
     * @tc.steps: step3. call the function UpdateLayoutWrapper.
     */
    frameNode->SetLayoutProperty(layoutProperty);
    frameNode->UpdateLayoutWrapper(nullptr, false, true);
    EXPECT_NE(frameNode, nullptr);
    EXPECT_NE(frameNode->layoutProperty_, nullptr);
    EXPECT_EQ(frameNode->layoutProperty_->propVisibility_, VisibleType::VISIBLE);
}

/**
 * @tc.name: FrameNodeGetContentModifier01
 * @tc.desc: Test the function GetContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetContentModifier01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 1, AceType::MakeRefPtr<ImagePattern>(), true);
    frameNode->renderContext_->UpdateAccessibilityFocus(true);
    frameNode->GetPattern<ImagePattern>()->image_ = AceType::MakeRefPtr<NG::MockCanvasImage>();

    /**
     * @tc.steps: step2. call the function GetContentModifier.
     */
    frameNode->GetContentModifier();
    frameNode->renderContext_->UpdateAccessibilityFocus(false);
    frameNode->GetContentModifier();
    EXPECT_NE(frameNode, nullptr);
}

/**
 * @tc.name: FrameNodeGetContentModifier02
 * @tc.desc: Test the function GetContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetContentModifier02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 1, AceType::MakeRefPtr<ImagePattern>(), true);
    frameNode->renderContext_->UpdateAccessibilityFocus(true);
    frameNode->GetPattern<ImagePattern>()->image_ = AceType::MakeRefPtr<NG::MockCanvasImage>();
    frameNode->extensionHandler_ = AceType::MakeRefPtr<ExtensionHandler>();

    /**
     * @tc.steps: step2. call the function GetContentModifier.
     */
    frameNode->GetContentModifier();
    EXPECT_NE(frameNode->extensionHandler_, nullptr);
}

/**
 * @tc.name: FrameNodeGetContentModifier03
 * @tc.desc: Test the function GetContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetContentModifier03, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->renderContext_->UpdateAccessibilityFocus(true);
    /**
     * @tc.steps: step2. call the function GetContentModifier.
     */
    frameNode->GetContentModifier();
    EXPECT_NE(frameNode, nullptr);
}

/**
 * @tc.name: FrameNodePostIdleTask01
 * @tc.desc: Test the function PostIdleTask
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodePostIdleTask01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    /**
     * @tc.steps: step2. call the function PostIdleTask.
     */
    int32_t flag = 0;
    std::function<void(int64_t, bool)>&& callback = [&flag](int64_t radio, bool isVisible) { flag++; };
    frameNode->PostIdleTask(std::move(callback));
    EXPECT_NE(frameNode, nullptr);
}

/**
 * @tc.name: FrameNodeRebuildRenderContextTree01
 * @tc.desc: Test the function RebuildRenderContextTree
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeRebuildRenderContextTree01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->needSyncRenderTree_ = true;
    frameNode->overlayNode_ = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. create layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->propVisibility_ = VisibleType::VISIBLE;

    /**
     * @tc.steps: step3. call the function RebuildRenderContextTree.
     */
    frameNode->overlayNode_->SetLayoutProperty(layoutProperty);
    frameNode->RebuildRenderContextTree();
    EXPECT_NE(frameNode->overlayNode_, nullptr);

    /**
     * @tc.steps: step4. update layoutProperty and call the function RebuildRenderContextTree.
     */
    layoutProperty->propVisibility_ = VisibleType::INVISIBLE;
    frameNode->overlayNode_->SetLayoutProperty(layoutProperty);
    frameNode->RebuildRenderContextTree();

    /**
     * @tc.steps: step5. update overlayNode_ nullptr and call the function RebuildRenderContextTree.
     */
    frameNode->overlayNode_ = nullptr;
    frameNode->RebuildRenderContextTree();
    EXPECT_EQ(frameNode->overlayNode_, nullptr);
}

/**
 * @tc.name: FrameNodeRebuildRenderContextTree02
 * @tc.desc: Test the function RebuildRenderContextTree
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeRebuildRenderContextTree02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->needSyncRenderTree_ = true;
    frameNode->overlayNode_ = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. create layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->propVisibility_ = VisibleType::INVISIBLE;

    /**
     * @tc.steps: step3. call the function RebuildRenderContextTree.
     */
    frameNode->overlayNode_->SetLayoutProperty(layoutProperty);
    frameNode->RebuildRenderContextTree();
    EXPECT_NE(frameNode->overlayNode_->layoutProperty_, nullptr);
}

/**
 * @tc.name: FrameNodeRebuildRenderContextTree03
 * @tc.desc: Test the function RebuildRenderContextTree
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeRebuildRenderContextTree03, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->needSyncRenderTree_ = true;
    frameNode->overlayNode_ = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    frameNode->overlayNode_->layoutProperty_ = nullptr;

    /**
     * @tc.steps: step2. call the function RebuildRenderContextTree.
     */
    frameNode->RebuildRenderContextTree();
    EXPECT_EQ(frameNode->overlayNode_->layoutProperty_, nullptr);
}

/**
 * @tc.name: FrameNodeMarkModifyDone01
 * @tc.desc: Test the function MarkModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeMarkModifyDone01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->isPrivacySensitive_ = true;
    frameNode->isRestoreInfoUsed_ = false;
    frameNode->restoreId_ = 1;
    auto index = static_cast<int32_t>(Recorder::EventCategory::CATEGORY_COMPONENT);
    Recorder::EventRecorder::Get().eventSwitch_[index] = true;
    Recorder::EventRecorder::Get().globalSwitch_[index] = true;
    std::unordered_set<std::string> nodeSet;
    nodeSet.emplace("abc");
    Recorder::NodeDataCache::Get().mergedConfig_->shareNodes.emplace("test", nodeSet);

    /**
     * @tc.steps: step2. call the function MarkModifyDone.
     */
    frameNode->MarkModifyDone();
    EXPECT_TRUE(frameNode->isPrivacySensitive_);
    EXPECT_TRUE(frameNode->isRestoreInfoUsed_);
}

/**
 * @tc.name: FrameNodeMarkModifyDone02
 * @tc.desc: Test the function MarkModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeMarkModifyDone02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->isPrivacySensitive_ = true;
    frameNode->isRestoreInfoUsed_ = false;
    frameNode->restoreId_ = 1;
    auto pipeline = MockPipelineContext::GetCurrentContext();
    pipeline->privacySensitiveManager_ = nullptr;

    /**
     * @tc.steps: step2. call the function MarkModifyDone.
     */
    frameNode->MarkModifyDone();
    EXPECT_TRUE(frameNode->isPrivacySensitive_);
    EXPECT_TRUE(frameNode->isRestoreInfoUsed_);
    EXPECT_EQ(pipeline->privacySensitiveManager_, nullptr);
}

/**
 * @tc.name: FrameNodeMarkDirtyNode01
 * @tc.desc: Test the function MarkDirtyNode
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeMarkDirtyNode01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->isPropertyDiffMarked_ = true;
    auto testNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    testNode->isPropertyDiffMarked_ = false;

    /**
     * @tc.steps: step2. call the function MarkDirtyNode.
     */
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_DIFF);
    testNode->MarkDirtyNode(PROPERTY_UPDATE_DIFF);
    EXPECT_FALSE(frameNode->isPrivacySensitive_);
    EXPECT_FALSE(frameNode->isRestoreInfoUsed_);
}

/**
 * @tc.name: FrameNodeGetAncestorNodeOfFrame01
 * @tc.desc: Test the function GetAncestorNodeOfFrame
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetAncestorNodeOfFrame01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->isWindowBoundary_ = true;

    /**
     * @tc.steps: step2. call the function GetAncestorNodeOfFrame.
     */
    frameNode->GetAncestorNodeOfFrame(true);
    EXPECT_TRUE(frameNode->isWindowBoundary_);
}

/**
 * @tc.name: FrameNodeGetFirstAutoFillContainerNode01
 * @tc.desc: Test the function GetFirstAutoFillContainerNode
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetFirstAutoFillContainerNode01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. call the function GetFirstAutoFillContainerNode.
     */
    frameNode->GetFirstAutoFillContainerNode();
    EXPECT_NE(frameNode, nullptr);
}

/**
 * @tc.name: FrameNodeGetFirstAutoFillContainerNode02
 * @tc.desc: Test the function GetFirstAutoFillContainerNode
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetFirstAutoFillContainerNode02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TABS_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);
    auto parentNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);
    parentNode->AddChild(frameNode);

    /**
     * @tc.steps: step2. call the function GetFirstAutoFillContainerNode.
     */
    frameNode->GetFirstAutoFillContainerNode();
    EXPECT_NE(frameNode, nullptr);
    EXPECT_NE(parentNode, nullptr);
}

/**
 * @tc.name: FrameNodeGetFirstAutoFillContainerNode03
 * @tc.desc: Test the function GetFirstAutoFillContainerNode
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetFirstAutoFillContainerNode03, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TABS_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);
    auto parentNode = FrameNode::CreateFrameNode(V2::TABS_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);
    parentNode->AddChild(frameNode);

    /**
     * @tc.steps: step2. call the function GetFirstAutoFillContainerNode.
     */
    frameNode->GetFirstAutoFillContainerNode();
    EXPECT_NE(frameNode, nullptr);
    EXPECT_NE(parentNode, nullptr);
}

/**
 * @tc.name: FrameNodeNotifyFillRequestSuccess01
 * @tc.desc: Test the function NotifyFillRequestSuccess
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeNotifyFillRequestSuccess01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);

    /**
     * @tc.steps: step2. call the function NotifyFillRequestSuccess.
     */
    auto viewDataWrap = ViewDataWrap::CreateViewDataWrap();
    auto nodeWrap = PageNodeInfoWrap::CreatePageNodeInfoWrap();
    frameNode->NotifyFillRequestSuccess(viewDataWrap, nodeWrap, AceAutoFillType::ACE_PASSWORD);
    auto pattern = frameNode->pattern_;
    frameNode->pattern_ = nullptr;
    frameNode->NotifyFillRequestSuccess(viewDataWrap, nodeWrap, AceAutoFillType::ACE_PASSWORD);
    frameNode->pattern_ = pattern;
}

/**
 * @tc.name: FrameNodeNotifyFillRequestFailed01
 * @tc.desc: Test the function NotifyFillRequestFailed
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeNotifyFillRequestFailed01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);

    /**
     * @tc.steps: step2. call the function NotifyFillRequestFailed.
     */
    auto pattern = frameNode->pattern_;
    frameNode->pattern_ = nullptr;
    frameNode->NotifyFillRequestFailed(1, "test", true);
    frameNode->pattern_ = pattern;
}

/**
 * @tc.name: FrameNodeMarkNeedRender01
 * @tc.desc: Test the function MarkNeedRender
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeMarkNeedRender01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->isLayoutDirtyMarked_ = false;
    frameNode->isRenderDirtyMarked_ = false;

    /**
     * @tc.steps: step2. call the function MarkNeedRender.
     */
    frameNode->MarkNeedRender(false);
    EXPECT_FALSE(frameNode->isLayoutDirtyMarked_);
    EXPECT_TRUE(frameNode->isRenderDirtyMarked_);
}

/**
 * @tc.name: FrameNodeOnGenerateOneDepthVisibleFrame01
 * @tc.desc: Test the function OnGenerateOneDepthVisibleFrame
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeOnGenerateOneDepthVisibleFrame01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto childNode = FrameNode::CreateFrameNode("childNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->isLayoutNode_ = true;
    frameNode->overlayNode_ = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. call the function OnGenerateOneDepthVisibleFrame.
     */
    std::list<RefPtr<FrameNode>> children;
    children.push_back(childNode);
    frameNode->OnGenerateOneDepthVisibleFrame(children);
    EXPECT_TRUE(frameNode->isLayoutNode_);
}

/**
 * @tc.name: FrameNodeOnGenerateOneDepthVisibleFrame02
 * @tc.desc: Test the function OnGenerateOneDepthVisibleFrame
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeOnGenerateOneDepthVisibleFrame02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto childNode = FrameNode::CreateFrameNode("childNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->isLayoutNode_ = true;
    frameNode->overlayNode_ = nullptr;

    /**
     * @tc.steps: step2. call the function OnGenerateOneDepthVisibleFrame.
     */
    std::list<RefPtr<FrameNode>> children;
    children.push_back(childNode);
    frameNode->OnGenerateOneDepthVisibleFrame(children);
    EXPECT_TRUE(frameNode->isLayoutNode_);
    EXPECT_EQ(frameNode->overlayNode_, nullptr);
}

/**
 * @tc.name: FrameNodeOnGenerateOneDepthVisibleFrameWithTransition01
 * @tc.desc: Test the function OnGenerateOneDepthVisibleFrameWithTransition
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeOnGenerateOneDepthVisibleFrameWithTransition01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto childNode = FrameNode::CreateFrameNode("childNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->isLayoutNode_ = true;
    frameNode->isActive_ = true;
    frameNode->overlayNode_ = nullptr;

    /**
     * @tc.steps: step2. call the function OnGenerateOneDepthVisibleFrameWithTransition.
     */
    std::list<RefPtr<FrameNode>> children;
    children.push_back(childNode);
    frameNode->OnGenerateOneDepthVisibleFrameWithTransition(children);
    frameNode->overlayNode_ = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    frameNode->OnGenerateOneDepthVisibleFrameWithTransition(children);
    EXPECT_TRUE(frameNode->isActive_);
    EXPECT_TRUE(frameNode->isLayoutNode_);
    EXPECT_EQ(frameNode->overlayNode_, 1);
}

/**
 * @tc.name: FrameNodeProcessThrottledVisibleCallback01
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeProcessThrottledVisibleCallback01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    
    /**
     * @tc.steps: step2. set VisibleAreaUserCallback.
     */
    VisibleCallbackInfo callbackInfo;
    constexpr uint32_t minInterval = 100; // 100ms
    int flag = 0;
    callbackInfo.callback = [&flag](bool input1, double input2) { flag += 1; };
    callbackInfo.period = minInterval;
    frameNode->SetVisibleAreaUserCallback({ 0.2, 0.8, 0.21, 0.79, 0.5 }, callbackInfo);
    frameNode->lastThrottledVisibleRatio_ = 0.7f;

    /**
     * @tc.steps: step3. call the function ProcessThrottledVisibleCallback.
     */
    frameNode->ProcessThrottledVisibleCallback(true);
    EXPECT_TRUE(frameNode->eventHub_->GetThrottledVisibleAreaCallback().callback);
    EXPECT_FLOAT_EQ(frameNode->lastThrottledVisibleRatio_, 0.0f);
}

/**
 * @tc.name: FrameNodeProcessThrottledVisibleCallback02
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeProcessThrottledVisibleCallback02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);

    /**
     * @tc.steps: step2. set VisibleAreaUserCallback.
     */
    VisibleCallbackInfo callbackInfo;
    constexpr uint32_t minInterval = 100; // 100ms
    int flag = 0;
    callbackInfo.callback = [&flag](bool input1, double input2) { flag += 1; };
    callbackInfo.period = minInterval;
    frameNode->SetVisibleAreaUserCallback({ 0.2, 0.8, 0.21, 0.79, 0.5 }, callbackInfo);
    auto context = MockPipelineContext::GetCurrentContext();
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    /**
     * @tc.steps: step3. call the function ProcessThrottledVisibleCallback.
     */
    frameNode->throttledCallbackOnTheWay_ = true;
    frameNode->ProcessThrottledVisibleCallback(false);
    EXPECT_EQ(frameNode->throttledCallbackOnTheWay_, true);
}

/**
 * @tc.name: FrameNodeProcessThrottledVisibleCallback03
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeProcessThrottledVisibleCallback03, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);

    /**
     * @tc.steps: step2. set VisibleAreaUserCallback.
     */
    VisibleCallbackInfo callbackInfo;
    constexpr uint32_t minInterval = 100; // 100ms
    int flag = 0;
    callbackInfo.callback = [&flag](bool input1, double input2) { flag += 1; };
    callbackInfo.period = minInterval;
    frameNode->SetVisibleAreaUserCallback({ 0.2, 0.8, 0.21, 0.79, 0.5 }, callbackInfo);
    auto context = MockPipelineContext::GetCurrentContext();
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    
    /**
     * @tc.steps: step2. call the function ProcessThrottledVisibleCallback.
     */
    frameNode->GetEventHub<EventHub>()->GetOrCreateFocusHub();
    frameNode->throttledCallbackOnTheWay_ = false;
    frameNode->ProcessThrottledVisibleCallback(false);
    EXPECT_EQ(frameNode->throttledCallbackOnTheWay_, false);
}

/**
 * @tc.name: FrameNodeProcessThrottledVisibleCallback04
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeProcessThrottledVisibleCallback04, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);

    /**
     * @tc.steps: step2. set VisibleAreaUserCallback.
     */
    VisibleCallbackInfo callbackInfo;
    constexpr uint32_t minInterval = 100; // 100ms
    int flag = 0;
    callbackInfo.callback = [&flag](bool input1, double input2) { flag += 1; };
    callbackInfo.period = minInterval;
    frameNode->lastThrottledTriggerTime_ = GetCurrentTimestamp();
    frameNode->SetVisibleAreaUserCallback({ 0.2, 0.8, 0.21, 0.79, 0.5 }, callbackInfo);
    auto context = MockPipelineContext::GetCurrentContext();
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();

    /**
     * @tc.steps: step2. call the function ProcessThrottledVisibleCallback.
     */
    frameNode->GetEventHub<EventHub>()->GetOrCreateFocusHub();
    frameNode->throttledCallbackOnTheWay_ = false;
    frameNode->ProcessThrottledVisibleCallback(false);
}

/**
 * @tc.name: FrameNodeGetResponseRegionListForTouch01
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetResponseRegionListForTouch01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    /**
     * @tc.steps: step2. construct parameters.
     */
    frameNode->isActive_ = true;
    frameNode->GetEventHub<EventHub>()->SetEnabled(true);

    DimensionRect responseRect(Dimension(0), Dimension(0), DimensionOffset(OFFSETF));
    std::vector<DimensionRect> responseRegion;
    responseRegion.emplace_back(responseRect);

    /**
     * @tc.steps: step3. call GetResponseRegionList.
     * @tc.expected: expect ResponseRegion is not empty.
     */
    auto gestureEventHub = frameNode->GetEventHub<EventHub>()->GetOrCreateGestureEventHub();
    gestureEventHub->SetResponseRegion(responseRegion);

    auto paintRect = frameNode->renderContext_->GetPaintRectWithoutTransform();
    frameNode->GetResponseRegionListForTouch(paintRect);
    EXPECT_FALSE(gestureEventHub->GetResponseRegion().empty());
}

/**
 * @tc.name: FrameNodeGetResponseRegionListForTouch02
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetResponseRegionListForTouch02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    /**
     * @tc.steps: step2. construct parameters.
     */
    frameNode->isActive_ = true;
    frameNode->GetEventHub<EventHub>()->SetEnabled(true);

    DimensionRect responseRect(Dimension(0), Dimension(0), DimensionOffset(OFFSETF));
    std::vector<DimensionRect> responseRegion;
    responseRegion.emplace_back(responseRect);

    /**
     * @tc.steps: step3. call GetResponseRegionList.
     * @tc.expected: expect ResponseRegion is not empty.
     */
    auto gestureEventHub = frameNode->GetEventHub<EventHub>()->GetOrCreateGestureEventHub();
    gestureEventHub->SetResponseRegion(responseRegion);
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(1, 1);
    gestureEventHub->gestureHierarchy_.emplace_back(clickRecognizer);

    auto paintRect = frameNode->renderContext_->GetPaintRectWithoutTransform();
    frameNode->GetResponseRegionListForTouch(paintRect);
    EXPECT_FALSE(gestureEventHub->GetResponseRegion().empty());
}

/**
 * @tc.name: FrameNodeGetResponseRegionListForTouch03
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetResponseRegionListForTouch03, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    /**
     * @tc.steps: step2. construct parameters.
     */
    frameNode->isActive_ = true;
    frameNode->GetEventHub<EventHub>()->SetEnabled(true);

    /**
     * @tc.steps: step3. call GetResponseRegionList.
     * @tc.expected: expect ResponseRegion is not empty.
     */
    auto gestureEventHub = frameNode->GetEventHub<EventHub>()->GetOrCreateGestureEventHub();
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(1, 1);
    gestureEventHub->gestureHierarchy_.emplace_back(clickRecognizer);

    auto paintRect = frameNode->renderContext_->GetPaintRectWithoutTransform();
    auto responseRegionList = frameNode->GetResponseRegionListForTouch(paintRect);
    EXPECT_TRUE(responseRegionList.empty());
}

/**
 * @tc.name: FrameNodeProcessMouseTestHit01
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeProcessMouseTestHit01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    /**
     * @tc.steps: step2. construct parameters.
     */
    PointF globalPoint;
    PointF parentLocalPoint;
    TouchRestrict touchRestrict;
    TouchTestResult result;
    ResponseLinkResult responseLinkResult;

    /**
     * @tc.steps: step3. eventHub_ is nullptr, call ProcessMouseTestHit.
     * @tc.expected: expect ProcessMouseTestHit is false.
     */
    frameNode->eventHub_ = nullptr;
    EXPECT_FALSE(frameNode->ProcessMouseTestHit(globalPoint, parentLocalPoint, touchRestrict, result));

    /**
     * @tc.steps: step4. eventHub_ is gestureEventHub, call ProcessMouseTestHit.
     * @tc.expected: expect ProcessMouseTestHit is false.
     */
    auto gestureEventHub = frameNode->GetEventHub<EventHub>()->GetOrCreateGestureEventHub();
    EXPECT_FALSE(frameNode->ProcessMouseTestHit(globalPoint, parentLocalPoint, touchRestrict, result));

    /**
     * @tc.steps: step3. call ProcessMouseTestHit.
     * @tc.expected: expect ProcessMouseTestHit is false.
     */
    auto inputEventHub = frameNode->GetEventHub<EventHub>()->GetOrCreateInputEventHub();
    EXPECT_FALSE(frameNode->ProcessMouseTestHit(globalPoint, parentLocalPoint, touchRestrict, result));

    /**
     * @tc.steps: step4. call ProcessMouseTestHit.
     * @tc.expected: expect ProcessMouseTestHit is false.
     */
    touchRestrict.touchEvent.SetSourceTool(SourceTool::PEN);
    touchRestrict.touchEvent.SetType(TouchType::PROXIMITY_IN);
    EXPECT_FALSE(frameNode->ProcessMouseTestHit(globalPoint, parentLocalPoint, touchRestrict, result));
}

/**
 * @tc.name: FrameNodeGetResponseRegionListByTraversal01
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetResponseRegionListByTraversal01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);

    /**
     * @tc.steps: step2. call GetResponseRegionListByTraversal.
     * @tc.expected: expect ResponseRegion is not empty.
     */
    NG::RectF responseRect = { 10.0f, 10.0f, 10.0f, 10.0f }; // 10.0f is the x, y, width and height of rect
    std::vector<RectF> responseRegionList;
    responseRegionList.emplace_back(responseRect);
    auto context = MockPipelineContext::GetCurrentContext();
    frameNode->GetResponseRegionListByTraversal(responseRegionList, responseRect);
}

/**
 * @tc.name: OnLayoutFinish001
 * @tc.desc: Test frameNode OnLayoutFinish
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, OnLayoutFinish001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);

    /**
     * @tc.steps: step2. call OnLayoutFinish.
     * @tc.expected: expect BorderRadius radiusTopLeft is 10, OuterBorderRadius radiusTopRight is 20
     * and result return true.
     */
    auto context = AceType::MakeRefPtr<PipelineContext>();
    frameNode->context_ = AceType::RawPtr(context);
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto geometryTransition = AceType::MakeRefPtr<GeometryTransition>("active");
    layoutProperty->geometryTransition_ = geometryTransition;
    frameNode->layoutProperty_ = layoutProperty;
    frameNode->isActive_ = true;
    Dimension radius(10.0f);
    Dimension dimension(20.0f);
    BorderRadiusProperty borderRadiusProperty;
    BorderRadiusProperty outerBorderRadiusProperty;
    borderRadiusProperty.radiusTopLeft = radius;
    outerBorderRadiusProperty.radiusTopRight = dimension;
    frameNode->renderContext_->UpdateBorderRadius(borderRadiusProperty);
    frameNode->renderContext_->UpdateOuterBorderRadius(outerBorderRadiusProperty);
    bool needSyncRsNode = true;
    DirtySwapConfig config;
    auto result = frameNode->OnLayoutFinish(needSyncRsNode, config);
    frameNode->context_ = nullptr;
    EXPECT_EQ(frameNode->renderContext_->GetBorderRadius()->radiusTopLeft.value().Value(), 10.0f);
    EXPECT_EQ(frameNode->renderContext_->GetOuterBorderRadius()->radiusTopRight.value().Value(), 20.0f);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnLayoutFinish002
 * @tc.desc: Test frameNode OnLayoutFinish
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, OnLayoutFinish002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);

    /**
     * @tc.steps: step2. call OnLayoutFinish.
     * @tc.expected: expect BorderRadius radiusTopLeft is 20, OuterBorderRadius radiusTopRight is 20
     * and result return true.
     */
    auto context = AceType::MakeRefPtr<PipelineContext>();
    frameNode->context_ = AceType::RawPtr(context);
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto geometryTransition = AceType::MakeRefPtr<GeometryTransition>("active");
    layoutProperty->geometryTransition_ = geometryTransition;
    frameNode->layoutProperty_ = layoutProperty;
    frameNode->isActive_ = true;
    Dimension radius(20.0f);
    Dimension dimension(20.0f);
    BorderRadiusProperty borderRadiusProperty;
    BorderRadiusProperty outerBorderRadiusProperty;
    borderRadiusProperty.radiusTopLeft = radius;
    outerBorderRadiusProperty.radiusTopRight = dimension;
    frameNode->renderContext_->UpdateBorderRadius(borderRadiusProperty);
    frameNode->renderContext_->UpdateOuterBorderRadius(outerBorderRadiusProperty);
    bool needSyncRsNode = true;
    DirtySwapConfig config;
    auto result = frameNode->OnLayoutFinish(needSyncRsNode, config);
    frameNode->context_ = nullptr;
    EXPECT_EQ(frameNode->renderContext_->GetBorderRadius()->radiusTopLeft.value().Value(), 20.0f);
    EXPECT_EQ(frameNode->renderContext_->GetOuterBorderRadius()->radiusTopRight.value().Value(), 20.0f);
    EXPECT_FALSE(result);
}


/**
 * @tc.name: OnLayoutFinish003
 * @tc.desc: Test frameNode OnLayoutFinish
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, OnLayoutFinish003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);

    /**
     * @tc.steps: step2. isLayoutNode_ true and context true, test OnLayoutFinish.
     * @tc.expected: result return false.
     */
    bool needSyncRsNode = true;
    DirtySwapConfig config;
    frameNode->isLayoutNode_ = true;
    auto context = AceType::MakeRefPtr<PipelineContext>();
    frameNode->context_ = AceType::RawPtr(context);
    auto result = frameNode->OnLayoutFinish(needSyncRsNode, config);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step3. isLayoutNode_ true and context false, test OnLayoutFinish.
     * @tc.expected: result return false.
     */
    frameNode->context_ = nullptr;
    result = frameNode->OnLayoutFinish(needSyncRsNode, config);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step4. isLayoutNode_ false, test OnLayoutFinish.
     * @tc.expected: result return false.
     */
    frameNode->isLayoutNode_ = false;
    result = frameNode->OnLayoutFinish(needSyncRsNode, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnLayoutFinish004
 * @tc.desc: Test frameNode OnLayoutFinish
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, OnLayoutFinish004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);

    /**
     * @tc.steps: step2. isActive_ false and hasTransition false, test OnLayoutFinish.
     * @tc.expected: result return false.
     */
    bool needSyncRsNode = true;
    DirtySwapConfig config;
    frameNode->isActive_ = false;
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->geometryTransition_ = nullptr;
    frameNode->layoutProperty_ = layoutProperty;
    auto result = frameNode->OnLayoutFinish(needSyncRsNode, config);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step3. isActive_ false and hasTransition true, test OnLayoutFinish.
     * @tc.expected: result return false.
     */
    auto geometryTransition = AceType::MakeRefPtr<GeometryTransition>("active");
    layoutProperty->geometryTransition_ = geometryTransition;
    frameNode->layoutProperty_ = layoutProperty;
    result = frameNode->OnLayoutFinish(needSyncRsNode, config);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step4. isActive_ true, test OnLayoutFinish.
     * @tc.expected: result return false.
     */
    frameNode->isActive_ = true;
    result = frameNode->OnLayoutFinish(needSyncRsNode, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnLayoutFinish005
 * @tc.desc: Test frameNode OnLayoutFinish
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, OnLayoutFinish005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);

    /**
     * @tc.steps: step2. needSkipSyncGeometryNode_ true and geometryTransition null, test OnLayoutFinish.
     * @tc.expected: result return false.
     */
    bool needSyncRsNode = true;
    DirtySwapConfig config;
    frameNode->isActive_ = true;
    frameNode->needSkipSyncGeometryNode_ = true;
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->geometryTransition_ = nullptr;
    frameNode->layoutProperty_ = layoutProperty;
    auto result = frameNode->OnLayoutFinish(needSyncRsNode, config);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step3. needSkipSyncGeometryNode_ true and geometryTransition valid,, test OnLayoutFinish.
     * @tc.expected: result return false.
     */
    auto geometryTransition = AceType::MakeRefPtr<GeometryTransition>("active");
    layoutProperty->geometryTransition_ = geometryTransition;
    frameNode->layoutProperty_ = layoutProperty;
    result = frameNode->OnLayoutFinish(needSyncRsNode, config);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step4. needSkipSyncGeometryNode_ false, test OnLayoutFinish.
     * @tc.expected: result return false.
     */
    frameNode->needSkipSyncGeometryNode_ = false;
    result = frameNode->OnLayoutFinish(needSyncRsNode, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnLayoutFinish006
 * @tc.desc: Test frameNode OnLayoutFinish
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, OnLayoutFinish006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);

    /**
     * @tc.steps: step2. oldGeometryNode_ valid, test OnLayoutFinish.
     * @tc.expected: result return false.
     */
    bool needSyncRsNode = true;
    DirtySwapConfig config;
    frameNode->isActive_ = true;
    frameNode->needSkipSyncGeometryNode_ = false;
    frameNode->oldGeometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    auto result = frameNode->OnLayoutFinish(needSyncRsNode, config);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step3. oldGeometryNode_ null, test OnLayoutFinish.
     * @tc.expected: result return false.
     */
    frameNode->oldGeometryNode_ = nullptr;
    result = frameNode->OnLayoutFinish(needSyncRsNode, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnLayoutFinish007
 * @tc.desc: Test frameNode OnLayoutFinish
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, OnLayoutFinish007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);

    /**
     * @tc.steps: step2. tag equals V2::PAGE_ETS_TAG, test OnLayoutFinish.
     * @tc.expected: result return false.
     */
    bool needSyncRsNode = true;
    DirtySwapConfig config;
    frameNode->isActive_ = true;
    frameNode->needSkipSyncGeometryNode_ = false;
    auto result = frameNode->OnLayoutFinish(needSyncRsNode, config);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step3. tag not equals V2::PAGE_ETS_TAG, test OnLayoutFinish.
     * @tc.expected: result return false.
     */
    frameNode->tag_ = "frameNode";
    result = frameNode->OnLayoutFinish(needSyncRsNode, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnLayoutFinish008
 * @tc.desc: Test frameNode OnLayoutFinish
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, OnLayoutFinish008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);

    /**
     * @tc.steps: step2. config.skipMeasure false and config.skipLayout false, test OnLayoutFinish.
     * @tc.expected: result return true.
     */
    bool needSyncRsNode = true;
    DirtySwapConfig config;
    frameNode->isActive_ = true;
    frameNode->needSkipSyncGeometryNode_ = false;
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(nullptr);
    frameNode->layoutAlgorithm_ = layoutAlgorithmWrapper;
    layoutAlgorithmWrapper->skipMeasure_ = false;
    layoutAlgorithmWrapper->skipLayout_ = false;
    auto result = frameNode->OnLayoutFinish(needSyncRsNode, config);
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step3. config.skipMeasure false and config.skipLayout true, test OnLayoutFinish.
     * @tc.expected: result return true.
     */
    layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(nullptr);
    frameNode->layoutAlgorithm_ = layoutAlgorithmWrapper;
    layoutAlgorithmWrapper->skipMeasure_ = false;
    layoutAlgorithmWrapper->skipLayout_ = true;
    result = frameNode->OnLayoutFinish(needSyncRsNode, config);
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step4. config.skipMeasure true, test OnLayoutFinish.
     * @tc.expected: result return true.
     */
    layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(nullptr);
    frameNode->layoutAlgorithm_ = layoutAlgorithmWrapper;
    layoutAlgorithmWrapper->skipMeasure_ = true;
    layoutAlgorithmWrapper->skipLayout_ = true;
    result = frameNode->OnLayoutFinish(needSyncRsNode, config);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: OnLayoutFinish009
 * @tc.desc: Test frameNode OnLayoutFinish
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, OnLayoutFinish009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set API20.
     */
    int originApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWENTY);

    /**
     * @tc.steps: step2. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);

    /**
     * @tc.steps: step3. API20, test OnLayoutFinish.
     * @tc.expected: result return true.
     */
    bool needSyncRsNode = true;
    DirtySwapConfig config;
    frameNode->isActive_ = true;
    frameNode->needSkipSyncGeometryNode_ = false;
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(nullptr);
    frameNode->layoutAlgorithm_ = layoutAlgorithmWrapper;
    auto result = frameNode->OnLayoutFinish(needSyncRsNode, config);
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step4. revert to the origin API.
     */
    AceApplicationInfo::GetInstance().SetApiTargetVersion(originApiVersion);
}

/**
 * @tc.name: OnLayoutFinish010
 * @tc.desc: Test frameNode OnLayoutFinish
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, OnLayoutFinish010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set API19.
     */
    int originApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_NINETEEN);

    /**
     * @tc.steps: step2. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);

    /**
     * @tc.steps: step3. API19, test OnLayoutFinish.
     * @tc.expected: result return true.
     */
    bool needSyncRsNode = true;
    DirtySwapConfig config;
    frameNode->isActive_ = true;
    frameNode->needSkipSyncGeometryNode_ = false;
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(nullptr);
    frameNode->layoutAlgorithm_ = layoutAlgorithmWrapper;
    auto result = frameNode->OnLayoutFinish(needSyncRsNode, config);
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step4. revert to the origin API.
     */
    AceApplicationInfo::GetInstance().SetApiTargetVersion(originApiVersion);
}

/**
 * @tc.name: OnLayoutFinish011
 * @tc.desc: Test frameNode OnLayoutFinish
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, OnLayoutFinish011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set API20.
     */
    int originApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWENTY);

    /**
     * @tc.steps: step2. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);

    /**
     * @tc.steps: step3. needRerender true, test OnLayoutFinish.
     * @tc.expected: result return true.
     */
    bool needSyncRsNode = true;
    DirtySwapConfig config;
    frameNode->isActive_ = true;
    frameNode->needSkipSyncGeometryNode_ = false;
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(nullptr);
    frameNode->layoutAlgorithm_ = layoutAlgorithmWrapper;
    auto extensionHandler = AceType::MakeRefPtr<ExtensionHandler>();
    frameNode->extensionHandler_ = extensionHandler;
    extensionHandler->needRender_ = true;
    auto result = frameNode->OnLayoutFinish(needSyncRsNode, config);
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step4. revert to the origin API.
     */
    AceApplicationInfo::GetInstance().SetApiTargetVersion(originApiVersion);
}

/**
 * @tc.name: OnLayoutFinish012
 * @tc.desc: Test frameNode OnLayoutFinish
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, OnLayoutFinish012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set API20.
     */
    int originApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWENTY);

    /**
     * @tc.steps: step2. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);

    /**
     * @tc.steps: step3. needRerender false, drawModifier valid and not skipMeasure, test OnLayoutFinish.
     * @tc.expected: result return true.
     */
    bool needSyncRsNode = true;
    DirtySwapConfig config;
    frameNode->isActive_ = true;
    frameNode->needSkipSyncGeometryNode_ = false;
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(nullptr);
    frameNode->layoutAlgorithm_ = layoutAlgorithmWrapper;
    auto extensionHandler = AceType::MakeRefPtr<ExtensionHandler>();
    frameNode->extensionHandler_ = extensionHandler;
    extensionHandler->needRender_ = false;
    auto drawModifier = AceType::MakeRefPtr<DrawModifier>();
    extensionHandler->drawModifier_ = drawModifier;
    layoutAlgorithmWrapper->skipMeasure_ = false;
    auto result = frameNode->OnLayoutFinish(needSyncRsNode, config);
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step4. needRerender false, drawModifier valid and skipMeasure, test OnLayoutFinish.
     * @tc.expected: result return true.
     */
    layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(nullptr);
    frameNode->layoutAlgorithm_ = layoutAlgorithmWrapper;
    layoutAlgorithmWrapper->skipMeasure_ = true;
    PropertyChangeFlag propertyChangeFlag = PROPERTY_UPDATE_NORMAL;
    frameNode->paintProperty_->propertyChangeFlag_ = propertyChangeFlag;
    result = frameNode->OnLayoutFinish(needSyncRsNode, config);
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step5. revert to the origin API.
     */
    AceApplicationInfo::GetInstance().SetApiTargetVersion(originApiVersion);
}

/**
 * @tc.name: OnLayoutFinish013
 * @tc.desc: Test frameNode OnLayoutFinish
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, OnLayoutFinish013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set API20.
     */
    int originApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWENTY);

    /**
     * @tc.steps: step2. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode->pattern_, nullptr);

    /**
     * @tc.steps: step3. needRerender false and CheckNeedRender true, test OnLayoutFinish.
     * @tc.expected: result return true.
     */
    bool needSyncRsNode = true;
    DirtySwapConfig config;
    frameNode->isActive_ = true;
    frameNode->needSkipSyncGeometryNode_ = false;
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(nullptr);
    frameNode->layoutAlgorithm_ = layoutAlgorithmWrapper;
    auto extensionHandler = AceType::MakeRefPtr<ExtensionHandler>();
    frameNode->extensionHandler_ = extensionHandler;
    extensionHandler->needRender_ = false;
    PropertyChangeFlag propertyChangeFlag = PROPERTY_UPDATE_RENDER;
    frameNode->paintProperty_->propertyChangeFlag_ = propertyChangeFlag;
    auto result = frameNode->OnLayoutFinish(needSyncRsNode, config);
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step4. needRerender false and CheckNeedRender false, test OnLayoutFinish.
     * @tc.expected: result return true.
     */
    layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(nullptr);
    frameNode->layoutAlgorithm_ = layoutAlgorithmWrapper;
    propertyChangeFlag = PROPERTY_UPDATE_NORMAL;
    frameNode->paintProperty_->propertyChangeFlag_ = propertyChangeFlag;
    result = frameNode->OnLayoutFinish(needSyncRsNode, config);
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step5. revert to the origin API.
     */
    AceApplicationInfo::GetInstance().SetApiTargetVersion(originApiVersion);
}
} // namespace OHOS::Ace::NG
