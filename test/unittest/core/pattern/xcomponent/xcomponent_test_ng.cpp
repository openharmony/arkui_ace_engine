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
#define protected public
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
const uint64_t XCOMPONENT_SCREEN_ID = 12345u;
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
bool isLock = true;
bool g_isDestroyed = false;
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

class XComponentMockRenderContext : public RenderContext {
    void SetRenderFit(RenderFit renderFit) override
    {
        propRenderFit_ = renderFit;
    }
};

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
    void TearDown() override
    {
        testProperty.loadEvent = std::nullopt;
        testProperty.destroyEvent = std::nullopt;
        testProperty.surfaceCreatedEvent = std::nullopt;
        testProperty.surfaceChangedEvent = std::nullopt;
        testProperty.surfaceDestroyedEvent = std::nullopt;
        g_isDestroyed = false;
    }

protected:
    static RefPtr<FrameNode> CreateXComponentNode(TestProperty& testProperty);
};

void XComponentTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    testProperty.xcId = XCOMPONENT_ID;
    testProperty.libraryName = XCOMPONENT_LIBRARY_NAME;
    testProperty.soPath = XCOMPONENT_SO_PATH;
    g_isDestroyed = false;
}

void XComponentTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> XComponentTestNg::CreateXComponentNode(TestProperty& testProperty)
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
 * @tc.name: InitControllerMultiThreadTest001
 * @tc.desc: Test InitControllerMultiThread func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, InitControllerMultiThreadTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create xcomponent pattern
     * @tc.expected: xcomponent pattern created
     */
    testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    testProperty.xcId = std::nullopt;
    testProperty.libraryName = std::nullopt;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    ASSERT_TRUE(pattern->xcomponentController_);
    pattern->isTypedNode_ = false;
    pattern->surfaceId_ = SURFACE_ID;
    pattern->xcomponentController_->surfaceId_ = "";
    /**
     * @tc.steps: step2. call InitControllerMultiThread
     * @tc.expected: xcomponent controller is initialized
     */
    pattern->InitControllerMultiThread();
    pattern->xcomponentController_->ConfigSurface(
        static_cast<uint32_t>(SURFACE_WIDTH), static_cast<uint32_t>(SURFACE_HEIGHT));
    EXPECT_EQ(pattern->xcomponentController_->surfaceId_, pattern->surfaceId_);
    auto controllerNG = static_cast<XComponentControllerNG*>(pattern->xcomponentController_.get());
    EXPECT_TRUE(controllerNG);
    EXPECT_FALSE(controllerNG->pattern_.Invalid());
    EXPECT_EQ(controllerNG->pattern_.Upgrade(), pattern);
}

/**
 * @tc.name: InitControllerMultiThreadTest002
 * @tc.desc: Test InitControllerMultiThread func for typedNode
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, InitControllerMultiThreadTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create xcomponent pattern
     * @tc.expected: xcomponent pattern created
     */
    testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    testProperty.xcId = std::nullopt;
    testProperty.libraryName = std::nullopt;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    ASSERT_TRUE(pattern->xcomponentController_);
    pattern->isTypedNode_ = true;
    pattern->surfaceId_ = SURFACE_ID;
    pattern->xcomponentController_->surfaceId_ = "";
    /**
     * @tc.steps: step2. call InitControllerMultiThread
     * @tc.expected: xcomponent controller is not initialized
     */
    pattern->InitControllerMultiThread();
    EXPECT_NE(pattern->xcomponentController_->surfaceId_, pattern->surfaceId_);
}

