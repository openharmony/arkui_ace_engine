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

#include "adapter/ohos/entrance/ace_container.h"

#include <ani.h>

#include "adapter/ohos/entrance/ace_view_ohos.h"
#include "adapter/ohos/entrance/data_ability_helper_standard.h"
#include "adapter/ohos/entrance/file_asset_provider_impl.h"
#include "adapter/ohos/entrance/hap_asset_provider_impl.h"
#include "adapter/ohos/entrance/mmi_event_convertor.h"
#include "adapter/ohos/entrance/ui_content_impl.h"
#include "adapter/ohos/entrance/utils.h"
#include "adapter/ohos/osal/page_viewport_config_ohos.h"
#include "adapter/ohos/osal/resource_adapter_impl_v2.h"
#include "adapter/ohos/osal/system_bar_style_ohos.h"
#include "adapter/ohos/osal/view_data_wrap_ohos.h"
#include "adapter/ohos/osal/window_utils.h"
#include "base/i18n/localization.h"
#include "base/log/jank_frame_report.h"
#include "base/thread/background_task_executor.h"
#include "bridge/card_frontend/card_frontend.h"
#include "bridge/card_frontend/form_frontend_declarative.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.h"
#include "bridge/js_frontend/js_frontend.h"
#include "bridge/arkts_frontend/arkts_frontend.h"
#include "core/common/ace_application_info.h"
#include "core/common/ace_engine.h"
#include "core/common/plugin_manager.h"
#include "core/common/resource/resource_manager.h"
#include "core/common/task_executor_impl.h"
#include "core/components_ng/base/inspector.h"
#include "core/components_ng/render/adapter/form_render_window.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_ng/render/adapter/rosen_window.h"
#include "core/components_ng/token_theme/token_theme_storage.h"

