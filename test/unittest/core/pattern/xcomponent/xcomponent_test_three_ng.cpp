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

#include <cstddef>
#include <optional>
#include <unistd.h>
#include <vector>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_image_analyzer_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/render/mock_render_surface.h"
#include "test/mock/core/rosen/testing_canvas_utils.h"
#include "test/mock/core/manager/mock_display_manager.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/common/ai/image_analyzer_mgr.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_controller_ng.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_layout_algorithm.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_model_ng.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern_v2.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_surface_holder.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_inner_surface_controller.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/touch_event.h"
#include "frameworks/core/gestures/press_recognizer.h"
#include "frameworks/core/components_ng/pattern/node_container/node_container_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_ext_surface_callback_client.h"
#include "frameworks/core/components_ng/pattern/node_container/node_container_pattern.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_accessibility_child_tree_callback.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_inner_surface_controller.h"

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
const float MAX_WIDTH = 400.0f;
const float MAX_HEIGHT = 400.0f;
const SizeF MAX_SIZE(MAX_WIDTH, MAX_HEIGHT);
TestProperty g_testProperty;
const float SURFACE_WIDTH = 250.0f;
const float SURFACE_HEIGHT = 150.0f;
constexpr uint32_t SURFACE_WIDTH_SIZE = 200;
constexpr uint32_t SURFACE_HEIGHT_SIZE = 250;
constexpr float OFFSET_X = 10;
constexpr float OFFSET_Y = 10;
bool g_isAxis = false;
bool g_isLock = true;
const RenderFit g_renderFitCases[] = {
    RenderFit::CENTER,
    RenderFit::TOP,
    RenderFit::BOTTOM,
    RenderFit::LEFT,
    RenderFit::RIGHT,
    RenderFit::TOP_LEFT,
    RenderFit::TOP_RIGHT,
    RenderFit::BOTTOM_LEFT,
    RenderFit::BOTTOM_RIGHT,
    RenderFit::RESIZE_FILL,
    RenderFit::RESIZE_CONTAIN,
    RenderFit::RESIZE_CONTAIN_TOP_LEFT,
    RenderFit::RESIZE_CONTAIN_BOTTOM_RIGHT,
    RenderFit::RESIZE_COVER,
    RenderFit::RESIZE_COVER_TOP_LEFT,
    RenderFit::RESIZE_COVER_BOTTOM_RIGHT,
};
const bool g_isEnableNewVersionRenderFitCases[] = {true, false};
const std::string INVALID_SURFACE_ID = "null";
const int NUM_SIXTEEN = 16;
const int NUM_TWO = 2;
const float SURFACE_OFFSETX = 10.0f;
const float SURFACE_OFFSETY = 20.0f;
int g_surfaceShowNum = 1;
const std::string NODE_ID_STRING = "-1";

class XComponentMockRenderContext : public RenderContext {
    void SetRenderFit(RenderFit renderFit) override
    {
        propRenderFit_ = renderFit;
    }
};

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

class XComponentTestThreeNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void TearDown() override
    {
        g_testProperty.loadEvent = std::nullopt;
        g_testProperty.destroyEvent = std::nullopt;
        g_testProperty.surfaceCreatedEvent = std::nullopt;
        g_testProperty.surfaceChangedEvent = std::nullopt;
        g_testProperty.surfaceDestroyedEvent = std::nullopt;
        g_isAxis = false;
        g_isLock = true;
    }
protected:
    static RefPtr<FrameNode> CreateXComponentNode(TestProperty& testProperty);
};

void XComponentTestThreeNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    g_testProperty.xcId = XCOMPONENT_ID;
    g_testProperty.libraryName = XCOMPONENT_LIBRARY_NAME;
    g_testProperty.soPath = XCOMPONENT_SO_PATH;
}

void XComponentTestThreeNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> XComponentTestThreeNg::CreateXComponentNode(TestProperty& testProperty)
{
    auto xcId = testProperty.xcId;
    auto xcType = testProperty.xcType.value();
    auto libraryName = testProperty.libraryName;
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
 * @tc.name: XComponentExtSurfaceCallbackClient026
 * @tc.desc: Create XComponentExtSurfaceCallbackClient, and test.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestThreeNg, XComponentExtSurfaceCallbackClient026, TestSize.Level1)
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
HWTEST_F(XComponentTestThreeNg, XComponentSurfaceTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set type = XCOMPONENT_SURFACE_TYPE and call CreateXComponentNode
     * @tc.expected: xcomponent frameNode create successfully
     */
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
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
    EXPECT_CALL(*AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_), ReleaseSurfaceBuffers())
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
    EXPECT_CALL(*AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_), ReleaseSurfaceBuffers())
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
HWTEST_F(XComponentTestThreeNg, XComponentControllerTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set type = XCOMPONENT_SURFACE_TYPE_VALUE and call CreateXComponentNode
     * @tc.expected: xcomponent frameNode create successfully
     */
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
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
    xcomponentController->GetSurfaceOffset(surfaceOffsetX, surfaceOffsetY);
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
    /**
     * @tc.steps: step5. call XcomponentController's interface relative to SetSurfaceRotation
     * @tc.expected: handlingSurfaceRenderContext_->SetSurfaceRotation(g_isLock) is called
     */
    EXPECT_CALL(
        *AceType::DynamicCast<MockRenderContext>(pattern->handlingSurfaceRenderContext_), SetSurfaceRotation(g_isLock))
        .WillOnce(Return());
    xcomponentController->SetSurfaceRotation(g_isLock);
    /**
     * @tc.steps: step6. call XcomponentController's interface relative to GetSurfaceRotation
     * @tc.expected: the lock status get from GetSurfaceRotation equals the lock status set by SetSurfaceRotation
     */
    auto lock = xcomponentController->GetSurfaceRotation();
    EXPECT_EQ(lock, g_isLock);
}

/**
 * @tc.name: XComponentAxisEventTest012
 * @tc.desc: Test AxisEvent
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestThreeNg, XComponentAxisEventTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set type = XCOMPONENT_SURFACE_TYPE and call CreateXComponentNode
     * @tc.expected: xcomponent frameNode create successfully
     */
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
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
                        ArkUI_UIInputEvent_Type type) { g_isAxis = true; };
    nativeXComponent->RegisterUIAxisEventCallback(callback);

    /**
     * @tc.steps: step4. call HandleAxisEvent
     */
    AxisInfo event;
    pattern->HandleAxisEvent(event);
    EXPECT_TRUE(g_isAxis);
}

/**
 * @tc.name: XComponentSourceTypeTest
 * @tc.desc: Test SourceType
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestThreeNg, XComponentSourceTypeTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set type = XCOMPONENT_SURFACE_TYPE and call CreateXComponentNode
     * @tc.expected: xcomponent frameNode create successfully
     */
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
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
 * @tc.name: XComponentSurfaceLifeCycleCallback
 * @tc.desc: Test XComponentController's surface life cycle callback
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestThreeNg, XComponentSurfaceLifeCycleCallback, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set surface life cycle callback, set id&libraryname to null and create XComponent
     * @tc.expected: xcomponent frameNode create successfully
     */
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    g_testProperty.xcId = std::nullopt;
    g_testProperty.libraryName = std::nullopt;
    std::string onSurfaceCreatedSurfaceId = "";
    std::string onSurfaceChangedSurfaceId = "";
    std::string onSurfaceDestroyedSurfaceId = "";
    auto onSurfaceCreated = [&onSurfaceCreatedSurfaceId](const std::string& surfaceId, const std::string& xcId) {
        onSurfaceCreatedSurfaceId = surfaceId;
    };
    auto onSurfaceChanged = [&onSurfaceChangedSurfaceId](const std::string& surfaceId, const RectF& /* rect */) {
        onSurfaceChangedSurfaceId = surfaceId;
    };
    auto onSurfaceDestroyed = [&onSurfaceDestroyedSurfaceId](const std::string& surfaceId, const std::string& xcId) {
        onSurfaceDestroyedSurfaceId = surfaceId;
    };
    g_testProperty.surfaceCreatedEvent = std::move(onSurfaceCreated);
    g_testProperty.surfaceChangedEvent = std::move(onSurfaceChanged);
    g_testProperty.surfaceDestroyedEvent = std::move(onSurfaceDestroyed);
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto xComponentEventHub = frameNode->GetEventHub<XComponentEventHub>();
    ASSERT_TRUE(xComponentEventHub);
    EXPECT_FALSE(xComponentEventHub->surfaceInitEvent_);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    pattern->surfaceId_ = SURFACE_ID;
    /**
     * @tc.steps: step2. call BeforeSyncGeometryProperties
     * @tc.expected: onSurfaceCreated & onSurfaceChanged has called and nativeXcomponent will not be created
     */
    DirtySwapConfig config;
    auto xComponentLayoutAlgorithm = AceType::MakeRefPtr<XComponentLayoutAlgorithm>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(MAX_SIZE);
    geometryNode->SetContentSize(MAX_SIZE);
    frameNode->geometryNode_ = geometryNode;
    EXPECT_CALL(*AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_), IsSurfaceValid())
        .WillOnce(Return(true));
    EXPECT_CALL(*AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_),
        AdjustNativeWindowSize(MAX_WIDTH, MAX_HEIGHT))
        .WillOnce(Return());
    EXPECT_CALL(*AceType::DynamicCast<MockRenderContext>(pattern->handlingSurfaceRenderContext_),
        SetBounds(0, 0, MAX_WIDTH, MAX_HEIGHT))
        .WillOnce(Return());
    pattern->BeforeSyncGeometryProperties(config);
    EXPECT_STREQ(SURFACE_ID.c_str(), onSurfaceCreatedSurfaceId.c_str());
    EXPECT_STREQ(SURFACE_ID.c_str(), onSurfaceChangedSurfaceId.c_str());
    EXPECT_FALSE(pattern->nativeXComponent_);
    EXPECT_FALSE(pattern->nativeXComponentImpl_);
    /**
     * @tc.steps: step3. call OnDetachFromFrameNode
     * @tc.expected: onSurfaceDestroyed has called
     */
    pattern->OnDetachFromFrameNode(AceType::RawPtr(frameNode));
    EXPECT_STREQ(SURFACE_ID.c_str(), onSurfaceDestroyedSurfaceId.c_str());
}

