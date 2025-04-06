/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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
#include "gtest/gtest.h"

#include "base/utils/utils.h"
#define protected public
#define private public
#include "test/mock/core/render/mock_canvas_image.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "base/geometry/ng/point_t.h"
#include "core/components/common/properties/paint_state.h"
#include "core/components_ng/pattern/image/image_paint_method.h"
#include "core/components_ng/render/adapter/pixelmap_image.h"
#include "core/components_ng/render/adapter/svg_canvas_image.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/image_painter.h"
#include "core/pipeline_ng/pipeline_context.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
Testing::MockCanvas testingCanvas;

const NG::OffsetF& OFFSETF { 1, 1 };
const NG::SizeF& SIZE { 10, 10 };

const NG::OffsetF& OFFSETF1 { 0, 0 };
const NG::SizeF& SIZE1 { 0, 0 };

const NG::RectF& CONTENTRECT { 1, 1, 1, 1 };

NG::SizeF rawpicsize { 1, 1 };
NG::SizeF dstsize { 1, 1 };

NG::SizeF boxPaintSize_ { 1, 1 };
NG::SizeF srcSize { 1, 1 };

NG::RectF srcRect_ { 2, 1, 2, 1 };
NG::RectF dstRect_ { 1, 1, 1, 1 };

NG::PointF pointF_ { 10.0, 10.0 };
} // namespace

class ImagePainterTestNg : public testing::Test {
public:
    void CallBack(Testing::MockCanvas& rSCanvas);
};

void ImagePainterTestNg::CallBack(Testing::MockCanvas& rSCanvas)
{
    EXPECT_CALL(rSCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachPen()).WillRepeatedly(ReturnRef(rSCanvas));
}

/**
 * @tc.name: ImagePainterTestNg_DrawImage1
 * @tc.desc: Test cast to CirclePainterTestNg
 * @tc.type: FUNC
 */
HWTEST_F(ImagePainterTestNg, ImagePainterTestNg_DrawImage1, TestSize.Level1)
{
    Testing::MockCanvas* canvasPtr = new Testing::MockCanvas();
    Testing::MockCanvas& canvas = *canvasPtr;
    /**
     * @tc.steps1: build a imagePainter and imagePaintConfig object.
     */
    CallBack(canvas);
    RefPtr<NG::CanvasImage> canvasImage;
    NG::ImagePainter imagePainter(canvasImage);
    NG::ImagePaintConfig imagePaintConfig;

    /**
     * @tc.steps2: callback DrawImage.
     * @tc.expected: expect imagePainter.canvasImage_ is null.
     */
    imagePainter.DrawImage(canvas, OFFSETF, SIZE);
    EXPECT_EQ(imagePainter.canvasImage_, nullptr);

    /**
     * @tc.steps3: build a cavans image object.
     */
    imagePainter.canvasImage_ = AceType::MakeRefPtr<NG::MockCanvasImage>();
    imagePainter.canvasImage_->paintConfig_ = std::make_unique<NG::ImagePaintConfig>();

    /**
     * @tc.steps4: callback DrawImage.
     * @tc.expected: expect imagePainter.canvasImage_ is not null.
     */
    imagePainter.DrawImage(canvas, OFFSETF, SIZE);
    ASSERT_NE(imagePainter.canvasImage_, nullptr);

    imagePaintConfig.isSvg_ = true;
    imagePainter.canvasImage_->paintConfig_ = std::make_unique<NG::ImagePaintConfig>(imagePaintConfig);
    imagePainter.DrawImage(canvas, OFFSETF, SIZE);

    /**
     * @tc.steps5: Assign values to call parameters.
     */
    imagePaintConfig.imageRepeat_ = ImageRepeat::REPEAT;
    imagePaintConfig.isSvg_ = false;
    imagePainter.canvasImage_->paintConfig_ = std::make_unique<NG::ImagePaintConfig>(imagePaintConfig);

    /**
     * @tc.steps6: callback DrawImage.
     * @tc.expected: expect contentRect.Width and contentRect.Height are 1.
     */
    imagePainter.DrawImage(canvas, OFFSETF, SIZE);
    EXPECT_EQ(CONTENTRECT.Width(), 1);
    EXPECT_EQ(CONTENTRECT.Height(), 1);

    /**
     * @tc.steps7: callback DrawImage.
     * @tc.expected: expect imagePainter.canvasImage_ is not null
     */
    ASSERT_NE(imagePainter.canvasImage_->paintConfig_, nullptr);
    std::vector<ObscuredReasons> reasons;
    reasons.emplace_back(static_cast<ObscuredReasons>(0));
    imagePainter.canvasImage_->paintConfig_->obscuredReasons_ = reasons;
    imagePainter.DrawImage(canvas, OFFSETF, SIZE);
    EXPECT_NE(imagePainter.canvasImage_, nullptr);
    testing::Mock::AllowLeak(canvasPtr);
}

/**
 * @tc.name: ImagePainterTestNg_DrawObscuration001
 * @tc.desc: Test DrawObscuration
 * @tc.type: FUNC
 */
HWTEST_F(ImagePainterTestNg, ImagePainterTestNg_DrawObscuration001, TestSize.Level1)
{
    Testing::MockCanvas* canvasPtr = new Testing::MockCanvas();
    Testing::MockCanvas& canvas = *canvasPtr;

    /**
     * @tc.steps1: create a imagePainter and imagePaintConfig object.
     */
    CallBack(canvas);
    RefPtr<NG::CanvasImage> canvasImage;
    NG::ImagePainter imagePainter(canvasImage);
    NG::ImagePaintConfig imagePaintConfig;
    /**
     * @tc.steps2: build a pixelMapImage object.
     */
    imagePainter.canvasImage_ = AceType::MakeRefPtr<NG::MockCanvasImage>();
    imagePainter.canvasImage_->paintConfig_ = std::make_unique<NG::ImagePaintConfig>();
    ASSERT_NE(imagePainter.canvasImage_, nullptr);
    ASSERT_NE(imagePainter.canvasImage_->paintConfig_, nullptr);
    /**
     * @tc.steps3: call DrawObscuration.
     * @tc.expected: expect canvasImage_.borderRadiusXY_ is null
     */
    imagePainter.DrawObscuration(canvas, OFFSETF, SIZE);
    imagePainter.canvasImage_->paintConfig_->isSvg_ = true;
    imagePainter.DrawObscuration(canvas, OFFSETF, SIZE);
    EXPECT_EQ(imagePainter.canvasImage_->paintConfig_->borderRadiusXY_, nullptr);
    /**
     * @tc.steps4: set radiusXY to canvasImage_.borderRadiusXY_ and call DrawObscuration
     * @tc.expected: expect canvasImage_.borderRadiusXY_ is not null
     */
    NG::BorderRadiusArray radiusXY = { pointF_, pointF_, pointF_, pointF_ };
    imagePainter.canvasImage_->paintConfig_->borderRadiusXY_ = std::make_shared<NG::BorderRadiusArray>(radiusXY);
    imagePainter.DrawObscuration(canvas, OFFSETF, SIZE);
    EXPECT_NE(imagePainter.canvasImage_->paintConfig_->borderRadiusXY_, nullptr);
    testing::Mock::AllowLeak(canvasPtr);
}

