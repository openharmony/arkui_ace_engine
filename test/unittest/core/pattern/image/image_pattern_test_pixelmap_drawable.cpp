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

/**
 * @file image_pattern_test_pixelmap_drawable.cpp
 * @brief TDD test coverage for PixelMapDrawableDescriptor integration in ImagePattern
 */

#include "image_base.h"
#include "test/mock/frameworks/base/image/mock_pixel_map.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t MOCK_IMAGE_WIDTH = 100;
constexpr int32_t MOCK_IMAGE_HEIGHT = 200;
} // namespace

class MockPixelMapDrawableDescriptor : public DrawableDescriptor {
public:
    MOCK_METHOD(DrawableDescriptorLoadResult, LoadSync, ());
    MOCK_METHOD(RefPtr<PixelMap>, GetPixelMap, ());
};

class ImagePatternPixelMapDrawableTestNg : public ImageBases {
public:
    void SetUp() override
    {
        ImageBases::SetUp();
        mockDrawable_ = AceType::MakeRefPtr<MockPixelMapDrawableDescriptor>();
    }

    RefPtr<MockPixelMapDrawableDescriptor> mockDrawable_;
};

/**
 * @tc.name: SetPixelMapDrawable001
 * @tc.desc: SetPixelMapDrawable stores the drawable reference
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPixelMapDrawableTestNg, SetPixelMapDrawable001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create ImagePattern and call SetPixelMapDrawable
     */
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->SetPixelMapDrawable(mockDrawable_);

    /**
     * @tc.expected: drawable_ is set to the mock drawable
     */
    EXPECT_EQ(pattern->drawable_, mockDrawable_);
}

