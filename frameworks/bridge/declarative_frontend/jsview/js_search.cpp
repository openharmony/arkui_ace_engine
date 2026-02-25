/*
 * Copyright (c) 2021-2025 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_search.h"

#include <optional>
#include <string>
#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/engine/functions/js_clipboard_function.h"
#include "bridge/declarative_frontend/engine/functions/js_common_event_function.h"
#include "bridge/declarative_frontend/engine/functions/js_cited_event_function.h"
#include "bridge/declarative_frontend/engine/functions/js_event_function.h"
#include "bridge/declarative_frontend/engine/jsi/js_ui_index.h"
#include "bridge/declarative_frontend/jsview/js_text_editable_controller.h"
#include "bridge/declarative_frontend/jsview/js_text_editable_controller_binding.h"
#include "bridge/declarative_frontend/jsview/js_textfield.h"
#include "bridge/declarative_frontend/jsview/js_textinput.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components/common/layout/common_text_constants.h"
#include "core/components/common/properties/text_style_parser.h"
#include "core/components/search/search_theme.h"
#include "core/components_ng/gestures/gesture_info.h"
#include "core/components_ng/pattern/search/search_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"

namespace OHOS::Ace::Framework {

void JSSearchController::JSBind(BindingTarget globalObj)
{
    JSClass<JSTextEditableController>::Declare("SearchController");
    JSTextEditableControllerBinding::JSBind(globalObj);
}

} // namespace OHOS::Ace::Framework
