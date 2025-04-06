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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ADVANCED_REGISTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ADVANCED_REGISTER_H

#include "frameworks/core/components_ng/pattern/pattern.h"
#include "frameworks/core/components_ng/pattern/stage/page_info.h"
#include "frameworks/core/components_ng/pattern/stage/page_pattern.h"
#include "frameworks/core/components_ng/pattern/stage/stage_manager.h"

namespace OHOS::Ace::NG {
class ViewAdvancedRegister : public AceType {
public:
    ACE_FORCE_EXPORT static ViewAdvancedRegister* GetInstance();

    RefPtr<PagePattern> CreatePagePattern(const RefPtr<PageInfo>& pageInfo);

    RefPtr<Pattern> GeneratePattern(const std::string& patternName);

    RefPtr<StageManager> GenerateStageManager(const RefPtr<FrameNode>& stage);

private:
    ViewAdvancedRegister() = default;

    static thread_local ViewAdvancedRegister* instance_;
    ACE_DISALLOW_COPY_AND_MOVE(ViewAdvancedRegister);
};
} // namespace OHOS::Ace::NG
#endif