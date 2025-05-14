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
#include "test/mock/core/rosen/mock_canvas.h"

#include "core/components_ng/render/border_image_painter.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
const NG::BorderWidthProperty BORDER_WIDTH_TEST = { 1.0_vp, 1.0_vp, 1.0_vp, 1.0_vp };
const NG::SizeF PAINTSIZE = { 5.0, 10.0 };
const NG::SizeF TEST_SIZE = { 100.0, 200.0 };
const NG::OffsetF OFFSET_F = { 1.0, 2.0 };

const NG::DisplayScaleInfo DIPSCALE = { .vpScale = 10.0 };
const double FIVE = 5.0;
const double TWO = 2.0;
const double ONE = 1.0;
const double ZERO_TEST = 0.0;
const std::string SRC_IMAGES = "images/mmm.jpg";

const Dimension DIMENSION_SLICE = 10.0_vp;
const Dimension DIMENSION_WIDTH = 30.0_vp;
const Dimension DIMENSION_OUTSET = 100.0_vp;

const BorderImageDirection DIRECTION_LEFT = BorderImageDirection::LEFT;
const BorderImageDirection DIRECTION_RIGHT = BorderImageDirection::RIGHT;
const BorderImageDirection DIRECTION_TOP = BorderImageDirection::TOP;
const BorderImageDirection DIRECTION_BOTTOM = BorderImageDirection::BOTTOM;

BorderImage* MakeBorderImage()
{
    BorderImage* testImage = new BorderImage(SRC_IMAGES);
    testImage->SetEdgeSlice(DIRECTION_LEFT, DIMENSION_SLICE);
    testImage->SetEdgeSlice(DIRECTION_RIGHT, DIMENSION_SLICE);
    testImage->SetEdgeSlice(DIRECTION_TOP, DIMENSION_SLICE);
    testImage->SetEdgeSlice(DIRECTION_BOTTOM, DIMENSION_SLICE);

    testImage->SetEdgeWidth(DIRECTION_LEFT, DIMENSION_WIDTH);
    testImage->SetEdgeWidth(DIRECTION_RIGHT, DIMENSION_WIDTH);
    testImage->SetEdgeWidth(DIRECTION_TOP, DIMENSION_WIDTH);
    testImage->SetEdgeWidth(DIRECTION_BOTTOM, DIMENSION_WIDTH);

    testImage->SetEdgeOutset(DIRECTION_LEFT, DIMENSION_OUTSET);
    testImage->SetEdgeOutset(DIRECTION_RIGHT, DIMENSION_OUTSET);
    testImage->SetEdgeOutset(DIRECTION_TOP, DIMENSION_OUTSET);
    testImage->SetEdgeOutset(DIRECTION_BOTTOM, DIMENSION_OUTSET);
    return testImage;
};
} // namespace

class BorderImagePainterTestNg : public testing::Test {
public:
    void CallBack(Testing::MockCanvas& rSCanvas);
};

void BorderImagePainterTestNg::CallBack(Testing::MockCanvas& rSCanvas)
{
    EXPECT_CALL(rSCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachPen()).WillRepeatedly(ReturnRef(rSCanvas));
}

/**
 * @tc.name: BorderImagePainter001
 * @tc.desc: Test cast to BorderImagePainterTestNg
 * @tc.type: FUNC
 */
HWTEST_F(BorderImagePainterTestNg, BorderImagePainter001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. push widthProp != nullptr.
     * @tc.steps: step1. Build a object borderImagePainter.
     */
    NG::BorderImageProperty borderImageProperty;
    RSImage image;
    std::unique_ptr<NG::BorderWidthProperty> widthProp { std::make_unique<NG::BorderWidthProperty>(BORDER_WIDTH_TEST) };
    NG::BorderImagePainter borderImagePainter(borderImageProperty, widthProp, PAINTSIZE, image, DIPSCALE);

    /**
     * @tc.steps: step2. push borderImagePainter.borderImageProperty_ is not null.
     * @tc.steps: step2. call InitPainter.
     */
    borderImageProperty.propBorderImage = AceType::MakeRefPtr<BorderImage>();

    borderImagePainter.borderImageProperty_ = std::move(borderImageProperty);
    borderImagePainter.hasWidthProp_ = true;
    borderImagePainter.imageWidth_ = 720.0;
    borderImagePainter.imageHeight_ = 1080.0;
    borderImagePainter.paintSize_ = TEST_SIZE;
    borderImagePainter.InitPainter();

    /**
     * @tc.expected: the borderImagePainter.borderCenterWidth_ is expected results.
     * @tc.expected: the borderImagePainter.imageCenterWidth_ is expected results.
     */
    EXPECT_EQ(borderImagePainter.borderCenterWidth_, 100);
    EXPECT_EQ(borderImagePainter.borderCenterHeight_, 200);
    EXPECT_EQ(borderImagePainter.imageCenterWidth_, -720);
    EXPECT_EQ(borderImagePainter.imageCenterHeight_, -1080);
}

