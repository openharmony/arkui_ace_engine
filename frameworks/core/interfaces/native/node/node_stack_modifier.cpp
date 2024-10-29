/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/node_stack_modifier.h"

#include "core/components_ng/pattern/stack/stack_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
Alignment DEFAULT_STACK_ALIGNMENT = Alignment::CENTER;
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr int NUM_6 = 6;
constexpr int NUM_7 = 7;
constexpr int NUM_8 = 8;
constexpr int32_t DEFAULT_ALIGNMENT_INDEX = 4;
void SetAlignContent(ArkUINodeHandle node, ArkUI_Int32 align)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Alignment alignment = Alignment::CENTER;
    switch (align) {
        case NUM_0:
            alignment = Alignment::TOP_LEFT;
            break;
        case NUM_1:
            alignment = Alignment::TOP_CENTER;
            break;
        case NUM_2:
            alignment = Alignment::TOP_RIGHT;
            break;
        case NUM_3:
            alignment = Alignment::CENTER_LEFT;
            break;
        case NUM_4:
            alignment = Alignment::CENTER;
            break;
        case NUM_5:
            alignment = Alignment::CENTER_RIGHT;
            break;
        case NUM_6:
            alignment = Alignment::BOTTOM_LEFT;
            break;
        case NUM_7:
            alignment = Alignment::BOTTOM_CENTER;
            break;
        case NUM_8:
            alignment = Alignment::BOTTOM_RIGHT;
            break;
        default:
            alignment = Alignment::CENTER;
    }
    StackModelNG::SetAlignment(frameNode, alignment);
}

void ResetAlignContent(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    StackModelNG::SetAlignment(frameNode, DEFAULT_STACK_ALIGNMENT);
}

int32_t findAlignmentIndex(Alignment& alignment)
{
    std::vector<Alignment> alignMents = {
        Alignment::TOP_LEFT,
        Alignment::TOP_CENTER,
        Alignment::TOP_RIGHT,
        Alignment::CENTER_LEFT,
        Alignment::CENTER,
        Alignment::CENTER_RIGHT,
        Alignment::BOTTOM_LEFT,
        Alignment::BOTTOM_CENTER,
        Alignment::BOTTOM_RIGHT,
    };
    auto iterator = std::find(alignMents.begin(), alignMents.end(), alignment);
    if (iterator == alignMents.end()) {
        return DEFAULT_ALIGNMENT_INDEX;
    }
    return iterator - alignMents.begin();
}

int32_t GetAlignContent(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, DEFAULT_ALIGNMENT_INDEX);
    auto currentAlignment = StackModelNG::GetAlignment(frameNode);
    return findAlignmentIndex(currentAlignment);
}
} // namespace
namespace NodeModifier {
const ArkUIStackModifier* GetStackModifier()
{
    static const ArkUIStackModifier modifier = { SetAlignContent, ResetAlignContent, GetAlignContent };

    return &modifier;
}

const CJUIStackModifier* GetCJUIStackModifier()
{
    static const CJUIStackModifier modifier = { SetAlignContent, ResetAlignContent, GetAlignContent };

    return &modifier;
}
}
}