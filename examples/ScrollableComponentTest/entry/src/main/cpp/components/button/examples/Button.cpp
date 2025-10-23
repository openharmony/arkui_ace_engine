/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "components/button/Button.h"

namespace ArkUICApiDemo {

void ButtonComponent::SetLabel(const std::string& content)
{
    ArkUI_AttributeItem item = { nullptr, 0, content.c_str() };
    _nodeAPI->setAttribute(_component, NODE_BUTTON_LABEL, &item);
}
} // namespace ArkUICApiDemo