/**
 * @tc.name: BorderImagePainter002
 * @tc.desc: Test cast to BorderImagePainterTestNg
 * @tc.type: FUNC
 */
HWTEST_F(BorderImagePainterTestNg, BorderImagePainter002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. push widthProp = nullptr.
     * @tc.steps: step1. Build a object borderImagePainter.
     */
    NG::BorderImageProperty borderImageProperty;
    RSImage image;
    std::unique_ptr<NG::BorderWidthProperty> widthProp;
    NG::BorderImagePainter borderImagePainter(borderImageProperty, widthProp, PAINTSIZE, image, DIPSCALE);

    /**
     * @tc.steps: step2. push borderImageProperty.propBorderImage is null.
     * @tc.steps: step2. push borderImagePainter.leftSlice_ < imageWidth_.
     * @tc.steps: step2. call InitPainter.
     */
    borderImageProperty.propBorderImage = AceType::MakeRefPtr<BorderImage>();
    borderImageProperty.propHasBorderImageSlice = true;

    borderImagePainter.borderImageProperty_ = std::move(borderImageProperty);
    borderImagePainter.leftSlice_ = 10.0;
    borderImagePainter.rightSlice_ = 20.0;
    borderImagePainter.topSlice_ = 40.0;
    borderImagePainter.bottomSlice_ = 80.0;
    borderImagePainter.InitBorderImageSlice();
    borderImagePainter.InitBorderImageWidth();
    borderImagePainter.InitBorderImageOutset();

    /**
     * @tc.expected: the borderImagePainter.leftSlice_ is expected results.
     * @tc.expected: the borderImagePainter.rightSlice_ is expected results.
     */
    EXPECT_EQ(borderImagePainter.leftSlice_, 10);
    EXPECT_EQ(borderImagePainter.rightSlice_, 20);
    EXPECT_EQ(borderImagePainter.topSlice_, 40);
    EXPECT_EQ(borderImagePainter.bottomSlice_, 80);
}

/**
 * @tc.name: BorderImagePainter003
 * @tc.desc: Test cast to BorderImagePainterTestNg
 * @tc.type: FUNC
 */
HWTEST_F(BorderImagePainterTestNg, BorderImagePainter003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. push widthProp != nullptr.
     * @tc.steps: step1. Build a object borderImagePainter.
     */
    NG::BorderImageProperty borderImageProperty;
    RSImage image;
    Testing::MockCanvas canvas;
    CallBack(canvas);
    std::unique_ptr<NG::BorderWidthProperty> widthProp { std::make_unique<NG::BorderWidthProperty>(BORDER_WIDTH_TEST) };
    NG::BorderImagePainter borderImagePainter(borderImageProperty, widthProp, PAINTSIZE, image, DIPSCALE);

    /**
     * @tc.steps: step2. push borderImageProperty.propBorderImage is not null.
     * @tc.steps: step2. push borderImagePainter.leftSlice_ > imageWidth_.
     * @tc.steps: step2. call InitBorderImageSlice.
     */
    auto testBorderImage = MakeBorderImage();
    testBorderImage->needFillCenter_ = true;

    borderImageProperty.propBorderImage = AceType::Claim(testBorderImage);
    borderImageProperty.propBorderImageSource = ImageSourceInfo(SRC_IMAGES);
    borderImageProperty.propHasBorderImageSlice = true;

    borderImagePainter.borderImageProperty_ = std::move(borderImageProperty);
    borderImagePainter.leftSlice_ = 120.0;
    borderImagePainter.rightSlice_ = 240.0;
    borderImagePainter.topSlice_ = 120.0;
    borderImagePainter.bottomSlice_ = 240.0;
    borderImagePainter.InitBorderImageSlice();
    borderImagePainter.PaintBorderImage(OFFSET_F, canvas);

    /**
     * @tc.expected: the borderImagePainter.leftSlice_ is expected results.
     * @tc.expected: the borderImagePainter.rightSlice_ is expected results.
     */
    EXPECT_EQ(borderImagePainter.leftSlice_, 100);
    EXPECT_EQ(borderImagePainter.rightSlice_, 100);
    EXPECT_EQ(borderImagePainter.topSlice_, 100);
    EXPECT_EQ(borderImagePainter.bottomSlice_, 100);
}

