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

var t5 = (this && this.t5) || function (u21, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === 'object' && typeof Reflect.w21 === 'function')
        r = Reflect.w21(u21, target, key, desc);
    else
        for (var v21 = u21.length - 1; v21 >= 0; v21--)
            if (d = u21[v21])
                r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => { });
}

const hilog = requireNapi('hilog');
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const resourceManager = requireNapi('resourceManager');
const accessibility = requireNapi('accessibility');
const BusinessError = requireNapi('BusinessError');

const u5 = 24;
const v5 = 24;
const w5 = 0;
const x5 = 48;
const y5 = 32;
const z5 = 2;
const a6 = 0;
const b6 = 48;
const c6 = 0;
const d6 = 48;
const e6 = 10;
const f6 = 2;
const g6 = 0.4;
const h6 = 1;
const i6 = 1;
const j6 = 2;
const k6 = '1.0vp';
const l6 = '0vp';
const m6 = '2.75vp';
const n6 = '-1.25vp';
const o6 = '1.5vp';
const p6 = '#FFFFFF';
const q6 = '#00000000';
const r6 = '#1A0A59F7';
const s6 = '#00001E';
const t6 = '48';
const u6 = '128vp';
const v6 = '208vp';
const w6 = '80vp';
const x6 = '160vp';
const y6 = '112vp';
const z6 = '192vp';
const a7 = '#00FFFFFF';
const b7 = 100;
const c7 = 12;
const d7 = 8;
const e7 = 'TreeView';
const f7 = 0x3900;
const g7 = 2000;
const h7 = 300;
const a1 = 40000;
const i7 = 1.3;
const j7 = 1;
const ARROW_DOWN = { 'id': -1, 'type': 40000, params: ['sys.symbol.chevron_down'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const k7 = { 'id': -1, 'type': 40000, params: ['sys.symbol.chevron_down'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const ARROW_RIGHT = { 'id': -1, 'type': 40000, params: ['sys.symbol.chevron_right'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const l7 = { 'id': -1, 'type': 40000, params: ['sys.symbol.chevron_right'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
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
var m7;
(function (t21) {
    t21[t21['ADD_NODE'] = 0] = 'ADD_NODE';
    t21[t21['REMOVE_NODE'] = 1] = 'REMOVE_NODE';
    t21[t21['MODIFY_NODE'] = 2] = 'MODIFY_NODE';
    t21[t21['COMMIT_NODE'] = 3] = 'COMMIT_NODE';
})(m7 || (m7 = {}));
var n7;
(function (s21) {
    s21[s21['HINTS'] = 0] = 'HINTS';
    s21[s21['WARNINGS'] = 1] = 'WARNINGS';
})(n7 || (n7 = {}));
var o7;
(function (r21) {
    r21[r21['INVALID_ERROR'] = 0] = 'INVALID_ERROR';
    r21[r21['LENGTH_ERROR'] = 1] = 'LENGTH_ERROR';
    r21[r21['NONE'] = 2] = 'NONE';
})(o7 || (o7 = {}));
var p7;
(function (q21) {
    q21[q21['DOWN_FLAG'] = 0] = 'DOWN_FLAG';
    q21[q21['UP_FLAG'] = 1] = 'UP_FLAG';
    q21[q21['NONE'] = 2] = 'NONE';
})(p7 || (p7 = {}));
export var q7;
(function (p21) {
    p21[p21['EXPAND'] = 0] = 'EXPAND';
    p21[p21['COLLAPSE'] = 1] = 'COLLAPSE';
})(q7 || (q7 = {}));
export var r7;
(function (o21) {
    o21[o21['NORMAL'] = 0] = 'NORMAL';
    o21[o21['SELECTED'] = 1] = 'SELECTED';
    o21[o21['EDIT'] = 2] = 'EDIT';
    o21[o21['FINISH_EDIT'] = 3] = 'FINISH_EDIT';
    o21[o21['DRAG_INSERT'] = 4] = 'DRAG_INSERT';
    o21[o21['FINISH_DRAG_INSERT'] = 5] = 'FINISH_DRAG_INSERT';
})(r7 || (r7 = {}));
var s7;
(function (n21) {
    n21[n21['ARROW_DOWN'] = 0] = 'ARROW_DOWN';
    n21[n21['ARROW_RIGHT'] = 1] = 'ARROW_RIGHT';
    n21[n21['ARROW_DOWN_WHITE'] = 2] = 'ARROW_DOWN_WHITE';
    n21[n21['ARROW_RIGHT_WHITE'] = 3] = 'ARROW_RIGHT_WHITE';
})(s7 || (s7 = {}));
var t7;
(function (m21) {
    m21[m21['TEXT'] = 0] = 'TEXT';
    m21[m21['PLACE'] = 1] = 'PLACE';
    m21[m21['LIFT'] = 2] = 'LIFT';
})(t7 || (t7 = {}));
class Util {
    static f1(p1) {
        if (!Util.g1(p1)) {
            return false;
        }
        let resource = p1;
        return resource.type === a1;
    }
    static g1(resource) {
        if (!resource) {
            return false;
        }
        if (typeof resource === 'string' || typeof resource === 'undefined') {
            return false;
        }
        return true;
    }
}
class u7 {
    constructor() {
    }
    static getInstance() {
        if (!u7.instance) {
            u7.instance = new u7();
        }
        return u7.instance;
    }
    createNode() {
        return {
            x21: undefined,
            inputText: new i8(),
            y21: new h8(''),
            z21: undefined,
            fontColor: undefined,
        };
    }
    a22(nodeParam) {
        let l21 = this.createNode();
        if (nodeParam.icon) {
            l21.x21 = new g8(nodeParam.icon, nodeParam.symbolIconStyle, { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_alpha_content_fourth'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, u5, v5, nodeParam.selectedIcon, nodeParam.symbolSelectedIconStyle, nodeParam.editIcon, nodeParam.symbolEditIconStyle);
        }
        if (nodeParam.primaryTitle) {
            l21.y21 = new h8(nodeParam.primaryTitle);
        }
        return l21;
    }
}
let v7 = {
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
class w7 {
    constructor() {
        this.b22 = '#1A0A59F7';
        this.c22 = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.d22 = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.e22 = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary_activated'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.f22 = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_click_effect'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.g22 = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_hover'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.h22 = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_focused_outline'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.i22 = { 'id': -1, 'type': 10001, params: ['sys.color.icon_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.j22 = { 'id': -1, 'type': 10001, params: ['sys.color.icon_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.k22 = { 'id': -1, 'type': 10001, params: ['sys.color.icon_tertiary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    }
    static getInstance() {
        if (!w7.instance) {
            w7.instance = new w7();
        }
        return w7.instance;
    }
}
let x7 = class NodeInfo {
    constructor(node, nodeParam) {
        this.imageSource = '';
        this.l22 = undefined;
        this.borderWidth = { has: z5, n22: a6 };
        this.o22 = false;
        this.p22 = false;
        this.q22 = false;
        this.r22 = false;
        this.s22 = false;
        this.treeViewTheme = w7.getInstance();
        this.fontColor = '';
        this.node = node;
        this.nodeParam = nodeParam;
        this.t22 = u7.getInstance().a22(nodeParam);
        this.u22 = {
            v22: false,
            w22: false,
            x22: undefined,
            y22: '',
            z22: undefined,
        };
        this.a23 = b6;
        this.b23 = node.c23 * c7 + d7;
        this.d23 = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.e23 = (this.node.c23 > 0) ? false : true;
        this.f23 = (this.node.c23 > 0) ? c6 : d6;
        this.g23 = true;
        this.h23 = false;
        this.isSelected = false;
        this.status = {
            normal: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            i23: this.treeViewTheme.g22,
            j23: this.treeViewTheme.f22,
            selected: this.treeViewTheme.b22,
            k23: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_activated'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }
        };
        this.l23 = {
            borderWidth: a6,
            borderColor: this.treeViewTheme.h22,
            borderRadius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }
        };
        this.n23 = node.c23 * c7 + d7;
    }
    o23(k21) {
        if (k21) {
            this.t22.z21 =
                f8.p23(s7.ARROW_RIGHT);
        }
        else {
            this.t22.z21 = undefined;
        }
    }
    q23(color) {
        this.fontColor = color;
    }
    r23() {
        return this.fontColor;
    }
    s23() {
        return this.u22;
    }
    t23(isShow) {
        this.u22.v22 = isShow;
    }
    u23(j21) {
        this.u22.w22 = j21;
    }
    v23(color) {
        this.u22.x22 = color;
    }
    w23(text) {
        this.u22.y22 = text;
    }
    x23(i21) {
        this.u22.z22 = i21;
    }
    y23() {
        return this.g23;
    }
    z23() {
        return this.h23;
    }
    a24(h21) {
        if (h21) {
            this.g23 = false;
            this.h23 = true;
        }
        else {
            this.g23 = true;
            this.h23 = false;
        }
    }
    b24(g21) {
        if (g21) {
            this.t22.z21 =
                f8.p23(s7.ARROW_DOWN);
        }
        else {
            this.t22.z21 = undefined;
        }
    }
    c24(f21) {
        if (f21 === undefined) {
            return;
        }
        this.d23 = f21;
    }
    d24() {
        return this.d23;
    }
    e24(e21) {
        this.f23 = e21;
    }
    f24() {
        return this.f23;
    }
    g24() {
        return this.node.currentNodeId;
    }
    h24() {
        return this.node.parentNodeId;
    }
    i24() {
        return this.b23;
    }
    j24() {
        return this.a23;
    }
    k24(d21) {
        this.e23 = d21;
    }
    l24() {
        return this.e23;
    }
    n24() {
        return this.t22;
    }
    o24() {
        return this.status;
    }
    p24() {
        return this.l23;
    }
    q24(c21) {
        this.l23.borderWidth = c21 ? this.borderWidth.has : this.borderWidth.n22;
    }
    r24() {
        return this.node.s24;
    }
    t24() {
        return this.nodeParam.container;
    }
    u24(isSelected) {
        this.isSelected = isSelected;
    }
    v24() {
        return this.isSelected;
    }
    w24() {
        return this.nodeParam;
    }
    x24() {
        return this.node;
    }
    y24() {
        return this.nodeParam.isFolder;
    }
    z24(b21) {
        this.o22 = b21;
    }
    a25() {
        return this.o22;
    }
    b25(a21) {
        if (a21 === undefined) {
            return;
        }
        this.n23 = a21 * c7 + d7;
    }
    c25() {
        return this.n23;
    }
    d25() {
        return this.node.c23;
    }
    e25(z20) {
        this.p22 = z20;
    }
    f25() {
        return this.p22;
    }
    g25(y20) {
        this.q22 = y20;
    }
    h25() {
        return this.q22;
    }
    i25(x20) {
        this.r22 = x20;
    }
    j25() {
        return this.r22;
    }
    k25(w20) {
        this.s22 = w20;
    }
    l25() {
        return this.s22;
    }
};
x7 = t5([
    Observed
], x7);
export { x7 };
export var TreeListenType;
(function (TreeListenType) {
    TreeListenType['NODE_CLICK'] = 'NodeClick';
    TreeListenType['NODE_ADD'] = 'NodeAdd';
    TreeListenType['NODE_DELETE'] = 'NodeDelete';
    TreeListenType['NODE_MODIFY'] = 'NodeModify';
    TreeListenType['NODE_MOVE'] = 'NodeMove';
})(TreeListenType || (TreeListenType = {}));
export class TreeListener {
    constructor() {
        this.m25 = [];
        this.n25 = [];
    }
    on(type, callback) {
        if (Array.isArray(type)) {
            for (let v20 = 0, l = type.length; v20 < l; v20++) {
                this.on(type[v20], callback);
            }
        }
        else {
            (this.m25[type] || (this.m25[type] = [])).push(callback);
        }
    }
    once(type, callback) {
        if (Array.isArray(type)) {
            this.off(type, callback);
        }
        else {
            (this.n25[type] || (this.n25[type] = [])).push(callback);
        }
    }
    off(type, callback) {
        if (type === null) {
            this.m25 = [];
        }
        if (Array.isArray(type)) {
            for (let u20 = 0, l = type.length; u20 < l; u20++) {
                this.off(type[u20], callback);
            }
        }
        let r20 = this.m25[type];
        if (!r20) {
            return;
        }
        if (callback === null) {
            this.m25[type] = null;
        }
        let s20 = r20.length;
        while (s20--) {
            let t20 = r20[s20];
            if (t20 === callback) {
                r20.splice(s20, 1);
                break;
            }
        }
    }
    emit(event, m20) {
        if (this.n25[event]) {
            let p20 = Array.from(this.n25[event]);
            if (p20) {
                for (let q20 = 0, l = p20.length; q20 < l; q20++) {
                    try {
                        p20[q20](m20);
                    }
                    catch (e) {
                        throw new Error('once function callbacks error.');
                    }
                }
                this.n25[event] = null;
            }
        }
        else if (this.m25[event]) {
            let n20 = Array.from(this.m25[event]);
            if (n20) {
                for (let o20 = 0, l = n20.length; o20 < l; o20++) {
                    try {
                        n20[o20](m20);
                    }
                    catch (e) {
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
TreeListenerManager.o25 = 'app_key_event_bus';
export class TreeView extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.treeController = new TreeController();
        this.__nodeList = new ObservedPropertyObjectPU([], this, 'nodeList');
        this.listNodeDataSource = new z7();
        this.__item = new ObservedPropertyObjectPU(null, this, 'item');
        this.__touchCount = new ObservedPropertySimplePU(0, this, 'touchCount');
        this.__dropSelectedIndex = new ObservedPropertySimplePU(0, this, 'dropSelectedIndex');
        this.__viewLastIndex = new ObservedPropertySimplePU(-1, this, 'viewLastIndex');
        this.__followingSystemFontScale = new ObservedPropertySimplePU(false, this, 'followingSystemFontScale');
        this.__maxAppFontScale = new ObservedPropertySimplePU(1, this, 'maxAppFontScale');
        this.__listItemBgColor = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'listItemBgColor');
        this.__allParentNode = new ObservedPropertyObjectPU([], this, 'allParentNode');
        this.__treeViewTheme = new ObservedPropertyObjectPU(w7.getInstance(), this, 'treeViewTheme');
        this.addProvidedVar('treeViewTheme', this.__treeViewTheme, false);
        this.__clickButtonFlag = new ObservedPropertySimplePU(true, this, 'clickButtonFlag');
        this.addProvidedVar('clickButtonFlag', this.__clickButtonFlag, false);
        this.__accessibilityNodeType = new ObservedPropertySimplePU(t7.TEXT, this, 'accessibilityNodeType');
        this.addProvidedVar('accessibilityNodeType', this.__accessibilityNodeType, false);
        this.__isAccessibilityEnabled = new ObservedPropertySimplePU(false, this, 'isAccessibilityEnabled');
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
            left: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_card_margin_start'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_card_margin_end'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            top: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_margin_vertical'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            bottom: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_margin_vertical'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        };
        this.textInputPadding = {
            left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        };
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(params) {
        if (params.treeController !== undefined) {
            this.treeController = params.treeController;
        }
        if (params.nodeList !== undefined) {
            this.nodeList = params.nodeList;
        }
        if (params.listNodeDataSource !== undefined) {
            this.listNodeDataSource = params.listNodeDataSource;
        }
        if (params.item !== undefined) {
            this.item = params.item;
        }
        if (params.touchCount !== undefined) {
            this.touchCount = params.touchCount;
        }
        if (params.dropSelectedIndex !== undefined) {
            this.dropSelectedIndex = params.dropSelectedIndex;
        }
        if (params.viewLastIndex !== undefined) {
            this.viewLastIndex = params.viewLastIndex;
        }
        if (params.followingSystemFontScale !== undefined) {
            this.followingSystemFontScale = params.followingSystemFontScale;
        }
        if (params.maxAppFontScale !== undefined) {
            this.maxAppFontScale = params.maxAppFontScale;
        }
        if (params.listItemBgColor !== undefined) {
            this.listItemBgColor = params.listItemBgColor;
        }
        if (params.allParentNode !== undefined) {
            this.allParentNode = params.allParentNode;
        }
        if (params.treeViewTheme !== undefined) {
            this.treeViewTheme = params.treeViewTheme;
        }
        if (params.clickButtonFlag !== undefined) {
            this.clickButtonFlag = params.clickButtonFlag;
        }
        if (params.accessibilityNodeType !== undefined) {
            this.accessibilityNodeType = params.accessibilityNodeType;
        }
        if (params.isAccessibilityEnabled !== undefined) {
            this.isAccessibilityEnabled = params.isAccessibilityEnabled;
        }
        if (params.listTreeViewMenu !== undefined) {
            this.listTreeViewMenu = params.listTreeViewMenu;
        }
        if (params.MAX_CN_LENGTH !== undefined) {
            this.MAX_CN_LENGTH = params.MAX_CN_LENGTH;
        }
        if (params.MAX_EN_LENGTH !== undefined) {
            this.MAX_EN_LENGTH = params.MAX_EN_LENGTH;
        }
        if (params.INITIAL_INVALID_VALUE !== undefined) {
            this.INITIAL_INVALID_VALUE = params.INITIAL_INVALID_VALUE;
        }
        if (params.MAX_TOUCH_DOWN_COUNT !== undefined) {
            this.MAX_TOUCH_DOWN_COUNT = params.MAX_TOUCH_DOWN_COUNT;
        }
        if (params.isMultiPress !== undefined) {
            this.isMultiPress = params.isMultiPress;
        }
        if (params.touchDownCount !== undefined) {
            this.touchDownCount = params.touchDownCount;
        }
        if (params.appEventBus !== undefined) {
            this.appEventBus = params.appEventBus;
        }
        if (params.itemPadding !== undefined) {
            this.itemPadding = params.itemPadding;
        }
        if (params.textInputPadding !== undefined) {
            this.textInputPadding = params.textInputPadding;
        }
    }
    updateStateVars(params) {
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__nodeList.purgeDependencyOnElmtId(rmElmtId);
        this.__item.purgeDependencyOnElmtId(rmElmtId);
        this.__touchCount.purgeDependencyOnElmtId(rmElmtId);
        this.__dropSelectedIndex.purgeDependencyOnElmtId(rmElmtId);
        this.__viewLastIndex.purgeDependencyOnElmtId(rmElmtId);
        this.__followingSystemFontScale.purgeDependencyOnElmtId(rmElmtId);
        this.__maxAppFontScale.purgeDependencyOnElmtId(rmElmtId);
        this.__listItemBgColor.purgeDependencyOnElmtId(rmElmtId);
        this.__allParentNode.purgeDependencyOnElmtId(rmElmtId);
        this.__treeViewTheme.purgeDependencyOnElmtId(rmElmtId);
        this.__clickButtonFlag.purgeDependencyOnElmtId(rmElmtId);
        this.__accessibilityNodeType.purgeDependencyOnElmtId(rmElmtId);
        this.__isAccessibilityEnabled.purgeDependencyOnElmtId(rmElmtId);
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
    set nodeList(newValue) {
        this.__nodeList.set(newValue);
    }
    get item() {
        return this.__item.get();
    }
    set item(newValue) {
        this.__item.set(newValue);
    }
    get touchCount() {
        return this.__touchCount.get();
    }
    set touchCount(newValue) {
        this.__touchCount.set(newValue);
    }
    get dropSelectedIndex() {
        return this.__dropSelectedIndex.get();
    }
    set dropSelectedIndex(newValue) {
        this.__dropSelectedIndex.set(newValue);
    }
    get viewLastIndex() {
        return this.__viewLastIndex.get();
    }
    set viewLastIndex(newValue) {
        this.__viewLastIndex.set(newValue);
    }
    get followingSystemFontScale() {
        return this.__followingSystemFontScale.get();
    }
    set followingSystemFontScale(newValue) {
        this.__followingSystemFontScale.set(newValue);
    }
    get maxAppFontScale() {
        return this.__maxAppFontScale.get();
    }
    set maxAppFontScale(newValue) {
        this.__maxAppFontScale.set(newValue);
    }
    get listItemBgColor() {
        return this.__listItemBgColor.get();
    }
    set listItemBgColor(newValue) {
        this.__listItemBgColor.set(newValue);
    }
    get allParentNode() {
        return this.__allParentNode.get();
    }
    set allParentNode(newValue) {
        this.__allParentNode.set(newValue);
    }
    get treeViewTheme() {
        return this.__treeViewTheme.get();
    }
    set treeViewTheme(newValue) {
        this.__treeViewTheme.set(newValue);
    }
    get clickButtonFlag() {
        return this.__clickButtonFlag.get();
    }
    set clickButtonFlag(newValue) {
        this.__clickButtonFlag.set(newValue);
    }
    get accessibilityNodeType() {
        return this.__accessibilityNodeType.get();
    }
    set accessibilityNodeType(newValue) {
        this.__accessibilityNodeType.set(newValue);
    }
    get isAccessibilityEnabled() {
        return this.__isAccessibilityEnabled.get();
    }
    set isAccessibilityEnabled(newValue) {
        this.__isAccessibilityEnabled.set(newValue);
    }
    NullBuilder(parent = null) {
    }
    onWillApplyTheme(theme) {
        this.treeViewTheme.b22 = theme.colors.interactiveSelect;
        this.treeViewTheme.f22 = theme.colors.interactivePressed;
        this.treeViewTheme.g22 = theme.colors.interactiveHover;
        this.treeViewTheme.c22 = theme.colors.fontPrimary;
        this.treeViewTheme.d22 = theme.colors.fontSecondary;
        this.treeViewTheme.e22 = theme.colors.interactiveActive;
        this.treeViewTheme.h22 = theme.colors.interactiveFocus;
        this.treeViewTheme.i22 = theme.colors.iconSecondary;
        this.treeViewTheme.j22 = theme.colors.interactiveActive;
        this.treeViewTheme.k22 = theme.colors.iconPrimary;
        this.treeController.treeViewTheme = this.treeViewTheme;
    }
    aboutToAppear() {
        if (this.treeController !== null) {
            this.listNodeDataSource = this.treeController.p25();
            this.nodeList = this.treeController.p25().q25;
            this.item = this.treeController.p25().q25;
        }
        let l20 = this.getUIContext();
        this.followingSystemFontScale = l20.isFollowingSystemFontScale();
        this.maxAppFontScale = l20.getMaxFontScale();
        accessibility.on('accessibilityStateChange', (state) => {
            this.isAccessibilityEnabled = state;
        });
    }
    decideFontScale() {
        let j20 = this.getUIContext();
        let k20 = j20.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.followingSystemFontScale) {
            return 1;
        }
        return Math.min(k20, this.maxAppFontScale, j6);
    }
    decideSymbolFontScale(f20) {
        if (!f20 || !this.followingSystemFontScale) {
            return 1;
        }
        let g20 = this.getUIContext();
        let h20 = g20.getHostContext()?.config?.fontSizeScale ?? 1;
        let i20 = Math.min(h20, this.maxAppFontScale, i7);
        return Math.max(i20, j7);
    }
    popupForShowTitle(text, backgroundColor, fontColor, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.backgroundColor(backgroundColor);
            Row.border({ radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_elements_margin_horizontal_l'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
            Row.padding({
                left: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_elements_margin_horizontal_l'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_elements_margin_horizontal_l'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                top: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_card_margin_middle'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                bottom: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_card_margin_middle'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(text);
            Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Text.fontWeight('regular');
            Text.fontColor(fontColor);
            Text.minFontScale(i6);
            Text.maxFontScale(this.decideFontScale());
        }, Text);
        Text.pop();
        Row.pop();
    }
    builder(parent = null) {
        this.listTreeViewMenu.bind(this)();
    }
    draggingPopup(item, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.id(`treeView_node_lift${item.g24()}`);
            Row.constraintSize({
                minWidth: this.listNodeDataSource.r25().s25.minWidth,
                maxWidth: this.listNodeDataSource.r25().s25.maxWidth,
            });
            Row.height(this.listNodeDataSource.r25().height);
            Row.backgroundColor(this.listNodeDataSource.r25().backgroundColor);
            Row.padding({
                start: LengthMetrics.resource(this.listNodeDataSource.r25().padding.left),
                end: LengthMetrics.resource(this.listNodeDataSource.r25().padding.right),
            });
            Row.shadow({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                color: s6,
                offsetY: 0,
            });
            Row.borderRadius(this.listNodeDataSource.r25().borderRadius);
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (item.n24().x21) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.backgroundColor(q6);
                        Row.margin({ end: s5(item.n24().x21?.t25) });
                        Row.height(item.n24().x21?.itemHeight * this.decideSymbolFontScale(item.n24().x21?.u25 !== undefined ||
                            Util.f1(item.n24().x21?.v25)));
                        Row.width(item.n24().x21?.itemWidth * this.decideSymbolFontScale(item.n24().x21?.u25 !== undefined ||
                            Util.f1(item.n24().x21?.v25)));
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (item.n24().x21?.u25) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.attributeModifier.bind(this)(item.n24().x21?.u25);
                                    SymbolGlyph.fontSize(`${item.n24().x21?.itemHeight * this.decideSymbolFontScale(true)}vp`);
                                    SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                    SymbolGlyph.opacity(this.listNodeDataSource.r25().w25);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    If.create();
                                    if (Util.f1(item.n24().x21?.v25)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                SymbolGlyph.create(item.n24().x21?.v25);
                                                SymbolGlyph.fontSize(`${item.n24().x21?.itemHeight * this.decideSymbolFontScale(true)}vp`);
                                                SymbolGlyph.opacity(this.listNodeDataSource.r25().w25);
                                            }, SymbolGlyph);
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                Image.create(item.n24().x21?.v25);
                                                Image.objectFit(ImageFit.Contain);
                                                Image.height(item.n24().x21?.itemHeight);
                                                Image.width(item.n24().x21?.itemWidth);
                                                Image.opacity(this.listNodeDataSource.r25().w25);
                                                Image.matchTextDirection((item.n24().z21?.x25 === ARROW_RIGHT ||
                                                    item.n24().z21?.x25 === l7) ? true : false);
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
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.constraintSize({
                minWidth: item.n24().x21 ?
                    this.listNodeDataSource.r25().y25.z25 :
                    this.listNodeDataSource.r25().y25.a26,
                maxWidth: item.n24().x21 ?
                    this.listNodeDataSource.r25().y25.b26 :
                    this.listNodeDataSource.r25().y25.c26,
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (item.n24().y21 && item.y23()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(item.n24().y21?.title);
                        Text.maxLines(1);
                        Text.minFontScale(i6);
                        Text.maxFontScale(this.decideFontScale());
                        Text.fontSize(item.n24().y21?.size);
                        Text.fontColor(this.listNodeDataSource.r25().fontColor);
                        Text.fontWeight(this.listNodeDataSource.r25().fontWeight);
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
        this.setImageSources(this.viewLastIndex, r7.NORMAL);
        this.listNodeDataSource.d26(this.viewLastIndex, r7.NORMAL);
        this.nodeList[this.viewLastIndex].c24({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
        this.nodeList[this.viewLastIndex].fontColor = this.treeViewTheme.c22;
        this.listNodeDataSource.q25[this.viewLastIndex].c24({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
        this.listNodeDataSource.q25[this.viewLastIndex].fontColor = this.treeViewTheme.c22;
        this.listNodeDataSource.q25[this.viewLastIndex].u24(false);
        this.listNodeDataSource.q25[this.viewLastIndex].imageSource =
            this.listNodeDataSource.q25[this.viewLastIndex].n24().x21?.source;
        this.listNodeDataSource.q25[this.viewLastIndex].l22 =
            this.listNodeDataSource.q25[this.viewLastIndex].n24().x21?.l22;
    }
    setImageSources(index, d20) {
        let e20 = this.nodeList[index];
        e20.u24(d20 === r7.SELECTED ||
            d20 === r7.EDIT || d20 === r7.FINISH_EDIT);
        if (e20.n24().y21 !== null && d20 !== r7.DRAG_INSERT &&
            d20 !== r7.FINISH_DRAG_INSERT) {
            e20.n24().y21?.e26(d20 === r7.SELECTED ||
                d20 === r7.FINISH_EDIT);
        }
        if (e20.n24().x21 !== null) {
            e20.n24().x21?.d26(d20);
        }
    }
    touchInner(c20, event) {
        this.viewLastIndex = this.listNodeDataSource.f26();
        let index = this.listNodeDataSource.findIndex(c20.g24());
        if (event.type === TouchType.Down) {
            if (index !== this.viewLastIndex) {
                this.clearLastIndexColor();
                this.listNodeDataSource.lastIndex = index;
                this.listNodeDataSource.g26(index);
            }
        }
        if (event.type === TouchType.Up) {
            this.listNodeDataSource.q25[index].u24(true);
            this.listNodeDataSource.d26(index, r7.SELECTED);
            if (this.listNodeDataSource.q25[index].n24().x21 !== null) {
                this.listNodeDataSource.q25[index].imageSource = this.listNodeDataSource.q25[index].n24().x21?.source;
                this.listNodeDataSource.q25[index].l22 = this.listNodeDataSource.q25[index].n24().x21?.l22;
            }
            if (index !== this.viewLastIndex) {
                this.clearLastIndexColor();
                this.listNodeDataSource.lastIndex = index;
                this.listNodeDataSource.g26(index);
            }
            this.viewLastIndex = index;
        }
        if (this.listNodeDataSource.f26() !== -1 && index !== this.listNodeDataSource.f26()) {
            this.listNodeDataSource.h26(n7.WARNINGS, o7.NONE, false, this.listNodeDataSource.f26());
            this.listNodeDataSource.i26(this.listNodeDataSource.f26(), m7.COMMIT_NODE);
        }
    }
    clickInner(b20) {
        this.viewLastIndex = this.listNodeDataSource.f26();
        let index = this.listNodeDataSource.findIndex(b20.g24());
        if (index !== this.viewLastIndex) {
            this.clearLastIndexColor();
            this.listNodeDataSource.lastIndex = index;
            this.listNodeDataSource.g26(index);
        }
        this.listNodeDataSource.q25[index].u24(true);
        this.listNodeDataSource.d26(index, r7.SELECTED);
        if (this.listNodeDataSource.q25[index].n24().x21 !== null) {
            this.listNodeDataSource.q25[index].imageSource = this.listNodeDataSource.q25[index].n24().x21?.source;
            this.listNodeDataSource.q25[index].l22 = this.listNodeDataSource.q25[index].n24().x21?.l22;
        }
        if (index !== this.viewLastIndex) {
            this.clearLastIndexColor();
            this.listNodeDataSource.lastIndex = index;
            this.listNodeDataSource.g26(index);
        }
        this.viewLastIndex = index;
        if (this.listNodeDataSource.f26() !== -1 && index !== this.listNodeDataSource.f26()) {
            this.listNodeDataSource.h26(n7.WARNINGS, o7.NONE, false, this.listNodeDataSource.f26());
            this.listNodeDataSource.i26(this.listNodeDataSource.f26(), m7.COMMIT_NODE);
        }
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            List.create({});
            List.onDragMove((event, extraParams) => {
                if (this.isMultiPress) {
                    hilog.error(f7, e7, 'drag error, a item has been dragged');
                    return;
                }
                let x19 = d6;
                let flag = Math.floor(event.getY() /
                    (x19 / f6)) % f6 ? p7.DOWN_FLAG : p7.UP_FLAG;
                let index = JSON.parse(extraParams).insertIndex;
                let y19 = false;
                if (index >= this.listNodeDataSource.totalCount()) {
                    flag = p7.DOWN_FLAG;
                    index = this.listNodeDataSource.totalCount() - 1;
                    this.listNodeDataSource.getData(index)?.e25(true);
                    y19 = true;
                }
                else {
                    this.listNodeDataSource.getData(index)?.e25(false);
                }
                let z19 = this.listNodeDataSource.getData(index);
                let currentNodeId = z19?.g24();
                if (index !== this.listNodeDataSource.j26() && this.listNodeDataSource.k26()) {
                    let a20 = this.listNodeDataSource.l26(currentNodeId);
                    if (a20) {
                        this.listNodeDataSource.m26(index);
                        if (currentNodeId !== undefined) {
                            this.listNodeDataSource.n26(this.listNodeDataSource.findIndex(currentNodeId));
                        }
                        this.listNodeDataSource.o26(p7.NONE);
                        return;
                    }
                }
                this.listNodeDataSource.p26(index);
                this.listNodeDataSource.q26(flag, index - 1, y19, ObservedObject.GetRawObject(this.allParentNode));
                if (currentNodeId !== undefined && currentNodeId !== this.listNodeDataSource.r26()) {
                    this.listNodeDataSource.s26(this.listNodeDataSource.findIndex(currentNodeId), currentNodeId, index);
                }
            });
            List.onDragEnter((event, extraParams) => {
                if (this.listNodeDataSource.k26()) {
                    this.listNodeDataSource.t26(true);
                    let w19 = g6;
                    this.listNodeDataSource.u26(w19);
                }
            });
            List.onDragLeave((event, extraParams) => {
                this.listNodeDataSource.v26();
                this.listNodeDataSource.w26();
                this.listNodeDataSource.x26();
                let v19 = h6;
                this.listNodeDataSource.u26(v19);
                this.listNodeDataSource.t26(false);
                this.listNodeDataSource.y26();
            });
            List.onDrop((event, extraParams) => {
                this.accessibilityNodeType = t7.PLACE;
                this.listNodeDataSource.x26();
                let i19 = h6;
                this.listNodeDataSource.u26(i19);
                let j19 = JSON.parse(extraParams).insertIndex;
                let k19 = this.dropSelectedIndex;
                if (k19 - 1 > this.listNodeDataSource.totalCount() || k19 === undefined) {
                    hilog.error(f7, e7, 'drag error, currentNodeIndex is not found');
                    this.listNodeDataSource.t26(false);
                    return;
                }
                if (j19 === this.listNodeDataSource.totalCount()) {
                    hilog.info(f7, e7, 'need to insert into the position of the last line');
                    j19 -= 1;
                }
                let l19 = this.listNodeDataSource.getData(j19);
                if (l19 === undefined) {
                    return;
                }
                let m19 = l19.g24();
                if (!this.listNodeDataSource.z26() || !this.listNodeDataSource.k26()) {
                    this.listNodeDataSource.w26();
                    this.listNodeDataSource.a27(false);
                    this.listNodeDataSource.v26();
                    this.listNodeDataSource.b27();
                    this.listNodeDataSource.c27(m19);
                    this.listNodeDataSource.y26();
                    return;
                }
                let n19 = this.listNodeDataSource.d27();
                let o19 = l19.h24();
                let p19 = this.listNodeDataSource.r26();
                let q19 = this.listNodeDataSource.e27();
                let r19 = this.listNodeDataSource.l26(m19);
                if (r19) {
                    this.listNodeDataSource.w26();
                    this.listNodeDataSource.a27(false);
                    this.listNodeDataSource.v26();
                    this.listNodeDataSource.f27(j19);
                    this.listNodeDataSource.b27();
                    this.listNodeDataSource.t26(false);
                    let u19 = this.listNodeDataSource.findIndex(p19);
                    this.listNodeDataSource.g26(u19);
                    this.listNodeDataSource.g27(Event.DRAG, u19);
                    return;
                }
                if (this.listNodeDataSource.h27(p19) === q7.EXPAND) {
                    this.listNodeDataSource.i27(this.listNodeDataSource.findIndex(p19));
                }
                let flag = false;
                if (this.listNodeDataSource.h27(m19) === q7.COLLAPSE) {
                    let currentIndex = this.listNodeDataSource.findIndex(m19);
                    if (this.listNodeDataSource.q25[currentIndex].j25()) {
                        this.listNodeDataSource.i27(currentIndex);
                    }
                    flag = true;
                }
                this.listNodeDataSource.j27();
                if (n19 !== null && p19 !== m19) {
                    this.listNodeDataSource.k27(o19, m19, q19, p19, n19);
                    this.listNodeDataSource.v26();
                }
                else {
                    this.listNodeDataSource.v26();
                    this.listNodeDataSource.l27(p19);
                    this.listNodeDataSource.v26();
                }
                let s19 = this.listNodeDataSource.findIndex(this.listNodeDataSource.m27());
                this.listNodeDataSource.n27(s19);
                this.listNodeDataSource.w26();
                this.listNodeDataSource.b27();
                this.listNodeDataSource.t26(false);
                let t19 = this.listNodeDataSource.findIndex(p19);
                this.listNodeDataSource.g26(t19);
                this.listNodeDataSource.g27(Event.DRAG, t19);
                this.listNodeDataSource.a27(false);
                this.listNodeDataSource.y26();
                this.listNodeDataSource.q25[t19].fontColor = this.treeViewTheme.e22;
                if (this.viewLastIndex !== -1 && k19 !== this.viewLastIndex) {
                    this.listNodeDataSource.q25[this.viewLastIndex].n24().y21?.e26(false);
                    this.listNodeDataSource.q25[this.viewLastIndex].n24().y21?.o27(false);
                }
                this.listNodeDataSource.lastIndex = this.viewLastIndex;
                if (this.listNodeDataSource.q25[this.viewLastIndex]) {
                    if (this.listNodeDataSource.q25[this.viewLastIndex].n24().x21 !== null) {
                        this.listNodeDataSource.q25[this.viewLastIndex].n24().x21?.d26(r7.NORMAL);
                        this.listNodeDataSource.q25[this.viewLastIndex].imageSource =
                            this.listNodeDataSource.q25[this.viewLastIndex].n24().x21?.source;
                        this.listNodeDataSource.q25[this.viewLastIndex].l22 =
                            this.listNodeDataSource.q25[this.viewLastIndex].n24().x21?.l22;
                    }
                }
                if (this.listNodeDataSource.q25[this.viewLastIndex]) {
                    this.listNodeDataSource.q25[this.viewLastIndex].c24({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                }
                this.listNodeDataSource.lastIndex = t19;
                let eventInfo = ({
                    type: 'requestFocusForAccessibility',
                    bundleName: getContext()?.abilityInfo?.bundleName,
                    triggerAction: 'common',
                    customId: `treeView_node${p19}`
                });
                accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                    setTimeout(() => {
                        this.accessibilityNodeType = t7.TEXT;
                    }, g7);
                    console.log(`test123 Succeeded in send event, eventInfo is ${JSON.stringify(eventInfo)}`);
                });
            });
        }, List);
        {
            const __lazyForEachItemGenFunction = _item => {
                const z18 = _item;
                {
                    const itemCreation2 = (elmtId, isInitialRender) => {
                        ListItem.create(() => { }, false);
                        ListItem.width('100%');
                        ListItem.height(z18.f24());
                        ListItem.padding({
                            start: LengthMetrics.resource(this.itemPadding.left),
                            end: LengthMetrics.resource(this.itemPadding.right)
                        });
                        ListItem.align(Alignment.Start);
                        ListItem.onDragStart((event, extraParams) => {
                            this.accessibilityNodeType = t7.LIFT;
                            if (this.listNodeDataSource.z26() || this.listNodeDataSource.k26() || this.isMultiPress) {
                                hilog.error(f7, e7, 'drag error, a item has been dragged');
                                return;
                            }
                            this.dropSelectedIndex = JSON.parse(extraParams).selectedIndex;
                            let a19 = JSON.parse(extraParams).selectedIndex;
                            let b19 = this.listNodeDataSource.getData(a19);
                            let c19 = z18.g24();
                            if (a19 >= this.listNodeDataSource.totalCount() || a19 === undefined) {
                                hilog.error(f7, e7, 'drag error, currentNodeIndex is not found in onDragStart');
                                return;
                            }
                            this.listNodeDataSource.a27(true);
                            this.listNodeDataSource.t26(true);
                            this.listNodeDataSource.p27(b19);
                            this.listNodeDataSource.q27(b19?.g24());
                            this.listNodeDataSource.r27(b19?.h24());
                            let d19 = g6;
                            this.listNodeDataSource.u26(d19);
                            this.listNodeDataSource.f27(a19);
                            if (c19 !== b19?.g24()) {
                                hilog.error(f7, e7, 'drag is too fast, it attribute a fault to OH');
                                this.listNodeDataSource.t26(false);
                                return;
                            }
                            let primaryTitle = b19.w24()?.primaryTitle === undefined ? '' :
                                b19.w24()?.primaryTitle;
                            let secondaryTitle = b19.w24()?.secondaryTitle === undefined ? '' :
                                b19.w24()?.secondaryTitle;
                            let e19 = this.listNodeDataSource.s27(primaryTitle);
                            let f19 = this.listNodeDataSource.s27(secondaryTitle);
                            let title = `${e19}, ${f19}`;
                            this.listNodeDataSource.t27(this.listNodeDataSource.getStringByName('treeview_accessibility_lift_node', title));
                            let g19 = [];
                            for (let h19 = 0; h19 < this.listNodeDataSource.q25.length; h19++) {
                                if (this.listNodeDataSource.q25[h19].h24() === -1) {
                                    g19.push(this.listNodeDataSource.q25[h19].g24());
                                }
                            }
                            this.allParentNode = g19;
                            let eventInfo = ({
                                type: 'requestFocusForAccessibility',
                                bundleName: getContext()?.abilityInfo?.bundleName,
                                triggerAction: 'common',
                                customId: `treeView_node_lift${c19}`
                            });
                            accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                                setTimeout(() => {
                                    this.accessibilityNodeType = t7.TEXT;
                                }, g7);
                            });
                            return { builder: () => {
                                    this.draggingPopup.call(this, b19);
                                } };
                        });
                    };
                    const observedDeepRender = () => {
                        this.observeComponentCreation2(itemCreation2, ListItem);
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            Row.create();
                            Row.onTouch(this.isAccessibilityEnabled ? undefined : (event) => {
                                this.touchInner(z18, event);
                            });
                        }, Row);
                        {
                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                if (isInitialRender) {
                                    let componentCall = new a8(this, {
                                        item: z18,
                                        listNodeDataSource: this.listNodeDataSource,
                                        index: this.listNodeDataSource.findIndex(z18.g24()),
                                        listTreeViewMenu: this.listTreeViewMenu,
                                        callBackClick: () => this.clickInner(z18),
                                    }, undefined, elmtId, () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 1291, m1: 13 });
                                    ViewPU.create(componentCall);
                                    let paramsLambda = () => {
                                        return {
                                            item: z18,
                                            listNodeDataSource: this.listNodeDataSource,
                                            index: this.listNodeDataSource.findIndex(z18.g24()),
                                            listTreeViewMenu: this.listTreeViewMenu,
                                            callBackClick: () => this.clickInner(z18)
                                        };
                                    };
                                    componentCall.paramsGenerator_ = paramsLambda;
                                }
                                else {
                                    this.updateStateVarsOfChildByElmtId(elmtId, {
                                        item: z18
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
            LazyForEach.create('1', this, this.listNodeDataSource, __lazyForEachItemGenFunction, __lazyForEachItemIdFunc);
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
        this.u27 = -1;
        this.v27 = [];
        this.listNodeDataSource = new z7();
        this.w27 = true;
        this.treeViewTheme = w7.getInstance();
    }
    p25() {
        return this.listNodeDataSource;
    }
    x27() {
        let y18 = this.listNodeDataSource.y27();
        return this.listNodeDataSource.x27(y18);
    }
    z27() {
        let x18 = this.listNodeDataSource.y27();
        return this.listNodeDataSource.a28(x18);
    }
    removeNode() {
        let v18 = this.listNodeDataSource.y27();
        if (v18 < 0) {
            return;
        }
        let parentNodeId = this.listNodeDataSource.b28(v18);
        let w18 = this.listNodeDataSource.removeNode(v18, parentNodeId);
        this.listNodeDataSource.c28(m7.REMOVE_NODE, parentNodeId, w18);
        this.v27.splice(this.v27.indexOf(v18), 1);
        this.listNodeDataSource.lastIndex = -1;
    }
    modifyNode() {
        let u18 = this.listNodeDataSource.y27();
        this.listNodeDataSource.i26(u18, m7.MODIFY_NODE);
    }
    add(o18) {
        let p18 = this.listNodeDataSource.y27();
        if (p18 === this.listNodeDataSource.u27 || !this.listNodeDataSource.y24(p18)) {
            return;
        }
        let q18 = this.listNodeDataSource.d28(p18);
        this.v27.push(this.v27[this.v27.length - 1] + 1);
        let r18 = this.v27[this.v27.length - 1];
        let s18 = this.listNodeDataSource.addNode(p18, r18, {
            isFolder: q18.isFolder,
            icon: q18.icon,
            symbolIconStyle: q18.symbolIconStyle,
            selectedIcon: q18.selectedIcon,
            symbolSelectedIconStyle: q18.symbolSelectedIconStyle,
            editIcon: q18.editIcon,
            symbolEditIconStyle: q18.symbolEditIconStyle,
            primaryTitle: '新建文件夹',
            container: q18.container,
            secondaryTitle: q18.secondaryTitle,
        }, o18);
        if (!s18) {
            return;
        }
        this.listNodeDataSource.c28(m7.ADD_NODE, p18, [r18]);
        this.listNodeDataSource.h26(n7.WARNINGS, o7.NONE, false, this.listNodeDataSource.f26());
        this.listNodeDataSource.i26(this.listNodeDataSource.f26(), m7.COMMIT_NODE);
        this.listNodeDataSource.q25[this.listNodeDataSource.f26()].q23(this.treeViewTheme.c22);
        let t18 = this.listNodeDataSource.findIndex(r18);
        this.listNodeDataSource.g26(t18);
        this.listNodeDataSource.g27(Event.TOUCH_UP, t18);
    }
    addNode(nodeParam) {
        if (nodeParam === undefined) {
            this.add(this.w27);
            return this;
        }
        else {
            let m18 = false;
            if (nodeParam.primaryTitle !== undefined &&
                !this.listNodeDataSource.e28(nodeParam.primaryTitle.toString())) {
                throw new Error('ListTreeNode[addNode]: ' +
                    'The directory name cannot contain the following characters\ /: *? "< > | or exceeds the maximum length.');
                return this;
            }
            if (nodeParam.primaryTitle === null && nodeParam.icon === null && nodeParam.symbolIconStyle === null) {
                throw new Error('ListTreeNode[addNode]: ' +
                    'The icon|symbolIconStyle and directory name cannot be empty at the same time.');
                return this;
            }
            if (nodeParam.currentNodeId === this.u27 || nodeParam.currentNodeId === null) {
                throw new Error('ListTreeNode[addNode]: currentNodeId can not be -1 or null.');
                return this;
            }
            if (nodeParam.currentNodeId !== undefined) {
                this.v27.push(nodeParam.currentNodeId);
            }
            if (nodeParam.parentNodeId !== undefined) {
                if (nodeParam.currentNodeId !== undefined) {
                    m18 =
                        this.listNodeDataSource.addNode(nodeParam.parentNodeId, nodeParam.currentNodeId, nodeParam, this.w27);
                }
            }
            if (!m18) {
                return this;
            }
            if (!this.w27 && nodeParam.parentNodeId !== undefined) {
                let n18 = this.v27[this.v27.length - 1];
                this.listNodeDataSource.c28(m7.ADD_NODE, nodeParam.parentNodeId, [n18]);
            }
            return this;
        }
    }
    refreshNode(parentId, parentSubTitle, l18) {
        this.listNodeDataSource.f28(parentId, parentSubTitle, l18);
    }
    buildDone() {
        this.listNodeDataSource.g28();
        this.listNodeDataSource.h28();
        this.listNodeDataSource.i28();
        r5(this.v27);
        this.w27 = false;
    }
}
class y7 {
    constructor() {
        this.j28 = [];
    }
    totalCount() {
        return 0;
    }
    getData(index) {
        return undefined;
    }
    registerDataChangeListener(listener) {
        if (this.j28.indexOf(listener) < 0) {
            this.j28.push(listener);
        }
    }
    unregisterDataChangeListener(listener) {
        const pos = this.j28.indexOf(listener);
        if (pos >= 0) {
            this.j28.splice(pos, 1);
        }
    }
    y26() {
        this.j28.forEach(listener => {
            listener.onDataReloaded();
        });
    }
    k28(index) {
        this.j28.forEach(listener => {
            listener.onDataAdd(index);
        });
    }
    f27(index) {
        if (index === undefined) {
            return;
        }
        this.j28.forEach(listener => {
            listener.onDataChange(index);
        });
    }
    l28(index) {
        this.j28.forEach(listener => {
            listener.onDataDelete(index);
        });
    }
    m28(from, to) {
        this.j28.forEach(listener => {
            listener.onDataMove(from, to);
        });
    }
}
function p5(i18, count, j18, k18) {
    let taskId = setTimeout(() => {
        k18.forEach((parentNodeId) => {
            q5(parentNodeId, j18, i18, count);
        });
        clearTimeout(taskId);
    }, b7);
}
function q5(parentNodeId, f18, g18, count) {
    let h18 = parentNodeId;
    while (h18 >= 0) {
        if (f18.has(h18)) {
            let parent = f18.get(h18);
            parent.r24().n28 =
                g18 ? parent.r24().n28 + count : parent.r24().n28 - count;
            h18 = parent.parentNodeId;
        }
        else {
            hilog.error(f7, e7, 'updateParentChildNumHandler: parent node not found');
            break;
        }
    }
}
function r5(e18) {
    let taskId = setTimeout(() => {
        e18.sort((a, b) => a - b);
        clearTimeout(taskId);
    }, b7);
}
class z7 extends y7 {
    constructor() {
        super();
        this.u27 = -1;
        this.o28 = new b8(v7);
        this.p28 = 50;
        this.MAX_CN_LENGTH = 254;
        this.MAX_EN_LENGTH = 255;
        this.INITIAL_INVALID_VALUE = -1;
        this.q25 = [];
        this.q28 = [];
        this.r28 = new Map();
        this.s28 = new Map();
        this.lastIndex = -1;
        this.t28 = -1;
        this.u28 = -1;
        this.v28 = -1;
        this.w28 = new Map();
        this.x28 = new Map();
        this.y28 = new Map();
        this.z28 = false;
        this.appEventBus = TreeListenerManager.getInstance().getTreeListener();
        this.a29 = false;
        this.b29 = false;
        this.c29 = this.INITIAL_INVALID_VALUE;
        this.d29 = this.INITIAL_INVALID_VALUE;
        this.e29 = null;
        this.f29 = 1;
        this.g29 = this.INITIAL_INVALID_VALUE;
        this.h29 = this.INITIAL_INVALID_VALUE;
        this.i29 = this.INITIAL_INVALID_VALUE;
        this.j29 = this.INITIAL_INVALID_VALUE;
        this.k29 = this.INITIAL_INVALID_VALUE;
        this.l29 = this.INITIAL_INVALID_VALUE;
        this.m29 = this.INITIAL_INVALID_VALUE;
        this.n29 = this.INITIAL_INVALID_VALUE;
        this.o29 = this.INITIAL_INVALID_VALUE;
        this.p29 = this.INITIAL_INVALID_VALUE;
        this.q29 = this.INITIAL_INVALID_VALUE;
        this.r29 = this.INITIAL_INVALID_VALUE;
        this.s29 = new Map();
        this.flag = p7.NONE;
        this.t29 = this.INITIAL_INVALID_VALUE;
        this.u29 = '';
        this.v29 = '';
        this.w29 = this.INITIAL_INVALID_VALUE;
        this.x29 = this.INITIAL_INVALID_VALUE;
        this.y29 = this.INITIAL_INVALID_VALUE;
        this.treeViewTheme = w7.getInstance();
        this.z29 = [];
        this.a30 = {
            b30: k6,
            c30: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_emphasize'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            xOffset: l6,
            d30: m6,
            e30: n6,
            f30: o6,
        };
        this.g30 = {
            s25: { minWidth: u6, maxWidth: v6 },
            y25: {
                z25: w6,
                b26: x6,
                a26: y6,
                c26: z6,
            },
            padding: { left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } },
            backgroundColor: p6,
            height: t6,
            shadow: {
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                color: s6,
                offsetX: 0,
                offsetY: e6,
            },
            borderRadius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            fontColor: this.treeViewTheme.c22,
            fontSize: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            fontWeight: FontWeight.Regular,
            w25: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_alpha_content_fourth'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }
        };
        this.subTitle = {
            h30: this.treeViewTheme.d22,
            i30: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_primary_contrary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            fontSize: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            fontWeight: FontWeight.Regular,
            margin: { left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } }
        };
        this.o28.c23 = -1;
        this.r28.set(-1, this.o28);
        this.s28.set(-1, v7);
    }
    j30(index) {
        if (index < 0 || index >= this.q25.length) {
            hilog.error(f7, e7, 'check index fail');
            return false;
        }
        return true;
    }
    k30(index, color) {
        if (!this.j30(index)) {
            return;
        }
        this.q25[index].c24(color);
        this.q25[index].q24(false);
    }
    d24(index) {
        return this.q25[index].d24();
    }
    l30(index, d18) {
        if (this.q25[index].l24()) {
            this.q25[index].q24(d18);
        }
    }
    d26(index, b18) {
        if (!this.j30(index)) {
            return;
        }
        let c18 = this.q25[index];
        c18.u24(b18 === r7.SELECTED ||
            b18 === r7.EDIT || b18 === r7.FINISH_EDIT);
        if (c18.n24().y21 !== null && b18 !== r7.DRAG_INSERT &&
            b18 !== r7.FINISH_DRAG_INSERT) {
            c18.n24().y21?.e26(b18 === r7.SELECTED ||
                b18 === r7.FINISH_EDIT);
        }
        if (c18.n24().x21 !== null) {
            c18.n24().x21?.d26(b18);
        }
    }
    m30(index, z17) {
        let a18 = this.q25[index];
        if (a18.n24().z21 !== undefined) {
            a18.n24().z21 = f8.n30(z17, this.w28.get(a18.g24()), a18.n24().z21?.type);
        }
    }
    o30() {
        if (!this.j30(this.lastIndex)) {
            return;
        }
        this.d26(this.lastIndex, r7.NORMAL);
        this.k30(this.lastIndex, this.q25[this.lastIndex].o24().normal);
        this.l30(this.lastIndex, false);
        this.f27(this.x28.get(this.q25[this.lastIndex].g24()));
    }
    p30() {
        let index = 0;
        this.x28.clear();
        this.y28.clear();
        this.q28.splice(0, this.q28.length);
        for (let y17 = 0; y17 < this.q25.length; y17++) {
            this.y28.set(this.q25[y17].g24(), y17);
            if (this.q25[y17].l24()) {
                this.x28.set(this.q25[y17].g24(), index++);
                this.q28.push(this.q25[y17]);
            }
        }
    }
    q30(v17) {
        if (v17 >= this.q25.length) {
            hilog.error(f7, e7, 'changeNodeStatus clickIndex error.');
            return;
        }
        let w17 = v17;
        let x17 = this.q25[v17].g24();
        if (this.w28.get(x17) === q7.EXPAND) {
            this.w28.set(x17, q7.COLLAPSE);
            this.q25[w17].n24().z21 = f8.r30(q7.COLLAPSE, this.q25[w17].n24().z21?.s30);
        }
        else if (this.w28.get(x17) === q7.COLLAPSE) {
            this.w28.set(x17, q7.EXPAND);
            this.q25[w17].n24().z21 = f8.r30(q7.EXPAND, this.q25[w17].n24().z21?.s30);
        }
    }
    t30(m17, n17) {
        if (m17 >= this.q25.length) {
            hilog.error(f7, e7, 'handleExpandAndCollapse clickIndex error.');
            return;
        }
        let o17 = m17;
        let p17 = this.q25[o17].g24();
        if (!this.w28.has(p17)) {
            return;
        }
        let q17 = this.w28.get(p17);
        if (this.q25[o17].r24().u30 && q17 === q7.COLLAPSE) {
            for (let u17 = 0; u17 < this.q25[o17].r24().n28; u17++) {
                if (this.q25[o17 + 1 + u17] === undefined) {
                    return;
                }
                this.q25[o17 + 1 + u17].k24(false);
                this.q25[o17 + 1 + u17].e24(c6);
            }
            this.p30();
            this.y26();
            return;
        }
        let r17 = new Array(this.q25[o17].r24().v30);
        r17[0] = o17 + 1;
        let index = 1;
        while (index < this.q25[o17].r24().v30) {
            r17[index] = r17[index - 1] + this.q25[r17[index - 1]].r24().n28 + 1;
            index++;
        }
        if (q17 === q7.EXPAND) {
            for (let s17 = 0; s17 < r17.length; s17++) {
                if (this.q25[r17[s17]] === undefined) {
                    return;
                }
                this.q25[r17[s17]].k24(true);
                this.q25[r17[s17]].e24(d6);
                let t17 = this.q25[r17[s17]].g24();
                if (this.w28.get(t17) === q7.EXPAND) {
                    this.t30(r17[s17], false);
                }
            }
        }
        r17 = null;
        if (n17) {
            this.p30();
            this.y26();
        }
    }
    i28() {
        p5(true, 1, this.r28, this.z29);
    }
    w30(l17) {
        l17.splice(0, l17.length);
        this.x28.clear();
        this.q28.splice(0, this.q28.length);
        this.y28.clear();
        this.s29.clear();
    }
    x30(g17, h17, i17) {
        let index = 0;
        let j17 = 0;
        this.w30(g17);
        try {
            this.y30((node) => {
                if (node.z30() >= 0 && this.s28.has(node.z30())) {
                    let k17 = new x7(node, this.s28.get(node.z30()));
                    k17.o23(node.r24().u30);
                    g17.push(k17);
                    this.y28.set(k17.g24(), j17++);
                    index = this.a31(k17, index);
                }
                return false;
            }, this.o28, h17, i17);
        }
        catch (err) {
            hilog.error(f7, e7, 'traverseSectionNodeDF function callbacks error.');
            this.w30(g17);
        }
    }
    a31(f17, index) {
        if (f17.r24().u30) {
            this.w28.set(f17.g24(), q7.COLLAPSE);
        }
        if (f17.l24()) {
            this.x28.set(f17.g24(), index++);
            this.q28.push(f17);
        }
        if (f17.y24()) {
            if (f17.w24().secondaryTitle !== undefined) {
                this.s29.set(f17.g24(), f17.w24().secondaryTitle);
            }
            else {
                this.s29.set(f17.g24(), '');
            }
        }
        return index;
    }
    h28() {
        let d17 = setTimeout(() => {
            let e17 = [];
            this.x30(e17, 0);
            this.q25.splice(0, this.q25.length);
            this.q25.push(...e17);
            this.q25.forEach((value, index) => {
                this.l28(index);
                this.k28(index);
            });
            clearTimeout(d17);
        }, b7);
    }
    g28() {
        this.x30(this.q25, 0, 1);
    }
    g26(index) {
        this.t28 = index;
    }
    y27() {
        if (!this.j30(this.t28)) {
            return -1;
        }
        return this.q25[this.t28].g24();
    }
    i27(c17) {
        this.q30(c17);
        this.t30(c17, true);
    }
    b31() {
        return this.z28;
    }
    f26() {
        return this.lastIndex;
    }
    findIndex(currentNodeId) {
        let b17 = -1;
        if (this.y28.has(currentNodeId)) {
            b17 = this.y28.get(currentNodeId);
        }
        return b17;
    }
    c31(index) {
        if (!this.j30(index)) {
            return;
        }
        this.d26(index, r7.NORMAL);
        this.k30(index, this.q25[index].o24().normal);
        this.l30(index, false);
        this.f27(this.x28.get(this.q25[index].g24()));
    }
    g27(event, index) {
        if (this.b29) {
            return;
        }
        if (!this.j30(index)) {
            return;
        }
        if (event === Event.TOUCH_DOWN || event === Event.TOUCH_UP || event === Event.MOUSE_BUTTON_RIGHT) {
            if (index !== this.lastIndex) {
                this.o30();
            }
        }
        this.d31(index, event);
    }
    d31(index, event) {
        let z16 = this.x28.get(this.q25[index].g24());
        switch (event) {
            case Event.TOUCH_DOWN:
                this.z28 = true;
                this.k30(index, this.q25[index].o24().j23);
                this.f27(z16);
                break;
            case Event.TOUCH_UP: {
                this.e31(index, z16);
                break;
            }
            case Event.HOVER:
                if (this.d24(index) !== this.q25[index].o24().selected) {
                    this.k30(index, this.q25[index].o24().i23);
                    this.f27(z16);
                }
                break;
            case Event.HOVER_OVER:
                if (this.d24(index) !== this.q25[index].o24().selected) {
                    this.k30(index, this.q25[index].o24().normal);
                    this.f27(z16);
                }
                break;
            case Event.FOCUS:
                this.l30(index, true);
                this.f27(z16);
                break;
            case Event.BLUR:
                this.l30(index, false);
                this.f27(z16);
                break;
            case Event.MOUSE_BUTTON_RIGHT:
                this.lastIndex = index;
                this.f31();
                break;
            case Event.DRAG:
                this.z28 = false;
                let a17 = this.q25[index];
                this.d26(index, r7.SELECTED);
                this.lastIndex = index;
                this.k30(index, a17.o24().selected);
                this.f27(z16);
                break;
            default:
                break;
        }
    }
    e31(index, x16) {
        if (this.a29) {
            this.a29 = false;
        }
        this.z28 = false;
        let y16 = this.q25[index];
        this.d26(index, r7.SELECTED);
        y16.q23(this.treeViewTheme.c22);
        this.lastIndex = index;
        this.k30(index, y16.o24().selected);
        this.f27(x16);
    }
    g31(t16, operation) {
        if (operation === m7.MODIFY_NODE) {
            let v16 = this.q25[this.u28];
            let w16 = {
                currentNodeId: v16?.g24(),
                parentNodeId: v16?.h24(),
            };
            this.appEventBus.emit(TreeListenType.NODE_MODIFY, w16);
        }
        else if (operation === m7.ADD_NODE) {
            let u16 = this.q25[t16];
            if (u16 === undefined) {
                return;
            }
            let icon = (u16.n24().x21 !== undefined) ?
                u16.n24().x21?.source : undefined;
            let selectedIcon = (u16.n24().x21 !== undefined) ?
                u16.n24().x21?.h31 : undefined;
            let editIcon = (u16.n24().x21 !== undefined) ?
                u16.n24().x21?.i31 : undefined;
            let callbackParam = {
                currentNodeId: u16?.g24(),
                parentNodeId: u16?.h24(),
            };
            this.appEventBus.emit(TreeListenType.NODE_ADD, callbackParam);
        }
    }
    f31() {
        if (this.u28 !== -1) {
            this.d26(this.u28, r7.FINISH_EDIT);
            this.m30(this.u28, r7.FINISH_EDIT);
            this.q25[this.u28].k25(false);
            this.q25[this.u28].a24(false);
            this.g31(this.u28, this.j31);
            this.f27(this.u28);
        }
    }
    i26(p16, operation) {
        let index = -1;
        if (p16 === -1) {
            return;
        }
        if (operation === m7.MODIFY_NODE) {
            for (let s16 = 0; s16 < this.q25.length; s16++) {
                if (this.q25[s16]?.g24() === p16) {
                    index = s16;
                    break;
                }
            }
            let r16 = this.q25[index];
            if (r16 === undefined) {
                return;
            }
            r16.k25(true);
            if (r16.n24().y21 === null) {
                return;
            }
            this.j31 = m7.MODIFY_NODE;
            r16.a24(true);
            this.d26(index, r7.EDIT);
            this.m30(index, r7.EDIT);
            this.u28 = index;
            if (r16.n24().inputText) {
                if (r16.n24().z21 !== null) {
                    r16.n24().inputText.rightMargin = { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_paragraph_margin_xs'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                }
                else {
                    r16.n24().inputText.rightMargin = { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_elements_margin_horizontal_m'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                }
            }
            this.f27(this.x28.get(p16));
        }
        index = p16;
        if (operation === m7.COMMIT_NODE) {
            let q16 = this.q25[index];
            if (q16 === undefined) {
                return;
            }
            q16.a24(false);
            q16.k25(false);
            this.d26(index, r7.FINISH_EDIT);
            this.m30(index, r7.FINISH_EDIT);
            this.g31(this.u28, this.j31);
            this.f27(this.x28.get(q16?.g24()));
        }
    }
    h26(l16, m16, isShow, index) {
        if (!this.j30(index)) {
            return;
        }
        let n16 = this.q25[index];
        if (n16 === undefined) {
            return;
        }
        n16.t23(isShow);
        let o16 = this.x28.get(n16.g24());
        if (!isShow) {
            this.f27(o16);
            return;
        }
        if (l16 === n7.HINTS) {
            if (n16.n24().y21 !== null) {
                n16.w23(n16.n24().y21?.title);
            }
            else {
                n16.w23('');
                n16.t23(false);
            }
            n16.u23(false);
            n16.v23({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            n16.x23(this.treeViewTheme.d22);
        }
        else if (l16 === n7.WARNINGS) {
            if (n16.n24().inputText !== null) {
                if (m16 === o7.INVALID_ERROR) {
                    n16.w23('invalid error');
                }
                else if (m16 === o7.LENGTH_ERROR) {
                    n16.w23('length error');
                }
                n16.u23(true);
                n16.v23({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_help_tip_bg'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                n16.x23({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_hint_contrary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            }
        }
        this.f27(o16);
    }
    k31(timeout, index) {
        if (!this.j30(index)) {
            return;
        }
        if (this.q25[index].n24().y21 !== null) {
            this.q25[index].n24().y21.l31 = timeout;
        }
        let k16 = this.x28.get(this.q25[index].g24());
        this.f27(k16);
    }
    n31(index, text) {
        this.u28 = index;
        if (this.q25[index].n24().y21 !== null) {
            this.q25[index].n24().y21.title = text;
        }
    }
    totalCount() {
        return this.x28.size;
    }
    getData(index) {
        if (index < 0 || index >= this.q28.length) {
            return undefined;
        }
        return this.q28[index];
    }
    o31(index, data) {
        if (!this.j30(index)) {
            return;
        }
        this.q25.splice(index, 0, data);
        this.y28.set(data.g24(), index);
        this.p30();
        this.k28(index);
    }
    p31(data) {
        this.q25.push(data);
        this.y28.set(data.g24(), this.q25.length);
        this.p30();
        this.k28(this.q25.length - 1);
    }
    a27(j16) {
        this.a29 = j16;
    }
    k26() {
        return this.a29;
    }
    t26(i16) {
        this.b29 = i16;
    }
    z26() {
        return this.b29;
    }
    p27(h16) {
        if (h16 === undefined) {
            return;
        }
        this.e29 = h16;
    }
    d27() {
        return this.e29;
    }
    r27(g16) {
        if (g16 === undefined) {
            return;
        }
        this.d29 = g16;
    }
    e27() {
        return this.d29;
    }
    r26() {
        return this.c29;
    }
    q27(f16) {
        if (f16 === undefined) {
            return;
        }
        this.c29 = f16;
    }
    u26(e16) {
        this.f29 = e16;
    }
    q31(item) {
        return item.g24() === this.r26() ? this.f29 : 1;
    }
    r25() {
        return this.g30;
    }
    p26(d16) {
        this.g29 = d16;
    }
    j26() {
        return this.g29;
    }
    l26(a16) {
        if (this.e29 === null || a16 === undefined) {
            return false;
        }
        let b16 = this.e29.x24();
        let parentId = b16.currentNodeId;
        let c16 = this.r28.get(a16)?.parentNodeId;
        while (c16 !== undefined && c16 !== -1) {
            if (parentId === c16) {
                return true;
            }
            else {
                c16 = this.r28.get(c16)?.parentNodeId;
            }
        }
        return false;
    }
    m26(z15) {
        this.i29 = z15;
    }
    r31() {
        return this.i29;
    }
    n26(currentIndex) {
        if (this.h29 !== this.INITIAL_INVALID_VALUE && this.x28.has(this.h29)) {
            let index = this.x28.get(this.h29);
            this.q25.forEach((value) => {
                if (value.g24() === this.h29) {
                    value.z24(false);
                    return;
                }
            });
            this.f27(index);
        }
        if ((this.o29 !== this.INITIAL_INVALID_VALUE &&
            this.p29 !== this.o29)) {
            clearTimeout(this.o29);
            if (this.q29 !== this.INITIAL_INVALID_VALUE) {
                this.s31(this.q29);
                let index = this.x28
                    .get(this.q25[this.q29].g24());
                this.f27(index);
            }
            this.p29 = this.o29;
        }
        this.o29 = this.n29;
        this.q29 = currentIndex;
        if ((this.l29 !== this.INITIAL_INVALID_VALUE &&
            this.m29 !== this.l29)) {
            clearTimeout(this.l29);
            this.m29 = this.l29;
        }
        this.l29 = this.k29;
        this.j29 = this.INITIAL_INVALID_VALUE;
    }
    s31(currentIndex) {
        if (!this.j30(currentIndex)) {
            return;
        }
        this.k30(currentIndex, this.q25[currentIndex].o24().normal);
        this.t31(currentIndex, false);
        this.d26(currentIndex, r7.FINISH_DRAG_INSERT);
        this.m30(currentIndex, r7.FINISH_DRAG_INSERT);
        this.q25[currentIndex].i25(false);
    }
    t31(index, y15) {
        if (this.q25[index].n24().y21 && this.q25[index].y23()) {
            this.q25[index].n24().y21?.o27(y15);
        }
    }
    u31(s15) {
        let t15 = [];
        while (s15 !== -1) {
            if (s15 === undefined) {
                return '';
            }
            let u15 = this.b28(s15);
            let v15 = this.r28.get(u15);
            if (v15 === undefined || u15 === undefined) {
                return '';
            }
            let primaryTitle = this.v31(v15).w24()?.primaryTitle === undefined
                ? '' : this.v31(v15).w24().primaryTitle;
            let secondaryTitle = this.v31(v15).w24()?.secondaryTitle === undefined
                ? '' : this.v31(v15).w24().secondaryTitle;
            let w15 = this.s27(primaryTitle);
            let x15 = this.s27(secondaryTitle);
            t15.unshift(`${w15}, ${x15}`);
            s15 = v15.currentNodeId;
        }
        return t15.join(',');
    }
    w31(h15) {
        if (h15 === undefined) {
            return '';
        }
        let i15 = this.b28(h15);
        if (i15 === -1) {
            let o15 = [];
            let p15 = this.r28.get(h15);
            if (p15 === undefined || i15 === undefined) {
                return '';
            }
            let primaryTitle = this.v31(p15).w24()?.primaryTitle === undefined
                ? '' : this.v31(p15).w24().primaryTitle;
            let secondaryTitle = this.v31(p15).w24()?.secondaryTitle === undefined
                ? '' : this.v31(p15).w24().secondaryTitle;
            let q15 = this.s27(primaryTitle);
            let r15 = this.s27(secondaryTitle);
            o15.unshift(`${q15}, ${r15}`);
            return o15.join(',');
        }
        else {
            let j15 = [];
            while (h15 !== -1) {
                if (h15 === undefined) {
                    return '';
                }
                let k15 = this.b28(h15);
                let l15 = this.r28.get(k15);
                if (l15 === undefined || k15 === undefined) {
                    return '';
                }
                let primaryTitle = this.v31(l15).w24()?.primaryTitle === undefined
                    ? '' : this.v31(l15).w24().primaryTitle;
                let secondaryTitle = this.v31(l15).w24()?.secondaryTitle === undefined
                    ? '' : this.v31(l15).w24().secondaryTitle;
                let m15 = this.s27(primaryTitle);
                let n15 = this.s27(secondaryTitle);
                j15.unshift(`${m15}, ${n15}`);
                h15 = l15.currentNodeId;
            }
            return j15.join(',');
        }
    }
    x31(a15, b15, c15) {
        this.u31(c15);
        if (b15 === undefined || c15 === undefined) {
            return;
        }
        let parentId = this.b28(c15);
        let d15 = a15.indexOf(c15) + 2;
        let e15 = this.x27(parentId);
        let f15 = e15.map(item => item.itemId);
        let g15 = f15.indexOf(c15) + 2;
        if (parentId === -1 && this.h27(b15) === q7.COLLAPSE ||
            parentId === -1 && this.h27(b15) === undefined) {
            this.t27(this.getStringByName('treeview_accessibility_move_node_parent', d15));
        }
        else if (this.h27(b15) === q7.EXPAND) {
            this.t27(this.getStringByName('treeview_accessibility_move_node_child', this.u31(c15), 1));
        }
        else if (parentId !== -1) {
            this.t27(this.getStringByName('treeview_accessibility_move_node_child', this.u31(c15), g15));
        }
    }
    getStringByName(resName, ...args) {
        if (resName) {
            try {
                return getContext()?.resourceManager.getStringByNameSync(resName, ...args);
            }
            catch (error) {
                console.error(`Ace SegmentButton getAccessibilityDescription, error: ${error.toString()}`);
            }
        }
        return '';
    }
    t27(textAnnouncedForAccessibility) {
        let eventInfo = ({
            type: 'announceForAccessibility',
            bundleName: getContext()?.abilityInfo?.bundleName,
            triggerAction: 'common',
            textAnnouncedForAccessibility: textAnnouncedForAccessibility
        });
        accessibility.sendAccessibilityEvent(eventInfo);
    }
    s27(resource) {
        let z14 = '';
        try {
            if (typeof resource === 'string') {
                z14 = resource;
            }
            else {
                z14 = getContext()?.resourceManager?.getStringSync(resource?.id);
            }
        }
        catch (error) {
            let code = error.code;
            let message = error.message;
            hilog.error(0x3900, 'Ace', `treeView getAccessibleTitleText error, code: ${code}, message: ${message}`);
        }
        return z14;
    }
    q26(flag, index, p14, q14) {
        let r14 = (this.i29 !== index || this.flag !== flag) ? true : false;
        this.i29 = index;
        if ((r14 || p14) && this.a29) {
            this.flag = flag;
            let currentNodeId = this.getData(index)?.g24();
            let s14 = this.getData(index)?.d25();
            if (currentNodeId !== undefined) {
                s14 = (this.w28.get(currentNodeId) === q7.EXPAND &&
                    this.flag === p7.DOWN_FLAG) ? (s14 ? s14 + 1 : undefined) : s14;
                if (this.h29 !== this.INITIAL_INVALID_VALUE &&
                    this.x28.has(this.h29)) {
                    let y14 = this.x28.get(this.h29);
                    this.q25.forEach((value) => {
                        if (value.g24() === this.h29) {
                            value.z24(false);
                        }
                    });
                    this.f27(y14);
                }
                let t14 = this.getData(index - 1)?.g24();
                let u14 = this.getData(index + 2)?.g24();
                let v14 = this.getData(index + 1)?.g24();
                let w14 = this.r28.get(v14);
                if (this.flag === p7.DOWN_FLAG && index < this.totalCount() - 1) {
                    this.getData(index)?.z24(false);
                    this.getData(index + 1)?.z24(true);
                    this.getData(index)?.g25(false);
                    this.getData(index + 1)?.b25(s14);
                    this.f27(index);
                    this.f27(index + 1);
                    this.h29 = this.getData(index + 1)?.g24();
                    let x14 = this.r28.get(v14);
                    if (!x14?.s24.u30) {
                        this.x31(q14, v14, v14);
                    }
                    else {
                        this.x31(q14, v14, u14);
                    }
                }
                else if (this.flag === p7.UP_FLAG && index < this.totalCount() - 1) {
                    this.getData(index)?.z24(true);
                    this.getData(index + 1)?.z24(false);
                    this.getData(index)?.g25(false);
                    this.getData(index)?.b25(s14);
                    this.f27(index);
                    this.f27(index + 1);
                    this.h29 = this.getData(index)?.g24();
                    if (w14?.s24.u30 && w14?.parentNodeId !== -1) {
                        this.x31(q14, v14, v14);
                    }
                    else if (w14?.s24.u30 && w14?.parentNodeId === -1) {
                        this.x31(q14, t14, v14);
                    }
                }
                else if (index >= this.totalCount() - 1) {
                    if (this.flag === p7.DOWN_FLAG) {
                        this.getData(index)?.z24(false);
                        this.getData(index)?.g25(true);
                    }
                    else {
                        this.getData(index)?.z24(true);
                        this.getData(index)?.g25(false);
                    }
                    this.getData(index)?.b25(s14);
                    this.f27(index);
                    this.h29 = this.getData(index)?.g24();
                }
            }
        }
    }
    s26(currentIndex, currentNodeId, g14) {
        let h14 = currentIndex !== this.j29 ? true : false;
        let i14 = this.getData(g14)?.f25();
        let j14 = this.q25[currentIndex + 1]?.g24();
        let k14 = this.b28(currentNodeId);
        if (i14) {
            this.j29 = this.INITIAL_INVALID_VALUE;
        }
        else {
            this.j29 = currentIndex;
        }
        if (i14 || h14) {
            let l14 = !i14 && (!this.a29 ||
                (this.w28.get(currentNodeId) === q7.COLLAPSE && this.a29) ||
                (!this.w28.has(currentNodeId) && this.q25[currentIndex].y24()));
            if (l14) {
                this.k30(currentIndex, this.q25[currentIndex].o24().i23);
                this.f27(g14);
                let o14 = this.a29 ? 1000 : 0;
                this.n29 = setTimeout(() => {
                    this.y31(currentIndex);
                    if (k14 === -1) {
                        this.t27(this.getStringByName('treeview_accessibility_move_node_child', this.w31(currentNodeId), 1));
                    }
                    else {
                        this.t27(this.getStringByName('treeview_accessibility_move_node_child', this.w31(j14), 1));
                    }
                }, o14);
            }
            if (i14 || (this.o29 !== this.INITIAL_INVALID_VALUE &&
                this.p29 !== this.o29)) {
                clearTimeout(this.o29);
                if (this.q29 !== this.INITIAL_INVALID_VALUE) {
                    this.s31(this.q29);
                    this.y26();
                }
                this.p29 = this.o29;
            }
            this.o29 = this.n29;
            this.q29 = currentIndex;
            if (!i14 && this.w28.get(currentNodeId) === q7.COLLAPSE) {
                let m14 = this.getData(g14)?.x24().children[0]?.currentNodeId;
                let n14 = 2000;
                this.k29 = setTimeout(() => {
                    this.s31(this.q29);
                    if (m14 !== undefined) {
                        this.z31(currentIndex, m14);
                    }
                }, n14);
            }
            if (i14 || (this.l29 !== this.INITIAL_INVALID_VALUE &&
                this.m29 !== this.l29)) {
                clearTimeout(this.l29);
                this.m29 = this.l29;
            }
            this.l29 = this.k29;
        }
    }
    y31(currentIndex) {
        this.q25.forEach((value) => {
            if (value.g24() === this.h29) {
                value.z24(false);
                value.g25(false);
                return;
            }
        });
        this.k30(currentIndex, this.q25[currentIndex].o24().k23);
        this.q25[currentIndex].i25(true);
        this.t31(currentIndex, true);
        this.d26(currentIndex, r7.DRAG_INSERT);
        this.m30(currentIndex, r7.DRAG_INSERT);
        this.y26();
    }
    z31(currentIndex, f14) {
        this.q25.forEach((value) => {
            if (value.g24() === this.h29) {
                value.z24(false);
                value.g25(false);
            }
        });
        this.q25.forEach((value) => {
            if (this.a29 && value.g24() === f14) {
                value.z24(true);
            }
        });
        this.q30(currentIndex);
        this.t30(currentIndex, true);
        this.h29 = f14;
    }
    v26() {
        if (this.h29 !== this.INITIAL_INVALID_VALUE && this.x28.has(this.h29)) {
            this.q25.forEach((value) => {
                if (value.g24() === this.h29) {
                    value.z24(false);
                    value.g25(false);
                    return;
                }
            });
            let index = this.x28.get(this.h29);
            this.f27(index);
        }
    }
    w26() {
        if (this.o29 !== this.INITIAL_INVALID_VALUE &&
            this.p29 !== this.o29) {
            clearTimeout(this.o29);
            if (this.q29 !== this.INITIAL_INVALID_VALUE) {
                this.s31(this.q29);
            }
        }
    }
    x26() {
        if (this.l29 !== this.INITIAL_INVALID_VALUE &&
            this.m29 !== this.l29) {
            clearTimeout(this.l29);
        }
    }
    a32(currentNodeId) {
        if (this.s29.has(currentNodeId)) {
            if (typeof this.s29.get(currentNodeId) === 'number') {
                return this.s29.get(currentNodeId)?.toString();
            }
            else {
                return this.s29.get(currentNodeId);
            }
        }
        else {
            return '';
        }
    }
    b32(currentNodeId) {
        return this.s29.has(currentNodeId);
    }
    b27() {
        this.q29 = this.INITIAL_INVALID_VALUE;
        this.j29 = this.INITIAL_INVALID_VALUE;
        this.g29 = this.INITIAL_INVALID_VALUE;
        this.c29 = this.INITIAL_INVALID_VALUE;
        this.flag = p7.NONE;
    }
    c27(e14) {
        this.s29.set(this.t29, this.u29);
        this.s29.set(e14, this.v29);
        this.f27(this.x28.get(this.t29));
        this.f27(this.x28.get(e14));
    }
    f28(b14, c14, d14) {
        this.t29 = b14;
        this.u29 = c14;
        this.v29 = d14;
    }
    c32() {
        return this.v29;
    }
    h27(currentNodeId) {
        return this.w28.get(currentNodeId);
    }
    m27() {
        return this.r29;
    }
    j27() {
        this.q25.forEach((value, index) => {
            if (index === this.q29) {
                this.r29 = value.g24();
            }
        });
    }
    l27(a14) {
        this.h29 = a14;
    }
    n27(z13) {
        this.q29 = z13;
    }
    k27(d13, e13, f13, g13, h13) {
        let i13 = [];
        let parentNodeId = d13;
        let currentNodeId = g13;
        let nodeParam = h13.w24();
        let j13 = null;
        let k13 = h13.x24();
        let l13 = false;
        let m13 = this.INITIAL_INVALID_VALUE;
        let n13 = this.INITIAL_INVALID_VALUE;
        let o13 = this.flag === p7.DOWN_FLAG ? true : false;
        n13 = this.d32(f13, g13);
        m13 = this.d32(d13, e13) + 1;
        if (d13 !== f13) {
            m13 = o13 ? m13 + 1 : m13;
        }
        else {
            if (m13 > n13) {
                m13 = o13 ? m13 : m13 - 1;
            }
            else {
                m13 = o13 ? m13 + 1 : m13;
            }
        }
        for (let y13 = 0; y13 < this.q25.length; y13++) {
            if (this.q25[y13].g24() === e13) {
                l13 = this.q25[y13].j25();
                if (this.flag === p7.DOWN_FLAG && this.w28.get(e13) === q7.EXPAND) {
                    parentNodeId = e13;
                    m13 = 0;
                }
                else if (this.flag === p7.UP_FLAG && this.w28.get(e13) ===
                    q7.EXPAND &&
                    this.q25[y13].a25() === false) {
                    parentNodeId = e13;
                    m13 = 0;
                }
                else if (l13) {
                    parentNodeId = e13;
                    m13 = 0;
                }
                break;
            }
        }
        let callbackParam = {
            currentNodeId: currentNodeId,
            parentNodeId: parentNodeId,
            childIndex: m13,
        };
        this.appEventBus.emit(TreeListenType.NODE_MOVE, callbackParam);
        i13.push({ parentId: parentNodeId, e32: currentNodeId, data: nodeParam });
        let callback = (node, w13) => {
            if (node) {
                parentNodeId = node.parentNodeId;
                currentNodeId = node.currentNodeId;
                for (let x13 = 0; x13 < w13.length; x13++) {
                    if (w13[x13].g24() === currentNodeId) {
                        j13 = w13[x13];
                        break;
                    }
                }
                if (j13 === null) {
                    return false;
                }
                let nodeParam = j13.w24();
                if (parentNodeId !== f13) {
                    i13.push({ parentId: parentNodeId, e32: currentNodeId, data: nodeParam });
                }
                return false;
            }
            return false;
        };
        this.f32(callback, k13, this.q25);
        let p13 = this.removeNode(g13, f13);
        if (p13.length === 0) {
            return;
        }
        let q13 = e13;
        let isAfter = o13;
        if (this.w28.get(e13) === q7.EXPAND) {
            isAfter = false;
            this.q25.forEach((value) => {
                if (value.g24() === e13 && value.a25() === false) {
                    if (value.x24().children.length) {
                        q13 = value.x24().children[0].currentNodeId;
                    }
                    else {
                        q13 = this.INITIAL_INVALID_VALUE;
                    }
                }
            });
        }
        else if (!this.w28.get(e13) && l13) {
            this.w28.set(e13, q7.EXPAND);
        }
        let r13 = this.g32(i13[0].parentId, i13[0].e32, q13, isAfter, i13[0].data);
        if (!r13) {
            return;
        }
        for (let u13 = 1; u13 < i13.length; u13++) {
            let v13 = this.addNode(i13[u13].parentId, i13[u13].e32, i13[u13].data, false);
            if (!v13) {
                return;
            }
        }
        for (let t13 = 0; t13 < this.q25.length; t13++) {
            if (this.q25[t13].g24() === f13) {
                if (this.q25[t13].n24().z21 === null) {
                    this.q25[t13].b24(false);
                    this.w28.delete(f13);
                    break;
                }
            }
        }
        let s13 = [...this.q25];
        this.h32(s13);
    }
    h32(z12) {
        let index = 0;
        let a13 = 0;
        this.q25.splice(0, this.q25.length);
        this.x28.clear();
        this.q28.splice(0, this.q28.length);
        this.i32((node) => {
            let currentNodeId = node.currentNodeId;
            if (currentNodeId >= 0) {
                if (this.s28.has(currentNodeId)) {
                    let b13 = new x7(node, this.s28.get(currentNodeId));
                    b13.o23(node.r24().u30);
                    this.q25.push(b13);
                    this.y28.set(b13.g24(), a13++);
                    if (this.w28.get(currentNodeId) === q7.EXPAND) {
                        b13.n24().z21 = f8.r30(q7.EXPAND, b13.n24().z21?.s30);
                    }
                    else if (this.w28.get(currentNodeId) === q7.COLLAPSE) {
                        b13.n24().z21 = f8.r30(q7.COLLAPSE, b13.n24().z21?.s30);
                    }
                    for (let c13 = 0; c13 < z12.length; c13++) {
                        if (z12[c13].g24() === b13.g24()) {
                            b13.k24(z12[c13].l24());
                            b13.e24(z12[c13].f24());
                            if (b13.n24().y21 && b13.y23()) {
                                b13.n24().y21.title = z12[c13].n24().y21?.title;
                            }
                            break;
                        }
                    }
                    if (b13.l24()) {
                        this.x28.set(b13.g24(), index++);
                        this.q28.push(b13);
                    }
                }
            }
            return false;
        });
    }
    j32() {
        return this.a30;
    }
    k32(w12) {
        let x12 = this.x28.get(w12.g24()) - 1;
        if (x12 > this.INITIAL_INVALID_VALUE) {
            let y12 = this.getData(x12);
            return (w12.a25() === true && !w12.j25() && !y12?.j25()) ?
                Visibility.Visible : Visibility.Hidden;
        }
        else {
            return (w12.a25() === true && !w12.j25()) ?
                Visibility.Visible : Visibility.Hidden;
        }
    }
    l32() {
        return this.subTitle;
    }
    y24(v12) {
        if (this.x28.has(v12)) {
            return this.getData(this.x28.get(v12))?.y24();
        }
        return false;
    }
    n32(u12) {
        return u12 ? this.subTitle.i30 : this.treeViewTheme.d22;
    }
    d32(r12, s12) {
        let t12 = this.INITIAL_INVALID_VALUE;
        if (this.r28.has(r12)) {
            let node = this.r28.get(r12);
            if (node.z30() === r12) {
                node.children.forEach((value, index) => {
                    if (value.z30() === s12) {
                        t12 = index;
                        return;
                    }
                });
            }
        }
        return t12;
    }
    o32(q12) {
        this.w29 = q12;
    }
    p32() {
        return this.w29;
    }
    q32(p12) {
        this.x29 = p12;
    }
    r32() {
        return this.x29;
    }
    s32() {
        return this.y29;
    }
    o26(flag) {
        this.flag = flag;
    }
    i32(callback, root = this.o28) {
        let stack = [];
        let n12 = false;
        stack.unshift(root);
        let o12 = stack.shift();
        while (!n12 && o12) {
            n12 = callback(o12) === true;
            if (!n12) {
                stack.unshift(...o12.children);
                o12 = stack.shift();
            }
        }
    }
    y30(callback, root = this.o28, i12, j12) {
        let stack = [];
        let k12 = false;
        let l12 = false;
        stack.unshift(root);
        let m12 = stack.shift();
        while (!k12 && m12) {
            try {
                if (i12 !== undefined && m12.c23 < i12) {
                    l12 = true;
                }
                if (j12 !== undefined && m12.c23 > j12) {
                    l12 = true;
                }
                if (!l12) {
                    k12 = callback(m12);
                }
            }
            catch (err) {
                throw new Error('traverseSectionNodeDF function callbacks error');
            }
            if (!k12) {
                stack.unshift(...m12.children);
                m12 = stack.shift();
                l12 = false;
            }
        }
    }
    t32(g12, h12, count) {
        let parentNodeId = g12.parentNodeId;
        while (parentNodeId >= 0) {
            if (this.r28.has(parentNodeId)) {
                let parent = this.r28.get(parentNodeId);
                parent.r24().n28 =
                    h12 ? parent.r24().n28 + count : parent.r24().n28 - count;
                parentNodeId = parent.parentNodeId;
            }
            else {
                hilog.error(f7, e7, 'updateParentChildNum: parent node not found.');
                break;
            }
        }
    }
    b28(currentNodeId) {
        let current = new b8(v7);
        if (this.r28.has(currentNodeId)) {
            current = this.r28.get(currentNodeId);
        }
        return current.parentNodeId;
    }
    u32(z11, a12) {
        let b12 = [];
        if (z11.length === 0) {
            return;
        }
        let startIndex = undefined;
        for (let d12 = 0; d12 < z11.length; d12++) {
            if (this.x28.has(z11[d12])) {
                let f12 = this.x28.get(z11[d12]);
                b12.push(f12);
            }
            if (startIndex === undefined && this.y28.has(z11[d12])) {
                startIndex = this.y28.get(z11[d12]);
            }
            if (startIndex !== undefined) {
                let e12 = this.q25.splice(startIndex, 1);
                e12 = null;
            }
            if (this.w28.has(z11[d12])) {
                this.w28.delete(z11[d12]);
            }
        }
        b12.forEach((value) => {
            this.l28(value);
            this.f27(value);
        });
        if (a12.n24().z21 === null) {
            if (this.y28.has(a12.g24())) {
                let c12 = this.y28.get(a12.g24());
                this.q25[c12]?.b24(false);
            }
            this.w28.delete(a12.g24());
            this.f27(this.x28.get(a12.g24()));
        }
        let callbackParam = {
            currentNodeId: a12.g24(),
            parentNodeId: a12.h24(),
        };
        this.p30();
        this.appEventBus.emit(TreeListenType.NODE_DELETE, callbackParam);
    }
    v32(w11) {
        let x11 = new x7(new b8(v7), v7);
        if (this.r28.has(w11[0])) {
            let node = this.r28.get(w11[0]);
            x11 = new x7(node, this.s28.get(w11[0]));
            x11.o23(node.r24().u30);
        }
        x11.k25(true);
        let index = 0;
        for (let y11 = 0; y11 < this.q25.length; y11++) {
            if (this.q25[y11].g24() === x11.h24()) {
                index = y11;
                if (this.q25[y11].n24().z21 === null) {
                    this.q25[y11].b24(true);
                    this.f27(index);
                }
                else if (this.w28.get(this.q25[y11].g24()) === q7.COLLAPSE) {
                    this.q30(index);
                }
                this.q25.splice(y11 + 1, 0, x11);
                this.q25[y11 + 1].a24(true);
                this.q25[y11 + 1].k24(true);
                this.q25[y11 + 1].e24(d6);
                this.y28.set(w11[0], y11 + 1);
                this.d26(y11 + 1, r7.EDIT);
                this.j31 = m7.ADD_NODE;
                this.k28(y11 + 1);
                this.g31(y11 + 1, this.j31);
                break;
            }
        }
        this.u28 = index + 1;
        this.g26(index);
        this.lastIndex = index;
        this.w28.set(x11.h24(), q7.EXPAND);
        this.t30(index, true);
    }
    c28(operation, parentNodeId, t11) {
        let u11 = new x7(new b8(v7), v7);
        if (this.r28.has(parentNodeId)) {
            let v11 = this.r28.get(parentNodeId);
            u11 = new x7(v11, this.s28.get(parentNodeId));
            u11.o23(v11.r24().u30);
        }
        if (operation === m7.REMOVE_NODE) {
            this.s29.set(parentNodeId, this.u29);
            this.f27(this.x28.get(parentNodeId));
            this.u32(t11, u11);
        }
        if (operation === m7.ADD_NODE) {
            this.y29 = t11[0];
            this.s29.set(this.y27(), this.u29);
            this.s29.set(t11[0], this.v29);
            this.v32(t11);
        }
    }
    removeNode(currentNodeId, parentNodeId) {
        if (this.r28.has(parentNodeId) && this.r28.has(currentNodeId)) {
            let parent = this.r28.get(parentNodeId);
            let current = this.r28.get(currentNodeId);
            let p11 = [];
            let index = current.w32;
            let q11 = 0;
            if (index < 0) {
                hilog.error(f7, e7, 'node does not exist.');
                return [];
            }
            else {
                q11 = parent.children[index].r24().n28 + 1;
                this.x32(parent.children[index], p11);
                for (let s11 = index; s11 < parent.children.length; s11++) {
                    parent.children[s11].w32 -= 1;
                }
                let node = parent.children.splice(index, 1);
                node = null;
                this.y32(parentNodeId);
            }
            parent.r24().v30 = parent.children.length;
            parent.r24().n28 -= (q11);
            let r11 = [];
            r11.push(parent.parentNodeId);
            p5(false, q11, this.r28, r11);
            return p11;
        }
        else {
            hilog.error(f7, e7, 'parent does not exist.');
            return [];
        }
    }
    addNode(parentNodeId, currentNodeId, data, m11) {
        if (this.o28 === null) {
            this.o28 = new b8(v7);
            this.o28.c23 = -1;
            this.r28.set(-1, this.o28);
            this.s28.set(-1, v7);
        }
        if (this.r28.has(parentNodeId)) {
            let parent = this.r28.get(parentNodeId);
            let n11 = new b8(data);
            if (parent.c23 > this.p28) {
                hilog.error(f7, e7, 'ListDataSource[addNode]: The level of the tree view cannot exceed 50.');
                return false;
            }
            n11.c23 = parent.c23 + 1;
            n11.parentNodeId = parentNodeId;
            n11.currentNodeId = currentNodeId;
            n11.w32 = parent.children.length;
            data.parentNodeId = parentNodeId;
            data.currentNodeId = currentNodeId;
            if (data.symbolIconStyle && !data.icon) {
                data.icon = 'symbolUsed';
            }
            parent.children.push(n11);
            parent.r24().u30 = true;
            parent.r24().v30 = parent.children.length;
            parent.r24().n28 += 1;
            this.y32(parentNodeId);
            if (m11) {
                this.z29.push(parent.parentNodeId);
            }
            else {
                let o11 = [];
                o11.push(parent.parentNodeId);
                p5(true, 1, this.r28, o11);
            }
            this.s28.set(currentNodeId, data);
            this.r28.set(currentNodeId, n11);
            return true;
        }
        else {
            hilog.error(f7, e7, 'ListDataSource[addNode]: Parent node not found.');
            return false;
        }
    }
    y32(parentNodeId) {
        let parent = this.r28.get(parentNodeId);
        let l11 = this.y28.get(parentNodeId);
        if (parent.children.length > 0) {
            if (this.y28.has(parentNodeId)) {
                this.q25[l11]?.o23(true);
            }
        }
        else {
            this.q25[l11]?.o23(false);
        }
    }
    x32(i11, j11) {
        let k11 = [];
        let callback = (node) => {
            k11.push(node);
            return false;
        };
        this.i32(callback, i11);
        k11.forEach((value) => {
            j11.push(value.z30());
            this.r28.delete(value.z30());
            this.s28.delete(value.z30());
            value = new b8(v7);
        });
    }
    v31(h11) {
        if (h11?.currentNodeId === undefined) {
            hilog.error(f7, e7, 'getNodeInfoByNodeItem: currentId is undefined');
            return new x7(new b8(v7), v7);
        }
        if (!this.y28.has(h11.currentNodeId)) {
            hilog.error(f7, e7, 'getNodeInfoByNodeItem: not has nodeItem.');
            return new x7(new b8(v7), v7);
        }
        let index = this.y28.get(h11.currentNodeId);
        return this.q25[index];
    }
    d28(d11) {
        let parent = new b8(v7);
        if (this.r28.has(d11)) {
            parent = this.r28.get(d11);
        }
        let e11 = v7;
        if (parent) {
            let f11 = this.v31(parent);
            if (parent.children.length === 0) {
                if (f11.n24().x21 !== undefined) {
                    e11.icon = f11.n24().x21?.v25;
                    e11.symbolIconStyle = f11.n24().x21?.u25;
                    e11.selectedIcon = f11.n24().x21?.h31;
                    e11.symbolSelectedIconStyle = f11.n24().x21?.z32;
                    e11.editIcon = f11.n24().x21?.i31;
                    e11.symbolEditIconStyle = f11.n24().x21?.a33;
                    e11.container = f11.t24();
                }
                else {
                    e11.icon = undefined;
                    e11.symbolIconStyle = undefined;
                    e11.selectedIcon = undefined;
                    e11.symbolSelectedIconStyle = undefined;
                    e11.editIcon = undefined;
                    e11.symbolEditIconStyle = undefined;
                    e11.container = f11.t24();
                }
            }
            else if (parent.children.length > 0) {
                let g11 = this.v31(parent.children[0]);
                if (f11.n24().x21 !== null) {
                    e11.icon = (g11.n24().x21 !== undefined) ?
                        g11.n24().x21?.v25 : undefined;
                    e11.symbolIconStyle = (g11.n24().x21 !== undefined) ?
                        g11.n24().x21?.u25 : undefined;
                    e11.selectedIcon = (g11.n24().x21 !== undefined) ?
                        g11.n24().x21?.h31 : undefined;
                    e11.symbolSelectedIconStyle = (g11.n24().x21 !== undefined) ?
                        g11.n24().x21?.z32 : undefined;
                    e11.editIcon = (g11.n24().x21 !== undefined) ?
                        g11.n24().x21?.i31 : undefined;
                    e11.symbolEditIconStyle = (g11.n24().x21 !== undefined) ?
                        g11.n24().x21?.a33 : undefined;
                    e11.container = g11.t24();
                }
                else {
                    e11.icon = undefined;
                    e11.symbolIconStyle = undefined;
                    e11.selectedIcon = undefined;
                    e11.symbolSelectedIconStyle = undefined;
                    e11.editIcon = undefined;
                    e11.symbolEditIconStyle = undefined;
                    e11.container = g11.t24();
                }
            }
        }
        return e11;
    }
    a28(z10) {
        let parent = new b8(v7);
        if (this.r28.has(z10)) {
            parent = this.r28.get(z10);
        }
        if (parent) {
            if (parent.children.length === 0) {
                return [];
            }
            else if (parent.children.length > 0) {
                let a11 = new Array(parent.children.length);
                for (let c11 = 0; c11 < a11.length; c11++) {
                    a11[c11] = 0;
                }
                for (let b11 = 0; b11 < parent.children.length && b11 < a11.length; b11++) {
                    a11[b11] = parent.children[b11].currentNodeId;
                }
                return a11;
            }
        }
        return [];
    }
    x27(u10) {
        let parent = new b8(v7);
        if (this.r28.has(u10)) {
            parent = this.r28.get(u10);
        }
        if (parent) {
            if (parent.children.length === 0) {
                return [];
            }
            else if (parent.children.length > 0) {
                let v10 = new Array(parent.children.length);
                for (let y10 = 0; y10 < v10.length; y10++) {
                    v10[y10] = {};
                }
                for (let w10 = 0; w10 < parent.children.length && w10 < v10.length; w10++) {
                    v10[w10].itemId = parent.children[w10].currentNodeId;
                    let x10 = this.v31(parent.children[w10]);
                    if (x10.n24().x21) {
                        v10[w10].b33 = x10.n24().x21?.source;
                    }
                    if (x10.n24().y21) {
                        v10[w10].c33 = x10.n24().y21?.title;
                    }
                    v10[w10].isFolder = x10.y24();
                }
                return v10;
            }
        }
        return [];
    }
    e28(title) {
        if (new RegExp('/[\\\/:*?"<>|]/').test(title)) {
            return false;
        }
        if ((new RegExp('/^[\u4e00-\u9fa5]+$/').test(title) && title.length > this.MAX_CN_LENGTH) ||
            (!new RegExp('/^[\u4e00-\u9fa5]+$/').test(title) && title.length > this.MAX_EN_LENGTH)) {
            return false;
        }
        return true;
    }
    f32(callback, root = this.o28, r10) {
        let stack = [];
        let s10 = false;
        stack.unshift(root);
        let t10 = stack.shift();
        while (!s10 && t10) {
            s10 = callback(t10, r10) === true;
            if (!s10) {
                stack.unshift(...t10.children);
                t10 = stack.shift();
            }
        }
    }
    d33(insertIndex, parent) {
        for (let q10 = insertIndex; q10 < parent.children.length; q10++) {
            parent.children[q10].w32 += 1;
        }
    }
    g32(parentNodeId, currentNodeId, n10, isAfter, data) {
        if (this.o28 === null) {
            this.o28 = new b8(v7);
            this.o28.c23 = this.INITIAL_INVALID_VALUE;
        }
        if (this.r28.has(parentNodeId)) {
            let parent = this.r28.get(parentNodeId);
            let o10 = new b8(data);
            if (parent.c23 > this.p28) {
                hilog.error(f7, e7, 'addDragNode: The level of the tree view cannot exceed 50.');
                return false;
            }
            o10.c23 = parent.c23 + 1;
            o10.parentNodeId = parentNodeId;
            o10.currentNodeId = currentNodeId;
            data.parentNodeId = parentNodeId;
            data.currentNodeId = currentNodeId;
            let insertIndex = this.INITIAL_INVALID_VALUE;
            if (parent.children.length) {
                for (let p10 = 0; p10 < parent.children.length; p10++) {
                    if (parent.children[p10].z30() === n10) {
                        insertIndex = p10;
                        break;
                    }
                }
                if (isAfter) {
                    o10.w32 = insertIndex + 1;
                    this.d33(o10.w32, parent);
                    parent.children.splice(insertIndex + 1, 0, o10);
                }
                else {
                    o10.w32 = insertIndex < 0 ? parent.children.length + insertIndex : insertIndex;
                    this.d33(o10.w32, parent);
                    parent.children.splice(insertIndex, 0, o10);
                }
            }
            else {
                o10.w32 = parent.children.length;
                parent.children.push(o10);
            }
            parent.r24().u30 = true;
            parent.r24().v30 = parent.children.length;
            parent.r24().n28 += 1;
            this.t32(parent, true, 1);
            this.r28.set(currentNodeId, o10);
            this.s28.set(currentNodeId, data);
            return true;
        }
        else {
            hilog.error(f7, e7, 'addDragNode: Parent node not found.');
            return false;
        }
    }
}
class b1 {
    constructor(controller) {
        this.fontSize = 1;
        this.controller = null;
        this.controller = controller;
    }
    applyGesture(event) {
        if (this.fontSize >= b1.minFontSize) {
            event.addGesture(new LongPressGestureHandler({ repeat: false, duration: b1.h1 })
                .onAction(() => {
                if (event) {
                    this.controller?.open();
                }
            })
                .onActionEnd(() => {
                this.controller?.close();
            }));
        }
        else {
            event.clearGestures();
        }
    }
}
b1.h1 = 500;
b1.minFontSize = 1.75;
export class a8 extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.__item = new SynchedPropertyNesedObjectPU(params.item, this, 'item');
        this.listNodeDataSource = new z7();
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
            left: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_card_margin_start'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_card_margin_end'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            top: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_margin_vertical'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        };
        this.textInputPadding = {
            left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        };
        this.inputFontSize = resourceManager.getSystemResourceManager().getNumberByName('ohos_id_text_size_body1');
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(params) {
        this.__item.set(params.item);
        if (params.listNodeDataSource !== undefined) {
            this.listNodeDataSource = params.listNodeDataSource;
        }
        if (params.columnWidth !== undefined) {
            this.columnWidth = params.columnWidth;
        }
        if (params.isFocused !== undefined) {
            this.isFocused = params.isFocused;
        }
        if (params.index !== undefined) {
            this.index = params.index;
        }
        if (params.lastIndex !== undefined) {
            this.lastIndex = params.lastIndex;
        }
        if (params.count !== undefined) {
            this.count = params.count;
        }
        if (params.followingSystemFontScale !== undefined) {
            this.followingSystemFontScale = params.followingSystemFontScale;
        }
        if (params.maxAppFontScale !== undefined) {
            this.maxAppFontScale = params.maxAppFontScale;
        }
        if (params.listTreeViewMenu !== undefined) {
            this.listTreeViewMenu = params.listTreeViewMenu;
        }
        if (params.callBackClick !== undefined) {
            this.callBackClick = params.callBackClick;
        }
        if (params.MAX_CN_LENGTH !== undefined) {
            this.MAX_CN_LENGTH = params.MAX_CN_LENGTH;
        }
        if (params.MAX_EN_LENGTH !== undefined) {
            this.MAX_EN_LENGTH = params.MAX_EN_LENGTH;
        }
        if (params.INITIAL_INVALID_VALUE !== undefined) {
            this.INITIAL_INVALID_VALUE = params.INITIAL_INVALID_VALUE;
        }
        if (params.MAX_TOUCH_DOWN_COUNT !== undefined) {
            this.MAX_TOUCH_DOWN_COUNT = params.MAX_TOUCH_DOWN_COUNT;
        }
        if (params.isMultiPress !== undefined) {
            this.isMultiPress = params.isMultiPress;
        }
        if (params.touchDownCount !== undefined) {
            this.touchDownCount = params.touchDownCount;
        }
        if (params.appEventBus !== undefined) {
            this.appEventBus = params.appEventBus;
        }
        if (params.itemPadding !== undefined) {
            this.itemPadding = params.itemPadding;
        }
        if (params.textInputPadding !== undefined) {
            this.textInputPadding = params.textInputPadding;
        }
        if (params.inputFontSize !== undefined) {
            this.inputFontSize = params.inputFontSize;
        }
    }
    updateStateVars(params) {
        this.__item.set(params.item);
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__item.purgeDependencyOnElmtId(rmElmtId);
        this.__columnWidth.purgeDependencyOnElmtId(rmElmtId);
        this.__isFocused.purgeDependencyOnElmtId(rmElmtId);
        this.__index.purgeDependencyOnElmtId(rmElmtId);
        this.__lastIndex.purgeDependencyOnElmtId(rmElmtId);
        this.__count.purgeDependencyOnElmtId(rmElmtId);
        this.__followingSystemFontScale.purgeDependencyOnElmtId(rmElmtId);
        this.__maxAppFontScale.purgeDependencyOnElmtId(rmElmtId);
        this.__treeViewTheme.purgeDependencyOnElmtId(rmElmtId);
        this.__clickButtonFlag.purgeDependencyOnElmtId(rmElmtId);
        this.__accessibilityNodeType.purgeDependencyOnElmtId(rmElmtId);
        this.__isAccessibilityEnabled.purgeDependencyOnElmtId(rmElmtId);
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
    set columnWidth(newValue) {
        this.__columnWidth.set(newValue);
    }
    get isFocused() {
        return this.__isFocused.get();
    }
    set isFocused(newValue) {
        this.__isFocused.set(newValue);
    }
    get index() {
        return this.__index.get();
    }
    set index(newValue) {
        this.__index.set(newValue);
    }
    get lastIndex() {
        return this.__lastIndex.get();
    }
    set lastIndex(newValue) {
        this.__lastIndex.set(newValue);
    }
    get count() {
        return this.__count.get();
    }
    set count(newValue) {
        this.__count.set(newValue);
    }
    get followingSystemFontScale() {
        return this.__followingSystemFontScale.get();
    }
    set followingSystemFontScale(newValue) {
        this.__followingSystemFontScale.set(newValue);
    }
    get maxAppFontScale() {
        return this.__maxAppFontScale.get();
    }
    set maxAppFontScale(newValue) {
        this.__maxAppFontScale.set(newValue);
    }
    get treeViewTheme() {
        return this.__treeViewTheme.get();
    }
    set treeViewTheme(newValue) {
        this.__treeViewTheme.set(newValue);
    }
    get clickButtonFlag() {
        return this.__clickButtonFlag.get();
    }
    set clickButtonFlag(newValue) {
        this.__clickButtonFlag.set(newValue);
    }
    get accessibilityNodeType() {
        return this.__accessibilityNodeType.get();
    }
    set accessibilityNodeType(newValue) {
        this.__accessibilityNodeType.set(newValue);
    }
    get isAccessibilityEnabled() {
        return this.__isAccessibilityEnabled.get();
    }
    set isAccessibilityEnabled(newValue) {
        this.__isAccessibilityEnabled.set(newValue);
    }
    aboutToAppear() {
        if (this.item.n24().x21) {
            this.item.imageSource = this.item.n24().x21?.source;
            this.item.l22 = this.item.n24().x21?.l22;
        }
        let m10 = this.getUIContext();
        this.followingSystemFontScale = m10.isFollowingSystemFontScale();
        this.maxAppFontScale = m10.getMaxFontScale();
    }
    decideFontScale() {
        let k10 = this.getUIContext();
        let l10 = k10.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.followingSystemFontScale) {
            return 1;
        }
        return Math.min(l10, this.maxAppFontScale, j6);
    }
    decideSymbolFontScale(g10) {
        if (!g10 || !this.followingSystemFontScale) {
            return 1;
        }
        let h10 = this.getUIContext();
        let i10 = h10.getHostContext()?.config?.fontSizeScale ?? 1;
        let j10 = Math.min(i10, this.maxAppFontScale, i7);
        return Math.max(j10, j7);
    }
    getInputTextMaxFontSize() {
        let f10 = this.decideFontScale() * this.inputFontSize + 'vp';
        return f10;
    }
    getLeftIconColor() {
        if (this.item.l25()) {
            return { 'id': -1, 'type': 10001, params: ['sys.color.icon_on_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        }
        else if (this.item.v24()) {
            return this.treeViewTheme.j22;
        }
        else {
            return this.treeViewTheme.i22;
        }
    }
    checkInvalidPattern(title) {
        return new RegExp('/[\\\/:*?"<>|]/').test(title);
    }
    checkIsAllCN(title) {
        return new RegExp('/^[\u4e00-\u9fa5]+$/').test(title);
    }
    getAccessibilityReadText(currentNodeId) {
        let u9 = this.listNodeDataSource.r28.get(currentNodeId);
        if (u9 === undefined || currentNodeId === undefined) {
            return '';
        }
        let v9 = this.listNodeDataSource.v31(u9);
        let primaryTitle = v9?.w24()?.primaryTitle === undefined
            ? '' : v9?.w24()?.primaryTitle;
        let secondaryTitle = v9?.w24()?.secondaryTitle === undefined
            ? '' : v9?.w24()?.secondaryTitle;
        let w9 = this.listNodeDataSource.s27(primaryTitle);
        let x9 = this.listNodeDataSource.s27(secondaryTitle);
        let title = `${w9}, ${x9}`;
        let parentId = this.listNodeDataSource.b28(currentNodeId);
        let y9 = [];
        let z9 = 0;
        let a10 = this.listNodeDataSource.x27(parentId);
        let b10 = a10.map(item => item.itemId);
        let c10 = b10.indexOf(currentNodeId) + 1;
        let d10 = this.listNodeDataSource.u31(currentNodeId);
        if (d10 === undefined) {
            return ' ';
        }
        if (this.accessibilityNodeType === t7.PLACE) {
            if (this.listNodeDataSource.b28(currentNodeId) === -1) {
                for (let e10 = 0; e10 < this.listNodeDataSource.q25.length; e10++) {
                    if (this.listNodeDataSource.q25[e10].h24() === -1) {
                        y9.push(this.listNodeDataSource.q25[e10].g24());
                    }
                }
                z9 = y9.indexOf(currentNodeId) + 1;
                return this.listNodeDataSource.getStringByName('treeview_accessibility_place_node_parent', z9);
            }
            else {
                return this.listNodeDataSource.getStringByName('treeview_accessibility_place_node_child', d10, c10);
            }
        }
        else if (this.accessibilityNodeType === t7.LIFT) {
            return title;
        }
        else {
            return title;
        }
    }
    getAccessibilityDescription() {
        if (this.accessibilityNodeType === t7.TEXT) {
            return this.listNodeDataSource.getStringByName('treeview_accessibility_node_desc');
        }
        else {
            return ' ';
        }
    }
    getAccessibilityReadButtonText(t9) {
        if (this.clickButtonFlag === false) {
            return this.item.n24().z21?.x25 === ARROW_RIGHT
                ? this.listNodeDataSource.getStringByName('treeview_accessibility_folded_node')
                : this.listNodeDataSource.getStringByName('treeview_accessibility_expanded_node');
        }
        else {
            return t9 ? this.listNodeDataSource.getStringByName('treeview_accessibility_expand_node')
                : this.listNodeDataSource.getStringByName('treeview_accessibility_fold_node');
        }
    }
    getAccessibilityReadButtonDescription() {
        if (this.clickButtonFlag === false) {
            return ' ';
        }
        else {
            return this.listNodeDataSource.getStringByName('treeview_accessibility_implement_node');
        }
    }
    onTouchNode(event) {
        this.count++;
        if (this.count > 1) {
            this.count--;
            return;
        }
        this.index = this.listNodeDataSource.findIndex(this.item.g24());
        this.listNodeDataSource.g26(this.index);
        let r9 = this.item.g24();
        if (event.type === TouchType.Down) {
            this.item.c24(this.treeViewTheme.f22);
        }
        else if (event.type === TouchType.Up) {
            if (!(typeof this.treeViewTheme.b22 === 'string')) {
                this.item.c24(r6);
            }
            else {
                this.item.c24(this.treeViewTheme.b22);
            }
            if (this.item.n24().x21 !== null) {
                this.item.n24().x21?.d26(r7.SELECTED);
                this.listNodeDataSource.d26(this.index, r7.SELECTED);
                this.item.imageSource = this.item.n24().x21?.source;
                this.item.l22 = this.item.n24().x21?.l22;
            }
            this.item.n24().y21?.e26(true);
            let s9 = { currentNodeId: r9 };
            this.appEventBus.emit(TreeListenType.NODE_CLICK, s9);
            this.listNodeDataSource.t27(this.item.v24()
                ? this.listNodeDataSource.getStringByName('treeview_accessibility_select_node', `${this.getAccessibilityReadText(this.item.g24())}`) : '');
        }
        if (this.listNodeDataSource.f26() !== -1 && this.index !== this.listNodeDataSource.f26()) {
            this.listNodeDataSource.h26(n7.WARNINGS, o7.NONE, false, this.listNodeDataSource.f26());
            this.listNodeDataSource.i26(this.listNodeDataSource.f26(), m7.COMMIT_NODE);
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
        this.index = this.listNodeDataSource.findIndex(this.item.g24());
        this.listNodeDataSource.g26(this.index);
        let p9 = this.item.g24();
        if (!(typeof this.treeViewTheme.b22 === 'string')) {
            this.item.c24(r6);
        }
        else {
            this.item.c24(this.treeViewTheme.b22);
        }
        if (this.item.n24().x21 !== null) {
            this.item.n24().x21?.d26(r7.SELECTED);
            this.listNodeDataSource.d26(this.index, r7.SELECTED);
            this.item.imageSource = this.item.n24().x21?.source;
            this.item.l22 = this.item.n24().x21?.l22;
        }
        this.item.n24().y21?.e26(true);
        let q9 = { currentNodeId: p9 };
        this.appEventBus.emit(TreeListenType.NODE_CLICK, q9);
        this.listNodeDataSource.t27(this.item.v24()
            ? this.listNodeDataSource.getStringByName('treeview_accessibility_select_node', `${this.getAccessibilityReadText(this.item.g24())}`) : '');
        if (this.listNodeDataSource.f26() !== -1 && this.index !== this.listNodeDataSource.f26()) {
            this.listNodeDataSource.h26(n7.WARNINGS, o7.NONE, false, this.listNodeDataSource.f26());
            this.listNodeDataSource.i26(this.listNodeDataSource.f26(), m7.COMMIT_NODE);
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
            customId: `treeView_button${this.item.g24()}`
        });
        accessibility.sendAccessibilityEvent(eventInfo).then(() => {
            setTimeout(() => {
                this.clickButtonFlag = true;
            }, g7);
        });
    }
    popupForShowTitle(text, backgroundColor, fontColor, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.backgroundColor(backgroundColor);
            Row.border({ radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_elements_margin_horizontal_l'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
            Row.padding({
                left: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_elements_margin_horizontal_l'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_elements_margin_horizontal_l'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                top: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_card_margin_middle'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                bottom: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_card_margin_middle'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(text);
            Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Text.fontWeight('regular');
            Text.fontColor(fontColor);
            Text.minFontScale(i6);
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
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.item.l24()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Stack.create();
                        ViewStackProcessor.visualState('focused');
                        Stack.border({
                            radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            width: f6,
                            color: this.treeViewTheme.h22,
                            style: BorderStyle.Solid,
                        });
                        ViewStackProcessor.visualState('normal');
                        Stack.border({
                            radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            width: 0,
                        });
                        ViewStackProcessor.visualState();
                    }, Stack);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                        Column.opacity(this.listNodeDataSource.q31(ObservedObject.GetRawObject(this.item)));
                        Column.onHover((isHover) => {
                            if (isHover) {
                                this.item.c24(this.treeViewTheme.g22);
                            }
                            else {
                                this.item.c24({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                            }
                        });
                        Column.onTouch(this.isAccessibilityEnabled ? undefined : (event) => {
                            this.onTouchNode(event);
                        });
                        Column.backgroundColor((this.item.n24().y21 && this.item.n24().inputText &&
                            this.item.z23()) ? this.item.n24().inputText?.e33 : this.item.d24());
                        Column.border({
                            width: this.item.p24().borderWidth,
                            color: this.item.p24().borderColor,
                            radius: this.item.p24().borderRadius,
                        });
                        Column.height(d6);
                        Column.focusable(true);
                        Column.onMouse((event) => {
                            let o9 = this.listNodeDataSource.findIndex(this.item.g24());
                            if (event.button === MouseButton.Right) {
                                this.listNodeDataSource.g27(Event.MOUSE_BUTTON_RIGHT, this.listNodeDataSource.findIndex(this.item.g24()));
                                this.listTreeViewMenu = this.item.t24();
                                this.listNodeDataSource.g26(o9);
                                clearTimeout(this.item.n24().y21?.l31);
                            }
                            event.stopPropagation();
                        });
                        Column.padding({ top: 0, bottom: 0 });
                        Column.bindPopup(this.item.s23().v22, {
                            builder: { builder: () => {
                                    this.popupForShowTitle.call(this, this.item.s23().y22, this.item.s23().x22, this.item.s23().z22);
                                } },
                            placement: Placement.BottomLeft,
                            placementOnTop: false,
                            popupColor: this.item.s23().x22,
                            autoCancel: true,
                            enableArrow: this.item.s23().w22
                        });
                        Column.onAreaChange((oldValue, newValue) => {
                            let n9 = Number.parseInt(newValue.width.toString());
                            this.columnWidth = n9;
                        });
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Stack.create({ alignContent: Alignment.Bottom });
                        Stack.focusable(true);
                    }, Stack);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Divider.create();
                        Divider.height(this.listNodeDataSource.j32().b30);
                        Divider.color(this.listNodeDataSource.j32().c30);
                        Divider.visibility(this.listNodeDataSource.k32(ObservedObject.GetRawObject(this.item)));
                        Divider.lineCap(LineCapStyle.Round);
                        Divider.margin({ start: LengthMetrics.vp(this.item.c25()) });
                        Divider.focusable(true);
                    }, Divider);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create({});
                        Row.focusable(true);
                        Row.width('100%');
                        Row.height(this.item.j24());
                        Row.padding({ start: LengthMetrics.vp(this.item.i24()) });
                        Row.bindContextMenu({ builder: this.builder.bind(this) }, ResponseType.RightClick);
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.height(d6);
                        Row.layoutWeight(1);
                        Row.focusable(true);
                        Row.accessibilityGroup(true);
                        Row.id(`treeView_node${this.item.g24()}`);
                        Row.accessibilityText(this.getAccessibilityReadText(this.item.g24()));
                        Row.accessibilityDescription(this.getAccessibilityDescription());
                        Row.onClick(this.isAccessibilityEnabled ? () => {
                            this.onClickNode();
                            this.callBackClick();
                        } : undefined);
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.item.n24().x21) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Row.create();
                                    Row.focusable(true);
                                    Row.backgroundColor(q6);
                                    Row.margin({
                                        end: s5(this.item.n24().x21?.t25)
                                    });
                                    Row.height(this.item.n24().x21?.itemHeight * this.decideSymbolFontScale(this.item.l22 !== undefined || Util.f1(this.item.imageSource)));
                                    Row.width(this.item.n24().x21?.itemWidth * this.decideSymbolFontScale(this.item.l22 !== undefined || Util.f1(this.item.imageSource)));
                                }, Row);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    If.create();
                                    if (this.item.l22) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                SymbolGlyph.create();
                                                SymbolGlyph.fontColor([this.getLeftIconColor()]);
                                                SymbolGlyph.attributeModifier.bind(this)(this.item.l22);
                                                SymbolGlyph.fontSize(`${this.item.n24().x21?.itemHeight *
                                                    this.decideSymbolFontScale(true)}vp`);
                                                SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                                SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                                SymbolGlyph.opacity(!this.item.v24() && !this.item.j25() ?
                                                    this.item.n24().x21?.opacity : this.item.n24().x21?.f33);
                                                SymbolGlyph.focusable(this.item.n24().y21 !== null ? false : true);
                                            }, SymbolGlyph);
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                If.create();
                                                if (Util.f1(this.item.imageSource)) {
                                                    this.ifElseBranchUpdateFunction(0, () => {
                                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                            SymbolGlyph.create(this.item.imageSource);
                                                            SymbolGlyph.fontSize(`${this.item.n24().x21?.itemHeight *
                                                                this.decideSymbolFontScale(true)}vp`);
                                                            SymbolGlyph.fontColor([this.getLeftIconColor()]);
                                                            SymbolGlyph.opacity(!this.item.v24() && !this.item.j25() ?
                                                                this.item.n24().x21?.opacity : this.item.n24().x21?.f33);
                                                            SymbolGlyph.focusable(this.item.n24().y21 !== null ? false : true);
                                                        }, SymbolGlyph);
                                                    });
                                                }
                                                else {
                                                    this.ifElseBranchUpdateFunction(1, () => {
                                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                            Image.create(this.item.imageSource);
                                                            Image.objectFit(ImageFit.Contain);
                                                            Image.height(this.item.n24().x21?.itemHeight);
                                                            Image.width(this.item.n24().x21?.itemWidth);
                                                            Image.opacity(!this.item.v24() && !this.item.j25() ?
                                                                this.item.n24().x21?.opacity : this.item.n24().x21?.f33);
                                                            Image.focusable(this.item.n24().y21 !== null ? false : true);
                                                            Image.fillColor(this.getLeftIconColor());
                                                            Image.matchTextDirection((this.item.n24().z21?.x25 === ARROW_RIGHT || this.item.n24().z21?.x25 === l7) ? true : false);
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
                        }
                        else {
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
                        if (this.item.n24().y21 && this.item.y23()) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Text.create(this.item.n24().y21?.title);
                                    Text.minFontScale(i6);
                                    Text.maxFontScale(this.decideFontScale());
                                    Text.maxLines(1);
                                    Text.fontSize(this.item.n24().y21?.size);
                                    Text.fontColor(this.item.v24() ?
                                        this.treeViewTheme.e22 : this.treeViewTheme.c22);
                                    Text.margin({
                                        end: s5(this.item.n24().y21?.t25)
                                    });
                                    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                                    Text.fontWeight(this.item.n24().y21?.weight);
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
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.item.n24().y21 && this.item.n24().inputText &&
                            this.item.z23()) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Row.create();
                                    Row.backgroundColor(this.item.n24().inputText?.backgroundColor);
                                    Row.borderRadius(this.item.n24().inputText?.borderRadius);
                                    Row.margin({
                                        end: s5(this.item.n24()
                                            .inputText?.t25)
                                    });
                                }, Row);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    TextInput.create({ text: this.item.n24().y21?.title });
                                    TextInput.height(this.item.n24().inputText?.itemHeight);
                                    TextInput.fontSize(this.getInputTextMaxFontSize());
                                    TextInput.fontColor(this.item.n24().inputText?.color);
                                    TextInput.borderRadius(this.item.n24().inputText?.borderRadius);
                                    TextInput.backgroundColor(this.item.n24().inputText?.backgroundColor);
                                    TextInput.enterKeyType(EnterKeyType.Done);
                                    TextInput.focusable(true);
                                    TextInput.padding({
                                        start: LengthMetrics.resource(this.textInputPadding.left),
                                        end: LengthMetrics.resource(this.textInputPadding.right),
                                        top: LengthMetrics.resource(this.textInputPadding.top),
                                        bottom: LengthMetrics.resource(this.textInputPadding.bottom),
                                    });
                                    TextInput.onChange((value) => {
                                        let i9 = this.listNodeDataSource.findIndex(this.item.g24());
                                        let j9 = '';
                                        let k9 = false;
                                        let l9 = false;
                                        if (this.checkInvalidPattern(value)) {
                                            for (let m9 = 0; m9 < value.length; m9++) {
                                                if (!this.checkInvalidPattern(value[m9])) {
                                                    j9 += value[m9];
                                                }
                                            }
                                            k9 = true;
                                            this.listNodeDataSource.h26(n7.WARNINGS, o7.INVALID_ERROR, true, i9);
                                        }
                                        else {
                                            j9 = value;
                                            k9 = false;
                                        }
                                        if ((this.checkIsAllCN(j9) && j9.length > this.MAX_CN_LENGTH) ||
                                            (!this.checkIsAllCN(j9) && j9.length > this.MAX_EN_LENGTH)) {
                                            j9 = this.checkIsAllCN(j9) ?
                                                j9.substr(0, this.MAX_CN_LENGTH) : j9.substr(0, this.MAX_EN_LENGTH);
                                            l9 = true;
                                            this.listNodeDataSource.h26(n7.WARNINGS, o7.LENGTH_ERROR, true, i9);
                                        }
                                        else {
                                            l9 = false;
                                        }
                                        if (!l9 && !k9) {
                                            this.listNodeDataSource.n31(i9, j9);
                                        }
                                    });
                                    TextInput.onSubmit((enterKey) => {
                                        let h9 = this.listNodeDataSource.findIndex(this.item.g24());
                                        this.listNodeDataSource.h26(n7.WARNINGS, o7.NONE, false, h9);
                                        this.listNodeDataSource.i26(h9, m7.COMMIT_NODE);
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
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Blank.create();
                    }, Blank);
                    Blank.pop();
                    Row.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.listNodeDataSource.b32(this.item.g24())) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Row.create();
                                    Row.focusable(true);
                                    Row.margin({
                                        start: LengthMetrics.resource(this.listNodeDataSource.l32().margin.left),
                                        end: this.item.n24().z21 ?
                                            LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }) :
                                            LengthMetrics.resource(this.listNodeDataSource.l32().margin.right)
                                    });
                                }, Row);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Text.create(this.listNodeDataSource.a32(this.item.g24()));
                                    Text.minFontScale(i6);
                                    Text.maxFontScale(this.decideFontScale());
                                    Text.fontSize(this.listNodeDataSource.l32().fontSize);
                                    Text.fontColor(this.item.j25() || this.item.l25() ? { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_primary_contrary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : this.treeViewTheme.d22);
                                    Text.fontWeight(this.listNodeDataSource.l32().fontWeight);
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
                    Row.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.item.n24().z21) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                if (!If.canRetake(`treeView_button${this.item.g24()}`)) {
                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                        Row.create();
                                        Row.focusable(true);
                                        Row.justifyContent(FlexAlign.Center);
                                        Row.height(this.item.n24().z21?.itemHeight * this.decideSymbolFontScale(true));
                                        Row.width(this.item.n24().z21?.itemWidth * this.decideSymbolFontScale(true));
                                        Row.onClick(() => {
                                            this.listNodeDataSource.i27(this.listNodeDataSource.findIndex(this.item.g24()));
                                            this.listNodeDataSource.o32(this.item.g24());
                                            setTimeout(() => {
                                                this.accessibilityRefocus();
                                            }, h7);
                                        });
                                        Row.id(`treeView_button${this.item.g24()}`);
                                        Row.accessibilityText(this.getAccessibilityReadButtonText(this.item.n24().z21?.x25 === ARROW_RIGHT));
                                        Row.accessibilityDescription(this.getAccessibilityReadButtonDescription());
                                    }, Row);
                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                        SymbolGlyph.create(this.item.n24().z21?.x25);
                                        SymbolGlyph.fontSize(`${this.item.n24().z21?.itemHeight *
                                            this.decideSymbolFontScale(true)}vp`);
                                        SymbolGlyph.fontColor([this.item.n24().z21?.s30 ?
                                                this.treeViewTheme.k22 : p6]);
                                        SymbolGlyph.opacity(!this.item.j25() ?
                                            this.item.n24().z21?.opacity : this.item.n24().z21?.f33);
                                        SymbolGlyph.focusable(true);
                                    }, SymbolGlyph);
                                    Row.pop();
                                }
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
export class b8 {
    constructor(nodeParam) {
        this.currentNodeId = nodeParam.currentNodeId ?? -1;
        this.parentNodeId = nodeParam.parentNodeId ?? -1;
        this.isFolder = nodeParam.isFolder;
        this.c23 = -1;
        this.w32 = -1;
        this.s24 = { u30: false, v30: 0, n28: 0 };
        this.children = [];
    }
    r24() {
        return this.s24;
    }
    z30() {
        return this.currentNodeId;
    }
    y24() {
        return this.isFolder;
    }
}
class c8 {
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
    set t25(rightMargin) {
        this.rightMargin = rightMargin;
    }
    get t25() {
        return this.rightMargin;
    }
}
export class d8 extends c8 {
    constructor(imageSource, c9, d9, itemWidth, itemHeight, e9, f9, g9) {
        super();
        this.rightMargin = { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_elements_margin_horizontal_m'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.imageSource = imageSource;
        this.g33 = c9;
        this.rightMargin = e9;
        this.w25 = d9;
        this.itemWidth = itemWidth;
        this.itemHeight = itemHeight;
        this.h33 = imageSource;
        this.i33 = c9;
        this.j33 = f9;
        this.k33 = g9;
    }
    get source() {
        return this.imageSource;
    }
    get l22() {
        return this.g33;
    }
    get opacity() {
        return this.w25;
    }
    get f33() {
        return 1;
    }
    get x25() {
        return this.h33;
    }
    get l33() {
        return this.i33;
    }
    get s30() {
        return this.j33;
    }
    get type() {
        return this.k33;
    }
}
class e8 {
    constructor() {
    }
    static getInstance() {
        if (!e8.instance) {
            e8.instance = new e8();
        }
        return e8.instance;
    }
    n33(type) {
        let imageSource;
        switch (type) {
            case s7.ARROW_RIGHT_WHITE:
                imageSource = l7;
                break;
            case s7.ARROW_RIGHT:
                imageSource = ARROW_RIGHT;
                break;
            case s7.ARROW_DOWN_WHITE:
                imageSource = k7;
                break;
            default:
                imageSource = ARROW_DOWN;
        }
        return new d8(imageSource, undefined, { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_alpha_content_tertiary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, u5, v5, { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_paragraph_margin_xs'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, (type === s7.ARROW_RIGHT_WHITE || type === s7.ARROW_DOWN_WHITE) ? false : true, type);
    }
}
class f8 {
    static p23(type) {
        let node = f8.o33.get(type);
        if (node === undefined) {
            node = e8.getInstance().n33(type);
            f8.o33.set(type, node);
        }
        return node;
    }
    static n30(z8, a9, b9) {
        if (b9 === undefined) {
            return undefined;
        }
        let type = b9;
        if (z8 == r7.EDIT ||
            z8 === r7.DRAG_INSERT) {
            if (a9 === q7.COLLAPSE) {
                type = s7.ARROW_RIGHT_WHITE;
            }
            else {
                type = s7.ARROW_DOWN_WHITE;
            }
        }
        else if (z8 === r7.FINISH_EDIT ||
            z8 === r7.FINISH_DRAG_INSERT) {
            if (a9 === q7.COLLAPSE) {
                type = s7.ARROW_RIGHT;
            }
            else {
                type = s7.ARROW_DOWN;
            }
        }
        return f8.p23(type);
    }
    static r30(x8, y8) {
        if (y8 === undefined) {
            return undefined;
        }
        let type;
        if (!y8) {
            if (x8 === q7.COLLAPSE) {
                type = s7.ARROW_RIGHT_WHITE;
            }
            else {
                type = s7.ARROW_DOWN_WHITE;
            }
        }
        else {
            if (x8 === q7.COLLAPSE) {
                type = s7.ARROW_RIGHT;
            }
            else {
                type = s7.ARROW_DOWN;
            }
        }
        return f8.p23(type);
    }
}
f8.o33 = new Map();
export class g8 extends c8 {
    constructor(imageSource, r8, s8, itemWidth, itemHeight, t8, u8, v8, w8) {
        super();
        this.rightMargin = { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_elements_margin_horizontal_m'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.imageSource = imageSource;
        this.g33 = r8;
        this.p33 = imageSource;
        this.q33 = r8;
        if (t8 !== undefined) {
            this.r33 = t8;
        }
        else {
            this.r33 = this.p33;
        }
        this.s33 = u8;
        if (v8 !== undefined) {
            this.t33 = v8;
        }
        else {
            this.t33 = this.p33;
        }
        this.u33 = w8;
        this.w25 = s8;
        this.itemWidth = itemWidth;
        this.itemHeight = itemHeight;
        this.h33 = imageSource;
        this.v33 = ARROW_DOWN;
        this.w33 = ARROW_RIGHT;
        this.j33 = true;
        this.x33 = r7.NORMAL;
    }
    get source() {
        return this.imageSource;
    }
    get l22() {
        return this.g33;
    }
    get v25() {
        return this.p33;
    }
    get u25() {
        return this.q33;
    }
    get h31() {
        return this.r33;
    }
    get z32() {
        return this.s33;
    }
    get i31() {
        return this.t33;
    }
    get a33() {
        return this.u33;
    }
    get opacity() {
        return this.w25;
    }
    get f33() {
        return 1;
    }
    get x25() {
        return this.h33;
    }
    get s30() {
        return this.j33;
    }
    r30(q8) {
        if (q8 === q7.EXPAND) {
            this.h33 = this.v33;
        }
        else if (q8 === q7.COLLAPSE) {
            this.h33 = this.w33;
        }
    }
    m30(o8, p8) {
        if (o8 === r7.EDIT || o8 === r7.DRAG_INSERT) {
            this.v33 = k7;
            this.w33 = l7;
            this.j33 = false;
        }
        else if (o8 === r7.FINISH_EDIT ||
            o8 === r7.FINISH_DRAG_INSERT) {
            this.v33 = ARROW_DOWN;
            this.w33 = ARROW_RIGHT;
            this.j33 = true;
        }
        this.h33 = (p8 === q7.COLLAPSE) ?
            this.w33 : this.v33;
    }
    d26(n8) {
        switch (n8) {
            case r7.NORMAL:
                this.imageSource = this.p33;
                this.g33 = this.q33;
                this.x33 = n8;
                break;
            case r7.SELECTED:
                if (this.x33 !== r7.EDIT) {
                    this.imageSource = this.r33;
                    this.g33 = this.s33;
                    this.x33 = n8;
                }
                break;
            case r7.EDIT:
                this.imageSource = this.t33;
                this.g33 = this.u33;
                this.x33 = n8;
                break;
            case r7.FINISH_EDIT:
                this.imageSource = this.r33;
                this.g33 = this.s33;
                this.x33 = n8;
                break;
            case r7.DRAG_INSERT:
                this.imageSource = this.t33;
                this.g33 = this.u33;
                this.x33 = n8;
                break;
            case r7.FINISH_DRAG_INSERT:
                this.imageSource = this.p33;
                this.g33 = this.q33;
                this.x33 = n8;
                break;
            default:
                break;
        }
    }
}
class h8 extends c8 {
    constructor(m8) {
        super();
        this.treeViewTheme = w7.getInstance();
        this.y33 = m8;
        this.itemWidth = w5;
        this.itemHeight = x5;
        this.rightMargin = { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_paragraph_margin_xs'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.z33 = {
            fontColor: this.treeViewTheme.c22,
            fontSize: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            fontWeight: FontWeight.Normal,
        };
        this.a34 = 0;
    }
    e26(isSelected) {
        if (isSelected) {
            this.z33 = {
                fontColor: this.treeViewTheme.e22,
                fontSize: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                fontWeight: FontWeight.Regular,
            };
        }
        else {
            this.z33 = {
                fontColor: this.treeViewTheme.c22,
                fontSize: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                fontWeight: FontWeight.Normal,
            };
        }
    }
    set title(text) {
        this.y33 = text;
    }
    get title() {
        return this.y33;
    }
    set l31(l8) {
        this.a34 = l8;
    }
    get l31() {
        return this.a34;
    }
    get color() {
        return this.z33.fontColor;
    }
    get size() {
        return this.z33.fontSize;
    }
    get weight() {
        return this.z33.fontWeight;
    }
    o27(k8) {
        if (k8) {
            this.z33 = {
                fontColor: this.treeViewTheme.e22,
                fontSize: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                fontWeight: FontWeight.Regular,
            };
        }
        else {
            this.z33 = {
                fontColor: this.treeViewTheme.c22,
                fontSize: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                fontWeight: FontWeight.Normal,
            };
        }
    }
}
export class i8 extends c8 {
    constructor() {
        super();
        this.status = undefined;
        this.b34 = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.c34 = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_emphasize'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.radius = { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_default_xs'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.treeViewTheme = w7.getInstance();
        this.itemWidth = w5;
        this.itemHeight = y5;
        this.rightMargin = { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_paragraph_margin_xs'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.d34 = {
            fontColor: this.treeViewTheme.c22,
            fontSize: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            fontWeight: FontWeight.Normal,
        };
    }
    get color() {
        return this.d34.fontColor;
    }
    get size() {
        return this.d34.fontSize;
    }
    get weight() {
        return this.d34.fontWeight;
    }
    get borderRadius() {
        return this.radius;
    }
    get backgroundColor() {
        return this.b34;
    }
    get e33() {
        return this.c34;
    }
    get e34() {
        return this.status;
    }
}
function s5(j8) {
    if (!j8) {
        return LengthMetrics.vp(0);
    }
    else if (typeof j8 === 'number') {
        return LengthMetrics.vp(j8);
    }
    else {
        return LengthMetrics.resource(j8);
    }
}

export default {
    TreeController,
    TreeListener,
    TreeListenerManager,
    TreeListenType,
    TreeView,
}