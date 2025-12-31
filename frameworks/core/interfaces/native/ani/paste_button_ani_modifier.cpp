/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "paste_button_ani_modifier.h"

#include "ani.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/security_component/paste_button/paste_button_common.h"
#include "core/components_ng/pattern/security_component/paste_button/paste_button_model_ng.h"

namespace OHOS::Ace::NG {
static void CreateBusinessError(
    ani_env* env, const GestureEvent& info, ani_object& errAni, ani_enum_item& resultAni)
{
    ani_class errorClass;
    env->FindClass("@ohos.base.BusinessError", &errorClass);
    CHECK_NULL_VOID(errorClass);
    ani_method ctor;
    int32_t res = static_cast<int32_t>(SecurityComponentHandleResult::CLICK_GRANT_FAILED);
#ifdef SECURITY_COMPONENT_ENABLE
    auto secEventValue = info.GetSecCompHandleEvent();
    if (secEventValue != nullptr) {
        res = secEventValue->GetInt("handleRes", res);
        int32_t code = static_cast<int32_t>(SecurityComponentErrorCode::SUCCESS);
        std::string message;
        if (res == static_cast<int32_t>(SecurityComponentHandleResult::DROP_CLICK)) {
            return;
        }

        env->Class_FindMethod(errorClass, "<ctor>", ":", &ctor);
        CHECK_NULL_VOID(ctor);
        env->Object_New(errorClass, ctor, &errAni);
        CHECK_NULL_VOID(errAni);
        code = secEventValue->GetInt("code", code);
        env->Object_SetPropertyByName_Int(errAni, "code", code);
        message = secEventValue->GetString("message", message);
        ani_string msgAni {};
        env->String_NewUTF8(message.c_str(), message.size(), &msgAni);
        env->Object_SetPropertyByName_Ref(errAni, "message", msgAni);

        ani_enum onClickResult;
        env->FindEnum("arkui.component.pasteButton.PasteButtonOnClickResult", &onClickResult);
        CHECK_NULL_VOID(onClickResult);
        env->Enum_GetEnumItemByIndex(onClickResult, static_cast<ani_size>(res), &resultAni);
        CHECK_NULL_VOID(resultAni);
    }
#endif
}

static ani_status GetAniEnv(ani_vm* vm, ani_env** env)
{
    CHECK_NULL_RETURN(vm, ANI_ERROR);
    ani_options aniOpt { 0, nullptr };
    auto status = vm->AttachCurrentThread(&aniOpt, ANI_VERSION_1, env);
    if (status != ANI_OK) {
        vm->GetEnv(ANI_VERSION_1, env);
    }
    return status;
}

class PasteButtonCallbackAni {
public:
    PasteButtonCallbackAni(ani_env* env, ani_ref func)
    {
        CHECK_NULL_VOID(env);
        env->GetVM(&vm_);
        env->GlobalReference_Create(func, &func_);
    }
    ~PasteButtonCallbackAni()
    {
        CHECK_NULL_VOID(vm_);
        CHECK_NULL_VOID(func_);
        ani_env* env;
        auto attachCurrentThreadStatus = GetAniEnv(vm_, &env);
        CHECK_NULL_VOID(env);
        env->GlobalReference_Delete(func_);
        if (attachCurrentThreadStatus == ANI_OK) {
            vm_->DetachCurrentThread();
        }
    }
    void Call(ani_env* env, ani_size argc, ani_ref* argv, ani_ref* result)
    {
        CHECK_NULL_VOID(env);
        ani_status status = env->FunctionalObject_Call(static_cast<ani_fn_object>(func_), argc, argv, result);
        if (status != ANI_OK) {
            SC_LOG_ERROR("PasteButtonCallbackAni call failed, status: %{public}d", status);
        }
    }

private:
    ani_vm* vm_ = nullptr;
    ani_ref func_ = nullptr;
};

static void ConvertOnClickCallback(
    ani_env* env, ani_object onClickCallback, std::function<void(const GestureEvent& info)>& callback)
{
    CHECK_NULL_VOID(env);

    ani_vm* vm = nullptr;
    env->GetVM(&vm);
    ani_ref fnObjGlobalRef = static_cast<ani_object>(onClickCallback);

    auto callbackAni = std::make_shared<PasteButtonCallbackAni>(env, fnObjGlobalRef);
    callback = [vm, callbackAni](const GestureEvent& info) {
        CHECK_NULL_VOID(vm);
        CHECK_NULL_VOID(callbackAni);
        ani_env* env;
        auto attachCurrentThreadStatus = GetAniEnv(vm, &env);
        CHECK_NULL_VOID(env);

        ani_object clickEventAni = SecurityComponentAniMethod::CreateClickEvent(env, info);
        CHECK_NULL_VOID(clickEventAni);
        ani_object errorAni {};
        ani_enum_item resultAni {};
        CreateBusinessError(env, info, errorAni, resultAni);
        CHECK_NULL_VOID(errorAni);
        CHECK_NULL_VOID(resultAni);
        std::vector<ani_ref> args = { clickEventAni, resultAni, errorAni };
        ani_ref ret = nullptr;
        callbackAni->Call(env, args.size(), args.data(), &ret);
        if (attachCurrentThreadStatus == ANI_OK) {
            vm->DetachCurrentThread();
        }
    };
}

void SetPasteButtonOnClickCallback(ani_env* env, ArkUINodeHandle node, void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(env);
    ani_object fnObjGlobal = static_cast<ani_object>(callback);

    std::function<void(const GestureEvent& info)> onEvent = nullptr;
    ConvertOnClickCallback(env, fnObjGlobal, onEvent);

    ViewAbstract::SetOnClick(frameNode, std::move(onEvent));
}

const ArkUIAniPasteButtonModifier* GetPasteButtonAniModifier()
{
    static const ArkUIAniPasteButtonModifier impl = {
        .setPasteButtonOnClickCallback = OHOS::Ace::NG::SetPasteButtonOnClickCallback,
    };
    return &impl;
}
} // namespace OHOS::Ace::NG