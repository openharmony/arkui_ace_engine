/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/components_ng/property/measure_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/touch_event.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_ext_surface_callback_client.h"
#include "frameworks/core/gestures/press_recognizer.h"
#include "frameworks/core/components_ng/pattern/node_container/node_container_pattern.h"

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
const std::string XCOMPONENT_ID = "xcomponent";
const std::string XCOMPONENT_LIBRARY_NAME = "native_render";
const std::string XCOMPONENT_SO_PATH = "com.example.xcomponentmultihap/entry";
const uint64_t XCOMPONENT_SCREEN_ID = 12345u;
constexpr XComponentType XCOMPONENT_SURFACE_TYPE_VALUE = XComponentType::SURFACE;
constexpr XComponentType XCOMPONENT_TEXTURE_TYPE_VALUE = XComponentType::TEXTURE;
constexpr XComponentType XCOMPONENT_COMPONENT_TYPE_VALUE = XComponentType::COMPONENT;
constexpr float MAX_WIDTH = 400.0f;
constexpr float MAX_HEIGHT = 400.0f;
constexpr uint32_t SURFACE_WIDTH_SIZE = 200;
constexpr uint32_t SURFACE_HEIGHT_SIZE = 250;
constexpr float OFFSET_X = 10;
constexpr float OFFSET_Y = 10;
const SizeF MAX_SIZE(MAX_WIDTH, MAX_HEIGHT);
const RectF MAX_SURFACE_RECT(0, 0, MAX_WIDTH, MAX_HEIGHT);
ArkUI_XComponent_Params params;
TestProperty g_testProperty;
} // namespace

class XComponentTestTwoNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();

protected:
    static RefPtr<FrameNode> CreateXComponentNode(TestProperty& testProperty);
};

void XComponentTestTwoNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    g_testProperty.xcId = XCOMPONENT_ID;
    g_testProperty.libraryName = XCOMPONENT_LIBRARY_NAME;
    g_testProperty.soPath = XCOMPONENT_SO_PATH;
}

void XComponentTestTwoNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void processImage(ImageAnalyzerState state) {}

void processPixelMap(const RefPtr<PixelMap>& pixelMap) {}

RefPtr<FrameNode> XComponentTestTwoNg::CreateXComponentNode(TestProperty& testProperty)
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
 * @tc.name: DumpInfoTest
 * @tc.desc: Test DumpInfo Func.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestTwoNg, DumpInfoTest, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    pattern->SetType(XComponentType::COMPONENT);
    pattern->DumpInfo();
    EXPECT_EQ(pattern->GetType(), XComponentType::COMPONENT);

    pattern->SetType(XComponentType::NODE);
    pattern->DumpInfo();
    EXPECT_EQ(pattern->GetType(), XComponentType::NODE);

    pattern->SetType(XComponentType::SURFACE);
    pattern->DumpInfo();
    EXPECT_EQ(pattern->GetType(), XComponentType::SURFACE);

    pattern->SetType(XComponentType::TEXTURE);
    pattern->DumpInfo();
    EXPECT_EQ(pattern->GetType(), XComponentType::TEXTURE);

    pattern->SetType(XComponentType::UNKNOWN);
    pattern->DumpInfo();
    EXPECT_EQ(pattern->GetType(), XComponentType::UNKNOWN);

    pattern->SetType(static_cast<XComponentType>(-2));
    pattern->DumpInfo();
    EXPECT_EQ(pattern->GetType(), static_cast<XComponentType>(-2));
}

