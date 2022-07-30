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

#ifndef OHOS_ACE_UISERVICE_DIALOG_INTERFACE_H
#define OHOS_ACE_UISERVICE_DIALOG_INTERFACE_H

#include <string>

#include "iremote_broker.h"

#include "base/utils/macros.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT IUiServiceDialog : public OHOS::IRemoteBroker {
public:
    DECLARE_INTERFACE_DESCRIPTOR(u"ohos.ace.UiserviceDialog");

    static constexpr int32_t SHOW_DIALOG = 0;
    static constexpr int32_t UPDATE_DIALOG = 1;
    static constexpr int32_t CANCEL_DIALOG = 2;

    virtual int32_t ShowDialog(
        const std::string& name,
        const std::string& params,
        uint32_t windowType,
        int x,
        int y,
        int width,
        int height,
        int32_t dialogId) = 0;

    virtual int32_t UpdateDialog(int32_t dialogId, const std::string& data) = 0;

    virtual int32_t CancelDialog(int32_t dialogId) = 0;
};
}

#endif