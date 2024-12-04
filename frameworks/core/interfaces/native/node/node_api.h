/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NODE_API_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NODE_API_H

#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/cjui/cjui_api.h"
#include "core/interfaces/native/node/node_utils.h"

#ifdef __cplusplus
extern "C" {
#endif

const struct ArkUINodeModifiers* GetArkUINodeModifiers(void);

// use internal, not for export.
const struct ArkUIFullNodeAPI* GetArkUIFullNodeAPI(void);
const struct CJUINodeModifiers* GetCJUINodeModifiers(void);
void SendArkUIAsyncEvent(struct ArkUINodeEvent* event);
void SendArkUIAsyncCustomEvent(struct ArkUICustomNodeEvent* event);
#ifdef __cplusplus
};
#endif

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NODE_API_H
