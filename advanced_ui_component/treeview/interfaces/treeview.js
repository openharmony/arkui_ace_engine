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

var __decorate = this && this.__decorate || function (e, t, i, o) {
    var s, d = arguments.length, a = d < 3 ? t : null === o ? o = Object.getOwnPropertyDescriptor(t, i) : o;
    if ('object' == typeof Reflect && 'function' == typeof Reflect.decorate) a = Reflect.decorate(e, t, i, o); else for (var r = e.length - 1; r >= 0; r--) (s = e[r]) && (a = (d < 3 ? s(a) : d > 3 ? s(t, i, a) : s(t, i)) || a);
    return d > 3 && a && Object.defineProperty(t, i, a), a
};
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
const DRAG_OPACITY = .4;
const DRAG_OPACITY_NONE = 1;
const FLAG_LINE_HEIGHT = '1.0vp';
const X_OFF_SET = '0vp';
const Y_OFF_SET = '2.75vp';
const Y_BOTTOM_OFF_SET = '-1.25vp';
const Y_BASE_PLATE_OFF_SET = '1.5vp';
const COLOR_SELECT = '#1A0A59F7';
const COLOR_IMAGE_ROW = '#00000000';
const COLOR_IMAGE_EDIT = '#FFFFFF';
const SHADOW_COLOR = '#00001E';
const GRAG_POP_UP_HEIGHT = '48';
const LEFT_PADDING = '8vp';
const RIGHT_PADDING = '8vp';
const FLOOR_MIN_WIDTH = '128vp';
const FLOOR_MAX_WIDTH = '208vp';
const TEXT_MIN_WIDTH = '80vp';
const TEXT_MAX_WIDTH = '160vp';
const MIN_WIDTH = '112vp';
const MAX_WIDTH = '192vp';
const TRANS_COLOR = '#00FFFFFF';
const ARROW_DOWN = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAGAAAABgCAYAAADimHc4AAAAIGNIUk0AAHomAACAhAAA+gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAAEZ0FNQQAAsY58+1GTAAAAAXNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAAlwSFlzAAAOxAAADsQBlSsOGwAAAq9JREFUeNrt2j9rFEEYx/FJziIECwsLCwsJIVhYiISgaIhiioiIlpaCjZ1/qhNUIkHE0negpZggEnwHFgoWFiJicVyRQsQXIHKIvyGzIJKbmTW7M7P6/cCvyR3c7fPsPLO7F2MAAAAAAAAAAAAAAAAAAAAAAAAAAF01keAz9ihrymVln/JEua18L7w2V5TrykHltXJTGTb9Ib0EB/JYueWKP6Ucd3mh/Ci0+Hfc9z6gTCuHlUvK06ZPnMkEB3Nth78tK89dQ0os/toOfz+kHG36w1I0YNwZs6JsFtaEccVvTYoGrHteW3ajaKoDxbfz/10X94BXyoIyO+b1Wbcn2JE0ylT8VeW+5/UtZUn52sUG/FQ23PycG/OeGWXevW+U4cwPFf+MMmjjw3uJDnLkRo2vCTlWQl954Hn9i3Je+djWF+glPNNimlCthJcJLlH7buZPemb+ovKpzS/RS7zcqybMB/aEhZZXwmqg+NXMH7ZdkNQNqJrwLLAxz7Q4jkIzf5iq+LkaUGdjbroJoUvNb674g1SFyNWAOntCU48tYq7zzyqfUxYhZwPqNOHYLi9RQ8XfylH8EhpQZ2P+23EUU/zFlGOntAbU2Zjr3qyF7nCrsTPIdeClNCB2Y66zEvoRG26WsVNqA+rerPlWwg3lYeAmayl38UtsQBOPLezMfxRxkzUo4WBLbEDsxmxXwinlrRsn+5W7yr1SbrJiTJiy2d+T7Y82K4H32QbsNf7fFeyDtRMlFb/kFVBnY7amXbN8l5oXTYtPNf/VBsTuCSZQfPs8/0OJB9eFBuymCXbsnCxlw+1yA2I35j+Lf860/Dz/f2rA73fMdhUc8bzvjXKhxJnftasgH3sJelU5bbb/Z8ee8e/N9j9PrZt8P/ADAAAAAAAAAAAAAAAAAAAAAAAgpV9KuZwVm6MIDQAAAABJRU5ErkJggg==';
const ARROW_DOWN_WITHE = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAAAIGNIUk0AAHomAACAhAAA+gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAAEZ0FNQQAAsY58+1GTAAAAAXNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAAlwSFlzAAAOxAAADsQBlSsOGwAAAKVJREFUeNpjYBgFo2AU0Bww4pL4////diC1hZGRcSo+A4DqWIDUZCB+AVTbiC7PhEfvByCeAjQgn4Dhy4E4BYgvYFODz4JYIF4DxBOwWYJkeAAQRwBdvxGbIcy4TG9sbPzX0NCwHsjUAuIiIPsDUOwkDsPXkhwHWFwaAsQlQAwyrJsYw4myAIslIPCHGMPxBhGO4PoGxF+AOA9o+NbRTDgKRgFxAAAzj0Grm3RjyAAAAABJRU5ErkJggg==';
const ARROW_RIGHT = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAGAAAABgCAYAAADimHc4AAAAIGNIUk0AAHomAACAhAAA+gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAAEZ0FNQQAAsY58+1GTAAAAAXNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAAlwSFlzAAAOxAAADsQBlSsOGwAAAjVJREFUeNrtnCtvG1EQRq+9BlVUEBAYYFBgYGBYaBBoFUVVfkCtyqDAIL8jtI8EBruVIgU4UvMD0iKDPmirtlJglJZUyqzsSFXlxwZsPPPtOdJHbDKac+/cXXvtlAAAAAAAAAAAAAAAAAAAAAAUyZzW1bMMLbuWv5YvqgJqTps/sjT+eW1geckOuB+OLdtzpHy3fFQTUHdY06MFr7+xPGMHlE93iYQnajvBo4APlj3LRhUkeBRwaRnProDkJXi9DP1ZFQmZ49oqISFzXl9RCb8sFwhYn4Sw9wlZkDplx1EWqFZJCVmwHSsnIZoAuYM5ogCpgzmqAJlxFFmAxDiKLiD8OFIQEHocqQgIK0FJwF0kfLZMELA+CTuWI8s1AtYj4YHlt+UcAeVK+JqmX2/OY9Pyat1F1pM2J2n6Fec8mh4KVBdwO27m8RAB5dNb0uhPCCiXTpo+zLWItwgoj/bsKmhrwft/PBzAOQ3RlT9a0vycF5ZvHoqtCTZ/vKL5fcuhl4KVRlA7WvOVBOQP875f0fyBt+arnAH52DmNtvJVzoBwM19pBBVp/r7n5kceQa0CYyfE78pqoiu/733lRxUg1fxoZ0BbrfmRzoAiHy+Ea36UEdRRXPlRRlCR5g+iNt/7CGoqr3zvAuRXvucR1CrQ/GES+fMOjzvgQH3seN8B3ao036uASVWan+Pxybgflqf/LY78wH2dBPF6I/bY8txyZXlnOUsAAAAAAAAAAAAAAAAAAAAAEIgb8WKMjSFbuAQAAAAASUVORK5CYII=';
const ARROW_RIGHT_WITHE = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAAAIGNIUk0AAHomAACAhAAA+gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAAEZ0FNQQAAsY58+1GTAAAAAXNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAAlwSFlzAAAOxAAADsQBlSsOGwAAAKFJREFUeNpjYBgFowAE/v//bwHEPOToZSJS3XIg3k6OJcRaUALEFuRYwkyMosbGxusNDQ3XgMwCIHYAslcDxX5RzQJKLGEmxbvkWMJEaqQxMjKuBVI5QGwDxOnUimR08AFK81DdAmAqArl8DhDfAOKpVLUAavh2IH4CxI7A4HpDMEgpMPwFUXFGS8NJCaL55BgOAixEqqsB4oOkGj4KRggAAN4STB9zyhGzAAAAAElFTkSuQmCC';
var Event;
!function(e){
    e[e.TOUCH_DOWN=0] = 'TOUCH_DOWN';
    e[e.TOUCH_UP=1] = 'TOUCH_UP';
    e[e.HOVER=3] = 'HOVER';
    e[e.HOVER_OVER=4] = 'HOVER_OVER';
    e[e.FOCUS=5] = 'FOCUS';
    e[e.BLUR=6] = 'BLUR';
    e[e.MOUSE_BUTTON_RIGHT=7] = 'MOUSE_BUTTON_RIGHT';
    e[e.DRAG=8] = 'DRAG'
}(Event || (Event = {}));
var MenuOperation;
!function(e){
    e[e.ADD_NODE=0] = 'ADD_NODE';
    e[e.REMOVE_NODE=1] = 'REMOVE_NODE';
    e[e.MODIFY_NODE=2] = 'MODIFY_NODE';
    e[e.COMMIT_NODE=3] = 'COMMIT_NODE'
}(MenuOperation || (MenuOperation = {}));
var PopUpType;
!function(e){
    e[e.HINTS=0] = 'HINTS';
    e[e.WARNINGS=1] = 'WARNINGS'
}(PopUpType || (PopUpType = {}));
var InputError;
!function(e){
    e[e.INVALID_ERROR=0] = 'INVALID_ERROR';
    e[e.LENGTH_ERROR=1] = 'LENGTH_ERROR';
    e[e.NONE=2] = 'NONE'
}(InputError || (InputError = {}));
var Flag;
!function(e){
    e[e.DOWN_FLAG=0] = 'DOWN_FLAG';
    e[e.UP_FLAG=1] = 'UP_FLAG';
    e[e.NONE=2] = 'NONE'
}(Flag || (Flag = {}));

export var NodeStatus;
!function(e){
    e[e.Expand=0] = 'Expand';
    e[e.Collapse=1] = 'Collapse'
}(NodeStatus || (NodeStatus = {}));

export var InteractionStatus;
!function(e){
    e[e.Normal=0] = 'Normal';
    e[e.Selected=1] = 'Selected';
    e[e.Edit=2] = 'Edit';
    e[e.FinishEdit=3] = 'FinishEdit';
    e[e.DragInsert=4] = 'DragInsert';
    e[e.FinishDragInsert=5] = 'FinishDragInsert'
}(InteractionStatus || (InteractionStatus = {}));
let emptyNodeInfo = {
    isFolder: !0,
    icon: '',
    selectedIcon: '',
    editIcon: '',
    container: () => {
    },
    secondaryTitle: '',
    primaryTitle: '',
    parentNodeId: -1,
    currentNodeId: -1
};
let NodeInfo = class {
    constructor(e) {
        this.imageSource = '';
        this.fontColor = '';
        this.borderWidth = { has: 2, none: 0 };
        this.canShowFlagLine = !1;
        this.isOverBorder = !1;
        this.canShowBottomFlagLine = !1;
        this.isHighLight = !1;
        this.isModify = !1;
        this.childNodeInfo = e.getChildNodeInfo();
        this.nodeItem = {
            imageNode: void 0,
            inputText: new InputText,
            mainTitleNode: e.getNodeItem().mainTitleNode,
            imageCollapse: void 0,
            fontColor: void 0
        };
        this.popUpInfo = {
            popUpIsShow: !1,
            popUpEnableArrow: !1,
            popUpColor: void 0,
            popUpText: '',
            popUpTextColor: void 0
        };
        this.nodeItem.imageNode = e.getNodeItem().imageNode;
        this.nodeItem.imageCollapse = e.getNodeItem().imageCollapse;
        this.container = e.container;
        this.parentNodeId = e.parentNodeId;
        this.currentNodeId = e.currentNodeId;
        this.nodeHeight = 48;
        this.nodeLevel = e.nodeLevel;
        this.nodeLeftPadding = 12 * e.nodeLevel + 8;
        this.nodeColor = {
            id: -1,
            type: 10001,
            params: ['sys.color.ohos_id_color_background'],
            bundleName: '',
            moduleName: ''
        };
        this.nodeIsShow = !(this.nodeLevel > 0);
        this.listItemHeight = this.nodeLevel > 0 ? 0 : 48;
        this.isShowTitle = !0;
        this.isShowInputText = !1;
        this.isSelected = !1;
        this.status = {
            normal: {
                id: -1,
                type: 10001,
                params: ['sys.color.ohos_id_color_background_transparent'],
                bundleName: '',
                moduleName: ''
            },
            hover: {
                id: -1,
                type: 10001,
                params: ['sys.color.ohos_id_color_hover'],
                bundleName: '',
                moduleName: ''
            },
            press: {
                id: -1,
                type: 10001,
                params: ['sys.color.ohos_id_color_click_effect'],
                bundleName: '',
                moduleName: ''
            },
            selected: '#1A0A59F7',
            highLight: {
                id: -1,
                type: 10001,
                params: ['sys.color.ohos_id_color_activated'],
                bundleName: '',
                moduleName: ''
            }
        };
        this.nodeBorder = {
            borderWidth: 0,
            borderColor: {
                id: -1,
                type: 10001,
                params: ['sys.color.ohos_id_color_focused_outline'],
                bundleName: '',
                moduleName: ''
            },
            borderRadius: {
                id: -1,
                type: 10002,
                params: ['sys.float.ohos_id_corner_radius_clicked'],
                bundleName: '',
                moduleName: ''
            }
        };
        this.flagLineLeftMargin = 12 * e.nodeLevel + 8;
        this.node = e;
        this.nodeParam = e.data
    }

    setFontColor(e) {
        this.fontColor = e
    }

    getFontColor() {
        return this.fontColor
    }

    getPopUpInfo() {
        return this.popUpInfo
    }

    setPopUpIsShow(e) {
        this.popUpInfo.popUpIsShow = e
    }

    setPopUpEnableArrow(e) {
        this.popUpInfo.popUpEnableArrow = e
    }

    setPopUpColor(e) {
        this.popUpInfo.popUpColor = e
    }

    setPopUpText(e) {
        this.popUpInfo.popUpText = e
    }

    setPopUpTextColor(e) {
        this.popUpInfo.popUpTextColor = e
    }

    getIsShowTitle() {
        return this.isShowTitle
    }

    getIsShowInputText() {
        return this.isShowInputText
    }

    setTitleAndInputTextStatus(e) {
        if (e) {
            this.isShowTitle = !1;
            this.isShowInputText = !0
        } else {
            this.isShowTitle = !0;
            this.isShowInputText = !1
        }
    }

    handleImageCollapseAfterAddNode(e) {
        if (e) {
            this.nodeItem.imageCollapse = new ImageNode(ARROW_DOWN, {
                id: -1,
                type: 10002,
                params: ['sys.float.ohos_id_alpha_content_tertiary'],
                bundleName: '',
                moduleName: ''
            }, 24, 24, void 0, void 0);
            this.nodeItem.imageCollapse.itemRightMargin = {
                id: -1,
                type: 10002,
                params: ['sys.float.ohos_id_text_paragraph_margin_xs'],
                bundleName: '',
                moduleName: ''
            }
        } else this.nodeItem.imageCollapse = void 0
    }

    setNodeColor(e) {
        void 0 !== e && (this.nodeColor = e)
    }

    getNodeColor() {
        return this.nodeColor
    }

    setListItemHeight(e) {
        this.listItemHeight = e
    }

    getListItemHeight() {
        return this.listItemHeight
    }

    getNodeCurrentNodeId() {
        return this.currentNodeId
    }

    getNodeParentNodeId() {
        return this.parentNodeId
    }

    getNodeLeftPadding() {
        return this.nodeLeftPadding
    }

    getNodeHeight() {
        return this.nodeHeight
    }

    setNodeIsShow(e) {
        this.nodeIsShow = e
    }

    getNodeIsShow() {
        return this.nodeIsShow
    }

    getNodeItem() {
        return this.nodeItem
    }

    getNodeStatus() {
        return this.status
    }

    getNodeBorder() {
        return this.nodeBorder
    }

    setNodeBorder(e) {
        this.nodeBorder.borderWidth = e ? this.borderWidth.has : this.borderWidth.none
    }

    getChildNodeInfo() {
        return this.childNodeInfo
    }

    getCurrentNodeId() {
        return this.currentNodeId
    }

    getMenu() {
        return this.container
    }

    setIsSelected(e) {
        this.isSelected = e
    }

    getIsSelected() {
        return this.isSelected
    }

    getNodeInfoData() {
        return this.nodeParam
    }

    getNodeInfoNode() {
        return this.node
    }

    getIsFolder() {
        return this.nodeParam.isFolder
    }

    setCanShowFlagLine(e) {
        this.canShowFlagLine = e
    }

    getCanShowFlagLine() {
        return this.canShowFlagLine
    }

    setFlagLineLeftMargin(e) {
        void 0 !== e && (this.flagLineLeftMargin = 12 * e + 8)
    }

    getFlagLineLeftMargin() {
        return this.flagLineLeftMargin
    }

    getNodeLevel() {
        return this.nodeLevel
    }

    setIsOverBorder(e) {
        this.isOverBorder = e
    }

    getIsOverBorder() {
        return this.isOverBorder
    }

    setCanShowBottomFlagLine(e) {
        this.canShowBottomFlagLine = e
    }

    getCanShowBottomFlagLine() {
        return this.canShowBottomFlagLine
    }

    setIsHighLight(e) {
        this.isHighLight = e
    }

    getIsHighLight() {
        return this.isHighLight
    }

    setIsModify(e) {
        this.isModify = e
    }

    getIsModify() {
        return this.isModify
    }
};
NodeInfo = __decorate([Observed], NodeInfo);

export { NodeInfo };

export var TreeListenType;
!function(e){
    e.NODE_CLICK = 'NodeClick';
    e.NODE_ADD = 'NodeAdd';
    e.NODE_DELETE = 'NodeDelete';
    e.NODE_MODIFY = 'NodeModify';
    e.NODE_MOVE = 'NodeMove'
}(TreeListenType || (TreeListenType = {}));

