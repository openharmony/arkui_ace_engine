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
#include "core/interfaces/native/implementation/rich_editor_styled_string_controller_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/implementation/styled_string_peer.h"
#include "core/interfaces/native/implementation/mutable_styled_string_peer.h"

namespace OHOS::Ace::NG::Converter {
void AssignArkValue(Ark_Materialized& dst, const std::string& src)
{
    auto str2 = const_cast<std::string&>(src);
    dst.ptr = &str2;
}
void AssignArkValue(Ark_StyledStringChangeValue& dst, const StyledStringChangeValue& src)
{
    auto str = src.GetReplacementString();
    auto replacementString = reinterpret_cast<MutableSpanString*>(str.GetRawPtr());
    if (replacementString) {
        dst.replacementString = Converter::ArkValue<Ark_StyledString>(replacementString->GetString());
    }
    dst.range.start = Converter::ArkValue<Opt_Number>(src.GetRangeAfter().start);
    dst.range.end = Converter::ArkValue<Opt_Number>(src.GetRangeAfter().end);
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
const GENERATED_ArkUIMutableStyledStringAccessor* GetMutableStyledStringAccessor();
namespace RichEditorStyledStringControllerAccessor {
void DestroyPeerImpl(RichEditorStyledStringControllerPeer* peer)
{
    delete peer;
}
Ark_NativePointer CtorImpl()
{
    return new RichEditorStyledStringControllerPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void SetStyledStringImpl(RichEditorStyledStringControllerPeer* peer,
                         const Ark_StyledString* styledString)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(styledString);
    CHECK_NULL_VOID(styledString->ptr);
    auto styledStringPeer = reinterpret_cast<StyledStringPeer *>(styledString->ptr);
    peer->SetStyledString(styledStringPeer->spanString);
}
Ark_NativePointer GetStyledStringImpl(RichEditorStyledStringControllerPeer* peer)
{
    auto mutableString = reinterpret_cast<MutableStyledStringPeer*>(GetMutableStyledStringAccessor()->ctor());
    CHECK_NULL_RETURN(peer && mutableString, mutableString);
    mutableString->spanString = AceType::DynamicCast<MutableSpanString>(peer->GetStyledString());
    return mutableString;
}
Ark_NativePointer GetSelectionImpl(RichEditorStyledStringControllerPeer* peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    LOGW("RichEditorStyledString Accessor:: GetSelectionImpl is not implemented");
    return nullptr;
}
void OnContentChangedImpl(RichEditorStyledStringControllerPeer* peer,
                          const Ark_StyledStringChangedListener* listener)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(listener);

    auto onWillChangeArk = Converter::OptConvert<Callback_StyledStringChangeValue_Boolean>(listener->onWillChange);
    auto onWillChangeCapture = std::make_shared<Callback_StyledStringChangeValue_Boolean>(*onWillChangeArk);
    auto onWillChange = [onWillChangeCapture, arkCallback = CallbackHelper(*onWillChangeCapture)](
        const StyledStringChangeValue& value) {
        auto changeValue = Converter::ArkValue<Ark_StyledStringChangeValue>(value);
        Callback_Boolean_Void continuation;
        arkCallback.Invoke(changeValue, continuation);
        return true;
    };
    peer->SetOnWillChange(std::move(onWillChange));

    auto onDidChangeArk = Converter::OptConvert<OnDidChangeCallback>(listener->onDidChange);
    auto onDidChangeCapture = std::make_shared<OnDidChangeCallback>(*onDidChangeArk);
    auto onDidChange = [onDidChangeCapture, arkCallback = CallbackHelper(*onDidChangeCapture)](
        const StyledStringChangeValue& value) {
        auto changeValue = Converter::ArkValue<Ark_StyledStringChangeValue>(value);
        arkCallback.Invoke(changeValue.range, changeValue.range);
        LOGW("RichEditorStyledStringControllerAccessor :: before range = after, that's temporary and will be fixed");
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
