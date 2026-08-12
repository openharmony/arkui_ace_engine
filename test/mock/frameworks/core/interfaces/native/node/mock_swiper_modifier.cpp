/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/interfaces/native/node/node_swiper_modifier.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/components_ng/pattern/swiper/swiper_model_ng.h"

namespace OHOS::Ace::NG {
ArkUINodeHandle CreateSwiperFrameNode(ArkUI_Int32 nodeId)
{
    auto frameNode = SwiperModelNG::CreateFrameNode(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}

ArkUINodeHandle GetSwiperController(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto controller = SwiperModelNG::GetOrCreateSwiperController(frameNode);
    CHECK_NULL_RETURN(controller, nullptr);
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(controller));
}
namespace NodeModifier {
const ArkUISwiperCustomModifier* GetSwiperCustomModifier()
{
    static const ArkUISwiperCustomModifier modifier = {
        .createFrameNode = CreateSwiperFrameNode,
        .getSwiperController = GetSwiperController,
    };
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG

namespace {
void MockSetSwiperFinishAnimation(ArkUINodeHandle node)
{
}

void MockCallSwiperShowPrevious(ArkUINodeHandle node)
{
}

void MockCallSwiperShowNext(ArkUINodeHandle node)
{
}

ArkUI_Int32 MockGetSwiperCurrentIndex(ArkUINodeHandle node, ArkUI_Bool original)
{
    return 0;
}
} // namespace

const ArkUISwiperModifier* GetMockSwiperModifier()
{
    static ArkUISwiperModifier modifier = {};
    modifier.setSwiperFinishAnimation = MockSetSwiperFinishAnimation;
    modifier.getSwiperCurrentIndex = MockGetSwiperCurrentIndex;
    modifier.callSwiperShowPrevious = MockCallSwiperShowPrevious;
    modifier.callSwiperShowNext = MockCallSwiperShowNext;
    return &modifier;
}
