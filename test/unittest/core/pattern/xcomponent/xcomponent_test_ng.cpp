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
const float FORCE = 3.0f;
TestProperty testProperty;
bool isFocus = false;
int g_surfaceShowNum = 1;
const float SURFACE_WIDTH = 250.0f;
const float SURFACE_HEIGHT = 150.0f;
const float SURFACE_OFFSETX = 10.0f;
const float SURFACE_OFFSETY = 20.0f;
bool isAxis = false;

TouchType ConvertXComponentTouchType(const OH_NativeXComponent_TouchEventType& type)
{
    switch (type) {
        case OH_NativeXComponent_TouchEventType::OH_NATIVEXCOMPONENT_CANCEL:
            return TouchType::CANCEL;
        case OH_NATIVEXCOMPONENT_DOWN:
            return TouchType::DOWN;
        case OH_NATIVEXCOMPONENT_UP:
            return TouchType::UP;
        case OH_NATIVEXCOMPONENT_MOVE:
            return TouchType::MOVE;
        case OH_NATIVEXCOMPONENT_UNKNOWN:
            return TouchType::UNKNOWN;
        default:
            return TouchType::UNKNOWN;
    }
}

OH_NativeXComponent_KeyAction ConvertNativeXComponentKeyAction(const KeyAction& keyAction)
{
    switch (keyAction) {
        case KeyAction::DOWN:
            return OH_NativeXComponent_KeyAction::OH_NATIVEXCOMPONENT_KEY_ACTION_DOWN;
        case KeyAction::UP:
            return OH_NativeXComponent_KeyAction::OH_NATIVEXCOMPONENT_KEY_ACTION_UP;
        default:
            return OH_NativeXComponent_KeyAction::OH_NATIVEXCOMPONENT_KEY_ACTION_UNKNOWN;
    }
}

OH_NativeXComponent_EventSourceType ConvertNativeXComponentEventSourceType(const SourceType& sourceType)
{
    switch (sourceType) {
        case SourceType::MOUSE:
            return OH_NativeXComponent_EventSourceType::OH_NATIVEXCOMPONENT_SOURCE_TYPE_MOUSE;
        case SourceType::TOUCH:
            return OH_NativeXComponent_EventSourceType::OH_NATIVEXCOMPONENT_SOURCE_TYPE_TOUCHSCREEN;
        case SourceType::TOUCH_PAD:
            return OH_NativeXComponent_EventSourceType::OH_NATIVEXCOMPONENT_SOURCE_TYPE_TOUCHPAD;
        case SourceType::KEYBOARD:
            return OH_NativeXComponent_EventSourceType::OH_NATIVEXCOMPONENT_SOURCE_TYPE_KEYBOARD;
        default:
            return OH_NativeXComponent_EventSourceType::OH_NATIVEXCOMPONENT_SOURCE_TYPE_UNKNOWN;
    }
}
} // namespace

class XComponentTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();

protected:
    static RefPtr<FrameNode> CreateXComponentNode(TestProperty& testProperty);
};

void XComponentTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    testProperty.xcId = XCOMPONENT_ID;
    testProperty.libraryName = XCOMPONENT_LIBRARY_NAME;
    testProperty.soPath = XCOMPONENT_SO_PATH;
}

void XComponentTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> XComponentTestNg::CreateXComponentNode(TestProperty& testProperty)
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
HWTEST_F(XComponentTestNg, XComponentPropertyTest001, TestSize.Level1)
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
 * @tc.name: XComponentEventTest002
 * @tc.desc: Test XComponent onLoad and onDestroy event.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, XComponentEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set the testProperty and CreateXComponentNode
     *            case: type = XCOMPONENT_SURFACE_TYPE
     * @tc.expected: frameNode create successfully
     */
    std::string onLoadKey;
    std::string onDestroyKey;
    auto onLoad = [&onLoadKey](const std::string& /* xComponentId */) { onLoadKey = CHECK_KEY; };
    auto onDestroy = [&onDestroyKey]() { onDestroyKey = CHECK_KEY; };

    testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    testProperty.loadEvent = std::move(onLoad);
    testProperty.destroyEvent = std::move(onDestroy);
    auto frameNode = CreateXComponentNode(testProperty);
    EXPECT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::XCOMPONENT_ETS_TAG);

    /**
     * @tc.steps: step2. call FireLoadEvent, FireDestroyEvent
     * @tc.expected: three checkKeys has changed
     */
    auto xComponentEventHub = frameNode->GetEventHub<XComponentEventHub>();
    ASSERT_TRUE(xComponentEventHub);
    xComponentEventHub->FireLoadEvent(XCOMPONENT_ID);
    xComponentEventHub->FireDestroyEvent();
    EXPECT_EQ(onLoadKey, CHECK_KEY);
    EXPECT_EQ(onDestroyKey, CHECK_KEY);

    /**
     * @tc.steps: step3. reset the testProperty and rerun step1&2
     *            case: type = XCOMPONENT_COMPONENT_TYPE
     * @tc.expected: three checkKeys has no change
     */

    auto onLoad2 = [&onLoadKey](const std::string& /* xComponentId */) { onLoadKey = ""; };
    auto onDestroy2 = [&onDestroyKey]() { onDestroyKey = ""; };
    testProperty.xcType = XCOMPONENT_COMPONENT_TYPE_VALUE;
    testProperty.loadEvent = std::move(onLoad2);
    testProperty.destroyEvent = std::move(onDestroy2);

    auto frameNode2 = CreateXComponentNode(testProperty);
    EXPECT_TRUE(frameNode2);
    xComponentEventHub = frameNode2->GetEventHub<XComponentEventHub>();
    ASSERT_TRUE(xComponentEventHub);
    xComponentEventHub->FireLoadEvent(XCOMPONENT_ID);
    xComponentEventHub->FireDestroyEvent();
    EXPECT_EQ(onLoadKey, CHECK_KEY);
    EXPECT_EQ(onDestroyKey, CHECK_KEY);
}

