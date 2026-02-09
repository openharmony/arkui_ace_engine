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

#include "test/unittest/core/pattern/custom/custom_test_ng.h"

namespace OHOS::Ace::NG {

/**
 * @tc.name: CustomTest032
 * @tc.desc: MeasureLayoutParam Update.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MeasureLayoutParam.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    RefPtr<GeometryNode> childGeometryOne = AceType::MakeRefPtr<GeometryNode>();
    auto childNodeOne = FrameNode::CreateFrameNode("childNodeOne", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto childWrapperOne =
        AceType::MakeRefPtr<LayoutWrapperNode>(childNodeOne, childGeometryOne, childNodeOne->GetLayoutProperty());
    layoutWrapper->AppendChild(childWrapperOne);
    MeasureLayoutParam layoutParam(AceType::RawPtr(layoutWrapper));
    ASSERT_NE(layoutParam.GetOrCreateChildByIndex(0), nullptr);

    /**
     * @tc.steps: step2. Create new layoutwrapper.
     */
    RefPtr<GeometryNode> testGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto testNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto testWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(testNode, testGeometryNode, testNode->GetLayoutProperty());
    RefPtr<GeometryNode> testGeometryOne = AceType::MakeRefPtr<GeometryNode>();
    auto testNodeOne = FrameNode::CreateFrameNode("testNodeOne", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto testWrapperOne =
        AceType::MakeRefPtr<LayoutWrapperNode>(testNodeOne, testGeometryOne, testNodeOne->GetLayoutProperty());
    RefPtr<GeometryNode> testGeometryTwo = AceType::MakeRefPtr<GeometryNode>();
    auto testNodeTwo = FrameNode::CreateFrameNode("testNodeTwo", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto testWrapperTwo =
        AceType::MakeRefPtr<LayoutWrapperNode>(testNodeTwo, testGeometryTwo, testNodeTwo->GetLayoutProperty());
    testWrapper->AppendChild(testWrapperOne);
    testWrapper->AppendChild(testWrapperTwo);

    /**
     * @tc.steps: step3. call the function Update.
     */
    layoutParam.Update(AceType::RawPtr(testWrapper));
    ASSERT_NE(layoutParam.GetOrCreateChildByIndex(0), nullptr);
}

/**
 * @tc.name: CustomTest033
 * @tc.desc: MeasureLayoutParam Update.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MeasureLayoutParam.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    RefPtr<GeometryNode> childGeometryOne = AceType::MakeRefPtr<GeometryNode>();
    auto childNodeOne = FrameNode::CreateFrameNode("childNodeOne", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto childWrapperOne =
        AceType::MakeRefPtr<LayoutWrapperNode>(childNodeOne, childGeometryOne, childNodeOne->GetLayoutProperty());
    RefPtr<GeometryNode> childGeometryTwo = AceType::MakeRefPtr<GeometryNode>();
    auto childNodeTwo = FrameNode::CreateFrameNode("childNodeTwo", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto childWrapperTwo =
        AceType::MakeRefPtr<LayoutWrapperNode>(childNodeTwo, childGeometryTwo, childNodeTwo->GetLayoutProperty());
    layoutWrapper->AppendChild(childWrapperOne);
    layoutWrapper->AppendChild(childWrapperTwo);
    MeasureLayoutParam layoutParam(AceType::RawPtr(layoutWrapper));
    ASSERT_NE(layoutParam.GetOrCreateChildByIndex(0), nullptr);

    /**
     * @tc.steps: step2. Create new layoutwrapper.
     */
    RefPtr<GeometryNode> testGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto testNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto testWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(testNode, testGeometryNode, testNode->GetLayoutProperty());
    RefPtr<GeometryNode> testGeometryOne = AceType::MakeRefPtr<GeometryNode>();
    auto testNodeOne = FrameNode::CreateFrameNode("testNodeOne", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto testWrapperOne =
        AceType::MakeRefPtr<LayoutWrapperNode>(testNodeOne, testGeometryOne, testNodeOne->GetLayoutProperty());
    testWrapper->AppendChild(testWrapperOne);

    /**
     * @tc.steps: step3. call the function Update.
     */
    layoutParam.Update(AceType::RawPtr(testWrapper));
    ASSERT_NE(layoutParam.GetOrCreateChildByIndex(0), nullptr);
}

/**
 * @tc.name: CustomTest034
 * @tc.desc: CustomNodeBase.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create customNode.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);

    /**
     * @tc.steps: step2. call the function FireRecycleRenderFunc.
     */
    bool appearFuncFlag = true;
    auto appearFunc = [&appearFuncFlag]() { appearFuncFlag = !appearFuncFlag; };
    customNode->SetAppearFunction(std::move(appearFunc));
    bool didBuildFuncFlag = true;
    auto didBuildFunc = [&didBuildFuncFlag]() { didBuildFuncFlag = !didBuildFuncFlag; };
    customNode->SetDidBuildFunction(std::move(didBuildFunc));
    bool recycleRenderFuncFlag = true;
    auto recycleRenderFunc = [&recycleRenderFuncFlag]() { recycleRenderFuncFlag = !recycleRenderFuncFlag; };
    customNode->SetRecycleRenderFunc(std::move(recycleRenderFunc));
    customNode->FireRecycleRenderFunc();
    customNode.Reset();
    EXPECT_FALSE(appearFuncFlag);
    EXPECT_FALSE(didBuildFuncFlag);
    EXPECT_FALSE(recycleRenderFuncFlag);
}

/**
 * @tc.name: CustomTest035
 * @tc.desc: CustomNodeBase.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest035, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create customNode.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);

    /**
     * @tc.steps: step2. call the function FireRecycleRenderFunc.
     */
    bool appearFuncFlag = true;
    auto appearFunc = [&appearFuncFlag]() { appearFuncFlag = !appearFuncFlag; };
    customNode->SetAppearFunction(std::move(appearFunc));
    bool recycleRenderFuncFlag = true;
    auto recycleRenderFunc = [&recycleRenderFuncFlag]() { recycleRenderFuncFlag = !recycleRenderFuncFlag; };
    customNode->SetRecycleRenderFunc(std::move(recycleRenderFunc));
    customNode->FireRecycleRenderFunc();
    customNode.Reset();
    EXPECT_FALSE(appearFuncFlag);
    EXPECT_FALSE(recycleRenderFuncFlag);
}

