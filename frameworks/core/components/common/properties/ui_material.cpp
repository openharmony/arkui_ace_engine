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

#include "core/components/common/properties/ui_material.h"

#include "interfaces/inner_api/ace/utils.h"

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {
const char UI_MATERIAL_EXTENSION_SO_PATH[] = "system/lib64/libhdsmaterialimpl.z.so";
const char UI_MATERIAL_FUNC_NAME[] = "SetMaterial";

namespace {
using SetMaterialFunc = void (*)(NG::FrameNode*, const UiMaterial*);

SetMaterialFunc GetOrCreateMaterialFunc()
{
    static bool isLoaded = false;
    static SetMaterialFunc materialFunc = nullptr;
    static std::mutex materialMutex;
    if (isLoaded) {
        return materialFunc;
    }
    std::lock_guard<std::mutex> lock(materialMutex);
    if (isLoaded) {
        return materialFunc;
    }
#ifndef _WIN32
    auto handle = LOADLIB(UI_MATERIAL_EXTENSION_SO_PATH);
    if (!handle) {
        isLoaded = true;
        return nullptr;
    }
    materialFunc = reinterpret_cast<SetMaterialFunc>(LOADSYM(handle, UI_MATERIAL_FUNC_NAME));
    if (!materialFunc) {
        FREELIB(handle);
    }
#endif
    isLoaded = true;
    return materialFunc;
}
} // namespace

std::optional<MaterialType> MaterialUtils::GetTypeFromMaterial(const UiMaterial* material)
{
    CHECK_NULL_RETURN(material, std::nullopt);
    auto type = material->GetType();
    if (type >= static_cast<int32_t>(MaterialType::NONE) && type <= static_cast<int32_t>(MaterialType::MAX)) {
        return static_cast<MaterialType>(type);
    }
    return MaterialType::NONE;
}
ColorMode MaterialUtils::GetResourceColorMode(NG::PipelineContext* pipeline)
{
    CHECK_NULL_RETURN(pipeline, ColorMode::LIGHT);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, ColorMode::LIGHT);
    auto themeConstants = themeManager->GetThemeConstants();
    CHECK_NULL_RETURN(themeConstants, ColorMode::LIGHT);
    auto resourceAdapter = themeConstants->GetResourceAdapter();
    CHECK_NULL_RETURN(resourceAdapter, ColorMode::LIGHT);
    return resourceAdapter->GetResourceColorMode();
}
bool MaterialUtils::CallSetMaterial(NG::FrameNode* node, const UiMaterial* material)
{
    auto materialFunc = GetOrCreateMaterialFunc();
    if (materialFunc) {
        materialFunc(node, material);
        return true;
    }
    return false;
}
} // namespace OHOS::Ace
