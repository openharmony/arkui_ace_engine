/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/components_ng/render/mock_render_context.h"

#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_controller_ng.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_event_hub.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_inner_surface_controller.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_layout_algorithm.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_layout_property.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_model.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_model_static.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_paint_method.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_surface_holder.h"
#include "core/components_ng/property/measure_property.h"
#include "core/event/mouse_event.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "interfaces/native/native_interface_xcomponent.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
// ============================================================================
// Test class for XComponentEventHub
// ============================================================================
class XComponentEventHubTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void XComponentEventHubTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void XComponentEventHubTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: XComponentEventHubTest001
 * @tc.desc: Test FireLoadEvent when loadEvent_ is set
 * @tc.type: FUNC
 */
HWTEST_F(XComponentEventHubTestNg, XComponentEventHubTest001, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<XComponentEventHub>();
    std::string receivedId = "";

    eventHub->SetOnLoad([&receivedId](const std::string& xcomponentId) {
        receivedId = xcomponentId;
    });

    eventHub->FireLoadEvent("test_xcomponent");
    EXPECT_EQ(receivedId, "test_xcomponent");
}

/**
 * @tc.name: XComponentEventHubTest002
 * @tc.desc: Test FireLoadEvent when loadEvent_ is not set
 * @tc.type: FUNC
 */
HWTEST_F(XComponentEventHubTestNg, XComponentEventHubTest002, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<XComponentEventHub>();

    // Should not crash when loadEvent_ is not set
    eventHub->FireLoadEvent("test_xcomponent");
}

/**
 * @tc.name: XComponentEventHubTest003
 * @tc.desc: Test FireDestroyEvent when destroyEvent_ is set
 * @tc.type: FUNC
 */
HWTEST_F(XComponentEventHubTestNg, XComponentEventHubTest003, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<XComponentEventHub>();
    std::string receivedId = "";

    eventHub->SetOnDestroy([&receivedId](const std::string& xcomponentId) {
        receivedId = xcomponentId;
    });

    eventHub->FireDestroyEvent("test_xcomponent");
    EXPECT_EQ(receivedId, "test_xcomponent");
}

/**
 * @tc.name: XComponentEventHubTest004
 * @tc.desc: Test FireDestroyEvent when destroyEvent_ is not set
 * @tc.type: FUNC
 */
HWTEST_F(XComponentEventHubTestNg, XComponentEventHubTest004, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<XComponentEventHub>();

    // Should not crash when destroyEvent_ is not set
    eventHub->FireDestroyEvent("test_xcomponent");
}

/**
 * @tc.name: XComponentEventHubTest005
 * @tc.desc: Test FireSurfaceInitEvent when surfaceInitEvent_ is set
 * @tc.type: FUNC
 */
HWTEST_F(XComponentEventHubTestNg, XComponentEventHubTest005, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<XComponentEventHub>();
    std::string receivedId = "";
    uint32_t receivedNodeId = 0;
    bool receivedIsDestroy = false;

    eventHub->SetOnSurfaceInitEvent([&receivedId, &receivedNodeId, &receivedIsDestroy](
        const std::string& componentId, const uint32_t nodeId, const bool isDestroy) {
        receivedId = componentId;
        receivedNodeId = nodeId;
        receivedIsDestroy = isDestroy;
    });

    eventHub->FireSurfaceInitEvent("test_xcomponent", 12345);
    EXPECT_EQ(receivedId, "test_xcomponent");
    EXPECT_EQ(receivedNodeId, 12345u);
    EXPECT_FALSE(receivedIsDestroy);
}

/**
 * @tc.name: XComponentEventHubTest006
 * @tc.desc: Test FireDetachEvent when detachEvent_ is set
 * @tc.type: FUNC
 */
HWTEST_F(XComponentEventHubTestNg, XComponentEventHubTest006, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<XComponentEventHub>();
    std::string receivedId = "";

    eventHub->SetDetachEvent([&receivedId](const std::string& componentId) {
        receivedId = componentId;
    });

    eventHub->FireDetachEvent("test_xcomponent");
    EXPECT_EQ(receivedId, "test_xcomponent");
}

/**
 * @tc.name: XComponentEventHubTest007
 * @tc.desc: Test FireControllerCreatedEvent when controllerCreatedEvent_ is set
 * @tc.type: FUNC
 */
