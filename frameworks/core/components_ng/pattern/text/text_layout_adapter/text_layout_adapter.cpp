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

#include "core/components_ng/pattern/text/text_layout_adapter.h"

#include "unicode/uchar.h"

namespace OHOS::Ace::NG {
bool TextLayoutadapter::IsLeftToRight(int32_t charOfShowingText)
{
    UChar32 uCharOfShowingText = charOfShowingText;
    return u_charDirection(uCharOfShowingText) == UCharDirection::U_LEFT_TO_RIGHT;
}
bool TextLayoutadapter::IsRightToLeft(int32_t charOfShowingText)
{
    UChar32 uCharOfShowingText = charOfShowingText;
    return u_charDirection(uCharOfShowingText) == UCharDirection::U_RIGHT_TO_LEFT;
}
bool TextLayoutadapter::IsRightTOLeftArabic(int32_t charOfShowingText)
{
    UChar32 uCharOfShowingText = charOfShowingText;
    return u_charDirection(uCharOfShowingText) == UCharDirection::U_RIGHT_TO_LEFT_ARABIC;
}
} // namespace OHOS::Ace::NG
