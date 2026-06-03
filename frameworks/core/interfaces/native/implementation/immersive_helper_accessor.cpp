/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"
#include "interfaces/inner_api/ace_kit/include/ui/properties/ui_material.h"
#include "interfaces/inner_api/ace_kit/include/ui/base/referenced.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ImmersiveHelperAccessor {
Ark_Int64 ImmersiveConstructImpl(const Opt_ImmersiveOptionsInner* options)
{
    std::optional<ImmersiveOptions> immersiveOptions = Converter::OptConvertPtr<ImmersiveOptions>(options);

    auto material = AceType::MakeRefPtr<UiMaterial>();
    material->SetType(static_cast<int32_t>(MaterialType::IMMERSIVE));
    material->IncRefCount();
    if (immersiveOptions.has_value()) {
        material->SetImmersiveOptions(immersiveOptions.value());
    } else {
        material->SetImmersiveOptions(ImmersiveOptions());
    }
    return Converter::ArkValue<Ark_Int64>(reinterpret_cast<int64_t>(AceType::RawPtr(material)));
}
} // ImmersiveHelperAccessor
const GENERATED_ArkUIImmersiveHelperAccessor* GetImmersiveHelperAccessor()
{
    static const GENERATED_ArkUIImmersiveHelperAccessor ImmersiveHelperAccessorImpl {
        ImmersiveHelperAccessor::ImmersiveConstructImpl,
    };
    return &ImmersiveHelperAccessorImpl;
}

}
