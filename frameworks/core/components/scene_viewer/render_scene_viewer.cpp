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

#include "core/components/scene_viewer/render_scene_viewer.h"

#include "base/log/ace_trace.h"
#include "core/event/ace_event_helper.h"
#include "graphics_manager.h"
#include "graphics_task.h"

namespace OHOS::Ace {

RenderSceneViewer::RenderSceneViewer(uint32_t key) : RenderNode(true), sceneViewerAdapter_(key), key_(key)
{
    Initialize();
}

RenderSceneViewer::~RenderSceneViewer()
{
    OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this)] {
        auto delegate = weak.Upgrade();
        if (delegate) {
            delegate->sceneViewerAdapter_.DeInitEngine();
            OHOS::Render3D::GraphicsManager::GetInstance().UnRegister(delegate->GetKey());
        }
    });

    auto context = context_.Upgrade();
    if (context) {
        context->UnregisterSurfaceChangedCallback(surfaceChangeCallbackId_);
    }
}

void RenderSceneViewer::Initialize()
{
    auto wp = AceType::WeakClaim(this);
    touchHandler_ = AceType::MakeRefPtr<SceneViewerTouchHandler>();
    touchHandler_->SetEventCallback([wp](const OHOS::Render3D::SceneViewerTouchEvent& event) {
      auto sv = wp.Upgrade();
      if (sv) {
          sv->HandleEvent(event);
      }
    });
}

void RenderSceneViewer::HandleEvent(const OHOS::Render3D::SceneViewerTouchEvent& event)
{
    ACE_SCOPED_TRACE("RenderSceneViewer::HandleEvent()");
    switch (event.GetEventType()) {
        case OHOS::Ace::TouchType::DOWN:
            isClicked_ = true;
            touchCount_++;
            break;
        case OHOS::Ace::TouchType::UP:
            touchCount_--;
            break;
        case OHOS::Ace::TouchType::MOVE:
            break;
        case OHOS::Ace::TouchType::CANCEL:
            touchCount_--;
            break;
        default:
            LOGW("Unknown touch type.");
            break;
    }

    if (!isHandleCameraMove_) {
        if (isClicked_ && touchCount_ == 0) {
            PerformClick();
        }
        isClicked_ = touchCount_ > 0;
        return;
    }

    // Convert to LUME stuff.
    auto context = GetContext().Upgrade();
    if (context) {
#if MULTI_ECS_UPDATE_AT_ONCE
        OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), event] {
#else
        OHOS::Render3D::GraphicsTask::GetInstance().PushAsyncMessage([weak = WeakClaim(this), event] {
#endif
            auto delegate = weak.Upgrade();
            if (delegate) {
                delegate->sceneViewerAdapter_.OnTouchEvent(event);
            }
        });
    } else {
        LOGE("ACE-3D RenderSceneViewer::HandleEvent() GetContext failed.");
    }
    SetNeedRender(false);
    MarkNeedRender();
}

