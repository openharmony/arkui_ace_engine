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
#include <securec.h>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "interfaces/inner_api/drawable_descriptor/drawable_descriptor.h"
#include "interfaces/inner_api/drawable_descriptor/image_converter.h"
#include "node_extened.h"
#include "native_drawable_descriptor.h"

#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
constexpr int32_t ID = 1;
const uint32_t DENSITY = 0;
const uint32_t ICONTYPE = 0;
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
    ArkUI_DrawableDescriptor *drawDes = OH_ArkUI_CreateFromNapiDrawable(&drawableDescriptor);
    EXPECT_EQ(drawDes->size, 0);
    delete drawDes;
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
    std::shared_ptr<Global::Resource::ResourceManager> resourceMgr(Global::Resource::CreateResourceManager());
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
     * @tc.steps: step3. call BitmapToPixelMap
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
    std::tuple<int32_t, uint32_t, uint32_t> drawableInfo(ID, ICONTYPE, DENSITY);
    auto res3 = drawableDescriptorFactory.Create(drawableInfo, resourceMgr, state, drawableType);
    EXPECT_EQ(res3, nullptr);

    std::tuple<const char *, uint32_t, uint32_t> drawableInfoName(nullptr, ICONTYPE, DENSITY);
    auto res4 = drawableDescriptorFactory.Create(drawableInfoName, resourceMgr, state, drawableType);
    EXPECT_EQ(res4, nullptr);

    std::pair<std::unique_ptr<uint8_t[]>, size_t> foregroundInfo = { nullptr, 0 };
    std::pair<std::unique_ptr<uint8_t[]>, size_t> backgroundInfo = { nullptr, 0 };
    std::string path = "path";
    auto res5 = drawableDescriptorFactory.Create(foregroundInfo, backgroundInfo, path, drawableType, resourceMgr);
    ASSERT_NE(res5, nullptr);
}

/**
 * @tc.name: DrawableDescTest005
 * @tc.desc: test LayeredDrawableDescriptor's member functions;
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create layeredDrawableDescriptor and call SetMaskPath
     * @tc.expected:return path.
     */
    std::unique_ptr<uint8_t[]> jsonBuf;
    size_t len = 0;
    std::shared_ptr<Global::Resource::ResourceManager> resourceMgr;
    std::string path = "path";
    uint32_t iconType = 1;
    uint32_t density = 2;
    auto layeredDrawableDescriptor = Napi::LayeredDrawableDescriptor(
        std::move(jsonBuf), len, std::move(resourceMgr), path, iconType, density);

    /**
     * @tc.steps: step2. check
     */
    EXPECT_EQ(layeredDrawableDescriptor.maskPath_, path);
    EXPECT_EQ(layeredDrawableDescriptor.iconType_, iconType);
    EXPECT_EQ(layeredDrawableDescriptor.density_, density);
}

/**
 * @tc.name: DrawableDescTest006
 * @tc.desc: test LayeredDrawableDescriptor's member functions;
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create layeredDrawableDescriptor and call SetMaskPath
     * @tc.expected:return path.
     */
    std::unique_ptr<uint8_t[]> jsonBuf;
    size_t len = 0;
    std::shared_ptr<Global::Resource::ResourceManager> resourceMgr;
    std::string path = "path";
    uint32_t iconType = 1;
    uint32_t density = 2;
    auto layeredDrawableDescriptor =
        Napi::LayeredDrawableDescriptor(std::move(jsonBuf), len, std::move(resourceMgr), path, iconType, density);

    /**
     * @tc.steps: step2. check
     */
    std::pair<std::unique_ptr<uint8_t[]>, size_t> foregroundInfo = { nullptr, 0 };
    std::pair<std::unique_ptr<uint8_t[]>, size_t> backgroundInfo = { nullptr, 0 };
    layeredDrawableDescriptor.InitLayeredParam(foregroundInfo, backgroundInfo);

    /**
     * @tc.steps: step2. check
     */
    EXPECT_EQ(layeredDrawableDescriptor.foreground_, std::nullopt);
    EXPECT_EQ(layeredDrawableDescriptor.background_, std::nullopt);
}

/**
 * @tc.name: DrawableDescTest007
 * @tc.desc: test DrawableDescriptor's member functions;
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DrawableDescriptor and call GetDrawableType()
     * @tc.expected:return BASE.
     */
    Napi::DrawableDescriptor drawableDescriptor;
    auto res = drawableDescriptor.GetDrawableType();
    EXPECT_EQ(res, Napi::DrawableDescriptor::DrawableType::BASE);
}

