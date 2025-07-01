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
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/render/mock_render_surface.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_layout_algorithm.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_model_ng.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern_v2.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_surface_holder.h"
#include "core/components_ng/property/measure_property.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr XComponentType XCOMPONENT_SURFACE_TYPE_VALUE = XComponentType::SURFACE;
ArkUI_XComponent_Params params;
bool g_isCreated = false;
bool g_isChanged = false;
bool g_isDestroyed = false;
const float MAX_WIDTH = 400.0f;
const float MAX_HEIGHT = 400.0f;
const SizeF MAX_SIZE(MAX_WIDTH, MAX_HEIGHT);
const float CHILD_WIDTH = 200.0f;
const float CHILD_HEIGHT = 200.0f;
const SizeF CHILD_SIZE(CHILD_WIDTH, CHILD_HEIGHT);
const int32_t MIN_RATE = 30;
const int32_t MAX_RATE = 120;
const int32_t EXPECTED_RATE = 120;
const int32_t CODE_NO_ERROR = 0;
const int32_t CODE_PARAM_INVALID = 401;
} // namespace

class XComponentV2TestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void TearDown() override
    {
        g_isCreated = false;
        g_isChanged = false;
        g_isDestroyed = false;
    }

protected:
    static RefPtr<FrameNode> CreateXComponentNode();
};

void XComponentV2TestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void XComponentV2TestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> XComponentV2TestNg::CreateXComponentNode()
{
    params.type = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = AceType::DynamicCast<FrameNode>(XComponentModelNG().CreateTypeNode(nodeId, &params));
    return frameNode;
}

/**
 * @tc.name: XComponentSurfaceLifeCycleCallback001
 * @tc.desc: Test SurfaceHolder's surface life cycle callback
 * @tc.type: FUNC
 */
HWTEST_F(XComponentV2TestNg, XComponentSurfaceLifeCycleCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateXComponentNode
     * @tc.expected: xcomponent frameNode create successfully
     */
    auto frameNode = CreateXComponentNode();
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::XCOMPONENT_ETS_TAG);
    auto pattern = frameNode->GetPattern<XComponentPatternV2>();
    ASSERT_TRUE(pattern);
    /**
     * @tc.steps: step2. set surfaceHolder and surface life cycle callback
     * @tc.expected: surface life cycle callback add successfully
     */
    OH_ArkUI_SurfaceHolder* surfaceHolder = new OH_ArkUI_SurfaceHolder();
    pattern->SetSurfaceHolder(surfaceHolder);
    ASSERT_TRUE(pattern->surfaceHolder_);

    OH_ArkUI_SurfaceCallback* surfaceCallback = new OH_ArkUI_SurfaceCallback();
    surfaceCallback->OnSurfaceCreated = [](OH_ArkUI_SurfaceHolder* /* surfaceHolder */) { g_isCreated = true; };
    surfaceCallback->OnSurfaceDestroyed = [](OH_ArkUI_SurfaceHolder* /* surfaceHolder */) { g_isCreated = false; };
    surfaceCallback->OnSurfaceChanged = [](OH_ArkUI_SurfaceHolder* /* surfaceHolder */, uint64_t width,
                                            uint64_t height) { g_isChanged = true; };
    auto code = surfaceHolder->AddSurfaceCallback(surfaceCallback);
    EXPECT_EQ(code, ERROR_CODE_NO_ERROR);
    /**
     * @tc.steps: step3. call OnAttachToMainTree
     * @tc.expected: OnSurfaceCreated has called
     */
    EXPECT_TRUE(pattern->autoInitialize_);
    pattern->OnAttachToMainTree();
    EXPECT_TRUE(g_isCreated);
    /**
     * @tc.steps: step4. call BeforeSyncGeometryProperties
     *            case: contentSize = 0
     *            case: config.skipMeasure = true
     * @tc.expected: OnSurfaceChanged has called
     */
    DirtySwapConfig config;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    frameNode->geometryNode_ = geometryNode;
    geometryNode->SetContentSize({ 0.0f, 0.0f });
    pattern->BeforeSyncGeometryProperties(config);
    EXPECT_FALSE(g_isChanged);
    config.skipMeasure = true;
    pattern->BeforeSyncGeometryProperties(config);
    EXPECT_FALSE(g_isChanged);
    /**
     * @tc.steps: step5. call BeforeSyncGeometryProperties
     * @tc.expected: OnSurfaceChanged has called
     */
    config.skipMeasure = false;
    geometryNode->SetFrameSize(MAX_SIZE);
    geometryNode->SetContentSize(MAX_SIZE);

    EXPECT_CALL(*AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_),
        AdjustNativeWindowSize(MAX_WIDTH, MAX_HEIGHT))
        .WillOnce(Return());
    EXPECT_CALL(*AceType::DynamicCast<MockRenderContext>(pattern->renderContextForSurface_),
        SetBounds(0, 0, MAX_WIDTH, MAX_HEIGHT))
        .WillOnce(Return());
    pattern->BeforeSyncGeometryProperties(config);
    EXPECT_TRUE(g_isChanged);
    /**
     * @tc.steps: step6. call OnDetachFromFrameNode
     * @tc.expected: onSurfaceDestroyed has called
     */
    pattern->OnDetachFromMainTree();
    EXPECT_FALSE(g_isCreated);
    /**
     * @tc.steps: step7. call OnDetachFromFrameNode
     * @tc.expected: nativeWindow has finalize
     */
    pattern->OnDetachFromFrameNode(AceType::RawPtr(frameNode));
    EXPECT_FALSE(surfaceHolder->node_);
    delete surfaceCallback;
    delete surfaceHolder;
}

