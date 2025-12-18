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

#include "gmock/gmock.h"

#include "accessor_test_base.h"
#include "core/components_ng/pattern/canvas/canvas_paint_method.h"
#include "core/components_ng/pattern/canvas/canvas_pattern.h"
#include "core/interfaces/native/implementation/drawing_rendering_context_peer_impl.h"
#include "test/mock/core/pattern/mock_canvas_pattern.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
const auto DEFAULT_SETTING_UNITS = Converter::ArkValue<Opt_LengthMetricsUnit>(ARK_LENGTH_METRICS_UNIT_PX);
const double DEFAULT_VALUE = -1;
const double DEFAULT_DENSITY = 1.0;
const double DENSITY_1_25 = 1.25;
const double FLT_PRECISION = 0.001;

const std::vector<std::pair<double, double>> floatNumberTestPlan = {
    { 100, 100 },
    { 0, 0 },
    { -100, -100 },
    { 12.34, 12.34 },
    { -56.73, -56.73 },
};
const std::vector<std::tuple<std::string, Opt_LengthMetricsUnit, OHOS::Ace::CanvasUnit>> optCanvasUnitTestPlan = {
    { "default", Converter::ArkValue<Opt_LengthMetricsUnit>(CanvasUnit::DEFAULT), CanvasUnit::DEFAULT },
    { "px", Converter::ArkValue<Opt_LengthMetricsUnit>(CanvasUnit::PX), CanvasUnit::PX },
    { "invalid", Converter::ArkValue<Opt_LengthMetricsUnit>(static_cast<CanvasUnit>(-1)), CanvasUnit::DEFAULT },
    { "undefined", Converter::ArkValue<Opt_LengthMetricsUnit>(Ark_Empty()), CanvasUnit::DEFAULT },
};

class MockCanvasPattern : public CanvasPattern {
public:
    MockCanvasPattern() = default;
    ~MockCanvasPattern() override = default;
};

} // namespace

class DrawingRenderingContextAccessorTest
    : public AccessorTestCtorBase<GENERATED_ArkUIDrawingRenderingContextAccessor,
    &GENERATED_ArkUIAccessors::getDrawingRenderingContextAccessor, DrawingRenderingContextPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestCtorBase::SetUp();
        mockPattern_ = new MockCanvasPattern();
        mockPatternKeeper_ = AceType::Claim(mockPattern_);
        ASSERT_NE(mockPatternKeeper_, nullptr);
        auto peerImpl = reinterpret_cast<GeneratedModifier::DrawingRenderingContextPeerImpl*>(peer_);
        ASSERT_NE(peerImpl, nullptr);
        TestHolder::GetInstance()->SetUp();
        peerImpl->SetCanvasPattern(mockPatternKeeper_);
        ASSERT_NE(mockPattern_, nullptr);
    }

    void TearDown() override
    {
        AccessorTestCtorBase::TearDown();
        ChangeDensity(DEFAULT_DENSITY);
        mockPatternKeeper_ = nullptr;
        mockPattern_ = nullptr;
    }

    DrawingRenderingContextPeer* CreatePeerInstanceT(const Opt_LengthMetricsUnit* value)
    {
        return accessor_->construct(value);
    }

    void* CreatePeerInstance() override
    {
        return CreatePeerInstanceT(&DEFAULT_SETTING_UNITS);
    }

    void ChangeDensity(const double density)
    {
        auto pipelineContext =
            AceType::DynamicCast<NG::MockPipelineContext>(NG::MockPipelineContext::GetCurrentContext());
        pipelineContext->SetDensity(density);
        if (peer_) {
            auto peerImpl = reinterpret_cast<GeneratedModifier::DrawingRenderingContextPeerImpl*>(peer_);
            peerImpl->SetUnit(Ace::CanvasUnit::DEFAULT);
        }
    }

    MockCanvasPattern* mockPattern_ = nullptr;
    RefPtr<MockCanvasPattern> mockPatternKeeper_ = nullptr;
};