/**
 * @tc.name: SetAndGetRenderFitBySurfaceIdTest
 * @tc.desc: Test innerAPI SetRenderFitBySurfaceId and GetRenderFitBySurfaceId
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestThreeNg, SetAndGetRenderFitBySurfaceIdTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create xcomponent pattern
     * @tc.expected: xcomponent pattern created
     */
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    g_testProperty.xcId = std::nullopt;
    g_testProperty.libraryName = std::nullopt;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    pattern->surfaceId_ = SURFACE_ID;
    pattern->initialSurfaceId_ = SURFACE_ID;
    pattern->SetScreenId(0U);
    EXPECT_EQ(pattern->surfaceId_, "");
    /**
     * @tc.steps: step2. set and get renderFit mode with valid surfaceId and valid renderFit number
     * @tc.expected: the return value equals 0 and get expected renderFit number
     */
    int32_t code;
    pattern->renderContextForSurface_ = AceType::MakeRefPtr<XComponentMockRenderContext>();
    pattern->RegisterNode();
    for (int i = 0; i < NUM_SIXTEEN; ++i) {
        for (int j = 0; j < NUM_TWO; ++j) {
            code = XComponentInnerSurfaceController::SetRenderFitBySurfaceId(SURFACE_ID, g_renderFitCases[i],
                g_isEnableNewVersionRenderFitCases[j]);
            EXPECT_EQ(code, 0);
            int32_t renderFitNumber = 0;
            bool isEnable = false;
            code = XComponentInnerSurfaceController::GetRenderFitBySurfaceId(SURFACE_ID, renderFitNumber, isEnable);
            EXPECT_EQ(code, 0);
            EXPECT_EQ(renderFitNumber, static_cast<int32_t>(g_renderFitCases[i]));
        }
    }
    pattern->UnregisterNode();
    /**
     * @tc.steps: step3. set and get renderFit mode with invalid surfaceId and valid renderFit number
     * @tc.expected: the return value equals 1
     */
    pattern->RegisterNode();
    for (int i = 0; i < NUM_SIXTEEN; ++i) {
        for (int j = 0; j < NUM_TWO; ++j) {
            code = XComponentInnerSurfaceController::SetRenderFitBySurfaceId(INVALID_SURFACE_ID, g_renderFitCases[i],
                g_isEnableNewVersionRenderFitCases[j]);
            EXPECT_EQ(code, 1);
            int32_t renderFitNumber = 0;
            bool isEnable = false;
            code = XComponentInnerSurfaceController::GetRenderFitBySurfaceId(INVALID_SURFACE_ID,
                renderFitNumber, isEnable);
            EXPECT_EQ(code, 1);
        }
    }
    /**
     * @tc.steps: step4. call SetRenderFitBySurfaceId after the renderContext has been destroyed.
     * @tc.expected: the return value equals 1
     */
    pattern->renderContextForSurface_.Reset();
    code = XComponentInnerSurfaceController::SetRenderFitBySurfaceId(SURFACE_ID, RenderFit::CENTER, true);
    EXPECT_EQ(code, 1);
}

