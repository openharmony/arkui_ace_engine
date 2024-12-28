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
#include "gmock/gmock.h"

#include "core/components_ng/pattern/canvas/canvas_paint_method.h"
#include "core/interfaces/native/implementation/canvas_renderer_peer_impl.h"
#include "core/interfaces/native/implementation/canvas_path_accessor_peer_impl.h"
#include "core/interfaces/native/implementation/canvas_pattern_peer.h"
#include "core/interfaces/native/implementation/canvas_gradient_peer.h"
#include "core/interfaces/native/implementation/matrix2d_peer.h"
#include "core/interfaces/native/implementation/image_bitmap_peer_impl.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
const auto EXPECTED_NUMBER_OF_CALLS = 3;
const auto ALPHA_LIMIT_MIN = 0.0;
const auto ALPHA_LIMIT_MAX = 1.0;
const auto SIZE_LIMIT_MIN = 0.0;
const auto SEGMENT_LIMIT_MIN = 0.0;
const auto SCALE_LIMIT_MIN = 0.0;
const auto EXPECTED_TRUE = true;
const auto EXPECTED_FALSE = false;

const double DEFAULT_DOUBLE_VALUE = 10.0;
const double DEFAULT_SCALE_VALUE = 1.0;
const std::string DEFAULT_STRING_VALUE = "text";
const std::string INVALID_STRING_VALUE = "";
const auto INVALID_COMPOSITE_VALUE = static_cast<CompositeOperation>(-1);
constexpr double MATH_2_PI = 2 * M_PI;
constexpr double DIFF = 1e-10;
const int32_t DEFAULT_ZERO_VALUE = 0;

// test plan
std::vector<std::tuple<Ark_Number, double>> ARK_NUMBER_TEST_PLAN = {
    { Converter::ArkValue<Ark_Number>(100), 100 },
    { Converter::ArkValue<Ark_Number>(0), 0 },
    { Converter::ArkValue<Ark_Number>(-100), -100 },
    { Converter::ArkValue<Ark_Number>(12.34), 12.34 },
    { Converter::ArkValue<Ark_Number>(-56.73), -56.73 },
};

std::vector<std::tuple<Ark_Number, double>> ARK_NUMBER_ALPHA_TEST_PLAN = {
    { Converter::ArkValue<Ark_Number>(100), 100 },
    { Converter::ArkValue<Ark_Number>(0), 0 },
    { Converter::ArkValue<Ark_Number>(-0.54), -0.54 },
    { Converter::ArkValue<Ark_Number>(0.98), 0.98 },
    { Converter::ArkValue<Ark_Number>(1.00), 1.00 },
    { Converter::ArkValue<Ark_Number>(1.01), 1.01 },
    { Converter::ArkValue<Ark_Number>(-100), -100 },
};

std::vector<std::vector<double>> ARRAY_NUMBER_TEST_PLAN = {
    { 100, 10.25, 2.35, 5.42, 12.34 },
    { 100, 10.25, 0, 5.42, 12.34 },
    { 100, -10.25, 0, -5.42, 12.34 },
    { 0, 0, 0, 0, 0 },
    { -100, -10.25, -2.35, -5.42, -12.34 },
    {},
};

std::vector<std::tuple<Ark_String, std::string>> ARK_STRING_TEST_PLAN = {
    { Converter::ArkValue<Ark_String>("string text"), "string text" },
    { Converter::ArkValue<Ark_String>(""), "" },
    { Converter::ArkValue<Ark_String>("123"), "123" },
    { Converter::ArkValue<Ark_String>("value %2"), "value %2" },
    { Converter::ArkValue<Ark_String>("echo(%10)"), "echo(%10)" }
};

std::vector<std::tuple<Opt_Number, std::optional<double>>> OPT_NUMBER_TEST_PLAN = {
    { Converter::ArkValue<Opt_Number>(100), 100 },
    { Converter::ArkValue<Opt_Number>(0), 0 },
    { Converter::ArkValue<Opt_Number>(-100), -100 },
    { Converter::ArkValue<Opt_Number>(12.34), 12.34 },
    { Converter::ArkValue<Opt_Number>(-56.73), -56.73 },
    { Converter::ArkValue<Opt_Number>(Ark_Empty()), std::make_optional<double>() },
};

std::vector<std::tuple<Ark_String, CompositeOperation>> ARK_COMPOSITE_TEST_PLAN = {
    { Converter::ArkValue<Ark_String>("source_OVER"), CompositeOperation::SOURCE_OVER },
    { Converter::ArkValue<Ark_String>("  source_ATOP"), CompositeOperation::SOURCE_ATOP },
    { Converter::ArkValue<Ark_String>("source_IN  "), CompositeOperation::SOURCE_IN },
    { Converter::ArkValue<Ark_String>("  source_OUT  "), CompositeOperation::SOURCE_OUT },
    { Converter::ArkValue<Ark_String>("DESTINATION_over"), CompositeOperation::DESTINATION_OVER },
    { Converter::ArkValue<Ark_String>("  DESTINATION_atop"), CompositeOperation::DESTINATION_ATOP },
    { Converter::ArkValue<Ark_String>("DESTINATION_in  "), CompositeOperation::DESTINATION_IN },
    { Converter::ArkValue<Ark_String>("  DESTINATION_out "), CompositeOperation::DESTINATION_OUT },
    { Converter::ArkValue<Ark_String>("LIGHTER  "), CompositeOperation::LIGHTER },
    { Converter::ArkValue<Ark_String>(" copy"), CompositeOperation::COPY },
    { Converter::ArkValue<Ark_String>("XOR"), CompositeOperation::XOR },
    { Converter::ArkValue<Ark_String>(""), static_cast<CompositeOperation>(-1) },
    { Converter::ArkValue<Ark_String>("unknown value"), static_cast<CompositeOperation>(-1) },
};

std::vector<std::tuple<Ark_String, Color>> ARK_STRING_COLOR_TEST_PLAN = {
    { Converter::ArkValue<Ark_String>("#ff0000ff"), Color(0xff0000ff) },
    { Converter::ArkValue<Ark_String>("#00000000"), Color(0x00000000) },
    { Converter::ArkValue<Ark_String>("#80ffffff"), Color(0x80ffffff) },
    { Converter::ArkValue<Ark_String>(""), Color::BLACK },
    { Converter::ArkValue<Ark_String>("invalid color"), Color::BLACK },
};

std::vector<std::tuple<Ark_Boolean, bool>> ARK_BOOL_TEST_PLAN = {
    { Converter::ArkValue<Ark_Boolean>(EXPECTED_FALSE), EXPECTED_FALSE },
    { Converter::ArkValue<Ark_Boolean>(EXPECTED_TRUE), EXPECTED_TRUE },
};

std::vector<double> NUMBER_ALPHA_TEST_PLAN = {
    100, 0, -0.54, 0.98, 1.00, 1.01, -100,
};

std::vector<double> NUMBER_TEST_PLAN = {
    100, 0, -100, 12.34, -56.73,
};

std::vector<int32_t> INT32_TEST_PLAN = {
    100, 0, -100, 12, -56,
};

std::vector<int32_t> SIZE_TEST_PLAN = {
    -100, -10, 0, 10, 12, 56, 100
};

typedef std::tuple<PathCmd, double, double> Path2DTestStep;
static const std::vector<Path2DTestStep> PATH2D_TEST_PLAN = {
    { PathCmd::MOVE_TO, 0, 0 },
    { PathCmd::MOVE_TO, -100, -100 },
    { PathCmd::MOVE_TO, 100, 100 },
    { PathCmd::MOVE_TO, 12.34, 53.76 },
    { PathCmd::MOVE_TO, -12.34, 53.76 },
    { PathCmd::LINE_TO, 0, 0 },
    { PathCmd::LINE_TO, -100, -100 },
    { PathCmd::LINE_TO, 100, 100 },
    { PathCmd::LINE_TO, 12.34, 53.76 },
    { PathCmd::LINE_TO, -12.34, 53.76 },
};

std::vector<std::pair<std::string, Ace::FontStyle>> FONT_STYLE_TEST_PLAN = {
    { "normal", Ace::FontStyle::NORMAL },
    { "none", Ace::FontStyle::NORMAL },
    { "italic", Ace::FontStyle::ITALIC },
    { "", Ace::FontStyle::NORMAL },
    { "invalid", Ace::FontStyle::NORMAL },
};

