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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_CPP_ACE_ROSEN_SYNC_TASK_H
#define FOUNDATION_ACE_ADAPTER_OHOS_CPP_ACE_ROSEN_SYNC_TASK_H

#include "render_service_client/core/ui/rs_ui_director.h"
#include "transaction/rs_transaction_proxy.h"

namespace OHOS::Ace::Platform {

class AceRosenSyncTask : public Rosen::RSSyncTask {
public:
    explicit AceRosenSyncTask(std::function<void()>&& task, unsigned long long timeoutNS = 30e9)
        : Rosen::RSSyncTask(timeoutNS), task_(std::move(task))
    {}
    virtual ~AceRosenSyncTask() = default;

#ifdef ROSEN_OHOS
    bool CheckHeader(Parcel& parcel) const override
    {
        return true;
    }

    bool ReadFromParcel(Parcel& parcel) override
    {
        return true;
    }

    bool Marshalling(Parcel& parcel) const override
    {
        return true;
    }
#endif // ROSEN_OHOS

    void Process(Rosen::RSContext& context) override
    {
        if (task_) {
            task_();
        }
    }

private:
    std::function<void()> task_;
};
} // namespace OHOS::Ace::Platform

#endif // FOUNDATION_ACE_ADAPTER_OHOS_CPP_ACE_ROSEN_SYNC_TASK_H