/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#define protected public
#define private public

#include <cstddef>
#include <optional>
#include <vector>

#include "gtest/gtest.h"
#include "test/mock/base/mock_pixel_map.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_interaction_interface.h"
#include "test/mock/core/image_provider/mock_image_file_cache.cpp"
#include "test/mock/core/image_provider/mock_image_loader.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/geometry/ng/size_t.h"
#include "base/geometry/size.h"
#include "base/image/pixel_map.h"
#include "base/utils/system_properties.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/image_provider/drawing_image_data.h"
#include "core/components_ng/image_provider/animated_image_object.h"
#include "core/components_ng/image_provider/image_data.h"
#include "core/components_ng/image_provider/image_loading_context.h"
#include "core/components_ng/image_provider/image_provider.h"
#include "core/components_ng/image_provider/image_state_manager.h"
#include "core/components_ng/image_provider/pixel_map_image_object.h"
#include "core/components_ng/image_provider/static_image_object.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/image_painter.h"
#include "core/image/image_cache.h"
#include "core/image/image_source_info.h"

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
constexpr uint64_t MAX_WAITING_TIME_FOR_TASKS = 1000; // 1000ms
int32_t callbackFlag = 0;
} // namespace

namespace OHOS::Ace::NG {
class ImageProviderTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    static void WaitForAsyncTasks();

    void SetUp() override;
    void TearDown() override;
};

class MockImageData : public ImageData {
public:
    MOCK_METHOD(size_t, GetSize, (), (const, override));
    MOCK_METHOD(const void*, GetData, (), (const, override));
    MOCK_METHOD(std::string, ToString, (), (const, override));
};

void ImageProviderTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    g_threads = std::vector<std::thread>();
}

void ImageProviderTestNg::SetUp()
{
    g_loader = AceType::MakeRefPtr<MockImageLoader>();
}

void ImageProviderTestNg::TearDown()
{
    g_loader = nullptr;
}

void ImageProviderTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
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
 * @tc.name: CreateFun001
 * @tc.desc: Test CreateFun.
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, CreateFunc001, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx, nullptr);

    auto src1 = ImageSourceInfo(SRC_JPG);
    src1.srcType_ = SrcType::PIXMAP;
    auto ctx1 = AceType::MakeRefPtr<ImageLoadingContext>(src1, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx1, nullptr);
}