/**
 * @tc.name: ImagePainterTestNg_DrawSVGImage2
 * @tc.desc: Test cast to CirclePainterTestNg
 * @tc.type: FUNC
 */
HWTEST_F(ImagePainterTestNg, ImagePainterTestNg_DrawSVGImage2, TestSize.Level1)
{
    /**
     * @tc.steps1: build a imagePainter and imagePaintConfig object.
     */
    RefPtr<NG::CanvasImage> canvasImage;
    NG::ImagePainter imagePainter(canvasImage);
    NG::ImagePaintConfig imagePaintConfig;

    /**
     * @tc.steps2: callback DrawImage.
     * @tc.expected: expect imagePainter.canvasImage_ is null.
     */
    EXPECT_EQ(imagePainter.canvasImage_, nullptr);

    /**
     * @tc.steps3: build a pixelMapImage object.
     */
    imagePainter.canvasImage_ = AceType::MakeRefPtr<NG::MockCanvasImage>();
    imagePainter.canvasImage_->paintConfig_ = std::make_unique<NG::ImagePaintConfig>();
    /**
     * @tc.steps4: Assign values to call parameters.
     */
    imagePaintConfig.flipHorizontally_ = true;
    imagePainter.canvasImage_->paintConfig_ = std::make_unique<NG::ImagePaintConfig>(imagePaintConfig);

    /**
     * @tc.steps5: callback DrawImage.
     * @tc.expected: expect OFFSETF.GetX() is 1 and test is 0.
     */
    imagePainter.DrawSVGImage(testingCanvas, OFFSETF, SIZE);
    EXPECT_EQ(OFFSETF.GetX(), 1);
    auto test = imagePainter.canvasImage_->GetPaintConfig().dstRect_.Width();
    EXPECT_EQ(test, 0);
}

/**
 * @tc.name: ImagePainterTestNg_DrawStaticImage3
 * @tc.desc: Test cast to CirclePainterTestNg
 * @tc.type: FUNC
 */
HWTEST_F(ImagePainterTestNg, ImagePainterTestNg_DrawStaticImage3, TestSize.Level1)
{
    /**
     * @tc.steps1: build a imagePainter and imagePaintConfig object.
     */
    RefPtr<NG::CanvasImage> canvasImage;
    NG::ImagePainter imagePainter(canvasImage);
    NG::ImagePaintConfig imagePaintConfig;

    /**
     * @tc.steps2: callback DrawImage.
     * @tc.expected: expect imagePainter.canvasImage_ is null.
     */
    imagePainter.DrawStaticImage(testingCanvas, OFFSETF, SIZE);
    EXPECT_EQ(imagePainter.canvasImage_, nullptr);

    /**
     * @tc.steps3: build a pixelMapImage object.
     */
    imagePainter.canvasImage_ = AceType::MakeRefPtr<NG::MockCanvasImage>();
    imagePainter.canvasImage_->paintConfig_ = std::make_unique<NG::ImagePaintConfig>();
    /**
     * @tc.steps4: Assign values to call parameters.
     */
    imagePaintConfig.renderMode_ = ImageRenderMode::TEMPLATE;
    imagePainter.canvasImage_->paintConfig_ = std::make_unique<NG::ImagePaintConfig>(imagePaintConfig);

    /**
     * @tc.steps5: callback DrawStaticImage.
     * @tc.expected: expect OFFSETF.GetX() and OFFSETF.GetY() are 1.
     */
    imagePainter.DrawStaticImage(testingCanvas, OFFSETF, SIZE);
    EXPECT_EQ(OFFSETF.GetX(), 1);
    EXPECT_EQ(OFFSETF.GetY(), 1);

    /**
     * @tc.steps6: Assign values to call parameters.
     */
    imagePaintConfig.flipHorizontally_ = true;
    imagePainter.canvasImage_->paintConfig_ = std::make_unique<NG::ImagePaintConfig>(imagePaintConfig);

    /**
     * @tc.steps7: callback DrawStaticImage.
     * @tc.expected: expect OFFSETF.GetX() is 1 and test is 0.
     */
    imagePainter.DrawStaticImage(testingCanvas, OFFSETF, SIZE);
    EXPECT_EQ(OFFSETF.GetX(), 1);
    auto test = imagePainter.canvasImage_->GetPaintConfig().dstRect_.Width();
    EXPECT_EQ(test, 0);
}

/**
 * @tc.name: ImagePainterTestNg_FlipHorizontal4
 * @tc.desc: Test cast to CirclePainterTestNg
 * @tc.type: FUNC
 */
HWTEST_F(ImagePainterTestNg, ImagePainterTestNg_FlipHorizontal4, TestSize.Level1)
{
    /**
     * @tc.steps1: build a imagePainter object.
     */
    RefPtr<NG::CanvasImage> canvasImage;
    NG::ImagePainter imagePainter(canvasImage);

    /**
     * @tc.steps2: callback DrawImage.
     */
    imagePainter.FlipHorizontal(testingCanvas, SIZE);
}

/**
 * @tc.name: ImagePainterTestNg_DrawImageWithRepeat5
 * @tc.desc: Test cast to CirclePainterTestNg
 * @tc.type: FUNC
 */
HWTEST_F(ImagePainterTestNg, ImagePainterTestNg_DrawImageWithRepeat5, TestSize.Level1)
{
    /**
     * @tc.steps1: build a imagePainter object.
     */
    RefPtr<NG::CanvasImage> canvasImage;
    NG::ImagePainter imagePainter(canvasImage);
    NG::ImagePaintConfig imagePaintConfig;

    /**
     * @tc.steps2 build a pixelMapImage object.
     */
    imagePainter.canvasImage_ = AceType::MakeRefPtr<NG::MockCanvasImage>();
    imagePainter.canvasImage_->paintConfig_ = std::make_unique<NG::ImagePaintConfig>();

    /**
     * @tc.steps3callback DrawImageWithRepeat.
     * @tc.expected: expect CONTENTRECT.Width() and CONTENTRECT.Height() is 0.
     */
    imagePainter.DrawImageWithRepeat(testingCanvas, CONTENTRECT);
    EXPECT_EQ(CONTENTRECT.Width(), 1);
    EXPECT_EQ(CONTENTRECT.Height(), 1);

    /**
     * @tc.steps4: Assign values to call parameters.
     */
    imagePaintConfig.imageRepeat_ = ImageRepeat::REPEAT;
    imagePaintConfig.dstRect_.width_ = 1;
    imagePaintConfig.dstRect_.height_ = 1;
    imagePainter.canvasImage_->paintConfig_ = std::make_unique<NG::ImagePaintConfig>(imagePaintConfig);

    /**
     * @tc.steps5 callback DrawImageWithRepeat.
     * @tc.expected: expect CONTENTRECT.GetOffset().GetX and CONTENTRECT.GetOffset().GetY is 0.
     */
    imagePainter.DrawImageWithRepeat(testingCanvas, CONTENTRECT);
    EXPECT_EQ(CONTENTRECT.GetOffset().GetX(), 1);
    EXPECT_EQ(CONTENTRECT.GetOffset().GetY(), 1);

    /**
     * @tc.steps6: Assign values to call parameters.
     */
    imagePaintConfig.imageRepeat_ = ImageRepeat::REPEAT_X;
    imagePaintConfig.imageRepeat_ = ImageRepeat::REPEAT_Y;
    imagePaintConfig.dstRect_.width_ = 1;
    imagePaintConfig.dstRect_.height_ = 1;
    imagePainter.canvasImage_->paintConfig_ = std::make_unique<NG::ImagePaintConfig>(imagePaintConfig);
    imagePainter.DrawImageWithRepeat(testingCanvas, CONTENTRECT);
}

