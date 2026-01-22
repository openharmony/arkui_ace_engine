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
#include "core/interfaces/native/node/alphabet_indexer_modifier.h"
#include "core/components_ng/pattern/indexer/indexer_model_ng.h"
namespace OHOS::Ace::NG {
ArkUINodeHandle CreateIndexer(ArkUI_Int32 nodeId, ArkUI_Bool isArc)
{
    auto frameNode = IndexerModelNG::CreateFrameNode(nodeId, isArc);
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}
namespace NodeModifier {
const ArkUIAlphabetIndexerModifier* GetAlphabetIndexerModifier()
{
    static const ArkUIAlphabetIndexerModifier modifier = {
        .createFrameNode = CreateIndexer,
    };
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG