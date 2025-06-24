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
 
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_MODEL_STATIC_H
 
#include <optional>
#include <utility>
 
#include "base/geometry/dimension_offset.h"
#include "base/geometry/ng/vector.h"
#include "base/geometry/offset.h"
#include "base/geometry/rect.h"
#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/position_param.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/border_image.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/property/overlay_property.h"
#include "core/components_ng/property/property.h"
#include "core/image/image_source_info.h"
#include "core/pipeline_ng/pipeline_context.h"
 
namespace OHOS::Ace::NG {
class ACE_FORCE_EXPORT ViewAbstractModelStatic {
public:
    static void SetClipEdge(FrameNode* frameNode, std::optional<bool> isClip);
    void BindContextMenu(const RefPtr<FrameNode>& targetNode, ResponseType type, std::function<void()>& buildFunc,
        const NG::MenuParam& menuParam, std::function<void()>& previewBuildFunc);
    static void BindContextMenuStatic(const RefPtr<FrameNode>& targetNode, ResponseType type,
        std::function<void()>&& buildFunc, const NG::MenuParam& menuParam, std::function<void()>&& previewBuildFunc);
    void BindDragWithContextMenuParams(FrameNode* targetNode, const NG::MenuParam& menuParam);
    static void SetAccessibilityVirtualNode(FrameNode* frameNode, std::function<RefPtr<NG::UINode>()>&& buildFunc);
    static void BindPopup(FrameNode* targetNode, const RefPtr<PopupParam>& param, const RefPtr<AceType>& customNode)
    {
        CHECK_NULL_VOID(targetNode);
        ViewAbstract::BindPopup(param, AceType::Claim(targetNode), AceType::DynamicCast<UINode>(customNode));
    }
    static void BindMenu(FrameNode* frameNode, std::vector<NG::OptionParam>&& params, std::function<void()>&& buildFunc,
        const MenuParam& menuParam);
    static void BindMenuGesture(FrameNode* frameNode, std::vector<NG::OptionParam>&& params,
        std::function<void()>&& buildFunc, const MenuParam& menuParam);
    static void BindDragWithContextMenuParamsStatic(FrameNode* targetNode, const NG::MenuParam& menuParam);
private:
    static bool CheckMenuIsShow(const MenuParam& menuParam, int32_t targetId, const RefPtr<FrameNode>& targetNode);
    static void BindContextMenuSingle(FrameNode* targetNode, std::function<void()>&& buildFunc,
        const MenuParam& menuParam, std::function<void()>&& previewBuildFunc);
    static void RegisterContextMenuKeyEvent(
        const RefPtr<FrameNode>& targetNode, std::function<void()>& buildFunc, const MenuParam& menuParam);
    static void CreateCustomMenuWithPreview(FrameNode* targetNode, std::function<void()>&& buildFunc,
        const MenuParam& menuParam, std::function<void()>&& previewBuildFunc);
};
} // namespace OHOS::Ace::NG
 
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_MODEL_STATIC_H