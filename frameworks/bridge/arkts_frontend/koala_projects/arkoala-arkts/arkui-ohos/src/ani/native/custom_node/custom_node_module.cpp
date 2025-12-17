/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "custom_node_module.h"
#include "load.h"
#include "utils/ani_utils.h"
#include "log/log.h"

#include <memory>
 
namespace OHOS::Ace::Ani {
ani_object CreateInt(ani_env* env, ani_int value)
{
    ani_class cls;
    if (env->FindClass("std.core.Int", &cls) != ANI_OK) {
        return nullptr;
    }
    ani_method ctor;
    if (env->Class_FindMethod(cls, "<ctor>", "i:", &ctor) != ANI_OK) {
        return nullptr;
    }
    ani_object rs;
    if (env->Object_New(cls, ctor, &rs, value) != ANI_OK) {
        return nullptr;
    }
    return rs;
}
 
ani_long ConstructCustomNode(ani_env* env, [[maybe_unused]] ani_object aniClass,
                             ani_int id, ani_object obj)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return 0;
    }

    // ani_object obj from ts is supposed to be processed here
    ani_vm* vm = nullptr;
    env->GetVM(&vm);

    std::shared_ptr<ani_wref> weakRef(new ani_wref, [vm](ani_wref* wref) {
        ani_env* env = nullptr;
        vm->GetEnv(ANI_VERSION_1, &env);
        env->WeakReference_Delete(*wref);
    });

    env->WeakReference_Create(obj, weakRef.get());

    ani_type type;
    env->Object_GetType(obj, &type);

    static ani_ref customComponentObj = nullptr;
    if (!customComponentObj) {
        if (env->GlobalReference_Create(type, &customComponentObj) != ANI_OK) {
            HILOGE("Failed to create global reference");
        }
    }

    static ani_method onPageShowMethod = nullptr;
    if (!onPageShowMethod) {
        env->Class_FindMethod(static_cast<ani_class>(customComponentObj), "onPageShow", ":", &onPageShowMethod);
    }
    auto&& onPageShow = [vm, weakRef]() {
        ani_env* env = nullptr;
        vm->GetEnv(ANI_VERSION_1, &env);

        ani_boolean released;
        ani_ref localRef;
        env->WeakReference_GetReference(*weakRef, &released, &localRef);
        if (!released) {
            env->Object_CallMethod_Void(static_cast<ani_object>(localRef), onPageShowMethod);
            env->Reference_Delete(localRef);
        }
    };

    static ani_method onPageHideMethod = nullptr;
    if (!onPageHideMethod) {
        env->Class_FindMethod(static_cast<ani_class>(customComponentObj), "onPageHide", ":", &onPageHideMethod);
    }
    auto&& onPageHide = [vm, weakRef]() {
        ani_env* env = nullptr;
        vm->GetEnv(ANI_VERSION_1, &env);

        ani_boolean released;
        ani_ref localRef;
        env->WeakReference_GetReference(*weakRef, &released, &localRef);
        if (!released) {
            env->Object_CallMethod_Void(static_cast<ani_object>(localRef), onPageHideMethod);
            env->Reference_Delete(localRef);
        }
    };

    static ani_method onBackPressMethod = nullptr;
    if (!onBackPressMethod) {
        env->Class_FindMethod(static_cast<ani_class>(customComponentObj), "onBackPress", ":z", &onBackPressMethod);
    }
    auto&& onBackPress = [vm, weakRef]() {
        ani_env* env = nullptr;
        vm->GetEnv(ANI_VERSION_1, &env);

        ani_boolean released;
        ani_ref localRef;
        ani_boolean result = ani_boolean(false);
        env->WeakReference_GetReference(*weakRef, &released, &localRef);
        if (!released) {
            env->Object_CallMethod_Boolean(static_cast<ani_object>(localRef), onBackPressMethod, &result);
            env->Reference_Delete(localRef);
        }
        return result;
    };

    static ani_method pageTransitionMethod = nullptr;
    if (!pageTransitionMethod) {
        env->Class_FindMethod(static_cast<ani_class>(customComponentObj), "pageTransition", ":", &
            pageTransitionMethod);
    }
    auto pageTransition = [vm, weakRef]() {
        ani_env* env = nullptr;
        vm->GetEnv(ANI_VERSION_1, &env);
        ani_boolean released;
        ani_ref localRef;
        env->WeakReference_GetReference(*weakRef, &released, &localRef);
        if (!released) {
            env->Object_CallMethod_Void(static_cast<ani_object>(localRef), pageTransitionMethod);
            env->Reference_Delete(localRef);
        }
    };

    static ani_method onCleanupMethod = nullptr;
    if (!onCleanupMethod) {
        env->Class_FindMethod(static_cast<ani_class>(customComponentObj), "onCleanup", nullptr, &onCleanupMethod);
    }
    auto onCleanupFunc = [vm, weakRef]() {
        ani_env* env = nullptr;
        if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
            return;
        }
        ani_boolean released;
        ani_ref localRef;
        if (ANI_OK != env->WeakReference_GetReference(*weakRef, &released, &localRef)) {
            return;
        }

        if (!released) {
            env->Object_CallMethod_Void(static_cast<ani_object>(localRef), onCleanupMethod);
            env->Reference_Delete(localRef);
        }
    };

    static ani_method onDumpInspectorMethod = nullptr;
    if (!onDumpInspectorMethod) {
        env->Class_FindMethod(static_cast<ani_class>(customComponentObj), "onDumpInspector", ":C{std.core.String}", &
            onDumpInspectorMethod);
    }
    auto onDumpInspector = [vm, weakRef]() {
        ani_env *env = nullptr;
        vm->GetEnv(ANI_VERSION_1, &env);
        ani_boolean released;
        ani_ref localRef;
        ani_ref result{};
        env->WeakReference_GetReference(*weakRef, &released, &localRef);
        if (!released) {
            env->Object_CallMethod_Ref(static_cast<ani_object>(localRef), onDumpInspectorMethod, &result);
            env->Reference_Delete(localRef);
        }
        ani_string aniStr = static_cast<ani_string>(result);
        return AniUtils::ANIStringToStdString(env, aniStr);
    };

    static ani_method setActiveMethod = nullptr;
    if (!setActiveMethod) {
        env->Class_FindMethod(static_cast<ani_class>(customComponentObj), "setActiveInternal", "zz:", &
            setActiveMethod);
    }
    auto setActive = [vm, weakRef](bool a, bool b) {
        ani_env *env = nullptr;
        vm->GetEnv(ANI_VERSION_1, &env);
        ani_boolean released;
        ani_ref localRef;
        ani_boolean param1 = ani_boolean(a);
        ani_boolean param2 = ani_boolean(b);
        env->WeakReference_GetReference(*weakRef, &released, &localRef);
        if (!released) {
            env->Object_CallMethod_Void(static_cast<ani_object>(localRef), setActiveMethod, param1, param2);
            env->Reference_Delete(localRef);
        }
    };

    struct ArkUICustomNodeInfo customNodeInfo {
        .onPageShowFunc = std::move(onPageShow),
        .onPageHideFunc = std::move(onPageHide),
        .onBackPressedFunc = std::move(onBackPress),
        .pageTransitionFunc = std::move(pageTransition),
        .onCleanupFunc = std::move(onCleanupFunc),
        .onDumpInspectorFunc = std::move(onDumpInspector),
        .setActiveFunc = std::move(setActive),
    };
    
    ani_long customNode = modifier->getCustomNodeAniModifier()->constructCustomNode(id, std::move(customNodeInfo));
    return customNode;
}

