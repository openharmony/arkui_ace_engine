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
    namespace ScrollerModifier {
        Ark_NativePointer CtorImpl() {
            return 0;
        }
        Ark_NativePointer GetFinalizerImpl() {
            return 0;
        }
        void ScrollToImpl(ScrollerPeer* peer, const Literal_xOffset_Union_Ark_Number_Ark_String_yOffset_Union_Ark_Number_Ark_String_animation_Opt_Union_Opt_ScrollAnimationOptions_Opt_Ark_Boolean* value) {
        }
        void ScrollEdgeImpl(ScrollerPeer* peer, Ark_Int32 value, const Opt_ScrollEdgeOptions* options) {
        }
        void FlingImpl(ScrollerPeer* peer, const Ark_Number* velocity) {
        }
        void ScrollPage_ScrollPageOptionsImpl(ScrollerPeer* peer, const ScrollPageOptions* value) {
        }
        void ScrollPage_nextbooleandirectionAxisImpl(ScrollerPeer* peer, const Literal_next_Ark_Boolean_direction_Ark_Axis* value) {
        }
        Ark_NativePointer CurrentOffsetImpl(ScrollerPeer* peer) {
            return 0;
        }
        void ScrollToIndexImpl(ScrollerPeer* peer, const Ark_Number* value, const Opt_Ark_Boolean* smooth, const Opt_Ark_ScrollAlign* align, const Opt_ScrollToIndexOptions* options) {
        }
        void ScrollByImpl(ScrollerPeer* peer, const Ark_Length* dx, const Ark_Length* dy) {
        }
        Ark_Boolean IsAtEndImpl(ScrollerPeer* peer) {
            return 0;
        }
        Ark_NativePointer GetItemRectImpl(ScrollerPeer* peer, const Ark_Number* index) {
            return 0;
        }
    } // ScrollerModifier
    const GENERATED_ArkUIScrollerAccessor* GetScrollerAccessor() {
        static const GENERATED_ArkUIScrollerAccessor ScrollerAccessorImpl {
            ScrollerModifier::CtorImpl,
            ScrollerModifier::GetFinalizerImpl,
            ScrollerModifier::ScrollToImpl,
            ScrollerModifier::ScrollEdgeImpl,
            ScrollerModifier::FlingImpl,
            ScrollerModifier::ScrollPage_ScrollPageOptionsImpl,
            ScrollerModifier::ScrollPage_nextbooleandirectionAxisImpl,
            ScrollerModifier::CurrentOffsetImpl,
            ScrollerModifier::ScrollToIndexImpl,
            ScrollerModifier::ScrollByImpl,
            ScrollerModifier::IsAtEndImpl,
            ScrollerModifier::GetItemRectImpl,
        };
        return &ScrollerAccessorImpl;
    }

}
