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
#include <optional>
#include <unistd.h>
#include <vector>

#include "gtest/gtest.h"

#define private public
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/render/mock_render_surface.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/common/ai/image_analyzer_mgr.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_controller_ng.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_layout_algorithm.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_model_ng.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/touch_event.h"
#include "frameworks/core/gestures/press_recognizer.h"
#include "frameworks/core/components_ng/pattern/node_container/node_container_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_ext_surface_callback_client.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
struct TestProperty {
    std::optional<std::string> xcId = std::nullopt;
    std::optional<XComponentType> xcType = std::nullopt;
    std::optional<std::string> libraryName = std::nullopt;
    std::optional<std::string> soPath = std::nullopt;
    std::optional<LoadEvent> loadEvent = std::nullopt;
    std::optional<DestroyEvent> destroyEvent = std::nullopt;
    std::optional<SurfaceCreatedEvent> surfaceCreatedEvent = std::nullopt;
    std::optional<SurfaceChangedEvent> surfaceChangedEvent = std::nullopt;
    std::optional<SurfaceDestroyedEvent> surfaceDestroyedEvent = std::nullopt;
};
namespace {
const std::string CHECK_KEY = "HI";
const std::string XCOMPONENT_ID = "xcomponent";
const std::string XCOMPONENT_LIBRARY_NAME = "native_render";
const std::string XCOMPONENT_SO_PATH = "com.example.xcomponentmultihap/entry";
const std::string SURFACE_ID = "2430951489577";
constexpr XComponentType XCOMPONENT_SURFACE_TYPE_VALUE = XComponentType::SURFACE;
constexpr XComponentType XCOMPONENT_COMPONENT_TYPE_VALUE = XComponentType::COMPONENT;
constexpr XComponentType XCOMPONENT_TEXTURE_TYPE_VALUE = XComponentType::TEXTURE;
constexpr XComponentType XCOMPONENT_NODE_TYPE_VALUE = XComponentType::NODE;
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
TestProperty testProperty;
} // namespace

class XComponentPropertyTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();

protected:
    static RefPtr<FrameNode> CreateXComponentNode(TestProperty& testProperty);
};

void XComponentPropertyTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    testProperty.xcId = XCOMPONENT_ID;
    testProperty.libraryName = XCOMPONENT_LIBRARY_NAME;
    testProperty.soPath = XCOMPONENT_SO_PATH;
}

void XComponentPropertyTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> XComponentPropertyTestNg::CreateXComponentNode(TestProperty& testProperty)
{
    auto xcId = testProperty.xcId.value();
    auto xcType = testProperty.xcType.value();
    auto libraryName = testProperty.libraryName.value();
    auto xcomponentController = std::make_shared<XComponentControllerNG>();
    XComponentModelNG().Create(xcId, xcType, libraryName, xcomponentController);

    if (testProperty.soPath.has_value()) {
        XComponentModelNG().SetSoPath(testProperty.soPath.value());
    }
    if (testProperty.loadEvent.has_value()) {
        XComponentModelNG().SetOnLoad(std::move(testProperty.loadEvent.value()));
    }
    if (testProperty.destroyEvent.has_value()) {
        XComponentModelNG().SetOnDestroy(std::move(testProperty.destroyEvent.value()));
    }
    if (testProperty.surfaceCreatedEvent.has_value()) {
        XComponentModelNG().SetControllerOnCreated(std::move(testProperty.surfaceCreatedEvent.value()));
    }
    if (testProperty.surfaceChangedEvent.has_value()) {
        XComponentModelNG().SetControllerOnChanged(std::move(testProperty.surfaceChangedEvent.value()));
    }
    if (testProperty.surfaceDestroyedEvent.has_value()) {
        XComponentModelNG().SetControllerOnDestroyed(std::move(testProperty.surfaceDestroyedEvent.value()));
    }
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish(); // pop
    return AceType::DynamicCast<FrameNode>(element);
}

