/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License")
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

#ifndef CAPI0805_2_ARKUISTACKNODE_H
#define CAPI0805_2_ARKUISTACKNODE_H

#include "ArkUINode.h"

namespace NativeModule {

class ArkUIStackNode : public ArkUINode {
public:
    ArkUIStackNode()
        : ArkUINode((NativeModuleInstance::GetInstance()->GetNativeNodeAPI())->createNode(ARKUI_NODE_STACK)) {}
    
    ~ArkUIStackNode() override {}
};

} // namespace NativeModule
#endif // CAPI0805_2_ARKUISTACKNODE_H
