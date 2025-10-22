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
constexpr int32_t LENGTH_128 = 128;
constexpr uint64_t MAX_WAITING_TIME_FOR_TASKS = 1000; // 1000ms
} // namespace

namespace OHOS::Ace::NG {
class ImageProviderTestNgTwo : public testing::Test {
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

void ImageProviderTestNgTwo::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    g_threads = std::vector<std::thread>();
}

void ImageProviderTestNgTwo::SetUp()
{
    g_loader = AceType::MakeRefPtr<MockImageLoader>();
}

void ImageProviderTestNgTwo::TearDown()
{
    g_loader = nullptr;
}

void ImageProviderTestNgTwo::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    g_loader = nullptr;
}

// wait for load task to finish
void ImageProviderTestNgTwo::WaitForAsyncTasks()
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
HWTEST_F(ImageProviderTestNgTwo, CreateFunc001, TestSize.Level1)
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
 * @tc.name: OnMakeCanvasImage001
 * @tc.desc: Test OnMakeCanvasImage
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNgTwo, OnMakeCanvasImage001, TestSize.Level1)
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
HWTEST_F(ImageProviderTestNgTwo, OnMakeCanvasImage002, TestSize.Level1)
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
HWTEST_F(ImageProviderTestNgTwo, ResizableCalcDstSize003, TestSize.Level1)
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
HWTEST_F(ImageProviderTestNgTwo, ResizableCalcDstSize004, TestSize.Level1)
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
HWTEST_F(ImageProviderTestNgTwo, MakeCanvasImageIfNeed003, TestSize.Level1)
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
HWTEST_F(ImageProviderTestNgTwo, MakeCanvasImageIfNeed004, TestSize.Level1)
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
HWTEST_F(ImageProviderTestNgTwo, GetImageSize002, TestSize.Level1)
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
HWTEST_F(ImageProviderTestNgTwo, PrepareImageData001, TestSize.Level1)
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
HWTEST_F(ImageProviderTestNgTwo, PrepareImageData002, TestSize.Level1)
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
HWTEST_F(ImageProviderTestNgTwo, PrepareImageData003, TestSize.Level1)
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
HWTEST_F(ImageProviderTestNgTwo, CreateImageObjHelper001, TestSize.Level1)
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
HWTEST_F(ImageProviderTestNgTwo, CreateImageObjHelper002, TestSize.Level1)
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
HWTEST_F(ImageProviderTestNgTwo, CreateImageObjHelper003, TestSize.Level1)
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
HWTEST_F(ImageProviderTestNgTwo, ImageProviderFailCallback001, TestSize.Level1)
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
HWTEST_F(ImageProviderTestNgTwo, ImageProviderFailCallback002, TestSize.Level1)
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
HWTEST_F(ImageProviderTestNgTwo, ImageProviderFailCallback003, TestSize.Level1)
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
HWTEST_F(ImageProviderTestNgTwo, ImageProviderCancelTask001, TestSize.Level1)
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
HWTEST_F(ImageProviderTestNgTwo, StaticImageDecoder001, TestSize.Level1)
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
HWTEST_F(ImageProviderTestNgTwo, ImageProviderCancelTask002, TestSize.Level1)
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
HWTEST_F(ImageProviderTestNgTwo, ImageProviderCancelTask003, TestSize.Level1)
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
HWTEST_F(ImageProviderTestNgTwo, ImageProviderCancelTask004, TestSize.Level1)
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
 * @tc.name: ImageProviderTestNgTwo_EndTaskKeyCorrectness
 * @tc.desc: Verify that ImageProvider uses GetTaskKey() for registering and ending tasks.
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNgTwo, ImageProviderTestNgTwo_EndTaskKeyCorrectness, TestSize.Level1)
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
HWTEST_F(ImageProviderTestNgTwo, StaticImageMakeCanvasImage001, TestSize.Level1)
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
 * @tc.name: ImageFileSizeTest001
 * @tc.desc: Test ImageFileSize
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNgTwo, ImageFileSizeTest001, TestSize.Level1)
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
    auto imageObj = ctx->imageObj_;
    EXPECT_NE(imageObj, nullptr);
    imageObj->SetImageFileSize(100);
    EXPECT_EQ(imageObj->GetImageFileSize(), 100);
    EXPECT_EQ(imageObj->GetImageDataSize(), 0);
}

/**
 * @tc.name: DownLoadSuccessCallbackTest001
 * @tc.desc: Test DownLoadSuccessCallback caches image and notifies context
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNgTwo, DownLoadSuccessCallbackTest001, TestSize.Level1)
{
    auto src = ImageSourceInfo("test.jpg");
    auto imageObj = AceType::MakeRefPtr<NG::StaticImageObject>(src, SizeF(100, 100), nullptr);

    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    std::string key = "test_key";
    bool res = ImageProvider::RegisterTask(key, WeakPtr<ImageLoadingContext>(ctx));
    EXPECT_TRUE(res);
    ImageProvider::DownLoadSuccessCallback(imageObj, key, true, 0);
    ImageProvider::DownLoadSuccessCallback(imageObj, key, false, 0);
}

/**
 * @tc.name: DownLoadOnProgressCallbackTest001
 * @tc.desc: Test DownLoadOnProgressCallback notifies context progress
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNgTwo, DownLoadOnProgressCallbackTest001, TestSize.Level1)
{
    auto src = ImageSourceInfo("test.jpg");
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(src, LoadNotifier(nullptr, nullptr, nullptr), true);
    std::string key = "progress_key";
    ImageProvider::RegisterTask(key, WeakPtr<ImageLoadingContext>(ctx));

    uint32_t progressNow = 0;
    uint32_t progressTotal = 0;
    ctx->SetOnProgressCallback([&progressNow, &progressTotal](uint32_t now, uint32_t total) {
        progressNow = now;
        progressTotal = total;
    });

    ImageProvider::DownLoadOnProgressCallback(key, true, 50, 100, 0);

    EXPECT_EQ(progressNow, 50);
    EXPECT_EQ(progressTotal, 100);
}

/**
 * @tc.name: QueryDataFromCacheTest001
 * @tc.desc: Test QueryDataFromCache returns nullptr if no cache
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNgTwo, QueryDataFromCacheTest001, TestSize.Level1)
{
    UriDownLoadConfig config;
    config.src = ImageSourceInfo("cache_hit.jpg");
    config.imageDfxConfig = ImageDfxConfig();
    config.taskKey = "download_key";
    config.sync = true;
    config.hasProgressCallback = false;
    ImageProvider::DownLoadImage(config);

    ImageSourceInfo src("not_exist.jpg");
    auto data = ImageProvider::QueryDataFromCache(src);
    EXPECT_EQ(data, nullptr);
}
} // namespace OHOS::Ace::NG