/**
 * @tc.name: XComponentPropertyTest001
 * @tc.desc: Create XComponent, and test XComponent type, id, libraryName, soPath interface.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPropertyTestNg, XComponentPropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a XComponentModelNG
     */
    const std::shared_ptr<InnerXComponentController> xComponentController;
    XComponentModelNG xComponent;

    /**
     * @tc.steps: step2. call Create and SetSoPath
     *            case: type = XCOMPONENT_SURFACE_TYPE
     * @tc.expected: the properties are expected
     */
    xComponent.Create(XCOMPONENT_ID, XCOMPONENT_SURFACE_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME, xComponentController);
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
    EXPECT_TRUE(xComponentPattern->IsAtomicNode()); // if xcomponentType = "surface"
    EXPECT_EQ(
        xComponentLayoutProperty->GetXComponentType().value_or(XComponentType::SURFACE), XCOMPONENT_SURFACE_TYPE_VALUE);

    /**
     * @tc.steps: step3. call Create and SetSoPath
     *            case: type = XCOMPONENT_COMPONENT_TYPE
     * @tc.expected: the properties are expected
     */
    const std::shared_ptr<InnerXComponentController> xComponentController2;
    XComponentModelNG xComponent2;
    xComponent2.Create(XCOMPONENT_ID, XCOMPONENT_COMPONENT_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME, xComponentController);
    xComponent2.SetSoPath(XCOMPONENT_SO_PATH);

    auto frameNode2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode2 != nullptr && frameNode2->GetTag() == V2::XCOMPONENT_ETS_TAG);
    auto xComponentPattern2 = frameNode2->GetPattern<XComponentPattern>();
    EXPECT_FALSE(xComponentPattern2 == nullptr);
    auto xComponentLayoutProperty2 = frameNode2->GetLayoutProperty<XComponentLayoutProperty>();
    EXPECT_FALSE(xComponentLayoutProperty2 == nullptr);
    EXPECT_TRUE(xComponentPattern2->GetSoPath()->empty());
    EXPECT_FALSE(xComponentPattern2->IsAtomicNode());
    EXPECT_EQ(xComponentLayoutProperty2->GetXComponentType().value_or(XComponentType::SURFACE),
        XCOMPONENT_COMPONENT_TYPE_VALUE);
}

/**
 * @tc.name: XComponentNDKTest003
 * @tc.desc: Test XComponent NDK interfaces.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPropertyTestNg, XComponentNDKTest003, TestSize.Level1)
{
    std::shared_ptr<InnerXComponentController> const xComponentController;
    XComponentModelNG xComponent;
    xComponent.Create(XCOMPONENT_ID, XCOMPONENT_SURFACE_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME, xComponentController);
    xComponent.SetSoPath(XCOMPONENT_SO_PATH);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::XCOMPONENT_ETS_TAG);

    auto xComponentPattern = frameNode->GetPattern<XComponentPattern>();
    EXPECT_FALSE(xComponentPattern == nullptr);

    auto pair = xComponentPattern->GetNativeXComponent();
    auto weakNativeXComponent = pair.second;
    auto nativeXComponent = weakNativeXComponent.lock();
    auto nativeXComponentImpl = pair.first;
    EXPECT_TRUE(nativeXComponent);
    EXPECT_TRUE(nativeXComponentImpl);
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
    std::shared_ptr<InnerXComponentController> const xComponentController;
    XComponentModelNG xComponent;
    xComponent.Create(XCOMPONENT_ID, XCOMPONENT_SURFACE_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME, xComponentController);
    xComponent.SetSoPath(XCOMPONENT_SO_PATH);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::XCOMPONENT_ETS_TAG);

    // Create LayoutWrapper and set XComponentLayoutAlgorithm.
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
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
    std::shared_ptr<InnerXComponentController> const xComponentController;
    XComponentModelNG xComponent;
    xComponent.Create(XCOMPONENT_ID, XCOMPONENT_COMPONENT_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME, xComponentController);
    xComponent.SetSoPath(XCOMPONENT_SO_PATH);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::XCOMPONENT_ETS_TAG);

    // Create LayoutWrapper and set XComponentLayoutAlgorithm.
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
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
    //           type: 'component',
    //           controller: this.xcomponentController
    //         })
    //         {
    //             Text().height(200).width(200)
    //         }.width(300).height(300)
    */
    auto childFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    childGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> const childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(childFrameNode, childGeometryNode, childFrameNode->GetLayoutProperty());
    childLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(CHILD_WIDTH), CalcLength(CHILD_HEIGHT)));

    auto boxLayoutAlgorithm = childFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
    childLayoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));

    frameNode->AddChild(childFrameNode);
    layoutWrapper.AppendChild(childLayoutWrapper);

    auto contentSize = xComponentLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper);
    EXPECT_EQ(contentSize, std::nullopt);

    auto childLayoutWrapper2 = layoutWrapper.GetOrCreateChildByIndex(0);
    xComponentLayoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameSize(), CONTAINER_SIZE);
    EXPECT_EQ(childLayoutWrapper2->GetGeometryNode()->GetFrameSize(), CHILD_SIZE);

    xComponentLayoutAlgorithm->Layout(&layoutWrapper);
    EXPECT_EQ(
        childLayoutWrapper2->GetGeometryNode()->GetFrameOffset(), OffsetF(CHILD_OFFSET_WIDTH, CHILD_OFFSET_HEIGHT));
}

