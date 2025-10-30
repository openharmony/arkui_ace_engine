/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License")
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

#ifndef CAPI0805_2_STACKEXAMPLE_REFACTORED_H
#define CAPI0805_2_STACKEXAMPLE_REFACTORED_H

#include "LayoutConstants.h"
#include "nodes/ArkUIBaseNode.h"
#include "nodes/ArkUIColumnNode.h"
#include "nodes/ArkUITextNode.h"
#include "nodes/ArkUIStackNode.h"
#include <vector>

namespace NativeModule {

using namespace LayoutConstants;

std::shared_ptr<ArkUIBaseNode> CreateStackExample()
{
    auto column = std::make_shared<ArkUIColumnNode>();
    auto stack = std::make_shared<ArkUIStackNode>();

    std::vector<std::shared_ptr<ArkUITextNode>> text(Counts::TEXT_NODES_SMALL);
    for (int i = 0; i < Counts::TEXT_NODES_SMALL; i++) {
        text[i] = std::make_shared<ArkUITextNode>();
        stack->AddChild(text[i]);
    }

    // 设置第一个文本节点（底部显示）
    text[Indices::ZERO]->SetTextContent(Texts::CONTENT_STACK_FIRST);
    text[Indices::ZERO]->SetPercentWidth(Percentages::NINETY_PERCENT);
    text[Indices::ZERO]->SetPercentHeight(Percentages::FULL_WIDTH);
    text[Indices::ZERO]->SetBackgroundColor(Colors::LIGHT_BROWN);
    text[Indices::ZERO]->SetStackAlignContent(ARKUI_ALIGNMENT_TOP);

    // 设置第二个文本节点（顶部显示）
    text[Indices::ONE]->SetTextContent(Texts::CONTENT_STACK_SECOND);
    text[Indices::ONE]->SetPercentWidth(Percentages::SEVENTY_PERCENT);
    text[Indices::ONE]->SetPercentHeight(Percentages::SIXTY_PERCENT);
    text[Indices::ONE]->SetBackgroundColor(Colors::SAGE_GREEN);
    text[Indices::ONE]->SetAlignment(ARKUI_ALIGNMENT_TOP);

    column->AddChild(stack);
    return column;
}

} // namespace NativeModule
#endif // CAPI0805_2_STACKEXAMPLE_REFACTORED_H