/**
 * @tc.name: BorderImagePainter004
 * @tc.desc: Test cast to BorderImagePainterTestNg
 * @tc.type: FUNC
 */
HWTEST_F(BorderImagePainterTestNg, BorderImagePainter004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. push widthProp != nullptr.
     * @tc.steps: step1. Build a object borderImagePainter.
     */
    NG::BorderImageProperty borderImageProperty;
    RSImage image;
    std::unique_ptr<NG::BorderWidthProperty> widthProp { std::make_unique<NG::BorderWidthProperty>(BORDER_WIDTH_TEST) };
    NG::BorderImagePainter borderImagePainter(borderImageProperty, widthProp, PAINTSIZE, image, DIPSCALE);

    /**
     * @tc.steps: step2. push borderImageProperty.propBorderImage is not null.
     * @tc.steps: step2. call InitBorderImageWidth.
     */
    auto testBorderImage = MakeBorderImage();

    borderImageProperty.propBorderImage = AceType::Claim(testBorderImage);
    borderImageProperty.propBorderImageSource = ImageSourceInfo(SRC_IMAGES);
    borderImageProperty.propHasBorderImageWidth = true;

    borderImagePainter.borderImageProperty_ = std::move(borderImageProperty);
    borderImagePainter.InitBorderImageWidth();

    auto borderImage = borderImagePainter.borderImageProperty_.GetBorderImageValue();
    BorderImageEdge imageLeft = borderImage->GetBorderImageEdge(DIRECTION_LEFT);
    BorderImageEdge imageTop = borderImage->GetBorderImageEdge(DIRECTION_RIGHT);
    BorderImageEdge imageRight = borderImage->GetBorderImageEdge(DIRECTION_TOP);
    BorderImageEdge imageBottom = borderImage->GetBorderImageEdge(DIRECTION_BOTTOM);

    /**
     * @tc.expected: the imageLeft.GetBorderImageWidth() is expected results.
     * @tc.expected: the imageTop.GetBorderImageWidth() is expected results.
     */
    EXPECT_EQ(imageLeft.GetBorderImageWidth(), DIMENSION_WIDTH);
    EXPECT_EQ(imageTop.GetBorderImageWidth(), DIMENSION_WIDTH);
    EXPECT_EQ(imageRight.GetBorderImageWidth(), DIMENSION_WIDTH);
    EXPECT_EQ(imageBottom.GetBorderImageWidth(), DIMENSION_WIDTH);
}

/**
 * @tc.name: BorderImagePainter005
 * @tc.desc: Test cast to BorderImagePainterTestNg
 * @tc.type: FUNC
 */
HWTEST_F(BorderImagePainterTestNg, BorderImagePainter005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. push widthProp != nullptr.
     * @tc.steps: step1. Build a object borderImagePainter.
     */
    NG::BorderImageProperty borderImageProperty;
    RSImage image;
    std::unique_ptr<NG::BorderWidthProperty> widthProp { std::make_unique<NG::BorderWidthProperty>(BORDER_WIDTH_TEST) };
    NG::BorderImagePainter borderImagePainter(borderImageProperty, widthProp, PAINTSIZE, image, DIPSCALE);

    /**
     * @tc.steps: step2. push borderImageProperty.propBorderImage is not null.
     * @tc.steps: step2. call InitBorderImageOutset.
     */
    auto testBorderImage = MakeBorderImage();

    borderImageProperty.propBorderImage = AceType::Claim(testBorderImage);
    borderImageProperty.propBorderImageSource = ImageSourceInfo(SRC_IMAGES);
    borderImageProperty.propHasBorderImageOutset = true;

    borderImagePainter.borderImageProperty_ = std::move(borderImageProperty);
    borderImagePainter.InitBorderImageOutset();

    auto borderImage = borderImagePainter.borderImageProperty_.GetBorderImageValue();
    BorderImageEdge imageLeft = borderImage->GetBorderImageEdge(DIRECTION_LEFT);
    BorderImageEdge imageTop = borderImage->GetBorderImageEdge(DIRECTION_RIGHT);
    BorderImageEdge imageRight = borderImage->GetBorderImageEdge(DIRECTION_TOP);
    BorderImageEdge imageBottom = borderImage->GetBorderImageEdge(DIRECTION_BOTTOM);

    /**
     * @tc.expected: the imageLeft.GetBorderImageOutset() is expected results.
     * @tc.expected: the imageTop.GetBorderImageOutset() is expected results.
     */
    EXPECT_EQ(imageLeft.GetBorderImageOutset(), DIMENSION_OUTSET);
    EXPECT_EQ(imageTop.GetBorderImageOutset(), DIMENSION_OUTSET);
    EXPECT_EQ(imageRight.GetBorderImageOutset(), DIMENSION_OUTSET);
    EXPECT_EQ(imageBottom.GetBorderImageOutset(), DIMENSION_OUTSET);
}

