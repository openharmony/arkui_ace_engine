/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

// 自定义入口函数。

#ifndef SCROLLABLE_COMPONENT_NORMALTEXTLISTEXAMPLE_H
#define SCROLLABLE_COMPONENT_NORMALTEXTLISTEXAMPLE_H

#include <memory>
#include <cstdint>

#include "common/ArkUINode.h"
#include "common/ArkUITextNode.h"
#include "components/list/List.h"
#include "components/list/ListItem.h"

constexpr int32_t K_ITEM_COUNT = 30;

inline std::shared_ptr<ArkUITextNode> MakeTextNode(int32_t i, float fontSize, float width, float height)
{
    auto textNode = std::make_shared<ArkUITextNode>();
    textNode->SetTextContent(std::to_string(i));
    textNode->SetFontSize(fontSize);
    textNode->SetFontColor(0xFFff00ff);
    textNode->SetPercentWidth(1.0f);
    textNode->SetWidth(width);
    textNode->SetHeight(height);
    textNode->SetBackgroundColor(0xFFfffacd);
    textNode->SetTextAlign(ARKUI_TEXT_ALIGNMENT_CENTER);
    return textNode;
}

inline std::shared_ptr<BaseNode> CreateTextListExample()
{
    auto list = std::make_shared<List>();
    list->SetPercentWidth(1.0f);
    list->SetPercentHeight(1.0f);
    list->SetScrollBarState(true);
    for (int32_t i = 0; i < K_ITEM_COUNT; ++i) {
        auto item = std::make_shared<ListItem>();
        item->InsertChild(MakeTextNode(i, 16.0f, 300.0f, 100.0f), i);
        list->AddChild(item);
    }
    return list;
}

#endif // SCROLLABLE_COMPONENT_NORMALTEXTLISTEXAMPLE_H