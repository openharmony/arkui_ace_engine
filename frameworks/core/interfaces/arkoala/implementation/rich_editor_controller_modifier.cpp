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

#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
    namespace RichEditorControllerModifier {
        Ark_NativePointer CtorImpl() {
            return 0;
        }
        Ark_NativePointer GetFinalizerImpl() {
            return 0;
        }
        Ark_Int32 AddTextSpanImpl(RichEditorControllerPeer* peer, const Ark_String* value, const Opt_RichEditorTextSpanOptions* options) {
            return 0;
        }
        Ark_Int32 AddImageSpanImpl(RichEditorControllerPeer* peer, const Union_PixelMap_ResourceStr* value, const Opt_RichEditorImageSpanOptions* options) {
            return 0;
        }
        Ark_Int32 AddBuilderSpanImpl(RichEditorControllerPeer* peer, const CustomBuilder* value, const Opt_RichEditorBuilderSpanOptions* options) {
            return 0;
        }
        Ark_Int32 AddSymbolSpanImpl(RichEditorControllerPeer* peer, const Ark_CustomObject* value, const Opt_RichEditorSymbolSpanOptions* options) {
            return 0;
        }
        void UpdateSpanStyleImpl(RichEditorControllerPeer* peer, const Union_RichEditorUpdateTextSpanStyleOptions_RichEditorUpdateImageSpanStyleOptions_RichEditorUpdateSymbolSpanStyleOptions* value) {
        }
        void UpdateParagraphStyleImpl(RichEditorControllerPeer* peer, const RichEditorParagraphStyleOptions* value) {
        }
        void DeleteSpansImpl(RichEditorControllerPeer* peer, const Opt_RichEditorRange* value) {
        }
        Ark_NativePointer GetSpansImpl(RichEditorControllerPeer* peer, const Opt_RichEditorRange* value) {
            return 0;
        }
        Ark_NativePointer GetParagraphsImpl(RichEditorControllerPeer* peer, const Opt_RichEditorRange* value) {
            return 0;
        }
        Ark_NativePointer GetSelectionImpl(RichEditorControllerPeer* peer) {
            return 0;
        }
        Ark_NativePointer FromStyledStringImpl(RichEditorControllerPeer* peer, const Ark_Materialized* value) {
            return 0;
        }
        Ark_NativePointer ToStyledStringImpl(RichEditorControllerPeer* peer, const RichEditorRange* value) {
            return 0;
        }
    } // RichEditorControllerModifier
    const GENERATED_ArkUIRichEditorControllerAccessor* GetRichEditorControllerAccessor() {
        static const GENERATED_ArkUIRichEditorControllerAccessor RichEditorControllerAccessorImpl {
            RichEditorControllerModifier::CtorImpl,
            RichEditorControllerModifier::GetFinalizerImpl,
            RichEditorControllerModifier::AddTextSpanImpl,
            RichEditorControllerModifier::AddImageSpanImpl,
            RichEditorControllerModifier::AddBuilderSpanImpl,
            RichEditorControllerModifier::AddSymbolSpanImpl,
            RichEditorControllerModifier::UpdateSpanStyleImpl,
            RichEditorControllerModifier::UpdateParagraphStyleImpl,
            RichEditorControllerModifier::DeleteSpansImpl,
            RichEditorControllerModifier::GetSpansImpl,
            RichEditorControllerModifier::GetParagraphsImpl,
            RichEditorControllerModifier::GetSelectionImpl,
            RichEditorControllerModifier::FromStyledStringImpl,
            RichEditorControllerModifier::ToStyledStringImpl,
        };
        return &RichEditorControllerAccessorImpl;
    }

}
