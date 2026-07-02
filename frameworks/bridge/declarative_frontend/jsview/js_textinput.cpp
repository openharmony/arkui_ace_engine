/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_textinput.h"

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "core/common/container.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_clipboard_function.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_text_editable_controller.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_text_editable_controller_binding.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_textfield.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"
#include "frameworks/core/common/ime/text_input_action.h"
#include "frameworks/core/common/ime/text_input_type.h"
#include "frameworks/compatible/components/text_field/text_field_component.h"
#include "frameworks/core/components/text_field/textfield_theme.h"
#include "frameworks/core/components_ng/pattern/text_field/text_content_type.h"

namespace OHOS::Ace::Framework {
void JSTextInputController::JSBind(BindingTarget globalObj)
{
    JSClass<JSTextEditableController>::Declare("TextInputController");
    JSTextEditableControllerBinding::JSBind(globalObj);
}
} // namespace OHOS::Ace::Framework
