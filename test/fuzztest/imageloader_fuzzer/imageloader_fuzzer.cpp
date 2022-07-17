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

#include "imageloader_fuzzer.h"
#include "core/image/image_loader.h"

namespace OHOS {
    const Ace::ImageSourceInfo CreatImageSourceInfo(const uint8_t* data, size_t size)
    {
        std::string randomString = reinterpret_cast<const char*>(data);
        Ace::InternalResource::ResourceId resourceId = Ace::InternalResource::ResourceId::NO_ID;
        Ace::RefPtr<Ace::PixelMap> pixmap = nullptr;
        Ace::Dimension dimension(static_cast<double>(U32_AT(data)));
        Ace::ImageSourceInfo info(randomString, dimension, dimension, resourceId, pixmap);
        return info;
    }

    bool FileImageLoaderTest(const uint8_t* data, size_t size)
    {
        auto info = CreatImageSourceInfo(data, size);
        Ace::WeakPtr<Ace::PipelineBase> context = nullptr;
        Ace::DataProviderImageLoader dataProviderImageLoader;
        return dataProviderImageLoader.LoadImageData(info, context) != nullptr;
    }

    bool AssetImageLoader(const uint8_t* data, size_t size)
    {
        auto info = CreatImageSourceInfo(data, size);
        Ace::WeakPtr<Ace::PipelineBase> context = nullptr;
        Ace::AssetImageLoader assetImageLoader;
        return assetImageLoader.LoadImageData(info, context) != nullptr;
    }

    bool NetworkImageLoader(const uint8_t* data, size_t size)
    {
        auto info = CreatImageSourceInfo(data, size);
        Ace::WeakPtr<Ace::PipelineBase> context = nullptr;
        Ace::NetworkImageLoader networkImageLoader;
        return networkImageLoader.LoadImageData(info, context) != nullptr;
    }

    bool InternalImageLoader(const uint8_t* data, size_t size)
    {
        auto info = CreatImageSourceInfo(data, size);
        Ace::WeakPtr<Ace::PipelineBase> context = nullptr;
        Ace::InternalImageLoader internalImageLoader;
        return internalImageLoader.LoadImageData(info, context) != nullptr;
    }
}

/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    /* Run your code on data */
    OHOS::FileImageLoaderTest(data, size);
    OHOS::AssetImageLoader(data, size);
    OHOS::NetworkImageLoader(data, size);
    OHOS::InternalImageLoader(data, size);
    return 0;
}

