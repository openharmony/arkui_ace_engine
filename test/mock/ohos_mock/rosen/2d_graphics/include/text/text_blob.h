/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef TEXT_BLOB_H
#define TEXT_BLOB_H

#include <memory>

#include "draw/path.h"
#include "utils/data.h"

#include "font.h"
#include "font_types.h"

namespace OHOS {
namespace Rosen {
namespace Drawing {
enum class TextContrast {
    FOLLOW_SYSTEM = 0, // Follow the system configuration.
    DISABLE_CONTRAST, // Do not follow the system, APP prohibits high contrast.
    ENABLE_CONTRAST // Do not follow the system, APP enables high contrast.
};
class TextBlob {
public:
    TextBlob() noexcept = default;
    virtual ~TextBlob() = default;

    static std::shared_ptr<TextBlob> MakeFromText(const void* text, size_t byteLength,
        const Font& font, TextEncoding encoding = TextEncoding::UTF8)
    {
        return std::make_shared<TextBlob>();
    }
};
} // namespace Drawing
} // namespace Rosen
} // namespace OHOS
#endif
