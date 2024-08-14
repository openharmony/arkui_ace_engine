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
#include "test/mock/core/render/mock_render_context.h"

#include "test/mock/core/render/mock_animation_manager.h"
#include "test/mock/core/render/mock_animation_proxy.h"

#include "core/components_ng/base/modifier.h"

namespace OHOS::Ace::NG {
void MockRenderContext::AttachNodeAnimatableProperty(RefPtr<NodeAnimatablePropertyBase> modifier)
{
    if (!MockAnimationManager::Enabled()) {
        return;
    }
    if (auto prop = DynamicCast<AnimatableProperty<float>>(modifier->GetProperty()); prop) {
        MockAnimationProxy<float>::GetInstance().RegisterProperty(prop, prop->Get());
        // setup proxy for Set, Get, GetStageValue
        prop->SetUpCallbacks(
            [weak = WeakPtr(prop)]() { return MockAnimationProxy<float>::GetInstance().GetEndValue(weak.Upgrade()); },
            [weak = WeakPtr(prop)](
                float value) { MockAnimationProxy<float>::GetInstance().RecordPropChange(weak.Upgrade(), value); },
            [weak = WeakPtr(prop)]() {
                return MockAnimationProxy<float>::GetInstance().GetStagingValue(weak.Upgrade());
            });
    }
}

} // namespace OHOS::Ace::NG