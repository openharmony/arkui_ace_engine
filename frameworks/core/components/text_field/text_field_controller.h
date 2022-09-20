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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_FIELD_TEXT_FIELD_CONTROLLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_FIELD_TEXT_FIELD_CONTROLLER_H

#include <functional>
#include <utility>

#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"

namespace OHOS::Ace {

class Element;

class ACE_EXPORT TextFieldController : public TextFieldControllerBase {
    DECLARE_ACE_TYPE(TextFieldController, TextFieldControllerBase);

public:
    void SetHandler(WeakPtr<Element> element)
    {
        element_ = std::move(element);
    }

    void Focus(bool focus) override;

    void ShowError(const std::string& errorText) override;
    void Delete() override;
    void Insert(const std::string& args) override;

    void CaretPosition(int32_t caretPosition) override;

private:
    WeakPtr<Element> element_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_FIELD_TEXT_FIELD_CONTROLLER_H
