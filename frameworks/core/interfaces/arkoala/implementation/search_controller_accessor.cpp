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

#include "search_controller_accessor_peer_impl.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::Converter {
template<>
void AssignCast(std::optional<MenuPolicy>& dst, const Ark_MenuPolicy& src)
{
    switch (src) {
        case ARK_MENU_POLICY_DEFAULT: dst = MenuPolicy::DEFAULT; break;
        case ARK_MENU_POLICY_HIDE: dst = MenuPolicy::HIDE; break;
        case ARK_MENU_POLICY_SHOW: dst = MenuPolicy::SHOW; break;
        default:
            LOGE("Unexpected enum value in Ark_MenuPolicy: %{public}d", src);
    }
}

template<>
SelectionOptions Convert(const Ark_SelectionOptions& options)
{
    SelectionOptions selectionOptions;
    auto menuPolicy = OptConvert<MenuPolicy>(options.menuPolicy);
    if (menuPolicy) {
        selectionOptions.menuPolicy = *menuPolicy;
    }
    return selectionOptions;
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace SearchControllerAccessor {

static void DestroyPeer(SearchControllerPeerImpl* peerImpl)
{
    if (peerImpl) {
        peerImpl->DecRefCount();
    }
}
SearchControllerPeer* CtorImpl()
{
    auto peerImpl = Referenced::MakeRefPtr<SearchControllerPeerImpl>();
    peerImpl->IncRefCount();
    return reinterpret_cast<SearchControllerPeer *>(Referenced::RawPtr(peerImpl));
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void*>(&DestroyPeer);
}
void CaretPositionImpl(SearchControllerPeer* peer,
                       const Ark_Number* value)
{
    CHECK_NULL_VOID(value);
    auto peerImpl = reinterpret_cast<SearchControllerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto caretPosition = Converter::Convert<int32_t>(*value);
    caretPosition = std::max(caretPosition, 0);
    peerImpl->TriggerCaretPosition(caretPosition);
}
void StopEditingImpl(SearchControllerPeer* peer)
{
    auto peerImpl = reinterpret_cast<SearchControllerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerStopEditing();
}
void SetTextSelectionImpl(SearchControllerPeer* peer,
                          const Ark_Number* selectionStart,
                          const Ark_Number* selectionEnd,
                          const Opt_SelectionOptions* options)
{
    auto peerImpl = reinterpret_cast<SearchControllerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    std::optional<SelectionOptions> selectionOptions = std::nullopt;
    int32_t start = 0;
    int32_t end = 0;
    if (!selectionStart || !selectionEnd) {
        LOGE("ArkUISearchControllerAccessor::SetTextSelection: The selectionStart or selectionEnd is NULL");
    }
    if (selectionStart != nullptr) {
        start = Converter::Convert<int32_t>(*selectionStart);
    }
    if (selectionEnd != nullptr) {
        end = Converter::Convert<int32_t>(*selectionEnd);
    }
    if (options != nullptr) {
        selectionOptions = Converter::OptConvert<SelectionOptions>(*options);
    }
    peerImpl->TriggerSetTextSelection(start, end, selectionOptions);
}
} // SearchControllerAccessor
const GENERATED_ArkUISearchControllerAccessor* GetSearchControllerAccessor()
{
    static const GENERATED_ArkUISearchControllerAccessor SearchControllerAccessorImpl {
        SearchControllerAccessor::CtorImpl,
        SearchControllerAccessor::GetFinalizerImpl,
        SearchControllerAccessor::CaretPositionImpl,
        SearchControllerAccessor::StopEditingImpl,
        SearchControllerAccessor::SetTextSelectionImpl,
    };
    return &SearchControllerAccessorImpl;
}

}
