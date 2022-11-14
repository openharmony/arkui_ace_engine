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

#include "sharedimagemanager_fuzzer.h"
#include "base/resource/shared_image_manager.h"


namespace OHOS::Ace {
bool AddSharedImageTest(const uint8_t* data, size_t size)
{
    RefPtr<Ace::TaskExecutor> taskExecutor;
    RefPtr<SharedImageManager> sharedImageManager =AceType::MakeRefPtr<SharedImageManager>(taskExecutor);
    std::string randomString(reinterpret_cast<const char*>(data), size);
    sharedImageManager->AddSharedImage(randomString, std::vector<uint8_t>(randomString.begin(), randomString.end()));
    sharedImageManager->AddPictureNamesToReloadMap(std::move(randomString));
    auto findResult = sharedImageManager->FindImageInSharedImageMap(randomString, nullptr);
    return findResult;
}
}

/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    /* Run your code on data */
    OHOS::Ace::AddSharedImageTest(data, size);
    return 0;
}

