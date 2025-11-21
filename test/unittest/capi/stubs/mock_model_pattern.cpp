/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/model/model_pattern.h"

namespace OHOS::Ace::NG {

ModelPattern::ModelPattern(uint32_t key, const ModelViewContext& context) : key_(key)
{
}
ModelPattern::ModelPattern(uint32_t key) : key_(key)
{
}
ModelPattern::~ModelPattern()
{
}

void ModelPattern::SetModelViewContext(const ModelViewContext& context)
{
}

static std::string ShaderInputBufferToStr(const RefPtr<ModelPaintProperty>& modelPaintProperty)
{
    std::string ret;
    const auto& shaderInputBuffer = modelPaintProperty->GetModelShaderInputBuffer().value();
    if (!shaderInputBuffer || !shaderInputBuffer->IsValid()) {
        return ret;
    }
    auto fSize = shaderInputBuffer->FloatSize();
    auto buffer = shaderInputBuffer->Map(fSize);
    if (!buffer) {
        return ret;
    }
    for (auto i = 0u; i < fSize; i++) {
        ret += std::to_string(buffer[i]) + " ";
    }
    return ret;
}

static std::string TextureImagesToStr(const RefPtr<ModelPaintProperty>& modelPaintProperty)
{
    std::string ret;
    if (modelPaintProperty->GetModelImageTexturePathsValue().empty()) {
        return ret;
    }
    auto& imageTextures = modelPaintProperty->GetModelImageTexturePaths().value();
    for (auto& imageTexture : imageTextures) {
        ret += imageTexture + " ";
    }
    return ret;
}

static std::string SurfaceTypeToStr(const RefPtr<ModelAdapterWrapper>& modelAdapter)
{
    std::string ret;
    if (!modelAdapter) {
        return ret;
    }
    auto surfaceType = modelAdapter->GetSurfaceType();
    switch (surfaceType) {
        case Render3D::SurfaceType::UNDEFINE: {
            ret = "UNDEFINE";
            break;
        }
        case Render3D::SurfaceType::SURFACE_WINDOW: {
            ret = "ModelType.SURFACE";
            break;
        }
        case Render3D::SurfaceType::SURFACE_TEXTURE: {
            ret = "ModelType.TEXTURE";
            break;
        }
        case Render3D::SurfaceType::SURFACE_BUFFER: {
            ret = "SURFACE_BUFFER";
            break;
        }
        default: {
            ret = "SURFACE_WINDOW";
            break;
        }
    }
    return ret;
}

static std::string SceneEnvironmentToStr(const RefPtr<ModelPaintProperty>& modelPaintProperty)
{
    std::string ret;
    if (modelPaintProperty->GetModelBackgroundValue().empty()) {
        return ret;
    }
    ret = modelPaintProperty->GetModelBackground().value();
    return ret;
}

static std::string SceneCustomRenderToStr(const RefPtr<ModelPaintProperty>& modelPaintProperty)
{
    std::string ret;
    auto& customRender = modelPaintProperty->GetModelCustomRender().value();
    if (!customRender) {
        return ret;
    }
    ret = customRender->GetUri();
    return ret;
}

static std::string SceneShaderPathToStr(const RefPtr<ModelPaintProperty>& modelPaintProperty)
{
    std::string ret;
    if (modelPaintProperty->GetShaderPathValue().empty()) {
        return ret;
    }
    ret = modelPaintProperty->GetShaderPath().value();
    return ret;
}

static std::string SceneResourceToStr(const RefPtr<ModelPaintProperty>& modelPaintProperty)
{
    std::string ret;
    if (modelPaintProperty->GetModelSourceValue().empty()) {
        return ret;
    }
    ret = modelPaintProperty->GetModelSource().value();
    return ret;
}

void ModelPattern::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    Pattern::ToJsonValue(json, filter);
   
    auto host = GetHost();
    
    CHECK_NULL_VOID(host);
    
    auto mainProperty = DynamicCast<ModelPaintProperty>(host->GetPaintProperty<ModelPaintProperty>());
    
    CHECK_NULL_VOID(mainProperty);
    
    auto widthScale = mainProperty->GetRenderWidth().value_or(1.0);
    auto heightScale = mainProperty->GetRenderHeight().value_or(1.0);
    json->PutExtAttr("renderWidth", std::to_string(widthScale).c_str(), filter);
    json->PutExtAttr("renderHeight", std::to_string(heightScale).c_str(), filter);
    json->PutExtAttr("shaderInputBuffer", ShaderInputBufferToStr(mainProperty).c_str(), filter);
    json->PutExtAttr("shaderImageTexture", TextureImagesToStr(mainProperty).c_str(), filter);
    json->PutExtAttr("modelType", SurfaceTypeToStr(modelAdapter_).c_str(), filter);

    json->PutExtAttr("environment", SceneEnvironmentToStr(mainProperty).c_str(), filter);
    json->PutExtAttr("customRender", SceneCustomRenderToStr(mainProperty).c_str(), filter);
    json->PutExtAttr("shader", SceneShaderPathToStr(mainProperty).c_str(), filter);
    json->PutExtAttr("scene", SceneResourceToStr(mainProperty).c_str(), filter);
}

void ModelPattern::OnModifyDone()
{
}

bool ModelPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    return false;
}

void ModelPattern::OnRebuildFrame()
{
}

void ModelPattern::OnAttachToFrameNode()
{
}

void ModelPattern::OnDetachFromFrameNode(FrameNode* node)
{
}
} // namespace OHOS::Ace::NG
