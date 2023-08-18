/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#define protected public
#define private public

#include "test/mock/base/mock_pixel_map.h"

#ifndef USE_ROSEN_DRAWING
#include "core/components_ng/image_provider/adapter/skia_image_data.h"
#else
#include "core/components_ng/image_provider/adapter/rosen/drawing_image_data.h"
#endif
#include "core/components_ng/image_provider/animated_image_object.h"
#include "core/components_ng/image_provider/image_loading_context.h"
#include "core/components_ng/image_provider/image_provider.h"
#include "core/components_ng/image_provider/image_state_manager.h"
#include "core/components_ng/image_provider/pixel_map_image_object.h"
#include "core/components_ng/image_provider/static_image_object.h"
#include "core/components_ng/test/mock/image_provider/mock_image_loader.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace {
const char* SRC_JPG = "file://data/data/com.example.test/res/exampleAlt.jpg";
const char* SRC_THUMBNAIL = "datashare:///media/9/thumbnail/300/300";
constexpr int32_t LENGTH_100 = 100;
constexpr int32_t LENGTH_65 = 65;
constexpr int32_t LENGTH_64 = 64;
constexpr int32_t LENGTH_63 = 63;
constexpr int32_t LENGTH_128 = 128;
} // namespace
namespace OHOS::Ace::NG {
class ImageProviderTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    static void WaitForAsyncTasks();
};

void ImageProviderTestNg::SetUpTestSuite()
{
    MockPipelineBase::SetUp();
    g_loader = AceType::MakeRefPtr<MockImageLoader>();
    g_threads = std::vector<std::thread>();
}

void ImageProviderTestNg::TearDownTestSuite()
{
    MockPipelineBase::TearDown();
    g_loader = nullptr;
}

// wait for load task to finish
void ImageProviderTestNg::WaitForAsyncTasks()
{
    for (auto& thread : g_threads) {
        thread.join();
    }
    g_threads.clear();
}

