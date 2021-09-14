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

#include "adapter/common/cpp/file_asset_provider.h"
#include "adapter/common/cpp/flutter_asset_manager.h"
#include "adapter/common/cpp/flutter_task_executor.h"
#include "frameworks/core/components/box/box_element.h"
#include "frameworks/core/components/form/form_element.h"
#include "frameworks/core/components/stage/stage_element.h"
#include "frameworks/core/components/transform/render_transform.h"
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

    auto flutterTaskExecutor = Referenced::MakeRefPtr<FlutterTaskExecutor>();
    flutterTaskExecutor->InitJsThread();
    subTaskExecutor_ = flutterTaskExecutor;
    taskExecutor_ = outSidePipelineContext_.Upgrade()->GetTaskExecutor();

    frontend_ = AceType::MakeRefPtr<CardFrontend>();
    frontend_->SetNoDependentContainer();

    frontend_->Initialize(FrontendType::JS_CARD, outSidePipelineContext_.Upgrade()->GetTaskExecutor());
    frontend_->SetSelfTaskExectuor(subTaskExecutor_);
}

void SubContainer::Destroy()
{
    if (stageElement_) {
        LOGI("reset stage");
        stageElement_.Reset();
    }

    if (!pipelineContext_) {
        LOGE("no context find for inner card");
        return;
    }

    if (!subTaskExecutor_) {
        LOGE("no taskExecutor find for inner card");
        return;
    }

    // How to destroy frontend.
    pipelineContext_->SetMainPipelineContext(nullptr);

    auto mainPipeline = outSidePipelineContext_.Upgrade();
    if (mainPipeline) {
        mainPipeline->RemoveCardPipelineContext(pipelineContext_);
    }

    assetManager_.Reset();
    pipelineContext_.Reset();
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

    pipelineContext_ = AceType::MakeRefPtr<PipelineContext>(taskExecutor_, assetManager_, frontend_);

    double density = outSidePipelineContext_.Upgrade()->GetDensity();

    auto formComponet = AceType::DynamicCast<FormComponent>(formComponent_);
    Dimension rootWidht = 0.0_vp;
    Dimension rootHeight = 0.0_vp;
    if (formComponet) {
        rootWidht = formComponet->GetWidth();
        rootHeight = formComponet->GetHeight();
    }
    pipelineContext_->SetRootSize(density, rootWidht.Value(), rootHeight.Value());
    pipelineContext_->SetIsJsCard(true);

    ResourceInfo cardResourceInfo;
    ResourceConfiguration resConfig;
    resConfig.SetDensity(density);
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
    auto weakStageElement = AceType::WeakClaim(AceType::RawPtr(stageElement_));

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
        frontend_->SetDensity(density);
        taskExecutor_->PostTask(
            [weakContext, rootWidht, rootHeight]() {
                auto context = weakContext.Upgrade();
                if (context == nullptr) {
                    LOGE("context is nullptr");
                    return;
                }
                context->OnSurfaceChanged(rootWidht.Value(), rootHeight.Value());
            },
            TaskExecutor::TaskType::UI);
    }

    outSidePipelineContext_.Upgrade()->SetCardPipelineContext(pipelineContext_);
    pipelineContext_->SetMainPipelineContext(outSidePipelineContext_.Upgrade());

    auto rootStage = AceType::DynamicCast<StageElement>(stageElement_);
    if (rootStage) {
        rootStage->SetCardContext(AceType::WeakClaim(AceType::RawPtr(pipelineContext_)));
    }

    frontend_->AddOnGotWindowConfigCallback(
        [weak = WeakClaim(this), rootWidht, rootHeight, weakStageElement, density](WindowConfig windowConfig) {
            if (windowConfig.designWidth <= 0) {
                LOGE("the frontend design width <= 0");
                return;
            }

            if (NearZero(density)) {
                LOGE("scale value is near zero");
                return;
            }

            auto subContainer = weak.Upgrade();
            if (!subContainer) {
                LOGE("sub container is null");
                return;
            }

            auto stage = weakStageElement.Upgrade();
            if (!stage) {
                LOGE("could not get stage element when set card size & scale");
                return;
            }
            auto rootBox = AceType::DynamicCast<BoxElement>(stage->GetElementParent().Upgrade());
            if (!rootBox) {
                LOGE("could not get root box element when set card size & scale");
                return;
            }
            auto renderBox = AceType::DynamicCast<RenderBox>(rootBox->GetRenderNode());
            if (!renderBox) {
                LOGE("could not get root render box element when set card size & scale");
                return;
            }

            auto transForm = AceType::DynamicCast<TransformElement>(rootBox->GetElementParent().Upgrade());
            if (!transForm) {
                LOGE("could not get transform element");
                return;
            }
            auto renderTransForm = AceType::DynamicCast<RenderTransform>(transForm->GetRenderNode());
            if (!renderTransForm) {
                LOGE("could not get transform render node when set card size & scale");
                return;
            }

            if (windowConfig.autoDesignWidth) {
                renderBox->SetWidth(Dimension(rootWidht.Value() / density, rootWidht.Unit()));
                renderBox->SetHeight(Dimension(rootHeight.Value() / density, rootHeight.Unit()));
                renderTransForm->Scale(density, density);
                renderTransForm->MarkNeedRender();

                subContainer->SetRootElementScale(density);

                return;
            }

            double scale = static_cast<float>(rootWidht.Value()) / windowConfig.designWidth;

            if (NearZero(scale)) {
                LOGE("cal scale value is near zero");
                return;
            }

            renderBox->SetWidth(Dimension(rootWidht.Value() / scale, rootWidht.Unit()));
            renderBox->SetHeight(Dimension(rootHeight.Value() / scale, rootHeight.Unit()));
            renderTransForm->Scale(scale, scale);
            renderTransForm->MarkNeedRender();

            subContainer->SetRootElementScale(scale);
        });

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
