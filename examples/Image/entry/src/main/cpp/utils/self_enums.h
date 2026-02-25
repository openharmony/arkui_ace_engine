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

#ifndef CAPI_SELF_ENUMS_H
#define CAPI_SELF_ENUMS_H

namespace Self::UI {
    enum class LayoutPolicy { MATCH_PARENT = 0, WRAP_CONTENT = 1, FIX_AT_IDEAL_SIZE = 2 };
    enum class ImageFit { COVER = 0, CONTAIN = 1, MATRIX = 2, NONE = 3 };
} // namespace Self::UI

#endif // CAPI_SELF_ENUMS_H