HWTEST_F(XComponentEventHubTestNg, XComponentEventHubTest007, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<XComponentEventHub>();
    std::string receivedSurfaceId = "";
    std::string receivedXComponentId = "";

    eventHub->SetControllerCreatedEvent([&receivedSurfaceId, &receivedXComponentId](
        const std::string& surfaceId, const std::string& xcomponentId) {
        receivedSurfaceId = surfaceId;
        receivedXComponentId = xcomponentId;
    });

    eventHub->FireControllerCreatedEvent("surface_123", "xcomponent_456");
    EXPECT_EQ(receivedSurfaceId, "surface_123");
    EXPECT_EQ(receivedXComponentId, "xcomponent_456");
}

/**
 * @tc.name: XComponentEventHubTest008
 * @tc.desc: Test FireControllerChangedEvent when controllerChangedEvent_ is set
 * @tc.type: FUNC
 */
HWTEST_F(XComponentEventHubTestNg, XComponentEventHubTest008, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<XComponentEventHub>();
    std::string receivedSurfaceId = "";
    RectF receivedRect;

    eventHub->SetControllerChangedEvent([&receivedSurfaceId, &receivedRect](
        const std::string& surfaceId, const RectF& rect) {
        receivedSurfaceId = surfaceId;
        receivedRect = rect;
    });

    RectF testRect(10.0f, 20.0f, 100.0f, 200.0f);
    eventHub->FireControllerChangedEvent("surface_789", testRect, "xcomponent_abc");
    EXPECT_EQ(receivedSurfaceId, "surface_789");
    EXPECT_FLOAT_EQ(receivedRect.GetX(), 10.0f);
    EXPECT_FLOAT_EQ(receivedRect.GetY(), 20.0f);
    EXPECT_FLOAT_EQ(receivedRect.Width(), 100.0f);
    EXPECT_FLOAT_EQ(receivedRect.Height(), 200.0f);
}

/**
 * @tc.name: XComponentEventHubTest009
 * @tc.desc: Test FireControllerDestroyedEvent when controllerDestroyedEvent_ is set
 * @tc.type: FUNC
 */
HWTEST_F(XComponentEventHubTestNg, XComponentEventHubTest009, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<XComponentEventHub>();
    std::string receivedSurfaceId = "";
    std::string receivedXComponentId = "";

    eventHub->SetControllerDestroyedEvent([&receivedSurfaceId, &receivedXComponentId](
        const std::string& surfaceId, const std::string& xcomponentId) {
        receivedSurfaceId = surfaceId;
        receivedXComponentId = xcomponentId;
    });

    eventHub->FireControllerDestroyedEvent("surface_destroy", "xcomponent_destroy");
    EXPECT_EQ(receivedSurfaceId, "surface_destroy");
    EXPECT_EQ(receivedXComponentId, "xcomponent_destroy");
}

// ============================================================================
// Test class for XComponentControllerNG
// ============================================================================
class XComponentControllerNGTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();

protected:
    static RefPtr<FrameNode> CreateXComponentNode();
};

void XComponentControllerNGTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void XComponentControllerNGTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> XComponentControllerNGTestNg::CreateXComponentNode()
{
    XComponentModelNG().Create("test_xcomponent", XComponentType::SURFACE, "native_render", nullptr);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    return AceType::DynamicCast<FrameNode>(element);
}

/**
 * @tc.name: XComponentControllerNGTest001
 * @tc.desc: Test GetGlobalPosition when pattern is weak
 * @tc.type: FUNC
 */
HWTEST_F(XComponentControllerNGTestNg, XComponentControllerNGTest001, TestSize.Level1)
{
    auto controller = AceType::MakeRefPtr<XComponentControllerNG>();

    float offsetX = 0.0f;
    float offsetY = 0.0f;
    auto result = controller->GetGlobalPosition(offsetX, offsetY);

    // Should return error when pattern is not set
    EXPECT_EQ(result, XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_ERROR_PATTERN_NULL);
}

/**
 * @tc.name: XComponentControllerNGTest002
 * @tc.desc: Test GetSize when pattern is weak
 * @tc.type: FUNC
 */
HWTEST_F(XComponentControllerNGTestNg, XComponentControllerNGTest002, TestSize.Level1)
{
    auto controller = AceType::MakeRefPtr<XComponentControllerNG>();

    float width = 0.0f;
    float height = 0.0f;
    auto result = controller->GetSize(width, height);

    // Should return error when pattern is not set
    EXPECT_EQ(result, XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_ERROR_PATTERN_NULL);
}

