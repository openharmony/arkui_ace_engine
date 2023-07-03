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

#include <EGL/egl.h>
#include "foundation/graphic/graphic_3d/3d_widget_adapter/include/graphics_task.h"
#include "foundation/graphic/graphic_3d/3d_widget_adapter/include/ohos/graphics_manager.h"
#include "render_service_client/core/ui/rs_ui_director.h"
#include "render_service_client/core/ui/rs_ui_share_context.h"

namespace OHOS::Ace::NG {

ModelAdapterWrapper::ModelAdapterWrapper(uint32_t key) : key_(key)
{
    touchHandler_ = MakeRefPtr<ModelTouchHandler>();
    touchHandler_->SetCameraEventCallback([weak = WeakClaim(this)]
        (const OHOS::Render3D::SceneViewerTouchEvent& event) {
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);
        adapter->HandleCameraMove(event);
    });

#if MULTI_ECS_UPDATE_AT_ONCE
    RefPtr<PipelineBase> pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    if (pipeline) {
        OHOS::Render3D::GraphicsManager::GetInstance().AttachContext(pipeline);
    } else {
        LOGE("MODEL_NG: pipeline context is null");
    }
#endif
}

void ModelAdapterWrapper::OnPaint(const RefPtr<ModelPaintProperty>& modelPaintProperty)
{
    auto properties = ExtractPaintProperties(modelPaintProperty);
    if (modelPaintProperty->NeedsCameraSetup()) {
        UpdateCamera(properties);
    }
    if (modelPaintProperty->NeedsLightsSetup()) {
        UpdateLights(properties);
    }
    if (modelPaintProperty->NeedsAnimationsSetup()) {
        UpdateGLTFAnimations(properties);
    }
    if (modelPaintProperty->NeedsGeometriesSetup()) {
        UpdateGeometries(properties);
    }
    if (modelPaintProperty->NeedsCustomRendersSetup()) {
        UpdateCustomRenders(properties);
    }
    if (modelPaintProperty->NeedsShaderPathSetup()) {
        UpdateShaderPath(properties);
    }
    if (modelPaintProperty->NeedsImageTexturePathsSetup()) {
        UpdateImageTexturePaths(properties);
    }
    if (modelPaintProperty->NeedsShaderInputBuffersSetup()) {
        UpdateShaderInputBuffers(properties);
    }
    DrawFrame();
}

void ModelAdapterWrapper::UpdateCamera(const SceneViewerAdapterProperties& properties)
{
    LOGD("MODEL_NG: ModelAdapterWrapper::UpdateCamera()");
#if MULTI_ECS_UPDATE_AT_ONCE
    OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &properties] {
#else
    OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &properties] {
#endif
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);
        adapter->sceneViewerAdapter_->SetUpCameraTransform(properties.cameraPosition_, properties.cameraLookAt_,
            properties.cameraUp_, properties.cameraRotation_);
        adapter->sceneViewerAdapter_->SetUpCameraViewProjection(properties.zNear_, properties.zFar_, properties.fov_);
    });
}

void ModelAdapterWrapper::UpdateLights(const SceneViewerAdapterProperties& properties)
{
    LOGD("MODEL_NG: ModelAdapterWrapper::UpdateLights()");
    if (!properties.lights_.empty()) {
#if MULTI_ECS_UPDATE_AT_ONCE
        OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &properties] {
#else
        OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &properties] {
#endif
            auto adapter = weak.Upgrade();
            CHECK_NULL_VOID(adapter);
            adapter->sceneViewerAdapter_->AddLights(properties.lights_);
            adapter->sceneViewerAdapter_->CreateLight();
        });
    }
}

void ModelAdapterWrapper::UpdateGLTFAnimations(const SceneViewerAdapterProperties& properties)
{
    LOGD("MODEL_NG: ModelAdapterWrapper::UpdateGLTFAnimations() -> %zu", properties.animations_.size());
    if (!properties.animations_.empty()) {
#if MULTI_ECS_UPDATE_AT_ONCE
        OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &properties] {
#else
        OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &properties] {
#endif
            auto adapter = weak.Upgrade();
            CHECK_NULL_VOID(adapter);
            adapter->sceneViewerAdapter_->UpdateGLTFAnimations(properties.animations_);
        });
    }
}