/**
 * @tc.name: DumpAdvanceInfo
 * @tc.desc: Test Enable Image Analyzer
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestThreeNg, DumpAdvanceInfo, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    pattern->DumpAdvanceInfo();
    EXPECT_NE(pattern->renderSurface_, nullptr);

    pattern->renderSurface_ = nullptr;
    pattern->DumpAdvanceInfo();
    EXPECT_EQ(pattern->renderSurface_, nullptr);
}

/**
 * @tc.name: SetSurfaceIsOpaque
 * @tc.desc: Test set SurfaceIsOpaque for XComponent
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestThreeNg, SetSurfaceIsOpaque, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call SetSurfaceIsOpaque when type = XComponentType::SURFACE
     * @tc.expected: isOpaque in pattern is true
     */
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    pattern->renderContextForSurface_ = AceType::MakeRefPtr<MockRenderContext>();
    EXPECT_CALL(
        *AceType::DynamicCast<MockRenderContext>(pattern->renderContextForSurface_), SetSurfaceBufferOpaque(true))
        .Times(1);
    pattern->SetSurfaceIsOpaque(true);
    EXPECT_TRUE(pattern->isOpaque_);
    /**
     * @tc.steps: step2. call SetSurfaceIsOpaque when type = XComponentType::TEXTURE
     * @tc.expected: isOpaque in pattern is true
     */
    g_testProperty.xcType = XCOMPONENT_TEXTURE_TYPE_VALUE;
    frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    pattern = frameNode->GetPattern<XComponentPattern>();
    pattern->renderSurface_ = AceType::MakeRefPtr<MockRenderSurface>();
    EXPECT_CALL(*AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_), SetSurfaceBufferOpaque(true))
        .Times(1);
    pattern->SetSurfaceIsOpaque(true);
    EXPECT_TRUE(pattern->isOpaque_);
}

/**
 * @tc.name: SendAccessibilityAsyncEventTest4
 * @tc.desc: Test SendAccessibilityAsyncEvent Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestThreeNg, SendAccessibilityAsyncEventTest4, TestSize.Level1)
{
    /**
     * @tc.step1: Create XComponent and XComponentAccessibilityProvider
     * @tc.expected: Create XComponent and XComponentAccessibilityProvider Successfully
     */
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    auto xComponentAccessibilityProvider = std::make_shared<XComponentAccessibilityProvider>(pattern);
    ASSERT_TRUE(xComponentAccessibilityProvider);
    /**
     * @tc.step2: Call SendAccessibilityAsyncEvent Func when callback is null and thirdAccessibilityManager_ is null
     * @tc.expected: ret = -1
     */
    ArkUI_AccessibilityEventInfo accessibilityEvent;
    xComponentAccessibilityProvider->thirdAccessibilityManager_ = std::shared_ptr<ThirdAccessibilityManager>();
    int32_t ret = xComponentAccessibilityProvider->SendAccessibilityAsyncEvent(accessibilityEvent, nullptr);
    EXPECT_EQ(ret, -1);
}

/**
 * @tc.name: SendThirdAccessibilityProviderTest
 * @tc.desc: Test SendThirdAccessibilityProvider Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestThreeNg, SendThirdAccessibilityProviderTest, TestSize.Level1)
{
    /**
     * @tc.step1: Create XComponent and XComponentAccessibilityProvider
     * @tc.expected: Create XComponent and XComponentAccessibilityProvider Successfully
     */
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    auto xComponentAccessibilityProvider = std::make_shared<XComponentAccessibilityProvider>(pattern);
    ASSERT_TRUE(xComponentAccessibilityProvider);
    /**
     * @tc.step2: Call SendThirdAccessibilityProvider Func
     * @tc.expected: xComponentAccessibilityProvider->thirdAccessibilityManager_ is not null
     */
    auto thirdAccessibilityManager = std::make_shared<ThirdAccessibilityManager>();
    xComponentAccessibilityProvider->SendThirdAccessibilityProvider(thirdAccessibilityManager);
    EXPECT_TRUE(xComponentAccessibilityProvider->thirdAccessibilityManager_.lock());
}

