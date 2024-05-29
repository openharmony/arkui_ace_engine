/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_TEXT_LAYOUT_INFO_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_TEXT_LAYOUT_INFO_H

#include "core/components/common/properties/text_style.h"

namespace OHOS::Ace {
struct FontMetrics {
    enum FontMetricsFlags {
        UNDERLINE_THICKNESS_IS_VALID_FLAG = 1 << 0,
        UNDERLINE_POSITION_IS_VALID_FLAG  = 1 << 1,
        STRIKEOUT_THICKNESS_IS_VALID_FLAG = 1 << 2,
        STRIKEOUT_POSITION_IS_VALID_FLAG  = 1 << 3,
        BOUNDS_INVALID_FLAG               = 1 << 4,
    };
 
    uint32_t fFlags;
    float fTop;
    float fAscent;
    float fDescent;
    float fBottom;
    float fLeading;
    float fAvgCharWidth;
    float fMaxCharWidth;
    float fXMin;
    float fXMax;
    float fXHeight;
    float fCapHeight;
    float fUnderlineThickness;
    float fUnderlinePosition;
    float fStrikeoutThickness;
    float fStrikeoutPosition;
};
 
class RunMetrics {
public:
    TextStyle textStyle;
    FontMetrics fontMetrics;
};
 
struct TextLineMetrics {
    /** Text ascender height */
    double ascender;
    /** Tex descender height */
    double descender;
    /** The height of a capital letter */
    double capHeight;
    /** The height of a lowercase letter */
    double xHeight;
    /** Text width */
    double width;
    /** Line height */
    double height;
    /**
     * The distance from the left end of the text to the left end of the container,
     * aligned to 0, is the width of the container minus the width of the line of text
     */
    double x;
    /**
     * The height from the top of the text to the top of the container, the first line is 0,
     *  and the second line is the height of the first line
     */
    double y;
    /** Start Index */
    size_t startIndex;
    /** End Index */
    size_t endIndex;
 
    FontMetrics firstCharMetrics;
 
    /** The y position of the baseline for this line from the top of the paragraph */
    double baseline;
    /** Zero indexed line number */
    size_t lineNumber;
 
    std::map<size_t, RunMetrics> runMetrics;
};
} // namespace OHOS::Ace
 
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_TEXT_LAYOUT_INFO_H