/**
 * @tc.name: RegisterContextEventMultiThreadTest
 * @tc.desc: Test RegisterContextEventMultiThread func for typedNode
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, RegisterContextEventMultiThreadTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create xcomponent pattern
     * @tc.expected: xcomponent pattern created
     */
    testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    testProperty.xcId = std::nullopt;
    testProperty.libraryName = std::nullopt;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    pattern->transformHintChangedCallbackId_ = std::nullopt;
    /**
     * @tc.steps: step2. call RegisterContextEventMultiThread
     * @tc.expected: pipeline context event is registered.
     */
    pattern->RegisterContextEventMultiThread(frameNode);
    EXPECT_TRUE(pattern->transformHintChangedCallbackId_.has_value());
}

/**
 * @tc.name: InitSurfaceMultiThreadTest001
 * @tc.desc: Test InitSurfaceMultiThread func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, InitSurfaceMultiThreadTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create xcomponent pattern
     * @tc.expected: xcomponent pattern created
     */
    testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    testProperty.xcId = std::nullopt;
    testProperty.libraryName = std::nullopt;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    pattern->renderSurface_ = nullptr;
    pattern->renderContextForSurface_ = nullptr;
    pattern->isCNode_ = true;
    /**
     * @tc.steps: step2. call InitSurfaceMultiThread
     * @tc.expected: surface is initialized
     */
    pattern->InitSurfaceMultiThread(frameNode);
    EXPECT_TRUE(pattern->renderSurface_);
    EXPECT_TRUE(pattern->renderContextForSurface_);
}

/**
 * @tc.name: InitSurfaceMultiThreadTest002
 * @tc.desc: Test InitSurfaceMultiThread func for XComponentType::TEXTURE
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, InitSurfaceMultiThreadTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create xcomponent pattern
     * @tc.expected: xcomponent pattern created
     */
    testProperty.xcType = XCOMPONENT_TEXTURE_TYPE_VALUE;
    testProperty.xcId = std::nullopt;
    testProperty.libraryName = std::nullopt;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    pattern->renderSurface_ = nullptr;
    pattern->renderContextForSurface_ = nullptr;
    pattern->isTypedNode_ = true;
    /**
     * @tc.steps: step2. call InitSurfaceMultiThread
     * @tc.expected: surface is initialized
     */
    pattern->InitSurfaceMultiThread(frameNode);
    EXPECT_FALSE(pattern->renderContextForSurface_);
}

/**
 * @tc.name: OnAttachToMainTreeMultiThreadTest001
 * @tc.desc: Test OnAttachToMainTreeMultiThread func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, OnAttachToMainTreeMultiThreadTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create xcomponent pattern
     * @tc.expected: xcomponent pattern created
     */
    testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    testProperty.xcId = std::nullopt;
    testProperty.libraryName = std::nullopt;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    pattern->isOnTree_ = false;
    pattern->isTypedNode_ = false;
    /**
     * @tc.steps: step2. call OnAttachToMainTreeMultiThread
     * @tc.expected: xcomponent pattern is on tree
     */
    pattern->OnAttachToMainTreeMultiThread(frameNode);
    EXPECT_TRUE(pattern->isOnTree_);
}

/**
 * @tc.name: OnAttachToMainTreeMultiThreadTest002
 * @tc.desc: Test OnAttachToMainTreeMultiThread func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, OnAttachToMainTreeMultiThreadTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create xcomponent pattern
     * @tc.expected: xcomponent pattern created
     */
    testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    testProperty.xcId = std::nullopt;
    testProperty.libraryName = std::nullopt;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    pattern->isOnTree_ = false;
    pattern->isTypedNode_ = true;
    pattern->surfaceId_ = SURFACE_ID;
    pattern->screenId_ = XCOMPONENT_SCREEN_ID;
    pattern->surfaceCallbackMode_ = SurfaceCallbackMode::DEFAULT;
    /**
     * @tc.steps: step2. call OnAttachToMainTreeMultiThread
     * @tc.expected: xcomponent pattern is on tree
     */
    pattern->OnAttachToMainTreeMultiThread(frameNode);
    EXPECT_TRUE(pattern->isOnTree_);
    EXPECT_TRUE(pattern->surfaceId_.empty());
}

