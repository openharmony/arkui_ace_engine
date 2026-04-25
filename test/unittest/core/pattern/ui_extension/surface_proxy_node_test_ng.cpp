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

#include "gtest/gtest.h"
#include "base/memory/ace_type.h"
#define private public
#define protected public
#include "frameworks/core/components_ng/pattern/ui_extension/surface_proxy_node.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_ng/property/safe_area_insets.h"
#include "core/pipeline/base/element_register.h"
#include "frameworks/base/log/log_wrapper.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    const std::string TEST_HOST_TAG = "TestHostNode";
} // namespace

class SurfaceProxyNodeTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        NG::MockPipelineContext::SetUp();
        MockContainer::SetUp();
        MockContainer::Current()->pipelineContext_ = PipelineBase::GetCurrentContext();
    }
    static void TearDownTestSuite()
    {
        MockContainer::Current()->pipelineContext_ = nullptr;
        NG::MockPipelineContext::TearDown();
    }
    void SetUp() override {}
    void TearDown() override {}
};

/**
 * @tc.name: SurfaceProxyNodeTest001
 * @tc.desc: Test SetHostNode and GetSurfaceProxyNode with no host set
 * @tc.type: FUNC
 */
HWTEST_F(SurfaceProxyNodeTestNg, SurfaceProxyNodeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a SurfaceProxyNode
     */
    auto surfaceProxyNode = AceType::MakeRefPtr<SurfaceProxyNode>();
    ASSERT_NE(surfaceProxyNode, nullptr);

    /**
     * @tc.steps: step2. call GetSurfaceProxyNode before any host is set
     * @tc.expected: expect result is nullptr
     */
    auto proxyNode = surfaceProxyNode->GetSurfaceProxyNode();
    EXPECT_EQ(proxyNode, nullptr);
}

/**
 * @tc.name: SurfaceProxyNodeTest002
 * @tc.desc: Test AddSurfaceNode with null surface node
 * @tc.type: FUNC
 */
