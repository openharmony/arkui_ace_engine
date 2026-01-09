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

#ifndef FONT_TYPES_H
#define FONT_TYPES_H

namespace OHOS {
namespace Rosen {
namespace Drawing {
enum class TextEncoding {
    UTF8 = 0,
    UTF16,
    UTF32,
    GLYPH_ID,
};

enum class FontHinting {
    NONE = 0,
    SLIGHT,
    NORMAL,
    FULL,
};

enum class FontEdging {
    ALIAS = 0,
    ANTI_ALIAS,
    SUBPIXEL_ANTI_ALIAS,
};
} // namespace Drawing
} // namespace Rosen
} // namespace OHOS
#endif
