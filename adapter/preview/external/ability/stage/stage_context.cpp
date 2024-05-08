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

#include "adapter/preview/external/ability/stage/stage_context.h"

namespace OHOS::Ace {
StageContext::StageContext()
    : appInfo_(Referenced::MakeRefPtr<StageAppInfo>()), hapModuleInfo_(Referenced::MakeRefPtr<StageHapModuleInfo>()),
    pkgContextInfo_(Referenced::MakeRefPtr<StagePkgContextInfo>())
{}

void StageContext::Parse(const std::string& contents)
{
    auto rootJson = JsonUtil::ParseJsonString(contents);
    if (!rootJson || !rootJson->IsValid()) {
        LOGW("The format of stage application config is illegal.");
        return;
    }
    appInfo_->Parse(rootJson->GetValue("app"));
    hapModuleInfo_->Parse(rootJson->GetValue("module"));
}

const RefPtr<StageAppInfo>& StageContext::GetAppInfo() const
{
    return appInfo_;
}

const RefPtr<StageHapModuleInfo>& StageContext::GetHapModuleInfo() const
{
    return hapModuleInfo_;
}

const RefPtr<StagePkgContextInfo>& StageContext::GetPkgContextInfo() const
{
    return pkgContextInfo_;
}
} // namespace OHOS::Ace
