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
const auto EXPECTED_TRUE = true;
const auto EXPECTED_FALSE = false;
const double DEFAULT_DOUBLE_VALUE = 2.0;
const std::string DEFAULT_STRING_VALUE = "text";
const std::string EMPTY_STRING = "";
const Opt_Boolean OPT_BOOLEAN_FALSE = Converter::ArkValue<Opt_Boolean>(false);
const std::string INVALID_STRING = "invalid";
const std::string REPEAT_STRING = "repeat";
const double FLT_PRECISION = 0.001;
const double DEFAULT_DENSITY = 1.0;
const double DENSITY_1_25 = 1.25;
const double DENSITY_NEGATIVE = -1.0;
const auto IMAGE_FIT_CENTER = Ace::ImageFit::CENTER;
const double DEFAULT_DOUBLE_ZERO = 0.0;
// test plan
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
std::vector<double> NUMBER_TEST_PLAN = {
    100, 0, -100, 12.34, -56.73,
};
std::vector<std::tuple<Ark_String, std::string>> IMAGE_SMOOTHING_TEST_PLAN = {
    { Converter::ArkValue<Ark_String>("low"), "low" },
    { Converter::ArkValue<Ark_String>("medium"), "medium" },
    { Converter::ArkValue<Ark_String>("high"), "high" },
    { Converter::ArkValue<Ark_String>(""), EMPTY_STRING },
    { Converter::ArkValue<Ark_String>("invalid"), EMPTY_STRING }
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
std::vector<std::tuple<Ark_String, Color, bool>> STYLE_STRING_TEST_PLAN = {
    { Converter::ArkValue<Ark_String>("#ff0000ff"), Color(0xff0000ff), true },
    { Converter::ArkValue<Ark_String>("#00000000"), Color(0x00000000), true },
    { Converter::ArkValue<Ark_String>("#80ffffff"), Color(0x80ffffff), true },
    { Converter::ArkValue<Ark_String>(""), Color(), false },
    { Converter::ArkValue<Ark_String>("invalid color"), Color(), false },
};
std::vector<std::tuple<Ark_Int32, Color>> STYLE_NUMBER_TEST_PLAN = {
    { Converter::ArkValue<Ark_Int32>(0xff0000ff), Color(0xff0000ff) },
    { Converter::ArkValue<Ark_Int32>(0x00000000), Color(0xff000000) },
    { Converter::ArkValue<Ark_Int32>(0x80ffffff), Color(0x80ffffff) },
    { Converter::ArkValue<Ark_Int32>(0xffffffff), Color(0xffffffff) },
    { Converter::ArkValue<Ark_Int32>(0x11111111), Color(0x11111111) },
    { Converter::ArkValue<Ark_Int32>(-1), Color() },
};
std::vector<std::tuple<Ark_Color, Color>> STYLE_COLOR_TEST_PLAN = {
    { Ark_Color::ARK_COLOR_RED, Color::RED },
    { Ark_Color::ARK_COLOR_WHITE, Color::WHITE },
    { Ark_Color::ARK_COLOR_TRANSPARENT, Color::TRANSPARENT },
    { Ark_Color::ARK_COLOR_BLACK, Color::BLACK },
    { Ark_Color::ARK_COLOR_BLUE, Color::BLUE },
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
    MOCK_METHOD(bool, GetIsWideColorGamut, (), (const override));
    MOCK_METHOD(uint32_t, GetInnerColorGamut, (), (const override));
    MOCK_METHOD(void, SetMemoryName, (std::string pixelMapName), (const override));
    MOCK_METHOD(uint32_t, GetUniqueId, (), (override));
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
struct MockImageBitmapPeerStyle : public ImageBitmapPeer {
public:
    MockImageBitmapPeerStyle() = default;
    ~MockImageBitmapPeerStyle() override = default;
    using ImageBitmapPeer::SetHeight;
    using ImageBitmapPeer::SetWidth;
    MOCK_METHOD(RefPtr<Ace::PixelMap>, GetPixelMap, (), (const));
    MOCK_METHOD(std::string, GetSrc, (), ());
};
struct MockImageBitmapPeer : public MockImageBitmapPeerStyle {
public:
    MockImageBitmapPeer() = default;
    ~MockImageBitmapPeer() override = default;
    MOCK_METHOD(bool, IsSvg, (), ());
    MOCK_METHOD(RefPtr<NG::SvgDomBase>, GetSvgDom, (), ());
    MOCK_METHOD(Ace::ImageFit, GetImageFit, (), ());
};
class MockSvgDom : public NG::SvgDomBase {
public:
    MockSvgDom() = default;
    ~MockSvgDom() override = default;
    MOCK_METHOD(SizeF, GetContainerSize, (), (const));
    MOCK_METHOD(void, SetContainerSize, (const SizeF&), ());
    MOCK_METHOD(void, DrawImage, (RSCanvas&, const ImageFit&, const Size&), ());
};
} // namespace

class CanvasRendererAccessorTest2
    : public AccessorTestBase<GENERATED_ArkUICanvasRendererAccessor,
    &GENERATED_ArkUIAccessors::getCanvasRendererAccessor, CanvasRendererPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        renderingModel_ = AceType::MakeRefPtr<MockCanvasRenderingContext2DModel>();
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
 * @tc.name: getTransformScaleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, getTransformScaleTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getTransform, nullptr);
    for (const auto& expectedX : NUMBER_TEST_PLAN) {
        for (const auto& expectedY : NUMBER_TEST_PLAN) {
            auto target = TransformParam {
                .scaleX = expectedX,
                .scaleY = expectedY,
            };
            EXPECT_CALL(*renderingModel_, GetTransform()).WillOnce(Return(target));
            Container::Current()->SetUseNewPipeline();

            Matrix2DPeer* matrix = accessor_->getTransform(peer_);
            ASSERT_NE(matrix, nullptr);
            EXPECT_NEAR(matrix->GetScaleX(), expectedX, FLT_PRECISION);
            EXPECT_NEAR(matrix->GetScaleY(), expectedY, FLT_PRECISION);
        }
    }
}

