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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_DYNAMIC_COMPONENT_ARKTS_DYNAMIC_UICONTENT_IMPL_H
#define FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_DYNAMIC_COMPONENT_ARKTS_DYNAMIC_UICONTENT_IMPL_H

#include <cstdint>

#include "adapter/ohos/entrance/ui_content_impl.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/entrance/ace_view_ohos.h"
#include "base/memory/ace_type.h"
#include "base/thread/task_executor.h"
#include "core/common/asset_manager_impl.h"
#include "interfaces/inner_api/ace/ui_content_config.h"

#include "core/image/image_file_cache.h"

namespace OHOS::Ace::NG {

struct DcCreateParam {
    bool isFormRender = false;
    AceLogTag aceLogTag = AceLogTag::ACE_DEFAULT_DOMAIN;
};

class ArktsDynamicUIContentImpl : public UIContentImpl {
public:
    ArktsDynamicUIContentImpl(OHOS::AbilityRuntime::Context* context,
        void* aniEnv, VMType vmType, const DcCreateParam& param);
    ~ArktsDynamicUIContentImpl() override;

    static std::shared_ptr<ArktsDynamicUIContentImpl> Create(OHOS::AbilityRuntime::Context* context,
        void* aniEnv, VMType vmType, const DcCreateParam& param);

    void InitializeArktsDynamicUIContentImpl(const DynamicInitialConfig& config);
    UIContentErrorCode CommonInitializeDc(const std::string& contentInfo);

private:
    void CommonInitializeAceApplicationInfo();
    void CommonInitializeConfiguration();
    void CommonInitializeDeviceInfo(
        int32_t &deviceWidth, int32_t &deviceHeight, float &density);
    void CommonInitializeResourceManager(ColorMode &colorMode);
    void CommonInitializeAssetManager(const RefPtr<AssetManager>& assetManager);
    RefPtr<Platform::AceContainer> CreateAceContainer(
        const std::shared_ptr<OHOS::AppExecFwk::AbilityInfo>& info);
    void AfterContainerInitialize();
    RefPtr<Platform::AceViewOhos> CreateAceView(float &density);
    void HandleCommonInitializeWindowFocus();
    void HandleSurfaceChanged(const RefPtr<Platform::AceViewOhos>& aceView,
        int32_t deviceWidth, int32_t deviceHeight, bool isModelJson);

    AceLogTag aceLogTag_ = AceLogTag::ACE_DEFAULT_DOMAIN;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_DYNAMIC_COMPONENT_ARKTS_DYNAMIC_UICONTENT_IMPL_H
