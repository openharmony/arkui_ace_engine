/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_TEST_MOCK_BASE_MOCK_IMAGE_PACKER_H
#define FOUNDATION_ACE_TEST_MOCK_BASE_MOCK_IMAGE_PACKER_H
#include "gmock/gmock.h"
#include "base/image/image_packer.h"
#include "base/image/pixel_map.h"
namespace OHOS::Ace {
class MockImagePacker : public ImagePacker {
    DECLARE_ACE_TYPE(MockImagePacker, ImagePacker)
public:
    MOCK_METHOD3(StartPacking, uint32_t(uint8_t*, uint32_t, const PackOption&));
    MOCK_METHOD2(StartPacking, uint32_t(const std::string&, const PackOption&));
    MOCK_METHOD1(AddImage, uint32_t(PixelMap&));
    MOCK_METHOD1(FinalizePacking, uint32_t(int64_t&));

    static RefPtr<MockImagePacker> mockImagePacker_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_TEST_MOCK_BASE_MOCK_IMAGE_PACKER_H