/**
 * @tc.name: XComponentInitializeFinalizeTest002
 * @tc.desc: Test Initialize and Finalize
 * @tc.type: FUNC
 */
HWTEST_F(XComponentV2TestNg, XComponentInitializeFinalizeTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateXComponentNode
     * @tc.expected: xcomponent frameNode create successfully
     */
    auto frameNode = CreateXComponentNode();
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::XCOMPONENT_ETS_TAG);
    auto pattern = frameNode->GetPattern<XComponentPatternV2>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. call Initialize
     * @tc.expected: surface initialize successfully
     */
    auto code = pattern->Initialize();
    EXPECT_EQ(code, ERROR_CODE_NO_ERROR);
    EXPECT_TRUE(pattern->isInitialized_);
    code = pattern->Initialize();
    EXPECT_EQ(code, ERROR_CODE_XCOMPONENT_STATE_INVALID);

    /**
     * @tc.steps: step3. call Finalize
     * @tc.expected: surface finalize successfully
     */
    code = pattern->Finalize();
    EXPECT_EQ(code, ERROR_CODE_NO_ERROR);
    EXPECT_FALSE(pattern->isInitialized_);
    code = pattern->Finalize();
    EXPECT_EQ(code, ERROR_CODE_XCOMPONENT_STATE_INVALID);

    /**
     * @tc.steps: step4. call Initialize and OnDetachFromFrameNode
     * @tc.expected: surface finalize successfully
     */
    code = pattern->Initialize();
    EXPECT_EQ(code, ERROR_CODE_NO_ERROR);
    EXPECT_TRUE(pattern->isInitialized_);
    pattern->OnDetachFromFrameNode(AceType::RawPtr(frameNode));
    EXPECT_FALSE(pattern->isInitialized_);
}

/**
 * @tc.name: XComponentLayoutAlgorithmTest003
 * @tc.desc: Test BeforeSyncGeometryProperties
 * @tc.type: FUNC
 */
HWTEST_F(XComponentV2TestNg, XComponentLayoutAlgorithmTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateXComponentNode
     * @tc.expected: xcomponent frameNode create successfully
     */
    auto frameNode = CreateXComponentNode();
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::XCOMPONENT_ETS_TAG);
    auto pattern = frameNode->GetPattern<XComponentPatternV2>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. call BeforeSyncGeometryProperties adjust frameOffsetChanges, contentOffsetChanges and
     *                   contentSizeChanges
     * @tc.expected: BeforeSyncGeometryProperties return false
     */
    DirtySwapConfig config;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    frameNode->geometryNode_ = geometryNode;
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
    // test OnRebuildFrame
    EXPECT_CALL(*AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_), IsSurfaceValid())
        .WillOnce(Return(true))
        .WillRepeatedly(Return(false));
    pattern->OnRebuildFrame(); // type="surface", IsSurfaceValid=true
    pattern->OnRebuildFrame(); // type="surface", IsSurfaceValid=false
}

/**
 * @tc.name: XComponentWindowTest004
 * @tc.desc: Test WindowHide/WindowShow callback
 * @tc.type: FUNC
 */
