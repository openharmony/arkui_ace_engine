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

#include "material_modifier.h"

#include "base/utils/system_properties.h"
#include "native_material_util.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/render/render_context.h"

namespace OHOS::Ace::NG {
namespace {
bool GetDeviceSystemMaterialSupported()
{
    return SystemProperties::IsDeviceSystemMaterialSupported();
}

ArkUI_Int32 GetGlobalMaterialLevel()
{
    return static_cast<ArkUI_Int32>(SystemProperties::GetUiMaterialLevel());
}

void SetSystemMaterialByHandle(ArkUINodeHandle node, ArkUI_ImmersiveMaterial* material)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (!material) {
        ViewAbstract::SetSystemMaterial(frameNode, nullptr);
        return;
    }
    auto uiMaterial = CreateUiMaterialFromHandle(material);
    ViewAbstract::SetSystemMaterial(frameNode, AceType::RawPtr(uiMaterial));
}

void ResetSystemMaterial(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetSystemMaterial(frameNode, nullptr);
}

bool GetSystemMaterialHandle(ArkUINodeHandle node, ArkUI_ImmersiveMaterial* material)
{
    CHECK_NULL_RETURN(material, false);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    auto uiMaterial = renderContext->GetSystemMaterial();
    CHECK_NULL_RETURN(uiMaterial, false);
    return CreateHandleFromUiMaterial(uiMaterial, material);
}
} // namespace

namespace NodeModifier {
const ArkUIMaterialModifier* GetMaterialModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN();
    static const ArkUIMaterialModifier modifier = {
        .getDeviceSystemMaterialSupported = GetDeviceSystemMaterialSupported,
        .getGlobalMaterialLevel = GetGlobalMaterialLevel,
        .setSystemMaterialByHandle = SetSystemMaterialByHandle,
        .resetSystemMaterial = ResetSystemMaterial,
        .getSystemMaterialHandle = GetSystemMaterialHandle,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0);
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