/**
 * @tc.name: OnRegisterTest
 * @tc.desc: Test OnRegister Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestThreeNg, OnRegisterTest, TestSize.Level1)
{
    /**
     * @tc.step1: Create XComponent and XComponentAccessibilityChildTreeCallback
     * @tc.expected: Create XComponent and XComponentAccessibilityChildTreeCallback Successfully
     */
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    int accessibilityId = 2;
    auto xComponentAccessibilityChildTreeCallback =
        std::make_shared<XComponentAccessibilityChildTreeCallback>(pattern, accessibilityId);
    ASSERT_TRUE(xComponentAccessibilityChildTreeCallback);
    /**
     * @tc.step2: Call OnRegister Func when nativeProvider->IsRegister() is false
     * @tc.expected: ret = false and xComponentAccessibilityChildTreeCallback->isReg_ = false
     */
    uint32_t windowId = 1;
    int32_t treeId = 2;
    bool ret = xComponentAccessibilityChildTreeCallback->OnRegister(windowId, treeId);
    EXPECT_FALSE(ret);
    EXPECT_FALSE(xComponentAccessibilityChildTreeCallback->isReg_);
}

/**
 * @tc.name: OnDeregisterTest
 * @tc.desc: Test OnDeregister Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestThreeNg, OnDeregisterTest, TestSize.Level1)
{
    /**
     * @tc.step1: Create XComponent and XComponentAccessibilityChildTreeCallback
     * @tc.expected: Create XComponent and XComponentAccessibilityChildTreeCallback Successfully
     */
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    int accessibilityId = 2;
    auto xComponentAccessibilityChildTreeCallback =
        std::make_shared<XComponentAccessibilityChildTreeCallback>(pattern, accessibilityId);
    ASSERT_TRUE(xComponentAccessibilityChildTreeCallback);
    /**
     * @tc.step2: Call OnDeregister Func
     * @tc.expected: ret = false and xComponentAccessibilityChildTreeCallback->isReg_ = false
     */
    bool ret = xComponentAccessibilityChildTreeCallback->OnDeregister();
    EXPECT_TRUE(ret);
    EXPECT_FALSE(xComponentAccessibilityChildTreeCallback->isReg_);
}

/**
 * @tc.name: OnSetChildTreeTest
 * @tc.desc: Test OnSetChildTree Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestThreeNg, OnSetChildTreeTest, TestSize.Level1)
{
    /**
     * @tc.step1: Create XComponent and XComponentAccessibilityChildTreeCallback
     * @tc.expected: Create XComponent and XComponentAccessibilityChildTreeCallback Successfully
     */
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    int accessibilityId = 2;
    auto xComponentAccessibilityChildTreeCallback =
        std::make_shared<XComponentAccessibilityChildTreeCallback>(pattern, accessibilityId);
    ASSERT_TRUE(xComponentAccessibilityChildTreeCallback);
    /**
     * @tc.step2: Call OnDeregister Func
     * @tc.expected: ret = true
     */
    int32_t childWindowId = 1;
    int32_t childTreeId = 2;
    bool ret = xComponentAccessibilityChildTreeCallback->OnSetChildTree(childWindowId, childTreeId);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: OnDumpChildInfoTest
 * @tc.desc: Test OnDumpChildInfo Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestThreeNg, OnDumpChildInfoTest, TestSize.Level1)
{
    /**
     * @tc.step1: Create XComponent and XComponentAccessibilityChildTreeCallback
     * @tc.expected: Create XComponent and XComponentAccessibilityChildTreeCallback Successfully
     */
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    int accessibilityId = 2;
    auto xComponentAccessibilityChildTreeCallback =
        std::make_shared<XComponentAccessibilityChildTreeCallback>(pattern, accessibilityId);
    ASSERT_TRUE(xComponentAccessibilityChildTreeCallback);
    /**
     * @tc.step2: Call OnDumpChildInfo Func
     * @tc.expected: ret = false
     */
    std::vector<std::string> g_params;
    std::vector<std::string> info;
    bool ret = xComponentAccessibilityChildTreeCallback->OnDumpChildInfo(g_params, info);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: OnClearRegisterFlagTest
 * @tc.desc: Test OnClearRegisterFlag Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestThreeNg, OnClearRegisterFlagTest, TestSize.Level1)
{
    /**
     * @tc.step1: Create XComponent and XComponentAccessibilityChildTreeCallback
     * @tc.expected: Create XComponent and XComponentAccessibilityChildTreeCallback Successfully
     */
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    int accessibilityId = 2;
    auto xComponentAccessibilityChildTreeCallback =
        std::make_shared<XComponentAccessibilityChildTreeCallback>(pattern, accessibilityId);
    ASSERT_TRUE(xComponentAccessibilityChildTreeCallback);
    /**
     * @tc.step2: Call OnClearRegisterFlag Func
     * @tc.expected: isReg_ = false;
     */
    xComponentAccessibilityChildTreeCallback->OnClearRegisterFlag();
    EXPECT_FALSE(xComponentAccessibilityChildTreeCallback->isReg_);
}

