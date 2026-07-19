/**
 * Copyright (c) 2026-2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length,
        r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === 'object' && typeof Reflect.decorate === 'function') r =
        Reflect.decorate(decorators, target, key, desc); else for (var i = decorators.length - 1; i >= 0; i--) if (d =
        decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {
    });
}

const hilog = requireNapi('hilog');
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const resourceManager = requireNapi('resourceManager');
const accessibility = requireNapi('accessibility');

const IMAGE_NODE_HEIGHT = 24;
const IMAGE_NODE_WIDTH = 24;
const ITEM_WIDTH = 0;
const ITEM_HEIGHT = 48;
const ITEM_HEIGHT_INPUT = 32;
const BORDER_WIDTH_HAS = 2;
const BORDER_WIDTH_NONE = 0;
const NODE_HEIGHT = 48;
const LIST_ITEM_HEIGHT_NONE = 0;
const LIST_ITEM_HEIGHT = 48;
const FLAG_NUMBER = 2;
const DRAG_OPACITY = 0.4;
const DRAG_OPACITY_NONE = 1;
const MIN_FONT_SCALE = 1;
const MAX_FONT_SCALE = 2;
const FLAG_LINE_HEIGHT = '1.0vp';
const X_OFF_SET = '0vp';
const Y_OFF_SET = '2.75vp';
const Y_BOTTOM_OFF_SET = '-1.25vp';
const Y_BASE_PLATE_OFF_SET = '1.5vp';
const COLOR_IMAGE_EDIT = '#FFFFFF';
const COLOR_IMAGE_ROW = '#00000000';
const COLOR_SELECT = '#1A0A59F7';
const GRAG_POP_UP_HEIGHT = '48';
const FLOOR_MIN_WIDTH = '128vp';
const FLOOR_MAX_WIDTH = '208vp';
const TEXT_MIN_WIDTH = '80vp';
const TEXT_MAX_WIDTH = '160vp';
const MIN_WIDTH = '112vp';
const MAX_WIDTH = '192vp';
const TRANS_COLOR = '#00FFFFFF';
const DELAY_TIME = 100;
const LEVEL_MARGIN = 12;
const MARGIN_OFFSET = 8;
const TAG = 'TreeViewV2';
const LOG_CODE = 0x3900;
const ENTER_EXIT_DURATION = 2000;
const ACCESSIBILITY_REFOCUS_DELAY_TIME = 300;
const RESOURCE_TYPE_SYMBOL = 40000;
const MAX_SYMBOL_FONT_SCALE = 1.3;
const MIN_SYMBOL_FONT_SCALE = 1;
const ARROW_DOWN = {
    'id': -1,
    'type': 40000,
    params: ['sys.symbol.chevron_down'],
    'bundleName': '__harDefaultBundleName__',
    'moduleName': '__harDefaultModuleName__'
};
const ARROW_DOWN_WITHE = {
    'id': -1,
    'type': 40000,
    params: ['sys.symbol.chevron_down'],
    'bundleName': '__harDefaultBundleName__',
    'moduleName': '__harDefaultModuleName__'
};
const ARROW_RIGHT = {
    'id': -1,
    'type': 40000,
    params: ['sys.symbol.chevron_right'],
    'bundleName': '__harDefaultBundleName__',
    'moduleName': '__harDefaultModuleName__'
};
const ARROW_RIGHT_WITHE = {
    'id': -1,
    'type': 40000,
    params: ['sys.symbol.chevron_right'],
    'bundleName': '__harDefaultBundleName__',
    'moduleName': '__harDefaultModuleName__'
};
var Event;
(function (Event) {
    Event[Event['TOUCH_DOWN'] = 0] = 'TOUCH_DOWN';
    Event[Event['TOUCH_UP'] = 1] = 'TOUCH_UP';
    Event[Event['HOVER'] = 3] = 'HOVER';
    Event[Event['HOVER_OVER'] = 4] = 'HOVER_OVER';
    Event[Event['FOCUS'] = 5] = 'FOCUS';
    Event[Event['BLUR'] = 6] = 'BLUR';
    Event[Event['MOUSE_BUTTON_RIGHT'] = 7] = 'MOUSE_BUTTON_RIGHT';
    Event[Event['DRAG'] = 8] = 'DRAG';
})(Event || (Event = {}));
var MenuOperation;
(function (MenuOperation) {
    MenuOperation[MenuOperation['ADD_NODE'] = 0] = 'ADD_NODE';
    MenuOperation[MenuOperation['REMOVE_NODE'] = 1] = 'REMOVE_NODE';
    MenuOperation[MenuOperation['MODIFY_NODE'] = 2] = 'MODIFY_NODE';
    MenuOperation[MenuOperation['COMMIT_NODE'] = 3] = 'COMMIT_NODE';
})(MenuOperation || (MenuOperation = {}));
var PopUpType;
(function (PopUpType) {
    PopUpType[PopUpType['HINTS'] = 0] = 'HINTS';
    PopUpType[PopUpType['WARNINGS'] = 1] = 'WARNINGS';
})(PopUpType || (PopUpType = {}));
var InputError;
(function (InputError) {
    InputError[InputError['INVALID_ERROR'] = 0] = 'INVALID_ERROR';
    InputError[InputError['LENGTH_ERROR'] = 1] = 'LENGTH_ERROR';
    InputError[InputError['NONE'] = 2] = 'NONE';
})(InputError || (InputError = {}));
var Flag;
(function (Flag) {
    Flag[Flag['DOWN_FLAG'] = 0] = 'DOWN_FLAG';
    Flag[Flag['UP_FLAG'] = 1] = 'UP_FLAG';
    Flag[Flag['NONE'] = 2] = 'NONE';
})(Flag || (Flag = {}));

export var NodeStatus;
(function (NodeStatus) {
    NodeStatus[NodeStatus['EXPAND'] = 0] = 'EXPAND';
    NodeStatus[NodeStatus['COLLAPSE'] = 1] = 'COLLAPSE';
})(NodeStatus || (NodeStatus = {}));

export var InteractionStatus;
(function (InteractionStatus) {
    InteractionStatus[InteractionStatus['NORMAL'] = 0] = 'NORMAL';
    InteractionStatus[InteractionStatus['SELECTED'] = 1] = 'SELECTED';
    InteractionStatus[InteractionStatus['EDIT'] = 2] = 'EDIT';
    InteractionStatus[InteractionStatus['FINISH_EDIT'] = 3] = 'FINISH_EDIT';
    InteractionStatus[InteractionStatus['DRAG_INSERT'] = 4] = 'DRAG_INSERT';
    InteractionStatus[InteractionStatus['FINISH_DRAG_INSERT'] = 5] = 'FINISH_DRAG_INSERT';
})(InteractionStatus || (InteractionStatus = {}));
var CollapseImageType;
(function (CollapseImageType) {
    CollapseImageType[CollapseImageType['ARROW_DOWN'] = 0] = 'ARROW_DOWN';
    CollapseImageType[CollapseImageType['ARROW_RIGHT'] = 1] = 'ARROW_RIGHT';
    CollapseImageType[CollapseImageType['ARROW_DOWN_WHITE'] = 2] = 'ARROW_DOWN_WHITE';
    CollapseImageType[CollapseImageType['ARROW_RIGHT_WHITE'] = 3] = 'ARROW_RIGHT_WHITE';
})(CollapseImageType || (CollapseImageType = {}));
var AccessibilityNodeType;
(function (AccessibilityNodeType) {
    AccessibilityNodeType[AccessibilityNodeType['TEXT'] = 0] = 'TEXT';
    AccessibilityNodeType[AccessibilityNodeType['PLACE'] = 1] = 'PLACE';
    AccessibilityNodeType[AccessibilityNodeType['LIFT'] = 2] = 'LIFT';
})(AccessibilityNodeType || (AccessibilityNodeType = {}));

class Util {
    static isSymbolResource(resourceStr) {
        if (!Util.isResourceType(resourceStr)) {
            return false;
        }
        let resource = resourceStr;
        return resource.type === RESOURCE_TYPE_SYMBOL;
    }

    static isResourceType(resource) {
        if (!resource) {
            return false;
        }
        if (typeof resource === 'string' || typeof resource === 'undefined') {
            return false;
        }
        return true;
    }
}

class TreeViewNodeItemFactory {
    constructor() {
    }

    /**
     * TreeViewNodeItemFactory singleton function
     *
     * @returns TreeViewNodeItemFactory
     */
    static getInstance() {
        if (!TreeViewNodeItemFactory.instance) {
            TreeViewNodeItemFactory.instance = new TreeViewNodeItemFactory();
        }
        return TreeViewNodeItemFactory.instance;
    }

    /**
     * TreeViewNodeItemFactory create default node
     *
     * @returns NodeItemView
     */
    createNode() {
        return {
            imageNode: undefined,
            inputText: new InputText(),
            mainTitleNode: new MainTitleNode(''),
            imageCollapse: undefined,
            fontColor: undefined,
        };
    }

    createNodeByNodeParam(nodeParam) {
        let nodeItemView = this.createNode();
        if (nodeParam.icon) {
            nodeItemView.imageNode = new ImageNode(nodeParam.icon, nodeParam.symbolIconStyle, {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_alpha_content_fourth'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            }, IMAGE_NODE_HEIGHT, IMAGE_NODE_WIDTH, nodeParam.selectedIcon, nodeParam.symbolSelectedIconStyle,
                nodeParam.editIcon, nodeParam.symbolEditIconStyle);
        }
        if (nodeParam.primaryTitle) {
            nodeItemView.mainTitleNode = new MainTitleNode(nodeParam.primaryTitle);
        }
        return nodeItemView;
    }
}

let emptyNodeInfo = {
    isFolder: true,
    icon: '',
    symbolIconStyle: undefined,
    selectedIcon: '',
    symbolSelectedIconStyle: undefined,
    editIcon: '',
    symbolEditIconStyle: undefined,
    container: () => {
    },
    secondaryTitle: '',
    primaryTitle: '',
    parentNodeId: -1,
    currentNodeId: -1,
};

class TreeViewTheme {
    constructor() {
        this.itemSelectedBgColor = '#1A0A59F7';
        this.primaryTitleFontColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_primary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.secondaryTitleFontColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_secondary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.primaryTitleActiveFontColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_text_primary_activated'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.itemPressedBgColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_click_effect'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.itemHoverBgColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_hover'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.borderFocusedColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_focused_outline'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.leftIconColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.icon_secondary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.leftIconActiveColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.icon_secondary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.arrowIconColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.icon_tertiary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
    }

    /**
     * TreeViewTheme singleton function
     *
     * @returns TreeViewNodeItemFactory
     */
    static getInstance() {
        if (!TreeViewTheme.instance) {
            TreeViewTheme.instance = new TreeViewTheme();
        }
        return TreeViewTheme.instance;
    }
}

