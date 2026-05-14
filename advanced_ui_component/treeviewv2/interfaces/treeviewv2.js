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

var __decorate = (this && this.__decorate) || function (d150, e150, f150, g150) {
    var h150 = arguments.length,
        i150 = h150 < 3 ? e150 : g150 === null ? g150 = Object.getOwnPropertyDescriptor(e150, f150) : g150, j150;
    if (typeof Reflect === 'object' && typeof Reflect.decorate === 'function')
        i150 = Reflect.decorate(d150, e150, f150, g150); else
        for (var k150 = d150.length - 1; k150 >= 0; k150--)
            if (j150 = d150[k150])
                i150 = (h150 < 3 ? j150(i150) : h150 > 3 ? j150(e150, f150, i150) : j150(e150, f150)) || i150;
    return h150 > 3 && i150 && Object.defineProperty(e150, f150, i150), i150;
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
(function (c150) {
    c150[c150['TOUCH_DOWN'] = 0] = 'TOUCH_DOWN';
    c150[c150['TOUCH_UP'] = 1] = 'TOUCH_UP';
    c150[c150['HOVER'] = 3] = 'HOVER';
    c150[c150['HOVER_OVER'] = 4] = 'HOVER_OVER';
    c150[c150['FOCUS'] = 5] = 'FOCUS';
    c150[c150['BLUR'] = 6] = 'BLUR';
    c150[c150['MOUSE_BUTTON_RIGHT'] = 7] = 'MOUSE_BUTTON_RIGHT';
    c150[c150['DRAG'] = 8] = 'DRAG';
})(Event || (Event = {}));
var MenuOperation;
(function (b150) {
    b150[b150['ADD_NODE'] = 0] = 'ADD_NODE';
    b150[b150['REMOVE_NODE'] = 1] = 'REMOVE_NODE';
    b150[b150['MODIFY_NODE'] = 2] = 'MODIFY_NODE';
    b150[b150['COMMIT_NODE'] = 3] = 'COMMIT_NODE';
})(MenuOperation || (MenuOperation = {}));
var PopUpType;
(function (a150) {
    a150[a150['HINTS'] = 0] = 'HINTS';
    a150[a150['WARNINGS'] = 1] = 'WARNINGS';
})(PopUpType || (PopUpType = {}));
var InputError;
(function (z149) {
    z149[z149['INVALID_ERROR'] = 0] = 'INVALID_ERROR';
    z149[z149['LENGTH_ERROR'] = 1] = 'LENGTH_ERROR';
    z149[z149['NONE'] = 2] = 'NONE';
})(InputError || (InputError = {}));
var Flag;
(function (y149) {
    y149[y149['DOWN_FLAG'] = 0] = 'DOWN_FLAG';
    y149[y149['UP_FLAG'] = 1] = 'UP_FLAG';
    y149[y149['NONE'] = 2] = 'NONE';
})(Flag || (Flag = {}));

export var NodeStatus;
(function (x149) {
    x149[x149['EXPAND'] = 0] = 'EXPAND';
    x149[x149['COLLAPSE'] = 1] = 'COLLAPSE';
})(NodeStatus || (NodeStatus = {}));

export var InteractionStatus;
(function (w149) {
    w149[w149['NORMAL'] = 0] = 'NORMAL';
    w149[w149['SELECTED'] = 1] = 'SELECTED';
    w149[w149['EDIT'] = 2] = 'EDIT';
    w149[w149['FINISH_EDIT'] = 3] = 'FINISH_EDIT';
    w149[w149['DRAG_INSERT'] = 4] = 'DRAG_INSERT';
    w149[w149['FINISH_DRAG_INSERT'] = 5] = 'FINISH_DRAG_INSERT';
})(InteractionStatus || (InteractionStatus = {}));
var CollapseImageType;
(function (v149) {
    v149[v149['ARROW_DOWN'] = 0] = 'ARROW_DOWN';
    v149[v149['ARROW_RIGHT'] = 1] = 'ARROW_RIGHT';
    v149[v149['ARROW_DOWN_WHITE'] = 2] = 'ARROW_DOWN_WHITE';
    v149[v149['ARROW_RIGHT_WHITE'] = 3] = 'ARROW_RIGHT_WHITE';
})(CollapseImageType || (CollapseImageType = {}));
var AccessibilityNodeType;
(function (u149) {
    u149[u149['TEXT'] = 0] = 'TEXT';
    u149[u149['PLACE'] = 1] = 'PLACE';
    u149[u149['LIFT'] = 2] = 'LIFT';
})(AccessibilityNodeType || (AccessibilityNodeType = {}));

class Util {
    static isSymbolResource(s149) {
        if (!Util.isResourceType(s149)) {
            return false;
        }
        let t149 = s149;
        return t149.type === RESOURCE_TYPE_SYMBOL;
    }

    static isResourceType(r149) {
        if (!r149) {
            return false;
        }
        if (typeof r149 === 'string' || typeof r149 === 'undefined') {
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

    createNodeByNodeParam(p149) {
        let q149 = this.createNode();
        if (p149.icon) {
            q149.imageNode = new ImageNode(p149.icon, p149.symbolIconStyle, {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_alpha_content_fourth'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            }, IMAGE_NODE_HEIGHT, IMAGE_NODE_WIDTH, p149.selectedIcon, p149.symbolSelectedIconStyle, p149.editIcon,
                p149.symbolEditIconStyle);
        }
        if (p149.primaryTitle) {
            q149.mainTitleNode = new MainTitleNode(p149.primaryTitle);
        }
        return q149;
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

    static getInstance() {
        if (!TreeViewTheme.instance) {
            TreeViewTheme.instance = new TreeViewTheme();
        }
        return TreeViewTheme.instance;
    }
}

let NodeInfo = class NodeInfo {
    constructor(n149, o149) {
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
        this.node = n149;
        this.nodeParam = o149;
        this.nodeItemView = TreeViewNodeItemFactory.getInstance().createNodeByNodeParam(o149);
        this.popUpInfo = {
            popUpIsShow: false,
            popUpEnableArrow: false,
            popUpColor: undefined,
            popUpText: '',
            popUpTextColor: undefined,
        };
        this.nodeHeight = NODE_HEIGHT;
        this.nodeLeftPadding = n149.nodeLevel * LEVEL_MARGIN + MARGIN_OFFSET;
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
        this.flagLineLeftMargin = n149.nodeLevel * LEVEL_MARGIN + MARGIN_OFFSET;
    }

    addImageCollapse(m149) {
        if (m149) {
            this.nodeItemView.imageCollapse =
                CollapseImageNodeFlyweightFactory.getCollapseImageNodeByType(CollapseImageType.ARROW_RIGHT);
        } else {
            this.nodeItemView.imageCollapse = undefined;
        }
    }

    addImageExpand(l149) {
        if (l149) {
            this.nodeItemView.imageCollapse =
                CollapseImageNodeFlyweightFactory.getCollapseImageNodeByType(CollapseImageType.ARROW_DOWN);
        } else {
            this.nodeItemView.imageCollapse = undefined;
        }
    }

    setFontColor(k149) {
        this.fontColor = k149;
    }

    getFontColor() {
        return this.fontColor;
    }

    getPopUpInfo() {
        return this.popUpInfo;
    }

    setPopUpIsShow(j149) {
        this.popUpInfo.popUpIsShow = j149;
    }

    setPopUpEnableArrow(i149) {
        this.popUpInfo.popUpEnableArrow = i149;
    }

    setPopUpColor(h149) {
        this.popUpInfo.popUpColor = h149;
    }

    setPopUpText(g149) {
        this.popUpInfo.popUpText = g149;
    }

    setPopUpTextColor(f149) {
        this.popUpInfo.popUpTextColor = f149;
    }

    getIsShowTitle() {
        return this.isShowTitle;
    }

    getIsShowInputText() {
        return this.isShowInputText;
    }

    setTitleAndInputTextStatus(e149) {
        if (e149) {
            this.isShowTitle = false;
            this.isShowInputText = true;
        } else {
            this.isShowTitle = true;
            this.isShowInputText = false;
        }
    }

    handleImageCollapseAfterAddNode(d149) {
        if (d149) {
            this.nodeItemView.imageCollapse =
                CollapseImageNodeFlyweightFactory.getCollapseImageNodeByType(CollapseImageType.ARROW_DOWN);
        } else {
            this.nodeItemView.imageCollapse = undefined;
        }
    }

    setNodeColor(c149) {
        if (c149 === undefined) {
            return;
        }
        this.nodeColor = c149;
    }

    getNodeColor() {
        return this.nodeColor;
    }

    setListItemHeight(b149) {
        this.listItemHeight = b149;
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

    setNodeIsShow(a149) {
        this.nodeIsShow = a149;
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

    setNodeBorder(z148) {
        this.nodeBorder.borderWidth = z148 ? this.borderWidth.has : this.borderWidth.none;
    }

    getChildNodeInfo() {
        return this.node.childNodeInfo;
    }

    getMenu() {
        return this.nodeParam.container;
    }

    setIsSelected(y148) {
        this.isSelected = y148;
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

    setCanShowFlagLine(x148) {
        this.canShowFlagLine = x148;
    }

    getCanShowFlagLine() {
        return this.canShowFlagLine;
    }

    setFlagLineLeftMargin(w148) {
        if (w148 === undefined) {
            return;
        }
        this.flagLineLeftMargin = w148 * LEVEL_MARGIN + MARGIN_OFFSET;
    }

    getFlagLineLeftMargin() {
        return this.flagLineLeftMargin;
    }

    getNodeLevel() {
        return this.node.nodeLevel;
    }

    setIsOverBorder(v148) {
        this.isOverBorder = v148;
    }

    getIsOverBorder() {
        return this.isOverBorder;
    }

    setCanShowBottomFlagLine(u148) {
        this.canShowBottomFlagLine = u148;
    }

    getCanShowBottomFlagLine() {
        return this.canShowBottomFlagLine;
    }

    setIsHighLight(t148) {
        this.isHighLight = t148;
    }

    getIsHighLight() {
        return this.isHighLight;
    }

    setIsModify(s148) {
        this.isModify = s148;
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
], NodeInfo.prototype, 'treeViewTheme', void 0);
__decorate([
    Trace
], NodeInfo.prototype, 'fontColor', void 0);
NodeInfo = __decorate([
    ObservedV2
], NodeInfo);

export { NodeInfo };

export var TreeListenTypeV2;
(function (r148) {
    r148['NODE_CLICK'] = 'NodeClick';
    r148['NODE_ADD'] = 'NodeAdd';
    r148['NODE_DELETE'] = 'NodeDelete';
    r148['NODE_MODIFY'] = 'NodeModify';
    r148['NODE_MOVE'] = 'NodeMove';
})(TreeListenTypeV2 || (TreeListenTypeV2 = {}));

export class TreeListenerV2 {
    constructor() {
        this._events = [];
        this._once_events = [];
    }

    on(n148, o148) {
        if (Array.isArray(n148)) {
            for (let p148 = 0, q148 = n148.length; p148 < q148; p148++) {
                this.on(n148[p148], o148);
            }
        } else {
            (this._events[n148] || (this._events[n148] = [])).push(o148);
        }
    }

    once(l148, m148) {
        if (Array.isArray(l148)) {
            this.off(l148, m148);
        } else {
            (this._once_events[l148] || (this._once_events[l148] = [])).push(m148);
        }
    }

    off(e148, f148) {
        if (e148 === null) {
            this._events = [];
        }
        if (Array.isArray(e148)) {
            for (let j148 = 0, k148 = e148.length; j148 < k148; j148++) {
                this.off(e148[j148], f148);
            }
        }
        let g148 = this._events[e148];
        if (!g148) {
            return;
        }
        if (f148 === null) {
            this._events[e148] = null;
        }
        let h148 = g148.length;
        while (h148--) {
            let i148 = g148[h148];
            if (i148 === f148) {
                g148.splice(h148, 1);
                break;
            }
        }
    }

    emit(u147, v147) {
        if (this._once_events[u147]) {
            let a148 = Array.from(this._once_events[u147]);
            if (a148) {
                for (let b148 = 0, c148 = a148.length; b148 < c148; b148++) {
                    try {
                        a148[b148](v147);
                    } catch (d148) {
                        throw new Error('once function callbacks error.');
                    }
                }
                this._once_events[u147] = null;
            }
        } else if (this._events[u147]) {
            let w147 = Array.from(this._events[u147]);
            if (w147) {
                for (let x147 = 0, y147 = w147.length; x147 < y147; x147++) {
                    try {
                        w147[x147](v147);
                    } catch (z147) {
                        throw new Error('on function callbacks error.');
                    }
                }
            }
        }
    }
}

export class TreeListenerManagerV2 {
    constructor() {
        this.appEventBus = new TreeListenerV2();
    }

    static getInstance() {
        if (AppStorage.Get('app_key_event_bus') === undefined) {
            AppStorage.SetOrCreate('app_key_event_bus', new TreeListenerManagerV2());
        }
        return AppStorage.Get('app_key_event_bus');
    }

    getTreeListenerV2() {
        return this.appEventBus;
    }
}
TreeListenerManagerV2.APP_KEY_EVENT_BUS = 'app_key_event_bus';

export class TreeViewV2 extends ViewV2 {
    constructor(o147, p147, q147, r147 = -1, s147, t147) {
        super(o147, r147, t147);
        this.initParam('treeControllerV2',
            (p147 && 'treeControllerV2' in p147) ? p147.treeControllerV2 : new TreeControllerV2());
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
        this.listTreeViewMenu = 'listTreeViewMenu' in p147 ? p147.listTreeViewMenu : this.NullBuilder;
        this.MAX_CN_LENGTH = 254;
        this.MAX_EN_LENGTH = 255;
        this.INITIAL_INVALID_VALUE = -1;
        this.MAX_TOUCH_DOWN_COUNT = 0;
        this.isMultiPress = false;
        this.touchDownCount = this.INITIAL_INVALID_VALUE;
        this.appEventBus = TreeListenerManagerV2.getInstance().getTreeListenerV2();
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

    resetStateVarsOnReuse(n147) {
        this.resetParam('treeControllerV2',
            (n147 && 'treeControllerV2' in n147) ? n147.treeControllerV2 : new TreeControllerV2());
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
        this.listTreeViewMenu = 'listTreeViewMenu' in n147 ? n147.listTreeViewMenu : this.NullBuilder;
    }

    NullBuilder(m147 = null) {
    }
    ;

    onWillApplyTheme(l147) {
        this.treeViewTheme.itemSelectedBgColor = l147.colors.interactiveSelect;
        this.treeViewTheme.itemPressedBgColor = l147.colors.interactivePressed;
        this.treeViewTheme.itemHoverBgColor = l147.colors.interactiveHover;
        this.treeViewTheme.primaryTitleFontColor = l147.colors.fontPrimary;
        this.treeViewTheme.secondaryTitleFontColor = l147.colors.fontSecondary;
        this.treeViewTheme.primaryTitleActiveFontColor = l147.colors.interactiveActive;
        this.treeViewTheme.borderFocusedColor = l147.colors.interactiveFocus;
        this.treeViewTheme.leftIconColor = l147.colors.iconSecondary;
        this.treeViewTheme.leftIconActiveColor = l147.colors.interactiveActive;
        this.treeViewTheme.arrowIconColor = l147.colors.iconPrimary;
        this.treeControllerV2.treeViewTheme = this.treeViewTheme;
    }

    aboutToAppear() {
        if (this.treeControllerV2 !== null) {
            this.listNodeDataSource = this.treeControllerV2.getListNodeDataSource();
            this.nodeList = this.treeControllerV2.getListNodeDataSource().listNode;
            this.item = this.treeControllerV2.getListNodeDataSource().listNode;
        }
        let j147 = this.getUIContext();
        this.followingSystemFontScale = j147.isFollowingSystemFontScale();
        this.maxAppFontScale = j147.getMaxFontScale();
        accessibility.on('screenReaderStateChange', (k147) => {
            this.isAccessibilityEnabled = k147;
        });
    }

    decideFontScale() {
        let h147 = this.getUIContext();
        let i147 = h147.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.followingSystemFontScale) {
            return 1;
        }
        return Math.min(i147, this.maxAppFontScale, MAX_FONT_SCALE);
    }

    decideSymbolFontScale(d147) {
        if (!d147 || !this.followingSystemFontScale) {
            return 1;
        }
        let e147 = this.getUIContext();
        let f147 = e147.getHostContext()?.config?.fontSizeScale ?? 1;
        let g147 = Math.min(f147, this.maxAppFontScale, MAX_SYMBOL_FONT_SCALE);
        return Math.max(g147, MIN_SYMBOL_FONT_SCALE);
    }

    popupForShowTitle(v146, w146, x146, y146 = null) {
        this.observeComponentCreation2((b147, c147) => {
            Row.create();
            Row.backgroundColor(w146);
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
        this.observeComponentCreation2((z146, a147) => {
            Text.create(v146);
            Text.fontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_body2'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Text.fontWeight('regular');
            Text.fontColor(x146);
            Text.minFontScale(MIN_FONT_SCALE);
            Text.maxFontScale(this.decideFontScale());
        }, Text);
        Text.pop();
        Row.pop();
    }

    builder(u146 = null) {
        this.listTreeViewMenu.bind(this)();
    }

    draggingPopup(w145, x145 = null) {
        this.observeComponentCreation2((s146, t146) => {
            Row.create();
            Row.id(`treeView_node_lift${w145.getNodeCurrentNodeId()}`);
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
        this.observeComponentCreation2((e146, f146) => {
            If.create();
            if (w145.getNodeItem().imageNode) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((q146, r146) => {
                        Row.create();
                        Row.backgroundColor(COLOR_IMAGE_ROW);
                        Row.margin({
                            end: getLengthMetricsByResourceOrNumber(w145.getNodeItem().imageNode?.itemRightMargin)
                        });
                        Row.height(w145.getNodeItem().imageNode?.itemHeight *
                            this.decideSymbolFontScale(w145.getNodeItem().imageNode?.symbolNormalSource !== undefined ||
                                Util.isSymbolResource(w145.getNodeItem().imageNode?.normalSource)));
                        Row.width(w145.getNodeItem().imageNode?.itemWidth *
                            this.decideSymbolFontScale(w145.getNodeItem().imageNode?.symbolNormalSource !== undefined ||
                                Util.isSymbolResource(w145.getNodeItem().imageNode?.normalSource)));
                    }, Row);
                    this.observeComponentCreation2((g146, h146) => {
                        If.create();
                        if (w145.getNodeItem().imageNode?.symbolNormalSource) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((o146, p146) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.attributeModifier.bind(this)(w145.getNodeItem()
                                        .imageNode?.symbolNormalSource);
                                    SymbolGlyph.fontSize(`${w145.getNodeItem().imageNode?.itemHeight *
                                        this.decideSymbolFontScale(true)}vp`);
                                    SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                    SymbolGlyph.opacity(this.listNodeDataSource.getDragPopupPara().imageOpacity);
                                }, SymbolGlyph);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((i146, j146) => {
                                    If.create();
                                    if (Util.isSymbolResource(w145.getNodeItem().imageNode?.normalSource)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((m146, n146) => {
                                                SymbolGlyph.create(w145.getNodeItem().imageNode?.normalSource);
                                                SymbolGlyph.fontSize(`${w145.getNodeItem().imageNode?.itemHeight *
                                                    this.decideSymbolFontScale(true)}vp`);
                                                SymbolGlyph.opacity(this.listNodeDataSource.getDragPopupPara()
                                                    .imageOpacity);
                                            }, SymbolGlyph);
                                        });
                                    } else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((k146, l146) => {
                                                Image.create(w145.getNodeItem().imageNode?.normalSource);
                                                Image.objectFit(ImageFit.Contain);
                                                Image.height(w145.getNodeItem().imageNode?.itemHeight);
                                                Image.width(w145.getNodeItem().imageNode?.itemWidth);
                                                Image.opacity(this.listNodeDataSource.getDragPopupPara().imageOpacity);
                                                Image.matchTextDirection((w145.getNodeItem()
                                                    .imageCollapse?.collapseSource === ARROW_RIGHT ||
                                                    w145.getNodeItem().imageCollapse?.collapseSource ===
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
        this.observeComponentCreation2((c146, d146) => {
            Row.create();
            Row.constraintSize({
                minWidth: w145.getNodeItem().imageNode ?
                    this.listNodeDataSource.getDragPopupPara().textConstraintSize.minWidth1 :
                    this.listNodeDataSource.getDragPopupPara().textConstraintSize.minWidth2,
                maxWidth: w145.getNodeItem().imageNode ?
                    this.listNodeDataSource.getDragPopupPara().textConstraintSize.maxWidth1 :
                    this.listNodeDataSource.getDragPopupPara().textConstraintSize.maxWidth2,
            });
        }, Row);
        this.observeComponentCreation2((y145, z145) => {
            If.create();
            if (w145.getNodeItem().mainTitleNode && w145.getIsShowTitle()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((a146, b146) => {
                        Text.create(w145.getNodeItem().mainTitleNode?.title);
                        Text.maxLines(1);
                        Text.minFontScale(MIN_FONT_SCALE);
                        Text.maxFontScale(this.decideFontScale());
                        Text.fontSize(w145.getNodeItem().mainTitleNode?.size);
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

    setImageSources(t145, u145) {
        let v145 = this.nodeList[t145];
        v145.setIsSelected(u145 === InteractionStatus.SELECTED ||
            u145 === InteractionStatus.EDIT || u145 === InteractionStatus.FINISH_EDIT);
        if (v145.getNodeItem().mainTitleNode !== null && u145 !== InteractionStatus.DRAG_INSERT &&
            u145 !== InteractionStatus.FINISH_DRAG_INSERT) {
            v145.getNodeItem().mainTitleNode?.setMainTitleSelected(u145 === InteractionStatus.SELECTED ||
                u145 === InteractionStatus.FINISH_EDIT);
        }
        if (v145.getNodeItem().imageNode !== null) {
            v145.getNodeItem().imageNode?.setImageSource(u145);
        }
    }

    touchInner(q145, r145) {
        this.viewLastIndex = this.listNodeDataSource.getLastIndex();
        let s145 = this.listNodeDataSource.findIndex(q145.getNodeCurrentNodeId());
        if (r145.type === TouchType.Down) {
            if (s145 !== this.viewLastIndex) {
                this.clearLastIndexColor();
                this.listNodeDataSource.lastIndex = s145;
                this.listNodeDataSource.setClickIndex(s145);
            }
        }
        if (r145.type === TouchType.Up) {
            this.listNodeDataSource.listNode[s145].setIsSelected(true);
            this.listNodeDataSource.setImageSource(s145, InteractionStatus.SELECTED);
            if (this.listNodeDataSource.listNode[s145].getNodeItem().imageNode !== null) {
                this.listNodeDataSource.listNode[s145].imageSource = this.listNodeDataSource.listNode[s145]
                    .getNodeItem().imageNode?.source;
                this.listNodeDataSource.listNode[s145].symbolSource = this.listNodeDataSource.listNode[s145]
                    .getNodeItem().imageNode?.symbolSource;
            }
            if (s145 !== this.viewLastIndex) {
                this.clearLastIndexColor();
                this.listNodeDataSource.lastIndex = s145;
                this.listNodeDataSource.setClickIndex(s145);
            }
            this.viewLastIndex = s145;
        }
        if (this.listNodeDataSource.getLastIndex() !== -1 && s145 !== this.listNodeDataSource.getLastIndex()) {
            this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false,
                this.listNodeDataSource.getLastIndex());
            this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(),
                MenuOperation.COMMIT_NODE);
        }
    }

    clickInner(o145) {
        this.viewLastIndex = this.listNodeDataSource.getLastIndex();
        let p145 = this.listNodeDataSource.findIndex(o145.getNodeCurrentNodeId());
        if (p145 !== this.viewLastIndex) {
            this.clearLastIndexColor();
            this.listNodeDataSource.lastIndex = p145;
            this.listNodeDataSource.setClickIndex(p145);
        }
        this.listNodeDataSource.listNode[p145].setIsSelected(true);
        this.listNodeDataSource.setImageSource(p145, InteractionStatus.SELECTED);
        if (this.listNodeDataSource.listNode[p145].getNodeItem().imageNode !== null) {
            this.listNodeDataSource.listNode[p145].imageSource = this.listNodeDataSource.listNode[p145]
                .getNodeItem().imageNode?.source;
            this.listNodeDataSource.listNode[p145].symbolSource = this.listNodeDataSource.listNode[p145]
                .getNodeItem().imageNode?.symbolSource;
        }
        if (p145 !== this.viewLastIndex) {
            this.clearLastIndexColor();
            this.listNodeDataSource.lastIndex = p145;
            this.listNodeDataSource.setClickIndex(p145);
        }
        this.viewLastIndex = p145;
        if (this.listNodeDataSource.getLastIndex() !== -1 && p145 !== this.listNodeDataSource.getLastIndex()) {
            this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false,
                this.listNodeDataSource.getLastIndex());
            this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(),
                MenuOperation.COMMIT_NODE);
        }
    }

    initialRender() {
        this.observeComponentCreation2((e144, f144) => {
            List.create({});
            List.onDragMove((f145, g145) => {
                if (this.isMultiPress) {
                    hilog.error(LOG_CODE, TAG, 'drag error, a item has been dragged');
                    return;
                }
                let h145 = LIST_ITEM_HEIGHT;
                let i145 = Math.floor(f145.getY() /
                    (h145 / FLAG_NUMBER)) %
                    FLAG_NUMBER ? Flag.DOWN_FLAG : Flag.UP_FLAG;
                let j145 = JSON.parse(g145).insertIndex;
                let k145 = false;
                if (j145 >= this.listNodeDataSource.totalCount()) {
                    i145 = Flag.DOWN_FLAG;
                    j145 = this.listNodeDataSource.totalCount() - 1;
                    this.listNodeDataSource.getData(j145)?.setIsOverBorder(true);
                    k145 = true;
                } else {
                    this.listNodeDataSource.getData(j145)?.setIsOverBorder(false);
                }
                let l145 = this.listNodeDataSource.getData(j145);
                let m145 = l145?.getNodeCurrentNodeId();
                if (j145 !== this.listNodeDataSource.getLastPassIndex() && this.listNodeDataSource.getIsInnerDrag()) {
                    let n145 = this.listNodeDataSource.getIsParentOfInsertNode(m145);
                    if (n145) {
                        this.listNodeDataSource.setPassIndex(j145);
                        if (m145 !== undefined) {
                            this.listNodeDataSource.clearTimeOutAboutDelayHighLightAndExpand(this.listNodeDataSource.findIndex(m145));
                        }
                        this.listNodeDataSource.setFlag(Flag.NONE);
                        return;
                    }
                }
                this.listNodeDataSource.setLastPassIndex(j145);
                this.listNodeDataSource.setVisibility(i145, j145 - 1, k145, this.allParentNode);
                if (m145 !== undefined && m145 !== this.listNodeDataSource.getDraggingCurrentNodeId()) {
                    this.listNodeDataSource.delayHighLightAndExpandNode(this.listNodeDataSource.findIndex(m145), m145,
                        j145);
                }
            });
            List.onDragEnter((c145, d145) => {
                if (this.listNodeDataSource.getIsInnerDrag()) {
                    this.listNodeDataSource.setIsDrag(true);
                    let e145 = DRAG_OPACITY;
                    this.listNodeDataSource.setListItemOpacity(e145);
                }
            });
            List.onDragLeave((z144, a145) => {
                this.listNodeDataSource.hideLastLine();
                this.listNodeDataSource.clearLastTimeoutHighLight();
                this.listNodeDataSource.clearLastTimeoutExpand();
                let b145 = DRAG_OPACITY_NONE;
                this.listNodeDataSource.setListItemOpacity(b145);
                this.listNodeDataSource.setIsDrag(false);
                this.listNodeDataSource.notifyDataReload();
            });
            List.onDrop((g144, h144) => {
                this.accessibilityNodeType = AccessibilityNodeType.PLACE;
                this.listNodeDataSource.clearLastTimeoutExpand();
                let i144 = DRAG_OPACITY_NONE;
                this.listNodeDataSource.setListItemOpacity(i144);
                let j144 = JSON.parse(h144).insertIndex;
                let k144 = this.dropSelectedIndex;
                if (k144 - 1 > this.listNodeDataSource.totalCount() || k144 === undefined) {
                    hilog.error(LOG_CODE, TAG, 'drag error, currentNodeIndex is not found');
                    this.listNodeDataSource.setIsDrag(false);
                    return;
                }
                if (j144 === this.listNodeDataSource.totalCount()) {
                    hilog.info(LOG_CODE, TAG, 'need to insert into the position of the last line');
                    j144 -= 1;
                }
                let l144 = this.listNodeDataSource.getData(j144);
                if (l144 === undefined) {
                    return;
                }
                let m144 = l144.getNodeCurrentNodeId();
                if (!this.listNodeDataSource.getIsDrag() || !this.listNodeDataSource.getIsInnerDrag()) {
                    this.listNodeDataSource.clearLastTimeoutHighLight();
                    this.listNodeDataSource.setIsInnerDrag(false);
                    this.listNodeDataSource.hideLastLine();
                    this.listNodeDataSource.initialParameterAboutDelayHighLightAndExpandIndex();
                    this.listNodeDataSource.refreshSubtitle(m144);
                    this.listNodeDataSource.notifyDataReload();
                    return;
                }
                let n144 = this.listNodeDataSource.getCurrentNodeInfo();
                let o144 = l144.getNodeParentNodeId();
                let p144 = this.listNodeDataSource.getDraggingCurrentNodeId();
                let q144 = this.listNodeDataSource.getDraggingParentNodeId();
                let r144 = this.listNodeDataSource.getIsParentOfInsertNode(m144);
                if (r144) {
                    this.listNodeDataSource.clearLastTimeoutHighLight();
                    this.listNodeDataSource.setIsInnerDrag(false);
                    this.listNodeDataSource.hideLastLine();
                    this.listNodeDataSource.notifyDataChange(j144);
                    this.listNodeDataSource.initialParameterAboutDelayHighLightAndExpandIndex();
                    this.listNodeDataSource.setIsDrag(false);
                    let y144 = this.listNodeDataSource.findIndex(p144);
                    this.listNodeDataSource.setClickIndex(y144);
                    this.listNodeDataSource.handleEvent(Event.DRAG, y144);
                    return;
                }
                if (this.listNodeDataSource.getExpandAndCollapseInfo(p144) === NodeStatus.EXPAND) {
                    this.listNodeDataSource.expandAndCollapseNode(this.listNodeDataSource.findIndex(p144));
                }
                let s144 = false;
                if (this.listNodeDataSource.getExpandAndCollapseInfo(m144) === NodeStatus.COLLAPSE) {
                    let x144 = this.listNodeDataSource.findIndex(m144);
                    if (this.listNodeDataSource.listNode[x144].getIsHighLight()) {
                        this.listNodeDataSource.expandAndCollapseNode(x144);
                    }
                    s144 = true;
                }
                this.listNodeDataSource.setLastDelayHighLightId();
                if (n144 !== null && p144 !== m144) {
                    this.listNodeDataSource.alterDragNode(o144, m144, q144, p144, n144);
                    this.listNodeDataSource.hideLastLine();
                } else {
                    this.listNodeDataSource.hideLastLine();
                    this.listNodeDataSource.setLastPassId(p144);
                    this.listNodeDataSource.hideLastLine();
                }
                let t144 = this.listNodeDataSource.findIndex(this.listNodeDataSource.getLastDelayHighLightId());
                this.listNodeDataSource.setLastDelayHighLightIndex(t144);
                this.listNodeDataSource.clearLastTimeoutHighLight();
                this.listNodeDataSource.initialParameterAboutDelayHighLightAndExpandIndex();
                this.listNodeDataSource.setIsDrag(false);
                let u144 = this.listNodeDataSource.findIndex(p144);
                this.listNodeDataSource.setClickIndex(u144);
                this.listNodeDataSource.handleEvent(Event.DRAG, u144);
                this.listNodeDataSource.setIsInnerDrag(false);
                this.listNodeDataSource.notifyDataReload();
                this.listNodeDataSource.listNode[u144].fontColor = this.treeViewTheme.primaryTitleActiveFontColor;
                if (this.viewLastIndex !== -1 && k144 !== this.viewLastIndex) {
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
                this.listNodeDataSource.lastIndex = u144;
                let v144 = n144?.getNodeParentNodeId();
                this.listNodeDataSource.judgeImageCollapse(v144);
                let w144 = ({
                    type: 'requestFocusForAccessibility',
                    bundleName: getContext()?.abilityInfo?.bundleName,
                    triggerAction: 'common',
                    customId: `treeView_node${p144}`
                });
                accessibility.sendAccessibilityEvent(w144).then(() => {
                    setTimeout(() => {
                        this.accessibilityNodeType = AccessibilityNodeType.TEXT;
                    }, ENTER_EXIT_DURATION);
                    console.log(`test123 Succeeded in send event, eventInfo is ${JSON.stringify(w144)}`);
                });
            });
        }, List);
        {
            const a143 = d143 => {
                const e143 = d143;
                {
                    const f143 = (o143, p143) => {
                        ListItem.create(() => {
                        }, false);
                        ListItem.width('100%');
                        ListItem.height(e143.getListItemHeight());
                        ListItem.padding({
                            start: LengthMetrics.resource(this.itemPadding.left),
                            end: LengthMetrics.resource(this.itemPadding.right)
                        });
                        ListItem.align(Alignment.Start);
                        ListItem.onDragStart((q143, r143) => {
                            this.accessibilityNodeType = AccessibilityNodeType.LIFT;
                            if (this.listNodeDataSource.getIsDrag() || this.listNodeDataSource.getIsInnerDrag() ||
                                this.isMultiPress) {
                                hilog.error(LOG_CODE, TAG, 'drag error, a item has been dragged');
                                return;
                            }
                            this.dropSelectedIndex = JSON.parse(r143).selectedIndex;
                            let s143 = JSON.parse(r143).selectedIndex;
                            let t143 = this.listNodeDataSource.getData(s143);
                            let u143 = e143.getNodeCurrentNodeId();
                            if (s143 >= this.listNodeDataSource.totalCount() || s143 === undefined) {
                                hilog.error(LOG_CODE, TAG, 'drag error, currentNodeIndex is not found in onDragStart');
                                return;
                            }
                            this.listNodeDataSource.setIsInnerDrag(true);
                            this.listNodeDataSource.setIsDrag(true);
                            this.listNodeDataSource.setCurrentNodeInfo(t143);
                            this.listNodeDataSource.setDraggingCurrentNodeId(t143?.getNodeCurrentNodeId());
                            this.listNodeDataSource.setDraggingParentNodeId(t143?.getNodeParentNodeId());
                            let v143 = DRAG_OPACITY;
                            this.listNodeDataSource.setListItemOpacity(v143);
                            this.listNodeDataSource.notifyDataChange(s143);
                            if (u143 !== t143?.getNodeCurrentNodeId()) {
                                hilog.error(LOG_CODE, TAG, 'drag is too fast, it attribute a fault to OH');
                                this.listNodeDataSource.setIsDrag(false);
                                return;
                            }
                            let w143 = t143.getNodeInfoData()?.primaryTitle === undefined ? '' :
                                t143.getNodeInfoData()?.primaryTitle;
                            let x143 = t143.getNodeInfoData()?.secondaryTitle === undefined ? '' :
                                t143.getNodeInfoData()?.secondaryTitle;
                            let y143 = this.listNodeDataSource.getAccessibleTitleText(w143);
                            let z143 = this.listNodeDataSource.getAccessibleTitleText(x143);
                            let a144 = `${y143}, ${z143}`;
                            this.listNodeDataSource.sendAccessibility(this.listNodeDataSource.getStringByName('treeview_accessibility_lift_node',
                                a144));
                            let b144 = [];
                            for (let d144 = 0; d144 < this.listNodeDataSource.listNode.length; d144++) {
                                if (this.listNodeDataSource.listNode[d144].getNodeParentNodeId() === -1) {
                                    b144.push(this.listNodeDataSource.listNode[d144].getNodeCurrentNodeId());
                                }
                            }
                            this.allParentNode = b144;
                            let c144 = ({
                                type: 'requestFocusForAccessibility',
                                bundleName: getContext()?.abilityInfo?.bundleName,
                                triggerAction: 'common',
                                customId: `treeView_node_lift${u143}`
                            });
                            accessibility.sendAccessibilityEvent(c144).then(() => {
                                setTimeout(() => {
                                    this.accessibilityNodeType = AccessibilityNodeType.TEXT;
                                }, ENTER_EXIT_DURATION);
                            });
                            return {
                                builder: () => {
                                    this.draggingPopup.call(this, t143);
                                }
                            };
                        });
                    };
                    const g143 = () => {
                        this.observeComponentCreation2(f143, ListItem);
                        this.observeComponentCreation2((l143, m143) => {
                            Row.create();
                            Row.onTouch(this.isAccessibilityEnabled ? undefined : (n143) => {
                                this.touchInner(e143, n143);
                            });
                        }, Row);
                        {
                            this.observeComponentCreation2((h143, i143) => {
                                if (i143) {
                                    let j143 = new TreeViewInner(this, {
                                        item: e143,
                                        listNodeDataSource: this.listNodeDataSource,
                                        index: this.listNodeDataSource.findIndex(e143.getNodeCurrentNodeId()),
                                        listTreeViewMenu: this.listTreeViewMenu,
                                        callBackClick: () => this.clickInner(e143),
                                    }, undefined, h143, () => {
                                    }, {
                                        page: 'library/src/main/ets/components/0508/treeviewv2/source/treeviewv2.ets',
                                        line: 1298,
                                        col: 13
                                    });
                                    ViewV2.create(j143);
                                    let k143 = () => {
                                        return {
                                            item: e143,
                                            listNodeDataSource: this.listNodeDataSource,
                                            index: this.listNodeDataSource.findIndex(e143.getNodeCurrentNodeId()),
                                            listTreeViewMenu: this.listTreeViewMenu,
                                            callBackClick: () => this.clickInner(e143)
                                        };
                                    };
                                    j143.paramsGenerator_ = k143;
                                } else {
                                    this.updateStateVarsOfChildByElmtId(h143, {
                                        item: e143,
                                        listNodeDataSource: this.listNodeDataSource,
                                        index: this.listNodeDataSource.findIndex(e143.getNodeCurrentNodeId()),
                                        callBackClick: () => this.clickInner(e143)
                                    });
                                }
                            }, { name: 'TreeViewInner' });
                        }
                        Row.pop();
                        ListItem.pop();
                    };
                    g143();
                }
            };
            const b143 = (c143) => JSON.stringify(c143);
            LazyForEach.create('1', this, this.listNodeDataSource, a143, b143);
            LazyForEach.pop();
        }
        List.pop();
    }

    updateStateVars(z142) {
        if (z142 === undefined) {
            return;
        }
        if ('treeControllerV2' in z142) {
            this.updateParam('treeControllerV2', z142.treeControllerV2);
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
    Provider()
], TreeViewV2.prototype, 'treeViewTheme', void 0);
__decorate([
    Provider()
], TreeViewV2.prototype, 'clickButtonFlag', void 0);
__decorate([
    Provider()
], TreeViewV2.prototype, 'accessibilityNodeType', void 0);
__decorate([
    Provider()
], TreeViewV2.prototype, 'isAccessibilityEnabled', void 0);

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
        let y142 = this.listNodeDataSource.getClickNodeId();
        return this.listNodeDataSource.getClickNodeChildrenInfo(y142);
    }

    getChildrenId() {
        let x142 = this.listNodeDataSource.getClickNodeId();
        return this.listNodeDataSource.getClickChildId(x142);
    }

    removeNode() {
        let u142 = this.listNodeDataSource.getClickNodeId();
        if (u142 < 0) {
            return;
        }
        let v142 = this.listNodeDataSource.findParentNodeId(u142);
        let w142 = this.listNodeDataSource.removeNode(u142, v142);
        this.listNodeDataSource.refreshData(MenuOperation.REMOVE_NODE, v142, w142);
        this.nodeIdList.splice(this.nodeIdList.indexOf(u142), 1);
        this.listNodeDataSource.lastIndex = -1;
    }

    modifyNode() {
        let t142 = this.listNodeDataSource.getClickNodeId();
        this.listNodeDataSource.setItemVisibilityOnEdit(t142, MenuOperation.MODIFY_NODE);
    }

    add(n142) {
        let o142 = this.listNodeDataSource.getClickNodeId();
        if (o142 === this.listNodeDataSource.ROOT_NODE_ID || !this.listNodeDataSource.getIsFolder(o142)) {
            return;
        }
        let p142 = this.listNodeDataSource.getNewNodeParam(o142);
        this.nodeIdList.push(this.nodeIdList[this.nodeIdList.length - 1] + 1);
        let q142 = this.nodeIdList[this.nodeIdList.length - 1];
        let r142 = this.listNodeDataSource.addNode(o142, q142, {
            isFolder: p142.isFolder,
            icon: p142.icon,
            symbolIconStyle: p142.symbolIconStyle,
            selectedIcon: p142.selectedIcon,
            symbolSelectedIconStyle: p142.symbolSelectedIconStyle,
            editIcon: p142.editIcon,
            symbolEditIconStyle: p142.symbolEditIconStyle,
            primaryTitle: '新建文件夹',
            container: p142.container,
            secondaryTitle: p142.secondaryTitle,
        }, n142);
        if (!r142) {
            return;
        }
        this.listNodeDataSource.refreshData(MenuOperation.ADD_NODE, o142, [q142]);
        this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false,
            this.listNodeDataSource.getLastIndex());
        this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(),
            MenuOperation.COMMIT_NODE);
        this.listNodeDataSource.listNode[this.listNodeDataSource.getLastIndex()]
            .setFontColor(this.treeViewTheme.primaryTitleFontColor);
        let s142 = this.listNodeDataSource.findIndex(q142);
        this.listNodeDataSource.setClickIndex(s142);
        this.listNodeDataSource.handleEvent(Event.TOUCH_UP, s142);
    }

    addNode(j142) {
        if (j142 === undefined) {
            this.add(this.initBuild);
            return this;
        } else {
            for (let m142 = 0; m142 < this.nodeIdList.length; m142++) {
                if (j142.currentNodeId === this.nodeIdList[m142].valueOf()) {
                    throw new Error('ListTreeNode[addNode]: ' +
                        'The parameters of the new node cannot contain the same currentNodeId.');
                    return this;
                }
            }
            let k142 = false;
            if (j142.primaryTitle !== undefined &&
                !this.listNodeDataSource.checkMainTitleIsValid(j142.primaryTitle.toString())) {
                throw new Error('ListTreeNode[addNode]: The directory name cannot contain ' +
                    'the following characters\ /: *? "< > | or exceeds the maximum length.');
                return this;
            }
            if (j142.primaryTitle === null && j142.icon === null && j142.symbolIconStyle === null) {
                throw new Error('ListTreeNode[addNode]: ' +
                    'The icon|symbolIconStyle and directory name cannot be empty at the same time.');
                return this;
            }
            if (j142.currentNodeId === this.ROOT_NODE_ID || j142.currentNodeId === null) {
                throw new Error('ListTreeNode[addNode]: currentNodeId can not be -1 or null.');
                return this;
            }
            if (j142.currentNodeId !== undefined) {
                this.nodeIdList.push(j142.currentNodeId);
            }
            if (j142.parentNodeId !== undefined) {
                if (j142.currentNodeId !== undefined) {
                    k142 =
                        this.listNodeDataSource.addNode(j142.parentNodeId, j142.currentNodeId, j142, this.initBuild);
                }
            }
            if (!k142) {
                return this;
            }
            if (!this.initBuild && j142.parentNodeId !== undefined) {
                let l142 = this.nodeIdList[this.nodeIdList.length - 1];
                this.listNodeDataSource.refreshData(MenuOperation.ADD_NODE, j142.parentNodeId, [l142]);
            }
            return this;
        }
    }

    refreshNode(g142, h142, i142) {
        this.listNodeDataSource.setNodeSubtitlePara(g142, h142, i142);
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

    getData(f142) {
        return undefined;
    }

    registerDataChangeListener(e142) {
        if (this.listeners.indexOf(e142) < 0) {
            this.listeners.push(e142);
        }
    }

    unregisterDataChangeListener(c142) {
        const d142 = this.listeners.indexOf(c142);
        if (d142 >= 0) {
            this.listeners.splice(d142, 1);
        }
    }

    notifyDataReload() {
        this.listeners.forEach(b142 => {
            b142.onDataReloaded();
        });
    }

    notifyDataAdd(z141) {
        this.listeners.forEach(a142 => {
            a142.onDataAdd(z141);
        });
    }

    notifyDataChange(x141) {
        if (x141 === undefined) {
            return;
        }
        this.listeners.forEach(y141 => {
            y141.onDataChange(x141);
        });
    }

    notifyDataDelete(v141) {
        this.listeners.forEach(w141 => {
            w141.onDataDelete(v141);
        });
    }

    notifyDataMove(s141, t141) {
        this.listeners.forEach(u141 => {
            u141.onDataMove(s141, t141);
        });
    }
}

function delayUpdateParentChildNum(m141, n141, o141, p141) {
    let q141 = setTimeout(() => {
        p141.forEach((r141) => {
            updateParentChildNumHandler(r141, o141, m141, n141);
        });
        clearTimeout(q141);
    }, DELAY_TIME);
}

function updateParentChildNumHandler(g141, h141, i141, j141) {
    let k141 = g141;
    while (k141 >= 0) {
        if (h141.has(k141)) {
            let l141 = h141.get(k141);
            l141.getChildNodeInfo().allChildNum =
                i141 ? l141.getChildNodeInfo().allChildNum + j141 : l141.getChildNodeInfo().allChildNum - j141;
            k141 = l141.parentNodeId;
        } else {
            hilog.error(LOG_CODE, TAG, 'updateParentChildNumHandler: parent node not found');
            break;
        }
    }
}

function delaySortNodeIdList(c141) {
    let d141 = setTimeout(() => {
        c141.sort((e141, f141) => e141 - f141);
        clearTimeout(d141);
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
        this.appEventBus = TreeListenerManagerV2.getInstance().getTreeListenerV2();
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

    checkIndex(b141) {
        if (b141 < 0 || b141 >= this.listNode.length) {
            hilog.error(LOG_CODE, TAG, 'check index fail');
            return false;
        }
        return true;
    }

    changeNodeColor(z140, a141) {
        if (!this.checkIndex(z140)) {
            return;
        }
        this.listNode[z140].setNodeColor(a141);
        this.listNode[z140].setNodeBorder(false);
    }

    getNodeColor(y140) {
        return this.listNode[y140].getNodeColor();
    }

    handleFocusEffect(w140, x140) {
        if (this.listNode[w140].getNodeIsShow()) {
            this.listNode[w140].setNodeBorder(x140);
        }
    }

    setImageSource(t140, u140) {
        if (!this.checkIndex(t140)) {
            return;
        }
        let v140 = this.listNode[t140];
        v140.setIsSelected(u140 === InteractionStatus.SELECTED ||
            u140 === InteractionStatus.EDIT || u140 === InteractionStatus.FINISH_EDIT);
        if (v140.getNodeItem().mainTitleNode !== null && u140 !== InteractionStatus.DRAG_INSERT &&
            u140 !== InteractionStatus.FINISH_DRAG_INSERT) {
            v140.getNodeItem().mainTitleNode?.setMainTitleSelected(u140 === InteractionStatus.SELECTED ||
                u140 === InteractionStatus.FINISH_EDIT);
        }
        if (v140.getNodeItem().imageNode !== null) {
            v140.getNodeItem().imageNode?.setImageSource(u140);
        }
    }

    setImageCollapseSource(q140, r140) {
        let s140 = this.listNode[q140];
        if (s140.getNodeItem().imageCollapse !== undefined) {
            s140.getNodeItem().imageCollapse = CollapseImageNodeFlyweightFactory.getCollapseImageNode(r140,
                this.expandAndCollapseInfo.get(s140.getNodeCurrentNodeId()), s140.getNodeItem().imageCollapse?.type);
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
        let o140 = 0;
        this.loadedNodeIdAndIndexMap.clear();
        this.nodeIdAndNodeIndexMap.clear();
        this.loadedListNode.splice(0, this.loadedListNode.length);
        for (let p140 = 0; p140 < this.listNode.length; p140++) {
            this.nodeIdAndNodeIndexMap.set(this.listNode[p140].getNodeCurrentNodeId(), p140);
            if (this.listNode[p140].getNodeIsShow()) {
                this.loadedNodeIdAndIndexMap.set(this.listNode[p140].getNodeCurrentNodeId(), o140++);
                this.loadedListNode.push(this.listNode[p140]);
            }
        }
    }

    changeNodeStatus(l140) {
        if (l140 >= this.listNode.length) {
            hilog.error(LOG_CODE, TAG, 'changeNodeStatus clickIndex error.');
            return;
        }
        let m140 = l140;
        let n140 = this.listNode[l140].getNodeCurrentNodeId();
        if (this.expandAndCollapseInfo.get(n140) === NodeStatus.EXPAND) {
            this.expandAndCollapseInfo.set(n140, NodeStatus.COLLAPSE);
            this.listNode[m140].getNodeItem()
                .imageCollapse = CollapseImageNodeFlyweightFactory.changeImageCollapseSource(NodeStatus.COLLAPSE,
                this.listNode[m140].getNodeItem().imageCollapse?.isCollapse);
        } else if (this.expandAndCollapseInfo.get(n140) === NodeStatus.COLLAPSE) {
            this.expandAndCollapseInfo.set(n140, NodeStatus.EXPAND);
            this.listNode[m140].getNodeItem()
                .imageCollapse = CollapseImageNodeFlyweightFactory.changeImageCollapseSource(NodeStatus.EXPAND,
                this.listNode[m140].getNodeItem().imageCollapse?.isCollapse);
        }
    }

    handleExpandAndCollapse(b140, c140) {
        if (b140 >= this.listNode.length) {
            hilog.error(LOG_CODE, TAG, 'handleExpandAndCollapse clickIndex error.');
            return;
        }
        let d140 = b140;
        let e140 = this.listNode[d140].getNodeCurrentNodeId();
        if (!this.expandAndCollapseInfo.has(e140)) {
            return;
        }
        let f140 = this.expandAndCollapseInfo.get(e140);
        if (this.listNode[d140].getChildNodeInfo().isHasChildNode && f140 === NodeStatus.COLLAPSE) {
            for (let k140 = 0; k140 < this.listNode[d140].getChildNodeInfo().allChildNum; k140++) {
                if (this.listNode[d140 + 1 + k140] === undefined) {
                    return;
                }
                this.listNode[d140 + 1 + k140].setNodeIsShow(false);
                this.listNode[d140 + 1 + k140].setListItemHeight(LIST_ITEM_HEIGHT_NONE);
            }
            this.loadedListNodeFunction();
            this.notifyDataReload();
            return;
        }
        let g140 = new Array(this.listNode[d140].getChildNodeInfo().childNum);
        g140[0] = d140 + 1;
        let h140 = 1;
        while (h140 < this.listNode[d140].getChildNodeInfo().childNum) {
            g140[h140] = g140[h140 - 1] + this.listNode[g140[h140 - 1]].getChildNodeInfo().allChildNum + 1;
            h140++;
        }
        if (f140 === NodeStatus.EXPAND) {
            for (let i140 = 0; i140 < g140.length; i140++) {
                if (this.listNode[g140[i140]] === undefined) {
                    return;
                }
                this.listNode[g140[i140]].setNodeIsShow(true);
                this.listNode[g140[i140]].setListItemHeight(LIST_ITEM_HEIGHT);
                let j140 = this.listNode[g140[i140]].getNodeCurrentNodeId();
                if (this.expandAndCollapseInfo.get(j140) === NodeStatus.EXPAND) {
                    this.handleExpandAndCollapse(g140[i140], false);
                }
            }
        }
        g140 = null;
        if (c140) {
            this.loadedListNodeFunction();
            this.notifyDataReload();
        }
    }

    updateAllChildNum() {
        delayUpdateParentChildNum(true, 1, this.nodeIdNodeItemMap, this.updateNodeIdList);
    }

    resetData(a140) {
        a140.splice(0, a140.length);
        this.loadedNodeIdAndIndexMap.clear();
        this.loadedListNode.splice(0, this.loadedListNode.length);
        this.nodeIdAndNodeIndexMap.clear();
        this.nodeIdAndSubtitleMap.clear();
    }

    initHandler(s139, t139, u139) {
        let v139 = 0;
        let w139 = 0;
        this.resetData(s139);
        try {
            this.traverseSectionNodeDF((y139) => {
                if (y139.getCurrentNodeId() >= 0 && this.nodeIdNodeParamMap.has(y139.getCurrentNodeId())) {
                    let z139 = new NodeInfo(y139, this.nodeIdNodeParamMap.get(y139.getCurrentNodeId()));
                    z139.addImageCollapse(y139.getChildNodeInfo().isHasChildNode);
                    s139.push(z139);
                    this.nodeIdAndNodeIndexMap.set(z139.getNodeCurrentNodeId(), w139++);
                    v139 = this.nodeDFHandler(z139, v139);
                }
                return false;
            }, this._root, t139, u139);
        } catch (x139) {
            hilog.error(LOG_CODE, TAG, 'traverseSectionNodeDF function callbacks error.');
            this.resetData(s139);
        }
    }

    nodeDFHandler(q139, r139) {
        if (q139.getChildNodeInfo().isHasChildNode) {
            this.expandAndCollapseInfo.set(q139.getNodeCurrentNodeId(), NodeStatus.COLLAPSE);
        }
        if (q139.getNodeIsShow()) {
            this.loadedNodeIdAndIndexMap.set(q139.getNodeCurrentNodeId(), r139++);
            this.loadedListNode.push(q139);
        }
        if (q139.getIsFolder()) {
            if (q139.getNodeInfoData().secondaryTitle !== undefined) {
                this.nodeIdAndSubtitleMap.set(q139.getNodeCurrentNodeId(), q139.getNodeInfoData().secondaryTitle);
            } else {
                this.nodeIdAndSubtitleMap.set(q139.getNodeCurrentNodeId(), '');
            }
        }
        return r139;
    }

    delayInit() {
        let m139 = setTimeout(() => {
            let n139 = [];
            this.initHandler(n139, 0);
            this.listNode.splice(0, this.listNode.length);
            this.listNode.push(...n139);
            this.listNode.forEach((o139, p139) => {
                this.notifyDataDelete(p139);
                this.notifyDataAdd(p139);
            });
            clearTimeout(m139);
        }, DELAY_TIME);
    }

    initSection() {
        this.initHandler(this.listNode, 0, 1);
    }

    setClickIndex(l139) {
        this.thisIndex = l139;
    }

    getClickNodeId() {
        if (!this.checkIndex(this.thisIndex)) {
            return -1;
        }
        return this.listNode[this.thisIndex].getNodeCurrentNodeId();
    }

    expandAndCollapseNode(k139) {
        this.changeNodeStatus(k139);
        this.handleExpandAndCollapse(k139, true);
    }

    getIsTouchDown() {
        return this.isTouchDown;
    }

    getLastIndex() {
        return this.lastIndex;
    }

    findIndex(i139) {
        let j139 = -1;
        if (this.nodeIdAndNodeIndexMap.has(i139)) {
            j139 = this.nodeIdAndNodeIndexMap.get(i139);
        }
        return j139;
    }

    handleEventDrag(h139) {
        if (!this.checkIndex(h139)) {
            return;
        }
        this.setImageSource(h139, InteractionStatus.NORMAL);
        this.changeNodeColor(h139, this.listNode[h139].getNodeStatus().normal);
        this.handleFocusEffect(h139, false);
        this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.listNode[h139].getNodeCurrentNodeId()));
    }

    handleEvent(f139, g139) {
        if (this.isDrag) {
            return;
        }
        if (!this.checkIndex(g139)) {
            return;
        }
        if (f139 === Event.TOUCH_DOWN || f139 === Event.TOUCH_UP || f139 === Event.MOUSE_BUTTON_RIGHT) {
            if (g139 !== this.lastIndex) {
                this.clearLastIndexStatus();
            }
        }
        this.eventHandler(g139, f139);
    }

    eventHandler(b139, c139) {
        let d139 = this.loadedNodeIdAndIndexMap.get(this.listNode[b139].getNodeCurrentNodeId());
        switch (c139) {
            case Event.TOUCH_DOWN:
                this.isTouchDown = true;
                this.changeNodeColor(b139, this.listNode[b139].getNodeStatus().press);
                this.notifyDataChange(d139);
                break;
            case Event.TOUCH_UP: {
                this.touchUpHandler(b139, d139);
                break;
            }
            case Event.HOVER:
                if (this.getNodeColor(b139) !== this.listNode[b139].getNodeStatus().selected) {
                    this.changeNodeColor(b139, this.listNode[b139].getNodeStatus().hover);
                    this.notifyDataChange(d139);
                }
                break;
            case Event.HOVER_OVER:
                if (this.getNodeColor(b139) !== this.listNode[b139].getNodeStatus().selected) {
                    this.changeNodeColor(b139, this.listNode[b139].getNodeStatus().normal);
                    this.notifyDataChange(d139);
                }
                break;
            case Event.FOCUS:
                this.handleFocusEffect(b139, true);
                this.notifyDataChange(d139);
                break;
            case Event.BLUR:
                this.handleFocusEffect(b139, false);
                this.notifyDataChange(d139);
                break;
            case Event.MOUSE_BUTTON_RIGHT:
                this.lastIndex = b139;
                this.finishEditing();
                break;
            case Event.DRAG:
                this.isTouchDown = false;
                let e139 = this.listNode[b139];
                this.setImageSource(b139, InteractionStatus.SELECTED);
                this.lastIndex = b139;
                this.changeNodeColor(b139, e139.getNodeStatus().selected);
                this.notifyDataChange(d139);
                break;
            default:
                break;
        }
    }

    touchUpHandler(y138, z138) {
        if (this.isInnerDrag) {
            this.isInnerDrag = false;
        }
        this.isTouchDown = false;
        let a139 = this.listNode[y138];
        this.setImageSource(y138, InteractionStatus.SELECTED);
        a139.setFontColor(this.treeViewTheme.primaryTitleFontColor);
        this.lastIndex = y138;
        this.changeNodeColor(y138, a139.getNodeStatus().selected);
        this.notifyDataChange(z138);
    }

    notificationNodeInfo(p138, q138) {
        if (q138 === MenuOperation.MODIFY_NODE) {
            let w138 = this.listNode[this.modifyNodeIndex];
            let x138 = {
                currentNodeId: w138?.getNodeCurrentNodeId(),
                parentNodeId: w138?.getNodeParentNodeId(),
            };
            this.appEventBus.emit(TreeListenTypeV2.NODE_MODIFY, x138);
        } else if (q138 === MenuOperation.ADD_NODE) {
            let r138 = this.listNode[p138];
            if (r138 === undefined) {
                return;
            }
            let s138 = (r138.getNodeItem().imageNode !== undefined) ?
                r138.getNodeItem().imageNode?.source : undefined;
            let t138 = (r138.getNodeItem().imageNode !== undefined) ?
                r138.getNodeItem().imageNode?.selectedSource : undefined;
            let u138 = (r138.getNodeItem().imageNode !== undefined) ?
                r138.getNodeItem().imageNode?.editSource : undefined;
            let v138 = {
                currentNodeId: r138?.getNodeCurrentNodeId(),
                parentNodeId: r138?.getNodeParentNodeId(),
            };
            this.appEventBus.emit(TreeListenTypeV2.NODE_ADD, v138);
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

    setItemVisibilityOnEdit(j138, k138) {
        let l138 = -1;
        if (j138 === -1) {
            return;
        }
        if (k138 === MenuOperation.MODIFY_NODE) {
            for (let o138 = 0; o138 < this.listNode.length; o138++) {
                if (this.listNode[o138]?.getNodeCurrentNodeId() === j138) {
                    l138 = o138;
                    break;
                }
            }
            let n138 = this.listNode[l138];
            if (n138 === undefined) {
                return;
            }
            n138.setIsModify(true);
            if (n138.getNodeItem().mainTitleNode === null) {
                return;
            }
            this.currentOperation = MenuOperation.MODIFY_NODE;
            n138.setTitleAndInputTextStatus(true);
            this.setImageSource(l138, InteractionStatus.EDIT);
            this.setImageCollapseSource(l138, InteractionStatus.EDIT);
            this.modifyNodeIndex = l138;
            if (n138.getNodeItem().inputText) {
                if (n138.getNodeItem().imageCollapse !== null) {
                    n138.getNodeItem().inputText.rightMargin = {
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.ohos_id_text_paragraph_margin_xs'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__'
                    };
                } else {
                    n138.getNodeItem().inputText.rightMargin = {
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.ohos_id_elements_margin_horizontal_m'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__'
                    };
                }
            }
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(j138));
        }
        l138 = j138;
        if (k138 === MenuOperation.COMMIT_NODE) {
            let m138 = this.listNode[l138];
            if (m138 === undefined) {
                return;
            }
            m138.setTitleAndInputTextStatus(false);
            m138.setIsModify(false);
            this.setImageSource(l138, InteractionStatus.FINISH_EDIT);
            this.setImageCollapseSource(l138, InteractionStatus.FINISH_EDIT);
            this.notificationNodeInfo(this.modifyNodeIndex, this.currentOperation);
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(m138?.getNodeCurrentNodeId()));
        }
    }

    setPopUpInfo(d138, e138, f138, g138) {
        if (!this.checkIndex(g138)) {
            return;
        }
        let h138 = this.listNode[g138];
        if (h138 === undefined) {
            return;
        }
        h138.setPopUpIsShow(f138);
        let i138 = this.loadedNodeIdAndIndexMap.get(h138.getNodeCurrentNodeId());
        if (!f138) {
            this.notifyDataChange(i138);
            return;
        }
        if (d138 === PopUpType.HINTS) {
            if (h138.getNodeItem().mainTitleNode !== null) {
                h138.setPopUpText(h138.getNodeItem().mainTitleNode?.title);
            } else {
                h138.setPopUpText('');
                h138.setPopUpIsShow(false);
            }
            h138.setPopUpEnableArrow(false);
            h138.setPopUpColor({
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_background'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            h138.setPopUpTextColor(this.treeViewTheme.secondaryTitleFontColor);
        } else if (d138 === PopUpType.WARNINGS) {
            if (h138.getNodeItem().inputText !== null) {
                if (e138 === InputError.INVALID_ERROR) {
                    h138.setPopUpText('invalid error');
                } else if (e138 === InputError.LENGTH_ERROR) {
                    h138.setPopUpText('length error');
                }
                h138.setPopUpEnableArrow(true);
                h138.setPopUpColor({
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_help_tip_bg'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                });
                h138.setPopUpTextColor({
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_text_hint_contrary'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                });
            }
        }
        this.notifyDataChange(i138);
    }

    setShowPopUpTimeout(a138, b138) {
        if (!this.checkIndex(b138)) {
            return;
        }
        if (this.listNode[b138].getNodeItem().mainTitleNode !== null) {
            this.listNode[b138].getNodeItem().mainTitleNode.popUpTimeout = a138;
        }
        let c138 = this.loadedNodeIdAndIndexMap.get(this.listNode[b138].getNodeCurrentNodeId());
        this.notifyDataChange(c138);
    }

    setMainTitleNameOnEdit(y137, z137) {
        this.modifyNodeIndex = y137;
        if (this.listNode[y137].getNodeItem().mainTitleNode !== null) {
            this.listNode[y137].getNodeItem().mainTitleNode.title = z137;
        }
    }

    totalCount() {
        return this.loadedNodeIdAndIndexMap.size;
    }

    getData(x137) {
        if (x137 < 0 || x137 >= this.loadedListNode.length) {
            return undefined;
        }
        return this.loadedListNode[x137];
    }

    addData(v137, w137) {
        if (!this.checkIndex(v137)) {
            return;
        }
        this.listNode.splice(v137, 0, w137);
        this.nodeIdAndNodeIndexMap.set(w137.getNodeCurrentNodeId(), v137);
        this.loadedListNodeFunction();
        this.notifyDataAdd(v137);
    }

    pushData(u137) {
        this.listNode.push(u137);
        this.nodeIdAndNodeIndexMap.set(u137.getNodeCurrentNodeId(), this.listNode.length);
        this.loadedListNodeFunction();
        this.notifyDataAdd(this.listNode.length - 1);
    }

    setIsInnerDrag(t137) {
        this.isInnerDrag = t137;
    }

    getIsInnerDrag() {
        return this.isInnerDrag;
    }

    setIsDrag(s137) {
        this.isDrag = s137;
    }

    getIsDrag() {
        return this.isDrag;
    }

    setCurrentNodeInfo(r137) {
        if (r137 === undefined) {
            return;
        }
        this.currentNodeInfo = r137;
    }

    getCurrentNodeInfo() {
        return this.currentNodeInfo;
    }

    setDraggingParentNodeId(q137) {
        if (q137 === undefined) {
            return;
        }
        this.draggingParentNodeId = q137;
    }

    getDraggingParentNodeId() {
        return this.draggingParentNodeId;
    }

    getDraggingCurrentNodeId() {
        return this.draggingCurrentNodeId;
    }

    setDraggingCurrentNodeId(p137) {
        if (p137 === undefined) {
            return;
        }
        this.draggingCurrentNodeId = p137;
    }

    setListItemOpacity(o137) {
        this.listItemOpacity = o137;
    }

    getListItemOpacity(n137) {
        return n137.getNodeCurrentNodeId() === this.getDraggingCurrentNodeId() ? this.listItemOpacity : 1;
    }

    getDragPopupPara() {
        return this.DRAG_POPUP;
    }

    setLastPassIndex(m137) {
        this.lastPassIndex = m137;
    }

    getLastPassIndex() {
        return this.lastPassIndex;
    }

    getIsParentOfInsertNode(i137) {
        if (this.currentNodeInfo === null || i137 === undefined) {
            return false;
        }
        let j137 = this.currentNodeInfo.getNodeInfoNode();
        let k137 = j137.currentNodeId;
        let l137 = this.nodeIdNodeItemMap.get(i137)?.parentNodeId;
        while (l137 !== undefined && l137 !== -1) {
            if (k137 === l137) {
                return true;
            } else {
                l137 = this.nodeIdNodeItemMap.get(l137)?.parentNodeId;
            }
        }
        return false;
    }

    setPassIndex(h137) {
        this.thisPassIndex = h137;
    }

    getPassIndex() {
        return this.thisPassIndex;
    }

    clearTimeOutAboutDelayHighLightAndExpand(d137) {
        if (this.lastPassId !== this.INITIAL_INVALID_VALUE && this.loadedNodeIdAndIndexMap.has(this.lastPassId)) {
            let f137 = this.loadedNodeIdAndIndexMap.get(this.lastPassId);
            this.listNode.forEach((g137) => {
                if (g137.getNodeCurrentNodeId() === this.lastPassId) {
                    g137.setCanShowFlagLine(false);
                    return;
                }
            });
            this.notifyDataChange(f137);
        }
        if ((this.lastTimeoutHighLightId !== this.INITIAL_INVALID_VALUE &&
            this.clearTimeoutHighLightId !== this.lastTimeoutHighLightId)) {
            clearTimeout(this.lastTimeoutHighLightId);
            if (this.lastDelayHighLightIndex !== this.INITIAL_INVALID_VALUE) {
                this.clearHighLight(this.lastDelayHighLightIndex);
                let e137 = this.loadedNodeIdAndIndexMap
                    .get(this.listNode[this.lastDelayHighLightIndex].getNodeCurrentNodeId());
                this.notifyDataChange(e137);
            }
            this.clearTimeoutHighLightId = this.lastTimeoutHighLightId;
        }
        this.lastTimeoutHighLightId = this.timeoutHighLightId;
        this.lastDelayHighLightIndex = d137;
        if ((this.lastTimeoutExpandId !== this.INITIAL_INVALID_VALUE &&
            this.clearTimeoutExpandId !== this.lastTimeoutExpandId)) {
            clearTimeout(this.lastTimeoutExpandId);
            this.clearTimeoutExpandId = this.lastTimeoutExpandId;
        }
        this.lastTimeoutExpandId = this.timeoutExpandId;
        this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE;
    }

    clearHighLight(c137) {
        if (!this.checkIndex(c137)) {
            return;
        }
        this.changeNodeColor(c137, this.listNode[c137].getNodeStatus().normal);
        this.changeNodeHighLightColor(c137, false);
        this.setImageSource(c137, InteractionStatus.FINISH_DRAG_INSERT);
        this.setImageCollapseSource(c137, InteractionStatus.FINISH_DRAG_INSERT);
        this.listNode[c137].setIsHighLight(false);
    }

    changeNodeHighLightColor(a137, b137) {
        if (this.listNode[a137].getNodeItem().mainTitleNode && this.listNode[a137].getIsShowTitle()) {
            this.listNode[a137].getNodeItem().mainTitleNode?.setMainTitleHighLight(b137);
        }
    }

    getAccessibleTitle(s136) {
        let t136 = [];
        while (s136 !== -1) {
            if (s136 === undefined) {
                return '';
            }
            let u136 = this.findParentNodeId(s136);
            let v136 = this.nodeIdNodeItemMap.get(u136);
            if (v136 === undefined || u136 === undefined) {
                return '';
            }
            let w136 = this.getNodeInfoByNodeItem(v136).getNodeInfoData()?.primaryTitle === undefined
                ? '' : this.getNodeInfoByNodeItem(v136).getNodeInfoData().primaryTitle;
            let x136 = this.getNodeInfoByNodeItem(v136).getNodeInfoData()?.secondaryTitle === undefined
                ? '' : this.getNodeInfoByNodeItem(v136).getNodeInfoData().secondaryTitle;
            let y136 = this.getAccessibleTitleText(w136);
            let z136 = this.getAccessibleTitleText(x136);
            t136.unshift(`${y136}, ${z136}`);
            s136 = v136.currentNodeId;
        }
        return t136.join(',');
    }

    getPlaceAccessibleTitle(y135) {
        if (y135 === undefined) {
            return '';
        }
        let z135 = this.findParentNodeId(y135);
        if (z135 === -1) {
            let m136 = [];
            let n136 = this.nodeIdNodeItemMap.get(y135);
            if (n136 === undefined || z135 === undefined) {
                return '';
            }
            let o136 = this.getNodeInfoByNodeItem(n136).getNodeInfoData()?.primaryTitle === undefined
                ? '' : this.getNodeInfoByNodeItem(n136).getNodeInfoData().primaryTitle;
            let p136 = this.getNodeInfoByNodeItem(n136).getNodeInfoData()?.secondaryTitle === undefined
                ? '' : this.getNodeInfoByNodeItem(n136).getNodeInfoData().secondaryTitle;
            let q136 = this.getAccessibleTitleText(o136);
            let r136 = this.getAccessibleTitleText(p136);
            m136.unshift(`${q136}, ${r136}`);
            return m136.join(',');
        } else {
            let a136 = [];
            let b136 = this.nodeIdNodeItemMap.get(y135);
            if (b136 === undefined || z135 === undefined) {
                return '';
            }
            let c136 = this.getNodeInfoByNodeItem(b136).getNodeInfoData()?.primaryTitle === undefined
                ? '' : this.getNodeInfoByNodeItem(b136).getNodeInfoData().primaryTitle;
            let d136 = this.getNodeInfoByNodeItem(b136).getNodeInfoData()?.secondaryTitle === undefined
                ? '' : this.getNodeInfoByNodeItem(b136).getNodeInfoData().secondaryTitle;
            let e136 = this.getAccessibleTitleText(c136);
            let f136 = this.getAccessibleTitleText(d136);
            a136.unshift(`${e136}, ${f136}`);
            while (y135 !== -1) {
                if (y135 === undefined) {
                    return '';
                }
                let g136 = this.findParentNodeId(y135);
                let h136 = this.nodeIdNodeItemMap.get(g136);
                if (h136 === undefined || g136 === undefined) {
                    return '';
                }
                let i136 = this.getNodeInfoByNodeItem(h136).getNodeInfoData()?.primaryTitle === undefined
                    ? '' : this.getNodeInfoByNodeItem(h136).getNodeInfoData().primaryTitle;
                let j136 = this.getNodeInfoByNodeItem(h136).getNodeInfoData()?.secondaryTitle === undefined
                    ? '' : this.getNodeInfoByNodeItem(h136).getNodeInfoData().secondaryTitle;
                let k136 = this.getAccessibleTitleText(i136);
                let l136 = this.getAccessibleTitleText(j136);
                a136.unshift(`${k136}, ${l136}`);
                y135 = h136.currentNodeId;
            }
            return a136.join(',');
        }
    }

    getDraggingAccessible(p135, q135, r135) {
        this.getAccessibleTitle(r135);
        if (q135 === undefined || r135 === undefined) {
            return;
        }
        let s135 = this.findParentNodeId(r135);
        let t135 = p135.indexOf(r135) + 2;
        let u135 = this.getClickNodeChildrenInfo(s135);
        let v135 = u135.map(x135 => x135.itemId);
        let w135 = v135.indexOf(r135) + 2;
        if (s135 === -1 && this.getExpandAndCollapseInfo(q135) === NodeStatus.COLLAPSE ||
            s135 === -1 && this.getExpandAndCollapseInfo(q135) === undefined) {
            this.sendAccessibility(this.getStringByName('treeview_accessibility_move_node_parent', t135));
        } else if (this.getExpandAndCollapseInfo(q135) === NodeStatus.EXPAND) {
            this.sendAccessibility(this.getStringByName('treeview_accessibility_move_node_child',
                this.getAccessibleTitle(r135), 1));
        } else if (s135 !== -1) {
            this.sendAccessibility(this.getStringByName('treeview_accessibility_move_node_child',
                this.getAccessibleTitle(r135), w135));
        }
    }

    getStringByName(m135, ...n135) {
        if (m135) {
            try {
                return getContext()?.resourceManager.getStringByNameSync(m135, ...n135);
            } catch (o135) {
                console.error(`Ace SegmentButton getAccessibilityDescription, error: ${o135.toString()}`);
            }
        }
        return '';
    }

    sendAccessibility(k135) {
        let l135 = ({
            type: 'announceForAccessibility',
            bundleName: getContext()?.abilityInfo?.bundleName,
            triggerAction: 'common',
            textAnnouncedForAccessibility: k135
        });
        accessibility.sendAccessibilityEvent(l135);
    }

    getAccessibleTitleText(f135) {
        let g135 = '';
        try {
            if (typeof f135 === 'string') {
                g135 = f135;
            } else {
                g135 = getContext()?.resourceManager?.getStringSync(f135?.id);
            }
        } catch (h135) {
            let i135 = h135.code;
            let j135 = h135.message;
            hilog.error(0x3900, 'Ace', `treeView getAccessibleTitleText error, code: ${i135}, message: ${j135}`);
        }
        return g135;
    }

    setVisibility(r134, s134, t134, u134) {
        let v134 = (this.thisPassIndex !== s134 || this.flag !== r134) ? true : false;
        this.thisPassIndex = s134;
        if ((v134 || t134) && this.isInnerDrag) {
            this.flag = r134;
            let w134 = this.getData(s134)?.getNodeCurrentNodeId();
            let x134 = this.getData(s134)?.getNodeLevel();
            if (w134 !== undefined) {
                x134 = (this.expandAndCollapseInfo.get(w134) === NodeStatus.EXPAND &&
                    this.flag === Flag.DOWN_FLAG) ? (x134 ? x134 + 1 : undefined) : x134;
                if (this.lastPassId !== this.INITIAL_INVALID_VALUE &&
                    this.loadedNodeIdAndIndexMap.has(this.lastPassId)) {
                    let d135 = this.loadedNodeIdAndIndexMap.get(this.lastPassId);
                    this.listNode.forEach((e135) => {
                        if (e135.getNodeCurrentNodeId() === this.lastPassId) {
                            e135.setCanShowFlagLine(false);
                        }
                    });
                    this.notifyDataChange(d135);
                }
                let y134 = this.getData(s134 - 1)?.getNodeCurrentNodeId();
                let z134 = this.getData(s134 + 2)?.getNodeCurrentNodeId();
                let a135 = this.getData(s134 + 1)?.getNodeCurrentNodeId();
                let b135 = this.nodeIdNodeItemMap.get(a135);
                if (this.flag === Flag.DOWN_FLAG && s134 < this.totalCount() - 1) {
                    this.getData(s134)?.setCanShowFlagLine(false);
                    this.getData(s134 + 1)?.setCanShowFlagLine(true);
                    this.getData(s134)?.setCanShowBottomFlagLine(false);
                    this.getData(s134 + 1)?.setFlagLineLeftMargin(x134);
                    this.notifyDataChange(s134);
                    this.notifyDataChange(s134 + 1);
                    this.lastPassId = this.getData(s134 + 1)?.getNodeCurrentNodeId();
                    let c135 = this.nodeIdNodeItemMap.get(a135);
                    if (!c135?.childNodeInfo.isHasChildNode) {
                        this.getDraggingAccessible(u134, a135, a135);
                    } else {
                        this.getDraggingAccessible(u134, a135, z134);
                    }
                } else if (this.flag === Flag.UP_FLAG && s134 < this.totalCount() - 1) {
                    this.getData(s134)?.setCanShowFlagLine(true);
                    this.getData(s134 + 1)?.setCanShowFlagLine(false);
                    this.getData(s134)?.setCanShowBottomFlagLine(false);
                    this.getData(s134)?.setFlagLineLeftMargin(x134);
                    this.notifyDataChange(s134);
                    this.notifyDataChange(s134 + 1);
                    this.lastPassId = this.getData(s134)?.getNodeCurrentNodeId();
                    if (b135?.childNodeInfo.isHasChildNode && b135?.parentNodeId !== -1) {
                        this.getDraggingAccessible(u134, a135, a135);
                    } else if (b135?.childNodeInfo.isHasChildNode && b135?.parentNodeId === -1) {
                        this.getDraggingAccessible(u134, y134, a135);
                    }
                } else if (s134 >= this.totalCount() - 1) {
                    if (this.flag === Flag.DOWN_FLAG) {
                        this.getData(s134)?.setCanShowFlagLine(false);
                        this.getData(s134)?.setCanShowBottomFlagLine(true);
                    } else {
                        this.getData(s134)?.setCanShowFlagLine(true);
                        this.getData(s134)?.setCanShowBottomFlagLine(false);
                    }
                    this.getData(s134)?.setFlagLineLeftMargin(x134);
                    this.notifyDataChange(s134);
                    this.lastPassId = this.getData(s134)?.getNodeCurrentNodeId();
                }
            }
        }
    }

    delayHighLightAndExpandNode(g134, h134, i134) {
        let j134 = g134 !== this.lastDelayExpandIndex ? true : false;
        let k134 = this.getData(i134)?.getIsOverBorder();
        let l134 = this.listNode[g134 + 1]?.getNodeCurrentNodeId();
        let m134 = this.findParentNodeId(h134);
        if (k134) {
            this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE;
        } else {
            this.lastDelayExpandIndex = g134;
        }
        if (k134 || j134) {
            let n134 = !k134 && (!this.isInnerDrag ||
                (this.expandAndCollapseInfo.get(h134) === NodeStatus.COLLAPSE && this.isInnerDrag) ||
                (!this.expandAndCollapseInfo.has(h134) && this.listNode[g134].getIsFolder()));
            if (n134) {
                this.changeNodeColor(g134, this.listNode[g134].getNodeStatus().hover);
                this.notifyDataChange(i134);
                let q134 = this.isInnerDrag ? 1000 : 0;
                this.timeoutHighLightId = setTimeout(() => {
                    this.delayHighLight(g134);
                    this.sendAccessibility(this.getStringByName('treeview_accessibility_move_node_child',
                        this.getPlaceAccessibleTitle(h134), 1));
                }, q134);
            }
            if (k134 || (this.lastTimeoutHighLightId !== this.INITIAL_INVALID_VALUE &&
                this.clearTimeoutHighLightId !== this.lastTimeoutHighLightId)) {
                clearTimeout(this.lastTimeoutHighLightId);
                if (this.lastDelayHighLightIndex !== this.INITIAL_INVALID_VALUE) {
                    this.clearHighLight(this.lastDelayHighLightIndex);
                    this.notifyDataReload();
                }
                this.clearTimeoutHighLightId = this.lastTimeoutHighLightId;
            }
            this.lastTimeoutHighLightId = this.timeoutHighLightId;
            this.lastDelayHighLightIndex = g134;
            if (!k134 && this.expandAndCollapseInfo.get(h134) === NodeStatus.COLLAPSE) {
                let o134 = this.getData(i134)?.getNodeInfoNode().children[0]?.currentNodeId;
                let p134 = 2000;
                this.timeoutExpandId = setTimeout(() => {
                    this.clearHighLight(this.lastDelayHighLightIndex);
                    if (o134 !== undefined) {
                        this.alterFlagLineAndExpandNode(g134, o134);
                    }
                }, p134);
            }
            if (k134 || (this.lastTimeoutExpandId !== this.INITIAL_INVALID_VALUE &&
                this.clearTimeoutExpandId !== this.lastTimeoutExpandId)) {
                clearTimeout(this.lastTimeoutExpandId);
                this.clearTimeoutExpandId = this.lastTimeoutExpandId;
            }
            this.lastTimeoutExpandId = this.timeoutExpandId;
        }
    }

    delayHighLight(e134) {
        this.listNode.forEach((f134) => {
            if (f134.getNodeCurrentNodeId() === this.lastPassId) {
                f134.setCanShowFlagLine(false);
                f134.setCanShowBottomFlagLine(false);
                return;
            }
        });
        this.changeNodeColor(e134, this.listNode[e134].getNodeStatus().highLight);
        this.listNode[e134].setIsHighLight(true);
        this.changeNodeHighLightColor(e134, true);
        this.setImageSource(e134, InteractionStatus.DRAG_INSERT);
        this.setImageCollapseSource(e134, InteractionStatus.DRAG_INSERT);
        this.notifyDataReload();
    }

    alterFlagLineAndExpandNode(a134, b134) {
        this.listNode.forEach((d134) => {
            if (d134.getNodeCurrentNodeId() === this.lastPassId) {
                d134.setCanShowFlagLine(false);
                d134.setCanShowBottomFlagLine(false);
            }
        });
        this.listNode.forEach((c134) => {
            if (this.isInnerDrag && c134.getNodeCurrentNodeId() === b134) {
                c134.setCanShowFlagLine(true);
            }
        });
        this.changeNodeStatus(a134);
        this.handleExpandAndCollapse(a134, true);
        this.lastPassId = b134;
    }

    hideLastLine() {
        if (this.lastPassId !== this.INITIAL_INVALID_VALUE && this.loadedNodeIdAndIndexMap.has(this.lastPassId)) {
            this.listNode.forEach((z133) => {
                if (z133.getNodeCurrentNodeId() === this.lastPassId) {
                    z133.setCanShowFlagLine(false);
                    z133.setCanShowBottomFlagLine(false);
                    return;
                }
            });
            let y133 = this.loadedNodeIdAndIndexMap.get(this.lastPassId);
            this.notifyDataChange(y133);
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

    getSubtitle(x133) {
        if (this.nodeIdAndSubtitleMap.has(x133)) {
            if (typeof this.nodeIdAndSubtitleMap.get(x133) === 'number') {
                return this.nodeIdAndSubtitleMap.get(x133)?.toString();
            } else {
                return this.nodeIdAndSubtitleMap.get(x133);
            }
        } else {
            return '';
        }
    }

    hasSubtitle(w133) {
        return this.nodeIdAndSubtitleMap.has(w133);
    }

    initialParameterAboutDelayHighLightAndExpandIndex() {
        this.lastDelayHighLightIndex = this.INITIAL_INVALID_VALUE;
        this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE;
        this.lastPassIndex = this.INITIAL_INVALID_VALUE;
        this.draggingCurrentNodeId = this.INITIAL_INVALID_VALUE;
        this.flag = Flag.NONE;
    }

    refreshSubtitle(v133) {
        this.nodeIdAndSubtitleMap.set(this.selectedParentNodeId, this.selectedParentNodeSubtitle);
        this.nodeIdAndSubtitleMap.set(v133, this.insertNodeSubtitle);
        this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.selectedParentNodeId));
        this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(v133));
    }

    setNodeSubtitlePara(s133, t133, u133) {
        this.selectedParentNodeId = s133;
        this.selectedParentNodeSubtitle = t133;
        this.insertNodeSubtitle = u133;
    }

    getInsertNodeSubtitle() {
        return this.insertNodeSubtitle;
    }

    getExpandAndCollapseInfo(r133) {
        return this.expandAndCollapseInfo.get(r133);
    }

    getLastDelayHighLightId() {
        return this.lastDelayHighLightId;
    }

    setLastDelayHighLightId() {
        this.listNode.forEach((p133, q133) => {
            if (q133 === this.lastDelayHighLightIndex) {
                this.lastDelayHighLightId = p133.getNodeCurrentNodeId();
            }
        });
    }

    setLastPassId(o133) {
        this.lastPassId = o133;
    }

    setLastDelayHighLightIndex(n133) {
        this.lastDelayHighLightIndex = n133;
    }

    alterDragNode(i132, j132, k132, l132, m132) {
        let n132 = [];
        let o132 = i132;
        let p132 = l132;
        let q132 = m132.getNodeInfoData();
        let r132 = null;
        let s132 = m132.getNodeInfoNode();
        let t132 = false;
        let u132 = this.INITIAL_INVALID_VALUE;
        let v132 = this.INITIAL_INVALID_VALUE;
        let w132 = this.flag === Flag.DOWN_FLAG ? true : false;
        v132 = this.getChildIndex(k132, l132);
        u132 = this.getChildIndex(i132, j132) + 1;
        if (i132 !== k132) {
            u132 = w132 ? u132 + 1 : u132;
        } else {
            if (u132 > v132) {
                u132 = w132 ? u132 : u132 - 1;
            } else {
                u132 = w132 ? u132 + 1 : u132;
            }
        }
        for (let m133 = 0; m133 < this.listNode.length; m133++) {
            if (this.listNode[m133].getNodeCurrentNodeId() === j132) {
                t132 = this.listNode[m133].getIsHighLight();
                if (this.flag === Flag.DOWN_FLAG && this.expandAndCollapseInfo.get(j132) === NodeStatus.EXPAND) {
                    o132 = j132;
                    u132 = 0;
                } else if (this.flag === Flag.UP_FLAG && this.expandAndCollapseInfo.get(j132) ===
                    NodeStatus.EXPAND &&
                    this.listNode[m133].getCanShowFlagLine() === false) {
                    o132 = j132;
                    u132 = 0;
                } else if (t132) {
                    o132 = j132;
                    u132 = 0;
                }
                break;
            }
        }
        let x132 = {
            currentNodeId: p132,
            parentNodeId: o132,
            childIndex: u132,
        };
        this.appEventBus.emit(TreeListenTypeV2.NODE_MOVE, x132);
        n132.push({ parentId: o132, currentId: p132, data: q132 });
        let y132 = (i133, j133) => {
            if (i133) {
                o132 = i133.parentNodeId;
                p132 = i133.currentNodeId;
                for (let l133 = 0; l133 < j133.length; l133++) {
                    if (j133[l133].getNodeCurrentNodeId() === p132) {
                        r132 = j133[l133];
                        break;
                    }
                }
                if (r132 === null) {
                    return false;
                }
                let k133 = r132.getNodeInfoData();
                if (o132 !== k132) {
                    n132.push({ parentId: o132, currentId: p132, data: k133 });
                }
                return false;
            }
            return false;
        };
        this.dragTraverseNodeDF(y132, s132, this.listNode);
        let z132 = this.removeNode(l132, k132);
        if (z132.length === 0) {
            return;
        }
        let a133 = j132;
        let b133 = w132;
        if (this.expandAndCollapseInfo.get(j132) === NodeStatus.EXPAND) {
            b133 = false;
            this.listNode.forEach((h133) => {
                if (h133.getNodeCurrentNodeId() === j132 && h133.getCanShowFlagLine() === false) {
                    if (h133.getNodeInfoNode().children.length) {
                        a133 = h133.getNodeInfoNode().children[0].currentNodeId;
                    } else {
                        a133 = this.INITIAL_INVALID_VALUE;
                    }
                }
            });
        } else if (!this.expandAndCollapseInfo.get(j132) && t132) {
            this.expandAndCollapseInfo.set(j132, NodeStatus.EXPAND);
        }
        let c133 = this.addDragNode(n132[0].parentId, n132[0].currentId, a133, b133, n132[0].data);
        if (!c133) {
            return;
        }
        for (let f133 = 1; f133 < n132.length; f133++) {
            let g133 = this.addNode(n132[f133].parentId, n132[f133].currentId, n132[f133].data, false);
            if (!g133) {
                return;
            }
        }
        for (let e133 = 0; e133 < this.listNode.length; e133++) {
            if (this.listNode[e133].getNodeCurrentNodeId() === k132) {
                if (this.listNode[e133].getNodeItem().imageCollapse === null) {
                    this.listNode[e133].handleImageCollapseAfterAddNode(false);
                    this.expandAndCollapseInfo.delete(k132);
                    break;
                }
            }
        }
        let d133 = [...this.listNode];
        this.reloadListNode(d133);
    }

    reloadListNode(b132) {
        let c132 = 0;
        let d132 = 0;
        this.listNode.splice(0, this.listNode.length);
        this.loadedNodeIdAndIndexMap.clear();
        this.loadedListNode.splice(0, this.loadedListNode.length);
        this.traverseNodeDF((e132) => {
            let f132 = e132.currentNodeId;
            if (f132 >= 0) {
                if (this.nodeIdNodeParamMap.has(f132)) {
                    let g132 = new NodeInfo(e132, this.nodeIdNodeParamMap.get(f132));
                    g132.addImageCollapse(e132.getChildNodeInfo().isHasChildNode);
                    this.listNode.push(g132);
                    this.nodeIdAndNodeIndexMap.set(g132.getNodeCurrentNodeId(), d132++);
                    if (this.expandAndCollapseInfo.get(f132) === NodeStatus.EXPAND) {
                        g132.getNodeItem()
                            .imageCollapse =
                            CollapseImageNodeFlyweightFactory.changeImageCollapseSource(NodeStatus.EXPAND,
                                g132.getNodeItem().imageCollapse?.isCollapse);
                    } else if (this.expandAndCollapseInfo.get(f132) === NodeStatus.COLLAPSE) {
                        g132.getNodeItem()
                            .imageCollapse =
                            CollapseImageNodeFlyweightFactory.changeImageCollapseSource(NodeStatus.COLLAPSE,
                                g132.getNodeItem().imageCollapse?.isCollapse);
                    }
                    for (let h132 = 0; h132 < b132.length; h132++) {
                        if (b132[h132].getNodeCurrentNodeId() === g132.getNodeCurrentNodeId()) {
                            g132.setNodeIsShow(b132[h132].getNodeIsShow());
                            g132.setListItemHeight(b132[h132].getListItemHeight());
                            if (g132.getNodeItem().mainTitleNode && g132.getIsShowTitle()) {
                                g132.getNodeItem().mainTitleNode.title = b132[h132].getNodeItem().mainTitleNode?.title;
                            }
                            break;
                        }
                    }
                    if (g132.getNodeIsShow()) {
                        this.loadedNodeIdAndIndexMap.set(g132.getNodeCurrentNodeId(), c132++);
                        this.loadedListNode.push(g132);
                    }
                }
            }
            return false;
        });
    }

    getFlagLine() {
        return this.FLAG_LINE;
    }

    getVisibility(y131) {
        let z131 = this.loadedNodeIdAndIndexMap.get(y131.getNodeCurrentNodeId()) - 1;
        if (z131 > this.INITIAL_INVALID_VALUE) {
            let a132 = this.getData(z131);
            return (y131.getCanShowFlagLine() === true && !y131.getIsHighLight() && !a132?.getIsHighLight()) ?
                Visibility.Visible : Visibility.Hidden;
        } else {
            return (y131.getCanShowFlagLine() === true && !y131.getIsHighLight()) ?
                Visibility.Visible : Visibility.Hidden;
        }
    }

    getSubTitlePara() {
        return this.subTitle;
    }

    getIsFolder(x131) {
        if (this.loadedNodeIdAndIndexMap.has(x131)) {
            return this.getData(this.loadedNodeIdAndIndexMap.get(x131))?.getIsFolder();
        }
        return false;
    }

    getSubTitleFontColor(w131) {
        return w131 ? this.subTitle.highLightFontColor : this.treeViewTheme.secondaryTitleFontColor;
    }

    getChildIndex(q131, r131) {
        let s131 = this.INITIAL_INVALID_VALUE;
        if (this.nodeIdNodeItemMap.has(q131)) {
            let t131 = this.nodeIdNodeItemMap.get(q131);
            if (t131.getCurrentNodeId() === q131) {
                t131.children.forEach((u131, v131) => {
                    if (u131.getCurrentNodeId() === r131) {
                        s131 = v131;
                        return;
                    }
                });
            }
        }
        return s131;
    }

    setCurrentFocusNodeId(p131) {
        this.currentFocusNodeId = p131;
    }

    getCurrentFocusNodeId() {
        return this.currentFocusNodeId;
    }

    setLastFocusNodeId(o131) {
        this.lastFocusNodeId = o131;
    }

    getLastFocusNodeId() {
        return this.lastFocusNodeId;
    }

    getAddFocusNodeId() {
        return this.addFocusNodeId;
    }

    setFlag(n131) {
        this.flag = n131;
    }

    traverseNodeDF(i131, j131 = this._root) {
        let k131 = [];
        let l131 = false;
        k131.unshift(j131);
        let m131 = k131.shift();
        while (!l131 && m131) {
            l131 = i131(m131) === true;
            if (!l131) {
                k131.unshift(...m131.children);
                m131 = k131.shift();
            }
        }
    }

    traverseSectionNodeDF(z130, a131 = this._root, b131, c131) {
        let d131 = [];
        let e131 = false;
        let f131 = false;
        d131.unshift(a131);
        let g131 = d131.shift();
        while (!e131 && g131) {
            try {
                if (b131 !== undefined && g131.nodeLevel < b131) {
                    f131 = true;
                }
                if (c131 !== undefined && g131.nodeLevel > c131) {
                    f131 = true;
                }
                if (!f131) {
                    e131 = z130(g131);
                }
            } catch (h131) {
                throw new Error('traverseSectionNodeDF function callbacks error');
            }
            if (!e131) {
                d131.unshift(...g131.children);
                g131 = d131.shift();
                f131 = false;
            }
        }
    }

    updateParentChildNum(u130, v130, w130) {
        let x130 = u130.parentNodeId;
        while (x130 >= 0) {
            if (this.nodeIdNodeItemMap.has(x130)) {
                let y130 = this.nodeIdNodeItemMap.get(x130);
                y130.getChildNodeInfo().allChildNum =
                    v130 ? y130.getChildNodeInfo().allChildNum + w130 : y130.getChildNodeInfo().allChildNum - w130;
                x130 = y130.parentNodeId;
            } else {
                hilog.error(LOG_CODE, TAG, 'updateParentChildNum: parent node not found.');
                break;
            }
        }
    }

    findParentNodeId(s130) {
        let t130 = new NodeItem(emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(s130)) {
            t130 = this.nodeIdNodeItemMap.get(s130);
        }
        return t130.parentNodeId;
    }

    refreshRemoveNodeData(i130, j130) {
        let k130 = [];
        if (i130.length === 0) {
            return;
        }
        let l130 = undefined;
        for (let p130 = 0; p130 < i130.length; p130++) {
            if (this.loadedNodeIdAndIndexMap.has(i130[p130])) {
                let r130 = this.loadedNodeIdAndIndexMap.get(i130[p130]);
                k130.push(r130);
            }
            if (l130 === undefined && this.nodeIdAndNodeIndexMap.has(i130[p130])) {
                l130 = this.nodeIdAndNodeIndexMap.get(i130[p130]);
            }
            if (l130 !== undefined) {
                let q130 = this.listNode.splice(l130, 1);
                q130 = null;
            }
            if (this.expandAndCollapseInfo.has(i130[p130])) {
                this.expandAndCollapseInfo.delete(i130[p130]);
            }
        }
        k130.forEach((o130) => {
            this.notifyDataDelete(o130);
            this.notifyDataChange(o130);
        });
        if (j130.getNodeItem().imageCollapse === null) {
            if (this.nodeIdAndNodeIndexMap.has(j130.getNodeCurrentNodeId())) {
                let n130 = this.nodeIdAndNodeIndexMap.get(j130.getNodeCurrentNodeId());
                this.listNode[n130]?.handleImageCollapseAfterAddNode(false);
            }
            this.expandAndCollapseInfo.delete(j130.getNodeCurrentNodeId());
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(j130.getNodeCurrentNodeId()));
        }
        let m130 = {
            currentNodeId: j130.getNodeCurrentNodeId(),
            parentNodeId: j130.getNodeParentNodeId(),
        };
        this.loadedListNodeFunction();
        this.appEventBus.emit(TreeListenTypeV2.NODE_DELETE, m130);
    }

    refreshAddNodeData(d130) {
        let e130 = new NodeInfo(new NodeItem(emptyNodeInfo), emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(d130[0])) {
            let h130 = this.nodeIdNodeItemMap.get(d130[0]);
            e130 = new NodeInfo(h130, this.nodeIdNodeParamMap.get(d130[0]));
            e130.addImageCollapse(h130.getChildNodeInfo().isHasChildNode);
        }
        e130.setIsModify(true);
        let f130 = 0;
        for (let g130 = 0; g130 < this.listNode.length; g130++) {
            if (this.listNode[g130].getNodeCurrentNodeId() === e130.getNodeParentNodeId()) {
                f130 = g130;
                if (this.listNode[g130].getNodeItem().imageCollapse === null) {
                    this.listNode[g130].handleImageCollapseAfterAddNode(true);
                    this.notifyDataChange(f130);
                } else if (this.expandAndCollapseInfo.get(this.listNode[g130].getNodeCurrentNodeId()) ===
                    NodeStatus.COLLAPSE) {
                    this.changeNodeStatus(f130);
                }
                this.listNode.splice(g130 + 1, 0, e130);
                this.listNode[g130 + 1].setTitleAndInputTextStatus(true);
                this.listNode[g130 + 1].setNodeIsShow(true);
                this.listNode[g130 + 1].setListItemHeight(LIST_ITEM_HEIGHT);
                this.nodeIdAndNodeIndexMap.set(d130[0], g130 + 1);
                this.setImageSource(g130 + 1, InteractionStatus.EDIT);
                this.currentOperation = MenuOperation.ADD_NODE;
                this.notifyDataAdd(g130 + 1);
                this.notificationNodeInfo(g130 + 1, this.currentOperation);
                break;
            }
        }
        this.modifyNodeIndex = f130 + 1;
        this.setClickIndex(f130);
        this.lastIndex = f130;
        this.expandAndCollapseInfo.set(e130.getNodeParentNodeId(), NodeStatus.EXPAND);
        this.handleExpandAndCollapse(f130, true);
    }

    refreshData(y129, z129, a130) {
        let b130 = new NodeInfo(new NodeItem(emptyNodeInfo), emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(z129)) {
            let c130 = this.nodeIdNodeItemMap.get(z129);
            b130 = new NodeInfo(c130, this.nodeIdNodeParamMap.get(z129));
            b130.addImageCollapse(c130.getChildNodeInfo().isHasChildNode);
        }
        if (y129 === MenuOperation.REMOVE_NODE) {
            this.nodeIdAndSubtitleMap.set(z129, this.selectedParentNodeSubtitle);
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(z129));
            this.refreshRemoveNodeData(a130, b130);
        }
        if (y129 === MenuOperation.ADD_NODE) {
            this.addFocusNodeId = a130[0];
            this.nodeIdAndSubtitleMap.set(this.getClickNodeId(), this.selectedParentNodeSubtitle);
            this.nodeIdAndSubtitleMap.set(a130[0], this.insertNodeSubtitle);
            this.refreshAddNodeData(a130);
        }
    }

    removeNode(o129, p129) {
        if (this.nodeIdNodeItemMap.has(p129) && this.nodeIdNodeItemMap.has(o129)) {
            let q129 = this.nodeIdNodeItemMap.get(p129);
            let r129 = this.nodeIdNodeItemMap.get(o129);
            let s129 = [];
            let t129 = r129.indexOfParent;
            let u129 = 0;
            if (t129 < 0) {
                hilog.error(LOG_CODE, TAG, 'node does not exist.');
                return [];
            } else {
                u129 = q129.children[t129].getChildNodeInfo().allChildNum + 1;
                this.freeNodeMemory(q129.children[t129], s129);
                for (let x129 = t129; x129 < q129.children.length; x129++) {
                    q129.children[x129].indexOfParent -= 1;
                }
                let w129 = q129.children.splice(t129, 1);
                w129 = null;
                this.judgeImageCollapse(p129);
            }
            q129.getChildNodeInfo().childNum = q129.children.length;
            q129.getChildNodeInfo().allChildNum -= (u129);
            let v129 = [];
            v129.push(q129.parentNodeId);
            delayUpdateParentChildNum(false, u129, this.nodeIdNodeItemMap, v129);
            return s129;
        } else {
            hilog.error(LOG_CODE, TAG, 'parent does not exist.');
            return [];
        }
    }

    addNode(h129, i129, j129, k129) {
        if (this._root === null) {
            this._root = new NodeItem(emptyNodeInfo);
            this._root.nodeLevel = -1;
            this.nodeIdNodeItemMap.set(-1, this._root);
            this.nodeIdNodeParamMap.set(-1, emptyNodeInfo);
        }
        if (this.nodeIdNodeItemMap.has(h129)) {
            let l129 = this.nodeIdNodeItemMap.get(h129);
            let m129 = new NodeItem(j129);
            if (l129.nodeLevel > this.maxNodeLevel) {
                hilog.error(LOG_CODE, TAG, 'ListDataSource[addNode]: The level of the tree view cannot exceed 50.');
                return false;
            }
            m129.nodeLevel = l129.nodeLevel + 1;
            m129.parentNodeId = h129;
            m129.currentNodeId = i129;
            m129.indexOfParent = l129.children.length;
            j129.parentNodeId = h129;
            j129.currentNodeId = i129;
            if (j129.symbolIconStyle && !j129.icon) {
                j129.icon = 'symbolUsed';
            }
            l129.children.push(m129);
            l129.getChildNodeInfo().isHasChildNode = true;
            l129.getChildNodeInfo().childNum = l129.children.length;
            l129.getChildNodeInfo().allChildNum += 1;
            this.judgeImageCollapse(h129);
            if (k129) {
                this.updateNodeIdList.push(l129.parentNodeId);
            } else {
                let n129 = [];
                n129.push(l129.parentNodeId);
                delayUpdateParentChildNum(true, 1, this.nodeIdNodeItemMap, n129);
            }
            this.nodeIdNodeParamMap.set(i129, j129);
            this.nodeIdNodeItemMap.set(i129, m129);
            return true;
        } else {
            hilog.error(LOG_CODE, TAG, 'ListDataSource[addNode]: Parent node not found.');
            return false;
        }
    }

    judgeImageCollapse(e129) {
        if (e129 === undefined) {
            return;
        }
        let f129 = this.nodeIdNodeItemMap.get(e129);
        let g129 = this.nodeIdAndNodeIndexMap.get(e129);
        if (f129.children.length > 0) {
            if (this.nodeIdAndNodeIndexMap.has(e129)) {
                this.listNode[g129]?.addImageExpand(true);
            }
        } else {
            this.listNode[g129]?.addImageExpand(false);
        }
    }

    freeNodeMemory(y128, z128) {
        let a129 = [];
        let b129 = (d129) => {
            a129.push(d129);
            return false;
        };
        this.traverseNodeDF(b129, y128);
        a129.forEach((c129) => {
            z128.push(c129.getCurrentNodeId());
            this.nodeIdNodeItemMap.delete(c129.getCurrentNodeId());
            this.nodeIdNodeParamMap.delete(c129.getCurrentNodeId());
            c129 = new NodeItem(emptyNodeInfo);
        });
    }

    getNodeInfoByNodeItem(w128) {
        if (w128?.currentNodeId === undefined) {
            hilog.error(LOG_CODE, TAG, 'getNodeInfoByNodeItem: currentId is undefined');
            return new NodeInfo(new NodeItem(emptyNodeInfo), emptyNodeInfo);
        }
        if (!this.nodeIdAndNodeIndexMap.has(w128.currentNodeId)) {
            hilog.error(LOG_CODE, TAG, 'getNodeInfoByNodeItem: not has nodeItem.');
            return new NodeInfo(new NodeItem(emptyNodeInfo), emptyNodeInfo);
        }
        let x128 = this.nodeIdAndNodeIndexMap.get(w128.currentNodeId);
        return this.listNode[x128];
    }

    getNewNodeParam(r128) {
        let s128 = new NodeItem(emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(r128)) {
            s128 = this.nodeIdNodeItemMap.get(r128);
        }
        let t128 = emptyNodeInfo;
        if (s128) {
            let u128 = this.getNodeInfoByNodeItem(s128);
            if (s128.children.length === 0) {
                if (u128.getNodeItem().imageNode !== undefined) {
                    t128.icon = u128.getNodeItem().imageNode?.normalSource;
                    t128.symbolIconStyle = u128.getNodeItem().imageNode?.symbolNormalSource;
                    t128.selectedIcon = u128.getNodeItem().imageNode?.selectedSource;
                    t128.symbolSelectedIconStyle = u128.getNodeItem().imageNode?.symbolSelectedSource;
                    t128.editIcon = u128.getNodeItem().imageNode?.editSource;
                    t128.symbolEditIconStyle = u128.getNodeItem().imageNode?.symbolEditSource;
                    t128.container = u128.getMenu();
                } else {
                    t128.icon = undefined;
                    t128.symbolIconStyle = undefined;
                    t128.selectedIcon = undefined;
                    t128.symbolSelectedIconStyle = undefined;
                    t128.editIcon = undefined;
                    t128.symbolEditIconStyle = undefined;
                    t128.container = u128.getMenu();
                }
            } else if (s128.children.length > 0) {
                let v128 = this.getNodeInfoByNodeItem(s128.children[0]);
                if (u128.getNodeItem().imageNode !== null) {
                    t128.icon = (v128.getNodeItem().imageNode !== undefined) ?
                        v128.getNodeItem().imageNode?.normalSource : undefined;
                    t128.symbolIconStyle = (v128.getNodeItem().imageNode !== undefined) ?
                        v128.getNodeItem().imageNode?.symbolNormalSource : undefined;
                    t128.selectedIcon = (v128.getNodeItem().imageNode !== undefined) ?
                        v128.getNodeItem().imageNode?.selectedSource : undefined;
                    t128.symbolSelectedIconStyle = (v128.getNodeItem().imageNode !== undefined) ?
                        v128.getNodeItem().imageNode?.symbolSelectedSource : undefined;
                    t128.editIcon = (v128.getNodeItem().imageNode !== undefined) ?
                        v128.getNodeItem().imageNode?.editSource : undefined;
                    t128.symbolEditIconStyle = (v128.getNodeItem().imageNode !== undefined) ?
                        v128.getNodeItem().imageNode?.symbolEditSource : undefined;
                    t128.container = v128.getMenu();
                } else {
                    t128.icon = undefined;
                    t128.symbolIconStyle = undefined;
                    t128.selectedIcon = undefined;
                    t128.symbolSelectedIconStyle = undefined;
                    t128.editIcon = undefined;
                    t128.symbolEditIconStyle = undefined;
                    t128.container = v128.getMenu();
                }
            }
        }
        return t128;
    }

    getClickChildId(m128) {
        let n128 = new NodeItem(emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(m128)) {
            n128 = this.nodeIdNodeItemMap.get(m128);
        }
        if (n128) {
            if (n128.children.length === 0) {
                return [];
            } else if (n128.children.length > 0) {
                let o128 = new Array(n128.children.length);
                for (let q128 = 0; q128 < o128.length; q128++) {
                    o128[q128] = 0;
                }
                for (let p128 = 0; p128 < n128.children.length && p128 < o128.length; p128++) {
                    o128[p128] = n128.children[p128].currentNodeId;
                }
                return o128;
            }
        }
        return [];
    }

    getClickNodeChildrenInfo(g128) {
        let h128 = new NodeItem(emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(g128)) {
            h128 = this.nodeIdNodeItemMap.get(g128);
        }
        if (h128) {
            if (h128.children.length === 0) {
                return [];
            } else if (h128.children.length > 0) {
                let i128 = new Array(h128.children.length);
                for (let l128 = 0; l128 < i128.length; l128++) {
                    i128[l128] = {};
                }
                for (let j128 = 0; j128 < h128.children.length && j128 < i128.length; j128++) {
                    i128[j128].itemId = h128.children[j128].currentNodeId;
                    let k128 = this.getNodeInfoByNodeItem(h128.children[j128]);
                    if (k128.getNodeItem().imageNode) {
                        i128[j128].itemIcon = k128.getNodeItem().imageNode?.source;
                    }
                    if (k128.getNodeItem().mainTitleNode) {
                        i128[j128].itemTitle = k128.getNodeItem().mainTitleNode?.title;
                    }
                    i128[j128].isFolder = k128.getIsFolder();
                }
                return i128;
            }
        }
        return [];
    }

    checkMainTitleIsValid(f128) {
        if (new RegExp('/[\\\/:*?"<>|]/').test(f128)) {
            return false;
        }
        if ((new RegExp('/^[\u4e00-\u9fa5]+$/').test(f128) && f128.length > this.MAX_CN_LENGTH) ||
            (!new RegExp('/^[\u4e00-\u9fa5]+$/').test(f128) && f128.length > this.MAX_EN_LENGTH)) {
            return false;
        }
        return true;
    }

    dragTraverseNodeDF(z127, a128 = this._root, b128) {
        let c128 = [];
        let d128 = false;
        c128.unshift(a128);
        let e128 = c128.shift();
        while (!d128 && e128) {
            d128 = z127(e128, b128) === true;
            if (!d128) {
                c128.unshift(...e128.children);
                e128 = c128.shift();
            }
        }
    }

    updateChildIndexOfParent(w127, x127) {
        for (let y127 = w127; y127 < x127.children.length; y127++) {
            x127.children[y127].indexOfParent += 1;
        }
    }

    addDragNode(n127, o127, p127, q127, r127) {
        if (this._root === null) {
            this._root = new NodeItem(emptyNodeInfo);
            this._root.nodeLevel = this.INITIAL_INVALID_VALUE;
        }
        if (this.nodeIdNodeItemMap.has(n127)) {
            let s127 = this.nodeIdNodeItemMap.get(n127);
            let t127 = new NodeItem(r127);
            if (s127.nodeLevel > this.maxNodeLevel) {
                hilog.error(LOG_CODE, TAG, 'addDragNode: The level of the tree view cannot exceed 50.');
                return false;
            }
            t127.nodeLevel = s127.nodeLevel + 1;
            t127.parentNodeId = n127;
            t127.currentNodeId = o127;
            r127.parentNodeId = n127;
            r127.currentNodeId = o127;
            let u127 = this.INITIAL_INVALID_VALUE;
            if (s127.children.length) {
                for (let v127 = 0; v127 < s127.children.length; v127++) {
                    if (s127.children[v127].getCurrentNodeId() === p127) {
                        u127 = v127;
                        break;
                    }
                }
                if (q127) {
                    t127.indexOfParent = u127 + 1;
                    this.updateChildIndexOfParent(t127.indexOfParent, s127);
                    s127.children.splice(u127 + 1, 0, t127);
                } else {
                    t127.indexOfParent = u127 < 0 ? s127.children.length + u127 : u127;
                    this.updateChildIndexOfParent(t127.indexOfParent, s127);
                    s127.children.splice(u127, 0, t127);
                }
            } else {
                t127.indexOfParent = s127.children.length;
                s127.children.push(t127);
            }
            s127.getChildNodeInfo().isHasChildNode = true;
            s127.getChildNodeInfo().childNum = s127.children.length;
            s127.getChildNodeInfo().allChildNum += 1;
            this.updateParentChildNum(s127, true, 1);
            this.nodeIdNodeItemMap.set(o127, t127);
            this.nodeIdNodeParamMap.set(o127, r127);
            return true;
        } else {
            hilog.error(LOG_CODE, TAG, 'addDragNode: Parent node not found.');
            return false;
        }
    }
}

class ButtonGestureModifier {
    constructor(m127) {
        this.fontSize = 1;
        this.controller = null;
        this.controller = m127;
    }

    applyGesture(l127) {
        if (this.fontSize >= ButtonGestureModifier.minFontSize) {
            l127.addGesture(new LongPressGestureHandler({
                repeat: false,
                duration: ButtonGestureModifier.longPressTime
            })
                .onAction(() => {
                    if (l127) {
                        this.controller?.open();
                    }
                })
                .onActionEnd(() => {
                    this.controller?.close();
                }));
        } else {
            l127.clearGestures();
        }
    }
}

ButtonGestureModifier.longPressTime = 500;
ButtonGestureModifier.minFontSize = 1.75;

export class TreeViewInner extends ViewV2 {
    constructor(f127, g127, h127, i127 = -1, j127, k127) {
        super(f127, i127, k127);
        this.initParam('item', (g127 && 'item' in g127) ? g127.item : undefined);
        this.initParam('listNodeDataSource',
            (g127 && 'listNodeDataSource' in g127) ? g127.listNodeDataSource : new ListNodeDataSource());
        this.columnWidth = 0;
        this.isFocused = false;
        this.initParam('index', (g127 && 'index' in g127) ? g127.index : -1);
        this.lastIndex = -1;
        this.count = 0;
        this.followingSystemFontScale = false;
        this.maxAppFontScale = 1;
        this.treeViewTheme = TreeViewTheme.getInstance();
        this.clickButtonFlag = true;
        this.accessibilityNodeType = AccessibilityNodeType.TEXT;
        this.isAccessibilityEnabled = false;
        this.listTreeViewMenu = 'listTreeViewMenu' in g127 ? g127.listTreeViewMenu : undefined;
        this.initParam('callBackClick', (g127 && 'callBackClick' in g127) ? g127.callBackClick : () => {
        });
        this.MAX_CN_LENGTH = 254;
        this.MAX_EN_LENGTH = 255;
        this.INITIAL_INVALID_VALUE = -1;
        this.MAX_TOUCH_DOWN_COUNT = 0;
        this.isMultiPress = false;
        this.touchDownCount = this.INITIAL_INVALID_VALUE;
        this.appEventBus = TreeListenerManagerV2.getInstance().getTreeListenerV2();
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

    resetStateVarsOnReuse(e127) {
        this.resetParam('item', (e127 && 'item' in e127) ? e127.item : undefined);
        this.resetParam('listNodeDataSource',
            (e127 && 'listNodeDataSource' in e127) ? e127.listNodeDataSource : new ListNodeDataSource());
        this.columnWidth = 0;
        this.isFocused = false;
        this.resetParam('index', (e127 && 'index' in e127) ? e127.index : -1);
        this.lastIndex = -1;
        this.count = 0;
        this.followingSystemFontScale = false;
        this.maxAppFontScale = 1;
        this.resetConsumer('treeViewTheme', TreeViewTheme.getInstance());
        this.resetConsumer('clickButtonFlag', true);
        this.resetConsumer('accessibilityNodeType', AccessibilityNodeType.TEXT);
        this.resetConsumer('isAccessibilityEnabled', false);
        this.listTreeViewMenu = 'listTreeViewMenu' in e127 ? e127.listTreeViewMenu : undefined;
        this.resetParam('callBackClick', (e127 && 'callBackClick' in e127) ? e127.callBackClick : () => {
        });
    }

    aboutToAppear() {
        if (this.item.getNodeItem().imageNode) {
            this.item.imageSource = this.item.getNodeItem().imageNode?.source;
            this.item.symbolSource = this.item.getNodeItem().imageNode?.symbolSource;
        }
        let d127 = this.getUIContext();
        this.followingSystemFontScale = d127.isFollowingSystemFontScale();
        this.maxAppFontScale = d127.getMaxFontScale();
    }

    decideFontScale() {
        let b127 = this.getUIContext();
        let c127 = b127.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.followingSystemFontScale) {
            return 1;
        }
        return Math.min(c127, this.maxAppFontScale, MAX_FONT_SCALE);
    }

    decideSymbolFontScale(x126) {
        if (!x126 || !this.followingSystemFontScale) {
            return 1;
        }
        let y126 = this.getUIContext();
        let z126 = y126.getHostContext()?.config?.fontSizeScale ?? 1;
        let a127 = Math.min(z126, this.maxAppFontScale, MAX_SYMBOL_FONT_SCALE);
        return Math.max(a127, MIN_SYMBOL_FONT_SCALE);
    }

    getInputTextMaxFontSize() {
        let w126 = this.decideFontScale() * this.inputFontSize + 'vp';
        return w126;
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

    checkInvalidPattern(v126) {
        return new RegExp('/[\\\/:*?"<>|]/').test(v126);
    }

    checkIsAllCN(u126) {
        return new RegExp('/^[\u4e00-\u9fa5]+$/').test(u126);
    }

    getAccessibilityReadText(d126) {
        let e126 = this.listNodeDataSource.nodeIdNodeItemMap.get(d126);
        if (e126 === undefined || d126 === undefined) {
            return '';
        }
        let f126 = this.listNodeDataSource.getNodeInfoByNodeItem(e126);
        let g126 = f126?.getNodeInfoData()?.primaryTitle === undefined
            ? '' : f126?.getNodeInfoData()?.primaryTitle;
        let h126 = f126?.getNodeInfoData()?.secondaryTitle === undefined
            ? '' : f126?.getNodeInfoData()?.secondaryTitle;
        let i126 = this.listNodeDataSource.getAccessibleTitleText(g126);
        let j126 = this.listNodeDataSource.getAccessibleTitleText(h126);
        let k126 = `${i126}, ${j126}`;
        let l126 = this.listNodeDataSource.findParentNodeId(d126);
        let m126 = [];
        let n126 = 0;
        let o126 = this.listNodeDataSource.getClickNodeChildrenInfo(l126);
        let p126 = o126.map(t126 => t126.itemId);
        let q126 = p126.indexOf(d126) + 1;
        let r126 = this.listNodeDataSource.getAccessibleTitle(d126);
        if (r126 === undefined) {
            return ' ';
        }
        if (this.accessibilityNodeType === AccessibilityNodeType.PLACE) {
            if (this.listNodeDataSource.findParentNodeId(d126) === -1) {
                for (let s126 = 0; s126 < this.listNodeDataSource.listNode.length; s126++) {
                    if (this.listNodeDataSource.listNode[s126].getNodeParentNodeId() === -1) {
                        m126.push(this.listNodeDataSource.listNode[s126].getNodeCurrentNodeId());
                    }
                }
                n126 = m126.indexOf(d126) + 1;
                return this.listNodeDataSource.getStringByName('treeview_accessibility_place_node_parent', n126);
            } else {
                return this.listNodeDataSource.getStringByName('treeview_accessibility_place_node_child', r126, q126);
            }
        } else if (this.accessibilityNodeType === AccessibilityNodeType.LIFT) {
            return k126;
        } else {
            return k126;
        }
    }

    getAccessibilityDescription() {
        if (this.accessibilityNodeType === AccessibilityNodeType.TEXT) {
            return this.listNodeDataSource.getStringByName('treeview_accessibility_node_desc');
        } else {
            return ' ';
        }
    }

    getAccessibilityReadButtonText(c126) {
        if (this.clickButtonFlag === false) {
            return this.item.getNodeItem().imageCollapse?.collapseSource === ARROW_RIGHT
                ? this.listNodeDataSource.getStringByName('treeview_accessibility_folded_node')
                : this.listNodeDataSource.getStringByName('treeview_accessibility_expanded_node');
        } else {
            return c126 ? this.listNodeDataSource.getStringByName('treeview_accessibility_expand_node')
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

    onTouchNode(z125) {
        this.count++;
        if (this.count > 1) {
            this.count--;
            return;
        }
        this.index = this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId());
        this.listNodeDataSource.setClickIndex(this.index);
        let a126 = this.item.getNodeCurrentNodeId();
        if (z125.type === TouchType.Down) {
            this.item.setNodeColor(this.treeViewTheme.itemPressedBgColor);
        } else if (z125.type === TouchType.Up) {
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
            let b126 = { currentNodeId: a126 };
            this.appEventBus.emit(TreeListenTypeV2.NODE_CLICK, b126);
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
        let x125 = this.item.getNodeCurrentNodeId();
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
        let y125 = { currentNodeId: x125 };
        this.appEventBus.emit(TreeListenTypeV2.NODE_CLICK, y125);
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
        let w125 = ({
            type: 'requestFocusForAccessibility',
            bundleName: getContext()?.abilityInfo?.bundleName,
            triggerAction: 'common',
            customId: `treeView_button${this.item.getNodeCurrentNodeId()}`
        });
        accessibility.sendAccessibilityEvent(w125).then(() => {
            setTimeout(() => {
                this.clickButtonFlag = true;
            }, ENTER_EXIT_DURATION);
        });
    }

    popupForShowTitle(o125, p125, q125, r125 = null) {
        this.observeComponentCreation2((u125, v125) => {
            Row.create();
            Row.backgroundColor(p125);
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
        this.observeComponentCreation2((s125, t125) => {
            Text.create(o125);
            Text.fontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_body2'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Text.fontWeight('regular');
            Text.fontColor(q125);
            Text.minFontScale(MIN_FONT_SCALE);
            Text.maxFontScale(this.decideFontScale());
        }, Text);
        Text.pop();
        Row.pop();
    }

    builder(l125 = null) {
        this.observeComponentCreation2((m125, n125) => {
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
        this.observeComponentCreation2((u122, v122) => {
            If.create();
            if (this.item.getNodeIsShow()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((j125, k125) => {
                        Stack.create();
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
                        ViewStackProcessor.visualState();
                    }, Stack);
                    this.observeComponentCreation2((a125, b125) => {
                        Column.create();
                        Column.opacity(this.listNodeDataSource.getListItemOpacity(this.item));
                        Column.onHover((i125) => {
                            if (i125) {
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
                        Column.onTouch(this.isAccessibilityEnabled ? undefined : (h125) => {
                            this.onTouchNode(h125);
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
                        Column.onMouse((f125) => {
                            let g125 = this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId());
                            if (f125.button === MouseButton.Right) {
                                this.listNodeDataSource.handleEvent(Event.MOUSE_BUTTON_RIGHT,
                                    this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId()));
                                this.listTreeViewMenu = this.item.getMenu();
                                this.listNodeDataSource.setClickIndex(g125);
                                clearTimeout(this.item.getNodeItem().mainTitleNode?.popUpTimeout);
                            }
                            f125.stopPropagation();
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
                        Column.onAreaChange((c125, d125) => {
                            let e125 = Number.parseInt(d125.width.toString());
                            this.columnWidth = e125;
                        });
                    }, Column);
                    this.observeComponentCreation2((y124, z124) => {
                        Stack.create({ alignContent: Alignment.Bottom });
                        Stack.focusable(true);
                    }, Stack);
                    this.observeComponentCreation2((w124, x124) => {
                        Divider.create();
                        Divider.height(this.listNodeDataSource.getFlagLine().flagLineHeight);
                        Divider.color(this.listNodeDataSource.getFlagLine().flagLineColor);
                        Divider.visibility(this.listNodeDataSource.getVisibility(this.item));
                        Divider.lineCap(LineCapStyle.Round);
                        Divider.margin({ start: LengthMetrics.vp(this.item.getFlagLineLeftMargin()) });
                        Divider.focusable(true);
                    }, Divider);
                    this.observeComponentCreation2((u124, v124) => {
                        Row.create({});
                        Row.focusable(true);
                        Row.width('100%');
                        Row.height(this.item.getNodeHeight());
                        Row.padding({ start: LengthMetrics.vp(this.item.getNodeLeftPadding()) });
                        Row.bindContextMenu({ builder: this.builder.bind(this) }, ResponseType.RightClick);
                    }, Row);
                    this.observeComponentCreation2((s124, t124) => {
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
                    this.observeComponentCreation2((e124, f124) => {
                        If.create();
                        if (this.item.getNodeItem().imageNode) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((q124, r124) => {
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
                                this.observeComponentCreation2((g124, h124) => {
                                    If.create();
                                    if (this.item.symbolSource) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((o124, p124) => {
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
                                            this.observeComponentCreation2((i124, j124) => {
                                                If.create();
                                                if (Util.isSymbolResource(this.item.imageSource)) {
                                                    this.ifElseBranchUpdateFunction(0, () => {
                                                        this.observeComponentCreation2((m124, n124) => {
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
                                                        this.observeComponentCreation2((k124, l124) => {
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
                    this.observeComponentCreation2((c124, d124) => {
                        Row.create();
                        Row.layoutWeight(1);
                        Row.focusable(true);
                    }, Row);
                    this.observeComponentCreation2((y123, z123) => {
                        If.create();
                        if (this.item.getNodeItem().mainTitleNode && this.item.getIsShowTitle()) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((a124, b124) => {
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
                    this.observeComponentCreation2((k123, l123) => {
                        If.create();
                        if (this.item.getNodeItem().mainTitleNode && this.item.getNodeItem().inputText &&
                            this.item.getIsShowInputText()) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((w123, x123) => {
                                    Row.create();
                                    Row.backgroundColor(this.item.getNodeItem().inputText?.backgroundColor);
                                    Row.borderRadius(this.item.getNodeItem().inputText?.borderRadius);
                                    Row.margin({
                                        end: getLengthMetricsByResourceOrNumber(this.item.getNodeItem()
                                            .inputText?.itemRightMargin)
                                    });
                                }, Row);
                                this.observeComponentCreation2((m123, n123) => {
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
                                    TextInput.onChange((q123) => {
                                        let r123 = this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId());
                                        let s123 = '';
                                        let t123 = false;
                                        let u123 = false;
                                        if (this.checkInvalidPattern(q123)) {
                                            for (let v123 = 0; v123 < q123.length; v123++) {
                                                if (!this.checkInvalidPattern(q123[v123])) {
                                                    s123 += q123[v123];
                                                }
                                            }
                                            t123 = true;
                                            this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS,
                                                InputError.INVALID_ERROR, true, r123);
                                        } else {
                                            s123 = q123;
                                            t123 = false;
                                        }
                                        if ((this.checkIsAllCN(s123) && s123.length > this.MAX_CN_LENGTH) ||
                                            (!this.checkIsAllCN(s123) && s123.length > this.MAX_EN_LENGTH)) {
                                            s123 = this.checkIsAllCN(s123) ?
                                                s123.substr(0, this.MAX_CN_LENGTH) : s123.substr(0, this.MAX_EN_LENGTH);
                                            u123 = true;
                                            this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS,
                                                InputError.LENGTH_ERROR, true, r123);
                                        } else {
                                            u123 = false;
                                        }
                                        if (!u123 && !t123) {
                                            this.listNodeDataSource.setMainTitleNameOnEdit(r123, s123);
                                        }
                                    });
                                    TextInput.onSubmit((o123) => {
                                        let p123 = this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId());
                                        this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false,
                                            p123);
                                        this.listNodeDataSource.setItemVisibilityOnEdit(p123,
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
                    this.observeComponentCreation2((i123, j123) => {
                        Blank.create();
                    }, Blank);
                    Blank.pop();
                    Row.pop();
                    this.observeComponentCreation2((c123, d123) => {
                        If.create();
                        if (this.listNodeDataSource.hasSubtitle(this.item.getNodeCurrentNodeId())) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((g123, h123) => {
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
                                this.observeComponentCreation2((e123, f123) => {
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
                    this.observeComponentCreation2((w122, x122) => {
                        If.create();
                        if (this.item.getNodeItem().imageCollapse) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                if (!If.canRetake(`treeView_button${this.item.getNodeCurrentNodeId()}`)) {
                                    this.observeComponentCreation2((a123, b123) => {
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
                                    this.observeComponentCreation2((y122, z122) => {
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

    updateStateVars(t122) {
        if (t122 === undefined) {
            return;
        }
        if ('item' in t122) {
            this.updateParam('item', t122.item);
        }
        if ('listNodeDataSource' in t122) {
            this.updateParam('listNodeDataSource', t122.listNodeDataSource);
        }
        if ('index' in t122) {
            this.updateParam('index', t122.index);
        }
        if ('callBackClick' in t122) {
            this.updateParam('callBackClick', t122.callBackClick);
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
    Param,
    Once
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
    Consumer()
], TreeViewInner.prototype, 'treeViewTheme', void 0);
__decorate([
    Consumer()
], TreeViewInner.prototype, 'clickButtonFlag', void 0);
__decorate([
    Consumer()
], TreeViewInner.prototype, 'accessibilityNodeType', void 0);
__decorate([
    Consumer()
], TreeViewInner.prototype, 'isAccessibilityEnabled', void 0);
__decorate([
    Param
], TreeViewInner.prototype, 'callBackClick', void 0);

export class NodeItem {
    constructor(s122) {
        this.currentNodeId = s122.currentNodeId ?? -1;
        this.parentNodeId = s122.parentNodeId ?? -1;
        this.isFolder = s122.isFolder;
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

    set itemWidth(r122) {
        this.width = r122;
    }

    get itemWidth() {
        return this.width;
    }

    set itemHeight(q122) {
        this.height = q122;
    }

    get itemHeight() {
        return this.height;
    }

    set itemRightMargin(p122) {
        this.rightMargin = p122;
    }

    get itemRightMargin() {
        return this.rightMargin;
    }
}

export class CollapseImageNode extends NodeBaseInfo {
    constructor(h122, i122, j122, k122, l122, m122, n122, o122) {
        super();
        this.rightMargin = {
            'id': -1,
            'type': 10002,
            params: ['sys.float.ohos_id_elements_margin_horizontal_m'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.imageSource = h122;
        this.symbolIconSource = i122;
        this.rightMargin = m122;
        this.imageOpacity = j122;
        this.itemWidth = k122;
        this.itemHeight = l122;
        this.imageCollapseSource = h122;
        this.symbolIconCollapseSource = i122;
        this.isImageCollapse = n122;
        this.collapseImageType = o122;
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

    createCollapseImageNodeByType(f122) {
        let g122;
        switch (f122) {
            case CollapseImageType.ARROW_RIGHT_WHITE:
                g122 = ARROW_RIGHT_WITHE;
                break;
            case CollapseImageType.ARROW_RIGHT:
                g122 = ARROW_RIGHT;
                break;
            case CollapseImageType.ARROW_DOWN_WHITE:
                g122 = ARROW_DOWN_WITHE;
                break;
            default:
                g122 = ARROW_DOWN;
        }
        return new CollapseImageNode(g122, undefined, {
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
        }, (f122 === CollapseImageType.ARROW_RIGHT_WHITE || f122 === CollapseImageType.ARROW_DOWN_WHITE) ? false : true,
            f122);
    }
}

class CollapseImageNodeFlyweightFactory {
    static getCollapseImageNodeByType(d122) {
        let e122 = CollapseImageNodeFlyweightFactory.nodeMap.get(d122);
        if (e122 === undefined) {
            e122 = CollapseImageNodeFactory.getInstance().createCollapseImageNodeByType(d122);
            CollapseImageNodeFlyweightFactory.nodeMap.set(d122, e122);
        }
        return e122;
    }

    static getCollapseImageNode(z121, a122, b122) {
        if (b122 === undefined) {
            return undefined;
        }
        let c122 = b122;
        if (z121 == InteractionStatus.EDIT ||
            z121 === InteractionStatus.DRAG_INSERT) {
            if (a122 === NodeStatus.COLLAPSE) {
                c122 = CollapseImageType.ARROW_RIGHT_WHITE;
            } else {
                c122 = CollapseImageType.ARROW_DOWN_WHITE;
            }
        } else if (z121 === InteractionStatus.FINISH_EDIT ||
            z121 === InteractionStatus.FINISH_DRAG_INSERT) {
            if (a122 === NodeStatus.COLLAPSE) {
                c122 = CollapseImageType.ARROW_RIGHT;
            } else {
                c122 = CollapseImageType.ARROW_DOWN;
            }
        }
        return CollapseImageNodeFlyweightFactory.getCollapseImageNodeByType(c122);
    }

    static changeImageCollapseSource(w121, x121) {
        if (x121 === undefined) {
            return undefined;
        }
        let y121;
        if (!x121) {
            if (w121 === NodeStatus.COLLAPSE) {
                y121 = CollapseImageType.ARROW_RIGHT_WHITE;
            } else {
                y121 = CollapseImageType.ARROW_DOWN_WHITE;
            }
        } else {
            if (w121 === NodeStatus.COLLAPSE) {
                y121 = CollapseImageType.ARROW_RIGHT;
            } else {
                y121 = CollapseImageType.ARROW_DOWN;
            }
        }
        return CollapseImageNodeFlyweightFactory.getCollapseImageNodeByType(y121);
    }
}

CollapseImageNodeFlyweightFactory.nodeMap = new Map();

export class ImageNode extends NodeBaseInfo {
    constructor(n121, o121, p121, q121, r121, s121, t121, u121, v121) {
        super();
        this.rightMargin = {
            'id': -1,
            'type': 10002,
            params: ['sys.float.ohos_id_elements_margin_horizontal_m'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.imageSource = n121;
        this.symbolIconSource = o121;
        this.imageNormalSource = n121;
        this.symbolIconNormalSource = o121;
        if (s121 !== undefined) {
            this.imageSelectedSource = s121;
        } else {
            this.imageSelectedSource = this.imageNormalSource;
        }
        this.symbolIconSelectedSource = t121;
        if (u121 !== undefined) {
            this.imageEditSource = u121;
        } else {
            this.imageEditSource = this.imageNormalSource;
        }
        this.symbolIconEditSource = v121;
        this.imageOpacity = p121;
        this.itemWidth = q121;
        this.itemHeight = r121;
        this.imageCollapseSource = n121;
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

    changeImageCollapseSource(m121) {
        if (m121 === NodeStatus.EXPAND) {
            this.imageCollapseSource = this.imageCollapseDownSource;
        } else if (m121 === NodeStatus.COLLAPSE) {
            this.imageCollapseSource = this.imageCollapseRightSource;
        }
    }

    setImageCollapseSource(k121, l121) {
        if (k121 === InteractionStatus.EDIT || k121 === InteractionStatus.DRAG_INSERT) {
            this.imageCollapseDownSource = ARROW_DOWN_WITHE;
            this.imageCollapseRightSource = ARROW_RIGHT_WITHE;
            this.isImageCollapse = false;
        } else if (k121 === InteractionStatus.FINISH_EDIT ||
            k121 === InteractionStatus.FINISH_DRAG_INSERT) {
            this.imageCollapseDownSource = ARROW_DOWN;
            this.imageCollapseRightSource = ARROW_RIGHT;
            this.isImageCollapse = true;
        }
        this.imageCollapseSource = (l121 === NodeStatus.COLLAPSE) ?
            this.imageCollapseRightSource : this.imageCollapseDownSource;
    }

    setImageSource(j121) {
        switch (j121) {
            case InteractionStatus.NORMAL:
                this.imageSource = this.imageNormalSource;
                this.symbolIconSource = this.symbolIconNormalSource;
                this.currentInteractionStatus = j121;
                break;
            case InteractionStatus.SELECTED:
                if (this.currentInteractionStatus !== InteractionStatus.EDIT) {
                    this.imageSource = this.imageSelectedSource;
                    this.symbolIconSource = this.symbolIconSelectedSource;
                    this.currentInteractionStatus = j121;
                }
                break;
            case InteractionStatus.EDIT:
                this.imageSource = this.imageEditSource;
                this.symbolIconSource = this.symbolIconEditSource;
                this.currentInteractionStatus = j121;
                break;
            case InteractionStatus.FINISH_EDIT:
                this.imageSource = this.imageSelectedSource;
                this.symbolIconSource = this.symbolIconSelectedSource;
                this.currentInteractionStatus = j121;
                break;
            case InteractionStatus.DRAG_INSERT:
                this.imageSource = this.imageEditSource;
                this.symbolIconSource = this.symbolIconEditSource;
                this.currentInteractionStatus = j121;
                break;
            case InteractionStatus.FINISH_DRAG_INSERT:
                this.imageSource = this.imageNormalSource;
                this.symbolIconSource = this.symbolIconNormalSource;
                this.currentInteractionStatus = j121;
                break;
            default:
                break;
        }
    }
}

class MainTitleNode extends NodeBaseInfo {
    constructor(i121) {
        super();
        this.treeViewTheme = TreeViewTheme.getInstance();
        this.mainTitleName = i121;
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

    setMainTitleSelected(h121) {
        if (h121) {
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

    set title(g121) {
        this.mainTitleName = g121;
    }

    get title() {
        return this.mainTitleName;
    }

    set popUpTimeout(f121) {
        this.showPopUpTimeout = f121;
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

    setMainTitleHighLight(e121) {
        if (e121) {
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

function getLengthMetricsByResourceOrNumber(d121) {
    if (!d121) {
        return LengthMetrics.vp(0);
    } else if (typeof d121 === 'number') {
        return LengthMetrics.vp(d121);
    } else {
        return LengthMetrics.resource(d121);
    }
}

export default {
    TreeControllerV2,
    TreeListenerV2,
    TreeListenerManagerV2,
    TreeListenTypeV2,
    TreeViewV2,
}