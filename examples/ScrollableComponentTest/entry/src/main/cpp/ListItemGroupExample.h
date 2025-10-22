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

#ifndef SCROLLABLE_COMPONENT_LISTITEMGROUPEXAMPLE_H
#define SCROLLABLE_COMPONENT_LISTITEMGROUPEXAMPLE_H

#include "ArkUIBaseNode.h"
#include "ArkUIListItemGroupNode.h"
#include "ArkUIListItemNode.h"
#include "ArkUIListNode.h"
#include "ArkUITextNode.h"
#include <cstdint>

namespace NativeModule {

std::shared_ptr<ArkUIBaseNode> CreateListItemGroupExample()
{
    // 创建组件并挂载
    // 1：使用智能指针创建List组件。
    auto list = std::make_shared<ArkUIListNode>();
    list->SetPercentWidth(1);
    list->SetPercentHeight(1);
    // 设置吸顶
    list->SetSticky(ARKUI_STICKY_STYLE_BOTH);
    // 2：创建ListItem子组件并挂载到List上。
    for (int32_t i = 0; i < 3; ++i) { /* 3: group count */
        auto textNode = std::make_shared<ArkUITextNode>();
        textNode->SetTextContent("header");
        textNode->SetFontSize(16); /* 16: font size */
        textNode->SetPercentWidth(1);
        textNode->SetHeight(50); /* 50: height */
        textNode->SetBackgroundColor(0xFFDCDCDC);
        textNode->SetTextAlign(ARKUI_TEXT_ALIGNMENT_CENTER);
        auto listItemGroup = std::make_shared<ArkUIListItemGroupNode>();
        listItemGroup->SetHeader(textNode);
        auto adapter = std::make_shared<ArkUIListItemAdapter>(4);
        listItemGroup->SetLazyAdapter(adapter);
        list->AddChild(listItemGroup);
    }
    return list;
}
} // namespace NativeModule

#endif // SCROLLABLE_COMPONENT_LAZYTEXTLISTEXAMPLE_H