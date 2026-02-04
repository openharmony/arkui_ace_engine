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
 
#include "arkoala_api_generated.h"
#include "sheet_dismiss_peer.h"

#include "core/components_ng/base/view_abstract_model_static.h"
#include "core/interfaces/native/utility/converter.h"

SheetDismissPeer g_sheetDismissPeer = {};

namespace OHOS::Ace::NG::GeneratedModifier {
namespace SheetDismissAccessor {
void DestroyPeerImpl([[maybe_unused]] Ark_SheetDismiss peer)
{}

Ark_SheetDismiss ConstructImpl()
{
    return &g_sheetDismissPeer;
}

Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}

void SheetDismissImpl([[maybe_unused]] Ark_SheetDismiss peer)
{
    ViewAbstractModelStatic::DismissSheetStatic();
}
} // namespace SheetDismissAccessor

const GENERATED_ArkUISheetDismissAccessor* GetSheetDismissAccessor()
{
    static const GENERATED_ArkUISheetDismissAccessor SheetDismissAccessorImpl {
        SheetDismissAccessor::DestroyPeerImpl,
        SheetDismissAccessor::ConstructImpl,
        SheetDismissAccessor::GetFinalizerImpl,
        SheetDismissAccessor::SheetDismissImpl,
    };
    return &SheetDismissAccessorImpl;
}

struct SheetDismissPeer {
    virtual ~SheetDismissPeer() = default;
};
}