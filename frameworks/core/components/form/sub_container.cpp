/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/form/sub_container.h"

#include "adapter/aosp/entrance/java/jni/file_asset_provider.h"  // TODO: should not deps on adapter
#include "frameworks/core/common/flutter/flutter_asset_manager.h"
#include "frameworks/core/common/flutter/flutter_task_executor.h"
#include "frameworks/core/components/form/form_element.h"
#include "frameworks/core/components/form/render_form.h"
#include "frameworks/core/components/form/form_window.h"
#include "frameworks/core/components/transform/transform_element.h"

namespace OHOS::Ace {

namespace {

const int32_t THEME_ID_DEFAULT = 117440515;

} // namespace

void SubContainer::Initialize()
{
    if (!outSidePipelineContext_.Upgrade()) {
        LOGE("no pipeline context for create form component container.");
        return;
    }

    auto executor = outSidePipelineContext_.Upgrade()->GetTaskExecutor();
    if (!executor) {
        LOGE("could not got main pipeline executor");
        return;
    }
    auto taskExecutor = AceType::DynamicCast<FlutterTaskExecutor>(executor);
    if (!taskExecutor) {
        LOGE("main pipeline context executor is not flutter taskexecutor");
        return;
    }
    taskExecutor_ = Referenced::MakeRefPtr<FlutterTaskExecutor>(taskExecutor);

    frontend_ = AceType::MakeRefPtr<CardFrontend>();
    frontend_->Initialize(FrontendType::JS_CARD, taskExecutor_);
}

void SubContainer::Destroy()
{
    if (!pipelineContext_) {
        LOGE("no context find for inner card");
        return;
    }

    if (!taskExecutor_) {
        LOGE("no taskExecutor find for inner card");
        return;
    }

    assetManager_.Reset();
    pipelineContext_.Reset();
}

void SubContainer::UpdateRootElmentSize()
{
    auto formComponet = AceType::DynamicCast<FormComponent>(formComponent_);
    Dimension rootWidht = 0.0_vp;
    Dimension rootHeight = 0.0_vp;
    if (formComponet) {
        rootWidht = formComponet->GetWidth();
        rootHeight = formComponet->GetHeight();
    }

    if (rootWidht_ == rootWidht && rootHeight == rootHeight) {
        LOGE("size not changed, should not change");
        return;
    }

    surfaceWidth_ = outSidePipelineContext_.Upgrade()->NormalizeToPx(rootWidht);
    surfaceHeight_ = outSidePipelineContext_.Upgrade()->NormalizeToPx(rootHeight);
    if (pipelineContext_) {
        pipelineContext_->SetRootSize(density_, rootWidht.Value(), rootHeight.Value());
    }
}

void SubContainer::UpdateSurfaceSize()
{
    if (!taskExecutor_) {
        LOGE("update surface size fail could not post task to ui thread");
        return;
    }
    auto weakContext = AceType::WeakClaim(AceType::RawPtr(pipelineContext_));
    taskExecutor_->PostTask(
        [weakContext, surfaceWidth = surfaceWidth_, surfaceHeight = surfaceHeight_]() {
          auto context = weakContext.Upgrade();
          if (context == nullptr) {
              LOGE("context is nullptr");
              return;
          }
          if (NearZero(surfaceWidth) && NearZero(surfaceHeight)) {
              LOGE("surface is zero, should not update");
              return;
          }
          context->OnSurfaceChanged(surfaceWidth, surfaceHeight);
        },
        TaskExecutor::TaskType::UI);
}

void SubContainer::RunCard(const int64_t id, const std::string path, const std::string module, const std::string data)
{
    if (id == runningCardId_) {
        LOGE("the card is showing, no need run again");
        return;
    }
    runningCardId_ = id;
    if (onFormAcquiredCallback_) {
        onFormAcquiredCallback_(id);
    }

    frontend_->ResetPageLoadState();

    LOGD("run card path:%{private}s, module:%{private}s, data:%{private}s", path.c_str(), module.c_str(), data.c_str());
    RefPtr<FlutterAssetManager> flutterAssetManager;
    flutterAssetManager = Referenced::MakeRefPtr<FlutterAssetManager>();

    if (flutterAssetManager) {
        frontend_->SetAssetManager(flutterAssetManager);
        assetManager_ = flutterAssetManager;

        auto assetProvider = AceType::MakeRefPtr<FileAssetProvider>();
        std::string temp1 = "assets/js/" + module + "/";
        std::string temp2 = "assets/js/share/";
        std::vector<std::string> basePaths;
        basePaths.push_back(temp1);
        basePaths.push_back(temp2);

        if (assetProvider->Initialize(path, basePaths)) {
            LOGI("push card asset provider to queue.");
            flutterAssetManager->PushBack(std::move(assetProvider));
        }
    }

    auto&& window = std::make_unique<FormWindow>(outSidePipelineContext_);
    pipelineContext_ = AceType::MakeRefPtr<PipelineContext>(std::move(window), taskExecutor_, assetManager_, frontend_);

    density_ = outSidePipelineContext_.Upgrade()->GetDensity();
    UpdateRootElmentSize();
    pipelineContext_->SetIsJsCard(true);

    ResourceInfo cardResourceInfo;
    ResourceConfiguration resConfig;
    resConfig.SetDensity(density_);
    cardResourceInfo.SetThemeId(THEME_ID_DEFAULT);
    cardResourceInfo.SetPackagePath(path);
    cardResourceInfo.SetResourceConfiguration(resConfig);
    auto cardThemeManager = pipelineContext_->GetThemeManager();
    if (cardThemeManager) {
        // Init resource, load theme map, do not parse yet.
        cardThemeManager->InitResource(cardResourceInfo);
        cardThemeManager->LoadSystemTheme(cardResourceInfo.GetThemeId());
        auto weakTheme = AceType::WeakClaim(AceType::RawPtr(cardThemeManager));
        auto weakAsset = AceType::WeakClaim(AceType::RawPtr(flutterAssetManager));
        taskExecutor_->PostTask(
            [weakTheme, weakAsset]() {
                auto themeManager = weakTheme.Upgrade();
                if (themeManager == nullptr) {
                    LOGE("themeManager or aceView is null!");
                    return;
                }
                themeManager->ParseSystemTheme();
                themeManager->SetColorScheme(ColorScheme::SCHEME_LIGHT);
                themeManager->LoadCustomTheme(weakAsset.Upgrade());
            },
            TaskExecutor::TaskType::UI);
    }

    auto&& actionEventHandler = [weak = WeakClaim(this)](const std::string& action) {
        auto container = weak.Upgrade();
        if (!container) {
            LOGE("ActionEventHandler sub container is null!");
            return;
        }
        auto form = AceType::DynamicCast<FormElement>(container->GetFormElement().Upgrade());
        if (!form) {
            LOGE("ActionEventHandler form is null!");
            return;
        }

        form->OnActionEvent(action);
    };
    pipelineContext_->SetActionEventHandler(actionEventHandler);

    auto weakContext = AceType::WeakClaim(AceType::RawPtr(pipelineContext_));

    taskExecutor_->PostTask(
        [weakContext]() {
            auto context = weakContext.Upgrade();
            if (context == nullptr) {
                LOGE("context or root box is nullptr");
                return;
            }
            context->SetupRootElement();
        },
        TaskExecutor::TaskType::UI);

    frontend_->AttachPipelineContext(pipelineContext_);

    auto cardFronted = AceType::DynamicCast<CardFrontend>(frontend_);
    if (frontend_) {
        frontend_->SetDensity(density_);
        UpdateSurfaceSize();
    }

    auto form = AceType::DynamicCast<FormElement>(GetFormElement().Upgrade());
    if (!form) {
        LOGE("set draw delegate could not get form element");
        return;
    }
    auto renderNode = form->GetRenderNode();
    if (!renderNode) {
        LOGE("set draw delegate could not get render node");
        return;
    }
    auto formRender = AceType::DynamicCast<RenderForm>(renderNode);
    if (!formRender) {
        LOGE("set draw delegate could not get render form");
        return;
    }
    pipelineContext_->SetDrawDelegate(formRender->GetDrawDelegate());

    frontend_->RunPage(0, "", data);
}

void SubContainer::UpdateCard(const std::string content)
{
    if (!frontend_) {
        LOGE("update card fial due to could not find card front end");
        return;
    }
    if (allowUpdate_) {
        frontend_->UpdateData(std::move(content));
    }
}

} // namespace OHOS::Ace
