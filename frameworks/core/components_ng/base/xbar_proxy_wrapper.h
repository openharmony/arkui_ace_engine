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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XBAR_PROXY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XBAR_PROXY_H

#include <functional>
#include <utility>

#include "ui/base/ace_type.h"

#include "base/image/pixel_map.h"
#include "core/components_ng/base/ui_node.h"


namespace OHOS::Ace::NG {
struct XbarFuncInfo {
    std::function<void()> onWindowFocusedFunc;
    std::function<void()> onWindowUnFocusedFunc;
    std::function<void(const std::string&)> setAppTitleFunc;
    std::function<void(void*)> setAppIconFunc;
    std::function<void(const std::string&, const std::string&)> setCustomCallbackFunc;
};
enum class XbarFuncType {
    WINDOW_FOCUS = 0,
    WINDOW_UN_FOCUSWINDOW_UN_FOCUS,
    SET_APP_TITLE,
    SET_APP_ICON,
    SET_CUSTOM_CALLBACK,
};
class ACE_FORCE_EXPORT XbarComponent : public AceType {
    DECLARE_ACE_TYPE(XbarComponent, AceType);

public:
    XbarComponent(intptr_t pointer) : xBarPoint(pointer) {}
    intptr_t GetUINodePointFromXbar()
    {
        return xBarPoint;
    }

    void FireWindowFocusedFunc();

    void FireWindowUnFocusedFunc();

    void FireSetAppTitleFunc(const std::string& content);

    void FireSetSetAppIconFunc(const RefPtr<PixelMap>& icon);

    void FireSetCustomCallbackFunc(const std::string& eventName, const std::string& param);

    void SetOnWindowFocusedFunc(std::function<void()>&& onWindowFocusedFunc);

    void SetOnWindowUnFocusedFunc(std::function<void()>&& onWindowUnFocusedFunc);

    void SetSetAppTitleFunc(std::function<void(const std::string&)>&& setAppTitleFunc);

    void SetSetAppIconFunc(std::function<void(void*)>&& setAppIconFunc);

    void SetSetCustomCallbackFunc(std::function<void(const std::string&, const std::string&)>&& setCustomCallbackFunc);

private:
    intptr_t xBarPoint;
    std::function<void()> onWindowFocusedFunc;
    std::function<void()> onWindowUnfocusedFunc;
    std::function<void(const std::string& content)> setAppTitleFunc;
    std::function<void(void* icon)> setAppIconFunc;
    std::function<void(const std::string& eventName, const std::string& param)> setCustomCallbackFunc;
};
class ACE_EXPORT XbarProxyWrapper : public AceType {
    DECLARE_ACE_TYPE(XbarProxyWrapper, AceType);

public:
    ACE_FORCE_EXPORT static XbarProxyWrapper* GetInstance();
    virtual ~XbarProxyWrapper() = default;
    RefPtr<XbarComponent> CreateXBarComponent(const int32_t& xbarType, const int32_t& instanceId);
    void SetOnWindowFocusedFunc(int64_t ptr, std::function<void()>&& onWindowFocusedFun);
    void SetOnWindowUnFocusedFunc(int64_t ptr, std::function<void()>&& onWindowUnFocusedFun);
    void SetSetAppTitleFunc(int64_t ptr, std::function<void(const std::string&)>&& setAppTitleFunc);
    void SetSetAppIconFunc(int64_t ptr, std::function<void(void*)>&& setAppIconFunc);
    void SetSetCustomCallbackFunc(
        int64_t ptr, std::function<void(const std::string&, const std::string&)>&& setCustomCallbackFunc);
    void InitXBarCreator(std::function<int64_t(const int32_t&, const int32_t&)>&& componentCreateFunc_);

private:
    std::function<int64_t(const int32_t&, const int32_t&)> componentCreateFunc_;
    std::unordered_map<int64_t, XbarFuncInfo> xbarFuncMap_;
    XbarProxyWrapper() = default;
    ACE_DISALLOW_COPY_AND_MOVE(XbarProxyWrapper);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XBAR_PROXY_H