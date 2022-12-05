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
#undef private
#undef protected

#include "gtest/gtest.h"
using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
class RosenBorderImagePainterTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
};

void RosenBorderImagePainterTestNg::SetUpTestCase() {}

void RosenBorderImagePainterTestNg::TearDownTestCase() {}

void RosenBorderImagePainterTestNg::SetUp() {}

void RosenBorderImagePainterTestNg::TearDown() {}

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
 * @tc.name: RosenBorderImagePainterTestNg001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RosenBorderImagePainterTestNg, RosenBorderImagePainterTestNg001, TestSize.Level1)
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
    auto borderImage = RosenBorderImagePainter.borderImageProperty_.GetBorderImageValue();
    OHOS::Ace::BorderImageEdge imageLeft = borderImage->GetBorderImageEdge(BorderImageDirection::LEFT);
    OHOS::Ace::BorderImageEdge imageTop = borderImage->GetBorderImageEdge(BorderImageDirection::TOP);
    OHOS::Ace::BorderImageEdge imageRight = borderImage->GetBorderImageEdge(BorderImageDirection::RIGHT);
    OHOS::Ace::BorderImageEdge imageBottom = borderImage->GetBorderImageEdge(BorderImageDirection::BOTTOM);
    EXPECT_TRUE(GreatNotEqual(imageLeft.GetBorderImageSlice().Value(), 0.0));
    EXPECT_TRUE(GreatNotEqual(imageTop.GetBorderImageSlice().Value(), 0.0));
    EXPECT_TRUE(GreatNotEqual(imageRight.GetBorderImageSlice().Value(), 0.0));
    EXPECT_TRUE(GreatNotEqual(imageBottom.GetBorderImageSlice().Value(), 0.0));
    RosenBorderImagePainter.InitBorderImageSlice();
}

/**
 * @tc.name: RosenBorderImagePainterTestNg002
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RosenBorderImagePainterTestNg, RosenBorderImagePainterTestNg002, TestSize.Level1)
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
    RosenBorderImagePainter.hasBorderWidthProperty_ = false;
    EXPECT_FALSE(RosenBorderImagePainter.hasBorderWidthProperty_);
    auto borderImage = RosenBorderImagePainter.borderImageProperty_.GetBorderImageValue();
    OHOS::Ace::BorderImageEdge imageLeft = borderImage->GetBorderImageEdge(BorderImageDirection::LEFT);
    OHOS::Ace::BorderImageEdge imageTop = borderImage->GetBorderImageEdge(BorderImageDirection::TOP);
    OHOS::Ace::BorderImageEdge imageRight = borderImage->GetBorderImageEdge(BorderImageDirection::RIGHT);
    OHOS::Ace::BorderImageEdge imageBottom = borderImage->GetBorderImageEdge(BorderImageDirection::BOTTOM);
    EXPECT_TRUE(GreatNotEqual(imageLeft.GetBorderImageWidth().Value(), 0.0));
    EXPECT_TRUE(GreatNotEqual(imageTop.GetBorderImageWidth().Value(), 0.0));
    EXPECT_TRUE(GreatNotEqual(imageRight.GetBorderImageWidth().Value(), 0.0));
    EXPECT_TRUE(GreatNotEqual(imageBottom.GetBorderImageWidth().Value(), 0.0));
    RosenBorderImagePainter.InitBorderImageWidth();
}

/**
 * @tc.name: RosenBorderImagePainterTestNg003
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RosenBorderImagePainterTestNg, RosenBorderImagePainterTestNg003, TestSize.Level1)
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
    RosenBorderImagePainter.hasBorderWidthProperty_ = false;
    EXPECT_FALSE(RosenBorderImagePainter.hasBorderWidthProperty_);
    auto borderImage = RosenBorderImagePainter.borderImageProperty_.GetBorderImageValue();
    OHOS::Ace::BorderImageEdge imageLeft = borderImage->GetBorderImageEdge(BorderImageDirection::LEFT);
    OHOS::Ace::BorderImageEdge imageTop = borderImage->GetBorderImageEdge(BorderImageDirection::TOP);
    OHOS::Ace::BorderImageEdge imageRight = borderImage->GetBorderImageEdge(BorderImageDirection::RIGHT);
    OHOS::Ace::BorderImageEdge imageBottom = borderImage->GetBorderImageEdge(BorderImageDirection::BOTTOM);
    EXPECT_TRUE(GreatNotEqual(imageLeft.GetBorderImageOutset().Value(), 0.0));
    EXPECT_TRUE(GreatNotEqual(imageTop.GetBorderImageOutset().Value(), 0.0));
    EXPECT_TRUE(GreatNotEqual(imageRight.GetBorderImageOutset().Value(), 0.0));
    EXPECT_TRUE(GreatNotEqual(imageBottom.GetBorderImageOutset().Value(), 0.0));
    RosenBorderImagePainter.InitBorderImageOutset();
}
} // namespace OHOS::Ace::NG