let NodeInfo = class NodeInfo {
    constructor(node, nodeParam) {
        this.imageSource = '';
        this.symbolSource = undefined;
        this.borderWidth = { has: BORDER_WIDTH_HAS, none: BORDER_WIDTH_NONE };
        this.canShowFlagLine = false;
        this.isOverBorder = false;
        this.canShowBottomFlagLine = false;
        this.isHighLight = false;
        this.isModify = false;
        this.treeViewTheme = TreeViewTheme.getInstance();
        this.fontColor = '';
        this.node = node;
        this.nodeParam = nodeParam;
        this.nodeItemView = TreeViewNodeItemFactory.getInstance().createNodeByNodeParam(nodeParam);
        this.popUpInfo = {
            popUpIsShow: false,
            popUpEnableArrow: false,
            popUpColor: undefined,
            popUpText: '',
            popUpTextColor: undefined,
        };
        this.nodeHeight = NODE_HEIGHT;
        this.nodeLeftPadding = node.nodeLevel * LEVEL_MARGIN + MARGIN_OFFSET;
        this.nodeColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_background'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.nodeIsShow = (this.node.nodeLevel > 0) ? false : true;
        this.listItemHeight = (this.node.nodeLevel > 0) ? LIST_ITEM_HEIGHT_NONE : LIST_ITEM_HEIGHT;
        this.isShowTitle = true;
        this.isShowInputText = false;
        this.isSelected = false;
        this.status = {
            normal: {
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_background_transparent'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
            hover: this.treeViewTheme.itemHoverBgColor,
            press: this.treeViewTheme.itemPressedBgColor,
            selected: this.treeViewTheme.itemSelectedBgColor,
            highLight: {
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_activated'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            }
        };
        this.nodeBorder = {
            borderWidth: BORDER_WIDTH_NONE,
            borderColor: this.treeViewTheme.borderFocusedColor,
            borderRadius: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_corner_radius_clicked'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            }
        };
        this.flagLineLeftMargin = node.nodeLevel * LEVEL_MARGIN + MARGIN_OFFSET;
    }

    /**
     * NodeInfo add collapse image
     *
     * @param isHasChildNode whether node has child node
     */
    addImageCollapse(isHasChildNode) {
        if (isHasChildNode) {
            this.nodeItemView.imageCollapse =
                CollapseImageNodeFlyweightFactory.getCollapseImageNodeByType(CollapseImageType.ARROW_RIGHT);
        } else {
            this.nodeItemView.imageCollapse = undefined;
        }
    }

    /**
     * NodeInfo add expand image
     *
     * @param isHasChildNode whether node has child node
     */
    addImageExpand(isHasChildNode) {
        if (isHasChildNode) {
            this.nodeItemView.imageCollapse =
                CollapseImageNodeFlyweightFactory.getCollapseImageNodeByType(CollapseImageType.ARROW_DOWN);
        } else {
            this.nodeItemView.imageCollapse = undefined;
        }
    }

    setFontColor(color) {
        this.fontColor = color;
    }

    getFontColor() {
        return this.fontColor;
    }

    getPopUpInfo() {
        return this.popUpInfo;
    }

    setPopUpIsShow(isShow) {
        this.popUpInfo.popUpIsShow = isShow;
    }

    setPopUpEnableArrow(popUpEnableArrow) {
        this.popUpInfo.popUpEnableArrow = popUpEnableArrow;
    }

    setPopUpColor(color) {
        this.popUpInfo.popUpColor = color;
    }

    setPopUpText(text) {
        this.popUpInfo.popUpText = text;
    }

    setPopUpTextColor(popUpTextColor) {
        this.popUpInfo.popUpTextColor = popUpTextColor;
    }

    getIsShowTitle() {
        return this.isShowTitle;
    }

    getIsShowInputText() {
        return this.isShowInputText;
    }

    setTitleAndInputTextStatus(isModify) {
        if (isModify) {
            this.isShowTitle = false;
            this.isShowInputText = true;
        } else {
            this.isShowTitle = true;
            this.isShowInputText = false;
        }
    }

    handleImageCollapseAfterAddNode(isAddImageCollapse) {
        // listTree this node already has ImageCollapse.
        if (isAddImageCollapse) {
            this.nodeItemView.imageCollapse =
                CollapseImageNodeFlyweightFactory.getCollapseImageNodeByType(CollapseImageType.ARROW_DOWN);
        } else {
            this.nodeItemView.imageCollapse = undefined;
        }
    }

    setNodeColor(nodeColor) {
        if (nodeColor === undefined) {
            return;
        }
        this.nodeColor = nodeColor;
    }

    getNodeColor() {
        return this.nodeColor;
    }

    setListItemHeight(listItemHeight) {
        this.listItemHeight = listItemHeight;
    }

    getListItemHeight() {
        return this.listItemHeight;
    }

    getNodeCurrentNodeId() {
        return this.node.currentNodeId;
    }

    getNodeParentNodeId() {
        return this.node.parentNodeId;
    }

    getNodeLeftPadding() {
        return this.nodeLeftPadding;
    }

    getNodeHeight() {
        return this.nodeHeight;
    }

    setNodeIsShow(nodeIsShow) {
        this.nodeIsShow = nodeIsShow;
    }

    getNodeIsShow() {
        return this.nodeIsShow;
    }

    getNodeItem() {
        return this.nodeItemView;
    }

    getNodeStatus() {
        return this.status;
    }

    getNodeBorder() {
        return this.nodeBorder;
    }

    setNodeBorder(isClearFocusStatus) {
        this.nodeBorder.borderWidth = isClearFocusStatus ? this.borderWidth.has : this.borderWidth.none;
    }

    getChildNodeInfo() {
        return this.node.childNodeInfo;
    }

    getMenu() {
        return this.nodeParam.container;
    }

    setIsSelected(isSelected) {
        this.isSelected = isSelected;
    }

    getIsSelected() {
        return this.isSelected;
    }

    getNodeInfoData() {
        return this.nodeParam;
    }

    /* To gain the tree Node(NodeItem) while to alter node. */
    getNodeInfoNode() {
        return this.node;
    }

    getIsFolder() {
        return this.nodeParam.isFolder;
    }

    setCanShowFlagLine(canShowFlagLine) {
        this.canShowFlagLine = canShowFlagLine;
    }

    getCanShowFlagLine() {
        return this.canShowFlagLine;
    }

    setFlagLineLeftMargin(currentNodeLevel) {
        if (currentNodeLevel === undefined) {
            return;
        }
        this.flagLineLeftMargin = currentNodeLevel * LEVEL_MARGIN + MARGIN_OFFSET; // calculate
    }

    getFlagLineLeftMargin() {
        return this.flagLineLeftMargin;
    }

    getNodeLevel() {
        return this.node.nodeLevel;
    }

    setIsOverBorder(isOverBorder) {
        this.isOverBorder = isOverBorder;
    }

    getIsOverBorder() {
        return this.isOverBorder;
    }

    setCanShowBottomFlagLine(canShowBottomFlagLine) {
        this.canShowBottomFlagLine = canShowBottomFlagLine;
    }

    getCanShowBottomFlagLine() {
        return this.canShowBottomFlagLine;
    }

    setIsHighLight(isHighLight) {
        this.isHighLight = isHighLight;
    }

    getIsHighLight() {
        return this.isHighLight;
    }

    setIsModify(isModify) {
        this.isModify = isModify;
    }

    getIsModify() {
        return this.isModify;
    }
};
__decorate([
    Trace
], NodeInfo.prototype, 'imageSource', void 0);
__decorate([
    Trace
], NodeInfo.prototype, 'symbolSource', void 0);
__decorate([
    Trace
], NodeInfo.prototype, 'nodeHeight', void 0);
__decorate([
    Trace
], NodeInfo.prototype, 'nodeItemView', void 0);
__decorate([
    Trace
], NodeInfo.prototype, 'nodeLeftPadding', void 0);
__decorate([
    Trace
], NodeInfo.prototype, 'nodeColor', void 0);
__decorate([
    Trace
], NodeInfo.prototype, 'nodeIsShow', void 0);
__decorate([
    Trace
], NodeInfo.prototype, 'status', void 0);
__decorate([
    Trace
], NodeInfo.prototype, 'nodeBorder', void 0);
__decorate([
    Trace
], NodeInfo.prototype, 'popUpInfo', void 0);
__decorate([
    Trace
], NodeInfo.prototype, 'listItemHeight', void 0);
__decorate([
    Trace
], NodeInfo.prototype, 'isShowTitle', void 0);
__decorate([
    Trace
], NodeInfo.prototype, 'isShowInputText', void 0);
__decorate([
    Trace
], NodeInfo.prototype, 'isSelected', void 0);
__decorate([
    Trace
], NodeInfo.prototype, 'nodeParam', void 0);
__decorate([
    Trace
], NodeInfo.prototype, 'node', void 0);
__decorate([
    Trace
], NodeInfo.prototype, 'canShowFlagLine', void 0);
__decorate([
    Trace
], NodeInfo.prototype, 'isOverBorder', void 0);
__decorate([
    Trace
], NodeInfo.prototype, 'canShowBottomFlagLine', void 0);
__decorate([
    Trace
], NodeInfo.prototype, 'isHighLight', void 0);
__decorate([
    Trace
], NodeInfo.prototype, 'flagLineLeftMargin', void 0);
__decorate([
    Trace
], NodeInfo.prototype, 'isModify', void 0);
__decorate([
    Trace
], NodeInfo.prototype, 'fontColor', void 0);
NodeInfo = __decorate([
    ObservedV2
], NodeInfo);

export { NodeInfo };

/**
 * Declare class TreeListenerV2.
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 26
 */
export class TreeListenerV2 {
    constructor() {
        this.nodeClickEvents = [];
        this.nodeClickOnceEvents = [];
        this.nodeAddEvents = [];
        this.nodeAddOnceEvents = [];
        this.nodeDeleteEvents = [];
        this.nodeDeleteOnceEvents = [];
        this.nodeModifyEvents = [];
        this.nodeModifyOnceEvents = [];
        this.nodeMoveEvents = [];
        this.nodeMoveOnceEvents = [];
    }

    /**
     * Node click event registration and processing.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 26
     */
    onNodeClick(callback) {
        this.nodeClickEvents.push(callback);
    }

    /**
     * Node click event registration and processing (once).
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 26
     */
    onceNodeClick(callback) {
        this.nodeClickOnceEvents.push(callback);
    }

    /**
     * Destroy node click callback event.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 26
     */
    offNodeClick(callback) {
        if (callback === undefined) {
            this.nodeClickEvents = [];
            this.nodeClickOnceEvents = [];
        } else {
            let index = this.nodeClickEvents.indexOf(callback);
            if (index >= 0) {
                this.nodeClickEvents.splice(index, 1);
            }
        }
    }

    /**
     * Node add event registration and processing.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 26
     */
    onNodeAdd(callback) {
        this.nodeAddEvents.push(callback);
    }

    /**
     * Node add event registration and processing (once).
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 26
     */
    onceNodeAdd(callback) {
        this.nodeAddOnceEvents.push(callback);
    }

    /**
     * Destroy node add callback event.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 26
     */
    offNodeAdd(callback) {
        if (callback === undefined) {
            this.nodeAddEvents = [];
            this.nodeAddOnceEvents = [];
        } else {
            let index = this.nodeAddEvents.indexOf(callback);
            if (index >= 0) {
                this.nodeAddEvents.splice(index, 1);
            }
        }
    }

    /**
     * Node delete event registration and processing.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 26
     */
    onNodeDelete(callback) {
        this.nodeDeleteEvents.push(callback);
    }

    /**
     * Node delete event registration and processing (once).
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 26
     */
    onceNodeDelete(callback) {
        this.nodeDeleteOnceEvents.push(callback);
    }

    /**
     * Destroy node delete callback event.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 26
     */
    offNodeDelete(callback) {
        if (callback === undefined) {
            this.nodeDeleteEvents = [];
            this.nodeDeleteOnceEvents = [];
        } else {
            let index = this.nodeDeleteEvents.indexOf(callback);
            if (index >= 0) {
                this.nodeDeleteEvents.splice(index, 1);
            }
        }
    }

    /**
     * Node modify event registration and processing.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 26
     */
    onNodeModify(callback) {
        this.nodeModifyEvents.push(callback);
    }

    /**
     * Node modify event registration and processing (once).
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 26
     */
    onceNodeModify(callback) {
        this.nodeModifyOnceEvents.push(callback);
    }

    /**
     * Destroy node modify callback event.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 26
     */
    offNodeModify(callback) {
        if (callback === undefined) {
            this.nodeModifyEvents = [];
            this.nodeModifyOnceEvents = [];
        } else {
            let index = this.nodeModifyEvents.indexOf(callback);
            if (index >= 0) {
                this.nodeModifyEvents.splice(index, 1);
            }
        }
    }

    /**
     * Node move event registration and processing.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 26
     */
    onNodeMove(callback) {
        this.nodeMoveEvents.push(callback);
    }

    /**
     * Node move event registration and processing (once).
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 26
     */
    onceNodeMove(callback) {
        this.nodeMoveOnceEvents.push(callback);
    }

    /**
     * Destroy node move callback event.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 26
     */
    offNodeMove(callback) {
        if (callback === undefined) {
            this.nodeMoveEvents = [];
            this.nodeMoveOnceEvents = [];
        } else {
            let index = this.nodeMoveEvents.indexOf(callback);
            if (index >= 0) {
                this.nodeMoveEvents.splice(index, 1);
            }
        }
    }

    /**
     * Triggers all callbacks of node click event.
     * @since 26
     */
    emitNodeClick(argument) {
        this.triggerCallbacks(this.nodeClickEvents, argument);
        this.triggerOnceCallbacks(this.nodeClickOnceEvents, argument);
    }

    /**
     * Triggers all callbacks of node add event.
     * @since 26
     */
    emitNodeAdd(argument) {
        this.triggerCallbacks(this.nodeAddEvents, argument);
        this.triggerOnceCallbacks(this.nodeAddOnceEvents, argument);
    }

    /**
     * Triggers all callbacks of node delete event.
     * @since 26
     */
    emitNodeDelete(argument) {
        this.triggerCallbacks(this.nodeDeleteEvents, argument);
        this.triggerOnceCallbacks(this.nodeDeleteOnceEvents, argument);
    }

    /**
     * Triggers all callbacks of node modify event.
     * @since 26
     */
    emitNodeModify(argument) {
        this.triggerCallbacks(this.nodeModifyEvents, argument);
        this.triggerOnceCallbacks(this.nodeModifyOnceEvents, argument);
    }

    /**
     * Triggers all callbacks of node move event.
     * @since 26
     */
    emitNodeMove(argument) {
        this.triggerCallbacks(this.nodeMoveEvents, argument);
        this.triggerOnceCallbacks(this.nodeMoveOnceEvents, argument);
    }

    triggerCallbacks(callbacks, argument) {
        for (let i = 0; i < callbacks.length; i++) {
            try {
                callbacks[i](argument);
            } catch (e) {
                hilog.error(LOG_CODE, TAG, 'triggerCallbacks error');
            }
        }
    }

    triggerOnceCallbacks(callbacks, argument) {
        for (let i = 0; i < callbacks.length; i++) {
            try {
                callbacks[i](argument);
            } catch (e) {
                hilog.error(LOG_CODE, TAG, 'triggerOnceCallbacks error');
            }
        }
        callbacks.splice(0, callbacks.length);
    }
}

/**
 * Declare class TreeListenerManagerV2.
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 26
 */
export class TreeListenerManagerV2 {
    constructor() {
        this.appEventBus = new TreeListenerV2();
    }

    /**
     * Get instance of treeListenerManagerV2.
     * @return treeListenerManagerV2 instance.
     * @static
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 26
     */
    static getInstance() {
        if (AppStorage.Get('app_key_event_bus_v2') === undefined) {
            AppStorage.SetOrCreate('app_key_event_bus_v2', new TreeListenerManagerV2());
        }
        return AppStorage.Get('app_key_event_bus_v2');
    }

    /**
     * Get treeListenerV2.
     * @return treeListenerV2 object
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 26
     */
    getTreeListener() {
        return this.appEventBus;
    }
}
TreeListenerManagerV2.APP_KEY_EVENT_BUS = 'app_key_event_bus_v2';

export class TreeViewV2 extends ViewV2 {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
        super(parent, elmtId, extraInfo);
        this.initParam('treeControllerV2',
            (params && 'treeControllerV2' in params) ? params.treeControllerV2 : new TreeControllerV2());
        this.nodeList = [];
        this.listNodeDataSource = new ListNodeDataSource();
        this.item = null;
        this.touchCount = 0;
        this.dropSelectedIndex = 0;
        this.viewLastIndex = -1;
        this.followingSystemFontScale = false;
        this.maxAppFontScale = 1;
        this.listItemBgColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_background_transparent'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.allParentNode = [];
        this.treeViewTheme = TreeViewTheme.getInstance();
        this.clickButtonFlag = true;
        this.accessibilityNodeType = AccessibilityNodeType.TEXT;
        this.isAccessibilityEnabled = accessibility.isScreenReaderOpenSync();
        this.listTreeViewMenu = 'listTreeViewMenu' in params ? params.listTreeViewMenu : this.NullBuilder;
        this.MAX_CN_LENGTH = 254;
        this.MAX_EN_LENGTH = 255;
        this.INITIAL_INVALID_VALUE = -1;
        this.MAX_TOUCH_DOWN_COUNT = 0;
        this.isMultiPress = false;
        this.touchDownCount = this.INITIAL_INVALID_VALUE;
        this.appEventBus = TreeListenerManagerV2.getInstance().getTreeListener();
        this.itemPadding = {
            left: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_card_margin_start'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
            right: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_card_margin_end'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
            top: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_margin_vertical'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
            bottom: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_margin_vertical'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
        };
        this.textInputPadding = {
            left: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level0'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
            right: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level0'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
            top: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level0'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
            bottom: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level0'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
        };
        this.finalizeConstruction();
    }

    resetStateVarsOnReuse(params) {
        this.resetParam('treeControllerV2',
            (params && 'treeControllerV2' in params) ? params.treeControllerV2 : new TreeControllerV2());
        this.nodeList = [];
        this.item = null;
        this.touchCount = 0;
        this.dropSelectedIndex = 0;
        this.viewLastIndex = -1;
        this.followingSystemFontScale = false;
        this.maxAppFontScale = 1;
        this.listItemBgColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_background_transparent'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.allParentNode = [];
        this.treeViewTheme = TreeViewTheme.getInstance();
        this.clickButtonFlag = true;
        this.accessibilityNodeType = AccessibilityNodeType.TEXT;
        this.isAccessibilityEnabled = accessibility.isScreenReaderOpenSync();
        this.listTreeViewMenu = 'listTreeViewMenu' in params ? params.listTreeViewMenu : this.NullBuilder;
    }

    NullBuilder(parent = null) {
    }
    ;

    onWillApplyTheme(theme) {
        this.treeViewTheme.itemSelectedBgColor = theme.colors.interactiveSelect;
        this.treeViewTheme.itemPressedBgColor = theme.colors.interactivePressed;
        this.treeViewTheme.itemHoverBgColor = theme.colors.interactiveHover;
        this.treeViewTheme.primaryTitleFontColor = theme.colors.fontPrimary;
        this.treeViewTheme.secondaryTitleFontColor = theme.colors.fontSecondary;
        this.treeViewTheme.primaryTitleActiveFontColor = theme.colors.interactiveActive;
        this.treeViewTheme.borderFocusedColor = theme.colors.interactiveFocus;
        this.treeViewTheme.leftIconColor = theme.colors.iconSecondary;
        this.treeViewTheme.leftIconActiveColor = theme.colors.interactiveActive;
        this.treeViewTheme.arrowIconColor = theme.colors.iconPrimary;
        this.treeControllerV2.treeViewTheme = this.treeViewTheme;
    }

    aboutToAppear() {
        if (this.treeControllerV2 !== null) {
            this.listNodeDataSource = this.treeControllerV2.getListNodeDataSource();
            this.nodeList = this.treeControllerV2.getListNodeDataSource().listNode;
            this.item = this.treeControllerV2.getListNodeDataSource().listNode;
        }
        let uiContent = this.getUIContext();
        this.followingSystemFontScale = uiContent.isFollowingSystemFontScale();
        this.maxAppFontScale = uiContent.getMaxFontScale();
        accessibility.on('screenReaderStateChange', (state) => {
            this.isAccessibilityEnabled = state;
        });
    }

    aboutToDisappear() {
        accessibility.off('screenReaderStateChange');
    }

    decideFontScale() {
        let uiContent = this.getUIContext();
        let systemFontScale = uiContent.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.followingSystemFontScale) {
            return 1;
        }
        return Math.min(systemFontScale, this.maxAppFontScale, MAX_FONT_SCALE);
    }

    decideSymbolFontScale(isSymbol) {
        if (!isSymbol || !this.followingSystemFontScale) {
            return 1;
        }
        let uiContent = this.getUIContext();
        let systemFontScale = uiContent.getHostContext()?.config?.fontSizeScale ?? 1;
        let symbolFontSizeScale = Math.min(systemFontScale, this.maxAppFontScale, MAX_SYMBOL_FONT_SCALE);
        return Math.max(symbolFontSizeScale, MIN_SYMBOL_FONT_SCALE);
    }

    popupForShowTitle(text, backgroundColor, fontColor, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.backgroundColor(backgroundColor);
            Row.border({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_elements_margin_horizontal_l'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                }
            });
            Row.padding({
                left: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_elements_margin_horizontal_l'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                right: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_elements_margin_horizontal_l'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                top: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_card_margin_middle'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                bottom: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_card_margin_middle'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(text);
            Text.fontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_body2'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Text.fontWeight('regular');
            Text.fontColor(fontColor);
            Text.minFontScale(MIN_FONT_SCALE);
            Text.maxFontScale(this.decideFontScale());
        }, Text);
        Text.pop();
        Row.pop();
    }

    builder(parent = null) {
        this.listTreeViewMenu.bind(this)();
    }

    /* Set the popup of dragging node. */
    draggingPopup(item, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.id(`treeView_node_lift${item.getNodeCurrentNodeId()}`);
            Row.constraintSize({
                minWidth: this.listNodeDataSource.getDragPopupPara().floorConstraintSize.minWidth,
                maxWidth: this.listNodeDataSource.getDragPopupPara().floorConstraintSize.maxWidth,
            });
            Row.height(this.listNodeDataSource.getDragPopupPara().height);
            Row.backgroundColor(this.listNodeDataSource.getDragPopupPara().backgroundColor);
            Row.padding({
                start: LengthMetrics.resource(this.listNodeDataSource.getDragPopupPara().padding.left),
                end: LengthMetrics.resource(this.listNodeDataSource.getDragPopupPara().padding.right),
            });
            Row.shadow(this.listNodeDataSource.getDragPopupPara().shadow);
            Row.borderRadius(this.listNodeDataSource.getDragPopupPara().borderRadius);
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (item.getNodeItem().imageNode) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.backgroundColor(COLOR_IMAGE_ROW);
                        Row.margin({
                            end: getLengthMetricsByResourceOrNumber(item.getNodeItem().imageNode?.itemRightMargin)
                        });
                        Row.height(item.getNodeItem().imageNode?.itemHeight *
                            this.decideSymbolFontScale(item.getNodeItem().imageNode?.symbolNormalSource !== undefined ||
                                Util.isSymbolResource(item.getNodeItem().imageNode?.normalSource)));
                        Row.width(item.getNodeItem().imageNode?.itemWidth *
                            this.decideSymbolFontScale(item.getNodeItem().imageNode?.symbolNormalSource !== undefined ||
                                Util.isSymbolResource(item.getNodeItem().imageNode?.normalSource)));
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (item.getNodeItem().imageNode?.symbolNormalSource) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.attributeModifier.bind(this)(item.getNodeItem()
                                        .imageNode?.symbolNormalSource);
                                    SymbolGlyph.fontSize(`${item.getNodeItem().imageNode?.itemHeight *
                                        this.decideSymbolFontScale(true)}vp`);
                                    SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                    SymbolGlyph.opacity(this.listNodeDataSource.getDragPopupPara().imageOpacity);
                                }, SymbolGlyph);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    If.create();
                                    if (Util.isSymbolResource(item.getNodeItem().imageNode?.normalSource)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                SymbolGlyph.create(item.getNodeItem().imageNode?.normalSource);
                                                SymbolGlyph.fontSize(`${item.getNodeItem().imageNode?.itemHeight *
                                                    this.decideSymbolFontScale(true)}vp`);
                                                SymbolGlyph.opacity(this.listNodeDataSource.getDragPopupPara()
                                                    .imageOpacity);
                                            }, SymbolGlyph);
                                        });
                                    } else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                Image.create(item.getNodeItem().imageNode?.normalSource);
                                                Image.objectFit(ImageFit.Contain);
                                                Image.height(item.getNodeItem().imageNode?.itemHeight);
                                                Image.width(item.getNodeItem().imageNode?.itemWidth);
                                                Image.opacity(this.listNodeDataSource.getDragPopupPara().imageOpacity);
                                                Image.matchTextDirection((item.getNodeItem()
                                                    .imageCollapse?.collapseSource === ARROW_RIGHT ||
                                                    item.getNodeItem().imageCollapse?.collapseSource ===
                                                        ARROW_RIGHT_WITHE) ? true : false);
                                            }, Image);
                                        });
                                    }
                                }, If);
                                If.pop();
                            });
                        }
                    }, If);
                    If.pop();
                    Row.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.constraintSize({
                minWidth: item.getNodeItem().imageNode ?
                    this.listNodeDataSource.getDragPopupPara().textConstraintSize.minWidth1 :
                    this.listNodeDataSource.getDragPopupPara().textConstraintSize.minWidth2,
                maxWidth: item.getNodeItem().imageNode ?
                    this.listNodeDataSource.getDragPopupPara().textConstraintSize.maxWidth1 :
                    this.listNodeDataSource.getDragPopupPara().textConstraintSize.maxWidth2,
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (item.getNodeItem().mainTitleNode && item.getIsShowTitle()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(item.getNodeItem().mainTitleNode?.title);
                        Text.maxLines(1);
                        Text.minFontScale(MIN_FONT_SCALE);
                        Text.maxFontScale(this.decideFontScale());
                        Text.fontSize(item.getNodeItem().mainTitleNode?.size);
                        Text.fontColor(this.listNodeDataSource.getDragPopupPara().fontColor);
                        Text.fontWeight(this.listNodeDataSource.getDragPopupPara().fontWeight);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                    }, Text);
                    Text.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Row.pop();
        Row.pop();
    }

    clearLastIndexColor() {
        if (this.viewLastIndex === -1 || this.viewLastIndex >= this.nodeList.length) {
            return;
        }
        this.setImageSources(this.viewLastIndex, InteractionStatus.NORMAL);
        this.listNodeDataSource.setImageSource(this.viewLastIndex, InteractionStatus.NORMAL);
        this.nodeList[this.viewLastIndex].setNodeColor({
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_background_transparent'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        });
        this.nodeList[this.viewLastIndex].fontColor = this.treeViewTheme.primaryTitleFontColor;
        this.listNodeDataSource.listNode[this.viewLastIndex].setNodeColor({
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_background_transparent'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        });
        this.listNodeDataSource.listNode[this.viewLastIndex].fontColor = this.treeViewTheme.primaryTitleFontColor;
        this.listNodeDataSource.listNode[this.viewLastIndex].setIsSelected(false);
        this.listNodeDataSource.listNode[this.viewLastIndex].imageSource =
            this.listNodeDataSource.listNode[this.viewLastIndex].getNodeItem()
                .imageNode?.source;
        this.listNodeDataSource.listNode[this.viewLastIndex].symbolSource =
            this.listNodeDataSource.listNode[this.viewLastIndex].getNodeItem()
                .imageNode?.symbolSource;
    }

    setImageSources(index, interactionStatus) {
        let nodeInfo = this.nodeList[index];
        nodeInfo.setIsSelected(interactionStatus === InteractionStatus.SELECTED ||
            interactionStatus === InteractionStatus.EDIT || interactionStatus === InteractionStatus.FINISH_EDIT);
        if (nodeInfo.getNodeItem().mainTitleNode !== null && interactionStatus !== InteractionStatus.DRAG_INSERT &&
            interactionStatus !== InteractionStatus.FINISH_DRAG_INSERT) {
            nodeInfo.getNodeItem()
                .mainTitleNode?.setMainTitleSelected(interactionStatus === InteractionStatus.SELECTED ||
                    interactionStatus === InteractionStatus.FINISH_EDIT);
        }
        if (nodeInfo.getNodeItem().imageNode !== null) {
            nodeInfo.getNodeItem().imageNode?.setImageSource(interactionStatus);
        }
    }

    touchInner(itemInner, event) {
        this.viewLastIndex = this.listNodeDataSource.getLastIndex();
        let index = this.listNodeDataSource.findIndex(itemInner.getNodeCurrentNodeId());
        if (event.type === TouchType.Down) {
            if (index !== this.viewLastIndex) {
                this.clearLastIndexColor();
                this.listNodeDataSource.lastIndex = index;
                this.listNodeDataSource.setClickIndex(index);
            }
        }
        if (event.type === TouchType.Up) {
            this.listNodeDataSource.listNode[index].setIsSelected(true);
            this.listNodeDataSource.setImageSource(index, InteractionStatus.SELECTED);
            if (this.listNodeDataSource.listNode[index].getNodeItem().imageNode !== null) {
                this.listNodeDataSource.listNode[index].imageSource = this.listNodeDataSource.listNode[index]
                    .getNodeItem().imageNode?.source;
                this.listNodeDataSource.listNode[index].symbolSource = this.listNodeDataSource.listNode[index]
                    .getNodeItem().imageNode?.symbolSource;
            }
            if (index !== this.viewLastIndex) {
                this.clearLastIndexColor();
                this.listNodeDataSource.lastIndex = index;
                this.listNodeDataSource.setClickIndex(index);
            }
            this.viewLastIndex = index;
        }
        if (this.listNodeDataSource.getLastIndex() !== -1 && index !== this.listNodeDataSource.getLastIndex()) {
            this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false,
                this.listNodeDataSource.getLastIndex());
            this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(),
                MenuOperation.COMMIT_NODE);
        }
    }

    clickInner(itemInner) {
        this.viewLastIndex = this.listNodeDataSource.getLastIndex();
        let index = this.listNodeDataSource.findIndex(itemInner.getNodeCurrentNodeId());
        if (index !== this.viewLastIndex) {
            this.clearLastIndexColor();
            this.listNodeDataSource.lastIndex = index;
            this.listNodeDataSource.setClickIndex(index);
        }
        this.listNodeDataSource.listNode[index].setIsSelected(true);
        this.listNodeDataSource.setImageSource(index, InteractionStatus.SELECTED);
        if (this.listNodeDataSource.listNode[index].getNodeItem().imageNode !== null) {
            this.listNodeDataSource.listNode[index].imageSource = this.listNodeDataSource.listNode[index]
                .getNodeItem().imageNode?.source;
            this.listNodeDataSource.listNode[index].symbolSource = this.listNodeDataSource.listNode[index]
                .getNodeItem().imageNode?.symbolSource;
        }
        if (index !== this.viewLastIndex) {
            this.clearLastIndexColor();
            this.listNodeDataSource.lastIndex = index;
            this.listNodeDataSource.setClickIndex(index);
        }
        this.viewLastIndex = index;
        if (this.listNodeDataSource.getLastIndex() !== -1 && index !== this.listNodeDataSource.getLastIndex()) {
            this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false,
                this.listNodeDataSource.getLastIndex());
            this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(),
                MenuOperation.COMMIT_NODE);
        }
    }

    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            List.create({});
            List.onDragMove((event, extraParams) => {
                if (this.isMultiPress) {
                    hilog.error(LOG_CODE, TAG, 'drag error, a item has been dragged');
                    return;
                }
                let nodeHeight = LIST_ITEM_HEIGHT;
                /* flag the position of the focus on the node. */
                let flag = Math.floor(event.getY() /
                    (nodeHeight / FLAG_NUMBER)) %
                    FLAG_NUMBER ? Flag.DOWN_FLAG : Flag.UP_FLAG;
                /* Record the node position to which the dragged node moves. */
                let index = JSON.parse(extraParams).insertIndex;
                /* Handle the situation where the focus(index) exceeds the list area. */
                let isOverBorder = false;
                if (index >= this.listNodeDataSource.totalCount()) {
                    flag = Flag.DOWN_FLAG;
                    index = this.listNodeDataSource.totalCount() - 1;
                    this.listNodeDataSource.getData(index)?.setIsOverBorder(true);
                    isOverBorder = true;
                } else {
                    this.listNodeDataSource.getData(index)?.setIsOverBorder(false);
                }
                let currentNodeInfo = this.listNodeDataSource.getData(index);
                let currentNodeId = currentNodeInfo?.getNodeCurrentNodeId();
                /**
                 * handle a situation that 'draggingCurrentNodeId' is parent of 'insertNodeCurrentNodeId';
                 * do not perform some functions.
                 */
                if (index !== this.listNodeDataSource.getLastPassIndex() && this.listNodeDataSource.getIsInnerDrag()) {
                    let isParentNodeOfInsertNode = this.listNodeDataSource.getIsParentOfInsertNode(currentNodeId);
                    if (isParentNodeOfInsertNode) {
                        this.listNodeDataSource.setPassIndex(index);
                        if (currentNodeId !== undefined) {
                            this.listNodeDataSource.clearTimeOutAboutDelayHighLightAndExpand(this.listNodeDataSource.findIndex(currentNodeId));
                        }
                        this.listNodeDataSource.setFlag(Flag.NONE);
                        return;
                    }
                }
                this.listNodeDataSource.setLastPassIndex(index);
                /* Set the visibility of the flag line. */
                this.listNodeDataSource.setVisibility(flag, index - 1, isOverBorder, this.allParentNode);
                /* Automatically HighLight one second delay and expand after two second delay. */
                if (currentNodeId !== undefined &&
                    currentNodeId !== this.listNodeDataSource.getDraggingCurrentNodeId()) {
                    this.listNodeDataSource.delayHighLightAndExpandNode(this.listNodeDataSource.findIndex(currentNodeId),
                        currentNodeId, index);
                }
            });
            List.onDragEnter((event, extraParams) => {
                if (this.listNodeDataSource.getIsInnerDrag()) {
                    this.listNodeDataSource.setIsDrag(true);
                    /* set the opacity of the dragging node. */
                    let draggingNodeOpacity = DRAG_OPACITY;
                    this.listNodeDataSource.setListItemOpacity(draggingNodeOpacity);
                }
            });
            List.onDragLeave((event, extraParams) => {
                this.listNodeDataSource.hideLastLine();
                this.listNodeDataSource.clearLastTimeoutHighLight();
                this.listNodeDataSource.clearLastTimeoutExpand();
                let draggingNodeOpacity = DRAG_OPACITY_NONE;
                this.listNodeDataSource.setListItemOpacity(draggingNodeOpacity);
                this.listNodeDataSource.setIsDrag(false);
                this.listNodeDataSource.notifyDataReload();
            });
            List.onDrop((event, extraParams) => {
                this.accessibilityNodeType = AccessibilityNodeType.PLACE;
                this.listNodeDataSource.clearLastTimeoutExpand();
                let draggingNodeOpacity = DRAG_OPACITY_NONE;
                this.listNodeDataSource.setListItemOpacity(draggingNodeOpacity);
                let insertNodeIndex = JSON.parse(extraParams).insertIndex;
                let currentNodeIndex = this.dropSelectedIndex;
                if (currentNodeIndex - 1 > this.listNodeDataSource.totalCount() || currentNodeIndex === undefined) {
                    hilog.error(LOG_CODE, TAG, 'drag error, currentNodeIndex is not found');
                    this.listNodeDataSource.setIsDrag(false);
                    return;
                }
                if (insertNodeIndex === this.listNodeDataSource.totalCount()) {
                    hilog.info(LOG_CODE, TAG, 'need to insert into the position of the last line');
                    insertNodeIndex -= 1;
                }
                let insertNodeInfo = this.listNodeDataSource.getData(insertNodeIndex);
                if (insertNodeInfo === undefined) {
                    return;
                }
                let insertNodeCurrentNodeId = insertNodeInfo.getNodeCurrentNodeId();
                /* outer node is move in. */
                if (!this.listNodeDataSource.getIsDrag() || !this.listNodeDataSource.getIsInnerDrag()) {
                    this.listNodeDataSource.clearLastTimeoutHighLight();
                    this.listNodeDataSource.setIsInnerDrag(false);
                    this.listNodeDataSource.hideLastLine();
                    this.listNodeDataSource.initialParameterAboutDelayHighLightAndExpandIndex();
                    this.listNodeDataSource.refreshSubtitle(insertNodeCurrentNodeId);
                    this.listNodeDataSource.notifyDataReload();
                    return;
                }
                let currentNodeInfo = this.listNodeDataSource.getCurrentNodeInfo();
                let insertNodeParentNodeId = insertNodeInfo.getNodeParentNodeId();
                let draggingCurrentNodeId = this.listNodeDataSource.getDraggingCurrentNodeId();
                let draggingParentNodeId = this.listNodeDataSource.getDraggingParentNodeId();
                /**
                 * handle a situation that 'draggingCurrentNodeId' is parent of 'insertNodeCurrentNodeId'.
                 * drag is fail.
                 */
                let isParentNodeOfInsertNode = this.listNodeDataSource.getIsParentOfInsertNode(insertNodeCurrentNodeId);
                if (isParentNodeOfInsertNode) {
                    this.listNodeDataSource.clearLastTimeoutHighLight();
                    this.listNodeDataSource.setIsInnerDrag(false);
                    this.listNodeDataSource.hideLastLine();
                    this.listNodeDataSource.notifyDataChange(insertNodeIndex);
                    this.listNodeDataSource.initialParameterAboutDelayHighLightAndExpandIndex();
                    this.listNodeDataSource.setIsDrag(false);
                    /* set the position of focus. */
                    let currentFocusIndex = this.listNodeDataSource.findIndex(draggingCurrentNodeId);
                    this.listNodeDataSource.setClickIndex(currentFocusIndex);
                    this.listNodeDataSource.handleEvent(Event.DRAG, currentFocusIndex);
                    return;
                }
                /* Collapse drag node. */
                if (this.listNodeDataSource.getExpandAndCollapseInfo(draggingCurrentNodeId) === NodeStatus.EXPAND) {
                    this.listNodeDataSource.expandAndCollapseNode(this.listNodeDataSource.findIndex(draggingCurrentNodeId));
                }
                let flag = false;
                /* Expand insert node. */
                if (this.listNodeDataSource.getExpandAndCollapseInfo(insertNodeCurrentNodeId) === NodeStatus.COLLAPSE) {
                    let currentIndex = this.listNodeDataSource.findIndex(insertNodeCurrentNodeId);
                    if (this.listNodeDataSource.listNode[currentIndex].getIsHighLight()) {
                        this.listNodeDataSource.expandAndCollapseNode(currentIndex);
                    }
                    flag = true;
                }
                /* alter dragNode. */
                this.listNodeDataSource.setLastDelayHighLightId();
                if (currentNodeInfo !== null && draggingCurrentNodeId !== insertNodeCurrentNodeId) {
                    this.listNodeDataSource.alterDragNode(insertNodeParentNodeId, insertNodeCurrentNodeId,
                        draggingParentNodeId, draggingCurrentNodeId, currentNodeInfo);
                    this.listNodeDataSource.hideLastLine();
                } else {
                    /*the position of dragNode is equal with the position of insertNode. */
                    this.listNodeDataSource.hideLastLine();
                    this.listNodeDataSource.setLastPassId(draggingCurrentNodeId);
                    this.listNodeDataSource.hideLastLine();
                }
                let lastDelayHighLightIndex =
                    this.listNodeDataSource.findIndex(this.listNodeDataSource.getLastDelayHighLightId());
                this.listNodeDataSource.setLastDelayHighLightIndex(lastDelayHighLightIndex);
                this.listNodeDataSource.clearLastTimeoutHighLight();
                this.listNodeDataSource.initialParameterAboutDelayHighLightAndExpandIndex();
                this.listNodeDataSource.setIsDrag(false);
                /* set the position of focus. */
                let currentFocusIndex = this.listNodeDataSource.findIndex(draggingCurrentNodeId);
                this.listNodeDataSource.setClickIndex(currentFocusIndex);
                this.listNodeDataSource.handleEvent(Event.DRAG, currentFocusIndex);
                /* innerDrag is over. */
                this.listNodeDataSource.setIsInnerDrag(false);
                this.listNodeDataSource.notifyDataReload();
                this.listNodeDataSource.listNode[currentFocusIndex].fontColor =
                    this.treeViewTheme.primaryTitleActiveFontColor;
                if (this.viewLastIndex !== -1 && currentNodeIndex !== this.viewLastIndex) {
                    this.listNodeDataSource.listNode[this.viewLastIndex].getNodeItem()
                        .mainTitleNode?.setMainTitleSelected(false);
                    this.listNodeDataSource.listNode[this.viewLastIndex].getNodeItem()
                        .mainTitleNode?.setMainTitleHighLight(false);
                }
                this.listNodeDataSource.lastIndex = this.viewLastIndex;
                if (this.listNodeDataSource.listNode[this.viewLastIndex]) {
                    if (this.listNodeDataSource.listNode[this.viewLastIndex].getNodeItem()
                        .imageNode !== null) {
                        this.listNodeDataSource.listNode[this.viewLastIndex].getNodeItem()
                            .imageNode?.setImageSource(InteractionStatus.NORMAL);
                        this.listNodeDataSource.listNode[this.viewLastIndex].imageSource =
                            this.listNodeDataSource.listNode[this.viewLastIndex].getNodeItem()
                                .imageNode?.source;
                        this.listNodeDataSource.listNode[this.viewLastIndex].symbolSource =
                            this.listNodeDataSource.listNode[this.viewLastIndex].getNodeItem()
                                .imageNode?.symbolSource;
                    }
                }
                if (this.listNodeDataSource.listNode[this.viewLastIndex]) {
                    this.listNodeDataSource.listNode[this.viewLastIndex]
                        .setNodeColor({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_background_transparent'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                }
                this.listNodeDataSource.lastIndex = currentFocusIndex;
                let parentNodeId = currentNodeInfo?.getNodeParentNodeId();
                this.listNodeDataSource.judgeImageCollapse(parentNodeId);
                /*accessibilityRead regain focus. */
                let eventInfo = ({
                    type: 'requestFocusForAccessibility',
                    bundleName: getContext()?.abilityInfo?.bundleName,
                    triggerAction: 'common',
                    customId: `treeView_node${draggingCurrentNodeId}`
                });
                accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                    setTimeout(() => {
                        this.accessibilityNodeType = AccessibilityNodeType.TEXT;
                    }, ENTER_EXIT_DURATION);
                });
            });
        }, List);
        {
            const __lazyForEachItemGenFunction = _item => {
                const itemInner = _item;
                {
                    const itemCreation2 = (elmtId, isInitialRender) => {
                        ListItem.create(() => {
                        }, false);
                        ListItem.width('100%');
                        ListItem.height(itemInner.getListItemHeight());
                        ListItem.padding({
                            start: LengthMetrics.resource(this.itemPadding.left),
                            end: LengthMetrics.resource(this.itemPadding.right)
                        });
                        ListItem.align(Alignment.Start);
                        ListItem.onDragStart((event, extraParams) => {
                            this.accessibilityNodeType = AccessibilityNodeType.LIFT;
                            if (this.listNodeDataSource.getIsDrag() || this.listNodeDataSource.getIsInnerDrag() ||
                                this.isMultiPress) {
                                hilog.error(LOG_CODE, TAG, 'drag error, a item has been dragged');
                                return;
                            }
                            this.dropSelectedIndex = JSON.parse(extraParams).selectedIndex;
                            let currentNodeIndex = JSON.parse(extraParams).selectedIndex;
                            let currentNodeInfo = this.listNodeDataSource.getData(currentNodeIndex);
                            let currentItemNodeId = itemInner.getNodeCurrentNodeId();
                            /* handle the situation of drag error, currentNodeIndex is not found in onDragStart. */
                            if (currentNodeIndex >= this.listNodeDataSource.totalCount() ||
                                currentNodeIndex === undefined) {
                                hilog.error(LOG_CODE, TAG, 'drag error, currentNodeIndex is not found in onDragStart');
                                return;
                            }
                            this.listNodeDataSource.setIsInnerDrag(true);
                            this.listNodeDataSource.setIsDrag(true);
                            this.listNodeDataSource.setCurrentNodeInfo(currentNodeInfo);
                            this.listNodeDataSource.setDraggingCurrentNodeId(currentNodeInfo?.getNodeCurrentNodeId());
                            this.listNodeDataSource.setDraggingParentNodeId(currentNodeInfo?.getNodeParentNodeId());
                            /* set the opacity of the dragging node. */
                            let draggingNodeOpacity = DRAG_OPACITY;
                            this.listNodeDataSource.setListItemOpacity(draggingNodeOpacity);
                            this.listNodeDataSource.notifyDataChange(currentNodeIndex);
                            /**
                             * handle the situation of drag is too fast,it attribute a fault to OH.
                             * OH has Solved on real machine.
                             */
                            if (currentItemNodeId !== currentNodeInfo?.getNodeCurrentNodeId()) {
                                hilog.error(LOG_CODE, TAG, 'drag is too fast, it attribute a fault to OH');
                                this.listNodeDataSource.setIsDrag(false);
                                return;
                            }
                            let primaryTitle = currentNodeInfo.getNodeInfoData()?.primaryTitle === undefined ? '' :
                                currentNodeInfo.getNodeInfoData()?.primaryTitle;
                            let secondaryTitle = currentNodeInfo.getNodeInfoData()?.secondaryTitle === undefined ? '' :
                                currentNodeInfo.getNodeInfoData()?.secondaryTitle;
                            let primaryTitleText = this.listNodeDataSource.getAccessibleTitleText(primaryTitle);
                            let secondaryTitleText = this.listNodeDataSource.getAccessibleTitleText(secondaryTitle);
                            let title = `${primaryTitleText}, ${secondaryTitleText}`;
                            this.listNodeDataSource.sendAccessibility(this.listNodeDataSource.getStringByName('treeview_accessibility_lift_node',
                                title));
                            let allParentNode = [];
                            for (let i = 0; i < this.listNodeDataSource.listNode.length; i++) {
                                if (this.listNodeDataSource.listNode[i].getNodeParentNodeId() === -1) {
                                    allParentNode.push(this.listNodeDataSource.listNode[i].getNodeCurrentNodeId());
                                }
                            }
                            this.allParentNode = allParentNode;
                            let eventInfo = ({
                                type: 'requestFocusForAccessibility',
                                bundleName: getContext()?.abilityInfo?.bundleName,
                                triggerAction: 'common',
                                customId: `treeView_node_lift${currentItemNodeId}`
                            });
                            accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                                setTimeout(() => {
                                    this.accessibilityNodeType = AccessibilityNodeType.TEXT;
                                }, ENTER_EXIT_DURATION);
                            });
                            return {
                                builder: () => {
                                    this.draggingPopup.call(this, currentNodeInfo);
                                }
                            };
                        });
                    };
                    const observedDeepRender = () => {
                        this.observeComponentCreation2(itemCreation2, ListItem);
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            Row.create();
                            Row.onTouch(this.isAccessibilityEnabled ? undefined : (event) => {
                                this.touchInner(itemInner, event);
                            });
                        }, Row);
                        {
                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                if (isInitialRender) {
                                    let componentCall = new TreeViewInner(this, {
                                        item: itemInner,
                                        listNodeDataSource: this.listNodeDataSource,
                                        initialIndex: this.listNodeDataSource.findIndex(itemInner.getNodeCurrentNodeId()),
                                        listTreeViewMenu: this.listTreeViewMenu,
                                        callBackClick: () => this.clickInner(itemInner),
                                    }, undefined, elmtId, () => {
                                    }, { page: 'library/src/main/ets/components/treeviewv2.ets', line: 1299, col: 13 });
                                    ViewV2.create(componentCall);
                                    let paramsLambda = () => {
                                        return {
                                            item: itemInner,
                                            listNodeDataSource: this.listNodeDataSource,
                                            initialIndex: this.listNodeDataSource.findIndex(itemInner.getNodeCurrentNodeId()),
                                            listTreeViewMenu: this.listTreeViewMenu,
                                            callBackClick: () => this.clickInner(itemInner)
                                        };
                                    };
                                    componentCall.paramsGenerator_ = paramsLambda;
                                } else {
                                    this.updateStateVarsOfChildByElmtId(elmtId, {
                                        item: itemInner,
                                        listNodeDataSource: this.listNodeDataSource,
                                        initialIndex: this.listNodeDataSource.findIndex(itemInner.getNodeCurrentNodeId()),
                                        callBackClick: () => this.clickInner(itemInner)
                                    });
                                }
                            }, { name: 'TreeViewInner' });
                        }
                        Row.pop();
                        ListItem.pop();
                    };
                    observedDeepRender();
                }
            };
            const __lazyForEachItemIdFunc = (item) => JSON.stringify(item);
            LazyForEach.create('1', this, this.listNodeDataSource, __lazyForEachItemGenFunction,
                __lazyForEachItemIdFunc);
            LazyForEach.pop();
        }
        List.pop();
    }

    updateStateVars(params) {
        if (params === undefined) {
            return;
        }
        if ('treeControllerV2' in params) {
            this.updateParam('treeControllerV2', params.treeControllerV2);
        }
    }

    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
], TreeViewV2.prototype, 'treeControllerV2', void 0);
__decorate([
    Local
], TreeViewV2.prototype, 'nodeList', void 0);
__decorate([
    Local
], TreeViewV2.prototype, 'item', void 0);
__decorate([
    Local
], TreeViewV2.prototype, 'touchCount', void 0);
__decorate([
    Local
], TreeViewV2.prototype, 'dropSelectedIndex', void 0);
__decorate([
    Local
], TreeViewV2.prototype, 'viewLastIndex', void 0);
__decorate([
    Local
], TreeViewV2.prototype, 'followingSystemFontScale', void 0);
__decorate([
    Local
], TreeViewV2.prototype, 'maxAppFontScale', void 0);
__decorate([
    Local
], TreeViewV2.prototype, 'listItemBgColor', void 0);
__decorate([
    Local
], TreeViewV2.prototype, 'allParentNode', void 0);
__decorate([
    Provider('treeViewThemeV2')
], TreeViewV2.prototype, 'treeViewTheme', void 0);
__decorate([
    Provider('clickButtonFlagV2')
], TreeViewV2.prototype, 'clickButtonFlag', void 0);
__decorate([
    Provider('accessibilityNodeTypeV2')
], TreeViewV2.prototype, 'accessibilityNodeType', void 0);
__decorate([
    Provider('isAccessibilityEnabledV2')
], TreeViewV2.prototype, 'isAccessibilityEnabled', void 0);

