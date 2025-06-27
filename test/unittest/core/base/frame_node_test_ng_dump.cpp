/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

/**
 * @tc.name: FrameNodeTestNgDumpPadding001
 * @tc.desc: Test DumpPadding.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNgDumpPadding001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialization frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), true);
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    auto testPadding = std::make_unique<PaddingProperty>();

    /**
     * @tc.steps: step2. Generate JSON using default PaddingProperty
     * @tc.expected: step2. get the JsonValue is "".
     */

    frameNode->DumpPadding(testPadding, "padding", json);
    EXPECT_EQ(json->GetString("padding"), "");
}

/**
 * @tc.name: FrameNodeTestNgDumpPadding002
 * @tc.desc: Test DumpPadding.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNgDumpPadding002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialization frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), true);
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    auto testPadding = std::make_unique<PaddingProperty>();

    /**
     * @tc.steps: step2. Give PaddingProperty bottom a new value.
     */
    testPadding->bottom = CalcLength(10.0f);

    /**
     * @tc.steps: step3. Execute DumpPadding.
     * @tc.expected: step3. get the JsonValue is "[NA,NA,NA,10.00px]".
     */

    frameNode->DumpPadding(testPadding, "padding1", json);
    EXPECT_EQ(json->GetString("padding1"), "[NA,NA,NA,10.00px]");

    /**
     * @tc.steps: step4. Give PaddingProperty top a new value.
     */
    testPadding->top = CalcLength(10.0f);

    /**
     * @tc.steps: step5. Execute DumpPadding.
     * @tc.expected: step5. get the JsonValue is "[NA,NA,20.00px,10.00px]".
     */

    frameNode->DumpPadding(testPadding, "padding2", json);
    EXPECT_EQ(json->GetString("padding2"), "[NA,NA,10.00px,10.00px]");

    /**
     * @tc.steps: step6. Give PaddingProperty right a new value.
     */
    testPadding->right = CalcLength(10.0f);

    /**
     * @tc.steps: step7. Execute DumpPadding.
     * @tc.expected: step7. get the JsonValue is "[NA,10.00px,10.00px,10.00px]".
     */

    frameNode->DumpPadding(testPadding, "padding3", json);
    EXPECT_EQ(json->GetString("padding3"), "[NA,10.00px,10.00px,10.00px]");

    /**
     * @tc.steps: step8. Give PaddingProperty left a new value.
     */
    testPadding->left = CalcLength(10.0f);

    /**
     * @tc.steps: step9. Execute DumpPadding.
     * @tc.expected: step9. get the JsonValue is "[10.00px,10.00px,10.00px,10.00px]".
     */

    frameNode->DumpPadding(testPadding, "padding4", json);
    EXPECT_EQ(json->GetString("padding4"), "[10.00px,10.00px,10.00px,10.00px]");
}

/**
 * @tc.name: FrameNodeTestNgDumpBorder001
 * @tc.desc: Test DumpBorder.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNgDumpBorder001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialization frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), true);
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    auto testBorder = std::make_unique<BorderWidthProperty>();

    /**
     * @tc.steps: step2. Generate JSON using default BorderWidthProperty
     * @tc.expected: step2. get the JsonValue is "".
     */

    frameNode->DumpBorder(testBorder, "border", json);
    EXPECT_EQ(json->GetString("border"), "");
}

/**
 * @tc.name: FrameNodeTestNgDumpBorder002
 * @tc.desc: Test DumpBorder.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNgDumpBorder002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialization frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), true);
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    auto testBorder = std::make_unique<BorderWidthProperty>();

    /**
     * @tc.steps: step2. Give BorderWidthProperty a new value.
     */
    testBorder->bottomDimen = Dimension(10.0f);

    /**
     * @tc.steps: step3. Execute DumpPadding.
     * @tc.expected: step3. get the JsonValue is "[NA,NA,NA,10.00px]".
     */

    frameNode->DumpBorder(testBorder, "border1", json);
    EXPECT_EQ(json->GetString("border1"), "[NA,NA,NA,10.00px]");

    /**
     * @tc.steps: step4. Give PaddingProperty a new value.
     */
    testBorder->topDimen = Dimension(10.0f);

    /**
     * @tc.steps: step5. Execute DumpPadding.
     * @tc.expected: step5. get the JsonValue is "[NA,NA,20.00px,10.00px]".
     */

    frameNode->DumpBorder(testBorder, "border2", json);
    EXPECT_EQ(json->GetString("border2"), "[NA,NA,10.00px,10.00px]");

    /**
     * @tc.steps: step6. Give PaddingProperty a new value.
     */
    testBorder->rightDimen = Dimension(10.0f);

    /**
     * @tc.steps: step7. Execute DumpPadding.
     * @tc.expected: step7. get the JsonValue is "[NA,10.00px,10.00px,10.00px]".
     */

    frameNode->DumpBorder(testBorder, "border3", json);
    EXPECT_EQ(json->GetString("border3"), "[NA,10.00px,10.00px,10.00px]");

    /**
     * @tc.steps: step8. Give PaddingProperty a new value.
     */
    testBorder->leftDimen = Dimension(10.0f);

    /**
     * @tc.steps: step9. Execute DumpPadding.
     * @tc.expected: step9. get the JsonValue is "[10.00px,10.00px,10.00px,10.00px]".
     */

    frameNode->DumpBorder(testBorder, "border4", json);
    EXPECT_EQ(json->GetString("border4"), "[10.00px,10.00px,10.00px,10.00px]");
}

