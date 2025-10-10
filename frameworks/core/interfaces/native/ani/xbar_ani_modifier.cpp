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
#include "xbar_ani_modifier.h"

// #include "core/components_ng/base/xbar_proxy_wrapper.h"
// #include "core/components_ng/pattern/container_modal/static/container_modal_static_bridge.h"
namespace OHOS::Ace::NG {
static void setXBarComponentCreateFunc(std::function<int64_t(const int32_t&, const int32_t&)>&& fn)
{
    // NG::XbarProxyWrapper::GetInstance()->InitXBarCreator(std::move(fn));
}
static void setOnWindowFocusedFunc(int64_t ptr, std::function<void()>&& fn)
{
    // NG::XbarProxyWrapper::GetInstance()->SetOnWindowFocusedFunc(ptr, std::move(fn));
}
static void setOnWindowUnFocusedFunc(int64_t ptr, std::function<void()>&& fn)
{
    // NG::XbarProxyWrapper::GetInstance()->SetOnWindowUnFocusedFunc(ptr, std::move(fn));
}
static void setSetAppTitleFunc(int64_t ptr, std::function<void(const std::string&)>&& fn)
{
    // NG::XbarProxyWrapper::GetInstance()->SetSetAppTitleFunc(ptr, std::move(fn));
}
static void setSetAppIconFunc(int64_t ptr, std::function<void(void*)>&& fn)
{
    // NG::XbarProxyWrapper::GetInstance()->SetSetAppIconFunc(ptr, std::move(fn));
}
static void SetSetCustomCallbackFunc(int64_t ptr, std::function<void(const std::string&, const std::string&)>&& fn)
{
    // NG::XbarProxyWrapper::GetInstance()->SetSetCustomCallbackFunc(ptr, std::move(fn));
}

static void callNative(const int32_t& xBarType, const std::string callType, const std::string message)
{
    // NG::ContainerModalStaticBridge::CallNative(callType, message);
}
const ArkUIAniXBarModifier* GetXBarAniModifier()
{
    static const ArkUIAniXBarModifier impl = {
        .setComponentCreateFunc = OHOS::Ace::NG::setXBarComponentCreateFunc,
        .setOnWindowFocusedFunc = OHOS::Ace::NG::setOnWindowFocusedFunc,
        .setOnWindowUnFocusedFunc = OHOS::Ace::NG::setOnWindowUnFocusedFunc,
        .setSetAppTitleFunc = OHOS::Ace::NG::setSetAppTitleFunc,
        .setSetAppIconFunc = OHOS::Ace::NG::setSetAppIconFunc,
        .setSetCustomCallbackFunc = OHOS::Ace::NG::SetSetCustomCallbackFunc,
        .callNative = OHOS::Ace::NG::callNative,
    };
    return &impl;
}
} // namespace OHOS::Ace::NG