/**
 * @tc.name: XComponentNDKTest003
 * @tc.desc: Test XComponent NDK interfaces.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, XComponentNDKTest003, TestSize.Level1)
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
HWTEST_F(XComponentTestNg, XComponentLayoutAlgorithmTest004, TestSize.Level1)
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
HWTEST_F(XComponentTestNg, XComponentLayoutAlgorithmTest005, TestSize.Level1)
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
 * @tc.name: XComponentLayoutAlgorithmTest006
 * @tc.desc: Test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, XComponentLayoutAlgorithmTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set type = XCOMPONENT_SURFACE_TYPE and call CreateXComponentNode
     * @tc.expected: frameNode create successfully
     */
    testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap
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
    auto layoutProperty = frameNode->GetLayoutProperty<XComponentLayoutProperty>();
    EXPECT_TRUE(layoutProperty);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(xComponentLayoutAlgorithm, false);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    EXPECT_FALSE(pattern->hasXComponentInit_);
    EXPECT_CALL(*AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_), IsSurfaceValid())
        .WillOnce(Return(true))
        .WillOnce(Return(true))
        .WillRepeatedly(Return(false));
    EXPECT_CALL(*AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_),
        AdjustNativeWindowSize(MAX_WIDTH, MAX_HEIGHT))
        .WillOnce(Return());
    auto flag = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config); // IsSurfaceValid=true
    EXPECT_FALSE(flag);
    EXPECT_TRUE(pattern->hasXComponentInit_);
    // test OnRebuildFrame
    pattern->OnRebuildFrame(); // type="surface", IsSurfaceValid=true
    pattern->OnRebuildFrame(); // type="surface", IsSurfaceValid=false
    // goto other branch
    pattern->type_ = XCOMPONENT_COMPONENT_TYPE_VALUE;
    pattern->XComponentSizeInit(); // IsSurfaceValid=false
    pattern->OnRebuildFrame();     // type="component"

    /**
     * @tc.steps: step3. call OnDirtyLayoutWrapperSwap adjust frameOffsetChanges, contentOffsetChanges and
     *                   contentSizeChanges
     * @tc.expected: OnDirtyLayoutWrapperSwap return false
     */
    bool frameOffsetChanges[2] = { false, true };
    bool contentOffsetChanges[2] = { false, true };
    pattern->type_ = XCOMPONENT_SURFACE_TYPE_VALUE;
    for (bool frameOffsetChange : frameOffsetChanges) {
        for (bool contentOffsetChange : contentOffsetChanges) {
            config.frameOffsetChange = frameOffsetChange;
            config.contentOffsetChange = contentOffsetChange;
            config.contentSizeChange = frameOffsetChange && contentOffsetChange;
            if (config.contentSizeChange) {
                geometryNode->SetContentSize(CHILD_SIZE);
                EXPECT_CALL(*AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_),
                    AdjustNativeWindowSize(CHILD_WIDTH, CHILD_HEIGHT))
                    .WillOnce(Return());
            }
            flag = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
            EXPECT_FALSE(flag);
        }
    }

    /**
     * @tc.steps: step4. call OnDirtyLayoutWrapperSwap
     *            case: size is zero
     * @tc.expected: OnDirtyLayoutWrapperSwap return false
     */
    geometryNode->SetContentSize({ 0.0f, 0.0f });
    flag = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(flag);

    /**
     * @tc.steps: step5. call OnDirtyLayoutWrapperSwap
     *            case: type="component", config.skipMeasure = true, dirty->SkipMeasureContent() = true
     * @tc.expected: OnDirtyLayoutWrapperSwap return false
     */
    layoutWrapper->skipMeasureContent_ = true;
    flag = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(flag);
    config.skipMeasure = true;
    flag = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(flag);
    pattern->type_ = XCOMPONENT_COMPONENT_TYPE_VALUE;
    flag = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(flag);
}

/**
 * @tc.name: XComponentMouseEventTest007
 * @tc.desc: Test MouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, XComponentMouseEventTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set type = XCOMPONENT_SURFACE_TYPE and call CreateXComponentNode
     * @tc.expected: xcomponent frameNode create successfully
     */
    testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    pattern->hasXComponentInit_ = true;

    /**
     * @tc.steps: step2. prepare mouse info
     */
    MouseInfo mouseInfo;
    std::vector<MouseAction> mouseActions { MouseAction::NONE, MouseAction::PRESS, MouseAction::RELEASE,
        MouseAction::MOVE };
    std::vector<MouseButton> mouseButtons {
        MouseButton::NONE_BUTTON,
        MouseButton::LEFT_BUTTON,
        MouseButton::RIGHT_BUTTON,
        MouseButton::MIDDLE_BUTTON,
        MouseButton::BACK_BUTTON,
        MouseButton::FORWARD_BUTTON,
    };

    /**
     * @tc.steps: step3. call HandleMouseEvent
     * @tc.expected: no error happens
     */
    for (MouseAction& action : mouseActions) {
        mouseInfo.SetAction(action);
        pattern->HandleMouseEvent(mouseInfo);
        pattern->HandleMouseHoverEvent(true);
        pattern->HandleMouseHoverEvent(false);
    }
    for (MouseButton& button : mouseButtons) {
        mouseInfo.SetButton(button);
        pattern->HandleMouseEvent(mouseInfo);
    }
}