/**
 * @tc.name: ImagePainterTestNg_ApplyImageFit6
 * @tc.desc: Test cast to CirclePainterTestNg
 * @tc.type: FUNC
 */
HWTEST_F(ImagePainterTestNg, ImagePainterTestNg_ApplyImageFit6, TestSize.Level1)
{
    /**
     * @tc.steps1: build a imagePainter object.
     */
    RefPtr<NG::CanvasImage> canvasImage;
    NG::ImagePainter imagePainter(canvasImage);
    NG::RectF srcRect_;
    NG::RectF dstRect_;

    /**
     * @tc.steps2: callback ApplyImageFit.
     * @tc.expected: expect viewScale is 1.
     */
    imagePainter.ApplyImageFit(ImageFit::FILL, rawpicsize, dstsize, srcRect_, dstRect_);
    auto context = PipelineContext::GetCurrentContext();
    float viewScale = context ? context->GetViewScale() : 1.0;
    EXPECT_EQ(viewScale, 1);

    /**
     * @tc.steps3: callback ApplyImageFit when ImageFit::NONE.
     * @tc.expected: expect testsize.GetX() and testsize.GetY() are 1.
     */
    imagePainter.ApplyImageFit(ImageFit::NONE, rawpicsize, dstsize, srcRect_, dstRect_);
    NG::SizeF srcSize(std::min(dstsize.Width(), rawpicsize.Width()), std::min(dstsize.Height(), rawpicsize.Height()));
    auto testSize = Alignment::GetAlignPosition(dstsize, srcSize, Alignment::CENTER);
    EXPECT_EQ(testSize.GetX(), 0);
    EXPECT_EQ(testSize.GetY(), 0);

    /**
     * @tc.steps4: callback ApplyImageFit when ImageFit::COVER.
     * @tc.expected: expect testsize1.GetX() and testsize1.GetY() are 1.
     */
    imagePainter.ApplyImageFit(ImageFit::COVER, rawpicsize, dstsize, srcRect_, dstRect_);
    auto testSize1 = Alignment::GetAlignPosition(rawpicsize, srcRect_.GetSize(), Alignment::CENTER);
    EXPECT_EQ(testSize1.GetX(), 0);
    EXPECT_EQ(testSize1.GetY(), 0);

    /**
     * @tc.steps5: callback ApplyImageFit when ImageFit::FITWIDTH.
     * @tc.expected: expect testsize2.GetX() and testsize2.GetY() are 1.
     */
    imagePainter.ApplyImageFit(ImageFit::FITWIDTH, rawpicsize, dstsize, srcRect_, dstRect_);
    auto testSize2 = Alignment::GetAlignPosition(rawpicsize, srcRect_.GetSize(), Alignment::CENTER);
    EXPECT_EQ(testSize2.GetX(), 0);
    EXPECT_EQ(testSize2.GetY(), 0);

    /**
     * @tc.steps6: callback ApplyImageFit when ImageFit::FITHEIGHT.
     * @tc.expected: expect testsize3.GetX() and testsize3.GetY() are 1.
     */
    imagePainter.ApplyImageFit(ImageFit::FITHEIGHT, rawpicsize, dstsize, srcRect_, dstRect_);
    auto testSize3 = Alignment::GetAlignPosition(dstsize, dstRect_.GetSize(), Alignment::CENTER);
    EXPECT_EQ(testSize3.GetX(), 0);
    EXPECT_EQ(testSize3.GetY(), 0);

    /**
     * @tc.steps7: callback ApplyImageFit when ImageFit::SCALE_DOWN.
     * @tc.expected: expect testsize4.GetX() and testsize4.GetY() are 1.
     */
    imagePainter.ApplyImageFit(ImageFit::SCALE_DOWN, rawpicsize, dstsize, srcRect_, dstRect_);
    NG::SizeF srcSize1(std::min(dstsize.Width(), rawpicsize.Width()), std::min(dstsize.Height(), rawpicsize.Height()));
    auto testSize4 = Alignment::GetAlignPosition(dstsize, srcSize1, Alignment::CENTER);
    EXPECT_EQ(testSize4.GetX(), 0);
    EXPECT_EQ(testSize4.GetY(), 0);

    /**
     * @tc.steps8: callback ApplyImageFit when ImageFit::CONTAIN.
     * @tc.expected: expect testsize8.GetX() and testsize8.GetY() are 1.
     */
    imagePainter.ApplyImageFit(ImageFit::CONTAIN, rawpicsize, dstsize, srcRect_, dstRect_);
    auto testSize5 = Alignment::GetAlignPosition(dstsize, dstRect_.GetSize(), Alignment::CENTER);
    EXPECT_EQ(testSize5.GetX(), 0);
    EXPECT_EQ(testSize5.GetY(), 0);

    /**
     * @tc.steps9: callback ApplyImageFit when ImageFit::COVER_TOP_LEFT.
     * @tc.expected: expect testsize6.GetX() and testsize6.GetY() are 1.
     */
    imagePainter.ApplyImageFit(ImageFit::COVER_TOP_LEFT, rawpicsize, dstsize, srcRect_, dstRect_);
    auto testSize6 = Alignment::GetAlignPosition(dstsize, dstRect_.GetSize(), Alignment::CENTER);
    EXPECT_EQ(testSize6.GetX(), 0);
    EXPECT_EQ(testSize6.GetY(), 0);
}

/**
 * @tc.name: ImagePainterTestNg_ImagePainter7
 * @tc.desc: Test cast to CirclePainterTestNg
 * @tc.type: FUNC
 */