/**
 * @tc.name: EnableAnalyzerTest001
 * @tc.desc: Test EnableAnalyzer Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestThreeNg, EnableAnalyzerTest001, TestSize.Level1)
{
    /**
     * @tc.step1: Create XComponent when Type = Surface
     * @tc.expected: Create XComponent Successfully
     */
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    /**
     * @tc.step2: Call EnableAnalyzer Func
     * @tc.expected: isEnableAnalyzer_ = true;
     */
    XComponentModelNG::EnableAnalyzer(AceType::RawPtr(frameNode), true);
    EXPECT_EQ(pattern->isEnableAnalyzer_, true);
}

/**
 * @tc.name: EnableAnalyzerTest002
 * @tc.desc: Test EnableAnalyzer Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestThreeNg, EnableAnalyzerTest002, TestSize.Level1)
{
    /**
     * @tc.step1: Create XComponent when Type = Component
     * @tc.expected: Create XComponent Successfully
     */
    g_testProperty.xcType = XCOMPONENT_COMPONENT_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    /**
     * @tc.step2: Call EnableAnalyzer Func
     * @tc.expected: isEnableAnalyzer_ = false;
     */
    XComponentModelNG::EnableAnalyzer(AceType::RawPtr(frameNode), true);
    EXPECT_EQ(pattern->isEnableAnalyzer_, false);
}

/**
 * @tc.name: EnableAnalyzerTest003
 * @tc.desc: Test EnableAnalyzer Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestThreeNg, EnableAnalyzerTest003, TestSize.Level1)
{
    /**
     * @tc.step1: Create XComponent when Type = Node
     * @tc.expected: Create XComponent Successfully
     */
    g_testProperty.xcType = XCOMPONENT_NODE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    /**
     * @tc.step2: Call EnableAnalyzer Func
     * @tc.expected: isEnableAnalyzer_ = false;
     */
    XComponentModelNG::EnableAnalyzer(AceType::RawPtr(frameNode), true);
    EXPECT_EQ(pattern->isEnableAnalyzer_, false);
}

/**
 * @tc.name: GetXComponentSurfaceRectTest
 * @tc.desc: Test GetXComponentSurfaceRect Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestThreeNg, GetXComponentSurfaceRectTest, TestSize.Level1)
{
    /**
     * @tc.step1: Create XComponent when Type = Surface
     * @tc.expected: Create XComponent Successfully
     */
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    /**
     * @tc.step2: Call GetXComponentSurfaceRect Func
     * @tc.expected: offsetX = OFFSET_X; offsetY = OFFSET_Y;
     * surfaceWidth = SURFACE_WIDTH_SIZE; surfaceHeight = SURFACE_HEIGHT_SIZE
     */
    pattern->surfaceOffset_ = OffsetF(OFFSET_X, OFFSET_Y);
    pattern->surfaceSize_ = SizeF(SURFACE_WIDTH_SIZE, SURFACE_HEIGHT_SIZE);
    float offsetX = 0;
    float offsetY = 0;
    float surfaceWidth = 0;
    float surfaceHeight = 0;
    XComponentModelNG::GetXComponentSurfaceRect(
        AceType::RawPtr(frameNode), offsetX, offsetY, surfaceWidth, surfaceHeight);
    EXPECT_EQ(offsetX, OFFSET_X);
    EXPECT_EQ(offsetY, OFFSET_Y);
    EXPECT_EQ(surfaceWidth, SURFACE_WIDTH_SIZE);
    EXPECT_EQ(surfaceHeight, SURFACE_HEIGHT_SIZE);
}

/**
 * @tc.name: OnDetachContextTest
 * @tc.desc: Test OnDetachContext Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestThreeNg, OnDetachContextTest, TestSize.Level1)
{
    /**
     * @tc.step1: Create XComponent
     * @tc.expected: Create XComponent Successfully
     */
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    PipelineContext* context = frameNode->GetContext();
    ASSERT_TRUE(context);
    /**
     * @tc.step2: Call OnDetachContext Func
     * @tc.expected: onWindowStateChangedCallbacks_ can not find nodeId by the frameNode
     */
    pattern->OnDetachContext(context);
    EXPECT_EQ(context->onWindowStateChangedCallbacks_.find(frameNode->GetId()),
        context->onWindowStateChangedCallbacks_.end());
}

