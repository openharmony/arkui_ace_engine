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
bool isCreated = false;
bool isChanged = false;
const float MAX_WIDTH = 400.0f;
const float MAX_HEIGHT = 400.0f;
const SizeF MAX_SIZE(MAX_WIDTH, MAX_HEIGHT);
const float CHILD_WIDTH = 200.0f;
const float CHILD_HEIGHT = 200.0f;
const SizeF CHILD_SIZE(CHILD_WIDTH, CHILD_HEIGHT);
} // namespace

class XComponentV2TestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void TearDown() override
    {
        isCreated = false;
        isChanged = false;
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
    surfaceCallback->OnSurfaceCreated = [](OH_ArkUI_SurfaceHolder* /* surfaceHolder */) { isCreated = true; };
    surfaceCallback->OnSurfaceDestroyed = [](OH_ArkUI_SurfaceHolder* /* surfaceHolder */) { isCreated = false; };
    surfaceCallback->OnSurfaceChanged = [](OH_ArkUI_SurfaceHolder* /* surfaceHolder */, uint64_t width,
                                            uint64_t height) { isChanged = true; };
    auto code = surfaceHolder->AddSurfaceCallback(surfaceCallback);
    EXPECT_EQ(code, ERROR_CODE_NO_ERROR);
    /**
     * @tc.steps: step3. call OnAttachToMainTree
     * @tc.expected: OnSurfaceCreated has called
     */
    EXPECT_TRUE(pattern->autoInitialize_);
    pattern->OnAttachToMainTree();
    EXPECT_TRUE(isCreated);
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
    EXPECT_FALSE(isChanged);
    config.skipMeasure = true;
    pattern->BeforeSyncGeometryProperties(config);
    EXPECT_FALSE(isChanged);
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
    EXPECT_TRUE(isChanged);
    /**
     * @tc.steps: step6. call OnDetachFromFrameNode
     * @tc.expected: onSurfaceDestroyed has called
     */
    pattern->OnDetachFromMainTree();
    EXPECT_FALSE(isCreated);
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
} // namespace OHOS::Ace::NG