HWTEST_F(ImagePainterTestNg, ImagePainterTestNg_ImagePainter7, TestSize.Level1)
{
    /**
     * @tc.steps1: build a imagePainter object.
     */
    RefPtr<NG::CanvasImage> canvasImage;
    NG::ImagePainter imagePainter(canvasImage);
    const NG::SizeF boxPaintSize_;
    const NG::SizeF imageRenderSize_;
    BackgroundImagePosition backgroundImagePosition(
        BackgroundImagePositionType::PERCENT, 1, BackgroundImagePositionType::PERCENT, 1);
    std::optional<BackgroundImagePosition> bgImgPositionOpt = backgroundImagePosition;

    /**
     * @tc.steps2: callback CalculateBgImagePosition when BackgroundImagePositionType::PERCENT.
     * @tc.expected: expect offset.GetX() and offset.GetY() are 0.
     */
    auto offset = imagePainter.CalculateBgImagePosition(boxPaintSize_, imageRenderSize_, bgImgPositionOpt);
    EXPECT_EQ(offset.GetX(), 0);
    EXPECT_EQ(offset.GetY(), 0);

    /**
     * @tc.steps3: callback CalculateBgImagePosition when BackgroundImagePositionType::PX.
     * @tc.expected: expect offset.GetX() and offset.GetY() are 0.
     */
    BackgroundImagePosition backgroundImagePosition1(
        BackgroundImagePositionType::PX, 1, BackgroundImagePositionType::PX, 1);
    std::optional<BackgroundImagePosition> bgImgPositionOpt1 = backgroundImagePosition1;
    auto offset1 = imagePainter.CalculateBgImagePosition(boxPaintSize_, imageRenderSize_, bgImgPositionOpt1);
    EXPECT_EQ(offset1.GetX(), 1);
    EXPECT_EQ(offset1.GetY(), 1);

    /**
     * @tc.steps3: callback CalculateBgImagePosition and reset bgImgPositionOpt.
     * @tc.expected: expect offset.GetX() and offset.GetY() are 0.
     */
    BackgroundImagePosition backgroundImagePosition2(
        BackgroundImagePositionType::PX, 1, BackgroundImagePositionType::PX, 1);
    std::optional<BackgroundImagePosition> bgImgPositionOpt2 = backgroundImagePosition2;
    bgImgPositionOpt2.reset();
    auto offset2 = imagePainter.CalculateBgImagePosition(boxPaintSize_, imageRenderSize_, bgImgPositionOpt2);
    EXPECT_EQ(offset2.GetX(), 0);
    EXPECT_EQ(offset2.GetY(), 0);
}

/**
 * @tc.name: ImagePainterTestNg_CalculateBgImageSize8
 * @tc.desc: Test cast to CirclePainterTestNg
 * @tc.type: FUNC
 */
HWTEST_F(ImagePainterTestNg, ImagePainterTestNg_CalculateBgImageSize8, TestSize.Level1)
{
    /**
     * @tc.steps1: creat a bgImageSizeOpt std::optiona.
     */
    BackgroundImageSize backgroundImageSize1(BackgroundImageSizeType::AUTO, 2, BackgroundImageSizeType::AUTO, 2);
    std::optional<BackgroundImageSize> bgImageSizeOpt1 = backgroundImageSize1;

    /**
     * @tc.steps2: callback CalculateBgImageSize when valueX_ is 2.
     * @tc.expected: expect sizeRet.Width() and sizeRet.Height() are 2.
     */
    auto sizeRet = NG::ImagePainter::CalculateBgImageSize(boxPaintSize_, srcSize, bgImageSizeOpt1);
    EXPECT_EQ(sizeRet.Width(), 1);
    EXPECT_EQ(sizeRet.Height(), 1);

    /**
     * @tc.steps3: callback CalculateBgImageSize when valueX_ is -1.
     * @tc.expected: expect sizeRet.Width() and sizeRet.Height() are -1.
     */
    BackgroundImageSize backgroundImageSize2(BackgroundImageSizeType::LENGTH, -1, BackgroundImageSizeType::LENGTH, -1);
    std::optional<BackgroundImageSize> bgImageSizeOpt2 = backgroundImageSize2;
    auto sizeRet1 = NG::ImagePainter::CalculateBgImageSize(boxPaintSize_, srcSize, bgImageSizeOpt2);
    EXPECT_EQ(sizeRet1.Width(), -1);
    EXPECT_EQ(sizeRet1.Height(), -1);

    /**
     * @tc.steps4: callback CalculateBgImageSize when valueX_ is 1 and valueY is 11.
     * @tc.expected: expect sizeRet.Width() and sizeRet.Height() are 2.
     */
    BackgroundImageSize backgroundImageSize3(BackgroundImageSizeType::LENGTH, 1, BackgroundImageSizeType::LENGTH, -1);
    std::optional<BackgroundImageSize> bgImageSizeOpt3 = backgroundImageSize3;
    auto sizeRet2 = NG::ImagePainter::CalculateBgImageSize(boxPaintSize_, srcSize, bgImageSizeOpt3);
    EXPECT_EQ(sizeRet2.Width(), 1);
    EXPECT_EQ(sizeRet2.Height(), 1);

    /**
     * @tc.steps5: callback CalculateBgImageSize when valueX_ is -1 and valueY is -1.
     * @tc.expected: expect sizeRet.Width() and sizeRet.Height() are -1.
     */
    srcSize = { -1, -1 };
    boxPaintSize_ = { -1, -1 };
    BackgroundImageSize backgroundImageSize4(BackgroundImageSizeType::LENGTH, 1, BackgroundImageSizeType::LENGTH, -1);
    std::optional<BackgroundImageSize> bgImageSizeOpt4 = backgroundImageSize4;
    bgImageSizeOpt4.reset();
    auto sizeRet3 = NG::ImagePainter::CalculateBgImageSize(boxPaintSize_, srcSize, bgImageSizeOpt4);
    EXPECT_EQ(sizeRet3.Width(), -1);
    EXPECT_EQ(sizeRet3.Height(), -1);
}

/**
 * @tc.name: ImagePainterTestNg_CalculateBgWidth9
 * @tc.desc: Test cast to CirclePainterTestNg
 * @tc.type: FUNC
 */