void RenderSceneViewer::RenderWithContext(RenderContext& context, const Offset& offset) {

    ACE_SCOPED_TRACE("RenderSceneViewer::RenderWithContext()");

    auto pipelineContext = GetContext().Upgrade();
    if (!pipelineContext) {
        LOGE("ACE-3D RenderSceneViewer::RenderWithContext() GetContext failed.");
        return;
    }
    if (!pipelineContext->IsSurfaceReady()) {
        // Surface not ready yet, reschedule render.
        LOGE("ACE-3D RenderSceneViewer::RenderWithContext() Surface not ready yet.");
        MarkNeedRender();
        return;
    }
    if (!inited_) {
        inited_ = true;
        EGLContext eglContext = GetRenderContext();

        // texture create must in sync manner
        OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([&eglContext, weak = WeakClaim(this)] {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                LOGE("delegate is null");
                return;
            }

            auto& gfxManager = OHOS::Render3D::GraphicsManager::GetInstance();
            gfxManager.Register(delegate->GetKey());

            delegate->eglContext_ = gfxManager.CreateOffScreenContext(eglContext);
            delegate->textureInfo_ = delegate->CreateRenderTarget(delegate->sceneSize_.Width(),
                delegate->sceneSize_.Height());
        });

        PrepareTextureLayer(textureInfo_);

#if MULTI_ECS_UPDATE_AT_ONCE
        OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([&eglContext, weak = WeakClaim(this)] {
#else
        // OHOS::Render3D::GraphicsTask::GetInstance().PushAsyncMessage([&eglContext, this] {
        // init engine in async manner sometimes crash on screen rotation
        OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([&eglContext, weak = WeakClaim(this)] {
#endif
            auto delegate = weak.Upgrade();
            if (!delegate) {
                LOGE("delegate is null");
                return;
            }

            auto& gfxManager = OHOS::Render3D::GraphicsManager::GetInstance();
            auto &&engine = gfxManager.GetEngine(OHOS::Render3D::EngineFactory::EngineType::LUME, eglContext);
            delegate->sceneViewerAdapter_.SetEngine(std::move(engine));
        });
    }

    if (needsSceneSetup_) {
        // Make sure needs scene setup is on, or introduce another flag
        if (!customRenders_.empty()) {
            PassCustomRenders(customRenders_);
        }

        if (!shapes_.empty()) {
            PassGeometries(shapes_);
        }

#if MULTI_ECS_UPDATE_AT_ONCE
        OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this)] {
#else
        OHOS::Render3D::GraphicsTask::GetInstance().PushAsyncMessage([weak = WeakClaim(this)] {
#endif
            auto delegate = weak.Upgrade();
            if (!delegate) {
                LOGE("delegate is null");
                return;
            }

            delegate->sceneViewerAdapter_.SetUpCameraTransform(
                delegate->cameraPosition_, delegate->cameraLookAtVec_,
                delegate->cameraUpVec_, delegate->cameraRotation_);
            delegate->sceneViewerAdapter_.SetUpCameraViewProjection(
                delegate->zNear_, delegate->zFar_, delegate->fovDegrees_);

            auto bg_type = delegate->isTransparent_ ? OHOS::Render3D::SceneViewerBackgroundType::TRANSPARENT :
                OHOS::Render3D::SceneViewerBackgroundType::CUBE_MAP;

            // Pass the lights to backend if any.
            if (!delegate->lights_.empty()) {
                delegate->sceneViewerAdapter_.AddLights(delegate->lights_);
            }

            delegate->sceneViewerAdapter_.SetUpSceneViewer(delegate->textureInfo_, delegate->glTFSrc_,
                delegate->backgroundSrc_, bg_type);
        });
        needsSceneSetup_ = false;
        SetNeedRender(true);
    }

    OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this)] {
        auto delegate = weak.Upgrade();
        if (delegate) {
            delegate->animating_ = delegate->sceneViewerAdapter_.IsAnimating();
            delegate->handlesNotReady_ = delegate->sceneViewerAdapter_.HandlesNotReady();
        }
    });

    RenderNode::RenderWithContext(context, offset);

    if (animating_ || handlesNotReady_) {
        SetNeedRender(true);
    }
}

void RenderSceneViewer::Paint(RenderContext& context, const Offset& offset)
{
    ACE_FUNCTION_TRACE();

    auto pipeline_context = GetContext().Upgrade();
    if (pipeline_context) {
        // auto &&ftr = OHOS::Render3D::GraphicsTask::GetInstance().PushAsyncMessage([this] {
        // If open MULTI_ECS_UPDATE_AT_ONCE macro  SetGSVsyncCallback is called on current thread
        // that means all the 3D engine task should be in syncorinize manner.
#if MULTI_ECS_UPDATE_AT_ONCE
        OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this)] {
#else
        renderFinished_ = OHOS::Render3D::GraphicsTask::GetInstance().PushAsyncMessage([weak = WeakClaim(this)] {
#endif
            auto delegate = weak.Upgrade();
            if (delegate) {
                delegate->sceneViewerAdapter_.DrawFrame();
            }
        });
    } else {
        LOGE("ACE-3D RenderSceneViewer::Paint() GetContext failed.");
    }

    // Texture layer position is (0,0) w.r.t to RenderNode.
    PaintTextureLayer(context, Offset(0.0, 0.0));
    RenderNode::Paint(context, offset);

    if ((animating_ || handlesNotReady_) && pipeline_context) {
        SetNeedRender(true);
        pipeline_context->AddDirtyRenderNode(AceType::Claim(this), false);
    }
}

