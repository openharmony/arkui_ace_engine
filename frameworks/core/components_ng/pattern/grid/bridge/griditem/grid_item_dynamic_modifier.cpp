/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/grid_layout/grid_layout_item_component.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/grid/bridge/griditem/grid_item_model_impl.h"
#include "core/components_ng/pattern/grid/grid_item_model_ng.h"
#include "core/components_ng/pattern/grid/grid_item_theme.h"
#include "core/interfaces/native/node/node_api.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace {
#ifndef CROSS_PLATFORM
Framework::GridItemModelImpl* GetGridItemModelImpl()
{
    static Framework::GridItemModelImpl instance;
    return &instance;
}
#endif
namespace NG {
namespace {
constexpr int32_t DEFAULT_GRID_ITEM_VALUE = 0;
const int32_t ERROR_INT_CODE = -1;
typedef void (*ComponentAsyncEventHandler)(ArkUINodeHandle node, void* extraParam);
typedef void (*ResetComponentAsyncEventHandler)(ArkUINodeHandle node);
FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}
} // namespace

void SetGridItemSelectable(ArkUINodeHandle node, ArkUI_Bool selectable)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetSelectable(frameNode, selectable);
}

void ResetGridItemSelectable(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetSelectable(frameNode, true);
}

ArkUI_Bool GetGridItemSelectable(ArkUINodeHandle node)
{
    CHECK_NULL_RETURN(node, true);
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, true);
    return GridItemModelNG::GetSelectable(frameNode);
}

void SetGridItemSelected(ArkUINodeHandle node, ArkUI_Bool selected)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetSelected(frameNode, selected);
}

void ResetGridItemSelected(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetSelected(frameNode, false);
}

ArkUI_Bool GetGridItemSelected(ArkUINodeHandle node)
{
    CHECK_NULL_RETURN(node, false);
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, false);
    return GridItemModelNG::GetSelected(frameNode);
}

void SetGridItemRowStart(ArkUINodeHandle node, int32_t rowStart)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetRowStart(frameNode, rowStart);
}

void ResetGridItemRowStart(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetRowStart(frameNode, DEFAULT_GRID_ITEM_VALUE);
}

void SetGridItemRowEnd(ArkUINodeHandle node, int32_t rowEnd)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetRowEnd(frameNode, rowEnd);
}

void ResetGridItemRowEnd(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetRowEnd(frameNode, DEFAULT_GRID_ITEM_VALUE);
}

void SetGridItemColumnStart(ArkUINodeHandle node, int32_t columnStart)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetColumnStart(frameNode, columnStart);
}

void ResetGridItemColumnStart(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetColumnStart(frameNode, DEFAULT_GRID_ITEM_VALUE);
}

void SetGridItemColumnEnd(ArkUINodeHandle node, int32_t columnEnd)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetColumnEnd(frameNode, columnEnd);
}

void ResetGridItemColumnEnd(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetColumnEnd(frameNode, DEFAULT_GRID_ITEM_VALUE);
}

void SetGridItemOptions(ArkUINodeHandle node, ArkUI_Int32 style)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetGridItemStyle(frameNode, static_cast<GridItemStyle>(style));
}

void ResetGridItemOptions(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetGridItemStyle(frameNode, GridItemStyle::NONE);
}

ArkUI_Int32 GetGridItemOptions(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<int32_t>(GridItemModelNG::GetGridItemStyle(frameNode));
}

void SetGridItemOnSelect(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onSelectEvent = reinterpret_cast<std::function<void(bool)>*>(callback);
        GridItemModelNG::SetOnSelect(frameNode, std::move(*onSelectEvent));
    } else {
        GridItemModelNG::SetOnSelect(frameNode, nullptr);
    }
}

void ResetGridItemOnSelect(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetOnSelect(frameNode, nullptr);
}

namespace NodeModifier {
void SetOnGridItemSelect(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [extraParam](bool isSelected) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_GRID_ITEM_SELECT;
        event.componentAsyncEvent.data[0].i32 = isSelected;
        SendArkUISyncEvent(&event);
    };
    GridItemModelNG::SetOnSelect(frameNode, std::move(onEvent));
}

void ResetOnGridItemSelect(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetOnSelect(frameNode, nullptr);
}

ArkUINodeHandle CreateFrameNode(ArkUI_Int32 nodeId)
{
    auto frameNode = GridItemModelNG::CreateFrameNode(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(frameNode.GetRawPtr());
}

void* GetEventSetHandler(uint32_t kind)
{
    static const ComponentAsyncEventHandler gridItemNodeAsyncEventHandlers[] = {
        SetOnGridItemSelect,
    };
    if (kind >= sizeof(gridItemNodeAsyncEventHandlers) / sizeof(ComponentAsyncEventHandler)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
        return nullptr;
    }
    return reinterpret_cast<void*>(gridItemNodeAsyncEventHandlers[kind]);
}

void* GetEventResetHandler(uint32_t kind)
{
    static const ResetComponentAsyncEventHandler gridItemNodeResetAsyncEventHandlers[] = {
        ResetOnGridItemSelect,
    };
    if (kind >= sizeof(gridItemNodeResetAsyncEventHandlers) / sizeof(ResetComponentAsyncEventHandler)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyResetComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
        return nullptr;
    }
    return reinterpret_cast<void*>(gridItemNodeResetAsyncEventHandlers[kind]);
}

void CreateStyle(ArkUI_Int32 style)
{
    GridItemModelNG::CreateStatic(static_cast<GridItemStyle>(style));
}

void Create(void* deepRenderFunc, ArkUI_Bool isLazy, ArkUI_Int32 style)
{
    auto gridItemDeepRenderFunc = reinterpret_cast<std::function<void(int32_t)>*>(deepRenderFunc);
    GridItemModelNG::CreateStatic(std::move(*gridItemDeepRenderFunc), isLazy, static_cast<GridItemStyle>(style));
}

void SetForceRebuild(ArkUINodeHandle node, ArkUI_Bool forceRebuild)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetForceRebuild(frameNode, static_cast<bool>(forceRebuild));
}

void SetSelectChangeEvent(ArkUINodeHandle node, void* selectChangeEvent)
{
    CHECK_NULL_VOID(selectChangeEvent);
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto onChangeEvent = reinterpret_cast<std::function<void(bool)>*>(selectChangeEvent);
    GridItemModelNG::SetSelectChangeEvent(frameNode, std::move(*onChangeEvent));
}

void BindContextMenu(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::BindContextMenu(frameNode);
}

#ifndef CROSS_PLATFORM
void CreateStyleImpl(ArkUI_Int32 style)
{
    GetGridItemModelImpl()->Create(static_cast<GridItemStyle>(style));
}

void CreateImpl(void* deepRenderFunc, ArkUI_Bool isLazy, ArkUI_Int32 style)
{
    CHECK_NULL_VOID(deepRenderFunc);
    auto gridItemDeepRenderFunc = reinterpret_cast<std::function<void(int32_t)>*>(deepRenderFunc);
    GetGridItemModelImpl()->Create(std::move(*gridItemDeepRenderFunc), isLazy, static_cast<GridItemStyle>(style));
}

void SetGridItemColumnStartImpl(ArkUINodeHandle node, int32_t columnStart)
{
    GetGridItemModelImpl()->SetColumnStart(columnStart);
}

void SetGridItemColumnEndImpl(ArkUINodeHandle node, int32_t columnEnd)
{
    GetGridItemModelImpl()->SetColumnEnd(columnEnd);
}

void SetGridItemRowStartImpl(ArkUINodeHandle node, int32_t rowStart)
{
    GetGridItemModelImpl()->SetRowStart(rowStart);
}

void SetGridItemRowEndImpl(ArkUINodeHandle node, int32_t rowEnd)
{
    GetGridItemModelImpl()->SetRowEnd(rowEnd);
}

void SetForceRebuildImpl(ArkUINodeHandle node, ArkUI_Bool forceRebuild)
{
    GetGridItemModelImpl()->SetForceRebuild(forceRebuild);
}

void SetGridItemSelectableImpl(ArkUINodeHandle node, ArkUI_Bool selectable)
{
    GetGridItemModelImpl()->SetSelectable(selectable);
}

void SetGridItemOnSelectImpl(ArkUINodeHandle node, void* callback)
{
    CHECK_NULL_VOID(callback);
    auto onSelectEvent = reinterpret_cast<std::function<void(bool)>*>(callback);
    GetGridItemModelImpl()->SetOnSelect(std::move(*onSelectEvent));
}

void SetWidthImpl(ArkUI_CharPtr str, ArkUI_Float64 val, ArkUI_Int32 unit)
{
    CalcDimension dimension;
    if (str) {
        dimension.SetCalcValue(str);
    } else {
        dimension.SetValue(val);
    }
    dimension.SetUnit(static_cast<DimensionUnit>(unit));
    auto gridItem =
        AceType::DynamicCast<GridLayoutItemComponent>(Framework::ViewStackProcessor::GetInstance()->GetMainComponent());
    if (gridItem) {
        gridItem->SetGridItemWidth(dimension);
    }
}

void SetHeightImpl(ArkUI_CharPtr str, ArkUI_Float64 val, ArkUI_Int32 unit)
{
    CalcDimension dimension;
    if (str) {
        dimension.SetCalcValue(str);
    } else {
        dimension.SetValue(val);
    }
    dimension.SetUnit(static_cast<DimensionUnit>(unit));
    auto gridItem =
        AceType::DynamicCast<GridLayoutItemComponent>(Framework::ViewStackProcessor::GetInstance()->GetMainComponent());
    if (gridItem) {
        gridItem->SetGridItemHeight(dimension);
    }
}