/**
 * @tc.name: CustomTest036
 * @tc.desc: CustomMeasureLayoutNode::FireOnUpdateParam.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest036, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create customNode.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    CustomTitleNode titleNode(1, "title");
    titleNode.FireAppTitleCallback("abc");
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);

    /**
     * @tc.steps: step2. call the function FireOnUpdateParam.
     */
    bool updateParamFuncFlag = true;
    auto updateParamFunc = [&updateParamFuncFlag](
                               LayoutWrapper* layoutWrapper) { updateParamFuncFlag = !updateParamFuncFlag; };
    customNode->SetUpdateParamFunc(std::move(updateParamFunc));
    RefPtr<GeometryNode> testGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto testNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto testWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(testNode, testGeometryNode, testNode->GetLayoutProperty());
    EXPECT_TRUE(customNode->FireOnUpdateParam(AceType::RawPtr(testWrapper)));
}

/**
 * @tc.name: CustomTest037
 * @tc.desc: CustomNodeLayoutAlgorithm::Measure.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest037, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CustomNodeLayoutAlgorithm and frameNode.
     */
    CustomNodeLayoutAlgorithm test = CustomNodeLayoutAlgorithm(nullptr);
    auto frameNode = CreateNode(V2::TEXT_ETS_TAG);

    /**
     * @tc.steps: step2. call the function Measure.
     */
    bool measureFuncFlag = true;
    auto measureFunc = [&measureFuncFlag](LayoutWrapper* layoutWrapper) { measureFuncFlag = !measureFuncFlag; };
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);
    customNode->SetMeasureFunction(std::move(measureFunc));
    auto layoutWrapper = customNode->CreateLayoutWrapper();
    test.Measure(AceType::RawPtr(layoutWrapper));
    EXPECT_FALSE(measureFuncFlag);
}

/**
 * @tc.name: CustomTest038
 * @tc.desc: test call OnAppear timeout.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest038, TestSize.Level1)
{
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    auto renderFunction = [&](int64_t deadline, bool& isTimeout) -> RefPtr<UINode> {
        RefPtr<UINode> uiNode =
            CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId() + 1, TEST_TAG);
        isTimeout = false;
        return uiNode;
    };
    customNode->executeFireOnAppear_ = false;
    customNode->renderFunction_ = renderFunction;
    bool result = customNode->Render(1);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CustomTest039
 * @tc.desc: test call renderFunction timeout.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest039, TestSize.Level1)
{
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    auto renderFunction = [&](int64_t deadline, bool& isTimeout) -> RefPtr<UINode> {
        RefPtr<UINode> uiNode =
            CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId() + 1, TEST_TAG);
        isTimeout = true;
        return uiNode;
    };
    customNode->executeFireOnAppear_ = true;
    customNode->renderFunction_ = renderFunction;
    bool result = customNode->Render();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CustomTest040
 * @tc.desc: CustomMeasureLayoutNode::GetJsActive.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest040, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create customNode.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);

    /**
     * @tc.steps: step2. Call DoSetActiveChildRange.
     * @tc.expected: Returns the expected result.
     */
    int32_t start = 0;
    int32_t end = 0;
    int32_t cacheStart = 0;
    int32_t cacheEnd = 0;
    bool showCache = true;
    customNode->DoSetActiveChildRange(start, end, cacheStart, cacheEnd, showCache);
    EXPECT_TRUE(customNode->GetJsActive());

    showCache = false;
    customNode->DoSetActiveChildRange(start, end, cacheStart, cacheEnd, showCache);
    EXPECT_TRUE(customNode->GetJsActive());

    start = -1;
    end = -1;
    customNode->DoSetActiveChildRange(start, end, cacheStart, cacheEnd, showCache);
    EXPECT_FALSE(customNode->GetJsActive());

    start = 1;
    end = 1;
    customNode->DoSetActiveChildRange(start, end, cacheStart, cacheEnd, showCache);
    EXPECT_FALSE(customNode->GetJsActive());

    end = 0;
    customNode->DoSetActiveChildRange(start, end, cacheStart, cacheEnd, showCache);
    EXPECT_TRUE(customNode->GetJsActive());

    end = -1;
    customNode->DoSetActiveChildRange(start, end, cacheStart, cacheEnd, showCache);
    EXPECT_FALSE(customNode->GetJsActive());

    start = -1;
    end = -2;
    customNode->DoSetActiveChildRange(start, end, cacheStart, cacheEnd, showCache);
    EXPECT_TRUE(customNode->GetJsActive());
}