/**
 * @tc.name: XComponentControllerSetExtControllerTest012
 * @tc.desc: Test XComponent type = XComponentType::SURFACE, ResetExtController, SetExtController
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPropertyTestNg, XComponentControllerSetExtControllerTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a XComponentModelNG
     *                   case:  type = XComponentType::SURFACE
     * @tc.expected: xcomponent frameNode create successfully
     */
    auto xComponentController = std::make_shared<XComponentControllerNG>();
    XComponentModelNG xComponent;
    xComponent.Create(XCOMPONENT_ID, XCOMPONENT_SURFACE_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME, xComponentController);
    xComponent.SetSoPath(XCOMPONENT_SO_PATH);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::XCOMPONENT_ETS_TAG);

    /**
     * @tc.steps: step2. call xComponentController->SetExtController
     * @tc.expected: result = XCOMPONENT_CONTROLLER_NO_ERROR
     */
    auto result = xComponentController->SetExtController(xComponentController);
    EXPECT_EQ(result, XCOMPONENT_CONTROLLER_NO_ERROR);

    /**
     * @tc.steps: step3. call xComponentController->ResetExtController
     * @tc.expected: result = XCOMPONENT_CONTROLLER_NO_ERROR
     */
    result = xComponentController->ResetExtController(xComponentController);
    EXPECT_EQ(result, XCOMPONENT_CONTROLLER_NO_ERROR);
}

