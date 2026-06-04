/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/view_advanced_register.h"

namespace OHOS::Ace::NG {
thread_local std::shared_ptr<ViewAdvancedRegister> ViewAdvancedRegister::instance_ = nullptr;

std::shared_ptr<ViewAdvancedRegister> ViewAdvancedRegister::GetInstance()
{
    if (!instance_) {
        instance_ = std::make_shared<ViewAdvancedRegister>();
    }
    return instance_;
}

RefPtr<PagePattern> ViewAdvancedRegister::CreatePagePattern(const RefPtr<PageInfo>& pageInfo)
{
    (void)pageInfo;
    return nullptr;
}

RefPtr<Pattern> ViewAdvancedRegister::GeneratePattern(const std::string& patternName)
{
    (void)patternName;
    return nullptr;
}

RefPtr<StageManager> ViewAdvancedRegister::GenerateStageManager(const RefPtr<FrameNode>& stage)
{
    (void)stage;
    return nullptr;
}
} // namespace OHOS::Ace::NG
