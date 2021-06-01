/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/image/test/unittest/image_provider_test_utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

class ImageProviderTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
    void SetUp() override {}
    void TearDown() override {}
};

/**
 * @tc.name: GIFSupport001
 * @tc.desc: if gif uri is right, loadImageData can get and decode the data.
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTest, GIFSupport001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create FileImageProvider.
     */
    auto imageProvider = FileImageProvider();
    /**
     * @tc.steps: step2. Call LoadImageData.
     * @tc.expected: step2. data should not be nullptr.
     */
    auto data = imageProvider.LoadImageData(FILE_GIF);
    ASSERT_TRUE(data);

    /**
     * @tc.steps: step3. Call GetCodec.
     * @tc.expected: step3. codec_ should not be nullptr.
     */
    auto codec = imageProvider.GetCodec(data);
    ASSERT_TRUE(codec);
}

/**
 * @tc.name: GIFSupport002
 * @tc.desc: if gif uri is right, but the file is broken, cannot decode the data.
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTest, GIFSupport002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create FileImageProvider.
     */
    auto imageProvider = FileImageProvider();

    /**
     * @tc.steps: step2. Call LoadImageData.
     * @tc.expected: step2. data should not be nullptr.
     */
    auto data = imageProvider.LoadImageData(FILE_GIF_BROKEN);
    ASSERT_TRUE(data);

    /**
     * @tc.steps: step3. Call GetCodec.
     * @tc.expected: step3. codec_ should be nullptr.
     */
    auto codec = imageProvider.GetCodec(data);
    ASSERT_TRUE(!codec);
}

/**
 * @tc.name: FileSupport001
 * @tc.desc: if file uri is right, test for loadImage can load and decode the image.
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTest, FileSupport001, TestSize.Level1)
{
    std::vector<std::string> fileImages = { FILE_JPG, FILE_PNG, FILE_WEBP, FILE_BMP };
    for (auto file : fileImages) {
        /**
         * @tc.steps: step1. create FileImageProvider.
         */
        auto imageProvider = FileImageProvider();

        /**
         * @tc.steps: step2. Call LoadImageData.
         * @tc.expected: step2. data should not be nullptr.
         */
        auto data = imageProvider.LoadImageData(file);
        ASSERT_TRUE(data);

        /**
         * @tc.steps: step3. Call GetCodec..
         * @tc.expected: step3. codec_ should not be nullptr.
         */
        auto codec = imageProvider.GetCodec(data);
        ASSERT_TRUE(codec);
    }
}

/**
 * @tc.name: FileSupport002
 * @tc.desc: if file uri is wrong, loadImageData can not load the image.
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTest, FileSupport002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create FileImageProvider.
     */
    auto imageProvider = FileImageProvider();

    /**
     * @tc.steps: step2. Call LoadImageData.
     * @tc.expected: step2. data should be nullptr.
     */
    auto data = imageProvider.LoadImageData(NO_FILE);
    ASSERT_TRUE(!data);
}

/**
 * @tc.name: MemorySupport001
 * @tc.desc: given right memory data, loadImageData can load and decode the image.
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTest, MemorySupport001, TestSize.Level1)
{
    std::vector<std::string> fileImages = { FILE_JPG, FILE_PNG, FILE_WEBP, FILE_BMP };
    for (auto fileImage : fileImages) {
        /**
         * @tc.steps: step1. create MemoryImageProvider by reading right image file.
         */
        std::string filePath = ImageProvider::RemovePathHead(fileImage);
        std::unique_ptr<FILE, decltype(&fclose)> file(fopen(filePath.c_str(), "rb"), fclose);
        std::vector<uint8_t> imageData = ReadFromFile(std::move(file));
        auto imageProvider = AceType::MakeRefPtr<MemoryImageProvider>();
        imageProvider->UpdateData(std::string(), imageData);

        /**
         * @tc.steps: step2. Call LoadImageData.
         * @tc.expected: step2. data should not be nullptr.
         */
        auto data = imageProvider->LoadImageData(std::string());
        ASSERT_TRUE(data);

        /**
         * @tc.steps: step3. Call GetCodec.
         * @tc.expected: step3. codec_ should not be nullptr.
         */
        auto codec = imageProvider->GetCodec(data);
        ASSERT_TRUE(codec);
    }
}