/**
 * @tc.name: XComponentTouchEventTest008
 * @tc.desc: Test TouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, XComponentTouchEventTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set type = XCOMPONENT_SURFACE_TYPE and call CreateXComponentNode
     * @tc.expected: xcomponent frameNode create successfully
     */
    testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. prepare touchEvent info
     */
    std::vector<TouchType> touchTypes { TouchType::DOWN, TouchType::UP, TouchType::MOVE, TouchType::CANCEL,
        TouchType::UNKNOWN };
    std::vector<SourceTool> sourceTools {
        SourceTool::UNKNOWN,
        SourceTool::FINGER,
        SourceTool::PEN,
        SourceTool::RUBBER,
        SourceTool::BRUSH,
        SourceTool::PENCIL,
        SourceTool::AIRBRUSH,
        SourceTool::MOUSE,
        SourceTool::LENS,
    };

    /**
     * @tc.steps: step3. call HandleTouchEvent
     *            case: touchEventInfo.GetChangedTouches is empty
     * @tc.expected: pattern->touchEventPoint_.numPoints not change
     */
    TouchEventInfo touchEventInfoEmpty("onTouch");
    uint32_t numPoints = pattern->touchEventPoint_.numPoints;
    pattern->HandleTouchEvent(touchEventInfoEmpty);
    EXPECT_EQ(pattern->touchEventPoint_.numPoints, numPoints);

    /**
     * @tc.steps: step4. call HandleTouchEvent
     *            case: different touchType
     * @tc.expected: touchType fit
     */
    for (TouchType& touchType : touchTypes) {
        TouchEventInfo touchEventInfo("onTouch");
        TouchLocationInfo locationInfo(1);
        locationInfo.SetTouchType(touchType);
        touchEventInfo.AddChangedTouchLocationInfo(std::move(locationInfo));
        pattern->HandleTouchEvent(touchEventInfo);
        EXPECT_EQ(
            static_cast<int>(ConvertXComponentTouchType(pattern->touchEventPoint_.type)), static_cast<int>(touchType));
    }

    /**
     * @tc.steps: step5. call HandleTouchEvent
     *            case: different sourceToolType
     * @tc.expected: sourceToolType fit
     */
    TouchEventInfo touchEventInfo("onTouch");
    TouchLocationInfo locationInfo(0);
    locationInfo.SetTouchType(TouchType::DOWN);
    touchEventInfo.AddChangedTouchLocationInfo(std::move(locationInfo));
    for (int i = 0; i < static_cast<int>(OH_MAX_TOUCH_POINTS_NUMBER) + 1; i++) { // over the OH_MAX_TOUCH_POINTS_NUMBER
        TouchLocationInfo pointInfo(i);
        pointInfo.SetSourceTool(sourceTools[i % sourceTools.size()]);
        touchEventInfo.AddTouchLocationInfo(std::move(pointInfo));
    }
    pattern->HandleTouchEvent(touchEventInfo);
    EXPECT_EQ(pattern->nativeXComponentTouchPoints_.size(), OH_MAX_TOUCH_POINTS_NUMBER);
    for (int i = 0; i < static_cast<int>(OH_MAX_TOUCH_POINTS_NUMBER); i++) {
        EXPECT_EQ(static_cast<int>(pattern->nativeXComponentTouchPoints_[i].sourceToolType),
            static_cast<int>(sourceTools[i % sourceTools.size()]));
    }
}

/**
 * @tc.name: XComponentTouchEventTest009
 * @tc.desc: Test TouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, XComponentTouchEventTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set type = XCOMPONENT_SURFACE_TYPE and call CreateXComponentNode
     * @tc.expected: xcomponent frameNode create successfully
     */
    testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    RefPtr<LayoutProperty> layoutPropertyTest = frameNode->GetLayoutProperty<LayoutProperty>();
    ASSERT_TRUE(layoutPropertyTest);
    RefPtr<Property> propertyTest = frameNode->GetPaintProperty<Property>();
    ASSERT_TRUE(propertyTest);
}

/**
 * @tc.name: XComponentKeyEventTest010
 * @tc.desc: Test KeyEvent/FocusEvent/BlurEvent
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, XComponentKeyEventTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set type = XCOMPONENT_SURFACE_TYPE and call CreateXComponentNode
     * @tc.expected: xcomponent frameNode create successfully
     */
    testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. create focusHub & nativeXComponent instance
     * @tc.expected: focusHub & nativeXComponent instance create successfully
     */
    auto host = pattern->GetHost();
    ASSERT_TRUE(host);
    auto focusHub = host->GetFocusHub();
    ASSERT_TRUE(focusHub);
    auto pair = pattern->GetNativeXComponent();
    auto weakNativeXComponent = pair.second;
    auto nativeXComponent = weakNativeXComponent.lock();
    auto nativeXComponentImpl = pair.first;
    ASSERT_TRUE(nativeXComponent);
    ASSERT_TRUE(nativeXComponentImpl);

    /**
     * @tc.steps: step3. register focus & blur event for nativeXComponent instance
     */
    nativeXComponent->RegisterFocusEventCallback(
        [](OH_NativeXComponent* /* nativeXComponent */, void* /* window */) { isFocus = true; });
    nativeXComponent->RegisterBlurEventCallback(
        [](OH_NativeXComponent* /* nativeXComponent */, void* /* window */) { isFocus = false; });

    /**
     * @tc.steps: step4. call focusHub's focus & blur event
     * @tc.expected: the callbacks registered in step3 are called
     */
    focusHub->onFocusInternal_();
    EXPECT_TRUE(isFocus);
    focusHub->onBlurInternal_();
    EXPECT_FALSE(isFocus);

    /**
     * @tc.steps: step5. call HandleKeyEvent
     *            case: different sourceType & keyAction
     * @tc.expected: sourceType & keyAction fit
     */
    std::vector<SourceType> sourceTypes { SourceType::NONE, SourceType::MOUSE, SourceType::TOUCH, SourceType::TOUCH_PAD,
        SourceType::KEYBOARD };
    std::vector<KeyAction> keyActions { KeyAction::UNKNOWN, KeyAction::DOWN, KeyAction::UP };
    for (SourceType& sourceType : sourceTypes) {
        for (KeyAction& keyAction : keyActions) {
            KeyEvent keyEvent { KeyCode::KEY_0, keyAction, 0, 0, 0, sourceType };
            focusHub->ProcessOnKeyEventInternal(keyEvent);
            EXPECT_EQ(nativeXComponentImpl->keyEvent_.sourceType, ConvertNativeXComponentEventSourceType(sourceType));
            EXPECT_EQ(nativeXComponentImpl->keyEvent_.action, ConvertNativeXComponentKeyAction(keyAction));
        }
    }
}

/**
 * @tc.name: XComponentKeyEventTest011
 * @tc.desc: Test XComponent type = XComponentType::TEXTURE
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, XComponentTextureTypeTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set type = XCOMPONENT_TEXTURE_TYPE_VALUE and call CreateXComponentNode
     * @tc.expected: xcomponent frameNode create successfully
     */
    testProperty.xcType = XCOMPONENT_TEXTURE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(testProperty);
    EXPECT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::XCOMPONENT_ETS_TAG);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    pattern->hasXComponentInit_ = true;
    EXPECT_EQ(pattern->type_, XCOMPONENT_TEXTURE_TYPE_VALUE);
    EXPECT_TRUE(pattern->IsAtomicNode());

    /**
     * @tc.steps: step2. call InitNativeWindow
     * @tc.expected: renderSurface_->AdjustNativeWindowSize is called
     */
    EXPECT_CALL(*AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_), IsSurfaceValid())
        .WillOnce(Return(true));
    EXPECT_CALL(*AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_),
        AdjustNativeWindowSize(MAX_WIDTH, MAX_HEIGHT))
        .WillOnce(Return());
    pattern->InitNativeWindow(MAX_WIDTH, MAX_HEIGHT);
}