HWTEST_F(SurfaceProxyNodeTestNg, SurfaceProxyNodeTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a SurfaceProxyNode and set a valid host
     */
    auto surfaceProxyNode = AceType::MakeRefPtr<SurfaceProxyNode>();
    ASSERT_NE(surfaceProxyNode, nullptr);

    auto hostNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto hostNode = FrameNode::GetOrCreateFrameNode(
        TEST_HOST_TAG, hostNodeId, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(hostNode, nullptr);
    surfaceProxyNode->SetHostNode(hostNode);

    /**
     * @tc.steps: step2. call AddSurfaceNode with nullptr
     * @tc.expected: expect result is false
     */
    bool result = surfaceProxyNode->AddSurfaceNode(nullptr);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SurfaceProxyNodeTest003
 * @tc.desc: Test AddSurfaceNode with no host set (host_ is null)
 * @tc.type: FUNC
 */
HWTEST_F(SurfaceProxyNodeTestNg, SurfaceProxyNodeTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a SurfaceProxyNode without setting host
     */
    auto surfaceProxyNode = AceType::MakeRefPtr<SurfaceProxyNode>();
    ASSERT_NE(surfaceProxyNode, nullptr);

    /**
     * @tc.steps: step2. create a valid RSSurfaceNode
     */
    Rosen::RSSurfaceNodeConfig surfaceConfig;
    surfaceConfig.SurfaceNodeName = "testSurface";
    auto rsSurfaceNode = Rosen::RSSurfaceNode::Create(surfaceConfig);

    /**
     * @tc.steps: step3. call AddSurfaceNode without host
     * @tc.expected: expect result is false
     */
    bool result = surfaceProxyNode->AddSurfaceNode(rsSurfaceNode);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SurfaceProxyNodeTest004
 * @tc.desc: Test CreateSurfaceProxyNode creates a valid FrameNode and sets properties
 * @tc.type: FUNC
 */
HWTEST_F(SurfaceProxyNodeTestNg, SurfaceProxyNodeTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a SurfaceProxyNode with a valid host
     */
    auto surfaceProxyNode = AceType::MakeRefPtr<SurfaceProxyNode>();
    ASSERT_NE(surfaceProxyNode, nullptr);

    auto hostNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto hostNode = FrameNode::GetOrCreateFrameNode(
        TEST_HOST_TAG, hostNodeId, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(hostNode, nullptr);
    surfaceProxyNode->SetHostNode(hostNode);

    /**
     * @tc.steps: step2. call CreateSurfaceProxyNode
     */
    surfaceProxyNode->CreateSurfaceProxyNode();

    /**
     * @tc.steps: step3. verify the created proxy node exists and has correct properties
     * @tc.expected: surfaceProxyNode_ is not nullptr
     * @tc.expected: measure type is MATCH_PARENT
     * @tc.expected: hit test mode is HTMNONE
     */
    auto proxyNode = surfaceProxyNode->GetSurfaceProxyNode();
    ASSERT_NE(proxyNode, nullptr);
    EXPECT_EQ(proxyNode->GetTag(), V2::UI_EXTENSION_SURFACE_TAG);

    auto layoutProperty = proxyNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetMeasureType(), MeasureType::MATCH_PARENT);

    EXPECT_EQ(proxyNode->GetHitTestMode(), HitTestMode::HTMNONE);
}

/**
 * @tc.name: SurfaceProxyNodeTest005
 * @tc.desc: Test CreateSurfaceProxyNode without host set
 * @tc.type: FUNC
 */
HWTEST_F(SurfaceProxyNodeTestNg, SurfaceProxyNodeTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a SurfaceProxyNode without setting host
     */
    auto surfaceProxyNode = AceType::MakeRefPtr<SurfaceProxyNode>();
    ASSERT_NE(surfaceProxyNode, nullptr);

    /**
     * @tc.steps: step2. call CreateSurfaceProxyNode without host
     * @tc.expected: surfaceProxyNode_ remains nullptr
     */
    surfaceProxyNode->CreateSurfaceProxyNode();
    auto proxyNode = surfaceProxyNode->GetSurfaceProxyNode();
    EXPECT_EQ(proxyNode, nullptr);
}

/**
 * @tc.name: SurfaceProxyNodeTest006
 * @tc.desc: Test OnAddSurfaceNode virtual method (base implementation is a no-op)
 * @tc.type: FUNC
 */
HWTEST_F(SurfaceProxyNodeTestNg, SurfaceProxyNodeTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a SurfaceProxyNode and set host
     */
    auto surfaceProxyNode = AceType::MakeRefPtr<SurfaceProxyNode>();
    ASSERT_NE(surfaceProxyNode, nullptr);

    auto hostNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto hostNode = FrameNode::GetOrCreateFrameNode(
        TEST_HOST_TAG, hostNodeId, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(hostNode, nullptr);
    surfaceProxyNode->SetHostNode(hostNode);

    /**
     * @tc.steps: step2. call OnAddSurfaceNode, base implementation should not crash
     */
    surfaceProxyNode->OnAddSurfaceNode();
}

/**
 * @tc.name: SurfaceProxyNodeTest007
 * @tc.desc: Test SetHostNode updates the host weak pointer correctly
 * @tc.type: FUNC
 */
HWTEST_F(SurfaceProxyNodeTestNg, SurfaceProxyNodeTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a SurfaceProxyNode
     */
    auto surfaceProxyNode = AceType::MakeRefPtr<SurfaceProxyNode>();
    ASSERT_NE(surfaceProxyNode, nullptr);

    /**
     * @tc.steps: step2. verify host_ is initially null
     * @tc.expected: surfaceProxyNode_->host_ is expired (null)
     */
    EXPECT_TRUE(surfaceProxyNode->host_.Invalid());

    /**
     * @tc.steps: step3. set a valid host
     */
    auto hostNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto hostNode = FrameNode::GetOrCreateFrameNode(
        TEST_HOST_TAG, hostNodeId, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(hostNode, nullptr);
    surfaceProxyNode->SetHostNode(hostNode);

    /**
     * @tc.steps: step4. verify host_ is now valid (not expired)
     * @tc.expected: surfaceProxyNode_->host_ is not expired
     */
    EXPECT_FALSE(surfaceProxyNode->host_.Invalid());
    auto upgradedHost = surfaceProxyNode->host_.Upgrade();
    EXPECT_EQ(upgradedHost, hostNode);
}
} // namespace OHOS::Ace::NG
