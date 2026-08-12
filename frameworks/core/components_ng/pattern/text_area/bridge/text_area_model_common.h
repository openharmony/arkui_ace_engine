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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_AREA_BRIDGE_TEXT_AREA_MODEL_COMMON_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_AREA_BRIDGE_TEXT_AREA_MODEL_COMMON_H

#include "core/common/dynamic_module_helper.h"

namespace OHOS::Ace::NG {
namespace {

#ifndef CROSS_PLATFORM
TextFieldModel* GetTextFieldModelImpl()
{
    static auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("textarea");
    if (loader == nullptr) {
        LOGF_ABORT("Can't find textarea loader");
    }
    static TextFieldModel* instance = reinterpret_cast<TextFieldModel*>(loader->CreateModel());
    if (instance == nullptr) {
        LOGF_ABORT("textarea loader CreateModel fail");
    }
    return instance;
}
#endif

} //namespace
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_AREA_BRIDGE_TEXT_AREA_MODEL_COMMON_H