HWTEST_F(ImagePainterTestNg, ImagePainterTestNg_CalculateBgWidth9, TestSize.Level1)
{
    /**
     * @tc.steps1: creat a backgroundImageSize object.
     */
    BackgroundImageSize backgroundImageSize(BackgroundImageSizeType::AUTO, 2, BackgroundImageSizeType::AUTO, 2);

    /**
     * @tc.steps2: creat for loop change BackgroundImageSizeTypeX and callback CalculateBgImageSize.
     * @tc.expected: expect offset.GetX() and offset.GetY() are -1.
     */
    for (int32_t index = 0; index <= 4; index++) {
        backgroundImageSize.typeX_ = static_cast<BackgroundImageSizeType>(index);
        const std::optional<BackgroundImageSize>& bgImageSizeOpt = backgroundImageSize;
        NG::ImagePainter::CalculateBgImageSize(boxPaintSize_, srcSize, bgImageSizeOpt);
        switch (backgroundImageSize.typeX_) {
            case BackgroundImageSizeType::COVER:
                EXPECT_EQ(srcSize.Width(), -1);
                break;
            case BackgroundImageSizeType::CONTAIN:
                EXPECT_EQ(srcSize.Width(), -1);
                break;
            case BackgroundImageSizeType::LENGTH:
                EXPECT_EQ(srcSize.Width(), -1);
                break;
            case BackgroundImageSizeType::PERCENT:
                EXPECT_EQ(srcSize.Width(), -1);
                break;
            default:
                break;
        }
    }

    /**
     * @tc.steps3: creat for loop change BackgroundImageSizeTypeY and callback CalculateBgImageSize.
     * @tc.expected: expect offset.GetX() and offset.GetY() are -1.
     */
    for (int32_t index = 0; index <= 4; index++) {
        backgroundImageSize.typeY_ = static_cast<BackgroundImageSizeType>(index);
        const std::optional<BackgroundImageSize>& bgImageSizeOpt = backgroundImageSize;
        NG::ImagePainter::CalculateBgImageSize(boxPaintSize_, srcSize, bgImageSizeOpt);
        switch (backgroundImageSize.typeY_) {
            case BackgroundImageSizeType::COVER:
                EXPECT_EQ(srcSize.Height(), -1);
                break;
            case BackgroundImageSizeType::CONTAIN:
                EXPECT_EQ(srcSize.Height(), -1);
                break;
            case BackgroundImageSizeType::LENGTH:
                EXPECT_EQ(srcSize.Height(), -1);
                break;
            case BackgroundImageSizeType::PERCENT:
                EXPECT_EQ(srcSize.Height(), -1);
                break;
            default:
                break;
        }
    }
}

/**
 * @tc.name: ImagePainterTestNg_CalculateBgWidth10
 * @tc.desc: Test cast to CirclePainterTestNg
 * @tc.type: FUNC
 */
HWTEST_F(ImagePainterTestNg, ImagePainterTestNg_CalculateBgImageSize10, TestSize.Level1)
{
    /**
     * @tc.steps1: creat a bgImageSizeOpt1 and callback CalculateBgImageSize.
     * @tc.expected: expect width1 is -2.
     */
    srcSize = { 2, 1 };
    BackgroundImageSize backgroundImageSize1(BackgroundImageSizeType::COVER, 1, BackgroundImageSizeType::COVER, 1);
    const std::optional<BackgroundImageSize>& bgImageSizeOpt1 = backgroundImageSize1;
    NG::ImagePainter::CalculateBgImageSize(boxPaintSize_, srcSize, bgImageSizeOpt1);
    auto width1 = srcSize.Width() * (boxPaintSize_.Height() / srcSize.Height());
    EXPECT_EQ(width1, -2);

    /**
     * @tc.steps2: creat a bgImageSizeOpt2 and callback CalculateBgImageSize.
     * @tc.expected: expect width1 is 1.
     */
    srcSize = { 2, 1 };
    BackgroundImageSize backgroundImageSize2(BackgroundImageSizeType::CONTAIN, 1, BackgroundImageSizeType::CONTAIN, 1);
    const std::optional<BackgroundImageSize>& bgImageSizeOpt2 = backgroundImageSize2;
    NG::ImagePainter::CalculateBgImageSize(boxPaintSize_, srcSize, bgImageSizeOpt2);
    auto width2 = boxPaintSize_.Width();
    EXPECT_EQ(width2, -1);
}

/**
 * @tc.name: ImagePainterTestNg_ApplyImageFit11
 * @tc.desc: Test cast to CirclePainterTestNg
 * @tc.type: FUNC
 */
HWTEST_F(ImagePainterTestNg, ImagePainterTestNg_ApplyImageFit11, TestSize.Level1)
{
    /**
     * @tc.steps1: build a imagePainter object.
     */
    RefPtr<NG::CanvasImage> canvasImage;
    NG::ImagePainter imagePainter(canvasImage);
    rawpicsize = { 10, 1 };

    /**
     * @tc.steps2: callback ApplyImageFit when ImageFit::COVER.
     * @tc.expected: expect testsize1.GetX() is 4.5 and testsize1.GetY() is 0.
     */
    imagePainter.ApplyImageFit(ImageFit::COVER, rawpicsize, dstsize, srcRect_, dstRect_);
    auto testSize1 = Alignment::GetAlignPosition(rawpicsize, srcRect_.GetSize(), Alignment::CENTER);
    EXPECT_EQ(testSize1.GetX(), 4.5);
    EXPECT_EQ(testSize1.GetY(), 0);

    /**
     * @tc.steps3: callback ApplyImageFit when ImageFit::FITWIDTH.
     * @tc.expected: expect testsize2.GetX() and testsize2.GetY() are 0.
     */
    imagePainter.ApplyImageFit(ImageFit::FITWIDTH, rawpicsize, dstsize, srcRect_, dstRect_);
    auto testSize2 = Alignment::GetAlignPosition(rawpicsize, srcRect_.GetSize(), Alignment::CENTER);
    EXPECT_EQ(testSize2.GetX(), 0);
    EXPECT_EQ(testSize2.GetY(), 0);

    /**
     * @tc.steps4: callback ApplyImageFit when ImageFit::FITHEIGHT.
     * @tc.expected: expect testsize3.GetX() and testsize3.GetY() are 0.
     */
    imagePainter.ApplyImageFit(ImageFit::FITHEIGHT, rawpicsize, dstsize, srcRect_, dstRect_);
    auto testSize3 = Alignment::GetAlignPosition(dstsize, dstRect_.GetSize(), Alignment::CENTER);
    EXPECT_EQ(testSize3.GetX(), 0);
    EXPECT_EQ(testSize3.GetY(), 0);

    /**
     * @tc.steps5: callback ApplyImageFit when ImageFit::CONTAIN.
     * @tc.expected: expect testsize8.GetX() is 0 and testsize8.GetY() are 0.45.
     */
    imagePainter.ApplyImageFit(ImageFit::CONTAIN, rawpicsize, dstsize, srcRect_, dstRect_);
    auto testSize4 = Alignment::GetAlignPosition(dstsize, dstRect_.GetSize(), Alignment::CENTER);
    EXPECT_EQ(testSize4.GetX(), 0);
    EXPECT_FLOAT_EQ(testSize4.GetY(), 0.45);

    /**
     * @tc.steps6: callback ApplyImageFit when ImageFit::CONTAIN.
     * @tc.expected: expect testsize8.GetX() and testsize8.GetY() are 0.
     */
    rawpicsize = { -1, -1 };
    imagePainter.ApplyImageFit(ImageFit::CONTAIN, rawpicsize, dstsize, srcRect_, dstRect_);
    auto testSize5 = Alignment::GetAlignPosition(dstsize, dstRect_.GetSize(), Alignment::CENTER);
    EXPECT_EQ(testSize5.GetX(), 0);
    EXPECT_EQ(testSize5.GetY(), 0);

    /**
     * @tc.steps7: callback ApplyImageFit when ImageFit::COVER_TOP_LEFT.
     * @tc.expected: expect testsize6.GetX() and testsize6.GetY() are 0.
     */
    rawpicsize = { -1, -1 };
    imagePainter.ApplyImageFit(ImageFit::COVER_TOP_LEFT, rawpicsize, dstsize, srcRect_, dstRect_);
    auto testSize6 = Alignment::GetAlignPosition(dstsize, dstRect_.GetSize(), Alignment::CENTER);
    EXPECT_EQ(testSize6.GetX(), 0);
    EXPECT_EQ(testSize6.GetY(), 0);
}