/**
 * @tc.name: RoundValueToPixelGridTest
 * @tc.desc: Test RoundValueToPixelGrid Func.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestTwoNg, RoundValueToPixelGridTest, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    float value = 1.0f;
    float ret = pattern->RoundValueToPixelGrid(value, true, true, true);
    EXPECT_EQ(ret, 2.0f);

    value = 1.5f;
    ret = pattern->RoundValueToPixelGrid(value, true, false, false);
    EXPECT_EQ(ret, 2.0f);

    value = -1.6f;
    ret = pattern->RoundValueToPixelGrid(value, true, false, false);
    EXPECT_EQ(ret, -2.0f);

    value = 1.0f;
    ret = pattern->RoundValueToPixelGrid(value, false, false, false);
    EXPECT_EQ(ret, 1.0f);
}

/**
 * @tc.name: OnModifyDoneTest
 * @tc.desc: Test OnModifyDone Func.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestTwoNg, OnModifyDoneTest, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    auto host = pattern->GetHost();
    ASSERT_TRUE(host);

    auto renderContext = host->GetRenderContext();
    ASSERT_TRUE(renderContext);
    renderContext->propBackgroundColor_ = Color::TRANSPARENT;
    pattern->OnModifyDone();
    EXPECT_EQ(pattern->handlingSurfaceRenderContext_->GetBackgroundColor(), Color::TRANSPARENT);

    renderContext->propBackgroundColor_ = Color::BLUE;
    pattern->OnModifyDone();
    EXPECT_EQ(pattern->handlingSurfaceRenderContext_->GetBackgroundColor(), Color::BLUE);

    renderContext->propBackgroundColor_ = Color::BLACK;
    pattern->OnModifyDone();
    EXPECT_EQ(pattern->handlingSurfaceRenderContext_->GetBackgroundColor(), Color::BLACK);
}

/**
 * @tc.name: BeforeSyncGeometryPropertiesTest
 * @tc.desc: Test BeforeSyncGeometryProperties Func.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestTwoNg, BeforeSyncGeometryPropertiesTest, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_TEXTURE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    DirtySwapConfig config;
    auto xComponentLayoutAlgorithm = AceType::MakeRefPtr<XComponentLayoutAlgorithm>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(MAX_SIZE);
    geometryNode->SetContentSize(MAX_SIZE);
    frameNode->geometryNode_ = geometryNode;
    pattern->hasXComponentInit_ = false;
    pattern->isEnableAnalyzer_ = true;
    auto imageAnalyzerManager =
        std::make_shared<MockImageAnalyzerManager>(frameNode, ImageAnalyzerHolder::XCOMPONENT);
    bool extSurfaceEnabled = SystemProperties::extSurfaceEnabled_;
    SystemProperties::extSurfaceEnabled_ = true;
    imageAnalyzerManager->SetSupportImageAnalyzerFeature(true);
    pattern->imageAnalyzerManager_ = imageAnalyzerManager;
    pattern->BeforeSyncGeometryProperties(config);
    EXPECT_TRUE(pattern->hasXComponentInit_);
    SystemProperties::extSurfaceEnabled_ = extSurfaceEnabled;
}

/**
 * @tc.name: SetHandlingRenderContextForSurfaceTest
 * @tc.desc: Test SetHandlingRenderContextForSurface Func.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestTwoNg, SetHandlingRenderContextForSurfaceTest, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto xComponentController = std::make_shared<XComponentControllerNG>();
    XComponentModelNG xComponent;
    xComponent.Create(XCOMPONENT_ID, XCOMPONENT_SURFACE_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME, xComponentController);
    xComponent.SetSoPath(XCOMPONENT_SO_PATH);

    auto extXComponentController = std::make_shared<XComponentControllerNG>();
    XComponentModelNG extXComponent;
    extXComponent.Create(
        XCOMPONENT_ID, XCOMPONENT_SURFACE_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME, extXComponentController);
    extXComponent.SetSoPath(XCOMPONENT_SO_PATH);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::XCOMPONENT_ETS_TAG);

    auto result = xComponentController->SetExtController(extXComponentController);
    EXPECT_EQ(result, XCOMPONENT_CONTROLLER_NO_ERROR);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(backupApiVersion));
}

/**
 * @tc.name: SetExtControllerTest
 * @tc.desc: Test SetExtController Func.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestTwoNg, SetExtControllerTest, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    auto result = pattern->SetExtController(nullptr);
    EXPECT_EQ(result, XCOMPONENT_CONTROLLER_BAD_PARAMETER);

    auto extFrameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(extFrameNode);
    auto extPattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(extPattern);

    pattern->extPattern_ = AceType::WeakClaim(AceType::RawPtr(extPattern));
    result = pattern->SetExtController(extPattern);
    EXPECT_EQ(result, XCOMPONENT_CONTROLLER_REPEAT_SET);
}

/**
 * @tc.name: ResetExtControllerTest
 * @tc.desc: Test ResetExtController Func.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestTwoNg, ResetExtControllerTest, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    auto result = pattern->ResetExtController(nullptr);
    EXPECT_EQ(result, XCOMPONENT_CONTROLLER_BAD_PARAMETER);

    auto extFrameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(extFrameNode);

    auto extPattern = extFrameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(extPattern);

    result = pattern->ResetExtController(extPattern);
    EXPECT_EQ(result, XCOMPONENT_CONTROLLER_RESET_ERROR);

    g_testProperty.xcType = XCOMPONENT_TEXTURE_TYPE_VALUE;
    auto frameNodeTmp = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNodeTmp);
    pattern->extPattern_ = AceType::WeakClaim(AceType::RawPtr(pattern));
    auto patternTmp = frameNodeTmp->GetPattern<XComponentPattern>();
    ASSERT_TRUE(patternTmp);
    result = pattern->ResetExtController(patternTmp);
    EXPECT_EQ(result, XCOMPONENT_CONTROLLER_RESET_ERROR);
}

/**
 * @tc.name: HandleSurfaceChangeEventTest
 * @tc.desc: Test HandleSurfaceChangeEvent Func.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestTwoNg, HandleSurfaceChangeEventTest, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto xComponentController = std::make_shared<XComponentControllerNG>();
    XComponentModelNG xComponent;
    xComponent.Create(XCOMPONENT_ID, XCOMPONENT_SURFACE_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME, xComponentController);
    xComponent.SetSoPath(XCOMPONENT_SO_PATH);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::XCOMPONENT_ETS_TAG);

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
    pattern->BeforeSyncGeometryProperties(config);
    EXPECT_TRUE(pattern->hasXComponentInit_);
    EXPECT_TRUE(AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(backupApiVersion));
}

/**
 * @tc.name: UpdateSurfaceRectTest
 * @tc.desc: Test UpdateSurfaceRect Func.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestTwoNg, UpdateSurfaceRectTest, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_TEXTURE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    pattern->drawSize_ = SizeF(0.0f, 0.0f);
    auto ret = pattern->UpdateSurfaceRect();
    std::tuple<bool, bool, bool> result(false, false, false);
    EXPECT_EQ(ret, result);
}

/**
 * @tc.name: StartImageAnalyzerTest
 * @tc.desc: Test StartImageAnalyzer Func.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestTwoNg, StartImageAnalyzerTest, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_TEXTURE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    std::optional<std::function<void(ImageAnalyzerState)>> callback;
    callback = processImage;
    pattern->isEnableAnalyzer_ = true;
    auto imageAnalyzerManager =
        std::make_shared<MockImageAnalyzerManager>(frameNode, ImageAnalyzerHolder::XCOMPONENT);
    bool extSurfaceEnabled = SystemProperties::extSurfaceEnabled_;
    SystemProperties::extSurfaceEnabled_ = true;
    imageAnalyzerManager->SetSupportImageAnalyzerFeature(true);
    pattern->imageAnalyzerManager_ = imageAnalyzerManager;

    pattern->StartImageAnalyzer(nullptr, callback);
    ASSERT_TRUE(pattern->IsSupportImageAnalyzerFeature());

    pattern->isEnableAnalyzer_ = false;
    pattern->StartImageAnalyzer(nullptr, callback);
    ASSERT_FALSE(pattern->IsSupportImageAnalyzerFeature());
    SystemProperties::extSurfaceEnabled_ = extSurfaceEnabled;
}

/**
 * @tc.name: ChangeSurfaceCallbackModeTest
 * @tc.desc: Test ChangeSurfaceCallbackMode.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestTwoNg, ChangeSurfaceCallbackModeTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set surface life cycle callback, set id&libraryname to null and create XComponent
     * @tc.expected: xcomponent frameNode create successfully
     */
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    g_testProperty.xcId = std::nullopt;
    g_testProperty.libraryName = std::nullopt;
    int32_t onSurfaceCreatedSurfaceCount = 0;
    int32_t onSurfaceDestroyedSurfaceCount = 0;
    auto onSurfaceCreated = [&onSurfaceCreatedSurfaceCount](const std::string& surfaceId, const std::string& xcId) {
        ++onSurfaceCreatedSurfaceCount;
    };
    auto onSurfaceDestroyed = [&onSurfaceDestroyedSurfaceCount](const std::string& surfaceId, const std::string& xcId) {
        ++onSurfaceDestroyedSurfaceCount;
    };
    g_testProperty.surfaceCreatedEvent = std::move(onSurfaceCreated);
    g_testProperty.surfaceDestroyedEvent = std::move(onSurfaceDestroyed);
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    pattern->isTypedNode_ = true;
    pattern->RegisterSurfaceCallbackModeEvent();
    EXPECT_EQ(pattern->surfaceCallbackMode_, SurfaceCallbackMode::DEFAULT);

    /**
     * @tc.steps: step2. attachTo&detachFrom main tree in DEFAULT mode
     * @tc.expected: DEFAULT mode attach to(detach from) main tree will call onSurfaceCreated(onSurfaceDestroyed) once
     */
    frameNode->AttachToMainTree(false);
    EXPECT_EQ(onSurfaceCreatedSurfaceCount, 1);
    frameNode->DetachFromMainTree();
    EXPECT_EQ(onSurfaceDestroyedSurfaceCount, 1);

    /**
     * @tc.steps: step3. detachFromFrameNode(in frameNode's destructor) in DEFAULT mode
     * @tc.expected: will not call onSurfaceDestroyed
     */
    pattern->OnDetachFromFrameNode(AceType::RawPtr(frameNode));
    EXPECT_EQ(onSurfaceDestroyedSurfaceCount, 1);

    /**
     * @tc.steps: step4. ChangeSurfaceCallbackMode to PIP not in main tree
     * @tc.expected: not in main tree change to pip will call onSurfaceCreated once
     */
    pattern->ChangeSurfaceCallbackMode(SurfaceCallbackMode::PIP);
    EXPECT_EQ(onSurfaceCreatedSurfaceCount, 2);

    /**
     * @tc.steps: step5. attachTo&detachFrom main tree in PIP mode
     * @tc.expected: PIP mode attach to(detach from) main tree will not call onSurfaceCreated(onSurfaceDestroyed)
     */
    frameNode->AttachToMainTree(false);
    EXPECT_EQ(onSurfaceCreatedSurfaceCount, 2);
    frameNode->DetachFromMainTree();
    EXPECT_EQ(onSurfaceDestroyedSurfaceCount, 1);

    /**
     * @tc.steps: step6. detachFromFrameNode(in frameNode's destructor) in PIP mode
     * @tc.expected: call onSurfaceDestroyed once
     */
    pattern->OnDetachFromFrameNode(AceType::RawPtr(frameNode));
    EXPECT_EQ(onSurfaceDestroyedSurfaceCount, 2);

    /**
     * @tc.steps: step7. ChangeSurfaceCallbackMode in main tree
     * @tc.expected: will not call onSurfaceCreated(onSurfaceDestroyed)
     */
    frameNode->AttachToMainTree(false);
    pattern->ChangeSurfaceCallbackMode(SurfaceCallbackMode::DEFAULT);
    EXPECT_EQ(onSurfaceDestroyedSurfaceCount, 2);
    pattern->ChangeSurfaceCallbackMode(SurfaceCallbackMode::PIP);
    EXPECT_EQ(onSurfaceCreatedSurfaceCount, 2);
}

