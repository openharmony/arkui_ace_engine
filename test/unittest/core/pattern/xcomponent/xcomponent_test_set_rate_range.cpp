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
#include "core/components_ng/pattern/xcomponent/xcomponent_accessibility_session_adapter.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_controller_ng.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_ext_surface_callback_client.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_model_ng.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern_v2.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
struct TestProperty {
    std::optional<std::string> xcId = std::nullopt;
    std::optional<XComponentType> xcType = std::nullopt;
    std::optional<std::string> libraryName = std::nullopt;
    std::optional<std::string> soPath = std::nullopt;
};

namespace {
const std::string XCOMPONENT_ID = "xcomponent";
const std::string XCOMPONENT_LIBRARY_NAME = "native_render";
const std::string XCOMPONENT_SO_PATH = "com.example.xcomponentmultihap/entry";
constexpr XComponentType XCOMPONENT_SURFACE_TYPE_VALUE = XComponentType::SURFACE;
ArkUI_XComponent_Params params;
const int32_t MIN_RATE = 30;
const int32_t MAX_RATE = 120;
const int32_t EXPECTED_RATE = 120;
const int32_t CODE_NO_ERROR = 0;
} // namespace

class XComponentTestSetRateRange : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void TearDown() override {}
protected:
    static RefPtr<FrameNode> CreateXComponentNode();
};

RefPtr<FrameNode> XComponentTestSetRateRange::CreateXComponentNode()
{
    params.type = XCOMPONENT_SURFACE_TYPE_VALUE;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = AceType::DynamicCast<FrameNode>(XComponentModelNG().CreateTypeNode(nodeId, &params));
    return frameNode;
}

void XComponentTestSetRateRange::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void XComponentTestSetRateRange::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: HandleSetExpectedRateRangeEventTest
 * @tc.desc: Test HandleSetExpectedRateRangeEvent successfully
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestSetRateRange, HandleSetExpectedRateRangeEventTest, TestSize.Level0)
{
#ifdef ENABLE_ROSEN_BACKEND
    auto frameNode = CreateXComponentNode();
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetTag(), V2::XCOMPONENT_ETS_TAG);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->nativeXComponentImpl_ = AceType::MakeRefPtr<NativeXComponentImpl>();
    EXPECT_NE(pattern->nativeXComponentImpl_, nullptr);
    pattern->nativeXComponent_ = std::make_shared<OH_NativeXComponent>(AceType::RawPtr(pattern->nativeXComponentImpl_));
    EXPECT_NE(pattern->nativeXComponent_, nullptr);
    EXPECT_NE(pattern->displaySync_, nullptr);
    OH_NativeXComponent_ExpectedRateRange* rateRange = new OH_NativeXComponent_ExpectedRateRange();
    rateRange->min = 10;
    rateRange->max = 60;
    rateRange->expected = 30;
    pattern->nativeXComponentImpl_->SetRateRange(rateRange);
    EXPECT_NE(pattern->nativeXComponentImpl_->GetRateRange(), nullptr);
    FrameRateRange frameRateRange;
    frameRateRange.Set(rateRange->min, rateRange->max, rateRange->expected);
    EXPECT_FALSE(pattern->displaySync_->lastFrameRateRange_.has_value());
    pattern->displaySync_->lastFrameRateRange_.emplace(rateRange->min, rateRange->max, rateRange->expected);
    pattern->OnDetachFromMainTree();
    EXPECT_FALSE(frameRateRange.preferred_ != pattern->displaySync_->lastFrameRateRange_->preferred_);
    pattern->HandleSetExpectedRateRangeEvent();
    EXPECT_TRUE(pattern->displaySync_->lastFrameRateRange_.has_value());
    pattern->displaySync_->lastFrameRateRange_.reset();
    pattern->OnAttachToMainTree();
    EXPECT_FALSE(pattern->displaySync_->lastFrameRateRange_.has_value());
    EXPECT_TRUE(pattern->isOnTree_);
    pattern->HandleSetExpectedRateRangeEvent();
    EXPECT_TRUE(pattern->displaySync_->lastFrameRateRange_.has_value());
    pattern->OnAttachToMainTree();

    auto extFrameNode = CreateXComponentNode();
    ASSERT_NE(extFrameNode, nullptr);
    auto extPattern = extFrameNode->GetPattern<XComponentPattern>();
    ASSERT_NE(extPattern, nullptr);
    extPattern->displaySync_->lastFrameRateRange_.reset();
    extPattern->OnDetachFromMainTree();
    delete rateRange;
#endif
}