/**
 * @tc.name: ImagePainterTestNg_DrawImage002
 * @tc.desc: Test cast to DrawImage
 * @tc.type: FUNC
 */
HWTEST_F(ImagePainterTestNg, ImagePainterTestNg_DrawImage002, TestSize.Level1)
{
    RefPtr<NG::CanvasImage> canvasImage;
    NG::ImagePainter imagePainter(canvasImage);
    NG::ImagePaintConfig imagePaintConfig;
    imagePainter.DrawImage(testingCanvas, OFFSETF, SIZE);
    EXPECT_EQ(imagePainter.canvasImage_, nullptr);

    imagePainter.canvasImage_ = AceType::MakeRefPtr<NG::MockCanvasImage>();
    imagePainter.canvasImage_->paintConfig_ = std::make_unique<NG::ImagePaintConfig>();
    imagePainter.DrawImage(testingCanvas, OFFSETF, SIZE);
    EXPECT_NE(imagePainter.canvasImage_, nullptr);

    imagePaintConfig.isSvg_ = true;
    imagePainter.canvasImage_->paintConfig_ = std::make_unique<NG::ImagePaintConfig>(imagePaintConfig);
    imagePainter.DrawImage(testingCanvas, OFFSETF, SIZE);
    EXPECT_NE(imagePainter.canvasImage_->paintConfig_, nullptr);
}

/**
 * @tc.name: ImagePainterTestNg_DrawObscuration002
 * @tc.desc: Test cast to DrawObscuration
 * @tc.type: FUNC
 */
HWTEST_F(ImagePainterTestNg, ImagePainterTestNg_DrawObscuration002, TestSize.Level1)
{
    RefPtr<NG::CanvasImage> canvasImage;
    NG::ImagePainter imagePainter(canvasImage);
    NG::ImagePaintConfig imagePaintConfig;
    EXPECT_EQ(imagePainter.canvasImage_, nullptr);
}

/**
 * @tc.name: ImagePainterTestNg_CalculateBgWidth001
 * @tc.desc: Test cast to CalculateBgWidth
 * @tc.type: FUNC
 */
HWTEST_F(ImagePainterTestNg, ImagePainterTestNg_CalculateBgImageSize001, TestSize.Level1)
{
    NG::SizeF boxPaintSize1 { 1, 1 };
    NG::SizeF srcSize1 = { 0, 0 };
    BackgroundImageSize backgroundImageSize1(BackgroundImageSizeType::COVER, 1, BackgroundImageSizeType::COVER, 1);
    const std::optional<BackgroundImageSize>& bgImageSizeOpt1 = backgroundImageSize1;
    NG::ImagePainter::CalculateBgImageSize(boxPaintSize1, srcSize1, bgImageSizeOpt1);

    BackgroundImageSize backgroundImageSize2(BackgroundImageSizeType::CONTAIN, 1, BackgroundImageSizeType::CONTAIN, 1);
    const std::optional<BackgroundImageSize>& bgImageSizeOpt2 = backgroundImageSize2;
    NG::ImagePainter::CalculateBgImageSize(boxPaintSize1, srcSize1, bgImageSizeOpt2);
    auto width = boxPaintSize1.Width();
    EXPECT_EQ(width, 1);
}

/**
 * @tc.name: ImagePainterTestNg_CalculateBgWidth002
 * @tc.desc: Test cast to CalculateBgWidth
 * @tc.type: FUNC
 */
HWTEST_F(ImagePainterTestNg, ImagePainterTestNg_CalculateBgImageSize002, TestSize.Level1)
{
    NG::SizeF boxPaintSize1 { 1, 1 };
    NG::SizeF srcSize1 = { 0, 1 };
    BackgroundImageSize backgroundImageSize1(BackgroundImageSizeType::COVER, 1, BackgroundImageSizeType::COVER, 1);
    const std::optional<BackgroundImageSize>& bgImageSizeOpt1 = backgroundImageSize1;
    NG::ImagePainter::CalculateBgImageSize(boxPaintSize1, srcSize1, bgImageSizeOpt1);

    BackgroundImageSize backgroundImageSize2(BackgroundImageSizeType::CONTAIN, 1, BackgroundImageSizeType::CONTAIN, 1);
    const std::optional<BackgroundImageSize>& bgImageSizeOpt2 = backgroundImageSize2;
    NG::ImagePainter::CalculateBgImageSize(boxPaintSize1, srcSize1, bgImageSizeOpt2);

    NG::SizeF boxPaintSize2 { 0, 0 };
    NG::SizeF srcSize2 = { 1, 0 };
    NG::ImagePainter::CalculateBgImageSize(boxPaintSize2, srcSize2, bgImageSizeOpt1);

    NG::ImagePainter::CalculateBgImageSize(boxPaintSize2, srcSize2, bgImageSizeOpt2);
    auto width = boxPaintSize2.Width();
    EXPECT_EQ(width, 0);
}

/**
 * @tc.name: ImagePainterTestNg_DrawImageWithRepeat12
 * @tc.desc: Test cast to CirclePainterTestNg
 * @tc.type: FUNC
 */
HWTEST_F(ImagePainterTestNg, ImagePainterTestNg_DrawImageWithRepeat12, TestSize.Level1)
{
    /**
     * @tc.steps1: build a imagePainter object.
     */
    RefPtr<NG::CanvasImage> canvasImage;
    NG::ImagePainter imagePainter(canvasImage);
    NG::ImagePaintConfig imagePaintConfig;

    /**
     * @tc.steps2 build a pixelMapImage object.
     */
    imagePainter.canvasImage_ = AceType::MakeRefPtr<NG::MockCanvasImage>();
    imagePainter.canvasImage_->paintConfig_ = std::make_unique<NG::ImagePaintConfig>();
    NG::RectF srcRect_(1.0f, 1.0f, 0.0001f, 0.0001f);

    /**
     * @tc.steps3callback DrawImageWithRepeat.
     * @tc.expected: expect NearZero(singleImageHeight).
     */
    imagePainter.canvasImage_->paintConfig_->dstRect_ = srcRect_;
    imagePainter.DrawImageWithRepeat(testingCanvas, CONTENTRECT);
    EXPECT_EQ(CONTENTRECT.Width(), 1);
    EXPECT_EQ(CONTENTRECT.Height(), 1);
}

