/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NAVIGATION_BAR_RENDER_NAVIGATION_CONTAINER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NAVIGATION_BAR_RENDER_NAVIGATION_CONTAINER_H

#include "core/animation/animation.h"
#include "core/animation/animator.h"
#include "core/components/navigation_bar/render_collapsing_navigation_bar.h"
#include "core/gestures/raw_recognizer.h"
#include "core/pipeline/base/related_node.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace {

class RenderNavigationContainer : public RenderNode, public RelatedContainer {
    DECLARE_ACE_TYPE(RenderNavigationContainer, RenderNode, RelatedContainer);

public:
    static RefPtr<RenderNode> Create();
    void Update(const RefPtr<Component>& component) override {};
    void PerformLayout() override;
    void OnRelatedStart() override;
    void OnRelatedPreScroll(const Offset& delta, Offset& consumed) override;
    void OnRelatedScroll(const Offset& delta, Offset& consumed) override;
    void OnRelatedEnd() override;
    void SetCollapsingNavigationBar(const RefPtr<RenderCollapsingNavigationBar>& collapsingNavigationBar)
    {
        collapsingNavigationBar_ = collapsingNavigationBar;
    }

private:
    RefPtr<RenderCollapsingNavigationBar> collapsingNavigationBar_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NAVIGATION_BAR_RENDER_NAVIGATION_CONTAINER_H
