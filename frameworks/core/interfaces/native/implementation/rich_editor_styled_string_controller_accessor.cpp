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
    dst.range.start = Converter::ArkValue<Opt_Int32>(src.GetRangeBefore().start);
    dst.range.end = Converter::ArkValue<Opt_Int32>(src.GetRangeBefore().end);
    dst.previewText = !src.GetPreviewText() ? Converter::ArkValue<Opt_StyledString>(Ark_Empty())
        : Converter::ArkValue<Opt_StyledString>(StyledStringPeer::Create(src.GetPreviewText()));
}
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RichEditorStyledStringControllerAccessor {
void DestroyPeerImpl(Ark_RichEditorStyledStringController peer)
{
    delete peer;
}
Ark_RichEditorStyledStringController ConstructImpl()
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
Opt_MutableStyledString GetStyledStringImpl(Ark_RichEditorStyledStringController peer)
{
    auto mutableString = PeerUtils::CreatePeer<MutableStyledStringPeer>();
    if (!peer || !mutableString) {
        PeerUtils::DestroyPeer(mutableString);
        return Converter::ArkValue<Opt_MutableStyledString>(Ark_Empty());
    }
    auto controller = (peer->GetTargetController()).Upgrade();
    if (!controller) {
        PeerUtils::DestroyPeer(mutableString);
        return Converter::ArkValue<Opt_MutableStyledString>(Ark_Empty());
    }
    mutableString->spanString = AceType::DynamicCast<MutableSpanString>(peer->GetStyledString());
    return Converter::ArkValue<Opt_MutableStyledString>(mutableString);
}
Opt_RichEditorRange GetSelectionImpl(Ark_RichEditorStyledStringController peer)
{
    CHECK_NULL_RETURN(peer, Converter::ArkValue<Opt_RichEditorRange>(Ark_Empty()));
    auto controller = (peer->GetTargetController()).Upgrade();
    CHECK_NULL_RETURN(controller, Converter::ArkValue<Opt_RichEditorRange>(Ark_Empty()));
    SelectionRangeInfo selection = peer->GetSelection();
    return Converter::ArkValue<Opt_RichEditorRange>(selection);
}
void OnContentChangedImpl(Ark_RichEditorStyledStringController peer,
                          const Ark_StyledStringChangedListener* listener)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(listener);
    // SetOnWillChange
    do {
        auto optValue = Converter::GetOpt(listener->onWillChange);
        CHECK_NULL_BREAK(optValue.has_value());
        auto onWillChangeArk = Converter::OptConvert<Callback_StyledStringChangeValue_Boolean>(optValue.value());
        auto onWillChange = [onWillChangeArk, arkCallback = CallbackHelper(*onWillChangeArk)](
            const StyledStringChangeValue& value) {
            auto changeValue = Converter::ArkValue<Ark_StyledStringChangeValue>(value);
            auto result = arkCallback.InvokeWithObtainResult<Ark_Boolean, Callback_Boolean_Void>(changeValue);
            return Converter::Convert<bool>(result);
        };
        peer->SetOnWillChange(std::move(onWillChange));
    } while (0);

    // SetOnDidChange
    do {
        auto optValue = Converter::GetOpt(listener->onDidChange);
        CHECK_NULL_BREAK(optValue.has_value());
        auto onDidChangeArk = Converter::OptConvert<OnDidChangeCallback>(optValue.value());
        auto onDidChange = [onDidChangeArk, arkCallback = CallbackHelper(*onDidChangeArk)](
            const StyledStringChangeValue& value) {
            TextRange inBefore = value.GetRangeBefore();
            TextRange inAfter = value.GetRangeAfter();
            Ark_TextRange rangeBefore = Converter::ArkValue<Ark_TextRange>(inBefore);
            Ark_TextRange rangeAfter = Converter::ArkValue<Ark_TextRange>(inAfter);
            arkCallback.Invoke(rangeBefore, rangeAfter);
        };
        peer->SetOnDidChange(std::move(onDidChange));
    } while (0);
}
} // RichEditorStyledStringControllerAccessor
const GENERATED_ArkUIRichEditorStyledStringControllerAccessor* GetRichEditorStyledStringControllerAccessor()
{
    static const GENERATED_ArkUIRichEditorStyledStringControllerAccessor RichEditorStyledStringControllerAccessorImpl {
        RichEditorStyledStringControllerAccessor::DestroyPeerImpl,
        RichEditorStyledStringControllerAccessor::ConstructImpl,
        RichEditorStyledStringControllerAccessor::GetFinalizerImpl,
        RichEditorStyledStringControllerAccessor::SetStyledStringImpl,
        RichEditorStyledStringControllerAccessor::GetStyledStringImpl,
        RichEditorStyledStringControllerAccessor::GetSelectionImpl,
        RichEditorStyledStringControllerAccessor::OnContentChangedImpl,
    };
    return &RichEditorStyledStringControllerAccessorImpl;
}
}
