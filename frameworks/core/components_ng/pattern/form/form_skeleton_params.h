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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_SKELETON_PARAMS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_SKELETON_PARAMS_H

#ifndef ARKUI_CAPI_UNITTEST
#include "form_constants.h"
#else
namespace OHOS::AppExecFwk::Constants {
enum class Dimension : int8_t {
    DIMENSION_MIN = 1,
    DIMENSION_1_2 = DIMENSION_MIN,
    DIMENSION_2_2,
    DIMENSION_2_4,
    DIMENSION_4_4,
    DIMENSION_2_1,
    DIMENSION_1_1,
    DIMENSION_6_4,
    DIMENSION_2_3,
    DIMENSION_3_3,
    DIMENSION_MAX = DIMENSION_3_3
};
} // OHOS::AppExecFwk::Constants
#endif // ARKUI_CAPI_UNITTEST
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t MARGIN_DOUBLE = 2;

constexpr int32_t FORM_DIMENSION_HEIGHT_1 = 1;
constexpr int32_t FORM_DIMENSION_HEIGHT_2 = 2;

constexpr uint32_t CONTENT_BG_COLOR_DARK = 0xE62E3033;
constexpr uint32_t CONTENT_BG_COLOR_LIGHT = 0xE6FFFFFF;
constexpr uint32_t CONTENT_BG_COLOR_DARK_WITHOUT_BLUR = 0xFF2E3033;
constexpr uint32_t CONTENT_BG_COLOR_LIGHT_WITHOUT_BLUR = 0xFFFFFFFF;
constexpr double CONTENT_BG_OPACITY = 0.9;
constexpr uint32_t LINE_COLOR_LIGHT = 0xFF000000;
constexpr uint32_t LINE_COLOR_DARK = 0xFFFFFFFF;
constexpr double TITLE_LINE_OPACITY_LIGHT = 0.1;
constexpr double TITLE_LINE_OPACITY_DARK = 0.11;
constexpr double CONTENT_LINE_OPACITY_LIGHT = 0.05;
constexpr double CONTENT_LINE_OPACITY_DARK = 0.07;

constexpr float TITLE_LINE_WIDTH_RATIO_COMMON = 0.25f;
constexpr float TITLE_LINE_WIDTH_RATIO_1_1 = 0.37f;
constexpr float ENDING_LINE_WIDTH_RATIO = 0.5f;
constexpr float CONTENT_HEIGHT_ONE_THIRD = 0.33f;
constexpr float CONTENT_HEIGHT_TWO_THIRDS = 0.67f;

const Dimension LINE_HEIGHT_COMMON = 12.0_vp;
const Dimension LINE_HEIGHT_1_N = 8.0_vp;
const Dimension LINE_OFFSET = 16.0_vp;
const Dimension TITLE_MARGIN_TOP = LINE_OFFSET;
const Dimension TITLE_CONTENT_MARGINS_COMMON = LINE_OFFSET;
const Dimension TITLE_CONTENT_MARGINS_1_N = 6.0_vp;
const Dimension CONTENT_MARGINS_COMMON = 8.0_vp;
const Dimension ENDING_MARGIN_BOTTOM_COMMON = 24.0_vp;
const Dimension ENDING_MARGIN_BOTTOM_2_N = LINE_OFFSET;
const Dimension LINE_MARGIN_LEFT_COMMON = LINE_OFFSET;
const Dimension LINE_MARGIN_LEFT_1_N = 12.0_vp;
const Dimension RECT_RADIUS = 16.0_vp;
}

class FormSkeletonParams {
public:
    FormSkeletonParams(double cardWidth, double cardHeight, int32_t dimension, int32_t dimensionHeight,
        bool isDarkMode) : cardWidth_(cardWidth), cardHeight_(cardHeight), dimension_(dimension),
        dimensionHeight_(dimensionHeight)
    {
        titleMarginTop_ = static_cast<float>(TITLE_MARGIN_TOP.ConvertToPx());
        contentMargins_ = static_cast<float>(CONTENT_MARGINS_COMMON.ConvertToPx());
        if (dimensionHeight == FORM_DIMENSION_HEIGHT_1) {
            SetLineParamsOfHeight1();
        } else {
            SetLineParamsCommon();
        }
        fillColor_ = isDarkMode ? LINE_COLOR_DARK : LINE_COLOR_LIGHT;
        titleOpacity_ = isDarkMode ? TITLE_LINE_OPACITY_DARK : TITLE_LINE_OPACITY_LIGHT;
        contentOpacity_ = isDarkMode ? CONTENT_LINE_OPACITY_DARK : CONTENT_LINE_OPACITY_LIGHT;
    }

    ~FormSkeletonParams() {};

