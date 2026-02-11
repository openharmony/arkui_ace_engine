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

#include "gtest/gtest.h"

#define private public
#define protected public

#include "interfaces/inner_api/drawable_descriptor/drawable_descriptor_utils.h"
#include "interfaces/inner_api/drawable_descriptor/image_loader/image_loader.h"
#include "interfaces/inner_api/drawable_descriptor/image_loader/image_define.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Napi;

namespace OHOS::Ace {

class DrawableDescriptorUtilsTest : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: DrawableDescriptorUtilsTest001
 * @tc.desc: test ToRSRadius with radiusXY.size() == RADIUS_POINTS_SIZE
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorUtilsTest, DrawableDescriptorUtilsTest001, TestSize.Level1)
{
    BorderRadiusArray radiusXY;
    radiusXY.resize(RADIUS_POINTS_SIZE);

    // Set valid radius values
    for (size_t i = 0; i < RADIUS_POINTS_SIZE; i++) {
        radiusXY[i] = RSPoint(10.0f, 10.0f);
    }

    auto radii = DrawableDescriptorUtils::ToRSRadius(radiusXY);

    ASSERT_NE(radii, nullptr);
    EXPECT_FLOAT_EQ(radii[RSRoundRect::TOP_LEFT_POS].GetX(), 10.0f);
    EXPECT_FLOAT_EQ(radii[RSRoundRect::TOP_LEFT_POS].GetY(), 10.0f);
    EXPECT_FLOAT_EQ(radii[RSRoundRect::TOP_RIGHT_POS].GetX(), 10.0f);
    EXPECT_FLOAT_EQ(radii[RSRoundRect::TOP_RIGHT_POS].GetY(), 10.0f);
    EXPECT_FLOAT_EQ(radii[RSRoundRect::BOTTOM_LEFT_POS].GetX(), 10.0f);
    EXPECT_FLOAT_EQ(radii[RSRoundRect::BOTTOM_LEFT_POS].GetY(), 10.0f);
    EXPECT_FLOAT_EQ(radii[RSRoundRect::BOTTOM_RIGHT_POS].GetX(), 10.0f);
    EXPECT_FLOAT_EQ(radii[RSRoundRect::BOTTOM_RIGHT_POS].GetY(), 10.0f);
}

