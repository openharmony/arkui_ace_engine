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
#include "frameworks/core/common/container.h"

namespace OHOS::Ace::NG {

Render3D::HapInfo ModelAdapterWrapper::SetHapInfo()
{
    auto container = Container::Current();
    if (container == nullptr) {
        LOGE("modle 3d fail to get container");
        return {};
    }
    std::string hapPath = container->GetHapPath();
    Render3D::HapInfo hapInfo { hapPath, bundleName_, moduleName_ };
    return hapInfo;
}

ModelAdapterWrapper::ModelAdapterWrapper(uint32_t key, const ModelViewContext& context) : key_(key),
    surfaceType_(context.surfaceType_), bundleName_(context.bundleName_),
#if defined(KIT_3D_ENABLE)
    moduleName_(context.moduleName_), sceneAdapter_(context.sceneAdapter_)
#else
    moduleName_(context.moduleName_)
#endif
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

std::shared_future<void> ModelAdapterWrapper::Deinit()
{
    ACE_SCOPED_TRACE("ModelAdapterWrapper::Deinit");
#if defined(KIT_3D_ENABLE)
    if (sceneAdapter_) {
        sceneAdapter_->Deinit();
        return std::shared_future<void>();
    }
#endif
    std::shared_ptr<Render3D::WidgetAdapter> widgetAdapter(widgetAdapter_);
    std::shared_ptr<Render3D::TextureLayer> textureLayer(textureLayer_);
    auto key = key_;
    return Render3D::GraphicsTask::GetInstance().PushAsyncMessage([widgetAdapter, textureLayer, key] {
        ACE_SCOPED_TRACE("ModelAdapterWrapper::Deinit render");
        
        CHECK_NULL_VOID(widgetAdapter);
        widgetAdapter->DeInitEngine();
        Render3D::GraphicsManager::GetInstance().UnRegister(key);
        CHECK_NULL_VOID(textureLayer);
        textureLayer->DestroyRenderTarget();
    });
}

void ModelAdapterWrapper::CreateTextureLayer()
{
#if defined(KIT_3D_ENABLE)
    if (sceneAdapter_) {
        return;
    }
#endif
    Render3D::GraphicsTask::GetInstance().PushAsyncMessage([weak = WeakClaim(this)] {
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);

        auto& gfxManager = Render3D::GraphicsManager::GetInstance();
        const auto& key = adapter->GetKey();
        gfxManager.Register(key);
        adapter->textureLayer_ = std::make_shared<Render3D::TextureLayer>(key);
    });
}

void ModelAdapterWrapper::CreateWidgetAdapter()
{
#if defined(KIT_3D_ENABLE)
    if (sceneAdapter_) {
        return;
    }
#endif
    auto key = GetKey();
    Render3D::HapInfo hapInfo = SetHapInfo();
    // init engine in async manager sometimes crash on screen rotation
    Render3D::GraphicsTask::GetInstance().PushAsyncMessage([weak = WeakClaim(this), key, hapInfo] {
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);

        adapter->widgetAdapter_ = std::make_shared<Render3D::WidgetAdapter>(key);
        auto& gfxManager = Render3D::GraphicsManager::GetInstance();
        auto&& engine = gfxManager.GetEngine(Render3D::EngineFactory::EngineType::LUME, adapter->GetKey(),
            hapInfo);
        adapter->widgetAdapter_->Initialize(std::move(engine));
    });
}

void ModelAdapterWrapper::OnAttachToFrameNode(const RefPtr<RenderContext>& context)
{
#if defined(KIT_3D_ENABLE)
    // scene adapter toutine
    if (sceneAdapter_) {
        sceneAdapter_->LoadPluginsAndInit();
        textureLayer_ = sceneAdapter_->CreateTextureLayer();
        return;
    }
#endif

#ifdef ENABLE_ROSEN_BACKEND
    auto rsContext = DynamicCast<NG::RosenRenderContext>(context);
    CHECK_NULL_VOID(rsContext);
    auto rsNode = rsContext->GetRSNode();
    CHECK_NULL_VOID(rsNode);
    rsNode->SetFrameGravity(Rosen::Gravity::RESIZE);
#endif
    CreateTextureLayer();
    CreateWidgetAdapter();
}

void ModelAdapterWrapper::OnDirtyLayoutWrapperSwap(const Render3D::WindowChangeInfo& windowChangeInfo)
{
    needsSyncPaint_ = true;
#if defined(KIT_3D_ENABLE)
    if (sceneAdapter_) {
        sceneAdapter_->OnWindowChange(windowChangeInfo);
        return;
    }
#endif
    Render3D::GraphicsTask::GetInstance().PushAsyncMessage([weak = WeakClaim(this), windowChangeInfo] {
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);
        CHECK_NULL_VOID(adapter->textureLayer_);
        CHECK_NULL_VOID(adapter->widgetAdapter_);

        adapter->textureLayer_->OnWindowChange(windowChangeInfo);
        adapter->widgetAdapter_->OnWindowChange(adapter->textureLayer_->GetTextureInfo());
    });
}

