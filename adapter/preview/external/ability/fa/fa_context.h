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

#ifndef FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_ABILITY_FA_CONTEXT_H
#define FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_ABILITY_FA_CONTEXT_H

#include <string>

#include "adapter/preview/external/ability/context.h"
#include "adapter/preview/external/ability/fa/fa_app_info.h"
#include "adapter/preview/external/ability/fa/fa_hap_module_info.h"
#include "base/json/json_util.h"
#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"

namespace OHOS::Ace {
class FaContext : public Context {
    DECLARE_ACE_TYPE(FaContext, Context);

public:
    FaContext();
    ~FaContext() override = default;
    void Parse(const std::string& contents) override;
    const RefPtr<FaAppInfo>& GetAppInfo() const;
    const RefPtr<FaHapModuleInfo>& GetHapModuleInfo() const;

private:
    RefPtr<FaAppInfo> appInfo_;
    RefPtr<FaHapModuleInfo> hapModuleInfo_;
    ACE_DISALLOW_COPY_AND_MOVE(FaContext);
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_ABILITY_FA_CONTEXT_H
