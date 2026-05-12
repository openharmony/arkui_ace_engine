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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace DragUtilsAccessor {
Ark_Int64 GetForegroundColorValueImpl(const Ark_ResourceColor* resourceColor)
{
    auto errValue = Converter::ArkValue<Ark_Int64>(static_cast<int64_t>(-1));
    CHECK_NULL_RETURN(resourceColor, errValue);
    const auto convColor = Converter::OptConvert<Color>(*resourceColor);
    CHECK_NULL_RETURN(convColor, errValue);
    int64_t value = static_cast<int64_t>(convColor->GetValue());
    return Converter::ArkValue<Ark_Int64>(value);
}
} // DragUtilsAccessor
const GENERATED_ArkUIDragUtilsAccessor* GetDragUtilsAccessor()
{
    static const GENERATED_ArkUIDragUtilsAccessor DragUtilsAccessorImpl {
        DragUtilsAccessor::GetForegroundColorValueImpl,
    };
    return &DragUtilsAccessorImpl;
}
}
