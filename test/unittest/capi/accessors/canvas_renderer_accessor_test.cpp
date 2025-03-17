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
#include "gmock/gmock-actions.h"
#include "gmock/gmock-matchers.h"

#include "core/components_ng/pattern/canvas/canvas_paint_method.h"
#include "core/components_ng/pattern/canvas/canvas_rendering_context_2d_model_ng.h"
#include "core/interfaces/native/implementation/canvas_renderer_peer_impl.h"
#include "core/interfaces/native/implementation/canvas_pattern_peer.h"
#include "core/interfaces/native/implementation/canvas_gradient_peer.h"
#include "core/interfaces/native/implementation/matrix2d_peer_impl.h"
#include "core/interfaces/native/implementation/image_bitmap_peer_impl.h"
#include "core/interfaces/native/implementation/image_data_peer.h"
#include "core/interfaces/native/implementation/pixel_map_peer.h"
#include "core/interfaces/native/implementation/path2d_peer_impl.h"
#include "core/interfaces/native/implementation/canvas_rendering_context2d_peer_impl.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
class MockCanvasRenderingContext2DModel;
const auto EXPECTED_NUMBER_OF_CALLS = 3;
const auto EXPECTED_TRUE = true;
const auto EXPECTED_FALSE = false;
const double DEFAULT_DOUBLE_VALUE = 10.0;
const double DEFAULT_SCALE_VALUE = 1.0;
const std::string DEFAULT_STRING_VALUE = "text";
const std::string INVALID_STRING_VALUE = "";
constexpr double MATH_2_PI = 2 * M_PI;
constexpr double DIFF = 1e-10;
const int32_t DEFAULT_ZERO_VALUE = 0;
const Opt_Boolean OPT_BOOLEAN_FALSE = Converter::ArkValue<Opt_Boolean>(false);
const double FLT_PRECISION = 0.001;
const double DEFAULT_DENSITY = 1.0;
const double DENSITY_1_25 = 1.25;
const double DENSITY_2_50 = 2.50;
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
    { 100, 10.25, 0, 5.42, 12.34, -1.05 },
    { 100, -10.25, 0, -5.42, 12.34 },
    { 0, 0, 0, 0, 0, 0 },
    { -100, -10.25, -2.35, -5.42, -12.34 },
    {},
};
std::vector<std::pair<std::vector<double>, std::vector<double>>> ARRAY_LINE_DASH_TEST_PLAN = {
    { { 100, 10.25, 2.35 }, { 100, 10.25, 2.35, 100, 10.25, 2.35 } },
    { { 0, 5.42 }, { 0, 5.42 } },
    { { 0, -5.42, 12.34 }, { 0, -5.42, 12.34, 0, -5.42, 12.34 } },
    { { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
    { { -100, -10.25, -2.35 }, { -100, -10.25, -2.35, -100, -10.25, -2.35 } },
    { {}, {} },
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
std::vector<std::tuple<Opt_Number, std::optional<double>>> OPT_MAX_WIDTH_TEST_PLAN = {
    { Converter::ArkValue<Opt_Number>(100), 100 },
    { Converter::ArkValue<Opt_Number>(0), 0 },
    { Converter::ArkValue<Opt_Number>(-100), -100 },
    { Converter::ArkValue<Opt_Number>(12.34), 12.34 },
    { Converter::ArkValue<Opt_Number>(-56.73), -56.73 },
    { Converter::ArkValue<Opt_Number>(Ark_Empty()), FLT_MAX },
};
std::vector<std::tuple<Ark_String, CompositeOperation>> ARK_COMPOSITE_TEST_PLAN = {
    { Converter::ArkValue<Ark_String>("source-over"), CompositeOperation::SOURCE_OVER },
    { Converter::ArkValue<Ark_String>("source-atop"), CompositeOperation::SOURCE_ATOP },
    { Converter::ArkValue<Ark_String>("source-in"), CompositeOperation::SOURCE_IN },
    { Converter::ArkValue<Ark_String>("source-out"), CompositeOperation::SOURCE_OUT },
    { Converter::ArkValue<Ark_String>("destination-over"), CompositeOperation::DESTINATION_OVER },
    { Converter::ArkValue<Ark_String>("destination-atop"), CompositeOperation::DESTINATION_ATOP },
    { Converter::ArkValue<Ark_String>("destination-in"), CompositeOperation::DESTINATION_IN },
    { Converter::ArkValue<Ark_String>("destination-out"), CompositeOperation::DESTINATION_OUT },
    { Converter::ArkValue<Ark_String>("lighter"), CompositeOperation::LIGHTER },
    { Converter::ArkValue<Ark_String>("copy"), CompositeOperation::COPY },
    { Converter::ArkValue<Ark_String>("xor"), CompositeOperation::XOR },
    { Converter::ArkValue<Ark_String>(""), CompositeOperation::SOURCE_OVER},
    { Converter::ArkValue<Ark_String>("unknown value"), CompositeOperation::SOURCE_OVER },
};
std::vector<std::tuple<Ark_String, Color>> ARK_STRING_COLOR_TEST_PLAN = {
    { Converter::ArkValue<Ark_String>("#ff0000ff"), Color(0xff0000ff) },
    { Converter::ArkValue<Ark_String>("#00000000"), Color(0x00000000) },
    { Converter::ArkValue<Ark_String>("#80ffffff"), Color(0x80ffffff) },
    { Converter::ArkValue<Ark_String>(""), Color(0x00000000) },
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
std::vector<std::tuple<Opt_String, Ace::CanvasFillRule>> FILL_RULE_TEST_PLAN = {
    { Converter::ArkValue<Opt_String>("evenodd"), Ace::CanvasFillRule::EVENODD },
    { Converter::ArkValue<Opt_String>("nonzero"), Ace::CanvasFillRule::NONZERO },
    { Converter::ArkValue<Opt_String>("invalid"), Ace::CanvasFillRule::NONZERO },
    { Converter::ArkValue<Opt_String>(""), Ace::CanvasFillRule::NONZERO },
    { Converter::ArkValue<Opt_String>(Ark_Empty()), Ace::CanvasFillRule::NONZERO }
};
std::vector<std::tuple<Ark_String, Ace::TextDirection>> DIRECTION_TEST_PLAN = {
    { Converter::ArkValue<Ark_String>("ltr"), Ace::TextDirection::LTR },
    { Converter::ArkValue<Ark_String>("rtl"), Ace::TextDirection::RTL },
    { Converter::ArkValue<Ark_String>("inherit"), Ace::TextDirection::INHERIT },
    { Converter::ArkValue<Ark_String>("auto"), Ace::TextDirection::AUTO },
    { Converter::ArkValue<Ark_String>("invalid"), Ace::TextDirection::LTR },
    { Converter::ArkValue<Ark_String>(""), Ace::TextDirection::LTR },
};
std::vector<std::tuple<Ark_String, Ace::TextAlign>> TEXT_ALIGN_TEST_PLAN = {
    { Converter::ArkValue<Ark_String>("center"), Ace::TextAlign::CENTER },
    { Converter::ArkValue<Ark_String>("end"), Ace::TextAlign::END },
    { Converter::ArkValue<Ark_String>("justify"), Ace::TextAlign::JUSTIFY },
    { Converter::ArkValue<Ark_String>("left"), Ace::TextAlign::LEFT },
    { Converter::ArkValue<Ark_String>("right"), Ace::TextAlign::RIGHT },
    { Converter::ArkValue<Ark_String>("start"), Ace::TextAlign::START },
    { Converter::ArkValue<Ark_String>("invalid"), Ace::TextAlign::CENTER },
    { Converter::ArkValue<Ark_String>(""), Ace::TextAlign::CENTER },
};
std::vector<std::tuple<Ark_String, TextBaseline>> TEXT_BASE_LINE_TEST_PLAN = {
    { Converter::ArkValue<Ark_String>("alphabetic"), Ace::TextBaseline::ALPHABETIC },
    { Converter::ArkValue<Ark_String>("bottom"), Ace::TextBaseline::BOTTOM },
    { Converter::ArkValue<Ark_String>("hanging"), Ace::TextBaseline::HANGING },
    { Converter::ArkValue<Ark_String>("ideographic"), Ace::TextBaseline::IDEOGRAPHIC },
    { Converter::ArkValue<Ark_String>("middle"), Ace::TextBaseline::MIDDLE },
    { Converter::ArkValue<Ark_String>("top"), Ace::TextBaseline::TOP },
    { Converter::ArkValue<Ark_String>("invalid"), Ace::TextBaseline::ALPHABETIC },
    { Converter::ArkValue<Ark_String>(""), Ace::TextBaseline::ALPHABETIC },
};
class MockPixelMap : public PixelMap {
public:
    MOCK_METHOD(bool, GetPixelsVec, (std::vector<uint8_t> & data), (const override));
    MOCK_METHOD(const uint8_t*, GetPixels, (), (const override));
    MOCK_METHOD(PixelFormat, GetPixelFormat, (), (const override));
    MOCK_METHOD(AlphaType, GetAlphaType, (), (const override));
    MOCK_METHOD(int32_t, GetRowStride, (), (const override));
    MOCK_METHOD(int32_t, GetRowBytes, (), (const override));
    MOCK_METHOD(int32_t, GetByteCount, (), (const override));
    MOCK_METHOD(void*, GetPixelManager, (), (const override));
    MOCK_METHOD(void*, GetRawPixelMapPtr, (), (const override));
    MOCK_CONST_METHOD0(GetWritablePixels, void*());
    MOCK_METHOD(void, Scale, (float xAxis, float yAxis), (override));
    MOCK_METHOD(void, Scale, (float xAxis, float yAxis, const AceAntiAliasingOption &option), (override));
    MOCK_METHOD(std::string, GetId, (), (override));
    MOCK_METHOD(std::string, GetModifyId, (), (override));
    MOCK_METHOD0(GetPixelMapSharedPtr, std::shared_ptr<Media::PixelMap>());
    MOCK_METHOD(void, SavePixelMapToFile, (const std::string& dst), (const override));
    MOCK_METHOD(RefPtr<PixelMap>, GetCropPixelMap, (const Rect& srcRect), (override));
    MOCK_METHOD(bool, EncodeTlv, (std::vector<uint8_t>& buff), (override));
    MOCK_METHOD(AllocatorType, GetAllocatorType, (), (const override));
    MOCK_METHOD(bool, IsHdr, (), (const override));

    int32_t GetWidth() const override
    {
        return width;
    }

    int32_t GetHeight() const override
    {
        return height;
    }

public:
    int32_t width = 0;
    int32_t height = 0;
};
class MockCanvasRenderingContext2DModel : public NG::CanvasRenderingContext2DModelNG {
public:
    MockCanvasRenderingContext2DModel() = default;
    ~MockCanvasRenderingContext2DModel() override = default;

    MOCK_METHOD(void, BeginPath, (), (override));
    MOCK_METHOD(void, SetStrokeRuleForPath, (const CanvasFillRule&), (override));
    MOCK_METHOD(void, SetLineDash, (const std::vector<double>&), (override));
    MOCK_METHOD(void, ClearRect, (const Rect&), (override));
    MOCK_METHOD(void, FillRect, (const Rect&), (override));
    MOCK_METHOD(void, StrokeRect, (const Rect&), (override));
    MOCK_METHOD(void, Restore, (), (override));
    MOCK_METHOD(void, CanvasRendererSave, (), (override));
    MOCK_METHOD(void, ResetTransform, (), (override));
    MOCK_METHOD(void, CanvasRendererRotate, (double), (override));
    MOCK_METHOD(void, CanvasRendererScale, (double, double), (override));
    MOCK_METHOD(void, Translate, (double, double), (override));
    MOCK_METHOD(void, SaveLayer, (), (override));
    MOCK_METHOD(void, RestoreLayer, (), (override));
    MOCK_METHOD(void, Reset, (), (override));
    MOCK_METHOD(void, SetGlobalAlpha, (double), (override));
    MOCK_METHOD(void, SetFillText, (const PaintState&, const FillTextInfo&), (override));
    MOCK_METHOD(void, SetStrokeText, (const PaintState&, const FillTextInfo&), (override));
    MOCK_METHOD(void, SetTransform, (TransformParam&, bool), (override));
    MOCK_METHOD(void, Transform, (const TransformParam&), (override));
    MOCK_METHOD(void, SetCompositeType, (const CompositeOperation&), (override));
    MOCK_METHOD(void, SetFilterParam, (const std::string&), (override));
    MOCK_METHOD(void, SetSmoothingEnabled, (bool), (override));
    MOCK_METHOD(void, SetLineDashOffset, (double), (override));
    MOCK_METHOD(void, SetLineWidth, (double), (override));
    MOCK_METHOD(void, SetMiterLimit, (double), (override));
    MOCK_METHOD(void, SetShadowBlur, (double), (override));
    MOCK_METHOD(void, SetShadowColor, (const Color&), (override));
    MOCK_METHOD(void, SetShadowOffsetX, (double), (override));
    MOCK_METHOD(void, SetShadowOffsetY, (double), (override));
    MOCK_METHOD(void, SetStrokeRuleForPath2D, (const CanvasFillRule&, const RefPtr<CanvasPath2D>&), (override));
};
class MockCanvasRenderingContext2DPeer : public GeneratedModifier::CanvasRenderingContext2DPeerImpl {
public:
    MockCanvasRenderingContext2DPeer(RefPtr<MockCanvasRenderingContext2DModel>& renderingContext2DModel)
    {
        renderingContext2DModel_ = renderingContext2DModel;
    }
    ~MockCanvasRenderingContext2DPeer() override = default;
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
        renderingModel_ = AceType::MakeRefPtr<MockCanvasRenderingContext2DModel>();
        renderingContext_ = new MockCanvasRenderingContext2DPeer(renderingModel_);
        peer_ = reinterpret_cast<CanvasRendererPeer*>(renderingContext_);
    }

    void TearDown() override
    {
        AccessorTestBaseParent::TearDown();
        if (renderingModel_) {
            renderingModel_->DecRefCount();
        }
        auto pipelineContext =
            AceType::DynamicCast<NG::MockPipelineContext>(NG::MockPipelineContext::GetCurrentContext());
        pipelineContext->SetDensity(DEFAULT_DENSITY);
        renderingModel_ = nullptr;
        renderingContext_ = nullptr;
    }

    void ChangeDensity(const double density)
    {
        auto pipelineContext =
            AceType::DynamicCast<NG::MockPipelineContext>(NG::MockPipelineContext::GetCurrentContext());
        pipelineContext->SetDensity(density);
        if (renderingContext_) {
            delete renderingContext_;
        }
        renderingContext_ = new MockCanvasRenderingContext2DPeer(renderingModel_);
        peer_ = reinterpret_cast<CanvasRendererPeer*>(renderingContext_);
    }

    RefPtr<MockCanvasRenderingContext2DModel> renderingModel_ = nullptr;
    MockCanvasRenderingContext2DPeer* renderingContext_ = nullptr;
};

/**
 * @tc.name: beginPathTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, beginPathTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->beginPath, nullptr);
    EXPECT_CALL(*renderingModel_, BeginPath()).Times(EXPECTED_NUMBER_OF_CALLS);
    accessor_->beginPath(peer_);
    accessor_->beginPath(peer_);
    accessor_->beginPath(peer_);
}

/**
 * @tc.name: stroke0Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, stroke0Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->stroke0, nullptr);
    EXPECT_CALL(*renderingModel_, SetStrokeRuleForPath(CanvasFillRule::NONZERO)).Times(EXPECTED_NUMBER_OF_CALLS);
    accessor_->stroke0(peer_);
    accessor_->stroke0(peer_);
    accessor_->stroke0(peer_);
}

/**
 * @tc.name: setLineDashTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setLineDashTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setLineDash, nullptr);
    double density = DENSITY_1_25;
    ChangeDensity(density);
    for (const auto& [actual, expected] : ARRAY_LINE_DASH_TEST_PLAN) {
        const auto segments = Converter::ArkValue<Array_Number>(actual, Converter::FC);
        std::vector<double> target;
        if (actual.size() > 0) {
            EXPECT_CALL(*renderingModel_, SetLineDash(_)).WillOnce(DoAll(SaveArg<0>(&target)));
        } else {
            EXPECT_CALL(*renderingModel_, SetLineDash(_)).Times(0);
        }
        accessor_->setLineDash(peer_, &segments);
        ASSERT_EQ(target.size(), expected.size());
        for (size_t i = 0; i < expected.size(); i++) {
            EXPECT_NEAR(target[i], expected[i] * density, FLT_PRECISION);
        }
    }
}

/**
 * @tc.name: clearRectTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, clearRectTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->clearRect, nullptr);
    auto arkD = Converter::ArkValue<Ark_Number>(static_cast<float>(DEFAULT_DOUBLE_VALUE));
    for (const auto& [x, expectedX] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_TEST_PLAN) {
            auto rect = Ace::Rect(expectedX, expectedY, DEFAULT_DOUBLE_VALUE, DEFAULT_DOUBLE_VALUE);
            EXPECT_CALL(*renderingModel_, ClearRect(rect)).Times(1);
            accessor_->clearRect(peer_, &x, &y, &arkD, &arkD);
        }
    }
    // with density
    double density = DENSITY_2_50;
    ChangeDensity(density);
    for (const auto& [w, expectedW] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [h, expectedH] : ARK_NUMBER_TEST_PLAN) {
            auto rect = Ace::Rect(DEFAULT_DOUBLE_VALUE, DEFAULT_DOUBLE_VALUE, expectedW, expectedH);
            EXPECT_CALL(*renderingModel_, ClearRect(rect * density)).Times(1);
            accessor_->clearRect(peer_, &arkD, &arkD, &w, &h);
        }
    }
}

/**
 * @tc.name: fillRectTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, fillRectTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->fillRect, nullptr);
    auto arkD = Converter::ArkValue<Ark_Number>(static_cast<float>(DEFAULT_DOUBLE_VALUE));
    for (const auto& [x, expectedX] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_TEST_PLAN) {
            auto rect = Ace::Rect(expectedX, expectedY, DEFAULT_DOUBLE_VALUE, DEFAULT_DOUBLE_VALUE);
            EXPECT_CALL(*renderingModel_, FillRect(rect)).Times(1);
            accessor_->fillRect(peer_, &x, &y, &arkD, &arkD);
        }
    }
    // with density
    double density = DENSITY_1_25;
    ChangeDensity(density);
    for (const auto& [w, expectedW] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [h, expectedH] : ARK_NUMBER_TEST_PLAN) {
            auto rect = Ace::Rect(DEFAULT_DOUBLE_VALUE, DEFAULT_DOUBLE_VALUE, expectedW, expectedH);
            EXPECT_CALL(*renderingModel_, FillRect(rect * density)).Times(1);
            accessor_->fillRect(peer_, &arkD, &arkD, &w, &h);
        }
    }
}

/**
 * @tc.name: strokeRectTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, strokeRectTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->strokeRect, nullptr);
    auto arkD = Converter::ArkValue<Ark_Number>(static_cast<float>(DEFAULT_DOUBLE_VALUE));
    for (const auto& [x, expectedX] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_TEST_PLAN) {
            auto rect = Ace::Rect(expectedX, expectedY, DEFAULT_DOUBLE_VALUE, DEFAULT_DOUBLE_VALUE);
            EXPECT_CALL(*renderingModel_, StrokeRect(rect)).Times(1);
            accessor_->strokeRect(peer_, &x, &y, &arkD, &arkD);
        }
    }
    // with density
    double density = DENSITY_2_50;
    ChangeDensity(density);
    for (const auto& [w, expectedW] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [h, expectedH] : ARK_NUMBER_TEST_PLAN) {
            auto rect = Ace::Rect(DEFAULT_DOUBLE_VALUE, DEFAULT_DOUBLE_VALUE, expectedW, expectedH);
            EXPECT_CALL(*renderingModel_, StrokeRect(rect * density)).Times(1);
            accessor_->strokeRect(peer_, &arkD, &arkD, &w, &h);
        }
    }
}

/**
 * @tc.name: restoreTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, restoreTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->restore, nullptr);
    EXPECT_CALL(*renderingModel_, Restore()).Times(EXPECTED_NUMBER_OF_CALLS);
    accessor_->restore(peer_);
    accessor_->restore(peer_);
    accessor_->restore(peer_);
}

/**
 * @tc.name: saveTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, saveTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->save, nullptr);
    EXPECT_CALL(*renderingModel_, CanvasRendererSave()).Times(EXPECTED_NUMBER_OF_CALLS);
    accessor_->save(peer_);
    accessor_->save(peer_);
    accessor_->save(peer_);
}

/**
 * @tc.name: resetTransformTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, resetTransformTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->resetTransform, nullptr);
    EXPECT_CALL(*renderingModel_, ResetTransform()).Times(EXPECTED_NUMBER_OF_CALLS);
    accessor_->resetTransform(peer_);
    accessor_->resetTransform(peer_);
    accessor_->resetTransform(peer_);
}

/**
 * @tc.name: rotateTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, rotateTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->rotate, nullptr);
    for (const auto& [actual, expected] : ARK_NUMBER_TEST_PLAN) {
        double target;
        EXPECT_CALL(*renderingModel_, CanvasRendererRotate(_)).WillOnce(DoAll(SaveArg<0>(&target)));
        accessor_->rotate(peer_, &actual);
        EXPECT_NEAR(target, expected, FLT_PRECISION);
    }
}

/**
 * @tc.name: scaleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, scaleTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->scale, nullptr);
    for (const auto& [x, expectedX] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_TEST_PLAN) {
            double targetX, targetY;
            EXPECT_CALL(*renderingModel_, CanvasRendererScale(_, _))
                .WillOnce(DoAll(SaveArg<0>(&targetX), SaveArg<1>(&targetY)));
            accessor_->scale(peer_, &x, &y);
            EXPECT_NEAR(targetX, expectedX, FLT_PRECISION);
            EXPECT_NEAR(targetY, expectedY, FLT_PRECISION);
        }
    }
}

/**
 * @tc.name: translateTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, translateTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->translate, nullptr);
    for (const auto& [x, expectedX] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_TEST_PLAN) {
            double targetX, targetY;
            EXPECT_CALL(*renderingModel_, Translate(_, _)).WillOnce(DoAll(SaveArg<0>(&targetX), SaveArg<1>(&targetY)));
            accessor_->translate(peer_, &x, &y);
            EXPECT_NEAR(targetX, expectedX, FLT_PRECISION);
            EXPECT_NEAR(targetY, expectedY, FLT_PRECISION);
        }
    }
    // with density
    double density = DENSITY_1_25;
    ChangeDensity(density);
    for (const auto& [x, expectedX] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_TEST_PLAN) {
            double targetX, targetY;
            EXPECT_CALL(*renderingModel_, Translate(_, _)).WillOnce(DoAll(SaveArg<0>(&targetX), SaveArg<1>(&targetY)));
            accessor_->translate(peer_, &x, &y);
            EXPECT_NEAR(targetX, expectedX * density, FLT_PRECISION);
            EXPECT_NEAR(targetY, expectedY * density, FLT_PRECISION);
        }
    }
}

/**
 * @tc.name: saveLayerTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, saveLayerTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->saveLayer, nullptr);
    EXPECT_CALL(*renderingModel_, SaveLayer()).Times(EXPECTED_NUMBER_OF_CALLS);
    accessor_->saveLayer(peer_);
    accessor_->saveLayer(peer_);
    accessor_->saveLayer(peer_);
}

/**
 * @tc.name: restoreLayerTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, restoreLayerTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->restoreLayer, nullptr);
    EXPECT_CALL(*renderingModel_, RestoreLayer()).Times(EXPECTED_NUMBER_OF_CALLS);
    accessor_->restoreLayer(peer_);
    accessor_->restoreLayer(peer_);
    accessor_->restoreLayer(peer_);
}

/**
 * @tc.name: resetTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, resetTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->reset, nullptr);
    EXPECT_CALL(*renderingModel_, Reset()).Times(EXPECTED_NUMBER_OF_CALLS);
    accessor_->reset(peer_);
    accessor_->reset(peer_);
    accessor_->reset(peer_);
}

/**
 * @tc.name: setGlobalAlphaTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setGlobalAlphaTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setGlobalAlpha, nullptr);
    for (const auto& [actual, expected] : ARK_NUMBER_ALPHA_TEST_PLAN) {
        double target;
        EXPECT_CALL(*renderingModel_, SetGlobalAlpha(_)).WillOnce(DoAll(SaveArg<0>(&target)));
        accessor_->setGlobalAlpha(peer_, &actual);
        EXPECT_NEAR(target, expected, FLT_PRECISION);
    }
}

/**
 * @tc.name: fillTextTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, fillTextTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->fillText, nullptr);
    auto arkT = Converter::ArkValue<Ark_String>(DEFAULT_STRING_VALUE, Converter::FC);
    auto arkD = Converter::ArkValue<Ark_Number>(static_cast<float>(DEFAULT_DOUBLE_VALUE));
    auto arkOpt = Converter::ArkValue<Opt_Number>(arkD);
    for (const auto& [actual, expected] : ARK_STRING_TEST_PLAN) {
        FillTextInfo target;
        EXPECT_CALL(*renderingModel_, SetFillText(_, _)).WillOnce(DoAll(SaveArg<1>(&target)));
        accessor_->fillText(peer_, &actual, &arkD, &arkD, &arkOpt);
        EXPECT_EQ(target.text, expected);
    }
    for (const auto& [x, expectedX] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_TEST_PLAN) {
            FillTextInfo target;
            EXPECT_CALL(*renderingModel_, SetFillText(_, _)).WillOnce(DoAll(SaveArg<1>(&target)));
            accessor_->fillText(peer_, &arkT, &x, &y, &arkOpt);
            EXPECT_NEAR(target.x, expectedX, FLT_PRECISION);
            EXPECT_NEAR(target.y, expectedY, FLT_PRECISION);
        }
    }
    for (const auto& [actual, expected] : OPT_MAX_WIDTH_TEST_PLAN) {
        FillTextInfo target;
        if (expected && expected.value() < 0) {
            EXPECT_CALL(*renderingModel_, SetFillText(_, _)).Times(0);
            accessor_->fillText(peer_, &arkT, &arkD, &arkD, &actual);
        } else {
            EXPECT_CALL(*renderingModel_, SetFillText(_, _)).WillOnce(DoAll(SaveArg<1>(&target)));
            accessor_->fillText(peer_, &arkT, &arkD, &arkD, &actual);
            EXPECT_EQ(target.maxWidth.has_value(), expected.has_value());
            EXPECT_NEAR(target.maxWidth ? *target.maxWidth : DEFAULT_DOUBLE_VALUE,
                expected ? *expected : DEFAULT_DOUBLE_VALUE, FLT_PRECISION);
        }
    }
}

/**
 * @tc.name: strokeTextTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, strokeTextTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->strokeText, nullptr);
    auto arkT = Converter::ArkValue<Ark_String>(DEFAULT_STRING_VALUE, Converter::FC);
    auto arkD = Converter::ArkValue<Ark_Number>(static_cast<float>(DEFAULT_DOUBLE_VALUE));
    auto arkOpt = Converter::ArkValue<Opt_Number>(arkD);
    for (const auto& [actual, expected] : ARK_STRING_TEST_PLAN) {
        FillTextInfo target;
        EXPECT_CALL(*renderingModel_, SetStrokeText(_, _)).WillOnce(DoAll(SaveArg<1>(&target)));
        accessor_->strokeText(peer_, &actual, &arkD, &arkD, &arkOpt);
        EXPECT_EQ(target.text, expected);
    }
    for (const auto& [x, expectedX] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_TEST_PLAN) {
            FillTextInfo target;
            EXPECT_CALL(*renderingModel_, SetStrokeText(_, _)).WillOnce(DoAll(SaveArg<1>(&target)));
            accessor_->strokeText(peer_, &arkT, &x, &y, &arkOpt);
            EXPECT_NEAR(target.x, expectedX, FLT_PRECISION);
            EXPECT_NEAR(target.y, expectedY, FLT_PRECISION);
        }
    }
    for (const auto& [actual, expected] : OPT_MAX_WIDTH_TEST_PLAN) {
        FillTextInfo target;
        if (expected && expected.value() < 0) {
            EXPECT_CALL(*renderingModel_, SetStrokeText(_, _)).Times(0);
            accessor_->strokeText(peer_, &arkT, &arkD, &arkD, &actual);
        } else {
            EXPECT_CALL(*renderingModel_, SetStrokeText(_, _)).WillOnce(DoAll(SaveArg<1>(&target)));
            accessor_->strokeText(peer_, &arkT, &arkD, &arkD, &actual);
            EXPECT_EQ(target.maxWidth.has_value(), expected.has_value());
            EXPECT_NEAR(target.maxWidth ? *target.maxWidth : DEFAULT_DOUBLE_VALUE,
                expected ? *expected : DEFAULT_DOUBLE_VALUE, FLT_PRECISION);
        }
    }
}

/**
 * @tc.name: setTransform0Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setTransform0Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->setTransform0, nullptr);
    auto arkD = Converter::ArkValue<Ark_Number>(static_cast<float>(DEFAULT_DOUBLE_VALUE));
    auto arkS = Converter::ArkValue<Ark_Number>(static_cast<float>(DEFAULT_SCALE_VALUE));
    for (const auto& [x, expectedX] : ARK_NUMBER_ALPHA_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_ALPHA_TEST_PLAN) {
            TransformParam target;
            EXPECT_CALL(*renderingModel_, SetTransform(_, EXPECTED_TRUE)).WillOnce(DoAll(SaveArg<0>(&target)));
            accessor_->setTransform0(peer_, &x, &arkD, &arkD, &y, &arkD, &arkD);
            EXPECT_NEAR(target.scaleX, expectedX, FLT_PRECISION);
            EXPECT_NEAR(target.scaleY, expectedY, FLT_PRECISION);
        }
    }
    for (const auto& [x, expectedX] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_TEST_PLAN) {
            TransformParam target;
            EXPECT_CALL(*renderingModel_, SetTransform(_, EXPECTED_TRUE)).WillOnce(DoAll(SaveArg<0>(&target)));
            accessor_->setTransform0(peer_, &arkS, &x, &y, &arkS, &arkD, &arkD);
            EXPECT_NEAR(target.skewX, expectedX, FLT_PRECISION);
            EXPECT_NEAR(target.skewY, expectedY, FLT_PRECISION);
        }
    }
    for (const auto& [x, expectedX] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_TEST_PLAN) {
            TransformParam target;
            EXPECT_CALL(*renderingModel_, SetTransform(_, EXPECTED_TRUE)).WillOnce(DoAll(SaveArg<0>(&target)));
            accessor_->setTransform0(peer_, &arkS, &arkD, &arkD, &arkS, &x, &y);
            EXPECT_NEAR(target.translateX, expectedX, FLT_PRECISION);
            EXPECT_NEAR(target.translateY, expectedY, FLT_PRECISION);
        }
    }
    // with density
    double density = DENSITY_1_25;
    ChangeDensity(density);
    for (const auto& [x, expectedX] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_TEST_PLAN) {
            TransformParam target;
            EXPECT_CALL(*renderingModel_, SetTransform(_, EXPECTED_TRUE)).WillOnce(DoAll(SaveArg<0>(&target)));
            accessor_->setTransform0(peer_, &arkS, &arkD, &arkD, &arkS, &x, &y);
            EXPECT_NEAR(target.translateX, expectedX * density, FLT_PRECISION);
            EXPECT_NEAR(target.translateY, expectedY * density, FLT_PRECISION);
        }
    }
}

/**
 * @tc.name: transformTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, transformTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->transform, nullptr);
    auto arkD = Converter::ArkValue<Ark_Number>(static_cast<float>(DEFAULT_DOUBLE_VALUE));
    auto arkS = Converter::ArkValue<Ark_Number>(static_cast<float>(DEFAULT_SCALE_VALUE));
    for (const auto& [x, expectedX] : ARK_NUMBER_ALPHA_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_ALPHA_TEST_PLAN) {
            TransformParam target;
            EXPECT_CALL(*renderingModel_, Transform(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            accessor_->transform(peer_, &x, &arkD, &arkD, &y, &arkD, &arkD);
            EXPECT_NEAR(target.scaleX, expectedX, FLT_PRECISION);
            EXPECT_NEAR(target.scaleY, expectedY, FLT_PRECISION);
        }
    }
    for (const auto& [x, expectedX] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_TEST_PLAN) {
            TransformParam target;
            EXPECT_CALL(*renderingModel_, Transform(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            accessor_->transform(peer_, &arkS, &x, &y, &arkS, &arkD, &arkD);
            EXPECT_NEAR(target.skewX, expectedX, FLT_PRECISION);
            EXPECT_NEAR(target.skewY, expectedY, FLT_PRECISION);
        }
    }
    for (const auto& [x, expectedX] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_TEST_PLAN) {
            TransformParam target;
            EXPECT_CALL(*renderingModel_, Transform(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            accessor_->transform(peer_, &arkS, &arkD, &arkD, &arkS, &x, &y);
            EXPECT_NEAR(target.translateX, expectedX, FLT_PRECISION);
            EXPECT_NEAR(target.translateY, expectedY, FLT_PRECISION);
        }
    }
    // with density
    double density = DENSITY_2_50;
    ChangeDensity(density);
    for (const auto& [x, expectedX] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_TEST_PLAN) {
            TransformParam target;
            EXPECT_CALL(*renderingModel_, Transform(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            accessor_->transform(peer_, &arkS, &arkD, &arkD, &arkS, &x, &y);
            EXPECT_NEAR(target.translateX, expectedX * density, FLT_PRECISION);
            EXPECT_NEAR(target.translateY, expectedY * density, FLT_PRECISION);
        }
    }
}

/**
 * @tc.name: setGlobalCompositeOperationTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setGlobalCompositeOperationTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setGlobalCompositeOperation, nullptr);
    for (const auto& [actual, expected] : ARK_COMPOSITE_TEST_PLAN) {
        EXPECT_CALL(*renderingModel_, SetCompositeType(expected)).Times(1);
        accessor_->setGlobalCompositeOperation(peer_, &actual);
    }
}

/**
 * @tc.name: setFilterTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setFilterTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setFilter, nullptr);
    for (const auto& [actual, expected] : ARK_STRING_TEST_PLAN) {
        auto nCalls = expected.empty() ? 0 : 1;
        EXPECT_CALL(*renderingModel_, SetFilterParam(expected)).Times(nCalls);
        accessor_->setFilter(peer_, &actual);
    }
}

/**
 * @tc.name: setImageSmoothingEnabledTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setImageSmoothingEnabledTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setImageSmoothingEnabled, nullptr);
    for (const auto& [actual, expected] : ARK_BOOL_TEST_PLAN) {
        EXPECT_CALL(*renderingModel_, SetSmoothingEnabled(expected)).Times(1);
        accessor_->setImageSmoothingEnabled(peer_, actual);
    }
}

/**
 * @tc.name: setLineDashOffsetTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setLineDashOffsetTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setLineDashOffset, nullptr);
    for (const auto& [actual, expected] : ARK_NUMBER_TEST_PLAN) {
        double target;
        EXPECT_CALL(*renderingModel_, SetLineDashOffset(_)).WillOnce(DoAll(SaveArg<0>(&target)));
        accessor_->setLineDashOffset(peer_, &actual);
        EXPECT_NEAR(target, expected, FLT_PRECISION);
    }
}

/**
 * @tc.name: setLineWidthTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setLineWidthTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setLineWidth, nullptr);
    for (const auto& [actual, expected] : ARK_NUMBER_TEST_PLAN) {
        double target;
        EXPECT_CALL(*renderingModel_, SetLineWidth(_)).WillOnce(DoAll(SaveArg<0>(&target)));
        accessor_->setLineWidth(peer_, &actual);
        EXPECT_NEAR(target, expected, FLT_PRECISION);
    }
}

/**
 * @tc.name: setMiterLimitTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setMiterLimitTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setMiterLimit, nullptr);
    for (const auto& [actual, expected] : ARK_NUMBER_TEST_PLAN) {
        double target;
        EXPECT_CALL(*renderingModel_, SetMiterLimit(_)).WillOnce(DoAll(SaveArg<0>(&target)));
        accessor_->setMiterLimit(peer_, &actual);
        EXPECT_NEAR(target, expected, FLT_PRECISION);
    }
}

/**
 * @tc.name: setShadowBlurTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setShadowBlurTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setShadowBlur, nullptr);
    for (const auto& [actual, expected] : ARK_NUMBER_TEST_PLAN) {
        double target;
        EXPECT_CALL(*renderingModel_, SetShadowBlur(_)).WillOnce(DoAll(SaveArg<0>(&target)));
        accessor_->setShadowBlur(peer_, &actual);
        EXPECT_NEAR(target, expected, FLT_PRECISION);
    }
}

/**
 * @tc.name: setShadowColorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setShadowColorTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setShadowColor, nullptr);
    for (const auto& [actual, expected] : ARK_STRING_COLOR_TEST_PLAN) {
        EXPECT_CALL(*renderingModel_, SetShadowColor(expected)).Times(1);
        accessor_->setShadowColor(peer_, &actual);
    }
}

/**
 * @tc.name: setShadowOffsetXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setShadowOffsetXTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setShadowOffsetX, nullptr);
    for (const auto& [actual, expected] : ARK_NUMBER_TEST_PLAN) {
        double target;
        EXPECT_CALL(*renderingModel_, SetShadowOffsetX(_)).WillOnce(DoAll(SaveArg<0>(&target)));
        accessor_->setShadowOffsetX(peer_, &actual);
        EXPECT_NEAR(target, expected, FLT_PRECISION);
    }
}

/**
 * @tc.name: setShadowOffsetYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setShadowOffsetYTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setShadowOffsetY, nullptr);
    for (const auto& [actual, expected] : ARK_NUMBER_TEST_PLAN) {
        double target;
        EXPECT_CALL(*renderingModel_, SetShadowOffsetY(_)).WillOnce(DoAll(SaveArg<0>(&target)));
        accessor_->setShadowOffsetY(peer_, &actual);
        EXPECT_NEAR(target, expected, FLT_PRECISION);
    }
}

/**
 * @tc.name: stroke1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, stroke1Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->stroke1, nullptr);
    auto peerImpl = Referenced::MakeRefPtr<Path2DPeer>();
    Ark_Path2D arkPath = Referenced::RawPtr(peerImpl);
    auto path = AceType::MakeRefPtr<CanvasPath2D>();
    peerImpl->SetCanvasPath2d(path);
    EXPECT_CALL(*renderingModel_, SetStrokeRuleForPath2D(CanvasFillRule::NONZERO, path)).Times(1);
    accessor_->stroke1(peer_, arkPath);
}

/**
 * @tc.name: setTransform1ScaleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setTransform1ScaleTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setTransform1, nullptr);
    Ark_Matrix2D arkMatrix;
    auto peer = new Matrix2DPeer();
    arkMatrix = peer;
    auto optMatrix = Converter::ArkValue<Opt_Matrix2D>(arkMatrix);
    for (const auto& expectedX : NUMBER_ALPHA_TEST_PLAN) {
        for (const auto& expectedY : NUMBER_ALPHA_TEST_PLAN) {
            TransformParam target;
            EXPECT_CALL(*renderingModel_, SetTransform(_, EXPECTED_FALSE)).WillOnce(DoAll(SaveArg<0>(&target)));
            peer->SetScaleX(expectedX);
            peer->SetScaleY(expectedY);
            accessor_->setTransform1(peer_, &optMatrix);
            EXPECT_NEAR(target.scaleX, expectedX, FLT_PRECISION);
            EXPECT_NEAR(target.scaleY, expectedY, FLT_PRECISION);
        }
    }
    // with optional
    Opt_Matrix2D emptyMatrix = Converter::ArkValue<Opt_Matrix2D>();
    EXPECT_CALL(*renderingModel_, SetTransform(_, EXPECTED_FALSE)).Times(0);
    EXPECT_CALL(*renderingModel_, ResetTransform()).Times(1);
    accessor_->setTransform1(peer_, &emptyMatrix);
}

/**
 * @tc.name: setTransform1SkewTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setTransform1SkewTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setTransform1, nullptr);
    Ark_Matrix2D arkMatrix;
    auto peer = new Matrix2DPeer();
    arkMatrix = peer;
    auto optMatrix = Converter::ArkValue<Opt_Matrix2D>(arkMatrix);
    for (const auto& expectedX : NUMBER_TEST_PLAN) {
        for (const auto& expectedY : NUMBER_TEST_PLAN) {
            TransformParam target;
            EXPECT_CALL(*renderingModel_, SetTransform(_, EXPECTED_FALSE)).WillOnce(DoAll(SaveArg<0>(&target)));
            peer->SetRotateX(expectedX);
            peer->SetRotateY(expectedY);
            accessor_->setTransform1(peer_, &optMatrix);
            EXPECT_NEAR(target.skewX, expectedX, FLT_PRECISION);
            EXPECT_NEAR(target.skewY, expectedY, FLT_PRECISION);
        }
    }
}

/**
 * @tc.name: setTransform1TranslateTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setTransform1TranslateTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setTransform1, nullptr);
    Ark_Matrix2D arkMatrix;
    auto peer = new Matrix2DPeer();
    arkMatrix = peer;
    auto optMatrix = Converter::ArkValue<Opt_Matrix2D>(arkMatrix);
    for (const auto& expectedX : NUMBER_TEST_PLAN) {
        for (const auto& expectedY : NUMBER_TEST_PLAN) {
            TransformParam target;
            EXPECT_CALL(*renderingModel_, SetTransform(_, EXPECTED_FALSE)).WillOnce(DoAll(SaveArg<0>(&target)));
            peer->SetTranslateX(expectedX);
            peer->SetTranslateY(expectedY);
            accessor_->setTransform1(peer_, &optMatrix);
            EXPECT_NEAR(target.translateX, expectedX, FLT_PRECISION);
            EXPECT_NEAR(target.translateY, expectedY, FLT_PRECISION);
        }
    }
    // with density
    double density = DENSITY_2_50;
    ChangeDensity(density);
    for (const auto& expectedX : NUMBER_TEST_PLAN) {
        for (const auto& expectedY : NUMBER_TEST_PLAN) {
            TransformParam target;
            EXPECT_CALL(*renderingModel_, SetTransform(_, EXPECTED_FALSE)).WillOnce(DoAll(SaveArg<0>(&target)));
            peer->SetTranslateX(expectedX);
            peer->SetTranslateY(expectedY);
            accessor_->setTransform1(peer_, &optMatrix);
            EXPECT_NEAR(target.translateX, expectedX * density, FLT_PRECISION);
            EXPECT_NEAR(target.translateY, expectedY * density, FLT_PRECISION);
        }
    }
}

#ifdef PIXEL_MAP_SUPPORTED
/**
 * @tc.name: transferFromImageBitmapTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, DISABLEDD_transferFromImageBitmapTest, TestSize.Level1) {}
#else

/**
 * @tc.name: transferFromImageBitmapTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, DISABLED_transferFromImageBitmapTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->transferFromImageBitmap, nullptr);

    Ark_ImageBitmap arkBitmap;
    auto peer = new MockImageBitmapPeer();
    arkBitmap = peer;

    for (const auto& expectedW : SIZE_TEST_PLAN) {
        for (const auto& expectedH : SIZE_TEST_PLAN) {
            peer->SetWidth(expectedW);
            peer->SetHeight(expectedH);

            holder->SetUp();
            accessor_->transferFromImageBitmap(peer_, arkBitmap);
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
HWTEST_F(CanvasRendererAccessorTest, DISABLED_setFontStyleTest, TestSize.Level1)
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
HWTEST_F(CanvasRendererAccessorTest, DISABLED_setFontWeightTest, TestSize.Level1)
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
HWTEST_F(CanvasRendererAccessorTest, DISABLED_setFontSizePxTest, TestSize.Level1)
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
HWTEST_F(CanvasRendererAccessorTest, DISABLED_setFontSizeVpTest, TestSize.Level1)
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
HWTEST_F(CanvasRendererAccessorTest, DISABLED_setFontFamiliesTest, TestSize.Level1)
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
HWTEST_F(CanvasRendererAccessorTest, DISABLED_createLinearGradientTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->createLinearGradient, nullptr);
    auto valD = DEFAULT_DOUBLE_VALUE;
    for (const auto& expectedX : NUMBER_TEST_PLAN) {
        for (const auto& expectedY : NUMBER_TEST_PLAN) {
            auto x0 = Converter::ArkValue<Ark_Number>(expectedX);
            auto y0 = Converter::ArkValue<Ark_Number>(expectedY);
            auto x1 = Converter::ArkValue<Ark_Number>(valD);
            auto y1 = Converter::ArkValue<Ark_Number>(valD);
            auto peer = accessor_->createLinearGradient(peer_, &x0, &y0, &x1, &y1);
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
            auto peer = accessor_->createLinearGradient(peer_, &x0, &y0, &x1, &y1);
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
HWTEST_F(CanvasRendererAccessorTest, DISABLED_createRadialGradientXRTest, TestSize.Level1)
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
            auto peer = accessor_->createRadialGradient(peer_, &x0, &y0, &r0, &x1, &y1, &r1);
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
HWTEST_F(CanvasRendererAccessorTest, DISABLED_createRadialGradientYRTest, TestSize.Level1)
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
            auto peer = accessor_->createRadialGradient(peer_, &x0, &y0, &r0, &x1, &y1, &r1);
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
HWTEST_F(CanvasRendererAccessorTest, DISABLED_createRadialGradientXYTest, TestSize.Level1)
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
            auto peer = accessor_->createRadialGradient(peer_, &x0, &y0, &r0, &x1, &y1, &r1);
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
HWTEST_F(CanvasRendererAccessorTest, DISABLED_createConicGradientTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->createConicGradient, nullptr);
    auto valD = DEFAULT_DOUBLE_VALUE;
    auto valR = DEFAULT_SCALE_VALUE;
    for (const auto& expectedX : NUMBER_TEST_PLAN) {
        for (const auto& expectedY : NUMBER_TEST_PLAN) {
            auto x = Converter::ArkValue<Ark_Number>(expectedX);
            auto y = Converter::ArkValue<Ark_Number>(expectedY);
            auto startAngle = Converter::ArkValue<Ark_Number>(valR);
            auto peer = accessor_->createConicGradient(peer_, &startAngle, &x, &y);
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
            auto peer = accessor_->createConicGradient(peer_, &startAngle, &x, &y);
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
HWTEST_F(CanvasRendererAccessorTest, DISABLED_createImageData0Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->createImageData0, nullptr);
    for (const auto& actualW : NUMBER_TEST_PLAN) {
        for (const auto& actualH : NUMBER_TEST_PLAN) {
            auto sw = Converter::ArkValue<Ark_Number>(actualW);
            auto sh = Converter::ArkValue<Ark_Number>(actualH);
            auto imageData = accessor_->createImageData0(peer_, &sw, &sh);
            ASSERT_NE(imageData, nullptr);
            auto expectedW = static_cast<uint32_t>(std::abs(actualW + DIFF));
            auto expectedH = static_cast<uint32_t>(std::abs(actualH + DIFF));
            EXPECT_TRUE(LessOrEqualCustomPrecision(imageData->value.dirtyWidth, expectedW));
            EXPECT_TRUE(LessOrEqualCustomPrecision(imageData->value.dirtyHeight, expectedH));
        }
    }
}

/**
 * @tc.name: createImageData1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, DISABLED_createImageData1Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->createImageData1, nullptr);
    for (const auto& actualW : NUMBER_TEST_PLAN) {
        for (const auto& actualH : NUMBER_TEST_PLAN) {
            Ace::ImageData data{.dirtyWidth = actualW, .dirtyHeight = actualH};
            Ark_ImageData arkImage = ImageDataPeer::Create(data);
            auto imageData = accessor_->createImageData1(peer_, arkImage);
            ImageDataPeer::Destroy(arkImage);
            ASSERT_NE(imageData, nullptr);
            auto expectedW = static_cast<int32_t>(actualW);
            auto expectedH = static_cast<int32_t>(actualH);
            EXPECT_EQ(imageData->value.dirtyWidth, expectedW);
            EXPECT_EQ(imageData->value.dirtyHeight, expectedH);
        }
    }
}

/**
 * @tc.name: getImageDataTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, DISABLED_getImageDataTest, TestSize.Level1)
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
            auto imageData = accessor_->getImageData(peer_, &sx, &sy, &sw, &sh);
            ASSERT_NE(imageData, nullptr);
            ASSERT_TRUE(holder->isCalled);
            ASSERT_NE(holder->imageData, nullptr);
            auto expected = holder->imageData;
            EXPECT_EQ(imageData->value.dirtyWidth, expected->dirtyWidth);
            EXPECT_EQ(imageData->value.dirtyHeight, expected->dirtyHeight);
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
HWTEST_F(CanvasRendererAccessorTest, DISABLED_getPixelMapTest, TestSize.Level1)
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
HWTEST_F(CanvasRendererAccessorTest, DISABLED_putImageData0Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->putImageData0, nullptr);
    auto holder = TestHolder::GetInstance();
    auto valD = DEFAULT_DOUBLE_VALUE;
    auto width = valD;
    auto height = valD;
    auto length = width * height;
    std::vector<uint32_t> vector(length);
    Ace::ImageData data{.dirtyWidth = width, .dirtyHeight = height, .data = std::move(vector)};
    Ark_ImageData arkData = ImageDataPeer::Create(data);
    for (const auto& actualX : NUMBER_TEST_PLAN) {
        for (const auto& actualY : NUMBER_TEST_PLAN) {
            auto dx = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(actualX);
            auto dy = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(actualY);
            holder->SetUp();
            accessor_->putImageData0(peer_, arkData, &dx, &dy);
            ASSERT_TRUE(holder->isCalled);
            ASSERT_NE(holder->imageData, nullptr);
            Ace::ImageData& imageData = *holder->imageData;
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
    ImageDataPeer::Destroy(arkData);
    holder->TearDown();
}

/**
 * @tc.name: putImageData1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, DISABLED_putImageData1Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->putImageData1, nullptr);
    auto holder = TestHolder::GetInstance();
    auto valD = DEFAULT_DOUBLE_VALUE;
    auto width = valD;
    auto height = valD;
    auto length = width * height;
    std::vector<uint32_t> vector(length);
    Ace::ImageData data{.dirtyWidth = width, .dirtyHeight = height, .data = std::move(vector)};
    Ark_ImageData arkData = ImageDataPeer::Create(data);
    for (const auto& actualX : NUMBER_TEST_PLAN) {
        for (const auto& actualY : NUMBER_TEST_PLAN) {
            auto dx = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(actualX);
            auto dy = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(actualY);
            auto dirtyX = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(valD);
            auto dirtyY = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(valD);
            auto dirtyWidth = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(valD * valD);
            auto dirtyHeight = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(valD * valD);
            holder->SetUp();
            accessor_->putImageData1(peer_, arkData, &dx, &dy, &dirtyX, &dirtyY, &dirtyWidth, &dirtyHeight);
            ASSERT_TRUE(holder->isCalled);
            ASSERT_NE(holder->imageData, nullptr);
            Ace::ImageData& imageData = *holder->imageData;
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
    ImageDataPeer::Destroy(arkData);
    holder->TearDown();
}

/**
 * @tc.name: getLineDashOffsetTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, DISABLED_getLineDashOffsetTest, TestSize.Level1)
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
HWTEST_F(CanvasRendererAccessorTest, DISABLED_createPatternTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    ASSERT_NE(accessor_->createPattern, nullptr);
    holder->SetUp();
    Ark_ImageBitmap arkBitmap;
    auto bitmapPeer = new MockImageBitmapPeer();
    arkBitmap = bitmapPeer;
    auto repetition = Converter::ArkValue<Opt_String>("repeat");
    bitmapPeer->SetWidth(NUMBER_TEST_PLAN[0]);
    bitmapPeer->SetHeight(NUMBER_TEST_PLAN[1]);
    auto result = Converter::OptConvert<Ark_CanvasPattern>(accessor_->createPattern(peer_, arkBitmap, &repetition));
    ASSERT_NE(result, nullptr);
    auto patternPeer = result.value();
    ASSERT_NE(patternPeer, nullptr);

    EXPECT_TRUE(holder->isCalled);
    holder->TearDown();
}

/**
 * @tc.name: getTransformTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, DISABLED_getTransformTest, TestSize.Level1)
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
            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(matrixPeer->GetScaleX(), holder->param->scaleX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(matrixPeer->GetScaleY(), holder->param->scaleY));
        }
    }
    holder->TearDown();
}

/**
 * @tc.name: setImageSmoothingQualityTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, DISABLED_setImageSmoothingQualityTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    ASSERT_NE(accessor_->setImageSmoothingQuality, nullptr);
    for (const auto& [actual, expected] : IMAGE_SMOOTHING_TEST_PLAN) {
        holder->SetUp();
        accessor_->setImageSmoothingQuality(peer_, &actual);
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
HWTEST_F(CanvasRendererAccessorTest, DISABLED_setLineCapTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    ASSERT_NE(accessor_->setLineCap, nullptr);
    for (const auto& [actual, expected] : LINE_CAP_TEST_PLAN) {
        holder->SetUp();
        accessor_->setLineCap(peer_, &actual);
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
HWTEST_F(CanvasRendererAccessorTest, DISABLED_setLineJoinTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    ASSERT_NE(accessor_->setLineJoin, nullptr);
    for (const auto& [actual, expected] : LINE_JOIN_TEST_PLAN) {
        holder->SetUp();
        accessor_->setLineJoin(peer_, &actual);
        EXPECT_TRUE(holder->isCalled);
        EXPECT_EQ(holder->lineJoin, expected);
    }
    holder->TearDown();
}

/**
 * @tc.name: setPixelMapTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, DISABLED_setPixelMapTest, TestSize.Level1)
{
#ifdef PIXEL_MAP_SUPPORTED
    auto holder = TestHolder::GetInstance();
    ASSERT_NE(accessor_->setPixelMap, nullptr);
    Ark_PixelMap arkPixelMap;
    auto peer = new PixelMapPeer();
    arkPixelMap = peer;
    auto optPixelMap = Converter::ArkValue<Opt_PixelMap>(arkPixelMap);
    for (const auto& width : NUMBER_TEST_PLAN) {
        for (const auto& height : NUMBER_TEST_PLAN) {
            auto ptr = AceType::MakeRefPtr<MockPixelMap>();
            uint32_t expectedWidth = std::round(width);
            uint32_t expectedHeight = std::round(height);
            ptr->width = expectedWidth;
            ptr->height = expectedHeight;
            peer->pixelMap = ptr;
            holder->SetUp();
            accessor_->setPixelMap(peer_, &optPixelMap);
            EXPECT_TRUE(holder->isCalled);
            EXPECT_EQ(holder->pixelMap->GetWidth(), expectedWidth);
            EXPECT_EQ(holder->pixelMap->GetHeight(), expectedHeight);
        }
    }
    holder->TearDown();
#else
    ASSERT_NE(accessor_->setPixelMap, nullptr);
    accessor_->setPixelMap(peer_, nullptr);
    EXPECT_TRUE(true);
#endif
}

/**
 * @tc.name: clip0Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, DISABLED_clip0Test, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    ASSERT_NE(accessor_->clip0, nullptr);
    for (const auto& [actual, expected] : FILL_RULE_TEST_PLAN) {
        holder->SetUp();
        accessor_->clip0(peer_, &actual);
        auto rule = *holder->fillRule;
        EXPECT_TRUE(holder->isCalled);
        EXPECT_TRUE(holder->isCalled2);
        EXPECT_EQ(rule, expected);
    }
    holder->TearDown();
}

/**
 * @tc.name: clip1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, DISABLED_clip1Test, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    ASSERT_NE(accessor_->clip1, nullptr);
    auto peerImpl = Referenced::MakeRefPtr<Path2DPeer>();
    Ark_Path2D arkPath = Referenced::RawPtr(peerImpl);
    for (const auto& [arkRule, expected] : FILL_RULE_TEST_PLAN) {
        for (const auto& actual : PATH2D_TEST_PLAN) {
            holder->SetUp();
            auto path = AceType::MakeRefPtr<CanvasPath2D>();
            auto cmd = std::get<0>(actual);
            auto x = std::get<1>(actual);
            auto y = std::get<2>(actual);
            if (cmd == PathCmd::MOVE_TO) {
                path->MoveTo(x, y);
            } else {
                path->LineTo(x, y);
            }
            peerImpl->SetCanvasPath2d(path);
            accessor_->clip1(peer_, arkPath, &arkRule);
            auto result = holder->path->GetCaches();
            auto rcmd = result[0].first;
            auto rx = result[0].second.para1;
            auto ry = result[0].second.para2;
            auto rule = *holder->fillRule;
            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(holder->isCalled2);
            EXPECT_EQ(rule, expected);
            EXPECT_EQ(rcmd, cmd);
            EXPECT_TRUE(LessOrEqualCustomPrecision(rx, x));
            EXPECT_TRUE(LessOrEqualCustomPrecision(ry, y));
        }
    }
    holder->TearDown();
}

/**
 * @tc.name: fill0Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, DISABLED_fill0Test, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    ASSERT_NE(accessor_->fill0, nullptr);
    for (const auto& [actual, expected] : FILL_RULE_TEST_PLAN) {
        holder->SetUp();
        accessor_->fill0(peer_, &actual);
        auto rule = *holder->fillRule;
        EXPECT_TRUE(holder->isCalled);
        EXPECT_TRUE(holder->isCalled2);
        EXPECT_EQ(rule, expected);
    }
    holder->TearDown();
}

/**
 * @tc.name: fill1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, DISABLED_fill1Test, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    ASSERT_NE(accessor_->fill1, nullptr);
    auto peerImpl = Referenced::MakeRefPtr<Path2DPeer>();
    Ark_Path2D arkPath = Referenced::RawPtr(peerImpl);
    for (const auto& [arkRule, expected] : FILL_RULE_TEST_PLAN) {
        for (const auto& actual : PATH2D_TEST_PLAN) {
            holder->SetUp();
            auto path = AceType::MakeRefPtr<CanvasPath2D>();
            auto cmd = std::get<0>(actual);
            auto x = std::get<1>(actual);
            auto y = std::get<2>(actual);
            if (cmd == PathCmd::MOVE_TO) {
                path->MoveTo(x, y);
            } else {
                path->LineTo(x, y);
            }
            peerImpl->SetCanvasPath2d(path);
            accessor_->fill1(peer_, arkPath, &arkRule);
            auto result = holder->path->GetCaches();
            auto rcmd = result[0].first;
            auto rx = result[0].second.para1;
            auto ry = result[0].second.para2;
            auto rule = *holder->fillRule;
            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(holder->isCalled2);
            EXPECT_EQ(rule, expected);
            EXPECT_EQ(rcmd, cmd);
            EXPECT_TRUE(LessOrEqualCustomPrecision(rx, x));
            EXPECT_TRUE(LessOrEqualCustomPrecision(ry, y));
        }
    }
    holder->TearDown();
}

/**
 * @tc.name: setDirectionTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, DISABLED_setDirectionTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    ASSERT_NE(accessor_->setDirection, nullptr);
    for (const auto& [actual, expected] : DIRECTION_TEST_PLAN) {
        holder->SetUp();
        accessor_->setDirection(peer_, &actual);
        EXPECT_TRUE(holder->isCalled);
        EXPECT_EQ(*holder->direction, expected);
    }
    holder->TearDown();
}

/**
 * @tc.name: setTextAlignTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, DISABLED_setTextAlignTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    ASSERT_NE(accessor_->setTextAlign, nullptr);
    for (const auto& [actual, expected] : TEXT_ALIGN_TEST_PLAN) {
        holder->SetUp();
        accessor_->setTextAlign(peer_, &actual);
        EXPECT_TRUE(holder->isCalled);
        EXPECT_EQ(*holder->textAlign, expected);
    }
    holder->TearDown();
}

/**
 * @tc.name: setTextBaselineTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, DISABLED_setTextBaselineTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    ASSERT_NE(accessor_->setTextBaseline, nullptr);
    for (const auto& [actual, expected] : TEXT_BASE_LINE_TEST_PLAN) {
        holder->SetUp();
        accessor_->setTextBaseline(peer_, &actual);
        EXPECT_TRUE(holder->isCalled);
        EXPECT_EQ(*holder->baseline, expected);
    }
    holder->TearDown();
}
} // namespace OHOS::Ace::NG
