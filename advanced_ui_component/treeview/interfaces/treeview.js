/**
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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


var __decorate = (this && this.__decorate) || function (a30, b30, c30, d30) {
    var e30 = arguments.length,
        f30 = e30 < 3 ? b30 : d30 === null ? d30 = Object.getOwnPropertyDescriptor(b30, c30) : d30, g30;
    if (typeof Reflect === 'object' && typeof Reflect.decorate === 'function') {
        f30 = Reflect.decorate(a30, b30, c30, d30);
    } else {
        for (var h30 = a30.length - 1; h30 >= 0; h30--) {
            if (g30 = a30[h30]) {
                f30 = (e30 < 3 ? g30(f30) : e30 > 3 ? g30(b30, c30, f30) : g30(b30, c30)) || f30;
            }
        }
    }
    return e30 > 3 && f30 && Object.defineProperty(b30, c30, f30), f30;
};
if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {
    });
}

const hilog = requireNapi('hilog');
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const resourceManager = requireNapi('resourceManager');
const accessibility = requireNapi('accessibility');
const BusinessError = requireNapi('BusinessError');

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
const TAG = 'TreeView';
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
    'moduleName': '__harDefaultModuleName__',
};
const ARROW_DOWN_WITHE = {
    'id': -1,
    'type': 40000,
    params: ['sys.symbol.chevron_down'],
    'bundleName': '__harDefaultBundleName__',
    'moduleName': '__harDefaultModuleName__',
};
const ARROW_RIGHT = {
    'id': -1,
    'type': 40000,
    params: ['sys.symbol.chevron_right'],
    'bundleName': '__harDefaultBundleName__',
    'moduleName': '__harDefaultModuleName__',
};
const ARROW_RIGHT_WITHE = {
    'id': -1,
    'type': 40000,
    params: ['sys.symbol.chevron_right'],
    'bundleName': '__harDefaultBundleName__',
    'moduleName': '__harDefaultModuleName__',
};
var Event;
(function (z29) {
    z29[z29['TOUCH_DOWN'] = 0] = 'TOUCH_DOWN';
    z29[z29['TOUCH_UP'] = 1] = 'TOUCH_UP';
    z29[z29['HOVER'] = 3] = 'HOVER';
    z29[z29['HOVER_OVER'] = 4] = 'HOVER_OVER';
    z29[z29['FOCUS'] = 5] = 'FOCUS';
    z29[z29['BLUR'] = 6] = 'BLUR';
    z29[z29['MOUSE_BUTTON_RIGHT'] = 7] = 'MOUSE_BUTTON_RIGHT';
    z29[z29['DRAG'] = 8] = 'DRAG';
})(Event || (Event = {}));
var MenuOperation;
(function (y29) {
    y29[y29['ADD_NODE'] = 0] = 'ADD_NODE';
    y29[y29['REMOVE_NODE'] = 1] = 'REMOVE_NODE';
    y29[y29['MODIFY_NODE'] = 2] = 'MODIFY_NODE';
    y29[y29['COMMIT_NODE'] = 3] = 'COMMIT_NODE';
})(MenuOperation || (MenuOperation = {}));
var PopUpType;
(function (x29) {
    x29[x29['HINTS'] = 0] = 'HINTS';
    x29[x29['WARNINGS'] = 1] = 'WARNINGS';
})(PopUpType || (PopUpType = {}));
var InputError;
(function (w29) {
    w29[w29['INVALID_ERROR'] = 0] = 'INVALID_ERROR';
    w29[w29['LENGTH_ERROR'] = 1] = 'LENGTH_ERROR';
    w29[w29['NONE'] = 2] = 'NONE';
})(InputError || (InputError = {}));
var Flag;
(function (v29) {
    v29[v29['DOWN_FLAG'] = 0] = 'DOWN_FLAG';
    v29[v29['UP_FLAG'] = 1] = 'UP_FLAG';
    v29[v29['NONE'] = 2] = 'NONE';
})(Flag || (Flag = {}));

export var NodeStatus;
(function (u29) {
    u29[u29['EXPAND'] = 0] = 'EXPAND';
    u29[u29['COLLAPSE'] = 1] = 'COLLAPSE';
})(NodeStatus || (NodeStatus = {}));

export var InteractionStatus;
(function (t29) {
    t29[t29['NORMAL'] = 0] = 'NORMAL';
    t29[t29['SELECTED'] = 1] = 'SELECTED';
    t29[t29['EDIT'] = 2] = 'EDIT';
    t29[t29['FINISH_EDIT'] = 3] = 'FINISH_EDIT';
    t29[t29['DRAG_INSERT'] = 4] = 'DRAG_INSERT';
    t29[t29['FINISH_DRAG_INSERT'] = 5] = 'FINISH_DRAG_INSERT';
})(InteractionStatus || (InteractionStatus = {}));
var CollapseImageType;
(function (s29) {
    s29[s29['ARROW_DOWN'] = 0] = 'ARROW_DOWN';
    s29[s29['ARROW_RIGHT'] = 1] = 'ARROW_RIGHT';
    s29[s29['ARROW_DOWN_WHITE'] = 2] = 'ARROW_DOWN_WHITE';
    s29[s29['ARROW_RIGHT_WHITE'] = 3] = 'ARROW_RIGHT_WHITE';
})(CollapseImageType || (CollapseImageType = {}));
var AccessibilityNodeType;
(function (r29) {
    r29[r29['TEXT'] = 0] = 'TEXT';
    r29[r29['PLACE'] = 1] = 'PLACE';
    r29[r29['LIFT'] = 2] = 'LIFT';
})(AccessibilityNodeType || (AccessibilityNodeType = {}));

class Util {
    static isSymbolResource(p29) {
        if (!Util.isResourceType(p29)) {
            return false;
        }
        let q29 = p29;
        return q29.type === RESOURCE_TYPE_SYMBOL;
    }

    static isResourceType(o29) {
        if (!o29) {
            return false;
        }
        if (typeof o29 === 'string' || typeof o29 === 'undefined') {
            return false;
        }
        return true;
    }
}

class TreeViewNodeItemFactory {
    constructor() {
    }

    static getInstance() {
        if (!TreeViewNodeItemFactory.instance) {
            TreeViewNodeItemFactory.instance = new TreeViewNodeItemFactory();
        }
        return TreeViewNodeItemFactory.instance;
    }

    createNode() {
        return {
            imageNode: undefined,
            inputText: new InputText(),
            mainTitleNode: new MainTitleNode(''),
            imageCollapse: undefined,
            fontColor: undefined,
        };
    }

    createNodeByNodeParam(m29) {
        let n29 = this.createNode();
        if (m29.icon) {
            n29.imageNode = new ImageNode(m29.icon, m29.symbolIconStyle, {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_alpha_content_fourth'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            }, IMAGE_NODE_HEIGHT, IMAGE_NODE_WIDTH, m29.selectedIcon, m29.symbolSelectedIconStyle, m29.editIcon,
                m29.symbolEditIconStyle);
        }
        if (m29.primaryTitle) {
            n29.mainTitleNode = new MainTitleNode(m29.primaryTitle);
        }
        return n29;
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
            'moduleName': '__harDefaultModuleName__',
        };
        this.secondaryTitleFontColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_secondary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.primaryTitleActiveFontColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_text_primary_activated'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.itemPressedBgColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_click_effect'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.itemHoverBgColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_hover'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.borderFocusedColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_focused_outline'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.leftIconColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.icon_secondary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.leftIconActiveColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.icon_secondary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.arrowIconColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.icon_tertiary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
    }

    static getInstance() {
        if (!TreeViewTheme.instance) {
            TreeViewTheme.instance = new TreeViewTheme();
        }
        return TreeViewTheme.instance;
    }
}

let NodeInfo = class NodeInfo {
    constructor(k29, l29) {
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
        this.node = k29;
        this.nodeParam = l29;
        this.nodeItemView = TreeViewNodeItemFactory.getInstance().createNodeByNodeParam(l29);
        this.popUpInfo = {
            popUpIsShow: false,
            popUpEnableArrow: false,
            popUpColor: undefined,
            popUpText: '',
            popUpTextColor: undefined,
        };
        this.nodeHeight = NODE_HEIGHT;
        this.nodeLeftPadding = k29.nodeLevel * LEVEL_MARGIN + MARGIN_OFFSET;
        this.nodeColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_background'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
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
                'moduleName': '__harDefaultModuleName__',
            },
            hover: this.treeViewTheme.itemHoverBgColor,
            press: this.treeViewTheme.itemPressedBgColor,
            selected: this.treeViewTheme.itemSelectedBgColor,
            highLight: {
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_activated'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
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
                'moduleName': '__harDefaultModuleName__',
            }
        };
        this.flagLineLeftMargin = k29.nodeLevel * LEVEL_MARGIN + MARGIN_OFFSET;
    }

    addImageCollapse(j29) {
        if (j29) {
            this.nodeItemView.imageCollapse =
                CollapseImageNodeFlyweightFactory.getCollapseImageNodeByType(CollapseImageType.ARROW_RIGHT);
        } else {
            this.nodeItemView.imageCollapse = undefined;
        }
    }

    addImageExpand(i29) {
        if (i29) {
            this.nodeItemView.imageCollapse =
                CollapseImageNodeFlyweightFactory.getCollapseImageNodeByType(CollapseImageType.ARROW_DOWN);
        } else {
            this.nodeItemView.imageCollapse = undefined;
        }
    }

    setFontColor(h29) {
        this.fontColor = h29;
    }

    getFontColor() {
        return this.fontColor;
    }

    getPopUpInfo() {
        return this.popUpInfo;
    }

    setPopUpIsShow(g29) {
        this.popUpInfo.popUpIsShow = g29;
    }

    setPopUpEnableArrow(f29) {
        this.popUpInfo.popUpEnableArrow = f29;
    }

    setPopUpColor(e29) {
        this.popUpInfo.popUpColor = e29;
    }

    setPopUpText(d29) {
        this.popUpInfo.popUpText = d29;
    }

    setPopUpTextColor(c29) {
        this.popUpInfo.popUpTextColor = c29;
    }

    getIsShowTitle() {
        return this.isShowTitle;
    }

    getIsShowInputText() {
        return this.isShowInputText;
    }

    setTitleAndInputTextStatus(b29) {
        if (b29) {
            this.isShowTitle = false;
            this.isShowInputText = true;
        } else {
            this.isShowTitle = true;
            this.isShowInputText = false;
        }
    }

    handleImageCollapseAfterAddNode(a29) {
        if (a29) {
            this.nodeItemView.imageCollapse =
                CollapseImageNodeFlyweightFactory.getCollapseImageNodeByType(CollapseImageType.ARROW_DOWN);
        } else {
            this.nodeItemView.imageCollapse = undefined;
        }
    }

    setNodeColor(z28) {
        if (z28 === undefined) {
            return;
        }
        this.nodeColor = z28;
    }

    getNodeColor() {
        return this.nodeColor;
    }

    setListItemHeight(y28) {
        this.listItemHeight = y28;
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

    setNodeIsShow(x28) {
        this.nodeIsShow = x28;
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

    setNodeBorder(w28) {
        this.nodeBorder.borderWidth = w28 ? this.borderWidth.has : this.borderWidth.none;
    }

    getChildNodeInfo() {
        return this.node.childNodeInfo;
    }

    getMenu() {
        return this.nodeParam.container;
    }

    setIsSelected(v28) {
        this.isSelected = v28;
    }

    getIsSelected() {
        return this.isSelected;
    }

    getNodeInfoData() {
        return this.nodeParam;
    }

    getNodeInfoNode() {
        return this.node;
    }

    getIsFolder() {
        return this.nodeParam.isFolder;
    }

    setCanShowFlagLine(u28) {
        this.canShowFlagLine = u28;
    }

    getCanShowFlagLine() {
        return this.canShowFlagLine;
    }

    setFlagLineLeftMargin(t28) {
        if (t28 === undefined) {
            return;
        }
        this.flagLineLeftMargin = t28 * LEVEL_MARGIN + MARGIN_OFFSET;
    }

    getFlagLineLeftMargin() {
        return this.flagLineLeftMargin;
    }

    getNodeLevel() {
        return this.node.nodeLevel;
    }

    setIsOverBorder(s28) {
        this.isOverBorder = s28;
    }

    getIsOverBorder() {
        return this.isOverBorder;
    }

    setCanShowBottomFlagLine(r28) {
        this.canShowBottomFlagLine = r28;
    }

    getCanShowBottomFlagLine() {
        return this.canShowBottomFlagLine;
    }

    setIsHighLight(q28) {
        this.isHighLight = q28;
    }

    getIsHighLight() {
        return this.isHighLight;
    }

    setIsModify(p28) {
        this.isModify = p28;
    }

    getIsModify() {
        return this.isModify;
    }
};
NodeInfo = __decorate([
    Observed
], NodeInfo);

export { NodeInfo };

export var TreeListenType;
(function (o28) {
    o28['NODE_CLICK'] = 'NodeClick';
    o28['NODE_ADD'] = 'NodeAdd';
    o28['NODE_DELETE'] = 'NodeDelete';
    o28['NODE_MODIFY'] = 'NodeModify';
    o28['NODE_MOVE'] = 'NodeMove';
})(TreeListenType || (TreeListenType = {}));

export class TreeListener {
    constructor() {
        this._events = [];
        this._once_events = [];
    }

    on(k28, l28) {
        if (Array.isArray(k28)) {
            for (let m28 = 0, n28 = k28.length; m28 < n28; m28++) {
                this.on(k28[m28], l28);
            }
        } else {
            (this._events[k28] || (this._events[k28] = [])).push(l28);
        }
    }

    once(i28, j28) {
        if (Array.isArray(i28)) {
            this.off(i28, j28);
        } else {
            (this._once_events[i28] || (this._once_events[i28] = [])).push(j28);
        }
    }

    off(b28, c28) {
        if (b28 === null) {
            this._events = [];
        }
        if (Array.isArray(b28)) {
            for (let g28 = 0, h28 = b28.length; g28 < h28; g28++) {
                this.off(b28[g28], c28);
            }
        }
        let d28 = this._events[b28];
        if (!d28) {
            return;
        }
        if (c28 === null) {
            this._events[b28] = null;
        }
        let e28 = d28.length;
        while (e28--) {
            let f28 = d28[e28];
            if (f28 === c28) {
                d28.splice(e28, 1);
                break;
            }
        }
    }

    emit(r27, s27) {
        if (this._once_events[r27]) {
            let x27 = Array.from(this._once_events[r27]);
            if (x27) {
                for (let y27 = 0, z27 = x27.length; y27 < z27; y27++) {
                    try {
                        x27[y27](s27);
                    } catch (a28) {
                        throw new Error('once function callbacks error.');
                    }
                }
                this._once_events[r27] = null;
            }
        } else if (this._events[r27]) {
            let t27 = Array.from(this._events[r27]);
            if (t27) {
                for (let u27 = 0, v27 = t27.length; u27 < v27; u27++) {
                    try {
                        t27[u27](s27);
                    } catch (w27) {
                        throw new Error('on function callbacks error.');
                    }
                }
            }
        }
    }
}

export class TreeListenerManager {
    constructor() {
        this.appEventBus = new TreeListener();
    }

    static getInstance() {
        if (AppStorage.Get('app_key_event_bus') === undefined) {
            AppStorage.SetOrCreate('app_key_event_bus', new TreeListenerManager());
        }
        return AppStorage.Get('app_key_event_bus');
    }

    getTreeListener() {
        return this.appEventBus;
    }
}
TreeListenerManager.APP_KEY_EVENT_BUS = 'app_key_event_bus';

export class TreeView extends ViewPU {
    constructor(l27, m27, n27, o27 = -1, p27 = undefined, q27) {
        super(l27, n27, o27, q27);
        if (typeof p27 === 'function') {
            this.paramsGenerator_ = p27;
        }
        this.treeController = new TreeController();
        this.__nodeList = new ObservedPropertyObjectPU([], this, 'nodeList');
        this.listNodeDataSource = new ListNodeDataSource();
        this.__item = new ObservedPropertyObjectPU(null, this, 'item');
        this.__touchCount = new ObservedPropertySimplePU(0, this, 'touchCount');
        this.__dropSelectedIndex = new ObservedPropertySimplePU(0, this, 'dropSelectedIndex');
        this.__viewLastIndex = new ObservedPropertySimplePU(-1, this, 'viewLastIndex');
        this.__followingSystemFontScale = new ObservedPropertySimplePU(false, this, 'followingSystemFontScale');
        this.__maxAppFontScale = new ObservedPropertySimplePU(1, this, 'maxAppFontScale');
        this.__listItemBgColor = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_background_transparent'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        }, this, 'listItemBgColor');
        this.__allParentNode = new ObservedPropertyObjectPU([], this, 'allParentNode');
        this.__treeViewTheme = new ObservedPropertyObjectPU(TreeViewTheme.getInstance(), this, 'treeViewTheme');
        this.addProvidedVar('treeViewTheme', this.__treeViewTheme, false);
        this.__clickButtonFlag = new ObservedPropertySimplePU(true, this, 'clickButtonFlag');
        this.addProvidedVar('clickButtonFlag', this.__clickButtonFlag, false);
        this.__accessibilityNodeType =
            new ObservedPropertySimplePU(AccessibilityNodeType.TEXT, this, 'accessibilityNodeType');
        this.addProvidedVar('accessibilityNodeType', this.__accessibilityNodeType, false);
        this.__isAccessibilityEnabled = new ObservedPropertySimplePU(accessibility.isScreenReaderOpenSync(), this, 'isAccessibilityEnabled');
        this.addProvidedVar('isAccessibilityEnabled', this.__isAccessibilityEnabled, false);
        this.listTreeViewMenu = this.NullBuilder;
        this.MAX_CN_LENGTH = 254;
        this.MAX_EN_LENGTH = 255;
        this.INITIAL_INVALID_VALUE = -1;
        this.MAX_TOUCH_DOWN_COUNT = 0;
        this.isMultiPress = false;
        this.touchDownCount = this.INITIAL_INVALID_VALUE;
        this.appEventBus = TreeListenerManager.getInstance().getTreeListener();
        this.itemPadding = {
            left: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_card_margin_start'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            },
            right: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_card_margin_end'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            },
            top: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_margin_vertical'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            },
            bottom: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_margin_vertical'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            },
        };
        this.textInputPadding = {
            left: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level0'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            },
            right: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level0'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            },
            top: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level0'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            },
            bottom: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level0'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            },
        };
        this.setInitiallyProvidedValue(m27);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(k27) {
        if (k27.treeController !== undefined) {
            this.treeController = k27.treeController;
        }
        if (k27.nodeList !== undefined) {
            this.nodeList = k27.nodeList;
        }
        if (k27.listNodeDataSource !== undefined) {
            this.listNodeDataSource = k27.listNodeDataSource;
        }
        if (k27.item !== undefined) {
            this.item = k27.item;
        }
        if (k27.touchCount !== undefined) {
            this.touchCount = k27.touchCount;
        }
        if (k27.dropSelectedIndex !== undefined) {
            this.dropSelectedIndex = k27.dropSelectedIndex;
        }
        if (k27.viewLastIndex !== undefined) {
            this.viewLastIndex = k27.viewLastIndex;
        }
        if (k27.followingSystemFontScale !== undefined) {
            this.followingSystemFontScale = k27.followingSystemFontScale;
        }
        if (k27.maxAppFontScale !== undefined) {
            this.maxAppFontScale = k27.maxAppFontScale;
        }
        if (k27.listItemBgColor !== undefined) {
            this.listItemBgColor = k27.listItemBgColor;
        }
        if (k27.allParentNode !== undefined) {
            this.allParentNode = k27.allParentNode;
        }
        if (k27.treeViewTheme !== undefined) {
            this.treeViewTheme = k27.treeViewTheme;
        }
        if (k27.clickButtonFlag !== undefined) {
            this.clickButtonFlag = k27.clickButtonFlag;
        }
        if (k27.accessibilityNodeType !== undefined) {
            this.accessibilityNodeType = k27.accessibilityNodeType;
        }
        if (k27.isAccessibilityEnabled !== undefined) {
            this.isAccessibilityEnabled = k27.isAccessibilityEnabled;
        }
        if (k27.listTreeViewMenu !== undefined) {
            this.listTreeViewMenu = k27.listTreeViewMenu;
        }
        if (k27.MAX_CN_LENGTH !== undefined) {
            this.MAX_CN_LENGTH = k27.MAX_CN_LENGTH;
        }
        if (k27.MAX_EN_LENGTH !== undefined) {
            this.MAX_EN_LENGTH = k27.MAX_EN_LENGTH;
        }
        if (k27.INITIAL_INVALID_VALUE !== undefined) {
            this.INITIAL_INVALID_VALUE = k27.INITIAL_INVALID_VALUE;
        }
        if (k27.MAX_TOUCH_DOWN_COUNT !== undefined) {
            this.MAX_TOUCH_DOWN_COUNT = k27.MAX_TOUCH_DOWN_COUNT;
        }
        if (k27.isMultiPress !== undefined) {
            this.isMultiPress = k27.isMultiPress;
        }
        if (k27.touchDownCount !== undefined) {
            this.touchDownCount = k27.touchDownCount;
        }
        if (k27.appEventBus !== undefined) {
            this.appEventBus = k27.appEventBus;
        }
        if (k27.itemPadding !== undefined) {
            this.itemPadding = k27.itemPadding;
        }
        if (k27.textInputPadding !== undefined) {
            this.textInputPadding = k27.textInputPadding;
        }
    }

    updateStateVars(j27) {
    }

    purgeVariableDependenciesOnElmtId(i27) {
        this.__nodeList.purgeDependencyOnElmtId(i27);
        this.__item.purgeDependencyOnElmtId(i27);
        this.__touchCount.purgeDependencyOnElmtId(i27);
        this.__dropSelectedIndex.purgeDependencyOnElmtId(i27);
        this.__viewLastIndex.purgeDependencyOnElmtId(i27);
        this.__followingSystemFontScale.purgeDependencyOnElmtId(i27);
        this.__maxAppFontScale.purgeDependencyOnElmtId(i27);
        this.__listItemBgColor.purgeDependencyOnElmtId(i27);
        this.__allParentNode.purgeDependencyOnElmtId(i27);
        this.__treeViewTheme.purgeDependencyOnElmtId(i27);
        this.__clickButtonFlag.purgeDependencyOnElmtId(i27);
        this.__accessibilityNodeType.purgeDependencyOnElmtId(i27);
        this.__isAccessibilityEnabled.purgeDependencyOnElmtId(i27);
    }

    aboutToBeDeleted() {
        this.__nodeList.aboutToBeDeleted();
        this.__item.aboutToBeDeleted();
        this.__touchCount.aboutToBeDeleted();
        this.__dropSelectedIndex.aboutToBeDeleted();
        this.__viewLastIndex.aboutToBeDeleted();
        this.__followingSystemFontScale.aboutToBeDeleted();
        this.__maxAppFontScale.aboutToBeDeleted();
        this.__listItemBgColor.aboutToBeDeleted();
        this.__allParentNode.aboutToBeDeleted();
        this.__treeViewTheme.aboutToBeDeleted();
        this.__clickButtonFlag.aboutToBeDeleted();
        this.__accessibilityNodeType.aboutToBeDeleted();
        this.__isAccessibilityEnabled.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get nodeList() {
        return this.__nodeList.get();
    }

    set nodeList(h27) {
        this.__nodeList.set(h27);
    }

    get item() {
        return this.__item.get();
    }

    set item(g27) {
        this.__item.set(g27);
    }

    get touchCount() {
        return this.__touchCount.get();
    }

    set touchCount(f27) {
        this.__touchCount.set(f27);
    }

    get dropSelectedIndex() {
        return this.__dropSelectedIndex.get();
    }

    set dropSelectedIndex(e27) {
        this.__dropSelectedIndex.set(e27);
    }

    get viewLastIndex() {
        return this.__viewLastIndex.get();
    }

    set viewLastIndex(d27) {
        this.__viewLastIndex.set(d27);
    }

    get followingSystemFontScale() {
        return this.__followingSystemFontScale.get();
    }

    set followingSystemFontScale(c27) {
        this.__followingSystemFontScale.set(c27);
    }

    get maxAppFontScale() {
        return this.__maxAppFontScale.get();
    }

    set maxAppFontScale(b27) {
        this.__maxAppFontScale.set(b27);
    }

    get listItemBgColor() {
        return this.__listItemBgColor.get();
    }

    set listItemBgColor(a27) {
        this.__listItemBgColor.set(a27);
    }

    get allParentNode() {
        return this.__allParentNode.get();
    }

    set allParentNode(z26) {
        this.__allParentNode.set(z26);
    }

    get treeViewTheme() {
        return this.__treeViewTheme.get();
    }

    set treeViewTheme(y26) {
        this.__treeViewTheme.set(y26);
    }

    get clickButtonFlag() {
        return this.__clickButtonFlag.get();
    }

    set clickButtonFlag(x26) {
        this.__clickButtonFlag.set(x26);
    }

    get accessibilityNodeType() {
        return this.__accessibilityNodeType.get();
    }

    set accessibilityNodeType(w26) {
        this.__accessibilityNodeType.set(w26);
    }

    get isAccessibilityEnabled() {
        return this.__isAccessibilityEnabled.get();
    }

    set isAccessibilityEnabled(v26) {
        this.__isAccessibilityEnabled.set(v26);
    }

    NullBuilder(u26 = null) {
    }

    onWillApplyTheme(t26) {
        this.treeViewTheme.itemSelectedBgColor = t26.colors.interactiveSelect;
        this.treeViewTheme.itemPressedBgColor = t26.colors.interactivePressed;
        this.treeViewTheme.itemHoverBgColor = t26.colors.interactiveHover;
        this.treeViewTheme.primaryTitleFontColor = t26.colors.fontPrimary;
        this.treeViewTheme.secondaryTitleFontColor = t26.colors.fontSecondary;
        this.treeViewTheme.primaryTitleActiveFontColor = t26.colors.interactiveActive;
        this.treeViewTheme.borderFocusedColor = t26.colors.interactiveFocus;
        this.treeViewTheme.leftIconColor = t26.colors.iconSecondary;
        this.treeViewTheme.leftIconActiveColor = t26.colors.interactiveActive;
        this.treeViewTheme.arrowIconColor = t26.colors.iconPrimary;
        this.treeController.treeViewTheme = this.treeViewTheme;
    }

    aboutToAppear() {
        if (this.treeController !== null) {
            this.listNodeDataSource = this.treeController.getListNodeDataSource();
            this.nodeList = this.treeController.getListNodeDataSource().listNode;
            this.item = this.treeController.getListNodeDataSource().listNode;
        }
        let r26 = this.getUIContext();
        this.followingSystemFontScale = r26.isFollowingSystemFontScale();
        this.maxAppFontScale = r26.getMaxFontScale();
        accessibility.on('screenReaderStateChange', (s26) => {
            this.isAccessibilityEnabled = s26;
        });
    }

    decideFontScale() {
        let p26 = this.getUIContext();
        let q26 = p26.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.followingSystemFontScale) {
            return 1;
        }
        return Math.min(q26, this.maxAppFontScale, MAX_FONT_SCALE);
    }

    decideSymbolFontScale(l26) {
        if (!l26 || !this.followingSystemFontScale) {
            return 1;
        }
        let m26 = this.getUIContext();
        let n26 = m26.getHostContext()?.config?.fontSizeScale ?? 1;
        let o26 = Math.min(n26, this.maxAppFontScale, MAX_SYMBOL_FONT_SCALE);
        return Math.max(o26, MIN_SYMBOL_FONT_SCALE);
    }

    popupForShowTitle(d26, e26, f26, g26 = null) {
        this.observeComponentCreation2((j26, k26) => {
            Row.create();
            Row.backgroundColor(e26);
            Row.border({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_elements_margin_horizontal_l'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                }
            });
            Row.padding({
                left: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_elements_margin_horizontal_l'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                },
                right: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_elements_margin_horizontal_l'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                },
                top: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_card_margin_middle'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                },
                bottom: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_card_margin_middle'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                },
            });
        }, Row);
        this.observeComponentCreation2((h26, i26) => {
            Text.create(d26);
            Text.fontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_body2'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            });
            Text.fontWeight('regular');
            Text.fontColor(f26);
            Text.minFontScale(MIN_FONT_SCALE);
            Text.maxFontScale(this.decideFontScale());
        }, Text);
        Text.pop();
        Row.pop();
    }

    builder(c26 = null) {
        this.listTreeViewMenu.bind(this)();
    }

    draggingPopup(e25, f25 = null) {
        this.observeComponentCreation2((a26, b26) => {
            Row.create();
            Row.id(`treeView_node_lift${e25.getNodeCurrentNodeId()}`);
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
        this.observeComponentCreation2((m25, n25) => {
            If.create();
            if (e25.getNodeItem().imageNode) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((y25, z25) => {
                        Row.create();
                        Row.backgroundColor(COLOR_IMAGE_ROW);
                        Row.margin({
                            end: getLengthMetricsByResourceOrNumber(e25.getNodeItem().imageNode?.itemRightMargin)
                        });
                        Row.height(e25.getNodeItem().imageNode?.itemHeight *
                        this.decideSymbolFontScale(e25.getNodeItem().imageNode?.symbolNormalSource !== undefined ||
                        Util.isSymbolResource(e25.getNodeItem().imageNode?.normalSource)));
                        Row.width(e25.getNodeItem().imageNode?.itemWidth *
                        this.decideSymbolFontScale(e25.getNodeItem().imageNode?.symbolNormalSource !== undefined ||
                        Util.isSymbolResource(e25.getNodeItem().imageNode?.normalSource)));
                    }, Row);
                    this.observeComponentCreation2((o25, p25) => {
                        If.create();
                        if (e25.getNodeItem().imageNode?.symbolNormalSource) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((w25, x25) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.attributeModifier.bind(this)(e25.getNodeItem()
                                        .imageNode?.symbolNormalSource);
                                    SymbolGlyph.fontSize(`${e25.getNodeItem().imageNode?.itemHeight *
                                    this.decideSymbolFontScale(true)}vp`);
                                    SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                    SymbolGlyph.opacity(this.listNodeDataSource.getDragPopupPara().imageOpacity);
                                }, SymbolGlyph);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((q25, r25) => {
                                    If.create();
                                    if (Util.isSymbolResource(e25.getNodeItem().imageNode?.normalSource)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((u25, v25) => {
                                                SymbolGlyph.create(e25.getNodeItem().imageNode?.normalSource);
                                                SymbolGlyph.fontSize(`${e25.getNodeItem().imageNode?.itemHeight *
                                                this.decideSymbolFontScale(true)}vp`);
                                                SymbolGlyph.opacity(this.listNodeDataSource.getDragPopupPara()
                                                    .imageOpacity);
                                            }, SymbolGlyph);
                                        });
                                    } else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((s25, t25) => {
                                                Image.create(e25.getNodeItem().imageNode?.normalSource);
                                                Image.objectFit(ImageFit.Contain);
                                                Image.height(e25.getNodeItem().imageNode?.itemHeight);
                                                Image.width(e25.getNodeItem().imageNode?.itemWidth);
                                                Image.opacity(this.listNodeDataSource.getDragPopupPara().imageOpacity);
                                                Image.matchTextDirection((e25.getNodeItem()
                                                    .imageCollapse?.collapseSource === ARROW_RIGHT ||
                                                    e25.getNodeItem().imageCollapse?.collapseSource ===
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
        this.observeComponentCreation2((k25, l25) => {
            Row.create();
            Row.constraintSize({
                minWidth: e25.getNodeItem().imageNode ?
                this.listNodeDataSource.getDragPopupPara().textConstraintSize.minWidth1 :
                this.listNodeDataSource.getDragPopupPara().textConstraintSize.minWidth2,
                maxWidth: e25.getNodeItem().imageNode ?
                this.listNodeDataSource.getDragPopupPara().textConstraintSize.maxWidth1 :
                this.listNodeDataSource.getDragPopupPara().textConstraintSize.maxWidth2,
            });
        }, Row);
        this.observeComponentCreation2((g25, h25) => {
            If.create();
            if (e25.getNodeItem().mainTitleNode && e25.getIsShowTitle()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((i25, j25) => {
                        Text.create(e25.getNodeItem().mainTitleNode?.title);
                        Text.maxLines(1);
                        Text.minFontScale(MIN_FONT_SCALE);
                        Text.maxFontScale(this.decideFontScale());
                        Text.fontSize(e25.getNodeItem().mainTitleNode?.size);
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
            'moduleName': '__harDefaultModuleName__',
        });
        this.nodeList[this.viewLastIndex].fontColor = this.treeViewTheme.primaryTitleFontColor;
        this.listNodeDataSource.listNode[this.viewLastIndex].setNodeColor({
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_background_transparent'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
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

    setImageSources(b25, c25) {
        let d25 = this.nodeList[b25];
        d25.setIsSelected(c25 === InteractionStatus.SELECTED ||
            c25 === InteractionStatus.EDIT || c25 === InteractionStatus.FINISH_EDIT);
        if (d25.getNodeItem().mainTitleNode !== null && c25 !== InteractionStatus.DRAG_INSERT &&
            c25 !== InteractionStatus.FINISH_DRAG_INSERT) {
            d25.getNodeItem().mainTitleNode?.setMainTitleSelected(c25 === InteractionStatus.SELECTED ||
                c25 === InteractionStatus.FINISH_EDIT);
        }
        if (d25.getNodeItem().imageNode !== null) {
            d25.getNodeItem().imageNode?.setImageSource(c25);
        }
    }

    touchInner(y24, z24) {
        this.viewLastIndex = this.listNodeDataSource.getLastIndex();
        let a25 = this.listNodeDataSource.findIndex(y24.getNodeCurrentNodeId());
        if (z24.type === TouchType.Down) {
            if (a25 !== this.viewLastIndex) {
                this.clearLastIndexColor();
                this.listNodeDataSource.lastIndex = a25;
                this.listNodeDataSource.setClickIndex(a25);
            }
        }
        if (z24.type === TouchType.Up) {
            this.listNodeDataSource.listNode[a25].setIsSelected(true);
            this.listNodeDataSource.setImageSource(a25, InteractionStatus.SELECTED);
            if (this.listNodeDataSource.listNode[a25].getNodeItem().imageNode !== null) {
                this.listNodeDataSource.listNode[a25].imageSource = this.listNodeDataSource.listNode[a25]
                    .getNodeItem().imageNode?.source;
                this.listNodeDataSource.listNode[a25].symbolSource = this.listNodeDataSource.listNode[a25]
                    .getNodeItem().imageNode?.symbolSource;
            }
            if (a25 !== this.viewLastIndex) {
                this.clearLastIndexColor();
                this.listNodeDataSource.lastIndex = a25;
                this.listNodeDataSource.setClickIndex(a25);
            }
            this.viewLastIndex = a25;
        }
        if (this.listNodeDataSource.getLastIndex() !== -1 && a25 !== this.listNodeDataSource.getLastIndex()) {
            this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false,
                this.listNodeDataSource.getLastIndex());
            this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(),
                MenuOperation.COMMIT_NODE);
        }
    }

    clickInner(w24) {
        this.viewLastIndex = this.listNodeDataSource.getLastIndex();
        let x24 = this.listNodeDataSource.findIndex(w24.getNodeCurrentNodeId());
        if (x24 !== this.viewLastIndex) {
            this.clearLastIndexColor();
            this.listNodeDataSource.lastIndex = x24;
            this.listNodeDataSource.setClickIndex(x24);
        }
        this.listNodeDataSource.listNode[x24].setIsSelected(true);
        this.listNodeDataSource.setImageSource(x24, InteractionStatus.SELECTED);
        if (this.listNodeDataSource.listNode[x24].getNodeItem().imageNode !== null) {
            this.listNodeDataSource.listNode[x24].imageSource = this.listNodeDataSource.listNode[x24]
                .getNodeItem().imageNode?.source;
            this.listNodeDataSource.listNode[x24].symbolSource = this.listNodeDataSource.listNode[x24]
                .getNodeItem().imageNode?.symbolSource;
        }
        if (x24 !== this.viewLastIndex) {
            this.clearLastIndexColor();
            this.listNodeDataSource.lastIndex = x24;
            this.listNodeDataSource.setClickIndex(x24);
        }
        this.viewLastIndex = x24;
        if (this.listNodeDataSource.getLastIndex() !== -1 && x24 !== this.listNodeDataSource.getLastIndex()) {
            this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false,
                this.listNodeDataSource.getLastIndex());
            this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(),
                MenuOperation.COMMIT_NODE);
        }
    }

    initialRender() {
        this.observeComponentCreation2((m23, n23) => {
            List.create({});
            List.onDragMove((n24, o24) => {
                if (this.isMultiPress) {
                    hilog.error(LOG_CODE, TAG, 'drag error, a item has been dragged');
                    return;
                }
                let p24 = LIST_ITEM_HEIGHT;
                let q24 = Math.floor(n24.getY() /
                    (p24 / FLAG_NUMBER)) %
                    FLAG_NUMBER ? Flag.DOWN_FLAG : Flag.UP_FLAG;
                let r24 = JSON.parse(o24).insertIndex;
                let s24 = false;
                if (r24 >= this.listNodeDataSource.totalCount()) {
                    q24 = Flag.DOWN_FLAG;
                    r24 = this.listNodeDataSource.totalCount() - 1;
                    this.listNodeDataSource.getData(r24)?.setIsOverBorder(true);
                    s24 = true;
                } else {
                    this.listNodeDataSource.getData(r24)?.setIsOverBorder(false);
                }
                let t24 = this.listNodeDataSource.getData(r24);
                let u24 = t24?.getNodeCurrentNodeId();
                if (r24 !== this.listNodeDataSource.getLastPassIndex() && this.listNodeDataSource.getIsInnerDrag()) {
                    let v24 = this.listNodeDataSource.getIsParentOfInsertNode(u24);
                    if (v24) {
                        this.listNodeDataSource.setPassIndex(r24);
                        if (u24 !== undefined) {
                            this.listNodeDataSource.clearTimeOutAboutDelayHighLightAndExpand(this.listNodeDataSource.findIndex(u24));
                        }
                        this.listNodeDataSource.setFlag(Flag.NONE);
                        return;
                    }
                }
                this.listNodeDataSource.setLastPassIndex(r24);
                this.listNodeDataSource.setVisibility(q24, r24 - 1, s24,
                    ObservedObject.GetRawObject(this.allParentNode));
                if (u24 !== undefined && u24 !== this.listNodeDataSource.getDraggingCurrentNodeId()) {
                    this.listNodeDataSource.delayHighLightAndExpandNode(this.listNodeDataSource.findIndex(u24), u24,
                        r24);
                }
            });
            List.onDragEnter((k24, l24) => {
                if (this.listNodeDataSource.getIsInnerDrag()) {
                    this.listNodeDataSource.setIsDrag(true);
                    let m24 = DRAG_OPACITY;
                    this.listNodeDataSource.setListItemOpacity(m24);
                }
            });
            List.onDragLeave((h24, i24) => {
                this.listNodeDataSource.hideLastLine();
                this.listNodeDataSource.clearLastTimeoutHighLight();
                this.listNodeDataSource.clearLastTimeoutExpand();
                let j24 = DRAG_OPACITY_NONE;
                this.listNodeDataSource.setListItemOpacity(j24);
                this.listNodeDataSource.setIsDrag(false);
                this.listNodeDataSource.notifyDataReload();
            });
            List.onDrop((o23, p23) => {
                this.accessibilityNodeType = AccessibilityNodeType.PLACE;
                this.listNodeDataSource.clearLastTimeoutExpand();
                let q23 = DRAG_OPACITY_NONE;
                this.listNodeDataSource.setListItemOpacity(q23);
                let r23 = JSON.parse(p23).insertIndex;
                let s23 = this.dropSelectedIndex;
                if (s23 - 1 > this.listNodeDataSource.totalCount() || s23 === undefined) {
                    hilog.error(LOG_CODE, TAG, 'drag error, currentNodeIndex is not found');
                    this.listNodeDataSource.setIsDrag(false);
                    return;
                }
                if (r23 === this.listNodeDataSource.totalCount()) {
                    hilog.info(LOG_CODE, TAG, 'need to insert into the position of the last line');
                    r23 -= 1;
                }
                let t23 = this.listNodeDataSource.getData(r23);
                if (t23 === undefined) {
                    return;
                }
                let u23 = t23.getNodeCurrentNodeId();
                if (!this.listNodeDataSource.getIsDrag() || !this.listNodeDataSource.getIsInnerDrag()) {
                    this.listNodeDataSource.clearLastTimeoutHighLight();
                    this.listNodeDataSource.setIsInnerDrag(false);
                    this.listNodeDataSource.hideLastLine();
                    this.listNodeDataSource.initialParameterAboutDelayHighLightAndExpandIndex();
                    this.listNodeDataSource.refreshSubtitle(u23);
                    this.listNodeDataSource.notifyDataReload();
                    return;
                }
                let v23 = this.listNodeDataSource.getCurrentNodeInfo();
                let w23 = t23.getNodeParentNodeId();
                let x23 = this.listNodeDataSource.getDraggingCurrentNodeId();
                let y23 = this.listNodeDataSource.getDraggingParentNodeId();
                let z23 = this.listNodeDataSource.getIsParentOfInsertNode(u23);
                if (z23) {
                    this.listNodeDataSource.clearLastTimeoutHighLight();
                    this.listNodeDataSource.setIsInnerDrag(false);
                    this.listNodeDataSource.hideLastLine();
                    this.listNodeDataSource.notifyDataChange(r23);
                    this.listNodeDataSource.initialParameterAboutDelayHighLightAndExpandIndex();
                    this.listNodeDataSource.setIsDrag(false);
                    let g24 = this.listNodeDataSource.findIndex(x23);
                    this.listNodeDataSource.setClickIndex(g24);
                    this.listNodeDataSource.handleEvent(Event.DRAG, g24);
                    return;
                }
                if (this.listNodeDataSource.getExpandAndCollapseInfo(x23) === NodeStatus.EXPAND) {
                    this.listNodeDataSource.expandAndCollapseNode(this.listNodeDataSource.findIndex(x23));
                }
                let a24 = false;
                if (this.listNodeDataSource.getExpandAndCollapseInfo(u23) === NodeStatus.COLLAPSE) {
                    let f24 = this.listNodeDataSource.findIndex(u23);
                    if (this.listNodeDataSource.listNode[f24].getIsHighLight()) {
                        this.listNodeDataSource.expandAndCollapseNode(f24);
                    }
                    a24 = true;
                }
                this.listNodeDataSource.setLastDelayHighLightId();
                if (v23 !== null && x23 !== u23) {
                    this.listNodeDataSource.alterDragNode(w23, u23, y23, x23, v23);
                    this.listNodeDataSource.hideLastLine();
                } else {
                    this.listNodeDataSource.hideLastLine();
                    this.listNodeDataSource.setLastPassId(x23);
                    this.listNodeDataSource.hideLastLine();
                }
                let b24 = this.listNodeDataSource.findIndex(this.listNodeDataSource.getLastDelayHighLightId());
                this.listNodeDataSource.setLastDelayHighLightIndex(b24);
                this.listNodeDataSource.clearLastTimeoutHighLight();
                this.listNodeDataSource.initialParameterAboutDelayHighLightAndExpandIndex();
                this.listNodeDataSource.setIsDrag(false);
                let c24 = this.listNodeDataSource.findIndex(x23);
                this.listNodeDataSource.setClickIndex(c24);
                this.listNodeDataSource.handleEvent(Event.DRAG, c24);
                this.listNodeDataSource.setIsInnerDrag(false);
                this.listNodeDataSource.notifyDataReload();
                this.listNodeDataSource.listNode[c24].fontColor = this.treeViewTheme.primaryTitleActiveFontColor;
                if (this.viewLastIndex !== -1 && s23 !== this.viewLastIndex) {
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
                            'moduleName': '__harDefaultModuleName__',
                        });
                }
                this.listNodeDataSource.lastIndex = c24;
                let d24 = v23?.getNodeParentNodeId();
                this.listNodeDataSource.judgeImageCollapse(d24);
                let e24 = ({
                    type: 'requestFocusForAccessibility',
                    bundleName: getContext()?.abilityInfo?.bundleName,
                    triggerAction: 'common',
                    customId: `treeView_node${x23}`
                });
                accessibility.sendAccessibilityEvent(e24).then(() => {
                    setTimeout(() => {
                        this.accessibilityNodeType = AccessibilityNodeType.TEXT;
                    }, ENTER_EXIT_DURATION);
                    console.log(`test123 Succeeded in send event, eventInfo is ${JSON.stringify(e24)}`);
                });
            });
        }, List);
        {
            const i22 = l22 => {
                const m22 = l22;
                {
                    const n22 = (w22, x22) => {
                        ListItem.create(() => {
                        }, false);
                        ListItem.width('100%');
                        ListItem.height(m22.getListItemHeight());
                        ListItem.padding({
                            start: LengthMetrics.resource(this.itemPadding.left),
                            end: LengthMetrics.resource(this.itemPadding.right)
                        });
                        ListItem.align(Alignment.Start);
                        ListItem.onDragStart((y22, z22) => {
                            this.accessibilityNodeType = AccessibilityNodeType.LIFT;
                            if (this.listNodeDataSource.getIsDrag() || this.listNodeDataSource.getIsInnerDrag() ||
                            this.isMultiPress) {
                                hilog.error(LOG_CODE, TAG, 'drag error, a item has been dragged');
                                return;
                            }
                            this.dropSelectedIndex = JSON.parse(z22).selectedIndex;
                            let a23 = JSON.parse(z22).selectedIndex;
                            let b23 = this.listNodeDataSource.getData(a23);
                            let c23 = m22.getNodeCurrentNodeId();
                            if (a23 >= this.listNodeDataSource.totalCount() || a23 === undefined) {
                                hilog.error(LOG_CODE, TAG, 'drag error, currentNodeIndex is not found in onDragStart');
                                return;
                            }
                            this.listNodeDataSource.setIsInnerDrag(true);
                            this.listNodeDataSource.setIsDrag(true);
                            this.listNodeDataSource.setCurrentNodeInfo(b23);
                            this.listNodeDataSource.setDraggingCurrentNodeId(b23?.getNodeCurrentNodeId());
                            this.listNodeDataSource.setDraggingParentNodeId(b23?.getNodeParentNodeId());
                            let d23 = DRAG_OPACITY;
                            this.listNodeDataSource.setListItemOpacity(d23);
                            this.listNodeDataSource.notifyDataChange(a23);
                            if (c23 !== b23?.getNodeCurrentNodeId()) {
                                hilog.error(LOG_CODE, TAG, 'drag is too fast, it attribute a fault to OH');
                                this.listNodeDataSource.setIsDrag(false);
                                return;
                            }
                            let e23 = b23.getNodeInfoData()?.primaryTitle === undefined ? '' :
                                b23.getNodeInfoData()?.primaryTitle;
                            let f23 = b23.getNodeInfoData()?.secondaryTitle === undefined ? '' :
                                b23.getNodeInfoData()?.secondaryTitle;
                            let g23 = this.listNodeDataSource.getAccessibleTitleText(e23);
                            let h23 = this.listNodeDataSource.getAccessibleTitleText(f23);
                            let i23 = `${g23}, ${h23}`;
                            this.listNodeDataSource.sendAccessibility(this.listNodeDataSource.getStringByName('treeview_accessibility_lift_node',
                                i23));
                            let j23 = [];
                            for (let l23 = 0; l23 < this.listNodeDataSource.listNode.length; l23++) {
                                if (this.listNodeDataSource.listNode[l23].getNodeParentNodeId() === -1) {
                                    j23.push(this.listNodeDataSource.listNode[l23].getNodeCurrentNodeId());
                                }
                            }
                            this.allParentNode = j23;
                            let k23 = ({
                                type: 'requestFocusForAccessibility',
                                bundleName: getContext()?.abilityInfo?.bundleName,
                                triggerAction: 'common',
                                customId: `treeView_node_lift${c23}`
                            });
                            accessibility.sendAccessibilityEvent(k23).then(() => {
                                setTimeout(() => {
                                    this.accessibilityNodeType = AccessibilityNodeType.TEXT;
                                }, ENTER_EXIT_DURATION);
                            });
                            return {
                                builder: () => {
                                    this.draggingPopup.call(this, b23);
                                }
                            };
                        });
                    };
                    const o22 = () => {
                        this.observeComponentCreation2(n22, ListItem);
                        this.observeComponentCreation2((t22, u22) => {
                            Row.create();
                            Row.onTouch(this.isAccessibilityEnabled ? undefined : (v22) => {
                                this.touchInner(m22, v22);
                            });
                        }, Row);
                        {
                            this.observeComponentCreation2((p22, q22) => {
                                if (q22) {
                                    let r22 = new TreeViewInner(this, {
                                        item: m22,
                                        listNodeDataSource: this.listNodeDataSource,
                                        index: this.listNodeDataSource.findIndex(m22.getNodeCurrentNodeId()),
                                        listTreeViewMenu: this.listTreeViewMenu,
                                        callBackClick: () => this.clickInner(m22),
                                    }, undefined, p22, () => {
                                    }, {
                                        page: 'library/src/main/ets/components/back/MainPage.ets',
                                        line: 1299,
                                        col: 13
                                    });
                                    ViewPU.create(r22);
                                    let s22 = () => {
                                        return {
                                            item: m22,
                                            listNodeDataSource: this.listNodeDataSource,
                                            index: this.listNodeDataSource.findIndex(m22.getNodeCurrentNodeId()),
                                            listTreeViewMenu: this.listTreeViewMenu,
                                            callBackClick: () => this.clickInner(m22)
                                        };
                                    };
                                    r22.paramsGenerator_ = s22;
                                } else {
                                    this.updateStateVarsOfChildByElmtId(p22, {
                                        item: m22
                                    });
                                }
                            }, { name: 'TreeViewInner' });
                        }
                        Row.pop();
                        ListItem.pop();
                    };
                    o22();
                }
            };
            const j22 = (k22) => JSON.stringify(k22);
            LazyForEach.create('1', this, this.listNodeDataSource, i22, j22);
            LazyForEach.pop();
        }
        List.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export class TreeController {
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
        let h22 = this.listNodeDataSource.getClickNodeId();
        return this.listNodeDataSource.getClickNodeChildrenInfo(h22);
    }

    getChildrenId() {
        let g22 = this.listNodeDataSource.getClickNodeId();
        return this.listNodeDataSource.getClickChildId(g22);
    }

    removeNode() {
        let d22 = this.listNodeDataSource.getClickNodeId();
        if (d22 < 0) {
            return;
        }
        let e22 = this.listNodeDataSource.findParentNodeId(d22);
        let f22 = this.listNodeDataSource.removeNode(d22, e22);
        this.listNodeDataSource.refreshData(MenuOperation.REMOVE_NODE, e22, f22);
        this.nodeIdList.splice(this.nodeIdList.indexOf(d22), 1);
        this.listNodeDataSource.lastIndex = -1;
    }

    modifyNode() {
        let c22 = this.listNodeDataSource.getClickNodeId();
        this.listNodeDataSource.setItemVisibilityOnEdit(c22, MenuOperation.MODIFY_NODE);
    }

    add(w21) {
        let x21 = this.listNodeDataSource.getClickNodeId();
        if (x21 === this.listNodeDataSource.ROOT_NODE_ID || !this.listNodeDataSource.getIsFolder(x21)) {
            return;
        }
        let y21 = this.listNodeDataSource.getNewNodeParam(x21);
        this.nodeIdList.push(this.nodeIdList[this.nodeIdList.length - 1] + 1);
        let z21 = this.nodeIdList[this.nodeIdList.length - 1];
        let a22 = this.listNodeDataSource.addNode(x21, z21, {
            isFolder: y21.isFolder,
            icon: y21.icon,
            symbolIconStyle: y21.symbolIconStyle,
            selectedIcon: y21.selectedIcon,
            symbolSelectedIconStyle: y21.symbolSelectedIconStyle,
            editIcon: y21.editIcon,
            symbolEditIconStyle: y21.symbolEditIconStyle,
            primaryTitle: '新建文件夹',
            container: y21.container,
            secondaryTitle: y21.secondaryTitle,
        }, w21);
        if (!a22) {
            return;
        }
        this.listNodeDataSource.refreshData(MenuOperation.ADD_NODE, x21, [z21]);
        this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false,
            this.listNodeDataSource.getLastIndex());
        this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(),
            MenuOperation.COMMIT_NODE);
        this.listNodeDataSource.listNode[this.listNodeDataSource.getLastIndex()]
            .setFontColor(this.treeViewTheme.primaryTitleFontColor);
        let b22 = this.listNodeDataSource.findIndex(z21);
        this.listNodeDataSource.setClickIndex(b22);
        this.listNodeDataSource.handleEvent(Event.TOUCH_UP, b22);
    }

    addNode(s21) {
        if (s21 === undefined) {
            this.add(this.initBuild);
            return this;
        } else {
            for (let v21 = 0; v21 < this.nodeIdList.length; v21++) {
                if (s21.currentNodeId === this.nodeIdList[v21].valueOf()) {
                    throw new Error('ListTreeNode[addNode]: ' +
                        'The parameters of the new node cannot contain the same currentNodeId.');
                    return this;
                }
            }
            let t21 = false;
            if (s21.primaryTitle !== undefined &&
                !this.listNodeDataSource.checkMainTitleIsValid(s21.primaryTitle.toString())) {
                throw new Error('ListTreeNode[addNode]: ' +
                    'The directory name cannot contain the following characters\ /: *? " < > | or exceeds the maximum length.');
                return this;
            }
            if (s21.primaryTitle === null && s21.icon === null && s21.symbolIconStyle === null) {
                throw new Error('ListTreeNode[addNode]: ' +
                    'The icon|symbolIconStyle and directory name cannot be empty at the same time.');
                return this;
            }
            if (s21.currentNodeId === this.ROOT_NODE_ID || s21.currentNodeId === null) {
                throw new Error('ListTreeNode[addNode]: currentNodeId can not be -1 or null.');
                return this;
            }
            if (s21.currentNodeId !== undefined) {
                this.nodeIdList.push(s21.currentNodeId);
            }
            if (s21.parentNodeId !== undefined) {
                if (s21.currentNodeId !== undefined) {
                    t21 =
                        this.listNodeDataSource.addNode(s21.parentNodeId, s21.currentNodeId, s21, this.initBuild);
                }
            }
            if (!t21) {
                return this;
            }
            if (!this.initBuild && s21.parentNodeId !== undefined) {
                let u21 = this.nodeIdList[this.nodeIdList.length - 1];
                this.listNodeDataSource.refreshData(MenuOperation.ADD_NODE, s21.parentNodeId, [u21]);
            }
            return this;
        }
    }

    refreshNode(p21, q21, r21) {
        this.listNodeDataSource.setNodeSubtitlePara(p21, q21, r21);
    }

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

    getData(o21) {
        return undefined;
    }

    registerDataChangeListener(n21) {
        if (this.listeners.indexOf(n21) < 0) {
            this.listeners.push(n21);
        }
    }

    unregisterDataChangeListener(l21) {
        const m21 = this.listeners.indexOf(l21);
        if (m21 >= 0) {
            this.listeners.splice(m21, 1);
        }
    }

    notifyDataReload() {
        this.listeners.forEach(k21 => {
            k21.onDataReloaded();
        });
    }

    notifyDataAdd(i21) {
        this.listeners.forEach(j21 => {
            j21.onDataAdd(i21);
        });
    }

    notifyDataChange(g21) {
        if (g21 === undefined) {
            return;
        }
        this.listeners.forEach(h21 => {
            h21.onDataChange(g21);
        });
    }

    notifyDataDelete(e21) {
        this.listeners.forEach(f21 => {
            f21.onDataDelete(e21);
        });
    }

    notifyDataMove(b21, c21) {
        this.listeners.forEach(d21 => {
            d21.onDataMove(b21, c21);
        });
    }
}

function delayUpdateParentChildNum(v20, w20, x20, y20) {
    let z20 = setTimeout(() => {
        y20.forEach((a21) => {
            updateParentChildNumHandler(a21, x20, v20, w20);
        });
        clearTimeout(z20);
    }, DELAY_TIME);
}

function updateParentChildNumHandler(p20, q20, r20, s20) {
    let t20 = p20;
    while (t20 >= 0) {
        if (q20.has(t20)) {
            let u20 = q20.get(t20);
            u20.getChildNodeInfo().allChildNum =
                r20 ? u20.getChildNodeInfo().allChildNum + s20 : u20.getChildNodeInfo().allChildNum - s20;
            t20 = u20.parentNodeId;
        } else {
            hilog.error(LOG_CODE, TAG, 'updateParentChildNumHandler: parent node not found');
            break;
        }
    }
}

function delaySortNodeIdList(l20) {
    let m20 = setTimeout(() => {
        l20.sort((n20, o20) => n20 - o20);
        clearTimeout(m20);
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
        this.appEventBus = TreeListenerManager.getInstance().getTreeListener();
        this.isInnerDrag = false;
        this.isDrag = false;
        this.draggingCurrentNodeId = this.INITIAL_INVALID_VALUE;
        this.draggingParentNodeId = this.INITIAL_INVALID_VALUE;
        this.currentNodeInfo = null;
        this.listItemOpacity = 1;
        this.lastPassIndex = this.INITIAL_INVALID_VALUE;
        this.lastPassId = this.INITIAL_INVALID_VALUE;
        this.thisPassIndex = this.INITIAL_INVALID_VALUE;
        this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE;
        this.timeoutExpandId = this.INITIAL_INVALID_VALUE;
        this.lastTimeoutExpandId = this.INITIAL_INVALID_VALUE;
        this.clearTimeoutExpandId = this.INITIAL_INVALID_VALUE;
        this.timeoutHighLightId = this.INITIAL_INVALID_VALUE;
        this.lastTimeoutHighLightId = this.INITIAL_INVALID_VALUE;
        this.clearTimeoutHighLightId = this.INITIAL_INVALID_VALUE;
        this.lastDelayHighLightIndex = this.INITIAL_INVALID_VALUE;
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
                'moduleName': '__harDefaultModuleName__',
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
                    'moduleName': '__harDefaultModuleName__',
                },
                right: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.padding_level4'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                }
            },
            backgroundColor: COLOR_IMAGE_EDIT,
            height: GRAG_POP_UP_HEIGHT,
            shadow: {
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_default_shadow_m'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                },
                color: {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_dialog_bg'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                },
                offsetX: 0,
                offsetY: 0,
            },
            borderRadius: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_corner_radius_default_s'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            },
            fontColor: this.treeViewTheme.primaryTitleFontColor,
            fontSize: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_body1'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            },
            fontWeight: FontWeight.Regular,
            imageOpacity: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_alpha_content_fourth'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            }
        };
        this.subTitle = {
            normalFontColor: this.treeViewTheme.secondaryTitleFontColor,
            highLightFontColor: {
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_primary_contrary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            },
            fontSize: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_body2'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            },
            fontWeight: FontWeight.Regular,
            margin: {
                left: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.padding_level2'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                },
                right: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.padding_level12'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                }
            }
        };
        this._root.nodeLevel = -1;
        this.nodeIdNodeItemMap.set(-1, this._root);
        this.nodeIdNodeParamMap.set(-1, emptyNodeInfo);
    }

    checkIndex(k20) {
        if (k20 < 0 || k20 >= this.listNode.length) {
            hilog.error(LOG_CODE, TAG, 'check index fail');
            return false;
        }
        return true;
    }

    changeNodeColor(i20, j20) {
        if (!this.checkIndex(i20)) {
            return;
        }
        this.listNode[i20].setNodeColor(j20);
        this.listNode[i20].setNodeBorder(false);
    }

    getNodeColor(h20) {
        return this.listNode[h20].getNodeColor();
    }

    handleFocusEffect(f20, g20) {
        if (this.listNode[f20].getNodeIsShow()) {
            this.listNode[f20].setNodeBorder(g20);
        }
    }

    setImageSource(c20, d20) {
        if (!this.checkIndex(c20)) {
            return;
        }
        let e20 = this.listNode[c20];
        e20.setIsSelected(d20 === InteractionStatus.SELECTED ||
            d20 === InteractionStatus.EDIT || d20 === InteractionStatus.FINISH_EDIT);
        if (e20.getNodeItem().mainTitleNode !== null && d20 !== InteractionStatus.DRAG_INSERT &&
            d20 !== InteractionStatus.FINISH_DRAG_INSERT) {
            e20.getNodeItem().mainTitleNode?.setMainTitleSelected(d20 === InteractionStatus.SELECTED ||
                d20 === InteractionStatus.FINISH_EDIT);
        }
        if (e20.getNodeItem().imageNode !== null) {
            e20.getNodeItem().imageNode?.setImageSource(d20);
        }
    }

    setImageCollapseSource(z19, a20) {
        let b20 = this.listNode[z19];
        if (b20.getNodeItem().imageCollapse !== undefined) {
            b20.getNodeItem().imageCollapse = CollapseImageNodeFlyweightFactory.getCollapseImageNode(a20,
                this.expandAndCollapseInfo.get(b20.getNodeCurrentNodeId()), b20.getNodeItem().imageCollapse?.type);
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
        let x19 = 0;
        this.loadedNodeIdAndIndexMap.clear();
        this.nodeIdAndNodeIndexMap.clear();
        this.loadedListNode.splice(0, this.loadedListNode.length);
        for (let y19 = 0; y19 < this.listNode.length; y19++) {
            this.nodeIdAndNodeIndexMap.set(this.listNode[y19].getNodeCurrentNodeId(), y19);
            if (this.listNode[y19].getNodeIsShow()) {
                this.loadedNodeIdAndIndexMap.set(this.listNode[y19].getNodeCurrentNodeId(), x19++);
                this.loadedListNode.push(this.listNode[y19]);
            }
        }
    }

    changeNodeStatus(u19) {
        if (u19 >= this.listNode.length) {
            hilog.error(LOG_CODE, TAG, 'changeNodeStatus clickIndex error.');
            return;
        }
        let v19 = u19;
        let w19 = this.listNode[u19].getNodeCurrentNodeId();
        if (this.expandAndCollapseInfo.get(w19) === NodeStatus.EXPAND) {
            this.expandAndCollapseInfo.set(w19, NodeStatus.COLLAPSE);
            this.listNode[v19].getNodeItem()
                .imageCollapse = CollapseImageNodeFlyweightFactory.changeImageCollapseSource(NodeStatus.COLLAPSE,
                this.listNode[v19].getNodeItem().imageCollapse?.isCollapse);
        } else if (this.expandAndCollapseInfo.get(w19) === NodeStatus.COLLAPSE) {
            this.expandAndCollapseInfo.set(w19, NodeStatus.EXPAND);
            this.listNode[v19].getNodeItem()
                .imageCollapse = CollapseImageNodeFlyweightFactory.changeImageCollapseSource(NodeStatus.EXPAND,
                this.listNode[v19].getNodeItem().imageCollapse?.isCollapse);
        }
    }

    handleExpandAndCollapse(k19, l19) {
        if (k19 >= this.listNode.length) {
            hilog.error(LOG_CODE, TAG, 'handleExpandAndCollapse clickIndex error.');
            return;
        }
        let m19 = k19;
        let n19 = this.listNode[m19].getNodeCurrentNodeId();
        if (!this.expandAndCollapseInfo.has(n19)) {
            return;
        }
        let o19 = this.expandAndCollapseInfo.get(n19);
        if (this.listNode[m19].getChildNodeInfo().isHasChildNode && o19 === NodeStatus.COLLAPSE) {
            for (let t19 = 0; t19 < this.listNode[m19].getChildNodeInfo().allChildNum; t19++) {
                if (this.listNode[m19 + 1 + t19] === undefined) {
                    return;
                }
                this.listNode[m19 + 1 + t19].setNodeIsShow(false);
                this.listNode[m19 + 1 + t19].setListItemHeight(LIST_ITEM_HEIGHT_NONE);
            }
            this.loadedListNodeFunction();
            this.notifyDataReload();
            return;
        }
        let p19 = new Array(this.listNode[m19].getChildNodeInfo().childNum);
        p19[0] = m19 + 1;
        let q19 = 1;
        while (q19 < this.listNode[m19].getChildNodeInfo().childNum) {
            p19[q19] = p19[q19 - 1] + this.listNode[p19[q19 - 1]].getChildNodeInfo().allChildNum + 1;
            q19++;
        }
        if (o19 === NodeStatus.EXPAND) {
            for (let r19 = 0; r19 < p19.length; r19++) {
                if (this.listNode[p19[r19]] === undefined) {
                    return;
                }
                this.listNode[p19[r19]].setNodeIsShow(true);
                this.listNode[p19[r19]].setListItemHeight(LIST_ITEM_HEIGHT);
                let s19 = this.listNode[p19[r19]].getNodeCurrentNodeId();
                if (this.expandAndCollapseInfo.get(s19) === NodeStatus.EXPAND) {
                    this.handleExpandAndCollapse(p19[r19], false);
                }
            }
        }
        p19 = null;
        if (l19) {
            this.loadedListNodeFunction();
            this.notifyDataReload();
        }
    }

    updateAllChildNum() {
        delayUpdateParentChildNum(true, 1, this.nodeIdNodeItemMap, this.updateNodeIdList);
    }

    resetData(j19) {
        j19.splice(0, j19.length);
        this.loadedNodeIdAndIndexMap.clear();
        this.loadedListNode.splice(0, this.loadedListNode.length);
        this.nodeIdAndNodeIndexMap.clear();
        this.nodeIdAndSubtitleMap.clear();
    }

    initHandler(b19, c19, d19) {
        let e19 = 0;
        let f19 = 0;
        this.resetData(b19);
        try {
            this.traverseSectionNodeDF((h19) => {
                if (h19.getCurrentNodeId() >= 0 && this.nodeIdNodeParamMap.has(h19.getCurrentNodeId())) {
                    let i19 = new NodeInfo(h19, this.nodeIdNodeParamMap.get(h19.getCurrentNodeId()));
                    i19.addImageCollapse(h19.getChildNodeInfo().isHasChildNode);
                    b19.push(i19);
                    this.nodeIdAndNodeIndexMap.set(i19.getNodeCurrentNodeId(), f19++);
                    e19 = this.nodeDFHandler(i19, e19);
                }
                return false;
            }, this._root, c19, d19);
        } catch (g19) {
            hilog.error(LOG_CODE, TAG, 'traverseSectionNodeDF function callbacks error.');
            this.resetData(b19);
        }
    }

    nodeDFHandler(z18, a19) {
        if (z18.getChildNodeInfo().isHasChildNode) {
            this.expandAndCollapseInfo.set(z18.getNodeCurrentNodeId(), NodeStatus.COLLAPSE);
        }
        if (z18.getNodeIsShow()) {
            this.loadedNodeIdAndIndexMap.set(z18.getNodeCurrentNodeId(), a19++);
            this.loadedListNode.push(z18);
        }
        if (z18.getIsFolder()) {
            if (z18.getNodeInfoData().secondaryTitle !== undefined) {
                this.nodeIdAndSubtitleMap.set(z18.getNodeCurrentNodeId(), z18.getNodeInfoData().secondaryTitle);
            } else {
                this.nodeIdAndSubtitleMap.set(z18.getNodeCurrentNodeId(), '');
            }
        }
        return a19;
    }

    delayInit() {
        let v18 = setTimeout(() => {
            let w18 = [];
            this.initHandler(w18, 0);
            this.listNode.splice(0, this.listNode.length);
            this.listNode.push(...w18);
            this.listNode.forEach((x18, y18) => {
                this.notifyDataDelete(y18);
                this.notifyDataAdd(y18);
            });
            clearTimeout(v18);
        }, DELAY_TIME);
    }

    initSection() {
        this.initHandler(this.listNode, 0, 1);
    }

    setClickIndex(u18) {
        this.thisIndex = u18;
    }

    getClickNodeId() {
        if (!this.checkIndex(this.thisIndex)) {
            return -1;
        }
        return this.listNode[this.thisIndex].getNodeCurrentNodeId();
    }

    expandAndCollapseNode(t18) {
        this.changeNodeStatus(t18);
        this.handleExpandAndCollapse(t18, true);
    }

    getIsTouchDown() {
        return this.isTouchDown;
    }

    getLastIndex() {
        return this.lastIndex;
    }

    findIndex(r18) {
        let s18 = -1;
        if (this.nodeIdAndNodeIndexMap.has(r18)) {
            s18 = this.nodeIdAndNodeIndexMap.get(r18);
        }
        return s18;
    }

    handleEventDrag(q18) {
        if (!this.checkIndex(q18)) {
            return;
        }
        this.setImageSource(q18, InteractionStatus.NORMAL);
        this.changeNodeColor(q18, this.listNode[q18].getNodeStatus().normal);
        this.handleFocusEffect(q18, false);
        this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.listNode[q18].getNodeCurrentNodeId()));
    }

    handleEvent(o18, p18) {
        if (this.isDrag) {
            return;
        }
        if (!this.checkIndex(p18)) {
            return;
        }
        if (o18 === Event.TOUCH_DOWN || o18 === Event.TOUCH_UP || o18 === Event.MOUSE_BUTTON_RIGHT) {
            if (p18 !== this.lastIndex) {
                this.clearLastIndexStatus();
            }
        }
        this.eventHandler(p18, o18);
    }

    eventHandler(k18, l18) {
        let m18 = this.loadedNodeIdAndIndexMap.get(this.listNode[k18].getNodeCurrentNodeId());
        switch (l18) {
            case Event.TOUCH_DOWN:
                this.isTouchDown = true;
                this.changeNodeColor(k18, this.listNode[k18].getNodeStatus().press);
                this.notifyDataChange(m18);
                break;
            case Event.TOUCH_UP: {
                this.touchUpHandler(k18, m18);
                break;
            }
            case Event.HOVER:
                if (this.getNodeColor(k18) !== this.listNode[k18].getNodeStatus().selected) {
                    this.changeNodeColor(k18, this.listNode[k18].getNodeStatus().hover);
                    this.notifyDataChange(m18);
                }
                break;
            case Event.HOVER_OVER:
                if (this.getNodeColor(k18) !== this.listNode[k18].getNodeStatus().selected) {
                    this.changeNodeColor(k18, this.listNode[k18].getNodeStatus().normal);
                    this.notifyDataChange(m18);
                }
                break;
            case Event.FOCUS:
                this.handleFocusEffect(k18, true);
                this.notifyDataChange(m18);
                break;
            case Event.BLUR:
                this.handleFocusEffect(k18, false);
                this.notifyDataChange(m18);
                break;
            case Event.MOUSE_BUTTON_RIGHT:
                this.lastIndex = k18;
                this.finishEditing();
                break;
            case Event.DRAG:
                this.isTouchDown = false;
                let n18 = this.listNode[k18];
                this.setImageSource(k18, InteractionStatus.SELECTED);
                this.lastIndex = k18;
                this.changeNodeColor(k18, n18.getNodeStatus().selected);
                this.notifyDataChange(m18);
                break;
            default:
                break;
        }
    }

    touchUpHandler(h18, i18) {
        if (this.isInnerDrag) {
            this.isInnerDrag = false;
        }
        this.isTouchDown = false;
        let j18 = this.listNode[h18];
        this.setImageSource(h18, InteractionStatus.SELECTED);
        j18.setFontColor(this.treeViewTheme.primaryTitleFontColor);
        this.lastIndex = h18;
        this.changeNodeColor(h18, j18.getNodeStatus().selected);
        this.notifyDataChange(i18);
    }

    notificationNodeInfo(y17, z17) {
        if (z17 === MenuOperation.MODIFY_NODE) {
            let f18 = this.listNode[this.modifyNodeIndex];
            let g18 = {
                currentNodeId: f18?.getNodeCurrentNodeId(),
                parentNodeId: f18?.getNodeParentNodeId(),
            };
            this.appEventBus.emit(TreeListenType.NODE_MODIFY, g18);
        } else if (z17 === MenuOperation.ADD_NODE) {
            let a18 = this.listNode[y17];
            if (a18 === undefined) {
                return;
            }
            let b18 = (a18.getNodeItem().imageNode !== undefined) ?
                a18.getNodeItem().imageNode?.source : undefined;
            let c18 = (a18.getNodeItem().imageNode !== undefined) ?
                a18.getNodeItem().imageNode?.selectedSource : undefined;
            let d18 = (a18.getNodeItem().imageNode !== undefined) ?
                a18.getNodeItem().imageNode?.editSource : undefined;
            let e18 = {
                currentNodeId: a18?.getNodeCurrentNodeId(),
                parentNodeId: a18?.getNodeParentNodeId(),
            };
            this.appEventBus.emit(TreeListenType.NODE_ADD, e18);
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

    setItemVisibilityOnEdit(s17, t17) {
        let u17 = -1;
        if (s17 === -1) {
            return;
        }
        if (t17 === MenuOperation.MODIFY_NODE) {
            for (let x17 = 0; x17 < this.listNode.length; x17++) {
                if (this.listNode[x17]?.getNodeCurrentNodeId() === s17) {
                    u17 = x17;
                    break;
                }
            }
            let w17 = this.listNode[u17];
            if (w17 === undefined) {
                return;
            }
            w17.setIsModify(true);
            if (w17.getNodeItem().mainTitleNode === null) {
                return;
            }
            this.currentOperation = MenuOperation.MODIFY_NODE;
            w17.setTitleAndInputTextStatus(true);
            this.setImageSource(u17, InteractionStatus.EDIT);
            this.setImageCollapseSource(u17, InteractionStatus.EDIT);
            this.modifyNodeIndex = u17;
            if (w17.getNodeItem().inputText) {
                if (w17.getNodeItem().imageCollapse !== null) {
                    w17.getNodeItem().inputText.rightMargin = {
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.ohos_id_text_paragraph_margin_xs'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__',
                    };
                } else {
                    w17.getNodeItem().inputText.rightMargin = {
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.ohos_id_elements_margin_horizontal_m'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__',
                    };
                }
            }
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(s17));
        }
        u17 = s17;
        if (t17 === MenuOperation.COMMIT_NODE) {
            let v17 = this.listNode[u17];
            if (v17 === undefined) {
                return;
            }
            v17.setTitleAndInputTextStatus(false);
            v17.setIsModify(false);
            this.setImageSource(u17, InteractionStatus.FINISH_EDIT);
            this.setImageCollapseSource(u17, InteractionStatus.FINISH_EDIT);
            this.notificationNodeInfo(this.modifyNodeIndex, this.currentOperation);
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(v17?.getNodeCurrentNodeId()));
        }
    }

    setPopUpInfo(m17, n17, o17, p17) {
        if (!this.checkIndex(p17)) {
            return;
        }
        let q17 = this.listNode[p17];
        if (q17 === undefined) {
            return;
        }
        q17.setPopUpIsShow(o17);
        let r17 = this.loadedNodeIdAndIndexMap.get(q17.getNodeCurrentNodeId());
        if (!o17) {
            this.notifyDataChange(r17);
            return;
        }
        if (m17 === PopUpType.HINTS) {
            if (q17.getNodeItem().mainTitleNode !== null) {
                q17.setPopUpText(q17.getNodeItem().mainTitleNode?.title);
            } else {
                q17.setPopUpText('');
                q17.setPopUpIsShow(false);
            }
            q17.setPopUpEnableArrow(false);
            q17.setPopUpColor({
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_background'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            });
            q17.setPopUpTextColor(this.treeViewTheme.secondaryTitleFontColor);
        } else if (m17 === PopUpType.WARNINGS) {
            if (q17.getNodeItem().inputText !== null) {
                if (n17 === InputError.INVALID_ERROR) {
                    q17.setPopUpText('invalid error');
                } else if (n17 === InputError.LENGTH_ERROR) {
                    q17.setPopUpText('length error');
                }
                q17.setPopUpEnableArrow(true);
                q17.setPopUpColor({
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_help_tip_bg'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                });
                q17.setPopUpTextColor({
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_text_hint_contrary'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                });
            }
        }
        this.notifyDataChange(r17);
    }

    setShowPopUpTimeout(j17, k17) {
        if (!this.checkIndex(k17)) {
            return;
        }
        if (this.listNode[k17].getNodeItem().mainTitleNode !== null) {
            this.listNode[k17].getNodeItem().mainTitleNode.popUpTimeout = j17;
        }
        let l17 = this.loadedNodeIdAndIndexMap.get(this.listNode[k17].getNodeCurrentNodeId());
        this.notifyDataChange(l17);
    }

    setMainTitleNameOnEdit(h17, i17) {
        this.modifyNodeIndex = h17;
        if (this.listNode[h17].getNodeItem().mainTitleNode !== null) {
            this.listNode[h17].getNodeItem().mainTitleNode.title = i17;
        }
    }

    totalCount() {
        return this.loadedNodeIdAndIndexMap.size;
    }

    getData(g17) {
        if (g17 < 0 || g17 >= this.loadedListNode.length) {
            return undefined;
        }
        return this.loadedListNode[g17];
    }

    addData(e17, f17) {
        if (!this.checkIndex(e17)) {
            return;
        }
        this.listNode.splice(e17, 0, f17);
        this.nodeIdAndNodeIndexMap.set(f17.getNodeCurrentNodeId(), e17);
        this.loadedListNodeFunction();
        this.notifyDataAdd(e17);
    }

    pushData(d17) {
        this.listNode.push(d17);
        this.nodeIdAndNodeIndexMap.set(d17.getNodeCurrentNodeId(), this.listNode.length);
        this.loadedListNodeFunction();
        this.notifyDataAdd(this.listNode.length - 1);
    }

    setIsInnerDrag(c17) {
        this.isInnerDrag = c17;
    }

    getIsInnerDrag() {
        return this.isInnerDrag;
    }

    setIsDrag(b17) {
        this.isDrag = b17;
    }

    getIsDrag() {
        return this.isDrag;
    }

    setCurrentNodeInfo(a17) {
        if (a17 === undefined) {
            return;
        }
        this.currentNodeInfo = a17;
    }

    getCurrentNodeInfo() {
        return this.currentNodeInfo;
    }

    setDraggingParentNodeId(z16) {
        if (z16 === undefined) {
            return;
        }
        this.draggingParentNodeId = z16;
    }

    getDraggingParentNodeId() {
        return this.draggingParentNodeId;
    }

    getDraggingCurrentNodeId() {
        return this.draggingCurrentNodeId;
    }

    setDraggingCurrentNodeId(y16) {
        if (y16 === undefined) {
            return;
        }
        this.draggingCurrentNodeId = y16;
    }

    setListItemOpacity(x16) {
        this.listItemOpacity = x16;
    }

    getListItemOpacity(w16) {
        return w16.getNodeCurrentNodeId() === this.getDraggingCurrentNodeId() ? this.listItemOpacity : 1;
    }

    getDragPopupPara() {
        return this.DRAG_POPUP;
    }

    setLastPassIndex(v16) {
        this.lastPassIndex = v16;
    }

    getLastPassIndex() {
        return this.lastPassIndex;
    }

    getIsParentOfInsertNode(r16) {
        if (this.currentNodeInfo === null || r16 === undefined) {
            return false;
        }
        let s16 = this.currentNodeInfo.getNodeInfoNode();
        let t16 = s16.currentNodeId;
        let u16 = this.nodeIdNodeItemMap.get(r16)?.parentNodeId;
        while (u16 !== undefined && u16 !== -1) {
            if (t16 === u16) {
                return true;
            } else {
                u16 = this.nodeIdNodeItemMap.get(u16)?.parentNodeId;
            }
        }
        return false;
    }

    setPassIndex(q16) {
        this.thisPassIndex = q16;
    }

    getPassIndex() {
        return this.thisPassIndex;
    }

    clearTimeOutAboutDelayHighLightAndExpand(m16) {
        if (this.lastPassId !== this.INITIAL_INVALID_VALUE && this.loadedNodeIdAndIndexMap.has(this.lastPassId)) {
            let o16 = this.loadedNodeIdAndIndexMap.get(this.lastPassId);
            this.listNode.forEach((p16) => {
                if (p16.getNodeCurrentNodeId() === this.lastPassId) {
                    p16.setCanShowFlagLine(false);
                    return;
                }
            });
            this.notifyDataChange(o16);
        }
        if ((this.lastTimeoutHighLightId !== this.INITIAL_INVALID_VALUE &&
            this.clearTimeoutHighLightId !== this.lastTimeoutHighLightId)) {
            clearTimeout(this.lastTimeoutHighLightId);
            if (this.lastDelayHighLightIndex !== this.INITIAL_INVALID_VALUE) {
                this.clearHighLight(this.lastDelayHighLightIndex);
                let n16 = this.loadedNodeIdAndIndexMap
                    .get(this.listNode[this.lastDelayHighLightIndex].getNodeCurrentNodeId());
                this.notifyDataChange(n16);
            }
            this.clearTimeoutHighLightId = this.lastTimeoutHighLightId;
        }
        this.lastTimeoutHighLightId = this.timeoutHighLightId;
        this.lastDelayHighLightIndex = m16;
        if ((this.lastTimeoutExpandId !== this.INITIAL_INVALID_VALUE &&
            this.clearTimeoutExpandId !== this.lastTimeoutExpandId)) {
            clearTimeout(this.lastTimeoutExpandId);
            this.clearTimeoutExpandId = this.lastTimeoutExpandId;
        }
        this.lastTimeoutExpandId = this.timeoutExpandId;
        this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE;
    }

    clearHighLight(l16) {
        if (!this.checkIndex(l16)) {
            return;
        }
        this.changeNodeColor(l16, this.listNode[l16].getNodeStatus().normal);
        this.changeNodeHighLightColor(l16, false);
        this.setImageSource(l16, InteractionStatus.FINISH_DRAG_INSERT);
        this.setImageCollapseSource(l16, InteractionStatus.FINISH_DRAG_INSERT);
        this.listNode[l16].setIsHighLight(false);
    }

    changeNodeHighLightColor(j16, k16) {
        if (this.listNode[j16].getNodeItem().mainTitleNode && this.listNode[j16].getIsShowTitle()) {
            this.listNode[j16].getNodeItem().mainTitleNode?.setMainTitleHighLight(k16);
        }
    }

    getAccessibleTitle(b16) {
        let c16 = [];
        while (b16 !== -1) {
            if (b16 === undefined) {
                return '';
            }
            let d16 = this.findParentNodeId(b16);
            let e16 = this.nodeIdNodeItemMap.get(d16);
            if (e16 === undefined || d16 === undefined) {
                return '';
            }
            let f16 = this.getNodeInfoByNodeItem(e16).getNodeInfoData()?.primaryTitle === undefined
                ? '' : this.getNodeInfoByNodeItem(e16).getNodeInfoData().primaryTitle;
            let g16 = this.getNodeInfoByNodeItem(e16).getNodeInfoData()?.secondaryTitle === undefined
                ? '' : this.getNodeInfoByNodeItem(e16).getNodeInfoData().secondaryTitle;
            let h16 = this.getAccessibleTitleText(f16);
            let i16 = this.getAccessibleTitleText(g16);
            c16.unshift(`${h16}, ${i16}`);
            b16 = e16.currentNodeId;
        }
        return c16.join(',');
    }

    getPlaceAccessibleTitle(h15) {
        if (h15 === undefined) {
            return '';
        }
        let i15 = this.findParentNodeId(h15);
        if (i15 === -1) {
            let v15 = [];
            let w15 = this.nodeIdNodeItemMap.get(h15);
            if (w15 === undefined || i15 === undefined) {
                return '';
            }
            let x15 = this.getNodeInfoByNodeItem(w15).getNodeInfoData()?.primaryTitle === undefined
                ? '' : this.getNodeInfoByNodeItem(w15).getNodeInfoData().primaryTitle;
            let y15 = this.getNodeInfoByNodeItem(w15).getNodeInfoData()?.secondaryTitle === undefined
                ? '' : this.getNodeInfoByNodeItem(w15).getNodeInfoData().secondaryTitle;
            let z15 = this.getAccessibleTitleText(x15);
            let a16 = this.getAccessibleTitleText(y15);
            v15.unshift(`${z15}, ${a16}`);
            return v15.join(',');
        } else {
            let j15 = [];
            let k15 = this.nodeIdNodeItemMap.get(h15);
            if (k15 === undefined || i15 === undefined) {
                return '';
            }
            let l15 = this.getNodeInfoByNodeItem(k15).getNodeInfoData()?.primaryTitle === undefined
                ? '' : this.getNodeInfoByNodeItem(k15).getNodeInfoData().primaryTitle;
            let m15 = this.getNodeInfoByNodeItem(k15).getNodeInfoData()?.secondaryTitle === undefined
                ? '' : this.getNodeInfoByNodeItem(k15).getNodeInfoData().secondaryTitle;
            let n15 = this.getAccessibleTitleText(l15);
            let o15 = this.getAccessibleTitleText(m15);
            j15.unshift(`${n15}, ${o15}`);
            while (h15 !== -1) {
                if (h15 === undefined) {
                    return '';
                }
                let p15 = this.findParentNodeId(h15);
                let q15 = this.nodeIdNodeItemMap.get(p15);
                if (q15 === undefined || p15 === undefined) {
                    return '';
                }
                let r15 = this.getNodeInfoByNodeItem(q15).getNodeInfoData()?.primaryTitle === undefined
                    ? '' : this.getNodeInfoByNodeItem(q15).getNodeInfoData().primaryTitle;
                let s15 = this.getNodeInfoByNodeItem(q15).getNodeInfoData()?.secondaryTitle === undefined
                    ? '' : this.getNodeInfoByNodeItem(q15).getNodeInfoData().secondaryTitle;
                let t15 = this.getAccessibleTitleText(r15);
                let u15 = this.getAccessibleTitleText(s15);
                j15.unshift(`${t15}, ${u15}`);
                h15 = q15.currentNodeId;
            }
            return j15.join(',');
        }
    }

    getDraggingAccessible(y14, z14, a15) {
        this.getAccessibleTitle(a15);
        if (z14 === undefined || a15 === undefined) {
            return;
        }
        let b15 = this.findParentNodeId(a15);
        let c15 = y14.indexOf(a15) + 2;
        let d15 = this.getClickNodeChildrenInfo(b15);
        let e15 = d15.map(g15 => g15.itemId);
        let f15 = e15.indexOf(a15) + 2;
        if (b15 === -1 && this.getExpandAndCollapseInfo(z14) === NodeStatus.COLLAPSE ||
            b15 === -1 && this.getExpandAndCollapseInfo(z14) === undefined) {
            this.sendAccessibility(this.getStringByName('treeview_accessibility_move_node_parent', c15));
        } else if (this.getExpandAndCollapseInfo(z14) === NodeStatus.EXPAND) {
            this.sendAccessibility(this.getStringByName('treeview_accessibility_move_node_child',
                this.getAccessibleTitle(a15), 1));
        } else if (b15 !== -1) {
            this.sendAccessibility(this.getStringByName('treeview_accessibility_move_node_child',
                this.getAccessibleTitle(a15), f15));
        }
    }

    getStringByName(v14, ...w14) {
        if (v14) {
            try {
                return getContext()?.resourceManager.getStringByNameSync(v14, ...w14);
            } catch (x14) {
                console.error(`Ace SegmentButton getAccessibilityDescription, error: ${x14.toString()}`);
            }
        }
        return '';
    }

    sendAccessibility(t14) {
        let u14 = ({
            type: 'announceForAccessibility',
            bundleName: getContext()?.abilityInfo?.bundleName,
            triggerAction: 'common',
            textAnnouncedForAccessibility: t14
        });
        accessibility.sendAccessibilityEvent(u14);
    }

    getAccessibleTitleText(o14) {
        let p14 = '';
        try {
            if (typeof o14 === 'string') {
                p14 = o14;
            } else {
                p14 = getContext()?.resourceManager?.getStringSync(o14?.id);
            }
        } catch (q14) {
            let r14 = q14.code;
            let s14 = q14.message;
            hilog.error(0x3900, 'Ace', `treeView getAccessibleTitleText error, code: ${r14}, message: ${s14}`);
        }
        return p14;
    }

    setVisibility(a14, b14, c14, d14) {
        let e14 = (this.thisPassIndex !== b14 || this.flag !== a14) ? true : false;
        this.thisPassIndex = b14;
        if ((e14 || c14) && this.isInnerDrag) {
            this.flag = a14;
            let f14 = this.getData(b14)?.getNodeCurrentNodeId();
            let g14 = this.getData(b14)?.getNodeLevel();
            if (f14 !== undefined) {
                g14 = (this.expandAndCollapseInfo.get(f14) === NodeStatus.EXPAND &&
                    this.flag === Flag.DOWN_FLAG) ? (g14 ? g14 + 1 : undefined) : g14;
                if (this.lastPassId !== this.INITIAL_INVALID_VALUE &&
                this.loadedNodeIdAndIndexMap.has(this.lastPassId)) {
                    let m14 = this.loadedNodeIdAndIndexMap.get(this.lastPassId);
                    this.listNode.forEach((n14) => {
                        if (n14.getNodeCurrentNodeId() === this.lastPassId) {
                            n14.setCanShowFlagLine(false);
                        }
                    });
                    this.notifyDataChange(m14);
                }
                let h14 = this.getData(b14 - 1)?.getNodeCurrentNodeId();
                let i14 = this.getData(b14 + 2)?.getNodeCurrentNodeId();
                let j14 = this.getData(b14 + 1)?.getNodeCurrentNodeId();
                let k14 = this.nodeIdNodeItemMap.get(j14);
                if (this.flag === Flag.DOWN_FLAG && b14 < this.totalCount() - 1) {
                    this.getData(b14)?.setCanShowFlagLine(false);
                    this.getData(b14 + 1)?.setCanShowFlagLine(true);
                    this.getData(b14)?.setCanShowBottomFlagLine(false);
                    this.getData(b14 + 1)?.setFlagLineLeftMargin(g14);
                    this.notifyDataChange(b14);
                    this.notifyDataChange(b14 + 1);
                    this.lastPassId = this.getData(b14 + 1)?.getNodeCurrentNodeId();
                    let l14 = this.nodeIdNodeItemMap.get(j14);
                    if (!l14?.childNodeInfo.isHasChildNode) {
                        this.getDraggingAccessible(d14, j14, j14);
                    } else {
                        this.getDraggingAccessible(d14, j14, i14);
                    }
                } else if (this.flag === Flag.UP_FLAG && b14 < this.totalCount() - 1) {
                    this.getData(b14)?.setCanShowFlagLine(true);
                    this.getData(b14 + 1)?.setCanShowFlagLine(false);
                    this.getData(b14)?.setCanShowBottomFlagLine(false);
                    this.getData(b14)?.setFlagLineLeftMargin(g14);
                    this.notifyDataChange(b14);
                    this.notifyDataChange(b14 + 1);
                    this.lastPassId = this.getData(b14)?.getNodeCurrentNodeId();
                    if (k14?.childNodeInfo.isHasChildNode && k14?.parentNodeId !== -1) {
                        this.getDraggingAccessible(d14, j14, j14);
                    } else if (k14?.childNodeInfo.isHasChildNode && k14?.parentNodeId === -1) {
                        this.getDraggingAccessible(d14, h14, j14);
                    }
                } else if (b14 >= this.totalCount() - 1) {
                    if (this.flag === Flag.DOWN_FLAG) {
                        this.getData(b14)?.setCanShowFlagLine(false);
                        this.getData(b14)?.setCanShowBottomFlagLine(true);
                    } else {
                        this.getData(b14)?.setCanShowFlagLine(true);
                        this.getData(b14)?.setCanShowBottomFlagLine(false);
                    }
                    this.getData(b14)?.setFlagLineLeftMargin(g14);
                    this.notifyDataChange(b14);
                    this.lastPassId = this.getData(b14)?.getNodeCurrentNodeId();
                }
            }
        }
    }

    delayHighLightAndExpandNode(p13, q13, r13) {
        let s13 = p13 !== this.lastDelayExpandIndex ? true : false;
        let t13 = this.getData(r13)?.getIsOverBorder();
        let u13 = this.listNode[p13 + 1]?.getNodeCurrentNodeId();
        let v13 = this.findParentNodeId(q13);
        if (t13) {
            this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE;
        } else {
            this.lastDelayExpandIndex = p13;
        }
        if (t13 || s13) {
            let w13 = !t13 && (!this.isInnerDrag ||
                (this.expandAndCollapseInfo.get(q13) === NodeStatus.COLLAPSE && this.isInnerDrag) ||
                (!this.expandAndCollapseInfo.has(q13) && this.listNode[p13].getIsFolder()));
            if (w13) {
                this.changeNodeColor(p13, this.listNode[p13].getNodeStatus().hover);
                this.notifyDataChange(r13);
                let z13 = this.isInnerDrag ? 1000 : 0;
                this.timeoutHighLightId = setTimeout(() => {
                    this.delayHighLight(p13);
                    this.sendAccessibility(this.getStringByName('treeview_accessibility_move_node_child',
                        this.getPlaceAccessibleTitle(q13), 1));
                }, z13);
            }
            if (t13 || (this.lastTimeoutHighLightId !== this.INITIAL_INVALID_VALUE &&
                this.clearTimeoutHighLightId !== this.lastTimeoutHighLightId)) {
                clearTimeout(this.lastTimeoutHighLightId);
                if (this.lastDelayHighLightIndex !== this.INITIAL_INVALID_VALUE) {
                    this.clearHighLight(this.lastDelayHighLightIndex);
                    this.notifyDataReload();
                }
                this.clearTimeoutHighLightId = this.lastTimeoutHighLightId;
            }
            this.lastTimeoutHighLightId = this.timeoutHighLightId;
            this.lastDelayHighLightIndex = p13;
            if (!t13 && this.expandAndCollapseInfo.get(q13) === NodeStatus.COLLAPSE) {
                let x13 = this.getData(r13)?.getNodeInfoNode().children[0]?.currentNodeId;
                let y13 = 2000;
                this.timeoutExpandId = setTimeout(() => {
                    this.clearHighLight(this.lastDelayHighLightIndex);
                    if (x13 !== undefined) {
                        this.alterFlagLineAndExpandNode(p13, x13);
                    }
                }, y13);
            }
            if (t13 || (this.lastTimeoutExpandId !== this.INITIAL_INVALID_VALUE &&
                this.clearTimeoutExpandId !== this.lastTimeoutExpandId)) {
                clearTimeout(this.lastTimeoutExpandId);
                this.clearTimeoutExpandId = this.lastTimeoutExpandId;
            }
            this.lastTimeoutExpandId = this.timeoutExpandId;
        }
    }

    delayHighLight(n13) {
        this.listNode.forEach((o13) => {
            if (o13.getNodeCurrentNodeId() === this.lastPassId) {
                o13.setCanShowFlagLine(false);
                o13.setCanShowBottomFlagLine(false);
                return;
            }
        });
        this.changeNodeColor(n13, this.listNode[n13].getNodeStatus().highLight);
        this.listNode[n13].setIsHighLight(true);
        this.changeNodeHighLightColor(n13, true);
        this.setImageSource(n13, InteractionStatus.DRAG_INSERT);
        this.setImageCollapseSource(n13, InteractionStatus.DRAG_INSERT);
        this.notifyDataReload();
    }

    alterFlagLineAndExpandNode(j13, k13) {
        this.listNode.forEach((m13) => {
            if (m13.getNodeCurrentNodeId() === this.lastPassId) {
                m13.setCanShowFlagLine(false);
                m13.setCanShowBottomFlagLine(false);
            }
        });
        this.listNode.forEach((l13) => {
            if (this.isInnerDrag && l13.getNodeCurrentNodeId() === k13) {
                l13.setCanShowFlagLine(true);
            }
        });
        this.changeNodeStatus(j13);
        this.handleExpandAndCollapse(j13, true);
        this.lastPassId = k13;
    }

    hideLastLine() {
        if (this.lastPassId !== this.INITIAL_INVALID_VALUE && this.loadedNodeIdAndIndexMap.has(this.lastPassId)) {
            this.listNode.forEach((i13) => {
                if (i13.getNodeCurrentNodeId() === this.lastPassId) {
                    i13.setCanShowFlagLine(false);
                    i13.setCanShowBottomFlagLine(false);
                    return;
                }
            });
            let h13 = this.loadedNodeIdAndIndexMap.get(this.lastPassId);
            this.notifyDataChange(h13);
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

    getSubtitle(g13) {
        if (this.nodeIdAndSubtitleMap.has(g13)) {
            if (typeof this.nodeIdAndSubtitleMap.get(g13) === 'number') {
                return this.nodeIdAndSubtitleMap.get(g13)?.toString();
            } else {
                return this.nodeIdAndSubtitleMap.get(g13);
            }
        } else {
            return '';
        }
    }

    hasSubtitle(f13) {
        return this.nodeIdAndSubtitleMap.has(f13);
    }

    initialParameterAboutDelayHighLightAndExpandIndex() {
        this.lastDelayHighLightIndex = this.INITIAL_INVALID_VALUE;
        this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE;
        this.lastPassIndex = this.INITIAL_INVALID_VALUE;
        this.draggingCurrentNodeId = this.INITIAL_INVALID_VALUE;
        this.flag = Flag.NONE;
    }

    refreshSubtitle(e13) {
        this.nodeIdAndSubtitleMap.set(this.selectedParentNodeId, this.selectedParentNodeSubtitle);
        this.nodeIdAndSubtitleMap.set(e13, this.insertNodeSubtitle);
        this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.selectedParentNodeId));
        this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(e13));
    }

    setNodeSubtitlePara(b13, c13, d13) {
        this.selectedParentNodeId = b13;
        this.selectedParentNodeSubtitle = c13;
        this.insertNodeSubtitle = d13;
    }

    getInsertNodeSubtitle() {
        return this.insertNodeSubtitle;
    }

    getExpandAndCollapseInfo(a13) {
        return this.expandAndCollapseInfo.get(a13);
    }

    getLastDelayHighLightId() {
        return this.lastDelayHighLightId;
    }

    setLastDelayHighLightId() {
        this.listNode.forEach((y12, z12) => {
            if (z12 === this.lastDelayHighLightIndex) {
                this.lastDelayHighLightId = y12.getNodeCurrentNodeId();
            }
        });
    }

    setLastPassId(x12) {
        this.lastPassId = x12;
    }

    setLastDelayHighLightIndex(w12) {
        this.lastDelayHighLightIndex = w12;
    }

    alterDragNode(r11, s11, t11, u11, v11) {
        let w11 = [];
        let x11 = r11;
        let y11 = u11;
        let z11 = v11.getNodeInfoData();
        let a12 = null;
        let b12 = v11.getNodeInfoNode();
        let c12 = false;
        let d12 = this.INITIAL_INVALID_VALUE;
        let e12 = this.INITIAL_INVALID_VALUE;
        let f12 = this.flag === Flag.DOWN_FLAG ? true : false;
        e12 = this.getChildIndex(t11, u11);
        d12 = this.getChildIndex(r11, s11) + 1;
        if (r11 !== t11) {
            d12 = f12 ? d12 + 1 : d12;
        } else {
            if (d12 > e12) {
                d12 = f12 ? d12 : d12 - 1;
            } else {
                d12 = f12 ? d12 + 1 : d12;
            }
        }
        for (let v12 = 0; v12 < this.listNode.length; v12++) {
            if (this.listNode[v12].getNodeCurrentNodeId() === s11) {
                c12 = this.listNode[v12].getIsHighLight();
                if (this.flag === Flag.DOWN_FLAG && this.expandAndCollapseInfo.get(s11) === NodeStatus.EXPAND) {
                    x11 = s11;
                    d12 = 0;
                } else if (this.flag === Flag.UP_FLAG && this.expandAndCollapseInfo.get(s11) ===
                NodeStatus.EXPAND &&
                    this.listNode[v12].getCanShowFlagLine() === false) {
                    x11 = s11;
                    d12 = 0;
                } else if (c12) {
                    x11 = s11;
                    d12 = 0;
                }
                break;
            }
        }
        let g12 = {
            currentNodeId: y11,
            parentNodeId: x11,
            childIndex: d12,
        };
        this.appEventBus.emit(TreeListenType.NODE_MOVE, g12);
        w11.push({ parentId: x11, currentId: y11, data: z11 });
        let h12 = (r12, s12) => {
            if (r12) {
                x11 = r12.parentNodeId;
                y11 = r12.currentNodeId;
                for (let u12 = 0; u12 < s12.length; u12++) {
                    if (s12[u12].getNodeCurrentNodeId() === y11) {
                        a12 = s12[u12];
                        break;
                    }
                }
                if (a12 === null) {
                    return false;
                }
                let t12 = a12.getNodeInfoData();
                if (x11 !== t11) {
                    w11.push({ parentId: x11, currentId: y11, data: t12 });
                }
                return false;
            }
            return false;
        };
        this.dragTraverseNodeDF(h12, b12, this.listNode);
        let i12 = this.removeNode(u11, t11);
        if (i12.length === 0) {
            return;
        }
        let j12 = s11;
        let k12 = f12;
        if (this.expandAndCollapseInfo.get(s11) === NodeStatus.EXPAND) {
            k12 = false;
            this.listNode.forEach((q12) => {
                if (q12.getNodeCurrentNodeId() === s11 && q12.getCanShowFlagLine() === false) {
                    if (q12.getNodeInfoNode().children.length) {
                        j12 = q12.getNodeInfoNode().children[0].currentNodeId;
                    } else {
                        j12 = this.INITIAL_INVALID_VALUE;
                    }
                }
            });
        } else if (!this.expandAndCollapseInfo.get(s11) && c12) {
            this.expandAndCollapseInfo.set(s11, NodeStatus.EXPAND);
        }
        let l12 = this.addDragNode(w11[0].parentId, w11[0].currentId, j12, k12, w11[0].data);
        if (!l12) {
            return;
        }
        for (let o12 = 1; o12 < w11.length; o12++) {
            let p12 = this.addNode(w11[o12].parentId, w11[o12].currentId, w11[o12].data, false);
            if (!p12) {
                return;
            }
        }
        for (let n12 = 0; n12 < this.listNode.length; n12++) {
            if (this.listNode[n12].getNodeCurrentNodeId() === t11) {
                if (this.listNode[n12].getNodeItem().imageCollapse === null) {
                    this.listNode[n12].handleImageCollapseAfterAddNode(false);
                    this.expandAndCollapseInfo.delete(t11);
                    break;
                }
            }
        }
        let m12 = [...this.listNode];
        this.reloadListNode(m12);
    }

    reloadListNode(k11) {
        let l11 = 0;
        let m11 = 0;
        this.listNode.splice(0, this.listNode.length);
        this.loadedNodeIdAndIndexMap.clear();
        this.loadedListNode.splice(0, this.loadedListNode.length);
        this.traverseNodeDF((n11) => {
            let o11 = n11.currentNodeId;
            if (o11 >= 0) {
                if (this.nodeIdNodeParamMap.has(o11)) {
                    let p11 = new NodeInfo(n11, this.nodeIdNodeParamMap.get(o11));
                    p11.addImageCollapse(n11.getChildNodeInfo().isHasChildNode);
                    this.listNode.push(p11);
                    this.nodeIdAndNodeIndexMap.set(p11.getNodeCurrentNodeId(), m11++);
                    if (this.expandAndCollapseInfo.get(o11) === NodeStatus.EXPAND) {
                        p11.getNodeItem()
                            .imageCollapse =
                            CollapseImageNodeFlyweightFactory.changeImageCollapseSource(NodeStatus.EXPAND,
                                p11.getNodeItem().imageCollapse?.isCollapse);
                    } else if (this.expandAndCollapseInfo.get(o11) === NodeStatus.COLLAPSE) {
                        p11.getNodeItem()
                            .imageCollapse =
                            CollapseImageNodeFlyweightFactory.changeImageCollapseSource(NodeStatus.COLLAPSE,
                                p11.getNodeItem().imageCollapse?.isCollapse);
                    }
                    for (let q11 = 0; q11 < k11.length; q11++) {
                        if (k11[q11].getNodeCurrentNodeId() === p11.getNodeCurrentNodeId()) {
                            p11.setNodeIsShow(k11[q11].getNodeIsShow());
                            p11.setListItemHeight(k11[q11].getListItemHeight());
                            if (p11.getNodeItem().mainTitleNode && p11.getIsShowTitle()) {
                                p11.getNodeItem().mainTitleNode.title = k11[q11].getNodeItem().mainTitleNode?.title;
                            }
                            break;
                        }
                    }
                    if (p11.getNodeIsShow()) {
                        this.loadedNodeIdAndIndexMap.set(p11.getNodeCurrentNodeId(), l11++);
                        this.loadedListNode.push(p11);
                    }
                }
            }
            return false;
        });
    }

    getFlagLine() {
        return this.FLAG_LINE;
    }

    getVisibility(h11) {
        let i11 = this.loadedNodeIdAndIndexMap.get(h11.getNodeCurrentNodeId()) - 1;
        if (i11 > this.INITIAL_INVALID_VALUE) {
            let j11 = this.getData(i11);
            return (h11.getCanShowFlagLine() === true && !h11.getIsHighLight() && !j11?.getIsHighLight()) ?
            Visibility.Visible : Visibility.Hidden;
        } else {
            return (h11.getCanShowFlagLine() === true && !h11.getIsHighLight()) ?
            Visibility.Visible : Visibility.Hidden;
        }
    }

    getSubTitlePara() {
        return this.subTitle;
    }

    getIsFolder(g11) {
        if (this.loadedNodeIdAndIndexMap.has(g11)) {
            return this.getData(this.loadedNodeIdAndIndexMap.get(g11))?.getIsFolder();
        }
        return false;
    }

    getSubTitleFontColor(f11) {
        return f11 ? this.subTitle.highLightFontColor : this.treeViewTheme.secondaryTitleFontColor;
    }

    getChildIndex(z10, a11) {
        let b11 = this.INITIAL_INVALID_VALUE;
        if (this.nodeIdNodeItemMap.has(z10)) {
            let c11 = this.nodeIdNodeItemMap.get(z10);
            if (c11.getCurrentNodeId() === z10) {
                c11.children.forEach((d11, e11) => {
                    if (d11.getCurrentNodeId() === a11) {
                        b11 = e11;
                        return;
                    }
                });
            }
        }
        return b11;
    }

    setCurrentFocusNodeId(y10) {
        this.currentFocusNodeId = y10;
    }

    getCurrentFocusNodeId() {
        return this.currentFocusNodeId;
    }

    setLastFocusNodeId(x10) {
        this.lastFocusNodeId = x10;
    }

    getLastFocusNodeId() {
        return this.lastFocusNodeId;
    }

    getAddFocusNodeId() {
        return this.addFocusNodeId;
    }

    setFlag(w10) {
        this.flag = w10;
    }

    traverseNodeDF(r10, s10 = this._root) {
        let t10 = [];
        let u10 = false;
        t10.unshift(s10);
        let v10 = t10.shift();
        while (!u10 && v10) {
            u10 = r10(v10) === true;
            if (!u10) {
                t10.unshift(...v10.children);
                v10 = t10.shift();
            }
        }
    }

    traverseSectionNodeDF(i10, j10 = this._root, k10, l10) {
        let m10 = [];
        let n10 = false;
        let o10 = false;
        m10.unshift(j10);
        let p10 = m10.shift();
        while (!n10 && p10) {
            try {
                if (k10 !== undefined && p10.nodeLevel < k10) {
                    o10 = true;
                }
                if (l10 !== undefined && p10.nodeLevel > l10) {
                    o10 = true;
                }
                if (!o10) {
                    n10 = i10(p10);
                }
            } catch (q10) {
                throw new Error('traverseSectionNodeDF function callbacks error');
            }
            if (!n10) {
                m10.unshift(...p10.children);
                p10 = m10.shift();
                o10 = false;
            }
        }
    }

    updateParentChildNum(d10, e10, f10) {
        let g10 = d10.parentNodeId;
        while (g10 >= 0) {
            if (this.nodeIdNodeItemMap.has(g10)) {
                let h10 = this.nodeIdNodeItemMap.get(g10);
                h10.getChildNodeInfo().allChildNum =
                    e10 ? h10.getChildNodeInfo().allChildNum + f10 : h10.getChildNodeInfo().allChildNum - f10;
                g10 = h10.parentNodeId;
            } else {
                hilog.error(LOG_CODE, TAG, 'updateParentChildNum: parent node not found.');
                break;
            }
        }
    }

    findParentNodeId(b10) {
        let c10 = new NodeItem(emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(b10)) {
            c10 = this.nodeIdNodeItemMap.get(b10);
        }
        return c10.parentNodeId;
    }

    refreshRemoveNodeData(r9, s9) {
        let t9 = [];
        if (r9.length === 0) {
            return;
        }
        let u9 = undefined;
        for (let y9 = 0; y9 < r9.length; y9++) {
            if (this.loadedNodeIdAndIndexMap.has(r9[y9])) {
                let a10 = this.loadedNodeIdAndIndexMap.get(r9[y9]);
                t9.push(a10);
            }
            if (u9 === undefined && this.nodeIdAndNodeIndexMap.has(r9[y9])) {
                u9 = this.nodeIdAndNodeIndexMap.get(r9[y9]);
            }
            if (u9 !== undefined) {
                let z9 = this.listNode.splice(u9, 1);
                z9 = null;
            }
            if (this.expandAndCollapseInfo.has(r9[y9])) {
                this.expandAndCollapseInfo.delete(r9[y9]);
            }
        }
        t9.forEach((x9) => {
            this.notifyDataDelete(x9);
            this.notifyDataChange(x9);
        });
        if (s9.getNodeItem().imageCollapse === null) {
            if (this.nodeIdAndNodeIndexMap.has(s9.getNodeCurrentNodeId())) {
                let w9 = this.nodeIdAndNodeIndexMap.get(s9.getNodeCurrentNodeId());
                this.listNode[w9]?.handleImageCollapseAfterAddNode(false);
            }
            this.expandAndCollapseInfo.delete(s9.getNodeCurrentNodeId());
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(s9.getNodeCurrentNodeId()));
        }
        let v9 = {
            currentNodeId: s9.getNodeCurrentNodeId(),
            parentNodeId: s9.getNodeParentNodeId(),
        };
        this.loadedListNodeFunction();
        this.appEventBus.emit(TreeListenType.NODE_DELETE, v9);
    }

    refreshAddNodeData(m9) {
        let n9 = new NodeInfo(new NodeItem(emptyNodeInfo), emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(m9[0])) {
            let q9 = this.nodeIdNodeItemMap.get(m9[0]);
            n9 = new NodeInfo(q9, this.nodeIdNodeParamMap.get(m9[0]));
            n9.addImageCollapse(q9.getChildNodeInfo().isHasChildNode);
        }
        n9.setIsModify(true);
        let o9 = 0;
        for (let p9 = 0; p9 < this.listNode.length; p9++) {
            if (this.listNode[p9].getNodeCurrentNodeId() === n9.getNodeParentNodeId()) {
                o9 = p9;
                if (this.listNode[p9].getNodeItem().imageCollapse === null) {
                    this.listNode[p9].handleImageCollapseAfterAddNode(true);
                    this.notifyDataChange(o9);
                } else if (this.expandAndCollapseInfo.get(this.listNode[p9].getNodeCurrentNodeId()) ===
                NodeStatus.COLLAPSE) {
                    this.changeNodeStatus(o9);
                }
                this.listNode.splice(p9 + 1, 0, n9);
                this.listNode[p9 + 1].setTitleAndInputTextStatus(true);
                this.listNode[p9 + 1].setNodeIsShow(true);
                this.listNode[p9 + 1].setListItemHeight(LIST_ITEM_HEIGHT);
                this.nodeIdAndNodeIndexMap.set(m9[0], p9 + 1);
                this.setImageSource(p9 + 1, InteractionStatus.EDIT);
                this.currentOperation = MenuOperation.ADD_NODE;
                this.notifyDataAdd(p9 + 1);
                this.notificationNodeInfo(p9 + 1, this.currentOperation);
                break;
            }
        }
        this.modifyNodeIndex = o9 + 1;
        this.setClickIndex(o9);
        this.lastIndex = o9;
        this.expandAndCollapseInfo.set(n9.getNodeParentNodeId(), NodeStatus.EXPAND);
        this.handleExpandAndCollapse(o9, true);
    }

    refreshData(h9, i9, j9) {
        let k9 = new NodeInfo(new NodeItem(emptyNodeInfo), emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(i9)) {
            let l9 = this.nodeIdNodeItemMap.get(i9);
            k9 = new NodeInfo(l9, this.nodeIdNodeParamMap.get(i9));
            k9.addImageCollapse(l9.getChildNodeInfo().isHasChildNode);
        }
        if (h9 === MenuOperation.REMOVE_NODE) {
            this.nodeIdAndSubtitleMap.set(i9, this.selectedParentNodeSubtitle);
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(i9));
            this.refreshRemoveNodeData(j9, k9);
        }
        if (h9 === MenuOperation.ADD_NODE) {
            this.addFocusNodeId = j9[0];
            this.nodeIdAndSubtitleMap.set(this.getClickNodeId(), this.selectedParentNodeSubtitle);
            this.nodeIdAndSubtitleMap.set(j9[0], this.insertNodeSubtitle);
            this.refreshAddNodeData(j9);
        }
    }

    removeNode(x8, y8) {
        if (this.nodeIdNodeItemMap.has(y8) && this.nodeIdNodeItemMap.has(x8)) {
            let z8 = this.nodeIdNodeItemMap.get(y8);
            let a9 = this.nodeIdNodeItemMap.get(x8);
            let b9 = [];
            let c9 = a9.indexOfParent;
            let d9 = 0;
            if (c9 < 0) {
                hilog.error(LOG_CODE, TAG, 'node does not exist.');
                return [];
            } else {
                d9 = z8.children[c9].getChildNodeInfo().allChildNum + 1;
                this.freeNodeMemory(z8.children[c9], b9);
                for (let g9 = c9; g9 < z8.children.length; g9++) {
                    z8.children[g9].indexOfParent -= 1;
                }
                let f9 = z8.children.splice(c9, 1);
                f9 = null;
                this.judgeImageCollapse(y8);
            }
            z8.getChildNodeInfo().childNum = z8.children.length;
            z8.getChildNodeInfo().allChildNum -= (d9);
            let e9 = [];
            e9.push(z8.parentNodeId);
            delayUpdateParentChildNum(false, d9, this.nodeIdNodeItemMap, e9);
            return b9;
        } else {
            hilog.error(LOG_CODE, TAG, 'parent does not exist.');
            return [];
        }
    }

    addNode(q8, r8, s8, t8) {
        if (this._root === null) {
            this._root = new NodeItem(emptyNodeInfo);
            this._root.nodeLevel = -1;
            this.nodeIdNodeItemMap.set(-1, this._root);
            this.nodeIdNodeParamMap.set(-1, emptyNodeInfo);
        }
        if (this.nodeIdNodeItemMap.has(q8)) {
            let u8 = this.nodeIdNodeItemMap.get(q8);
            let v8 = new NodeItem(s8);
            if (u8.nodeLevel > this.maxNodeLevel) {
                hilog.error(LOG_CODE, TAG, 'ListDataSource[addNode]: The level of the tree view cannot exceed 50.');
                return false;
            }
            v8.nodeLevel = u8.nodeLevel + 1;
            v8.parentNodeId = q8;
            v8.currentNodeId = r8;
            v8.indexOfParent = u8.children.length;
            s8.parentNodeId = q8;
            s8.currentNodeId = r8;
            if (s8.symbolIconStyle && !s8.icon) {
                s8.icon = 'symbolUsed';
            }
            u8.children.push(v8);
            u8.getChildNodeInfo().isHasChildNode = true;
            u8.getChildNodeInfo().childNum = u8.children.length;
            u8.getChildNodeInfo().allChildNum += 1;
            this.judgeImageCollapse(q8);
            if (t8) {
                this.updateNodeIdList.push(u8.parentNodeId);
            } else {
                let w8 = [];
                w8.push(u8.parentNodeId);
                delayUpdateParentChildNum(true, 1, this.nodeIdNodeItemMap, w8);
            }
            this.nodeIdNodeParamMap.set(r8, s8);
            this.nodeIdNodeItemMap.set(r8, v8);
            return true;
        } else {
            hilog.error(LOG_CODE, TAG, 'ListDataSource[addNode]: Parent node not found.');
            return false;
        }
    }

    judgeImageCollapse(n8) {
        if (n8 === undefined) {
            return;
        }
        let o8 = this.nodeIdNodeItemMap.get(n8);
        let p8 = this.nodeIdAndNodeIndexMap.get(n8);
        if (o8.children.length > 0) {
            if (this.nodeIdAndNodeIndexMap.has(n8)) {
                this.listNode[p8]?.addImageExpand(true);
            }
        } else {
            this.listNode[p8]?.addImageExpand(false);
        }
    }

    freeNodeMemory(h8, i8) {
        let j8 = [];
        let k8 = (m8) => {
            j8.push(m8);
            return false;
        };
        this.traverseNodeDF(k8, h8);
        j8.forEach((l8) => {
            i8.push(l8.getCurrentNodeId());
            this.nodeIdNodeItemMap.delete(l8.getCurrentNodeId());
            this.nodeIdNodeParamMap.delete(l8.getCurrentNodeId());
            l8 = new NodeItem(emptyNodeInfo);
        });
    }

    getNodeInfoByNodeItem(f8) {
        if (f8?.currentNodeId === undefined) {
            hilog.error(LOG_CODE, TAG, 'getNodeInfoByNodeItem: currentId is undefined');
            return new NodeInfo(new NodeItem(emptyNodeInfo), emptyNodeInfo);
        }
        if (!this.nodeIdAndNodeIndexMap.has(f8.currentNodeId)) {
            hilog.error(LOG_CODE, TAG, 'getNodeInfoByNodeItem: not has nodeItem.');
            return new NodeInfo(new NodeItem(emptyNodeInfo), emptyNodeInfo);
        }
        let g8 = this.nodeIdAndNodeIndexMap.get(f8.currentNodeId);
        return this.listNode[g8];
    }

    getNewNodeParam(a8) {
        let b8 = new NodeItem(emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(a8)) {
            b8 = this.nodeIdNodeItemMap.get(a8);
        }
        let c8 = emptyNodeInfo;
        if (b8) {
            let d8 = this.getNodeInfoByNodeItem(b8);
            if (b8.children.length === 0) {
                if (d8.getNodeItem().imageNode !== undefined) {
                    c8.icon = d8.getNodeItem().imageNode?.normalSource;
                    c8.symbolIconStyle = d8.getNodeItem().imageNode?.symbolNormalSource;
                    c8.selectedIcon = d8.getNodeItem().imageNode?.selectedSource;
                    c8.symbolSelectedIconStyle = d8.getNodeItem().imageNode?.symbolSelectedSource;
                    c8.editIcon = d8.getNodeItem().imageNode?.editSource;
                    c8.symbolEditIconStyle = d8.getNodeItem().imageNode?.symbolEditSource;
                    c8.container = d8.getMenu();
                } else {
                    c8.icon = undefined;
                    c8.symbolIconStyle = undefined;
                    c8.selectedIcon = undefined;
                    c8.symbolSelectedIconStyle = undefined;
                    c8.editIcon = undefined;
                    c8.symbolEditIconStyle = undefined;
                    c8.container = d8.getMenu();
                }
            } else if (b8.children.length > 0) {
                let e8 = this.getNodeInfoByNodeItem(b8.children[0]);
                if (d8.getNodeItem().imageNode !== null) {
                    c8.icon = (e8.getNodeItem().imageNode !== undefined) ?
                        e8.getNodeItem().imageNode?.normalSource : undefined;
                    c8.symbolIconStyle = (e8.getNodeItem().imageNode !== undefined) ?
                        e8.getNodeItem().imageNode?.symbolNormalSource : undefined;
                    c8.selectedIcon = (e8.getNodeItem().imageNode !== undefined) ?
                        e8.getNodeItem().imageNode?.selectedSource : undefined;
                    c8.symbolSelectedIconStyle = (e8.getNodeItem().imageNode !== undefined) ?
                        e8.getNodeItem().imageNode?.symbolSelectedSource : undefined;
                    c8.editIcon = (e8.getNodeItem().imageNode !== undefined) ?
                        e8.getNodeItem().imageNode?.editSource : undefined;
                    c8.symbolEditIconStyle = (e8.getNodeItem().imageNode !== undefined) ?
                        e8.getNodeItem().imageNode?.symbolEditSource : undefined;
                    c8.container = e8.getMenu();
                } else {
                    c8.icon = undefined;
                    c8.symbolIconStyle = undefined;
                    c8.selectedIcon = undefined;
                    c8.symbolSelectedIconStyle = undefined;
                    c8.editIcon = undefined;
                    c8.symbolEditIconStyle = undefined;
                    c8.container = e8.getMenu();
                }
            }
        }
        return c8;
    }

    getClickChildId(v7) {
        let w7 = new NodeItem(emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(v7)) {
            w7 = this.nodeIdNodeItemMap.get(v7);
        }
        if (w7) {
            if (w7.children.length === 0) {
                return [];
            } else if (w7.children.length > 0) {
                let x7 = new Array(w7.children.length);
                for (let z7 = 0; z7 < x7.length; z7++) {
                    x7[z7] = 0;
                }
                for (let y7 = 0; y7 < w7.children.length && y7 < x7.length; y7++) {
                    x7[y7] = w7.children[y7].currentNodeId;
                }
                return x7;
            }
        }
        return [];
    }

    getClickNodeChildrenInfo(p7) {
        let q7 = new NodeItem(emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(p7)) {
            q7 = this.nodeIdNodeItemMap.get(p7);
        }
        if (q7) {
            if (q7.children.length === 0) {
                return [];
            } else if (q7.children.length > 0) {
                let r7 = new Array(q7.children.length);
                for (let u7 = 0; u7 < r7.length; u7++) {
                    r7[u7] = {};
                }
                for (let s7 = 0; s7 < q7.children.length && s7 < r7.length; s7++) {
                    r7[s7].itemId = q7.children[s7].currentNodeId;
                    let t7 = this.getNodeInfoByNodeItem(q7.children[s7]);
                    if (t7.getNodeItem().imageNode) {
                        r7[s7].itemIcon = t7.getNodeItem().imageNode?.source;
                    }
                    if (t7.getNodeItem().mainTitleNode) {
                        r7[s7].itemTitle = t7.getNodeItem().mainTitleNode?.title;
                    }
                    r7[s7].isFolder = t7.getIsFolder();
                }
                return r7;
            }
        }
        return [];
    }

    checkMainTitleIsValid(o7) {
        if (new RegExp('/[\\\/:*?"<>|]/').test(o7)) {
            return false;
        }
        if ((new RegExp('/^[\u4e00-\u9fa5]+$/').test(o7) && o7.length > this.MAX_CN_LENGTH) ||
            (!new RegExp('/^[\u4e00-\u9fa5]+$/').test(o7) && o7.length > this.MAX_EN_LENGTH)) {
            return false;
        }
        return true;
    }

    dragTraverseNodeDF(i7, j7 = this._root, k7) {
        let l7 = [];
        let m7 = false;
        l7.unshift(j7);
        let n7 = l7.shift();
        while (!m7 && n7) {
            m7 = i7(n7, k7) === true;
            if (!m7) {
                l7.unshift(...n7.children);
                n7 = l7.shift();
            }
        }
    }

    updateChildIndexOfParent(f7, g7) {
        for (let h7 = f7; h7 < g7.children.length; h7++) {
            g7.children[h7].indexOfParent += 1;
        }
    }

    addDragNode(w6, x6, y6, z6, a7) {
        if (this._root === null) {
            this._root = new NodeItem(emptyNodeInfo);
            this._root.nodeLevel = this.INITIAL_INVALID_VALUE;
        }
        if (this.nodeIdNodeItemMap.has(w6)) {
            let b7 = this.nodeIdNodeItemMap.get(w6);
            let c7 = new NodeItem(a7);
            if (b7.nodeLevel > this.maxNodeLevel) {
                hilog.error(LOG_CODE, TAG, 'addDragNode: The level of the tree view cannot exceed 50.');
                return false;
            }
            c7.nodeLevel = b7.nodeLevel + 1;
            c7.parentNodeId = w6;
            c7.currentNodeId = x6;
            a7.parentNodeId = w6;
            a7.currentNodeId = x6;
            let d7 = this.INITIAL_INVALID_VALUE;
            if (b7.children.length) {
                for (let e7 = 0; e7 < b7.children.length; e7++) {
                    if (b7.children[e7].getCurrentNodeId() === y6) {
                        d7 = e7;
                        break;
                    }
                }
                if (z6) {
                    c7.indexOfParent = d7 + 1;
                    this.updateChildIndexOfParent(c7.indexOfParent, b7);
                    b7.children.splice(d7 + 1, 0, c7);
                } else {
                    c7.indexOfParent = d7 < 0 ? b7.children.length + d7 : d7;
                    this.updateChildIndexOfParent(c7.indexOfParent, b7);
                    b7.children.splice(d7, 0, c7);
                }
            } else {
                c7.indexOfParent = b7.children.length;
                b7.children.push(c7);
            }
            b7.getChildNodeInfo().isHasChildNode = true;
            b7.getChildNodeInfo().childNum = b7.children.length;
            b7.getChildNodeInfo().allChildNum += 1;
            this.updateParentChildNum(b7, true, 1);
            this.nodeIdNodeItemMap.set(x6, c7);
            this.nodeIdNodeParamMap.set(x6, a7);
            return true;
        } else {
            hilog.error(LOG_CODE, TAG, 'addDragNode: Parent node not found.');
            return false;
        }
    }
}

class ButtonGestureModifier {
    constructor(v6) {
        this.fontSize = 1;
        this.controller = null;
        this.controller = v6;
    }

    applyGesture(u6) {
        if (this.fontSize >= ButtonGestureModifier.minFontSize) {
            u6.addGesture(new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime })
                .onAction(() => {
                    if (u6) {
                        this.controller?.open();
                    }
                })
                .onActionEnd(() => {
                    this.controller?.close();
                }));
        } else {
            u6.clearGestures();
        }
    }
}

ButtonGestureModifier.longPressTime = 500;
ButtonGestureModifier.minFontSize = 1.75;

export class TreeViewInner extends ViewPU {
    constructor(o6, p6, q6, r6 = -1, s6 = undefined, t6) {
        super(o6, q6, r6, t6);
        if (typeof s6 === 'function') {
            this.paramsGenerator_ = s6;
        }
        this.__item = new SynchedPropertyNesedObjectPU(p6.item, this, 'item');
        this.listNodeDataSource = new ListNodeDataSource();
        this.__columnWidth = new ObservedPropertySimplePU(0, this, 'columnWidth');
        this.__isFocused = new ObservedPropertySimplePU(false, this, 'isFocused');
        this.__index = new ObservedPropertySimplePU(-1, this, 'index');
        this.__lastIndex = new ObservedPropertySimplePU(-1, this, 'lastIndex');
        this.__count = new ObservedPropertySimplePU(0, this, 'count');
        this.__followingSystemFontScale = new ObservedPropertySimplePU(false, this, 'followingSystemFontScale');
        this.__maxAppFontScale = new ObservedPropertySimplePU(1, this, 'maxAppFontScale');
        this.__treeViewTheme = this.initializeConsume('treeViewTheme', 'treeViewTheme');
        this.__clickButtonFlag = this.initializeConsume('clickButtonFlag', 'clickButtonFlag');
        this.__accessibilityNodeType = this.initializeConsume('accessibilityNodeType', 'accessibilityNodeType');
        this.__isAccessibilityEnabled = this.initializeConsume('isAccessibilityEnabled', 'isAccessibilityEnabled');
        this.listTreeViewMenu = undefined;
        this.callBackClick = () => {
        };
        this.MAX_CN_LENGTH = 254;
        this.MAX_EN_LENGTH = 255;
        this.INITIAL_INVALID_VALUE = -1;
        this.MAX_TOUCH_DOWN_COUNT = 0;
        this.isMultiPress = false;
        this.touchDownCount = this.INITIAL_INVALID_VALUE;
        this.appEventBus = TreeListenerManager.getInstance().getTreeListener();
        this.itemPadding = {
            left: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_card_margin_start'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            },
            right: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_card_margin_end'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            },
            top: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_margin_vertical'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            },
            bottom: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level0'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            },
        };
        this.textInputPadding = {
            left: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level0'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            },
            right: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level0'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            },
            top: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level0'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            },
            bottom: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level0'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            },
        };
        this.inputFontSize = resourceManager.getSystemResourceManager().getNumberByName('ohos_id_text_size_body1');
        this.setInitiallyProvidedValue(p6);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(n6) {
        this.__item.set(n6.item);
        if (n6.listNodeDataSource !== undefined) {
            this.listNodeDataSource = n6.listNodeDataSource;
        }
        if (n6.columnWidth !== undefined) {
            this.columnWidth = n6.columnWidth;
        }
        if (n6.isFocused !== undefined) {
            this.isFocused = n6.isFocused;
        }
        if (n6.index !== undefined) {
            this.index = n6.index;
        }
        if (n6.lastIndex !== undefined) {
            this.lastIndex = n6.lastIndex;
        }
        if (n6.count !== undefined) {
            this.count = n6.count;
        }
        if (n6.followingSystemFontScale !== undefined) {
            this.followingSystemFontScale = n6.followingSystemFontScale;
        }
        if (n6.maxAppFontScale !== undefined) {
            this.maxAppFontScale = n6.maxAppFontScale;
        }
        if (n6.listTreeViewMenu !== undefined) {
            this.listTreeViewMenu = n6.listTreeViewMenu;
        }
        if (n6.callBackClick !== undefined) {
            this.callBackClick = n6.callBackClick;
        }
        if (n6.MAX_CN_LENGTH !== undefined) {
            this.MAX_CN_LENGTH = n6.MAX_CN_LENGTH;
        }
        if (n6.MAX_EN_LENGTH !== undefined) {
            this.MAX_EN_LENGTH = n6.MAX_EN_LENGTH;
        }
        if (n6.INITIAL_INVALID_VALUE !== undefined) {
            this.INITIAL_INVALID_VALUE = n6.INITIAL_INVALID_VALUE;
        }
        if (n6.MAX_TOUCH_DOWN_COUNT !== undefined) {
            this.MAX_TOUCH_DOWN_COUNT = n6.MAX_TOUCH_DOWN_COUNT;
        }
        if (n6.isMultiPress !== undefined) {
            this.isMultiPress = n6.isMultiPress;
        }
        if (n6.touchDownCount !== undefined) {
            this.touchDownCount = n6.touchDownCount;
        }
        if (n6.appEventBus !== undefined) {
            this.appEventBus = n6.appEventBus;
        }
        if (n6.itemPadding !== undefined) {
            this.itemPadding = n6.itemPadding;
        }
        if (n6.textInputPadding !== undefined) {
            this.textInputPadding = n6.textInputPadding;
        }
        if (n6.inputFontSize !== undefined) {
            this.inputFontSize = n6.inputFontSize;
        }
    }

    updateStateVars(m6) {
        this.__item.set(m6.item);
    }

    purgeVariableDependenciesOnElmtId(l6) {
        this.__item.purgeDependencyOnElmtId(l6);
        this.__columnWidth.purgeDependencyOnElmtId(l6);
        this.__isFocused.purgeDependencyOnElmtId(l6);
        this.__index.purgeDependencyOnElmtId(l6);
        this.__lastIndex.purgeDependencyOnElmtId(l6);
        this.__count.purgeDependencyOnElmtId(l6);
        this.__followingSystemFontScale.purgeDependencyOnElmtId(l6);
        this.__maxAppFontScale.purgeDependencyOnElmtId(l6);
        this.__treeViewTheme.purgeDependencyOnElmtId(l6);
        this.__clickButtonFlag.purgeDependencyOnElmtId(l6);
        this.__accessibilityNodeType.purgeDependencyOnElmtId(l6);
        this.__isAccessibilityEnabled.purgeDependencyOnElmtId(l6);
    }

    aboutToBeDeleted() {
        this.__item.aboutToBeDeleted();
        this.__columnWidth.aboutToBeDeleted();
        this.__isFocused.aboutToBeDeleted();
        this.__index.aboutToBeDeleted();
        this.__lastIndex.aboutToBeDeleted();
        this.__count.aboutToBeDeleted();
        this.__followingSystemFontScale.aboutToBeDeleted();
        this.__maxAppFontScale.aboutToBeDeleted();
        this.__treeViewTheme.aboutToBeDeleted();
        this.__clickButtonFlag.aboutToBeDeleted();
        this.__accessibilityNodeType.aboutToBeDeleted();
        this.__isAccessibilityEnabled.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get item() {
        return this.__item.get();
    }

    get columnWidth() {
        return this.__columnWidth.get();
    }

    set columnWidth(k6) {
        this.__columnWidth.set(k6);
    }

    get isFocused() {
        return this.__isFocused.get();
    }

    set isFocused(j6) {
        this.__isFocused.set(j6);
    }

    get index() {
        return this.__index.get();
    }

    set index(i6) {
        this.__index.set(i6);
    }

    get lastIndex() {
        return this.__lastIndex.get();
    }

    set lastIndex(h6) {
        this.__lastIndex.set(h6);
    }

    get count() {
        return this.__count.get();
    }

    set count(g6) {
        this.__count.set(g6);
    }

    get followingSystemFontScale() {
        return this.__followingSystemFontScale.get();
    }

    set followingSystemFontScale(f6) {
        this.__followingSystemFontScale.set(f6);
    }

    get maxAppFontScale() {
        return this.__maxAppFontScale.get();
    }

    set maxAppFontScale(e6) {
        this.__maxAppFontScale.set(e6);
    }

    get treeViewTheme() {
        return this.__treeViewTheme.get();
    }

    set treeViewTheme(d6) {
        this.__treeViewTheme.set(d6);
    }

    get clickButtonFlag() {
        return this.__clickButtonFlag.get();
    }

    set clickButtonFlag(c6) {
        this.__clickButtonFlag.set(c6);
    }

    get accessibilityNodeType() {
        return this.__accessibilityNodeType.get();
    }

    set accessibilityNodeType(b6) {
        this.__accessibilityNodeType.set(b6);
    }

    get isAccessibilityEnabled() {
        return this.__isAccessibilityEnabled.get();
    }

    set isAccessibilityEnabled(a6) {
        this.__isAccessibilityEnabled.set(a6);
    }

    aboutToAppear() {
        if (this.item.getNodeItem().imageNode) {
            this.item.imageSource = this.item.getNodeItem().imageNode?.source;
            this.item.symbolSource = this.item.getNodeItem().imageNode?.symbolSource;
        }
        let z5 = this.getUIContext();
        this.followingSystemFontScale = z5.isFollowingSystemFontScale();
        this.maxAppFontScale = z5.getMaxFontScale();
    }

    decideFontScale() {
        let x5 = this.getUIContext();
        let y5 = x5.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.followingSystemFontScale) {
            return 1;
        }
        return Math.min(y5, this.maxAppFontScale, MAX_FONT_SCALE);
    }

    decideSymbolFontScale(t5) {
        if (!t5 || !this.followingSystemFontScale) {
            return 1;
        }
        let u5 = this.getUIContext();
        let v5 = u5.getHostContext()?.config?.fontSizeScale ?? 1;
        let w5 = Math.min(v5, this.maxAppFontScale, MAX_SYMBOL_FONT_SCALE);
        return Math.max(w5, MIN_SYMBOL_FONT_SCALE);
    }

    getInputTextMaxFontSize() {
        let s5 = this.decideFontScale() * this.inputFontSize + 'vp';
        return s5;
    }

    getLeftIconColor() {
        if (this.item.getIsModify() || this.item.getIsHighLight()) {
            return {
                'id': -1,
                'type': 10001,
                params: ['sys.color.icon_on_primary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
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
                'moduleName': '__harDefaultModuleName__',
            };
        } else if (this.item.getIsSelected()) {
            return this.treeViewTheme.primaryTitleActiveFontColor;
        } else {
            return this.treeViewTheme.primaryTitleFontColor;
        }
    }

    checkInvalidPattern(r5) {
        return new RegExp('/[\\\/:*?" < > |]/').test(r5);
    }

    checkIsAllCN(q5) {
        return new RegExp('/^[\u4e00-\u9fa5]+$/').test(q5);
    }

    getAccessibilityReadText(z4) {
        let a5 = this.listNodeDataSource.nodeIdNodeItemMap.get(z4);
        if (a5 === undefined || z4 === undefined) {
            return '';
        }
        let b5 = this.listNodeDataSource.getNodeInfoByNodeItem(a5);
        let c5 = b5?.getNodeInfoData()?.primaryTitle === undefined
            ? '' : b5?.getNodeInfoData()?.primaryTitle;
        let d5 = b5?.getNodeInfoData()?.secondaryTitle === undefined
            ? '' : b5?.getNodeInfoData()?.secondaryTitle;
        let e5 = this.listNodeDataSource.getAccessibleTitleText(c5);
        let f5 = this.listNodeDataSource.getAccessibleTitleText(d5);
        let g5 = `${e5}, ${f5}`;
        let h5 = this.listNodeDataSource.findParentNodeId(z4);
        let i5 = [];
        let j5 = 0;
        let k5 = this.listNodeDataSource.getClickNodeChildrenInfo(h5);
        let l5 = k5.map(p5 => p5.itemId);
        let m5 = l5.indexOf(z4) + 1;
        let n5 = this.listNodeDataSource.getAccessibleTitle(z4);
        if (n5 === undefined) {
            return ' ';
        }
        if (this.accessibilityNodeType === AccessibilityNodeType.PLACE) {
            if (this.listNodeDataSource.findParentNodeId(z4) === -1) {
                for (let o5 = 0; o5 < this.listNodeDataSource.listNode.length; o5++) {
                    if (this.listNodeDataSource.listNode[o5].getNodeParentNodeId() === -1) {
                        i5.push(this.listNodeDataSource.listNode[o5].getNodeCurrentNodeId());
                    }
                }
                j5 = i5.indexOf(z4) + 1;
                return this.listNodeDataSource.getStringByName('treeview_accessibility_place_node_parent', j5);
            } else {
                return this.listNodeDataSource.getStringByName('treeview_accessibility_place_node_child', n5, m5);
            }
        } else if (this.accessibilityNodeType === AccessibilityNodeType.LIFT) {
            return g5;
        } else {
            return g5;
        }
    }

    getAccessibilityDescription() {
        if (this.accessibilityNodeType === AccessibilityNodeType.TEXT) {
            return this.listNodeDataSource.getStringByName('treeview_accessibility_node_desc');
        } else {
            return ' ';
        }
    }

    getAccessibilityReadButtonText(y4) {
        if (this.clickButtonFlag === false) {
            return this.item.getNodeItem().imageCollapse?.collapseSource === ARROW_RIGHT
                ? this.listNodeDataSource.getStringByName('treeview_accessibility_folded_node')
                : this.listNodeDataSource.getStringByName('treeview_accessibility_expanded_node');
        } else {
            return y4 ? this.listNodeDataSource.getStringByName('treeview_accessibility_expand_node')
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

    onTouchNode(v4) {
        this.count++;
        if (this.count > 1) {
            this.count--;
            return;
        }
        this.index = this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId());
        this.listNodeDataSource.setClickIndex(this.index);
        let w4 = this.item.getNodeCurrentNodeId();
        if (v4.type === TouchType.Down) {
            this.item.setNodeColor(this.treeViewTheme.itemPressedBgColor);
        } else if (v4.type === TouchType.Up) {
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
            let x4 = { currentNodeId: w4 };
            this.appEventBus.emit(TreeListenType.NODE_CLICK, x4);
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
        let t4 = this.item.getNodeCurrentNodeId();
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
        let u4 = { currentNodeId: t4 };
        this.appEventBus.emit(TreeListenType.NODE_CLICK, u4);
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
        let s4 = ({
            type: 'requestFocusForAccessibility',
            bundleName: getContext()?.abilityInfo?.bundleName,
            triggerAction: 'common',
            customId: `treeView_button${this.item.getNodeCurrentNodeId()}`
        });
        accessibility.sendAccessibilityEvent(s4).then(() => {
            setTimeout(() => {
                this.clickButtonFlag = true;
            }, ENTER_EXIT_DURATION);
        });
    }

    popupForShowTitle(k4, l4, m4, n4 = null) {
        this.observeComponentCreation2((q4, r4) => {
            Row.create();
            Row.backgroundColor(l4);
            Row.border({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_elements_margin_horizontal_l'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                }
            });
            Row.padding({
                left: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_elements_margin_horizontal_l'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                },
                right: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_elements_margin_horizontal_l'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                },
                top: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_card_margin_middle'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                },
                bottom: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_card_margin_middle'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                },
            });
        }, Row);
        this.observeComponentCreation2((o4, p4) => {
            Text.create(k4);
            Text.fontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_body2'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            });
            Text.fontWeight('regular');
            Text.fontColor(m4);
            Text.minFontScale(MIN_FONT_SCALE);
            Text.maxFontScale(this.decideFontScale());
        }, Text);
        Text.pop();
        Row.pop();
    }

    builder(h4 = null) {
        this.observeComponentCreation2((i4, j4) => {
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
        this.observeComponentCreation2((q1, r1) => {
            If.create();
            if (this.item.getNodeIsShow()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((f4, g4) => {
                        Stack.create();
                        ViewStackProcessor.visualState('focused');
                        Stack.border({
                            radius: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.ohos_id_corner_radius_clicked'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__',
                            },
                            width: FLAG_NUMBER,
                            color: this.treeViewTheme.borderFocusedColor,
                            style: BorderStyle.Solid,
                        });
                        ViewStackProcessor.visualState('normal');
                        Stack.border({
                            radius: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.ohos_id_corner_radius_clicked'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__',
                            },
                            width: 0,
                        });
                        ViewStackProcessor.visualState();
                    }, Stack);
                    this.observeComponentCreation2((w3, x3) => {
                        Column.create();
                        Column.opacity(this.listNodeDataSource.getListItemOpacity(ObservedObject.GetRawObject(this.item)));
                        Column.onHover((e4) => {
                            if (e4) {
                                this.item.setNodeColor(this.treeViewTheme.itemHoverBgColor);
                            } else {
                                this.item.setNodeColor({
                                    'id': -1,
                                    'type': 10001,
                                    params: ['sys.color.ohos_id_color_background_transparent'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__',
                                });
                            }
                        });
                        Column.onTouch(this.isAccessibilityEnabled ? undefined : (d4) => {
                            this.onTouchNode(d4);
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
                        Column.onMouse((b4) => {
                            let c4 = this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId());
                            if (b4.button === MouseButton.Right) {
                                this.listNodeDataSource.handleEvent(Event.MOUSE_BUTTON_RIGHT,
                                    this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId()));
                                this.listTreeViewMenu = this.item.getMenu();
                                this.listNodeDataSource.setClickIndex(c4);
                                clearTimeout(this.item.getNodeItem().mainTitleNode?.popUpTimeout);
                            }
                            b4.stopPropagation();
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
                        Column.onAreaChange((y3, z3) => {
                            let a4 = Number.parseInt(z3.width.toString());
                            this.columnWidth = a4;
                        });
                    }, Column);
                    this.observeComponentCreation2((u3, v3) => {
                        Stack.create({ alignContent: Alignment.Bottom });
                        Stack.focusable(true);
                    }, Stack);
                    this.observeComponentCreation2((s3, t3) => {
                        Divider.create();
                        Divider.height(this.listNodeDataSource.getFlagLine().flagLineHeight);
                        Divider.color(this.listNodeDataSource.getFlagLine().flagLineColor);
                        Divider.visibility(this.listNodeDataSource.getVisibility(ObservedObject.GetRawObject(this.item)));
                        Divider.lineCap(LineCapStyle.Round);
                        Divider.margin({ start: LengthMetrics.vp(this.item.getFlagLineLeftMargin()) });
                        Divider.focusable(true);
                    }, Divider);
                    this.observeComponentCreation2((q3, r3) => {
                        Row.create({});
                        Row.focusable(true);
                        Row.width('100%');
                        Row.height(this.item.getNodeHeight());
                        Row.padding({ start: LengthMetrics.vp(this.item.getNodeLeftPadding()) });
                        Row.bindContextMenu({ builder: this.builder.bind(this) }, ResponseType.RightClick);
                    }, Row);
                    this.observeComponentCreation2((o3, p3) => {
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
                    this.observeComponentCreation2((a3, b3) => {
                        If.create();
                        if (this.item.getNodeItem().imageNode) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((m3, n3) => {
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
                                this.observeComponentCreation2((c3, d3) => {
                                    If.create();
                                    if (this.item.symbolSource) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((k3, l3) => {
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
                                            this.observeComponentCreation2((e3, f3) => {
                                                If.create();
                                                if (Util.isSymbolResource(this.item.imageSource)) {
                                                    this.ifElseBranchUpdateFunction(0, () => {
                                                        this.observeComponentCreation2((i3, j3) => {
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
                                                        this.observeComponentCreation2((g3, h3) => {
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
                    this.observeComponentCreation2((y2, z2) => {
                        Row.create();
                        Row.layoutWeight(1);
                        Row.focusable(true);
                    }, Row);
                    this.observeComponentCreation2((u2, v2) => {
                        If.create();
                        if (this.item.getNodeItem().mainTitleNode && this.item.getIsShowTitle()) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((w2, x2) => {
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
                    this.observeComponentCreation2((g2, h2) => {
                        If.create();
                        if (this.item.getNodeItem().mainTitleNode && this.item.getNodeItem().inputText &&
                        this.item.getIsShowInputText()) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((s2, t2) => {
                                    Row.create();
                                    Row.backgroundColor(this.item.getNodeItem().inputText?.backgroundColor);
                                    Row.borderRadius(this.item.getNodeItem().inputText?.borderRadius);
                                    Row.margin({
                                        end: getLengthMetricsByResourceOrNumber(this.item.getNodeItem()
                                            .inputText?.itemRightMargin)
                                    });
                                }, Row);
                                this.observeComponentCreation2((i2, j2) => {
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
                                    TextInput.onChange((m2) => {
                                        let n2 = this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId());
                                        let o2 = '';
                                        let p2 = false;
                                        let q2 = false;
                                        if (this.checkInvalidPattern(m2)) {
                                            for (let r2 = 0; r2 < m2.length; r2++) {
                                                if (!this.checkInvalidPattern(m2[r2])) {
                                                    o2 += m2[r2];
                                                }
                                            }
                                            p2 = true;
                                            this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS,
                                                InputError.INVALID_ERROR, true, n2);
                                        } else {
                                            o2 = m2;
                                            p2 = false;
                                        }
                                        if ((this.checkIsAllCN(o2) && o2.length > this.MAX_CN_LENGTH) ||
                                            (!this.checkIsAllCN(o2) && o2.length > this.MAX_EN_LENGTH)) {
                                            o2 = this.checkIsAllCN(o2) ?
                                            o2.substr(0, this.MAX_CN_LENGTH) : o2.substr(0, this.MAX_EN_LENGTH);
                                            q2 = true;
                                            this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS,
                                                InputError.LENGTH_ERROR, true, n2);
                                        } else {
                                            q2 = false;
                                        }
                                        if (!q2 && !p2) {
                                            this.listNodeDataSource.setMainTitleNameOnEdit(n2, o2);
                                        }
                                    });
                                    TextInput.onSubmit((k2) => {
                                        let l2 = this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId());
                                        this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false,
                                            l2);
                                        this.listNodeDataSource.setItemVisibilityOnEdit(l2, MenuOperation.COMMIT_NODE);
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
                    this.observeComponentCreation2((e2, f2) => {
                        Blank.create();
                    }, Blank);
                    Blank.pop();
                    Row.pop();
                    this.observeComponentCreation2((y1, z1) => {
                        If.create();
                        if (this.listNodeDataSource.hasSubtitle(this.item.getNodeCurrentNodeId())) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((c2, d2) => {
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
                                            'moduleName': '__harDefaultModuleName__',
                                        }) :
                                        LengthMetrics.resource(this.listNodeDataSource.getSubTitlePara().margin.right)
                                    });
                                }, Row);
                                this.observeComponentCreation2((a2, b2) => {
                                    Text.create(this.listNodeDataSource.getSubtitle(this.item.getNodeCurrentNodeId()));
                                    Text.minFontScale(MIN_FONT_SCALE);
                                    Text.maxFontScale(this.decideFontScale());
                                    Text.fontSize(this.listNodeDataSource.getSubTitlePara().fontSize);
                                    Text.fontColor(this.item.getIsHighLight() || this.item.getIsModify() ? {
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_primary_contrary'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
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
                    this.observeComponentCreation2((s1, t1) => {
                        If.create();
                        if (this.item.getNodeItem().imageCollapse) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                if (!If.canRetake(`treeView_button${this.item.getNodeCurrentNodeId()}`)) {
                                    this.observeComponentCreation2((w1, x1) => {
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
                                    this.observeComponentCreation2((u1, v1) => {
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

    rerender() {
        this.updateDirtyElements();
    }
}

export class NodeItem {
    constructor(p1) {
        this.currentNodeId = p1.currentNodeId ?? -1;
        this.parentNodeId = p1.parentNodeId ?? -1;
        this.isFolder = p1.isFolder;
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

    set itemWidth(o1) {
        this.width = o1;
    }

    get itemWidth() {
        return this.width;
    }

    set itemHeight(n1) {
        this.height = n1;
    }

    get itemHeight() {
        return this.height;
    }

    set itemRightMargin(m1) {
        this.rightMargin = m1;
    }

    get itemRightMargin() {
        return this.rightMargin;
    }
}

export class CollapseImageNode extends NodeBaseInfo {
    constructor(e1, f1, g1, h1, i1, j1, k1, l1) {
        super();
        this.rightMargin = {
            'id': -1,
            'type': 10002,
            params: ['sys.float.ohos_id_elements_margin_horizontal_m'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.imageSource = e1;
        this.symbolIconSource = f1;
        this.rightMargin = j1;
        this.imageOpacity = g1;
        this.itemWidth = h1;
        this.itemHeight = i1;
        this.imageCollapseSource = e1;
        this.symbolIconCollapseSource = f1;
        this.isImageCollapse = k1;
        this.collapseImageType = l1;
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

    static getInstance() {
        if (!CollapseImageNodeFactory.instance) {
            CollapseImageNodeFactory.instance = new CollapseImageNodeFactory();
        }
        return CollapseImageNodeFactory.instance;
    }

    createCollapseImageNodeByType(c1) {
        let d1;
        switch (c1) {
            case CollapseImageType.ARROW_RIGHT_WHITE:
                d1 = ARROW_RIGHT_WITHE;
                break;
            case CollapseImageType.ARROW_RIGHT:
                d1 = ARROW_RIGHT;
                break;
            case CollapseImageType.ARROW_DOWN_WHITE:
                d1 = ARROW_DOWN_WITHE;
                break;
            default:
                d1 = ARROW_DOWN;
        }
        return new CollapseImageNode(d1, undefined, {
            'id': -1,
            'type': 10002,
            params: ['sys.float.ohos_id_alpha_content_tertiary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        }, IMAGE_NODE_HEIGHT, IMAGE_NODE_WIDTH, {
            'id': -1,
            'type': 10002,
            params: ['sys.float.ohos_id_text_paragraph_margin_xs'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        }, (c1 === CollapseImageType.ARROW_RIGHT_WHITE || c1 === CollapseImageType.ARROW_DOWN_WHITE) ? false : true,
            c1);
    }
}

class CollapseImageNodeFlyweightFactory {
    static getCollapseImageNodeByType(a1) {
        let b1 = CollapseImageNodeFlyweightFactory.nodeMap.get(a1);
        if (b1 === undefined) {
            b1 = CollapseImageNodeFactory.getInstance().createCollapseImageNodeByType(a1);
            CollapseImageNodeFlyweightFactory.nodeMap.set(a1, b1);
        }
        return b1;
    }

    static getCollapseImageNode(w, x, y) {
        if (y === undefined) {
            return undefined;
        }
        let z = y;
        if (w == InteractionStatus.EDIT ||
            w === InteractionStatus.DRAG_INSERT) {
            if (x === NodeStatus.COLLAPSE) {
                z = CollapseImageType.ARROW_RIGHT_WHITE;
            } else {
                z = CollapseImageType.ARROW_DOWN_WHITE;
            }
        } else if (w === InteractionStatus.FINISH_EDIT ||
            w === InteractionStatus.FINISH_DRAG_INSERT) {
            if (x === NodeStatus.COLLAPSE) {
                z = CollapseImageType.ARROW_RIGHT;
            } else {
                z = CollapseImageType.ARROW_DOWN;
            }
        }
        return CollapseImageNodeFlyweightFactory.getCollapseImageNodeByType(z);
    }

    static changeImageCollapseSource(t, u) {
        if (u === undefined) {
            return undefined;
        }
        let v;
        if (!u) {
            if (t === NodeStatus.COLLAPSE) {
                v = CollapseImageType.ARROW_RIGHT_WHITE;
            } else {
                v = CollapseImageType.ARROW_DOWN_WHITE;
            }
        } else {
            if (t === NodeStatus.COLLAPSE) {
                v = CollapseImageType.ARROW_RIGHT;
            } else {
                v = CollapseImageType.ARROW_DOWN;
            }
        }
        return CollapseImageNodeFlyweightFactory.getCollapseImageNodeByType(v);
    }
}

CollapseImageNodeFlyweightFactory.nodeMap = new Map();

export class ImageNode extends NodeBaseInfo {
    constructor(k, l, m, n, o, p, q, r, s) {
        super();
        this.rightMargin = {
            'id': -1,
            'type': 10002,
            params: ['sys.float.ohos_id_elements_margin_horizontal_m'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.imageSource = k;
        this.symbolIconSource = l;
        this.imageNormalSource = k;
        this.symbolIconNormalSource = l;
        if (p !== undefined) {
            this.imageSelectedSource = p;
        } else {
            this.imageSelectedSource = this.imageNormalSource;
        }
        this.symbolIconSelectedSource = q;
        if (r !== undefined) {
            this.imageEditSource = r;
        } else {
            this.imageEditSource = this.imageNormalSource;
        }
        this.symbolIconEditSource = s;
        this.imageOpacity = m;
        this.itemWidth = n;
        this.itemHeight = o;
        this.imageCollapseSource = k;
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

    changeImageCollapseSource(j) {
        if (j === NodeStatus.EXPAND) {
            this.imageCollapseSource = this.imageCollapseDownSource;
        } else if (j === NodeStatus.COLLAPSE) {
            this.imageCollapseSource = this.imageCollapseRightSource;
        }
    }

    setImageCollapseSource(h, i) {
        if (h === InteractionStatus.EDIT || h === InteractionStatus.DRAG_INSERT) {
            this.imageCollapseDownSource = ARROW_DOWN_WITHE;
            this.imageCollapseRightSource = ARROW_RIGHT_WITHE;
            this.isImageCollapse = false;
        } else if (h === InteractionStatus.FINISH_EDIT ||
            h === InteractionStatus.FINISH_DRAG_INSERT) {
            this.imageCollapseDownSource = ARROW_DOWN;
            this.imageCollapseRightSource = ARROW_RIGHT;
            this.isImageCollapse = true;
        }
        this.imageCollapseSource = (i === NodeStatus.COLLAPSE) ?
        this.imageCollapseRightSource : this.imageCollapseDownSource;
    }

    setImageSource(g) {
        switch (g) {
            case InteractionStatus.NORMAL:
                this.imageSource = this.imageNormalSource;
                this.symbolIconSource = this.symbolIconNormalSource;
                this.currentInteractionStatus = g;
                break;
            case InteractionStatus.SELECTED:
                if (this.currentInteractionStatus !== InteractionStatus.EDIT) {
                    this.imageSource = this.imageSelectedSource;
                    this.symbolIconSource = this.symbolIconSelectedSource;
                    this.currentInteractionStatus = g;
                }
                break;
            case InteractionStatus.EDIT:
                this.imageSource = this.imageEditSource;
                this.symbolIconSource = this.symbolIconEditSource;
                this.currentInteractionStatus = g;
                break;
            case InteractionStatus.FINISH_EDIT:
                this.imageSource = this.imageSelectedSource;
                this.symbolIconSource = this.symbolIconSelectedSource;
                this.currentInteractionStatus = g;
                break;
            case InteractionStatus.DRAG_INSERT:
                this.imageSource = this.imageEditSource;
                this.symbolIconSource = this.symbolIconEditSource;
                this.currentInteractionStatus = g;
                break;
            case InteractionStatus.FINISH_DRAG_INSERT:
                this.imageSource = this.imageNormalSource;
                this.symbolIconSource = this.symbolIconNormalSource;
                this.currentInteractionStatus = g;
                break;
            default:
                break;
        }
    }
}

class MainTitleNode extends NodeBaseInfo {
    constructor(f) {
        super();
        this.treeViewTheme = TreeViewTheme.getInstance();
        this.mainTitleName = f;
        this.itemWidth = ITEM_WIDTH;
        this.itemHeight = ITEM_HEIGHT;
        this.rightMargin = {
            'id': -1,
            'type': 10002,
            params: ['sys.float.ohos_id_text_paragraph_margin_xs'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.mainTitleSetting = {
            fontColor: this.treeViewTheme.primaryTitleFontColor,
            fontSize: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_body1'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            },
            fontWeight: FontWeight.Normal,
        };
        this.showPopUpTimeout = 0;
    }

    setMainTitleSelected(e) {
        if (e) {
            this.mainTitleSetting = {
                fontColor: this.treeViewTheme.primaryTitleActiveFontColor,
                fontSize: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_text_size_body1'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
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
                    'moduleName': '__harDefaultModuleName__',
                },
                fontWeight: FontWeight.Normal,
            };
        }
    }

    set title(d) {
        this.mainTitleName = d;
    }

    get title() {
        return this.mainTitleName;
    }

    set popUpTimeout(c) {
        this.showPopUpTimeout = c;
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

    setMainTitleHighLight(b) {
        if (b) {
            this.mainTitleSetting = {
                fontColor: this.treeViewTheme.primaryTitleActiveFontColor,
                fontSize: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_text_size_body1'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
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
                    'moduleName': '__harDefaultModuleName__',
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
            'moduleName': '__harDefaultModuleName__',
        };
        this.editItemColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_emphasize'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.radius = {
            'id': -1,
            'type': 10002,
            params: ['sys.float.ohos_id_corner_radius_default_xs'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.treeViewTheme = TreeViewTheme.getInstance();
        this.itemWidth = ITEM_WIDTH;
        this.itemHeight = ITEM_HEIGHT_INPUT;
        this.rightMargin = {
            'id': -1,
            'type': 10002,
            params: ['sys.float.ohos_id_text_paragraph_margin_xs'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.inputTextSetting = {
            fontColor: this.treeViewTheme.primaryTitleFontColor,
            fontSize: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_body1'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
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

function getLengthMetricsByResourceOrNumber(a) {
    if (!a) {
        return LengthMetrics.vp(0);
    } else if (typeof a === 'number') {
        return LengthMetrics.vp(a);
    } else {
        return LengthMetrics.resource(a);
    }
}

export default {
    TreeController,
    TreeListener,
    TreeListenerManager,
    TreeListenType,
    TreeView,
}