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

#include "core/common/color_inverter.h"
#include "core/common/visual_effect/transparency_utils.h"
#include "core/components/theme/resource_adapter.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components/theme/theme_constants.h"
#include "core/components_ng/render/ui_material_filter_creator.h"

namespace OHOS::Ace {
const char UI_MATERIAL_EXTENSION_SO_PATH[] = "system/lib64/libhdsmaterialimpl.z.so";
const char UI_MATERIAL_FUNC_NAME[] = "SetMaterial";
const char UI_MATERIAL_FUNC_GET_ID[] = "GetMaterialId";

namespace {
constexpr float IMMERSIVE_SHADOW_RADIUS = 26.0f;  // in vp
constexpr float IMMERSIVE_SHADOW_OFFSET_Y = 8.0f; // in vp
const Color IMMERSIVE_SHADOW_COLOR(0x14050505);

using SetMaterialFunc = void (*)(NG::FrameNode*, const UiMaterial*);
using GetMaterialIdFunc = int32_t (*)(const UiMaterial*);
using CreateMaterialFilterFunc = void* (*)(const ArkUIMaterialKeyParams*);
using ReleaseMaterialFilterFunc = void (*)(void*);
using GetEnableColorInvertFunc = int32_t (*)(int32_t, int32_t);
using GetGlobalMaterialLevelFunc = int32_t (*)();
using GetEnableMaterialFunc = bool (*)();
struct MaterialFilterStruct {
    std::shared_ptr<Rosen::RSNGFilterBase> filter;
};
struct MaterialFilterECStruct {
    std::shared_ptr<Rosen::RSNGFilterBase> filter;
};
struct MaterialShaderECSubStruct {
    std::shared_ptr<Rosen::RSNGShaderBase> shader;
};

#ifndef _WIN32
const char UI_MATERIAL_FUNC_CREATE_UI_MATERIAL[] = "CreateUiMaterialFilter";
const char UI_MATERIAL_FUNC_RELEASE_UI_MATERIAL[] = "ReleaseUiMaterialFilter";
const char UI_MATERIAL_FUNC_CREATE_UI_MATERIAL_EC[] = "CreateUiMaterialFilterEC";
const char UI_MATERIAL_FUNC_RELEASE_UI_MATERIAL_EC[] = "ReleaseUiMaterialFilterEC";
const char UI_MATERIAL_FUNC_CREATE_UI_MATERIAL_EC_SUB[] = "CreateUiMaterialShaderECSub";
const char UI_MATERIAL_FUNC_RELEASE_UI_MATERIAL_EC_SUB[] = "ReleaseUiMaterialShaderECSub";
const char UI_MATERIAL_FUNC_GET_ENABLE_COLOR_INVERT[] = "GetEnableColorInvert";
const char UI_MATERIAL_FUNC_GET_GLOBAL_LEVEL[] = "GetGlobalMaterialLevel";
const char UI_MATERIAL_FUNC_GET_ENABLE_MATERIAL[] = "IsSystemMaterialSupported";
void* GetMaterialLib()
{
    static void* handle = nullptr;
    static std::once_flag onceFlag;
    std::call_once(onceFlag, []() { handle = LOADLIB(UI_MATERIAL_EXTENSION_SO_PATH); });
    return handle;
}
#endif

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
    auto handle = GetMaterialLib();
    if (!handle) {
        isLoaded = true;
        return nullptr;
    }
    materialFunc = reinterpret_cast<SetMaterialFunc>(LOADSYM(handle, UI_MATERIAL_FUNC_NAME));
#endif
    isLoaded = true;
    return materialFunc;
}

GetMaterialIdFunc GetOrCreateGetMaterialIdFunc()
{
    static bool isLoaded = false;
    static GetMaterialIdFunc getMaterialIdFunc = nullptr;
    static std::mutex materialMutex;
    if (isLoaded) {
        return getMaterialIdFunc;
    }
    std::lock_guard<std::mutex> lock(materialMutex);
    if (isLoaded) {
        return getMaterialIdFunc;
    }
#ifndef _WIN32
    auto handle = GetMaterialLib();
    if (!handle) {
        isLoaded = true;
        return nullptr;
    }
    getMaterialIdFunc = reinterpret_cast<GetMaterialIdFunc>(LOADSYM(handle, UI_MATERIAL_FUNC_GET_ID));
#endif
    isLoaded = true;
    return getMaterialIdFunc;
}

ArkUIMaterialKeyParams ConvertToArkUIMaterialKeyParams(const ImmersiveMaterialConfig& config)
{
    const auto& key = config.key;
    return ArkUIMaterialKeyParams {
        .level = static_cast<int32_t>(key.level),
        .style = static_cast<int32_t>(key.style),
        .transparency = static_cast<int32_t>(key.transparency),
        .colorMode = static_cast<int32_t>(key.colorMode),
        .dipScale = config.dipScale,
    };
}

bool IsTransparencyThin(UiMaterialTransparency transparency)
{
    return transparency == UiMaterialTransparency::THIN || transparency == UiMaterialTransparency::GENTLE_THIN;
}
} // namespace