export class TreeListener {
    constructor() {
        this._events = [];
        this._once_events = []
    }

    on(e, t) {
        if (Array.isArray(e)) for (let i = 0,
            o = e.length; i < o; i++) this.on(e[i], t); else (this._events[e] || (this._events[e] = [])).push(t)
    }

    once(e, t) {
        Array.isArray(e) ? this.off(e, t) : (this._once_events[e] || (this._once_events[e] = [])).push(t)
    }

    off(e, t) {
        null === e && (this._events = []);
        if (Array.isArray(e)) for (let i = 0, o = e.length; i < o; i++) this.off(e[i], t);
        let i = this._events[e];
        if (!i) return;
        null === t && (this._events[e] = null);
        let o = i.length;
        for (; o--; ) {
            if (i[o] === t) {
                i.splice(o, 1);
                break
            }
        }
    }

    emit(e, t) {
        if (this._once_events[e]) {
            let i = Array.from(this._once_events[e]);
            if (i) {
                for (let e = 0, o = i.length; e < o; e++) try {
                    i[e](t)
                } catch (e) {
                    new Error(e)
                }
                this._once_events[e] = null
            }
        } else if (this._events[e]) {
            let i = Array.from(this._events[e]);
            if (i) for (let e = 0, o = i.length; e < o; e++) try {
                i[e](t)
            } catch (e) {
                new Error(e)
            }
        }
    }
}

export class TreeListenerManager {
    constructor() {
        this.appEventBus = new TreeListener
    }

    static getInstance() {
        void 0 === AppStorage.Get('app_key_event_bus') && AppStorage.SetOrCreate('app_key_event_bus', new TreeListenerManager);
        return AppStorage.Get('app_key_event_bus')
    }

    getTreeListener() {
        return this.appEventBus
    }
}
TreeListenerManager.APP_KEY_EVENT_BUS = 'app_key_event_bus';

export class TreeView extends ViewPU {
    constructor(e, t, i, o = -1) {
        super(e, i, o);
        this.treeController = new TreeController;
        this.__nodeList = new ObservedPropertyObjectPU([], this, 'nodeList');
        this.listNodeDataSource = new ListNodeDataSource;
        this.__item = new ObservedPropertyObjectPU(null, this, 'item');
        this.__touchCount = new ObservedPropertySimplePU(0, this, 'touchCount');
        this.__dropSelectedIndex = new ObservedPropertySimplePU(0, this, 'dropSelectedIndex');
        this.__viewLastIndex = new ObservedPropertySimplePU(-1, this, 'viewLastIndex');
        this.__listItemBgColor = new ObservedPropertyObjectPU({
            id: -1,
            type: 10001,
            params: ['sys.color.ohos_id_color_background_transparent'],
            bundleName: '',
            moduleName: ''
        }, this, 'listItemBgColor');
        this.listTreeViewMenu = this.NullBuilder;
        this.MAX_CN_LENGTH = 254;
        this.MAX_EN_LENGTH = 255;
        this.INITIAL_INVALID_VALUE = -1;
        this.MAX_TOUCH_DOWN_COUNT = 0;
        this.isMultiPress = !1;
        this.touchDownCount = this.INITIAL_INVALID_VALUE;
        this.appEventBus = TreeListenerManager.getInstance().getTreeListener();
        this.itemPadding = {
            left: {
                id: -1,
                type: 10002,
                params: ['sys.float.ohos_id_card_margin_start'],
                bundleName: '',
                moduleName: ''
            },
            right: {
                id: -1,
                type: 10002,
                params: ['sys.float.ohos_id_card_margin_end'],
                bundleName: '',
                moduleName: ''
            },
            top: {
                id: -1,
                type: 10002,
                params: ['sys.float.ohos_id_text_margin_vertical'],
                bundleName: '',
                moduleName: ''
            },
            bottom: {
                id: -1,
                type: 10002,
                params: ['sys.float.ohos_id_text_margin_vertical'],
                bundleName: '',
                moduleName: ''
            }
        };
        this.textInputPadding = { left: '0vp', right: '0vp', top: '0vp', bottom: '0vp' };
        this.setInitiallyProvidedValue(t)
    }

    setInitiallyProvidedValue(e) {
        void 0 !== e.treeController && (this.treeController = e.treeController);
        void 0 !== e.nodeList && (this.nodeList = e.nodeList);
        void 0 !== e.listNodeDataSource && (this.listNodeDataSource = e.listNodeDataSource);
        void 0 !== e.item && (this.item = e.item);
        void 0 !== e.touchCount && (this.touchCount = e.touchCount);
        void 0 !== e.dropSelectedIndex && (this.dropSelectedIndex = e.dropSelectedIndex);
        void 0 !== e.viewLastIndex && (this.viewLastIndex = e.viewLastIndex);
        void 0 !== e.listItemBgColor && (this.listItemBgColor = e.listItemBgColor);
        void 0 !== e.listTreeViewMenu && (this.listTreeViewMenu = e.listTreeViewMenu);
        void 0 !== e.MAX_CN_LENGTH && (this.MAX_CN_LENGTH = e.MAX_CN_LENGTH);
        void 0 !== e.MAX_EN_LENGTH && (this.MAX_EN_LENGTH = e.MAX_EN_LENGTH);
        void 0 !== e.INITIAL_INVALID_VALUE && (this.INITIAL_INVALID_VALUE = e.INITIAL_INVALID_VALUE);
        void 0 !== e.MAX_TOUCH_DOWN_COUNT && (this.MAX_TOUCH_DOWN_COUNT = e.MAX_TOUCH_DOWN_COUNT);
        void 0 !== e.isMultiPress && (this.isMultiPress = e.isMultiPress);
        void 0 !== e.touchDownCount && (this.touchDownCount = e.touchDownCount);
        void 0 !== e.appEventBus && (this.appEventBus = e.appEventBus);
        void 0 !== e.itemPadding && (this.itemPadding = e.itemPadding);
        void 0 !== e.textInputPadding && (this.textInputPadding = e.textInputPadding)
    }

    updateStateVars(e) {
    }

    purgeVariableDependenciesOnElmtId(e) {
        this.__nodeList.purgeDependencyOnElmtId(e);
        this.__item.purgeDependencyOnElmtId(e);
        this.__touchCount.purgeDependencyOnElmtId(e);
        this.__dropSelectedIndex.purgeDependencyOnElmtId(e);
        this.__viewLastIndex.purgeDependencyOnElmtId(e);
        this.__listItemBgColor.purgeDependencyOnElmtId(e)
    }

    aboutToBeDeleted() {
        this.__nodeList.aboutToBeDeleted();
        this.__item.aboutToBeDeleted();
        this.__touchCount.aboutToBeDeleted();
        this.__dropSelectedIndex.aboutToBeDeleted();
        this.__viewLastIndex.aboutToBeDeleted();
        this.__listItemBgColor.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal()
    }

    get nodeList() {
        return this.__nodeList.get()
    }

    set nodeList(e) {
        this.__nodeList.set(e)
    }

    get item() {
        return this.__item.get()
    }

    set item(e) {
        this.__item.set(e)
    }

    get touchCount() {
        return this.__touchCount.get()
    }

    set touchCount(e) {
        this.__touchCount.set(e)
    }

    get dropSelectedIndex() {
        return this.__dropSelectedIndex.get()
    }

    set dropSelectedIndex(e) {
        this.__dropSelectedIndex.set(e)
    }

    get viewLastIndex() {
        return this.__viewLastIndex.get()
    }

    set viewLastIndex(e) {
        this.__viewLastIndex.set(e)
    }

    get listItemBgColor() {
        return this.__listItemBgColor.get()
    }

    set listItemBgColor(e) {
        this.__listItemBgColor.set(e)
    }

    NullBuilder(e = null) {
    }

    aboutToAppear() {
        if (null !== this.treeController) {
            this.listNodeDataSource = this.treeController.getListNodeDataSource();
            this.nodeList = this.treeController.getListNodeDataSource().listNode;
            this.item = this.treeController.getListNodeDataSource().listNode
        }
    }

