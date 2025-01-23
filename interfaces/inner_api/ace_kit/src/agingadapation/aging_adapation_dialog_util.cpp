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

#include "ui/base/agingadapation/aging_adapation_dialog_util.h"

#include "core/common/agingadapation/aging_adapation_dialog_util.h"
#include "interfaces/inner_api/ace_kit/src/view/frame_node_impl.h"
#include "ui/base/utils/utils.h"

namespace OHOS::Ace::Kit {

RefPtr<FrameNode> AgingAdapationDialogUtil::ShowLongPressDialog(
    const std::string& message, const int32_t iconNodeId, const IconNodeType type)
{
    auto uiNode = ElementRegister::GetInstance()->GetUINodeById(iconNodeId);
    CHECK_NULL_RETURN(uiNode, nullptr);
    auto frameNode = AceType::DynamicCast<NG::FrameNode>(uiNode);
    CHECK_NULL_RETURN(frameNode, nullptr);
    RefPtr<AceNode> dialogNode = nullptr;
    switch (type) {
        case IconNodeType::SYMBOL:
            dialogNode = OHOS::Ace::NG::AgingAdapationDialogUtil::ShowLongPressDialog(message, frameNode);
            break;
        case IconNodeType::IMAGE:
            {
                auto imageProperty = frameNode->GetLayoutProperty<NG::ImageLayoutProperty>();
                CHECK_NULL_RETURN(imageProperty, nullptr);
                ImageSourceInfo sourceInfo = imageProperty->GetImageSourceInfoValue();
                dialogNode = OHOS::Ace::NG::AgingAdapationDialogUtil::ShowLongPressDialog(message, sourceInfo);
                break;
            }
        default:
            break;
    }
    CHECK_NULL_RETURN(dialogNode, nullptr);
    RefPtr<FrameNode> node = AceType::MakeRefPtr<FrameNodeImpl>(dialogNode);
    return node;
}

float AgingAdapationDialogUtil::GetDialogBigFontSizeScale()
{
    return OHOS::Ace::NG::AgingAdapationDialogUtil::GetDialogBigFontSizeScale();
}

float AgingAdapationDialogUtil::GetDialogLargeFontSizeScale()
{
    return OHOS::Ace::NG::AgingAdapationDialogUtil::GetDialogLargeFontSizeScale();
}

float AgingAdapationDialogUtil::GetDialogMaxFontSizeScale()
{
    return OHOS::Ace::NG::AgingAdapationDialogUtil::GetDialogMaxFontSizeScale();
}
} // OHOS::Ace::Kit