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

#define private public
#define protected public
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/xcomponent/xcomponent_pattern.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_ext_surface_callback_client.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_accessibility_session_adapter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class XComponentTestSetRateRange : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

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
    auto pattern = XComponentPattern();
    pattern.nativeXComponentImpl_ = AceType::MakeRefPtr<NativeXComponentImpl>();
    EXPECT_NE(pattern.nativeXComponentImpl_, nullptr);
    pattern.nativeXcomponent_ = std::make_shared<OH_NativeXComponent>(AceType::RawPtr(pattern.nativeXComponentImpl_));

    EXPECT_NE(pattern.nativeXComponent_, nullptr);

    EXPECT_NE(pattern.displaySync_, nullptr);
    OH_NativeXComponent_ExpectedRateRange* rateRange =
        (OH_NativeXComponent_ExpectedRateRange*)malloc(sizeof(OH_NativeXComponent_ExpectedRateRange));
    rateRange->min = 10;
    rateRange->max = 60;
    rateRange->expected = 30;
    pattern.nativeXComponentImpl_->SetRateRange(rateRange);
    EXPECT_NE(pattern.nativeXComponentImpl_->GetRateRange(), nullptr);

#ifdef ENABLE_ROSEN_BACKEND
    FrameRateRange frameRateRange;
    frameRateRange.Set(rateRange->min, rateRange->max, rateRange->expected);
    pattern.lastFrameRateRange_.Set(rateRange->min, rateRange->max, rateRange->expected);
    EXPECT_FALSE(frameRateRange.preferred_ != pattern.lastFrameRateRange_.preferred_);
    pattern.HandleSetExpectedRateRangeEvent();
    EXPECT_FALSE(pattern.lastFrameRateRange_.IsZero());

    pattern.lastFrameRateRange_Reset();
    EXPECT_TRUE(pattern.lastFrameRateRange_.IsZero());
    EXPECT_TRUE(frameRateRange.preferred_ != pattern.lastFrameRateRange_.perferred_);
    pattern.HandleSetExpectedRateRangeEvent();
    EXPECT_FALSE(pattern.lastFrameRateRange_.IsZero());
#endif

    free(rateRange);
}
} // namespace OHOS::Ace::NG