std::optional<MaterialType> MaterialUtils::GetTypeFromMaterial(const UiMaterial* material)
{
    CHECK_NULL_RETURN(material, std::nullopt);
    auto type = material->GetType();
    if (MaterialUtils::CheckMaterialValid(type)) {
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
int32_t MaterialUtils::CallGetMaterialId(const UiMaterial* material)
{
    CHECK_NULL_RETURN(material, -1);
    auto getMaterialIdFunc = GetOrCreateGetMaterialIdFunc();
    int32_t materialId = -1;
    if (getMaterialIdFunc) {
        materialId = getMaterialIdFunc(material);
    }
    return materialId;
}

bool MaterialUtils::CheckMaterialValid(int32_t type)
{
    return type == static_cast<int32_t>(MaterialType::NONE) ||
           type == static_cast<int32_t>(MaterialType::SEMI_TRANSPARENT) ||
           type == static_cast<int32_t>(MaterialType::IMMERSIVE);
}

RefPtr<UiMaterial> UiMaterial::Copy() const
{
    auto result = AceType::MakeRefPtr<UiMaterial>();
    CopyTo(result);
    return result;
}

void UiMaterial::CopyTo(RefPtr<UiMaterial>& other) const
{
    other->SetType(type_);
    other->SetEmpty(isEmpty_);
    if (immersiveOptions_) {
        other->SetImmersiveOptions(*immersiveOptions_);
    }
}

void UiMaterial::SetImmersiveOptions(const ImmersiveOptions& options)
{
    if (!immersiveOptions_) {
        immersiveOptions_ = std::make_shared<ImmersiveOptions>(options);
        return;
    }
    *immersiveOptions_ = options;
}

const std::shared_ptr<ImmersiveOptions>& UiMaterial::GetImmersiveOptions() const
{
    return immersiveOptions_;
}

std::shared_ptr<ImmersiveOptions> UiMaterial::CopyImmersiveOptions() const
{
    CHECK_NULL_RETURN(immersiveOptions_, nullptr);
    return std::make_shared<ImmersiveOptions>(*immersiveOptions_);
}

bool UiMaterial::IsForceShadow() const
{
    if (immersiveOptions_) {
        return immersiveOptions_->applyShadow;
    }
    return false;
}

std::optional<bool> UiMaterial::IsInteractived() const
{
    if (immersiveOptions_) {
        return immersiveOptions_->interactive;
    }
    return false;
}

std::size_t UiMaterialMapKeyHasher::operator()(const UiMaterialMapKey& key) const
{
    static constexpr int levelDigit = 8;
    static constexpr int levelShiftDigit = 0;
    static constexpr int styleDigit = 16;
    static constexpr int styleShiftDigit = levelShiftDigit + levelDigit; // 8
    static constexpr int colorModeDigit = 4;
    static constexpr int colorModeShiftDigit = styleShiftDigit + styleDigit; // 24
    return (GetOpValue(static_cast<size_t>(key.level), levelDigit, levelShiftDigit) |
            GetOpValue(static_cast<size_t>(key.style), styleDigit, styleShiftDigit) |
            GetOpValue(static_cast<size_t>(key.colorMode), colorModeDigit, colorModeShiftDigit));
}

std::optional<ImmersiveMaterialConfig> MaterialUtils::GetImmersiveMaterialConfig(
    const std::shared_ptr<ImmersiveOptions>& options, const RefPtr<NG::FrameNode>& node)
{
    if (!options || !node) {
        return std::nullopt;
    }
    auto pipeline = node->GetContextWithCheck();
    CHECK_NULL_RETURN(pipeline, std::nullopt);
    auto colorMode = GetNodeColorMode(node);
    return GetImmersiveMaterialConfig(options, pipeline->GetDipScale(), colorMode);
}

std::optional<ImmersiveMaterialConfig> MaterialUtils::GetImmersiveMaterialConfig(
    const std::shared_ptr<ImmersiveOptions>& options, float dipScale, ColorMode colorMode)
{
    if (!options) {
        return std::nullopt;
    }
    if (colorMode == ColorMode::COLOR_MODE_UNDEFINED) {
        colorMode = ColorMode::LIGHT;
    }
    auto materialLevel = SystemProperties::GetUiMaterialLevel();
    ImmersiveMaterialConfig result {
        .applyShadow = options->applyShadow, .dipScale = dipScale, .interactive = options->interactive.value_or(false),
        .lightEffectOptions = options->lightEffectOptions
    };
    if (materialLevel == UiMaterialLevel::SMOOTH) {
        result.key = UiMaterialMapKey {
            .level = UiMaterialLevel::SMOOTH,
            .colorMode = (options->colorMode == ColorMode::COLOR_MODE_UNDEFINED) ?
                                    colorMode : options->colorMode,
        };
        return result;
    }
    int32_t transparency = TransparencyUtils::GetTransparencyLevel(static_cast<int32_t>(materialLevel));
    bool finalInvertColor = ValidColorInvert(options, materialLevel, static_cast<UiMaterialTransparency>(transparency));
    result.colorInvert = finalInvertColor;
    result.materialColor = options->materialColor;
    if (finalInvertColor) {
        colorMode = ColorMode::LIGHT;
    } else if (options->colorMode != ColorMode::COLOR_MODE_UNDEFINED) {
        colorMode = options->colorMode;
    }
    result.key = UiMaterialMapKey {
        .level = materialLevel,
        .style = options->style,
        .transparency = static_cast<UiMaterialTransparency>(transparency),
        .colorMode = colorMode,
    };
    return result;
}

ColorMode MaterialUtils::GetNodeColorMode(const RefPtr<NG::FrameNode>& node)
{
    ColorMode colorMode = node->GetLocalColorMode();
    if (colorMode == ColorMode::COLOR_MODE_UNDEFINED) {
        auto pipeline = node->GetContextWithCheck();
        CHECK_NULL_RETURN(pipeline, ColorMode::LIGHT);
        colorMode = MaterialUtils::GetResourceColorMode(pipeline);
    }
    return colorMode;
}

std::optional<ImmersiveMaterialConfig> MaterialUtils::GetImmersiveMaterialConfigWithScale(
    const std::shared_ptr<ImmersiveOptions>& options, const RefPtr<NG::FrameNode>& node, float componentScale)
{
    if (!options || !node) {
        return std::nullopt;
    }
    auto pipeline = node->GetContextWithCheck();
    CHECK_NULL_RETURN(pipeline, std::nullopt);
    auto colorMode = GetNodeColorMode(node);

    // Get base dipScale and adjust by component scale
    float baseDipScale = pipeline->GetDipScale();
    // Ensure componentScale is valid
    if (componentScale <= 0.0f || NearZero(componentScale)) {
        componentScale = 1.0f;
    }
    // When component is scaled (componentScale != 1.0), the graphic side applies transform matrix
    // to material effects, causing blur radius to be compressed/stretched.
    // To compensate: we divide dipScale by componentScale (inverse scaling).
    // Example: scale=0.5 means 2x larger dipScale to compensate for 0.5x compression.
    float adjustedDipScale = baseDipScale / componentScale;

    return GetImmersiveMaterialConfig(options, adjustedDipScale, colorMode);
}

bool MaterialUtils::ValidColorInvert(const std::shared_ptr<ImmersiveOptions>& options, UiMaterialLevel systemLevel,
    UiMaterialTransparency systemTransparency)
{
    if (!options || !options->colorInvert) {
        return false;
    }
    if (systemLevel == UiMaterialLevel::SMOOTH) {
        return false;
    }
    static GetEnableColorInvertFunc enableFunc = nullptr;
#ifndef _WIN32
    static std::once_flag onceFlag;
    std::call_once(onceFlag, []() {
        auto handle = GetMaterialLib();
        CHECK_NULL_VOID(handle);
        enableFunc =
            reinterpret_cast<GetEnableColorInvertFunc>(LOADSYM(handle, UI_MATERIAL_FUNC_GET_ENABLE_COLOR_INVERT));
    });
#endif
    if (enableFunc) {
        return enableFunc(static_cast<int32_t>(options->style), static_cast<int32_t>(systemTransparency)) != 0;
    }
    bool status =
        (options->style == UiMaterialStyle::ULTRA_THIN || options->style == UiMaterialStyle::THIN ||
            options->style == UiMaterialStyle::ULTRA_THIN_EC || options->style == UiMaterialStyle::THIN_EC ||
            options->style == UiMaterialStyle::ULTRA_THIN_EC_SUB || options->style == UiMaterialStyle::THIN_EC_SUB);
    if (status && IsTransparencyThin(systemTransparency)) {
        return true;
    }
    return false;
}

bool MaterialUtils::GetUiMaterialFilter(
    const ImmersiveMaterialConfig& params, std::shared_ptr<Rosen::RSNGFilterBase>& filter)
{
    if (params.key.level != UiMaterialLevel::EXQUISITE) {
        return false;
    }
    static CreateMaterialFilterFunc createFunc = nullptr;
    static ReleaseMaterialFilterFunc releaseFunc = nullptr;
#ifndef _WIN32
    static std::once_flag onceFlag;
    std::call_once(onceFlag, []() {
        auto handle = GetMaterialLib();
        CHECK_NULL_VOID(handle);
        createFunc = reinterpret_cast<CreateMaterialFilterFunc>(LOADSYM(handle, UI_MATERIAL_FUNC_CREATE_UI_MATERIAL));
        releaseFunc =
            reinterpret_cast<ReleaseMaterialFilterFunc>(LOADSYM(handle, UI_MATERIAL_FUNC_RELEASE_UI_MATERIAL));
    });
#endif
    if (createFunc && releaseFunc) {
        auto arkParam = ConvertToArkUIMaterialKeyParams(params);
        auto filterStructVoid = createFunc(&arkParam);
        auto filterStruct = reinterpret_cast<MaterialFilterStruct*>(filterStructVoid);
        if (!filterStruct) {
            TAG_LOGW(AceLogTag::ACE_VISUAL_EFFECT, "not find param, (%{public}d, %{public}d, %{public}d)",
                arkParam.style, arkParam.transparency, arkParam.colorMode);
            return true;
        }
        filter = filterStruct->filter;
        releaseFunc(filterStructVoid);
        return true;
    }
    return false;
}

bool MaterialUtils::GetUiMaterialFilterEC(
    const ImmersiveMaterialConfig& params, std::shared_ptr<Rosen::RSNGFilterBase>& filter)
{
    if (params.key.level != UiMaterialLevel::EXQUISITE) {
        return false;
    }
    static CreateMaterialFilterFunc createFunc = nullptr;
    static ReleaseMaterialFilterFunc releaseFunc = nullptr;
#ifndef _WIN32
    static std::once_flag onceFlag;
    std::call_once(onceFlag, []() {
        auto handle = GetMaterialLib();
        CHECK_NULL_VOID(handle);
        createFunc =
            reinterpret_cast<CreateMaterialFilterFunc>(LOADSYM(handle, UI_MATERIAL_FUNC_CREATE_UI_MATERIAL_EC));
        releaseFunc =
            reinterpret_cast<ReleaseMaterialFilterFunc>(LOADSYM(handle, UI_MATERIAL_FUNC_RELEASE_UI_MATERIAL_EC));
    });
#endif
    if (createFunc && releaseFunc) {
        auto arkParam = ConvertToArkUIMaterialKeyParams(params);
        auto filterStructVoid = createFunc(&arkParam);
        auto filterStruct = reinterpret_cast<MaterialFilterECStruct*>(filterStructVoid);
        if (!filterStruct) {
            TAG_LOGW(AceLogTag::ACE_VISUAL_EFFECT, "not find param, (%{public}d, %{public}d, %{public}d)",
                arkParam.style, arkParam.transparency, arkParam.colorMode);
            return true;
        }
        filter = filterStruct->filter;
        releaseFunc(filterStructVoid);
        return true;
    }
    return false;
}

bool MaterialUtils::GetUiMaterialShaderECSub(
    const ImmersiveMaterialConfig& params, std::shared_ptr<Rosen::RSNGShaderBase>& shader)
{
    if (params.key.level != UiMaterialLevel::EXQUISITE) {
        return false;
    }
    static CreateMaterialFilterFunc createFunc = nullptr;
    static ReleaseMaterialFilterFunc releaseFunc = nullptr;
#ifndef _WIN32
    static std::once_flag onceFlag;
    std::call_once(onceFlag, []() {
        auto handle = GetMaterialLib();
        CHECK_NULL_VOID(handle);
        createFunc =
            reinterpret_cast<CreateMaterialFilterFunc>(LOADSYM(handle, UI_MATERIAL_FUNC_CREATE_UI_MATERIAL_EC_SUB));
        releaseFunc =
            reinterpret_cast<ReleaseMaterialFilterFunc>(LOADSYM(handle, UI_MATERIAL_FUNC_RELEASE_UI_MATERIAL_EC_SUB));
    });
#endif
    if (createFunc && releaseFunc) {
        auto arkParam = ConvertToArkUIMaterialKeyParams(params);
        auto filterStructVoid = createFunc(&arkParam);
        auto filterStruct = reinterpret_cast<MaterialShaderECSubStruct*>(filterStructVoid);
        if (!filterStruct) {
            TAG_LOGW(AceLogTag::ACE_VISUAL_EFFECT, "not find param, (%{public}d, %{public}d, %{public}d)",
                arkParam.style, arkParam.transparency, arkParam.colorMode);
            return true;
        }
        shader = filterStruct->shader;
        releaseFunc(filterStructVoid);
        return true;
    }
    return false;
}

bool MaterialUtils::GetGlobalMaterialLevel(UiMaterialLevel& result)
{
    static GetGlobalMaterialLevelFunc levelFunc = nullptr;
#ifndef _WIN32
    static std::once_flag onceFlag;
    std::call_once(onceFlag, []() {
        auto handle = GetMaterialLib();
        CHECK_NULL_VOID(handle);
        levelFunc = reinterpret_cast<GetGlobalMaterialLevelFunc>(LOADSYM(handle, UI_MATERIAL_FUNC_GET_GLOBAL_LEVEL));
    });
#endif
    if (levelFunc) {
        auto level = levelFunc();
        if (level >= static_cast<int32_t>(UiMaterialLevel::EXQUISITE) &&
            level <= static_cast<int32_t>(UiMaterialLevel::MAX)) {
            result = static_cast<UiMaterialLevel>(level);
            return true;
        }
    }
    return false;
}

bool MaterialUtils::GetDeviceUiMaterialEnabled(bool& result)
{
    static std::optional<bool> executeResult;
#ifndef _WIN32
    static GetEnableMaterialFunc enableFunc = nullptr;
    static std::once_flag onceFlag;
    std::call_once(onceFlag, []() {
        auto handle = GetMaterialLib();
        CHECK_NULL_VOID(handle);
        enableFunc = reinterpret_cast<GetEnableMaterialFunc>(LOADSYM(handle, UI_MATERIAL_FUNC_GET_ENABLE_MATERIAL));
        if (enableFunc) {
            executeResult = enableFunc();
        }
    });
#endif
    if (executeResult.has_value()) {
        result = executeResult.value();
        return true;
    }
    return false;
}

Shadow MaterialUtils::GetImmersiveShadow(float dipScale)
{
    Shadow shadow;
    shadow.SetBlurRadius(IMMERSIVE_SHADOW_RADIUS * dipScale);
    shadow.SetColor(IMMERSIVE_SHADOW_COLOR);
    shadow.SetOffsetY(IMMERSIVE_SHADOW_OFFSET_Y * dipScale);
    return shadow;
}

Shadow MaterialUtils::GetImmersiveEmptyShadow()
{
    Shadow shadow;
    shadow.SetBlurRadius(-1.0f);
    shadow.SetColor(Color::TRANSPARENT);
    return shadow;
}

MaterialState MaterialUtils::ParseMaterialState(const std::string& value)
{
    if (value == "enable") {
        return MaterialState::ENABLE;
    } else if (value == "disable") {
        return MaterialState::DISABLE;
    }
    return MaterialState::DEFAULT;
}

MaterialType MaterialUtils::ParseMaterialType(const std::string& value)
{
    return MaterialType::IMMERSIVE; // IMMERSIVE
}

MaterialState MaterialUtils::GetConfiguredMaterialState()
{
    const auto& rawState = AceApplicationInfo::GetInstance().GetUIMaterialState();
    return ParseMaterialState(rawState);
}

MaterialType MaterialUtils::GetConfiguredMaterialType()
{
    const auto& rawType = AceApplicationInfo::GetInstance().GetUIMaterialType();
    return ParseMaterialType(rawType);
}

bool MaterialUtils::IsMaterialDisabled()
{
    return GetConfiguredMaterialState() == MaterialState::DISABLE;
}

bool MaterialUtils::IsMaterialEnabled()
{
    return GetConfiguredMaterialState() == MaterialState::ENABLE;
}

bool MaterialUtils::IsEmptyMaterial(const RefPtr<UiMaterial>& material)
{
    CHECK_NULL_RETURN(material, false);
    return material->IsEmpty();
}

RefPtr<UiMaterial> MaterialUtils::GetInitMaterial(const UiMaterialStyle style)
{
    auto material = AceType::MakeRefPtr<UiMaterial>();
    material->SetType(static_cast<int32_t>(MaterialType::IMMERSIVE));
    ImmersiveOptions options {};
    options.style = style;
    material->SetImmersiveOptions(options);
    return material;
}

bool MaterialUtils::IsEnableMaterialParam(const RefPtr<UiMaterial>& material)
{
    if (MaterialUtils::IsMaterialDisabled()) {
        return false;
    }
    auto nativeMaterial = MaterialUtils::PreProcessMaterial(AceType::RawPtr(material));
    CHECK_NULL_RETURN(nativeMaterial, false);
    return true;
}

const UiMaterial* MaterialUtils::PreProcessMaterial(const UiMaterial* material)
{
    CHECK_NULL_RETURN(material, nullptr);
    if (material->IsEmpty() || !MaterialUtils::CheckMaterialValid(material->GetType())) {
        return nullptr;
    }
    return material;
}

MaterialState UiMaterial::GetConfiguredMaterialState()
{
    return MaterialUtils::GetConfiguredMaterialState();
}

bool UiMaterial::IsMaterialDisabled()
{
    return MaterialUtils::IsMaterialDisabled();
}

bool UiMaterial::IsMaterialEnabled()
{
    return MaterialUtils::IsMaterialEnabled();
}

RefPtr<UiMaterial> UiMaterial::CreateEmpty()
{
    auto material = AceType::MakeRefPtr<UiMaterial>();
    material->SetEmpty(true);
    return material;
}

std::shared_ptr<Rosen::Filter> MaterialUtils::CreateRosenFilter(const ImmersiveMaterialConfig& params)
{
    return NG::UiMaterialFilterCreator::CreateRosenFilter(params);
}
} // namespace OHOS::Ace
