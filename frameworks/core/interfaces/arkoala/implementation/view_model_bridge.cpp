/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!
 */

#include "core/interfaces/arkoala/arkoala_api.h"
#include "arkoala_api_generated.h"
#include "base/utils/utils.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
namespace ViewModel {
    Ark_NodeHandle createTextNode(Ark_Int32 nodeId);
    Ark_NodeHandle createSpanNode(Ark_Int32 nodeId);
    Ark_NodeHandle createImageSpanNode(Ark_Int32 nodeId);
    Ark_NodeHandle createImageNode(Ark_Int32 nodeId);
    Ark_NodeHandle createToggleNode(Ark_Int32 nodeId);
    Ark_NodeHandle createLoadingProgress(Ark_Int32 nodeId);
    Ark_NodeHandle createTextInputNode(Ark_Int32 nodeId);
    Ark_NodeHandle createStackNode(Ark_Int32 nodeId);
    Ark_NodeHandle createScrollNode(Ark_Int32 nodeId);
    Ark_NodeHandle createListNode(Ark_Int32 nodeId);
    Ark_NodeHandle createSwiperNode(Ark_Int32 nodeId);
    Ark_NodeHandle createTextAreaNode(Ark_Int32 nodeId);
    Ark_NodeHandle createButtonNode(Ark_Int32 nodeId);
    Ark_NodeHandle createProgressNode(Ark_Int32 nodeId);
    Ark_NodeHandle createCheckBoxNode(Ark_Int32 nodeId);
    Ark_NodeHandle createColumnNode(Ark_Int32 nodeId);
    Ark_NodeHandle createRowNode(Ark_Int32 nodeId);
    Ark_NodeHandle createFlexNode(Ark_Int32 nodeId);
    Ark_NodeHandle createListItemNode(Ark_Int32 nodeId);
    Ark_NodeHandle createRefreshNode(Ark_Int32 nodeId);
    Ark_NodeHandle createRootNode(Ark_Int32 nodeId);
    Ark_NodeHandle createComponentRootNode(Ark_Int32 nodeId);
#ifdef XCOMPONENT_SUPPORTED
    Ark_NodeHandle createXComponentNode(Ark_Int32 nodeId);
#endif
    Ark_NodeHandle createListItemGroupNode(Ark_Int32 nodeId);
    Ark_NodeHandle createSliderNode(Ark_Int32 nodeId);
    Ark_NodeHandle createCanvasNode(Ark_Int32 nodeId);
    Ark_NodeHandle createDatePickerNode(Ark_Int32 nodeId);
    Ark_NodeHandle createTimePickerNode(Ark_Int32 nodeId);
    Ark_NodeHandle createTextPickerNode(Ark_Int32 nodeId);
    Ark_NodeHandle createCalendarPickerNode(Ark_Int32 nodeId);
    Ark_NodeHandle createCustomNode(Ark_Int32 nodeId);
    Ark_NodeHandle createNavigationNode(Ark_Int32 nodeId);
    Ark_NodeHandle createWaterFlowNode(Ark_Int32 nodeId);
    Ark_NodeHandle createFlowItemNode(Ark_Int32 nodeId);
    Ark_NodeHandle createCircleNode(Ark_Int32 nodeId);
    Ark_NodeHandle createRelativeContainerNode(Ark_Int32 nodeId);
    Ark_NodeHandle createGridNode(Ark_Int32 nodeId);
    Ark_NodeHandle createTabsNode(Ark_Int32 nodeId);
    Ark_NodeHandle createGridItemNode(Ark_Int32 nodeId);
    Ark_NodeHandle createBlankNode(Ark_Int32 nodeId);
    Ark_NodeHandle createDividerNode(Ark_Int32 nodeId);
    Ark_NodeHandle createAlphabetIndexerNode(Ark_Int32 nodeId);
    Ark_NodeHandle createSearchNode(Ark_Int32 nodeId);
    Ark_NodeHandle createGridRowNode(Ark_Int32 nodeId);
    Ark_NodeHandle createGridColNode(Ark_Int32 nodeId);
    Ark_NodeHandle createRadioNode(Ark_Int32 nodeId);
    Ark_NodeHandle createTabContentNode(Ark_Int32 nodeId);
    Ark_NodeHandle createQRCodeNode(Ark_Int32 nodeId);

    void SetCallbackMethod(ArkUIAPICallbackMethod* method);
} // namespace ViewModel

using FrameNodeCreator = Ark_NodeHandle(Ark_Int32 nodeId);