/**
 * @tc.name: OnAttachToMainTreeMultiThreadTest003
 * @tc.desc: Test OnAttachToMainTreeMultiThread func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, OnAttachToMainTreeMultiThreadTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create xcomponent pattern
     * @tc.expected: xcomponent pattern created
     */
    testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    testProperty.xcId = std::nullopt;
    testProperty.libraryName = std::nullopt;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    pattern->isOnTree_ = false;
    pattern->isTypedNode_ = true;
    pattern->surfaceId_ = SURFACE_ID;
    pattern->screenId_ = XCOMPONENT_SCREEN_ID;
    pattern->surfaceCallbackMode_ = SurfaceCallbackMode::PIP;
    /**
     * @tc.steps: step2. call OnAttachToMainTreeMultiThread
     * @tc.expected: xcomponent pattern is on tree
     */
    pattern->OnAttachToMainTreeMultiThread(frameNode);
    EXPECT_TRUE(pattern->isOnTree_);
    EXPECT_EQ(pattern->surfaceId_, SURFACE_ID);
}

/**
 * @tc.name: OnDetachFromMainTreeMultiThreadTest001
 * @tc.desc: Test OnDetachFromMainTreeMultiThread func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, OnDetachFromMainTreeMultiThreadTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create xcomponent pattern
     * @tc.expected: xcomponent pattern created
     */
    testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    testProperty.xcId = std::nullopt;
    testProperty.libraryName = std::nullopt;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    pattern->isOnTree_ = true;
    pattern->isTypedNode_ = false;
    pattern->transformHintChangedCallbackId_ = std::nullopt;
    /**
     * @tc.steps: step2. call OnDetachFromMainTreeMultiThread
     * @tc.expected: xcomponent pattern is not on tree
     */
    pattern->OnDetachFromMainTreeMultiThread(frameNode);
    EXPECT_FALSE(pattern->isOnTree_);
}

/**
 * @tc.name: OnDetachFromMainTreeMultiThreadTest002
 * @tc.desc: Test OnDetachFromMainTreeMultiThread func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, OnDetachFromMainTreeMultiThreadTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create xcomponent pattern
     * @tc.expected: xcomponent pattern created
     */
    testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    testProperty.xcId = std::nullopt;
    testProperty.libraryName = std::nullopt;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    ASSERT_TRUE(pattern->xcomponentController_);
    pattern->xcomponentController_->SetSurfaceId(SURFACE_ID);
    pattern->isOnTree_ = true;
    pattern->isTypedNode_ = true;
    pattern->surfaceCallbackMode_ = SurfaceCallbackMode::DEFAULT;
    /**
     * @tc.steps: step2. call OnDetachFromMainTreeMultiThread
     * @tc.expected: xcomponent pattern is not on tree
     */
    pattern->OnDetachFromMainTreeMultiThread(frameNode);
    EXPECT_FALSE(pattern->isOnTree_);
    EXPECT_TRUE(pattern->xcomponentController_->surfaceId_.empty());
}

/**
 * @tc.name: OnDetachFromMainTreeMultiThreadTest003
 * @tc.desc: Test OnDetachFromMainTreeMultiThread func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, OnDetachFromMainTreeMultiThreadTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create xcomponent pattern
     * @tc.expected: xcomponent pattern created
     */
    testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    testProperty.xcId = std::nullopt;
    testProperty.libraryName = std::nullopt;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    ASSERT_TRUE(pattern->xcomponentController_);
    pattern->xcomponentController_->SetSurfaceId(SURFACE_ID);
    pattern->isOnTree_ = true;
    pattern->isTypedNode_ = true;
    pattern->surfaceCallbackMode_ = SurfaceCallbackMode::PIP;
    /**
     * @tc.steps: step2. call OnDetachFromMainTreeMultiThread
     * @tc.expected: xcomponent pattern is not on tree
     */
    pattern->OnDetachFromMainTreeMultiThread(frameNode);
    EXPECT_FALSE(pattern->isOnTree_);
    EXPECT_FALSE(pattern->xcomponentController_->surfaceId_.empty());
}

