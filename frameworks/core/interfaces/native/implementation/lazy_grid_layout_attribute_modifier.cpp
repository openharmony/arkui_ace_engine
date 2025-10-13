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

#include "arkoala_api_generated.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_model_static.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/validators.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace LazyGridLayoutAttributeModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = LazyGridLayoutModelStatic::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
void SetRowsGapImpl(Ark_NativePointer node,
                    const Opt_LengthMetrics* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue =  Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(convValue);
    LazyGridLayoutModelStatic::SetRowGap(frameNode, convValue);
}
void SetColumnsGapImpl(Ark_NativePointer node,
                       const Opt_LengthMetrics* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue =  Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(convValue);
    LazyGridLayoutModelStatic::SetColumnGap(frameNode, convValue);
}
} // LazyGridLayoutAttributeModifier
const GENERATED_ArkUILazyGridLayoutAttributeModifier* GetLazyGridLayoutAttributeModifier()
{
    static const GENERATED_ArkUILazyGridLayoutAttributeModifier ArkUILazyGridLayoutAttributeModifierImpl {
        LazyGridLayoutAttributeModifier::ConstructImpl,
        LazyGridLayoutAttributeModifier::SetRowsGapImpl,
        LazyGridLayoutAttributeModifier::SetColumnsGapImpl,
    };
    return &ArkUILazyGridLayoutAttributeModifierImpl;
}

}