/**
 * @tc.name: BorderImagePainter006
 * @tc.desc: Test cast to BorderImagePainterTestNg
 * @tc.type: FUNC
 */
HWTEST_F(BorderImagePainterTestNg, BorderImagePainter006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. push widthProp = nullptr.
     * @tc.steps: step1. Build a object borderImagePainter.
     */
    NG::BorderImageProperty borderImageProperty;
    RSImage image;
    std::unique_ptr<NG::BorderWidthProperty> widthProp;
    NG::BorderImagePainter borderImagePainter(borderImageProperty, widthProp, PAINTSIZE, image, DIPSCALE);

    /**
     * @tc.steps: step2. push borderImageProperty.propBorderImage is null.
     * @tc.steps: step2. push propHasBorderImageWidth and propHasBorderImageOutset is true.
     * @tc.steps: step2. call InitBorderImageWidth and InitBorderImageOutset.
     */
    borderImageProperty.propBorderImage = AceType::MakeRefPtr<BorderImage>();
    borderImageProperty.propBorderImageSource = ImageSourceInfo(SRC_IMAGES);
    borderImageProperty.propHasBorderImageWidth = true;
    borderImageProperty.propHasBorderImageOutset = true;

    borderImagePainter.borderImageProperty_ = std::move(borderImageProperty);
    borderImagePainter.InitBorderImageWidth();
    borderImagePainter.InitBorderImageOutset();

    /**
     * @tc.expected: the borderImagePainter.borderCenterWidth_ is expected results.
     * @tc.expected: the borderImagePainter.imageCenterWidth_ is expected results.
     */
    auto result = borderImagePainter.widthProp_;
    EXPECT_EQ(result.leftDimen, std::nullopt);
    EXPECT_EQ(result.topDimen, std::nullopt);
    EXPECT_EQ(result.rightDimen, std::nullopt);
    EXPECT_EQ(result.bottomDimen, std::nullopt);
}

/**
 * @tc.name: BorderImagePainter007
 * @tc.desc: Test cast to BorderImagePainterTestNg
 * @tc.type: FUNC
 */
HWTEST_F(BorderImagePainterTestNg, BorderImagePainter007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. push widthProp = nullptr.
     * @tc.steps: step1. Build a object borderImagePainter.
     */
    NG::BorderImageProperty borderImageProperty;
    RSImage image;
    Testing::MockCanvas canvas;
    CallBack(canvas);
    std::unique_ptr<NG::BorderWidthProperty> widthProp;
    NG::BorderImagePainter borderImagePainter(borderImageProperty, widthProp, PAINTSIZE, image, DIPSCALE);

    /**
     * @tc.steps: step2. call PaintBorderImage .
     * @tc.expected: the borderImagePainter.imageWidth_ is 100.
     */
    borderImagePainter.PaintBorderImage(OFFSET_F, canvas);
    EXPECT_EQ(borderImagePainter.imageWidth_, 100);
    EXPECT_EQ(borderImagePainter.imageHeight_, 100);

    /**
     * @tc.steps: step3. push borderImageProperty.propBorderImage is default value.
     * @tc.steps: step3. push paintCornersOnly_ is true, call PaintBorderImage.
     * @tc.expected: the borderImagePainter.hasWidthProp_ is false.
     */
    borderImageProperty.propBorderImage = AceType::MakeRefPtr<BorderImage>();
    borderImagePainter.borderImageProperty_ = std::move(borderImageProperty);
    borderImagePainter.paintCornersOnly_ = true;
    borderImagePainter.PaintBorderImage(OFFSET_F, canvas);
    EXPECT_EQ(borderImagePainter.hasWidthProp_, false);
}