/**
 * @tc.name: CustomTest041
 * @tc.desc: GetFrameChildByIndex.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest041, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create customNode.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);

    /**
     * @tc.steps: step2. Set isCache is false and call GetFrameChildByIndex.
     * @tc.expected: Create successful and prevJsActive_ is false.
     */
    auto node = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    uint32_t index = 0;
    customNode->AddChild(node);
    customNode->SetJSViewActive(false);
    RefPtr<UINode> UINode = customNode->GetFrameChildByIndex(index, true, true);
    EXPECT_NE(UINode, nullptr);
    EXPECT_FALSE(customNode->GetJsActive());
}

/**
 * @tc.name: CustomTest042
 * @tc.desc: FireCustomDisappear.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest042, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create customNode.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);

    /**
     * @tc.steps: step2. Set customNode->executeFireOnAppear_ is true and call FireCustomDisappear.
     * @tc.expected: customNode->executeFireOnAppear_ is true.
     */
    customNode->executeFireOnAppear_ = true;
    customNode->FireCustomDisappear();
    EXPECT_TRUE(customNode->executeFireOnAppear_);

    /**
     * @tc.steps: step2. Set customNode->executeFireOnAppear_ is false and call FireCustomDisappear.
     * @tc.expected: customNode->executeFireOnAppear_ is true.
     */
    customNode->executeFireOnAppear_ = false;
    customNode->FireCustomDisappear();
    EXPECT_TRUE(customNode->executeFireOnAppear_);
}

/**
 * @tc.name: CustomTest043
 * @tc.desc: FireCustomCallback1
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest043, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CustomAppBarNode.
     */
    auto customAppBarNode = CustomAppBarNode::CreateCustomAppBarNode(-1, "");
    ViewStackProcessor::GetInstance()->SetCustomAppBarNode(customAppBarNode);

    /**
     * @tc.steps: step2. Set callback.
     */
    bool isExecute = false;
    std::string name1 = "qw";
    auto callback = [&isExecute, &name1](const std::string& name, const std::string& value) mutable {
        name1 = name;
        isExecute = true;
    };

    /**
     * @tc.steps: step3. Add the callback in customAppBarNode.
     */
    customAppBarNode->SetCustomCallback(std::move(callback));
    std::string event = "myEvent";
    std::string param = "myParameter";

    /**
     * @tc.steps: step4. Expect the callback is used.
     */
    customAppBarNode->FireCustomCallback(event, param);
    EXPECT_EQ(name1, "myEvent");
    EXPECT_EQ(isExecute, true);
}

/**
 * @tc.name: CustomTest044
 * @tc.desc: FireCustomCallback2
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest044, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CustomAppBarNode.
     */
    auto customAppBarNode = CustomAppBarNode::CreateCustomAppBarNode(-1, "");
    ViewStackProcessor::GetInstance()->SetCustomAppBarNode(customAppBarNode);

    /**
     * @tc.steps: step2. Set callback.
     */
    bool isExecute = false;
    std::string name1 = "qw";
    auto callback = [&isExecute, &name1](const std::string& name, const std::string& value) mutable {
        name1 = name;
        isExecute = true;
    };

    /**
     * @tc.steps: step3. Add the callback in customAppBarNode.
     */
    customAppBarNode->SetCustomCallback(std::move(callback));
    std::string event = "myEvent";
    auto value = true;

    /**
     * @tc.steps: step4. Expect the callback is used.
     */
    customAppBarNode->FireCustomCallback(event, value);
    EXPECT_EQ(name1, "myEvent");
    EXPECT_EQ(isExecute, true);
}

/**
 * @tc.name: CustomTest045
 * @tc.desc: FireCustomCallback2
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest045, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CustomAppBarNode , capturedPixelMap and callbackFired.
     */
    auto customAppBarNode =
        CustomAppBarNode::CreateCustomAppBarNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ViewStackProcessor::GetInstance()->SetCustomAppBarNode(customAppBarNode);
    bool callbackFired = false;
    RefPtr<PixelMap> capturedPixelMap = nullptr;

    /**
     * @tc.steps: step2. Set callback.
     */
    auto appIconCallback = [&callbackFired, &capturedPixelMap](const RefPtr<PixelMap>& pixelMap) mutable {
        callbackFired = true;
        capturedPixelMap = pixelMap;
    };

    /**
     * @tc.steps: step3. Add the callback in customAppBarNode.
     */
    customAppBarNode->SetAppIconCallback(std::move(appIconCallback));
    auto testPixelMap = RefPtr<PixelMap>();

    /**
     * @tc.steps: step4. Expect the callback is used.
     */
    customAppBarNode->FireAppIconCallback(testPixelMap);
    EXPECT_EQ(capturedPixelMap, nullptr);
    EXPECT_EQ(capturedPixelMap, testPixelMap);
    EXPECT_NE(customAppBarNode->appIconCallback_, nullptr);
}

/**
 * @tc.name: CustomTest046
 * @tc.desc: SetJSViewActive
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest046, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TabContent and push it to view stack processor.
     * @tc.expected: Make TabContent as CustomNode parent.
     */
    auto frameNode = CreateNode(V2::TAB_CONTENT_ITEM_ETS_TAG);

    /**
     * @tc.steps: step2. Invoke CustomNode Create function.
     * @tc.expected: Create CustomNode.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);

    /**
     * @tc.steps: step3. Expect the prevJsActive_ is changed.
     */
    customNode->prevJsActive_ = true;
    bool active = false;
    customNode->SetJSViewActive(active, false, false);
    EXPECT_FALSE(customNode->prevJsActive_);
}