std::vector<std::pair<std::string, Ace::FontWeight>> FONT_WEIGHT_TEST_PLAN = {
    { "100", FontWeight::W100 },
    { "200", FontWeight::W200 },
    { "300", FontWeight::W300 },
    { "400", FontWeight::W400 },
    { "500", FontWeight::W500 },
    { "600", FontWeight::W600 },
    { "700", FontWeight::W700 },
    { "800", FontWeight::W800 },
    { "900", FontWeight::W900 },
    { "bold", FontWeight::BOLD },
    { "bolder", FontWeight::BOLDER },
    { "lighter", FontWeight::LIGHTER },
    { "medium", FontWeight::MEDIUM },
    { "normal", FontWeight::NORMAL },
    { "regular", FontWeight::REGULAR },
    { "", Ace::FontWeight::NORMAL },
    { "invalid", Ace::FontWeight::NORMAL },
};

std::vector<std::pair<std::string, Dimension>> FONT_SIZE_PX_TEST_PLAN = {
    { "0px", Dimension(0, OHOS::Ace::DimensionUnit::PX) },
    { "14px", Dimension(14, OHOS::Ace::DimensionUnit::PX) },
    { "-56px", Dimension(-100) },
    { "abcpx", Dimension(0, OHOS::Ace::DimensionUnit::PX) },
    { "px200", Dimension(0, OHOS::Ace::DimensionUnit::PX) },
    { "", Dimension(-100) },
    { "invalid", Dimension(-100) },
};

std::vector<std::pair<std::string, Dimension>> FONT_SIZE_VP_TEST_PLAN = {
    { "10vp", Dimension(10, DimensionUnit::PX) },
    { "0vp", Dimension(0, DimensionUnit::PX) },
    { "-10vp", Dimension(-100) },
    { "", Dimension(-100) },
    { "invalid", Dimension(-100) },
};

std::vector<std::pair<std::string, std::vector<std::string>>>  FONT_FAMILIES_TEST_PLAN = {
    { "sans-serif", { "sans-serif" } },
    { "monospace", { "monospace" } },
    { "serif", { "serif" } },
    { "", {} },
    { "invalid", {} },
};

std::vector<std::tuple<Ark_String, std::string>> IMAGE_SMOOTHING_TEST_PLAN = {
    { Converter::ArkValue<Ark_String>("low"), "low" },
    { Converter::ArkValue<Ark_String>("medium"), "medium" },
    { Converter::ArkValue<Ark_String>("high"), "high" },
    { Converter::ArkValue<Ark_String>(""), INVALID_STRING_VALUE },
    { Converter::ArkValue<Ark_String>("invalid"), INVALID_STRING_VALUE }
};
std::vector<std::tuple<Ark_String, LineCapStyle>> LINE_CAP_TEST_PLAN = {
    { Converter::ArkValue<Ark_String>("butt"), LineCapStyle::BUTT },
    { Converter::ArkValue<Ark_String>("round"), LineCapStyle::ROUND },
    { Converter::ArkValue<Ark_String>("square"), LineCapStyle::SQUARE },
    { Converter::ArkValue<Ark_String>(""), LineCapStyle::BUTT },
    { Converter::ArkValue<Ark_String>("invalid"), LineCapStyle::BUTT }
};
std::vector<std::tuple<Ark_String, LineJoinStyle>> LINE_JOIN_TEST_PLAN = {
    { Converter::ArkValue<Ark_String>("bevel"), LineJoinStyle::BEVEL },
    { Converter::ArkValue<Ark_String>("miter"), LineJoinStyle::MITER },
    { Converter::ArkValue<Ark_String>("round"), LineJoinStyle::ROUND },
    { Converter::ArkValue<Ark_String>(""), LineJoinStyle::MITER },
    { Converter::ArkValue<Ark_String>("invalid"), LineJoinStyle::MITER }
};

class MockCanvasPattern : public CanvasPattern {
public:
    MockCanvasPattern() = default;
    ~MockCanvasPattern() override = default;
};
struct MockImageBitmapPeer : public ImageBitmapPeer {
public:
    MockImageBitmapPeer() = default;
    ~MockImageBitmapPeer() override = default;
    using ImageBitmapPeer::SetHeight;
    using ImageBitmapPeer::SetWidth;
};
} // namespace

class CanvasRendererAccessorTest
    : public AccessorTestBase<GENERATED_ArkUICanvasRendererAccessor,
    &GENERATED_ArkUIAccessors::getCanvasRendererAccessor, CanvasRendererPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        mockPattern_ = new MockCanvasPattern();
        mockPatternKeeper_ = AceType::Claim(mockPattern_);
        ASSERT_NE(mockPatternKeeper_, nullptr);
        auto peerImpl = reinterpret_cast<GeneratedModifier::CanvasRendererPeerImpl*>(peer_);
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
 * @tc.name: beginPathTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, beginPathTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->beginPath, nullptr);

    accessor_->beginPath(peer_);
    accessor_->beginPath(peer_);
    accessor_->beginPath(peer_);

    EXPECT_EQ(holder->counter, EXPECTED_NUMBER_OF_CALLS);
    holder->TearDown();
}