void RequestFrame(ani_env* env)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }

    modifier->getCustomNodeAniModifier()->requestFrame();
    return;
}

ani_object QueryNavigationInfo(ani_env* env, [[maybe_unused]] ani_object, ani_long node)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return nullptr;
    }
    ArkUINavigationInfo info;
    modifier->getCustomNodeAniModifier()->queryNavigationInfo(node, info);

    ani_object res = {};
    static const char* className = "@ohos.arkui.observer.uiObserver.NavigationInfoImpl";
    ani_class cls;
    env->FindClass(className, &cls);
    ani_method navInfoCtor;
    env->Class_FindMethod(cls, "<ctor>", nullptr, &navInfoCtor);
    env->Object_New(cls, navInfoCtor, &res);

    // set navigationId
    std::string navigationId = info.navigationId;
    ani_string id_string{};
    env->String_NewUTF8(navigationId.c_str(), navigationId.size(), &id_string);
    env->Object_SetPropertyByName_Ref(res, "navigationId", id_string);
    
    // set pathStack
    ani_class interCls;
    env->FindClass("arkui.component.navigation.NavPathStackInternal", &interCls);
    ani_ref pathStack;
    env->Class_CallStaticMethodByName_Ref(interCls, "fromPtr", nullptr, &pathStack, info.navPathStack);
    env->Object_SetPropertyByName_Ref(res, "pathStack", static_cast<ani_object>(pathStack));
    return res;
}