    popupForShowTitle(e, t, i, o = null) {
        this.observeComponentCreation(((e, i) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            Row.create();
            Row.backgroundColor(t);
            Row.border({
                radius: {
                    id: -1,
                    type: 10002,
                    params: ['sys.float.ohos_id_elements_margin_horizontal_l'],
                    bundleName: '',
                    moduleName: ''
                }
            });
            Row.padding({
                left: {
                    id: -1,
                    type: 10002,
                    params: ['sys.float.ohos_id_elements_margin_horizontal_l'],
                    bundleName: '',
                    moduleName: ''
                },
                right: {
                    id: -1,
                    type: 10002,
                    params: ['sys.float.ohos_id_elements_margin_horizontal_l'],
                    bundleName: '',
                    moduleName: ''
                },
                top: {
                    id: -1,
                    type: 10002,
                    params: ['sys.float.ohos_id_card_margin_middle'],
                    bundleName: '',
                    moduleName: ''
                },
                bottom: {
                    id: -1,
                    type: 10002,
                    params: ['sys.float.ohos_id_card_margin_middle'],
                    bundleName: '',
                    moduleName: ''
                }
            });
            i || Row.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((t, o) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            Text.create(e);
            Text.fontSize({
                id: -1,
                type: 10002,
                params: ['sys.float.ohos_id_text_size_body2'],
                bundleName: '',
                moduleName: ''
            });
            Text.fontWeight('regular');
            Text.fontColor(i);
            o || Text.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        Text.pop();
        Row.pop()
    }

    builder(e = null) {
        this.listTreeViewMenu.bind(this)()
    }

    draggingPopup(e, t = null) {
        this.observeComponentCreation(((e, t) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            Row.create();
            Row.constraintSize({
                minWidth: this.listNodeDataSource.getDragPopupPara().floorConstraintSize.minWidth,
                maxWidth: this.listNodeDataSource.getDragPopupPara().floorConstraintSize.maxWidth
            });
            Row.height(this.listNodeDataSource.getDragPopupPara().height);
            Row.backgroundColor(this.listNodeDataSource.getDragPopupPara().backgroundColor);
            Row.padding({
                left: this.listNodeDataSource.getDragPopupPara().padding.left,
                right: this.listNodeDataSource.getDragPopupPara().padding.right
            });
            Row.shadow({
                radius: {
                    id: -1,
                    type: 10002,
                    params: ['sys.float.ohos_id_corner_radius_default_m'],
                    bundleName: '',
                    moduleName: ''
                },
                color: '#00001E',
                offsetY: 0
            });
            Row.borderRadius(this.listNodeDataSource.getDragPopupPara().borderRadius);
            t || Row.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((t, i) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            If.create();
            e.getNodeItem().imageNode ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation(((t, i) => {
                    var o, s, d;
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Row.create();
                    Row.backgroundColor('#00000000');
                    Row.margin({
                        right: null === (o = e.getNodeItem().imageNode) || void 0 === o ? void 0 : o.itemRightMargin
                    });
                    Row.height(null === (s = e.getNodeItem().imageNode) || void 0 === s ? void 0 : s.itemHeight);
                    Row.width(null === (d = e.getNodeItem().imageNode) || void 0 === d ? void 0 : d.itemWidth);
                    i || Row.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, i) => {
                    var o, s, d;
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Image.create(null === (o = e.getNodeItem().imageNode) || void 0 === o ? void 0 : o.normalSource);
                    Image.objectFit(ImageFit.Contain);
                    Image.height(null === (s = e.getNodeItem().imageNode) || void 0 === s ? void 0 : s.itemHeight);
                    Image.width(null === (d = e.getNodeItem().imageNode) || void 0 === d ? void 0 : d.itemWidth);
                    Image.opacity(this.listNodeDataSource.getDragPopupPara().imageOpacity);
                    i || Image.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                Row.pop()
            })) : If.branchId(1);
            i || If.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        If.pop();
        this.observeComponentCreation(((t, i) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            Row.create();
            Row.constraintSize({
                minWidth: e.getNodeItem().imageNode ? this.listNodeDataSource.getDragPopupPara().textConstraintSize.minWidth1 : this.listNodeDataSource.getDragPopupPara().textConstraintSize.minWidth2,
                maxWidth: e.getNodeItem().imageNode ? this.listNodeDataSource.getDragPopupPara().textConstraintSize.maxWidth1 : this.listNodeDataSource.getDragPopupPara().textConstraintSize.maxWidth2
            });
            i || Row.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((t, i) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            If.create();
            e.getNodeItem().mainTitleNode && e.getIsShowTitle() ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation(((t, i) => {
                    var o, s;
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Text.create(null === (o = e.getNodeItem().mainTitleNode) || void 0 === o ? void 0 : o.title);
                    Text.maxLines(1);
                    Text.fontSize(null === (s = e.getNodeItem().mainTitleNode) || void 0 === s ? void 0 : s.size);
                    Text.fontColor(this.listNodeDataSource.getDragPopupPara().fontColor);
                    Text.fontWeight(this.listNodeDataSource.getDragPopupPara().fontWeight);
                    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                    i || Text.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                Text.pop()
            })) : If.branchId(1);
            i || If.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        If.pop();
        Row.pop();
        Row.pop()
    }

    clearLastIndexColor() {
        if (!(-1 === this.viewLastIndex || this.viewLastIndex >= this.nodeList.length)) {
            this.setImageSources(this.viewLastIndex, InteractionStatus.Normal);
            this.nodeList[this.viewLastIndex].setNodeColor({
                id: -1,
                type: 10001,
                params: ['sys.color.ohos_id_color_background_transparent'],
                bundleName: '',
                moduleName: ''
            });
            this.nodeList[this.viewLastIndex].fontColor = {
                id: -1,
                type: 10001,
                params: ['sys.color.ohos_id_color_primary'],
                bundleName: '',
                moduleName: ''
            };
            this.listNodeDataSource.listNode[this.viewLastIndex].setNodeColor({
                id: -1,
                type: 10001,
                params: ['sys.color.ohos_id_color_background_transparent'],
                bundleName: '',
                moduleName: ''
            });
            this.listNodeDataSource.listNode[this.viewLastIndex].fontColor = {
                id: -1,
                type: 10001,
                params: ['sys.color.ohos_id_color_primary'],
                bundleName: '',
                moduleName: ''
            };
            this.listNodeDataSource.listNode[this.viewLastIndex].setIsSelected(!1);
            this.listNodeDataSource.setImageSource(this.viewLastIndex, InteractionStatus.Normal)
        }
    }

    setImageSources(e, t) {
        var i, o;
        let s = this.nodeList[e];
        s.setIsSelected(t === InteractionStatus.Selected || t === InteractionStatus.Edit || t === InteractionStatus.FinishEdit);
        null !== s.getNodeItem().mainTitleNode && t !== InteractionStatus.DragInsert && t !== InteractionStatus.FinishDragInsert && (null === (i = s.getNodeItem().mainTitleNode) || void 0 === i || i.setMainTitleSelected(t === InteractionStatus.Selected || t === InteractionStatus.FinishEdit));
        null !== s.getNodeItem().imageNode && (null === (o = s.getNodeItem().imageNode) || void 0 === o || o.setImageSource(t))
    }

    initialRender() {
        this.observeComponentCreation(((e, t) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            List.create({});
            List.onDragMove(((e, t) => {
                var i, o;
                if (this.isMultiPress) {
                    console.error('drag error, a item has been dragged');
                    return
                }
                let s = Math.floor(e.getY() / 24) % 2 ? Flag.DOWN_FLAG : Flag.UP_FLAG;
                let d = JSON.parse(t).insertIndex;
                let a = !1;
                if (d >= this.listNodeDataSource.totalCount()) {
                    s = Flag.DOWN_FLAG;
                    d = this.listNodeDataSource.totalCount() - 1;
                    null === (i = this.listNodeDataSource.getData(d)) || void 0 === i || i.setIsOverBorder(!0);
                    a = !0
                } else null === (o = this.listNodeDataSource.getData(d)) || void 0 === o || o.setIsOverBorder(!1);
                let r = this.listNodeDataSource.getData(d);
                let n = null == r ? void 0 : r.getCurrentNodeId();
                if (d !== this.listNodeDataSource.getLastPassIndex() && this.listNodeDataSource.getIsInnerDrag()) {
                    if (this.listNodeDataSource.getIsParentOfInsertNode(n)) {
                        this.listNodeDataSource.setPassIndex(d);
                        void 0 !== n && this.listNodeDataSource.clearTimeOutAboutDelayHighLightAndExpand(findCurrentNodeIndex(this.listNodeDataSource, n));
                        this.listNodeDataSource.setFlag(Flag.NONE);
                        return
                    }
                }
                this.listNodeDataSource.setLastPassIndex(d);
                this.listNodeDataSource.setVisibility(s, d - 1, a);
                void 0 !== n && n !== this.listNodeDataSource.getDraggingCurrentNodeId() && this.listNodeDataSource.delayHighLightAndExpandNode(findCurrentNodeIndex(this.listNodeDataSource, n), n, d)
            }));
            List.onDragEnter(((e, t) => {
                if (this.listNodeDataSource.getIsInnerDrag()) {
                    this.listNodeDataSource.setIsDrag(!0);
                    let e = .4;
                    this.listNodeDataSource.setListItemOpacity(e)
                }
            }));
            List.onDragLeave(((e, t) => {
                this.listNodeDataSource.hideLastLine();
                this.listNodeDataSource.clearLastTimeoutHighLight();
                this.listNodeDataSource.clearLastTimeoutExpand();
                this.listNodeDataSource.setListItemOpacity(1);
                this.listNodeDataSource.setIsDrag(!1);
                this.listNodeDataSource.notifyDataReload()
            }));
            List.onDrop(((e, t) => {
                var i, o, s, d;
                this.listNodeDataSource.clearLastTimeoutExpand();
                this.listNodeDataSource.setListItemOpacity(1);
                let a = JSON.parse(t).insertIndex;
                let r = this.dropSelectedIndex;
                if (r - 1 > this.listNodeDataSource.totalCount() || void 0 === r) {
                    console.error('drag error, currentNodeIndex is not found');
                    this.listNodeDataSource.setIsDrag(!1);
                    return
                }
                if (a === this.listNodeDataSource.totalCount()) {
                    console.log('need to insert into the position of the last line, now insertNodeIndex = insertNodeIndex - 1');
                    a -= 1
                }
                let n = this.listNodeDataSource.getData(a);
                if (void 0 === n) return;
                let l = n.getNodeCurrentNodeId();
                if (!this.listNodeDataSource.getIsDrag() || !this.listNodeDataSource.getIsInnerDrag()) {
                    this.listNodeDataSource.clearLastTimeoutHighLight();
                    this.listNodeDataSource.setIsInnerDrag(!1);
                    this.listNodeDataSource.hideLastLine();
                    this.listNodeDataSource.initialParameterAboutDelayHighLightAndExpandIndex();
                    this.listNodeDataSource.refreshSubtitle(l);
                    this.listNodeDataSource.notifyDataReload();
                    return
                }
                let h = this.listNodeDataSource.getCurrentNodeInfo();
                let N = n.getNodeParentNodeId();
                let u = this.listNodeDataSource.getDraggingCurrentNodeId();
                let c = this.listNodeDataSource.getDraggingParentNodeId();
                if (this.listNodeDataSource.getIsParentOfInsertNode(l)) {
                    this.listNodeDataSource.clearLastTimeoutHighLight();
                    this.listNodeDataSource.setIsInnerDrag(!1);
                    this.listNodeDataSource.hideLastLine();
                    this.listNodeDataSource.notifyDataChange(a);
                    this.listNodeDataSource.initialParameterAboutDelayHighLightAndExpandIndex();
                    this.listNodeDataSource.setIsDrag(!1);
                    let e = findCurrentNodeIndex(this.listNodeDataSource, u);
                    this.listNodeDataSource.setClickIndex(e);
                    this.listNodeDataSource.handleEvent(Event.DRAG, e);
                    return
                }
                this.listNodeDataSource.getExpandAndCollapseInfo(u) === NodeStatus.Expand && this.listNodeDataSource.expandAndCollapseNode(findCurrentNodeIndex(this.listNodeDataSource, u));
                let I = !1;
                if (this.listNodeDataSource.getExpandAndCollapseInfo(l) === NodeStatus.Collapse) {
                    let e = findCurrentNodeIndex(this.listNodeDataSource, l);
                    this.listNodeDataSource.ListNode[e].getIsHighLight() && this.listNodeDataSource.expandAndCollapseNode(e);
                    I = !0
                }
                this.listNodeDataSource.setLastDelayHighLightId();
                if (null !== h && u !== l) {
                    this.listNodeDataSource.alterDragNode(N, l, c, u, h);
                    this.listNodeDataSource.hideLastLine()
                } else {
                    this.listNodeDataSource.hideLastLine();
                    this.listNodeDataSource.setLastPassId(u);
                    this.listNodeDataSource.hideLastLine()
                }
                let g = findCurrentNodeIndex(this.listNodeDataSource, this.listNodeDataSource.getLastDelayHighLightId());
                this.listNodeDataSource.setLastDelayHighLightIndex(g);
                this.listNodeDataSource.clearLastTimeoutHighLight();
                this.listNodeDataSource.initialParameterAboutDelayHighLightAndExpandIndex();
                this.listNodeDataSource.setIsDrag(!1);
                let p = findCurrentNodeIndex(this.listNodeDataSource, u);
                this.listNodeDataSource.setClickIndex(p);
                this.listNodeDataSource.handleEvent(Event.DRAG, p);
                this.listNodeDataSource.setIsInnerDrag(!1);
                this.listNodeDataSource.notifyDataReload();
                this.listNodeDataSource.listNode[p].fontColor = {
                    id: -1,
                    type: 10001,
                    params: ['sys.color.ohos_id_color_text_primary_activated'],
                    bundleName: '',
                    moduleName: ''
                };
                if (-1 !== this.viewLastIndex && r !== this.viewLastIndex) {
                    null === (i = this.listNodeDataSource.listNode[this.viewLastIndex].getNodeItem().mainTitleNode) || void 0 === i || i.setMainTitleSelected(!1);
                    null === (o = this.listNodeDataSource.listNode[this.viewLastIndex].getNodeItem().mainTitleNode) || void 0 === o || o.setMainTitleHighLight(!1)
                }
                null !== this.listNodeDataSource.listNode[this.viewLastIndex] && (this.listNodeDataSource.listNode[this.viewLastIndex].fontColor = {
                    id: -1,
                    type: 10001,
                    params: ['sys.color.ohos_id_color_text_primary'],
                    bundleName: '',
                    moduleName: ''
                });
                this.listNodeDataSource.lastIndex = this.viewLastIndex;
                if (this.listNodeDataSource.listNode[this.viewLastIndex] && null !== this.listNodeDataSource.listNode[this.viewLastIndex].getNodeItem().imageNode) {
                    null === (s = this.listNodeDataSource.listNode[this.viewLastIndex].getNodeItem().imageNode) || void 0 === s || s.setImageSource(InteractionStatus.Normal);
                    this.listNodeDataSource.listNode[this.viewLastIndex].imageSource = null === (d = this.listNodeDataSource.listNode[this.viewLastIndex].getNodeItem().imageNode) || void 0 === d ? void 0 : d.source
                }
                this.listNodeDataSource.listNode[this.viewLastIndex] && this.listNodeDataSource.listNode[this.viewLastIndex].setNodeColor({
                    id: -1,
                    type: 10001,
                    params: ['sys.color.ohos_id_color_background_transparent'],
                    bundleName: '',
                    moduleName: ''
                });
                this.viewLastIndex = p
            }));
            t || List.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        {
            const e = e => {
                const t = e;
                {
                    const e = void 0 !== globalThis.__lazyForEachItemGenFunction && !0;
                    const i = (i, o) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(i);
                        ListItem.create(d, e);
                        ListItem.width('100%');
                        ListItem.height(t.getListItemHeight());
                        ListItem.padding({ left: this.itemPadding.left, right: this.itemPadding.right });
                        ListItem.align(Alignment.Start);
                        ListItem.onDragStart(((e, i) => {
                            if (this.listNodeDataSource.getIsDrag() || this.listNodeDataSource.getIsInnerDrag() || this.isMultiPress) {
                                console.error('drag error, a item has been dragged');
                                return
                            }
                            this.dropSelectedIndex = JSON.parse(i).selectedIndex;
                            let o = JSON.parse(i).selectedIndex;
                            let s = this.listNodeDataSource.getData(o);
                            let d = t.getNodeCurrentNodeId();
                            if (o >= this.listNodeDataSource.totalCount() || void 0 === o) {
                                console.error('drag error, currentNodeIndex is not found in onDragStart');
                                return
                            }
                            this.listNodeDataSource.setIsInnerDrag(!0);
                            this.listNodeDataSource.setIsDrag(!0);
                            this.listNodeDataSource.setCurrentNodeInfo(s);
                            this.listNodeDataSource.setDraggingCurrentNodeId(null == s ? void 0 : s.getNodeCurrentNodeId());
                            this.listNodeDataSource.setDraggingParentNodeId(null == s ? void 0 : s.getNodeParentNodeId());
                            this.listNodeDataSource.setListItemOpacity(.4);
                            this.listNodeDataSource.notifyDataChange(o);
                            if (d === (null == s ? void 0 : s.getNodeCurrentNodeId())) return { builder: () => {
                                this.draggingPopup.call(this, s)
                            } };
                            console.error('drag is too fast,it attribute a fault to OH');
                            this.listNodeDataSource.setIsDrag(!1)
                        }));
                        o || ListItem.pop();
                        ViewStackProcessor.StopGetAccessRecording()
                    };
                    const o = () => {
                        this.observeComponentCreation(i);
                        ListItem.pop()
                    };
                    const s = () => {
                        this.observeComponentCreation(i);
                        this.observeComponentCreation(((e, i) => {
                            ViewStackProcessor.StartGetAccessRecordingFor(e);
                            Row.create();
                            Row.onTouch((e => {
                                var i;
                                this.viewLastIndex = this.listNodeDataSource.getLastIndex();
                                let o = this.listNodeDataSource.findIndex(t.getNodeCurrentNodeId());
                                if (e.type === TouchType.Down && o !== this.viewLastIndex) {
                                    this.clearLastIndexColor();
                                    this.listNodeDataSource.lastIndex = o;
                                    this.listNodeDataSource.setClickIndex(o)
                                }
                                if (e.type === TouchType.Up) {
                                    this.listNodeDataSource.listNode[o].setIsSelected(!0);
                                    this.listNodeDataSource.setImageSource(o, InteractionStatus.Selected);
                                    null !== this.listNodeDataSource.listNode[o].getNodeItem().imageNode && (this.listNodeDataSource.listNode[o].imageSource = null === (i = this.listNodeDataSource.listNode[o].getNodeItem().imageNode) || void 0 === i ? void 0 : i.source);
                                    if (o !== this.viewLastIndex) {
                                        this.clearLastIndexColor();
                                        this.listNodeDataSource.lastIndex = o;
                                        this.listNodeDataSource.setClickIndex(o)
                                    }
                                    this.viewLastIndex = o
                                }
                                if (-1 !== this.listNodeDataSource.getLastIndex() && o !== this.listNodeDataSource.getLastIndex()) {
                                    this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE,!1, this.listNodeDataSource.getLastIndex());
                                    this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(), MenuOperation.COMMIT_NODE)
                                }
                            }));
                            i || Row.pop();
                            ViewStackProcessor.StopGetAccessRecording()
                        }));
                        this.observeComponentCreation(((e, i) => {
                            ViewStackProcessor.StartGetAccessRecordingFor(e);
                            i ? ViewPU.create(new TreeViewInner(this, {
                                item: t,
                                listNodeDataSource: this.listNodeDataSource,
                                index: this.listNodeDataSource.findIndex(t.getNodeCurrentNodeId()),
                                listTreeViewMenu: this.listTreeViewMenu
                            }, void 0, e)) : this.updateStateVarsOfChildByElmtId(e, { item: t });
                            ViewStackProcessor.StopGetAccessRecording()
                        }));
                        Row.pop();
                        ListItem.pop()
                    };
                    const d = (e, o) => {
                        i(e, o);
                        this.updateFuncByElmtId.set(e, i);
                        this.observeComponentCreation(((e, i) => {
                            ViewStackProcessor.StartGetAccessRecordingFor(e);
                            Row.create();
                            Row.onTouch((e => {
                                var i;
                                this.viewLastIndex = this.listNodeDataSource.getLastIndex();
                                let o = this.listNodeDataSource.findIndex(t.getNodeCurrentNodeId());
                                if (e.type === TouchType.Down && o !== this.viewLastIndex) {
                                    this.clearLastIndexColor();
                                    this.listNodeDataSource.lastIndex = o;
                                    this.listNodeDataSource.setClickIndex(o)
                                }
                                if (e.type === TouchType.Up) {
                                    this.listNodeDataSource.listNode[o].setIsSelected(!0);
                                    this.listNodeDataSource.setImageSource(o, InteractionStatus.Selected);
                                    null !== this.listNodeDataSource.listNode[o].getNodeItem().imageNode && (this.listNodeDataSource.listNode[o].imageSource = null === (i = this.listNodeDataSource.listNode[o].getNodeItem().imageNode) || void 0 === i ? void 0 : i.source);
                                    if (o !== this.viewLastIndex) {
                                        this.clearLastIndexColor();
                                        this.listNodeDataSource.lastIndex = o;
                                        this.listNodeDataSource.setClickIndex(o)
                                    }
                                    this.viewLastIndex = o
                                }
                                if (-1 !== this.listNodeDataSource.getLastIndex() && o !== this.listNodeDataSource.getLastIndex()) {
                                    this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE,!1, this.listNodeDataSource.getLastIndex());
                                    this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(), MenuOperation.COMMIT_NODE)
                                }
                            }));
                            i || Row.pop();
                            ViewStackProcessor.StopGetAccessRecording()
                        }));
                        this.observeComponentCreation(((e, i) => {
                            ViewStackProcessor.StartGetAccessRecordingFor(e);
                            i ? ViewPU.create(new TreeViewInner(this, {
                                item: t,
                                listNodeDataSource: this.listNodeDataSource,
                                index: this.listNodeDataSource.findIndex(t.getNodeCurrentNodeId()),
                                listTreeViewMenu: this.listTreeViewMenu
                            }, void 0, e)) : this.updateStateVarsOfChildByElmtId(e, { item: t });
                            ViewStackProcessor.StopGetAccessRecording()
                        }));
                        Row.pop();
                        ListItem.pop()
                    };
                    e ? o() : s()
                }
            };
            const t = e => JSON.stringify(e);
            LazyForEach.create('1', this, this.listNodeDataSource, e, t);
            LazyForEach.pop()
        }
        List.pop()
    }

    rerender() {
        this.updateDirtyElements()
    }
}

function findCurrentNodeIndex(e, t) {
    let i = 0;
    e.ListNode.forEach(((e, o) => {
        e.getNodeCurrentNodeId() === t && (i = o)
    }));
    return i
}

export class TreeController {
    constructor() {
        this.ROOT_NODE_ID = -1;
        this.nodeIdList = [];
        this.listNodeUtils = new ListNodeUtils;
        this.listNodeDataSource = new ListNodeDataSource;
        this.initBuild = !0
    }

    getListNodeDataSource() {
        return this.listNodeDataSource
    }

    getClickNodeChildrenInfo() {
        let e = this.listNodeDataSource.getClickNodeId();
        return this.listNodeUtils.getClickNodeChildrenInfo(e)
    }

    getChildrenId() {
        let e = this.listNodeDataSource.getClickNodeId();
        return this.listNodeUtils.getClickChildId(e)
    }

    removeNode() {
        let e = this.listNodeDataSource.getClickNodeId();
        if (e < 0) return;
        let t = this.listNodeUtils.findParentNodeId(e);
        let i = this.listNodeUtils.removeNode(e, t);
        this.listNodeDataSource.refreshData(this.listNodeUtils, MenuOperation.REMOVE_NODE, t, i);
        this.nodeIdList.splice(this.nodeIdList.indexOf(e), 1)
    }

    modifyNode() {
        let e = this.listNodeDataSource.getClickNodeId();
        this.listNodeDataSource.setItemVisibilityOnEdit(e, MenuOperation.MODIFY_NODE)
    }

    add() {
        let e = this.listNodeDataSource.getClickNodeId();
        if (e === this.listNodeDataSource.ROOT_NODE_ID || !this.listNodeDataSource.getIsFolder(e)) return;
        let t = this.listNodeUtils.getNewNodeInfo(e);
        this.nodeIdList.push(this.nodeIdList[this.nodeIdList.length-1] + 1);
        let i = this.nodeIdList[this.nodeIdList.length-1];
        this.listNodeUtils.addNewNodeId = i;
        this.listNodeUtils.addNode(e, i, {
            isFolder: t.isFolder,
            icon: t.icon,
            selectedIcon: t.selectedIcon,
            editIcon: t.editIcon,
            primaryTitle: '新建文件夹',
            container: t.container,
            secondaryTitle: t.secondaryTitle
        });
        this.listNodeDataSource.refreshData(this.listNodeUtils, MenuOperation.ADD_NODE, e, [i]);
        this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE,!1, this.listNodeDataSource.getLastIndex());
        this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(), MenuOperation.COMMIT_NODE);
        this.listNodeDataSource.listNode[this.listNodeDataSource.getLastIndex()].setFontColor({
            id: -1,
            type: 10001,
            params: ['sys.color.ohos_id_color_text_primary'],
            bundleName: '',
            moduleName: ''
        });
        let o = findCurrentNodeIndex(this.listNodeDataSource, i);
        this.listNodeDataSource.setClickIndex(o);
        this.listNodeDataSource.handleEvent(Event.TOUCH_UP, o)
    }

    addNode(e) {
        if (void 0 === e) {
            this.add();
            return this
        }
        if (void 0 !== e.primaryTitle && !this.listNodeUtils.checkMainTitleIsValid(e.primaryTitle.toString())) throw new Error('ListTreeNode[addNode]: The directory name cannot contain the following characters /: *? "< > | or exceeds the maximum length.');
        if (null === e.primaryTitle && null === e.icon) throw new Error('ListTreeNode[addNode]: The icon and directory name cannot be empty at the same time.');
        if (e.currentNodeId === this.ROOT_NODE_ID || null === e.currentNodeId) throw new Error('ListTreeNode[addNode]: currentNodeId can not be -1 or null.');
        void 0 !== e.currentNodeId && this.nodeIdList.push(e.currentNodeId);
        void 0 !== e.parentNodeId && void 0 !== e.currentNodeId && this.listNodeUtils.addNode(e.parentNodeId, e.currentNodeId, e);
        if (!this.initBuild && void 0 !== e.parentNodeId) {
            let t = this.nodeIdList[this.nodeIdList.length-1];
            this.listNodeDataSource.refreshData(this.listNodeUtils, MenuOperation.ADD_NODE, e.parentNodeId, [t])
        }
        return this
    }

    refreshNode(e, t, i) {
        this.listNodeDataSource.setNodeSubtitlePara(e, t, i)
    }

    buildDone() {
        this.listNodeDataSource.init(this.listNodeUtils);
        this.nodeIdList.sort(((e, t) => e - t));
        this.initBuild = !1
    }
}

class BasicDataSource {
    constructor() {
        this.listeners = []
    }

    totalCount() {
        return 0
    }

    getData(e) {
    }

    registerDataChangeListener(e) {
        this.listeners.indexOf(e) < 0 && this.listeners.push(e)
    }

    unregisterDataChangeListener(e) {
        const t = this.listeners.indexOf(e);
        t >= 0 && this.listeners.splice(t, 1)
    }

    notifyDataReload() {
        this.listeners.forEach((e => {
            e.onDataReloaded()
        }))
    }

    notifyDataAdd(e) {
        this.listeners.forEach((t => {
            t.onDataAdd(e)
        }))
    }

    notifyDataChange(e) {
        void 0 !== e && this.listeners.forEach((t => {
            t.onDataChange(e)
        }))
    }

    notifyDataDelete(e) {
        this.listeners.forEach((t => {
            t.onDataDelete(e)
        }))
    }

    notifyDataMove(e, t) {
        this.listeners.forEach((i => {
            i.onDataMove(e, t)
        }))
    }
}

class ListNodeDataSource extends BasicDataSource {
    constructor() {
        super(...arguments);
        this.ROOT_NODE_ID = -1;
        this.listNodeUtils = new ListNodeUtils;
        this.listNode = [];
        this.INITIAL_INVALID_VALUE = -1;
        this.lastIndex = -1;
        this.thisIndex = -1;
        this.modifyNodeIndex = -1;
        this.modifyNodeId = -1;
        this.expandAndCollapseInfo = new Map;
        this.loadedNodeIdAndIndexMap = new Map;
        this.isTouchDown = !1;
        this.appEventBus = TreeListenerManager.getInstance().getTreeListener();
        this.isInnerDrag = !1;
        this.isDrag = !1;
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
        this.nodeIdAndSubtitleMap = new Map;
        this.flag = Flag.NONE;
        this.selectedParentNodeId = this.INITIAL_INVALID_VALUE;
        this.selectedParentNodeSubtitle = '';
        this.insertNodeSubtitle = '';
        this.currentFocusNodeId = this.INITIAL_INVALID_VALUE;
        this.lastFocusNodeId = this.INITIAL_INVALID_VALUE;
        this.addFocusNodeId = this.INITIAL_INVALID_VALUE;
        this.FLAG_LINE = {
            flagLineHeight: '1.0vp',
            flagLineColor: {
                id: -1,
                type: 10001,
                params: ['sys.color.ohos_id_color_emphasize'],
                bundleName: '',
                moduleName: ''
            },
            xOffset: '0vp',
            yTopOffset: '2.75vp',
            yBottomOffset: '-1.25vp',
            yBasePlateOffset: '1.5vp'
        };
        this.DRAG_POPUP = {
            floorConstraintSize: { minWidth: '128vp', maxWidth: '208vp' },
            textConstraintSize: { minWidth1: '80vp', maxWidth1: '160vp', minWidth2: '112vp', maxWidth2: '192vp' },
            padding: { left: '8vp', right: '8vp' },
            backgroundColor: '#FFFFFF',
            height: '48',
            shadow: {
                radius: {
                    id: -1,
                    type: 10002,
                    params: ['sys.float.ohos_id_corner_radius_default_m'],
                    bundleName: '',
                    moduleName: ''
                },
                color: '#00001E',
                offsetX: 0,
                offsetY: 10
            },
            borderRadius: {
                id: -1,
                type: 10002,
                params: ['sys.float.ohos_id_corner_radius_clicked'],
                bundleName: '',
                moduleName: ''
            },
            fontColor: {
                id: -1,
                type: 10001,
                params: ['sys.color.ohos_id_color_primary'],
                bundleName: '',
                moduleName: ''
            },
            fontSize: {
                id: -1,
                type: 10002,
                params: ['sys.float.ohos_id_text_size_body1'],
                bundleName: '',
                moduleName: ''
            },
            fontWeight: FontWeight.Regular,
            imageOpacity: {
                id: -1,
                type: 10002,
                params: ['sys.float.ohos_id_alpha_content_fourth'],
                bundleName: '',
                moduleName: ''
            }
        };
        this.subTitle = {
            normalFontColor: {
                id: -1,
                type: 10001,
                params: ['sys.color.ohos_id_color_secondary'],
                bundleName: '',
                moduleName: ''
            },
            highLightFontColor: {
                id: -1,
                type: 10001,
                params: ['sys.color.ohos_id_color_primary_contrary'],
                bundleName: '',
                moduleName: ''
            },
            fontSize: {
                id: -1,
                type: 10002,
                params: ['sys.float.ohos_id_text_size_body2'],
                bundleName: '',
                moduleName: ''
            },
            fontWeight: FontWeight.Regular,
            margin: { left: '4vp', right: '24' }
        }
    }

    changeNodeColor(e, t) {
        this.listNode[e].setNodeColor(t);
        this.listNode[e].setNodeBorder(!1)
    }

    getNodeColor(e) {
        return this.listNode[e].getNodeColor()
    }

    handleFocusEffect(e, t) {
        this.listNode[e].getNodeIsShow() && this.listNode[e].setNodeBorder(t)
    }

    setImageSource(e, t) {
        var i, o;
        let s = this.listNode[e];
        s.setIsSelected(t === InteractionStatus.Selected || t === InteractionStatus.Edit || t === InteractionStatus.FinishEdit);
        null !== s.getNodeItem().mainTitleNode && t !== InteractionStatus.DragInsert && t !== InteractionStatus.FinishDragInsert && (null === (i = s.getNodeItem().mainTitleNode) || void 0 === i || i.setMainTitleSelected(t === InteractionStatus.Selected || t === InteractionStatus.FinishEdit));
        null !== s.getNodeItem().imageNode && (null === (o = s.getNodeItem().imageNode) || void 0 === o || o.setImageSource(t))
    }

    setImageCollapseSource(e, t) {
        var i;
        let o = this.listNode[e];
        void 0 !== o.getNodeItem().imageCollapse && (null === (i = o.getNodeItem().imageCollapse) || void 0 === i || i.setImageCollapseSource(t, this.expandAndCollapseInfo.get(o.getCurrentNodeId())))
    }

    clearLastIndexStatus() {
        if (!(-1 === this.lastIndex || this.lastIndex >= this.listNode.length)) {
            this.setImageSource(this.lastIndex, InteractionStatus.Normal);
            this.changeNodeColor(this.lastIndex, this.listNode[this.lastIndex].getNodeStatus().normal);
            this.handleFocusEffect(this.lastIndex,!1);
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.listNode[this.lastIndex].getCurrentNodeId()))
        }
    }

    changeNodeStatus(e) {
        var t, i;
        let o = e;
        let s = this.ListNode;
        let d = s[e].getCurrentNodeId();
        if (this.expandAndCollapseInfo.get(d) === NodeStatus.Expand) {
            this.expandAndCollapseInfo.set(d, NodeStatus.Collapse);
            null === (t = s[o].getNodeItem().imageCollapse) || void 0 === t || t.changeImageCollapseSource(NodeStatus.Collapse)
        } else if (this.expandAndCollapseInfo.get(d) === NodeStatus.Collapse) {
            this.expandAndCollapseInfo.set(d, NodeStatus.Expand);
            null === (i = s[o].getNodeItem().imageCollapse) || void 0 === i || i.changeImageCollapseSource(NodeStatus.Expand)
        }
    }

    handleExpandAndCollapse(e) {
        let t = e;
        let i = this.ListNode;
        let o = i[t].getCurrentNodeId();
        if (!this.expandAndCollapseInfo.has(o)) return;
        let s = this.expandAndCollapseInfo.get(o);
        if (i[t].getChildNodeInfo().isHasChildNode && s === NodeStatus.Collapse) {
            for (let e = 0; e < i[t].getChildNodeInfo().allChildNum; e++) {
                i[t + 1+e].setNodeIsShow(!1);
                i[t + 1+e].setListItemHeight(0)
            }
            this.notifyDataReload();
            return
        }
        let d = new Array(i[t].getChildNodeInfo().childNum);
        d[0] = t + 1;
        let a = 1;
        for (; a < i[t].getChildNodeInfo().childNum; ) {
            d[a] = d[a-1] + i[d[a-1]].getChildNodeInfo().allChildNum + 1;
            a++
        }
        if (s === NodeStatus.Expand) for (let e = 0; e < d.length; e++) {
            i[d[e]].setNodeIsShow(!0);
            i[d[e]].setListItemHeight(48);
            let t = i[d[e]].getCurrentNodeId();
            this.expandAndCollapseInfo.get(t) === NodeStatus.Expand && this.handleExpandAndCollapse(d[e])
        }
        d = null;
        this.notifyDataReload()
    }

    init(e) {
        let t = 0;
        this.listNode = [];
        this.listNodeUtils = e;
        this.loadedNodeIdAndIndexMap.clear();
        this.listNodeUtils.traverseNodeDF((e => {
            if (e.currentNodeId >= 0) {
                let i = new NodeInfo(e);
                this.listNode.push(i);
                i.getChildNodeInfo().isHasChildNode && this.expandAndCollapseInfo.set(i.getCurrentNodeId(), NodeStatus.Collapse);
                i.getNodeIsShow() && this.loadedNodeIdAndIndexMap.set(i.getCurrentNodeId(), t++);
                i.getIsFolder() && (void 0 !== i.getNodeInfoData().secondaryTitle ? this.nodeIdAndSubtitleMap.set(i.getCurrentNodeId(), i.getNodeInfoData().secondaryTitle) : this.nodeIdAndSubtitleMap.set(i.getCurrentNodeId(), ''))
            }
            return !1
        }))
    }

    refreshRemoveNodeData(e, t) {
        let i = [];
        for (let t = 0; t < e.length; t++) for (let o = 0; o < this.listNode.length; o++) if (this.listNode[o].getNodeCurrentNodeId() === e[t]) {
            let s = this.listNode[o].getNodeCurrentNodeId();
            this.loadedNodeIdAndIndexMap.has(s) && i.push(this.loadedNodeIdAndIndexMap.get(s));
            let d = this.listNode.splice(o, 1);
            d = null;
            this.expandAndCollapseInfo.has(e[t]) && this.expandAndCollapseInfo.delete(e[t]);
            break
        }
        i.forEach((e => {
            this.notifyDataDelete(e);
            this.notifyDataChange(e)
        }));
        for (let e = 0; e < this.listNode.length; e++) if (this.listNode[e].getNodeCurrentNodeId() === t.getNodeCurrentNodeId()) {
            if (null === t.getNodeItem().imageCollapse) {
                this.listNode[e].handleImageCollapseAfterAddNode(!1);
                this.expandAndCollapseInfo.delete(t.getNodeCurrentNodeId());
                this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.listNode[e].getNodeCurrentNodeId()))
            }
            break
        }
        let o = { currentNodeId: t.getNodeCurrentNodeId(), parentNodeId: t.getNodeParentNodeId() };
        this.appEventBus.emit(TreeListenType.NODE_DELETE, o)
    }

