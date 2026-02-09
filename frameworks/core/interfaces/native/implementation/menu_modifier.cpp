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
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/menu/menu_model_static.h"
#include "core/components_ng/property/border_property.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"
#include "core/interfaces/native/implementation/symbol_glyph_modifier_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "ui/base/utils/utils.h"

namespace OHOS::Ace::NG::GeneratedModifier {
#ifdef ACE_UNITTEST
const GENERATED_ArkUIMenuModifier* GetMenuStaticModifier();
#endif

const GENERATED_ArkUIMenuModifier* GetMenuModifier()
{
#ifdef ACE_UNITTEST
    return GetMenuStaticModifier();
#else
    static const GENERATED_ArkUIMenuModifier* modifier = nullptr;
    if (modifier == nullptr) {
        auto module = DynamicModuleHelper::GetInstance().GetDynamicModule("Menu");
        if (module == nullptr) {
            LOGF("Can't find Menu dynamic module");
            abort();
        }
        modifier = reinterpret_cast<const GENERATED_ArkUIMenuModifier*>(module->GetStaticModifier());
    }
    return modifier;
#endif
}
} // namespace OHOS::Ace::NG::GeneratedModifier
