/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UI_EXTENSION_AVOID_LISTENER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UI_EXTENSION_AVOID_LISTENER_H

#include "core/common/event_manager.h"
#include "core/components_ng/manager/avoid_info/avoid_info_manager.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_pattern.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT UIExtensionAvoidListener : public IAvoidInfoListener {
    DECLARE_ACE_TYPE(UIExtensionAvoidListener, IAvoidInfoListener);

public:
    UIExtensionAvoidListener(const WeakPtr<UIExtensionPattern>& pattern);
    ~UIExtensionAvoidListener() override;

    void OnAvoidInfoChange(const ContainerModalAvoidInfo& info) override;
    void RegisterAvoidInfoChangeListener(int32_t instanceId);
    void UnRegisterAvoidInfoChangeListener();
private:
    WeakPtr<UIExtensionPattern> pattern_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UI_EXTENSION_AVOID_LISTENER_H
