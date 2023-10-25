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

#include "core/components_ng/pattern/model/model_adapter_wrapper.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"

#include "graphics_task.h"
#include "ohos/graphics_manager.h"

#include "render_service_client/core/ui/rs_ui_director.h"
#include "render_service_client/core/ui/rs_ui_share_context.h"

namespace OHOS::Ace::NG {

ModelAdapterWrapper::ModelAdapterWrapper(uint32_t key, Render3D::SurfaceType surfaceType) : key_(key),
    surfaceType_(surfaceType)
{
    touchHandler_ = MakeRefPtr<ModelTouchHandler>();
    touchHandler_->SetCameraEventCallback([weak = WeakClaim(this)]
        (const Render3D::PointerEvent& event) {
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);
        adapter->HandleCameraMove(event);
    });

#if MULTI_ECS_UPDATE_AT_ONCE
    RefPtr<PipelineBase> pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    if (pipeline) {
        Render3D::GraphicsManager::GetInstance().AttachContext(pipeline);
    } else {
        LOGE("MODEL_NG: pipeline context is null");
    }
#endif
}

void ModelAdapterWrapper::CreateTextureLayer()
{
    Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this)] {
        LOGD("CreateTexture layer Register key %d", key);
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);

        auto& gfxManager = Render3D::GraphicsManager::GetInstance();
        const auto& key = adapter->GetKey();
        gfxManager.Register(key);
        adapter->textureLayer_ = std::make_unique<Render3D::TextureLayer>(key);
    });
}

void ModelAdapterWrapper::CreateWidgetAdapter()
{
    LOGD("ModelAdapterWrapper::CreateWidgetAdapter key %d", GetKey());
    auto key = GetKey();

    // init engine in async manager sometimes crash on screen rotation
    Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), key] {
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);

        adapter->widgetAdapter_ = std::make_shared<Render3D::WidgetAdapter>(key);
        auto& gfxManager = Render3D::GraphicsManager::GetInstance();
        auto&& engine = gfxManager.GetEngine(Render3D::EngineFactory::EngineType::LUME, adapter->GetKey());
        adapter->widgetAdapter_->Initialize(std::move(engine));
    });
}

void ModelAdapterWrapper::OnAttachToFrameNode(const RefPtr<RenderContext>& context)
{
    CreateTextureLayer();
    CreateWidgetAdapter();

#ifdef ENABLE_ROSEN_BACKEND
    auto rsContext = DynamicCast<NG::RosenRenderContext>(context);
    CHECK_NULL_VOID(rsContext);
    auto rsNode = rsContext->GetRSNode();
    CHECK_NULL_VOID(rsNode);
    rsNode->SetFrameGravity(Rosen::Gravity::RESIZE);
#endif
}

void ModelAdapterWrapper::OnDirtyLayoutWrapperSwap(float offsetX, float offsetY, float width, float height,
    float scale, bool recreateWindow)
{
    needsSyncPaint_ = true;
    Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), offsetX, offsetY,
        width, height, scale, recreateWindow] {
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);
        CHECK_NULL_VOID(adapter->textureLayer_);
        CHECK_NULL_VOID(adapter->widgetAdapter_);

        adapter->textureLayer_->OnWindowChange(offsetX, offsetY, width, height, scale, recreateWindow,
            adapter->surfaceType_);
        adapter->widgetAdapter_->OnWindowChange(adapter->textureLayer_->GetTextureInfo());
    });
}

void ModelAdapterWrapper::OnRebuildFrame(RefPtr<RenderContext>& context)
{
    LOGD("adapter OnRebuildFrame with context");
    CHECK_NULL_VOID(textureLayer_);

#ifdef ENABLE_ROSEN_BACKEND
    CHECK_NULL_VOID(context);
    auto rsNode = DynamicCast<NG::RosenRenderContext>(context)->GetRSNode();
    textureLayer_->SetParent(rsNode);
#endif
}