HWTEST_F(XComponentV2TestNg, XComponentWindowTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateXComponentNode
     * @tc.expected: xcomponent frameNode create successfully
     */
    auto frameNode = CreateXComponentNode();
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::XCOMPONENT_ETS_TAG);
    auto pattern = frameNode->GetPattern<XComponentPatternV2>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. create surfaceHolder instance and get nativeWindow
     * @tc.expected: create surfaceHolder instance and get nativeWindow successfully
     */
    OH_ArkUI_SurfaceHolder* surfaceHolder = new OH_ArkUI_SurfaceHolder();
    pattern->SetSurfaceHolder(surfaceHolder);
    EXPECT_TRUE(pattern->surfaceHolder_);

    /**
     * @tc.steps: step3. call OnWindowHide and OnWindowShow
     * @tc.expected: OnWindowHide/OnWindowShow return false
     */
    pattern->OnWindowHide();
    pattern->OnWindowHide(); // test when hasReleasedSurface_ is not satisfied
    EXPECT_TRUE(pattern->hasReleasedSurface_);
    pattern->OnWindowShow();
    pattern->OnWindowShow(); // test when hasReleasedSurface_ is not satisfied
    EXPECT_FALSE(pattern->hasReleasedSurface_);
    delete surfaceHolder;
}

/**
 * @tc.name: XComponentSurfaceLifeCycleCallbackTest002
 * @tc.desc: Test SurfaceHolder's surface life cycle callback
 * @tc.type: FUNC
 */
HWTEST_F(XComponentV2TestNg, XComponentSurfaceLifeCycleCallbackTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateXComponentNode
     * @tc.expected: xcomponent frameNode create successfully
     */
    auto frameNode = CreateXComponentNode();
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::XCOMPONENT_ETS_TAG);
    auto pattern = frameNode->GetPattern<XComponentPatternV2>();
    ASSERT_TRUE(pattern);
    /**
     * @tc.steps: step2. set surface life cycle callback functions pointers as nullptr
     * @tc.expected: surface life cycle callback add successfully
     */
    OH_ArkUI_SurfaceHolder surfaceHolder;
    pattern->SetSurfaceHolder(&surfaceHolder);
    ASSERT_TRUE(pattern->surfaceHolder_);

    g_isCreated = false;
    g_isChanged = false;
    g_isDestroyed = false;

    OH_ArkUI_SurfaceCallback surfaceCallback = {
        .OnSurfaceCreated = nullptr,
        .OnSurfaceChanged = nullptr,
        .OnSurfaceDestroyed = nullptr
    };
    auto code = surfaceHolder.AddSurfaceCallback(&surfaceCallback);
    EXPECT_EQ(code, ERROR_CODE_NO_ERROR);
    /**
     * @tc.steps: step3. change surface life cycle callback functions pointers after add the callback to SurfaceHolder
     * @tc.expected: surface life cycle callback functions pointers are not nullptrs;
     */
    surfaceCallback.OnSurfaceCreated = [](OH_ArkUI_SurfaceHolder* /* surfaceHolder */) { g_isCreated = true; };
    surfaceCallback.OnSurfaceChanged = [](OH_ArkUI_SurfaceHolder* /* surfaceHolder */, uint64_t width,
        uint64_t height) { g_isChanged = true; };
    surfaceCallback.OnSurfaceDestroyed = [](OH_ArkUI_SurfaceHolder* /* surfaceHolder */) { g_isDestroyed = true; };
    ASSERT_TRUE(surfaceCallback.OnSurfaceCreated);
    ASSERT_TRUE(surfaceCallback.OnSurfaceChanged);
    ASSERT_TRUE(surfaceCallback.OnSurfaceDestroyed);
    /**
     * @tc.steps: step4. call OnAttachToMainTree after change the surface life cycle callback functions pointers
     * @tc.expected: OnSurfaceCreated has called
     */
    EXPECT_TRUE(pattern->autoInitialize_);
    pattern->OnAttachToMainTree();
    EXPECT_TRUE(g_isCreated);
    /**
     * @tc.steps: step5. call BeforeSyncGeometryProperties
     * @tc.expected: OnSurfaceChanged has called
     */
    DirtySwapConfig config;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    frameNode->geometryNode_ = geometryNode;
    config.skipMeasure = false;
    geometryNode->SetFrameSize(MAX_SIZE);
    geometryNode->SetContentSize(MAX_SIZE);
    pattern->BeforeSyncGeometryProperties(config);
    EXPECT_TRUE(g_isChanged);
    /**
     * @tc.steps: step6. call OnDetachFromFrameNode
     * @tc.expected: onSurfaceDestroyed has called
     */
    pattern->OnDetachFromMainTree();
    EXPECT_TRUE(g_isDestroyed);
}

