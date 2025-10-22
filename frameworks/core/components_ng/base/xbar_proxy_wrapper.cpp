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
#include "core/components_ng/base/xbar_proxy_wrapper.h"

#include <memory>
#include <shared_mutex>
#include <utility>

#include "base/log/log_wrapper.h"

namespace OHOS::Ace::NG {

XbarProxyWrapper* XbarProxyWrapper::GetInstance()
{
    static XbarProxyWrapper instance;
    return &instance;
}

void XbarProxyWrapper::InitXBarCreator(std::function<int64_t(const int32_t&, const int32_t&)>&& aniComponentCreateFunc_)
{
    componentCreateFunc_ = std::move(aniComponentCreateFunc_);
}

void XbarProxyWrapper::SetOnWindowFocusedFunc(int64_t ptr, std::function<void()>&& onWindowFocusedFun)
{
    xbarFuncMap_[ptr].onWindowFocusedFunc = std::move(onWindowFocusedFun);
}

void XbarProxyWrapper::SetOnWindowUnFocusedFunc(int64_t ptr, std::function<void()>&& onWindowUnFocusedFun)
{
    xbarFuncMap_[ptr].onWindowUnFocusedFunc = std::move(onWindowUnFocusedFun);
}

void XbarProxyWrapper::SetSetAppIconFunc(int64_t ptr, std::function<void(void*)>&& setAppIconFunc)
{
    xbarFuncMap_[ptr].setAppIconFunc = std::move(setAppIconFunc);
}

void XbarProxyWrapper::SetSetAppTitleFunc(int64_t ptr, std::function<void(const std::string&)>&& setAppTitleFunc)
{
    xbarFuncMap_[ptr].setAppTitleFunc = std::move(setAppTitleFunc);
}

void XbarProxyWrapper::SetSetCustomCallbackFunc(
    int64_t ptr, std::function<void(const std::string&, const std::string&)>&& setCustomCallbackFunc)
{
    xbarFuncMap_[ptr].setCustomCallbackFunc = std::move(setCustomCallbackFunc);
}

RefPtr<XbarComponent> XbarProxyWrapper::CreateXBarComponent(const int32_t& xbarType, const int32_t& instanceID)
{
    if (!componentCreateFunc_) {
        TAG_LOGE(AceLogTag::ACE_APPBAR, "component create func is empty");
        return nullptr;
    }
    int64_t componentPointLong = componentCreateFunc_(xbarType, instanceID);
    auto xbarComponent = AceType::MakeRefPtr<XbarComponent>(static_cast<intptr_t>(componentPointLong));
    auto xbarFuncInfoIter = xbarFuncMap_.find(componentPointLong);
    if (xbarFuncInfoIter != xbarFuncMap_.end()) {
        xbarComponent->SetOnWindowFocusedFunc(std::move(xbarFuncInfoIter->second.onWindowFocusedFunc));
        xbarComponent->SetOnWindowUnFocusedFunc(std::move(xbarFuncInfoIter->second.onWindowUnFocusedFunc));
        xbarComponent->SetSetAppTitleFunc(std::move(xbarFuncInfoIter->second.setAppTitleFunc));
        xbarComponent->SetSetAppIconFunc(std::move(xbarFuncInfoIter->second.setAppIconFunc));
        xbarComponent->SetSetCustomCallbackFunc(std::move(xbarFuncInfoIter->second.setCustomCallbackFunc));
        XbarProxyWrapper::GetInstance()->xbarFuncMap_.erase(componentPointLong);
    }
    return xbarComponent;
}

void XbarComponent::FireWindowFocusedFunc()
{
    if (!onWindowFocusedFunc) {
        TAG_LOGW(AceLogTag::ACE_APPBAR, "onWindowFocusedFunc not implement");
        return;
    }
    onWindowFocusedFunc();
    TAG_LOGI(AceLogTag::ACE_APPBAR, "onWindowFocusedFunc called");
}

void XbarComponent::FireWindowUnFocusedFunc()
{
    if (!onWindowUnfocusedFunc) {
        TAG_LOGW(AceLogTag::ACE_APPBAR, "onWindowUnfocusedFunc not implement");
        return;
    }
    onWindowUnfocusedFunc();
    TAG_LOGI(AceLogTag::ACE_APPBAR, "onWindowUnfocusedFunc called");
}

void XbarComponent::FireSetAppTitleFunc(const std::string& content)
{
    if (!setAppTitleFunc) {
        TAG_LOGW(AceLogTag::ACE_APPBAR, "setAppTitleFunc not implement");
        return;
    }
    setAppTitleFunc(content);
    TAG_LOGI(AceLogTag::ACE_APPBAR, "setAppTitleFunc called");
}

void XbarComponent::FireSetSetAppIconFunc(const RefPtr<PixelMap>& icon)
{
    if (!setAppIconFunc) {
        TAG_LOGW(AceLogTag::ACE_APPBAR, "setAppIconFunc not implement");
        return;
    }
    auto pixelMapSharedPtr = icon->GetPixelMapSharedPtr();
    setAppIconFunc(&pixelMapSharedPtr);
    TAG_LOGI(AceLogTag::ACE_APPBAR, "setAppIconFunc called");
}

void XbarComponent::FireSetCustomCallbackFunc(const std::string& eventName, const std::string& param)
{
    if (!setCustomCallbackFunc) {
        TAG_LOGW(AceLogTag::ACE_APPBAR, "setCustomCallbackFunc not implement");
        return;
    }
    setCustomCallbackFunc(eventName, param);
    TAG_LOGI(AceLogTag::ACE_APPBAR, "setCustomCallbackFunc called");
}

void XbarComponent::SetOnWindowFocusedFunc(std::function<void()>&& onWindowFocusedFunc)
{
    this->onWindowFocusedFunc = std::move(onWindowFocusedFunc);
    if (this->onWindowFocusedFunc) {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "component init onWindowFocusedFunc");
    }
}
void XbarComponent::SetOnWindowUnFocusedFunc(std::function<void()>&& onWindowUnFocusedFunc)
{
    this->onWindowUnfocusedFunc = std::move(onWindowUnFocusedFunc);
    if (this->onWindowUnfocusedFunc) {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "component init onWindowUnFocusedFunc");
    }
}
void XbarComponent::SetSetAppTitleFunc(std::function<void(const std::string&)>&& setAppTitleFunc)
{
    this->setAppTitleFunc = std::move(setAppTitleFunc);
    if (this->setAppTitleFunc) {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "component init setAppTitleFunc");
    }
}
void XbarComponent::SetSetAppIconFunc(std::function<void(void*)>&& setAppIconFunc)
{
    this->setAppIconFunc = std::move(setAppIconFunc);
    if (this->setAppIconFunc) {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "component init setAppIconFunc");
    }
}
void XbarComponent::SetSetCustomCallbackFunc(
    std::function<void(const std::string&, const std::string&)>&& setCustomCallbackFunc)
{
    this->setCustomCallbackFunc = std::move(setCustomCallbackFunc);
    if (this->setCustomCallbackFunc) {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "component init setCustomCallbackFunc");
    }
}
} // namespace OHOS::Ace::NG