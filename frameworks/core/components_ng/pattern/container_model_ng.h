/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LINEAR_LAYOUT_ROW_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LINEAR_LAYOUT_ROW_MODEL_NG_H

#include <memory>

#include "base/utils/macros.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/container_model.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ContainerModelNG : public ContainerModel {
public:
    void Pop() override
    {
        ViewStackProcessor::GetInstance()->PopContainer();
    }

    void NewScope() override
    {
        scopeStack_ = std::make_unique<ScopedViewStackProcessor>();
    }

    RefPtr<AceType> Finish() override
    {
        auto node = ViewStackProcessor::GetInstance()->Finish();
        scopeStack_.reset();
        return node;
    }

private:
    std::unique_ptr<ScopedViewStackProcessor> scopeStack_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LINEAR_LAYOUT_ROW_MODEL_NG_H