/**
 * @tc.name: XComponentSurfaceHolderTest001
 * @tc.desc: Test SurfaceHolder AddSurfaceCallback and RemoveSurfaceCallback method
 * @tc.type: FUNC
 */
HWTEST_F(XComponentV2TestNg, XComponentSurfaceHolderTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare SurfaceHolder and SurfaceCallback
     */
    OH_ArkUI_SurfaceHolder surfaceHolder;
    OH_ArkUI_SurfaceCallback surfaceCallback;
    /**
     * @tc.steps: step2. add SurfaceCallback to SurfaceHolder
     * @tc.expected: add SurfaceCallback successfully
     */
    auto code = surfaceHolder.AddSurfaceCallback(&surfaceCallback);
    EXPECT_EQ(code, ERROR_CODE_NO_ERROR);
    /**
     * @tc.steps: step3. add duplicated SurfaceCallback to SurfaceHolder
     * @tc.expected: add SurfaceCallback failed
     */
    code = surfaceHolder.AddSurfaceCallback(&surfaceCallback);
    EXPECT_EQ(code, ERROR_CODE_PARAM_INVALID);
    /**
     * @tc.steps: step4. remove SurfaceCallback from SurfaceHolder
     * @tc.expected: remove SurfaceCallback successfully
     */
    code = surfaceHolder.RemoveSurfaceCallback(&surfaceCallback);
    EXPECT_EQ(code, ERROR_CODE_NO_ERROR);
    /**
     * @tc.steps: step5. remove nonexistent SurfaceCallback from SurfaceHolder
     * @tc.expected: remove SurfaceCallback failed
     */
    code = surfaceHolder.RemoveSurfaceCallback(&surfaceCallback);
    EXPECT_EQ(code, ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: SetExpectedRateRangeTest
 * @tc.desc: Test SetExpectedRateRange method
 * @tc.type: FUNC
 */
HWTEST_F(XComponentV2TestNg, SetExpectedRateRangeTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateXComponentNode
     * @tc.expected: xcomponent frameNode create successfully
     */
    auto frameNode = CreateXComponentNode();
    ASSERT_TRUE(frameNode);
    ASSERT_EQ(frameNode->GetTag(), V2::XCOMPONENT_ETS_TAG);
    auto pattern = frameNode->GetPattern<XComponentPatternV2>();
    ASSERT_TRUE(pattern);
    /**
     * @tc.steps: step2. call SetExpectedRateRangeTest
     * @tc.expected: return code CODE_NO_ERROR
     */
    auto code = XComponentModelNG::SetExpectedRateRange(AceType::RawPtr(frameNode), MIN_RATE, MAX_RATE, EXPECTED_RATE);
    ASSERT_EQ(code, CODE_NO_ERROR);
    /**
     * @tc.steps: step3. call SetExpectedRateRangeTest after get Native XComponent
     * @tc.expected: return code CODE_PARAM_INVALID
     */
    pattern->hasGotNativeXComponent_ = true;
    code = XComponentModelNG::SetExpectedRateRange(AceType::RawPtr(frameNode), MIN_RATE, MAX_RATE, EXPECTED_RATE);
    ASSERT_EQ(code, CODE_PARAM_INVALID);
}

/**
 * @tc.name: SetOnFrameCallbackTest
 * @tc.desc: Test SetOnFrameCallback method
 * @tc.type: FUNC
 */
HWTEST_F(XComponentV2TestNg, SetOnFrameCallbackTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateXComponentNode
     * @tc.expected: xcomponent frameNode create successfully
     */
    auto frameNode = CreateXComponentNode();
    ASSERT_TRUE(frameNode);
    ASSERT_EQ(frameNode->GetTag(), V2::XCOMPONENT_ETS_TAG);
    auto pattern = frameNode->GetPattern<XComponentPatternV2>();
    ASSERT_TRUE(pattern);
    /**
     * @tc.steps: step2. call SetOnFrameCallback
     * @tc.expected: return code CODE_NO_ERROR
     */
    auto code = XComponentModelNG::SetOnFrameCallback(AceType::RawPtr(frameNode), nullptr, nullptr);
    ASSERT_EQ(code, CODE_NO_ERROR);
    /**
     * @tc.steps: step3. call SetOnFrameCallback after get Native XComponent
     * @tc.expected: return code CODE_PARAM_INVALID
     */
    pattern->hasGotNativeXComponent_ = true;
    code = XComponentModelNG::SetOnFrameCallback(AceType::RawPtr(frameNode), nullptr, nullptr);
    ASSERT_EQ(code, CODE_PARAM_INVALID);
}

/**
 * @tc.name: UnregisterOnFrameCallbackTest
 * @tc.desc: Test UnregisterOnFrameCallback method
 * @tc.type: FUNC
 */
HWTEST_F(XComponentV2TestNg, UnregisterOnFrameCallbackTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateXComponentNode
     * @tc.expected: xcomponent frameNode create successfully
     */
    auto frameNode = CreateXComponentNode();
    ASSERT_TRUE(frameNode);
    ASSERT_EQ(frameNode->GetTag(), V2::XCOMPONENT_ETS_TAG);
    auto pattern = frameNode->GetPattern<XComponentPatternV2>();
    ASSERT_TRUE(pattern);
    /**
     * @tc.steps: step2. call UnregisterOnFrameCallback
     * @tc.expected: return code CODE_NO_ERROR
     */
    auto code = XComponentModelNG::UnregisterOnFrameCallback(AceType::RawPtr(frameNode));
    ASSERT_EQ(code, CODE_NO_ERROR);
    /**
     * @tc.steps: step3. call UnregisterOnFrameCallback after get Native XComponent
     * @tc.expected: return code CODE_PARAM_INVALID
     */
    pattern->hasGotNativeXComponent_ = true;
    code = XComponentModelNG::UnregisterOnFrameCallback(AceType::RawPtr(frameNode));
    ASSERT_EQ(code, CODE_PARAM_INVALID);
}

/**
 * @tc.name: SetNeedSoftKeyboardTest
 * @tc.desc: Test SetNeedSoftKeyboard method
 * @tc.type: FUNC
 */
HWTEST_F(XComponentV2TestNg, SetNeedSoftKeyboardTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateXComponentNode
     * @tc.expected: xcomponent frameNode create successfully
     */
    auto frameNode = CreateXComponentNode();
    ASSERT_TRUE(frameNode);
    ASSERT_EQ(frameNode->GetTag(), V2::XCOMPONENT_ETS_TAG);
    auto pattern = frameNode->GetPattern<XComponentPatternV2>();
    ASSERT_TRUE(pattern);
    /**
     * @tc.steps: step2. call SetNeedSoftKeyboard
     * @tc.expected: return code CODE_NO_ERROR
     */
    auto code = XComponentModelNG::SetNeedSoftKeyboard(AceType::RawPtr(frameNode), true);
    ASSERT_EQ(code, CODE_NO_ERROR);
    ASSERT_EQ(pattern->isNeedSoftKeyboard_, true);
    /**
     * @tc.steps: step3. call SetNeedSoftKeyboard after get Native XComponent
     * @tc.expected: return code CODE_PARAM_INVALID
     */
    pattern->hasGotNativeXComponent_ = true;
    code = XComponentModelNG::SetNeedSoftKeyboard(AceType::RawPtr(frameNode), false);
    ASSERT_EQ(code, CODE_PARAM_INVALID);
    ASSERT_EQ(pattern->isNeedSoftKeyboard_, true);
}

/**
 * @tc.name: CreateAndDisposeAccessibilityProviderTest
 * @tc.desc: Test CreateAccessibilityProvider and DisposeAccessibilityProvider method
 * @tc.type: FUNC
 */
HWTEST_F(XComponentV2TestNg, CreateAndDisposeAccessibilityProviderTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateXComponentNode
     * @tc.expected: xcomponent frameNode create successfully
     */
    auto frameNode = CreateXComponentNode();
    ASSERT_TRUE(frameNode);
    ASSERT_EQ(frameNode->GetTag(), V2::XCOMPONENT_ETS_TAG);
    auto pattern = frameNode->GetPattern<XComponentPatternV2>();
    ASSERT_TRUE(pattern);
    /**
     * @tc.steps: step2. call CreateAccessibilityProvider
     * @tc.expected: return a provider pointer which is not nullptr
     */
    auto provider = reinterpret_cast<ArkUI_AccessibilityProvider*>(
        XComponentModelNG::CreateAccessibilityProvider(AceType::RawPtr(frameNode)));
    ASSERT_TRUE(provider);
    /**
     * @tc.steps: step3. call CreateAccessibilityProvider again
     * @tc.expected: return a provider which equals to the former
     */
    auto provider_repeat = reinterpret_cast<ArkUI_AccessibilityProvider*>(
        XComponentModelNG::CreateAccessibilityProvider(AceType::RawPtr(frameNode)));
    ASSERT_EQ(provider, provider_repeat);
    /**
     * @tc.steps: step4. call CreateAccessibilityProvider after get Native XComponent
     * @tc.expected: return nullptr
     */
    pattern->hasGotNativeXComponent_ = true;
    auto provider_null = reinterpret_cast<ArkUI_AccessibilityProvider*>(
        XComponentModelNG::CreateAccessibilityProvider(AceType::RawPtr(frameNode)));
    ASSERT_FALSE(provider_null);
    /**
     * @tc.steps: step5. call DisposeAccessibilityProvider after get Native XComponent
     * @tc.expected: return nullptr
     */
    XComponentModelNG::DisposeAccessibilityProvider(provider);
    ASSERT_TRUE(pattern->arkuiAccessibilityProvider_);
    /**
     * @tc.steps: step6. call DisposeAccessibilityProvider for invalid provider
     * @tc.expected: dispose failed
     */
    pattern->hasGotNativeXComponent_ = false;
    auto provider_invalid = new ArkUI_AccessibilityProvider();
    XComponentModelNG::DisposeAccessibilityProvider(provider_invalid);
    ASSERT_TRUE(pattern->arkuiAccessibilityProvider_);
    /**
     * @tc.steps: step7. call DisposeAccessibilityProvider for valid provider
     * @tc.expected: dispose success
     */
    XComponentModelNG::DisposeAccessibilityProvider(provider);
    ASSERT_FALSE(pattern->arkuiAccessibilityProvider_);
    delete provider_invalid;
}

/**
 * @tc.name: GetRSTransactionHandlerTest001
 * @tc.desc: Test GetRSTransactionHandler method when multiInstanceEnabled is false
 * @tc.type: FUNC
 */
HWTEST_F(XComponentV2TestNg, GetRSTransactionHandlerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set multiInstanceEnabled property to false
     * @tc.expected: multiInstanceEnabled is false
     */
    SystemProperties::multiInstanceEnabled_ = false;
    ASSERT_FALSE(SystemProperties::multiInstanceEnabled_);

    auto frameNode = CreateXComponentNode();
    ASSERT_TRUE(frameNode);
    ASSERT_EQ(frameNode->GetTag(), V2::XCOMPONENT_ETS_TAG);
    auto xcomponentPattern = frameNode->GetPattern<XComponentPatternV2>();
    ASSERT_NE(xcomponentPattern, nullptr);
    auto hostNode = xcomponentPattern->GetHost();
    /**
     * @tc.steps: step2. call GetRSTransactionHandle
     * @tc.expected: GetRSTransactionHandle return nullptr
     */
    auto transactionHandler = xcomponentPattern->GetRSTransactionHandler(hostNode);
    ASSERT_EQ(transactionHandler, nullptr);
}

/**
 * @tc.name: GetRSTransactionHandlerTest002
 * @tc.desc: Test GetRSTransactionHandler method when multiInstanceEnabled is true
 * @tc.type: FUNC
 */
HWTEST_F(XComponentV2TestNg, GetRSTransactionHandlerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set multiInstanceEnabled property to true
     * @tc.expected: multiInstanceEnabled is true
     */
    SystemProperties::multiInstanceEnabled_ = true;
    ASSERT_TRUE(SystemProperties::multiInstanceEnabled_);
    /**
     * @tc.steps: step2. create new xcomponent node
     * @tc.expected: create xcomponent node, do not set a RSUIContext
     */
    auto frameNode = CreateXComponentNode();
    ASSERT_TRUE(frameNode);
    ASSERT_EQ(frameNode->GetTag(), V2::XCOMPONENT_ETS_TAG);
    auto xcomponentPattern = frameNode->GetPattern<XComponentPatternV2>();
    ASSERT_NE(xcomponentPattern, nullptr);
    auto hostNode = xcomponentPattern->GetHost();
    /**
     * @tc.steps: step3. call GetRSTransactionHandle
     * @tc.expected: GetRSTransactionHandle return nullptr
     */
    auto transactionHandler = xcomponentPattern->GetRSTransactionHandler(hostNode);
    ASSERT_EQ(transactionHandler, nullptr);
}

/**
 * @tc.name: GetRSUIContextTest001
 * @tc.desc: Test GetRSUIContext method when framenode is a new node
 * @tc.type: FUNC
 */
HWTEST_F(XComponentV2TestNg, GetRSUIContextTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set multiInstanceEnabled property to false
     * @tc.expected: multiInstanceEnabled is false
     */
    SystemProperties::multiInstanceEnabled_ = false;
    ASSERT_FALSE(SystemProperties::multiInstanceEnabled_);
    /**
     * @tc.steps: step2. create xcomponent frameNode by GetOrCreateFrameNode
     * @tc.expected: xcomponent frameNode create successfully
     */
    auto* stack = ViewStackProcessor::GetInstance();
    XComponentType type = XComponentType::COMPONENT;
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::XCOMPONENT_ETS_TAG, stack->ClaimNodeId(), [type]() {
            return AceType::MakeRefPtr<XComponentPatternV2>(type, XComponentNodeType::DECLARATIVE_NODE); });
    ASSERT_TRUE(frameNode);
    ASSERT_EQ(frameNode->GetTag(), V2::XCOMPONENT_ETS_TAG);
    auto xcomponentPattern = frameNode->GetPattern<XComponentPatternV2>();
    ASSERT_NE(xcomponentPattern, nullptr);
    /**
     * @tc.steps: step3. call GetRSUIContext
     * @tc.expected: GetRSUIContext return nullptr
     */
    auto transactionHandler = xcomponentPattern->GetRSUIContext(frameNode);
    ASSERT_EQ(transactionHandler, nullptr);
}

/**
 * @tc.name: GetRSUIContextTest002
 * @tc.desc: Test GetRSUIContext method when frameNode is host node
 * @tc.type: FUNC
 */
HWTEST_F(XComponentV2TestNg, GetRSUIContextTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set multiInstanceEnabled property to false
     * @tc.expected: multiInstanceEnabled is false
     */
    SystemProperties::multiInstanceEnabled_ = false;
    ASSERT_FALSE(SystemProperties::multiInstanceEnabled_);
    /**
     * @tc.steps: step2. create xcomponent frameNode by XComponentModelNG
     * @tc.expected: xcomponent frameNode create successfully
     */
    auto frameNode = CreateXComponentNode();
    ASSERT_TRUE(frameNode);
    ASSERT_EQ(frameNode->GetTag(), V2::XCOMPONENT_ETS_TAG);
    auto xcomponentPattern = frameNode->GetPattern<XComponentPatternV2>();
    ASSERT_NE(xcomponentPattern, nullptr);
    auto hostNode = xcomponentPattern->GetHost();
    /**
     * @tc.steps: step3. call GetRSUIContext
     * @tc.expected: GetRSUIContext return nullptr
     */
    auto transactionHandler = xcomponentPattern->GetRSUIContext(hostNode);
    ASSERT_EQ(transactionHandler, nullptr);
}

/**
 * @tc.name: GetRSUIContextTest003
 * @tc.desc: Test GetRSUIContext method when framenode is a new node
 * @tc.type: FUNC
 */
HWTEST_F(XComponentV2TestNg, GetRSUIContextTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set multiInstanceEnabled property to true
     * @tc.expected: multiInstanceEnabled is true
     */
    SystemProperties::multiInstanceEnabled_ = true;
    ASSERT_TRUE(SystemProperties::multiInstanceEnabled_);
    /**
     * @tc.steps: step2. create xcomponent frameNode by GetOrCreateFrameNode
     * @tc.expected: xcomponent frameNode create successfully
     */
    auto* stack = ViewStackProcessor::GetInstance();
    XComponentType type = XComponentType::COMPONENT;
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::XCOMPONENT_ETS_TAG, stack->ClaimNodeId(), [type]() {
            return AceType::MakeRefPtr<XComponentPatternV2>(type, XComponentNodeType::DECLARATIVE_NODE); });
    ASSERT_TRUE(frameNode);
    ASSERT_EQ(frameNode->GetTag(), V2::XCOMPONENT_ETS_TAG);
    auto xcomponentPattern = frameNode->GetPattern<XComponentPatternV2>();
    ASSERT_NE(xcomponentPattern, nullptr);
    /**
     * @tc.steps: step3. call GetRSUIContext
     * @tc.expected: GetRSUIContext return nullptr
     */
    auto transactionHandler = xcomponentPattern->GetRSUIContext(frameNode);
    ASSERT_EQ(transactionHandler, nullptr);
}

