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
const double DEFAULT_DOUBLE_VALUE = 2.0;
const double DEFAULT_SCALE_VALUE = 1.0;
const std::string DEFAULT_STRING_VALUE = "text";
const std::string EMPTY_STRING = "";
constexpr double MATH_2_PI = 2 * M_PI;
const Opt_Boolean OPT_BOOLEAN_FALSE = Converter::ArkValue<Opt_Boolean>(false);
const std::string INVALID_STRING = "invalid";
const std::string REPEAT_STRING = "repeat";
const double FLT_PRECISION = 0.001;
const double DEFAULT_DENSITY = 1.0;
const double DENSITY_1_25 = 1.25;
const double DENSITY_2_50 = 2.50;
// test plan
std::vector<std::tuple<Ark_Float64, double>> ARK_FLOAT64_TEST_PLAN = {
    { Converter::ArkValue<Ark_Float64>(100), 100 },
    { Converter::ArkValue<Ark_Float64>(0), 0 },
    { Converter::ArkValue<Ark_Float64>(-100), -100 },
    { Converter::ArkValue<Ark_Float64>(12.34), 12.34 },
    { Converter::ArkValue<Ark_Float64>(-56.73), -56.73 },
};
std::vector<std::tuple<Ark_Float64, double>> ARK_FLOAT64_LINE_WIDTH_TEST_PLAN = {
    { Converter::ArkValue<Ark_Float64>(100), 100 },
    { Converter::ArkValue<Ark_Float64>(0), 1 },
    { Converter::ArkValue<Ark_Float64>(-100), 1 },
    { Converter::ArkValue<Ark_Float64>(12.34), 12.34 },
};
std::vector<std::tuple<Ark_Float64, double>> ARK_FLOAT64_MITER_LIMIT_TEST_PLAN = {
    { Converter::ArkValue<Ark_Float64>(100), 100 },
    { Converter::ArkValue<Ark_Float64>(0), 10 },
    { Converter::ArkValue<Ark_Float64>(-100), 10 },
    { Converter::ArkValue<Ark_Float64>(12.34), 12.34 },
};
std::vector<std::tuple<Ark_Float64, double>> ARK_FLOAT64_SHADOW_BLUR_TEST_PLAN = {
    { Converter::ArkValue<Ark_Float64>(100), 100 },
    { Converter::ArkValue<Ark_Float64>(0), 0 },
    { Converter::ArkValue<Ark_Float64>(-100), 0 },
    { Converter::ArkValue<Ark_Float64>(12.34), 12.34 },
};
std::vector<std::tuple<Ark_Float64, double>> ARK_FLOAT64_ALPHA_TEST_PLAN = {
    { Converter::ArkValue<Ark_Float64>(100), 100 },
    { Converter::ArkValue<Ark_Float64>(0), 0 },
    { Converter::ArkValue<Ark_Float64>(-0.54), 0.0 },
    { Converter::ArkValue<Ark_Float64>(0.98), 0.98 },
    { Converter::ArkValue<Ark_Float64>(1.00), 1.00 },
    { Converter::ArkValue<Ark_Float64>(1.01), 1.0 },
    { Converter::ArkValue<Ark_Float64>(-100), 0.0 },
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
std::vector<std::tuple<Opt_Float64, std::optional<double>>> OPT_MAX_WIDTH_TEST_PLAN = {
    { Converter::ArkValue<Opt_Float64>(100), 100 },
    { Converter::ArkValue<Opt_Float64>(0), 0 },
    { Converter::ArkValue<Opt_Float64>(-100), -100 },
    { Converter::ArkValue<Opt_Float64>(12.34), 12.34 },
    { Converter::ArkValue<Opt_Float64>(-56.73), -56.73 },
    { Converter::ArkValue<Opt_Float64>(Ark_Empty()), FLT_MAX },
};
std::vector<std::tuple<Ark_String, CompositeOperation, std::string>> ARK_COMPOSITE_TEST_PLAN = {
    { Converter::ArkValue<Ark_String>("source-over"), CompositeOperation::SOURCE_OVER, "source-over" },
    { Converter::ArkValue<Ark_String>("source-atop"), CompositeOperation::SOURCE_ATOP, "source-atop" },
    { Converter::ArkValue<Ark_String>("source-in"), CompositeOperation::SOURCE_IN, "source-in" },
    { Converter::ArkValue<Ark_String>("source-out"), CompositeOperation::SOURCE_OUT, "source-out" },
    { Converter::ArkValue<Ark_String>("destination-over"), CompositeOperation::DESTINATION_OVER, "destination-over" },
    { Converter::ArkValue<Ark_String>("destination-atop"), CompositeOperation::DESTINATION_ATOP, "destination-atop" },
    { Converter::ArkValue<Ark_String>("destination-in"), CompositeOperation::DESTINATION_IN, "destination-in" },
    { Converter::ArkValue<Ark_String>("destination-out"), CompositeOperation::DESTINATION_OUT, "destination-out" },
    { Converter::ArkValue<Ark_String>("lighter"), CompositeOperation::LIGHTER, "lighter" },
    { Converter::ArkValue<Ark_String>("copy"), CompositeOperation::COPY, "copy" },
    { Converter::ArkValue<Ark_String>("xor"), CompositeOperation::XOR, "xor" },
    { Converter::ArkValue<Ark_String>(""), CompositeOperation::SOURCE_OVER, "source-over" },
    { Converter::ArkValue<Ark_String>("unknown value"), CompositeOperation::SOURCE_OVER, "source-over" },
};
std::vector<std::tuple<Ark_String, Color, std::string>> ARK_STRING_COLOR_TEST_PLAN = {
    { Converter::ArkValue<Ark_String>("#ff0000ff"), Color(0xff0000ff), "#ff0000ff" },
    { Converter::ArkValue<Ark_String>("#00000000"), Color(0x00000000), "#00000000" },
    { Converter::ArkValue<Ark_String>("#80ffffff"), Color(0x80ffffff), "#80ffffff" },
    { Converter::ArkValue<Ark_String>(""), Color(0x00000000), "#00000000" },
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
std::vector<double> BUFFER_TEST_PLAN = {
    1, 0, -2, 4, 5,
};
std::vector<int32_t> SIZE_TEST_PLAN = {
    -100, -10, 0, 10, 12, 56, 100
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
    { "0px", Dimension(0) },
    { "14px", Dimension(14) },
    { "-56px", Dimension(-56) },
    { "abcpx", Dimension(0) },
    { "px200", Dimension(0) },
    { "", Dimension(0) },
    { "invalid", Dimension(0) },
};
std::vector<std::pair<std::string, Dimension>> FONT_SIZE_VP_TEST_PLAN = {
    { "10vp", Dimension(10, DimensionUnit::VP) },
    { "0vp", Dimension(0, DimensionUnit::VP) },
    { "-10vp", Dimension(-10, DimensionUnit::VP) },
    { "", Dimension(0) },
    { "invalid", Dimension(0) },
};
std::vector<std::pair<std::string, std::vector<std::string>>>  FONT_FAMILIES_TEST_PLAN = {
    { "sans-serif", { "sans-serif" } },
    { "monospace", { "monospace" } },
    { "serif", { "serif" } },
    { "", {} },
    { "invalid", {} },
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
    MOCK_METHOD(int32_t, GetWidth, (), (const override));
    MOCK_METHOD(int32_t, GetHeight, (), (const override));
    MOCK_METHOD(uint32_t, WritePixels, (const WritePixelsOptions&), (override));
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
    MOCK_METHOD(void, SetLetterSpacing, (const Dimension&), (override));
#ifdef PIXEL_MAP_SUPPORTED
    MOCK_METHOD(void, TransferFromImageBitmap, (const RefPtr<AceType>&), (override));
#else
    MOCK_METHOD(void, TransferFromImageBitmap, (const std::shared_ptr<Ace::ImageData>&), (override));
#endif
    MOCK_METHOD(void, SetFontStyle, (const Ace::FontStyle&), (override));
    MOCK_METHOD(void, SetFontWeight, (const FontWeight&), (override));
    MOCK_METHOD(void, SetFontSize, (const Dimension&), (override));
    MOCK_METHOD(void, SetFontFamilies, (const std::vector<std::string>&), (override));
    MOCK_METHOD(void, SetSmoothingQuality, (const std::string&), (override));
    MOCK_METHOD(void, SetLineCap, (const LineCapStyle&), (override));
    MOCK_METHOD(void, SetLineJoin, (const LineJoinStyle&), (override));
    MOCK_METHOD(void, SetTextDirection, (const TextDirection&), (override));
    MOCK_METHOD(void, SetTextAlign, (const TextAlign&), (override));
    MOCK_METHOD(void, SetTextBaseline, (const TextBaseline&), (override));
    MOCK_METHOD(void, SetClipRuleForPath, (const CanvasFillRule&), (override));
    MOCK_METHOD(void, SetClipRuleForPath2D, (const CanvasFillRule&, const RefPtr<CanvasPath2D>&), (override));
    MOCK_METHOD(void, SetFillRuleForPath, (const CanvasFillRule&), (override));
    MOCK_METHOD(void, SetFillRuleForPath2D, (const CanvasFillRule&, const RefPtr<CanvasPath2D>&), (override));
    MOCK_METHOD(void, GetImageDataModel, (const ImageSize&, uint8_t*), (override));
    MOCK_METHOD(void, PutImageData, (const Ace::ImageData&), (override));
    MOCK_METHOD(void, SetTransform, (std::shared_ptr<Ace::Pattern>, const TransformParam&), (override));
    MOCK_METHOD(TransformParam, GetTransform, (), (override));
    MOCK_METHOD(void, DrawPixelMap, (const Ace::ImageInfo&), (override));
    MOCK_METHOD(RefPtr<Ace::PixelMap>, GetPixelMap, (const ImageSize&), (override));
    MOCK_METHOD(void, DrawSvgImage, (const Ace::ImageInfo&), (override));
    MOCK_METHOD(void, DrawImage, (const ImageInfo&), (override));
    MOCK_METHOD(std::vector<double>, GetLineDash, (), (override));
    MOCK_METHOD(TextMetrics, GetMeasureTextMetrics, (const PaintState&, const std::string&), (override));
    MOCK_METHOD(void, SetFillColor, (const Color&, bool), (override));
    MOCK_METHOD(void, SetFillGradient, (const std::shared_ptr<Ace::Gradient>&), (override));
    MOCK_METHOD(void, SetFillPattern, (const std::shared_ptr<Ace::Pattern>&), (override));
    MOCK_METHOD(void, SetStrokeColor, (const Color&, bool), (override));
    MOCK_METHOD(void, SetStrokeGradient, (const std::shared_ptr<Ace::Gradient>&), (override));
    MOCK_METHOD(void, SetStrokePattern, (const std::shared_ptr<Ace::Pattern>&), (override));
};
struct MockImageBitmapPeer : public ImageBitmapPeer {
public:
    MockImageBitmapPeer() = default;
    ~MockImageBitmapPeer() override = default;
    MOCK_METHOD(RefPtr<Ace::PixelMap>, GetPixelMap, (), (const));
    MOCK_METHOD(bool, IsSvg, (), ());
    MOCK_METHOD(RefPtr<NG::SvgDomBase>, GetSvgDom, (), ());
    MOCK_METHOD(Ace::ImageFit, GetImageFit, (), ());
};
struct MockImageBitmapPeerPattern : public ImageBitmapPeer {
public:
    MockImageBitmapPeerPattern() = default;
    ~MockImageBitmapPeerPattern() override = default;
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
        renderingModel_ = AceType::MakeRefPtr<NiceMock<MockCanvasRenderingContext2DModel>>();
        reinterpret_cast<GeneratedModifier::CanvasRendererPeerImpl*>(peer_)->SetRenderingContext2DModel(
            renderingModel_);
    }

    void TearDown() override
    {
        AccessorTestBaseParent::TearDown();
        auto pipelineContext =
            AceType::DynamicCast<NG::MockPipelineContext>(NG::MockPipelineContext::GetCurrentContext());
        pipelineContext->SetDensity(DEFAULT_DENSITY);
    }

    void ChangeDensity(const double density)
    {
        auto pipelineContext =
            AceType::DynamicCast<NG::MockPipelineContext>(NG::MockPipelineContext::GetCurrentContext());
        pipelineContext->SetDensity(density);
        // Re-create peer for density to have effect
        finalyzer_(peer_);
        peer_ = accessor_->construct();
        reinterpret_cast<GeneratedModifier::CanvasRendererPeerImpl*>(peer_)->SetRenderingContext2DModel(
            renderingModel_);
    }

    RefPtr<MockCanvasRenderingContext2DModel> renderingModel_ = nullptr;
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
 * @tc.name: strokeTestEmpty
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, strokeTestEmpty, TestSize.Level1)
{
    ASSERT_NE(accessor_->stroke, nullptr);
    EXPECT_CALL(*renderingModel_, SetStrokeRuleForPath(CanvasFillRule::NONZERO)).Times(EXPECTED_NUMBER_OF_CALLS);
    auto path = Converter::ArkValue<Opt_Path2D>();
    accessor_->stroke(peer_, &path);
    accessor_->stroke(peer_, &path);
    accessor_->stroke(peer_, &path);
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
        const auto segments = Converter::ArkValue<Array_Float64>(actual, Converter::FC);
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
    auto arkD = Converter::ArkValue<Ark_Float64>(DEFAULT_DOUBLE_VALUE);
    for (const auto& [x, expectedX] : ARK_FLOAT64_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_FLOAT64_TEST_PLAN) {
            auto rect = Ace::Rect(expectedX, expectedY, DEFAULT_DOUBLE_VALUE, DEFAULT_DOUBLE_VALUE);
            EXPECT_CALL(*renderingModel_, ClearRect(rect)).Times(1);
            accessor_->clearRect(peer_, x, y, arkD, arkD);
        }
    }
    // with density
    double density = DENSITY_2_50;
    ChangeDensity(density);
    for (const auto& [w, expectedW] : ARK_FLOAT64_TEST_PLAN) {
        for (const auto& [h, expectedH] : ARK_FLOAT64_TEST_PLAN) {
            auto rect = Ace::Rect(DEFAULT_DOUBLE_VALUE, DEFAULT_DOUBLE_VALUE, expectedW, expectedH);
            EXPECT_CALL(*renderingModel_, ClearRect(rect * density)).Times(1);
            accessor_->clearRect(peer_, arkD, arkD, w, h);
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
    auto arkD = Converter::ArkValue<Ark_Float64>(DEFAULT_DOUBLE_VALUE);
    for (const auto& [x, expectedX] : ARK_FLOAT64_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_FLOAT64_TEST_PLAN) {
            auto rect = Ace::Rect(expectedX, expectedY, DEFAULT_DOUBLE_VALUE, DEFAULT_DOUBLE_VALUE);
            EXPECT_CALL(*renderingModel_, FillRect(rect)).Times(1);
            accessor_->fillRect(peer_, x, y, arkD, arkD);
        }
    }
    // with density
    double density = DENSITY_1_25;
    ChangeDensity(density);
    for (const auto& [w, expectedW] : ARK_FLOAT64_TEST_PLAN) {
        for (const auto& [h, expectedH] : ARK_FLOAT64_TEST_PLAN) {
            auto rect = Ace::Rect(DEFAULT_DOUBLE_VALUE, DEFAULT_DOUBLE_VALUE, expectedW, expectedH);
            EXPECT_CALL(*renderingModel_, FillRect(rect * density)).Times(1);
            accessor_->fillRect(peer_, arkD, arkD, w, h);
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
    auto arkD = Converter::ArkValue<Ark_Float64>(DEFAULT_DOUBLE_VALUE);
    for (const auto& [x, expectedX] : ARK_FLOAT64_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_FLOAT64_TEST_PLAN) {
            auto rect = Ace::Rect(expectedX, expectedY, DEFAULT_DOUBLE_VALUE, DEFAULT_DOUBLE_VALUE);
            EXPECT_CALL(*renderingModel_, StrokeRect(rect)).Times(1);
            accessor_->strokeRect(peer_, x, y, arkD, arkD);
        }
    }
    // with density
    double density = DENSITY_2_50;
    ChangeDensity(density);
    for (const auto& [w, expectedW] : ARK_FLOAT64_TEST_PLAN) {
        for (const auto& [h, expectedH] : ARK_FLOAT64_TEST_PLAN) {
            auto rect = Ace::Rect(DEFAULT_DOUBLE_VALUE, DEFAULT_DOUBLE_VALUE, expectedW, expectedH);
            EXPECT_CALL(*renderingModel_, StrokeRect(rect * density)).Times(1);
            accessor_->strokeRect(peer_, arkD, arkD, w, h);
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
    for (const auto& [actual, expected] : ARK_FLOAT64_TEST_PLAN) {
        double target;
        EXPECT_CALL(*renderingModel_, CanvasRendererRotate(_)).WillOnce(DoAll(SaveArg<0>(&target)));
        accessor_->rotate(peer_, actual);
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
    for (const auto& [x, expectedX] : ARK_FLOAT64_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_FLOAT64_TEST_PLAN) {
            double targetX, targetY;
            EXPECT_CALL(*renderingModel_, CanvasRendererScale(_, _))
                .WillOnce(DoAll(SaveArg<0>(&targetX), SaveArg<1>(&targetY)));
            accessor_->scale(peer_, x, y);
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
    for (const auto& [x, expectedX] : ARK_FLOAT64_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_FLOAT64_TEST_PLAN) {
            double targetX, targetY;
            EXPECT_CALL(*renderingModel_, Translate(_, _)).WillOnce(DoAll(SaveArg<0>(&targetX), SaveArg<1>(&targetY)));
            accessor_->translate(peer_, x, y);
            EXPECT_NEAR(targetX, expectedX, FLT_PRECISION);
            EXPECT_NEAR(targetY, expectedY, FLT_PRECISION);
        }
    }
    // with density
    double density = DENSITY_1_25;
    ChangeDensity(density);
    for (const auto& [x, expectedX] : ARK_FLOAT64_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_FLOAT64_TEST_PLAN) {
            double targetX, targetY;
            EXPECT_CALL(*renderingModel_, Translate(_, _)).WillOnce(DoAll(SaveArg<0>(&targetX), SaveArg<1>(&targetY)));
            accessor_->translate(peer_, x, y);
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
 * @tc.name: globalAlphaSetterGetterTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, globalAlphaSetterGetterTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setGlobalAlpha, nullptr);
    for (const auto& [actual, expected] : ARK_FLOAT64_ALPHA_TEST_PLAN) {
        double target;
        EXPECT_CALL(*renderingModel_, SetGlobalAlpha(_)).WillOnce(DoAll(SaveArg<0>(&target)));
        accessor_->setGlobalAlpha(peer_, actual);
        auto globalAlpha = accessor_->getGlobalAlpha(peer_);
        auto alpha = Converter::Convert<double>(globalAlpha);
        EXPECT_EQ(alpha, expected);
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
    auto arkD = Converter::ArkValue<Ark_Float64>(DEFAULT_DOUBLE_VALUE);
    auto arkOpt = Converter::ArkValue<Opt_Float64>(arkD);
    for (const auto& [actual, expected] : ARK_STRING_TEST_PLAN) {
        FillTextInfo target;
        EXPECT_CALL(*renderingModel_, SetFillText(_, _)).WillOnce(DoAll(SaveArg<1>(&target)));
        accessor_->fillText(peer_, &actual, arkD, arkD, &arkOpt);
        EXPECT_EQ(target.text, expected);
    }
    for (const auto& [x, expectedX] : ARK_FLOAT64_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_FLOAT64_TEST_PLAN) {
            FillTextInfo target;
            EXPECT_CALL(*renderingModel_, SetFillText(_, _)).WillOnce(DoAll(SaveArg<1>(&target)));
            accessor_->fillText(peer_, &arkT, x, y, &arkOpt);
            EXPECT_NEAR(target.x, expectedX, FLT_PRECISION);
            EXPECT_NEAR(target.y, expectedY, FLT_PRECISION);
        }
    }
    for (const auto& [actual, expected] : OPT_MAX_WIDTH_TEST_PLAN) {
        FillTextInfo target;
        if (expected && expected.value() < 0) {
            EXPECT_CALL(*renderingModel_, SetFillText(_, _)).Times(0);
            accessor_->fillText(peer_, &arkT, arkD, arkD, &actual);
        } else {
            EXPECT_CALL(*renderingModel_, SetFillText(_, _)).WillOnce(DoAll(SaveArg<1>(&target)));
            accessor_->fillText(peer_, &arkT, arkD, arkD, &actual);
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
    auto arkD = Converter::ArkValue<Ark_Float64>(DEFAULT_DOUBLE_VALUE);
    auto arkOpt = Converter::ArkValue<Opt_Float64>(arkD);
    for (const auto& [actual, expected] : ARK_STRING_TEST_PLAN) {
        FillTextInfo target;
        EXPECT_CALL(*renderingModel_, SetStrokeText(_, _)).WillOnce(DoAll(SaveArg<1>(&target)));
        accessor_->strokeText(peer_, &actual, arkD, arkD, &arkOpt);
        EXPECT_EQ(target.text, expected);
    }
    for (const auto& [x, expectedX] : ARK_FLOAT64_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_FLOAT64_TEST_PLAN) {
            FillTextInfo target;
            EXPECT_CALL(*renderingModel_, SetStrokeText(_, _)).WillOnce(DoAll(SaveArg<1>(&target)));
            accessor_->strokeText(peer_, &arkT, x, y, &arkOpt);
            EXPECT_NEAR(target.x, expectedX, FLT_PRECISION);
            EXPECT_NEAR(target.y, expectedY, FLT_PRECISION);
        }
    }
    for (const auto& [actual, expected] : OPT_MAX_WIDTH_TEST_PLAN) {
        FillTextInfo target;
        if (expected && expected.value() < 0) {
            EXPECT_CALL(*renderingModel_, SetStrokeText(_, _)).Times(0);
            accessor_->strokeText(peer_, &arkT, arkD, arkD, &actual);
        } else {
            EXPECT_CALL(*renderingModel_, SetStrokeText(_, _)).WillOnce(DoAll(SaveArg<1>(&target)));
            accessor_->strokeText(peer_, &arkT, arkD, arkD, &actual);
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
HWTEST_F(CanvasRendererAccessorTest, DISABLED_setTransform0Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->setTransform0, nullptr);
    auto arkD = Converter::ArkValue<Ark_Float64>(DEFAULT_DOUBLE_VALUE);
    auto arkS = Converter::ArkValue<Ark_Float64>(DEFAULT_SCALE_VALUE);
    for (const auto& [x, expectedX] : ARK_FLOAT64_ALPHA_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_FLOAT64_ALPHA_TEST_PLAN) {
            TransformParam target;
            EXPECT_CALL(*renderingModel_, SetTransform(_, EXPECTED_TRUE)).WillOnce(DoAll(SaveArg<0>(&target)));
            accessor_->setTransform0(peer_, x, arkD, arkD, y, arkD, arkD);
            EXPECT_NEAR(target.scaleX, expectedX, FLT_PRECISION);
            EXPECT_NEAR(target.scaleY, expectedY, FLT_PRECISION);
        }
    }
    for (const auto& [x, expectedX] : ARK_FLOAT64_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_FLOAT64_TEST_PLAN) {
            TransformParam target;
            EXPECT_CALL(*renderingModel_, SetTransform(_, EXPECTED_TRUE)).WillOnce(DoAll(SaveArg<0>(&target)));
            accessor_->setTransform0(peer_, arkS, x, y, arkS, arkD, arkD);
            EXPECT_NEAR(target.skewX, expectedX, FLT_PRECISION);
            EXPECT_NEAR(target.skewY, expectedY, FLT_PRECISION);
        }
    }
    for (const auto& [x, expectedX] : ARK_FLOAT64_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_FLOAT64_TEST_PLAN) {
            TransformParam target;
            EXPECT_CALL(*renderingModel_, SetTransform(_, EXPECTED_TRUE)).WillOnce(DoAll(SaveArg<0>(&target)));
            accessor_->setTransform0(peer_, arkS, arkD, arkD, arkS, x, y);
            EXPECT_NEAR(target.translateX, expectedX, FLT_PRECISION);
            EXPECT_NEAR(target.translateY, expectedY, FLT_PRECISION);
        }
    }
    // with density
    double density = DENSITY_1_25;
    ChangeDensity(density);
    for (const auto& [x, expectedX] : ARK_FLOAT64_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_FLOAT64_TEST_PLAN) {
            TransformParam target;
            EXPECT_CALL(*renderingModel_, SetTransform(_, EXPECTED_TRUE)).WillOnce(DoAll(SaveArg<0>(&target)));
            accessor_->setTransform0(peer_, arkS, arkD, arkD, arkS, x, y);
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
    auto arkD = Converter::ArkValue<Ark_Float64>(DEFAULT_DOUBLE_VALUE);
    auto arkS = Converter::ArkValue<Ark_Float64>(DEFAULT_SCALE_VALUE);
    for (const auto& [x, expectedX] : ARK_FLOAT64_ALPHA_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_FLOAT64_ALPHA_TEST_PLAN) {
            TransformParam target;
            EXPECT_CALL(*renderingModel_, Transform(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            accessor_->transform(peer_, x, arkD, arkD, y, arkD, arkD);
            EXPECT_NEAR(target.scaleX, expectedX, FLT_PRECISION);
            EXPECT_NEAR(target.scaleY, expectedY, FLT_PRECISION);
        }
    }
    for (const auto& [x, expectedX] : ARK_FLOAT64_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_FLOAT64_TEST_PLAN) {
            TransformParam target;
            EXPECT_CALL(*renderingModel_, Transform(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            accessor_->transform(peer_, arkS, x, y, arkS, arkD, arkD);
            EXPECT_NEAR(target.skewX, expectedX, FLT_PRECISION);
            EXPECT_NEAR(target.skewY, expectedY, FLT_PRECISION);
        }
    }
    for (const auto& [x, expectedX] : ARK_FLOAT64_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_FLOAT64_TEST_PLAN) {
            TransformParam target;
            EXPECT_CALL(*renderingModel_, Transform(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            accessor_->transform(peer_, arkS, arkD, arkD, arkS, x, y);
            EXPECT_NEAR(target.translateX, expectedX, FLT_PRECISION);
            EXPECT_NEAR(target.translateY, expectedY, FLT_PRECISION);
        }
    }
    // with density
    double density = DENSITY_2_50;
    ChangeDensity(density);
    for (const auto& [x, expectedX] : ARK_FLOAT64_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_FLOAT64_TEST_PLAN) {
            TransformParam target;
            EXPECT_CALL(*renderingModel_, Transform(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            accessor_->transform(peer_, arkS, arkD, arkD, arkS, x, y);
            EXPECT_NEAR(target.translateX, expectedX * density, FLT_PRECISION);
            EXPECT_NEAR(target.translateY, expectedY * density, FLT_PRECISION);
        }
    }
}

/**
 * @tc.name: globalCompositeOperationSetterGetterTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, globalCompositeOperationSetterGetterTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setGlobalCompositeOperation, nullptr);
    for (const auto& [actual, expected, expectedStr] : ARK_COMPOSITE_TEST_PLAN) {
        EXPECT_CALL(*renderingModel_, SetCompositeType(expected)).Times(1);
        accessor_->setGlobalCompositeOperation(peer_, &actual);
        auto globalCompositeOperation = accessor_->getGlobalCompositeOperation(peer_);
        auto compositeStr = Converter::Convert<std::string>(globalCompositeOperation);
        EXPECT_EQ(alpha, expectedStr);
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
 * @tc.name: imageSmoothingEnabledSetterGetterTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, imageSmoothingEnabledSetterGetterTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setImageSmoothingEnabled, nullptr);
    for (const auto& [actual, expected] : ARK_BOOL_TEST_PLAN) {
        EXPECT_CALL(*renderingModel_, SetSmoothingEnabled(expected)).Times(1);
        accessor_->setImageSmoothingEnabled(peer_, actual);
        auto imageSmoothingEnabled = accessor_->getImageSmoothingEnabled(peer_);
        auto enabled = Converter::Convert<bool>(imageSmoothingEnabled);
        EXPECT_EQ(enabled, expected);
    }
}

/**
 * @tc.name: lineDashOffsetSetterGetterTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, lineDashOffsetSetterGetterTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setLineDashOffset, nullptr);
    for (const auto& [actual, expected] : ARK_FLOAT64_TEST_PLAN) {
        double target;
        EXPECT_CALL(*renderingModel_, SetLineDashOffset(_)).WillOnce(DoAll(SaveArg<0>(&target)));
        accessor_->setLineDashOffset(peer_, actual);
        EXPECT_NEAR(target, expected, FLT_PRECISION);
        auto lineDashOffset = accessor_->getLineDashOffset(peer_);
        auto offset = Converter::Convert<double>(lineDashOffset);
        EXPECT_EQ(offset, expected);
    }
}

/**
 * @tc.name: lineWidthSetterGetterTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, lineWidthSetterGetterTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setLineWidth, nullptr);
    ChangeDensity(DEFAULT_DENSITY);
    for (const auto& [actual, expected] : ARK_FLOAT64_LINE_WIDTH_TEST_PLAN) {
        double target;
        EXPECT_CALL(*renderingModel_, SetLineWidth(_)).WillOnce(DoAll(SaveArg<0>(&target)));
        accessor_->setLineWidth(peer_, actual);
        EXPECT_NEAR(target, expected, FLT_PRECISION);
        auto lineWidth = accessor_->getLineWidth(peer_);
        auto width = Converter::Convert<double>(lineWidth);
        EXPECT_EQ(width, expected);
    }
}

/**
 * @tc.name: miterLimitSetterGetterTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setMiterLimitTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setMiterLimit, nullptr);
    ChangeDensity(DEFAULT_DENSITY);
    for (const auto& [actual, expected] : ARK_FLOAT64_MITER_LIMIT_TEST_PLAN) {
        double target;
        EXPECT_CALL(*renderingModel_, SetMiterLimit(_)).WillOnce(DoAll(SaveArg<0>(&target)));
        accessor_->setMiterLimit(peer_, actual);
        EXPECT_NEAR(target, expected, FLT_PRECISION);
        auto miterLimit = accessor_->getMiterLimit(peer_);
        auto limit = Converter::Convert<double>(miterLimit);
        EXPECT_EQ(limit, expected);
    }
}

/**
 * @tc.name: shadowBlurSetterGetterTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, shadowBlurSetterGetterTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setShadowBlur, nullptr);
    for (const auto& [actual, expected] : ARK_FLOAT64_SHADOW_BLUR_TEST_PLAN) {
        double target;
        EXPECT_CALL(*renderingModel_, SetShadowBlur(_)).WillOnce(DoAll(SaveArg<0>(&target)));
        accessor_->setShadowBlur(peer_, actual);
        EXPECT_NEAR(target, expected, FLT_PRECISION);
        auto shadowBlur = accessor_->getShadowBlur(peer_);
        auto blur = Converter::Convert<double>(shadowBlur);
        EXPECT_EQ(blur, expected);
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
 * @tc.name: shadowOffsetXSetterGetterTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, shadowOffsetXSetterGetterTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setShadowOffsetX, nullptr);
    for (const auto& [actual, expected] : ARK_FLOAT64_TEST_PLAN) {
        double target;
        EXPECT_CALL(*renderingModel_, SetShadowOffsetX(_)).WillOnce(DoAll(SaveArg<0>(&target)));
        accessor_->setShadowOffsetX(peer_, actual);
        EXPECT_NEAR(target, expected, FLT_PRECISION);
        auto shadowOffsetX = accessor_->getShadowOffsetX(peer_);
        auto offsetX = Converter::Convert<double>(shadowOffsetX);
        EXPECT_EQ(offsetX, expected);
    }
}

/**
 * @tc.name: shadowOffsetYSetterGetterTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, shadowOffsetYSetterGetterTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setShadowOffsetY, nullptr);
    for (const auto& [actual, expected] : ARK_FLOAT64_TEST_PLAN) {
        double target;
        EXPECT_CALL(*renderingModel_, SetShadowOffsetY(_)).WillOnce(DoAll(SaveArg<0>(&target)));
        accessor_->setShadowOffsetY(peer_, actual);
        EXPECT_NEAR(target, expected, FLT_PRECISION);
        auto shadowOffsetY = accessor_->getShadowOffsetY(peer_);
        auto offsetY = Converter::Convert<double>(shadowOffsetY);
        EXPECT_EQ(offsetY, expected);
    }
}

/**
 * @tc.name: strokeTestWithPath
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, strokeTestWithPath, TestSize.Level1)
{
    ASSERT_NE(accessor_->stroke, nullptr);
    Ark_Path2D arkPath = PeerUtils::CreatePeer<Path2DPeer>();
    auto path = AceType::MakeRefPtr<CanvasPath2D>();
    arkPath->SetCanvasPath2d(path);
    EXPECT_CALL(*renderingModel_, SetStrokeRuleForPath2D(CanvasFillRule::NONZERO, path)).Times(1);
    auto optPath = Converter::ArkValue<Opt_Path2D>(arkPath);
    accessor_->stroke(peer_, &optPath);
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
    auto peer = PeerUtils::CreatePeer<Matrix2DPeer>();
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
    auto peer = PeerUtils::CreatePeer<Matrix2DPeer>();
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
    auto peer = PeerUtils::CreatePeer<Matrix2DPeer>();
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
HWTEST_F(CanvasRendererAccessorTest, transferFromImageBitmapTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->transferFromImageBitmap, nullptr);
    RefPtr<AceType> target;
    EXPECT_CALL(*renderingModel_, TransferFromImageBitmap(_)).WillOnce(DoAll(SaveArg<0>(&target)));
    auto bitmap = AceType::MakeRefPtr<NiceMock<MockImageBitmapPeer>>();
    Ark_ImageBitmap arkBitmap = Referenced::RawPtr(bitmap);
    const RefPtr<PixelMap> pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    EXPECT_CALL(*bitmap, GetPixelMap()).WillOnce(Return(pixelMap));

    accessor_->transferFromImageBitmap(peer_, arkBitmap);
    EXPECT_EQ(Referenced::RawPtr(target), Referenced::RawPtr(pixelMap));
}
#else

/**
 * @tc.name: transferFromImageBitmapTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, transferFromImageBitmapTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->transferFromImageBitmap, nullptr);
    Ark_ImageBitmap arkBitmap;
    auto peer = new NiceMock<MockImageBitmapPeer>();
    arkBitmap = peer;
    for (const auto& expectedW : SIZE_TEST_PLAN) {
        for (const auto& expectedH : SIZE_TEST_PLAN) {
            std::shared_ptr<Ace::ImageData> target;
            EXPECT_CALL(*renderingModel_, TransferFromImageBitmap(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            auto imageData = std::make_shared<Ace::ImageData>();
            imageData->dirtyWidth = expectedW;
            imageData->dirtyHeight = expectedH;
            peer->SetImageData(imageData);
            accessor_->transferFromImageBitmap(peer_, arkBitmap);
            EXPECT_EQ(target->dirtyWidth, expectedW);
            EXPECT_EQ(target->dirtyHeight, expectedH);
        }
    }
}
#endif

/**
 * @tc.name: setFontStyleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setFontStyleTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setFont, nullptr);
    for (const auto& [actual, expected] : FONT_STYLE_TEST_PLAN) {
        EXPECT_CALL(*renderingModel_, SetFontStyle(expected)).Times(1);
        EXPECT_CALL(*renderingModel_, SetFontWeight(Ace::FontWeight::NORMAL)).Times(1);
        auto arkFont = Converter::ArkValue<Ark_String>(actual, Converter::FC);
        accessor_->setFont(peer_, &arkFont);
    }
}

/**
 * @tc.name: setFontWeightTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setFontWeightTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setFont, nullptr);
    auto style = FONT_STYLE_TEST_PLAN[2].first;
    auto size = FONT_SIZE_PX_TEST_PLAN[0].first;
    auto family = FONT_FAMILIES_TEST_PLAN[0].first;
    for (const auto& [actual, expected] : FONT_WEIGHT_TEST_PLAN) {
        EXPECT_CALL(*renderingModel_, SetFontWeight(expected)).Times(1);
        EXPECT_CALL(*renderingModel_, SetFontStyle(FONT_STYLE_TEST_PLAN[2].second)).Times(1);
        EXPECT_CALL(*renderingModel_, SetFontSize(FONT_SIZE_PX_TEST_PLAN[0].second)).Times(1);
        EXPECT_CALL(*renderingModel_, SetFontFamilies(FONT_FAMILIES_TEST_PLAN[0].second)).Times(1);
        auto font = style + " " + actual + " " + size + " " + family;
        auto arkFont = Converter::ArkValue<Ark_String>(font, Converter::FC);
        accessor_->setFont(peer_, &arkFont);
    }
}

/**
 * @tc.name: setFontSizePxTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setFontSizePxTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setFont, nullptr);
    for (const auto& [actual, expected] : FONT_SIZE_PX_TEST_PLAN) {
        auto nCalls = (actual == INVALID_STRING || actual == EMPTY_STRING) ? 0 : 1;
        EXPECT_CALL(*renderingModel_, SetFontSize(expected)).Times(nCalls);
        EXPECT_CALL(*renderingModel_, SetFontStyle(Ace::FontStyle::NORMAL)).Times(1);
        EXPECT_CALL(*renderingModel_, SetFontWeight(Ace::FontWeight::NORMAL)).Times(1);
        auto arkFont = Converter::ArkValue<Ark_String>(actual, Converter::FC);
        accessor_->setFont(peer_, &arkFont);
    }
}

/**
 * @tc.name: setFontSizeVpTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setFontSizeVpTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setFont, nullptr);
    for (const auto& [actual, expected] : FONT_SIZE_VP_TEST_PLAN) {
        auto nCalls = (actual == INVALID_STRING || actual == EMPTY_STRING) ? 0 : 1;
        EXPECT_CALL(*renderingModel_, SetFontSize(expected)).Times(nCalls);
        EXPECT_CALL(*renderingModel_, SetFontStyle(Ace::FontStyle::NORMAL)).Times(1);
        EXPECT_CALL(*renderingModel_, SetFontWeight(Ace::FontWeight::NORMAL)).Times(1);
        auto arkFont = Converter::ArkValue<Ark_String>(actual, Converter::FC);
        accessor_->setFont(peer_, &arkFont);
    }
}

/**
 * @tc.name: setFontFamiliesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setFontFamiliesTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setFont, nullptr);
    for (const auto& [actual, expected] : FONT_FAMILIES_TEST_PLAN) {
        auto nCalls = (actual == INVALID_STRING || actual == EMPTY_STRING) ? 0 : 1;
        EXPECT_CALL(*renderingModel_, SetFontFamilies(expected)).Times(nCalls);
        EXPECT_CALL(*renderingModel_, SetFontStyle(Ace::FontStyle::NORMAL)).Times(1);
        EXPECT_CALL(*renderingModel_, SetFontWeight(Ace::FontWeight::NORMAL)).Times(1);
        auto arkFont = Converter::ArkValue<Ark_String>(actual, Converter::FC);
        accessor_->setFont(peer_, &arkFont);
    }
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
            auto x0 = Converter::ArkValue<Ark_Float64>(expectedX);
            auto y0 = Converter::ArkValue<Ark_Float64>(expectedY);
            auto x1 = Converter::ArkValue<Ark_Float64>(valD);
            auto y1 = Converter::ArkValue<Ark_Float64>(valD);
            auto peer = accessor_->createLinearGradient(peer_, x0, y0, x1, y1);
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
    // with density
    double density = DENSITY_1_25;
    ChangeDensity(density);
    for (const auto& expectedX : NUMBER_TEST_PLAN) {
        for (const auto& expectedY : NUMBER_TEST_PLAN) {
            auto x0 = Converter::ArkValue<Ark_Float64>(valD);
            auto y0 = Converter::ArkValue<Ark_Float64>(valD);
            auto x1 = Converter::ArkValue<Ark_Float64>(expectedX);
            auto y1 = Converter::ArkValue<Ark_Float64>(expectedY);
            auto peer = accessor_->createLinearGradient(peer_, x0, y0, x1, y1);
            ASSERT_NE(peer, nullptr);
            std::shared_ptr<OHOS::Ace::Gradient> gradient = peer->GetGradient();
            ASSERT_NE(gradient, nullptr);
            auto o1 = gradient->GetBeginOffset();
            auto o2 = gradient->GetEndOffset();
            EXPECT_TRUE(LessOrEqualCustomPrecision(o1.GetX(), valD * density));
            EXPECT_TRUE(LessOrEqualCustomPrecision(o1.GetY(), valD * density));
            EXPECT_TRUE(LessOrEqualCustomPrecision(o2.GetX(), expectedX * density));
            EXPECT_TRUE(LessOrEqualCustomPrecision(o2.GetY(), expectedY * density));
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
            auto x0 = Converter::ArkValue<Ark_Float64>(expectedX);
            auto y0 = Converter::ArkValue<Ark_Float64>(valD);
            auto r0 = Converter::ArkValue<Ark_Float64>(expectedR);
            auto x1 = Converter::ArkValue<Ark_Float64>(valD);
            auto y1 = Converter::ArkValue<Ark_Float64>(valD);
            auto r1 = Converter::ArkValue<Ark_Float64>(valR);
            auto peer = accessor_->createRadialGradient(peer_, x0, y0, r0, x1, y1, r1);
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
    // with density
    double density = DENSITY_2_50;
    ChangeDensity(density);
    for (const auto& expectedY : NUMBER_TEST_PLAN) {
        for (const auto& expectedR : NUMBER_ALPHA_TEST_PLAN) {
            auto x0 = Converter::ArkValue<Ark_Float64>(valD);
            auto y0 = Converter::ArkValue<Ark_Float64>(valD);
            auto r0 = Converter::ArkValue<Ark_Float64>(valR);
            auto x1 = Converter::ArkValue<Ark_Float64>(valD);
            auto y1 = Converter::ArkValue<Ark_Float64>(expectedY);
            auto r1 = Converter::ArkValue<Ark_Float64>(expectedR);
            auto peer = accessor_->createRadialGradient(peer_, x0, y0, r0, x1, y1, r1);
            ASSERT_NE(peer, nullptr);
            std::shared_ptr<OHOS::Ace::Gradient> gradient = peer->GetGradient();
            ASSERT_NE(gradient, nullptr);
            auto o1 = gradient->GetBeginOffset();
            auto o2 = gradient->GetEndOffset();
            auto ri = gradient->GetInnerRadius();
            auto ro = gradient->GetOuterRadius();
            EXPECT_NEAR(o1.GetX(), valD * density, FLT_PRECISION);
            EXPECT_NEAR(o1.GetY(), valD * density, FLT_PRECISION);
            EXPECT_NEAR(o2.GetX(), valD * density, FLT_PRECISION);
            EXPECT_NEAR(o2.GetY(), expectedY * density, FLT_PRECISION);
            EXPECT_NEAR(ri, valR * density, FLT_PRECISION);
            EXPECT_NEAR(ro, expectedR * density, FLT_PRECISION);
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
            auto x0 = Converter::ArkValue<Ark_Float64>(valD);
            auto y0 = Converter::ArkValue<Ark_Float64>(expectedY);
            auto r0 = Converter::ArkValue<Ark_Float64>(valR);
            auto x1 = Converter::ArkValue<Ark_Float64>(expectedX);
            auto y1 = Converter::ArkValue<Ark_Float64>(valD);
            auto r1 = Converter::ArkValue<Ark_Float64>(valR);
            auto peer = accessor_->createRadialGradient(peer_, x0, y0, r0, x1, y1, r1);
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
            auto x = Converter::ArkValue<Ark_Float64>(expectedX);
            auto y = Converter::ArkValue<Ark_Float64>(expectedY);
            auto startAngle = Converter::ArkValue<Ark_Float64>(valR);
            auto peer = accessor_->createConicGradient(peer_, startAngle, x, y);
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
    // with density
    double density = DENSITY_2_50;
    ChangeDensity(density);
    for (const auto& expectedX : NUMBER_TEST_PLAN) {
        for (const auto& actualA : NUMBER_ALPHA_TEST_PLAN) {
            auto x = Converter::ArkValue<Ark_Float64>(expectedX);
            auto y = Converter::ArkValue<Ark_Float64>(valD);
            auto startAngle = Converter::ArkValue<Ark_Float64>(actualA);
            auto expectedA = fmod(actualA, (MATH_2_PI));
            auto peer = accessor_->createConicGradient(peer_, startAngle, x, y);
            ASSERT_NE(peer, nullptr);
            std::shared_ptr<OHOS::Ace::Gradient> gradient = peer->GetGradient();
            ASSERT_NE(gradient, nullptr);
            auto optX = gradient->GetConicGradient().centerX;
            auto optY = gradient->GetConicGradient().centerY;
            auto optA = gradient->GetConicGradient().startAngle;
            ASSERT_TRUE(optX);
            ASSERT_TRUE(optY);
            ASSERT_TRUE(optA);
            EXPECT_NEAR(optX->Value(), expectedX * density, FLT_PRECISION);
            EXPECT_NEAR(optY->Value(), valD * density, FLT_PRECISION);
            EXPECT_NEAR(optA->Value(), expectedA, FLT_PRECISION);
        }
    }
}

#ifdef PIXEL_MAP_SUPPORTED
/**
 * @tc.name: getPixelMapXYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, getPixelMapXYTest, TestSize.Level1)
{
    auto valD = DEFAULT_DOUBLE_VALUE;
    ASSERT_NE(accessor_->getPixelMap, nullptr);
    for (const auto& actualX : NUMBER_TEST_PLAN) {
        for (const auto& actualY : NUMBER_TEST_PLAN) {
            ImageSize target;
            RefPtr<PixelMap> pixelMap = AceType::MakeRefPtr<MockPixelMap>();
            EXPECT_CALL(*renderingModel_, GetPixelMap(_)).WillOnce(DoAll(SaveArg<0>(&target), Return(pixelMap)));
            auto sx = Converter::ArkValue<Ark_Float64>(actualX);
            auto sy = Converter::ArkValue<Ark_Float64>(actualY);
            auto sw = Converter::ArkValue<Ark_Float64>(valD);
            auto sh = Converter::ArkValue<Ark_Float64>(valD);
            Ark_PixelMap pixelMapPeer = accessor_->getPixelMap(peer_, sx, sy, sw, sh);
            ASSERT_NE(pixelMapPeer, nullptr);
            EXPECT_EQ(Referenced::RawPtr(pixelMapPeer->pixelMap), Referenced::RawPtr(pixelMap));
            EXPECT_NEAR(target.left, actualX, FLT_PRECISION);
            EXPECT_NEAR(target.top, actualY, FLT_PRECISION);
        }
    }
    // with density
    double density = DENSITY_1_25;
    ChangeDensity(density);
    for (const auto& actualX : NUMBER_TEST_PLAN) {
        for (const auto& actualY : NUMBER_TEST_PLAN) {
            ImageSize target;
            RefPtr<PixelMap> pixelMap = AceType::MakeRefPtr<MockPixelMap>();
            EXPECT_CALL(*renderingModel_, GetPixelMap(_)).WillOnce(DoAll(SaveArg<0>(&target), Return(pixelMap)));
            auto sx = Converter::ArkValue<Ark_Float64>(actualX);
            auto sy = Converter::ArkValue<Ark_Float64>(actualY);
            auto sw = Converter::ArkValue<Ark_Float64>(valD);
            auto sh = Converter::ArkValue<Ark_Float64>(valD);
            Ark_PixelMap pixelMapPeer = accessor_->getPixelMap(peer_, sx, sy, sw, sh);
            ASSERT_NE(pixelMapPeer, nullptr);
            EXPECT_EQ(Referenced::RawPtr(pixelMapPeer->pixelMap), Referenced::RawPtr(pixelMap));
            EXPECT_NEAR(target.left, actualX * density, FLT_PRECISION);
            EXPECT_NEAR(target.top, actualY * density, FLT_PRECISION);
        }
    }
}

/**
 * @tc.name: getPixelMapWHTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, getPixelMapWHTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getPixelMap, nullptr);
    for (const auto& actualW : NUMBER_TEST_PLAN) {
        for (const auto& actualH : NUMBER_TEST_PLAN) {
            ImageSize target;
            RefPtr<PixelMap> pixelMap = AceType::MakeRefPtr<MockPixelMap>();
            EXPECT_CALL(*renderingModel_, GetPixelMap(_)).WillOnce(DoAll(SaveArg<0>(&target), Return(pixelMap)));
            auto sx = Converter::ArkValue<Ark_Float64>(DEFAULT_DOUBLE_VALUE);
            auto sy = Converter::ArkValue<Ark_Float64>(DEFAULT_DOUBLE_VALUE);
            auto sw = Converter::ArkValue<Ark_Float64>(actualW);
            auto sh = Converter::ArkValue<Ark_Float64>(actualH);
            Ark_PixelMap pixelMapPeer = accessor_->getPixelMap(peer_, sx, sy, sw, sh);
            ASSERT_NE(pixelMapPeer, nullptr);
            EXPECT_EQ(Referenced::RawPtr(pixelMapPeer->pixelMap), Referenced::RawPtr(pixelMap));
            EXPECT_NEAR(target.width, actualW, FLT_PRECISION);
            EXPECT_NEAR(target.height, actualH, FLT_PRECISION);
        }
    }
    // with density
    double density = DENSITY_2_50;
    ChangeDensity(density);
    for (const auto& actualW : NUMBER_TEST_PLAN) {
        for (const auto& actualH : NUMBER_TEST_PLAN) {
            ImageSize target;
            RefPtr<PixelMap> pixelMap = AceType::MakeRefPtr<MockPixelMap>();
            EXPECT_CALL(*renderingModel_, GetPixelMap(_)).WillOnce(DoAll(SaveArg<0>(&target), Return(pixelMap)));
            auto sx = Converter::ArkValue<Ark_Float64>(DEFAULT_DOUBLE_VALUE);
            auto sy = Converter::ArkValue<Ark_Float64>(DEFAULT_DOUBLE_VALUE);
            auto sw = Converter::ArkValue<Ark_Float64>(actualW);
            auto sh = Converter::ArkValue<Ark_Float64>(actualH);
            Ark_PixelMap pixelMapPeer = accessor_->getPixelMap(peer_, sx, sy, sw, sh);
            ASSERT_NE(pixelMapPeer, nullptr);
            EXPECT_EQ(Referenced::RawPtr(pixelMapPeer->pixelMap), Referenced::RawPtr(pixelMap));
            EXPECT_NEAR(target.width, actualW * density, FLT_PRECISION);
            EXPECT_NEAR(target.height, actualH * density, FLT_PRECISION);
        }
    }
}

#else

/**
 * @tc.name: getPixelMapTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, getPixelMapTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getPixelMap, nullptr);
    auto arkD = Converter::ArkValue<Ark_Float64>(DEFAULT_DOUBLE_VALUE);
    auto arkR = Converter::ArkValue<Ark_Float64>(DEFAULT_SCALE_VALUE);
    auto ptr = accessor_->getPixelMap(peer_, arkD, arkR, arkD, arkR);
    EXPECT_EQ(ptr, nullptr);
    ptr = accessor_->getPixelMap(peer_, arkR, arkD, arkR, arkD);
    EXPECT_EQ(ptr, nullptr);
}
#endif

/**
 * @tc.name: createPatternTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, createPatternTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->createPattern, nullptr);
    Ark_ImageBitmap arkBitmap;
    auto bitmapPeer = new NiceMock<MockImageBitmapPeerPattern>();
    arkBitmap = bitmapPeer;
    auto repetition = Converter::ArkValue<Opt_String>(REPEAT_STRING);
    for (const auto& actualW : NUMBER_TEST_PLAN) {
        for (const auto& actualH : NUMBER_TEST_PLAN) {
            std::shared_ptr<Ace::Pattern> target;
            TransformParam param;
            EXPECT_CALL(*renderingModel_, SetTransform(Matcher<std::shared_ptr<Ace::Pattern>>(testing::_), _))
                .WillOnce(DoAll(SaveArg<0>(&target), SaveArg<1>(&param)));
            bitmapPeer->SetWidth(actualW);
            bitmapPeer->SetHeight(actualH);

            Opt_CanvasPattern result = accessor_->createPattern(peer_, arkBitmap, &repetition);
            auto pattern = Converter::OptConvert<Ark_CanvasPattern>(result);
            ASSERT_TRUE(pattern.has_value());
            Ark_CanvasPattern patternPeer = pattern.value();
            ASSERT_NE(patternPeer, nullptr);

            std::optional<Matrix2DPeer*> optMatrix = PeerUtils::CreatePeer<Matrix2DPeer>();
            patternPeer->SetTransform(optMatrix);
            ASSERT_NE(target, nullptr);
            EXPECT_NEAR(target->GetImageWidth(), actualW, FLT_PRECISION);
            EXPECT_NEAR(target->GetImageHeight(), actualH, FLT_PRECISION);
            EXPECT_EQ(target->GetRepetition(), REPEAT_STRING);
        }
    }
}
} // namespace OHOS::Ace::NG
