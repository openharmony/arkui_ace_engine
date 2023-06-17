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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_PATTERN_CUSTOM_PAINT_COMMON_CONSTANTS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_PATTERN_CUSTOM_PAINT_COMMON_CONSTANTS_H

#include <string>
#include <vector>

#include "base/geometry/ng/size_t.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/paint_state.h"
#include "core/components/common/layout/constants.h"
#include "third_party/skia/include/core/SkPath.h"

namespace OHOS::Ace::NG {
extern const float IDEAL_WIDTH;
extern const float IDEAL_HEIGHT;
extern const SizeF IDEAL_SIZE;

extern const float MAX_WIDTH;
extern const float MAX_HEIGHT;
extern const SizeF MAX_SIZE;

extern const float MIN_WIDTH;
extern const float MIN_HEIGHT;
extern const SizeF MIN_SIZE;

extern const int32_t CANVAS_WIDTH;
extern const int32_t CANVAS_HEIGHT;
extern const int32_t DEFAULT_INSTANCE_ID;
extern const int32_t DEFAULT_INSTANCE_ID1;
extern const int32_t DEFAULT_INSTANCE_ID2;
extern const int32_t IMAGEDATA_WIDTH;
extern const int32_t IMAGEDATA_HEIGHT;
extern const int32_t BLENDMODE_VALUE_BEGIN;
extern const int32_t BLENDMODE_VALUE_END;

extern const double DEFAULT_DOUBLE0;
extern const double DEFAULT_DOUBLE1;
extern const double DEFAULT_DOUBLE2;
extern const double DEFAULT_DOUBLE10;
extern const double HALF_CIRCLE_ANGLE;
extern const double FULL_CIRCLE_ANGLE;
extern const double SPECIAL_CIRCLE_ANGLE;
extern const double SPECIAL2_CIRCLE_ANGLE;

extern const std::string URL_PREFIX;
extern const std::string IMAGE_PNG;
extern const std::string IMAGE_JPEG;
extern const std::string IMAGE_WEBP;
extern const std::string QUALITY_0;
extern const std::string QUALITY_50;
extern const std::string QUALITY_100;

extern const std::string NULL_STR;
extern const std::string DEFAULT_STR;
extern const std::string IMAGE_SRC;
extern const std::string REPETITION_STR;
extern const std::vector<std::string> CANDIDATE_STRINGS;
extern const std::vector<std::string> FUNCTION_NAMES;

extern const std::vector<double> CANDIDATE_DOUBLES;

extern const std::vector<Color> CANDIDATE_COLORS;

extern const std::vector<CompositeOperation> CANDIDATE_COMPOSITE_OPERATIONS;

extern const std::vector<TextAlign> CANDIDATE_TEXT_ALIGNS;

extern const std::vector<TextBaseline> CANDIDATE_TEXT_BASELINES;

extern const std::vector<Dimension> CANDIDATE_DIMENSIONS;

extern const std::vector<FontStyle> CANDIDATE_FONT_STYLES;

extern const std::vector<FontWeight> CANDIDATE_FONT_WEIGHTS;

extern const std::vector<std::string> FONT_FAMILY;

extern const std::vector<LineCapStyle> CANDIDATE_LINE_CAP_STYLES;

extern const std::vector<LineJoinStyle> CANDIDATE_LINE_JOIN_STYLES;

extern const std::vector<CanvasFillRule> CANDIDATE_CANVAS_FILL_RULES;

#ifndef NEW_SKIA
extern const std::vector<SkPath::FillType> CANDIDATE_SKPATH_FILL_TYPES;
#else
extern const std::vector<SkPathFillType> CANDIDATE_SKPATH_FILL_TYPES;
#endif
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_PATTERN_CUSTOM_PAINT_COMMON_CONSTANTS_H
