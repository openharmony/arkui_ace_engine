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
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "water_flow_sections_accessor_peer_impl.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::Converter {
    template<>
WaterFlowSections::Section Convert(const Ark_SectionOptions& src)
{
    WaterFlowSections::Section dst;
    dst.itemsCount = Converter::Convert<int32_t>(src.itemsCount);
    dst.crossCount = Converter::OptConvert<int32_t>(src.crossCount);
    dst.onGetItemMainSizeByIndex = nullptr;
    auto onGetItemMainSizeByIndex = Converter::OptConvert<::GetItemMainSizeByIndex>(src.onGetItemMainSizeByIndex);
    if (onGetItemMainSizeByIndex) {
        auto modelCallback = [callback = CallbackHelper(*onGetItemMainSizeByIndex)]
            (int32_t value) -> float {
                Ark_Int32 param = Converter::ArkValue<Ark_Int32>(value);
                auto resultOpt = callback.InvokeWithOptConvertResult<float, Ark_Float64, Callback_F64_Void>(param);
                return resultOpt.value_or(0);
            };
        dst.onGetItemMainSizeByIndex = modelCallback;
    }
    dst.columnsGap = Converter::OptConvert<Dimension>(src.columnsGap);
    dst.rowsGap = Converter::OptConvert<Dimension>(src.rowsGap);
    dst.margin = Converter::OptConvert<MarginProperty>(src.margin);
    return dst;
}

template<>
std::vector<WaterFlowSections::Section> Convert(const Array_SectionOptions& src)
{
    std::vector<WaterFlowSections::Section> dst;
    auto length = Converter::Convert<int>(src.length);
    for (int i = 0; i < length; i++) {
        WaterFlowSections::Section newSession = Converter::Convert<WaterFlowSections::Section>(src.array[i]);
        dst.push_back(newSession);
    }
    return dst;
}
void AssignArkValue(Ark_SectionOptions& dst, const WaterFlowSections::Section& src, ConvContext *ctx)
{
    dst.itemsCount = Converter::ArkValue<Ark_Int32>(src.itemsCount);
    dst.crossCount = Converter::ArkValue<Opt_Int32>(src.crossCount);
    auto cb = [src](const Ark_Int32 index, const Callback_F64_Void continuation) {
        auto result = src.onGetItemMainSizeByIndex(Converter::Convert<int32_t>(index));
        auto helper = CallbackHelper(continuation);
        helper.Invoke(Converter::ArkValue<Ark_Float64>(result));
    };
    auto rc = CallbackKeeper::RegisterReverseCallback<::GetItemMainSizeByIndex,
                                                   std::function<void(Ark_Int32, Callback_F64_Void)>>(cb);
    dst.onGetItemMainSizeByIndex = Converter::ArkValue<Opt_GetItemMainSizeByIndex>(rc);
    dst.columnsGap = Converter::ArkValue<Opt_Dimension>(src.columnsGap, ctx);
    dst.rowsGap = Converter::ArkValue<Opt_Dimension>(src.rowsGap, ctx);
    dst.margin = Converter::ArkUnion<Opt_Union_Margin_Dimension, Ark_Padding>(src.margin, ctx);
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace WaterFlowSectionsAccessor {
void DestroyPeerImpl(Ark_WaterFlowSections peer)
{
    delete peer;
}
Ark_WaterFlowSections ConstructImpl()
{
    return new WaterFlowSectionsPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Boolean SpliceImpl(Ark_WaterFlowSections peer,
                       Ark_Int32 start,
                       const Opt_Int32* deleteCount,
                       const Opt_Array_SectionOptions* sections)
{
    CHECK_NULL_RETURN(peer, false);
    CHECK_NULL_RETURN(peer->GetController(), false);
    CHECK_NULL_RETURN(start, false);
    auto deleteCountOpt = Converter::OptConvertPtr<int32_t>(deleteCount);
    auto delCnt = deleteCountOpt ? deleteCountOpt.value() : 0;
    auto sectionsOpt = Converter::OptConvertPtr<Array_SectionOptions>(sections);
    if (sectionsOpt) {
        auto sections = Converter::OptConvert<std::vector<WaterFlowSections::Section>>(*sectionsOpt);
        peer->GetController()->ChangeData(Converter::Convert<int32_t>(start), delCnt, sections.value());
        return true;
    } else {
        return false;
    }
}
Ark_Boolean PushImpl(Ark_WaterFlowSections peer,
                     const Ark_SectionOptions* section)
{
    CHECK_NULL_RETURN(peer, false);
    CHECK_NULL_RETURN(peer->GetController(), false);
    auto start = peer->GetController()->GetSectionInfo().size();
    std::vector<WaterFlowSections::Section> sections;
    auto newSection = Converter::OptConvert<WaterFlowSections::Section>(*section);
    sections.push_back(newSection.value());
    peer->GetController()->ChangeData(start, 0, sections);
    return true;
}
Ark_Boolean UpdateImpl(Ark_WaterFlowSections peer,
                       Ark_Int32 sectionIndex,
                       const Ark_SectionOptions* section)
{
    CHECK_NULL_RETURN(peer, false);
    CHECK_NULL_RETURN(peer->GetController(), false);
    std::vector<WaterFlowSections::Section> sections;
    auto newSection = Converter::OptConvert<WaterFlowSections::Section>(*section);
    sections.push_back(newSection.value());
    peer->GetController()->ChangeData(Converter::Convert<int32_t>(sectionIndex), 0, sections);
    return true;
}
Array_SectionOptions ValuesImpl(Ark_WaterFlowSections peer)
{
    CHECK_NULL_RETURN(peer, {});
    CHECK_NULL_RETURN(peer->GetController(), {});
    auto info = peer->GetController()->GetSectionInfo();
    auto options = Converter::ArkValue<Array_SectionOptions>(info, Converter::FC);
    return options;
}
Ark_Int32 LengthImpl(Ark_WaterFlowSections peer)
{
    const auto errValue = Converter::ArkValue<Ark_Int32>(0);
    CHECK_NULL_RETURN(peer, errValue);
    CHECK_NULL_RETURN(peer->GetController(), errValue);
    auto res = peer->GetController()->GetSectionInfo().size();
    return Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(res));
}
} // WaterFlowSectionsAccessor
const GENERATED_ArkUIWaterFlowSectionsAccessor* GetWaterFlowSectionsAccessor()
{
    static const GENERATED_ArkUIWaterFlowSectionsAccessor WaterFlowSectionsAccessorImpl {
        WaterFlowSectionsAccessor::DestroyPeerImpl,
        WaterFlowSectionsAccessor::ConstructImpl,
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
