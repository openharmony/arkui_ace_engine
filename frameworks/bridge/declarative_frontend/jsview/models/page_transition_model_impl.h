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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JSVIEW_MODELS_PAGE_TRANSITION_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JSVIEW_MODELS_PAGE_TRANSITION_MODEL_IMPL_H

#include "frameworks/core/components_ng/pattern/stage/page_transition_model.h"

namespace OHOS::Ace {
class PageTransition;
} // OHOS::Ace

namespace OHOS::Ace::Framework {
class PageTransitionModelImpl : public PageTransitionModel {
public:
    PageTransitionModelImpl() = default;
    ~PageTransitionModelImpl() override = default;

    void SetSlideEffect(SlideEffect effect) override;
    void SetTranslateEffect(const NG::TranslateOptions& option) override;
    void SetScaleEffect(const NG::ScaleOptions& option) override;
    void SetOpacityEffect(float opacity) override;
    void SetOnEnter(PageTransitionEventFunc&& handler) override;
    void SetOnExit(PageTransitionEventFunc&& handler) override;
    void CreateTransition(PageTransitionType type, const PageTransitionOption& option) override;
    void Create() override;
    void Pop() override;

private:
    static RefPtr<PageTransition> GetPageTransition();
};
} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JSVIEW_MODELS_PAGE_TRANSITION_MODEL_IMPL_H