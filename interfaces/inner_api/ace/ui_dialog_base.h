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

#ifndef OHOS_ACE_UI_DIALOG_BASE_H
#define OHOS_ACE_UI_DIALOG_BASE_H

#include <functional>
#include <string>

#include "refbase.h"

namespace OHOS::Ace {
class IDialogCallback;

class UIDialogBase {
public:
    UIDialogBase() = default;
    virtual ~UIDialogBase() = default;

    // show system dialog
    virtual void ShowDialog(
        const std::string& name,
        const std::string& params,
        uint32_t windowType,
        int x,
        int y,
        int width,
        int height,
        const std::function<void(int32_t, const std::string&, const std::string&)>& dialogCallback,
        int32_t dialogId) = 0;

    // update system dialog
    virtual void UpdateDialog(int id, const std::string& data) = 0;

    // cancel system dialog
    virtual void CancelDialog(int32_t id, const std::function<void()>& destroyCallback) = 0;
};
}

#endif