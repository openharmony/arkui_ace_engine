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
} // namespace OHOS::Ace::NG