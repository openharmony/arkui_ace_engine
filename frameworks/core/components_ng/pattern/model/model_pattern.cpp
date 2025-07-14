/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void ModelPattern::OnRebuildFrame()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetRenderContext();
    modelAdapter_->OnRebuildFrame(context);
}

ModelPattern::ModelPattern(uint32_t key, const ModelViewContext& context) : key_(key)
{
    modelAdapter_ = MakeRefPtr<ModelAdapterWrapper>(key_, context);
    modelAdapter_->SetPaintFinishCallback([weak = WeakClaim(this)]() {
            auto model = weak.Upgrade();
            if (model) {
                if (model->NeedsRepaint()) {
                    model->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
                }
                model->GetPaintProperty<ModelPaintProperty>()->ResetFlagProperties();
            }
        });
}
ModelPattern::ModelPattern(uint32_t key) : key_(key)
{
}

void ModelPattern::SetModelViewContext(const ModelViewContext& context)
{
    modelAdapter_ = MakeRefPtr<ModelAdapterWrapper>(key_, context);
    modelAdapter_->SetPaintFinishCallback([weak = WeakClaim(this)]() {
            auto model = weak.Upgrade();
            if (model) {
                if (model->NeedsRepaint()) {
                    model->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
                }
                model->GetPaintProperty<ModelPaintProperty>()->ResetFlagProperties();
            }
        });
}

void ModelPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetOrCreateEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    if (touchListener_) {
        return;
    }
    auto touchTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleTouchEvent(info);
        }
    };

    if (touchListener_) {
        gestureHub->RemoveTouchEvent(touchListener_);
    }
    touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gestureHub->AddTouchEvent(touchListener_);
}

bool ModelPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    CHECK_NULL_RETURN(modelAdapter_, false);
    auto host = GetHost();
    CHECK_NULL_RETURN(dirty, false);
    CHECK_NULL_RETURN(host, false);
    auto geometryNode = dirty->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);

    auto mainProperty = DynamicCast<ModelPaintProperty>(host->GetPaintProperty<ModelPaintProperty>());
    auto widthScale = mainProperty->GetRenderWidth().value_or(1.0);
    auto heightScale = mainProperty->GetRenderHeight().value_or(1.0);

    auto contentSize = geometryNode->GetContentSize();
    auto contentOffset = geometryNode->GetContentOffset();

    bool measure = (config.skipMeasure || dirty->SkipMeasureContent()) ? false : true;
    float width = contentSize.Width();
    float height = contentSize.Height();
    float scale = PipelineContext::GetCurrentContextSafelyWithCheck()->GetViewScale();
    Render3D::WindowChangeInfo windowChangeInfo {
        contentOffset.GetX(), contentOffset.GetY(),
        width, height,
        scale, widthScale, heightScale,
        config.contentSizeChange, modelAdapter_->GetSurfaceType(), rotation_,
    };
    modelAdapter_->OnDirtyLayoutWrapperSwap(windowChangeInfo);
    host->MarkNeedSyncRenderTree();

    return measure;
}

void ModelPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(modelAdapter_);
    // hint
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddWindowStateChangedCallback(host->GetId());
    uint32_t rotation = pipeline->GetTransformHint();
    if (rotation_ != rotation) {
        rotation_ = rotation;
    }
    auto callbackId = pipeline->RegisterTransformHintChangeCallback([weak = WeakClaim(this)](uint32_t rotation) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->rotation_ = rotation;
        }
    });
    UpdateTransformHintChangedCallbackId(callbackId);
    modelAdapter_->OnAttachToFrameNode(host->GetRenderContext());
}

void ModelPattern::OnDetachFromFrameNode(FrameNode* node)
{
    CHECK_NULL_VOID(node);
    auto id = node->GetId();
    auto pipeline = node->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowStateChangedCallback(id);

    if (HasTransformHintChangedCallbackId()) {
        pipeline->UnregisterTransformHintChangedCallback(transformHintChangedCallbackId_.value_or(-1));
    }
}

void ModelPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    CHECK_NULL_VOID(modelAdapter_);
    auto mainProperty = DynamicCast<ModelPaintProperty>(GetHost()->GetPaintProperty<ModelPaintProperty>());
    bool repaint = modelAdapter_->HandleTouchEvent(info, mainProperty);
    if (repaint) {
        MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

bool ModelPattern::NeedsRepaint()
{
    CHECK_NULL_RETURN(modelAdapter_, false);
    return modelAdapter_->NeedsRepaint();
}

void ModelPattern::MarkDirtyNode(const PropertyChangeFlag flag)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(flag);
}

static std::string TextureImagesToStr(const RefPtr<ModelPaintProperty>& modelPaintProperty)
{
    std::string ret;
    if (!modelPaintProperty->HasModelImageTexturePaths() ||
            modelPaintProperty->GetModelImageTexturePathsValue().empty()) {
        return ret;
    }
    auto& imageTextures = modelPaintProperty->GetModelImageTexturePaths().value();
    for (auto& imageTexture : imageTextures) {
        ret += imageTexture + " ";
    }
    return ret;
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

static std::string SceneResourceToStr(const RefPtr<ModelPaintProperty>& modelPaintProperty)
{
    std::string ret;
    if (!modelPaintProperty->HasModelSource() || modelPaintProperty->GetModelSourceValue().empty()) {
        return ret;
    }
    ret = modelPaintProperty->GetModelSource().value();
    return ret;
}

static std::string SceneEnvironmentToStr(const RefPtr<ModelPaintProperty>& modelPaintProperty)
{
    std::string ret;
    if (!modelPaintProperty->HasModelBackground() || modelPaintProperty->GetModelBackgroundValue().empty()) {
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
    if (!modelPaintProperty->HasShaderPath() || modelPaintProperty->GetShaderPathValue().empty()) {
        return ret;
    }
    ret = modelPaintProperty->GetShaderPath().value();
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

ModelPattern::~ModelPattern()
{
    CHECK_NULL_VOID(modelAdapter_);
    modelAdapter_->Deinit();
}
} // namespace OHOS::Ace::NG
