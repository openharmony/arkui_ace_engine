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
var __decorate = (this && this.__decorate) || function (b27, c27, d27, e27) {
    var f27 = arguments.length, g27 = f27 < 3 ? c27 : e27 === null ? e27 = Object.getOwnPropertyDescriptor(c27, d27) : e27, h27;
    if (typeof Reflect === 'object' && typeof Reflect.decorate === 'function')
        g27 = Reflect.decorate(b27, c27, d27, e27);
    else
        for (var i27 = b27.length - 1; i27 >= 0; i27--)
            if (h27 = b27[i27])
                g27 = (f27 < 3 ? h27(g27) : f27 > 3 ? h27(c27, d27, g27) : h27(c27, d27)) || g27;
    return f27 > 3 && g27 && Object.defineProperty(c27, d27, g27), g27;
};
if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => { });
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
  id: -1,
  type: 20000,
  params: ['sys.media.ohos_ic_public_arrow_down'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
const ARROW_DOWN_WITHE = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAAAIGNIUk0AAHomAAC' +
    'AhAAA+gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAAEZ0FNQQAAsY58+1GTAAAAAXNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAAl' +
    'wSFlzAAAOxAAADsQBlSsOGwAAAKVJREFUeNpjYBgFo2AU0Bww4pL4////diC1hZGRcSo+A4DqWIDUZCB+AVTbiC7PhEfvByCeAjQgn4Dhy4E' +
    '4BYgvYFODz4JYIF4DxBOwWYJkeAAQRwBdvxGbIcy4TG9sbPzX0NCwHsjUAuIiIPsDUOwkDsPXkhwHWFwaAsQlQAwyrJsYw4myAIslIPCHGMP' +
    'xBhGO4PoGxF+AOA9o+NbRTDgKRgFxAAAzj0Grm3RjyAAAAABJRU5ErkJggg==';
const ARROW_RIGHT = {
  id: -1,
  type: 20000,
  params: ['sys.media.ohos_ic_public_arrow_right'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
const ARROW_RIGHT_WITHE = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAAAIGNIUk0AAHomAA' +
    'CAhAAA+gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAAEZ0FNQQAAsY58+1GTAAAAAXNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAA' +
    'lwSFlzAAAOxAAADsQBlSsOGwAAAKFJREFUeNpjYBgFowAE/v//bwHEPOToZSJS3XIg3k6OJcRaUALEFuRYwkyMosbGxusNDQ3XgMwCIHYAsl' +
    'cDxX5RzQJKLGEmxbvkWMJEaqQxMjKuBVI5QGwDxOnUimR08AFK81DdAmAqArl8DhDfAOKpVLUAavh2IH4CxI7A4HpDMEgpMPwFUXFGS8NJCa' +
    'L55BgOAixEqqsB4oOkGj4KRggAAN4STB9zyhGzAAAAAElFTkSuQmCC';
var Event;
(function (z26) {
    z26[z26['TOUCH_DOWN'] = 0] = 'TOUCH_DOWN';
    z26[z26['TOUCH_UP'] = 1] = 'TOUCH_UP';
    z26[z26['HOVER'] = 3] = 'HOVER';
    z26[z26['HOVER_OVER'] = 4] = 'HOVER_OVER';
    z26[z26['FOCUS'] = 5] = 'FOCUS';
    z26[z26['BLUR'] = 6] = 'BLUR';
    z26[z26['MOUSE_BUTTON_RIGHT'] = 7] = 'MOUSE_BUTTON_RIGHT';
    z26[z26['DRAG'] = 8] = 'DRAG';
})(Event || (Event = {}));
var MenuOperation;
(function (y26) {
    y26[y26['ADD_NODE'] = 0] = 'ADD_NODE';
    y26[y26['REMOVE_NODE'] = 1] = 'REMOVE_NODE';
    y26[y26['MODIFY_NODE'] = 2] = 'MODIFY_NODE';
    y26[y26['COMMIT_NODE'] = 3] = 'COMMIT_NODE';
})(MenuOperation || (MenuOperation = {}));
var PopUpType;
(function (x26) {
    x26[x26['HINTS'] = 0] = 'HINTS';
    x26[x26['WARNINGS'] = 1] = 'WARNINGS';
})(PopUpType || (PopUpType = {}));
var InputError;
(function (w26) {
    w26[w26['INVALID_ERROR'] = 0] = 'INVALID_ERROR';
    w26[w26['LENGTH_ERROR'] = 1] = 'LENGTH_ERROR';
    w26[w26['NONE'] = 2] = 'NONE';
})(InputError || (InputError = {}));
var Flag;
(function (v26) {
    v26[v26['DOWN_FLAG'] = 0] = 'DOWN_FLAG';
    v26[v26['UP_FLAG'] = 1] = 'UP_FLAG';
    v26[v26['NONE'] = 2] = 'NONE';
})(Flag || (Flag = {}));
export var NodeStatus;
(function (u26) {
    u26[u26['EXPAND'] = 0] = 'EXPAND';
    u26[u26['COLLAPSE'] = 1] = 'COLLAPSE';
})(NodeStatus || (NodeStatus = {}));
export var InteractionStatus;
(function (t26) {
    t26[t26['NORMAL'] = 0] = 'NORMAL';
    t26[t26['SELECTED'] = 1] = 'SELECTED';
    t26[t26['EDIT'] = 2] = 'EDIT';
    t26[t26['FINISH_EDIT'] = 3] = 'FINISH_EDIT';
    t26[t26['DRAG_INSERT'] = 4] = 'DRAG_INSERT';
    t26[t26['FINISH_DRAG_INSERT'] = 5] = 'FINISH_DRAG_INSERT';
})(InteractionStatus || (InteractionStatus = {}));
var CollapseImageType;
(function (y22) {
    y22[y22['ARROW_DOWN'] = 0] = 'ARROW_DOWN';
    y22[y22['ARROW_RIGHT'] = 1] = 'ARROW_RIGHT';
    y22[y22['ARROW_DOWN_WHITE'] = 2] = 'ARROW_DOWN_WHITE';
    y22[y22['ARROW_RIGHT_WHITE'] = 3] = 'ARROW_RIGHT_WHITE';
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
    createNodeByNodeParam(k21) {
        let x22 = this.createNode();
        if (k21.icon) {
            x22.imageNode = new ImageNode(k21.icon, {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_alpha_content_fourth'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            }, IMAGE_NODE_HEIGHT, IMAGE_NODE_WIDTH, k21.selectedIcon, k21.editIcon);
        }
        if (k21.primaryTitle) {
            x22.mainTitleNode = new MainTitleNode(k21.primaryTitle);
        }
        return x22;
    }
}
TreeViewNodeItemFactory.instance = new TreeViewNodeItemFactory();
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
      id: -1,
      type: 10001,
      params: ['sys.color.ohos_id_color_primary'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    };
    this.secondaryTitleFontColor = {
      id: -1,
      type: 10001,
      params: ['sys.color.ohos_id_color_secondary'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    };
    this.primaryTitleActiveFontColor = {
      id: -1,
      type: 10001,
      params: ['sys.color.ohos_id_color_text_primary_activated'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    };
    this.itemPressedBgColor = {
      id: -1,
      type: 10001,
      params: ['sys.color.ohos_id_color_click_effect'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    };
    this.itemHoverBgColor = {
      id: -1,
      type: 10001,
      params: ['sys.color.ohos_id_color_hover'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    };
    this.borderFocusedColor = {
      id: -1,
      type: 10001,
      params: ['sys.color.ohos_id_color_focused_outline'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    };
    this.leftIconColor = {
      id: -1,
      type: 10001,
      params: ['sys.color.icon_secondary'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    };
    this.leftIconActiveColor = {
      id: -1,
      type: 10001,
      params: ['sys.color.icon_secondary'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    };
    this.arrowIconColor = {
      id: -1,
      type: 10001,
      params: ['sys.color.icon_tertiary'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    };
  }
  static getInstance() {
      if (!TreeViewTheme.instance) {
          TreeViewTheme.instance = new TreeViewTheme();
      }
      return TreeViewTheme.instance;
  }
}
TreeViewTheme.instance = new TreeViewTheme();
let NodeInfo = class NodeInfo {
    constructor(r26, s26) {
        this.imageSource = '';
        this.borderWidth = { has: BORDER_WIDTH_HAS, none: BORDER_WIDTH_NONE };
        this.canShowFlagLine = false;
        this.isOverBorder = false;
        this.canShowBottomFlagLine = false;
        this.isHighLight = false;
        this.isModify = false;
        this.treeViewTheme = TreeViewTheme.getInstance();
        this.fontColor = '';
        this.node = r26;
        this.nodeParam = s26;
        this.nodeItemView = TreeViewNodeItemFactory.getInstance().createNodeByNodeParam(s26);
        this.popUpInfo = {
            popUpIsShow: false,
            popUpEnableArrow: false,
            popUpColor: undefined,
            popUpText: '',
            popUpTextColor: undefined,
        };
        this.nodeHeight = NODE_HEIGHT;
        this.nodeLeftPadding = r26.nodeLevel * LEVEL_MARGIN + MARGIN_OFFSET;
        this.nodeColor = {
          id: -1,
          type: 10001,
          params: ['sys.color.ohos_id_color_background'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        };
        this.nodeIsShow = (this.node.nodeLevel > 0) ? false : true;
        this.listItemHeight = (this.node.nodeLevel > 0) ? LIST_ITEM_HEIGHT_NONE : LIST_ITEM_HEIGHT;
        this.isShowTitle = true;
        this.isShowInputText = false;
        this.isSelected = false;
        this.status = {
          normal: {
            id: -1,
            type: 10001,
            params: ['sys.color.ohos_id_color_background_transparent'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
          hover: this.treeViewTheme.itemHoverBgColor,
          press: this.treeViewTheme.itemPressedBgColor,
          selected: this.treeViewTheme.itemSelectedBgColor,
          highLight: {
            id: -1,
            type: 10001,
            params: ['sys.color.ohos_id_color_activated'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
        };
        this.nodeBorder = {
          borderWidth: BORDER_WIDTH_NONE,
          borderColor: this.treeViewTheme.borderFocusedColor,
          borderRadius: {
            id: -1,
            type: 10002,
            params: ['sys.float.ohos_id_corner_radius_clicked'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
        };
        this.flagLineLeftMargin = r26.nodeLevel * LEVEL_MARGIN + MARGIN_OFFSET;
    }
    addImageCollapse(q26) {
        if (q26) {
            this.nodeItemView.imageCollapse =
                CollapseImageNodeFlyweightFactory.getCollapseImageNodeByType(CollapseImageType.ARROW_RIGHT);
        }
        else {
            this.nodeItemView.imageCollapse = undefined;
        }
    }
    setFontColor(p26) {
        this.fontColor = p26;
    }
    getFontColor() {
        return this.fontColor;
    }
    getPopUpInfo() {
        return this.popUpInfo;
    }
    setPopUpIsShow(o26) {
        this.popUpInfo.popUpIsShow = o26;
    }
    setPopUpEnableArrow(n26) {
        this.popUpInfo.popUpEnableArrow = n26;
    }
    setPopUpColor(m26) {
        this.popUpInfo.popUpColor = m26;
    }
    setPopUpText(l26) {
        this.popUpInfo.popUpText = l26;
    }
    setPopUpTextColor(k26) {
        this.popUpInfo.popUpTextColor = k26;
    }
    getIsShowTitle() {
        return this.isShowTitle;
    }
    getIsShowInputText() {
        return this.isShowInputText;
    }
    setTitleAndInputTextStatus(j26) {
        if (j26) {
            this.isShowTitle = false;
            this.isShowInputText = true;
        }
        else {
            this.isShowTitle = true;
            this.isShowInputText = false;
        }
    }
    handleImageCollapseAfterAddNode(i26) {
        if (i26) {
            this.nodeItemView.imageCollapse =
                CollapseImageNodeFlyweightFactory.getCollapseImageNodeByType(CollapseImageType.ARROW_DOWN);
        }
        else {
            this.nodeItemView.imageCollapse = undefined;
        }
    }
    setNodeColor(h26) {
        if (h26 === undefined) {
            return;
        }
        this.nodeColor = h26;
    }
    getNodeColor() {
        return this.nodeColor;
    }
    setListItemHeight(g26) {
        this.listItemHeight = g26;
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
    setNodeIsShow(f26) {
        this.nodeIsShow = f26;
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
    setNodeBorder(e26) {
        this.nodeBorder.borderWidth = e26 ? this.borderWidth.has : this.borderWidth.none;
    }
    getChildNodeInfo() {
        return this.node.childNodeInfo;
    }
    getMenu() {
        return this.nodeParam.container;
    }
    setIsSelected(d26) {
        this.isSelected = d26;
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
    setCanShowFlagLine(c26) {
        this.canShowFlagLine = c26;
    }
    getCanShowFlagLine() {
        return this.canShowFlagLine;
    }
    setFlagLineLeftMargin(b26) {
        if (b26 === undefined) {
            return;
        }
        this.flagLineLeftMargin = b26 * LEVEL_MARGIN + MARGIN_OFFSET;
    }
    getFlagLineLeftMargin() {
        return this.flagLineLeftMargin;
    }
    getNodeLevel() {
        return this.node.nodeLevel;
    }
    setIsOverBorder(a26) {
        this.isOverBorder = a26;
    }
    getIsOverBorder() {
        return this.isOverBorder;
    }
    setCanShowBottomFlagLine(z25) {
        this.canShowBottomFlagLine = z25;
    }
    getCanShowBottomFlagLine() {
        return this.canShowBottomFlagLine;
    }
    setIsHighLight(y25) {
        this.isHighLight = y25;
    }
    getIsHighLight() {
        return this.isHighLight;
    }
    setIsModify(x25) {
        this.isModify = x25;
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
(function (w25) {
    w25['NODE_CLICK'] = 'NodeClick';
    w25['NODE_ADD'] = 'NodeAdd';
    w25['NODE_DELETE'] = 'NodeDelete';
    w25['NODE_MODIFY'] = 'NodeModify';
    w25['NODE_MOVE'] = 'NodeMove';
})(TreeListenType || (TreeListenType = {}));
export class TreeListener {
    constructor() {
        this._events = [];
        this._once_events = [];
    }
    on(s25, t25) {
        if (Array.isArray(s25)) {
            for (let u25 = 0, v25 = s25.length; u25 < v25; u25++) {
                this.on(s25[u25], t25);
            }
        }
        else {
            (this._events[s25] || (this._events[s25] = [])).push(t25);
        }
    }
    once(q25, r25) {
        if (Array.isArray(q25)) {
            this.off(q25, r25);
        }
        else {
            (this._once_events[q25] || (this._once_events[q25] = [])).push(r25);
        }
    }
    off(j25, k25) {
        if (j25 === null) {
            this._events = [];
        }
        if (Array.isArray(j25)) {
            for (let o25 = 0, p25 = j25.length; o25 < p25; o25++) {
                this.off(j25[o25], k25);
            }
        }
        let l25 = this._events[j25];
        if (!l25) {
            return;
        }
        if (k25 === null) {
            this._events[j25] = null;
        }
        let m25 = l25.length;
        while (m25--) {
            let n25 = l25[m25];
            if (n25 === k25) {
                l25.splice(m25, 1);
                break;
            }
        }
    }
    emit(z24, a25) {
        if (this._once_events[z24]) {
            let f25 = Array.from(this._once_events[z24]);
            if (f25) {
                for (let g25 = 0, h25 = f25.length; g25 < h25; g25++) {
                    try {
                        f25[g25](a25);
                    }
                    catch (i25) {
                        throw new Error('once function callbacks error.');
                    }
                }
                this._once_events[z24] = null;
            }
        }
        else if (this._events[z24]) {
            let b25 = Array.from(this._events[z24]);
            if (b25) {
                for (let c25 = 0, d25 = b25.length; c25 < d25; c25++) {
                    try {
                        b25[c25](a25);
                    }
                    catch (e25) {
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
    constructor(t24, u24, v24, w24 = -1, x24 = undefined, y24) {
        super(t24, v24, w24, y24);
        if (typeof x24 === 'function') {
            this.paramsGenerator_ = x24;
        }
        this.treeController = new TreeController();
        this.__nodeList = new ObservedPropertyObjectPU([], this, 'nodeList');
        this.listNodeDataSource = new ListNodeDataSource();
        this.__item = new ObservedPropertyObjectPU(null, this, 'item');
        this.__touchCount = new ObservedPropertySimplePU(0, this, 'touchCount');
        this.__dropSelectedIndex = new ObservedPropertySimplePU(
          0,
          this,
          'dropSelectedIndex'
        );
        this.__viewLastIndex = new ObservedPropertySimplePU(
          -1,
          this,
          'viewLastIndex'
        );
        this.__listItemBgColor = new ObservedPropertyObjectPU(
          {
            id: -1,
            type: 10001,
            params: ['sys.color.ohos_id_color_background_transparent'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
          this,
          'listItemBgColor'
        );
        this.__treeViewTheme = new ObservedPropertyObjectPU(
          TreeViewTheme.getInstance(),
          this,
          'treeViewTheme'
        );
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
            id: -1,
            type: 10002,
            params: ['sys.float.ohos_id_card_margin_start'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
          right: {
            id: -1,
            type: 10002,
            params: ['sys.float.ohos_id_card_margin_end'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
          top: {
            id: -1,
            type: 10002,
            params: ['sys.float.ohos_id_text_margin_vertical'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
          bottom: {
            id: -1,
            type: 10002,
            params: ['sys.float.ohos_id_text_margin_vertical'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
        };
        this.textInputPadding = {
          left: {
            id: -1,
            type: 10002,
            params: ['sys.float.padding_level0'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
          right: {
            id: -1,
            type: 10002,
            params: ['sys.float.padding_level0'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
          top: {
            id: -1,
            type: 10002,
            params: ['sys.float.padding_level0'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
          bottom: {
            id: -1,
            type: 10002,
            params: ['sys.float.padding_level0'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
        };
        this.setInitiallyProvidedValue(u24);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(s24) {
        if (s24.treeController !== undefined) {
            this.treeController = s24.treeController;
        }
        if (s24.nodeList !== undefined) {
            this.nodeList = s24.nodeList;
        }
        if (s24.listNodeDataSource !== undefined) {
            this.listNodeDataSource = s24.listNodeDataSource;
        }
        if (s24.item !== undefined) {
            this.item = s24.item;
        }
        if (s24.touchCount !== undefined) {
            this.touchCount = s24.touchCount;
        }
        if (s24.dropSelectedIndex !== undefined) {
            this.dropSelectedIndex = s24.dropSelectedIndex;
        }
        if (s24.viewLastIndex !== undefined) {
            this.viewLastIndex = s24.viewLastIndex;
        }
        if (s24.listItemBgColor !== undefined) {
            this.listItemBgColor = s24.listItemBgColor;
        }
        if (s24.treeViewTheme !== undefined) {
            this.treeViewTheme = s24.treeViewTheme;
        }
        if (s24.listTreeViewMenu !== undefined) {
            this.listTreeViewMenu = s24.listTreeViewMenu;
        }
        if (s24.MAX_CN_LENGTH !== undefined) {
            this.MAX_CN_LENGTH = s24.MAX_CN_LENGTH;
        }
        if (s24.MAX_EN_LENGTH !== undefined) {
            this.MAX_EN_LENGTH = s24.MAX_EN_LENGTH;
        }
        if (s24.INITIAL_INVALID_VALUE !== undefined) {
            this.INITIAL_INVALID_VALUE = s24.INITIAL_INVALID_VALUE;
        }
        if (s24.MAX_TOUCH_DOWN_COUNT !== undefined) {
            this.MAX_TOUCH_DOWN_COUNT = s24.MAX_TOUCH_DOWN_COUNT;
        }
        if (s24.isMultiPress !== undefined) {
            this.isMultiPress = s24.isMultiPress;
        }
        if (s24.touchDownCount !== undefined) {
            this.touchDownCount = s24.touchDownCount;
        }
        if (s24.appEventBus !== undefined) {
            this.appEventBus = s24.appEventBus;
        }
        if (s24.itemPadding !== undefined) {
            this.itemPadding = s24.itemPadding;
        }
        if (s24.textInputPadding !== undefined) {
            this.textInputPadding = s24.textInputPadding;
        }
    }
    updateStateVars(r24) {
    }
    purgeVariableDependenciesOnElmtId(q24) {
        this.__nodeList.purgeDependencyOnElmtId(q24);
        this.__item.purgeDependencyOnElmtId(q24);
        this.__touchCount.purgeDependencyOnElmtId(q24);
        this.__dropSelectedIndex.purgeDependencyOnElmtId(q24);
        this.__viewLastIndex.purgeDependencyOnElmtId(q24);
        this.__listItemBgColor.purgeDependencyOnElmtId(q24);
        this.__treeViewTheme.purgeDependencyOnElmtId(q24);
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
    set nodeList(p24) {
        this.__nodeList.set(p24);
    }
    get item() {
        return this.__item.get();
    }
    set item(o24) {
        this.__item.set(o24);
    }
    get touchCount() {
        return this.__touchCount.get();
    }
    set touchCount(n24) {
        this.__touchCount.set(n24);
    }
    get dropSelectedIndex() {
        return this.__dropSelectedIndex.get();
    }
    set dropSelectedIndex(m24) {
        this.__dropSelectedIndex.set(m24);
    }
    get viewLastIndex() {
        return this.__viewLastIndex.get();
    }
    set viewLastIndex(l24) {
        this.__viewLastIndex.set(l24);
    }
    get listItemBgColor() {
        return this.__listItemBgColor.get();
    }
    set listItemBgColor(k24) {
        this.__listItemBgColor.set(k24);
    }
    get treeViewTheme() {
        return this.__treeViewTheme.get();
    }
    set treeViewTheme(j24) {
        this.__treeViewTheme.set(j24);
    }
    NullBuilder(i24 = null) {
    }
    onWillApplyTheme(h24) {
        this.treeViewTheme.itemSelectedBgColor = h24.colors.interactiveSelect;
        this.treeViewTheme.itemPressedBgColor = h24.colors.interactivePressed;
        this.treeViewTheme.itemHoverBgColor = h24.colors.interactiveHover;
        this.treeViewTheme.primaryTitleFontColor = h24.colors.fontPrimary;
        this.treeViewTheme.secondaryTitleFontColor = h24.colors.fontSecondary;
        this.treeViewTheme.primaryTitleActiveFontColor = h24.colors.interactiveActive;
        this.treeViewTheme.borderFocusedColor = h24.colors.interactiveFocus;
        this.treeViewTheme.leftIconColor = h24.colors.iconSecondary;
        this.treeViewTheme.leftIconActiveColor = h24.colors.interactiveActive;
        this.treeViewTheme.arrowIconColor = h24.colors.iconPrimary;
        this.treeController.treeViewTheme = this.treeViewTheme;
    }
    aboutToAppear() {
        if (this.treeController !== null) {
            this.listNodeDataSource = this.treeController.getListNodeDataSource();
            this.nodeList = this.treeController.getListNodeDataSource().listNode;
            this.item = this.treeController.getListNodeDataSource().listNode;
        }
    }
    popupForShowTitle(x23, y23, z23, a24 = null) {
        this.observeComponentCreation2((f24, g24) => {
            Row.create();
            Row.backgroundColor(y23);
            Row.border({
              radius: {
                id: -1,
                type: 10002,
                params: ['sys.float.ohos_id_elements_margin_horizontal_l'],
                bundleName: '__harDefaultBundleName__',
                moduleName: '__harDefaultModuleName__',
              },
            });
            Row.padding({
              left: {
                id: -1,
                type: 10002,
                params: ['sys.float.ohos_id_elements_margin_horizontal_l'],
                bundleName: '__harDefaultBundleName__',
                moduleName: '__harDefaultModuleName__',
              },
              right: {
                id: -1,
                type: 10002,
                params: ['sys.float.ohos_id_elements_margin_horizontal_l'],
                bundleName: '__harDefaultBundleName__',
                moduleName: '__harDefaultModuleName__',
              },
              top: {
                id: -1,
                type: 10002,
                params: ['sys.float.ohos_id_card_margin_middle'],
                bundleName: '__harDefaultBundleName__',
                moduleName: '__harDefaultModuleName__',
              },
              bottom: {
                id: -1,
                type: 10002,
                params: ['sys.float.ohos_id_card_margin_middle'],
                bundleName: '__harDefaultBundleName__',
                moduleName: '__harDefaultModuleName__',
              },
            });
        }, Row);
        this.observeComponentCreation2((d24, e24) => {
            Text.create(x23);
            Text.fontSize({
              id: -1,
              type: 10002,
              params: ['sys.float.ohos_id_text_size_body2'],
              bundleName: '__harDefaultBundleName__',
              moduleName: '__harDefaultModuleName__',
            });
            Text.fontWeight('regular');
            Text.fontColor(z23);
        }, Text);
        Text.pop();
        Row.pop();
    }
    builder(w23 = null) {
        this.listTreeViewMenu.bind(this)(w23 ? w23 : this);
    }
    draggingPopup(v22, w22 = null) {
        this.observeComponentCreation2((u23, v23) => {
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
                id: -1,
                type: 10002,
                params: ['sys.float.ohos_id_corner_radius_default_m'],
                bundleName: '__harDefaultBundleName__',
                moduleName: '__harDefaultModuleName__',
              },
              color: SHADOW_COLOR,
              offsetY: 0,
            });
            Row.borderRadius(this.listNodeDataSource.getDragPopupPara().borderRadius);
        }, Row);
        this.observeComponentCreation2((k23, l23) => {
            If.create();
            if (v22.getNodeItem().imageNode) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((s23, t23) => {
                        Row.create();
                        Row.backgroundColor(COLOR_IMAGE_ROW);
                        Row.margin({ end: getLengthMetricsByResourceOrNumber(v22.getNodeItem().imageNode?.itemRightMargin) });
                        Row.height(v22.getNodeItem().imageNode?.itemHeight);
                        Row.width(v22.getNodeItem().imageNode?.itemWidth);
                    }, Row);
                    this.observeComponentCreation2((q23, r23) => {
                        Image.create(v22.getNodeItem().imageNode?.normalSource);
                        Image.objectFit(ImageFit.Contain);
                        Image.height(v22.getNodeItem().imageNode?.itemHeight);
                        Image.width(v22.getNodeItem().imageNode?.itemWidth);
                        Image.opacity(this.listNodeDataSource.getDragPopupPara().imageOpacity);
                        Image.matchTextDirection((v22.getNodeItem().imageCollapse?.collapseSource === ARROW_RIGHT || v22.getNodeItem()
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
        this.observeComponentCreation2((i23, j23) => {
            Row.create();
            Row.constraintSize({
                minWidth: v22.getNodeItem().imageNode ?
                    this.listNodeDataSource.getDragPopupPara().textConstraintSize.minWidth1 :
                    this.listNodeDataSource.getDragPopupPara().textConstraintSize.minWidth2,
                maxWidth: v22.getNodeItem().imageNode ?
                    this.listNodeDataSource.getDragPopupPara().textConstraintSize.maxWidth1 :
                    this.listNodeDataSource.getDragPopupPara().textConstraintSize.maxWidth2
            });
        }, Row);
        this.observeComponentCreation2((b23, c23) => {
            If.create();
            if (v22.getNodeItem().mainTitleNode && v22.getIsShowTitle()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((g23, h23) => {
                        Text.create(v22.getNodeItem().mainTitleNode?.title);
                        Text.maxLines(1);
                        Text.fontSize(v22.getNodeItem().mainTitleNode?.size);
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
        this.setImageSources(this.viewLastIndex, InteractionStatus.NORMAL);
        this.nodeList[this.viewLastIndex].setNodeColor({
          id: -1,
          type: 10001,
          params: ['sys.color.ohos_id_color_background_transparent'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        });
        this.nodeList[this.viewLastIndex].fontColor =
          this.treeViewTheme.primaryTitleFontColor;
        this.listNodeDataSource.listNode[this.viewLastIndex].setNodeColor({
          id: -1,
          type: 10001,
          params: ['sys.color.ohos_id_color_background_transparent'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        });
        this.listNodeDataSource.listNode[this.viewLastIndex].fontColor =
          this.treeViewTheme.primaryTitleFontColor;
        this.listNodeDataSource.listNode[this.viewLastIndex].setIsSelected(false);
        this.listNodeDataSource.setImageSource(this.viewLastIndex, InteractionStatus.NORMAL);
    }
    setImageSources(s22, t22) {
        let u22 = this.nodeList[s22];
        u22.setIsSelected(t22 === InteractionStatus.SELECTED ||
            t22 === InteractionStatus.EDIT || t22 === InteractionStatus.FINISH_EDIT);
        if (u22.getNodeItem().mainTitleNode !== null && t22 !== InteractionStatus.DRAG_INSERT &&
            t22 !== InteractionStatus.FINISH_DRAG_INSERT) {
            u22.getNodeItem().mainTitleNode?.setMainTitleSelected(t22 === InteractionStatus.SELECTED ||
                t22 === InteractionStatus.FINISH_EDIT);
        }
        if (u22.getNodeItem().imageNode !== null) {
            u22.getNodeItem().imageNode?.setImageSource(t22);
        }
    }
    initialRender() {
        this.observeComponentCreation2((g21, h21) => {
            List.create({});
            List.onDragMove((j22, k22) => {
                if (this.isMultiPress) {
                    console.error('drag error, a item has been dragged');
                    return;
                }
                let l22 = LIST_ITEM_HEIGHT;
                let m22 = Math.floor(j22.getY() /
                    (l22 / FLAG_NUMBER)) %
                    FLAG_NUMBER ? Flag.DOWN_FLAG : Flag.UP_FLAG;
                let n22 = JSON.parse(k22).insertIndex;
                let o22 = false;
                if (n22 >= this.listNodeDataSource.totalCount()) {
                    m22 = Flag.DOWN_FLAG;
                    n22 = this.listNodeDataSource.totalCount() - 1;
                    this.listNodeDataSource.getData(n22)?.setIsOverBorder(true);
                    o22 = true;
                }
                else {
                    this.listNodeDataSource.getData(n22)?.setIsOverBorder(false);
                }
                let p22 = this.listNodeDataSource.getData(n22);
                let q22 = p22?.getNodeCurrentNodeId();
                if (n22 !== this.listNodeDataSource.getLastPassIndex() && this.listNodeDataSource.getIsInnerDrag()) {
                    let r22 = this.listNodeDataSource.getIsParentOfInsertNode(q22);
                    if (r22) {
                        this.listNodeDataSource.setPassIndex(n22);
                        if (q22 !== undefined) {
                            this.listNodeDataSource.clearTimeOutAboutDelayHighLightAndExpand(this.listNodeDataSource.findIndex(q22));
                        }
                        this.listNodeDataSource.setFlag(Flag.NONE);
                        return;
                    }
                }
                this.listNodeDataSource.setLastPassIndex(n22);
                this.listNodeDataSource.setVisibility(m22, n22 - 1, o22);
                if (q22 !== undefined && q22 !== this.listNodeDataSource.getDraggingCurrentNodeId()) {
                    this.listNodeDataSource.delayHighLightAndExpandNode(this.listNodeDataSource.findIndex(q22), q22, n22);
                }
            });
            List.onDragEnter((g22, h22) => {
                if (this.listNodeDataSource.getIsInnerDrag()) {
                    this.listNodeDataSource.setIsDrag(true);
                    let i22 = DRAG_OPACITY;
                    this.listNodeDataSource.setListItemOpacity(i22);
                }
            });
            List.onDragLeave((d22, e22) => {
                this.listNodeDataSource.hideLastLine();
                this.listNodeDataSource.clearLastTimeoutHighLight();
                this.listNodeDataSource.clearLastTimeoutExpand();
                let f22 = DRAG_OPACITY_NONE;
                this.listNodeDataSource.setListItemOpacity(f22);
                this.listNodeDataSource.setIsDrag(false);
                this.listNodeDataSource.notifyDataReload();
            });
            List.onDrop((m21, n21) => {
                this.listNodeDataSource.clearLastTimeoutExpand();
                let o21 = DRAG_OPACITY_NONE;
                this.listNodeDataSource.setListItemOpacity(o21);
                let p21 = JSON.parse(n21).insertIndex;
                let q21 = this.dropSelectedIndex;
                if (q21 - 1 > this.listNodeDataSource.totalCount() || q21 === undefined) {
                    console.error('drag error, currentNodeIndex is not found');
                    this.listNodeDataSource.setIsDrag(false);
                    return;
                }
                if (p21 === this.listNodeDataSource.totalCount()) {
                    console.log('need to insert into the position of the last line, now insertNodeIndex = insertNodeIndex - 1');
                    p21 -= 1;
                }
                let r21 = this.listNodeDataSource.getData(p21);
                if (r21 === undefined) {
                    return;
                }
                let s21 = r21.getNodeCurrentNodeId();
                if (!this.listNodeDataSource.getIsDrag() || !this.listNodeDataSource.getIsInnerDrag()) {
                    this.listNodeDataSource.clearLastTimeoutHighLight();
                    this.listNodeDataSource.setIsInnerDrag(false);
                    this.listNodeDataSource.hideLastLine();
                    this.listNodeDataSource.initialParameterAboutDelayHighLightAndExpandIndex();
                    this.listNodeDataSource.refreshSubtitle(s21);
                    this.listNodeDataSource.notifyDataReload();
                    return;
                }
                let t21 = this.listNodeDataSource.getCurrentNodeInfo();
                let u21 = r21.getNodeParentNodeId();
                let v21 = this.listNodeDataSource.getDraggingCurrentNodeId();
                let w21 = this.listNodeDataSource.getDraggingParentNodeId();
                let x21 = this.listNodeDataSource.getIsParentOfInsertNode(s21);
                if (x21) {
                    this.listNodeDataSource.clearLastTimeoutHighLight();
                    this.listNodeDataSource.setIsInnerDrag(false);
                    this.listNodeDataSource.hideLastLine();
                    this.listNodeDataSource.notifyDataChange(p21);
                    this.listNodeDataSource.initialParameterAboutDelayHighLightAndExpandIndex();
                    this.listNodeDataSource.setIsDrag(false);
                    let c22 = this.listNodeDataSource.findIndex(v21);
                    this.listNodeDataSource.setClickIndex(c22);
                    this.listNodeDataSource.handleEvent(Event.DRAG, c22);
                    return;
                }
                if (this.listNodeDataSource.getExpandAndCollapseInfo(v21) === NodeStatus.EXPAND) {
                    this.listNodeDataSource.expandAndCollapseNode(this.listNodeDataSource.findIndex(v21));
                }
                let y21 = false;
                if (this.listNodeDataSource.getExpandAndCollapseInfo(s21) === NodeStatus.COLLAPSE) {
                    let b22 = this.listNodeDataSource.findIndex(s21);
                    if (this.listNodeDataSource.listNode[b22].getIsHighLight()) {
                        this.listNodeDataSource.expandAndCollapseNode(b22);
                    }
                    y21 = true;
                }
                this.listNodeDataSource.setLastDelayHighLightId();
                if (t21 !== null && v21 !== s21) {
                    this.listNodeDataSource.alterDragNode(u21, s21, w21, v21, t21);
                    this.listNodeDataSource.hideLastLine();
                }
                else {
                    this.listNodeDataSource.hideLastLine();
                    this.listNodeDataSource.setLastPassId(v21);
                    this.listNodeDataSource.hideLastLine();
                }
                let z21 = this.listNodeDataSource.findIndex(this.listNodeDataSource.getLastDelayHighLightId());
                this.listNodeDataSource.setLastDelayHighLightIndex(z21);
                this.listNodeDataSource.clearLastTimeoutHighLight();
                this.listNodeDataSource.initialParameterAboutDelayHighLightAndExpandIndex();
                this.listNodeDataSource.setIsDrag(false);
                let a22 = this.listNodeDataSource.findIndex(v21);
                this.listNodeDataSource.setClickIndex(a22);
                this.listNodeDataSource.handleEvent(Event.DRAG, a22);
                this.listNodeDataSource.setIsInnerDrag(false);
                this.listNodeDataSource.notifyDataReload();
                this.listNodeDataSource.listNode[a22].fontColor = this.treeViewTheme.primaryTitleActiveFontColor;
                if (this.viewLastIndex !== -1 && q21 !== this.viewLastIndex) {
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
                    this.listNodeDataSource.listNode[
                      this.viewLastIndex
                    ].setNodeColor({
                      id: -1,
                      type: 10001,
                      params: [
                        'sys.color.ohos_id_color_background_transparent',
                      ],
                      bundleName: '__harDefaultBundleName__',
                      moduleName: '__harDefaultModuleName__',
                    });
                }
                this.listNodeDataSource.lastIndex = a22;
            });
        }, List);
        {
            const y19 = d20 => {
                const e20 = d20;
                {
                    const f20 = (w20, x20) => {
                        ListItem.create(() => { }, false);
                        ListItem.width('100%');
                        ListItem.height(e20.getListItemHeight());
                        ListItem.padding({
                            start: LengthMetrics.resource(this.itemPadding.left),
                            end: LengthMetrics.resource(this.itemPadding.right)
                        });
                        ListItem.align(Alignment.Start);
                        ListItem.onDragStart((a21, b21) => {
                            if (this.listNodeDataSource.getIsDrag() || this.listNodeDataSource.getIsInnerDrag() || this.isMultiPress) {
                                console.error('drag error, a item has been dragged');
                                return;
                            }
                            this.dropSelectedIndex = JSON.parse(b21).selectedIndex;
                            let c21 = JSON.parse(b21).selectedIndex;
                            let d21 = this.listNodeDataSource.getData(c21);
                            let e21 = e20.getNodeCurrentNodeId();
                            if (c21 >= this.listNodeDataSource.totalCount() || c21 === undefined) {
                                console.error('drag error, currentNodeIndex is not found in onDragStart');
                                return;
                            }
                            this.listNodeDataSource.setIsInnerDrag(true);
                            this.listNodeDataSource.setIsDrag(true);
                            this.listNodeDataSource.setCurrentNodeInfo(d21);
                            this.listNodeDataSource.setDraggingCurrentNodeId(d21?.getNodeCurrentNodeId());
                            this.listNodeDataSource.setDraggingParentNodeId(d21?.getNodeParentNodeId());
                            let f21 = DRAG_OPACITY;
                            this.listNodeDataSource.setListItemOpacity(f21);
                            this.listNodeDataSource.notifyDataChange(c21);
                            if (e21 !== d21?.getNodeCurrentNodeId()) {
                                console.error('drag is too fast,it attribute a fault to OH');
                                this.listNodeDataSource.setIsDrag(false);
                                return;
                            }
                            return { builder: () => {
                                    this.draggingPopup.call(this, d21);
                                } };
                        });
                    };
                    const g20 = () => {
                        this.observeComponentCreation2(f20, ListItem);
                        this.observeComponentCreation2((r20, s20) => {
                            Row.create();
                            Row.onTouch((u20) => {
                                this.viewLastIndex = this.listNodeDataSource.getLastIndex();
                                let v20 = this.listNodeDataSource.findIndex(e20.getNodeCurrentNodeId());
                                if (u20.type === TouchType.Down) {
                                    if (v20 !== this.viewLastIndex) {
                                        this.clearLastIndexColor();
                                        this.listNodeDataSource.lastIndex = v20;
                                        this.listNodeDataSource.setClickIndex(v20);
                                    }
                                }
                                if (u20.type === TouchType.Up) {
                                    this.listNodeDataSource.listNode[v20].setIsSelected(true);
                                    this.listNodeDataSource.setImageSource(v20, InteractionStatus.SELECTED);
                                    if (this.listNodeDataSource.listNode[v20].getNodeItem().imageNode !== null) {
                                        this.listNodeDataSource.listNode[v20].imageSource = this.listNodeDataSource.listNode[v20]
                                            .getNodeItem().imageNode?.source;
                                    }
                                    if (v20 !== this.viewLastIndex) {
                                        this.clearLastIndexColor();
                                        this.listNodeDataSource.lastIndex = v20;
                                        this.listNodeDataSource.setClickIndex(v20);
                                    }
                                    this.viewLastIndex = v20;
                                }
                                if (this.listNodeDataSource.getLastIndex() !== -1 && v20 !== this.listNodeDataSource.getLastIndex()) {
                                    this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false, this.listNodeDataSource.getLastIndex());
                                    this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(), MenuOperation.COMMIT_NODE);
                                }
                            });
                        }, Row);
                        {
                            this.observeComponentCreation2((l20, m20) => {
                                if (m20) {
                                    let n20 = new TreeViewInner(this, {
                                        item: e20,
                                        listNodeDataSource: this.listNodeDataSource,
                                        index: this.listNodeDataSource.findIndex(e20.getNodeCurrentNodeId()),
                                        listTreeViewMenu: this.listTreeViewMenu,
                                    }, undefined, l20, () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 1040, col: 13 });
                                    ViewPU.create(n20);
                                    let o20 = () => {
                                        return {
                                            item: e20,
                                            listNodeDataSource: this.listNodeDataSource,
                                            index: this.listNodeDataSource.findIndex(e20.getNodeCurrentNodeId()),
                                            listTreeViewMenu: this.listTreeViewMenu
                                        };
                                    };
                                    n20.paramsGenerator_ = o20;
                                }
                                else {
                                    this.updateStateVarsOfChildByElmtId(l20, {
                                        item: e20
                                    });
                                }
                            }, { name: 'TreeViewInner' });
                        }
                        Row.pop();
                        ListItem.pop();
                    };
                    g20();
                }
            };
            const z19 = (c20) => JSON.stringify(c20);
            LazyForEach.create('1', this, this.listNodeDataSource, y19, z19);
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
        let w19 = this.listNodeDataSource.getClickNodeId();
        return this.listNodeDataSource.getClickNodeChildrenInfo(w19);
    }
    getChildrenId() {
        let v19 = this.listNodeDataSource.getClickNodeId();
        return this.listNodeDataSource.getClickChildId(v19);
    }
    removeNode() {
        let s19 = this.listNodeDataSource.getClickNodeId();
        if (s19 < 0) {
            return;
        }
        let t19 = this.listNodeDataSource.findParentNodeId(s19);
        let u19 = this.listNodeDataSource.removeNode(s19, t19);
        this.listNodeDataSource.refreshData(MenuOperation.REMOVE_NODE, t19, u19);
        this.nodeIdList.splice(this.nodeIdList.indexOf(s19), 1);
        this.listNodeDataSource.lastIndex = -1;
    }
    modifyNode() {
        let r19 = this.listNodeDataSource.getClickNodeId();
        this.listNodeDataSource.setItemVisibilityOnEdit(r19, MenuOperation.MODIFY_NODE);
    }
    add(m19) {
        let n19 = this.listNodeDataSource.getClickNodeId();
        if (n19 === this.listNodeDataSource.ROOT_NODE_ID || !this.listNodeDataSource.getIsFolder(n19)) {
            return;
        }
        let o19 = this.listNodeDataSource.getNewNodeParam(n19);
        this.nodeIdList.push(this.nodeIdList[this.nodeIdList.length - 1] + 1);
        let p19 = this.nodeIdList[this.nodeIdList.length - 1];
        this.listNodeDataSource.addNode(n19, p19, {
            isFolder: o19.isFolder,
            icon: o19.icon,
            selectedIcon: o19.selectedIcon,
            editIcon: o19.editIcon,
            primaryTitle: '新建文件夹',
            container: o19.container,
            secondaryTitle: o19.secondaryTitle,
        }, m19);
        this.listNodeDataSource.refreshData(MenuOperation.ADD_NODE, n19, [p19]);
        this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false, this.listNodeDataSource.getLastIndex());
        this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(), MenuOperation.COMMIT_NODE);
        this.listNodeDataSource.listNode[this.listNodeDataSource.getLastIndex()]
            .setFontColor(this.treeViewTheme.primaryTitleFontColor);
        let q19 = this.listNodeDataSource.findIndex(p19);
        this.listNodeDataSource.setClickIndex(q19);
        this.listNodeDataSource.handleEvent(Event.TOUCH_UP, q19);
    }
    addNode(k19) {
        if (k19 === undefined) {
            this.add(this.initBuild);
            return this;
        }
        else {
            if (k19.primaryTitle !== undefined &&
                !this.listNodeDataSource.checkMainTitleIsValid(k19.primaryTitle.toString())) {
                throw new Error('ListTreeNode[addNode]: ' +
                    "The directory name cannot contain the following characters\ /: *? '< > | or exceeds the maximum length.");
                return this;
            }
            if (k19.primaryTitle === null && k19.icon === null) {
                throw new Error('ListTreeNode[addNode]: ' +
                    'The icon and directory name cannot be empty at the same time.');
                return this;
            }
            if (k19.currentNodeId === this.ROOT_NODE_ID || k19.currentNodeId === null) {
                throw new Error('ListTreeNode[addNode]: currentNodeId can not be -1 or null.');
                return this;
            }
            if (k19.currentNodeId !== undefined) {
                this.nodeIdList.push(k19.currentNodeId);
            }
            if (k19.parentNodeId !== undefined) {
                if (k19.currentNodeId !== undefined) {
                    this.listNodeDataSource.addNode(k19.parentNodeId, k19.currentNodeId, k19, this.initBuild);
                }
            }
            if (!this.initBuild && k19.parentNodeId !== undefined) {
                let l19 = this.nodeIdList[this.nodeIdList.length - 1];
                this.listNodeDataSource.refreshData(MenuOperation.ADD_NODE, k19.parentNodeId, [l19]);
            }
            return this;
        }
    }
    refreshNode(h19, i19, j19) {
        this.listNodeDataSource.setNodeSubtitlePara(h19, i19, j19);
    }
    buildDone() {
        this.listNodeDataSource.initSection();
        this.listNodeDataSource.delayInit();
        this.listNodeDataSource.updateAllChildNum();
        let f19 = setTimeout(() => {
            concurrentSortNodeIdList(this.nodeIdList);
            clearTimeout(f19);
        }, DELAY_TIME);
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
function concurrentUpdateParentChildNum(e18, f18, g18, h18) {
    h18.forEach((j18) => {
        let k18 = j18;
        while (k18 >= 0) {
            if (g18.has(k18)) {
                let l18 = g18.get(k18);
                l18.getChildNodeInfo().allChildNum =
                    e18 ? l18.getChildNodeInfo().allChildNum + f18 : l18.getChildNodeInfo().allChildNum - f18;
                k18 = l18.parentNodeId;
            }
            else {
                throw new Error('concurrentUpdateParentChildNum: Parent node not found.');
            }
        }
    });
}
function concurrentSortNodeIdList(a18) {
    a18.sort((c18, d18) => c18 - d18);
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
            id: -1,
            type: 10001,
            params: ['sys.color.ohos_id_color_emphasize'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
          xOffset: X_OFF_SET,
          yTopOffset: Y_OFF_SET,
          yBottomOffset: Y_BOTTOM_OFF_SET,
          yBasePlateOffset: Y_BASE_PLATE_OFF_SET,
        };
        this.DRAG_POPUP = {
          floorConstraintSize: {
            minWidth: FLOOR_MIN_WIDTH,
            maxWidth: FLOOR_MAX_WIDTH,
          },
          textConstraintSize: {
            minWidth1: TEXT_MIN_WIDTH,
            maxWidth1: TEXT_MAX_WIDTH,
            minWidth2: MIN_WIDTH,
            maxWidth2: MAX_WIDTH,
          },
          padding: {
            left: {
              id: -1,
              type: 10002,
              params: ['sys.float.padding_level4'],
              bundleName: '__harDefaultBundleName__',
              moduleName: '__harDefaultModuleName__',
            },
            right: {
              id: -1,
              type: 10002,
              params: ['sys.float.padding_level4'],
              bundleName: '__harDefaultBundleName__',
              moduleName: '__harDefaultModuleName__',
            },
          },
          backgroundColor: COLOR_IMAGE_EDIT,
          height: GRAG_POP_UP_HEIGHT,
          shadow: {
            radius: {
              id: -1,
              type: 10002,
              params: ['sys.float.ohos_id_corner_radius_default_m'],
              bundleName: '__harDefaultBundleName__',
              moduleName: '__harDefaultModuleName__',
            },
            color: SHADOW_COLOR,
            offsetX: 0,
            offsetY: SHADOW_OFFSETY,
          },
          borderRadius: {
            id: -1,
            type: 10002,
            params: ['sys.float.ohos_id_corner_radius_clicked'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
          fontColor: this.treeViewTheme.primaryTitleFontColor,
          fontSize: {
            id: -1,
            type: 10002,
            params: ['sys.float.ohos_id_text_size_body1'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
          fontWeight: FontWeight.Regular,
          imageOpacity: {
            id: -1,
            type: 10002,
            params: ['sys.float.ohos_id_alpha_content_fourth'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
        };
        this.subTitle = {
          normalFontColor: this.treeViewTheme.secondaryTitleFontColor,
          highLightFontColor: {
            id: -1,
            type: 10001,
            params: ['sys.color.ohos_id_color_primary_contrary'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
          fontSize: {
            id: -1,
            type: 10002,
            params: ['sys.float.ohos_id_text_size_body2'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
          fontWeight: FontWeight.Regular,
          margin: {
            left: {
              id: -1,
              type: 10002,
              params: ['sys.float.padding_level2'],
              bundleName: '__harDefaultBundleName__',
              moduleName: '__harDefaultModuleName__',
            },
            right: {
              id: -1,
              type: 10002,
              params: ['sys.float.padding_level12'],
              bundleName: '__harDefaultBundleName__',
              moduleName: '__harDefaultModuleName__',
            },
          },
        };
        this._root.nodeLevel = -1;
        this.nodeIdNodeItemMap.set(-1, this._root);
        this.nodeIdNodeParamMap.set(-1, emptyNodeInfo);
    }
    changeNodeColor(y17, z17) {
        this.listNode[y17].setNodeColor(z17);
        this.listNode[y17].setNodeBorder(false);
    }
    getNodeColor(x17) {
        return this.listNode[x17].getNodeColor();
    }
    handleFocusEffect(v17, w17) {
        if (this.listNode[v17].getNodeIsShow()) {
            this.listNode[v17].setNodeBorder(w17);
        }
    }
    setImageSource(s17, t17) {
        let u17 = this.listNode[s17];
        u17.setIsSelected(t17 === InteractionStatus.SELECTED ||
            t17 === InteractionStatus.EDIT || t17 === InteractionStatus.FINISH_EDIT);
        if (u17.getNodeItem().mainTitleNode !== null && t17 !== InteractionStatus.DRAG_INSERT &&
            t17 !== InteractionStatus.FINISH_DRAG_INSERT) {
            u17.getNodeItem().mainTitleNode?.setMainTitleSelected(t17 === InteractionStatus.SELECTED ||
                t17 === InteractionStatus.FINISH_EDIT);
        }
        if (u17.getNodeItem().imageNode !== null) {
            u17.getNodeItem().imageNode?.setImageSource(t17);
        }
    }
    setImageCollapseSource(p17, q17) {
        let r17 = this.listNode[p17];
        if (r17.getNodeItem().imageCollapse !== undefined) {
            r17.getNodeItem().imageCollapse = CollapseImageNodeFlyweightFactory.getCollapseImageNode(q17,
                this.expandAndCollapseInfo.get(r17.getNodeCurrentNodeId()), r17.getNodeItem().imageCollapse.type);
        }
    }
    clearLastIndexStatus() {
        if (this.lastIndex === -1 || this.lastIndex >= this.listNode.length) {
            return;
        }
        this.setImageSource(this.lastIndex, InteractionStatus.NORMAL);
        this.changeNodeColor(this.lastIndex, this.listNode[this.lastIndex].getNodeStatus().normal);
        this.handleFocusEffect(this.lastIndex, false);
        this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.listNode[this.lastIndex].getNodeCurrentNodeId()));
    }
    loadedListNodeFunction() {
        let n17 = 0;
        this.loadedNodeIdAndIndexMap.clear();
        this.nodeIdAndNodeIndexMap.clear();
        this.loadedListNode.splice(0, this.loadedListNode.length);
        for (let o17 = 0; o17 < this.listNode.length; o17++) {
            this.nodeIdAndNodeIndexMap.set(this.listNode[o17].getNodeCurrentNodeId(), o17);
            if (this.listNode[o17].getNodeIsShow()) {
                this.loadedNodeIdAndIndexMap.set(this.listNode[o17].getNodeCurrentNodeId(), n17++);
                this.loadedListNode.push(this.listNode[o17]);
            }
        }
    }
    changeNodeStatus(k17) {
        if (k17 >= this.listNode.length) {
            throw new Error('changeNodeStatus clickIndex error.');
        }
        let l17 = k17;
        let m17 = this.listNode[k17].getNodeCurrentNodeId();
        if (this.expandAndCollapseInfo.get(m17) === NodeStatus.EXPAND) {
            this.expandAndCollapseInfo.set(m17, NodeStatus.COLLAPSE);
            this.listNode[l17].getNodeItem().imageCollapse = this.listNode[l17].getNodeItem().imageCollapse ?
            CollapseImageNodeFlyweightFactory.changeImageCollapseSource(NodeStatus.COLLAPSE,
                this.listNode[l17].getNodeItem().imageCollapse.isCollapse) : undefined;
        } else if (this.expandAndCollapseInfo.get(m17) === NodeStatus.COLLAPSE) {
            this.expandAndCollapseInfo.set(m17, NodeStatus.EXPAND);
            this.listNode[l17].getNodeItem().imageCollapse = this.listNode[l17].getNodeItem().imageCollapse ?
            CollapseImageNodeFlyweightFactory.changeImageCollapseSource(NodeStatus.EXPAND,
                this.listNode[l17].getNodeItem().imageCollapse.isCollapse) : undefined;
        }
    }
    handleExpandAndCollapse(a17, b17) {
        if (a17 >= this.listNode.length) {
            throw new Error('handleExpandAndCollapse clickIndex error.');
        }
        let c17 = a17;
        let d17 = this.listNode[c17].getNodeCurrentNodeId();
        if (!this.expandAndCollapseInfo.has(d17)) {
            return;
        }
        let e17 = this.expandAndCollapseInfo.get(d17);
        if (this.listNode[c17].getChildNodeInfo().isHasChildNode && e17 === NodeStatus.COLLAPSE) {
            for (let j17 = 0; j17 < this.listNode[c17].getChildNodeInfo().allChildNum; j17++) {
                this.listNode[c17 + 1 + j17].setNodeIsShow(false);
                this.listNode[c17 + 1 + j17].setListItemHeight(LIST_ITEM_HEIGHT_NONE);
            }
            this.loadedListNodeFunction();
            this.notifyDataReload();
            return;
        }
        let f17 = new Array(this.listNode[c17].getChildNodeInfo().childNum);
        f17[0] = c17 + 1;
        let g17 = 1;
        while (g17 < this.listNode[c17].getChildNodeInfo().childNum) {
            f17[g17] = f17[g17 - 1] + this.listNode[f17[g17 - 1]].getChildNodeInfo().allChildNum + 1;
            g17++;
        }
        if (e17 === NodeStatus.EXPAND) {
            for (let h17 = 0; h17 < f17.length; h17++) {
                this.listNode[f17[h17]].setNodeIsShow(true);
                this.listNode[f17[h17]].setListItemHeight(LIST_ITEM_HEIGHT);
                let i17 = this.listNode[f17[h17]].getNodeCurrentNodeId();
                if (this.expandAndCollapseInfo.get(i17) === NodeStatus.EXPAND) {
                    this.handleExpandAndCollapse(f17[h17], false);
                }
            }
        }
        f17 = null;
        if (b17) {
            this.loadedListNodeFunction();
            this.notifyDataReload();
        }
    }
    updateAllChildNum() {
        let y16 = setTimeout(() => {
            concurrentUpdateParentChildNum(true, 1, this.nodeIdNodeItemMap, this.updateNodeIdList);
            clearTimeout(y16);
        }, DELAY_TIME);
    }
    initHandler(q16, r16, s16) {
        let t16 = 0;
        let u16 = 0;
        q16.splice(0, q16.length);
        this.loadedNodeIdAndIndexMap.clear();
        this.loadedListNode.splice(0, this.loadedListNode.length);
        this.nodeIdAndNodeIndexMap.clear();
        this.nodeIdAndSubtitleMap.clear();
        this.traverseSectionNodeDF((w16) => {
            if (w16.getCurrentNodeId() >= 0 && this.nodeIdNodeParamMap.has(w16.getCurrentNodeId())) {
                let x16 = new NodeInfo(w16, this.nodeIdNodeParamMap.get(w16.getCurrentNodeId()));
                x16.addImageCollapse(w16.getChildNodeInfo().isHasChildNode);
                q16.push(x16);
                this.nodeIdAndNodeIndexMap.set(x16.getNodeCurrentNodeId(), u16++);
                if (x16.getChildNodeInfo().isHasChildNode) {
                    this.expandAndCollapseInfo.set(x16.getNodeCurrentNodeId(), NodeStatus.COLLAPSE);
                }
                if (x16.getNodeIsShow()) {
                    this.loadedNodeIdAndIndexMap.set(x16.getNodeCurrentNodeId(), t16++);
                    this.loadedListNode.push(x16);
                }
                if (x16.getIsFolder()) {
                    if (x16.getNodeInfoData().secondaryTitle !== undefined) {
                        this.nodeIdAndSubtitleMap.set(x16.getNodeCurrentNodeId(), x16.getNodeInfoData().secondaryTitle);
                    }
                    else {
                        this.nodeIdAndSubtitleMap.set(x16.getNodeCurrentNodeId(), '');
                    }
                }
            }
            return false;
        }, this._root, r16, s16);
    }
    delayInit() {
        let n16 = setTimeout(() => {
            let p16 = [];
            this.initHandler(p16, 0);
            this.listNode.splice(0, this.listNode.length);
            this.listNode.push(...p16);
            clearTimeout(n16);
        }, DELAY_TIME);
    }
    initSection() {
        this.initHandler(this.listNode, 0, 1);
    }
    refreshRemoveNodeData(c16, d16) {
        let e16 = [];
        if (c16.length === 0) {
            return;
        }
        let f16 = undefined;
        for (let k16 = 0; k16 < c16.length; k16++) {
            if (this.loadedNodeIdAndIndexMap.has(c16[k16])) {
                let m16 = this.loadedNodeIdAndIndexMap.get(c16[k16]);
                e16.push(m16);
            }
            if (f16 === undefined && this.nodeIdAndNodeIndexMap.has(c16[k16])) {
                f16 = this.nodeIdAndNodeIndexMap.get(c16[k16]);
            }
            if (f16 !== undefined) {
                let l16 = this.listNode.splice(f16, 1);
                l16 = null;
            }
            if (this.expandAndCollapseInfo.has(c16[k16])) {
                this.expandAndCollapseInfo.delete(c16[k16]);
            }
        }
        e16.forEach((j16) => {
            this.notifyDataDelete(j16);
            this.notifyDataChange(j16);
        });
        if (d16.getNodeItem().imageCollapse === null) {
            if (this.nodeIdAndNodeIndexMap.has(d16.getNodeCurrentNodeId())) {
                let i16 = this.nodeIdAndNodeIndexMap.get(d16.getNodeCurrentNodeId());
                this.listNode[i16]?.handleImageCollapseAfterAddNode(false);
            }
            this.expandAndCollapseInfo.delete(d16.getNodeCurrentNodeId());
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(d16.getNodeCurrentNodeId()));
        }
        let g16 = {
            currentNodeId: d16.getNodeCurrentNodeId(),
            parentNodeId: d16.getNodeParentNodeId(),
        };
        this.loadedListNodeFunction();
        this.appEventBus.emit(TreeListenType.NODE_DELETE, g16);
    }
    refreshAddNodeData(x15) {
        let y15 = new NodeInfo(new NodeItem(emptyNodeInfo), emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(x15[0])) {
            let b16 = this.nodeIdNodeItemMap.get(x15[0]);
            y15 = new NodeInfo(b16, this.nodeIdNodeParamMap.get(x15[0]));
            y15.addImageCollapse(b16.getChildNodeInfo().isHasChildNode);
        }
        y15.setIsModify(true);
        let z15 = 0;
        for (let a16 = 0; a16 < this.listNode.length; a16++) {
            if (this.listNode[a16].getNodeCurrentNodeId() === y15.getNodeParentNodeId()) {
                z15 = a16;
                if (this.listNode[a16].getNodeItem().imageCollapse === null) {
                    this.listNode[a16].handleImageCollapseAfterAddNode(true);
                    this.notifyDataChange(z15);
                }
                else if (this.expandAndCollapseInfo.get(this.listNode[a16].getNodeCurrentNodeId()) === NodeStatus.COLLAPSE) {
                    this.changeNodeStatus(z15);
                }
                this.listNode.splice(a16 + 1, 0, y15);
                this.listNode[a16 + 1].setTitleAndInputTextStatus(true);
                this.listNode[a16 + 1].setNodeIsShow(true);
                this.listNode[a16 + 1].setListItemHeight(LIST_ITEM_HEIGHT);
                this.nodeIdAndNodeIndexMap.set(x15[0], a16 + 1);
                this.setImageSource(a16 + 1, InteractionStatus.EDIT);
                this.currentOperation = MenuOperation.ADD_NODE;
                this.notifyDataAdd(a16 + 1);
                this.notificationNodeInfo(a16 + 1, this.currentOperation);
                break;
            }
        }
        this.modifyNodeIndex = z15 + 1;
        this.setClickIndex(z15);
        this.lastIndex = z15;
        this.expandAndCollapseInfo.set(y15.getNodeParentNodeId(), NodeStatus.EXPAND);
        this.handleExpandAndCollapse(z15, true);
    }
    refreshData(s15, t15, u15) {
        let v15 = new NodeInfo(new NodeItem(emptyNodeInfo), emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(t15)) {
            let w15 = this.nodeIdNodeItemMap.get(t15);
            v15 = new NodeInfo(w15, this.nodeIdNodeParamMap.get(t15));
            v15.addImageCollapse(w15.getChildNodeInfo().isHasChildNode);
        }
        if (s15 === MenuOperation.REMOVE_NODE) {
            this.nodeIdAndSubtitleMap.set(t15, this.selectedParentNodeSubtitle);
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(t15));
            this.refreshRemoveNodeData(u15, v15);
        }
        if (s15 === MenuOperation.ADD_NODE) {
            this.addFocusNodeId = u15[0];
            this.nodeIdAndSubtitleMap.set(this.getClickNodeId(), this.selectedParentNodeSubtitle);
            this.nodeIdAndSubtitleMap.set(u15[0], this.insertNodeSubtitle);
            this.refreshAddNodeData(u15);
        }
    }
    setClickIndex(r15) {
        this.thisIndex = r15;
    }
    getClickNodeId() {
        if (this.thisIndex < 0 || this.thisIndex >= this.listNode.length) {
            return -1;
        }
        return this.listNode[this.thisIndex].getNodeCurrentNodeId();
    }
    expandAndCollapseNode(q15) {
        this.changeNodeStatus(q15);
        this.handleExpandAndCollapse(q15, true);
    }
    getIsTouchDown() {
        return this.isTouchDown;
    }
    getLastIndex() {
        return this.lastIndex;
    }
    findIndex(o15) {
        let p15 = -1;
        if (this.nodeIdAndNodeIndexMap.has(o15)) {
            p15 = this.nodeIdAndNodeIndexMap.get(o15);
        }
        return p15;
    }
    handleEventDrag(n15) {
        this.setImageSource(n15, InteractionStatus.NORMAL);
        this.changeNodeColor(n15, this.listNode[n15].getNodeStatus().normal);
        this.handleFocusEffect(n15, false);
        this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.listNode[n15].getNodeCurrentNodeId()));
    }
    handleEvent(i15, j15) {
        if (this.isDrag) {
            return;
        }
        if (i15 === Event.TOUCH_DOWN || i15 === Event.TOUCH_UP || i15 === Event.MOUSE_BUTTON_RIGHT) {
            if (j15 !== this.lastIndex) {
                this.clearLastIndexStatus();
            }
        }
        this.eventHandler(j15, i15);
    }
    eventHandler(j12, y19) {
        let z19 = this.loadedNodeIdAndIndexMap.get(this.listNode[j12].getNodeCurrentNodeId());
        switch (y19) {
            case Event.TOUCH_DOWN:
                this.isTouchDown = true;
                this.changeNodeColor(j12, this.listNode[j12].getNodeStatus().press);
                this.notifyDataChange(z19);
                break;
            case Event.TOUCH_UP: {
                this.touchUpHandler(j12, z19);
                break;
            }
            case Event.HOVER:
                if (this.getNodeColor(j12) !== this.listNode[j12].getNodeStatus().selected) {
                    this.changeNodeColor(j12, this.listNode[j12].getNodeStatus().hover);
                    this.notifyDataChange(z19);
                }
                break;
            case Event.HOVER_OVER:
                if (this.getNodeColor(j12) !== this.listNode[j12].getNodeStatus().selected) {
                    this.changeNodeColor(j12, this.listNode[j12].getNodeStatus().normal);
                    this.notifyDataChange(z19);
                }
                break;
            case Event.FOCUS:
                this.handleFocusEffect(j12, true);
                this.notifyDataChange(z19);
                break;
            case Event.BLUR:
                this.handleFocusEffect(j12, false);
                this.notifyDataChange(z19);
                break;
            case Event.MOUSE_BUTTON_RIGHT:
                this.lastIndex = j12;
                this.finishEditing();
                break;
            case Event.DRAG:
                this.isTouchDown = false;
                let a20 = this.listNode[j12];
                this.setImageSource(j12, InteractionStatus.SELECTED);
                this.lastIndex = j12;
                this.changeNodeColor(j12, a20.getNodeStatus().selected);
                this.notifyDataChange(z19);
                break;
            default:
                break;
        }
    }
    touchUpHandler(i4, f5) {
        if (this.isInnerDrag) {
            this.isInnerDrag = false;
        }
        this.isTouchDown = false;
        let e8 = this.listNode[i4];
        this.setImageSource(i4, InteractionStatus.SELECTED);
        e8.setFontColor(this.treeViewTheme.primaryTitleFontColor);
        this.lastIndex = i4;
        this.changeNodeColor(i4, e8.getNodeStatus().selected);
        this.notifyDataChange(f5);
    }
    notificationNodeInfo(z14, a15) {
        if (a15 === MenuOperation.MODIFY_NODE) {
            let g15 = this.listNode[this.modifyNodeIndex];
            let h15 = {
                currentNodeId: g15.getNodeCurrentNodeId(),
                parentNodeId: g15.getNodeParentNodeId(),
            };
            this.appEventBus.emit(TreeListenType.NODE_MODIFY, h15);
        }
        else if (a15 === MenuOperation.ADD_NODE) {
            let b15 = this.listNode[z14];
            if (b15 === undefined) {
                return;
            }
            let c15 = (b15.getNodeItem().imageNode !== undefined) ?
                b15.getNodeItem().imageNode?.source : undefined;
            let d15 = (b15.getNodeItem().imageNode !== undefined) ?
                b15.getNodeItem().imageNode?.selectedSource : undefined;
            let e15 = (b15.getNodeItem().imageNode !== undefined) ?
                b15.getNodeItem().imageNode?.editSource : undefined;
            let f15 = {
                currentNodeId: b15.getNodeCurrentNodeId(),
                parentNodeId: b15.getNodeParentNodeId(),
            };
            this.appEventBus.emit(TreeListenType.NODE_ADD, f15);
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
    setItemVisibilityOnEdit(t14, u14) {
        let v14 = -1;
        if (t14 === -1) {
            return;
        }
        if (u14 === MenuOperation.MODIFY_NODE) {
            for (let y14 = 0; y14 < this.listNode.length; y14++) {
                if (this.listNode[y14].getNodeCurrentNodeId() === t14) {
                    v14 = y14;
                    break;
                }
            }
            let x14 = this.listNode[v14];
            if (x14 === undefined) {
                return;
            }
            x14.setIsModify(true);
            if (x14.getNodeItem().mainTitleNode === null) {
                return;
            }
            this.currentOperation = MenuOperation.MODIFY_NODE;
            x14.setTitleAndInputTextStatus(true);
            this.setImageSource(v14, InteractionStatus.EDIT);
            this.setImageCollapseSource(v14, InteractionStatus.EDIT);
            this.modifyNodeIndex = v14;
            if (x14.getNodeItem().inputText) {
                if (x14.getNodeItem().imageCollapse !== null) {
                  x14.getNodeItem().inputText.rightMargin = {
                    id: -1,
                    type: 10002,
                    params: ['sys.float.ohos_id_text_paragraph_margin_xs'],
                    bundleName: '__harDefaultBundleName__',
                    moduleName: '__harDefaultModuleName__',
                  };
                } else {
                  x14.getNodeItem().inputText.rightMargin = {
                    id: -1,
                    type: 10002,
                    params: ['sys.float.ohos_id_elements_margin_horizontal_m'],
                    bundleName: '__harDefaultBundleName__',
                    moduleName: '__harDefaultModuleName__',
                  };
                }
            }
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(t14));
        }
        v14 = t14;
        if (u14 === MenuOperation.COMMIT_NODE) {
            let w14 = this.listNode[v14];
            if (w14 === undefined) {
                return;
            }
            w14.setTitleAndInputTextStatus(false);
            w14.setIsModify(false);
            this.setImageSource(v14, InteractionStatus.FINISH_EDIT);
            this.setImageCollapseSource(v14, InteractionStatus.FINISH_EDIT);
            this.notificationNodeInfo(this.modifyNodeIndex, this.currentOperation);
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(w14.getNodeCurrentNodeId()));
        }
    }
    setPopUpInfo(n14, o14, p14, q14) {
        let r14 = this.listNode[q14];
        if (r14 === undefined) {
            return;
        }
        r14.setPopUpIsShow(p14);
        let s14 = this.loadedNodeIdAndIndexMap.get(r14.getNodeCurrentNodeId());
        if (!p14) {
            this.notifyDataChange(s14);
            return;
        }
        if (n14 === PopUpType.HINTS) {
            if (r14.getNodeItem().mainTitleNode !== null) {
                r14.setPopUpText(r14.getNodeItem().mainTitleNode?.title);
            }
            else {
                r14.setPopUpText('');
                r14.setPopUpIsShow(false);
            }
            r14.setPopUpEnableArrow(false);
            r14.setPopUpColor({
              id: -1,
              type: 10001,
              params: ['sys.color.ohos_id_color_background'],
              bundleName: '__harDefaultBundleName__',
              moduleName: '__harDefaultModuleName__',
            });
            r14.setPopUpTextColor({
              id: -1,
              type: 10001,
              params: ['sys.color.ohos_id_color_text_secondary'],
              bundleName: '__harDefaultBundleName__',
              moduleName: '__harDefaultModuleName__',
            });
        }
        else if (n14 === PopUpType.WARNINGS) {
            if (r14.getNodeItem().inputText !== null) {
                if (o14 === InputError.INVALID_ERROR) {
                    r14.setPopUpText('invalid error');
                }
                else if (o14 === InputError.LENGTH_ERROR) {
                    r14.setPopUpText('length error');
                }
                r14.setPopUpEnableArrow(true);
                r14.setPopUpColor({
                  id: -1,
                  type: 10001,
                  params: ['sys.color.ohos_id_color_help_tip_bg'],
                  bundleName: '__harDefaultBundleName__',
                  moduleName: '__harDefaultModuleName__',
                });
                r14.setPopUpTextColor({
                  id: -1,
                  type: 10001,
                  params: ['sys.color.ohos_id_color_text_hint_contrary'],
                  bundleName: '__harDefaultBundleName__',
                  moduleName: '__harDefaultModuleName__',
                });
            }
        }
        this.notifyDataChange(s14);
    }
    setShowPopUpTimeout(k14, l14) {
        if (this.listNode[l14].getNodeItem().mainTitleNode !== null) {
            this.listNode[l14].getNodeItem().mainTitleNode.popUpTimeout = k14;
        }
        let m14 = this.loadedNodeIdAndIndexMap.get(this.listNode[l14].getNodeCurrentNodeId());
        this.notifyDataChange(m14);
    }
    setMainTitleNameOnEdit(i14, j14) {
        this.modifyNodeIndex = i14;
        if (this.listNode[i14].getNodeItem().mainTitleNode !== null) {
            this.listNode[i14].getNodeItem().mainTitleNode.title = j14;
        }
    }
    totalCount() {
        return this.loadedNodeIdAndIndexMap.size;
    }
    getData(h14) {
        if (h14 < 0 || h14 >= this.loadedListNode.length) {
            return undefined;
        }
        return this.loadedListNode[h14];
    }
    addData(f14, g14) {
        this.listNode.splice(f14, 0, g14);
        this.nodeIdAndNodeIndexMap.set(g14.getNodeCurrentNodeId(), f14);
        this.loadedListNodeFunction();
        this.notifyDataAdd(f14);
    }
    pushData(e14) {
        this.listNode.push(e14);
        this.nodeIdAndNodeIndexMap.set(e14.getNodeCurrentNodeId(), this.listNode.length);
        this.loadedListNodeFunction();
        this.notifyDataAdd(this.listNode.length - 1);
    }
    setIsInnerDrag(d14) {
        this.isInnerDrag = d14;
    }
    getIsInnerDrag() {
        return this.isInnerDrag;
    }
    setIsDrag(c14) {
        this.isDrag = c14;
    }
    getIsDrag() {
        return this.isDrag;
    }
    setCurrentNodeInfo(b14) {
        if (b14 === undefined) {
            return;
        }
        this.currentNodeInfo = b14;
    }
    getCurrentNodeInfo() {
        return this.currentNodeInfo;
    }
    setDraggingParentNodeId(a14) {
        if (a14 === undefined) {
            return;
        }
        this.draggingParentNodeId = a14;
    }
    getDraggingParentNodeId() {
        return this.draggingParentNodeId;
    }
    getDraggingCurrentNodeId() {
        return this.draggingCurrentNodeId;
    }
    setDraggingCurrentNodeId(z13) {
        if (z13 === undefined) {
            return;
        }
        this.draggingCurrentNodeId = z13;
    }
    setListItemOpacity(y13) {
        this.listItemOpacity = y13;
    }
    getListItemOpacity(x13) {
        return x13.getNodeCurrentNodeId() === this.getDraggingCurrentNodeId() ? this.listItemOpacity : 1;
    }
    getDragPopupPara() {
        return this.DRAG_POPUP;
    }
    setLastPassIndex(w13) {
        this.lastPassIndex = w13;
    }
    getLastPassIndex() {
        return this.lastPassIndex;
    }
    getIsParentOfInsertNode(t13) {
        if (this.currentNodeInfo === null || t13 === undefined) {
            return false;
        }
        let u13 = this.currentNodeInfo.getNodeInfoNode();
        let v13 = u13.currentNodeId;
        let k15 = this.nodeIdNodeItemMap.get(t13)?.parentNodeId;
        while (k15 !== undefined && k15 !== -1) {
            if (v13 === k15) {
                return true;
            }
            else {
                k15 = this.nodeIdNodeItemMap.get(k15)?.parentNodeId;
            }
        }
        return false;
    }
    setPassIndex(s13) {
        this.thisPassIndex = s13;
    }
    getPassIndex() {
        return this.thisPassIndex;
    }
    clearTimeOutAboutDelayHighLightAndExpand(n13) {
        if (this.lastPassId !== this.INITIAL_INVALID_VALUE && this.loadedNodeIdAndIndexMap.has(this.lastPassId)) {
            let p13 = this.loadedNodeIdAndIndexMap.get(this.lastPassId);
            this.listNode.forEach((r13) => {
                if (r13.getNodeCurrentNodeId() === this.lastPassId) {
                    r13.setCanShowFlagLine(false);
                    return;
                }
            });
            this.notifyDataChange(p13);
        }
        if ((this.lastTimeoutHighLightId !== this.INITIAL_INVALID_VALUE &&
            this.clearTimeoutHighLightId !== this.lastTimeoutHighLightId)) {
            clearTimeout(this.lastTimeoutHighLightId);
            if (this.lastDelayHighLightIndex !== this.INITIAL_INVALID_VALUE) {
                this.clearHighLight(this.lastDelayHighLightIndex);
                let o13 = this.loadedNodeIdAndIndexMap
                    .get(this.listNode[this.lastDelayHighLightIndex].getNodeCurrentNodeId());
                this.notifyDataChange(o13);
            }
            this.clearTimeoutHighLightId = this.lastTimeoutHighLightId;
        }
        this.lastTimeoutHighLightId = this.timeoutHighLightId;
        this.lastDelayHighLightIndex = n13;
        if ((this.lastTimeoutExpandId !== this.INITIAL_INVALID_VALUE &&
            this.clearTimeoutExpandId !== this.lastTimeoutExpandId)) {
            clearTimeout(this.lastTimeoutExpandId);
            this.clearTimeoutExpandId = this.lastTimeoutExpandId;
        }
        this.lastTimeoutExpandId = this.timeoutExpandId;
        this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE;
    }
    clearHighLight(m13) {
        this.changeNodeColor(m13, this.listNode[m13].getNodeStatus().normal);
        this.changeNodeHighLightColor(m13, false);
        this.setImageSource(m13, InteractionStatus.FINISH_DRAG_INSERT);
        this.setImageCollapseSource(m13, InteractionStatus.FINISH_DRAG_INSERT);
        this.listNode[m13].setIsHighLight(false);
    }
    changeNodeHighLightColor(k13, l13) {
        if (this.listNode[k13].getNodeItem().mainTitleNode && this.listNode[k13].getIsShowTitle()) {
            this.listNode[k13].getNodeItem().mainTitleNode?.setMainTitleHighLight(l13);
        }
    }
    setVisibility(b13, c13, d13) {
        let e13 = (this.thisPassIndex !== c13 || this.flag !== b13) ? true : false;
        this.thisPassIndex = c13;
        if ((e13 || d13) && this.isInnerDrag) {
            this.flag = b13;
            let f13 = this.getData(c13)?.getNodeCurrentNodeId();
            let g13 = this.getData(c13)?.getNodeLevel();
            if (f13 !== undefined) {
                g13 = (this.expandAndCollapseInfo.get(f13) === NodeStatus.EXPAND &&
                    this.flag === Flag.DOWN_FLAG) ? (g13 ? g13 + 1 : undefined) : g13;
                if (this.lastPassId !== this.INITIAL_INVALID_VALUE && this.loadedNodeIdAndIndexMap.has(this.lastPassId)) {
                    let h13 = this.loadedNodeIdAndIndexMap.get(this.lastPassId);
                    this.listNode.forEach((j13) => {
                        if (j13.getNodeCurrentNodeId() === this.lastPassId) {
                            j13.setCanShowFlagLine(false);
                        }
                    });
                    this.notifyDataChange(h13);
                }
                if (this.flag === Flag.DOWN_FLAG && c13 < this.totalCount() - 1) {
                    this.getData(c13)?.setCanShowFlagLine(false);
                    this.getData(c13 + 1)?.setCanShowFlagLine(true);
                    this.getData(c13)?.setCanShowBottomFlagLine(false);
                    this.getData(c13 + 1)?.setFlagLineLeftMargin(g13);
                    this.notifyDataChange(c13);
                    this.notifyDataChange(c13 + 1);
                    this.lastPassId = this.getData(c13 + 1)?.getNodeCurrentNodeId();
                }
                else if (this.flag === Flag.UP_FLAG && c13 < this.totalCount() - 1) {
                    this.getData(c13)?.setCanShowFlagLine(true);
                    this.getData(c13 + 1)?.setCanShowFlagLine(false);
                    this.getData(c13)?.setCanShowBottomFlagLine(false);
                    this.getData(c13)?.setFlagLineLeftMargin(g13);
                    this.notifyDataChange(c13);
                    this.notifyDataChange(c13 + 1);
                    this.lastPassId = this.getData(c13)?.getNodeCurrentNodeId();
                }
                else if (c13 >= this.totalCount() - 1) {
                    if (this.flag === Flag.DOWN_FLAG) {
                        this.getData(c13)?.setCanShowFlagLine(false);
                        this.getData(c13)?.setCanShowBottomFlagLine(true);
                    }
                    else {
                        this.getData(c13)?.setCanShowFlagLine(true);
                        this.getData(c13)?.setCanShowBottomFlagLine(false);
                    }
                    this.getData(c13)?.setFlagLineLeftMargin(g13);
                    this.notifyDataChange(c13);
                    this.lastPassId = this.getData(c13)?.getNodeCurrentNodeId();
                }
            }
        }
    }
    delayHighLightAndExpandNode(q12, r12, s12) {
        let t12 = q12 !== this.lastDelayExpandIndex ? true : false;
        let u12 = this.getData(s12)?.getIsOverBorder();
        if (u12) {
            this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE;
        }
        else {
            this.lastDelayExpandIndex = q12;
        }
        if (u12 || t12) {
            let v12 = !u12 && (!this.isInnerDrag ||
                (this.expandAndCollapseInfo.get(r12) === NodeStatus.COLLAPSE && this.isInnerDrag) ||
                (!this.expandAndCollapseInfo.has(r12) && this.listNode[q12].getIsFolder()));
            if (v12) {
                this.changeNodeColor(q12, this.listNode[q12].getNodeStatus().hover);
                this.notifyDataChange(s12);
                let z12 = this.isInnerDrag ? 1000 : 0;
                this.timeoutHighLightId = setTimeout(() => {
                    this.delayHighLight(q12);
                }, z12);
            }
            if (u12 || (this.lastTimeoutHighLightId !== this.INITIAL_INVALID_VALUE &&
                this.clearTimeoutHighLightId !== this.lastTimeoutHighLightId)) {
                clearTimeout(this.lastTimeoutHighLightId);
                if (this.lastDelayHighLightIndex !== this.INITIAL_INVALID_VALUE) {
                    this.clearHighLight(this.lastDelayHighLightIndex);
                    this.notifyDataReload();
                }
                this.clearTimeoutHighLightId = this.lastTimeoutHighLightId;
            }
            this.lastTimeoutHighLightId = this.timeoutHighLightId;
            this.lastDelayHighLightIndex = q12;
            if (!u12 && this.expandAndCollapseInfo.get(r12) === NodeStatus.COLLAPSE) {
                let w12 = this.getData(s12)?.getNodeInfoNode().children[0]?.currentNodeId;
                let x12 = 2000;
                this.timeoutExpandId = setTimeout(() => {
                    this.clearHighLight(this.lastDelayHighLightIndex);
                    if (w12 !== undefined) {
                        this.alterFlagLineAndExpandNode(q12, w12);
                    }
                }, x12);
            }
            if (u12 || (this.lastTimeoutExpandId !== this.INITIAL_INVALID_VALUE &&
                this.clearTimeoutExpandId !== this.lastTimeoutExpandId)) {
                clearTimeout(this.lastTimeoutExpandId);
                this.clearTimeoutExpandId = this.lastTimeoutExpandId;
            }
            this.lastTimeoutExpandId = this.timeoutExpandId;
        }
    }
    delayHighLight(n12) {
        this.listNode.forEach((p12) => {
            if (p12.getNodeCurrentNodeId() === this.lastPassId) {
                p12.setCanShowFlagLine(false);
                p12.setCanShowBottomFlagLine(false);
                return;
            }
        });
        this.changeNodeColor(n12, this.listNode[n12].getNodeStatus().highLight);
        this.listNode[n12].setIsHighLight(true);
        this.changeNodeHighLightColor(n12, true);
        this.setImageSource(n12, InteractionStatus.DRAG_INSERT);
        this.setImageCollapseSource(n12, InteractionStatus.DRAG_INSERT);
        this.notifyDataReload();
    }
    alterFlagLineAndExpandNode(h12, i12) {
        this.listNode.forEach((m12) => {
            if (m12.getNodeCurrentNodeId() === this.lastPassId) {
                m12.setCanShowFlagLine(false);
                m12.setCanShowBottomFlagLine(false);
            }
        });
        this.listNode.forEach((l12) => {
            if (this.isInnerDrag && l12.getNodeCurrentNodeId() === i12) {
                l12.setCanShowFlagLine(true);
            }
        });
        this.changeNodeStatus(h12);
        this.handleExpandAndCollapse(h12, true);
        this.lastPassId = i12;
    }
    hideLastLine() {
        if (this.lastPassId !== this.INITIAL_INVALID_VALUE && this.loadedNodeIdAndIndexMap.has(this.lastPassId)) {
            this.listNode.forEach((g12) => {
                if (g12.getNodeCurrentNodeId() === this.lastPassId) {
                    g12.setCanShowFlagLine(false);
                    g12.setCanShowBottomFlagLine(false);
                    return;
                }
            });
            let e12 = this.loadedNodeIdAndIndexMap.get(this.lastPassId);
            this.notifyDataChange(e12);
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
    getSubtitle(d12) {
        if (this.nodeIdAndSubtitleMap.has(d12)) {
            if (typeof this.nodeIdAndSubtitleMap.get(d12) === 'number') {
                return this.nodeIdAndSubtitleMap.get(d12)?.toString();
            }
            else {
                return this.nodeIdAndSubtitleMap.get(d12);
            }
        }
        else {
            return '';
        }
    }
    hasSubtitle(c12) {
        return this.nodeIdAndSubtitleMap.has(c12);
    }
    initialParameterAboutDelayHighLightAndExpandIndex() {
        this.lastDelayHighLightIndex = this.INITIAL_INVALID_VALUE;
        this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE;
        this.lastPassIndex = this.INITIAL_INVALID_VALUE;
        this.draggingCurrentNodeId = this.INITIAL_INVALID_VALUE;
        this.flag = Flag.NONE;
    }
    refreshSubtitle(b12) {
        this.nodeIdAndSubtitleMap.set(this.selectedParentNodeId, this.selectedParentNodeSubtitle);
        this.nodeIdAndSubtitleMap.set(b12, this.insertNodeSubtitle);
        this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.selectedParentNodeId));
        this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(b12));
    }
    setNodeSubtitlePara(y11, z11, a12) {
        this.selectedParentNodeId = y11;
        this.selectedParentNodeSubtitle = z11;
        this.insertNodeSubtitle = a12;
    }
    getInsertNodeSubtitle() {
        return this.insertNodeSubtitle;
    }
    getExpandAndCollapseInfo(x11) {
        return this.expandAndCollapseInfo.get(x11);
    }
    getLastDelayHighLightId() {
        return this.lastDelayHighLightId;
    }
    setLastDelayHighLightId() {
        this.listNode.forEach((v11, w11) => {
            if (w11 === this.lastDelayHighLightIndex) {
                this.lastDelayHighLightId = v11.getNodeCurrentNodeId();
            }
        });
    }
    setLastPassId(t11) {
        this.lastPassId = t11;
    }
    setLastDelayHighLightIndex(s11) {
        this.lastDelayHighLightIndex = s11;
    }
    alterDragNode(o10, p10, q10, r10, s10) {
        let t10 = [];
        let u10 = o10;
        let v10 = r10;
        let w10 = s10.getNodeInfoData();
        let x10 = null;
        let y10 = s10.getNodeInfoNode();
        let z10 = false;
        let a11 = this.INITIAL_INVALID_VALUE;
        let b11 = this.INITIAL_INVALID_VALUE;
        let c11 = this.flag === Flag.DOWN_FLAG ? true : false;
        b11 = this.getChildIndex(q10, r10);
        a11 = this.getChildIndex(o10, p10) + 1;
        if (o10 !== q10) {
            a11 = c11 ? a11 + 1 : a11;
        }
        else {
            if (a11 > b11) {
                a11 = c11 ? a11 : a11 - 1;
            }
            else {
                a11 = c11 ? a11 + 1 : a11;
            }
        }
        for (let r11 = 0; r11 < this.listNode.length; r11++) {
            if (this.listNode[r11].getNodeCurrentNodeId() === p10) {
                z10 = this.listNode[r11].getIsHighLight();
                if (this.flag === Flag.DOWN_FLAG && this.expandAndCollapseInfo.get(p10) === NodeStatus.EXPAND) {
                    u10 = p10;
                    a11 = 0;
                }
                else if (this.flag === Flag.UP_FLAG && this.expandAndCollapseInfo.get(p10) ===
                    NodeStatus.EXPAND &&
                    this.listNode[r11].getCanShowFlagLine() === false) {
                    u10 = p10;
                    a11 = 0;
                }
                else if (z10) {
                    u10 = p10;
                    a11 = 0;
                }
                break;
            }
        }
        let d11 = {
            currentNodeId: v10,
            parentNodeId: u10,
            childIndex: a11,
        };
        this.appEventBus.emit(TreeListenType.NODE_MOVE, d11);
        t10.push({ parentId: u10, currentId: v10, data: w10 });
        let e11 = (n11, o11) => {
            if (n11) {
                u10 = n11.parentNodeId;
                v10 = n11.currentNodeId;
                for (let q11 = 0; q11 < o11.length; q11++) {
                    if (o11[q11].getNodeCurrentNodeId() === v10) {
                        x10 = o11[q11];
                        break;
                    }
                }
                if (x10 === null) {
                    return false;
                }
                let p11 = x10.getNodeInfoData();
                if (u10 !== q10) {
                    t10.push({ parentId: u10, currentId: v10, data: p11 });
                }
                return false;
            }
            return false;
        };
        this.dragTraverseNodeDF(e11, y10, this.listNode);
        this.removeNode(r10, q10);
        let f11 = p10;
        let g11 = c11;
        if (this.expandAndCollapseInfo.get(p10) === NodeStatus.EXPAND) {
            g11 = false;
            this.listNode.forEach((m11) => {
                if (m11.getNodeCurrentNodeId() === p10 && m11.getCanShowFlagLine() === false) {
                    if (m11.getNodeInfoNode().children.length) {
                        f11 = m11.getNodeInfoNode().children[0].currentNodeId;
                    }
                    else {
                        f11 = this.INITIAL_INVALID_VALUE;
                    }
                }
            });
        }
        else if (!this.expandAndCollapseInfo.get(p10) && z10) {
            this.expandAndCollapseInfo.set(p10, NodeStatus.EXPAND);
        }
        this.addDragNode(t10[0].parentId, t10[0].currentId, f11, g11, t10[0].data);
        for (let k11 = 1; k11 < t10.length; k11++) {
            this.addNode(t10[k11].parentId, t10[k11].currentId, t10[k11].data, false);
        }
        for (let j11 = 0; j11 < this.listNode.length; j11++) {
            if (this.listNode[j11].getNodeCurrentNodeId() === q10) {
                if (this.listNode[j11].getNodeItem().imageCollapse === null) {
                    this.listNode[j11].handleImageCollapseAfterAddNode(false);
                    this.expandAndCollapseInfo.delete(q10);
                    break;
                }
            }
        }
        let h11 = [...this.listNode];
        this.reloadListNode(h11);
    }
    reloadListNode(g10) {
        let h10 = 0;
        let i10 = 0;
        this.listNode.splice(0, this.listNode.length);
        this.loadedNodeIdAndIndexMap.clear();
        this.loadedListNode.splice(0, this.loadedListNode.length);
        this.traverseNodeDF((k10) => {
            let l10 = k10.currentNodeId;
            if (l10 >= 0) {
                if (this.nodeIdNodeParamMap.has(l10)) {
                    let m10 = new NodeInfo(k10, this.nodeIdNodeParamMap.get(l10));
                    m10.addImageCollapse(k10.getChildNodeInfo().isHasChildNode);
                    this.listNode.push(m10);
                    this.nodeIdAndNodeIndexMap.set(m10.getNodeCurrentNodeId(), i10++);
                    if (this.expandAndCollapseInfo.get(l10) === NodeStatus.EXPAND) {
                        m10.getNodeItem().imageCollapse = m10.getNodeItem().imageCollapse ?
                        CollapseImageNodeFlyweightFactory.changeImageCollapseSource(NodeStatus.EXPAND,
                            m10.getNodeItem().imageCollapse.isCollapse) : undefined;
                    } else if (this.expandAndCollapseInfo.get(l10) === NodeStatus.COLLAPSE) {
                        m10.getNodeItem().imageCollapse = m10.getNodeItem().imageCollapse ?
                        CollapseImageNodeFlyweightFactory.changeImageCollapseSource(NodeStatus.COLLAPSE,
                            m10.getNodeItem().imageCollapse.isCollapse) : undefined;
                    }
                    for (let n10 = 0; n10 < g10.length; n10++) {
                        if (g10[n10].getNodeCurrentNodeId() === m10.getNodeCurrentNodeId()) {
                            m10.setNodeIsShow(g10[n10].getNodeIsShow());
                            m10.setListItemHeight(g10[n10].getListItemHeight());
                            if (m10.getNodeItem().mainTitleNode && m10.getIsShowTitle()) {
                                m10.getNodeItem().mainTitleNode.title = g10[n10].getNodeItem().mainTitleNode?.title;
                            }
                            break;
                        }
                    }
                    if (m10.getNodeIsShow()) {
                        this.loadedNodeIdAndIndexMap.set(m10.getNodeCurrentNodeId(), h10++);
                        this.loadedListNode.push(m10);
                    }
                }
            }
            return false;
        });
    }
    getFlagLine() {
        return this.FLAG_LINE;
    }
    getVisibility(d10) {
        let e10 = this.loadedNodeIdAndIndexMap.get(d10.getNodeCurrentNodeId()) - 1;
        if (e10 > this.INITIAL_INVALID_VALUE) {
            let f10 = this.getData(e10);
            return (d10.getCanShowFlagLine() === true && !d10.getIsHighLight() && !f10?.getIsHighLight()) ?
                Visibility.Visible : Visibility.Hidden;
        }
        else {
            return (d10.getCanShowFlagLine() === true && !d10.getIsHighLight()) ?
                Visibility.Visible : Visibility.Hidden;
        }
    }
    getSubTitlePara() {
        return this.subTitle;
    }
    getIsFolder(c10) {
        if (this.loadedNodeIdAndIndexMap.has(c10)) {
            return this.getData(this.loadedNodeIdAndIndexMap.get(c10))?.getIsFolder();
        }
        return false;
    }
    getSubTitleFontColor(b10) {
        return b10 ? this.subTitle.highLightFontColor : this.treeViewTheme.secondaryTitleFontColor;
    }
    getChildIndex(u9, v9) {
        let w9 = this.INITIAL_INVALID_VALUE;
        if (this.nodeIdNodeItemMap.has(u9)) {
            let x9 = this.nodeIdNodeItemMap.get(u9);
            if (x9.getCurrentNodeId() === u9) {
                x9.children.forEach((z9, a10) => {
                    if (z9.getCurrentNodeId() === v9) {
                        w9 = a10;
                        return;
                    }
                });
            }
        }
        return w9;
    }
    setCurrentFocusNodeId(t9) {
        this.currentFocusNodeId = t9;
    }
    getCurrentFocusNodeId() {
        return this.currentFocusNodeId;
    }
    setLastFocusNodeId(s9) {
        this.lastFocusNodeId = s9;
    }
    getLastFocusNodeId() {
        return this.lastFocusNodeId;
    }
    getAddFocusNodeId() {
        return this.addFocusNodeId;
    }
    setFlag(r9) {
        this.flag = r9;
    }
    traverseNodeDF(m9, n9 = this._root) {
        let o9 = [];
        let p9 = false;
        o9.unshift(n9);
        let q9 = o9.shift();
        while (!p9 && q9) {
            p9 = m9(q9) === true;
            if (!p9) {
                o9.unshift(...q9.children);
                q9 = o9.shift();
            }
        }
    }
    traverseSectionNodeDF(d9, e9 = this._root, f9, g9) {
        let h9 = [];
        let i9 = false;
        let j9 = false;
        h9.unshift(e9);
        let k9 = h9.shift();
        while (!i9 && k9) {
            try {
                if (f9 !== undefined && k9.nodeLevel < f9) {
                    j9 = true;
                }
                if (g9 !== undefined && k9.nodeLevel > g9) {
                    j9 = true;
                }
                if (!j9) {
                    i9 = d9(k9);
                }
            }
            catch (l9) {
                throw new Error('traverseSectionNodeDF function callbacks error');
            }
            if (!i9) {
                h9.unshift(...k9.children);
                k9 = h9.shift();
                j9 = false;
            }
        }
    }
    updateParentChildNum(y8, z8, a9) {
        let b9 = y8.parentNodeId;
        while (b9 >= 0) {
            if (this.nodeIdNodeItemMap.has(b9)) {
                let c9 = this.nodeIdNodeItemMap.get(b9);
                c9.getChildNodeInfo().allChildNum =
                    z8 ? c9.getChildNodeInfo().allChildNum + a9 : c9.getChildNodeInfo().allChildNum - a9;
                b9 = c9.parentNodeId;
            }
            else {
                throw new Error('updateParentChildNum: Parent node not found');
            }
        }
    }
    findParentNodeId(w8) {
        let x8 = new NodeItem(emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(w8)) {
            x8 = this.nodeIdNodeItemMap.get(w8);
        }
        return x8.parentNodeId;
    }
    addNode(n8, o8, p8, q8) {
        if (this._root === null) {
            this._root = new NodeItem(emptyNodeInfo);
            this._root.nodeLevel = -1;
            this.nodeIdNodeItemMap.set(-1, this._root);
            this.nodeIdNodeParamMap.set(-1, emptyNodeInfo);
        }
        if (this.nodeIdNodeItemMap.has(n8)) {
            let r8 = this.nodeIdNodeItemMap.get(n8);
            let s8 = new NodeItem(p8);
            if (r8.nodeLevel > this.maxNodeLevel) {
                throw new Error('ListNodeUtils[addNode]: The level of the tree view cannot exceed 50.');
            }
            s8.nodeLevel = r8.nodeLevel + 1;
            s8.parentNodeId = n8;
            s8.currentNodeId = o8;
            s8.indexOfParent = r8.children.length;
            p8.parentNodeId = n8;
            p8.currentNodeId = o8;
            r8.children.push(s8);
            r8.getChildNodeInfo().isHasChildNode = true;
            r8.getChildNodeInfo().childNum = r8.children.length;
            r8.getChildNodeInfo().allChildNum += 1;
            if (q8) {
                this.updateNodeIdList.push(r8.parentNodeId);
            }
            else {
                let t8 = [];
                t8.push(r8.parentNodeId);
                let u8 = setTimeout(() => {
                    concurrentUpdateParentChildNum(true, 1, this.nodeIdNodeItemMap, t8);
                    clearTimeout(u8);
                }, DELAY_TIME);
            }
            this.nodeIdNodeParamMap.set(o8, p8);
            this.nodeIdNodeItemMap.set(o8, s8);
            return;
        }
        else {
            throw new Error('ListDataSource[addNode]: Parent node not found.');
        }
    }
    findNodeIndex(i8, j8) {
        let k8 = this.INITIAL_INVALID_VALUE;
        for (let l8 = 0, m8 = i8.length; l8 < m8; l8++) {
            if (i8[l8].currentNodeId === j8) {
                k8 = l8;
                break;
            }
        }
        return k8;
    }
    freeNodeMemory(a8, b8) {
        let c8 = [];
        let d8 = (h8) => {
            c8.push(h8);
            return false;
        };
        this.traverseNodeDF(d8, a8);
        c8.forEach((g8) => {
            b8.push(g8.getCurrentNodeId());
            this.nodeIdNodeItemMap.delete(g8.getCurrentNodeId());
            this.nodeIdNodeParamMap.delete(g8.getCurrentNodeId());
            g8 = new NodeItem(emptyNodeInfo);
        });
    }
    removeNode(n7, o7) {
        if (this.nodeIdNodeItemMap.has(o7) && this.nodeIdNodeItemMap.has(n7)) {
            let p7 = this.nodeIdNodeItemMap.get(o7);
            let q7 = this.nodeIdNodeItemMap.get(n7);
            let r7 = [];
            let s7 = q7.indexOfParent;
            let t7 = 0;
            if (s7 < 0) {
                throw new Error('Node does not exist.');
            }
            else {
                t7 = p7.children[s7].getChildNodeInfo().allChildNum + 1;
                this.freeNodeMemory(p7.children[s7], r7);
                for (let z7 = s7; z7 < p7.children.length; z7++) {
                    p7.children[z7].indexOfParent -= 1;
                }
                let x7 = p7.children.splice(s7, 1);
                x7 = null;
                if (p7.children.length === 0) {
                    if (this.nodeIdAndNodeIndexMap.has(o7)) {
                        let y7 = this.nodeIdAndNodeIndexMap.get(o7);
                        this.listNode[y7]?.addImageCollapse(false);
                    }
                }
            }
            p7.getChildNodeInfo().childNum = p7.children.length;
            p7.getChildNodeInfo().allChildNum -= (t7);
            let u7 = [];
            u7.push(p7.parentNodeId);
            let v7 = setTimeout(() => {
                concurrentUpdateParentChildNum(false, t7, this.nodeIdNodeItemMap, u7);
                clearTimeout(v7);
            }, DELAY_TIME);
            return r7;
        }
        else {
            throw new Error('Parent does not exist.');
        }
    }
    getNodeInfoByNodeItem(l7) {
        if (l7?.currentNodeId === undefined) {
            throw new Error('getNodeInfoByNodeItem: currentId is undefined');
        }
        if (!this.nodeIdAndNodeIndexMap.has(l7.currentNodeId)) {
            throw new Error('getNodeInfoByNodeItem: not has nodeItem');
        }
        let m7 = this.nodeIdAndNodeIndexMap.get(l7.currentNodeId);
        return this.listNode[m7];
    }
    getNewNodeParam(g7) {
        let h7 = new NodeItem(emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(g7)) {
            h7 = this.nodeIdNodeItemMap.get(g7);
        }
        let i7 = emptyNodeInfo;
        if (h7) {
            let j7 = this.getNodeInfoByNodeItem(h7);
            if (h7.children.length === 0) {
                if (j7.getNodeItem().imageNode !== undefined) {
                    i7.icon = j7.getNodeItem().imageNode?.normalSource;
                    i7.selectedIcon = j7.getNodeItem().imageNode?.selectedSource;
                    i7.editIcon = j7.getNodeItem().imageNode?.editSource;
                    i7.container = j7.getMenu();
                }
                else {
                    i7.icon = undefined;
                    i7.selectedIcon = undefined;
                    i7.editIcon = undefined;
                    i7.container = j7.getMenu();
                }
            }
            else if (h7.children.length > 0) {
                let k7 = this.getNodeInfoByNodeItem(h7.children[0]);
                if (j7.getNodeItem().imageNode !== null) {
                    i7.icon = (k7.getNodeItem().imageNode !== undefined) ?
                        k7.getNodeItem().imageNode?.normalSource : undefined;
                    i7.selectedIcon = (k7.getNodeItem().imageNode !== undefined) ?
                        k7.getNodeItem().imageNode?.selectedSource : undefined;
                    i7.editIcon = (k7.getNodeItem().imageNode !== undefined) ?
                        k7.getNodeItem().imageNode?.editSource : undefined;
                    i7.container = k7.getMenu();
                }
                else {
                    i7.icon = undefined;
                    i7.selectedIcon = undefined;
                    i7.editIcon = undefined;
                    i7.container = k7.getMenu();
                }
            }
        }
        return i7;
    }
    getClickChildId(b7) {
        let c7 = new NodeItem(emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(b7)) {
            c7 = this.nodeIdNodeItemMap.get(b7);
        }
        if (c7) {
            if (c7.children.length === 0) {
                return [];
            }
            else if (c7.children.length > 0) {
                let d7 = new Array(c7.children.length);
                for (let f7 = 0; f7 < d7.length; f7++) {
                    d7[f7] = 0;
                }
                for (let e7 = 0; e7 < c7.children.length && e7 < d7.length; e7++) {
                    d7[e7] = c7.children[e7].currentNodeId;
                }
                return d7;
            }
        }
        return [];
    }
    getClickNodeChildrenInfo(v6) {
        let w6 = new NodeItem(emptyNodeInfo);
        if (this.nodeIdNodeItemMap.has(v6)) {
            w6 = this.nodeIdNodeItemMap.get(v6);
        }
        if (w6) {
            if (w6.children.length === 0) {
                return [];
            }
            else if (w6.children.length > 0) {
                let x6 = new Array(w6.children.length);
                for (let a7 = 0; a7 < x6.length; a7++) {
                    x6[a7] = {};
                }
                for (let y6 = 0; y6 < w6.children.length && y6 < x6.length; y6++) {
                    x6[y6].itemId = w6.children[y6].currentNodeId;
                    let z6 = this.getNodeInfoByNodeItem(w6.children[y6]);
                    if (z6.getNodeItem().imageNode) {
                        x6[y6].itemIcon = z6.getNodeItem().imageNode?.source;
                    }
                    if (z6.getNodeItem().mainTitleNode) {
                        x6[y6].itemTitle = z6.getNodeItem().mainTitleNode?.title;
                    }
                    x6[y6].isFolder = z6.getIsFolder();
                }
                return x6;
            }
        }
        return [];
    }
    checkMainTitleIsValid(u6) {
        if (new RegExp('/[\\\/:*?"<>|]/').test(u6)) {
            return false;
        }
        if ((new RegExp('/^[\u4e00-\u9fa5]+$/').test(u6) && u6.length > this.MAX_CN_LENGTH) ||
            (!new RegExp('/^[\u4e00-\u9fa5]+$/').test(u6) && u6.length > this.MAX_EN_LENGTH)) {
            return false;
        }
        return true;
    }
    dragTraverseNodeDF(o6, p6 = this._root, q6) {
        let r6 = [];
        let s6 = false;
        r6.unshift(p6);
        let t6 = r6.shift();
        while (!s6 && t6) {
            s6 = o6(t6, q6) === true;
            if (!s6) {
                r6.unshift(...t6.children);
                t6 = r6.shift();
            }
        }
    }
    updateChildIndexOfParent(l6, m6) {
        for (let n6 = l6; n6 < m6.children.length; n6++) {
            m6.children[n6].indexOfParent += 1;
        }
    }
    addDragNode(c6, d6, e6, f6, g6) {
        if (this._root === null) {
            this._root = new NodeItem(emptyNodeInfo);
            this._root.nodeLevel = this.INITIAL_INVALID_VALUE;
        }
        if (this.nodeIdNodeItemMap.has(c6)) {
            let h6 = this.nodeIdNodeItemMap.get(c6);
            let i6 = new NodeItem(g6);
            if (h6.nodeLevel > this.maxNodeLevel) {
                throw new Error('ListNodeUtils[addNode]: The level of the tree view cannot exceed 50.');
            }
            i6.nodeLevel = h6.nodeLevel + 1;
            i6.parentNodeId = c6;
            i6.currentNodeId = d6;
            g6.parentNodeId = c6;
            g6.currentNodeId = d6;
            let j6 = this.INITIAL_INVALID_VALUE;
            if (h6.children.length) {
                for (let k6 = 0; k6 < h6.children.length; k6++) {
                    if (h6.children[k6].getCurrentNodeId() === e6) {
                        j6 = k6;
                        break;
                    }
                }
                if (f6) {
                    i6.indexOfParent = j6 + 1;
                    this.updateChildIndexOfParent(i6.indexOfParent, h6);
                    h6.children.splice(j6 + 1, 0, i6);
                }
                else {
                    i6.indexOfParent = j6 < 0 ? h6.children.length + j6 : j6;
                    this.updateChildIndexOfParent(i6.indexOfParent, h6);
                    h6.children.splice(j6, 0, i6);
                }
            }
            else {
                i6.indexOfParent = h6.children.length;
                h6.children.push(i6);
            }
            h6.getChildNodeInfo().isHasChildNode = true;
            h6.getChildNodeInfo().childNum = h6.children.length;
            h6.getChildNodeInfo().allChildNum += 1;
            this.updateParentChildNum(h6, true, 1);
            this.nodeIdNodeItemMap.set(d6, i6);
            this.nodeIdNodeParamMap.set(d6, g6);
        }
        else {
            throw new Error('addDragNode: Parent node not found.');
        }
    }
}
export class TreeViewInner extends ViewPU {
    constructor(w5, x5, y5, z5 = -1, a6 = undefined, b6) {
        super(w5, y5, z5, b6);
        if (typeof a6 === 'function') {
            this.paramsGenerator_ = a6;
        }
        this.__item = new SynchedPropertyNesedObjectPU(x5.item, this, 'item');
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
            id: -1,
            type: 10002,
            params: ['sys.float.ohos_id_card_margin_start'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
          right: {
            id: -1,
            type: 10002,
            params: ['sys.float.ohos_id_card_margin_end'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
          top: {
            id: -1,
            type: 10002,
            params: ['sys.float.ohos_id_text_margin_vertical'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
          bottom: {
            id: -1,
            type: 10002,
            params: ['sys.float.padding_level0'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
        };
        this.textInputPadding = {
          left: {
            id: -1,
            type: 10002,
            params: ['sys.float.padding_level0'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
          right: {
            id: -1,
            type: 10002,
            params: ['sys.float.padding_level0'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
          top: {
            id: -1,
            type: 10002,
            params: ['sys.float.padding_level0'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
          bottom: {
            id: -1,
            type: 10002,
            params: ['sys.float.padding_level0'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
        };
        this.setInitiallyProvidedValue(x5);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(v5) {
        this.__item.set(v5.item);
        if (v5.listNodeDataSource !== undefined) {
            this.listNodeDataSource = v5.listNodeDataSource;
        }
        if (v5.columnWidth !== undefined) {
            this.columnWidth = v5.columnWidth;
        }
        if (v5.isFocused !== undefined) {
            this.isFocused = v5.isFocused;
        }
        if (v5.index !== undefined) {
            this.index = v5.index;
        }
        if (v5.lastIndex !== undefined) {
            this.lastIndex = v5.lastIndex;
        }
        if (v5.count !== undefined) {
            this.count = v5.count;
        }
        if (v5.listTreeViewMenu !== undefined) {
            this.listTreeViewMenu = v5.listTreeViewMenu;
        }
        if (v5.MAX_CN_LENGTH !== undefined) {
            this.MAX_CN_LENGTH = v5.MAX_CN_LENGTH;
        }
        if (v5.MAX_EN_LENGTH !== undefined) {
            this.MAX_EN_LENGTH = v5.MAX_EN_LENGTH;
        }
        if (v5.INITIAL_INVALID_VALUE !== undefined) {
            this.INITIAL_INVALID_VALUE = v5.INITIAL_INVALID_VALUE;
        }
        if (v5.MAX_TOUCH_DOWN_COUNT !== undefined) {
            this.MAX_TOUCH_DOWN_COUNT = v5.MAX_TOUCH_DOWN_COUNT;
        }
        if (v5.isMultiPress !== undefined) {
            this.isMultiPress = v5.isMultiPress;
        }
        if (v5.touchDownCount !== undefined) {
            this.touchDownCount = v5.touchDownCount;
        }
        if (v5.appEventBus !== undefined) {
            this.appEventBus = v5.appEventBus;
        }
        if (v5.itemPadding !== undefined) {
            this.itemPadding = v5.itemPadding;
        }
        if (v5.textInputPadding !== undefined) {
            this.textInputPadding = v5.textInputPadding;
        }
    }
    updateStateVars(u5) {
        this.__item.set(u5.item);
    }
    purgeVariableDependenciesOnElmtId(t5) {
        this.__item.purgeDependencyOnElmtId(t5);
        this.__columnWidth.purgeDependencyOnElmtId(t5);
        this.__isFocused.purgeDependencyOnElmtId(t5);
        this.__index.purgeDependencyOnElmtId(t5);
        this.__lastIndex.purgeDependencyOnElmtId(t5);
        this.__count.purgeDependencyOnElmtId(t5);
        this.__treeViewTheme.purgeDependencyOnElmtId(t5);
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
    set columnWidth(s5) {
        this.__columnWidth.set(s5);
    }
    get isFocused() {
        return this.__isFocused.get();
    }
    set isFocused(r5) {
        this.__isFocused.set(r5);
    }
    get index() {
        return this.__index.get();
    }
    set index(q5) {
        this.__index.set(q5);
    }
    get lastIndex() {
        return this.__lastIndex.get();
    }
    set lastIndex(p5) {
        this.__lastIndex.set(p5);
    }
    get count() {
        return this.__count.get();
    }
    set count(o5) {
        this.__count.set(o5);
    }
    get treeViewTheme() {
        return this.__treeViewTheme.get();
    }
    set treeViewTheme(n5) {
        this.__treeViewTheme.set(n5);
    }
    aboutToAppear() {
        if (this.item.getNodeItem().imageNode) {
            this.item.imageSource = this.item.getNodeItem().imageNode?.source;
        }
    }
    checkInvalidPattern(m5) {
        return new RegExp('/[\\\/:*?"<>|]/').test(m5);
    }
    checkIsAllCN(l5) {
        return new RegExp('/^[\u4e00-\u9fa5]+$/').test(l5);
    }
    popupForShowTitle(b5, c5, d5, e5 = null) {
        this.observeComponentCreation2((j5, k5) => {
            Row.create();
            Row.backgroundColor(c5);
            Row.border({
              radius: {
                id: -1,
                type: 10002,
                params: ['sys.float.ohos_id_elements_margin_horizontal_l'],
                bundleName: '__harDefaultBundleName__',
                moduleName: '__harDefaultModuleName__',
              },
            });
            Row.padding({
              left: {
                id: -1,
                type: 10002,
                params: ['sys.float.ohos_id_elements_margin_horizontal_l'],
                bundleName: '__harDefaultBundleName__',
                moduleName: '__harDefaultModuleName__',
              },
              right: {
                id: -1,
                type: 10002,
                params: ['sys.float.ohos_id_elements_margin_horizontal_l'],
                bundleName: '__harDefaultBundleName__',
                moduleName: '__harDefaultModuleName__',
              },
              top: {
                id: -1,
                type: 10002,
                params: ['sys.float.ohos_id_card_margin_middle'],
                bundleName: '__harDefaultBundleName__',
                moduleName: '__harDefaultModuleName__',
              },
              bottom: {
                id: -1,
                type: 10002,
                params: ['sys.float.ohos_id_card_margin_middle'],
                bundleName: '__harDefaultBundleName__',
                moduleName: '__harDefaultModuleName__',
              },
            });
        }, Row);
        this.observeComponentCreation2((h5, i5) => {
            Text.create(b5);
            Text.fontSize({
              id: -1,
              type: 10002,
              params: ['sys.float.ohos_id_text_size_body2'],
              bundleName: '__harDefaultBundleName__',
              moduleName: '__harDefaultModuleName__',
            });
            Text.fontWeight('regular');
            Text.fontColor(d5);
        }, Text);
        Text.pop();
        Row.pop();
    }
    builder(v4 = null) {
        this.observeComponentCreation2((x4, y4) => {
            If.create();
            if (this.listTreeViewMenu) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.listTreeViewMenu.bind(this)(v4 ? v4 : this);
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
        this.observeComponentCreation2((v, w) => {
            If.create();
            if (this.item.getNodeIsShow()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((t4, u4) => {
                        Stack.create();
                        ViewStackProcessor.visualState('focused');
                        Stack.border({
                          radius: {
                            id: -1,
                            type: 10002,
                            params: ['sys.float.ohos_id_corner_radius_clicked'],
                            bundleName: '__harDefaultBundleName__',
                            moduleName: '__harDefaultModuleName__',
                          },
                          width: FLAG_NUMBER,
                          color: this.treeViewTheme.borderFocusedColor,
                          style: BorderStyle.Solid,
                        });
                        ViewStackProcessor.visualState('normal');
                        Stack.border({
                          radius: {
                            id: -1,
                            type: 10002,
                            params: ['sys.float.ohos_id_corner_radius_clicked'],
                            bundleName: '__harDefaultBundleName__',
                            moduleName: '__harDefaultModuleName__',
                          },
                          width: 0,
                        });
                        ViewStackProcessor.visualState();
                    }, Stack);
                    this.observeComponentCreation2((e4, f4) => {
                        Column.create();
                        Column.opacity(this.listNodeDataSource.getListItemOpacity(ObservedObject.GetRawObject(this.item)));
                        Column.onHover((s4) => {
                            if (s4) {
                                this.item.setNodeColor(this.treeViewTheme.itemHoverBgColor);
                            }
                            else {
                                this.item.setNodeColor({
                                  id: -1,
                                  type: 10001,
                                  params: [
                                    'sys.color.ohos_id_color_background_transparent',
                                  ],
                                  bundleName: '__harDefaultBundleName__',
                                  moduleName: '__harDefaultModuleName__',
                                });
                            }
                        });
                        Column.onTouch((p4) => {
                            this.count++;
                            if (this.count > 1) {
                                this.count--;
                                return;
                            }
                            this.index = this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId());
                            this.listNodeDataSource.setClickIndex(this.index);
                            let q4 = this.item.getNodeCurrentNodeId();
                            if (p4.type === TouchType.Down) {
                                this.item.setNodeColor(this.treeViewTheme.itemPressedBgColor);
                            }
                            else if (p4.type === TouchType.Up) {
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
                                let r4 = { currentNodeId: q4 };
                                this.appEventBus.emit(TreeListenType.NODE_CLICK, r4);
                            }
                            if (this.listNodeDataSource.getLastIndex() !== -1 && this.index !== this.listNodeDataSource.getLastIndex()) {
                                this.listNodeDataSource.setPopUpInfo(
                                  PopUpType.WARNINGS,
                                  InputError.NONE,
                                  false,
                                  this.listNodeDataSource.getLastIndex()
                                );
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
                        Column.onMouse((n4) => {
                            let o4 = this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId());
                            if (n4.button === MouseButton.Right) {
                                this.listNodeDataSource.handleEvent(
                                  Event.MOUSE_BUTTON_RIGHT,
                                  this.listNodeDataSource.findIndex(
                                    this.item.getNodeCurrentNodeId()
                                  )
                                );
                                this.listTreeViewMenu = this.item.getMenu();
                                this.listNodeDataSource.setClickIndex(o4);
                                clearTimeout(this.item.getNodeItem().mainTitleNode?.popUpTimeout);
                            }
                            n4.stopPropagation();
                        });
                        Column.padding({ top: 0, bottom: 0 });
                        Column.bindPopup(this.item.getPopUpInfo().popUpIsShow, {
                            builder: { builder: () => {
                                    this.popupForShowTitle.call(
                                      this,
                                      this.item.getPopUpInfo().popUpText,
                                      this.item.getPopUpInfo().popUpColor,
                                      this.item.getPopUpInfo().popUpTextColor
                                    );
                                } },
                            placement: Placement.BottomLeft,
                            placementOnTop: false,
                            popupColor: this.item.getPopUpInfo().popUpColor,
                            autoCancel: true,
                            enableArrow: this.item.getPopUpInfo().popUpEnableArrow
                        });
                        Column.onAreaChange((k4, l4) => {
                            let m4 = Number.parseInt(l4.width.toString());
                            this.columnWidth = m4;
                        });
                    }, Column);
                    this.observeComponentCreation2((c4, d4) => {
                        Stack.create({ alignContent: Alignment.Bottom });
                        Stack.focusable(true);
                    }, Stack);
                    this.observeComponentCreation2((a4, b4) => {
                        Divider.create();
                        Divider.height(this.listNodeDataSource.getFlagLine().flagLineHeight);
                        Divider.color(this.listNodeDataSource.getFlagLine().flagLineColor);
                        Divider.visibility(this.listNodeDataSource.getVisibility(ObservedObject.GetRawObject(this.item)));
                        Divider.lineCap(LineCapStyle.Round);
                        Divider.margin({ start: LengthMetrics.vp(this.item.getFlagLineLeftMargin()) });
                        Divider.focusable(true);
                    }, Divider);
                    this.observeComponentCreation2((w3, x3) => {
                        Row.create({});
                        Row.focusable(true);
                        Row.width('100%');
                        Gesture.create(GesturePriority.Low);
                        TapGesture.create({ count: 2 });
                        TapGesture.onAction((z3) => {
                            this.listNodeDataSource.expandAndCollapseNode(this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId()));
                        });
                        TapGesture.pop();
                        Gesture.pop();
                        Row.height(this.item.getNodeHeight());
                        Row.padding({ start: LengthMetrics.vp(this.item.getNodeLeftPadding()) });
                        Row.bindContextMenu({ builder: this.builder.bind(this) }, ResponseType.RightClick);
                    }, Row);
                    this.observeComponentCreation2((m3, n3) => {
                        If.create();
                        if (this.item.getNodeItem().imageNode) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((u3, v3) => {
                                    Row.create();
                                    Row.focusable(true);
                                    Row.backgroundColor(COLOR_IMAGE_ROW);
                                    Row.margin({
                                        end: getLengthMetricsByResourceOrNumber(this.item.getNodeItem().imageNode?.itemRightMargin)
                                    });
                                    Row.height(this.item.getNodeItem().imageNode?.itemHeight);
                                    Row.width(this.item.getNodeItem().imageNode?.itemWidth);
                                }, Row);
                                this.observeComponentCreation2((s3, t3) => {
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
                    this.observeComponentCreation2((k3, l3) => {
                        Row.create();
                        Row.layoutWeight(1);
                        Row.focusable(true);
                    }, Row);
                    this.observeComponentCreation2((d3, e3) => {
                        If.create();
                        if (this.item.getNodeItem().mainTitleNode && this.item.getIsShowTitle()) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((i3, j3) => {
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
                    this.observeComponentCreation2((j2, k2) => {
                        If.create();
                        if (this.item.getNodeItem().mainTitleNode && this.item.getNodeItem().inputText &&
                            this.item.getIsShowInputText()) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((b3, c3) => {
                                    Row.create();
                                    Row.backgroundColor(this.item.getNodeItem().inputText?.backgroundColor);
                                    Row.borderRadius(this.item.getNodeItem().inputText?.borderRadius);
                                    Row.margin({
                                        end: getLengthMetricsByResourceOrNumber(this.item.getNodeItem()
                                            .inputText?.itemRightMargin)
                                    });
                                }, Row);
                                this.observeComponentCreation2((p2, q2) => {
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
                                    TextInput.onChange((v2) => {
                                        let w2 = this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId());
                                        let x2 = '';
                                        let y2 = false;
                                        let z2 = false;
                                        if (this.checkInvalidPattern(v2)) {
                                            for (let a3 = 0; a3 < v2.length; a3++) {
                                                if (!this.checkInvalidPattern(v2[a3])) {
                                                    x2 += v2[a3];
                                                }
                                            }
                                            y2 = true;
                                            this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.INVALID_ERROR, true, w2);
                                        }
                                        else {
                                            x2 = v2;
                                            y2 = false;
                                        }
                                        if ((this.checkIsAllCN(x2) && x2.length > this.MAX_CN_LENGTH) ||
                                            (!this.checkIsAllCN(x2) && x2.length > this.MAX_EN_LENGTH)) {
                                            x2 = this.checkIsAllCN(x2) ?
                                                x2.substr(0, this.MAX_CN_LENGTH) : x2.substr(0, this.MAX_EN_LENGTH);
                                            z2 = true;
                                            this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.LENGTH_ERROR, true, w2);
                                        }
                                        else {
                                            z2 = false;
                                        }
                                        if (!z2 && !y2) {
                                            this.listNodeDataSource.setMainTitleNameOnEdit(w2, x2);
                                        }
                                    });
                                    TextInput.onSubmit((t2) => {
                                        let u2 = this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId());
                                        this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false, u2);
                                        this.listNodeDataSource.setItemVisibilityOnEdit(u2, MenuOperation.COMMIT_NODE);
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
                    this.observeComponentCreation2((h2, i2) => {
                        Blank.create();
                    }, Blank);
                    Blank.pop();
                    Row.pop();
                    this.observeComponentCreation2((x1, y1) => {
                        If.create();
                        if (this.listNodeDataSource.hasSubtitle(this.item.getNodeCurrentNodeId())) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((f2, g2) => {
                                    Row.create();
                                    Row.focusable(true);
                                    Row.margin({
                                      start: LengthMetrics.resource(
                                        this.listNodeDataSource.getSubTitlePara()
                                          .margin.left
                                      ),
                                      end: this.item.getNodeItem().imageCollapse
                                        ? LengthMetrics.resource({
                                            id: -1,
                                            type: 10002,
                                            params: [
                                              'sys.float.padding_level0',
                                            ],
                                            bundleName:
                                              '__harDefaultBundleName__',
                                            moduleName:
                                              '__harDefaultModuleName__',
                                          })
                                        : LengthMetrics.resource(
                                            this.listNodeDataSource.getSubTitlePara()
                                              .margin.right
                                          ),
                                    });
                                }, Row);
                                this.observeComponentCreation2((d2, e2) => {
                                    Text.create(this.listNodeDataSource.getSubtitle(this.item.getNodeCurrentNodeId()));
                                    Text.fontSize(this.listNodeDataSource.getSubTitlePara().fontSize);
                                    Text.fontColor(
                                      this.item.getIsHighLight() ||
                                        this.item.getIsModify()
                                        ? {
                                            id: -1,
                                            type: 10001,
                                            params: [
                                              'sys.color.ohos_id_color_primary_contrary',
                                            ],
                                            bundleName:
                                              '__harDefaultBundleName__',
                                            moduleName:
                                              '__harDefaultModuleName__',
                                          }
                                        : this.treeViewTheme
                                            .secondaryTitleFontColor
                                    );
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
                    this.observeComponentCreation2((l1, m1) => {
                        If.create();
                        if (this.item.getNodeItem().imageCollapse) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((v1, w1) => {
                                    Row.create();
                                    Row.focusable(true);
                                    Row.height(this.item.getNodeItem().imageCollapse?.itemHeight);
                                    Row.width(this.item.getNodeItem().imageCollapse?.itemWidth);
                                }, Row);
                                this.observeComponentCreation2((r1, s1) => {
                                    Image.create(this.item.getNodeItem().imageCollapse?.collapseSource);
                                    Image.fillColor(
                                      this.item.getNodeItem().imageCollapse
                                        ?.isCollapse
                                        ? this.treeViewTheme.arrowIconColor
                                        : COLOR_IMAGE_EDIT
                                    );
                                    Image.align(Alignment.End);
                                    Image.objectFit(ImageFit.Contain);
                                    Image.height(this.item.getNodeItem().imageCollapse?.itemHeight);
                                    Image.width(this.item.getNodeItem().imageCollapse?.itemWidth);
                                    Image.opacity(!this.item.getIsHighLight() ?
                                        this.item.getNodeItem().imageCollapse?.opacity : this.item.getNodeItem().imageCollapse?.noOpacity);
                                    Image.onTouch((u1) => {
                                        if (u1.type === TouchType.Down) {
                                            this.listNodeDataSource.expandAndCollapseNode(this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId()));
                                            this.listNodeDataSource.setCurrentFocusNodeId(this.item.getNodeCurrentNodeId());
                                        }
                                        u1.stopPropagation();
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
    constructor(t) {
        this.currentNodeId = t.currentNodeId ?? -1;
        this.parentNodeId = t.parentNodeId ?? -1;
        this.isFolder = t.isFolder;
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
    set itemWidth(s) {
        this.width = s;
    }
    get itemWidth() {
        return this.width;
    }
    set itemHeight(r) {
        this.height = r;
    }
    get itemHeight() {
        return this.height;
    }
    set itemRightMargin(q) {
        this.rightMargin = q;
    }
    get itemRightMargin() {
        return this.rightMargin;
    }
}
export class CollapseImageNode extends NodeBaseInfo {
    constructor(p1, b2, n2, r2, q3, g4, h4) {
        super();
        this.rightMargin = {
            'id': -1,
            'type': 10002,
            params: ['sys.float.ohos_id_elements_margin_horizontal_m'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.imageSource = p1;
        this.rightMargin = q3;
        this.imageOpacity = b2;
        this.itemWidth = n2;
        this.itemHeight = r2;
        this.imageCollapseSource = p1;
        this.isImageCollapse = g4;
        this.collapseImageType = h4;
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
    createCollapseImageNodeByType(i1) {
        let j1;
        switch (i1) {
            case CollapseImageType.ARROW_RIGHT_WHITE:
                j1 = ARROW_RIGHT_WITHE;
                break;
            case CollapseImageType.ARROW_RIGHT:
                j1 = ARROW_RIGHT;
                break;
            case CollapseImageType.ARROW_DOWN_WHITE:
                j1 = ARROW_DOWN_WITHE;
                break;
            default:
                j1 = ARROW_DOWN;
        }
        return new CollapseImageNode(j1, {
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
        }, (i1 === CollapseImageType.ARROW_RIGHT_WHITE || i1 === CollapseImageType.ARROW_DOWN_WHITE) ? false : true,
            i1);
    }
}

CollapseImageNodeFactory.instance = new CollapseImageNodeFactory();

class CollapseImageNodeFlyweightFactory {
    static getCollapseImageNodeByType(g1) {
        let h1 = CollapseImageNodeFlyweightFactory.nodeMap.get(g1);
        if (h1 === undefined) {
            h1 = CollapseImageNodeFactory.getInstance().createCollapseImageNodeByType(g1);
            CollapseImageNodeFlyweightFactory.nodeMap.set(g1, h1);
        }
        return h1;
    }
    static getCollapseImageNode(c1, d1, e1) {
        let f1 = e1;
        if (c1 == InteractionStatus.EDIT ||
            c1 === InteractionStatus.DRAG_INSERT) {
            if (d1 === NodeStatus.COLLAPSE) {
                f1 = CollapseImageType.ARROW_RIGHT_WHITE;
            }
            else {
                f1 = CollapseImageType.ARROW_DOWN_WHITE;
            }
        }
        else if (c1 === InteractionStatus.FINISH_EDIT ||
            c1 === InteractionStatus.FINISH_DRAG_INSERT) {
            if (d1 === NodeStatus.COLLAPSE) {
                f1 = CollapseImageType.ARROW_RIGHT;
            }
            else {
                f1 = CollapseImageType.ARROW_DOWN;
            }
        }
        return CollapseImageNodeFlyweightFactory.getCollapseImageNodeByType(f1);
    }
    static changeImageCollapseSource(z, a1) {
        let b1;
        if (!a1) {
            if (z === NodeStatus.COLLAPSE) {
                b1 = CollapseImageType.ARROW_RIGHT_WHITE;
            }
            else {
                b1 = CollapseImageType.ARROW_DOWN_WHITE;
            }
        }
        else {
            if (z === NodeStatus.COLLAPSE) {
                b1 = CollapseImageType.ARROW_RIGHT;
            }
            else {
                b1 = CollapseImageType.ARROW_DOWN;
            }
        }
        return CollapseImageNodeFlyweightFactory.getCollapseImageNodeByType(b1);
    }
}
CollapseImageNodeFlyweightFactory.nodeMap = new Map();

export class ImageNode extends NodeBaseInfo {
    constructor(k, l, m, n, o, p) {
        super();
        this.rightMargin = {
          id: -1,
          type: 10002,
          params: ['sys.float.ohos_id_elements_margin_horizontal_m'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
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
      id: -1,
      type: 10002,
      params: ['sys.float.ohos_id_text_paragraph_margin_xs'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    };
    this.mainTitleSetting = {
      fontColor: this.treeViewTheme.primaryTitleFontColor,
      fontSize: {
        id: -1,
        type: 10002,
        params: ['sys.float.ohos_id_text_size_body1'],
        bundleName: '__harDefaultBundleName__',
        moduleName: '__harDefaultModuleName__',
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
          id: -1,
          type: 10002,
          params: ['sys.float.ohos_id_text_size_body1'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
        fontWeight: FontWeight.Regular,
      };
    } else {
      this.mainTitleSetting = {
        fontColor: this.treeViewTheme.primaryTitleFontColor,
        fontSize: {
          id: -1,
          type: 10002,
          params: ['sys.float.ohos_id_text_size_body1'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
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
          id: -1,
          type: 10002,
          params: ['sys.float.ohos_id_text_size_body1'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
        fontWeight: FontWeight.Regular,
      };
    } else {
      this.mainTitleSetting = {
        fontColor: this.treeViewTheme.primaryTitleFontColor,
        fontSize: {
          id: -1,
          type: 10002,
          params: ['sys.float.ohos_id_text_size_body1'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
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
          id: -1,
          type: 10001,
          params: ['sys.color.ohos_id_color_background'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        };
        this.editItemColor = {
          id: -1,
          type: 10001,
          params: ['sys.color.ohos_id_color_emphasize'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        };
        this.radius = {
          id: -1,
          type: 10002,
          params: ['sys.float.ohos_id_corner_radius_default_xs'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        };
        this.treeViewTheme = TreeViewTheme.getInstance();
        this.itemWidth = ITEM_WIDTH;
        this.itemHeight = ITEM_HEIGHT_INPUT;
        this.rightMargin = {
          id: -1,
          type: 10002,
          params: ['sys.float.ohos_id_text_paragraph_margin_xs'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        };
        this.inputTextSetting = {
          fontColor: this.treeViewTheme.primaryTitleFontColor,
          fontSize: {
            id: -1,
            type: 10002,
            params: ['sys.float.ohos_id_text_size_body1'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
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