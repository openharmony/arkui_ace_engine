/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_ABILITY_STAGE_CONTEXT_H
#define FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_ABILITY_STAGE_CONTEXT_H

#include <string>

#include "adapter/preview/external/ability/context.h"
#include "adapter/preview/external/ability/stage/stage_app_info.h"
#include "adapter/preview/external/ability/stage/stage_pkg_context_info.h"
#include "adapter/preview/external/ability/stage/stage_hap_module_info.h"
#include "base/json/json_util.h"
#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"

namespace OHOS::Ace {
class StageContext : public Context {
    DECLARE_ACE_TYPE(StageContext, Context);

public:
    StageContext();
    ~StageContext() override = default;
    void Parse(const std::string& contents) override;
    const RefPtr<StageAppInfo>& GetAppInfo() const;
    const RefPtr<StageHapModuleInfo>& GetHapModuleInfo() const;
    const RefPtr<StagePkgContextInfo>& GetPkgContextInfo() const;
    
private:
    RefPtr<StageAppInfo> appInfo_;
    RefPtr<StageHapModuleInfo> hapModuleInfo_;
    RefPtr<StagePkgContextInfo> pkgContextInfo_;
    ACE_DISALLOW_COPY_AND_MOVE(StageContext);
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_ABILITY_STAGE_CONTEXT_H
