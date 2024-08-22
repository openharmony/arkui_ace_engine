/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "ashmem.h"

#include "adapter/ohos/entrance/utils.h"
#include "base/utils/utils.h"
#include "core/common/container_scope.h"
#include "core/components/theme/theme_manager_impl.h"
#include "core/components_ng/pattern/form/form_layout_property.h"
#include "frameworks/core/common/asset_manager_impl.h"
#include "frameworks/core/common/task_executor_impl.h"
#include "frameworks/core/components/form/form_element.h"
#include "frameworks/core/components/form/form_window.h"
#include "frameworks/core/components/form/render_form.h"

namespace OHOS::Ace {
namespace {

const int32_t THEME_ID_DEFAULT = 117440515;

} // namespace

SubContainer::~SubContainer()
{
    Destroy();
}

void SubContainer::Initialize()
{
    auto formPattern = formPattern_.Upgrade();
    if (formPattern && !formPattern->IsJsCard()) {
        LOGI("ETS card do not require the creation of a separate TaskExecutor");
        return;
    }

    if (!outSidePipelineContext_.Upgrade()) {
        LOGE("no pipeline context for create form component container.");
        return;
    }

    auto executor = outSidePipelineContext_.Upgrade()->GetTaskExecutor();
    if (!executor) {
        LOGE("could not got main pipeline executor");
        return;
    }

    auto taskExecutor = AceType::DynamicCast<TaskExecutorImpl>(executor);
    if (!taskExecutor) {
        LOGE("main pipeline context executor is not flutter taskexecutor");
        return;
    }
    taskExecutor_ = Referenced::MakeRefPtr<TaskExecutorImpl>(taskExecutor);
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

    auto outPipelineContext = outSidePipelineContext_.Upgrade();
    if (outPipelineContext) {
        outPipelineContext->RemoveTouchPipeline(WeakPtr<PipelineBase>(pipelineContext_));
    }

    assetManager_.Reset();
    pipelineContext_.Reset();
}

void SubContainer::UpdateRootElementSize()
{
    Dimension rootWidth = 0.0_vp;
    Dimension rootHeight = 0.0_vp;
    if (Container::IsCurrentUseNewPipeline()) {
        auto form = formPattern_.Upgrade();
        CHECK_NULL_VOID(form);
        auto layoutProperty = form->GetLayoutProperty<NG::FormLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        auto formInfo = layoutProperty->GetRequestFormInfo();
        if (formInfo.has_value()) {
            rootWidth = formInfo->width;
            rootHeight = formInfo->height;
        }
    } else {
        auto formComponent = AceType::DynamicCast<FormComponent>(formComponent_);
        if (formComponent) {
            rootWidth = formComponent->GetWidth();
            rootHeight = formComponent->GetHeight();
        }
    }

    if (rootWidht_ == rootWidth && rootHeight_ == rootHeight) {
        LOGE("size not changed, should not change");
        return;
    }

    surfaceWidth_ = outSidePipelineContext_.Upgrade()->NormalizeToPx(rootWidth);
    surfaceHeight_ = outSidePipelineContext_.Upgrade()->NormalizeToPx(rootHeight);
    if (pipelineContext_) {
        pipelineContext_->SetRootSize(density_, rootWidth.Value(), rootHeight.Value());
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
        TaskExecutor::TaskType::UI, "ArkUIFormUpdateSurfaceSize");
}

void SubContainer::UpdateSurfaceSizeWithAnimathion()
{
    CHECK_NULL_VOID(pipelineContext_);
    pipelineContext_->OnSurfaceChanged(surfaceWidth_, surfaceHeight_);
    pipelineContext_->FlushPipelineImmediately();
}

void SubContainer::RunCard(int64_t formId, const std::string& path, const std::string& module, const std::string& data,
    const std::map<std::string, sptr<AppExecFwk::FormAshmem>>& imageDataMap, const std::string& formSrc,
    const FrontendType& cardType, const FrontendType& uiSyntax)
{
    LOGI("SubContainer::RunCard RunCard!!! path = %{public}s formSrc = %{public}s", path.c_str(), formSrc.c_str());
    if (formId == runningCardId_) {
        LOGE("the card is showing, no need run again");
        return;
    }

    runningCardId_ = formId;
    if (onFormAcquiredCallback_) {
        onFormAcquiredCallback_(formId);
    }
    if (uiSyntax == FrontendType::ETS_CARD) {
        // ArkTSCard: 确认Acquired事件时序
        LOGI("Run Card in FRS");
        uiSyntax_ = FrontendType::ETS_CARD;
        return;
    }

    cardType_ = cardType;
    if (cardType_ == FrontendType::ETS_CARD) {
        frontend_ = AceType::MakeRefPtr<CardFrontendDeclarative>();
        onFormVisibleCallback_();
    } else if (cardType_ == FrontendType::JS_CARD) {
        frontend_ = AceType::MakeRefPtr<CardFrontend>();
        frontend_->AddFormVisiableCallback(onFormVisibleCallback_);
    } else {
        LOGE("Run Card failed, card type unknown");
        return;
    }
    frontend_->Initialize(cardType_, taskExecutor_);
    frontend_->ResetPageLoadState();
    LOGI("run card path:%{private}s, module:%{private}s, data:%{private}s", path.c_str(), module.c_str(), data.c_str());
    RefPtr<AssetManagerImpl> assetManagerImpl = Referenced::MakeRefPtr<AssetManagerImpl>();
    std::vector<std::string> basePaths;
    basePaths.push_back("assets/js/" + module + "/");
    basePaths.emplace_back("assets/js/share/");
    basePaths.emplace_back("");
    basePaths.emplace_back("js/");
    basePaths.emplace_back("ets/");
    if (assetManagerImpl) {
        frontend_->SetAssetManager(assetManagerImpl);
        assetManager_ = assetManagerImpl;
        auto assetProvider = CreateAssetProviderImpl(path, basePaths);
        if (assetProvider) {
            LOGI("push card asset provider to queue.");
            assetManagerImpl->PushBack(std::move(assetProvider));
        }
    }
    if (formSrc.compare(0, 2, "./") == 0) {       // 2:length of "./"
        frontend_->SetFormSrc(formSrc.substr(2)); // 2:length of "./"
    } else {
        frontend_->SetFormSrc(formSrc);
    }
    LOGI("RunCard formSrc = %{public}s", formSrc.c_str());
    frontend_->SetCardWindowConfig(GetWindowConfig());
    auto&& window = std::make_unique<FormWindow>(outSidePipelineContext_);
    window->SetFormWindowId(nodeId_);
    window->SetId(instanceId_);
    windowId_ = nodeId_;
    if (cardType_ == FrontendType::ETS_CARD) { // ETS Card : API9 only support New Pipeline
        pipelineContext_ = AceType::MakeRefPtr<NG::PipelineContext>(
            std::move(window), taskExecutor_, assetManager_, nullptr, frontend_, instanceId_);
    } else { // JS Card : API9 only support Old Pipeline
        pipelineContext_ = AceType::MakeRefPtr<PipelineContext>(
            std::move(window), taskExecutor_, assetManager_, nullptr, frontend_, instanceId_);
    }
    ContainerScope scope(instanceId_);
    density_ = outSidePipelineContext_.Upgrade()->GetDensity();
    auto eventManager = outSidePipelineContext_.Upgrade()->GetEventManager();
    pipelineContext_->SetEventManager(eventManager);
    ProcessSharedImage(imageDataMap);
    UpdateRootElementSize();
    pipelineContext_->SetIsJsCard(true); // JSCard & eTSCard both use this flag
    if (cardType_ == FrontendType::ETS_CARD) {
        pipelineContext_->SetIsFormRender(true); // only eTSCard use this flag
    }

    ResourceInfo cardResourceInfo;
    ResourceConfiguration resConfig;
    resConfig.SetDensity(density_);
    cardResourceInfo.SetThemeId(THEME_ID_DEFAULT);
    cardResourceInfo.SetPackagePath(path);
    cardResourceInfo.SetResourceConfiguration(resConfig);
    auto cardThemeManager = pipelineContext_->GetThemeManager();
    if (!cardThemeManager) {
        cardThemeManager = AceType::MakeRefPtr<ThemeManagerImpl>();
        pipelineContext_->SetThemeManager(cardThemeManager);
    }
    if (cardThemeManager) {
        // Init resource, load theme map, do not parse yet.
        cardThemeManager->InitResource(cardResourceInfo);
        cardThemeManager->LoadSystemTheme(cardResourceInfo.GetThemeId());
        auto weakTheme = AceType::WeakClaim(AceType::RawPtr(cardThemeManager));
        auto weakAsset = AceType::WeakClaim(AceType::RawPtr(assetManagerImpl));
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
            TaskExecutor::TaskType::UI, "ArkUIFormLoadTheme");
    }

