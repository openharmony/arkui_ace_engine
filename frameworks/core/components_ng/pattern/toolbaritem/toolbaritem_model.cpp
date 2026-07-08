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

#include "core/components_ng/pattern/toolbaritem/toolbaritem_model.h"

#include "core/common/container.h"
#include "core/components_ng/pattern/toolbaritem/toolbaritem_model_ng.h"

namespace OHOS::Ace {

ToolBarItemModel* ToolBarItemModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::ToolBarItemModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::ToolBarItemModelNG instance;
        return &instance;
    } else {
        static NG::ToolBarItemModelNG instance;
        return &instance;
    }
#endif
}

void ToolBarItemModel::Create(int32_t value) {}

void ToolBarItemModel::SetIsFirstCreate(bool value) {}

} // namespace OHOS::Ace