/**
 * @tc.name: ctorRenderingContextSettingsPeerTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DrawingRenderingContextAccessorTest, ctorTest, TestSize.Level1)
{
    for (const auto& [input, value, expected] : optCanvasUnitTestPlan) {
        auto peer = CreatePeerInstanceT(&value);
        auto result = reinterpret_cast<GeneratedModifier::DrawingRenderingContextPeerImpl*>(peer)->GetUnit();
        finalyzer_(peer);
        std::optional<CanvasUnit> units = Converter::OptConvert<Ace::CanvasUnit>(result);
        ASSERT_NE(units, std::nullopt);
        EXPECT_EQ(units.value(), expected) <<
            "Input value is: " << input << ", method: GetRepeat";
    }
    // nullptr
    auto peer = CreatePeerInstanceT(nullptr);
    auto result = reinterpret_cast<GeneratedModifier::DrawingRenderingContextPeerImpl*>(peer)->GetUnit();
    finalyzer_(peer);
    std::optional<CanvasUnit> units = Converter::OptConvert<Ace::CanvasUnit>(result);
    ASSERT_NE(units, std::nullopt);
    EXPECT_EQ(units.value(), Ace::CanvasUnit::DEFAULT) <<
        "Input value is: nullptr, method: GetRepeat";
}

/**
 * @tc.name: invalidateTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DrawingRenderingContextAccessorTest, DISABLED_invalidateTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->invalidate, nullptr);

    accessor_->invalidate(peer_);
    accessor_->invalidate(peer_);
    accessor_->invalidate(peer_);

    EXPECT_EQ(holder->counter, 3);

    holder->TearDown();
}
/**
 * @tc.name: getSizeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DrawingRenderingContextAccessorTest, DISABLED_getSizeTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();
    ASSERT_NE(accessor_->getSize, nullptr);
    auto peerImpl = reinterpret_cast<GeneratedModifier::DrawingRenderingContextPeerImpl*>(peer_);
    ASSERT_NE(peerImpl, nullptr);
    peerImpl->SetCanvasPattern(mockPatternKeeper_);
    for (const auto& [actualW, expectedW] : floatNumberTestPlan) {
        for (const auto& [actualH, expectedH] : floatNumberTestPlan) {
            holder->width = DEFAULT_VALUE;
            holder->height = DEFAULT_VALUE;
            ASSERT_NE(holder->rsCallback, nullptr);
            holder->rsCallback(nullptr, actualW, actualH);

            Ark_Size result = accessor_->getSize(peer_);

            auto width = Converter::Convert<float>(result.width);
            auto height = Converter::Convert<float>(result.height);
            EXPECT_NEAR(width, expectedW, FLT_PRECISION);
            EXPECT_NEAR(height, expectedH, FLT_PRECISION);
        }
    }
    // widh density
    ChangeDensity(DENSITY_1_25);
    for (const auto& [actualW, expectedW] : floatNumberTestPlan) {
        for (const auto& [actualH, expectedH] : floatNumberTestPlan) {
            holder->width = DEFAULT_VALUE;
            holder->height = DEFAULT_VALUE;
            ASSERT_NE(holder->rsCallback, nullptr);
            holder->rsCallback(nullptr, actualW, actualH);

            Ark_Size result = accessor_->getSize(peer_);

            auto width = Converter::Convert<float>(result.width);
            auto height = Converter::Convert<float>(result.height);
            EXPECT_NEAR(width, expectedW / DENSITY_1_25, FLT_PRECISION);
            EXPECT_NEAR(height, expectedH / DENSITY_1_25, FLT_PRECISION);
        }
    }
    holder->TearDown();
}
/**
 * @tc.name: getCanvasTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DrawingRenderingContextAccessorTest, DISABLED_getCanvasTest, TestSize.Level1)
{
#ifdef WRONG_SDK
    auto holder = TestHolder::GetInstance();
    holder->SetUp();
    ASSERT_NE(accessor_->getCanvas, nullptr);
    auto peerImpl = reinterpret_cast<GeneratedModifier::DrawingRenderingContextPeerImpl*>(peer_);
    ASSERT_NE(peerImpl, nullptr);
    peerImpl->SetCanvasPattern(mockPatternKeeper_);
    ASSERT_NE(holder->rsCallback, nullptr);
    std::shared_ptr<RSCanvas> rsCanvas = std::make_shared<RSCanvas>();
    holder->rsCallback(rsCanvas, DEFAULT_VALUE, DEFAULT_VALUE);

    Ark_drawing_Canvas result = accessor_->getCanvas(peer_);

    ASSERT_NE(result, nullptr);
    auto canvas = result->GetCanvas();
    EXPECT_EQ(canvas, rsCanvas);
#endif
}
} // namespace OHOS::Ace::NG
