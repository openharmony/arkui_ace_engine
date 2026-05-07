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

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/pipeline_ng/environment_manager.h"

namespace OHOS::Ace::NG {
namespace {
constexpr char ENV_KEY_FONT_SCALE[] = "system.arkui.fontScale";

void DispatchLayoutFontScaleChangedToAffectedNode(
    const RefPtr<UINode>& node, EnvironmentPropertyKind kind, const std::string& key)
{
    if (kind != EnvironmentPropertyKind::ENV || key != ENV_KEY_FONT_SCALE) {
        return;
    }
    CHECK_NULL_VOID(node);
    auto customNode = AceType::DynamicCast<CustomNode>(node);
    if (customNode) {
        customNode->MarkNeedUpdate();
    }

    auto frameNode = AceType::DynamicCast<FrameNode>(node);
    if (frameNode) {
        ConfigurationChange configurationChange;
        configurationChange.fontScaleUpdate = true;
        frameNode->OnConfigurationUpdate(configurationChange);
    }
}

void EnsureLayoutFontScaleEnvInitialized()
{
    EnvironmentManager::RegisterValueChangedCallback(
        EnvironmentPropertyKind::ENV, ENV_KEY_FONT_SCALE, &DispatchLayoutFontScaleChangedToAffectedNode);
}

struct LayoutFontScaleEnvBootstrap {
    LayoutFontScaleEnvBootstrap()
    {
        EnsureLayoutFontScaleEnvInitialized();
    }
};

const LayoutFontScaleEnvBootstrap g_layoutFontScaleEnvBootstrap;
} // namespace

} // namespace OHOS::Ace::NG