/**
 * @tc.name: ImagePainterTestNg_CalculateBgWidth13
 * @tc.desc: Test cast to CalculateBgWidth
 * @tc.type: FUNC
 */
HWTEST_F(ImagePainterTestNg, ImagePainterTestNg_CalculateBgImageSize13, TestSize.Level1)
{
    srcSize = { 2, 1 };
    BackgroundImageSize backgroundImageSize(
        BackgroundImageSizeType::PERCENT, 100, BackgroundImageSizeType::PERCENT, 100);
    const std::optional<BackgroundImageSize>& bgImageSizeOpt = backgroundImageSize;
    auto sizeRet = NG::ImagePainter::CalculateBgImageSize(boxPaintSize_, srcSize, bgImageSizeOpt);
    EXPECT_EQ(boxPaintSize_.Width() * bgImageSizeOpt.value().GetSizeValueX() * srcSize.Width() / srcSize.Height(),
        sizeRet.Width() * 100);

    BackgroundImageSize backgroundImageSize1(BackgroundImageSizeType::AUTO, 100, BackgroundImageSizeType::PERCENT, 100);
    const std::optional<BackgroundImageSize>& bgImageSizeOpt1 = backgroundImageSize1;
    auto sizeRet_ = NG::ImagePainter::CalculateBgImageSize(boxPaintSize_, srcSize, bgImageSizeOpt1);
    EXPECT_EQ(boxPaintSize_.Width() * bgImageSizeOpt.value().GetSizeValueX() * srcSize.Width() / srcSize.Height(),
        sizeRet_.Width() * 100);
}

/**
 * @tc.name: ImagePainterTestNg_CalculateBgImagePosition14
 * @tc.desc: Test cast to CalculateBgImagePosition
 * @tc.type: FUNC
 */
HWTEST_F(ImagePainterTestNg, ImagePainterTestNg_CalculateBgImagePosition14, TestSize.Level1)
{
    RefPtr<NG::CanvasImage> canvasImage;
    NG::ImagePainter imagePainter(canvasImage);
    const NG::SizeF boxPaintSize_;
    const NG::SizeF imageRenderSize_;

    BackgroundImagePosition backgroundImagePosition(
        BackgroundImagePositionType::PX, 1, BackgroundImagePositionType::PX, 1);
    std::optional<BackgroundImagePosition> bgImgPositionOpt = backgroundImagePosition;
    bgImgPositionOpt.value().SetIsAlign(true);
    auto offset = imagePainter.CalculateBgImagePosition(boxPaintSize_, imageRenderSize_, bgImgPositionOpt);
    EXPECT_EQ(offset.GetX(), 0);
    EXPECT_EQ(offset.GetY(), 0);
}

/**
 * @tc.name: ImagePainterTestNg_ApplyImageAlignmentFit15
 * @tc.desc: Test cast to CirclePainterTestNg
 * @tc.type: FUNC
 */
HWTEST_F(ImagePainterTestNg, ImagePainterTestNg_ApplyImageAlignmentFit15, TestSize.Level1)
{
    /**
     * @tc.steps1: build a imagePainter object.
     */
    RefPtr<NG::CanvasImage> canvasImage;
    NG::ImagePainter imagePainter(canvasImage);
    NG::RectF srcRect_;
    NG::RectF dstRect_;

    /**
     * @tc.steps2: callback ApplyImageAlignmentFit when ImageFit::FILL
     * @tc.expected: not find.
     */
    imagePainter.ApplyImageAlignmentFit(ImageFit::FILL, rawpicsize, dstsize, srcRect_, dstRect_);
    auto itImageFit = imagePainter.ALIMENT_OPERATIONS.find(ImageFit::FILL);
    EXPECT_EQ(itImageFit, imagePainter.ALIMENT_OPERATIONS.end());

    /**
     * @tc.steps3: callback ApplyImageAlignmentFit when ImageFit::TOP_LEFT.
     * @tc.expected: find.
     */
    imagePainter.ApplyImageAlignmentFit(ImageFit::TOP_LEFT, rawpicsize, dstsize, srcRect_, dstRect_);
    auto itImageFit_ = imagePainter.ALIMENT_OPERATIONS.find(ImageFit::TOP_LEFT);
    EXPECT_NE(itImageFit_, imagePainter.ALIMENT_OPERATIONS.end());
}

/**
 * @tc.name: ImagePainterTestNg_ApplyImageFit16
 * @tc.desc: Test cast to ApplyImageFit
 * @tc.type: FUNC
 */
HWTEST_F(ImagePainterTestNg, ImagePainterTestNg_ApplyImageFit16, TestSize.Level1)
{
    /**
     * @tc.steps1: build a imagePainter object.
     */
    RefPtr<NG::CanvasImage> canvasImage;
    NG::ImagePainter imagePainter(canvasImage);
    NG::RectF srcRect_(1.0f, 1.0f, 2.0f, 2.0f);
    NG::RectF dstRect_(1.0f, 1.0f, 1.0f, 1.0f);
    NG::RectF dstRect(1.0f, 1.0f, 2.0f, 2.0f);

    /**
     * @tc.steps2: callback ApplyImageFit.
     * @tc.expected: expect ImageFit is COVER_TOP_LEFT.
     */
    imagePainter.ApplyImageFit(ImageFit::COVER_TOP_LEFT, rawpicsize, dstsize, srcRect_, dstRect_);
    auto itImageFit = imagePainter.ALIMENT_OPERATIONS.find(ImageFit::COVER_TOP_LEFT);
    EXPECT_EQ(itImageFit, imagePainter.ALIMENT_OPERATIONS.end());

    imagePainter.ApplyImageFit(ImageFit::END, rawpicsize, dstsize, srcRect_, dstRect_);
    auto itImageFit1 = imagePainter.ALIMENT_OPERATIONS.find(ImageFit::END);
    EXPECT_NE(itImageFit1, imagePainter.ALIMENT_OPERATIONS.end());

    /**
     * @tc.steps2: callback ApplyImageFit.
     * @tc.expected: expect ImageFit is SCALE_DOWN,srcRect_=dstRect_.
     */
    imagePainter.ApplyImageFit(ImageFit::SCALE_DOWN, rawpicsize, dstsize, srcRect_, dstRect);
    EXPECT_NE(srcRect_.GetSize() > dstRect.GetSize(), true);
}

/**
 * @tc.name: ImagePainterTestNg_ApplyImageAlignmentFit17
 * @tc.desc: Test cast to ApplyImageAlignmentFit
 * @tc.type: FUNC
 */
