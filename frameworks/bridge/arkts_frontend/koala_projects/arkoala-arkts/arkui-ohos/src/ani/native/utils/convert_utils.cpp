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

#include "convert_utils.h"

#if defined(PIXEL_MAP_SUPPORTED)
#include "pixel_map.h"
#include "base/image/pixel_map.h"
#endif
#include "base/log/log_wrapper.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"

namespace OHOS::Ace::Ani {
ani_long ConvertFromPixelMapAni(ani_env* env, [[maybe_unused]]ani_object aniClass, ani_object pixelMapObj)
{
    ani_status ret;
    ani_long nativeObj {};
    if ((ret = env->Object_GetFieldByName_Long(pixelMapObj, "nativeObj", &nativeObj)) != ANI_OK) {
        return nativeObj;
    }
    return nativeObj;
}

ani_object ConvertToPixelMapAni(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long pixelMapPtr)
{
    static const char* className = "L@ohos/multimedia/image/image/PixelMapInner;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return nullptr;
    }
    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", "J:V", &ctor)) {
        return nullptr;
    }
    ani_object aniValue;
    if (ANI_OK != env->Object_New(cls, ctor, &aniValue, pixelMapPtr)) {
        return nullptr;
    }
    return aniValue;
}

} // namespace OHOS::Ace::Ani
