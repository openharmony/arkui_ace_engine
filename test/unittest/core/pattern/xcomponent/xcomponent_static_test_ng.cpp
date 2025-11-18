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
#include "core/components_ng/pattern/xcomponent/xcomponent_controller_ng.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_layout_algorithm.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_model_ng.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_model_static.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern_v2.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_surface_holder.h"
#include "core/components_ng/property/measure_property.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr XComponentType XCOMPONENT_SURFACE_TYPE_VALUE = XComponentType::SURFACE;
const std::string XCOMPONENT_ID = "xcomponentId";
constexpr uint64_t SCREEN_ID = 1;
void* g_nativeXComponent = nullptr;
} // namespace

class XComponentStaticTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void TearDown() override
    {
        g_nativeXComponent = nullptr;
    }

protected:
    static RefPtr<FrameNode> CreateXComponentNode(bool isTypeNode);
};

void XComponentStaticTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void XComponentStaticTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> XComponentStaticTestNg::CreateXComponentNode(bool isTypeNode)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = AceType::DynamicCast<FrameNode>(XComponentModelStatic::CreateFrameNode(nodeId, isTypeNode));
    return frameNode;
}

/**
 * @tc.name: SetXComponentControllerStaticTest
 * @tc.desc: Test XComponentModelStatic SetXComponentController func.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentStaticTestNg, SetXComponentControllerStaticTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateXComponentNode
     * @tc.expected: xcomponent frameNode create successfully
     */
    auto frameNode = CreateXComponentNode(false);
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::XCOMPONENT_ETS_TAG);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    EXPECT_EQ(pattern->type_, XComponentType::UNKNOWN);
    /**
     * @tc.steps: step2. call SetXComponentController
     * @tc.expected: set xcomponent controller successfully
     */
    auto frameNodePtr = AceType::RawPtr(frameNode);
    auto controller = std::make_shared<XComponentControllerNG>();
    XComponentModelStatic::SetXComponentController(frameNodePtr, controller);
    EXPECT_EQ(pattern->xcomponentController_, controller);
    EXPECT_TRUE(pattern->xcomponentController_);
    /**
     * @tc.steps: step3. call SetXComponentController to update XComponentController
     * @tc.expected: set xcomponent controller is not updated
     */
    auto controllerUpdate = std::make_shared<XComponentControllerNG>();
    XComponentModelStatic::SetXComponentController(frameNodePtr, controllerUpdate);
    EXPECT_NE(pattern->xcomponentController_, controllerUpdate);
}

/**
 * @tc.name: InitParamsTest
 * @tc.desc: Test XComponentModelStatic InitParams func.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentStaticTestNg, InitParamsTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateXComponentNode
     * @tc.expected: xcomponent frameNode create successfully
     */
    auto frameNode = CreateXComponentNode(true);
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::XCOMPONENT_ETS_TAG);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    EXPECT_EQ(pattern->type_, XComponentType::UNKNOWN);
    /**
     * @tc.steps: step2. set xcomponent parameters and initialize xcomponent type
     * @tc.expected: set xcomponent parameters successfully
     */
    auto frameNodePtr = AceType::RawPtr(frameNode);
    XComponentModelStatic::SetXComponentType(frameNodePtr, XCOMPONENT_SURFACE_TYPE_VALUE);
    XComponentModelStatic::InitParams(frameNodePtr);
    XComponentModelStatic::SetXComponentId(frameNodePtr, XCOMPONENT_ID);
    auto handler = [](void* ptr) {
        g_nativeXComponent = ptr;
    };
    XComponentModelStatic::SetNativeXComponentHandler(frameNodePtr, handler);
    EXPECT_EQ(pattern->type_, XCOMPONENT_SURFACE_TYPE_VALUE);
    EXPECT_EQ(pattern->id_, XCOMPONENT_ID);
    /**
     * @tc.steps: step3. call InitParams
     * @tc.expected: set xcomponent parameters successfully
     */
    XComponentModelStatic::InitParams(frameNodePtr);
    EXPECT_TRUE(pattern->nativeXComponent_);
    EXPECT_EQ(g_nativeXComponent, pattern->nativeXComponent_.get());
}

/**
 * @tc.name: MarkBindNativeTest
 * @tc.desc: Test XComponentModelStatic MarkBindNative func.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentStaticTestNg, MarkBindNative, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateXComponentNode
     * @tc.expected: xcomponent frameNode create successfully
     */
    auto frameNode = CreateXComponentNode(false);
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::XCOMPONENT_ETS_TAG);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    EXPECT_EQ(pattern->type_, XComponentType::UNKNOWN);
    /**
     * @tc.steps: step2. call MarkBindNative and SetXComponentId
     * @tc.expected: xcomponent id is not updated
     */
    auto frameNodePtr = AceType::RawPtr(frameNode);
    XComponentModelStatic::MarkBindNative(frameNodePtr);
    XComponentModelStatic::SetXComponentId(frameNodePtr, XCOMPONENT_ID);
    XComponentModelStatic::SetScreenId(frameNodePtr, SCREEN_ID);
    EXPECT_NE(pattern->id_, XCOMPONENT_ID);
    EXPECT_EQ(pattern->screenId_, std::nullopt);
}

/**
 * @tc.name: OnModifyDoneTest
 * @tc.desc: Test XComponentStaticPattern OnModifyDone func.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentStaticTestNg, OnModifyDoneTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateXComponentNode
     * @tc.expected: xcomponent frameNode create successfully
     */
    auto frameNode = CreateXComponentNode(false);
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::XCOMPONENT_ETS_TAG);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    EXPECT_EQ(pattern->type_, XComponentType::UNKNOWN);
    /**
     * @tc.steps: step2. call InitParams
     * @tc.expected: surface node is created
     */
    auto frameNodePtr = AceType::RawPtr(frameNode);
    XComponentModelStatic::SetXComponentType(frameNodePtr, XCOMPONENT_SURFACE_TYPE_VALUE);
    XComponentModelStatic::InitParams(frameNodePtr);
    EXPECT_TRUE(pattern->renderContextForSurface_);
    pattern->renderFit_ = RenderFit::TOP_LEFT;
    /**
     * @tc.steps: step3. call OnModifyDone
     * @tc.expected: renderFit property is updated
     */
    pattern->OnModifyDone();
    EXPECT_EQ(pattern->renderFit_, RenderFit::RESIZE_FILL);
}
} // namespace OHOS::Ace::NG