/**
 * @tc.name: FrameNodeDumpSimplifySafeAreaInfo001
 * @tc.desc: Test DumpSimplifySafeAreaInfo.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeDumpSimplifySafeAreaInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is nullptr.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create json, create SafeAreaExpandOpts.
     * @tc.expected: expect is nullptr.
     */
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    SafeAreaExpandOpts opts;
    frameNode->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);

    /**
     * @tc.steps: step3.Opts have no value, test DumpSimplifySafeAreaInfo.
     * @tc.expected: json is null.
     */
    frameNode->DumpSimplifySafeAreaInfo(json);
    const auto& valueExpandOpts = json->GetValue("SafeAreaExpandOpts");
    EXPECT_TRUE(valueExpandOpts->IsNull());
    const auto& valueInsets = json->GetValue("SafeAreaInsets");
    EXPECT_TRUE(valueInsets->IsNull());
    const auto& valueSelfAdjust = json->GetValue("SelfAdjust");
    EXPECT_TRUE(valueSelfAdjust->IsNull());
    const auto& valueParentSelfAdjust = json->GetValue("ParentSelfAdjust");
    EXPECT_TRUE(valueParentSelfAdjust->IsNull());

    /**
     * @tc.steps: step4.Opts have value, test DumpSimplifySafeAreaInfo.
     * @tc.expected: JSON data has values and their values are predictable.
     */
    opts.edges = SAFE_AREA_EDGE_TOP;
    std::string optsString = "SafeAreaExpandOpts: type:SAFE_AREA_TYPE_NONE, edges: SAFE_AREA_EDGE_TOP";
    frameNode->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);
    frameNode->DumpSimplifySafeAreaInfo(json);
    EXPECT_EQ(json->GetString("SafeAreaExpandOpts"), optsString);

    json->Delete("SafeAreaExpandOpts");
    opts.type = SAFE_AREA_TYPE_SYSTEM;
    optsString = "SafeAreaExpandOpts: type:SAFE_AREA_TYPE_SYSTEM, edges: SAFE_AREA_EDGE_TOP";
    frameNode->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);
    frameNode->DumpSimplifySafeAreaInfo(json);
    EXPECT_EQ(json->GetString("SafeAreaExpandOpts"), optsString);

    SafeAreaInsets safeArea;
    optsString = "SafeAreaInsets left_";
    frameNode->GetLayoutProperty()->UpdateSafeAreaInsets(safeArea);
    frameNode->DumpSimplifySafeAreaInfo(json);
    EXPECT_EQ(json->GetString("SafeAreaInsets").find("left_"), optsString.find("left_"));
}