/**
 * @tc.name: DrawableDescTest008
 * @tc.desc: test LayeredDrawableDescriptor's member functions;
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create layeredDrawableDescriptor and call GetDrawableType()
     * @tc.expected:return LAYERED.
     */
    std::unique_ptr<uint8_t[]> jsonBuf;
    size_t len = 0;
    std::shared_ptr<Global::Resource::ResourceManager> resourceMgr;
    std::string path = "path";
    uint32_t iconType = 1;
    uint32_t density = 2;
    auto layeredDrawableDescriptor = Napi::LayeredDrawableDescriptor(
        std::move(jsonBuf), len, std::move(resourceMgr), path, iconType, density);

    /**
     * @tc.steps: step2. check
     */
    auto res = layeredDrawableDescriptor.GetDrawableType();
    EXPECT_EQ(res, Napi::DrawableDescriptor::DrawableType::LAYERED);
}

/**
 * @tc.name: DrawableDescTest009
 * @tc.desc: test AnimatedDrawableDescriptor's member functions;
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create AnimatedDrawableDescriptor and call GetDrawableType()
     * @tc.expected:return ANIMATED.
     */
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMaps;
    int32_t duration = -1;
    int32_t iterations = 2;
    auto* animatedDrawable = new Napi::AnimatedDrawableDescriptor(pixelMaps, duration, iterations);
    auto res = animatedDrawable->GetDrawableType();
    EXPECT_EQ(res, Napi::DrawableDescriptor::DrawableType::ANIMATED);

    /**
     * @tc.steps: step2.  call GetPixelMap()
     * @tc.expected:return nullptr.
     */
    auto pixelMap = animatedDrawable->GetPixelMap();
    EXPECT_EQ(pixelMap, nullptr);

    /**
     * @tc.steps: step3. call GetPixelMapList()
     * @tc.expected: pixelMaps.size().
     */
    auto pixelMapList = animatedDrawable->GetPixelMapList();
    EXPECT_EQ(pixelMapList.size(), pixelMaps.size());

    /**
     * @tc.steps: step4. create AnimatedDrawableDescriptor and call GetDuration()
     * @tc.expected:return 1000.
     */
    duration = 1000;
    iterations = 1;
    animatedDrawable = new Napi::AnimatedDrawableDescriptor(pixelMaps, duration, iterations);
    EXPECT_EQ(animatedDrawable->GetDuration(), 1000);

    /**
     * @tc.steps: step5. create AnimatedDrawableDescriptor and call GetIterations()
     * @tc.expected:return 2.
     */
    EXPECT_EQ(animatedDrawable->GetIterations(), 1);

    /**
     * @tc.steps: step6. create AnimatedDrawableDescriptor and call GetDuration()
     * @tc.expected:return 0.
     */
    duration = -1;
    iterations = -2;
    animatedDrawable = new Napi::AnimatedDrawableDescriptor(pixelMaps, duration, iterations);
    EXPECT_EQ(animatedDrawable->GetDuration(), 0);

    /**
     * @tc.steps: step7. create AnimatedDrawableDescriptor and call GetIterations()
     * @tc.expected:return 1.
     */
    EXPECT_EQ(animatedDrawable->GetIterations(), 1);
}

/**
 * @tc.name: DrawableDescTest0010
 * @tc.desc: test LayeredDrawableDescriptor's member functions;
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescTest0010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create layeredDrawableDescriptor and init mask only
     */
    std::shared_ptr<Global::Resource::ResourceManager> resMgr(Global::Resource::CreateResourceManager());
    auto layeredDrawable = Napi::LayeredDrawableDescriptor();
    /**
     * @tc.steps: step2. init resource name and data
     */
    layeredDrawable.InitialMask(resMgr);
    /**
     * @tc.steps: step2. check creating mask ok
     */
    EXPECT_FALSE(layeredDrawable.GetDefaultMask());
}

/**
 * @tc.name: DrawableDescTest0011
 * @tc.desc: test LayeredDrawableDescriptor's member functions;
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescTest0011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. pixelMap param not exist in pixelMapDrawable 
     */
    std::shared_ptr<Global::Resource::ResourceManager> resMgr(Global::Resource::CreateResourceManager());
    auto layeredDrawable = Napi::LayeredDrawableDescriptor();
    /**
     * @tc.steps: step2. init resource name and data
     */
    layeredDrawable.InitialMask(resMgr);
    /**
     * @tc.steps: step3. update foreground into layeredDrawable
     */
    std::shared_ptr<Media::PixelMap> foreground = std::make_shared<Media::PixelMap>();
    layeredDrawable.SetForeground(foreground);
    layeredDrawable.layeredPixelMap_ = foreground;
    auto composedResult = layeredDrawable.GetPixelMap();
    /**
     * @tc.steps: step3. check pixelMap should not be null since this layeredDrawable is customized
     */
    EXPECT_NE(composedResult, nullptr);
}