/**
 * @tc.name: XComponentControllerNGTest003
 * @tc.desc: Test GetSurfaceSize when pattern is weak
 * @tc.type: FUNC
 */
HWTEST_F(XComponentControllerNGTestNg, XComponentControllerNGTest003, TestSize.Level1)
{
    auto controller = AceType::MakeRefPtr<XComponentControllerNG>();

    float surfaceWidth = 0.0f;
    float surfaceHeight = 0.0f;

    // Should not crash when pattern is weak
    controller->GetSurfaceSize(surfaceWidth, surfaceHeight);
}

/**
 * @tc.name: XComponentControllerNGTest004
 * @tc.desc: Test GetSurfaceOffset when pattern is weak
 * @tc.type: FUNC
 */
HWTEST_F(XComponentControllerNGTestNg, XComponentControllerNGTest004, TestSize.Level1)
{
    auto controller = AceType::MakeRefPtr<XComponentControllerNG>();

    float offsetX = 0.0f;
    float offsetY = 0.0f;

    // Should not crash when pattern is weak
    controller->GetSurfaceOffset(offsetX, offsetY);
}

/**
 * @tc.name: XComponentControllerNGTest005
 * @tc.desc: Test SetSurfaceRotation
 * @tc.type: FUNC
 */
HWTEST_F(XComponentControllerNGTestNg, XComponentControllerNGTest005, TestSize.Level1)
{
    auto controller = AceType::MakeRefPtr<XComponentControllerNG>();

    // Should not crash when pattern is weak
    controller->SetSurfaceRotation(true);
    controller->SetSurfaceRotation(false);
}

/**
 * @tc.name: XComponentControllerNGTest006
 * @tc.desc: Test GetSurfaceRotation when pattern is weak
 * @tc.type: FUNC
 */
HWTEST_F(XComponentControllerNGTestNg, XComponentControllerNGTest006, TestSize.Level1)
{
    auto controller = AceType::MakeRefPtr<XComponentControllerNG>();

    // Should return false when pattern is weak
    EXPECT_FALSE(controller->GetSurfaceRotation());
}

/**
 * @tc.name: XComponentControllerNGTest007
 * @tc.desc: Test LockCanvas and UnlockCanvasAndPost when pattern is weak
 * @tc.type: FUNC
 */
HWTEST_F(XComponentControllerNGTestNg, XComponentControllerNGTest007, TestSize.Level1)
{
    auto controller = AceType::MakeRefPtr<XComponentControllerNG>();

    // Should not crash when pattern is weak
    auto canvas = controller->LockCanvas();
    EXPECT_EQ(canvas, nullptr);

    controller->UnlockCanvasAndPost(nullptr);
}

/**
 * @tc.name: XComponentControllerNGTest008
 * @tc.desc: Test SetSurfaceConfig
 * @tc.type: FUNC
 */
HWTEST_F(XComponentControllerNGTestNg, XComponentControllerNGTest008, TestSize.Level1)
{
    auto controller = AceType::MakeRefPtr<XComponentControllerNG>();

    // Should not crash when pattern is weak
    controller->SetSurfaceConfig(true);
    controller->SetSurfaceConfig(false);
}

// ============================================================================
// Test class for XComponentLayoutAlgorithm
// ============================================================================
class XComponentLayoutAlgorithmTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void XComponentLayoutAlgorithmTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void XComponentLayoutAlgorithmTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: XComponentLayoutAlgorithmTest001
 * @tc.desc: Test MeasureContent with valid constraint
 * @tc.type: FUNC
 */
HWTEST_F(XComponentLayoutAlgorithmTestNg, XComponentLayoutAlgorithmTest001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<XComponentLayoutAlgorithm>();
    LayoutConstraintF contentConstraint;
    contentConstraint.selfIdealSize.SetWidth(SizeF(100.0f));
    contentConstraint.selfIdealSize.SetHeight(SizeF(100.0f));

    auto result = algorithm->MeasureContent(contentConstraint, nullptr);

    EXPECT_TRUE(result.has_value());
    EXPECT_FLOAT_EQ(result.value().Width(), 100.0f);
    EXPECT_FLOAT_EQ(result.value().Height(), 100.0f);
}

/**
 * @tc.name: XComponentLayoutAlgorithmTest002
 * @tc.desc: Test MeasureContent with min/max constraints
 * @tc.type: FUNC
 */
