/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef COMPONENT_EXT_ARC_LIST_ARC_LIST_NAPI_H
#define COMPONENT_EXT_ARC_LIST_ARC_LIST_NAPI_H

#include "napi/native_api.h"
#include "napi/native_node_api.h"

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::ArcList {
using HandleValue = std::function<void(napi_env, napi_value, napi_valuetype)>;
using HandleUndefined = std::function<void()>;
napi_value UnwrapOptionalValue(
    napi_env env, napi_callback_info info, const HandleValue& handleValue, const HandleUndefined& handleUndefined);

using HandleModifier = std::function<void(napi_env, NG::FrameNode*, int32_t, napi_value*)>;
napi_value UnwrapModifier(napi_env env, napi_callback_info info, const HandleModifier& handleModifier);
} // namespace OHOS::Ace::ArcList
#endif // COMPONENT_EXT_ARC_LIST_ARC_LIST_NAPI_H
