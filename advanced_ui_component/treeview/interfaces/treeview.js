/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
var __decorate = (this && this.__decorate) || function (f27, g27, h27, i27) {
    var j27 = arguments.length,
        k27 = j27 < 3 ? g27 : i27 === null ? i27 = Object.getOwnPropertyDescriptor(g27, h27) : i27, l27;
    if (typeof Reflect === 'object' && typeof Reflect.decorate === 'function')
        k27 = Reflect.decorate(f27, g27, h27, i27);
    else
        for (var m27 = f27.length - 1; m27 >= 0; m27--)
            if (l27 = f27[m27])
                k27 = (j27 < 3 ? l27(k27) : j27 > 3 ? l27(g27, h27, k27) : l27(g27, h27)) || k27;
    return j27 > 3 && k27 && Object.defineProperty(g27, h27, k27), k27;
};
if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {
    });
}
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;

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
const FLAG_LINE_HEIGHT = '1.0vp';
const X_OFF_SET = '0vp';
const Y_OFF_SET = '2.75vp';
const Y_BOTTOM_OFF_SET = '-1.25vp';
const Y_BASE_PLATE_OFF_SET = '1.5vp';
const COLOR_IMAGE_EDIT = '#FFFFFF';
const SHADOW_COLOR = '#00001E';
const GRAG_POP_UP_HEIGHT = '48';
const FLOOR_MIN_WIDTH = '128vp';
const FLOOR_MAX_WIDTH = '208vp';
const TEXT_MIN_WIDTH = '80vp';
const TEXT_MAX_WIDTH = '160vp';
const MIN_WIDTH = '112vp';
const MAX_WIDTH = '192vp';
const TRANS_COLOR = '#00FFFFFF';
const ARROW_DOWN = {
    'id': -1,
    'type': 20000,
    params: ['sys.media.ohos_ic_public_arrow_down'],
    'bundleName': '__harDefaultBundleName__',
    'moduleName': '__harDefaultModuleName__',
};
const ARROW_DOWN_WITHE = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAAAIGNIUk0AAHomAAC' +
    'AhAAA+gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAAEZ0FNQQAAsY58+1GTAAAAAXNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAAl' +
    'wSFlzAAAOxAAADsQBlSsOGwAAAKVJREFUeNpjYBgFo2AU0Bww4pL4////diC1hZGRcSo+A4DqWIDUZCB+AVTbiC7PhEfvByCeAjQgn4Dhy4E' +
    '4BYgvYFODz4JYIF4DxBOwWYJkeAAQRwBdvxGbIcy4TG9sbPzX0NCwHsjUAuIiIPsDUOwkDsPXkhwHWFwaAsQlQAwyrJsYw4myAIslIPCHGMP' +
    'xBhGO4PoGxF+AOA9o+NbRTDgKRgFxAAAzj0Grm3RjyAAAAABJRU5ErkJggg==';
const ARROW_RIGHT = {
    'id': -1,
    'type': 20000,
    params: ['sys.media.ohos_ic_public_arrow_right'],
    'bundleName': '__harDefaultBundleName__',
    'moduleName': '__harDefaultModuleName__',
};
const ARROW_RIGHT_WITHE = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAAAIGNIUk0AAHomAA' +
    'CAhAAA+gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAAEZ0FNQQAAsY58+1GTAAAAAXNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAA' +
    'lwSFlzAAAOxAAADsQBlSsOGwAAAKFJREFUeNpjYBgFowAE/v//bwHEPOToZSJS3XIg3k6OJcRaUALEFuRYwkyMosbGxusNDQ3XgMwCIHYAsl' +
    'cDxX5RzQJKLGEmxbvkWMJEaqQxMjKuBVI5QGwDxOnUimR08AFK81DdAmAqArl8DhDfAOKpVLUAavh2IH4CxI7A4HpDMEgpMPwFUXFGS8NJCa' +
    'L55BgOAixEqqsB4oOkGj4KRggAAN4STB9zyhGzAAAAAElFTkSuQmCC';
var Event;
(function (d27) {
    d27[d27['TOUCH_DOWN'] = 0] = 'TOUCH_DOWN';
    d27[d27['TOUCH_UP'] = 1] = 'TOUCH_UP';
    d27[d27['HOVER'] = 3] = 'HOVER';
    d27[d27['HOVER_OVER'] = 4] = 'HOVER_OVER';
    d27[d27['FOCUS'] = 5] = 'FOCUS';
    d27[d27['BLUR'] = 6] = 'BLUR';
    d27[d27['MOUSE_BUTTON_RIGHT'] = 7] = 'MOUSE_BUTTON_RIGHT';
    d27[d27['DRAG'] = 8] = 'DRAG';
})(Event || (Event = {}));
var MenuOperation;
(function (c27) {
    c27[c27['ADD_NODE'] = 0] = 'ADD_NODE';
    c27[c27['REMOVE_NODE'] = 1] = 'REMOVE_NODE';
    c27[c27['MODIFY_NODE'] = 2] = 'MODIFY_NODE';
    c27[c27['COMMIT_NODE'] = 3] = 'COMMIT_NODE';
})(MenuOperation || (MenuOperation = {}));
var PopUpType;
(function (b27) {
    b27[b27['HINTS'] = 0] = 'HINTS';
    b27[b27['WARNINGS'] = 1] = 'WARNINGS';
})(PopUpType || (PopUpType = {}));
var InputError;
(function (a27) {
    a27[a27['INVALID_ERROR'] = 0] = 'INVALID_ERROR';
    a27[a27['LENGTH_ERROR'] = 1] = 'LENGTH_ERROR';
    a27[a27['NONE'] = 2] = 'NONE';
})(InputError || (InputError = {}));
var Flag;
(function (z26) {
    z26[z26['DOWN_FLAG'] = 0] = 'DOWN_FLAG';
    z26[z26['UP_FLAG'] = 1] = 'UP_FLAG';
    z26[z26['NONE'] = 2] = 'NONE';
})(Flag || (Flag = {}));

export var NodeStatus;
(function (y26) {
    y26[y26['Expand'] = 0] = 'Expand';
    y26[y26['Collapse'] = 1] = 'Collapse';
})(NodeStatus || (NodeStatus = {}));

export var InteractionStatus;
(function (x26) {
    x26[x26['Normal'] = 0] = 'Normal';
    x26[x26['Selected'] = 1] = 'Selected';
    x26[x26['Edit'] = 2] = 'Edit';
    x26[x26['FinishEdit'] = 3] = 'FinishEdit';
    x26[x26['DragInsert'] = 4] = 'DragInsert';
    x26[x26['FinishDragInsert'] = 5] = 'FinishDragInsert';
})(InteractionStatus || (InteractionStatus = {}));
let emptyNodeInfo = {
    isFolder: true,
    icon: '',
    selectedIcon: '',
    editIcon: '',
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
}