/**
 * @tc.name: XComponentControllerSetExtControllerTest013
 * @tc.desc: Test SetExtController Error
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPropertyTestNg, XComponentControllerSetExtControllerTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a XComponentModelNG
     *                   case:  type != XComponentType::SURFACE
     * @tc.expected: xcomponent frameNode create successfully
     */
    auto xComponentController = std::make_shared<XComponentControllerNG>();
    XComponentModelNG xComponent;
    xComponent.Create(XCOMPONENT_ID, XCOMPONENT_NODE_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME, xComponentController);
    xComponent.SetSoPath(XCOMPONENT_SO_PATH);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::XCOMPONENT_ETS_TAG);

    /**
     * @tc.steps: step2. call xComponentController->SetExtController
     *                   case: !pattern
     * @tc.expected: result = XCOMPONENT_CONTROLLER_BAD_PARAMETER
     */
    auto result = xComponentController->SetExtController(xComponentController);
    EXPECT_EQ(result, XCOMPONENT_CONTROLLER_BAD_PARAMETER);

    /**
     * @tc.steps: step3. call xComponentController->SetExtController
     *                   case: pattern->GetType() != XComponentType::SURFACE
     * @tc.expected: result = XCOMPONENT_CONTROLLER_TYPE_ERROR
     */
    XComponentModelNG::SetXComponentType(Referenced::RawPtr(frameNode), XCOMPONENT_SURFACE_TYPE_VALUE);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    pattern->OnAttachToFrameNode();
    XComponentModelNG::SetXComponentType(Referenced::RawPtr(frameNode), XCOMPONENT_TEXTURE_TYPE_VALUE);
    result = xComponentController->SetExtController(xComponentController);
    EXPECT_EQ(result, XCOMPONENT_CONTROLLER_TYPE_ERROR);

    /**
     * @tc.steps: step4. call xComponentController->SetExtController
     *                   case: !extPattern
     * @tc.expected: result = XCOMPONENT_CONTROLLER_BAD_PARAMETER
     */
    XComponentModelNG::SetXComponentType(Referenced::RawPtr(frameNode), XCOMPONENT_SURFACE_TYPE_VALUE);
    pattern->OnAttachToFrameNode();
    auto xComponentController2 = std::make_shared<XComponentControllerNG>();
    result = xComponentController->SetExtController(xComponentController2);
    EXPECT_EQ(result, XCOMPONENT_CONTROLLER_BAD_PARAMETER);

    /**
     * @tc.steps: step5. call xComponentController->SetExtController
     *                   case: extPattern->GetType() != XComponentType::SURFACE
     * @tc.expected: result = XCOMPONENT_CONTROLLER_TYPE_ERROR
     */
    XComponentModelNG xComponent2;
    xComponent2.Create(XCOMPONENT_ID, XCOMPONENT_SURFACE_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME, xComponentController2);
    xComponent2.SetSoPath(XCOMPONENT_SO_PATH);
    auto frameNode2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode2 != nullptr && frameNode2->GetTag() == V2::XCOMPONENT_ETS_TAG);

    XComponentModelNG::SetXComponentType(Referenced::RawPtr(frameNode2), XCOMPONENT_TEXTURE_TYPE_VALUE);
    result = xComponentController->SetExtController(xComponentController2);
    EXPECT_EQ(result, XCOMPONENT_CONTROLLER_TYPE_ERROR);
}

