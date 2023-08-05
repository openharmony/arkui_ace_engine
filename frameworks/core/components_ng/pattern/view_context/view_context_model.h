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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIEW_VIEW_CONTEXT_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIEW_VIEW_CONTEXT_MODEL_H

#include <mutex>

#include "core/components/common/properties/animation_option.h"

namespace OHOS::Ace {
class ViewContextModel {
public:
    static ViewContextModel* GetInstance();
    virtual ~ViewContextModel() = default;

    virtual void closeAnimation(const AnimationOption& option, bool needFlush) = 0;
    virtual void openAnimation(const AnimationOption& option) = 0;

private:
    static std::unique_ptr<ViewContextModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIEW_VIEW_CONTEXT_MODEL_H
