/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include <memory>

#define private public
#define protected public
#include "third_party/skia/include/core/SkBitmap.h"
#include "third_party/skia/include/core/SkPictureRecorder.h"

#include "frameworks/base/geometry/dimension.h"
#include "frameworks/base/geometry/ng/offset_t.h"
#include "frameworks/core/components/common/properties/border_image_edge.h"
#include "frameworks/core/components/common/properties/decoration.h"
#include "frameworks/core/components_ng/base/modifier.h"
#include "frameworks/core/components_ng/render/adapter/rosen_render_context.h"
#include "frameworks/core/components_ng/render/adapter/skia_decoration_painter.h"
#include "frameworks/core/components_ng/render/adapter/svg_canvas_image.h"
#include "frameworks/core/components_ng/render/border_image_painter.h"
#include "frameworks/core/components_ng/render/canvas.h"
#include "frameworks/core/components_ng/render/render_context.h"
#include "frameworks/core/components_ng/test/mock/render/mock_render_context.h"
#undef priate
#undef protected

#include "gtest/gtest.h"
using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
class RosenBorderImagePainterTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
};

void RosenBorderImagePainterTest::SetUpTestCase() {}

void RosenBorderImagePainterTest::TearDownTestCase() {}

void RosenBorderImagePainterTest::SetUp() {}

void RosenBorderImagePainterTest::TearDown() {}

RSImage getRSImage(const SizeF& paintSize)
{
    SkPaint paint;
    paint.setAntiAlias(true);
    auto imageInfo = SkImageInfo::Make(
        paintSize.Width(), paintSize.Height(), SkColorType::kRGBA_8888_SkColorType, SkAlphaType::kOpaque_SkAlphaType);
    SkBitmap skBitmap;
    skBitmap.allocPixels(imageInfo);
    std::unique_ptr<SkCanvas> skCanvas = std::make_unique<SkCanvas>(skBitmap);
    skCanvas->drawPaint(paint);
    auto skImage = SkImage::MakeFromBitmap(skBitmap);
    return RSImage(&skImage);
}

