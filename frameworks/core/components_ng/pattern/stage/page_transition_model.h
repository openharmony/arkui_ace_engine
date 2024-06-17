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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_STAGE_PAGE_TRANSITION_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_STAGE_PAGE_TRANSITION_MODEL_H

#include <functional>
#include <mutex>

#include "frameworks/core/animation/page_transition_common.h"
#include "frameworks/core/components_ng/property/transition_property.h"

namespace OHOS::Ace {
using PageTransitionEventFunc = std::function<void(RouteType, const float&)>;

class ACE_FORCE_EXPORT PageTransitionModel {
public:
    static PageTransitionModel* GetInstance();
    virtual ~PageTransitionModel() = default;

    virtual void SetSlideEffect(SlideEffect effect) = 0;
    virtual void SetTranslateEffect(const NG::TranslateOptions& option) = 0;
    virtual void SetScaleEffect(const NG::ScaleOptions& option) = 0;
    virtual void SetOpacityEffect(float opacity) = 0;
    virtual void SetOnEnter(PageTransitionEventFunc&& handler) = 0;
    virtual void SetOnExit(PageTransitionEventFunc&& handler) = 0;
    virtual void CreateTransition(PageTransitionType type, const PageTransitionOption& option) = 0;
    virtual void Create() = 0;
    virtual void Pop() = 0;

private:
    static std::unique_ptr<PageTransitionModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_STAGE_PAGE_TRANSITION_MODEL_H