/**
 * @tc.name: OnDetachFromFrameNodeMultiThread001
 * @tc.desc: Test OnDetachFromFrameNodeMultiThread func when xcomponent is not initialized
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, OnDetachFromFrameNodeMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create xcomponent pattern
     * @tc.expected: xcomponent pattern created
     */
    testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    testProperty.xcId = XCOMPONENT_ID;
    testProperty.libraryName = XCOMPONENT_LIBRARY_NAME;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    pattern->isTypedNode_ = false;
    pattern->hasXComponentInit_ = false;
    /**
     * @tc.steps: step2. register surface events
     * @tc.expected: surface event is registered
     */
    auto pair = pattern->GetNativeXComponent();
    auto weakNativeXComponent = pair.second;
    auto nativeXComponent = weakNativeXComponent.lock();
    auto nativeXComponentImpl = pair.first;
    ASSERT_TRUE(nativeXComponent);
    ASSERT_TRUE(nativeXComponentImpl);
    auto onSurfaceDestroyed = [](OH_NativeXComponent* component, void* window) {
        g_isDestroyed = true;
    };
    OH_NativeXComponent_Callback callback = {
        .OnSurfaceDestroyed = onSurfaceDestroyed
    };
    nativeXComponent->RegisterCallback(&callback);
    /**
     * @tc.steps: step3. call OnDetachFromMainTreeMultiThread
     * @tc.expected: surface is not destroyed
     */
    pattern->OnDetachFromFrameNodeMultiThread(AceType::RawPtr(frameNode));
    EXPECT_FALSE(g_isDestroyed);
}

/**
 * @tc.name: OnDetachFromFrameNodeMultiThread002
 * @tc.desc: Test OnDetachFromFrameNodeMultiThread func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, OnDetachFromFrameNodeMultiThread002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create xcomponent pattern
     * @tc.expected: xcomponent pattern created
     */
    testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    testProperty.xcId = XCOMPONENT_ID;
    testProperty.libraryName = XCOMPONENT_LIBRARY_NAME;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    pattern->isTypedNode_ = false;
    pattern->hasXComponentInit_ = true;
    /**
     * @tc.steps: step2. register surface events
     * @tc.expected: surface event is registered
     */
    auto pair = pattern->GetNativeXComponent();
    auto weakNativeXComponent = pair.second;
    auto nativeXComponent = weakNativeXComponent.lock();
    auto nativeXComponentImpl = pair.first;
    ASSERT_TRUE(nativeXComponent);
    ASSERT_TRUE(nativeXComponentImpl);
    auto onSurfaceDestroyed = [](OH_NativeXComponent* component, void* window) {
        g_isDestroyed = true;
    };
    OH_NativeXComponent_Callback callback = {
        .OnSurfaceDestroyed = onSurfaceDestroyed
    };
    nativeXComponent->RegisterCallback(&callback);
    /**
     * @tc.steps: step3. call OnDetachFromMainTreeMultiThread
     * @tc.expected: surface is not destroyed
     */
    pattern->OnDetachFromFrameNodeMultiThread(AceType::RawPtr(frameNode));
    EXPECT_TRUE(g_isDestroyed);
}

