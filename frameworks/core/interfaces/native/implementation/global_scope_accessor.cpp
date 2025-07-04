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
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace GlobalScopeAccessor {
Ark_Resource $rImpl(const Ark_String* value,
                    const Array_Opt_Object* params)
{
    return {};
}
Ark_Resource $rawfileImpl(const Ark_String* value)
{
    return {};
}
void AnimateToImpl(const Ark_AnimateParam* value,
                   const Callback_Void* event)
{
}
void AnimateToImmediatelyImpl(const Ark_AnimateParam* value,
                              const Callback_Void* event)
{
}
void ArkUICompatibleImpl(const Callback_InteropComponent* init,
                         const Callback_Number_ESObject_Void* update)
{
}
Ark_BorderRadiuses BorderRadiusesImpl(const Ark_Number* all)
{
    return {};
}
Ark_Edges BorderStylesImpl(Ark_BorderStyle all)
{
    return {};
}
void CursorControl_restoreDefaultImpl()
{
}
void CursorControl_setCursorImpl(Ark_pointer_PointerStyle value)
{
}
Ark_Edges EdgeColorsImpl(const Ark_Number* all)
{
    return {};
}
Ark_Edges EdgeWidthsImpl(const Ark_Number* all)
{
    return {};
}
Ark_Boolean FocusControl_requestFocusImpl(const Ark_String* value)
{
    return {};
}
Ark_font_UIFontConfig Font_getUIFontConfigImpl()
{
    return {};
}
Ark_ComponentInfo GetRectangleByIdImpl(const Ark_String* id)
{
    return {};
}
void PostCardActionImpl(const Ark_Object* component,
                        const Ark_Object* action)
{
}
void Profiler_registerVsyncCallbackImpl(const Profiler_Callback_String_Void* callback_)
{
}
void Profiler_unregisterVsyncCallbackImpl()
{
}
Ark_Number Px2vpImpl(const Ark_Number* value)
{
    return {};
}
void SetAppBgColorImpl(const Ark_String* value)
{
}
void Text_getFontDescriptorByFullNameImpl(Ark_VMContext vmContext,
                                          Ark_AsyncWorkerPtr asyncWorker,
                                          const Ark_String* fullName,
                                          Ark_text_SystemFontType fontType,
                                          const Callback_Opt_FontDescriptor_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
}
void Text_getSystemFontFullNamesByTypeImpl(Ark_VMContext vmContext,
                                           Ark_AsyncWorkerPtr asyncWorker,
                                           Ark_text_SystemFontType fontType,
                                           const Callback_Opt_Array_String_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
}
void Text_matchFontDescriptorsImpl(Ark_VMContext vmContext,
                                   Ark_AsyncWorkerPtr asyncWorker,
                                   const Ark_text_FontDescriptor* desc,
                                   const Callback_Opt_Array_FontDescriptor_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
}
Ark_uiEffect_BrightnessBlender UiEffect_createBrightnessBlenderImpl(const Ark_uiEffect_BrightnessBlenderParam* param)
{
    return {};
}
Ark_uiEffect_VisualEffect UiEffect_createEffectImpl()
{
    return {};
}
Ark_Number Vp2pxImpl(const Ark_Number* value)
{
    return {};
}
} // GlobalScopeAccessor
const GENERATED_ArkUIGlobalScopeAccessor* GetGlobalScopeAccessor()
{
    static const GENERATED_ArkUIGlobalScopeAccessor GlobalScopeAccessorImpl {
        GlobalScopeAccessor::$rImpl,
        GlobalScopeAccessor::$rawfileImpl,
        GlobalScopeAccessor::AnimateToImpl,
        GlobalScopeAccessor::AnimateToImmediatelyImpl,
        GlobalScopeAccessor::ArkUICompatibleImpl,
        GlobalScopeAccessor::BorderRadiusesImpl,
        GlobalScopeAccessor::BorderStylesImpl,
        GlobalScopeAccessor::CursorControl_restoreDefaultImpl,
        GlobalScopeAccessor::CursorControl_setCursorImpl,
        GlobalScopeAccessor::EdgeColorsImpl,
        GlobalScopeAccessor::EdgeWidthsImpl,
        GlobalScopeAccessor::FocusControl_requestFocusImpl,
        GlobalScopeAccessor::Font_getUIFontConfigImpl,
        GlobalScopeAccessor::GetRectangleByIdImpl,
        GlobalScopeAccessor::PostCardActionImpl,
        GlobalScopeAccessor::Profiler_registerVsyncCallbackImpl,
        GlobalScopeAccessor::Profiler_unregisterVsyncCallbackImpl,
        GlobalScopeAccessor::Px2vpImpl,
        GlobalScopeAccessor::SetAppBgColorImpl,
        GlobalScopeAccessor::Text_getFontDescriptorByFullNameImpl,
        GlobalScopeAccessor::Text_getSystemFontFullNamesByTypeImpl,
        GlobalScopeAccessor::Text_matchFontDescriptorsImpl,
        GlobalScopeAccessor::UiEffect_createBrightnessBlenderImpl,
        GlobalScopeAccessor::UiEffect_createEffectImpl,
        GlobalScopeAccessor::Vp2pxImpl,
    };
    return &GlobalScopeAccessorImpl;
}

struct GlobalScopePeer {
    virtual ~GlobalScopePeer() = default;
};
}
