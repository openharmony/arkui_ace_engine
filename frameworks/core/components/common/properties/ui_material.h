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
#include "ui/properties/ui_material_structs.h"

#include "core/common/ace_application_info.h"
#include "core/components/common/properties/shadow.h"
#include "core/components_ng/property/border_property.h"

namespace OHOS::Rosen {
class Filter;
class RSNGFilterBase;
}

namespace OHOS::Ace {
extern const char UI_MATERIAL_EXTENSION_SO_PATH[];
extern const char UI_MATERIAL_FUNC_NAME[];
extern const char UI_MATERIAL_FUNC_GET_ID[];

namespace NG {
class PipelineContext;
class FrameNode;
} // namespace OHOS::Ace::NG

enum class DistortionMode: int32_t {
    DISTORTION_AUTO = 0,
    DISTORTION_ENABLED = 1,
    DISTORTION_DISABLED = 2,
};

enum class EdgeLightMode: int32_t {
    EDGELIGHT_AUTO = 0,
    EDGELIGHT_ENABLED = 1,
    EDGELIGHT_DISABLED = 2,
};

struct UiMaterialParam {
    Shadow shadow;
    Color backgroundColor;
    NG::BorderWidthProperty borderWidth;
    NG::BorderColorProperty borderColor;
};

struct ImmersiveMaterialConfig {
    UiMaterialMapKey key {};
    Color materialColor;
    bool colorInvert = false;
    bool applyShadow = true;
    float dipScale = 1.0f;

    bool operator==(const ImmersiveMaterialConfig& other) const
    {
        return key == other.key && materialColor == other.materialColor && colorInvert == other.colorInvert &&
               applyShadow == other.applyShadow && NearEqual(dipScale, other.dipScale);
    }
};

// store UiMaterial all information
struct UiMaterialInfo {
    RefPtr<UiMaterial> material;
    std::optional<ImmersiveMaterialConfig> immersiveConfig;
    std::optional<int32_t> transparencyCallbackId;
};

class ACE_FORCE_EXPORT MaterialUtils {
public:
    // get type of material to MaterialType enum, return MaterialType::NONE if invalid number,
    // return std::nullopt if material is nullptr.
    static std::optional<MaterialType> GetTypeFromMaterial(const UiMaterial* material);
    static ColorMode GetResourceColorMode(NG::PipelineContext* pipeline);
    static bool CallSetMaterial(NG::FrameNode* node, const UiMaterial* material);
    static int32_t CallGetMaterialId(const UiMaterial* material);
    static bool CheckMaterialValid(int32_t type);
    static std::optional<ImmersiveMaterialConfig> GetImmersiveMaterialConfig(
        const std::shared_ptr<ImmersiveOptions>& options, const RefPtr<NG::FrameNode>& node);
    static std::optional<ImmersiveMaterialConfig> GetImmersiveMaterialConfig(
        const std::shared_ptr<ImmersiveOptions>& options, float dipScale, ColorMode colorMode);
    static bool GetUiMaterialFilter(
        const ImmersiveMaterialConfig& params, std::shared_ptr<Rosen::RSNGFilterBase>& filter);
    static Shadow GetImmersiveShadow(float dipScale);
    static Shadow GetImmersiveEmptyShadow();
    static bool GetGlobalMaterialLevel(UiMaterialLevel& result);
    static MaterialState GetConfiguredMaterialState();
    static MaterialType GetConfiguredMaterialType();
    static bool IsMaterialDisabled();
    static bool IsMaterialEnabled();
    static bool IsEmptyMaterial(const RefPtr<UiMaterial>& material);
    static RefPtr<UiMaterial> GetInitMaterial(const UiMaterialStyle style);
    static bool IsEnableMaterialParam(const RefPtr<UiMaterial>& material);
    static const UiMaterial* PreProcessMaterial(const UiMaterial* material);
    static std::shared_ptr<Rosen::Filter> CreateRosenFilter(const ImmersiveMaterialConfig& params);
    static ColorMode GetNodeColorMode(const RefPtr<NG::FrameNode>& node);

private:
    static bool ValidColorInvert(const std::shared_ptr<ImmersiveOptions>& options, UiMaterialLevel systemLevel,
        UiMaterialTransparency systemTransparency);
    static MaterialState ParseMaterialState(const std::string& value);
    static MaterialType ParseMaterialType(const std::string& value);
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_COMMON_PROPERTIES_UI_MATERIAL_H
