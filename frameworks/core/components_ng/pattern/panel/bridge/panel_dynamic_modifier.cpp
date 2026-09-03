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
#include "core/interfaces/native/node/panel_modifier.h"

#include "core/common/container.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/panel/sliding_panel_model.h"
#include "core/components_ng/pattern/panel/sliding_panel_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<SlidingPanelModel> SlidingPanelModel::instance_ = nullptr;
std::mutex SlidingPanelModel::mutex_;

SlidingPanelModel* SlidingPanelModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
            instance_.reset(new NG::SlidingPanelModelNG());
        }
    }
    return instance_.get();
}

#ifndef CROSS_PLATFORM
SlidingPanelModel* GetSlidingPanelModelImpl()
{
    static auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("panel");
    static SlidingPanelModel* instance =
        loader ? reinterpret_cast<SlidingPanelModel*>(loader->CreateModel()) : nullptr;
    return instance;
}
#endif
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
constexpr int32_t DEFAULT_PANEL_MODE = 1;
constexpr double DEFAULT_HEIGHT = 48;
constexpr uint32_t DEFAULT_PANEL_BACKGROUND_COLOR = 0x08182431;
constexpr int32_t DEFAULT_PANEL_TYPE = 1;
constexpr double DEFAULT_CUSTOM_HEIGHT = 0;

void SetPanelMode(ArkUINodeHandle node, int32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto mode = static_cast<PanelMode>(value);
    SlidingPanelModelNG::SetPanelMode(frameNode, mode);
}

void ResetPanelMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto mode = static_cast<PanelMode>(DEFAULT_PANEL_MODE);
    SlidingPanelModelNG::SetPanelMode(frameNode, mode);
}

void SetPanelFullHeight(ArkUINodeHandle node, ArkUI_Float32 value, int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetPanelFullHeight(frameNode, Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit)));
}
void ResetPanelFullHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::ResetPanelFullHeight(frameNode);
}

void SetPanelHalfHeight(ArkUINodeHandle node, ArkUI_Float32 value, int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetPanelHalfHeight(frameNode, Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit)));
}
void ResetPanelHalfHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::ResetPanelHalfHeight(frameNode);
}

void SetPanelMiniHeight(ArkUINodeHandle node, ArkUI_Float32 value, int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetPanelMiniHeight(frameNode, Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit)));
}

void ResetPanelMiniHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetPanelMiniHeight(frameNode, Dimension(DEFAULT_HEIGHT, DimensionUnit::VP));
}

void SetPanelBackgroundMask(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetPanelBackgroundMask(frameNode, Color(color));
}

void ResetPanelBackgroundMask(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetPanelBackgroundMask(frameNode, Color(DEFAULT_PANEL_BACKGROUND_COLOR));
}

void SetPanelType(ArkUINodeHandle node, int32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto type = static_cast<PanelType>(value);
    SlidingPanelModelNG::SetPanelType(frameNode, type);
}

void ResetPanelType(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto type = static_cast<PanelType>(DEFAULT_PANEL_TYPE);
    SlidingPanelModelNG::SetPanelType(frameNode, type);
}

void SetPanelCustomHeight(ArkUINodeHandle node, ArkUI_Float32 value, int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetPanelCustomHeight(
        frameNode, CalcDimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit)));
}

void SetPanelCustomHeightByString(ArkUINodeHandle node, const char* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetPanelCustomHeight(frameNode, CalcDimension(value));
}

void ResetPanelCustomHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetPanelCustomHeight(frameNode, CalcDimension(DEFAULT_CUSTOM_HEIGHT));
}

void SetShowCloseIcon(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetShowCloseIcon(frameNode, value);
}

void ResetShowCloseIcon(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetShowCloseIcon(frameNode, false);
}

void SetDragBar(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetHasDragBar(frameNode, value);
}

void ResetDragBar(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetHasDragBar(frameNode, true);
}

void SetShow(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetIsShow(frameNode, value);
}

void ResetShow(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetIsShow(frameNode, true);
}

void CreatePanel(ArkUI_Bool isShow)
{
    SlidingPanelModel::GetInstance()->Create(isShow);
}

void Pop()
{
    if (ViewStackModel::GetInstance()->IsPrebuilding()) {
        return ViewStackModel::GetInstance()->PushPrebuildCompCmd("[JSSlidingPanel][pop]", &Pop);
    }
    SlidingPanelModel::GetInstance()->Pop();
}

void SetModeChangeEvent(void* modeChangeEvent)
{
    SlidingPanelModel::GetInstance()->SetModeChangeEvent(
        std::move(*reinterpret_cast<std::function<void(const BaseEventInfo*)>*>(modeChangeEvent)));
}

void setBackgroundColorForHDR(ArkUINodeHandle node, ArkUIColorHeadRoom color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Color backgroundColor = Color::FromFloat(color.red, color.green, color.blue, color.alpha, color.headRoom);
    backgroundColor.SetColorSpace(static_cast<ColorSpace>(color.colorSpace));
    SlidingPanelModel::GetInstance()->SetBackgroundColor(backgroundColor);
}