ani_object QueryNavDestinationInfo(ani_env* env, [[maybe_unused]] ani_object, ani_long node)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return nullptr;
    }
    ArkUINavDestinationInfo info;
    modifier->getCustomNodeAniModifier()->queryNavDestinationInfo(node, info);

    ani_object res = {};
    static const char* className = "@ohos.arkui.observer.uiObserver.NavDestinationInfoImpl";
    ani_class cls;
    env->FindClass(className, &cls);
    ani_method routerInfoCtor;
    env->Class_FindMethod(cls, "<ctor>", nullptr, &routerInfoCtor);
    env->Object_New(cls, routerInfoCtor, &res);

    ani_object uniqueId_obj = CreateInt(env, info.uniqueId);
    env->Object_SetPropertyByName_Ref(res, "uniqueId", uniqueId_obj);
    env->Object_SetPropertyByName_Int(res, "index", info.index);

    ani_string navDesName {};
    env->String_NewUTF8(info.name.c_str(), info.name.size(), &navDesName);
    env->Object_SetPropertyByName_Ref(res, "name", navDesName);

    ani_string navDesId {};
    env->String_NewUTF8(info.navDestinationId.c_str(), info.navDestinationId.size(), &navDesId);
    env->Object_SetPropertyByName_Ref(res, "navDestinationId", navDesId);

    ani_string navigationId {};
    env->String_NewUTF8(info.navigationId.c_str(), info.navigationId.size(), &navigationId);
    env->Object_SetPropertyByName_Ref(res, "navigationId", navigationId);
    
    ani_enum navDesState;
    env->FindEnum("@ohos.arkui.observer.uiObserver.NavDestinationState", &navDesState);
    ani_enum_item navDesStateItem;
    env->Enum_GetEnumItemByIndex(navDesState, info.state, &navDesStateItem);
    env->Object_SetPropertyByName_Ref(res, "state", navDesStateItem);
    
    ani_enum navMode;
    env->FindEnum("@ohos.arkui.component.navDestination.NavDestinationMode", &navMode);
    ani_enum_item navModeItem;
    env->Enum_GetEnumItemByIndex(navMode, info.mode, &navModeItem);
    ani_int navModeInt;
    env->EnumItem_GetValue_Int(navModeItem, &navModeInt);
    ani_object mode_obj = CreateInt(env, navModeInt);
    env->Object_SetPropertyByName_Ref(res, "mode", mode_obj);
    return res;
}

