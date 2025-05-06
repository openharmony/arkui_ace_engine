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
    static void SetWidth(FrameNode* frameNode, const CalcDimension& width)
    {
        if (width.Unit() == DimensionUnit::CALC) {
            ViewAbstract::SetWidth(frameNode, NG::CalcLength(width.CalcValue()));
        } else {
            ViewAbstract::SetWidth(frameNode, NG::CalcLength(width));
        }
    }

    static void SetHeight(FrameNode* frameNode, const CalcDimension& height)
    {
        if (height.Unit() == DimensionUnit::CALC) {
            ViewAbstract::SetHeight(frameNode, NG::CalcLength(height.CalcValue()));
        } else {
            ViewAbstract::SetHeight(frameNode, NG::CalcLength(height));
        }
    }

    static void SetMinWidth(FrameNode* frameNode, const CalcDimension& minWidth)
    {
        if (minWidth.Unit() == DimensionUnit::CALC) {
            ViewAbstract::SetMinWidth(frameNode, NG::CalcLength(minWidth.CalcValue()));
        } else {
            ViewAbstract::SetMinWidth(frameNode, NG::CalcLength(minWidth));
        }
    }

    static void SetMinHeight(FrameNode* frameNode, const CalcDimension& minHeight)
    {
        if (minHeight.Unit() == DimensionUnit::CALC) {
            ViewAbstract::SetMinHeight(frameNode, NG::CalcLength(minHeight.CalcValue()));
        } else {
            ViewAbstract::SetMinHeight(frameNode, NG::CalcLength(minHeight));
        }
    }
    static void BindMenuTouch(FrameNode* targetNode, const RefPtr<GestureEventHub>& gestrueHub);

    static RefPtr<PipelineContext> GetSheetContext(NG::SheetStyle& sheetStyle);
    static void DismissSheetStatic();
    static void DismissContentCoverStatic();
    static void SheetSpringBackStatic();
    static void SetAccessibilityTextHint(FrameNode* frameNode, const std::string& text);
    static void SetBackShadow(FrameNode *frameNode, const std::vector<Shadow>& shadows);
    static void SetLightPosition(FrameNode* frameNode, const std::optional<CalcDimension>& positionX,
        const std::optional<CalcDimension>& positionY, const std::optional<CalcDimension>& positionZ);
    static void SetLightIntensity(FrameNode* frameNode, const std::optional<float>& value);
    static void SetLightIlluminated(FrameNode *frameNode, const std::optional<uint32_t>& value,
        const RefPtr<ThemeConstants>& themeConstants);
    static void SetIlluminatedBorderWidth(FrameNode* frameNode, const Dimension& value);
    static void SetLightColor(FrameNode* frameNode, const std::optional<Color>& value);
    static void SetBloom(FrameNode *frameNode, const std::optional<float>& value,
        const RefPtr<ThemeConstants>& themeConstants);

    static void SetChainStyle(FrameNode* frameNode, const ChainInfo& chainInfo)
    {
        ViewAbstract::SetChainStyle(frameNode, chainInfo);
    }
    static void SetChainWeight(FrameNode* frameNode, const ChainWeightPair& value)
    {
        ViewAbstract::SetChainWeight(frameNode, value);
    }

    static void BindPopup(FrameNode* targetNode, const RefPtr<PopupParam>& param, const RefPtr<AceType>& customNode)
    {
        CHECK_NULL_VOID(targetNode);
        ViewAbstract::BindPopup(param, AceType::Claim(targetNode), AceType::DynamicCast<UINode>(customNode));
    }
    static void SetAccessibilityVirtualNode(FrameNode* frameNode, std::function<RefPtr<NG::UINode>()>&& buildFunc);
    static void BindMenu(FrameNode* frameNode,
        std::vector<NG::OptionParam>&& params, std::function<void()>&& buildFunc, const MenuParam& menuParam);
    static void BindMenuGesture(FrameNode* frameNode,
        std::vector<NG::OptionParam>&& params, std::function<void()>&& buildFunc, const MenuParam& menuParam);
    static void BindContextMenuStatic(const RefPtr<FrameNode>& targetNode, ResponseType type,
        std::function<void()>&& buildFunc, const NG::MenuParam& menuParam, std::function<void()>&& previewBuildFunc);
    static void BindDragWithContextMenuParamsStatic(FrameNode* targetNode, const NG::MenuParam& menuParam);

    static void BindContentCover(FrameNode* targetNode, bool isShow,
        std::function<void(const std::string&)>&& callback, std::function<RefPtr<UINode>()>&& buildFunc,
        NG::ModalStyle& modalStyle, std::function<void()>&& onAppear, std::function<void()>&& onDisappear,
        std::function<void()>&& onWillAppear, std::function<void()>&& onWillDisappear,
        const NG::ContentCoverParam& contentCoverParam);

    static void BindSheet(FrameNode* frameNode, bool isShow,
        std::function<void(const std::string&)>&& callback,
        std::function<void()>&& buildFunc,
        std::function<void()>&& titleBuildFunc, NG::SheetStyle& sheetStyle, std::function<void()>&& onAppear,
        std::function<void()>&& onDisappear, std::function<void()>&& shouldDismiss,
        std::function<void(const int32_t info)>&& onWillDismiss,
        std::function<void()>&& onWillAppear, std::function<void()>&& onWillDisappear,
        std::function<void(const float)>&& onHeightDidChange,
        std::function<void(const float)>&& onDetentsDidChange,
        std::function<void(const float)>&& onWidthDidChange,
        std::function<void(const float)>&& onTypeDidChange, std::function<void()>&& sheetSpringBack);

    static void BindBackground(FrameNode* frameNode,
        std::function<RefPtr<UINode>()>&& buildFunc, const std::optional<Alignment>& align);

private:
    static bool CheckMenuIsShow(const MenuParam& menuParam, int32_t targetId, const RefPtr<FrameNode>& targetNode);
    static void RegisterContextMenuKeyEvent(
        const RefPtr<FrameNode>& targetNode, std::function<void()>& buildFunc, const MenuParam& menuParam);
    static void CreateCustomMenuWithPreview(FrameNode* targetNode,
        std::function<void()>&& buildFunc, const MenuParam& menuParam, std::function<void()>&& previewBuildFunc);
    static void BindContextMenuSingle(FrameNode* targetNode,
        std::function<void()>&& buildFunc, const MenuParam& menuParam, std::function<void()>&& previewBuildFunc);

};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_MODEL_STATIC_H
