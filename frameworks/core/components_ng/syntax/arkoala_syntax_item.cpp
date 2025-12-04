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

#include "core/components_ng/syntax/arkoala_syntax_item.h"

namespace OHOS::Ace::NG {

ArkoalaSyntaxItem::ArkoalaSyntaxItem(int32_t nodeId) : UINode(V2::JS_SYNTAX_ITEM_ETS_TAG, nodeId) {}

void ArkoalaSyntaxItem::MarkDirtyNode(PropertyChangeFlag extraFlag)
{
    if (!IsOnMainTree()) {
        return;
    }
    UINode::MarkDirtyNode(extraFlag);
}

} // namespace OHOS::Ace::NG