void ModelAdapterWrapper::OnPaint3D(const RefPtr<ModelPaintProperty>& modelPaintProperty)
{
    CHECK_NULL_VOID(modelPaintProperty);

    if (modelPaintProperty->NeedsCameraSetup()) {
        UpdateCamera(modelPaintProperty);
    }

    if (modelPaintProperty->NeedsLightsSetup()) {
        UpdateLights(modelPaintProperty);
    }

    if (modelPaintProperty->NeedsAnimationsSetup()) {
        UpdateGLTFAnimations(modelPaintProperty);
    }

    if (modelPaintProperty->NeedsGeometriesSetup()) {
        UpdateGeometries(modelPaintProperty);
    }

    if (modelPaintProperty->NeedsModelSourceSetup()) {
        UpdateScene(modelPaintProperty);
    }

    if (modelPaintProperty->NeedsModelBackgroundSetup()) {
        UpdateEnviroment(modelPaintProperty);
    }

    if (modelPaintProperty->NeedsCustomRenderSetup()) {
        UpdateCustomRender(modelPaintProperty);
    }

    if (modelPaintProperty->NeedsShaderPathSetup()) {
        UpdateShaderPath(modelPaintProperty);
    }

    if (modelPaintProperty->NeedsImageTexturePathsSetup()) {
        UpdateImageTexturePaths(modelPaintProperty);
    }

    if (modelPaintProperty->NeedsShaderInputBufferSetup()) {
        UpdateShaderInputBuffers(modelPaintProperty);
    }

    DrawFrame();
}

void ModelAdapterWrapper::OnPaint3DSceneTexture(SkCanvas* skCanvas)
{
    textureLayer_->OnDraw(skCanvas);
}

void ModelAdapterWrapper::DrawFrame()
{
    ACE_FUNCTION_TRACE();
    const auto& msg = [weak = WeakClaim(this)] {
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);
        CHECK_NULL_VOID(adapter->widgetAdapter_);

        adapter->widgetAdapter_->DrawFrame();
    };

    if (needsSyncPaint_) {
#if !defined (MULTI_ECS_UPDATE_AT_ONCE) || (MULTI_ECS_UPDATE_AT_ONCE == 0)
        needsSyncPaint_ = false;
#endif
        Render3D::GraphicsTask::GetInstance().PushSyncMessage(msg);
    } else {
        Render3D::GraphicsTask::GetInstance().PushAsyncMessage(msg);
    }
}

void ModelAdapterWrapper::OnPaintFinish()
{
    if (callback_) {
        callback_();
    }
}

void ModelAdapterWrapper::UnloadSceneAndBackground()
{
    Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this)] {
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);
        CHECK_NULL_VOID(adapter->widgetAdapter_);

        adapter->widgetAdapter_->UnloadSceneModel();
        adapter->widgetAdapter_->UnloadEnvModel();
        LOGD("MODEL_NG: UnloadScene -> Unload model GetKey() %d", adapter->GetKey());
    });
}

bool ModelAdapterWrapper::NeedsRepaint()
{
    bool needsRepaint = false;
    Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &needsRepaint] {
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);
        CHECK_NULL_VOID(adapter->widgetAdapter_);

        needsRepaint = adapter->widgetAdapter_->NeedsRepaint();
    });

    return needsRepaint;
}

ModelAdapterWrapper::~ModelAdapterWrapper()
{
    Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this)] {
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);
        Render3D::GraphicsManager::GetInstance().UnRegister(adapter->GetKey());
    });
}

uint32_t ModelAdapterWrapper::GetKey()
{
    return key_;
}

void ModelAdapterWrapper::SetPaintFinishCallback(PaintFinishCallback callback)
{
    callback_ = std::move(callback);
}

bool ModelAdapterWrapper::HandleTouchEvent(const TouchEventInfo& info)
{
    CHECK_NULL_RETURN(touchHandler_, false);
    CHECK_NULL_RETURN(textureLayer_, false);
    const auto& textureInfo = textureLayer_->GetTextureInfo();
    auto width = textureInfo.width_;
    auto height = textureInfo.height_;
    return touchHandler_->HandleTouchEvent(info, width, height);
}

void ModelAdapterWrapper::UpdateScene(const RefPtr<ModelPaintProperty>& modelPaintProperty)
{
    if (!modelPaintProperty->GetModelSource().has_value()) {
        LOGW("UpdateScene invalid model source");
        return;
    }

    auto& modelSource = modelPaintProperty->GetModelSource().value();
    Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), modelSource] {
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);
        CHECK_NULL_VOID(adapter->widgetAdapter_);

        adapter->widgetAdapter_->LoadSceneModel(modelSource.c_str());
    });
}

void ModelAdapterWrapper::UpdateEnviroment(const RefPtr<ModelPaintProperty>& modelPaintProperty)
{
    if (!modelPaintProperty->GetModelBackground().has_value()) {
        LOGW("UpdateEnviroment invalid model background");
        return;
    }

    Render3D::BackgroundType backgroundType = modelPaintProperty->GetModelTransparent().value_or(false) ?
        Render3D::BackgroundType::TRANSPARENT : Render3D::BackgroundType::CUBE_MAP;
    auto& backgroundPath = modelPaintProperty->GetModelBackground().value();

    Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &backgroundPath,
        &backgroundType] {
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);
        CHECK_NULL_VOID(adapter->widgetAdapter_);

        adapter->widgetAdapter_->LoadEnvModel(backgroundPath, backgroundType);
    });
}