/**
 * @tc.name: GetRSUIContextTest004
 * @tc.desc: Test GetRSUIContext method when frameNode is host node
 * @tc.type: FUNC
 */
HWTEST_F(XComponentV2TestNg, GetRSUIContextTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set multiInstanceEnabled property to true
     * @tc.expected: multiInstanceEnabled is true
     */
    SystemProperties::multiInstanceEnabled_ = true;
    ASSERT_TRUE(SystemProperties::multiInstanceEnabled_);
    /**
     * @tc.steps: step2. create xcomponent frameNode by XComponentModelNG
     * @tc.expected: xcomponent frameNode create successfully
     */
    auto frameNode = CreateXComponentNode();
    ASSERT_TRUE(frameNode);
    ASSERT_EQ(frameNode->GetTag(), V2::XCOMPONENT_ETS_TAG);
    auto xcomponentPattern = frameNode->GetPattern<XComponentPatternV2>();
    ASSERT_NE(xcomponentPattern, nullptr);
    auto hostNode = xcomponentPattern->GetHost();
    /**
     * @tc.steps: step3. call GetRSUIContext
     * @tc.expected: GetRSUIContext return nullptr
     */
    auto transactionHandler = xcomponentPattern->GetRSUIContext(hostNode);
    ASSERT_EQ(transactionHandler, nullptr);
}

