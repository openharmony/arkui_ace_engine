/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#if defined(MODEL_COMPONENT_SUPPORTED)
#include "core/components_ng/pattern/model/model_view_ng.h"
#endif
#include "core/interfaces/native/utility/validators.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG {
namespace Converter {
#if defined(MODEL_COMPONENT_SUPPORTED)
template<>
void AssignCast(std::optional<OHOS::Render3D::SurfaceType>& dst, const Ark_ModelType& src)
{
    switch (src) {
        case ARK_MODEL_TYPE_TEXTURE: dst = OHOS::Render3D::SurfaceType::SURFACE_TEXTURE; break;
        case ARK_MODEL_TYPE_SURFACE: dst = OHOS::Render3D::SurfaceType::SURFACE_WINDOW; break;
        default: LOGE("Unexpected enum value in Ark_ModelType: %{public}d", src);
    }
}
#endif // MODEL_COMPONENT_SUPPORTED
} // Converter
} // OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace Component3DModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
#ifdef MODEL_COMPONENT_SUPPORTED
    auto frameNode = ModelViewNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
#else
    return nullptr;
#endif // MODEL_COMPONENT_SUPPORTED
}
} // Component3DModifier
namespace Component3DInterfaceModifier {
void SetComponent3DOptionsImpl(Ark_NativePointer node,
                               const Opt_SceneOptions* sceneOptions)
{
    #ifdef MODEL_COMPONENT_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::string bundleName;
    std::string moduleName;
    Render3D::SurfaceType surfaceType = OHOS::Render3D::SurfaceType::SURFACE_TEXTURE;
#if defined(KIT_3D_ENABLE)
    std::shared_ptr<Render3D::ISceneAdapter> scene = nullptr;
    bool isSceneApi = false;
#endif
    auto options = Converter::OptConvert<Ark_SceneOptions>(*sceneOptions);
    if (options) {
        auto modelOpt = Converter::OptConvert<Ark_ModelType>(options.value().modelType);
        if (modelOpt) {
            auto st = Converter::OptConvert<OHOS::Render3D::SurfaceType>(modelOpt.value());
            if (st) {
                surfaceType = st.value();
            }
        }
        Converter::VisitUnion(options.value().scene,
            [frameNode, surfaceType](const Ark_ResourceStr& value0) {
                std::string bundleName = Converter::Convert<std::string>(value0.value1.bundleName);
                std::string moduleName = Converter::Convert<std::string>(value0.value1.moduleName);
                ModelViewNG::SetModelViewContext(frameNode, { bundleName, moduleName, surfaceType });
            },
            [](const Ark_Scene& value) {
#if defined(KIT_3D_ENABLE)
                LOGE("Component3DInterfaceModifier::SetComponent3DOptionsImpl scene attribute is stub.");
#endif
            },
            []() {}
        );
    }
#endif
}
} // Component3DInterfaceModifier
namespace Component3DAttributeModifier {
static const std::regex MODEL_RES_ID_REGEX(R"(^resource://\w+/([0-9]+)\.\w+$)", std::regex::icase);
static const std::regex MODEL_APP_RES_PATH_REGEX(R"(^resource://RAWFILE/(.*)$)");
static const std::regex MODEL_APP_RES_ID_REGEX(R"(^resource://.*/([0-9]+)\.\w+$)", std::regex::icase);
static const std::regex MODEL_RES_NAME_REGEX(R"(^resource://.*/(\w+)\.\w+$)", std::regex::icase);
static constexpr uint32_t MODEL_RESOURCE_MATCH_SIZE = 2;
bool GetResourceId(const std::string& uri, uint32_t& resId)
{
    std::smatch matches;
    if (std::regex_match(uri, matches, MODEL_RES_ID_REGEX) && matches.size() == MODEL_RESOURCE_MATCH_SIZE) {
        resId = static_cast<uint32_t>(std::stoul(matches[1].str()));
        return true;
    }

    std::smatch appMatches;
    if (std::regex_match(uri, appMatches, MODEL_APP_RES_ID_REGEX) && appMatches.size() == MODEL_RESOURCE_MATCH_SIZE) {
        resId = static_cast<uint32_t>(std::stoul(appMatches[1].str()));
        return true;
    }
    return false;
}
bool GetResourceId(const std::string& uri, std::string& path)
{
    std::smatch matches;
    if (std::regex_match(uri, matches, MODEL_APP_RES_PATH_REGEX) && matches.size() == MODEL_RESOURCE_MATCH_SIZE) {
        path = matches[1].str();
        return true;
    }
    return false;
}
bool GetResourceName(const std::string& uri, std::string& resName)
{
    std::smatch matches;
    if (std::regex_match(uri, matches, MODEL_RES_NAME_REGEX) && matches.size() == MODEL_RESOURCE_MATCH_SIZE) {
        resName = matches[1].str();
        return true;
    }
    return false;
}
bool SetOhosPath(const std::string& uri, std::string& ohosPath)
{
    if (GetResourceId(uri, ohosPath)) {
        ohosPath = "OhosRawFile://" + ohosPath;
        return true;
    }

    uint32_t resId = 0;
    if (GetResourceId(uri, resId)) {
        ohosPath = "OhosRawFile://" + std::to_string(resId);
        return true;
    }

    if (GetResourceName(uri, ohosPath)) {
        ohosPath = "OhosRawFile://" + ohosPath;
        return true;
    }
    // set default format as system resource
    ohosPath = "file://" + uri;
    return false;
}
void EnvironmentImpl(Ark_NativePointer node,
                     const Opt_ResourceStr* value)
{
    #if defined(MODEL_COMPONENT_SUPPORTED)
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto srcPath = Converter::OptConvert<std::string>(*value);
    if (srcPath) {
        std::string ohosPath("");
        SetOhosPath(srcPath.value(), ohosPath);
        ModelViewNG::SetBackground(frameNode, ohosPath);
    }
    #endif
}
void ShaderImpl(Ark_NativePointer node,
                const Opt_ResourceStr* value)
{
    #if defined(MODEL_COMPONENT_SUPPORTED)
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto srcPath = Converter::OptConvert<std::string>(*value);
    if (srcPath) {
        std::string ohosPath("");
        SetOhosPath(srcPath.value(), ohosPath);
        ModelViewNG::SetShader(frameNode, ohosPath);
    }
    #endif
}
void ShaderImageTextureImpl(Ark_NativePointer node,
                            const Opt_ResourceStr* value)
{
    #if defined(MODEL_COMPONENT_SUPPORTED)
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto srcPath = Converter::OptConvert<std::string>(*value);
    if (srcPath) {
        std::string ohosPath("");
        SetOhosPath(srcPath.value(), ohosPath);
        ModelViewNG::AddShaderImageTexture(frameNode, ohosPath);
    }
    #endif
}
void ShaderInputBufferImpl(Ark_NativePointer node,
                           const Opt_Array_Number* value)
{
    #if defined(MODEL_COMPONENT_SUPPORTED)
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto shaderInputVec = Converter::OptConvert<std::vector<float>>(*value);
    if (!shaderInputVec) {
        // TODO: Reset value
        return;
    }
    int32_t length = shaderInputVec->size();
    if (length <= 0) {
        return;
    }
    auto buffer = std::make_shared<OHOS::Render3D::ShaderInputBuffer>();
    if (!buffer->Alloc(length)) {
        return;
    }
    for (int32_t i = 0; i < length; i++) {
        buffer->Update(shaderInputVec->at(i), i);
    }
    ModelViewNG::AddShaderInputBuffer(frameNode, buffer);
    #endif
}
void RenderWidthImpl(Ark_NativePointer node,
                     const Opt_Length* value)
{
    #if defined(MODEL_COMPONENT_SUPPORTED)
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Dimension>(*value);
    Validator::ValidatePositive(convValue);
    ModelViewNG::SetRenderWidth(frameNode, convValue);
    #endif
}
void RenderHeightImpl(Ark_NativePointer node,
                      const Opt_Length* value)
{
    #if defined(MODEL_COMPONENT_SUPPORTED)
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Dimension>(*value);
    Validator::ValidatePositive(convValue);
    ModelViewNG::SetRenderHeight(frameNode, convValue);
    #endif
}
void CustomRenderImpl(Ark_NativePointer node,
                      const Opt_ResourceStr* uri,
                      const Opt_Boolean* selfRenderUpdate)
{
    #if defined(MODEL_COMPONENT_SUPPORTED)
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(uri);
    auto update = Converter::OptConvert<bool>(*selfRenderUpdate);
    if (!update) {
        // TODO: Reset value
        return;
    }
    auto uriString = Converter::OptConvert<std::string>(*uri); //uriString.value_or("")
    auto customRender = std::make_shared<OHOS::Render3D::CustomRenderDescriptor>(uriString.value_or(""), *update);
    ModelViewNG::AddCustomRender(frameNode, customRender);
    #endif
}
} // Component3DAttributeModifier
const GENERATED_ArkUIComponent3DModifier* GetComponent3DModifier()
{
    static const GENERATED_ArkUIComponent3DModifier ArkUIComponent3DModifierImpl {
        Component3DModifier::ConstructImpl,
        Component3DInterfaceModifier::SetComponent3DOptionsImpl,
        Component3DAttributeModifier::EnvironmentImpl,
        Component3DAttributeModifier::ShaderImpl,
        Component3DAttributeModifier::ShaderImageTextureImpl,
        Component3DAttributeModifier::ShaderInputBufferImpl,
        Component3DAttributeModifier::RenderWidthImpl,
        Component3DAttributeModifier::RenderHeightImpl,
        Component3DAttributeModifier::CustomRenderImpl,
    };
    return &ArkUIComponent3DModifierImpl;
}

}
