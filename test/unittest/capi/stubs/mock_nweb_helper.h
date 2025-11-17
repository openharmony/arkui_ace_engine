/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#ifndef CAPI_STUBS_MOCK_NWEB_HELPER_H
#define CAPI_STUBS_MOCK_NWEB_HELPER_H

#include <unordered_map>
#include <memory>
#include <string>

#include "mock_nweb.h"

namespace OHOS::NWeb {

class NWebHelper {
public:
    static NWebHelper& Instance()
    {
        static NWebHelper helper;
        return helper;
    }
    bool InitAndRun(bool from_ark = true)
    {
        init_ = true;
        return true;
    }
    void SetBundlePath(const std::string& path)
    {
        bundlePath_ = path;
    }
    std::shared_ptr<NWeb> GetNWeb(int32_t nweb_id)
    {
        return mapNWeb_[nweb_id];
    }
    void SetNWeb(int32_t nweb_id, std::shared_ptr<NWeb> nweb)
    {
        mapNWeb_[nweb_id] = nweb;
    }
    bool IsInited()
    {
        return init_;
    }

private:
    NWebHelper() : init_(false) {}

private:
    bool init_;
    std::string bundlePath_;
    std::unordered_map<int32_t, std::shared_ptr<NWeb>> mapNWeb_;
};
} // namespace OHOS::NWeb

#endif