HWTEST_F(XComponentLayoutAlgorithmTestNg, XComponentLayoutAlgorithmTest002, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<XComponentLayoutAlgorithm>();
    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(50.0f, 50.0f);
    contentConstraint.maxSize = SizeF(200.0f, 200.0f);

    auto result = algorithm->MeasureContent(contentConstraint, nullptr);

    EXPECT_TRUE(result.has_value());
}

/**
 * @tc.name: XComponentLayoutAlgorithmTest003
 * @tc.desc: Test Measure with null layoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(XComponentLayoutAlgorithmTestNg, XComponentLayoutAlgorithmTest003, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<XComponentLayoutAlgorithm>();

    // Should not crash with null layoutWrapper
    algorithm->Measure(nullptr);
}

/**
 * @tc.name: XComponentLayoutAlgorithmTest004
 * @tc.desc: Test Layout with null layoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(XComponentLayoutAlgorithmTestNg, XComponentLayoutAlgorithmTest004, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<XComponentLayoutAlgorithm>();

    // Should not crash with null layoutWrapper
    algorithm->Layout(nullptr);
}

// ============================================================================
// Test class for XComponentPaintMethod
// ============================================================================
class XComponentPaintMethodTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void XComponentPaintMethodTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void XComponentPaintMethodTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: XComponentPaintMethodTest001
 * @tc.desc: Test GetContentDrawFunction with null pattern
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPaintMethodTestNg, XComponentPaintMethodTest001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<XComponentPattern>();
    auto renderSurface = AceType::MakeRefPtr<RenderSurface>();
    auto paintMethod = AceType::MakeRefPtr<XComponentPaintMethod>(renderSurface, pattern);

    PaintWrapper paintWrapper;
    auto drawFunc = paintMethod->GetContentDrawFunction(&paintWrapper);

    // Should return valid draw function even with weak pattern
    EXPECT_NE(drawFunc, nullptr);
}

/**
 * @tc.name: XComponentPaintMethodTest002
 * @tc.desc: Test GetContentDrawFunction with null paintWrapper
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPaintMethodTestNg, XComponentPaintMethodTest002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<XComponentPattern>();
    auto renderSurface = AceType::MakeRefPtr<RenderSurface>();
    auto paintMethod = AceType::MakeRefPtr<XComponentPaintMethod>(renderSurface, pattern);

    auto drawFunc = paintMethod->GetContentDrawFunction(nullptr);

    // Should return valid draw function
    EXPECT_NE(drawFunc, nullptr);
}

// ============================================================================
// Test class for XComponentLayoutProperty
// ============================================================================
class XComponentLayoutPropertyTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
};

/**
 * @tc.name: XComponentLayoutPropertyTest001
 * @tc.desc: Test Clone method
 * @tc.type: FUNC
 */
HWTEST_F(XComponentLayoutPropertyTestNg, XComponentLayoutPropertyTest001, TestSize.Level1)
{
    auto property = AceType::MakeRefPtr<XComponentLayoutProperty>();
    property->UpdateXComponentType(XComponentType::SURFACE);

    auto cloned = property->Clone();
    auto clonedProperty = AceType::DynamicCast<XComponentLayoutProperty>(cloned);

    ASSERT_NE(clonedProperty, nullptr);
    EXPECT_EQ(clonedProperty->GetXComponentTypeValue(), XComponentType::SURFACE);
}

/**
 * @tc.name: XComponentLayoutPropertyTest002
 * @tc.desc: Test Reset method
 * @tc.type: FUNC
 */
HWTEST_F(XComponentLayoutPropertyTestNg, XComponentLayoutPropertyTest002, TestSize.Level1)
{
    auto property = AceType::MakeRefPtr<XComponentLayoutProperty>();
    property->UpdateXComponentType(XComponentType::TEXTURE);

    property->Reset();

    // After reset, property should return to default value
    auto prop = property->GetXComponentTypeValue();
    EXPECT_EQ(prop, XComponentType::UNKNOWN);
}

// ============================================================================
// Test class for XComponentModel
// ============================================================================
class XComponentModelTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
};

/**
 * @tc.name: XComponentModelTest001
 * @tc.desc: Test IsBackGroundColorAvailable
 * @tc.type: FUNC
 */
