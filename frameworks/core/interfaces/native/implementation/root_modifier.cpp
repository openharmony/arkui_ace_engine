/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"
#include "core/components_ng/pattern/stage/page_pattern.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RootModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    RefPtr<PipelineBase> pipeline;
    pipeline = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipeline);
    CHECK_NULL_RETURN(context, nullptr);
    auto stageManager = context->GetStageManager();
    CHECK_NULL_RETURN(stageManager, nullptr);
    auto stageNode = stageManager->GetStageNode();
    TAG_LOGD(AceLogTag::ACE_NATIVE_NODE, "createRootNode: stageNode %{public}p", AceType::RawPtr(stageNode));

    // create page node as CAPI root node to support existing
    // PageNode functionality like status bar offset supporting for example
    auto pageInfo = AceType::MakeRefPtr<PageInfo>(id, "", "");
    CHECK_NULL_RETURN(pageInfo, AceType::RawPtr(stageNode));
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(pageInfo);
    CHECK_NULL_RETURN(pagePattern, AceType::RawPtr(stageNode));
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, id, pagePattern);
    CHECK_NULL_RETURN(pageNode, AceType::RawPtr(stageNode));
    pageNode->SetHostPageId(id);
    if (stageManager->PushPage(pageNode, true, false)) {
        return AceType::RawPtr(pageNode);
    }

    return AceType::RawPtr(stageNode);
}
} // RootModifier
const GENERATED_ArkUIRootModifier* GetRootModifier()
{
    static const GENERATED_ArkUIRootModifier ArkUIRootModifierImpl {
        RootModifier::ConstructImpl,
    };
    return &ArkUIRootModifierImpl;
}

}