void SetPanelBackgroundColorWithColorSpace(ArkUI_Uint32 color, ArkUI_Int32 colorSpace)
{
    Color backgroundColor { color };
    if (ColorSpace::DISPLAY_P3 == colorSpace) {
        backgroundColor.SetColorSpace(ColorSpace::DISPLAY_P3);
    } else {
        backgroundColor.SetColorSpace(ColorSpace::SRGB);
    }
    SlidingPanelModel::GetInstance()->SetBackgroundColor(backgroundColor);
}

void SetPanelBorderWidth(ArkUI_Float32 value, ArkUI_Int32 unit)
{
    CalcDimension width(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    SlidingPanelModel::GetInstance()->SetBorderWidth(width);
}

void SetPanelBorderStyle(ArkUI_Int32 borderStyle)
{
    SlidingPanelModel::GetInstance()->SetBorderStyle(static_cast<BorderStyle>(borderStyle));
}

void SetPanelBorderColor(ArkUI_Uint32 color)
{
    SlidingPanelModel::GetInstance()->SetBorderColor(Color(color));
}

void SetOnSizeChange(void* onSizeChange)
{
    SlidingPanelModel::GetInstance()->SetOnSizeChange(
        std::move(*reinterpret_cast<std::function<void(const BaseEventInfo*)>*>(onSizeChange)));
}

void SetOnHeightChange(void* onHeightChange)
{
    SlidingPanelModel::GetInstance()->SetOnHeightChange(
        std::move(*reinterpret_cast<std::function<void(const float)>*>(onHeightChange)));
}
#ifndef CROSS_PLATFORM
void SetPanelModeImpl(ArkUINodeHandle node, int32_t value)
{
    auto mode = static_cast<PanelMode>(value);
    GetSlidingPanelModelImpl()->SetPanelMode(mode);
}

void SetPanelFullHeightImpl(ArkUINodeHandle node, ArkUI_Float32 value, int unit)
{
    GetSlidingPanelModelImpl()->SetFullHeight(Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit)));
}

void SetPanelHalfHeightImpl(ArkUINodeHandle node, ArkUI_Float32 value, int unit)
{
    GetSlidingPanelModelImpl()->SetHalfHeight(Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit)));
}

void SetPanelMiniHeightImpl(ArkUINodeHandle node, ArkUI_Float32 value, int unit)
{
    GetSlidingPanelModelImpl()->SetMiniHeight(Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit)));
}

void SetPanelBackgroundMaskImpl(ArkUINodeHandle node, uint32_t color)
{
    GetSlidingPanelModelImpl()->SetBackgroundMask(Color(color));
}

void SetPanelTypeImpl(ArkUINodeHandle node, int32_t value)
{
    auto type = static_cast<PanelType>(value);
    GetSlidingPanelModelImpl()->SetPanelType(type);
}

void SetDragBarImpl(ArkUINodeHandle node, ArkUI_Bool value)
{
    GetSlidingPanelModelImpl()->SetHasDragBar(value);
}

void SetShowImpl(ArkUINodeHandle node, ArkUI_Bool value)
{
    GetSlidingPanelModelImpl()->SetIsShow(value);
}

void CreatePanelImpl(ArkUI_Bool isShow)
{
    GetSlidingPanelModelImpl()->Create(isShow);
}

void PopImpl()
{
    if (ViewStackModel::GetInstance()->IsPrebuilding()) {
        return ViewStackModel::GetInstance()->PushPrebuildCompCmd("[JSSlidingPanel][pop]", &PopImpl);
    }
    GetSlidingPanelModelImpl()->Pop();
}

void SetModeChangeEventImpl(void* modeChangeEvent)
{
    GetSlidingPanelModelImpl()->SetModeChangeEvent(
        std::move(*reinterpret_cast<std::function<void(const BaseEventInfo*)>*>(modeChangeEvent)));
}