/**
 * @tc.name: CustomTest047
 * @tc.desc: GetStateInspectorInfo
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest047, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TabContent and push it to view stack processor.
     * @tc.expected: Make TabContent as CustomNode parent.
     */
    auto frameNode = CreateNode(V2::TAB_CONTENT_ITEM_ETS_TAG);

    /**
     * @tc.steps: step2. Invoke CustomNode Create function.
     * @tc.expected: Create CustomNode.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);

    /**
     * @tc.steps: step3. Expect the json->GetString() is equal to result->GetString().
     */
    customNode->onDumpInspectorFunc_ = nullptr;
    std::string res = customNode->FireOnDumpInspectorFunc();
    auto result = JsonUtil::ParseJsonString(res);
    auto json = customNode->GetStateInspectorInfo();
    EXPECT_EQ(json->GetString(), result->GetString());
}

/**
 * @tc.name: CustomTest048
 * @tc.desc: SetJSViewName and GetJSViewName
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest048, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CustomNodeBase through customNode.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);

    /**
     * @tc.steps: step2. Expect the jsViewName_ is name.
     */
    std::string name = "name";
    customNode->SetJSViewName(std::move(name));
    EXPECT_EQ(customNode->jsViewName_, "name");
    
    /**
     * @tc.steps: step3. Expect the jsViewName is name.
     */
    auto jsViewName = customNode->GetJSViewName();
    EXPECT_EQ(jsViewName, "name");
}

/**
 * @tc.name: CustomTest049
 * @tc.desc: SetIsV2 and GetIsV2
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest049, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CustomNodeBase through customNode.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);

    /**
     * @tc.steps: step2. Expect the customNode->GetIsV2() is true.
     */
    EXPECT_EQ(customNode->GetIsV2(), false);
    bool isV2 = true;
    customNode->SetIsV2(isV2);
    EXPECT_EQ(customNode->isV2_, isV2);
    EXPECT_EQ(customNode->GetIsV2(), true);
}

/**
 * @tc.name: CustomTest100
 * @tc.desc: Test FindParentCustomNode method
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest100, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a regular FrameNode as root.
     * @tc.expected: Root node created successfully.
     */
    auto rootFrameNode = CreateNode(V2::TEXT_ETS_TAG);
    ASSERT_NE(rootFrameNode, nullptr);

    /**
     * @tc.steps: step2. Create first level CustomNode and mount to root.
     * @tc.expected: First level CustomNode created and mounted.
     */
    auto parentCustomNode = CustomNode::CreateCustomNode(
        ElementRegister::GetInstance()->MakeUniqueId(), "ParentCustom");
    ASSERT_NE(parentCustomNode, nullptr);
    parentCustomNode->SetJSViewName("ParentCustomNode");
    parentCustomNode->MountToParent(rootFrameNode);

    /**
     * @tc.steps: step3. Create another regular FrameNode and mount to parent CustomNode.
     * @tc.expected: Intermediate FrameNode created and mounted.
     */
    auto intermediateFrameNode = CreateNode(V2::COLUMN_ETS_TAG);
    ASSERT_NE(intermediateFrameNode, nullptr);
    intermediateFrameNode->MountToParent(parentCustomNode);

    /**
     * @tc.steps: step4. Create child CustomNode and mount to intermediate FrameNode.
     * @tc.expected: Child CustomNode created and mounted.
     */
    auto childCustomNode = CustomNode::CreateCustomNode(
        ElementRegister::GetInstance()->MakeUniqueId(), "ChildCustom");
    ASSERT_NE(childCustomNode, nullptr);
    childCustomNode->SetJSViewName("ChildCustomNode");
    childCustomNode->MountToParent(intermediateFrameNode);

    /**
     * @tc.steps: step5. Test FindParentCustomNode for child CustomNode.
     * @tc.expected: Should find parentCustomNode.
     */
    auto foundParent = childCustomNode->FindParentCustomNode();
    EXPECT_EQ(foundParent, parentCustomNode);
    EXPECT_EQ(foundParent->GetJSViewName(), "ParentCustomNode");

    /**
     * @tc.steps: step6. Test FindParentCustomNode for parent CustomNode.
     * @tc.expected: Should return nullptr since no CustomNode parent exists.
     */
    auto foundGrandParent = parentCustomNode->FindParentCustomNode();
    EXPECT_EQ(foundGrandParent, nullptr);
}