/**
 * @tc.name: ToJsonValueTest
 * @tc.desc: Test ToJsonValue Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestThreeNg, ToJsonValueTest, TestSize.Level1)
{
    /**
     * @tc.step1: Create XComponent
     * @tc.expected: Create XComponent Successfully
     */
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    PipelineContext* context = frameNode->GetContext();
    ASSERT_TRUE(context);
    /**
     * @tc.step2: Call ToJsonValueTest Func
     * @tc.expected: EXPECT_EQ has no failure
     */
    pattern->isEnableAnalyzer_ = true;
    pattern->isEnableSecure_ = true;
    pattern->hdrBrightness_ = 0.5;
    pattern->isTransparentLayer_ = true;
    pattern->screenId_ = 12345;

    InspectorFilter filter;
    auto JsonValue = JsonUtil::Create(true);
    pattern->ToJsonValue(JsonValue, filter);
    EXPECT_EQ(JsonValue->GetString("enableAnalyzer"), "true");
    EXPECT_EQ(JsonValue->GetString("enableSecure"), "true");
    EXPECT_EQ(std::stof(JsonValue->GetString("hdrBrightness")), 0.5);
    EXPECT_EQ(JsonValue->GetString("enableTransparentLayer"), "true");
    EXPECT_EQ(std::stof(JsonValue->GetString("screenId")), 12345);
    EXPECT_EQ(JsonValue->GetString("renderFit"), "RenderFit.RESIZE_FILL");
}

/**
 * @tc.name: LockCanvasTest
 * @tc.desc: Test LockCanvas Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestThreeNg, LockCanvasTest, TestSize.Level1)
{
    /**
     * @tc.step1: Create XComponent
     * @tc.expected: Create XComponent Successfully
     */
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    pattern->nativeWindow_ = new int();
    /**
     * @tc.step2: Call LockCanvasTest Func
     * @tc.expected: first call's returnValue is not nullptr and second call's returnValue is nullptr
     */
    auto canvas = pattern->LockCanvas();
    EXPECT_TRUE(canvas);
    canvas = pattern->LockCanvas();
    EXPECT_FALSE(canvas);

    // clear variables on the stack to prevent memory leaks
    RSCanvasUtils::UnlockCanvas(canvas, reinterpret_cast<OHNativeWindow*>(pattern->nativeWindow_));
    delete reinterpret_cast<int*>(pattern->nativeWindow_);
    pattern->nativeWindow_ = nullptr;
}

/**
 * @tc.name: UnlockCanvasAndPostTest
 * @tc.desc: Test UnlockCanvasAndPost Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestThreeNg, UnlockCanvasAndPostTest, TestSize.Level1)
{
    /**
     * @tc.step1: Create XComponent
     * @tc.expected: Create XComponent Successfully
     */
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    pattern->nativeWindow_ = new int();
    /**
     * @tc.step2: Call UnlockCanvasAndPost Func
     * @tc.expected: returnValue is false
     */
    auto canvas = pattern->LockCanvas();
    EXPECT_TRUE(canvas);
    pattern->UnlockCanvasAndPost(canvas);
    EXPECT_FALSE(Testing::TestingCanvasUtils::GetInstance()->lockCanvas);
    pattern->UnlockCanvasAndPost(canvas);
    EXPECT_FALSE(Testing::TestingCanvasUtils::GetInstance()->lockCanvas);

    // clear variables on the stack to prevent memory leaks
    delete reinterpret_cast<int*>(pattern->nativeWindow_);
    pattern->nativeWindow_ = nullptr;
}

/**
 * @tc.name: IsEnableMatchParentTest
 * @tc.desc: Test IsEnableMatchParent Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestThreeNg, IsEnableMatchParentTest, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    /**
     * @tc.steps2: Check Function IsEnableMatchParent's return value.
     * @tc.expected: Function IsEnableMatchParent returns true.
     */
    EXPECT_TRUE(pattern->IsEnableMatchParent());
}

