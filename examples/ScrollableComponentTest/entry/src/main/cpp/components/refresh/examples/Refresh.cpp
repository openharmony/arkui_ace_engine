/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "components/refresh/Refresh1.h"

#include <cstdint>

namespace ArkUICApiDemo {

void RefreshComponent::SetPullToRefresh(int32_t pullToRefresh)
{
    ArkUI_NumberValue value[] = { { .i32 = pullToRefresh } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_REFRESH_PULL_TO_REFRESH, &item);
}
void RefreshComponent::SetPullDownRatio(float pullDownRatio)
{
    ArkUI_NumberValue value[] = { { .f32 = pullDownRatio } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_REFRESH_PULL_DOWN_RATIO, &item);
}
void RefreshComponent::SetRefreshOffset(float refreshOffset)
{
    ArkUI_NumberValue value[] = { { .f32 = refreshOffset } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_REFRESH_OFFSET, &item);
}
void RefreshComponent::SetRefreshing(bool refreshing)
{
    ArkUI_NumberValue value[] = { { .i32 = refreshing } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_REFRESH_REFRESHING, &item);
}
void RefreshComponent::SetRefreshContent(ArkUI_NodeHandle& node)
{
    ArkUI_AttributeItem item { .object = node };
    _nodeAPI->setAttribute(_component, NODE_REFRESH_CONTENT, &item);
}
} // namespace ArkUICApiDemo
