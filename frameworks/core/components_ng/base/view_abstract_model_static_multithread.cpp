/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model_static.h"

namespace OHOS::Ace::NG {
void SetBackgroundEffectMultiThread(FrameNode* frameNode,
    const std::optional<EffectOption>& effectOption, const std::optional<SysOptions>& sysOptions)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->PostAfterAttachMainTreeTask([weak = AceType::WeakClaim(frameNode), effectOption, sysOptions]() {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        ViewAbstract::SetBackgroundEffect(frameNode.GetRawPtr(), effectOption.value_or(EffectOption()),
            sysOptions.value_or(ViewAbstractModelStatic::DEFAULT_SYS_OPTIONS));
    });
}

void SetTranslateMultiThread(FrameNode* frameNode, const NG::TranslateOptions& value)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->PostAfterAttachMainTreeTask([weak = AceType::WeakClaim(frameNode), value]() {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        ViewAbstract::SetTranslate(frameNode.GetRawPtr(), value);
    });
}

void SetGeometryTransitionMultiThread(FrameNode* frameNode, const std::string& id,
    bool followWithoutTransition, bool doRegisterSharedTransition)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->PostAfterAttachMainTreeTask([weak = AceType::WeakClaim(frameNode),
        id, followWithoutTransition, doRegisterSharedTransition]() {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        ViewAbstract::SetGeometryTransition(frameNode.GetRawPtr(),
            id, followWithoutTransition, doRegisterSharedTransition);
    });
}

void BindMenuMultiThread(FrameNode* frameNode, std::vector<NG::OptionParam>&& params, std::function<void()>&& buildFunc,
    const MenuParam& menuParam)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->PostAfterAttachMainTreeTask([weak = AceType::WeakClaim(frameNode), params = std::move(params),
                                               buildFunc = std::move(buildFunc), menuParam]() mutable {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        ViewAbstractModelStatic::BindMenu(frameNode.GetRawPtr(), std::move(params), std::move(buildFunc), menuParam);
    });
}

void BindContextMenuStaticMultiThread(const RefPtr<FrameNode>& targetNode, ResponseType type,
    std::function<void()>&& buildFunc, NG::MenuParam& menuParam, std::function<void()>&& previewBuildFunc)
{
    CHECK_NULL_VOID(targetNode);
    targetNode->PostAfterAttachMainTreeTask(
        [weak = AceType::WeakClaim(targetNode.GetRawPtr()), type, builder = std::move(buildFunc), menuParam,
            previewBuildFunc = std::move(previewBuildFunc)]() mutable {
            auto frameNode = weak.Upgrade();
            CHECK_NULL_VOID(frameNode);
            ViewAbstractModelStatic::BindContextMenuStatic(
                frameNode, type, std::move(builder), menuParam, std::move(previewBuildFunc));
        });
}
} // namespace OHOS::Ace::NG
