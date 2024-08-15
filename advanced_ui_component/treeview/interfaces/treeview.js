/**
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

var __decorate = (this && this.__decorate) || function (k28, l28, m28, n28) {
    var o28 = arguments.length,
        p28 = o28 < 3 ? l28 : n28 === null ? n28 = Object.getOwnPropertyDescriptor(l28, m28) : n28, q28;
    if (typeof Reflect === 'object' && typeof Reflect.decorate === 'function')
        p28 = Reflect.decorate(k28, l28, m28, n28);
    else
        for (var r28 = k28.length - 1; r28 >= 0; r28--)
            if (q28 = k28[r28])
                p28 = (o28 < 3 ? q28(p28) : o28 > 3 ? q28(l28, m28, p28) : q28(l28, m28)) || p28;
    return o28 > 3 && p28 && Object.defineProperty(l28, m28, p28), p28;
};
if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {
    });
}

const hilog = requireNapi('hilog');
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const resourceManager = requireNapi('resourceManager');

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
(function (i28) {
    i28[i28['TOUCH_DOWN'] = 0] = 'TOUCH_DOWN';
    i28[i28['TOUCH_UP'] = 1] = 'TOUCH_UP';
    i28[i28['HOVER'] = 3] = 'HOVER';
    i28[i28['HOVER_OVER'] = 4] = 'HOVER_OVER';
    i28[i28['FOCUS'] = 5] = 'FOCUS';
    i28[i28['BLUR'] = 6] = 'BLUR';
    i28[i28['MOUSE_BUTTON_RIGHT'] = 7] = 'MOUSE_BUTTON_RIGHT';
    i28[i28['DRAG'] = 8] = 'DRAG';
})(Event || (Event = {}));
var MenuOperation;
(function (h28) {
    h28[h28['ADD_NODE'] = 0] = 'ADD_NODE';
    h28[h28['REMOVE_NODE'] = 1] = 'REMOVE_NODE';
    h28[h28['MODIFY_NODE'] = 2] = 'MODIFY_NODE';
    h28[h28['COMMIT_NODE'] = 3] = 'COMMIT_NODE';
})(MenuOperation || (MenuOperation = {}));
var PopUpType;
(function (g28) {
    g28[g28['HINTS'] = 0] = 'HINTS';
    g28[g28['WARNINGS'] = 1] = 'WARNINGS';
})(PopUpType || (PopUpType = {}));
var InputError;
(function (f28) {
    f28[f28['INVALID_ERROR'] = 0] = 'INVALID_ERROR';
    f28[f28['LENGTH_ERROR'] = 1] = 'LENGTH_ERROR';
    f28[f28['NONE'] = 2] = 'NONE';
})(InputError || (InputError = {}));
var Flag;
(function (e28) {
    e28[e28['DOWN_FLAG'] = 0] = 'DOWN_FLAG';
    e28[e28['UP_FLAG'] = 1] = 'UP_FLAG';
    e28[e28['NONE'] = 2] = 'NONE';
})(Flag || (Flag = {}));

export var NodeStatus;
(function (d28) {
    d28[d28['EXPAND'] = 0] = 'EXPAND';
    d28[d28['COLLAPSE'] = 1] = 'COLLAPSE';
})(NodeStatus || (NodeStatus = {}));

export var InteractionStatus;
(function (c28) {
    c28[c28['NORMAL'] = 0] = 'NORMAL';
    c28[c28['SELECTED'] = 1] = 'SELECTED';
    c28[c28['EDIT'] = 2] = 'EDIT';
    c28[c28['FINISH_EDIT'] = 3] = 'FINISH_EDIT';
    c28[c28['DRAG_INSERT'] = 4] = 'DRAG_INSERT';
    c28[c28['FINISH_DRAG_INSERT'] = 5] = 'FINISH_DRAG_INSERT';
})(InteractionStatus || (InteractionStatus = {}));
var CollapseImageType;
(function (b28) {
    b28[b28['ARROW_DOWN'] = 0] = 'ARROW_DOWN';
    b28[b28['ARROW_RIGHT'] = 1] = 'ARROW_RIGHT';
    b28[b28['ARROW_DOWN_WHITE'] = 2] = 'ARROW_DOWN_WHITE';
    b28[b28['ARROW_RIGHT_WHITE'] = 3] = 'ARROW_RIGHT_WHITE';
})(CollapseImageType || (CollapseImageType = {}));

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

    createNodeByNodeParam(z27) {
        let a28 = this.createNode();
        if (z27.icon) {
            a28.imageNode = new ImageNode(z27.icon, {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_alpha_content_fourth'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            }, IMAGE_NODE_HEIGHT, IMAGE_NODE_WIDTH, z27.selectedIcon, z27.editIcon);
        }
        if (z27.primaryTitle) {
            a28.mainTitleNode = new MainTitleNode(z27.primaryTitle);
        }
        return a28;
    }
}

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

    static getInstance() {
        if (!TreeViewTheme.instance) {
            TreeViewTheme.instance = new TreeViewTheme();
        }
        return TreeViewTheme.instance;
    }
}

let NodeInfo = class NodeInfo {
    constructor(x27, y27) {
        this.imageSource = '';
        this.borderWidth = { has: BORDER_WIDTH_HAS, none: BORDER_WIDTH_NONE };
        this.canShowFlagLine = false;
        this.isOverBorder = false;
        this.canShowBottomFlagLine = false;
        this.isHighLight = false;
        this.isModify = false;
        this.treeViewTheme = TreeViewTheme.getInstance();
        this.fontColor = '';
        this.node = x27;
        this.nodeParam = y27;
        this.nodeItemView = TreeViewNodeItemFactory.getInstance().createNodeByNodeParam(y27);
        this.popUpInfo = {
            popUpIsShow: false,
            popUpEnableArrow: false,
            popUpColor: undefined,
            popUpText: '',
            popUpTextColor: undefined,
        };
        this.nodeHeight = NODE_HEIGHT;
        this.nodeLeftPadding = x27.nodeLevel * LEVEL_MARGIN + MARGIN_OFFSET;
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
        this.flagLineLeftMargin = x27.nodeLevel * LEVEL_MARGIN + MARGIN_OFFSET;
    }

    addImageCollapse(w27) {
        if (w27) {
            this.nodeItemView.imageCollapse =
            CollapseImageNodeFlyweightFactory.getCollapseImageNodeByType(CollapseImageType.ARROW_RIGHT);
        }
        else {
            this.nodeItemView.imageCollapse = undefined;
        }
    }

    setFontColor(v27) {
        this.fontColor = v27;
    }

    getFontColor() {
        return this.fontColor;
    }

    getPopUpInfo() {
        return this.popUpInfo;
    }

    setPopUpIsShow(u27) {
        this.popUpInfo.popUpIsShow = u27;
    }

    setPopUpEnableArrow(t27) {
        this.popUpInfo.popUpEnableArrow = t27;
    }

    setPopUpColor(s27) {
        this.popUpInfo.popUpColor = s27;
    }

    setPopUpText(r27) {
        this.popUpInfo.popUpText = r27;
    }

    setPopUpTextColor(q27) {
        this.popUpInfo.popUpTextColor = q27;
    }

    getIsShowTitle() {
        return this.isShowTitle;
    }

    getIsShowInputText() {
        return this.isShowInputText;
    }

    setTitleAndInputTextStatus(p27) {
        if (p27) {
            this.isShowTitle = false;
            this.isShowInputText = true;
        }
        else {
            this.isShowTitle = true;
            this.isShowInputText = false;
        }
    }

    handleImageCollapseAfterAddNode(o27) {
        if (o27) {
            this.nodeItemView.imageCollapse =
            CollapseImageNodeFlyweightFactory.getCollapseImageNodeByType(CollapseImageType.ARROW_DOWN);
        }
        else {
            this.nodeItemView.imageCollapse = undefined;
        }
    }

    setNodeColor(n27) {
        if (n27 === undefined) {
            return;
        }
        this.nodeColor = n27;
    }

    getNodeColor() {
        return this.nodeColor;
    }

    setListItemHeight(m27) {
        this.listItemHeight = m27;
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

    setNodeIsShow(l27) {
        this.nodeIsShow = l27;
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

    setNodeBorder(k27) {
        this.nodeBorder.borderWidth = k27 ? this.borderWidth.has : this.borderWidth.none;
    }

    getChildNodeInfo() {
        return this.node.childNodeInfo;
    }

    getMenu() {
        return this.nodeParam.container;
    }

    setIsSelected(j27) {
        this.isSelected = j27;
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

    setCanShowFlagLine(i27) {
        this.canShowFlagLine = i27;
    }

    getCanShowFlagLine() {
        return this.canShowFlagLine;
    }

    setFlagLineLeftMargin(h27) {
        if (h27 === undefined) {
            return;
        }
        this.flagLineLeftMargin = h27 * LEVEL_MARGIN + MARGIN_OFFSET;
    }

    getFlagLineLeftMargin() {
        return this.flagLineLeftMargin;
    }

    getNodeLevel() {
        return this.node.nodeLevel;
    }

    setIsOverBorder(g27) {
        this.isOverBorder = g27;
    }

    getIsOverBorder() {
        return this.isOverBorder;
    }

    setCanShowBottomFlagLine(f27) {
        this.canShowBottomFlagLine = f27;
    }

    getCanShowBottomFlagLine() {
        return this.canShowBottomFlagLine;
    }

    setIsHighLight(e27) {
        this.isHighLight = e27;
    }

    getIsHighLight() {
        return this.isHighLight;
    }

    setIsModify(d27) {
        this.isModify = d27;
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
(function (c27) {
    c27['NODE_CLICK'] = 'NodeClick';
    c27['NODE_ADD'] = 'NodeAdd';
    c27['NODE_DELETE'] = 'NodeDelete';
    c27['NODE_MODIFY'] = 'NodeModify';
    c27['NODE_MOVE'] = 'NodeMove';
})(TreeListenType || (TreeListenType = {}));

export class TreeListener {
    constructor() {
        this._events = [];
        this._once_events = [];
    }

    on(y26, z26) {
        if (Array.isArray(y26)) {
            for (let a27 = 0, b27 = y26.length; a27 < b27; a27++) {
                this.on(y26[a27], z26);
            }
        }
        else {
            (this._events[y26] || (this._events[y26] = [])).push(z26);
        }
    }

    once(w26, x26) {
        if (Array.isArray(w26)) {
            this.off(w26, x26);
        }
        else {
            (this._once_events[w26] || (this._once_events[w26] = [])).push(x26);
        }
    }

    off(p26, q26) {
        if (p26 === null) {
            this._events = [];
        }
        if (Array.isArray(p26)) {
            for (let u26 = 0, v26 = p26.length; u26 < v26; u26++) {
                this.off(p26[u26], q26);
            }
        }
        let r26 = this._events[p26];
        if (!r26) {
            return;
        }
        if (q26 === null) {
            this._events[p26] = null;
        }
        let s26 = r26.length;
        while (s26--) {
            let t26 = r26[s26];
            if (t26 === q26) {
                r26.splice(s26, 1);
                break;
            }
        }
    }

    emit(f26, g26) {
        if (this._once_events[f26]) {
            let l26 = Array.from(this._once_events[f26]);
            if (l26) {
                for (let m26 = 0, n26 = l26.length; m26 < n26; m26++) {
                    try {
                        l26[m26](g26);
                    }
                    catch (o26) {
                        throw new Error('once function callbacks error.');
                    }
                }
                this._once_events[f26] = null;
            }
        }
        else if (this._events[f26]) {
            let h26 = Array.from(this._events[f26]);
            if (h26) {
                for (let i26 = 0, j26 = h26.length; i26 < j26; i26++) {
                    try {
                        h26[i26](g26);
                    }
                    catch (k26) {
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
    constructor(z25, a26, b26, c26 = -1, d26 = undefined, e26) {
        super(z25, b26, c26, e26);
        if (typeof d26 === 'function') {
            this.paramsGenerator_ = d26;
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
        this.__treeViewTheme = new ObservedPropertyObjectPU(TreeViewTheme.getInstance(), this, 'treeViewTheme');
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
        this.setInitiallyProvidedValue(a26);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(y25) {
        if (y25.treeController !== undefined) {
            this.treeController = y25.treeController;
        }
        if (y25.nodeList !== undefined) {
            this.nodeList = y25.nodeList;
        }
        if (y25.listNodeDataSource !== undefined) {
            this.listNodeDataSource = y25.listNodeDataSource;
        }
        if (y25.item !== undefined) {
            this.item = y25.item;
        }
        if (y25.touchCount !== undefined) {
            this.touchCount = y25.touchCount;
        }
        if (y25.dropSelectedIndex !== undefined) {
            this.dropSelectedIndex = y25.dropSelectedIndex;
        }
        if (y25.viewLastIndex !== undefined) {
            this.viewLastIndex = y25.viewLastIndex;
        }
        if (y25.followingSystemFontScale !== undefined) {
            this.followingSystemFontScale = y25.followingSystemFontScale;
        }
        if (y25.maxAppFontScale !== undefined) {
            this.maxAppFontScale = y25.maxAppFontScale;
        }
        if (y25.listItemBgColor !== undefined) {
            this.listItemBgColor = y25.listItemBgColor;
        }
        if (y25.treeViewTheme !== undefined) {
            this.treeViewTheme = y25.treeViewTheme;
        }
        if (y25.listTreeViewMenu !== undefined) {
            this.listTreeViewMenu = y25.listTreeViewMenu;
        }
        if (y25.MAX_CN_LENGTH !== undefined) {
            this.MAX_CN_LENGTH = y25.MAX_CN_LENGTH;
        }
        if (y25.MAX_EN_LENGTH !== undefined) {
            this.MAX_EN_LENGTH = y25.MAX_EN_LENGTH;
        }
        if (y25.INITIAL_INVALID_VALUE !== undefined) {
            this.INITIAL_INVALID_VALUE = y25.INITIAL_INVALID_VALUE;
        }
        if (y25.MAX_TOUCH_DOWN_COUNT !== undefined) {
            this.MAX_TOUCH_DOWN_COUNT = y25.MAX_TOUCH_DOWN_COUNT;
        }
        if (y25.isMultiPress !== undefined) {
            this.isMultiPress = y25.isMultiPress;
        }
        if (y25.touchDownCount !== undefined) {
            this.touchDownCount = y25.touchDownCount;
        }
        if (y25.appEventBus !== undefined) {
            this.appEventBus = y25.appEventBus;
        }
        if (y25.itemPadding !== undefined) {
            this.itemPadding = y25.itemPadding;
        }
        if (y25.textInputPadding !== undefined) {
            this.textInputPadding = y25.textInputPadding;
        }
    }

    updateStateVars(x25) {
    }

    purgeVariableDependenciesOnElmtId(w25) {
        this.__nodeList.purgeDependencyOnElmtId(w25);
        this.__item.purgeDependencyOnElmtId(w25);
        this.__touchCount.purgeDependencyOnElmtId(w25);
        this.__dropSelectedIndex.purgeDependencyOnElmtId(w25);
        this.__viewLastIndex.purgeDependencyOnElmtId(w25);
        this.__followingSystemFontScale.purgeDependencyOnElmtId(w25);
        this.__maxAppFontScale.purgeDependencyOnElmtId(w25);
        this.__listItemBgColor.purgeDependencyOnElmtId(w25);
        this.__treeViewTheme.purgeDependencyOnElmtId(w25);
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
        this.__treeViewTheme.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get nodeList() {
        return this.__nodeList.get();
    }

    set nodeList(v25) {
        this.__nodeList.set(v25);
    }

    get item() {
        return this.__item.get();
    }

    set item(u25) {
        this.__item.set(u25);
    }

    get touchCount() {
        return this.__touchCount.get();
    }

    set touchCount(t25) {
        this.__touchCount.set(t25);
    }

    get dropSelectedIndex() {
        return this.__dropSelectedIndex.get();
    }

    set dropSelectedIndex(s25) {
        this.__dropSelectedIndex.set(s25);
    }

    get viewLastIndex() {
        return this.__viewLastIndex.get();
    }

    set viewLastIndex(r25) {
        this.__viewLastIndex.set(r25);
    }

    get followingSystemFontScale() {
        return this.__followingSystemFontScale.get();
    }

    set followingSystemFontScale(q25) {
        this.__followingSystemFontScale.set(q25);
    }

    get maxAppFontScale() {
        return this.__maxAppFontScale.get();
    }

    set maxAppFontScale(p25) {
        this.__maxAppFontScale.set(p25);
    }

    get listItemBgColor() {
        return this.__listItemBgColor.get();
    }

    set listItemBgColor(o25) {
        this.__listItemBgColor.set(o25);
    }

    get treeViewTheme() {
        return this.__treeViewTheme.get();
    }

    set treeViewTheme(n25) {
        this.__treeViewTheme.set(n25);
    }

    NullBuilder(m25 = null) {
    }

    onWillApplyTheme(l25) {
        this.treeViewTheme.itemSelectedBgColor = l25.colors.interactiveSelect;
        this.treeViewTheme.itemPressedBgColor = l25.colors.interactivePressed;
        this.treeViewTheme.itemHoverBgColor = l25.colors.interactiveHover;
        this.treeViewTheme.primaryTitleFontColor = l25.colors.fontPrimary;
        this.treeViewTheme.secondaryTitleFontColor = l25.colors.fontSecondary;
        this.treeViewTheme.primaryTitleActiveFontColor = l25.colors.interactiveActive;
        this.treeViewTheme.borderFocusedColor = l25.colors.interactiveFocus;
        this.treeViewTheme.leftIconColor = l25.colors.iconSecondary;
        this.treeViewTheme.leftIconActiveColor = l25.colors.interactiveActive;
        this.treeViewTheme.arrowIconColor = l25.colors.iconPrimary;
        this.treeController.treeViewTheme = this.treeViewTheme;
    }

    aboutToAppear() {
        if (this.treeController !== null) {
            this.listNodeDataSource = this.treeController.getListNodeDataSource();
            this.nodeList = this.treeController.getListNodeDataSource().listNode;
            this.item = this.treeController.getListNodeDataSource().listNode;
        }
        let k25 = this.getUIContext();
        this.followingSystemFontScale = k25.isFollowingSystemFontScale();
        this.maxAppFontScale = k25.getMaxFontScale();
    }

    decideFontScale() {
        let i25 = this.getUIContext();
        let j25 = i25.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.followingSystemFontScale) {
            return 1;
        }
        return Math.min(j25, this.maxAppFontScale, MAX_FONT_SCALE);
    }

    popupForShowTitle(y24, z24, a25, b25 = null) {
        this.observeComponentCreation((g25, h25) => {
            ViewStackProcessor.StartGetAccessRecordingFor(g25);
            Row.create();
            Row.backgroundColor(z24);
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
            if (!h25) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((e25, f25) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e25);
            Text.create(y24);
            Text.fontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_body2'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            });
            Text.fontWeight('regular');
            Text.fontColor(a25);
            Text.minFontScale(MIN_FONT_SCALE);
            Text.maxFontScale(this.decideFontScale());
            if (!f25) {
                Text.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        Text.pop();
        Row.pop();
    }

    builder(x24 = null) {
        this.listTreeViewMenu.bind(this)(x24 ? x24 : this);
    }

    draggingPopup(w23, x23 = null) {
        this.observeComponentCreation((v24, w24) => {
            ViewStackProcessor.StartGetAccessRecordingFor(v24);
            Row.create();
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
            if (!w24) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((l24, m24) => {
            ViewStackProcessor.StartGetAccessRecordingFor(l24);
            If.create();
            if (w23.getNodeItem().imageNode) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((t24, u24) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(t24);
                        Row.create();
                        Row.backgroundColor(COLOR_IMAGE_ROW);
                        Row.margin({
                            end: getLengthMetricsByResourceOrNumber(w23.getNodeItem().imageNode?.itemRightMargin)
                        });
                        Row.height(w23.getNodeItem().imageNode?.itemHeight);
                        Row.width(w23.getNodeItem().imageNode?.itemWidth);
                        if (!u24) {
                            Row.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((r24, s24) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(r24);
                        Image.create(w23.getNodeItem().imageNode?.normalSource);
                        Image.objectFit(ImageFit.Contain);
                        Image.height(w23.getNodeItem().imageNode?.itemHeight);
                        Image.width(w23.getNodeItem().imageNode?.itemWidth);
                        Image.opacity(this.listNodeDataSource.getDragPopupPara().imageOpacity);
                        Image.matchTextDirection((w23.getNodeItem().imageCollapse?.collapseSource === ARROW_RIGHT || w23.getNodeItem()
                            .imageCollapse?.collapseSource === ARROW_RIGHT_WITHE) ? true : false);
                        if (!s24) {
                            Image.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    Row.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!m24) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        this.observeComponentCreation((j24, k24) => {
            ViewStackProcessor.StartGetAccessRecordingFor(j24);
            Row.create();
            Row.constraintSize({
                minWidth: w23.getNodeItem().imageNode ?
                this.listNodeDataSource.getDragPopupPara().textConstraintSize.minWidth1 :
                this.listNodeDataSource.getDragPopupPara().textConstraintSize.minWidth2,
                maxWidth: w23.getNodeItem().imageNode ?
                this.listNodeDataSource.getDragPopupPara().textConstraintSize.maxWidth1 :
                this.listNodeDataSource.getDragPopupPara().textConstraintSize.maxWidth2,
            });
            if (!k24) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((c24, d24) => {
            ViewStackProcessor.StartGetAccessRecordingFor(c24);
            If.create();
            if (w23.getNodeItem().mainTitleNode && w23.getIsShowTitle()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((h24, i24) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(h24);
                        Text.create(w23.getNodeItem().mainTitleNode?.title);
                        Text.maxLines(1);
                        Text.minFontScale(MIN_FONT_SCALE);
                        Text.maxFontScale(this.decideFontScale());
                        Text.fontSize(w23.getNodeItem().mainTitleNode?.size);
                        Text.fontColor(this.listNodeDataSource.getDragPopupPara().fontColor);
                        Text.fontWeight(this.listNodeDataSource.getDragPopupPara().fontWeight);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        if (!i24) {
                            Text.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    Text.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!d24) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        Row.pop();
        Row.pop();
    }

    clearLastIndexColor() {
        if (this.viewLastIndex === -1 || this.viewLastIndex >= this.nodeList.length) {
            return;
        }
        this.setImageSources(this.viewLastIndex, InteractionStatus.NORMAL);
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
        this.listNodeDataSource.setImageSource(this.viewLastIndex, InteractionStatus.NORMAL);
    }

    setImageSources(t23, u23) {
        let v23 = this.nodeList[t23];
        v23.setIsSelected(u23 === InteractionStatus.SELECTED ||
            u23 === InteractionStatus.EDIT || u23 === InteractionStatus.FINISH_EDIT);
        if (v23.getNodeItem().mainTitleNode !== null && u23 !== InteractionStatus.DRAG_INSERT &&
            u23 !== InteractionStatus.FINISH_DRAG_INSERT) {
            v23.getNodeItem().mainTitleNode?.setMainTitleSelected(u23 === InteractionStatus.SELECTED ||
                u23 === InteractionStatus.FINISH_EDIT);
        }
        if (v23.getNodeItem().imageNode !== null) {
            v23.getNodeItem().imageNode?.setImageSource(u23);
        }
    }

    initialRender() {
        this.observeComponentCreation((h22, i22) => {
            ViewStackProcessor.StartGetAccessRecordingFor(h22);
            List.create({});
            List.onDragMove((k23, l23) => {
                if (this.isMultiPress) {
                    hilog.error(0x3900, 'TreeView', 'drag error, a item has been dragged');
                    return;
                }
                let m23 = LIST_ITEM_HEIGHT;
                let n23 = Math.floor(k23.getY() /
                    (m23 / FLAG_NUMBER)) %
                    FLAG_NUMBER ? Flag.DOWN_FLAG : Flag.UP_FLAG;
                let o23 = JSON.parse(l23).insertIndex;
                let p23 = false;
                if (o23 >= this.listNodeDataSource.totalCount()) {
                    n23 = Flag.DOWN_FLAG;
                    o23 = this.listNodeDataSource.totalCount() - 1;
                    this.listNodeDataSource.getData(o23)?.setIsOverBorder(true);
                    p23 = true;
                }
                else {
                    this.listNodeDataSource.getData(o23)?.setIsOverBorder(false);
                }
                let q23 = this.listNodeDataSource.getData(o23);
                let r23 = q23?.getNodeCurrentNodeId();
                if (o23 !== this.listNodeDataSource.getLastPassIndex() && this.listNodeDataSource.getIsInnerDrag()) {
                    let s23 = this.listNodeDataSource.getIsParentOfInsertNode(r23);
                    if (s23) {
                        this.listNodeDataSource.setPassIndex(o23);
                        if (r23 !== undefined) {
                            this.listNodeDataSource.clearTimeOutAboutDelayHighLightAndExpand(this.listNodeDataSource.findIndex(r23));
                        }
                        this.listNodeDataSource.setFlag(Flag.NONE);
                        return;
                    }
                }
                this.listNodeDataSource.setLastPassIndex(o23);
                this.listNodeDataSource.setVisibility(n23, o23 - 1, p23);
                if (r23 !== undefined && r23 !== this.listNodeDataSource.getDraggingCurrentNodeId()) {
                    this.listNodeDataSource.delayHighLightAndExpandNode(this.listNodeDataSource.findIndex(r23), r23, o23);
                }
            });
            List.onDragEnter((h23, i23) => {
                if (this.listNodeDataSource.getIsInnerDrag()) {
                    this.listNodeDataSource.setIsDrag(true);
                    let j23 = DRAG_OPACITY;
                    this.listNodeDataSource.setListItemOpacity(j23);
                }
            });
            List.onDragLeave((e23, f23) => {
                this.listNodeDataSource.hideLastLine();
                this.listNodeDataSource.clearLastTimeoutHighLight();
                this.listNodeDataSource.clearLastTimeoutExpand();
                let g23 = DRAG_OPACITY_NONE;
                this.listNodeDataSource.setListItemOpacity(g23);
                this.listNodeDataSource.setIsDrag(false);
                this.listNodeDataSource.notifyDataReload();
            });
            List.onDrop((n22, o22) => {
                this.listNodeDataSource.clearLastTimeoutExpand();
                let p22 = DRAG_OPACITY_NONE;
                this.listNodeDataSource.setListItemOpacity(p22);
                let q22 = JSON.parse(o22).insertIndex;
                let r22 = this.dropSelectedIndex;
                if (r22 - 1 > this.listNodeDataSource.totalCount() || r22 === undefined) {
                    hilog.error(0x3900, 'TreeView', 'drag error, currentNodeIndex is not found');
                    this.listNodeDataSource.setIsDrag(false);
                    return;
                }
                if (q22 === this.listNodeDataSource.totalCount()) {
                    hilog.info(0x3900, 'TreeView', 'need to insert into the position of the last line');
                    q22 -= 1;
                }
                let s22 = this.listNodeDataSource.getData(q22);
                if (s22 === undefined) {
                    return;
                }
                let t22 = s22.getNodeCurrentNodeId();
                if (!this.listNodeDataSource.getIsDrag() || !this.listNodeDataSource.getIsInnerDrag()) {
                    this.listNodeDataSource.clearLastTimeoutHighLight();
                    this.listNodeDataSource.setIsInnerDrag(false);
                    this.listNodeDataSource.hideLastLine();
                    this.listNodeDataSource.initialParameterAboutDelayHighLightAndExpandIndex();
                    this.listNodeDataSource.refreshSubtitle(t22);
                    this.listNodeDataSource.notifyDataReload();
                    return;
                }
                let u22 = this.listNodeDataSource.getCurrentNodeInfo();
                let v22 = s22.getNodeParentNodeId();
                let w22 = this.listNodeDataSource.getDraggingCurrentNodeId();
                let x22 = this.listNodeDataSource.getDraggingParentNodeId();
                let y22 = this.listNodeDataSource.getIsParentOfInsertNode(t22);
                if (y22) {
                    this.listNodeDataSource.clearLastTimeoutHighLight();
                    this.listNodeDataSource.setIsInnerDrag(false);
                    this.listNodeDataSource.hideLastLine();
                    this.listNodeDataSource.notifyDataChange(q22);
                    this.listNodeDataSource.initialParameterAboutDelayHighLightAndExpandIndex();
                    this.listNodeDataSource.setIsDrag(false);
                    let d23 = this.listNodeDataSource.findIndex(w22);
                    this.listNodeDataSource.setClickIndex(d23);
                    this.listNodeDataSource.handleEvent(Event.DRAG, d23);
                    return;
                }
                if (this.listNodeDataSource.getExpandAndCollapseInfo(w22) === NodeStatus.EXPAND) {
                    this.listNodeDataSource.expandAndCollapseNode(this.listNodeDataSource.findIndex(w22));
                }
                let z22 = false;
                if (this.listNodeDataSource.getExpandAndCollapseInfo(t22) === NodeStatus.COLLAPSE) {
                    let c23 = this.listNodeDataSource.findIndex(t22);
                    if (this.listNodeDataSource.listNode[c23].getIsHighLight()) {
                        this.listNodeDataSource.expandAndCollapseNode(c23);
                    }
                    z22 = true;
                }
                this.listNodeDataSource.setLastDelayHighLightId();
                if (u22 !== null && w22 !== t22) {
                    this.listNodeDataSource.alterDragNode(v22, t22, x22, w22, u22);
                    this.listNodeDataSource.hideLastLine();
                }
                else {
                    this.listNodeDataSource.hideLastLine();
                    this.listNodeDataSource.setLastPassId(w22);
                    this.listNodeDataSource.hideLastLine();
                }
                let a23 = this.listNodeDataSource.findIndex(this.listNodeDataSource.getLastDelayHighLightId());
                this.listNodeDataSource.setLastDelayHighLightIndex(a23);
                this.listNodeDataSource.clearLastTimeoutHighLight();
                this.listNodeDataSource.initialParameterAboutDelayHighLightAndExpandIndex();
                this.listNodeDataSource.setIsDrag(false);
                let b23 = this.listNodeDataSource.findIndex(w22);
                this.listNodeDataSource.setClickIndex(b23);
                this.listNodeDataSource.handleEvent(Event.DRAG, b23);
                this.listNodeDataSource.setIsInnerDrag(false);
                this.listNodeDataSource.notifyDataReload();
                this.listNodeDataSource.listNode[b23].fontColor = this.treeViewTheme.primaryTitleActiveFontColor;
                if (this.viewLastIndex !== -1 && r22 !== this.viewLastIndex) {
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
                            .imageNode?.setImageSource(InteractionStatus.NORMAL);
                        this.listNodeDataSource.listNode[this.viewLastIndex].imageSource =
                            this.listNodeDataSource.listNode[this.viewLastIndex].getNodeItem()
                                .imageNode?.source;
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
                this.listNodeDataSource.lastIndex = b23;
            });
            if (!i22) {
                List.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        {
            const v20 = a21 => {
                const b21 = a21;
                {
                    const c21 = (f22, g22) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(f22);
                        d21(f22, g22);
                        if (!g22) {
                            ListItem.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    };
                    const d21 = (v21, w21) => {
                        ListItem.create(() => {
                        }, false);
                        ListItem.width('100%');
                        ListItem.height(b21.getListItemHeight());
                        ListItem.padding({
                            start: LengthMetrics.resource(this.itemPadding.left),
                            end: LengthMetrics.resource(this.itemPadding.right)
                        });
                        ListItem.align(Alignment.Start);
                        ListItem.onDragStart((z21, a22) => {
                            if (this.listNodeDataSource.getIsDrag() || this.listNodeDataSource.getIsInnerDrag() || this.isMultiPress) {
                                hilog.error(0x3900, 'TreeView', 'drag error, a item has been dragged');
                                return;
                            }
                            this.dropSelectedIndex = JSON.parse(a22).selectedIndex;
                            let b22 = JSON.parse(a22).selectedIndex;
                            let c22 = this.listNodeDataSource.getData(b22);
                            let d22 = b21.getNodeCurrentNodeId();
                            if (b22 >= this.listNodeDataSource.totalCount() || b22 === undefined) {
                                hilog.error(0x3900, 'TreeView', 'drag error, currentNodeIndex is not found in onDragStart');
                                return;
                            }
                            this.listNodeDataSource.setIsInnerDrag(true);
                            this.listNodeDataSource.setIsDrag(true);
                            this.listNodeDataSource.setCurrentNodeInfo(c22);
                            this.listNodeDataSource.setDraggingCurrentNodeId(c22?.getNodeCurrentNodeId());
                            this.listNodeDataSource.setDraggingParentNodeId(c22?.getNodeParentNodeId());
                            let e22 = DRAG_OPACITY;
                            this.listNodeDataSource.setListItemOpacity(e22);
                            this.listNodeDataSource.notifyDataChange(b22);
                            if (d22 !== c22?.getNodeCurrentNodeId()) {
                                hilog.error(0x3900, 'TreeView', 'drag is too fast, it attribute a fault to OH');
                                this.listNodeDataSource.setIsDrag(false);
                                return;
                            }
                            return { builder: () => {
                                this.draggingPopup.call(this, c22);
                            } };
                        });
                    };
                    const e21 = () => {
                        this.observeComponentCreation(c21);
                        this.observeComponentCreation((q21, r21) => {
                            ViewStackProcessor.StartGetAccessRecordingFor(q21);
                            Row.create();
                            Row.onTouch((t21) => {
                                this.viewLastIndex = this.listNodeDataSource.getLastIndex();
                                let u21 = this.listNodeDataSource.findIndex(b21.getNodeCurrentNodeId());
                                if (t21.type === TouchType.Down) {
                                    if (u21 !== this.viewLastIndex) {
                                        this.clearLastIndexColor();
                                        this.listNodeDataSource.lastIndex = u21;
                                        this.listNodeDataSource.setClickIndex(u21);
                                    }
                                }
                                if (t21.type === TouchType.Up) {
                                    this.listNodeDataSource.listNode[u21].setIsSelected(true);
                                    this.listNodeDataSource.setImageSource(u21, InteractionStatus.SELECTED);
                                    if (this.listNodeDataSource.listNode[u21].getNodeItem().imageNode !== null) {
                                        this.listNodeDataSource.listNode[u21].imageSource = this.listNodeDataSource.listNode[u21]
                                            .getNodeItem().imageNode?.source;
                                    }
                                    if (u21 !== this.viewLastIndex) {
                                        this.clearLastIndexColor();
                                        this.listNodeDataSource.lastIndex = u21;
                                        this.listNodeDataSource.setClickIndex(u21);
                                    }
                                    this.viewLastIndex = u21;
                                }
                                if (this.listNodeDataSource.getLastIndex() !== -1 && u21 !== this.listNodeDataSource.getLastIndex()) {
                                    this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false, this.listNodeDataSource.getLastIndex());
                                    this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(), MenuOperation.COMMIT_NODE);
                                }
                            });
                            if (!r21) {
                                Row.pop();
                            }
                            ViewStackProcessor.StopGetAccessRecording();
                        });
                        {
                            this.observeComponentCreation((k21, l21) => {
                                ViewStackProcessor.StartGetAccessRecordingFor(k21);
                                if (l21) {
                                    let m21 = new TreeViewInner(this, {
                                        item: b21,
                                        listNodeDataSource: this.listNodeDataSource,
                                        index: this.listNodeDataSource.findIndex(b21.getNodeCurrentNodeId()),
                                        listTreeViewMenu: this.listTreeViewMenu,
                                    }, undefined, k21, () => {
                                    }, {
                                        page: 'library/src/main/ets/components/mainpage/MainPage.ets',
                                        line: 1130,
                                        col: 13
                                    });
                                    ViewPU.create(m21);
                                    let n21 = () => {
                                        return {
                                            item: b21,
                                            listNodeDataSource: this.listNodeDataSource,
                                            index: this.listNodeDataSource.findIndex(b21.getNodeCurrentNodeId()),
                                            listTreeViewMenu: this.listTreeViewMenu
                                        };
                                    };
                                    m21.paramsGenerator_ = n21;
                                }
                                else {
                                    this.updateStateVarsOfChildByElmtId(k21, {
                                        item: b21
                                    });
                                }
                                ViewStackProcessor.StopGetAccessRecording();
                            });
                        }
                        Row.pop();
                        ListItem.pop();
                    };
                    e21();
                }
            };
            const w20 = (z20) => JSON.stringify(z20);
            LazyForEach.create('1', this, this.listNodeDataSource, v20, w20);
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
        let t20 = this.listNodeDataSource.getClickNodeId();
        return this.listNodeDataSource.getClickNodeChildrenInfo(t20);
    }

    getChildrenId() {
        let s20 = this.listNodeDataSource.getClickNodeId();
        return this.listNodeDataSource.getClickChildId(s20);
    }

    removeNode() {
        let p20 = this.listNodeDataSource.getClickNodeId();
        if (p20 < 0) {
            return;
        }
        let q20 = this.listNodeDataSource.findParentNodeId(p20);
        let r20 = this.listNodeDataSource.removeNode(p20, q20);
        this.listNodeDataSource.refreshData(MenuOperation.REMOVE_NODE, q20, r20);
        this.nodeIdList.splice(this.nodeIdList.indexOf(p20), 1);
        this.listNodeDataSource.lastIndex = -1;
    }

    modifyNode() {
        let o20 = this.listNodeDataSource.getClickNodeId();
        this.listNodeDataSource.setItemVisibilityOnEdit(o20, MenuOperation.MODIFY_NODE);
    }

    add(j20) {
        let k20 = this.listNodeDataSource.getClickNodeId();
        if (k20 === this.listNodeDataSource.ROOT_NODE_ID || !this.listNodeDataSource.getIsFolder(k20)) {
            return;
        }
        let l20 = this.listNodeDataSource.getNewNodeParam(k20);
        this.nodeIdList.push(this.nodeIdList[this.nodeIdList.length - 1] + 1);
        let m20 = this.nodeIdList[this.nodeIdList.length - 1];
        let t27 = this.listNodeDataSource.addNode(k20, m20, {
            isFolder: l20.isFolder,
            icon: l20.icon,
            selectedIcon: l20.selectedIcon,
            editIcon: l20.editIcon,
            primaryTitle: '新建文件夹',
            container: l20.container,
            secondaryTitle: l20.secondaryTitle,
        }, j20);
        if (!t27) {
            return;
        }
        this.listNodeDataSource.refreshData(MenuOperation.ADD_NODE, k20, [m20]);
        this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false, this.listNodeDataSource.getLastIndex());
        this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(), MenuOperation.COMMIT_NODE);
        this.listNodeDataSource.listNode[this.listNodeDataSource.getLastIndex()]
            .setFontColor(this.treeViewTheme.primaryTitleFontColor);
        let n20 = this.listNodeDataSource.findIndex(m20);
        this.listNodeDataSource.setClickIndex(n20);
        this.listNodeDataSource.handleEvent(Event.TOUCH_UP, n20);
    }

    addNode(h20) {
        if (h20 === undefined) {
            this.add(this.initBuild);
            return this;
        }
        else {
            let r27 = false;
            if (h20.primaryTitle !== undefined &&
                !this.listNodeDataSource.checkMainTitleIsValid(h20.primaryTitle.toString())) {
                throw new Error('ListTreeNode[addNode]: ' +
                    'The directory name cannot contain the following characters\ /: *? "< > | or exceeds the maximum length.');
                return this;
            }
            if (h20.primaryTitle === null && h20.icon === null) {
                throw new Error('ListTreeNode[addNode]: ' +
                    'The icon and directory name cannot be empty at the same time.');
                return this;
            }
            if (h20.currentNodeId === this.ROOT_NODE_ID || h20.currentNodeId === null) {
                throw new Error('ListTreeNode[addNode]: currentNodeId can not be -1 or null.');
                return this;
            }
            if (h20.currentNodeId !== undefined) {
                this.nodeIdList.push(h20.currentNodeId);
            }
            if (h20.parentNodeId !== undefined) {
                if (h20.currentNodeId !== undefined) {
                    r27 = this.listNodeDataSource.addNode(h20.parentNodeId, h20.currentNodeId, h20, this.initBuild);
                }
            }
            if (!r27) {
                return this;
            }
            if (!this.initBuild && h20.parentNodeId !== undefined) {
                let i20 = this.nodeIdList[this.nodeIdList.length - 1];
                this.listNodeDataSource.refreshData(MenuOperation.ADD_NODE, h20.parentNodeId, [i20]);
            }
            return this;
        }
    }

    refreshNode(e20, f20, g20) {
        this.listNodeDataSource.setNodeSubtitlePara(e20, f20, g20);
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

    getData(d20) {
        return undefined;
    }

    registerDataChangeListener(c20) {
        if (this.listeners.indexOf(c20) < 0) {
            this.listeners.push(c20);
        }
    }

    unregisterDataChangeListener(a20) {
        const b20 = this.listeners.indexOf(a20);
        if (b20 >= 0) {
            this.listeners.splice(b20, 1);
        }
    }

    notifyDataReload() {
        this.listeners.forEach(z19 => {
            z19.onDataReloaded();
        });
    }

    notifyDataAdd(v19) {
        this.listeners.forEach(x19 => {
            x19.onDataAdd(v19);
        });
    }

    notifyDataChange(s19) {
        if (s19 === undefined) {
            return;
        }
        this.listeners.forEach(u19 => {
            u19.onDataChange(s19);
        });
    }

    notifyDataDelete(p19) {
        this.listeners.forEach(r19 => {
            r19.onDataDelete(p19);
        });
    }

    notifyDataMove(l19, m19) {
        this.listeners.forEach(o19 => {
            o19.onDataMove(l19, m19);
        });
    }
}

function delayUpdateParentChildNum(b24, b25, f25, w25) {
    let j27 = setTimeout(() => {
        w25.forEach((m27) => {
            updateParentChildNumHandler(m27, f25, b24, b25);
        });
        clearTimeout(j27);
    }, DELAY_TIME);
}

function updateParentChildNumHandler(m8, u8, v8, y16) {
    let z16 = m8;
    while (z16 >= 0) {
        if (u8.has(z16)) {
            let a18 = u8.get(z16);
            a18.getChildNodeInfo().allChildNum =
                v8 ? a18.getChildNodeInfo().allChildNum + y16 : a18.getChildNodeInfo().allChildNum - y16;
            z16 = a18.parentNodeId;
        }
        else {
            hilog.error(0x3900, 'TreeView', 'updateParentChildNumHandler: parent node not found');
            break;
        }
    }
}

function delaySortNodeIdList(v18) {
    let w18 = setTimeout(() => {
        v18.sort((z18, a19) => z18 - a19);
        clearTimeout(w18);
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
        this._root.nodeLevel = -1;
        this.nodeIdNodeItemMap.set(-1, this._root);
        this.nodeIdNodeParamMap.set(-1, emptyNodeInfo);
    }

    checkIndex(j11) {
        if (j11 < 0 || j11 >= this.listNode.length) {
            hilog.error(0x3900, 'TreeView', 'check index fail');
            return false;
        }
        return true;
    }

    changeNodeColor(t18, u18) {
        if (!this.checkIndex(t18)) {
            return;
        }
        this.listNode[t18].setNodeColor(u18);
        this.listNode[t18].setNodeBorder(false);
    }

    getNodeColor(s18) {
        return this.listNode[s18].getNodeColor();
    }

    handleFocusEffect(q18, r18) {
        if (this.listNode[q18].getNodeIsShow()) {
            this.listNode[q18].setNodeBorder(r18);
        }
    }

    setImageSource(n18, o18) {
        if (!this.checkIndex(n18)) {
            return;
        }
        let p18 = this.listNode[n18];
        p18.setIsSelected(o18 === InteractionStatus.SELECTED ||
            o18 === InteractionStatus.EDIT || o18 === InteractionStatus.FINISH_EDIT);
        if (p18.getNodeItem().mainTitleNode !== null && o18 !== InteractionStatus.DRAG_INSERT &&
            o18 !== InteractionStatus.FINISH_DRAG_INSERT) {
            p18.getNodeItem().mainTitleNode?.setMainTitleSelected(o18 === InteractionStatus.SELECTED ||
                o18 === InteractionStatus.FINISH_EDIT);
        }
        if (p18.getNodeItem().imageNode !== null) {
            p18.getNodeItem().imageNode?.setImageSource(o18);
        }
    }

    setImageCollapseSource(k18, l18) {
        let m18 = this.listNode[k18];
        if (m18.getNodeItem().imageCollapse !== undefined) {
            m18.getNodeItem().imageCollapse = CollapseImageNodeFlyweightFactory.getCollapseImageNode(l18, this.expandAndCollapseInfo.get(m18.getNodeCurrentNodeId()), m18.getNodeItem().imageCollapse.type);
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
        let i18 = 0;
        this.loadedNodeIdAndIndexMap.clear();
        this.nodeIdAndNodeIndexMap.clear();
        this.loadedListNode.splice(0, this.loadedListNode.length);
        for (let j18 = 0; j18 < this.listNode.length; j18++) {
            this.nodeIdAndNodeIndexMap.set(this.listNode[j18].getNodeCurrentNodeId(), j18);
            if (this.listNode[j18].getNodeIsShow()) {
                this.loadedNodeIdAndIndexMap.set(this.listNode[j18].getNodeCurrentNodeId(), i18++);
                this.loadedListNode.push(this.listNode[j18]);
            }
        }
    }

    changeNodeStatus(f18) {
        if (f18 >= this.listNode.length) {
            hilog.error(0x3900, 'TreeView', 'changeNodeStatus clickIndex error.');
            return;
        }
        let g18 = f18;
        let h18 = this.listNode[f18].getNodeCurrentNodeId();
        if (this.expandAndCollapseInfo.get(h18) === NodeStatus.EXPAND) {
            this.expandAndCollapseInfo.set(h18, NodeStatus.COLLAPSE);
            this.listNode[g18].getNodeItem().imageCollapse = this.listNode[g18].getNodeItem().imageCollapse ?
            CollapseImageNodeFlyweightFactory.changeImageCollapseSource(NodeStatus.COLLAPSE, this.listNode[g18].getNodeItem().imageCollapse.isCollapse) : undefined;
        }
        else if (this.expandAndCollapseInfo.get(h18) === NodeStatus.COLLAPSE) {
            this.expandAndCollapseInfo.set(h18, NodeStatus.EXPAND);
            this.listNode[g18].getNodeItem().imageCollapse = this.listNode[g18].getNodeItem().imageCollapse ?
            CollapseImageNodeFlyweightFactory.changeImageCollapseSource(NodeStatus.EXPAND, this.listNode[g18].getNodeItem().imageCollapse.isCollapse) : undefined;
        }
    }

    handleExpandAndCollapse(v17, w17) {
        if (v17 >= this.listNode.length) {
            hilog.error(0x3900, 'TreeView', 'handleExpandAndCollapse clickIndex error.');
            return;
        }
        let x17 = v17;
        let y17 = this.listNode[x17].getNodeCurrentNodeId();
        if (!this.expandAndCollapseInfo.has(y17)) {
            return;
        }
        let z17 = this.expandAndCollapseInfo.get(y17);
        if (this.listNode[x17].getChildNodeInfo().isHasChildNode && z17 === NodeStatus.COLLAPSE) {
            for (let e18 = 0; e18 < this.listNode[x17].getChildNodeInfo().allChildNum; e18++) {
                this.listNode[x17 + 1 + e18].setNodeIsShow(false);
                this.listNode[x17 + 1 + e18].setListItemHeight(LIST_ITEM_HEIGHT_NONE);
            }
            this.loadedListNodeFunction();
            this.notifyDataReload();
            return;
        }
        let a18 = new Array(this.listNode[x17].getChildNodeInfo().childNum);
        a18[0] = x17 + 1;
        let b18 = 1;
        while (b18 < this.listNode[x17].getChildNodeInfo().childNum) {
            a18[b18] = a18[b18 - 1] + this.listNode[a18[b18 - 1]].getChildNodeInfo().allChildNum + 1;
            b18++;
        }
        if (z17 === NodeStatus.EXPAND) {
            for (let c18 = 0; c18 < a18.length; c18++) {
                this.listNode[a18[c18]].setNodeIsShow(true);
                this.listNode[a18[c18]].setListItemHeight(LIST_ITEM_HEIGHT);
                let d18 = this.listNode[a18[c18]].getNodeCurrentNodeId();
                if (this.expandAndCollapseInfo.get(d18) === NodeStatus.EXPAND) {
                    this.handleExpandAndCollapse(a18[c18], false);
                }
            }
        }
        a18 = null;
        if (w17) {
            this.loadedListNodeFunction();
            this.notifyDataReload();
        }
    }

    updateAllChildNum() {
        delayUpdateParentChildNum(true, 1, this.nodeIdNodeItemMap, this.updateNodeIdList);
    }

    resetData(q27) {
        q27.splice(0, q27.length);
        this.loadedNodeIdAndIndexMap.clear();
        this.loadedListNode.splice(0, this.loadedListNode.length);
        this.nodeIdAndNodeIndexMap.clear();
        this.nodeIdAndSubtitleMap.clear();
    }

    initHandler(n17, o17, p17) {
        let q17 = 0;
        let r17 = 0;
        this.resetData(n17);
        try {
            this.traverseSectionNodeDF((t17) => {
                if (t17.getCurrentNodeId() >= 0 && this.nodeIdNodeParamMap.has(t17.getCurrentNodeId())) {
                    let u17 = new NodeInfo(t17, this.nodeIdNodeParamMap.get(t17.getCurrentNodeId()));
                    u17.addImageCollapse(t17.getChildNodeInfo().isHasChildNode);
                    n17.push(u17);
                    this.nodeIdAndNodeIndexMap.set(u17.getNodeCurrentNodeId(), r17++);
                    if (u17.getChildNodeInfo().isHasChildNode) {
                        this.expandAndCollapseInfo.set(u17.getNodeCurrentNodeId(), NodeStatus.COLLAPSE);
                    }
                    if (u17.getNodeIsShow()) {
                        this.loadedNodeIdAndIndexMap.set(u17.getNodeCurrentNodeId(), q17++);
                        this.loadedListNode.push(u17);
                    }
                    if (u17.getIsFolder()) {
                        if (u17.getNodeInfoData().secondaryTitle !== undefined) {
                            this.nodeIdAndSubtitleMap.set(u17.getNodeCurrentNodeId(), u17.getNodeInfoData().secondaryTitle);
                        }
                        else {
                            this.nodeIdAndSubtitleMap.set(u17.getNodeCurrentNodeId(), '');
                        }
                    }
                }
                return false;
            }, this._root, o17, p17);
        }
        catch (g19) {
            hilog.error(0x3900, 'TreeView', 'traverseSectionNodeDF function callbacks error.');
            this.resetData(n17);
        }
    }

    delayInit() {
        let h17 = setTimeout(() => {
            let j17 = [];
            this.initHandler(j17, 0);
            this.listNode.splice(0, this.listNode.length);
            this.listNode.push(...j17);
            this.listNode.forEach((l17, m17) => {
                this.notifyDataDelete(m17);
                this.notifyDataAdd(m17);
            });
            clearTimeout(h17);
        }, DELAY_TIME);
    }

    initSection() {
        this.initHandler(this.listNode, 0, 1);
    }

    refreshRemoveNodeData(w16, x16) {
        let y16 = [];
        if (w16.length === 0) {
            return;
        }
        let z16 = undefined;
        for (let e17 = 0; e17 < w16.length; e17++) {
            if (this.loadedNodeIdAndIndexMap.has(w16[e17])) {
                let g17 = this.loadedNodeIdAndIndexMap.get(w16[e17]);
                y16.push(g17);
            }
            if (z16 === undefined && this.nodeIdAndNodeIndexMap.has(w16[e17])) {
                z16 = this.nodeIdAndNodeIndexMap.get(w16[e17]);
            }
            if (z16 !== undefined) {
                let f17 = this.listNode.splice(z16, 1);
                f17 = null;
            }
            if (this.expandAndCollapseInfo.has(w16[e17])) {
                this.expandAndCollapseInfo.delete(w16[e17]);
            }
        }
        y16.forEach((d17) => {
            this.notifyDataDelete(d17);
            this.notifyDataChange(d17);
        });
        if (x16.getNodeItem().imageCollapse === null) {
            if (this.nodeIdAndNodeIndexMap.has(x16.getNodeCurrentNodeId())) {
                let c17 = this.nodeIdAndNodeIndexMap.get(x16.getNodeCurrentNodeId());
                this.listNode[c17]?.handleImageCollapseAfterAddNode(false);
            }
            this.expandAndCollapseInfo.delete(x16.getNodeCurrentNodeId());
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(x16.getNodeCurrentNodeId()));
        }
        let a17 = {
            currentNodeId: x16.getNodeCurrentNodeId(),
            parentNodeId: x16.getNodeParentNodeId(),
        };
        this.loadedListNodeFunction();
        this.appEventBus.emit(TreeListenType.NODE_DELETE, a17);
    }

    refreshAddNodeData(r16) {
        let s16 = new NodeInfo(new NodeItem(emptyNodeInfo), emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(r16[0])) {
            let v16 = this.nodeIdNodeItemMap.get(r16[0]);
            s16 = new NodeInfo(v16, this.nodeIdNodeParamMap.get(r16[0]));
            s16.addImageCollapse(v16.getChildNodeInfo().isHasChildNode);
        }
        s16.setIsModify(true);
        let t16 = 0;
        for (let u16 = 0; u16 < this.listNode.length; u16++) {
            if (this.listNode[u16].getNodeCurrentNodeId() === s16.getNodeParentNodeId()) {
                t16 = u16;
                if (this.listNode[u16].getNodeItem().imageCollapse === null) {
                    this.listNode[u16].handleImageCollapseAfterAddNode(true);
                    this.notifyDataChange(t16);
                }
                else if (this.expandAndCollapseInfo.get(this.listNode[u16].getNodeCurrentNodeId()) === NodeStatus.COLLAPSE) {
                    this.changeNodeStatus(t16);
                }
                this.listNode.splice(u16 + 1, 0, s16);
                this.listNode[u16 + 1].setTitleAndInputTextStatus(true);
                this.listNode[u16 + 1].setNodeIsShow(true);
                this.listNode[u16 + 1].setListItemHeight(LIST_ITEM_HEIGHT);
                this.nodeIdAndNodeIndexMap.set(r16[0], u16 + 1);
                this.setImageSource(u16 + 1, InteractionStatus.EDIT);
                this.currentOperation = MenuOperation.ADD_NODE;
                this.notifyDataAdd(u16 + 1);
                this.notificationNodeInfo(u16 + 1, this.currentOperation);
                break;
            }
        }
        this.modifyNodeIndex = t16 + 1;
        this.setClickIndex(t16);
        this.lastIndex = t16;
        this.expandAndCollapseInfo.set(s16.getNodeParentNodeId(), NodeStatus.EXPAND);
        this.handleExpandAndCollapse(t16, true);
    }

    refreshData(m16, n16, o16) {
        let p16 = new NodeInfo(new NodeItem(emptyNodeInfo), emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(n16)) {
            let q16 = this.nodeIdNodeItemMap.get(n16);
            p16 = new NodeInfo(q16, this.nodeIdNodeParamMap.get(n16));
            p16.addImageCollapse(q16.getChildNodeInfo().isHasChildNode);
        }
        if (m16 === MenuOperation.REMOVE_NODE) {
            this.nodeIdAndSubtitleMap.set(n16, this.selectedParentNodeSubtitle);
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(n16));
            this.refreshRemoveNodeData(o16, p16);
        }
        if (m16 === MenuOperation.ADD_NODE) {
            this.addFocusNodeId = o16[0];
            this.nodeIdAndSubtitleMap.set(this.getClickNodeId(), this.selectedParentNodeSubtitle);
            this.nodeIdAndSubtitleMap.set(o16[0], this.insertNodeSubtitle);
            this.refreshAddNodeData(o16);
        }
    }

    setClickIndex(l16) {
        this.thisIndex = l16;
    }

    getClickNodeId() {
        if (!this.checkIndex(this.thisIndex)) {
            return -1;
        }
        return this.listNode[this.thisIndex].getNodeCurrentNodeId();
    }

    expandAndCollapseNode(k16) {
        this.changeNodeStatus(k16);
        this.handleExpandAndCollapse(k16, true);
    }

    getIsTouchDown() {
        return this.isTouchDown;
    }

    getLastIndex() {
        return this.lastIndex;
    }

    findIndex(i16) {
        let j16 = -1;
        if (this.nodeIdAndNodeIndexMap.has(i16)) {
            j16 = this.nodeIdAndNodeIndexMap.get(i16);
        }
        return j16;
    }

    handleEventDrag(h16) {
        if (!this.checkIndex(h16)) {
            return;
        }
        this.setImageSource(h16, InteractionStatus.NORMAL);
        this.changeNodeColor(h16, this.listNode[h16].getNodeStatus().normal);
        this.handleFocusEffect(h16, false);
        this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.listNode[h16].getNodeCurrentNodeId()));
    }

    handleEvent(f16, g16) {
        if (this.isDrag) {
            return;
        }
        if (!this.checkIndex(g16)) {
            return;
        }
        if (f16 === Event.TOUCH_DOWN || f16 === Event.TOUCH_UP || f16 === Event.MOUSE_BUTTON_RIGHT) {
            if (g16 !== this.lastIndex) {
                this.clearLastIndexStatus();
            }
        }
        this.eventHandler(g16, f16);
    }

    eventHandler(b16, c16) {
        let d16 = this.loadedNodeIdAndIndexMap.get(this.listNode[b16].getNodeCurrentNodeId());
        switch (c16) {
            case Event.TOUCH_DOWN:
                this.isTouchDown = true;
                this.changeNodeColor(b16, this.listNode[b16].getNodeStatus().press);
                this.notifyDataChange(d16);
                break;
            case Event.TOUCH_UP: {
                this.touchUpHandler(b16, d16);
                break;
            }
            case Event.HOVER:
                if (this.getNodeColor(b16) !== this.listNode[b16].getNodeStatus().selected) {
                    this.changeNodeColor(b16, this.listNode[b16].getNodeStatus().hover);
                    this.notifyDataChange(d16);
                }
                break;
            case Event.HOVER_OVER:
                if (this.getNodeColor(b16) !== this.listNode[b16].getNodeStatus().selected) {
                    this.changeNodeColor(b16, this.listNode[b16].getNodeStatus().normal);
                    this.notifyDataChange(d16);
                }
                break;
            case Event.FOCUS:
                this.handleFocusEffect(b16, true);
                this.notifyDataChange(d16);
                break;
            case Event.BLUR:
                this.handleFocusEffect(b16, false);
                this.notifyDataChange(d16);
                break;
            case Event.MOUSE_BUTTON_RIGHT:
                this.lastIndex = b16;
                this.finishEditing();
                break;
            case Event.DRAG:
                this.isTouchDown = false;
                let e16 = this.listNode[b16];
                this.setImageSource(b16, InteractionStatus.SELECTED);
                this.lastIndex = b16;
                this.changeNodeColor(b16, e16.getNodeStatus().selected);
                this.notifyDataChange(d16);
                break;
            default:
                break;
        }
    }

    touchUpHandler(y15, z15) {
        if (this.isInnerDrag) {
            this.isInnerDrag = false;
        }
        this.isTouchDown = false;
        let a16 = this.listNode[y15];
        this.setImageSource(y15, InteractionStatus.SELECTED);
        a16.setFontColor(this.treeViewTheme.primaryTitleFontColor);
        this.lastIndex = y15;
        this.changeNodeColor(y15, a16.getNodeStatus().selected);
        this.notifyDataChange(z15);
    }

    notificationNodeInfo(p15, q15) {
        if (q15 === MenuOperation.MODIFY_NODE) {
            let w15 = this.listNode[this.modifyNodeIndex];
            let x15 = {
                currentNodeId: w15.getNodeCurrentNodeId(),
                parentNodeId: w15.getNodeParentNodeId(),
            };
            this.appEventBus.emit(TreeListenType.NODE_MODIFY, x15);
        }
        else if (q15 === MenuOperation.ADD_NODE) {
            let r15 = this.listNode[p15];
            if (r15 === undefined) {
                return;
            }
            let s15 = (r15.getNodeItem().imageNode !== undefined) ?
                r15.getNodeItem().imageNode?.source : undefined;
            let t15 = (r15.getNodeItem().imageNode !== undefined) ?
                r15.getNodeItem().imageNode?.selectedSource : undefined;
            let u15 = (r15.getNodeItem().imageNode !== undefined) ?
                r15.getNodeItem().imageNode?.editSource : undefined;
            let v15 = {
                currentNodeId: r15.getNodeCurrentNodeId(),
                parentNodeId: r15.getNodeParentNodeId(),
            };
            this.appEventBus.emit(TreeListenType.NODE_ADD, v15);
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

    setItemVisibilityOnEdit(j15, k15) {
        let l15 = -1;
        if (j15 === -1) {
            return;
        }
        if (k15 === MenuOperation.MODIFY_NODE) {
            for (let o15 = 0; o15 < this.listNode.length; o15++) {
                if (this.listNode[o15].getNodeCurrentNodeId() === j15) {
                    l15 = o15;
                    break;
                }
            }
            let n15 = this.listNode[l15];
            if (n15 === undefined) {
                return;
            }
            n15.setIsModify(true);
            if (n15.getNodeItem().mainTitleNode === null) {
                return;
            }
            this.currentOperation = MenuOperation.MODIFY_NODE;
            n15.setTitleAndInputTextStatus(true);
            this.setImageSource(l15, InteractionStatus.EDIT);
            this.setImageCollapseSource(l15, InteractionStatus.EDIT);
            this.modifyNodeIndex = l15;
            if (n15.getNodeItem().inputText) {
                if (n15.getNodeItem().imageCollapse !== null) {
                    n15.getNodeItem().inputText.rightMargin = {
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.ohos_id_text_paragraph_margin_xs'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__',
                    };
                }
                else {
                    n15.getNodeItem().inputText.rightMargin = {
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.ohos_id_elements_margin_horizontal_m'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__',
                    };
                }
            }
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(j15));
        }
        l15 = j15;
        if (k15 === MenuOperation.COMMIT_NODE) {
            let m15 = this.listNode[l15];
            if (m15 === undefined) {
                return;
            }
            m15.setTitleAndInputTextStatus(false);
            m15.setIsModify(false);
            this.setImageSource(l15, InteractionStatus.FINISH_EDIT);
            this.setImageCollapseSource(l15, InteractionStatus.FINISH_EDIT);
            this.notificationNodeInfo(this.modifyNodeIndex, this.currentOperation);
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(m15.getNodeCurrentNodeId()));
        }
    }

    setPopUpInfo(d15, e15, f15, g15) {
        if (!this.checkIndex(g15)) {
            return;
        }
        let h15 = this.listNode[g15];
        if (h15 === undefined) {
            return;
        }
        h15.setPopUpIsShow(f15);
        let i15 = this.loadedNodeIdAndIndexMap.get(h15.getNodeCurrentNodeId());
        if (!f15) {
            this.notifyDataChange(i15);
            return;
        }
        if (d15 === PopUpType.HINTS) {
            if (h15.getNodeItem().mainTitleNode !== null) {
                h15.setPopUpText(h15.getNodeItem().mainTitleNode?.title);
            }
            else {
                h15.setPopUpText('');
                h15.setPopUpIsShow(false);
            }
            h15.setPopUpEnableArrow(false);
            h15.setPopUpColor({
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_background'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            });
            h15.setPopUpTextColor(this.treeViewTheme.secondaryTitleFontColor);
        }
        else if (d15 === PopUpType.WARNINGS) {
            if (h15.getNodeItem().inputText !== null) {
                if (e15 === InputError.INVALID_ERROR) {
                    h15.setPopUpText('invalid error');
                }
                else if (e15 === InputError.LENGTH_ERROR) {
                    h15.setPopUpText('length error');
                }
                h15.setPopUpEnableArrow(true);
                h15.setPopUpColor({
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_help_tip_bg'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                });
                h15.setPopUpTextColor({
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_text_hint_contrary'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                });
            }
        }
        this.notifyDataChange(i15);
    }

    setShowPopUpTimeout(a15, b15) {
        if (!this.checkIndex(b15)) {
            return;
        }
        if (this.listNode[b15].getNodeItem().mainTitleNode !== null) {
            this.listNode[b15].getNodeItem().mainTitleNode.popUpTimeout = a15;
        }
        let c15 = this.loadedNodeIdAndIndexMap.get(this.listNode[b15].getNodeCurrentNodeId());
        this.notifyDataChange(c15);
    }

    setMainTitleNameOnEdit(y14, z14) {
        this.modifyNodeIndex = y14;
        if (this.listNode[y14].getNodeItem().mainTitleNode !== null) {
            this.listNode[y14].getNodeItem().mainTitleNode.title = z14;
        }
    }

    totalCount() {
        return this.loadedNodeIdAndIndexMap.size;
    }

    getData(x14) {
        if (x14 < 0 || x14 >= this.loadedListNode.length) {
            return undefined;
        }
        return this.loadedListNode[x14];
    }

    addData(v14, w14) {
        if (!this.checkIndex(v14)) {
            return;
        }
        this.listNode.splice(v14, 0, w14);
        this.nodeIdAndNodeIndexMap.set(w14.getNodeCurrentNodeId(), v14);
        this.loadedListNodeFunction();
        this.notifyDataAdd(v14);
    }

    pushData(u14) {
        this.listNode.push(u14);
        this.nodeIdAndNodeIndexMap.set(u14.getNodeCurrentNodeId(), this.listNode.length);
        this.loadedListNodeFunction();
        this.notifyDataAdd(this.listNode.length - 1);
    }

    setIsInnerDrag(t14) {
        this.isInnerDrag = t14;
    }

    getIsInnerDrag() {
        return this.isInnerDrag;
    }

    setIsDrag(s14) {
        this.isDrag = s14;
    }

    getIsDrag() {
        return this.isDrag;
    }

    setCurrentNodeInfo(r14) {
        if (r14 === undefined) {
            return;
        }
        this.currentNodeInfo = r14;
    }

    getCurrentNodeInfo() {
        return this.currentNodeInfo;
    }

    setDraggingParentNodeId(q14) {
        if (q14 === undefined) {
            return;
        }
        this.draggingParentNodeId = q14;
    }

    getDraggingParentNodeId() {
        return this.draggingParentNodeId;
    }

    getDraggingCurrentNodeId() {
        return this.draggingCurrentNodeId;
    }

    setDraggingCurrentNodeId(p14) {
        if (p14 === undefined) {
            return;
        }
        this.draggingCurrentNodeId = p14;
    }

    setListItemOpacity(o14) {
        this.listItemOpacity = o14;
    }

    getListItemOpacity(n14) {
        return n14.getNodeCurrentNodeId() === this.getDraggingCurrentNodeId() ? this.listItemOpacity : 1;
    }

    getDragPopupPara() {
        return this.DRAG_POPUP;
    }

    setLastPassIndex(m14) {
        this.lastPassIndex = m14;
    }

    getLastPassIndex() {
        return this.lastPassIndex;
    }

    getIsParentOfInsertNode(i14) {
        if (this.currentNodeInfo === null || i14 === undefined) {
            return false;
        }
        let j14 = this.currentNodeInfo.getNodeInfoNode();
        let k14 = j14.currentNodeId;
        let l14 = this.nodeIdNodeItemMap.get(i14)?.parentNodeId;
        while (l14 !== undefined && l14 !== -1) {
            if (k14 === l14) {
                return true;
            }
            else {
                l14 = this.nodeIdNodeItemMap.get(l14)?.parentNodeId;
            }
        }
        return false;
    }

    setPassIndex(h14) {
        this.thisPassIndex = h14;
    }

    getPassIndex() {
        return this.thisPassIndex;
    }

    clearTimeOutAboutDelayHighLightAndExpand(c14) {
        if (this.lastPassId !== this.INITIAL_INVALID_VALUE && this.loadedNodeIdAndIndexMap.has(this.lastPassId)) {
            let e14 = this.loadedNodeIdAndIndexMap.get(this.lastPassId);
            this.listNode.forEach((g14) => {
                if (g14.getNodeCurrentNodeId() === this.lastPassId) {
                    g14.setCanShowFlagLine(false);
                    return;
                }
            });
            this.notifyDataChange(e14);
        }
        if ((this.lastTimeoutHighLightId !== this.INITIAL_INVALID_VALUE &&
            this.clearTimeoutHighLightId !== this.lastTimeoutHighLightId)) {
            clearTimeout(this.lastTimeoutHighLightId);
            if (this.lastDelayHighLightIndex !== this.INITIAL_INVALID_VALUE) {
                this.clearHighLight(this.lastDelayHighLightIndex);
                let d14 = this.loadedNodeIdAndIndexMap
                    .get(this.listNode[this.lastDelayHighLightIndex].getNodeCurrentNodeId());
                this.notifyDataChange(d14);
            }
            this.clearTimeoutHighLightId = this.lastTimeoutHighLightId;
        }
        this.lastTimeoutHighLightId = this.timeoutHighLightId;
        this.lastDelayHighLightIndex = c14;
        if ((this.lastTimeoutExpandId !== this.INITIAL_INVALID_VALUE &&
            this.clearTimeoutExpandId !== this.lastTimeoutExpandId)) {
            clearTimeout(this.lastTimeoutExpandId);
            this.clearTimeoutExpandId = this.lastTimeoutExpandId;
        }
        this.lastTimeoutExpandId = this.timeoutExpandId;
        this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE;
    }

    clearHighLight(b14) {
        if (!this.checkIndex(b14)) {
            return;
        }
        this.changeNodeColor(b14, this.listNode[b14].getNodeStatus().normal);
        this.changeNodeHighLightColor(b14, false);
        this.setImageSource(b14, InteractionStatus.FINISH_DRAG_INSERT);
        this.setImageCollapseSource(b14, InteractionStatus.FINISH_DRAG_INSERT);
        this.listNode[b14].setIsHighLight(false);
    }

    changeNodeHighLightColor(z13, a14) {
        if (this.listNode[z13].getNodeItem().mainTitleNode && this.listNode[z13].getIsShowTitle()) {
            this.listNode[z13].getNodeItem().mainTitleNode?.setMainTitleHighLight(a14);
        }
    }

    setVisibility(q13, r13, s13) {
        let t13 = (this.thisPassIndex !== r13 || this.flag !== q13) ? true : false;
        this.thisPassIndex = r13;
        if ((t13 || s13) && this.isInnerDrag) {
            this.flag = q13;
            let u13 = this.getData(r13)?.getNodeCurrentNodeId();
            let v13 = this.getData(r13)?.getNodeLevel();
            if (u13 !== undefined) {
                v13 = (this.expandAndCollapseInfo.get(u13) === NodeStatus.EXPAND &&
                    this.flag === Flag.DOWN_FLAG) ? (v13 ? v13 + 1 : undefined) : v13;
                if (this.lastPassId !== this.INITIAL_INVALID_VALUE && this.loadedNodeIdAndIndexMap.has(this.lastPassId)) {
                    let w13 = this.loadedNodeIdAndIndexMap.get(this.lastPassId);
                    this.listNode.forEach((y13) => {
                        if (y13.getNodeCurrentNodeId() === this.lastPassId) {
                            y13.setCanShowFlagLine(false);
                        }
                    });
                    this.notifyDataChange(w13);
                }
                if (this.flag === Flag.DOWN_FLAG && r13 < this.totalCount() - 1) {
                    this.getData(r13)?.setCanShowFlagLine(false);
                    this.getData(r13 + 1)?.setCanShowFlagLine(true);
                    this.getData(r13)?.setCanShowBottomFlagLine(false);
                    this.getData(r13 + 1)?.setFlagLineLeftMargin(v13);
                    this.notifyDataChange(r13);
                    this.notifyDataChange(r13 + 1);
                    this.lastPassId = this.getData(r13 + 1)?.getNodeCurrentNodeId();
                }
                else if (this.flag === Flag.UP_FLAG && r13 < this.totalCount() - 1) {
                    this.getData(r13)?.setCanShowFlagLine(true);
                    this.getData(r13 + 1)?.setCanShowFlagLine(false);
                    this.getData(r13)?.setCanShowBottomFlagLine(false);
                    this.getData(r13)?.setFlagLineLeftMargin(v13);
                    this.notifyDataChange(r13);
                    this.notifyDataChange(r13 + 1);
                    this.lastPassId = this.getData(r13)?.getNodeCurrentNodeId();
                }
                else if (r13 >= this.totalCount() - 1) {
                    if (this.flag === Flag.DOWN_FLAG) {
                        this.getData(r13)?.setCanShowFlagLine(false);
                        this.getData(r13)?.setCanShowBottomFlagLine(true);
                    }
                    else {
                        this.getData(r13)?.setCanShowFlagLine(true);
                        this.getData(r13)?.setCanShowBottomFlagLine(false);
                    }
                    this.getData(r13)?.setFlagLineLeftMargin(v13);
                    this.notifyDataChange(r13);
                    this.lastPassId = this.getData(r13)?.getNodeCurrentNodeId();
                }
            }
        }
    }

    delayHighLightAndExpandNode(f13, g13, h13) {
        let i13 = f13 !== this.lastDelayExpandIndex ? true : false;
        let j13 = this.getData(h13)?.getIsOverBorder();
        if (j13) {
            this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE;
        }
        else {
            this.lastDelayExpandIndex = f13;
        }
        if (j13 || i13) {
            let k13 = !j13 && (!this.isInnerDrag ||
                (this.expandAndCollapseInfo.get(g13) === NodeStatus.COLLAPSE && this.isInnerDrag) ||
                (!this.expandAndCollapseInfo.has(g13) && this.listNode[f13].getIsFolder()));
            if (k13) {
                this.changeNodeColor(f13, this.listNode[f13].getNodeStatus().hover);
                this.notifyDataChange(h13);
                let o13 = this.isInnerDrag ? 1000 : 0;
                this.timeoutHighLightId = setTimeout(() => {
                    this.delayHighLight(f13);
                }, o13);
            }
            if (j13 || (this.lastTimeoutHighLightId !== this.INITIAL_INVALID_VALUE &&
                this.clearTimeoutHighLightId !== this.lastTimeoutHighLightId)) {
                clearTimeout(this.lastTimeoutHighLightId);
                if (this.lastDelayHighLightIndex !== this.INITIAL_INVALID_VALUE) {
                    this.clearHighLight(this.lastDelayHighLightIndex);
                    this.notifyDataReload();
                }
                this.clearTimeoutHighLightId = this.lastTimeoutHighLightId;
            }
            this.lastTimeoutHighLightId = this.timeoutHighLightId;
            this.lastDelayHighLightIndex = f13;
            if (!j13 && this.expandAndCollapseInfo.get(g13) === NodeStatus.COLLAPSE) {
                let l13 = this.getData(h13)?.getNodeInfoNode().children[0]?.currentNodeId;
                let m13 = 2000;
                this.timeoutExpandId = setTimeout(() => {
                    this.clearHighLight(this.lastDelayHighLightIndex);
                    if (l13 !== undefined) {
                        this.alterFlagLineAndExpandNode(f13, l13);
                    }
                }, m13);
            }
            if (j13 || (this.lastTimeoutExpandId !== this.INITIAL_INVALID_VALUE &&
                this.clearTimeoutExpandId !== this.lastTimeoutExpandId)) {
                clearTimeout(this.lastTimeoutExpandId);
                this.clearTimeoutExpandId = this.lastTimeoutExpandId;
            }
            this.lastTimeoutExpandId = this.timeoutExpandId;
        }
    }

    delayHighLight(c13) {
        this.listNode.forEach((e13) => {
            if (e13.getNodeCurrentNodeId() === this.lastPassId) {
                e13.setCanShowFlagLine(false);
                e13.setCanShowBottomFlagLine(false);
                return;
            }
        });
        this.changeNodeColor(c13, this.listNode[c13].getNodeStatus().highLight);
        this.listNode[c13].setIsHighLight(true);
        this.changeNodeHighLightColor(c13, true);
        this.setImageSource(c13, InteractionStatus.DRAG_INSERT);
        this.setImageCollapseSource(c13, InteractionStatus.DRAG_INSERT);
        this.notifyDataReload();
    }

    alterFlagLineAndExpandNode(w12, x12) {
        this.listNode.forEach((b13) => {
            if (b13.getNodeCurrentNodeId() === this.lastPassId) {
                b13.setCanShowFlagLine(false);
                b13.setCanShowBottomFlagLine(false);
            }
        });
        this.listNode.forEach((a13) => {
            if (this.isInnerDrag && a13.getNodeCurrentNodeId() === x12) {
                a13.setCanShowFlagLine(true);
            }
        });
        this.changeNodeStatus(w12);
        this.handleExpandAndCollapse(w12, true);
        this.lastPassId = x12;
    }

    hideLastLine() {
        if (this.lastPassId !== this.INITIAL_INVALID_VALUE && this.loadedNodeIdAndIndexMap.has(this.lastPassId)) {
            this.listNode.forEach((v12) => {
                if (v12.getNodeCurrentNodeId() === this.lastPassId) {
                    v12.setCanShowFlagLine(false);
                    v12.setCanShowBottomFlagLine(false);
                    return;
                }
            });
            let t12 = this.loadedNodeIdAndIndexMap.get(this.lastPassId);
            this.notifyDataChange(t12);
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

    getSubtitle(s12) {
        if (this.nodeIdAndSubtitleMap.has(s12)) {
            if (typeof this.nodeIdAndSubtitleMap.get(s12) === 'number') {
                return this.nodeIdAndSubtitleMap.get(s12)?.toString();
            }
            else {
                return this.nodeIdAndSubtitleMap.get(s12);
            }
        }
        else {
            return '';
        }
    }

    hasSubtitle(r12) {
        return this.nodeIdAndSubtitleMap.has(r12);
    }

    initialParameterAboutDelayHighLightAndExpandIndex() {
        this.lastDelayHighLightIndex = this.INITIAL_INVALID_VALUE;
        this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE;
        this.lastPassIndex = this.INITIAL_INVALID_VALUE;
        this.draggingCurrentNodeId = this.INITIAL_INVALID_VALUE;
        this.flag = Flag.NONE;
    }

    refreshSubtitle(q12) {
        this.nodeIdAndSubtitleMap.set(this.selectedParentNodeId, this.selectedParentNodeSubtitle);
        this.nodeIdAndSubtitleMap.set(q12, this.insertNodeSubtitle);
        this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.selectedParentNodeId));
        this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(q12));
    }

    setNodeSubtitlePara(n12, o12, p12) {
        this.selectedParentNodeId = n12;
        this.selectedParentNodeSubtitle = o12;
        this.insertNodeSubtitle = p12;
    }

    getInsertNodeSubtitle() {
        return this.insertNodeSubtitle;
    }

    getExpandAndCollapseInfo(m12) {
        return this.expandAndCollapseInfo.get(m12);
    }

    getLastDelayHighLightId() {
        return this.lastDelayHighLightId;
    }

    setLastDelayHighLightId() {
        this.listNode.forEach((k12, l12) => {
            if (l12 === this.lastDelayHighLightIndex) {
                this.lastDelayHighLightId = k12.getNodeCurrentNodeId();
            }
        });
    }

    setLastPassId(i12) {
        this.lastPassId = i12;
    }

    setLastDelayHighLightIndex(h12) {
        this.lastDelayHighLightIndex = h12;
    }

    alterDragNode(d11, e11, f11, g11, h11) {
        let i11 = [];
        let j11 = d11;
        let k11 = g11;
        let l11 = h11.getNodeInfoData();
        let m11 = null;
        let n11 = h11.getNodeInfoNode();
        let o11 = false;
        let p11 = this.INITIAL_INVALID_VALUE;
        let q11 = this.INITIAL_INVALID_VALUE;
        let r11 = this.flag === Flag.DOWN_FLAG ? true : false;
        q11 = this.getChildIndex(f11, g11);
        p11 = this.getChildIndex(d11, e11) + 1;
        if (d11 !== f11) {
            p11 = r11 ? p11 + 1 : p11;
        }
        else {
            if (p11 > q11) {
                p11 = r11 ? p11 : p11 - 1;
            }
            else {
                p11 = r11 ? p11 + 1 : p11;
            }
        }
        for (let g12 = 0; g12 < this.listNode.length; g12++) {
            if (this.listNode[g12].getNodeCurrentNodeId() === e11) {
                o11 = this.listNode[g12].getIsHighLight();
                if (this.flag === Flag.DOWN_FLAG && this.expandAndCollapseInfo.get(e11) === NodeStatus.EXPAND) {
                    j11 = e11;
                    p11 = 0;
                }
                else if (this.flag === Flag.UP_FLAG && this.expandAndCollapseInfo.get(e11) ===
                NodeStatus.EXPAND &&
                    this.listNode[g12].getCanShowFlagLine() === false) {
                    j11 = e11;
                    p11 = 0;
                }
                else if (o11) {
                    j11 = e11;
                    p11 = 0;
                }
                break;
            }
        }
        let s11 = {
            currentNodeId: k11,
            parentNodeId: j11,
            childIndex: p11,
        };
        this.appEventBus.emit(TreeListenType.NODE_MOVE, s11);
        i11.push({ parentId: j11, currentId: k11, data: l11 });
        let t11 = (c12, d12) => {
            if (c12) {
                j11 = c12.parentNodeId;
                k11 = c12.currentNodeId;
                for (let f12 = 0; f12 < d12.length; f12++) {
                    if (d12[f12].getNodeCurrentNodeId() === k11) {
                        m11 = d12[f12];
                        break;
                    }
                }
                if (m11 === null) {
                    return false;
                }
                let e12 = m11.getNodeInfoData();
                if (j11 !== f11) {
                    i11.push({ parentId: j11, currentId: k11, data: e12 });
                }
                return false;
            }
            return false;
        };
        this.dragTraverseNodeDF(t11, n11, this.listNode);
        let b18 = this.removeNode(g11, f11);
        if (b18.length === 0) {
            return;
        }
        let u11 = e11;
        let v11 = r11;
        if (this.expandAndCollapseInfo.get(e11) === NodeStatus.EXPAND) {
            v11 = false;
            this.listNode.forEach((b12) => {
                if (b12.getNodeCurrentNodeId() === e11 && b12.getCanShowFlagLine() === false) {
                    if (b12.getNodeInfoNode().children.length) {
                        u11 = b12.getNodeInfoNode().children[0].currentNodeId;
                    }
                    else {
                        u11 = this.INITIAL_INVALID_VALUE;
                    }
                }
            });
        }
        else if (!this.expandAndCollapseInfo.get(e11) && o11) {
            this.expandAndCollapseInfo.set(e11, NodeStatus.EXPAND);
        }
        let c18 = this.addDragNode(i11[0].parentId, i11[0].currentId, u11, v11, i11[0].data);
        if (!c18) {
            return;
        }
        for (let z11 = 1; z11 < i11.length; z11++) {
            let f18 = this.addNode(i11[z11].parentId, i11[z11].currentId, i11[z11].data, false);
            if (!f18) {
                return;
            }
        }
        for (let y11 = 0; y11 < this.listNode.length; y11++) {
            if (this.listNode[y11].getNodeCurrentNodeId() === f11) {
                if (this.listNode[y11].getNodeItem().imageCollapse === null) {
                    this.listNode[y11].handleImageCollapseAfterAddNode(false);
                    this.expandAndCollapseInfo.delete(f11);
                    break;
                }
            }
        }
        let w11 = [...this.listNode];
        this.reloadListNode(w11);
    }

    reloadListNode(v10) {
        let w10 = 0;
        let x10 = 0;
        this.listNode.splice(0, this.listNode.length);
        this.loadedNodeIdAndIndexMap.clear();
        this.loadedListNode.splice(0, this.loadedListNode.length);
        this.traverseNodeDF((z10) => {
            let a11 = z10.currentNodeId;
            if (a11 >= 0) {
                if (this.nodeIdNodeParamMap.has(a11)) {
                    let b11 = new NodeInfo(z10, this.nodeIdNodeParamMap.get(a11));
                    b11.addImageCollapse(z10.getChildNodeInfo().isHasChildNode);
                    this.listNode.push(b11);
                    this.nodeIdAndNodeIndexMap.set(b11.getNodeCurrentNodeId(), x10++);
                    if (this.expandAndCollapseInfo.get(a11) === NodeStatus.EXPAND) {
                        b11.getNodeItem().imageCollapse = b11.getNodeItem().imageCollapse ?
                        CollapseImageNodeFlyweightFactory.changeImageCollapseSource(NodeStatus.EXPAND, b11.getNodeItem().imageCollapse.isCollapse) : undefined;
                    }
                    else if (this.expandAndCollapseInfo.get(a11) === NodeStatus.COLLAPSE) {
                        b11.getNodeItem().imageCollapse = b11.getNodeItem().imageCollapse ?
                        CollapseImageNodeFlyweightFactory.changeImageCollapseSource(NodeStatus.COLLAPSE, b11.getNodeItem().imageCollapse.isCollapse) : undefined;
                    }
                    for (let c11 = 0; c11 < v10.length; c11++) {
                        if (v10[c11].getNodeCurrentNodeId() === b11.getNodeCurrentNodeId()) {
                            b11.setNodeIsShow(v10[c11].getNodeIsShow());
                            b11.setListItemHeight(v10[c11].getListItemHeight());
                            if (b11.getNodeItem().mainTitleNode && b11.getIsShowTitle()) {
                                b11.getNodeItem().mainTitleNode.title = v10[c11].getNodeItem().mainTitleNode?.title;
                            }
                            break;
                        }
                    }
                    if (b11.getNodeIsShow()) {
                        this.loadedNodeIdAndIndexMap.set(b11.getNodeCurrentNodeId(), w10++);
                        this.loadedListNode.push(b11);
                    }
                }
            }
            return false;
        });
    }

    getFlagLine() {
        return this.FLAG_LINE;
    }

    getVisibility(s10) {
        let t10 = this.loadedNodeIdAndIndexMap.get(s10.getNodeCurrentNodeId()) - 1;
        if (t10 > this.INITIAL_INVALID_VALUE) {
            let u10 = this.getData(t10);
            return (s10.getCanShowFlagLine() === true && !s10.getIsHighLight() && !u10?.getIsHighLight()) ?
            Visibility.Visible : Visibility.Hidden;
        }
        else {
            return (s10.getCanShowFlagLine() === true && !s10.getIsHighLight()) ?
            Visibility.Visible : Visibility.Hidden;
        }
    }

    getSubTitlePara() {
        return this.subTitle;
    }

    getIsFolder(r10) {
        if (this.loadedNodeIdAndIndexMap.has(r10)) {
            return this.getData(this.loadedNodeIdAndIndexMap.get(r10))?.getIsFolder();
        }
        return false;
    }

    getSubTitleFontColor(q10) {
        return q10 ? this.subTitle.highLightFontColor : this.treeViewTheme.secondaryTitleFontColor;
    }

    getChildIndex(j10, k10) {
        let l10 = this.INITIAL_INVALID_VALUE;
        if (this.nodeIdNodeItemMap.has(j10)) {
            let m10 = this.nodeIdNodeItemMap.get(j10);
            if (m10.getCurrentNodeId() === j10) {
                m10.children.forEach((o10, p10) => {
                    if (o10.getCurrentNodeId() === k10) {
                        l10 = p10;
                        return;
                    }
                });
            }
        }
        return l10;
    }

    setCurrentFocusNodeId(i10) {
        this.currentFocusNodeId = i10;
    }

    getCurrentFocusNodeId() {
        return this.currentFocusNodeId;
    }

    setLastFocusNodeId(h10) {
        this.lastFocusNodeId = h10;
    }

    getLastFocusNodeId() {
        return this.lastFocusNodeId;
    }

    getAddFocusNodeId() {
        return this.addFocusNodeId;
    }

    setFlag(g10) {
        this.flag = g10;
    }

    traverseNodeDF(b10, c10 = this._root) {
        let d10 = [];
        let e10 = false;
        d10.unshift(c10);
        let f10 = d10.shift();
        while (!e10 && f10) {
            e10 = b10(f10) === true;
            if (!e10) {
                d10.unshift(...f10.children);
                f10 = d10.shift();
            }
        }
    }

    traverseSectionNodeDF(s9, t9 = this._root, u9, v9) {
        let w9 = [];
        let x9 = false;
        let y9 = false;
        w9.unshift(t9);
        let z9 = w9.shift();
        while (!x9 && z9) {
            try {
                if (u9 !== undefined && z9.nodeLevel < u9) {
                    y9 = true;
                }
                if (v9 !== undefined && z9.nodeLevel > v9) {
                    y9 = true;
                }
                if (!y9) {
                    x9 = s9(z9);
                }
            }
            catch (a10) {
                throw new Error('traverseSectionNodeDF function callbacks error');
            }
            if (!x9) {
                w9.unshift(...z9.children);
                z9 = w9.shift();
                y9 = false;
            }
        }
    }

    updateParentChildNum(n9, o9, p9) {
        let q9 = n9.parentNodeId;
        while (q9 >= 0) {
            if (this.nodeIdNodeItemMap.has(q9)) {
                let r9 = this.nodeIdNodeItemMap.get(q9);
                r9.getChildNodeInfo().allChildNum =
                    o9 ? r9.getChildNodeInfo().allChildNum + p9 : r9.getChildNodeInfo().allChildNum - p9;
                q9 = r9.parentNodeId;
            }
            else {
                hilog.error(0x3900, 'TreeView', 'updateParentChildNum: parent node not found.');
                break;
            }
        }
    }

    findParentNodeId(l9) {
        let m9 = new NodeItem(emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(l9)) {
            m9 = this.nodeIdNodeItemMap.get(l9);
        }
        return m9.parentNodeId;
    }

    addNode(e9, f9, g9, h9) {
        if (this._root === null) {
            this._root = new NodeItem(emptyNodeInfo);
            this._root.nodeLevel = -1;
            this.nodeIdNodeItemMap.set(-1, this._root);
            this.nodeIdNodeParamMap.set(-1, emptyNodeInfo);
        }
        if (this.nodeIdNodeItemMap.has(e9)) {
            let i9 = this.nodeIdNodeItemMap.get(e9);
            let j9 = new NodeItem(g9);
            if (i9.nodeLevel > this.maxNodeLevel) {
                hilog.error(0x3900, 'TreeView', 'ListDataSource[addNode]: The level of the tree view cannot exceed 50.');
                return false;
            }
            j9.nodeLevel = i9.nodeLevel + 1;
            j9.parentNodeId = e9;
            j9.currentNodeId = f9;
            j9.indexOfParent = i9.children.length;
            g9.parentNodeId = e9;
            g9.currentNodeId = f9;
            i9.children.push(j9);
            i9.getChildNodeInfo().isHasChildNode = true;
            i9.getChildNodeInfo().childNum = i9.children.length;
            i9.getChildNodeInfo().allChildNum += 1;
            if (h9) {
                this.updateNodeIdList.push(i9.parentNodeId);
            }
            else {
                let k9 = [];
                k9.push(i9.parentNodeId);
                delayUpdateParentChildNum(true, 1, this.nodeIdNodeItemMap, k9);
            }
            this.nodeIdNodeParamMap.set(f9, g9);
            this.nodeIdNodeItemMap.set(f9, j9);
            return true;
        }
        else {
            hilog.error(0x3900, 'TreeView', 'ListDataSource[addNode]: Parent node not found.');
            return false;
        }
    }

    freeNodeMemory(w8, x8) {
        let y8 = [];
        let z8 = (d9) => {
            y8.push(d9);
            return false;
        };
        this.traverseNodeDF(z8, w8);
        y8.forEach((c9) => {
            x8.push(c9.getCurrentNodeId());
            this.nodeIdNodeItemMap.delete(c9.getCurrentNodeId());
            this.nodeIdNodeParamMap.delete(c9.getCurrentNodeId());
            c9 = new NodeItem(emptyNodeInfo);
        });
    }

    removeNode(l8, m8) {
        if (this.nodeIdNodeItemMap.has(m8) && this.nodeIdNodeItemMap.has(l8)) {
            let n8 = this.nodeIdNodeItemMap.get(m8);
            let o8 = this.nodeIdNodeItemMap.get(l8);
            let p8 = [];
            let q8 = o8.indexOfParent;
            let r8 = 0;
            if (q8 < 0) {
                hilog.error(0x3900, 'TreeView', 'node does not exist.');
                return [];
            }
            else {
                r8 = n8.children[q8].getChildNodeInfo().allChildNum + 1;
                this.freeNodeMemory(n8.children[q8], p8);
                for (let v8 = q8; v8 < n8.children.length; v8++) {
                    n8.children[v8].indexOfParent -= 1;
                }
                let t8 = n8.children.splice(q8, 1);
                t8 = null;
                if (n8.children.length === 0) {
                    if (this.nodeIdAndNodeIndexMap.has(m8)) {
                        let u8 = this.nodeIdAndNodeIndexMap.get(m8);
                        this.listNode[u8]?.addImageCollapse(false);
                    }
                }
            }
            n8.getChildNodeInfo().childNum = n8.children.length;
            n8.getChildNodeInfo().allChildNum -= (r8);
            let s8 = [];
            s8.push(n8.parentNodeId);
            delayUpdateParentChildNum(false, r8, this.nodeIdNodeItemMap, s8);
            return p8;
        }
        else {
            hilog.error(0x3900, 'TreeView', 'parent does not exist.');
            return [];
        }
    }

    getNodeInfoByNodeItem(j8) {
        if (j8?.currentNodeId === undefined) {
            hilog.error(0x3900, 'TreeView', 'getNodeInfoByNodeItem: currentId is undefined');
            return new NodeInfo(new NodeItem(emptyNodeInfo), emptyNodeInfo);
        }
        if (!this.nodeIdAndNodeIndexMap.has(j8.currentNodeId)) {
            hilog.error(0x3900, 'TreeView', 'getNodeInfoByNodeItem: not has nodeItem.');
            return new NodeInfo(new NodeItem(emptyNodeInfo), emptyNodeInfo);
        }
        let k8 = this.nodeIdAndNodeIndexMap.get(j8.currentNodeId);
        return this.listNode[k8];
    }

    getNewNodeParam(e8) {
        let f8 = new NodeItem(emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(e8)) {
            f8 = this.nodeIdNodeItemMap.get(e8);
        }
        let g8 = emptyNodeInfo;
        if (f8) {
            let h8 = this.getNodeInfoByNodeItem(f8);
            if (f8.children.length === 0) {
                if (h8.getNodeItem().imageNode !== undefined) {
                    g8.icon = h8.getNodeItem().imageNode?.normalSource;
                    g8.selectedIcon = h8.getNodeItem().imageNode?.selectedSource;
                    g8.editIcon = h8.getNodeItem().imageNode?.editSource;
                    g8.container = h8.getMenu();
                }
                else {
                    g8.icon = undefined;
                    g8.selectedIcon = undefined;
                    g8.editIcon = undefined;
                    g8.container = h8.getMenu();
                }
            }
            else if (f8.children.length > 0) {
                let i8 = this.getNodeInfoByNodeItem(f8.children[0]);
                if (h8.getNodeItem().imageNode !== null) {
                    g8.icon = (i8.getNodeItem().imageNode !== undefined) ?
                        i8.getNodeItem().imageNode?.normalSource : undefined;
                    g8.selectedIcon = (i8.getNodeItem().imageNode !== undefined) ?
                        i8.getNodeItem().imageNode?.selectedSource : undefined;
                    g8.editIcon = (i8.getNodeItem().imageNode !== undefined) ?
                        i8.getNodeItem().imageNode?.editSource : undefined;
                    g8.container = i8.getMenu();
                }
                else {
                    g8.icon = undefined;
                    g8.selectedIcon = undefined;
                    g8.editIcon = undefined;
                    g8.container = i8.getMenu();
                }
            }
        }
        return g8;
    }

    getClickChildId(z7) {
        let a8 = new NodeItem(emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(z7)) {
            a8 = this.nodeIdNodeItemMap.get(z7);
        }
        if (a8) {
            if (a8.children.length === 0) {
                return [];
            }
            else if (a8.children.length > 0) {
                let b8 = new Array(a8.children.length);
                for (let d8 = 0; d8 < b8.length; d8++) {
                    b8[d8] = 0;
                }
                for (let c8 = 0; c8 < a8.children.length && c8 < b8.length; c8++) {
                    b8[c8] = a8.children[c8].currentNodeId;
                }
                return b8;
            }
        }
        return [];
    }

    getClickNodeChildrenInfo(t7) {
        let u7 = new NodeItem(emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(t7)) {
            u7 = this.nodeIdNodeItemMap.get(t7);
        }
        if (u7) {
            if (u7.children.length === 0) {
                return [];
            }
            else if (u7.children.length > 0) {
                let v7 = new Array(u7.children.length);
                for (let y7 = 0; y7 < v7.length; y7++) {
                    v7[y7] = {};
                }
                for (let w7 = 0; w7 < u7.children.length && w7 < v7.length; w7++) {
                    v7[w7].itemId = u7.children[w7].currentNodeId;
                    let x7 = this.getNodeInfoByNodeItem(u7.children[w7]);
                    if (x7.getNodeItem().imageNode) {
                        v7[w7].itemIcon = x7.getNodeItem().imageNode?.source;
                    }
                    if (x7.getNodeItem().mainTitleNode) {
                        v7[w7].itemTitle = x7.getNodeItem().mainTitleNode?.title;
                    }
                    v7[w7].isFolder = x7.getIsFolder();
                }
                return v7;
            }
        }
        return [];
    }

    checkMainTitleIsValid(s7) {
        if (new RegExp('/[\\\/:*?"<>|]/').test(s7)) {
            return false;
        }

        if ((new RegExp('/^[\u4e00-\u9fa5]+$/').test(s7) && s7.length > this.MAX_CN_LENGTH) ||
            (!new RegExp('/^[\u4e00-\u9fa5]+$/').test(s7) && s7.length > this.MAX_EN_LENGTH)) {
            return false;
        }

        return true;
    }

    dragTraverseNodeDF(m7, n7 = this._root, o7) {
        let p7 = [];
        let q7 = false;
        p7.unshift(n7);
        let r7 = p7.shift();
        while (!q7 && r7) {
            q7 = m7(r7, o7) === true;
            if (!q7) {
                p7.unshift(...r7.children);
                r7 = p7.shift();
            }
        }
    }

    updateChildIndexOfParent(j7, k7) {
        for (let l7 = j7; l7 < k7.children.length; l7++) {
            k7.children[l7].indexOfParent += 1;
        }
    }

    addDragNode(a7, b7, c7, d7, e7) {
        if (this._root === null) {
            this._root = new NodeItem(emptyNodeInfo);
            this._root.nodeLevel = this.INITIAL_INVALID_VALUE;
        }
        if (this.nodeIdNodeItemMap.has(a7)) {
            let f7 = this.nodeIdNodeItemMap.get(a7);
            let g7 = new NodeItem(e7);
            if (f7.nodeLevel > this.maxNodeLevel) {
                hilog.error(0x3900, 'TreeView', 'addDragNode: The level of the tree view cannot exceed 50.');
                return false;
            }
            g7.nodeLevel = f7.nodeLevel + 1;
            g7.parentNodeId = a7;
            g7.currentNodeId = b7;
            e7.parentNodeId = a7;
            e7.currentNodeId = b7;
            let h7 = this.INITIAL_INVALID_VALUE;
            if (f7.children.length) {
                for (let i7 = 0; i7 < f7.children.length; i7++) {
                    if (f7.children[i7].getCurrentNodeId() === c7) {
                        h7 = i7;
                        break;
                    }
                }
                if (d7) {
                    g7.indexOfParent = h7 + 1;
                    this.updateChildIndexOfParent(g7.indexOfParent, f7);
                    f7.children.splice(h7 + 1, 0, g7);
                }
                else {
                    g7.indexOfParent = h7 < 0 ? f7.children.length + h7 : h7;
                    this.updateChildIndexOfParent(g7.indexOfParent, f7);
                    f7.children.splice(h7, 0, g7);
                }
            }
            else {
                g7.indexOfParent = f7.children.length;
                f7.children.push(g7);
            }
            f7.getChildNodeInfo().isHasChildNode = true;
            f7.getChildNodeInfo().childNum = f7.children.length;
            f7.getChildNodeInfo().allChildNum += 1;
            this.updateParentChildNum(f7, true, 1);
            this.nodeIdNodeItemMap.set(b7, g7);
            this.nodeIdNodeParamMap.set(b7, e7);
            return true;
        }
        else {
            hilog.error(0x3900, 'TreeView', 'addDragNode: parent node not found.');
            return false;
        }
    }
}

export class TreeViewInner extends ViewPU {
    constructor(u6, v6, w6, x6 = -1, y6 = undefined, z6) {
        super(u6, w6, x6, z6);
        if (typeof y6 === 'function') {
            this.paramsGenerator_ = y6;
        }
        this.__item = new SynchedPropertyNesedObjectPU(v6.item, this, 'item');
        this.listNodeDataSource = new ListNodeDataSource();
        this.__columnWidth = new ObservedPropertySimplePU(0, this, 'columnWidth');
        this.__isFocused = new ObservedPropertySimplePU(false, this, 'isFocused');
        this.__index = new ObservedPropertySimplePU(-1, this, 'index');
        this.__lastIndex = new ObservedPropertySimplePU(-1, this, 'lastIndex');
        this.__count = new ObservedPropertySimplePU(0, this, 'count');
        this.__followingSystemFontScale = new ObservedPropertySimplePU(false, this, 'followingSystemFontScale');
        this.__maxAppFontScale = new ObservedPropertySimplePU(1, this, 'maxAppFontScale');
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
        this.inputFontSize = resourceManager.getSystemResourceManager().getNumberByName('ohos_id_text_size_body1');
        this.setInitiallyProvidedValue(v6);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(t6) {
        this.__item.set(t6.item);
        if (t6.listNodeDataSource !== undefined) {
            this.listNodeDataSource = t6.listNodeDataSource;
        }
        if (t6.columnWidth !== undefined) {
            this.columnWidth = t6.columnWidth;
        }
        if (t6.isFocused !== undefined) {
            this.isFocused = t6.isFocused;
        }
        if (t6.index !== undefined) {
            this.index = t6.index;
        }
        if (t6.lastIndex !== undefined) {
            this.lastIndex = t6.lastIndex;
        }
        if (t6.count !== undefined) {
            this.count = t6.count;
        }
        if (t6.followingSystemFontScale !== undefined) {
            this.followingSystemFontScale = t6.followingSystemFontScale;
        }
        if (t6.maxAppFontScale !== undefined) {
            this.maxAppFontScale = t6.maxAppFontScale;
        }
        if (t6.listTreeViewMenu !== undefined) {
            this.listTreeViewMenu = t6.listTreeViewMenu;
        }
        if (t6.MAX_CN_LENGTH !== undefined) {
            this.MAX_CN_LENGTH = t6.MAX_CN_LENGTH;
        }
        if (t6.MAX_EN_LENGTH !== undefined) {
            this.MAX_EN_LENGTH = t6.MAX_EN_LENGTH;
        }
        if (t6.INITIAL_INVALID_VALUE !== undefined) {
            this.INITIAL_INVALID_VALUE = t6.INITIAL_INVALID_VALUE;
        }
        if (t6.MAX_TOUCH_DOWN_COUNT !== undefined) {
            this.MAX_TOUCH_DOWN_COUNT = t6.MAX_TOUCH_DOWN_COUNT;
        }
        if (t6.isMultiPress !== undefined) {
            this.isMultiPress = t6.isMultiPress;
        }
        if (t6.touchDownCount !== undefined) {
            this.touchDownCount = t6.touchDownCount;
        }
        if (t6.appEventBus !== undefined) {
            this.appEventBus = t6.appEventBus;
        }
        if (t6.itemPadding !== undefined) {
            this.itemPadding = t6.itemPadding;
        }
        if (t6.textInputPadding !== undefined) {
            this.textInputPadding = t6.textInputPadding;
        }
        if (t6.inputFontSize !== undefined) {
            this.inputFontSize = t6.inputFontSize;
        }
    }

    updateStateVars(s6) {
        this.__item.set(s6.item);
    }

    purgeVariableDependenciesOnElmtId(r6) {
        this.__item.purgeDependencyOnElmtId(r6);
        this.__columnWidth.purgeDependencyOnElmtId(r6);
        this.__isFocused.purgeDependencyOnElmtId(r6);
        this.__index.purgeDependencyOnElmtId(r6);
        this.__lastIndex.purgeDependencyOnElmtId(r6);
        this.__count.purgeDependencyOnElmtId(r6);
        this.__followingSystemFontScale.purgeDependencyOnElmtId(r6);
        this.__maxAppFontScale.purgeDependencyOnElmtId(r6);
        this.__treeViewTheme.purgeDependencyOnElmtId(r6);
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
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get item() {
        return this.__item.get();
    }

    get columnWidth() {
        return this.__columnWidth.get();
    }

    set columnWidth(q6) {
        this.__columnWidth.set(q6);
    }

    get isFocused() {
        return this.__isFocused.get();
    }

    set isFocused(p6) {
        this.__isFocused.set(p6);
    }

    get index() {
        return this.__index.get();
    }

    set index(o6) {
        this.__index.set(o6);
    }

    get lastIndex() {
        return this.__lastIndex.get();
    }

    set lastIndex(n6) {
        this.__lastIndex.set(n6);
    }

    get count() {
        return this.__count.get();
    }

    set count(m6) {
        this.__count.set(m6);
    }

    get followingSystemFontScale() {
        return this.__followingSystemFontScale.get();
    }

    set followingSystemFontScale(l6) {
        this.__followingSystemFontScale.set(l6);
    }

    get maxAppFontScale() {
        return this.__maxAppFontScale.get();
    }

    set maxAppFontScale(k6) {
        this.__maxAppFontScale.set(k6);
    }

    get treeViewTheme() {
        return this.__treeViewTheme.get();
    }

    set treeViewTheme(j6) {
        this.__treeViewTheme.set(j6);
    }

    aboutToAppear() {
        if (this.item.getNodeItem().imageNode) {
            this.item.imageSource = this.item.getNodeItem().imageNode?.source;
        }
        let i6 = this.getUIContext();
        this.followingSystemFontScale = i6.isFollowingSystemFontScale();
        this.maxAppFontScale = i6.getMaxFontScale();
    }

    decideFontScale() {
        let g6 = this.getUIContext();
        let h6 = g6.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.followingSystemFontScale) {
            return 1;
        }
        return Math.min(h6, this.maxAppFontScale, MAX_FONT_SCALE);
    }

    getInputTextMaxFontSize() {
        let f6 = this.decideFontScale() * this.inputFontSize + 'vp';
        return f6;
    }

    checkInvalidPattern(e6) {
        return new RegExp('/[\\\/:*?" < > |] /').test(e6);
    }

    checkIsAllCN(d6) {
        return new RegExp('/^[\u4e00-\u9fa5]+$/').test(d6);
    }

    popupForShowTitle(t5, u5, v5, w5 = null) {
        this.observeComponentCreation((b6, c6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(b6);
            Row.create();
            Row.backgroundColor(u5);
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
            if (!c6) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((z5, a6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(z5);
            Text.create(t5);
            Text.fontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_body2'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            });
            Text.fontWeight('regular');
            Text.fontColor(v5);
            Text.minFontScale(MIN_FONT_SCALE);
            Text.maxFontScale(this.decideFontScale());
            if (!a6) {
                Text.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        Text.pop();
        Row.pop();
    }

    builder(n5 = null) {
        this.observeComponentCreation((p5, q5) => {
            ViewStackProcessor.StartGetAccessRecordingFor(p5);
            If.create();
            if (this.listTreeViewMenu) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.listTreeViewMenu.bind(this)(n5 ? n5 : this);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!q5) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
    }

    initialRender() {
        this.observeComponentCreation((n1, o1) => {
            ViewStackProcessor.StartGetAccessRecordingFor(n1);
            If.create();
            if (this.item.getNodeIsShow()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((l5, m5) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(l5);
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
                        if (!m5) {
                            Stack.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((w4, x4) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(w4);
                        Column.create();
                        Column.opacity(this.listNodeDataSource.getListItemOpacity(ObservedObject.GetRawObject(this.item)));
                        Column.onHover((k5) => {
                            if (k5) {
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
                        Column.onTouch((h5) => {
                            this.count++;
                            if (this.count > 1) {
                                this.count--;
                                return;
                            }
                            this.index = this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId());
                            this.listNodeDataSource.setClickIndex(this.index);
                            let i5 = this.item.getNodeCurrentNodeId();
                            if (h5.type === TouchType.Down) {
                                this.item.setNodeColor(this.treeViewTheme.itemPressedBgColor);
                            }
                            else if (h5.type === TouchType.Up) {
                                if (!(typeof this.treeViewTheme.itemSelectedBgColor === 'string')) {
                                    this.item.setNodeColor(COLOR_SELECT);
                                }
                                else {
                                    this.item.setNodeColor(this.treeViewTheme.itemSelectedBgColor);
                                }
                                if (this.item.getNodeItem().imageNode !== null) {
                                    this.item.getNodeItem().imageNode?.setImageSource(InteractionStatus.SELECTED);
                                    this.listNodeDataSource.setImageSource(this.index, InteractionStatus.SELECTED);
                                    this.item.imageSource = this.item.getNodeItem().imageNode?.source;
                                }
                                this.item.getNodeItem().mainTitleNode?.setMainTitleSelected(true);
                                let j5 = { currentNodeId: i5 };
                                this.appEventBus.emit(TreeListenType.NODE_CLICK, j5);
                            }
                            if (this.listNodeDataSource.getLastIndex() !== -1 && this.index !== this.listNodeDataSource.getLastIndex()) {
                                this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false, this.listNodeDataSource.getLastIndex());
                                this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(), MenuOperation.COMMIT_NODE);
                            }
                            this.lastIndex = this.index;
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
                        Column.onMouse((f5) => {
                            let g5 = this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId());
                            if (f5.button === MouseButton.Right) {
                                this.listNodeDataSource.handleEvent(Event.MOUSE_BUTTON_RIGHT, this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId()));
                                this.listTreeViewMenu = this.item.getMenu();
                                this.listNodeDataSource.setClickIndex(g5);
                                clearTimeout(this.item.getNodeItem().mainTitleNode?.popUpTimeout);
                            }
                            f5.stopPropagation();
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
                        Column.onAreaChange((c5, d5) => {
                            let e5 = Number.parseInt(d5.width.toString());
                            this.columnWidth = e5;
                        });
                        if (!x4) {
                            Column.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((u4, v4) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(u4);
                        Stack.create({ alignContent: Alignment.Bottom });
                        Stack.focusable(true);
                        if (!v4) {
                            Stack.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((s4, t4) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(s4);
                        Divider.create();
                        Divider.height(this.listNodeDataSource.getFlagLine().flagLineHeight);
                        Divider.color(this.listNodeDataSource.getFlagLine().flagLineColor);
                        Divider.visibility(this.listNodeDataSource.getVisibility(ObservedObject.GetRawObject(this.item)));
                        Divider.lineCap(LineCapStyle.Round);
                        Divider.margin({ start: LengthMetrics.vp(this.item.getFlagLineLeftMargin()) });
                        Divider.focusable(true);
                        if (!t4) {
                            Divider.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((o4, p4) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(o4);
                        Row.create({});
                        Row.focusable(true);
                        Row.width('100%');
                        Gesture.create(GesturePriority.Low);
                        TapGesture.create({ count: 2 });
                        TapGesture.onAction((r4) => {
                            this.listNodeDataSource.expandAndCollapseNode(this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId()));
                        });
                        TapGesture.pop();
                        Gesture.pop();
                        Row.height(this.item.getNodeHeight());
                        Row.padding({ start: LengthMetrics.vp(this.item.getNodeLeftPadding()) });
                        Row.bindContextMenu({ builder: this.builder.bind(this) }, ResponseType.RightClick);
                        if (!p4) {
                            Row.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((e4, f4) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(e4);
                        If.create();
                        if (this.item.getNodeItem().imageNode) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation((m4, n4) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(m4);
                                    Row.create();
                                    Row.focusable(true);
                                    Row.backgroundColor(COLOR_IMAGE_ROW);
                                    Row.margin({
                                        end: getLengthMetricsByResourceOrNumber(this.item.getNodeItem().imageNode?.itemRightMargin)
                                    });
                                    Row.height(this.item.getNodeItem().imageNode?.itemHeight);
                                    Row.width(this.item.getNodeItem().imageNode?.itemWidth);
                                    if (!n4) {
                                        Row.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                this.observeComponentCreation((k4, l4) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(k4);
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
                                    if (!l4) {
                                        Image.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                Row.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                        if (!f4) {
                            If.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    If.pop();
                    this.observeComponentCreation((c4, d4) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(c4);
                        Row.create();
                        Row.layoutWeight(1);
                        Row.focusable(true);
                        if (!d4) {
                            Row.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((v3, w3) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(v3);
                        If.create();
                        if (this.item.getNodeItem().mainTitleNode && this.item.getIsShowTitle()) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation((a4, b4) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(a4);
                                    Text.create(this.item.getNodeItem().mainTitleNode?.title);
                                    Text.minFontScale(MIN_FONT_SCALE);
                                    Text.maxFontScale(this.decideFontScale());
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
                                    if (!b4) {
                                        Text.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                Text.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                        if (!w3) {
                            If.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    If.pop();
                    this.observeComponentCreation((b3, c3) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(b3);
                        If.create();
                        if (this.item.getNodeItem().mainTitleNode && this.item.getNodeItem().inputText &&
                        this.item.getIsShowInputText()) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation((t3, u3) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(t3);
                                    Row.create();
                                    Row.backgroundColor(this.item.getNodeItem().inputText?.backgroundColor);
                                    Row.borderRadius(this.item.getNodeItem().inputText?.borderRadius);
                                    Row.margin({
                                        end: getLengthMetricsByResourceOrNumber(this.item.getNodeItem()
                                            .inputText?.itemRightMargin)
                                    });
                                    if (!u3) {
                                        Row.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                this.observeComponentCreation((h3, i3) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(h3);
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
                                    TextInput.onChange((n3) => {
                                        let o3 = this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId());
                                        let p3 = '';
                                        let q3 = false;
                                        let r3 = false;
                                        if (this.checkInvalidPattern(n3)) {
                                            for (let s3 = 0; s3 < n3.length; s3++) {
                                                if (!this.checkInvalidPattern(n3[s3])) {
                                                    p3 += n3[s3];
                                                }
                                            }
                                            q3 = true;
                                            this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.INVALID_ERROR, true, o3);
                                        }
                                        else {
                                            p3 = n3;
                                            q3 = false;
                                        }
                                        if ((this.checkIsAllCN(p3) && p3.length > this.MAX_CN_LENGTH) ||
                                            (!this.checkIsAllCN(p3) && p3.length > this.MAX_EN_LENGTH)) {
                                            p3 = this.checkIsAllCN(p3) ?
                                            p3.substr(0, this.MAX_CN_LENGTH) : p3.substr(0, this.MAX_EN_LENGTH);
                                            r3 = true;
                                            this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.LENGTH_ERROR, true, o3);
                                        }
                                        else {
                                            r3 = false;
                                        }
                                        if (!r3 && !q3) {
                                            this.listNodeDataSource.setMainTitleNameOnEdit(o3, p3);
                                        }
                                    });
                                    TextInput.onSubmit((l3) => {
                                        let m3 = this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId());
                                        this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false, m3);
                                        this.listNodeDataSource.setItemVisibilityOnEdit(m3, MenuOperation.COMMIT_NODE);
                                    });
                                    if (!i3) {
                                        TextInput.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                Row.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                        if (!c3) {
                            If.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    If.pop();
                    this.observeComponentCreation((z2, a3) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(z2);
                        Blank.create();
                        if (!a3) {
                            Blank.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    Blank.pop();
                    Row.pop();
                    this.observeComponentCreation((p2, q2) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(p2);
                        If.create();
                        if (this.listNodeDataSource.hasSubtitle(this.item.getNodeCurrentNodeId())) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation((x2, y2) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(x2);
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
                                    if (!y2) {
                                        Row.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                this.observeComponentCreation((v2, w2) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(v2);
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
                                    if (!w2) {
                                        Text.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                Text.pop();
                                Row.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                        if (!q2) {
                            If.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    If.pop();
                    this.observeComponentCreation((d2, e2) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(d2);
                        If.create();
                        if (this.item.getNodeItem().imageCollapse) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation((n2, o2) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(n2);
                                    Row.create();
                                    Row.focusable(true);
                                    Row.height(this.item.getNodeItem().imageCollapse?.itemHeight);
                                    Row.width(this.item.getNodeItem().imageCollapse?.itemWidth);
                                    if (!o2) {
                                        Row.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                this.observeComponentCreation((j2, k2) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(j2);
                                    Image.create(this.item.getNodeItem().imageCollapse?.collapseSource);
                                    Image.fillColor(this.item.getNodeItem().imageCollapse?.isCollapse ?
                                    this.treeViewTheme.arrowIconColor : COLOR_IMAGE_EDIT);
                                    Image.align(Alignment.End);
                                    Image.objectFit(ImageFit.Contain);
                                    Image.height(this.item.getNodeItem().imageCollapse?.itemHeight);
                                    Image.width(this.item.getNodeItem().imageCollapse?.itemWidth);
                                    Image.opacity(!this.item.getIsHighLight() ?
                                        this.item.getNodeItem().imageCollapse?.opacity : this.item.getNodeItem().imageCollapse?.noOpacity);
                                    Image.onTouch((m2) => {
                                        if (m2.type === TouchType.Down) {
                                            this.listNodeDataSource.expandAndCollapseNode(this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId()));
                                            this.listNodeDataSource.setCurrentFocusNodeId(this.item.getNodeCurrentNodeId());
                                        }
                                        m2.stopPropagation();
                                    });
                                    Image.focusable(true);
                                    Image.matchTextDirection((this.item.getNodeItem()
                                        .imageCollapse?.collapseSource === ARROW_RIGHT || this.item.getNodeItem()
                                        .imageCollapse?.collapseSource === ARROW_RIGHT_WITHE) ? true : false);
                                    if (!k2) {
                                        Image.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                Row.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                        if (!e2) {
                            If.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
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
            if (!o1) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export class NodeItem {
    constructor(l1) {
        this.currentNodeId = l1.currentNodeId ?? -1;
        this.parentNodeId = l1.parentNodeId ?? -1;
        this.isFolder = l1.isFolder;
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

    set itemWidth(k1) {
        this.width = k1;
    }

    get itemWidth() {
        return this.width;
    }

    set itemHeight(j1) {
        this.height = j1;
    }

    get itemHeight() {
        return this.height;
    }

    set itemRightMargin(i1) {
        this.rightMargin = i1;
    }

    get itemRightMargin() {
        return this.rightMargin;
    }
}

export class CollapseImageNode extends NodeBaseInfo {
    constructor(b1, c1, d1, e1, f1, g1, h1) {
        super();
        this.rightMargin = {
            'id': -1,
            'type': 10002,
            params: ['sys.float.ohos_id_elements_margin_horizontal_m'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.imageSource = b1;
        this.rightMargin = f1;
        this.imageOpacity = c1;
        this.itemWidth = d1;
        this.itemHeight = e1;
        this.imageCollapseSource = b1;
        this.isImageCollapse = g1;
        this.collapseImageType = h1;
    }

    get source() {
        return this.imageSource;
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

    createCollapseImageNodeByType(z) {
        let a1;
        switch (z) {
            case CollapseImageType.ARROW_RIGHT_WHITE:
                a1 = ARROW_RIGHT_WITHE;
                break;
            case CollapseImageType.ARROW_RIGHT:
                a1 = ARROW_RIGHT;
                break;
            case CollapseImageType.ARROW_DOWN_WHITE:
                a1 = ARROW_DOWN_WITHE;
                break;
            default:
                a1 = ARROW_DOWN;
        }
        return new CollapseImageNode(a1, {
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
        }, (z === CollapseImageType.ARROW_RIGHT_WHITE || z === CollapseImageType.ARROW_DOWN_WHITE) ? false : true, z);
    }
}

class CollapseImageNodeFlyweightFactory {
    static getCollapseImageNodeByType(x) {
        let y = CollapseImageNodeFlyweightFactory.nodeMap.get(x);
        if (y === undefined) {
            y = CollapseImageNodeFactory.getInstance().createCollapseImageNodeByType(x);
            CollapseImageNodeFlyweightFactory.nodeMap.set(x, y);
        }
        return y;
    }

    static getCollapseImageNode(t, u, v) {
        let w = v;
        if (t == InteractionStatus.EDIT ||
            t === InteractionStatus.DRAG_INSERT) {
            if (u === NodeStatus.COLLAPSE) {
                w = CollapseImageType.ARROW_RIGHT_WHITE;
            }
            else {
                w = CollapseImageType.ARROW_DOWN_WHITE;
            }
        }
        else if (t === InteractionStatus.FINISH_EDIT ||
            t === InteractionStatus.FINISH_DRAG_INSERT) {
            if (u === NodeStatus.COLLAPSE) {
                w = CollapseImageType.ARROW_RIGHT;
            }
            else {
                w = CollapseImageType.ARROW_DOWN;
            }
        }
        return CollapseImageNodeFlyweightFactory.getCollapseImageNodeByType(w);
    }

    static changeImageCollapseSource(q, r) {
        let s;
        if (!r) {
            if (q === NodeStatus.COLLAPSE) {
                s = CollapseImageType.ARROW_RIGHT_WHITE;
            }
            else {
                s = CollapseImageType.ARROW_DOWN_WHITE;
            }
        }
        else {
            if (q === NodeStatus.COLLAPSE) {
                s = CollapseImageType.ARROW_RIGHT;
            }
            else {
                s = CollapseImageType.ARROW_DOWN;
            }
        }
        return CollapseImageNodeFlyweightFactory.getCollapseImageNodeByType(s);
    }
}

CollapseImageNodeFlyweightFactory.nodeMap = new Map();

export class ImageNode extends NodeBaseInfo {
    constructor(k, l, m, n, o, p) {
        super();
        this.rightMargin = {
            'id': -1,
            'type': 10002,
            params: ['sys.float.ohos_id_elements_margin_horizontal_m'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.imageSource = k;
        this.imageNormalSource = k;
        if (o !== undefined) {
            this.imageSelectedSource = o;
        }
        else {
            this.imageSelectedSource = this.imageNormalSource;
        }
        if (p !== undefined) {
            this.imageEditSource = p;
        }
        else {
            this.imageEditSource = this.imageNormalSource;
        }
        this.imageOpacity = l;
        this.itemWidth = m;
        this.itemHeight = n;
        this.imageCollapseSource = k;
        this.imageCollapseDownSource = ARROW_DOWN;
        this.imageCollapseRightSource = ARROW_RIGHT;
        this.isImageCollapse = true;
        this.currentInteractionStatus = InteractionStatus.NORMAL;
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

    changeImageCollapseSource(j) {
        if (j === NodeStatus.EXPAND) {
            this.imageCollapseSource = this.imageCollapseDownSource;
        }
        else if (j === NodeStatus.COLLAPSE) {
            this.imageCollapseSource = this.imageCollapseRightSource;
        }
    }

    setImageCollapseSource(h, i) {
        if (h === InteractionStatus.EDIT || h === InteractionStatus.DRAG_INSERT) {
            this.imageCollapseDownSource = ARROW_DOWN_WITHE;
            this.imageCollapseRightSource = ARROW_RIGHT_WITHE;
            this.isImageCollapse = false;
        }
        else if (h === InteractionStatus.FINISH_EDIT ||
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
                this.currentInteractionStatus = g;
                break;
            case InteractionStatus.SELECTED:
                if (this.currentInteractionStatus !== InteractionStatus.EDIT) {
                    this.imageSource = this.imageSelectedSource;
                    this.currentInteractionStatus = g;
                }
                break;
            case InteractionStatus.EDIT:
                this.imageSource = this.imageEditSource;
                this.currentInteractionStatus = g;
                break;
            case InteractionStatus.FINISH_EDIT:
                this.imageSource = this.imageSelectedSource;
                this.currentInteractionStatus = g;
                break;
            case InteractionStatus.DRAG_INSERT:
                this.imageSource = this.imageEditSource;
                this.currentInteractionStatus = g;
                break;
            case InteractionStatus.FINISH_DRAG_INSERT:
                this.imageSource = this.imageNormalSource;
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