/**
 * @tc.name: FlushImplicitTransaction001
 * @tc.desc: Test FlushImplicitTransaction method
 * @tc.type: FUNC
 */
HWTEST_F(XComponentV2TestNg, FlushImplicitTransaction001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set multiInstanceEnabled property to false
     * @tc.expected: multiInstanceEnabled is false
     */
    SystemProperties::multiInstanceEnabled_ = false;
    ASSERT_FALSE(SystemProperties::multiInstanceEnabled_);

    params.type = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = AceType::DynamicCast<FrameNode>(XComponentModelNG().CreateTypeNode(nodeId, &params));

    ASSERT_TRUE(frameNode);
    auto xcomponentPattern = frameNode->GetPattern<XComponentPatternV2>();
    ASSERT_NE(xcomponentPattern, nullptr);
    auto hostNode = xcomponentPattern->GetHost();
    /**
     * @tc.steps: step2. call FlushImplicitTransaction
     * @tc.expected: FlushImplicitTransaction return nullptr
     */
    xcomponentPattern->FlushImplicitTransaction(hostNode);
    EXPECT_EQ(frameNode->GetId(), nodeId);
}

/**
 * @tc.name: FlushImplicitTransaction002
 * @tc.desc: Test FlushImplicitTransaction method
 * @tc.type: FUNC
 */
HWTEST_F(XComponentV2TestNg, FlushImplicitTransaction002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set multiInstanceEnabled property to false
     * @tc.expected: multiInstanceEnabled is false
     */
    SystemProperties::multiInstanceEnabled_ = true;
    ASSERT_TRUE(SystemProperties::multiInstanceEnabled_);

    params.type = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = AceType::DynamicCast<FrameNode>(XComponentModelNG().CreateTypeNode(nodeId, &params));

    ASSERT_TRUE(frameNode);
    auto xcomponentPattern = frameNode->GetPattern<XComponentPatternV2>();
    ASSERT_NE(xcomponentPattern, nullptr);
    auto hostNode = xcomponentPattern->GetHost();
    /**
     * @tc.steps: step2. call FlushImplicitTransaction
     * @tc.expected: FlushImplicitTransaction return nullptr
     */
    xcomponentPattern->FlushImplicitTransaction(hostNode);
    EXPECT_EQ(frameNode->GetId(), nodeId);
}
} // namespace OHOS::Ace::NG