/**
 * @tc.name: SetExpectedRateRangeTest
 * @tc.desc: Test SetExpectedRateRangeTest successfully
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestSetRateRange, SetExpectedRateRangeTest, TestSize.Level1)
{
#ifdef ENABLE_ROSEN_BACKEND
    int32_t invalidRate = -1;
    auto frameNode = CreateXComponentNode();
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetTag(), V2::XCOMPONENT_ETS_TAG);
    auto pattern = frameNode->GetPattern<XComponentPatternV2>();
    ASSERT_NE(pattern, nullptr);
    auto code = XComponentModelNG::SetExpectedRateRange(AceType::RawPtr(frameNode), MIN_RATE, MAX_RATE, EXPECTED_RATE);
    ASSERT_EQ(code, CODE_NO_ERROR);

    OH_NativeXComponent_ExpectedRateRange* rateRange = new OH_NativeXComponent_ExpectedRateRange();
    rateRange->min = 10;
    rateRange->max = 60;
    rateRange->expected = 30;
    FrameRateRange frameRateRange;
    frameRateRange.Set(rateRange->min, rateRange->max, rateRange->expected);
    EXPECT_TRUE(pattern->displaySync_->lastFrameRateRange_.has_value());
    pattern->displaySync_->lastFrameRateRange_.emplace(rateRange->min, rateRange->max, rateRange->expected);
    pattern->usesSuperMethod_ = true;
    pattern->OnDetachFromMainTree();
    EXPECT_FALSE(frameRateRange.preferred_ != pattern->displaySync_->lastFrameRateRange_->preferred_);
    code = XComponentModelNG::SetExpectedRateRange(AceType::RawPtr(frameNode), MIN_RATE, MAX_RATE, EXPECTED_RATE);
    ASSERT_EQ(code, CODE_NO_ERROR);
    EXPECT_FALSE(pattern->displaySync_->lastFrameRateRange_->IsZero());

    pattern->displaySync_->lastFrameRateRange_->Reset();
    pattern->OnAttachToMainTree();
    EXPECT_TRUE(pattern->displaySync_->lastFrameRateRange_->IsZero());
    code = XComponentModelNG::SetExpectedRateRange(AceType::RawPtr(frameNode), MIN_RATE, MAX_RATE, EXPECTED_RATE);
    ASSERT_EQ(code, CODE_NO_ERROR);
    EXPECT_FALSE(pattern->displaySync_->lastFrameRateRange_->IsZero());
    pattern->OnAttachToMainTree();
    code = XComponentModelNG::SetExpectedRateRange(AceType::RawPtr(frameNode), MIN_RATE, MAX_RATE, invalidRate);
    delete rateRange;
#endif
}

/**
 * @tc.name: HandleOnFrameEventTest
 * @tc.desc: Test HandleOnFrameEvent successfully
 * @tc.type: FUNC
 */
HWTEST_F(XComponentTestSetRateRange, HandleOnFrameEventTest, TestSize.Level0)
{
    auto frameNode = CreateXComponentNode();
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetTag(), V2::XCOMPONENT_ETS_TAG);
    auto pattern = frameNode->GetPattern<XComponentPatternV2>();
    ASSERT_NE(pattern, nullptr);
    auto code = XComponentModelNG::SetExpectedRateRange(AceType::RawPtr(frameNode), MIN_RATE, MAX_RATE, EXPECTED_RATE);
    ASSERT_EQ(code, CODE_NO_ERROR);

    pattern->nativeXComponentImpl_ = AceType::MakeRefPtr<NativeXComponentImpl>();
    EXPECT_NE(pattern->nativeXComponentImpl_, nullptr);
    pattern->nativeXComponent_ = std::make_shared<OH_NativeXComponent>(AceType::RawPtr(pattern->nativeXComponentImpl_));
    EXPECT_NE(pattern->nativeXComponent_, nullptr);
    EXPECT_NE(pattern->displaySync_, nullptr);
    OH_NativeXComponent_ExpectedRateRange* rateRange = new OH_NativeXComponent_ExpectedRateRange();
    rateRange->min = 10;
    rateRange->max = 60;
    rateRange->expected = 30;
    pattern->nativeXComponentImpl_->SetRateRange(rateRange);
    EXPECT_NE(pattern->nativeXComponentImpl_->GetRateRange(), nullptr);
    pattern->HandleOnFrameEvent();
    EXPECT_NE(pattern->GetHost(), nullptr);
    pattern->frameNode_.Reset();
    pattern->HandleOnFrameEvent();
    EXPECT_EQ(pattern->GetHost(), nullptr);
    delete rateRange;
}
} // namespace OHOS::Ace::NG