    refreshAddNodeData(e) {
        let t = new NodeInfo(new NodeItem(emptyNodeInfo));
        this.listNodeUtils.traverseNodeDF((i => {
            if (i.currentNodeId === e[0]) {
                t = new NodeInfo(i);
                return !0
            }
            return !1
        }));
        t.setIsModify(!0);
        let i = 0;
        for (let e = 0; e < this.listNode.length; e++) if (this.listNode[e].getNodeCurrentNodeId() === t.getNodeParentNodeId()) {
            i = e;
            if (null === this.listNode[e].getNodeItem().imageCollapse) {
                this.listNode[e].handleImageCollapseAfterAddNode(!0);
                this.notifyDataChange(i)
            } else this.expandAndCollapseInfo.get(this.listNode[e].getNodeCurrentNodeId()) === NodeStatus.Collapse && this.changeNodeStatus(i);
            this.listNode.splice(e + 1, 0, t);
            this.listNode[e+1].setTitleAndInputTextStatus(!0);
            this.listNode[e+1].setNodeIsShow(!0);
            this.listNode[e+1].setListItemHeight(48);
            this.setImageSource(e + 1, InteractionStatus.Edit);
            this.currentOperation = MenuOperation.ADD_NODE;
            this.notifyDataAdd(e + 1);
            this.notificationNodeInfo(e + 1, this.currentOperation);
            break
        }
        this.modifyNodeIndex = i + 1;
        this.setClickIndex(i);
        this.lastIndex = i;
        this.expandAndCollapseInfo.set(t.getNodeParentNodeId(), NodeStatus.Expand);
        this.handleExpandAndCollapse(i)
    }