/**
 * @tc.name: ImageProviderTestNg001
 * @tc.desc: Test ImageProvider Synchronous CreateImageObj failure
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, ImageProviderTestNg001, TestSize.Level1)
{
    EXPECT_CALL(*g_loader, LoadImageData).Times(1);
    auto src = ImageSourceInfo(SRC_JPG);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_EQ(ctx->stateManager_->GetCurrentState(), ImageLoadingState::UNLOADED);
    ctx->LoadImageData();

    EXPECT_EQ(ctx->syncLoad_, true);
    EXPECT_EQ(ctx->imageObj_, nullptr);
    EXPECT_EQ(ctx->stateManager_->GetCurrentState(), ImageLoadingState::LOAD_FAIL);
}

/**
 * @tc.name: ImageProviderTestNg002
 * @tc.desc: Test ImageProvider merging repeated tasks
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, ImageProviderTestNg002, TestSize.Level1)
{
    EXPECT_CALL(*g_loader, LoadImageData).Times(1);
    auto src = ImageSourceInfo(SRC_JPG);
    // create 20 repeated tasks
    std::vector<RefPtr<ImageLoadingContext>> contexts(20);
    for (auto& ctx : contexts) {
        ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), false);
        ctx->LoadImageData();
    }
    // check task map
    {
        std::scoped_lock<std::mutex> lock(ImageProvider::taskMtx_);
        EXPECT_EQ(ImageProvider::tasks_.size(), (size_t)1);
        EXPECT_EQ(ImageProvider::tasks_[src.GetKey()].ctxs_.size(), (size_t)20);
    }
    // wait for load task to finish
    WaitForAsyncTasks();
    std::scoped_lock<std::mutex> lock(ImageProvider::taskMtx_);
    EXPECT_EQ(ImageProvider::tasks_.size(), (size_t)0);
}

/**
 * @tc.name: ImageProviderTestNg003
 * @tc.desc: Test ImageProvider load thumbnail
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, ImageProviderTestNg003, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_THUMBNAIL);

    EXPECT_CALL(*g_loader, LoadDecodedImageData).Times(1);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    ctx->LoadImageData();
}

/**
 * @tc.name: ImageProviderTestNg004
 * @tc.desc: Test ImageProvider load success
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, ImageProviderTestNg004, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_THUMBNAIL);

    EXPECT_CALL(*g_loader, LoadDecodedImageData).Times(1);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr));
    ctx->LoadImageData();
    EXPECT_EQ(ctx->stateManager_->state_, ImageLoadingState::DATA_LOADING);

    WaitForAsyncTasks();

    // mock data loading succeeded
    ctx->stateManager_->state_ = ImageLoadingState::DATA_LOADING;
    auto pixmap = AceType::MakeRefPtr<MockPixelMap>();
    SizeF size(LENGTH_100, LENGTH_100);
    ctx->DataReadyCallback(AceType::MakeRefPtr<PixelMapImageObject>(pixmap, src, size));
    EXPECT_EQ(ctx->stateManager_->state_, ImageLoadingState::DATA_READY);
    EXPECT_TRUE(ctx->NeedAlt());
    EXPECT_EQ(ctx->GetImageSize(), size);
}

/**
 * @tc.name: ImageProviderTestNg005
 * @tc.desc: Test ImageProvider resize condition
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, ImageProviderTestNg005, TestSize.Level1)
{
    auto ctx =
        AceType::MakeRefPtr<ImageLoadingContext>(ImageSourceInfo(), LoadNotifier(nullptr, nullptr, nullptr), true);
    ctx->stateManager_->state_ = ImageLoadingState::DATA_READY;
    ctx->imageObj_ =
        AceType::MakeRefPtr<NG::StaticImageObject>(ImageSourceInfo(SRC_JPG), SizeF(LENGTH_128, LENGTH_128), nullptr);
    SizeF dstSize(LENGTH_100, LENGTH_100);
    auto res = ctx->MakeCanvasImageIfNeed(dstSize, true, ImageFit::COVER);
    EXPECT_TRUE(res);
    EXPECT_EQ(ctx->dstSize_, SizeF(LENGTH_100, LENGTH_100));
    EXPECT_EQ(ctx->stateManager_->state_, ImageLoadingState::LOAD_SUCCESS);

    // call MakeCanvasSize with dstSize in the same level
    res = ctx->MakeCanvasImageIfNeed(SizeF(LENGTH_65, LENGTH_65), true, ImageFit::COVER);
    EXPECT_TRUE(res);
    EXPECT_EQ(ctx->sizeLevel_, LENGTH_128);

    res = ctx->MakeCanvasImageIfNeed(SizeF(LENGTH_128, LENGTH_128), true, ImageFit::COVER);
    EXPECT_FALSE(res);

    res = ctx->MakeCanvasImageIfNeed(SizeF(LENGTH_64, LENGTH_64), true, ImageFit::COVER);
    EXPECT_TRUE(res);
    EXPECT_EQ(ctx->sizeLevel_, LENGTH_64);

    res = ctx->MakeCanvasImageIfNeed(SizeF(LENGTH_63, LENGTH_63), true, ImageFit::COVER);
    EXPECT_FALSE(res);
    EXPECT_EQ(ctx->sizeLevel_, LENGTH_64);
}

/**
 * @tc.name: ImageProviderTestNg006
 * @tc.desc: Test BuildImageObject and frame count check
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, ImageProviderTestNg006, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    EXPECT_FALSE(ImageProvider::BuildImageObject(src, nullptr));

    auto data = AceType::MakeRefPtr<SkiaImageData>(nullptr, 0);
    auto imageObject = ImageProvider::BuildImageObject(src, data);
    EXPECT_TRUE(AceType::DynamicCast<StaticImageObject>(imageObject));

    data = AceType::MakeRefPtr<SkiaImageData>(nullptr, 2);
    imageObject = ImageProvider::BuildImageObject(src, data);
    EXPECT_TRUE(AceType::DynamicCast<AnimatedImageObject>(imageObject));

    // thumbnail src with mismatched data
    src = ImageSourceInfo(SRC_THUMBNAIL);
    EXPECT_FALSE(ImageProvider::BuildImageObject(src, data));
}

/**
 * @tc.name: ImageProviderTestNg007
 * @tc.desc: Test Cancel task
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, ImageProviderTestNg007, TestSize.Level1)
{
    EXPECT_CALL(*g_loader, LoadImageData).Times(1);
    auto src = ImageSourceInfo(SRC_JPG);
    // create 2 repeated tasks
    std::vector<RefPtr<ImageLoadingContext>> contexts(2);
    for (auto& ctx : contexts) {
        ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr));
        ctx->LoadImageData();
    }
    {
        std::scoped_lock<std::mutex> lock(ImageProvider::taskMtx_);
        EXPECT_EQ(ImageProvider::tasks_.size(), (size_t)1);
        auto it = ImageProvider::tasks_.find(src.GetKey());
        EXPECT_NE(it, ImageProvider::tasks_.end());
        // set impl_ to false to force successful cancellation
        it->second.bgTask_.impl_ = nullptr;
    }

    for (auto& ctx : contexts) {
        // nullify ctx to trigger task cancel
        ctx = nullptr;
    }
    // check task is successfully canceled
    {
        std::scoped_lock<std::mutex> lock(ImageProvider::taskMtx_);
        EXPECT_EQ(ImageProvider::tasks_.size(), (size_t)0);
    }
    WaitForAsyncTasks();
    {
        std::scoped_lock<std::mutex> lock(ImageProvider::taskMtx_);
        EXPECT_EQ(ImageProvider::tasks_.size(), (size_t)0);
    }
}

/**
 * @tc.name: RoundUp001
 * @tc.desc: Test RoundUp with invalid input (infinite loop)
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, RoundUp001, TestSize.Level1)
{
    auto ctx =
        AceType::MakeRefPtr<ImageLoadingContext>(ImageSourceInfo(), LoadNotifier(nullptr, nullptr, nullptr), true);
    ctx->imageObj_ = AceType::MakeRefPtr<NG::StaticImageObject>(ImageSourceInfo(SRC_JPG), SizeF(-1, -1), nullptr);
    EXPECT_EQ(ctx->RoundUp(-1), -1);

    ctx->imageObj_ = AceType::MakeRefPtr<NG::StaticImageObject>(ImageSourceInfo(SRC_JPG), SizeF(0, 0), nullptr);
    EXPECT_EQ(ctx->RoundUp(0), -1);

    ctx->imageObj_ = AceType::MakeRefPtr<NG::StaticImageObject>(ImageSourceInfo(SRC_JPG), SizeF(-1, -1), nullptr);
    EXPECT_EQ(ctx->RoundUp(0), -1);

    ctx->imageObj_ = AceType::MakeRefPtr<NG::StaticImageObject>(ImageSourceInfo(SRC_JPG), SizeF(0, 0), nullptr);
    EXPECT_EQ(ctx->RoundUp(-1), -1);

    ctx->imageObj_ =
        AceType::MakeRefPtr<NG::StaticImageObject>(ImageSourceInfo(SRC_JPG), SizeF(LENGTH_128, LENGTH_128), nullptr);
    EXPECT_EQ(ctx->RoundUp(0), -1);

    ctx->imageObj_ = AceType::MakeRefPtr<NG::StaticImageObject>(ImageSourceInfo(SRC_JPG), SizeF(0, 0), nullptr);
    EXPECT_EQ(ctx->RoundUp(LENGTH_128), -1);
}

/**
 * @tc.name: TargetSize001
 * @tc.desc: Test calculating targetSize
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, TargetSize001, TestSize.Level1)
{
    auto ctx =
        AceType::MakeRefPtr<ImageLoadingContext>(ImageSourceInfo(), LoadNotifier(nullptr, nullptr, nullptr), true);
    ctx->dstSize_ = SizeF(200, 200);
    ctx->imageObj_ = AceType::MakeRefPtr<NG::StaticImageObject>(ImageSourceInfo(SRC_JPG), SizeF(1000, 1000), nullptr);
    ctx->imageFit_ = ImageFit::NONE;
    ctx->sourceSizePtr_ = std::make_unique<SizeF>(50, 50);
    ctx->OnMakeCanvasImage();
    // canvasKey contains targetSize info
    EXPECT_EQ(ctx->dstRect_.GetSize(), SizeF(50, 50));

    ctx->imageFit_ = ImageFit::SCALE_DOWN;
    ctx->OnMakeCanvasImage();
    EXPECT_EQ(ctx->dstRect_.GetSize(), SizeF(50, 50));
}
} // namespace OHOS::Ace::NG