void ModelAdapterWrapper::HandleCameraMove(const Render3D::PointerEvent& event)
{
    Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &event] {
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);
        CHECK_NULL_VOID(adapter->widgetAdapter_);

        adapter->widgetAdapter_->OnTouchEvent(event);
    });
}

void ExtractCameraProperty(const RefPtr<ModelPaintProperty>& modelPaintProperty,
    CameraProperty& camera)
{
    if (modelPaintProperty->GetCameraPosition().has_value()) {
        auto& v = modelPaintProperty->GetCameraPosition().value();
        camera.position_.SetPosition(Render3D::Vec3 { v.GetX(), v.GetY(), v.GetZ() });
    }

    if (modelPaintProperty->GetCameraDistance().has_value()) {
        const auto& v = modelPaintProperty->GetCameraDistance().value().GetValue();
        camera.position_.SetDistance(v);
    }

    if (modelPaintProperty->GetCameraIsAngular().has_value()) {
        auto& v = modelPaintProperty->GetCameraIsAngular().value();
        camera.position_.SetIsAngular(v);
    }

    if (modelPaintProperty->GetCameraLookAt().has_value()) {
        const auto& v = modelPaintProperty->GetCameraLookAt().value();
        camera.lookAt_.SetX(v.GetX());
        camera.lookAt_.SetY(v.GetY());
        camera.lookAt_.SetZ(v.GetZ());
    }

    if (modelPaintProperty->GetCameraUp().has_value()) {
        const auto& v = modelPaintProperty->GetCameraUp().value();
        camera.up_.SetX(v.GetX());
        camera.up_.SetY(v.GetY());
        camera.up_.SetZ(v.GetZ());
    }

    if (modelPaintProperty->GetCameraUp().has_value()) {
        const auto& v = modelPaintProperty->GetCameraUp().value();
        camera.up_.SetX(v.GetX());
        camera.up_.SetY(v.GetY());
        camera.up_.SetZ(v.GetZ());
    }

    if (modelPaintProperty->GetCameraRotation().has_value()) {
        const auto& v = modelPaintProperty->GetCameraRotation().value();
        camera.rotation_.SetX(v.GetX());
        camera.rotation_.SetY(v.GetY());
        camera.rotation_.SetZ(v.GetZ());
        camera.rotation_.SetW(v.GetW());
    }

    if (modelPaintProperty->GetCameraZNear().has_value()) {
        camera.near_ = modelPaintProperty->GetCameraZNear().value();
    }

    if (modelPaintProperty->GetCameraZFar().has_value()) {
        camera.far_ = modelPaintProperty->GetCameraZFar().value();
    }

    if (modelPaintProperty->GetCameraFOV().has_value()) {
        camera.fov_ = modelPaintProperty->GetCameraFOV().value();
    }
}

void ModelAdapterWrapper::UpdateCamera(const RefPtr<ModelPaintProperty>& modelPaintProperty)
{
    LOGD("MODEL_NG: ModelAdapterWrapper::UpdateCamera()");
    CameraProperty camera;
    ExtractCameraProperty(modelPaintProperty, camera);
    Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &camera] {
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);
        CHECK_NULL_VOID(adapter->widgetAdapter_);
        
        adapter->widgetAdapter_->SetupCameraTransform(camera.position_, camera.lookAt_, camera.up_,
            camera.rotation_);
        adapter->widgetAdapter_->SetupCameraViewProjection(camera.near_, camera.far_, camera.fov_);
    });
}

void ExtractLightsProperty(const RefPtr<ModelPaintProperty>& modelPaintProperty,
    std::vector<std::shared_ptr<Render3D::Light>>& lights)
{
    auto& propLights = modelPaintProperty->GetModelLights().value();
    for (auto& light : propLights) {
        const auto& color = light->GetLightColor();
        const auto& rotation = light->GetRotation();
        const auto& position = light->GetPosition();

        Render3D::Position lightPosition;
        lightPosition.SetPosition(Render3D::Vec3(position.GetX(), position.GetY(), position.GetZ()));
        lightPosition.SetDistance(position.GetDistance().GetValue());
        lightPosition.SetIsAngular(position.GetIsAngular());
        Render3D::LightType lightType;
        switch (light->GetLightType()) {
            case ModelLightType::INVALID_LIGHT:
                lightType = Render3D::LightType::INVALID;
                break;
            case ModelLightType::DIRECTIONAL_LIGHT:
                lightType = Render3D::LightType::DIRECTIONAL;
                break;
            case ModelLightType::POINT_LIGHT:
                lightType = Render3D::LightType::POINT;
                break;
            case ModelLightType::SPOT_LIGHT:
                lightType = Render3D::LightType::SPOT;
                break;
            default:
                LOGW("invalid light type");
        }

        lights.push_back(std::make_shared<Render3D::Light>(lightType, Render3D::Vec3(
            color.GetX(), color.GetY(), color.GetZ()), light->GetLightIntensity().GetValue(),
            light->GetLightShadow(), lightPosition, Render3D::Quaternion(rotation.GetX(),
            rotation.GetY(), rotation.GetZ(), rotation.GetW())));
    }
}