/**
 * @tc.name: OnDetachFromFrameNodeMultiThread003
 * @tc.desc: Test OnDetachFromFrameNodeMultiThread func for type node
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, OnDetachFromFrameNodeMultiThread003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create xcomponent pattern
     * @tc.expected: xcomponent pattern created
     */
    testProperty.xcType = XCOMPONENT_TEXTURE_TYPE_VALUE;
    testProperty.xcId = XCOMPONENT_ID;
    testProperty.libraryName = XCOMPONENT_LIBRARY_NAME;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    pattern->isTypedNode_ = true;
    pattern->hasLoadNativeDone_ = true;
    pattern->isNativeXComponent_ = true;
    /**
     * @tc.steps: step2. call OnDetachFromMainTreeMultiThread
     * @tc.expected: OnNativeUnload is called
     */
    pattern->OnDetachFromFrameNodeMultiThread(AceType::RawPtr(frameNode));
    EXPECT_FALSE(pattern->hasLoadNativeDone_);
}

/**
 * @tc.name: OnDetachFromFrameNodeMultiThread004
 * @tc.desc: Test OnDetachFromFrameNodeMultiThread func for type node
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, OnDetachFromFrameNodeMultiThread004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create xcomponent pattern
     * @tc.expected: xcomponent pattern created
     */
    testProperty.xcType = XCOMPONENT_TEXTURE_TYPE_VALUE;
    testProperty.xcId = XCOMPONENT_ID;
    testProperty.libraryName = XCOMPONENT_LIBRARY_NAME;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    ASSERT_TRUE(pattern->xcomponentController_);
    pattern->isTypedNode_ = true;
    pattern->surfaceCallbackMode_ = SurfaceCallbackMode::PIP;
    /**
     * @tc.steps: step2. call OnDetachFromMainTreeMultiThread
     * @tc.expected: surface is destroyed
     */
    pattern->OnDetachFromFrameNodeMultiThread(AceType::RawPtr(frameNode));
    EXPECT_TRUE(pattern->xcomponentController_->surfaceId_.empty());
}

/**
 * @tc.name: OnDetachFromFrameNodeMultiThread005
 * @tc.desc: Test OnDetachFromFrameNodeMultiThread func for XComponentType::TEXTURE
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, OnDetachFromFrameNodeMultiThread005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create xcomponent pattern
     * @tc.expected: xcomponent pattern created
     */
    testProperty.xcType = XCOMPONENT_TEXTURE_TYPE_VALUE;
    testProperty.xcId = std::nullopt;
    testProperty.libraryName = XCOMPONENT_LIBRARY_NAME;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    pattern->isTypedNode_ = false;
    pattern->hasXComponentInit_ = true;
    /**
     * @tc.steps: step2. register surface events
     * @tc.expected: surface event is registered
     */
    auto pair = pattern->GetNativeXComponent();
    auto weakNativeXComponent = pair.second;
    auto nativeXComponent = weakNativeXComponent.lock();
    auto nativeXComponentImpl = pair.first;
    ASSERT_TRUE(nativeXComponent);
    ASSERT_TRUE(nativeXComponentImpl);
    auto onSurfaceDestroyed = [](OH_NativeXComponent* component, void* window) {
        g_isDestroyed = true;
    };
    OH_NativeXComponent_Callback callback = {
        .OnSurfaceDestroyed = onSurfaceDestroyed
    };
    nativeXComponent->RegisterCallback(&callback);
    /**
     * @tc.steps: step3. call OnDetachFromMainTreeMultiThread
     * @tc.expected: surface is not destroyed
     */
    pattern->OnDetachFromFrameNodeMultiThread(AceType::RawPtr(frameNode));
    EXPECT_TRUE(g_isDestroyed);
}