void ModelAdapterWrapper::UpdateGeometries(const SceneViewerAdapterProperties& properties)
{
    LOGD("MODEL_NG: ModelAdapterWrapper::UpdateGeometries() -> %zu", properties.geometries_.size());
    if (!properties.geometries_.empty()) {
#if MULTI_ECS_UPDATE_AT_ONCE
        OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &properties] {
#else
        OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &properties] {
#endif
            auto adapter = weak.Upgrade();
            CHECK_NULL_VOID(adapter);
            adapter->sceneViewerAdapter_->UpdateGeometries(properties.geometries_);
        });
    }
}

void ModelAdapterWrapper::DrawFrame()
{
    ACE_FUNCTION_TRACE();
    // if open MULTI_ECS_UPDATE_AT_ONCE macro  SetGSVsyncCallback is called on current thread
    // that means all the 3D engine task should be in syncorinize manner.
#if MULTI_ECS_UPDATE_AT_ONCE
    OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this)] {
#else
    // Async painting does not seem to work.
    OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this)] {
#endif
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);
        adapter->sceneViewerAdapter_->DrawFrame();
    });
}

void ModelAdapterWrapper::OnPaintFinish()
{
    if (callback_) {
        callback_();
    }
}

SkDrawable* ModelAdapterWrapper::GetDrawable(OffsetF offset)
{
    /*
        Async painting does not seem to work.
    */
    CHECK_NULL_RETURN(textureLayer_, nullptr);
    textureLayer_->SetOffset(offset.GetX(), offset.GetY());
    ACE_FUNCTION_TRACE();

    return textureLayer_.get();
}

std::shared_ptr<OHOS::Render3D::TextureLayer> ModelAdapterWrapper::GetTextureLayer(OffsetF offset)
{
    textureLayer_->SetOffset(offset.GetX(), offset.GetY());
    return textureLayer_;
}

void ModelAdapterWrapper::OnMeasureContent(const RefPtr<ModelLayoutProperty>& modelLayoutProperty, SizeF size)
{
    LOGD("MODEL_NG: OnMeasureContent");
    bool sizeChanged = size_.UpdateSizeWithCheck(size);
    bool sceneChanged = modelLayoutProperty->NeedsSceneSetup();
    bool needsSetup = !sceneIsSetUp_ || sceneChanged || sizeChanged;

    if (IsInitialized() && sceneChanged) {
        UnloadScene();
    }

    if (!IsInitialized()) {
        Initialize();
    }

    if (!IsInitialized()) {
        // Failed to create TextureLayer or Engine, or Cannot obtain EGL context
        LOGW("MODEL_NG: OnMeasureContent() - Failed to initialize");
        return;
    }

    if (sizeChanged) {
        UpdateTextureLayer();
    }

    if (needsSetup) {
        modelLayoutProperty->UpdateNeedsSceneSetup(false);
        auto properties = ExtractLayoutProperties(modelLayoutProperty);
        UpdateSceneViewerAdapter(properties);
    }
}

void ModelAdapterWrapper::Initialize()
{
    // Obtain EGLContext
    EGLContext eglContext = GetRenderContext();

    if (eglContext == EGL_NO_CONTEXT) {
        LOGW("MODEL_NG: Initialize() - No render context. Start unify rendering");
    }

    CreateTextureLayer(eglContext);
    CreateSceneViewerAdapter(eglContext_);
}

void ModelAdapterWrapper::CreateSceneViewerAdapter(const EGLContext& eglContext)
{
    sceneViewerAdapter_ = std::make_shared<OHOS::Render3D::SceneViewerAdapter>(GetKey());
#if MULTI_ECS_UPDATE_AT_ONCE
    OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &eglContext] {
#else
    // init engine in async manner sometimes crash on screen rotation
    OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &eglContext] {
#endif
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);
        auto& gfxManager = OHOS::Render3D::GraphicsManager::GetInstance();
        auto &&engine = gfxManager.GetEngine(OHOS::Render3D::EngineFactory::EngineType::LUME, eglContext);
        LOGD("MODEL_NG: ModelAdapterWrapper::CreateSceneViewerAdapter() init Engine key_ = %d", adapter->GetKey());
        adapter->sceneViewerAdapter_->SetEngine(std::move(engine));
    });
}

void ModelAdapterWrapper::UpdateSceneViewerAdapter(const SceneViewerAdapterProperties& properties)
{
#if MULTI_ECS_UPDATE_AT_ONCE
    OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &properties] {
#else
    OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &properties] {
#endif
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);
        const OHOS::Render3D::TextureInfo& obj = *(adapter->textureInfo_);
        adapter->sceneViewerAdapter_->SetUpSceneViewer(
            obj, properties.gltfSrc_, properties.backgroundSrc_, properties.bgType_);
        LOGD("MODEL_NG: ModelAdapterWrapper::UpdateSceneViewerAdapter() glTFSrc_ %s GetKey() %d",
            properties.gltfSrc_.c_str(), adapter->GetKey());
        adapter->sceneIsSetUp_ = true;
    });
}

