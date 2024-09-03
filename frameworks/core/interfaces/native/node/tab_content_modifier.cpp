/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/tab_content_modifier.h"
#include "core/interfaces/native/node/node_image_modifier.h"
#include "bridge/common/utils/engine_helper.h"
#include "core/components_ng/pattern/tabs/tab_content_model_ng.h"
#include "core/interfaces/native/node/view_model.h"

namespace OHOS::Ace::NG {

std::optional<std::string> TextResourceToString(ArkUINodeHandle node, const ArkUIResource* resource)
{
    std::optional<std::string> result;
    if (resource) {
        auto themeConstants = NodeModifier::GetThemeConstants(node, resource->bundleName, resource->moduleName);

        if (resource->id != -1) {
            switch (static_cast<NodeModifier::ResourceType>(resource->type)) {
                case NodeModifier::ResourceType::STRING:
                    result = themeConstants->GetString(resource->id);
                    break;

                default:
                    LOGW("TextResource type = %{public}d not supported", resource->type);
                    break;
            }
        }
    }

    return result;
}

void SetTabContent(ArkUINodeHandle node, const ArkUIResource* iconResource, const ArkUIResource* labelResource)
{
    auto icon = NodeModifier::ImageResourceToString(node, iconResource);
    auto label = TextResourceToString(node, labelResource);

    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabContentModelNG::SetTabBar(frameNode, label.value_or(""), icon.value_or(""), nullptr);
}

void SetTabContentBuilder(ArkUINodeHandle node, ArkUI_Int32 methodId)
{
    auto builder = [methodId]() {
        auto engine = EngineHelper::GetCurrentEngine();
        CHECK_NULL_VOID(engine);
        NativeEngine* nativeEngine = engine->GetNativeEngine();
        ArkUIEventCallbackArg args[] = {};
        auto dispatch = ViewModel::GetCallbackMethod();
        CHECK_NULL_VOID(dispatch);
        auto vmContext = reinterpret_cast<ArkUIVMContext>(nativeEngine);
        CHECK_NULL_VOID(vmContext);
        dispatch->CallInt(vmContext, methodId, 0, args);
    };

    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabContentModelNG::SetTabBar(frameNode, "", "", std::move(builder));
}

void SetTabContentLabel(ArkUINodeHandle node, ArkUI_CharPtr label)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabContentModelNG::SetTabBar(frameNode, label, "", nullptr);
}

void SetLayoutMode(ArkUINodeHandle node, ArkUI_Int32 mode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabContentModelNG::SetLayoutMode(frameNode, static_cast<LayoutMode>(mode));
}

void SetId(ArkUINodeHandle node, ArkUI_CharPtr id)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabContentModelNG::SetId(frameNode, id);
}

namespace NodeModifier {
const ArkUITabContentModifier* GetTabContentModifier()
{
    static const ArkUITabContentModifier modifier = {
        SetTabContent,
        SetTabContentBuilder,
        SetTabContentLabel,
        SetLayoutMode,
        SetId
    };
    return &modifier;
}

const CJUITabContentModifier* GetCJUITabContentModifier()
{
    static const CJUITabContentModifier modifier = {
        SetTabContentBuilder,
        SetTabContentLabel
    };
    return &modifier;
}
}
}