HWTEST_F(ImagePainterTestNg, ImagePainterTestNg_ApplyImageAlignmentFit17, TestSize.Level1)
{
    /**
     * @tc.steps1: build a imagePainter object.
     */
    RefPtr<NG::CanvasImage> canvasImage;
    NG::ImagePainter imagePainter(canvasImage);
    NG::RectF srcRect_;
    NG::RectF dstRect_;

    /**
     * @tc.steps2: callback ApplyImageAlignmentFit when ImageFit::TOP_END.
     * @tc.expected: find && isRightToLeft_ = false.
     */
    imagePainter.ApplyImageAlignmentFit(ImageFit::TOP_END, rawpicsize, dstsize, srcRect_, dstRect_);
    auto itImageFit1 = imagePainter.ALIMENT_OPERATIONS.find(ImageFit::TOP_END);
    EXPECT_NE(itImageFit1, imagePainter.ALIMENT_OPERATIONS.end());

    /**
     * @tc.steps3: callback ApplyImageAlignmentFit when ImageFit::START.
     * @tc.expected: find && isRightToLeft_ = false.
     */
    imagePainter.ApplyImageAlignmentFit(ImageFit::START, rawpicsize, dstsize, srcRect_, dstRect_);
    auto itImageFit2 = imagePainter.ALIMENT_OPERATIONS.find(ImageFit::START);
    EXPECT_NE(itImageFit2, imagePainter.ALIMENT_OPERATIONS.end());

    /**
     * @tc.steps4: callback ApplyImageAlignmentFit when ImageFit::END.
     * @tc.expected: find && isRightToLeft_ = false.
     */
    imagePainter.ApplyImageAlignmentFit(ImageFit::END, rawpicsize, dstsize, srcRect_, dstRect_);
    auto itImageFit3 = imagePainter.ALIMENT_OPERATIONS.find(ImageFit::END);
    EXPECT_NE(itImageFit3, imagePainter.ALIMENT_OPERATIONS.end());

    /**
     * @tc.steps5: callback ApplyImageAlignmentFit when ImageFit::BOTTOM_START.
     * @tc.expected: find && isRightToLeft_ = false.
     */
    imagePainter.ApplyImageAlignmentFit(ImageFit::BOTTOM_START, rawpicsize, dstsize, srcRect_, dstRect_);
    auto itImageFit4 = imagePainter.ALIMENT_OPERATIONS.find(ImageFit::BOTTOM_START);
    EXPECT_NE(itImageFit4, imagePainter.ALIMENT_OPERATIONS.end());

    /**
     * @tc.steps6: callback ApplyImageAlignmentFit when ImageFit::BOTTOM_END.
     * @tc.expected: find && isRightToLeft_ = false.
     */
    imagePainter.ApplyImageAlignmentFit(ImageFit::BOTTOM_END, rawpicsize, dstsize, srcRect_, dstRect_);
    auto itImageFit5 = imagePainter.ALIMENT_OPERATIONS.find(ImageFit::BOTTOM_END);
    EXPECT_NE(itImageFit5, imagePainter.ALIMENT_OPERATIONS.end());
}

/**
 * @tc.name: ImagePainterTestNg_ApplyImageAlignmentFit18
 * @tc.desc: Test cast to ApplyImageAlignmentFit
 * @tc.type: FUNC
 */
HWTEST_F(ImagePainterTestNg, ImagePainterTestNg_ApplyImageAlignmentFit18, TestSize.Level1)
{
    /**
     * @tc.steps1: build a imagePainter object.
     */
    RefPtr<NG::CanvasImage> canvasImage;
    NG::ImagePainter imagePainter(canvasImage);
    NG::RectF srcRect_;
    NG::RectF dstRect_;

    /**
     * @tc.steps2: callback ApplyImageAlignmentFit when ImageFit::TOP_LEFT,ImageFit::TOP_END...
     * @tc.expected: find && isRightToLeft_ = true.
     */
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    imagePainter.ApplyImageAlignmentFit(ImageFit::TOP_LEFT, rawpicsize, dstsize, srcRect_, dstRect_);
    auto itImageFit_ = imagePainter.ALIMENT_OPERATIONS.find(ImageFit::TOP_LEFT);
    EXPECT_NE(itImageFit_, imagePainter.ALIMENT_OPERATIONS.end());
    EXPECT_EQ(itImageFit_->second(AceApplicationInfo::GetInstance().isRightToLeft_), Alignment::TOP_RIGHT);

    imagePainter.ApplyImageAlignmentFit(ImageFit::TOP_END, rawpicsize, dstsize, srcRect_, dstRect_);
    auto itImageFit1 = imagePainter.ALIMENT_OPERATIONS.find(ImageFit::TOP_END);
    EXPECT_NE(itImageFit1, imagePainter.ALIMENT_OPERATIONS.end());
    EXPECT_EQ(itImageFit1->second(AceApplicationInfo::GetInstance().isRightToLeft_), Alignment::TOP_LEFT);

    imagePainter.ApplyImageAlignmentFit(ImageFit::START, rawpicsize, dstsize, srcRect_, dstRect_);
    auto itImageFit2 = imagePainter.ALIMENT_OPERATIONS.find(ImageFit::START);
    EXPECT_NE(itImageFit2, imagePainter.ALIMENT_OPERATIONS.end());
    EXPECT_EQ(itImageFit2->second(AceApplicationInfo::GetInstance().isRightToLeft_), Alignment::CENTER_RIGHT);

    imagePainter.ApplyImageAlignmentFit(ImageFit::END, rawpicsize, dstsize, srcRect_, dstRect_);
    auto itImageFit3 = imagePainter.ALIMENT_OPERATIONS.find(ImageFit::END);
    EXPECT_NE(itImageFit3, imagePainter.ALIMENT_OPERATIONS.end());
    EXPECT_EQ(itImageFit3->second(AceApplicationInfo::GetInstance().isRightToLeft_), Alignment::CENTER_LEFT);

    imagePainter.ApplyImageAlignmentFit(ImageFit::BOTTOM_START, rawpicsize, dstsize, srcRect_, dstRect_);
    auto itImageFit4 = imagePainter.ALIMENT_OPERATIONS.find(ImageFit::BOTTOM_START);
    EXPECT_NE(itImageFit4, imagePainter.ALIMENT_OPERATIONS.end());
    EXPECT_EQ(itImageFit4->second(AceApplicationInfo::GetInstance().isRightToLeft_), Alignment::BOTTOM_RIGHT);

    imagePainter.ApplyImageAlignmentFit(ImageFit::BOTTOM_END, rawpicsize, dstsize, srcRect_, dstRect_);
    auto itImageFit5 = imagePainter.ALIMENT_OPERATIONS.find(ImageFit::BOTTOM_END);
    EXPECT_NE(itImageFit5, imagePainter.ALIMENT_OPERATIONS.end());
    EXPECT_EQ(itImageFit5->second(AceApplicationInfo::GetInstance().isRightToLeft_), Alignment::BOTTOM_LEFT);
}
} // namespace OHOS::Ace