namespace OHOS::Ace::Platform {
namespace {
constexpr char DECLARATIVE_ARK_ENGINE_SHARED_LIB[] = "libace_engine_declarative_ark.z.so";
const char* GetDeclarativeSharedLibrary()
{
    return DECLARATIVE_ARK_ENGINE_SHARED_LIB;
}
} // namespace

void AceContainer::InitializeStaticHybridDynamic(std::shared_ptr<OHOS::AppExecFwk::Ability> aceAbility)
{
    // 1.2 initialization
    frontend_ = MakeRefPtr<ArktsFrontend>(sharedRuntime_);
    // 1.1 initialization
#ifdef NG_BUILD
    subFrontend_ = AceType::MakeRefPtr<DeclarativeFrontendNG>();
    auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontendNG>(subFrontend_);
#else
    subFrontend_ = AceType::MakeRefPtr<DeclarativeFrontend>();
    auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontend>(subFrontend_);
#endif
    auto& loader = Framework::JsEngineLoader::GetDeclarative(GetDeclarativeSharedLibrary());
    RefPtr<Framework::JsEngine> jsEngine;
    if (GetSettings().usingSharedRuntime) {
        jsEngine = loader.CreateJsEngineUsingSharedRuntime(
            instanceId_, nullptr); // replace 1.1 preload runtime when initialize
    } else {
        jsEngine = loader.CreateJsEngine(instanceId_);
    }

    jsEngine->AddExtraNativeObject("ability", aceAbility.get());
    auto pageUrlCheckFunc = [id = instanceId_](
        const std::string& url, const std::function<void()>& callback,
        const std::function<void(int32_t, const std::string&)>& silentInstallErrorCallBack) {
        ContainerScope scope(id);
        auto container = Container::Current();
        CHECK_NULL_VOID(container);
        auto pageUrlChecker = container->GetPageUrlChecker();
        CHECK_NULL_VOID(pageUrlChecker);
        pageUrlChecker->LoadPageUrl(url, callback, silentInstallErrorCallBack);
    };
    jsEngine->SetPageUrlCheckFunc(std::move(pageUrlCheckFunc));

    EngineHelper::AddEngine(instanceId_, jsEngine);
    declarativeFrontend->SetJsEngine(jsEngine);
    declarativeFrontend->SetPageProfile(pageProfile_);
    declarativeFrontend->SetNeedDebugBreakPoint(AceApplicationInfo::GetInstance().IsNeedDebugBreakPoint());
    declarativeFrontend->SetDebugVersion(AceApplicationInfo::GetInstance().IsDebugVersion());
}

void AceContainer::InitializeDynamicHybridStatic(std::shared_ptr<OHOS::AppExecFwk::Ability> aceAbility)
{
    // 1.2 initialization
    if (!ArktsFrontend::preloadArkTSRuntime) {
        LOGE("AceContainer::InitializeDynamicHybridStatic: ArktsFrontend::preloadArkTSRuntime is null, preload Fail");
    }
    subFrontend_ = MakeRefPtr<ArktsFrontend>(ArktsFrontend::preloadArkTSRuntime);
    // 1.1 initialization
    if (isFormRender_) {
#ifdef FORM_SUPPORTED
        LOGI("Init Form Frontend");
        frontend_ = AceType::MakeRefPtr<FormFrontendDeclarative>();
        auto cardFrontend = AceType::DynamicCast<FormFrontendDeclarative>(frontend_);
        auto& loader = Framework::JsEngineLoader::GetDeclarative(GetDeclarativeSharedLibrary());
        RefPtr<Framework::JsEngine> jsEngine;
        if (GetSettings().usingSharedRuntime) {
            jsEngine = loader.CreateJsEngineUsingSharedRuntime(instanceId_, sharedRuntime_);
        } else {
            jsEngine = loader.CreateJsEngine(instanceId_);
        }
        jsEngine->AddExtraNativeObject("ability", aceAbility.get());

        EngineHelper::AddEngine(instanceId_, jsEngine);
        cardFrontend->SetJsEngine(jsEngine);
        cardFrontend->SetPageProfile(pageProfile_);
        cardFrontend->SetNeedDebugBreakPoint(AceApplicationInfo::GetInstance().IsNeedDebugBreakPoint());
        cardFrontend->SetDebugVersion(AceApplicationInfo::GetInstance().IsDebugVersion());
        // Card front
        cardFrontend->SetRunningCardId(0); // ArkTsCard : nodeId, Host->FMS->FRS->innersdk
        cardFrontend->SetIsFormRender(true);
#endif
    } else if (!isSubContainer_) {
#ifdef NG_BUILD
        frontend_ = AceType::MakeRefPtr<DeclarativeFrontendNG>();
        auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontendNG>(frontend_);
#else
        frontend_ = AceType::MakeRefPtr<DeclarativeFrontend>();
        auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontend>(frontend_);
#endif

        if (!IsDialogContainer()) {
            auto& loader = Framework::JsEngineLoader::GetDeclarative(GetDeclarativeSharedLibrary());
            RefPtr<Framework::JsEngine> jsEngine;
            if (GetSettings().usingSharedRuntime) {
                jsEngine = loader.CreateJsEngineUsingSharedRuntime(instanceId_, sharedRuntime_);
            } else {
                jsEngine = loader.CreateJsEngine(instanceId_);
            }

            jsEngine->AddExtraNativeObject("ability", aceAbility.get());
            auto pageUrlCheckFunc = [id = instanceId_](
                const std::string& url, const std::function<void()>& callback,
                const std::function<void(int32_t, const std::string&)>& silentInstallErrorCallBack) {
                ContainerScope scope(id);
                auto container = Container::Current();
                CHECK_NULL_VOID(container);
                auto pageUrlChecker = container->GetPageUrlChecker();
                CHECK_NULL_VOID(pageUrlChecker);
                pageUrlChecker->LoadPageUrl(url, callback, silentInstallErrorCallBack);
            };
            jsEngine->SetPageUrlCheckFunc(std::move(pageUrlCheckFunc));
            EngineHelper::AddEngine(instanceId_, jsEngine);

            declarativeFrontend->SetJsEngine(jsEngine);
            declarativeFrontend->SetPageProfile(pageProfile_);
            declarativeFrontend->SetNeedDebugBreakPoint(AceApplicationInfo::GetInstance().IsNeedDebugBreakPoint());
            declarativeFrontend->SetDebugVersion(AceApplicationInfo::GetInstance().IsDebugVersion());
        }
    } else {
        frontend_ = OHOS::Ace::Platform::AceContainer::GetContainer(parentId_)->GetFrontend();
        return;
    }
}

} // namespace OHOS::Ace::Platform