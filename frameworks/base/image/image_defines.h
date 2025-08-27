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
#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_IMAGE_ACE_IMAGE_DEFINES_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_IMAGE_ACE_IMAGE_DEFINES_H

#include <string>

namespace OHOS {
namespace Ace {
enum class ImageType {
    BASE = 0,
    DRAWABLE,
    PIXELMAP_DRAWABLE,
    LAYERED_DRAWABLE,
    ANIMATED_DRAWABLE,
};

enum class ImageErrorCode : int32_t {
    DEFAULT = -1,
    CREATE_IMAGE_UNKNOWN_SOURCE_TYPE = 101000,
    GET_IMAGE_SYNC_HTTP_CANCELLED = 102010,
    GET_IMAGE_SYNC_HTTP_FAILED = 102011,
    GET_IMAGE_ASYNC_HTTP_CANCELLED = 102012,
    GET_IMAGE_ASYNC_HTTP_FAILED = 102013,
    GET_IMAGE_BASE_WRONG_CODE_FORMAT = 102030,
    GET_IMAGE_BASE_DECODE_IMAGE_FAILED = 102031,
    GET_IMAGE_FILE_PATH_TOO_LONG = 102050,
    GET_IMAGE_FILE_READ_DATA_FAILED = 102051,
    GET_IMAGE_RESOURCE_GET_DATA_BY_NAME_FAILED = 102070,
    GET_IMAGE_RESOURCE_GET_DATA_BY_ID_FAILED = 102071,
    GET_IMAGE_RESOURCE_URI_INVALID = 102072,
    GET_IMAGE_ASSET_URI_INVALID = 102090,
    GET_IMAGE_ASSET_GET_FAILED = 102091,
    GET_IMAGE_DATA_PROVIDER_OPEN_FAILED = 102110,
    GET_IMAGE_DATA_PROVIDER_GET_FAILED = 102111,
    GET_IMAGE_DATA_PROVIDER_READ_FAILED = 102112,
    GET_IMAGE_DECODE_DATA_PROVIDER_DATA_EMPTY = 102130,
    GET_IMAGE_SHARED_MEMORY_LOAD_TIMEOUT = 102131,
    BUILD_IMAGE_MAKE_SVG_DOM_FAILED = 103100,
    BUILD_IMAGE_DATA_SIZE_INVALID = 103200,
    MAKE_CANVAS_IMAGE_SOURCE_CREATE_FAILED = 111000,
    MAKE_CANVAS_IMAGE_PIXELMAP_FAILED = 111001,
};

struct ImageErrorInfo {
    ImageErrorCode errorCode = ImageErrorCode::DEFAULT;
    std::string errorMessage = "";
};
}
} // namespace OHOS
#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_IMAGE_ACE_IMAGE_DEFINES_H