#endif
const ArkUIGridItemModifier* GetGridItemDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUIGridItemModifier modifierImpl = {
            .setGridItemSelectable = SetGridItemSelectableImpl,
            .resetGridItemSelectable = nullptr,
            .getGridItemSelectable = nullptr,
            .setGridItemSelected = nullptr,
            .resetGridItemSelected = nullptr,
            .getGridItemSelected = nullptr,
            .setGridItemRowStart = SetGridItemRowStartImpl,
            .resetGridItemRowStart = nullptr,
            .setGridItemRowEnd = SetGridItemRowEndImpl,
            .resetGridItemRowEnd = nullptr,
            .setGridItemColumnStart = SetGridItemColumnStartImpl,
            .resetGridItemColumnStart = nullptr,
            .setGridItemColumnEnd = SetGridItemColumnEndImpl,
            .resetGridItemColumnEnd = nullptr,
            .setGridItemOptions = nullptr,
            .resetGridItemOptions = nullptr,
            .getGridItemOptions = nullptr,
            .setGridItemOnSelect = SetGridItemOnSelectImpl,
            .resetGridItemOnSelect = nullptr,
            .setOnGridItemSelect = nullptr,
            .resetOnGridItemSelect = nullptr,
            .createFrameNode = nullptr,
            .createStyle = CreateStyleImpl,
            .create = CreateImpl,
            .getEventSetHandler = nullptr,
            .getEventResetHandler = nullptr,
            .setForceRebuild = SetForceRebuildImpl,
            .setWidthImpl = SetWidthImpl,
            .setHeightImpl = SetHeightImpl,
            .setSelectChangeEvent = nullptr,
            .bindContextMenu = nullptr,
        };
        CHECK_INITIALIZED_FIELDS_END(modifierImpl, 0, 0, 0); // don't move this line
        return &modifierImpl;
#endif
    }
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIGridItemModifier modifier = {
        .setGridItemSelectable = SetGridItemSelectable,
        .resetGridItemSelectable = ResetGridItemSelectable,
        .getGridItemSelectable = GetGridItemSelectable,
        .setGridItemSelected = SetGridItemSelected,
        .resetGridItemSelected = ResetGridItemSelected,
        .getGridItemSelected = GetGridItemSelected,
        .setGridItemRowStart = SetGridItemRowStart,
        .resetGridItemRowStart = ResetGridItemRowStart,
        .setGridItemRowEnd = SetGridItemRowEnd,
        .resetGridItemRowEnd = ResetGridItemRowEnd,
        .setGridItemColumnStart = SetGridItemColumnStart,
        .resetGridItemColumnStart = ResetGridItemColumnStart,
        .setGridItemColumnEnd = SetGridItemColumnEnd,
        .resetGridItemColumnEnd = ResetGridItemColumnEnd,
        .setGridItemOptions = SetGridItemOptions,
        .resetGridItemOptions = ResetGridItemOptions,
        .getGridItemOptions = GetGridItemOptions,
        .setGridItemOnSelect = SetGridItemOnSelect,
        .resetGridItemOnSelect = ResetGridItemOnSelect,
        .setOnGridItemSelect = SetOnGridItemSelect,
        .resetOnGridItemSelect = ResetOnGridItemSelect,
        .createFrameNode = CreateFrameNode,
        .createStyle = CreateStyle,
        .create = Create,
        .getEventSetHandler = GetEventSetHandler,
        .getEventResetHandler = GetEventResetHandler,
        .setForceRebuild = SetForceRebuild,
        .setWidthImpl = nullptr,
        .setHeightImpl = nullptr,
        .setSelectChangeEvent = SetSelectChangeEvent,
        .bindContextMenu = BindContextMenu,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUIGridItemModifier* GetCJUIGridItemDynamicModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIGridItemModifier modifier = {
        .setGridItemSelectable = SetGridItemSelectable,
        .resetGridItemSelectable = ResetGridItemSelectable,
        .setGridItemSelected = SetGridItemSelected,
        .resetGridItemSelected = ResetGridItemSelected,
        .setGridItemRowStart = SetGridItemRowStart,
        .resetGridItemRowStart = ResetGridItemRowStart,
        .setGridItemRowEnd = SetGridItemRowEnd,
        .resetGridItemRowEnd = ResetGridItemRowEnd,
        .setGridItemColumnStart = SetGridItemColumnStart,
        .resetGridItemColumnStart = ResetGridItemColumnStart,
        .setGridItemColumnEnd = SetGridItemColumnEnd,
        .resetGridItemColumnEnd = ResetGridItemColumnEnd,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace NodeModifier
} // namespace NG
} // namespace OHOS::Ace
