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
#include "drag_controller_module.h"

#include "load.h"
#include "utils/ani_utils.h"
#include "log/log.h"

namespace OHOS::Ace::Ani {
ani_object ANIExecuteDragWithCallback(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_object custom,
    ani_long builderObj, ani_object destroyCallbackObj, ani_object dragInfo, ani_object callback)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragControllerAniModifier()) {
        return nullptr;
    }
    ani_object object = modifier->getDragControllerAniModifier()->aniExecuteDragWithCallback(
        env, aniClass, custom, builderObj, destroyCallbackObj, dragInfo, callback);
    return object;
}

ani_object ANIExecuteDragWithPromise([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass,
    ani_object custom, ani_long builderObj, ani_object destroyCallbackObj, ani_object dragInfo)
{
    return ANIExecuteDragWithCallback(env, aniClass, custom, builderObj, destroyCallbackObj, dragInfo, nullptr);
}

ani_object ANICreateDragAction([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass,
    ani_object customArray, ani_object builderArray, ani_object destroyCallbackObj,
    [[maybe_unused]] ani_object dragInfoObj)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragControllerAniModifier()) {
        return nullptr;
    }
    ani_object object = modifier->getDragControllerAniModifier()->aniCreateDragAction(
        env, aniClass, customArray, builderArray, destroyCallbackObj, dragInfoObj);
    return object;
}

ani_object ANIDragActionStartDrag(
    [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long dragActionPtr)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragControllerAniModifier()) {
        return nullptr;
    }
    ani_object object = modifier->getDragControllerAniModifier()->aniDragActionStartDrag(env, aniClass, dragActionPtr);
    return object;
}

void ANIDragActionOn([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, ani_string type,
    ani_object callback, ani_long dragActionPtr)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragControllerAniModifier()) {
        return;
    }
    std::string aniType = AniUtils::ANIStringToStdString(env, type);
    modifier->getDragControllerAniModifier()->aniDragActionOn(env, aniClass, aniType.c_str(), callback, dragActionPtr);
}

void ANIDragActionOff([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, ani_string type,
    [[maybe_unused]] ani_object callback, ani_long dragActionPtr)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragControllerAniModifier()) {
        return;
    }
    std::string aniType = AniUtils::ANIStringToStdString(env, type);
    modifier->getDragControllerAniModifier()->aniDragActionOff(env, aniClass, aniType.c_str(), callback, dragActionPtr);
}

ani_object ANIGetDragPreview([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragControllerAniModifier()) {
        return nullptr;
    }
    return modifier->getDragControllerAniModifier()->aniGetDragPreview(env, aniClass);
}

void ANIDragPreviewSetForegroundColor([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass,
    ani_object color, ani_long dragPreviewPtr)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragControllerAniModifier()) {
        return;
    }
    modifier->getDragControllerAniModifier()->aniDragPreviewSetForegroundColor(env, aniClass, color, dragPreviewPtr);
}

void ANIDragPreviewAnimate([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, ani_object options,
    ani_object handler, ani_long dragPreviewPtr)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragControllerAniModifier()) {
        return;
    }
    modifier->getDragControllerAniModifier()->aniDragPreviewAnimate(env, aniClass, options, handler, dragPreviewPtr);
}

void ANIDragActionSetDragEventStrictReportingEnabled(
    [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, bool enable)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragControllerAniModifier()) {
        return;
    }
    modifier->getDragControllerAniModifier()->aniDragActionSetDragEventStrictReportingEnabled(env, aniClass, enable);
}

void ANIDragActionCancelDataLoading(
    [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, ani_string key)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragControllerAniModifier()) {
        return;
    }
    modifier->getDragControllerAniModifier()->aniDragActionCancelDataLoading(env, aniClass, key);
}

void ANIDragActionNotifyDragStartReques(
    [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, ani_enum_item requestStatus)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragControllerAniModifier()) {
        return;
    }
    modifier->getDragControllerAniModifier()->aniDragActionNotifyDragStartReques(env, aniClass, requestStatus);
}
} // namespace OHOS::Ace::Ani