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

#include "core/interfaces/native/node/extension_custom_node.h"

namespace OHOS::Ace::NG {
void ExtensionCustomNode::OnMeasure(const ExtensionLayoutConstraint& layoutConstraint)
{
    if (measureCallback_) {
        auto param = LayoutConstraintF();
        param.minSize = SizeF(layoutConstraint.minWidth, layoutConstraint.minHeight);
        param.maxSize = SizeF(layoutConstraint.maxWidth, layoutConstraint.maxHeight);
        param.percentReference = SizeF(layoutConstraint.parentIdealWidth, layoutConstraint.parentIdealHeight);
        measureCallback_(param);
    } else {
        // call origin measure.
        InnerMeasure(layoutConstraint);
    }
}

void ExtensionCustomNode::OnLayout(int32_t width, int32_t height, int32_t positionX, int32_t positionY)
{
    if (layoutCallback_) {
        auto position = OffsetF(positionX, positionY);
        layoutCallback_(position);
    } else {
        InnerLayout(width, height, positionX, positionY);
    }
}
} // namespace OHOS::Ace::NG