/**
 * @tc.name: MemorySupport002
 * @tc.desc: given wrong memory data, loadImageData can not decode the image.
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTest, MemorySupport002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MemoryImageProvider by a wrong memory data.
     */
    std::vector<uint8_t> emptyData(100, 0);
    auto imageProvider = AceType::MakeRefPtr<MemoryImageProvider>();
    imageProvider->UpdateData(std::string(), emptyData);

    /**
     * @tc.steps: step2. Call LoadImageData.
     * @tc.expected: step2. data should not be nullptr.
     */
    auto data = imageProvider->LoadImageData(std::string());
    ASSERT_TRUE(data);

    /**
     * @tc.steps: step3. Call GetCodec.
     * @tc.expected: step3. codec_ should be nullptr.
     */
    auto codec = imageProvider->GetCodec(data);
    ASSERT_TRUE(!codec);
}

/**
 * @tc.name: MemorySupport003
 * @tc.desc: given null memory data, loadImageData can not load the image.
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTest, MemorySupport003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MemoryImageProvider by a null memory data.
     */
    std::vector<uint8_t> emptyData;
    auto imageProvider = AceType::MakeRefPtr<MemoryImageProvider>();
    imageProvider->UpdateData(std::string(), emptyData);

    /**
     * @tc.steps: step2. Call LoadImageData.
     * @tc.expected: step2. data should be nullptr.
     */
    auto data = imageProvider->LoadImageData(std::string());
    ASSERT_TRUE(!data);
}

/**
 * @tc.name: Create001
 * @tc.desc: given right uri, ImageProvider::Create can create an ImageProvider pointer.
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTest, Create001, TestSize.Level1)
{
    std::vector<std::string> uris = { ASSET_IMAGE, FILE_GIF, NETWORK_HTTP_IMAGE, NETWORK_HTTPS_IMAGE };
    for (auto uri : uris) {
        /**
         * @tc.steps: step1. create ImageProvider by calling Create().
         * @tc.expected: step1. imageProvider should not be nullptr.
         */
        auto imageProvider = ImageProvider::Create(uri);
        ASSERT_TRUE(imageProvider);
    }
}

/**
 * @tc.name: Create002
 * @tc.desc: given wrong uri, ImageProvider::Create cannot create an ImageProvider pointer.
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTest, Create002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ImageProvider by calling Create().
     * @tc.expected: step1. imageProvider should be nullptr.
     */
    auto imageProvider = ImageProvider::Create(WRONG_URI);
    ASSERT_TRUE(!imageProvider);
}

/**
 * @tc.name: WrongImageData001
 * @tc.desc: given right uri, but broken image. FileImageProvider cannot decode the data.
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTest, WrongImageData001, TestSize.Level1)
{
    std::vector<std::string> brokenFiles = { FILE_JPG_BROKEN, FILE_PNG_BROKEN, FILE_WEBP_BROKEN, FILE_BMP_BROKEN };
    for (auto brokenFile : brokenFiles) {
        /**
         * @tc.steps: step1. create FileImageProvider.
         */
        auto imageProvider = FileImageProvider();

        /**
         * @tc.steps: step2. Call LoadImageData.
         * @tc.expected: step2. data should not be nullptr.
         */
        auto data = imageProvider.LoadImageData(brokenFile);
        ASSERT_TRUE(data);

        /**
         * @tc.steps: step3. Call GetCodec.
         * @tc.expected: step3. codec_ should be nullptr.
         */
        auto codec = imageProvider.GetCodec(data);
        ASSERT_TRUE(!codec);
    }
}

} // namespace OHOS::Ace