/**
 * @tc.name: CustomTest101
 * @tc.desc: Test FindParentCustomNode with nested CustomNodes
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest101, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create nested CustomNode hierarchy.
     * @tc.expected: All nodes created successfully.
     */
    auto grandParentCustomNode = CustomNode::CreateCustomNode(
        ElementRegister::GetInstance()->MakeUniqueId(), "GrandParent");
    grandParentCustomNode->SetJSViewName("GrandParentCustomNode");

    auto parentCustomNode = CustomNode::CreateCustomNode(
        ElementRegister::GetInstance()->MakeUniqueId(), "Parent");
    parentCustomNode->SetJSViewName("ParentCustomNode");
    parentCustomNode->MountToParent(grandParentCustomNode);

    auto childCustomNode = CustomNode::CreateCustomNode(
        ElementRegister::GetInstance()->MakeUniqueId(), "Child");
    childCustomNode->SetJSViewName("ChildCustomNode");
    childCustomNode->MountToParent(parentCustomNode);

    /**
     * @tc.steps: step2. Test FindParentCustomNode for deeply nested child.
     * @tc.expected: Should find immediate parent CustomNode.
     */
    auto foundParent = childCustomNode->FindParentCustomNode();
    EXPECT_EQ(foundParent, parentCustomNode);
    EXPECT_EQ(foundParent->GetJSViewName(), "ParentCustomNode");

    /**
     * @tc.steps: step3. Test FindParentCustomNode for middle level CustomNode.
     * @tc.expected: Should find grandparent CustomNode.
     */
    auto foundGrandParent = parentCustomNode->FindParentCustomNode();
    EXPECT_EQ(foundGrandParent, grandParentCustomNode);
    EXPECT_EQ(foundGrandParent->GetJSViewName(), "GrandParentCustomNode");

    /**
     * @tc.steps: step4. Test FindParentCustomNode for top level CustomNode.
     * @tc.expected: Should return nullptr.
     */
    auto foundGreatGrandParent = grandParentCustomNode->FindParentCustomNode();
    EXPECT_EQ(foundGreatGrandParent, nullptr);
}

/**
 * @tc.name: CustomTest102
 * @tc.desc: Test FindParentCustomNode with no parent CustomNode
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest102, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a standalone CustomNode.
     * @tc.expected: CustomNode created successfully.
     */
    auto standaloneCustomNode = CustomNode::CreateCustomNode(
        ElementRegister::GetInstance()->MakeUniqueId(), "Standalone");
    standaloneCustomNode->SetJSViewName("StandaloneCustomNode");

    /**
     * @tc.steps: step2. Test FindParentCustomNode for standalone CustomNode.
     * @tc.expected: Should return nullptr.
     */
    auto foundParent = standaloneCustomNode->FindParentCustomNode();
    EXPECT_EQ(foundParent, nullptr);

    /**
     * @tc.steps: step3. Create regular FrameNode hierarchy and mount CustomNode.
     * @tc.expected: CustomNode mounted to regular FrameNode hierarchy.
     */
    auto rootFrame = CreateNode(V2::TEXT_ETS_TAG);
    auto columnFrame = CreateNode(V2::COLUMN_ETS_TAG);
    columnFrame->MountToParent(rootFrame);

    auto customNodeInRegularHierarchy = CustomNode::CreateCustomNode(
        ElementRegister::GetInstance()->MakeUniqueId(), "InRegular");
    customNodeInRegularHierarchy->SetJSViewName("CustomInRegularHierarchy");
    customNodeInRegularHierarchy->MountToParent(columnFrame);

    /**
     * @tc.steps: step4. Test FindParentCustomNode for CustomNode in regular hierarchy.
     * @tc.expected: Should return nullptr as no parent CustomNode exists.
     */
    auto foundParentInRegular = customNodeInRegularHierarchy->FindParentCustomNode();
    EXPECT_EQ(foundParentInRegular, nullptr);
}

/**
 * @tc.name: CustomTest103
 * @tc.desc: Test colorMode when reuse
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest103, TestSize.Level1)
{
    MockContainer::SetUp();
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_FALSE(customNode->isDarkMode_);

    g_isConfigChangePerform = true;
    MockContainer::SetMockColorMode(ColorMode::DARK);
    auto childNode = FrameNode::CreateFrameNode("childNode", 1000, AceType::MakeRefPtr<Pattern>());
    customNode->AddChild(childNode);
    customNode->FireRecycleRenderFunc();
    EXPECT_TRUE(childNode->isDarkMode_);
}

HWTEST_F(CustomTestNg, CustomTest104, TestSize.Level1)
{
    /**
     * @tc.name: CustomTest104
     * @tc.desc: Verify ACE_UINODE_TRACE is called when creating CustomNode.
     * @tc.type: FUNC
     */
    constexpr int32_t TEST_NODE_ID = 12345;

    /**
     * @tc.steps1: Create CustomNode with specific ID.
     * @tc.expected: CustomNode created successfully.
     */
    ResetLastTraceId();
    auto customNode = CustomNode::CreateCustomNode(TEST_NODE_ID, TEST_TAG);
    ASSERT_NE(customNode, nullptr);
    EXPECT_EQ(customNode->GetId(), TEST_NODE_ID);

    /**
     * @tc.steps2: Trigger ACE_UINODE_TRACE by accessing the node.
     * @tc.expected: Global trace ID is updated.
     */
    // The ACE_UINODE_TRACE macro is called when certain operations are performed
    // Verify that the trace system records the correct node ID
    uint64_t lastTraceId = GetLastTraceId();

    /**
     * @tc.steps3: Verify the trace type corresponds to UINode trace.
     * @tc.expected: Trace type matches ResTraceType::UINode.
     */
    // ResTraceType::UINode = 0 (based on enum in ace_trace.h)
    EXPECT_EQ(TEST_NODE_ID, lastTraceId);
}

