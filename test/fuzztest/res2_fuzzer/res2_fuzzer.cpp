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
 

#include "res2_fuzzer.h"

#include <stddef.h>
#include <stdint.h>
#include "adapter/ohos/entrance/file_asset_provider_impl.h"
#include "core/common/asset_manager_impl.h"
#include "frameworks/core/components/theme/theme_constants.h"
#include "test/mock/core/common/theme_mock.h"

const uint32_t u16m = 65535;

namespace OHOS {
using namespace OHOS::Ace;
using namespace std;

int32_t WriteDataToFile(const string &path, const char* data, size_t size)
{
    FILE *file = nullptr;
    file = fopen(path.c_str(), "w+");
    if (file == nullptr) {
        return -1;
    }
    if (fwrite(data, 1, size, file) != size) {
        (void)fclose(file);
        return -1;
    }
    (void)fclose(file);
    return 0;
}

bool DoSomethingInterestingWithMyAPI(const uint8_t* data, size_t size)
{
    bool result = false;
    string cmd = "mkdir -p /data/test/arkui";
    auto ri = size % u16m;
    std::string s (reinterpret_cast<const char*>(data), ri);
    WriteDataToFile("/data/test/arkui/123.png", s.c_str(), ri);
    auto res = AceType::MakeRefPtr<ResourceAdapterMock>();
    auto theme = AceType::MakeRefPtr<ThemeConstants>(res);
    auto file = AceType::MakeRefPtr<FileAssetProviderImpl>();
    auto asset = AceType::MakeRefPtr<AssetManagerImpl>();
    string pack = "/data/test/arkui";
    vector<string> files  = {""};
    if(file->Initialize(pack,files)){
        asset->PushBack(file);
    }
    theme->LoadCustomStyle(asset);
    return result; 
}

}

/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    /* Run your code on data */
    OHOS::DoSomethingInterestingWithMyAPI(data, size);
    return 0;
}

