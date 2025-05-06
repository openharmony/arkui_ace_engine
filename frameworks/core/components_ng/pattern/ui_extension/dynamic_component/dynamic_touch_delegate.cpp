/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/ui_extension/dynamic_component/dynamic_touch_delegate.h"

#include "base/utils/utils.h"
#include "core/components_ng/pattern/ui_extension/dynamic_component/dynamic_pattern.h"
#include "core/pipeline/pipeline_context.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "pointer_event.h"

namespace OHOS::Ace::NG {
namespace {
}
DynamicTouchDelegate::DynamicTouchDelegate(const WeakPtr<DynamicPattern>& pattern)
    : pattern_(pattern)
{}

DynamicTouchDelegate::~DynamicTouchDelegate()
{}

void DynamicTouchDelegate::DelegateTouchEvent(const TouchEvent& point)
{
    auto dynamicPattern = pattern_.Upgrade();
    CHECK_NULL_VOID(dynamicPattern);
    auto pointEvent = point.GetTouchEventPointerEvent();
    CHECK_NULL_VOID(pointEvent);
    bool ret = dynamicPattern->HandleTouchEvent(pointEvent);
    if (!ret) {
        TAG_LOGW(AceLogTag::ACE_DYNAMIC_COMPONENT, "DC HandleTouchEvent failed, "
            "pointEvent: %{public}s", pointEvent->ToString().c_str());
    }
}
} // namespace OHOS::Ace::NG
