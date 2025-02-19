/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_IMAGE_PROVIDER_MOCK_IMAGE_LOADER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_IMAGE_PROVIDER_MOCK_IMAGE_LOADER_H
#include "gmock/gmock.h" // Brings in gMock.

#include "core/image/image_loader.h"

namespace OHOS::Ace {
class MockImageLoader : public ImageLoader {
public:
    MOCK_METHOD(std::shared_ptr<RSData>, LoadImageData,
        (const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context), (override));
    MOCK_METHOD(RefPtr<NG::ImageData>, LoadDecodedImageData,
        (const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context), (override));
};
// unit test globals
extern std::vector<std::thread> g_threads;
extern RefPtr<MockImageLoader> g_loader;
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_IMAGE_PROVIDER_MOCK_IMAGE_LOADER_H
