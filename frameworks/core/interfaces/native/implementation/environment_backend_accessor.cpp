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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace EnvironmentBackendAccessor {
Ark_Boolean IsAccessibilityEnabledImpl()
{
    return {};
}
Ark_Int32 GetColorModeImpl()
{
    return {};
}
Ark_Float32 GetFontScaleImpl()
{
    return {};
}
Ark_Float32 GetFontWeightScaleImpl()
{
    return {};
}
Ark_String GetLayoutDirectionImpl()
{
    return {};
}
Ark_String GetLanguageCodeImpl()
{
    return {};
}
} // EnvironmentBackendAccessor
const GENERATED_ArkUIEnvironmentBackendAccessor* GetEnvironmentBackendAccessor()
{
    static const GENERATED_ArkUIEnvironmentBackendAccessor EnvironmentBackendAccessorImpl {
        EnvironmentBackendAccessor::IsAccessibilityEnabledImpl,
        EnvironmentBackendAccessor::GetColorModeImpl,
        EnvironmentBackendAccessor::GetFontScaleImpl,
        EnvironmentBackendAccessor::GetFontWeightScaleImpl,
        EnvironmentBackendAccessor::GetLayoutDirectionImpl,
        EnvironmentBackendAccessor::GetLanguageCodeImpl,
    };
    return &EnvironmentBackendAccessorImpl;
}

}