/**
 * @tc.name: XComponentControllerSetExtControllerTest012
 * @tc.desc: Test XComponent type = XComponentType::SURFACE, ResetExtController, SetExtController
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, XComponentControllerSetExtControllerTest012, TestSize.Level1)
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
HWTEST_F(XComponentTestNg, XComponentControllerSetExtControllerTest013, TestSize.Level1)
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
HWTEST_F(XComponentTestNg, XComponentControllerResetExtControllerTest014, TestSize.Level1)
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
HWTEST_F(XComponentTestNg, XComponentPaintMethodTest015, TestSize.Level1)
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
HWTEST_F(XComponentTestNg, XComponentGetSizeTest016, TestSize.Level1)
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
     * @tc.steps: step4. call OnDirtyLayoutWrapperSwap
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
    auto layoutProperty = frameNode->GetLayoutProperty<XComponentLayoutProperty>();
    EXPECT_TRUE(layoutProperty);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(xComponentLayoutAlgorithm, false);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    EXPECT_FALSE(pattern->hasXComponentInit_);
    EXPECT_CALL(*AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_), IsSurfaceValid())
        .WillOnce(Return(true))
        .WillOnce(Return(true))
        .WillRepeatedly(Return(false));
    EXPECT_CALL(*AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_),
        AdjustNativeWindowSize(MAX_WIDTH, MAX_HEIGHT))
        .WillOnce(Return());
    auto flag = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config); // IsSurfaceValid=true
    EXPECT_FALSE(flag);
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
HWTEST_F(XComponentTestNg, XComponentSetRenderTypeTest17, TestSize.Level1)
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
    auto layoutProperty = frameNode->GetLayoutProperty<XComponentLayoutProperty>();
    EXPECT_TRUE(layoutProperty);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(xComponentLayoutAlgorithm, false);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    EXPECT_FALSE(pattern->hasXComponentInit_);
    EXPECT_CALL(*AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_), IsSurfaceValid())
        .WillOnce(Return(true))
        .WillRepeatedly(Return(false));
    EXPECT_CALL(*AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_),
        AdjustNativeWindowSize(MAX_WIDTH, MAX_HEIGHT))
        .WillOnce(Return());

    pattern->SetRenderType(NodeRenderType::RENDER_TYPE_TEXTURE);
    auto flag = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config); // IsSurfaceValid=true
    EXPECT_TRUE(pattern->hasXComponentInit_);
    EXPECT_FALSE(flag);
}

/**
 * @tc.name: XComponentRenderTypeTest018
 * @tc.desc: Test XComponent ChangeRenderType
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, XComponentRenderTypeTest018, TestSize.Level1)
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

/**
 * @tc.name: XComponentOnAreaChangedInnerTest019
 * @tc.desc: Test XComponent OnAreaChangedInner.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, XComponentOnAreaChangedInnerTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set the testProperty and CreateXComponentNode
     *            case: type = XCOMPONENT_SURFACE_TYPE
     * @tc.expected: frameNode create successfully
     */
    std::string onLoadKey;
    std::string onDestroyKey;
    auto onLoad = [&onLoadKey](const std::string& /* xComponentId */) { onLoadKey = CHECK_KEY; };
    auto onDestroy = [&onDestroyKey]() { onDestroyKey = CHECK_KEY; };

    testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    testProperty.loadEvent = std::move(onLoad);
    testProperty.destroyEvent = std::move(onDestroy);
    auto frameNode = CreateXComponentNode(testProperty);
    EXPECT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::XCOMPONENT_ETS_TAG);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. call OnAreaChangedInner
     *            case: SystemProperties::GetExtSurfaceEnabled() == true
     * @tc.expected: call SetExtSurfaceBounds
     */
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    geometryNode->SetFrameSize(MAX_SIZE);
    geometryNode->SetContentSize(MAX_SIZE);

    EXPECT_CALL(*AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_),
                SetExtSurfaceBounds(0, 0, MAX_WIDTH, MAX_HEIGHT))
        .WillOnce(Return());
    SystemProperties::SetExtSurfaceEnabled(true);
    pattern->OnAreaChangedInner();
    SystemProperties::SetExtSurfaceEnabled(false);
}

/**
 * @tc.name: XComponentSetHistoryPointTest20
 * @tc.desc: Test SetHistoryPoint
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, XComponentSetHistoryPointTest20, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set type = XCOMPONENT_SURFACE_TYPE and call CreateXComponentNode
     * @tc.expected: xcomponent frameNode create successfully
     */
    testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    pattern->hasXComponentInit_ = true;

    /**
     * @tc.steps: step2. prepare point info
     */
    std::vector<TouchLocationInfo> pList {
        DragStartInfo(1),
        DragUpdateInfo(2),
        DragEndInfo(3),
        ClickInfo(4),
        PressInfo(5),
        LongPressInfo(6),
    };

    std::list<TouchLocationInfo> touchInfoList;

    for (auto&& item : pList) {
        item.SetLocalLocation(Offset(CHILD_OFFSET_WIDTH, CHILD_OFFSET_HEIGHT));
        item.SetScreenLocation(Offset(CHILD_OFFSET_WIDTH, CHILD_OFFSET_HEIGHT));
        item.SetTouchType(TouchType::PULL_DOWN);
        item.SetSize(XCOMPONENT_ID_LEN_MAX);
        item.SetForce(FORCE);
        item.SetTiltX(CHILD_OFFSET_WIDTH);
        item.SetTiltY(CHILD_OFFSET_HEIGHT);
        item.SetSourceTool(SourceTool::MOUSE);
        touchInfoList.push_back(item);
    }

    auto pVector = pattern->SetHistoryPoint(touchInfoList);

    /**
     * @tc.steps: step3. check
     */
    EXPECT_EQ(touchInfoList.size(), pVector.size());
    for (auto&& item : pVector) {
        EXPECT_EQ(item.x, CHILD_OFFSET_WIDTH);
        EXPECT_EQ(item.y, CHILD_OFFSET_HEIGHT);
        EXPECT_EQ(item.screenX, CHILD_OFFSET_WIDTH);
        EXPECT_EQ(item.screenY, CHILD_OFFSET_HEIGHT);
        EXPECT_EQ(item.type, static_cast<OH_NativeXComponent_TouchEventType>(TouchType::PULL_DOWN));
        EXPECT_EQ(item.size, XCOMPONENT_ID_LEN_MAX);
        EXPECT_EQ(item.force, FORCE);
        EXPECT_EQ(item.titlX, CHILD_OFFSET_WIDTH);
        EXPECT_EQ(item.titlY, CHILD_OFFSET_HEIGHT);
        EXPECT_EQ(item.sourceTool, static_cast<OH_NativeXComponent_TouchEvent_SourceTool>(SourceTool::MOUSE));
    }
}

