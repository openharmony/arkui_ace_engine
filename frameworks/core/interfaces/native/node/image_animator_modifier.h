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

#ifndef FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_IMAGE_ANIMATOR_MODIFIER_H
#define FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_IMAGE_ANIMATOR_MODIFIER_H

#include "core/interfaces/native/node/node_api.h"

namespace OHOS::Ace::NG::NodeModifier {
const ArkUIImageAnimatorModifier* GetImageAnimatorModifier();
const CJUIImageAnimatorModifier* GetCJUIImageAnimatorModifier();
void SetImageAnimatorOnStart(ArkUINodeHandle node, void* extraParam);
void SetImageAnimatorOnPause(ArkUINodeHandle node, void* extraParam);
void SetImageAnimatorOnRepeat(ArkUINodeHandle node, void* extraParam);
void SetImageAnimatorOnCancel(ArkUINodeHandle node, void* extraParam);
void SetImageAnimatorOnFinish(ArkUINodeHandle node, void* extraParam);

void ResetImageAnimatorOnStart(ArkUINodeHandle node);
void ResetImageAnimatorOnPause(ArkUINodeHandle node);
void ResetImageAnimatorOnRepeat(ArkUINodeHandle node);
void ResetImageAnimatorOnCancel(ArkUINodeHandle node);
void ResetImageAnimatorOnFinish(ArkUINodeHandle node);
}

#endif // FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_IMAGE_ANIMATOR_MODIFIER_H
