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

#include "arkts_entry_loader.h"

#include "base/log/log_wrapper.h"
#include "bridge/arkts_frontend/arkts_ani_utils.h"
#include "core/common/container.h"

namespace OHOS::Ace {

static const std::string ENTRY_PREFIX = "/src/main/ets/";
static const std::string ENTRY_SUFFIX = "/__EntryWrapper";

ani_object EntryLoader::GetPageEntryObj()
{
    const std::string moduleName = Container::Current()->GetModuleName();
    std::string entryPointName;
    entryPointName.reserve(moduleName.size() + ENTRY_PREFIX.size() + url_.size() + ENTRY_SUFFIX.size());
    entryPointName.append(moduleName).append(ENTRY_PREFIX).append(url_).append(ENTRY_SUFFIX);
    ani_string entryStr;
    env_->String_NewUTF8(entryPointName.c_str(), entryPointName.length(), &entryStr);
    ani_class entryClass = nullptr;
    ani_ref entryClassRef = nullptr;
    ani_class cls = nullptr;
    ani_status state;
    ani_ref linkerRef;

    do {
        if ((state = static_cast<ani_status>(ArktsAniUtils::GetNearestNonBootRuntimeLinker(env_, linkerRef))) !=
            ANI_OK) {
            LOGE("EntryLoader Get getNearestNonBootRuntimeLinker failed, %{public}d", state);
            break;
        }
        if ((state = env_->FindClass("Lstd/core/RuntimeLinker;", &cls)) != ANI_OK) {
            LOGE("EntryLoader FindClass RuntimeLinker failed, %{public}d", state);
            break;
        }

        ani_method loadClassMethod;
        if ((state = env_->Class_FindMethod(cls, "loadClass", "Lstd/core/String;Lstd/core/Boolean;:Lstd/core/Class;",
                 &loadClassMethod)) != ANI_OK) {
            LOGE("EntryLoader Class_FindMethod loadClass failed, %{public}d", state);
            break;
        }

        ani_object isInit;
        if ((state = static_cast<ani_status>(ArktsAniUtils::CreateAniBoolean(env_, false, isInit))) != ANI_OK) {
            LOGE("EntryLoader Create Boolean object failed, %{public}d", state);
            break;
        }

        if ((state = env_->Object_CallMethod_Ref(
                 (ani_object)linkerRef, loadClassMethod, &entryClassRef, entryStr, isInit)) != ANI_OK) {
            LOGE("EntryLoader Object_CallMethod_Ref loadClassMethod failed %{public}d %s", state,
                entryPointName.c_str());
            ani_error errorInfo;
            env_->GetUnhandledError(&errorInfo);
            env_->ResetError();
            break;
        }
        entryClass = static_cast<ani_class>(entryClassRef);

        ani_method entryMethod = nullptr;
        if (env_->Class_FindMethod(entryClass, "<ctor>", ":V", &entryMethod) != ANI_OK) {
            LOGE("EntryLoader Class_FindMethod ctor failed");
            break;
        }

        ani_object entryObject = nullptr;
        if (env_->Object_New(entryClass, entryMethod, &entryObject) != ANI_OK) {
            LOGE("EntryLoader Object_New AbcRuntimeLinker failed");
            break;
        }
        return entryObject;
    } while (false);
    return nullptr;
}

namespace NG {
EntryLoader::EntryLoader(ani_env* env, const std::string& abcModulePath): env_(env)
{
    ani_ref undefined;
    ANI_CALL(env, GetUndefined(&undefined), return);

    ani_string abcModulePathStr;
    ANI_CALL(env, String_NewUTF8(abcModulePath.c_str(), abcModulePath.length(), &abcModulePathStr), return);

    ani_type stringCls;
    ANI_CALL(env, Object_GetType(abcModulePathStr, &stringCls), return);

    ani_array_ref refArray;
    ANI_CALL(env, Array_New_Ref(stringCls, 1, abcModulePathStr, &refArray), return);

    ani_class cls;
    ANI_CALL(env, FindClass("Lstd/core/AbcRuntimeLinker;", &cls), return);

    ani_method ctor;
    ANI_CALL(env, Class_FindMethod(
        cls, "<ctor>", "Lstd/core/RuntimeLinker;[Lstd/core/String;:V", &ctor), return);

    ANI_CALL(env, Object_New(cls, ctor, &runtimeLinkerObj_, undefined, refArray), return);

    ANI_CALL(env, Class_FindMethod(
        cls, "loadClass", "Lstd/core/String;Lstd/core/Boolean;:Lstd/core/Class;", &loadClass_), return);
}

EntryLoader::EntryLoader(ani_env* env, const std::vector<uint8_t>& abcContent): env_(env)
{
    ani_ref undefined;
    ANI_CALL(env, GetUndefined(&undefined), return);

    ani_array_byte byteArray;
    ANI_CALL(env, Array_New_Byte(abcContent.size(), &byteArray), return);
    ANI_CALL(env, Array_SetRegion_Byte(
        byteArray, 0, abcContent.size(), reinterpret_cast<const ani_byte*>(abcContent.data())), return);

    ani_type byteArrayCls;
    ANI_CALL(env, Object_GetType(byteArray, &byteArrayCls), return);

    ani_array_ref refArray;
    ANI_CALL(env, Array_New_Ref(byteArrayCls, 1, byteArray, &refArray), return);

    ani_class cls;
    ANI_CALL(env, FindClass("Lstd/core/MemoryRuntimeLinker;", &cls), return);

    ani_method ctor;
    ANI_CALL(env, Class_FindMethod(
        cls, "<ctor>", "Lstd/core/RuntimeLinker;[[B:V", &ctor), return);

    ANI_CALL(env, Object_New(cls, ctor, &runtimeLinkerObj_, undefined, refArray), return);

    ANI_CALL(env, Class_FindMethod(
        cls, "loadClass", "Lstd/core/String;Lstd/core/Boolean;:Lstd/core/Class;", &loadClass_), return);
}

ani_object EntryLoader::GetPageEntryObj(const std::string& entryPath) const
{
    ani_string entryClassStr;
    ANI_CALL(env_, String_NewUTF8(entryPath.c_str(), entryPath.length(), &entryClassStr), return {});

    ani_ref entryClass;
    ANI_CALL(env_, Object_CallMethod_Ref(runtimeLinkerObj_, loadClass_, &entryClass, entryClassStr, false), return {});

    ani_method entryCtor;
    ANI_CALL(env_, Class_FindMethod(static_cast<ani_class>(entryClass), "<ctor>", ":V", &entryCtor), return {});

    ani_object entryObject = nullptr;
    ANI_CALL(env_, Object_New(static_cast<ani_class>(entryClass), entryCtor, &entryObject), return {});

    return entryObject;
}
}
} // namespace OHOS::Ace