/**
 * @tc.name: XComponentControllerResetExtControllerTest014
 * @tc.desc: Test ResetExtController error
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPropertyTestNg, XComponentControllerResetExtControllerTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a XComponentModelNG
     *                   case:  type != XComponentType::SURFACE
     * @tc.expected: xcomponent frameNode create successfully
     */
    auto xComponentController = std::make_shared<XComponentControllerNG>();
    XComponentModelNG xComponent;
    xComponent.Create(XCOMPONENT_ID, XCOMPONENT_COMPONENT_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME, xComponentController);
    xComponent.SetSoPath(XCOMPONENT_SO_PATH);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::XCOMPONENT_ETS_TAG);

    /**
     * @tc.steps: step2. call xComponentController->ResetExtController
     *                   case: !pattern
     * @tc.expected: result = XCOMPONENT_CONTROLLER_BAD_PARAMETER
     */
    auto result = xComponentController->ResetExtController(xComponentController);
    EXPECT_EQ(result, XCOMPONENT_CONTROLLER_BAD_PARAMETER);

    /**
     * @tc.steps: step3. call xComponentController->ResetExtController
     *                   case: pattern->GetType() != XComponentType::SURFACE
     * @tc.expected: result = XCOMPONENT_CONTROLLER_TYPE_ERROR
     */
    XComponentModelNG::SetXComponentType(Referenced::RawPtr(frameNode), XCOMPONENT_SURFACE_TYPE_VALUE);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    pattern->OnAttachToFrameNode();
    XComponentModelNG::SetXComponentType(Referenced::RawPtr(frameNode), XCOMPONENT_TEXTURE_TYPE_VALUE);
    result = xComponentController->ResetExtController(xComponentController);
    EXPECT_EQ(result, XCOMPONENT_CONTROLLER_TYPE_ERROR);

    /**
     * @tc.steps: step4. call xComponentController->ResetExtController
     *                   case: !extPattern
     * @tc.expected: result = XCOMPONENT_CONTROLLER_BAD_PARAMETER
     */
    XComponentModelNG::SetXComponentType(Referenced::RawPtr(frameNode), XCOMPONENT_SURFACE_TYPE_VALUE);
    pattern->OnAttachToFrameNode();
    auto xComponentController2 = std::make_shared<XComponentControllerNG>();
    result = xComponentController->ResetExtController(xComponentController2);
    EXPECT_EQ(result, XCOMPONENT_CONTROLLER_BAD_PARAMETER);

    /**
     * @tc.steps: step5. call xComponentController->ResetExtController
     *                   case: extPattern->GetType() != XComponentType::SURFACE
     * @tc.expected: result = XCOMPONENT_CONTROLLER_TYPE_ERROR
     */
    XComponentModelNG xComponent2;
    xComponent2.Create(XCOMPONENT_ID, XCOMPONENT_SURFACE_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME, xComponentController2);
    xComponent2.SetSoPath(XCOMPONENT_SO_PATH);
    auto frameNode2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode2 != nullptr && frameNode2->GetTag() == V2::XCOMPONENT_ETS_TAG);

    XComponentModelNG::SetXComponentType(Referenced::RawPtr(frameNode2), XCOMPONENT_TEXTURE_TYPE_VALUE);
    result = xComponentController->ResetExtController(xComponentController2);
    EXPECT_EQ(result, XCOMPONENT_CONTROLLER_TYPE_ERROR);
}

/**
 * @tc.name: XComponentPaintMethodTest015
 * @tc.desc: Test XComponent type = XComponentType::TEXTURE
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPropertyTestNg, XComponentPaintMethodTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a XComponentModelNG
     *                   case:  type = XComponentType::TEXTURE
     * @tc.expected: xcomponent frameNode create successfully
     */
    auto xComponentController = std::make_shared<XComponentControllerNG>();
    XComponentModelNG xComponent;
    xComponent.Create(XCOMPONENT_ID, XCOMPONENT_TEXTURE_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME, xComponentController);
    xComponent.SetSoPath(XCOMPONENT_SO_PATH);
    EXPECT_TRUE(xComponent.IsTexture());

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::XCOMPONENT_ETS_TAG);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. xComponent.IsTexture
     * @tc.expected: true
     */
    EXPECT_TRUE(xComponent.IsTexture(Referenced::RawPtr(frameNode)));

    /**
     * @tc.steps: step3. xComponent.GetType
     * @tc.expected: type = XCOMPONENT_TEXTURE_TYPE_VALUE
     */
    auto type = xComponent.GetType(Referenced::RawPtr(frameNode));
    EXPECT_EQ(type, XCOMPONENT_TEXTURE_TYPE_VALUE);

    /**
     * @tc.steps: step4. PaintMethod GetContentDrawFunction.
     */
    auto renderProperty = pattern->GetPaintProperty<PaintProperty>();
    ASSERT_NE(renderProperty, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(MAX_SIZE);
    geometryNode->SetContentSize(MAX_SIZE);
    PaintWrapper paintWrapper(frameNode->GetRenderContext(), geometryNode, renderProperty);
    auto paintMethodNode = pattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethodNode, nullptr);
    auto paintMethod = paintMethodNode->GetContentDrawFunction(&paintWrapper);
    ASSERT_NE(paintMethod, nullptr);
    RSCanvas canvas;
    paintMethod(canvas);

    EXPECT_CALL(*AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_), IsSurfaceValid())
        .WillOnce(Return(true))
        .WillOnce(Return(true))
        .WillRepeatedly(Return(false));
    EXPECT_CALL(*AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_),
        AdjustNativeWindowSize(_, _))
        .WillOnce(Return());
    // goto other branch
    XComponentModelNG::SetXComponentType(Referenced::RawPtr(frameNode), XCOMPONENT_COMPONENT_TYPE_VALUE);
    pattern->XComponentSizeInit(); // IsSurfaceValid=false
    paintMethodNode = pattern->CreateNodePaintMethod();
    EXPECT_EQ(paintMethodNode, nullptr);

    XComponentModelNG::SetXComponentType(Referenced::RawPtr(frameNode), XCOMPONENT_SURFACE_TYPE_VALUE);
    pattern->XComponentSizeInit(); // IsSurfaceValid=false
    paintMethodNode = pattern->CreateNodePaintMethod();
    EXPECT_EQ(paintMethodNode, nullptr);
}


