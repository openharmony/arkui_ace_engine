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

#include "core/image/test/unittest/image_compressor_test.h"

#include "gtest/gtest.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

class ImageCompressorTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
    void SetUp()
    {
        instance->refCount_ = 0;
    }
    void TearDown() {}

    std::shared_ptr<ImageCompressor> instance = ImageCompressor::GetInstance();
};

static sk_sp<SkImage> LoadImage()
{
    auto imageLoader = FileImageLoader();
    auto data = imageLoader.LoadImageData(ImageSourceInfo(FILE_JPG));
    auto image = SkImage::MakeFromEncoded(data);
    GTEST_LOG_(INFO) << "ImageCompressorTest LoadImage " << image;
    if (image) {
        return image->makeRasterImage();
    }
    return nullptr;
}

/**
 * @tc.name: ImageCompressor001
 * @tc.desc: Test partition info init
 * @tc.type: FUNC
 * @tc.require: issueI5PFV6
 */
HWTEST_F(ImageCompressorTest, ImageCompressor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init instance
     * @tc.expected: parts inited
     */
    instance->Init();
    ImageCompressor::PartInfo p = {};
    for (int i = 0; i < 1024; i++) {
        instance->InitPartitionInfo(&p, instance->partitions_[1], 1);
        instance->InitPartitionInfo(&p, instance->partitions_[1], 2);
        instance->InitPartitionInfo(&p, instance->partitions_[1], 3);
    }
    ASSERT_TRUE(instance->parts_.size() > 0);
}

/**
 * @tc.name: ImageCompressor002
 * @tc.desc: Test no shader file
 * @tc.type: FUNC
 * @tc.require: issueI5PFV6
 */
HWTEST_F(ImageCompressorTest, ImageCompressor002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. cache images one by one.
     */
    std::string &path = const_cast<std::string &>(instance->shader_path_);
    path = "";
    instance->Init();
    auto image = LoadImage();
    if (image && instance->CanCompress()) {
        SkPixmap pixmap;
        image->peekPixels(&pixmap);
        std::string key = "key2";
        int32_t width = static_cast<int32_t>(pixmap.width());
        int32_t height = static_cast<int32_t>(pixmap.height());
        auto compressData = instance->GpuCompress(key, pixmap, width, height);
        ASSERT_TRUE(compressData == nullptr);
        instance->WriteToFile(key, compressData, {width, height});
    }
    path = "/system/bin/astc.bin";
}

/**
 * @tc.name: ImageCompressor003
 * @tc.desc: Test compress success
 * @tc.type: FUNC
 * @tc.require: issueI5PFV6
 */
HWTEST_F(ImageCompressorTest, ImageCompressor003, TestSize.Level1)
{
    instance->Init();
    auto image = LoadImage();
    if (image && instance->CanCompress()) {
        SkPixmap pixmap;
        image->peekPixels(&pixmap);
        std::string key = "key3";
        int32_t width = static_cast<int32_t>(pixmap.width());
        int32_t height = static_cast<int32_t>(pixmap.height());
        auto compressData = instance->GpuCompress(key, pixmap, width, height);
        ASSERT_TRUE(compressData != nullptr);
        instance->WriteToFile(key, compressData, {width, height});
    }
}

/**
 * @tc.name: ImageCompressor004
 * @tc.desc: Test compress failed with quality failed
 * @tc.type: FUNC
 * @tc.require: issueI5PFV6
 */
HWTEST_F(ImageCompressorTest, ImageCompressor004, TestSize.Level1)
{
    instance->Init();
    instance->maxErr_ = 0;
    auto image = LoadImage();
    if (image && instance->CanCompress()) {
        SkPixmap pixmap;
        image->peekPixels(&pixmap);
        std::string key = "key4";
        int32_t width = static_cast<int32_t>(pixmap.width());
        int32_t height = static_cast<int32_t>(pixmap.height());
        auto compressData = instance->GpuCompress(key, pixmap, width, height);
        ASSERT_TRUE(compressData == nullptr);
        instance->WriteToFile(key, compressData, {width, height});
    }
}

/**
 * @tc.name: ImageCompressor005
 * @tc.desc: Test compress sucess and release context
 * @tc.type: FUNC
 * @tc.require: issueI5PFV6
 */
HWTEST_F(ImageCompressorTest, ImageCompressor005, TestSize.Level1)
{
    instance->Init();
    auto image = LoadImage();
    if (image && instance->CanCompress()) {
        SkPixmap pixmap;
        image->peekPixels(&pixmap);
        std::string key = "key5";
        int32_t width = static_cast<int32_t>(pixmap.width());
        int32_t height = static_cast<int32_t>(pixmap.height());
        auto compressData = instance->GpuCompress(key, pixmap, width, height);
        ASSERT_TRUE(compressData != nullptr);
        instance->WriteToFile(key, compressData, {width, height});
        auto task = instance->ScheduleReleaseTask();
        task();
        ASSERT_TRUE(instance->context_ == nullptr);
        instance->InitRecords();
    }
}

/**
 * @tc.name: ImageCompressor006
 * @tc.desc: Test compress sucess and release context
 * @tc.type: FUNC
 * @tc.require: issueI5PFV6
 */
HWTEST_F(ImageCompressorTest, ImageCompressor006, TestSize.Level1)
{
    instance->Init();
    auto image = LoadImage();
    if (image && instance->CanCompress()) {
        SkPixmap pixmap;
        image->peekPixels(&pixmap);
        std::string key = "key6";
        int32_t width = 0;
        int32_t height = 0;
        auto compressData = instance->GpuCompress(key, pixmap, width, height);
        ASSERT_TRUE(compressData == nullptr);
    }
}

/**
 * @tc.name: ImageCompressor007
 * @tc.desc: Test compress sucess and release context
 * @tc.type: FUNC
 * @tc.require: issueI5PFV6
 */
HWTEST_F(ImageCompressorTest, ImageCompressor007, TestSize.Level1)
{
    instance->Init();
    auto image = LoadImage();
    if (image && instance->CanCompress()) {
        SkPixmap pixmap;
        image->peekPixels(&pixmap);
        std::string key = "key7";
        int32_t width = static_cast<int32_t>(pixmap.width());
        int32_t height = static_cast<int32_t>(pixmap.height());
        auto compressData = instance->GpuCompress(key, pixmap, width, height);
        auto strip = instance->StripFileHeader(compressData);
        ASSERT_TRUE(strip != nullptr);
    }
}

/**
 * @tc.name: TestSwitch001
 * @tc.desc: Test switch
 * @tc.type: FUNC
 * @tc.require: issueI5PFV6
 */
HWTEST_F(ImageCompressorTest, TestSwitch001, TestSize.Level1)
{
    instance->Init();
    instance->switch_ = false;
    ASSERT_TRUE(!instance->CanCompress());
    instance->switch_ = true;
    instance->clOk_ = true;
    ASSERT_TRUE(instance->CanCompress());
}

} // namespace OHOS::Ace
