/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
namespace WaterFlowSectionsAccessor {
WaterFlowSectionsPeer* CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return 0;
}
Ark_Boolean SpliceImpl(WaterFlowSectionsPeer* peer,
                       const Ark_Number* start,
                       const Opt_Number* deleteCount,
                       const Opt_Array_SectionOptions* sections)
{
    return 0;
}
Ark_Boolean PushImpl(WaterFlowSectionsPeer* peer,
                     const Ark_SectionOptions* section)
{
    return 0;
}
Ark_Boolean UpdateImpl(WaterFlowSectionsPeer* peer,
                       const Ark_Number* sectionIndex,
                       const Ark_SectionOptions* section)
{
    return 0;
}
void ValuesImpl(WaterFlowSectionsPeer* peer)
{
}
Ark_Int32 LengthImpl(WaterFlowSectionsPeer* peer)
{
    return 0;
}
} // WaterFlowSectionsAccessor
const GENERATED_ArkUIWaterFlowSectionsAccessor* GetWaterFlowSectionsAccessor()
{
    static const GENERATED_ArkUIWaterFlowSectionsAccessor WaterFlowSectionsAccessorImpl {
        WaterFlowSectionsAccessor::CtorImpl,
        WaterFlowSectionsAccessor::GetFinalizerImpl,
        WaterFlowSectionsAccessor::SpliceImpl,
        WaterFlowSectionsAccessor::PushImpl,
        WaterFlowSectionsAccessor::UpdateImpl,
        WaterFlowSectionsAccessor::ValuesImpl,
        WaterFlowSectionsAccessor::LengthImpl,
    };
    return &WaterFlowSectionsAccessorImpl;
}

}