/**
 * @tc.name: RosenBorderImagePainterTest001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RosenBorderImagePainterTest, RosenBorderImagePainterTest001, TestSize.Level1)
{
    BorderImageProperty imgProperty;
    imgProperty.propBorderImage = AceType::MakeRefPtr<BorderImage>("test");
    imgProperty.propHasBorderImageSlice = false;
    imgProperty.propHasBorderImageWidth = false;
    imgProperty.propHasBorderImageOutset = false;
    imgProperty.propHasBorderImageRepeat = false;
    OHOS::Ace::Dimension RosenDimension(20.0);
    BorderWidthProperty borderWidthPro;
    borderWidthPro.SetBorderWidth(RosenDimension);
    SizeF paintSize(20.5, 20.5);
    double dipscale = 5.0;
    auto rsImage = getRSImage(paintSize);
    OHOS::Ace::NG::BorderImagePainter RosenBorderImagePainter(
        false, imgProperty, borderWidthPro, paintSize, rsImage, dipscale);
    RosenBorderImagePainter.leftSlice_ = 22.0;
    RosenBorderImagePainter.rightSlice_ = 22.0;
    RosenBorderImagePainter.topSlice_ = 22.0;
    RosenBorderImagePainter.bottomSlice_ = 22.0;
    RosenBorderImagePainter.imageWidth_ = 20.0;
    RosenBorderImagePainter.imageHeight_ = 20.0;
    EXPECT_TRUE(GreatNotEqual(RosenBorderImagePainter.leftSlice_, RosenBorderImagePainter.imageWidth_));
    EXPECT_TRUE(GreatNotEqual(RosenBorderImagePainter.rightSlice_, RosenBorderImagePainter.imageWidth_));
    EXPECT_TRUE(GreatNotEqual(RosenBorderImagePainter.topSlice_, RosenBorderImagePainter.imageHeight_));
    EXPECT_TRUE(GreatNotEqual(RosenBorderImagePainter.bottomSlice_, RosenBorderImagePainter.imageHeight_));
    RosenBorderImagePainter.InitBorderImageSlice();
}

/**
 * @tc.name: RosenBorderImagePainterTest002
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RosenBorderImagePainterTest, RosenBorderImagePainterTest002, TestSize.Level1)
{
    BorderImageProperty imgProperty;
    imgProperty.propBorderImage = AceType::MakeRefPtr<BorderImage>("test");
    imgProperty.propHasBorderImageSlice = false;
    imgProperty.propHasBorderImageWidth = false;
    imgProperty.propHasBorderImageOutset = false;
    imgProperty.propHasBorderImageRepeat = false;
    OHOS::Ace::Dimension RosenDimension(-20.0);
    BorderWidthProperty borderWidthPro;
    borderWidthPro.SetBorderWidth(RosenDimension);
    SizeF paintSize(20.5, 20.5);
    double dipscale = 5.0;
    auto rsImage = getRSImage(paintSize);
    OHOS::Ace::NG::BorderImagePainter RosenBorderImagePainter(
        false, imgProperty, borderWidthPro, paintSize, rsImage, dipscale);
    RosenBorderImagePainter.leftSlice_ = 20.0;
    RosenBorderImagePainter.rightSlice_ = 20.0;
    RosenBorderImagePainter.topSlice_ = 20.0;
    RosenBorderImagePainter.bottomSlice_ = 20.0;
    RosenBorderImagePainter.imageWidth_ = 22.0;
    RosenBorderImagePainter.imageHeight_ = 22.0;
    EXPECT_FALSE(GreatNotEqual(RosenBorderImagePainter.leftSlice_, RosenBorderImagePainter.imageWidth_));
    EXPECT_FALSE(GreatNotEqual(RosenBorderImagePainter.rightSlice_, RosenBorderImagePainter.imageWidth_));
    EXPECT_FALSE(GreatNotEqual(RosenBorderImagePainter.topSlice_, RosenBorderImagePainter.imageHeight_));
    EXPECT_FALSE(GreatNotEqual(RosenBorderImagePainter.bottomSlice_, RosenBorderImagePainter.imageHeight_));
    RosenBorderImagePainter.InitBorderImageSlice();
}

/**
 * @tc.name: RosenBorderImagePainterTest003
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RosenBorderImagePainterTest, RosenBorderImagePainterTest003, TestSize.Level1)
{
    BorderImageProperty imgProperty;
    imgProperty.propBorderImage = AceType::MakeRefPtr<BorderImage>("test");
    imgProperty.propHasBorderImageSlice = false;
    imgProperty.propHasBorderImageWidth = false;
    imgProperty.propHasBorderImageOutset = false;
    imgProperty.propHasBorderImageRepeat = false;
    OHOS::Ace::Dimension RosenDimension(20.0);
    BorderWidthProperty borderWidthPro;
    borderWidthPro.SetBorderWidth(RosenDimension);
    SizeF paintSize(20.5, 20.5);
    double dipscale = 5.0;
    auto rsImage = getRSImage(paintSize);
    OHOS::Ace::NG::BorderImagePainter RosenBorderImagePainter(
        false, imgProperty, borderWidthPro, paintSize, rsImage, dipscale);
    RosenBorderImagePainter.hasBorderWidthProperty_ = true;
    EXPECT_TRUE(RosenBorderImagePainter.hasBorderWidthProperty_);
    RosenBorderImagePainter.InitBorderImageWidth();
}

/**
 * @tc.name: RosenBorderImagePainterTest004
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RosenBorderImagePainterTest, RosenBorderImagePainterTest004, TestSize.Level1)
{
    BorderImageProperty imgProperty;
    imgProperty.propBorderImage = AceType::MakeRefPtr<BorderImage>("test");
    imgProperty.propHasBorderImageSlice = false;
    imgProperty.propHasBorderImageWidth = false;
    imgProperty.propHasBorderImageOutset = false;
    imgProperty.propHasBorderImageRepeat = false;
    OHOS::Ace::Dimension RosenDimension(20.0);
    BorderWidthProperty borderWidthPro;
    borderWidthPro.SetBorderWidth(RosenDimension);
    SizeF paintSize(20.5, 20.5);
    double dipscale = 5.0;
    auto rsImage = getRSImage(paintSize);
    OHOS::Ace::NG::BorderImagePainter RosenBorderImagePainter(
        false, imgProperty, borderWidthPro, paintSize, rsImage, dipscale);
    RosenBorderImagePainter.hasBorderWidthProperty_ = true;
    EXPECT_TRUE(RosenBorderImagePainter.hasBorderWidthProperty_);
    RosenBorderImagePainter.InitBorderImageOutset();
}

/**
 * @tc.name: RosenBorderImagePainterTest005
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RosenBorderImagePainterTest, RosenBorderImagePainterTest005, TestSize.Level1)
{
    BorderImageProperty imgProperty;
    imgProperty.propBorderImage = AceType::MakeRefPtr<BorderImage>("test");
    imgProperty.propHasBorderImageSlice = false;
    imgProperty.propHasBorderImageWidth = false;
    imgProperty.propHasBorderImageOutset = false;
    imgProperty.propHasBorderImageRepeat = false;
    OHOS::Ace::Dimension RosenDimension(20.0);
    BorderWidthProperty borderWidthPro;
    borderWidthPro.SetBorderWidth(RosenDimension);
    SizeF paintSize(20.5, 20.5);
    double dipscale = 5.0;
    auto rsImage = getRSImage(paintSize);
    RefPtr<OHOS::Ace::NG::BorderImagePainter> RosenBorderImagePainter =
        AceType::MakeRefPtr<OHOS::Ace::NG::BorderImagePainter>(
            false, imgProperty, borderWidthPro, paintSize, rsImage, dipscale);
    EXPECT_TRUE(RosenBorderImagePainter);
    RosenBorderImagePainter->InitPainter();
}

/**
 * @tc.name: RosenBorderImagePainterTest006
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RosenBorderImagePainterTest, RosenBorderImagePainterTest006, TestSize.Level1)
{
    BorderImageProperty imgProperty;
    imgProperty.propBorderImage = AceType::MakeRefPtr<BorderImage>("test");
    imgProperty.propHasBorderImageSlice = false;
    imgProperty.propHasBorderImageWidth = false;
    imgProperty.propHasBorderImageOutset = false;
    imgProperty.propHasBorderImageRepeat = false;
    OHOS::Ace::Dimension RosenDimension(20.0);
    BorderWidthProperty borderWidthPro;
    borderWidthPro.SetBorderWidth(RosenDimension);
    SizeF paintSize(20.5, 20.5);
    double dipscale = 5.0;
    auto rsImage = getRSImage(paintSize);
    OHOS::Ace::NG::BorderImagePainter RosenBorderImagePainter(
        false, imgProperty, borderWidthPro, paintSize, rsImage, dipscale);
    double value1 = 20.0;
    RosenBorderImagePainter.ParseNegativeNumberToZeroOrCeil(value1);
    EXPECT_DOUBLE_EQ(value1, 20.0);
    double value2 = -20.0;
    RosenBorderImagePainter.ParseNegativeNumberToZeroOrCeil(value2);
    EXPECT_DOUBLE_EQ(value2, 0.0);
}
} // namespace OHOS::Ace::NG