/**
 * @tc.name: DrawableDescTest0012
 * @tc.desc: test LayeredDrawableDescriptor's member functions;
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescTest0012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init drawble
     */
    auto layeredDrawable = Napi::LayeredDrawableDescriptor();
    /**
     * @tc.steps: step2. get pixelMap directly from layeredDrawable
     */
    auto composedResult = layeredDrawable.GetPixelMap();
    /**
     * @tc.steps: step3. check pixelMap should be null since this layeredDrawable is not customized
     * therefore foreground, background does not exist when create
     */
    EXPECT_EQ(composedResult, nullptr);
}

/**
 * @tc.name: DrawableDescTest0013
 * @tc.desc: test LayeredDrawableDescriptor's member functions;
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescTest0013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init layeredDrawble
     */
    auto drawable = Napi::DrawableDescriptor();

    /**
     * @tc.steps: step2. set pixelMap to drawable
     */
    drawable.SetPixelMap(std::make_shared<Media::PixelMap>());
    /**
     * @tc.steps: step3. check drawable has pixelMap
     */
    EXPECT_TRUE(drawable.HasPixelMap());
    drawable.ResetPixelMap();
    EXPECT_FALSE(drawable.HasPixelMap());
}

/**
 * @tc.name: DrawableDescTest0014
 * @tc.desc: test LayeredDrawableDescriptor's member functions;
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescTest0014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init layeredDrawble
     */
    auto drawable = Napi::LayeredDrawableDescriptor();

    /**
     * @tc.steps: step2. set param to layeredDrawable
     */
    drawable.SetForeground(std::make_shared<Media::PixelMap>());
    drawable.SetBackground(std::make_shared<Media::PixelMap>());
    drawable.SetMask(std::make_shared<Media::PixelMap>());
    /**
     * @tc.steps: step3. check layeredDrawable is customized 
     */
    EXPECT_TRUE(drawable.Customized());
}

/**
 * @tc.name: DrawableDescTest0015
 * @tc.desc: test AnimatedDrawableDescriptor's member functions;
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescTest0015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create AnimatedDrawableDescriptor
     * @tc.expected:return ANIMATED.
     */
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMaps;
    int32_t duration = -1;
    int32_t iterations = 2;
    auto* animatedDrawable = new Napi::AnimatedDrawableDescriptor(pixelMaps, duration, iterations);
    auto res = animatedDrawable->GetDrawableType();
    EXPECT_EQ(res, Napi::DrawableDescriptor::DrawableType::ANIMATED);

    /**
     * @tc.steps: step2. set value
     */
    animatedDrawable->SetDuration(1000);

    /**
     * @tc.steps: step3. check duration should be the value set.
     */
    EXPECT_EQ(animatedDrawable->GetDuration(), 1000);
}

/**
 * @tc.name: DrawableDescTest0016
 * @tc.desc: test AnimatedDrawableDescriptor's member functions;
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescTest0016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create AnimatedDrawableDescriptor
     * @tc.expected:return ANIMATED.
     */
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMaps;
    int32_t duration = -1;
    int32_t iterations = 2;
    auto* animatedDrawable = new Napi::AnimatedDrawableDescriptor(pixelMaps, duration, iterations);
    auto res = animatedDrawable->GetDrawableType();
    EXPECT_EQ(res, Napi::DrawableDescriptor::DrawableType::ANIMATED);

    /**
     * @tc.steps: step2. set value
     */
    animatedDrawable->SetIterations(1);

    /**
     * @tc.steps: step3. check duration should be the value set.
     */
    EXPECT_EQ(animatedDrawable->GetIterations(), 1);
}

/**
 * @tc.name: DrawableDescTest0017
 * @tc.desc: test LayeredDrawableDescriptor's member functions;
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescTest0017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init layeredDrawable
     */
    auto drawable = Napi::LayeredDrawableDescriptor();

    /**
     * @tc.steps: step2. set param to layeredDrawable
     */
    std::shared_ptr<Media::PixelMap> layeredPixelMap;
    std::shared_ptr<Media::PixelMap> badgedPixelMap;
    std::shared_ptr<Media::PixelMap> compositePixelMap;
    bool ret = drawable.GetCompositePixelMapWithBadge(layeredPixelMap, badgedPixelMap, compositePixelMap);
    /**
     * @tc.steps: step3. check layeredDrawable result
     */
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: DrawableDescTest0018
 * @tc.desc: test LayeredDrawableDescriptor's member functions;
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescTest0018, TestSize.Level1)
{
    auto drawable = Napi::LayeredDrawableDescriptor();;
    const char* item = "item";
    Napi::DrawableItem resItem = drawable.PreGetDrawableItem(nullptr, item);
    EXPECT_EQ(resItem.len_, 0);
    const char* item1 = "";
    resItem = drawable.PreGetDrawableItem(nullptr, item1);
    EXPECT_EQ(resItem.len_, 0);
}

