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

#include "adapter/preview/entrance/ace_container.h"
#include "adapter/preview/external/ability/context.h"
#include "bridge/common/utils/engine_helper.h"

#include "frameworks/base/i18n/localization.h"
#include "frameworks/core/common/ace_engine.h"
#include "frameworks/core/components_ng/render/adapter/rosen_window.h"

#include "frameworks/core/common/window_free_container.h"

namespace OHOS::Ace::Platform {
static RefPtr<AceContainer> g_windowFreeContainer = nullptr;
static RefPtr<Framework::JsEngine> g_jsEngine = nullptr;
RefPtr<Container> WindowFreeContainer::CreateWindowFreeContainer(void *runtime, void *ctx)
{
    LOGI("Create container without window.");
    auto container = AceContainer::GetContainerInstance(WINDOW_FREE_CONTAINER_ID);
    if (container) {
        return container;
    }

    if (g_windowFreeContainer) {
        AceEngine::Get().AddContainer(WINDOW_FREE_CONTAINER_ID, g_windowFreeContainer);
        EngineHelper::AddEngine(WINDOW_FREE_CONTAINER_ID, g_jsEngine);
        return g_windowFreeContainer;
    }

    CHECK_NULL_RETURN(runtime, nullptr);

    AceContainer::CreateContainer(WINDOW_FREE_CONTAINER_ID, FrontendType::DECLARATIVE_JS, true);
    auto ncontainer = AceContainer::GetContainerInstance(WINDOW_FREE_CONTAINER_ID);
    ncontainer->SetSharedRuntime(runtime);

    auto& setting = ncontainer->GetSettings();
    setting.usePlatformAsUIThread = true;
    setting.useUIAsJSThread = true;
    if (!Localization::GetInstance()->IsInit()) {
        AceApplicationInfo::GetInstance().SetLocale("", "", "", "");
    }

    auto view = AceViewPreview::CreateView(WINDOW_FREE_CONTAINER_ID, false, true);
    auto window = std::make_shared<NG::RosenWindow>(nullptr, ncontainer->GetTaskExecutor(), WINDOW_FREE_CONTAINER_ID);
    float width = 0.0f;
    float height = 0.0f;
    double density = 0.0;
    ncontainer->AttachView(window, view, density, width, height, nullptr);
    g_windowFreeContainer = ncontainer;
    g_jsEngine = EngineHelper::GetEngine(WINDOW_FREE_CONTAINER_ID);
    return ncontainer;
}

void WindowFreeContainer::DestroyWindowFreeContainer()
{
    LOGI("Destroy container without window.");
    // Destroy any container will make the rs being background, and stop rendering.
    // So just keep the container here.
    auto container = AceEngine::Get().GetContainer(WINDOW_FREE_CONTAINER_ID);
    if (!container) {
        return;
    }
    EngineHelper::RemoveEngine(WINDOW_FREE_CONTAINER_ID);
    AceEngine::Get().RemoveContainer(WINDOW_FREE_CONTAINER_ID);
}
} // namespace OHOS::Ace