    auto&& actionEventHandler = [weak = WeakClaim(this)](const std::string& action) {
        auto container = weak.Upgrade();
        CHECK_NULL_VOID(container);

        if (Container::IsCurrentUseNewPipeline()) {
            auto form = container->GetFormPattern();
            CHECK_NULL_VOID(form);
            form->OnActionEvent(action);
        } else {
            auto form = AceType::DynamicCast<FormElement>(container->GetFormElement().Upgrade());
            CHECK_NULL_VOID(form);
            form->OnActionEvent(action);
        }
    };
    pipelineContext_->SetActionEventHandler(actionEventHandler);

    auto weakContext = AceType::WeakClaim(AceType::RawPtr(pipelineContext_));
    taskExecutor_->PostTask(
        [weakContext]() {
            auto context = weakContext.Upgrade();
            if (context == nullptr) {
                LOGE("RunCard PostTask Task failed, context is nullptr");
                return;
            }
            context->SetupRootElement();
        },
        TaskExecutor::TaskType::UI, "ArkUIFormSetupRootElement");

    frontend_->AttachPipelineContext(pipelineContext_);
    frontend_->SetLoadCardCallBack(outSidePipelineContext_);
    frontend_->SetRunningCardId(nodeId_);
    frontend_->SetDensity(density_);
    UpdateSurfaceSize();