/**
 * @tc.name: XComponentSetDetachEventTest021
 * @tc.desc: Test XComponent detachEvent event.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, XComponentSetDetachEventTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set the testProperty and CreateXComponentNode
     *            case: type = XCOMPONENT_SURFACE_TYPE
     * @tc.expected: frameNode create successfully
     */
    testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(testProperty);
    EXPECT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::XCOMPONENT_ETS_TAG);

    /**
     * @tc.steps: step2. call FireDetachEvent
     * @tc.expected: three checkKeys has changed
     */
    auto xComponentEventHub = frameNode->GetEventHub<XComponentEventHub>();
    ASSERT_TRUE(xComponentEventHub);

    bool detachFlage = false;
    auto detachCallback = [&detachFlage](const std::string& xcomponentId) {
        detachFlage = true;
    };
    xComponentEventHub->SetDetachEvent(std::move(detachCallback));

    xComponentEventHub->FireDetachEvent(XCOMPONENT_ID);
    ASSERT_TRUE(detachFlage);
}

/**
 * @tc.name: XComponentFrameCallbackTest022
 * @tc.desc: Test XComponent RegisterOnFrameCallback and UnregisterOnFrameCallback.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, XComponentFrameCallbackTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set the testProperty and CreateXComponentNode
     *            case: type = XCOMPONENT_SURFACE_TYPE
     * @tc.expected: frameNode create successfully
     */
    testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(testProperty);
    EXPECT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::XCOMPONENT_ETS_TAG);

    auto xComponentPattern = frameNode->GetPattern<XComponentPattern>();
    EXPECT_FALSE(xComponentPattern == nullptr);

    auto pair = xComponentPattern->GetNativeXComponent();
    auto weakNativeXComponent = pair.second;
    auto nativeXComponent = weakNativeXComponent.lock();
    auto nativeXComponentImpl = pair.first;
    EXPECT_TRUE(nativeXComponent);
    EXPECT_TRUE(nativeXComponentImpl);

    /**
     * @tc.steps: step2. call RegisterOnFrameCallback
     */
    auto frameCallback = [](OH_NativeXComponent* /* component */, uint64_t /* timestamp */,
                            uint64_t /* targetTimestamp */) {};
    nativeXComponent->RegisterOnFrameCallback(frameCallback);

    xComponentPattern->NativeXComponentInit();
    OH_NativeXComponent_ExpectedRateRange range = {0, 120, 90};
    nativeXComponent->SetExpectedFrameRateRange(&range);

    /**
     * @tc.steps: step3. call UnregisterOnFrameCallback
     */
    nativeXComponent->UnregisterOnFrameCallback();
}

/**
 * @tc.name: XComponentEventTest023
 * @tc.desc: Test XComponent RegisterOnCreate and RegisterOnDestroy register event.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, XComponentEventTest023, TestSize.Level1)
{
    std::string onLoadKey;
    std::string onDestroyKey;
    auto onLoad = [&onLoadKey](const std::string& /* xComponentId */) { onLoadKey = CHECK_KEY; };
    auto onDestroy = [&onDestroyKey]() { onDestroyKey = CHECK_KEY; };

    /**
     * @tc.steps: step1. set the testProperty and CreateXComponentNode
     *            case: type = XCOMPONENT_COMPONENT_TYPE_VALUE
     * @tc.expected: frameNode create successfully
     */
    testProperty.xcType = XCOMPONENT_COMPONENT_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(testProperty);
    EXPECT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::XCOMPONENT_ETS_TAG);

    /**
     * @tc.steps: step2. call RegisterOnCreate and RegisterOnDestroy register event.
     * */
    XComponentModelNG().RegisterOnCreate(frameNode, std::move(onLoad));
    XComponentModelNG().RegisterOnDestroy(frameNode, std::move(onDestroy));

    auto xComponentPattern = frameNode->GetPattern<XComponentPattern>();
    EXPECT_FALSE(xComponentPattern == nullptr);

    /**
     * @tc.steps: step3. call FireLoadEvent, FireDestroyEvent
     * @tc.expected: three checkKeys not changed
     */
    auto xComponentEventHub = frameNode->GetEventHub<XComponentEventHub>();
    ASSERT_TRUE(xComponentEventHub);
    xComponentEventHub->FireLoadEvent(XCOMPONENT_ID);
    xComponentEventHub->FireDestroyEvent();
    EXPECT_FALSE(onLoadKey == CHECK_KEY);
    EXPECT_FALSE(onDestroyKey == CHECK_KEY);

    // goto other branch
    XComponentModelNG::SetXComponentType(Referenced::RawPtr(frameNode), XCOMPONENT_SURFACE_TYPE_VALUE);

    /**
     * @tc.steps: step4. call RegisterOnCreate and RegisterOnDestroy register event.
     * */
    XComponentModelNG().RegisterOnCreate(frameNode, std::move(onLoad));
    XComponentModelNG().RegisterOnDestroy(frameNode, std::move(onDestroy));

    /**
     * @tc.steps: step5. call FireLoadEvent, FireDestroyEvent
     * @tc.expected: three checkKeys has changed
     */
    ASSERT_TRUE(xComponentEventHub);
    xComponentEventHub->FireLoadEvent(XCOMPONENT_ID);
    xComponentEventHub->FireDestroyEvent();
    EXPECT_EQ(onLoadKey, CHECK_KEY);
    EXPECT_EQ(onDestroyKey, CHECK_KEY);
}

