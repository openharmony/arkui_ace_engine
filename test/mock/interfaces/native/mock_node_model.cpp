/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "interfaces/native/native_material.h"
#include "interfaces/native/node/node_model.h"

#include "frameworks/core/interfaces/arkoala/arkoala_api.h"

namespace OHOS::Ace::NodeModel {

namespace {

bool MockGetDeviceSystemMaterialSupported()
{
    return true;
}

ArkUI_Int32 MockGetGlobalMaterialLevel()
{
    return ARKUI_MATERIAL_LEVEL_SMOOTH;
}

const ArkUIMaterialModifier* MockGetMaterialModifier()
{
    static ArkUIMaterialModifier modifier = {
        .getDeviceSystemMaterialSupported = MockGetDeviceSystemMaterialSupported,
        .getGlobalMaterialLevel = MockGetGlobalMaterialLevel,
    };
    return &modifier;
}

const ArkUINodeModifiers* MockGetNodeModifiers()
{
    static ArkUINodeModifiers modifiers = {
        .getMaterialModifier = MockGetMaterialModifier,
    };
    return &modifiers;
}

ArkUIFullNodeAPI* MockGetFullImpl()
{
    static ArkUIFullNodeAPI impl = {
        .getNodeModifiers = MockGetNodeModifiers,
    };
    return &impl;
}

} // namespace

bool InitialFullImpl()
{
    return true;
}

ArkUIFullNodeAPI* GetFullImpl()
{
    return MockGetFullImpl();
}

ArkUIFullNodeAPI* GetOrCreateFullImpl()
{
    return MockGetFullImpl();
}

ArkUIFullNodeAPI* GetFullImplForErrorMessage()
{
    return GetFullImpl();
}

} // namespace OHOS::Ace::NodeModel
