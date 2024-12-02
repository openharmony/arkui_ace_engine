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

#include "test/mock/core/pattern/mock_canvas_pattern.h"
#include "accessor_test_base.h"
#include "node_api.h"
#include "canvas_rendering_context2d_accessor_test.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "gmock/gmock.h"

#include "core/components_ng/pattern/canvas/canvas_paint_method.h"
#include "core/interfaces/native/implementation/canvas_rendering_context2d_peer_impl.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
const Opt_RenderingContextSettings DEFAULT_SETTINGS =
    Converter::ArkValue<Opt_RenderingContextSettings>(Converter::ArkValue<Opt_Boolean>(false));

class MockCanvasPattern : public CanvasPattern {
public:
    MockCanvasPattern() = default;
    ~MockCanvasPattern() override = default;
};

// test plans
typedef std::pair<double, Ark_Int32> DoubleValueTestStep;
const std::vector<DoubleValueTestStep> DOUBLE_VALUE_TEST_PLAN = {
    { 0, Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(0)) },
    { 1.25, Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(1.25)) },
    { 100.15, Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(100.15)) },
    { -2.35, Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(-2.35)) },
};

const std::vector<ImageAnalyzerType> IMAGE_TYPE_TEST_PLAN {
    ImageAnalyzerType::TEXT,
    ImageAnalyzerType::SUBJECT,
};

const std::vector<Ark_ImageAnalyzerType> ARK_IMAGE_TYPE_TEST_PLAN {
    Ark_ImageAnalyzerType::ARK_IMAGE_ANALYZER_TYPE_TEXT,
    Ark_ImageAnalyzerType::ARK_IMAGE_ANALYZER_TYPE_SUBJECT,
    static_cast<Ark_ImageAnalyzerType>(100),
    static_cast<Ark_ImageAnalyzerType>(-100)
};

} // namespace

class CanvasRenderingContext2DAccessorTest
    : public AccessorTestBaseParent<GENERATED_ArkUICanvasRenderingContext2DAccessor,
    &GENERATED_ArkUIAccessors::getCanvasRenderingContext2DAccessor, CanvasRenderingContext2DPeer> {
public:
    void SetUp(void) override
    {
        ASSERT_NE(accessor_->ctor, nullptr);
        peer_ = reinterpret_cast<CanvasRenderingContext2DPeer*>(accessor_->ctor(&DEFAULT_SETTINGS));
        ASSERT_NE(peer_, nullptr);

        AccessorTestBaseParent::SetUp();
        mockPattern_ = new MockCanvasPattern();
        mockPatternKeeper_ = AceType::Claim(mockPattern_);
        ASSERT_NE(mockPatternKeeper_, nullptr);
        auto peerImpl = reinterpret_cast<GeneratedModifier::CanvasRenderingContext2DPeerImpl*>(peer_);
        ASSERT_NE(peerImpl, nullptr);
        peerImpl->SetCanvasPattern(mockPatternKeeper_);
        ASSERT_NE(mockPattern_, nullptr);
    }

    void TearDown() override
    {
        AccessorTestBaseParent::TearDown();
        mockPatternKeeper_ = nullptr;
        mockPattern_ = nullptr;
    }

    MockCanvasPattern* mockPattern_ = nullptr;
    RefPtr<MockCanvasPattern> mockPatternKeeper_ = nullptr;
};

/**
 * @tc.name: startImageAnalyzerTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderingContext2DAccessorTest, startImageAnalyzerTest, TestSize.Level1)
{
    // check config
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    std::vector<Ark_ImageAnalyzerType> src = ARK_IMAGE_TYPE_TEST_PLAN;
    Ark_ImageAnalyzerConfig arkConfig = {
        .types.array = reinterpret_cast<Ark_ImageAnalyzerType*>(src.data()),
        .types.length = Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(src.size())),
    };

    ASSERT_NE(accessor_->startImageAnalyzer, nullptr);
    Callback_Opt_Array_String_Void cont{};
    accessor_->startImageAnalyzer(peer_, &arkConfig, &cont);

    std::vector<ImageAnalyzerType>* config = reinterpret_cast<std::vector<ImageAnalyzerType>*>(holder->config);
    std::vector<ImageAnalyzerType> vector = *config;
    auto length = IMAGE_TYPE_TEST_PLAN.size();
    for (int i = 0; i < length; i++) {
        ImageAnalyzerType actual = vector[i]; //*(config + i);
        ImageAnalyzerType expected = IMAGE_TYPE_TEST_PLAN[i];
        EXPECT_EQ(actual, expected);
    }
    OnAnalyzedCallback onAnalyzed = holder->onAnalyzed;

    // check callback
    holder->SetUp();
    accessor_->startImageAnalyzer(peer_, &arkConfig, &cont);
    EXPECT_FALSE(holder->isCalled);

    EXPECT_EQ(holder->config, nullptr);
    EXPECT_EQ(holder->onAnalyzed, nullptr);
    EXPECT_NE(onAnalyzed, nullptr);

    holder->SetUp();
    (onAnalyzed.value())(ImageAnalyzerState::FINISHED);
    accessor_->startImageAnalyzer(peer_, &arkConfig, &cont);
    EXPECT_TRUE(holder->isCalled);
    EXPECT_NE(holder->config, nullptr);
    EXPECT_NE(holder->onAnalyzed, nullptr);

    holder->TearDown();
}

/**
 * @tc.name: stopImageAnalyzerTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderingContext2DAccessorTest, stopImageAnalyzerTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->stopImageAnalyzer, nullptr);

    accessor_->stopImageAnalyzer(peer_);
    accessor_->stopImageAnalyzer(peer_);
    accessor_->stopImageAnalyzer(peer_);

    EXPECT_EQ(holder->counter, 3);
    holder->TearDown();
}

/**
 * @tc.name: getHeightTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderingContext2DAccessorTest, getHeightTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->getHeight, nullptr);

    for (auto& [actual, expected] : DOUBLE_VALUE_TEST_PLAN) {
        holder->height = actual;
        auto result = accessor_->getHeight(peer_);
        EXPECT_DOUBLE_EQ(result, expected);
    }
    EXPECT_EQ(holder->counter, DOUBLE_VALUE_TEST_PLAN.size());
    holder->TearDown();
}

/**
 * @tc.name: getWidthTest
    * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderingContext2DAccessorTest, getWidthTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->getWidth, nullptr);

    for (auto& [actual, expected] : DOUBLE_VALUE_TEST_PLAN) {
        holder->width = actual;
        auto result = accessor_->getWidth(peer_);
        EXPECT_DOUBLE_EQ(result, expected);
    }
    EXPECT_EQ(holder->counter, DOUBLE_VALUE_TEST_PLAN.size());
    holder->TearDown();
}

} // namespace OHOS::Ace::NG