/**
 * @tc.name: SetHasGotNativeXComponentTest
 * @tc.desc: Test SetHasGotNativeXComponent Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestThreeNg, SetHasGotNativeXComponentTest, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    /**
     * @tc.steps2: Check Param hasGotNativeXComponent_'s value.
     * @tc.expected: Param hasGotNativeXComponent_ equals true.
     */
    pattern->SetHasGotNativeXComponent(true);
    EXPECT_TRUE(pattern->hasGotNativeXComponent_);
}

/**
 * @tc.name: GetSurfaceRotationBySurfaceIdTest
 * @tc.desc: Test innerAPI GetSurfaceRotationBySurfaceId Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestThreeNg, GetSurfaceRotationBySurfaceIdTest, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    /**
     * @tc.steps2: Call XComponentInnerSurfaceController::GetSurfaceRotationBySurfaceId Func when isSurfaceLock_ = true
     * and isSurfaceLock = false with invalid surfaceId.
     * @tc.expected: code equals 1 and isSurfaceLock = false.
     */
    pattern->isSurfaceLock_ = true;
    bool isSurfaceLock = false;
    std::string surfaceId = "123";
    int32_t code = XComponentInnerSurfaceController::GetSurfaceRotationBySurfaceId(surfaceId, isSurfaceLock);
    EXPECT_EQ(code, 1);
    EXPECT_FALSE(isSurfaceLock);
    /**
     * @tc.steps3: Call XComponentInnerSurfaceController::GetSurfaceRotationBySurfaceId Func when isSurfaceLock_ = true
     * and isSurfaceLock = false with valid surfaceId.
     * @tc.expected: code equals 0 and isSurfaceLock = true.
     */
    pattern->isSurfaceLock_ = true;
    isSurfaceLock = false;
    surfaceId = "123";
    pattern->initialSurfaceId_ = "123";
    pattern->RegisterNode();
    code = XComponentInnerSurfaceController::GetSurfaceRotationBySurfaceId(surfaceId, isSurfaceLock);
    EXPECT_EQ(code, 0);
    EXPECT_TRUE(isSurfaceLock);
}

/**
 * @tc.name: InitNativeNodeCallbacksTest
 * @tc.desc: Test InitNativeNodeCallbacks Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestThreeNg, InitNativeNodeCallbacksTest, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    g_testProperty.libraryName = XCOMPONENT_LIBRARY_NAME;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    /**
     * @tc.steps2: Call InitNativeNodeCallbacks Func
     * @tc.expected: attachNativeNodeCallback_ is not null and detachNativeNodeCallback_ is not null.
     */
    pattern->InitNativeNodeCallbacks();
    ASSERT_TRUE(pattern->nativeXComponentImpl_);
    EXPECT_TRUE(pattern->nativeXComponentImpl_->attachNativeNodeCallback_);
    EXPECT_TRUE(pattern->nativeXComponentImpl_->detachNativeNodeCallback_);
}

/**
 * @tc.name: OnAccessibilityChildTreeDeregisterTest001
 * @tc.desc: Test InitNativeNodeCallbacks Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestThreeNg, OnAccessibilityChildTreeDeregisterTest001, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    g_testProperty.libraryName = XCOMPONENT_LIBRARY_NAME;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    /**
     * @tc.steps2: GetNativeProvider is null ptr
     * @tc.expected: OnAccessibilityChildTreeDeregister return false
     */
    auto result = pattern->OnAccessibilityChildTreeDeregister(AceType::RawPtr(frameNode));
    ASSERT_FALSE(result);
    result = pattern->OnAccessibilityChildTreeDeregister();
    ASSERT_FALSE(result);
}

/**
 * @tc.name: XComponentAttachToFrameNodeTest001
 * @tc.desc: Test OnAttachToFrameNode Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestThreeNg, XComponentAttachToFrameNodeTest001, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    g_testProperty.libraryName = XCOMPONENT_LIBRARY_NAME;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    pattern->nodeId_ = NODE_ID_STRING;
    /**
     * @tc.steps2: call OnAttachToFrameNode
     * @tc.expected: nodeId_ is updated
     */
    pattern->OnAttachToFrameNode();
    EXPECT_EQ(pattern->nodeId_, std::to_string(frameNode->GetId()));
    /**
     * @tc.steps3: call OnAttachToFrameNode when host is nullptr
     * @tc.expected: nodeId_ is not updated
     */
    pattern->nodeId_ = NODE_ID_STRING;
    pattern->frameNode_ = nullptr;
    pattern->OnAttachToFrameNode();
    EXPECT_EQ(pattern->nodeId_, NODE_ID_STRING);
}
}
