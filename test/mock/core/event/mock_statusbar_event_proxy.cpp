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
#include "core/common/container.h"
#include "core/event/statusbar/statusbar_event_proxy.h"

namespace OHOS::Ace {
class MockStatusBarEventProxy : public StatusBarEventProxy {
public:
    MockStatusBarEventProxy();
    ~MockStatusBarEventProxy() override;

    void Register(const WeakPtr<StatusBarClickListener>& listener) override;
    void UnRegister(const WeakPtr<StatusBarClickListener>& listener) override;
    void OnStatusBarClick() override {}
    std::set<std::pair<WeakPtr<StatusBarClickListener>, int32_t>> GetStatusBarClickListener() override;

private:
    std::set<std::pair<WeakPtr<StatusBarClickListener>, int32_t>> listeners_;
};

MockStatusBarEventProxy::MockStatusBarEventProxy() = default;
MockStatusBarEventProxy::~MockStatusBarEventProxy() = default;

std::unique_ptr<StatusBarEventProxy> StatusBarEventProxy::instance_;
std::mutex StatusBarEventProxy::mutex_;
StatusBarEventProxy* StatusBarEventProxy::GetInstance()
{
    if (!instance_) {
        std::scoped_lock lock(mutex_);
        if (!instance_) {
            instance_ = std::make_unique<MockStatusBarEventProxy>();
        }
    }
    return instance_.get();
}
std::set<std::pair<WeakPtr<StatusBarClickListener>, int32_t>> MockStatusBarEventProxy::GetStatusBarClickListener()
{
    return listeners_;
}
void MockStatusBarEventProxy::Register(const WeakPtr<StatusBarClickListener>& listener)
{
    listeners_.insert({ listener, Container::CurrentId() });
}

void MockStatusBarEventProxy::UnRegister(const WeakPtr<StatusBarClickListener>& listener)
{
    if (listeners_.empty()) {
        return;
    }
    for (auto it = listeners_.begin(); it != listeners_.end(); ++it) {
        if (it->first == listener) {
            listeners_.erase(it);
            break;
        }
    }
}
} // namespace OHOS::Ace
