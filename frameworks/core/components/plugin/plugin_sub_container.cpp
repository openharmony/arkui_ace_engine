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

#include "core/components/plugin/plugin_sub_container.h"

#include "adapter/ohos/entrance/ace_application_info.h"
#include "bridge/common/utils/engine_helper.h"
#include "core/common/ace_engine.h"
#include "core/common/container_scope.h"
#include "core/common/plugin_manager.h"
#include "adapter/ohos/entrance/file_asset_provider_impl.h"
#include "core/components/plugin/hap_asset_provider_impl.h"
#include "core/components/plugin/plugin_element.h"
#include "core/components/plugin/plugin_window.h"
#include "core/components/plugin/render_plugin.h"

namespace OHOS::Ace {
namespace {
const int32_t THEME_ID_DEFAULT = 117440515;
constexpr char DECLARATIVE_ARK_ENGINE_SHARED_LIB[] = "libace_engine_declarative_ark.z.so";
} // namespace

const char* GetDeclarativeSharedLibrary()
{
    return DECLARATIVE_ARK_ENGINE_SHARED_LIB;
}

void PluginSubContainer::Initialize()
{
    ContainerScope scope(instanceId_);

    auto outSidePipelineContext = outSidePipelineContext_.Upgrade();
    if (!outSidePipelineContext) {
        return;
    }

    auto executor = outSidePipelineContext->GetTaskExecutor();
    if (!executor) {
        return;
    }

    taskExecutor_ = executor;

    frontend_ = AceType::MakeRefPtr<PluginFrontend>();
    if (!frontend_) {
        return;
    }

    auto container = AceEngine::Get().GetContainer(outSidePipelineContext->GetInstanceId());
    if (!container) {
        return;
    }

    // set JS engine，init in JS thread
    auto loader = PluginManager::GetInstance().GetJsEngineLoader();
    if (!loader) {
        loader = &Framework::JsEngineLoader::GetDeclarative(GetDeclarativeSharedLibrary());
        PluginManager::GetInstance().SetJsEngineLoader(loader);
    }

    RefPtr<Framework::JsEngine> jsEngine;
    if (container->GetSettings().usingSharedRuntime) {
        jsEngine = loader->CreateJsEngineUsingSharedRuntime(instanceId_, container->GetSharedRuntime());
    } else {
        jsEngine = loader->CreateJsEngine(instanceId_);
    }
    if (!jsEngine) {
        return;
    }
    if (!PluginManager::GetInstance().GetAceAbility()) {
        jsEngine->AddExtraNativeObject("ability", PluginManager::GetInstance().GetAceAbility());
    }

    frontend_->SetNeedDebugBreakPoint(AceApplicationInfo::GetInstance().IsNeedDebugBreakPoint());
    frontend_->SetDebugVersion(AceApplicationInfo::GetInstance().IsDebugVersion());
    jsEngine->SetForceUpdate(true);
    EngineHelper::AddEngine(instanceId_, jsEngine);
    frontend_->SetJsEngine(jsEngine);
    frontend_->Initialize(FrontendType::JS_PLUGIN, taskExecutor_);
}

void PluginSubContainer::Destroy()
{
    ContainerScope scope(instanceId_);
    if (frontend_) {
        frontend_->Destroy();
        frontend_.Reset();
    }
    if (!pipelineContext_) {
        return;
    }

    if (!taskExecutor_) {
        return;
    }

    auto outPipelineContext = outSidePipelineContext_.Upgrade();
    if (outPipelineContext) {
        outPipelineContext->RemoveTouchPipeline(WeakPtr<PipelineBase>(pipelineContext_));
    }
    assetManager_.Reset();
    pipelineContext_.Reset();
    EngineHelper::RemoveEngine(instanceId_);
}

void PluginSubContainer::UpdateRootElementSize()
{
    Dimension rootWidth = 0.0_vp;
    Dimension rootHeight = 0.0_vp;
    if (Container::IsCurrentUseNewPipeline()) {
        auto plugin = pluginPattern_.Upgrade();
        CHECK_NULL_VOID(plugin);
        auto layoutProperty = plugin->GetLayoutProperty<NG::PluginLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        auto pluginInfo = layoutProperty->GetRequestPluginInfo();
        if (pluginInfo.has_value()) {
            rootWidth = pluginInfo->width;
            rootHeight = pluginInfo->height;
        }
    } else {
        auto pluginComponent = AceType::DynamicCast<PluginComponent>(pluginComponent_);
        if (pluginComponent) {
            rootWidth = pluginComponent->GetWidth();
            rootHeight = pluginComponent->GetHeight();
        }
    }

    if (rootWidth_ == rootWidth && rootHeight_ == rootHeight) {
        return;
    }
    surfaceWidth_ = outSidePipelineContext_.Upgrade()->NormalizeToPx(rootWidth);
    surfaceHeight_ = outSidePipelineContext_.Upgrade()->NormalizeToPx(rootHeight);
    if (pipelineContext_) {
        pipelineContext_->SetRootSize(density_, rootWidth.Value(), rootHeight.Value());
    }
}

void PluginSubContainer::UpdateSurfaceSize()
{
    if (!taskExecutor_) {
        return;
    }
    auto weakContext = AceType::WeakClaim(AceType::RawPtr(pipelineContext_));
    taskExecutor_->PostTask(
        [weakContext, surfaceWidth = surfaceWidth_, surfaceHeight = surfaceHeight_]() {
            auto context = weakContext.Upgrade();
            if (context == nullptr) {
                return;
            }
            if (NearZero(surfaceWidth) && NearZero(surfaceHeight)) {
                return;
            }
            context->OnSurfaceChanged(surfaceWidth, surfaceHeight);
        },
        TaskExecutor::TaskType::UI, "ArkUIPluginUpdateSurfaceSize");
}

void PluginSubContainer::RunDecompressedPlugin(const std::string& hapPath, const std::string& module,
    const std::string& source, const std::string& moduleResPath, const std::string& data)
{
    ContainerScope scope(instanceId_);
    CHECK_NULL_VOID(frontend_);
    frontend_->ResetPageLoadState();
    auto assetManager = GetDecompressedAssetManager(hapPath, module);

    auto&& window = std::make_unique<PluginWindow>(outSidePipelineContext_);
    window->SetPluginWindowId(pluginWindowId_);
    pipelineContext_ = AceType::MakeRefPtr<PipelineContext>(std::move(window), taskExecutor_, assetManager_,
        outSidePipelineContext_.Upgrade()->GetPlatformResRegister(), frontend_, instanceId_);

    density_ = outSidePipelineContext_.Upgrade()->GetDensity();
    auto eventManager = outSidePipelineContext_.Upgrade()->GetEventManager();
    pipelineContext_->SetEventManager(eventManager);
    UpdateRootElementSize();
    pipelineContext_->SetIsJsPlugin(true);

    SetPluginComponentTheme(moduleResPath, assetManager);
    SetActionEventHandler();

    auto weakContext = AceType::WeakClaim(AceType::RawPtr(pipelineContext_));
    taskExecutor_->PostTask(
        [weakContext, instance = instanceId_]() {
            ContainerScope scope(instance);
            auto context = weakContext.Upgrade();
            if (context == nullptr) {
                return;
            }
            context->SetupRootElement();
        },
        TaskExecutor::TaskType::UI, "ArkUIPluginDecompressedSetupRootElement");

    if (frontend_) {
        frontend_->AttachPipelineContext(pipelineContext_);
    }
    if (frontend_) {
        frontend_->SetDensity(density_);
        UpdateSurfaceSize();
    }

    if (Container::IsCurrentUseNewPipeline()) {
        auto pluginPattern = pluginPattern_.Upgrade();
        CHECK_NULL_VOID(pluginPattern);
        pipelineContext_->SetDrawDelegate(pluginPattern->GetDrawDelegate());
        frontend_->SetInstanceName(module);
        frontend_->RunPage(source, data);
        return;
    }

    auto plugin = AceType::DynamicCast<PluginElement>(GetPluginElement().Upgrade());
    CHECK_NULL_VOID(plugin);
    auto renderNode = plugin->GetRenderNode();
    CHECK_NULL_VOID(renderNode);
    auto pluginRender = AceType::DynamicCast<RenderPlugin>(renderNode);
    CHECK_NULL_VOID(pluginRender);
    pipelineContext_->SetDrawDelegate(pluginRender->GetDrawDelegate());

    frontend_->SetInstanceName(module);
    frontend_->RunPage(source, data);
}

void PluginSubContainer::RunPlugin(const std::string& path, const std::string& module, const std::string& source,
    const std::string& moduleResPath, const std::string& data)
{
    ContainerScope scope(instanceId_);
    CHECK_NULL_VOID(frontend_);
    frontend_->ResetPageLoadState();
    auto assetManager = SetAssetManager(path, module);

    auto&& window = std::make_unique<PluginWindow>(outSidePipelineContext_);
    pipelineContext_ = AceType::MakeRefPtr<PipelineContext>(std::move(window), taskExecutor_, assetManager_,
        outSidePipelineContext_.Upgrade()->GetPlatformResRegister(), frontend_, instanceId_);

    density_ = outSidePipelineContext_.Upgrade()->GetDensity();
    auto eventManager = outSidePipelineContext_.Upgrade()->GetEventManager();
    pipelineContext_->SetEventManager(eventManager);
    UpdateRootElementSize();
    pipelineContext_->SetIsJsPlugin(true);

    SetPluginComponentTheme(moduleResPath, assetManager);
    SetActionEventHandler();

    auto weakContext = AceType::WeakClaim(AceType::RawPtr(pipelineContext_));
    taskExecutor_->PostTask(
        [weakContext, this]() {
            ContainerScope scope(instanceId_);
            auto context = weakContext.Upgrade();
            if (context == nullptr) {
                return;
            }
            context->SetupRootElement();
        },
        TaskExecutor::TaskType::UI, "ArkUIPluginSetupRootElement");

    if (frontend_) {
        frontend_->AttachPipelineContext(pipelineContext_);
    }
    if (frontend_) {
        frontend_->SetDensity(density_);
        UpdateSurfaceSize();
    }

    if (Container::IsCurrentUseNewPipeline()) {
        auto pluginPattern = pluginPattern_.Upgrade();
        CHECK_NULL_VOID(pluginPattern);
        pipelineContext_->SetDrawDelegate(pluginPattern->GetDrawDelegate());
        frontend_->SetInstanceName(module);
        frontend_->RunPage(source, data);
        return;
    }

    auto plugin = AceType::DynamicCast<PluginElement>(GetPluginElement().Upgrade());
    if (!plugin) {
        return;
    }
    auto renderNode = plugin->GetRenderNode();
    if (!renderNode) {
        return;
    }
    auto pluginRender = AceType::DynamicCast<RenderPlugin>(renderNode);
    if (!pluginRender) {
        return;
    }
    pipelineContext_->SetDrawDelegate(pluginRender->GetDrawDelegate());

    frontend_->SetInstanceName(module);
    frontend_->RunPage(source, data);
}

void PluginSubContainer::SetPluginComponentTheme(
    const std::string& path, const RefPtr<AssetManager>& assetManager)
{
    ResourceInfo pluginResourceInfo;
    ResourceConfiguration resConfig;
    resConfig.SetDensity(density_);
    pluginResourceInfo.SetThemeId(THEME_ID_DEFAULT);
    auto position = path.rfind('/');
    if (position == std::string::npos) {
        pluginResourceInfo.SetPackagePath(path);
    } else {
        pluginResourceInfo.SetPackagePath(path.substr(0, position + 1));
    }
    pluginResourceInfo.SetResourceConfiguration(resConfig);
    RefPtr<ThemeManagerImpl> pluginThemeManager;
    if (SystemProperties::GetResourceDecoupling()) {
        auto resourceAdapter = ResourceAdapter::CreateV2();
        pluginThemeManager = AceType::MakeRefPtr<ThemeManagerImpl>(resourceAdapter);
    } else {
        pluginThemeManager = AceType::MakeRefPtr<ThemeManagerImpl>();
    }
    pipelineContext_->SetThemeManager(pluginThemeManager);
    if (pluginThemeManager) {
        // Init resource, load theme map, do not parse yet.
        pluginThemeManager->InitResource(pluginResourceInfo);
        pluginThemeManager->LoadSystemTheme(pluginResourceInfo.GetThemeId());
        auto weakTheme = AceType::WeakClaim(AceType::RawPtr(pluginThemeManager));
        auto weakAsset = AceType::WeakClaim(AceType::RawPtr(assetManager));
        taskExecutor_->PostTask(
            [weakTheme, weakAsset]() {
                auto themeManager = weakTheme.Upgrade();
                if (themeManager == nullptr) {
                    return;
                }
                themeManager->ParseSystemTheme();
                themeManager->SetColorScheme(ColorScheme::SCHEME_LIGHT);
                themeManager->LoadCustomTheme(weakAsset.Upgrade());
            },
            TaskExecutor::TaskType::UI, "ArkUIPluginLoadTheme");
    }
}

void PluginSubContainer::SetActionEventHandler()
{
    auto&& actionEventHandler = [weak = WeakClaim(this)](const std::string& action) {
        auto container = weak.Upgrade();
        CHECK_NULL_VOID(container);
        if (Container::IsCurrentUseNewPipeline()) {
            auto plugin = container->GetPluginPattern();
            CHECK_NULL_VOID(plugin);
            plugin->OnActionEvent(action);
        } else {
            auto plugin = AceType::DynamicCast<PluginElement>(container->GetPluginElement().Upgrade());
            CHECK_NULL_VOID(plugin);
            plugin->OnActionEvent(action);
        }
    };
    pipelineContext_->SetActionEventHandler(actionEventHandler);
}

RefPtr<AssetManager> PluginSubContainer::GetDecompressedAssetManager(
    const std::string& hapPath, const std::string& module)
{
    std::vector<std::string> basePaths;
    std::string path1 = "assets/js/" + module + "/";
    std::string path2 = "assets/js/share";
    basePaths.push_back(path1);
    basePaths.push_back(path2);
    basePaths.push_back("");
    RefPtr<AssetManagerImpl> assetManagerImpl = Referenced::MakeRefPtr<AssetManagerImpl>();
    if (assetManagerImpl) {
        frontend_->SetAssetManager(assetManagerImpl);
        assetManager_ = assetManagerImpl;
        auto assetProvider = AceType::MakeRefPtr<Plugin::HapAssetProviderImpl>();
        if (assetProvider->Initialize(hapPath, basePaths)) {
            assetManagerImpl->PushBack(std::move(assetProvider));
        }
    }
    return assetManagerImpl;
}

RefPtr<AssetManager> PluginSubContainer::SetAssetManager(const std::string& path, const std::string& module)
{
    std::string temp1 = "assets/js/" + module + "/";
    std::string temp2 = "assets/js/share/";
    std::vector<std::string> basePaths;
    basePaths.push_back(temp1);
    basePaths.push_back(temp2);
    basePaths.push_back("");
    RefPtr<AssetManagerImpl> assetManagerImpl = Referenced::MakeRefPtr<AssetManagerImpl>();
    if (assetManagerImpl) {
        frontend_->SetAssetManager(assetManagerImpl);
        assetManager_ = assetManagerImpl;
        auto assetProvider = AceType::MakeRefPtr<FileAssetProviderImpl>();
        if (assetProvider->Initialize(path, basePaths)) {
            assetManagerImpl->PushBack(std::move(assetProvider));
        }
    }
    return assetManagerImpl;
}

void PluginSubContainer::UpdatePlugin(const std::string& content)
{
    ContainerScope scope(instanceId_);

    if (!frontend_) {
        return;
    }
    frontend_->UpdatePlugin(content);
}
} // namespace OHOS::Ace
