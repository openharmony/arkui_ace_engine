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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_OSAL_PAGE_VIEWPORT_CONFIG_OHOS_H
#define FOUNDATION_ACE_ADAPTER_OHOS_OSAL_PAGE_VIEWPORT_CONFIG_OHOS_H

#include <map>
#include <stack>

#include "core/common/page_viewport_config.h"
#include "core/components_ng/manager/safe_area/safe_area_manager.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "interfaces/inner_api/ace/viewport_config.h"

#include "wm/window.h"
#include "wm/wm_common.h"

namespace OHOS::Ace {
using AvoidAreaInfo = std::map<Rosen::AvoidAreaType, Rosen::AvoidArea>;

class PageViewportConfigOhos : public PageViewportConfig {
    DECLARE_ACE_TYPE(PageViewportConfigOhos, PageViewportConfig)
public:
    PageViewportConfigOhos() = default;
    ~PageViewportConfigOhos() = default;

    RefPtr<PageViewportConfig> Clone() const override;

    void SetPipelineContext(const WeakPtr<NG::PipelineContext>& pipeline)
    {
        pipeline_ = pipeline;
    }
    void SetViewportConfig(const ViewportConfig& config)
    {
        config_ = config;
    }

    NG::LayoutConstraintF CreateRootLayoutConstraint() const override;
    NG::SafeAreaInsets GetSafeArea() const override;
    void SetAvoidAreas(const AvoidAreaInfo& info)
    {
        avoidAreas_ = info;
    }

    int32_t GetWidth() const override
    {
        return config_.Width();
    }
    DisplayOrientation GetOrientation() const override
    {
        return static_cast<DisplayOrientation>(config_.Orientation());
    }
    void ApplySafeArea() override;
    void RestoreSafeArea() override;

private:
    struct BackupInfo {
        int32_t rootWidth = -1;
        int32_t rootHeight = -1;
        std::map<OHOS::Rosen::AvoidAreaType, NG::SafeAreaInsets> safeAreas;
    };
    std::stack<BackupInfo> backupInfos_;
    ViewportConfig config_;
    AvoidAreaInfo avoidAreas_;
    WeakPtr<NG::PipelineContext> pipeline_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_ADAPTER_OHOS_OSAL_PAGE_VIEWPORT_CONFIG_OHOS_H