/**
 * @tc.name: CustomTest105
 * @tc.desc: Test SetTriggerLifecycleFunction and FireTriggerLifecycleFunc with valid function
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest105, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create customNode.
     * @tc.expected: CustomNode created successfully.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);

    /**
     * @tc.steps: step2. Set trigger lifecycle function that returns true.
     * @tc.expected: Function is stored successfully.
     */
    bool triggerFuncCalled = false;
    int32_t receivedEventId = -1;
    auto triggerFunc = [&triggerFuncCalled, &receivedEventId](int32_t eventId) -> bool {
        triggerFuncCalled = true;
        receivedEventId = eventId;
        return true;
    };
    customNode->SetTriggerLifecycleFunction(std::move(triggerFunc));

    /**
     * @tc.steps: step3. Fire trigger lifecycle function with ON_APPEAR event.
     * @tc.expected: Function is called with correct eventId and returns true.
     */
    triggerFuncCalled = false;
    bool result = customNode->FireTriggerLifecycleFunc(CustomNodeBase::LifeCycleEvent::ON_APPEAR);
    EXPECT_TRUE(result);
    EXPECT_TRUE(triggerFuncCalled);
    EXPECT_EQ(receivedEventId, CustomNodeBase::LifeCycleEvent::ON_APPEAR);

    /**
     * @tc.steps: step4. Fire trigger lifecycle function with ON_BUILD event.
     * @tc.expected: Function is called with correct eventId and returns true.
     */
    triggerFuncCalled = false;
    result = customNode->FireTriggerLifecycleFunc(CustomNodeBase::LifeCycleEvent::ON_BUILD);
    EXPECT_TRUE(result);
    EXPECT_TRUE(triggerFuncCalled);
    EXPECT_EQ(receivedEventId, CustomNodeBase::LifeCycleEvent::ON_BUILD);
}

/**
 * @tc.name: CustomTest106
 * @tc.desc: Test FireTriggerLifecycleFunc when function returns false
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest106, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create customNode.
     * @tc.expected: CustomNode created successfully.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);

    /**
     * @tc.steps: step2. Set trigger lifecycle function that returns false.
     * @tc.expected: Function is stored successfully.
     */
    bool triggerFuncCalled = false;
    auto triggerFunc = [&triggerFuncCalled](int32_t eventId) -> bool {
        triggerFuncCalled = true;
        return false;
    };
    customNode->SetTriggerLifecycleFunction(std::move(triggerFunc));

    /**
     * @tc.steps: step3. Fire trigger lifecycle function.
     * @tc.expected: Function is called and returns false.
     */
    bool result = customNode->FireTriggerLifecycleFunc(CustomNodeBase::LifeCycleEvent::ON_APPEAR);
    EXPECT_FALSE(result);
    EXPECT_TRUE(triggerFuncCalled);
}

/**
 * @tc.name: CustomTest107
 * @tc.desc: Test FireTriggerLifecycleFunc when no function is set
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest107, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create customNode without setting trigger lifecycle function.
     * @tc.expected: CustomNode created successfully.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);

    /**
     * @tc.steps: step2. Fire trigger lifecycle function without setting it first.
     * @tc.expected: Should return false when function is not set.
     */
    bool result = customNode->FireTriggerLifecycleFunc(CustomNodeBase::LifeCycleEvent::ON_APPEAR);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step3. Fire with different lifecycle events.
     * @tc.expected: All return false when function is not set.
     */
    EXPECT_FALSE(customNode->FireTriggerLifecycleFunc(CustomNodeBase::LifeCycleEvent::ON_BUILD));
    EXPECT_FALSE(customNode->FireTriggerLifecycleFunc(CustomNodeBase::LifeCycleEvent::ON_RECYCLE));
    EXPECT_FALSE(customNode->FireTriggerLifecycleFunc(CustomNodeBase::LifeCycleEvent::ON_REUSE));
    EXPECT_FALSE(customNode->FireTriggerLifecycleFunc(CustomNodeBase::LifeCycleEvent::ON_DISAPPEAR));
}

/**
 * @tc.name: CustomTest108
 * @tc.desc: Test FireTriggerLifecycleFunc with all lifecycle events
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest108, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create customNode and set trigger lifecycle function.
     * @tc.expected: CustomNode created and function set successfully.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);

    std::vector<int32_t> receivedEvents;
    auto triggerFunc = [&receivedEvents](int32_t eventId) -> bool {
        receivedEvents.push_back(eventId);
        return true;
    };
    customNode->SetTriggerLifecycleFunction(std::move(triggerFunc));

    /**
     * @tc.steps: step2. Fire all lifecycle events.
     * @tc.expected: All events are received correctly.
     */
    customNode->FireTriggerLifecycleFunc(CustomNodeBase::LifeCycleEvent::ON_APPEAR);
    customNode->FireTriggerLifecycleFunc(CustomNodeBase::LifeCycleEvent::ON_BUILD);
    customNode->FireTriggerLifecycleFunc(CustomNodeBase::LifeCycleEvent::ON_RECYCLE);
    customNode->FireTriggerLifecycleFunc(CustomNodeBase::LifeCycleEvent::ON_REUSE);
    customNode->FireTriggerLifecycleFunc(CustomNodeBase::LifeCycleEvent::ON_DISAPPEAR);

    /**
     * @tc.steps: step3. Verify all events were received in correct order.
     * @tc.expected: All 5 events are received.
     */
    EXPECT_EQ(receivedEvents.size(), 5);
    EXPECT_EQ(receivedEvents[0], CustomNodeBase::LifeCycleEvent::ON_APPEAR);
    EXPECT_EQ(receivedEvents[1], CustomNodeBase::LifeCycleEvent::ON_BUILD);
    EXPECT_EQ(receivedEvents[2], CustomNodeBase::LifeCycleEvent::ON_RECYCLE);
    EXPECT_EQ(receivedEvents[3], CustomNodeBase::LifeCycleEvent::ON_REUSE);
    EXPECT_EQ(receivedEvents[4], CustomNodeBase::LifeCycleEvent::ON_DISAPPEAR);
}

