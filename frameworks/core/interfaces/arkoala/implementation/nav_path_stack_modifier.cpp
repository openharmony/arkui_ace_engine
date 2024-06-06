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
    namespace NavPathStackModifier {
        Ark_NativePointer CtorImpl() {
            return 0;
        }
        Ark_NativePointer GetFinalizerImpl() {
            return 0;
        }
        void PushPath_NavPathInfo_booleanImpl(NavPathStackPeer* peer, const NavPathInfo* info, const Opt_Ark_Boolean* animated) {
        }
        void PushPath_NavPathInfo_NavigationOptionsImpl(NavPathStackPeer* peer, const NavPathInfo* info, const Opt_NavigationOptions* options) {
        }
        Ark_NativePointer PushDestination_NavPathInfo_booleanImpl(NavPathStackPeer* peer, const NavPathInfo* info, const Opt_Ark_Boolean* animated) {
            return 0;
        }
        Ark_NativePointer PushDestination_NavPathInfo_NavigationOptionsImpl(NavPathStackPeer* peer, const NavPathInfo* info, const Opt_NavigationOptions* options) {
            return 0;
        }
        void PushPathByName_string_unknown_booleanImpl(NavPathStackPeer* peer, const Ark_String* name, const Ark_CustomObject* param, const Opt_Ark_Boolean* animated) {
        }
        void PushPathByName_string_Object_IMPORTCallbackPopInfoFROMapiohosbase_booleanImpl(NavPathStackPeer* peer, const Ark_String* name, const Object* param, Ark_Function onPop, const Opt_Ark_Boolean* animated) {
        }
        Ark_NativePointer PushDestinationByName_string_Object_booleanImpl(NavPathStackPeer* peer, const Ark_String* name, const Object* param, const Opt_Ark_Boolean* animated) {
            return 0;
        }
        Ark_NativePointer PushDestinationByName_string_Object_IMPORTCallbackPopInfoFROMapiohosbase_booleanImpl(NavPathStackPeer* peer, const Ark_String* name, const Object* param, Ark_Function onPop, const Opt_Ark_Boolean* animated) {
            return 0;
        }
        void ReplacePath_NavPathInfo_booleanImpl(NavPathStackPeer* peer, const NavPathInfo* info, const Opt_Ark_Boolean* animated) {
        }
        void ReplacePath_NavPathInfo_NavigationOptionsImpl(NavPathStackPeer* peer, const NavPathInfo* info, const Opt_NavigationOptions* options) {
        }
        void ReplacePathByNameImpl(NavPathStackPeer* peer, const Ark_String* name, const Object* param, const Opt_Ark_Boolean* animated) {
        }
        Ark_Int32 RemoveByIndexesImpl(NavPathStackPeer* peer, const Array_Ark_Number* indexes) {
            return 0;
        }
        Ark_Int32 RemoveByNameImpl(NavPathStackPeer* peer, const Ark_String* name) {
            return 0;
        }
        void Pop_booleanImpl(NavPathStackPeer* peer, const Opt_Ark_Boolean* animated) {
        }
        void Pop_Object_booleanImpl(NavPathStackPeer* peer, const Object* result, const Opt_Ark_Boolean* animated) {
        }
        Ark_Int32 PopToName_string_booleanImpl(NavPathStackPeer* peer, const Ark_String* name, const Opt_Ark_Boolean* animated) {
            return 0;
        }
        Ark_Int32 PopToName_string_Object_booleanImpl(NavPathStackPeer* peer, const Ark_String* name, const Object* result, const Opt_Ark_Boolean* animated) {
            return 0;
        }
        void PopToIndex_number_booleanImpl(NavPathStackPeer* peer, const Ark_Number* index, const Opt_Ark_Boolean* animated) {
        }
        void PopToIndex_number_Object_booleanImpl(NavPathStackPeer* peer, const Ark_Number* index, const Object* result, const Opt_Ark_Boolean* animated) {
        }
        Ark_Int32 MoveToTopImpl(NavPathStackPeer* peer, const Ark_String* name, const Opt_Ark_Boolean* animated) {
            return 0;
        }
        void MoveIndexToTopImpl(NavPathStackPeer* peer, const Ark_Number* index, const Opt_Ark_Boolean* animated) {
        }
        void ClearImpl(NavPathStackPeer* peer, const Opt_Ark_Boolean* animated) {
        }
        Ark_NativePointer GetAllPathNameImpl(NavPathStackPeer* peer) {
            return 0;
        }
        void GetParamByIndexImpl(NavPathStackPeer* peer, const Ark_Number* index) {
        }
        Ark_NativePointer GetParamByNameImpl(NavPathStackPeer* peer, const Ark_String* name) {
            return 0;
        }
        Ark_NativePointer GetIndexByNameImpl(NavPathStackPeer* peer, const Ark_String* name) {
            return 0;
        }
        Ark_NativePointer GetParentImpl(NavPathStackPeer* peer) {
            return 0;
        }
        Ark_Int32 SizeImpl(NavPathStackPeer* peer) {
            return 0;
        }
        void DisableAnimationImpl(NavPathStackPeer* peer, Ark_Boolean value) {
        }
        void SetInterceptionImpl(NavPathStackPeer* peer, const NavigationInterception* interception) {
        }
    } // NavPathStackModifier
    const GENERATED_ArkUINavPathStackAccessor* GetNavPathStackAccessor() {
        static const GENERATED_ArkUINavPathStackAccessor NavPathStackAccessorImpl {
            NavPathStackModifier::CtorImpl,
            NavPathStackModifier::GetFinalizerImpl,
            NavPathStackModifier::PushPath_NavPathInfo_booleanImpl,
            NavPathStackModifier::PushPath_NavPathInfo_NavigationOptionsImpl,
            NavPathStackModifier::PushDestination_NavPathInfo_booleanImpl,
            NavPathStackModifier::PushDestination_NavPathInfo_NavigationOptionsImpl,
            NavPathStackModifier::PushPathByName_string_unknown_booleanImpl,
            NavPathStackModifier::PushPathByName_string_Object_IMPORTCallbackPopInfoFROMapiohosbase_booleanImpl,
            NavPathStackModifier::PushDestinationByName_string_Object_booleanImpl,
            NavPathStackModifier::PushDestinationByName_string_Object_IMPORTCallbackPopInfoFROMapiohosbase_booleanImpl,
            NavPathStackModifier::ReplacePath_NavPathInfo_booleanImpl,
            NavPathStackModifier::ReplacePath_NavPathInfo_NavigationOptionsImpl,
            NavPathStackModifier::ReplacePathByNameImpl,
            NavPathStackModifier::RemoveByIndexesImpl,
            NavPathStackModifier::RemoveByNameImpl,
            NavPathStackModifier::Pop_booleanImpl,
            NavPathStackModifier::Pop_Object_booleanImpl,
            NavPathStackModifier::PopToName_string_booleanImpl,
            NavPathStackModifier::PopToName_string_Object_booleanImpl,
            NavPathStackModifier::PopToIndex_number_booleanImpl,
            NavPathStackModifier::PopToIndex_number_Object_booleanImpl,
            NavPathStackModifier::MoveToTopImpl,
            NavPathStackModifier::MoveIndexToTopImpl,
            NavPathStackModifier::ClearImpl,
            NavPathStackModifier::GetAllPathNameImpl,
            NavPathStackModifier::GetParamByIndexImpl,
            NavPathStackModifier::GetParamByNameImpl,
            NavPathStackModifier::GetIndexByNameImpl,
            NavPathStackModifier::GetParentImpl,
            NavPathStackModifier::SizeImpl,
            NavPathStackModifier::DisableAnimationImpl,
            NavPathStackModifier::SetInterceptionImpl,
        };
        return &NavPathStackAccessorImpl;
    }

}