/**
 * @tc.name: OnDetachFromFrameNodeMultiThread006
 * @tc.desc: Test OnDetachFromFrameNodeMultiThread func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestNg, OnDetachFromFrameNodeMultiThread006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create xcomponent pattern
     * @tc.expected: xcomponent pattern created
     */
    testProperty.xcType = XCOMPONENT_TEXTURE_TYPE_VALUE;
    testProperty.xcId = XCOMPONENT_ID;
    testProperty.libraryName = XCOMPONENT_LIBRARY_NAME;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    pattern->isTypedNode_ = true;
    pattern->isNativeXComponent_ = false;
    EXPECT_TRUE(pattern->accessibilityChildTreeCallback_);
    /**
     * @tc.steps: step2. call OnDetachFromMainTreeMultiThread
     * @tc.expected: Child tree callback is released
     */
    pattern->OnDetachFromFrameNodeMultiThread(AceType::RawPtr(frameNode));
    EXPECT_FALSE(pattern->accessibilityChildTreeCallback_);
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
    auto onDestroy = [&onDestroyKey](const std::string& /* xComponentId */) { onDestroyKey = CHECK_KEY; };

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
    auto xComponentEventHub = frameNode->GetOrCreateEventHub<XComponentEventHub>();
    ASSERT_TRUE(xComponentEventHub);
    xComponentEventHub->FireLoadEvent(XCOMPONENT_ID);
    xComponentEventHub->FireDestroyEvent(XCOMPONENT_ID);
    EXPECT_EQ(onLoadKey, CHECK_KEY);
    EXPECT_EQ(onDestroyKey, CHECK_KEY);

    /**
     * @tc.steps: step3. reset the testProperty and rerun step1&2
     *            case: type = XCOMPONENT_COMPONENT_TYPE
     * @tc.expected: three checkKeys has no change
     */

    auto onLoad2 = [&onLoadKey](const std::string& /* xComponentId */) { onLoadKey = ""; };
    auto onDestroy2 = [&onDestroyKey](const std::string& /* xComponentId */) { onDestroyKey = ""; };
    testProperty.xcType = XCOMPONENT_COMPONENT_TYPE_VALUE;
    testProperty.loadEvent = std::move(onLoad2);
    testProperty.destroyEvent = std::move(onDestroy2);

    auto frameNode2 = CreateXComponentNode(testProperty);
    EXPECT_TRUE(frameNode2);
    xComponentEventHub = frameNode2->GetOrCreateEventHub<XComponentEventHub>();
    ASSERT_TRUE(xComponentEventHub);
    xComponentEventHub->FireLoadEvent(XCOMPONENT_ID);
    xComponentEventHub->FireDestroyEvent(XCOMPONENT_ID);
    EXPECT_EQ(onLoadKey, CHECK_KEY);
    EXPECT_EQ(onDestroyKey, CHECK_KEY);
}