namespace Bridge {
    Ark_NodeHandle CreateNode(GENERATED_Ark_NodeType type, Ark_Int32 id, Ark_Int32 flags)
    {
        if (id == GENERATED_ARKUI_AUTO_GENERATE_NODE_ID) {
            id = ElementRegister::GetInstance()->MakeUniqueId();
        }

        switch (type) {
            case GENERATED_ARKUI_TEXT: return ViewModel::createTextNode(id);
            case GENERATED_ARKUI_SPAN: return ViewModel::createSpanNode(id);
            case GENERATED_ARKUI_IMAGE_SPAN: return ViewModel::createImageSpanNode(id);
            case GENERATED_ARKUI_IMAGE: return ViewModel::createImageNode(id);
            case GENERATED_ARKUI_TOGGLE: return ViewModel::createToggleNode(id);
            case GENERATED_ARKUI_LOADING_PROGRESS: return ViewModel::createLoadingProgress(id);
            case GENERATED_ARKUI_TEXT_INPUT: return ViewModel::createTextInputNode(id);
            case GENERATED_ARKUI_STACK: return ViewModel::createStackNode(id);
            case GENERATED_ARKUI_SCROLL: return ViewModel::createScrollNode(id);
            case GENERATED_ARKUI_LIST: return ViewModel::createListNode(id);
            case GENERATED_ARKUI_SWIPER: return ViewModel::createSwiperNode(id);
            case GENERATED_ARKUI_TEXTAREA: return ViewModel::createTextAreaNode(id);
            case GENERATED_ARKUI_BUTTON: return ViewModel::createButtonNode(id);
            case GENERATED_ARKUI_PROGRESS: return ViewModel::createProgressNode(id);
            case GENERATED_ARKUI_CHECKBOX: return ViewModel::createCheckBoxNode(id);
            case GENERATED_ARKUI_COLUMN: return ViewModel::createColumnNode(id);
            case GENERATED_ARKUI_ROW: return ViewModel::createRowNode(id);
            case GENERATED_ARKUI_FLEX: return ViewModel::createFlexNode(id);
            case GENERATED_ARKUI_LIST_ITEM: return ViewModel::createListItemNode(id);
            case GENERATED_ARKUI_REFRESH: return ViewModel::createRefreshNode(id);
            case GENERATED_ARKUI_ROOT: return ViewModel::createRootNode(id);
            case GENERATED_ARKUI_COMPONENT_ROOT: return ViewModel::createComponentRootNode(id);
#ifdef XCOMPONENT_SUPPORTED
            case GENERATED_ARKUI_XCOMPONENT: return ViewModel::createXComponentNode(id);
#endif
            case GENERATED_ARKUI_LIST_ITEM_GROUP: return ViewModel::createListItemGroupNode(id);
            case GENERATED_ARKUI_SLIDER: return ViewModel::createSliderNode(id);
            case GENERATED_ARKUI_CANVAS: return ViewModel::createCanvasNode(id);
            case GENERATED_ARKUI_DATE_PICKER: return ViewModel::createDatePickerNode(id);
            case GENERATED_ARKUI_TIME_PICKER: return ViewModel::createTimePickerNode(id);
            case GENERATED_ARKUI_TEXT_PICKER: return ViewModel::createTextPickerNode(id);
            case GENERATED_ARKUI_CALENDAR_PICKER: return ViewModel::createCalendarPickerNode(id);
            case GENERATED_ARKUI_CUSTOM: return ViewModel::createCustomNode(id);
            case GENERATED_ARKUI_NAVIGATION: return ViewModel::createNavigationNode(id);
            case GENERATED_ARKUI_WATER_FLOW: return ViewModel::createWaterFlowNode(id);
            case GENERATED_ARKUI_FLOW_ITEM: return ViewModel::createFlowItemNode(id);
            case GENERATED_ARKUI_CIRCLE: return ViewModel::createCircleNode(id);
            case GENERATED_ARKUI_RELATIVE_CONTAINER: return ViewModel::createRelativeContainerNode(id);
            case GENERATED_ARKUI_GRID: return ViewModel::createGridNode(id);
            case GENERATED_ARKUI_TABS: return ViewModel::createTabsNode(id);
            case GENERATED_ARKUI_GRID_ITEM: return ViewModel::createGridItemNode(id);
            case GENERATED_ARKUI_BLANK: return ViewModel::createBlankNode(id);
            case GENERATED_ARKUI_DIVIDER: return ViewModel::createDividerNode(id);
            case GENERATED_ARKUI_ALPHABET_INDEXER: return ViewModel::createAlphabetIndexerNode(id);
            case GENERATED_ARKUI_SEARCH: return ViewModel::createSearchNode(id);
            case GENERATED_ARKUI_GRID_ROW: return ViewModel::createGridRowNode(id);
            case GENERATED_ARKUI_GRID_COL: return ViewModel::createGridColNode(id);
            case GENERATED_ARKUI_RADIO: return ViewModel::createRadioNode(id);
            case GENERATED_ARKUI_TABCONTENT: return ViewModel::createTabContentNode(id);
            case GENERATED_ARKUI_QRCODE: return ViewModel::createQRCodeNode(id);
            default: return nullptr;
        }
    }

    void SetCallbackMethod(GENERATED_Ark_APICallbackMethod* method)
    {
        ViewModel::SetCallbackMethod(reinterpret_cast<ArkUIAPICallbackMethod*>(method));
    }
}
}
