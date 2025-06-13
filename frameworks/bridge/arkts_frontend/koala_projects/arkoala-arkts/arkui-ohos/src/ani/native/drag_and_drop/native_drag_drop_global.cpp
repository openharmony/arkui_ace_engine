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

#include "native_drag_drop_global.h"

#include "ani_utils.h"
#include "log.h"
#include "utils/convert_utils.h"
#include "core/gestures/drag_event.h"
#include "load.h"
#include "pixel_map_taihe_ani.h"

namespace OHOS::Ace::Ani {
void DragEventSetData([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object data)
{
    // not implemented
}

ani_object DragEventGetData([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer)
{
    // not implemented
    ani_object result_obj = {};
    return result_obj;
}

ani_object DragEventGetSummary([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer)
{
    // not implemented
    ani_object result_obj = {};
    return result_obj;
}

void DragEventSetPixelMap([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object pixelMap)
{
    auto dragEvent = reinterpret_cast<ani_ref>(pointer);
    auto pixelMapValue = OHOS::Media::PixelMapTaiheAni::GetNativePixelMap(env, pixelMap);
    if (!dragEvent || !pixelMapValue) {
        return;
    }
    auto pixelMapPtr = reinterpret_cast<void*>(&pixelMapValue);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragAniModifier() || !env) {
        return;
    }
    modifier->getDragAniModifier()->setDragDropInfoPixelMap(dragEvent, reinterpret_cast<ani_ref>(pixelMapPtr));
}

void DragEventSetExtraInfo([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_string extraInfo)
{
    auto dragEvent = reinterpret_cast<ani_ref>(pointer);
    if (!dragEvent) {
        return;
    }
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragAniModifier() || !env) {
        return;
    }
    std::string aniExtraInfo = AniUtils::ANIStringToStdString(env, extraInfo);
    modifier->getDragAniModifier()->setDragDropInfoExtraInfo(dragEvent, aniExtraInfo);
}

void DragEventSetCustomNode([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_long node)
{
    auto dragEvent = reinterpret_cast<ani_ref>(pointer);
    auto* customNode = reinterpret_cast<ArkUINodeHandle>(node);
    if (!dragEvent || !customNode) {
        return;
    }
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragAniModifier() || !env) {
        return;
    }
    modifier->getDragAniModifier()->setDragDropInfoCustomNode(dragEvent, customNode);
}
} // namespace OHOS::Ace::Ani