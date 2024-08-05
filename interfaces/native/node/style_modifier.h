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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_STYLE_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_STYLE_MODIFIER_H

#include "native_node.h"
#include "native_type.h"

namespace OHOS::Ace::NodeModel {

[[deprecated]] void SetNodeAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType type, const char* value);

int32_t SetNodeAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType type, const ArkUI_AttributeItem* item);

const ArkUI_AttributeItem* GetNodeAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType type);

int32_t ResetNodeAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType type);

}; // namespace OHOS::Ace::NodeModel
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_STYLE_MODIFIER_H