/**
 * @tc.name: XComponentGetSizeTest016
 * @tc.desc: Test XComponent GetSize, type = XComponentType::SURFACE
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPropertyTestNg, XComponentGetSizeTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ComponentController.
     * @tc.expected: xcomponent frameNode create successfully
     */
    auto xComponentController = std::make_shared<XComponentControllerNG>();
    XComponentModelNG xComponent;
    xComponent.Create(XCOMPONENT_ID, XCOMPONENT_SURFACE_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME, xComponentController);
    xComponent.SetSoPath(XCOMPONENT_SO_PATH);
    EXPECT_FALSE(xComponent.IsTexture());

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::XCOMPONENT_ETS_TAG);

    /**
     * @tc.steps: step2. xComponent.IsTexture
     * @tc.expected: true
     */
    EXPECT_FALSE(xComponent.IsTexture(Referenced::RawPtr(frameNode)));

    /**
     * @tc.steps: step3. xComponent.GetType
     * @tc.expected: type = XCOMPONENT_SURFACE_TYPE_VALUE
     */
    auto type = xComponent.GetType(Referenced::RawPtr(frameNode));
    EXPECT_EQ(type, XCOMPONENT_SURFACE_TYPE_VALUE);

    /**
     * @tc.steps: step4. call BeforeSyncGeometryProperties
     *            case: hasXComponentInit_ = false
     * @tc.expected: hasXComponentInit_ = true
     */
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    DirtySwapConfig config;
    auto xComponentLayoutAlgorithm = AceType::MakeRefPtr<XComponentLayoutAlgorithm>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(MAX_SIZE);
    geometryNode->SetContentSize(MAX_SIZE);
    geometryNode->SetFrameOffset(OffsetF(MAX_WIDTH, MAX_HEIGHT));
    frameNode->geometryNode_ = geometryNode;
    EXPECT_FALSE(pattern->hasXComponentInit_);
    EXPECT_CALL(*AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_), IsSurfaceValid())
        .WillOnce(Return(true))
        .WillOnce(Return(true))
        .WillRepeatedly(Return(false));
    EXPECT_CALL(*AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_),
        AdjustNativeWindowSize(MAX_WIDTH, MAX_HEIGHT))
        .WillOnce(Return());
    pattern->BeforeSyncGeometryProperties(config); // IsSurfaceValid=true
    EXPECT_TRUE(pattern->hasXComponentInit_);
    // test OnRebuildFrame
    pattern->OnRebuildFrame(); // type="surface", IsSurfaceValid=true
    pattern->OnRebuildFrame(); // type="surface", IsSurfaceValid=false

    /**
     * @tc.steps: step5. GetSize
     * @tc.expected: result == XCOMPONENT_CONTROLLER_NO_ERROR,
     *               w == MAX_WIDTH
     *               h == MAX_HEIGHT
     */
    float w, h;
    auto result = xComponentController->GetSize(w, h);
    EXPECT_EQ(result, XCOMPONENT_CONTROLLER_NO_ERROR);
    EXPECT_EQ(w, MAX_WIDTH);
    EXPECT_EQ(h, MAX_HEIGHT);

    /**
     * @tc.steps: step6. GetSize
     * @tc.desc: Test XComponent type = XComponentType::COMPONENT
     */
    XComponentModelNG::SetXComponentType(Referenced::RawPtr(frameNode), XCOMPONENT_COMPONENT_TYPE_VALUE);
    pattern->XComponentSizeInit(); // IsSurfaceValid=false
    pattern->OnRebuildFrame();     // type="component"
    result = xComponentController->GetSize(w, h);
    EXPECT_EQ(result, XCOMPONENT_CONTROLLER_TYPE_ERROR);
}

