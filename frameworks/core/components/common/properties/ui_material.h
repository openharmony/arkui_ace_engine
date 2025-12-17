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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_COMMON_PROPERTIES_UI_MATERIAL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_COMMON_PROPERTIES_UI_MATERIAL_H

#include <optional>

#include "ui/properties/color.h"
#include "ui/properties/ui_material.h"

#include "core/components/common/properties/shadow.h"
#include "core/components_ng/property/border_property.h"

namespace OHOS::Ace {
extern const char UI_MATERIAL_EXTENSION_SO_PATH[];
extern const char UI_MATERIAL_FUNC_NAME[];
extern const char UI_MATERIAL_FUNC_GET_ID[];

namespace NG {
class PipelineContext;
class FrameNode;
} // namespace OHOS::Ace::NG

enum class MaterialType: int32_t {
    NONE = 0,
    SEMI_TRANSPARENT = 1,
    MAX = 1,
};

struct UiMaterialParam {
    Shadow shadow;
    Color backgroundColor;
    NG::BorderWidthProperty borderWidth;
    NG::BorderColorProperty borderColor;
};

class ACE_FORCE_EXPORT MaterialUtils {
public:
    // get type of material to MaterialType enum, return MaterialType::NONE if invalid number,
    // return std::nullopt if material is nullptr.
    static std::optional<MaterialType> GetTypeFromMaterial(const UiMaterial* material);
    static ColorMode GetResourceColorMode(NG::PipelineContext* pipeline);
    static bool CallSetMaterial(NG::FrameNode* node, const UiMaterial* material);
    static int32_t CallGetMaterialId(const UiMaterial* material);
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_COMMON_PROPERTIES_UI_MATERIAL_H
