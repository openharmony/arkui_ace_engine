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
 
    uint32_t fFlags = 0;
    float fTop = 0.0f;
    float fAscent = 0.0f;
    float fDescent = 0.0f;
    float fBottom = 0.0f;
    float fLeading = 0.0f;
    float fAvgCharWidth = 0.0f;
    float fMaxCharWidth = 0.0f;
    float fXMin = 0.0f;
    float fXMax = 0.0f;
    float fXHeight = 0.0f;
    float fCapHeight = 0.0f;
    float fUnderlineThickness = 0.0f;
    float fUnderlinePosition = 0.0f;
    float fStrikeoutThickness = 0.0f;
    float fStrikeoutPosition = 0.0f;
};
 
class RunMetrics {
public:
    TextStyle textStyle;
    FontMetrics fontMetrics;
};
 
struct TextLineMetrics {
    /** Text ascender height */
    double ascender = 0.0;
    /** Tex descender height */
    double descender = 0.0;
    /** The height of a capital letter */
    double capHeight = 0.0;
    /** The height of a lowercase letter */
    double xHeight = 0.0;
    /** Text width */
    double width = 0.0;
    /** Line height */
    double height = 0.0;
    /**
     * The distance from the left end of the text to the left end of the container,
     * aligned to 0, is the width of the container minus the width of the line of text
     */
    double x = 0.0;
    /**
     * The height from the top of the text to the top of the container, the first line is 0,
     *  and the second line is the height of the first line
     */
    double y = 0.0;
    /** Start Index */
    size_t startIndex = 0;
    /** End Index */
    size_t endIndex = 0;
 
    FontMetrics firstCharMetrics;
 
    /** The y position of the baseline for this line from the top of the paragraph */
    double baseline = 0.0;
    /** Zero indexed line number */
    size_t lineNumber = 0;
 
    std::map<size_t, RunMetrics> runMetrics;
};
} // namespace OHOS::Ace
 
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_TEXT_LAYOUT_INFO_H