    refreshData(e, t, i, o) {
        let s = new NodeInfo(new NodeItem(emptyNodeInfo));
        this.listNodeUtils = e;
        this.listNodeUtils.traverseNodeDF((e => {
            if (e.currentNodeId === i) {
                s = new NodeInfo(e);
                return !0
            }
            return !1
        }));
        if (t === MenuOperation.REMOVE_NODE) {
            this.nodeIdAndSubtitleMap.set(i, this.selectedParentNodeSubtitle);
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(i));
            this.refreshRemoveNodeData(o, s)
        }
        if (t === MenuOperation.ADD_NODE) {
            this.addFocusNodeId = o[0];
            this.nodeIdAndSubtitleMap.set(this.getClickNodeId(), this.selectedParentNodeSubtitle);
            this.nodeIdAndSubtitleMap.set(o[0], this.insertNodeSubtitle);
            this.refreshAddNodeData(o)
        }
    }

    setClickIndex(e) {
        this.thisIndex = e
    }

    getClickNodeId() {
        return this.thisIndex < 0 || this.thisIndex >= this.ListNode.length ? -1 : this.ListNode[this.thisIndex].getCurrentNodeId()
    }

    expandAndCollapseNode(e) {
        this.changeNodeStatus(e);
        this.handleExpandAndCollapse(e)
    }

    getIsTouchDown() {
        return this.isTouchDown
    }

    getLastIndex() {
        return this.lastIndex
    }

    findIndex(e) {
        let t = -1;
        this.ListNode.forEach(((i, o) => {
            i.getNodeCurrentNodeId() === e && (t = o)
        }));
        return t
    }

    handleEventDrag(e) {
        this.setImageSource(e, InteractionStatus.Normal);
        this.changeNodeColor(e, this.listNode[e].getNodeStatus().normal);
        this.handleFocusEffect(e,!1);
        this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.listNode[e].getCurrentNodeId()))
    }

    handleEvent(e, t) {
        if (this.isDrag) return;
        e !== Event.TOUCH_DOWN && e !== Event.TOUCH_UP && e !== Event.MOUSE_BUTTON_RIGHT || t !== this.lastIndex && this.clearLastIndexStatus();
        let i = this.loadedNodeIdAndIndexMap.get(this.listNode[t].getCurrentNodeId());
        switch (e) {
            case Event.TOUCH_DOWN:
                this.isTouchDown = !0;
                this.changeNodeColor(t, this.listNode[t].getNodeStatus().press);
                this.notifyDataChange(i);
                break;
            case Event.TOUCH_UP: {
                this.isInnerDrag && (this.isInnerDrag = !1);
                this.isTouchDown = !1;
                let e = this.listNode[t];
                this.setImageSource(t, InteractionStatus.Selected);
                e.setFontColor({
                    id: -1,
                    type: 10001,
                    params: ['sys.color.ohos_id_color_primary'],
                    bundleName: '',
                    moduleName: ''
                });
                this.lastIndex = t;
                this.changeNodeColor(t, e.getNodeStatus().selected);
                this.notifyDataChange(i);
                break
            }
            case Event.HOVER:
                if (this.getNodeColor(t) !== this.listNode[t].getNodeStatus().selected) {
                    this.changeNodeColor(t, this.listNode[t].getNodeStatus().hover);
                    this.notifyDataChange(i)
                }
                break;
            case Event.HOVER_OVER:
                if (this.getNodeColor(t) !== this.listNode[t].getNodeStatus().selected) {
                    this.changeNodeColor(t, this.listNode[t].getNodeStatus().normal);
                    this.notifyDataChange(i)
                }
                break;
            case Event.FOCUS:
                this.handleFocusEffect(t,!0);
                this.notifyDataChange(i);
                break;
            case Event.BLUR:
                this.handleFocusEffect(t,!1);
                this.notifyDataChange(i);
                break;
            case Event.MOUSE_BUTTON_RIGHT:
                this.lastIndex = t;
                this.finishEditing();
                break;
            case Event.DRAG:
                this.isTouchDown = !1;
                let e = this.listNode[t];
                this.setImageSource(t, InteractionStatus.Selected);
                this.lastIndex = t;
                this.changeNodeColor(t, e.getNodeStatus().selected);
                this.notifyDataChange(i)
        }
    }

    notificationNodeInfo(e, t) {
        var i, o, s;
        if (t === MenuOperation.MODIFY_NODE) {
            let e = this.listNode[this.modifyNodeIndex];
            let t = { currentNodeId: e.getNodeCurrentNodeId(), parentNodeId: e.getNodeParentNodeId() };
            this.appEventBus.emit(TreeListenType.NODE_MODIFY, t)
        } else if (t === MenuOperation.ADD_NODE) {
            let t = this.listNode[e];
            void 0 !== t.getNodeItem().imageNode && (null === (i = t.getNodeItem().imageNode) || void 0 === i || i.source);
            void 0 !== t.getNodeItem().imageNode && (null === (o = t.getNodeItem().imageNode) || void 0 === o || o.selectedSource);
            void 0 !== t.getNodeItem().imageNode && (null === (s = t.getNodeItem().imageNode) || void 0 === s || s.editSource);
            let d = { currentNodeId: t.getNodeCurrentNodeId(), parentNodeId: t.getNodeParentNodeId() };
            this.appEventBus.emit(TreeListenType.NODE_ADD, d)
        }
    }

    finishEditing() {
        if (-1 !== this.modifyNodeIndex) {
            this.setImageSource(this.modifyNodeIndex, InteractionStatus.FinishEdit);
            this.setImageCollapseSource(this.modifyNodeIndex, InteractionStatus.FinishEdit);
            this.listNode[this.modifyNodeIndex].setIsModify(!1);
            this.listNode[this.modifyNodeIndex].setTitleAndInputTextStatus(!1);
            this.notificationNodeInfo(this.modifyNodeIndex, this.currentOperation);
            this.notifyDataChange(this.modifyNodeIndex)
        }
    }

    setItemVisibilityOnEdit(e, t) {
        let i = -1;
        if (-1 !== e) {
            if (t === MenuOperation.MODIFY_NODE) {
                for (let t = 0; t < this.listNode.length; t++) if (this.listNode[t].getCurrentNodeId() === e) {
                    i = t;
                    break
                }
                let t = this.listNode[i];
                t.setIsModify(!0);
                if (null === t.getNodeItem().mainTitleNode) return;
                this.currentOperation = MenuOperation.MODIFY_NODE;
                t.setTitleAndInputTextStatus(!0);
                this.setImageSource(i, InteractionStatus.Edit);
                this.setImageCollapseSource(i, InteractionStatus.Edit);
                this.modifyNodeIndex = i;
                t.getNodeItem().inputText && (null !== t.getNodeItem().imageCollapse ? t.getNodeItem().inputText.rightMargin = {
                    id: -1,
                    type: 10002,
                    params: ['sys.float.ohos_id_text_paragraph_margin_xs'],
                    bundleName: '',
                    moduleName: ''
                } : t.getNodeItem().inputText.rightMargin = {
                    id: -1,
                    type: 10002,
                    params: ['sys.float.ohos_id_elements_margin_horizontal_m'],
                    bundleName: '',
                    moduleName: ''
                });
                this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(e))
            }
            i = e;
            if (t === MenuOperation.COMMIT_NODE) {
                let e = this.listNode[i];
                e.setTitleAndInputTextStatus(!1);
                e.setIsModify(!1);
                this.setImageSource(i, InteractionStatus.FinishEdit);
                this.setImageCollapseSource(i, InteractionStatus.FinishEdit);
                this.notificationNodeInfo(this.modifyNodeIndex, this.currentOperation);
                this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(e.getCurrentNodeId()))
            }
        }
    }

    setPopUpInfo(e, t, i, o) {
        var s;
        let d = this.listNode[o];
        d.setPopUpIsShow(i);
        let a = this.loadedNodeIdAndIndexMap.get(d.getCurrentNodeId());
        if (i) {
            if (e === PopUpType.HINTS) {
                if (null !== d.getNodeItem().mainTitleNode) d.setPopUpText(null === (s = d.getNodeItem().mainTitleNode) || void 0 === s ? void 0 : s.title); else {
                    d.setPopUpText('');
                    d.setPopUpIsShow(!1)
                }
                d.setPopUpEnableArrow(!1);
                d.setPopUpColor({
                    id: -1,
                    type: 10001,
                    params: ['sys.color.ohos_id_color_background'],
                    bundleName: '',
                    moduleName: ''
                });
                d.setPopUpTextColor({
                    id: -1,
                    type: 10001,
                    params: ['sys.color.ohos_id_color_text_secondary'],
                    bundleName: '',
                    moduleName: ''
                })
            } else if (e === PopUpType.WARNINGS && null !== d.getNodeItem().inputText) {
                t === InputError.INVALID_ERROR ? d.setPopUpText('invalid error') : t === InputError.LENGTH_ERROR && d.setPopUpText('length error');
                d.setPopUpEnableArrow(!0);
                d.setPopUpColor({
                    id: -1,
                    type: 10001,
                    params: ['sys.color.ohos_id_color_help_tip_bg'],
                    bundleName: '',
                    moduleName: ''
                });
                d.setPopUpTextColor({
                    id: -1,
                    type: 10001,
                    params: ['sys.color.ohos_id_color_text_hint_contrary'],
                    bundleName: '',
                    moduleName: ''
                })
            }
            this.notifyDataChange(a)
        } else this.notifyDataChange(a)
    }

    setShowPopUpTimeout(e, t) {
        null !== this.listNode[t].getNodeItem().mainTitleNode && (this.listNode[t].getNodeItem().mainTitleNode.popUpTimeout = e);
        let i = this.loadedNodeIdAndIndexMap.get(this.listNode[t].getCurrentNodeId());
        this.notifyDataChange(i)
    }

    setMainTitleNameOnEdit(e, t) {
        this.modifyNodeIndex = e;
        null !== this.listNode[e].getNodeItem().mainTitleNode && (this.listNode[e].getNodeItem().mainTitleNode.title = t)
    }

    get ListNode() {
        return this.listNode
    }

    totalCount() {
        let e = 0;
        let t = 0;
        this.loadedNodeIdAndIndexMap.clear();
        for (let i = 0; i < this.listNode.length; i++) if (this.listNode[i].getNodeIsShow()) {
            this.loadedNodeIdAndIndexMap.set(this.listNode[i].getCurrentNodeId(), t++);
            e++
        }
        return e
    }

    getData(e) {
        let t = 0;
        for (let i = 0; i < this.listNode.length; i++) if (this.listNode[i].getNodeIsShow()) {
            if (e === t) return this.listNode[i];
            t++
        }
    }

    addData(e, t) {
        this.listNode.splice(e, 0, t);
        this.notifyDataAdd(e)
    }

    pushData(e) {
        this.listNode.push(e);
        this.notifyDataAdd(this.listNode.length - 1)
    }

    setIsInnerDrag(e) {
        this.isInnerDrag = e
    }

    getIsInnerDrag() {
        return this.isInnerDrag
    }

    setIsDrag(e) {
        this.isDrag = e
    }

    getIsDrag() {
        return this.isDrag
    }

    setCurrentNodeInfo(e) {
        void 0 !== e && (this.currentNodeInfo = e)
    }

    getCurrentNodeInfo() {
        return this.currentNodeInfo
    }

    setDraggingParentNodeId(e) {
        void 0 !== e && (this.draggingParentNodeId = e)
    }

    getDraggingParentNodeId() {
        return this.draggingParentNodeId
    }

    getDraggingCurrentNodeId() {
        return this.draggingCurrentNodeId
    }

    setDraggingCurrentNodeId(e) {
        void 0 !== e && (this.draggingCurrentNodeId = e)
    }

    setListItemOpacity(e) {
        this.listItemOpacity = e
    }

    getListItemOpacity(e) {
        return e.getCurrentNodeId() === this.getDraggingCurrentNodeId() ? this.listItemOpacity : 1
    }

    getDragPopupPara() {
        return this.DRAG_POPUP
    }

    setLastPassIndex(e) {
        this.lastPassIndex = e
    }

    getLastPassIndex() {
        return this.lastPassIndex
    }

    getIsParentOfInsertNode(e) {
        if (null === this.currentNodeInfo || void 0 === e) return !1;
        let t = this.currentNodeInfo.getNodeInfoNode();
        let i = !1;
        this.listNodeUtils.traverseNodeDF((t => {
            if (t.currentNodeId === e) {
                i = !0;
                return !0
            }
            return !1
        }), t);
        return i
    }

    setPassIndex(e) {
        this.thisPassIndex = e
    }

    getPassIndex() {
        return this.thisPassIndex
    }

    clearTimeOutAboutDelayHighLightAndExpand(e) {
        if (this.lastPassId !== this.INITIAL_INVALID_VALUE && this.loadedNodeIdAndIndexMap.has(this.lastPassId)) {
            let e = this.loadedNodeIdAndIndexMap.get(this.lastPassId);
            this.ListNode.forEach((e => {
                e.getNodeCurrentNodeId() === this.lastPassId && e.setCanShowFlagLine(!1)
            }));
            this.notifyDataChange(e)
        }
        if (this.lastTimeoutHighLightId !== this.INITIAL_INVALID_VALUE && this.clearTimeoutHighLightId !== this.lastTimeoutHighLightId) {
            clearTimeout(this.lastTimeoutHighLightId);
            if (this.lastDelayHighLightIndex !== this.INITIAL_INVALID_VALUE) {
                this.clearHighLight(this.lastDelayHighLightIndex);
                let e = this.loadedNodeIdAndIndexMap.get(this.listNode[this.lastDelayHighLightIndex].getCurrentNodeId());
                this.notifyDataChange(e)
            }
            this.clearTimeoutHighLightId = this.lastTimeoutHighLightId
        }
        this.lastTimeoutHighLightId = this.timeoutHighLightId;
        this.lastDelayHighLightIndex = e;
        if (this.lastTimeoutExpandId !== this.INITIAL_INVALID_VALUE && this.clearTimeoutExpandId !== this.lastTimeoutExpandId) {
            clearTimeout(this.lastTimeoutExpandId);
            this.clearTimeoutExpandId = this.lastTimeoutExpandId
        }
        this.lastTimeoutExpandId = this.timeoutExpandId;
        this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE
    }

    clearHighLight(e) {
        this.changeNodeColor(e, this.listNode[e].getNodeStatus().normal);
        this.changeNodeHighLightColor(e,!1);
        this.setImageSource(e, InteractionStatus.FinishDragInsert);
        this.setImageCollapseSource(e, InteractionStatus.FinishDragInsert);
        this.listNode[e].setIsHighLight(!1)
    }

    changeNodeHighLightColor(e, t) {
        var i;
        this.listNode[e].getNodeItem().mainTitleNode && this.listNode[e].getIsShowTitle() && (null === (i = this.listNode[e].getNodeItem().mainTitleNode) || void 0 === i || i.setMainTitleHighLight(t))
    }

    setVisibility(e, t, i) {
        var o, s, d, a, r, n, l, h, N, u, c, I, g, p, m, A, S, _;
        let f = this.thisPassIndex !== t || this.flag !== e;
        this.thisPassIndex = t;
        if ((f || i) && this.isInnerDrag) {
            this.flag = e;
            let i = null === (o = this.getData(t)) || void 0 === o ? void 0 : o.getCurrentNodeId();
            let f = null === (s = this.getData(t)) || void 0 === s ? void 0 : s.getNodeLevel();
            if (void 0 !== i) {
                f = this.expandAndCollapseInfo.get(i) === NodeStatus.Expand && this.flag === Flag.DOWN_FLAG ? f ? f + 1 : void 0 : f;
                if (this.lastPassId !== this.INITIAL_INVALID_VALUE && this.loadedNodeIdAndIndexMap.has(this.lastPassId)) {
                    let e = this.loadedNodeIdAndIndexMap.get(this.lastPassId);
                    this.ListNode.forEach((e => {
                        e.getNodeCurrentNodeId() === this.lastPassId && e.setCanShowFlagLine(!1)
                    }));
                    this.notifyDataChange(e)
                }
                if (this.flag === Flag.DOWN_FLAG && t < this.totalCount() - 1) {
                    null === (d = this.getData(t)) || void 0 === d || d.setCanShowFlagLine(!1);
                    null === (a = this.getData(t + 1)) || void 0 === a || a.setCanShowFlagLine(!0);
                    null === (r = this.getData(t)) || void 0 === r || r.setCanShowBottomFlagLine(!1);
                    null === (n = this.getData(t + 1)) || void 0 === n || n.setFlagLineLeftMargin(f);
                    this.notifyDataChange(t);
                    this.notifyDataChange(t + 1);
                    this.lastPassId = null === (l = this.getData(t + 1)) || void 0 === l ? void 0 : l.getNodeCurrentNodeId()
                } else if (this.flag === Flag.UP_FLAG && t < this.totalCount() - 1) {
                    null === (h = this.getData(t)) || void 0 === h || h.setCanShowFlagLine(!0);
                    null === (N = this.getData(t + 1)) || void 0 === N || N.setCanShowFlagLine(!1);
                    null === (u = this.getData(t)) || void 0 === u || u.setCanShowBottomFlagLine(!1);
                    null === (c = this.getData(t)) || void 0 === c || c.setFlagLineLeftMargin(f);
                    this.notifyDataChange(t);
                    this.notifyDataChange(t + 1);
                    this.lastPassId = null === (I = this.getData(t)) || void 0 === I ? void 0 : I.getNodeCurrentNodeId()
                } else if (t >= this.totalCount() - 1) {
                    if (this.flag === Flag.DOWN_FLAG) {
                        null === (g = this.getData(t)) || void 0 === g || g.setCanShowFlagLine(!1);
                        null === (p = this.getData(t)) || void 0 === p || p.setCanShowBottomFlagLine(!0)
                    } else {
                        null === (m = this.getData(t)) || void 0 === m || m.setCanShowFlagLine(!0);
                        null === (A = this.getData(t)) || void 0 === A || A.setCanShowBottomFlagLine(!1)
                    }
                    null === (S = this.getData(t)) || void 0 === S || S.setFlagLineLeftMargin(f);
                    this.notifyDataChange(t);
                    this.lastPassId = null === (_ = this.getData(t)) || void 0 === _ ? void 0 : _.getNodeCurrentNodeId()
                }
            }
        }
    }

    delayHighLightAndExpandNode(e, t, i) {
        var o, s;
        let d = e !== this.lastDelayExpandIndex;
        let a = null === (o = this.getData(i)) || void 0 === o ? void 0 : o.getIsOverBorder();
        this.lastDelayExpandIndex = a ? this.INITIAL_INVALID_VALUE : e;
        if (a || d) {
            if (!a && (!this.isInnerDrag || this.expandAndCollapseInfo.get(t) === NodeStatus.Collapse && this.isInnerDrag || !this.expandAndCollapseInfo.has(t) && this.listNode[e].getIsFolder())) {
                this.changeNodeColor(e, this.listNode[e].getNodeStatus().hover);
                this.notifyDataChange(i);
                let t = this.isInnerDrag ? 1e3 : 0;
                this.timeoutHighLightId = setTimeout((() => {
                    this.delayHighLight(e)
                }), t)
            }
            if (a || this.lastTimeoutHighLightId !== this.INITIAL_INVALID_VALUE && this.clearTimeoutHighLightId !== this.lastTimeoutHighLightId) {
                clearTimeout(this.lastTimeoutHighLightId);
                if (this.lastDelayHighLightIndex !== this.INITIAL_INVALID_VALUE) {
                    this.clearHighLight(this.lastDelayHighLightIndex);
                    this.notifyDataReload()
                }
                this.clearTimeoutHighLightId = this.lastTimeoutHighLightId
            }
            this.lastTimeoutHighLightId = this.timeoutHighLightId;
            this.lastDelayHighLightIndex = e;
            if (!a && this.expandAndCollapseInfo.get(t) === NodeStatus.Collapse) {
                let t = null === (s = this.getData(i)) || void 0 === s ? void 0 : s.getNodeInfoNode().children[0].currentNodeId;
                let o = 2e3;
                this.timeoutExpandId = setTimeout((() => {
                    this.clearHighLight(this.lastDelayHighLightIndex);
                    void 0 !== t && this.alterFlagLineAndExpandNode(e, t)
                }), o)
            }
            if (a || this.lastTimeoutExpandId !== this.INITIAL_INVALID_VALUE && this.clearTimeoutExpandId !== this.lastTimeoutExpandId) {
                clearTimeout(this.lastTimeoutExpandId);
                this.clearTimeoutExpandId = this.lastTimeoutExpandId
            }
            this.lastTimeoutExpandId = this.timeoutExpandId
        }
    }

    delayHighLight(e) {
        this.ListNode.forEach((e => {
            if (e.getNodeCurrentNodeId() === this.lastPassId) {
                e.setCanShowFlagLine(!1);
                e.setCanShowBottomFlagLine(!1)
            }
        }));
        this.changeNodeColor(e, this.listNode[e].getNodeStatus().highLight);
        this.listNode[e].setIsHighLight(!0);
        this.changeNodeHighLightColor(e,!0);
        this.setImageSource(e, InteractionStatus.DragInsert);
        this.setImageCollapseSource(e, InteractionStatus.DragInsert);
        this.notifyDataReload()
    }

    alterFlagLineAndExpandNode(e, t) {
        this.ListNode.forEach((e => {
            if (e.getNodeCurrentNodeId() === this.lastPassId) {
                e.setCanShowFlagLine(!1);
                e.setCanShowBottomFlagLine(!1)
            }
        }));
        this.ListNode.forEach((e => {
            this.isInnerDrag && e.getNodeCurrentNodeId() === t && e.setCanShowFlagLine(!0)
        }));
        this.changeNodeStatus(e);
        this.handleExpandAndCollapse(e);
        this.lastPassId = t
    }

    hideLastLine() {
        if (this.lastPassId !== this.INITIAL_INVALID_VALUE && this.loadedNodeIdAndIndexMap.has(this.lastPassId)) {
            this.ListNode.forEach((e => {
                if (e.getNodeCurrentNodeId() === this.lastPassId) {
                    e.setCanShowFlagLine(!1);
                    e.setCanShowBottomFlagLine(!1)
                }
            }));
            let e = this.loadedNodeIdAndIndexMap.get(this.lastPassId);
            this.notifyDataChange(e)
        }
    }

    clearLastTimeoutHighLight() {
        if (this.lastTimeoutHighLightId !== this.INITIAL_INVALID_VALUE && this.clearTimeoutHighLightId !== this.lastTimeoutHighLightId) {
            clearTimeout(this.lastTimeoutHighLightId);
            this.lastDelayHighLightIndex !== this.INITIAL_INVALID_VALUE && this.clearHighLight(this.lastDelayHighLightIndex)
        }
    }

    clearLastTimeoutExpand() {
        this.lastTimeoutExpandId !== this.INITIAL_INVALID_VALUE && this.clearTimeoutExpandId !== this.lastTimeoutExpandId && clearTimeout(this.lastTimeoutExpandId)
    }

    getSubtitle(e) {
        var t;
        return this.nodeIdAndSubtitleMap.has(e) ? 'number' == typeof this.nodeIdAndSubtitleMap.get(e) ? null === (t = this.nodeIdAndSubtitleMap.get(e)) || void 0 === t ? void 0 : t.toString() : this.nodeIdAndSubtitleMap.get(e) : ''
    }

    hasSubtitle(e) {
        return this.nodeIdAndSubtitleMap.has(e)
    }

    initialParameterAboutDelayHighLightAndExpandIndex() {
        this.lastDelayHighLightIndex = this.INITIAL_INVALID_VALUE;
        this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE;
        this.lastPassIndex = this.INITIAL_INVALID_VALUE;
        this.draggingCurrentNodeId = this.INITIAL_INVALID_VALUE;
        this.flag = Flag.NONE
    }

    refreshSubtitle(e) {
        this.nodeIdAndSubtitleMap.set(this.selectedParentNodeId, this.selectedParentNodeSubtitle);
        this.nodeIdAndSubtitleMap.set(e, this.insertNodeSubtitle);
        this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.selectedParentNodeId));
        this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(e))
    }

    setNodeSubtitlePara(e, t, i) {
        this.selectedParentNodeId = e;
        this.selectedParentNodeSubtitle = t;
        this.insertNodeSubtitle = i
    }

    getInsertNodeSubtitle() {
        return this.insertNodeSubtitle
    }

    getExpandAndCollapseInfo(e) {
        return this.expandAndCollapseInfo.get(e)
    }

    getLastDelayHighLightId() {
        return this.lastDelayHighLightId
    }

    setLastDelayHighLightId() {
        this.ListNode.forEach(((e, t) => {
            t === this.lastDelayHighLightIndex && (this.lastDelayHighLightId = e.getCurrentNodeId())
        }))
    }

    setLastPassId(e) {
        this.lastPassId = e
    }

    setLastDelayHighLightIndex(e) {
        this.lastDelayHighLightIndex = e
    }

    alterDragNode(e, t, i, o, s) {
        let d = [];
        let a = e;
        let r = o;
        let n = s.getNodeInfoData();
        let l = null;
        let h = s.getNodeInfoNode();
        let N = !1;
        let u = this.INITIAL_INVALID_VALUE;
        let c = this.INITIAL_INVALID_VALUE;
        let I = this.flag === Flag.DOWN_FLAG;
        c = this.getChildIndex(i, o);
        u = this.getChildIndex(e, t) + 1;
        u = e !== i ? I ? u + 1 : u : u > c ? I ? u : u - 1 : I ? u + 1 : u;
        for (let e = 0; e < this.listNode.length; e++) if (this.listNode[e].getCurrentNodeId() === t) {
            N = this.listNode[e].getIsHighLight();
            if (this.flag === Flag.DOWN_FLAG && this.expandAndCollapseInfo.get(t) === NodeStatus.Expand) {
                a = t;
                u = 0
            } else if (this.flag === Flag.UP_FLAG && this.expandAndCollapseInfo.get(t) === NodeStatus.Expand && !1 === this.listNode[e].getCanShowFlagLine()) {
                a = t;
                u = 0
            } else if (N) {
                a = t;
                u = 0
            }
            break
        }
        let g = { currentNodeId: r, parentNodeId: a, childIndex: u };
        this.appEventBus.emit(TreeListenType.NODE_MOVE, g);
        d.push({ parentId: a, currentId: r, data: n });
        let p = null;
        this.listNodeUtils.dragTraverseNodeDF(((e, t) => {
            if (e) {
                p = e;
                a = p.parentNodeId;
                r = p.currentNodeId;
                for (let e = 0; e < t.length; e++) if (t[e].getNodeCurrentNodeId() === r) {
                    l = t[e];
                    break
                }
                if (null === l) return !1;
                let o = l.getNodeInfoData();
                a !== i && d.push({ parentId: a, currentId: r, data: o });
                return !1
            }
            return !1
        }), h, this.listNode);
        this.listNodeUtils.removeNode(o, i);
        let m = t;
        let A = I;
        if (this.expandAndCollapseInfo.get(t) === NodeStatus.Expand) {
            A = !1;
            this.listNode.forEach((e => {
                e.getCurrentNodeId() === t && !1 === e.getCanShowFlagLine() && (m = e.getNodeInfoNode().children.length ? e.getNodeInfoNode().children[0].currentNodeId : this.INITIAL_INVALID_VALUE)
            }))
        } else !this.expandAndCollapseInfo.get(t) && N && this.expandAndCollapseInfo.set(t, NodeStatus.Expand);
        this.listNodeUtils.addDragNode(d[0].parentId, d[0].currentId, m, A, d[0].data);
        for (let e = 1; e < d.length; e++) this.listNodeUtils.addNode(d[e].parentId, d[e].currentId, d[e].data);
        for (let e = 0; e < this.listNode.length; e++) if (this.listNode[e].getCurrentNodeId() === i && null === this.listNode[e].getNodeInfoNode().getNodeItem().imageCollapse) {
            this.listNode[e].handleImageCollapseAfterAddNode(!1);
            this.expandAndCollapseInfo.delete(i);
            break
        }
        let S = [...this.listNode];
        this.reloadListNode(this.listNodeUtils, S)
    }

    reloadListNode(e, t) {
        let i = 0;
        this.listNode = [];
        this.listNodeUtils = e;
        this.loadedNodeIdAndIndexMap.clear();
        this.listNodeUtils.traverseNodeDF((e => {
            var o, s, d;
            if (e.currentNodeId >= 0) {
                let a = new NodeInfo(e);
                this.listNode.push(a);
                this.expandAndCollapseInfo.get(e.currentNodeId) === NodeStatus.Expand ? null === (o = a.getNodeItem().imageCollapse) || void 0 === o || o.changeImageCollapseSource(NodeStatus.Expand) : this.expandAndCollapseInfo.get(e.currentNodeId) === NodeStatus.Collapse && (null === (s = a.getNodeItem().imageCollapse) || void 0 === s || s.changeImageCollapseSource(NodeStatus.Collapse));
                for (let e = 0; e < t.length; e++) if (t[e].getCurrentNodeId() === a.getCurrentNodeId()) {
                    a.setNodeIsShow(t[e].getNodeIsShow());
                    a.setListItemHeight(t[e].getListItemHeight());
                    a.getNodeItem().mainTitleNode && a.getIsShowTitle() && (a.getNodeItem().mainTitleNode.title = null === (d = t[e].getNodeItem().mainTitleNode) || void 0 === d ? void 0 : d.title);
                    break
                }
                a.getNodeIsShow() && this.loadedNodeIdAndIndexMap.set(a.getCurrentNodeId(), i++)
            }
            return !1
        }))
    }

    getFlagLine() {
        return this.FLAG_LINE
    }

    getVisibility(e) {
        let t = this.loadedNodeIdAndIndexMap.get(e.getCurrentNodeId()) - 1;
        if (t > this.INITIAL_INVALID_VALUE) {
            let i = this.getData(t);
            return!0 !== e.getCanShowFlagLine() || e.getIsHighLight() || (null == i ? void 0 : i.getIsHighLight()) ? Visibility.Hidden : Visibility.Visible
        }
        return!0 !== e.getCanShowFlagLine() || e.getIsHighLight() ? Visibility.Hidden : Visibility.Visible
    }

    getSubTitlePara() {
        return this.subTitle
    }

    getIsFolder(e) {
        var t;
        return!!this.loadedNodeIdAndIndexMap.has(e) && (null === (t = this.getData(this.loadedNodeIdAndIndexMap.get(e))) || void 0 === t ? void 0 : t.getIsFolder())
    }

    getSubTitleFontColor(e) {
        return e ? this.subTitle.highLightFontColor : this.subTitle.normalFontColor
    }

    getChildIndex(e, t) {
        let i = this.INITIAL_INVALID_VALUE;
        this.listNodeUtils.traverseNodeBF((o => {
            if (o.getCurrentNodeId() === e) {
                o.children.forEach(((e, o) => {
                    e.getCurrentNodeId() === t && (i = o)
                }));
                return !0
            }
            return !1
        }));
        return i
    }

    setCurrentFocusNodeId(e) {
        this.currentFocusNodeId = e
    }

    getCurrentFocusNodeId() {
        return this.currentFocusNodeId
    }

    setLastFocusNodeId(e) {
        this.lastFocusNodeId = e
    }

    getLastFocusNodeId() {
        return this.lastFocusNodeId
    }

    getAddFocusNodeId() {
        return this.addFocusNodeId
    }

    setFlag(e) {
        this.flag = e
    }
}

