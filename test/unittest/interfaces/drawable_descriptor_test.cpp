/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "interfaces/inner_api/drawable_descriptor/drawable_descriptor.h"
#include "interfaces/inner_api/drawable_descriptor/image_converter.h"

#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
constexpr int32_t ID = 1;
const uint32_t DENSITY = 0;
const std::string PATH_NAME = "";
} // namespace
class DrawableDescriptorTest : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: DrawableDescTest001
 * @tc.desc: test DrawableDescriptor GetPixelMap when pixMap is empty;
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescTest001, TestSize.Level1)
{
    Napi::DrawableDescriptor drawableDescriptor;
    auto res = drawableDescriptor.GetPixelMap();
    EXPECT_EQ(res, nullptr);
}

/**
 * @tc.name: DrawableDescTest002
 * @tc.desc: test LayeredDrawableDescriptor's member functions;
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create layeredDrawableDescriptor and call GetPixelMap when layeredPixelMap is empty
     * @tc.expected: return nullptr
     */
    std::unique_ptr<uint8_t[]> jsonBuf;
    size_t len = 0;
    std::shared_ptr<Global::Resource::ResourceManager> resourceMgr;
    auto layeredDrawableDescriptor = Napi::LayeredDrawableDescriptor(std::move(jsonBuf), len, std::move(resourceMgr));
    auto res = layeredDrawableDescriptor.GetPixelMap();
    EXPECT_EQ(res, nullptr);

    /**
     * @tc.steps: step2. call GetForeground when foreground is empty
     * @tc.expected: return nullptr
     */
    auto res2 = layeredDrawableDescriptor.GetForeground();
    EXPECT_EQ(res2, nullptr);

    /**
     * @tc.steps: step3. call GetBackground when background is empty
     * @tc.expected: return nullptr
     */
    auto res3 = layeredDrawableDescriptor.GetBackground();
    EXPECT_EQ(res3, nullptr);
}

/**
 * @tc.name: ImageConverterTest001
 * @tc.desc: test ImageConverter's member functions;
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, ImageConverterTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create imageConverter and call PixelFormatToSkColorType
     * @tc.expected: return rightly
     */
    Napi::ImageConverter imageConverter;
    Media::PixelFormat pixelFormat = Media::PixelFormat::BGRA_8888;
    auto res = imageConverter.PixelFormatToSkColorType(pixelFormat);
    EXPECT_EQ(res, SkColorType::kBGRA_8888_SkColorType);

    /**
     * @tc.steps: step2. call AlphaTypeToSkAlphaType
     * @tc.expected: return rightly
     */
    Media::AlphaType alphaType = Media::AlphaType::IMAGE_ALPHA_TYPE_OPAQUE;
    auto res2 = imageConverter.AlphaTypeToSkAlphaType(alphaType);
    EXPECT_EQ(res2, SkAlphaType::kOpaque_SkAlphaType);

    /**
     * @tc.steps: step3. call PixelMapToBitmap
     * @tc.expected: created successfully
     */
    Media::PixelMap pixel;
    auto pixelMap = std::make_shared<Media::PixelMap>(pixel);
    ASSERT_NE(pixelMap, nullptr);
    auto res3 = imageConverter.PixelMapToBitmap(pixelMap);
    EXPECT_NE(res3, nullptr);

    /**
     * @tc.steps: step4. call BitmapToPixelMap
     * @tc.expected: function exits normally
     */
    Media::InitializationOptions opts;
    SkBitmap skBitmap;
    auto bitmap = std::make_shared<SkBitmap>(skBitmap);
    ASSERT_NE(bitmap, nullptr);
    auto res4 = imageConverter.BitmapToPixelMap(bitmap, opts);
    EXPECT_EQ(res4, nullptr);
}
/**
 * @tc.name: DrawableDescTest003
 * @tc.desc: test LayeredDrawableDescriptor::GetMask()
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create layeredDrawableDescriptor and call GetMask when layeredPixelMap is empty
     * @tc.expected: return nullptr
     */
    std::unique_ptr<uint8_t[]> jsonBuf;
    size_t len = 0;
    std::shared_ptr<Global::Resource::ResourceManager> resourceMgr(Global::Resource::CreateResourceManager());
    ASSERT_NE(resourceMgr, nullptr);
    auto layeredDrawableDescriptor = Napi::LayeredDrawableDescriptor(std::move(jsonBuf), len, std::move(resourceMgr));
    auto res = layeredDrawableDescriptor.GetMask();
    EXPECT_EQ(res, nullptr);
    /**
     * @tc.steps: step2. call GetStaticMaskClipPath
     * @tc.expected: return rightly
     */
    auto str = layeredDrawableDescriptor.GetStaticMaskClipPath();
    EXPECT_EQ(str, PATH_NAME);
}

/**
 * @tc.name: DrawableDescTest004
 * @tc.desc: test DrawableDescriptorFactory::Create()
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DrawableDescriptorFactory and call create when RState is not success
     * @tc.expected: return nullptr
     */
    std::unique_ptr<uint8_t[]> jsonBuf;
    std::shared_ptr<Global::Resource::ResourceManager> resourceMgr(Global::Resource::CreateResourceManager());
    ASSERT_NE(resourceMgr, nullptr);
    Napi::DrawableDescriptorFactory drawableDescriptorFactory;
    Global::Resource::RState state(Global::Resource::INVALID_FORMAT);
    Napi::DrawableDescriptor::DrawableType drawableType;
    auto res = drawableDescriptorFactory.Create(ID, resourceMgr, state, drawableType, DENSITY);
    EXPECT_EQ(res, nullptr);

    auto res2 = drawableDescriptorFactory.Create(nullptr, resourceMgr, state, drawableType, DENSITY);
    EXPECT_EQ(res2, nullptr);
}
} // namespace OHOS::Ace