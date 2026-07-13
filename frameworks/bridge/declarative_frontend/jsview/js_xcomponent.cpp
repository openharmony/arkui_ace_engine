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

#include "frameworks/bridge/declarative_frontend/jsview/js_xcomponent.h"

#include "base/log/ace_scoring_log.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/common/dynamic_module_helper.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/js_xcomponent_controller.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_model.h"
#include "core/interfaces/native/node/node_xcomponent_modifier.h"

namespace OHOS::Ace {
XComponentModel* XComponentModel::GetInstance()
{
    auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("XComponent");
    CHECK_NULL_RETURN(module, nullptr);
    return reinterpret_cast<XComponentModel*>(module->GetModel());
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
XComponentClient& XComponentClient::GetInstance()
{
    static XComponentClient instance;
    return instance;
}
} // namespace OHOS::Ace::Framework