/**
 * Declare TreeControllerV2.
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 26
 */
export class TreeControllerV2 {
    constructor() {
        this.ROOT_NODE_ID = -1;
        this.nodeIdList = [];
        this.listNodeDataSource = new ListNodeDataSource();
        this.initBuild = true;
        this.treeViewTheme = TreeViewTheme.getInstance();
    }

    getListNodeDataSource() {
        return this.listNodeDataSource;
    }

    getClickNodeChildrenInfo() {
        let clickNodeId = this.listNodeDataSource.getClickNodeId();
        return this.listNodeDataSource.getClickNodeChildrenInfo(clickNodeId);
    }

    getChildrenId() {
        let clickNodeId = this.listNodeDataSource.getClickNodeId();
        return this.listNodeDataSource.getClickChildId(clickNodeId);
    }

    /**
     * Delete a node.
     * Register an ON_ITEM_DELETE callback through the EventBus mechanism to obtain the IDs of all deleted nodes.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 26
     */
    removeNode() {
        let clickNodeId = this.listNodeDataSource.getClickNodeId();
        if (clickNodeId < 0) {
            return;
        }
        let parentNodeId = this.listNodeDataSource.findParentNodeId(clickNodeId);
        let removeNodeIdList = this.listNodeDataSource.removeNode(clickNodeId, parentNodeId);
        this.listNodeDataSource.refreshData(MenuOperation.REMOVE_NODE, parentNodeId, removeNodeIdList);
        this.nodeIdList.splice(this.nodeIdList.indexOf(clickNodeId), 1);
        this.listNodeDataSource.lastIndex = -1;
    }

    /**
     * Modify the node name.
     * Register an ON_ITEM_MODIFY callback to obtain the ID, parent node ID, and node name of the modified node.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 26
     */
    modifyNode() {
        let clickNodeId = this.listNodeDataSource.getClickNodeId();
        this.listNodeDataSource.setItemVisibilityOnEdit(clickNodeId, MenuOperation.MODIFY_NODE);
    }

    /**
     * add new node
     *
     * @param initBuild whether is in initialization process
     */
    add(initBuild) {
        let clickNodeId = this.listNodeDataSource.getClickNodeId();
        if (clickNodeId === this.listNodeDataSource.ROOT_NODE_ID || !this.listNodeDataSource.getIsFolder(clickNodeId)) {
            return;
        }
        let newNodeParam = this.listNodeDataSource.getNewNodeParam(clickNodeId);
        this.nodeIdList.push(this.nodeIdList[this.nodeIdList.length - 1] + 1);
        let newNodeId = this.nodeIdList[this.nodeIdList.length - 1];
        let addNodeResult = this.listNodeDataSource.addNode(clickNodeId, newNodeId, {
            isFolder: newNodeParam.isFolder,
            icon: newNodeParam.icon,
            symbolIconStyle: newNodeParam.symbolIconStyle,
            selectedIcon: newNodeParam.selectedIcon,
            symbolSelectedIconStyle: newNodeParam.symbolSelectedIconStyle,
            editIcon: newNodeParam.editIcon,
            symbolEditIconStyle: newNodeParam.symbolEditIconStyle,
            primaryTitle: '新建文件夹',
            container: newNodeParam.container,
            secondaryTitle: newNodeParam.secondaryTitle,
        }, initBuild);
        if (!addNodeResult) {
            return;
        }
        this.listNodeDataSource.refreshData(MenuOperation.ADD_NODE, clickNodeId, [newNodeId]);
        this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false,
            this.listNodeDataSource.getLastIndex());
        this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(),
            MenuOperation.COMMIT_NODE);
        this.listNodeDataSource.listNode[this.listNodeDataSource.getLastIndex()]
            .setFontColor(this.treeViewTheme.primaryTitleFontColor);
        let newNodeIndex = this.listNodeDataSource.findIndex(newNodeId);
        this.listNodeDataSource.setClickIndex(newNodeIndex);
        this.listNodeDataSource.handleEvent(Event.TOUCH_UP, newNodeIndex);
    }

    /**
     * Initialize the interface of the tree view. This interface is used to generate ListNodeDataSource data.
     * addNode is only designed for initialization. It can only be invoked during initialization.
     *
     * A maximum of 50 directory levels can be added.
     *
     * @param nodeParam Configuration information of the newly added node.
     *
     * For details, see the comment description of NodeParamV2.
     * @return ListTreeNode Tree view component proxy class.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 26
     */
    addNode(nodeParam) {
        if (nodeParam === undefined) {
            this.add(this.initBuild);
            return this;
        } else {
            for (let i = 0; i < this.nodeIdList.length; i++) {
                if (nodeParam.currentNodeId === this.nodeIdList[i].valueOf()) {
                    throw new Error('ListTreeNode[addNode]: ' +
                        'The parameters of the new node cannot contain the same currentNodeId.');
                    return this;
                }
            }
            let addNodeResult = false;
            if (nodeParam.primaryTitle !== undefined &&
                !this.listNodeDataSource.checkMainTitleIsValid(nodeParam.primaryTitle.toString())) {
                throw new Error('ListTreeNode[addNode]: The directory name cannot contain ' +
                    'the following characters\ /: *? "< > | or exceeds the maximum length.');
                return this;
            }
            if (nodeParam.primaryTitle === null && nodeParam.icon === null && nodeParam.symbolIconStyle === null) {
                throw new Error('ListTreeNode[addNode]: ' +
                    'The icon|symbolIconStyle and directory name cannot be empty at the same time.');
                return this;
            }
            if (nodeParam.currentNodeId === this.ROOT_NODE_ID || nodeParam.currentNodeId === null) {
                throw new Error('ListTreeNode[addNode]: currentNodeId can not be -1 or null.');
                return this;
            }
            if (nodeParam.currentNodeId !== undefined) {
                this.nodeIdList.push(nodeParam.currentNodeId);
            }
            if (nodeParam.parentNodeId !== undefined) {
                if (nodeParam.currentNodeId !== undefined) {
                    addNodeResult =
                        this.listNodeDataSource.addNode(nodeParam.parentNodeId, nodeParam.currentNodeId, nodeParam,
                            this.initBuild);
                }
            }
            if (!addNodeResult) {
                return this;
            }
            if (!this.initBuild && nodeParam.parentNodeId !== undefined) {
                let newNodeId = this.nodeIdList[this.nodeIdList.length - 1];
                this.listNodeDataSource.refreshData(MenuOperation.ADD_NODE, nodeParam.parentNodeId, [newNodeId]);
            }
            return this;
        }
    }

    /**
     * this interface is called when a secondaryTitle needs to be updated.
     *
     * @Param parentId ID of the parent node.
     * @Param parentSubTitle secondaryTitle of parent node.
     * @Param currentSubTitle secondaryTitle of current node.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 26
     */
    refreshNode(parentId, parentSubTitle, CurrentSubtitle) {
        this.listNodeDataSource.setNodeSubtitlePara(parentId, parentSubTitle, CurrentSubtitle);
    }

    /**
     * After the initialization is complete by calling the addNode interface,
     * call this interface to complete initialization.
     *
     * This interface must be called when you finish initializing the ListTreeViewV2 by addNode.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 26
     */
    buildDone() {
        this.listNodeDataSource.initSection();
        this.listNodeDataSource.delayInit();
        this.listNodeDataSource.updateAllChildNum();
        delaySortNodeIdList(this.nodeIdList);
        this.initBuild = false;
    }
}

class BasicDataSource {
    constructor() {
        this.listeners = [];
    }

    totalCount() {
        return 0;
    }

    getData(index) {
        return undefined;
    }

    registerDataChangeListener(listener) {
        if (this.listeners.indexOf(listener) < 0) {
            this.listeners.push(listener);
        }
    }

    unregisterDataChangeListener(listener) {
        const pos = this.listeners.indexOf(listener);
        if (pos >= 0) {
            this.listeners.splice(pos, 1);
        }
    }

    notifyDataReload() {
        this.listeners.forEach(listener => {
            listener.onDataReloaded();
        });
    }

    notifyDataAdd(index) {
        this.listeners.forEach(listener => {
            listener.onDataAdd(index);
        });
    }

    notifyDataChange(index) {
        if (index === undefined) {
            return;
        }
        this.listeners.forEach(listener => {
            listener.onDataChange(index);
        });
    }

    notifyDataDelete(index) {
        this.listeners.forEach(listener => {
            listener.onDataDelete(index);
        });
    }

    notifyDataMove(from, to) {
        this.listeners.forEach(listener => {
            listener.onDataMove(from, to);
        });
    }
}

/**
 * delay update all parentnodes childNum
 *
 * @param isAdd whether addNode or delete node
 * @param count node count
 * @param nodeIdNodeItemMap nodeId and nodeItem relation map
 * @param updateNodeIdList nodeId list whose childNum need update
 */
function delayUpdateParentChildNum(isAdd, count, nodeIdNodeItemMap, updateNodeIdList) {
    let taskId = setTimeout(() => {
        updateNodeIdList.forEach((parentNodeId) => {
            updateParentChildNumHandler(parentNodeId, nodeIdNodeItemMap, isAdd, count);
        });
        clearTimeout(taskId);
    }, DELAY_TIME);
}

/**
 * delay update all parentnodes child number handler
 *
 * @param parentNodeId parent node id
 * @param nodeIdNodeItemMap nodeId and nodeItem relation map
 * @param isAdd whether addNode or delete node
 * @param count node count
 */
function updateParentChildNumHandler(parentNodeId, nodeIdNodeItemMap, isAdd, count) {
    let tmpParentNodeId = parentNodeId;
    while (tmpParentNodeId >= 0) {
        if (nodeIdNodeItemMap.has(tmpParentNodeId)) {
            let parent = nodeIdNodeItemMap.get(tmpParentNodeId);
            parent.getChildNodeInfo().allChildNum =
                isAdd ? parent.getChildNodeInfo().allChildNum + count : parent.getChildNodeInfo().allChildNum - count;
            tmpParentNodeId = parent.parentNodeId;
        } else {
            hilog.error(LOG_CODE, TAG, 'updateParentChildNumHandler: parent node not found');
            break;
        }
    }
}

/**
 * delay sort nodeId list
 *
 * @param nodeIdList nodeId list
 */
function delaySortNodeIdList(nodeIdList) {
    let taskId = setTimeout(() => {
        nodeIdList.sort((a, b) => a - b);
        clearTimeout(taskId);
    }, DELAY_TIME);
}

class ListNodeDataSource extends BasicDataSource {
    constructor() {
        super();
        this.ROOT_NODE_ID = -1;
        this._root = new NodeItem(emptyNodeInfo);
        this.maxNodeLevel = 50;
        this.MAX_CN_LENGTH = 254;
        this.MAX_EN_LENGTH = 255;
        this.INITIAL_INVALID_VALUE = -1;
        this.listNode = [];
        this.loadedListNode = [];
        this.nodeIdNodeItemMap = new Map();
        this.nodeIdNodeParamMap = new Map();
        this.lastIndex = -1;
        this.thisIndex = -1;
        this.modifyNodeIndex = -1;
        this.modifyNodeId = -1;
        this.expandAndCollapseInfo = new Map();
        this.loadedNodeIdAndIndexMap = new Map();
        this.nodeIdAndNodeIndexMap = new Map();
        this.isTouchDown = false;
        this.appEventBus = TreeListenerManagerV2.getInstance().getTreeListener();
        /* parameter of the drag event. */
        this.isInnerDrag = false; // Judge whether it is an internal drag event.
        // It is used to handle events(For example, prevent press events) during global drag.
        this.isDrag = false;
        this.draggingCurrentNodeId = this.INITIAL_INVALID_VALUE; // Record the current ID of the dragged node.
        this.draggingParentNodeId = this.INITIAL_INVALID_VALUE; // Record the parent ID of the dragged node.
        this.currentNodeInfo = null; // To solve the problem of currentIndex missed in onDrop event.
        this.listItemOpacity = 1; // It is used to set the opacity of the node when dragged.
        this.lastPassIndex = this.INITIAL_INVALID_VALUE; // record the last passing node index in drag.
        this.lastPassId = this.INITIAL_INVALID_VALUE; // record the last passing node Id in drag.
        this.thisPassIndex = this.INITIAL_INVALID_VALUE; // record the current passing node in drag.
        // record last passing node in delay expand event.
        this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE;
        this.timeoutExpandId = this.INITIAL_INVALID_VALUE;
        this.lastTimeoutExpandId = this.INITIAL_INVALID_VALUE;
        this.clearTimeoutExpandId = this.INITIAL_INVALID_VALUE;
        this.timeoutHighLightId = this.INITIAL_INVALID_VALUE;
        this.lastTimeoutHighLightId = this.INITIAL_INVALID_VALUE;
        this.clearTimeoutHighLightId = this.INITIAL_INVALID_VALUE;
        // record last passing node in HighLight event.
        this.lastDelayHighLightIndex = this.INITIAL_INVALID_VALUE;
        //record last passing node Id in HighLight event.
        this.lastDelayHighLightId = this.INITIAL_INVALID_VALUE;
        this.nodeIdAndSubtitleMap = new Map();
        this.flag = Flag.NONE;
        this.selectedParentNodeId = this.INITIAL_INVALID_VALUE;
        this.selectedParentNodeSubtitle = '';
        this.insertNodeSubtitle = '';
        this.currentFocusNodeId = this.INITIAL_INVALID_VALUE;
        this.lastFocusNodeId = this.INITIAL_INVALID_VALUE;
        this.addFocusNodeId = this.INITIAL_INVALID_VALUE;
        this.treeViewTheme = TreeViewTheme.getInstance();
        this.updateNodeIdList = [];
        this.FLAG_LINE = {
            flagLineHeight: FLAG_LINE_HEIGHT,
            flagLineColor: {
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_emphasize'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
            xOffset: X_OFF_SET,
            yTopOffset: Y_OFF_SET,
            yBottomOffset: Y_BOTTOM_OFF_SET,
            yBasePlateOffset: Y_BASE_PLATE_OFF_SET,
        };
        this.DRAG_POPUP = {
            floorConstraintSize: { minWidth: FLOOR_MIN_WIDTH, maxWidth: FLOOR_MAX_WIDTH },
            textConstraintSize: {
                minWidth1: TEXT_MIN_WIDTH,
                maxWidth1: TEXT_MAX_WIDTH,
                minWidth2: MIN_WIDTH,
                maxWidth2: MAX_WIDTH,
            },
            padding: {
                left: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.padding_level4'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                right: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.padding_level4'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                }
            },
            backgroundColor: {
                'id': -1,
                'type': 10001,
                params: ['sys.color.comp_background_primary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
            height: GRAG_POP_UP_HEIGHT,
            shadow: {
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_default_shadow_m'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                color: {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_dialog_bg'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                offsetX: 0,
                offsetY: 0,
            },
            borderRadius: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_corner_radius_default_s'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
            fontColor: this.treeViewTheme.primaryTitleFontColor,
            fontSize: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_body1'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
            fontWeight: FontWeight.Regular,
            imageOpacity: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_alpha_content_fourth'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            }
        };
        this.subTitle = {
            normalFontColor: this.treeViewTheme.secondaryTitleFontColor,
            highLightFontColor: {
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_primary_contrary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
            fontSize: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_body2'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
            fontWeight: FontWeight.Regular,
            margin: {
                left: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.padding_level2'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                right: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.padding_level12'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                }
            }
        };
        this._root.nodeLevel = -1;
        this.nodeIdNodeItemMap.set(-1, this._root);
        this.nodeIdNodeParamMap.set(-1, emptyNodeInfo);
    }

    checkIndex(index) {
        if (index < 0 || index >= this.listNode.length) {
            hilog.error(LOG_CODE, TAG, 'check index fail');
            return false;
        }
        return true;
    }

    changeNodeColor(index, color) {
        if (!this.checkIndex(index)) {
            return;
        }
        this.listNode[index].setNodeColor(color);
        this.listNode[index].setNodeBorder(false);
    }

    getNodeColor(index) {
        return this.listNode[index].getNodeColor();
    }

    handleFocusEffect(index, isClearFocusStatus) {
        if (this.listNode[index].getNodeIsShow()) {
            this.listNode[index].setNodeBorder(isClearFocusStatus);
        }
    }

    setImageSource(index, interactionStatus) {
        if (!this.checkIndex(index)) {
            return;
        }
        let nodeInfo = this.listNode[index];
        nodeInfo.setIsSelected(interactionStatus === InteractionStatus.SELECTED ||
            interactionStatus === InteractionStatus.EDIT || interactionStatus === InteractionStatus.FINISH_EDIT);
        if (nodeInfo.getNodeItem().mainTitleNode !== null && interactionStatus !== InteractionStatus.DRAG_INSERT &&
            interactionStatus !== InteractionStatus.FINISH_DRAG_INSERT) {
            nodeInfo.getNodeItem()
                .mainTitleNode?.setMainTitleSelected(interactionStatus === InteractionStatus.SELECTED ||
                    interactionStatus === InteractionStatus.FINISH_EDIT);
        }
        if (nodeInfo.getNodeItem().imageNode !== null) {
            nodeInfo.getNodeItem().imageNode?.setImageSource(interactionStatus);
        }
    }

    setImageCollapseSource(index, interactionStatus) {
        let nodeInfo = this.listNode[index];
        if (nodeInfo.getNodeItem().imageCollapse !== undefined) {
            nodeInfo.getNodeItem().imageCollapse =
                CollapseImageNodeFlyweightFactory.getCollapseImageNode(interactionStatus,
                    this.expandAndCollapseInfo.get(nodeInfo.getNodeCurrentNodeId()),
                    nodeInfo.getNodeItem().imageCollapse?.type);
        }
    }

    clearLastIndexStatus() {
        if (!this.checkIndex(this.lastIndex)) {
            return;
        }
        this.setImageSource(this.lastIndex, InteractionStatus.NORMAL);
        this.changeNodeColor(this.lastIndex, this.listNode[this.lastIndex].getNodeStatus().normal);
        this.handleFocusEffect(this.lastIndex, false);
        this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.listNode[this.lastIndex].getNodeCurrentNodeId()));
    }

