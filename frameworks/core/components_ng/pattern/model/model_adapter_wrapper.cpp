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
}

void ModelAdapterWrapper::OnPaint(const RefPtr<ModelPaintProperty>& modelPaintProperty)
{
    if (!setupDone_) {
        LOGE("MODEL_NG: ModelAdapterWrapper::OnPaint() setup not done!");
        return;
    }

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
    LOGD("MODEL_NG: ModelAdapterWrapper::UpdateGLTFAnimations() -> %u", properties.animations_.size());
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
    LOGD("MODEL_NG: ModelAdapterWrapper::UpdateGeometries() -> %u", properties.geometries_.size());
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

void ModelAdapterWrapper::OnMeasureContent(const RefPtr<ModelLayoutProperty>& modelLayoutProperty, SizeF size)
{
    bool sizeChanged = size_.UpdateSizeWithCheck(size);
    bool needsUpdate = sizeChanged || modelLayoutProperty->NeedsSceneSetup();

    // Do not create Texture layer with zero size.
    if (!textureLayer_ && NearEqual(size_.Width(), 0) && NearEqual(size_.Height(), 0)) {
        LOGE("MODEL_NG: ModelAdapterWrapper::OnMeasureContent() size is zero!");
        return;
    }

    if (sizeChanged && textureLayer_) {
        textureLayer_->SetWH(size_.Width(), size_.Height());
    }

    if (IsInitialized() && needsUpdate) {
        UnloadScene();
    }

    if (!IsInitialized()) {
        Initialize();
    }

    if (needsUpdate) {
        modelLayoutProperty->UpdateNeedsSceneSetup(false);
        auto properties = ExtractLayoutProperties(modelLayoutProperty);
        UpdateSceneViewerAdapter(properties);
    }
}

void ModelAdapterWrapper::Initialize()
{
    // Obtain EGLContext
    EGLContext eglContext = GetRenderContext();

    CreateTextureLayer(eglContext);
    CreateSceneViewerAdapter(eglContext);
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
        adapter->setupDone_ = true;
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

        auto info = gfxManager.CreateRenderTexture(adapter->GetKey(),
            adapter->size_.Width(), adapter->size_.Height(), eglContext);
        adapter->textureInfo_ = std::make_shared<OHOS::Render3D::TextureInfo>(std::move(info));
        adapter->textureLayer_ = std::shared_ptr<OHOS::Render3D::TextureLayer> {
            new OHOS::Render3D::TextureLayer(*(adapter->textureInfo_)) };

        const OHOS::Render3D::TextureInfo& obj = *(adapter->textureInfo_);
        LOGD("MODEL_NG: ModelAdapterWrapper::CreateTextureLayer() key_ = %d, texture_id = %d",
            adapter->GetKey(), obj.textureId_);
    });
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
        LOGD("MODEL_NG: SetupSceneViewer -> Unload model GetKey() %d", adapter->GetKey());
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
    return properties;
}

EGLContext ModelAdapterWrapper::GetRenderContext()
{
    auto ret = EGL_NO_CONTEXT;
    ret = Rosen::RSUIShareContext::GetInstance().GetRsRenderContext();
    LOGD("MODEL_NG: RenderContext %p", ret);
    return ret;
}

bool ModelAdapterWrapper::IsInitialized()
{
    return sceneViewerAdapter_ ? true : false;
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
    LOGD("MODEL_NG HandleCameraMove() eventId[%d], eventType[%u], position[%.2f, %.2f], delta[%.2f, %.2f], key = %d",
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
} // namespace OHOS::Ace::NG