/**
 * @tc.name: CustomTest109
 * @tc.desc: Test isDidBuild method
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest109, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create customNode.
     * @tc.expected: CustomNode created successfully and isDidBuild is false initially.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);
    EXPECT_FALSE(customNode->isDidBuild());

    /**
     * @tc.steps: step2. Set render function and build the node.
     * @tc.expected: Node builds successfully.
     */
    auto renderFunction = [&](int64_t deadline, bool& isTimeout) -> RefPtr<UINode> {
        RefPtr<UINode> uiNode =
            CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId() + 1, TEST_TAG);
        isTimeout = false;
        return uiNode;
    };
    customNode->executeFireOnAppear_ = true;
    customNode->renderFunction_ = renderFunction;

    /**
     * @tc.steps: step3. Call Build method.
     * @tc.expected: isDidBuild should be true after build.
     */
    customNode->Build(nullptr);
    EXPECT_TRUE(customNode->isDidBuild());
}

/**
 * @tc.name: CustomTest110
 * @tc.desc: Test isDidBuild when render is not called
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest110, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create customNode.
     * @tc.expected: CustomNode created successfully.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);

    /**
     * @tc.steps: step2. Check isDidBuild without calling render.
     * @tc.expected: isDidBuild should be false initially.
     */
    EXPECT_FALSE(customNode->isDidBuild());

    /**
     * @tc.steps: step3. Check isDidBuild after setting render function but not building.
     * @tc.expected: isDidBuild should still be false.
     */
    auto renderFunction = [&](int64_t deadline, bool& isTimeout) -> RefPtr<UINode> {
        RefPtr<UINode> uiNode =
            CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId() + 1, TEST_TAG);
        isTimeout = false;
        return uiNode;
    };
    customNode->renderFunction_ = renderFunction;
    EXPECT_FALSE(customNode->isDidBuild());
}

/**
 * @tc.name: CustomTest111
 * @tc.desc: Test HasRenderFunction method
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest111, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create customNode without render function.
     * @tc.expected: CustomNode created successfully and HasRenderFunction returns false.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);
    EXPECT_FALSE(customNode->HasRenderFunction());

    /**
     * @tc.steps: step2. Set render function.
     * @tc.expected: Render function is set successfully.
     */
    auto renderFunction = [&](int64_t deadline, bool& isTimeout) -> RefPtr<UINode> {
        RefPtr<UINode> uiNode =
            CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId() + 1, TEST_TAG);
        isTimeout = false;
        return uiNode;
    };
    customNode->renderFunction_ = renderFunction;

    /**
     * @tc.steps: step3. Check HasRenderFunction after setting.
     * @tc.expected: HasRenderFunction should return true.
     */
    EXPECT_TRUE(customNode->HasRenderFunction());
}

/**
 * @tc.name: CustomTest112
 * @tc.desc: Test HasRenderFunction when render function is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest112, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create customNode.
     * @tc.expected: CustomNode created successfully.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);

    /**
     * @tc.steps: step2. Set render function to nullptr explicitly.
     * @tc.expected: HasRenderFunction should return false.
     */
    customNode->renderFunction_ = nullptr;
    EXPECT_FALSE(customNode->HasRenderFunction());

    /**
     * @tc.steps: step3. Set render function and then set to nullptr again.
     * @tc.expected: HasRenderFunction returns false after setting to nullptr.
     */
    auto renderFunction = [&](int64_t deadline, bool& isTimeout) -> RefPtr<UINode> {
        RefPtr<UINode> uiNode =
            CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId() + 1, TEST_TAG);
        isTimeout = false;
        return uiNode;
    };
    customNode->renderFunction_ = renderFunction;
    EXPECT_TRUE(customNode->HasRenderFunction());

    customNode->renderFunction_ = nullptr;
    EXPECT_FALSE(customNode->HasRenderFunction());
}

/**
 * @tc.name: CustomTest113
 * @tc.desc: Test NodeDidBuild method
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest113, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create customNode.
     * @tc.expected: CustomNode created successfully.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);

    /**
     * @tc.steps: step2. Set trigger lifecycle function and did build function.
     * @tc.expected: Functions are set successfully.
     */
    bool triggerLifecycleCalled = false;
    int32_t receivedEventId = -1;
    auto triggerFunc = [&triggerLifecycleCalled, &receivedEventId](int32_t eventId) -> bool {
        triggerLifecycleCalled = true;
        receivedEventId = eventId;
        return true;
    };
    customNode->SetTriggerLifecycleFunction(std::move(triggerFunc));

    bool didBuildCalled = false;
    auto didBuildFunc = [&didBuildCalled]() { didBuildCalled = true; };
    customNode->SetDidBuildFunction(std::move(didBuildFunc));

    /**
     * @tc.steps: step3. Call NodeDidBuild.
     * @tc.expected: Both trigger lifecycle with ON_BUILD and did build functions are called.
     */
    customNode->NodeDidBuild();
    EXPECT_TRUE(triggerLifecycleCalled);
    EXPECT_EQ(receivedEventId, CustomNodeBase::LifeCycleEvent::ON_BUILD);
    EXPECT_TRUE(didBuildCalled);
    EXPECT_TRUE(customNode->isDidBuild());
}

