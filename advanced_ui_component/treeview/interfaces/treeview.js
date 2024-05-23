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

var __decorate = (this && this.__decorate) || function (i27, j27, k27, l27) {
    var m27 = arguments.length,
        n27 = m27 < 3 ? j27 : l27 === null ? l27 = Object.getOwnPropertyDescriptor(j27, k27) : l27, o27;
    if (typeof Reflect === 'object' && typeof Reflect.decorate === 'function')
        n27 = Reflect.decorate(i27, j27, k27, l27);
    else
        for (var p27 = i27.length - 1; p27 >= 0; p27--)
            if (o27 = i27[p27])
                n27 = (m27 < 3 ? o27(n27) : m27 > 3 ? o27(j27, k27, n27) : o27(j27, k27)) || n27;
    return m27 > 3 && n27 && Object.defineProperty(j27, k27, n27), n27;
};
if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {
    });
}
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
const ARROW_DOWN = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAGAAAABgCAYAAADimHc4AAAAIGNIUk0AAHomAACAhAAA+' +
    'gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAAEZ0FNQQAAsY58+1GTAAAAAXNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAAlwSFlzA' +
    'AAOxAAADsQBlSsOGwAAAq9JREFUeNrt2j9rFEEYx/FJziIECwsLCwsJIVhYiISgaIhiioiIlpaCjZ1/qhNUIkHE0negpZggEnwHFgoWFiJic' +
    'VyRQsQXIHKIvyGzIJKbmTW7M7P6/cCvyR3c7fPsPLO7F2MAAAAAAAAAAAAAAAAAAAAAAAAAAF01keAz9ihrymVln/JEua18L7w2V5TrykHlt' +
    'XJTGTb9Ib0EB/JYueWKP6Ucd3mh/Ci0+Hfc9z6gTCuHlUvK06ZPnMkEB3Nth78tK89dQ0os/toOfz+kHG36w1I0YNwZs6JsFtaEccVvTYoGr' +
    'HteW3ajaKoDxbfz/10X94BXyoIyO+b1Wbcn2JE0ylT8VeW+5/UtZUn52sUG/FQ23PycG/OeGWXevW+U4cwPFf+MMmjjw3uJDnLkRo2vCTlWQ' +
    'l954Hn9i3Je+djWF+glPNNimlCthJcJLlH7buZPemb+ovKpzS/RS7zcqybMB/aEhZZXwmqg+NXMH7ZdkNQNqJrwLLAxz7Q4jkIzf5iq+LkaU' +
    'GdjbroJoUvNb674g1SFyNWAOntCU48tYq7zzyqfUxYhZwPqNOHYLi9RQ8XfylH8EhpQZ2P+23EUU/zFlGOntAbU2Zjr3qyF7nCrsTPIdeClN' +
    'CB2Y66zEvoRG26WsVNqA+rerPlWwg3lYeAmayl38UtsQBOPLezMfxRxkzUo4WBLbEDsxmxXwinlrRsn+5W7yr1SbrJiTJiy2d+T7Y82K4H32' +
    'QbsNf7fFeyDtRMlFb/kFVBnY7amXbN8l5oXTYtPNf/VBsTuCSZQfPs8/0OJB9eFBuymCXbsnCxlw+1yA2I35j+Lf860/Dz/f2rA73fMdhUc8' +
    'bzvjXKhxJnftasgH3sJelU5bbb/Z8ee8e/N9j9PrZt8P/ADAAAAAAAAAAAAAAAAAAAAAAAgpV9KuZwVm6MIDQAAAABJRU5ErkJggg==';
const ARROW_DOWN_WITHE = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAAAIGNIUk0AAHomAAC' +
    'AhAAA+gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAAEZ0FNQQAAsY58+1GTAAAAAXNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAAl' +
    'wSFlzAAAOxAAADsQBlSsOGwAAAKVJREFUeNpjYBgFo2AU0Bww4pL4////diC1hZGRcSo+A4DqWIDUZCB+AVTbiC7PhEfvByCeAjQgn4Dhy4E' +
    '4BYgvYFODz4JYIF4DxBOwWYJkeAAQRwBdvxGbIcy4TG9sbPzX0NCwHsjUAuIiIPsDUOwkDsPXkhwHWFwaAsQlQAwyrJsYw4myAIslIPCHGMP' +
    'xBhGO4PoGxF+AOA9o+NbRTDgKRgFxAAAzj0Grm3RjyAAAAABJRU5ErkJggg==';
const ARROW_RIGHT = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAGAAAABgCAYAAADimHc4AAAAIGNIUk0AAHomAACAhAAA' +
    '+gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAAEZ0FNQQAAsY58+1GTAAAAAXNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAAlwSFlz' +
    'AAAOxAAADsQBlSsOGwAAAjVJREFUeNrtnCtvG1EQRq+9BlVUEBAYYFBgYGBYaBBoFUVVfkCtyqDAIL8jtI8EBruVIgU4UvMD0iKDPmirtlJg' +
    'lJZUyqzsSFXlxwZsPPPtOdJHbDKac+/cXXvtlAAAAAAAAAAAAAAAAAAAAAAUyZzW1bMMLbuWv5YvqgJqTps/sjT+eW1geckOuB+OLdtzpHy3' +
    'fFQTUHdY06MFr7+xPGMHlE93iYQnajvBo4APlj3LRhUkeBRwaRnProDkJXi9DP1ZFQmZ49oqISFzXl9RCb8sFwhYn4Sw9wlZkDplx1EWqFZJ' +
    'CVmwHSsnIZoAuYM5ogCpgzmqAJlxFFmAxDiKLiD8OFIQEHocqQgIK0FJwF0kfLZMELA+CTuWI8s1AtYj4YHlt+UcAeVK+JqmX2/OY9Pyat1F' +
    '1pM2J2n6Fec8mh4KVBdwO27m8RAB5dNb0uhPCCiXTpo+zLWItwgoj/bsKmhrwft/PBzAOQ3RlT9a0vycF5ZvHoqtCTZ/vKL5fcuhl4KVRlA7' +
    'WvOVBOQP875f0fyBt+arnAH52DmNtvJVzoBwM19pBBVp/r7n5kceQa0CYyfE78pqoiu/733lRxUg1fxoZ0BbrfmRzoAiHy+Ea36UEdRRXPlR' +
    'RlCR5g+iNt/7CGoqr3zvAuRXvucR1CrQ/GES+fMOjzvgQH3seN8B3ao036uASVWan+Pxybgflqf/LY78wH2dBPF6I/bY8txyZXlnOUsAAAAA' +
    'AAAAAAAAAAAAAAAAEIgb8WKMjSFbuAQAAAAASUVORK5CYII=';
const ARROW_RIGHT_WITHE = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAAAIGNIUk0AAHomAA' +
    'CAhAAA+gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAAEZ0FNQQAAsY58+1GTAAAAAXNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAA' +
    'lwSFlzAAAOxAAADsQBlSsOGwAAAKFJREFUeNpjYBgFowAE/v//bwHEPOToZSJS3XIg3k6OJcRaUALEFuRYwkyMosbGxusNDQ3XgMwCIHYAsl' +
    'cDxX5RzQJKLGEmxbvkWMJEaqQxMjKuBVI5QGwDxOnUimR08AFK81DdAmAqArl8DhDfAOKpVLUAavh2IH4CxI7A4HpDMEgpMPwFUXFGS8NJCa' +
    'L55BgOAixEqqsB4oOkGj4KRggAAN4STB9zyhGzAAAAAElFTkSuQmCC';
var Event;
(function (g27) {
    g27[g27['TOUCH_DOWN'] = 0] = 'TOUCH_DOWN';
    g27[g27['TOUCH_UP'] = 1] = 'TOUCH_UP';
    g27[g27['HOVER'] = 3] = 'HOVER';
    g27[g27['HOVER_OVER'] = 4] = 'HOVER_OVER';
    g27[g27['FOCUS'] = 5] = 'FOCUS';
    g27[g27['BLUR'] = 6] = 'BLUR';
    g27[g27['MOUSE_BUTTON_RIGHT'] = 7] = 'MOUSE_BUTTON_RIGHT';
    g27[g27['DRAG'] = 8] = 'DRAG';
})(Event || (Event = {}));
var MenuOperation;
(function (f27) {
    f27[f27['ADD_NODE'] = 0] = 'ADD_NODE';
    f27[f27['REMOVE_NODE'] = 1] = 'REMOVE_NODE';
    f27[f27['MODIFY_NODE'] = 2] = 'MODIFY_NODE';
    f27[f27['COMMIT_NODE'] = 3] = 'COMMIT_NODE';
})(MenuOperation || (MenuOperation = {}));
var PopUpType;
(function (e27) {
    e27[e27['HINTS'] = 0] = 'HINTS';
    e27[e27['WARNINGS'] = 1] = 'WARNINGS';
})(PopUpType || (PopUpType = {}));
var InputError;
(function (d27) {
    d27[d27['INVALID_ERROR'] = 0] = 'INVALID_ERROR';
    d27[d27['LENGTH_ERROR'] = 1] = 'LENGTH_ERROR';
    d27[d27['NONE'] = 2] = 'NONE';
})(InputError || (InputError = {}));
var Flag;
(function (c27) {
    c27[c27['DOWN_FLAG'] = 0] = 'DOWN_FLAG';
    c27[c27['UP_FLAG'] = 1] = 'UP_FLAG';
    c27[c27['NONE'] = 2] = 'NONE';
})(Flag || (Flag = {}));

export var NodeStatus;
(function (b27) {
    b27[b27['Expand'] = 0] = 'Expand';
    b27[b27['Collapse'] = 1] = 'Collapse';
})(NodeStatus || (NodeStatus = {}));

