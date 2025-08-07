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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UI_EXTENSION_TOUCH_DELEGATE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UI_EXTENSION_TOUCH_DELEGATE_H

#include <optional>

#include "core/common/event_manager.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_pattern.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT UIExtensionTouchDelegate : public TouchDelegate {
    DECLARE_ACE_TYPE(UIExtensionTouchDelegate, TouchDelegate);

public:
    UIExtensionTouchDelegate(const WeakPtr<UIExtensionPattern>& pattern);
    ~UIExtensionTouchDelegate() override;

    void DelegateTouchEvent(const TouchEvent& point) override;
private:
    WeakPtr<UIExtensionPattern> pattern_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UI_EXTENSION_TOUCH_DELEGATE_H
