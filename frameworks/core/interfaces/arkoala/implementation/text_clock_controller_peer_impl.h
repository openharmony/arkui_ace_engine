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
#pragma once

#include <optional>
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/text_clock/text_clock_controller.h"

struct TextClockControllerPeer {
public:
    TextClockControllerPeer() = default;

    void SetController(const OHOS::Ace::RefPtr<OHOS::Ace::TextClockController>& controller)
    {
        controller_ = controller;
    }

    void StartImpl()
    {
        if (controller_) {
            controller_->Start();
        }
    }

    void StopImpl()
    {
        if (controller_) {
            controller_->Stop();
        }
    }

private:
    OHOS::Ace::RefPtr<OHOS::Ace::TextClockController> controller_ = nullptr;
};