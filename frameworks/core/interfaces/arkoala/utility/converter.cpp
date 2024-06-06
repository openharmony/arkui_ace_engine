/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "converter.h"

namespace OHOS::Ace::NG::Converter
{
void ParseDimension(const Ark_String &string, Ark_Length *result) {
    char *suffixPtr = nullptr;
    float value = std::strtof(string.chars, &suffixPtr);

    if (!suffixPtr || suffixPtr == string.chars)
    {
      // not a numeric value
      result->unit = -1;
      return;
    }
    result->value = value;
    if (suffixPtr[0] == '\0' || (suffixPtr[0] == 'v' && suffixPtr[1] == 'p'))
    {
      result->unit = 1;
    }
    else if (suffixPtr[0] == '%')
    {
      result->unit = 3;
    }
    else if (suffixPtr[0] == 'p' && suffixPtr[1] == 'x')
    {
      result->unit = 0;
    }
    else if (suffixPtr[0] == 'l' && suffixPtr[1] == 'p' && suffixPtr[2] == 'x')
    {
      result->unit = 4;
    }
    else if (suffixPtr[0] == 'f' && suffixPtr[1] == 'p')
    {
      result->unit = 2;
    }
    else
    {
      result->unit = -1;
    }
}

Color Convert(const Ark_Color& src) {
    switch (src) {
        case 0: { // White
            return Color(0xffffffff);
        }
        case 1: { // Black
            return Color(0xff000000);
        }
        case 2: { // Blue
            return Color(0xff0000ff);
        }
        case 3: { // Brown
            return Color(0xffa52a2a);
        }
        case 4: { // Gray
            return Color(0xffc0c0c0);
        }
        case 5: { // Green
            return Color(0xff00ff00);
        }
        case 6: { // Grey
            return Color(0xffc0c0c0);
        }
        case 7: { // Orange
            return Color(0xffffa500);
        }
        case 8: { // Pink
            return Color(0xffffc0cb);
        }
        case 9: { // Red
            return Color(0xffff0000);
        }
        case 10: { // Yellow
            return Color(0xffffff00);
        }
        case 11: { // Transparent
            return Color(0x00000000);
        }
        default: {
            return Color(0x000000);
        }
    }
}

} // namespace OHOS::Ace::NG::Converter