void ModelAdapterWrapper::OnRebuildFrame(RefPtr<RenderContext>& context)
{
#ifdef ENABLE_ROSEN_BACKEND
    auto rsContext = DynamicCast<NG::RosenRenderContext>(context);
    CHECK_NULL_VOID(rsContext);
    auto rsNode = rsContext->GetRSNode();
#if defined(KIT_3D_ENABLE)
    if (sceneAdapter_) {
        CHECK_NULL_VOID(textureLayer_);
        textureLayer_->SetParent(rsNode);
        return;
    }
#endif
    Render3D::GraphicsTask::GetInstance().PushAsyncMessage([weak = WeakClaim(this), rsNode]() mutable {
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);
        CHECK_NULL_VOID(adapter->textureLayer_);

        adapter->textureLayer_->SetParent(rsNode);
    });
#endif
}

void ModelAdapterWrapper::OnPaint3D(const RefPtr<ModelPaintProperty>& modelPaintProperty)
{
    CHECK_NULL_VOID(modelPaintProperty);

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

void ModelAdapterWrapper::DrawFrame()
{
    ACE_FUNCTION_TRACE();
#if defined(KIT_3D_ENABLE)
    if (sceneAdapter_) {
        sceneAdapter_->RenderFrame(needsSyncPaint_);
        needsRepaint_ = sceneAdapter_->NeedsRepaint();
        needsSyncPaint_ = false;
        return;
    }
#endif
    Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this)] {
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);
        CHECK_NULL_VOID(adapter->widgetAdapter_);

        adapter->needsRepaint_ = adapter->widgetAdapter_->NeedsRepaint();
    });

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
#if defined(KIT_3D_ENABLE)
    if (sceneAdapter_) {
        return;
    }
#endif
    Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this)] {
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);
        CHECK_NULL_VOID(adapter->widgetAdapter_);

        adapter->widgetAdapter_->UnloadSceneModel();
        adapter->widgetAdapter_->UnloadEnvModel();
    });
}

bool ModelAdapterWrapper::NeedsRepaint()
{
    return needsRepaint_;
}

ModelAdapterWrapper::~ModelAdapterWrapper()
{
    // Destroy resource explicitly before destruct
}

uint32_t ModelAdapterWrapper::GetKey()
{
    return key_;
}

void ModelAdapterWrapper::SetPaintFinishCallback(PaintFinishCallback callback)
{
    callback_ = std::move(callback);
}

bool ModelAdapterWrapper::HandleTouchEvent(const TouchEventInfo& info,
    const RefPtr<ModelPaintProperty>& modelPaintProperty)
{
    CHECK_NULL_RETURN(touchHandler_, false);
    CHECK_NULL_RETURN(textureLayer_, false);
    const auto& textureInfo = textureLayer_->GetTextureInfo();
    auto width = textureInfo.width_;
    auto height = textureInfo.height_;
    auto cameraState = modelPaintProperty->GetModelCameraMove().value_or(true);
    touchHandler_->HandleCameraEvents(cameraState);
    return touchHandler_->HandleTouchEvent(info, width, height);
}

void ModelAdapterWrapper::UpdateScene(const RefPtr<ModelPaintProperty>& modelPaintProperty)
{
#if defined(KIT_3D_ENABLE)
    if (sceneAdapter_) {
        return;
    }
#endif
    if (modelPaintProperty->GetModelSourceValue().empty()) {
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
#if defined(KIT_3D_ENABLE)
    if (sceneAdapter_) {
        return;
    }
#endif
    if (modelPaintProperty->GetModelBackgroundValue().empty()) {
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
#if defined(KIT_3D_ENABLE)
    if (sceneAdapter_) {
        return;
    }
#endif
    Render3D::GraphicsTask::GetInstance().PushSyncMessage([weak = WeakClaim(this), &event] {
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);
        CHECK_NULL_VOID(adapter->widgetAdapter_);

        adapter->widgetAdapter_->OnTouchEvent(event);
    });
}

void ModelAdapterWrapper::UpdateCustomRender(const RefPtr<ModelPaintProperty>& modelPaintProperty)
{
#if defined(KIT_3D_ENABLE)
    if (sceneAdapter_) {
        return;
    }
#endif
    auto& customRender = modelPaintProperty->GetModelCustomRender().value();
    if (!customRender) {
        LOGW("UpdateCustomRender invalid custom render");
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
#if defined(KIT_3D_ENABLE)
    if (sceneAdapter_) {
        return;
    }
#endif
    if (modelPaintProperty->GetShaderPathValue().empty()) {
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
#if defined(KIT_3D_ENABLE)
    if (sceneAdapter_) {
        return;
    }
#endif
    if (modelPaintProperty->GetModelImageTexturePathsValue().empty()) {
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
#if defined(KIT_3D_ENABLE)
    if (sceneAdapter_) {
        return;
    }
#endif
    if (modelPaintProperty->GetModelShaderInputBufferValue() == nullptr) {
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
