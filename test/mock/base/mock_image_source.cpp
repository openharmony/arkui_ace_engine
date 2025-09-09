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
#include "test/mock/base/mock_image_source.h"
namespace OHOS::Ace {
RefPtr<MockImageSource> MockImageSource::mockImageSource_ = nullptr;

RefPtr<ImageSource> ImageSource::Create(int32_t fd)
{
    return MockImageSource::mockImageSource_;
}

RefPtr<ImageSource> ImageSource::Create(const uint8_t* data, uint32_t size, uint32_t& errorCode)
{
    return MockImageSource::mockImageSource_;
}

RefPtr<ImageSource> ImageSource::Create(const std::string& filePath)
{
    return MockImageSource::mockImageSource_;
}

bool ImageSource::IsAstc(const uint8_t* data, size_t size)
{
    return true;
}

ImageSource::Size ImageSource::GetASTCInfo(const uint8_t* data, size_t size)
{
    return { 0, 0 };
}

RefPtr<ImageSource> ImageSource::Create(const uint8_t* data, uint32_t size)
{
    return MockImageSource::mockImageSource_;
}

} // namespace OHOS::Ace
