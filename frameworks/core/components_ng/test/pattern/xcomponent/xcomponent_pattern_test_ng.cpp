/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include <cstddef>
#include <unistd.h>

#include "gtest/gtest.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_model_ng.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string XCOMPONENT_ID = "xcomponent";
const std::string XCOMPONENT_SURFACE_TYPE = "surface";
const std::string XCOMPONENT_COMPONENT_TYPE = "component";
const std::string XCOMPONENT_LIBRARY_NAME = "native_render";
const std::string XCOMPONENT_SO_PATH = "com.example.xcomponentmultihap/entry";
const XComponentType XCOMPONENT_SURFACE_TYPE_VALUE = XComponentType::SURFACE;
const float CONTAINER_WIDTH = 300.0f;
const float CONTAINER_HEIGHT = 300.0f;
const SizeF CONTAINER_SIZE(CONTAINER_WIDTH, CONTAINER_HEIGHT);
const uint32_t XCOMPONENT_ID_LEN_MAX = 10;
const float MAX_WIDTH = 400.0f;
const float MAX_HEIGHT = 400.0f;
const SizeF MAX_SIZE(MAX_WIDTH, MAX_HEIGHT);
const float CHILD_WIDTH = 200.0f;
const float CHILD_HEIGHT = 200.0f;
const SizeF CHILD_SIZE(CHILD_WIDTH, CHILD_HEIGHT);
const float CHILD_OFFSET_WIDTH = 50.0f;
const float CHILD_OFFSET_HEIGHT = 0.0f;
} // namespace

class XComponentPropertyTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: XComponentPropertyTest001
 * @tc.desc: Create XComponent, and test XComponent type, id, libraryName, soPath interface.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPropertyTestNg, XComponentPropertyTest001, TestSize.Level1)
{
    RefPtr<XComponentController> const xComponentController;
    XComponentModelNG xComponent;
    xComponent.Create(XCOMPONENT_ID, XCOMPONENT_SURFACE_TYPE, XCOMPONENT_LIBRARY_NAME, xComponentController);
    xComponent.SetSoPath(XCOMPONENT_SO_PATH);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::XCOMPONENT_ETS_TAG);
    auto xComponentPattern = frameNode->GetPattern<XComponentPattern>();
    EXPECT_FALSE(xComponentPattern == nullptr);
    auto xComponentLayoutProperty = frameNode->GetLayoutProperty<XComponentLayoutProperty>();
    EXPECT_FALSE(xComponentLayoutProperty == nullptr);

    EXPECT_EQ(xComponentPattern->GetId(), XCOMPONENT_ID);
    EXPECT_EQ(xComponentPattern->GetLibraryName(), XCOMPONENT_LIBRARY_NAME);
    EXPECT_EQ(xComponentPattern->GetSoPath(), XCOMPONENT_SO_PATH);
    EXPECT_EQ(xComponentPattern->IsAtomicNode(), XCOMPONENT_SURFACE_TYPE == "surface");
    EXPECT_EQ(
        xComponentLayoutProperty->GetXComponentType().value_or(XComponentType::SURFACE), XCOMPONENT_SURFACE_TYPE_VALUE);
}