    void SetLineParamsOfHeight1()
    {
        lineWidth_ = static_cast<float>(cardWidth_ - LINE_MARGIN_LEFT_1_N.ConvertToPx() * MARGIN_DOUBLE);
        lineHeight_ = static_cast<float>(LINE_HEIGHT_1_N.ConvertToPx());
        titleContentMargins_ = static_cast<float>(TITLE_CONTENT_MARGINS_1_N.ConvertToPx());
        lineMarginLeft_ = static_cast<float>(LINE_MARGIN_LEFT_1_N.ConvertToPx());
        if (dimension_ == static_cast<int32_t>(OHOS::AppExecFwk::Constants::Dimension::DIMENSION_1_1)) {
            titleLineWidth_ = static_cast<float>(cardWidth_ * TITLE_LINE_WIDTH_RATIO_1_1);
        } else {
            titleLineWidth_ = static_cast<float>(cardWidth_ * TITLE_LINE_WIDTH_RATIO_COMMON);
        }
        contentLineNum_ = 1;
    }

    void SetLineParamsCommon()
    {
        lineWidth_ = static_cast<float>(cardWidth_ - LINE_MARGIN_LEFT_COMMON.ConvertToPx() * MARGIN_DOUBLE);
        lineHeight_ = static_cast<float>(LINE_HEIGHT_COMMON.ConvertToPx());
        titleContentMargins_ = static_cast<float>(TITLE_CONTENT_MARGINS_COMMON.ConvertToPx());
        lineMarginLeft_ = static_cast<float>(LINE_MARGIN_LEFT_COMMON.ConvertToPx());
        titleLineWidth_ = static_cast<float>(cardWidth_ * TITLE_LINE_WIDTH_RATIO_COMMON);
        endingLineWidth_ = static_cast<float>(cardWidth_ * ENDING_LINE_WIDTH_RATIO);
        float contentHeightRatio;
        float endingMarginBottom;
        if (dimensionHeight_ == FORM_DIMENSION_HEIGHT_2) {
            contentHeightRatio = CONTENT_HEIGHT_TWO_THIRDS;
            endingMarginBottom = static_cast<float>(ENDING_MARGIN_BOTTOM_2_N.ConvertToPx());
        } else {
            contentHeightRatio = CONTENT_HEIGHT_ONE_THIRD;
            endingMarginBottom = static_cast<float>(ENDING_MARGIN_BOTTOM_COMMON.ConvertToPx());
        }
        float titleContentAreaHeight = static_cast<float>(cardHeight_) * contentHeightRatio;
        float titleAreaHeight = titleMarginTop_ + lineHeight_ + titleContentMargins_;
        float contentAreaHeight = titleContentAreaHeight - titleAreaHeight;
        if (lineHeight_ + contentMargins_ > 0) {
            contentLineNum_ = static_cast<int32_t>(contentAreaHeight / (lineHeight_ + contentMargins_));
        }
        endingLineMarginTop_ = static_cast<float>(cardHeight_ - (titleAreaHeight +
            (lineHeight_ + contentMargins_) * contentLineNum_ - contentMargins_ +
            lineHeight_ + endingMarginBottom));
    }

    float GetLineWidth() const
    {
        return lineWidth_;
    }

    float GetLineHeight() const
    {
        return lineHeight_;
    }

    float GetTitleContentMargins() const
    {
        return titleContentMargins_;
    }

    float GetLineMarginLeft() const
    {
        return lineMarginLeft_;
    }

    float GetTitleLineWidth() const
    {
        return titleLineWidth_;
    }

    float GetTitleMarginTop() const
    {
        return titleMarginTop_;
    }

    float GetContentMargins() const
    {
        return contentMargins_;
    }

    float GetEndingLineWidth() const
    {
        return endingLineWidth_;
    }

    float GetEndingLineMarginTop() const
    {
        return endingLineMarginTop_;
    }

    int32_t GetContentLineNum() const
    {
        return contentLineNum_;
    }

    uint32_t GetFillColor() const
    {
        return fillColor_;
    }

    double GetTitleOpacity() const
    {
        return titleOpacity_;
    }

    double GetContentOpacity() const
    {
        return contentOpacity_;
    }

private:
    double cardWidth_ = 0.0;
    double cardHeight_ = 0.0;
    int32_t dimension_ = 0;
    int32_t dimensionHeight_ = 0;

    float lineWidth_ = 0.0f;
    float lineHeight_ = 0.0f;
    float titleContentMargins_ = 0.0f;
    float lineMarginLeft_ = 0.0f;
    float titleLineWidth_ = 0.0f;
    float titleMarginTop_ = 0.0f;
    float contentMargins_ = 0.0f;
    float endingLineWidth_ = 0.0f;
    float endingLineMarginTop_ = 0.0f;
    int32_t contentLineNum_ = 0;
    uint32_t fillColor_;
    double titleOpacity_;
    double contentOpacity_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_SKELETON_PARAMS_H