/**
 * @tc.name: stroke0Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, stroke0Test, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->stroke0, nullptr);

    accessor_->stroke0(peer_);
    accessor_->stroke0(peer_);
    accessor_->stroke0(peer_);

    EXPECT_EQ(holder->counter, EXPECTED_NUMBER_OF_CALLS);

    holder->TearDown();
}

/**
 * @tc.name: setLineDashTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setLineDashTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    ASSERT_NE(accessor_->setLineDash, nullptr);

    for (const auto& expected : ARRAY_NUMBER_TEST_PLAN) {
        holder->SetUp();

        Converter::ArkArrayHolder<Array_Number> arrayHolder(expected);
        const auto segments = arrayHolder.ArkValue();

        accessor_->setLineDash(peer_, &segments);
        bool isNegative = false;
        if (expected.size() == SIZE_LIMIT_MIN) {
            EXPECT_FALSE(holder->isCalled);
            continue;
        }
        for (const auto& value : expected) {
            if (value < SEGMENT_LIMIT_MIN) {
                isNegative = true;
                break;
            }
        }
        if (isNegative) {
            EXPECT_FALSE(holder->isCalled);
            continue;
        }
        EXPECT_TRUE(holder->isCalled);
        EXPECT_EQ(expected.size(), holder->segments.size());
        for (size_t i = 0; i < expected.size(); i++) {
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->segments[i], expected[i]));
        }
    }
    holder->TearDown();
}

/**
 * @tc.name: clearRectTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, clearRectTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    ASSERT_NE(accessor_->clearRect, nullptr);

    auto arkD = Converter::ArkValue<Ark_Number>(static_cast<float>(DEFAULT_DOUBLE_VALUE));

    for (const auto& [x, expectedX] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_TEST_PLAN) {
            holder->SetUp();
            accessor_->clearRect(peer_, &x, &y, &arkD, &arkD);
            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->rect.GetOffset().GetX(), expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->rect.GetOffset().GetY(), expectedY));
        }
    }
    for (const auto& [w, expectedW] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [h, expectedH] : ARK_NUMBER_TEST_PLAN) {
            holder->SetUp();
            accessor_->clearRect(peer_, &arkD, &arkD, &w, &h);
            if (!(expectedW > SIZE_LIMIT_MIN && expectedH > SIZE_LIMIT_MIN)) {
                EXPECT_FALSE(holder->isCalled);
                continue;
            }
            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->rect.GetSize().Width(), expectedW));
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->rect.GetSize().Height(), expectedH));
        }
    }
    holder->TearDown();
}

/**
 * @tc.name: fillRectTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, fillRectTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    ASSERT_NE(accessor_->fillRect, nullptr);

    auto arkD = Converter::ArkValue<Ark_Number>(static_cast<float>(DEFAULT_DOUBLE_VALUE));

    for (const auto& [x, expectedX] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_TEST_PLAN) {
            holder->SetUp();
            accessor_->fillRect(peer_, &x, &y, &arkD, &arkD);
            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->rect.GetOffset().GetX(), expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->rect.GetOffset().GetY(), expectedY));
        }
    }
    for (const auto& [w, expectedW] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [h, expectedH] : ARK_NUMBER_TEST_PLAN) {
            holder->SetUp();
            accessor_->fillRect(peer_, &arkD, &arkD, &w, &h);
            if (!(expectedW > SIZE_LIMIT_MIN && expectedH > SIZE_LIMIT_MIN)) {
                EXPECT_FALSE(holder->isCalled);
                continue;
            }
            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->rect.GetSize().Width(), expectedW));
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->rect.GetSize().Height(), expectedH));
        }
    }
    holder->TearDown();
}

/**
 * @tc.name: strokeRectTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, strokeRectTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    ASSERT_NE(accessor_->strokeRect, nullptr);

    auto arkD = Converter::ArkValue<Ark_Number>(static_cast<float>(DEFAULT_DOUBLE_VALUE));

    for (const auto& [x, expectedX] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_TEST_PLAN) {
            holder->SetUp();
            accessor_->strokeRect(peer_, &x, &y, &arkD, &arkD);
            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->rect.GetOffset().GetX(), expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->rect.GetOffset().GetY(), expectedY));
        }
    }
    for (const auto& [w, expectedW] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [h, expectedH] : ARK_NUMBER_TEST_PLAN) {
            holder->SetUp();
            accessor_->strokeRect(peer_, &arkD, &arkD, &w, &h);
            if (!(expectedW > SIZE_LIMIT_MIN && expectedH > SIZE_LIMIT_MIN)) {
                EXPECT_FALSE(holder->isCalled);
                continue;
            }
            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->rect.GetSize().Width(), expectedW));
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->rect.GetSize().Height(), expectedH));
        }
    }
    holder->TearDown();
}

/**
 * @tc.name: restoreTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, restoreTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->restore, nullptr);

    accessor_->restore(peer_);
    accessor_->restore(peer_);
    accessor_->restore(peer_);

    EXPECT_EQ(holder->counter, EXPECTED_NUMBER_OF_CALLS);
    holder->TearDown();
}

/**
 * @tc.name: saveTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, saveTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->save, nullptr);

    accessor_->save(peer_);
    accessor_->save(peer_);
    accessor_->save(peer_);

    EXPECT_EQ(holder->counter, EXPECTED_NUMBER_OF_CALLS);
    holder->TearDown();
}

/**
 * @tc.name: resetTransformTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, resetTransformTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->resetTransform, nullptr);

    accessor_->resetTransform(peer_);
    accessor_->resetTransform(peer_);
    accessor_->resetTransform(peer_);

    EXPECT_EQ(holder->counter, EXPECTED_NUMBER_OF_CALLS);
    holder->TearDown();
}

/**
 * @tc.name: rotateTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, rotateTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->rotate, nullptr);

    for (const auto& [actual, expected] : ARK_NUMBER_TEST_PLAN) {
        holder->SetUp();

        accessor_->rotate(peer_, &actual);
        EXPECT_TRUE(holder->isCalled);
        EXPECT_TRUE(LessOrEqualCustomPrecision(holder->value, expected));
    }
    holder->TearDown();
}

/**
 * @tc.name: scaleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, scaleTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->scale, nullptr);

    for (const auto& [x, expectedX] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_TEST_PLAN) {
            holder->SetUp();
            accessor_->scale(peer_, &x, &y);

            if (expectedX < SCALE_LIMIT_MIN || expectedY < SCALE_LIMIT_MIN) {
                EXPECT_FALSE(holder->isCalled);
                continue;
            }
            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->x, expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->y, expectedY));
        }
    }
    holder->TearDown();
}

/**
 * @tc.name: translateTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, translateTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->translate, nullptr);

    for (const auto& [x, expectedX] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_TEST_PLAN) {
            holder->SetUp();
            accessor_->translate(peer_, &x, &y);

            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->x, expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->y, expectedY));
        }
    }
    holder->TearDown();
}

/**
 * @tc.name: saveLayerTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, saveLayerTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->saveLayer, nullptr);

    accessor_->saveLayer(peer_);
    accessor_->saveLayer(peer_);
    accessor_->saveLayer(peer_);

    EXPECT_EQ(holder->counter, EXPECTED_NUMBER_OF_CALLS);
    holder->TearDown();
}

/**
 * @tc.name: restoreLayerTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, restoreLayerTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->restoreLayer, nullptr);

    accessor_->restoreLayer(peer_);
    accessor_->restoreLayer(peer_);
    accessor_->restoreLayer(peer_);

    EXPECT_EQ(holder->counter, EXPECTED_NUMBER_OF_CALLS);
    holder->TearDown();
}

/**
 * @tc.name: resetTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, resetTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->reset, nullptr);

    accessor_->reset(peer_);
    accessor_->reset(peer_);
    accessor_->reset(peer_);

    EXPECT_EQ(holder->counter, EXPECTED_NUMBER_OF_CALLS);
    holder->TearDown();
}

/**
 * @tc.name: setGlobalAlphaTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setGlobalAlphaTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setGlobalAlpha, nullptr);

    for (const auto& [actual, expected] : ARK_NUMBER_ALPHA_TEST_PLAN) {
        holder->SetUp();
        accessor_->setGlobalAlpha(peer_, &actual);

        if (expected < ALPHA_LIMIT_MIN || expected > ALPHA_LIMIT_MAX) {
            EXPECT_FALSE(holder->isCalled);
            continue;
        }
        EXPECT_TRUE(holder->isCalled);
        EXPECT_TRUE(LessOrEqualCustomPrecision(holder->value, expected));
    }
    holder->TearDown();
}

/**
 * @tc.name: fillTextTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, fillTextTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->fillText, nullptr);

    auto arkT = Converter::ArkValue<Ark_String>(DEFAULT_STRING_VALUE);
    auto arkD = Converter::ArkValue<Ark_Number>(static_cast<float>(DEFAULT_DOUBLE_VALUE));
    auto arkOpt = Converter::ArkValue<Opt_Number>(arkD);

    for (const auto& [actual, expected] : ARK_STRING_TEST_PLAN) {
        holder->SetUp();
        accessor_->fillText(peer_, &actual, &arkD, &arkD, &arkOpt);

        EXPECT_TRUE(holder->isCalled);
        EXPECT_EQ(holder->text, expected);
    }
    for (const auto& [x, expectedX] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_TEST_PLAN) {
            holder->SetUp();
            accessor_->fillText(peer_, &arkT, &x, &y, &arkOpt);

            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->x, expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->y, expectedY));
        }
    }
    for (const auto& [actual, expected] : OPT_NUMBER_TEST_PLAN) {
        holder->SetUp();
        accessor_->fillText(peer_, &arkT, &arkD, &arkD, &actual);

        EXPECT_EQ(holder->maxWidth.has_value(), expected.has_value());
        if (expected.has_value()) {
            EXPECT_TRUE(LessOrEqualCustomPrecision(*holder->maxWidth, *expected));
        }
        EXPECT_TRUE(holder->isCalled);
    }
    holder->TearDown();
}

/**
 * @tc.name: strokeTextTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, strokeTextTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->strokeText, nullptr);

    auto arkT = Converter::ArkValue<Ark_String>(DEFAULT_STRING_VALUE);
    auto arkD = Converter::ArkValue<Ark_Number>(static_cast<float>(DEFAULT_DOUBLE_VALUE));
    auto arkOpt = Converter::ArkValue<Opt_Number>(arkD);

    for (const auto& [actual, expected] : ARK_STRING_TEST_PLAN) {
        holder->SetUp();
        accessor_->strokeText(peer_, &actual, &arkD, &arkD, &arkOpt);

        EXPECT_TRUE(holder->isCalled);
        EXPECT_EQ(holder->text, expected);
    }
    for (const auto& [x, expectedX] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_TEST_PLAN) {
            holder->SetUp();
            accessor_->strokeText(peer_, &arkT, &x, &y, &arkOpt);

            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->x, expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->y, expectedY));
        }
    }
    for (const auto& [actual, expected] : OPT_NUMBER_TEST_PLAN) {
        holder->SetUp();
        accessor_->strokeText(peer_, &arkT, &arkD, &arkD, &actual);

        EXPECT_EQ(holder->maxWidth.has_value(), expected.has_value());
        if (expected.has_value()) {
            EXPECT_TRUE(LessOrEqualCustomPrecision(*holder->maxWidth, *expected));
        }
        EXPECT_TRUE(holder->isCalled);
    }
    holder->TearDown();
}

/**
 * @tc.name: setTransform0Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setTransform0Test, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setTransform0, nullptr);

    auto arkD = Converter::ArkValue<Ark_Number>(static_cast<float>(DEFAULT_DOUBLE_VALUE));
    auto arkS = Converter::ArkValue<Ark_Number>(static_cast<float>(DEFAULT_SCALE_VALUE));

    for (const auto& [x, expectedX] : ARK_NUMBER_ALPHA_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_ALPHA_TEST_PLAN) {
            holder->SetUp();
            accessor_->setTransform0(peer_, &x, &arkD, &arkD, &y, &arkD, &arkD);

            if (expectedX < SCALE_LIMIT_MIN || expectedY < SCALE_LIMIT_MIN) {
                EXPECT_FALSE(holder->isCalled);
                continue;
            }
            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->scaleX, expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->scaleY, expectedY));
        }
    }
    for (const auto& [x, expectedX] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_TEST_PLAN) {
            holder->SetUp();
            accessor_->setTransform0(peer_, &arkS, &x, &y, &arkS, &arkD, &arkD);

            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->skewX, expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->skewY, expectedY));
        }
    }
    for (const auto& [x, expectedX] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_TEST_PLAN) {
            holder->SetUp();
            accessor_->setTransform0(peer_, &arkS, &arkD, &arkD, &arkS, &x, &y);

            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->transX, expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->transY, expectedY));
        }
    }
    holder->TearDown();
}

/**
 * @tc.name: transformTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, transformTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->transform, nullptr);

    auto arkD = Converter::ArkValue<Ark_Number>(static_cast<float>(DEFAULT_DOUBLE_VALUE));
    auto arkS = Converter::ArkValue<Ark_Number>(static_cast<float>(DEFAULT_SCALE_VALUE));

    for (const auto& [x, expectedX] : ARK_NUMBER_ALPHA_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_ALPHA_TEST_PLAN) {
            holder->SetUp();
            accessor_->transform(peer_, &x, &arkD, &arkD, &y, &arkD, &arkD);

            if (expectedX < SCALE_LIMIT_MIN || expectedY < SCALE_LIMIT_MIN) {
                EXPECT_FALSE(holder->isCalled);
                continue;
            }
            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->scaleX, expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->scaleY, expectedY));
        }
    }
    for (const auto& [x, expectedX] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_TEST_PLAN) {
            holder->SetUp();
            accessor_->transform(peer_, &arkS, &x, &y, &arkS, &arkD, &arkD);

            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->skewX, expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->skewY, expectedY));
        }
    }
    for (const auto& [x, expectedX] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_TEST_PLAN) {
            holder->SetUp();
            accessor_->transform(peer_, &arkS, &arkD, &arkD, &arkS, &x, &y);

            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->transX, expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->transY, expectedY));
        }
    }
    holder->TearDown();
}

/**
 * @tc.name: setGlobalCompositeOperationTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setGlobalCompositeOperationTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setGlobalCompositeOperation, nullptr);

    for (const auto& [actual, expected] : ARK_COMPOSITE_TEST_PLAN) {
        holder->SetUp();
        accessor_->setGlobalCompositeOperation(peer_, &actual);

        if (expected == INVALID_COMPOSITE_VALUE) {
            EXPECT_FALSE(holder->isCalled);
            continue;
        }
        EXPECT_TRUE(holder->isCalled);
        EXPECT_EQ(holder->composite, expected);
    }
    holder->TearDown();
}

/**
 * @tc.name: setFilterTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setFilterTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setFilter, nullptr);

    for (const auto& [actual, expected] : ARK_STRING_TEST_PLAN) {
        holder->SetUp();
        accessor_->setFilter(peer_, &actual);

        if (expected == INVALID_STRING_VALUE) {
            EXPECT_FALSE(holder->isCalled);
            continue;
        }
        EXPECT_TRUE(holder->isCalled);
        EXPECT_EQ(holder->text, expected);
    }
    holder->TearDown();
}

/**
 * @tc.name: setImageSmoothingEnabledTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setImageSmoothingEnabledTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setImageSmoothingEnabled, nullptr);

    for (const auto& [actual, expected] : ARK_BOOL_TEST_PLAN) {
        holder->SetUp();

        accessor_->setImageSmoothingEnabled(peer_, actual);
        EXPECT_TRUE(holder->isCalled);
        EXPECT_EQ(holder->enabled, expected);
    }
    holder->TearDown();
}

/**
 * @tc.name: setLineDashOffsetTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setLineDashOffsetTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setLineDashOffset, nullptr);

    for (const auto& [actual, expected] : ARK_NUMBER_TEST_PLAN) {
        holder->SetUp();

        accessor_->setLineDashOffset(peer_, &actual);
        EXPECT_TRUE(holder->isCalled);
        EXPECT_TRUE(LessOrEqualCustomPrecision(holder->value, expected));
    }
    holder->TearDown();
}

/**
 * @tc.name: setLineWidthTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setLineWidthTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setLineWidth, nullptr);

    for (const auto& [actual, expected] : ARK_NUMBER_TEST_PLAN) {
        holder->SetUp();

        accessor_->setLineWidth(peer_, &actual);
        EXPECT_TRUE(holder->isCalled);
        EXPECT_TRUE(LessOrEqualCustomPrecision(holder->value, expected));
    }
    holder->TearDown();
}

/**
 * @tc.name: setMiterLimitTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setMiterLimitTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setMiterLimit, nullptr);

    for (const auto& [actual, expected] : ARK_NUMBER_TEST_PLAN) {
        holder->SetUp();

        accessor_->setMiterLimit(peer_, &actual);
        EXPECT_TRUE(holder->isCalled);
        EXPECT_TRUE(LessOrEqualCustomPrecision(holder->value, expected));
    }
    holder->TearDown();
}

/**
 * @tc.name: setShadowBlurTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setShadowBlurTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setShadowBlur, nullptr);

    for (const auto& [actual, expected] : ARK_NUMBER_TEST_PLAN) {
        holder->SetUp();

        accessor_->setShadowBlur(peer_, &actual);
        EXPECT_TRUE(holder->isCalled);
        EXPECT_TRUE(LessOrEqualCustomPrecision(holder->value, expected));
    }
    holder->TearDown();
}

/**
 * @tc.name: setShadowColorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setShadowColorTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setShadowColor, nullptr);

    for (const auto& [actual, expected] : ARK_STRING_COLOR_TEST_PLAN) {
        holder->SetUp();
        accessor_->setShadowColor(peer_, &actual);

        if (expected == Color::BLACK) {
            EXPECT_FALSE(holder->isCalled);
            continue;
        }

        EXPECT_TRUE(holder->isCalled);
        EXPECT_EQ(holder->color.ToString(), expected.ToString());
    }
    holder->TearDown();
}

/**
 * @tc.name: setShadowOffsetXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setShadowOffsetXTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setShadowOffsetX, nullptr);

    for (const auto& [actual, expected] : ARK_NUMBER_TEST_PLAN) {
        holder->SetUp();

        accessor_->setShadowOffsetX(peer_, &actual);
        EXPECT_TRUE(holder->isCalled);
        EXPECT_TRUE(LessOrEqualCustomPrecision(holder->value, expected));
    }
    holder->TearDown();
}

/**
 * @tc.name: setShadowOffsetYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setShadowOffsetYTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setShadowOffsetY, nullptr);

    for (const auto& [actual, expected] : ARK_NUMBER_TEST_PLAN) {
        holder->SetUp();

        accessor_->setShadowOffsetY(peer_, &actual);
        EXPECT_TRUE(holder->isCalled);
        EXPECT_TRUE(LessOrEqualCustomPrecision(holder->value, expected));
    }
    holder->TearDown();
}

/**
 * @tc.name: stroke1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, stroke1Test, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->stroke1, nullptr);

    Ark_Materialized arkPath;
    auto peerImpl = Referenced::MakeRefPtr<GeneratedModifier::CanvasPathPeerImpl>();
    arkPath.ptr = reinterpret_cast<CanvasPathPeer*>(Referenced::RawPtr(peerImpl));

    for (const auto& expected : PATH2D_TEST_PLAN) {
        holder->SetUp();
        auto path = AceType::MakeRefPtr<CanvasPath2D>();
        auto cmd = std::get<0>(expected);
        auto x = std::get<1>(expected);
        auto y = std::get<2>(expected);

        if (cmd == PathCmd::MOVE_TO) {
            path->MoveTo(x, y);
        } else {
            path->LineTo(x, y);
        }
        peerImpl->path = path;

        accessor_->stroke1(peer_, &arkPath);

        auto result = holder->path->GetCaches();
        auto rcmd = result[0].first;
        auto rx = result[0].second.para1;
        auto ry = result[0].second.para2;

        EXPECT_TRUE(holder->isCalled);
        EXPECT_EQ(rcmd, cmd);
        EXPECT_TRUE(LessOrEqualCustomPrecision(rx, x));
        EXPECT_TRUE(LessOrEqualCustomPrecision(ry, y));
    }
    holder->TearDown();
}

/**
 * @tc.name: setTransform1ScaleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setTransform1ScaleTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setTransform1, nullptr);

    Ark_Matrix2D arkMatrix;
    auto peer = new Matrix2DPeer();
    arkMatrix.ptr = peer;
    auto optMatrix = Converter::ArkValue<Opt_Matrix2D>(arkMatrix);

    auto valD = DEFAULT_DOUBLE_VALUE;

    for (const auto& expectedX : NUMBER_ALPHA_TEST_PLAN) {
        for (const auto& expectedY : NUMBER_ALPHA_TEST_PLAN) {
            peer->transform.scaleX = expectedX;
            peer->transform.scaleY = expectedY;
            peer->transform.skewX = valD;
            peer->transform.skewY = valD;
            peer->transform.translateX = valD;
            peer->transform.translateY = valD;

            holder->SetUp();
            accessor_->setTransform1(peer_, &optMatrix);

            if (expectedX < SCALE_LIMIT_MIN || expectedY < SCALE_LIMIT_MIN) {
                EXPECT_FALSE(holder->isCalled);
                continue;
            }
            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->scaleX, expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->scaleY, expectedY));
        }
    }
    holder->TearDown();
}

/**
 * @tc.name: setTransform1SkewTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setTransform1SkewTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setTransform1, nullptr);

    Ark_Matrix2D arkMatrix;
    auto peer = new Matrix2DPeer();
    arkMatrix.ptr = peer;
    auto optMatrix = Converter::ArkValue<Opt_Matrix2D>(arkMatrix);

    auto valD = DEFAULT_DOUBLE_VALUE;
    auto valS = DEFAULT_SCALE_VALUE;

    for (const auto& expectedX : NUMBER_TEST_PLAN) {
        for (const auto& expectedY : NUMBER_TEST_PLAN) {
            peer->transform.scaleX = valS;
            peer->transform.scaleY = valS;
            peer->transform.skewX = expectedX;
            peer->transform.skewY = expectedY;
            peer->transform.translateX = valD;
            peer->transform.translateY = valD;

            holder->SetUp();
            accessor_->setTransform1(peer_, &optMatrix);

            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->skewX, expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->skewY, expectedY));
        }
    }
    holder->TearDown();
}

/**
 * @tc.name: setTransform1TranslateTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setTransform1TranslateTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setTransform1, nullptr);

    Ark_Matrix2D arkMatrix;
    auto peer = new Matrix2DPeer();
    arkMatrix.ptr = peer;
    auto optMatrix = Converter::ArkValue<Opt_Matrix2D>(arkMatrix);

    auto valD = DEFAULT_DOUBLE_VALUE;
    auto valS = DEFAULT_SCALE_VALUE;

    for (const auto& expectedX : NUMBER_TEST_PLAN) {
        for (const auto& expectedY : NUMBER_TEST_PLAN) {
            peer->transform.scaleX = valS;
            peer->transform.scaleY = valS;
            peer->transform.skewX = valD;
            peer->transform.skewY = valD;
            peer->transform.translateX = expectedX;
            peer->transform.translateY = expectedY;

            holder->SetUp();
            accessor_->setTransform1(peer_, &optMatrix);

            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->transX, expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->transY, expectedY));
        }
    }
    holder->TearDown();
}

#ifdef PIXEL_MAP_SUPPORTED
/**
 * @tc.name: transferFromImageBitmapTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, DISABLED_transferFromImageBitmapTest, TestSize.Level1) {}
#else

/**
 * @tc.name: transferFromImageBitmapTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, transferFromImageBitmapTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->transferFromImageBitmap, nullptr);

    Ark_Materialized arkBitmap;
    auto peer = new MockImageBitmapPeer();
    arkBitmap.ptr = peer;

    for (const auto& expectedW : SIZE_TEST_PLAN) {
        for (const auto& expectedH : SIZE_TEST_PLAN) {
            peer->SetWidth(expectedW);
            peer->SetHeight(expectedH);

            holder->SetUp();
            accessor_->transferFromImageBitmap(peer_, &arkBitmap);
            if (expectedW <= 0 || expectedH <= 0) {
                EXPECT_FALSE(holder->isCalled);
                continue;
            }
            EXPECT_TRUE(holder->isCalled);
            EXPECT_EQ(holder->imageData->dirtyWidth, expectedW);
            EXPECT_EQ(holder->imageData->dirtyHeight, expectedH);
        }
    }
    holder->TearDown();
}
#endif

/**
 * @tc.name: setFontStyleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setFontStyleTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setFont, nullptr);

    auto weight = FONT_WEIGHT_TEST_PLAN[0].first;
    auto size = FONT_SIZE_PX_TEST_PLAN[0].first;
    auto family = FONT_FAMILIES_TEST_PLAN[0].first;

    for (const auto& [actual, expected] : FONT_STYLE_TEST_PLAN) {
        auto font = actual + " " + weight + " " + size + " " + family;
        auto arkFont = Converter::ArkValue<Ark_String>(font);

        holder->SetUp();
        accessor_->setFont(peer_, &arkFont);

        EXPECT_TRUE(holder->isCalled);
        EXPECT_TRUE(holder->isCalled2);
        EXPECT_TRUE(holder->isCalled3);
        EXPECT_TRUE(holder->isCalled4);
        EXPECT_EQ(holder->fontStyle, expected);
    }

    holder->TearDown();
}

/**
 * @tc.name: setFontWeightTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setFontWeightTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setFont, nullptr);

    auto style = FONT_STYLE_TEST_PLAN[0].first;
    auto size = FONT_SIZE_PX_TEST_PLAN[0].first;
    auto family = FONT_FAMILIES_TEST_PLAN[0].first;

    for (const auto& [actual, expected] : FONT_WEIGHT_TEST_PLAN) {
        auto font = style + " " + actual + " " + size + " " + family;
        auto arkFont = Converter::ArkValue<Ark_String>(font);

        holder->SetUp();
        accessor_->setFont(peer_, &arkFont);

        EXPECT_TRUE(holder->isCalled);
        EXPECT_TRUE(holder->isCalled2);
        EXPECT_TRUE(holder->isCalled3);
        EXPECT_TRUE(holder->isCalled4);
        EXPECT_EQ(holder->fontWeight, expected);
    }
    holder->TearDown();
}

/**
 * @tc.name: setFontSizePxTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setFontSizePxTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setFont, nullptr);

    auto style = FONT_STYLE_TEST_PLAN[0].first;
    auto weight = FONT_WEIGHT_TEST_PLAN[0].first;
    auto family = FONT_FAMILIES_TEST_PLAN[0].first;

    for (const auto& [actual, expected] : FONT_SIZE_PX_TEST_PLAN) {
        auto font = style + " " + weight + " " + actual + " " + family;
        auto arkFont = Converter::ArkValue<Ark_String>(font);

        holder->SetUp();
        accessor_->setFont(peer_, &arkFont);

        if (expected == Dimension(-100)) {
            EXPECT_FALSE(holder->isCalled3);
            continue;
        }
        EXPECT_TRUE(holder->isCalled);
        EXPECT_TRUE(holder->isCalled2);
        EXPECT_TRUE(holder->isCalled3);
        EXPECT_TRUE(holder->isCalled4);
        EXPECT_EQ(holder->fontSize, expected);
    }
    holder->TearDown();
}

/**
 * @tc.name: setFontSizeVpTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setFontSizeVpTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setFont, nullptr);

    auto style = FONT_STYLE_TEST_PLAN[0].first;
    auto weight = FONT_WEIGHT_TEST_PLAN[0].first;
    auto family = FONT_FAMILIES_TEST_PLAN[0].first;

    for (const auto& [actual, expected] : FONT_SIZE_VP_TEST_PLAN) {
        auto font = style + " " + weight + " " + actual + " " + family;
        auto arkFont = Converter::ArkValue<Ark_String>(font);

        holder->SetUp();
        accessor_->setFont(peer_, &arkFont);

        if (expected == Dimension(-100)) {
            EXPECT_FALSE(holder->isCalled3);
            continue;
        }
        EXPECT_TRUE(holder->isCalled);
        EXPECT_TRUE(holder->isCalled2);
        EXPECT_TRUE(holder->isCalled3);
        EXPECT_TRUE(holder->isCalled4);
        EXPECT_EQ(holder->fontSize, expected);
    }
    holder->TearDown();
}

/**
 * @tc.name: setFontFamiliesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setFontFamiliesTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setFont, nullptr);

    auto style = FONT_STYLE_TEST_PLAN[0].first;
    auto weight = FONT_WEIGHT_TEST_PLAN[0].first;
    auto size = FONT_SIZE_PX_TEST_PLAN[0].first;

    for (const auto& [actual, expected] : FONT_FAMILIES_TEST_PLAN) {
        auto font = style + " " + weight + " " + size + " " + actual;
        auto arkFont = Converter::ArkValue<Ark_String>(font);

        holder->SetUp();
        accessor_->setFont(peer_, &arkFont);

        if (expected.size() == 0) {
            EXPECT_FALSE(holder->isCalled4);
            continue;
        }

        EXPECT_TRUE(holder->isCalled);
        EXPECT_TRUE(holder->isCalled2);
        EXPECT_TRUE(holder->isCalled3);
        EXPECT_TRUE(holder->isCalled4);
        EXPECT_EQ(holder->fontFamilies, expected);
    }
    holder->TearDown();
}

/**
 * @tc.name: createLinearGradientTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, createLinearGradientTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->createLinearGradient, nullptr);
    auto valD = DEFAULT_DOUBLE_VALUE;
    for (const auto& expectedX : NUMBER_TEST_PLAN) {
        for (const auto& expectedY : NUMBER_TEST_PLAN) {
            auto x0 = Converter::ArkValue<Ark_Number>(expectedX);
            auto y0 = Converter::ArkValue<Ark_Number>(expectedY);
            auto x1 = Converter::ArkValue<Ark_Number>(valD);
            auto y1 = Converter::ArkValue<Ark_Number>(valD);
            auto ptr = accessor_->createLinearGradient(peer_, &x0, &y0, &x1, &y1);
            ASSERT_NE(ptr, nullptr);
            auto peer = reinterpret_cast<CanvasGradientPeer*>(ptr);
            ASSERT_NE(peer, nullptr);
            std::shared_ptr<OHOS::Ace::Gradient> gradient = peer->GetGradient();
            ASSERT_NE(gradient, nullptr);
            auto o1 = gradient->GetBeginOffset();
            auto o2 = gradient->GetEndOffset();
            EXPECT_TRUE(LessOrEqualCustomPrecision(o1.GetX(), expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(o1.GetY(), expectedY));
            EXPECT_TRUE(LessOrEqualCustomPrecision(o2.GetX(), valD));
            EXPECT_TRUE(LessOrEqualCustomPrecision(o2.GetY(), valD));
        }
    }
    for (const auto& expectedX : NUMBER_TEST_PLAN) {
        for (const auto& expectedY : NUMBER_TEST_PLAN) {
            auto x0 = Converter::ArkValue<Ark_Number>(valD);
            auto y0 = Converter::ArkValue<Ark_Number>(valD);
            auto x1 = Converter::ArkValue<Ark_Number>(expectedX);
            auto y1 = Converter::ArkValue<Ark_Number>(expectedY);
            auto ptr = accessor_->createLinearGradient(peer_, &x0, &y0, &x1, &y1);
            ASSERT_NE(ptr, nullptr);
            auto peer = reinterpret_cast<CanvasGradientPeer*>(ptr);
            ASSERT_NE(peer, nullptr);
            std::shared_ptr<OHOS::Ace::Gradient> gradient = peer->GetGradient();
            ASSERT_NE(gradient, nullptr);
            auto o1 = gradient->GetBeginOffset();
            auto o2 = gradient->GetEndOffset();
            EXPECT_TRUE(LessOrEqualCustomPrecision(o1.GetX(), valD));
            EXPECT_TRUE(LessOrEqualCustomPrecision(o1.GetY(), valD));
            EXPECT_TRUE(LessOrEqualCustomPrecision(o2.GetX(), expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(o2.GetY(), expectedY));
        }
    }
}

/**
 * @tc.name: createRadialGradientXRTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, createRadialGradientXRTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->createRadialGradient, nullptr);
    auto valD = DEFAULT_DOUBLE_VALUE;
    auto valR = DEFAULT_SCALE_VALUE;
    for (const auto& expectedX : NUMBER_TEST_PLAN) {
        for (const auto& expectedR : NUMBER_ALPHA_TEST_PLAN) {
            auto x0 = Converter::ArkValue<Ark_Number>(expectedX);
            auto y0 = Converter::ArkValue<Ark_Number>(valD);
            auto r0 = Converter::ArkValue<Ark_Number>(expectedR);
            auto x1 = Converter::ArkValue<Ark_Number>(valD);
            auto y1 = Converter::ArkValue<Ark_Number>(valD);
            auto r1 = Converter::ArkValue<Ark_Number>(valR);
            auto ptr = accessor_->createRadialGradient(peer_, &x0, &y0, &r0, &x1, &y1, &r1);
            ASSERT_NE(ptr, nullptr);
            auto peer = reinterpret_cast<CanvasGradientPeer*>(ptr);
            ASSERT_NE(peer, nullptr);
            std::shared_ptr<OHOS::Ace::Gradient> gradient = peer->GetGradient();
            ASSERT_NE(gradient, nullptr);
            auto o1 = gradient->GetBeginOffset();
            auto o2 = gradient->GetEndOffset();
            auto ri = gradient->GetInnerRadius();
            auto ro = gradient->GetOuterRadius();
            EXPECT_TRUE(LessOrEqualCustomPrecision(o1.GetX(), expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(o1.GetY(), valD));
            EXPECT_TRUE(LessOrEqualCustomPrecision(o2.GetX(), valD));
            EXPECT_TRUE(LessOrEqualCustomPrecision(o2.GetY(), valD));
            EXPECT_TRUE(LessOrEqualCustomPrecision(ri, expectedR));
            EXPECT_TRUE(LessOrEqualCustomPrecision(ro, valR));
        }
    }
}

/**
 * @tc.name: createRadialGradientYRTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, createRadialGradientYRTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->createRadialGradient, nullptr);
    auto valD = DEFAULT_DOUBLE_VALUE;
    auto valR = DEFAULT_SCALE_VALUE;
    for (const auto& expectedY : NUMBER_TEST_PLAN) {
        for (const auto& expectedR : NUMBER_ALPHA_TEST_PLAN) {
            auto x0 = Converter::ArkValue<Ark_Number>(valD);
            auto y0 = Converter::ArkValue<Ark_Number>(valD);
            auto r0 = Converter::ArkValue<Ark_Number>(valR);
            auto x1 = Converter::ArkValue<Ark_Number>(valD);
            auto y1 = Converter::ArkValue<Ark_Number>(expectedY);
            auto r1 = Converter::ArkValue<Ark_Number>(expectedR);
            auto ptr = accessor_->createRadialGradient(peer_, &x0, &y0, &r0, &x1, &y1, &r1);
            ASSERT_NE(ptr, nullptr);
            auto peer = reinterpret_cast<CanvasGradientPeer*>(ptr);
            ASSERT_NE(peer, nullptr);
            std::shared_ptr<OHOS::Ace::Gradient> gradient = peer->GetGradient();
            ASSERT_NE(gradient, nullptr);
            auto o1 = gradient->GetBeginOffset();
            auto o2 = gradient->GetEndOffset();
            auto ri = gradient->GetInnerRadius();
            auto ro = gradient->GetOuterRadius();
            EXPECT_TRUE(LessOrEqualCustomPrecision(o1.GetX(), valD));
            EXPECT_TRUE(LessOrEqualCustomPrecision(o1.GetY(), valD));
            EXPECT_TRUE(LessOrEqualCustomPrecision(o2.GetX(), valD));
            EXPECT_TRUE(LessOrEqualCustomPrecision(o2.GetY(), expectedY));
            EXPECT_TRUE(LessOrEqualCustomPrecision(ri, valD));
            EXPECT_TRUE(LessOrEqualCustomPrecision(ro, expectedR));
        }
    }
}

/**
 * @tc.name: createRadialGradientXYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, createRadialGradientXYTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->createRadialGradient, nullptr);
    auto valD = DEFAULT_DOUBLE_VALUE;
    auto valR = DEFAULT_SCALE_VALUE;
    for (const auto& expectedX : NUMBER_TEST_PLAN) {
        for (const auto& expectedY : NUMBER_TEST_PLAN) {
            auto x0 = Converter::ArkValue<Ark_Number>(valD);
            auto y0 = Converter::ArkValue<Ark_Number>(expectedY);
            auto r0 = Converter::ArkValue<Ark_Number>(valR);
            auto x1 = Converter::ArkValue<Ark_Number>(expectedX);
            auto y1 = Converter::ArkValue<Ark_Number>(valD);
            auto r1 = Converter::ArkValue<Ark_Number>(valR);
            auto ptr = accessor_->createRadialGradient(peer_, &x0, &y0, &r0, &x1, &y1, &r1);
            ASSERT_NE(ptr, nullptr);
            auto peer = reinterpret_cast<CanvasGradientPeer*>(ptr);
            ASSERT_NE(peer, nullptr);
            std::shared_ptr<OHOS::Ace::Gradient> gradient = peer->GetGradient();
            ASSERT_NE(gradient, nullptr);
            auto o1 = gradient->GetBeginOffset();
            auto o2 = gradient->GetEndOffset();
            auto ri = gradient->GetInnerRadius();
            auto ro = gradient->GetOuterRadius();
            EXPECT_TRUE(LessOrEqualCustomPrecision(o1.GetX(), valD));
            EXPECT_TRUE(LessOrEqualCustomPrecision(o1.GetY(), expectedY));
            EXPECT_TRUE(LessOrEqualCustomPrecision(o2.GetX(), expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(o2.GetY(), valD));
            EXPECT_TRUE(LessOrEqualCustomPrecision(ri, valR));
            EXPECT_TRUE(LessOrEqualCustomPrecision(ro, valR));
        }
    }
}

/**
 * @tc.name: createConicGradientTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, createConicGradientTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->createConicGradient, nullptr);
    auto valD = DEFAULT_DOUBLE_VALUE;
    auto valR = DEFAULT_SCALE_VALUE;
    for (const auto& expectedX : NUMBER_TEST_PLAN) {
        for (const auto& expectedY : NUMBER_TEST_PLAN) {
            auto x = Converter::ArkValue<Ark_Number>(expectedX);
            auto y = Converter::ArkValue<Ark_Number>(expectedY);
            auto startAngle = Converter::ArkValue<Ark_Number>(valR);
            auto ptr = accessor_->createConicGradient(peer_, &startAngle, &x, &y);
            ASSERT_NE(ptr, nullptr);
            auto peer = reinterpret_cast<CanvasGradientPeer*>(ptr);
            ASSERT_NE(peer, nullptr);
            std::shared_ptr<OHOS::Ace::Gradient> gradient = peer->GetGradient();
            ASSERT_NE(gradient, nullptr);
            auto optX = gradient->GetConicGradient().centerX;
            auto optY = gradient->GetConicGradient().centerY;
            auto optA = gradient->GetConicGradient().startAngle;
            ASSERT_TRUE(optX);
            ASSERT_TRUE(optY);
            ASSERT_TRUE(optA);
            EXPECT_TRUE(LessOrEqualCustomPrecision((*optX).Value(), expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision((*optY).Value(), expectedY));
            EXPECT_TRUE(LessOrEqualCustomPrecision((*optA).Value(), valR));
        }
    }
    for (const auto& expectedX : NUMBER_TEST_PLAN) {
        for (const auto& actualA : NUMBER_ALPHA_TEST_PLAN) {
            auto x = Converter::ArkValue<Ark_Number>(expectedX);
            auto y = Converter::ArkValue<Ark_Number>(valD);
            auto startAngle = Converter::ArkValue<Ark_Number>(actualA);
            auto expectedA = fmod(actualA, (MATH_2_PI));
            auto ptr = accessor_->createConicGradient(peer_, &startAngle, &x, &y);
            ASSERT_NE(ptr, nullptr);
            auto peer = reinterpret_cast<CanvasGradientPeer*>(ptr);
            ASSERT_NE(peer, nullptr);
            std::shared_ptr<OHOS::Ace::Gradient> gradient = peer->GetGradient();
            ASSERT_NE(gradient, nullptr);
            auto optX = gradient->GetConicGradient().centerX;
            auto optY = gradient->GetConicGradient().centerY;
            auto optA = gradient->GetConicGradient().startAngle;
            ASSERT_TRUE(optX);
            ASSERT_TRUE(optY);
            ASSERT_TRUE(optA);
            EXPECT_TRUE(LessOrEqualCustomPrecision((*optX).Value(), expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision((*optY).Value(), valD));
            EXPECT_TRUE(LessOrEqualCustomPrecision((*optA).Value(), expectedA));
        }
    }
}

/**
 * @tc.name: createImageData0Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, createImageData0Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->createImageData0, nullptr);
    for (const auto& actualW : NUMBER_TEST_PLAN) {
        for (const auto& actualH : NUMBER_TEST_PLAN) {
            auto sw = Converter::ArkValue<Ark_Number>(actualW);
            auto sh = Converter::ArkValue<Ark_Number>(actualH);
            auto ptr = accessor_->createImageData0(peer_, &sw, &sh);
            ASSERT_NE(ptr, nullptr);
            auto peerImpl = reinterpret_cast<GeneratedModifier::CanvasRendererPeerImpl*>(ptr);
            ASSERT_NE(peerImpl, nullptr);
            auto imageData = peerImpl->imageData;
            auto expectedW = static_cast<uint32_t>(std::abs(actualW + DIFF));
            auto expectedH = static_cast<uint32_t>(std::abs(actualH + DIFF));
            EXPECT_TRUE(LessOrEqualCustomPrecision(imageData.dirtyWidth, expectedW));
            EXPECT_TRUE(LessOrEqualCustomPrecision(imageData.dirtyHeight, expectedH));
        }
    }
}

/**
 * @tc.name: createImageData1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, createImageData1Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->createImageData1, nullptr);
    for (const auto& actualW : NUMBER_TEST_PLAN) {
        for (const auto& actualH : NUMBER_TEST_PLAN) {
            auto sw = Converter::ArkValue<Ark_Number>(actualW);
            auto sh = Converter::ArkValue<Ark_Number>(actualH);
            Ark_ImageData arkImage = { .width = sw, .height = sh };
            auto ptr = accessor_->createImageData1(peer_, &arkImage);
            ASSERT_NE(ptr, nullptr);
            auto peerImpl = reinterpret_cast<GeneratedModifier::CanvasRendererPeerImpl*>(ptr);
            ASSERT_NE(peerImpl, nullptr);
            auto imageData = peerImpl->imageData;
            auto expectedW = static_cast<int32_t>(actualW);
            auto expectedH = static_cast<int32_t>(actualH);
            EXPECT_EQ(imageData.dirtyWidth, expectedW);
            EXPECT_EQ(imageData.dirtyHeight, expectedH);
        }
    }
}

/**
 * @tc.name: getImageDataTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, getImageDataTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    auto valD = DEFAULT_DOUBLE_VALUE;
    ASSERT_NE(accessor_->getImageData, nullptr);
    for (const auto& actualX : NUMBER_TEST_PLAN) {
        for (const auto& actualY : NUMBER_TEST_PLAN) {
            auto sx = Converter::ArkValue<Ark_Number>(actualX);
            auto sy = Converter::ArkValue<Ark_Number>(actualY);
            auto sw = Converter::ArkValue<Ark_Number>(valD);
            auto sh = Converter::ArkValue<Ark_Number>(valD);
            holder->SetUp();
            auto ptr = accessor_->getImageData(peer_, &sx, &sy, &sw, &sh);
            ASSERT_NE(ptr, nullptr);
            auto peerImpl = reinterpret_cast<GeneratedModifier::CanvasRendererPeerImpl*>(ptr);
            ASSERT_NE(peerImpl, nullptr);
            ASSERT_TRUE(holder->isCalled);
            ASSERT_NE(holder->imageData, nullptr);
            auto imageData = peerImpl->imageData;
            auto expected = holder->imageData;
            EXPECT_EQ(imageData.dirtyWidth, expected->dirtyWidth);
            EXPECT_EQ(imageData.dirtyHeight, expected->dirtyHeight);
        }
    }
    holder->TearDown();
}

#ifdef PIXEL_MAP_SUPPORTED
/**
 * @tc.name: getPixelMapTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, DISABLED_getPixelMapTest, TestSize.Level1) {}
#else

/**
 * @tc.name: getPixelMapTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, getPixelMapTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getPixelMap, nullptr);
    auto arkD = Converter::ArkValue<Ark_Number>(DEFAULT_DOUBLE_VALUE);
    auto arkR = Converter::ArkValue<Ark_Number>(DEFAULT_SCALE_VALUE);
    auto ptr = accessor_->getPixelMap(peer_, &arkD, &arkR, &arkD, &arkR);
    EXPECT_EQ(ptr, nullptr);
    ptr = accessor_->getPixelMap(peer_, &arkR, &arkD, &arkR, &arkD);
    EXPECT_EQ(ptr, nullptr);
}
#endif

/**
 * @tc.name: putImageData0Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, putImageData0Test, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    auto valD = DEFAULT_DOUBLE_VALUE;
    auto width = valD;
    auto height = valD;
    auto length = width * height;
    std::vector<uint32_t> vector(length);
    auto arkWidth = Converter::ArkValue<Ark_Number>(width);
    auto arkHeight = Converter::ArkValue<Ark_Number>(height);
    auto arkLength = length;
    auto arkBuffer = Ark_Buffer { .data = reinterpret_cast<void*>(vector.data()), .length = arkLength };
    auto arkData = Ark_ImageData { .data = arkBuffer, .width = arkWidth, .height = arkHeight };
    ASSERT_NE(accessor_->putImageData0, nullptr);
    for (const auto& actualX : NUMBER_TEST_PLAN) {
        for (const auto& actualY : NUMBER_TEST_PLAN) {
            auto dx = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(actualX);
            auto dy = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(actualY);
            holder->SetUp();
            accessor_->putImageData0(peer_, &arkData, &dx, &dy);
            ASSERT_TRUE(holder->isCalled);
            ASSERT_NE(holder->imageData, nullptr);
            Ace::ImageData imageData = *holder->imageData;
            auto expectedX = static_cast<uint32_t>(actualX + DIFF);
            auto expectedY = static_cast<uint32_t>(actualY + DIFF);
            auto expectedW = static_cast<uint32_t>(std::abs(width + DIFF));
            auto expectedH = static_cast<uint32_t>(std::abs(height + DIFF));
            EXPECT_EQ(imageData.x, expectedX);
            EXPECT_EQ(imageData.y, expectedY);
            EXPECT_EQ(imageData.dirtyX, DEFAULT_ZERO_VALUE);
            EXPECT_EQ(imageData.dirtyY, DEFAULT_ZERO_VALUE);
            EXPECT_EQ(imageData.dirtyWidth, expectedW);
            EXPECT_EQ(imageData.dirtyHeight, expectedH);
        }
    }
    holder->TearDown();
}

/**
 * @tc.name: putImageData1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, putImageData1Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->putImageData1, nullptr);
    auto holder = TestHolder::GetInstance();
    auto valD = DEFAULT_DOUBLE_VALUE;
    auto width = valD;
    auto height = valD;
    auto length = width * height;
    std::vector<uint32_t> vector(length);
    auto arkWidth = Converter::ArkValue<Ark_Number>(width);
    auto arkHeight = Converter::ArkValue<Ark_Number>(height);
    auto arkLength = length;
    auto arkBuffer = Ark_Buffer { .data = reinterpret_cast<void*>(vector.data()), .length = arkLength };
    auto arkData = Ark_ImageData { .data = arkBuffer, .width = arkWidth, .height = arkHeight };
    ASSERT_NE(accessor_->putImageData1, nullptr);
    for (const auto& actualX : NUMBER_TEST_PLAN) {
        for (const auto& actualY : NUMBER_TEST_PLAN) {
            auto dx = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(actualX);
            auto dy = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(actualY);
            auto dirtyX = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(valD);
            auto dirtyY = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(valD);
            auto dirtyWidth = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(valD * valD);
            auto dirtyHeight = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(valD * valD);
            holder->SetUp();
            accessor_->putImageData1(peer_, &arkData, &dx, &dy, &dirtyX, &dirtyY, &dirtyWidth, &dirtyHeight);
            ASSERT_TRUE(holder->isCalled);
            ASSERT_NE(holder->imageData, nullptr);
            Ace::ImageData imageData = *holder->imageData;
            auto expectedX = static_cast<uint32_t>(actualX + DIFF);
            auto expectedY = static_cast<uint32_t>(actualY + DIFF);
            auto expectedDX = static_cast<uint32_t>(valD + DIFF);
            auto expectedDY = static_cast<uint32_t>(valD + DIFF);
            EXPECT_EQ(imageData.x, expectedX);
            EXPECT_EQ(imageData.y, expectedY);
            EXPECT_EQ(imageData.dirtyX, expectedDX);
            EXPECT_EQ(imageData.dirtyY, expectedDY);
        }
    }
    holder->TearDown();
}

/**
 * @tc.name: getLineDashOffsetTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, getLineDashOffsetTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    ASSERT_NE(accessor_->getLineDashOffset, nullptr);
    for (const auto& actual : NUMBER_TEST_PLAN) {
        holder->SetUp();
        LineDashParam lineDash = { .dashOffset = actual };
        holder->lineDash = std::make_shared<LineDashParam>(lineDash);
        auto result = accessor_->getLineDashOffset(peer_);
        auto offset = Converter::Convert<int32_t>(result);
        auto expected = static_cast<int32_t>(actual);
        EXPECT_TRUE(holder->isCalled);
        EXPECT_EQ(offset, expected);
    }
    holder->TearDown();
}

/**
 * @tc.name: createPatternTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, createPatternTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    ASSERT_NE(accessor_->createPattern, nullptr);
    holder->SetUp();
    Ark_Materialized arkBitmap;
    auto bitmapPeer = new MockImageBitmapPeer();
    arkBitmap.ptr = bitmapPeer;
    auto repetition = Converter::ArkValue<Opt_String>("repeat");
    bitmapPeer->SetWidth(NUMBER_TEST_PLAN[0]);
    bitmapPeer->SetHeight(NUMBER_TEST_PLAN[1]);
    auto result = accessor_->createPattern(peer_, &arkBitmap, &repetition);
    ASSERT_NE(result, nullptr);
    auto patternPeer = reinterpret_cast<CanvasPatternPeer*>(result);
    ASSERT_NE(patternPeer, nullptr);
    auto rendererPeer = patternPeer->GetCanvasRenderer();
    ASSERT_NE(rendererPeer, nullptr);
    auto pattern = rendererPeer->patterns[rendererPeer->patternCount - 1];
    ASSERT_NE(patternPeer, nullptr);
    ASSERT_FALSE(holder->isCalled);
    rendererPeer->TriggerRestoreImpl();
    ASSERT_TRUE(holder->isCalled);

    std::printf("create: holder ps: %zu patternCount: %d pattern: w: %.2f h: %.2f r: %s isCalled: %d\n",
        rendererPeer->patterns.size(), rendererPeer->patternCount, pattern->GetImageWidth(), pattern->GetImageHeight(),
        pattern->GetRepetition().c_str(), holder->isCalled);

    holder->TearDown();
}

/**
 * @tc.name: getTransformTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, getTransformTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    ASSERT_NE(accessor_->measureText, nullptr);
    for (const auto& expectedX : NUMBER_TEST_PLAN) {
        for (const auto& expectedY : NUMBER_TEST_PLAN) {
            holder->SetUp();
            auto param = TransformParam {
                .scaleX = expectedX,
                .scaleY = expectedY,
            };
            holder->param = std::make_shared<TransformParam>(param);
            auto container = Container::Current();
            container->SetUseNewPipeline();
            auto result = accessor_->getTransform(peer_);
            auto matrixPeer = reinterpret_cast<Matrix2DPeer*>(result);

            std::printf("matrix: result: %s peer: %s w: %.2f h: %.2f %d\n", result == nullptr ? "null" : "exist",
                matrixPeer == nullptr ? "null" : "exist", matrixPeer->transform.scaleX, matrixPeer->transform.scaleY,
                holder->isCalled);

            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(matrixPeer->transform.scaleX, holder->param->scaleX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(matrixPeer->transform.scaleY, holder->param->scaleY));
        }
    }
    holder->TearDown();
}

/**
 * @tc.name: setImageSmoothingQualityTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setImageSmoothingQualityTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    ASSERT_NE(accessor_->setImageSmoothingQuality, nullptr);
    for (const auto& [actual, expected] : IMAGE_SMOOTHING_TEST_PLAN) {
        holder->SetUp();
        accessor_->setImageSmoothingQuality(peer_, &actual);

        std::printf("imageSmoothing: holder text: %s==%s isCalled: %d\n", holder->text.c_str(), expected.c_str(),
            holder->isCalled);

        if (expected == INVALID_STRING_VALUE) {
            EXPECT_FALSE(holder->isCalled);
            continue;
        }
        EXPECT_TRUE(holder->isCalled);
        EXPECT_EQ(holder->text, expected);
    }
    holder->TearDown();
}
/**
 * @tc.name: setLineCapTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setLineCapTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    ASSERT_NE(accessor_->setLineCap, nullptr);
    for (const auto& [actual, expected] : LINE_CAP_TEST_PLAN) {
        holder->SetUp();
        accessor_->setLineCap(peer_, &actual);

        auto lineCap = holder->lineCap ? *holder->lineCap : static_cast<LineCapStyle>(-1);
        std::printf("lineCap: holder lineCap: %d==%d isCalled: %d\n", lineCap, expected, holder->isCalled);

        EXPECT_TRUE(holder->isCalled);
        EXPECT_EQ(holder->lineCap, expected);
    }
    holder->TearDown();
}
/**
 * @tc.name: setLineJoinTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setLineJoinTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    ASSERT_NE(accessor_->setLineJoin, nullptr);
    for (const auto& [actual, expected] : LINE_JOIN_TEST_PLAN) {
        holder->SetUp();
        accessor_->setLineJoin(peer_, &actual);

        auto lineJoin = holder->lineJoin ? *holder->lineJoin : static_cast<LineJoinStyle>(-1);
        std::printf("lineCap: holder lineCap: %d==%d isCalled: %d\n", lineJoin, expected, holder->isCalled);

        EXPECT_TRUE(holder->isCalled);
        EXPECT_EQ(holder->lineJoin, expected);
    }
    holder->TearDown();
}
} // namespace OHOS::Ace::NG