void RenderSceneViewer::Update(const RefPtr<Component>& component)
{
    ACE_SCOPED_TRACE("RenderSceneViewer::Update()");
    RefPtr<SceneViewerComponent> svComponent = AceType::DynamicCast<SceneViewerComponent>(component);
    if (!svComponent) {
        LOGE("ACE-3D RenderSceneViewer::Update() svComponent is null!");
        return;
    }

    bool src_updated = (!glTFSrc_.empty() && glTFSrc_ != svComponent->GetGltfSrc());
    bool background_updated = (backgroundSrc_ != svComponent->GetBackgroundSrc());

    if (src_updated || background_updated) {
        auto pipeline_context = GetContext().Upgrade();
        if (pipeline_context) {
#if MULTI_ECS_UPDATE_AT_ONCE
            OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this)] {
#else
            OHOS::Render3D::GraphicsTask::GetInstance().PushAsyncMessage([weak = WeakClaim(this)] {
#endif
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->sceneViewerAdapter_.UnLoadModel();
                }
            });
        } else {
            LOGE("ACE-3D RenderSceneViewer::Update() GetContext failed.");
        }
    }

    // Update camera properties if changed.
    if (IsCameraPropertyChanged(svComponent)) {
        // Position is Animatable currently.
        cameraPosition_.SetVec(svComponent->GetCameraPositionVec());
        cameraPosition_.SetDistance(svComponent->GetCameraPosDistance());
        cameraPosition_.SetIsAngular(svComponent->GetIsCameraPosInAngles());
        cameraLookAtVec_ = svComponent->GetCameraLookAtVec();
        cameraUpVec_ = svComponent->GetCameraUpVec();
        cameraRotation_ = svComponent->GetCameraRotation();
        zNear_ = svComponent->GetZNear();
        zFar_ = svComponent->GetZFar();
        fovDegrees_ = svComponent->GetFovDegrees();
        PerformCameraUpdate();
    }
    needsSceneSetup_ |= (src_updated || background_updated);

    if (!svComponent->GetLights().empty()) {
        HandleLightsUpdate(svComponent);
    }

    if (!svComponent->GetGLTFAnimations().empty()) {
        UpdateGLTFAnimations(svComponent->GetGLTFAnimations());
    }

    glTFSrc_ = svComponent->GetGltfSrc();
    backgroundSrc_ = svComponent->GetBackgroundSrc();
    MarkNeedLayout();

    onClick_ = AceAsyncEvent<void()>::Create(svComponent->GetClickedEventId(), context_);
    isHandleCameraMove_ = svComponent->IsHandleCameraMove();
    isTransparent_= svComponent->IsTransparent();

    if (!svComponent->GetGeometries().empty()) {
        shapes_ = svComponent->GetGeometries();
        needsSceneSetup_ = true;
    }

    if (!svComponent->GetCustomRenders().empty()) {
        customRenders_ = svComponent->GetCustomRenders();
        needsSceneSetup_ = true;
    }
}

void RenderSceneViewer::PerformLayout()
{
    ACE_SCOPED_TRACE("RenderSceneViewer::PerformLayout()");
    double w = GetLayoutParam().GetMaxSize().Width();
    double h = GetLayoutParam().GetMaxSize().Height();
    sceneSize_ = Size(w, h);
    SetLayoutSize(Size(w, h));
}

void RenderSceneViewer::OnPaintFinish() {}

void RenderSceneViewer::OnSurfaceChanged()
{
    ACE_SCOPED_TRACE("RenderSceneViewer::OnSurfaceChanged key: %d", GetKey());
    if (inited_) {
        OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this)] {
            auto delegate = weak.Upgrade();
            if (delegate) {
                delegate->sceneViewerAdapter_.DeInitEngine();
                OHOS::Render3D::GraphicsManager::GetInstance().UnRegister(delegate->GetKey());
            }
        });
        inited_ = false;
        SetNeedRender(false);
        MarkNeedRender();
        needsSceneSetup_ = true;
    }
}

void RenderSceneViewer::ClearRenderObject() {
    RenderNode::ClearRenderObject();
}

uint32_t RenderSceneViewer::GetKey() {
    return key_;
}

Size RenderSceneViewer::GetSize() {
    return sceneSize_;
}

