/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_FRAME_NODE_MODIFIER_MULTI_THREAD_H
#define FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_FRAME_NODE_MODIFIER_MULTI_THREAD_H

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
void ClearChildrenInFrameNodeMultiThread(ArkUINodeHandle node);
} // namespace OHOS::Ace::NG

#endif // FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_FRAME_NODE_MODIFIER_MULTI_THREAD_H