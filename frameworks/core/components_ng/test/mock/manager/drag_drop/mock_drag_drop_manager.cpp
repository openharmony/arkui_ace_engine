/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#include "gtest/gtest.h"

#include "core/components_ng/manager/drag_drop/drag_drop_manager.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t CURRENT_ID = 1;
} // namespace

void DragDropManager::onDragCancel() {}

bool DragDropManager::CheckDragDropProxy(int64_t id) const
{
    return CURRENT_ID == 1;
}
} // namespace OHOS::Ace::NG
