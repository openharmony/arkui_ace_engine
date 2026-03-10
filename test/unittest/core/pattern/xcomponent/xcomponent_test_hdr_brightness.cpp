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

#include "gtest/gtest.h"

#include <optional>
#include <iostream>

#define private public
#define protected public

#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/render/mock_render_surface.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_controller_ng.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_model_ng.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string XCOMPONENT_ID = "xcomponent";
const std::string XCOMPONENT_LIBRARY_NAME = "native_render";
constexpr XComponentType XCOMPONENT_SURFACE_TYPE_VALUE = XComponentType::SURFACE;
constexpr XComponentType XCOMPONENT_COMPONENT_TYPE_VALUE = XComponentType::COMPONENT;
constexpr XComponentType XCOMPONENT_TEXTURE_TYPE_VALUE = XComponentType::TEXTURE;
constexpr XComponentType XCOMPONENT_NODE_TYPE_VALUE = XComponentType::NODE;
} // namespace

class XComponentTestHdrBrightness : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void TearDown() override {}
protected:
    static RefPtr<FrameNode> CreateXComponentNode(XComponentType type);
};

RefPtr<FrameNode> XComponentTestHdrBrightness::CreateXComponentNode(XComponentType type)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto xcomponentController = std::make_shared<XComponentControllerNG>();
    XComponentModelNG().Create(XCOMPONENT_ID, type, XCOMPONENT_LIBRARY_NAME, xcomponentController);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    return AceType::DynamicCast<FrameNode>(element);
}

void XComponentTestHdrBrightness::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void XComponentTestHdrBrightness::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: HdrBrightnessTest001
 * @tc.desc: Test HdrBrightness with valid parameters on SURFACE type
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestHdrBrightness, HdrBrightnessTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create xcomponent node with SURFACE type
     * @tc.expected: frameNode created successfully
     */
    auto frameNode = CreateXComponentNode(XCOMPONENT_SURFACE_TYPE_VALUE);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetTag(), V2::XCOMPONENT_ETS_TAG);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Initialize renderContextForSurface_
     * @tc.expected: renderContextForSurface_ initialized
     */
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    pattern->renderContextForSurface_ = mockRenderContext;
    ASSERT_NE(pattern->renderContextForSurface_, nullptr);

    /**
     * @tc.steps: step3. Call HdrBrightness with DEFAULT HdrType
     * @tc.expected: hdrBrightness_ and hdrType_ set correctly
     */
    float testBrightness = 0.5f;
    pattern->HdrBrightness(testBrightness, HdrType::DEFAULT);
    EXPECT_EQ(pattern->hdrBrightness_, testBrightness);
    EXPECT_EQ(pattern->hdrType_, HdrType::DEFAULT);
}

/**
 * @tc.name: HdrBrightnessTest002
 * @tc.desc: Test HdrBrightness with AIHDR HdrType
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestHdrBrightness, HdrBrightnessTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create xcomponent node with SURFACE type
     * @tc.expected: frameNode created successfully
     */
    auto frameNode = CreateXComponentNode(XCOMPONENT_SURFACE_TYPE_VALUE);
    ASSERT_NE(frameNode, nullptr);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Initialize renderContextForSurface_
     * @tc.expected: renderContextForSurface_ initialized
     */
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    pattern->renderContextForSurface_ = mockRenderContext;

    /**
     * @tc.steps: step3. Call HdrBrightness with AIHDR HdrType
     * @tc.expected: hdrBrightness_ and hdrType_ set correctly
     */
    float testBrightness = 0.75f;
    pattern->HdrBrightness(testBrightness, HdrType::AIHDR);
    EXPECT_EQ(pattern->hdrBrightness_, testBrightness);
    EXPECT_EQ(pattern->hdrType_, HdrType::AIHDR);
}

/**
 * @tc.name: HdrBrightnessTest003
 * @tc.desc: Test HdrBrightness with brightness value > 1.0f (clamp behavior)
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestHdrBrightness, HdrBrightnessTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create xcomponent node with SURFACE type
     * @tc.expected: frameNode created successfully
     */
    auto frameNode = CreateXComponentNode(XCOMPONENT_SURFACE_TYPE_VALUE);
    ASSERT_NE(frameNode, nullptr);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Initialize renderContextForSurface_
     * @tc.expected: renderContextForSurface_ initialized
     */
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    pattern->renderContextForSurface_ = mockRenderContext;

    /**
     * @tc.steps: step3. Call HdrBrightness with brightness > 1.0f
     * @tc.expected: hdrBrightness_ clamped to 1.0f
     */
    float testBrightness = 1.5f;
    pattern->HdrBrightness(testBrightness, HdrType::DEFAULT);
    EXPECT_FLOAT_EQ(pattern->hdrBrightness_, 1.0f);
    EXPECT_EQ(pattern->hdrType_, HdrType::DEFAULT);
}