ani_object QueryNavDestinationInfo0(ani_env* env, [[maybe_unused]] ani_object, ani_long node, ani_boolean isInner)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return nullptr;
    }
    ArkUINavDestinationInfo info;
    modifier->getCustomNodeAniModifier()->queryNavDestinationInfo0(node, info, isInner);

    ani_object res = {};
    static const char* className = "@ohos.arkui.observer.uiObserver.NavDestinationInfoImpl";
    ani_class cls;
    env->FindClass(className, &cls);
    ani_method routerInfoCtor;
    env->Class_FindMethod(cls, "<ctor>", nullptr, &routerInfoCtor);
    env->Object_New(cls, routerInfoCtor, &res);

    ani_object uniqueId_obj = CreateInt(env, info.uniqueId);
    env->Object_SetPropertyByName_Ref(res, "uniqueId", uniqueId_obj);
    env->Object_SetPropertyByName_Int(res, "index", info.index);

    ani_string navDesName {};
    env->String_NewUTF8(info.name.c_str(), info.name.size(), &navDesName);
    env->Object_SetPropertyByName_Ref(res, "name", navDesName);

    ani_string navDesId {};
    env->String_NewUTF8(info.navDestinationId.c_str(), info.navDestinationId.size(), &navDesId);
    env->Object_SetPropertyByName_Ref(res, "navDestinationId", navDesId);

    ani_string navigationId {};
    env->String_NewUTF8(info.navigationId.c_str(), info.navigationId.size(), &navigationId);
    env->Object_SetPropertyByName_Ref(res, "navigationId", navigationId);
    
    ani_enum navDesState;
    env->FindEnum("@ohos.arkui.observer.uiObserver.NavDestinationState", &navDesState);
    ani_enum_item navDesStateItem;
    env->Enum_GetEnumItemByIndex(navDesState, info.state, &navDesStateItem);
    env->Object_SetPropertyByName_Ref(res, "state", navDesStateItem);
    
    ani_enum navMode;
    env->FindEnum("@ohos.arkui.component.navDestination.NavDestinationMode", &navMode);
    ani_enum_item navModeItem;
    env->Enum_GetEnumItemByIndex(navMode, info.mode, &navModeItem);
    ani_int navModeInt;
    env->EnumItem_GetValue_Int(navModeItem, &navModeInt);
    ani_object mode_obj = CreateInt(env, navModeInt);
    env->Object_SetPropertyByName_Ref(res, "mode", mode_obj);
    return res;
}

ani_object QueryNavDestinationInfo1(ani_env* env, [[maybe_unused]] ani_object, ani_int uniqueId)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return nullptr;
    }
    ArkUINavDestinationInfo info;
    bool isNull = !modifier->getCustomNodeAniModifier()->queryNavDestinationInfo1(uniqueId, info);
    if (isNull) {
        return nullptr;
    }
    ani_object res = {};
    static const char* className = "@ohos.arkui.observer.uiObserver.NavDestinationInfoImpl";
    ani_class cls;
    env->FindClass(className, &cls);
    ani_method routerInfoCtor;
    env->Class_FindMethod(cls, "<ctor>", nullptr, &routerInfoCtor);
    env->Object_New(cls, routerInfoCtor, &res);
    ani_object uniqueId_obj = CreateInt(env, info.uniqueId);
    env->Object_SetPropertyByName_Ref(res, "uniqueId", uniqueId_obj);
    env->Object_SetPropertyByName_Int(res, "index", info.index);
    ani_string navDesName {};
    env->String_NewUTF8(info.name.c_str(), info.name.size(), &navDesName);
    env->Object_SetPropertyByName_Ref(res, "name", navDesName);
    ani_string navDesId {};
    env->String_NewUTF8(info.navDestinationId.c_str(), info.navDestinationId.size(), &navDesId);
    env->Object_SetPropertyByName_Ref(res, "navDestinationId", navDesId);
    ani_string navigationId {};
    env->String_NewUTF8(info.navigationId.c_str(), info.navigationId.size(), &navigationId);
    env->Object_SetPropertyByName_Ref(res, "navigationId", navigationId);
    ani_enum navDesState;
    env->FindEnum("@ohos.arkui.observer.uiObserver.NavDestinationState", &navDesState);
    ani_enum_item navDesStateItem;
    env->Enum_GetEnumItemByIndex(navDesState, info.state, &navDesStateItem);
    env->Object_SetPropertyByName_Ref(res, "state", navDesStateItem);
    ani_enum navMode;
    env->FindEnum("@ohos.arkui.component.navDestination.NavDestinationMode", &navMode);
    ani_enum_item navModeItem;
    env->Enum_GetEnumItemByIndex(navMode, info.mode, &navModeItem);

    ani_int navModeInt;
    env->EnumItem_GetValue_Int(navModeItem, &navModeInt);
    ani_object mode_obj = CreateInt(env, navModeInt);
    env->Object_SetPropertyByName_Ref(res, "mode", mode_obj);
    return res;
}

