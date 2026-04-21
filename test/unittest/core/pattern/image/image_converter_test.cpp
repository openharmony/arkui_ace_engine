/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"

#define private public
#define protected public

#include "interfaces/inner_api/drawable_descriptor/image_converter.h"
#include "interfaces/inner_api/drawable_descriptor/drawable_descriptor.h"
#include "include/core/SkBitmap.h"
#include "include/core/SkImageInfo.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Napi;

namespace OHOS::Ace {

class ImageConverterTest : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

#ifndef USE_ROSEN_DRAWING

/**
 * @tc.name: ImageConverterTest001
 * @tc.desc: test PixelFormatToSkColorType with BGRA_8888
 * @tc.type: FUNC
 */
HWTEST_F(ImageConverterTest, ImageConverterTest001, TestSize.Level1)
{
    ImageConverter converter;
    Media::PixelFormat pixelFormat = Media::PixelFormat::BGRA_8888;

    auto result = converter.PixelFormatToSkColorType(pixelFormat);

    EXPECT_EQ(result, SkColorType::kBGRA_8888_SkColorType);
}

/**
 * @tc.name: ImageConverterTest002
 * @tc.desc: test PixelFormatToSkColorType with ARGB_8888
 * @tc.type: FUNC
 */
HWTEST_F(ImageConverterTest, ImageConverterTest002, TestSize.Level1)
{
    ImageConverter converter;
    Media::PixelFormat pixelFormat = Media::PixelFormat::ARGB_8888;

    auto result = converter.PixelFormatToSkColorType(pixelFormat);

    EXPECT_EQ(result, SkColorType::kUnknown_SkColorType);
}

/**
 * @tc.name: ImageConverterTest003
 * @tc.desc: test PixelFormatToSkColorType with ALPHA_8
 * @tc.type: FUNC
 */
HWTEST_F(ImageConverterTest, ImageConverterTest003, TestSize.Level1)
{
    ImageConverter converter;
    Media::PixelFormat pixelFormat = Media::PixelFormat::ALPHA_8;

    auto result = converter.PixelFormatToSkColorType(pixelFormat);

    EXPECT_EQ(result, SkColorType::kUnknown_SkColorType);
}

/**
 * @tc.name: ImageConverterTest004
 * @tc.desc: test PixelFormatToSkColorType with RGBA_8888
 * @tc.type: FUNC
 */
HWTEST_F(ImageConverterTest, ImageConverterTest004, TestSize.Level1)
{
    ImageConverter converter;
    Media::PixelFormat pixelFormat = Media::PixelFormat::RGBA_8888;

    auto result = converter.PixelFormatToSkColorType(pixelFormat);

    EXPECT_EQ(result, SkColorType::kUnknown_SkColorType);
}

/**
 * @tc.name: ImageConverterTest005
 * @tc.desc: test PixelFormatToSkColorType with RGB_565
 * @tc.type: FUNC
 */
HWTEST_F(ImageConverterTest, ImageConverterTest005, TestSize.Level1)
{
    ImageConverter converter;
    Media::PixelFormat pixelFormat = Media::PixelFormat::RGB_565;

    auto result = converter.PixelFormatToSkColorType(pixelFormat);

    EXPECT_EQ(result, SkColorType::kUnknown_SkColorType);
}

/**
 * @tc.name: ImageConverterTest006
 * @tc.desc: test PixelFormatToSkColorType with RGB_888
 * @tc.type: FUNC
 */
HWTEST_F(ImageConverterTest, ImageConverterTest006, TestSize.Level1)
{
    ImageConverter converter;
    Media::PixelFormat pixelFormat = Media::PixelFormat::RGB_888;

    auto result = converter.PixelFormatToSkColorType(pixelFormat);

    EXPECT_EQ(result, SkColorType::kUnknown_SkColorType);
}

/**
 * @tc.name: ImageConverterTest007
 * @tc.desc: test PixelFormatToSkColorType with RGBA_F16
 * @tc.type: FUNC
 */
HWTEST_F(ImageConverterTest, ImageConverterTest007, TestSize.Level1)
{
    ImageConverter converter;
    Media::PixelFormat pixelFormat = Media::PixelFormat::RGBA_F16;

    auto result = converter.PixelFormatToSkColorType(pixelFormat);

    EXPECT_EQ(result, SkColorType::kUnknown_SkColorType);
}

/**
 * @tc.name: ImageConverterTest008
 * @tc.desc: test PixelFormatToSkColorType with NV21
 * @tc.type: FUNC
 */
HWTEST_F(ImageConverterTest, ImageConverterTest008, TestSize.Level1)
{
    ImageConverter converter;
    Media::PixelFormat pixelFormat = Media::PixelFormat::NV21;

    auto result = converter.PixelFormatToSkColorType(pixelFormat);

    EXPECT_EQ(result, SkColorType::kUnknown_SkColorType);
}

/**
 * @tc.name: ImageConverterTest009
 * @tc.desc: test PixelFormatToSkColorType with NV12
 * @tc.type: FUNC
 */
HWTEST_F(ImageConverterTest, ImageConverterTest009, TestSize.Level1)
{
    ImageConverter converter;
    Media::PixelFormat pixelFormat = Media::PixelFormat::NV12;

    auto result = converter.PixelFormatToSkColorType(pixelFormat);

    EXPECT_EQ(result, SkColorType::kUnknown_SkColorType);
}

/**
 * @tc.name: ImageConverterTest010
 * @tc.desc: test PixelFormatToSkColorType with CMYK
 * @tc.type: FUNC
 */
HWTEST_F(ImageConverterTest, ImageConverterTest010, TestSize.Level1)
{
    ImageConverter converter;
    Media::PixelFormat pixelFormat = Media::PixelFormat::CMYK;

    auto result = converter.PixelFormatToSkColorType(pixelFormat);

    EXPECT_EQ(result, SkColorType::kUnknown_SkColorType);
}

/**
 * @tc.name: ImageConverterTest011
 * @tc.desc: test PixelFormatToSkColorType with UNKNOWN
 * @tc.type: FUNC
 */
HWTEST_F(ImageConverterTest, ImageConverterTest011, TestSize.Level1)
{
    ImageConverter converter;
    Media::PixelFormat pixelFormat = Media::PixelFormat::UNKNOWN;

    auto result = converter.PixelFormatToSkColorType(pixelFormat);

    EXPECT_EQ(result, SkColorType::kUnknown_SkColorType);
}

/**
 * @tc.name: ImageConverterTest012
 * @tc.desc: test AlphaTypeToSkAlphaType with IMAGE_ALPHA_TYPE_OPAQUE
 * @tc.type: FUNC
 */
HWTEST_F(ImageConverterTest, ImageConverterTest012, TestSize.Level1)
{
    ImageConverter converter;
    Media::AlphaType alphaType = Media::AlphaType::IMAGE_ALPHA_TYPE_OPAQUE;

    auto result = converter.AlphaTypeToSkAlphaType(alphaType);

    EXPECT_EQ(result, SkAlphaType::kOpaque_SkAlphaType);
}

/**
 * @tc.name: ImageConverterTest013
 * @tc.desc: test AlphaTypeToSkAlphaType with IMAGE_ALPHA_TYPE_PREMUL
 * @tc.type: FUNC
 */
HWTEST_F(ImageConverterTest, ImageConverterTest013, TestSize.Level1)
{
    ImageConverter converter;
    Media::AlphaType alphaType = Media::AlphaType::IMAGE_ALPHA_TYPE_PREMUL;

    auto result = converter.AlphaTypeToSkAlphaType(alphaType);

    EXPECT_EQ(result, SkAlphaType::kPremul_SkAlphaType);
}

/**
 * @tc.name: ImageConverterTest014
 * @tc.desc: test AlphaTypeToSkAlphaType with IMAGE_ALPHA_TYPE_UNPREMUL
 * @tc.type: FUNC
 */
HWTEST_F(ImageConverterTest, ImageConverterTest014, TestSize.Level1)
{
    ImageConverter converter;
    Media::AlphaType alphaType = Media::AlphaType::IMAGE_ALPHA_TYPE_UNPREMUL;

    auto result = converter.AlphaTypeToSkAlphaType(alphaType);

    EXPECT_EQ(result, SkAlphaType::kUnpremul_SkAlphaType);
}

/**
 * @tc.name: ImageConverterTest015
 * @tc.desc: test AlphaTypeToSkAlphaType with IMAGE_ALPHA_TYPE_UNKNOWN
 * @tc.type: FUNC
 */
HWTEST_F(ImageConverterTest, ImageConverterTest015, TestSize.Level1)
{
    ImageConverter converter;
    Media::AlphaType alphaType = Media::AlphaType::IMAGE_ALPHA_TYPE_UNKNOWN;

    auto result = converter.AlphaTypeToSkAlphaType(alphaType);

    EXPECT_EQ(result, SkAlphaType::kUnknown_SkAlphaType);
}

#else

/**
 * @tc.name: ImageConverterTest016
 * @tc.desc: test PixelFormatToColorType with BGRA_8888 (Rosen Drawing)
 * @tc.type: FUNC
 */
HWTEST_F(ImageConverterTest, ImageConverterTest016, TestSize.Level1)
{
    ImageConverter converter;
    Media::PixelFormat pixelFormat = Media::PixelFormat::BGRA_8888;

    auto result = converter.PixelFormatToColorType(pixelFormat);

    EXPECT_EQ(result, Rosen::Drawing::ColorType::COLORTYPE_BGRA_8888);
}

/**
 * @tc.name: ImageConverterTest017
 * @tc.desc: test PixelFormatToColorType with ARGB_8888 (Rosen Drawing)
 * @tc.type: FUNC
 */
HWTEST_F(ImageConverterTest, ImageConverterTest017, TestSize.Level1)
{
    ImageConverter converter;
    Media::PixelFormat pixelFormat = Media::PixelFormat::ARGB_8888;

    auto result = converter.PixelFormatToColorType(pixelFormat);

    EXPECT_EQ(result, Rosen::Drawing::ColorType::COLORTYPE_UNKNOWN);
}

/**
 * @tc.name: ImageConverterTest018
 * @tc.desc: test AlphaTypeToAlphaType with IMAGE_ALPHA_TYPE_OPAQUE (Rosen Drawing)
 * @tc.type: FUNC
 */
HWTEST_F(ImageConverterTest, ImageConverterTest018, TestSize.Level1)
{
    ImageConverter converter;
    Media::AlphaType alphaType = Media::AlphaType::IMAGE_ALPHA_TYPE_OPAQUE;

    auto result = converter.AlphaTypeToAlphaType(alphaType);

    EXPECT_EQ(result, Rosen::Drawing::AlphaType::ALPHATYPE_OPAQUE);
}

/**
 * @tc.name: ImageConverterTest019
 * @tc.desc: test AlphaTypeToAlphaType with IMAGE_ALPHA_TYPE_PREMUL (Rosen Drawing)
 * @tc.type: FUNC
 */
HWTEST_F(ImageConverterTest, ImageConverterTest019, TestSize.Level1)
{
    ImageConverter converter;
    Media::AlphaType alphaType = Media::AlphaType::IMAGE_ALPHA_TYPE_PREMUL;

    auto result = converter.AlphaTypeToAlphaType(alphaType);

    EXPECT_EQ(result, Rosen::Drawing::AlphaType::ALPHATYPE_PREMUL);
}

/**
 * @tc.name: ImageConverterTest020
 * @tc.desc: test AlphaTypeToAlphaType with IMAGE_ALPHA_TYPE_UNPREMUL (Rosen Drawing)
 * @tc.type: FUNC
 */
HWTEST_F(ImageConverterTest, ImageConverterTest020, TestSize.Level1)
{
    ImageConverter converter;
    Media::AlphaType alphaType = Media::AlphaType::IMAGE_ALPHA_TYPE_UNPREMUL;

    auto result = converter.AlphaTypeToAlphaType(alphaType);

    EXPECT_EQ(result, Rosen::Drawing::AlphaType::ALPHATYPE_UNPREMUL);
}

/**
 * @tc.name: ImageConverterTest021
 * @tc.desc: test PixelMapToBitmap with nullptr (Rosen Drawing)
 * @tc.type: FUNC
 */
HWTEST_F(ImageConverterTest, ImageConverterTest021, TestSize.Level1)
{
    ImageConverter converter;
    std::shared_ptr<Media::PixelMap> pixelMap = nullptr;

    auto result = converter.PixelMapToBitmap(pixelMap);

    EXPECT_EQ(result, nullptr);
}

#endif

} // namespace OHOS::Ace
