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
#include "core/common/ace_application_info.h"

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

bool (*g_testThreadChecker)() = nullptr;
const ArkUIBasicAPI* (*g_testBasicAPIProvider)() = nullptr;

ArkUI_Bool MockIsCurrentThreadSafe()
{
    return g_testThreadChecker ? (g_testThreadChecker() ? 1 : 0) : 1;
}

const ArkUIBasicAPI* MockGetBasicAPI()
{
    static ArkUIBasicAPI api {
        .isCurrentThreadSafe = MockIsCurrentThreadSafe,
        .isDebugForParallel = []() -> ArkUI_Bool {
            return AceApplicationInfo::GetInstance().IsDebugForParallel();
        },
    };
    return &api;
}

ArkUIFullNodeAPI* MockGetFullImpl()
{
    static ArkUIFullNodeAPI impl = {
        .getBasicAPI = []() -> const ArkUIBasicAPI* {
            return g_testBasicAPIProvider ? g_testBasicAPIProvider() : nullptr;
        },
        .getNodeModifiers = MockGetNodeModifiers,
    };
    return &impl;
}

} // namespace

void SetMockIsCurrentThreadSafe(bool (*checker)())
{
    g_testThreadChecker = checker;
}

void ResetMockIsCurrentThreadSafe()
{
    g_testThreadChecker = nullptr;
}

void SetMockBasicAPIProvider(const ArkUIBasicAPI* (*provider)())
{
    g_testBasicAPIProvider = provider;
}

void ResetMockBasicAPIProvider()
{
    g_testBasicAPIProvider = nullptr;
}

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

const ArkUIBasicAPI* GetBasicAPI()
{
    return g_testBasicAPIProvider == nullptr ? MockGetBasicAPI() : g_testBasicAPIProvider();
}

} // namespace OHOS::Ace::NodeModel
