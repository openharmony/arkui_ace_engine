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
#include "core/interfaces/native/node/swiper_controller_modifier.h"

#include "core/components_ng/pattern/swiper/swiper_model_ng.h"

namespace OHOS::Ace::NG {

ArkUINodeHandle GetSwiperController(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto controller = SwiperModelNG::GetOrCreateSwiperController(frameNode);
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(controller));
}

void ShowNext(ArkUINodeHandle controller)
{
    CHECK_NULL_VOID(controller);
    auto* swiperController = reinterpret_cast<SwiperController*>(controller);
    swiperController->ShowNext();
}

void ShowPrevious(ArkUINodeHandle controller)
{
    CHECK_NULL_VOID(controller);
    auto* swiperController = reinterpret_cast<SwiperController*>(controller);
    swiperController->ShowPrevious();
}

namespace NodeModifier {
const ArkUISwiperControllerModifier* GetSwiperControllerModifier()
{
    constexpr auto lineBegin = __LINE__; // don't move this line
    static const ArkUISwiperControllerModifier modifier = {
        .getSwiperController = GetSwiperController,
        .showNext = ShowNext,
        .showPrevious = ShowPrevious,
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

const CJUISwiperControllerModifier* GetCJUISwiperControllerModifier()
{
    constexpr auto lineBegin = __LINE__; // don't move this line
    static const CJUISwiperControllerModifier modifier = {
        .getSwiperController = GetSwiperController,
        .showNext = ShowNext,
        .showPrevious = ShowPrevious,
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