ani_object QueryRouterPageInfo1(ani_env* env, [[maybe_unused]] ani_object, ani_int uniqueId)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return nullptr;
    }
    ArkUIRouterPageInfo info;
    bool isNull = !modifier->getCustomNodeAniModifier()->queryRouterPageInfo1(uniqueId, info);
    if (isNull) {
        return nullptr;
    }
    ani_object res = {};
    static const char* className = "@ohos.arkui.observer.uiObserver.RouterPageInfo";
    ani_class cls;
    env->FindClass(className, &cls);
    ani_method routerInfoCtor;
    env->Class_FindMethod(cls, "<ctor>", nullptr, &routerInfoCtor);
    env->Object_New(cls, routerInfoCtor, &res);

    env->Object_SetPropertyByName_Double(res, "index", static_cast<ani_double>(info.index));

    ani_string pageName {};
    env->String_NewUTF8(info.name.c_str(), info.name.size(), &pageName);
    env->Object_SetPropertyByName_Ref(res, "name", pageName);

    ani_string pagePath {};
    env->String_NewUTF8(info.path.c_str(), info.path.size(), &pagePath);
    env->Object_SetPropertyByName_Ref(res, "path", pagePath);
    env->Object_SetPropertyByName_Int(res, "state", static_cast<ani_int>(info.state));

    ani_string aniPageId {};
    env->String_NewUTF8(info.pageId.c_str(), info.pageId.size(), &aniPageId);
    env->Object_SetPropertyByName_Ref(res, "pageId", aniPageId);

    ani_enum routerPageState;
    env->FindEnum("@ohos.arkui.observer.uiObserver.RouterPageState", &routerPageState);
    ani_enum_item enumItem;
    env->Enum_GetEnumItemByIndex(routerPageState, info.state, &enumItem);
    env->Object_SetPropertyByName_Ref(res, "state", enumItem);
    return res;
}

ani_object QueryRouterPageInfo(ani_env* env, [[maybe_unused]] ani_object, ani_long node)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return nullptr;
    }
    ArkUIRouterPageInfo info;
    modifier->getCustomNodeAniModifier()->queryRouterPageInfo(node, info);

    ani_object res = {};
    static const char* className = "@ohos.arkui.observer.uiObserver.RouterPageInfo";
    ani_class cls;
    env->FindClass(className, &cls);
    ani_method routerInfoCtor;
    env->Class_FindMethod(cls, "<ctor>", nullptr, &routerInfoCtor);
    env->Object_New(cls, routerInfoCtor, &res);

    env->Object_SetPropertyByName_Double(res, "index", static_cast<ani_double>(info.index));

    ani_string pageName{};
    env->String_NewUTF8(info.name.c_str(), info.name.size(), &pageName);
    env->Object_SetPropertyByName_Ref(res, "name", pageName);

    ani_string pagePath{};
    env->String_NewUTF8(info.path.c_str(), info.path.size(), &pagePath);
    env->Object_SetPropertyByName_Ref(res, "path", pagePath);
    env->Object_SetPropertyByName_Int(res, "state", static_cast<ani_int>(info.state));

    ani_string aniPageId{};
    env->String_NewUTF8(info.pageId.c_str(), info.pageId.size(), &aniPageId);
    env->Object_SetPropertyByName_Ref(res, "pageId", aniPageId);

    ani_enum routerPageState;
    env->FindEnum("@ohos.arkui.observer.uiObserver.RouterPageState", &routerPageState);
    ani_enum_item enumItem;
    env->Enum_GetEnumItemByIndex(routerPageState, info.state, &enumItem);
    env->Object_SetPropertyByName_Ref(res, "state", enumItem);

    return res;
}

void OnReuse(ani_env* env, [[maybe_unused]] ani_object, ani_long node)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }

    modifier->getCustomNodeAniModifier()->onReuse(node);
    return;
}

void OnRecycle(ani_env* env, [[maybe_unused]] ani_object, ani_long node)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }

    modifier->getCustomNodeAniModifier()->onRecycle(node);
    return;
}
} // namespace OHOS::Ace::Ani
