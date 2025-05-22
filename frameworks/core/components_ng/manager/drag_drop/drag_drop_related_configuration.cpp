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

#include "core/components_ng/manager/drag_drop/drag_drop_related_configuration.h"
#include "ui/base/utils/utils.h"

namespace OHOS::Ace::NG {

RefPtr<DragSpringLoadingConfiguration> DragDropRelatedConfigurations::GetOrCreateDragSpringLoadingConfiguration()
{
    if (dragSpringLoadingConfiguration_) {
        return dragSpringLoadingConfiguration_;
    }
    dragSpringLoadingConfiguration_ = MakeRefPtr<DragSpringLoadingConfiguration>();
    return dragSpringLoadingConfiguration_;
}

void DragDropRelatedConfigurations::SetDragSpringLoadingConfiguration(
    const RefPtr<DragSpringLoadingConfiguration>& dragSpringLoadingConfiguration)
{
    CHECK_NULL_VOID(dragSpringLoadingConfiguration);
    dragSpringLoadingConfiguration_ = std::move(dragSpringLoadingConfiguration);
}
} // namespace OHOS::Ace::NG