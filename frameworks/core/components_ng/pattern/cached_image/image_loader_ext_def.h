/*
 * Copyright (C) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_LOADER_EXT_DEF_H
#define INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_LOADER_EXT_DEF_H

#include <stdint.h>
#include <string>
#include <vector>

#include <iremote_object.h>

#include "core/components_ng/pattern/cached_image/image_target.h"

constexpr uint64_t REQUEST_ID_UNASSIGNED = 0;
const std::string REQUEST_ID_STR_UNASSIGNED = "\'0\'";

constexpr const char* IMAGE_LOADER_SO_PATH = "/system/lib64/platformsdk/libimageloader_core.z.so";

constexpr const char* FUNC_REQUEST_IMAGE = "RequestImage";
constexpr const char* FUNC_CANCEL_IMAGE_REQUEST = "CancelImageRequest";

namespace OHOS::AbilityRuntime {
class Context;
}

#ifdef __cplusplus
extern "C" {
#endif

struct RequestOptionsInfo {
    int32_t width;
    int32_t height;
    int32_t row;
    int32_t column;
    bool isHdr;
    uint32_t imageQuality;
}__attribute__((weak));

struct ImageRequestInfo {
    OHOS::sptr<OHOS::IRemoteObject> token;
    std::string src;
    std::vector<std::string> srcs;
    RequestOptionsInfo requestOptionsInfo;
    uint64_t identifier;
    OHOS::sptr<OHOS::Media::ImageTarget> target;
    std::shared_ptr<OHOS::AbilityRuntime::Context> context;
}__attribute__((weak));

using RequestImageFunc = void (*)(const ImageRequestInfo& imageRequestInfo);
using CancelImageRequestFunc = void (*)(const ImageRequestInfo& imageRequestInfo);

#ifdef __cplusplus
};
#endif

#endif // INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_LOADER_EXT_DEF_H