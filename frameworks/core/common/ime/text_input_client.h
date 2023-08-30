/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_IME_TEXT_INPUT_CLIENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_IME_TEXT_INPUT_CLIENT_H

#include "base/memory/ace_type.h"
#include "core/common/ime/text_input_action.h"
#include "core/common/ime/text_editing_value.h"

namespace OHOS::Ace {

class TextInputClient : public virtual AceType {
    DECLARE_ACE_TYPE(TextInputClient, AceType);

public:
    // Requests that this client update its editing state to the given value.
    virtual void UpdateEditingValue(
        const std::shared_ptr<TextEditingValue>& value, bool needFireChangeEvent = true) = 0;

    // Requests that this client perform the given action.
    virtual void PerformAction(TextInputAction action, bool forceCloseKeyboard = false) = 0;
 
#if defined(IOS_PLATFORM)
    virtual const TextEditingValue& GetInputEditingValue() const {
        static TextEditingValue value;
        return value;
    };
#endif
    virtual void UpdateInputFilterErrorText(const std::string& errorText) {};

    // Requests that this client Y point.
    virtual double GetEditingBoxY() const { return 0.0; };
    virtual double GetEditingBoxTopY() const { return 0.0; };
    virtual bool GetEditingBoxModel() const { return false; };

};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_IME_TEXT_INPUT_CLIENT_H