/**
 * @tc.name: XComponentDetachCallbackTest024
 * @tc.desc: Test XComponent SetDetachCallback test.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, XComponentDetachCallbackTest024, TestSize.Level1)
{
    std::string onDetachKey;
    auto onDetach = [&onDetachKey](const std::string& /* xcomponentId */) { onDetachKey = CHECK_KEY; };

    /**
     * @tc.steps: step1. set the testProperty and CreateXComponentNode
     *            case: XCOMPONENT_SURFACE_TYPE_VALUE
     * @tc.expected: frameNode create successfully
     */
    auto xComponentController = std::make_shared<XComponentControllerNG>();
    XComponentModelNG xComponent;
    xComponent.Create(XCOMPONENT_ID, XCOMPONENT_NODE_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME, xComponentController);
    xComponent.SetSoPath(XCOMPONENT_SO_PATH);
    xComponent.SetDetachCallback(std::move(onDetach));

    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::XCOMPONENT_ETS_TAG);

    /**
     * @tc.steps: step2. call FireDetachEvent
     * @tc.expected: three checkKeys has changed
     */
    auto xComponentEventHub = frameNode->GetEventHub<XComponentEventHub>();
    ASSERT_TRUE(xComponentEventHub);
    xComponentEventHub->FireDetachEvent(XCOMPONENT_ID);
    EXPECT_FALSE(onDetachKey == CHECK_KEY);


    onDetachKey.clear();
    XComponentModelNG::SetXComponentType(Referenced::RawPtr(frameNode), XCOMPONENT_COMPONENT_TYPE_VALUE);
    xComponent.SetDetachCallback(std::move(onDetach));
    xComponentEventHub->FireDetachEvent(XCOMPONENT_ID);
    EXPECT_FALSE(onDetachKey == CHECK_KEY);

    onDetachKey.clear();
    XComponentModelNG::SetXComponentType(Referenced::RawPtr(frameNode), XCOMPONENT_SURFACE_TYPE_VALUE);
    xComponent.SetDetachCallback(std::move(onDetach));
    xComponentEventHub->FireDetachEvent(XCOMPONENT_ID);
    EXPECT_EQ(onDetachKey, CHECK_KEY);
}

/**
 * @tc.name: XComponentPropertyTest025
 * @tc.desc: Create XComponent, and test XComponent type, id, libraryName, soPath interface.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, XComponentPropertyTest025, TestSize.Level1)
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
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = AceType::DynamicCast<FrameNode>(xComponent.Create(nodeId, MAX_WIDTH, MAX_HEIGHT, XCOMPONENT_ID,
        XCOMPONENT_SURFACE_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME, xComponentController));

    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::XCOMPONENT_ETS_TAG);
    auto xComponentPattern = frameNode->GetPattern<XComponentPattern>();
    EXPECT_FALSE(xComponentPattern == nullptr);
    xComponentPattern->SetSoPath(XCOMPONENT_SO_PATH);
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
 * @tc.name: XComponentExtSurfaceCallbackClient026
 * @tc.desc: Create XComponentExtSurfaceCallbackClient, and test.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, XComponentExtSurfaceCallbackClient026, TestSize.Level1)
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
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = AceType::DynamicCast<FrameNode>(xComponent.Create(nodeId, MAX_WIDTH, MAX_HEIGHT, XCOMPONENT_ID,
        XCOMPONENT_SURFACE_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME, xComponentController));

    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::XCOMPONENT_ETS_TAG);
    auto xComponentPattern = frameNode->GetPattern<XComponentPattern>();
    EXPECT_FALSE(xComponentPattern == nullptr);

    /**
     * @tc.steps: step2. call FireDetachEvent
     * @tc.expected: three checkKeys has changed
     */
    auto xComponentEventHub = frameNode->GetEventHub<XComponentEventHub>();
    ASSERT_TRUE(xComponentEventHub);

    std::string surfaceInitFlage;
    auto surfaceInitCallback = [&surfaceInitFlage](const std::string&, const uint32_t, const bool) {
        surfaceInitFlage = CHECK_KEY;
    };
    xComponentEventHub->SetOnSurfaceInitEvent(std::move(surfaceInitCallback));

    /**
     * @tc.steps: step3. call ProcessSurfaceCreate
     */
    auto extSurfaceClient = Referenced::MakeRefPtr<XComponentExtSurfaceCallbackClient>(xComponentPattern);
    extSurfaceClient->ProcessSurfaceCreate();
    EXPECT_EQ(surfaceInitFlage, CHECK_KEY);

    /**
     * @tc.steps: step4. call ProcessSurfaceChange
     */
    EXPECT_CALL(*AceType::DynamicCast<MockRenderSurface>(xComponentPattern->renderSurface_),
        AdjustNativeWindowSize(MAX_WIDTH, MAX_HEIGHT))
        .WillOnce(Return());
    extSurfaceClient->ProcessSurfaceChange(MAX_WIDTH, MAX_HEIGHT);

    /**
     * @tc.steps: step5. call ProcessSurfaceChange
     */
    extSurfaceClient->ProcessSurfaceDestroy();

    // got other branch
    /**
     * @tc.steps: step6. call XComponentExtSurfaceCallbackClient func
     */
    auto extSurfaceClient2 = Referenced::MakeRefPtr<XComponentExtSurfaceCallbackClient>(nullptr);
    extSurfaceClient2->ProcessSurfaceCreate();
    extSurfaceClient2->ProcessSurfaceChange(MAX_WIDTH, MAX_HEIGHT);
    extSurfaceClient2->ProcessSurfaceDestroy();
}

