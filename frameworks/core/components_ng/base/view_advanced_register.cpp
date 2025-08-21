/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "frameworks/core/components_ng/base/view_advanced_register.h"
#include "frameworks/core/components_ng/pattern/root/root_pattern.h"
#ifdef ENABLE_SPLIT_MODE
#include "frameworks/core/components_ng/pattern/stage/force_split/parallel_page_pattern.h"
#include "frameworks/core/components_ng/pattern/stage/force_split/parallel_stage_manager.h"
#include "frameworks/core/components_ng/pattern/stage/force_split/parallel_stage_pattern.h"
#endif

namespace OHOS::Ace::NG {
thread_local ViewAdvancedRegister* ViewAdvancedRegister::instance_ = nullptr;

ViewAdvancedRegister* ViewAdvancedRegister::GetInstance()
{
    if (ViewAdvancedRegister::instance_ == nullptr) {
        ViewAdvancedRegister::instance_ = new ViewAdvancedRegister();
    }
    return ViewAdvancedRegister::instance_;
}

RefPtr<PagePattern> ViewAdvancedRegister::CreatePagePattern(const RefPtr<PageInfo>& pageInfo)
{
#ifdef ENABLE_SPLIT_MODE
    if (SystemProperties::GetDeviceType() == DeviceType::TABLET ||
        SystemProperties::GetDeviceType() == DeviceType::TWO_IN_ONE ||
        SystemProperties::IsForcibleLandscapeEnabled()) {
        return AceType::MakeRefPtr<ParallelPagePattern>(pageInfo);
    }
#endif
    return AceType::MakeRefPtr<PagePattern>(pageInfo);
}

RefPtr<Pattern> ViewAdvancedRegister::GeneratePattern(const std::string& patternName)
{
    if (patternName == V2::STAGE_ETS_TAG) {
#ifdef ENABLE_SPLIT_MODE
        if (SystemProperties::GetDeviceType() == DeviceType::TABLET ||
            SystemProperties::GetDeviceType() == DeviceType::TWO_IN_ONE ||
            SystemProperties::IsForcibleLandscapeEnabled()) {
            return AceType::MakeRefPtr<ParallelStagePattern>();
        }
#endif
        return AceType::MakeRefPtr<StagePattern>();
    }
    if (patternName == V2::ROOT_ETS_TAG) {
        return AceType::MakeRefPtr<RootPattern>();
    }
    return nullptr;
}

RefPtr<StageManager> ViewAdvancedRegister::GenerateStageManager(const RefPtr<FrameNode>& stage)
{
#ifdef ENABLE_SPLIT_MODE
    if (SystemProperties::GetDeviceType() == DeviceType::TABLET ||
        SystemProperties::GetDeviceType() == DeviceType::TWO_IN_ONE ||
        SystemProperties::IsForcibleLandscapeEnabled()) {
        return AceType::MakeRefPtr<ParallelStageManager>(stage);
    }
#endif
    return AceType::MakeRefPtr<StageManager>(stage);
}
} // namespace OHOS::Ace::NG