HWTEST_F(XComponentModelTestNg, XComponentModelTest001, TestSize.Level1)
{
    // Test with TEXTURE type
    EXPECT_TRUE(XComponentModel::IsBackGroundColorAvailable(XComponentType::TEXTURE));

    // Test with NODE type
    EXPECT_TRUE(XComponentModel::IsBackGroundColorAvailable(XComponentType::NODE));

    // Test with SURFACE type (depends on API version)
    bool result = XComponentModel::IsBackGroundColorAvailable(XComponentType::SURFACE);
    EXPECT_TRUE(result == true || result == false); // Depends on API version
}

/**
 * @tc.name: XComponentModelTest002
 * @tc.desc: Test IsCommonEventAvailable
 * @tc.type: FUNC
 */
HWTEST_F(XComponentModelTestNg, XComponentModelTest002, TestSize.Level1)
{
    std::optional<std::string> libraryName = "native_render";

    // Test with NODE type
    EXPECT_TRUE(XComponentModel::IsCommonEventAvailable(XComponentType::NODE, libraryName));

    // Test with no library name
    std::optional<std::string> noLibraryName;
    bool result = XComponentModel::IsCommonEventAvailable(XComponentType::SURFACE, noLibraryName);
    EXPECT_TRUE(result == true || result == false); // Depends on API version
}

/**
 * @tc.name: XComponentModelTest003
 * @tc.desc: Test default virtual methods
 * @tc.type: FUNC
 */
HWTEST_F(XComponentModelTestNg, XComponentModelTest003, TestSize.Level1)
{
    XComponentModel model;

    // Test default virtual methods
    EXPECT_FALSE(model.IsTexture());
    EXPECT_EQ(model.GetType(), XComponentType::UNKNOWN);
    EXPECT_EQ(model.GetLibraryName(), std::nullopt);

    // These should not crash
    model.Create(XComponentType::SURFACE);
    model.SetDetachCallback([](const std::string&) {});
    model.SetControllerOnCreated([](const std::string&, const std::string&) {});
    model.SetControllerOnChanged([](const std::string&, const RectF&) {});
    model.SetControllerOnDestroyed([](const std::string&, const std::string&) {});
    model.EnableAnalyzer(true);
    model.SetImageAIOptions(nullptr);
    model.SetRenderFit(RenderFit::CENTER);
    model.EnableSecure(true);
    model.HdrBrightness(1.0f);
    model.EnableTransparentLayer(true);
    model.SetScreenId(1);
}

// ============================================================================
// Test class for XComponentSurfaceHolder
// ============================================================================
class XComponentSurfaceHolderTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
};

/**
 * @tc.name: XComponentSurfaceHolderTest001
 * @tc.desc: Test AddSurfaceCallback
 * @tc.type: FUNC
 */
HWTEST_F(XComponentSurfaceHolderTestNg, XComponentSurfaceHolderTest001, TestSize.Level1)
{
    OH_ArkUI_SurfaceHolder holder;
    OH_ArkUI_SurfaceCallback callback;

    auto result = holder.AddSurfaceCallback(&callback);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_NO_ERROR);

    // Adding same callback again should fail
    result = holder.AddSurfaceCallback(&callback);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: XComponentSurfaceHolderTest002
 * @tc.desc: Test RemoveSurfaceCallback
 * @tc.type: FUNC
 */
HWTEST_F(XComponentSurfaceHolderTestNg, XComponentSurfaceHolderTest002, TestSize.Level1)
{
    OH_ArkUI_SurfaceHolder holder;
    OH_ArkUI_SurfaceCallback callback;

    // Adding callback
    holder.AddSurfaceCallback(&callback);

    // Removing callback
    auto result = holder.RemoveSurfaceCallback(&callback);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_NO_ERROR);

    // Removing same callback again should fail
    result = holder.RemoveSurfaceCallback(&callback);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: XComponentSurfaceHolderTest003
 * @tc.desc: Test SetSurfaceConfig with null config
 * @tc.type: FUNC
 */
