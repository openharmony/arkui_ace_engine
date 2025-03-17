/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "ability_info.h"
#include "ability_context.h"
#include "ui_extension_context.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/entrance/ace_application_info.h"
#include "adapter/ohos/entrance/ace_view_ohos.h"
#include "adapter/ohos/entrance/hap_asset_provider_impl.h"
#include "adapter/ohos/entrance/file_asset_provider_impl.h"
#include "frameworks/base/i18n/localization.h"
#include "frameworks/core/common/ace_engine.h"
#include "frameworks/core/common/ace_view.h"
#include "frameworks/core/common/asset_manager_impl.h"
#include "frameworks/core/common/window_free_container.h"
#include "frameworks/core/components_ng/render/adapter/rosen_window.h"

namespace OHOS::Ace::Platform {
namespace {
static RefPtr<Platform::AceContainer> g_WindowFreeContainer = nullptr;

constexpr char ABS_BUNDLE_CODE_PATH[] = "/data/app/el1/bundle/public/";
constexpr char LOCAL_BUNDLE_CODE_PATH[] = "/data/storage/el1/bundle/";
constexpr char FILE_SEPARATOR[] = "/";

}

class PseudoEventCallback final : public Platform::PlatformEventCallback {
public:
    PseudoEventCallback() = default;
    virtual ~PseudoEventCallback() = default;
    void OnFinish() const override {}
    void OnStatusBarBgColorChanged(uint32_t) override {}
};

void InitAssetManager(RefPtr<AssetManagerImpl> &assetManagerImpl, std::shared_ptr<OHOS::AppExecFwk::AbilityInfo> info,
    std::shared_ptr<OHOS::AbilityRuntime::Context> context)
{
    if (!assetManagerImpl) {
        return;
    }

    bool isModelJson = info != nullptr ? info->isModuleJson : false;
    if (!isModelJson) {
        LOGW("The application doesn't use module.json5.");
        return;
    }

    std::string moduleName = info != nullptr ? info->moduleName : "";
    auto appInfo = context != nullptr ? context->GetApplicationInfo() : nullptr;
    auto hapModuleInfo = context != nullptr ? context->GetHapModuleInfo() : nullptr;
    auto bundleName = info != nullptr ? info->bundleName : "";
    std::string resPath;

    std::string hapPath = info != nullptr ? info->hapPath : "";
    // first use hap provider
    if (!hapPath.empty()) {
        auto hapAssetProviderImpl = AceType::MakeRefPtr<HapAssetProviderImpl>();
        if (hapAssetProviderImpl->Initialize(hapPath, { "", "ets/", "resources/base/profile/" })) {
            assetManagerImpl->PushBack(std::move(hapAssetProviderImpl));
        }
    }

    if (appInfo) {
        std::vector<OHOS::AppExecFwk::ModuleInfo> moduleList = appInfo->moduleInfos;
        for (const auto& module : moduleList) {
            if (module.moduleName == moduleName) {
                std::regex pattern(ABS_BUNDLE_CODE_PATH + bundleName + FILE_SEPARATOR);
                auto moduleSourceDir =
                    std::regex_replace(module.moduleSourceDir, pattern, LOCAL_BUNDLE_CODE_PATH);
                resPath = moduleSourceDir + "/";
                break;
            }
        }
    }

    // second use file provider, will remove later
    auto assetBasePathStr = { std::string("ets/"), std::string("resources/base/profile/") };
    if (!resPath.empty()) {
        auto assetProvider = AceType::MakeRefPtr<FileAssetProviderImpl>();
        if (assetProvider->Initialize(resPath, assetBasePathStr)) {
            assetManagerImpl->PushBack(std::move(assetProvider));
        }
    }
}

std::shared_ptr<OHOS::AppExecFwk::AbilityInfo> GetAbilityInfo(std::shared_ptr<OHOS::AbilityRuntime::Context>& context,
    std::string& tempDir)
{
    std::shared_ptr<OHOS::AppExecFwk::AbilityInfo> info;
    auto abilityContext = OHOS::AbilityRuntime::Context::ConvertTo<OHOS::AbilityRuntime::AbilityContext>(context);
    if (abilityContext) {
        info = abilityContext->GetAbilityInfo();
        tempDir = abilityContext->GetTempDir();
        return info;
    }

    auto extensionContext =
        OHOS::AbilityRuntime::Context::ConvertTo<OHOS::AbilityRuntime::ExtensionContext>(context);
    if (extensionContext) {
        info = extensionContext->GetAbilityInfo();
    }
    return info;
}

std::string GetHapPath(std::shared_ptr<OHOS::AppExecFwk::AbilityInfo>& info)
{
    std::string hapPath;
    std::string moduleHapPath = info != nullptr ? info->hapPath : "";
    if (moduleHapPath.empty()) {
        return hapPath;
    }

    if (moduleHapPath.find(ABS_BUNDLE_CODE_PATH) == std::string::npos) {
        hapPath = moduleHapPath;
    } else {
        auto pos = moduleHapPath.find_last_of('/');
        if (pos != std::string::npos) {
            hapPath = LOCAL_BUNDLE_CODE_PATH + moduleHapPath.substr(pos + 1);
        }
    }
    return hapPath;
}

void InitLocalizationIfNeeded(std::shared_ptr<OHOS::AbilityRuntime::Context>& context)
{
    if (Localization::GetInstance()->IsInit()) {
        return;
    }

    std::unique_ptr<Global::Resource::ResConfig> resConfig(Global::Resource::CreateResConfig());
    auto resourceManager = context->GetResourceManager();
    if (resourceManager == nullptr) {
        return;
    }

    resourceManager->GetResConfig(*resConfig);
    auto localeInfo = resConfig->GetLocaleInfo();
    Platform::AceApplicationInfoImpl::GetInstance().SetResourceManager(resourceManager);
    if (localeInfo != nullptr) {
        auto language = localeInfo->getLanguage();
        auto region = localeInfo->getCountry();
        auto script = localeInfo->getScript();
        AceApplicationInfo::GetInstance().SetLocale((language == nullptr) ? "" : language,
            (region == nullptr) ? "" : region, (script == nullptr) ? "" : script, "");
    }
}

double GetDensity()
{
    double density = 1.0;
    auto defaultDisplay = Rosen::DisplayManager::GetInstance().GetDefaultDisplay();
    if (defaultDisplay) {
        auto temp = defaultDisplay->GetVirtualPixelRatio();
        if (!NearEqual(temp, 1.0f)) {
            density = temp;
        }
    }
    return density;
}

RefPtr<Container> WindowFreeContainer::CreateWindowFreeContainer(void *runtime, void *ctx)
{
    if (g_WindowFreeContainer) {
        return g_WindowFreeContainer;
    }
    CHECK_NULL_RETURN(runtime, nullptr);
    CHECK_NULL_RETURN(ctx, nullptr);
    int32_t instanceId = Container::GenerateId<WINDOW_FREE_CONTAINER>();

    std::shared_ptr<OHOS::AbilityRuntime::Context> context =
        (static_cast<std::weak_ptr<AbilityRuntime::Context>*>(ctx))->lock();
    CHECK_NULL_RETURN(context, nullptr);
    std::string tempDir;
    std::shared_ptr<OHOS::AppExecFwk::AbilityInfo> info = GetAbilityInfo(context, tempDir);
    auto container = AceType::MakeRefPtr<Platform::AceContainer>(instanceId, FrontendType::DECLARATIVE_JS,
        context, info, std::make_unique<PseudoEventCallback>(), false, false, true);
    if (!container) {
        LOGW("Create container failed.");
        return container;
    }

    AceEngine::Get().AddContainer(instanceId, container);
    g_WindowFreeContainer = container;

    container->SetSharedRuntime(runtime);
    container->GetSettings().SetUsingSharedRuntime(true);
    container->GetSettings().usePlatformAsUIThread = true;
    container->GetSettings().useUIAsJSThread = true;

    container->Initialize();
    container->SetBundlePath(context->GetBundleCodeDir());
    container->SetFilesDataPath(context->GetFilesDir());
    std::string hapPath = GetHapPath(info);
    container->SetHapPath(hapPath);
    container->SetTempDir(tempDir);

    ContainerScope scope(instanceId);
    InitLocalizationIfNeeded(context);
    RefPtr<AssetManagerImpl> assetManagerImpl;
    InitAssetManager(assetManagerImpl, info, context);
    container->SetAssetManager(assetManagerImpl);

    auto window = std::make_shared<NG::RosenWindow>(nullptr, container->GetTaskExecutor(), instanceId);
    RefPtr<Platform::AceViewOhos> aceView =
        Platform::AceViewOhos::CreateView(instanceId, false, container->GetSettings().usePlatformAsUIThread);
    double density = GetDensity();
    float width = 0.0f;
    float height = 0.0f;

    container->AttachView(window, aceView, density, width, height, Rosen::INVALID_WINDOW_ID, nullptr);
    return container;
}

void WindowFreeContainer::DestroyWindowFreeContainer()
{
    if (!g_WindowFreeContainer) {
        LOGW("Container without window doesn't exist.");
        return;
    }
    int32_t instanceId = g_WindowFreeContainer->GetInstanceId();
    Platform::AceContainer::DestroyContainer(instanceId, nullptr);
    ContainerScope::RemoveAndCheck(instanceId);
    g_WindowFreeContainer.Reset();
}
} // namespace OHOS::Ace
