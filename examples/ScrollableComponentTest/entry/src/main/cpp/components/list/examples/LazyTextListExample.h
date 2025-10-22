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

#ifndef SCROLLABLE_COMPONENT_LAZYTEXTLISTEXAMPLE_H
#define SCROLLABLE_COMPONENT_LAZYTEXTLISTEXAMPLE_H

#include "common/ArkUITextNode.h"
#include "components/list/ListItemGroup.h"
#include "components/list/ListItem.h"
#include "components/list/List.h"
#include <cstdint>

std::shared_ptr<BaseNode> CreateLazyTextListExample()
{
    // 使用智能指针创建List组件。
    auto list = std::make_shared<List>();
    list->SetPercentWidth(1);
    list->SetPercentHeight(1);

    auto adapter = std::make_shared<ArkUINodeAdapter>(100); /* 100: item count */
    list->SetLazyAdapter(adapter);
    return list;
}

#endif // SCROLLABLE_COMPONENT_LAZYTEXTLISTEXAMPLE_H