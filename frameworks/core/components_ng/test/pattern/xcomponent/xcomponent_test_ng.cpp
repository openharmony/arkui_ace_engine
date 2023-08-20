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
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_layout_algorithm.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_model_ng.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/test/mock/render/mock_render_context.h"
#include "core/components_ng/test/mock/render/mock_render_surface.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

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
};
namespace {
const std::string CHECK_KEY = "HI";
const std::string XCOMPONENT_ID = "xcomponent";
const std::string XCOMPONENT_LIBRARY_NAME = "native_render";
const std::string XCOMPONENT_SO_PATH = "com.example.xcomponentmultihap/entry";
constexpr XComponentType XCOMPONENT_SURFACE_TYPE_VALUE = XComponentType::SURFACE;
constexpr XComponentType XCOMPONENT_COMPONENT_TYPE_VALUE = XComponentType::COMPONENT;
constexpr XComponentType XCOMPONENT_TEXTURE_TYPE_VALUE = XComponentType::TEXTURE;
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
bool isFocus = false;

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
    MockPipelineBase::SetUp();
    testProperty.xcId = XCOMPONENT_ID;
    testProperty.libraryName = XCOMPONENT_LIBRARY_NAME;
    testProperty.soPath = XCOMPONENT_SO_PATH;
}

void XComponentTestNg::TearDownTestSuite()
{
    MockPipelineBase::TearDown();
}

RefPtr<FrameNode> XComponentTestNg::CreateXComponentNode(TestProperty& testProperty)
{
    auto xcId = testProperty.xcId.value();
    auto xcType = testProperty.xcType.value();
    auto libraryName = testProperty.libraryName.value();
    auto xcomponentController = AceType::MakeRefPtr<XComponentController>();
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
    const RefPtr<XComponentController> xComponentController;
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
    const RefPtr<XComponentController> xComponentController2;
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
    RefPtr<XComponentController> const xComponentController;
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
    RefPtr<XComponentController> const xComponentController;
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
    RefPtr<XComponentController> const xComponentController;
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

    auto contentSize =  xComponentLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper);
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
    EXPECT_CALL(*AceType::DynamicCast<MockRenderContext>(pattern->renderContextForSurface_),
        SetBounds(0.0f, 0.0f, MAX_WIDTH, MAX_HEIGHT))
        .WillOnce(Return());
    EXPECT_CALL(*AceType::DynamicCast<MockRenderContext>(frameNode->GetRenderContext()),
        AddChild(pattern->renderContextForSurface_, 0))
        .WillOnce(Return());
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
    EXPECT_CALL(*AceType::DynamicCast<MockRenderContext>(pattern->renderContextForSurface_),
        SetBounds(0.0f, 0.0f, MAX_WIDTH, MAX_HEIGHT))
        .Times(4);
    EXPECT_CALL(*AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_),
        AdjustNativeWindowSize(MAX_WIDTH, MAX_HEIGHT))
        .WillOnce(Return());
    pattern->type_ = XCOMPONENT_SURFACE_TYPE_VALUE;
    for (bool frameOffsetChange : frameOffsetChanges) {
        for (bool contentOffsetChange : contentOffsetChanges) {
            config.frameOffsetChange = frameOffsetChange;
            config.contentOffsetChange = contentOffsetChange;
            config.contentSizeChange = frameOffsetChange && contentOffsetChange;
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
     *            case: different sourceType
     * @tc.expected: sourceType fit
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
} // namespace OHOS::Ace::NG
