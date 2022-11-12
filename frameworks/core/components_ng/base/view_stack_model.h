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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_STACK_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_STACK_MODEL_H

#include <memory>
#include <string>

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components/common/properties/animation_option.h"

namespace OHOS::Ace {

class ACE_EXPORT ViewStackModel {
public:
    static ViewStackModel* GetInstance();
    virtual ~ViewStackModel() = default;

    virtual void Push(const RefPtr<AceType>& node, bool isCustomView) = 0;
    virtual void Pop() = 0;
    virtual void PopContainer() = 0;
    virtual void PushKey(const std::string& key) = 0;
    virtual void PopKey() = 0;
    virtual void NewScope() = 0;
    virtual RefPtr<AceType> Finish() = 0;
    virtual std::string ProcessViewId(const std::string& viewId) = 0;
    virtual AnimationOption GetImplicitAnimationOption() = 0;

private:
    static std::unique_ptr<ViewStackModel> instance_;
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_STACK_MODEL_H