    if (cardType_ == FrontendType::ETS_CARD) { // ETS Card : API9 only support NG-Host & NG-eTSCard
        if (Container::IsCurrentUseNewPipeline()) {
            auto pattern = formPattern_.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto pipelineContext = DynamicCast<NG::PipelineContext>(pipelineContext_);
            if (!pipelineContext) {
                LOGE("RunCard failed, pipeline context is nullptr");
                return;
            }
            pipelineContext->SetDrawDelegate(pattern->GetDrawDelegate());
            frontend_->RunPage("", data);
            return;
        } else {
            LOGE("ETS Card not support old pipeline");
            return;
        }
    } else if (cardType_ == FrontendType::JS_CARD) {
        // JS Card : API9 only support Old Pipeline JSCard, Host can be NG or Old
        if (Container::IsCurrentUseNewPipeline()) {
            auto pattern = formPattern_.Upgrade();
            CHECK_NULL_VOID(pattern);
            pipelineContext_->SetDrawDelegate(pattern->GetDrawDelegate());
            frontend_->RunPage("", data);
            if (onFormLoadCallback_) {
                onFormLoadCallback_();
            }
            return;
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

        frontend_->RunPage("", data);
    } else {
        LOGE("SubContainer::RunCard card type error");
    }
}

void SubContainer::RunSameCard()
{
    LOGI("SubContainer::RunSameCard ");
    if (onFormAcquiredCallback_) {
        onFormAcquiredCallback_(runningCardId_);
    }
    auto pattern = formPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto pipelineContext = DynamicCast<PipelineContext>(pipelineContext_);
    CHECK_NULL_VOID(pipelineContext);
    UpdateRootElementSize();
    pipelineContext_->OnSurfaceChanged(surfaceWidth_, surfaceHeight_);
    auto delegeta = pattern->GetDrawDelegate();
    pipelineContext->SetDrawDelegate(std::move(delegeta));
    pipelineContext->MarkForcedRefresh();
    pipelineContext_->FlushPipelineImmediately();
    onFormVisibleCallback_();
}

void SubContainer::ProcessSharedImage(const std::map<std::string, sptr<AppExecFwk::FormAshmem>> imageDataMap)
{
    std::vector<std::string> picNameArray;
    std::vector<int> fileDescriptorArray;
    std::vector<int> byteLenArray;
    if (!imageDataMap.empty()) {
        for (auto& imageData : imageDataMap) {
            if (!imageData.second) {
                LOGI("the point of FormAshmem about %{private}s is null, continue", imageData.first.c_str());
                continue;
            }
            picNameArray.push_back(imageData.first);
            fileDescriptorArray.push_back(imageData.second->GetAshmemFd());
            byteLenArray.push_back(imageData.second->GetAshmemSize());
        }
        GetNamesOfSharedImage(picNameArray);
        UpdateSharedImage(picNameArray, byteLenArray, fileDescriptorArray);
    }
}

void SubContainer::GetNamesOfSharedImage(std::vector<std::string>& picNameArray)
{
    if (picNameArray.empty()) {
        LOGE("picNameArray is null!");
        return;
    }
    auto pipelineCtx = DynamicCast<PipelineContext>(GetPipelineContext());
    if (!pipelineCtx) {
        LOGE("pipeline context is null!");
        return;
    }
    auto sharedImageManager = pipelineCtx->GetOrCreateSharedImageManager();
    auto nameSize = picNameArray.size();
    for (uint32_t i = 0; i < nameSize; i++) {
        // get name of picture
        auto name = picNameArray[i];
        sharedImageManager->AddPictureNamesToReloadMap(std::move(name));
    }
}

void SubContainer::UpdateSharedImage(
    std::vector<std::string>& picNameArray, std::vector<int32_t>& byteLenArray, std::vector<int>& fileDescriptorArray)
{
    auto pipelineCtx = GetPipelineContext();
    if (!pipelineCtx) {
        LOGE("pipeline context is null! when try UpdateSharedImage");
        return;
    }
    if (picNameArray.empty() || byteLenArray.empty() || fileDescriptorArray.empty()) {
        LOGE("array is null! when try UpdateSharedImage");
        return;
    }
    auto nameArraySize = picNameArray.size();
    if (nameArraySize != byteLenArray.size()) {
        LOGE("nameArraySize does not equal to fileDescriptorArraySize, please check!");
        return;
    }
    if (nameArraySize != fileDescriptorArray.size()) {
        LOGE("nameArraySize does not equal to fileDescriptorArraySize, please check!");
        return;
    }
    // now it can be assured that all three arrays are of the same size

    std::string picNameCopy;
    for (uint32_t i = 0; i < nameArraySize; i++) {
        // get name of picture
        auto picName = picNameArray[i];
        // save a copy of picName and ReleaseStringUTFChars immediately to avoid memory leak
        picNameCopy = picName;

        // get fd ID
        auto fd = fileDescriptorArray[i];

        auto newFd = dup(fd);
        if (newFd < 0) {
            LOGE("dup fd fail, fail reason: %{public}s, fd: %{public}d, picName: %{private}s, length: %{public}d",
                strerror(errno), fd, picNameCopy.c_str(), byteLenArray[i]);
            continue;
        }

        auto ashmem = Ashmem(newFd, byteLenArray[i]);
        GetImageDataFromAshmem(picNameCopy, ashmem, pipelineCtx, byteLenArray[i]);
        ashmem.UnmapAshmem();
        ashmem.CloseAshmem();
    }
}

void SubContainer::GetImageDataFromAshmem(
    const std::string& picName, Ashmem& ashmem, const RefPtr<PipelineBase>& pipelineContext, int len)
{
    bool ret = ashmem.MapReadOnlyAshmem();
    // if any exception causes a [return] before [AddSharedImage], the memory image will not show because [RenderImage]
    // will never be notified to start loading.
    if (!ret) {
        LOGE("MapReadOnlyAshmem fail, fail reason: %{public}s, picName: %{private}s, length: %{public}d, "
             "fd: %{public}d",
            strerror(errno), picName.c_str(), len, ashmem.GetAshmemFd());
        return;
    }
    const uint8_t* imageData = reinterpret_cast<const uint8_t*>(ashmem.ReadFromAshmem(len, 0));
    if (imageData == nullptr) {
        LOGE("imageData is nullptr, errno is: %{public}s, picName: %{private}s, length: %{public}d, fd: %{public}d",
            strerror(errno), picName.c_str(), len, ashmem.GetAshmemFd());
        return;
    }
    auto context = DynamicCast<PipelineContext>(pipelineContext);
    CHECK_NULL_VOID(context);
    RefPtr<SharedImageManager> sharedImageManager = context->GetOrCreateSharedImageManager();
    if (sharedImageManager) {
        // read image data from shared memory and save a copy to sharedImageManager
        sharedImageManager->AddSharedImage(picName, std::vector<uint8_t>(imageData, imageData + len));
    }
}

void SubContainer::UpdateCard(
    const std::string& content, const std::map<std::string, sptr<AppExecFwk::FormAshmem>>& imageDataMap)
{
    if (!frontend_) {
        LOGE("update card fial due to could not find card front end");
        return;
    }
    if (allowUpdate_) {
        frontend_->UpdateData(std::move(content));
        ProcessSharedImage(imageDataMap);
    }
}

void SubContainer::UpdateConfiguration()
{
    if (frontend_) {
        frontend_->OnMediaFeatureUpdate();
    }
}

bool SubContainer::Dump(const std::vector<std::string>& params)
{
    if (pipelineContext_) {
        pipelineContext_->Dump(params);
        return true;
    }
    return false;
}
} // namespace OHOS::Ace
