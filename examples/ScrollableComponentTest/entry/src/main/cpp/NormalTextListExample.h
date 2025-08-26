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

#include "ArkUIBaseNode.h"
#include "ArkUIListItemNode.h"
#include "ArkUIListNode.h"
#include "ArkUITextNode.h"
#include <cstdint>

namespace NativeModule {

std::shared_ptr<ArkUIBaseNode> CreateTextListExample()
{
    static const int32_t itemCount = 30;
    static const float itemFontSize = 16;
    static const float itemWidth = 300;
    static const float itemHeight = 100;
    // 创建组件并挂载
    // 1：使用智能指针创建List组件。
    auto list = std::make_shared<ArkUIListNode>();
    list->SetPercentWidth(1);
    list->SetPercentHeight(1);
    list->SetScrollBarState(true);
    // 2：创建ListItem子组件并挂载到List上。
    for (int32_t i = 0; i < itemCount; ++i) {
        auto listItem = std::make_shared<ArkUIListItemNode>();
        auto textNode = std::make_shared<ArkUITextNode>();
        textNode->SetTextContent(std::to_string(i));
        textNode->SetFontSize(itemFontSize);
        textNode->SetFontColor(0xFFff00ff);
        textNode->SetPercentWidth(1);
        textNode->SetWidth(itemWidth);
        textNode->SetHeight(itemHeight);
        textNode->SetBackgroundColor(0xFFfffacd);
        textNode->SetTextAlign(ARKUI_TEXT_ALIGNMENT_CENTER);
        listItem->InsertChild(textNode, i);
        list->AddChild(listItem);
    }
    return list;
}
} // namespace NativeModule

#endif // SCROLLABLE_COMPONENT_NORMALTEXTLISTEXAMPLE_H