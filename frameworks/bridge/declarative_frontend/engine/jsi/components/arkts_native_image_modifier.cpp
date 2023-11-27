/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_image_modifier.h"

#include "base/utils/utils.h"
#include "core/components/image/image_component.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/image/image_model_ng.h"
#include "core/pipeline/base/element_register.h"
#include "frameworks/core/components/common/layout/constants.h"
#include "core/components/common/properties/alignment.h"

namespace OHOS::Ace::NG {
constexpr ImageFit DEFAULT_OBJECT_FIT_VALUE = ImageFit::COVER;
void SetObjectFit(NodeHandle node, int32_t objectFitNumber)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ImageFit objectFitValue = static_cast<ImageFit>(objectFitNumber);
    ImageModelNG::SetImageFit(frameNode, objectFitValue);
}

void ResetObjectFit(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetImageFit(frameNode, DEFAULT_OBJECT_FIT_VALUE);
}

ArkUIImageModifierAPI GetImageModifier()
{
    static const ArkUIImageModifierAPI modifier = { SetObjectFit, ResetObjectFit };
    return modifier;
}
} // namespace OHOS::Ace::NG