    loadedListNodeFunction() {
        let index = 0;
        this.loadedNodeIdAndIndexMap.clear();
        this.nodeIdAndNodeIndexMap.clear();
        this.loadedListNode.splice(0, this.loadedListNode.length);
        for (let i = 0; i < this.listNode.length; i++) {
            this.nodeIdAndNodeIndexMap.set(this.listNode[i].getNodeCurrentNodeId(), i);
            if (this.listNode[i].getNodeIsShow()) {
                this.loadedNodeIdAndIndexMap.set(this.listNode[i].getNodeCurrentNodeId(), index++);
                this.loadedListNode.push(this.listNode[i]);
            }
        }
    }

    changeNodeStatus(clickIndex) {
        if (clickIndex >= this.listNode.length) {
            hilog.error(LOG_CODE, TAG, 'changeNodeStatus clickIndex error.');
            return;
        }
        let thisIndex = clickIndex;
        let nodeId = this.listNode[clickIndex].getNodeCurrentNodeId();
        if (this.expandAndCollapseInfo.get(nodeId) === NodeStatus.EXPAND) {
            this.expandAndCollapseInfo.set(nodeId, NodeStatus.COLLAPSE);
            this.listNode[thisIndex].getNodeItem()
                .imageCollapse = CollapseImageNodeFlyweightFactory.changeImageCollapseSource(NodeStatus.COLLAPSE,
                this.listNode[thisIndex].getNodeItem().imageCollapse?.isCollapse);
        } else if (this.expandAndCollapseInfo.get(nodeId) === NodeStatus.COLLAPSE) {
            this.expandAndCollapseInfo.set(nodeId, NodeStatus.EXPAND);
            this.listNode[thisIndex].getNodeItem()
                .imageCollapse = CollapseImageNodeFlyweightFactory.changeImageCollapseSource(NodeStatus.EXPAND,
                this.listNode[thisIndex].getNodeItem().imageCollapse?.isCollapse);
        }
    }

    handleExpandAndCollapse(clickIndex, isRefreshList) {
        if (clickIndex >= this.listNode.length) {
            hilog.error(LOG_CODE, TAG, 'handleExpandAndCollapse clickIndex error.');
            return;
        }
        let thisIndex = clickIndex;
        let nodeId = this.listNode[thisIndex].getNodeCurrentNodeId();
        if (!this.expandAndCollapseInfo.has(nodeId)) {
            return;
        }
        let rootNodeStatus = this.expandAndCollapseInfo.get(nodeId);
        if (this.listNode[thisIndex].getChildNodeInfo().isHasChildNode && rootNodeStatus === NodeStatus.COLLAPSE) {
            for (let i = 0; i < this.listNode[thisIndex].getChildNodeInfo().allChildNum; i++) {
                if (this.listNode[thisIndex + 1 + i] === undefined) {
                    return;
                }
                this.listNode[thisIndex + 1 + i].setNodeIsShow(false);
                this.listNode[thisIndex + 1 + i].setListItemHeight(LIST_ITEM_HEIGHT_NONE);
            }
            this.loadedListNodeFunction();
            this.notifyDataReload();
            return;
        }
        let childNum = new Array(this.listNode[thisIndex].getChildNodeInfo().childNum);
        childNum[0] = thisIndex + 1;
        let index = 1;
        while (index < this.listNode[thisIndex].getChildNodeInfo().childNum) {
            childNum[index] =
                childNum[index - 1] + this.listNode[childNum[index - 1]].getChildNodeInfo().allChildNum + 1;
            index++;
        }
        if (rootNodeStatus === NodeStatus.EXPAND) {
            for (let i = 0; i < childNum.length; i++) {
                if (this.listNode[childNum[i]] === undefined) {
                    return;
                }
                this.listNode[childNum[i]].setNodeIsShow(true);
                this.listNode[childNum[i]].setListItemHeight(LIST_ITEM_HEIGHT);
                let nodeId = this.listNode[childNum[i]].getNodeCurrentNodeId();
                if (this.expandAndCollapseInfo.get(nodeId) === NodeStatus.EXPAND) {
                    this.handleExpandAndCollapse(childNum[i], false);
                }
            }
        }
        childNum = null;
        if (isRefreshList) {
            this.loadedListNodeFunction();
            this.notifyDataReload();
        }
    }

    /**
     * update all parentNodes childNum
     */
    updateAllChildNum() {
        delayUpdateParentChildNum(true, 1, this.nodeIdNodeItemMap, this.updateNodeIdList);
    }

    resetData(listNode) {
        listNode.splice(0, listNode.length);
        this.loadedNodeIdAndIndexMap.clear();
        this.loadedListNode.splice(0, this.loadedListNode.length);
        this.nodeIdAndNodeIndexMap.clear();
        this.nodeIdAndSubtitleMap.clear();
    }

    initHandler(listNode, startLevel, endLevel) {
        let index = 0;
        let listIndex = 0;
        this.resetData(listNode);
        try {
            this.traverseSectionNodeDF((node) => {
                if (node.getCurrentNodeId() >= 0 && this.nodeIdNodeParamMap.has(node.getCurrentNodeId())) {
                    let nodeInfo = new NodeInfo(node, this.nodeIdNodeParamMap.get(node.getCurrentNodeId()));
                    nodeInfo.addImageCollapse(node.getChildNodeInfo().isHasChildNode);
                    listNode.push(nodeInfo);
                    this.nodeIdAndNodeIndexMap.set(nodeInfo.getNodeCurrentNodeId(), listIndex++);
                    index = this.nodeDFHandler(nodeInfo, index);
                }
                return false;
            }, this._root, startLevel, endLevel);
        } catch (err) {
            hilog.error(LOG_CODE, TAG, 'traverseSectionNodeDF function callbacks error.');
            this.resetData(listNode);
        }
    }

    nodeDFHandler(nodeInfo, index) {
        if (nodeInfo.getChildNodeInfo().isHasChildNode) {
            this.expandAndCollapseInfo.set(nodeInfo.getNodeCurrentNodeId(), NodeStatus.COLLAPSE);
        }
        if (nodeInfo.getNodeIsShow()) {
            this.loadedNodeIdAndIndexMap.set(nodeInfo.getNodeCurrentNodeId(), index++);
            this.loadedListNode.push(nodeInfo);
        }
        if (nodeInfo.getIsFolder()) {
            if (nodeInfo.getNodeInfoData().secondaryTitle !== undefined) {
                this.nodeIdAndSubtitleMap.set(nodeInfo.getNodeCurrentNodeId(),
                    nodeInfo.getNodeInfoData().secondaryTitle);
            } else {
                this.nodeIdAndSubtitleMap.set(nodeInfo.getNodeCurrentNodeId(), '');
            }
        }
        return index;
    }

    /**
     * update delay init all nodes
     */
    delayInit() {
        let timeId = setTimeout(() => {
            let listNode = [];
            this.initHandler(listNode, 0);
            this.listNode.splice(0, this.listNode.length);
            this.listNode.push(...listNode);
            this.listNode.forEach((value, index) => {
                this.notifyDataDelete(index);
                this.notifyDataAdd(index);
            });
            clearTimeout(timeId);
        }, DELAY_TIME);
    }

    /**
     * update delay init some nodes
     */
    initSection() {
        this.initHandler(this.listNode, 0, 1);
    }

    setClickIndex(index) {
        this.thisIndex = index;
    }

    getClickNodeId() {
        if (!this.checkIndex(this.thisIndex)) {
            return -1;
        }
        return this.listNode[this.thisIndex].getNodeCurrentNodeId();
    }

    expandAndCollapseNode(clickIndex) {
        this.changeNodeStatus(clickIndex);
        this.handleExpandAndCollapse(clickIndex, true);
    }

    getIsTouchDown() {
        return this.isTouchDown;
    }

    getLastIndex() {
        return this.lastIndex;
    }

    findIndex(currentNodeId) {
        let thisIndex = -1;
        if (this.nodeIdAndNodeIndexMap.has(currentNodeId)) {
            thisIndex = this.nodeIdAndNodeIndexMap.get(currentNodeId);
        }
        return thisIndex;
    }

