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
namespace SectionOptionsAccessor {
void DestroyPeerImpl(Ark_SectionOptions peer)
{
}
Ark_SectionOptions CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Number GetItemsCountImpl(Ark_SectionOptions peer)
{
    return {};
}
void SetItemsCountImpl(Ark_SectionOptions peer,
                       const Ark_Number* itemsCount)
{
}
Opt_Number GetCrossCountImpl(Ark_SectionOptions peer)
{
    return {};
}
void SetCrossCountImpl(Ark_SectionOptions peer,
                       const Opt_Number* crossCount)
{
}
Opt_GetItemMainSizeByIndex GetOnGetItemMainSizeByIndexImpl(Ark_SectionOptions peer)
{
    return {};
}
void SetOnGetItemMainSizeByIndexImpl(Ark_SectionOptions peer,
                                     const Opt_GetItemMainSizeByIndex* onGetItemMainSizeByIndex)
{
}
Opt_Dimension GetColumnsGapImpl(Ark_SectionOptions peer)
{
    return {};
}
void SetColumnsGapImpl(Ark_SectionOptions peer,
                       const Opt_Dimension* columnsGap)
{
}
Opt_Dimension GetRowsGapImpl(Ark_SectionOptions peer)
{
    return {};
}
void SetRowsGapImpl(Ark_SectionOptions peer,
                    const Opt_Dimension* rowsGap)
{
}
Opt_Union_Margin_Dimension GetMarginImpl(Ark_SectionOptions peer)
{
    return {};
}
void SetMarginImpl(Ark_SectionOptions peer,
                   const Opt_Union_Margin_Dimension* margin)
{
}
} // SectionOptionsAccessor
const GENERATED_ArkUISectionOptionsAccessor* GetSectionOptionsAccessor()
{
    static const GENERATED_ArkUISectionOptionsAccessor SectionOptionsAccessorImpl {
        SectionOptionsAccessor::DestroyPeerImpl,
        SectionOptionsAccessor::CtorImpl,
        SectionOptionsAccessor::GetFinalizerImpl,
        SectionOptionsAccessor::GetItemsCountImpl,
        SectionOptionsAccessor::SetItemsCountImpl,
        SectionOptionsAccessor::GetCrossCountImpl,
        SectionOptionsAccessor::SetCrossCountImpl,
        SectionOptionsAccessor::GetOnGetItemMainSizeByIndexImpl,
        SectionOptionsAccessor::SetOnGetItemMainSizeByIndexImpl,
        SectionOptionsAccessor::GetColumnsGapImpl,
        SectionOptionsAccessor::SetColumnsGapImpl,
        SectionOptionsAccessor::GetRowsGapImpl,
        SectionOptionsAccessor::SetRowsGapImpl,
        SectionOptionsAccessor::GetMarginImpl,
        SectionOptionsAccessor::SetMarginImpl,
    };
    return &SectionOptionsAccessorImpl;
}

}