/**
 * @tc.name: XComponentSetRenderTypeTest17
 * @tc.desc: Test XComponent SetRenderType
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPropertyTestNg, XComponentSetRenderTypeTest17, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ComponentController.
     * @tc.expected: xcomponent frameNode create successfully
     */
    auto xComponentController = std::make_shared<XComponentControllerNG>();
    XComponentModelNG xComponent;
    xComponent.Create(XCOMPONENT_ID, XCOMPONENT_SURFACE_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME, xComponentController);
    xComponent.SetSoPath(XCOMPONENT_SO_PATH);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::XCOMPONENT_ETS_TAG);

    /**
     * @tc.steps: step2. call SetRenderType
     *            case: hasXComponentInit_ = false
     * @tc.expected: hasXComponentInit_ = true
     */
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    DirtySwapConfig config;
    auto xComponentLayoutAlgorithm = AceType::MakeRefPtr<XComponentLayoutAlgorithm>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(MAX_SIZE);
    geometryNode->SetContentSize(MAX_SIZE);
    frameNode->geometryNode_ = geometryNode;
    EXPECT_FALSE(pattern->hasXComponentInit_);
    EXPECT_CALL(*AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_), IsSurfaceValid())
        .WillOnce(Return(true))
        .WillRepeatedly(Return(false));
    EXPECT_CALL(*AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_),
        AdjustNativeWindowSize(MAX_WIDTH, MAX_HEIGHT))
        .WillOnce(Return());

    pattern->SetRenderType(NodeRenderType::RENDER_TYPE_TEXTURE);
    pattern->BeforeSyncGeometryProperties(config); // IsSurfaceValid=true
    EXPECT_TRUE(pattern->hasXComponentInit_);
}