void RenderSceneViewer::OnTouchTestHit(
    const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result) {
    ACE_SCOPED_TRACE("RenderSceneViewer::OnTouchTestHit()");
    touchHandler_->SetCoordinateOffset(coordinateOffset);
    result.emplace_back(touchHandler_);
}

void RenderSceneViewer::PerformClick()
{
    if (onClick_) {
        onClick_();
    }
}

void RenderSceneViewer::PerformCameraUpdate()
{
    UpdateCameraOnly();
}

void RenderSceneViewer::UpdateCameraOnly()
{
    ACE_SCOPED_TRACE("RenderSceneViewer::UpdateCameraOnly()");
    auto pipeline_context = GetContext().Upgrade();
    if (pipeline_context) {
#if MULTI_ECS_UPDATE_AT_ONCE
        OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this)] {
#else
        OHOS::Render3D::GraphicsTask::GetInstance().PushAsyncMessage([weak = WeakClaim(this)] {
#endif
            auto delegate = weak.Upgrade();
            if (delegate) {
                delegate->sceneViewerAdapter_.SetUpCameraTransform(delegate->cameraPosition_,
                    delegate->cameraLookAtVec_, delegate->cameraUpVec_, delegate->cameraRotation_);
                delegate->sceneViewerAdapter_.SetUpCameraViewProjection(
                    delegate->zNear_, delegate->zFar_, delegate->fovDegrees_);
            }
        });
        MarkNeedLayout();
    } else {
        LOGE("ACE-3D RenderSceneViewer::UpdateCameraOnly() GetContext failed.");
    }
}

void RenderSceneViewer::PerformLightUpdate()
{
    UpdateLightOnly();
}

void RenderSceneViewer::UpdateLightOnly()
{
    ACE_SCOPED_TRACE("RenderSceneViewer::UpdateLightOnly()");
    auto pipeline_context = GetContext().Upgrade();
    if (pipeline_context) {
#if MULTI_ECS_UPDATE_AT_ONCE
        OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this)] {
#else
        OHOS::Render3D::GraphicsTask::GetInstance().PushAsyncMessage([weak = WeakClaim(this)] {
#endif
            auto delegate = weak.Upgrade();
            if (delegate) {
                delegate->sceneViewerAdapter_.AddLights(delegate->lights_);
                delegate->sceneViewerAdapter_.CreateLight();
            }
        });
        MarkNeedLayout();
    } else {
        LOGE("ACE-3D RenderSceneViewer::UpdateLightOnly() GetContext failed.");
    }
}

// Save the geometry if engine not start up
void RenderSceneViewer::PassGeometries(const std::vector<RefPtr<OHOS::Render3D::SVGeometry>>& geometries)
{
    auto pipeline_context = GetContext().Upgrade();
    if (pipeline_context) {
#if MULTI_ECS_UPDATE_AT_ONCE
        OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &geometries] {
#else
        OHOS::Render3D::GraphicsTask::GetInstance().PushAsyncMessage([weak = WeakClaim(this), &geometries] {
#endif
            auto delegate = weak.Upgrade();
            if (delegate) {
                delegate->sceneViewerAdapter_.UpdateGeometries(geometries);
            }
        });
    } else {
        LOGE("ACE-3D RenderSceneViewer::PassGeometries() GetContext failed.");
    }
}

// Save the gltf animation if engine not start up
void RenderSceneViewer::UpdateGLTFAnimations(const std::vector<RefPtr<OHOS::Render3D::GLTFAnimation>>& gltfAnimations)
{
    ACE_SCOPED_TRACE("RenderSceneViewer::UpdateGLTFAnimations()");
    auto pipeline_context = GetContext().Upgrade();
    if (!pipeline_context) {
        LOGE("RenderSceneViewer::UpdateGLTFAnimations() GetContext failed.");
        return;
    }

#if MULTI_ECS_UPDATE_AT_ONCE
    OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), gltfAnimations] {
#else
    OHOS::Render3D::GraphicsTask::GetInstance().PushAsyncMessage([weak = WeakClaim(this), gltfAnimations] {
#endif
        auto delegate = weak.Upgrade();
        if (delegate) {
            delegate->sceneViewerAdapter_.UpdateGLTFAnimations(gltfAnimations);
            delegate->animating_ = delegate->sceneViewerAdapter_.IsAnimating();
        }
    });
}