export var InteractionStatus;
(function (a27) {
    a27[a27['Normal'] = 0] = 'Normal';
    a27[a27['Selected'] = 1] = 'Selected';
    a27[a27['Edit'] = 2] = 'Edit';
    a27[a27['FinishEdit'] = 3] = 'FinishEdit';
    a27[a27['DragInsert'] = 4] = 'DragInsert';
    a27[a27['FinishDragInsert'] = 5] = 'FinishDragInsert';
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
    constructor(z26) {
        this.imageSource = '';
        this.borderWidth = { has: BORDER_WIDTH_HAS, none: BORDER_WIDTH_NONE };
        this.canShowFlagLine = false;
        this.isOverBorder = false;
        this.canShowBottomFlagLine = false;
        this.isHighLight = false;
        this.isModify = false;
        this.treeViewTheme = new TreeViewTheme();
        this.fontColor = '';
        this.childNodeInfo = z26.getChildNodeInfo();
        this.nodeItem = {
            imageNode: undefined,
            inputText: new InputText(),
            mainTitleNode: z26.getNodeItem().mainTitleNode,
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
        this.nodeItem.imageNode = z26.getNodeItem().imageNode;
        this.nodeItem.imageCollapse = z26.getNodeItem().imageCollapse;
        this.container = z26.container;
        this.parentNodeId = z26.parentNodeId;
        this.currentNodeId = z26.currentNodeId;
        this.nodeHeight = NODE_HEIGHT;
        this.nodeLevel = z26.nodeLevel;
        this.nodeLeftPadding = z26.nodeLevel * 12 + 8;
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
        this.flagLineLeftMargin = z26.nodeLevel * 12 + 8;
        this.node = z26;
        this.nodeParam = z26.data;
    }

    setFontColor(y26) {
        this.fontColor = y26;
    }

    getFontColor() {
        return this.fontColor;
    }

    getPopUpInfo() {
        return this.popUpInfo;
    }

    setPopUpIsShow(x26) {
        this.popUpInfo.popUpIsShow = x26;
    }

    setPopUpEnableArrow(w26) {
        this.popUpInfo.popUpEnableArrow = w26;
    }

    setPopUpColor(v26) {
        this.popUpInfo.popUpColor = v26;
    }

    setPopUpText(u26) {
        this.popUpInfo.popUpText = u26;
    }

    setPopUpTextColor(t26) {
        this.popUpInfo.popUpTextColor = t26;
    }

    getIsShowTitle() {
        return this.isShowTitle;
    }

    getIsShowInputText() {
        return this.isShowInputText;
    }

    setTitleAndInputTextStatus(s26) {
        if (s26) {
            this.isShowTitle = false;
            this.isShowInputText = true;
        }
        else {
            this.isShowTitle = true;
            this.isShowInputText = false;
        }
    }

    handleImageCollapseAfterAddNode(r26) {
        if (r26) {
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

    setNodeColor(q26) {
        if (q26 === undefined) {
            return;
        }
        this.nodeColor = q26;
    }

    getNodeColor() {
        return this.nodeColor;
    }

    setListItemHeight(p26) {
        this.listItemHeight = p26;
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

    setNodeIsShow(o26) {
        this.nodeIsShow = o26;
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

    setNodeBorder(n26) {
        this.nodeBorder.borderWidth = n26 ? this.borderWidth.has : this.borderWidth.none;
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

    setIsSelected(m26) {
        this.isSelected = m26;
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

    setCanShowFlagLine(l26) {
        this.canShowFlagLine = l26;
    }

    getCanShowFlagLine() {
        return this.canShowFlagLine;
    }

    setFlagLineLeftMargin(k26) {
        if (k26 === undefined) {
            return;
        }
        this.flagLineLeftMargin = k26 * 12 + 8;
    }

    getFlagLineLeftMargin() {
        return this.flagLineLeftMargin;
    }

    getNodeLevel() {
        return this.nodeLevel;
    }

    setIsOverBorder(j26) {
        this.isOverBorder = j26;
    }

    getIsOverBorder() {
        return this.isOverBorder;
    }

    setCanShowBottomFlagLine(i26) {
        this.canShowBottomFlagLine = i26;
    }

    getCanShowBottomFlagLine() {
        return this.canShowBottomFlagLine;
    }

    setIsHighLight(h26) {
        this.isHighLight = h26;
    }

    getIsHighLight() {
        return this.isHighLight;
    }

    setIsModify(g26) {
        this.isModify = g26;
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
(function (f26) {
    f26['NODE_CLICK'] = 'NodeClick';
    f26['NODE_ADD'] = 'NodeAdd';
    f26['NODE_DELETE'] = 'NodeDelete';
    f26['NODE_MODIFY'] = 'NodeModify';
    f26['NODE_MOVE'] = 'NodeMove';
})(TreeListenType || (TreeListenType = {}));

export class TreeListener {
    constructor() {
        this._events = [];
        this._once_events = [];
    }

    on(b26, c26) {
        if (Array.isArray(b26)) {
            for (let d26 = 0, e26 = b26.length; d26 < e26; d26++) {
                this.on(b26[d26], c26);
            }
        }
        else {
            (this._events[b26] || (this._events[b26] = [])).push(c26);
        }
    }

    once(z25, a26) {
        if (Array.isArray(z25)) {
            this.off(z25, a26);
        }
        else {
            (this._once_events[z25] || (this._once_events[z25] = [])).push(a26);
        }
    }

    off(s25, t25) {
        if (s25 === null) {
            this._events = [];
        }
        if (Array.isArray(s25)) {
            for (let x25 = 0, y25 = s25.length; x25 < y25; x25++) {
                this.off(s25[x25], t25);
            }
        }
        let u25 = this._events[s25];
        if (!u25) {
            return;
        }
        if (t25 === null) {
            this._events[s25] = null;
        }
        let v25 = u25.length;
        while (v25--) {
            let w25 = u25[v25];
            if (w25 === t25) {
                u25.splice(v25, 1);
                break;
            }
        }
    }

    emit(i25, j25) {
        if (this._once_events[i25]) {
            let o25 = Array.from(this._once_events[i25]);
            if (o25) {
                for (let p25 = 0, q25 = o25.length; p25 < q25; p25++) {
                    try {
                        o25[p25](j25);
                    }
                    catch (r25) {
                        throw new Error('once function callbacks error.');
                    }
                }
                this._once_events[i25] = null;
            }
        }
        else if (this._events[i25]) {
            let k25 = Array.from(this._events[i25]);
            if (k25) {
                for (let l25 = 0, m25 = k25.length; l25 < m25; l25++) {
                    try {
                        k25[l25](j25);
                    }
                    catch (n25) {
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
    constructor(c25, d25, e25, f25 = -1, g25 = undefined, h25) {
        super(c25, e25, f25, h25);
        if (typeof g25 === 'function') {
            this.paramsGenerator_ = g25;
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
        this.textInputPadding = { left: '0vp', right: '0vp', top: '0vp', bottom: '0vp' };
        this.setInitiallyProvidedValue(d25);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(b25) {
        if (b25.treeController !== undefined) {
            this.treeController = b25.treeController;
        }
        if (b25.nodeList !== undefined) {
            this.nodeList = b25.nodeList;
        }
        if (b25.listNodeDataSource !== undefined) {
            this.listNodeDataSource = b25.listNodeDataSource;
        }
        if (b25.item !== undefined) {
            this.item = b25.item;
        }
        if (b25.touchCount !== undefined) {
            this.touchCount = b25.touchCount;
        }
        if (b25.dropSelectedIndex !== undefined) {
            this.dropSelectedIndex = b25.dropSelectedIndex;
        }
        if (b25.viewLastIndex !== undefined) {
            this.viewLastIndex = b25.viewLastIndex;
        }
        if (b25.listItemBgColor !== undefined) {
            this.listItemBgColor = b25.listItemBgColor;
        }
        if (b25.treeViewTheme !== undefined) {
            this.treeViewTheme = b25.treeViewTheme;
        }
        if (b25.listTreeViewMenu !== undefined) {
            this.listTreeViewMenu = b25.listTreeViewMenu;
        }
        if (b25.MAX_CN_LENGTH !== undefined) {
            this.MAX_CN_LENGTH = b25.MAX_CN_LENGTH;
        }
        if (b25.MAX_EN_LENGTH !== undefined) {
            this.MAX_EN_LENGTH = b25.MAX_EN_LENGTH;
        }
        if (b25.INITIAL_INVALID_VALUE !== undefined) {
            this.INITIAL_INVALID_VALUE = b25.INITIAL_INVALID_VALUE;
        }
        if (b25.MAX_TOUCH_DOWN_COUNT !== undefined) {
            this.MAX_TOUCH_DOWN_COUNT = b25.MAX_TOUCH_DOWN_COUNT;
        }
        if (b25.isMultiPress !== undefined) {
            this.isMultiPress = b25.isMultiPress;
        }
        if (b25.touchDownCount !== undefined) {
            this.touchDownCount = b25.touchDownCount;
        }
        if (b25.appEventBus !== undefined) {
            this.appEventBus = b25.appEventBus;
        }
        if (b25.itemPadding !== undefined) {
            this.itemPadding = b25.itemPadding;
        }
        if (b25.textInputPadding !== undefined) {
            this.textInputPadding = b25.textInputPadding;
        }
    }

    updateStateVars(a25) {
    }

    purgeVariableDependenciesOnElmtId(z24) {
        this.__nodeList.purgeDependencyOnElmtId(z24);
        this.__item.purgeDependencyOnElmtId(z24);
        this.__touchCount.purgeDependencyOnElmtId(z24);
        this.__dropSelectedIndex.purgeDependencyOnElmtId(z24);
        this.__viewLastIndex.purgeDependencyOnElmtId(z24);
        this.__listItemBgColor.purgeDependencyOnElmtId(z24);
        this.__treeViewTheme.purgeDependencyOnElmtId(z24);
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

    set nodeList(y24) {
        this.__nodeList.set(y24);
    }

    get item() {
        return this.__item.get();
    }

    set item(x24) {
        this.__item.set(x24);
    }

    get touchCount() {
        return this.__touchCount.get();
    }

    set touchCount(w24) {
        this.__touchCount.set(w24);
    }

    get dropSelectedIndex() {
        return this.__dropSelectedIndex.get();
    }

    set dropSelectedIndex(v24) {
        this.__dropSelectedIndex.set(v24);
    }

    get viewLastIndex() {
        return this.__viewLastIndex.get();
    }

    set viewLastIndex(u24) {
        this.__viewLastIndex.set(u24);
    }

    get listItemBgColor() {
        return this.__listItemBgColor.get();
    }

    set listItemBgColor(t24) {
        this.__listItemBgColor.set(t24);
    }

    get treeViewTheme() {
        return this.__treeViewTheme.get();
    }

    set treeViewTheme(s24) {
        this.__treeViewTheme.set(s24);
    }

    NullBuilder(r24 = null) {
    }

    onWillApplyTheme(q24) {
        this.treeViewTheme.itemSelectedBgColor = q24.colors.interactiveSelect;
        this.treeViewTheme.itemPressedBgColor = q24.colors.interactivePressed;
        this.treeViewTheme.itemHoverBgColor = q24.colors.interactiveHover;
        this.treeViewTheme.primaryTitleFontColor = q24.colors.fontPrimary;
        this.treeViewTheme.secondaryTitleFontColor = q24.colors.fontSecondary;
        this.treeViewTheme.primaryTitleActiveFontColor = q24.colors.interactiveActive;
        this.treeViewTheme.borderFocusedColor = q24.colors.interactiveFocus;
        this.treeViewTheme.leftIconColor = q24.colors.iconSecondary;
        this.treeViewTheme.leftIconActiveColor = q24.colors.interactiveActive;
        this.treeViewTheme.arrowIconColor = q24.colors.iconTertiary;
        this.treeController.treeViewTheme = this.treeViewTheme;
    }

    aboutToAppear() {
        if (this.treeController !== null) {
            this.listNodeDataSource = this.treeController.getListNodeDataSource();
            this.nodeList = this.treeController.getListNodeDataSource().listNode;
            this.item = this.treeController.getListNodeDataSource().listNode;
        }
    }

    popupForShowTitle(g24, h24, i24, j24 = null) {
        this.observeComponentCreation((o24, p24) => {
            ViewStackProcessor.StartGetAccessRecordingFor(o24);
            Row.create();
            Row.backgroundColor(h24);
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
            if (!p24) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((m24, n24) => {
            ViewStackProcessor.StartGetAccessRecordingFor(m24);
            Text.create(g24);
            Text.fontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_body2'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            });
            Text.fontWeight('regular');
            Text.fontColor(i24);
            if (!n24) {
                Text.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        Text.pop();
        Row.pop();
    }

    builder(f24 = null) {
        this.listTreeViewMenu.bind(this)(f24 ? f24 : this);
    }

    draggingPopup(e23, f23 = null) {
        this.observeComponentCreation((d24, e24) => {
            ViewStackProcessor.StartGetAccessRecordingFor(d24);
            Row.create();
            Row.constraintSize({
                minWidth: this.listNodeDataSource.getDragPopupPara().floorConstraintSize.minWidth,
                maxWidth: this.listNodeDataSource.getDragPopupPara().floorConstraintSize.maxWidth,
            });
            Row.height(this.listNodeDataSource.getDragPopupPara().height);
            Row.backgroundColor(this.listNodeDataSource.getDragPopupPara().backgroundColor);
            Row.padding({
                left: this.listNodeDataSource.getDragPopupPara().padding.left,
                right: this.listNodeDataSource.getDragPopupPara().padding.right,
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
            if (!e24) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((t23, u23) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t23);
            If.create();
            if (e23.getNodeItem().imageNode) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((b24, c24) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(b24);
                        Row.create();
                        Row.backgroundColor(COLOR_IMAGE_ROW);
                        Row.margin({ right: e23.getNodeItem().imageNode?.itemRightMargin });
                        Row.height(e23.getNodeItem().imageNode?.itemHeight);
                        Row.width(e23.getNodeItem().imageNode?.itemWidth);
                        if (!c24) {
                            Row.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((z23, a24) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(z23);
                        Image.create(e23.getNodeItem().imageNode?.normalSource);
                        Image.objectFit(ImageFit.Contain);
                        Image.height(e23.getNodeItem().imageNode?.itemHeight);
                        Image.width(e23.getNodeItem().imageNode?.itemWidth);
                        Image.opacity(this.listNodeDataSource.getDragPopupPara().imageOpacity);
                        if (!a24) {
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
            if (!u23) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        this.observeComponentCreation((r23, s23) => {
            ViewStackProcessor.StartGetAccessRecordingFor(r23);
            Row.create();
            Row.constraintSize({
                minWidth: e23.getNodeItem().imageNode ?
                this.listNodeDataSource.getDragPopupPara().textConstraintSize.minWidth1 :
                this.listNodeDataSource.getDragPopupPara().textConstraintSize.minWidth2,
                maxWidth: e23.getNodeItem().imageNode ?
                this.listNodeDataSource.getDragPopupPara().textConstraintSize.maxWidth1 :
                this.listNodeDataSource.getDragPopupPara().textConstraintSize.maxWidth2
            });
            if (!s23) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((k23, l23) => {
            ViewStackProcessor.StartGetAccessRecordingFor(k23);
            If.create();
            if (e23.getNodeItem().mainTitleNode && e23.getIsShowTitle()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((p23, q23) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(p23);
                        Text.create(e23.getNodeItem().mainTitleNode?.title);
                        Text.maxLines(1);
                        Text.fontSize(e23.getNodeItem().mainTitleNode?.size);
                        Text.fontColor(this.listNodeDataSource.getDragPopupPara().fontColor);
                        Text.fontWeight(this.listNodeDataSource.getDragPopupPara().fontWeight);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        if (!q23) {
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
            if (!l23) {
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

    setImageSources(b23, c23) {
        let d23 = this.nodeList[b23];
        d23.setIsSelected(c23 === InteractionStatus.Selected ||
            c23 === InteractionStatus.Edit || c23 === InteractionStatus.FinishEdit);
        if (d23.getNodeItem().mainTitleNode !== null && c23 !== InteractionStatus.DragInsert &&
            c23 !== InteractionStatus.FinishDragInsert) {
            d23.getNodeItem().mainTitleNode?.setMainTitleSelected(c23 === InteractionStatus.Selected ||
                c23 === InteractionStatus.FinishEdit);
        }
        if (d23.getNodeItem().imageNode !== null) {
            d23.getNodeItem().imageNode?.setImageSource(c23);
        }
    }

    initialRender() {
        this.observeComponentCreation((p21, q21) => {
            ViewStackProcessor.StartGetAccessRecordingFor(p21);
            List.create({});
            List.onDragMove((s22, t22) => {
                if (this.isMultiPress) {
                    console.error('drag error, a item has been dragged');
                    return;
                }
                let u22 = LIST_ITEM_HEIGHT;
                let v22 = Math.floor(s22.getY() / (u22 / FLAG_NUMBER)) % FLAG_NUMBER ? Flag.DOWN_FLAG : Flag.UP_FLAG;
                let w22 = JSON.parse(t22).insertIndex;
                let x22 = false;
                if (w22 >= this.listNodeDataSource.totalCount()) {
                    v22 = Flag.DOWN_FLAG;
                    w22 = this.listNodeDataSource.totalCount() - 1;
                    this.listNodeDataSource.getData(w22)?.setIsOverBorder(true);
                    x22 = true;
                }
                else {
                    this.listNodeDataSource.getData(w22)?.setIsOverBorder(false);
                }
                let y22 = this.listNodeDataSource.getData(w22);
                let z22 = y22?.getCurrentNodeId();
                if (w22 !== this.listNodeDataSource.getLastPassIndex() && this.listNodeDataSource.getIsInnerDrag()) {
                    let a23 = this.listNodeDataSource.getIsParentOfInsertNode(z22);
                    if (a23) {
                        this.listNodeDataSource.setPassIndex(w22);
                        if (z22 !== undefined) {
                            this.listNodeDataSource.clearTimeOutAboutDelayHighLightAndExpand(findCurrentNodeIndex(this.listNodeDataSource, z22));
                        }
                        this.listNodeDataSource.setFlag(Flag.NONE);
                        return;
                    }
                }
                this.listNodeDataSource.setLastPassIndex(w22);
                this.listNodeDataSource.setVisibility(v22, w22 - 1, x22);
                if (z22 !== undefined && z22 !== this.listNodeDataSource.getDraggingCurrentNodeId()) {
                    this.listNodeDataSource.delayHighLightAndExpandNode(findCurrentNodeIndex(this.listNodeDataSource, z22), z22, w22);
                }
            });
            List.onDragEnter((p22, q22) => {
                if (this.listNodeDataSource.getIsInnerDrag()) {
                    this.listNodeDataSource.setIsDrag(true);
                    let r22 = DRAG_OPACITY;
                    this.listNodeDataSource.setListItemOpacity(r22);
                }
            });
            List.onDragLeave((m22, n22) => {
                this.listNodeDataSource.hideLastLine();
                this.listNodeDataSource.clearLastTimeoutHighLight();
                this.listNodeDataSource.clearLastTimeoutExpand();
                let o22 = DRAG_OPACITY_NONE;
                this.listNodeDataSource.setListItemOpacity(o22);
                this.listNodeDataSource.setIsDrag(false);
                this.listNodeDataSource.notifyDataReload();
            });
            List.onDrop((v21, w21) => {
                this.listNodeDataSource.clearLastTimeoutExpand();
                let x21 = DRAG_OPACITY_NONE;
                this.listNodeDataSource.setListItemOpacity(x21);
                let y21 = JSON.parse(w21).insertIndex;
                let z21 = this.dropSelectedIndex;
                if (z21 - 1 > this.listNodeDataSource.totalCount() || z21 === undefined) {
                    console.error('drag error, currentNodeIndex is not found');
                    this.listNodeDataSource.setIsDrag(false);
                    return;
                }
                if (y21 === this.listNodeDataSource.totalCount()) {
                    console.log('need to insert into the position of the last line, now insertNodeIndex = insertNodeIndex - 1');
                    y21 -= 1;
                }
                let a22 = this.listNodeDataSource.getData(y21);
                if (a22 === undefined) {
                    return;
                }
                let b22 = a22.getNodeCurrentNodeId();
                if (!this.listNodeDataSource.getIsDrag() || !this.listNodeDataSource.getIsInnerDrag()) {
                    this.listNodeDataSource.clearLastTimeoutHighLight();
                    this.listNodeDataSource.setIsInnerDrag(false);
                    this.listNodeDataSource.hideLastLine();
                    this.listNodeDataSource.initialParameterAboutDelayHighLightAndExpandIndex();
                    this.listNodeDataSource.refreshSubtitle(b22);
                    this.listNodeDataSource.notifyDataReload();
                    return;
                }
                let c22 = this.listNodeDataSource.getCurrentNodeInfo();
                let d22 = a22.getNodeParentNodeId();
                let e22 = this.listNodeDataSource.getDraggingCurrentNodeId();
                let f22 = this.listNodeDataSource.getDraggingParentNodeId();
                let g22 = this.listNodeDataSource.getIsParentOfInsertNode(b22);
                if (g22) {
                    this.listNodeDataSource.clearLastTimeoutHighLight();
                    this.listNodeDataSource.setIsInnerDrag(false);
                    this.listNodeDataSource.hideLastLine();
                    this.listNodeDataSource.notifyDataChange(y21);
                    this.listNodeDataSource.initialParameterAboutDelayHighLightAndExpandIndex();
                    this.listNodeDataSource.setIsDrag(false);
                    let l22 = findCurrentNodeIndex(this.listNodeDataSource, e22);
                    this.listNodeDataSource.setClickIndex(l22);
                    this.listNodeDataSource.handleEvent(Event.DRAG, l22);
                    return;
                }
                if (this.listNodeDataSource.getExpandAndCollapseInfo(e22) === NodeStatus.Expand) {
                    this.listNodeDataSource.expandAndCollapseNode(findCurrentNodeIndex(this.listNodeDataSource, e22));
                }
                let h22 = false;
                if (this.listNodeDataSource.getExpandAndCollapseInfo(b22) === NodeStatus.Collapse) {
                    let k22 = findCurrentNodeIndex(this.listNodeDataSource, b22);
                    if (this.listNodeDataSource.ListNode[k22].getIsHighLight()) {
                        this.listNodeDataSource.expandAndCollapseNode(k22);
                    }
                    h22 = true;
                }
                this.listNodeDataSource.setLastDelayHighLightId();
                if (c22 !== null && e22 !== b22) {
                    this.listNodeDataSource.alterDragNode(d22, b22, f22, e22, c22);
                    this.listNodeDataSource.hideLastLine();
                }
                else {
                    this.listNodeDataSource.hideLastLine();
                    this.listNodeDataSource.setLastPassId(e22);
                    this.listNodeDataSource.hideLastLine();
                }
                let i22 = findCurrentNodeIndex(this.listNodeDataSource, this.listNodeDataSource.getLastDelayHighLightId());
                this.listNodeDataSource.setLastDelayHighLightIndex(i22);
                this.listNodeDataSource.clearLastTimeoutHighLight();
                this.listNodeDataSource.initialParameterAboutDelayHighLightAndExpandIndex();
                this.listNodeDataSource.setIsDrag(false);
                let j22 = findCurrentNodeIndex(this.listNodeDataSource, e22);
                this.listNodeDataSource.setClickIndex(j22);
                this.listNodeDataSource.handleEvent(Event.DRAG, j22);
                this.listNodeDataSource.setIsInnerDrag(false);
                this.listNodeDataSource.notifyDataReload();
                this.listNodeDataSource.listNode[j22].fontColor = this.treeViewTheme.primaryTitleActiveFontColor;
                if (this.viewLastIndex !== -1 && z21 !== this.viewLastIndex) {
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
                this.listNodeDataSource.lastIndex = j22;
            });
            if (!q21) {
                List.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        {
            const d20 = i20 => {
                const j20 = i20;
                {
                    const k20 = (n21, o21) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(n21);
                        l20(n21, o21);
                        if (!o21) {
                            ListItem.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    };
                    const l20 = (d21, e21) => {
                        ListItem.create(() => {
                        }, false);
                        ListItem.width('100%');
                        ListItem.height(j20.getListItemHeight());
                        ListItem.padding({ left: this.itemPadding.left, right: this.itemPadding.right });
                        ListItem.align(Alignment.Start);
                        ListItem.onDragStart((h21, i21) => {
                            if (this.listNodeDataSource.getIsDrag() || this.listNodeDataSource.getIsInnerDrag() || this.isMultiPress) {
                                console.error('drag error, a item has been dragged');
                                return;
                            }
                            this.dropSelectedIndex = JSON.parse(i21).selectedIndex;
                            let j21 = JSON.parse(i21).selectedIndex;
                            let k21 = this.listNodeDataSource.getData(j21);
                            let l21 = j20.getNodeCurrentNodeId();
                            if (j21 >= this.listNodeDataSource.totalCount() || j21 === undefined) {
                                console.error('drag error, currentNodeIndex is not found in onDragStart');
                                return;
                            }
                            this.listNodeDataSource.setIsInnerDrag(true);
                            this.listNodeDataSource.setIsDrag(true);
                            this.listNodeDataSource.setCurrentNodeInfo(k21);
                            this.listNodeDataSource.setDraggingCurrentNodeId(k21?.getNodeCurrentNodeId());
                            this.listNodeDataSource.setDraggingParentNodeId(k21?.getNodeParentNodeId());
                            let m21 = DRAG_OPACITY;
                            this.listNodeDataSource.setListItemOpacity(m21);
                            this.listNodeDataSource.notifyDataChange(j21);
                            if (l21 !== k21?.getNodeCurrentNodeId()) {
                                console.error('drag is too fast,it attribute a fault to OH');
                                this.listNodeDataSource.setIsDrag(false);
                                return;
                            }
                            return { builder: () => {
                                this.draggingPopup.call(this, k21);
                            } };
                        });
                    };
                    const m20 = () => {
                        this.observeComponentCreation(k20);
                        this.observeComponentCreation((y20, z20) => {
                            ViewStackProcessor.StartGetAccessRecordingFor(y20);
                            Row.create();
                            Row.onTouch((b21) => {
                                this.viewLastIndex = this.listNodeDataSource.getLastIndex();
                                let c21 = this.listNodeDataSource.findIndex(j20.getNodeCurrentNodeId());
                                if (b21.type === TouchType.Down) {
                                    if (c21 !== this.viewLastIndex) {
                                        this.clearLastIndexColor();
                                        this.listNodeDataSource.lastIndex = c21;
                                        this.listNodeDataSource.setClickIndex(c21);
                                    }
                                }
                                if (b21.type === TouchType.Up) {
                                    this.listNodeDataSource.listNode[c21].setIsSelected(true);
                                    this.listNodeDataSource.setImageSource(c21, InteractionStatus.Selected);
                                    if (this.listNodeDataSource.listNode[c21].getNodeItem().imageNode !== null) {
                                        this.listNodeDataSource.listNode[c21].imageSource = this.listNodeDataSource.listNode[c21]
                                            .getNodeItem().imageNode?.source;
                                    }
                                    if (c21 !== this.viewLastIndex) {
                                        this.clearLastIndexColor();
                                        this.listNodeDataSource.lastIndex = c21;
                                        this.listNodeDataSource.setClickIndex(c21);
                                    }
                                    this.viewLastIndex = c21;
                                }
                                if (this.listNodeDataSource.getLastIndex() !== -1 && c21 !== this.listNodeDataSource.getLastIndex()) {
                                    this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false, this.listNodeDataSource.getLastIndex());
                                    this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(), MenuOperation.COMMIT_NODE);
                                }
                            });
                            if (!z20) {
                                Row.pop();
                            }
                            ViewStackProcessor.StopGetAccessRecording();
                        });
                        {
                            this.observeComponentCreation((s20, t20) => {
                                ViewStackProcessor.StartGetAccessRecordingFor(s20);
                                if (t20) {
                                    let u20 = new TreeViewInner(this, {
                                        item: j20,
                                        listNodeDataSource: this.listNodeDataSource,
                                        index: this.listNodeDataSource.findIndex(j20.getNodeCurrentNodeId()),
                                        listTreeViewMenu: this.listTreeViewMenu,
                                    }, undefined, s20, () => {
                                    }, {
                                        page: 'library/src/main/ets/components/mainpage/MainPage.ets',
                                        line: 1045,
                                        col: 13
                                    });
                                    ViewPU.create(u20);
                                    let v20 = () => {
                                        return {
                                            item: j20,
                                            listNodeDataSource: this.listNodeDataSource,
                                            index: this.listNodeDataSource.findIndex(j20.getNodeCurrentNodeId()),
                                            listTreeViewMenu: this.listTreeViewMenu
                                        };
                                    };
                                    u20.paramsGenerator_ = v20;
                                }
                                else {
                                    this.updateStateVarsOfChildByElmtId(s20, {
                                        item: j20
                                    });
                                }
                                ViewStackProcessor.StopGetAccessRecording();
                            });
                        }
                        Row.pop();
                        ListItem.pop();
                    };
                    m20();
                }
            };
            const e20 = (h20) => JSON.stringify(h20);
            LazyForEach.create('1', this, this.listNodeDataSource, d20, e20);
            LazyForEach.pop();
        }
        List.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

function findCurrentNodeIndex(w19, x19) {
    let y19 = 0;
    w19.ListNode.forEach((a20, b20) => {
        if (a20.getNodeCurrentNodeId() === x19) {
            y19 = b20;
        }
    });
    return y19;
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
        let v19 = this.listNodeDataSource.getClickNodeId();
        return this.listNodeUtils.getClickNodeChildrenInfo(v19);
    }

    getChildrenId() {
        let u19 = this.listNodeDataSource.getClickNodeId();
        return this.listNodeUtils.getClickChildId(u19);
    }

    removeNode() {
        let r19 = this.listNodeDataSource.getClickNodeId();
        if (r19 < 0) {
            return;
        }
        let s19 = this.listNodeUtils.findParentNodeId(r19);
        let t19 = this.listNodeUtils.removeNode(r19, s19);
        this.listNodeDataSource.refreshData(this.listNodeUtils, MenuOperation.REMOVE_NODE, s19, t19);
        this.nodeIdList.splice(this.nodeIdList.indexOf(r19), 1);
    }

    modifyNode() {
        let q19 = this.listNodeDataSource.getClickNodeId();
        this.listNodeDataSource.setItemVisibilityOnEdit(q19, MenuOperation.MODIFY_NODE);
    }

    add() {
        let m19 = this.listNodeDataSource.getClickNodeId();
        if (m19 === this.listNodeDataSource.ROOT_NODE_ID || !this.listNodeDataSource.getIsFolder(m19)) {
            return;
        }
        let n19 = this.listNodeUtils.getNewNodeInfo(m19);
        this.nodeIdList.push(this.nodeIdList[this.nodeIdList.length - 1] + 1);
        let o19 = this.nodeIdList[this.nodeIdList.length - 1];
        this.listNodeUtils.addNewNodeId = o19;
        this.listNodeUtils.addNode(m19, o19, {
            isFolder: n19.isFolder,
            icon: n19.icon,
            selectedIcon: n19.selectedIcon,
            editIcon: n19.editIcon,
            primaryTitle: '新建文件夹',
            container: n19.container,
            secondaryTitle: n19.secondaryTitle,
        });
        this.listNodeDataSource.refreshData(this.listNodeUtils, MenuOperation.ADD_NODE, m19, [o19]);
        this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false, this.listNodeDataSource.getLastIndex());
        this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(), MenuOperation.COMMIT_NODE);
        this.listNodeDataSource.listNode[this.listNodeDataSource.getLastIndex()]
            .setFontColor(this.treeViewTheme.primaryTitleFontColor);
        let p19 = findCurrentNodeIndex(this.listNodeDataSource, o19);
        this.listNodeDataSource.setClickIndex(p19);
        this.listNodeDataSource.handleEvent(Event.TOUCH_UP, p19);
    }

    addNode(k19) {
        if (k19 === undefined) {
            this.add();
            return this;
        }
        else {
            if (k19.primaryTitle !== undefined &&
                !this.listNodeUtils.checkMainTitleIsValid(k19.primaryTitle.toString())) {
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
                    this.listNodeUtils.addNode(k19.parentNodeId, k19.currentNodeId, k19);
                }
            }
            if (!this.initBuild && k19.parentNodeId !== undefined) {
                let l19 = this.nodeIdList[this.nodeIdList.length - 1];
                this.listNodeDataSource.refreshData(this.listNodeUtils, MenuOperation.ADD_NODE, k19.parentNodeId, [l19]);
            }
            return this;
        }
    }

    refreshNode(h19, i19, j19) {
        this.listNodeDataSource.setNodeSubtitlePara(h19, i19, j19);
    }

    buildDone() {
        this.listNodeDataSource.init(this.listNodeUtils);
        this.nodeIdList.sort((f19, g19) => f19 - g19);
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

    getData(d19) {
        return undefined;
    }

    registerDataChangeListener(c19) {
        if (this.listeners.indexOf(c19) < 0) {
            this.listeners.push(c19);
        }
    }

    unregisterDataChangeListener(a19) {
        const b19 = this.listeners.indexOf(a19);
        if (b19 >= 0) {
            this.listeners.splice(b19, 1);
        }
    }

    notifyDataReload() {
        this.listeners.forEach(z18 => {
            z18.onDataReloaded();
        });
    }

    notifyDataAdd(v18) {
        this.listeners.forEach(x18 => {
            x18.onDataAdd(v18);
        });
    }

    notifyDataChange(s18) {
        if (s18 === undefined) {
            return;
        }
        this.listeners.forEach(u18 => {
            u18.onDataChange(s18);
        });
    }

    notifyDataDelete(p18) {
        this.listeners.forEach(r18 => {
            r18.onDataDelete(p18);
        });
    }

    notifyDataMove(l18, m18) {
        this.listeners.forEach(o18 => {
            o18.onDataMove(l18, m18);
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
            padding: { left: LEFT_PADDING, right: RIGHT_PADDING },
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
            margin: { left: '4vp', right: '24' }
        };
    }

    changeNodeColor(j18, k18) {
        this.listNode[j18].setNodeColor(k18);
        this.listNode[j18].setNodeBorder(false);
    }

    getNodeColor(i18) {
        return this.listNode[i18].getNodeColor();
    }

    handleFocusEffect(g18, h18) {
        if (this.listNode[g18].getNodeIsShow()) {
            this.listNode[g18].setNodeBorder(h18);
        }
    }

    setImageSource(d18, e18) {
        let f18 = this.listNode[d18];
        f18.setIsSelected(e18 === InteractionStatus.Selected ||
            e18 === InteractionStatus.Edit || e18 === InteractionStatus.FinishEdit);
        if (f18.getNodeItem().mainTitleNode !== null && e18 !== InteractionStatus.DragInsert &&
            e18 !== InteractionStatus.FinishDragInsert) {
            f18.getNodeItem().mainTitleNode?.setMainTitleSelected(e18 === InteractionStatus.Selected ||
                e18 === InteractionStatus.FinishEdit);
        }
        if (f18.getNodeItem().imageNode !== null) {
            f18.getNodeItem().imageNode?.setImageSource(e18);
        }
    }

    setImageCollapseSource(a18, b18) {
        let c18 = this.listNode[a18];
        if (c18.getNodeItem().imageCollapse !== undefined) {
            c18.getNodeItem().imageCollapse?.setImageCollapseSource(b18, this.expandAndCollapseInfo.get(c18.getCurrentNodeId()));
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

    changeNodeStatus(w17) {
        let x17 = w17;
        let y17 = this.ListNode;
        let z17 = y17[w17].getCurrentNodeId();
        if (this.expandAndCollapseInfo.get(z17) === NodeStatus.Expand) {
            this.expandAndCollapseInfo.set(z17, NodeStatus.Collapse);
            y17[x17].getNodeItem().imageCollapse?.changeImageCollapseSource(NodeStatus.Collapse);
        }
        else if (this.expandAndCollapseInfo.get(z17) === NodeStatus.Collapse) {
            this.expandAndCollapseInfo.set(z17, NodeStatus.Expand);
            y17[x17].getNodeItem().imageCollapse?.changeImageCollapseSource(NodeStatus.Expand);
        }
    }

    handleExpandAndCollapse(m17) {
        let n17 = m17;
        let o17 = this.ListNode;
        let p17 = o17[n17].getCurrentNodeId();
        if (!this.expandAndCollapseInfo.has(p17)) {
            return;
        }
        let q17 = this.expandAndCollapseInfo.get(p17);
        if (o17[n17].getChildNodeInfo().isHasChildNode && q17 === NodeStatus.Collapse) {
            for (let v17 = 0; v17 < o17[n17].getChildNodeInfo().allChildNum; v17++) {
                o17[n17 + 1 + v17].setNodeIsShow(false);
                o17[n17 + 1 + v17].setListItemHeight(LIST_ITEM_HEIGHT_NONE);
            }
            this.notifyDataReload();
            return;
        }
        let r17 = new Array(o17[n17].getChildNodeInfo().childNum);
        r17[0] = n17 + 1;
        let s17 = 1;
        while (s17 < o17[n17].getChildNodeInfo().childNum) {
            r17[s17] = r17[s17 - 1] + o17[r17[s17 - 1]].getChildNodeInfo().allChildNum + 1;
            s17++;
        }
        if (q17 === NodeStatus.Expand) {
            for (let t17 = 0; t17 < r17.length; t17++) {
                o17[r17[t17]].setNodeIsShow(true);
                o17[r17[t17]].setListItemHeight(LIST_ITEM_HEIGHT);
                let u17 = o17[r17[t17]].getCurrentNodeId();
                if (this.expandAndCollapseInfo.get(u17) === NodeStatus.Expand) {
                    this.handleExpandAndCollapse(r17[t17]);
                }
            }
        }
        r17 = null;
        this.notifyDataReload();
    }

    init(h17) {
        let i17 = 0;
        this.listNode = [];
        this.listNodeUtils = h17;
        this.loadedNodeIdAndIndexMap.clear();
        this.listNodeUtils.traverseNodeDF((k17) => {
            if (k17.currentNodeId >= 0) {
                let l17 = new NodeInfo(k17);
                this.listNode.push(l17);
                if (l17.getChildNodeInfo().isHasChildNode) {
                    this.expandAndCollapseInfo.set(l17.getCurrentNodeId(), NodeStatus.Collapse);
                }
                if (l17.getNodeIsShow()) {
                    this.loadedNodeIdAndIndexMap.set(l17.getCurrentNodeId(), i17++);
                }
                if (l17.getIsFolder()) {
                    if (l17.getNodeInfoData().secondaryTitle !== undefined) {
                        this.nodeIdAndSubtitleMap.set(l17.getCurrentNodeId(), l17.getNodeInfoData().secondaryTitle);
                    }
                    else {
                        this.nodeIdAndSubtitleMap.set(l17.getCurrentNodeId(), '');
                    }
                }
            }
            return false;
        });
    }

    refreshRemoveNodeData(v16, w16) {
        let x16 = [];
        for (let d17 = 0; d17 < v16.length; d17++) {
            for (let e17 = 0; e17 < this.listNode.length; e17++) {
                if (this.listNode[e17].getNodeCurrentNodeId() === v16[d17]) {
                    let f17 = this.listNode[e17].getNodeCurrentNodeId();
                    if (this.loadedNodeIdAndIndexMap.has(f17)) {
                        x16.push(this.loadedNodeIdAndIndexMap.get(f17));
                    }
                    let g17 = this.listNode.splice(e17, 1);
                    g17 = null;
                    if (this.expandAndCollapseInfo.has(v16[d17])) {
                        this.expandAndCollapseInfo.delete(v16[d17]);
                    }
                    break;
                }
            }
        }
        x16.forEach((c17) => {
            this.notifyDataDelete(c17);
            this.notifyDataChange(c17);
        });
        let y16 = 0;
        for (let b17 = 0; b17 < this.listNode.length; b17++) {
            if (this.listNode[b17].getNodeCurrentNodeId() === w16.getNodeCurrentNodeId()) {
                if (w16.getNodeItem().imageCollapse === null) {
                    this.listNode[b17].handleImageCollapseAfterAddNode(false);
                    this.expandAndCollapseInfo.delete(w16.getNodeCurrentNodeId());
                    this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.listNode[b17].getNodeCurrentNodeId()));
                }
                break;
            }
        }
        let z16 = {
            currentNodeId: w16.getNodeCurrentNodeId(),
            parentNodeId: w16.getNodeParentNodeId(),
        };
        this.appEventBus.emit(TreeListenType.NODE_DELETE, z16);
    }

    refreshAddNodeData(p16) {
        let q16 = new NodeInfo(new NodeItem(emptyNodeInfo));
        this.listNodeUtils.traverseNodeDF((u16) => {
            if (u16.currentNodeId === p16[0]) {
                q16 = new NodeInfo(u16);
                return true;
            }
            return false;
        });
        q16.setIsModify(true);
        let r16 = 0;
        for (let t16 = 0; t16 < this.listNode.length; t16++) {
            if (this.listNode[t16].getNodeCurrentNodeId() === q16.getNodeParentNodeId()) {
                r16 = t16;
                if (this.listNode[t16].getNodeItem().imageCollapse === null) {
                    this.listNode[t16].handleImageCollapseAfterAddNode(true);
                    this.notifyDataChange(r16);
                }
                else if (this.expandAndCollapseInfo.get(this.listNode[t16].getNodeCurrentNodeId()) === NodeStatus.Collapse) {
                    this.changeNodeStatus(r16);
                }
                this.listNode.splice(t16 + 1, 0, q16);
                this.listNode[t16 + 1].setTitleAndInputTextStatus(true);
                this.listNode[t16 + 1].setNodeIsShow(true);
                this.listNode[t16 + 1].setListItemHeight(LIST_ITEM_HEIGHT);
                this.setImageSource(t16 + 1, InteractionStatus.Edit);
                this.currentOperation = MenuOperation.ADD_NODE;
                this.notifyDataAdd(t16 + 1);
                this.notificationNodeInfo(t16 + 1, this.currentOperation);
                break;
            }
        }
        this.modifyNodeIndex = r16 + 1;
        this.setClickIndex(r16);
        this.lastIndex = r16;
        this.expandAndCollapseInfo.set(q16.getNodeParentNodeId(), NodeStatus.Expand);
        this.handleExpandAndCollapse(r16);
    }

    refreshData(i16, j16, k16, l16) {
        let m16 = new NodeInfo(new NodeItem(emptyNodeInfo));
        this.listNodeUtils = i16;
        this.listNodeUtils.traverseNodeDF((o16) => {
            if (o16.currentNodeId === k16) {
                m16 = new NodeInfo(o16);
                return true;
            }
            return false;
        });
        if (j16 === MenuOperation.REMOVE_NODE) {
            this.nodeIdAndSubtitleMap.set(k16, this.selectedParentNodeSubtitle);
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(k16));
            this.refreshRemoveNodeData(l16, m16);
        }
        if (j16 === MenuOperation.ADD_NODE) {
            this.addFocusNodeId = l16[0];
            this.nodeIdAndSubtitleMap.set(this.getClickNodeId(), this.selectedParentNodeSubtitle);
            this.nodeIdAndSubtitleMap.set(l16[0], this.insertNodeSubtitle);
            this.refreshAddNodeData(l16);
        }
    }

    setClickIndex(h16) {
        this.thisIndex = h16;
    }

    getClickNodeId() {
        if (this.thisIndex < 0 || this.thisIndex >= this.ListNode.length) {
            return -1;
        }
        return this.ListNode[this.thisIndex].getCurrentNodeId();
    }

    expandAndCollapseNode(g16) {
        this.changeNodeStatus(g16);
        this.handleExpandAndCollapse(g16);
    }

    getIsTouchDown() {
        return this.isTouchDown;
    }

    getLastIndex() {
        return this.lastIndex;
    }

    findIndex(b16) {
        let c16 = -1;
        this.ListNode.forEach((e16, f16) => {
            if (e16.getNodeCurrentNodeId() === b16) {
                c16 = f16;
            }
        });
        return c16;
    }

    handleEventDrag(a16) {
        this.setImageSource(a16, InteractionStatus.Normal);
        this.changeNodeColor(a16, this.listNode[a16].getNodeStatus().normal);
        this.handleFocusEffect(a16, false);
        this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.listNode[a16].getCurrentNodeId()));
    }

    handleEvent(v15, w15) {
        if (this.isDrag) {
            return;
        }
        if (v15 === Event.TOUCH_DOWN || v15 === Event.TOUCH_UP || v15 === Event.MOUSE_BUTTON_RIGHT) {
            if (w15 !== this.lastIndex) {
                this.clearLastIndexStatus();
            }
        }
        let x15 = this.loadedNodeIdAndIndexMap.get(this.listNode[w15].getCurrentNodeId());
        switch (v15) {
            case Event.TOUCH_DOWN:
                this.isTouchDown = true;
                this.changeNodeColor(w15, this.listNode[w15].getNodeStatus().press);
                this.notifyDataChange(x15);
                break;
            case Event.TOUCH_UP: {
                if (this.isInnerDrag) {
                    this.isInnerDrag = false;
                }
                this.isTouchDown = false;
                let z15 = this.listNode[w15];
                this.setImageSource(w15, InteractionStatus.Selected);
                z15.setFontColor(this.treeViewTheme.primaryTitleFontColor);
                this.lastIndex = w15;
                this.changeNodeColor(w15, z15.getNodeStatus().selected);
                this.notifyDataChange(x15);
                break;
            }
            case Event.HOVER:
                if (this.getNodeColor(w15) !== this.listNode[w15].getNodeStatus().selected) {
                    this.changeNodeColor(w15, this.listNode[w15].getNodeStatus().hover);
                    this.notifyDataChange(x15);
                }
                break;
            case Event.HOVER_OVER:
                if (this.getNodeColor(w15) !== this.listNode[w15].getNodeStatus().selected) {
                    this.changeNodeColor(w15, this.listNode[w15].getNodeStatus().normal);
                    this.notifyDataChange(x15);
                }
                break;
            case Event.FOCUS:
                this.handleFocusEffect(w15, true);
                this.notifyDataChange(x15);
                break;
            case Event.BLUR:
                this.handleFocusEffect(w15, false);
                this.notifyDataChange(x15);
                break;
            case Event.MOUSE_BUTTON_RIGHT:
                this.lastIndex = w15;
                this.finishEditing();
                break;
            case Event.DRAG:
                this.isTouchDown = false;
                let y15 = this.listNode[w15];
                this.setImageSource(w15, InteractionStatus.Selected);
                this.lastIndex = w15;
                this.changeNodeColor(w15, y15.getNodeStatus().selected);
                this.notifyDataChange(x15);
                break;
            default:
                break;
        }
    }

    notificationNodeInfo(m15, n15) {
        if (n15 === MenuOperation.MODIFY_NODE) {
            let t15 = this.listNode[this.modifyNodeIndex];
            let u15 = {
                currentNodeId: t15.getNodeCurrentNodeId(),
                parentNodeId: t15.getNodeParentNodeId(),
            };
            this.appEventBus.emit(TreeListenType.NODE_MODIFY, u15);
        }
        else if (n15 === MenuOperation.ADD_NODE) {
            let o15 = this.listNode[m15];
            let p15 = (o15.getNodeItem().imageNode !== undefined) ?
                o15.getNodeItem().imageNode?.source : undefined;
            let q15 = (o15.getNodeItem().imageNode !== undefined) ?
                o15.getNodeItem().imageNode?.selectedSource : undefined;
            let r15 = (o15.getNodeItem().imageNode !== undefined) ?
                o15.getNodeItem().imageNode?.editSource : undefined;
            let s15 = {
                currentNodeId: o15.getNodeCurrentNodeId(),
                parentNodeId: o15.getNodeParentNodeId(),
            };
            this.appEventBus.emit(TreeListenType.NODE_ADD, s15);
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

    setItemVisibilityOnEdit(g15, h15) {
        let i15 = -1;
        if (g15 === -1) {
            return;
        }
        if (h15 === MenuOperation.MODIFY_NODE) {
            for (let l15 = 0; l15 < this.listNode.length; l15++) {
                if (this.listNode[l15].getCurrentNodeId() === g15) {
                    i15 = l15;
                    break;
                }
            }
            let k15 = this.listNode[i15];
            k15.setIsModify(true);
            if (k15.getNodeItem().mainTitleNode === null) {
                return;
            }
            this.currentOperation = MenuOperation.MODIFY_NODE;
            k15.setTitleAndInputTextStatus(true);
            this.setImageSource(i15, InteractionStatus.Edit);
            this.setImageCollapseSource(i15, InteractionStatus.Edit);
            this.modifyNodeIndex = i15;
            if (k15.getNodeItem().inputText) {
                if (k15.getNodeItem().imageCollapse !== null) {
                    k15.getNodeItem().inputText.rightMargin = {
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.ohos_id_text_paragraph_margin_xs'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__',
                    };
                }
                else {
                    k15.getNodeItem().inputText.rightMargin = {
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.ohos_id_elements_margin_horizontal_m'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__',
                    };
                }
            }
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(g15));
        }
        i15 = g15;
        if (h15 === MenuOperation.COMMIT_NODE) {
            let j15 = this.listNode[i15];
            j15.setTitleAndInputTextStatus(false);
            j15.setIsModify(false);
            this.setImageSource(i15, InteractionStatus.FinishEdit);
            this.setImageCollapseSource(i15, InteractionStatus.FinishEdit);
            this.notificationNodeInfo(this.modifyNodeIndex, this.currentOperation);
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(j15.getCurrentNodeId()));
        }
    }

    setPopUpInfo(a15, b15, c15, d15) {
        let e15 = this.listNode[d15];
        e15.setPopUpIsShow(c15);
        let f15 = this.loadedNodeIdAndIndexMap.get(e15.getCurrentNodeId());
        if (!c15) {
            this.notifyDataChange(f15);
            return;
        }
        if (a15 === PopUpType.HINTS) {
            if (e15.getNodeItem().mainTitleNode !== null) {
                e15.setPopUpText(e15.getNodeItem().mainTitleNode?.title);
            }
            else {
                e15.setPopUpText('');
                e15.setPopUpIsShow(false);
            }
            e15.setPopUpEnableArrow(false);
            e15.setPopUpColor({
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_background'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            });
            e15.setPopUpTextColor({
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_text_secondary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            });
        }
        else if (a15 === PopUpType.WARNINGS) {
            if (e15.getNodeItem().inputText !== null) {
                if (b15 === InputError.INVALID_ERROR) {
                    e15.setPopUpText('invalid error');
                }
                else if (b15 === InputError.LENGTH_ERROR) {
                    e15.setPopUpText('length error');
                }
                e15.setPopUpEnableArrow(true);
                e15.setPopUpColor({
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_help_tip_bg'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                });
                e15.setPopUpTextColor({
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_text_hint_contrary'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                });
            }
        }
        this.notifyDataChange(f15);
    }

    setShowPopUpTimeout(x14, y14) {
        if (this.listNode[y14].getNodeItem().mainTitleNode !== null) {
            this.listNode[y14].getNodeItem().mainTitleNode.popUpTimeout = x14;
        }
        let z14 = this.loadedNodeIdAndIndexMap.get(this.listNode[y14].getCurrentNodeId());
        this.notifyDataChange(z14);
    }

    setMainTitleNameOnEdit(v14, w14) {
        this.modifyNodeIndex = v14;
        if (this.listNode[v14].getNodeItem().mainTitleNode !== null) {
            this.listNode[v14].getNodeItem().mainTitleNode.title = w14;
        }
    }

    get ListNode() {
        return this.listNode;
    }

    totalCount() {
        let s14 = 0;
        let t14 = 0;
        this.loadedNodeIdAndIndexMap.clear();
        for (let u14 = 0; u14 < this.listNode.length; u14++) {
            if (this.listNode[u14].getNodeIsShow()) {
                this.loadedNodeIdAndIndexMap.set(this.listNode[u14].getCurrentNodeId(), t14++);
                s14++;
            }
        }
        return s14;
    }

    getData(p14) {
        let q14 = 0;
        for (let r14 = 0; r14 < this.listNode.length; r14++) {
            if (this.listNode[r14].getNodeIsShow()) {
                if (p14 === q14) {
                    return this.listNode[r14];
                }
                q14++;
            }
        }
        return undefined;
    }

    addData(n14, o14) {
        this.listNode.splice(n14, 0, o14);
        this.notifyDataAdd(n14);
    }

    pushData(m14) {
        this.listNode.push(m14);
        this.notifyDataAdd(this.listNode.length - 1);
    }

    setIsInnerDrag(l14) {
        this.isInnerDrag = l14;
    }

    getIsInnerDrag() {
        return this.isInnerDrag;
    }

    setIsDrag(k14) {
        this.isDrag = k14;
    }

    getIsDrag() {
        return this.isDrag;
    }

    setCurrentNodeInfo(j14) {
        if (j14 === undefined) {
            return;
        }
        this.currentNodeInfo = j14;
    }

    getCurrentNodeInfo() {
        return this.currentNodeInfo;
    }

    setDraggingParentNodeId(i14) {
        if (i14 === undefined) {
            return;
        }
        this.draggingParentNodeId = i14;
    }

    getDraggingParentNodeId() {
        return this.draggingParentNodeId;
    }

    getDraggingCurrentNodeId() {
        return this.draggingCurrentNodeId;
    }

    setDraggingCurrentNodeId(h14) {
        if (h14 === undefined) {
            return;
        }
        this.draggingCurrentNodeId = h14;
    }

    setListItemOpacity(g14) {
        this.listItemOpacity = g14;
    }

    getListItemOpacity(f14) {
        return f14.getCurrentNodeId() === this.getDraggingCurrentNodeId() ? this.listItemOpacity : 1;
    }

    getDragPopupPara() {
        return this.DRAG_POPUP;
    }

    setLastPassIndex(e14) {
        this.lastPassIndex = e14;
    }

    getLastPassIndex() {
        return this.lastPassIndex;
    }

    getIsParentOfInsertNode(y13) {
        if (this.currentNodeInfo === null || y13 === undefined) {
            return false;
        }
        let z13 = this.currentNodeInfo.getNodeInfoNode();
        let a14 = false;
        let b14 = (d14) => {
            if (d14.currentNodeId === y13) {
                a14 = true;
                return true;
            }
            return false;
        };
        this.listNodeUtils.traverseNodeDF(b14, z13);
        return a14;
    }

    setPassIndex(x13) {
        this.thisPassIndex = x13;
    }

    getPassIndex() {
        return this.thisPassIndex;
    }

    clearTimeOutAboutDelayHighLightAndExpand(s13) {
        if (this.lastPassId !== this.INITIAL_INVALID_VALUE && this.loadedNodeIdAndIndexMap.has(this.lastPassId)) {
            let u13 = this.loadedNodeIdAndIndexMap.get(this.lastPassId);
            this.ListNode.forEach((w13) => {
                if (w13.getNodeCurrentNodeId() === this.lastPassId) {
                    w13.setCanShowFlagLine(false);
                }
            });
            this.notifyDataChange(u13);
        }
        if ((this.lastTimeoutHighLightId !== this.INITIAL_INVALID_VALUE &&
            this.clearTimeoutHighLightId !== this.lastTimeoutHighLightId)) {
            clearTimeout(this.lastTimeoutHighLightId);
            if (this.lastDelayHighLightIndex !== this.INITIAL_INVALID_VALUE) {
                this.clearHighLight(this.lastDelayHighLightIndex);
                let t13 = this.loadedNodeIdAndIndexMap
                    .get(this.listNode[this.lastDelayHighLightIndex].getCurrentNodeId());
                this.notifyDataChange(t13);
            }
            this.clearTimeoutHighLightId = this.lastTimeoutHighLightId;
        }
        this.lastTimeoutHighLightId = this.timeoutHighLightId;
        this.lastDelayHighLightIndex = s13;
        if ((this.lastTimeoutExpandId !== this.INITIAL_INVALID_VALUE &&
            this.clearTimeoutExpandId !== this.lastTimeoutExpandId)) {
            clearTimeout(this.lastTimeoutExpandId);
            this.clearTimeoutExpandId = this.lastTimeoutExpandId;
        }
        this.lastTimeoutExpandId = this.timeoutExpandId;
        this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE;
    }

    clearHighLight(r13) {
        this.changeNodeColor(r13, this.listNode[r13].getNodeStatus().normal);
        this.changeNodeHighLightColor(r13, false);
        this.setImageSource(r13, InteractionStatus.FinishDragInsert);
        this.setImageCollapseSource(r13, InteractionStatus.FinishDragInsert);
        this.listNode[r13].setIsHighLight(false);
    }

    changeNodeHighLightColor(p13, q13) {
        if (this.listNode[p13].getNodeItem().mainTitleNode && this.listNode[p13].getIsShowTitle()) {
            this.listNode[p13].getNodeItem().mainTitleNode?.setMainTitleHighLight(q13);
        }
    }

    setVisibility(g13, h13, i13) {
        let j13 = (this.thisPassIndex !== h13 || this.flag !== g13) ? true : false;
        this.thisPassIndex = h13;
        if ((j13 || i13) && this.isInnerDrag) {
            this.flag = g13;
            let k13 = this.getData(h13)?.getCurrentNodeId();
            let l13 = this.getData(h13)?.getNodeLevel();
            if (k13 !== undefined) {
                l13 = (this.expandAndCollapseInfo.get(k13) === NodeStatus.Expand &&
                    this.flag === Flag.DOWN_FLAG) ? (l13 ? l13 + 1 : undefined) : l13;
                if (this.lastPassId !== this.INITIAL_INVALID_VALUE && this.loadedNodeIdAndIndexMap.has(this.lastPassId)) {
                    let m13 = this.loadedNodeIdAndIndexMap.get(this.lastPassId);
                    this.ListNode.forEach((o13) => {
                        if (o13.getNodeCurrentNodeId() === this.lastPassId) {
                            o13.setCanShowFlagLine(false);
                        }
                    });
                    this.notifyDataChange(m13);
                }
                if (this.flag === Flag.DOWN_FLAG && h13 < this.totalCount() - 1) {
                    this.getData(h13)?.setCanShowFlagLine(false);
                    this.getData(h13 + 1)?.setCanShowFlagLine(true);
                    this.getData(h13)?.setCanShowBottomFlagLine(false);
                    this.getData(h13 + 1)?.setFlagLineLeftMargin(l13);
                    this.notifyDataChange(h13);
                    this.notifyDataChange(h13 + 1);
                    this.lastPassId = this.getData(h13 + 1)?.getNodeCurrentNodeId();
                }
                else if (this.flag === Flag.UP_FLAG && h13 < this.totalCount() - 1) {
                    this.getData(h13)?.setCanShowFlagLine(true);
                    this.getData(h13 + 1)?.setCanShowFlagLine(false);
                    this.getData(h13)?.setCanShowBottomFlagLine(false);
                    this.getData(h13)?.setFlagLineLeftMargin(l13);
                    this.notifyDataChange(h13);
                    this.notifyDataChange(h13 + 1);
                    this.lastPassId = this.getData(h13)?.getNodeCurrentNodeId();
                }
                else if (h13 >= this.totalCount() - 1) {
                    if (this.flag === Flag.DOWN_FLAG) {
                        this.getData(h13)?.setCanShowFlagLine(false);
                        this.getData(h13)?.setCanShowBottomFlagLine(true);
                    }
                    else {
                        this.getData(h13)?.setCanShowFlagLine(true);
                        this.getData(h13)?.setCanShowBottomFlagLine(false);
                    }
                    this.getData(h13)?.setFlagLineLeftMargin(l13);
                    this.notifyDataChange(h13);
                    this.lastPassId = this.getData(h13)?.getNodeCurrentNodeId();
                }
            }
        }
    }

    delayHighLightAndExpandNode(v12, w12, x12) {
        let y12 = v12 !== this.lastDelayExpandIndex ? true : false;
        let z12 = this.getData(x12)?.getIsOverBorder();
        if (z12) {
            this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE;
        }
        else {
            this.lastDelayExpandIndex = v12;
        }
        if (z12 || y12) {
            let a13 = !z12 && (!this.isInnerDrag ||
                (this.expandAndCollapseInfo.get(w12) === NodeStatus.Collapse && this.isInnerDrag) ||
                (!this.expandAndCollapseInfo.has(w12) && this.listNode[v12].getIsFolder()));
            if (a13) {
                this.changeNodeColor(v12, this.listNode[v12].getNodeStatus().hover);
                this.notifyDataChange(x12);
                let e13 = this.isInnerDrag ? 1000 : 0;
                this.timeoutHighLightId = setTimeout(() => {
                    this.delayHighLight(v12);
                }, e13);
            }
            if (z12 || (this.lastTimeoutHighLightId !== this.INITIAL_INVALID_VALUE &&
                this.clearTimeoutHighLightId !== this.lastTimeoutHighLightId)) {
                clearTimeout(this.lastTimeoutHighLightId);
                if (this.lastDelayHighLightIndex !== this.INITIAL_INVALID_VALUE) {
                    this.clearHighLight(this.lastDelayHighLightIndex);
                    this.notifyDataReload();
                }
                this.clearTimeoutHighLightId = this.lastTimeoutHighLightId;
            }
            this.lastTimeoutHighLightId = this.timeoutHighLightId;
            this.lastDelayHighLightIndex = v12;
            if (!z12 && this.expandAndCollapseInfo.get(w12) === NodeStatus.Collapse) {
                let b13 = this.getData(x12)?.getNodeInfoNode().children[0].currentNodeId;
                let c13 = 2000;
                this.timeoutExpandId = setTimeout(() => {
                    this.clearHighLight(this.lastDelayHighLightIndex);
                    if (b13 !== undefined) {
                        this.alterFlagLineAndExpandNode(v12, b13);
                    }
                }, c13);
            }
            if (z12 || (this.lastTimeoutExpandId !== this.INITIAL_INVALID_VALUE &&
                this.clearTimeoutExpandId !== this.lastTimeoutExpandId)) {
                clearTimeout(this.lastTimeoutExpandId);
                this.clearTimeoutExpandId = this.lastTimeoutExpandId;
            }
            this.lastTimeoutExpandId = this.timeoutExpandId;
        }
    }

    delayHighLight(s12) {
        this.ListNode.forEach((u12) => {
            if (u12.getNodeCurrentNodeId() === this.lastPassId) {
                u12.setCanShowFlagLine(false);
                u12.setCanShowBottomFlagLine(false);
            }
        });
        this.changeNodeColor(s12, this.listNode[s12].getNodeStatus().highLight);
        this.listNode[s12].setIsHighLight(true);
        this.changeNodeHighLightColor(s12, true);
        this.setImageSource(s12, InteractionStatus.DragInsert);
        this.setImageCollapseSource(s12, InteractionStatus.DragInsert);
        this.notifyDataReload();
    }

    alterFlagLineAndExpandNode(m12, n12) {
        this.ListNode.forEach((r12) => {
            if (r12.getNodeCurrentNodeId() === this.lastPassId) {
                r12.setCanShowFlagLine(false);
                r12.setCanShowBottomFlagLine(false);
            }
        });
        this.ListNode.forEach((q12) => {
            if (this.isInnerDrag && q12.getNodeCurrentNodeId() === n12) {
                q12.setCanShowFlagLine(true);
            }
        });
        this.changeNodeStatus(m12);
        this.handleExpandAndCollapse(m12);
        this.lastPassId = n12;
    }

    hideLastLine() {
        if (this.lastPassId !== this.INITIAL_INVALID_VALUE && this.loadedNodeIdAndIndexMap.has(this.lastPassId)) {
            this.ListNode.forEach((l12) => {
                if (l12.getNodeCurrentNodeId() === this.lastPassId) {
                    l12.setCanShowFlagLine(false);
                    l12.setCanShowBottomFlagLine(false);
                }
            });
            let j12 = this.loadedNodeIdAndIndexMap.get(this.lastPassId);
            this.notifyDataChange(j12);
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

    getSubtitle(i12) {
        if (this.nodeIdAndSubtitleMap.has(i12)) {
            if (typeof this.nodeIdAndSubtitleMap.get(i12) === 'number') {
                return this.nodeIdAndSubtitleMap.get(i12)?.toString();
            }
            else {
                return this.nodeIdAndSubtitleMap.get(i12);
            }
        }
        else {
            return '';
        }
    }

    hasSubtitle(h12) {
        return this.nodeIdAndSubtitleMap.has(h12);
    }

    initialParameterAboutDelayHighLightAndExpandIndex() {
        this.lastDelayHighLightIndex = this.INITIAL_INVALID_VALUE;
        this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE;
        this.lastPassIndex = this.INITIAL_INVALID_VALUE;
        this.draggingCurrentNodeId = this.INITIAL_INVALID_VALUE;
        this.flag = Flag.NONE;
    }

    refreshSubtitle(g12) {
        this.nodeIdAndSubtitleMap.set(this.selectedParentNodeId, this.selectedParentNodeSubtitle);
        this.nodeIdAndSubtitleMap.set(g12, this.insertNodeSubtitle);
        this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.selectedParentNodeId));
        this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(g12));
    }

    setNodeSubtitlePara(d12, e12, f12) {
        this.selectedParentNodeId = d12;
        this.selectedParentNodeSubtitle = e12;
        this.insertNodeSubtitle = f12;
    }

    getInsertNodeSubtitle() {
        return this.insertNodeSubtitle;
    }

    getExpandAndCollapseInfo(c12) {
        return this.expandAndCollapseInfo.get(c12);
    }

    getLastDelayHighLightId() {
        return this.lastDelayHighLightId;
    }

    setLastDelayHighLightId() {
        this.ListNode.forEach((a12, b12) => {
            if (b12 === this.lastDelayHighLightIndex) {
                this.lastDelayHighLightId = a12.getCurrentNodeId();
            }
        });
    }

    setLastPassId(y11) {
        this.lastPassId = y11;
    }

    setLastDelayHighLightIndex(x11) {
        this.lastDelayHighLightIndex = x11;
    }

    alterDragNode(s10, t10, u10, v10, w10) {
        let x10 = [];
        let y10 = s10;
        let z10 = v10;
        let a11 = w10.getNodeInfoData();
        let b11 = null;
        let c11 = w10.getNodeInfoNode();
        let d11 = false;
        let e11 = this.INITIAL_INVALID_VALUE;
        let f11 = this.INITIAL_INVALID_VALUE;
        let g11 = this.flag === Flag.DOWN_FLAG ? true : false;
        f11 = this.getChildIndex(u10, v10);
        e11 = this.getChildIndex(s10, t10) + 1;
        if (s10 !== u10) {
            e11 = g11 ? e11 + 1 : e11;
        }
        else {
            if (e11 > f11) {
                e11 = g11 ? e11 : e11 - 1;
            }
            else {
                e11 = g11 ? e11 + 1 : e11;
            }
        }
        for (let w11 = 0; w11 < this.listNode.length; w11++) {
            if (this.listNode[w11].getCurrentNodeId() === t10) {
                d11 = this.listNode[w11].getIsHighLight();
                if (this.flag === Flag.DOWN_FLAG && this.expandAndCollapseInfo.get(t10) === NodeStatus.Expand) {
                    y10 = t10;
                    e11 = 0;
                }
                else if (this.flag === Flag.UP_FLAG && this.expandAndCollapseInfo.get(t10) === NodeStatus.Expand
                    && this.listNode[w11].getCanShowFlagLine() === false) {
                    y10 = t10;
                    e11 = 0;
                }
                else if (d11) {
                    y10 = t10;
                    e11 = 0;
                }
                break;
            }
        }
        let h11 = {
            currentNodeId: z10,
            parentNodeId: y10,
            childIndex: e11,
        };
        this.appEventBus.emit(TreeListenType.NODE_MOVE, h11);
        x10.push({ parentId: y10, currentId: z10, data: a11 });
        let i11 = null;
        let j11 = (s11, t11) => {
            if (s11) {
                i11 = s11;
                y10 = i11.parentNodeId;
                z10 = i11.currentNodeId;
                for (let v11 = 0; v11 < t11.length; v11++) {
                    if (t11[v11].getNodeCurrentNodeId() === z10) {
                        b11 = t11[v11];
                        break;
                    }
                }
                if (b11 === null) {
                    return false;
                }
                let u11 = b11.getNodeInfoData();
                if (y10 !== u10) {
                    x10.push({ parentId: y10, currentId: z10, data: u11 });
                }
                return false;
            }
            return false;
        };
        this.listNodeUtils.dragTraverseNodeDF(j11, c11, this.listNode);
        this.listNodeUtils.removeNode(v10, u10);
        let k11 = t10;
        let l11 = g11;
        if (this.expandAndCollapseInfo.get(t10) === NodeStatus.Expand) {
            l11 = false;
            this.listNode.forEach((r11) => {
                if (r11.getCurrentNodeId() === t10 && r11.getCanShowFlagLine() === false) {
                    if (r11.getNodeInfoNode().children.length) {
                        k11 = r11.getNodeInfoNode().children[0].currentNodeId;
                    }
                    else {
                        k11 = this.INITIAL_INVALID_VALUE;
                    }
                }
            });
        }
        else if (!this.expandAndCollapseInfo.get(t10) && d11) {
            this.expandAndCollapseInfo.set(t10, NodeStatus.Expand);
        }
        this.listNodeUtils.addDragNode(x10[0].parentId, x10[0].currentId, k11, l11, x10[0].data);
        for (let p11 = 1; p11 < x10.length; p11++) {
            this.listNodeUtils.addNode(x10[p11].parentId, x10[p11].currentId, x10[p11].data);
        }
        for (let o11 = 0; o11 < this.listNode.length; o11++) {
            if (this.listNode[o11].getCurrentNodeId() === u10) {
                if (this.listNode[o11].getNodeInfoNode().getNodeItem().imageCollapse === null) {
                    this.listNode[o11].handleImageCollapseAfterAddNode(false);
                    this.expandAndCollapseInfo.delete(u10);
                    break;
                }
            }
        }
        let m11 = [...this.listNode];
        this.reloadListNode(this.listNodeUtils, m11);
    }

    reloadListNode(l10, m10) {
        let n10 = 0;
        this.listNode = [];
        this.listNodeUtils = l10;
        this.loadedNodeIdAndIndexMap.clear();
        this.listNodeUtils.traverseNodeDF((p10) => {
            if (p10.currentNodeId >= 0) {
                let q10 = new NodeInfo(p10);
                this.listNode.push(q10);
                if (this.expandAndCollapseInfo.get(p10.currentNodeId) === NodeStatus.Expand) {
                    q10.getNodeItem().imageCollapse?.changeImageCollapseSource(NodeStatus.Expand);
                }
                else if (this.expandAndCollapseInfo.get(p10.currentNodeId) === NodeStatus.Collapse) {
                    q10.getNodeItem().imageCollapse?.changeImageCollapseSource(NodeStatus.Collapse);
                }
                for (let r10 = 0; r10 < m10.length; r10++) {
                    if (m10[r10].getCurrentNodeId() === q10.getCurrentNodeId()) {
                        q10.setNodeIsShow(m10[r10].getNodeIsShow());
                        q10.setListItemHeight(m10[r10].getListItemHeight());
                        if (q10.getNodeItem().mainTitleNode && q10.getIsShowTitle()) {
                            q10.getNodeItem().mainTitleNode.title = m10[r10].getNodeItem().mainTitleNode?.title;
                        }
                        break;
                    }
                }
                if (q10.getNodeIsShow()) {
                    this.loadedNodeIdAndIndexMap.set(q10.getCurrentNodeId(), n10++);
                }
            }
            return false;
        });
    }

    getFlagLine() {
        return this.FLAG_LINE;
    }

    getVisibility(i10) {
        let j10 = this.loadedNodeIdAndIndexMap.get(i10.getCurrentNodeId()) - 1;
        if (j10 > this.INITIAL_INVALID_VALUE) {
            let k10 = this.getData(j10);
            return (i10.getCanShowFlagLine() === true && !i10.getIsHighLight() && !k10?.getIsHighLight()) ?
            Visibility.Visible : Visibility.Hidden;
        }
        else {
            return (i10.getCanShowFlagLine() === true && !i10.getIsHighLight()) ?
            Visibility.Visible : Visibility.Hidden;
        }
    }

    getSubTitlePara() {
        return this.subTitle;
    }

    getIsFolder(h10) {
        if (this.loadedNodeIdAndIndexMap.has(h10)) {
            return this.getData(this.loadedNodeIdAndIndexMap.get(h10))?.getIsFolder();
        }
        return false;
    }

    getSubTitleFontColor(g10) {
        return g10 ? this.subTitle.highLightFontColor : this.treeViewTheme.secondaryTitleFontColor;
    }

    getChildIndex(y9, z9) {
        let a10 = this.INITIAL_INVALID_VALUE;
        this.listNodeUtils.traverseNodeBF((c10) => {
            if (c10.getCurrentNodeId() === y9) {
                c10.children.forEach((e10, f10) => {
                    if (e10.getCurrentNodeId() === z9) {
                        a10 = f10;
                    }
                });
                return true;
            }
            return false;
        });
        return a10;
    }

    setCurrentFocusNodeId(x9) {
        this.currentFocusNodeId = x9;
    }

    getCurrentFocusNodeId() {
        return this.currentFocusNodeId;
    }

    setLastFocusNodeId(w9) {
        this.lastFocusNodeId = w9;
    }

    getLastFocusNodeId() {
        return this.lastFocusNodeId;
    }

    getAddFocusNodeId() {
        return this.addFocusNodeId;
    }

    setFlag(v9) {
        this.flag = v9;
    }
}

export class TreeViewInner extends ViewPU {
    constructor(p9, q9, r9, s9 = -1, t9 = undefined, u9) {
        super(p9, r9, s9, u9);
        if (typeof t9 === 'function') {
            this.paramsGenerator_ = t9;
        }
        this.__item = new SynchedPropertyNesedObjectPU(q9.item, this, 'item');
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
            bottom: '0vp',
        };
        this.textInputPadding = { left: '0vp', right: '0vp', top: '0vp', bottom: '0vp' };
        this.setInitiallyProvidedValue(q9);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(o9) {
        this.__item.set(o9.item);
        if (o9.listNodeDataSource !== undefined) {
            this.listNodeDataSource = o9.listNodeDataSource;
        }
        if (o9.columnWidth !== undefined) {
            this.columnWidth = o9.columnWidth;
        }
        if (o9.isFocused !== undefined) {
            this.isFocused = o9.isFocused;
        }
        if (o9.index !== undefined) {
            this.index = o9.index;
        }
        if (o9.lastIndex !== undefined) {
            this.lastIndex = o9.lastIndex;
        }
        if (o9.count !== undefined) {
            this.count = o9.count;
        }
        if (o9.listTreeViewMenu !== undefined) {
            this.listTreeViewMenu = o9.listTreeViewMenu;
        }
        if (o9.MAX_CN_LENGTH !== undefined) {
            this.MAX_CN_LENGTH = o9.MAX_CN_LENGTH;
        }
        if (o9.MAX_EN_LENGTH !== undefined) {
            this.MAX_EN_LENGTH = o9.MAX_EN_LENGTH;
        }
        if (o9.INITIAL_INVALID_VALUE !== undefined) {
            this.INITIAL_INVALID_VALUE = o9.INITIAL_INVALID_VALUE;
        }
        if (o9.MAX_TOUCH_DOWN_COUNT !== undefined) {
            this.MAX_TOUCH_DOWN_COUNT = o9.MAX_TOUCH_DOWN_COUNT;
        }
        if (o9.isMultiPress !== undefined) {
            this.isMultiPress = o9.isMultiPress;
        }
        if (o9.touchDownCount !== undefined) {
            this.touchDownCount = o9.touchDownCount;
        }
        if (o9.appEventBus !== undefined) {
            this.appEventBus = o9.appEventBus;
        }
        if (o9.itemPadding !== undefined) {
            this.itemPadding = o9.itemPadding;
        }
        if (o9.textInputPadding !== undefined) {
            this.textInputPadding = o9.textInputPadding;
        }
    }

    updateStateVars(n9) {
        this.__item.set(n9.item);
    }

    purgeVariableDependenciesOnElmtId(m9) {
        this.__item.purgeDependencyOnElmtId(m9);
        this.__columnWidth.purgeDependencyOnElmtId(m9);
        this.__isFocused.purgeDependencyOnElmtId(m9);
        this.__index.purgeDependencyOnElmtId(m9);
        this.__lastIndex.purgeDependencyOnElmtId(m9);
        this.__count.purgeDependencyOnElmtId(m9);
        this.__treeViewTheme.purgeDependencyOnElmtId(m9);
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

    set columnWidth(l9) {
        this.__columnWidth.set(l9);
    }

    get isFocused() {
        return this.__isFocused.get();
    }

    set isFocused(k9) {
        this.__isFocused.set(k9);
    }

    get index() {
        return this.__index.get();
    }

    set index(j9) {
        this.__index.set(j9);
    }

    get lastIndex() {
        return this.__lastIndex.get();
    }

    set lastIndex(i9) {
        this.__lastIndex.set(i9);
    }

    get count() {
        return this.__count.get();
    }

    set count(h9) {
        this.__count.set(h9);
    }

    get treeViewTheme() {
        return this.__treeViewTheme.get();
    }

    set treeViewTheme(g9) {
        this.__treeViewTheme.set(g9);
    }

    aboutToAppear() {
        if (this.item.getNodeItem().imageNode) {
            this.item.imageSource = this.item.getNodeItem().imageNode?.source;
        }
    }

    checkInvalidPattern(f9) {
        return new RegExp("/[\\\/:*?' < > |]/").test(f9);
    }

    checkIsAllCN(e9) {
        return new RegExp('/^[\u4e00-\u9fa5]+$/').test(e9);
    }

    popupForShowTitle(u8, v8, w8, x8 = null) {
        this.observeComponentCreation((c9, d9) => {
            ViewStackProcessor.StartGetAccessRecordingFor(c9);
            Row.create();
            Row.backgroundColor(v8);
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
            if (!d9) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((a9, b9) => {
            ViewStackProcessor.StartGetAccessRecordingFor(a9);
            Text.create(u8);
            Text.fontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_body2'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            });
            Text.fontWeight('regular');
            Text.fontColor(w8);
            if (!b9) {
                Text.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        Text.pop();
        Row.pop();
    }

    builder(o8 = null) {
        this.observeComponentCreation((q8, r8) => {
            ViewStackProcessor.StartGetAccessRecordingFor(q8);
            If.create();
            if (this.listTreeViewMenu) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.listTreeViewMenu.bind(this)(o8 ? o8 : this);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!r8) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
    }

    initialRender() {
        this.observeComponentCreation((n4, o4) => {
            ViewStackProcessor.StartGetAccessRecordingFor(n4);
            If.create();
            if (this.item.getNodeIsShow()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((m8, n8) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(m8);
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
                        if (!n8) {
                            Stack.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((w7, x7) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(w7);
                        Column.create();
                        Column.opacity(this.listNodeDataSource.getListItemOpacity(ObservedObject.GetRawObject(this.item)));
                        Column.onHover((l8) => {
                            if (l8) {
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
                        Column.onTouch((h8) => {
                            this.count++;
                            if (this.count > 1) {
                                this.count--;
                                return;
                            }
                            let i8 = this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId());
                            this.listNodeDataSource.setClickIndex(this.index);
                            let j8 = this.item.getNodeCurrentNodeId();
                            if (h8.type === TouchType.Down) {
                                this.item.setNodeColor(this.treeViewTheme.itemPressedBgColor);
                            }
                            else if (h8.type === TouchType.Up) {
                                this.item.setNodeColor(COLOR_SELECT);
                                if (this.item.getNodeItem().imageNode !== null) {
                                    this.item.getNodeItem().imageNode?.setImageSource(InteractionStatus.Selected);
                                    this.item.imageSource = this.item.getNodeItem().imageNode?.source;
                                }
                                this.item.getNodeItem().mainTitleNode?.setMainTitleSelected(true);
                                let k8 = { currentNodeId: j8 };
                                this.appEventBus.emit(TreeListenType.NODE_CLICK, k8);
                            }
                            if (this.listNodeDataSource.getLastIndex() !== -1 && i8 !== this.listNodeDataSource.getLastIndex()) {
                                this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false, this.listNodeDataSource.getLastIndex());
                                this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(), MenuOperation.COMMIT_NODE);
                            }
                            this.lastIndex = i8;
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
                        Column.onMouse((f8) => {
                            let g8 = findCurrentNodeIndex(this.listNodeDataSource, this.item.getNodeCurrentNodeId());
                            if (f8.button === MouseButton.Right) {
                                this.listNodeDataSource.handleEvent(Event.MOUSE_BUTTON_RIGHT, findCurrentNodeIndex(this.listNodeDataSource, this.item.getNodeCurrentNodeId()));
                                this.listTreeViewMenu = this.item.getMenu();
                                this.listNodeDataSource.setClickIndex(g8);
                                clearTimeout(this.item.getNodeItem().mainTitleNode?.popUpTimeout);
                            }
                            f8.stopPropagation();
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
                        Column.onAreaChange((c8, d8) => {
                            let e8 = Number.parseInt(d8.width.toString());
                            this.columnWidth = e8;
                        });
                        if (!x7) {
                            Column.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((u7, v7) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(u7);
                        Stack.create({ alignContent: Alignment.Bottom });
                        Stack.focusable(true);
                        if (!v7) {
                            Stack.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((s7, t7) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(s7);
                        Divider.create();
                        Divider.height(this.listNodeDataSource.getFlagLine().flagLineHeight);
                        Divider.color(this.listNodeDataSource.getFlagLine().flagLineColor);
                        Divider.visibility(this.listNodeDataSource.getVisibility(ObservedObject.GetRawObject(this.item)));
                        Divider.lineCap(LineCapStyle.Round);
                        Divider.margin({ left: this.item.getFlagLineLeftMargin() });
                        Divider.focusable(true);
                        if (!t7) {
                            Divider.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((o7, p7) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(o7);
                        Row.create({});
                        Row.focusable(true);
                        Row.width('100%');
                        Gesture.create(GesturePriority.Low);
                        TapGesture.create({ count: 2 });
                        TapGesture.onAction((r7) => {
                            this.listNodeDataSource.expandAndCollapseNode(findCurrentNodeIndex(this.listNodeDataSource, this.item.getNodeCurrentNodeId()));
                        });
                        TapGesture.pop();
                        Gesture.pop();
                        Row.height(this.item.getNodeHeight());
                        Row.padding({ left: this.item.getNodeLeftPadding() });
                        Row.bindContextMenu({ builder: this.builder.bind(this) }, ResponseType.RightClick);
                        if (!p7) {
                            Row.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((e7, f7) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(e7);
                        If.create();
                        if (this.item.getNodeItem().imageNode) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation((m7, n7) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(m7);
                                    Row.create();
                                    Row.focusable(true);
                                    Row.backgroundColor(COLOR_IMAGE_ROW);
                                    Row.margin({ right: this.item.getNodeItem().imageNode?.itemRightMargin });
                                    Row.height(this.item.getNodeItem().imageNode?.itemHeight);
                                    Row.width(this.item.getNodeItem().imageNode?.itemWidth);
                                    if (!n7) {
                                        Row.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                this.observeComponentCreation((k7, l7) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(k7);
                                    Image.create(this.item.imageSource);
                                    Image.objectFit(ImageFit.Contain);
                                    Image.height(this.item.getNodeItem().imageNode?.itemHeight);
                                    Image.width(this.item.getNodeItem().imageNode?.itemWidth);
                                    Image.opacity(!this.item.getIsSelected() && !this.item.getIsHighLight() ?
                                        this.item.getNodeItem().imageNode?.opacity : this.item.getNodeItem().imageNode?.noOpacity);
                                    Image.focusable(this.item.getNodeItem().mainTitleNode !== null ? false : true);
                                    Image.fillColor(!this.item.getIsSelected() && !this.item.getIsHighLight() ?
                                    this.treeViewTheme.leftIconColor : this.treeViewTheme.leftIconActiveColor);
                                    if (!l7) {
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
                        if (!f7) {
                            If.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    If.pop();
                    this.observeComponentCreation((c7, d7) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(c7);
                        Row.create();
                        Row.layoutWeight(1);
                        Row.focusable(true);
                        if (!d7) {
                            Row.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((v6, w6) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(v6);
                        If.create();
                        if (this.item.getNodeItem().mainTitleNode && this.item.getIsShowTitle()) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation((a7, b7) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(a7);
                                    Text.create(this.item.getNodeItem().mainTitleNode?.title);
                                    Text.maxLines(1);
                                    Text.fontSize(this.item.getNodeItem().mainTitleNode?.size);
                                    Text.fontColor(this.item.getIsSelected() ?
                                    this.treeViewTheme.primaryTitleActiveFontColor : this.treeViewTheme.primaryTitleFontColor);
                                    Text.margin({ right: this.item.getNodeItem().mainTitleNode?.itemRightMargin });
                                    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                                    Text.fontWeight(this.item.getNodeItem().mainTitleNode?.weight);
                                    Text.focusable(true);
                                    if (!b7) {
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
                        if (!w6) {
                            If.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    If.pop();
                    this.observeComponentCreation((b6, c6) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(b6);
                        If.create();
                        if (this.item.getNodeItem().mainTitleNode && this.item.getNodeItem().inputText &&
                        this.item.getIsShowInputText()) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation((t6, u6) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(t6);
                                    Row.create();
                                    Row.backgroundColor(this.item.getNodeItem().inputText?.backgroundColor);
                                    Row.borderRadius(this.item.getNodeItem().inputText?.borderRadius);
                                    Row.margin({ right: this.item.getNodeItem().inputText?.itemRightMargin });
                                    if (!u6) {
                                        Row.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                this.observeComponentCreation((h6, i6) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(h6);
                                    TextInput.create({ text: this.item.getNodeItem().mainTitleNode?.title });
                                    TextInput.height(this.item.getNodeItem().inputText?.itemHeight);
                                    TextInput.fontSize(this.item.getNodeItem().inputText?.size);
                                    TextInput.fontColor(this.item.getNodeItem().inputText?.color);
                                    TextInput.borderRadius(this.item.getNodeItem().inputText?.borderRadius);
                                    TextInput.backgroundColor(this.item.getNodeItem().inputText?.backgroundColor);
                                    TextInput.enterKeyType(EnterKeyType.Done);
                                    TextInput.focusable(true);
                                    TextInput.padding({
                                        left: this.textInputPadding.left, right: this.textInputPadding.right,
                                        top: this.textInputPadding.top, bottom: this.textInputPadding.bottom,
                                    });
                                    TextInput.onChange((n6) => {
                                        let o6 = findCurrentNodeIndex(this.listNodeDataSource, this.item.getNodeCurrentNodeId());
                                        let p6 = '';
                                        let q6 = false;
                                        let r6 = false;
                                        if (this.checkInvalidPattern(n6)) {
                                            for (let s6 = 0; s6 < n6.length; s6++) {
                                                if (!this.checkInvalidPattern(n6[s6])) {
                                                    p6 += n6[s6];
                                                }
                                            }
                                            q6 = true;
                                            this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.INVALID_ERROR, true, o6);
                                        }
                                        else {
                                            p6 = n6;
                                            q6 = false;
                                        }
                                        if ((this.checkIsAllCN(p6) && p6.length > this.MAX_CN_LENGTH) ||
                                            (!this.checkIsAllCN(p6) && p6.length > this.MAX_EN_LENGTH)) {
                                            p6 = this.checkIsAllCN(p6) ?
                                            p6.substr(0, this.MAX_CN_LENGTH) : p6.substr(0, this.MAX_EN_LENGTH);
                                            r6 = true;
                                            this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.LENGTH_ERROR, true, o6);
                                        }
                                        else {
                                            r6 = false;
                                        }
                                        if (!r6 && !q6) {
                                            this.listNodeDataSource.setMainTitleNameOnEdit(o6, p6);
                                        }
                                    });
                                    TextInput.onSubmit((l6) => {
                                        let m6 = findCurrentNodeIndex(this.listNodeDataSource, this.item.getNodeCurrentNodeId());
                                        this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false, m6);
                                        this.listNodeDataSource.setItemVisibilityOnEdit(m6, MenuOperation.COMMIT_NODE);
                                    });
                                    if (!i6) {
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
                        if (!c6) {
                            If.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    If.pop();
                    this.observeComponentCreation((z5, a6) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(z5);
                        Blank.create();
                        if (!a6) {
                            Blank.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    Blank.pop();
                    Row.pop();
                    this.observeComponentCreation((p5, q5) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(p5);
                        If.create();
                        if (this.listNodeDataSource.hasSubtitle(this.item.getCurrentNodeId())) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation((x5, y5) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(x5);
                                    Row.create();
                                    Row.focusable(true);
                                    Row.margin({ left: this.listNodeDataSource.getSubTitlePara().margin.left,
                                        right: this.item.getNodeItem().imageCollapse ?
                                            0 : this.listNodeDataSource.getSubTitlePara().margin.right });
                                    if (!y5) {
                                        Row.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                this.observeComponentCreation((v5, w5) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(v5);
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
                                    if (!w5) {
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
                        if (!q5) {
                            If.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    If.pop();
                    this.observeComponentCreation((d5, e5) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(d5);
                        If.create();
                        if (this.item.getNodeItem().imageCollapse) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation((n5, o5) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(n5);
                                    Row.create();
                                    Row.focusable(true);
                                    Row.height(this.item.getNodeItem().imageCollapse?.itemHeight);
                                    Row.width(this.item.getNodeItem().imageCollapse?.itemWidth);
                                    if (!o5) {
                                        Row.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                this.observeComponentCreation((j5, k5) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(j5);
                                    Image.create(this.item.getNodeItem().imageCollapse?.collapseSource);
                                    Image.fillColor(this.item.getNodeItem().imageCollapse?.isCollapse ? COLOR_IMAGE_ROW : COLOR_IMAGE_EDIT);
                                    Image.align(Alignment.End);
                                    Image.objectFit(ImageFit.Contain);
                                    Image.height(this.item.getNodeItem().imageCollapse?.itemHeight);
                                    Image.width(this.item.getNodeItem().imageCollapse?.itemWidth);
                                    Image.opacity(!this.item.getIsHighLight() ?
                                        this.item.getNodeItem().imageCollapse?.opacity : this.item.getNodeItem().imageCollapse?.noOpacity);
                                    Image.onTouch((m5) => {
                                        if (m5.type === TouchType.Down) {
                                            this.listNodeDataSource.expandAndCollapseNode(findCurrentNodeIndex(this.listNodeDataSource, this.item.getNodeCurrentNodeId()));
                                            this.listNodeDataSource.setCurrentFocusNodeId(this.item.getCurrentNodeId());
                                        }
                                        m5.stopPropagation();
                                    });
                                    Image.focusable(true);
                                    if (!k5) {
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
                        if (!e5) {
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
            if (!o4) {
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
    constructor(l4) {
        this.data = l4;
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
        this.container = l4.container;
        if (l4.icon) {
            this.nodeItem.imageNode = new ImageNode(l4.icon, {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_alpha_content_fourth'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            }, IMAGE_NODE_HEIGHT, IMAGE_NODE_WIDTH, l4.selectedIcon, l4.editIcon);
        }
        if (l4.primaryTitle) {
            this.nodeItem.mainTitleNode = new MainTitleNode(l4.primaryTitle);
        }
        this.children = [];
    }

    addImageCollapse(k4) {
        if (k4) {
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

    set itemWidth(j4) {
        this.width = j4;
    }

    get itemWidth() {
        return this.width;
    }

    set itemHeight(i4) {
        this.height = i4;
    }

    get itemHeight() {
        return this.height;
    }

    set itemRightMargin(h4) {
        this.rightMargin = h4;
    }

    get itemRightMargin() {
        return this.rightMargin;
    }
}

export class ImageNode extends NodeBaseInfo {
    constructor(b4, c4, d4, e4, f4, g4) {
        super();
        this.rightMargin = {
            'id': -1,
            'type': 10002,
            params: ['sys.float.ohos_id_elements_margin_horizontal_m'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.imageSource = b4;
        this.imageNormalSource = b4;
        if (f4 !== undefined) {
            this.imageSelectedSource = f4;
        }
        else {
            this.imageSelectedSource = this.imageNormalSource;
        }
        if (g4 !== undefined) {
            this.imageEditSource = g4;
        }
        else {
            this.imageEditSource = this.imageNormalSource;
        }
        this.imageOpacity = c4;
        this.itemWidth = d4;
        this.itemHeight = e4;
        this.imageCollapseSource = b4;
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

    changeImageCollapseSource(a4) {
        if (a4 === NodeStatus.Expand) {
            this.imageCollapseSource = this.imageCollapseDownSource;
        }
        else if (a4 === NodeStatus.Collapse) {
            this.imageCollapseSource = this.imageCollapseRightSource;
        }
    }

    setImageCollapseSource(y3, z3) {
        if (y3 === InteractionStatus.Edit || y3 === InteractionStatus.DragInsert) {
            this.imageCollapseDownSource = ARROW_DOWN_WITHE;
            this.imageCollapseRightSource = ARROW_RIGHT_WITHE;
            this.isImageCollapse = false;
        }
        else if (y3 === InteractionStatus.FinishEdit ||
            y3 === InteractionStatus.FinishDragInsert) {
            this.imageCollapseDownSource = ARROW_DOWN;
            this.imageCollapseRightSource = ARROW_RIGHT;
            this.isImageCollapse = true;
        }
        this.imageCollapseSource = (z3 === NodeStatus.Collapse) ?
        this.imageCollapseRightSource : this.imageCollapseDownSource;
    }

    setImageSource(x3) {
        switch (x3) {
            case InteractionStatus.Normal:
                this.imageSource = this.imageNormalSource;
                this.currentInteractionStatus = x3;
                break;
            case InteractionStatus.Selected:
                if (this.currentInteractionStatus !== InteractionStatus.Edit) {
                    this.imageSource = this.imageSelectedSource;
                    this.currentInteractionStatus = x3;
                }
                break;
            case InteractionStatus.Edit:
                this.imageSource = this.imageEditSource;
                this.currentInteractionStatus = x3;
                break;
            case InteractionStatus.FinishEdit:
                this.imageSource = this.imageSelectedSource;
                this.currentInteractionStatus = x3;
                break;
            case InteractionStatus.DragInsert:
                this.imageSource = this.imageEditSource;
                this.currentInteractionStatus = x3;
                break;
            case InteractionStatus.FinishDragInsert:
                this.imageSource = this.imageNormalSource;
                this.currentInteractionStatus = x3;
                break;
            default:
                break;
        }
    }
}

class MainTitleNode extends NodeBaseInfo {
    constructor(w3) {
        super();
        this.treeViewTheme = new TreeViewTheme();
        this.mainTitleName = w3;
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

    setMainTitleSelected(v3) {
        if (v3) {
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

    set title(u3) {
        this.mainTitleName = u3;
    }

    get title() {
        return this.mainTitleName;
    }

    set popUpTimeout(t3) {
        this.showPopUpTimeout = t3;
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

    setMainTitleHighLight(s3) {
        if (s3) {
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

    traverseNodeDF(n3, o3 = this._root) {
        let p3 = [], q3 = false;
        p3.unshift(o3);
        let r3 = p3.shift();
        while (!q3 && r3) {
            q3 = n3(r3) === true;
            if (!q3) {
                p3.unshift(...r3.children);
                r3 = p3.shift();
            }
        }
    }

    traverseNodeBF(i3) {
        let j3 = [];
        let k3 = false;
        j3.push(this._root);
        let l3 = j3.shift();
        while (!k3 && l3) {
            try {
                k3 = i3(l3);
            }
            catch (m3) {
                throw new Error('traverseNodeBF function callbacks error.');
            }
            if (!k3) {
                j3.push(...l3.children);
                l3 = j3.shift();
            }
        }
    }

    contains(g3, h3) {
        h3(g3);
    }

    updateParentChildNum(a3, b3, c3) {
        let d3 = a3.parentNodeId;
        while (d3 >= 0) {
            this.traverseNodeDF((f3) => {
                if (f3.currentNodeId === d3) {
                    f3.getChildNodeInfo().allChildNum =
                        b3 ? f3.getChildNodeInfo().allChildNum + c3 : f3.getChildNodeInfo().allChildNum - c3;
                    d3 = f3.parentNodeId;
                    return false;
                }
                return false;
            });
        }
    }

    findParentNodeId(v2) {
        let w2 = new NodeItem(emptyNodeInfo);
        let x2 = (z2) => {
            if (z2.currentNodeId === v2) {
                w2 = z2;
                return true;
            }
            return false;
        };
        this.traverseNodeBF(x2);
        return w2.parentNodeId;
    }

    addNode(n2, o2, p2) {
        if (this._root === null) {
            this._root = new NodeItem(emptyNodeInfo);
            this._root.nodeLevel = -1;
            this._root.parentNodeId = -1;
            this._root.currentNodeId = -1;
        }
        let q2 = new NodeItem(emptyNodeInfo);
        let r2 = (u2) => {
            if (u2.currentNodeId === n2) {
                q2 = u2;
                return true;
            }
            return false;
        };
        this.traverseNodeBF(r2);
        if (q2) {
            let t2 = new NodeItem(p2);
            if (q2.nodeLevel > this.MaxNodeLevel) {
                throw new Error('ListNodeUtils[addNode]: The level of the tree view cannot exceed 50.');
            }
            t2.nodeLevel = q2.nodeLevel + 1;
            t2.parentNodeId = n2;
            t2.currentNodeId = o2;
            q2.children.push(t2);
            q2.getChildNodeInfo().isHasChildNode = true;
            q2.getChildNodeInfo().childNum = q2.children.length;
            q2.getChildNodeInfo().allChildNum += 1;
            q2.addImageCollapse(q2.getChildNodeInfo().isHasChildNode);
            this.updateParentChildNum(q2, true, 1);
            return this;
        }
        else {
            throw new Error('ListNodeUtils[addNode]: Parent node not found.');
        }
    }

    findNodeIndex(i2, j2) {
        let k2 = this.INITIAL_INVALID_VALUE;
        for (let l2 = 0, m2 = i2.length; l2 < m2; l2++) {
            if (i2[l2].currentNodeId === j2) {
                k2 = l2;
                break;
            }
        }
        return k2;
    }

    freeNodeMemory(a2, b2) {
        let c2 = [];
        let d2 = (h2) => {
            c2.push(h2);
            return false;
        };
        this.traverseNodeDF(d2, a2);
        c2.forEach((g2) => {
            b2.push(g2.currentNodeId);
            g2 = new NodeItem(emptyNodeInfo);
        });
    }

    removeNode(q1, r1) {
        let s1 = new NodeItem(emptyNodeInfo);
        let t1 = (z1) => {
            if (z1.currentNodeId === r1) {
                s1 = z1;
                return true;
            }
            return false;
        };
        this.traverseNodeBF(t1);
        if (s1) {
            let v1 = [];
            let w1 = this.findNodeIndex(s1.children, q1);
            let x1 = 0;
            if (w1 < 0) {
                throw new Error('Node does not exist.');
            }
            else {
                x1 = s1.children[w1].getChildNodeInfo().allChildNum + 1;
                this.freeNodeMemory(s1.children[w1], v1);
                let y1 = s1.children.splice(w1, 1);
                y1 = null;
                if (s1.children.length === 0) {
                    s1.addImageCollapse(false);
                }
            }
            s1.getChildNodeInfo().childNum = s1.children.length;
            s1.getChildNodeInfo().allChildNum -= (x1);
            this.updateParentChildNum(s1, false, x1);
            return v1;
        }
        else {
            throw new Error('Parent does not exist.');
        }
    }

    getNewNodeInfo(k1) {
        let l1 = new NodeItem(emptyNodeInfo);
        let m1 = (p1) => {
            if (p1.currentNodeId === k1) {
                l1 = p1;
                return true;
            }
            return false;
        };
        this.traverseNodeBF(m1);
        let n1 = emptyNodeInfo;
        if (l1) {
            if (l1.children.length === 0) {
                if (l1.getNodeItem().imageNode !== undefined) {
                    n1.icon = l1.getNodeItem().imageNode?.normalSource;
                    n1.selectedIcon = l1.getNodeItem().imageNode?.selectedSource;
                    n1.editIcon = l1.getNodeItem().imageNode?.editSource;
                    n1.container = l1.getMenu();
                }
                else {
                    n1.icon = undefined;
                    n1.selectedIcon = undefined;
                    n1.editIcon = undefined;
                    n1.container = l1.getMenu();
                }
            }
            else if (l1.children.length > 0) {
                if (l1.getNodeItem().imageNode !== null) {
                    n1.icon = (l1.children[0].getNodeItem().imageNode !== undefined) ?
                        l1.children[0].getNodeItem().imageNode?.normalSource : undefined;
                    n1.selectedIcon = (l1.children[0].getNodeItem().imageNode !== undefined) ?
                        l1.children[0].getNodeItem().imageNode?.selectedSource : undefined;
                    n1.editIcon = (l1.children[0].getNodeItem().imageNode !== undefined) ?
                        l1.children[0].getNodeItem().imageNode?.editSource : undefined;
                    n1.container = l1.children[0].getMenu();
                }
                else {
                    n1.icon = undefined;
                    n1.selectedIcon = undefined;
                    n1.editIcon = undefined;
                    n1.container = l1.children[0].getMenu();
                }
            }
        }
        return n1;
    }

    getClickChildId(b1) {
        let c1 = new NodeItem(emptyNodeInfo);
        let d1 = (j1) => {
            if (j1.currentNodeId === b1) {
                c1 = j1;
                return true;
            }
            return false;
        };
        this.traverseNodeBF(d1);
        if (c1) {
            if (c1.children.length === 0) {
                return [];
            }
            else if (c1.children.length > 0) {
                let f1 = { itemId: undefined, itemIcon: undefined, itemTitle: undefined };
                let g1 = new Array(c1.children.length);
                for (let i1 = 0; i1 < g1.length; i1++) {
                    g1[i1] = 0;
                }
                for (let h1 = 0; h1 < c1.children.length && h1 < g1.length; h1++) {
                    g1[h1] = c1.children[h1].currentNodeId;
                }
                return g1;
            }
        }
        return [];
    }

    getClickNodeChildrenInfo(t) {
        let u = new NodeItem(emptyNodeInfo);
        let v = (a1) => {
            if (a1.currentNodeId === t) {
                u = a1;
                return true;
            }
            return false;
        };
        this.traverseNodeBF(v);
        if (u) {
            if (u.children.length === 0) {
                return [];
            }
            else if (u.children.length > 0) {
                let x = new Array(u.children.length);
                for (let z = 0; z < x.length; z++) {
                    x[z] = {};
                }
                for (let y = 0; y < u.children.length && y < x.length; y++) {
                    x[y].itemId = u.children[y].currentNodeId;
                    if (u.children[y].getNodeItem().imageNode) {
                        x[y].itemIcon = u.children[y].getNodeItem().imageNode?.source;
                    }
                    if (u.children[y].getNodeItem().mainTitleNode) {
                        x[y].itemTitle = u.children[y].getNodeItem().mainTitleNode?.title;
                    }
                    x[y].isFolder = u.children[y].getIsFolder();
                }
                return x;
            }
        }
        return [];
    }

    checkMainTitleIsValid(s) {
        if (new RegExp("/[\\\/:*?'<>|]/").test(s)) {
            return false;
        }

    if ((new RegExp('/^[\u4e00-\u9fa5]+$/').test(s) && s.length > this.MAX_CN_LENGTH) ||
    (!new RegExp('/^[\u4e00-\u9fa5]+$/').test(s) && s.length > this.MAX_EN_LENGTH)) {
    return false;
}
return true;
}
dragTraverseNodeDF(m, n = this._root, o) {
    let p = [], q = false;
    p.unshift(n);
    let r = p.shift();
    while (!q && r) {
        q = m(r, o) === true;
        if (!q) {
            p.unshift(...r.children);
            r = p.shift();
        }
    }
}
addDragNode(a, b, c, d, e) {
    if (this._root === null) {
        this._root = new NodeItem(emptyNodeInfo);
        this._root.nodeLevel = this.INITIAL_INVALID_VALUE;
        this._root.parentNodeId = this.INITIAL_INVALID_VALUE;
        this._root.currentNodeId = this.INITIAL_INVALID_VALUE;
    }
    let f = new NodeItem(emptyNodeInfo);
    let g = (l) => {
        if (l.currentNodeId === a) {
            f = l;
            return true;
        }
        return false;
    };
    this.traverseNodeBF(g);
    if (f) {
        let i = new NodeItem(e);
        if (f.nodeLevel > this.MaxNodeLevel) {
            throw new Error('ListNodeUtils[addNode]: The level of the tree view cannot exceed 50.');
        }
        i.nodeLevel = f.nodeLevel + 1;
        i.parentNodeId = a;
        i.currentNodeId = b;
        let j = this.INITIAL_INVALID_VALUE;
        if (f.children.length) {
            for (let k = 0; k < f.children.length; k++) {
                if (f.children[k].getCurrentNodeId() === c) {
                    j = k;
                    break;
                }
            }
            if (d) {
                f.children.splice(j + 1, 0, i);
            }
            else {
                f.children.splice(j, 0, i);
            }
        }
        else {
            f.children.push(i);
        }
        f.getChildNodeInfo().isHasChildNode = true;
        f.getChildNodeInfo().childNum = f.children.length;
        f.getChildNodeInfo().allChildNum += 1;
        f.addImageCollapse(f.getChildNodeInfo().isHasChildNode);
        this.updateParentChildNum(f, true, 1);
        return this;
    }
    else {
        throw new Error('ListNodeUtils[addNode]: Parent node not found.');
    }
}
}

export default {
    TreeController,
    TreeListener,
    TreeListenerManager,
    TreeListenType,
    TreeView,
}