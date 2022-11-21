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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_STAGE_PAGE_TRANSITION_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_STAGE_PAGE_TRANSITION_MODEL_NG_H

#include "frameworks/core/components_ng/pattern/stage/page_transition_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT PageTransitionModelNG : public PageTransitionModel {
public:
    PageTransitionModelNG() = default;
    ~PageTransitionModelNG() override = default;

    void SetSlideEffect(SlideEffect effect) override;
    void SetTranslateEffect(const NG::TranslateOptions& option) override;
    void SetScaleEffect(const NG::ScaleOptions& option) override;
    void SetOpacityEffect(float opacity) override;
    void SetOnEnter(PageTransitionEventFunc&& handler) override;
    void SetOnExit(PageTransitionEventFunc&& handler) override;
    void CreateTransition(PageTransitionType type, const PageTransitionOption& option) override;
    void Create() override;
    void Pop() override;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_STAGE_PAGE_TRANSITION_MODEL_NG_H