/**
 * @tc.name: XComponentRenderTypeTest018
 * @tc.desc: Test XComponent ChangeRenderType
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPropertyTestNg, XComponentRenderTypeTest018, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();

    /**
     * @tc.steps: step1. create root node.
     * @tc.expected: frameNode create successfully
     */
    auto rootNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto rootFrameNode = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, rootNodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    ASSERT_TRUE(rootFrameNode != nullptr);

    /**
     * @tc.steps: step2. create NodeContainer.
     * @tc.expected: NodeContainer create successfully
     */
    auto nodeId = stack->ClaimNodeId();
    auto nodeContainerFrameNode = FrameNode::GetOrCreateFrameNode(
        "NodeContainer", nodeId, []() { return AceType::MakeRefPtr<NodeContainerPattern>(); });
    stack->Push(nodeContainerFrameNode);
    rootFrameNode->AddChild(nodeContainerFrameNode);

    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Alignment, Alignment::TOP_LEFT);

    /**
     * @tc.steps: step3. create ComponentController.
     * @tc.expected: xcomponent frameNode create successfully
     */
    auto xComponentController = std::make_shared<XComponentControllerNG>();
    XComponentModelNG xComponent;
    xComponent.Create(XCOMPONENT_ID, XCOMPONENT_SURFACE_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME, xComponentController);
    xComponent.SetSoPath(XCOMPONENT_SO_PATH);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::XCOMPONENT_ETS_TAG);
    nodeContainerFrameNode->AddChild(frameNode);

    /**
     * @tc.steps: step4. call ChangeRenderType
     *            case: NodeRenderType::RENDER_TYPE_DISPLAY
     *            case: StopTextureExport true
     * @tc.expected: flag = true
     */
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    EXPECT_CALL(*AceType::DynamicCast<MockRenderContext>(pattern->handlingSurfaceRenderContext_), StopTextureExport())
        .WillOnce(Return(true));
    auto flag = pattern->ChangeRenderType(NodeRenderType::RENDER_TYPE_DISPLAY); // StopTextureExport() = true
    EXPECT_TRUE(flag);

    /**
     * @tc.steps: step5. call ChangeRenderType
     *            case: NodeRenderType::RENDER_TYPE_DISPLAY
     *            case: StopTextureExport false
     * @tc.expected: flag = true
     */
    EXPECT_CALL(*AceType::DynamicCast<MockRenderContext>(pattern->handlingSurfaceRenderContext_), StopTextureExport())
        .WillOnce(Return(false));
    flag = pattern->ChangeRenderType(NodeRenderType::RENDER_TYPE_DISPLAY); // StopTextureExport() = false
    EXPECT_FALSE(flag);

    /**
     * @tc.steps: step6. call ChangeRenderType
     *            case: NodeRenderType::RENDER_TYPE_TEXTURE
     * @tc.expected: flag = false
     */
    EXPECT_CALL(*AceType::DynamicCast<MockRenderContext>(pattern->handlingSurfaceRenderContext_), DoTextureExport(_))
        .WillOnce(Return(false));
    flag = pattern->ChangeRenderType(NodeRenderType::RENDER_TYPE_TEXTURE); // DoTextureExport() = false
    EXPECT_FALSE(flag);

    /**
     * @tc.steps: step7. call ChangeRenderType
     *            case: NodeRenderType::RENDER_TYPE_TEXTURE
     * @tc.expected: flag = false
     */
    EXPECT_CALL(*AceType::DynamicCast<MockRenderContext>(pattern->handlingSurfaceRenderContext_), DoTextureExport(_))
        .WillOnce(Return(true));
    flag = pattern->ChangeRenderType(NodeRenderType::RENDER_TYPE_TEXTURE); // DoTextureExport() = true
    EXPECT_TRUE(flag);

    /**
     * @tc.steps: step8. call ChangeRenderType
     *            case: type_ != XComponentType::SURFACE
     *            case: type_ == NodeRenderType::RENDER_TYPE_DISPLAY
     * @tc.expected: flag = true
     */
    XComponentModelNG::SetXComponentType(Referenced::RawPtr(frameNode), XCOMPONENT_COMPONENT_TYPE_VALUE);
    flag = pattern->ChangeRenderType(NodeRenderType::RENDER_TYPE_DISPLAY);
    EXPECT_TRUE(flag);

    /**
     * @tc.steps: step9. call ChangeRenderType
     *            case: type_ != XComponentType::SURFACE
     *            case: type_ != NodeRenderType::RENDER_TYPE_DISPLAY
     * @tc.expected: flag = false
     */
    XComponentModelNG::SetXComponentType(Referenced::RawPtr(frameNode), XCOMPONENT_TEXTURE_TYPE_VALUE);
    flag = pattern->ChangeRenderType(NodeRenderType::RENDER_TYPE_TEXTURE);
    EXPECT_FALSE(flag);

    /**
     * @tc.steps: step10. call ChangeRenderType
     *            case: !host->GetNodeContainer()
     * @tc.expected: flag = true
     */
    nodeContainerFrameNode->RemoveChild(frameNode);
    XComponentModelNG::SetXComponentType(Referenced::RawPtr(frameNode), XCOMPONENT_SURFACE_TYPE_VALUE);
    flag = pattern->ChangeRenderType(NodeRenderType::RENDER_TYPE_TEXTURE);
    EXPECT_TRUE(flag);
}
} // namespace OHOS::Ace::NG