bool RenderSceneViewer::IsCameraPropertyChanged(const RefPtr<SceneViewerComponent>& svComponent)
{
    if (!svComponent) {
        LOGE("ACE-3D RenderSceneViewer::IsCameraPropertyChanged() svComponent is null!");
        return false;
    }

    if (cameraPosition_.GetVec() != svComponent->GetCameraPositionVec()
        || cameraPosition_.GetDistance() != svComponent->GetCameraPosDistance()
        || !NearEqual(zNear_, svComponent->GetZNear())
        || !NearEqual(zFar_, svComponent->GetZFar())
        || !NearEqual(fovDegrees_, svComponent->GetFovDegrees())
        || cameraLookAtVec_ != svComponent->GetCameraLookAtVec()
        || cameraUpVec_ != svComponent->GetCameraUpVec()
        || cameraRotation_ != svComponent->GetCameraRotation()) {
        return true;
    }
    return false;
}

void RenderSceneViewer::HandleLightsUpdate(const RefPtr<SceneViewerComponent>& svComponent)
{
    if (!svComponent) {
        LOGE("ACE-3D RenderSceneViewer::HandleLightsUpdate() svComponent is null!");
        return;
    }

    // First time update. Attach the animation callbacks.
    if (lights_.empty()) {
        lights_ = svComponent->GetLights();
        for (auto& light : lights_) {
            light->SetContextAndCallback(
                context_,
                std::bind(&RenderSceneViewer::PerformLightUpdate, this));
        }
        PerformLightUpdate();
        return;
    }

    if (!IsLightPropertyChanged(svComponent)) {
        return;
    }

    std::vector<OHOS::Ace::RefPtr<OHOS::Render3D::SVLight>> newLights = svComponent->GetLights();

    int index = 0;
    for (auto& light : lights_) {
        light->SetLightType(newLights.at(index)->GetLightType());
        light->SetIntensity(newLights.at(index)->GetLightIntensity());
        light->SetColor(newLights.at(index)->GetLightColor());
        light->SetLightShadow(newLights.at(index)->GetLightShadow());
        light->SetPosition(newLights.at(index)->GetPosition());
        light->SetRotation(newLights.at(index)->GetRotation());
        index++;
    }
    PerformLightUpdate();
}

bool RenderSceneViewer::IsLightPropertyChanged(const RefPtr<SceneViewerComponent>& svComponent)
{
    if (!svComponent) {
        LOGE("ACE-3D RenderSceneViewer::IsLightPropertyChanged() svComponent is null!");
        return false;
    }

    std::vector<OHOS::Ace::RefPtr<OHOS::Render3D::SVLight>> newLights = svComponent->GetLights();
    int index = 0;
    for (auto& light : lights_) {
        if (light->GetLightType() != newLights.at(index)->GetLightType()
            || light->GetLightIntensity() != newLights.at(index)->GetLightIntensity()
            || light->GetLightColor() != newLights.at(index)->GetLightColor()
            || light->GetLightShadow() != newLights.at(index)->GetLightShadow()
            || light->GetPosition().GetVec() != newLights.at(index)->GetPosition().GetVec()
            || light->GetPosition().GetDistance() != newLights.at(index)->GetPosition().GetDistance()
            || light->GetRotation() != newLights.at(index)->GetRotation()) {
            return true;
        }
        index++;
    }
    return false;
}

// Save the custom renders if engine not start up
void RenderSceneViewer::PassCustomRenders(
    const std::vector<RefPtr<OHOS::Render3D::SVCustomRenderDescriptor>>& customRenders)
{
    auto pipeline_context = GetContext().Upgrade();
    if (pipeline_context) {
#if MULTI_ECS_UPDATE_AT_ONCE
        OHOS::Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &customRenders] {
#else
        OHOS::Render3D::GraphicsTask::GetInstance().PushAsyncMessage([weak = WeakClaim(this), &customRenders] {
#endif
            auto delegate = weak.Upgrade();
            if (delegate) {
                delegate->sceneViewerAdapter_.AddCustomRenders(customRenders);
            }
        });
    } else {
        LOGE("ACE-3D RenderSceneViewer::PassCustomRenders() GetContext failed.");
    }
}

} // namespace OHOS::Ace
