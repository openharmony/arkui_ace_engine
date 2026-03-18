/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "gesture_event_uiobserver_module.h"
#include "base/utils/utils.h"
#include "load.h"
#include "utils/ani_utils.h"
#include <mutex>
#include <string>
#include <map>

namespace OHOS::Ace::Ani {

namespace {
void ReleaseGlobalRef(ani_env* env, ani_ref& ref)
{
    if (env != nullptr && ref != nullptr) {
        env->GlobalReference_Delete(ref);
        ref = nullptr;
    }
}
}

constexpr int32_t GESTURE_TYPE_MIN = 0;
constexpr int32_t GESTURE_TYPE_MAX = 5;

struct CallbackResourceInfo {
    int32_t instanceId;
    int32_t resourceId;
    std::string tag;
    int32_t type;
};

static std::mutex g_panListenerMutex;
static std::mutex g_clickListenerMutex;
static std::mutex g_globalGestureListenerMutex;

static std::map<ani_ref, CallbackResourceInfo> beforePanStartListenerCallbackMap = {};
static std::map<ani_ref, CallbackResourceInfo> beforePanEndListenerCallbackMap = {};
static std::map<ani_ref, CallbackResourceInfo> afterPanStartListenerCallbackMap = {};
static std::map<ani_ref, CallbackResourceInfo> afterPanEndListenerCallbackMap = {};

static std::map<ani_ref, CallbackResourceInfo> willClickListenerCallbackMap = {};
static std::map<ani_ref, CallbackResourceInfo> didClickListenerCallbackMap = {};
static std::map<ani_ref, CallbackResourceInfo> willTapListenerCallbackMap = {};
static std::map<ani_ref, CallbackResourceInfo> didTapListenerCallbackMap = {};
static std::map<ani_ref, CallbackResourceInfo> globalGestureListenerCallbackMap = {};

void RegisterBeforePanStartCallback(ani_env* env, CallbackResourceInfo info, ani_ref& callback)
{
    CHECK_NULL_VOID(env);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    std::lock_guard<std::mutex> lock(g_panListenerMutex);
    for (auto it = beforePanStartListenerCallbackMap.begin(); it != beforePanStartListenerCallbackMap.end();) {
        ani_boolean isEquals = false;
        env->Reference_StrictEquals(callback, it->first, &isEquals);
        if (!isEquals) {
            ++it;
            continue;
        }
        modifier->getArkUIAniGestureEventUIObserverModifier()->removePanListenerCallback(
            info.tag, it->second.instanceId, it->second.resourceId, false);
        env->GlobalReference_Delete(it->first);
        it = beforePanStartListenerCallbackMap.erase(it);
        break;
    }
    beforePanStartListenerCallbackMap[callback] = info;
}

void RegisterBeforePanEndCallback(ani_env* env, CallbackResourceInfo info, ani_ref& callback)
{
    CHECK_NULL_VOID(env);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    std::lock_guard<std::mutex> lock(g_panListenerMutex);
    for (auto it = beforePanEndListenerCallbackMap.begin(); it != beforePanEndListenerCallbackMap.end();) {
        ani_boolean isEquals = false;
        env->Reference_StrictEquals(callback, it->first, &isEquals);
        if (!isEquals) {
            ++it;
            continue;
        }
        modifier->getArkUIAniGestureEventUIObserverModifier()->removePanListenerCallback(
            info.tag, it->second.instanceId, it->second.resourceId, false);
        env->GlobalReference_Delete(it->first);
        it = beforePanEndListenerCallbackMap.erase(it);
        break;
    }
    beforePanEndListenerCallbackMap[callback] = info;
}

void RegisterAfterPanStartCallback(ani_env* env, CallbackResourceInfo info, ani_ref& callback)
{
    CHECK_NULL_VOID(env);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    std::lock_guard<std::mutex> lock(g_panListenerMutex);
    for (auto it = afterPanStartListenerCallbackMap.begin(); it != afterPanStartListenerCallbackMap.end();) {
        ani_boolean isEquals = false;
        env->Reference_StrictEquals(callback, it->first, &isEquals);
        if (!isEquals) {
            ++it;
            continue;
        }
        modifier->getArkUIAniGestureEventUIObserverModifier()->removePanListenerCallback(
            info.tag, it->second.instanceId, it->second.resourceId, false);
        env->GlobalReference_Delete(it->first);
        it = afterPanStartListenerCallbackMap.erase(it);
        break;
    }
    afterPanStartListenerCallbackMap[callback] = info;
}

void RegisterAfterPanEndCallback(ani_env* env, CallbackResourceInfo info, ani_ref& callback)
{
    CHECK_NULL_VOID(env);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    std::lock_guard<std::mutex> lock(g_panListenerMutex);
    for (auto it = afterPanEndListenerCallbackMap.begin(); it != afterPanEndListenerCallbackMap.end();) {
        ani_boolean isEquals = false;
        env->Reference_StrictEquals(callback, it->first, &isEquals);
        if (!isEquals) {
            ++it;
            continue;
        }
        modifier->getArkUIAniGestureEventUIObserverModifier()->removePanListenerCallback(
            info.tag, it->second.instanceId, it->second.resourceId, false);
        env->GlobalReference_Delete(it->first);
        it = afterPanEndListenerCallbackMap.erase(it);
        break;
    }
    afterPanEndListenerCallbackMap[callback] = info;
}

void RegisterWillClickCallback(ani_env* env, CallbackResourceInfo info, ani_ref& callback)
{
    CHECK_NULL_VOID(env);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    std::lock_guard<std::mutex> lock(g_clickListenerMutex);
    for (auto it = willClickListenerCallbackMap.begin(); it != willClickListenerCallbackMap.end();) {
        ani_boolean isEquals = false;
        env->Reference_StrictEquals(callback, it->first, &isEquals);
        if (!isEquals) {
            ++it;
            continue;
        }
        modifier->getArkUIAniGestureEventUIObserverModifier()->removeClickListenerCallback(
            info.tag, it->second.instanceId, it->second.resourceId, false);
        env->GlobalReference_Delete(it->first);
        it = willClickListenerCallbackMap.erase(it);
        break;
    }
    willClickListenerCallbackMap[callback] = info;
}

void RegisterDidClickCallback(ani_env* env, CallbackResourceInfo info, ani_ref& callback)
{
    CHECK_NULL_VOID(env);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    std::lock_guard<std::mutex> lock(g_clickListenerMutex);
    for (auto it = didClickListenerCallbackMap.begin(); it != didClickListenerCallbackMap.end();) {
        ani_boolean isEquals = false;
        env->Reference_StrictEquals(callback, it->first, &isEquals);
        if (!isEquals) {
            ++it;
            continue;
        }
        modifier->getArkUIAniGestureEventUIObserverModifier()->removeClickListenerCallback(
            info.tag, it->second.instanceId, it->second.resourceId, false);
        env->GlobalReference_Delete(it->first);
        it = didClickListenerCallbackMap.erase(it);
    }
    didClickListenerCallbackMap[callback] = info;
}

void RegisterWillTapCallback(ani_env* env, CallbackResourceInfo info, ani_ref& callback)
{
    CHECK_NULL_VOID(env);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    std::lock_guard<std::mutex> lock(g_clickListenerMutex);
    for (auto it = willTapListenerCallbackMap.begin(); it != willTapListenerCallbackMap.end();) {
        ani_boolean isEquals = false;
        env->Reference_StrictEquals(callback, it->first, &isEquals);
        if (!isEquals) {
            ++it;
            continue;
        }
        modifier->getArkUIAniGestureEventUIObserverModifier()->removeTapListenerCallback(
            info.tag, it->second.instanceId, it->second.resourceId, false);
        env->GlobalReference_Delete(it->first);
        it = willTapListenerCallbackMap.erase(it);
    }
    willTapListenerCallbackMap[callback] = info;
}

void RegisterDidTapCallback(ani_env* env, CallbackResourceInfo info, ani_ref& callback)
{
    CHECK_NULL_VOID(env);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    std::lock_guard<std::mutex> lock(g_clickListenerMutex);
    for (auto it = didTapListenerCallbackMap.begin(); it != didTapListenerCallbackMap.end();) {
        ani_boolean isEquals = false;
        env->Reference_StrictEquals(callback, it->first, &isEquals);
        if (!isEquals) {
            ++it;
            continue;
        }
        modifier->getArkUIAniGestureEventUIObserverModifier()->removeTapListenerCallback(
            info.tag, it->second.instanceId, it->second.resourceId, false);
        env->GlobalReference_Delete(it->first);
        it = didTapListenerCallbackMap.erase(it);
    }
    didTapListenerCallbackMap[callback] = info;
}

void RegisterGlobalGestureListenerCallback(ani_env* env, CallbackResourceInfo info, ani_ref& callback)
{
    CHECK_NULL_VOID(env);
    std::lock_guard<std::mutex> lock(g_globalGestureListenerMutex);
    for (auto it = globalGestureListenerCallbackMap.begin(); it != globalGestureListenerCallbackMap.end();) {
        ani_boolean isEquals = false;
        env->Reference_StrictEquals(callback, it->first, &isEquals);
        if (!isEquals) {
            ++it;
            continue;
        }
        env->GlobalReference_Delete(it->first);
        it = globalGestureListenerCallbackMap.erase(it);
        break;
    }
    if (callback != nullptr) {
        globalGestureListenerCallbackMap[callback] = info;
    }
}

void UnregisterGlobalGestureCallback(ani_env* env, ani_int type, ani_ref& callback)
{
    CHECK_NULL_VOID(env);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    std::lock_guard<std::mutex> lock(g_globalGestureListenerMutex);

    ani_boolean isUndef = false;
    env->Reference_IsUndefined(callback, &isUndef);
    if (isUndef || !callback) {
        for (auto it = globalGestureListenerCallbackMap.begin(); it != globalGestureListenerCallbackMap.end();) {
            if (it->second.type == type) {
                modifier->getArkUIAniGestureEventUIObserverModifier()->removeGlobalGestureListenerCallback(
                    static_cast<int32_t>(type), it->second.resourceId, false);
                env->GlobalReference_Delete(it->first);
                it = globalGestureListenerCallbackMap.erase(it);
            } else {
                ++it;
            }
        }
        return;
    }

    for (auto it = globalGestureListenerCallbackMap.begin(); it != globalGestureListenerCallbackMap.end();) {
        ani_boolean isEquals = false;
        env->Reference_StrictEquals(callback, it->first, &isEquals);
        if (isEquals && it->second.type == type) {
            modifier->getArkUIAniGestureEventUIObserverModifier()->removeGlobalGestureListenerCallback(
                static_cast<int32_t>(type), it->second.resourceId, false);
            env->GlobalReference_Delete(it->first);
            it = globalGestureListenerCallbackMap.erase(it);
        } else {
            ++it;
        }
    }
}

void UnregisterBeforePanStartCallback(ani_env* env, ani_int instanceId, const std::string& tag, ani_ref& callback)
{
    CHECK_NULL_VOID(env);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    std::lock_guard<std::mutex> lock(g_panListenerMutex);
    ani_boolean isUndef = false;
    env->Reference_IsUndefined(callback, &isUndef);
    if (isUndef || !callback) {
        for (auto it = beforePanStartListenerCallbackMap.begin(); it != beforePanStartListenerCallbackMap.end();) {
            if (it->second.instanceId == instanceId) {
                modifier->getArkUIAniGestureEventUIObserverModifier()->removePanListenerCallback(
                    tag, it->second.instanceId, it->second.resourceId, false);
                env->GlobalReference_Delete(it->first);
                it = beforePanStartListenerCallbackMap.erase(it);
            } else {
                ++it;
            }
        }
        return;
    }
    for (auto it = beforePanStartListenerCallbackMap.begin(); it != beforePanStartListenerCallbackMap.end();) {
        ani_boolean isEquals = false;
        env->Reference_StrictEquals(callback, it->first, &isEquals);
        if (isEquals && it->second.instanceId == instanceId) {
            modifier->getArkUIAniGestureEventUIObserverModifier()->removePanListenerCallback(
                tag, it->second.instanceId, it->second.resourceId, false);
            env->GlobalReference_Delete(it->first);
            it = beforePanStartListenerCallbackMap.erase(it);
        } else {
            ++it;
        }
    }
}

void UnregisterBeforePanEndCallback(ani_env* env, ani_int instanceId, const std::string& tag, ani_ref& callback)
{
    CHECK_NULL_VOID(env);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    std::lock_guard<std::mutex> lock(g_panListenerMutex);
    ani_boolean isUndef = false;
    env->Reference_IsUndefined(callback, &isUndef);
    if (isUndef || !callback) {
        for (auto it = beforePanEndListenerCallbackMap.begin(); it != beforePanEndListenerCallbackMap.end();) {
            if (it->second.instanceId == instanceId) {
                modifier->getArkUIAniGestureEventUIObserverModifier()->removePanListenerCallback(
                    tag, it->second.instanceId, it->second.resourceId, false);
                env->GlobalReference_Delete(it->first);
                it = beforePanEndListenerCallbackMap.erase(it);
            } else {
                ++it;
            }
        }
        return;
    }
    for (auto it = beforePanEndListenerCallbackMap.begin(); it != beforePanEndListenerCallbackMap.end();) {
        ani_boolean isEquals = false;
        env->Reference_StrictEquals(callback, it->first, &isEquals);
        if (isEquals && it->second.instanceId == instanceId) {
            modifier->getArkUIAniGestureEventUIObserverModifier()->removePanListenerCallback(
                tag, it->second.instanceId, it->second.resourceId, false);
            env->GlobalReference_Delete(it->first);
            it = beforePanEndListenerCallbackMap.erase(it);
        } else {
            ++it;
        }
    }
}

void UnregisterAfterPanStartCallback(ani_env* env, ani_int instanceId, const std::string& tag, ani_ref& callback)
{
    CHECK_NULL_VOID(env);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    std::lock_guard<std::mutex> lock(g_panListenerMutex);
    ani_boolean isUndef = false;
    env->Reference_IsUndefined(callback, &isUndef);
    if (isUndef || !callback) {
        for (auto it = afterPanStartListenerCallbackMap.begin(); it != afterPanStartListenerCallbackMap.end();) {
            if (it->second.instanceId == instanceId) {
                modifier->getArkUIAniGestureEventUIObserverModifier()->removePanListenerCallback(
                    tag, it->second.instanceId, it->second.resourceId, false);
                env->GlobalReference_Delete(it->first);
                it = afterPanStartListenerCallbackMap.erase(it);
            } else {
                ++it;
            }
        }
        return;
    }
    for (auto it = afterPanStartListenerCallbackMap.begin(); it != afterPanStartListenerCallbackMap.end();) {
        ani_boolean isEquals = false;
        env->Reference_StrictEquals(callback, it->first, &isEquals);
        if (isEquals && it->second.instanceId == instanceId) {
            modifier->getArkUIAniGestureEventUIObserverModifier()->removePanListenerCallback(
                tag, it->second.instanceId, it->second.resourceId, false);
            env->GlobalReference_Delete(it->first);
            it = afterPanStartListenerCallbackMap.erase(it);
        } else {
            ++it;
        }
    }
}

void UnregisterAfterPanEndCallback(ani_env* env, ani_int instanceId, const std::string& tag, ani_ref& callback)
{
    CHECK_NULL_VOID(env);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    std::lock_guard<std::mutex> lock(g_panListenerMutex);
    ani_boolean isUndef = false;
    env->Reference_IsUndefined(callback, &isUndef);
    if (isUndef || !callback) {
        for (auto it = afterPanEndListenerCallbackMap.begin(); it != afterPanEndListenerCallbackMap.end();) {
            if (it->second.instanceId == instanceId) {
                modifier->getArkUIAniGestureEventUIObserverModifier()->removePanListenerCallback(
                    tag, it->second.instanceId, it->second.resourceId, false);
                env->GlobalReference_Delete(it->first);
                it = afterPanEndListenerCallbackMap.erase(it);
            } else {
                ++it;
            }
        }
        return;
    }
    for (auto it = afterPanEndListenerCallbackMap.begin(); it != afterPanEndListenerCallbackMap.end();) {
        ani_boolean isEquals = false;
        env->Reference_StrictEquals(callback, it->first, &isEquals);
        if (isEquals && it->second.instanceId == instanceId) {
            modifier->getArkUIAniGestureEventUIObserverModifier()->removePanListenerCallback(
                tag, it->second.instanceId, it->second.resourceId, false);
            env->GlobalReference_Delete(it->first);
            it = afterPanEndListenerCallbackMap.erase(it);
        } else {
            ++it;
        }
    }
}

void UnregisterWillClickCallback(ani_env* env, ani_int instanceId, const std::string& tag, ani_ref& callback)
{
    CHECK_NULL_VOID(env);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    std::lock_guard<std::mutex> lock(g_clickListenerMutex);
    ani_boolean isUndef = false;
    env->Reference_IsUndefined(callback, &isUndef);
    if (isUndef || !callback) {
        for (auto it = willClickListenerCallbackMap.begin(); it != willClickListenerCallbackMap.end();) {
            if (it->second.instanceId == instanceId) {
                modifier->getArkUIAniGestureEventUIObserverModifier()->removeClickListenerCallback(
                    tag, it->second.instanceId, it->second.resourceId, false);
                env->GlobalReference_Delete(it->first);
                it = willClickListenerCallbackMap.erase(it);
            } else {
                ++it;
            }
        }
        return;
    }
    for (auto it = willClickListenerCallbackMap.begin(); it != willClickListenerCallbackMap.end();) {
        ani_boolean isEquals = false;
        env->Reference_StrictEquals(callback, it->first, &isEquals);
        if (isEquals && it->second.instanceId == instanceId) {
            modifier->getArkUIAniGestureEventUIObserverModifier()->removeClickListenerCallback(
                tag, it->second.instanceId, it->second.resourceId, false);
            env->GlobalReference_Delete(it->first);
            it = willClickListenerCallbackMap.erase(it);
        } else {
            ++it;
        }
    }
}

void UnregisterDidClickCallback(ani_env* env, ani_int instanceId, const std::string& tag, ani_ref& callback)
{
    CHECK_NULL_VOID(env);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    std::lock_guard<std::mutex> lock(g_clickListenerMutex);
    ani_boolean isUndef = false;
    env->Reference_IsUndefined(callback, &isUndef);
    if (isUndef || !callback) {
        for (auto it = didClickListenerCallbackMap.begin(); it != didClickListenerCallbackMap.end();) {
            if (it->second.instanceId == instanceId) {
                modifier->getArkUIAniGestureEventUIObserverModifier()->removeClickListenerCallback(
                    tag, it->second.instanceId, it->second.resourceId, false);
                env->GlobalReference_Delete(it->first);
                it = didClickListenerCallbackMap.erase(it);
            } else {
                ++it;
            }
        }
        return;
    }
    for (auto it = didClickListenerCallbackMap.begin(); it != didClickListenerCallbackMap.end();) {
        ani_boolean isEquals = false;
        env->Reference_StrictEquals(callback, it->first, &isEquals);
        if (isEquals && it->second.instanceId == instanceId) {
            modifier->getArkUIAniGestureEventUIObserverModifier()->removeClickListenerCallback(
                tag, it->second.instanceId, it->second.resourceId, false);
            env->GlobalReference_Delete(it->first);
            it = didClickListenerCallbackMap.erase(it);
        } else {
            ++it;
        }
    }
}

void UnregisterWillTapCallback(ani_env* env, ani_int instanceId, const std::string& tag, ani_ref& callback)
{
    CHECK_NULL_VOID(env);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    std::lock_guard<std::mutex> lock(g_clickListenerMutex);
    ani_boolean isUndef = false;
    env->Reference_IsUndefined(callback, &isUndef);
    if (isUndef || !callback) {
        for (auto it = willTapListenerCallbackMap.begin(); it != willTapListenerCallbackMap.end();) {
            if (it->second.instanceId == instanceId) {
                modifier->getArkUIAniGestureEventUIObserverModifier()->removeTapListenerCallback(
                    tag, it->second.instanceId, it->second.resourceId, false);
                env->GlobalReference_Delete(it->first);
                it = willTapListenerCallbackMap.erase(it);
            } else {
                ++it;
            }
        }
        return;
    }
    for (auto it = willTapListenerCallbackMap.begin(); it != willTapListenerCallbackMap.end();) {
        ani_boolean isEquals = false;
        env->Reference_StrictEquals(callback, it->first, &isEquals);
        if (isEquals && it->second.instanceId == instanceId) {
            modifier->getArkUIAniGestureEventUIObserverModifier()->removeTapListenerCallback(
                tag, it->second.instanceId, it->second.resourceId, false);
            env->GlobalReference_Delete(it->first);
            it = willTapListenerCallbackMap.erase(it);
        } else {
            ++it;
        }
    }
}

void UnregisterDidTapCallback(ani_env* env, ani_int instanceId, const std::string& tag, ani_ref& callback)
{
    CHECK_NULL_VOID(env);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    std::lock_guard<std::mutex> lock(g_clickListenerMutex);
    ani_boolean isUndef = false;
    env->Reference_IsUndefined(callback, &isUndef);
    if (isUndef || !callback) {
        for (auto it = didTapListenerCallbackMap.begin(); it != didTapListenerCallbackMap.end();) {
            if (it->second.instanceId == instanceId) {
                modifier->getArkUIAniGestureEventUIObserverModifier()->removeTapListenerCallback(
                    tag, it->second.instanceId, it->second.resourceId, false);
                env->GlobalReference_Delete(it->first);
                it = didTapListenerCallbackMap.erase(it);
            } else {
                ++it;
            }
        }
        return;
    }
    for (auto it = didTapListenerCallbackMap.begin(); it != didTapListenerCallbackMap.end();) {
        ani_boolean isEquals = false;
        env->Reference_StrictEquals(callback, it->first, &isEquals);
        if (isEquals && it->second.instanceId == instanceId) {
            modifier->getArkUIAniGestureEventUIObserverModifier()->removeTapListenerCallback(
                tag, it->second.instanceId, it->second.resourceId, false);
            env->GlobalReference_Delete(it->first);
            it = didTapListenerCallbackMap.erase(it);
        } else {
            ++it;
        }
    }
}

void SetPanListenerCallback(ani_env* env, [[maybe_unused]] ani_object aniClass,
    ani_int instanceId, ani_int resourceId, ani_string tag, ani_fn_object fnObj)
{
    CHECK_NULL_VOID(env);
    auto tagStr = AniUtils::ANIStringToStdString(env, tag);
    ani_ref fnObjGlobalRef = nullptr;
    env->GlobalReference_Create(reinterpret_cast<ani_ref>(fnObj), &fnObjGlobalRef);

    CallbackResourceInfo info;
    info.instanceId = static_cast<int32_t>(instanceId);
    info.resourceId = static_cast<int32_t>(resourceId);
    info.tag = tagStr;
    if (tagStr == "beforePanStart") {
        RegisterBeforePanStartCallback(env, info, fnObjGlobalRef);
    } else if (tagStr == "beforePanEnd") {
        RegisterBeforePanEndCallback(env, info, fnObjGlobalRef);
    } else if (tagStr == "afterPanStart") {
        RegisterAfterPanStartCallback(env, info, fnObjGlobalRef);
    } else if (tagStr == "afterPanEnd") {
        RegisterAfterPanEndCallback(env, info, fnObjGlobalRef);
    }
}

void RemovePanListenerCallback(ani_env* env, [[maybe_unused]] ani_object aniClass,
    ani_int instanceId, ani_string tag, ani_fn_object fnObj)
{
    CHECK_NULL_VOID(env);
    auto tagStr = AniUtils::ANIStringToStdString(env, tag);
    ani_ref fnObjGlobalRef = nullptr;
    env->GlobalReference_Create(reinterpret_cast<ani_ref>(fnObj), &fnObjGlobalRef);

    if (tagStr == "beforePanStart") {
        UnregisterBeforePanStartCallback(env, instanceId, tagStr, fnObjGlobalRef);
    } else if (tagStr == "beforePanEnd") {
        UnregisterBeforePanEndCallback(env, instanceId, tagStr, fnObjGlobalRef);
    } else if (tagStr == "afterPanStart") {
        UnregisterAfterPanStartCallback(env, instanceId, tagStr, fnObjGlobalRef);
    } else if (tagStr == "afterPanEnd") {
        UnregisterAfterPanEndCallback(env, instanceId, tagStr, fnObjGlobalRef);
    }
    ReleaseGlobalRef(env, fnObjGlobalRef);
}

void SetClickListenerCallback(ani_env* env, [[maybe_unused]] ani_object aniClass,
    ani_int instanceId, ani_int resourceId, ani_string tag, ani_fn_object fnObj)
{
    CHECK_NULL_VOID(env);
    auto tagStr = AniUtils::ANIStringToStdString(env, tag);
    ani_ref fnObjGlobalRef = nullptr;
    env->GlobalReference_Create(reinterpret_cast<ani_ref>(fnObj), &fnObjGlobalRef);

    CallbackResourceInfo info;
    info.instanceId = static_cast<int32_t>(instanceId);
    info.resourceId = static_cast<int32_t>(resourceId);
    info.tag = tagStr;
    if (tagStr == "willClick") {
        RegisterWillClickCallback(env, info, fnObjGlobalRef);
    } else if (tagStr == "didClick") {
        RegisterDidClickCallback(env, info, fnObjGlobalRef);
    }
}

void RemoveClickListenerCallback(ani_env* env, [[maybe_unused]] ani_object aniClass,
    ani_int instanceId, ani_string tag, ani_fn_object fnObj)
{
    CHECK_NULL_VOID(env);
    auto tagStr = AniUtils::ANIStringToStdString(env, tag);
    ani_ref fnObjGlobalRef = nullptr;
    env->GlobalReference_Create(reinterpret_cast<ani_ref>(fnObj), &fnObjGlobalRef);

    if (tagStr == "willClick") {
        UnregisterWillClickCallback(env, instanceId, tagStr, fnObjGlobalRef);
    } else if (tagStr == "didClick") {
        UnregisterDidClickCallback(env, instanceId, tagStr, fnObjGlobalRef);
    }
    ReleaseGlobalRef(env, fnObjGlobalRef);
}

void SetTapListenerCallback(ani_env* env, [[maybe_unused]] ani_object aniClass,
    ani_int instanceId, ani_int resourceId, ani_string tag, ani_fn_object fnObj)
{
    CHECK_NULL_VOID(env);
    auto tagStr = AniUtils::ANIStringToStdString(env, tag);
    ani_ref fnObjGlobalRef = nullptr;
    env->GlobalReference_Create(reinterpret_cast<ani_ref>(fnObj), &fnObjGlobalRef);

    CallbackResourceInfo info;
    info.instanceId = static_cast<int32_t>(instanceId);
    info.resourceId = static_cast<int32_t>(resourceId);
    info.tag = tagStr;
    if (tagStr == "willTap") {
        RegisterWillTapCallback(env, info, fnObjGlobalRef);
    } else if (tagStr == "didTap") {
        RegisterDidTapCallback(env, info, fnObjGlobalRef);
    }
}

void RemoveTapListenerCallback(ani_env* env, [[maybe_unused]] ani_object aniClass,
    ani_int instanceId, ani_string tag, ani_fn_object fnObj)
{
    CHECK_NULL_VOID(env);
    auto tagStr = AniUtils::ANIStringToStdString(env, tag);
    ani_ref fnObjGlobalRef = nullptr;
    env->GlobalReference_Create(reinterpret_cast<ani_ref>(fnObj), &fnObjGlobalRef);

    if (tagStr == "willTap") {
        UnregisterWillTapCallback(env, instanceId, tagStr, fnObjGlobalRef);
    } else if (tagStr == "didTap") {
        UnregisterDidTapCallback(env, instanceId, tagStr, fnObjGlobalRef);
    }
    ReleaseGlobalRef(env, fnObjGlobalRef);
}

void AddGlobalGestureListener(ani_env* env, [[maybe_unused]] ani_object aniClass,
    ani_int resourceId, ani_int type, ani_fn_object fnObj)
{
    CHECK_NULL_VOID(env);

    int32_t gestureType = static_cast<int32_t>(type);
    if (gestureType < GESTURE_TYPE_MIN || gestureType > GESTURE_TYPE_MAX) {
        return;
    }

    ani_ref fnObjGlobalRef = nullptr;
    if (fnObj != nullptr) {
        env->GlobalReference_Create(reinterpret_cast<ani_ref>(fnObj), &fnObjGlobalRef);
    }

    CallbackResourceInfo info;
    info.resourceId = static_cast<int32_t>(resourceId);
    info.type = gestureType;

    RegisterGlobalGestureListenerCallback(env, info, fnObjGlobalRef);
}

void RemoveGlobalGestureListener(ani_env* env, [[maybe_unused]] ani_object aniClass,
    ani_int type, ani_fn_object fnObj)
{
    CHECK_NULL_VOID(env);

    int32_t gestureType = static_cast<int32_t>(type);
    if (gestureType < GESTURE_TYPE_MIN || gestureType > GESTURE_TYPE_MAX) {
        return;
    }

    ani_ref fnObjGlobalRef = nullptr;
    if (fnObj != nullptr) {
        env->GlobalReference_Create(reinterpret_cast<ani_ref>(fnObj), &fnObjGlobalRef);
    }

    UnregisterGlobalGestureCallback(env, gestureType, fnObjGlobalRef);
    ReleaseGlobalRef(env, fnObjGlobalRef);
}

} // namespace OHOS::Ace::Ani
