/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUBBLE_BUBBLE_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUBBLE_BUBBLE_VIEW_H

#include <string>

#include "base/geometry/dimension.h"
#include "base/memory/referenced.h"
#include "base/utils/device_config.h"
#include "base/utils/macros.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/popup_param.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT BubbleView {
public:
    static RefPtr<FrameNode> CreateBubbleNode(
        const std::string& tag, int32_t targetId, const RefPtr<PopupParam>& param);
    static RefPtr<FrameNode> CreateCustomBubbleNode(const std::string& targetTag, int32_t targetId,
        const RefPtr<UINode>& customNode, const RefPtr<PopupParam>& param);
    static RefPtr<FrameNode> CreateMessage(const std::string& message, bool isUseCustom);
    static RefPtr<FrameNode> CreateCombinedChild(
        const RefPtr<PopupParam>& param, int32_t popupId, int32_t targetId, const RefPtr<FrameNode>& bobbleNode);
    static RefPtr<FrameNode> CreateButtons(const RefPtr<PopupParam>& param, int32_t popupId, int32_t targetId);
    static RefPtr<FrameNode> CreateButton(
        ButtonProperties& buttonParam, int32_t popupId, int32_t targetId, const RefPtr<PopupParam>& param);
    static void UpdatePopupParam(int32_t popupId, const RefPtr<PopupParam>& param, const RefPtr<FrameNode>& targetNode);
    static void UpdateCustomPopupParam(int32_t popupId, const RefPtr<PopupParam>& param);
    static void UpdateCommonParam(int32_t popupId, const RefPtr<PopupParam>& param, bool custom = true);
    static void GetPopupMaxWidthAndHeight(
        const RefPtr<PopupParam>& param, float& popupMaxWidth, float& popupMaxHeight, int32_t popupId);
    static void UpdateBubbleContent(int32_t popupId, const RefPtr<PopupParam>& param);
    static void UpdateBubbleButtons(std::list<RefPtr<UINode>>& buttons, const RefPtr<PopupParam>& param);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUBBLE_BUBBLE_VIEW_H