void ModelAdapterWrapper::CreateTextureLayer(const EGLContext& eglContext)
{
    // texture create must in sync manner
    OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &eglContext] {
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);
        auto& gfxManager = OHOS::Render3D::GraphicsManager::GetInstance();
        gfxManager.Register(adapter->GetKey());

        adapter->eglContext_ = gfxManager.CreateOffScreenContext(eglContext);
        adapter->textureLayer_ = std::make_shared<OHOS::Render3D::TextureLayer>();
        auto info = adapter->textureLayer_->CreateRenderTarget(adapter->size_.Width(), adapter->size_.Height());
        adapter->textureInfo_ = std::make_shared<OHOS::Render3D::TextureInfo>(std::move(info));
        adapter->textureLayer_->SetTextureInfo(info);
    });
}

void ModelAdapterWrapper::UpdateTextureLayer()
{
    CHECK_NULL_VOID(textureLayer_);
    textureLayer_->SetWH(size_.Width(), size_.Height());
}

void ModelAdapterWrapper::UnloadScene()
{
#if MULTI_ECS_UPDATE_AT_ONCE
    OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this)] {
#else
    OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this)] {
#endif
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);
        adapter->sceneViewerAdapter_->UnLoadModel();
        LOGD("MODEL_NG: UnloadScene -> Unload model GetKey() %d", adapter->GetKey());
    });
}

SceneViewerAdapterProperties ModelAdapterWrapper::ExtractLayoutProperties(
    const RefPtr<ModelLayoutProperty>& modelLayoutProperty)
{
    SceneViewerAdapterProperties properties {};
    properties.gltfSrc_ = modelLayoutProperty->GetModelSource().value_or(properties.gltfSrc_);
    properties.backgroundSrc_ = modelLayoutProperty->GetModelBackground().value_or(properties.backgroundSrc_);
    bool isTransparent = modelLayoutProperty->GetModelTransparent().value_or(false);
    properties.bgType_ = isTransparent ? OHOS::Render3D::SceneViewerBackgroundType::TRANSPARENT :
        OHOS::Render3D::SceneViewerBackgroundType::CUBE_MAP;

    return properties;
}

SceneViewerAdapterProperties ModelAdapterWrapper::ExtractPaintProperties(
    const RefPtr<ModelPaintProperty>& modelPaintProperty)
{
    SceneViewerAdapterProperties properties {};

    auto cameraPosition = modelPaintProperty->GetCameraPosition().value_or(properties.cameraPosition_.GetVec());
    auto cameraDistance = modelPaintProperty->GetCameraDistance().value_or(properties.cameraPosition_.GetDistance());
    auto cameraIsAngular = modelPaintProperty->GetCameraIsAngular().value_or(properties.cameraPosition_.GetIsAngular());
    properties.cameraPosition_.SetVec(cameraPosition);
    properties.cameraPosition_.SetDistance(cameraDistance);
    properties.cameraPosition_.SetIsAngular(cameraIsAngular);
    properties.cameraRotation_ = modelPaintProperty->GetCameraRotation().value_or(properties.cameraRotation_);
    properties.cameraLookAt_ = modelPaintProperty->GetCameraLookAt().value_or(properties.cameraLookAt_);
    properties.cameraUp_ = modelPaintProperty->GetCameraUp().value_or(properties.cameraUp_);
    properties.zNear_ = modelPaintProperty->GetCameraZNear().value_or(properties.zNear_);
    properties.zFar_ = modelPaintProperty->GetCameraZFar().value_or(properties.zFar_);
    properties.fov_ = modelPaintProperty->GetCameraFOV().value_or(properties.fov_);
    properties.lights_ = modelPaintProperty->GetModelLights().value_or(properties.lights_);
    properties.animations_ = modelPaintProperty->GetModelAnimations().value_or(properties.animations_);
    properties.geometries_ = modelPaintProperty->GetModelGeometries().value_or(properties.geometries_);
    properties.customRenders_ = modelPaintProperty->GetModelCustomRenders().value_or(properties.customRenders_);
    properties.shaderPath_ = modelPaintProperty->GetShaderPath().value_or(properties.shaderPath_);
    properties.imageTexturePaths_ =
        modelPaintProperty->GetModelImageTexturePaths().value_or(properties.imageTexturePaths_);
    properties.shaderInputBuffers_ =
        modelPaintProperty->GetModelShaderInputBuffers().value_or(properties.shaderInputBuffers_);
    return properties;
}