/**
 * @tc.name: SetPixelMapDrawable002
 * @tc.desc: SetPixelMapDrawable with nullptr clears the drawable
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPixelMapDrawableTestNg, SetPixelMapDrawable002, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->drawable_ = mockDrawable_;
    pattern->SetPixelMapDrawable(nullptr);

    EXPECT_EQ(pattern->drawable_, nullptr);
}

/**
 * @tc.name: LoadPixelMapDrawable001
 * @tc.desc: LoadPixelMapDrawable returns early when image type is not PIXELMAP_DRAWABLE
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPixelMapDrawableTestNg, LoadPixelMapDrawable001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->imageType_ = ImageType::BASE;
    pattern->drawable_ = mockDrawable_;

    EXPECT_CALL(*mockDrawable_, LoadSync()).Times(0);

    pattern->LoadPixelMapDrawable();
}

/**
 * @tc.name: LoadPixelMapDrawable002
 * @tc.desc: LoadPixelMapDrawable returns early when drawable_ is null
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPixelMapDrawableTestNg, LoadPixelMapDrawable002, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->imageType_ = ImageType::PIXELMAP_DRAWABLE;
    pattern->drawable_ = nullptr;

    pattern->LoadPixelMapDrawable();
    // no crash, no-op expected
}

/**
 * @tc.name: LoadPixelMapDrawableSync001
 * @tc.desc: LoadPixelMapDrawableSync loads pixelmap and updates ImageSourceInfo
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPixelMapDrawableTestNg, LoadPixelMapDrawableSync001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->imageType_ = ImageType::PIXELMAP_DRAWABLE;
    pattern->syncLoad_ = true;
    pattern->drawable_ = mockDrawable_;

    DrawableDescriptorLoadResult result = { MOCK_IMAGE_WIDTH, MOCK_IMAGE_HEIGHT, 0 };
    EXPECT_CALL(*mockDrawable_, LoadSync()).WillOnce(Return(result));
    auto mockPixelMap = AceType::MakeRefPtr<MockPixelMap>();
    EXPECT_CALL(*mockDrawable_, GetPixelMap()).WillOnce(Return(mockPixelMap));

    pattern->LoadPixelMapDrawableSync();

    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto srcInfo = layoutProperty->GetImageSourceInfo();
    ASSERT_NE(srcInfo, std::nullopt);
    EXPECT_TRUE(srcInfo->IsPixmap());
}

/**
 * @tc.name: LoadPixelMapDrawableSync002
 * @tc.desc: LoadPixelMapDrawableSync with error code does not update ImageSourceInfo
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPixelMapDrawableTestNg, LoadPixelMapDrawableSync002, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->imageType_ = ImageType::PIXELMAP_DRAWABLE;
    pattern->syncLoad_ = true;
    pattern->drawable_ = mockDrawable_;

    DrawableDescriptorLoadResult result = { 0, 0, -1 };
    EXPECT_CALL(*mockDrawable_, LoadSync()).WillOnce(Return(result));
    EXPECT_CALL(*mockDrawable_, GetPixelMap()).Times(0);

    pattern->LoadPixelMapDrawableSync();

    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: LoadPixelMapDrawableSync003
 * @tc.desc: LoadPixelMapDrawableSync returns early when not PIXELMAP_DRAWABLE
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPixelMapDrawableTestNg, LoadPixelMapDrawableSync003, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->imageType_ = ImageType::BASE;
    pattern->syncLoad_ = true;
    pattern->drawable_ = mockDrawable_;

    EXPECT_CALL(*mockDrawable_, LoadSync()).Times(0);

    pattern->LoadPixelMapDrawableSync();
}

/**
 * @tc.name: LoadPixelMapDrawableSync004
 * @tc.desc: LoadPixelMapDrawableSync returns early when syncLoad_ is false
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPixelMapDrawableTestNg, LoadPixelMapDrawableSync004, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->imageType_ = ImageType::PIXELMAP_DRAWABLE;
    pattern->syncLoad_ = false;
    pattern->drawable_ = mockDrawable_;

    EXPECT_CALL(*mockDrawable_, LoadSync()).Times(0);

    pattern->LoadPixelMapDrawableSync();
}

/**
 * @tc.name: OnPixelMapDrawableLoaded001
 * @tc.desc: OnPixelMapDrawableLoaded with valid result updates ImageSourceInfo
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPixelMapDrawableTestNg, OnPixelMapDrawableLoaded001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->drawable_ = mockDrawable_;

    DrawableDescriptorLoadResult result = { MOCK_IMAGE_WIDTH, MOCK_IMAGE_HEIGHT, 0 };
    auto mockPixelMap = AceType::MakeRefPtr<MockPixelMap>();
    EXPECT_CALL(*mockDrawable_, GetPixelMap()).WillOnce(Return(mockPixelMap));

    pattern->OnPixelMapDrawableLoaded(result);

    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto srcInfo = layoutProperty->GetImageSourceInfo();
    ASSERT_NE(srcInfo, std::nullopt);
    EXPECT_TRUE(srcInfo->IsPixmap());
}

/**
 * @tc.name: OnPixelMapDrawableLoaded002
 * @tc.desc: OnPixelMapDrawableLoaded with error code returns early
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPixelMapDrawableTestNg, OnPixelMapDrawableLoaded002, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->drawable_ = mockDrawable_;

    DrawableDescriptorLoadResult result = { 0, 0, -1 };
    EXPECT_CALL(*mockDrawable_, GetPixelMap()).Times(0);

    pattern->OnPixelMapDrawableLoaded(result);

    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: OnPixelMapDrawableLoaded003
 * @tc.desc: OnPixelMapDrawableLoaded returns early when drawable_ is null
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPixelMapDrawableTestNg, OnPixelMapDrawableLoaded003, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->drawable_ = nullptr;

    DrawableDescriptorLoadResult result = { MOCK_IMAGE_WIDTH, MOCK_IMAGE_HEIGHT, 0 };

    pattern->OnPixelMapDrawableLoaded(result);
    // no crash expected
}

/**
 * @tc.name: OnPixelMapDrawableLoaded004
 * @tc.desc: OnPixelMapDrawableLoaded when GetPixelMap returns nullptr returns early
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPixelMapDrawableTestNg, OnPixelMapDrawableLoaded004, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->drawable_ = mockDrawable_;

    DrawableDescriptorLoadResult result = { MOCK_IMAGE_WIDTH, MOCK_IMAGE_HEIGHT, 0 };
    EXPECT_CALL(*mockDrawable_, GetPixelMap()).WillOnce(Return(nullptr));

    pattern->OnPixelMapDrawableLoaded(result);

    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
}
} // namespace OHOS::Ace::NG