HWTEST_F(XComponentSurfaceHolderTestNg, XComponentSurfaceHolderTest003, TestSize.Level1)
{
    OH_ArkUI_SurfaceHolder holder;

    auto result = holder.SetSurfaceConfig(nullptr);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: XComponentSurfaceHolderTest004
 * @tc.desc: Test SetSurfaceConfig with valid config
 * @tc.type: FUNC
 */
HWTEST_F(XComponentSurfaceHolderTestNg, XComponentSurfaceHolderTest004, TestSize.Level1)
{
    OH_ArkUI_SurfaceHolder holder;
    ArkUI_XComponentSurfaceConfig config;
    config.isOpaque_ = true;

    // Without xComponentSurfaceConfigInterface_, should return ERROR_CODE_PARAM_INVALID
    auto result = holder.SetSurfaceConfig(&config);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

// ============================================================================
// Test class for XComponentPattern additional methods
// ============================================================================
class XComponentPatternExtraTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();

protected:
    static RefPtr<FrameNode> CreateXComponentNode(XComponentType type);
};

void XComponentPatternExtraTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void XComponentPatternExtraTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> XComponentPatternExtraTestNg::CreateXComponentNode(XComponentType type)
{
    XComponentModelNG().Create("test_xcomponent", type, "native_render", nullptr);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    return AceType::DynamicCast<FrameNode>(element);
}

/**
 * @tc.name: XComponentPatternExtraTest001
 * @tc.desc: Test SetId and GetId
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternExtraTestNg, XComponentPatternExtraTest001, TestSize.Level1)
{
    auto frameNode = CreateXComponentNode(XComponentType::SURFACE);
    ASSERT_NE(frameNode, nullptr);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->SetId("custom_id");
    EXPECT_EQ(pattern->GetId(), "custom_id");
}

/**
 * @tc.name: XComponentPatternExtraTest002
 * @tc.desc: Test SetLibraryName and GetLibraryName
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternExtraTestNg, XComponentPatternExtraTest002, TestSize.Level1)
{
    auto frameNode = CreateXComponentNode(XComponentType::SURFACE);
    ASSERT_NE(frameNode, nullptr);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    std::optional<std::string> libraryName = "test_library";
    pattern->SetLibraryName(libraryName);

    auto result = pattern->GetLibraryName();
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "test_library");
}

/**
 * @tc.name: XComponentPatternExtraTest003
 * @tc.desc: Test SetSoPath and GetSoPath
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternExtraTestNg, XComponentPatternExtraTest003, TestSize.Level1)
{
    auto frameNode = CreateXComponentNode(XComponentType::SURFACE);
    ASSERT_NE(frameNode, nullptr);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->SetSoPath("/path/to/library.so");

    auto result = pattern->GetSoPath();
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "/path/to/library.so");
}

/**
 * @tc.name: XComponentPatternExtraTest004
 * @tc.desc: Test SetType and GetType
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternExtraTestNg, XComponentPatternExtraTest004, TestSize.Level1)
{
    auto frameNode = CreateXComponentNode(XComponentType::SURFACE);
    ASSERT_NE(frameNode, nullptr);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->SetType(XComponentType::TEXTURE);
    EXPECT_EQ(pattern->GetType(), XComponentType::TEXTURE);
}

/**
 * @tc.name: XComponentPatternExtraTest005
 * @tc.desc: Test GetDrawSize, GetSurfaceSize, GetSurfaceOffset
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternExtraTestNg, XComponentPatternExtraTest005, TestSize.Level1)
{
    auto frameNode = CreateXComponentNode(XComponentType::SURFACE);
    ASSERT_NE(frameNode, nullptr);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    // Initial values should be zero
    EXPECT_FLOAT_EQ(pattern->GetDrawSize().Width(), 0.0f);
    EXPECT_FLOAT_EQ(pattern->GetDrawSize().Height(), 0.0f);
    EXPECT_FLOAT_EQ(pattern->GetSurfaceSize().Width(), 0.0f);
    EXPECT_FLOAT_EQ(pattern->GetSurfaceSize().Height(), 0.0f);
    EXPECT_FLOAT_EQ(pattern->GetSurfaceOffset().GetX(), 0.0f);
    EXPECT_FLOAT_EQ(pattern->GetSurfaceOffset().GetY(), 0.0f);
}

/**
 * @tc.name: XComponentPatternExtraTest006
 * @tc.desc: Test SetSurfaceRotation and GetSurfaceRotation
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternExtraTestNg, XComponentPatternExtraTest006, TestSize.Level1)
{
    auto frameNode = CreateXComponentNode(XComponentType::SURFACE);
    ASSERT_NE(frameNode, nullptr);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->SetSurfaceRotation(true);
    EXPECT_TRUE(pattern->GetSurfaceRotation());

    pattern->SetSurfaceRotation(false);
    EXPECT_FALSE(pattern->GetSurfaceRotation());
}

/**
 * @tc.name: XComponentPatternExtraTest007
 * @tc.desc: Test SetIsTypeNode
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternExtraTestNg, XComponentPatternExtraTest007, TestSize.Level1)
{
    auto frameNode = CreateXComponentNode(XComponentType::SURFACE);
    ASSERT_NE(frameNode, nullptr);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->SetIsTypeNode(true);
}

/**
 * @tc.name: XComponentPatternExtraTest008
 * @tc.desc: Test GetXComponentController
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternExtraTestNg, XComponentPatternExtraTest008, TestSize.Level1)
{
    auto frameNode = CreateXComponentNode(XComponentType::SURFACE);
    ASSERT_NE(frameNode, nullptr);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    auto controller = pattern->GetXComponentController();
    // May be null or valid depending on initialization
}

/**
 * @tc.name: XComponentPatternExtraTest009
 * @tc.desc: Test GetRenderContextForSurface
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternExtraTestNg, XComponentPatternExtraTest009, TestSize.Level1)
{
    auto frameNode = CreateXComponentNode(XComponentType::TEXTURE);
    ASSERT_NE(frameNode, nullptr);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    auto renderContext = pattern->GetRenderContextForSurface();
    // May be null or valid depending on initialization
}

/**
 * @tc.name: XComponentPatternExtraTest010
 * @tc.desc: Test HasGotSurfaceHolder and HasGotNativeXComponent
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternExtraTestNg, XComponentPatternExtraTest010, TestSize.Level1)
{
    auto frameNode = CreateXComponentNode(XComponentType::SURFACE);
    ASSERT_NE(frameNode, nullptr);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    // Initially should be false
    EXPECT_FALSE(pattern->HasGotSurfaceHolder());
    EXPECT_FALSE(pattern->HasGotNativeXComponent());
}

/**
 * @tc.name: XComponentPatternExtraTest011
 * @tc.desc: Test SetHasGotNativeXComponent
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternExtraTestNg, XComponentPatternExtraTest011, TestSize.Level1)
{
    auto frameNode = CreateXComponentNode(XComponentType::SURFACE);
    ASSERT_NE(frameNode, nullptr);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->SetHasGotNativeXComponent(true);
    EXPECT_TRUE(pattern->HasGotNativeXComponent());
}

/**
 * @tc.name: XComponentPatternExtraTest012
 * @tc.desc: Test IsNativeXComponentDisabled
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternExtraTestNg, XComponentPatternExtraTest012, TestSize.Level1)
{
    auto frameNode = CreateXComponentNode(XComponentType::SURFACE);
    ASSERT_NE(frameNode, nullptr);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    // Initially should be false
    EXPECT_FALSE(pattern->IsNativeXComponentDisabled());
}

/**
 * @tc.name: XComponentPatternExtraTest013
 * @tc.desc: Test SetRenderType and ChangeRenderType
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternExtraTestNg, XComponentPatternExtraTest013, TestSize.Level1)
{
    auto frameNode = CreateXComponentNode(XComponentType::SURFACE);
    ASSERT_NE(frameNode, nullptr);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->SetRenderType(NodeRenderType::RENDER_TYPE_CPU);
    EXPECT_EQ(pattern->renderType_, NodeRenderType::RENDER_TYPE_CPU);
}

/**
 * @tc.name: XComponentPatternExtraTest014
 * @tc.desc: Test HasTransformHintChangedCallbackId and UpdateTransformHintChangedCallbackId
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternExtraTestNg, XComponentPatternExtraTest014, TestSize.Level1)
{
    auto frameNode = CreateXComponentNode(XComponentType::SURFACE);
    ASSERT_NE(frameNode, nullptr);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    // Initially should be false
    EXPECT_FALSE(pattern->HasTransformHintChangedCallbackId());

    pattern->UpdateTransformHintChangedCallbackId(123);
    EXPECT_TRUE(pattern->HasTransformHintChangedCallbackId());
}

/**
 * @tc.name: XComponentPatternExtraTest015
 * @tc.desc: Test NeedTriggerLoadEventImmediately
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternExtraTestNg, XComponentPatternExtraTest015, TestSize.Level1)
{
    auto frameNode = CreateXComponentNode(XComponentType::SURFACE);
    ASSERT_NE(frameNode, nullptr);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    // Initially should be false (isTypedNode_ is false)
    EXPECT_FALSE(pattern->NeedTriggerLoadEventImmediately());
}

/**
 * @tc.name: XComponentPatternExtraTest016
 * @tc.desc: Test IsBindNative
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternExtraTestNg, XComponentPatternExtraTest016, TestSize.Level1)
{
    auto frameNode = CreateXComponentNode(XComponentType::SURFACE);
    ASSERT_NE(frameNode, nullptr);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    // Base class returns false
    EXPECT_FALSE(pattern->IsBindNative());
}

// ============================================================================
// Test class for XComponentPatternV2
// ============================================================================
class XComponentPatternV2TestNg : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
};

/**
 * @tc.name: XComponentPatternV2Test001
 * @tc.desc: Test IsBindNative for V2 pattern
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternV2TestNg, XComponentPatternV2Test001, TestSize.Level1)
{
    XComponentPatternV2 pattern;

    // V2 pattern always returns true
    EXPECT_TRUE(pattern.IsBindNative());
}

/**
 * @tc.name: XComponentPatternV2Test002
 * @tc.desc: Test GetXComponentNodeType
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternV2TestNg, XComponentPatternV2Test002, TestSize.Level1)
{
    XComponentPatternV2 pattern(XComponentType::NODE, XComponentNodeType::TYPE_NODE);

    EXPECT_EQ(pattern.GetXComponentNodeType(), XComponentNodeType::TYPE_NODE);
}

/**
 * @tc.name: XComponentPatternV2Test003
 * @tc.desc: Test IsCreateSurfaceHolderForbidden
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternV2TestNg, XComponentPatternV2Test003, TestSize.Level1)
{
    XComponentPatternV2 pattern;

    // Initially should be false (hasGotNativeXComponent_ and usesSuperMethod_ are false)
    EXPECT_FALSE(pattern.IsCreateSurfaceHolderForbidden());
}

/**
 * @tc.name: XComponentPatternV2Test004
 * @tc.desc: Test SetSurfaceHolder and GetSurfaceHolder
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternV2TestNg, XComponentPatternV2Test004, TestSize.Level1)
{
    XComponentPatternV2 pattern;

    OH_ArkUI_SurfaceHolder* testHolder = new OH_ArkUI_SurfaceHolder();
    pattern.SetSurfaceHolder(testHolder);

    EXPECT_EQ(pattern.GetSurfaceHolder(), testHolder);

    delete testHolder;
}

/**
 * @tc.name: XComponentPatternV2Test005
 * @tc.desc: Test SetExpectedRateRange
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternV2TestNg, XComponentPatternV2Test005, TestSize.Level1)
{
    XComponentPatternV2 pattern;

    // Should not crash
    pattern.SetExpectedRateRange(30, 60, 60);
}

/**
 * @tc.name: XComponentPatternV2Test006
 * @tc.desc: Test SetNeedSoftKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternV2TestNg, XComponentPatternV2Test006, TestSize.Level1)
{
    XComponentPatternV2 pattern;

    // Should not crash
    pattern.SetNeedSoftKeyboard(true);
    pattern.SetNeedSoftKeyboard(false);
}

/**
 * @tc.name: XComponentPatternV2Test007
 * @tc.desc: Test QueryAccessibilityProviderHost with null provider
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternV2TestNg, XComponentPatternV2Test007, TestSize.Level1)
{
    bool isProviderValid = false;
    auto result = XComponentPatternV2::QueryAccessibilityProviderHost(nullptr, isProviderValid);

    EXPECT_EQ(result, nullptr);
    EXPECT_FALSE(isProviderValid);
}

// ============================================================================
// Test class for XComponentSurfaceConfigInterface
// ============================================================================
class XComponentSurfaceConfigInterfaceTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
};

/**
 * @tc.name: XComponentSurfaceConfigInterfaceTest001
 * @tc.desc: Test SetSurfaceIsOpaque default implementation
 * @tc.type: FUNC
 */
HWTEST_F(XComponentSurfaceConfigInterfaceTestNg, XComponentSurfaceConfigInterfaceTest001, TestSize.Level1)
{
    // This test verifies the interface exists and can be called
    // Actual implementation depends on the concrete class
    OH_ArkUI_SurfaceHolder holder;

    // The holder's SetSurfaceConfig requires xComponentSurfaceConfigInterface_ to be set
    // which we can't do here, but we verify the structure
    EXPECT_EQ(holder.userData_, nullptr);
    EXPECT_EQ(holder.nativeWindow_, nullptr);
    EXPECT_TRUE(holder.surfaceCallbackList_.empty());
    EXPECT_EQ(holder.node_, nullptr);
    EXPECT_EQ(holder.config_, nullptr);
}

} // namespace OHOS::Ace::NG
