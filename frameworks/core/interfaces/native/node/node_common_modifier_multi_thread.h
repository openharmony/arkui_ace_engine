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


#ifndef FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_NODE_COMMON_MODIFIER_MULTI_THREAD_H
#define FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_NODE_COMMON_MODIFIER_MULTI_THREAD_H

#include "base/utils/multi_thread.h"
#include "core/interfaces/native/node/node_common_modifier.h"
#include "core/components_ng/base/view_abstract.h"
namespace OHOS::Ace::NG {
 
void SetGeometryTransitionMultiThread(ArkUINodeHandle node, ArkUI_CharPtr id,
    const ArkUIGeometryTransitionOptions* options);
void ResetGeometryTransitionMultiThread(ArkUINodeHandle node);
}
#endif // FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_NODE_COMMON_MODIFIER_MULTI_THREAD_H