/**
 * @tc.name: Destruction001
 * @tc.desc: Test Destruction.
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, Destruction001, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx, nullptr);
    ctx->syncLoad_ = false;

    auto src1 = ImageSourceInfo(SRC_JPG);
    auto ctx1 = AceType::MakeRefPtr<ImageLoadingContext>(src1, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx1, nullptr);

    ctx->stateManager_ = AceType::MakeRefPtr<ImageStateManager>(ctx1);
    ctx->stateManager_->state_ = ImageLoadingState::MAKE_CANVAS_IMAGE;
    EXPECT_NE(ctx, nullptr);
}

/**
 * @tc.name: Destruction002
 * @tc.desc: Test Destruction.
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, Destruction002, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx, nullptr);
    ctx->syncLoad_ = false;

    auto src1 = ImageSourceInfo(SRC_JPG);
    auto ctx1 = AceType::MakeRefPtr<ImageLoadingContext>(src1, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx1, nullptr);

    ctx->stateManager_ = AceType::MakeRefPtr<ImageStateManager>(ctx1);
    ctx->stateManager_->state_ = ImageLoadingState::MAKE_CANVAS_IMAGE;
    ctx->imageObj_ = AceType::MakeRefPtr<NG::StaticImageObject>(ImageSourceInfo(SRC_JPG), SizeF(1000, 1000), nullptr);
    EXPECT_NE(ctx, nullptr);
}

/**
 * @tc.name: HandleCommand001
 * @tc.desc: Test HandleCommand.
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, HandleCommand001, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx, nullptr);
    ctx->syncLoad_ = false;

    auto src1 = ImageSourceInfo(SRC_JPG);
    auto ctx1 = AceType::MakeRefPtr<ImageLoadingContext>(src1, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx1, nullptr);

    ctx->stateManager_ = AceType::MakeRefPtr<ImageStateManager>(ctx1);
    ctx->stateManager_->state_ = ImageLoadingState::MAKE_CANVAS_IMAGE;
    EXPECT_NE(ctx, nullptr);

    ctx->stateManager_->state_ = ImageLoadingState::LOAD_FAIL;
    ctx->stateManager_->HandleCommand(ImageLoadingCommand::LOAD_FAIL);
    EXPECT_NE(ctx, nullptr);

    ctx->stateManager_->state_ = ImageLoadingState(-1);
    ctx->stateManager_->HandleCommand(ImageLoadingCommand::LOAD_FAIL);
    EXPECT_NE(ctx, nullptr);
}

/**
 * @tc.name: NotifiersTest001
 * @tc.desc: Test NotifiersTest.
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, NotifiersTest001, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx, nullptr);

    callbackFlag = 0;
    auto callback1 = [](const ImageSourceInfo& src) {
        callbackFlag = 1;
        return;
    };
    auto callback2 = [](const ImageSourceInfo& src) {
        callbackFlag = 2;
        return;
    };
    auto callback3 = [](const ImageSourceInfo& src, const std::string& errorMsg, const ImageErrorInfo& errorInfo) {
        callbackFlag = 3;
        return;
    };
    ctx->notifiers_ = LoadNotifier(std::move(callback1), std::move(callback2), std::move(callback3));
    std::function<void()> func = []() {};
    ctx->pendingMakeCanvasImageTask_ = func;
    ctx->OnLoadFail();
    EXPECT_EQ(callbackFlag, 3);
    ctx->OnDataReady();
    EXPECT_EQ(callbackFlag, 1);
    ctx->OnLoadSuccess();
    EXPECT_EQ(callbackFlag, 2);
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
    EXPECT_EQ(ctx->stateManager_->GetCurrentState(), ImageLoadingState::DATA_LOADING);

    auto src1 = ImageSourceInfo(SRC_JPG);
    src1.srcType_ = SrcType::PIXMAP;
    auto ctx1 = AceType::MakeRefPtr<ImageLoadingContext>(src1, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx1, nullptr);
}

/**
 * @tc.name: CalculateTargetSize001
 * @tc.desc: Test CalculateTargetSize
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, CalculateTargetSize001, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_EQ(ctx->stateManager_->GetCurrentState(), ImageLoadingState::UNLOADED);

    SizeF srcSize(1, 1);
    SizeF dstSize(2, 2);
    SizeF rawImageSize(3, 3);
    auto size = ctx->CalculateTargetSize(srcSize, dstSize, rawImageSize);
    EXPECT_EQ(size, rawImageSize);

    auto context = PipelineContext::GetCurrentContext();
    context.Reset();

    srcSize.SetSizeT(SizeF(-1, -1));
    size = ctx->CalculateTargetSize(srcSize, dstSize, rawImageSize);
    EXPECT_EQ(size, rawImageSize);

    srcSize.SetSizeT(SizeF(4, 4));
    size = ctx->CalculateTargetSize(srcSize, dstSize, rawImageSize);
    EXPECT_EQ(size, SizeF(1.5, 1.5));

    srcSize.SetSizeT(SizeF(4, 1));
    size = ctx->CalculateTargetSize(srcSize, dstSize, rawImageSize);
    EXPECT_EQ(size, rawImageSize);

    srcSize.SetSizeT(SizeF(1, 4));
    size = ctx->CalculateTargetSize(srcSize, dstSize, rawImageSize);
    EXPECT_EQ(size, rawImageSize);
}

/**
 * @tc.name: SourceSizeTest001
 * @tc.desc: Test SourceSizeTest
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, SourceSizeTest001, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_EQ(ctx->stateManager_->GetCurrentState(), ImageLoadingState::UNLOADED);

    ctx->sourceSizePtr_.reset(new SizeF(1, 1));
    auto size = ctx->GetSourceSize();
    EXPECT_EQ(size.value(), *ctx->sourceSizePtr_.get());

    ctx->sourceSizePtr_.reset(new SizeF(-1, 1));
    size = ctx->GetSourceSize();
    EXPECT_EQ(size, std::nullopt);

    ctx->sourceSizePtr_.reset(new SizeF(1, -1));
    size = ctx->GetSourceSize();
    EXPECT_EQ(size, std::nullopt);

    ctx->sourceSizePtr_.reset(new SizeF(-1, -1));
    size = ctx->GetSourceSize();
    EXPECT_EQ(size, std::nullopt);

    ctx->sourceSizePtr_ = nullptr;
    ctx->SetSourceSize(std::nullopt);
    EXPECT_EQ(ctx->sourceSizePtr_, nullptr);

    ctx->SetSourceSize(SizeF(1, 1));
    EXPECT_EQ(*ctx->sourceSizePtr_.get(), SizeF(1, 1));
}

/**
 * @tc.name: GetImageSize001
 * @tc.desc: Test GetImageSize
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, GetImageSize001, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_EQ(ctx->stateManager_->GetCurrentState(), ImageLoadingState::UNLOADED);
    auto size = ctx->GetImageSize();
    EXPECT_EQ(size, SizeF(-1, -1));

    ctx->imageObj_ =
        AceType::MakeRefPtr<NG::StaticImageObject>(ImageSourceInfo(SRC_JPG), SizeF(LENGTH_128, LENGTH_128), nullptr);
    size = ctx->GetImageSize();
    EXPECT_EQ(size, SizeF(LENGTH_128, LENGTH_128));
}

/**
 * @tc.name: GetImageSize003
 * @tc.desc: Test GetImageSize
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, GetImageSize003, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_EQ(ctx->stateManager_->GetCurrentState(), ImageLoadingState::UNLOADED);
    auto size = ctx->GetImageSize();
    EXPECT_EQ(size, SizeF(-1, -1));

    ctx->imageObj_ =
        AceType::MakeRefPtr<NG::StaticImageObject>(ImageSourceInfo(SRC_JPG), SizeF(LENGTH_63, LENGTH_128), nullptr);
    ctx->GetImageObject()->SetOrientation(ImageRotateOrientation::RIGHT_MIRRORED);
    size = ctx->GetImageSize();
    EXPECT_EQ(size, SizeF(LENGTH_128, LENGTH_63));
}

/**
 * @tc.name: GetImageSize004
 * @tc.desc: Test GetImageSize
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, GetImageSize004, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_EQ(ctx->stateManager_->GetCurrentState(), ImageLoadingState::UNLOADED);
    auto size = ctx->GetImageSize();
    EXPECT_EQ(size, SizeF(-1, -1));

    ctx->imageObj_ =
        AceType::MakeRefPtr<NG::StaticImageObject>(ImageSourceInfo(SRC_JPG), SizeF(LENGTH_63, LENGTH_128), nullptr);
    ctx->GetImageObject()->SetOrientation(ImageRotateOrientation::LEFT_MIRRORED);
    size = ctx->GetImageSize();
    EXPECT_EQ(size, SizeF(LENGTH_128, LENGTH_63));
}

/**
 * @tc.name: MakeCanvasImageIfNeed001
 * @tc.desc: Test MakeCanvasImageIfNeed
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, MakeCanvasImageIfNeed001, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_EQ(ctx->stateManager_->GetCurrentState(), ImageLoadingState::UNLOADED);

    std::vector<ImageFit> imageFitCases = { ImageFit::COVER, ImageFit::FILL };
    std::vector<std::optional<SizeF>> sourceSizeCases = { std::make_optional(SizeF(1, 1)),
        std::make_optional(SizeF(2, 2)) };
    ctx->SetSourceSize(SizeF(1, 1));

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                if (i == 0 && j == 0 && k == 0) {
                    ctx->dstSize_ = SizeF(1, 1);
                    auto ret = ctx->MakeCanvasImageIfNeed(SizeF(1, 1), i, imageFitCases[j], sourceSizeCases[k]);
                    EXPECT_TRUE(ret);
                } else {
                    ctx->dstSize_ = SizeF();
                    auto ret = ctx->MakeCanvasImageIfNeed(SizeF(4, 4), i, imageFitCases[j], sourceSizeCases[k]);
                    EXPECT_TRUE(ret);
                }
            }
        }
    }
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
        if (!ImageProvider::taskMtx_.try_lock_for(std::chrono::milliseconds(MAX_WAITING_TIME_FOR_TASKS))) {
            return;
        }
        // Adopt the already acquired lock
        std::scoped_lock lock(std::adopt_lock, ImageProvider::taskMtx_);
        EXPECT_EQ(ImageProvider::tasks_.size(), (size_t)1);
        EXPECT_EQ(ImageProvider::tasks_[src.GetKey()].ctxs_.size(), (size_t)20);
    }
    // wait for load task to finish
    WaitForAsyncTasks();
    if (!ImageProvider::taskMtx_.try_lock_for(std::chrono::milliseconds(MAX_WAITING_TIME_FOR_TASKS))) {
        return;
    }
    // Adopt the already acquired lock
    std::scoped_lock lock(std::adopt_lock, ImageProvider::taskMtx_);
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
    std::function<void()> func = []() {};
    ctx->pendingMakeCanvasImageTask_ = func;
    auto res = ctx->MakeCanvasImageIfNeed(dstSize, true, ImageFit::COVER);
    EXPECT_TRUE(res);
    EXPECT_EQ(ctx->dstSize_, SizeF(LENGTH_100, LENGTH_100));
    EXPECT_EQ(ctx->stateManager_->state_, ImageLoadingState::LOAD_SUCCESS);

    // call MakeCanvasSize with dstSize in the same level
    res = ctx->MakeCanvasImageIfNeed(SizeF(LENGTH_65, LENGTH_65), true, ImageFit::COVER);
    EXPECT_FALSE(res);
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
    ImageErrorInfo errorInfo;
    EXPECT_FALSE(ImageProvider::BuildImageObject(src, errorInfo, nullptr));

    auto data = AceType::MakeRefPtr<DrawingImageData>(nullptr, 0);
    auto imageObject = ImageProvider::BuildImageObject(src, errorInfo, data);
    EXPECT_TRUE(AceType::DynamicCast<StaticImageObject>(imageObject));

    data = AceType::MakeRefPtr<DrawingImageData>(nullptr, 2);
    imageObject = ImageProvider::BuildImageObject(src, errorInfo, data);
    EXPECT_TRUE(AceType::DynamicCast<AnimatedImageObject>(imageObject));

    // thumbnail src with mismatched data
    src = ImageSourceInfo(SRC_THUMBNAIL);
    EXPECT_FALSE(ImageProvider::BuildImageObject(src, errorInfo, data));
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
        if (!ImageProvider::taskMtx_.try_lock_for(std::chrono::milliseconds(MAX_WAITING_TIME_FOR_TASKS))) {
            return;
        }
        // Adopt the already acquired lock
        std::scoped_lock lock(std::adopt_lock, ImageProvider::taskMtx_);
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
        if (!ImageProvider::taskMtx_.try_lock_for(std::chrono::milliseconds(MAX_WAITING_TIME_FOR_TASKS))) {
            return;
        }
        // Adopt the already acquired lock
        std::scoped_lock lock(std::adopt_lock, ImageProvider::taskMtx_);
        EXPECT_EQ(ImageProvider::tasks_.size(), (size_t)0);
    }
    WaitForAsyncTasks();
    {
        if (!ImageProvider::taskMtx_.try_lock_for(std::chrono::milliseconds(MAX_WAITING_TIME_FOR_TASKS))) {
            return;
        }
        // Adopt the already acquired lock
        std::scoped_lock lock(std::adopt_lock, ImageProvider::taskMtx_);
        EXPECT_EQ(ImageProvider::tasks_.size(), (size_t)0);
    }
}

/**
 * @tc.name: GetImageSize005
 * @tc.desc: Test GetImageSize
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, GetImageSize005, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_EQ(ctx->stateManager_->GetCurrentState(), ImageLoadingState::UNLOADED);
    auto size = ctx->GetImageSize();
    EXPECT_EQ(size, SizeF(-1, -1));

    ctx->imageObj_ =
        AceType::MakeRefPtr<NG::StaticImageObject>(ImageSourceInfo(SRC_JPG), SizeF(LENGTH_63, LENGTH_128), nullptr);
    ctx->GetImageObject()->SetOrientation(ImageRotateOrientation::LEFT);
    size = ctx->GetImageSize();
    EXPECT_EQ(size, SizeF(LENGTH_128, LENGTH_63));
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

/**
 * @tc.name: NotifiersTest002
 * @tc.desc: Test NotifiersTest.
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, NotifiersTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construction parameters
     * @tc.expected: ImageSourceInfo.
     */
    auto src = ImageSourceInfo(SRC_JPG);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx, nullptr);

    callbackFlag = 0;
    auto callback1 = [](const ImageSourceInfo& src) {
        callbackFlag = 1;
        return;
    };
    auto callback2 = [](const ImageSourceInfo& src) {
        callbackFlag = 2;
        return;
    };
    auto callback3 = [](const ImageSourceInfo& src, const std::string& errorMsg, const ImageErrorInfo& errorInfo) {
        callbackFlag = 3;
        return;
    };
    /**
     * @tc.steps: step2. Manage notification tasks for loading data
     * @tc.expected: LoadNotifier.
     */
    ctx->notifiers_ = LoadNotifier(std::move(callback1), std::move(callback2), std::move(callback3));
    std::function<void()> func = []() {};
    ctx->pendingMakeCanvasImageTask_ = func;
    /**
     * @tc.steps: step3. Cleaning or resetting with image loading.
     * @tc.expected: OnUnloaded.
     */
    ctx->OnUnloaded();
    ctx->OnLoadFail();
    EXPECT_EQ(callbackFlag, 3);
    ctx->OnDataReady();
    EXPECT_EQ(callbackFlag, 1);
    ctx->OnLoadSuccess();
    EXPECT_EQ(callbackFlag, 2);
}