void SetPanelBorderWidthImpl(ArkUI_Float32 value, ArkUI_Int32 unit)
{
    CalcDimension width(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    GetSlidingPanelModelImpl()->SetBorderWidth(width);
}

void SetPanelBorderStyleImpl(ArkUI_Int32 borderStyle)
{
    GetSlidingPanelModelImpl()->SetBorderStyle(static_cast<BorderStyle>(borderStyle));
}

void SetPanelBorderColorImpl(ArkUI_Uint32 color)
{
    GetSlidingPanelModelImpl()->SetBorderColor(Color(color));
}

void SetOnSizeChangeImpl(void* onSizeChange)
{
    GetSlidingPanelModelImpl()->SetOnSizeChange(
        std::move(*reinterpret_cast<std::function<void(const BaseEventInfo*)>*>(onSizeChange)));
}

void SetOnHeightChangeImpl(void* onHeightChange)
{
    GetSlidingPanelModelImpl()->SetOnHeightChange(
        std::move(*reinterpret_cast<std::function<void(const float)>*>(onHeightChange)));
}
#endif

namespace NodeModifier {
const ArkUIPanelModifier* GetPanelDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUIPanelModifier modifier = {
        .setPanelMode = SetPanelModeImpl,
        .resetPanelMode = nullptr,
        .setPanelFullHeight = SetPanelFullHeightImpl,
        .resetPanelFullHeight = nullptr,
        .setPanelHalfHeight = SetPanelHalfHeightImpl,
        .resetPanelHalfHeight = nullptr,
        .setPanelMiniHeight = SetPanelMiniHeightImpl,
        .resetPanelMiniHeight = nullptr,
        .setPanelBackgroundMask = SetPanelBackgroundMaskImpl,
        .resetPanelBackgroundMask = nullptr,
        .setPanelType = SetPanelTypeImpl,
        .resetPanelType = nullptr,
        .setPanelCustomHeight = nullptr,
        .setPanelCustomHeightByString = nullptr,
        .resetPanelCustomHeight = nullptr,
        .setShowCloseIcon = nullptr,
        .resetShowCloseIcon = nullptr,
        .setDragBar = SetDragBarImpl,
        .resetDragBar = nullptr,
        .setShow = SetShowImpl,
        .resetShow = nullptr,
        .createPanel = CreatePanelImpl,
        .pop = PopImpl,
        .setModeChangeEvent = SetModeChangeEventImpl,
        .setBackgroundColorForHDR = nullptr,
        .setPanelBackgroundColorWithColorSpace = nullptr,
        .setPanelBorderWidth = SetPanelBorderWidthImpl,
        .setPanelBorderStyle = SetPanelBorderStyleImpl,
        .setPanelBorderColor = SetPanelBorderColorImpl,
        .setOnSizeChange = SetOnSizeChangeImpl,
        .setOnHeightChange = SetOnHeightChangeImpl,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

        return &modifier;
#endif
    }
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIPanelModifier modifier = {
        .setPanelMode = SetPanelMode,
        .resetPanelMode = ResetPanelMode,
        .setPanelFullHeight = SetPanelFullHeight,
        .resetPanelFullHeight = ResetPanelFullHeight,
        .setPanelHalfHeight = SetPanelHalfHeight,
        .resetPanelHalfHeight = ResetPanelHalfHeight,
        .setPanelMiniHeight = SetPanelMiniHeight,
        .resetPanelMiniHeight = ResetPanelMiniHeight,
        .setPanelBackgroundMask = SetPanelBackgroundMask,
        .resetPanelBackgroundMask = ResetPanelBackgroundMask,
        .setPanelType = SetPanelType,
        .resetPanelType = ResetPanelType,
        .setPanelCustomHeight = SetPanelCustomHeight,
        .setPanelCustomHeightByString = SetPanelCustomHeightByString,
        .resetPanelCustomHeight = ResetPanelCustomHeight,
        .setShowCloseIcon = SetShowCloseIcon,
        .resetShowCloseIcon = ResetShowCloseIcon,
        .setDragBar = SetDragBar,
        .resetDragBar = ResetDragBar,
        .setShow = SetShow,
        .resetShow = ResetShow,
        .createPanel = CreatePanel,
        .pop = Pop,
        .setModeChangeEvent = SetModeChangeEvent,
        .setBackgroundColorForHDR = setBackgroundColorForHDR,
        .setPanelBackgroundColorWithColorSpace = SetPanelBackgroundColorWithColorSpace,
        .setPanelBorderWidth = SetPanelBorderWidth,
        .setPanelBorderStyle = SetPanelBorderStyle,
        .setPanelBorderColor = SetPanelBorderColor,
        .setOnSizeChange = SetOnSizeChange,
        .setOnHeightChange = SetOnHeightChange,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUIPanelModifier* GetCJUIPanelModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIPanelModifier modifier = {
        .setPanelMode = SetPanelMode,
        .resetPanelMode = ResetPanelMode,
        .setPanelFullHeight = SetPanelFullHeight,
        .resetPanelFullHeight = ResetPanelFullHeight,
        .setPanelHalfHeight = SetPanelHalfHeight,
        .resetPanelHalfHeight = ResetPanelHalfHeight,
        .setPanelMiniHeight = SetPanelMiniHeight,
        .resetPanelMiniHeight = ResetPanelMiniHeight,
        .setPanelBackgroundMask = SetPanelBackgroundMask,
        .resetPanelBackgroundMask = ResetPanelBackgroundMask,
        .setPanelType = SetPanelType,
        .resetPanelType = ResetPanelType,
        .setPanelCustomHeight = SetPanelCustomHeight,
        .setPanelCustomHeightByString = SetPanelCustomHeightByString,
        .resetPanelCustomHeight = ResetPanelCustomHeight,
        .setShowCloseIcon = SetShowCloseIcon,
        .resetShowCloseIcon = ResetShowCloseIcon,
        .setDragBar = SetDragBar,
        .resetDragBar = ResetDragBar,
        .setShow = SetShow,
        .resetShow = ResetShow,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
}
} // namespace OHOS::Ace::NG
