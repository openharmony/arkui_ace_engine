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

var __decorate = (this && this.__decorate) || function (z34, a35, b35, c35) {
    var d35 = arguments.length,
        e35 = d35 < 3 ? a35 : c35 === null ? c35 = Object.getOwnPropertyDescriptor(a35, b35) : c35, f35;
    if (typeof Reflect === 'object' && typeof Reflect.decorate === 'function') {
        e35 = Reflect.decorate(z34, a35, b35, c35);
    } else {
        for (var g35 = z34.length - 1; g35 >= 0; g35--) {
            if (f35 = z34[g35]) {
                e35 = (d35 < 3 ? f35(e35) : d35 > 3 ? f35(a35, b35, e35) : f35(a35, b35)) || e35;
            }
        }
    }
    return d35 > 3 && e35 && Object.defineProperty(a35, b35, e35), e35;
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
const SHADOW_OFFSETY = 10;
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
const SHADOW_COLOR = '#00001E';
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
(function (x34) {
    x34[x34['TOUCH_DOWN'] = 0] = 'TOUCH_DOWN';
    x34[x34['TOUCH_UP'] = 1] = 'TOUCH_UP';
    x34[x34['HOVER'] = 3] = 'HOVER';
    x34[x34['HOVER_OVER'] = 4] = 'HOVER_OVER';
    x34[x34['FOCUS'] = 5] = 'FOCUS';
    x34[x34['BLUR'] = 6] = 'BLUR';
    x34[x34['MOUSE_BUTTON_RIGHT'] = 7] = 'MOUSE_BUTTON_RIGHT';
    x34[x34['DRAG'] = 8] = 'DRAG';
})(Event || (Event = {}));
var MenuOperation;
(function (w34) {
    w34[w34['ADD_NODE'] = 0] = 'ADD_NODE';
    w34[w34['REMOVE_NODE'] = 1] = 'REMOVE_NODE';
    w34[w34['MODIFY_NODE'] = 2] = 'MODIFY_NODE';
    w34[w34['COMMIT_NODE'] = 3] = 'COMMIT_NODE';
})(MenuOperation || (MenuOperation = {}));
var PopUpType;
(function (v34) {
    v34[v34['HINTS'] = 0] = 'HINTS';
    v34[v34['WARNINGS'] = 1] = 'WARNINGS';
})(PopUpType || (PopUpType = {}));
var InputError;
(function (u34) {
    u34[u34['INVALID_ERROR'] = 0] = 'INVALID_ERROR';
    u34[u34['LENGTH_ERROR'] = 1] = 'LENGTH_ERROR';
    u34[u34['NONE'] = 2] = 'NONE';
})(InputError || (InputError = {}));
var Flag;
(function (t34) {
    t34[t34['DOWN_FLAG'] = 0] = 'DOWN_FLAG';
    t34[t34['UP_FLAG'] = 1] = 'UP_FLAG';
    t34[t34['NONE'] = 2] = 'NONE';
})(Flag || (Flag = {}));

export var NodeStatus;
(function (s34) {
    s34[s34['EXPAND'] = 0] = 'EXPAND';
    s34[s34['COLLAPSE'] = 1] = 'COLLAPSE';
})(NodeStatus || (NodeStatus = {}));

export var InteractionStatus;
(function (r34) {
    r34[r34['NORMAL'] = 0] = 'NORMAL';
    r34[r34['SELECTED'] = 1] = 'SELECTED';
    r34[r34['EDIT'] = 2] = 'EDIT';
    r34[r34['FINISH_EDIT'] = 3] = 'FINISH_EDIT';
    r34[r34['DRAG_INSERT'] = 4] = 'DRAG_INSERT';
    r34[r34['FINISH_DRAG_INSERT'] = 5] = 'FINISH_DRAG_INSERT';
})(InteractionStatus || (InteractionStatus = {}));
var CollapseImageType;
(function (q34) {
    q34[q34['ARROW_DOWN'] = 0] = 'ARROW_DOWN';
    q34[q34['ARROW_RIGHT'] = 1] = 'ARROW_RIGHT';
    q34[q34['ARROW_DOWN_WHITE'] = 2] = 'ARROW_DOWN_WHITE';
    q34[q34['ARROW_RIGHT_WHITE'] = 3] = 'ARROW_RIGHT_WHITE';
})(CollapseImageType || (CollapseImageType = {}));
var AccessibilityNodeType;
(function (p34) {
    p34[p34['TEXT'] = 0] = 'TEXT';
    p34[p34['PLACE'] = 1] = 'PLACE';
    p34[p34['LIFT'] = 2] = 'LIFT';
})(AccessibilityNodeType || (AccessibilityNodeType = {}));

class Util {
    static isSymbolResource(n34) {
        if (!Util.isResourceType(n34)) {
            return false;
        }
        let o34 = n34;
        return o34.type === RESOURCE_TYPE_SYMBOL;
    }

    static isResourceType(m34) {
        if (!m34) {
            return false;
        }
        if (typeof m34 === 'string' || typeof m34 === 'undefined') {
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

    createNodeByNodeParam(k34) {
        let l34 = this.createNode();
        if (k34.icon) {
            l34.imageNode = new ImageNode(k34.icon, k34.symbolIconStyle, {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_alpha_content_fourth'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            }, IMAGE_NODE_HEIGHT, IMAGE_NODE_WIDTH, k34.selectedIcon, k34.symbolSelectedIconStyle, k34.editIcon,
                k34.symbolEditIconStyle);
        }
        if (k34.primaryTitle) {
            l34.mainTitleNode = new MainTitleNode(k34.primaryTitle);
        }
        return l34;
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
    constructor(i34, j34) {
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
        this.node = i34;
        this.nodeParam = j34;
        this.nodeItemView = TreeViewNodeItemFactory.getInstance().createNodeByNodeParam(j34);
        this.popUpInfo = {
            popUpIsShow: false,
            popUpEnableArrow: false,
            popUpColor: undefined,
            popUpText: '',
            popUpTextColor: undefined,
        };
        this.nodeHeight = NODE_HEIGHT;
        this.nodeLeftPadding = i34.nodeLevel * LEVEL_MARGIN + MARGIN_OFFSET;
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
        this.flagLineLeftMargin = i34.nodeLevel * LEVEL_MARGIN + MARGIN_OFFSET;
    }

    addImageCollapse(h34) {
        if (h34) {
            this.nodeItemView.imageCollapse =
                CollapseImageNodeFlyweightFactory.getCollapseImageNodeByType(CollapseImageType.ARROW_RIGHT);
        } else {
            this.nodeItemView.imageCollapse = undefined;
        }
    }

    addImageExpand(a2) {
        if (a2) {
            this.nodeItemView.imageCollapse =
                CollapseImageNodeFlyweightFactory.getCollapseImageNodeByType(CollapseImageType.ARROW_DOWN);
        } else {
            this.nodeItemView.imageCollapse = undefined;
        }
    }

    setFontColor(g34) {
        this.fontColor = g34;
    }

    getFontColor() {
        return this.fontColor;
    }

    getPopUpInfo() {
        return this.popUpInfo;
    }

    setPopUpIsShow(f34) {
        this.popUpInfo.popUpIsShow = f34;
    }

    setPopUpEnableArrow(e34) {
        this.popUpInfo.popUpEnableArrow = e34;
    }

    setPopUpColor(d34) {
        this.popUpInfo.popUpColor = d34;
    }

    setPopUpText(c34) {
        this.popUpInfo.popUpText = c34;
    }

    setPopUpTextColor(b34) {
        this.popUpInfo.popUpTextColor = b34;
    }

    getIsShowTitle() {
        return this.isShowTitle;
    }

    getIsShowInputText() {
        return this.isShowInputText;
    }

    setTitleAndInputTextStatus(a34) {
        if (a34) {
            this.isShowTitle = false;
            this.isShowInputText = true;
        } else {
            this.isShowTitle = true;
            this.isShowInputText = false;
        }
    }

    handleImageCollapseAfterAddNode(z33) {
        if (z33) {
            this.nodeItemView.imageCollapse =
                CollapseImageNodeFlyweightFactory.getCollapseImageNodeByType(CollapseImageType.ARROW_DOWN);
        } else {
            this.nodeItemView.imageCollapse = undefined;
        }
    }

    setNodeColor(y33) {
        if (y33 === undefined) {
            return;
        }
        this.nodeColor = y33;
    }

    getNodeColor() {
        return this.nodeColor;
    }

    setListItemHeight(x33) {
        this.listItemHeight = x33;
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

    setNodeIsShow(w33) {
        this.nodeIsShow = w33;
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

    setNodeBorder(v33) {
        this.nodeBorder.borderWidth = v33 ? this.borderWidth.has : this.borderWidth.none;
    }

    getChildNodeInfo() {
        return this.node.childNodeInfo;
    }

    getMenu() {
        return this.nodeParam.container;
    }

    setIsSelected(u33) {
        this.isSelected = u33;
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

    setCanShowFlagLine(t33) {
        this.canShowFlagLine = t33;
    }

    getCanShowFlagLine() {
        return this.canShowFlagLine;
    }

    setFlagLineLeftMargin(s33) {
        if (s33 === undefined) {
            return;
        }
        this.flagLineLeftMargin = s33 * LEVEL_MARGIN + MARGIN_OFFSET;
    }

    getFlagLineLeftMargin() {
        return this.flagLineLeftMargin;
    }

    getNodeLevel() {
        return this.node.nodeLevel;
    }

    setIsOverBorder(r33) {
        this.isOverBorder = r33;
    }

    getIsOverBorder() {
        return this.isOverBorder;
    }

    setCanShowBottomFlagLine(q33) {
        this.canShowBottomFlagLine = q33;
    }

    getCanShowBottomFlagLine() {
        return this.canShowBottomFlagLine;
    }

    setIsHighLight(p33) {
        this.isHighLight = p33;
    }

    getIsHighLight() {
        return this.isHighLight;
    }

    setIsModify(o33) {
        this.isModify = o33;
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
(function (n33) {
    n33['NODE_CLICK'] = 'NodeClick';
    n33['NODE_ADD'] = 'NodeAdd';
    n33['NODE_DELETE'] = 'NodeDelete';
    n33['NODE_MODIFY'] = 'NodeModify';
    n33['NODE_MOVE'] = 'NodeMove';
})(TreeListenType || (TreeListenType = {}));

export class TreeListener {
    constructor() {
        this._events = [];
        this._once_events = [];
    }

    on(j33, k33) {
        if (Array.isArray(j33)) {
            for (let l33 = 0, m33 = j33.length; l33 < m33; l33++) {
                this.on(j33[l33], k33);
            }
        } else {
            (this._events[j33] || (this._events[j33] = [])).push(k33);
        }
    }

    once(h33, i33) {
        if (Array.isArray(h33)) {
            this.off(h33, i33);
        } else {
            (this._once_events[h33] || (this._once_events[h33] = [])).push(i33);
        }
    }

    off(a33, b33) {
        if (a33 === null) {
            this._events = [];
        }
        if (Array.isArray(a33)) {
            for (let f33 = 0, g33 = a33.length; f33 < g33; f33++) {
                this.off(a33[f33], b33);
            }
        }
        let c33 = this._events[a33];
        if (!c33) {
            return;
        }
        if (b33 === null) {
            this._events[a33] = null;
        }
        let d33 = c33.length;
        while (d33--) {
            let e33 = c33[d33];
            if (e33 === b33) {
                c33.splice(d33, 1);
                break;
            }
        }
    }

    emit(q32, r32) {
        if (this._once_events[q32]) {
            let w32 = Array.from(this._once_events[q32]);
            if (w32) {
                for (let x32 = 0, y32 = w32.length; x32 < y32; x32++) {
                    try {
                        w32[x32](r32);
                    } catch (z32) {
                        throw new Error('once function callbacks error.');
                    }
                }
                this._once_events[q32] = null;
            }
        } else if (this._events[q32]) {
            let s32 = Array.from(this._events[q32]);
            if (s32) {
                for (let t32 = 0, u32 = s32.length; t32 < u32; t32++) {
                    try {
                        s32[t32](r32);
                    } catch (v32) {
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
    constructor(k32, l32, m32, n32 = -1, o32 = undefined, p32) {
        super(k32, m32, n32, p32);
        if (typeof o32 === 'function') {
            this.paramsGenerator_ = o32;
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
        this.__isAccessibilityEnabled =
            new ObservedPropertySimplePU(accessibility.isScreenReaderOpenSync(), this, 'isAccessibilityEnabled');
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
        this.setInitiallyProvidedValue(l32);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(j32) {
        if (j32.treeController !== undefined) {
            this.treeController = j32.treeController;
        }
        if (j32.nodeList !== undefined) {
            this.nodeList = j32.nodeList;
        }
        if (j32.listNodeDataSource !== undefined) {
            this.listNodeDataSource = j32.listNodeDataSource;
        }
        if (j32.item !== undefined) {
            this.item = j32.item;
        }
        if (j32.touchCount !== undefined) {
            this.touchCount = j32.touchCount;
        }
        if (j32.dropSelectedIndex !== undefined) {
            this.dropSelectedIndex = j32.dropSelectedIndex;
        }
        if (j32.viewLastIndex !== undefined) {
            this.viewLastIndex = j32.viewLastIndex;
        }
        if (j32.followingSystemFontScale !== undefined) {
            this.followingSystemFontScale = j32.followingSystemFontScale;
        }
        if (j32.maxAppFontScale !== undefined) {
            this.maxAppFontScale = j32.maxAppFontScale;
        }
        if (j32.listItemBgColor !== undefined) {
            this.listItemBgColor = j32.listItemBgColor;
        }
        if (j32.allParentNode !== undefined) {
            this.allParentNode = j32.allParentNode;
        }
        if (j32.treeViewTheme !== undefined) {
            this.treeViewTheme = j32.treeViewTheme;
        }
        if (j32.clickButtonFlag !== undefined) {
            this.clickButtonFlag = j32.clickButtonFlag;
        }
        if (j32.accessibilityNodeType !== undefined) {
            this.accessibilityNodeType = j32.accessibilityNodeType;
        }
        if (j32.isAccessibilityEnabled !== undefined) {
            this.isAccessibilityEnabled = j32.isAccessibilityEnabled;
        }
        if (j32.listTreeViewMenu !== undefined) {
            this.listTreeViewMenu = j32.listTreeViewMenu;
        }
        if (j32.MAX_CN_LENGTH !== undefined) {
            this.MAX_CN_LENGTH = j32.MAX_CN_LENGTH;
        }
        if (j32.MAX_EN_LENGTH !== undefined) {
            this.MAX_EN_LENGTH = j32.MAX_EN_LENGTH;
        }
        if (j32.INITIAL_INVALID_VALUE !== undefined) {
            this.INITIAL_INVALID_VALUE = j32.INITIAL_INVALID_VALUE;
        }
        if (j32.MAX_TOUCH_DOWN_COUNT !== undefined) {
            this.MAX_TOUCH_DOWN_COUNT = j32.MAX_TOUCH_DOWN_COUNT;
        }
        if (j32.isMultiPress !== undefined) {
            this.isMultiPress = j32.isMultiPress;
        }
        if (j32.touchDownCount !== undefined) {
            this.touchDownCount = j32.touchDownCount;
        }
        if (j32.appEventBus !== undefined) {
            this.appEventBus = j32.appEventBus;
        }
        if (j32.itemPadding !== undefined) {
            this.itemPadding = j32.itemPadding;
        }
        if (j32.textInputPadding !== undefined) {
            this.textInputPadding = j32.textInputPadding;
        }
    }

    updateStateVars(i32) {
    }

    purgeVariableDependenciesOnElmtId(h32) {
        this.__nodeList.purgeDependencyOnElmtId(h32);
        this.__item.purgeDependencyOnElmtId(h32);
        this.__touchCount.purgeDependencyOnElmtId(h32);
        this.__dropSelectedIndex.purgeDependencyOnElmtId(h32);
        this.__viewLastIndex.purgeDependencyOnElmtId(h32);
        this.__followingSystemFontScale.purgeDependencyOnElmtId(h32);
        this.__maxAppFontScale.purgeDependencyOnElmtId(h32);
        this.__listItemBgColor.purgeDependencyOnElmtId(h32);
        this.__allParentNode.purgeDependencyOnElmtId(h32);
        this.__treeViewTheme.purgeDependencyOnElmtId(h32);
        this.__clickButtonFlag.purgeDependencyOnElmtId(h32);
        this.__accessibilityNodeType.purgeDependencyOnElmtId(h32);
        this.__isAccessibilityEnabled.purgeDependencyOnElmtId(h32);
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

    set nodeList(g32) {
        this.__nodeList.set(g32);
    }

    get item() {
        return this.__item.get();
    }

    set item(f32) {
        this.__item.set(f32);
    }

    get touchCount() {
        return this.__touchCount.get();
    }

    set touchCount(e32) {
        this.__touchCount.set(e32);
    }

    get dropSelectedIndex() {
        return this.__dropSelectedIndex.get();
    }

    set dropSelectedIndex(d32) {
        this.__dropSelectedIndex.set(d32);
    }

    get viewLastIndex() {
        return this.__viewLastIndex.get();
    }

    set viewLastIndex(c32) {
        this.__viewLastIndex.set(c32);
    }

    get followingSystemFontScale() {
        return this.__followingSystemFontScale.get();
    }

    set followingSystemFontScale(b32) {
        this.__followingSystemFontScale.set(b32);
    }

    get maxAppFontScale() {
        return this.__maxAppFontScale.get();
    }

    set maxAppFontScale(a32) {
        this.__maxAppFontScale.set(a32);
    }

    get listItemBgColor() {
        return this.__listItemBgColor.get();
    }

    set listItemBgColor(z31) {
        this.__listItemBgColor.set(z31);
    }

    get allParentNode() {
        return this.__allParentNode.get();
    }

    set allParentNode(y31) {
        this.__allParentNode.set(y31);
    }

    get treeViewTheme() {
        return this.__treeViewTheme.get();
    }

    set treeViewTheme(x31) {
        this.__treeViewTheme.set(x31);
    }

    get clickButtonFlag() {
        return this.__clickButtonFlag.get();
    }

    set clickButtonFlag(w31) {
        this.__clickButtonFlag.set(w31);
    }

    get accessibilityNodeType() {
        return this.__accessibilityNodeType.get();
    }

    set accessibilityNodeType(v31) {
        this.__accessibilityNodeType.set(v31);
    }

    get isAccessibilityEnabled() {
        return this.__isAccessibilityEnabled.get();
    }

    set isAccessibilityEnabled(u31) {
        this.__isAccessibilityEnabled.set(u31);
    }

    NullBuilder(t31 = null) {
    }

    onWillApplyTheme(s31) {
        this.treeViewTheme.itemSelectedBgColor = s31.colors.interactiveSelect;
        this.treeViewTheme.itemPressedBgColor = s31.colors.interactivePressed;
        this.treeViewTheme.itemHoverBgColor = s31.colors.interactiveHover;
        this.treeViewTheme.primaryTitleFontColor = s31.colors.fontPrimary;
        this.treeViewTheme.secondaryTitleFontColor = s31.colors.fontSecondary;
        this.treeViewTheme.primaryTitleActiveFontColor = s31.colors.interactiveActive;
        this.treeViewTheme.borderFocusedColor = s31.colors.interactiveFocus;
        this.treeViewTheme.leftIconColor = s31.colors.iconSecondary;
        this.treeViewTheme.leftIconActiveColor = s31.colors.interactiveActive;
        this.treeViewTheme.arrowIconColor = s31.colors.iconPrimary;
        this.treeController.treeViewTheme = this.treeViewTheme;
    }

    aboutToAppear() {
        if (this.treeController !== null) {
            this.listNodeDataSource = this.treeController.getListNodeDataSource();
            this.nodeList = this.treeController.getListNodeDataSource().listNode;
            this.item = this.treeController.getListNodeDataSource().listNode;
        }
        let p31 = this.getUIContext();
        this.followingSystemFontScale = p31.isFollowingSystemFontScale();
        this.maxAppFontScale = p31.getMaxFontScale();
        accessibility.on('screenReaderStateChange', (r31) => {
            this.isAccessibilityEnabled = r31;
        });
    }

    decideFontScale() {
        let n31 = this.getUIContext();
        let o31 = n31.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.followingSystemFontScale) {
            return 1;
        }
        return Math.min(o31, this.maxAppFontScale, MAX_FONT_SCALE);
    }

    decideSymbolFontScale(j31) {
        if (!j31 || !this.followingSystemFontScale) {
            return 1;
        }
        let k31 = this.getUIContext();
        let l31 = k31.getHostContext()?.config?.fontSizeScale ?? 1;
        let m31 = Math.min(l31, this.maxAppFontScale, MAX_SYMBOL_FONT_SCALE);
        return Math.max(m31, MIN_SYMBOL_FONT_SCALE);
    }

    popupForShowTitle(z30, a31, b31, c31 = null) {
        this.observeComponentCreation2((h31, i31) => {
            Row.create();
            Row.backgroundColor(a31);
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
        this.observeComponentCreation2((f31, g31) => {
            Text.create(z30);
            Text.fontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_body2'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            });
            Text.fontWeight('regular');
            Text.fontColor(b31);
            Text.minFontScale(MIN_FONT_SCALE);
            Text.maxFontScale(this.decideFontScale());
        }, Text);
        Text.pop();
        Row.pop();
    }

    builder(y30 = null) {
        this.listTreeViewMenu.bind(this)();
    }

    draggingPopup(h29, i29 = null) {
        this.observeComponentCreation2((w30, x30) => {
            Row.create();
            Row.id(`treeView_node_lift${h29.getNodeCurrentNodeId()}`);
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
        this.observeComponentCreation2((w29, x29) => {
            If.create();
            if (h29.getNodeItem().imageNode) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((u30, v30) => {
                        Row.create();
                        Row.backgroundColor(COLOR_IMAGE_ROW);
                        Row.margin({
                            end: getLengthMetricsByResourceOrNumber(h29.getNodeItem().imageNode?.itemRightMargin)
                        });
                        Row.height(h29.getNodeItem().imageNode?.itemHeight *
                        this.decideSymbolFontScale(h29.getNodeItem().imageNode?.symbolNormalSource !== undefined ||
                        Util.isSymbolResource(h29.getNodeItem().imageNode?.normalSource)));
                        Row.width(h29.getNodeItem().imageNode?.itemWidth *
                        this.decideSymbolFontScale(h29.getNodeItem().imageNode?.symbolNormalSource !== undefined ||
                        Util.isSymbolResource(h29.getNodeItem().imageNode?.normalSource)));
                    }, Row);
                    this.observeComponentCreation2((c30, d30) => {
                        If.create();
                        if (h29.getNodeItem().imageNode?.symbolNormalSource) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((s30, t30) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.attributeModifier.bind(this)(h29.getNodeItem()
                                        .imageNode?.symbolNormalSource);
                                    SymbolGlyph.fontSize(`${h29.getNodeItem().imageNode?.itemHeight *
                                    this.decideSymbolFontScale(true)}vp`);
                                    SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                    SymbolGlyph.opacity(this.listNodeDataSource.getDragPopupPara().imageOpacity);
                                }, SymbolGlyph);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((g30, h30) => {
                                    If.create();
                                    if (Util.isSymbolResource(h29.getNodeItem().imageNode?.normalSource)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((o30, p30) => {
                                                SymbolGlyph.create(h29.getNodeItem().imageNode?.normalSource);
                                                SymbolGlyph.fontSize(`${h29.getNodeItem().imageNode?.itemHeight *
                                                this.decideSymbolFontScale(true)}vp`);
                                                SymbolGlyph.opacity(this.listNodeDataSource.getDragPopupPara()
                                                    .imageOpacity);
                                            }, SymbolGlyph);
                                        });
                                    } else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((k30, l30) => {
                                                Image.create(h29.getNodeItem().imageNode?.normalSource);
                                                Image.objectFit(ImageFit.Contain);
                                                Image.height(h29.getNodeItem().imageNode?.itemHeight);
                                                Image.width(h29.getNodeItem().imageNode?.itemWidth);
                                                Image.opacity(this.listNodeDataSource.getDragPopupPara().imageOpacity);
                                                Image.matchTextDirection((h29.getNodeItem()
                                                    .imageCollapse?.collapseSource === ARROW_RIGHT ||
                                                    h29.getNodeItem().imageCollapse?.collapseSource ===
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
        this.observeComponentCreation2((u29, v29) => {
            Row.create();
            Row.constraintSize({
                minWidth: h29.getNodeItem().imageNode ?
                this.listNodeDataSource.getDragPopupPara().textConstraintSize.minWidth1 :
                this.listNodeDataSource.getDragPopupPara().textConstraintSize.minWidth2,
                maxWidth: h29.getNodeItem().imageNode ?
                this.listNodeDataSource.getDragPopupPara().textConstraintSize.maxWidth1 :
                this.listNodeDataSource.getDragPopupPara().textConstraintSize.maxWidth2,
            });
        }, Row);
        this.observeComponentCreation2((n29, o29) => {
            If.create();
            if (h29.getNodeItem().mainTitleNode && h29.getIsShowTitle()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((s29, t29) => {
                        Text.create(h29.getNodeItem().mainTitleNode?.title);
                        Text.maxLines(1);
                        Text.minFontScale(MIN_FONT_SCALE);
                        Text.maxFontScale(this.decideFontScale());
                        Text.fontSize(h29.getNodeItem().mainTitleNode?.size);
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

    setImageSources(e29, f29) {
        let g29 = this.nodeList[e29];
        g29.setIsSelected(f29 === InteractionStatus.SELECTED ||
            f29 === InteractionStatus.EDIT || f29 === InteractionStatus.FINISH_EDIT);
        if (g29.getNodeItem().mainTitleNode !== null && f29 !== InteractionStatus.DRAG_INSERT &&
            f29 !== InteractionStatus.FINISH_DRAG_INSERT) {
            g29.getNodeItem().mainTitleNode?.setMainTitleSelected(f29 === InteractionStatus.SELECTED ||
                f29 === InteractionStatus.FINISH_EDIT);
        }
        if (g29.getNodeItem().imageNode !== null) {
            g29.getNodeItem().imageNode?.setImageSource(f29);
        }
    }

    touchInner(b29, c29) {
        this.viewLastIndex = this.listNodeDataSource.getLastIndex();
        let d29 = this.listNodeDataSource.findIndex(b29.getNodeCurrentNodeId());
        if (c29.type === TouchType.Down) {
            if (d29 !== this.viewLastIndex) {
                this.clearLastIndexColor();
                this.listNodeDataSource.lastIndex = d29;
                this.listNodeDataSource.setClickIndex(d29);
            }
        }
        if (c29.type === TouchType.Up) {
            this.listNodeDataSource.listNode[d29].setIsSelected(true);
            this.listNodeDataSource.setImageSource(d29, InteractionStatus.SELECTED);
            if (this.listNodeDataSource.listNode[d29].getNodeItem().imageNode !== null) {
                this.listNodeDataSource.listNode[d29].imageSource = this.listNodeDataSource.listNode[d29]
                    .getNodeItem().imageNode?.source;
                this.listNodeDataSource.listNode[d29].symbolSource = this.listNodeDataSource.listNode[d29]
                    .getNodeItem().imageNode?.symbolSource;
            }
            if (d29 !== this.viewLastIndex) {
                this.clearLastIndexColor();
                this.listNodeDataSource.lastIndex = d29;
                this.listNodeDataSource.setClickIndex(d29);
            }
            this.viewLastIndex = d29;
        }
        if (this.listNodeDataSource.getLastIndex() !== -1 && d29 !== this.listNodeDataSource.getLastIndex()) {
            this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false,
                this.listNodeDataSource.getLastIndex());
            this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(),
                MenuOperation.COMMIT_NODE);
        }
    }

    clickInner(z28) {
        this.viewLastIndex = this.listNodeDataSource.getLastIndex();
        let a29 = this.listNodeDataSource.findIndex(z28.getNodeCurrentNodeId());
        if (a29 !== this.viewLastIndex) {
            this.clearLastIndexColor();
            this.listNodeDataSource.lastIndex = a29;
            this.listNodeDataSource.setClickIndex(a29);
        }
        this.listNodeDataSource.listNode[a29].setIsSelected(true);
        this.listNodeDataSource.setImageSource(a29, InteractionStatus.SELECTED);
        if (this.listNodeDataSource.listNode[a29].getNodeItem().imageNode !== null) {
            this.listNodeDataSource.listNode[a29].imageSource = this.listNodeDataSource.listNode[a29]
                .getNodeItem().imageNode?.source;
            this.listNodeDataSource.listNode[a29].symbolSource = this.listNodeDataSource.listNode[a29]
                .getNodeItem().imageNode?.symbolSource;
        }
        if (a29 !== this.viewLastIndex) {
            this.clearLastIndexColor();
            this.listNodeDataSource.lastIndex = a29;
            this.listNodeDataSource.setClickIndex(a29);
        }
        this.viewLastIndex = a29;
        if (this.listNodeDataSource.getLastIndex() !== -1 && a29 !== this.listNodeDataSource.getLastIndex()) {
            this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false,
                this.listNodeDataSource.getLastIndex());
            this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(),
                MenuOperation.COMMIT_NODE);
        }
    }

    initialRender() {
        this.observeComponentCreation2((j27, k27) => {
            List.create({});
            List.onDragMove((q28, r28) => {
                if (this.isMultiPress) {
                    hilog.error(LOG_CODE, TAG, 'drag error, a item has been dragged');
                    return;
                }
                let s28 = LIST_ITEM_HEIGHT;
                let t28 = Math.floor(q28.getY() /
                    (s28 / FLAG_NUMBER)) %
                    FLAG_NUMBER ? Flag.DOWN_FLAG : Flag.UP_FLAG;
                let u28 = JSON.parse(r28).insertIndex;
                let v28 = false;
                if (u28 >= this.listNodeDataSource.totalCount()) {
                    t28 = Flag.DOWN_FLAG;
                    u28 = this.listNodeDataSource.totalCount() - 1;
                    this.listNodeDataSource.getData(u28)?.setIsOverBorder(true);
                    v28 = true;
                } else {
                    this.listNodeDataSource.getData(u28)?.setIsOverBorder(false);
                }
                let w28 = this.listNodeDataSource.getData(u28);
                let x28 = w28?.getNodeCurrentNodeId();
                if (u28 !== this.listNodeDataSource.getLastPassIndex() && this.listNodeDataSource.getIsInnerDrag()) {
                    let y28 = this.listNodeDataSource.getIsParentOfInsertNode(x28);
                    if (y28) {
                        this.listNodeDataSource.setPassIndex(u28);
                        if (x28 !== undefined) {
                            this.listNodeDataSource.clearTimeOutAboutDelayHighLightAndExpand(this.listNodeDataSource.findIndex(x28));
                        }
                        this.listNodeDataSource.setFlag(Flag.NONE);
                        return;
                    }
                }
                this.listNodeDataSource.setLastPassIndex(u28);
                this.listNodeDataSource.setVisibility(t28, u28 - 1, v28,
                    ObservedObject.GetRawObject(this.allParentNode));
                if (x28 !== undefined && x28 !== this.listNodeDataSource.getDraggingCurrentNodeId()) {
                    this.listNodeDataSource.delayHighLightAndExpandNode(this.listNodeDataSource.findIndex(x28), x28,
                        u28);
                }
            });
            List.onDragEnter((n28, o28) => {
                if (this.listNodeDataSource.getIsInnerDrag()) {
                    this.listNodeDataSource.setIsDrag(true);
                    let p28 = DRAG_OPACITY;
                    this.listNodeDataSource.setListItemOpacity(p28);
                }
            });
            List.onDragLeave((k28, l28) => {
                this.listNodeDataSource.hideLastLine();
                this.listNodeDataSource.clearLastTimeoutHighLight();
                this.listNodeDataSource.clearLastTimeoutExpand();
                let m28 = DRAG_OPACITY_NONE;
                this.listNodeDataSource.setListItemOpacity(m28);
                this.listNodeDataSource.setIsDrag(false);
                this.listNodeDataSource.notifyDataReload();
            });
            List.onDrop((p27, q27) => {
                this.accessibilityNodeType = AccessibilityNodeType.PLACE;
                this.listNodeDataSource.clearLastTimeoutExpand();
                let r27 = DRAG_OPACITY_NONE;
                this.listNodeDataSource.setListItemOpacity(r27);
                let s27 = JSON.parse(q27).insertIndex;
                let t27 = this.dropSelectedIndex;
                if (t27 - 1 > this.listNodeDataSource.totalCount() || t27 === undefined) {
                    hilog.error(LOG_CODE, TAG, 'drag error, currentNodeIndex is not found');
                    this.listNodeDataSource.setIsDrag(false);
                    return;
                }
                if (s27 === this.listNodeDataSource.totalCount()) {
                    hilog.info(LOG_CODE, TAG, 'need to insert into the position of the last line');
                    s27 -= 1;
                }
                let u27 = this.listNodeDataSource.getData(s27);
                if (u27 === undefined) {
                    return;
                }
                let v27 = u27.getNodeCurrentNodeId();
                if (!this.listNodeDataSource.getIsDrag() || !this.listNodeDataSource.getIsInnerDrag()) {
                    this.listNodeDataSource.clearLastTimeoutHighLight();
                    this.listNodeDataSource.setIsInnerDrag(false);
                    this.listNodeDataSource.hideLastLine();
                    this.listNodeDataSource.initialParameterAboutDelayHighLightAndExpandIndex();
                    this.listNodeDataSource.refreshSubtitle(v27);
                    this.listNodeDataSource.notifyDataReload();
                    return;
                }
                let w27 = this.listNodeDataSource.getCurrentNodeInfo();
                let x27 = u27.getNodeParentNodeId();
                let y27 = this.listNodeDataSource.getDraggingCurrentNodeId();
                let z27 = this.listNodeDataSource.getDraggingParentNodeId();
                let a28 = this.listNodeDataSource.getIsParentOfInsertNode(v27);
                if (a28) {
                    this.listNodeDataSource.clearLastTimeoutHighLight();
                    this.listNodeDataSource.setIsInnerDrag(false);
                    this.listNodeDataSource.hideLastLine();
                    this.listNodeDataSource.notifyDataChange(s27);
                    this.listNodeDataSource.initialParameterAboutDelayHighLightAndExpandIndex();
                    this.listNodeDataSource.setIsDrag(false);
                    let j28 = this.listNodeDataSource.findIndex(y27);
                    this.listNodeDataSource.setClickIndex(j28);
                    this.listNodeDataSource.handleEvent(Event.DRAG, j28);
                    return;
                }
                if (this.listNodeDataSource.getExpandAndCollapseInfo(y27) === NodeStatus.EXPAND) {
                    this.listNodeDataSource.expandAndCollapseNode(this.listNodeDataSource.findIndex(y27));
                }
                let b28 = false;
                if (this.listNodeDataSource.getExpandAndCollapseInfo(v27) === NodeStatus.COLLAPSE) {
                    let i28 = this.listNodeDataSource.findIndex(v27);
                    if (this.listNodeDataSource.listNode[i28].getIsHighLight()) {
                        this.listNodeDataSource.expandAndCollapseNode(i28);
                    }
                    b28 = true;
                }
                this.listNodeDataSource.setLastDelayHighLightId();
                if (w27 !== null && y27 !== v27) {
                    this.listNodeDataSource.alterDragNode(x27, v27, z27, y27, w27);
                    this.listNodeDataSource.hideLastLine();
                } else {
                    this.listNodeDataSource.hideLastLine();
                    this.listNodeDataSource.setLastPassId(y27);
                    this.listNodeDataSource.hideLastLine();
                }
                let c28 = this.listNodeDataSource.findIndex(this.listNodeDataSource.getLastDelayHighLightId());
                this.listNodeDataSource.setLastDelayHighLightIndex(c28);
                this.listNodeDataSource.clearLastTimeoutHighLight();
                this.listNodeDataSource.initialParameterAboutDelayHighLightAndExpandIndex();
                this.listNodeDataSource.setIsDrag(false);
                let d28 = this.listNodeDataSource.findIndex(y27);
                this.listNodeDataSource.setClickIndex(d28);
                this.listNodeDataSource.handleEvent(Event.DRAG, d28);
                this.listNodeDataSource.setIsInnerDrag(false);
                this.listNodeDataSource.notifyDataReload();
                this.listNodeDataSource.listNode[d28].fontColor = this.treeViewTheme.primaryTitleActiveFontColor;
                if (this.viewLastIndex !== -1 && t27 !== this.viewLastIndex) {
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
                this.listNodeDataSource.lastIndex = d28;
                let e28 = w27?.getNodeParentNodeId();
                this.listNodeDataSource.judgeImageCollapse(e28);
                let f28 = ({
                    type: 'requestFocusForAccessibility',
                    bundleName: getContext()?.abilityInfo?.bundleName,
                    triggerAction: 'common',
                    customId: `treeView_node${y27}`
                });
                accessibility.sendAccessibilityEvent(f28).then(() => {
                    setTimeout(() => {
                        this.accessibilityNodeType = AccessibilityNodeType.TEXT;
                    }, ENTER_EXIT_DURATION);
                    console.log(`test123 Succeeded in send event, eventInfo is ${JSON.stringify(f28)}`);
                });
            });
        }, List);
        {
            const m2 = x25 => {
                const y25 = x25;
                {
                    const k3 = (p26, q26) => {
                        ListItem.create(() => {
                        }, false);
                        ListItem.width('100%');
                        ListItem.height(y25.getListItemHeight());
                        ListItem.padding({
                            start: LengthMetrics.resource(this.itemPadding.left),
                            end: LengthMetrics.resource(this.itemPadding.right)
                        });
                        ListItem.align(Alignment.Start);
                        ListItem.onDragStart((t26, u26) => {
                            this.accessibilityNodeType = AccessibilityNodeType.LIFT;
                            if (this.listNodeDataSource.getIsDrag() || this.listNodeDataSource.getIsInnerDrag() ||
                            this.isMultiPress) {
                                hilog.error(LOG_CODE, TAG, 'drag error, a item has been dragged');
                                return;
                            }
                            this.dropSelectedIndex = JSON.parse(u26).selectedIndex;
                            let v26 = JSON.parse(u26).selectedIndex;
                            let w26 = this.listNodeDataSource.getData(v26);
                            let x26 = y25.getNodeCurrentNodeId();
                            if (v26 >= this.listNodeDataSource.totalCount() || v26 === undefined) {
                                hilog.error(LOG_CODE, TAG, 'drag error, currentNodeIndex is not found in onDragStart');
                                return;
                            }
                            this.listNodeDataSource.setIsInnerDrag(true);
                            this.listNodeDataSource.setIsDrag(true);
                            this.listNodeDataSource.setCurrentNodeInfo(w26);
                            this.listNodeDataSource.setDraggingCurrentNodeId(w26?.getNodeCurrentNodeId());
                            this.listNodeDataSource.setDraggingParentNodeId(w26?.getNodeParentNodeId());
                            let y26 = DRAG_OPACITY;
                            this.listNodeDataSource.setListItemOpacity(y26);
                            this.listNodeDataSource.notifyDataChange(v26);
                            if (x26 !== w26?.getNodeCurrentNodeId()) {
                                hilog.error(LOG_CODE, TAG, 'drag is too fast, it attribute a fault to OH');
                                this.listNodeDataSource.setIsDrag(false);
                                return;
                            }
                            let z26 = w26.getNodeInfoData()?.primaryTitle === undefined ? '' :
                                w26.getNodeInfoData()?.primaryTitle;
                            let a27 = w26.getNodeInfoData()?.secondaryTitle === undefined ? '' :
                                w26.getNodeInfoData()?.secondaryTitle;
                            let b27 = this.listNodeDataSource.getAccessibleTitleText(z26);
                            let c27 = this.listNodeDataSource.getAccessibleTitleText(a27);
                            let d27 = `${b27}, ${c27}`;
                            this.listNodeDataSource.sendAccessibility(this.listNodeDataSource.getStringByName('treeview_accessibility_lift_node',
                                d27));
                            let e27 = [];
                            for (let i27 = 0; i27 < this.listNodeDataSource.listNode.length; i27++) {
                                if (this.listNodeDataSource.listNode[i27].getNodeParentNodeId() === -1) {
                                    e27.push(this.listNodeDataSource.listNode[i27].getNodeCurrentNodeId());
                                }
                            }
                            this.allParentNode = e27;
                            let f27 = ({
                                type: 'requestFocusForAccessibility',
                                bundleName: getContext()?.abilityInfo?.bundleName,
                                triggerAction: 'common',
                                customId: `treeView_node_lift${x26}`
                            });
                            accessibility.sendAccessibilityEvent(f27).then(() => {
                                setTimeout(() => {
                                    this.accessibilityNodeType = AccessibilityNodeType.TEXT;
                                }, ENTER_EXIT_DURATION);
                            });
                            return {
                                builder: () => {
                                    this.draggingPopup.call(this, w26);
                                }
                            };
                        });
                    };
                    const o3 = () => {
                        this.observeComponentCreation2(k3, ListItem);
                        this.observeComponentCreation2((l26, m26) => {
                            Row.create();
                            Row.onTouch(this.isAccessibilityEnabled ? undefined : (o26) => {
                                this.touchInner(y25, o26);
                            });
                        }, Row);
                        {
                            this.observeComponentCreation2((f26, g26) => {
                                if (g26) {
                                    let h26 = new TreeViewInner(this, {
                                        item: y25,
                                        listNodeDataSource: this.listNodeDataSource,
                                        index: this.listNodeDataSource.findIndex(y25.getNodeCurrentNodeId()),
                                        listTreeViewMenu: this.listTreeViewMenu,
                                        callBackClick: () => this.clickInner(y25),
                                    }, undefined, f26, () => {
                                    }, { page: 'library/src/main/ets/components/MainPage.ets', line: 1301, col: 13 });
                                    ViewPU.create(h26);
                                    let n4 = () => {
                                        return {
                                            item: y25,
                                            listNodeDataSource: this.listNodeDataSource,
                                            index: this.listNodeDataSource.findIndex(y25.getNodeCurrentNodeId()),
                                            listTreeViewMenu: this.listTreeViewMenu,
                                            callBackClick: () => this.clickInner(y25)
                                        };
                                    };
                                    h26.paramsGenerator_ = n4;
                                } else {
                                    this.updateStateVarsOfChildByElmtId(f26, {
                                        item: y25
                                    });
                                }
                            }, { name: 'TreeViewInner' });
                        }
                        Row.pop();
                        ListItem.pop();
                    };
                    o3();
                }
            };
            const y2 = (w25) => JSON.stringify(w25);
            LazyForEach.create('1', this, this.listNodeDataSource, m2, y2);
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
        let q25 = this.listNodeDataSource.getClickNodeId();
        return this.listNodeDataSource.getClickNodeChildrenInfo(q25);
    }

    getChildrenId() {
        let p25 = this.listNodeDataSource.getClickNodeId();
        return this.listNodeDataSource.getClickChildId(p25);
    }

    removeNode() {
        let m25 = this.listNodeDataSource.getClickNodeId();
        if (m25 < 0) {
            return;
        }
        let n25 = this.listNodeDataSource.findParentNodeId(m25);
        let o25 = this.listNodeDataSource.removeNode(m25, n25);
        this.listNodeDataSource.refreshData(MenuOperation.REMOVE_NODE, n25, o25);
        this.nodeIdList.splice(this.nodeIdList.indexOf(m25), 1);
        this.listNodeDataSource.lastIndex = -1;
    }

    modifyNode() {
        let l25 = this.listNodeDataSource.getClickNodeId();
        this.listNodeDataSource.setItemVisibilityOnEdit(l25, MenuOperation.MODIFY_NODE);
    }

    add(f25) {
        let g25 = this.listNodeDataSource.getClickNodeId();
        if (g25 === this.listNodeDataSource.ROOT_NODE_ID || !this.listNodeDataSource.getIsFolder(g25)) {
            return;
        }
        let h25 = this.listNodeDataSource.getNewNodeParam(g25);
        this.nodeIdList.push(this.nodeIdList[this.nodeIdList.length - 1] + 1);
        let i25 = this.nodeIdList[this.nodeIdList.length - 1];
        let j25 = this.listNodeDataSource.addNode(g25, i25, {
            isFolder: h25.isFolder,
            icon: h25.icon,
            symbolIconStyle: h25.symbolIconStyle,
            selectedIcon: h25.selectedIcon,
            symbolSelectedIconStyle: h25.symbolSelectedIconStyle,
            editIcon: h25.editIcon,
            symbolEditIconStyle: h25.symbolEditIconStyle,
            primaryTitle: '新建文件夹',
            container: h25.container,
            secondaryTitle: h25.secondaryTitle,
        }, f25);
        if (!j25) {
            return;
        }
        this.listNodeDataSource.refreshData(MenuOperation.ADD_NODE, g25, [i25]);
        this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false,
            this.listNodeDataSource.getLastIndex());
        this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(),
            MenuOperation.COMMIT_NODE);
        this.listNodeDataSource.listNode[this.listNodeDataSource.getLastIndex()]
            .setFontColor(this.treeViewTheme.primaryTitleFontColor);
        let k25 = this.listNodeDataSource.findIndex(i25);
        this.listNodeDataSource.setClickIndex(k25);
        this.listNodeDataSource.handleEvent(Event.TOUCH_UP, k25);
    }

    addNode(b25) {
        if (b25 === undefined) {
            this.add(this.initBuild);
            return this;
        } else {
            for (let e25 = 0; e25 < this.nodeIdList.length; e25++) {
                if (b25.currentNodeId === this.nodeIdList[e25].valueOf()) {
                    throw new Error('ListTreeNode[addNode]: ' +
                        'The parameters of the new node cannot contain the same currentNodeId.');
                    return this;
                }
            }
            let c25 = false;
            if (b25.primaryTitle !== undefined &&
                !this.listNodeDataSource.checkMainTitleIsValid(b25.primaryTitle.toString())) {
                throw new Error('ListTreeNode[addNode]: ' +
                    'The directory name cannot contain the following characters\ /: *? " < > | orexceedsthemaximumlength.');
                return this;
            }
            if (b25.primaryTitle === null && b25.icon === null && b25.symbolIconStyle === null) {
                throw new Error('ListTreeNode[addNode]: ' +
                    'The icon|symbolIconStyle and directory name cannot be empty at the same time.');
                return this;
            }
            if (b25.currentNodeId === this.ROOT_NODE_ID || b25.currentNodeId === null) {
                throw new Error('ListTreeNode[addNode]: currentNodeId can not be -1 or null.');
                return this;
            }
            if (b25.currentNodeId !== undefined) {
                this.nodeIdList.push(b25.currentNodeId);
            }
            if (b25.parentNodeId !== undefined) {
                if (b25.currentNodeId !== undefined) {
                    c25 =
                        this.listNodeDataSource.addNode(b25.parentNodeId, b25.currentNodeId, b25, this.initBuild);
                }
            }
            if (!c25) {
                return this;
            }
            if (!this.initBuild && b25.parentNodeId !== undefined) {
                let d25 = this.nodeIdList[this.nodeIdList.length - 1];
                this.listNodeDataSource.refreshData(MenuOperation.ADD_NODE, b25.parentNodeId, [d25]);
            }
            return this;
        }
    }

    refreshNode(y24, z24, a25) {
        this.listNodeDataSource.setNodeSubtitlePara(y24, z24, a25);
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

    getData(x24) {
        return undefined;
    }

    registerDataChangeListener(w24) {
        if (this.listeners.indexOf(w24) < 0) {
            this.listeners.push(w24);
        }
    }

    unregisterDataChangeListener(u24) {
        const v24 = this.listeners.indexOf(u24);
        if (v24 >= 0) {
            this.listeners.splice(v24, 1);
        }
    }

    notifyDataReload() {
        this.listeners.forEach(t24 => {
            t24.onDataReloaded();
        });
    }

    notifyDataAdd(p24) {
        this.listeners.forEach(r24 => {
            r24.onDataAdd(p24);
        });
    }

    notifyDataChange(m24) {
        if (m24 === undefined) {
            return;
        }
        this.listeners.forEach(o24 => {
            o24.onDataChange(m24);
        });
    }

    notifyDataDelete(j24) {
        this.listeners.forEach(l24 => {
            l24.onDataDelete(j24);
        });
    }

    notifyDataMove(f24, g24) {
        this.listeners.forEach(i24 => {
            i24.onDataMove(f24, g24);
        });
    }
}

function delayUpdateParentChildNum(x23, y23, z23, a24) {
    let b24 = setTimeout(() => {
        a24.forEach((e24) => {
            updateParentChildNumHandler(e24, z23, x23, y23);
        });
        clearTimeout(b24);
    }, DELAY_TIME);
}

function updateParentChildNumHandler(r23, s23, t23, u23) {
    let v23 = r23;
    while (v23 >= 0) {
        if (s23.has(v23)) {
            let w23 = s23.get(v23);
            w23.getChildNodeInfo().allChildNum =
                t23 ? w23.getChildNodeInfo().allChildNum + u23 : w23.getChildNodeInfo().allChildNum - u23;
            v23 = w23.parentNodeId;
        } else {
            hilog.error(LOG_CODE, TAG, 'updateParentChildNumHandler: parent node not found');
            break;
        }
    }
}

function delaySortNodeIdList(l23) {
    let m23 = setTimeout(() => {
        l23.sort((p23, q23) => p23 - q23);
        clearTimeout(m23);
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
                color: SHADOW_COLOR,
                offsetX: 0,
                offsetY: SHADOW_OFFSETY,
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

    checkIndex(k23) {
        if (k23 < 0 || k23 >= this.listNode.length) {
            hilog.error(LOG_CODE, TAG, 'check index fail');
            return false;
        }
        return true;
    }

    changeNodeColor(i23, j23) {
        if (!this.checkIndex(i23)) {
            return;
        }
        this.listNode[i23].setNodeColor(j23);
        this.listNode[i23].setNodeBorder(false);
    }

    getNodeColor(h23) {
        return this.listNode[h23].getNodeColor();
    }

    handleFocusEffect(f23, g23) {
        if (this.listNode[f23].getNodeIsShow()) {
            this.listNode[f23].setNodeBorder(g23);
        }
    }

    setImageSource(c23, d23) {
        if (!this.checkIndex(c23)) {
            return;
        }
        let e23 = this.listNode[c23];
        e23.setIsSelected(d23 === InteractionStatus.SELECTED ||
            d23 === InteractionStatus.EDIT || d23 === InteractionStatus.FINISH_EDIT);
        if (e23.getNodeItem().mainTitleNode !== null && d23 !== InteractionStatus.DRAG_INSERT &&
            d23 !== InteractionStatus.FINISH_DRAG_INSERT) {
            e23.getNodeItem().mainTitleNode?.setMainTitleSelected(d23 === InteractionStatus.SELECTED ||
                d23 === InteractionStatus.FINISH_EDIT);
        }
        if (e23.getNodeItem().imageNode !== null) {
            e23.getNodeItem().imageNode?.setImageSource(d23);
        }
    }

    setImageCollapseSource(z22, a23) {
        let b23 = this.listNode[z22];
        if (b23.getNodeItem().imageCollapse !== undefined) {
            b23.getNodeItem().imageCollapse = CollapseImageNodeFlyweightFactory.getCollapseImageNode(a23,
                this.expandAndCollapseInfo.get(b23.getNodeCurrentNodeId()), b23.getNodeItem().imageCollapse?.type);
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
        let x22 = 0;
        this.loadedNodeIdAndIndexMap.clear();
        this.nodeIdAndNodeIndexMap.clear();
        this.loadedListNode.splice(0, this.loadedListNode.length);
        for (let y22 = 0; y22 < this.listNode.length; y22++) {
            this.nodeIdAndNodeIndexMap.set(this.listNode[y22].getNodeCurrentNodeId(), y22);
            if (this.listNode[y22].getNodeIsShow()) {
                this.loadedNodeIdAndIndexMap.set(this.listNode[y22].getNodeCurrentNodeId(), x22++);
                this.loadedListNode.push(this.listNode[y22]);
            }
        }
    }

    changeNodeStatus(u22) {
        if (u22 >= this.listNode.length) {
            hilog.error(LOG_CODE, TAG, 'changeNodeStatus clickIndex error.');
            return;
        }
        let v22 = u22;
        let w22 = this.listNode[u22].getNodeCurrentNodeId();
        if (this.expandAndCollapseInfo.get(w22) === NodeStatus.EXPAND) {
            this.expandAndCollapseInfo.set(w22, NodeStatus.COLLAPSE);
            this.listNode[v22].getNodeItem()
                .imageCollapse = CollapseImageNodeFlyweightFactory.changeImageCollapseSource(NodeStatus.COLLAPSE,
                this.listNode[v22].getNodeItem().imageCollapse?.isCollapse);
        } else if (this.expandAndCollapseInfo.get(w22) === NodeStatus.COLLAPSE) {
            this.expandAndCollapseInfo.set(w22, NodeStatus.EXPAND);
            this.listNode[v22].getNodeItem()
                .imageCollapse = CollapseImageNodeFlyweightFactory.changeImageCollapseSource(NodeStatus.EXPAND,
                this.listNode[v22].getNodeItem().imageCollapse?.isCollapse);
        }
    }

    handleExpandAndCollapse(k22, l22) {
        if (k22 >= this.listNode.length) {
            hilog.error(LOG_CODE, TAG, 'handleExpandAndCollapse clickIndex error.');
            return;
        }
        let m22 = k22;
        let n22 = this.listNode[m22].getNodeCurrentNodeId();
        if (!this.expandAndCollapseInfo.has(n22)) {
            return;
        }
        let o22 = this.expandAndCollapseInfo.get(n22);
        if (this.listNode[m22].getChildNodeInfo().isHasChildNode && o22 === NodeStatus.COLLAPSE) {
            for (let t22 = 0; t22 < this.listNode[m22].getChildNodeInfo().allChildNum; t22++) {
                if (this.listNode[m22 + 1 + t22] === undefined) {
                    return;
                }
                this.listNode[m22 + 1 + t22].setNodeIsShow(false);
                this.listNode[m22 + 1 + t22].setListItemHeight(LIST_ITEM_HEIGHT_NONE);
            }
            this.loadedListNodeFunction();
            this.notifyDataReload();
            return;
        }
        let p22 = new Array(this.listNode[m22].getChildNodeInfo().childNum);
        p22[0] = m22 + 1;
        let q22 = 1;
        while (q22 < this.listNode[m22].getChildNodeInfo().childNum) {
            p22[q22] = p22[q22 - 1] + this.listNode[p22[q22 - 1]].getChildNodeInfo().allChildNum + 1;
            q22++;
        }
        if (o22 === NodeStatus.EXPAND) {
            for (let r22 = 0; r22 < p22.length; r22++) {
                if (this.listNode[p22[r22]] === undefined) {
                    return;
                }
                this.listNode[p22[r22]].setNodeIsShow(true);
                this.listNode[p22[r22]].setListItemHeight(LIST_ITEM_HEIGHT);
                let s22 = this.listNode[p22[r22]].getNodeCurrentNodeId();
                if (this.expandAndCollapseInfo.get(s22) === NodeStatus.EXPAND) {
                    this.handleExpandAndCollapse(p22[r22], false);
                }
            }
        }
        p22 = null;
        if (l22) {
            this.loadedListNodeFunction();
            this.notifyDataReload();
        }
    }

    updateAllChildNum() {
        delayUpdateParentChildNum(true, 1, this.nodeIdNodeItemMap, this.updateNodeIdList);
    }

    resetData(j22) {
        j22.splice(0, j22.length);
        this.loadedNodeIdAndIndexMap.clear();
        this.loadedListNode.splice(0, this.loadedListNode.length);
        this.nodeIdAndNodeIndexMap.clear();
        this.nodeIdAndSubtitleMap.clear();
    }

    initHandler(a22, b22, c22) {
        let d22 = 0;
        let e22 = 0;
        this.resetData(a22);
        try {
            this.traverseSectionNodeDF((h22) => {
                if (h22.getCurrentNodeId() >= 0 && this.nodeIdNodeParamMap.has(h22.getCurrentNodeId())) {
                    let i22 = new NodeInfo(h22, this.nodeIdNodeParamMap.get(h22.getCurrentNodeId()));
                    i22.addImageCollapse(h22.getChildNodeInfo().isHasChildNode);
                    a22.push(i22);
                    this.nodeIdAndNodeIndexMap.set(i22.getNodeCurrentNodeId(), e22++);
                    d22 = this.nodeDFHandler(i22, d22);
                }
                return false;
            }, this._root, b22, c22);
        } catch (f22) {
            hilog.error(LOG_CODE, TAG, 'traverseSectionNodeDF function callbacks error.');
            this.resetData(a22);
        }
    }

    nodeDFHandler(y21, z21) {
        if (y21.getChildNodeInfo().isHasChildNode) {
            this.expandAndCollapseInfo.set(y21.getNodeCurrentNodeId(), NodeStatus.COLLAPSE);
        }
        if (y21.getNodeIsShow()) {
            this.loadedNodeIdAndIndexMap.set(y21.getNodeCurrentNodeId(), z21++);
            this.loadedListNode.push(y21);
        }
        if (y21.getIsFolder()) {
            if (y21.getNodeInfoData().secondaryTitle !== undefined) {
                this.nodeIdAndSubtitleMap.set(y21.getNodeCurrentNodeId(), y21.getNodeInfoData().secondaryTitle);
            } else {
                this.nodeIdAndSubtitleMap.set(y21.getNodeCurrentNodeId(), '');
            }
        }
        return z21;
    }

    delayInit() {
        let s21 = setTimeout(() => {
            let u21 = [];
            this.initHandler(u21, 0);
            this.listNode.splice(0, this.listNode.length);
            this.listNode.push(...u21);
            this.listNode.forEach((w21, x21) => {
                this.notifyDataDelete(x21);
                this.notifyDataAdd(x21);
            });
            clearTimeout(s21);
        }, DELAY_TIME);
    }

    initSection() {
        this.initHandler(this.listNode, 0, 1);
    }

    setClickIndex(r21) {
        this.thisIndex = r21;
    }

    getClickNodeId() {
        if (!this.checkIndex(this.thisIndex)) {
            return -1;
        }
        return this.listNode[this.thisIndex].getNodeCurrentNodeId();
    }

    expandAndCollapseNode(q21) {
        this.changeNodeStatus(q21);
        this.handleExpandAndCollapse(q21, true);
    }

    getIsTouchDown() {
        return this.isTouchDown;
    }

    getLastIndex() {
        return this.lastIndex;
    }

    findIndex(o21) {
        let p21 = -1;
        if (this.nodeIdAndNodeIndexMap.has(o21)) {
            p21 = this.nodeIdAndNodeIndexMap.get(o21);
        }
        return p21;
    }

    handleEventDrag(n21) {
        if (!this.checkIndex(n21)) {
            return;
        }
        this.setImageSource(n21, InteractionStatus.NORMAL);
        this.changeNodeColor(n21, this.listNode[n21].getNodeStatus().normal);
        this.handleFocusEffect(n21, false);
        this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.listNode[n21].getNodeCurrentNodeId()));
    }

    handleEvent(l21, m21) {
        if (this.isDrag) {
            return;
        }
        if (!this.checkIndex(m21)) {
            return;
        }
        if (l21 === Event.TOUCH_DOWN || l21 === Event.TOUCH_UP || l21 === Event.MOUSE_BUTTON_RIGHT) {
            if (m21 !== this.lastIndex) {
                this.clearLastIndexStatus();
            }
        }
        this.eventHandler(m21, l21);
    }

    eventHandler(h21, i21) {
        let j21 = this.loadedNodeIdAndIndexMap.get(this.listNode[h21].getNodeCurrentNodeId());
        switch (i21) {
            case Event.TOUCH_DOWN:
                this.isTouchDown = true;
                this.changeNodeColor(h21, this.listNode[h21].getNodeStatus().press);
                this.notifyDataChange(j21);
                break;
            case Event.TOUCH_UP: {
                this.touchUpHandler(h21, j21);
                break;
            }
            case Event.HOVER:
                if (this.getNodeColor(h21) !== this.listNode[h21].getNodeStatus().selected) {
                    this.changeNodeColor(h21, this.listNode[h21].getNodeStatus().hover);
                    this.notifyDataChange(j21);
                }
                break;
            case Event.HOVER_OVER:
                if (this.getNodeColor(h21) !== this.listNode[h21].getNodeStatus().selected) {
                    this.changeNodeColor(h21, this.listNode[h21].getNodeStatus().normal);
                    this.notifyDataChange(j21);
                }
                break;
            case Event.FOCUS:
                this.handleFocusEffect(h21, true);
                this.notifyDataChange(j21);
                break;
            case Event.BLUR:
                this.handleFocusEffect(h21, false);
                this.notifyDataChange(j21);
                break;
            case Event.MOUSE_BUTTON_RIGHT:
                this.lastIndex = h21;
                this.finishEditing();
                break;
            case Event.DRAG:
                this.isTouchDown = false;
                let k21 = this.listNode[h21];
                this.setImageSource(h21, InteractionStatus.SELECTED);
                this.lastIndex = h21;
                this.changeNodeColor(h21, k21.getNodeStatus().selected);
                this.notifyDataChange(j21);
                break;
            default:
                break;
        }
    }

    touchUpHandler(e21, f21) {
        if (this.isInnerDrag) {
            this.isInnerDrag = false;
        }
        this.isTouchDown = false;
        let g21 = this.listNode[e21];
        this.setImageSource(e21, InteractionStatus.SELECTED);
        g21.setFontColor(this.treeViewTheme.primaryTitleFontColor);
        this.lastIndex = e21;
        this.changeNodeColor(e21, g21.getNodeStatus().selected);
        this.notifyDataChange(f21);
    }

    notificationNodeInfo(v20, w20) {
        if (w20 === MenuOperation.MODIFY_NODE) {
            let c21 = this.listNode[this.modifyNodeIndex];
            let d21 = {
                currentNodeId: c21?.getNodeCurrentNodeId(),
                parentNodeId: c21?.getNodeParentNodeId(),
            };
            this.appEventBus.emit(TreeListenType.NODE_MODIFY, d21);
        } else if (w20 === MenuOperation.ADD_NODE) {
            let x20 = this.listNode[v20];
            if (x20 === undefined) {
                return;
            }
            let y20 = (x20.getNodeItem().imageNode !== undefined) ?
                x20.getNodeItem().imageNode?.source : undefined;
            let z20 = (x20.getNodeItem().imageNode !== undefined) ?
                x20.getNodeItem().imageNode?.selectedSource : undefined;
            let a21 = (x20.getNodeItem().imageNode !== undefined) ?
                x20.getNodeItem().imageNode?.editSource : undefined;
            let b21 = {
                currentNodeId: x20?.getNodeCurrentNodeId(),
                parentNodeId: x20?.getNodeParentNodeId(),
            };
            this.appEventBus.emit(TreeListenType.NODE_ADD, b21);
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

    setItemVisibilityOnEdit(p20, q20) {
        let r20 = -1;
        if (p20 === -1) {
            return;
        }
        if (q20 === MenuOperation.MODIFY_NODE) {
            for (let u20 = 0; u20 < this.listNode.length; u20++) {
                if (this.listNode[u20]?.getNodeCurrentNodeId() === p20) {
                    r20 = u20;
                    break;
                }
            }
            let t20 = this.listNode[r20];
            if (t20 === undefined) {
                return;
            }
            t20.setIsModify(true);
            if (t20.getNodeItem().mainTitleNode === null) {
                return;
            }
            this.currentOperation = MenuOperation.MODIFY_NODE;
            t20.setTitleAndInputTextStatus(true);
            this.setImageSource(r20, InteractionStatus.EDIT);
            this.setImageCollapseSource(r20, InteractionStatus.EDIT);
            this.modifyNodeIndex = r20;
            if (t20.getNodeItem().inputText) {
                if (t20.getNodeItem().imageCollapse !== null) {
                    t20.getNodeItem().inputText.rightMargin = {
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.ohos_id_text_paragraph_margin_xs'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__',
                    };
                } else {
                    t20.getNodeItem().inputText.rightMargin = {
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.ohos_id_elements_margin_horizontal_m'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__',
                    };
                }
            }
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(p20));
        }
        r20 = p20;
        if (q20 === MenuOperation.COMMIT_NODE) {
            let s20 = this.listNode[r20];
            if (s20 === undefined) {
                return;
            }
            s20.setTitleAndInputTextStatus(false);
            s20.setIsModify(false);
            this.setImageSource(r20, InteractionStatus.FINISH_EDIT);
            this.setImageCollapseSource(r20, InteractionStatus.FINISH_EDIT);
            this.notificationNodeInfo(this.modifyNodeIndex, this.currentOperation);
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(s20?.getNodeCurrentNodeId()));
        }
    }

    setPopUpInfo(j20, k20, l20, m20) {
        if (!this.checkIndex(m20)) {
            return;
        }
        let n20 = this.listNode[m20];
        if (n20 === undefined) {
            return;
        }
        n20.setPopUpIsShow(l20);
        let o20 = this.loadedNodeIdAndIndexMap.get(n20.getNodeCurrentNodeId());
        if (!l20) {
            this.notifyDataChange(o20);
            return;
        }
        if (j20 === PopUpType.HINTS) {
            if (n20.getNodeItem().mainTitleNode !== null) {
                n20.setPopUpText(n20.getNodeItem().mainTitleNode?.title);
            } else {
                n20.setPopUpText('');
                n20.setPopUpIsShow(false);
            }
            n20.setPopUpEnableArrow(false);
            n20.setPopUpColor({
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_background'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            });
            n20.setPopUpTextColor(this.treeViewTheme.secondaryTitleFontColor);
        } else if (j20 === PopUpType.WARNINGS) {
            if (n20.getNodeItem().inputText !== null) {
                if (k20 === InputError.INVALID_ERROR) {
                    n20.setPopUpText('invalid error');
                } else if (k20 === InputError.LENGTH_ERROR) {
                    n20.setPopUpText('length error');
                }
                n20.setPopUpEnableArrow(true);
                n20.setPopUpColor({
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_help_tip_bg'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                });
                n20.setPopUpTextColor({
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_text_hint_contrary'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                });
            }
        }
        this.notifyDataChange(o20);
    }

    setShowPopUpTimeout(g20, h20) {
        if (!this.checkIndex(h20)) {
            return;
        }
        if (this.listNode[h20].getNodeItem().mainTitleNode !== null) {
            this.listNode[h20].getNodeItem().mainTitleNode.popUpTimeout = g20;
        }
        let i20 = this.loadedNodeIdAndIndexMap.get(this.listNode[h20].getNodeCurrentNodeId());
        this.notifyDataChange(i20);
    }

    setMainTitleNameOnEdit(e20, f20) {
        this.modifyNodeIndex = e20;
        if (this.listNode[e20].getNodeItem().mainTitleNode !== null) {
            this.listNode[e20].getNodeItem().mainTitleNode.title = f20;
        }
    }

    totalCount() {
        return this.loadedNodeIdAndIndexMap.size;
    }

    getData(d20) {
        if (d20 < 0 || d20 >= this.loadedListNode.length) {
            return undefined;
        }
        return this.loadedListNode[d20];
    }

    addData(b20, c20) {
        if (!this.checkIndex(b20)) {
            return;
        }
        this.listNode.splice(b20, 0, c20);
        this.nodeIdAndNodeIndexMap.set(c20.getNodeCurrentNodeId(), b20);
        this.loadedListNodeFunction();
        this.notifyDataAdd(b20);
    }

    pushData(a20) {
        this.listNode.push(a20);
        this.nodeIdAndNodeIndexMap.set(a20.getNodeCurrentNodeId(), this.listNode.length);
        this.loadedListNodeFunction();
        this.notifyDataAdd(this.listNode.length - 1);
    }

    setIsInnerDrag(z19) {
        this.isInnerDrag = z19;
    }

    getIsInnerDrag() {
        return this.isInnerDrag;
    }

    setIsDrag(y19) {
        this.isDrag = y19;
    }

    getIsDrag() {
        return this.isDrag;
    }

    setCurrentNodeInfo(x19) {
        if (x19 === undefined) {
            return;
        }
        this.currentNodeInfo = x19;
    }

    getCurrentNodeInfo() {
        return this.currentNodeInfo;
    }

    setDraggingParentNodeId(w19) {
        if (w19 === undefined) {
            return;
        }
        this.draggingParentNodeId = w19;
    }

    getDraggingParentNodeId() {
        return this.draggingParentNodeId;
    }

    getDraggingCurrentNodeId() {
        return this.draggingCurrentNodeId;
    }

    setDraggingCurrentNodeId(v19) {
        if (v19 === undefined) {
            return;
        }
        this.draggingCurrentNodeId = v19;
    }

    setListItemOpacity(u19) {
        this.listItemOpacity = u19;
    }

    getListItemOpacity(t19) {
        return t19.getNodeCurrentNodeId() === this.getDraggingCurrentNodeId() ? this.listItemOpacity : 1;
    }

    getDragPopupPara() {
        return this.DRAG_POPUP;
    }

    setLastPassIndex(s19) {
        this.lastPassIndex = s19;
    }

    getLastPassIndex() {
        return this.lastPassIndex;
    }

    getIsParentOfInsertNode(o19) {
        if (this.currentNodeInfo === null || o19 === undefined) {
            return false;
        }
        let p19 = this.currentNodeInfo.getNodeInfoNode();
        let q19 = p19.currentNodeId;
        let r19 = this.nodeIdNodeItemMap.get(o19)?.parentNodeId;
        while (r19 !== undefined && r19 !== -1) {
            if (q19 === r19) {
                return true;
            } else {
                r19 = this.nodeIdNodeItemMap.get(r19)?.parentNodeId;
            }
        }
        return false;
    }

    setPassIndex(n19) {
        this.thisPassIndex = n19;
    }

    getPassIndex() {
        return this.thisPassIndex;
    }

    clearTimeOutAboutDelayHighLightAndExpand(i19) {
        if (this.lastPassId !== this.INITIAL_INVALID_VALUE && this.loadedNodeIdAndIndexMap.has(this.lastPassId)) {
            let k19 = this.loadedNodeIdAndIndexMap.get(this.lastPassId);
            this.listNode.forEach((m19) => {
                if (m19.getNodeCurrentNodeId() === this.lastPassId) {
                    m19.setCanShowFlagLine(false);
                    return;
                }
            });
            this.notifyDataChange(k19);
        }
        if ((this.lastTimeoutHighLightId !== this.INITIAL_INVALID_VALUE &&
            this.clearTimeoutHighLightId !== this.lastTimeoutHighLightId)) {
            clearTimeout(this.lastTimeoutHighLightId);
            if (this.lastDelayHighLightIndex !== this.INITIAL_INVALID_VALUE) {
                this.clearHighLight(this.lastDelayHighLightIndex);
                let j19 = this.loadedNodeIdAndIndexMap
                    .get(this.listNode[this.lastDelayHighLightIndex].getNodeCurrentNodeId());
                this.notifyDataChange(j19);
            }
            this.clearTimeoutHighLightId = this.lastTimeoutHighLightId;
        }
        this.lastTimeoutHighLightId = this.timeoutHighLightId;
        this.lastDelayHighLightIndex = i19;
        if ((this.lastTimeoutExpandId !== this.INITIAL_INVALID_VALUE &&
            this.clearTimeoutExpandId !== this.lastTimeoutExpandId)) {
            clearTimeout(this.lastTimeoutExpandId);
            this.clearTimeoutExpandId = this.lastTimeoutExpandId;
        }
        this.lastTimeoutExpandId = this.timeoutExpandId;
        this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE;
    }

    clearHighLight(h19) {
        if (!this.checkIndex(h19)) {
            return;
        }
        this.changeNodeColor(h19, this.listNode[h19].getNodeStatus().normal);
        this.changeNodeHighLightColor(h19, false);
        this.setImageSource(h19, InteractionStatus.FINISH_DRAG_INSERT);
        this.setImageCollapseSource(h19, InteractionStatus.FINISH_DRAG_INSERT);
        this.listNode[h19].setIsHighLight(false);
    }

    changeNodeHighLightColor(f19, g19) {
        if (this.listNode[f19].getNodeItem().mainTitleNode && this.listNode[f19].getIsShowTitle()) {
            this.listNode[f19].getNodeItem().mainTitleNode?.setMainTitleHighLight(g19);
        }
    }

    getAccessibleTitle(x18) {
        let y18 = [];
        while (x18 !== -1) {
            if (x18 === undefined) {
                return '';
            }
            let z18 = this.findParentNodeId(x18);
            let a19 = this.nodeIdNodeItemMap.get(z18);
            if (a19 === undefined || z18 === undefined) {
                return '';
            }
            let b19 = this.getNodeInfoByNodeItem(a19).getNodeInfoData()?.primaryTitle === undefined
                ? '' : this.getNodeInfoByNodeItem(a19).getNodeInfoData().primaryTitle;
            let c19 = this.getNodeInfoByNodeItem(a19).getNodeInfoData()?.secondaryTitle === undefined
                ? '' : this.getNodeInfoByNodeItem(a19).getNodeInfoData().secondaryTitle;
            let d19 = this.getAccessibleTitleText(b19);
            let e19 = this.getAccessibleTitleText(c19);
            y18.unshift(`${d19}, ${e19}`);
            x18 = a19.currentNodeId;
        }
        return y18.join(',');
    }

    getPlaceAccessibleTitle(i18) {
        if (i18 === undefined) {
            return '';
        }
        let j18 = this.findParentNodeId(i18);
        if (j18 === -1) {
            let r18 = [];
            let s18 = this.nodeIdNodeItemMap.get(i18);
            if (s18 === undefined || j18 === undefined) {
                return '';
            }
            let t18 = this.getNodeInfoByNodeItem(s18).getNodeInfoData()?.primaryTitle === undefined
                ? '' : this.getNodeInfoByNodeItem(s18).getNodeInfoData().primaryTitle;
            let u18 = this.getNodeInfoByNodeItem(s18).getNodeInfoData()?.secondaryTitle === undefined
                ? '' : this.getNodeInfoByNodeItem(s18).getNodeInfoData().secondaryTitle;
            let v18 = this.getAccessibleTitleText(t18);
            let w18 = this.getAccessibleTitleText(u18);
            r18.unshift(`${v18}, ${w18}`);
            return r18.join(',');
        } else {
            let k18 = [];
            let v1 = this.nodeIdNodeItemMap.get(i18);
            if (v1 === undefined || j18 === undefined) {
                return '';
            }
            let w1 = this.getNodeInfoByNodeItem(v1).getNodeInfoData()?.primaryTitle === undefined
                ? '' : this.getNodeInfoByNodeItem(v1).getNodeInfoData().primaryTitle;
            let x1 = this.getNodeInfoByNodeItem(v1).getNodeInfoData()?.secondaryTitle === undefined
                ? '' : this.getNodeInfoByNodeItem(v1).getNodeInfoData().secondaryTitle;
            let y1 = this.getAccessibleTitleText(w1);
            let z1 = this.getAccessibleTitleText(x1);
            k18.unshift(`${y1}, ${z1}`);
            while (i18 !== -1) {
                if (i18 === undefined) {
                    return '';
                }
                let b2 = this.findParentNodeId(i18);
                let c2 = this.nodeIdNodeItemMap.get(b2);
                if (c2 === undefined || b2 === undefined) {
                    return '';
                }
                let d2 = this.getNodeInfoByNodeItem(c2).getNodeInfoData()?.primaryTitle === undefined
                    ? '' : this.getNodeInfoByNodeItem(c2).getNodeInfoData().primaryTitle;
                let e2 = this.getNodeInfoByNodeItem(c2).getNodeInfoData()?.secondaryTitle === undefined
                    ? '' : this.getNodeInfoByNodeItem(c2).getNodeInfoData().secondaryTitle;
                let f2 = this.getAccessibleTitleText(d2);
                let g2 = this.getAccessibleTitleText(e2);
                k18.unshift(`${f2}, ${g2}`);
                i18 = c2.currentNodeId;
            }
            return k18.join(',');
        }
    }

    getDraggingAccessible(y17, z17, a18) {
        this.getAccessibleTitle(a18);
        if (z17 === undefined || a18 === undefined) {
            return;
        }
        let b18 = this.findParentNodeId(a18);
        let c18 = y17.indexOf(a18) + 2;
        let d18 = this.getClickNodeChildrenInfo(b18);
        let e18 = d18.map(h18 => h18.itemId);
        let f18 = e18.indexOf(a18) + 2;
        if (b18 === -1 && this.getExpandAndCollapseInfo(z17) === NodeStatus.COLLAPSE ||
            b18 === -1 && this.getExpandAndCollapseInfo(z17) === undefined) {
            this.sendAccessibility(this.getStringByName('treeview_accessibility_move_node_parent', c18));
        } else if (this.getExpandAndCollapseInfo(z17) === NodeStatus.EXPAND) {
            this.sendAccessibility(this.getStringByName('treeview_accessibility_move_node_child',
                this.getAccessibleTitle(a18), 1));
        } else if (b18 !== -1) {
            this.sendAccessibility(this.getStringByName('treeview_accessibility_move_node_child',
                this.getAccessibleTitle(a18), f18));
        }
    }

    getStringByName(v17, ...w17) {
        if (v17) {
            try {
                return getContext()?.resourceManager.getStringByNameSync(v17, ...w17);
            } catch (x17) {
                console.error(`Ace SegmentButton getAccessibilityDescription, error: ${x17.toString()}`);
            }
        }
        return '';
    }

    sendAccessibility(t17) {
        let u17 = ({
            type: 'announceForAccessibility',
            bundleName: getContext()?.abilityInfo?.bundleName,
            triggerAction: 'common',
            textAnnouncedForAccessibility: t17
        });
        accessibility.sendAccessibilityEvent(u17);
    }

    getAccessibleTitleText(o17) {
        let p17 = '';
        try {
            if (typeof o17 === 'string') {
                p17 = o17;
            } else {
                p17 = getContext()?.resourceManager?.getStringSync(o17?.id);
            }
        } catch (q17) {
            let r17 = q17.code;
            let s17 = q17.message;
            hilog.error(0x3900, 'Ace', `treeView getAccessibleTitleText error, code: ${r17}, message: ${s17}`);
        }
        return p17;
    }

    setVisibility(z16, a17, b17, c17) {
        let d17 = (this.thisPassIndex !== a17 || this.flag !== z16) ? true : false;
        this.thisPassIndex = a17;
        if ((d17 || b17) && this.isInnerDrag) {
            this.flag = z16;
            let e17 = this.getData(a17)?.getNodeCurrentNodeId();
            let f17 = this.getData(a17)?.getNodeLevel();
            if (e17 !== undefined) {
                f17 = (this.expandAndCollapseInfo.get(e17) === NodeStatus.EXPAND &&
                    this.flag === Flag.DOWN_FLAG) ? (f17 ? f17 + 1 : undefined) : f17;
                if (this.lastPassId !== this.INITIAL_INVALID_VALUE &&
                this.loadedNodeIdAndIndexMap.has(this.lastPassId)) {
                    let l17 = this.loadedNodeIdAndIndexMap.get(this.lastPassId);
                    this.listNode.forEach((n17) => {
                        if (n17.getNodeCurrentNodeId() === this.lastPassId) {
                            n17.setCanShowFlagLine(false);
                        }
                    });
                    this.notifyDataChange(l17);
                }
                let g17 = this.getData(a17 - 1)?.getNodeCurrentNodeId();
                let h17 = this.getData(a17 + 2)?.getNodeCurrentNodeId();
                let i17 = this.getData(a17 + 1)?.getNodeCurrentNodeId();
                let j17 = this.nodeIdNodeItemMap.get(i17);
                if (this.flag === Flag.DOWN_FLAG && a17 < this.totalCount() - 1) {
                    this.getData(a17)?.setCanShowFlagLine(false);
                    this.getData(a17 + 1)?.setCanShowFlagLine(true);
                    this.getData(a17)?.setCanShowBottomFlagLine(false);
                    this.getData(a17 + 1)?.setFlagLineLeftMargin(f17);
                    this.notifyDataChange(a17);
                    this.notifyDataChange(a17 + 1);
                    this.lastPassId = this.getData(a17 + 1)?.getNodeCurrentNodeId();
                    let k17 = this.nodeIdNodeItemMap.get(i17);
                    if (!k17?.childNodeInfo.isHasChildNode) {
                        this.getDraggingAccessible(c17, i17, i17);
                    } else {
                        this.getDraggingAccessible(c17, i17, h17);
                    }
                } else if (this.flag === Flag.UP_FLAG && a17 < this.totalCount() - 1) {
                    this.getData(a17)?.setCanShowFlagLine(true);
                    this.getData(a17 + 1)?.setCanShowFlagLine(false);
                    this.getData(a17)?.setCanShowBottomFlagLine(false);
                    this.getData(a17)?.setFlagLineLeftMargin(f17);
                    this.notifyDataChange(a17);
                    this.notifyDataChange(a17 + 1);
                    this.lastPassId = this.getData(a17)?.getNodeCurrentNodeId();
                    if (j17?.childNodeInfo.isHasChildNode && j17?.parentNodeId !== -1) {
                        this.getDraggingAccessible(c17, i17, i17);
                    } else if (j17?.childNodeInfo.isHasChildNode && j17?.parentNodeId === -1) {
                        this.getDraggingAccessible(c17, g17, i17);
                    }
                } else if (a17 >= this.totalCount() - 1) {
                    if (this.flag === Flag.DOWN_FLAG) {
                        this.getData(a17)?.setCanShowFlagLine(false);
                        this.getData(a17)?.setCanShowBottomFlagLine(true);
                    } else {
                        this.getData(a17)?.setCanShowFlagLine(true);
                        this.getData(a17)?.setCanShowBottomFlagLine(false);
                    }
                    this.getData(a17)?.setFlagLineLeftMargin(f17);
                    this.notifyDataChange(a17);
                    this.lastPassId = this.getData(a17)?.getNodeCurrentNodeId();
                }
            }
        }
    }

    delayHighLightAndExpandNode(m16, n16, o16) {
        let p16 = m16 !== this.lastDelayExpandIndex ? true : false;
        let q16 = this.getData(o16)?.getIsOverBorder();
        let r16 = this.listNode[m16 + 1]?.getNodeCurrentNodeId();
        let s16 = this.findParentNodeId(n16);
        if (q16) {
            this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE;
        } else {
            this.lastDelayExpandIndex = m16;
        }
        if (q16 || p16) {
            let t16 = !q16 && (!this.isInnerDrag ||
                (this.expandAndCollapseInfo.get(n16) === NodeStatus.COLLAPSE && this.isInnerDrag) ||
                (!this.expandAndCollapseInfo.has(n16) && this.listNode[m16].getIsFolder()));
            if (t16) {
                this.changeNodeColor(m16, this.listNode[m16].getNodeStatus().hover);
                this.notifyDataChange(o16);
                let x16 = this.isInnerDrag ? 1000 : 0;
                this.timeoutHighLightId = setTimeout(() => {
                    this.delayHighLight(m16);
                    this.sendAccessibility(this.getStringByName('treeview_accessibility_move_node_child',
                        this.getPlaceAccessibleTitle(n16), 1));
                }, x16);
            }
            if (q16 || (this.lastTimeoutHighLightId !== this.INITIAL_INVALID_VALUE &&
                this.clearTimeoutHighLightId !== this.lastTimeoutHighLightId)) {
                clearTimeout(this.lastTimeoutHighLightId);
                if (this.lastDelayHighLightIndex !== this.INITIAL_INVALID_VALUE) {
                    this.clearHighLight(this.lastDelayHighLightIndex);
                    this.notifyDataReload();
                }
                this.clearTimeoutHighLightId = this.lastTimeoutHighLightId;
            }
            this.lastTimeoutHighLightId = this.timeoutHighLightId;
            this.lastDelayHighLightIndex = m16;
            if (!q16 && this.expandAndCollapseInfo.get(n16) === NodeStatus.COLLAPSE) {
                let u16 = this.getData(o16)?.getNodeInfoNode().children[0]?.currentNodeId;
                let v16 = 2000;
                this.timeoutExpandId = setTimeout(() => {
                    this.clearHighLight(this.lastDelayHighLightIndex);
                    if (u16 !== undefined) {
                        this.alterFlagLineAndExpandNode(m16, u16);
                    }
                }, v16);
            }
            if (q16 || (this.lastTimeoutExpandId !== this.INITIAL_INVALID_VALUE &&
                this.clearTimeoutExpandId !== this.lastTimeoutExpandId)) {
                clearTimeout(this.lastTimeoutExpandId);
                this.clearTimeoutExpandId = this.lastTimeoutExpandId;
            }
            this.lastTimeoutExpandId = this.timeoutExpandId;
        }
    }

    delayHighLight(j16) {
        this.listNode.forEach((l16) => {
            if (l16.getNodeCurrentNodeId() === this.lastPassId) {
                l16.setCanShowFlagLine(false);
                l16.setCanShowBottomFlagLine(false);
                return;
            }
        });
        this.changeNodeColor(j16, this.listNode[j16].getNodeStatus().highLight);
        this.listNode[j16].setIsHighLight(true);
        this.changeNodeHighLightColor(j16, true);
        this.setImageSource(j16, InteractionStatus.DRAG_INSERT);
        this.setImageCollapseSource(j16, InteractionStatus.DRAG_INSERT);
        this.notifyDataReload();
    }

    alterFlagLineAndExpandNode(d16, e16) {
        this.listNode.forEach((i16) => {
            if (i16.getNodeCurrentNodeId() === this.lastPassId) {
                i16.setCanShowFlagLine(false);
                i16.setCanShowBottomFlagLine(false);
            }
        });
        this.listNode.forEach((h16) => {
            if (this.isInnerDrag && h16.getNodeCurrentNodeId() === e16) {
                h16.setCanShowFlagLine(true);
            }
        });
        this.changeNodeStatus(d16);
        this.handleExpandAndCollapse(d16, true);
        this.lastPassId = e16;
    }

    hideLastLine() {
        if (this.lastPassId !== this.INITIAL_INVALID_VALUE && this.loadedNodeIdAndIndexMap.has(this.lastPassId)) {
            this.listNode.forEach((c16) => {
                if (c16.getNodeCurrentNodeId() === this.lastPassId) {
                    c16.setCanShowFlagLine(false);
                    c16.setCanShowBottomFlagLine(false);
                    return;
                }
            });
            let a16 = this.loadedNodeIdAndIndexMap.get(this.lastPassId);
            this.notifyDataChange(a16);
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

    getSubtitle(z15) {
        if (this.nodeIdAndSubtitleMap.has(z15)) {
            if (typeof this.nodeIdAndSubtitleMap.get(z15) === 'number') {
                return this.nodeIdAndSubtitleMap.get(z15)?.toString();
            } else {
                return this.nodeIdAndSubtitleMap.get(z15);
            }
        } else {
            return '';
        }
    }

    hasSubtitle(y15) {
        return this.nodeIdAndSubtitleMap.has(y15);
    }

    initialParameterAboutDelayHighLightAndExpandIndex() {
        this.lastDelayHighLightIndex = this.INITIAL_INVALID_VALUE;
        this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE;
        this.lastPassIndex = this.INITIAL_INVALID_VALUE;
        this.draggingCurrentNodeId = this.INITIAL_INVALID_VALUE;
        this.flag = Flag.NONE;
    }

    refreshSubtitle(x15) {
        this.nodeIdAndSubtitleMap.set(this.selectedParentNodeId, this.selectedParentNodeSubtitle);
        this.nodeIdAndSubtitleMap.set(x15, this.insertNodeSubtitle);
        this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.selectedParentNodeId));
        this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(x15));
    }

    setNodeSubtitlePara(u15, v15, w15) {
        this.selectedParentNodeId = u15;
        this.selectedParentNodeSubtitle = v15;
        this.insertNodeSubtitle = w15;
    }

    getInsertNodeSubtitle() {
        return this.insertNodeSubtitle;
    }

    getExpandAndCollapseInfo(t15) {
        return this.expandAndCollapseInfo.get(t15);
    }

    getLastDelayHighLightId() {
        return this.lastDelayHighLightId;
    }

    setLastDelayHighLightId() {
        this.listNode.forEach((r15, s15) => {
            if (s15 === this.lastDelayHighLightIndex) {
                this.lastDelayHighLightId = r15.getNodeCurrentNodeId();
            }
        });
    }

    setLastPassId(p15) {
        this.lastPassId = p15;
    }

    setLastDelayHighLightIndex(o15) {
        this.lastDelayHighLightIndex = o15;
    }

    alterDragNode(h14, i14, j14, k14, l14) {
        let m14 = [];
        let n14 = h14;
        let o14 = k14;
        let p14 = l14.getNodeInfoData();
        let q14 = null;
        let r14 = l14.getNodeInfoNode();
        let s14 = false;
        let t14 = this.INITIAL_INVALID_VALUE;
        let u14 = this.INITIAL_INVALID_VALUE;
        let v14 = this.flag === Flag.DOWN_FLAG ? true : false;
        u14 = this.getChildIndex(j14, k14);
        t14 = this.getChildIndex(h14, i14) + 1;
        if (h14 !== j14) {
            t14 = v14 ? t14 + 1 : t14;
        } else {
            if (t14 > u14) {
                t14 = v14 ? t14 : t14 - 1;
            } else {
                t14 = v14 ? t14 + 1 : t14;
            }
        }
        for (let n15 = 0; n15 < this.listNode.length; n15++) {
            if (this.listNode[n15].getNodeCurrentNodeId() === i14) {
                s14 = this.listNode[n15].getIsHighLight();
                if (this.flag === Flag.DOWN_FLAG && this.expandAndCollapseInfo.get(i14) === NodeStatus.EXPAND) {
                    n14 = i14;
                    t14 = 0;
                } else if (this.flag === Flag.UP_FLAG && this.expandAndCollapseInfo.get(i14) ===
                NodeStatus.EXPAND &&
                    this.listNode[n15].getCanShowFlagLine() === false) {
                    n14 = i14;
                    t14 = 0;
                } else if (s14) {
                    n14 = i14;
                    t14 = 0;
                }
                break;
            }
        }
        let w14 = {
            currentNodeId: o14,
            parentNodeId: n14,
            childIndex: t14,
        };
        this.appEventBus.emit(TreeListenType.NODE_MOVE, w14);
        m14.push({ parentId: n14, currentId: o14, data: p14 });
        let x14 = (j15, k15) => {
            if (j15) {
                n14 = j15.parentNodeId;
                o14 = j15.currentNodeId;
                for (let m15 = 0; m15 < k15.length; m15++) {
                    if (k15[m15].getNodeCurrentNodeId() === o14) {
                        q14 = k15[m15];
                        break;
                    }
                }
                if (q14 === null) {
                    return false;
                }
                let l15 = q14.getNodeInfoData();
                if (n14 !== j14) {
                    m14.push({ parentId: n14, currentId: o14, data: l15 });
                }
                return false;
            }
            return false;
        };
        this.dragTraverseNodeDF(x14, r14, this.listNode);
        let y14 = this.removeNode(k14, j14);
        if (y14.length === 0) {
            return;
        }
        let z14 = i14;
        let a15 = v14;
        if (this.expandAndCollapseInfo.get(i14) === NodeStatus.EXPAND) {
            a15 = false;
            this.listNode.forEach((i15) => {
                if (i15.getNodeCurrentNodeId() === i14 && i15.getCanShowFlagLine() === false) {
                    if (i15.getNodeInfoNode().children.length) {
                        z14 = i15.getNodeInfoNode().children[0].currentNodeId;
                    } else {
                        z14 = this.INITIAL_INVALID_VALUE;
                    }
                }
            });
        } else if (!this.expandAndCollapseInfo.get(i14) && s14) {
            this.expandAndCollapseInfo.set(i14, NodeStatus.EXPAND);
        }
        let b15 = this.addDragNode(m14[0].parentId, m14[0].currentId, z14, a15, m14[0].data);
        if (!b15) {
            return;
        }
        for (let f15 = 1; f15 < m14.length; f15++) {
            let g15 = this.addNode(m14[f15].parentId, m14[f15].currentId, m14[f15].data, false);
            if (!g15) {
                return;
            }
        }
        for (let e15 = 0; e15 < this.listNode.length; e15++) {
            if (this.listNode[e15].getNodeCurrentNodeId() === j14) {
                if (this.listNode[e15].getNodeItem().imageCollapse === null) {
                    this.listNode[e15].handleImageCollapseAfterAddNode(false);
                    this.expandAndCollapseInfo.delete(j14);
                    break;
                }
            }
        }
        let c15 = [...this.listNode];
        this.reloadListNode(c15);
    }

    reloadListNode(z13) {
        let a14 = 0;
        let b14 = 0;
        this.listNode.splice(0, this.listNode.length);
        this.loadedNodeIdAndIndexMap.clear();
        this.loadedListNode.splice(0, this.loadedListNode.length);
        this.traverseNodeDF((d14) => {
            let e14 = d14.currentNodeId;
            if (e14 >= 0) {
                if (this.nodeIdNodeParamMap.has(e14)) {
                    let f14 = new NodeInfo(d14, this.nodeIdNodeParamMap.get(e14));
                    f14.addImageCollapse(d14.getChildNodeInfo().isHasChildNode);
                    this.listNode.push(f14);
                    this.nodeIdAndNodeIndexMap.set(f14.getNodeCurrentNodeId(), b14++);
                    if (this.expandAndCollapseInfo.get(e14) === NodeStatus.EXPAND) {
                        f14.getNodeItem()
                            .imageCollapse =
                            CollapseImageNodeFlyweightFactory.changeImageCollapseSource(NodeStatus.EXPAND,
                                f14.getNodeItem().imageCollapse?.isCollapse);
                    } else if (this.expandAndCollapseInfo.get(e14) === NodeStatus.COLLAPSE) {
                        f14.getNodeItem()
                            .imageCollapse =
                            CollapseImageNodeFlyweightFactory.changeImageCollapseSource(NodeStatus.COLLAPSE,
                                f14.getNodeItem().imageCollapse?.isCollapse);
                    }
                    for (let g14 = 0; g14 < z13.length; g14++) {
                        if (z13[g14].getNodeCurrentNodeId() === f14.getNodeCurrentNodeId()) {
                            f14.setNodeIsShow(z13[g14].getNodeIsShow());
                            f14.setListItemHeight(z13[g14].getListItemHeight());
                            if (f14.getNodeItem().mainTitleNode && f14.getIsShowTitle()) {
                                f14.getNodeItem().mainTitleNode.title = z13[g14].getNodeItem().mainTitleNode?.title;
                            }
                            break;
                        }
                    }
                    if (f14.getNodeIsShow()) {
                        this.loadedNodeIdAndIndexMap.set(f14.getNodeCurrentNodeId(), a14++);
                        this.loadedListNode.push(f14);
                    }
                }
            }
            return false;
        });
    }

    getFlagLine() {
        return this.FLAG_LINE;
    }

    getVisibility(w13) {
        let x13 = this.loadedNodeIdAndIndexMap.get(w13.getNodeCurrentNodeId()) - 1;
        if (x13 > this.INITIAL_INVALID_VALUE) {
            let y13 = this.getData(x13);
            return (w13.getCanShowFlagLine() === true && !w13.getIsHighLight() && !y13?.getIsHighLight()) ?
            Visibility.Visible : Visibility.Hidden;
        } else {
            return (w13.getCanShowFlagLine() === true && !w13.getIsHighLight()) ?
            Visibility.Visible : Visibility.Hidden;
        }
    }

    getSubTitlePara() {
        return this.subTitle;
    }

    getIsFolder(v13) {
        if (this.loadedNodeIdAndIndexMap.has(v13)) {
            return this.getData(this.loadedNodeIdAndIndexMap.get(v13))?.getIsFolder();
        }
        return false;
    }

    getSubTitleFontColor(u13) {
        return u13 ? this.subTitle.highLightFontColor : this.treeViewTheme.secondaryTitleFontColor;
    }

    getChildIndex(n13, o13) {
        let p13 = this.INITIAL_INVALID_VALUE;
        if (this.nodeIdNodeItemMap.has(n13)) {
            let q13 = this.nodeIdNodeItemMap.get(n13);
            if (q13.getCurrentNodeId() === n13) {
                q13.children.forEach((s13, t13) => {
                    if (s13.getCurrentNodeId() === o13) {
                        p13 = t13;
                        return;
                    }
                });
            }
        }
        return p13;
    }

    setCurrentFocusNodeId(m13) {
        this.currentFocusNodeId = m13;
    }

    getCurrentFocusNodeId() {
        return this.currentFocusNodeId;
    }

    setLastFocusNodeId(l13) {
        this.lastFocusNodeId = l13;
    }

    getLastFocusNodeId() {
        return this.lastFocusNodeId;
    }

    getAddFocusNodeId() {
        return this.addFocusNodeId;
    }

    setFlag(k13) {
        this.flag = k13;
    }

    traverseNodeDF(f13, g13 = this._root) {
        let h13 = [];
        let i13 = false;
        h13.unshift(g13);
        let j13 = h13.shift();
        while (!i13 && j13) {
            i13 = f13(j13) === true;
            if (!i13) {
                h13.unshift(...j13.children);
                j13 = h13.shift();
            }
        }
    }

    traverseSectionNodeDF(w12, x12 = this._root, y12, z12) {
        let a13 = [];
        let b13 = false;
        let c13 = false;
        a13.unshift(x12);
        let d13 = a13.shift();
        while (!b13 && d13) {
            try {
                if (y12 !== undefined && d13.nodeLevel < y12) {
                    c13 = true;
                }
                if (z12 !== undefined && d13.nodeLevel > z12) {
                    c13 = true;
                }
                if (!c13) {
                    b13 = w12(d13);
                }
            } catch (e13) {
                throw new Error('traverseSectionNodeDF function callbacks error');
            }
            if (!b13) {
                a13.unshift(...d13.children);
                d13 = a13.shift();
                c13 = false;
            }
        }
    }

    updateParentChildNum(r12, s12, t12) {
        let u12 = r12.parentNodeId;
        while (u12 >= 0) {
            if (this.nodeIdNodeItemMap.has(u12)) {
                let v12 = this.nodeIdNodeItemMap.get(u12);
                v12.getChildNodeInfo().allChildNum =
                    s12 ? v12.getChildNodeInfo().allChildNum + t12 : v12.getChildNodeInfo().allChildNum - t12;
                u12 = v12.parentNodeId;
            } else {
                hilog.error(LOG_CODE, TAG, 'updateParentChildNum: parent node not found.');
                break;
            }
        }
    }

    findParentNodeId(p12) {
        let q12 = new NodeItem(emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(p12)) {
            q12 = this.nodeIdNodeItemMap.get(p12);
        }
        return q12.parentNodeId;
    }

    refreshRemoveNodeData(e12, f12) {
        let g12 = [];
        if (e12.length === 0) {
            return;
        }
        let h12 = undefined;
        for (let m12 = 0; m12 < e12.length; m12++) {
            if (this.loadedNodeIdAndIndexMap.has(e12[m12])) {
                let o12 = this.loadedNodeIdAndIndexMap.get(e12[m12]);
                g12.push(o12);
            }
            if (h12 === undefined && this.nodeIdAndNodeIndexMap.has(e12[m12])) {
                h12 = this.nodeIdAndNodeIndexMap.get(e12[m12]);
            }
            if (h12 !== undefined) {
                let n12 = this.listNode.splice(h12, 1);
                n12 = null;
            }
            if (this.expandAndCollapseInfo.has(e12[m12])) {
                this.expandAndCollapseInfo.delete(e12[m12]);
            }
        }
        g12.forEach((l12) => {
            this.notifyDataDelete(l12);
            this.notifyDataChange(l12);
        });
        if (f12.getNodeItem().imageCollapse === null) {
            if (this.nodeIdAndNodeIndexMap.has(f12.getNodeCurrentNodeId())) {
                let k12 = this.nodeIdAndNodeIndexMap.get(f12.getNodeCurrentNodeId());
                this.listNode[k12]?.handleImageCollapseAfterAddNode(false);
            }
            this.expandAndCollapseInfo.delete(f12.getNodeCurrentNodeId());
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(f12.getNodeCurrentNodeId()));
        }
        let i12 = {
            currentNodeId: f12.getNodeCurrentNodeId(),
            parentNodeId: f12.getNodeParentNodeId(),
        };
        this.loadedListNodeFunction();
        this.appEventBus.emit(TreeListenType.NODE_DELETE, i12);
    }

    refreshAddNodeData(z11) {
        let a12 = new NodeInfo(new NodeItem(emptyNodeInfo), emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(z11[0])) {
            let d12 = this.nodeIdNodeItemMap.get(z11[0]);
            a12 = new NodeInfo(d12, this.nodeIdNodeParamMap.get(z11[0]));
            a12.addImageCollapse(d12.getChildNodeInfo().isHasChildNode);
        }
        a12.setIsModify(true);
        let b12 = 0;
        for (let c12 = 0; c12 < this.listNode.length; c12++) {
            if (this.listNode[c12].getNodeCurrentNodeId() === a12.getNodeParentNodeId()) {
                b12 = c12;
                if (this.listNode[c12].getNodeItem().imageCollapse === null) {
                    this.listNode[c12].handleImageCollapseAfterAddNode(true);
                    this.notifyDataChange(b12);
                } else if (this.expandAndCollapseInfo.get(this.listNode[c12].getNodeCurrentNodeId()) ===
                NodeStatus.COLLAPSE) {
                    this.changeNodeStatus(b12);
                }
                this.listNode.splice(c12 + 1, 0, a12);
                this.listNode[c12 + 1].setTitleAndInputTextStatus(true);
                this.listNode[c12 + 1].setNodeIsShow(true);
                this.listNode[c12 + 1].setListItemHeight(LIST_ITEM_HEIGHT);
                this.nodeIdAndNodeIndexMap.set(z11[0], c12 + 1);
                this.setImageSource(c12 + 1, InteractionStatus.EDIT);
                this.currentOperation = MenuOperation.ADD_NODE;
                this.notifyDataAdd(c12 + 1);
                this.notificationNodeInfo(c12 + 1, this.currentOperation);
                break;
            }
        }
        this.modifyNodeIndex = b12 + 1;
        this.setClickIndex(b12);
        this.lastIndex = b12;
        this.expandAndCollapseInfo.set(a12.getNodeParentNodeId(), NodeStatus.EXPAND);
        this.handleExpandAndCollapse(b12, true);
    }

    refreshData(u11, v11, w11) {
        let x11 = new NodeInfo(new NodeItem(emptyNodeInfo), emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(v11)) {
            let y11 = this.nodeIdNodeItemMap.get(v11);
            x11 = new NodeInfo(y11, this.nodeIdNodeParamMap.get(v11));
            x11.addImageCollapse(y11.getChildNodeInfo().isHasChildNode);
        }
        if (u11 === MenuOperation.REMOVE_NODE) {
            this.nodeIdAndSubtitleMap.set(v11, this.selectedParentNodeSubtitle);
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(v11));
            this.refreshRemoveNodeData(w11, x11);
        }
        if (u11 === MenuOperation.ADD_NODE) {
            this.addFocusNodeId = w11[0];
            this.nodeIdAndSubtitleMap.set(this.getClickNodeId(), this.selectedParentNodeSubtitle);
            this.nodeIdAndSubtitleMap.set(w11[0], this.insertNodeSubtitle);
            this.refreshAddNodeData(w11);
        }
    }

    removeNode(k11, l11) {
        if (this.nodeIdNodeItemMap.has(l11) && this.nodeIdNodeItemMap.has(k11)) {
            let m11 = this.nodeIdNodeItemMap.get(l11);
            let n11 = this.nodeIdNodeItemMap.get(k11);
            let o11 = [];
            let p11 = n11.indexOfParent;
            let q11 = 0;
            if (p11 < 0) {
                hilog.error(LOG_CODE, TAG, 'node does not exist.');
                return [];
            } else {
                q11 = m11.children[p11].getChildNodeInfo().allChildNum + 1;
                this.freeNodeMemory(m11.children[p11], o11);
                for (let t11 = p11; t11 < m11.children.length; t11++) {
                    m11.children[t11].indexOfParent -= 1;
                }
                let s11 = m11.children.splice(p11, 1);
                s11 = null;
                this.judgeImageCollapse(l11);
            }
            m11.getChildNodeInfo().childNum = m11.children.length;
            m11.getChildNodeInfo().allChildNum -= (q11);
            let r11 = [];
            r11.push(m11.parentNodeId);
            delayUpdateParentChildNum(false, q11, this.nodeIdNodeItemMap, r11);
            return o11;
        } else {
            hilog.error(LOG_CODE, TAG, 'parent does not exist.');
            return [];
        }
    }

    addNode(d11, e11, f11, g11) {
        if (this._root === null) {
            this._root = new NodeItem(emptyNodeInfo);
            this._root.nodeLevel = -1;
            this.nodeIdNodeItemMap.set(-1, this._root);
            this.nodeIdNodeParamMap.set(-1, emptyNodeInfo);
        }
        if (this.nodeIdNodeItemMap.has(d11)) {
            let h11 = this.nodeIdNodeItemMap.get(d11);
            let i11 = new NodeItem(f11);
            if (h11.nodeLevel > this.maxNodeLevel) {
                hilog.error(LOG_CODE, TAG, 'ListDataSource[addNode]: The level of the tree view cannot exceed 50.');
                return false;
            }
            i11.nodeLevel = h11.nodeLevel + 1;
            i11.parentNodeId = d11;
            i11.currentNodeId = e11;
            i11.indexOfParent = h11.children.length;
            f11.parentNodeId = d11;
            f11.currentNodeId = e11;
            if (f11.symbolIconStyle && !f11.icon) {
                f11.icon = 'symbolUsed';
            }
            h11.children.push(i11);
            h11.getChildNodeInfo().isHasChildNode = true;
            h11.getChildNodeInfo().childNum = h11.children.length;
            h11.getChildNodeInfo().allChildNum += 1;
            this.judgeImageCollapse(d11);
            if (g11) {
                this.updateNodeIdList.push(h11.parentNodeId);
            } else {
                let j11 = [];
                j11.push(h11.parentNodeId);
                delayUpdateParentChildNum(true, 1, this.nodeIdNodeItemMap, j11);
            }
            this.nodeIdNodeParamMap.set(e11, f11);
            this.nodeIdNodeItemMap.set(e11, i11);
            return true;
        } else {
            hilog.error(LOG_CODE, TAG, 'ListDataSource[addNode]: Parent node not found.');
            return false;
        }
    }

    judgeImageCollapse(a11) {
        if (a11 === undefined) {
            return;
        }
        let b11 = this.nodeIdNodeItemMap.get(a11);
        let c11 = this.nodeIdAndNodeIndexMap.get(a11);
        if (b11.children.length > 0) {
            if (this.nodeIdAndNodeIndexMap.has(a11)) {
                this.listNode[c11]?.addImageExpand(true);
            }
        } else {
            this.listNode[c11]?.addImageExpand(false);
        }
    }

    freeNodeMemory(s10, t10) {
        let u10 = [];
        let v10 = (z10) => {
            u10.push(z10);
            return false;
        };
        this.traverseNodeDF(v10, s10);
        u10.forEach((y10) => {
            t10.push(y10.getCurrentNodeId());
            this.nodeIdNodeItemMap.delete(y10.getCurrentNodeId());
            this.nodeIdNodeParamMap.delete(y10.getCurrentNodeId());
            y10 = new NodeItem(emptyNodeInfo);
        });
    }

    getNodeInfoByNodeItem(q10) {
        if (q10?.currentNodeId === undefined) {
            hilog.error(LOG_CODE, TAG, 'getNodeInfoByNodeItem: currentId is undefined');
            return new NodeInfo(new NodeItem(emptyNodeInfo), emptyNodeInfo);
        }
        if (!this.nodeIdAndNodeIndexMap.has(q10.currentNodeId)) {
            hilog.error(LOG_CODE, TAG, 'getNodeInfoByNodeItem: not has nodeItem.');
            return new NodeInfo(new NodeItem(emptyNodeInfo), emptyNodeInfo);
        }
        let r10 = this.nodeIdAndNodeIndexMap.get(q10.currentNodeId);
        return this.listNode[r10];
    }

    getNewNodeParam(l10) {
        let m10 = new NodeItem(emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(l10)) {
            m10 = this.nodeIdNodeItemMap.get(l10);
        }
        let n10 = emptyNodeInfo;
        if (m10) {
            let o10 = this.getNodeInfoByNodeItem(m10);
            if (m10.children.length === 0) {
                if (o10.getNodeItem().imageNode !== undefined) {
                    n10.icon = o10.getNodeItem().imageNode?.normalSource;
                    n10.symbolIconStyle = o10.getNodeItem().imageNode?.symbolNormalSource;
                    n10.selectedIcon = o10.getNodeItem().imageNode?.selectedSource;
                    n10.symbolSelectedIconStyle = o10.getNodeItem().imageNode?.symbolSelectedSource;
                    n10.editIcon = o10.getNodeItem().imageNode?.editSource;
                    n10.symbolEditIconStyle = o10.getNodeItem().imageNode?.symbolEditSource;
                    n10.container = o10.getMenu();
                } else {
                    n10.icon = undefined;
                    n10.symbolIconStyle = undefined;
                    n10.selectedIcon = undefined;
                    n10.symbolSelectedIconStyle = undefined;
                    n10.editIcon = undefined;
                    n10.symbolEditIconStyle = undefined;
                    n10.container = o10.getMenu();
                }
            } else if (m10.children.length > 0) {
                let p10 = this.getNodeInfoByNodeItem(m10.children[0]);
                if (o10.getNodeItem().imageNode !== null) {
                    n10.icon = (p10.getNodeItem().imageNode !== undefined) ?
                        p10.getNodeItem().imageNode?.normalSource : undefined;
                    n10.symbolIconStyle = (p10.getNodeItem().imageNode !== undefined) ?
                        p10.getNodeItem().imageNode?.symbolNormalSource : undefined;
                    n10.selectedIcon = (p10.getNodeItem().imageNode !== undefined) ?
                        p10.getNodeItem().imageNode?.selectedSource : undefined;
                    n10.symbolSelectedIconStyle = (p10.getNodeItem().imageNode !== undefined) ?
                        p10.getNodeItem().imageNode?.symbolSelectedSource : undefined;
                    n10.editIcon = (p10.getNodeItem().imageNode !== undefined) ?
                        p10.getNodeItem().imageNode?.editSource : undefined;
                    n10.symbolEditIconStyle = (p10.getNodeItem().imageNode !== undefined) ?
                        p10.getNodeItem().imageNode?.symbolEditSource : undefined;
                    n10.container = p10.getMenu();
                } else {
                    n10.icon = undefined;
                    n10.symbolIconStyle = undefined;
                    n10.selectedIcon = undefined;
                    n10.symbolSelectedIconStyle = undefined;
                    n10.editIcon = undefined;
                    n10.symbolEditIconStyle = undefined;
                    n10.container = p10.getMenu();
                }
            }
        }
        return n10;
    }

    getClickChildId(g10) {
        let h10 = new NodeItem(emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(g10)) {
            h10 = this.nodeIdNodeItemMap.get(g10);
        }
        if (h10) {
            if (h10.children.length === 0) {
                return [];
            } else if (h10.children.length > 0) {
                let i10 = new Array(h10.children.length);
                for (let k10 = 0; k10 < i10.length; k10++) {
                    i10[k10] = 0;
                }
                for (let j10 = 0; j10 < h10.children.length && j10 < i10.length; j10++) {
                    i10[j10] = h10.children[j10].currentNodeId;
                }
                return i10;
            }
        }
        return [];
    }

    getClickNodeChildrenInfo(a10) {
        let b10 = new NodeItem(emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(a10)) {
            b10 = this.nodeIdNodeItemMap.get(a10);
        }
        if (b10) {
            if (b10.children.length === 0) {
                return [];
            } else if (b10.children.length > 0) {
                let c10 = new Array(b10.children.length);
                for (let f10 = 0; f10 < c10.length; f10++) {
                    c10[f10] = {};
                }
                for (let d10 = 0; d10 < b10.children.length && d10 < c10.length; d10++) {
                    c10[d10].itemId = b10.children[d10].currentNodeId;
                    let e10 = this.getNodeInfoByNodeItem(b10.children[d10]);
                    if (e10.getNodeItem().imageNode) {
                        c10[d10].itemIcon = e10.getNodeItem().imageNode?.source;
                    }
                    if (e10.getNodeItem().mainTitleNode) {
                        c10[d10].itemTitle = e10.getNodeItem().mainTitleNode?.title;
                    }
                    c10[d10].isFolder = e10.getIsFolder();
                }
                return c10;
            }
        }
        return [];
    }

    checkMainTitleIsValid(z9) {
        if (new RegExp('/[\\\/:*?" < > |]/').test(z9)){
            return false;
        }
        if ((new RegExp('/^[\u4e00-\u9fa5]+$/').test(z9) && z9.length > this.MAX_CN_LENGTH) ||
            (!new RegExp('/^[\u4e00-\u9fa5]+$/').test(z9) && z9.length > this.MAX_EN_LENGTH)) {
            return false;
        }
        return true;
    }

    dragTraverseNodeDF(t9, u9 = this._root, v9) {
        let w9 = [];
        let x9 = false;
        w9.unshift(u9);
        let y9 = w9.shift();
        while (!x9 && y9) {
            x9 = t9(y9, v9) === true;
            if (!x9) {
                w9.unshift(...y9.children);
                y9 = w9.shift();
            }
        }
    }

    updateChildIndexOfParent(q9, r9) {
        for (let s9 = q9; s9 < r9.children.length; s9++) {
            r9.children[s9].indexOfParent += 1;
        }
    }

    addDragNode(h9, i9, j9, k9, l9) {
        if (this._root === null) {
            this._root = new NodeItem(emptyNodeInfo);
            this._root.nodeLevel = this.INITIAL_INVALID_VALUE;
        }
        if (this.nodeIdNodeItemMap.has(h9)) {
            let m9 = this.nodeIdNodeItemMap.get(h9);
            let n9 = new NodeItem(l9);
            if (m9.nodeLevel > this.maxNodeLevel) {
                hilog.error(LOG_CODE, TAG, 'addDragNode: The level of the tree view cannot exceed 50.');
                return false;
            }
            n9.nodeLevel = m9.nodeLevel + 1;
            n9.parentNodeId = h9;
            n9.currentNodeId = i9;
            l9.parentNodeId = h9;
            l9.currentNodeId = i9;
            let o9 = this.INITIAL_INVALID_VALUE;
            if (m9.children.length) {
                for (let p9 = 0; p9 < m9.children.length; p9++) {
                    if (m9.children[p9].getCurrentNodeId() === j9) {
                        o9 = p9;
                        break;
                    }
                }
                if (k9) {
                    n9.indexOfParent = o9 + 1;
                    this.updateChildIndexOfParent(n9.indexOfParent, m9);
                    m9.children.splice(o9 + 1, 0, n9);
                } else {
                    n9.indexOfParent = o9 < 0 ? m9.children.length + o9 : o9;
                    this.updateChildIndexOfParent(n9.indexOfParent, m9);
                    m9.children.splice(o9, 0, n9);
                }
            } else {
                n9.indexOfParent = m9.children.length;
                m9.children.push(n9);
            }
            m9.getChildNodeInfo().isHasChildNode = true;
            m9.getChildNodeInfo().childNum = m9.children.length;
            m9.getChildNodeInfo().allChildNum += 1;
            this.updateParentChildNum(m9, true, 1);
            this.nodeIdNodeItemMap.set(i9, n9);
            this.nodeIdNodeParamMap.set(i9, l9);
            return true;
        } else {
            hilog.error(LOG_CODE, TAG, 'addDragNode: Parent node not found.');
            return false;
        }
    }
}

class ButtonGestureModifier {
    constructor(g9) {
        this.fontSize = 1;
        this.controller = null;
        this.controller = g9;
    }

    applyGesture(d9) {
        if (this.fontSize >= ButtonGestureModifier.minFontSize) {
            d9.addGesture(new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime })
                .onAction(() => {
                    if (d9) {
                        this.controller?.open();
                    }
                })
                .onActionEnd(() => {
                    this.controller?.close();
                }));
        } else {
            d9.clearGestures();
        }
    }
}

ButtonGestureModifier.longPressTime = 500;
ButtonGestureModifier.minFontSize = 1.75;

export class TreeViewInner extends ViewPU {
    constructor(w8, x8, y8, z8 = -1, a9 = undefined, b9) {
        super(w8, y8, z8, b9);
        if (typeof a9 === 'function') {
            this.paramsGenerator_ = a9;
        }
        this.__item = new SynchedPropertyNesedObjectPU(x8.item, this, 'item');
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
        this.setInitiallyProvidedValue(x8);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(v8) {
        this.__item.set(v8.item);
        if (v8.listNodeDataSource !== undefined) {
            this.listNodeDataSource = v8.listNodeDataSource;
        }
        if (v8.columnWidth !== undefined) {
            this.columnWidth = v8.columnWidth;
        }
        if (v8.isFocused !== undefined) {
            this.isFocused = v8.isFocused;
        }
        if (v8.index !== undefined) {
            this.index = v8.index;
        }
        if (v8.lastIndex !== undefined) {
            this.lastIndex = v8.lastIndex;
        }
        if (v8.count !== undefined) {
            this.count = v8.count;
        }
        if (v8.followingSystemFontScale !== undefined) {
            this.followingSystemFontScale = v8.followingSystemFontScale;
        }
        if (v8.maxAppFontScale !== undefined) {
            this.maxAppFontScale = v8.maxAppFontScale;
        }
        if (v8.listTreeViewMenu !== undefined) {
            this.listTreeViewMenu = v8.listTreeViewMenu;
        }
        if (v8.callBackClick !== undefined) {
            this.callBackClick = v8.callBackClick;
        }
        if (v8.MAX_CN_LENGTH !== undefined) {
            this.MAX_CN_LENGTH = v8.MAX_CN_LENGTH;
        }
        if (v8.MAX_EN_LENGTH !== undefined) {
            this.MAX_EN_LENGTH = v8.MAX_EN_LENGTH;
        }
        if (v8.INITIAL_INVALID_VALUE !== undefined) {
            this.INITIAL_INVALID_VALUE = v8.INITIAL_INVALID_VALUE;
        }
        if (v8.MAX_TOUCH_DOWN_COUNT !== undefined) {
            this.MAX_TOUCH_DOWN_COUNT = v8.MAX_TOUCH_DOWN_COUNT;
        }
        if (v8.isMultiPress !== undefined) {
            this.isMultiPress = v8.isMultiPress;
        }
        if (v8.touchDownCount !== undefined) {
            this.touchDownCount = v8.touchDownCount;
        }
        if (v8.appEventBus !== undefined) {
            this.appEventBus = v8.appEventBus;
        }
        if (v8.itemPadding !== undefined) {
            this.itemPadding = v8.itemPadding;
        }
        if (v8.textInputPadding !== undefined) {
            this.textInputPadding = v8.textInputPadding;
        }
        if (v8.inputFontSize !== undefined) {
            this.inputFontSize = v8.inputFontSize;
        }
    }

    updateStateVars(u8) {
        this.__item.set(u8.item);
    }

    purgeVariableDependenciesOnElmtId(t8) {
        this.__item.purgeDependencyOnElmtId(t8);
        this.__columnWidth.purgeDependencyOnElmtId(t8);
        this.__isFocused.purgeDependencyOnElmtId(t8);
        this.__index.purgeDependencyOnElmtId(t8);
        this.__lastIndex.purgeDependencyOnElmtId(t8);
        this.__count.purgeDependencyOnElmtId(t8);
        this.__followingSystemFontScale.purgeDependencyOnElmtId(t8);
        this.__maxAppFontScale.purgeDependencyOnElmtId(t8);
        this.__treeViewTheme.purgeDependencyOnElmtId(t8);
        this.__clickButtonFlag.purgeDependencyOnElmtId(t8);
        this.__accessibilityNodeType.purgeDependencyOnElmtId(t8);
        this.__isAccessibilityEnabled.purgeDependencyOnElmtId(t8);
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

    set columnWidth(s8) {
        this.__columnWidth.set(s8);
    }

    get isFocused() {
        return this.__isFocused.get();
    }

    set isFocused(r8) {
        this.__isFocused.set(r8);
    }

    get index() {
        return this.__index.get();
    }

    set index(q8) {
        this.__index.set(q8);
    }

    get lastIndex() {
        return this.__lastIndex.get();
    }

    set lastIndex(p8) {
        this.__lastIndex.set(p8);
    }

    get count() {
        return this.__count.get();
    }

    set count(o8) {
        this.__count.set(o8);
    }

    get followingSystemFontScale() {
        return this.__followingSystemFontScale.get();
    }

    set followingSystemFontScale(n8) {
        this.__followingSystemFontScale.set(n8);
    }

    get maxAppFontScale() {
        return this.__maxAppFontScale.get();
    }

    set maxAppFontScale(m8) {
        this.__maxAppFontScale.set(m8);
    }

    get treeViewTheme() {
        return this.__treeViewTheme.get();
    }

    set treeViewTheme(l8) {
        this.__treeViewTheme.set(l8);
    }

    get clickButtonFlag() {
        return this.__clickButtonFlag.get();
    }

    set clickButtonFlag(k8) {
        this.__clickButtonFlag.set(k8);
    }

    get accessibilityNodeType() {
        return this.__accessibilityNodeType.get();
    }

    set accessibilityNodeType(j8) {
        this.__accessibilityNodeType.set(j8);
    }

    get isAccessibilityEnabled() {
        return this.__isAccessibilityEnabled.get();
    }

    set isAccessibilityEnabled(i8) {
        this.__isAccessibilityEnabled.set(i8);
    }

    aboutToAppear() {
        if (this.item.getNodeItem().imageNode) {
            this.item.imageSource = this.item.getNodeItem().imageNode?.source;
            this.item.symbolSource = this.item.getNodeItem().imageNode?.symbolSource;
        }
        let h8 = this.getUIContext();
        this.followingSystemFontScale = h8.isFollowingSystemFontScale();
        this.maxAppFontScale = h8.getMaxFontScale();
    }

    decideFontScale() {
        let f8 = this.getUIContext();
        let g8 = f8.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.followingSystemFontScale) {
            return 1;
        }
        return Math.min(g8, this.maxAppFontScale, MAX_FONT_SCALE);
    }

    decideSymbolFontScale(b8) {
        if (!b8 || !this.followingSystemFontScale) {
            return 1;
        }
        let c8 = this.getUIContext();
        let d8 = c8.getHostContext()?.config?.fontSizeScale ?? 1;
        let e8 = Math.min(d8, this.maxAppFontScale, MAX_SYMBOL_FONT_SCALE);
        return Math.max(e8, MIN_SYMBOL_FONT_SCALE);
    }

    getInputTextMaxFontSize() {
        let a8 = this.decideFontScale() * this.inputFontSize + 'vp';
        return a8;
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

    checkInvalidPattern(z7) {
        return new RegExp('/[\\\/:*?" < > |]/').test(z7);
    }

    checkIsAllCN(y7) {
        return new RegExp('/^[\u4e00-\u9fa5]+$/').test(y7);
    }

    getAccessibilityReadText(g7) {
        let h7 = this.listNodeDataSource.nodeIdNodeItemMap.get(g7);
        if (h7 === undefined || g7 === undefined) {
            return '';
        }
        let i7 = this.listNodeDataSource.getNodeInfoByNodeItem(h7);
        let j7 = i7?.getNodeInfoData()?.primaryTitle === undefined
            ? '' : i7?.getNodeInfoData()?.primaryTitle;
        let k7 = i7?.getNodeInfoData()?.secondaryTitle === undefined
            ? '' : i7?.getNodeInfoData()?.secondaryTitle;
        let l7 = this.listNodeDataSource.getAccessibleTitleText(j7);
        let m7 = this.listNodeDataSource.getAccessibleTitleText(k7);
        let n7 = `${l7}, ${m7}`;
        let o7 = this.listNodeDataSource.findParentNodeId(g7);
        let p7 = [];
        let q7 = 0;
        let r7 = this.listNodeDataSource.getClickNodeChildrenInfo(o7);
        let s7 = r7.map(x7 => x7.itemId);
        let t7 = s7.indexOf(g7) + 1;
        let u7 = this.listNodeDataSource.getAccessibleTitle(g7);
        if (u7 === undefined) {
            return ' ';
        }
        if (this.accessibilityNodeType === AccessibilityNodeType.PLACE) {
            if (this.listNodeDataSource.findParentNodeId(g7) === -1) {
                for (let w7 = 0; w7 < this.listNodeDataSource.listNode.length; w7++) {
                    if (this.listNodeDataSource.listNode[w7].getNodeParentNodeId() === -1) {
                        p7.push(this.listNodeDataSource.listNode[w7].getNodeCurrentNodeId());
                    }
                }
                q7 = p7.indexOf(g7) + 1;
                return this.listNodeDataSource.getStringByName('treeview_accessibility_place_node_parent', q7);
            } else {
                return this.listNodeDataSource.getStringByName('treeview_accessibility_place_node_child', u7, t7);
            }
        } else if (this.accessibilityNodeType === AccessibilityNodeType.LIFT) {
            return n7;
        } else {
            return n7;
        }
    }

    getAccessibilityDescription() {
        if (this.accessibilityNodeType === AccessibilityNodeType.TEXT) {
            return this.listNodeDataSource.getStringByName('treeview_accessibility_node_desc');
        } else {
            return ' ';
        }
    }

    getAccessibilityReadButtonText(f7) {
        if (this.clickButtonFlag === false) {
            return this.item.getNodeItem().imageCollapse?.collapseSource === ARROW_RIGHT
                ? this.listNodeDataSource.getStringByName('treeview_accessibility_folded_node')
                : this.listNodeDataSource.getStringByName('treeview_accessibility_expanded_node');
        } else {
            return f7 ? this.listNodeDataSource.getStringByName('treeview_accessibility_expand_node')
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

    onTouchNode(c7) {
        this.count++;
        if (this.count > 1) {
            this.count--;
            return;
        }
        this.index = this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId());
        this.listNodeDataSource.setClickIndex(this.index);
        let d7 = this.item.getNodeCurrentNodeId();
        if (c7.type === TouchType.Down) {
            this.item.setNodeColor(this.treeViewTheme.itemPressedBgColor);
        } else if (c7.type === TouchType.Up) {
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
            let e7 = { currentNodeId: d7 };
            this.appEventBus.emit(TreeListenType.NODE_CLICK, e7);
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
        let a7 = this.item.getNodeCurrentNodeId();
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
        let b7 = { currentNodeId: a7 };
        this.appEventBus.emit(TreeListenType.NODE_CLICK, b7);
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
        let x6 = ({
            type: 'requestFocusForAccessibility',
            bundleName: getContext()?.abilityInfo?.bundleName,
            triggerAction: 'common',
            customId: `treeView_button${this.item.getNodeCurrentNodeId()}`
        });
        accessibility.sendAccessibilityEvent(x6).then(() => {
            setTimeout(() => {
                this.clickButtonFlag = true;
            }, ENTER_EXIT_DURATION);
        });
    }

    popupForShowTitle(n6, o6, p6, q6 = null) {
        this.observeComponentCreation2((v6, w6) => {
            Row.create();
            Row.backgroundColor(o6);
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
        this.observeComponentCreation2((t6, u6) => {
            Text.create(n6);
            Text.fontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_body2'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            });
            Text.fontWeight('regular');
            Text.fontColor(p6);
            Text.minFontScale(MIN_FONT_SCALE);
            Text.maxFontScale(this.decideFontScale());
        }, Text);
        Text.pop();
        Row.pop();
    }

    builder(h6 = null) {
        this.observeComponentCreation2((j6, k6) => {
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
        this.observeComponentCreation2((r1, s1) => {
            If.create();
            if (this.item.getNodeIsShow()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((f6, g6) => {
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
                    this.observeComponentCreation2((s5, t5) => {
                        Column.create();
                        Column.opacity(this.listNodeDataSource.getListItemOpacity(ObservedObject.GetRawObject(this.item)));
                        Column.onHover((e6) => {
                            if (e6) {
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
                        Column.onTouch(this.isAccessibilityEnabled ? undefined : (d6) => {
                            this.onTouchNode(d6);
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
                        Column.onMouse((b6) => {
                            let c6 = this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId());
                            if (b6.button === MouseButton.Right) {
                                this.listNodeDataSource.handleEvent(Event.MOUSE_BUTTON_RIGHT,
                                    this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId()));
                                this.listTreeViewMenu = this.item.getMenu();
                                this.listNodeDataSource.setClickIndex(c6);
                                clearTimeout(this.item.getNodeItem().mainTitleNode?.popUpTimeout);
                            }
                            b6.stopPropagation();
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
                        Column.onAreaChange((y5, z5) => {
                            let a6 = Number.parseInt(z5.width.toString());
                            this.columnWidth = a6;
                        });
                    }, Column);
                    this.observeComponentCreation2((q5, r5) => {
                        Stack.create({ alignContent: Alignment.Bottom });
                        Stack.focusable(true);
                    }, Stack);
                    this.observeComponentCreation2((o5, p5) => {
                        Divider.create();
                        Divider.height(this.listNodeDataSource.getFlagLine().flagLineHeight);
                        Divider.color(this.listNodeDataSource.getFlagLine().flagLineColor);
                        Divider.visibility(this.listNodeDataSource.getVisibility(ObservedObject.GetRawObject(this.item)));
                        Divider.lineCap(LineCapStyle.Round);
                        Divider.margin({ start: LengthMetrics.vp(this.item.getFlagLineLeftMargin()) });
                        Divider.focusable(true);
                    }, Divider);
                    this.observeComponentCreation2((m5, n5) => {
                        Row.create({});
                        Row.focusable(true);
                        Row.width('100%');
                        Row.height(this.item.getNodeHeight());
                        Row.padding({ start: LengthMetrics.vp(this.item.getNodeLeftPadding()) });
                        Row.bindContextMenu({ builder: this.builder.bind(this) }, ResponseType.RightClick);
                    }, Row);
                    this.observeComponentCreation2((j5, k5) => {
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
                    this.observeComponentCreation2((j4, k4) => {
                        If.create();
                        if (this.item.getNodeItem().imageNode) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((h5, i5) => {
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
                                this.observeComponentCreation2((p4, q4) => {
                                    If.create();
                                    if (this.item.symbolSource) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((f5, g5) => {
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
                                            this.observeComponentCreation2((t4, u4) => {
                                                If.create();
                                                if (Util.isSymbolResource(this.item.imageSource)) {
                                                    this.ifElseBranchUpdateFunction(0, () => {
                                                        this.observeComponentCreation2((b5, c5) => {
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
                                                        this.observeComponentCreation2((x4, y4) => {
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
                    this.observeComponentCreation2((h4, i4) => {
                        Row.create();
                        Row.layoutWeight(1);
                        Row.focusable(true);
                    }, Row);
                    this.observeComponentCreation2((a4, b4) => {
                        If.create();
                        if (this.item.getNodeItem().mainTitleNode && this.item.getIsShowTitle()) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((f4, g4) => {
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
                    this.observeComponentCreation2((g3, h3) => {
                        If.create();
                        if (this.item.getNodeItem().mainTitleNode && this.item.getNodeItem().inputText &&
                        this.item.getIsShowInputText()) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((y3, z3) => {
                                    Row.create();
                                    Row.backgroundColor(this.item.getNodeItem().inputText?.backgroundColor);
                                    Row.borderRadius(this.item.getNodeItem().inputText?.borderRadius);
                                    Row.margin({
                                        end: getLengthMetricsByResourceOrNumber(this.item.getNodeItem()
                                            .inputText?.itemRightMargin)
                                    });
                                }, Row);
                                this.observeComponentCreation2((m3, n3) => {
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
                                    TextInput.onChange((s3) => {
                                        let t3 = this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId());
                                        let u3 = '';
                                        let v3 = false;
                                        let w3 = false;
                                        if (this.checkInvalidPattern(s3)) {
                                            for (let x3 = 0; x3 < s3.length; x3++) {
                                                if (!this.checkInvalidPattern(s3[x3])) {
                                                    u3 += s3[x3];
                                                }
                                            }
                                            v3 = true;
                                            this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS,
                                                InputError.INVALID_ERROR, true, t3);
                                        } else {
                                            u3 = s3;
                                            v3 = false;
                                        }
                                        if ((this.checkIsAllCN(u3) && u3.length > this.MAX_CN_LENGTH) ||
                                            (!this.checkIsAllCN(u3) && u3.length > this.MAX_EN_LENGTH)) {
                                            u3 = this.checkIsAllCN(u3) ?
                                            u3.substr(0, this.MAX_CN_LENGTH) : u3.substr(0, this.MAX_EN_LENGTH);
                                            w3 = true;
                                            this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS,
                                                InputError.LENGTH_ERROR, true, t3);
                                        } else {
                                            w3 = false;
                                        }
                                        if (!w3 && !v3) {
                                            this.listNodeDataSource.setMainTitleNameOnEdit(t3, u3);
                                        }
                                    });
                                    TextInput.onSubmit((q3) => {
                                        let r3 = this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId());
                                        this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false,
                                            r3);
                                        this.listNodeDataSource.setItemVisibilityOnEdit(r3, MenuOperation.COMMIT_NODE);
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
                    this.observeComponentCreation2((e3, f3) => {
                        Blank.create();
                    }, Blank);
                    Blank.pop();
                    Row.pop();
                    this.observeComponentCreation2((u2, v2) => {
                        If.create();
                        if (this.listNodeDataSource.hasSubtitle(this.item.getNodeCurrentNodeId())) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((c3, d3) => {
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
                                this.observeComponentCreation2((a3, b3) => {
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
                    this.observeComponentCreation2((i2, j2) => {
                        If.create();
                        if (this.item.getNodeItem().imageCollapse) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                if (!If.canRetake(`treeView_button${this.item.getNodeCurrentNodeId()}`)) {
                                    this.observeComponentCreation2((q2, r2) => {
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
                                    this.observeComponentCreation2((o2, p2) => {
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