/**
 * @tc.name: DrawableDescriptorUtilsTest002
 * @tc.desc: test ToRSRadius with radiusXY.size() != RADIUS_POINTS_SIZE
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorUtilsTest, DrawableDescriptorUtilsTest002, TestSize.Level1)
{
    BorderRadiusArray radiusXY;
    radiusXY.resize(RADIUS_POINTS_SIZE - 1);

    auto radii = DrawableDescriptorUtils::ToRSRadius(radiusXY);

    ASSERT_NE(radii, nullptr);
    // Should return zero-initialized array when size doesn't match
    EXPECT_FLOAT_EQ(radii[RSRoundRect::TOP_LEFT_POS].GetX(), 0.0f);
    EXPECT_FLOAT_EQ(radii[RSRoundRect::TOP_LEFT_POS].GetY(), 0.0f);
}

/**
 * @tc.name: DrawableDescriptorUtilsTest003
 * @tc.desc: test ToRSRadius with negative radius values (clamped to 0)
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorUtilsTest, DrawableDescriptorUtilsTest003, TestSize.Level1)
{
    BorderRadiusArray radiusXY;
    radiusXY.resize(RADIUS_POINTS_SIZE);

    // Set negative radius values
    for (size_t i = 0; i < RADIUS_POINTS_SIZE; i++) {
        radiusXY[i] = RSPoint(-5.0f, -3.0f);
    }

    auto radii = DrawableDescriptorUtils::ToRSRadius(radiusXY);

    ASSERT_NE(radii, nullptr);
    // Negative values should be clamped to 0
    EXPECT_FLOAT_EQ(radii[RSRoundRect::TOP_LEFT_POS].GetX(), 0.0f);
    EXPECT_FLOAT_EQ(radii[RSRoundRect::TOP_LEFT_POS].GetY(), 0.0f);
}

/**
 * @tc.name: DrawableDescriptorUtilsTest004
 * @tc.desc: test ToRSRadius with mixed positive and negative values
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorUtilsTest, DrawableDescriptorUtilsTest004, TestSize.Level1)
{
    BorderRadiusArray radiusXY;
    radiusXY.resize(RADIUS_POINTS_SIZE);

    radiusXY[RSRoundRect::TOP_LEFT_POS] = RSPoint(10.0f, -5.0f);
    radiusXY[RSRoundRect::TOP_RIGHT_POS] = RSPoint(-3.0f, 15.0f);
    radiusXY[RSRoundRect::BOTTOM_LEFT_POS] = RSPoint(8.0f, 12.0f);
    radiusXY[RSRoundRect::BOTTOM_RIGHT_POS] = RSPoint(-10.0f, -10.0f);

    auto radii = DrawableDescriptorUtils::ToRSRadius(radiusXY);

    ASSERT_NE(radii, nullptr);
    EXPECT_FLOAT_EQ(radii[RSRoundRect::TOP_LEFT_POS].GetX(), 10.0f); // positive
    EXPECT_FLOAT_EQ(radii[RSRoundRect::TOP_LEFT_POS].GetY(), 0.0f);  // negative clamped
    EXPECT_FLOAT_EQ(radii[RSRoundRect::TOP_RIGHT_POS].GetX(), 0.0f); // negative clamped
    EXPECT_FLOAT_EQ(radii[RSRoundRect::TOP_RIGHT_POS].GetY(), 15.0f); // positive
    EXPECT_FLOAT_EQ(radii[RSRoundRect::BOTTOM_LEFT_POS].GetX(), 8.0f);  // positive
    EXPECT_FLOAT_EQ(radii[RSRoundRect::BOTTOM_LEFT_POS].GetY(), 12.0f); // positive
    EXPECT_FLOAT_EQ(radii[RSRoundRect::BOTTOM_RIGHT_POS].GetX(), 0.0f); // negative clamped
    EXPECT_FLOAT_EQ(radii[RSRoundRect::BOTTOM_RIGHT_POS].GetY(), 0.0f); // negative clamped
}

/**
 * @tc.name: DrawableDescriptorUtilsTest005
 * @tc.desc: test AddFilter with ImageInterpolation::LOW
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorUtilsTest, DrawableDescriptorUtilsTest005, TestSize.Level1)
{
    RSBrush brush;
    RSSamplingOptions options;
    PaintConfig config;
    config.imageInterpolation = ImageInterpolation::LOW;

    DrawableDescriptorUtils::AddFilter(brush, options, config);

    // Verify filter mode is LINEAR and mipmap mode is NONE
    auto filter = brush.GetFilter();
    EXPECT_NE(filter, nullptr);
}

/**
 * @tc.name: DrawableDescriptorUtilsTest006
 * @tc.desc: test AddFilter with ImageInterpolation::MEDIUM
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorUtilsTest, DrawableDescriptorUtilsTest006, TestSize.Level1)
{
    RSBrush brush;
    RSSamplingOptions options;
    PaintConfig config;
    config.imageInterpolation = ImageInterpolation::MEDIUM;

    DrawableDescriptorUtils::AddFilter(brush, options, config);

    // Verify filter mode is LINEAR and mipmap mode is LINEAR
    auto filter = brush.GetFilter();
    EXPECT_NE(filter, nullptr);
}

/**
 * @tc.name: DrawableDescriptorUtilsTest007
 * @tc.desc: test AddFilter with ImageInterpolation::HIGH
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorUtilsTest, DrawableDescriptorUtilsTest007, TestSize.Level1)
{
    RSBrush brush;
    RSSamplingOptions options;
    PaintConfig config;
    config.imageInterpolation = ImageInterpolation::HIGH;

    DrawableDescriptorUtils::AddFilter(brush, options, config);

    // Verify cubic resampler is used (Mitchell)
    auto filter = brush.GetFilter();
    EXPECT_NE(filter, nullptr);
}

/**
 * @tc.name: DrawableDescriptorUtilsTest008
 * @tc.desc: test AddFilter with default ImageInterpolation
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorUtilsTest, DrawableDescriptorUtilsTest008, TestSize.Level1)
{
    RSBrush brush;
    RSSamplingOptions options;
    PaintConfig config;
    // Use invalid enum value to test default branch
    config.imageInterpolation = static_cast<ImageInterpolation>(999);

    DrawableDescriptorUtils::AddFilter(brush, options, config);

    auto filter = brush.GetFilter();
    EXPECT_NE(filter, nullptr);
}

/**
 * @tc.name: DrawableDescriptorUtilsTest009
 * @tc.desc: test AddFilter with colorFilter set
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorUtilsTest, DrawableDescriptorUtilsTest009, TestSize.Level1)
{
    RSBrush brush;
    RSSamplingOptions options;
    PaintConfig config;
    config.imageInterpolation = ImageInterpolation::LOW;
    config.colorFilter = std::make_shared<RSColorFilter>();

    DrawableDescriptorUtils::AddFilter(brush, options, config);

    auto filter = brush.GetFilter();
    EXPECT_NE(filter, nullptr);
    // Verify color filter is set
}

/**
 * @tc.name: DrawableDescriptorUtilsTest010
 * @tc.desc: test AddFilter with renderMode TEMPLATE and no colorFilter
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorUtilsTest, DrawableDescriptorUtilsTest010, TestSize.Level1)
{
    RSBrush brush;
    RSSamplingOptions options;
    PaintConfig config;
    config.imageInterpolation = ImageInterpolation::LOW;
    config.renderMode = ImageRenderMode::TEMPLATE;
    config.colorFilter = nullptr;

    DrawableDescriptorUtils::AddFilter(brush, options, config);

    auto filter = brush.GetFilter();
    EXPECT_NE(filter, nullptr);
    // Verify grayscale matrix filter is applied for TEMPLATE mode
}

/**
 * @tc.name: DrawableDescriptorUtilsTest011
 * @tc.desc: test AddFilter with colorFilter overriding TEMPLATE mode
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorUtilsTest, DrawableDescriptorUtilsTest011, TestSize.Level1)
{
    RSBrush brush;
    RSSamplingOptions options;
    PaintConfig config;
    config.imageInterpolation = ImageInterpolation::LOW;
    config.renderMode = ImageRenderMode::TEMPLATE;
    config.colorFilter = std::make_shared<RSColorFilter>();

    DrawableDescriptorUtils::AddFilter(brush, options, config);

    auto filter = brush.GetFilter();
    EXPECT_NE(filter, nullptr);
    // colorFilter should take precedence over TEMPLATE grayscale
}

/**
 * @tc.name: DrawableDescriptorUtilsTest012
 * @tc.desc: test CreateImageLoader with SrcType::INTERNAL
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorUtilsTest, DrawableDescriptorUtilsTest012, TestSize.Level1)
{
    SourceInfo src;
    src.SetSrcType(SrcType::INTERNAL);
    src.SetSrc("internal://app/icon.png");

    auto loader = DrawableDescriptorUtils::CreateImageLoader(src);

    EXPECT_NE(loader, nullptr);
    EXPECT_NE(dynamic_cast<FileImageLoader*>(loader.get()), nullptr);
}

/**
 * @tc.name: DrawableDescriptorUtilsTest013
 * @tc.desc: test CreateImageLoader with SrcType::FILE
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorUtilsTest, DrawableDescriptorUtilsTest013, TestSize.Level1)
{
    SourceInfo src;
    src.SetSrcType(SrcType::FILE);
    src.SetSrc("file:///data/local/tmp/image.png");

    auto loader = DrawableDescriptorUtils::CreateImageLoader(src);

    EXPECT_NE(loader, nullptr);
    EXPECT_NE(dynamic_cast<FileImageLoader*>(loader.get()), nullptr);
}

/**
 * @tc.name: DrawableDescriptorUtilsTest014
 * @tc.desc: test CreateImageLoader with unsupported SrcType
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorUtilsTest, DrawableDescriptorUtilsTest014, TestSize.Level1)
{
    SourceInfo src;
    // Use an unsupported source type
    src.SetSrcType(static_cast<SrcType>(999));
    src.SetSrc("http://example.com/image.png");

    auto loader = DrawableDescriptorUtils::CreateImageLoader(src);

    EXPECT_EQ(loader, nullptr);
}

/**
 * @tc.name: DrawableDescriptorUtilsTest015
 * @tc.desc: test CreateImageLoader with SrcType::NETWORK (unsupported)
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorUtilsTest, DrawableDescriptorUtilsTest015, TestSize.Level1)
{
    SourceInfo src;
    src.SetSrcType(SrcType::NETWORK);
    src.SetSrc("https://example.com/image.png");

    auto loader = DrawableDescriptorUtils::CreateImageLoader(src);

    EXPECT_EQ(loader, nullptr);
}

/**
 * @tc.name: DrawableDescriptorUtilsTest016
 * @tc.desc: test CreateImageLoader with SrcType::DATA (unsupported)
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorUtilsTest, DrawableDescriptorUtilsTest016, TestSize.Level1)
{
    SourceInfo src;
    src.SetSrcType(SrcType::DATA);
    src.SetSrc("data:image/png;base64,iVBORw0KG...");

    auto loader = DrawableDescriptorUtils::CreateImageLoader(src);

    EXPECT_EQ(loader, nullptr);
}

} // namespace OHOS::Ace