/**
 * @tc.name: BorderImagePainter008
 * @tc.desc: Test cast to BorderImagePainterTestNg
 * @tc.type: FUNC
 */
HWTEST_F(BorderImagePainterTestNg, BorderImagePainter008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. push widthProp != nullptr.
     * @tc.steps: step1. Build a object borderImagePainter.
     */
    NG::BorderImageProperty borderImageProperty;
    RSImage image;
    Testing::MockCanvas canvas;
    CallBack(canvas);
    std::unique_ptr<NG::BorderWidthProperty> widthProp { std::make_unique<NG::BorderWidthProperty>(BORDER_WIDTH_TEST) };
    NG::BorderImagePainter borderImagePainter(borderImageProperty, widthProp, PAINTSIZE, image, DIPSCALE);

    /**
     * @tc.steps: step3. push borderImagePainter.borderImageProperty_.GetBorderImageValue() is new value.
     * @tc.steps: step3. push paintCornersOnly_ is true, call PaintBorderImage.
     * @tc.expected: Return expected results.
     */
    auto testBorderImage = MakeBorderImage();

    for (int32_t id = 0; id < 5; id++) {
        auto state = static_cast<BorderImageRepeat>(id);
        testBorderImage->repeatMode_ = state;
        borderImageProperty.propBorderImage = AceType::Claim(testBorderImage);
        borderImagePainter.borderImageProperty_ = std::move(borderImageProperty);
        borderImagePainter.PaintBorderImage(OFFSET_F, canvas);

        switch (borderImagePainter.borderImageProperty_.GetBorderImageValue()->GetRepeatMode()) {
            case BorderImageRepeat::STRETCH:
            case BorderImageRepeat::SPACE:
            case BorderImageRepeat::ROUND:
            case BorderImageRepeat::REPEAT:
                EXPECT_EQ(borderImagePainter.imageWidth_, 100);
                EXPECT_EQ(borderImagePainter.imageHeight_, 100);
                break;
            default:
                LOGE("Unsupported Border Image repeat mode");
        }
    }
}

/**
 * @tc.name: BorderImagePainter009
 * @tc.desc: Test cast to BorderImagePainterTestNg
 * @tc.type: FUNC
 */
HWTEST_F(BorderImagePainterTestNg, BorderImagePainter009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. push widthProp != nullptr.
     * @tc.steps: step1. Build a object borderImagePainter.
     */
    NG::BorderImageProperty borderImageProperty;
    RSImage image;
    Testing::MockCanvas canvas;
    std::unique_ptr<NG::BorderWidthProperty> widthProp { std::make_unique<NG::BorderWidthProperty>(BORDER_WIDTH_TEST) };
    NG::BorderImagePainter borderImagePainter(borderImageProperty, widthProp, PAINTSIZE, image, DIPSCALE);

    /**
     * @tc.steps: step2. push borderImagePainter.borderImageProperty_.GetBorderImageValue() is new value.
     * @tc.steps: step2. push borderCenterWidth_ is FIVE, imageCenterWidth_ is ONE.
     */
    auto testBorderImage = MakeBorderImage();
    borderImageProperty.propBorderImage = AceType::Claim(testBorderImage);

    borderImagePainter.borderImageProperty_ = std::move(borderImageProperty);
    borderImagePainter.borderCenterWidth_ = FIVE;
    borderImagePainter.borderCenterHeight_ = FIVE;
    borderImagePainter.imageCenterWidth_ = ONE;
    borderImagePainter.imageCenterHeight_ = ONE;

    /**
     * @tc.steps: step3. call PaintBorderImageRound PaintBorderImageSpace and PaintBorderImageRepeat.
     * @tc.expected: expected the widthCount and heightCount is 0.
     */
    borderImagePainter.PaintBorderImageRound(OFFSET_F, canvas);
    borderImagePainter.PaintBorderImageSpace(OFFSET_F, canvas);
    borderImagePainter.PaintBorderImageRepeat(OFFSET_F, canvas);
    auto widthCount = fmod(borderImagePainter.borderCenterWidth_, borderImagePainter.imageCenterWidth_);
    auto heightCount = fmod(borderImagePainter.borderCenterHeight_, borderImagePainter.imageCenterHeight_);
    EXPECT_EQ(widthCount, 0);
    EXPECT_EQ(heightCount, 0);
}

/**
 * @tc.name: BorderImagePainter010
 * @tc.desc: Test cast to BorderImagePainterTestNg
 * @tc.type: FUNC
 */