/**
 * @tc.name: XComponentLayoutAlgorithmTest006
 * @tc.desc: Test BeforeSyncGeometryProperties
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
     * @tc.steps: step2. call BeforeSyncGeometryProperties
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
    // goto other branch
    pattern->type_ = XCOMPONENT_COMPONENT_TYPE_VALUE;
    pattern->XComponentSizeInit(); // IsSurfaceValid=false
    pattern->OnRebuildFrame();     // type="component"

    /**
     * @tc.steps: step3. call BeforeSyncGeometryProperties adjust frameOffsetChanges, contentOffsetChanges and
     *                   contentSizeChanges
     * @tc.expected: BeforeSyncGeometryProperties return false
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
            pattern->BeforeSyncGeometryProperties(config);
        }
    }

    /**
     * @tc.steps: step4. call BeforeSyncGeometryProperties
     *            case: size is zero
     * @tc.expected: BeforeSyncGeometryProperties return false
     */
    geometryNode->SetContentSize({ 0.0f, 0.0f });
    pattern->BeforeSyncGeometryProperties(config);

    /**
     * @tc.steps: step5. call BeforeSyncGeometryProperties
     *            case: type="component", config.skipMeasure = true, dirty->SkipMeasureContent() = true
     * @tc.expected: BeforeSyncGeometryProperties return false
     */
    pattern->BeforeSyncGeometryProperties(config);
    config.skipMeasure = true;
    pattern->BeforeSyncGeometryProperties(config);
    pattern->type_ = XCOMPONENT_COMPONENT_TYPE_VALUE;
    pattern->BeforeSyncGeometryProperties(config);
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
    focusHub->onFocusInternal_(focusHub->focusReason_);
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
    auto onDestroy = [&onDestroyKey](const std::string& /* xComponentId */) { onDestroyKey = CHECK_KEY; };

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
        EXPECT_EQ(static_cast<int>(item.type), static_cast<int>(TouchType::PULL_DOWN));
        EXPECT_EQ(item.size, XCOMPONENT_ID_LEN_MAX);
        EXPECT_EQ(item.force, FORCE);
        EXPECT_EQ(item.titlX, CHILD_OFFSET_WIDTH);
        EXPECT_EQ(item.titlY, CHILD_OFFSET_HEIGHT);
        EXPECT_EQ(static_cast<int>(item.sourceTool), static_cast<int>(SourceTool::MOUSE));
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
    auto xComponentEventHub = frameNode->GetOrCreateEventHub<XComponentEventHub>();
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
    auto onDestroy = [&onDestroyKey](const std::string& /* xComponentId */) { onDestroyKey = CHECK_KEY; };

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
    auto xComponentEventHub = frameNode->GetOrCreateEventHub<XComponentEventHub>();
    ASSERT_TRUE(xComponentEventHub);
    xComponentEventHub->FireLoadEvent(XCOMPONENT_ID);
    xComponentEventHub->FireDestroyEvent(XCOMPONENT_ID);
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
    xComponentEventHub->FireDestroyEvent(XCOMPONENT_ID);
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
    auto xComponentEventHub = frameNode->GetOrCreateEventHub<XComponentEventHub>();
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
    auto xComponentEventHub = frameNode->GetOrCreateEventHub<XComponentEventHub>();
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
     * @tc.expected: handlingSurfaceRenderContext_->SetSurfaceRotation(isLock) is called
     */
    EXPECT_CALL(
        *AceType::DynamicCast<MockRenderContext>(pattern->handlingSurfaceRenderContext_), SetSurfaceRotation(isLock))
        .WillOnce(Return());
    xcomponentController->SetSurfaceRotation(isLock);

    /**
     * @tc.steps: step6. call XcomponentController's interface relative to GetSurfaceRotation
     * @tc.expected: the lock status get from GetSurfaceRotation equals the lock status set by SetSurfaceRotation
     */
    auto lock = xcomponentController->GetSurfaceRotation();
    EXPECT_EQ(lock, isLock);
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

    if (ImageAnalyzerMgr::GetInstance().IsImageAnalyzerSupported()) {
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
     * @tc.steps: step1. set surface life cycle callback, set id&libraryname to null and create XComponent
     * @tc.expected: xcomponent frameNode create successfully
     */
    testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    testProperty.xcId = std::nullopt;
    testProperty.libraryName = std::nullopt;
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
    testProperty.surfaceCreatedEvent = std::move(onSurfaceCreated);
    testProperty.surfaceChangedEvent = std::move(onSurfaceChanged);
    testProperty.surfaceDestroyedEvent = std::move(onSurfaceDestroyed);
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto xComponentEventHub = frameNode->GetOrCreateEventHub<XComponentEventHub>();
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
HWTEST_F(XComponentTestNg, SetAndGetRenderFitBySurfaceIdTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create xcomponent pattern
     * @tc.expected: xcomponent pattern created
     */
    testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    testProperty.xcId = std::nullopt;
    testProperty.libraryName = std::nullopt;
    auto frameNode = CreateXComponentNode(testProperty);
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
HWTEST_F(XComponentTestNg, DumpAdvanceInfo, TestSize.Level1)
{
    testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    pattern->DumpAdvanceInfo();
    EXPECT_NE(pattern->renderSurface_, nullptr);

    pattern->renderSurface_ = nullptr;
    pattern->DumpAdvanceInfo();
    EXPECT_EQ(pattern->renderSurface_, nullptr);
}
} // namespace OHOS::Ace::NG