/**
 * @tc.name: XComponentSurfaceTest
 * @tc.desc: Test SurfaceHide/SurfaceShow callback
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, XComponentSurfaceTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set type = XCOMPONENT_SURFACE_TYPE and call CreateXComponentNode
     * @tc.expected: xcomponent frameNode create successfully
     */
    testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    /**
     * @tc.steps: step2. create nativeXComponent instance
     * @tc.expected: nativeXComponent instance create successfully
     */
    auto host = pattern->GetHost();
    ASSERT_TRUE(host);
    auto pair = pattern->GetNativeXComponent();
    auto weakNativeXComponent = pair.second;
    auto nativeXComponent = weakNativeXComponent.lock();
    auto nativeXComponentImpl = pair.first;
    ASSERT_TRUE(nativeXComponent);
    ASSERT_TRUE(nativeXComponentImpl);
    pattern->hasXComponentInit_ = true;


    /**
     * @tc.steps: step3. call surfaceHide and surfaceShow event without register callbacks
     * @tc.expected: no error happens and g_surfaceShowNum remains the same
     */
    pattern->OnWindowHide();
    EXPECT_EQ(g_surfaceShowNum, 1);
    pattern->OnWindowShow();
    EXPECT_EQ(g_surfaceShowNum, 1);

    /**
     * @tc.steps: step4. register surfaceHide/Show event for nativeXComponent instance and trigger callback
     * @tc.expected: callback is triggered successfully
     */
    nativeXComponent->RegisterSurfaceShowCallback(
        [](OH_NativeXComponent* /* nativeXComponent */, void* /* window */) { g_surfaceShowNum += 1; });
    nativeXComponent->RegisterSurfaceHideCallback(
        [](OH_NativeXComponent* /* nativeXComponent */, void* /* window */) { g_surfaceShowNum -= 1; });
    EXPECT_CALL(*AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_), releaseSurfaceBuffers())
        .WillOnce(Return());
    pattern->OnWindowHide();
    pattern->OnWindowHide(); // test when hasReleasedSurface_ is not satisfied
    EXPECT_EQ(g_surfaceShowNum, 0);
    pattern->OnWindowShow();
    pattern->OnWindowShow(); // test when hasReleasedSurface_ is not satisfied
    EXPECT_EQ(g_surfaceShowNum, 1);

    /**
     * @tc.steps: step5. call OnWindowHide and OnWindowShoww when the pre-judgment of the function is not satisfied
     * @tc.expected: callback will be triggered only once
     */
    bool initConditions[2] = { true, false };
    bool typeConditions[2] = { true, false };
    EXPECT_CALL(*AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_), releaseSurfaceBuffers())
        .WillOnce(Return());
    for (bool initCondition : initConditions) {
        for (bool typeCondition : typeConditions) {
            pattern->hasXComponentInit_ = initCondition;
            pattern->type_ = typeCondition ? XCOMPONENT_TEXTURE_TYPE_VALUE : XCOMPONENT_COMPONENT_TYPE_VALUE;
            pattern->OnWindowHide();
            if (initCondition && typeCondition) {
                EXPECT_EQ(g_surfaceShowNum, 0);
            }
            pattern->OnWindowShow();
            EXPECT_EQ(g_surfaceShowNum, 1);
        }
    }
}

/**
 * @tc.name: XComponentControllerTest
 * @tc.desc: Test XComponentController's interface
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, XComponentControllerTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set type = XCOMPONENT_SURFACE_TYPE_VALUE and call CreateXComponentNode
     * @tc.expected: xcomponent frameNode create successfully
     */
    testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(testProperty);
    EXPECT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::XCOMPONENT_ETS_TAG);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    pattern->hasXComponentInit_ = true;
    EXPECT_EQ(pattern->type_, XCOMPONENT_SURFACE_TYPE_VALUE);
    EXPECT_TRUE(pattern->IsAtomicNode());
    auto renderContext = AceType::MakeRefPtr<MockRenderContext>();
    pattern->handlingSurfaceRenderContext_ = renderContext;

    /**
     * @tc.steps: step2. call XcomponentController's interface releative to SetSurfaceRect
     * @tc.expected: handlingSurfaceRenderContext_->SetBounds(SURFACE_OFFSETX, SURFACE_OFFSETY,
     *               SURFACE_WIDTH, SURFACE_HEIGHT) is called
     */
    auto xcomponentController = pattern->xcomponentController_;
    EXPECT_TRUE(xcomponentController);
    pattern->drawSize_ = MAX_SIZE;
    xcomponentController->SetIdealSurfaceWidth(SURFACE_WIDTH);
    xcomponentController->SetIdealSurfaceHeight(SURFACE_HEIGHT);
    xcomponentController->SetIdealSurfaceOffsetX(SURFACE_OFFSETX);
    xcomponentController->SetIdealSurfaceOffsetY(SURFACE_OFFSETY);
    EXPECT_CALL(*AceType::DynamicCast<MockRenderContext>(pattern->handlingSurfaceRenderContext_),
        SetBounds(SURFACE_OFFSETX, SURFACE_OFFSETY, SURFACE_WIDTH, SURFACE_HEIGHT))
        .WillOnce(Return());
    xcomponentController->UpdateSurfaceBounds();

    /**
     * @tc.steps: step3. call XcomponentController's interface releative to GetSurfaceRect
     * @tc.expected: the rect get from GetSurfaceRect equals the rect set by SetSurfaceRect
     */
    auto surfaceWidth = 0.0f;
    auto surfaceHeight = 0.0f;
    auto surfaceOffsetX = 0.0f;
    auto surfaceOffsetY = 0.0f;
    xcomponentController->GetSurfaceSize(surfaceWidth, surfaceHeight);
    xcomponentController->GetLocalLocation(surfaceOffsetX, surfaceOffsetY);
    EXPECT_EQ(surfaceOffsetX, SURFACE_OFFSETX);
    EXPECT_EQ(surfaceOffsetY, SURFACE_OFFSETY);
    EXPECT_EQ(surfaceWidth, SURFACE_WIDTH);
    EXPECT_EQ(surfaceHeight, SURFACE_HEIGHT);

    /**
     * @tc.steps: step4. call XcomponentController's ClearIdealSurfaceOffset
     * @tc.expected: handlingSurfaceRenderContext_->SetBounds(newSurfaceOffsetX, newSurfaceOffsetY,
     *               SURFACE_WIDTH, SURFACE_HEIGHT) is called
     */
    auto newSurfaceOffsetX = (MAX_WIDTH - SURFACE_WIDTH) / 2.0f;
    auto newSurfaceOffsetY = (MAX_HEIGHT - SURFACE_HEIGHT) / 2.0f;
    xcomponentController->ClearIdealSurfaceOffset(true);
    xcomponentController->ClearIdealSurfaceOffset(false);
    EXPECT_CALL(*AceType::DynamicCast<MockRenderContext>(pattern->handlingSurfaceRenderContext_),
        SetBounds(newSurfaceOffsetX, newSurfaceOffsetY, SURFACE_WIDTH, SURFACE_HEIGHT))
        .WillOnce(Return());
    xcomponentController->UpdateSurfaceBounds();
}