/**
 * @tc.name: MakeCanvasImage
 * @tc.desc: Test MakeCanvasImage
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, MakeCanvasImage, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_THUMBNAIL);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    SizeF size(LENGTH_100, LENGTH_100);
    auto pixmap = AceType::MakeRefPtr<MockPixelMap>();
    auto pixmapObj = AceType::MakeRefPtr<PixelMapImageObject>(pixmap, src, size);
    pixmapObj->MakeCanvasImage(ctx, size, true, true);
    EXPECT_NE(ctx->canvasImage_, nullptr);

    pixmap = nullptr;
    pixmapObj = AceType::MakeRefPtr<PixelMapImageObject>(pixmap, src, size);
    pixmapObj->MakeCanvasImage(ctx, size, true, true);
    EXPECT_NE(ctx->canvasImage_, nullptr);
}

/**
 * @tc.name: CreatePixmap
 * @tc.desc: Test CreatePixmap
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, CreatePixmap, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    auto pixmap = AceType::MakeRefPtr<MockPixelMap>();
    auto data = AceType::MakeRefPtr<PixmapData>(pixmap);
    EXPECT_NE(PixelMapImageObject::Create(src, data), nullptr);
}

/**
 * @tc.name: TargetSize002
 * @tc.desc: Test calculating targetSize
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, TargetSize002, TestSize.Level1)
{
    /**
     * @tc.steps1: Construction parameters
     */
    RefPtr<NG::CanvasImage> canvasImage;
    NG::ImagePainter imagePainter(canvasImage);
    NG::RectF srcRect_;
    NG::RectF dstRect_;
    NG::SizeF rawpicsize { 1, 1 };
    NG::SizeF dstsize { 1, 1 };
    auto ctx =
        AceType::MakeRefPtr<ImageLoadingContext>(ImageSourceInfo(), LoadNotifier(nullptr, nullptr, nullptr), true);
    ctx->dstSize_ = SizeF(200, 200);
    ctx->imageObj_ = AceType::MakeRefPtr<NG::StaticImageObject>(ImageSourceInfo(SRC_JPG), SizeF(-1.0, -1.0), nullptr);
    ctx->imageFit_ = ImageFit::NONE;

    /**
     * @tc.steps2: If userDefinedSize is true.SizeF(1, 1).
     * @tc.expected:EXPECT_EQ(size.value(), *ctx->sourceSizePtr_.get()).
     */
    ctx->sourceSizePtr_.reset(new SizeF(1, 1));
    auto size = ctx->GetSourceSize();
    EXPECT_EQ(size.value(), *ctx->sourceSizePtr_.get());

    /**
     * @tc.steps3: callback ApplyImageFit when ImageFit::NONE.
     */
    imagePainter.ApplyImageFit(ImageFit::NONE, rawpicsize, dstsize, srcRect_, dstRect_);
    NG::SizeF srcSize(std::min(dstsize.Width(), rawpicsize.Width()), std::min(dstsize.Height(), rawpicsize.Height()));
    auto testSize = Alignment::GetAlignPosition(dstsize, srcSize, Alignment::CENTER);
    EXPECT_EQ(testSize.GetX(), 0);
    EXPECT_EQ(testSize.GetY(), 0);
    auto imageSize = ctx->GetImageSize();
    EXPECT_EQ(imageSize, SizeF(-1.0, -1.0));
    bool autoResize = true;
    bool isPixelMapResource = (SrcType::DATA_ABILITY_DECODED == ctx->GetSourceInfo().GetSrcType());
    ctx->ResizableCalcDstSize();

    /**
     * @tc.steps4: callback ApplyImageFit when ImageFit::COVER.
     */
    ctx->imageFit_ = ImageFit::COVER;
    imagePainter.ApplyImageFit(ImageFit::COVER, rawpicsize, dstsize, srcRect_, dstRect_);
    auto testSize1 = Alignment::GetAlignPosition(rawpicsize, srcRect_.GetSize(), Alignment::CENTER);
    EXPECT_EQ(testSize1.GetX(), 0);
    EXPECT_EQ(testSize1.GetY(), 0);
    ctx->ResizableCalcDstSize();
    EXPECT_EQ(imageSize, SizeF(-1.0, -1.0));
    EXPECT_TRUE(autoResize);
    EXPECT_FALSE(isPixelMapResource);
}

/**
 * @tc.name: ImageProviderTestNg008
 * @tc.desc: Test ImageProvider
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, ImageProviderTestNg008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construction parameters
     * @tc.expected: ImageSourceInfo.
     */
    auto src = ImageSourceInfo(SRC_JPG);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_EQ(ctx->stateManager_->GetCurrentState(), ImageLoadingState::UNLOADED);

    /**
     * @tc.steps: step2. Information related to building and managing image loading
     */
    ctx->GetDstRect();
    ctx->GetSrcRect();
    ctx->MoveCanvasImage();
    ctx->GetFrameCount();

    EXPECT_EQ(ctx->syncLoad_, true);
    EXPECT_EQ(ctx->imageObj_, nullptr);

    auto src1 = ImageSourceInfo(SRC_JPG);
    src1.srcType_ = SrcType::PIXMAP;
    auto ctx1 = AceType::MakeRefPtr<ImageLoadingContext>(src1, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx1, nullptr);
}

/**
 * @tc.name: TargetSize003
 * @tc.desc: Test calculating targetSize
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, TargetSize003, TestSize.Level1)
{
    /**
     * @tc.steps1: Construction parameters
     */
    RefPtr<NG::CanvasImage> canvasImage;
    NG::ImagePainter imagePainter(canvasImage);
    NG::RectF srcRect_;
    NG::RectF dstRect_;
    NG::SizeF rawpicsize { 1, 1 };
    NG::SizeF dstsize { 1, 1 };
    auto ctx =
        AceType::MakeRefPtr<ImageLoadingContext>(ImageSourceInfo(), LoadNotifier(nullptr, nullptr, nullptr), true);
    ctx->dstSize_ = SizeF(200, 200);
    ctx->imageObj_ = AceType::MakeRefPtr<NG::StaticImageObject>(ImageSourceInfo(SRC_JPG), SizeF(-1.0, -1.0), nullptr);
    ctx->imageFit_ = ImageFit::NONE;

    /**
     * @tc.steps2: If userDefinedSize is false.Width() <= 0.0.Height() <= 0.0.
     * @tc.expected: std::nullopt.
     */
    ctx->sourceSizePtr_.reset(new SizeF(-1, 1));
    auto size = ctx->GetSourceSize();
    EXPECT_EQ(size, std::nullopt);

    /**
     * @tc.steps3: callback ApplyImageFit when ImageFit::NONE.
     */
    imagePainter.ApplyImageFit(ImageFit::NONE, rawpicsize, dstsize, srcRect_, dstRect_);
    NG::SizeF srcSize(std::min(dstsize.Width(), rawpicsize.Width()), std::min(dstsize.Height(), rawpicsize.Height()));
    auto testSize = Alignment::GetAlignPosition(dstsize, srcSize, Alignment::CENTER);
    EXPECT_EQ(testSize.GetX(), 0);
    EXPECT_EQ(testSize.GetY(), 0);
    auto imageSize = ctx->GetImageSize();
    EXPECT_EQ(imageSize, SizeF(-1.0, -1.0));
    bool autoResize = true;
    bool isPixelMapResource = (SrcType::DATA_ABILITY_DECODED == ctx->GetSourceInfo().GetSrcType());
    ctx->ResizableCalcDstSize();

    /**
     * @tc.steps4: callback ApplyImageFit when ImageFit::COVER.
     */
    ctx->imageFit_ = ImageFit::COVER;
    imagePainter.ApplyImageFit(ImageFit::COVER, rawpicsize, dstsize, srcRect_, dstRect_);
    auto testSize1 = Alignment::GetAlignPosition(rawpicsize, srcRect_.GetSize(), Alignment::CENTER);
    EXPECT_EQ(testSize1.GetX(), 0);
    EXPECT_EQ(testSize1.GetY(), 0);
    ctx->ResizableCalcDstSize();
    EXPECT_EQ(imageSize, SizeF(-1.0, -1.0));
    EXPECT_TRUE(autoResize);
    EXPECT_FALSE(isPixelMapResource);
}

