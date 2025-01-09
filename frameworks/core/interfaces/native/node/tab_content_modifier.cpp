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

#include "bridge/common/utils/engine_helper.h"
#include "core/components_ng/pattern/tabs/tab_content_model_ng.h"
#include "core/interfaces/native/node/view_model.h"

namespace OHOS::Ace::NG {

void SetTabContentBuilder(ArkUINodeHandle node, ArkUI_Int32 methodId)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
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
    TabContentModelNG::SetTabBarBuilder(frameNode, std::move(builder));
}

void SetTabContentLabel(ArkUINodeHandle node, ArkUI_CharPtr label)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabContentModelNG::SetTabBarLabel(frameNode, label);
}

namespace NodeModifier {
const ArkUITabContentModifier* GetTabContentModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUITabContentModifier modifier = {
        .setTabContentBuilder = SetTabContentBuilder,
        .setTabContentLabel = SetTabContentLabel,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUITabContentModifier* GetCJUITabContentModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUITabContentModifier modifier = {
        .setTabContentBuilder = SetTabContentBuilder,
        .setTabContentLabel = SetTabContentLabel,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
}
}