/**
 * @tc.name: DrawableDescTest0019
 * @tc.desc: test LayeredDrawableDescriptor's member functions;
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescTest0019, TestSize.Level1)
{
    auto drawable = Napi::LayeredDrawableDescriptor();
    const char* jsonBuf = "{\"background\":\"background\"}";
    drawable.len_ = strlen(jsonBuf) + 1;
    drawable.jsonBuf_ = std::make_unique<uint8_t[]>(drawable.len_);
    memcpy_s(drawable.jsonBuf_.get(), strlen(jsonBuf), jsonBuf, strlen(jsonBuf));
    auto ret = drawable.PreGetPixelMapFromJsonBuf(nullptr, true);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: DrawableDescTest0020
 * @tc.desc: test LayeredDrawableDescriptor's member functions;
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescTest0020, TestSize.Level1)
{
    auto drawable = Napi::LayeredDrawableDescriptor();
    const char* jsonBuf = "{\"foreground\": \"foreground\"}";
    drawable.len_ = strlen(jsonBuf) + 1;
    drawable.jsonBuf_ = std::make_unique<uint8_t[]>(drawable.len_);
    memcpy_s(drawable.jsonBuf_.get(), strlen(jsonBuf), jsonBuf, strlen(jsonBuf));
    auto ret = drawable.PreGetPixelMapFromJsonBuf(nullptr, false);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: DrawableDescTest0021
 * @tc.desc: test LayeredDrawableDescriptor's member functions;
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescTest0021, TestSize.Level1)
{
    auto drawable = Napi::LayeredDrawableDescriptor();
    auto ret = drawable.GetPixelMapFromBuffer();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: DrawableDescTest0022
 * @tc.desc: test LayeredDrawableDescriptor's member functions;
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescTest0022, TestSize.Level1)
{
    auto drawable = Napi::LayeredDrawableDescriptor();
    Napi::DrawableItem drawableItem;
    drawableItem.state_ = Global::Resource::ERROR;
    uint32_t errorCode = 0;
    auto ret = drawable.CreateImageSource(drawableItem, errorCode);
    EXPECT_TRUE(ret == nullptr);
    drawableItem.state_ = Global::Resource::SUCCESS;
    ret = drawable.CreateImageSource(drawableItem, errorCode);
    EXPECT_TRUE(ret == nullptr);
}

/**
 * @tc.name: DrawableDescTest0023
 * @tc.desc: test LayeredDrawableDescriptor's member functions;
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescTest0023, TestSize.Level1)
{
    auto drawable = Napi::LayeredDrawableDescriptor();
    drawable.backgroundItem_.state_ = Global::Resource::SUCCESS;
    auto ret = drawable.GetPixelMapFromJsonBuf(true);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: DrawableDescTest0024
 * @tc.desc: test LayeredDrawableDescriptor's member functions;
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescTest0024, TestSize.Level1)
{
    auto drawable = Napi::LayeredDrawableDescriptor();
    drawable.maskPath_ = "/data/local/tmp/image/123.jpg";
    auto ret = drawable.GetMaskByPath();
    EXPECT_FALSE(ret);
    std::shared_ptr<Media::PixelMap> pixelMap = std::make_shared<Media::PixelMap>();
    drawable.mask_ = pixelMap;
    ret = drawable.GetMaskByPath();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: DrawableDescTest0025
 * @tc.desc: test LayeredDrawableDescriptor's member functions;
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescTest0025, TestSize.Level1)
{
    auto drawable = Napi::LayeredDrawableDescriptor();
    std::shared_ptr<Global::Resource::ResourceManager> resourceMgr(Global::Resource::CreateResourceManager());
    auto ret = drawable.GetMaskByName(resourceMgr, "name");
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: DrawableDescTest0026
 * @tc.desc: test LayeredDrawableDescriptor's member functions;
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescTest0026, TestSize.Level1)
{
    auto drawable = Napi::LayeredDrawableDescriptor();
    std::shared_ptr<Media::PixelMap> pixelMap = std::make_shared<Media::PixelMap>();
    drawable.foreground_ = pixelMap;
    auto ret = drawable.GetForeground();
    EXPECT_FALSE(ret == nullptr);
}

/**
 * @tc.name: DrawableDescTest0027
 * @tc.desc: test LayeredDrawableDescriptor's member functions;
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescTest0027, TestSize.Level1)
{
    auto drawable = Napi::LayeredDrawableDescriptor();
    std::shared_ptr<Media::PixelMap> pixelMap = std::make_shared<Media::PixelMap>();
    drawable.background_ = pixelMap;
    auto ret = drawable.GetBackground();
    EXPECT_FALSE(ret == nullptr);
}

/**
 * @tc.name: DrawableDescTest0028
 * @tc.desc: test LayeredDrawableDescriptor's member functions;
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescTest0028, TestSize.Level1)
{
    auto drawable = Napi::LayeredDrawableDescriptor();
    std::shared_ptr<Media::PixelMap> pixelMap = std::make_shared<Media::PixelMap>();
    drawable.mask_ = pixelMap;
    auto ret = drawable.GetMask();
    EXPECT_FALSE(ret == nullptr);
}

/**
 * @tc.name: DrawableDescTest0029
 * @tc.desc: test LayeredDrawableDescriptor's member functions;
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescTest0029, TestSize.Level1)
{
    auto drawable = Napi::LayeredDrawableDescriptor();
    std::shared_ptr<Media::PixelMap> pixelMap = std::make_shared<Media::PixelMap>();
    drawable.layeredPixelMap_ = pixelMap;
    auto ret = drawable.GetPixelMap();
    EXPECT_FALSE(ret == nullptr);
}

/**
 * @tc.name: DrawableDescTest0030
 * @tc.desc: test AnimatedDrawableDescriptor's member functions;
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescTest0030, TestSize.Level1)
{
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMaps;
    int32_t duration = -1;
    int32_t iterations = 2;
    auto* animatedDrawable = new Napi::AnimatedDrawableDescriptor(pixelMaps, duration, iterations);
    auto ret = animatedDrawable->GetDuration();
    EXPECT_EQ(ret, 0);
    animatedDrawable->duration_ = 10;
    ret = animatedDrawable->GetDuration();
    EXPECT_EQ(ret, 10);
    ret = animatedDrawable->GetIterations();
    EXPECT_EQ(ret, 2);
    animatedDrawable->iterations_ = -10;
    ret = animatedDrawable->GetIterations();
    EXPECT_EQ(ret, 1);
}

/**
 * @tc.name: DrawableDescTest031
 * @tc.desc: test AnimatedDrawableDescriptor's member functions;
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescTest031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create AnimatedDrawableDescriptor
     * @tc.expected:return ANIMATED.
     */
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMaps;
    int32_t duration = -1;
    int32_t iterations = 2;
    auto* animatedDrawable = new Napi::AnimatedDrawableDescriptor(pixelMaps, duration, iterations);
    auto res = animatedDrawable->GetPixelMap();
    EXPECT_EQ(res, nullptr);
}

