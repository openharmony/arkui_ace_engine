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

#ifndef FOUNDATION_ACE_DRAWABLE_DESCRIPTOR_BASE_ERROR_H
#define FOUNDATION_ACE_DRAWABLE_DESCRIPTOR_BASE_ERROR_H

namespace OHOS {
namespace Ace {
namespace Drawable {
enum class LoadError {
    ERROR_CODE_NO_ERROR = -1,
    ERROR_CODE_FETCH_LOADING_ERROR = 10001,
    ERROR_CODE_FETCH_DECODE_ERROR = 10002,
    ERROR_CODE_ANIMATED_DATA_NOT_READY_ERROR = 10003,
};
}
} // namespace Ace
} // namespace OHOS

#endif // FOUNDATION_ACE_DRAWABLE_DESCRIPTOR_BASE_ERROR_H