    handleEventDrag(index) {
        if (!this.checkIndex(index)) {
            return;
        }
        this.setImageSource(index, InteractionStatus.NORMAL);
        this.changeNodeColor(index, this.listNode[index].getNodeStatus().normal);
        this.handleFocusEffect(index, false);
        this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.listNode[index].getNodeCurrentNodeId()));
    }

    handleEvent(event, index) {
        /* Return while the event is dragging event. */
        if (this.isDrag) {
            return;
        }
        if (!this.checkIndex(index)) {
            return;
        }
        if (event === Event.TOUCH_DOWN || event === Event.TOUCH_UP || event === Event.MOUSE_BUTTON_RIGHT) {
            if (index !== this.lastIndex) {
                this.clearLastIndexStatus();
            }
        }
        this.eventHandler(index, event);
    }

    eventHandler(index, event) {
        let lazyForEachIndex = this.loadedNodeIdAndIndexMap.get(this.listNode[index].getNodeCurrentNodeId());
        switch (event) {
            case Event.TOUCH_DOWN:
                this.isTouchDown = true;
                this.changeNodeColor(index, this.listNode[index].getNodeStatus().press);
                this.notifyDataChange(lazyForEachIndex);
                break;
            case Event.TOUCH_UP: {
                this.touchUpHandler(index, lazyForEachIndex);
                break;
            }
            case Event.HOVER:
                if (this.getNodeColor(index) !== this.listNode[index].getNodeStatus().selected) {
                    this.changeNodeColor(index, this.listNode[index].getNodeStatus().hover);
                    this.notifyDataChange(lazyForEachIndex);
                }
                break;
            case Event.HOVER_OVER:
                if (this.getNodeColor(index) !== this.listNode[index].getNodeStatus().selected) {
                    this.changeNodeColor(index, this.listNode[index].getNodeStatus().normal);
                    this.notifyDataChange(lazyForEachIndex);
                }
                break;
            case Event.FOCUS:
                this.handleFocusEffect(index, true);
                this.notifyDataChange(lazyForEachIndex);
                break;
            case Event.BLUR:
                this.handleFocusEffect(index, false);
                this.notifyDataChange(lazyForEachIndex);
                break;
            case Event.MOUSE_BUTTON_RIGHT:
                this.lastIndex = index;
                this.finishEditing();
                break;
            case Event.DRAG:
                this.isTouchDown = false;
                let nodeInfo = this.listNode[index];
                this.setImageSource(index, InteractionStatus.SELECTED);
                this.lastIndex = index;
                this.changeNodeColor(index, nodeInfo.getNodeStatus().selected);
                this.notifyDataChange(lazyForEachIndex);
                break;
            default:
                break;
        }
    }

    touchUpHandler(index, lazyForEachIndex) {
        if (this.isInnerDrag) {
            this.isInnerDrag = false;
        }
        this.isTouchDown = false;
        let nodeInfo = this.listNode[index];
        this.setImageSource(index, InteractionStatus.SELECTED);
        nodeInfo.setFontColor(this.treeViewTheme.primaryTitleFontColor);
        this.lastIndex = index;
        this.changeNodeColor(index, nodeInfo.getNodeStatus().selected);
        this.notifyDataChange(lazyForEachIndex);
    }

    notificationNodeInfo(addNodeId, operation) {
        if (operation === MenuOperation.MODIFY_NODE) {
            let modifyNodeInfo = this.listNode[this.modifyNodeIndex];
            let backParamModify = {
                currentNodeId: modifyNodeInfo?.getNodeCurrentNodeId(),
                parentNodeId: modifyNodeInfo?.getNodeParentNodeId(),
            };
            this.appEventBus.emitNodeModify(backParamModify);
        } else if (operation === MenuOperation.ADD_NODE) {
            let addNodeInfo = this.listNode[addNodeId];
            if (addNodeInfo === undefined) {
                return;
            }
            let icon = (addNodeInfo.getNodeItem().imageNode !== undefined) ?
                addNodeInfo.getNodeItem().imageNode?.source : undefined;
            let selectedIcon = (addNodeInfo.getNodeItem().imageNode !== undefined) ?
                addNodeInfo.getNodeItem().imageNode?.selectedSource : undefined;
            let editIcon = (addNodeInfo.getNodeItem().imageNode !== undefined) ?
                addNodeInfo.getNodeItem().imageNode?.editSource : undefined;
            let callbackParam = {
                currentNodeId: addNodeInfo?.getNodeCurrentNodeId(),
                parentNodeId: addNodeInfo?.getNodeParentNodeId(),
            };
            this.appEventBus.emitNodeAdd(callbackParam);
        }
    }

    finishEditing() {
        if (this.modifyNodeIndex !== -1) {
            this.setImageSource(this.modifyNodeIndex, InteractionStatus.FINISH_EDIT);
            this.setImageCollapseSource(this.modifyNodeIndex, InteractionStatus.FINISH_EDIT);
            this.listNode[this.modifyNodeIndex].setIsModify(false);
            this.listNode[this.modifyNodeIndex].setTitleAndInputTextStatus(false);
            this.notificationNodeInfo(this.modifyNodeIndex, this.currentOperation);
            this.notifyDataChange(this.modifyNodeIndex);
        }
    }

    setItemVisibilityOnEdit(nodeId, operation) {
        let index = -1;
        if (nodeId === -1) {
            return;
        }
        if (operation === MenuOperation.MODIFY_NODE) {
            for (let i = 0; i < this.listNode.length; i++) { // nodeId to find index
                if (this.listNode[i]?.getNodeCurrentNodeId() === nodeId) {
                    index = i;
                    break;
                }
            }
            let nodeInfo = this.listNode[index];
            if (nodeInfo === undefined) {
                return;
            }
            nodeInfo.setIsModify(true);
            if (nodeInfo.getNodeItem().mainTitleNode === null) {
                return; // no title
            }
            this.currentOperation = MenuOperation.MODIFY_NODE;
            nodeInfo.setTitleAndInputTextStatus(true);
            this.setImageSource(index, InteractionStatus.EDIT);
            this.setImageCollapseSource(index, InteractionStatus.EDIT);
            this.modifyNodeIndex = index;
            if (nodeInfo.getNodeItem().inputText) {
                if (nodeInfo.getNodeItem().imageCollapse !== null) {
                    nodeInfo.getNodeItem().inputText.rightMargin = {
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.ohos_id_text_paragraph_margin_xs'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__'
                    };
                } else {
                    nodeInfo.getNodeItem().inputText.rightMargin = {
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.ohos_id_elements_margin_horizontal_m'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__'
                    };
                }
            }
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(nodeId));
        }
        index = nodeId;
        if (operation === MenuOperation.COMMIT_NODE) {
            let nodeInfo = this.listNode[index];
            if (nodeInfo === undefined) {
                return;
            }
            nodeInfo.setTitleAndInputTextStatus(false);
            nodeInfo.setIsModify(false);
            this.setImageSource(index, InteractionStatus.FINISH_EDIT);
            this.setImageCollapseSource(index, InteractionStatus.FINISH_EDIT);
            this.notificationNodeInfo(this.modifyNodeIndex, this.currentOperation);
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(nodeInfo?.getNodeCurrentNodeId()));
        }
    }

    setPopUpInfo(popUpType, inputError, isShow, index) {
        if (!this.checkIndex(index)) {
            return;
        }
        let nodeInfo = this.listNode[index];
        if (nodeInfo === undefined) {
            return;
        }
        nodeInfo.setPopUpIsShow(isShow);
        // this.listNode index to lazyForEach index.
        let lazyForEachIndex = this.loadedNodeIdAndIndexMap.get(nodeInfo.getNodeCurrentNodeId());
        if (!isShow) {
            this.notifyDataChange(lazyForEachIndex);
            return;
        }
        if (popUpType === PopUpType.HINTS) {
            if (nodeInfo.getNodeItem().mainTitleNode !== null) {
                nodeInfo.setPopUpText(nodeInfo.getNodeItem().mainTitleNode?.title);
            } else {
                nodeInfo.setPopUpText('');
                nodeInfo.setPopUpIsShow(false);
            }
            nodeInfo.setPopUpEnableArrow(false);
            nodeInfo.setPopUpColor({
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_background'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            nodeInfo.setPopUpTextColor(this.treeViewTheme.secondaryTitleFontColor);
        } else if (popUpType === PopUpType.WARNINGS) {
            if (nodeInfo.getNodeItem().inputText !== null) {
                if (inputError === InputError.INVALID_ERROR) {
                    nodeInfo.setPopUpText('invalid error');
                } else if (inputError === InputError.LENGTH_ERROR) {
                    nodeInfo.setPopUpText('length error');
                }
                nodeInfo.setPopUpEnableArrow(true);
                nodeInfo.setPopUpColor({
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_help_tip_bg'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                });
                nodeInfo.setPopUpTextColor({
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_text_hint_contrary'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                });
            }
        }
        this.notifyDataChange(lazyForEachIndex);
    }

    setShowPopUpTimeout(timeout, index) {
        if (!this.checkIndex(index)) {
            return;
        }
        if (this.listNode[index].getNodeItem().mainTitleNode !== null) {
            this.listNode[index].getNodeItem().mainTitleNode.popUpTimeout = timeout;
        }
        let lazyForEachIndex = this.loadedNodeIdAndIndexMap.get(this.listNode[index].getNodeCurrentNodeId());
        this.notifyDataChange(lazyForEachIndex);
    }

    setMainTitleNameOnEdit(index, text) {
        this.modifyNodeIndex = index;
        if (this.listNode[index].getNodeItem().mainTitleNode !== null) {
            this.listNode[index].getNodeItem().mainTitleNode.title = text;
        }
    }

    totalCount() {
        return this.loadedNodeIdAndIndexMap.size;
    }

    getData(index) {
        if (index < 0 || index >= this.loadedListNode.length) {
            return undefined;
        }
        return this.loadedListNode[index];
    }

    addData(index, data) {
        if (!this.checkIndex(index)) {
            return;
        }
        this.listNode.splice(index, 0, data);
        this.nodeIdAndNodeIndexMap.set(data.getNodeCurrentNodeId(), index);
        this.loadedListNodeFunction();
        this.notifyDataAdd(index);
    }

    pushData(data) {
        this.listNode.push(data);
        this.nodeIdAndNodeIndexMap.set(data.getNodeCurrentNodeId(), this.listNode.length);
        this.loadedListNodeFunction();
        this.notifyDataAdd(this.listNode.length - 1);
    }

    setIsInnerDrag(isInnerDrag) {
        this.isInnerDrag = isInnerDrag;
    }

    getIsInnerDrag() {
        return this.isInnerDrag;
    }

    setIsDrag(isDrag) {
        this.isDrag = isDrag;
    }

    getIsDrag() {
        return this.isDrag;
    }

    setCurrentNodeInfo(currentNodeInfo) {
        if (currentNodeInfo === undefined) {
            return;
        }
        this.currentNodeInfo = currentNodeInfo;
    }

    getCurrentNodeInfo() {
        return this.currentNodeInfo;
    }

    setDraggingParentNodeId(draggingParentNodeId) {
        if (draggingParentNodeId === undefined) {
            return;
        }
        this.draggingParentNodeId = draggingParentNodeId;
    }

    getDraggingParentNodeId() {
        return this.draggingParentNodeId;
    }

    getDraggingCurrentNodeId() {
        return this.draggingCurrentNodeId;
    }

    setDraggingCurrentNodeId(draggingCurrentNodeId) {
        if (draggingCurrentNodeId === undefined) {
            return;
        }
        this.draggingCurrentNodeId = draggingCurrentNodeId;
    }

    setListItemOpacity(listItemOpacity) {
        this.listItemOpacity = listItemOpacity;
    }

    getListItemOpacity(item) {
        return item.getNodeCurrentNodeId() === this.getDraggingCurrentNodeId() ? this.listItemOpacity : 1;
    }

    getDragPopupPara() {
        return this.DRAG_POPUP;
    }

    setLastPassIndex(lastPassIndex) {
        this.lastPassIndex = lastPassIndex;
    }

    getLastPassIndex() {
        return this.lastPassIndex;
    }

    getIsParentOfInsertNode(insertNodeId) {
        if (this.currentNodeInfo === null || insertNodeId === undefined) {
            return false;
        }
        let selectedNodeItem = this.currentNodeInfo.getNodeInfoNode();
        let parentId = selectedNodeItem.currentNodeId;
        let insertParentId = this.nodeIdNodeItemMap.get(insertNodeId)?.parentNodeId;
        while (insertParentId !== undefined && insertParentId !== -1) {
            if (parentId === insertParentId) {
                return true;
            } else {
                insertParentId = this.nodeIdNodeItemMap.get(insertParentId)?.parentNodeId;
            }
        }
        return false;
    }

    setPassIndex(thisPassIndex) {
        this.thisPassIndex = thisPassIndex;
    }

    getPassIndex() {
        return this.thisPassIndex;
    }

    clearTimeOutAboutDelayHighLightAndExpand(currentIndex) {
        if (this.lastPassId !== this.INITIAL_INVALID_VALUE && this.loadedNodeIdAndIndexMap.has(this.lastPassId)) {
            let index = this.loadedNodeIdAndIndexMap.get(this.lastPassId);
            this.listNode.forEach((value) => {
                if (value.getNodeCurrentNodeId() === this.lastPassId) {
                    value.setCanShowFlagLine(false);
                    return;
                }
            });
            this.notifyDataChange(index);
        }
        if ((this.lastTimeoutHighLightId !== this.INITIAL_INVALID_VALUE &&
            this.clearTimeoutHighLightId !== this.lastTimeoutHighLightId)) {
            clearTimeout(this.lastTimeoutHighLightId);
            if (this.lastDelayHighLightIndex !== this.INITIAL_INVALID_VALUE) {
                this.clearHighLight(this.lastDelayHighLightIndex);
                let index = this.loadedNodeIdAndIndexMap
                    .get(this.listNode[this.lastDelayHighLightIndex].getNodeCurrentNodeId());
                this.notifyDataChange(index);
            }
            this.clearTimeoutHighLightId = this.lastTimeoutHighLightId;
        }
        this.lastTimeoutHighLightId = this.timeoutHighLightId;
        this.lastDelayHighLightIndex = currentIndex;
        if ((this.lastTimeoutExpandId !== this.INITIAL_INVALID_VALUE &&
            this.clearTimeoutExpandId !== this.lastTimeoutExpandId)) {
            clearTimeout(this.lastTimeoutExpandId);
            this.clearTimeoutExpandId = this.lastTimeoutExpandId;
        }
        this.lastTimeoutExpandId = this.timeoutExpandId;
        this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE;
    }

    clearHighLight(currentIndex) {
        if (!this.checkIndex(currentIndex)) {
            return;
        }
        this.changeNodeColor(currentIndex, this.listNode[currentIndex].getNodeStatus().normal);
        this.changeNodeHighLightColor(currentIndex, false);
        this.setImageSource(currentIndex, InteractionStatus.FINISH_DRAG_INSERT);
        this.setImageCollapseSource(currentIndex, InteractionStatus.FINISH_DRAG_INSERT);
        this.listNode[currentIndex].setIsHighLight(false);
    }

    changeNodeHighLightColor(index, isHighLight) {
        if (this.listNode[index].getNodeItem().mainTitleNode && this.listNode[index].getIsShowTitle()) {
            this.listNode[index].getNodeItem().mainTitleNode?.setMainTitleHighLight(isHighLight);
        }
    }

    getAccessibleTitle(insertNodeCurrentNodeId) {
        let accessibleTitleList = [];
        while (insertNodeCurrentNodeId !== -1) {
            if (insertNodeCurrentNodeId === undefined) {
                return '';
            }
            let insertNodeParentNodeId = this.findParentNodeId(insertNodeCurrentNodeId);
            let nodeItem = this.nodeIdNodeItemMap.get(insertNodeParentNodeId);
            if (nodeItem === undefined || insertNodeParentNodeId === undefined) {
                return '';
            }
            let primaryTitle = this.getNodeInfoByNodeItem(nodeItem).getNodeInfoData()?.primaryTitle === undefined
                ? '' : this.getNodeInfoByNodeItem(nodeItem).getNodeInfoData().primaryTitle;
            let secondaryTitle = this.getNodeInfoByNodeItem(nodeItem).getNodeInfoData()?.secondaryTitle === undefined
                ? '' : this.getNodeInfoByNodeItem(nodeItem).getNodeInfoData().secondaryTitle;
            let primaryTitleText = this.getAccessibleTitleText(primaryTitle);
            let secondaryTitleText = this.getAccessibleTitleText(secondaryTitle);
            accessibleTitleList.unshift(`${primaryTitleText}, ${secondaryTitleText}`);
            insertNodeCurrentNodeId = nodeItem.currentNodeId;
        }
        return accessibleTitleList.join(',');
    }

    getPlaceAccessibleTitle(insertNodeCurrentNodeId) {
        if (insertNodeCurrentNodeId === undefined) {
            return '';
        }
        let insertNodeParentNodeId = this.findParentNodeId(insertNodeCurrentNodeId);
        if (insertNodeParentNodeId === -1) {
            let accessibleTitleList = [];
            let nodeItem = this.nodeIdNodeItemMap.get(insertNodeCurrentNodeId);
            if (nodeItem === undefined || insertNodeParentNodeId === undefined) {
                return '';
            }
            let primaryTitle = this.getNodeInfoByNodeItem(nodeItem).getNodeInfoData()?.primaryTitle === undefined
                ? '' : this.getNodeInfoByNodeItem(nodeItem).getNodeInfoData().primaryTitle;
            let secondaryTitle = this.getNodeInfoByNodeItem(nodeItem).getNodeInfoData()?.secondaryTitle === undefined
                ? '' : this.getNodeInfoByNodeItem(nodeItem).getNodeInfoData().secondaryTitle;
            let primaryTitleText = this.getAccessibleTitleText(primaryTitle);
            let secondaryTitleText = this.getAccessibleTitleText(secondaryTitle);
            accessibleTitleList.unshift(`${primaryTitleText}, ${secondaryTitleText}`);
            return accessibleTitleList.join(',');
        } else {
            let accessibleTitleList = [];
            let currentNodeItem = this.nodeIdNodeItemMap.get(insertNodeCurrentNodeId);
            if (currentNodeItem === undefined || insertNodeParentNodeId === undefined) {
                return '';
            }
            let primaryTitle = this.getNodeInfoByNodeItem(currentNodeItem).getNodeInfoData()?.primaryTitle === undefined
                ? '' : this.getNodeInfoByNodeItem(currentNodeItem).getNodeInfoData().primaryTitle;
            let secondaryTitle =
                this.getNodeInfoByNodeItem(currentNodeItem).getNodeInfoData()?.secondaryTitle === undefined
                    ? '' : this.getNodeInfoByNodeItem(currentNodeItem).getNodeInfoData().secondaryTitle;
            let primaryTitleText = this.getAccessibleTitleText(primaryTitle);
            let secondaryTitleText = this.getAccessibleTitleText(secondaryTitle);
            accessibleTitleList.unshift(`${primaryTitleText}, ${secondaryTitleText}`);
            while (insertNodeCurrentNodeId !== -1) {
                if (insertNodeCurrentNodeId === undefined) {
                    return '';
                }
                let insertNodeParentNodeId = this.findParentNodeId(insertNodeCurrentNodeId);
                let nodeItem = this.nodeIdNodeItemMap.get(insertNodeParentNodeId);
                if (nodeItem === undefined || insertNodeParentNodeId === undefined) {
                    return '';
                }
                let primaryTitle = this.getNodeInfoByNodeItem(nodeItem).getNodeInfoData()?.primaryTitle === undefined
                    ? '' : this.getNodeInfoByNodeItem(nodeItem).getNodeInfoData().primaryTitle;
                let secondaryTitle =
                    this.getNodeInfoByNodeItem(nodeItem).getNodeInfoData()?.secondaryTitle === undefined
                        ? '' : this.getNodeInfoByNodeItem(nodeItem).getNodeInfoData().secondaryTitle;
                let primaryTitleText = this.getAccessibleTitleText(primaryTitle);
                let secondaryTitleText = this.getAccessibleTitleText(secondaryTitle);
                accessibleTitleList.unshift(`${primaryTitleText}, ${secondaryTitleText}`);
                insertNodeCurrentNodeId = nodeItem.currentNodeId;
            }
            return accessibleTitleList.join(',');
        }
    }

    getDraggingAccessible(allParentNode, insertNodeCurrentNodeId, insertNodeId) {
        this.getAccessibleTitle(insertNodeId);
        if (insertNodeCurrentNodeId === undefined || insertNodeId === undefined) {
            return;
        }
        let parentId = this.findParentNodeId(insertNodeId);
        let currentPlaceNode = allParentNode.indexOf(insertNodeId) + 2;
        let childrenInfo = this.getClickNodeChildrenInfo(parentId);
        let childrenItemId = childrenInfo.map(item => item.itemId);
        let insertNodePosition = childrenItemId.indexOf(insertNodeId) + 2;
        if (parentId === -1 && this.getExpandAndCollapseInfo(insertNodeCurrentNodeId) === NodeStatus.COLLAPSE ||
            parentId === -1 && this.getExpandAndCollapseInfo(insertNodeCurrentNodeId) === undefined) {
            this.sendAccessibility(this.getStringByName('treeview_accessibility_move_node_parent', currentPlaceNode));
        } else if (this.getExpandAndCollapseInfo(insertNodeCurrentNodeId) === NodeStatus.EXPAND) {
            this.sendAccessibility(this.getStringByName('treeview_accessibility_move_node_child',
                this.getAccessibleTitle(insertNodeId), 1));
        } else if (parentId !== -1) {
            this.sendAccessibility(this.getStringByName('treeview_accessibility_move_node_child',
                this.getAccessibleTitle(insertNodeId), insertNodePosition));
        }
    }

    getStringByName(resName, ...args) {
        if (resName) {
            try {
                return getContext()?.resourceManager.getStringByNameSync(resName, ...args);
            } catch (error) {
                console.error(`Ace SegmentButton getAccessibilityDescription, error: ${error.toString()}`);
            }
        }
        return '';
    }

    sendAccessibility(textAnnouncedForAccessibility) {
        let eventInfo = ({
            type: 'announceForAccessibility',
            bundleName: getContext()?.abilityInfo?.bundleName,
            triggerAction: 'common',
            textAnnouncedForAccessibility: textAnnouncedForAccessibility // 主动播报的内容。
        });
        accessibility.sendAccessibilityEvent(eventInfo);
    }

    getAccessibleTitleText(resource) {
        let resourceString = '';
        try {
            if (typeof resource === 'string') {
                resourceString = resource;
            } else {
                resourceString = getContext()?.resourceManager?.getStringSync(resource?.id);
            }
        } catch (error) {
            let code = error.code;
            let message = error.message;
            hilog.error(0x3900, 'Ace', `treeView getAccessibleTitleText error, code: ${code}, message: ${message}`);
        }
        return resourceString;
    }

    setVisibility(flag, index, isOverBorder, allParentNode) {
        let isChanged = (this.thisPassIndex !== index || this.flag !== flag) ? true : false;
        this.thisPassIndex = index;
        if ((isChanged || isOverBorder) && this.isInnerDrag) {
            this.flag = flag;
            let currentNodeId = this.getData(index)?.getNodeCurrentNodeId();
            let currentNodeLevel = this.getData(index)?.getNodeLevel();
            if (currentNodeId !== undefined) {
                currentNodeLevel = (this.expandAndCollapseInfo.get(currentNodeId) === NodeStatus.EXPAND &&
                    this.flag === Flag.DOWN_FLAG) ? (currentNodeLevel ? currentNodeLevel + 1 : undefined) :
                    currentNodeLevel;
                if (this.lastPassId !== this.INITIAL_INVALID_VALUE &&
                    this.loadedNodeIdAndIndexMap.has(this.lastPassId)) {
                    let lastIndex = this.loadedNodeIdAndIndexMap.get(this.lastPassId);
                    this.listNode.forEach((value) => {
                        if (value.getNodeCurrentNodeId() === this.lastPassId) {
                            value.setCanShowFlagLine(false);
                        }
                    });
                    this.notifyDataChange(lastIndex);
                }
                let insertNodeUpNodeId = this.getData(index - 1)?.getNodeCurrentNodeId();
                let insertNodeDownNodeId = this.getData(index + 2)?.getNodeCurrentNodeId();
                let insertNodeCurrentNodeId = this.getData(index + 1)?.getNodeCurrentNodeId();
                let nodeItem = this.nodeIdNodeItemMap.get(insertNodeCurrentNodeId);
                if (this.flag === Flag.DOWN_FLAG && index < this.totalCount() - 1) {
                    this.getData(index)?.setCanShowFlagLine(false);
                    this.getData(index + 1)?.setCanShowFlagLine(true);
                    this.getData(index)?.setCanShowBottomFlagLine(false);
                    this.getData(index + 1)?.setFlagLineLeftMargin(currentNodeLevel);
                    this.notifyDataChange(index);
                    this.notifyDataChange(index + 1);
                    this.lastPassId = this.getData(index + 1)?.getNodeCurrentNodeId();
                    let nodeItem = this.nodeIdNodeItemMap.get(insertNodeCurrentNodeId);
                    if (!nodeItem?.childNodeInfo.isHasChildNode) {
                        this.getDraggingAccessible(allParentNode, insertNodeCurrentNodeId, insertNodeCurrentNodeId);
                    } else {
                        this.getDraggingAccessible(allParentNode, insertNodeCurrentNodeId, insertNodeDownNodeId);
                    }
                } else if (this.flag === Flag.UP_FLAG && index < this.totalCount() - 1) {
                    this.getData(index)?.setCanShowFlagLine(true);
                    this.getData(index + 1)?.setCanShowFlagLine(false);
                    this.getData(index)?.setCanShowBottomFlagLine(false);
                    this.getData(index)?.setFlagLineLeftMargin(currentNodeLevel);
                    this.notifyDataChange(index);
                    this.notifyDataChange(index + 1);
                    this.lastPassId = this.getData(index)?.getNodeCurrentNodeId();
                    if (nodeItem?.childNodeInfo.isHasChildNode && nodeItem?.parentNodeId !== -1) {
                        this.getDraggingAccessible(allParentNode, insertNodeCurrentNodeId, insertNodeCurrentNodeId);
                    } else if (nodeItem?.childNodeInfo.isHasChildNode && nodeItem?.parentNodeId === -1) {
                        this.getDraggingAccessible(allParentNode, insertNodeUpNodeId, insertNodeCurrentNodeId);
                    }
                } else if (index >= this.totalCount() - 1) {
                    if (this.flag === Flag.DOWN_FLAG) {
                        this.getData(index)?.setCanShowFlagLine(false);
                        this.getData(index)?.setCanShowBottomFlagLine(true);
                    } else {
                        this.getData(index)?.setCanShowFlagLine(true);
                        this.getData(index)?.setCanShowBottomFlagLine(false);
                    }
                    this.getData(index)?.setFlagLineLeftMargin(currentNodeLevel);
                    this.notifyDataChange(index);
                    this.lastPassId = this.getData(index)?.getNodeCurrentNodeId();
                }
            }
        }
    }

    delayHighLightAndExpandNode(currentIndex, currentNodeId, showIndex) {
        let isChangIndex = currentIndex !== this.lastDelayExpandIndex ? true : false;
        let isOverBorder = this.getData(showIndex)?.getIsOverBorder();
        let insertNodeId = this.listNode[currentIndex + 1]?.getNodeCurrentNodeId();
        let insertNodeParentNodeId = this.findParentNodeId(currentNodeId);
        if (isOverBorder) {
            this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE;
        } else {
            this.lastDelayExpandIndex = currentIndex;
        }
        if (isOverBorder || isChangIndex) {
            /* highLight node time-out. */
            let canDelayHighLight = !isOverBorder && (!this.isInnerDrag ||
                (this.expandAndCollapseInfo.get(currentNodeId) === NodeStatus.COLLAPSE && this.isInnerDrag) ||
                (!this.expandAndCollapseInfo.has(currentNodeId) && this.listNode[currentIndex].getIsFolder()));
            if (canDelayHighLight) {
                /* set hoverState color before highLight. */
                this.changeNodeColor(currentIndex, this.listNode[currentIndex].getNodeStatus().hover);
                this.notifyDataChange(showIndex);
                let delayHighLightTime = this.isInnerDrag ? 1000 : 0; // ms
                this.timeoutHighLightId = setTimeout(() => {
                    this.delayHighLight(currentIndex);
                    this.sendAccessibility(this.getStringByName('treeview_accessibility_move_node_child',
                        this.getPlaceAccessibleTitle(currentNodeId), 1));
                }, delayHighLightTime);
            }
            if (isOverBorder || (this.lastTimeoutHighLightId !== this.INITIAL_INVALID_VALUE &&
                this.clearTimeoutHighLightId !== this.lastTimeoutHighLightId)) {
                clearTimeout(this.lastTimeoutHighLightId);
                if (this.lastDelayHighLightIndex !== this.INITIAL_INVALID_VALUE) {
                    this.clearHighLight(this.lastDelayHighLightIndex);
                    this.notifyDataReload();
                }
                this.clearTimeoutHighLightId = this.lastTimeoutHighLightId;
            }
            this.lastTimeoutHighLightId = this.timeoutHighLightId;
            this.lastDelayHighLightIndex = currentIndex;
            /* alter flagLine and expand node time-out. */
            if (!isOverBorder && this.expandAndCollapseInfo.get(currentNodeId) === NodeStatus.COLLAPSE) {
                let firstChildNodeId = this.getData(showIndex)?.getNodeInfoNode().children[0]?.currentNodeId;
                let delayAlterFlagLineAndExpandNodeTime = 2000; // ms
                this.timeoutExpandId = setTimeout(() => {
                    this.clearHighLight(this.lastDelayHighLightIndex);
                    if (firstChildNodeId !== undefined) {
                        this.alterFlagLineAndExpandNode(currentIndex, firstChildNodeId);
                    }
                }, delayAlterFlagLineAndExpandNodeTime);
            }
            if (isOverBorder || (this.lastTimeoutExpandId !== this.INITIAL_INVALID_VALUE &&
                this.clearTimeoutExpandId !== this.lastTimeoutExpandId)) {
                clearTimeout(this.lastTimeoutExpandId);
                this.clearTimeoutExpandId = this.lastTimeoutExpandId;
            }
            this.lastTimeoutExpandId = this.timeoutExpandId;
        }
    }

    delayHighLight(currentIndex) {
        this.listNode.forEach((value) => {
            if (value.getNodeCurrentNodeId() === this.lastPassId) {
                value.setCanShowFlagLine(false);
                value.setCanShowBottomFlagLine(false);
                return;
            }
        });
        this.changeNodeColor(currentIndex, this.listNode[currentIndex].getNodeStatus().highLight);
        this.listNode[currentIndex].setIsHighLight(true);
        this.changeNodeHighLightColor(currentIndex, true);
        this.setImageSource(currentIndex, InteractionStatus.DRAG_INSERT);
        this.setImageCollapseSource(currentIndex, InteractionStatus.DRAG_INSERT);
        this.notifyDataReload();
    }

    alterFlagLineAndExpandNode(currentIndex, firstChildNodeId) {
        this.listNode.forEach((value) => {
            if (value.getNodeCurrentNodeId() === this.lastPassId) {
                value.setCanShowFlagLine(false);
                value.setCanShowBottomFlagLine(false);
            }
        });
        this.listNode.forEach((value) => {
            if (this.isInnerDrag && value.getNodeCurrentNodeId() === firstChildNodeId) {
                value.setCanShowFlagLine(true);
            }
        });
        this.changeNodeStatus(currentIndex);
        this.handleExpandAndCollapse(currentIndex, true);
        this.lastPassId = firstChildNodeId;
    }

    hideLastLine() {
        if (this.lastPassId !== this.INITIAL_INVALID_VALUE && this.loadedNodeIdAndIndexMap.has(this.lastPassId)) {
            this.listNode.forEach((value) => {
                if (value.getNodeCurrentNodeId() === this.lastPassId) {
                    value.setCanShowFlagLine(false);
                    value.setCanShowBottomFlagLine(false);
                    return;
                }
            });
            let index = this.loadedNodeIdAndIndexMap.get(this.lastPassId);
            this.notifyDataChange(index);
        }
    }

    clearLastTimeoutHighLight() {
        if (this.lastTimeoutHighLightId !== this.INITIAL_INVALID_VALUE &&
            this.clearTimeoutHighLightId !== this.lastTimeoutHighLightId) {
            clearTimeout(this.lastTimeoutHighLightId);
            if (this.lastDelayHighLightIndex !== this.INITIAL_INVALID_VALUE) {
                this.clearHighLight(this.lastDelayHighLightIndex);
            }
        }
    }

    clearLastTimeoutExpand() {
        if (this.lastTimeoutExpandId !== this.INITIAL_INVALID_VALUE &&
            this.clearTimeoutExpandId !== this.lastTimeoutExpandId) {
            clearTimeout(this.lastTimeoutExpandId);
        }
    }

    getSubtitle(currentNodeId) {
        if (this.nodeIdAndSubtitleMap.has(currentNodeId)) {
            if (typeof this.nodeIdAndSubtitleMap.get(currentNodeId) === 'number') {
                return this.nodeIdAndSubtitleMap.get(currentNodeId)?.toString();
            } else {
                return this.nodeIdAndSubtitleMap.get(currentNodeId);
            }
        } else {
            return '';
        }
    }

    hasSubtitle(currentNodeId) {
        return this.nodeIdAndSubtitleMap.has(currentNodeId);
    }

    initialParameterAboutDelayHighLightAndExpandIndex() {
        this.lastDelayHighLightIndex = this.INITIAL_INVALID_VALUE;
        this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE;
        this.lastPassIndex = this.INITIAL_INVALID_VALUE;
        this.draggingCurrentNodeId = this.INITIAL_INVALID_VALUE;
        this.flag = Flag.NONE;
    }

    refreshSubtitle(insertNodeCurrentNodeId) {
        this.nodeIdAndSubtitleMap.set(this.selectedParentNodeId, this.selectedParentNodeSubtitle);
        this.nodeIdAndSubtitleMap.set(insertNodeCurrentNodeId, this.insertNodeSubtitle);
        this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.selectedParentNodeId));
        this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(insertNodeCurrentNodeId));
    }

    setNodeSubtitlePara(selectedParentNodeId, selectedParentNodeSubtitle, insertNodeSubtitle) {
        this.selectedParentNodeId = selectedParentNodeId;
        this.selectedParentNodeSubtitle = selectedParentNodeSubtitle;
        this.insertNodeSubtitle = insertNodeSubtitle;
    }

    getInsertNodeSubtitle() {
        return this.insertNodeSubtitle;
    }

    getExpandAndCollapseInfo(currentNodeId) {
        return this.expandAndCollapseInfo.get(currentNodeId);
    }

    getLastDelayHighLightId() {
        return this.lastDelayHighLightId;
    }

    setLastDelayHighLightId() {
        this.listNode.forEach((value, index) => {
            if (index === this.lastDelayHighLightIndex) {
                this.lastDelayHighLightId = value.getNodeCurrentNodeId();
            }
        });
    }

    setLastPassId(lastPassId) {
        this.lastPassId = lastPassId;
    }

    setLastDelayHighLightIndex(lastDelayHighLightIndex) {
        this.lastDelayHighLightIndex = lastDelayHighLightIndex;
    }

    /**
     * Alter the current node location to a needful position.
     * 1.Create an array named 'dragNodeParam' to store dragging node information.
     * 2.Delete the dragging node from the tree.
     * 3.Add the dragging node to the tree.
     */
    alterDragNode(rearParentNodeId, rearCurrentNodeId, dragParentNodeId, dragCurrentNodeId, frontNodeInfoItem) {
        let dragNodeParam = [];
        let parentNodeId = rearParentNodeId;
        let currentNodeId = dragCurrentNodeId;
        let nodeParam = frontNodeInfoItem.getNodeInfoData();
        let nodeInfo = null;
        let nodeInfoNode = frontNodeInfoItem.getNodeInfoNode();
        let isHighLight = false;
        let insertChildIndex = this.INITIAL_INVALID_VALUE;
        let currentChildIndex = this.INITIAL_INVALID_VALUE;
        let isDownFlag = this.flag === Flag.DOWN_FLAG ? true : false;
        currentChildIndex = this.getChildIndex(dragParentNodeId, dragCurrentNodeId);
        insertChildIndex = this.getChildIndex(rearParentNodeId, rearCurrentNodeId) + 1;
        if (rearParentNodeId !== dragParentNodeId) {
            insertChildIndex = isDownFlag ? insertChildIndex + 1 : insertChildIndex;
        } else {
            if (insertChildIndex > currentChildIndex) {
                insertChildIndex = isDownFlag ? insertChildIndex : insertChildIndex - 1;
            } else {
                insertChildIndex = isDownFlag ? insertChildIndex + 1 : insertChildIndex;
            }
        }
        for (let i = 0; i < this.listNode.length; i++) {
            if (this.listNode[i].getNodeCurrentNodeId() === rearCurrentNodeId) {
                isHighLight = this.listNode[i].getIsHighLight();
                if (this.flag === Flag.DOWN_FLAG &&
                    this.expandAndCollapseInfo.get(rearCurrentNodeId) === NodeStatus.EXPAND) {
                    parentNodeId = rearCurrentNodeId;
                    insertChildIndex = 0;
                } else if (this.flag === Flag.UP_FLAG && this.expandAndCollapseInfo.get(rearCurrentNodeId) ===
                    NodeStatus.EXPAND &&
                    this.listNode[i].getCanShowFlagLine() === false) {
                    parentNodeId = rearCurrentNodeId;
                    insertChildIndex = 0;
                } else if (isHighLight) {
                    parentNodeId = rearCurrentNodeId;
                    insertChildIndex = 0;
                }
                break;
            }
        }
        let callbackParam = {
            currentNodeId: currentNodeId,
            parentNodeId: parentNodeId,
            childIndex: insertChildIndex,
        };
        /* export inner drag node Id. */
        this.appEventBus.emitNodeMove(callbackParam);
        /* To store dragging node information by the array named 'dragNodeParam'. */
        dragNodeParam.push({ parentId: parentNodeId, currentId: currentNodeId, data: nodeParam });
        let callback = (node, listNode) => {
            if (node) {
                parentNodeId = node.parentNodeId;
                currentNodeId = node.currentNodeId;
                for (let i = 0; i < listNode.length; i++) {
                    if (listNode[i].getNodeCurrentNodeId() === currentNodeId) {
                        nodeInfo = listNode[i];
                        break;
                    }
                }
                if (nodeInfo === null) {
                    return false;
                }
                let nodeParam = nodeInfo.getNodeInfoData();
                if (parentNodeId !== dragParentNodeId) {
                    dragNodeParam.push({ parentId: parentNodeId, currentId: currentNodeId, data: nodeParam });
                }
                return false;
            }
            return false;
        };
        this.dragTraverseNodeDF(callback, nodeInfoNode, this.listNode);
        /* Delete the dragging node from the tree. */
        let removeNodeIdList = this.removeNode(dragCurrentNodeId, dragParentNodeId);
        if (removeNodeIdList.length === 0) {
            return;
        }
        /**
         * Add the dragging node to the tree
         * 1.The first dragging node is added singly, because it needs to distinguish the position to insert
         *
         * Add first node.
         */
        let insertCurrentNodeId = rearCurrentNodeId;
        let isAfter = isDownFlag;
        if (this.expandAndCollapseInfo.get(rearCurrentNodeId) === NodeStatus.EXPAND) {
            isAfter = false;
            this.listNode.forEach((value) => {
                if (value.getNodeCurrentNodeId() === rearCurrentNodeId && value.getCanShowFlagLine() === false) {
                    if (value.getNodeInfoNode().children.length) {
                        insertCurrentNodeId = value.getNodeInfoNode().children[0].currentNodeId;
                    } else {
                        insertCurrentNodeId = this.INITIAL_INVALID_VALUE;
                    }
                }
            });
        } else if (!this.expandAndCollapseInfo.get(rearCurrentNodeId) && isHighLight) {
            this.expandAndCollapseInfo.set(rearCurrentNodeId, NodeStatus.EXPAND);
        }
        let addDragNodeResult =
            this.addDragNode(dragNodeParam[0].parentId, dragNodeParam[0].currentId, insertCurrentNodeId, isAfter,
                dragNodeParam[0].data);
        if (!addDragNodeResult) {
            return;
        }
        /* Add remaining node. */
        for (let j = 1; j < dragNodeParam.length; j++) {
            let addNodeResult =
                this.addNode(dragNodeParam[j].parentId, dragNodeParam[j].currentId, dragNodeParam[j].data, false);
            if (!addNodeResult) {
                return;
            }
        }
        /* Update node data and reload the array named 'listNode'. */
        for (let i = 0; i < this.listNode.length; i++) {
            if (this.listNode[i].getNodeCurrentNodeId() === dragParentNodeId) {
                if (this.listNode[i].getNodeItem().imageCollapse === null) {
                    this.listNode[i].handleImageCollapseAfterAddNode(false);
                    this.expandAndCollapseInfo.delete(dragParentNodeId);
                    break;
                }
            }
        }
        let tmp = [...this.listNode];
        this.reloadListNode(tmp);
    }

    /**
     * Reload the array named 'listNode'
     * @param tmp
     */
    reloadListNode(tmp) {
        let index = 0;
        let listIndex = 0;
        this.listNode.splice(0, this.listNode.length);
        this.loadedNodeIdAndIndexMap.clear();
        this.loadedListNode.splice(0, this.loadedListNode.length);
        this.traverseNodeDF((node) => {
            let currentNodeId = node.currentNodeId;
            if (currentNodeId >= 0) {
                if (this.nodeIdNodeParamMap.has(currentNodeId)) {
                    let nodeInfo = new NodeInfo(node, this.nodeIdNodeParamMap.get(currentNodeId));
                    nodeInfo.addImageCollapse(node.getChildNodeInfo().isHasChildNode);
                    this.listNode.push(nodeInfo);
                    this.nodeIdAndNodeIndexMap.set(nodeInfo.getNodeCurrentNodeId(), listIndex++);
                    if (this.expandAndCollapseInfo.get(currentNodeId) === NodeStatus.EXPAND) {
                        nodeInfo.getNodeItem()
                            .imageCollapse =
                            CollapseImageNodeFlyweightFactory.changeImageCollapseSource(NodeStatus.EXPAND,
                                nodeInfo.getNodeItem().imageCollapse?.isCollapse);
                    } else if (this.expandAndCollapseInfo.get(currentNodeId) === NodeStatus.COLLAPSE) {
                        nodeInfo.getNodeItem()
                            .imageCollapse =
                            CollapseImageNodeFlyweightFactory.changeImageCollapseSource(NodeStatus.COLLAPSE,
                                nodeInfo.getNodeItem().imageCollapse?.isCollapse);
                    }
                    for (let i = 0; i < tmp.length; i++) {
                        if (tmp[i].getNodeCurrentNodeId() === nodeInfo.getNodeCurrentNodeId()) {
                            nodeInfo.setNodeIsShow(tmp[i].getNodeIsShow());
                            nodeInfo.setListItemHeight(tmp[i].getListItemHeight());
                            if (nodeInfo.getNodeItem().mainTitleNode && nodeInfo.getIsShowTitle()) {
                                nodeInfo.getNodeItem().mainTitleNode.title = tmp[i].getNodeItem().mainTitleNode?.title;
                            }
                            break;
                        }
                    }
                    if (nodeInfo.getNodeIsShow()) {
                        this.loadedNodeIdAndIndexMap.set(nodeInfo.getNodeCurrentNodeId(), index++);
                        this.loadedListNode.push(nodeInfo);
                    }
                }
            }
            return false;
        });
    }

    getFlagLine() {
        return this.FLAG_LINE;
    }

    getVisibility(nodeInfo) {
        let lastShowIndex = this.loadedNodeIdAndIndexMap.get(nodeInfo.getNodeCurrentNodeId()) - 1;
        if (lastShowIndex > this.INITIAL_INVALID_VALUE) {
            let lastNodeInfo = this.getData(lastShowIndex);
            return (nodeInfo.getCanShowFlagLine() === true && !nodeInfo.getIsHighLight() &&
                !lastNodeInfo?.getIsHighLight()) ?
                Visibility.Visible : Visibility.Hidden;
        } else {
            return (nodeInfo.getCanShowFlagLine() === true && !nodeInfo.getIsHighLight()) ?
                Visibility.Visible : Visibility.Hidden;
        }
    }

    getSubTitlePara() {
        return this.subTitle;
    }

    getIsFolder(nodeId) {
        if (this.loadedNodeIdAndIndexMap.has(nodeId)) {
            return this.getData(this.loadedNodeIdAndIndexMap.get(nodeId))?.getIsFolder();
        }
        return false;
    }

    getSubTitleFontColor(isHighLight) {
        return isHighLight ? this.subTitle.highLightFontColor : this.treeViewTheme.secondaryTitleFontColor;
    }

    getChildIndex(rearParentNodeId, rearCurrentNodeId) {
        let insertChildIndex = this.INITIAL_INVALID_VALUE;
        if (this.nodeIdNodeItemMap.has(rearParentNodeId)) {
            let node = this.nodeIdNodeItemMap.get(rearParentNodeId);
            if (node.getCurrentNodeId() === rearParentNodeId) {
                node.children.forEach((value, index) => {
                    if (value.getCurrentNodeId() === rearCurrentNodeId) {
                        insertChildIndex = index;
                        return;
                    }
                });
            }
        }
        return insertChildIndex;
    }

    setCurrentFocusNodeId(focusNodeId) {
        this.currentFocusNodeId = focusNodeId;
    }

    getCurrentFocusNodeId() {
        return this.currentFocusNodeId;
    }

    setLastFocusNodeId(focusNodeId) {
        this.lastFocusNodeId = focusNodeId;
    }

    getLastFocusNodeId() {
        return this.lastFocusNodeId;
    }

    getAddFocusNodeId() {
        return this.addFocusNodeId;
    }

    setFlag(flag) {
        this.flag = flag;
    }

    traverseNodeDF(callback, root = this._root) {
        let stack = [];
        let found = false;
        stack.unshift(root);
        let currentNode = stack.shift();
        while (!found && currentNode) {
            found = callback(currentNode) === true;
            if (!found) {
                stack.unshift(...currentNode.children);
                currentNode = stack.shift();
            }
        }
    }

    traverseSectionNodeDF(callback, root = this._root, startLevel, endLevel) {
        let stack = [];
        let found = false;
        let isPassNode = false;
        stack.unshift(root);
        let currentNode = stack.shift();
        while (!found && currentNode) {
            try {
                if (startLevel !== undefined && currentNode.nodeLevel < startLevel) {
                    isPassNode = true;
                }
                if (endLevel !== undefined && currentNode.nodeLevel > endLevel) {
                    isPassNode = true;
                }
                if (!isPassNode) {
                    found = callback(currentNode);
                }
            } catch (err) {
                throw new Error('traverseSectionNodeDF function callbacks error');
            }
            if (!found) {
                stack.unshift(...currentNode.children);
                currentNode = stack.shift();
                isPassNode = false;
            }
        }
    }

    updateParentChildNum(parentNode, isAdd, count) {
        let parentNodeId = parentNode.parentNodeId;
        while (parentNodeId >= 0) {
            if (this.nodeIdNodeItemMap.has(parentNodeId)) {
                let parent = this.nodeIdNodeItemMap.get(parentNodeId);
                parent.getChildNodeInfo().allChildNum =
                    isAdd ? parent.getChildNodeInfo().allChildNum + count :
                        parent.getChildNodeInfo().allChildNum - count;
                parentNodeId = parent.parentNodeId;
            } else {
                hilog.error(LOG_CODE, TAG, 'updateParentChildNum: parent node not found.');
                break;
            }
        }
    }

    /**
     * find parent node id
     *
     * @param currentNodeId current node id
     * @returns parent node id
     */
    findParentNodeId(currentNodeId) {
        let current = new NodeItem(emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(currentNodeId)) {
            current = this.nodeIdNodeItemMap.get(currentNodeId);
        }
        return current.parentNodeId;
    }

    refreshRemoveNodeData(removeNodeIdList, parentNodeInfo) {
        let deleteIndexList = [];
        if (removeNodeIdList.length === 0) {
            return;
        }
        let startIndex = undefined;
        for (let i = 0; i < removeNodeIdList.length; i++) {
            if (this.loadedNodeIdAndIndexMap.has(removeNodeIdList[i])) {
                let loadedIndex = this.loadedNodeIdAndIndexMap.get(removeNodeIdList[i]);
                deleteIndexList.push(loadedIndex);
            }
            if (startIndex === undefined && this.nodeIdAndNodeIndexMap.has(removeNodeIdList[i])) {
                startIndex = this.nodeIdAndNodeIndexMap.get(removeNodeIdList[i]);
            }
            if (startIndex !== undefined) {
                let deleteNode = this.listNode.splice(startIndex, 1);
                deleteNode = null;
            }
            if (this.expandAndCollapseInfo.has(removeNodeIdList[i])) {
                this.expandAndCollapseInfo.delete(removeNodeIdList[i]);
            }
        }
        deleteIndexList.forEach((value) => {
            this.notifyDataDelete(value);
            this.notifyDataChange(value);
        });
        if (parentNodeInfo.getNodeItem().imageCollapse === null) {
            if (this.nodeIdAndNodeIndexMap.has(parentNodeInfo.getNodeCurrentNodeId())) {
                let parentIndex = this.nodeIdAndNodeIndexMap.get(parentNodeInfo.getNodeCurrentNodeId());
                this.listNode[parentIndex]?.handleImageCollapseAfterAddNode(false);
            }
            this.expandAndCollapseInfo.delete(parentNodeInfo.getNodeCurrentNodeId());
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(parentNodeInfo.getNodeCurrentNodeId()));
        }
        let callbackParam = {
            currentNodeId: parentNodeInfo.getNodeCurrentNodeId(),
            parentNodeId: parentNodeInfo.getNodeParentNodeId(),
        };
        this.loadedListNodeFunction();
        this.appEventBus.emitNodeDelete(callbackParam);
    }

    refreshAddNodeData(addNodeIdList) {
        let addNodeInfo = new NodeInfo(new NodeItem(emptyNodeInfo), emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(addNodeIdList[0])) {
            let node = this.nodeIdNodeItemMap.get(addNodeIdList[0]);
            addNodeInfo = new NodeInfo(node, this.nodeIdNodeParamMap.get(addNodeIdList[0]));
            addNodeInfo.addImageCollapse(node.getChildNodeInfo().isHasChildNode);
        }
        addNodeInfo.setIsModify(true);
        let index = 0;
        for (let i = 0; i < this.listNode.length; i++) {
            if (this.listNode[i].getNodeCurrentNodeId() === addNodeInfo.getNodeParentNodeId()) {
                index = i;
                if (this.listNode[i].getNodeItem().imageCollapse === null) {
                    this.listNode[i].handleImageCollapseAfterAddNode(true);
                    this.notifyDataChange(index);
                } else if (this.expandAndCollapseInfo.get(this.listNode[i].getNodeCurrentNodeId()) ===
                    NodeStatus.COLLAPSE) {
                    this.changeNodeStatus(index);
                }
                this.listNode.splice(i + 1, 0, addNodeInfo);
                this.listNode[i + 1].setTitleAndInputTextStatus(true);
                this.listNode[i + 1].setNodeIsShow(true);
                this.listNode[i + 1].setListItemHeight(LIST_ITEM_HEIGHT);
                this.nodeIdAndNodeIndexMap.set(addNodeIdList[0], i + 1);
                this.setImageSource(i + 1, InteractionStatus.EDIT);
                this.currentOperation = MenuOperation.ADD_NODE;
                this.notifyDataAdd(i + 1);
                this.notificationNodeInfo(i + 1, this.currentOperation);
                break;
            }
        }
        this.modifyNodeIndex = index + 1;
        this.setClickIndex(index);
        this.lastIndex = index;
        this.expandAndCollapseInfo.set(addNodeInfo.getNodeParentNodeId(), NodeStatus.EXPAND);
        this.handleExpandAndCollapse(index, true);
    }

    refreshData(operation, parentNodeId, changeNodeIdList) {
        let parentNodeInfo = new NodeInfo(new NodeItem(emptyNodeInfo), emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(parentNodeId)) {
            let parentNode = this.nodeIdNodeItemMap.get(parentNodeId);
            parentNodeInfo = new NodeInfo(parentNode, this.nodeIdNodeParamMap.get(parentNodeId));
            parentNodeInfo.addImageCollapse(parentNode.getChildNodeInfo().isHasChildNode);
        }
        if (operation === MenuOperation.REMOVE_NODE) {
            this.nodeIdAndSubtitleMap.set(parentNodeId, this.selectedParentNodeSubtitle);
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(parentNodeId));
            this.refreshRemoveNodeData(changeNodeIdList, parentNodeInfo);
        }
        if (operation === MenuOperation.ADD_NODE) {
            this.addFocusNodeId = changeNodeIdList[0];
            this.nodeIdAndSubtitleMap.set(this.getClickNodeId(), this.selectedParentNodeSubtitle);
            this.nodeIdAndSubtitleMap.set(changeNodeIdList[0], this.insertNodeSubtitle);
            this.refreshAddNodeData(changeNodeIdList);
        }
    }

    /**
     * remove node
     *
     * @param currentNodeId current node id
     * @param parentNodeId  parent node id
     * @returns node id list which is removed
     */
    removeNode(currentNodeId, parentNodeId) {
        if (this.nodeIdNodeItemMap.has(parentNodeId) && this.nodeIdNodeItemMap.has(currentNodeId)) {
            let parent = this.nodeIdNodeItemMap.get(parentNodeId);
            let current = this.nodeIdNodeItemMap.get(currentNodeId);
            let removeNodeIdList = [];
            let index = current.indexOfParent;
            let deleteNodeAllChildNum = 0;
            if (index < 0) {
                hilog.error(LOG_CODE, TAG, 'node does not exist.');
                return [];
            } else {
                deleteNodeAllChildNum = parent.children[index].getChildNodeInfo().allChildNum + 1;
                this.freeNodeMemory(parent.children[index], removeNodeIdList);
                for (let i = index; i < parent.children.length; i++) {
                    parent.children[i].indexOfParent -= 1;
                }
                let node = parent.children.splice(index, 1);
                node = null;
                this.judgeImageCollapse(parentNodeId);
            }
            parent.getChildNodeInfo().childNum = parent.children.length;
            parent.getChildNodeInfo().allChildNum -= (deleteNodeAllChildNum);
            let updateNodeIdList = [];
            updateNodeIdList.push(parent.parentNodeId);
            delayUpdateParentChildNum(false, deleteNodeAllChildNum, this.nodeIdNodeItemMap, updateNodeIdList);
            return removeNodeIdList;
        } else {
            hilog.error(LOG_CODE, TAG, 'parent does not exist.');
            return [];
        }
    }

    addNode(parentNodeId, currentNodeId, data, initBuild) {
        if (this._root === null) {
            this._root = new NodeItem(emptyNodeInfo);
            this._root.nodeLevel = -1;
            this.nodeIdNodeItemMap.set(-1, this._root);
            this.nodeIdNodeParamMap.set(-1, emptyNodeInfo);
        }
        if (this.nodeIdNodeItemMap.has(parentNodeId)) {
            let parent = this.nodeIdNodeItemMap.get(parentNodeId);
            let currentNode = new NodeItem(data);
            if (parent.nodeLevel > this.maxNodeLevel) {
                hilog.error(LOG_CODE, TAG, 'ListDataSource[addNode]: The level of the tree view cannot exceed 50.');
                return false;
            }
            currentNode.nodeLevel = parent.nodeLevel + 1;
            currentNode.parentNodeId = parentNodeId;
            currentNode.currentNodeId = currentNodeId;
            currentNode.indexOfParent = parent.children.length;
            data.parentNodeId = parentNodeId;
            data.currentNodeId = currentNodeId;
            if (data.symbolIconStyle && !data.icon) {
                data.icon = 'symbolUsed';
            }
            parent.children.push(currentNode);
            parent.getChildNodeInfo().isHasChildNode = true;
            parent.getChildNodeInfo().childNum = parent.children.length;
            parent.getChildNodeInfo().allChildNum += 1;
            this.judgeImageCollapse(parentNodeId);
            if (initBuild) {
                this.updateNodeIdList.push(parent.parentNodeId);
            } else {
                let updateNodeIdList = [];
                updateNodeIdList.push(parent.parentNodeId);
                delayUpdateParentChildNum(true, 1, this.nodeIdNodeItemMap, updateNodeIdList);
            }
            this.nodeIdNodeParamMap.set(currentNodeId, data);
            this.nodeIdNodeItemMap.set(currentNodeId, currentNode);
            return true;
        } else {
            hilog.error(LOG_CODE, TAG, 'ListDataSource[addNode]: Parent node not found.');
            return false;
        }
    }

    judgeImageCollapse(parentNodeId) {
        if (parentNodeId === undefined) {
            return;
        }
        let parent = this.nodeIdNodeItemMap.get(parentNodeId);
        let parentIndex = this.nodeIdAndNodeIndexMap.get(parentNodeId);
        if (parent.children.length > 0) {
            if (this.nodeIdAndNodeIndexMap.has(parentNodeId)) {
                this.listNode[parentIndex]?.addImageExpand(true);
            }
        } else {
            this.listNode[parentIndex]?.addImageExpand(false);
        }
    }

    freeNodeMemory(rootNode, removeNodeIdList) {
        let deleteNode = [];
        let callback = (node) => {
            deleteNode.push(node);
            return false;
        };
        this.traverseNodeDF(callback, rootNode);
        deleteNode.forEach((value) => {
            removeNodeIdList.push(value.getCurrentNodeId());
            this.nodeIdNodeItemMap.delete(value.getCurrentNodeId());
            this.nodeIdNodeParamMap.delete(value.getCurrentNodeId());
            value = new NodeItem(emptyNodeInfo);
        });
    }

    getNodeInfoByNodeItem(nodeItem) {
        if (nodeItem?.currentNodeId === undefined) {
            hilog.error(LOG_CODE, TAG, 'getNodeInfoByNodeItem: currentId is undefined');
            return new NodeInfo(new NodeItem(emptyNodeInfo), emptyNodeInfo);
        }
        if (!this.nodeIdAndNodeIndexMap.has(nodeItem.currentNodeId)) {
            hilog.error(LOG_CODE, TAG, 'getNodeInfoByNodeItem: not has nodeItem.');
            return new NodeInfo(new NodeItem(emptyNodeInfo), emptyNodeInfo);
        }
        let index = this.nodeIdAndNodeIndexMap.get(nodeItem.currentNodeId);
        return this.listNode[index];
    }

    getNewNodeParam(nodeId) {
        let parent = new NodeItem(emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(nodeId)) {
            parent = this.nodeIdNodeItemMap.get(nodeId);
        }
        let newNodeParam = emptyNodeInfo;
        if (parent) {
            let nodeInfo = this.getNodeInfoByNodeItem(parent);
            if (parent.children.length === 0) {
                if (nodeInfo.getNodeItem().imageNode !== undefined) {
                    newNodeParam.icon = nodeInfo.getNodeItem().imageNode?.normalSource;
                    newNodeParam.symbolIconStyle = nodeInfo.getNodeItem().imageNode?.symbolNormalSource;
                    newNodeParam.selectedIcon = nodeInfo.getNodeItem().imageNode?.selectedSource;
                    newNodeParam.symbolSelectedIconStyle = nodeInfo.getNodeItem().imageNode?.symbolSelectedSource;
                    newNodeParam.editIcon = nodeInfo.getNodeItem().imageNode?.editSource;
                    newNodeParam.symbolEditIconStyle = nodeInfo.getNodeItem().imageNode?.symbolEditSource;
                    newNodeParam.container = nodeInfo.getMenu();
                } else {
                    newNodeParam.icon = undefined;
                    newNodeParam.symbolIconStyle = undefined;
                    newNodeParam.selectedIcon = undefined;
                    newNodeParam.symbolSelectedIconStyle = undefined;
                    newNodeParam.editIcon = undefined;
                    newNodeParam.symbolEditIconStyle = undefined;
                    newNodeParam.container = nodeInfo.getMenu();
                }
            } else if (parent.children.length > 0) {
                let childNodeInfo = this.getNodeInfoByNodeItem(parent.children[0]);
                if (nodeInfo.getNodeItem().imageNode !== null) {
                    newNodeParam.icon = (childNodeInfo.getNodeItem().imageNode !== undefined) ?
                        childNodeInfo.getNodeItem().imageNode?.normalSource : undefined;
                    newNodeParam.symbolIconStyle = (childNodeInfo.getNodeItem().imageNode !== undefined) ?
                        childNodeInfo.getNodeItem().imageNode?.symbolNormalSource : undefined;
                    newNodeParam.selectedIcon = (childNodeInfo.getNodeItem().imageNode !== undefined) ?
                        childNodeInfo.getNodeItem().imageNode?.selectedSource : undefined;
                    newNodeParam.symbolSelectedIconStyle = (childNodeInfo.getNodeItem().imageNode !== undefined) ?
                        childNodeInfo.getNodeItem().imageNode?.symbolSelectedSource : undefined;
                    newNodeParam.editIcon = (childNodeInfo.getNodeItem().imageNode !== undefined) ?
                        childNodeInfo.getNodeItem().imageNode?.editSource : undefined;
                    newNodeParam.symbolEditIconStyle = (childNodeInfo.getNodeItem().imageNode !== undefined) ?
                        childNodeInfo.getNodeItem().imageNode?.symbolEditSource : undefined;
                    newNodeParam.container = childNodeInfo.getMenu();
                } else {
                    newNodeParam.icon = undefined;
                    newNodeParam.symbolIconStyle = undefined;
                    newNodeParam.selectedIcon = undefined;
                    newNodeParam.symbolSelectedIconStyle = undefined;
                    newNodeParam.editIcon = undefined;
                    newNodeParam.symbolEditIconStyle = undefined;
                    newNodeParam.container = childNodeInfo.getMenu();
                }
            }
        }
        return newNodeParam;
    }

    /**
     * get child node ids by node id
     *
     * @param nodeId node id
     * @returns child node ids
     */
    getClickChildId(nodeId) {
        let parent = new NodeItem(emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(nodeId)) {
            parent = this.nodeIdNodeItemMap.get(nodeId);
        }
        if (parent) {
            if (parent.children.length === 0) {
                return [];
            } else if (parent.children.length > 0) {
                let childrenNodeInfo = new Array(parent.children.length);
                for (let i = 0; i < childrenNodeInfo.length; i++) {
                    childrenNodeInfo[i] = 0;
                }
                for (let i = 0; i < parent.children.length && i < childrenNodeInfo.length; i++) {
                    childrenNodeInfo[i] = parent.children[i].currentNodeId;
                }
                return childrenNodeInfo;
            }
        }
        return [];
    }

    /**
     * get child nodeInfo views by node id
     *
     * @param nodeId node id
     * @returns child nodeInfo views
     */
    getClickNodeChildrenInfo(nodeId) {
        let parent = new NodeItem(emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(nodeId)) {
            parent = this.nodeIdNodeItemMap.get(nodeId);
        }
        if (parent) {
            if (parent.children.length === 0) {
                return [];
            } else if (parent.children.length > 0) {
                let childrenNodeInfo = new Array(parent.children.length);
                for (let i = 0; i < childrenNodeInfo.length; i++) {
                    childrenNodeInfo[i] = {};
                }
                for (let i = 0; i < parent.children.length && i < childrenNodeInfo.length; i++) {
                    childrenNodeInfo[i].itemId = parent.children[i].currentNodeId;
                    let nodeInfo = this.getNodeInfoByNodeItem(parent.children[i]);
                    if (nodeInfo.getNodeItem().imageNode) {
                        childrenNodeInfo[i].itemIcon = nodeInfo.getNodeItem().imageNode?.source;
                    }
                    if (nodeInfo.getNodeItem().mainTitleNode) {
                        childrenNodeInfo[i].itemTitle = nodeInfo.getNodeItem().mainTitleNode?.title;
                    }
                    childrenNodeInfo[i].isFolder = nodeInfo.getIsFolder();
                }
                return childrenNodeInfo;
            }
        }
        return [];
    }

    /**
     * check main title is valid
     *
     * @param title main title
     * @returns check result
     */
    checkMainTitleIsValid(title) {
        if (new RegExp('/[\\\/:*?"<>|]/').test(title)) {
            return false;
        }
        if ((new RegExp('/^[\u4e00-\u9fa5]+$/').test(title) && title.length > this.MAX_CN_LENGTH) ||
            (!new RegExp('/^[\u4e00-\u9fa5]+$/').test(title) && title.length > this.MAX_EN_LENGTH)) {
            return false;
        }
        return true;
    }

    /**
     * DFS: Depth first traversal in drag event.
     *
     * @param callback dfs callback fuction
     */
    dragTraverseNodeDF(callback, root = this._root, listNode) {
        let stack = [];
        let found = false;
        stack.unshift(root);
        let currentNode = stack.shift();
        while (!found && currentNode) {
            found = callback(currentNode, listNode) === true;
            if (!found) {
                stack.unshift(...currentNode.children);
                currentNode = stack.shift();
            }
        }
    }

    updateChildIndexOfParent(insertIndex, parent) {
        for (let i = insertIndex; i < parent.children.length; i++) {
            parent.children[i].indexOfParent += 1;
        }
    }

    /**
     * Add the first dragging node in dragging nodes
     * 1.the first dragging node needs to distinguish the position to insert
     */
    addDragNode(parentNodeId, currentNodeId, insertCurrentNodeId, isAfter, data) {
        if (this._root === null) {
            this._root = new NodeItem(emptyNodeInfo);
            this._root.nodeLevel = this.INITIAL_INVALID_VALUE;
        }
        if (this.nodeIdNodeItemMap.has(parentNodeId)) {
            let parent = this.nodeIdNodeItemMap.get(parentNodeId);
            let currentNode = new NodeItem(data);
            if (parent.nodeLevel > this.maxNodeLevel) {
                hilog.error(LOG_CODE, TAG, 'addDragNode: The level of the tree view cannot exceed 50.');
                return false;
            }
            currentNode.nodeLevel = parent.nodeLevel + 1;
            currentNode.parentNodeId = parentNodeId;
            currentNode.currentNodeId = currentNodeId;
            data.parentNodeId = parentNodeId;
            data.currentNodeId = currentNodeId;
            let insertIndex = this.INITIAL_INVALID_VALUE;
            if (parent.children.length) {
                for (let i = 0; i < parent.children.length; i++) {
                    if (parent.children[i].getCurrentNodeId() === insertCurrentNodeId) {
                        insertIndex = i;
                        break;
                    }
                }
                if (isAfter) {
                    currentNode.indexOfParent = insertIndex + 1;
                    this.updateChildIndexOfParent(currentNode.indexOfParent, parent);
                    parent.children.splice(insertIndex + 1, 0, currentNode);
                } else {
                    currentNode.indexOfParent = insertIndex < 0 ? parent.children.length + insertIndex : insertIndex;
                    this.updateChildIndexOfParent(currentNode.indexOfParent, parent);
                    parent.children.splice(insertIndex, 0, currentNode);
                }
            } else {
                currentNode.indexOfParent = parent.children.length;
                parent.children.push(currentNode);
            }
            parent.getChildNodeInfo().isHasChildNode = true;
            parent.getChildNodeInfo().childNum = parent.children.length;
            parent.getChildNodeInfo().allChildNum += 1;
            this.updateParentChildNum(parent, true, 1);
            this.nodeIdNodeItemMap.set(currentNodeId, currentNode);
            this.nodeIdNodeParamMap.set(currentNodeId, data);
            return true;
        } else {
            hilog.error(LOG_CODE, TAG, 'addDragNode: Parent node not found.');
            return false;
        }
    }
}