/**
 * @tc.name: DrawableDescTest0031
 * @tc.desc: test LayeredDrawableDescriptor's member functions;
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescTest0031, TestSize.Level1)
{
    std::shared_ptr<Global::Resource::ResourceManager> resourceMgr(Global::Resource::CreateResourceManager());
    auto drawable = Napi::LayeredDrawableDescriptor();
    const char* item = "i:1";
    Napi::DrawableItem resItem = drawable.PreGetDrawableItem(resourceMgr, item);
    EXPECT_EQ(resItem.len_, 0);
}

/**
 * @tc.name: DrawableDescTest0032
 * @tc.desc: test AnimatedDrawableDescriptor's member functions;
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescTest0032, TestSize.Level1)
{
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMaps;
    int32_t duration = -1;
    int32_t iterations = 2;
    auto* animatedDrawable = new Napi::AnimatedDrawableDescriptor(pixelMaps, duration, iterations);
    animatedDrawable->SetIterations(-2);
    EXPECT_EQ(animatedDrawable->iterations_, 1);
}

/**
 * @tc.name: DrawableDescTest0033
 * @tc.desc: test AnimatedDrawableDescriptor's member functions;
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescTest0033, TestSize.Level1)
{
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMaps;
    int32_t duration = -1;
    int32_t iterations = 2;
    auto* animatedDrawable = new Napi::AnimatedDrawableDescriptor(pixelMaps, duration, iterations);
    animatedDrawable->SetDuration(0);
    EXPECT_EQ(animatedDrawable->duration_, 0);
}
} // namespace OHOS::Ace