/**
 * @tc.name: EnableSecureTest
 * @tc.desc: Test EnableSecure Func.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestTwoNg, EnableSecureTest, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    EXPECT_CALL(*AceType::DynamicCast<MockRenderContext>(pattern->renderContextForSurface_),
                SetSecurityLayer(true)).WillOnce(Return());
    pattern->EnableSecure(true);
    EXPECT_CALL(*AceType::DynamicCast<MockRenderContext>(pattern->renderContextForSurface_),
                SetSecurityLayer(false)).WillOnce(Return());
    pattern->EnableSecure(false);

    pattern->type_ = XCOMPONENT_TEXTURE_TYPE_VALUE;

    EXPECT_CALL(*AceType::DynamicCast<MockRenderContext>(pattern->renderContextForSurface_),
                SetSecurityLayer(true)).Times(0);
    pattern->EnableSecure(true);
    EXPECT_CALL(*AceType::DynamicCast<MockRenderContext>(pattern->renderContextForSurface_),
                SetSecurityLayer(false)).Times(0);
    pattern->EnableSecure(false);
}

/**
 * @tc.name: EnableLayerTransparentTest
 * @tc.desc: Test EnableLayerTransparent Func.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestTwoNg, EnableLayerTransparentTest, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    EXPECT_CALL(*AceType::DynamicCast<MockRenderContext>(pattern->renderContextForSurface_),
                SetTransparentLayer(true)).WillOnce(Return());
    pattern->EnableTransparentLayer(true);
    EXPECT_CALL(*AceType::DynamicCast<MockRenderContext>(pattern->renderContextForSurface_),
                SetTransparentLayer(false)).WillOnce(Return());
    pattern->EnableTransparentLayer(false);

    pattern->type_ = XCOMPONENT_TEXTURE_TYPE_VALUE;

    EXPECT_CALL(*AceType::DynamicCast<MockRenderContext>(pattern->renderContextForSurface_),
                SetTransparentLayer(true)).Times(0);
    pattern->EnableTransparentLayer(true);
    EXPECT_CALL(*AceType::DynamicCast<MockRenderContext>(pattern->renderContextForSurface_),
                SetTransparentLayer(false)).Times(0);
    pattern->EnableTransparentLayer(false);
}

/**
 * @tc.name: ConfigSurfaceTest
 * @tc.desc: Test ConfigSurface Func.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestTwoNg, ConfigSurfaceTest, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    EXPECT_CALL(*AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_),
                ConfigSurface(MAX_WIDTH, MAX_HEIGHT)).WillOnce(Return());
    pattern->ConfigSurface(MAX_WIDTH, MAX_HEIGHT);
}

/**
 * @tc.name: OnAttachContextTest
 * @tc.desc: Test OnAttachContext Func.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestTwoNg, OnAttachContextTest, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    PipelineContext* context = frameNode->GetContext();
    EXPECT_CALL(*AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_),
                SetInstanceId(context->GetInstanceId())).WillOnce(Return());
    pattern->OnAttachContext(context);
}

/**
 * @tc.name: HdrBrightnessTest
 * @tc.desc: Test HdrBrightness Func.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestTwoNg, HdrBrightnessTest, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    EXPECT_CALL(*AceType::DynamicCast<MockRenderContext>(pattern->renderContextForSurface_),
                SetHDRBrightness(0.0f)).WillOnce(Return());
    pattern->HdrBrightness(-0.5f);
    EXPECT_CALL(*AceType::DynamicCast<MockRenderContext>(pattern->renderContextForSurface_),
                SetHDRBrightness(1.0f)).WillOnce(Return());
    pattern->HdrBrightness(1.5f);
    EXPECT_CALL(*AceType::DynamicCast<MockRenderContext>(pattern->renderContextForSurface_),
                SetHDRBrightness(0.5f)).WillOnce(Return());
    pattern->HdrBrightness(0.5f);

    pattern->type_ = XCOMPONENT_TEXTURE_TYPE_VALUE;

    EXPECT_CALL(*AceType::DynamicCast<MockRenderContext>(pattern->renderContextForSurface_),
                SetHDRBrightness(0.5f)).Times(0);
    pattern->HdrBrightness(0.5f);
}

/**
 * @tc.name: NativeStartImageAnalyzerTest
 * @tc.desc: Test NativeStartImageAnalyzer Func.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestTwoNg, NativeStartImageAnalyzerTest, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_TEXTURE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    int32_t nativeAnalyzerState = -1;
    std::function<void(int32_t)> nativeOnAnalyzed = [&](int32_t state) {
        nativeAnalyzerState = state;
    };

    EXPECT_FALSE(pattern->GetEnableAnalyzer());
    pattern->NativeStartImageAnalyzer(nativeOnAnalyzed);
    EXPECT_EQ(nativeAnalyzerState, ArkUI_XComponent_ImageAnalyzerState::ARKUI_XCOMPONENT_AI_ANALYSIS_DISABLED);

    pattern->EnableAnalyzer(true);
    EXPECT_TRUE(pattern->GetEnableAnalyzer());

    auto imageAnalyzerManager =
        std::make_shared<MockImageAnalyzerManager>(frameNode, ImageAnalyzerHolder::XCOMPONENT);
    imageAnalyzerManager->SetSupportImageAnalyzerFeature(true);
    pattern->imageAnalyzerManager_ = imageAnalyzerManager;

    pattern->isOnTree_ = false;
    pattern->NativeStartImageAnalyzer(nativeOnAnalyzed);
    EXPECT_EQ(nativeAnalyzerState, ArkUI_XComponent_ImageAnalyzerState::ARKUI_XCOMPONENT_AI_ANALYSIS_DISABLED);

    pattern->isOnTree_ = true;
    imageAnalyzerManager->SetSupportImageAnalyzerFeature(false);
    pattern->NativeStartImageAnalyzer(nativeOnAnalyzed);
    EXPECT_EQ(nativeAnalyzerState, ArkUI_XComponent_ImageAnalyzerState::ARKUI_XCOMPONENT_AI_ANALYSIS_UNSUPPORTED);

    imageAnalyzerManager->SetSupportImageAnalyzerFeature(true);
    pattern->NativeStartImageAnalyzer(nativeOnAnalyzed);
    EXPECT_TRUE(pattern->isNativeImageAnalyzing_);

    pattern->NativeStartImageAnalyzer(nativeOnAnalyzed);
    EXPECT_EQ(nativeAnalyzerState, ArkUI_XComponent_ImageAnalyzerState::ARKUI_XCOMPONENT_AI_ANALYSIS_ONGOING);
}

/**
 * @tc.name: NativeXComponentCallbackTest
 * @tc.desc: Test Register NativeXComponentCallback Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestTwoNg, NativeXComponentCallbackTest, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    g_testProperty.xcId = XCOMPONENT_ID;
    g_testProperty.libraryName = XCOMPONENT_LIBRARY_NAME;
    g_testProperty.soPath = XCOMPONENT_SO_PATH;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    auto pair = pattern->GetNativeXComponent();
    auto weakNativeXComponent = pair.second;
    auto nativeXComponent = weakNativeXComponent.lock();
    auto nativeXComponentImpl = pair.first;
    ASSERT_TRUE(nativeXComponent);
    ASSERT_TRUE(nativeXComponentImpl);
    pattern->hasXComponentInit_ = true;

    OH_NativeXComponent_Callback nativeCallback = {nullptr, nullptr, nullptr, nullptr};
    nativeXComponent->RegisterCallback(&nativeCallback);
    static bool hasSurfaceCreated = false;
    static bool hasSurfaceChanged = false;
    static bool hasSurfaceDestroyed = false;
    static bool hasDispatchTouchEvent = false;
    nativeCallback.OnSurfaceCreated = [](OH_NativeXComponent* component, void* window) {
        hasSurfaceCreated = true;
    };
    nativeCallback.OnSurfaceChanged = [](OH_NativeXComponent* component, void* window) {
        hasSurfaceChanged = true;
    };
    nativeCallback.OnSurfaceDestroyed = [](OH_NativeXComponent* component, void* window) {
        hasSurfaceDestroyed = true;
    };
    nativeCallback.DispatchTouchEvent = [](OH_NativeXComponent* component, void* window) {
        hasDispatchTouchEvent = true;
    };
    
    pattern->OnSurfaceCreated();
    ASSERT_TRUE(hasSurfaceCreated);

    pattern->OnSurfaceChanged(MAX_SURFACE_RECT, true);
    ASSERT_TRUE(hasSurfaceChanged);

    pattern->NativeXComponentDispatchTouchEvent({}, {});
    ASSERT_TRUE(hasDispatchTouchEvent);

    pattern->OnSurfaceDestroyed();
    ASSERT_TRUE(hasSurfaceDestroyed);
}

/**
 * @tc.name: GetGlobalPositionTestOne
 * @tc.desc: Test GetGlobalPosition Func.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestTwoNg, GetGlobalPositionTestOne, TestSize.Level1)
{
    auto xComponentController = std::make_shared<XComponentControllerNG>();
    g_testProperty.xcType = XCOMPONENT_TEXTURE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    pattern->type_ = XComponentType::SURFACE;
    xComponentController->pattern_ = pattern;
    float offsetX = 20.0f;
    float offsetY = 30.0f;
    auto result = xComponentController->GetGlobalPosition(offsetX, offsetY);
    EXPECT_EQ(result, XCOMPONENT_CONTROLLER_NO_ERROR);
    EXPECT_EQ(offsetX, pattern->GetOffsetRelativeToWindow().GetX());
    EXPECT_EQ(offsetY, pattern->GetOffsetRelativeToWindow().GetY());
}

/**
 * @tc.name: GetGlobalPositionTestTwo
 * @tc.desc: Test GetGlobalPosition Func.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestTwoNg, GetGlobalPositionTestTwo, TestSize.Level1)
{
    auto xComponentController = std::make_shared<XComponentControllerNG>();
    g_testProperty.xcType = XCOMPONENT_TEXTURE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    pattern->type_ = XComponentType::TEXTURE;
    xComponentController->pattern_ = pattern;
    float offsetX = 20.0f;
    float offsetY = 30.0f;
    auto result = xComponentController->GetGlobalPosition(offsetX, offsetY);
    EXPECT_EQ(result, XCOMPONENT_CONTROLLER_TYPE_ERROR);
}

/**
 * @tc.name: SetScreenIdShouldCallPatternSetFuncTest
 * @tc.desc: Test SetScreenIdShouldCallPatternSetFunc Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestTwoNg, SetScreenIdShouldCallPatternSetFuncTest, TestSize.Level1)
{
    // type is surface
    params.type = XCOMPONENT_SURFACE_TYPE_VALUE;
    params.id = XCOMPONENT_ID;
    params.controller = std::make_shared<XComponentControllerNG>();
    params.screenId = XCOMPONENT_SCREEN_ID;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = AceType::DynamicCast<FrameNode>(XComponentModelNG().CreateTypeNode(nodeId, &params));
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    EXPECT_EQ(pattern->screenId_.value(), XCOMPONENT_SCREEN_ID);
}

/**
 * @tc.name: SetScreenIdShouldNotCallPatternSetFuncTest
 * @tc.desc: Test SetScreenIdShouldNotCallPatternSetFunc Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestTwoNg, SetScreenIdShouldNotCallPatternSetFuncTest, TestSize.Level1)
{
    // type is component
    params.type = XCOMPONENT_COMPONENT_TYPE_VALUE;
    params.id = XCOMPONENT_ID;
    params.controller = std::make_shared<XComponentControllerNG>();
    params.screenId = XCOMPONENT_SCREEN_ID;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = AceType::DynamicCast<FrameNode>(XComponentModelNG().CreateTypeNode(nodeId, &params));
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    EXPECT_EQ(pattern->screenId_.has_value(), false);
}

/**
 * @tc.name: SetXComponentSurfaceSizeTest
 * @tc.desc: Test SetXComponentSurfaceSize Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestTwoNg, SetXComponentSurfaceSizeTest, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    EXPECT_CALL(*AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_),
        ConfigSurface(SURFACE_WIDTH_SIZE, SURFACE_HEIGHT_SIZE))
        .WillOnce(Return());
    XComponentModelNG::SetXComponentSurfaceSize(Referenced::RawPtr(frameNode), SURFACE_WIDTH_SIZE, SURFACE_HEIGHT_SIZE);
}

/**
 * @tc.name: InitXComponentShouldNotCallInitNativeXComponentAndLoadNativeTest
 * @tc.desc: Test InitXComponentShouldNotCallInitNativeXComponentAndLoadNative Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestTwoNg, InitXComponentShouldNotCallInitNativeXComponentAndLoadNativeTest, TestSize.Level1)
{
    // type = XCOMPONENT_COMPONENT_TYPE_VALUE
    g_testProperty.xcType = XCOMPONENT_COMPONENT_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    
    XComponentModelNG().InitXComponent(Referenced::RawPtr(frameNode));
    EXPECT_EQ(pattern->isNativeXComponent_, false);
}

/**
 * @tc.name: InitXComponentShouldCallInitNativeXComponentAndLoadNativeTest
 * @tc.desc: Test InitXComponentShouldCallInitNativeXComponentAndLoadNative Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestTwoNg, InitXComponentShouldCallInitNativeXComponentAndLoadNativeTest, TestSize.Level1)
{
    // type = XCOMPONENT_SURFACE_TYPE_VALUE, isTypedNode_= true, libraryName has value
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    pattern->isTypedNode_ = true;
    
    XComponentModelNG().InitXComponent(Referenced::RawPtr(frameNode));
    EXPECT_EQ(pattern->isNativeXComponent_, true);
}

/**
 * @tc.name: InitXComponentShouldCallInitNativeXComponentTest
 * @tc.desc: Test InitXComponentShouldCallInitNativeXComponent Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestTwoNg, InitXComponentShouldCallInitNativeXComponentTest, TestSize.Level1)
{
    // type = XCOMPONENT_SURFACE_TYPE_VALUE, isTypedNode_ = true, libraryName = std::nullopt
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    g_testProperty.libraryName = std::nullopt;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    pattern->isTypedNode_ = true;
    
    XComponentModelNG().InitXComponent(Referenced::RawPtr(frameNode));
    EXPECT_EQ(pattern->isNativeXComponent_, false);
}

/**
 * @tc.name: InitXComponentShouldNotCallInitNativeXComponentTest
 * @tc.desc: Test InitXComponentShouldNotCallInitNativeXComponent Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestTwoNg, InitXComponentShouldNotCallInitNativeXComponentTest, TestSize.Level1)
{
    // type = XCOMPONENT_SURFACE_TYPE_VALUE, isTypedNode_ = false
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    
    XComponentModelNG().InitXComponent(Referenced::RawPtr(frameNode));
    EXPECT_EQ(pattern->isNativeXComponent_, false);
}

/**
 * @tc.name: SetOnLoadShouldCallEventHubSetFuncTest
 * @tc.desc: Test SetOnLoadShouldCallEventHubSetFunc Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestTwoNg, SetOnLoadShouldCallEventHubSetFuncTest, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    uint32_t onNativeLoadCount = 0;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    auto loadEvent = [&onNativeLoadCount](const std::string&) {
        ++onNativeLoadCount;
    };

    XComponentModelNG::SetOnLoad(Referenced::RawPtr(frameNode), loadEvent);
    pattern->OnNativeLoad(Referenced::RawPtr(frameNode));
    EXPECT_EQ(onNativeLoadCount, 1);
}

/**
 * @tc.name: SetOnLoadShouldNotCallEventHubSetFuncTest
 * @tc.desc: Test SetOnLoadShouldNotCallEventHubSetFunc Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestTwoNg, SetOnLoadShouldNotCallEventHubSetFuncTest, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_COMPONENT_TYPE_VALUE;
    uint32_t onNativeLoadCount = 0;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    auto loadEvent = [&onNativeLoadCount](const std::string&) {
        ++onNativeLoadCount;
    };

    XComponentModelNG::SetOnLoad(Referenced::RawPtr(frameNode), loadEvent);
    pattern->OnNativeLoad(Referenced::RawPtr(frameNode));
    EXPECT_EQ(onNativeLoadCount, 0);
}

/**
 * @tc.name: SetOnDestroyShouldCallEventHubSetFuncTest
 * @tc.desc: Test SetOnDestroyShouldCallEventHubSetFunc Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestTwoNg, SetOnDestroyShouldCallEventHubSetFuncTest, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    uint32_t onDestroyCount = 0;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    auto destroyEvent = [&onDestroyCount](const std::string&) {
        ++onDestroyCount;
    };

    XComponentModelNG::SetOnDestroy(Referenced::RawPtr(frameNode), destroyEvent);
    pattern->OnNativeUnload(Referenced::RawPtr(frameNode));
    EXPECT_EQ(onDestroyCount, 1);
}

/**
 * @tc.name: SetOnDestroyShouldNotCallEventHubSetFuncTest
 * @tc.desc: Test SetOnDestroyShouldNotCallEventHubSetFunc Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestTwoNg, SetOnDestroyShouldNotCallEventHubSetFuncTest, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_COMPONENT_TYPE_VALUE;
    uint32_t onDestroyCount = 0;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    auto destroyEvent = [&onDestroyCount](const std::string&) {
        ++onDestroyCount;
    };

    XComponentModelNG::SetOnDestroy(Referenced::RawPtr(frameNode), destroyEvent);
    pattern->OnNativeUnload(Referenced::RawPtr(frameNode));
    EXPECT_EQ(onDestroyCount, 0);
}

/**
 * @tc.name: GetSurfaceRenderFitTest
 * @tc.desc: Test GetSurfaceRenderFit Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestTwoNg, GetSurfaceRenderFitTest, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);

    RenderFit renderFit = XComponentModelNG::GetSurfaceRenderFit(Referenced::RawPtr(frameNode));
    EXPECT_EQ(renderFit, RenderFit::RESIZE_FILL);
}

/**
 * @tc.name: SetXComponentSurfaceRectTest
 * @tc.desc: Test SetXComponentSurfaceRect Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestTwoNg, SetXComponentSurfaceRectTest, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    XComponentModelNG::SetXComponentSurfaceRect(
        Referenced::RawPtr(frameNode), OFFSET_X, OFFSET_Y, SURFACE_WIDTH_SIZE, SURFACE_HEIGHT_SIZE);
    EXPECT_EQ(pattern->selfIdealSurfaceOffsetX_, OFFSET_X);
    EXPECT_EQ(pattern->selfIdealSurfaceOffsetY_, OFFSET_Y);
    EXPECT_EQ(pattern->selfIdealSurfaceWidth_, SURFACE_WIDTH_SIZE);
    EXPECT_EQ(pattern->selfIdealSurfaceHeight_, SURFACE_HEIGHT_SIZE);
}

/**
 * @tc.name: GetXComponentEnableAnalyzerTest
 * @tc.desc: Test GetXComponentEnableAnalyzer Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestTwoNg, GetXComponentEnableAnalyzerTest, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    pattern->EnableAnalyzer(true);
    auto isEnableAnalyzer = XComponentModelNG().GetXComponentEnableAnalyzer(Referenced::RawPtr(frameNode));
    EXPECT_EQ(isEnableAnalyzer, true);
}
} // namespace OHOS::Ace::NG