HWTEST_F(BorderImagePainterTestNg, BorderImagePainter010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. push widthProp != nullptr.
     * @tc.steps: step1. Build a object borderImagePainter.
     */
    NG::BorderImageProperty borderImageProperty;
    RSImage image;
    Testing::MockCanvas canvas;
    std::unique_ptr<NG::BorderWidthProperty> widthProp { std::make_unique<NG::BorderWidthProperty>(BORDER_WIDTH_TEST) };
    NG::BorderImagePainter borderImagePainter(borderImageProperty, widthProp, PAINTSIZE, image, DIPSCALE);

    /**
     * @tc.steps: step2. push borderImagePainter.borderImageProperty_.GetBorderImageValue() is new value.
     * @tc.steps: step2. push borderCenterWidth_ is TWO, imageCenterWidth_ is FIVE.
     */
    auto testBorderImage = MakeBorderImage();
    borderImageProperty.propBorderImage = AceType::Claim(testBorderImage);

    borderImagePainter.borderImageProperty_ = std::move(borderImageProperty);
    borderImagePainter.borderCenterWidth_ = TWO;
    borderImagePainter.borderCenterHeight_ = TWO;
    borderImagePainter.imageCenterWidth_ = FIVE;
    borderImagePainter.imageCenterHeight_ = FIVE;

    /**
     * @tc.steps: step3. call PaintBorderImageRound PaintBorderImageSpace and PaintBorderImageRepeat.
     * @tc.expected: expected the widthCount and heightCount is 2.
     */
    borderImagePainter.PaintBorderImageRepeat(OFFSET_F, canvas);
    auto widthCount = fmod(borderImagePainter.borderCenterWidth_, borderImagePainter.imageCenterWidth_);
    auto heightCount = fmod(borderImagePainter.borderCenterHeight_, borderImagePainter.imageCenterHeight_);
    EXPECT_EQ(widthCount, 2);
    EXPECT_EQ(heightCount, 2);
}

/**
 * @tc.name: BorderImagePainter011
 * @tc.desc: Test cast to BorderImagePainterTestNg
 * @tc.type: FUNC
 */
HWTEST_F(BorderImagePainterTestNg, BorderImagePainter011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. push widthProp != nullptr.
     * @tc.steps: step1. Build a object borderImagePainter.
     */
    NG::BorderImageProperty borderImageProperty;
    RSImage image;
    Testing::MockCanvas canvas;
    std::unique_ptr<NG::BorderWidthProperty> widthProp { std::make_unique<NG::BorderWidthProperty>(BORDER_WIDTH_TEST) };
    NG::BorderImagePainter borderImagePainter(borderImageProperty, widthProp, PAINTSIZE, image, DIPSCALE);

    /**
     * @tc.steps: step2. push borderImagePainter.borderImageProperty_.GetBorderImageValue() is new value.
     * @tc.steps: step2. push borderCenterWidth_ is minus, imageCenterWidth_ is TWO.
     */
    double minus = -1.0;
    auto testBorderImage = MakeBorderImage();
    borderImageProperty.propBorderImage = AceType::Claim(testBorderImage);

    borderImagePainter.borderImageProperty_ = std::move(borderImageProperty);
    borderImagePainter.borderCenterWidth_ = minus;
    borderImagePainter.borderCenterHeight_ = minus;
    borderImagePainter.imageCenterWidth_ = TWO;
    borderImagePainter.imageCenterHeight_ = TWO;

    /**
     * @tc.steps: step3. call PaintBorderImageRepeat.
     * @tc.expected: expected the widthCount and heightCount is minus.
     */
    borderImagePainter.PaintBorderImageRepeat(OFFSET_F, canvas);
    auto widthCount = fmod(borderImagePainter.borderCenterWidth_, borderImagePainter.imageCenterWidth_);
    auto heightCount = fmod(borderImagePainter.borderCenterHeight_, borderImagePainter.imageCenterHeight_);
    EXPECT_EQ(widthCount, minus);
    EXPECT_EQ(heightCount, minus);

    /**
     * @tc.steps: step4. push value is minus, call ParseNegativeNumberToZeroOrCeil.
     * @tc.expected: expected the minus = ZERO_TEST.
     */
    borderImagePainter.ParseNegativeNumberToZeroOrCeil(minus);
    EXPECT_EQ(minus, ZERO_TEST);
}
} // namespace OHOS::Ace
