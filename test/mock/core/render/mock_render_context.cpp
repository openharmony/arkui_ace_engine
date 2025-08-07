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

#include "test/mock/core/animation/mock_animation_manager.h"
#include "test/mock/core/animation/mock_animation_proxy.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/modifier.h"

namespace OHOS::Ace::NG {
namespace {
void InitProp(const RefPtr<PropertyBase>& propBase)
{
    if (auto prop = AceType::DynamicCast<AnimatablePropertyFloat>(propBase); prop) {
        MockAnimationProxy<float>::GetInstance().RegisterProperty(prop, prop->Get());
        // setup proxy for Set, Get, GetStageValue
        prop->SetUpCallbacks(
            [weak = WeakPtr(prop)]() { return MockAnimationProxy<float>::GetInstance().GetValue(weak.Upgrade()); },
            [weak = WeakPtr(prop)](
                float value) { MockAnimationProxy<float>::GetInstance().RecordPropChange(weak, value); },
            [weak = WeakPtr(prop)]() { return MockAnimationProxy<float>::GetInstance().GetEndValue(weak.Upgrade()); });
    }

    if (auto prop = AceType::DynamicCast<AnimatablePropertyOffsetF>(propBase); prop) {
        MockAnimationProxy<OffsetF>::GetInstance().RegisterProperty(prop, prop->Get());
        prop->SetUpCallbacks(
            [weak = WeakPtr(prop)]() { return MockAnimationProxy<OffsetF>::GetInstance().GetValue(weak.Upgrade()); },
            [weak = WeakPtr(prop)](
                OffsetF value) { MockAnimationProxy<OffsetF>::GetInstance().RecordPropChange(weak, value); },
            [weak = WeakPtr(prop)]() {
                return MockAnimationProxy<OffsetF>::GetInstance().GetEndValue(weak.Upgrade());
            });
    }
    /* add code for other types */
}
} // namespace

void MockRenderContext::AttachNodeAnimatableProperty(RefPtr<NodeAnimatablePropertyBase> modifier)
{
    if (!MockAnimationManager::Enabled()) {
        return;
    }
    InitProp(modifier->GetProperty());
}

void MockRenderContext::CancelTranslateXYAnimation()
{
    CHECK_NULL_VOID(translateXY_);
    translateXY_->Set(translateXY_->Get());
}
OffsetF MockRenderContext::GetTranslateXYProperty()
{
    if (!translateXY_) {
        translateXY_ = MakeRefPtr<AnimatablePropertyOffsetF>(OffsetF());
        InitProp(translateXY_);
    }
    return translateXY_->Get();
}
void MockRenderContext::UpdateTranslateInXY(const OffsetF& offset)
{
    if (!translateXY_) {
        translateXY_ = MakeRefPtr<AnimatablePropertyOffsetF>(OffsetF());
        InitProp(translateXY_);
    }
    translateXY_->Set(offset);
}
} // namespace OHOS::Ace::NG