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

#include "core/components_ng/test/pattern/custom_paint/common_constants.h"

namespace OHOS::Ace::NG {
const float IDEAL_WIDTH = 300.0f;
const float IDEAL_HEIGHT = 300.0f;
const SizeF IDEAL_SIZE(IDEAL_WIDTH, IDEAL_HEIGHT);

const float MAX_WIDTH = 400.0f;
const float MAX_HEIGHT = 400.0f;
const SizeF MAX_SIZE(MAX_WIDTH, MAX_HEIGHT);

const float MIN_WIDTH = 0.0f;
const float MIN_HEIGHT = 0.0f;
const SizeF MIN_SIZE(MIN_WIDTH, MIN_HEIGHT);

const int32_t CANVAS_WIDTH = 300;
const int32_t CANVAS_HEIGHT = 300;
const int32_t IMAGEDATA_WIDTH = 40;
const int32_t IMAGEDATA_HEIGHT = 40;
const int32_t DEFAULT_INSTANCE_ID = 0;
const int32_t DEFAULT_INSTANCE_ID1 = 1;
const int32_t DEFAULT_INSTANCE_ID2 = 2;
const int32_t BLENDMODE_VALUE_BEGIN = 3;
const int32_t BLENDMODE_VALUE_END = 5;

const double DEFAULT_DOUBLE0 = 0.0;
const double DEFAULT_DOUBLE1 = 1.0;
const double DEFAULT_DOUBLE2 = 2.0;
const double DEFAULT_DOUBLE10 = 10.0;

const double HALF_CIRCLE_ANGLE = 180.0;
const double FULL_CIRCLE_ANGLE = 360.0;
const double SPECIAL_CIRCLE_ANGLE = 324.0;
const double SPECIAL2_CIRCLE_ANGLE = -36.0;

const std::string URL_PREFIX = "data:";
const std::string IMAGE_PNG = "image/png";
const std::string IMAGE_JPEG = "image/jpeg";
const std::string IMAGE_WEBP = "image/webp";
const std::string QUALITY_0 = "0";
const std::string QUALITY_50 = "0.5";
const std::string QUALITY_100 = "1.0";

const std::string NULL_STR;
const std::string DEFAULT_STR = "default";
const std::string IMAGE_SRC = "common/images/test.png";
const std::string REPETITION_STR = "repetition";

const std::vector<std::string> CANDIDATE_STRINGS = { "aaaaaaaaaaaa", "bbbbbb", "abcdefg" };

const std::vector<std::string> FUNCTION_NAMES = { "grayscale", "sepia", "invert", "opacity", "brightness", "contrast",
    "blur", "drop-shadow", "saturate", "hue-rotate" };

const std::vector<double> CANDIDATE_DOUBLES = { 0.0, 1.0, 10.0, 100.0, 1000.0 };

const std::vector<Color> CANDIDATE_COLORS = { Color::TRANSPARENT, Color::WHITE, Color::BLACK, Color::RED, Color::GREEN,
    Color::BLUE, Color::GRAY };

const std::vector<CompositeOperation> CANDIDATE_COMPOSITE_OPERATIONS = { CompositeOperation::SOURCE_OVER,
    CompositeOperation::SOURCE_ATOP, CompositeOperation::SOURCE_IN, CompositeOperation::SOURCE_OUT,
    CompositeOperation::DESTINATION_OVER, CompositeOperation::DESTINATION_ATOP, CompositeOperation::DESTINATION_IN,
    CompositeOperation::DESTINATION_OUT, CompositeOperation::LIGHTER, CompositeOperation::COPY,
    CompositeOperation::XOR };

const std::vector<TextAlign> CANDIDATE_TEXT_ALIGNS = { TextAlign::LEFT, TextAlign::RIGHT, TextAlign::CENTER,
    TextAlign::JUSTIFY, TextAlign::START, TextAlign::END };

const std::vector<TextBaseline> CANDIDATE_TEXT_BASELINES = { TextBaseline::ALPHABETIC, TextBaseline::IDEOGRAPHIC,
    TextBaseline::TOP, TextBaseline::BOTTOM, TextBaseline::MIDDLE, TextBaseline::HANGING };

const std::vector<Dimension> CANDIDATE_DIMENSIONS = { 0.0_vp, 10.0_vp, 100.0_vp, 0.0_px, 10.0_px, 100.0_px, 0.0_fp,
    10.0_fp, 100.0_fp, 0.0_pct, 10.0_pct, 100.0_pct };

const std::vector<FontStyle> CANDIDATE_FONT_STYLES = { FontStyle::NORMAL, FontStyle::ITALIC };

const std::vector<FontWeight> CANDIDATE_FONT_WEIGHTS = {
    FontWeight::W100,
    FontWeight::W200,
    FontWeight::W300,
    FontWeight::W400,
    FontWeight::W500,
    FontWeight::W600,
    FontWeight::W700,
    FontWeight::W800,
    FontWeight::W900,
    FontWeight::BOLD,
    FontWeight::NORMAL,
    FontWeight::BOLDER,
    FontWeight::LIGHTER,
    FontWeight::MEDIUM,
    FontWeight::REGULAR,
};

const std::vector<std::string> FONT_FAMILY = { "Arial", "sans-serif", "monospace", "fantasy", "serif", "cursive",
    "system-ui", "emoji", "math" };

const std::vector<LineCapStyle> CANDIDATE_LINE_CAP_STYLES = { LineCapStyle::BUTT, LineCapStyle::ROUND,
    LineCapStyle::SQUARE };

const std::vector<LineJoinStyle> CANDIDATE_LINE_JOIN_STYLES = { LineJoinStyle::MITER, LineJoinStyle::ROUND,
    LineJoinStyle::BEVEL };

const std::vector<CanvasFillRule> CANDIDATE_CANVAS_FILL_RULES = { CanvasFillRule::NONZERO, CanvasFillRule::EVENODD };

const std::vector<SkPathFillType> CANDIDATE_SKPATH_FILL_TYPES = { SkPathFillType::kWinding, SkPathFillType::kEvenOdd };
} // namespace OHOS::Ace::NG
