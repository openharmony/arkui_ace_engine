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
#include "core/interfaces/native/implementation/file_selector_param_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"


namespace OHOS::Ace::NG::GeneratedModifier {
namespace FileSelectorParamAccessor {
void DestroyPeerImpl(Ark_FileSelectorParam peer)
{
    delete peer;
}
Ark_FileSelectorParam ConstructImpl()
{
    return new FileSelectorParamPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_String GetTitleImpl(Ark_FileSelectorParam peer)
{
    std::string result = "";
    CHECK_NULL_RETURN(peer && peer->handler, Converter::ArkValue<Ark_String>(result, Converter::FC));
    result = peer->handler->GetTitle();
    return Converter::ArkValue<Ark_String>(result, Converter::FC);
}
Ark_FileSelectorMode GetModeImpl(Ark_FileSelectorParam peer)
{
    CHECK_NULL_RETURN(peer && peer->handler, {});
    return static_cast<Ark_FileSelectorMode>(peer->handler->GetMode());
}
Array_String GetAcceptTypeImpl(Ark_FileSelectorParam peer)
{
    CHECK_NULL_RETURN(peer && peer->handler, {});
    auto acceptType = peer->handler->GetAcceptType();
    return Converter::ArkValue<Array_String>(acceptType, Converter::FC);
}
Ark_Boolean IsCaptureImpl(Ark_FileSelectorParam peer)
{
    CHECK_NULL_RETURN(peer && peer->handler, false);
    return Converter::ArkValue<Ark_Boolean>(peer->handler->IsCapture());
}
Array_String GetMimeTypesImpl(Ark_FileSelectorParam peer)
{
    CHECK_NULL_RETURN(peer && peer->handler, {});
    auto mimeTypes = peer->handler->GetMimeType();
    return Converter::ArkValue<Array_String>(mimeTypes, Converter::FC);
}
Ark_String GetSuggestedNameImpl(Ark_FileSelectorParam peer)
{
    std::string result = "";
    CHECK_NULL_RETURN(peer && peer->handler, Converter::ArkValue<Ark_String>(result, Converter::FC));
    result = peer->handler->GetDefaultFileName();
    return Converter::ArkValue<Ark_String>(result, Converter::FC);
}
Ark_String GetDefaultPathImpl(Ark_FileSelectorParam peer)
{
    std::string result = "";
    CHECK_NULL_RETURN(peer && peer->handler, Converter::ArkValue<Ark_String>(result, Converter::FC));
    result = peer->handler->GetDefaultPath();
    return Converter::ArkValue<Ark_String>(result, Converter::FC);
}
Array_String GetDescriptionsImpl(Ark_FileSelectorParam peer)
{
    CHECK_NULL_RETURN(peer && peer->handler, {});
    auto descriptions = peer->handler->GetDescriptions();
    return Converter::ArkValue<Array_String>(descriptions, Converter::FC);
}
Ark_Boolean IsAcceptAllOptionExcludedImpl(Ark_FileSelectorParam peer)
{
    CHECK_NULL_RETURN(peer && peer->handler, false);
    return Converter::ArkValue<Ark_Boolean>(peer->handler->IsAcceptAllOptionExcluded());
}
Array_Array_AcceptableFileType GetAcceptableFileTypesImpl(Ark_FileSelectorParam peer)
{
    CHECK_NULL_RETURN(peer && peer->handler, {});
    using AcceptableFileType = OHOS::Ace::AcceptFileType;
    using TypeList = std::vector<AcceptableFileType>;
    using TypeLists = std::vector<TypeList>;
    auto accepts = peer->handler->GetAccepts();
    auto ctx = Converter::FC;
    auto convertType = [ctx](const AcceptableFileType& t) -> Ark_AcceptableFileType {
        return {
            .mimeType = Converter::ArkValue<Ark_String>(t.mimeType, ctx),
            .acceptableType = Converter::ArkValue<Array_String>(t.acceptType, ctx),
        };
    };
    auto convertTypeList = [&convertType](const TypeList& src) {
        std::vector<Ark_AcceptableFileType> arkTypeList(src.size());
        std::transform(src.begin(), src.end(), arkTypeList.begin(), [&convertType](const AcceptableFileType& src) {
            return convertType(src);
        });
        return arkTypeList;
    };
    auto convertTypeLists = [&convertTypeList](const TypeLists& src) {
        std::vector<std::vector<Ark_AcceptableFileType>> arkTypeLists(src.size());
        std::transform(src.begin(), src.end(), arkTypeLists.begin(), [&convertTypeList](const TypeList& src) {
            return convertTypeList(src);
        });
        return arkTypeLists;
    };
    auto acceptableFileTypes = convertTypeLists(accepts);
    return Converter::ArkValue<Array_Array_AcceptableFileType>(acceptableFileTypes, Converter::FC);
}
} // FileSelectorParamAccessor
const GENERATED_ArkUIFileSelectorParamAccessor* GetFileSelectorParamAccessor()
{
    static const GENERATED_ArkUIFileSelectorParamAccessor FileSelectorParamAccessorImpl {
        FileSelectorParamAccessor::DestroyPeerImpl,
        FileSelectorParamAccessor::ConstructImpl,
        FileSelectorParamAccessor::GetFinalizerImpl,
        FileSelectorParamAccessor::GetTitleImpl,
        FileSelectorParamAccessor::GetModeImpl,
        FileSelectorParamAccessor::GetAcceptTypeImpl,
        FileSelectorParamAccessor::IsCaptureImpl,
        FileSelectorParamAccessor::GetMimeTypesImpl,
        FileSelectorParamAccessor::GetSuggestedNameImpl,
        FileSelectorParamAccessor::GetDefaultPathImpl,
        FileSelectorParamAccessor::GetDescriptionsImpl,
        FileSelectorParamAccessor::IsAcceptAllOptionExcludedImpl,
        FileSelectorParamAccessor::GetAcceptableFileTypesImpl,
    };
    return &FileSelectorParamAccessorImpl;
}

}
