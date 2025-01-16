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
#include "core/interfaces/native/node/rating_modifier.h"
#include "core/components_ng/pattern/rating/rating_model_ng.h"

namespace OHOS::Ace::NG {
constexpr int32_t STARS_DEFAULT = 5;
constexpr double STEPS_DEFAULT = 0.5;
void SetStars(ArkUINodeHandle node, int32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RatingModelNG::SetStars(frameNode, value);
}

void SetRatingStepSize(ArkUINodeHandle node, ArkUI_Float32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RatingModelNG::SetStepSize(frameNode, value);
}
void SetStarStyle(ArkUINodeHandle node,
    const char* backgroundUri, const char* foregroundUri, const char* secondaryUri)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string backgroundUriStr = backgroundUri;
    if (backgroundUriStr.empty()) {
        RatingModelNG::SetBackgroundSrc(frameNode, "", true);
    } else {
        RatingModelNG::SetBackgroundSrc(frameNode, backgroundUriStr, false);
    }

    std::string foregroundUriStr = foregroundUri;
    if (foregroundUriStr.empty()) {
        RatingModelNG::SetForegroundSrc(frameNode, "", true);
    } else {
        RatingModelNG::SetForegroundSrc(frameNode, foregroundUriStr, false);
    }

    std::string secondaryUriStr = secondaryUri;
    if (!secondaryUriStr.empty()) {
        RatingModelNG::SetSecondarySrc(frameNode, secondaryUriStr, false);
    } else if (!backgroundUriStr.empty()) {
        RatingModelNG::SetSecondarySrc(frameNode, backgroundUriStr, false);
    } else {
        RatingModelNG::SetSecondarySrc(frameNode, "", true);
    }
}

void ResetStars(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RatingModelNG::SetStars(frameNode, STARS_DEFAULT);
}

void ResetRatingStepSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RatingModelNG::SetStepSize(frameNode, STEPS_DEFAULT);
}

void ResetStarStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RatingModelNG::SetBackgroundSrc(frameNode, "", true);
    RatingModelNG::SetForegroundSrc(frameNode, "", true);
    RatingModelNG::SetSecondarySrc(frameNode, "", true);
}

void SetRatingOptions(ArkUINodeHandle node, ArkUI_Float64 rating, ArkUI_Bool indicator)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RatingModelNG::SetRatingOptions(frameNode, rating, static_cast<bool>(indicator));
}

namespace NodeModifier {
const ArkUIRatingModifier* GetRatingModifier()
{
    constexpr auto lineBegin = __LINE__; // don't move this line
    static const ArkUIRatingModifier modifier = {
        .setStars = SetStars,
        .setRatingStepSize = SetRatingStepSize,
        .setStarStyle = SetStarStyle,
        .resetStars = ResetStars,
        .resetRatingStepSize = ResetRatingStepSize,
        .resetStarStyle = ResetStarStyle,
        .setRatingOptions = SetRatingOptions,
    };
    constexpr auto lineEnd = __LINE__; // don't move this line
    constexpr auto ifdefOverhead = 4; // don't modify this line
    constexpr auto overHeadLines = 3; // don't modify this line
    constexpr auto blankLines = 0; // modify this line accordingly
    constexpr auto ifdefs = 0; // modify this line accordingly
    constexpr auto initializedFieldLines = lineEnd - lineBegin - ifdefs * ifdefOverhead - overHeadLines - blankLines;
    static_assert(initializedFieldLines == sizeof(modifier) / sizeof(void*),
        "ensure all fields are explicitly initialized");
    return &modifier;
}

const CJUIRatingModifier* GetCJUIRatingModifier()
{
    constexpr auto lineBegin = __LINE__; // don't move this line
    static const CJUIRatingModifier modifier = {
        .setStars = SetStars,
        .setRatingStepSize = SetRatingStepSize,
        .setStarStyle = SetStarStyle,
        .resetStars = ResetStars,
        .resetRatingStepSize = ResetRatingStepSize,
        .resetStarStyle = ResetStarStyle,
    };
    constexpr auto lineEnd = __LINE__; // don't move this line
    constexpr auto ifdefOverhead = 4; // don't modify this line
    constexpr auto overHeadLines = 3; // don't modify this line
    constexpr auto blankLines = 0; // modify this line accordingly
    constexpr auto ifdefs = 0; // modify this line accordingly
    constexpr auto initializedFieldLines = lineEnd - lineBegin - ifdefs * ifdefOverhead - overHeadLines - blankLines;
    static_assert(initializedFieldLines == sizeof(modifier) / sizeof(void*),
        "ensure all fields are explicitly initialized");
    return &modifier;
}
}
}
