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

#include "core/interfaces/native/ani/resource_ani_modifier.h"

#include <cstdint>

#include "ani.h"

#include "base/log/log.h"
#include "base/log/log_wrapper.h"
#include "bridge/arkts_frontend/arkts_ani_utils.h"
#include "core/common/container.h"
#include "core/common/resource/resource_manager.h"
#include "core/common/resource/resource_object.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t COLOR_ALPHA_OFFSET = 24;
constexpr uint32_t COLOR_ALPHA_VALUE = 0xFF000000;
uint32_t ColorAlphaAdapt(uint32_t origin)
{
    uint32_t result = origin;
    if ((origin >> COLOR_ALPHA_OFFSET) == 0) {
        result = origin | COLOR_ALPHA_VALUE;
    }
    return result;
}
} // namespace
bool ResourceAniModifier::ParseAniColor(ani_env* env, ani_object aniValue, Color& color)
{
    ani_status status;
    ani_class stringClass;
    if ((status = env->FindClass("Lstd/core/String;", &stringClass)) != ANI_OK) {
        LOGW("ParseAniColor find string failed. %{public}d", status);
        return false;
    }
    ani_boolean isString;
    if ((status = env->Object_InstanceOf(aniValue, stringClass, &isString)) != ANI_OK) {
        LOGW("ParseAniColor call instanceof string failed. %{public}d", status);
        return false;
    }
    if (isString) {
        auto srcString = ArktsAniUtils::ANIStringToStdString(env, static_cast<ani_string>(aniValue));
        Color::ParseColorString(srcString, color);
        return true;
    }

    ani_class doubleClass;
    if ((status = env->FindClass("Lstd/core/Double;", &doubleClass)) != ANI_OK) {
        LOGW("ParseAniColor find int failed. %{public}d", status);
        return false;
    }
    ani_boolean isDouble;
    if ((status = env->Object_InstanceOf(aniValue, doubleClass, &isDouble)) != ANI_OK) {
        LOGW("ParseAniColor call instanceof double failed. %{public}d", status);
        return false;
    }
    if (isDouble) {
        ani_double doubleSrc;
        if ((status = env->Object_CallMethodByName_Double(aniValue, "unboxed", ":d", &doubleSrc)) != ANI_OK) {
            LOGW("GetColorValue unboxed double failed. %{public}d", status);
            return false;
        }
        color = Color(ColorAlphaAdapt(static_cast<uint32_t>(doubleSrc)));
        return true;
    }

    ani_class resourceClass;
    if ((status = env->FindClass("Lglobal/resource/Resource;", &resourceClass)) != ANI_OK) {
        LOGW("ParseAniColor find Resource failed. %{public}d", status);
        return false;
    }
    ani_boolean isResource;
    if ((status = env->Object_InstanceOf(aniValue, resourceClass, &isResource)) != ANI_OK) {
        LOGW("ParseAniColor call instanceof Resource failed. %{public}d", status);
        return false;
    }
    if (isResource) {
        ani_double resId;
        env->Object_GetPropertyByName_Double(aniValue, "id", &resId);
        ani_ref bundleName;
        env->Object_GetPropertyByName_Ref(aniValue, "bundleName", &bundleName);
        ani_ref moduleName;
        env->Object_GetPropertyByName_Ref(aniValue, "moduleName", &moduleName);
        auto resObj = AceType::MakeRefPtr<ResourceObject>(
            ArktsAniUtils::ANIStringToStdString(env, static_cast<ani_string>(bundleName)),
            ArktsAniUtils::ANIStringToStdString(env, static_cast<ani_string>(moduleName)),
            Container::CurrentIdSafely());
        auto resAdapter = ResourceManager::GetInstance().GetOrCreateResourceAdapter(resObj);
        color =  resAdapter->GetColor(static_cast<int32_t>(resId));
        return true;
    }
    return false;
}
} // namespace OHOS::Ace::NG