class ButtonGestureModifier {
    constructor(controller) {
        this.fontSize = 1;
        this.controller = null;
        this.controller = controller;
    }

    applyGesture(event) {
        if (this.fontSize >= ButtonGestureModifier.minFontSize) {
            event.addGesture(new LongPressGestureHandler({
                repeat: false,
                duration: ButtonGestureModifier.longPressTime
            })
                .onAction(() => {
                    if (event) {
                        this.controller?.open();
                    }
                })
                .onActionEnd(() => {
                    this.controller?.close();
                }));
        } else {
            event.clearGestures();
        }
    }
}

ButtonGestureModifier.longPressTime = 500;
ButtonGestureModifier.minFontSize = 1.75;

export class TreeViewInner extends ViewV2 {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
        super(parent, elmtId, extraInfo);
        this.initParam('item', (params && 'item' in params) ? params.item : undefined);
        this.initParam('listNodeDataSource',
            (params && 'listNodeDataSource' in params) ? params.listNodeDataSource : new ListNodeDataSource());
        this.columnWidth = 0;
        this.isFocused = false;
        this.initParam('initialIndex', (params && 'initialIndex' in params) ? params.initialIndex : -1);
        this.index = -1;
        this.lastIndex = -1;
        this.count = 0;
        this.followingSystemFontScale = false;
        this.maxAppFontScale = 1;
        this.treeViewTheme = TreeViewTheme.getInstance();
        this.clickButtonFlag = true;
        this.accessibilityNodeType = AccessibilityNodeType.TEXT;
        this.isAccessibilityEnabled = false;
        this.listTreeViewMenu = 'listTreeViewMenu' in params ? params.listTreeViewMenu : undefined;
        this.initParam('callBackClick', (params && 'callBackClick' in params) ? params.callBackClick : () => {
        });
        this.MAX_CN_LENGTH = 254;
        this.MAX_EN_LENGTH = 255;
        this.INITIAL_INVALID_VALUE = -1;
        this.MAX_TOUCH_DOWN_COUNT = 0;
        this.isMultiPress = false;
        this.touchDownCount = this.INITIAL_INVALID_VALUE;
        this.appEventBus = TreeListenerManagerV2.getInstance().getTreeListener();
        this.itemPadding = {
            left: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_card_margin_start'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
            right: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_card_margin_end'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
            top: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_margin_vertical'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
            bottom: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level0'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
        };
        this.textInputPadding = {
            left: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level0'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
            right: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level0'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
            top: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level0'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
            bottom: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level0'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
        };
        this.inputFontSize = resourceManager.getSystemResourceManager().getNumberByName('ohos_id_text_size_body1');
        this.finalizeConstruction();
    }

    resetStateVarsOnReuse(params) {
        this.resetParam('item', (params && 'item' in params) ? params.item : undefined);
        this.resetParam('listNodeDataSource',
            (params && 'listNodeDataSource' in params) ? params.listNodeDataSource : new ListNodeDataSource());
        this.columnWidth = 0;
        this.isFocused = false;
        this.resetParam('initialIndex', (params && 'initialIndex' in params) ? params.initialIndex : -1);
        this.index = -1;
        this.lastIndex = -1;
        this.count = 0;
        this.followingSystemFontScale = false;
        this.maxAppFontScale = 1;
        this.resetConsumer('treeViewTheme', TreeViewTheme.getInstance());
        this.resetConsumer('clickButtonFlag', true);
        this.resetConsumer('accessibilityNodeType', AccessibilityNodeType.TEXT);
        this.resetConsumer('isAccessibilityEnabled', false);
        this.listTreeViewMenu = 'listTreeViewMenu' in params ? params.listTreeViewMenu : undefined;
        this.resetParam('callBackClick', (params && 'callBackClick' in params) ? params.callBackClick : () => {
        });
    }

    aboutToAppear() {
        this.index = this.initialIndex;
        if (this.item.getNodeItem().imageNode) {
            this.item.imageSource = this.item.getNodeItem().imageNode?.source;
            this.item.symbolSource = this.item.getNodeItem().imageNode?.symbolSource;
        }
        let uiContent = this.getUIContext();
        this.followingSystemFontScale = uiContent.isFollowingSystemFontScale();
        this.maxAppFontScale = uiContent.getMaxFontScale();
    }

    decideFontScale() {
        let uiContent = this.getUIContext();
        let systemFontScale = uiContent.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.followingSystemFontScale) {
            return 1;
        }
        return Math.min(systemFontScale, this.maxAppFontScale, MAX_FONT_SCALE);
    }

    decideSymbolFontScale(isSymbol) {
        if (!isSymbol || !this.followingSystemFontScale) {
            return 1;
        }
        let uiContent = this.getUIContext();
        let systemFontScale = uiContent.getHostContext()?.config?.fontSizeScale ?? 1;
        let symbolFontSizeScale = Math.min(systemFontScale, this.maxAppFontScale, MAX_SYMBOL_FONT_SCALE);
        return Math.max(symbolFontSizeScale, MIN_SYMBOL_FONT_SCALE);
    }

    getInputTextMaxFontSize() {
        let inputTextMaxFontSize = this.decideFontScale() * this.inputFontSize + 'vp';
        return inputTextMaxFontSize;
    }

    getLeftIconColor() {
        if (this.item.getIsModify() || this.item.getIsHighLight()) {
            return {
                'id': -1,
                'type': 10001,
                params: ['sys.color.icon_on_primary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        } else if (this.item.getIsSelected()) {
            return this.treeViewTheme.leftIconActiveColor;
        } else {
            return this.treeViewTheme.leftIconColor;
        }
    }

    getPrimaryTextColor() {
        if (this.item.getIsModify() || this.item.getIsHighLight()) {
            return {
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_primary_contrary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        } else if (this.item.getIsSelected()) {
            return this.treeViewTheme.primaryTitleActiveFontColor;
        } else {
            return this.treeViewTheme.primaryTitleFontColor;
        }
    }

    checkInvalidPattern(title) {
        return new RegExp('/[\\\/:*?"<>|]/').test(title);
    }

    checkIsAllCN(title) {
        return new RegExp('/^[\u4e00-\u9fa5]+$/').test(title);
    }

    getAccessibilityReadText(currentNodeId) {
        let nodeItem = this.listNodeDataSource.nodeIdNodeItemMap.get(currentNodeId);
        if (nodeItem === undefined || currentNodeId === undefined) {
            return '';
        }
        let nodeInfo = this.listNodeDataSource.getNodeInfoByNodeItem(nodeItem);
        let primaryTitle = nodeInfo?.getNodeInfoData()?.primaryTitle === undefined
            ? '' : nodeInfo?.getNodeInfoData()?.primaryTitle;
        let secondaryTitle = nodeInfo?.getNodeInfoData()?.secondaryTitle === undefined
            ? '' : nodeInfo?.getNodeInfoData()?.secondaryTitle;
        let primaryTitleText = this.listNodeDataSource.getAccessibleTitleText(primaryTitle);
        let secondaryTitleText = this.listNodeDataSource.getAccessibleTitleText(secondaryTitle);
        let title = `${primaryTitleText}, ${secondaryTitleText}`;
        let parentId = this.listNodeDataSource.findParentNodeId(currentNodeId);
        let parentNode = [];
        let insertRootNodePosition = 0;
        let childrenInfo = this.listNodeDataSource.getClickNodeChildrenInfo(parentId);
        let childrenItemId = childrenInfo.map(item => item.itemId);
        let insertNodePosition = childrenItemId.indexOf(currentNodeId) + 1;
        let accessibleTitle = this.listNodeDataSource.getAccessibleTitle(currentNodeId);
        if (accessibleTitle === undefined) {
            return ' ';
        }
        if (this.accessibilityNodeType === AccessibilityNodeType.PLACE) {
            if (this.listNodeDataSource.findParentNodeId(currentNodeId) === -1) {
                for (let i = 0; i < this.listNodeDataSource.listNode.length; i++) {
                    if (this.listNodeDataSource.listNode[i].getNodeParentNodeId() === -1) {
                        parentNode.push(this.listNodeDataSource.listNode[i].getNodeCurrentNodeId());
                    }
                }
                insertRootNodePosition = parentNode.indexOf(currentNodeId) + 1;
                return this.listNodeDataSource.getStringByName('treeview_accessibility_place_node_parent',
                    insertRootNodePosition);
            } else {
                return this.listNodeDataSource.getStringByName('treeview_accessibility_place_node_child',
                    accessibleTitle, insertNodePosition);
            }
        } else if (this.accessibilityNodeType === AccessibilityNodeType.LIFT) {
            return title;
        } else {
            return title;
        }
    }

    getAccessibilityDescription() {
        if (this.accessibilityNodeType === AccessibilityNodeType.TEXT) {
            return this.listNodeDataSource.getStringByName('treeview_accessibility_node_desc');
        } else {
            return ' ';
        }
    }

    getAccessibilityReadButtonText(isFolded) {
        if (this.clickButtonFlag === false) {
            return this.item.getNodeItem().imageCollapse?.collapseSource === ARROW_RIGHT
                ? this.listNodeDataSource.getStringByName('treeview_accessibility_folded_node')
                : this.listNodeDataSource.getStringByName('treeview_accessibility_expanded_node');
        } else {
            return isFolded
                ? this.listNodeDataSource.getStringByName('treeview_accessibility_expand_node')
                : this.listNodeDataSource.getStringByName('treeview_accessibility_fold_node');
        }
    }

    getAccessibilityReadButtonDescription() {
        if (this.clickButtonFlag === false) {
            return ' ';
        } else {
            return this.listNodeDataSource.getStringByName('treeview_accessibility_implement_node');
        }
    }

    onTouchNode(event) {
        this.count++;
        if (this.count > 1) {
            this.count--;
            return;
        }
        this.index = this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId());
        this.listNodeDataSource.setClickIndex(this.index);
        let currentId = this.item.getNodeCurrentNodeId();
        if (event.type === TouchType.Down) {
            this.item.setNodeColor(this.treeViewTheme.itemPressedBgColor);
        } else if (event.type === TouchType.Up) {
            if (!(typeof this.treeViewTheme.itemSelectedBgColor === 'string')) {
                this.item.setNodeColor(COLOR_SELECT);
            } else {
                this.item.setNodeColor(this.treeViewTheme.itemSelectedBgColor);
            }
            if (this.item.getNodeItem().imageNode !== null) {
                this.item.getNodeItem().imageNode?.setImageSource(InteractionStatus.SELECTED);
                this.listNodeDataSource.setImageSource(this.index, InteractionStatus.SELECTED);
                this.item.imageSource = this.item.getNodeItem().imageNode?.source;
                this.item.symbolSource = this.item.getNodeItem().imageNode?.symbolSource;
            }
            this.item.getNodeItem().mainTitleNode?.setMainTitleSelected(true);
            let callParam = { currentNodeId: currentId };
            this.appEventBus.emitNodeClick(callParam);
            this.listNodeDataSource.sendAccessibility(this.item.getIsSelected()
                ? this.listNodeDataSource.getStringByName('treeview_accessibility_select_node',
                    `${this.getAccessibilityReadText(this.item.getNodeCurrentNodeId())}`) : '');
        }
        if (this.listNodeDataSource.getLastIndex() !== -1 && this.index !== this.listNodeDataSource.getLastIndex()) {
            this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false,
                this.listNodeDataSource.getLastIndex());
            this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(),
                MenuOperation.COMMIT_NODE);
        }
        this.lastIndex = this.index;
        this.count--;
    }

    onClickNode() {
        this.count++;
        if (this.count > 1) {
            this.count--;
            return;
        }
        this.index = this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId());
        this.listNodeDataSource.setClickIndex(this.index);
        let currentId = this.item.getNodeCurrentNodeId();
        if (!(typeof this.treeViewTheme.itemSelectedBgColor === 'string')) {
            this.item.setNodeColor(COLOR_SELECT);
        } else {
            this.item.setNodeColor(this.treeViewTheme.itemSelectedBgColor);
        }
        if (this.item.getNodeItem().imageNode !== null) {
            this.item.getNodeItem().imageNode?.setImageSource(InteractionStatus.SELECTED);
            this.listNodeDataSource.setImageSource(this.index, InteractionStatus.SELECTED);
            this.item.imageSource = this.item.getNodeItem().imageNode?.source;
            this.item.symbolSource = this.item.getNodeItem().imageNode?.symbolSource;
        }
        this.item.getNodeItem().mainTitleNode?.setMainTitleSelected(true);
        let callParam = { currentNodeId: currentId };
        this.appEventBus.emitNodeClick(callParam);
        this.listNodeDataSource.sendAccessibility(this.item.getIsSelected()
            ? this.listNodeDataSource.getStringByName('treeview_accessibility_select_node',
                `${this.getAccessibilityReadText(this.item.getNodeCurrentNodeId())}`) : '');
        if (this.listNodeDataSource.getLastIndex() !== -1 && this.index !== this.listNodeDataSource.getLastIndex()) {
            this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false,
                this.listNodeDataSource.getLastIndex());
            this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(),
                MenuOperation.COMMIT_NODE);
        }
        this.lastIndex = this.index;
        this.count--;
    }

    accessibilityRefocus() {
        this.clickButtonFlag = false;
        let eventInfo = ({
            type: 'requestFocusForAccessibility',
            bundleName: getContext()?.abilityInfo?.bundleName,
            triggerAction: 'common',
            customId: `treeView_button${this.item.getNodeCurrentNodeId()}`
        });
        accessibility.sendAccessibilityEvent(eventInfo).then(() => {
            setTimeout(() => {
                this.clickButtonFlag = true;
            }, ENTER_EXIT_DURATION);
        });
    }

    popupForShowTitle(text, backgroundColor, fontColor, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.backgroundColor(backgroundColor);
            Row.border({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_elements_margin_horizontal_l'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                }
            });
            Row.padding({
                left: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_elements_margin_horizontal_l'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                right: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_elements_margin_horizontal_l'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                top: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_card_margin_middle'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                bottom: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_card_margin_middle'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(text);
            Text.fontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_body2'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Text.fontWeight('regular');
            Text.fontColor(fontColor);
            Text.minFontScale(MIN_FONT_SCALE);
            Text.maxFontScale(this.decideFontScale());
        }, Text);
        Text.pop();
        Row.pop();
    }

    builder(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.listTreeViewMenu) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.listTreeViewMenu.bind(this)();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }

    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.item.getNodeIsShow()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Stack.create();
                        ViewStackProcessor.visualState('normal');
                        Stack.border({
                            radius: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.ohos_id_corner_radius_clicked'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                            width: 0,
                        });
                        ViewStackProcessor.visualState('focused');
                        Stack.border({
                            radius: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.ohos_id_corner_radius_clicked'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                            width: FLAG_NUMBER,
                            color: this.treeViewTheme.borderFocusedColor,
                            style: BorderStyle.Solid,
                        });
                        ViewStackProcessor.visualState();
                    }, Stack);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                        Column.opacity(this.listNodeDataSource.getListItemOpacity(this.item));
                        Column.onHover((isHover) => {
                            if (isHover) {
                                this.item.setNodeColor(this.treeViewTheme.itemHoverBgColor);
                            } else {
                                this.item.setNodeColor({
                                    'id': -1,
                                    'type': 10001,
                                    params: ['sys.color.ohos_id_color_background_transparent'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                });
                            }
                        });
                        Column.onTouch(this.isAccessibilityEnabled ? undefined : (event) => {
                            this.onTouchNode(event);
                        });
                        Column.backgroundColor((this.item.getNodeItem().mainTitleNode &&
                            this.item.getNodeItem().inputText &&
                            this.item.getIsShowInputText()) ? this.item.getNodeItem().inputText?.editColor :
                            this.item.getNodeColor());
                        Column.border({
                            width: this.item.getNodeBorder().borderWidth,
                            color: this.item.getNodeBorder().borderColor,
                            radius: this.item.getNodeBorder().borderRadius,
                        });
                        Column.height(LIST_ITEM_HEIGHT);
                        Column.focusable(true);
                        Column.onMouse((event) => {
                            let thisIndex = this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId());
                            if (event.button === MouseButton.Right) {
                                this.listNodeDataSource.handleEvent(Event.MOUSE_BUTTON_RIGHT,
                                    this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId()));
                                this.listTreeViewMenu = this.item.getMenu();
                                this.listNodeDataSource.setClickIndex(thisIndex);
                                clearTimeout(this.item.getNodeItem().mainTitleNode?.popUpTimeout);
                            }
                            event.stopPropagation();
                        });
                        Column.padding({ top: 0, bottom: 0 });
                        Column.bindPopup(this.item.getPopUpInfo().popUpIsShow, {
                            builder: {
                                builder: () => {
                                    this.popupForShowTitle.call(this, this.item.getPopUpInfo().popUpText,
                                        this.item.getPopUpInfo().popUpColor, this.item.getPopUpInfo().popUpTextColor);
                                }
                            },
                            placement: Placement.BottomLeft,
                            placementOnTop: false,
                            popupColor: this.item.getPopUpInfo().popUpColor,
                            autoCancel: true,
                            enableArrow: this.item.getPopUpInfo().popUpEnableArrow
                        });
                        Column.onAreaChange((oldValue, newValue) => {
                            let columnWidthNum = Number.parseInt(newValue.width.toString());
                            this.columnWidth = columnWidthNum;
                        });
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Stack.create({ alignContent: Alignment.Bottom });
                        Stack.focusable(true);
                    }, Stack);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Divider.create();
                        Divider.height(this.listNodeDataSource.getFlagLine().flagLineHeight);
                        Divider.color(this.listNodeDataSource.getFlagLine().flagLineColor);
                        Divider.visibility(this.listNodeDataSource.getVisibility(this.item));
                        Divider.lineCap(LineCapStyle.Round);
                        Divider.margin({ start: LengthMetrics.vp(this.item.getFlagLineLeftMargin()) });
                        Divider.focusable(true);
                    }, Divider);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create({});
                        Row.focusable(true);
                        Row.width('100%');
                        Row.height(this.item.getNodeHeight());
                        Row.padding({ start: LengthMetrics.vp(this.item.getNodeLeftPadding()) });
                        Row.bindContextMenu({ builder: this.builder.bind(this) }, ResponseType.RightClick);
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.height(LIST_ITEM_HEIGHT);
                        Row.layoutWeight(1);
                        Row.focusable(true);
                        Row.accessibilityGroup(true);
                        Row.id(`treeView_node${this.item.getNodeCurrentNodeId()}`);
                        Row.accessibilityText(this.getAccessibilityReadText(this.item.getNodeCurrentNodeId()));
                        Row.accessibilityDescription(this.getAccessibilityDescription());
                        Row.onClick(this.isAccessibilityEnabled ? () => {
                            this.onClickNode();
                            this.callBackClick();
                        } : undefined);
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.item.getNodeItem().imageNode) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Row.create();
                                    Row.focusable(true);
                                    Row.backgroundColor(COLOR_IMAGE_ROW);
                                    Row.margin({
                                        end: getLengthMetricsByResourceOrNumber(this.item.getNodeItem()
                                            .imageNode?.itemRightMargin)
                                    });
                                    Row.height(this.item.getNodeItem().imageNode?.itemHeight *
                                        this.decideSymbolFontScale(this.item.symbolSource !== undefined ||
                                            Util.isSymbolResource(this.item.imageSource)));
                                    Row.width(this.item.getNodeItem().imageNode?.itemWidth *
                                        this.decideSymbolFontScale(this.item.symbolSource !== undefined ||
                                            Util.isSymbolResource(this.item.imageSource)));
                                }, Row);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    If.create();
                                    if (this.item.symbolSource) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                SymbolGlyph.create();
                                                SymbolGlyph.fontColor([this.getLeftIconColor()]);
                                                SymbolGlyph.attributeModifier.bind(this)(this.item.symbolSource);
                                                SymbolGlyph.fontSize(`${this.item.getNodeItem().imageNode?.itemHeight *
                                                    this.decideSymbolFontScale(true)}vp`);
                                                SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                                SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                                SymbolGlyph.opacity(!this.item.getIsSelected() &&
                                                    !this.item.getIsHighLight() ?
                                                    this.item.getNodeItem().imageNode?.opacity :
                                                    this.item.getNodeItem().imageNode?.noOpacity);
                                                SymbolGlyph.focusable(this.item.getNodeItem().mainTitleNode !== null ?
                                                    false : true);
                                            }, SymbolGlyph);
                                        });
                                    } else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                If.create();
                                                if (Util.isSymbolResource(this.item.imageSource)) {
                                                    this.ifElseBranchUpdateFunction(0, () => {
                                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                            SymbolGlyph.create(this.item.imageSource);
                                                            SymbolGlyph.fontSize(`${this.item.getNodeItem()
                                                                .imageNode?.itemHeight *
                                                                this.decideSymbolFontScale(true)}vp`);
                                                            SymbolGlyph.fontColor([this.getLeftIconColor()]);
                                                            SymbolGlyph.opacity(!this.item.getIsSelected() &&
                                                                !this.item.getIsHighLight() ?
                                                                this.item.getNodeItem().imageNode?.opacity :
                                                                this.item.getNodeItem().imageNode?.noOpacity);
                                                            SymbolGlyph.focusable(this.item.getNodeItem()
                                                                .mainTitleNode !== null ? false : true);
                                                        }, SymbolGlyph);
                                                    });
                                                } else {
                                                    this.ifElseBranchUpdateFunction(1, () => {
                                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                            Image.create(this.item.imageSource);
                                                            Image.objectFit(ImageFit.Contain);
                                                            Image.height(this.item.getNodeItem().imageNode?.itemHeight);
                                                            Image.width(this.item.getNodeItem().imageNode?.itemWidth);
                                                            Image.opacity(!this.item.getIsSelected() &&
                                                                !this.item.getIsHighLight() ?
                                                                this.item.getNodeItem().imageNode?.opacity :
                                                                this.item.getNodeItem().imageNode?.noOpacity);
                                                            Image.focusable(this.item.getNodeItem().mainTitleNode !==
                                                                null ? false : true);
                                                            Image.fillColor(this.getLeftIconColor());
                                                            Image.matchTextDirection((this.item.getNodeItem()
                                                                .imageCollapse?.collapseSource === ARROW_RIGHT ||
                                                                this.item.getNodeItem()
                                                                    .imageCollapse?.collapseSource ===
                                                                    ARROW_RIGHT_WITHE) ? true : false);
                                                        }, Image);
                                                    });
                                                }
                                            }, If);
                                            If.pop();
                                        });
                                    }
                                }, If);
                                If.pop();
                                Row.pop();
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.layoutWeight(1);
                        Row.focusable(true);
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.item.getNodeItem().mainTitleNode && this.item.getIsShowTitle()) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Text.create(this.item.getNodeItem().mainTitleNode?.title);
                                    Text.minFontScale(MIN_FONT_SCALE);
                                    Text.maxFontScale(this.decideFontScale());
                                    Text.maxLines(1);
                                    Text.fontSize(this.item.getNodeItem().mainTitleNode?.size);
                                    Text.fontColor(this.getPrimaryTextColor());
                                    Text.margin({
                                        end: getLengthMetricsByResourceOrNumber(this.item.getNodeItem()
                                            .mainTitleNode?.itemRightMargin)
                                    });
                                    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                                    Text.fontWeight(this.item.getNodeItem().mainTitleNode?.weight);
                                    Text.focusable(true);
                                }, Text);
                                Text.pop();
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.item.getNodeItem().mainTitleNode && this.item.getNodeItem().inputText &&
                            this.item.getIsShowInputText()) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Row.create();
                                    Row.backgroundColor(this.item.getNodeItem().inputText?.backgroundColor);
                                    Row.borderRadius(this.item.getNodeItem().inputText?.borderRadius);
                                    Row.margin({
                                        end: getLengthMetricsByResourceOrNumber(this.item.getNodeItem()
                                            .inputText?.itemRightMargin)
                                    });
                                }, Row);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    TextInput.create({ text: this.item.getNodeItem().mainTitleNode?.title });
                                    TextInput.height(this.item.getNodeItem().inputText?.itemHeight);
                                    TextInput.fontSize(this.getInputTextMaxFontSize());
                                    TextInput.fontColor(this.item.getNodeItem().inputText?.color);
                                    TextInput.borderRadius(this.item.getNodeItem().inputText?.borderRadius);
                                    TextInput.backgroundColor(this.item.getNodeItem().inputText?.backgroundColor);
                                    TextInput.enterKeyType(EnterKeyType.Done);
                                    TextInput.focusable(true);
                                    TextInput.padding({
                                        start: LengthMetrics.resource(this.textInputPadding.left),
                                        end: LengthMetrics.resource(this.textInputPadding.right),
                                        top: LengthMetrics.resource(this.textInputPadding.top),
                                        bottom: LengthMetrics.resource(this.textInputPadding.bottom),
                                    });
                                    TextInput.onChange((value) => {
                                        let thisIndex =
                                            this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId());
                                        let res = '';
                                        let isInvalidError = false;
                                        let isLengthError = false;
                                        if (this.checkInvalidPattern(value)) {
                                            for (let i = 0; i < value.length; i++) {
                                                if (!this.checkInvalidPattern(value[i])) {
                                                    res += value[i];
                                                }
                                            }
                                            isInvalidError = true;
                                            this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS,
                                                InputError.INVALID_ERROR, true, thisIndex);
                                        } else {
                                            res = value;
                                            isInvalidError = false;
                                        }
                                        if ((this.checkIsAllCN(res) && res.length > this.MAX_CN_LENGTH) ||
                                            (!this.checkIsAllCN(res) && res.length > this.MAX_EN_LENGTH)) {
                                            res = this.checkIsAllCN(res) ?
                                                res.substr(0, this.MAX_CN_LENGTH) : res.substr(0, this.MAX_EN_LENGTH);
                                            isLengthError = true;
                                            this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS,
                                                InputError.LENGTH_ERROR, true, thisIndex);
                                        } else {
                                            isLengthError = false;
                                        }
                                        if (!isLengthError && !isInvalidError) {
                                            this.listNodeDataSource.setMainTitleNameOnEdit(thisIndex, res);
                                        }
                                    });
                                    TextInput.onSubmit((enterKey) => {
                                        let thisIndex =
                                            this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId());
                                        this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false,
                                            thisIndex);
                                        this.listNodeDataSource.setItemVisibilityOnEdit(thisIndex,
                                            MenuOperation.COMMIT_NODE);
                                    });
                                }, TextInput);
                                Row.pop();
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Blank.create();
                    }, Blank);
                    Blank.pop();
                    Row.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.listNodeDataSource.hasSubtitle(this.item.getNodeCurrentNodeId())) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Row.create();
                                    Row.focusable(true);
                                    Row.margin({
                                        start: LengthMetrics.resource(this.listNodeDataSource.getSubTitlePara().margin
                                            .left),
                                        end: this.item.getNodeItem().imageCollapse ?
                                            LengthMetrics.resource({
                                                'id': -1,
                                                'type': 10002,
                                                params: ['sys.float.padding_level0'],
                                                'bundleName': '__harDefaultBundleName__',
                                                'moduleName': '__harDefaultModuleName__'
                                            }) :
                                            LengthMetrics.resource(this.listNodeDataSource.getSubTitlePara().margin
                                                .right)
                                    });
                                }, Row);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Text.create(this.listNodeDataSource.getSubtitle(this.item.getNodeCurrentNodeId()));
                                    Text.minFontScale(MIN_FONT_SCALE);
                                    Text.maxFontScale(this.decideFontScale());
                                    Text.fontSize(this.listNodeDataSource.getSubTitlePara().fontSize);
                                    Text.fontColor(this.item.getIsHighLight() || this.item.getIsModify() ? {
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_primary_contrary'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    } : this.treeViewTheme.secondaryTitleFontColor);
                                    Text.fontWeight(this.listNodeDataSource.getSubTitlePara().fontWeight);
                                }, Text);
                                Text.pop();
                                Row.pop();
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    Row.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.item.getNodeItem().imageCollapse) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                if (!If.canRetake(`treeView_button${this.item.getNodeCurrentNodeId()}`)) {
                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                        Row.create();
                                        Row.focusable(true);
                                        Row.justifyContent(FlexAlign.Center);
                                        Row.height(this.item.getNodeItem().imageCollapse?.itemHeight *
                                            this.decideSymbolFontScale(true));
                                        Row.width(this.item.getNodeItem().imageCollapse?.itemWidth *
                                            this.decideSymbolFontScale(true));
                                        Row.onClick(() => {
                                            this.listNodeDataSource.expandAndCollapseNode(this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId()));
                                            this.listNodeDataSource.setCurrentFocusNodeId(this.item.getNodeCurrentNodeId());
                                            setTimeout(() => {
                                                this.accessibilityRefocus();
                                            }, ACCESSIBILITY_REFOCUS_DELAY_TIME);
                                        });
                                        Row.id(`treeView_button${this.item.getNodeCurrentNodeId()}`);
                                        Row.accessibilityText(this.getAccessibilityReadButtonText(this.item.getNodeItem()
                                            .imageCollapse?.collapseSource === ARROW_RIGHT));
                                        Row.accessibilityDescription(this.getAccessibilityReadButtonDescription());
                                    }, Row);
                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                        SymbolGlyph.create(this.item.getNodeItem().imageCollapse?.collapseSource);
                                        SymbolGlyph.fontSize(`${this.item.getNodeItem().imageCollapse?.itemHeight *
                                            this.decideSymbolFontScale(true)}vp`);
                                        SymbolGlyph.fontColor([this.item.getNodeItem().imageCollapse?.isCollapse ?
                                            this.treeViewTheme.arrowIconColor : COLOR_IMAGE_EDIT]);
                                        SymbolGlyph.opacity(!this.item.getIsHighLight() ?
                                            this.item.getNodeItem().imageCollapse?.opacity :
                                            this.item.getNodeItem().imageCollapse?.noOpacity);
                                        SymbolGlyph.focusable(true);
                                    }, SymbolGlyph);
                                    Row.pop();
                                }
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    Row.pop();
                    Stack.pop();
                    Column.pop();
                    Stack.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }

    updateStateVars(params) {
        if (params === undefined) {
            return;
        }
        if ('item' in params) {
            this.updateParam('item', params.item);
        }
        if ('listNodeDataSource' in params) {
            this.updateParam('listNodeDataSource', params.listNodeDataSource);
        }
        if ('initialIndex' in params) {
            this.updateParam('initialIndex', params.initialIndex);
        }
        if ('callBackClick' in params) {
            this.updateParam('callBackClick', params.callBackClick);
        }
    }

    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
], TreeViewInner.prototype, 'item', void 0);
__decorate([
    Param
], TreeViewInner.prototype, 'listNodeDataSource', void 0);
__decorate([
    Local
], TreeViewInner.prototype, 'columnWidth', void 0);
__decorate([
    Local
], TreeViewInner.prototype, 'isFocused', void 0);
__decorate([
    Param
], TreeViewInner.prototype, 'initialIndex', void 0);
__decorate([
    Local
], TreeViewInner.prototype, 'index', void 0);
__decorate([
    Local
], TreeViewInner.prototype, 'lastIndex', void 0);
__decorate([
    Local
], TreeViewInner.prototype, 'count', void 0);
__decorate([
    Local
], TreeViewInner.prototype, 'followingSystemFontScale', void 0);
__decorate([
    Local
], TreeViewInner.prototype, 'maxAppFontScale', void 0);
__decorate([
    Consumer('treeViewThemeV2')
], TreeViewInner.prototype, 'treeViewTheme', void 0);
__decorate([
    Consumer('clickButtonFlagV2')
], TreeViewInner.prototype, 'clickButtonFlag', void 0);
__decorate([
    Consumer('accessibilityNodeTypeV2')
], TreeViewInner.prototype, 'accessibilityNodeType', void 0);
__decorate([
    Consumer('isAccessibilityEnabledV2')
], TreeViewInner.prototype, 'isAccessibilityEnabled', void 0);
__decorate([
    Param
], TreeViewInner.prototype, 'callBackClick', void 0);