/**
 * @tc.name: CustomTest114
 * @tc.desc: Test NodeDidBuild when trigger lifecycle function returns false
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest114, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create customNode.
     * @tc.expected: CustomNode created successfully.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);

    /**
     * @tc.steps: step2. Set trigger lifecycle function that returns false and did build function.
     * @tc.expected: Functions are set successfully.
     */
    bool triggerLifecycleCalled = false;
    auto triggerFunc = [&triggerLifecycleCalled](int32_t eventId) -> bool {
        triggerLifecycleCalled = true;
        return false;
    };
    customNode->SetTriggerLifecycleFunction(std::move(triggerFunc));

    bool didBuildCalled = false;
    auto didBuildFunc = [&didBuildCalled]() { didBuildCalled = true; };
    customNode->SetDidBuildFunction(std::move(didBuildFunc));

    /**
     * @tc.steps: step3. Call NodeDidBuild.
     * @tc.expected: Both functions are called and isDidBuild is set to true.
     */
    customNode->NodeDidBuild();
    EXPECT_TRUE(triggerLifecycleCalled);
    EXPECT_TRUE(didBuildCalled);
    EXPECT_TRUE(customNode->isDidBuild());
}

/**
 * @tc.name: CustomTest115
 * @tc.desc: Test NodeDidBuild when no functions are set
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest115, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create customNode without setting any lifecycle functions.
     * @tc.expected: CustomNode created successfully.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);

    /**
     * @tc.steps: step2. Check isDidBuild before calling NodeDidBuild.
     * @tc.expected: isDidBuild should be false initially.
     */
    EXPECT_FALSE(customNode->isDidBuild());

    /**
     * @tc.steps: step3. Call NodeDidBuild without setting any functions.
     * @tc.expected: isDidBuild should be set to true even without functions.
     */
    customNode->NodeDidBuild();
    EXPECT_TRUE(customNode->isDidBuild());
}

/**
 * @tc.name: CustomTest116
 * @tc.desc: Test complete lifecycle flow with all new APIs
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest116, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create customNode and setup all lifecycle functions.
     * @tc.expected: CustomNode created and all functions set successfully.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);

    // Set render function
    auto renderFunction = [&](int64_t deadline, bool& isTimeout) -> RefPtr<UINode> {
        RefPtr<UINode> uiNode =
            CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId() + 1, TEST_TAG);
        isTimeout = false;
        return uiNode;
    };
    customNode->renderFunction_ = renderFunction;

    // Setup lifecycle tracking
    std::vector<int32_t> lifecycleEvents;
    auto triggerFunc = [&lifecycleEvents](int32_t eventId) -> bool {
        lifecycleEvents.push_back(eventId);
        return true;
    };
    customNode->SetTriggerLifecycleFunction(std::move(triggerFunc));

    /**
     * @tc.steps: step2. Check initial state.
     * @tc.expected: HasRenderFunction true, isDidBuild false.
     */
    EXPECT_TRUE(customNode->HasRenderFunction());
    EXPECT_FALSE(customNode->isDidBuild());

    /**
     * @tc.steps: step3. Call NodeDidBuild.
     * @tc.expected: ON_BUILD event fired and isDidBuild set to true.
     */
    customNode->NodeDidBuild();
    EXPECT_EQ(lifecycleEvents.size(), 1);
    EXPECT_EQ(lifecycleEvents[0], CustomNodeBase::LifeCycleEvent::ON_BUILD);
    EXPECT_TRUE(customNode->isDidBuild());

    /**
     * @tc.steps: step4. Fire additional lifecycle events.
     * @tc.expected: All events are tracked correctly.
     */
    customNode->FireTriggerLifecycleFunc(CustomNodeBase::LifeCycleEvent::ON_APPEAR);
    customNode->FireTriggerLifecycleFunc(CustomNodeBase::LifeCycleEvent::ON_RECYCLE);
    customNode->FireTriggerLifecycleFunc(CustomNodeBase::LifeCycleEvent::ON_REUSE);
    customNode->FireTriggerLifecycleFunc(CustomNodeBase::LifeCycleEvent::ON_DISAPPEAR);

    /**
     * @tc.steps: step5. Verify all lifecycle events in order.
     * @tc.expected: All 5 events received in correct order.
     */
    EXPECT_EQ(lifecycleEvents.size(), 5);
    EXPECT_EQ(lifecycleEvents[0], CustomNodeBase::LifeCycleEvent::ON_BUILD);
    EXPECT_EQ(lifecycleEvents[1], CustomNodeBase::LifeCycleEvent::ON_APPEAR);
    EXPECT_EQ(lifecycleEvents[2], CustomNodeBase::LifeCycleEvent::ON_RECYCLE);
    EXPECT_EQ(lifecycleEvents[3], CustomNodeBase::LifeCycleEvent::ON_REUSE);
    EXPECT_EQ(lifecycleEvents[4], CustomNodeBase::LifeCycleEvent::ON_DISAPPEAR);
}

} // namespace OHOS::Ace::NG