/**
 * @tc.name: getTransformRotateTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, getTransformRotateTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getTransform, nullptr);
    for (const auto& expectedX : NUMBER_TEST_PLAN) {
        for (const auto& expectedY : NUMBER_TEST_PLAN) {
            auto target = TransformParam {
                .skewX = expectedX,
                .skewY = expectedY,
            };
            EXPECT_CALL(*renderingModel_, GetTransform()).WillOnce(Return(target));
            Container::Current()->SetUseNewPipeline();

            Matrix2DPeer* matrix = accessor_->getTransform(peer_);
            ASSERT_NE(matrix, nullptr);
            EXPECT_NEAR(matrix->GetRotateX(), expectedX, FLT_PRECISION);
            EXPECT_NEAR(matrix->GetRotateY(), expectedY, FLT_PRECISION);
        }
    }
}

/**
 * @tc.name: getTransformTranslateTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, getTransformTranslateTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getTransform, nullptr);
    for (const auto& expectedX : NUMBER_TEST_PLAN) {
        for (const auto& expectedY : NUMBER_TEST_PLAN) {
            auto target = TransformParam {
                .translateX = expectedX,
                .translateY = expectedY,
            };
            EXPECT_CALL(*renderingModel_, GetTransform()).WillOnce(Return(target));
            Container::Current()->SetUseNewPipeline();

            Matrix2DPeer* matrix = accessor_->getTransform(peer_);
            ASSERT_NE(matrix, nullptr);
            EXPECT_NEAR(matrix->GetTranslateX(), expectedX, FLT_PRECISION);
            EXPECT_NEAR(matrix->GetTranslateY(), expectedY, FLT_PRECISION);
        }
    }
}

/**
 * @tc.name: setImageSmoothingQualityTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, setImageSmoothingQualityTest, TestSize.Level1)
{
    for (const auto& [actual, expected] : IMAGE_SMOOTHING_TEST_PLAN) {
        auto nCalls = (expected == EMPTY_STRING) ? 0 : 1;
        EXPECT_CALL(*renderingModel_, SetSmoothingQuality(expected)).Times(nCalls);
        accessor_->setImageSmoothingQuality(peer_, &actual);
    }
}

/**
 * @tc.name: setLineCapTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, setLineCapTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setLineCap, nullptr);
    for (const auto& [actual, expected] : LINE_CAP_TEST_PLAN) {
        EXPECT_CALL(*renderingModel_, SetLineCap(expected)).Times(1);
        accessor_->setLineCap(peer_, &actual);
    }
}

/**
 * @tc.name: setLineJoinTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, setLineJoinTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setLineJoin, nullptr);
    for (const auto& [actual, expected] : LINE_JOIN_TEST_PLAN) {
        EXPECT_CALL(*renderingModel_, SetLineJoin(expected)).Times(1);
        accessor_->setLineJoin(peer_, &actual);
    }
}

#ifdef PIXEL_MAP_SUPPORTED
/**
 * @tc.name: setPixelMapTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, setPixelMapTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setPixelMap, nullptr);
    Ark_image_PixelMap arkPixelMap = PeerUtils::CreatePeer<image_PixelMapPeer>();
    auto optPixelMap = Converter::ArkValue<Opt_PixelMap>(arkPixelMap);
    Ace::ImageInfo target;
    EXPECT_CALL(*renderingModel_, DrawPixelMap(_)).WillOnce(DoAll(SaveArg<0>(&target)));
    arkPixelMap->pixelMap = AceType::MakeRefPtr<MockPixelMap>();

    accessor_->setPixelMap(peer_, &optPixelMap);
    EXPECT_EQ(Referenced::RawPtr(target.pixelMap), Referenced::RawPtr(arkPixelMap->pixelMap));
}
#else

/**
 * @tc.name: setPixelMapTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, setPixelMapTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setPixelMap, nullptr);
    accessor_->setPixelMap(peer_, nullptr);
    EXPECT_TRUE(true);
}
#endif

/**
 * @tc.name: clip0Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, clip0Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->clip0, nullptr);
    for (const auto& [actual, expected] : FILL_RULE_TEST_PLAN) {
        EXPECT_CALL(*renderingModel_, SetClipRuleForPath(expected)).Times(1);
        accessor_->clip0(peer_, &actual);
    }
}

/**
 * @tc.name: clip1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, clip1Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->clip1, nullptr);
    Ark_Path2D arkPath = new Path2DPeer();
    auto path = AceType::MakeRefPtr<CanvasPath2D>();
    arkPath->SetCanvasPath2d(path);
    for (const auto& [arkRule, expected] : FILL_RULE_TEST_PLAN) {
        EXPECT_CALL(*renderingModel_, SetClipRuleForPath2D(expected, path)).Times(1);
        accessor_->clip1(peer_, arkPath, &arkRule);
    }
}

/**
 * @tc.name: fill0Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, fill0Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->fill0, nullptr);
    for (const auto& [actual, expected] : FILL_RULE_TEST_PLAN) {
        EXPECT_CALL(*renderingModel_, SetFillRuleForPath(expected)).Times(1);
        accessor_->fill0(peer_, &actual);
    }
}

/**
 * @tc.name: fill1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, fill1Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->fill1, nullptr);
    Ark_Path2D arkPath = new Path2DPeer();
    auto path = AceType::MakeRefPtr<CanvasPath2D>();
    arkPath->SetCanvasPath2d(path);
    for (const auto& [arkRule, expected] : FILL_RULE_TEST_PLAN) {
        EXPECT_CALL(*renderingModel_, SetFillRuleForPath2D(expected, path)).Times(1);
        accessor_->fill1(peer_, arkPath, &arkRule);
    }
}

/**
 * @tc.name: setDirectionTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, setDirectionTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setDirection, nullptr);
    for (const auto& [actual, expected] : DIRECTION_TEST_PLAN) {
        EXPECT_CALL(*renderingModel_, SetTextDirection(expected)).Times(1);
        accessor_->setDirection(peer_, &actual);
    }
}

/**
 * @tc.name: setTextAlignTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, setTextAlignTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setTextAlign, nullptr);
    for (const auto& [actual, expected] : TEXT_ALIGN_TEST_PLAN) {
        EXPECT_CALL(*renderingModel_, SetTextAlign(expected)).Times(1);
        accessor_->setTextAlign(peer_, &actual);
    }
}

/**
 * @tc.name: setTextBaselineTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, setTextBaselineTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setTextBaseline, nullptr);
    for (const auto& [actual, expected] : TEXT_BASE_LINE_TEST_PLAN) {
        EXPECT_CALL(*renderingModel_, SetTextBaseline(expected)).Times(1);
        accessor_->setTextBaseline(peer_, &actual);
    }
}

/**
 * @tc.name: drawImage0BitmapTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, drawImage0BitmapTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->drawImage0, nullptr);
    RefPtr<MockImageBitmapPeer> bitmap = AceType::MakeRefPtr<NiceMock<MockImageBitmapPeer>>();
    Ark_ImageBitmap arkBitmap = Referenced::RawPtr(bitmap);
#if !defined(PREVIEW)
    const RefPtr<PixelMap> pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    for (const auto& actualX : NUMBER_TEST_PLAN) {
        for (const auto& actualY : NUMBER_TEST_PLAN) {
            Ace::ImageInfo target;
            EXPECT_CALL(*renderingModel_, DrawPixelMap(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            EXPECT_CALL(*bitmap, GetPixelMap()).WillOnce(Return(pixelMap));
            EXPECT_CALL(*bitmap, IsSvg()).WillOnce(Return(EXPECTED_FALSE));
            auto dx = Converter::ArkValue<Ark_Float64>(actualX);
            auto dy = Converter::ArkValue<Ark_Float64>(actualY);
            auto image = Converter::ArkUnion<Ark_Union_ImageBitmap_PixelMap, Ark_ImageBitmap>(arkBitmap);
            accessor_->drawImage0(peer_, &image, dx, dy);

            ASSERT_NE(target.pixelMap, nullptr);
            EXPECT_NEAR(target.image.dx, actualX, FLT_PRECISION);
            EXPECT_NEAR(target.image.dy, actualY, FLT_PRECISION);
            EXPECT_EQ(target.pixelMap, pixelMap);
        }
    }
#else
    const auto imageData = std::make_shared<Ace::ImageData>();
    arkBitmap->SetImageData(imageData);
    for (const auto& actualX : NUMBER_TEST_PLAN) {
        for (const auto& actualY : NUMBER_TEST_PLAN) {
            Ace::ImageInfo target;
            EXPECT_CALL(*renderingModel_, DrawImage(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            EXPECT_CALL(*bitmap, IsSvg()).WillOnce(Return(EXPECTED_FALSE));
            auto dx = Converter::ArkValue<Ark_Float64>(actualX);
            auto dy = Converter::ArkValue<Ark_Float64>(actualY);
            auto image = Converter::ArkUnion<Ark_Union_ImageBitmap_PixelMap, Ark_ImageBitmap>(arkBitmap);
            accessor_->drawImage0(peer_, &image, dx, dy);

            ASSERT_NE(target.image.imageData, nullptr);
            EXPECT_NEAR(target.image.dx, actualX, FLT_PRECISION);
            EXPECT_NEAR(target.image.dy, actualY, FLT_PRECISION);
            EXPECT_EQ(target.image.imageData, imageData);
        }
    }
#endif
}

/**
 * @tc.name: drawImage0SvgTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, drawImage0SvgTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->drawImage0, nullptr);
    RefPtr<MockImageBitmapPeer> bitmap = AceType::MakeRefPtr<NiceMock<MockImageBitmapPeer>>();
    Ark_ImageBitmap arkBitmap = Referenced::RawPtr(bitmap);
    const RefPtr<NG::SvgDomBase> svgDom = AceType::MakeRefPtr<MockSvgDom>();
    for (const auto& actualX : NUMBER_TEST_PLAN) {
        for (const auto& actualY : NUMBER_TEST_PLAN) {
            Ace::ImageInfo target;
            EXPECT_CALL(*renderingModel_, DrawSvgImage(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            EXPECT_CALL(*bitmap, IsSvg()).WillOnce(Return(EXPECTED_TRUE));
            EXPECT_CALL(*bitmap, GetSvgDom()).WillOnce(Return(svgDom));
            EXPECT_CALL(*bitmap, GetImageFit()).WillOnce(Return(IMAGE_FIT_CENTER));
            auto dx = Converter::ArkValue<Ark_Float64>(actualX);
            auto dy = Converter::ArkValue<Ark_Float64>(actualY);
            auto image = Converter::ArkUnion<Ark_Union_ImageBitmap_PixelMap, Ark_ImageBitmap>(arkBitmap);
            accessor_->drawImage0(peer_, &image, dx, dy);

            ASSERT_NE(target.svgDom, nullptr);
            EXPECT_NEAR(target.image.dx, actualX, FLT_PRECISION);
            EXPECT_NEAR(target.image.dy, actualY, FLT_PRECISION);
            EXPECT_EQ(target.imageFit, IMAGE_FIT_CENTER);
            EXPECT_EQ(target.svgDom, svgDom);
        }
    }
}

#if !defined(PREVIEW)
/**
 * @tc.name: drawImage0PixelMapTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, drawImage0PixelMapTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->drawImage0, nullptr);
    Ark_image_PixelMap arkPixelMap = PeerUtils::CreatePeer<image_PixelMapPeer>();
    const RefPtr<PixelMap> pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    arkPixelMap->pixelMap = pixelMap;
    for (const auto& actualX : NUMBER_TEST_PLAN) {
        for (const auto& actualY : NUMBER_TEST_PLAN) {
            Ace::ImageInfo target;
            EXPECT_CALL(*renderingModel_, DrawPixelMap(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            auto dx = Converter::ArkValue<Ark_Float64>(actualX);
            auto dy = Converter::ArkValue<Ark_Float64>(actualY);
            auto image = Converter::ArkUnion<Ark_Union_ImageBitmap_PixelMap, Ark_image_PixelMap>(arkPixelMap);
            accessor_->drawImage0(peer_, &image, dx, dy);

            ASSERT_NE(target.pixelMap, nullptr);
            EXPECT_NEAR(target.image.dx, actualX, FLT_PRECISION);
            EXPECT_NEAR(target.image.dy, actualY, FLT_PRECISION);
            EXPECT_EQ(target.pixelMap, pixelMap);
        }
    }
}
#endif

/**
 * @tc.name: drawImage1BitmapXYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, drawImage1BitmapXYTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->drawImage1, nullptr);
    RefPtr<MockImageBitmapPeer> bitmap = AceType::MakeRefPtr<NiceMock<MockImageBitmapPeer>>();
    Ark_ImageBitmap arkBitmap = Referenced::RawPtr(bitmap);
    Ark_Float64 dv = Converter::ArkValue<Ark_Float64>(DEFAULT_DOUBLE_VALUE);
#if !defined(PREVIEW)
    const RefPtr<PixelMap> pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    for (const auto& actualX : NUMBER_TEST_PLAN) {
        for (const auto& actualY : NUMBER_TEST_PLAN) {
            Ace::ImageInfo target;
            EXPECT_CALL(*renderingModel_, DrawPixelMap(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            EXPECT_CALL(*bitmap, GetPixelMap()).WillOnce(Return(pixelMap));
            EXPECT_CALL(*bitmap, IsSvg()).WillOnce(Return(EXPECTED_FALSE));
            auto dx = Converter::ArkValue<Ark_Float64>(actualX);
            auto dy = Converter::ArkValue<Ark_Float64>(actualY);
            auto image = Converter::ArkUnion<Ark_Union_ImageBitmap_PixelMap, Ark_ImageBitmap>(arkBitmap);
            accessor_->drawImage1(peer_, &image, dx, dy, dv, dv);

            ASSERT_NE(target.pixelMap, nullptr);
            EXPECT_NEAR(target.image.dx, actualX, FLT_PRECISION);
            EXPECT_NEAR(target.image.dy, actualY, FLT_PRECISION);
            EXPECT_EQ(target.pixelMap, pixelMap);
        }
    }
#else
    const auto imageData = std::make_shared<Ace::ImageData>();
    arkBitmap->SetImageData(imageData);
    for (const auto& actualX : NUMBER_TEST_PLAN) {
        for (const auto& actualY : NUMBER_TEST_PLAN) {
            Ace::ImageInfo target;
            EXPECT_CALL(*renderingModel_, DrawImage(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            EXPECT_CALL(*bitmap, IsSvg()).WillOnce(Return(EXPECTED_FALSE));
            auto dx = Converter::ArkValue<Ark_Float64>(actualX);
            auto dy = Converter::ArkValue<Ark_Float64>(actualY);
            auto image = Converter::ArkUnion<Ark_Union_ImageBitmap_PixelMap, Ark_ImageBitmap>(arkBitmap);
            accessor_->drawImage1(peer_, &image, dx, dy, dv, dv);

            ASSERT_NE(target.image.imageData, nullptr);
            EXPECT_NEAR(target.image.dx, actualX, FLT_PRECISION);
            EXPECT_NEAR(target.image.dy, actualY, FLT_PRECISION);
            EXPECT_EQ(target.image.imageData, imageData);
        }
    }
#endif
}

/**
 * @tc.name: drawImage1BitmapXYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, drawImage1BitmapWHTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->drawImage1, nullptr);
    RefPtr<MockImageBitmapPeer> bitmap = AceType::MakeRefPtr<NiceMock<MockImageBitmapPeer>>();
    Ark_ImageBitmap arkBitmap = Referenced::RawPtr(bitmap);
    Ark_Float64 dv = Converter::ArkValue<Ark_Float64>(DEFAULT_DOUBLE_VALUE);
#if !defined(PREVIEW)
    const RefPtr<PixelMap> pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    for (const auto& actualX : NUMBER_TEST_PLAN) {
        for (const auto& actualY : NUMBER_TEST_PLAN) {
            Ace::ImageInfo target;
            EXPECT_CALL(*renderingModel_, DrawPixelMap(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            EXPECT_CALL(*bitmap, GetPixelMap()).WillOnce(Return(pixelMap));
            EXPECT_CALL(*bitmap, IsSvg()).WillOnce(Return(EXPECTED_FALSE));
            auto dx = Converter::ArkValue<Ark_Float64>(actualX);
            auto dy = Converter::ArkValue<Ark_Float64>(actualY);
            auto image = Converter::ArkUnion<Ark_Union_ImageBitmap_PixelMap, Ark_ImageBitmap>(arkBitmap);
            accessor_->drawImage1(peer_, &image, dv, dv, dx, dy);

            ASSERT_NE(target.pixelMap, nullptr);
            EXPECT_NEAR(target.image.dWidth, actualX, FLT_PRECISION);
            EXPECT_NEAR(target.image.dHeight, actualY, FLT_PRECISION);
            EXPECT_EQ(target.pixelMap, pixelMap);
        }
    }
#else
    const auto imageData = std::make_shared<Ace::ImageData>();
    arkBitmap->SetImageData(imageData);
    for (const auto& actualX : NUMBER_TEST_PLAN) {
        for (const auto& actualY : NUMBER_TEST_PLAN) {
            Ace::ImageInfo target;
            EXPECT_CALL(*renderingModel_, DrawImage(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            EXPECT_CALL(*bitmap, IsSvg()).WillOnce(Return(EXPECTED_FALSE));
            auto dx = Converter::ArkValue<Ark_Float64>(actualX);
            auto dy = Converter::ArkValue<Ark_Float64>(actualY);
            auto image = Converter::ArkUnion<Ark_Union_ImageBitmap_PixelMap, Ark_ImageBitmap>(arkBitmap);
            accessor_->drawImage1(peer_, &image, dv, dv, dx, dy);

            ASSERT_NE(target.image.imageData, nullptr);
            EXPECT_NEAR(target.image.dWidth, actualX, FLT_PRECISION);
            EXPECT_NEAR(target.image.dHeight, actualY, FLT_PRECISION);
            EXPECT_EQ(target.image.imageData, imageData);
        }
    }
#endif
}

/**
 * @tc.name: drawImage1SvgXYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, drawImage1SvgXYTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->drawImage1, nullptr);
    RefPtr<MockImageBitmapPeer> bitmap = AceType::MakeRefPtr<NiceMock<MockImageBitmapPeer>>();
    Ark_ImageBitmap arkBitmap = Referenced::RawPtr(bitmap);
    const RefPtr<NG::SvgDomBase> svgDom = AceType::MakeRefPtr<MockSvgDom>();
    Ark_Float64 dv = Converter::ArkValue<Ark_Float64>(DEFAULT_DOUBLE_VALUE);
    for (const auto& actualX : NUMBER_TEST_PLAN) {
        for (const auto& actualY : NUMBER_TEST_PLAN) {
            Ace::ImageInfo target;
            EXPECT_CALL(*renderingModel_, DrawSvgImage(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            EXPECT_CALL(*bitmap, IsSvg()).WillOnce(Return(EXPECTED_TRUE));
            EXPECT_CALL(*bitmap, GetSvgDom()).WillOnce(Return(svgDom));
            EXPECT_CALL(*bitmap, GetImageFit()).WillOnce(Return(IMAGE_FIT_CENTER));
            auto dx = Converter::ArkValue<Ark_Float64>(actualX);
            auto dy = Converter::ArkValue<Ark_Float64>(actualY);
            auto image = Converter::ArkUnion<Ark_Union_ImageBitmap_PixelMap, Ark_ImageBitmap>(arkBitmap);
            accessor_->drawImage1(peer_, &image, dx, dy, dv, dv);

            ASSERT_NE(target.svgDom, nullptr);
            EXPECT_NEAR(target.image.dx, actualX, FLT_PRECISION);
            EXPECT_NEAR(target.image.dy, actualY, FLT_PRECISION);
            EXPECT_EQ(target.imageFit, IMAGE_FIT_CENTER);
            EXPECT_EQ(target.svgDom, svgDom);
        }
    }
}

/**
 * @tc.name: drawImage1SvgWHTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, drawImage1SvgWHTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->drawImage1, nullptr);
    RefPtr<MockImageBitmapPeer> bitmap = AceType::MakeRefPtr<NiceMock<MockImageBitmapPeer>>();
    Ark_ImageBitmap arkBitmap = Referenced::RawPtr(bitmap);
    const RefPtr<NG::SvgDomBase> svgDom = AceType::MakeRefPtr<MockSvgDom>();
    Ark_Float64 dv = Converter::ArkValue<Ark_Float64>(DEFAULT_DOUBLE_VALUE);
    for (const auto& actualX : NUMBER_TEST_PLAN) {
        for (const auto& actualY : NUMBER_TEST_PLAN) {
            Ace::ImageInfo target;
            EXPECT_CALL(*renderingModel_, DrawSvgImage(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            EXPECT_CALL(*bitmap, IsSvg()).WillOnce(Return(EXPECTED_TRUE));
            EXPECT_CALL(*bitmap, GetSvgDom()).WillOnce(Return(svgDom));
            EXPECT_CALL(*bitmap, GetImageFit()).WillOnce(Return(IMAGE_FIT_CENTER));
            auto dw = Converter::ArkValue<Ark_Float64>(actualX);
            auto dh = Converter::ArkValue<Ark_Float64>(actualY);
            auto image = Converter::ArkUnion<Ark_Union_ImageBitmap_PixelMap, Ark_ImageBitmap>(arkBitmap);
            accessor_->drawImage1(peer_, &image, dv, dv, dw, dh);

            ASSERT_NE(target.svgDom, nullptr);
            EXPECT_NEAR(target.image.dWidth, actualX, FLT_PRECISION);
            EXPECT_NEAR(target.image.dHeight, actualY, FLT_PRECISION);
            EXPECT_EQ(target.imageFit, IMAGE_FIT_CENTER);
            EXPECT_EQ(target.svgDom, svgDom);
        }
    }
}

#if !defined(PREVIEW)
/**
 * @tc.name: drawImage1PixelMapXYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, drawImage1PixelMapXYTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->drawImage1, nullptr);
    Ark_image_PixelMap arkPixelMap = PeerUtils::CreatePeer<image_PixelMapPeer>();
    const RefPtr<PixelMap> pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    arkPixelMap->pixelMap = pixelMap;
    Ark_Float64 dv = Converter::ArkValue<Ark_Float64>(DEFAULT_DOUBLE_VALUE);
    for (const auto& actualX : NUMBER_TEST_PLAN) {
        for (const auto& actualY : NUMBER_TEST_PLAN) {
            Ace::ImageInfo target;
            EXPECT_CALL(*renderingModel_, DrawPixelMap(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            auto dx = Converter::ArkValue<Ark_Float64>(actualX);
            auto dy = Converter::ArkValue<Ark_Float64>(actualY);
            auto image = Converter::ArkUnion<Ark_Union_ImageBitmap_PixelMap, Ark_image_PixelMap>(arkPixelMap);
            accessor_->drawImage1(peer_, &image, dx, dy, dv, dv);

            ASSERT_NE(target.pixelMap, nullptr);
            EXPECT_NEAR(target.image.dx, actualX, FLT_PRECISION);
            EXPECT_NEAR(target.image.dy, actualY, FLT_PRECISION);
            EXPECT_EQ(target.pixelMap, pixelMap);
        }
    }
}

/**
 * @tc.name: drawImage1PixelMapWHTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, drawImage1PixelMapWHTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->drawImage1, nullptr);
    Ark_image_PixelMap arkPixelMap = PeerUtils::CreatePeer<image_PixelMapPeer>();
    const RefPtr<PixelMap> pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    arkPixelMap->pixelMap = pixelMap;
    Ark_Float64 dv = Converter::ArkValue<Ark_Float64>(DEFAULT_DOUBLE_VALUE);
    for (const auto& actualX : NUMBER_TEST_PLAN) {
        for (const auto& actualY : NUMBER_TEST_PLAN) {
            Ace::ImageInfo target;
            EXPECT_CALL(*renderingModel_, DrawPixelMap(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            auto dw = Converter::ArkValue<Ark_Float64>(actualX);
            auto dh = Converter::ArkValue<Ark_Float64>(actualY);
            auto image = Converter::ArkUnion<Ark_Union_ImageBitmap_PixelMap, Ark_image_PixelMap>(arkPixelMap);
            accessor_->drawImage1(peer_, &image, dv, dv, dw, dh);

            ASSERT_NE(target.pixelMap, nullptr);
            EXPECT_NEAR(target.image.dWidth, actualX, FLT_PRECISION);
            EXPECT_NEAR(target.image.dHeight, actualY, FLT_PRECISION);
            EXPECT_EQ(target.pixelMap, pixelMap);
        }
    }
}
#endif

/**
 * @tc.name: drawImage2BitmapSXYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, drawImage2BitmapSXYTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->drawImage2, nullptr);
    RefPtr<MockImageBitmapPeer> bitmap = AceType::MakeRefPtr<NiceMock<MockImageBitmapPeer>>();
    Ark_ImageBitmap arkBitmap = Referenced::RawPtr(bitmap);
    Ark_Float64 dv = Converter::ArkValue<Ark_Float64>(DEFAULT_DOUBLE_VALUE);
#if !defined(PREVIEW)
    const RefPtr<PixelMap> pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    for (const auto& actualX : NUMBER_TEST_PLAN) {
        for (const auto& actualY : NUMBER_TEST_PLAN) {
            Ace::ImageInfo target;
            EXPECT_CALL(*renderingModel_, DrawPixelMap(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            EXPECT_CALL(*bitmap, GetPixelMap()).WillOnce(Return(pixelMap));
            EXPECT_CALL(*bitmap, IsSvg()).WillOnce(Return(EXPECTED_FALSE));
            auto dx = Converter::ArkValue<Ark_Float64>(actualX);
            auto dy = Converter::ArkValue<Ark_Float64>(actualY);
            auto image = Converter::ArkUnion<Ark_Union_ImageBitmap_PixelMap, Ark_ImageBitmap>(arkBitmap);
            accessor_->drawImage2(peer_, &image, dx, dy, dv, dv, dv, dv, dv, dv);

            ASSERT_NE(target.pixelMap, nullptr);
            EXPECT_NEAR(target.image.sx, actualX, FLT_PRECISION);
            EXPECT_NEAR(target.image.sy, actualY, FLT_PRECISION);
            EXPECT_EQ(target.pixelMap, pixelMap);
        }
    }
#else
    const auto imageData = std::make_shared<Ace::ImageData>();
    arkBitmap->SetImageData(imageData);
    for (const auto& actualX : NUMBER_TEST_PLAN) {
        for (const auto& actualY : NUMBER_TEST_PLAN) {
            Ace::ImageInfo target;
            EXPECT_CALL(*renderingModel_, DrawImage(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            EXPECT_CALL(*bitmap, IsSvg()).WillOnce(Return(EXPECTED_FALSE));
            auto dx = Converter::ArkValue<Ark_Float64>(actualX);
            auto dy = Converter::ArkValue<Ark_Float64>(actualY);
            auto image = Converter::ArkUnion<Ark_Union_ImageBitmap_PixelMap, Ark_ImageBitmap>(arkBitmap);
            accessor_->drawImage2(peer_, &image, dx, dy, dv, dv, dv, dv, dv, dv);

            ASSERT_NE(target.image.imageData, nullptr);
            EXPECT_NEAR(target.image.sx, actualX, FLT_PRECISION);
            EXPECT_NEAR(target.image.sy, actualY, FLT_PRECISION);
            EXPECT_EQ(target.image.imageData, imageData);
        }
    }
#endif
}

/**
 * @tc.name: drawImage2BitmapSWHTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, drawImage2BitmapSWHTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->drawImage2, nullptr);
    RefPtr<MockImageBitmapPeer> bitmap = AceType::MakeRefPtr<NiceMock<MockImageBitmapPeer>>();
    Ark_ImageBitmap arkBitmap = Referenced::RawPtr(bitmap);
    Ark_Float64 dv = Converter::ArkValue<Ark_Float64>(DEFAULT_DOUBLE_VALUE);
#if !defined(PREVIEW)
    const RefPtr<PixelMap> pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    for (const auto& actualX : NUMBER_TEST_PLAN) {
        for (const auto& actualY : NUMBER_TEST_PLAN) {
            Ace::ImageInfo target;
            EXPECT_CALL(*renderingModel_, DrawPixelMap(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            EXPECT_CALL(*bitmap, GetPixelMap()).WillOnce(Return(pixelMap));
            EXPECT_CALL(*bitmap, IsSvg()).WillOnce(Return(EXPECTED_FALSE));
            auto dx = Converter::ArkValue<Ark_Float64>(actualX);
            auto dy = Converter::ArkValue<Ark_Float64>(actualY);
            auto image = Converter::ArkUnion<Ark_Union_ImageBitmap_PixelMap, Ark_ImageBitmap>(arkBitmap);
            accessor_->drawImage2(peer_, &image, dv, dv, dx, dy, dv, dv, dv, dv);

            ASSERT_NE(target.pixelMap, nullptr);
            EXPECT_NEAR(target.image.sWidth, actualX, FLT_PRECISION);
            EXPECT_NEAR(target.image.sHeight, actualY, FLT_PRECISION);
            EXPECT_EQ(target.pixelMap, pixelMap);
        }
    }
#else
    const auto imageData = std::make_shared<Ace::ImageData>();
    arkBitmap->SetImageData(imageData);
    for (const auto& actualX : NUMBER_TEST_PLAN) {
        for (const auto& actualY : NUMBER_TEST_PLAN) {
            Ace::ImageInfo target;
            EXPECT_CALL(*renderingModel_, DrawImage(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            EXPECT_CALL(*bitmap, IsSvg()).WillOnce(Return(EXPECTED_FALSE));
            auto dx = Converter::ArkValue<Ark_Float64>(actualX);
            auto dy = Converter::ArkValue<Ark_Float64>(actualY);
            auto image = Converter::ArkUnion<Ark_Union_ImageBitmap_PixelMap, Ark_ImageBitmap>(arkBitmap);
            accessor_->drawImage2(peer_, &image, dv, dv, dx, dy, dv, dv, dv, dv);

            ASSERT_NE(target.image.imageData, nullptr);
            EXPECT_NEAR(target.image.sWidth, actualX, FLT_PRECISION);
            EXPECT_NEAR(target.image.sHeight, actualY, FLT_PRECISION);
            EXPECT_EQ(target.image.imageData, imageData);
        }
    }
#endif
}

/**
 * @tc.name: drawImage2BitmapXYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, drawImage2BitmapXYTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->drawImage2, nullptr);
    RefPtr<MockImageBitmapPeer> bitmap = AceType::MakeRefPtr<NiceMock<MockImageBitmapPeer>>();
    Ark_ImageBitmap arkBitmap = Referenced::RawPtr(bitmap);
    Ark_Float64 dv = Converter::ArkValue<Ark_Float64>(DEFAULT_DOUBLE_VALUE);
#if !defined(PREVIEW)
    const RefPtr<PixelMap> pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    for (const auto& actualX : NUMBER_TEST_PLAN) {
        for (const auto& actualY : NUMBER_TEST_PLAN) {
            Ace::ImageInfo target;
            EXPECT_CALL(*renderingModel_, DrawPixelMap(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            EXPECT_CALL(*bitmap, GetPixelMap()).WillOnce(Return(pixelMap));
            EXPECT_CALL(*bitmap, IsSvg()).WillOnce(Return(EXPECTED_FALSE));
            auto dx = Converter::ArkValue<Ark_Float64>(actualX);
            auto dy = Converter::ArkValue<Ark_Float64>(actualY);
            auto image = Converter::ArkUnion<Ark_Union_ImageBitmap_PixelMap, Ark_ImageBitmap>(arkBitmap);
            accessor_->drawImage2(peer_, &image, dv, dv, dv, dv, dx, dy, dv, dv);

            ASSERT_NE(target.pixelMap, nullptr);
            EXPECT_NEAR(target.image.dx, actualX, FLT_PRECISION);
            EXPECT_NEAR(target.image.dy, actualY, FLT_PRECISION);
            EXPECT_EQ(target.pixelMap, pixelMap);
        }
    }
#else
    const auto imageData = std::make_shared<Ace::ImageData>();
    arkBitmap->SetImageData(imageData);
    for (const auto& actualX : NUMBER_TEST_PLAN) {
        for (const auto& actualY : NUMBER_TEST_PLAN) {
            Ace::ImageInfo target;
            EXPECT_CALL(*renderingModel_, DrawImage(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            EXPECT_CALL(*bitmap, IsSvg()).WillOnce(Return(EXPECTED_FALSE));
            auto dx = Converter::ArkValue<Ark_Float64>(actualX);
            auto dy = Converter::ArkValue<Ark_Float64>(actualY);
            auto image = Converter::ArkUnion<Ark_Union_ImageBitmap_PixelMap, Ark_ImageBitmap>(arkBitmap);
            accessor_->drawImage2(peer_, &image, dv, dv, dv, dv, dx, dy, dv, dv);

            ASSERT_NE(target.image.imageData, nullptr);
            EXPECT_NEAR(target.image.dx, actualX, FLT_PRECISION);
            EXPECT_NEAR(target.image.dy, actualY, FLT_PRECISION);
            EXPECT_EQ(target.image.imageData, imageData);
        }
    }
#endif
}

/**
 * @tc.name: drawImage2BitmapWHTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, drawImage2BitmapWHTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->drawImage2, nullptr);
    RefPtr<MockImageBitmapPeer> bitmap = AceType::MakeRefPtr<NiceMock<MockImageBitmapPeer>>();
    Ark_ImageBitmap arkBitmap = Referenced::RawPtr(bitmap);
    Ark_Float64 dv = Converter::ArkValue<Ark_Float64>(DEFAULT_DOUBLE_VALUE);
#if !defined(PREVIEW)
    const RefPtr<PixelMap> pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    for (const auto& actualX : NUMBER_TEST_PLAN) {
        for (const auto& actualY : NUMBER_TEST_PLAN) {
            Ace::ImageInfo target;
            EXPECT_CALL(*renderingModel_, DrawPixelMap(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            EXPECT_CALL(*bitmap, GetPixelMap()).WillOnce(Return(pixelMap));
            EXPECT_CALL(*bitmap, IsSvg()).WillOnce(Return(EXPECTED_FALSE));
            auto dx = Converter::ArkValue<Ark_Float64>(actualX);
            auto dy = Converter::ArkValue<Ark_Float64>(actualY);
            auto image = Converter::ArkUnion<Ark_Union_ImageBitmap_PixelMap, Ark_ImageBitmap>(arkBitmap);
            accessor_->drawImage2(peer_, &image, dv, dv, dv, dv, dv, dv, dx, dy);

            ASSERT_NE(target.pixelMap, nullptr);
            EXPECT_NEAR(target.image.dWidth, actualX, FLT_PRECISION);
            EXPECT_NEAR(target.image.dHeight, actualY, FLT_PRECISION);
            EXPECT_EQ(target.pixelMap, pixelMap);
        }
    }
#else
    const auto imageData = std::make_shared<Ace::ImageData>();
    arkBitmap->SetImageData(imageData);
    for (const auto& actualX : NUMBER_TEST_PLAN) {
        for (const auto& actualY : NUMBER_TEST_PLAN) {
            Ace::ImageInfo target;
            EXPECT_CALL(*renderingModel_, DrawImage(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            EXPECT_CALL(*bitmap, IsSvg()).WillOnce(Return(EXPECTED_FALSE));
            auto dx = Converter::ArkValue<Ark_Float64>(actualX);
            auto dy = Converter::ArkValue<Ark_Float64>(actualY);
            auto image = Converter::ArkUnion<Ark_Union_ImageBitmap_PixelMap, Ark_ImageBitmap>(arkBitmap);
            accessor_->drawImage2(peer_, &image, dv, dv, dv, dv, dv, dv, dx, dy);

            ASSERT_NE(target.image.imageData, nullptr);
            EXPECT_NEAR(target.image.dWidth, actualX, FLT_PRECISION);
            EXPECT_NEAR(target.image.dHeight, actualY, FLT_PRECISION);
            EXPECT_EQ(target.image.imageData, imageData);
        }
    }
#endif
}

/**
 * @tc.name: drawImage2SvgSXYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, drawImage2SvgSXYTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->drawImage2, nullptr);
    RefPtr<MockImageBitmapPeer> bitmap = AceType::MakeRefPtr<NiceMock<MockImageBitmapPeer>>();
    Ark_ImageBitmap arkBitmap = Referenced::RawPtr(bitmap);
    const RefPtr<NG::SvgDomBase> svgDom = AceType::MakeRefPtr<MockSvgDom>();
    Ark_Float64 dv = Converter::ArkValue<Ark_Float64>(DEFAULT_DOUBLE_VALUE);
    for (const auto& actualX : NUMBER_TEST_PLAN) {
        for (const auto& actualY : NUMBER_TEST_PLAN) {
            Ace::ImageInfo target;
            EXPECT_CALL(*renderingModel_, DrawSvgImage(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            EXPECT_CALL(*bitmap, IsSvg()).WillOnce(Return(EXPECTED_TRUE));
            EXPECT_CALL(*bitmap, GetSvgDom()).WillOnce(Return(svgDom));
            EXPECT_CALL(*bitmap, GetImageFit()).WillOnce(Return(IMAGE_FIT_CENTER));
            auto dx = Converter::ArkValue<Ark_Float64>(actualX);
            auto dy = Converter::ArkValue<Ark_Float64>(actualY);
            auto image = Converter::ArkUnion<Ark_Union_ImageBitmap_PixelMap, Ark_ImageBitmap>(arkBitmap);
            accessor_->drawImage2(peer_, &image, dx, dy, dv, dv, dv, dv, dv, dv);

            ASSERT_NE(target.svgDom, nullptr);
            EXPECT_NEAR(target.image.sx, actualX, FLT_PRECISION);
            EXPECT_NEAR(target.image.sy, actualY, FLT_PRECISION);
            EXPECT_EQ(target.imageFit, IMAGE_FIT_CENTER);
            EXPECT_EQ(target.svgDom, svgDom);
        }
    }
}

/**
 * @tc.name: drawImage2SvgSWHTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, drawImage2SvgSWHTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->drawImage2, nullptr);
    RefPtr<MockImageBitmapPeer> bitmap = AceType::MakeRefPtr<NiceMock<MockImageBitmapPeer>>();
    Ark_ImageBitmap arkBitmap = Referenced::RawPtr(bitmap);
    const RefPtr<NG::SvgDomBase> svgDom = AceType::MakeRefPtr<MockSvgDom>();
    Ark_Float64 dv = Converter::ArkValue<Ark_Float64>(DEFAULT_DOUBLE_VALUE);
    for (const auto& actualX : NUMBER_TEST_PLAN) {
        for (const auto& actualY : NUMBER_TEST_PLAN) {
            Ace::ImageInfo target;
            EXPECT_CALL(*renderingModel_, DrawSvgImage(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            EXPECT_CALL(*bitmap, IsSvg()).WillOnce(Return(EXPECTED_TRUE));
            EXPECT_CALL(*bitmap, GetSvgDom()).WillOnce(Return(svgDom));
            EXPECT_CALL(*bitmap, GetImageFit()).WillOnce(Return(IMAGE_FIT_CENTER));
            auto dx = Converter::ArkValue<Ark_Float64>(actualX);
            auto dy = Converter::ArkValue<Ark_Float64>(actualY);
            auto image = Converter::ArkUnion<Ark_Union_ImageBitmap_PixelMap, Ark_ImageBitmap>(arkBitmap);
            accessor_->drawImage2(peer_, &image, dv, dv, dx, dy, dv, dv, dv, dv);

            ASSERT_NE(target.svgDom, nullptr);
            EXPECT_NEAR(target.image.sWidth, actualX, FLT_PRECISION);
            EXPECT_NEAR(target.image.sHeight, actualY, FLT_PRECISION);
            EXPECT_EQ(target.imageFit, IMAGE_FIT_CENTER);
            EXPECT_EQ(target.svgDom, svgDom);
        }
    }
}

/**
 * @tc.name: drawImage2SvgXYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, drawImage2SvgXYTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->drawImage2, nullptr);
    RefPtr<MockImageBitmapPeer> bitmap = AceType::MakeRefPtr<NiceMock<MockImageBitmapPeer>>();
    Ark_ImageBitmap arkBitmap = Referenced::RawPtr(bitmap);
    const RefPtr<NG::SvgDomBase> svgDom = AceType::MakeRefPtr<MockSvgDom>();
    Ark_Float64 dv = Converter::ArkValue<Ark_Float64>(DEFAULT_DOUBLE_VALUE);
    for (const auto& actualX : NUMBER_TEST_PLAN) {
        for (const auto& actualY : NUMBER_TEST_PLAN) {
            Ace::ImageInfo target;
            EXPECT_CALL(*renderingModel_, DrawSvgImage(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            EXPECT_CALL(*bitmap, IsSvg()).WillOnce(Return(EXPECTED_TRUE));
            EXPECT_CALL(*bitmap, GetSvgDom()).WillOnce(Return(svgDom));
            EXPECT_CALL(*bitmap, GetImageFit()).WillOnce(Return(IMAGE_FIT_CENTER));
            auto dx = Converter::ArkValue<Ark_Float64>(actualX);
            auto dy = Converter::ArkValue<Ark_Float64>(actualY);
            auto image = Converter::ArkUnion<Ark_Union_ImageBitmap_PixelMap, Ark_ImageBitmap>(arkBitmap);
            accessor_->drawImage2(peer_, &image, dv, dv, dv, dv, dx, dy, dv, dv);

            ASSERT_NE(target.svgDom, nullptr);
            EXPECT_NEAR(target.image.dx, actualX, FLT_PRECISION);
            EXPECT_NEAR(target.image.dy, actualY, FLT_PRECISION);
            EXPECT_EQ(target.imageFit, IMAGE_FIT_CENTER);
            EXPECT_EQ(target.svgDom, svgDom);
        }
    }
}

/**
 * @tc.name: drawImage2SvgWHTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, drawImage2SvgWHTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->drawImage2, nullptr);
    RefPtr<MockImageBitmapPeer> bitmap = AceType::MakeRefPtr<NiceMock<MockImageBitmapPeer>>();
    Ark_ImageBitmap arkBitmap = Referenced::RawPtr(bitmap);
    const RefPtr<NG::SvgDomBase> svgDom = AceType::MakeRefPtr<MockSvgDom>();
    Ark_Float64 dv = Converter::ArkValue<Ark_Float64>(DEFAULT_DOUBLE_VALUE);
    for (const auto& actualX : NUMBER_TEST_PLAN) {
        for (const auto& actualY : NUMBER_TEST_PLAN) {
            Ace::ImageInfo target;
            EXPECT_CALL(*renderingModel_, DrawSvgImage(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            EXPECT_CALL(*bitmap, IsSvg()).WillOnce(Return(EXPECTED_TRUE));
            EXPECT_CALL(*bitmap, GetSvgDom()).WillOnce(Return(svgDom));
            EXPECT_CALL(*bitmap, GetImageFit()).WillOnce(Return(IMAGE_FIT_CENTER));
            auto dx = Converter::ArkValue<Ark_Float64>(actualX);
            auto dy = Converter::ArkValue<Ark_Float64>(actualY);
            auto image = Converter::ArkUnion<Ark_Union_ImageBitmap_PixelMap, Ark_ImageBitmap>(arkBitmap);
            accessor_->drawImage2(peer_, &image, dv, dv, dv, dv, dv, dv, dx, dy);

            ASSERT_NE(target.svgDom, nullptr);
            EXPECT_NEAR(target.image.dWidth, actualX, FLT_PRECISION);
            EXPECT_NEAR(target.image.dHeight, actualY, FLT_PRECISION);
            EXPECT_EQ(target.imageFit, IMAGE_FIT_CENTER);
            EXPECT_EQ(target.svgDom, svgDom);
        }
    }
}

#if !defined(PREVIEW)
/**
 * @tc.name: drawImage2PixelMapSXYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, drawImage2PixelMapSXYTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->drawImage2, nullptr);
    Ark_image_PixelMap arkPixelMap = PeerUtils::CreatePeer<image_PixelMapPeer>();
    const RefPtr<PixelMap> pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    arkPixelMap->pixelMap = pixelMap;
    Ark_Float64 dv = Converter::ArkValue<Ark_Float64>(DEFAULT_DOUBLE_VALUE);
    for (const auto& actualX : NUMBER_TEST_PLAN) {
        for (const auto& actualY : NUMBER_TEST_PLAN) {
            Ace::ImageInfo target;
            EXPECT_CALL(*renderingModel_, DrawPixelMap(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            auto dx = Converter::ArkValue<Ark_Float64>(actualX);
            auto dy = Converter::ArkValue<Ark_Float64>(actualY);
            auto image = Converter::ArkUnion<Ark_Union_ImageBitmap_PixelMap, Ark_image_PixelMap>(arkPixelMap);
            accessor_->drawImage2(peer_, &image, dx, dy, dv, dv, dv, dv, dv, dv);

            ASSERT_NE(target.pixelMap, nullptr);
            EXPECT_NEAR(target.image.sx, actualX, FLT_PRECISION);
            EXPECT_NEAR(target.image.sy, actualY, FLT_PRECISION);
            EXPECT_EQ(target.pixelMap, pixelMap);
        }
    }
}

/**
 * @tc.name: drawImage2PixelMapSWHTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, drawImage2PixelMapSWHTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->drawImage2, nullptr);
    Ark_image_PixelMap arkPixelMap = PeerUtils::CreatePeer<image_PixelMapPeer>();
    const RefPtr<PixelMap> pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    arkPixelMap->pixelMap = pixelMap;
    Ark_Float64 dv = Converter::ArkValue<Ark_Float64>(DEFAULT_DOUBLE_VALUE);
    for (const auto& actualX : NUMBER_TEST_PLAN) {
        for (const auto& actualY : NUMBER_TEST_PLAN) {
            Ace::ImageInfo target;
            EXPECT_CALL(*renderingModel_, DrawPixelMap(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            auto dx = Converter::ArkValue<Ark_Float64>(actualX);
            auto dy = Converter::ArkValue<Ark_Float64>(actualY);
            auto image = Converter::ArkUnion<Ark_Union_ImageBitmap_PixelMap, Ark_image_PixelMap>(arkPixelMap);
            accessor_->drawImage2(peer_, &image, dv, dv, dx, dy, dv, dv, dv, dv);

            ASSERT_NE(target.pixelMap, nullptr);
            EXPECT_NEAR(target.image.sWidth, actualX, FLT_PRECISION);
            EXPECT_NEAR(target.image.sHeight, actualY, FLT_PRECISION);
            EXPECT_EQ(target.pixelMap, pixelMap);
        }
    }
}

/**
 * @tc.name: drawImage2PixelMapXYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, drawImage2PixelMapXYTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->drawImage2, nullptr);
    Ark_image_PixelMap arkPixelMap = PeerUtils::CreatePeer<image_PixelMapPeer>();
    const RefPtr<PixelMap> pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    arkPixelMap->pixelMap = pixelMap;
    Ark_Float64 dv = Converter::ArkValue<Ark_Float64>(DEFAULT_DOUBLE_VALUE);
    for (const auto& actualX : NUMBER_TEST_PLAN) {
        for (const auto& actualY : NUMBER_TEST_PLAN) {
            Ace::ImageInfo target;
            EXPECT_CALL(*renderingModel_, DrawPixelMap(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            auto dx = Converter::ArkValue<Ark_Float64>(actualX);
            auto dy = Converter::ArkValue<Ark_Float64>(actualY);
            auto image = Converter::ArkUnion<Ark_Union_ImageBitmap_PixelMap, Ark_image_PixelMap>(arkPixelMap);
            accessor_->drawImage2(peer_, &image, dv, dv, dv, dv, dx, dy, dv, dv);

            ASSERT_NE(target.pixelMap, nullptr);
            EXPECT_NEAR(target.image.dx, actualX, FLT_PRECISION);
            EXPECT_NEAR(target.image.dy, actualY, FLT_PRECISION);
            EXPECT_EQ(target.pixelMap, pixelMap);
        }
    }
}

/**
 * @tc.name: drawImage2PixelMapWHTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, drawImage2PixelMapWHTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->drawImage2, nullptr);
    Ark_image_PixelMap arkPixelMap = PeerUtils::CreatePeer<image_PixelMapPeer>();
    const RefPtr<PixelMap> pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    arkPixelMap->pixelMap = pixelMap;
    Ark_Float64 dv = Converter::ArkValue<Ark_Float64>(DEFAULT_DOUBLE_VALUE);
    for (const auto& actualX : NUMBER_TEST_PLAN) {
        for (const auto& actualY : NUMBER_TEST_PLAN) {
            Ace::ImageInfo target;
            EXPECT_CALL(*renderingModel_, DrawPixelMap(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            auto dx = Converter::ArkValue<Ark_Float64>(actualX);
            auto dy = Converter::ArkValue<Ark_Float64>(actualY);
            auto image = Converter::ArkUnion<Ark_Union_ImageBitmap_PixelMap, Ark_image_PixelMap>(arkPixelMap);
            accessor_->drawImage2(peer_, &image, dv, dv, dv, dv, dv, dv, dx, dy);

            ASSERT_NE(target.pixelMap, nullptr);
            EXPECT_NEAR(target.image.dWidth, actualX, FLT_PRECISION);
            EXPECT_NEAR(target.image.dHeight, actualY, FLT_PRECISION);
            EXPECT_EQ(target.pixelMap, pixelMap);
        }
    }
}
#endif

/**
 * @tc.name: getLineDashTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, getLineDashTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getLineDash, nullptr);
    for (const auto& [actual, _] : ARRAY_LINE_DASH_TEST_PLAN) {
        EXPECT_CALL(*renderingModel_, GetLineDash()).WillOnce(Return(actual));
        Array_Float64 result = accessor_->getLineDash(peer_);

        const auto segments = Converter::Convert<std::vector<double>>(result);
        ASSERT_EQ(segments.size(), actual.size());
        for (size_t i = 0; i < segments.size(); i++) {
            EXPECT_NEAR(segments[i], actual[i], FLT_PRECISION);
        }
    }
    // with density
    double density = DENSITY_1_25;
    ChangeDensity(density);
    for (const auto& [actual, _] : ARRAY_LINE_DASH_TEST_PLAN) {
        EXPECT_CALL(*renderingModel_, GetLineDash()).WillOnce(Return(actual));
        Array_Float64 result = accessor_->getLineDash(peer_);

        const auto segments = Converter::Convert<std::vector<double>>(result);
        ASSERT_EQ(segments.size(), actual.size());
        for (size_t i = 0; i < segments.size(); i++) {
            EXPECT_NEAR(segments[i], actual[i] / density, FLT_PRECISION);
        }
    }
}

/**
 * @tc.name: measureTextTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, measureTextTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->measureText, nullptr);
    for (const auto& [actual, expected] : ARK_STRING_TEST_PLAN) {
        for (const auto& actualW : NUMBER_TEST_PLAN) {
            TextMetrics textMetrics = { .width = actualW };
            std::string target;
            EXPECT_CALL(*renderingModel_, GetMeasureTextMetrics(_, _))
                .WillOnce(DoAll(SaveArg<1>(&target), Return(textMetrics)));
            Ark_TextMetrics result = accessor_->measureText(peer_, &actual);

            TextMetrics actualMetrics = Converter::Convert<TextMetrics>(result);
            EXPECT_EQ(target, expected);
            EXPECT_NEAR(actualMetrics.width, textMetrics.width, FLT_PRECISION);
        }
    }
    // with density
    double density = DENSITY_NEGATIVE;
    ChangeDensity(density);
    for (const auto& [actual, expected] : ARK_STRING_TEST_PLAN) {
        EXPECT_CALL(*renderingModel_, GetMeasureTextMetrics(_, _)).Times(0);
        Ark_TextMetrics result = accessor_->measureText(peer_, &actual);

        TextMetrics actualMetrics = Converter::Convert<TextMetrics>(result);
        EXPECT_NEAR(actualMetrics.width, DEFAULT_DOUBLE_ZERO, FLT_PRECISION);
        EXPECT_NEAR(actualMetrics.height, DEFAULT_DOUBLE_ZERO, FLT_PRECISION);
    }
}

/**
 * @tc.name: setFillStyleStringTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, setFillStyleStringTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setFillStyle, nullptr);
    for (const auto& [actual, expected, pass] : STYLE_STRING_TEST_PLAN) {
        if (pass) {
            Ace::Color target;
            bool targetFlag = false;
            EXPECT_CALL(*renderingModel_, SetFillColor(_, _))
                .WillOnce(DoAll(SaveArg<0>(&target), SaveArg<1>(&targetFlag)));
            auto style =
                Converter::ArkUnion<Ark_Union_String_Color_I32_CanvasGradient_CanvasPattern, Ark_String>(actual);
            accessor_->setFillStyle(peer_, &style);
            EXPECT_EQ(target, expected);
            EXPECT_TRUE(targetFlag);
        } else {
            EXPECT_CALL(*renderingModel_, SetFillColor(_, _)).Times(0);
            auto style =
                Converter::ArkUnion<Ark_Union_String_Color_I32_CanvasGradient_CanvasPattern, Ark_String>(actual);
            accessor_->setFillStyle(peer_, &style);
        }
    }
}

/**
 * @tc.name: setFillStyleNumberTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, DISABLED_setFillStyleNumberTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setFillStyle, nullptr);
    for (const auto& [actual, expected] : STYLE_NUMBER_TEST_PLAN) {
        Ace::Color target;
        bool targetFlag = false;
        EXPECT_CALL(*renderingModel_, SetFillColor(_, _)).WillOnce(DoAll(SaveArg<0>(&target), SaveArg<1>(&targetFlag)));
        auto style = Converter::ArkUnion<Ark_Union_String_Color_I32_CanvasGradient_CanvasPattern, Ark_Int32>(actual);
        accessor_->setFillStyle(peer_, &style);
        EXPECT_EQ(target, expected);
        EXPECT_FALSE(targetFlag);
    }
}

/**
 * @tc.name: setFillStyleColorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, DISABLED_setFillStyleColorTest, TestSize.Level1)
{
#ifdef WRONG_GEN
    ASSERT_NE(accessor_->setFillStyle, nullptr);
    for (const auto& [actual, expected] : STYLE_COLOR_TEST_PLAN) {
        Ace::Color target;
        bool targetFlag = false;
        EXPECT_CALL(*renderingModel_, SetFillColor(_, _)).WillOnce(DoAll(SaveArg<0>(&target), SaveArg<1>(&targetFlag)));
        auto style = Converter::ArkUnion<Ark_Union_String_Color_I32_CanvasGradient_CanvasPattern, Ark_Color>(actual);
        accessor_->setFillStyle(peer_, &style);
        EXPECT_EQ(target, expected);
        EXPECT_TRUE(targetFlag);
    }
#endif
}

/**
 * @tc.name: setFillStyleGradientTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, setFillStyleGradientTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setFillStyle, nullptr);
    Ark_CanvasGradient arkGradient = new CanvasGradientPeer();
    const auto gradient = std::make_shared<Ace::Gradient>();
    arkGradient->SetGradient(gradient);
    std::shared_ptr<Ace::Gradient> target;
    EXPECT_CALL(*renderingModel_, SetFillGradient(_)).WillOnce(DoAll(SaveArg<0>(&target)));
    auto style =
        Converter::ArkUnion<Ark_Union_String_Color_I32_CanvasGradient_CanvasPattern, Ark_CanvasGradient>(arkGradient);
    accessor_->setFillStyle(peer_, &style);

    EXPECT_EQ(target.get(), gradient.get());
}

/**
 * @tc.name: setFillStylePatternStrTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, setFillStylePatternStrTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setFillStyle, nullptr);
    RefPtr<MockImageBitmapPeerStyle> bitmap = AceType::MakeRefPtr<MockImageBitmapPeerStyle>();
    Ark_ImageBitmap arkBitmap = Referenced::RawPtr(bitmap);
    auto pattern = Referenced::MakeRefPtr<CanvasPatternPeer>();
    Ark_CanvasPattern arkPattern = Referenced::RawPtr(pattern);
    GeneratedModifier::CanvasRendererPeerImpl* peer =
        reinterpret_cast<GeneratedModifier::CanvasRendererPeerImpl*>(peer_);
    const auto actualW = DEFAULT_DOUBLE_VALUE;
    const auto actualH = DEFAULT_DOUBLE_VALUE;
    for (const auto& [actualArkStr_, actualStr] : ARK_STRING_TEST_PLAN) {
        for (const auto& [actualArkRpt, actualRpt] : IMAGE_SMOOTHING_TEST_PLAN) {
            std::shared_ptr<Ace::Pattern> target;
            EXPECT_CALL(*renderingModel_, SetFillPattern(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            EXPECT_CALL(*bitmap, GetSrc()).WillOnce(Return(actualStr));
#if !defined(PREVIEW)
            const RefPtr<PixelMap> pixelMap = AceType::MakeRefPtr<MockPixelMap>();
            EXPECT_CALL(*bitmap, GetPixelMap()).WillOnce(Return(pixelMap));
#else
            EXPECT_CALL(*bitmap, GetPixelMap()).Times(0);
#endif
            bitmap->SetWidth(actualW);
            bitmap->SetHeight(actualH);
            auto repetition = std::make_optional<std::string>(actualRpt);
            peer->CreatePattern(arkBitmap, arkPattern, repetition);
            auto style =
                Converter::ArkUnion<Ark_Union_String_Color_I32_CanvasGradient_CanvasPattern, Ark_CanvasPattern>(
                    arkPattern);
            accessor_->setFillStyle(peer_, &style);

            EXPECT_EQ(target->GetImageWidth(), actualW);
            EXPECT_EQ(target->GetImageHeight(), actualH);
            EXPECT_EQ(target->GetImgSrc(), actualStr);
            EXPECT_EQ(target->GetRepetition(), actualRpt);
#if !defined(PREVIEW)
            ASSERT_NE(target->GetPixelMap(), nullptr);
            ASSERT_NE(pixelMap, nullptr);
            EXPECT_EQ(target->GetPixelMap(), pixelMap);
#endif
        }
    }
}

/**
 * @tc.name: setFillStylePatternWHTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, setFillStylePatternWHTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setFillStyle, nullptr);
    RefPtr<MockImageBitmapPeerStyle> bitmap = AceType::MakeRefPtr<MockImageBitmapPeerStyle>();
    Ark_ImageBitmap arkBitmap = Referenced::RawPtr(bitmap);
    auto pattern = Referenced::MakeRefPtr<CanvasPatternPeer>();
    Ark_CanvasPattern arkPattern = Referenced::RawPtr(pattern);
    GeneratedModifier::CanvasRendererPeerImpl* peer =
        reinterpret_cast<GeneratedModifier::CanvasRendererPeerImpl*>(peer_);
    auto actualStr = DEFAULT_STRING_VALUE;
    auto actualRpt = REPEAT_STRING;
    for (const auto& actualW : NUMBER_TEST_PLAN) {
        for (const auto& actualH : NUMBER_TEST_PLAN) {
            std::shared_ptr<Ace::Pattern> target;
            EXPECT_CALL(*renderingModel_, SetFillPattern(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            EXPECT_CALL(*bitmap, GetSrc()).WillOnce(Return(actualStr));
#if !defined(PREVIEW)
            const RefPtr<PixelMap> pixelMap = AceType::MakeRefPtr<MockPixelMap>();
            EXPECT_CALL(*bitmap, GetPixelMap()).WillOnce(Return(pixelMap));
#else
            EXPECT_CALL(*bitmap, GetPixelMap()).Times(0);
#endif
            bitmap->SetWidth(actualW);
            bitmap->SetHeight(actualH);
            auto repetition = std::make_optional<std::string>(actualRpt);
            peer->CreatePattern(arkBitmap, arkPattern, repetition);
            auto style =
                Converter::ArkUnion<Ark_Union_String_Color_I32_CanvasGradient_CanvasPattern, Ark_CanvasPattern>(
                    arkPattern);
            accessor_->setFillStyle(peer_, &style);

            EXPECT_EQ(target->GetImageWidth(), actualW);
            EXPECT_EQ(target->GetImageHeight(), actualH);
            EXPECT_EQ(target->GetImgSrc(), actualStr);
            EXPECT_EQ(target->GetRepetition(), actualRpt);

#if !defined(PREVIEW)
            ASSERT_NE(target->GetPixelMap(), nullptr);
            ASSERT_NE(pixelMap, nullptr);
            EXPECT_EQ(target->GetPixelMap(), pixelMap);
#endif
        }
    }
}

/**
 * @tc.name: setStrokeStyleStringTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, setStrokeStyleStringTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setStrokeStyle, nullptr);
    for (const auto& [actual, expected, pass] : STYLE_STRING_TEST_PLAN) {
        if (pass) {
            Ace::Color target;
            bool targetFlag = false;
            EXPECT_CALL(*renderingModel_, SetStrokeColor(_, _))
                .WillOnce(DoAll(SaveArg<0>(&target), SaveArg<1>(&targetFlag)));
            auto style =
                Converter::ArkUnion<Ark_Union_String_Color_I32_CanvasGradient_CanvasPattern, Ark_String>(actual);
            accessor_->setStrokeStyle(peer_, &style);
            EXPECT_EQ(target, expected);
            EXPECT_TRUE(targetFlag);
        } else {
            EXPECT_CALL(*renderingModel_, SetStrokeColor(_, _)).Times(0);
            auto style =
                Converter::ArkUnion<Ark_Union_String_Color_I32_CanvasGradient_CanvasPattern, Ark_String>(actual);
            accessor_->setStrokeStyle(peer_, &style);
        }
    }
}

/**
 * @tc.name: setStrokeStyleNumberTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, DISABLED_setStrokeStyleNumberTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setStrokeStyle, nullptr);
    for (const auto& [actual, expected] : STYLE_NUMBER_TEST_PLAN) {
        Ace::Color target;
        bool targetFlag = false;
        EXPECT_CALL(*renderingModel_, SetStrokeColor(_, _))
            .WillOnce(DoAll(SaveArg<0>(&target), SaveArg<1>(&targetFlag)));
        auto style = Converter::ArkUnion<Ark_Union_String_Color_I32_CanvasGradient_CanvasPattern, Ark_Int32>(actual);
        accessor_->setStrokeStyle(peer_, &style);
        EXPECT_EQ(target, expected);
        EXPECT_FALSE(targetFlag);
    }
}

/**
 * @tc.name: setStrokeStyleColorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, setStrokeStyleColorTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setStrokeStyle, nullptr);
    for (const auto& [actual, expected] : STYLE_COLOR_TEST_PLAN) {
        Ace::Color target;
        bool targetFlag = false;
        EXPECT_CALL(*renderingModel_, SetStrokeColor(_, _))
            .WillOnce(DoAll(SaveArg<0>(&target), SaveArg<1>(&targetFlag)));
        auto style = Converter::ArkUnion<Ark_Union_String_Color_I32_CanvasGradient_CanvasPattern, Ark_Color>(actual);
        accessor_->setStrokeStyle(peer_, &style);
        EXPECT_EQ(target, expected);
        EXPECT_TRUE(targetFlag);
    }
}

/**
 * @tc.name: setStrokeStyleGradientTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, setStrokeStyleGradientTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setStrokeStyle, nullptr);
    Ark_CanvasGradient arkGradient = new CanvasGradientPeer();
    const auto gradient = std::make_shared<Ace::Gradient>();
    arkGradient->SetGradient(gradient);
    std::shared_ptr<Ace::Gradient> target;
    EXPECT_CALL(*renderingModel_, SetStrokeGradient(_)).WillOnce(DoAll(SaveArg<0>(&target)));
    auto style =
        Converter::ArkUnion<Ark_Union_String_Color_I32_CanvasGradient_CanvasPattern, Ark_CanvasGradient>(arkGradient);
    accessor_->setStrokeStyle(peer_, &style);
    EXPECT_EQ(target.get(), gradient.get());
}

/**
 * @tc.name: setStrokeStylePatternStrTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, setStrokeStylePatternStrTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setStrokeStyle, nullptr);
    RefPtr<MockImageBitmapPeerStyle> bitmap = AceType::MakeRefPtr<MockImageBitmapPeerStyle>();
    Ark_ImageBitmap arkBitmap = Referenced::RawPtr(bitmap);
    auto pattern = Referenced::MakeRefPtr<CanvasPatternPeer>();
    Ark_CanvasPattern arkPattern = Referenced::RawPtr(pattern);
    GeneratedModifier::CanvasRendererPeerImpl* peer =
        reinterpret_cast<GeneratedModifier::CanvasRendererPeerImpl*>(peer_);
    const auto actualW = DEFAULT_DOUBLE_VALUE;
    const auto actualH = DEFAULT_DOUBLE_VALUE;
    for (const auto& [actualArkStr_, actualStr] : ARK_STRING_TEST_PLAN) {
        for (const auto& [actualArkRpt, actualRpt] : IMAGE_SMOOTHING_TEST_PLAN) {
            std::shared_ptr<Ace::Pattern> target;
            EXPECT_CALL(*renderingModel_, SetStrokePattern(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            EXPECT_CALL(*bitmap, GetSrc()).WillOnce(Return(actualStr));
#if !defined(PREVIEW)
            const RefPtr<PixelMap> pixelMap = AceType::MakeRefPtr<MockPixelMap>();
            EXPECT_CALL(*bitmap, GetPixelMap()).WillOnce(Return(pixelMap));
#else
            EXPECT_CALL(*bitmap, GetPixelMap()).Times(0);
#endif
            bitmap->SetWidth(actualW);
            bitmap->SetHeight(actualH);
            auto repetition = std::make_optional<std::string>(actualRpt);
            peer->CreatePattern(arkBitmap, arkPattern, repetition);
            auto style =
                Converter::ArkUnion<Ark_Union_String_Color_I32_CanvasGradient_CanvasPattern, Ark_CanvasPattern>(
                    arkPattern);
            accessor_->setStrokeStyle(peer_, &style);

            EXPECT_EQ(target->GetImageWidth(), actualW);
            EXPECT_EQ(target->GetImageHeight(), actualH);
            EXPECT_EQ(target->GetImgSrc(), actualStr);
            EXPECT_EQ(target->GetRepetition(), actualRpt);
#if !defined(PREVIEW)
            ASSERT_NE(target->GetPixelMap(), nullptr);
            ASSERT_NE(pixelMap, nullptr);
            EXPECT_EQ(target->GetPixelMap(), pixelMap);
#endif
        }
    }
}

/**
 * @tc.name: setStrokeStylePatternWHTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest2, setStrokeStylePatternWHTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setStrokeStyle, nullptr);
    RefPtr<MockImageBitmapPeerStyle> bitmap = AceType::MakeRefPtr<MockImageBitmapPeerStyle>();
    Ark_ImageBitmap arkBitmap = Referenced::RawPtr(bitmap);
    auto pattern = Referenced::MakeRefPtr<CanvasPatternPeer>();
    Ark_CanvasPattern arkPattern = Referenced::RawPtr(pattern);
    GeneratedModifier::CanvasRendererPeerImpl* peer =
        reinterpret_cast<GeneratedModifier::CanvasRendererPeerImpl*>(peer_);
    auto actualStr = DEFAULT_STRING_VALUE;
    auto actualRpt = REPEAT_STRING;
    for (const auto& actualW : NUMBER_TEST_PLAN) {
        for (const auto& actualH : NUMBER_TEST_PLAN) {
            std::shared_ptr<Ace::Pattern> target;
            EXPECT_CALL(*renderingModel_, SetStrokePattern(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            EXPECT_CALL(*bitmap, GetSrc()).WillOnce(Return(actualStr));
#if !defined(PREVIEW)
            const RefPtr<PixelMap> pixelMap = AceType::MakeRefPtr<MockPixelMap>();
            EXPECT_CALL(*bitmap, GetPixelMap()).WillOnce(Return(pixelMap));
#else
            EXPECT_CALL(*bitmap, GetPixelMap()).Times(0);
#endif
            bitmap->SetWidth(actualW);
            bitmap->SetHeight(actualH);
            auto repetition = std::make_optional<std::string>(actualRpt);
            peer->CreatePattern(arkBitmap, arkPattern, repetition);
            auto style =
                Converter::ArkUnion<Ark_Union_String_Color_I32_CanvasGradient_CanvasPattern, Ark_CanvasPattern>(
                    arkPattern);
            accessor_->setStrokeStyle(peer_, &style);

            EXPECT_EQ(target->GetImageWidth(), actualW);
            EXPECT_EQ(target->GetImageHeight(), actualH);
            EXPECT_EQ(target->GetImgSrc(), actualStr);
            EXPECT_EQ(target->GetRepetition(), actualRpt);

#if !defined(PREVIEW)
            ASSERT_NE(target->GetPixelMap(), nullptr);
            ASSERT_NE(pixelMap, nullptr);
            EXPECT_EQ(target->GetPixelMap(), pixelMap);
#endif
        }
    }
}
} // namespace OHOS::Ace::NG
