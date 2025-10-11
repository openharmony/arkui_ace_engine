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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_STATIC_BRIDGE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_STATIC_BRIDGE_H

#include <functional>
#include <optional>

#include "base/geometry/calc_dimension.h"
#include "base/geometry/dimension.h"
#include "base/memory/referenced.h"
#include "core/components_ng/pattern/container_modal/enhance/container_modal_pattern_enhance.h"
#include "core/components_ng/pattern/container_modal/static/container_modal_static_pattern.h"
namespace OHOS::Ace::NG {

class ContainerModalStaticBridge {
public:
    // js->native
    static void CallNative(const std::string& eventName, const std::string& param);

private:
    static RefPtr<ContainerModalStaticPattern> GetContainerModalPattern();

    static void OnMaxBtnClick(const std::string& eventName, const std::string& param);
    static void OnMinBtnClick(const std::string& eventName, const std::string& param);
    static void OnCloseBtnClick(const std::string& eventName, const std::string& param);
    static void OnLeftSplitClick(const std::string& eventName, const std::string& param);
    static void OnRightSplitClick(const std::string& eventName, const std::string& param);
    static void AddButtonPointLightAnim(const std::string& eventName, const std::string& param);
    static void CallButtonsRectChange(const std::string& eventName, const std::string& param);
    static void CallMenuWidthChange(const std::string& eventName, const std::string& param);
    static void CallWindowNative(const std::string& eventName, const std::string& param);
    static const std::map<std::string, std::function<void(const std::string& eventName, const std::string& param)>>
        nativeFuncMap_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_STATIC_BRIDGE_H
