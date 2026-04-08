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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_OSAL_IME_EXTRA_CONFIG_OHOS_H
#define FOUNDATION_ACE_ADAPTER_OHOS_OSAL_IME_EXTRA_CONFIG_OHOS_H

#include "core/common/ime/ime_extra_config.h"
#include "extra_config.h"

namespace OHOS::Ace {

class IMEExtraConfigOHOS : public IMEExtraConfig {
    DECLARE_ACE_TYPE(IMEExtraConfigOHOS, IMEExtraConfig);

public:
    explicit IMEExtraConfigOHOS(std::shared_ptr<OHOS::MiscServices::ExtraConfig> extraConfig)
        : extraConfig_(extraConfig) {};
    ~IMEExtraConfigOHOS() override = default;

    void* GetRawExtraConfig() const override;

private:
    std::shared_ptr<OHOS::MiscServices::ExtraConfig> extraConfig_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_OHOS_OSAL_IME_EXTRA_CONFIG_OHOS_H