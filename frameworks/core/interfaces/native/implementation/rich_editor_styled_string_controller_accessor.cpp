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

#include "mutable_styled_string_peer.h"
#include "rich_editor_styled_string_controller_peer_impl.h"
#include "styled_string_peer.h"

namespace OHOS::Ace::NG {
void AssignArkValue(Ark_StyledStringChangeValue& dst, const StyledStringChangeValue& src)
{
    dst.replacementString = StyledStringPeer::Create(src.GetReplacementString());
    dst.range.start = Converter::ArkValue<Opt_Number>(src.GetRangeAfter().start);
    dst.range.end = Converter::ArkValue<Opt_Number>(src.GetRangeAfter().end);
}
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
const GENERATED_ArkUIMutableStyledStringAccessor* GetMutableStyledStringAccessor();
namespace RichEditorStyledStringControllerAccessor {
void DestroyPeerImpl(Ark_RichEditorStyledStringController peer)
{
    delete peer;
}
Ark_RichEditorStyledStringController CtorImpl()
{
    return new RichEditorStyledStringControllerPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void SetStyledStringImpl(Ark_RichEditorStyledStringController peer,
                         Ark_StyledString styledString)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(styledString);
    peer->SetStyledString(styledString->spanString);
}
Ark_MutableStyledString GetStyledStringImpl(Ark_RichEditorStyledStringController peer)
{
    auto mutableString = reinterpret_cast<MutableStyledStringPeer*>(GetMutableStyledStringAccessor()->ctor());
    CHECK_NULL_RETURN(peer && mutableString, mutableString);
    mutableString->spanString = AceType::DynamicCast<MutableSpanString>(peer->GetStyledString());
    return mutableString;
}
Ark_RichEditorRange GetSelectionImpl(Ark_RichEditorStyledStringController peer)
{
    CHECK_NULL_RETURN(peer, {});
    LOGW("RichEditorStyledString Accessor:: GetSelectionImpl is not implemented");
    return {};
}
void OnContentChangedImpl(Ark_RichEditorStyledStringController peer,
                          const Ark_StyledStringChangedListener* listener)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(listener);

    auto onWillChangeArk = Converter::OptConvert<Callback_StyledStringChangeValue_Boolean>(listener->onWillChange);
    auto onWillChange = [onWillChangeArk, arkCallback = CallbackHelper(*onWillChangeArk)](
        const StyledStringChangeValue& value) {
        auto changeValue = Converter::ArkValue<Ark_StyledStringChangeValue>(value);
        Callback_Boolean_Void continuation;
        arkCallback.Invoke(changeValue, continuation);
        return true;
    };
    peer->SetOnWillChange(std::move(onWillChange));

    auto onDidChangeArk = Converter::OptConvert<OnDidChangeCallback>(listener->onDidChange);
    auto onDidChange = [onDidChangeArk, arkCallback = CallbackHelper(*onDidChangeArk)](
        const StyledStringChangeValue& value) {
        auto changeValue = Converter::ArkValue<Ark_StyledStringChangeValue>(value);
        arkCallback.Invoke(changeValue.range, changeValue.range);
    };
    peer->SetOnDidChange(std::move(onDidChange));
}
} // RichEditorStyledStringControllerAccessor
const GENERATED_ArkUIRichEditorStyledStringControllerAccessor* GetRichEditorStyledStringControllerAccessor()
{
    static const GENERATED_ArkUIRichEditorStyledStringControllerAccessor RichEditorStyledStringControllerAccessorImpl {
        RichEditorStyledStringControllerAccessor::DestroyPeerImpl,
        RichEditorStyledStringControllerAccessor::CtorImpl,
        RichEditorStyledStringControllerAccessor::GetFinalizerImpl,
        RichEditorStyledStringControllerAccessor::SetStyledStringImpl,
        RichEditorStyledStringControllerAccessor::GetStyledStringImpl,
        RichEditorStyledStringControllerAccessor::GetSelectionImpl,
        RichEditorStyledStringControllerAccessor::OnContentChangedImpl,
    };
    return &RichEditorStyledStringControllerAccessorImpl;
}
}