EGLContext ModelAdapterWrapper::GetRenderContext()
{
    auto ret = EGL_NO_CONTEXT;
    ret = Rosen::RSUIShareContext::GetInstance().GetRsRenderContext();
    return ret;
}

bool ModelAdapterWrapper::IsInitialized()
{
    return sceneViewerAdapter_ ? true : false;
}

bool ModelAdapterWrapper::IsReady()
{
    return IsInitialized() && sceneIsSetUp_;
}

bool ModelAdapterWrapper::NeedsRepaint()
{
    if (!sceneViewerAdapter_) {
        return false;
    }

    if (sceneViewerAdapter_->IsAnimating() || sceneViewerAdapter_->HandlesNotReady()) {
        return true;
    }

    return needsRepaint_;
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
    return touchHandler_->HandleTouchEvent(info);
}

void ModelAdapterWrapper::HandleCameraMove(const OHOS::Render3D::SceneViewerTouchEvent& event)
{
    LOGD("MODEL_NG HandleCameraMove() eventId[%d], eventType[%zu], position[%.2f, %.2f], delta[%.2f, %.2f], key = %d",
    event.GetFingerId(), event.GetEventType(), event.GetGlobalLocation().GetX(), event.GetGlobalLocation().GetY(),
    event.GetDeltaChange().GetX(), event.GetDeltaChange().GetY(), GetKey());
#if MULTI_ECS_UPDATE_AT_ONCE
    OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &event] {
#else
    OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &event] {
#endif
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);
        adapter->sceneViewerAdapter_->OnTouchEvent(event);
    });
}

void ModelAdapterWrapper::UpdateCustomRenders(const SceneViewerAdapterProperties& properties)
{
    LOGD("MODEL_NG: ModelAdapterWrapper::UpdateCustomRenders() size: %zu", properties.customRenders_.size());
    if (!properties.customRenders_.empty()) {
#if MULTI_ECS_UPDATE_AT_ONCE
        OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &properties] {
#else
        OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &properties] {
#endif
            auto adapter = weak.Upgrade();
            CHECK_NULL_VOID(adapter);
            adapter->sceneViewerAdapter_->AddCustomRenders(properties.customRenders_);
        });
    }
}

void ModelAdapterWrapper::UpdateShaderPath(const SceneViewerAdapterProperties& properties)
{
    LOGD("ModelAdapterWrapper::UpdateShaderPath() %s", properties.shaderPath_.c_str());
#if MULTI_ECS_UPDATE_AT_ONCE
    OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &properties] {
#else
    OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &properties] {
#endif
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);
        adapter->sceneViewerAdapter_->UpdateShaderPath(properties.shaderPath_);
    });
}

void ModelAdapterWrapper::UpdateImageTexturePaths(const SceneViewerAdapterProperties& properties)
{
    LOGD("MODEL_NG: ModelAdapterWrapper::UpdateImageTexturePaths() size: %zu", properties.imageTexturePaths_.size());
    if (!properties.imageTexturePaths_.empty()) {
#if MULTI_ECS_UPDATE_AT_ONCE
        OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &properties] {
#else
        OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &properties] {
#endif
            auto adapter = weak.Upgrade();
            CHECK_NULL_VOID(adapter);
            adapter->sceneViewerAdapter_->UpdateImageTexturePaths(properties.imageTexturePaths_);
        });
    }
}

void ModelAdapterWrapper::UpdateShaderInputBuffers(const SceneViewerAdapterProperties& properties)
{
    LOGD("MODEL_NG: ModelAdapterWrapper::UpdateShaderInputBuffers() size: %zu", properties.shaderInputBuffers_.size());
    if (!properties.shaderInputBuffers_.empty()) {
#if MULTI_ECS_UPDATE_AT_ONCE
        OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &properties] {
#else
        OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &properties] {
#endif
            auto adapter = weak.Upgrade();
            CHECK_NULL_VOID(adapter);
            adapter->sceneViewerAdapter_->UpdateShaderInputBuffers(properties.shaderInputBuffers_);
        });
    }
}

} // namespace OHOS::Ace::NG
