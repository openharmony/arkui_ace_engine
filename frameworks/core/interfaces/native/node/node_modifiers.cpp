/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/node_modifiers.h"

#include "core/interfaces/native/node/node_common_modifier.h"

namespace OHOS::Ace::NG {
namespace {
const ArkUINodeModifiers impl = {
    ARKUI_NODE_MODIFIERS_API_VERSION,
    NodeModifier::GetCommonModifier,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
#ifdef PLUGIN_COMPONENT_SUPPORTED
    nullptr,
#else
    nullptr,
#endif
#ifdef XCOMPONENT_SUPPORTED
    nullptr,
#else
    nullptr,
#endif
#ifdef FORM_SUPPORTED
    nullptr,
#else
    nullptr,
#endif
};

} // namespace

} // namespace OHOS::Ace::NG

extern "C" {

const ArkUINodeModifiers* GetArkUINodeModifiers()
{
    return &OHOS::Ace::NG::impl;
}
}