/**
 * @tc.name: FrameNodeDumpSimplifySafeAreaInfo002
 * @tc.desc: Test DumpSimplifySafeAreaInfo.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeDumpSimplifySafeAreaInfo002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is nullptr.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create json, create SafeAreaExpandOpts.
     * @tc.expected: expect is nullptr.
     */
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    SafeAreaExpandOpts opts;
    opts.edges = SAFE_AREA_EDGE_TOP;
    opts.type = SAFE_AREA_TYPE_SYSTEM;
    frameNode->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);
    frameNode->DumpSimplifySafeAreaInfo(json);
    const auto& valueSelfAdjust = json->GetValue("SelfAdjust");
    EXPECT_TRUE(valueSelfAdjust->IsNull());
    const auto& valueParentSelfAdjust = json->GetValue("ParentSelfAdjust");
    EXPECT_TRUE(valueParentSelfAdjust->IsNull());

    /**
     * @tc.steps: step3.SetGeometryNode, test DumpSimplifySafeAreaInfo.
     * @tc.expected: JSON data has values and their values are predictable.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetSelfAdjust(RectF(10.0f, 10.0f, 10.0f, 10.0f));
    geometryNode->SetParentAdjust(RectF(20.0f, 20.0f, 20.0f, 20.0f));
    frameNode->SetGeometryNode(geometryNode);
    frameNode->DumpSimplifySafeAreaInfo(json);
    std::string str = "RectT (10.00, 10.00) - [10.00 x 10.00]";
    EXPECT_EQ(json->GetString("SelfAdjust"), str);
    str = "RectT (20.00, 20.00) - [20.00 x 20.00]";
    EXPECT_EQ(json->GetString("ParentSelfAdjust"), str);
}

/**
 * @tc.name: FrameNodeDumpSimplifySafeAreaInfo003
 * @tc.desc: Test DumpSimplifySafeAreaInfo.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeDumpSimplifySafeAreaInfo003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is nullptr.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create json, create SafeAreaExpandOpts.
     * @tc.expected: expect is nullptr.
     */
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    frameNode->DumpSimplifySafeAreaInfo(json);
    const auto& valueKeyboardInset = json->GetValue("KeyboardInset: ");
    EXPECT_TRUE(valueKeyboardInset->IsNull());
    /**
     * @tc.steps: step3.SetGeometryNode, test DumpSimplifySafeAreaInfo.
     * @tc.expected: JSON data has values and their values are predictable.
     */
    auto manager = MockPipelineContext::GetCurrent()->GetSafeAreaManager();
    ASSERT_NE(manager, nullptr);
    SafeAreaInsets::Inset keyboardInset;
    manager->keyboardInset_ = keyboardInset;
    manager->keyboardSafeAreaEnabled_ = true;
    frameNode->DumpSimplifySafeAreaInfo(json);
    EXPECT_EQ(json->GetBool("IgnoreSafeArea"), false);
    EXPECT_EQ(json->GetBool("IsNeedAvoidWindow"), false);
    EXPECT_EQ(json->GetBool("IsFullScreen"), false);
    EXPECT_EQ(json->GetInt("IsKeyboardAvoidMode"), 0);
    EXPECT_EQ(json->GetBool("IsKeyboardAvoidMode"), false);
    std::string str = "[start: 0, end: 0]";
    EXPECT_EQ(json->GetString("KeyboardInset: "), str);
}

/**
 * @tc.name: FrameNodeDumpSimplifyOverlayInfo001
 * @tc.desc: Test DumpSimplifyOverlayInfo.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeDumpSimplifyOverlayInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is nullptr.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create json, create SafeAreaExpandOpts.
     * @tc.expected: expect is nullptr.
     */
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    frameNode->DumpSimplifyOverlayInfo(json);
    const auto& valueIsOverlayNode = json->GetValue("IsOverlayNode");
    EXPECT_TRUE(valueIsOverlayNode->IsNull());

    /**
     * @tc.steps: step3.IsOverlayNode == true, test DumpSimplifyOverlayInfo.
     * @tc.expected: JSON data has values and their values are predictable.
     */
    frameNode->GetLayoutProperty()->SetIsOverlayNode(true);
    frameNode->DumpSimplifyOverlayInfo(json);
    EXPECT_EQ(json->GetBool("IsOverlayNode"), true);
    EXPECT_EQ(json->GetString("OverlayOffset"), "0.00px,0.00px");
}

/**
 * @tc.name: FrameNodeGeometryNodeToJsonValue
 * @tc.desc: Test method GeometryNodeToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGeometryNodeToJsonValue, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is nullptr.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create json, create InspectorFilter.
     * @tc.expected: width is 0.00vp, height is 0.00vp.
     */
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    InspectorFilter filter;
    frameNode->GeometryNodeToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("width"), "0.00vp");
    EXPECT_EQ(json->GetString("height"), "0.00vp");

    /**
     * @tc.steps: step3. has CalcLayoutProperty.
     * @tc.expected: width is 0.00vp, height is 0.00vp.
     */
    MeasureProperty calc;
    frameNode->GetLayoutProperty()->UpdateCalcLayoutProperty(calc);
    json->Delete("width");
    json->Delete("height");
    frameNode->GeometryNodeToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("width"), "0.00vp");
    EXPECT_EQ(json->GetString("height"), "0.00vp");

    /**
     * @tc.steps: step3. GeometryNode has value.
     * @tc.expected: width is 10.00vp, height is 10.00vp.
     */
    frameNode->GetGeometryNode()->SetFrameSize(SizeF(10.0, 10.0));
    json->Delete("width");
    json->Delete("height");
    frameNode->GeometryNodeToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("width"), "10.00vp");
    EXPECT_EQ(json->GetString("height"), "10.00vp");
}
} // namespace OHOS::Ace::NG