/**
 * @tc.name: HdrBrightnessTest004
 * @tc.desc: Test HdrBrightness with brightness value < 0.0f (clamp behavior)
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestHdrBrightness, HdrBrightnessTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create xcomponent node with SURFACE type
     * @tc.expected: frameNode created successfully
     */
    auto frameNode = CreateXComponentNode(XCOMPONENT_SURFACE_TYPE_VALUE);
    ASSERT_NE(frameNode, nullptr);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Initialize renderContextForSurface_
     * @tc.expected: renderContextForSurface_ initialized
     */
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    pattern->renderContextForSurface_ = mockRenderContext;

    /**
     * @tc.steps: step3. Call HdrBrightness with brightness < 0.0f
     * @tc.expected: hdrBrightness_ clamped to 0.0f
     */
    float testBrightness = -0.5f;
    pattern->HdrBrightness(testBrightness, HdrType::DEFAULT);
    EXPECT_FLOAT_EQ(pattern->hdrBrightness_, 0.0f);
    EXPECT_EQ(pattern->hdrType_, HdrType::DEFAULT);
}

/**
 * @tc.name: HdrBrightnessTest005
 * @tc.desc: Test HdrBrightness with boundary values (0.0f and 1.0f)
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestHdrBrightness, HdrBrightnessTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create xcomponent node with SURFACE type
     * @tc.expected: frameNode created successfully
     */
    auto frameNode = CreateXComponentNode(XCOMPONENT_SURFACE_TYPE_VALUE);
    ASSERT_NE(frameNode, nullptr);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Initialize renderContextForSurface_
     * @tc.expected: renderContextForSurface_ initialized
     */
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    pattern->renderContextForSurface_ = mockRenderContext;

    /**
     * @tc.steps: step3. Call HdrBrightness with brightness = 0.0f
     * @tc.expected: hdrBrightness_ = 0.0f
     */
    pattern->HdrBrightness(0.0f, HdrType::DEFAULT);
    EXPECT_FLOAT_EQ(pattern->hdrBrightness_, 0.0f);

    /**
     * @tc.steps: step4. Call HdrBrightness with brightness = 1.0f
     * @tc.expected: hdrBrightness_ = 1.0f
     */
    pattern->HdrBrightness(1.0f, HdrType::AIHDR);
    EXPECT_FLOAT_EQ(pattern->hdrBrightness_, 1.0f);
    EXPECT_EQ(pattern->hdrType_, HdrType::AIHDR);
}

/**
 * @tc.name: HdrBrightnessTest006
 * @tc.desc: Test HdrBrightness with COMPONENT type (should return early)
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestHdrBrightness, HdrBrightnessTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create xcomponent node with COMPONENT type
     * @tc.expected: frameNode created successfully
     */
    auto frameNode = CreateXComponentNode(XCOMPONENT_COMPONENT_TYPE_VALUE);
    ASSERT_NE(frameNode, nullptr);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Initialize renderContextForSurface_
     * @tc.expected: renderContextForSurface_ initialized
     */
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    pattern->renderContextForSurface_ = mockRenderContext;

    /**
     * @tc.steps: step3. Call HdrBrightness with COMPONENT type
     * @tc.expected: hdrBrightness_ and hdrType_ not changed (default values)
     */
    float initialBrightness = pattern->hdrBrightness_;
    HdrType initialType = pattern->hdrType_;

    pattern->HdrBrightness(0.8f, HdrType::AIHDR);

    EXPECT_EQ(pattern->hdrBrightness_, initialBrightness);
    EXPECT_EQ(pattern->hdrType_, initialType);
}