/**
 * @tc.name: XComponentAxisEventTest012
 * @tc.desc: Test AxisEvent
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, XComponentAxisEventTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set type = XCOMPONENT_SURFACE_TYPE and call CreateXComponentNode
     * @tc.expected: xcomponent frameNode create successfully
     */
    testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. create nativeXComponent instance
     * @tc.expected: focusHub & nativeXComponent instance create successfully
     */
    auto pair = pattern->GetNativeXComponent();
    auto weakNativeXComponent = pair.second;
    auto nativeXComponent = weakNativeXComponent.lock();
    auto nativeXComponentImpl = pair.first;
    ASSERT_TRUE(nativeXComponent);
    ASSERT_TRUE(nativeXComponentImpl);

    /**
     * @tc.steps: step3. register axis event for nativeXComponent instance
     */
    auto callback = [](OH_NativeXComponent* /* nativeXComponent */, ArkUI_UIInputEvent* event,
                        ArkUI_UIInputEvent_Type type) { isAxis = true; };
    nativeXComponent->RegisterUIAxisEventCallback(callback);

    /**
     * @tc.steps: step4. call HandleAxisEvent
     */
    AxisInfo event;
    pattern->HandleAxisEvent(event);
    EXPECT_TRUE(isAxis);
}

/**
 * @tc.name: XComponentSourceTypeTest
 * @tc.desc: Test SourceType
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, XComponentSourceTypeTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set type = XCOMPONENT_SURFACE_TYPE and call CreateXComponentNode
     * @tc.expected: xcomponent frameNode create successfully
     */
    testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. call HandleTouchEvent
     *            case: set source type
     * @tc.expected: sourceType fit
     */
    TouchEventInfo touchEventInfoSourceType("onTouch");
    TouchLocationInfo locationInfoSourceType(0);
    pattern->GetNativeXComponent();
    touchEventInfoSourceType.AddChangedTouchLocationInfo(std::move(locationInfoSourceType));
    std::vector<SourceType> sourceTypes { SourceType::NONE, SourceType::MOUSE, SourceType::TOUCH, SourceType::TOUCH_PAD,
        SourceType::KEYBOARD };
    for (SourceType& sourceType : sourceTypes) {
        touchEventInfoSourceType.SetSourceDevice(sourceType);
        pattern->HandleTouchEvent(touchEventInfoSourceType);
        EXPECT_EQ(pattern->nativeXComponentImpl_->curSourceType_.first, 0);
        EXPECT_EQ(static_cast<int>(pattern->nativeXComponentImpl_->curSourceType_.second),
            static_cast<int>(ConvertNativeXComponentEventSourceType(sourceType)));
    }
}

/**
 * @tc.name: XComponentImageAnalyzerTest
 * @tc.desc: Test Enable Image Analyzer
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, XComponentImageAnalyzerTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set type = XCOMPONENT_SURFACE_TYPE and call CreateXComponentNode
     * @tc.expected: xcomponent frameNode create successfully
     */
    testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. call EnableImageAnalyzer
     * @tc.expected: IsSupportImageAnalyzerFeature() return right value
     */
    pattern->EnableAnalyzer(true);
    EXPECT_TRUE(pattern->isEnableAnalyzer_);

    if (ImageAnalyzerMgr::GetInstance()->IsImageAnalyzerSupported()) {
        EXPECT_TRUE(pattern->IsSupportImageAnalyzerFeature());
    } else {
        EXPECT_FALSE(pattern->IsSupportImageAnalyzerFeature());
    }

    pattern->imageAnalyzerManager_ = nullptr;
    EXPECT_FALSE(pattern->IsSupportImageAnalyzerFeature());
}

/**
 * @tc.name: XComponentSurfaceLifeCycleCallback
 * @tc.desc: Test XComponentController's surface life cycle callback
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, XComponentSurfaceLifeCycleCallback, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set surface life cycle callback and create XComponent
     * @tc.expected: xcomponent frameNode create successfully
     */
    testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    std::string onSurfaceCreatedSurfaceId;
    std::string onSurfaceChangedSurfaceId;
    std::string onSurfaceDestroyedSurfaceId;
    auto onSurfaceCreated = [&onSurfaceCreatedSurfaceId](
                                const std::string& surfaceId) { onSurfaceCreatedSurfaceId = surfaceId; };
    auto onSurfaceChanged = [&onSurfaceChangedSurfaceId](const std::string& surfaceId, const RectF& /* rect */) {
        onSurfaceChangedSurfaceId = surfaceId;
    };
    auto onSurfaceDestroyed = [&onSurfaceDestroyedSurfaceId](
                                  const std::string& surfaceId) { onSurfaceDestroyedSurfaceId = surfaceId; };
    testProperty.surfaceCreatedEvent = std::move(onSurfaceCreated);
    testProperty.surfaceChangedEvent = std::move(onSurfaceChanged);
    testProperty.surfaceDestroyedEvent = std::move(onSurfaceDestroyed);
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    pattern->surfaceId_ = SURFACE_ID;

    /**
     * @tc.steps: step2. call onDirtyLayoutWrapper
     * @tc.expected: onSurfaceCreated & onSurfaceChanged has called
     */
    DirtySwapConfig config;
    auto xComponentLayoutAlgorithm = AceType::MakeRefPtr<XComponentLayoutAlgorithm>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(MAX_SIZE);
    geometryNode->SetContentSize(MAX_SIZE);
    auto layoutProperty = frameNode->GetLayoutProperty<XComponentLayoutProperty>();
    EXPECT_TRUE(layoutProperty);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(xComponentLayoutAlgorithm, false);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    EXPECT_CALL(*AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_), IsSurfaceValid())
        .WillOnce(Return(true));
    EXPECT_CALL(*AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_),
        AdjustNativeWindowSize(MAX_WIDTH, MAX_HEIGHT))
        .WillOnce(Return());
    EXPECT_CALL(*AceType::DynamicCast<MockRenderContext>(pattern->handlingSurfaceRenderContext_),
        SetBounds(0, 0, MAX_WIDTH, MAX_HEIGHT))
        .WillOnce(Return());
    pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(onSurfaceCreatedSurfaceId, SURFACE_ID);
    EXPECT_EQ(onSurfaceChangedSurfaceId, SURFACE_ID);

    /**
     * @tc.steps: step3. call OnDetachFromFrameNode
     * @tc.expected: onSurfaceDestroyed has called
     */
    pattern->OnDetachFromFrameNode(AceType::RawPtr(frameNode));
    EXPECT_EQ(onSurfaceDestroyedSurfaceId, SURFACE_ID);
}
} // namespace OHOS::Ace::NG