export class NodeItem {
    constructor(nodeParam) {
        this.currentNodeId = nodeParam.currentNodeId ?? -1;
        this.parentNodeId = nodeParam.parentNodeId ?? -1;
        this.isFolder = nodeParam.isFolder;
        this.nodeLevel = -1;
        this.indexOfParent = -1;
        this.childNodeInfo = { isHasChildNode: false, childNum: 0, allChildNum: 0 };
        this.children = [];
    }

    getChildNodeInfo() {
        return this.childNodeInfo;
    }

    getCurrentNodeId() {
        return this.currentNodeId;
    }

    getIsFolder() {
        return this.isFolder;
    }
}

class NodeBaseInfo {
    constructor() {
        this.rightMargin = -1;
        this.width = -1;
        this.height = -1;
    }

    set itemWidth(width) {
        this.width = width;
    }

    get itemWidth() {
        return this.width;
    }

    set itemHeight(height) {
        this.height = height;
    }

    get itemHeight() {
        return this.height;
    }

    set itemRightMargin(rightMargin) {
        this.rightMargin = rightMargin;
    }

    get itemRightMargin() {
        return this.rightMargin;
    }
}

export class CollapseImageNode extends NodeBaseInfo {
    constructor(imageSource, symbolSource, imageOpacity, itemWidth, itemHeight, itemRightMargin, isImageCollapse,
        collapseImageType) {
        super();
        this.rightMargin = {
            'id': -1,
            'type': 10002,
            params: ['sys.float.ohos_id_elements_margin_horizontal_m'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.imageSource = imageSource;
        this.symbolIconSource = symbolSource;
        this.rightMargin = itemRightMargin;
        this.imageOpacity = imageOpacity;
        this.itemWidth = itemWidth;
        this.itemHeight = itemHeight;
        this.imageCollapseSource = imageSource;
        this.symbolIconCollapseSource = symbolSource;
        this.isImageCollapse = isImageCollapse;
        this.collapseImageType = collapseImageType;
    }

    get source() {
        return this.imageSource;
    }

    get symbolSource() {
        return this.symbolIconSource;
    }

    get opacity() {
        return this.imageOpacity;
    }

    get noOpacity() {
        return 1;
    }

    get collapseSource() {
        return this.imageCollapseSource;
    }

    get symbolCollapseSource() {
        return this.symbolIconCollapseSource;
    }

    get isCollapse() {
        return this.isImageCollapse;
    }

    get type() {
        return this.collapseImageType;
    }
}

class CollapseImageNodeFactory {
    constructor() {
    }

    /**
     * CollapseImageNodeFactory singleton function
     *
     * @returns CollapseImageNodeFactory
     */
    static getInstance() {
        if (!CollapseImageNodeFactory.instance) {
            CollapseImageNodeFactory.instance = new CollapseImageNodeFactory();
        }
        return CollapseImageNodeFactory.instance;
    }

    /**
     * create collapse image node by type
     *
     * @param type collapse image type
     * @returns collapse image node
     */
    createCollapseImageNodeByType(type) {
        let imageSource;
        switch (type) {
            case CollapseImageType.ARROW_RIGHT_WHITE:
                imageSource = ARROW_RIGHT_WITHE;
                break;
            case CollapseImageType.ARROW_RIGHT:
                imageSource = ARROW_RIGHT;
                break;
            case CollapseImageType.ARROW_DOWN_WHITE:
                imageSource = ARROW_DOWN_WITHE;
                break;
            default:
                imageSource = ARROW_DOWN;
        }
        return new CollapseImageNode(imageSource, undefined, {
            'id': -1,
            'type': 10002,
            params: ['sys.float.ohos_id_alpha_content_tertiary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, IMAGE_NODE_HEIGHT, IMAGE_NODE_WIDTH, {
            'id': -1,
            'type': 10002,
            params: ['sys.float.ohos_id_text_paragraph_margin_xs'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, (type === CollapseImageType.ARROW_RIGHT_WHITE || type === CollapseImageType.ARROW_DOWN_WHITE) ? false : true,
            type);
    }
}

class CollapseImageNodeFlyweightFactory {
    /**
     * get collapse image node by type
     *
     * @param type collapse image node type
     * @returns collapse image node
     */
    static getCollapseImageNodeByType(type) {
        let node = CollapseImageNodeFlyweightFactory.nodeMap.get(type);
        if (node === undefined) {
            node = CollapseImageNodeFactory.getInstance().createCollapseImageNodeByType(type);
            CollapseImageNodeFlyweightFactory.nodeMap.set(type, node);
        }
        return node;
    }

    /**
     * get collapse image node by interactionStatus and nodeStatus
     *
     * @param interactionStatus interaction status
     * @param nodeStatus node status
     * @param defaultType default collapse image type
     * @returns collapse image node
     */
    static getCollapseImageNode(interactionStatus, nodeStatus, defaultType) {
        if (defaultType === undefined) {
            return undefined;
        }
        let type = defaultType;
        if (interactionStatus == InteractionStatus.EDIT ||
            interactionStatus === InteractionStatus.DRAG_INSERT) {
            if (nodeStatus === NodeStatus.COLLAPSE) {
                type = CollapseImageType.ARROW_RIGHT_WHITE;
            } else {
                type = CollapseImageType.ARROW_DOWN_WHITE;
            }
        } else if (interactionStatus === InteractionStatus.FINISH_EDIT ||
            interactionStatus === InteractionStatus.FINISH_DRAG_INSERT) {
            if (nodeStatus === NodeStatus.COLLAPSE) {
                type = CollapseImageType.ARROW_RIGHT;
            } else {
                type = CollapseImageType.ARROW_DOWN;
            }
        }
        return CollapseImageNodeFlyweightFactory.getCollapseImageNodeByType(type);
    }

    /**
     * change collapse image node source
     *
     * @param nodeStatus node status
     * @param isImageCollapse whether collapse image or white collapse image
     * @returns collapse image node
     */
    static changeImageCollapseSource(nodeStatus, isImageCollapse) {
        if (isImageCollapse === undefined) {
            return undefined;
        }
        let type;
        if (!isImageCollapse) {
            if (nodeStatus === NodeStatus.COLLAPSE) {
                type = CollapseImageType.ARROW_RIGHT_WHITE;
            } else {
                type = CollapseImageType.ARROW_DOWN_WHITE;
            }
        } else {
            if (nodeStatus === NodeStatus.COLLAPSE) {
                type = CollapseImageType.ARROW_RIGHT;
            } else {
                type = CollapseImageType.ARROW_DOWN;
            }
        }
        return CollapseImageNodeFlyweightFactory.getCollapseImageNodeByType(type);
    }
}

CollapseImageNodeFlyweightFactory.nodeMap = new Map();

export class ImageNode extends NodeBaseInfo {
    constructor(imageSource, symbolSource, imageOpacity, itemWidth, itemHeight, itemSelectedIcon, symbolSelectedIcon,
        itemEditIcon, symbolEditIcon) {
        super();
        this.rightMargin = {
            'id': -1,
            'type': 10002,
            params: ['sys.float.ohos_id_elements_margin_horizontal_m'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.imageSource = imageSource;
        this.symbolIconSource = symbolSource;
        this.imageNormalSource = imageSource;
        this.symbolIconNormalSource = symbolSource;
        if (itemSelectedIcon !== undefined) {
            this.imageSelectedSource = itemSelectedIcon;
        } else {
            this.imageSelectedSource = this.imageNormalSource;
        }
        this.symbolIconSelectedSource = symbolSelectedIcon;
        if (itemEditIcon !== undefined) {
            this.imageEditSource = itemEditIcon;
        } else {
            this.imageEditSource = this.imageNormalSource;
        }
        this.symbolIconEditSource = symbolEditIcon;
        this.imageOpacity = imageOpacity;
        this.itemWidth = itemWidth;
        this.itemHeight = itemHeight;
        this.imageCollapseSource = imageSource;
        this.imageCollapseDownSource = ARROW_DOWN;
        this.imageCollapseRightSource = ARROW_RIGHT;
        this.isImageCollapse = true;
        this.currentInteractionStatus = InteractionStatus.NORMAL;
    }

    get source() {
        return this.imageSource;
    }

    get symbolSource() {
        return this.symbolIconSource;
    }

    get normalSource() {
        return this.imageNormalSource;
    }

    get symbolNormalSource() {
        return this.symbolIconNormalSource;
    }

    get selectedSource() {
        return this.imageSelectedSource;
    }

    get symbolSelectedSource() {
        return this.symbolIconSelectedSource;
    }

    get editSource() {
        return this.imageEditSource;
    }

    get symbolEditSource() {
        return this.symbolIconEditSource;
    }

    get opacity() {
        return this.imageOpacity;
    }

    get noOpacity() {
        return 1;
    }

    get collapseSource() {
        return this.imageCollapseSource;
    }

    get isCollapse() {
        return this.isImageCollapse;
    }

    changeImageCollapseSource(nodeStatus) {
        if (nodeStatus === NodeStatus.EXPAND) {
            this.imageCollapseSource = this.imageCollapseDownSource;
        } else if (nodeStatus === NodeStatus.COLLAPSE) {
            this.imageCollapseSource = this.imageCollapseRightSource;
        }
    }

    setImageCollapseSource(interactionStatus, nodeStatus) {
        if (interactionStatus === InteractionStatus.EDIT || interactionStatus === InteractionStatus.DRAG_INSERT) {
            this.imageCollapseDownSource = ARROW_DOWN_WITHE;
            this.imageCollapseRightSource = ARROW_RIGHT_WITHE;
            this.isImageCollapse = false;
        } else if (interactionStatus === InteractionStatus.FINISH_EDIT ||
            interactionStatus === InteractionStatus.FINISH_DRAG_INSERT) {
            this.imageCollapseDownSource = ARROW_DOWN;
            this.imageCollapseRightSource = ARROW_RIGHT;
            this.isImageCollapse = true;
        }
        this.imageCollapseSource = (nodeStatus === NodeStatus.COLLAPSE) ?
            this.imageCollapseRightSource : this.imageCollapseDownSource;
    }

    setImageSource(interactionStatus) {
        switch (interactionStatus) {
            case InteractionStatus.NORMAL:
                this.imageSource = this.imageNormalSource;
                this.symbolIconSource = this.symbolIconNormalSource;
                this.currentInteractionStatus = interactionStatus;
                break;
            case InteractionStatus.SELECTED:
                if (this.currentInteractionStatus !== InteractionStatus.EDIT) {
                    this.imageSource = this.imageSelectedSource;
                    this.symbolIconSource = this.symbolIconSelectedSource;
                    this.currentInteractionStatus = interactionStatus;
                }
                break;
            case InteractionStatus.EDIT:
                this.imageSource = this.imageEditSource;
                this.symbolIconSource = this.symbolIconEditSource;
                this.currentInteractionStatus = interactionStatus;
                break;
            case InteractionStatus.FINISH_EDIT:
                this.imageSource = this.imageSelectedSource;
                this.symbolIconSource = this.symbolIconSelectedSource;
                this.currentInteractionStatus = interactionStatus;
                break;
            case InteractionStatus.DRAG_INSERT:
                this.imageSource = this.imageEditSource;
                this.symbolIconSource = this.symbolIconEditSource;
                this.currentInteractionStatus = interactionStatus;
                break;
            case InteractionStatus.FINISH_DRAG_INSERT:
                this.imageSource = this.imageNormalSource;
                this.symbolIconSource = this.symbolIconNormalSource;
                this.currentInteractionStatus = interactionStatus;
                break;
            default:
                break;
        }
    }
}

class MainTitleNode extends NodeBaseInfo {
    constructor(mainTitleName) {
        super();
        this.treeViewTheme = TreeViewTheme.getInstance();
        this.mainTitleName = mainTitleName;
        this.itemWidth = ITEM_WIDTH;
        this.itemHeight = ITEM_HEIGHT;
        this.rightMargin = {
            'id': -1,
            'type': 10002,
            params: ['sys.float.ohos_id_text_paragraph_margin_xs'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.mainTitleSetting = {
            fontColor: this.treeViewTheme.primaryTitleFontColor,
            fontSize: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_body1'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
            fontWeight: FontWeight.Normal,
        };
        this.showPopUpTimeout = 0;
    }

    setMainTitleSelected(isSelected) {
        if (isSelected) {
            this.mainTitleSetting = {
                fontColor: this.treeViewTheme.primaryTitleActiveFontColor,
                fontSize: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_text_size_body1'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                fontWeight: FontWeight.Regular,
            };
        } else {
            this.mainTitleSetting = {
                fontColor: this.treeViewTheme.primaryTitleFontColor,
                fontSize: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_text_size_body1'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                fontWeight: FontWeight.Normal,
            };
        }
    }

    set title(text) {
        this.mainTitleName = text;
    }

    get title() {
        return this.mainTitleName;
    }

    set popUpTimeout(showPopUpTimeout) {
        this.showPopUpTimeout = showPopUpTimeout;
    }

    get popUpTimeout() {
        return this.showPopUpTimeout;
    }

    get color() {
        return this.mainTitleSetting.fontColor;
    }

    get size() {
        return this.mainTitleSetting.fontSize;
    }

    get weight() {
        return this.mainTitleSetting.fontWeight;
    }

    setMainTitleHighLight(isHighLight) {
        if (isHighLight) {
            this.mainTitleSetting = {
                fontColor: this.treeViewTheme.primaryTitleActiveFontColor,
                fontSize: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_text_size_body1'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                fontWeight: FontWeight.Regular,
            };
        } else {
            this.mainTitleSetting = {
                fontColor: this.treeViewTheme.primaryTitleFontColor,
                fontSize: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_text_size_body1'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                fontWeight: FontWeight.Normal,
            };
        }
    }
}

export class InputText extends NodeBaseInfo {
    constructor() {
        super();
        this.status = undefined;
        this.statusColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_background'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.editItemColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_emphasize'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.radius = {
            'id': -1,
            'type': 10002,
            params: ['sys.float.ohos_id_corner_radius_default_xs'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.treeViewTheme = TreeViewTheme.getInstance();
        this.itemWidth = ITEM_WIDTH;
        this.itemHeight = ITEM_HEIGHT_INPUT;
        this.rightMargin = {
            'id': -1,
            'type': 10002,
            params: ['sys.float.ohos_id_text_paragraph_margin_xs'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.inputTextSetting = {
            fontColor: this.treeViewTheme.primaryTitleFontColor,
            fontSize: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_body1'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
            fontWeight: FontWeight.Normal,
        };
    }

    get color() {
        return this.inputTextSetting.fontColor;
    }

    get size() {
        return this.inputTextSetting.fontSize;
    }

    get weight() {
        return this.inputTextSetting.fontWeight;
    }

    get borderRadius() {
        return this.radius;
    }

    get backgroundColor() {
        return this.statusColor;
    }

    get editColor() {
        return this.editItemColor;
    }

    get textInputStatusColor() {
        return this.status;
    }
}

/**
 * get LengthMetrics
 *
 * @param Resource | number type
 * @returns LengthMetrics
 */
function getLengthMetricsByResourceOrNumber(resourceOrNumber) {
    if (!resourceOrNumber) {
        return LengthMetrics.vp(0);
    } else if (typeof resourceOrNumber === 'number') {
        return LengthMetrics.vp(resourceOrNumber);
    } else {
        return LengthMetrics.resource(resourceOrNumber);
    }
}

export default {
    TreeControllerV2,
    TreeListenerV2,
    TreeListenerManagerV2,
    TreeViewV2
}