/**
 * @tc.name: HandleCommand002
 * @tc.desc: Test HandleCommand.
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, HandleCommand002, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    ctx->syncLoad_ = true;
    auto stateManager = AceType::MakeRefPtr<ImageStateManager>(AceType::WeakClaim(AceType::RawPtr(ctx)));
    stateManager->HandleCommandByUnloadedState(ImageLoadingCommand::LOAD_DATA);
    EXPECT_EQ(stateManager->state_, ImageLoadingState::DATA_LOADING);

    stateManager->HandleCommandByUnloadedState(ImageLoadingCommand::RESET_STATE);
    EXPECT_EQ(stateManager->state_, ImageLoadingState::UNLOADED);

    stateManager->HandleCommandByUnloadedState(ImageLoadingCommand::LOAD_DATA_SUCCESS);
    EXPECT_EQ(stateManager->state_, ImageLoadingState::UNLOADED);
}

/**
 * @tc.name: HandleCommand003
 * @tc.desc: Test HandleCommand.
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, HandleCommand003, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    ctx->syncLoad_ = true;
    auto stateManager = AceType::MakeRefPtr<ImageStateManager>(ctx);
    stateManager->HandleCommandByDataLoadingState(ImageLoadingCommand::LOAD_DATA_SUCCESS);
    EXPECT_EQ(stateManager->state_, ImageLoadingState::DATA_READY);

    stateManager->HandleCommandByDataLoadingState(ImageLoadingCommand::LOAD_FAIL);
    EXPECT_EQ(stateManager->state_, ImageLoadingState::LOAD_FAIL);

    stateManager->HandleCommandByDataLoadingState(ImageLoadingCommand::RESET_STATE);
    EXPECT_EQ(stateManager->state_, ImageLoadingState::UNLOADED);

    stateManager->HandleCommandByDataLoadingState(ImageLoadingCommand::RETRY_LOADING);
    EXPECT_EQ(stateManager->state_, ImageLoadingState::UNLOADED);
}

/**
 * @tc.name: HandleCommand004
 * @tc.desc: Test HandleCommand.
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, HandleCommand004, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    ctx->syncLoad_ = true;
    auto stateManager = AceType::MakeRefPtr<ImageStateManager>(ctx);
    stateManager->HandleCommandByDataReadyState(ImageLoadingCommand::MAKE_CANVAS_IMAGE);
    EXPECT_EQ(stateManager->state_, ImageLoadingState::MAKE_CANVAS_IMAGE);

    stateManager->HandleCommandByDataReadyState(ImageLoadingCommand::RESET_STATE);
    EXPECT_EQ(stateManager->state_, ImageLoadingState::UNLOADED);

    stateManager->HandleCommandByDataReadyState(ImageLoadingCommand::LOAD_DATA_SUCCESS);
    EXPECT_EQ(stateManager->state_, ImageLoadingState::UNLOADED);
}

/**
 * @tc.name: HandleCommand005
 * @tc.desc: Test HandleCommand.
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, HandleCommand005, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    ctx->syncLoad_ = true;
    auto stateManager = AceType::MakeRefPtr<ImageStateManager>(ctx);

    stateManager->HandleCommandByMakeCanvasImageState(ImageLoadingCommand::LOAD_FAIL);
    EXPECT_EQ(stateManager->state_, ImageLoadingState::LOAD_FAIL);

    stateManager->HandleCommandByMakeCanvasImageState(ImageLoadingCommand::RESET_STATE);
    EXPECT_EQ(stateManager->state_, ImageLoadingState::UNLOADED);

    stateManager->HandleCommandByMakeCanvasImageState(ImageLoadingCommand::LOAD_DATA_SUCCESS);
    EXPECT_EQ(stateManager->state_, ImageLoadingState::UNLOADED);
}

/**
 * @tc.name: HandleCommand006
 * @tc.desc: Test HandleCommand.
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, HandleCommand006, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    ctx->syncLoad_ = true;
    auto stateManager = AceType::MakeRefPtr<ImageStateManager>(ctx);
    stateManager->HandleCommandByLoadSuccessState(ImageLoadingCommand::MAKE_CANVAS_IMAGE);
    EXPECT_EQ(stateManager->state_, ImageLoadingState::MAKE_CANVAS_IMAGE);

    stateManager->HandleCommandByLoadSuccessState(ImageLoadingCommand::RESET_STATE);
    EXPECT_EQ(stateManager->state_, ImageLoadingState::UNLOADED);

    stateManager->HandleCommandByLoadSuccessState(ImageLoadingCommand::LOAD_DATA_SUCCESS);
    EXPECT_EQ(stateManager->state_, ImageLoadingState::UNLOADED);
}

/**
 * @tc.name: HandleCommand007
 * @tc.desc: Test HandleCommand.
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, HandleCommand007, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    ctx->syncLoad_ = true;
    auto stateManager = AceType::MakeRefPtr<ImageStateManager>(ctx);

    stateManager->HandleCommandByLoadFailState(ImageLoadingCommand::RESET_STATE);
    EXPECT_EQ(stateManager->state_, ImageLoadingState::UNLOADED);

    stateManager->HandleCommandByLoadFailState(ImageLoadingCommand::LOAD_DATA_SUCCESS);
    EXPECT_EQ(stateManager->state_, ImageLoadingState::UNLOADED);
}

/**
 * @tc.name: GetCurrentLoadingState001
 * @tc.desc: Test GetCurrentLoadingState
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, GetCurrentLoadingState001, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_EQ(ctx->stateManager_->GetCurrentState(), ImageLoadingState::UNLOADED);
    ctx->GetCurrentLoadingState();

    ctx->stateManager_ = AceType::MakeRefPtr<ImageStateManager>(ctx);
    ctx->stateManager_->state_ = ImageLoadingState::MAKE_CANVAS_IMAGE;
    EXPECT_EQ(ctx->stateManager_->GetCurrentState(), ImageLoadingState::MAKE_CANVAS_IMAGE);

    ctx->stateManager_->state_ = ImageLoadingState::LOAD_FAIL;
    ctx->stateManager_->HandleCommand(ImageLoadingCommand::LOAD_FAIL);
    EXPECT_EQ(ctx->stateManager_->GetCurrentState(), ImageLoadingState::LOAD_FAIL);
}

/**
 * @tc.name: GetCurrentLoadingState002
 * @tc.desc: Test GetCurrentLoadingState
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, GetCurrentLoadingState002, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_EQ(ctx->stateManager_->GetCurrentState(), ImageLoadingState::UNLOADED);

    ctx->stateManager_ = AceType::MakeRefPtr<ImageStateManager>(ctx);
    ctx->stateManager_->state_ = ImageLoadingState::DATA_LOADING;
    ctx->GetCurrentLoadingState();
    EXPECT_EQ(ctx->stateManager_->GetCurrentState(), ImageLoadingState::DATA_LOADING);
}

/**
 * @tc.name: GetCurrentLoadingState003
 * @tc.desc: Test GetCurrentLoadingState
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, GetCurrentLoadingState003, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_EQ(ctx->stateManager_->GetCurrentState(), ImageLoadingState::UNLOADED);

    ctx->stateManager_ = AceType::MakeRefPtr<ImageStateManager>(ctx);
    ctx->stateManager_->state_ = ImageLoadingState::DATA_READY;
    ctx->GetCurrentLoadingState();
    EXPECT_EQ(ctx->stateManager_->GetCurrentState(), ImageLoadingState::DATA_READY);
}

/**
 * @tc.name: GetCurrentLoadingState004
 * @tc.desc: Test GetCurrentLoadingState
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, GetCurrentLoadingState004, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_EQ(ctx->stateManager_->GetCurrentState(), ImageLoadingState::UNLOADED);

    ctx->stateManager_ = AceType::MakeRefPtr<ImageStateManager>(ctx);
    ctx->stateManager_->state_ = ImageLoadingState::MAKE_CANVAS_IMAGE;
    ctx->GetCurrentLoadingState();
    EXPECT_EQ(ctx->stateManager_->GetCurrentState(), ImageLoadingState::MAKE_CANVAS_IMAGE);
}

/**
 * @tc.name: GetCurrentLoadingState005
 * @tc.desc: Test GetCurrentLoadingState
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, GetCurrentLoadingState005, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_EQ(ctx->stateManager_->GetCurrentState(), ImageLoadingState::UNLOADED);

    ctx->stateManager_ = AceType::MakeRefPtr<ImageStateManager>(ctx);
    ctx->stateManager_->state_ = ImageLoadingState::LOAD_SUCCESS;
    ctx->GetCurrentLoadingState();
    EXPECT_EQ(ctx->stateManager_->GetCurrentState(), ImageLoadingState::LOAD_SUCCESS);
}

/**
 * @tc.name: GetCurrentLoadingState006
 * @tc.desc: Test GetCurrentLoadingState
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, GetCurrentLoadingState006, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_EQ(ctx->stateManager_->GetCurrentState(), ImageLoadingState::UNLOADED);

    ctx->stateManager_ = AceType::MakeRefPtr<ImageStateManager>(ctx);
    ctx->stateManager_->state_ = ImageLoadingState::LOAD_FAIL;
    ctx->GetCurrentLoadingState();
    EXPECT_EQ(ctx->stateManager_->GetCurrentState(), ImageLoadingState::LOAD_FAIL);
}

/**
 * @tc.name: GetFrameCount001
 * @tc.desc: Test GetFrameCount
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, GetFrameCount001, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);

    ctx->GetFrameCount();
    EXPECT_EQ(ctx->imageObj_, nullptr);

    ctx->imageObj_ = AceType::MakeRefPtr<NG::StaticImageObject>(ImageSourceInfo(SRC_JPG), SizeF(1000, 1000), nullptr);
    ctx->GetFrameCount();
    EXPECT_NE(ctx->imageObj_, nullptr);
}

/**
 * @tc.name: CallbackAfterMeasureIfNeed001
 * @tc.desc: Test CallbackAfterMeasureIfNeed
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, CallbackAfterMeasureIfNeed001, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);

    ctx->needErrorCallBack_ = false;
    ctx->CallbackAfterMeasureIfNeed();

    ctx->needErrorCallBack_ = true;
    ctx->CallbackAfterMeasureIfNeed();
    EXPECT_EQ(ctx->needErrorCallBack_, false);
}

/**
 * @tc.name: CallbackAfterMeasureIfNeed002
 * @tc.desc: Test CallbackAfterMeasureIfNeed
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, CallbackAfterMeasureIfNeed002, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);

    ctx->needErrorCallBack_ = false;
    ctx->needDataReadyCallBack_ = false;
    ctx->CallbackAfterMeasureIfNeed();

    ctx->needDataReadyCallBack_ = true;
    ctx->CallbackAfterMeasureIfNeed();
    EXPECT_EQ(ctx->needDataReadyCallBack_, false);
}

/**
 * @tc.name: FailCallback001
 * @tc.desc: Test FailCallback
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, FailCallback001, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    src.srcType_ = SrcType::NETWORK;
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);

    ctx->measureFinish_ = true;
    ctx->FailCallback("test error");
    EXPECT_EQ(ctx->needErrorCallBack_, false);
}

/**
 * @tc.name: FailCallback002
 * @tc.desc: Test FailCallback
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, FailCallback002, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    src.srcType_ = SrcType::MEMORY;
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);

    ctx->measureFinish_ = false;
    ctx->FailCallback("test error");
    EXPECT_EQ(ctx->Downloadable(), false);
}

/**
 * @tc.name: DataReadyCallback001
 * @tc.desc: Test DataReadyCallback
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, DataReadyCallback001, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    src.srcType_ = SrcType::NETWORK;
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);

    auto pixmap = AceType::MakeRefPtr<MockPixelMap>();
    SizeF size(LENGTH_100, LENGTH_100);
    ctx->measureFinish_ = true;

    ctx->DataReadyCallback(AceType::MakeRefPtr<PixelMapImageObject>(pixmap, src, size));
    EXPECT_EQ(ctx->GetImageSize(), size);
}

/**
 * @tc.name: ResizableCalcDstSize001
 * @tc.desc: Test ResizableCalcDstSize
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, ResizableCalcDstSize001, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);

    ctx->autoResize_ = true;
    bool isPixelMapResource = (SrcType::DATA_ABILITY_DECODED == ctx->GetSourceInfo().GetSrcType());
    ctx->ResizableCalcDstSize();
    EXPECT_FALSE(isPixelMapResource);
}

/**
 * @tc.name: ResizableCalcDstSize002
 * @tc.desc: Test ResizableCalcDstSize
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, ResizableCalcDstSize002, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    src.srcType_ = SrcType::DATA_ABILITY_DECODED;
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);

    ctx->autoResize_ = false;
    bool isPixelMapResource = (SrcType::DATA_ABILITY_DECODED == ctx->GetSourceInfo().GetSrcType());
    ctx->ResizableCalcDstSize();
    EXPECT_TRUE(isPixelMapResource);
}

/**
 * @tc.name: DownloadOnProgress001
 * @tc.desc: Test DownloadOnProgress
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, DownloadOnProgress001, TestSize.Level1)
{
    uint32_t dlNow = 0;
    uint32_t dlTotal = 0;
    auto src = ImageSourceInfo(SRC_JPG);
    src.srcType_ = SrcType::DATA_ABILITY_DECODED;
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);

    ctx->onProgressCallback_ = [](const uint32_t& dlNow, const uint32_t& dlTotal) {};
    ctx->DownloadOnProgress(dlNow, dlTotal);

    ctx->onProgressCallback_ = nullptr;
    bool isPixelMapResource = (SrcType::DATA_ABILITY == ctx->GetSourceInfo().GetSrcType());
    ctx->DownloadOnProgress(dlNow, dlTotal);
    EXPECT_FALSE(isPixelMapResource);
}

/**
 * @tc.name: MakeCanvasImageIfNeed002
 * @tc.desc: Test MakeCanvasImageIfNeed
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, MakeCanvasImageIfNeed002, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    ctx->stateManager_->state_ = ImageLoadingState::MAKE_CANVAS_IMAGE;
    SizeF dstSize(LENGTH_100, LENGTH_100);
    std::function<void()> func = []() {};
    ctx->pendingMakeCanvasImageTask_ = func;
    auto res = ctx->MakeCanvasImageIfNeed(dstSize, true, ImageFit::COVER);
    EXPECT_TRUE(res);
}

/**
 * @tc.name: MakeCanvasImage001
 * @tc.desc: Test MakeCanvasImage
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, MakeCanvasImage001, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_THUMBNAIL);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx, nullptr);

    SizeF size(LENGTH_100, LENGTH_100);
    auto pixmap = AceType::MakeRefPtr<MockPixelMap>();
    auto pixmapObj = AceType::MakeRefPtr<PixelMapImageObject>(pixmap, src, size);
    EXPECT_NE(pixmapObj, nullptr);

    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN));

    pixmapObj->MakeCanvasImage(ctx, size, true, true);
    EXPECT_NE(ctx->canvasImage_, nullptr);

    pixmapObj = AceType::MakeRefPtr<PixelMapImageObject>(pixmap, src, size);
    EXPECT_NE(pixmapObj, nullptr);

    pixmapObj->MakeCanvasImage(ctx, size, true, false);
    EXPECT_NE(ctx->canvasImage_, nullptr);

    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);

    pixmapObj->MakeCanvasImage(ctx, size, true, false);
    EXPECT_NE(ctx->canvasImage_, nullptr);
}

/**
 * @tc.name: CreatePixmap001
 * @tc.desc: Test PixelMapImageObject Create
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, CreatePixmap001, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_THUMBNAIL);

    SizeF size(LENGTH_100, LENGTH_100);
    auto pixmap = AceType::MakeRefPtr<MockPixelMap>();
    auto pixmapObj = AceType::MakeRefPtr<PixelMapImageObject>(pixmap, src, size);
    EXPECT_NE(pixmapObj, nullptr);

    pixmap = nullptr;
    auto data = AceType::MakeRefPtr<PixmapData>(pixmap);
    EXPECT_NE(data, nullptr);

    auto pixelMapImageObject = pixmapObj->Create(src, data);
    EXPECT_EQ(pixelMapImageObject, nullptr);
}

/**
 * @tc.name: ImageLoadingContext001
 * @tc.desc: Test ImageLoadingContext.
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, ImageLoadingContext001, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    src.srcType_ = SrcType::NETWORK;

    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN));

    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx, nullptr);

    auto src1 = ImageSourceInfo(SRC_JPG);
    src1.srcType_ = SrcType::PIXMAP;

    auto ctx1 = AceType::MakeRefPtr<ImageLoadingContext>(src1, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx1, nullptr);

    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);

    EXPECT_TRUE(ctx1->syncLoad_);
}

/**
 * @tc.name: OnMakeCanvasImage001
 * @tc.desc: Test OnMakeCanvasImage
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, OnMakeCanvasImage001, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    src.srcType_ = SrcType::PIXMAP;

    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx, nullptr);

    ctx->imageObj_ = AceType::MakeRefPtr<NG::StaticImageObject>(ImageSourceInfo(SRC_JPG), SizeF(1000, 1000), nullptr);
    EXPECT_NE(ctx->imageObj_, nullptr);

    ctx->imageFit_ = ImageFit::NONE;
    ctx->sourceSizePtr_ = nullptr;
    ctx->dstSize_ = SizeF(200, 200);
    ctx->autoResize_ = false;

    ctx->OnMakeCanvasImage();
    EXPECT_FALSE(ctx->GetSourceSize());
    EXPECT_EQ(ctx->dstRect_.Height(), 200);
}

/**
 * @tc.name: OnMakeCanvasImage002
 * @tc.desc: Test OnMakeCanvasImage
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, OnMakeCanvasImage002, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    src.srcType_ = SrcType::DATA_ABILITY_DECODED;

    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx, nullptr);

    ctx->imageObj_ = AceType::MakeRefPtr<NG::StaticImageObject>(ImageSourceInfo(SRC_JPG), SizeF(1000, 1000), nullptr);
    EXPECT_NE(ctx->imageObj_, nullptr);

    ctx->sourceSizePtr_ = nullptr;
    ctx->dstSize_ = SizeF(200, 200);
    ctx->autoResize_ = false;

    ctx->OnMakeCanvasImage();
    EXPECT_FALSE(ctx->GetSourceSize());
    EXPECT_EQ(ctx->dstRect_.Height(), 200);

    ctx->autoResize_ = true;
    ctx->OnMakeCanvasImage();
    EXPECT_FALSE(ctx->GetSourceSize());
    EXPECT_EQ(ctx->dstRect_.Height(), 200);
}

/**
 * @tc.name: ResizableCalcDstSize003
 * @tc.desc: Test ResizableCalcDstSize
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, ResizableCalcDstSize003, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    src.srcType_ = SrcType::DATA_ABILITY_DECODED;

    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx, nullptr);

    ctx->sourceSizePtr_ = nullptr;
    ctx->dstSize_ = SizeF(200, 200);

    ctx->ResizableCalcDstSize();
    EXPECT_EQ(ctx->GetSourceInfo().GetSrcType(), SrcType::DATA_ABILITY_DECODED);
}

/**
 * @tc.name: ResizableCalcDstSize004
 * @tc.desc: Test ResizableCalcDstSize
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, ResizableCalcDstSize004, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_JPG);
    src.srcType_ = SrcType::PIXMAP;

    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx, nullptr);

    ctx->sourceSizePtr_ = nullptr;
    ctx->dstSize_ = SizeF(200, 200);
    ctx->autoResize_ = false;

    ctx->ResizableCalcDstSize();
    EXPECT_EQ(ctx->GetSourceInfo().GetSrcType(), SrcType::PIXMAP);
}

/**
 * @tc.name: MakeCanvasImageIfNeed003
 * @tc.desc: Test MakeCanvasImageIfNeed
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, MakeCanvasImageIfNeed003, TestSize.Level1)
{
    auto ctx =
        AceType::MakeRefPtr<ImageLoadingContext>(ImageSourceInfo(), LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx, nullptr);

    ctx->imageObj_ =
        AceType::MakeRefPtr<NG::StaticImageObject>(ImageSourceInfo(SRC_JPG), SizeF(LENGTH_128, LENGTH_128), nullptr);
    EXPECT_NE(ctx->imageObj_, nullptr);

    SizeF dstSize(LENGTH_100, LENGTH_100);
    std::function<void()> func = []() {};
    ctx->pendingMakeCanvasImageTask_ = func;
    ctx->stateManager_->state_ = ImageLoadingState::DATA_READY;

    auto res = ctx->MakeCanvasImageIfNeed(dstSize, true, ImageFit::COVER);
    EXPECT_TRUE(res);
    EXPECT_EQ(ctx->dstSize_, SizeF(LENGTH_100, LENGTH_100));
    EXPECT_EQ(ctx->stateManager_->state_, ImageLoadingState::LOAD_SUCCESS);

    res = ctx->MakeCanvasImageIfNeed(SizeF(LENGTH_65, LENGTH_65), true, ImageFit::COVER, std::nullopt, true);
    EXPECT_FALSE(res);
    EXPECT_EQ(ctx->sizeLevel_, LENGTH_128);
}

/**
 * @tc.name: MakeCanvasImageIfNeed004
 * @tc.desc: Test MakeCanvasImageIfNeed when firstLoadImage_ is false
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, MakeCanvasImageIfNeed004, TestSize.Level1)
{
    auto ctx =
        AceType::MakeRefPtr<ImageLoadingContext>(ImageSourceInfo(), LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx, nullptr);

    ctx->imageObj_ =
        AceType::MakeRefPtr<NG::StaticImageObject>(ImageSourceInfo(SRC_JPG), SizeF(LENGTH_128, LENGTH_128), nullptr);
    EXPECT_NE(ctx->imageObj_, nullptr);

    SizeF dstSize(LENGTH_100, LENGTH_100);
    std::function<void()> func = []() {};
    ctx->pendingMakeCanvasImageTask_ = func;
    ctx->firstLoadImage_ = false;
    ctx->stateManager_->state_ = ImageLoadingState::DATA_READY;

    auto res = ctx->MakeCanvasImageIfNeed(dstSize, true, ImageFit::COVER);
    EXPECT_TRUE(res);
    EXPECT_EQ(ctx->dstSize_, SizeF(LENGTH_100, LENGTH_100));
    EXPECT_EQ(ctx->stateManager_->state_, ImageLoadingState::LOAD_SUCCESS);
}

/**
 * @tc.name: GetImageSize002
 * @tc.desc: Test GetImageSize
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, GetImageSize002, TestSize.Level1)
{
    auto ctx =
        AceType::MakeRefPtr<ImageLoadingContext>(ImageSourceInfo(), LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx, nullptr);

    ctx->imageObj_ =
        AceType::MakeRefPtr<NG::StaticImageObject>(ImageSourceInfo(SRC_JPG), SizeF(LENGTH_128, LENGTH_128), nullptr);
    EXPECT_NE(ctx->imageObj_, nullptr);

    ctx->imageObj_->SetOrientation(ImageRotateOrientation::LEFT);
    auto imageSize = ctx->GetImageSize();
    EXPECT_EQ(imageSize, SizeF(LENGTH_128, LENGTH_128));

    ctx->imageObj_->SetOrientation(ImageRotateOrientation::RIGHT);
    imageSize = ctx->GetImageSize();
    EXPECT_EQ(imageSize, SizeF(LENGTH_128, LENGTH_128));
}

/**
 * @tc.name: PrepareImageData001
 * @tc.desc: Test PrepareImageData
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, PrepareImageData001, TestSize.Level1)
{
    auto imageProvider = AceType::MakeRefPtr<ImageProvider>();
    EXPECT_NE(imageProvider, nullptr);

    auto src = ImageSourceInfo(SRC_JPG);
    ImageErrorInfo errorInfo;
    EXPECT_FALSE(ImageProvider::BuildImageObject(src, errorInfo, nullptr));
    auto data = AceType::MakeRefPtr<DrawingImageData>(nullptr, 0);
    auto imageObject = ImageProvider::BuildImageObject(src, errorInfo, data);

    auto lock = imageObject->GetPrepareImageDataLock();
    lock.__owns_ = false;

    EXPECT_FALSE(imageProvider->PrepareImageData(imageObject));
}

/**
 * @tc.name: PrepareImageData002
 * @tc.desc: Test PrepareImageData
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, PrepareImageData002, TestSize.Level1)
{
    auto imageProvider = AceType::MakeRefPtr<ImageProvider>();
    EXPECT_NE(imageProvider, nullptr);

    auto src = ImageSourceInfo(SRC_JPG);
    ImageErrorInfo errorInfo;
    EXPECT_FALSE(ImageProvider::BuildImageObject(src, errorInfo, nullptr));
    auto data = AceType::MakeRefPtr<DrawingImageData>(nullptr, 0);
    auto imageObject = ImageProvider::BuildImageObject(src, errorInfo, data);
    imageObject->data_ = nullptr;

    MockContainer::SetUp();
    auto container = MockContainer::Current();

    EXPECT_FALSE(imageProvider->PrepareImageData(imageObject));
}

/**
 * @tc.name: PrepareImageData003
 * @tc.desc: Test PrepareImageData
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, PrepareImageData003, TestSize.Level1)
{
    auto imageProvider = AceType::MakeRefPtr<ImageProvider>();
    EXPECT_NE(imageProvider, nullptr);

    auto src = ImageSourceInfo(SRC_JPG);
    ImageErrorInfo errorInfo;
    EXPECT_FALSE(ImageProvider::BuildImageObject(src, errorInfo, nullptr));
    auto data = AceType::MakeRefPtr<DrawingImageData>(nullptr, 0);
    auto imageObject = ImageProvider::BuildImageObject(src, errorInfo, data);
    imageObject->data_ = nullptr;

    MockContainer::SetUp();
    auto container = MockContainer::Current();
    g_loader = nullptr;
    container->pipelineContext_ = PipelineBase::GetCurrentContext();

    EXPECT_FALSE(imageProvider->PrepareImageData(imageObject));
}

/**
 * @tc.name: CreateImageObjHelper001
 * @tc.desc: Test CreateImageObjHelper
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, CreateImageObjHelper001, TestSize.Level1)
{
    auto imageProvider = AceType::MakeRefPtr<ImageProvider>();
    EXPECT_NE(imageProvider, nullptr);

    auto src = ImageSourceInfo(SRC_THUMBNAIL);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr));
    ctx->LoadImageData();
    EXPECT_EQ(ctx->stateManager_->state_, ImageLoadingState::DATA_LOADING);
    g_loader = nullptr;

    WaitForAsyncTasks();

    EXPECT_EQ(ctx->errorMsg_, "Failed to create image loader.");
}

/**
 * @tc.name: CreateImageObjHelper002
 * @tc.desc: Test CreateImageObjHelper
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, CreateImageObjHelper002, TestSize.Level1)
{
    auto imageProvider = AceType::MakeRefPtr<ImageProvider>();
    EXPECT_NE(imageProvider, nullptr);

    auto src = ImageSourceInfo(SRC_THUMBNAIL);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr));
    ctx->LoadImageData();
    EXPECT_EQ(ctx->stateManager_->state_, ImageLoadingState::DATA_LOADING);

    MockContainer::SetUp();
    auto container = MockContainer::Current();
    auto data = AceType::MakeRefPtr<MockImageData>();
    EXPECT_CALL(*g_loader, LoadDecodedImageData(testing::_, testing::_, testing::_)).WillOnce(testing::Return(data));
    auto pixmap = AceType::MakeRefPtr<MockPixelMap>();
    src.pixmap_ = pixmap;

    WaitForAsyncTasks();

    EXPECT_EQ(ctx->errorMsg_, "Failed to build image object");
}

/**
 * @tc.name: CreateImageObjHelper003
 * @tc.desc: Test CreateImageObjHelper
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, CreateImageObjHelper003, TestSize.Level1)
{
    auto imageProvider = AceType::MakeRefPtr<ImageProvider>();
    EXPECT_NE(imageProvider, nullptr);

    auto src = ImageSourceInfo(SRC_THUMBNAIL);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr));
    ctx->LoadImageData();
    EXPECT_EQ(ctx->stateManager_->state_, ImageLoadingState::DATA_LOADING);

    MockContainer::SetUp();
    auto container = MockContainer::Current();

    auto pixmap = AceType::MakeRefPtr<MockPixelMap>();
    src.pixmap_ = pixmap;
    auto data = AceType::MakeRefPtr<PixmapData>(pixmap);
    EXPECT_CALL(*g_loader, LoadDecodedImageData(testing::_, testing::_, testing::_)).WillOnce(testing::Return(data));

    ImageErrorInfo errorInfo;
    auto imageObject = ImageProvider::BuildImageObject(src, errorInfo, data);

    EXPECT_CALL(*pixmap, GetWidth()).Times(1);
    EXPECT_CALL(*pixmap, GetHeight()).Times(1);

    WaitForAsyncTasks();

    EXPECT_EQ(ctx->errorMsg_, "");
}

/**
 * @tc.name: ImageProviderFailCallback001
 * @tc.desc: Test ImageProvider FailCallback
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, ImageProviderFailCallback001, TestSize.Level1)
{
    auto src = ImageSourceInfo();
    // Create multiple ImageLoadingContext instances associated with the same ImageSourceInfo.
    // The LoadNotifier parameters are set to nullptr, meaning no callback is registered.
    auto ctx1 = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx1, nullptr);

    auto ctx2 = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx2, nullptr);

    auto ctx3 = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx3, nullptr);

    // Register weak references of these ImageLoadingContext instances in ImageProvider's task management.
    ImageProvider::RegisterTask(src.GetKey(), WeakPtr(ctx1));
    ImageProvider::RegisterTask(src.GetKey(), WeakPtr(ctx2));
    ImageProvider::RegisterTask(src.GetKey(), WeakPtr(ctx3));

    ctx2 = nullptr;

    // Define the error message.
    auto errorMsg = "error";
    // Define the error information.
    ImageErrorInfo errorInfo;

    // Invoke FailCallback to trigger the failure callback.
    // Expected behavior: ctx1 and ctx3 should update their error messages.
    ImageProvider::FailCallback(src.GetKey(), errorMsg, errorInfo, true);

    // Verify that ctx1 and ctx3 have correctly received the error message.
    EXPECT_EQ(ctx1->errorMsg_, errorMsg);
    EXPECT_EQ(ctx2, nullptr);
    EXPECT_EQ(ctx3->errorMsg_, errorMsg);
}

/**
 * @tc.name: ImageProviderFailCallback002
 * @tc.desc: Test ImageProvider FailCallback
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, ImageProviderFailCallback002, TestSize.Level1)
{
    auto src = ImageSourceInfo();
    // Create multiple ImageLoadingContext instances associated with the same ImageSourceInfo.
    // The LoadNotifier parameters are set to nullptr, meaning no callback is registered.
    auto ctx1 = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx1, nullptr);

    auto ctx2 = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx2, nullptr);

    auto ctx3 = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx3, nullptr);

    auto ctx4 = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx3, nullptr);

    // Register weak references of these ImageLoadingContext instances in ImageProvider's task management.
    ImageProvider::RegisterTask(src.GetKey(), WeakPtr(ctx1));
    ImageProvider::RegisterTask(src.GetKey(), WeakPtr(ctx2));
    ImageProvider::RegisterTask(src.GetKey(), WeakPtr(ctx3));
    ImageProvider::RegisterTask(src.GetKey(), WeakPtr(ctx4));

    ctx2 = nullptr;
    ctx3 = nullptr;

    // Define the error message.
    auto errorMsg = "error";
    // Define the error information.
    ImageErrorInfo errorInfo;

    // Invoke FailCallback to trigger the failure callback.
    // Expected behavior: ctx1 and ctx3 should update their error messages.
    ImageProvider::FailCallback(src.GetKey(), errorMsg, errorInfo, true);

    // Verify that ctx1 and ctx4 have correctly received the error message.
    EXPECT_EQ(ctx1->errorMsg_, errorMsg);
    EXPECT_EQ(ctx2, nullptr);
    EXPECT_EQ(ctx3, nullptr);
    EXPECT_EQ(ctx4->errorMsg_, errorMsg);
}

/**
 * @tc.name: ImageProviderFailCallback003
 * @tc.desc: Test ImageProvider FailCallback
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, ImageProviderFailCallback003, TestSize.Level1)
{
    auto src = ImageSourceInfo();
    // Create multiple ImageLoadingContext instances associated with the same ImageSourceInfo.
    // The LoadNotifier parameters are set to nullptr, meaning no callback is registered.
    auto ctx1 = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx1, nullptr);

    auto ctx2 = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx2, nullptr);

    auto ctx3 = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx3, nullptr);

    auto ctx4 = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx3, nullptr);

    // Register weak references of these ImageLoadingContext instances in ImageProvider's task management.
    ImageProvider::RegisterTask(src.GetKey(), WeakPtr(ctx1));
    ImageProvider::RegisterTask(src.GetKey(), WeakPtr(ctx2));
    ImageProvider::RegisterTask(src.GetKey(), WeakPtr(ctx3));
    ImageProvider::RegisterTask(src.GetKey(), WeakPtr(ctx4));

    // Define the error message.
    auto errorMsg = "error";
    ImageErrorInfo errorInfo;

    // Invoke FailCallback to trigger the failure callback.
    // Expected behavior: all ctx should update their error messages.
    ImageProvider::FailCallback(src.GetKey(), errorMsg, errorInfo, true);

    // Verify that all ctx have correctly received the error message.
    EXPECT_EQ(ctx1->errorMsg_, errorMsg);
    EXPECT_EQ(ctx2->errorMsg_, errorMsg);
    EXPECT_EQ(ctx3->errorMsg_, errorMsg);
    EXPECT_EQ(ctx4->errorMsg_, errorMsg);
}

/**
 * @tc.name: ImageProviderCancelTask001
 * @tc.desc: Test ImageProvider::CancelTask with multiple contexts; only one is removed
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, ImageProviderCancelTask001, TestSize.Level1)
{
    ImageProvider::tasks_.clear();
    auto src = ImageSourceInfo();

    // Create multiple ImageLoadingContext instances and register them under the same key
    auto ctx1 = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx1, nullptr);
    auto ctx2 = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx2, nullptr);

    ImageProvider::RegisterTask(src.GetKey(), WeakPtr(ctx1));
    ImageProvider::RegisterTask(src.GetKey(), WeakPtr(ctx2));

    // CancelTask for ctx1 should return false since ctx2 is still waiting
    bool result1 = ImageProvider::CancelTask(src.GetKey(), WeakPtr(ctx1));
    EXPECT_FALSE(result1);

    // CancelTask for ctx2 should return true as it's the last context
    bool result2 = ImageProvider::CancelTask(src.GetKey(), WeakPtr(ctx2));
    EXPECT_TRUE(result2);
}

/**
 * @tc.name: StaticImageDecoder001
 * @tc.desc: Test MakeCanvasImage
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, StaticImageDecoder001, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_THUMBNAIL);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx, nullptr);

    SizeF size(LENGTH_100, LENGTH_100);
    auto pixmap = AceType::MakeRefPtr<MockPixelMap>();
    auto pixmapObj = AceType::MakeRefPtr<PixelMapImageObject>(pixmap, src, size);
    EXPECT_NE(pixmapObj, nullptr);

    pixmapObj->MakeCanvasImage(ctx, size, true, true);
    EXPECT_NE(ctx->canvasImage_, nullptr);

    pixmapObj = AceType::MakeRefPtr<PixelMapImageObject>(pixmap, src, size);
    EXPECT_NE(pixmapObj, nullptr);

    pixmapObj->MakeCanvasImage(ctx, size, true, false);
    EXPECT_NE(ctx->canvasImage_, nullptr);

    pixmapObj->MakeCanvasImage(ctx, size, true, false);
    EXPECT_NE(ctx->canvasImage_, nullptr);
}

/**
 * @tc.name: ImageProviderCancelTask002
 * @tc.desc: Test ImageProvider::CancelTask when context is not registered
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, ImageProviderCancelTask002, TestSize.Level1)
{
    ImageProvider::tasks_.clear();
    auto src = ImageSourceInfo();

    // Register one context
    auto ctx1 = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx1, nullptr);
    ImageProvider::RegisterTask(src.GetKey(), WeakPtr(ctx1));

    // Create a context that is not registered
    auto ctxNotRegistered =
        AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctxNotRegistered, nullptr);

    // Attempting to cancel an unregistered context should return false
    bool result = ImageProvider::CancelTask(src.GetKey(), WeakPtr(ctxNotRegistered));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ImageProviderCancelTask003
 * @tc.desc: Test ImageProvider::CancelTask when key does not exist
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, ImageProviderCancelTask003, TestSize.Level1)
{
    ImageProvider::tasks_.clear();
    auto src = ImageSourceInfo();

    // Create a context but do not register it
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx, nullptr);

    // Attempting to cancel with a non-existent key should return false
    bool result = ImageProvider::CancelTask("non_exist_key", WeakPtr(ctx));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ImageProviderCancelTask004
 * @tc.desc: Test ImageProvider::CancelTask when only one context is registered
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, ImageProviderCancelTask004, TestSize.Level1)
{
    ImageProvider::tasks_.clear();
    auto src = ImageSourceInfo();

    // Register a single context
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx, nullptr);
    ImageProvider::RegisterTask(src.GetKey(), WeakPtr(ctx));

    // CancelTask should return true and remove the entire task
    bool result = ImageProvider::CancelTask(src.GetKey(), WeakPtr(ctx));
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ImageProviderTestNg_EndTaskKeyCorrectness
 * @tc.desc: Verify that ImageProvider uses GetTaskKey() for registering and ending tasks.
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, ImageProviderTestNg_EndTaskKeyCorrectness, TestSize.Level1)
{
    // Expect LoadImageData to be called only once, since repeated tasks should be merged.
    EXPECT_CALL(*g_loader, LoadImageData).Times(1);

    auto src = ImageSourceInfo(SRC_JPG);

    // Step 1: Create multiple ImageLoadingContext instances with the same image source.
    std::vector<RefPtr<ImageLoadingContext>> contexts(10);
    for (auto& ctx : contexts) {
        ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), false);
        ctx->LoadImageData(); // Triggers CreateImageObject and registers task.
    }

    // Step 2: Verify that task was registered using the correct key and merged properly.
    {
        if (!ImageProvider::taskMtx_.try_lock_for(std::chrono::milliseconds(MAX_WAITING_TIME_FOR_TASKS))) {
            EXPECT_TRUE(false) << "Failed to acquire mutex.";
            return;
        }
        std::scoped_lock lock(std::adopt_lock, ImageProvider::taskMtx_);

        // Use GetTaskKey() instead of GetKey() to check the task map.
        auto taskKey = src.GetTaskKey();
        auto it = ImageProvider::tasks_.find(taskKey);
        EXPECT_NE(it, ImageProvider::tasks_.end());     // Task should exist.
        EXPECT_EQ(it->second.ctxs_.size(), (size_t)10); // All contexts should be merged under the same task.
        auto errorKey = "non_exist_key";
        auto tmpIt = ImageProvider::tasks_.find(errorKey);
        EXPECT_EQ(tmpIt, ImageProvider::tasks_.end()); // errorTask shouldn't exist.
    }

    // Step 3: Wait for the background loading task to finish, which will trigger EndTask().
    WaitForAsyncTasks();

    // Step 4: Check that the task has been properly removed from the map after completion.
    {
        if (!ImageProvider::taskMtx_.try_lock_for(std::chrono::milliseconds(MAX_WAITING_TIME_FOR_TASKS))) {
            EXPECT_TRUE(false) << "Failed to acquire mutex after WaitForAsyncTasks.";
            return;
        }
        std::scoped_lock lock(std::adopt_lock, ImageProvider::taskMtx_);
        EXPECT_EQ(ImageProvider::tasks_.size(), (size_t)0); // The task map should be empty after cleanup.
    }
}

/**
 * @tc.name: StaticImageMakeCanvasImage001
 * @tc.desc: Test MakeCanvasImage
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, StaticImageMakeCanvasImage001, TestSize.Level1)
{
    auto src = ImageSourceInfo(SRC_THUMBNAIL);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    EXPECT_NE(ctx, nullptr);

    SizeF size(LENGTH_100, LENGTH_100);
    auto pixmap = AceType::MakeRefPtr<MockPixelMap>();
    auto pixmapObj = AceType::MakeRefPtr<PixelMapImageObject>(pixmap, src, size);
    EXPECT_NE(pixmapObj, nullptr);

    pixmapObj->MakeCanvasImage(ctx, size, true, true);
    EXPECT_NE(ctx->canvasImage_, nullptr);

    pixmapObj = AceType::MakeRefPtr<PixelMapImageObject>(pixmap, src, size);
    EXPECT_NE(pixmapObj, nullptr);

    pixmapObj->MakeCanvasImage(ctx, size, true, false);
    EXPECT_NE(ctx->canvasImage_, nullptr);

    pixmapObj->MakeCanvasImage(ctx, size, true, false);
    EXPECT_NE(ctx->canvasImage_, nullptr);
}
} // namespace OHOS::Ace::NG
