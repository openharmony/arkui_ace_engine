/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "base/log/log_wrapper.h"
#include "core/common/dynamic_module_helper.h"
#include "base/subwindow/subwindow_manager.h"
#include "bridge/common/utils/engine_helper.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"
#include "ui/base/utils/utils.h"

namespace OHOS::Ace::NG::GeneratedModifier {
const GENERATED_ArkUIContextMenuAccessor* GetContextMenuAccessor()
{
    static const GENERATED_ArkUIContextMenuAccessor* accessor = nullptr;
    if (accessor == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Menu");
        if (module == nullptr) {
            LOGF("Can't find ContextMenuAccessor dynamic module");
            abort();
        }
        accessor = reinterpret_cast<const GENERATED_ArkUIContextMenuAccessor*>(
            module->GetCustomModifier("contextMenuAccessor"));
    }
    return accessor;
}

}
