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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_OSAL_SYSTEM_BAR_STYLE_OHOS_H
#define FOUNDATION_ACE_ADAPTER_OHOS_OSAL_SYSTEM_BAR_STYLE_OHOS_H

#include <map>

#include "base/system_bar/system_bar_style.h"

#include "wm/window.h"
#include "wm/wm_common.h"

namespace OHOS::Ace {
class SystemBarStyleOhos : public SystemBarStyle {
    DECLARE_ACE_TYPE(SystemBarStyleOhos, SystemBarStyle)
public:
    SystemBarStyleOhos() = default;
    ~SystemBarStyleOhos() = default;

    static RefPtr<SystemBarStyleOhos> GetCurrentSystemBarStyle(const sptr<Rosen::Window>& window);
    static void SetSystemBarStyle(const sptr<Rosen::Window>& window, const RefPtr<SystemBarStyle>& style);

private:
    friend class SystemBarStyle;
    std::map<Rosen::WindowType, Rosen::SystemBarPropertyFlag> propertyFlags_;
    std::map<Rosen::WindowType, Rosen::SystemBarProperty> properties_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_ADAPTER_OHOS_OSAL_SYSTEM_BAR_STYLE_OHOS_H