export class TreeViewInner extends ViewPU {
    constructor(e, t, i, o = -1) {
        super(e, i, o);
        this.__item = new SynchedPropertyNesedObjectPU(t.item, this, 'item');
        this.listNodeDataSource = new ListNodeDataSource;
        this.__columnWidth = new ObservedPropertySimplePU(0, this, 'columnWidth');
        this.__isFocused = new ObservedPropertySimplePU(!1, this, 'isFocused');
        this.__index = new ObservedPropertySimplePU(-1, this, 'index');
        this.__lastIndex = new ObservedPropertySimplePU(-1, this, 'lastIndex');
        this.__count = new ObservedPropertySimplePU(0, this, 'count');
        this.listTreeViewMenu = void 0;
        this.MAX_CN_LENGTH = 254;
        this.MAX_EN_LENGTH = 255;
        this.INITIAL_INVALID_VALUE = -1;
        this.MAX_TOUCH_DOWN_COUNT = 0;
        this.isMultiPress = !1;
        this.touchDownCount = this.INITIAL_INVALID_VALUE;
        this.appEventBus = TreeListenerManager.getInstance().getTreeListener();
        this.itemPadding = {
            left: {
                id: -1,
                type: 10002,
                params: ['sys.float.ohos_id_card_margin_start'],
                bundleName: '',
                moduleName: ''
            },
            right: {
                id: -1,
                type: 10002,
                params: ['sys.float.ohos_id_card_margin_end'],
                bundleName: '',
                moduleName: ''
            },
            top: {
                id: -1,
                type: 10002,
                params: ['sys.float.ohos_id_text_margin_vertical'],
                bundleName: '',
                moduleName: ''
            },
            bottom: '0vp'
        };
        this.textInputPadding = { left: '0vp', right: '0vp', top: '0vp', bottom: '0vp' };
        this.setInitiallyProvidedValue(t)
    }

    setInitiallyProvidedValue(e) {
        this.__item.set(e.item);
        void 0 !== e.listNodeDataSource && (this.listNodeDataSource = e.listNodeDataSource);
        void 0 !== e.columnWidth && (this.columnWidth = e.columnWidth);
        void 0 !== e.isFocused && (this.isFocused = e.isFocused);
        void 0 !== e.index && (this.index = e.index);
        void 0 !== e.lastIndex && (this.lastIndex = e.lastIndex);
        void 0 !== e.count && (this.count = e.count);
        void 0 !== e.listTreeViewMenu && (this.listTreeViewMenu = e.listTreeViewMenu);
        void 0 !== e.MAX_CN_LENGTH && (this.MAX_CN_LENGTH = e.MAX_CN_LENGTH);
        void 0 !== e.MAX_EN_LENGTH && (this.MAX_EN_LENGTH = e.MAX_EN_LENGTH);
        void 0 !== e.INITIAL_INVALID_VALUE && (this.INITIAL_INVALID_VALUE = e.INITIAL_INVALID_VALUE);
        void 0 !== e.MAX_TOUCH_DOWN_COUNT && (this.MAX_TOUCH_DOWN_COUNT = e.MAX_TOUCH_DOWN_COUNT);
        void 0 !== e.isMultiPress && (this.isMultiPress = e.isMultiPress);
        void 0 !== e.touchDownCount && (this.touchDownCount = e.touchDownCount);
        void 0 !== e.appEventBus && (this.appEventBus = e.appEventBus);
        void 0 !== e.itemPadding && (this.itemPadding = e.itemPadding);
        void 0 !== e.textInputPadding && (this.textInputPadding = e.textInputPadding)
    }

    updateStateVars(e) {
        this.__item.set(e.item)
    }

    purgeVariableDependenciesOnElmtId(e) {
        this.__item.purgeDependencyOnElmtId(e);
        this.__columnWidth.purgeDependencyOnElmtId(e);
        this.__isFocused.purgeDependencyOnElmtId(e);
        this.__index.purgeDependencyOnElmtId(e);
        this.__lastIndex.purgeDependencyOnElmtId(e);
        this.__count.purgeDependencyOnElmtId(e)
    }

    aboutToBeDeleted() {
        this.__item.aboutToBeDeleted();
        this.__columnWidth.aboutToBeDeleted();
        this.__isFocused.aboutToBeDeleted();
        this.__index.aboutToBeDeleted();
        this.__lastIndex.aboutToBeDeleted();
        this.__count.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal()
    }

    get item() {
        return this.__item.get()
    }

    get columnWidth() {
        return this.__columnWidth.get()
    }

    set columnWidth(e) {
        this.__columnWidth.set(e)
    }

    get isFocused() {
        return this.__isFocused.get()
    }

    set isFocused(e) {
        this.__isFocused.set(e)
    }

    get index() {
        return this.__index.get()
    }

    set index(e) {
        this.__index.set(e)
    }

    get lastIndex() {
        return this.__lastIndex.get()
    }

    set lastIndex(e) {
        this.__lastIndex.set(e)
    }

    get count() {
        return this.__count.get()
    }

    set count(e) {
        this.__count.set(e)
    }

    aboutToAppear() {
        var e;
        this.item.getNodeItem().imageNode && (this.item.imageSource = null === (e = this.item.getNodeItem().imageNode) || void 0 === e ? void 0 : e.source)
    }

    checkInvalidPattern(e) {
        return new RegExp('/[\\\/:*?"<>|]/').test(e)
    }

    checkIsAllCN(e) {
        return new RegExp('/^[\u4e00-\u9fa5]+$/').test(e)
    }