void ModelAdapterWrapper::UpdateLights(const RefPtr<ModelPaintProperty>& modelPaintProperty)
{
    if (!modelPaintProperty->GetModelLights().has_value()) {
        LOGW("MODEL_NG: UpdateLights invalid lights");
        return;
    }

    std::vector<std::shared_ptr<Render3D::Light>> lights;
    ExtractLightsProperty(modelPaintProperty, lights);

    Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &lights] {
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);
        CHECK_NULL_VOID(adapter->widgetAdapter_);

        adapter->widgetAdapter_->UpdateLights(lights);
    });
}

void ModelAdapterWrapper::UpdateGLTFAnimations(const RefPtr<ModelPaintProperty>& modelPaintProperty)
{
    if (!modelPaintProperty->GetModelAnimations().has_value()) {
        LOGW("UpdateGLTFAnimations invalid animation");
        return;
    }

    auto& animations = modelPaintProperty->GetModelAnimations().value();
    Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &animations] {
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);
        CHECK_NULL_VOID(adapter->widgetAdapter_);

        adapter->widgetAdapter_->UpdateGLTFAnimations(animations);
    });
}

void ModelAdapterWrapper::UpdateGeometries(const RefPtr<ModelPaintProperty>& modelPaintProperty)
{
    if (!modelPaintProperty->GetModelGeometries().has_value()) {
        LOGW("UpdateGeometries invalid geometries");
        return;
    }

    auto& geometries = modelPaintProperty->GetModelGeometries().value();

    Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &geometries] {
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);
        CHECK_NULL_VOID(adapter->widgetAdapter_);

        adapter->widgetAdapter_->UpdateGeometries(geometries);
    });
}

void ModelAdapterWrapper::UpdateCustomRender(const RefPtr<ModelPaintProperty>& modelPaintProperty)
{
    if (!modelPaintProperty->GetModelCustomRender().has_value()) {
        LOGW("UpdateCustomRender invalid custom render");
        return;
    }

    auto& customRender = modelPaintProperty->GetModelCustomRender().value();
    if (!customRender) {
        return;
    }

    Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &customRender] {
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);
        CHECK_NULL_VOID(adapter->widgetAdapter_);

        adapter->widgetAdapter_->UpdateCustomRender(customRender);
    });
}

void ModelAdapterWrapper::UpdateShaderPath(const RefPtr<ModelPaintProperty>& modelPaintProperty)
{
    if (!modelPaintProperty->GetShaderPath().has_value()) {
        LOGW("UpdateShaderPath invalid shader path");
        return;
    }

    auto& shaderPath = modelPaintProperty->GetShaderPath().value();

    Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &shaderPath] {
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);
        CHECK_NULL_VOID(adapter->widgetAdapter_);

        adapter->widgetAdapter_->UpdateShaderPath(shaderPath);
    });
}

void ModelAdapterWrapper::UpdateImageTexturePaths(const RefPtr<ModelPaintProperty>& modelPaintProperty)
{
    if (!modelPaintProperty->GetModelImageTexturePaths().has_value()) {
        LOGW("UpdateImageTexturePaths invalid image texture");
        return;
    }

    auto& imageTexture = modelPaintProperty->GetModelImageTexturePaths().value();

    Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &imageTexture] {
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);
        CHECK_NULL_VOID(adapter->widgetAdapter_);

        adapter->widgetAdapter_->UpdateImageTexturePaths(imageTexture);
    });
}

void ModelAdapterWrapper::UpdateShaderInputBuffers(const RefPtr<ModelPaintProperty>& modelPaintProperty)
{
    if (!modelPaintProperty->GetModelShaderInputBuffer().has_value()) {
        LOGW("UpdateShaderInputBuffers invalid shader input buffer");
        return;
    }

    auto& shaderInputBuffer = modelPaintProperty->GetModelShaderInputBuffer().value();

    Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &shaderInputBuffer] {
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);
        CHECK_NULL_VOID(adapter->widgetAdapter_);

        adapter->widgetAdapter_->UpdateShaderInputBuffer(shaderInputBuffer);
    });
}
} // namespace OHOS::Ace::NG