let NodeInfo = class NodeInfo {
    constructor(w26) {
        this.imageSource = '';
        this.borderWidth = { has: BORDER_WIDTH_HAS, none: BORDER_WIDTH_NONE };
        this.canShowFlagLine = false;
        this.isOverBorder = false;
        this.canShowBottomFlagLine = false;
        this.isHighLight = false;
        this.isModify = false;
        this.treeViewTheme = new TreeViewTheme();
        this.fontColor = '';
        this.childNodeInfo = w26.getChildNodeInfo();
        this.nodeItem = {
            imageNode: undefined,
            inputText: new InputText(),
            mainTitleNode: w26.getNodeItem().mainTitleNode,
            imageCollapse: undefined,
            fontColor: undefined,
        };
        this.popUpInfo = {
            popUpIsShow: false,
            popUpEnableArrow: false,
            popUpColor: undefined,
            popUpText: '',
            popUpTextColor: undefined,
        };
        this.nodeItem.imageNode = w26.getNodeItem().imageNode;
        this.nodeItem.imageCollapse = w26.getNodeItem().imageCollapse;
        this.container = w26.container;
        this.parentNodeId = w26.parentNodeId;
        this.currentNodeId = w26.currentNodeId;
        this.nodeHeight = NODE_HEIGHT;
        this.nodeLevel = w26.nodeLevel;
        this.nodeLeftPadding = w26.nodeLevel * 12 + 8;
        this.nodeColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_background'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.nodeIsShow = (this.nodeLevel > 0) ? false : true;
        this.listItemHeight = (this.nodeLevel > 0) ? LIST_ITEM_HEIGHT_NONE : LIST_ITEM_HEIGHT;
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
        this.flagLineLeftMargin = w26.nodeLevel * 12 + 8;
        this.node = w26;
        this.nodeParam = w26.data;
    }

    setFontColor(v26) {
        this.fontColor = v26;
    }

    getFontColor() {
        return this.fontColor;
    }

    getPopUpInfo() {
        return this.popUpInfo;
    }

    setPopUpIsShow(u26) {
        this.popUpInfo.popUpIsShow = u26;
    }

    setPopUpEnableArrow(t26) {
        this.popUpInfo.popUpEnableArrow = t26;
    }

    setPopUpColor(s26) {
        this.popUpInfo.popUpColor = s26;
    }

    setPopUpText(r26) {
        this.popUpInfo.popUpText = r26;
    }

    setPopUpTextColor(q26) {
        this.popUpInfo.popUpTextColor = q26;
    }

    getIsShowTitle() {
        return this.isShowTitle;
    }

    getIsShowInputText() {
        return this.isShowInputText;
    }

    setTitleAndInputTextStatus(p26) {
        if (p26) {
            this.isShowTitle = false;
            this.isShowInputText = true;
        }
        else {
            this.isShowTitle = true;
            this.isShowInputText = false;
        }
    }

    handleImageCollapseAfterAddNode(o26) {
        if (o26) {
            this.nodeItem.imageCollapse = new ImageNode(ARROW_DOWN, {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_alpha_content_tertiary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            }, IMAGE_NODE_HEIGHT, IMAGE_NODE_WIDTH, undefined, undefined);
            this.nodeItem.imageCollapse.itemRightMargin = ({
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_paragraph_margin_xs'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            });
        }
        else {
            this.nodeItem.imageCollapse = undefined;
        }
    }

    setNodeColor(n26) {
        if (n26 === undefined) {
            return;
        }
        this.nodeColor = n26;
    }

    getNodeColor() {
        return this.nodeColor;
    }

    setListItemHeight(m26) {
        this.listItemHeight = m26;
    }

    getListItemHeight() {
        return this.listItemHeight;
    }

    getNodeCurrentNodeId() {
        return this.currentNodeId;
    }

    getNodeParentNodeId() {
        return this.parentNodeId;
    }

    getNodeLeftPadding() {
        return this.nodeLeftPadding;
    }

    getNodeHeight() {
        return this.nodeHeight;
    }

    setNodeIsShow(l26) {
        this.nodeIsShow = l26;
    }

    getNodeIsShow() {
        return this.nodeIsShow;
    }

    getNodeItem() {
        return this.nodeItem;
    }

    getNodeStatus() {
        return this.status;
    }

    getNodeBorder() {
        return this.nodeBorder;
    }

    setNodeBorder(k26) {
        this.nodeBorder.borderWidth = k26 ? this.borderWidth.has : this.borderWidth.none;
    }

    getChildNodeInfo() {
        return this.childNodeInfo;
    }

    getCurrentNodeId() {
        return this.currentNodeId;
    }

    getMenu() {
        return this.container;
    }

    setIsSelected(j26) {
        this.isSelected = j26;
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

    setCanShowFlagLine(i26) {
        this.canShowFlagLine = i26;
    }

    getCanShowFlagLine() {
        return this.canShowFlagLine;
    }

    setFlagLineLeftMargin(h26) {
        if (h26 === undefined) {
            return;
        }
        this.flagLineLeftMargin = h26 * 12 + 8;
    }

    getFlagLineLeftMargin() {
        return this.flagLineLeftMargin;
    }

    getNodeLevel() {
        return this.nodeLevel;
    }

    setIsOverBorder(g26) {
        this.isOverBorder = g26;
    }

    getIsOverBorder() {
        return this.isOverBorder;
    }

    setCanShowBottomFlagLine(f26) {
        this.canShowBottomFlagLine = f26;
    }

    getCanShowBottomFlagLine() {
        return this.canShowBottomFlagLine;
    }

    setIsHighLight(e26) {
        this.isHighLight = e26;
    }

    getIsHighLight() {
        return this.isHighLight;
    }

    setIsModify(d26) {
        this.isModify = d26;
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
(function (c26) {
    c26['NODE_CLICK'] = 'NodeClick';
    c26['NODE_ADD'] = 'NodeAdd';
    c26['NODE_DELETE'] = 'NodeDelete';
    c26['NODE_MODIFY'] = 'NodeModify';
    c26['NODE_MOVE'] = 'NodeMove';
})(TreeListenType || (TreeListenType = {}));

export class TreeListener {
    constructor() {
        this._events = [];
        this._once_events = [];
    }

    on(y25, z25) {
        if (Array.isArray(y25)) {
            for (let a26 = 0, b26 = y25.length; a26 < b26; a26++) {
                this.on(y25[a26], z25);
            }
        }
        else {
            (this._events[y25] || (this._events[y25] = [])).push(z25);
        }
    }

    once(w25, x25) {
        if (Array.isArray(w25)) {
            this.off(w25, x25);
        }
        else {
            (this._once_events[w25] || (this._once_events[w25] = [])).push(x25);
        }
    }

    off(p25, q25) {
        if (p25 === null) {
            this._events = [];
        }
        if (Array.isArray(p25)) {
            for (let u25 = 0, v25 = p25.length; u25 < v25; u25++) {
                this.off(p25[u25], q25);
            }
        }
        let r25 = this._events[p25];
        if (!r25) {
            return;
        }
        if (q25 === null) {
            this._events[p25] = null;
        }
        let s25 = r25.length;
        while (s25--) {
            let t25 = r25[s25];
            if (t25 === q25) {
                r25.splice(s25, 1);
                break;
            }
        }
    }

    emit(f25, g25) {
        if (this._once_events[f25]) {
            let l25 = Array.from(this._once_events[f25]);
            if (l25) {
                for (let m25 = 0, n25 = l25.length; m25 < n25; m25++) {
                    try {
                        l25[m25](g25);
                    }
                    catch (o25) {
                        throw new Error('once function callbacks error.');
                    }
                }
                this._once_events[f25] = null;
            }
        }
        else if (this._events[f25]) {
            let h25 = Array.from(this._events[f25]);
            if (h25) {
                for (let i25 = 0, j25 = h25.length; i25 < j25; i25++) {
                    try {
                        h25[i25](g25);
                    }
                    catch (k25) {
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
    constructor(z24, a25, b25, c25 = -1, d25 = undefined, e25) {
        super(z24, b25, c25, e25);
        if (typeof d25 === 'function') {
            this.paramsGenerator_ = d25;
        }
        this.treeController = new TreeController();
        this.__nodeList = new ObservedPropertyObjectPU([], this, 'nodeList');
        this.listNodeDataSource = new ListNodeDataSource();
        this.__item = new ObservedPropertyObjectPU(null, this, 'item');
        this.__touchCount = new ObservedPropertySimplePU(0, this, 'touchCount');
        this.__dropSelectedIndex = new ObservedPropertySimplePU(0, this, 'dropSelectedIndex');
        this.__viewLastIndex = new ObservedPropertySimplePU(-1, this, 'viewLastIndex');
        this.__listItemBgColor = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_background_transparent'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        }, this, 'listItemBgColor');
        this.__treeViewTheme = new ObservedPropertyObjectPU(new TreeViewTheme(), this, 'treeViewTheme');
        this.addProvidedVar('treeViewTheme', this.__treeViewTheme, false);
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
            }
        };
        this.setInitiallyProvidedValue(a25);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(y24) {
        if (y24.treeController !== undefined) {
            this.treeController = y24.treeController;
        }
        if (y24.nodeList !== undefined) {
            this.nodeList = y24.nodeList;
        }
        if (y24.listNodeDataSource !== undefined) {
            this.listNodeDataSource = y24.listNodeDataSource;
        }
        if (y24.item !== undefined) {
            this.item = y24.item;
        }
        if (y24.touchCount !== undefined) {
            this.touchCount = y24.touchCount;
        }
        if (y24.dropSelectedIndex !== undefined) {
            this.dropSelectedIndex = y24.dropSelectedIndex;
        }
        if (y24.viewLastIndex !== undefined) {
            this.viewLastIndex = y24.viewLastIndex;
        }
        if (y24.listItemBgColor !== undefined) {
            this.listItemBgColor = y24.listItemBgColor;
        }
        if (y24.treeViewTheme !== undefined) {
            this.treeViewTheme = y24.treeViewTheme;
        }
        if (y24.listTreeViewMenu !== undefined) {
            this.listTreeViewMenu = y24.listTreeViewMenu;
        }
        if (y24.MAX_CN_LENGTH !== undefined) {
            this.MAX_CN_LENGTH = y24.MAX_CN_LENGTH;
        }
        if (y24.MAX_EN_LENGTH !== undefined) {
            this.MAX_EN_LENGTH = y24.MAX_EN_LENGTH;
        }
        if (y24.INITIAL_INVALID_VALUE !== undefined) {
            this.INITIAL_INVALID_VALUE = y24.INITIAL_INVALID_VALUE;
        }
        if (y24.MAX_TOUCH_DOWN_COUNT !== undefined) {
            this.MAX_TOUCH_DOWN_COUNT = y24.MAX_TOUCH_DOWN_COUNT;
        }
        if (y24.isMultiPress !== undefined) {
            this.isMultiPress = y24.isMultiPress;
        }
        if (y24.touchDownCount !== undefined) {
            this.touchDownCount = y24.touchDownCount;
        }
        if (y24.appEventBus !== undefined) {
            this.appEventBus = y24.appEventBus;
        }
        if (y24.itemPadding !== undefined) {
            this.itemPadding = y24.itemPadding;
        }
        if (y24.textInputPadding !== undefined) {
            this.textInputPadding = y24.textInputPadding;
        }
    }

    updateStateVars(x24) {
    }

    purgeVariableDependenciesOnElmtId(w24) {
        this.__nodeList.purgeDependencyOnElmtId(w24);
        this.__item.purgeDependencyOnElmtId(w24);
        this.__touchCount.purgeDependencyOnElmtId(w24);
        this.__dropSelectedIndex.purgeDependencyOnElmtId(w24);
        this.__viewLastIndex.purgeDependencyOnElmtId(w24);
        this.__listItemBgColor.purgeDependencyOnElmtId(w24);
        this.__treeViewTheme.purgeDependencyOnElmtId(w24);
    }

    aboutToBeDeleted() {
        this.__nodeList.aboutToBeDeleted();
        this.__item.aboutToBeDeleted();
        this.__touchCount.aboutToBeDeleted();
        this.__dropSelectedIndex.aboutToBeDeleted();
        this.__viewLastIndex.aboutToBeDeleted();
        this.__listItemBgColor.aboutToBeDeleted();
        this.__treeViewTheme.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get nodeList() {
        return this.__nodeList.get();
    }

    set nodeList(v24) {
        this.__nodeList.set(v24);
    }

    get item() {
        return this.__item.get();
    }

    set item(u24) {
        this.__item.set(u24);
    }

    get touchCount() {
        return this.__touchCount.get();
    }

    set touchCount(t24) {
        this.__touchCount.set(t24);
    }

    get dropSelectedIndex() {
        return this.__dropSelectedIndex.get();
    }

    set dropSelectedIndex(s24) {
        this.__dropSelectedIndex.set(s24);
    }

    get viewLastIndex() {
        return this.__viewLastIndex.get();
    }

    set viewLastIndex(r24) {
        this.__viewLastIndex.set(r24);
    }

    get listItemBgColor() {
        return this.__listItemBgColor.get();
    }

    set listItemBgColor(q24) {
        this.__listItemBgColor.set(q24);
    }

    get treeViewTheme() {
        return this.__treeViewTheme.get();
    }

    set treeViewTheme(p24) {
        this.__treeViewTheme.set(p24);
    }

    NullBuilder(o24 = null) {
    }

    onWillApplyTheme(n24) {
        this.treeViewTheme.itemSelectedBgColor = n24.colors.interactiveSelect;
        this.treeViewTheme.itemPressedBgColor = n24.colors.interactivePressed;
        this.treeViewTheme.itemHoverBgColor = n24.colors.interactiveHover;
        this.treeViewTheme.primaryTitleFontColor = n24.colors.fontPrimary;
        this.treeViewTheme.secondaryTitleFontColor = n24.colors.fontSecondary;
        this.treeViewTheme.primaryTitleActiveFontColor = n24.colors.interactiveActive;
        this.treeViewTheme.borderFocusedColor = n24.colors.interactiveFocus;
        this.treeViewTheme.leftIconColor = n24.colors.iconSecondary;
        this.treeViewTheme.leftIconActiveColor = n24.colors.interactiveActive;
        this.treeViewTheme.arrowIconColor = n24.colors.iconPrimary;
        this.treeController.treeViewTheme = this.treeViewTheme;
    }

    aboutToAppear() {
        if (this.treeController !== null) {
            this.listNodeDataSource = this.treeController.getListNodeDataSource();
            this.nodeList = this.treeController.getListNodeDataSource().listNode;
            this.item = this.treeController.getListNodeDataSource().listNode;
        }
    }

    popupForShowTitle(d24, e24, f24, g24 = null) {
        this.observeComponentCreation2((l24, m24) => {
            Row.create();
            Row.backgroundColor(e24);
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
        this.observeComponentCreation2((j24, k24) => {
            Text.create(d24);
            Text.fontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_body2'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            });
            Text.fontWeight('regular');
            Text.fontColor(f24);
        }, Text);
        Text.pop();
        Row.pop();
    }

    builder(c24 = null) {
        this.listTreeViewMenu.bind(this)(c24 ? c24 : this);
    }

    draggingPopup(b23, c23 = null) {
        this.observeComponentCreation2((a24, b24) => {
            Row.create();
            Row.constraintSize({
                minWidth: this.listNodeDataSource.getDragPopupPara().floorConstraintSize.minWidth,
                maxWidth: this.listNodeDataSource.getDragPopupPara().floorConstraintSize.maxWidth,
            });
            Row.height(this.listNodeDataSource.getDragPopupPara().height);
            Row.backgroundColor(this.listNodeDataSource.getDragPopupPara().backgroundColor);
            Row.padding({
                start: LengthMetrics.resource(this.listNodeDataSource.getDragPopupPara().padding.left),
                end: LengthMetrics.resource(this.listNodeDataSource.getDragPopupPara().padding.right)
            });
            Row.shadow({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_corner_radius_default_m'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                },
                color: SHADOW_COLOR,
                offsetY: 0,
            });
            Row.borderRadius(this.listNodeDataSource.getDragPopupPara().borderRadius);
        }, Row);
        this.observeComponentCreation2((q23, r23) => {
            If.create();
            if (b23.getNodeItem().imageNode) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((y23, z23) => {
                        Row.create();
                        Row.backgroundColor(this.treeViewTheme.arrowIconColor);
                        Row.margin({
                            end: getLengthMetricsByResourceOrNumber(b23.getNodeItem().imageNode?.itemRightMargin)
                        });
                        Row.height(b23.getNodeItem().imageNode?.itemHeight);
                        Row.width(b23.getNodeItem().imageNode?.itemWidth);
                    }, Row);
                    this.observeComponentCreation2((w23, x23) => {
                        Image.create(b23.getNodeItem().imageNode?.normalSource);
                        Image.objectFit(ImageFit.Contain);
                        Image.height(b23.getNodeItem().imageNode?.itemHeight);
                        Image.width(b23.getNodeItem().imageNode?.itemWidth);
                        Image.opacity(this.listNodeDataSource.getDragPopupPara().imageOpacity);
                        Image.matchTextDirection((b23.getNodeItem().imageCollapse?.collapseSource === ARROW_RIGHT || b23.getNodeItem()
                            .imageCollapse?.collapseSource === ARROW_RIGHT_WITHE) ? true : false);
                    }, Image);
                    Row.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((o23, p23) => {
            Row.create();
            Row.constraintSize({
                minWidth: b23.getNodeItem().imageNode ?
                this.listNodeDataSource.getDragPopupPara().textConstraintSize.minWidth1 :
                this.listNodeDataSource.getDragPopupPara().textConstraintSize.minWidth2,
                maxWidth: b23.getNodeItem().imageNode ?
                this.listNodeDataSource.getDragPopupPara().textConstraintSize.maxWidth1 :
                this.listNodeDataSource.getDragPopupPara().textConstraintSize.maxWidth2
            });
        }, Row);
        this.observeComponentCreation2((h23, i23) => {
            If.create();
            if (b23.getNodeItem().mainTitleNode && b23.getIsShowTitle()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((m23, n23) => {
                        Text.create(b23.getNodeItem().mainTitleNode?.title);
                        Text.maxLines(1);
                        Text.fontSize(b23.getNodeItem().mainTitleNode?.size);
                        Text.fontColor(this.listNodeDataSource.getDragPopupPara().fontColor);
                        Text.fontWeight(this.listNodeDataSource.getDragPopupPara().fontWeight);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                    }, Text);
                    Text.pop();
                });
            }
            else {
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
        this.setImageSources(this.viewLastIndex, InteractionStatus.Normal);
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
        this.listNodeDataSource.setImageSource(this.viewLastIndex, InteractionStatus.Normal);
    }

    setImageSources(y22, z22) {
        let a23 = this.nodeList[y22];
        a23.setIsSelected(z22 === InteractionStatus.Selected ||
            z22 === InteractionStatus.Edit || z22 === InteractionStatus.FinishEdit);
        if (a23.getNodeItem().mainTitleNode !== null && z22 !== InteractionStatus.DragInsert &&
            z22 !== InteractionStatus.FinishDragInsert) {
            a23.getNodeItem().mainTitleNode?.setMainTitleSelected(z22 === InteractionStatus.Selected ||
                z22 === InteractionStatus.FinishEdit);
        }
        if (a23.getNodeItem().imageNode !== null) {
            a23.getNodeItem().imageNode?.setImageSource(z22);
        }
    }

    initialRender() {
        this.observeComponentCreation2((m21, n21) => {
            List.create({});
            List.onDragMove((p22, q22) => {
                if (this.isMultiPress) {
                    console.error('drag error, a item has been dragged');
                    return;
                }
                let r22 = LIST_ITEM_HEIGHT;
                let s22 = Math.floor(p22.getY() / (r22 / FLAG_NUMBER)) % FLAG_NUMBER ? Flag.DOWN_FLAG : Flag.UP_FLAG;
                let t22 = JSON.parse(q22).insertIndex;
                let u22 = false;
                if (t22 >= this.listNodeDataSource.totalCount()) {
                    s22 = Flag.DOWN_FLAG;
                    t22 = this.listNodeDataSource.totalCount() - 1;
                    this.listNodeDataSource.getData(t22)?.setIsOverBorder(true);
                    u22 = true;
                }
                else {
                    this.listNodeDataSource.getData(t22)?.setIsOverBorder(false);
                }
                let v22 = this.listNodeDataSource.getData(t22);
                let w22 = v22?.getCurrentNodeId();
                if (t22 !== this.listNodeDataSource.getLastPassIndex() && this.listNodeDataSource.getIsInnerDrag()) {
                    let x22 = this.listNodeDataSource.getIsParentOfInsertNode(w22);
                    if (x22) {
                        this.listNodeDataSource.setPassIndex(t22);
                        if (w22 !== undefined) {
                            this.listNodeDataSource.clearTimeOutAboutDelayHighLightAndExpand(findCurrentNodeIndex(this.listNodeDataSource, w22));
                        }
                        this.listNodeDataSource.setFlag(Flag.NONE);
                        return;
                    }
                }
                this.listNodeDataSource.setLastPassIndex(t22);
                this.listNodeDataSource.setVisibility(s22, t22 - 1, u22);
                if (w22 !== undefined && w22 !== this.listNodeDataSource.getDraggingCurrentNodeId()) {
                    this.listNodeDataSource.delayHighLightAndExpandNode(findCurrentNodeIndex(this.listNodeDataSource, w22), w22, t22);
                }
            });
            List.onDragEnter((m22, n22) => {
                if (this.listNodeDataSource.getIsInnerDrag()) {
                    this.listNodeDataSource.setIsDrag(true);
                    let o22 = DRAG_OPACITY;
                    this.listNodeDataSource.setListItemOpacity(o22);
                }
            });
            List.onDragLeave((j22, k22) => {
                this.listNodeDataSource.hideLastLine();
                this.listNodeDataSource.clearLastTimeoutHighLight();
                this.listNodeDataSource.clearLastTimeoutExpand();
                let l22 = DRAG_OPACITY_NONE;
                this.listNodeDataSource.setListItemOpacity(l22);
                this.listNodeDataSource.setIsDrag(false);
                this.listNodeDataSource.notifyDataReload();
            });
            List.onDrop((s21, t21) => {
                this.listNodeDataSource.clearLastTimeoutExpand();
                let u21 = DRAG_OPACITY_NONE;
                this.listNodeDataSource.setListItemOpacity(u21);
                let v21 = JSON.parse(t21).insertIndex;
                let w21 = this.dropSelectedIndex;
                if (w21 - 1 > this.listNodeDataSource.totalCount() || w21 === undefined) {
                    console.error('drag error, currentNodeIndex is not found');
                    this.listNodeDataSource.setIsDrag(false);
                    return;
                }
                if (v21 === this.listNodeDataSource.totalCount()) {
                    console.log('need to insert into the position of the last line, now insertNodeIndex = insertNodeIndex - 1');
                    v21 -= 1;
                }
                let x21 = this.listNodeDataSource.getData(v21);
                if (x21 === undefined) {
                    return;
                }
                let y21 = x21.getNodeCurrentNodeId();
                if (!this.listNodeDataSource.getIsDrag() || !this.listNodeDataSource.getIsInnerDrag()) {
                    this.listNodeDataSource.clearLastTimeoutHighLight();
                    this.listNodeDataSource.setIsInnerDrag(false);
                    this.listNodeDataSource.hideLastLine();
                    this.listNodeDataSource.initialParameterAboutDelayHighLightAndExpandIndex();
                    this.listNodeDataSource.refreshSubtitle(y21);
                    this.listNodeDataSource.notifyDataReload();
                    return;
                }
                let z21 = this.listNodeDataSource.getCurrentNodeInfo();
                let a22 = x21.getNodeParentNodeId();
                let b22 = this.listNodeDataSource.getDraggingCurrentNodeId();
                let c22 = this.listNodeDataSource.getDraggingParentNodeId();
                let d22 = this.listNodeDataSource.getIsParentOfInsertNode(y21);
                if (d22) {
                    this.listNodeDataSource.clearLastTimeoutHighLight();
                    this.listNodeDataSource.setIsInnerDrag(false);
                    this.listNodeDataSource.hideLastLine();
                    this.listNodeDataSource.notifyDataChange(v21);
                    this.listNodeDataSource.initialParameterAboutDelayHighLightAndExpandIndex();
                    this.listNodeDataSource.setIsDrag(false);
                    let i22 = findCurrentNodeIndex(this.listNodeDataSource, b22);
                    this.listNodeDataSource.setClickIndex(i22);
                    this.listNodeDataSource.handleEvent(Event.DRAG, i22);
                    return;
                }
                if (this.listNodeDataSource.getExpandAndCollapseInfo(b22) === NodeStatus.Expand) {
                    this.listNodeDataSource.expandAndCollapseNode(findCurrentNodeIndex(this.listNodeDataSource, b22));
                }
                let e22 = false;
                if (this.listNodeDataSource.getExpandAndCollapseInfo(y21) === NodeStatus.Collapse) {
                    let h22 = findCurrentNodeIndex(this.listNodeDataSource, y21);
                    if (this.listNodeDataSource.ListNode[h22].getIsHighLight()) {
                        this.listNodeDataSource.expandAndCollapseNode(h22);
                    }
                    e22 = true;
                }
                this.listNodeDataSource.setLastDelayHighLightId();
                if (z21 !== null && b22 !== y21) {
                    this.listNodeDataSource.alterDragNode(a22, y21, c22, b22, z21);
                    this.listNodeDataSource.hideLastLine();
                }
                else {
                    this.listNodeDataSource.hideLastLine();
                    this.listNodeDataSource.setLastPassId(b22);
                    this.listNodeDataSource.hideLastLine();
                }
                let f22 = findCurrentNodeIndex(this.listNodeDataSource, this.listNodeDataSource.getLastDelayHighLightId());
                this.listNodeDataSource.setLastDelayHighLightIndex(f22);
                this.listNodeDataSource.clearLastTimeoutHighLight();
                this.listNodeDataSource.initialParameterAboutDelayHighLightAndExpandIndex();
                this.listNodeDataSource.setIsDrag(false);
                let g22 = findCurrentNodeIndex(this.listNodeDataSource, b22);
                this.listNodeDataSource.setClickIndex(g22);
                this.listNodeDataSource.handleEvent(Event.DRAG, g22);
                this.listNodeDataSource.setIsInnerDrag(false);
                this.listNodeDataSource.notifyDataReload();
                this.listNodeDataSource.listNode[g22].fontColor = this.treeViewTheme.primaryTitleActiveFontColor;
                if (this.viewLastIndex !== -1 && w21 !== this.viewLastIndex) {
                    this.listNodeDataSource.listNode[this.viewLastIndex].getNodeItem()
                        .mainTitleNode?.setMainTitleSelected(false);
                    this.listNodeDataSource.listNode[this.viewLastIndex].getNodeItem()
                        .mainTitleNode?.setMainTitleHighLight(false);
                }
                if (this.listNodeDataSource.listNode[this.viewLastIndex] !== null) {
                    this.listNodeDataSource.listNode[this.viewLastIndex].fontColor = this.treeViewTheme.primaryTitleFontColor;
                }
                this.listNodeDataSource.lastIndex = this.viewLastIndex;
                if (this.listNodeDataSource.listNode[this.viewLastIndex]) {
                    if (this.listNodeDataSource.listNode[this.viewLastIndex].getNodeItem()
                        .imageNode !== null) {
                        this.listNodeDataSource.listNode[this.viewLastIndex].getNodeItem()
                            .imageNode?.setImageSource(InteractionStatus.Normal);
                        this.listNodeDataSource.listNode[this.viewLastIndex].imageSource = this.listNodeDataSource.listNode[this.viewLastIndex].getNodeItem()
                            .imageNode?.source;
                    }
                }
                if (this.listNodeDataSource.listNode[this.viewLastIndex]) {
                    this.listNodeDataSource.listNode[this.viewLastIndex].setNodeColor({
                        'id': -1,
                        'type': 10001,
                        params: ['sys.color.ohos_id_color_background_transparent'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__',
                    });
                }
                this.listNodeDataSource.lastIndex = g22;
            });
        }, List);
        {
            const e20 = j20 => {
                const k20 = j20;
                {
                    const l20 = (c21, d21) => {
                        ListItem.create(() => {
                        }, false);
                        ListItem.width('100%');
                        ListItem.height(k20.getListItemHeight());
                        ListItem.padding({
                            start: LengthMetrics.resource(this.itemPadding.left),
                            end: LengthMetrics.resource(this.itemPadding.right)
                        });
                        ListItem.align(Alignment.Start);
                        ListItem.onDragStart((g21, h21) => {
                            if (this.listNodeDataSource.getIsDrag() || this.listNodeDataSource.getIsInnerDrag() || this.isMultiPress) {
                                console.error('drag error, a item has been dragged');
                                return;
                            }
                            this.dropSelectedIndex = JSON.parse(h21).selectedIndex;
                            let i21 = JSON.parse(h21).selectedIndex;
                            let j21 = this.listNodeDataSource.getData(i21);
                            let k21 = k20.getNodeCurrentNodeId();
                            if (i21 >= this.listNodeDataSource.totalCount() || i21 === undefined) {
                                console.error('drag error, currentNodeIndex is not found in onDragStart');
                                return;
                            }
                            this.listNodeDataSource.setIsInnerDrag(true);
                            this.listNodeDataSource.setIsDrag(true);
                            this.listNodeDataSource.setCurrentNodeInfo(j21);
                            this.listNodeDataSource.setDraggingCurrentNodeId(j21?.getNodeCurrentNodeId());
                            this.listNodeDataSource.setDraggingParentNodeId(j21?.getNodeParentNodeId());
                            let l21 = DRAG_OPACITY;
                            this.listNodeDataSource.setListItemOpacity(l21);
                            this.listNodeDataSource.notifyDataChange(i21);
                            if (k21 !== j21?.getNodeCurrentNodeId()) {
                                console.error('drag is too fast,it attribute a fault to OH');
                                this.listNodeDataSource.setIsDrag(false);
                                return;
                            }
                            return { builder: () => {
                                this.draggingPopup.call(this, j21);
                            } };
                        });
                    };
                    const m20 = () => {
                        this.observeComponentCreation2(l20, ListItem);
                        this.observeComponentCreation2((x20, y20) => {
                            Row.create();
                            Row.onTouch((a21) => {
                                this.viewLastIndex = this.listNodeDataSource.getLastIndex();
                                let b21 = this.listNodeDataSource.findIndex(k20.getNodeCurrentNodeId());
                                if (a21.type === TouchType.Down) {
                                    if (b21 !== this.viewLastIndex) {
                                        this.clearLastIndexColor();
                                        this.listNodeDataSource.lastIndex = b21;
                                        this.listNodeDataSource.setClickIndex(b21);
                                    }
                                }
                                if (a21.type === TouchType.Up) {
                                    this.listNodeDataSource.listNode[b21].setIsSelected(true);
                                    this.listNodeDataSource.setImageSource(b21, InteractionStatus.Selected);
                                    if (this.listNodeDataSource.listNode[b21].getNodeItem().imageNode !== null) {
                                        this.listNodeDataSource.listNode[b21].imageSource = this.listNodeDataSource.listNode[b21]
                                            .getNodeItem().imageNode?.source;
                                    }
                                    if (b21 !== this.viewLastIndex) {
                                        this.clearLastIndexColor();
                                        this.listNodeDataSource.lastIndex = b21;
                                        this.listNodeDataSource.setClickIndex(b21);
                                    }
                                    this.viewLastIndex = b21;
                                }
                                if (this.listNodeDataSource.getLastIndex() !== -1 && b21 !== this.listNodeDataSource.getLastIndex()) {
                                    this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false, this.listNodeDataSource.getLastIndex());
                                    this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(), MenuOperation.COMMIT_NODE);
                                }
                            });
                        }, Row);
                        {
                            this.observeComponentCreation2((r20, s20) => {
                                if (s20) {
                                    let t20 = new TreeViewInner(this, {
                                        item: k20,
                                        listNodeDataSource: this.listNodeDataSource,
                                        index: this.listNodeDataSource.findIndex(k20.getNodeCurrentNodeId()),
                                        listTreeViewMenu: this.listTreeViewMenu,
                                    }, undefined, r20, () => {
                                    }, {
                                        page: 'library/src/main/ets/components/mainpage/MainPage.ets',
                                        line: 1044,
                                        col: 13
                                    });
                                    ViewPU.create(t20);
                                    let u20 = () => {
                                        return {
                                            item: k20,
                                            listNodeDataSource: this.listNodeDataSource,
                                            index: this.listNodeDataSource.findIndex(k20.getNodeCurrentNodeId()),
                                            listTreeViewMenu: this.listTreeViewMenu
                                        };
                                    };
                                    t20.paramsGenerator_ = u20;
                                }
                                else {
                                    this.updateStateVarsOfChildByElmtId(r20, {
                                        item: k20
                                    });
                                }
                            }, { name: 'TreeViewInner' });
                        }
                        Row.pop();
                        ListItem.pop();
                    };
                    m20();
                }
            };
            const f20 = (i20) => JSON.stringify(i20);
            LazyForEach.create('1', this, this.listNodeDataSource, e20, f20);
            LazyForEach.pop();
        }
        List.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

function findCurrentNodeIndex(x19, y19) {
    let z19 = 0;
    x19.ListNode.forEach((b20, c20) => {
        if (b20.getNodeCurrentNodeId() === y19) {
            z19 = c20;
        }
    });
    return z19;
}

export class TreeController {
    constructor() {
        this.ROOT_NODE_ID = -1;
        this.nodeIdList = [];
        this.listNodeUtils = new ListNodeUtils();
        this.listNodeDataSource = new ListNodeDataSource();
        this.initBuild = true;
        this.treeViewTheme = new TreeViewTheme();
    }

    getListNodeDataSource() {
        return this.listNodeDataSource;
    }

    getClickNodeChildrenInfo() {
        let w19 = this.listNodeDataSource.getClickNodeId();
        return this.listNodeUtils.getClickNodeChildrenInfo(w19);
    }

    getChildrenId() {
        let v19 = this.listNodeDataSource.getClickNodeId();
        return this.listNodeUtils.getClickChildId(v19);
    }

    removeNode() {
        let s19 = this.listNodeDataSource.getClickNodeId();
        if (s19 < 0) {
            return;
        }
        let t19 = this.listNodeUtils.findParentNodeId(s19);
        let u19 = this.listNodeUtils.removeNode(s19, t19);
        this.listNodeDataSource.refreshData(this.listNodeUtils, MenuOperation.REMOVE_NODE, t19, u19);
        this.nodeIdList.splice(this.nodeIdList.indexOf(s19), 1);
    }

    modifyNode() {
        let r19 = this.listNodeDataSource.getClickNodeId();
        this.listNodeDataSource.setItemVisibilityOnEdit(r19, MenuOperation.MODIFY_NODE);
    }

    add() {
        let n19 = this.listNodeDataSource.getClickNodeId();
        if (n19 === this.listNodeDataSource.ROOT_NODE_ID || !this.listNodeDataSource.getIsFolder(n19)) {
            return;
        }
        let o19 = this.listNodeUtils.getNewNodeInfo(n19);
        this.nodeIdList.push(this.nodeIdList[this.nodeIdList.length - 1] + 1);
        let p19 = this.nodeIdList[this.nodeIdList.length - 1];
        this.listNodeUtils.addNewNodeId = p19;
        this.listNodeUtils.addNode(n19, p19, {
            isFolder: o19.isFolder,
            icon: o19.icon,
            selectedIcon: o19.selectedIcon,
            editIcon: o19.editIcon,
            primaryTitle: '新建文件夹',
            container: o19.container,
            secondaryTitle: o19.secondaryTitle,
        });
        this.listNodeDataSource.refreshData(this.listNodeUtils, MenuOperation.ADD_NODE, n19, [p19]);
        this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false, this.listNodeDataSource.getLastIndex());
        this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(), MenuOperation.COMMIT_NODE);
        this.listNodeDataSource.listNode[this.listNodeDataSource.getLastIndex()]
            .setFontColor(this.treeViewTheme.primaryTitleFontColor);
        let q19 = findCurrentNodeIndex(this.listNodeDataSource, p19);
        this.listNodeDataSource.setClickIndex(q19);
        this.listNodeDataSource.handleEvent(Event.TOUCH_UP, q19);
    }

    addNode(l19) {
        if (l19 === undefined) {
            this.add();
            return this;
        }
        else {
            if (l19.primaryTitle !== undefined &&
                !this.listNodeUtils.checkMainTitleIsValid(l19.primaryTitle.toString())) {
                throw new Error('ListTreeNode[addNode]: ' +
                    'The directory name cannot contain the following characters\ /: *? "< > | or exceeds the maximum length.');
                return this;
            }
            if (l19.primaryTitle === null && l19.icon === null) {
                throw new Error('ListTreeNode[addNode]: ' +
                    'The icon and directory name cannot be empty at the same time.');
                return this;
            }
            if (l19.currentNodeId === this.ROOT_NODE_ID || l19.currentNodeId === null) {
                throw new Error('ListTreeNode[addNode]: currentNodeId can not be -1 or null.');
                return this;
            }
            if (l19.currentNodeId !== undefined) {
                this.nodeIdList.push(l19.currentNodeId);
            }
            if (l19.parentNodeId !== undefined) {
                if (l19.currentNodeId !== undefined) {
                    this.listNodeUtils.addNode(l19.parentNodeId, l19.currentNodeId, l19);
                }
            }
            if (!this.initBuild && l19.parentNodeId !== undefined) {
                let m19 = this.nodeIdList[this.nodeIdList.length - 1];
                this.listNodeDataSource.refreshData(this.listNodeUtils, MenuOperation.ADD_NODE, l19.parentNodeId, [m19]);
            }
            return this;
        }
    }

    refreshNode(i19, j19, k19) {
        this.listNodeDataSource.setNodeSubtitlePara(i19, j19, k19);
    }

    buildDone() {
        this.listNodeDataSource.init(this.listNodeUtils);
        this.nodeIdList.sort((g19, h19) => g19 - h19);
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

    getData(e19) {
        return undefined;
    }

    registerDataChangeListener(d19) {
        if (this.listeners.indexOf(d19) < 0) {
            this.listeners.push(d19);
        }
    }

    unregisterDataChangeListener(b19) {
        const c19 = this.listeners.indexOf(b19);
        if (c19 >= 0) {
            this.listeners.splice(c19, 1);
        }
    }

    notifyDataReload() {
        this.listeners.forEach(a19 => {
            a19.onDataReloaded();
        });
    }

    notifyDataAdd(w18) {
        this.listeners.forEach(y18 => {
            y18.onDataAdd(w18);
        });
    }

    notifyDataChange(t18) {
        if (t18 === undefined) {
            return;
        }
        this.listeners.forEach(v18 => {
            v18.onDataChange(t18);
        });
    }

    notifyDataDelete(q18) {
        this.listeners.forEach(s18 => {
            s18.onDataDelete(q18);
        });
    }

    notifyDataMove(m18, n18) {
        this.listeners.forEach(p18 => {
            p18.onDataMove(m18, n18);
        });
    }
}

class ListNodeDataSource extends BasicDataSource {
    constructor() {
        super(...arguments);
        this.ROOT_NODE_ID = -1;
        this.listNodeUtils = new ListNodeUtils();
        this.listNode = [];
        this.INITIAL_INVALID_VALUE = -1;
        this.lastIndex = -1;
        this.thisIndex = -1;
        this.modifyNodeIndex = -1;
        this.modifyNodeId = -1;
        this.expandAndCollapseInfo = new Map();
        this.loadedNodeIdAndIndexMap = new Map();
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
        this.treeViewTheme = new TreeViewTheme();
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
                    params: ['sys.float.ohos_id_corner_radius_default_m'],
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
                params: ['sys.float.ohos_id_corner_radius_clicked'],
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
    }

    changeNodeColor(k18, l18) {
        this.listNode[k18].setNodeColor(l18);
        this.listNode[k18].setNodeBorder(false);
    }

    getNodeColor(j18) {
        return this.listNode[j18].getNodeColor();
    }

    handleFocusEffect(h18, i18) {
        if (this.listNode[h18].getNodeIsShow()) {
            this.listNode[h18].setNodeBorder(i18);
        }
    }

    setImageSource(e18, f18) {
        let g18 = this.listNode[e18];
        g18.setIsSelected(f18 === InteractionStatus.Selected ||
            f18 === InteractionStatus.Edit || f18 === InteractionStatus.FinishEdit);
        if (g18.getNodeItem().mainTitleNode !== null && f18 !== InteractionStatus.DragInsert &&
            f18 !== InteractionStatus.FinishDragInsert) {
            g18.getNodeItem().mainTitleNode?.setMainTitleSelected(f18 === InteractionStatus.Selected ||
                f18 === InteractionStatus.FinishEdit);
        }
        if (g18.getNodeItem().imageNode !== null) {
            g18.getNodeItem().imageNode?.setImageSource(f18);
        }
    }

    setImageCollapseSource(b18, c18) {
        let d18 = this.listNode[b18];
        if (d18.getNodeItem().imageCollapse !== undefined) {
            d18.getNodeItem().imageCollapse?.setImageCollapseSource(c18, this.expandAndCollapseInfo.get(d18.getCurrentNodeId()));
        }
    }

    clearLastIndexStatus() {
        if (this.lastIndex === -1 || this.lastIndex >= this.listNode.length) {
            return;
        }
        this.setImageSource(this.lastIndex, InteractionStatus.Normal);
        this.changeNodeColor(this.lastIndex, this.listNode[this.lastIndex].getNodeStatus().normal);
        this.handleFocusEffect(this.lastIndex, false);
        this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.listNode[this.lastIndex].getCurrentNodeId()));
    }

    changeNodeStatus(x17) {
        let y17 = x17;
        let z17 = this.ListNode;
        let a18 = z17[x17].getCurrentNodeId();
        if (this.expandAndCollapseInfo.get(a18) === NodeStatus.Expand) {
            this.expandAndCollapseInfo.set(a18, NodeStatus.Collapse);
            z17[y17].getNodeItem().imageCollapse?.changeImageCollapseSource(NodeStatus.Collapse);
        }
        else if (this.expandAndCollapseInfo.get(a18) === NodeStatus.Collapse) {
            this.expandAndCollapseInfo.set(a18, NodeStatus.Expand);
            z17[y17].getNodeItem().imageCollapse?.changeImageCollapseSource(NodeStatus.Expand);
        }
    }

    handleExpandAndCollapse(n17) {
        let o17 = n17;
        let p17 = this.ListNode;
        let q17 = p17[o17].getCurrentNodeId();
        if (!this.expandAndCollapseInfo.has(q17)) {
            return;
        }
        let r17 = this.expandAndCollapseInfo.get(q17);
        if (p17[o17].getChildNodeInfo().isHasChildNode && r17 === NodeStatus.Collapse) {
            for (let w17 = 0; w17 < p17[o17].getChildNodeInfo().allChildNum; w17++) {
                p17[o17 + 1 + w17].setNodeIsShow(false);
                p17[o17 + 1 + w17].setListItemHeight(LIST_ITEM_HEIGHT_NONE);
            }
            this.notifyDataReload();
            return;
        }
        let s17 = new Array(p17[o17].getChildNodeInfo().childNum);
        s17[0] = o17 + 1;
        let t17 = 1;
        while (t17 < p17[o17].getChildNodeInfo().childNum) {
            s17[t17] = s17[t17 - 1] + p17[s17[t17 - 1]].getChildNodeInfo().allChildNum + 1;
            t17++;
        }
        if (r17 === NodeStatus.Expand) {
            for (let u17 = 0; u17 < s17.length; u17++) {
                p17[s17[u17]].setNodeIsShow(true);
                p17[s17[u17]].setListItemHeight(LIST_ITEM_HEIGHT);
                let v17 = p17[s17[u17]].getCurrentNodeId();
                if (this.expandAndCollapseInfo.get(v17) === NodeStatus.Expand) {
                    this.handleExpandAndCollapse(s17[u17]);
                }
            }
        }
        s17 = null;
        this.notifyDataReload();
    }

    init(i17) {
        let j17 = 0;
        this.listNode = [];
        this.listNodeUtils = i17;
        this.loadedNodeIdAndIndexMap.clear();
        this.listNodeUtils.traverseNodeDF((l17) => {
            if (l17.currentNodeId >= 0) {
                let m17 = new NodeInfo(l17);
                this.listNode.push(m17);
                if (m17.getChildNodeInfo().isHasChildNode) {
                    this.expandAndCollapseInfo.set(m17.getCurrentNodeId(), NodeStatus.Collapse);
                }
                if (m17.getNodeIsShow()) {
                    this.loadedNodeIdAndIndexMap.set(m17.getCurrentNodeId(), j17++);
                }
                if (m17.getIsFolder()) {
                    if (m17.getNodeInfoData().secondaryTitle !== undefined) {
                        this.nodeIdAndSubtitleMap.set(m17.getCurrentNodeId(), m17.getNodeInfoData().secondaryTitle);
                    }
                    else {
                        this.nodeIdAndSubtitleMap.set(m17.getCurrentNodeId(), '');
                    }
                }
            }
            return false;
        });
    }

    refreshRemoveNodeData(w16, x16) {
        let y16 = [];
        for (let e17 = 0; e17 < w16.length; e17++) {
            for (let f17 = 0; f17 < this.listNode.length; f17++) {
                if (this.listNode[f17].getNodeCurrentNodeId() === w16[e17]) {
                    let g17 = this.listNode[f17].getNodeCurrentNodeId();
                    if (this.loadedNodeIdAndIndexMap.has(g17)) {
                        y16.push(this.loadedNodeIdAndIndexMap.get(g17));
                    }
                    let h17 = this.listNode.splice(f17, 1);
                    h17 = null;
                    if (this.expandAndCollapseInfo.has(w16[e17])) {
                        this.expandAndCollapseInfo.delete(w16[e17]);
                    }
                    break;
                }
            }
        }
        y16.forEach((d17) => {
            this.notifyDataDelete(d17);
            this.notifyDataChange(d17);
        });
        let z16 = 0;
        for (let c17 = 0; c17 < this.listNode.length; c17++) {
            if (this.listNode[c17].getNodeCurrentNodeId() === x16.getNodeCurrentNodeId()) {
                if (x16.getNodeItem().imageCollapse === null) {
                    this.listNode[c17].handleImageCollapseAfterAddNode(false);
                    this.expandAndCollapseInfo.delete(x16.getNodeCurrentNodeId());
                    this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.listNode[c17].getNodeCurrentNodeId()));
                }
                break;
            }
        }
        let a17 = {
            currentNodeId: x16.getNodeCurrentNodeId(),
            parentNodeId: x16.getNodeParentNodeId(),
        };
        this.appEventBus.emit(TreeListenType.NODE_DELETE, a17);
    }

    refreshAddNodeData(q16) {
        let r16 = new NodeInfo(new NodeItem(emptyNodeInfo));
        this.listNodeUtils.traverseNodeDF((v16) => {
            if (v16.currentNodeId === q16[0]) {
                r16 = new NodeInfo(v16);
                return true;
            }
            return false;
        });
        r16.setIsModify(true);
        let s16 = 0;
        for (let u16 = 0; u16 < this.listNode.length; u16++) {
            if (this.listNode[u16].getNodeCurrentNodeId() === r16.getNodeParentNodeId()) {
                s16 = u16;
                if (this.listNode[u16].getNodeItem().imageCollapse === null) {
                    this.listNode[u16].handleImageCollapseAfterAddNode(true);
                    this.notifyDataChange(s16);
                }
                else if (this.expandAndCollapseInfo.get(this.listNode[u16].getNodeCurrentNodeId()) === NodeStatus.Collapse) {
                    this.changeNodeStatus(s16);
                }
                this.listNode.splice(u16 + 1, 0, r16);
                this.listNode[u16 + 1].setTitleAndInputTextStatus(true);
                this.listNode[u16 + 1].setNodeIsShow(true);
                this.listNode[u16 + 1].setListItemHeight(LIST_ITEM_HEIGHT);
                this.setImageSource(u16 + 1, InteractionStatus.Edit);
                this.currentOperation = MenuOperation.ADD_NODE;
                this.notifyDataAdd(u16 + 1);
                this.notificationNodeInfo(u16 + 1, this.currentOperation);
                break;
            }
        }
        this.modifyNodeIndex = s16 + 1;
        this.setClickIndex(s16);
        this.lastIndex = s16;
        this.expandAndCollapseInfo.set(r16.getNodeParentNodeId(), NodeStatus.Expand);
        this.handleExpandAndCollapse(s16);
    }

    refreshData(j16, k16, l16, m16) {
        let n16 = new NodeInfo(new NodeItem(emptyNodeInfo));
        this.listNodeUtils = j16;
        this.listNodeUtils.traverseNodeDF((p16) => {
            if (p16.currentNodeId === l16) {
                n16 = new NodeInfo(p16);
                return true;
            }
            return false;
        });
        if (k16 === MenuOperation.REMOVE_NODE) {
            this.nodeIdAndSubtitleMap.set(l16, this.selectedParentNodeSubtitle);
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(l16));
            this.refreshRemoveNodeData(m16, n16);
        }
        if (k16 === MenuOperation.ADD_NODE) {
            this.addFocusNodeId = m16[0];
            this.nodeIdAndSubtitleMap.set(this.getClickNodeId(), this.selectedParentNodeSubtitle);
            this.nodeIdAndSubtitleMap.set(m16[0], this.insertNodeSubtitle);
            this.refreshAddNodeData(m16);
        }
    }

    setClickIndex(i16) {
        this.thisIndex = i16;
    }

    getClickNodeId() {
        if (this.thisIndex < 0 || this.thisIndex >= this.ListNode.length) {
            return -1;
        }
        return this.ListNode[this.thisIndex].getCurrentNodeId();
    }

    expandAndCollapseNode(h16) {
        this.changeNodeStatus(h16);
        this.handleExpandAndCollapse(h16);
    }

    getIsTouchDown() {
        return this.isTouchDown;
    }

    getLastIndex() {
        return this.lastIndex;
    }

    findIndex(c16) {
        let d16 = -1;
        this.ListNode.forEach((f16, g16) => {
            if (f16.getNodeCurrentNodeId() === c16) {
                d16 = g16;
            }
        });
        return d16;
    }

    handleEventDrag(b16) {
        this.setImageSource(b16, InteractionStatus.Normal);
        this.changeNodeColor(b16, this.listNode[b16].getNodeStatus().normal);
        this.handleFocusEffect(b16, false);
        this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.listNode[b16].getCurrentNodeId()));
    }

    handleEvent(w15, x15) {
        if (this.isDrag) {
            return;
        }
        if (w15 === Event.TOUCH_DOWN || w15 === Event.TOUCH_UP || w15 === Event.MOUSE_BUTTON_RIGHT) {
            if (x15 !== this.lastIndex) {
                this.clearLastIndexStatus();
            }
        }
        let y15 = this.loadedNodeIdAndIndexMap.get(this.listNode[x15].getCurrentNodeId());
        switch (w15) {
            case Event.TOUCH_DOWN:
                this.isTouchDown = true;
                this.changeNodeColor(x15, this.listNode[x15].getNodeStatus().press);
                this.notifyDataChange(y15);
                break;
            case Event.TOUCH_UP: {
                if (this.isInnerDrag) {
                    this.isInnerDrag = false;
                }
                this.isTouchDown = false;
                let a16 = this.listNode[x15];
                this.setImageSource(x15, InteractionStatus.Selected);
                a16.setFontColor(this.treeViewTheme.primaryTitleFontColor);
                this.lastIndex = x15;
                this.changeNodeColor(x15, a16.getNodeStatus().selected);
                this.notifyDataChange(y15);
                break;
            }
            case Event.HOVER:
                if (this.getNodeColor(x15) !== this.listNode[x15].getNodeStatus().selected) {
                    this.changeNodeColor(x15, this.listNode[x15].getNodeStatus().hover);
                    this.notifyDataChange(y15);
                }
                break;
            case Event.HOVER_OVER:
                if (this.getNodeColor(x15) !== this.listNode[x15].getNodeStatus().selected) {
                    this.changeNodeColor(x15, this.listNode[x15].getNodeStatus().normal);
                    this.notifyDataChange(y15);
                }
                break;
            case Event.FOCUS:
                this.handleFocusEffect(x15, true);
                this.notifyDataChange(y15);
                break;
            case Event.BLUR:
                this.handleFocusEffect(x15, false);
                this.notifyDataChange(y15);
                break;
            case Event.MOUSE_BUTTON_RIGHT:
                this.lastIndex = x15;
                this.finishEditing();
                break;
            case Event.DRAG:
                this.isTouchDown = false;
                let z15 = this.listNode[x15];
                this.setImageSource(x15, InteractionStatus.Selected);
                this.lastIndex = x15;
                this.changeNodeColor(x15, z15.getNodeStatus().selected);
                this.notifyDataChange(y15);
                break;
            default:
                break;
        }
    }

    notificationNodeInfo(n15, o15) {
        if (o15 === MenuOperation.MODIFY_NODE) {
            let u15 = this.listNode[this.modifyNodeIndex];
            let v15 = {
                currentNodeId: u15.getNodeCurrentNodeId(),
                parentNodeId: u15.getNodeParentNodeId(),
            };
            this.appEventBus.emit(TreeListenType.NODE_MODIFY, v15);
        }
        else if (o15 === MenuOperation.ADD_NODE) {
            let p15 = this.listNode[n15];
            let q15 = (p15.getNodeItem().imageNode !== undefined) ?
                p15.getNodeItem().imageNode?.source : undefined;
            let r15 = (p15.getNodeItem().imageNode !== undefined) ?
                p15.getNodeItem().imageNode?.selectedSource : undefined;
            let s15 = (p15.getNodeItem().imageNode !== undefined) ?
                p15.getNodeItem().imageNode?.editSource : undefined;
            let t15 = {
                currentNodeId: p15.getNodeCurrentNodeId(),
                parentNodeId: p15.getNodeParentNodeId(),
            };
            this.appEventBus.emit(TreeListenType.NODE_ADD, t15);
        }
    }

    finishEditing() {
        if (this.modifyNodeIndex !== -1) {
            this.setImageSource(this.modifyNodeIndex, InteractionStatus.FinishEdit);
            this.setImageCollapseSource(this.modifyNodeIndex, InteractionStatus.FinishEdit);
            this.listNode[this.modifyNodeIndex].setIsModify(false);
            this.listNode[this.modifyNodeIndex].setTitleAndInputTextStatus(false);
            this.notificationNodeInfo(this.modifyNodeIndex, this.currentOperation);
            this.notifyDataChange(this.modifyNodeIndex);
        }
    }

    setItemVisibilityOnEdit(h15, i15) {
        let j15 = -1;
        if (h15 === -1) {
            return;
        }
        if (i15 === MenuOperation.MODIFY_NODE) {
            for (let m15 = 0; m15 < this.listNode.length; m15++) {
                if (this.listNode[m15].getCurrentNodeId() === h15) {
                    j15 = m15;
                    break;
                }
            }
            let l15 = this.listNode[j15];
            l15.setIsModify(true);
            if (l15.getNodeItem().mainTitleNode === null) {
                return;
            }
            this.currentOperation = MenuOperation.MODIFY_NODE;
            l15.setTitleAndInputTextStatus(true);
            this.setImageSource(j15, InteractionStatus.Edit);
            this.setImageCollapseSource(j15, InteractionStatus.Edit);
            this.modifyNodeIndex = j15;
            if (l15.getNodeItem().inputText) {
                if (l15.getNodeItem().imageCollapse !== null) {
                    l15.getNodeItem().inputText.rightMargin = {
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.ohos_id_text_paragraph_margin_xs'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__',
                    };
                }
                else {
                    l15.getNodeItem().inputText.rightMargin = {
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.ohos_id_elements_margin_horizontal_m'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__',
                    };
                }
            }
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(h15));
        }
        j15 = h15;
        if (i15 === MenuOperation.COMMIT_NODE) {
            let k15 = this.listNode[j15];
            k15.setTitleAndInputTextStatus(false);
            k15.setIsModify(false);
            this.setImageSource(j15, InteractionStatus.FinishEdit);
            this.setImageCollapseSource(j15, InteractionStatus.FinishEdit);
            this.notificationNodeInfo(this.modifyNodeIndex, this.currentOperation);
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(k15.getCurrentNodeId()));
        }
    }

    setPopUpInfo(b15, c15, d15, e15) {
        let f15 = this.listNode[e15];
        f15.setPopUpIsShow(d15);
        let g15 = this.loadedNodeIdAndIndexMap.get(f15.getCurrentNodeId());
        if (!d15) {
            this.notifyDataChange(g15);
            return;
        }
        if (b15 === PopUpType.HINTS) {
            if (f15.getNodeItem().mainTitleNode !== null) {
                f15.setPopUpText(f15.getNodeItem().mainTitleNode?.title);
            }
            else {
                f15.setPopUpText('');
                f15.setPopUpIsShow(false);
            }
            f15.setPopUpEnableArrow(false);
            f15.setPopUpColor({
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_background'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            });
            f15.setPopUpTextColor({
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_text_secondary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            });
        }
        else if (b15 === PopUpType.WARNINGS) {
            if (f15.getNodeItem().inputText !== null) {
                if (c15 === InputError.INVALID_ERROR) {
                    f15.setPopUpText('invalid error');
                }
                else if (c15 === InputError.LENGTH_ERROR) {
                    f15.setPopUpText('length error');
                }
                f15.setPopUpEnableArrow(true);
                f15.setPopUpColor({
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_help_tip_bg'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                });
                f15.setPopUpTextColor({
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_text_hint_contrary'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                });
            }
        }
        this.notifyDataChange(g15);
    }

    setShowPopUpTimeout(y14, z14) {
        if (this.listNode[z14].getNodeItem().mainTitleNode !== null) {
            this.listNode[z14].getNodeItem().mainTitleNode.popUpTimeout = y14;
        }
        let a15 = this.loadedNodeIdAndIndexMap.get(this.listNode[z14].getCurrentNodeId());
        this.notifyDataChange(a15);
    }

    setMainTitleNameOnEdit(w14, x14) {
        this.modifyNodeIndex = w14;
        if (this.listNode[w14].getNodeItem().mainTitleNode !== null) {
            this.listNode[w14].getNodeItem().mainTitleNode.title = x14;
        }
    }

    get ListNode() {
        return this.listNode;
    }

    totalCount() {
        let t14 = 0;
        let u14 = 0;
        this.loadedNodeIdAndIndexMap.clear();
        for (let v14 = 0; v14 < this.listNode.length; v14++) {
            if (this.listNode[v14].getNodeIsShow()) {
                this.loadedNodeIdAndIndexMap.set(this.listNode[v14].getCurrentNodeId(), u14++);
                t14++;
            }
        }
        return t14;
    }

    getData(q14) {
        let r14 = 0;
        for (let s14 = 0; s14 < this.listNode.length; s14++) {
            if (this.listNode[s14].getNodeIsShow()) {
                if (q14 === r14) {
                    return this.listNode[s14];
                }
                r14++;
            }
        }
        return undefined;
    }

    addData(o14, p14) {
        this.listNode.splice(o14, 0, p14);
        this.notifyDataAdd(o14);
    }

    pushData(n14) {
        this.listNode.push(n14);
        this.notifyDataAdd(this.listNode.length - 1);
    }

    setIsInnerDrag(m14) {
        this.isInnerDrag = m14;
    }

    getIsInnerDrag() {
        return this.isInnerDrag;
    }

    setIsDrag(l14) {
        this.isDrag = l14;
    }

    getIsDrag() {
        return this.isDrag;
    }

    setCurrentNodeInfo(k14) {
        if (k14 === undefined) {
            return;
        }
        this.currentNodeInfo = k14;
    }

    getCurrentNodeInfo() {
        return this.currentNodeInfo;
    }

    setDraggingParentNodeId(j14) {
        if (j14 === undefined) {
            return;
        }
        this.draggingParentNodeId = j14;
    }

    getDraggingParentNodeId() {
        return this.draggingParentNodeId;
    }

    getDraggingCurrentNodeId() {
        return this.draggingCurrentNodeId;
    }

    setDraggingCurrentNodeId(i14) {
        if (i14 === undefined) {
            return;
        }
        this.draggingCurrentNodeId = i14;
    }

    setListItemOpacity(h14) {
        this.listItemOpacity = h14;
    }

    getListItemOpacity(g14) {
        return g14.getCurrentNodeId() === this.getDraggingCurrentNodeId() ? this.listItemOpacity : 1;
    }

    getDragPopupPara() {
        return this.DRAG_POPUP;
    }

    setLastPassIndex(f14) {
        this.lastPassIndex = f14;
    }

    getLastPassIndex() {
        return this.lastPassIndex;
    }

    getIsParentOfInsertNode(z13) {
        if (this.currentNodeInfo === null || z13 === undefined) {
            return false;
        }
        let a14 = this.currentNodeInfo.getNodeInfoNode();
        let b14 = false;
        let c14 = (e14) => {
            if (e14.currentNodeId === z13) {
                b14 = true;
                return true;
            }
            return false;
        };
        this.listNodeUtils.traverseNodeDF(c14, a14);
        return b14;
    }

    setPassIndex(y13) {
        this.thisPassIndex = y13;
    }

    getPassIndex() {
        return this.thisPassIndex;
    }

    clearTimeOutAboutDelayHighLightAndExpand(t13) {
        if (this.lastPassId !== this.INITIAL_INVALID_VALUE && this.loadedNodeIdAndIndexMap.has(this.lastPassId)) {
            let v13 = this.loadedNodeIdAndIndexMap.get(this.lastPassId);
            this.ListNode.forEach((x13) => {
                if (x13.getNodeCurrentNodeId() === this.lastPassId) {
                    x13.setCanShowFlagLine(false);
                }
            });
            this.notifyDataChange(v13);
        }
        if ((this.lastTimeoutHighLightId !== this.INITIAL_INVALID_VALUE &&
            this.clearTimeoutHighLightId !== this.lastTimeoutHighLightId)) {
            clearTimeout(this.lastTimeoutHighLightId);
            if (this.lastDelayHighLightIndex !== this.INITIAL_INVALID_VALUE) {
                this.clearHighLight(this.lastDelayHighLightIndex);
                let u13 = this.loadedNodeIdAndIndexMap
                    .get(this.listNode[this.lastDelayHighLightIndex].getCurrentNodeId());
                this.notifyDataChange(u13);
            }
            this.clearTimeoutHighLightId = this.lastTimeoutHighLightId;
        }
        this.lastTimeoutHighLightId = this.timeoutHighLightId;
        this.lastDelayHighLightIndex = t13;
        if ((this.lastTimeoutExpandId !== this.INITIAL_INVALID_VALUE &&
            this.clearTimeoutExpandId !== this.lastTimeoutExpandId)) {
            clearTimeout(this.lastTimeoutExpandId);
            this.clearTimeoutExpandId = this.lastTimeoutExpandId;
        }
        this.lastTimeoutExpandId = this.timeoutExpandId;
        this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE;
    }

    clearHighLight(s13) {
        this.changeNodeColor(s13, this.listNode[s13].getNodeStatus().normal);
        this.changeNodeHighLightColor(s13, false);
        this.setImageSource(s13, InteractionStatus.FinishDragInsert);
        this.setImageCollapseSource(s13, InteractionStatus.FinishDragInsert);
        this.listNode[s13].setIsHighLight(false);
    }

    changeNodeHighLightColor(q13, r13) {
        if (this.listNode[q13].getNodeItem().mainTitleNode && this.listNode[q13].getIsShowTitle()) {
            this.listNode[q13].getNodeItem().mainTitleNode?.setMainTitleHighLight(r13);
        }
    }

    setVisibility(h13, i13, j13) {
        let k13 = (this.thisPassIndex !== i13 || this.flag !== h13) ? true : false;
        this.thisPassIndex = i13;
        if ((k13 || j13) && this.isInnerDrag) {
            this.flag = h13;
            let l13 = this.getData(i13)?.getCurrentNodeId();
            let m13 = this.getData(i13)?.getNodeLevel();
            if (l13 !== undefined) {
                m13 = (this.expandAndCollapseInfo.get(l13) === NodeStatus.Expand &&
                    this.flag === Flag.DOWN_FLAG) ? (m13 ? m13 + 1 : undefined) : m13;
                if (this.lastPassId !== this.INITIAL_INVALID_VALUE && this.loadedNodeIdAndIndexMap.has(this.lastPassId)) {
                    let n13 = this.loadedNodeIdAndIndexMap.get(this.lastPassId);
                    this.ListNode.forEach((p13) => {
                        if (p13.getNodeCurrentNodeId() === this.lastPassId) {
                            p13.setCanShowFlagLine(false);
                        }
                    });
                    this.notifyDataChange(n13);
                }
                if (this.flag === Flag.DOWN_FLAG && i13 < this.totalCount() - 1) {
                    this.getData(i13)?.setCanShowFlagLine(false);
                    this.getData(i13 + 1)?.setCanShowFlagLine(true);
                    this.getData(i13)?.setCanShowBottomFlagLine(false);
                    this.getData(i13 + 1)?.setFlagLineLeftMargin(m13);
                    this.notifyDataChange(i13);
                    this.notifyDataChange(i13 + 1);
                    this.lastPassId = this.getData(i13 + 1)?.getNodeCurrentNodeId();
                }
                else if (this.flag === Flag.UP_FLAG && i13 < this.totalCount() - 1) {
                    this.getData(i13)?.setCanShowFlagLine(true);
                    this.getData(i13 + 1)?.setCanShowFlagLine(false);
                    this.getData(i13)?.setCanShowBottomFlagLine(false);
                    this.getData(i13)?.setFlagLineLeftMargin(m13);
                    this.notifyDataChange(i13);
                    this.notifyDataChange(i13 + 1);
                    this.lastPassId = this.getData(i13)?.getNodeCurrentNodeId();
                }
                else if (i13 >= this.totalCount() - 1) {
                    if (this.flag === Flag.DOWN_FLAG) {
                        this.getData(i13)?.setCanShowFlagLine(false);
                        this.getData(i13)?.setCanShowBottomFlagLine(true);
                    }
                    else {
                        this.getData(i13)?.setCanShowFlagLine(true);
                        this.getData(i13)?.setCanShowBottomFlagLine(false);
                    }
                    this.getData(i13)?.setFlagLineLeftMargin(m13);
                    this.notifyDataChange(i13);
                    this.lastPassId = this.getData(i13)?.getNodeCurrentNodeId();
                }
            }
        }
    }

    delayHighLightAndExpandNode(w12, x12, y12) {
        let z12 = w12 !== this.lastDelayExpandIndex ? true : false;
        let a13 = this.getData(y12)?.getIsOverBorder();
        if (a13) {
            this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE;
        }
        else {
            this.lastDelayExpandIndex = w12;
        }
        if (a13 || z12) {
            let b13 = !a13 && (!this.isInnerDrag ||
                (this.expandAndCollapseInfo.get(x12) === NodeStatus.Collapse && this.isInnerDrag) ||
                (!this.expandAndCollapseInfo.has(x12) && this.listNode[w12].getIsFolder()));
            if (b13) {
                this.changeNodeColor(w12, this.listNode[w12].getNodeStatus().hover);
                this.notifyDataChange(y12);
                let f13 = this.isInnerDrag ? 1000 : 0;
                this.timeoutHighLightId = setTimeout(() => {
                    this.delayHighLight(w12);
                }, f13);
            }
            if (a13 || (this.lastTimeoutHighLightId !== this.INITIAL_INVALID_VALUE &&
                this.clearTimeoutHighLightId !== this.lastTimeoutHighLightId)) {
                clearTimeout(this.lastTimeoutHighLightId);
                if (this.lastDelayHighLightIndex !== this.INITIAL_INVALID_VALUE) {
                    this.clearHighLight(this.lastDelayHighLightIndex);
                    this.notifyDataReload();
                }
                this.clearTimeoutHighLightId = this.lastTimeoutHighLightId;
            }
            this.lastTimeoutHighLightId = this.timeoutHighLightId;
            this.lastDelayHighLightIndex = w12;
            if (!a13 && this.expandAndCollapseInfo.get(x12) === NodeStatus.Collapse) {
                let c13 = this.getData(y12)?.getNodeInfoNode().children[0].currentNodeId;
                let d13 = 2000;
                this.timeoutExpandId = setTimeout(() => {
                    this.clearHighLight(this.lastDelayHighLightIndex);
                    if (c13 !== undefined) {
                        this.alterFlagLineAndExpandNode(w12, c13);
                    }
                }, d13);
            }
            if (a13 || (this.lastTimeoutExpandId !== this.INITIAL_INVALID_VALUE &&
                this.clearTimeoutExpandId !== this.lastTimeoutExpandId)) {
                clearTimeout(this.lastTimeoutExpandId);
                this.clearTimeoutExpandId = this.lastTimeoutExpandId;
            }
            this.lastTimeoutExpandId = this.timeoutExpandId;
        }
    }

    delayHighLight(t12) {
        this.ListNode.forEach((v12) => {
            if (v12.getNodeCurrentNodeId() === this.lastPassId) {
                v12.setCanShowFlagLine(false);
                v12.setCanShowBottomFlagLine(false);
            }
        });
        this.changeNodeColor(t12, this.listNode[t12].getNodeStatus().highLight);
        this.listNode[t12].setIsHighLight(true);
        this.changeNodeHighLightColor(t12, true);
        this.setImageSource(t12, InteractionStatus.DragInsert);
        this.setImageCollapseSource(t12, InteractionStatus.DragInsert);
        this.notifyDataReload();
    }

    alterFlagLineAndExpandNode(n12, o12) {
        this.ListNode.forEach((s12) => {
            if (s12.getNodeCurrentNodeId() === this.lastPassId) {
                s12.setCanShowFlagLine(false);
                s12.setCanShowBottomFlagLine(false);
            }
        });
        this.ListNode.forEach((r12) => {
            if (this.isInnerDrag && r12.getNodeCurrentNodeId() === o12) {
                r12.setCanShowFlagLine(true);
            }
        });
        this.changeNodeStatus(n12);
        this.handleExpandAndCollapse(n12);
        this.lastPassId = o12;
    }

    hideLastLine() {
        if (this.lastPassId !== this.INITIAL_INVALID_VALUE && this.loadedNodeIdAndIndexMap.has(this.lastPassId)) {
            this.ListNode.forEach((m12) => {
                if (m12.getNodeCurrentNodeId() === this.lastPassId) {
                    m12.setCanShowFlagLine(false);
                    m12.setCanShowBottomFlagLine(false);
                }
            });
            let k12 = this.loadedNodeIdAndIndexMap.get(this.lastPassId);
            this.notifyDataChange(k12);
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

    getSubtitle(j12) {
        if (this.nodeIdAndSubtitleMap.has(j12)) {
            if (typeof this.nodeIdAndSubtitleMap.get(j12) === 'number') {
                return this.nodeIdAndSubtitleMap.get(j12)?.toString();
            }
            else {
                return this.nodeIdAndSubtitleMap.get(j12);
            }
        }
        else {
            return '';
        }
    }

    hasSubtitle(i12) {
        return this.nodeIdAndSubtitleMap.has(i12);
    }

    initialParameterAboutDelayHighLightAndExpandIndex() {
        this.lastDelayHighLightIndex = this.INITIAL_INVALID_VALUE;
        this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE;
        this.lastPassIndex = this.INITIAL_INVALID_VALUE;
        this.draggingCurrentNodeId = this.INITIAL_INVALID_VALUE;
        this.flag = Flag.NONE;
    }

    refreshSubtitle(h12) {
        this.nodeIdAndSubtitleMap.set(this.selectedParentNodeId, this.selectedParentNodeSubtitle);
        this.nodeIdAndSubtitleMap.set(h12, this.insertNodeSubtitle);
        this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.selectedParentNodeId));
        this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(h12));
    }

    setNodeSubtitlePara(e12, f12, g12) {
        this.selectedParentNodeId = e12;
        this.selectedParentNodeSubtitle = f12;
        this.insertNodeSubtitle = g12;
    }

    getInsertNodeSubtitle() {
        return this.insertNodeSubtitle;
    }

    getExpandAndCollapseInfo(d12) {
        return this.expandAndCollapseInfo.get(d12);
    }

    getLastDelayHighLightId() {
        return this.lastDelayHighLightId;
    }

    setLastDelayHighLightId() {
        this.ListNode.forEach((b12, c12) => {
            if (c12 === this.lastDelayHighLightIndex) {
                this.lastDelayHighLightId = b12.getCurrentNodeId();
            }
        });
    }

    setLastPassId(z11) {
        this.lastPassId = z11;
    }

    setLastDelayHighLightIndex(y11) {
        this.lastDelayHighLightIndex = y11;
    }

    alterDragNode(t10, u10, v10, w10, x10) {
        let y10 = [];
        let z10 = t10;
        let a11 = w10;
        let b11 = x10.getNodeInfoData();
        let c11 = null;
        let d11 = x10.getNodeInfoNode();
        let e11 = false;
        let f11 = this.INITIAL_INVALID_VALUE;
        let g11 = this.INITIAL_INVALID_VALUE;
        let h11 = this.flag === Flag.DOWN_FLAG ? true : false;
        g11 = this.getChildIndex(v10, w10);
        f11 = this.getChildIndex(t10, u10) + 1;
        if (t10 !== v10) {
            f11 = h11 ? f11 + 1 : f11;
        }
        else {
            if (f11 > g11) {
                f11 = h11 ? f11 : f11 - 1;
            }
            else {
                f11 = h11 ? f11 + 1 : f11;
            }
        }
        for (let x11 = 0; x11 < this.listNode.length; x11++) {
            if (this.listNode[x11].getCurrentNodeId() === u10) {
                e11 = this.listNode[x11].getIsHighLight();
                if (this.flag === Flag.DOWN_FLAG && this.expandAndCollapseInfo.get(u10) === NodeStatus.Expand) {
                    z10 = u10;
                    f11 = 0;
                }
                else if (this.flag === Flag.UP_FLAG && this.expandAndCollapseInfo.get(u10) === NodeStatus.Expand
                    && this.listNode[x11].getCanShowFlagLine() === false) {
                    z10 = u10;
                    f11 = 0;
                }
                else if (e11) {
                    z10 = u10;
                    f11 = 0;
                }
                break;
            }
        }
        let i11 = {
            currentNodeId: a11,
            parentNodeId: z10,
            childIndex: f11,
        };
        this.appEventBus.emit(TreeListenType.NODE_MOVE, i11);
        y10.push({ parentId: z10, currentId: a11, data: b11 });
        let j11 = null;
        let k11 = (t11, u11) => {
            if (t11) {
                j11 = t11;
                z10 = j11.parentNodeId;
                a11 = j11.currentNodeId;
                for (let w11 = 0; w11 < u11.length; w11++) {
                    if (u11[w11].getNodeCurrentNodeId() === a11) {
                        c11 = u11[w11];
                        break;
                    }
                }
                if (c11 === null) {
                    return false;
                }
                let v11 = c11.getNodeInfoData();
                if (z10 !== v10) {
                    y10.push({ parentId: z10, currentId: a11, data: v11 });
                }
                return false;
            }
            return false;
        };
        this.listNodeUtils.dragTraverseNodeDF(k11, d11, this.listNode);
        this.listNodeUtils.removeNode(w10, v10);
        let l11 = u10;
        let m11 = h11;
        if (this.expandAndCollapseInfo.get(u10) === NodeStatus.Expand) {
            m11 = false;
            this.listNode.forEach((s11) => {
                if (s11.getCurrentNodeId() === u10 && s11.getCanShowFlagLine() === false) {
                    if (s11.getNodeInfoNode().children.length) {
                        l11 = s11.getNodeInfoNode().children[0].currentNodeId;
                    }
                    else {
                        l11 = this.INITIAL_INVALID_VALUE;
                    }
                }
            });
        }
        else if (!this.expandAndCollapseInfo.get(u10) && e11) {
            this.expandAndCollapseInfo.set(u10, NodeStatus.Expand);
        }
        this.listNodeUtils.addDragNode(y10[0].parentId, y10[0].currentId, l11, m11, y10[0].data);
        for (let q11 = 1; q11 < y10.length; q11++) {
            this.listNodeUtils.addNode(y10[q11].parentId, y10[q11].currentId, y10[q11].data);
        }
        for (let p11 = 0; p11 < this.listNode.length; p11++) {
            if (this.listNode[p11].getCurrentNodeId() === v10) {
                if (this.listNode[p11].getNodeInfoNode().getNodeItem().imageCollapse === null) {
                    this.listNode[p11].handleImageCollapseAfterAddNode(false);
                    this.expandAndCollapseInfo.delete(v10);
                    break;
                }
            }
        }
        let n11 = [...this.listNode];
        this.reloadListNode(this.listNodeUtils, n11);
    }

    reloadListNode(m10, n10) {
        let o10 = 0;
        this.listNode = [];
        this.listNodeUtils = m10;
        this.loadedNodeIdAndIndexMap.clear();
        this.listNodeUtils.traverseNodeDF((q10) => {
            if (q10.currentNodeId >= 0) {
                let r10 = new NodeInfo(q10);
                this.listNode.push(r10);
                if (this.expandAndCollapseInfo.get(q10.currentNodeId) === NodeStatus.Expand) {
                    r10.getNodeItem().imageCollapse?.changeImageCollapseSource(NodeStatus.Expand);
                }
                else if (this.expandAndCollapseInfo.get(q10.currentNodeId) === NodeStatus.Collapse) {
                    r10.getNodeItem().imageCollapse?.changeImageCollapseSource(NodeStatus.Collapse);
                }
                for (let s10 = 0; s10 < n10.length; s10++) {
                    if (n10[s10].getCurrentNodeId() === r10.getCurrentNodeId()) {
                        r10.setNodeIsShow(n10[s10].getNodeIsShow());
                        r10.setListItemHeight(n10[s10].getListItemHeight());
                        if (r10.getNodeItem().mainTitleNode && r10.getIsShowTitle()) {
                            r10.getNodeItem().mainTitleNode.title = n10[s10].getNodeItem().mainTitleNode?.title;
                        }
                        break;
                    }
                }
                if (r10.getNodeIsShow()) {
                    this.loadedNodeIdAndIndexMap.set(r10.getCurrentNodeId(), o10++);
                }
            }
            return false;
        });
    }

    getFlagLine() {
        return this.FLAG_LINE;
    }

    getVisibility(j10) {
        let k10 = this.loadedNodeIdAndIndexMap.get(j10.getCurrentNodeId()) - 1;
        if (k10 > this.INITIAL_INVALID_VALUE) {
            let l10 = this.getData(k10);
            return (j10.getCanShowFlagLine() === true && !j10.getIsHighLight() && !l10?.getIsHighLight()) ?
            Visibility.Visible : Visibility.Hidden;
        }
        else {
            return (j10.getCanShowFlagLine() === true && !j10.getIsHighLight()) ?
            Visibility.Visible : Visibility.Hidden;
        }
    }

    getSubTitlePara() {
        return this.subTitle;
    }

    getIsFolder(i10) {
        if (this.loadedNodeIdAndIndexMap.has(i10)) {
            return this.getData(this.loadedNodeIdAndIndexMap.get(i10))?.getIsFolder();
        }
        return false;
    }

    getSubTitleFontColor(h10) {
        return h10 ? this.subTitle.highLightFontColor : this.treeViewTheme.secondaryTitleFontColor;
    }

    getChildIndex(z9, a10) {
        let b10 = this.INITIAL_INVALID_VALUE;
        this.listNodeUtils.traverseNodeBF((d10) => {
            if (d10.getCurrentNodeId() === z9) {
                d10.children.forEach((f10, g10) => {
                    if (f10.getCurrentNodeId() === a10) {
                        b10 = g10;
                    }
                });
                return true;
            }
            return false;
        });
        return b10;
    }

    setCurrentFocusNodeId(y9) {
        this.currentFocusNodeId = y9;
    }

    getCurrentFocusNodeId() {
        return this.currentFocusNodeId;
    }

    setLastFocusNodeId(x9) {
        this.lastFocusNodeId = x9;
    }

    getLastFocusNodeId() {
        return this.lastFocusNodeId;
    }

    getAddFocusNodeId() {
        return this.addFocusNodeId;
    }

    setFlag(w9) {
        this.flag = w9;
    }
}

export class TreeViewInner extends ViewPU {
    constructor(q9, r9, s9, t9 = -1, u9 = undefined, v9) {
        super(q9, s9, t9, v9);
        if (typeof u9 === 'function') {
            this.paramsGenerator_ = u9;
        }
        this.__item = new SynchedPropertyNesedObjectPU(r9.item, this, 'item');
        this.listNodeDataSource = new ListNodeDataSource();
        this.__columnWidth = new ObservedPropertySimplePU(0, this, 'columnWidth');
        this.__isFocused = new ObservedPropertySimplePU(false, this, 'isFocused');
        this.__index = new ObservedPropertySimplePU(-1, this, 'index');
        this.__lastIndex = new ObservedPropertySimplePU(-1, this, 'lastIndex');
        this.__count = new ObservedPropertySimplePU(0, this, 'count');
        this.__treeViewTheme = this.initializeConsume('treeViewTheme', 'treeViewTheme');
        this.listTreeViewMenu = undefined;
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
            }
        };
        this.setInitiallyProvidedValue(r9);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(p9) {
        this.__item.set(p9.item);
        if (p9.listNodeDataSource !== undefined) {
            this.listNodeDataSource = p9.listNodeDataSource;
        }
        if (p9.columnWidth !== undefined) {
            this.columnWidth = p9.columnWidth;
        }
        if (p9.isFocused !== undefined) {
            this.isFocused = p9.isFocused;
        }
        if (p9.index !== undefined) {
            this.index = p9.index;
        }
        if (p9.lastIndex !== undefined) {
            this.lastIndex = p9.lastIndex;
        }
        if (p9.count !== undefined) {
            this.count = p9.count;
        }
        if (p9.listTreeViewMenu !== undefined) {
            this.listTreeViewMenu = p9.listTreeViewMenu;
        }
        if (p9.MAX_CN_LENGTH !== undefined) {
            this.MAX_CN_LENGTH = p9.MAX_CN_LENGTH;
        }
        if (p9.MAX_EN_LENGTH !== undefined) {
            this.MAX_EN_LENGTH = p9.MAX_EN_LENGTH;
        }
        if (p9.INITIAL_INVALID_VALUE !== undefined) {
            this.INITIAL_INVALID_VALUE = p9.INITIAL_INVALID_VALUE;
        }
        if (p9.MAX_TOUCH_DOWN_COUNT !== undefined) {
            this.MAX_TOUCH_DOWN_COUNT = p9.MAX_TOUCH_DOWN_COUNT;
        }
        if (p9.isMultiPress !== undefined) {
            this.isMultiPress = p9.isMultiPress;
        }
        if (p9.touchDownCount !== undefined) {
            this.touchDownCount = p9.touchDownCount;
        }
        if (p9.appEventBus !== undefined) {
            this.appEventBus = p9.appEventBus;
        }
        if (p9.itemPadding !== undefined) {
            this.itemPadding = p9.itemPadding;
        }
        if (p9.textInputPadding !== undefined) {
            this.textInputPadding = p9.textInputPadding;
        }
    }

    updateStateVars(o9) {
        this.__item.set(o9.item);
    }

    purgeVariableDependenciesOnElmtId(n9) {
        this.__item.purgeDependencyOnElmtId(n9);
        this.__columnWidth.purgeDependencyOnElmtId(n9);
        this.__isFocused.purgeDependencyOnElmtId(n9);
        this.__index.purgeDependencyOnElmtId(n9);
        this.__lastIndex.purgeDependencyOnElmtId(n9);
        this.__count.purgeDependencyOnElmtId(n9);
        this.__treeViewTheme.purgeDependencyOnElmtId(n9);
    }

    aboutToBeDeleted() {
        this.__item.aboutToBeDeleted();
        this.__columnWidth.aboutToBeDeleted();
        this.__isFocused.aboutToBeDeleted();
        this.__index.aboutToBeDeleted();
        this.__lastIndex.aboutToBeDeleted();
        this.__count.aboutToBeDeleted();
        this.__treeViewTheme.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get item() {
        return this.__item.get();
    }

    get columnWidth() {
        return this.__columnWidth.get();
    }

    set columnWidth(m9) {
        this.__columnWidth.set(m9);
    }

    get isFocused() {
        return this.__isFocused.get();
    }

    set isFocused(l9) {
        this.__isFocused.set(l9);
    }

    get index() {
        return this.__index.get();
    }

    set index(k9) {
        this.__index.set(k9);
    }

    get lastIndex() {
        return this.__lastIndex.get();
    }

    set lastIndex(j9) {
        this.__lastIndex.set(j9);
    }

    get count() {
        return this.__count.get();
    }

    set count(i9) {
        this.__count.set(i9);
    }

    get treeViewTheme() {
        return this.__treeViewTheme.get();
    }

    set treeViewTheme(h9) {
        this.__treeViewTheme.set(h9);
    }

    aboutToAppear() {
        if (this.item.getNodeItem().imageNode) {
            this.item.imageSource = this.item.getNodeItem().imageNode?.source;
        }
    }

    checkInvalidPattern(g9) {
        return new RegExp('/[\\\/:*?"<>|]/').test(g9);
    }

    checkIsAllCN(f9) {
        return new RegExp('/^[\u4e00-\u9fa5]+$/').test(f9);
    }

    popupForShowTitle(v8, w8, x8, y8 = null) {
        this.observeComponentCreation2((d9, e9) => {
            Row.create();
            Row.backgroundColor(w8);
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
        this.observeComponentCreation2((b9, c9) => {
            Text.create(v8);
            Text.fontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_body2'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            });
            Text.fontWeight('regular');
            Text.fontColor(x8);
        }, Text);
        Text.pop();
        Row.pop();
    }

    builder(p8 = null) {
        this.observeComponentCreation2((r8, s8) => {
            If.create();
            if (this.listTreeViewMenu) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.listTreeViewMenu.bind(this)(p8 ? p8 : this);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }

    initialRender() {
        this.observeComponentCreation2((o4, p4) => {
            If.create();
            if (this.item.getNodeIsShow()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((n8, o8) => {
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
                            style: BorderStyle.Solid
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
                            width: 0
                        });
                        ViewStackProcessor.visualState();
                    }, Stack);
                    this.observeComponentCreation2((x7, y7) => {
                        Column.create();
                        Column.opacity(this.listNodeDataSource.getListItemOpacity(ObservedObject.GetRawObject(this.item)));
                        Column.onHover((m8) => {
                            if (m8) {
                                this.item.setNodeColor(this.treeViewTheme.itemHoverBgColor);
                            }
                            else {
                                this.item.setNodeColor({
                                    'id': -1,
                                    'type': 10001,
                                    params: ['sys.color.ohos_id_color_background_transparent'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__',
                                });
                            }
                        });
                        Column.onTouch((i8) => {
                            this.count++;
                            if (this.count > 1) {
                                this.count--;
                                return;
                            }
                            let j8 = this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId());
                            this.listNodeDataSource.setClickIndex(this.index);
                            let k8 = this.item.getNodeCurrentNodeId();
                            if (i8.type === TouchType.Down) {
                                this.item.setNodeColor(this.treeViewTheme.itemPressedBgColor);
                            }
                            else if (i8.type === TouchType.Up) {
                                this.item.setNodeColor(this.treeViewTheme.itemSelectedBgColor);
                                if (this.item.getNodeItem().imageNode !== null) {
                                    this.item.getNodeItem().imageNode?.setImageSource(InteractionStatus.Selected);
                                    this.item.imageSource = this.item.getNodeItem().imageNode?.source;
                                }
                                this.item.getNodeItem().mainTitleNode?.setMainTitleSelected(true);
                                let l8 = { currentNodeId: k8 };
                                this.appEventBus.emit(TreeListenType.NODE_CLICK, l8);
                            }
                            if (this.listNodeDataSource.getLastIndex() !== -1 && j8 !== this.listNodeDataSource.getLastIndex()) {
                                this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false, this.listNodeDataSource.getLastIndex());
                                this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(), MenuOperation.COMMIT_NODE);
                            }
                            this.lastIndex = j8;
                            this.count--;
                        });
                        Column.backgroundColor((this.item.getNodeItem().mainTitleNode && this.item.getNodeItem().inputText &&
                        this.item.getIsShowInputText()) ? this.item.getNodeItem().inputText?.editColor : this.item.getNodeColor());
                        Column.border({
                            width: this.item.getNodeBorder().borderWidth,
                            color: this.item.getNodeBorder().borderColor,
                            radius: this.item.getNodeBorder().borderRadius,
                        });
                        Column.height(LIST_ITEM_HEIGHT);
                        Column.focusable(true);
                        Column.onMouse((g8) => {
                            let h8 = findCurrentNodeIndex(this.listNodeDataSource, this.item.getNodeCurrentNodeId());
                            if (g8.button === MouseButton.Right) {
                                this.listNodeDataSource.handleEvent(Event.MOUSE_BUTTON_RIGHT, findCurrentNodeIndex(this.listNodeDataSource, this.item.getNodeCurrentNodeId()));
                                this.listTreeViewMenu = this.item.getMenu();
                                this.listNodeDataSource.setClickIndex(h8);
                                clearTimeout(this.item.getNodeItem().mainTitleNode?.popUpTimeout);
                            }
                            g8.stopPropagation();
                        });
                        Column.padding({ top: 0, bottom: 0 });
                        Column.bindPopup(this.item.getPopUpInfo().popUpIsShow, {
                            builder: { builder: () => {
                                this.popupForShowTitle.call(this, this.item.getPopUpInfo().popUpText, this.item.getPopUpInfo().popUpColor, this.item.getPopUpInfo().popUpTextColor);
                            } },
                            placement: Placement.BottomLeft,
                            placementOnTop: false,
                            popupColor: this.item.getPopUpInfo().popUpColor,
                            autoCancel: true,
                            enableArrow: this.item.getPopUpInfo().popUpEnableArrow
                        });
                        Column.onAreaChange((d8, e8) => {
                            let f8 = Number.parseInt(e8.width.toString());
                            this.columnWidth = f8;
                        });
                    }, Column);
                    this.observeComponentCreation2((v7, w7) => {
                        Stack.create({ alignContent: Alignment.Bottom });
                        Stack.focusable(true);
                    }, Stack);
                    this.observeComponentCreation2((t7, u7) => {
                        Divider.create();
                        Divider.height(this.listNodeDataSource.getFlagLine().flagLineHeight);
                        Divider.color(this.listNodeDataSource.getFlagLine().flagLineColor);
                        Divider.visibility(this.listNodeDataSource.getVisibility(ObservedObject.GetRawObject(this.item)));
                        Divider.lineCap(LineCapStyle.Round);
                        Divider.margin({ start: LengthMetrics.vp(this.item.getFlagLineLeftMargin()) });
                        Divider.focusable(true);
                    }, Divider);
                    this.observeComponentCreation2((p7, q7) => {
                        Row.create({});
                        Row.focusable(true);
                        Row.width('100%');
                        Gesture.create(GesturePriority.Low);
                        TapGesture.create({ count: 2 });
                        TapGesture.onAction((s7) => {
                            this.listNodeDataSource.expandAndCollapseNode(findCurrentNodeIndex(this.listNodeDataSource, this.item.getNodeCurrentNodeId()));
                        });
                        TapGesture.pop();
                        Gesture.pop();
                        Row.height(this.item.getNodeHeight());
                        Row.padding({ start: LengthMetrics.vp(this.item.getNodeLeftPadding()) });
                        Row.bindContextMenu({ builder: this.builder.bind(this) }, ResponseType.RightClick);
                    }, Row);
                    this.observeComponentCreation2((f7, g7) => {
                        If.create();
                        if (this.item.getNodeItem().imageNode) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((n7, o7) => {
                                    Row.create();
                                    Row.focusable(true);
                                    Row.backgroundColor(this.treeViewTheme.arrowIconColor);
                                    Row.margin({
                                        end: getLengthMetricsByResourceOrNumber(this.item.getNodeItem().imageNode?.itemRightMargin)
                                    });
                                    Row.height(this.item.getNodeItem().imageNode?.itemHeight);
                                    Row.width(this.item.getNodeItem().imageNode?.itemWidth);
                                }, Row);
                                this.observeComponentCreation2((l7, m7) => {
                                    Image.create(this.item.imageSource);
                                    Image.objectFit(ImageFit.Contain);
                                    Image.height(this.item.getNodeItem().imageNode?.itemHeight);
                                    Image.width(this.item.getNodeItem().imageNode?.itemWidth);
                                    Image.opacity(!this.item.getIsSelected() && !this.item.getIsHighLight() ?
                                        this.item.getNodeItem().imageNode?.opacity : this.item.getNodeItem().imageNode?.noOpacity);
                                    Image.focusable(this.item.getNodeItem().mainTitleNode !== null ? false : true);
                                    Image.fillColor(!this.item.getIsSelected() && !this.item.getIsHighLight() ?
                                    this.treeViewTheme.leftIconColor : this.treeViewTheme.leftIconActiveColor);
                                    Image.matchTextDirection((this.item.getNodeItem()
                                        .imageCollapse?.collapseSource === ARROW_RIGHT || this.item.getNodeItem()
                                        .imageCollapse?.collapseSource === ARROW_RIGHT_WITHE) ? true : false);
                                }, Image);
                                Row.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    this.observeComponentCreation2((d7, e7) => {
                        Row.create();
                        Row.layoutWeight(1);
                        Row.focusable(true);
                    }, Row);
                    this.observeComponentCreation2((w6, x6) => {
                        If.create();
                        if (this.item.getNodeItem().mainTitleNode && this.item.getIsShowTitle()) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((b7, c7) => {
                                    Text.create(this.item.getNodeItem().mainTitleNode?.title);
                                    Text.maxLines(1);
                                    Text.fontSize(this.item.getNodeItem().mainTitleNode?.size);
                                    Text.fontColor(this.item.getIsSelected() ?
                                    this.treeViewTheme.primaryTitleActiveFontColor : this.treeViewTheme.primaryTitleFontColor);
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
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    this.observeComponentCreation2((c6, d6) => {
                        If.create();
                        if (this.item.getNodeItem().mainTitleNode && this.item.getNodeItem().inputText &&
                        this.item.getIsShowInputText()) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((u6, v6) => {
                                    Row.create();
                                    Row.backgroundColor(this.item.getNodeItem().inputText?.backgroundColor);
                                    Row.borderRadius(this.item.getNodeItem().inputText?.borderRadius);
                                    Row.margin({
                                        end: getLengthMetricsByResourceOrNumber(this.item.getNodeItem()
                                            .inputText?.itemRightMargin)
                                    });
                                }, Row);
                                this.observeComponentCreation2((i6, j6) => {
                                    TextInput.create({ text: this.item.getNodeItem().mainTitleNode?.title });
                                    TextInput.height(this.item.getNodeItem().inputText?.itemHeight);
                                    TextInput.fontSize(this.item.getNodeItem().inputText?.size);
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
                                    TextInput.onChange((o6) => {
                                        let p6 = findCurrentNodeIndex(this.listNodeDataSource, this.item.getNodeCurrentNodeId());
                                        let q6 = '';
                                        let r6 = false;
                                        let s6 = false;
                                        if (this.checkInvalidPattern(o6)) {
                                            for (let t6 = 0; t6 < o6.length; t6++) {
                                                if (!this.checkInvalidPattern(o6[t6])) {
                                                    q6 += o6[t6];
                                                }
                                            }
                                            r6 = true;
                                            this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.INVALID_ERROR, true, p6);
                                        }
                                        else {
                                            q6 = o6;
                                            r6 = false;
                                        }
                                        if ((this.checkIsAllCN(q6) && q6.length > this.MAX_CN_LENGTH) ||
                                            (!this.checkIsAllCN(q6) && q6.length > this.MAX_EN_LENGTH)) {
                                            q6 = this.checkIsAllCN(q6) ?
                                            q6.substr(0, this.MAX_CN_LENGTH) : q6.substr(0, this.MAX_EN_LENGTH);
                                            s6 = true;
                                            this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.LENGTH_ERROR, true, p6);
                                        }
                                        else {
                                            s6 = false;
                                        }
                                        if (!s6 && !r6) {
                                            this.listNodeDataSource.setMainTitleNameOnEdit(p6, q6);
                                        }
                                    });
                                    TextInput.onSubmit((m6) => {
                                        let n6 = findCurrentNodeIndex(this.listNodeDataSource, this.item.getNodeCurrentNodeId());
                                        this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false, n6);
                                        this.listNodeDataSource.setItemVisibilityOnEdit(n6, MenuOperation.COMMIT_NODE);
                                    });
                                }, TextInput);
                                Row.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    this.observeComponentCreation2((a6, b6) => {
                        Blank.create();
                    }, Blank);
                    Blank.pop();
                    Row.pop();
                    this.observeComponentCreation2((q5, r5) => {
                        If.create();
                        if (this.listNodeDataSource.hasSubtitle(this.item.getCurrentNodeId())) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((y5, z5) => {
                                    Row.create();
                                    Row.focusable(true);
                                    Row.margin({
                                        start: LengthMetrics.resource(this.listNodeDataSource.getSubTitlePara().margin.left),
                                        end: this.item.getNodeItem().imageCollapse ?
                                        LengthMetrics.resource({
                                            'id': -1,
                                            'type': 10002,
                                            params: ['sys.float.padding_level0'],
                                            'bundleName': '__harDefaultBundleName__',
                                            'moduleName': '__harDefaultModuleName__',
                                        }) : LengthMetrics.resource(this.listNodeDataSource.getSubTitlePara().margin.right)
                                    });
                                }, Row);
                                this.observeComponentCreation2((w5, x5) => {
                                    Text.create(this.listNodeDataSource.getSubtitle(this.item.getCurrentNodeId()));
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
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    this.observeComponentCreation2((e5, f5) => {
                        If.create();
                        if (this.item.getNodeItem().imageCollapse) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((o5, p5) => {
                                    Row.create();
                                    Row.focusable(true);
                                    Row.height(this.item.getNodeItem().imageCollapse?.itemHeight);
                                    Row.width(this.item.getNodeItem().imageCollapse?.itemWidth);
                                }, Row);
                                this.observeComponentCreation2((k5, l5) => {
                                    Image.create(this.item.getNodeItem().imageCollapse?.collapseSource);
                                    Image.fillColor(this.item.getNodeItem().imageCollapse?.isCollapse ?
                                    this.treeViewTheme.arrowIconColor : COLOR_IMAGE_EDIT);
                                    Image.align(Alignment.End);
                                    Image.objectFit(ImageFit.Contain);
                                    Image.height(this.item.getNodeItem().imageCollapse?.itemHeight);
                                    Image.width(this.item.getNodeItem().imageCollapse?.itemWidth);
                                    Image.opacity(!this.item.getIsHighLight() ?
                                        this.item.getNodeItem().imageCollapse?.opacity : this.item.getNodeItem().imageCollapse?.noOpacity);
                                    Image.onTouch((n5) => {
                                        if (n5.type === TouchType.Down) {
                                            this.listNodeDataSource.expandAndCollapseNode(findCurrentNodeIndex(this.listNodeDataSource,
                                                this.item.getNodeCurrentNodeId()));
                                            this.listNodeDataSource.setCurrentFocusNodeId(this.item.getCurrentNodeId());
                                        }
                                        n5.stopPropagation();
                                    });
                                    Image.focusable(true);
                                    Image.matchTextDirection((this.item.getNodeItem()
                                        .imageCollapse?.collapseSource === ARROW_RIGHT || this.item.getNodeItem()
                                        .imageCollapse?.collapseSource === ARROW_RIGHT_WITHE) ? true : false);
                                }, Image);
                                Row.pop();
                            });
                        }
                        else {
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
            }
            else {
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
    constructor(m4) {
        this.data = m4;
        this.nodeLevel = -1;
        this.parentNodeId = -1;
        this.currentNodeId = -1;
        this.nodeItem = {
            imageNode: undefined,
            inputText: new InputText(),
            mainTitleNode: new MainTitleNode(''),
            imageCollapse: undefined,
            fontColor: undefined,
        };
        this.childNodeInfo = { isHasChildNode: false, childNum: 0, allChildNum: 0 };
        this.container = m4.container;
        if (m4.icon) {
            this.nodeItem.imageNode = new ImageNode(m4.icon, {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_alpha_content_fourth'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            }, IMAGE_NODE_HEIGHT, IMAGE_NODE_WIDTH, m4.selectedIcon, m4.editIcon);
        }
        if (m4.primaryTitle) {
            this.nodeItem.mainTitleNode = new MainTitleNode(m4.primaryTitle);
        }
        this.children = [];
    }

    addImageCollapse(l4) {
        if (l4) {
            this.nodeItem.imageCollapse = new ImageNode(ARROW_RIGHT, {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_alpha_content_tertiary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            }, IMAGE_NODE_HEIGHT, IMAGE_NODE_WIDTH, undefined, undefined);
            this.nodeItem.imageCollapse.itemRightMargin = ({
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_paragraph_margin_xs'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            });
        }
        else {
            this.nodeItem.imageCollapse = undefined;
        }
    }

    getNodeItem() {
        return this.nodeItem;
    }

    getChildNodeInfo() {
        return this.childNodeInfo;
    }

    getMenu() {
        return this.container;
    }

    getCurrentNodeId() {
        return this.currentNodeId;
    }

    getIsFolder() {
        return this.data.isFolder;
    }
}

class NodeBaseInfo {
    constructor() {
        this.rightMargin = -1;
        this.width = -1;
        this.height = -1;
    }

    set itemWidth(k4) {
        this.width = k4;
    }

    get itemWidth() {
        return this.width;
    }

    set itemHeight(j4) {
        this.height = j4;
    }

    get itemHeight() {
        return this.height;
    }

    set itemRightMargin(i4) {
        this.rightMargin = i4;
    }

    get itemRightMargin() {
        return this.rightMargin;
    }
}

export class ImageNode extends NodeBaseInfo {
    constructor(c4, d4, e4, f4, g4, h4) {
        super();
        this.rightMargin = {
            'id': -1,
            'type': 10002,
            params: ['sys.float.ohos_id_elements_margin_horizontal_m'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.imageSource = c4;
        this.imageNormalSource = c4;
        if (g4 !== undefined) {
            this.imageSelectedSource = g4;
        }
        else {
            this.imageSelectedSource = this.imageNormalSource;
        }
        if (h4 !== undefined) {
            this.imageEditSource = h4;
        }
        else {
            this.imageEditSource = this.imageNormalSource;
        }
        this.imageOpacity = d4;
        this.itemWidth = e4;
        this.itemHeight = f4;
        this.imageCollapseSource = c4;
        this.imageCollapseDownSource = ARROW_DOWN;
        this.imageCollapseRightSource = ARROW_RIGHT;
        this.isImageCollapse = true;
        this.currentInteractionStatus = InteractionStatus.Normal;
    }

    get source() {
        return this.imageSource;
    }

    get normalSource() {
        return this.imageNormalSource;
    }

    get selectedSource() {
        return this.imageSelectedSource;
    }

    get editSource() {
        return this.imageEditSource;
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

    changeImageCollapseSource(b4) {
        if (b4 === NodeStatus.Expand) {
            this.imageCollapseSource = this.imageCollapseDownSource;
        }
        else if (b4 === NodeStatus.Collapse) {
            this.imageCollapseSource = this.imageCollapseRightSource;
        }
    }

    setImageCollapseSource(z3, a4) {
        if (z3 === InteractionStatus.Edit || z3 === InteractionStatus.DragInsert) {
            this.imageCollapseDownSource = ARROW_DOWN_WITHE;
            this.imageCollapseRightSource = ARROW_RIGHT_WITHE;
            this.isImageCollapse = false;
        }
        else if (z3 === InteractionStatus.FinishEdit ||
            z3 === InteractionStatus.FinishDragInsert) {
            this.imageCollapseDownSource = ARROW_DOWN;
            this.imageCollapseRightSource = ARROW_RIGHT;
            this.isImageCollapse = true;
        }
        this.imageCollapseSource = (a4 === NodeStatus.Collapse) ?
        this.imageCollapseRightSource : this.imageCollapseDownSource;
    }

    setImageSource(y3) {
        switch (y3) {
            case InteractionStatus.Normal:
                this.imageSource = this.imageNormalSource;
                this.currentInteractionStatus = y3;
                break;
            case InteractionStatus.Selected:
                if (this.currentInteractionStatus !== InteractionStatus.Edit) {
                    this.imageSource = this.imageSelectedSource;
                    this.currentInteractionStatus = y3;
                }
                break;
            case InteractionStatus.Edit:
                this.imageSource = this.imageEditSource;
                this.currentInteractionStatus = y3;
                break;
            case InteractionStatus.FinishEdit:
                this.imageSource = this.imageSelectedSource;
                this.currentInteractionStatus = y3;
                break;
            case InteractionStatus.DragInsert:
                this.imageSource = this.imageEditSource;
                this.currentInteractionStatus = y3;
                break;
            case InteractionStatus.FinishDragInsert:
                this.imageSource = this.imageNormalSource;
                this.currentInteractionStatus = y3;
                break;
            default:
                break;
        }
    }
}

class MainTitleNode extends NodeBaseInfo {
    constructor(x3) {
        super();
        this.treeViewTheme = new TreeViewTheme();
        this.mainTitleName = x3;
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

    setMainTitleSelected(w3) {
        if (w3) {
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
        }
        else {
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

    set title(v3) {
        this.mainTitleName = v3;
    }

    get title() {
        return this.mainTitleName;
    }

    set popUpTimeout(u3) {
        this.showPopUpTimeout = u3;
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

    setMainTitleHighLight(t3) {
        if (t3) {
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
        }
        else {
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
        this.treeViewTheme = new TreeViewTheme();
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

export class ListNodeUtils {
    constructor() {
        this.MaxNodeLevel = 50;
        this.MAX_CN_LENGTH = 254;
        this.MAX_EN_LENGTH = 255;
        this.INITIAL_INVALID_VALUE = -1;
        this._root = new NodeItem(emptyNodeInfo);
        this._root.nodeLevel = -1;
        this._root.parentNodeId = -1;
        this._root.currentNodeId = -1;
        this.addNewNodeId = -1;
    }

    getNewNodeId() {
        return this.addNewNodeId;
    }

    traverseNodeDF(o3, p3 = this._root) {
        let q3 = [], r3 = false;
        q3.unshift(p3);
        let s3 = q3.shift();
        while (!r3 && s3) {
            r3 = o3(s3) === true;
            if (!r3) {
                q3.unshift(...s3.children);
                s3 = q3.shift();
            }
        }
    }

    traverseNodeBF(j3) {
        let k3 = [];
        let l3 = false;
        k3.push(this._root);
        let m3 = k3.shift();
        while (!l3 && m3) {
            try {
                l3 = j3(m3);
            }
            catch (n3) {
                throw new Error('traverseNodeBF function callbacks error.');
            }
            if (!l3) {
                k3.push(...m3.children);
                m3 = k3.shift();
            }
        }
    }

    contains(h3, i3) {
        i3(h3);
    }

    updateParentChildNum(b3, c3, d3) {
        let e3 = b3.parentNodeId;
        while (e3 >= 0) {
            this.traverseNodeDF((g3) => {
                if (g3.currentNodeId === e3) {
                    g3.getChildNodeInfo().allChildNum =
                        c3 ? g3.getChildNodeInfo().allChildNum + d3 : g3.getChildNodeInfo().allChildNum - d3;
                    e3 = g3.parentNodeId;
                    return false;
                }
                return false;
            });
        }
    }

    findParentNodeId(w2) {
        let x2 = new NodeItem(emptyNodeInfo);
        let y2 = (a3) => {
            if (a3.currentNodeId === w2) {
                x2 = a3;
                return true;
            }
            return false;
        };
        this.traverseNodeBF(y2);
        return x2.parentNodeId;
    }

    addNode(o2, p2, q2) {
        if (this._root === null) {
            this._root = new NodeItem(emptyNodeInfo);
            this._root.nodeLevel = -1;
            this._root.parentNodeId = -1;
            this._root.currentNodeId = -1;
        }
        let r2 = new NodeItem(emptyNodeInfo);
        let s2 = (v2) => {
            if (v2.currentNodeId === o2) {
                r2 = v2;
                return true;
            }
            return false;
        };
        this.traverseNodeBF(s2);
        if (r2) {
            let u2 = new NodeItem(q2);
            if (r2.nodeLevel > this.MaxNodeLevel) {
                throw new Error('ListNodeUtils[addNode]: The level of the tree view cannot exceed 50.');
            }
            u2.nodeLevel = r2.nodeLevel + 1;
            u2.parentNodeId = o2;
            u2.currentNodeId = p2;
            r2.children.push(u2);
            r2.getChildNodeInfo().isHasChildNode = true;
            r2.getChildNodeInfo().childNum = r2.children.length;
            r2.getChildNodeInfo().allChildNum += 1;
            r2.addImageCollapse(r2.getChildNodeInfo().isHasChildNode);
            this.updateParentChildNum(r2, true, 1);
            return this;
        }
        else {
            throw new Error('ListNodeUtils[addNode]: Parent node not found.');
        }
    }

    findNodeIndex(j2, k2) {
        let l2 = this.INITIAL_INVALID_VALUE;
        for (let m2 = 0, n2 = j2.length; m2 < n2; m2++) {
            if (j2[m2].currentNodeId === k2) {
                l2 = m2;
                break;
            }
        }
        return l2;
    }

    freeNodeMemory(b2, c2) {
        let d2 = [];
        let e2 = (i2) => {
            d2.push(i2);
            return false;
        };
        this.traverseNodeDF(e2, b2);
        d2.forEach((h2) => {
            c2.push(h2.currentNodeId);
            h2 = new NodeItem(emptyNodeInfo);
        });
    }

    removeNode(r1, s1) {
        let t1 = new NodeItem(emptyNodeInfo);
        let u1 = (a2) => {
            if (a2.currentNodeId === s1) {
                t1 = a2;
                return true;
            }
            return false;
        };
        this.traverseNodeBF(u1);
        if (t1) {
            let w1 = [];
            let x1 = this.findNodeIndex(t1.children, r1);
            let y1 = 0;
            if (x1 < 0) {
                throw new Error('Node does not exist.');
            }
            else {
                y1 = t1.children[x1].getChildNodeInfo().allChildNum + 1;
                this.freeNodeMemory(t1.children[x1], w1);
                let z1 = t1.children.splice(x1, 1);
                z1 = null;
                if (t1.children.length === 0) {
                    t1.addImageCollapse(false);
                }
            }
            t1.getChildNodeInfo().childNum = t1.children.length;
            t1.getChildNodeInfo().allChildNum -= (y1);
            this.updateParentChildNum(t1, false, y1);
            return w1;
        }
        else {
            throw new Error('Parent does not exist.');
        }
    }

    getNewNodeInfo(l1) {
        let m1 = new NodeItem(emptyNodeInfo);
        let n1 = (q1) => {
            if (q1.currentNodeId === l1) {
                m1 = q1;
                return true;
            }
            return false;
        };
        this.traverseNodeBF(n1);
        let o1 = emptyNodeInfo;
        if (m1) {
            if (m1.children.length === 0) {
                if (m1.getNodeItem().imageNode !== undefined) {
                    o1.icon = m1.getNodeItem().imageNode?.normalSource;
                    o1.selectedIcon = m1.getNodeItem().imageNode?.selectedSource;
                    o1.editIcon = m1.getNodeItem().imageNode?.editSource;
                    o1.container = m1.getMenu();
                }
                else {
                    o1.icon = undefined;
                    o1.selectedIcon = undefined;
                    o1.editIcon = undefined;
                    o1.container = m1.getMenu();
                }
            }
            else if (m1.children.length > 0) {
                if (m1.getNodeItem().imageNode !== null) {
                    o1.icon = (m1.children[0].getNodeItem().imageNode !== undefined) ?
                        m1.children[0].getNodeItem().imageNode?.normalSource : undefined;
                    o1.selectedIcon = (m1.children[0].getNodeItem().imageNode !== undefined) ?
                        m1.children[0].getNodeItem().imageNode?.selectedSource : undefined;
                    o1.editIcon = (m1.children[0].getNodeItem().imageNode !== undefined) ?
                        m1.children[0].getNodeItem().imageNode?.editSource : undefined;
                    o1.container = m1.children[0].getMenu();
                }
                else {
                    o1.icon = undefined;
                    o1.selectedIcon = undefined;
                    o1.editIcon = undefined;
                    o1.container = m1.children[0].getMenu();
                }
            }
        }
        return o1;
    }

    getClickChildId(c1) {
        let d1 = new NodeItem(emptyNodeInfo);
        let e1 = (k1) => {
            if (k1.currentNodeId === c1) {
                d1 = k1;
                return true;
            }
            return false;
        };
        this.traverseNodeBF(e1);
        if (d1) {
            if (d1.children.length === 0) {
                return [];
            }
            else if (d1.children.length > 0) {
                let g1 = { itemId: undefined, itemIcon: undefined, itemTitle: undefined };
                let h1 = new Array(d1.children.length);
                for (let j1 = 0; j1 < h1.length; j1++) {
                    h1[j1] = 0;
                }
                for (let i1 = 0; i1 < d1.children.length && i1 < h1.length; i1++) {
                    h1[i1] = d1.children[i1].currentNodeId;
                }
                return h1;
            }
        }
        return [];
    }

    getClickNodeChildrenInfo(u) {
        let v = new NodeItem(emptyNodeInfo);
        let w = (b1) => {
            if (b1.currentNodeId === u) {
                v = b1;
                return true;
            }
            return false;
        };
        this.traverseNodeBF(w);
        if (v) {
            if (v.children.length === 0) {
                return [];
            }
            else if (v.children.length > 0) {
                let y = new Array(v.children.length);
                for (let a1 = 0; a1 < y.length; a1++) {
                    y[a1] = {};
                }
                for (let z = 0; z < v.children.length && z < y.length; z++) {
                    y[z].itemId = v.children[z].currentNodeId;
                    if (v.children[z].getNodeItem().imageNode) {
                        y[z].itemIcon = v.children[z].getNodeItem().imageNode?.source;
                    }
                    if (v.children[z].getNodeItem().mainTitleNode) {
                        y[z].itemTitle = v.children[z].getNodeItem().mainTitleNode?.title;
                    }
                    y[z].isFolder = v.children[z].getIsFolder();
                }
                return y;
            }
        }
        return [];
    }

    checkMainTitleIsValid(t) {
        if (new RegExp('/[\\\/:*?"<>|]/').test(t)) {
            return false;
        }
        if ((new RegExp('/^[\u4e00-\u9fa5]+$/').test(t) && t.length > this.MAX_CN_LENGTH) ||
            (!new RegExp('/^[\u4e00-\u9fa5]+$/').test(t) && t.length > this.MAX_EN_LENGTH)) {
            return false;
        }
        return true;
    }

    dragTraverseNodeDF(n, o = this._root, p) {
        let q = [], r = false;
        q.unshift(o);
        let s = q.shift();
        while (!r && s) {
            r = n(s, p) === true;
            if (!r) {
                q.unshift(...s.children);
                s = q.shift();
            }
        }
    }

    addDragNode(b, c, d, e, f) {
        if (this._root === null) {
            this._root = new NodeItem(emptyNodeInfo);
            this._root.nodeLevel = this.INITIAL_INVALID_VALUE;
            this._root.parentNodeId = this.INITIAL_INVALID_VALUE;
            this._root.currentNodeId = this.INITIAL_INVALID_VALUE;
        }
        let g = new NodeItem(emptyNodeInfo);
        let h = (m) => {
            if (m.currentNodeId === b) {
                g = m;
                return true;
            }
            return false;
        };
        this.traverseNodeBF(h);
        if (g) {
            let j = new NodeItem(f);
            if (g.nodeLevel > this.MaxNodeLevel) {
                throw new Error('ListNodeUtils[addNode]: The level of the tree view cannot exceed 50.');
            }
            j.nodeLevel = g.nodeLevel + 1;
            j.parentNodeId = b;
            j.currentNodeId = c;
            let k = this.INITIAL_INVALID_VALUE;
            if (g.children.length) {
                for (let l = 0; l < g.children.length; l++) {
                    if (g.children[l].getCurrentNodeId() === d) {
                        k = l;
                        break;
                    }
                }
                if (e) {
                    g.children.splice(k + 1, 0, j);
                }
                else {
                    g.children.splice(k, 0, j);
                }
            }
            else {
                g.children.push(j);
            }
            g.getChildNodeInfo().isHasChildNode = true;
            g.getChildNodeInfo().childNum = g.children.length;
            g.getChildNodeInfo().allChildNum += 1;
            g.addImageCollapse(g.getChildNodeInfo().isHasChildNode);
            this.updateParentChildNum(g, true, 1);
            return this;
        }
        else {
            throw new Error('ListNodeUtils[addNode]: Parent node not found.');
        }
    }
}

function getLengthMetricsByResourceOrNumber(a) {
    if (!a) {
        return LengthMetrics.vp(0);
    }
    else if (typeof a === 'number') {
        return LengthMetrics.vp(a);
    }
    else {
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