    popupForShowTitle(e, t, i, o = null) {
        this.observeComponentCreation(((e, i) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            Row.create();
            Row.backgroundColor(t);
            Row.border({
                radius: {
                    id: -1,
                    type: 10002,
                    params: ['sys.float.ohos_id_elements_margin_horizontal_l'],
                    bundleName: '',
                    moduleName: ''
                }
            });
            Row.padding({
                left: {
                    id: -1,
                    type: 10002,
                    params: ['sys.float.ohos_id_elements_margin_horizontal_l'],
                    bundleName: '',
                    moduleName: ''
                },
                right: {
                    id: -1,
                    type: 10002,
                    params: ['sys.float.ohos_id_elements_margin_horizontal_l'],
                    bundleName: '',
                    moduleName: ''
                },
                top: {
                    id: -1,
                    type: 10002,
                    params: ['sys.float.ohos_id_card_margin_middle'],
                    bundleName: '',
                    moduleName: ''
                },
                bottom: {
                    id: -1,
                    type: 10002,
                    params: ['sys.float.ohos_id_card_margin_middle'],
                    bundleName: '',
                    moduleName: ''
                }
            });
            i || Row.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((t, o) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            Text.create(e);
            Text.fontSize({
                id: -1,
                type: 10002,
                params: ['sys.float.ohos_id_text_size_body2'],
                bundleName: '',
                moduleName: ''
            });
            Text.fontWeight('regular');
            Text.fontColor(i);
            o || Text.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        Text.pop();
        Row.pop()
    }

    builder(e = null) {
        this.observeComponentCreation(((e, t) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            If.create();
            this.listTreeViewMenu ? this.ifElseBranchUpdateFunction(0, (() => {
                this.listTreeViewMenu.bind(this)()
            })) : If.branchId(1);
            t || If.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        If.pop()
    }

    initialRender() {
        this.observeComponentCreation(((e, t) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            If.create();
            this.item.getNodeIsShow() ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation(((e, t) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(e);
                    Stack.create();
                    ViewStackProcessor.visualState('focused');
                    Stack.border({
                        radius: {
                            id: -1,
                            type: 10002,
                            params: ['sys.float.ohos_id_corner_radius_clicked'],
                            bundleName: '',
                            moduleName: ''
                        },
                        width: 2,
                        color: {
                            id: -1,
                            type: 10001,
                            params: ['sys.color.ohos_id_color_focused_outline'],
                            bundleName: '',
                            moduleName: ''
                        },
                        style: BorderStyle.Solid
                    });
                    ViewStackProcessor.visualState('normal');
                    Stack.border({
                        radius: {
                            id: -1,
                            type: 10002,
                            params: ['sys.float.ohos_id_corner_radius_clicked'],
                            bundleName: '',
                            moduleName: ''
                        },
                        width: 0
                    });
                    ViewStackProcessor.visualState();
                    t || Stack.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((e, t) => {
                    var i;
                    ViewStackProcessor.StartGetAccessRecordingFor(e);
                    Column.create();
                    Column.opacity(this.listNodeDataSource.getListItemOpacity(ObservedObject.GetRawObject(this.item)));
                    Column.onHover((e => {
                        e ? this.item.setNodeColor({
                            id: -1,
                            type: 10001,
                            params: ['sys.color.ohos_id_color_hover'],
                            bundleName: '',
                            moduleName: ''
                        }) : this.item.setNodeColor({
                            id: -1,
                            type: 10001,
                            params: ['sys.color.ohos_id_color_background_transparent'],
                            bundleName: '',
                            moduleName: ''
                        })
                    }));
                    Column.onTouch((e => {
                        var t, i, o;
                        this.count++;
                        if (this.count > 1) {
                            this.count--;
                            return
                        }
                        this.listNodeDataSource.setClickIndex(this.index);
                        let s = this.item.getNodeCurrentNodeId();
                        if (e.type === TouchType.Down) this.item.setNodeColor({
                            id: -1,
                            type: 10001,
                            params: ['sys.color.ohos_id_color_click_effect'],
                            bundleName: '',
                            moduleName: ''
                        }); else if (e.type === TouchType.Up) {
                            this.item.setNodeColor('#1A0A59F7');
                            this.item.fontColor = {
                                id: -1,
                                type: 10001,
                                params: ['sys.color.ohos_id_color_text_primary_activated'],
                                bundleName: '',
                                moduleName: ''
                            };
                            if (null !== this.item.getNodeItem().imageNode) {
                                null === (t = this.item.getNodeItem().imageNode) || void 0 === t || t.setImageSource(InteractionStatus.Selected);
                                this.listNodeDataSource.setImageSource(this.index, InteractionStatus.Selected);
                                this.item.imageSource = null === (i = this.item.getNodeItem().imageNode) || void 0 === i ? void 0 : i.source
                            }
                            null === (o = this.item.getNodeItem().mainTitleNode) || void 0 === o || o.setMainTitleSelected(!0);
                            this.lastIndex = this.index;
                            let e = { currentNodeId: s };
                            this.appEventBus.emit(TreeListenType.NODE_CLICK, e)
                        }
                        if (-1 !== this.listNodeDataSource.getLastIndex() && this.index !== this.listNodeDataSource.getLastIndex()) {
                            this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE,!1, this.listNodeDataSource.getLastIndex());
                            this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(), MenuOperation.COMMIT_NODE)
                        }
                        this.count--
                    }));
                    Column.backgroundColor(this.item.getNodeItem().mainTitleNode && this.item.getNodeItem().inputText && this.item.getIsShowInputText() ? null === (i = this.item.getNodeItem().inputText) || void 0 === i ? void 0 : i.editColor : this.item.getNodeColor());
                    Column.border({
                        width: this.item.getNodeBorder().borderWidth,
                        color: this.item.getNodeBorder().borderColor,
                        radius: this.item.getNodeBorder().borderRadius
                    });
                    Column.height(48);
                    Column.focusable(!0);
                    Column.onMouse((e => {
                        var t;
                        let i = findCurrentNodeIndex(this.listNodeDataSource, this.item.getNodeCurrentNodeId());
                        if (e.button === MouseButton.Right) {
                            this.listNodeDataSource.handleEvent(Event.MOUSE_BUTTON_RIGHT, findCurrentNodeIndex(this.listNodeDataSource, this.item.getNodeCurrentNodeId()));
                            this.listTreeViewMenu = this.item.getMenu();
                            this.listNodeDataSource.setClickIndex(i);
                            clearTimeout(null === (t = this.item.getNodeItem().mainTitleNode) || void 0 === t ? void 0 : t.popUpTimeout)
                        }
                        e.stopPropagation()
                    }));
                    Column.padding({ top: 0, bottom: 0 });
                    Column.bindPopup(this.item.getPopUpInfo().popUpIsShow, {
                        builder: { builder: () => {
                            this.popupForShowTitle.call(this, this.item.getPopUpInfo().popUpText, this.item.getPopUpInfo().popUpColor, this.item.getPopUpInfo().popUpTextColor)
                        } },
                        placement: Placement.BottomLeft,
                        placementOnTop: !1,
                        popupColor: this.item.getPopUpInfo().popUpColor,
                        autoCancel: !0,
                        enableArrow: this.item.getPopUpInfo().popUpEnableArrow
                    });
                    Column.onAreaChange(((e, t) => {
                        let i = Number.parseInt(t.width.toString());
                        this.columnWidth = i
                    }));
                    t || Column.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((e, t) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(e);
                    Stack.create({ alignContent: Alignment.Bottom });
                    Stack.focusable(!0);
                    t || Stack.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((e, t) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(e);
                    Divider.create();
                    Divider.height(this.listNodeDataSource.getFlagLine().flagLineHeight);
                    Divider.color(this.listNodeDataSource.getFlagLine().flagLineColor);
                    Divider.visibility(this.listNodeDataSource.getVisibility(ObservedObject.GetRawObject(this.item)));
                    Divider.lineCap(LineCapStyle.Round);
                    Divider.margin({ left: this.item.getFlagLineLeftMargin() });
                    Divider.focusable(!0);
                    t || Divider.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((e, t) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(e);
                    Row.create({});
                    Row.focusable(!0);
                    Row.width('100%');
                    Gesture.create(GesturePriority.Low);
                    TapGesture.create({ count: 2 });
                    TapGesture.onAction((e => {
                        this.listNodeDataSource.expandAndCollapseNode(findCurrentNodeIndex(this.listNodeDataSource, this.item.getNodeCurrentNodeId()))
                    }));
                    TapGesture.pop();
                    Gesture.pop();
                    Row.height(this.item.getNodeHeight());
                    Row.padding({ left: this.item.getNodeLeftPadding() });
                    Row.bindContextMenu({ builder: this.builder.bind(this) }, ResponseType.RightClick);
                    t || Row.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((e, t) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(e);
                    If.create();
                    this.item.getNodeItem().imageNode ? this.ifElseBranchUpdateFunction(0, (() => {
                        this.observeComponentCreation(((e, t) => {
                            var i, o, s;
                            ViewStackProcessor.StartGetAccessRecordingFor(e);
                            Row.create();
                            Row.focusable(!0);
                            Row.backgroundColor('#00000000');
                            Row.margin({
                                right: null === (i = this.item.getNodeItem().imageNode) || void 0 === i ? void 0 : i.itemRightMargin
                            });
                            Row.height(null === (o = this.item.getNodeItem().imageNode) || void 0 === o ? void 0 : o.itemHeight);
                            Row.width(null === (s = this.item.getNodeItem().imageNode) || void 0 === s ? void 0 : s.itemWidth);
                            t || Row.pop();
                            ViewStackProcessor.StopGetAccessRecording()
                        }));
                        this.observeComponentCreation(((e, t) => {
                            var i, o, s, d;
                            ViewStackProcessor.StartGetAccessRecordingFor(e);
                            Image.create(this.item.imageSource);
                            Image.objectFit(ImageFit.Contain);
                            Image.height(null === (i = this.item.getNodeItem().imageNode) || void 0 === i ? void 0 : i.itemHeight);
                            Image.width(null === (o = this.item.getNodeItem().imageNode) || void 0 === o ? void 0 : o.itemWidth);
                            Image.opacity(this.item.getIsSelected() || this.item.getIsHighLight() ? null === (d = this.item.getNodeItem().imageNode) || void 0 === d ? void 0 : d.noOpacity : null === (s = this.item.getNodeItem().imageNode) || void 0 === s ? void 0 : s.opacity);
                            Image.focusable(null === this.item.getNodeItem().mainTitleNode);
                            t || Image.pop();
                            ViewStackProcessor.StopGetAccessRecording()
                        }));
                        Row.pop()
                    })) : If.branchId(1);
                    t || If.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                If.pop();
                this.observeComponentCreation(((e, t) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(e);
                    Row.create();
                    Row.layoutWeight(1);
                    Row.focusable(!0);
                    t || Row.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((e, t) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(e);
                    If.create();
                    this.item.getNodeItem().mainTitleNode && this.item.getIsShowTitle() ? this.ifElseBranchUpdateFunction(0, (() => {
                        this.observeComponentCreation(((e, t) => {
                            var i, o, s, d;
                            ViewStackProcessor.StartGetAccessRecordingFor(e);
                            Text.create(null === (i = this.item.getNodeItem().mainTitleNode) || void 0 === i ? void 0 : i.title);
                            Text.maxLines(1);
                            Text.fontSize(null === (o = this.item.getNodeItem().mainTitleNode) || void 0 === o ? void 0 : o.size);
                            Text.fontColor(this.item.fontColor);
                            Text.margin({
                                right: null === (s = this.item.getNodeItem().mainTitleNode) || void 0 === s ? void 0 : s.itemRightMargin
                            });
                            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                            Text.fontWeight(null === (d = this.item.getNodeItem().mainTitleNode) || void 0 === d ? void 0 : d.weight);
                            Text.focusable(!0);
                            t || Text.pop();
                            ViewStackProcessor.StopGetAccessRecording()
                        }));
                        Text.pop()
                    })) : If.branchId(1);
                    t || If.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                If.pop();
                this.observeComponentCreation(((e, t) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(e);
                    If.create();
                    this.item.getNodeItem().mainTitleNode && this.item.getNodeItem().inputText && this.item.getIsShowInputText() ? this.ifElseBranchUpdateFunction(0, (() => {
                        this.observeComponentCreation(((e, t) => {
                            var i, o, s;
                            ViewStackProcessor.StartGetAccessRecordingFor(e);
                            Row.create();
                            Row.backgroundColor(null === (i = this.item.getNodeItem().inputText) || void 0 === i ? void 0 : i.backgroundColor);
                            Row.borderRadius(null === (o = this.item.getNodeItem().inputText) || void 0 === o ? void 0 : o.borderRadius);
                            Row.margin({
                                right: null === (s = this.item.getNodeItem().inputText) || void 0 === s ? void 0 : s.itemRightMargin
                            });
                            t || Row.pop();
                            ViewStackProcessor.StopGetAccessRecording()
                        }));
                        this.observeComponentCreation(((e, t) => {
                            var i, o, s, d, a, r;
                            ViewStackProcessor.StartGetAccessRecordingFor(e);
                            TextInput.create({
                                text: null === (i = this.item.getNodeItem().mainTitleNode) || void 0 === i ? void 0 : i.title
                            });
                            TextInput.height(null === (o = this.item.getNodeItem().inputText) || void 0 === o ? void 0 : o.itemHeight);
                            TextInput.fontSize(null === (s = this.item.getNodeItem().inputText) || void 0 === s ? void 0 : s.size);
                            TextInput.fontColor(null === (d = this.item.getNodeItem().inputText) || void 0 === d ? void 0 : d.color);
                            TextInput.borderRadius(null === (a = this.item.getNodeItem().inputText) || void 0 === a ? void 0 : a.borderRadius);
                            TextInput.backgroundColor(null === (r = this.item.getNodeItem().inputText) || void 0 === r ? void 0 : r.backgroundColor);
                            TextInput.enterKeyType(EnterKeyType.Done);
                            TextInput.focusable(!0);
                            TextInput.padding({
                                left: this.textInputPadding.left,
                                right: this.textInputPadding.right,
                                top: this.textInputPadding.top,
                                bottom: this.textInputPadding.bottom
                            });
                            TextInput.onChange((e => {
                                let t = findCurrentNodeIndex(this.listNodeDataSource, this.item.getNodeCurrentNodeId());
                                let i = '';
                                let o = !1;
                                let s = !1;
                                if (this.checkInvalidPattern(e)) {
                                    for (let t = 0; t < e.length; t++) this.checkInvalidPattern(e[t]) || (i += e[t]);
                                    o = !0;
                                    this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.INVALID_ERROR,!0, t)
                                } else {
                                    i = e;
                                    o = !1
                                }
                                if (this.checkIsAllCN(i) && i.length > this.MAX_CN_LENGTH || !this.checkIsAllCN(i) && i.length > this.MAX_EN_LENGTH) {
                                    i = this.checkIsAllCN(i) ? i.substr(0, this.MAX_CN_LENGTH) : i.substr(0, this.MAX_EN_LENGTH);
                                    s = !0;
                                    this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.LENGTH_ERROR,!0, t)
                                } else s = !1;
                                s || o || this.listNodeDataSource.setMainTitleNameOnEdit(t, i)
                            }));
                            TextInput.onSubmit((e => {
                                let t = findCurrentNodeIndex(this.listNodeDataSource, this.item.getNodeCurrentNodeId());
                                this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE,!1, t);
                                this.listNodeDataSource.setItemVisibilityOnEdit(t, MenuOperation.COMMIT_NODE)
                            }));
                            t || TextInput.pop();
                            ViewStackProcessor.StopGetAccessRecording()
                        }));
                        Row.pop()
                    })) : If.branchId(1);
                    t || If.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                If.pop();
                this.observeComponentCreation(((e, t) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(e);
                    Blank.create();
                    t || Blank.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                Blank.pop();
                Row.pop();
                this.observeComponentCreation(((e, t) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(e);
                    If.create();
                    this.listNodeDataSource.hasSubtitle(this.item.getCurrentNodeId()) ? this.ifElseBranchUpdateFunction(0, (() => {
                        this.observeComponentCreation(((e, t) => {
                            ViewStackProcessor.StartGetAccessRecordingFor(e);
                            Row.create();
                            Row.focusable(!0);
                            Row.margin({
                                left: this.listNodeDataSource.getSubTitlePara().margin.left,
                                right: this.item.getNodeItem().imageCollapse ? 0 : this.listNodeDataSource.getSubTitlePara().margin.right
                            });
                            t || Row.pop();
                            ViewStackProcessor.StopGetAccessRecording()
                        }));
                        this.observeComponentCreation(((e, t) => {
                            ViewStackProcessor.StartGetAccessRecordingFor(e);
                            Text.create(this.listNodeDataSource.getSubtitle(this.item.getCurrentNodeId()));
                            Text.fontSize(this.listNodeDataSource.getSubTitlePara().fontSize);
                            Text.fontColor(this.listNodeDataSource.getSubTitleFontColor(this.item.getIsHighLight() || this.item.getIsModify()));
                            Text.fontWeight(this.listNodeDataSource.getSubTitlePara().fontWeight);
                            t || Text.pop();
                            ViewStackProcessor.StopGetAccessRecording()
                        }));
                        Text.pop();
                        Row.pop()
                    })) : If.branchId(1);
                    t || If.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                If.pop();
                this.observeComponentCreation(((e, t) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(e);
                    If.create();
                    this.item.getNodeItem().imageCollapse ? this.ifElseBranchUpdateFunction(0, (() => {
                        this.observeComponentCreation(((e, t) => {
                            var i, o;
                            ViewStackProcessor.StartGetAccessRecordingFor(e);
                            Row.create();
                            Row.focusable(!0);
                            Row.height(null === (i = this.item.getNodeItem().imageCollapse) || void 0 === i ? void 0 : i.itemHeight);
                            Row.width(null === (o = this.item.getNodeItem().imageCollapse) || void 0 === o ? void 0 : o.itemWidth);
                            t || Row.pop();
                            ViewStackProcessor.StopGetAccessRecording()
                        }));
                        this.observeComponentCreation(((e, t) => {
                            var i, o, s, d, a, r;
                            ViewStackProcessor.StartGetAccessRecordingFor(e);
                            Image.create(null === (i = this.item.getNodeItem().imageCollapse) || void 0 === i ? void 0 : i.collapseSource);
                            Image.fillColor((null === (o = this.item.getNodeItem().imageCollapse) || void 0 === o ? void 0 : o.isCollapse) ? '#00000000' : '#FFFFFF');
                            Image.align(Alignment.End);
                            Image.objectFit(ImageFit.Contain);
                            Image.height(null === (s = this.item.getNodeItem().imageCollapse) || void 0 === s ? void 0 : s.itemHeight);
                            Image.width(null === (d = this.item.getNodeItem().imageCollapse) || void 0 === d ? void 0 : d.itemWidth);
                            Image.opacity(this.item.getIsHighLight() ? null === (r = this.item.getNodeItem().imageCollapse) || void 0 === r ? void 0 : r.noOpacity : null === (a = this.item.getNodeItem().imageCollapse) || void 0 === a ? void 0 : a.opacity);
                            Image.onTouch((e => {
                                if (e.type === TouchType.Down) {
                                    this.listNodeDataSource.expandAndCollapseNode(findCurrentNodeIndex(this.listNodeDataSource, this.item.getNodeCurrentNodeId()));
                                    this.listNodeDataSource.setCurrentFocusNodeId(this.item.getCurrentNodeId())
                                }
                                e.stopPropagation()
                            }));
                            Image.focusable(!0);
                            t || Image.pop();
                            ViewStackProcessor.StopGetAccessRecording()
                        }));
                        Row.pop()
                    })) : If.branchId(1);
                    t || If.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                If.pop();
                Row.pop();
                Stack.pop();
                Column.pop();
                Stack.pop()
            })) : If.branchId(1);
            t || If.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        If.pop()
    }

    rerender() {
        this.updateDirtyElements()
    }
}

export class NodeItem {
    constructor(e) {
        this.data = e;
        this.nodeLevel = -1;
        this.parentNodeId = -1;
        this.currentNodeId = -1;
        this.nodeItem = {
            imageNode: void 0,
            inputText: new InputText,
            mainTitleNode: new MainTitleNode(''),
            imageCollapse: void 0,
            fontColor: void 0
        };
        this.childNodeInfo = { isHasChildNode: !1, childNum: 0, allChildNum: 0 };
        this.container = e.container;
        e.icon && (this.nodeItem.imageNode = new ImageNode(e.icon, {
            id: -1,
            type: 10002,
            params: ['sys.float.ohos_id_alpha_content_fourth'],
            bundleName: '',
            moduleName: ''
        }, 24, 24, e.selectedIcon, e.editIcon));
        e.primaryTitle && (this.nodeItem.mainTitleNode = new MainTitleNode(e.primaryTitle));
        this.children = []
    }

    addImageCollapse(e) {
        if (e) {
            this.nodeItem.imageCollapse = new ImageNode(ARROW_RIGHT, {
                id: -1,
                type: 10002,
                params: ['sys.float.ohos_id_alpha_content_tertiary'],
                bundleName: '',
                moduleName: ''
            }, 24, 24, void 0, void 0);
            this.nodeItem.imageCollapse.itemRightMargin = {
                id: -1,
                type: 10002,
                params: ['sys.float.ohos_id_text_paragraph_margin_xs'],
                bundleName: '',
                moduleName: ''
            }
        } else this.nodeItem.imageCollapse = void 0
    }

    getNodeItem() {
        return this.nodeItem
    }

    getChildNodeInfo() {
        return this.childNodeInfo
    }

    getMenu() {
        return this.container
    }

    getCurrentNodeId() {
        return this.currentNodeId
    }

    getIsFolder() {
        return this.data.isFolder
    }
}

class NodeBaseInfo {
    constructor() {
        this.rightMargin = -1;
        this.width = -1;
        this.height = -1
    }

    set itemWidth(e) {
        this.width = e
    }

    get itemWidth() {
        return this.width
    }

    set itemHeight(e) {
        this.height = e
    }

    get itemHeight() {
        return this.height
    }

    set itemRightMargin(e) {
        this.rightMargin = e
    }

    get itemRightMargin() {
        return this.rightMargin
    }
}

export class ImageNode extends NodeBaseInfo {
    constructor(e, t, i, o, s, d) {
        super();
        this.rightMargin = {
            id: -1,
            type: 10002,
            params: ['sys.float.ohos_id_elements_margin_horizontal_m'],
            bundleName: '',
            moduleName: ''
        };
        this.imageSource = e;
        this.imageNormalSource = e;
        this.imageSelectedSource = void 0 !== s ? s : this.imageNormalSource;
        this.imageEditSource = void 0 !== d ? d : this.imageNormalSource;
        this.imageOpacity = t;
        this.itemWidth = i;
        this.itemHeight = o;
        this.imageCollapseSource = e;
        this.imageCollapseDownSource = ARROW_DOWN;
        this.imageCollapseRightSource = ARROW_RIGHT;
        this.isImageCollapse = !0;
        this.currentInteractionStatus = InteractionStatus.Normal
    }

    get source() {
        return this.imageSource
    }

    get normalSource() {
        return this.imageNormalSource
    }

    get selectedSource() {
        return this.imageSelectedSource
    }

    get editSource() {
        return this.imageEditSource
    }

    get opacity() {
        return this.imageOpacity
    }

    get noOpacity() {
        return 1
    }

    get collapseSource() {
        return this.imageCollapseSource
    }

    get isCollapse() {
        return this.isImageCollapse
    }

    changeImageCollapseSource(e) {
        e === NodeStatus.Expand ? this.imageCollapseSource = this.imageCollapseDownSource : e === NodeStatus.Collapse && (this.imageCollapseSource = this.imageCollapseRightSource)
    }

    setImageCollapseSource(e, t) {
        if (e === InteractionStatus.Edit || e === InteractionStatus.DragInsert) {
            this.imageCollapseDownSource = ARROW_DOWN_WITHE;
            this.imageCollapseRightSource = ARROW_RIGHT_WITHE;
            this.isImageCollapse = !1
        } else if (e === InteractionStatus.FinishEdit || e === InteractionStatus.FinishDragInsert) {
            this.imageCollapseDownSource = ARROW_DOWN;
            this.imageCollapseRightSource = ARROW_RIGHT;
            this.isImageCollapse = !0
        }
        this.imageCollapseSource = t === NodeStatus.Collapse ? this.imageCollapseRightSource : this.imageCollapseDownSource
    }

    setImageSource(e) {
        switch (e) {
            case InteractionStatus.Normal:
                this.imageSource = this.imageNormalSource;
                this.currentInteractionStatus = e;
                break;
            case InteractionStatus.Selected:
                if (this.currentInteractionStatus !== InteractionStatus.Edit) {
                    this.imageSource = this.imageSelectedSource;
                    this.currentInteractionStatus = e
                }
                break;
            case InteractionStatus.Edit:
                this.imageSource = this.imageEditSource;
                this.currentInteractionStatus = e;
                break;
            case InteractionStatus.FinishEdit:
                this.imageSource = this.imageSelectedSource;
                this.currentInteractionStatus = e;
                break;
            case InteractionStatus.DragInsert:
                this.imageSource = this.imageEditSource;
                this.currentInteractionStatus = e;
                break;
            case InteractionStatus.FinishDragInsert:
                this.imageSource = this.imageNormalSource;
                this.currentInteractionStatus = e
        }
    }
}

class MainTitleNode extends NodeBaseInfo {
    constructor(e) {
        super();
        this.mainTitleName = e;
        this.itemWidth = 0;
        this.itemHeight = 48;
        this.rightMargin = {
            id: -1,
            type: 10002,
            params: ['sys.float.ohos_id_text_paragraph_margin_xs'],
            bundleName: '',
            moduleName: ''
        };
        this.mainTitleSetting = {
            fontColor: {
                id: -1,
                type: 10001,
                params: ['sys.color.ohos_id_color_primary'],
                bundleName: '',
                moduleName: ''
            },
            fontSize: {
                id: -1,
                type: 10002,
                params: ['sys.float.ohos_id_text_size_body1'],
                bundleName: '',
                moduleName: ''
            },
            fontWeight: FontWeight.Normal
        };
        this.showPopUpTimeout = 0
    }

    setMainTitleSelected(e) {
        this.mainTitleSetting = e ? {
            fontColor: {
                id: -1,
                type: 10001,
                params: ['sys.color.ohos_id_color_text_primary_activated'],
                bundleName: '',
                moduleName: ''
            },
            fontSize: {
                id: -1,
                type: 10002,
                params: ['sys.float.ohos_id_text_size_body1'],
                bundleName: '',
                moduleName: ''
            },
            fontWeight: FontWeight.Regular
        } : {
            fontColor: {
                id: -1,
                type: 10001,
                params: ['sys.color.ohos_id_color_primary'],
                bundleName: '',
                moduleName: ''
            },
            fontSize: {
                id: -1,
                type: 10002,
                params: ['sys.float.ohos_id_text_size_body1'],
                bundleName: '',
                moduleName: ''
            },
            fontWeight: FontWeight.Normal
        }
    }

    set title(e) {
        this.mainTitleName = e
    }

    get title() {
        return this.mainTitleName
    }

    set popUpTimeout(e) {
        this.showPopUpTimeout = e
    }

    get popUpTimeout() {
        return this.showPopUpTimeout
    }

    get color() {
        return this.mainTitleSetting.fontColor
    }

    get size() {
        return this.mainTitleSetting.fontSize
    }

    get weight() {
        return this.mainTitleSetting.fontWeight
    }

    setMainTitleHighLight(e) {
        this.mainTitleSetting = e ? {
            fontColor: {
                id: -1,
                type: 10001,
                params: ['sys.color.ohos_id_color_primary_contrary'],
                bundleName: '',
                moduleName: ''
            },
            fontSize: {
                id: -1,
                type: 10002,
                params: ['sys.float.ohos_id_text_size_body1'],
                bundleName: '',
                moduleName: ''
            },
            fontWeight: FontWeight.Regular
        } : {
            fontColor: {
                id: -1,
                type: 10001,
                params: ['sys.color.ohos_id_color_primary'],
                bundleName: '',
                moduleName: ''
            },
            fontSize: {
                id: -1,
                type: 10002,
                params: ['sys.float.ohos_id_text_size_body1'],
                bundleName: '',
                moduleName: ''
            },
            fontWeight: FontWeight.Normal
        }
    }
}

export class InputText extends NodeBaseInfo {
    constructor() {
        super();
        this.status = void 0;
        this.statusColor = {
            id: -1,
            type: 10001,
            params: ['sys.color.ohos_id_color_background'],
            bundleName: '',
            moduleName: ''
        };
        this.editItemColor = {
            id: -1,
            type: 10001,
            params: ['sys.color.ohos_id_color_emphasize'],
            bundleName: '',
            moduleName: ''
        };
        this.radius = {
            id: -1,
            type: 10002,
            params: ['sys.float.ohos_id_corner_radius_default_xs'],
            bundleName: '',
            moduleName: ''
        };
        this.itemWidth = 0;
        this.itemHeight = 32;
        this.rightMargin = {
            id: -1,
            type: 10002,
            params: ['sys.float.ohos_id_text_paragraph_margin_xs'],
            bundleName: '',
            moduleName: ''
        };
        this.inputTextSetting = {
            fontColor: {
                id: -1,
                type: 10001,
                params: ['sys.color.ohos_id_color_text_primary'],
                bundleName: '',
                moduleName: ''
            },
            fontSize: {
                id: -1,
                type: 10002,
                params: ['sys.float.ohos_id_text_size_body1'],
                bundleName: '',
                moduleName: ''
            },
            fontWeight: FontWeight.Normal
        }
    }

    get color() {
        return this.inputTextSetting.fontColor
    }

    get size() {
        return this.inputTextSetting.fontSize
    }

    get weight() {
        return this.inputTextSetting.fontWeight
    }

    get borderRadius() {
        return this.radius
    }

    get backgroundColor() {
        return this.statusColor
    }

    get editColor() {
        return this.editItemColor
    }

    get textInputStatusColor() {
        return this.status
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
        this.addNewNodeId = -1
    }

    getNewNodeId() {
        return this.addNewNodeId
    }

    traverseNodeDF(e, t = this._root) {
        let i = [], o = !1;
        i.unshift(t);
        let s = i.shift();
        for (;!o && s; ) {
            o = !0 === e(s);
            if (!o) {
                i.unshift(...s.children);
                s = i.shift()
            }
        }
    }

    traverseNodeBF(e) {
        let t = [];
        let i = !1;
        t.push(this._root);
        let o = t.shift();
        for (;!i && o; ) {
            try {
                i = e(o)
            } catch (e) {
                throw new Error('traverseNodeBF function callbacks error.')
            }
            if (!i) {
                t.push(...o.children);
                o = t.shift()
            }
        }
    }

    contains(e, t) {
        t(e)
    }

    updateParentChildNum(e, t, i) {
        let o = e.parentNodeId;
        for (; o >= 0; ) this.traverseNodeDF((e => {
            if (e.currentNodeId === o) {
                e.getChildNodeInfo().allChildNum = t ? e.getChildNodeInfo().allChildNum + i : e.getChildNodeInfo().allChildNum - i;
                o = e.parentNodeId;
                return !1
            }
            return !1
        }))
    }

    findParentNodeId(e) {
        let t = new NodeItem(emptyNodeInfo);
        this.traverseNodeBF((i => {
            if (i.currentNodeId === e) {
                t = i;
                return !0
            }
            return !1
        }));
        return t.parentNodeId
    }

    addNode(e, t, i) {
        if (null === this._root) {
            this._root = new NodeItem(emptyNodeInfo);
            this._root.nodeLevel = -1;
            this._root.parentNodeId = -1;
            this._root.currentNodeId = -1
        }
        let o = new NodeItem(emptyNodeInfo);
        this.traverseNodeBF((t => {
            if (t.currentNodeId === e) {
                o = t;
                return !0
            }
            return !1
        }));
        if (o) {
            let s = new NodeItem(i);
            if (o.nodeLevel > this.MaxNodeLevel) throw new Error('ListNodeUtils[addNode]: The level of the tree view cannot exceed 50.');
            s.nodeLevel = o.nodeLevel + 1;
            s.parentNodeId = e;
            s.currentNodeId = t;
            o.children.push(s);
            o.getChildNodeInfo().isHasChildNode = !0;
            o.getChildNodeInfo().childNum = o.children.length;
            o.getChildNodeInfo().allChildNum += 1;
            o.addImageCollapse(o.getChildNodeInfo().isHasChildNode);
            this.updateParentChildNum(o,!0, 1);
            return this
        }
        throw new Error('ListNodeUtils[addNode]: Parent node not found.')
    }

    findNodeIndex(e, t) {
        let i = this.INITIAL_INVALID_VALUE;
        for (let o = 0, s = e.length; o < s; o++) if (e[o].currentNodeId === t) {
            i = o;
            break
        }
        return i
    }

    freeNodeMemory(e, t) {
        let i = [];
        this.traverseNodeDF((e => {
            i.push(e);
            return !1
        }), e);
        i.forEach((e => {
            t.push(e.currentNodeId);
            e = new NodeItem(emptyNodeInfo)
        }))
    }

    removeNode(e, t) {
        let i = new NodeItem(emptyNodeInfo);
        this.traverseNodeBF((e => {
            if (e.currentNodeId === t) {
                i = e;
                return !0
            }
            return !1
        }));
        if (i) {
            let t = [];
            let o = this.findNodeIndex(i.children, e);
            let s = 0;
            if (o < 0) throw new Error('Node does not exist.');
            {
                s = i.children[o].getChildNodeInfo().allChildNum + 1;
                this.freeNodeMemory(i.children[o], t);
                let e = i.children.splice(o, 1);
                e = null;
                0 === i.children.length && i.addImageCollapse(!1)
            }
            i.getChildNodeInfo().childNum = i.children.length;
            i.getChildNodeInfo().allChildNum -= s;
            this.updateParentChildNum(i,!1, s);
            return t
        }
        throw new Error('Parent does not exist.')
    }

    getNewNodeInfo(e) {
        var t, i, o, s, d, a;
        let r = new NodeItem(emptyNodeInfo);
        this.traverseNodeBF((t => {
            if (t.currentNodeId === e) {
                r = t;
                return !0
            }
            return !1
        }));
        let n = emptyNodeInfo;
        if (r) if (0 === r.children.length) if (void 0 !== r.getNodeItem().imageNode) {
            n.icon = null === (t = r.getNodeItem().imageNode) || void 0 === t ? void 0 : t.normalSource;
            n.selectedIcon = null === (i = r.getNodeItem().imageNode) || void 0 === i ? void 0 : i.selectedSource;
            n.editIcon = null === (o = r.getNodeItem().imageNode) || void 0 === o ? void 0 : o.editSource;
            n.container = r.getMenu()
        } else {
            n.icon = void 0;
            n.selectedIcon = void 0;
            n.editIcon = void 0;
            n.container = r.getMenu()
        } else if (r.children.length > 0) if (null !== r.getNodeItem().imageNode) {
            n.icon = void 0 !== r.children[0].getNodeItem().imageNode ? null === (s = r.children[0].getNodeItem().imageNode) || void 0 === s ? void 0 : s.normalSource : void 0;
            n.selectedIcon = void 0 !== r.children[0].getNodeItem().imageNode ? null === (d = r.children[0].getNodeItem().imageNode) || void 0 === d ? void 0 : d.selectedSource : void 0;
            n.editIcon = void 0 !== r.children[0].getNodeItem().imageNode ? null === (a = r.children[0].getNodeItem().imageNode) || void 0 === a ? void 0 : a.editSource : void 0;
            n.container = r.children[0].getMenu()
        } else {
            n.icon = void 0;
            n.selectedIcon = void 0;
            n.editIcon = void 0;
            n.container = r.children[0].getMenu()
        }
        return n
    }

    getClickChildId(e) {
        let t = new NodeItem(emptyNodeInfo);
        this.traverseNodeBF((i => {
            if (i.currentNodeId === e) {
                t = i;
                return !0
            }
            return !1
        }));
        if (t) {
            if (0 === t.children.length) return [];
            if (t.children.length > 0) {
                let e = new Array(t.children.length);
                for (let t = 0; t < e.length; t++) e[t] = 0;
                for (let i = 0; i < t.children.length && i < e.length; i++) e[i] = t.children[i].currentNodeId;
                return e
            }
        }
        return []
    }

    getClickNodeChildrenInfo(e) {
        var t, i;
        let o = new NodeItem(emptyNodeInfo);
        this.traverseNodeBF((t => {
            if (t.currentNodeId === e) {
                o = t;
                return !0
            }
            return !1
        }));
        if (o) {
            if (0 === o.children.length) return [];
            if (o.children.length > 0) {
                let e = new Array(o.children.length);
                for (let t = 0; t < e.length; t++) e[t] = {};
                for (let s = 0; s < o.children.length && s < e.length; s++) {
                    e[s].itemId = o.children[s].currentNodeId;
                    o.children[s].getNodeItem().imageNode && (e[s].itemIcon = null === (t = o.children[s].getNodeItem().imageNode) || void 0 === t ? void 0 : t.source);
                    o.children[s].getNodeItem().mainTitleNode && (e[s].itemTitle = null === (i = o.children[s].getNodeItem().mainTitleNode) || void 0 === i ? void 0 : i.title);
                    e[s].isFolder = o.children[s].getIsFolder()
                }
                return e
            }
        }
        return []
    }

    checkMainTitleIsValid(e) {
        return!new RegExp('/[\\/:*?"<>|]/').test(e) && !(new RegExp('/^[\u4e00-\u9fa5]+$/').test(e) && e.length > this.MAX_CN_LENGTH || !new RegExp('/^[\u4e00-\u9fa5]+$/').test(e) && e.length > this.MAX_EN_LENGTH)
    }

    dragTraverseNodeDF(e, t = this._root, i) {
        let o = [], s = !1;
        o.unshift(t);
        let d = o.shift();
        for (;!s && d; ) {
            s = !0 === e(d, i);
            if (!s) {
                o.unshift(...d.children);
                d = o.shift()
            }
        }
    }

    addDragNode(e, t, i, o, s) {
        if (null === this._root) {
            this._root = new NodeItem(emptyNodeInfo);
            this._root.nodeLevel = this.INITIAL_INVALID_VALUE;
            this._root.parentNodeId = this.INITIAL_INVALID_VALUE;
            this._root.currentNodeId = this.INITIAL_INVALID_VALUE
        }
        let d = new NodeItem(emptyNodeInfo);
        this.traverseNodeBF((t => {
            if (t.currentNodeId === e) {
                d = t;
                return !0
            }
            return !1
        }));
        if (d) {
            let a = new NodeItem(s);
            if (d.nodeLevel > this.MaxNodeLevel) throw new Error('ListNodeUtils[addNode]: The level of the tree view cannot exceed 50.');
            a.nodeLevel = d.nodeLevel + 1;
            a.parentNodeId = e;
            a.currentNodeId = t;
            let r = this.INITIAL_INVALID_VALUE;
            if (d.children.length) {
                for (let e = 0; e < d.children.length; e++) if (d.children[e].getCurrentNodeId() === i) {
                    r = e;
                    break
                }
                o ? d.children.splice(r + 1, 0, a) : d.children.splice(r, 0, a)
            } else d.children.push(a);
            d.getChildNodeInfo().isHasChildNode = !0;
            d.getChildNodeInfo().childNum = d.children.length;
            d.getChildNodeInfo().allChildNum += 1;
            d.addImageCollapse(d.getChildNodeInfo().isHasChildNode);
            this.updateParentChildNum(d,!0, 1);
            return this
        }
        throw new Error('ListNodeUtils[addNode]: Parent node not found.')
    }
}

export default { TreeController, TreeListener, TreeListenerManager, TreeListenType, TreeView }