/**
 * @tc.name: XComponentEventTest002
 * @tc.desc: Test XComponent onLoad and onDestroy event.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPropertyTestNg, XComponentEventTest002, TestSize.Level1)
{
    RefPtr<XComponentController> const xComponentController;
    XComponentModelNG xComponent;
    xComponent.Create(XCOMPONENT_ID, XCOMPONENT_SURFACE_TYPE, XCOMPONENT_LIBRARY_NAME, xComponentController);
    xComponent.SetSoPath(XCOMPONENT_SO_PATH);

    std::string unknownId;
    std::string unknownType;
    auto onLoad = [&unknownId](const std::string& xComponentId) { unknownId = xComponentId; };
    xComponent.SetOnLoad(onLoad);
    auto onDestroy = [&unknownType]() { unknownType = XCOMPONENT_SURFACE_TYPE; };
    xComponent.SetOnDestroy(onDestroy);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::XCOMPONENT_ETS_TAG);
    auto xComponentEventHub = frameNode->GetEventHub<XComponentEventHub>();
    xComponentEventHub->FireLoadEvent(XCOMPONENT_ID);
    xComponentEventHub->FireDestroyEvent();
    EXPECT_EQ(unknownId, XCOMPONENT_ID);
    EXPECT_EQ(unknownType, XCOMPONENT_SURFACE_TYPE);
}

/**
 * @tc.name: XComponentNDKTest003
 * @tc.desc: Test XComponent NDK interfaces.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPropertyTestNg, XComponentNDKTest003, TestSize.Level1)
{
    RefPtr<XComponentController> const xComponentController;
    XComponentModelNG xComponent;
    xComponent.Create(XCOMPONENT_ID, XCOMPONENT_SURFACE_TYPE, XCOMPONENT_LIBRARY_NAME, xComponentController);
    xComponent.SetSoPath(XCOMPONENT_SO_PATH);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::XCOMPONENT_ETS_TAG);

    auto xComponentPattern = frameNode->GetPattern<XComponentPattern>();
    EXPECT_FALSE(xComponentPattern == nullptr);

    auto pair = xComponentPattern->GetNativeXComponent();
    auto* nativeXComponent = pair.second;
    auto nativeXComponentImpl = pair.first;
    EXPECT_FALSE(nativeXComponent == nullptr);
    EXPECT_FALSE(nativeXComponentImpl == nullptr);
    nativeXComponentImpl->SetXComponentId(XCOMPONENT_ID);

    uint64_t size = XCOMPONENT_ID_LEN_MAX + 1;
    char id[XCOMPONENT_ID_LEN_MAX] = {};
    nativeXComponent->GetXComponentId(id, &size);
    EXPECT_EQ(xComponentPattern->GetId(), id);
}

/**
 * @tc.name: XComponentLayoutAlgorithmTest004
 * @tc.desc: Test XComponent algorithm functions when XComponent type is surface.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPropertyTestNg, XComponentLayoutAlgorithmTest004, TestSize.Level1)
{
    RefPtr<XComponentController> const xComponentController;
    XComponentModelNG xComponent;
    xComponent.Create(XCOMPONENT_ID, XCOMPONENT_SURFACE_TYPE, XCOMPONENT_LIBRARY_NAME, xComponentController);
    xComponent.SetSoPath(XCOMPONENT_SO_PATH);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::XCOMPONENT_ETS_TAG);

    // Create LayoutWrapper and set XComponentLayoutAlgorithm.
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto xComponentLayoutProperty = frameNode->GetLayoutProperty<XComponentLayoutProperty>();
    auto xComponentPattern = frameNode->GetPattern<XComponentPattern>();
    EXPECT_FALSE(xComponentPattern == nullptr);
    auto xComponentLayoutAlgorithm = xComponentPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(xComponentLayoutAlgorithm == nullptr);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(xComponentLayoutAlgorithm));

    // Test MeasureContent.
    /**
    //     corresponding ets code:
    //         XComponent({
    //           id: 'xcomponent',
    //           type: 'surface',
    //           controller: this.xcomponentController
    //         })
    */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = MAX_SIZE;
    auto xComponentDefaultSize =
        xComponentLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper).value_or(SizeF(0.0f, 0.0f));
    EXPECT_EQ(xComponentDefaultSize, MAX_SIZE);

    /**
    //     corresponding ets code:
    //         XComponent({
    //           id: 'xcomponent',
    //           type: 'surface',
    //           controller: this.xcomponentController
    //         }).height(300).width(300)
    */
    layoutConstraint.selfIdealSize.SetSize(CONTAINER_SIZE);
    xComponentLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper);
    auto xComponentSize =
        xComponentLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper).value_or(SizeF(0.0f, 0.0f));
    EXPECT_EQ(xComponentSize, CONTAINER_SIZE);

    // Test Measure.
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    xComponentLayoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameSize(), CONTAINER_SIZE);

    // Test Layout.
    xComponentLayoutAlgorithm->Layout(&layoutWrapper);
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameOffset(), OffsetF(0.0, 0.0));
}

/**
 * @tc.name: XComponentLayoutAlgorithmTest005
 * @tc.desc: Test XComponent measure functions when XComponent type is component.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPropertyTestNg, XComponentLayoutAlgorithmTest005, TestSize.Level1)
{
    RefPtr<XComponentController> const xComponentController;
    XComponentModelNG xComponent;
    xComponent.Create(XCOMPONENT_ID, XCOMPONENT_COMPONENT_TYPE, XCOMPONENT_LIBRARY_NAME, xComponentController);
    xComponent.SetSoPath(XCOMPONENT_SO_PATH);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::XCOMPONENT_ETS_TAG);

    // Create LayoutWrapper and set XComponentLayoutAlgorithm.
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto xComponentLayoutProperty = frameNode->GetLayoutProperty<XComponentLayoutProperty>();
    auto xComponentPattern = frameNode->GetPattern<XComponentPattern>();
    EXPECT_FALSE(xComponentPattern == nullptr);
    auto xComponentLayoutAlgorithm = xComponentPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(xComponentLayoutAlgorithm == nullptr);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(xComponentLayoutAlgorithm));

    // XComponent is container component when its type is component.
    LayoutConstraintF layoutConstraint;
    layoutConstraint.selfIdealSize.SetSize(CONTAINER_SIZE);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    /**
    //     corresponding ets code:
    //         XComponent({
    //           id: 'xcomponent',
    //           type: 'surface',
    //           controller: this.xcomponentController
    //         })
    //         {
    //             Text().height(200).width(200)
    //         }.width(300).height(300)
    */
    auto childFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    childGeometryNode->Reset();
    RefPtr<LayoutWrapper> const childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(childFrameNode, childGeometryNode, childFrameNode->GetLayoutProperty());
    childLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(CHILD_WIDTH), CalcLength(CHILD_HEIGHT)));

    auto boxLayoutAlgorithm = childFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
    childLayoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));

    frameNode->AddChild(childFrameNode);
    layoutWrapper.AppendChild(childLayoutWrapper);

    auto childLayoutWrapper2 = layoutWrapper.GetOrCreateChildByIndex(0);
    xComponentLayoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameSize(), CONTAINER_SIZE);
    EXPECT_EQ(childLayoutWrapper2->GetGeometryNode()->GetFrameSize(), CHILD_SIZE);

    xComponentLayoutAlgorithm->Layout(&layoutWrapper);
    EXPECT_EQ(
        childLayoutWrapper2->GetGeometryNode()->GetFrameOffset(), OffsetF(CHILD_OFFSET_WIDTH, CHILD_OFFSET_HEIGHT));
}

} // namespace OHOS::Ace::NG
