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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_ARKTS_DYNAMIC_FRONTEND_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_ARKTS_DYNAMIC_FRONTEND_H

#include <string>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/thread/task_executor.h"
#include "base/utils/noncopyable.h"
#include "core/common/frontend.h"
#include "core/pipeline/pipeline_context.h"
#include "frameworks/bridge/common/accessibility/accessibility_node_manager.h"
#include "bridge/arkts_frontend/arkts_frontend.h"

typedef struct __ani_env ani_env;
typedef class __ani_ref* ani_ref;
typedef struct __ani_vm ani_vm;

namespace OHOS::Ace {
/**
 * @brief Proxy class to interact with Koala frontend and static ArkTS runtime.
 *
 */
class ACE_FORCE_EXPORT ArktsDynamicFrontend : public ArktsFrontend {
    DECLARE_ACE_TYPE(ArktsDynamicFrontend, ArktsFrontend);

public:
    explicit ArktsDynamicFrontend(void* runtime);
    ~ArktsDynamicFrontend() override = default;

    void SetAssetManager(const RefPtr<AssetManager>& assetManager) override
    {
        assetManager_ = assetManager;
    }

    UIContentErrorCode RunDynamicPage(
        const std::string& content, const std::string& params, const std::string& entryPoint) override;

    void SetModuleName(const std::string& moduleName)
    {
        moduleName_ = moduleName;
    }

    void SetBundleName(const std::string& bundleName)
    {
        bundleName_ = bundleName;
    }

    std::string GetModuleName() const
    {
        return moduleName_;
    }

    std::string GetBundleName() const
    {
        return bundleName_;
    }

    void SetIsBundle(bool isBundle)
    {
        isBundle_ = isBundle;
    }

    bool IsBundle() const
    {
        return isBundle_;
    }

private:
    std::string bundleName_;
    std::string moduleName_;
    RefPtr<AssetManager> assetManager_;
    bool isBundle_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(ArktsDynamicFrontend);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_ARKTS_DYNAMIC_FRONTEND_H