/**
 * @tc.name: HdrBrightnessTest007
 * @tc.desc: Test HdrBrightness with TEXTURE type (should return early)
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestHdrBrightness, HdrBrightnessTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create xcomponent node with TEXTURE type
     * @tc.expected: frameNode created successfully
     */
    auto frameNode = CreateXComponentNode(XCOMPONENT_TEXTURE_TYPE_VALUE);
    ASSERT_NE(frameNode, nullptr);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Initialize renderContextForSurface_
     * @tc.expected: renderContextForSurface_ initialized
     */
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    pattern->renderContextForSurface_ = mockRenderContext;

    /**
     * @tc.steps: step3. Call HdrBrightness with TEXTURE type
     * @tc.expected: hdrBrightness_ and hdrType_ not changed (default values)
     */
    float initialBrightness = pattern->hdrBrightness_;
    HdrType initialType = pattern->hdrType_;

    pattern->HdrBrightness(0.6f, HdrType::AIHDR);

    EXPECT_EQ(pattern->hdrBrightness_, initialBrightness);
    EXPECT_EQ(pattern->hdrType_, initialType);
}

/**
 * @tc.name: HdrBrightnessTest008
 * @tc.desc: Test HdrBrightness with NODE type (should return early)
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestHdrBrightness, HdrBrightnessTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create xcomponent node with NODE type
     * @tc.expected: frameNode created successfully
     */
    auto frameNode = CreateXComponentNode(XCOMPONENT_NODE_TYPE_VALUE);
    ASSERT_NE(frameNode, nullptr);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Initialize renderContextForSurface_
     * @tc.expected: renderContextForSurface_ initialized
     */
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    pattern->renderContextForSurface_ = mockRenderContext;

    /**
     * @tc.steps: step3. Call HdrBrightness with NODE type
     * @tc.expected: hdrBrightness_ and hdrType_ not changed (default values)
     */
    float initialBrightness = pattern->hdrBrightness_;
    HdrType initialType = pattern->hdrType_;

    pattern->HdrBrightness(0.9f, HdrType::AIHDR);

    EXPECT_EQ(pattern->hdrBrightness_, initialBrightness);
    EXPECT_EQ(pattern->hdrType_, initialType);
}

/**
 * @tc.name: HdrBrightnessTest009
 * @tc.desc: Test HdrBrightness with null renderContextForSurface_ (should return early)
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestHdrBrightness, HdrBrightnessTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create xcomponent node with SURFACE type
     * @tc.expected: frameNode created successfully
     */
    auto frameNode = CreateXComponentNode(XCOMPONENT_SURFACE_TYPE_VALUE);
    ASSERT_NE(frameNode, nullptr);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set renderContextForSurface_ to null
     * @tc.expected: renderContextForSurface_ is null
     */
    pattern->renderContextForSurface_ = nullptr;

    /**
     * @tc.steps: step3. Call HdrBrightness with null renderContextForSurface_
     * @tc.expected: hdrBrightness_ and hdrType_ not changed (default values)
     */
    float initialBrightness = pattern->hdrBrightness_;
    HdrType initialType = pattern->hdrType_;

    pattern->HdrBrightness(0.5f, HdrType::AIHDR);

    EXPECT_EQ(pattern->hdrBrightness_, initialBrightness);
    EXPECT_EQ(pattern->hdrType_, initialType);
}

/**
 * @tc.name: HdrBrightnessTest010
 * @tc.desc: Test HdrBrightness with multiple calls (update behavior)
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestHdrBrightness, HdrBrightnessTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create xcomponent node with SURFACE type
     * @tc.expected: frameNode created successfully
     */
    auto frameNode = CreateXComponentNode(XCOMPONENT_SURFACE_TYPE_VALUE);
    ASSERT_NE(frameNode, nullptr);

    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Initialize renderContextForSurface_
     * @tc.expected: renderContextForSurface_ initialized
     */
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    pattern->renderContextForSurface_ = mockRenderContext;

    /**
     * @tc.steps: step3. Call HdrBrightness multiple times with different values
     * @tc.expected: hdrBrightness_ and hdrType_ updated correctly on each call
     */
    pattern->HdrBrightness(0.3f, HdrType::DEFAULT);
    EXPECT_FLOAT_EQ(pattern->hdrBrightness_, 0.3f);
    EXPECT_EQ(pattern->hdrType_, HdrType::DEFAULT);

    pattern->HdrBrightness(0.6f, HdrType::AIHDR);
    EXPECT_FLOAT_EQ(pattern->hdrBrightness_, 0.6f);
    EXPECT_EQ(pattern->hdrType_, HdrType::AIHDR);

    pattern->HdrBrightness(0.9f, HdrType::DEFAULT);
    EXPECT_FLOAT_EQ(pattern->hdrBrightness_, 0.9f);
    EXPECT_EQ(pattern->hdrType_, HdrType::DEFAULT);
}

} // namespace OHOS::Ace::NG
