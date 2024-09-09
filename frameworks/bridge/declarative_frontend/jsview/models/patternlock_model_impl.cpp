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

#include "bridge/declarative_frontend/jsview/models/patternlock_model_impl.h"

#include <utility>

#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components_v2/pattern_lock/pattern_lock_component.h"
#include "core/components_v2/pattern_lock/pattern_lock_theme.h"

namespace OHOS::Ace::Framework {

RefPtr<V2::PatternLockController> PatternLockModelImpl::Create()
{
    auto lock = AceType::MakeRefPtr<V2::PatternLockComponent>();
    auto lockTheme = JSViewAbstract::GetTheme<V2::PatternLockTheme>();
    if (!lockTheme) {
        LOGE("Get PatternLock theme error");
    } else {
        lock->SetRegularColor(lockTheme->GetRegularColor());
        lock->SetSelectedColor(lockTheme->GetSelectedColor());
        lock->SetActiveColor(lockTheme->GetActiveColor());
        lock->SetPathColor(lockTheme->GetPathColor());
    }

    ViewStackProcessor::GetInstance()->Push(lock);
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    auto flexItem = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
    Dimension defaultSideLength { V2::DEFAULT_SIDE_LENGTH, DimensionUnit::VP };
    box->SetMinWidth(defaultSideLength);
    box->SetMinHeight(defaultSideLength);
    box->SetMaxHeight(defaultSideLength);
    box->SetMaxWidth(defaultSideLength);
    flexItem->SetMinWidth(defaultSideLength);
    flexItem->SetMinHeight(defaultSideLength);
    flexItem->SetMaxWidth(defaultSideLength);
    flexItem->SetMaxHeight(defaultSideLength);

    return lock->GetPatternLockController();
}

void PatternLockModelImpl::SetPatternComplete(std::function<void(const BaseEventInfo* info)>&& onComplete)
{
    auto lock = AceType::DynamicCast<V2::PatternLockComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(lock);
    lock->SetPatternCompleteEvent(EventMarker(std::move(onComplete)));
}

void PatternLockModelImpl::SetSelectedColor(const Color& selectedColor)
{
    auto lock = AceType::DynamicCast<V2::PatternLockComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(lock);
    lock->SetSelectedColor(selectedColor);
}

void PatternLockModelImpl::SetAutoReset(bool isAutoReset)
{
    auto lock = AceType::DynamicCast<V2::PatternLockComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(lock);
    lock->SetAutoReset(isAutoReset);
}

void PatternLockModelImpl::SetPathColor(const Color& pathColor)
{
    auto lock = AceType::DynamicCast<V2::PatternLockComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(lock);
    lock->SetPathColor(pathColor);
}

void PatternLockModelImpl::SetActiveColor(const Color& activeColor)
{
    auto lock = AceType::DynamicCast<V2::PatternLockComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(lock);
    lock->SetActiveColor(activeColor);
}

void PatternLockModelImpl::SetRegularColor(const Color& regularColor)
{
    auto lock = AceType::DynamicCast<V2::PatternLockComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(lock);
    lock->SetRegularColor(regularColor);
}

void PatternLockModelImpl::SetCircleRadius(const Dimension& radius)
{
    auto lock = AceType::DynamicCast<V2::PatternLockComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(lock);
    lock->SetCircleRadius(radius);
}

void PatternLockModelImpl::SetSideLength(const Dimension& sideLength)
{
    auto lock = AceType::DynamicCast<V2::PatternLockComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(lock);
    lock->SetSideLength(sideLength);
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    box->SetMinWidth(sideLength);
    box->SetMinHeight(sideLength);
    box->SetMaxWidth(sideLength);
    box->SetMaxHeight(sideLength);
    auto flexItem = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
    flexItem->SetMinWidth(sideLength);
    flexItem->SetMinHeight(sideLength);
    flexItem->SetMaxWidth(sideLength);
    flexItem->SetMaxHeight(sideLength);
}

void PatternLockModelImpl::SetStrokeWidth(const Dimension& lineWidth)
{
    auto component =
        AceType::DynamicCast<V2::PatternLockComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(component);
    if (GreatOrEqual(lineWidth.Value(), 0.0)) {
        component->SetStrokeWidth(lineWidth);
    } else {
        component->SetStrokeWidth(0.0_vp);
    }
}

void PatternLockModelImpl::SetActiveCircleColor(const Color& activeCircleColor) {};
void PatternLockModelImpl::SetActiveCircleRadius(const Dimension& activeCircleRadius) {};
void PatternLockModelImpl::SetEnableWaveEffect(bool enableWaveEffect) {};
} // namespace OHOS::Ace::Framework
