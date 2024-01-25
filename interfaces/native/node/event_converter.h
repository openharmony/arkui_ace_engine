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

#pragma once

#include "native_node.h"

#include "core/interfaces/arkoala/arkoala_api.h"

namespace OHOS::Ace::NodeModel {

// for error info, use int instead of ArkUINodeEventType
ArkUI_Int32 ConvertOriginEventType(ArkUI_NodeEventType type);
ArkUI_Int32 ConvertToNodeEventType(ArkUIAsyncEventKind type);

bool ConvertEvent(ArkUINodeEvent* origin, ArkUI_NodeEvent* event);

}; // namespace OHOS::Ace::NodeModel
