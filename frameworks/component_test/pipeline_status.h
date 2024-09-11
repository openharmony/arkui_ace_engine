/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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

#ifndef OHOS_ACE_COMPONENT_TEST_PIPELINE_STATUS_H
#define OHOS_ACE_COMPONENT_TEST_PIPELINE_STATUS_H

namespace OHOS::Ace::ComponentTest {

class PipelineStatusHolder {
public:
    void Update()
    {
        ++vsyncCountRealTime_;
    }

private:
    friend class IdleMonitorThread;
    friend class IdleWatcher;

    uint32_t vsyncCountRealTime_ = 0;
    uint32_t vsyncCountLastCheck_ = 0;
    uint8_t idleCounter_ = 0;
    uint8_t longOptCounter_ = 0;
    uint8_t idleCheckRetry_;

    bool Check()
    {
        uint8_t vsyncCount = vsyncCountLastCheck_;
        vsyncCountLastCheck_ = vsyncCountRealTime_;
        if (longOptCounter_ == 0) {
            ++idleCheckRetry_;
            return vsyncCountRealTime_ == vsyncCount;
        } else {
            idleCheckRetry_ = 0;
            return false;
        }
    }

    void IncreaseLongOpt()
    {
        ++longOptCounter_;
    }

    void DecreaseLongOpt()
    {
        if (longOptCounter_ > 0) {
            --longOptCounter_;
        }
    }

    void IdleCounterAdd()
    {
        ++idleCounter_;
    }

    void IdleCounterClear()
    {
        idleCounter_ = 0;
    }

    bool IdleCounterReached(uint8_t num) const
    {
        return idleCounter_ >= num;
    }

    void RetryCounterClear()
    {
        idleCheckRetry_ = 0;
    }

    bool RetryCounterReached(uint8_t num) const
    {
        return idleCheckRetry_ >= num;
    }
};

// extern g_pipelineStatusHolder;

extern void UpdatePipelineStatus();

} // namespace OHOS::Ace::ComponentTest

#endif // OHOS_ACE_COMPONENT_TEST_PIPELINE_STATUS_H
