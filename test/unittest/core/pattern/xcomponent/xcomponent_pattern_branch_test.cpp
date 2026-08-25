/*
 * Copyright (c) 2026 Huawei Device Co. Ltd.
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
#include "test/mock/frameworks/core/common/mock_image_analyzer_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/components_ng/render/mock_render_context.h"
#include "test/mock/frameworks/core/components_ng/render/mock_render_surface.h"
#include "test/mock/frameworks/core/rosen/testing_canvas_utils.h"
#include "test/mock/frameworks/base/display_manager/mock_display_manager.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/common/ace_application_info.h"
#include "core/common/ai/image_analyzer_mgr.h"
#include "core/common/statistic_event_reporter.h"
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
#include "core/event/key_event.h"
#include "core/event/touch_event.h"
#include "core/interfaces/native/node/node_xcomponent_modifier.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_ext_surface_callback_client.h"
#include "frameworks/core/gestures/press_recognizer.h"
#include "frameworks/core/components_ng/pattern/node_container/node_container_pattern.h"
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
const std::string XCOMPONENT_ID = "xcomponent";
const std::string XCOMPONENT_LIBRARY_NAME = "native_render";
const std::string XCOMPONENT_SO_PATH = "com.example.xcomponentmultihap/entry";
constexpr XComponentType XCOMPONENT_SURFACE_TYPE_VALUE = XComponentType::SURFACE;
constexpr XComponentType XCOMPONENT_TEXTURE_TYPE_VALUE = XComponentType::TEXTURE;
constexpr XComponentType XCOMPONENT_NODE_TYPE_VALUE = XComponentType::NODE;
constexpr float MAX_WIDTH = 400.0f;
constexpr float MAX_HEIGHT = 400.0f;
const SizeF MAX_SIZE(MAX_WIDTH, MAX_HEIGHT);
constexpr uint32_t ROTATION_HINT_90 = 90;
constexpr uint32_t ROTATION_HINT_0 = 0;
constexpr float IDEAL_W = 100.0f;
constexpr float IDEAL_H = 60.0f;
TestProperty g_testProperty;
} // namespace

class XComponentPatternBranchTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();

protected:
    static RefPtr<FrameNode> CreateXComponentNode(TestProperty& testProperty);
};

void XComponentPatternBranchTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    g_testProperty.xcId = XCOMPONENT_ID;
    g_testProperty.libraryName = XCOMPONENT_LIBRARY_NAME;
    g_testProperty.soPath = XCOMPONENT_SO_PATH;
}

void XComponentPatternBranchTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> XComponentPatternBranchTestNg::CreateXComponentNode(TestProperty& testProperty)
{
    auto xcId = testProperty.xcId;
    auto xcType = testProperty.xcType.value();
    auto libraryName = testProperty.libraryName;
    auto xcomponentController = std::make_shared<XComponentControllerNG>();
    XComponentModelNG().Create(xcId, xcType, libraryName, xcomponentController);
    if (testProperty.soPath.has_value()) {
        XComponentModelNG().SetSoPath(testProperty.soPath.value());
    }
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish(); // pop
    return AceType::DynamicCast<FrameNode>(element);
}

/**
 * @tc.name: XComponentSetRotationLockedTest001
 * @tc.desc: Test SetRotation early return when surface is locked or rotation unchanged
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternBranchTestNg, XComponentSetRotationLockedTest001, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    pattern->renderSurface_ = AceType::MakeRefPtr<MockRenderSurface>();
    pattern->isSurfaceLock_ = true;
    pattern->rotation_ = ROTATION_HINT_0;
    pattern->SetRotation(ROTATION_HINT_90);
    EXPECT_EQ(pattern->rotation_, ROTATION_HINT_0);

    pattern->isSurfaceLock_ = false;
    pattern->rotation_ = ROTATION_HINT_90;
    pattern->SetRotation(ROTATION_HINT_90);
    EXPECT_EQ(pattern->rotation_, ROTATION_HINT_90);
}

/**
 * @tc.name: XComponentRoundValueToPixelGridFloorTest002
 * @tc.desc: Test RoundValueToPixelGrid forceFloor and isRound small-fraction branches
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternBranchTestNg, XComponentRoundValueToPixelGridFloorTest002, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    float value = 1.7f;
    auto ret = pattern->RoundValueToPixelGrid(value, true, false, true);
    EXPECT_FLOAT_EQ(ret, 1.0f);

    value = -1.7f;
    ret = pattern->RoundValueToPixelGrid(value, true, false, true);
    EXPECT_FLOAT_EQ(ret, -2.0f);

    value = 1.2f;
    ret = pattern->RoundValueToPixelGrid(value, true, false, true);
    EXPECT_FLOAT_EQ(ret, 1.0f);

    value = 1.2f;
    ret = pattern->RoundValueToPixelGrid(value, true, false, false);
    EXPECT_FLOAT_EQ(ret, 1.0f);
}

/**
 * @tc.name: XComponentGetSurfaceRenderFitTest003
 * @tc.desc: Test GetSurfaceRenderFit with null and non-null handling context
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternBranchTestNg, XComponentGetSurfaceRenderFitTest003, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    pattern->handlingSurfaceRenderContext_ = nullptr;
    EXPECT_EQ(pattern->GetSurfaceRenderFit(), RenderFit::RESIZE_FILL);

    auto renderContext = AceType::MakeRefPtr<MockRenderContext>();
    pattern->handlingSurfaceRenderContext_ = renderContext;
    EXPECT_EQ(pattern->GetSurfaceRenderFit(), RenderFit::RESIZE_FILL);
}

/**
 * @tc.name: XComponentInitNativeXComponentElseTest004
 * @tc.desc: Test InitNativeXComponent else branch (NODE type / no library name)
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternBranchTestNg, XComponentInitNativeXComponentElseTest004, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_NODE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    pattern->isNativeXComponent_ = false;
    pattern->nativeXComponent_.reset();
    pattern->nativeXComponentImpl_ = nullptr;
    pattern->InitNativeXComponent();
    EXPECT_FALSE(pattern->isNativeXComponent_);
    EXPECT_FALSE(pattern->nativeXComponent_);

    pattern->type_ = XCOMPONENT_SURFACE_TYPE_VALUE;
    pattern->libraryname_ = std::nullopt;
    pattern->InitNativeXComponent();
    EXPECT_FALSE(pattern->isNativeXComponent_);
}

/**
 * @tc.name: XComponentUpdateSurfaceRectBranchTest005
 * @tc.desc: Test UpdateSurfaceRect ideal/no-ideal and API version branches
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternBranchTestNg, XComponentUpdateSurfaceRectBranchTest005, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    pattern->drawSize_ = MAX_SIZE;
    pattern->selfIdealSurfaceWidth_ = IDEAL_W;
    pattern->selfIdealSurfaceHeight_ = IDEAL_H;
    pattern->selfIdealSurfaceOffsetX_ = std::nullopt;
    pattern->selfIdealSurfaceOffsetY_ = std::nullopt;
    pattern->surfaceOffset_ = OffsetF(0.0f, 0.0f);
    pattern->surfaceSize_ = SizeF(0.0f, 0.0f);
    auto ret = pattern->UpdateSurfaceRect();
    EXPECT_TRUE(std::get<0>(ret));
    EXPECT_TRUE(std::get<1>(ret));
    EXPECT_EQ(pattern->surfaceSize_.Width(), IDEAL_W);
    EXPECT_FLOAT_EQ(pattern->surfaceOffset_.GetX(), (MAX_WIDTH - IDEAL_W) / 2.0f);

    pattern->selfIdealSurfaceOffsetX_ = 5.0f;
    pattern->selfIdealSurfaceOffsetY_ = 7.0f;
    pattern->surfaceOffset_ = OffsetF(0.0f, 0.0f);
    ret = pattern->UpdateSurfaceRect();
    EXPECT_FLOAT_EQ(pattern->surfaceOffset_.GetX(), 5.0f);
    EXPECT_FLOAT_EQ(pattern->surfaceOffset_.GetY(), 7.0f);

    pattern->selfIdealSurfaceWidth_ = std::nullopt;
    pattern->selfIdealSurfaceHeight_ = std::nullopt;
    pattern->selfIdealSurfaceOffsetX_ = std::nullopt;
    pattern->selfIdealSurfaceOffsetY_ = std::nullopt;
    pattern->localPosition_ = OffsetF(3.0f, 4.0f);
    pattern->surfaceOffset_ = OffsetF(0.0f, 0.0f);
    ret = pattern->UpdateSurfaceRect();
    EXPECT_FLOAT_EQ(pattern->surfaceSize_.Width(), MAX_WIDTH);
    EXPECT_FLOAT_EQ(pattern->surfaceOffset_.GetX(), 3.0f);

    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    pattern->selfIdealSurfaceWidth_ = IDEAL_W;
    pattern->selfIdealSurfaceHeight_ = IDEAL_H;
    pattern->surfaceOffset_ = OffsetF(0.0f, 0.0f);
    pattern->surfaceSize_ = SizeF(0.0f, 0.0f);
    ret = pattern->UpdateSurfaceRect();
    EXPECT_EQ(pattern->paintRect_.Width(), IDEAL_W);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(backupApiVersion));
}

/**
 * @tc.name: XComponentHandleSurfaceChangeEventBranchTest006
 * @tc.desc: Test HandleSurfaceChangeEvent offset/handling/forceRender branches
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternBranchTestNg, XComponentHandleSurfaceChangeEventBranchTest006, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    pattern->drawSize_ = SizeF(0.0f, 0.0f);
    pattern->HandleSurfaceChangeEvent(false, false, false, false, false);

    pattern->drawSize_ = MAX_SIZE;
    pattern->globalPosition_ = OffsetF(10.0f, 20.0f);
    pattern->paintRect_.SetRect(5.0f, 6.0f, IDEAL_W, IDEAL_H);
    pattern->nativeXComponent_ = nullptr;
    pattern->nativeXComponentImpl_ = nullptr;
    auto handlingContext = AceType::MakeRefPtr<MockRenderContext>();
    pattern->handlingSurfaceRenderContext_ = handlingContext;
    pattern->renderSurface_ = nullptr;
    EXPECT_CALL(*handlingContext, SetBounds(5.0f, 6.0f, IDEAL_W, IDEAL_H)).WillOnce(Return());
    pattern->HandleSurfaceChangeEvent(false, true, false, false, false);

    pattern->handlingSurfaceRenderContext_ = nullptr;
    pattern->renderSurface_ = nullptr;
    pattern->HandleSurfaceChangeEvent(true, false, false, false, true);

    pattern->drawSize_ = SizeF(0.0f, 0.0f);
    pattern->HandleSurfaceChangeEvent(false, true, true, true, true);
}

/**
 * @tc.name: XComponentOnSurfaceCallbackModeSameTest007
 * @tc.desc: Test OnSurfaceCallbackModeChange early return when mode unchanged
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternBranchTestNg, XComponentOnSurfaceCallbackModeSameTest007, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    pattern->surfaceCallbackMode_ = SurfaceCallbackMode::PIP;
    pattern->OnSurfaceCallbackModeChange(SurfaceCallbackMode::PIP);
    EXPECT_EQ(pattern->surfaceCallbackMode_, SurfaceCallbackMode::PIP);
}

/**
 * @tc.name: XComponentSetExtControllerSuccessTest008
 * @tc.desc: Test SetExtController success path with null handling context
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternBranchTestNg, XComponentSetExtControllerSuccessTest008, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto extFrameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(extFrameNode);
    auto extPattern = extFrameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(extPattern);

    pattern->extPattern_ = nullptr;
    pattern->handlingSurfaceRenderContext_ = nullptr;
    auto result = pattern->SetExtController(extPattern);
    EXPECT_EQ(result, XCOMPONENT_CONTROLLER_NO_ERROR);
    EXPECT_FALSE(pattern->handlingSurfaceRenderContext_);
    EXPECT_EQ(pattern->extPattern_.Upgrade(), extPattern);
}

/**
 * @tc.name: XComponentResetExtControllerSuccessTest009
 * @tc.desc: Test ResetExtController success path
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternBranchTestNg, XComponentResetExtControllerSuccessTest009, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto extFrameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(extFrameNode);
    auto extPattern = extFrameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(extPattern);

    pattern->handlingSurfaceRenderContext_ = nullptr;
    pattern->renderContextForSurface_ = nullptr;
    extPattern->handlingSurfaceRenderContext_ = nullptr;
    extPattern->renderContextForSurface_ = nullptr;
    auto result = pattern->SetExtController(extPattern);
    EXPECT_EQ(result, XCOMPONENT_CONTROLLER_NO_ERROR);

    result = pattern->ResetExtController(extPattern);
    EXPECT_EQ(result, XCOMPONENT_CONTROLLER_NO_ERROR);
    EXPECT_FALSE(pattern->extPattern_.Upgrade());
}

/**
 * @tc.name: XComponentHandleKeyEventNullTest010
 * @tc.desc: Test HandleKeyEvent returns false when nativeXComponent is null
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternBranchTestNg, XComponentHandleKeyEventNullTest010, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    pattern->nativeXComponent_ = nullptr;
    pattern->nativeXComponentImpl_ = nullptr;
    KeyEvent event;
    auto result = pattern->HandleKeyEvent(event);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: XComponentNativeStartImageAnalyzerDisabledTest011
 * @tc.desc: Test NativeStartImageAnalyzer disabled/unsupported paths
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternBranchTestNg, XComponentNativeStartImageAnalyzerDisabledTest011, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_TEXTURE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    int32_t statusCode = -1;
    std::function<void(int32_t)> callback = [&statusCode](int32_t code) { statusCode = code; };

    pattern->isOnTree_ = false;
    pattern->isEnableAnalyzer_ = true;
    pattern->NativeStartImageAnalyzer(callback);
    EXPECT_NE(statusCode, -1);

    pattern->isOnTree_ = true;
    pattern->isEnableAnalyzer_ = false;
    statusCode = -1;
    pattern->NativeStartImageAnalyzer(callback);
    EXPECT_NE(statusCode, -1);

    pattern->isEnableAnalyzer_ = true;
    pattern->imageAnalyzerManager_ = nullptr;
    statusCode = -1;
    pattern->NativeStartImageAnalyzer(callback);
    EXPECT_NE(statusCode, -1);
}

/**
 * @tc.name: XComponentOnSurfaceCreatedNotNativeTest012
 * @tc.desc: Test OnSurfaceCreated eventHub path when not native xcomponent
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternBranchTestNg, XComponentOnSurfaceCreatedNotNativeTest012, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    pattern->isNativeXComponent_ = false;
    pattern->nativeXComponent_ = nullptr;
    pattern->nativeXComponentImpl_ = nullptr;
    pattern->surfaceId_ = "test_surface";
    pattern->OnSurfaceCreated();
    EXPECT_FALSE(pattern->isNativeXComponent_);
}

/**
 * @tc.name: XComponentXComponentSizeChangeEarlyReturnTest013
 * @tc.desc: Test XComponentSizeChange early return for native non-typed node
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternBranchTestNg, XComponentXComponentSizeChangeEarlyReturnTest013, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    pattern->isTypedNode_ = false;
    pattern->isNativeXComponent_ = true;
    RectF surfaceRect(0.0f, 0.0f, MAX_WIDTH, MAX_HEIGHT);
    pattern->XComponentSizeChange(surfaceRect, false);
}

/**
 * @tc.name: XComponentDoTextureExportNullTest014
 * @tc.desc: Test DoTextureExport/StopTextureExport null handling context
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternBranchTestNg, XComponentDoTextureExportNullTest014, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    pattern->handlingSurfaceRenderContext_ = nullptr;
    EXPECT_FALSE(pattern->DoTextureExport());
    EXPECT_FALSE(pattern->StopTextureExport());
}

/**
 * @tc.name: XComponentGetOffsetRelativeToWindowNullTest015
 * @tc.desc: Test GetOffsetRelativeToWindow returns empty when host is null
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternBranchTestNg, XComponentGetOffsetRelativeToWindowNullTest015, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    pattern->frameNode_.Reset();
    auto offset = pattern->GetOffsetRelativeToWindow();
    EXPECT_FLOAT_EQ(offset.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(offset.GetY(), 0.0f);
}

/**
 * @tc.name: XComponentSetSurfaceIsOpaqueBranchTest016
 * @tc.desc: Test SetSurfaceIsOpaque for SURFACE and TEXTURE render context paths
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternBranchTestNg, XComponentSetSurfaceIsOpaqueBranchTest016, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    auto surfaceCtx = AceType::MakeRefPtr<MockRenderContext>();
    pattern->renderContextForSurface_ = surfaceCtx;
    EXPECT_CALL(*surfaceCtx, SetSurfaceBufferOpaque(true)).WillOnce(Return());
    pattern->SetSurfaceIsOpaque(true);
    EXPECT_TRUE(pattern->isOpaque_);

    pattern->type_ = XCOMPONENT_TEXTURE_TYPE_VALUE;
    pattern->renderSurface_ = AceType::MakeRefPtr<MockRenderSurface>();
    EXPECT_CALL(*AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_), SetSurfaceBufferOpaque(false))
        .WillOnce(Return());
    pattern->SetSurfaceIsOpaque(false);
    EXPECT_FALSE(pattern->isOpaque_);
}

/**
 * @tc.name: XComponentEnableSecureTransparentBranchTest017
 * @tc.desc: Test EnableSecure/EnableTransparentLayer early return for non-SURFACE type
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternBranchTestNg, XComponentEnableSecureTransparentBranchTest017, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_TEXTURE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    pattern->renderContextForSurface_ = AceType::MakeRefPtr<MockRenderContext>();
    pattern->EnableSecure(true);
    EXPECT_FALSE(pattern->isEnableSecure_);
    pattern->HdrBrightness(0.5f);
    EXPECT_FLOAT_EQ(pattern->hdrBrightness_, 1.0f);
    pattern->EnableTransparentLayer(true);
    EXPECT_FALSE(pattern->isTransparentLayer_);
}

/**
 * @tc.name: XComponentDumpAdvanceInfoRenderSurfaceTest018
 * @tc.desc: Test DumpAdvanceInfo/DumpInfo with and without renderSurface
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternBranchTestNg, XComponentDumpAdvanceInfoRenderSurfaceTest018, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    pattern->renderSurface_ = nullptr;
    pattern->DumpAdvanceInfo();
    pattern->DumpInfo();

    pattern->renderSurface_ = AceType::MakeRefPtr<MockRenderSurface>();
    pattern->DumpAdvanceInfo();
    pattern->DumpInfo();
    SUCCEED();
}

/**
 * @tc.name: XComponentSetRenderFitBranchTest019
 * @tc.desc: Test SetRenderFit with null and non-null handling context
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternBranchTestNg, XComponentSetRenderFitBranchTest019, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    pattern->handlingSurfaceRenderContext_ = nullptr;
    pattern->SetRenderFit(RenderFit::CENTER);
    EXPECT_EQ(pattern->renderFit_, RenderFit::RESIZE_FILL);

    auto handlingContext = AceType::MakeRefPtr<MockRenderContext>();
    EXPECT_CALL(*handlingContext, SetRenderFit(RenderFit::TOP)).WillOnce(Return());
    pattern->handlingSurfaceRenderContext_ = handlingContext;
    pattern->SetRenderFit(RenderFit::TOP);
    EXPECT_EQ(pattern->renderFit_, RenderFit::TOP);
}

/**
 * @tc.name: XComponentGetNativeProviderBranchTest020
 * @tc.desc: Test GetNativeProvider useNodeHandleAccessibilityProvider path
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternBranchTestNg, XComponentGetNativeProviderBranchTest020, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    pattern->useNodeHandleAccessibilityProvider_ = true;
    auto* fakeProvider = reinterpret_cast<ArkUI_AccessibilityProvider*>(0x1234);
    pattern->arkuiAccessibilityProvider_ = fakeProvider;
    EXPECT_EQ(pattern->GetNativeProvider(), fakeProvider);
    pattern->arkuiAccessibilityProvider_ = nullptr;
}

/**
 * @tc.name: XComponentDispatchTouchEventNullTest021
 * @tc.desc: Test NativeXComponentDispatchTouchEvent returns early when nativeXComponent is null
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPatternBranchTestNg, XComponentDispatchTouchEventNullTest021, TestSize.Level1)
{
    g_testProperty.xcType = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    pattern->nativeXComponent_ = nullptr;
    pattern->nativeXComponentImpl_ = nullptr;
    OH_NativeXComponent_TouchEvent touchEvent = {};
    std::vector<XComponentTouchPoint> touchPoints;
    pattern->NativeXComponentDispatchTouchEvent(touchEvent, touchPoints);
}
} // namespace OHOS::Ace::NG
