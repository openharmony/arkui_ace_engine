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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RELATIVE_CONTAINER_RELATIVE_CONTAINER_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RELATIVE_CONTAINER_RELATIVE_CONTAINER_MODEL_H

#include <mutex>

#include "base/memory/ace_type.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_abstract_model.h"

namespace OHOS::Ace {

class ACE_FORCE_EXPORT RelativeContainerModel {
public:
    static RelativeContainerModel* GetInstance();
    virtual ~RelativeContainerModel() = default;

    virtual void Create();
    virtual void SetBarrier(const std::vector<BarrierInfo>& barrierInfo) = 0;
    virtual void SetGuideline(const std::vector<GuidelineInfo>& guidelineInfo) = 0;
    virtual void ResetResObj(const std::string& key) {};
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RELATIVE_CONTAINER_RELATIVE_CONTAINER_MODEL_H