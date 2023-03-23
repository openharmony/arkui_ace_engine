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

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
struct TestProperty {
    std::optional<std::string> xcId = std::nullopt;
    std::optional<std::string> xcType = std::nullopt;
    std::optional<std::string> libraryName = std::nullopt;
    std::optional<std::string> soPath = std::nullopt;
    std::optional<LoadEvent> loadEvent = std::nullopt;
    std::optional<DestroyEvent> destroyEvent = std::nullopt;
};
namespace {
const std::string CHECK_KEY = "HI";
const std::string XCOMPONENT_ID = "xcomponent";
const std::string XCOMPONENT_SURFACE_TYPE = "surface";
const std::string XCOMPONENT_COMPONENT_TYPE = "component";
const std::string XCOMPONENT_LIBRARY_NAME = "native_render";
const std::string XCOMPONENT_SO_PATH = "com.example.xcomponentmultihap/entry";
const XComponentType XCOMPONENT_SURFACE_TYPE_VALUE = XComponentType::SURFACE;
const XComponentType XCOMPONENT_COMPONENT_TYPE_VALUE = XComponentType::COMPONENT;
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
} // namespace

class XComponentPropertyTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite() {};

protected:
    static RefPtr<FrameNode> CreateXComponentNode(TestProperty& testProperty);
};

void XComponentPropertyTestNg::SetUpTestSuite()
{
    testProperty.xcId = XCOMPONENT_ID;
    testProperty.libraryName = XCOMPONENT_LIBRARY_NAME;
    testProperty.soPath = XCOMPONENT_SO_PATH;
}

RefPtr<FrameNode> XComponentPropertyTestNg::CreateXComponentNode(TestProperty& testProperty)
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
HWTEST_F(XComponentPropertyTestNg, XComponentPropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a XComponentModelNG
     */
    const RefPtr<XComponentController> xComponentController;
    XComponentModelNG xComponent;

    /**
     * @tc.steps: step2. call Create and SetSoPath
     *            case: type = XCOMPONENT_SURFACE_TYPE
     * @tc.expected: step2. the properties are expected
     */
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
    EXPECT_TRUE(xComponentPattern->IsAtomicNode()); // if xcomponentType = "surface"
    EXPECT_EQ(
        xComponentLayoutProperty->GetXComponentType().value_or(XComponentType::SURFACE), XCOMPONENT_SURFACE_TYPE_VALUE);

    /**
     * @tc.steps: step3. call Create and SetSoPath
     *            case: type = XCOMPONENT_COMPONENT_TYPE
     * @tc.expected: step3. the properties are expected
     */
    const RefPtr<XComponentController> xComponentController2;
    XComponentModelNG xComponent2;
    xComponent2.Create(XCOMPONENT_ID, XCOMPONENT_COMPONENT_TYPE, XCOMPONENT_LIBRARY_NAME, xComponentController);
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
HWTEST_F(XComponentPropertyTestNg, XComponentEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set the testProperty and CreateXComponentNode
     *            case: type = XCOMPONENT_SURFACE_TYPE
     * @tc.expected: step1. frameNode create successfully
     */
    std::string onLoadKey;
    std::string onDestroyKey;
    auto onLoad = [&onLoadKey](const std::string& /* xComponentId */) { onLoadKey = CHECK_KEY; };
    auto onDestroy = [&onDestroyKey]() { onDestroyKey = CHECK_KEY; };

    testProperty.xcType = XCOMPONENT_SURFACE_TYPE;
    testProperty.loadEvent = std::move(onLoad);
    testProperty.destroyEvent = std::move(onDestroy);
    auto frameNode = CreateXComponentNode(testProperty);
    EXPECT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::XCOMPONENT_ETS_TAG);

    /**
     * @tc.steps: step2. call FireLoadEvent, FireDestroyEvent
     * @tc.expected: step2. three checkKeys has changed
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
     * @tc.expected: step3. three checkKeys has no change
     */

    auto onLoad2 = [&onLoadKey](const std::string& /* xComponentId */) { onLoadKey = ""; };
    auto onDestroy2 = [&onDestroyKey]() { onDestroyKey = ""; };
    testProperty.xcType = XCOMPONENT_COMPONENT_TYPE;
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

/**
 * @tc.name: XComponentLayoutAlgorithmTest006
 * @tc.desc: Test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPropertyTestNg, XComponentLayoutAlgorithmTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set type = XCOMPONENT_SURFACE_TYPE and call CreateXComponentNode
     * @tc.expected: step1. frameNode create successfully
     */
    testProperty.xcType = XCOMPONENT_SURFACE_TYPE;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap
     *            case: hasXComponentInit_ = false
     * @tc.expected: step2. hasXComponentInit_ = true
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
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, layoutProperty);
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(xComponentLayoutAlgorithm, false);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    EXPECT_FALSE(pattern->hasXComponentInit_);
    EXPECT_CALL(*(AceType::RawPtr(AceType::DynamicCast<MockRenderContext>(pattern->renderContextForSurface_))),
        SetBounds(0.0f, 0.0f, MAX_WIDTH, MAX_HEIGHT))
        .WillOnce(Return());
    EXPECT_CALL(*(AceType::RawPtr(AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_))), IsSurfaceValid())
        .WillOnce(Return(true))
        .WillOnce(Return(true))
        .WillOnce(Return(false))
        .WillOnce(Return(false));
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
     * @tc.expected: step3. OnDirtyLayoutWrapperSwap return false
     */
    bool frameOffsetChanges[2] = { false, true };
    bool contentOffsetChanges[2] = { false, true };
    EXPECT_CALL(*(AceType::RawPtr(AceType::DynamicCast<MockRenderContext>(pattern->renderContextForSurface_))),
        SetBounds(0.0f, 0.0f, MAX_WIDTH, MAX_HEIGHT))
        .Times(4);
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
     *            case: type="component", config.skipMeasure = true, dirty->SkipMeasureContent() = true
     * @tc.expected: step4. OnDirtyLayoutWrapperSwap return false
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
HWTEST_F(XComponentPropertyTestNg, XComponentMouseEventTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set type = XCOMPONENT_SURFACE_TYPE and call CreateXComponentNode
     * @tc.expected: step1. xcomponent frameNode create successfully
     */
    testProperty.xcType = XCOMPONENT_SURFACE_TYPE;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

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
     * @tc.expected: step3. no error happens
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
HWTEST_F(XComponentPropertyTestNg, XComponentTouchEventTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set type = XCOMPONENT_SURFACE_TYPE and call CreateXComponentNode
     * @tc.expected: step1. xcomponent frameNode create successfully
     */
    testProperty.xcType = XCOMPONENT_SURFACE_TYPE;
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
     * @tc.expected: step3. pattern->touchEventPoint_.numPoints not change
     */
    TouchEventInfo touchEventInfoEmpty("onTouch");
    uint32_t numPoints = pattern->touchEventPoint_.numPoints;
    pattern->HandleTouchEvent(touchEventInfoEmpty);
    EXPECT_EQ(pattern->touchEventPoint_.numPoints, numPoints);

    /**
     * @tc.steps: step4. call HandleTouchEvent
     *            case: different touchType
     * @tc.expected: step4. touchType fit
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
     * @tc.expected: step5. sourceType fit
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
} // namespace OHOS::Ace::NG
