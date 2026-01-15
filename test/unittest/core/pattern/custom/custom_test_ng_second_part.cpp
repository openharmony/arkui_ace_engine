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

} // namespace OHOS::Ace::NG