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

var t = (this && this.t) || function (u16, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === 'object' && typeof Reflect.a4 === 'function')
        r = Reflect.a4(u16, target, key, desc);
    else
        for (var v16 = u16.length - 1; v16 >= 0; v16--)
            if (d = u16[v16])
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

const u = 24;
const a1 = 24;
const b1 = 0;
const c1 = 48;
const d1 = 32;
const e1 = 2;
const f1 = 0;
const g1 = 48;
const h1 = 0;
const i1 = 48;
const j1 = 10;
const l1 = 2;
const m1 = 0.4;
const n1 = 1;
const o1 = 1;
const q1 = 2;
const s1 = '1.0vp';
const t1 = '0vp';
const u1 = '2.75vp';
const v1 = '-1.25vp';
const w1 = '1.5vp';
const z1 = '#FFFFFF';
const a2 = '#00000000';
const b2 = '#1A0A59F7';
const c2 = '#00001E';
const d2 = '48';
const e2 = '128vp';
const f2 = '208vp';
const g2 = '80vp';
const h2 = '160vp';
const i2 = '112vp';
const j2 = '192vp';
const l2 = '#00FFFFFF';
const m2 = 100;
const n2 = 12;
const o2 = 8;
const q2 = 'TreeView';
const s2 = 0x3900;
const t2 = 2000;
const u2 = 40000;
const ARROW_DOWN = { 'id': -1, 'type': 40000, params: ['sys.symbol.chevron_down'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const v2 = { 'id': -1, 'type': 40000, params: ['sys.symbol.chevron_down'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const ARROW_RIGHT = { 'id': -1, 'type': 40000, params: ['sys.symbol.chevron_forward'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const w2 = { 'id': -1, 'type': 40000, params: ['sys.symbol.chevron_forward'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
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
var z2;
(function (t16) {
    t16[t16['ADD_NODE'] = 0] = 'ADD_NODE';
    t16[t16['REMOVE_NODE'] = 1] = 'REMOVE_NODE';
    t16[t16['MODIFY_NODE'] = 2] = 'MODIFY_NODE';
    t16[t16['COMMIT_NODE'] = 3] = 'COMMIT_NODE';
})(z2 || (z2 = {}));
var a3;
(function (s16) {
    s16[s16['HINTS'] = 0] = 'HINTS';
    s16[s16['WARNINGS'] = 1] = 'WARNINGS';
})(a3 || (a3 = {}));
var b3;
(function (r16) {
    r16[r16['INVALID_ERROR'] = 0] = 'INVALID_ERROR';
    r16[r16['LENGTH_ERROR'] = 1] = 'LENGTH_ERROR';
    r16[r16['NONE'] = 2] = 'NONE';
})(b3 || (b3 = {}));
var c3;
(function (q16) {
    q16[q16['DOWN_FLAG'] = 0] = 'DOWN_FLAG';
    q16[q16['UP_FLAG'] = 1] = 'UP_FLAG';
    q16[q16['NONE'] = 2] = 'NONE';
})(c3 || (c3 = {}));
export var d3;
(function (p16) {
    p16[p16['EXPAND'] = 0] = 'EXPAND';
    p16[p16['COLLAPSE'] = 1] = 'COLLAPSE';
})(d3 || (d3 = {}));
export var e3;
(function (o16) {
    o16[o16['NORMAL'] = 0] = 'NORMAL';
    o16[o16['SELECTED'] = 1] = 'SELECTED';
    o16[o16['EDIT'] = 2] = 'EDIT';
    o16[o16['FINISH_EDIT'] = 3] = 'FINISH_EDIT';
    o16[o16['DRAG_INSERT'] = 4] = 'DRAG_INSERT';
    o16[o16['FINISH_DRAG_INSERT'] = 5] = 'FINISH_DRAG_INSERT';
})(e3 || (e3 = {}));
var f3;
(function (n16) {
    n16[n16['ARROW_DOWN'] = 0] = 'ARROW_DOWN';
    n16[n16['ARROW_RIGHT'] = 1] = 'ARROW_RIGHT';
    n16[n16['ARROW_DOWN_WHITE'] = 2] = 'ARROW_DOWN_WHITE';
    n16[n16['ARROW_RIGHT_WHITE'] = 3] = 'ARROW_RIGHT_WHITE';
})(f3 || (f3 = {}));
var g3;
(function (m16) {
    m16[m16['TEXT'] = 0] = 'TEXT';
    m16[m16['PLACE'] = 1] = 'PLACE';
    m16[m16['LIFT'] = 2] = 'LIFT';
})(g3 || (g3 = {}));
class Util {
    static b4(l16) {
        if (!Util.c4(l16)) {
            return false;
        }
        let resource = l16;
        return resource.type === u2;
    }
    static c4(resource) {
        if (!resource) {
            return false;
        }
        if (typeof resource === 'string' || typeof resource === 'undefined') {
            return false;
        }
        return true;
    }
}
class h3 {
    constructor() {
    }
    static getInstance() {
        if (!h3.instance) {
            h3.instance = new h3();
        }
        return h3.instance;
    }
    createNode() {
        return {
            d4: undefined,
            inputText: new z3(),
            e4: new y3(''),
            f4: undefined,
            fontColor: undefined,
        };
    }
    g4(nodeParam) {
        let k16 = this.createNode();
        if (nodeParam.icon) {
            k16.d4 = new x3(nodeParam.icon, nodeParam.symbolIconStyle, { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_alpha_content_fourth'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, u, a1, nodeParam.selectedIcon, nodeParam.symbolSelectedIconStyle, nodeParam.editIcon, nodeParam.symbolEditIconStyle);
        }
        if (nodeParam.primaryTitle) {
            k16.e4 = new y3(nodeParam.primaryTitle);
        }
        return k16;
    }
}
let i3 = {
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
class j3 {
    constructor() {
        this.h4 = '#1A0A59F7';
        this.i4 = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.j4 = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.l4 = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary_activated'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.m4 = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_click_effect'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.n4 = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_hover'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.o4 = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_focused_outline'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.q4 = { 'id': -1, 'type': 10001, params: ['sys.color.icon_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.r4 = { 'id': -1, 'type': 10001, params: ['sys.color.icon_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.s4 = { 'id': -1, 'type': 10001, params: ['sys.color.icon_tertiary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    }
    static getInstance() {
        if (!j3.instance) {
            j3.instance = new j3();
        }
        return j3.instance;
    }
}
let l3 = class NodeInfo {
    constructor(node, nodeParam) {
        this.imageSource = '';
        this.t4 = undefined;
        this.borderWidth = { has: e1, u4: f1 };
        this.v4 = false;
        this.w4 = false;
        this.x4 = false;
        this.y4 = false;
        this.z4 = false;
        this.treeViewTheme = j3.getInstance();
        this.fontColor = '';
        this.node = node;
        this.nodeParam = nodeParam;
        this.a5 = h3.getInstance().g4(nodeParam);
        this.b5 = {
            c5: false,
            d5: false,
            e5: undefined,
            f5: '',
            g5: undefined,
        };
        this.h5 = g1;
        this.i5 = node.j5 * n2 + o2;
        this.k5 = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.l5 = (this.node.j5 > 0) ? false : true;
        this.m5 = (this.node.j5 > 0) ? h1 : i1;
        this.n5 = true;
        this.o5 = false;
        this.isSelected = false;
        this.status = {
            normal: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            p5: this.treeViewTheme.n4,
            q5: this.treeViewTheme.m4,
            selected: this.treeViewTheme.h4,
            r5: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_activated'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }
        };
        this.s5 = {
            borderWidth: f1,
            borderColor: this.treeViewTheme.o4,
            borderRadius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }
        };
        this.t5 = node.j5 * n2 + o2;
    }
    u5(j16) {
        if (j16) {
            this.a5.f4 =
                w3.v5(f3.ARROW_RIGHT);
        }
        else {
            this.a5.f4 = undefined;
        }
    }
    w5(color) {
        this.fontColor = color;
    }
    x5() {
        return this.fontColor;
    }
    y5() {
        return this.b5;
    }
    z5(isShow) {
        this.b5.c5 = isShow;
    }
    a6(i16) {
        this.b5.d5 = i16;
    }
    b6(color) {
        this.b5.e5 = color;
    }
    c6(text) {
        this.b5.f5 = text;
    }
    d6(h16) {
        this.b5.g5 = h16;
    }
    e6() {
        return this.n5;
    }
    f6() {
        return this.o5;
    }
    g6(g16) {
        if (g16) {
            this.n5 = false;
            this.o5 = true;
        }
        else {
            this.n5 = true;
            this.o5 = false;
        }
    }
    h6(f16) {
        if (f16) {
            this.a5.f4 =
                w3.v5(f3.ARROW_DOWN);
        }
        else {
            this.a5.f4 = undefined;
        }
    }
    i6(e16) {
        if (e16 === undefined) {
            return;
        }
        this.k5 = e16;
    }
    j6() {
        return this.k5;
    }
    k6(d16) {
        this.m5 = d16;
    }
    l6() {
        return this.m5;
    }
    m6() {
        return this.node.currentNodeId;
    }
    n6() {
        return this.node.parentNodeId;
    }
    o6() {
        return this.i5;
    }
    p6() {
        return this.h5;
    }
    q6(c16) {
        this.l5 = c16;
    }
    r6() {
        return this.l5;
    }
    s6() {
        return this.a5;
    }
    t6() {
        return this.status;
    }
    u6() {
        return this.s5;
    }
    v6(b16) {
        this.s5.borderWidth = b16 ? this.borderWidth.has : this.borderWidth.u4;
    }
    w6() {
        return this.node.x6;
    }
    y6() {
        return this.nodeParam.container;
    }
    z6(isSelected) {
        this.isSelected = isSelected;
    }
    a7() {
        return this.isSelected;
    }
    b7() {
        return this.nodeParam;
    }
    c7() {
        return this.node;
    }
    d7() {
        return this.nodeParam.isFolder;
    }
    e7(a16) {
        this.v4 = a16;
    }
    f7() {
        return this.v4;
    }
    g7(z15) {
        if (z15 === undefined) {
            return;
        }
        this.t5 = z15 * n2 + o2;
    }
    h7() {
        return this.t5;
    }
    i7() {
        return this.node.j5;
    }
    j7(y15) {
        this.w4 = y15;
    }
    k7() {
        return this.w4;
    }
    l7(x15) {
        this.x4 = x15;
    }
    m7() {
        return this.x4;
    }
    n7(w15) {
        this.y4 = w15;
    }
    o7() {
        return this.y4;
    }
    p7(v15) {
        this.z4 = v15;
    }
    q7() {
        return this.z4;
    }
};
l3 = t([
    Observed
], l3);
export { l3 };
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
        this.r7 = [];
        this.s7 = [];
    }
    on(type, callback) {
        if (Array.isArray(type)) {
            for (let u15 = 0, l = type.length; u15 < l; u15++) {
                this.on(type[u15], callback);
            }
        }
        else {
            (this.r7[type] || (this.r7[type] = [])).push(callback);
        }
    }
    once(type, callback) {
        if (Array.isArray(type)) {
            this.off(type, callback);
        }
        else {
            (this.s7[type] || (this.s7[type] = [])).push(callback);
        }
    }
    off(type, callback) {
        if (type === null) {
            this.r7 = [];
        }
        if (Array.isArray(type)) {
            for (let t15 = 0, l = type.length; t15 < l; t15++) {
                this.off(type[t15], callback);
            }
        }
        let q15 = this.r7[type];
        if (!q15) {
            return;
        }
        if (callback === null) {
            this.r7[type] = null;
        }
        let r15 = q15.length;
        while (r15--) {
            let s15 = q15[r15];
            if (s15 === callback) {
                q15.splice(r15, 1);
                break;
            }
        }
    }
    emit(event, l15) {
        if (this.s7[event]) {
            let o15 = Array.from(this.s7[event]);
            if (o15) {
                for (let p15 = 0, l = o15.length; p15 < l; p15++) {
                    try {
                        o15[p15](l15);
                    }
                    catch (e) {
                        throw new Error('once function callbacks error.');
                    }
                }
                this.s7[event] = null;
            }
        }
        else if (this.r7[event]) {
            let m15 = Array.from(this.r7[event]);
            if (m15) {
                for (let n15 = 0, l = m15.length; n15 < l; n15++) {
                    try {
                        m15[n15](l15);
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
TreeListenerManager.t7 = 'app_key_event_bus';
export class TreeView extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.treeController = new TreeController();
        this.u7 = new ObservedPropertyObjectPU([], this, 'nodeList');
        this.listNodeDataSource = new n3();
        this.v7 = new ObservedPropertyObjectPU(null, this, 'item');
        this.w7 = new ObservedPropertySimplePU(0, this, 'touchCount');
        this.x7 = new ObservedPropertySimplePU(0, this, 'dropSelectedIndex');
        this.y7 = new ObservedPropertySimplePU(-1, this, 'viewLastIndex');
        this.z7 = new ObservedPropertySimplePU(false, this, 'followingSystemFontScale');
        this.a8 = new ObservedPropertySimplePU(1, this, 'maxAppFontScale');
        this.b8 = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'listItemBgColor');
        this.c8 = new ObservedPropertyObjectPU([], this, 'allParentNode');
        this.d8 = new ObservedPropertyObjectPU(j3.getInstance(), this, 'treeViewTheme');
        this.addProvidedVar('treeViewTheme', this.d8, false);
        this.e8 = new ObservedPropertySimplePU(true, this, 'clickButtonFlag');
        this.addProvidedVar('clickButtonFlag', this.e8, false);
        this.f8 = new ObservedPropertySimplePU(g3.TEXT, this, 'accessibilityNodeType');
        this.addProvidedVar('accessibilityNodeType', this.f8, false);
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
        this.u7.purgeDependencyOnElmtId(rmElmtId);
        this.v7.purgeDependencyOnElmtId(rmElmtId);
        this.w7.purgeDependencyOnElmtId(rmElmtId);
        this.x7.purgeDependencyOnElmtId(rmElmtId);
        this.y7.purgeDependencyOnElmtId(rmElmtId);
        this.z7.purgeDependencyOnElmtId(rmElmtId);
        this.a8.purgeDependencyOnElmtId(rmElmtId);
        this.b8.purgeDependencyOnElmtId(rmElmtId);
        this.c8.purgeDependencyOnElmtId(rmElmtId);
        this.d8.purgeDependencyOnElmtId(rmElmtId);
        this.e8.purgeDependencyOnElmtId(rmElmtId);
        this.f8.purgeDependencyOnElmtId(rmElmtId);
    }
    aboutToBeDeleted() {
        this.u7.aboutToBeDeleted();
        this.v7.aboutToBeDeleted();
        this.w7.aboutToBeDeleted();
        this.x7.aboutToBeDeleted();
        this.y7.aboutToBeDeleted();
        this.z7.aboutToBeDeleted();
        this.a8.aboutToBeDeleted();
        this.b8.aboutToBeDeleted();
        this.c8.aboutToBeDeleted();
        this.d8.aboutToBeDeleted();
        this.e8.aboutToBeDeleted();
        this.f8.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get nodeList() {
        return this.u7.get();
    }
    set nodeList(newValue) {
        this.u7.set(newValue);
    }
    get item() {
        return this.v7.get();
    }
    set item(newValue) {
        this.v7.set(newValue);
    }
    get touchCount() {
        return this.w7.get();
    }
    set touchCount(newValue) {
        this.w7.set(newValue);
    }
    get dropSelectedIndex() {
        return this.x7.get();
    }
    set dropSelectedIndex(newValue) {
        this.x7.set(newValue);
    }
    get viewLastIndex() {
        return this.y7.get();
    }
    set viewLastIndex(newValue) {
        this.y7.set(newValue);
    }
    get followingSystemFontScale() {
        return this.z7.get();
    }
    set followingSystemFontScale(newValue) {
        this.z7.set(newValue);
    }
    get maxAppFontScale() {
        return this.a8.get();
    }
    set maxAppFontScale(newValue) {
        this.a8.set(newValue);
    }
    get listItemBgColor() {
        return this.b8.get();
    }
    set listItemBgColor(newValue) {
        this.b8.set(newValue);
    }
    get allParentNode() {
        return this.c8.get();
    }
    set allParentNode(newValue) {
        this.c8.set(newValue);
    }
    get treeViewTheme() {
        return this.d8.get();
    }
    set treeViewTheme(newValue) {
        this.d8.set(newValue);
    }
    get clickButtonFlag() {
        return this.e8.get();
    }
    set clickButtonFlag(newValue) {
        this.e8.set(newValue);
    }
    get accessibilityNodeType() {
        return this.f8.get();
    }
    set accessibilityNodeType(newValue) {
        this.f8.set(newValue);
    }
    NullBuilder(parent = null) {
    }
    onWillApplyTheme(theme) {
        this.treeViewTheme.h4 = theme.colors.interactiveSelect;
        this.treeViewTheme.m4 = theme.colors.interactivePressed;
        this.treeViewTheme.n4 = theme.colors.interactiveHover;
        this.treeViewTheme.i4 = theme.colors.fontPrimary;
        this.treeViewTheme.j4 = theme.colors.fontSecondary;
        this.treeViewTheme.l4 = theme.colors.interactiveActive;
        this.treeViewTheme.o4 = theme.colors.interactiveFocus;
        this.treeViewTheme.q4 = theme.colors.iconSecondary;
        this.treeViewTheme.r4 = theme.colors.interactiveActive;
        this.treeViewTheme.s4 = theme.colors.iconPrimary;
        this.treeController.treeViewTheme = this.treeViewTheme;
    }
    aboutToAppear() {
        if (this.treeController !== null) {
            this.listNodeDataSource = this.treeController.g8();
            this.nodeList = this.treeController.g8().h8;
            this.item = this.treeController.g8().h8;
        }
        let k15 = this.getUIContext();
        this.followingSystemFontScale = k15.isFollowingSystemFontScale();
        this.maxAppFontScale = k15.getMaxFontScale();
    }
    decideFontScale() {
        let i15 = this.getUIContext();
        let j15 = i15.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.followingSystemFontScale) {
            return 1;
        }
        return Math.min(j15, this.maxAppFontScale, q1);
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
            Text.minFontScale(o1);
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
            Row.id(`treeView_node_lift${item.m6()}`);
            Row.constraintSize({
                minWidth: this.listNodeDataSource.i8().j8.minWidth,
                maxWidth: this.listNodeDataSource.i8().j8.maxWidth,
            });
            Row.height(this.listNodeDataSource.i8().height);
            Row.backgroundColor(this.listNodeDataSource.i8().backgroundColor);
            Row.padding({
                start: LengthMetrics.resource(this.listNodeDataSource.i8().padding.left),
                end: LengthMetrics.resource(this.listNodeDataSource.i8().padding.right),
            });
            Row.shadow({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                color: c2,
                offsetY: 0,
            });
            Row.borderRadius(this.listNodeDataSource.i8().borderRadius);
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (item.s6().d4) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.backgroundColor(a2);
                        Row.margin({ end: o(item.s6().d4?.k8) });
                        Row.height(item.s6().d4?.itemHeight);
                        Row.width(item.s6().d4?.itemWidth);
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (item.s6().d4?.l8) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.attributeModifier.bind(this)(item.s6().d4?.l8);
                                    SymbolGlyph.fontSize(item.s6().d4?.itemHeight);
                                    SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                    SymbolGlyph.opacity(this.listNodeDataSource.i8().m8);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    If.create();
                                    if (Util.b4(item.s6().d4?.n8)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                SymbolGlyph.create(item.s6().d4?.n8);
                                                SymbolGlyph.fontSize(item.s6().d4?.itemHeight);
                                                SymbolGlyph.opacity(this.listNodeDataSource.i8().m8);
                                            }, SymbolGlyph);
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                Image.create(item.s6().d4?.n8);
                                                Image.objectFit(ImageFit.Contain);
                                                Image.height(item.s6().d4?.itemHeight);
                                                Image.width(item.s6().d4?.itemWidth);
                                                Image.opacity(this.listNodeDataSource.i8().m8);
                                                Image.matchTextDirection((item.s6().f4?.o8 === ARROW_RIGHT ||
                                                    item.s6().f4?.o8 === w2) ? true : false);
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
                minWidth: item.s6().d4 ?
                    this.listNodeDataSource.i8().p8.q8 :
                    this.listNodeDataSource.i8().p8.r8,
                maxWidth: item.s6().d4 ?
                    this.listNodeDataSource.i8().p8.s8 :
                    this.listNodeDataSource.i8().p8.t8,
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (item.s6().e4 && item.e6()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(item.s6().e4?.title);
                        Text.maxLines(1);
                        Text.minFontScale(o1);
                        Text.maxFontScale(this.decideFontScale());
                        Text.fontSize(item.s6().e4?.size);
                        Text.fontColor(this.listNodeDataSource.i8().fontColor);
                        Text.fontWeight(this.listNodeDataSource.i8().fontWeight);
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
        this.setImageSources(this.viewLastIndex, e3.NORMAL);
        this.listNodeDataSource.u8(this.viewLastIndex, e3.NORMAL);
        this.nodeList[this.viewLastIndex].i6({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
        this.nodeList[this.viewLastIndex].fontColor = this.treeViewTheme.i4;
        this.listNodeDataSource.h8[this.viewLastIndex].i6({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
        this.listNodeDataSource.h8[this.viewLastIndex].fontColor = this.treeViewTheme.i4;
        this.listNodeDataSource.h8[this.viewLastIndex].z6(false);
        this.listNodeDataSource.h8[this.viewLastIndex].imageSource =
            this.listNodeDataSource.h8[this.viewLastIndex].s6().d4?.source;
        this.listNodeDataSource.h8[this.viewLastIndex].t4 =
            this.listNodeDataSource.h8[this.viewLastIndex].s6().d4?.t4;
    }
    setImageSources(index, g15) {
        let h15 = this.nodeList[index];
        h15.z6(g15 === e3.SELECTED ||
            g15 === e3.EDIT || g15 === e3.FINISH_EDIT);
        if (h15.s6().e4 !== null && g15 !== e3.DRAG_INSERT &&
            g15 !== e3.FINISH_DRAG_INSERT) {
            h15.s6().e4?.v8(g15 === e3.SELECTED ||
                g15 === e3.FINISH_EDIT);
        }
        if (h15.s6().d4 !== null) {
            h15.s6().d4?.u8(g15);
        }
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            List.create({});
            List.onDragMove((event, extraParams) => {
                if (this.isMultiPress) {
                    hilog.error(s2, q2, 'drag error, a item has been dragged');
                    return;
                }
                let c15 = i1;
                let flag = Math.floor(event.getY() /
                    (c15 / l1)) % l1 ? c3.DOWN_FLAG : c3.UP_FLAG;
                let index = JSON.parse(extraParams).insertIndex;
                let d15 = false;
                if (index >= this.listNodeDataSource.totalCount()) {
                    flag = c3.DOWN_FLAG;
                    index = this.listNodeDataSource.totalCount() - 1;
                    this.listNodeDataSource.getData(index)?.j7(true);
                    d15 = true;
                }
                else {
                    this.listNodeDataSource.getData(index)?.j7(false);
                }
                let e15 = this.listNodeDataSource.getData(index);
                let currentNodeId = e15?.m6();
                if (index !== this.listNodeDataSource.w8() && this.listNodeDataSource.x8()) {
                    let f15 = this.listNodeDataSource.y8(currentNodeId);
                    if (f15) {
                        this.listNodeDataSource.z8(index);
                        if (currentNodeId !== undefined) {
                            this.listNodeDataSource.a9(this.listNodeDataSource.findIndex(currentNodeId));
                        }
                        this.listNodeDataSource.b9(c3.NONE);
                        return;
                    }
                }
                this.listNodeDataSource.c9(index);
                this.listNodeDataSource.d9(flag, index - 1, d15, ObservedObject.GetRawObject(this.allParentNode));
                if (currentNodeId !== undefined && currentNodeId !== this.listNodeDataSource.e9()) {
                    this.listNodeDataSource.f9(this.listNodeDataSource.findIndex(currentNodeId), currentNodeId, index);
                }
            });
            List.onDragEnter((event, extraParams) => {
                if (this.listNodeDataSource.x8()) {
                    this.listNodeDataSource.g9(true);
                    let b15 = m1;
                    this.listNodeDataSource.h9(b15);
                }
            });
            List.onDragLeave((event, extraParams) => {
                this.listNodeDataSource.i9();
                this.listNodeDataSource.j9();
                this.listNodeDataSource.k9();
                let a15 = n1;
                this.listNodeDataSource.h9(a15);
                this.listNodeDataSource.g9(false);
                this.listNodeDataSource.l9();
            });
            List.onDrop((event, extraParams) => {
                this.accessibilityNodeType = g3.PLACE;
                this.listNodeDataSource.k9();
                let n14 = n1;
                this.listNodeDataSource.h9(n14);
                let o14 = JSON.parse(extraParams).insertIndex;
                let p14 = this.dropSelectedIndex;
                if (p14 - 1 > this.listNodeDataSource.totalCount() || p14 === undefined) {
                    hilog.error(s2, q2, 'drag error, currentNodeIndex is not found');
                    this.listNodeDataSource.g9(false);
                    return;
                }
                if (o14 === this.listNodeDataSource.totalCount()) {
                    hilog.info(s2, q2, 'need to insert into the position of the last line');
                    o14 -= 1;
                }
                let q14 = this.listNodeDataSource.getData(o14);
                if (q14 === undefined) {
                    return;
                }
                let r14 = q14.m6();
                if (!this.listNodeDataSource.m9() || !this.listNodeDataSource.x8()) {
                    this.listNodeDataSource.j9();
                    this.listNodeDataSource.n9(false);
                    this.listNodeDataSource.i9();
                    this.listNodeDataSource.o9();
                    this.listNodeDataSource.p9(r14);
                    this.listNodeDataSource.l9();
                    return;
                }
                let s14 = this.listNodeDataSource.q9();
                let t14 = q14.n6();
                let u14 = this.listNodeDataSource.e9();
                let v14 = this.listNodeDataSource.r9();
                let w14 = this.listNodeDataSource.y8(r14);
                if (w14) {
                    this.listNodeDataSource.j9();
                    this.listNodeDataSource.n9(false);
                    this.listNodeDataSource.i9();
                    this.listNodeDataSource.s9(o14);
                    this.listNodeDataSource.o9();
                    this.listNodeDataSource.g9(false);
                    let z14 = this.listNodeDataSource.findIndex(u14);
                    this.listNodeDataSource.t9(z14);
                    this.listNodeDataSource.u9(Event.DRAG, z14);
                    return;
                }
                if (this.listNodeDataSource.v9(u14) === d3.EXPAND) {
                    this.listNodeDataSource.w9(this.listNodeDataSource.findIndex(u14));
                }
                let flag = false;
                if (this.listNodeDataSource.v9(r14) === d3.COLLAPSE) {
                    let currentIndex = this.listNodeDataSource.findIndex(r14);
                    if (this.listNodeDataSource.h8[currentIndex].o7()) {
                        this.listNodeDataSource.w9(currentIndex);
                    }
                    flag = true;
                }
                this.listNodeDataSource.x9();
                if (s14 !== null && u14 !== r14) {
                    this.listNodeDataSource.y9(t14, r14, v14, u14, s14);
                    this.listNodeDataSource.i9();
                }
                else {
                    this.listNodeDataSource.i9();
                    this.listNodeDataSource.z9(u14);
                    this.listNodeDataSource.i9();
                }
                let x14 = this.listNodeDataSource.findIndex(this.listNodeDataSource.a10());
                this.listNodeDataSource.b10(x14);
                this.listNodeDataSource.j9();
                this.listNodeDataSource.o9();
                this.listNodeDataSource.g9(false);
                let y14 = this.listNodeDataSource.findIndex(u14);
                this.listNodeDataSource.t9(y14);
                this.listNodeDataSource.u9(Event.DRAG, y14);
                this.listNodeDataSource.n9(false);
                this.listNodeDataSource.l9();
                this.listNodeDataSource.h8[y14].fontColor = this.treeViewTheme.l4;
                if (this.viewLastIndex !== -1 && p14 !== this.viewLastIndex) {
                    this.listNodeDataSource.h8[this.viewLastIndex].s6().e4?.v8(false);
                    this.listNodeDataSource.h8[this.viewLastIndex].s6().e4?.c10(false);
                }
                if (this.listNodeDataSource.h8[this.viewLastIndex] !== null) {
                    this.listNodeDataSource.h8[this.viewLastIndex].fontColor = this.treeViewTheme.i4;
                }
                this.listNodeDataSource.lastIndex = this.viewLastIndex;
                if (this.listNodeDataSource.h8[this.viewLastIndex]) {
                    if (this.listNodeDataSource.h8[this.viewLastIndex].s6().d4 !== null) {
                        this.listNodeDataSource.h8[this.viewLastIndex].s6().d4?.u8(e3.NORMAL);
                        this.listNodeDataSource.h8[this.viewLastIndex].imageSource =
                            this.listNodeDataSource.h8[this.viewLastIndex].s6().d4?.source;
                        this.listNodeDataSource.h8[this.viewLastIndex].t4 =
                            this.listNodeDataSource.h8[this.viewLastIndex].s6().d4?.t4;
                    }
                }
                if (this.listNodeDataSource.h8[this.viewLastIndex]) {
                    this.listNodeDataSource.h8[this.viewLastIndex].i6({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                }
                this.listNodeDataSource.lastIndex = y14;
                let eventInfo = ({
                    type: 'requestFocusForAccessibility',
                    bundleName: getContext()?.abilityInfo?.bundleName,
                    triggerAction: 'common',
                    customId: `treeView_node${u14}`
                });
                accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                    setTimeout(() => {
                        this.accessibilityNodeType = g3.TEXT;
                    }, t2);
                    console.log(`test123 Succeeded in send event, eventInfo is ${JSON.stringify(eventInfo)}`);
                });
            });
        }, List);
        {
            const __lazyForEachItemGenFunction = _item => {
                const e14 = _item;
                {
                    const itemCreation2 = (elmtId, isInitialRender) => {
                        ListItem.create(() => { }, false);
                        ListItem.width('100%');
                        ListItem.height(e14.l6());
                        ListItem.padding({
                            start: LengthMetrics.resource(this.itemPadding.left),
                            end: LengthMetrics.resource(this.itemPadding.right)
                        });
                        ListItem.align(Alignment.Start);
                        ListItem.onDragStart((event, extraParams) => {
                            this.accessibilityNodeType = g3.LIFT;
                            if (this.listNodeDataSource.m9() || this.listNodeDataSource.x8() || this.isMultiPress) {
                                hilog.error(s2, q2, 'drag error, a item has been dragged');
                                return;
                            }
                            this.dropSelectedIndex = JSON.parse(extraParams).selectedIndex;
                            let f14 = JSON.parse(extraParams).selectedIndex;
                            let g14 = this.listNodeDataSource.getData(f14);
                            let h14 = e14.m6();
                            if (f14 >= this.listNodeDataSource.totalCount() || f14 === undefined) {
                                hilog.error(s2, q2, 'drag error, currentNodeIndex is not found in onDragStart');
                                return;
                            }
                            this.listNodeDataSource.n9(true);
                            this.listNodeDataSource.g9(true);
                            this.listNodeDataSource.d10(g14);
                            this.listNodeDataSource.e10(g14?.m6());
                            this.listNodeDataSource.f10(g14?.n6());
                            let i14 = m1;
                            this.listNodeDataSource.h9(i14);
                            this.listNodeDataSource.s9(f14);
                            if (h14 !== g14?.m6()) {
                                hilog.error(s2, q2, 'drag is too fast, it attribute a fault to OH');
                                this.listNodeDataSource.g9(false);
                                return;
                            }
                            let primaryTitle = g14.b7()?.primaryTitle === undefined ? '' :
                                g14.b7()?.primaryTitle;
                            let secondaryTitle = g14.b7()?.secondaryTitle === undefined ? '' :
                                g14.b7()?.secondaryTitle;
                            let j14 = this.listNodeDataSource.g10(primaryTitle);
                            let k14 = this.listNodeDataSource.g10(secondaryTitle);
                            let title = `${j14}, ${k14}`;
                            this.listNodeDataSource.h10(this.listNodeDataSource.getStringByName('treeview_accessibility_lift_node', title));
                            let l14 = [];
                            for (let m14 = 0; m14 < this.listNodeDataSource.h8.length; m14++) {
                                if (this.listNodeDataSource.h8[m14].n6() === -1) {
                                    l14.push(this.listNodeDataSource.h8[m14].m6());
                                }
                            }
                            this.allParentNode = l14;
                            let eventInfo = ({
                                type: 'requestFocusForAccessibility',
                                bundleName: getContext()?.abilityInfo?.bundleName,
                                triggerAction: 'common',
                                customId: `treeView_node_lift${h14}`
                            });
                            accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                                setTimeout(() => {
                                    this.accessibilityNodeType = g3.TEXT;
                                }, t2);
                            });
                            return { builder: () => {
                                    this.draggingPopup.call(this, g14);
                                } };
                        });
                    };
                    const observedDeepRender = () => {
                        this.observeComponentCreation2(itemCreation2, ListItem);
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            Row.create();
                            Row.onTouch((event) => {
                                this.viewLastIndex = this.listNodeDataSource.i10();
                                let index = this.listNodeDataSource.findIndex(e14.m6());
                                if (event.type === TouchType.Down) {
                                    if (index !== this.viewLastIndex) {
                                        this.clearLastIndexColor();
                                        this.listNodeDataSource.lastIndex = index;
                                        this.listNodeDataSource.t9(index);
                                    }
                                }
                                if (event.type === TouchType.Up) {
                                    this.listNodeDataSource.h8[index].z6(true);
                                    this.listNodeDataSource.u8(index, e3.SELECTED);
                                    if (this.listNodeDataSource.h8[index].s6().d4 !== null) {
                                        this.listNodeDataSource.h8[index].imageSource = this.listNodeDataSource.h8[index].s6().d4?.source;
                                        this.listNodeDataSource.h8[index].t4 = this.listNodeDataSource.h8[index].s6().d4?.t4;
                                    }
                                    if (index !== this.viewLastIndex) {
                                        this.clearLastIndexColor();
                                        this.listNodeDataSource.lastIndex = index;
                                        this.listNodeDataSource.t9(index);
                                    }
                                    this.viewLastIndex = index;
                                }
                                if (this.listNodeDataSource.i10() !== -1 && index !== this.listNodeDataSource.i10()) {
                                    this.listNodeDataSource.j10(a3.WARNINGS, b3.NONE, false, this.listNodeDataSource.i10());
                                    this.listNodeDataSource.k10(this.listNodeDataSource.i10(), z2.COMMIT_NODE);
                                }
                            });
                        }, Row);
                        {
                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                if (isInitialRender) {
                                    let componentCall = new r3(this, {
                                        item: e14,
                                        listNodeDataSource: this.listNodeDataSource,
                                        index: this.listNodeDataSource.findIndex(e14.m6()),
                                        listTreeViewMenu: this.listTreeViewMenu,
                                    }, undefined, elmtId, () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 1187, l10: 13 });
                                    ViewPU.create(componentCall);
                                    let paramsLambda = () => {
                                        return {
                                            item: e14,
                                            listNodeDataSource: this.listNodeDataSource,
                                            index: this.listNodeDataSource.findIndex(e14.m6()),
                                            listTreeViewMenu: this.listTreeViewMenu
                                        };
                                    };
                                    componentCall.paramsGenerator_ = paramsLambda;
                                }
                                else {
                                    this.updateStateVarsOfChildByElmtId(elmtId, {
                                        item: e14
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
        this.m10 = -1;
        this.n10 = [];
        this.listNodeDataSource = new n3();
        this.o10 = true;
        this.treeViewTheme = j3.getInstance();
    }
    g8() {
        return this.listNodeDataSource;
    }
    p10() {
        let d14 = this.listNodeDataSource.q10();
        return this.listNodeDataSource.p10(d14);
    }
    r10() {
        let c14 = this.listNodeDataSource.q10();
        return this.listNodeDataSource.s10(c14);
    }
    removeNode() {
        let a14 = this.listNodeDataSource.q10();
        if (a14 < 0) {
            return;
        }
        let parentNodeId = this.listNodeDataSource.t10(a14);
        let b14 = this.listNodeDataSource.removeNode(a14, parentNodeId);
        this.listNodeDataSource.u10(z2.REMOVE_NODE, parentNodeId, b14);
        this.n10.splice(this.n10.indexOf(a14), 1);
        this.listNodeDataSource.lastIndex = -1;
    }
    modifyNode() {
        let z13 = this.listNodeDataSource.q10();
        this.listNodeDataSource.k10(z13, z2.MODIFY_NODE);
    }
    add(t13) {
        let u13 = this.listNodeDataSource.q10();
        if (u13 === this.listNodeDataSource.m10 || !this.listNodeDataSource.d7(u13)) {
            return;
        }
        let v13 = this.listNodeDataSource.v10(u13);
        this.n10.push(this.n10[this.n10.length - 1] + 1);
        let w13 = this.n10[this.n10.length - 1];
        let x13 = this.listNodeDataSource.addNode(u13, w13, {
            isFolder: v13.isFolder,
            icon: v13.icon,
            symbolIconStyle: v13.symbolIconStyle,
            selectedIcon: v13.selectedIcon,
            symbolSelectedIconStyle: v13.symbolSelectedIconStyle,
            editIcon: v13.editIcon,
            symbolEditIconStyle: v13.symbolEditIconStyle,
            primaryTitle: '新建文件夹',
            container: v13.container,
            secondaryTitle: v13.secondaryTitle,
        }, t13);
        if (!x13) {
            return;
        }
        this.listNodeDataSource.u10(z2.ADD_NODE, u13, [w13]);
        this.listNodeDataSource.j10(a3.WARNINGS, b3.NONE, false, this.listNodeDataSource.i10());
        this.listNodeDataSource.k10(this.listNodeDataSource.i10(), z2.COMMIT_NODE);
        this.listNodeDataSource.h8[this.listNodeDataSource.i10()].w5(this.treeViewTheme.i4);
        let y13 = this.listNodeDataSource.findIndex(w13);
        this.listNodeDataSource.t9(y13);
        this.listNodeDataSource.u9(Event.TOUCH_UP, y13);
    }
    addNode(nodeParam) {
        if (nodeParam === undefined) {
            this.add(this.o10);
            return this;
        }
        else {
            let r13 = false;
            if (nodeParam.primaryTitle !== undefined &&
                !this.listNodeDataSource.w10(nodeParam.primaryTitle.toString())) {
                throw new Error('ListTreeNode[addNode]: ' +
                    'The directory name cannot contain the following characters\ /: *? "< > | or exceeds the maximum length.');
                return this;
            }
            if (nodeParam.primaryTitle === null && nodeParam.icon === null) {
                throw new Error('ListTreeNode[addNode]: ' +
                    'The icon and directory name cannot be empty at the same time.');
                return this;
            }
            if (nodeParam.currentNodeId === this.m10 || nodeParam.currentNodeId === null) {
                throw new Error('ListTreeNode[addNode]: currentNodeId can not be -1 or null.');
                return this;
            }
            if (nodeParam.currentNodeId !== undefined) {
                this.n10.push(nodeParam.currentNodeId);
            }
            if (nodeParam.parentNodeId !== undefined) {
                if (nodeParam.currentNodeId !== undefined) {
                    r13 =
                        this.listNodeDataSource.addNode(nodeParam.parentNodeId, nodeParam.currentNodeId, nodeParam, this.o10);
                }
            }
            if (!r13) {
                return this;
            }
            if (!this.o10 && nodeParam.parentNodeId !== undefined) {
                let s13 = this.n10[this.n10.length - 1];
                this.listNodeDataSource.u10(z2.ADD_NODE, nodeParam.parentNodeId, [s13]);
            }
            return this;
        }
    }
    refreshNode(parentId, parentSubTitle, q13) {
        this.listNodeDataSource.x10(parentId, parentSubTitle, q13);
    }
    buildDone() {
        this.listNodeDataSource.y10();
        this.listNodeDataSource.z10();
        this.listNodeDataSource.a11();
        m(this.n10);
        this.o10 = false;
    }
}
class m3 {
    constructor() {
        this.b11 = [];
    }
    totalCount() {
        return 0;
    }
    getData(index) {
        return undefined;
    }
    registerDataChangeListener(listener) {
        if (this.b11.indexOf(listener) < 0) {
            this.b11.push(listener);
        }
    }
    unregisterDataChangeListener(listener) {
        const pos = this.b11.indexOf(listener);
        if (pos >= 0) {
            this.b11.splice(pos, 1);
        }
    }
    l9() {
        this.b11.forEach(listener => {
            listener.onDataReloaded();
        });
    }
    c11(index) {
        this.b11.forEach(listener => {
            listener.onDataAdd(index);
        });
    }
    s9(index) {
        if (index === undefined) {
            return;
        }
        this.b11.forEach(listener => {
            listener.onDataChange(index);
        });
    }
    d11(index) {
        this.b11.forEach(listener => {
            listener.onDataDelete(index);
        });
    }
    e11(from, to) {
        this.b11.forEach(listener => {
            listener.onDataMove(from, to);
        });
    }
}
function i(n13, count, o13, p13) {
    let taskId = setTimeout(() => {
        p13.forEach((parentNodeId) => {
            j(parentNodeId, o13, n13, count);
        });
        clearTimeout(taskId);
    }, m2);
}
function j(parentNodeId, k13, l13, count) {
    let m13 = parentNodeId;
    while (m13 >= 0) {
        if (k13.has(m13)) {
            let parent = k13.get(m13);
            parent.w6().f11 =
                l13 ? parent.w6().f11 + count : parent.w6().f11 - count;
            m13 = parent.parentNodeId;
        }
        else {
            hilog.error(s2, q2, 'updateParentChildNumHandler: parent node not found');
            break;
        }
    }
}
function m(j13) {
    let taskId = setTimeout(() => {
        j13.sort((a, b) => a - b);
        clearTimeout(taskId);
    }, m2);
}
class n3 extends m3 {
    constructor() {
        super();
        this.m10 = -1;
        this.g11 = new s3(i3);
        this.h11 = 50;
        this.MAX_CN_LENGTH = 254;
        this.MAX_EN_LENGTH = 255;
        this.INITIAL_INVALID_VALUE = -1;
        this.h8 = [];
        this.i11 = [];
        this.j11 = new Map();
        this.k11 = new Map();
        this.lastIndex = -1;
        this.l11 = -1;
        this.n11 = -1;
        this.o11 = -1;
        this.p11 = new Map();
        this.q11 = new Map();
        this.r11 = new Map();
        this.s11 = false;
        this.appEventBus = TreeListenerManager.getInstance().getTreeListener();
        this.t11 = false;
        this.u11 = false;
        this.v11 = this.INITIAL_INVALID_VALUE;
        this.w11 = this.INITIAL_INVALID_VALUE;
        this.x11 = null;
        this.y11 = 1;
        this.z11 = this.INITIAL_INVALID_VALUE;
        this.a12 = this.INITIAL_INVALID_VALUE;
        this.b12 = this.INITIAL_INVALID_VALUE;
        this.c12 = this.INITIAL_INVALID_VALUE;
        this.d12 = this.INITIAL_INVALID_VALUE;
        this.e12 = this.INITIAL_INVALID_VALUE;
        this.f12 = this.INITIAL_INVALID_VALUE;
        this.g12 = this.INITIAL_INVALID_VALUE;
        this.h12 = this.INITIAL_INVALID_VALUE;
        this.i12 = this.INITIAL_INVALID_VALUE;
        this.j12 = this.INITIAL_INVALID_VALUE;
        this.k12 = this.INITIAL_INVALID_VALUE;
        this.l12 = new Map();
        this.flag = c3.NONE;
        this.n12 = this.INITIAL_INVALID_VALUE;
        this.o12 = '';
        this.p12 = '';
        this.q12 = this.INITIAL_INVALID_VALUE;
        this.r12 = this.INITIAL_INVALID_VALUE;
        this.s12 = this.INITIAL_INVALID_VALUE;
        this.treeViewTheme = j3.getInstance();
        this.t12 = [];
        this.u12 = {
            v12: s1,
            w12: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_emphasize'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            xOffset: t1,
            x12: u1,
            y12: v1,
            z12: w1,
        };
        this.a13 = {
            j8: { minWidth: e2, maxWidth: f2 },
            p8: {
                q8: g2,
                s8: h2,
                r8: i2,
                t8: j2,
            },
            padding: { left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } },
            backgroundColor: z1,
            height: d2,
            shadow: {
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                color: c2,
                offsetX: 0,
                offsetY: j1,
            },
            borderRadius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            fontColor: this.treeViewTheme.i4,
            fontSize: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            fontWeight: FontWeight.Regular,
            m8: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_alpha_content_fourth'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }
        };
        this.subTitle = {
            b13: this.treeViewTheme.j4,
            c13: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_primary_contrary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            fontSize: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            fontWeight: FontWeight.Regular,
            margin: { left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } }
        };
        this.g11.j5 = -1;
        this.j11.set(-1, this.g11);
        this.k11.set(-1, i3);
    }
    d13(index) {
        if (index < 0 || index >= this.h8.length) {
            hilog.error(s2, q2, 'check index fail');
            return false;
        }
        return true;
    }
    e13(index, color) {
        if (!this.d13(index)) {
            return;
        }
        this.h8[index].i6(color);
        this.h8[index].v6(false);
    }
    j6(index) {
        return this.h8[index].j6();
    }
    f13(index, i13) {
        if (this.h8[index].r6()) {
            this.h8[index].v6(i13);
        }
    }
    u8(index, g13) {
        if (!this.d13(index)) {
            return;
        }
        let h13 = this.h8[index];
        h13.z6(g13 === e3.SELECTED ||
            g13 === e3.EDIT || g13 === e3.FINISH_EDIT);
        if (h13.s6().e4 !== null && g13 !== e3.DRAG_INSERT &&
            g13 !== e3.FINISH_DRAG_INSERT) {
            h13.s6().e4?.v8(g13 === e3.SELECTED ||
                g13 === e3.FINISH_EDIT);
        }
        if (h13.s6().d4 !== null) {
            h13.s6().d4?.u8(g13);
        }
    }
    g13(index, e13) {
        let f13 = this.h8[index];
        if (f13.s6().f4 !== undefined) {
            f13.s6().f4 = w3.h13(e13, this.p11.get(f13.m6()), f13.s6().f4?.type);
        }
    }
    i13() {
        if (!this.d13(this.lastIndex)) {
            return;
        }
        this.u8(this.lastIndex, e3.NORMAL);
        this.e13(this.lastIndex, this.h8[this.lastIndex].t6().normal);
        this.f13(this.lastIndex, false);
        this.s9(this.q11.get(this.h8[this.lastIndex].m6()));
    }
    j13() {
        let index = 0;
        this.q11.clear();
        this.r11.clear();
        this.i11.splice(0, this.i11.length);
        for (let d13 = 0; d13 < this.h8.length; d13++) {
            this.r11.set(this.h8[d13].m6(), d13);
            if (this.h8[d13].r6()) {
                this.q11.set(this.h8[d13].m6(), index++);
                this.i11.push(this.h8[d13]);
            }
        }
    }
    k13(a13) {
        if (a13 >= this.h8.length) {
            hilog.error(s2, q2, 'changeNodeStatus clickIndex error.');
            return;
        }
        let b13 = a13;
        let c13 = this.h8[a13].m6();
        if (this.p11.get(c13) === d3.EXPAND) {
            this.p11.set(c13, d3.COLLAPSE);
            this.h8[b13].s6().f4 = w3.l13(d3.COLLAPSE, this.h8[b13].s6().f4?.n13);
        }
        else if (this.p11.get(c13) === d3.COLLAPSE) {
            this.p11.set(c13, d3.EXPAND);
            this.h8[b13].s6().f4 = w3.l13(d3.EXPAND, this.h8[b13].s6().f4?.n13);
        }
    }
    o13(r12, s12) {
        if (r12 >= this.h8.length) {
            hilog.error(s2, q2, 'handleExpandAndCollapse clickIndex error.');
            return;
        }
        let t12 = r12;
        let u12 = this.h8[t12].m6();
        if (!this.p11.has(u12)) {
            return;
        }
        let v12 = this.p11.get(u12);
        if (this.h8[t12].w6().p13 && v12 === d3.COLLAPSE) {
            for (let z12 = 0; z12 < this.h8[t12].w6().f11; z12++) {
                if (this.h8[t12 + 1 + z12] === undefined) {
                    return;
                }
                this.h8[t12 + 1 + z12].q6(false);
                this.h8[t12 + 1 + z12].k6(h1);
            }
            this.j13();
            this.l9();
            return;
        }
        let w12 = new Array(this.h8[t12].w6().q13);
        w12[0] = t12 + 1;
        let index = 1;
        while (index < this.h8[t12].w6().q13) {
            w12[index] = w12[index - 1] + this.h8[w12[index - 1]].w6().f11 + 1;
            index++;
        }
        if (v12 === d3.EXPAND) {
            for (let x12 = 0; x12 < w12.length; x12++) {
                if (this.h8[w12[x12]] === undefined) {
                    return;
                }
                this.h8[w12[x12]].q6(true);
                this.h8[w12[x12]].k6(i1);
                let y12 = this.h8[w12[x12]].m6();
                if (this.p11.get(y12) === d3.EXPAND) {
                    this.o13(w12[x12], false);
                }
            }
        }
        w12 = null;
        if (s12) {
            this.j13();
            this.l9();
        }
    }
    a11() {
        i(true, 1, this.j11, this.t12);
    }
    r13(q12) {
        q12.splice(0, q12.length);
        this.q11.clear();
        this.i11.splice(0, this.i11.length);
        this.r11.clear();
        this.l12.clear();
    }
    s13(l12, m12, n12) {
        let index = 0;
        let o12 = 0;
        this.r13(l12);
        try {
            this.t13((node) => {
                if (node.u13() >= 0 && this.k11.has(node.u13())) {
                    let p12 = new l3(node, this.k11.get(node.u13()));
                    p12.u5(node.w6().p13);
                    l12.push(p12);
                    this.r11.set(p12.m6(), o12++);
                    index = this.v13(p12, index);
                }
                return false;
            }, this.g11, m12, n12);
        }
        catch (err) {
            hilog.error(s2, q2, 'traverseSectionNodeDF function callbacks error.');
            this.r13(l12);
        }
    }
    v13(k12, index) {
        if (k12.w6().p13) {
            this.p11.set(k12.m6(), d3.COLLAPSE);
        }
        if (k12.r6()) {
            this.q11.set(k12.m6(), index++);
            this.i11.push(k12);
        }
        if (k12.d7()) {
            if (k12.b7().secondaryTitle !== undefined) {
                this.l12.set(k12.m6(), k12.b7().secondaryTitle);
            }
            else {
                this.l12.set(k12.m6(), '');
            }
        }
        return index;
    }
    z10() {
        let i12 = setTimeout(() => {
            let j12 = [];
            this.s13(j12, 0);
            this.h8.splice(0, this.h8.length);
            this.h8.push(...j12);
            this.h8.forEach((value, index) => {
                this.d11(index);
                this.c11(index);
            });
            clearTimeout(i12);
        }, m2);
    }
    y10() {
        this.s13(this.h8, 0, 1);
    }
    t9(index) {
        this.l11 = index;
    }
    q10() {
        if (!this.d13(this.l11)) {
            return -1;
        }
        return this.h8[this.l11].m6();
    }
    w9(h12) {
        this.k13(h12);
        this.o13(h12, true);
    }
    w13() {
        return this.s11;
    }
    i10() {
        return this.lastIndex;
    }
    findIndex(currentNodeId) {
        let g12 = -1;
        if (this.r11.has(currentNodeId)) {
            g12 = this.r11.get(currentNodeId);
        }
        return g12;
    }
    x13(index) {
        if (!this.d13(index)) {
            return;
        }
        this.u8(index, e3.NORMAL);
        this.e13(index, this.h8[index].t6().normal);
        this.f13(index, false);
        this.s9(this.q11.get(this.h8[index].m6()));
    }
    u9(event, index) {
        if (this.u11) {
            return;
        }
        if (!this.d13(index)) {
            return;
        }
        if (event === Event.TOUCH_DOWN || event === Event.TOUCH_UP || event === Event.MOUSE_BUTTON_RIGHT) {
            if (index !== this.lastIndex) {
                this.i13();
            }
        }
        this.y13(index, event);
    }
    y13(index, event) {
        let e12 = this.q11.get(this.h8[index].m6());
        switch (event) {
            case Event.TOUCH_DOWN:
                this.s11 = true;
                this.e13(index, this.h8[index].t6().q5);
                this.s9(e12);
                break;
            case Event.TOUCH_UP: {
                this.z13(index, e12);
                break;
            }
            case Event.HOVER:
                if (this.j6(index) !== this.h8[index].t6().selected) {
                    this.e13(index, this.h8[index].t6().p5);
                    this.s9(e12);
                }
                break;
            case Event.HOVER_OVER:
                if (this.j6(index) !== this.h8[index].t6().selected) {
                    this.e13(index, this.h8[index].t6().normal);
                    this.s9(e12);
                }
                break;
            case Event.FOCUS:
                this.f13(index, true);
                this.s9(e12);
                break;
            case Event.BLUR:
                this.f13(index, false);
                this.s9(e12);
                break;
            case Event.MOUSE_BUTTON_RIGHT:
                this.lastIndex = index;
                this.a14();
                break;
            case Event.DRAG:
                this.s11 = false;
                let f12 = this.h8[index];
                this.u8(index, e3.SELECTED);
                this.lastIndex = index;
                this.e13(index, f12.t6().selected);
                this.s9(e12);
                break;
            default:
                break;
        }
    }
    z13(index, c12) {
        if (this.t11) {
            this.t11 = false;
        }
        this.s11 = false;
        let d12 = this.h8[index];
        this.u8(index, e3.SELECTED);
        d12.w5(this.treeViewTheme.i4);
        this.lastIndex = index;
        this.e13(index, d12.t6().selected);
        this.s9(c12);
    }
    b14(y11, operation) {
        if (operation === z2.MODIFY_NODE) {
            let a12 = this.h8[this.n11];
            let b12 = {
                currentNodeId: a12?.m6(),
                parentNodeId: a12?.n6(),
            };
            this.appEventBus.emit(TreeListenType.NODE_MODIFY, b12);
        }
        else if (operation === z2.ADD_NODE) {
            let z11 = this.h8[y11];
            if (z11 === undefined) {
                return;
            }
            let icon = (z11.s6().d4 !== undefined) ?
                z11.s6().d4?.source : undefined;
            let selectedIcon = (z11.s6().d4 !== undefined) ?
                z11.s6().d4?.c14 : undefined;
            let editIcon = (z11.s6().d4 !== undefined) ?
                z11.s6().d4?.d14 : undefined;
            let callbackParam = {
                currentNodeId: z11?.m6(),
                parentNodeId: z11?.n6(),
            };
            this.appEventBus.emit(TreeListenType.NODE_ADD, callbackParam);
        }
    }
    a14() {
        if (this.n11 !== -1) {
            this.u8(this.n11, e3.FINISH_EDIT);
            this.g13(this.n11, e3.FINISH_EDIT);
            this.h8[this.n11].p7(false);
            this.h8[this.n11].g6(false);
            this.b14(this.n11, this.e14);
            this.s9(this.n11);
        }
    }
    k10(u11, operation) {
        let index = -1;
        if (u11 === -1) {
            return;
        }
        if (operation === z2.MODIFY_NODE) {
            for (let x11 = 0; x11 < this.h8.length; x11++) {
                if (this.h8[x11]?.m6() === u11) {
                    index = x11;
                    break;
                }
            }
            let w11 = this.h8[index];
            if (w11 === undefined) {
                return;
            }
            w11.p7(true);
            if (w11.s6().e4 === null) {
                return;
            }
            this.e14 = z2.MODIFY_NODE;
            w11.g6(true);
            this.u8(index, e3.EDIT);
            this.g13(index, e3.EDIT);
            this.n11 = index;
            if (w11.s6().inputText) {
                if (w11.s6().f4 !== null) {
                    w11.s6().inputText.rightMargin = { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_paragraph_margin_xs'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                }
                else {
                    w11.s6().inputText.rightMargin = { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_elements_margin_horizontal_m'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                }
            }
            this.s9(this.q11.get(u11));
        }
        index = u11;
        if (operation === z2.COMMIT_NODE) {
            let v11 = this.h8[index];
            if (v11 === undefined) {
                return;
            }
            v11.g6(false);
            v11.p7(false);
            this.u8(index, e3.FINISH_EDIT);
            this.g13(index, e3.FINISH_EDIT);
            this.b14(this.n11, this.e14);
            this.s9(this.q11.get(v11?.m6()));
        }
    }
    j10(q11, r11, isShow, index) {
        if (!this.d13(index)) {
            return;
        }
        let s11 = this.h8[index];
        if (s11 === undefined) {
            return;
        }
        s11.z5(isShow);
        let t11 = this.q11.get(s11.m6());
        if (!isShow) {
            this.s9(t11);
            return;
        }
        if (q11 === a3.HINTS) {
            if (s11.s6().e4 !== null) {
                s11.c6(s11.s6().e4?.title);
            }
            else {
                s11.c6('');
                s11.z5(false);
            }
            s11.a6(false);
            s11.b6({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            s11.d6(this.treeViewTheme.j4);
        }
        else if (q11 === a3.WARNINGS) {
            if (s11.s6().inputText !== null) {
                if (r11 === b3.INVALID_ERROR) {
                    s11.c6('invalid error');
                }
                else if (r11 === b3.LENGTH_ERROR) {
                    s11.c6('length error');
                }
                s11.a6(true);
                s11.b6({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_help_tip_bg'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                s11.d6({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_hint_contrary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            }
        }
        this.s9(t11);
    }
    f14(timeout, index) {
        if (!this.d13(index)) {
            return;
        }
        if (this.h8[index].s6().e4 !== null) {
            this.h8[index].s6().e4.g14 = timeout;
        }
        let p11 = this.q11.get(this.h8[index].m6());
        this.s9(p11);
    }
    h14(index, text) {
        this.n11 = index;
        if (this.h8[index].s6().e4 !== null) {
            this.h8[index].s6().e4.title = text;
        }
    }
    totalCount() {
        return this.q11.size;
    }
    getData(index) {
        if (index < 0 || index >= this.i11.length) {
            return undefined;
        }
        return this.i11[index];
    }
    i14(index, data) {
        if (!this.d13(index)) {
            return;
        }
        this.h8.splice(index, 0, data);
        this.r11.set(data.m6(), index);
        this.j13();
        this.c11(index);
    }
    j14(data) {
        this.h8.push(data);
        this.r11.set(data.m6(), this.h8.length);
        this.j13();
        this.c11(this.h8.length - 1);
    }
    n9(o11) {
        this.t11 = o11;
    }
    x8() {
        return this.t11;
    }
    g9(n11) {
        this.u11 = n11;
    }
    m9() {
        return this.u11;
    }
    d10(m11) {
        if (m11 === undefined) {
            return;
        }
        this.x11 = m11;
    }
    q9() {
        return this.x11;
    }
    f10(l11) {
        if (l11 === undefined) {
            return;
        }
        this.w11 = l11;
    }
    r9() {
        return this.w11;
    }
    e9() {
        return this.v11;
    }
    e10(k11) {
        if (k11 === undefined) {
            return;
        }
        this.v11 = k11;
    }
    h9(j11) {
        this.y11 = j11;
    }
    k14(item) {
        return item.m6() === this.e9() ? this.y11 : 1;
    }
    i8() {
        return this.a13;
    }
    c9(i11) {
        this.z11 = i11;
    }
    w8() {
        return this.z11;
    }
    y8(f11) {
        if (this.x11 === null || f11 === undefined) {
            return false;
        }
        let g11 = this.x11.c7();
        let parentId = g11.currentNodeId;
        let h11 = this.j11.get(f11)?.parentNodeId;
        while (h11 !== undefined && h11 !== -1) {
            if (parentId === h11) {
                return true;
            }
            else {
                h11 = this.j11.get(h11)?.parentNodeId;
            }
        }
        return false;
    }
    z8(e11) {
        this.b12 = e11;
    }
    l14() {
        return this.b12;
    }
    a9(currentIndex) {
        if (this.a12 !== this.INITIAL_INVALID_VALUE && this.q11.has(this.a12)) {
            let index = this.q11.get(this.a12);
            this.h8.forEach((value) => {
                if (value.m6() === this.a12) {
                    value.e7(false);
                    return;
                }
            });
            this.s9(index);
        }
        if ((this.h12 !== this.INITIAL_INVALID_VALUE &&
            this.i12 !== this.h12)) {
            clearTimeout(this.h12);
            if (this.j12 !== this.INITIAL_INVALID_VALUE) {
                this.n14(this.j12);
                let index = this.q11
                    .get(this.h8[this.j12].m6());
                this.s9(index);
            }
            this.i12 = this.h12;
        }
        this.h12 = this.g12;
        this.j12 = currentIndex;
        if ((this.e12 !== this.INITIAL_INVALID_VALUE &&
            this.f12 !== this.e12)) {
            clearTimeout(this.e12);
            this.f12 = this.e12;
        }
        this.e12 = this.d12;
        this.c12 = this.INITIAL_INVALID_VALUE;
    }
    n14(currentIndex) {
        if (!this.d13(currentIndex)) {
            return;
        }
        this.e13(currentIndex, this.h8[currentIndex].t6().normal);
        this.o14(currentIndex, false);
        this.u8(currentIndex, e3.FINISH_DRAG_INSERT);
        this.g13(currentIndex, e3.FINISH_DRAG_INSERT);
        this.h8[currentIndex].n7(false);
    }
    o14(index, d11) {
        if (this.h8[index].s6().e4 && this.h8[index].e6()) {
            this.h8[index].s6().e4?.c10(d11);
        }
    }
    p14(x10) {
        let y10 = [];
        while (x10 !== -1) {
            if (x10 === undefined) {
                return '';
            }
            let z10 = this.t10(x10);
            let a11 = this.j11.get(z10);
            if (a11 === undefined || z10 === undefined) {
                return '';
            }
            let primaryTitle = this.q14(a11).b7()?.primaryTitle === undefined
                ? '' : this.q14(a11).b7().primaryTitle;
            let secondaryTitle = this.q14(a11).b7()?.secondaryTitle === undefined
                ? '' : this.q14(a11).b7().secondaryTitle;
            let b11 = this.g10(primaryTitle);
            let c11 = this.g10(secondaryTitle);
            y10.unshift(`${b11}, ${c11}`);
            x10 = a11.currentNodeId;
        }
        return y10.join(',');
    }
    r14(q10) {
        let r10 = [];
        while (q10 !== -1) {
            if (q10 === undefined) {
                return;
            }
            let s10 = this.t10(q10);
            let t10 = this.findIndex(s10);
            let u10 = this.j11.get(s10);
            if (u10 === undefined || s10 === undefined) {
                return;
            }
            let primaryTitle = this.getData(t10)?.b7()?.primaryTitle === undefined
                ? '' : this.getData(t10)?.b7()?.primaryTitle;
            let secondaryTitle = this.getData(t10)?.b7()?.secondaryTitle === undefined
                ? '' : this.getData(t10)?.b7()?.secondaryTitle;
            let v10 = this.g10(primaryTitle);
            let w10 = this.g10(secondaryTitle);
            r10.unshift(`${v10}, ${w10}`);
            q10 = u10.currentNodeId;
        }
        return r10.join(',');
    }
    s14(j10, k10, l10) {
        this.p14(l10);
        if (k10 === undefined || l10 === undefined) {
            return;
        }
        let parentId = this.t10(l10);
        let m10 = j10.indexOf(l10) + 2;
        let n10 = this.p10(parentId);
        let o10 = n10.map(item => item.itemId);
        let p10 = o10.indexOf(l10) + 2;
        if (parentId === -1 && this.v9(k10) === d3.COLLAPSE ||
            parentId === -1 && this.v9(k10) === undefined) {
            this.h10(this.getStringByName('treeview_accessibility_move_node_parent', m10));
        }
        else if (this.v9(k10) === d3.EXPAND) {
            this.h10(this.getStringByName('treeview_accessibility_move_node_child', this.p14(l10), 1));
        }
        else if (parentId !== -1) {
            this.h10(this.getStringByName('treeview_accessibility_move_node_child', this.p14(l10), p10));
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
    h10(textAnnouncedForAccessibility) {
        let eventInfo = ({
            type: 'announceForAccessibility',
            bundleName: getContext()?.abilityInfo?.bundleName,
            triggerAction: 'common',
            textAnnouncedForAccessibility: textAnnouncedForAccessibility
        });
        accessibility.sendAccessibilityEvent(eventInfo);
    }
    g10(resource) {
        let i10 = '';
        try {
            if (typeof resource === 'string') {
                i10 = resource;
            }
            else {
                i10 = getContext()?.resourceManager?.getStringSync(resource?.id);
            }
        }
        catch (error) {
            let code = error.code;
            let message = error.message;
            hilog.error(0x3900, 'Ace', `treeView getAccessibleTitleText error, code: ${code}, message: ${message}`);
        }
        return i10;
    }
    d9(flag, index, y9, z9) {
        let a10 = (this.b12 !== index || this.flag !== flag) ? true : false;
        this.b12 = index;
        if ((a10 || y9) && this.t11) {
            this.flag = flag;
            let currentNodeId = this.getData(index)?.m6();
            let b10 = this.getData(index)?.i7();
            if (currentNodeId !== undefined) {
                b10 = (this.p11.get(currentNodeId) === d3.EXPAND &&
                    this.flag === c3.DOWN_FLAG) ? (b10 ? b10 + 1 : undefined) : b10;
                if (this.a12 !== this.INITIAL_INVALID_VALUE &&
                    this.q11.has(this.a12)) {
                    let h10 = this.q11.get(this.a12);
                    this.h8.forEach((value) => {
                        if (value.m6() === this.a12) {
                            value.e7(false);
                        }
                    });
                    this.s9(h10);
                }
                let c10 = this.getData(index - 1)?.m6();
                let d10 = this.getData(index + 2)?.m6();
                let e10 = this.getData(index + 1)?.m6();
                let f10 = this.j11.get(e10);
                if (this.flag === c3.DOWN_FLAG && index < this.totalCount() - 1) {
                    this.getData(index)?.e7(false);
                    this.getData(index + 1)?.e7(true);
                    this.getData(index)?.l7(false);
                    this.getData(index + 1)?.g7(b10);
                    this.s9(index);
                    this.s9(index + 1);
                    this.a12 = this.getData(index + 1)?.m6();
                    let g10 = this.j11.get(e10);
                    if (!g10?.x6.p13) {
                        this.s14(z9, e10, e10);
                    }
                    else {
                        this.s14(z9, e10, d10);
                    }
                }
                else if (this.flag === c3.UP_FLAG && index < this.totalCount() - 1) {
                    this.getData(index)?.e7(true);
                    this.getData(index + 1)?.e7(false);
                    this.getData(index)?.l7(false);
                    this.getData(index)?.g7(b10);
                    this.s9(index);
                    this.s9(index + 1);
                    this.a12 = this.getData(index)?.m6();
                    if (f10?.x6.p13 && f10?.parentNodeId !== -1) {
                        this.s14(z9, e10, e10);
                    }
                    else if (f10?.x6.p13 && f10?.parentNodeId === -1) {
                        this.s14(z9, c10, e10);
                    }
                }
                else if (index >= this.totalCount() - 1) {
                    if (this.flag === c3.DOWN_FLAG) {
                        this.getData(index)?.e7(false);
                        this.getData(index)?.l7(true);
                    }
                    else {
                        this.getData(index)?.e7(true);
                        this.getData(index)?.l7(false);
                    }
                    this.getData(index)?.g7(b10);
                    this.s9(index);
                    this.a12 = this.getData(index)?.m6();
                }
            }
        }
    }
    f9(currentIndex, currentNodeId, r9) {
        let s9 = currentIndex !== this.c12 ? true : false;
        let t9 = this.getData(r9)?.k7();
        if (t9) {
            this.c12 = this.INITIAL_INVALID_VALUE;
        }
        else {
            this.c12 = currentIndex;
        }
        if (t9 || s9) {
            let u9 = !t9 && (!this.t11 ||
                (this.p11.get(currentNodeId) === d3.COLLAPSE && this.t11) ||
                (!this.p11.has(currentNodeId) && this.h8[currentIndex].d7()));
            if (u9) {
                this.e13(currentIndex, this.h8[currentIndex].t6().p5);
                this.s9(r9);
                let x9 = this.t11 ? 1000 : 0;
                this.g12 = setTimeout(() => {
                    this.t14(currentIndex);
                }, x9);
            }
            if (t9 || (this.h12 !== this.INITIAL_INVALID_VALUE &&
                this.i12 !== this.h12)) {
                clearTimeout(this.h12);
                if (this.j12 !== this.INITIAL_INVALID_VALUE) {
                    this.n14(this.j12);
                    this.l9();
                }
                this.i12 = this.h12;
            }
            this.h12 = this.g12;
            this.j12 = currentIndex;
            if (!t9 && this.p11.get(currentNodeId) === d3.COLLAPSE) {
                let v9 = this.getData(r9)?.c7().children[0]?.currentNodeId;
                let w9 = 2000;
                this.d12 = setTimeout(() => {
                    this.n14(this.j12);
                    if (v9 !== undefined) {
                        this.u14(currentIndex, v9);
                    }
                }, w9);
            }
            if (t9 || (this.e12 !== this.INITIAL_INVALID_VALUE &&
                this.f12 !== this.e12)) {
                clearTimeout(this.e12);
                this.f12 = this.e12;
            }
            this.e12 = this.d12;
        }
    }
    t14(currentIndex) {
        this.h8.forEach((value) => {
            if (value.m6() === this.a12) {
                value.e7(false);
                value.l7(false);
                return;
            }
        });
        this.e13(currentIndex, this.h8[currentIndex].t6().r5);
        this.h8[currentIndex].n7(true);
        this.o14(currentIndex, true);
        this.u8(currentIndex, e3.DRAG_INSERT);
        this.g13(currentIndex, e3.DRAG_INSERT);
        this.l9();
    }
    u14(currentIndex, q9) {
        this.h8.forEach((value) => {
            if (value.m6() === this.a12) {
                value.e7(false);
                value.l7(false);
            }
        });
        this.h8.forEach((value) => {
            if (this.t11 && value.m6() === q9) {
                value.e7(true);
            }
        });
        this.k13(currentIndex);
        this.o13(currentIndex, true);
        this.a12 = q9;
    }
    i9() {
        if (this.a12 !== this.INITIAL_INVALID_VALUE && this.q11.has(this.a12)) {
            this.h8.forEach((value) => {
                if (value.m6() === this.a12) {
                    value.e7(false);
                    value.l7(false);
                    return;
                }
            });
            let index = this.q11.get(this.a12);
            this.s9(index);
        }
    }
    j9() {
        if (this.h12 !== this.INITIAL_INVALID_VALUE &&
            this.i12 !== this.h12) {
            clearTimeout(this.h12);
            if (this.j12 !== this.INITIAL_INVALID_VALUE) {
                this.n14(this.j12);
            }
        }
    }
    k9() {
        if (this.e12 !== this.INITIAL_INVALID_VALUE &&
            this.f12 !== this.e12) {
            clearTimeout(this.e12);
        }
    }
    v14(currentNodeId) {
        if (this.l12.has(currentNodeId)) {
            if (typeof this.l12.get(currentNodeId) === 'number') {
                return this.l12.get(currentNodeId)?.toString();
            }
            else {
                return this.l12.get(currentNodeId);
            }
        }
        else {
            return '';
        }
    }
    w14(currentNodeId) {
        return this.l12.has(currentNodeId);
    }
    o9() {
        this.j12 = this.INITIAL_INVALID_VALUE;
        this.c12 = this.INITIAL_INVALID_VALUE;
        this.z11 = this.INITIAL_INVALID_VALUE;
        this.v11 = this.INITIAL_INVALID_VALUE;
        this.flag = c3.NONE;
    }
    p9(p9) {
        this.l12.set(this.n12, this.o12);
        this.l12.set(p9, this.p12);
        this.s9(this.q11.get(this.n12));
        this.s9(this.q11.get(p9));
    }
    x10(m9, n9, o9) {
        this.n12 = m9;
        this.o12 = n9;
        this.p12 = o9;
    }
    x14() {
        return this.p12;
    }
    v9(currentNodeId) {
        return this.p11.get(currentNodeId);
    }
    a10() {
        return this.k12;
    }
    x9() {
        this.h8.forEach((value, index) => {
            if (index === this.j12) {
                this.k12 = value.m6();
            }
        });
    }
    z9(l9) {
        this.a12 = l9;
    }
    b10(k9) {
        this.j12 = k9;
    }
    y9(o8, p8, q8, r8, s8) {
        let t8 = [];
        let parentNodeId = o8;
        let currentNodeId = r8;
        let nodeParam = s8.b7();
        let u8 = null;
        let v8 = s8.c7();
        let w8 = false;
        let x8 = this.INITIAL_INVALID_VALUE;
        let y8 = this.INITIAL_INVALID_VALUE;
        let z8 = this.flag === c3.DOWN_FLAG ? true : false;
        y8 = this.y14(q8, r8);
        x8 = this.y14(o8, p8) + 1;
        if (o8 !== q8) {
            x8 = z8 ? x8 + 1 : x8;
        }
        else {
            if (x8 > y8) {
                x8 = z8 ? x8 : x8 - 1;
            }
            else {
                x8 = z8 ? x8 + 1 : x8;
            }
        }
        for (let j9 = 0; j9 < this.h8.length; j9++) {
            if (this.h8[j9].m6() === p8) {
                w8 = this.h8[j9].o7();
                if (this.flag === c3.DOWN_FLAG && this.p11.get(p8) === d3.EXPAND) {
                    parentNodeId = p8;
                    x8 = 0;
                }
                else if (this.flag === c3.UP_FLAG && this.p11.get(p8) ===
                    d3.EXPAND &&
                    this.h8[j9].f7() === false) {
                    parentNodeId = p8;
                    x8 = 0;
                }
                else if (w8) {
                    parentNodeId = p8;
                    x8 = 0;
                }
                break;
            }
        }
        let callbackParam = {
            currentNodeId: currentNodeId,
            parentNodeId: parentNodeId,
            childIndex: x8,
        };
        this.appEventBus.emit(TreeListenType.NODE_MOVE, callbackParam);
        t8.push({ parentId: parentNodeId, z14: currentNodeId, data: nodeParam });
        let callback = (node, h9) => {
            if (node) {
                parentNodeId = node.parentNodeId;
                currentNodeId = node.currentNodeId;
                for (let i9 = 0; i9 < h9.length; i9++) {
                    if (h9[i9].m6() === currentNodeId) {
                        u8 = h9[i9];
                        break;
                    }
                }
                if (u8 === null) {
                    return false;
                }
                let nodeParam = u8.b7();
                if (parentNodeId !== q8) {
                    t8.push({ parentId: parentNodeId, z14: currentNodeId, data: nodeParam });
                }
                return false;
            }
            return false;
        };
        this.a15(callback, v8, this.h8);
        let a9 = this.removeNode(r8, q8);
        if (a9.length === 0) {
            return;
        }
        let b9 = p8;
        let isAfter = z8;
        if (this.p11.get(p8) === d3.EXPAND) {
            isAfter = false;
            this.h8.forEach((value) => {
                if (value.m6() === p8 && value.f7() === false) {
                    if (value.c7().children.length) {
                        b9 = value.c7().children[0].currentNodeId;
                    }
                    else {
                        b9 = this.INITIAL_INVALID_VALUE;
                    }
                }
            });
        }
        else if (!this.p11.get(p8) && w8) {
            this.p11.set(p8, d3.EXPAND);
        }
        let c9 = this.b15(t8[0].parentId, t8[0].z14, b9, isAfter, t8[0].data);
        if (!c9) {
            return;
        }
        for (let f9 = 1; f9 < t8.length; f9++) {
            let g9 = this.addNode(t8[f9].parentId, t8[f9].z14, t8[f9].data, false);
            if (!g9) {
                return;
            }
        }
        for (let e9 = 0; e9 < this.h8.length; e9++) {
            if (this.h8[e9].m6() === q8) {
                if (this.h8[e9].s6().f4 === null) {
                    this.h8[e9].h6(false);
                    this.p11.delete(q8);
                    break;
                }
            }
        }
        let d9 = [...this.h8];
        this.c15(d9);
    }
    c15(k8) {
        let index = 0;
        let l8 = 0;
        this.h8.splice(0, this.h8.length);
        this.q11.clear();
        this.i11.splice(0, this.i11.length);
        this.d15((node) => {
            let currentNodeId = node.currentNodeId;
            if (currentNodeId >= 0) {
                if (this.k11.has(currentNodeId)) {
                    let m8 = new l3(node, this.k11.get(currentNodeId));
                    m8.u5(node.w6().p13);
                    this.h8.push(m8);
                    this.r11.set(m8.m6(), l8++);
                    if (this.p11.get(currentNodeId) === d3.EXPAND) {
                        m8.s6().f4 = w3.l13(d3.EXPAND, m8.s6().f4?.n13);
                    }
                    else if (this.p11.get(currentNodeId) === d3.COLLAPSE) {
                        m8.s6().f4 = w3.l13(d3.COLLAPSE, m8.s6().f4?.n13);
                    }
                    for (let n8 = 0; n8 < k8.length; n8++) {
                        if (k8[n8].m6() === m8.m6()) {
                            m8.q6(k8[n8].r6());
                            m8.k6(k8[n8].l6());
                            if (m8.s6().e4 && m8.e6()) {
                                m8.s6().e4.title = k8[n8].s6().e4?.title;
                            }
                            break;
                        }
                    }
                    if (m8.r6()) {
                        this.q11.set(m8.m6(), index++);
                        this.i11.push(m8);
                    }
                }
            }
            return false;
        });
    }
    e15() {
        return this.u12;
    }
    f15(h8) {
        let i8 = this.q11.get(h8.m6()) - 1;
        if (i8 > this.INITIAL_INVALID_VALUE) {
            let j8 = this.getData(i8);
            return (h8.f7() === true && !h8.o7() && !j8?.o7()) ?
                Visibility.Visible : Visibility.Hidden;
        }
        else {
            return (h8.f7() === true && !h8.o7()) ?
                Visibility.Visible : Visibility.Hidden;
        }
    }
    g15() {
        return this.subTitle;
    }
    d7(g8) {
        if (this.q11.has(g8)) {
            return this.getData(this.q11.get(g8))?.d7();
        }
        return false;
    }
    h15(f8) {
        return f8 ? this.subTitle.c13 : this.treeViewTheme.j4;
    }
    y14(c8, d8) {
        let e8 = this.INITIAL_INVALID_VALUE;
        if (this.j11.has(c8)) {
            let node = this.j11.get(c8);
            if (node.u13() === c8) {
                node.children.forEach((value, index) => {
                    if (value.u13() === d8) {
                        e8 = index;
                        return;
                    }
                });
            }
        }
        return e8;
    }
    i15(b8) {
        this.q12 = b8;
    }
    j15() {
        return this.q12;
    }
    k15(a8) {
        this.r12 = a8;
    }
    l15() {
        return this.r12;
    }
    m15() {
        return this.s12;
    }
    b9(flag) {
        this.flag = flag;
    }
    d15(callback, root = this.g11) {
        let stack = [];
        let y7 = false;
        stack.unshift(root);
        let z7 = stack.shift();
        while (!y7 && z7) {
            y7 = callback(z7) === true;
            if (!y7) {
                stack.unshift(...z7.children);
                z7 = stack.shift();
            }
        }
    }
    t13(callback, root = this.g11, t7, u7) {
        let stack = [];
        let v7 = false;
        let w7 = false;
        stack.unshift(root);
        let x7 = stack.shift();
        while (!v7 && x7) {
            try {
                if (t7 !== undefined && x7.j5 < t7) {
                    w7 = true;
                }
                if (u7 !== undefined && x7.j5 > u7) {
                    w7 = true;
                }
                if (!w7) {
                    v7 = callback(x7);
                }
            }
            catch (err) {
                throw new Error('traverseSectionNodeDF function callbacks error');
            }
            if (!v7) {
                stack.unshift(...x7.children);
                x7 = stack.shift();
                w7 = false;
            }
        }
    }
    n15(r7, s7, count) {
        let parentNodeId = r7.parentNodeId;
        while (parentNodeId >= 0) {
            if (this.j11.has(parentNodeId)) {
                let parent = this.j11.get(parentNodeId);
                parent.w6().f11 =
                    s7 ? parent.w6().f11 + count : parent.w6().f11 - count;
                parentNodeId = parent.parentNodeId;
            }
            else {
                hilog.error(s2, q2, 'updateParentChildNum: parent node not found.');
                break;
            }
        }
    }
    t10(currentNodeId) {
        let current = new s3(i3);
        if (this.j11.has(currentNodeId)) {
            current = this.j11.get(currentNodeId);
        }
        return current.parentNodeId;
    }
    o15(k7, l7) {
        let m7 = [];
        if (k7.length === 0) {
            return;
        }
        let startIndex = undefined;
        for (let o7 = 0; o7 < k7.length; o7++) {
            if (this.q11.has(k7[o7])) {
                let q7 = this.q11.get(k7[o7]);
                m7.push(q7);
            }
            if (startIndex === undefined && this.r11.has(k7[o7])) {
                startIndex = this.r11.get(k7[o7]);
            }
            if (startIndex !== undefined) {
                let p7 = this.h8.splice(startIndex, 1);
                p7 = null;
            }
            if (this.p11.has(k7[o7])) {
                this.p11.delete(k7[o7]);
            }
        }
        m7.forEach((value) => {
            this.d11(value);
            this.s9(value);
        });
        if (l7.s6().f4 === null) {
            if (this.r11.has(l7.m6())) {
                let n7 = this.r11.get(l7.m6());
                this.h8[n7]?.h6(false);
            }
            this.p11.delete(l7.m6());
            this.s9(this.q11.get(l7.m6()));
        }
        let callbackParam = {
            currentNodeId: l7.m6(),
            parentNodeId: l7.n6(),
        };
        this.j13();
        this.appEventBus.emit(TreeListenType.NODE_DELETE, callbackParam);
    }
    p15(h7) {
        let i7 = new l3(new s3(i3), i3);
        if (this.j11.has(h7[0])) {
            let node = this.j11.get(h7[0]);
            i7 = new l3(node, this.k11.get(h7[0]));
            i7.u5(node.w6().p13);
        }
        i7.p7(true);
        let index = 0;
        for (let j7 = 0; j7 < this.h8.length; j7++) {
            if (this.h8[j7].m6() === i7.n6()) {
                index = j7;
                if (this.h8[j7].s6().f4 === null) {
                    this.h8[j7].h6(true);
                    this.s9(index);
                }
                else if (this.p11.get(this.h8[j7].m6()) === d3.COLLAPSE) {
                    this.k13(index);
                }
                this.h8.splice(j7 + 1, 0, i7);
                this.h8[j7 + 1].g6(true);
                this.h8[j7 + 1].q6(true);
                this.h8[j7 + 1].k6(i1);
                this.r11.set(h7[0], j7 + 1);
                this.u8(j7 + 1, e3.EDIT);
                this.e14 = z2.ADD_NODE;
                this.c11(j7 + 1);
                this.b14(j7 + 1, this.e14);
                break;
            }
        }
        this.n11 = index + 1;
        this.t9(index);
        this.lastIndex = index;
        this.p11.set(i7.n6(), d3.EXPAND);
        this.o13(index, true);
    }
    u10(operation, parentNodeId, e7) {
        let f7 = new l3(new s3(i3), i3);
        if (this.j11.has(parentNodeId)) {
            let g7 = this.j11.get(parentNodeId);
            f7 = new l3(g7, this.k11.get(parentNodeId));
            f7.u5(g7.w6().p13);
        }
        if (operation === z2.REMOVE_NODE) {
            this.l12.set(parentNodeId, this.o12);
            this.s9(this.q11.get(parentNodeId));
            this.o15(e7, f7);
        }
        if (operation === z2.ADD_NODE) {
            this.s12 = e7[0];
            this.l12.set(this.q10(), this.o12);
            this.l12.set(e7[0], this.p12);
            this.p15(e7);
        }
    }
    removeNode(currentNodeId, parentNodeId) {
        if (this.j11.has(parentNodeId) && this.j11.has(currentNodeId)) {
            let parent = this.j11.get(parentNodeId);
            let current = this.j11.get(currentNodeId);
            let a7 = [];
            let index = current.q15;
            let b7 = 0;
            if (index < 0) {
                hilog.error(s2, q2, 'node does not exist.');
                return [];
            }
            else {
                b7 = parent.children[index].w6().f11 + 1;
                this.r15(parent.children[index], a7);
                for (let d7 = index; d7 < parent.children.length; d7++) {
                    parent.children[d7].q15 -= 1;
                }
                let node = parent.children.splice(index, 1);
                node = null;
                this.s15(parentNodeId);
            }
            parent.w6().q13 = parent.children.length;
            parent.w6().f11 -= (b7);
            let c7 = [];
            c7.push(parent.parentNodeId);
            i(false, b7, this.j11, c7);
            return a7;
        }
        else {
            hilog.error(s2, q2, 'parent does not exist.');
            return [];
        }
    }
    addNode(parentNodeId, currentNodeId, data, x6) {
        if (this.g11 === null) {
            this.g11 = new s3(i3);
            this.g11.j5 = -1;
            this.j11.set(-1, this.g11);
            this.k11.set(-1, i3);
        }
        if (this.j11.has(parentNodeId)) {
            let parent = this.j11.get(parentNodeId);
            let y6 = new s3(data);
            if (parent.j5 > this.h11) {
                hilog.error(s2, q2, 'ListDataSource[addNode]: The level of the tree view cannot exceed 50.');
                return false;
            }
            y6.j5 = parent.j5 + 1;
            y6.parentNodeId = parentNodeId;
            y6.currentNodeId = currentNodeId;
            y6.q15 = parent.children.length;
            data.parentNodeId = parentNodeId;
            data.currentNodeId = currentNodeId;
            parent.children.push(y6);
            parent.w6().p13 = true;
            parent.w6().q13 = parent.children.length;
            parent.w6().f11 += 1;
            this.s15(parentNodeId);
            if (x6) {
                this.t12.push(parent.parentNodeId);
            }
            else {
                let z6 = [];
                z6.push(parent.parentNodeId);
                i(true, 1, this.j11, z6);
            }
            this.k11.set(currentNodeId, data);
            this.j11.set(currentNodeId, y6);
            return true;
        }
        else {
            hilog.error(s2, q2, 'ListDataSource[addNode]: Parent node not found.');
            return false;
        }
    }
    s15(parentNodeId) {
        let parent = this.j11.get(parentNodeId);
        let w6 = this.r11.get(parentNodeId);
        if (parent.children.length > 0) {
            if (this.r11.has(parentNodeId)) {
                this.h8[w6]?.u5(true);
            }
        }
        else {
            this.h8[w6]?.u5(false);
        }
    }
    r15(t6, u6) {
        let v6 = [];
        let callback = (node) => {
            v6.push(node);
            return false;
        };
        this.d15(callback, t6);
        v6.forEach((value) => {
            u6.push(value.u13());
            this.j11.delete(value.u13());
            this.k11.delete(value.u13());
            value = new s3(i3);
        });
    }
    q14(s6) {
        if (s6?.currentNodeId === undefined) {
            hilog.error(s2, q2, 'getNodeInfoByNodeItem: currentId is undefined');
            return new l3(new s3(i3), i3);
        }
        if (!this.r11.has(s6.currentNodeId)) {
            hilog.error(s2, q2, 'getNodeInfoByNodeItem: not has nodeItem.');
            return new l3(new s3(i3), i3);
        }
        let index = this.r11.get(s6.currentNodeId);
        return this.h8[index];
    }
    v10(o6) {
        let parent = new s3(i3);
        if (this.j11.has(o6)) {
            parent = this.j11.get(o6);
        }
        let p6 = i3;
        if (parent) {
            let q6 = this.q14(parent);
            if (parent.children.length === 0) {
                if (q6.s6().d4 !== undefined) {
                    p6.icon = q6.s6().d4?.n8;
                    p6.symbolIconStyle = q6.s6().d4?.l8;
                    p6.selectedIcon = q6.s6().d4?.c14;
                    p6.symbolSelectedIconStyle = q6.s6().d4?.t15;
                    p6.editIcon = q6.s6().d4?.d14;
                    p6.symbolEditIconStyle = q6.s6().d4?.u15;
                    p6.container = q6.y6();
                }
                else {
                    p6.icon = undefined;
                    p6.symbolIconStyle = undefined;
                    p6.selectedIcon = undefined;
                    p6.symbolSelectedIconStyle = undefined;
                    p6.editIcon = undefined;
                    p6.symbolEditIconStyle = undefined;
                    p6.container = q6.y6();
                }
            }
            else if (parent.children.length > 0) {
                let r6 = this.q14(parent.children[0]);
                if (q6.s6().d4 !== null) {
                    p6.icon = (r6.s6().d4 !== undefined) ?
                        r6.s6().d4?.n8 : undefined;
                    p6.symbolIconStyle = (r6.s6().d4 !== undefined) ?
                        r6.s6().d4?.l8 : undefined;
                    p6.selectedIcon = (r6.s6().d4 !== undefined) ?
                        r6.s6().d4?.c14 : undefined;
                    p6.symbolSelectedIconStyle = (r6.s6().d4 !== undefined) ?
                        r6.s6().d4?.t15 : undefined;
                    p6.editIcon = (r6.s6().d4 !== undefined) ?
                        r6.s6().d4?.d14 : undefined;
                    p6.symbolEditIconStyle = (r6.s6().d4 !== undefined) ?
                        r6.s6().d4?.u15 : undefined;
                    p6.container = r6.y6();
                }
                else {
                    p6.icon = undefined;
                    p6.symbolIconStyle = undefined;
                    p6.selectedIcon = undefined;
                    p6.symbolSelectedIconStyle = undefined;
                    p6.editIcon = undefined;
                    p6.symbolEditIconStyle = undefined;
                    p6.container = r6.y6();
                }
            }
        }
        return p6;
    }
    s10(k6) {
        let parent = new s3(i3);
        if (this.j11.has(k6)) {
            parent = this.j11.get(k6);
        }
        if (parent) {
            if (parent.children.length === 0) {
                return [];
            }
            else if (parent.children.length > 0) {
                let l6 = new Array(parent.children.length);
                for (let n6 = 0; n6 < l6.length; n6++) {
                    l6[n6] = 0;
                }
                for (let m6 = 0; m6 < parent.children.length && m6 < l6.length; m6++) {
                    l6[m6] = parent.children[m6].currentNodeId;
                }
                return l6;
            }
        }
        return [];
    }
    p10(f6) {
        let parent = new s3(i3);
        if (this.j11.has(f6)) {
            parent = this.j11.get(f6);
        }
        if (parent) {
            if (parent.children.length === 0) {
                return [];
            }
            else if (parent.children.length > 0) {
                let g6 = new Array(parent.children.length);
                for (let j6 = 0; j6 < g6.length; j6++) {
                    g6[j6] = {};
                }
                for (let h6 = 0; h6 < parent.children.length && h6 < g6.length; h6++) {
                    g6[h6].itemId = parent.children[h6].currentNodeId;
                    let i6 = this.q14(parent.children[h6]);
                    if (i6.s6().d4) {
                        g6[h6].v15 = i6.s6().d4?.source;
                    }
                    if (i6.s6().e4) {
                        g6[h6].w15 = i6.s6().e4?.title;
                    }
                    g6[h6].isFolder = i6.d7();
                }
                return g6;
            }
        }
        return [];
    }
    w10(title) {
        if (new RegExp('/[\\\/:*?"<>|]/').test(title)) {
            return false;
        }
        if ((new RegExp('/^[\u4e00-\u9fa5]+$/').test(title) && title.length > this.MAX_CN_LENGTH) ||
            (!new RegExp('/^[\u4e00-\u9fa5]+$/').test(title) && title.length > this.MAX_EN_LENGTH)) {
            return false;
        }
        return true;
    }
    a15(callback, root = this.g11, c6) {
        let stack = [];
        let d6 = false;
        stack.unshift(root);
        let e6 = stack.shift();
        while (!d6 && e6) {
            d6 = callback(e6, c6) === true;
            if (!d6) {
                stack.unshift(...e6.children);
                e6 = stack.shift();
            }
        }
    }
    x15(insertIndex, parent) {
        for (let b6 = insertIndex; b6 < parent.children.length; b6++) {
            parent.children[b6].q15 += 1;
        }
    }
    b15(parentNodeId, currentNodeId, y5, isAfter, data) {
        if (this.g11 === null) {
            this.g11 = new s3(i3);
            this.g11.j5 = this.INITIAL_INVALID_VALUE;
        }
        if (this.j11.has(parentNodeId)) {
            let parent = this.j11.get(parentNodeId);
            let z5 = new s3(data);
            if (parent.j5 > this.h11) {
                hilog.error(s2, q2, 'addDragNode: The level of the tree view cannot exceed 50.');
                return false;
            }
            z5.j5 = parent.j5 + 1;
            z5.parentNodeId = parentNodeId;
            z5.currentNodeId = currentNodeId;
            data.parentNodeId = parentNodeId;
            data.currentNodeId = currentNodeId;
            let insertIndex = this.INITIAL_INVALID_VALUE;
            if (parent.children.length) {
                for (let a6 = 0; a6 < parent.children.length; a6++) {
                    if (parent.children[a6].u13() === y5) {
                        insertIndex = a6;
                        break;
                    }
                }
                if (isAfter) {
                    z5.q15 = insertIndex + 1;
                    this.x15(z5.q15, parent);
                    parent.children.splice(insertIndex + 1, 0, z5);
                }
                else {
                    z5.q15 = insertIndex < 0 ? parent.children.length + insertIndex : insertIndex;
                    this.x15(z5.q15, parent);
                    parent.children.splice(insertIndex, 0, z5);
                }
            }
            else {
                z5.q15 = parent.children.length;
                parent.children.push(z5);
            }
            parent.w6().p13 = true;
            parent.w6().q13 = parent.children.length;
            parent.w6().f11 += 1;
            this.n15(parent, true, 1);
            this.j11.set(currentNodeId, z5);
            this.k11.set(currentNodeId, data);
            return true;
        }
        else {
            hilog.error(s2, q2, 'addDragNode: Parent node not found.');
            return false;
        }
    }
}
class q3 {
    constructor(controller) {
        this.fontSize = 1;
        this.controller = null;
        this.controller = controller;
    }
    applyGesture(event) {
        if (this.fontSize >= q3.minFontSize) {
            event.addGesture(new LongPressGestureHandler({ repeat: false, duration: q3.y15 })
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
q3.y15 = 500;
q3.minFontSize = 1.75;
export class r3 extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.v7 = new SynchedPropertyNesedObjectPU(params.item, this, 'item');
        this.listNodeDataSource = new n3();
        this.z15 = new ObservedPropertySimplePU(0, this, 'columnWidth');
        this.a16 = new ObservedPropertySimplePU(false, this, 'isFocused');
        this.b16 = new ObservedPropertySimplePU(-1, this, 'index');
        this.c16 = new ObservedPropertySimplePU(-1, this, 'lastIndex');
        this.d16 = new ObservedPropertySimplePU(0, this, 'count');
        this.z7 = new ObservedPropertySimplePU(false, this, 'followingSystemFontScale');
        this.a8 = new ObservedPropertySimplePU(1, this, 'maxAppFontScale');
        this.d8 = this.initializeConsume('treeViewTheme', 'treeViewTheme');
        this.e8 = this.initializeConsume('clickButtonFlag', 'clickButtonFlag');
        this.f8 = this.initializeConsume('accessibilityNodeType', 'accessibilityNodeType');
        this.listTreeViewMenu = undefined;
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
        this.v7.set(params.item);
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
        this.v7.set(params.item);
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.v7.purgeDependencyOnElmtId(rmElmtId);
        this.z15.purgeDependencyOnElmtId(rmElmtId);
        this.a16.purgeDependencyOnElmtId(rmElmtId);
        this.b16.purgeDependencyOnElmtId(rmElmtId);
        this.c16.purgeDependencyOnElmtId(rmElmtId);
        this.d16.purgeDependencyOnElmtId(rmElmtId);
        this.z7.purgeDependencyOnElmtId(rmElmtId);
        this.a8.purgeDependencyOnElmtId(rmElmtId);
        this.d8.purgeDependencyOnElmtId(rmElmtId);
        this.e8.purgeDependencyOnElmtId(rmElmtId);
        this.f8.purgeDependencyOnElmtId(rmElmtId);
    }
    aboutToBeDeleted() {
        this.v7.aboutToBeDeleted();
        this.z15.aboutToBeDeleted();
        this.a16.aboutToBeDeleted();
        this.b16.aboutToBeDeleted();
        this.c16.aboutToBeDeleted();
        this.d16.aboutToBeDeleted();
        this.z7.aboutToBeDeleted();
        this.a8.aboutToBeDeleted();
        this.d8.aboutToBeDeleted();
        this.e8.aboutToBeDeleted();
        this.f8.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get item() {
        return this.v7.get();
    }
    get columnWidth() {
        return this.z15.get();
    }
    set columnWidth(newValue) {
        this.z15.set(newValue);
    }
    get isFocused() {
        return this.a16.get();
    }
    set isFocused(newValue) {
        this.a16.set(newValue);
    }
    get index() {
        return this.b16.get();
    }
    set index(newValue) {
        this.b16.set(newValue);
    }
    get lastIndex() {
        return this.c16.get();
    }
    set lastIndex(newValue) {
        this.c16.set(newValue);
    }
    get count() {
        return this.d16.get();
    }
    set count(newValue) {
        this.d16.set(newValue);
    }
    get followingSystemFontScale() {
        return this.z7.get();
    }
    set followingSystemFontScale(newValue) {
        this.z7.set(newValue);
    }
    get maxAppFontScale() {
        return this.a8.get();
    }
    set maxAppFontScale(newValue) {
        this.a8.set(newValue);
    }
    get treeViewTheme() {
        return this.d8.get();
    }
    set treeViewTheme(newValue) {
        this.d8.set(newValue);
    }
    get clickButtonFlag() {
        return this.e8.get();
    }
    set clickButtonFlag(newValue) {
        this.e8.set(newValue);
    }
    get accessibilityNodeType() {
        return this.f8.get();
    }
    set accessibilityNodeType(newValue) {
        this.f8.set(newValue);
    }
    aboutToAppear() {
        if (this.item.s6().d4) {
            this.item.imageSource = this.item.s6().d4?.source;
            this.item.t4 = this.item.s6().d4?.t4;
        }
        let x5 = this.getUIContext();
        this.followingSystemFontScale = x5.isFollowingSystemFontScale();
        this.maxAppFontScale = x5.getMaxFontScale();
    }
    decideFontScale() {
        let v5 = this.getUIContext();
        let w5 = v5.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.followingSystemFontScale) {
            return 1;
        }
        return Math.min(w5, this.maxAppFontScale, q1);
    }
    getInputTextMaxFontSize() {
        let u5 = this.decideFontScale() * this.inputFontSize + 'vp';
        return u5;
    }
    getLeftIconColor() {
        if (this.item.q7()) {
            return { 'id': -1, 'type': 10001, params: ['sys.color.icon_on_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        }
        else if (this.item.a7()) {
            return this.treeViewTheme.r4;
        }
        else {
            return this.treeViewTheme.q4;
        }
    }
    checkInvalidPattern(title) {
        return new RegExp('/[\\\/:*?"<>|]/').test(title);
    }
    checkIsAllCN(title) {
        return new RegExp('/^[\u4e00-\u9fa5]+$/').test(title);
    }
    getAccessibilityReadText(currentNodeId) {
        let j5 = this.listNodeDataSource.j11.get(currentNodeId);
        if (j5 === undefined || currentNodeId === undefined) {
            return '';
        }
        let k5 = this.listNodeDataSource.q14(j5);
        let primaryTitle = k5?.b7()?.primaryTitle === undefined
            ? '' : k5?.b7()?.primaryTitle;
        let secondaryTitle = k5?.b7()?.secondaryTitle === undefined
            ? '' : k5?.b7()?.secondaryTitle;
        let l5 = this.listNodeDataSource.g10(primaryTitle);
        let m5 = this.listNodeDataSource.g10(secondaryTitle);
        let title = `${l5}, ${m5}`;
        let parentId = this.listNodeDataSource.t10(currentNodeId);
        let n5 = [];
        let o5 = 0;
        let p5 = this.listNodeDataSource.p10(parentId);
        let q5 = p5.map(item => item.itemId);
        let r5 = q5.indexOf(currentNodeId) + 1;
        let s5 = this.listNodeDataSource.p14(currentNodeId);
        if (s5 === undefined) {
            return '';
        }
        if (this.accessibilityNodeType === g3.PLACE) {
            if (this.listNodeDataSource.t10(currentNodeId) === -1) {
                for (let t5 = 0; t5 < this.listNodeDataSource.h8.length; t5++) {
                    if (this.listNodeDataSource.h8[t5].n6() === -1) {
                        n5.push(this.listNodeDataSource.h8[t5].m6());
                    }
                }
                o5 = n5.indexOf(currentNodeId) + 1;
                return this.listNodeDataSource.getStringByName('treeview_accessibility_place_node_parent', o5);
            }
            else {
                return this.listNodeDataSource.getStringByName('treeview_accessibility_place_node_child', s5, r5);
            }
        }
        else if (this.accessibilityNodeType === g3.LIFT) {
            return title;
        }
        else {
            return title;
        }
    }
    getAccessibilityDescription() {
        if (this.accessibilityNodeType === g3.TEXT) {
            return this.listNodeDataSource.getStringByName('treeview_accessibility_node_desc');
        }
        else {
            return '';
        }
    }
    getAccessibilityReadButtonText(i5) {
        if (this.clickButtonFlag === false) {
            return this.item.s6().f4?.o8 === ARROW_RIGHT
                ? this.listNodeDataSource.getStringByName('treeview_accessibility_folded_node')
                : this.listNodeDataSource.getStringByName('treeview_accessibility_expanded_node');
        }
        else {
            return i5 ? this.listNodeDataSource.getStringByName('treeview_accessibility_expand_node')
                : this.listNodeDataSource.getStringByName('treeview_accessibility_fold_node');
        }
    }
    getAccessibilityReadButtonDescription() {
        if (this.clickButtonFlag === false) {
            return '';
        }
        else {
            return this.listNodeDataSource.getStringByName('treeview_accessibility_implement_node');
        }
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
            Text.minFontScale(o1);
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
            if (this.item.r6()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Stack.create();
                        ViewStackProcessor.visualState('normal');
                        Stack.border({
                            radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            width: 0,
                        });
                        ViewStackProcessor.visualState('focused');
                        Stack.border({
                            radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            width: l1,
                            color: this.treeViewTheme.o4,
                            style: BorderStyle.Solid,
                        });
                        ViewStackProcessor.visualState();
                    }, Stack);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                        Column.opacity(this.listNodeDataSource.k14(ObservedObject.GetRawObject(this.item)));
                        Column.onHover((isHover) => {
                            if (isHover) {
                                this.item.i6(this.treeViewTheme.n4);
                            }
                            else {
                                this.item.i6({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                            }
                        });
                        Column.onTouch((event) => {
                            this.count++;
                            if (this.count > 1) {
                                this.count--;
                                return;
                            }
                            this.index = this.listNodeDataSource.findIndex(this.item.m6());
                            this.listNodeDataSource.t9(this.index);
                            let g5 = this.item.m6();
                            if (event.type === TouchType.Down) {
                                this.item.i6(this.treeViewTheme.m4);
                            }
                            else if (event.type === TouchType.Up) {
                                if (!(typeof this.treeViewTheme.h4 === 'string')) {
                                    this.item.i6(b2);
                                }
                                else {
                                    this.item.i6(this.treeViewTheme.h4);
                                }
                                if (this.item.s6().d4 !== null) {
                                    this.item.s6().d4?.u8(e3.SELECTED);
                                    this.listNodeDataSource.u8(this.index, e3.SELECTED);
                                    this.item.imageSource = this.item.s6().d4?.source;
                                    this.item.t4 = this.item.s6().d4?.t4;
                                }
                                this.item.s6().e4?.v8(true);
                                let h5 = { currentNodeId: g5 };
                                this.appEventBus.emit(TreeListenType.NODE_CLICK, h5);
                                this.listNodeDataSource.h10(this.item.a7()
                                    ? this.listNodeDataSource.getStringByName('treeview_accessibility_select_node', `${this.getAccessibilityReadText(this.item.m6())}`) : '');
                            }
                            if (this.listNodeDataSource.i10() !== -1 && this.index !== this.listNodeDataSource.i10()) {
                                this.listNodeDataSource.j10(a3.WARNINGS, b3.NONE, false, this.listNodeDataSource.i10());
                                this.listNodeDataSource.k10(this.listNodeDataSource.i10(), z2.COMMIT_NODE);
                            }
                            this.lastIndex = this.index;
                            this.count--;
                        });
                        Column.backgroundColor((this.item.s6().e4 && this.item.s6().inputText &&
                            this.item.f6()) ? this.item.s6().inputText?.e16 : this.item.j6());
                        Column.border({
                            width: this.item.u6().borderWidth,
                            color: this.item.u6().borderColor,
                            radius: this.item.u6().borderRadius,
                        });
                        Column.height(i1);
                        Column.focusable(true);
                        Column.onMouse((event) => {
                            let f5 = this.listNodeDataSource.findIndex(this.item.m6());
                            if (event.button === MouseButton.Right) {
                                this.listNodeDataSource.u9(Event.MOUSE_BUTTON_RIGHT, this.listNodeDataSource.findIndex(this.item.m6()));
                                this.listTreeViewMenu = this.item.y6();
                                this.listNodeDataSource.t9(f5);
                                clearTimeout(this.item.s6().e4?.g14);
                            }
                            event.stopPropagation();
                        });
                        Column.padding({ top: 0, bottom: 0 });
                        Column.bindPopup(this.item.y5().c5, {
                            builder: { builder: () => {
                                    this.popupForShowTitle.call(this, this.item.y5().f5, this.item.y5().e5, this.item.y5().g5);
                                } },
                            placement: Placement.BottomLeft,
                            placementOnTop: false,
                            popupColor: this.item.y5().e5,
                            autoCancel: true,
                            enableArrow: this.item.y5().d5
                        });
                        Column.onAreaChange((oldValue, newValue) => {
                            let e5 = Number.parseInt(newValue.width.toString());
                            this.columnWidth = e5;
                        });
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Stack.create({ alignContent: Alignment.Bottom });
                        Stack.focusable(true);
                    }, Stack);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Divider.create();
                        Divider.height(this.listNodeDataSource.e15().v12);
                        Divider.color(this.listNodeDataSource.e15().w12);
                        Divider.visibility(this.listNodeDataSource.f15(ObservedObject.GetRawObject(this.item)));
                        Divider.lineCap(LineCapStyle.Round);
                        Divider.margin({ start: LengthMetrics.vp(this.item.h7()) });
                        Divider.focusable(true);
                    }, Divider);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create({});
                        Row.focusable(true);
                        Row.width('100%');
                        Row.height(this.item.p6());
                        Row.padding({ start: LengthMetrics.vp(this.item.o6()) });
                        Row.bindContextMenu({ builder: this.builder.bind(this) }, ResponseType.RightClick);
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.height(i1);
                        Row.layoutWeight(1);
                        Row.focusable(true);
                        Row.accessibilityGroup(true);
                        Row.id(`treeView_node${this.item.m6()}`);
                        Row.accessibilityText(this.getAccessibilityReadText(this.item.m6()));
                        Row.accessibilityDescription(this.getAccessibilityDescription());
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.item.s6().d4) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Row.create();
                                    Row.focusable(true);
                                    Row.backgroundColor(a2);
                                    Row.margin({
                                        end: o(this.item.s6().d4?.k8)
                                    });
                                    Row.height(this.item.s6().d4?.itemHeight);
                                    Row.width(this.item.s6().d4?.itemWidth);
                                }, Row);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    If.create();
                                    if (this.item.t4) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                SymbolGlyph.create();
                                                SymbolGlyph.attributeModifier.bind(this)(this.item.t4);
                                                SymbolGlyph.fontSize(this.item.s6().d4?.itemHeight);
                                                SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                                SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                                SymbolGlyph.opacity(!this.item.a7() && !this.item.o7() ?
                                                    this.item.s6().d4?.opacity : this.item.s6().d4?.f16);
                                                SymbolGlyph.focusable(this.item.s6().e4 !== null ? false : true);
                                            }, SymbolGlyph);
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                If.create();
                                                if (Util.b4(this.item.imageSource)) {
                                                    this.ifElseBranchUpdateFunction(0, () => {
                                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                            SymbolGlyph.create(this.item.imageSource);
                                                            SymbolGlyph.fontSize(this.item.s6().d4?.itemHeight);
                                                            SymbolGlyph.fontColor([this.getLeftIconColor()]);
                                                            SymbolGlyph.opacity(!this.item.a7() && !this.item.o7() ?
                                                                this.item.s6().d4?.opacity : this.item.s6().d4?.f16);
                                                            SymbolGlyph.focusable(this.item.s6().e4 !== null ? false : true);
                                                        }, SymbolGlyph);
                                                    });
                                                }
                                                else {
                                                    this.ifElseBranchUpdateFunction(1, () => {
                                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                            Image.create(this.item.imageSource);
                                                            Image.objectFit(ImageFit.Contain);
                                                            Image.height(this.item.s6().d4?.itemHeight);
                                                            Image.width(this.item.s6().d4?.itemWidth);
                                                            Image.opacity(!this.item.a7() && !this.item.o7() ?
                                                                this.item.s6().d4?.opacity : this.item.s6().d4?.f16);
                                                            Image.focusable(this.item.s6().e4 !== null ? false : true);
                                                            Image.fillColor(this.getLeftIconColor());
                                                            Image.matchTextDirection((this.item.s6().f4?.o8 === ARROW_RIGHT || this.item.s6().f4?.o8 === w2) ? true : false);
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
                        if (this.item.s6().e4 && this.item.e6()) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Text.create(this.item.s6().e4?.title);
                                    Text.minFontScale(o1);
                                    Text.maxFontScale(this.decideFontScale());
                                    Text.maxLines(1);
                                    Text.fontSize(this.item.s6().e4?.size);
                                    Text.fontColor(this.item.a7() ?
                                        this.treeViewTheme.l4 : this.treeViewTheme.i4);
                                    Text.margin({
                                        end: o(this.item.s6().e4?.k8)
                                    });
                                    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                                    Text.fontWeight(this.item.s6().e4?.weight);
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
                        if (this.item.s6().e4 && this.item.s6().inputText &&
                            this.item.f6()) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Row.create();
                                    Row.backgroundColor(this.item.s6().inputText?.backgroundColor);
                                    Row.borderRadius(this.item.s6().inputText?.borderRadius);
                                    Row.margin({
                                        end: o(this.item.s6()
                                            .inputText?.k8)
                                    });
                                }, Row);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    TextInput.create({ text: this.item.s6().e4?.title });
                                    TextInput.height(this.item.s6().inputText?.itemHeight);
                                    TextInput.fontSize(this.getInputTextMaxFontSize());
                                    TextInput.fontColor(this.item.s6().inputText?.color);
                                    TextInput.borderRadius(this.item.s6().inputText?.borderRadius);
                                    TextInput.backgroundColor(this.item.s6().inputText?.backgroundColor);
                                    TextInput.enterKeyType(EnterKeyType.Done);
                                    TextInput.focusable(true);
                                    TextInput.padding({
                                        start: LengthMetrics.resource(this.textInputPadding.left),
                                        end: LengthMetrics.resource(this.textInputPadding.right),
                                        top: LengthMetrics.resource(this.textInputPadding.top),
                                        bottom: LengthMetrics.resource(this.textInputPadding.bottom),
                                    });
                                    TextInput.onChange((value) => {
                                        let z4 = this.listNodeDataSource.findIndex(this.item.m6());
                                        let a5 = '';
                                        let b5 = false;
                                        let c5 = false;
                                        if (this.checkInvalidPattern(value)) {
                                            for (let d5 = 0; d5 < value.length; d5++) {
                                                if (!this.checkInvalidPattern(value[d5])) {
                                                    a5 += value[d5];
                                                }
                                            }
                                            b5 = true;
                                            this.listNodeDataSource.j10(a3.WARNINGS, b3.INVALID_ERROR, true, z4);
                                        }
                                        else {
                                            a5 = value;
                                            b5 = false;
                                        }
                                        if ((this.checkIsAllCN(a5) && a5.length > this.MAX_CN_LENGTH) ||
                                            (!this.checkIsAllCN(a5) && a5.length > this.MAX_EN_LENGTH)) {
                                            a5 = this.checkIsAllCN(a5) ?
                                                a5.substr(0, this.MAX_CN_LENGTH) : a5.substr(0, this.MAX_EN_LENGTH);
                                            c5 = true;
                                            this.listNodeDataSource.j10(a3.WARNINGS, b3.LENGTH_ERROR, true, z4);
                                        }
                                        else {
                                            c5 = false;
                                        }
                                        if (!c5 && !b5) {
                                            this.listNodeDataSource.h14(z4, a5);
                                        }
                                    });
                                    TextInput.onSubmit((enterKey) => {
                                        let y4 = this.listNodeDataSource.findIndex(this.item.m6());
                                        this.listNodeDataSource.j10(a3.WARNINGS, b3.NONE, false, y4);
                                        this.listNodeDataSource.k10(y4, z2.COMMIT_NODE);
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
                        if (this.listNodeDataSource.w14(this.item.m6())) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Row.create();
                                    Row.focusable(true);
                                    Row.margin({
                                        start: LengthMetrics.resource(this.listNodeDataSource.g15().margin.left),
                                        end: this.item.s6().f4 ?
                                            LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }) :
                                            LengthMetrics.resource(this.listNodeDataSource.g15().margin.right)
                                    });
                                }, Row);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Text.create(this.listNodeDataSource.v14(this.item.m6()));
                                    Text.minFontScale(o1);
                                    Text.maxFontScale(this.decideFontScale());
                                    Text.fontSize(this.listNodeDataSource.g15().fontSize);
                                    Text.fontColor(this.item.o7() || this.item.q7() ? { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_primary_contrary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : this.treeViewTheme.j4);
                                    Text.fontWeight(this.listNodeDataSource.g15().fontWeight);
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
                        if (this.item.s6().f4) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                if (!If.canRetake(`treeView_button${this.item.m6()}`)) {
                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                        Row.create();
                                        Row.focusable(true);
                                        Row.justifyContent(FlexAlign.Center);
                                        Row.height(this.item.s6().f4?.itemHeight);
                                        Row.width(this.item.s6().f4?.itemWidth);
                                        Row.id(`treeView_button${this.item.m6()}`);
                                        Row.accessibilityText(this.getAccessibilityReadButtonText(this.item.s6().f4?.o8 === ARROW_RIGHT));
                                        Row.accessibilityDescription(this.getAccessibilityReadButtonDescription());
                                        Row.accessibilityLevel('yes');
                                    }, Row);
                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                        SymbolGlyph.create(this.item.s6().f4?.o8);
                                        SymbolGlyph.fontSize(this.item.s6().f4?.itemHeight);
                                        SymbolGlyph.fontColor([this.item.s6().f4?.n13 ?
                                                this.treeViewTheme.s4 : z1]);
                                        SymbolGlyph.opacity(!this.item.o7() ?
                                            this.item.s6().f4?.opacity : this.item.s6().f4?.f16);
                                        SymbolGlyph.onTouch((event) => {
                                            if (event.type === TouchType.Down) {
                                                this.listNodeDataSource.w9(this.listNodeDataSource.findIndex(this.item.m6()));
                                                this.listNodeDataSource.i15(this.item.m6());
                                                this.clickButtonFlag = false;
                                            }
                                            if (event.type === TouchType.Up) {
                                                let eventInfo = ({
                                                    type: 'requestFocusForAccessibility',
                                                    bundleName: getContext()?.abilityInfo?.bundleName,
                                                    triggerAction: 'common',
                                                    customId: `treeView_button${this.item.m6()}`
                                                });
                                                accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                                                    setTimeout(() => {
                                                        this.clickButtonFlag = true;
                                                    }, t2);
                                                });
                                            }
                                            event.stopPropagation();
                                        });
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
export class s3 {
    constructor(nodeParam) {
        this.currentNodeId = nodeParam.currentNodeId ?? -1;
        this.parentNodeId = nodeParam.parentNodeId ?? -1;
        this.isFolder = nodeParam.isFolder;
        this.j5 = -1;
        this.q15 = -1;
        this.x6 = { p13: false, q13: 0, f11: 0 };
        this.children = [];
    }
    w6() {
        return this.x6;
    }
    u13() {
        return this.currentNodeId;
    }
    d7() {
        return this.isFolder;
    }
}
class t3 {
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
    set k8(rightMargin) {
        this.rightMargin = rightMargin;
    }
    get k8() {
        return this.rightMargin;
    }
}
export class u3 extends t3 {
    constructor(imageSource, t4, u4, itemWidth, itemHeight, v4, w4, x4) {
        super();
        this.rightMargin = { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_elements_margin_horizontal_m'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.imageSource = imageSource;
        this.g16 = t4;
        this.rightMargin = v4;
        this.m8 = u4;
        this.itemWidth = itemWidth;
        this.itemHeight = itemHeight;
        this.h16 = imageSource;
        this.i16 = t4;
        this.j16 = w4;
        this.k16 = x4;
    }
    get source() {
        return this.imageSource;
    }
    get t4() {
        return this.g16;
    }
    get opacity() {
        return this.m8;
    }
    get f16() {
        return 1;
    }
    get o8() {
        return this.h16;
    }
    get l16() {
        return this.i16;
    }
    get n13() {
        return this.j16;
    }
    get type() {
        return this.k16;
    }
}
class v3 {
    constructor() {
    }
    static getInstance() {
        if (!v3.instance) {
            v3.instance = new v3();
        }
        return v3.instance;
    }
    m16(type) {
        let imageSource;
        switch (type) {
            case f3.ARROW_RIGHT_WHITE:
                imageSource = w2;
                break;
            case f3.ARROW_RIGHT:
                imageSource = ARROW_RIGHT;
                break;
            case f3.ARROW_DOWN_WHITE:
                imageSource = v2;
                break;
            default:
                imageSource = ARROW_DOWN;
        }
        return new u3(imageSource, undefined, { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_alpha_content_tertiary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, u, a1, { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_paragraph_margin_xs'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, (type === f3.ARROW_RIGHT_WHITE || type === f3.ARROW_DOWN_WHITE) ? false : true, type);
    }
}
class w3 {
    static v5(type) {
        let node = w3.n16.get(type);
        if (node === undefined) {
            node = v3.getInstance().m16(type);
            w3.n16.set(type, node);
        }
        return node;
    }
    static h13(q4, r4, s4) {
        if (s4 === undefined) {
            return undefined;
        }
        let type = s4;
        if (q4 == e3.EDIT ||
            q4 === e3.DRAG_INSERT) {
            if (r4 === d3.COLLAPSE) {
                type = f3.ARROW_RIGHT_WHITE;
            }
            else {
                type = f3.ARROW_DOWN_WHITE;
            }
        }
        else if (q4 === e3.FINISH_EDIT ||
            q4 === e3.FINISH_DRAG_INSERT) {
            if (r4 === d3.COLLAPSE) {
                type = f3.ARROW_RIGHT;
            }
            else {
                type = f3.ARROW_DOWN;
            }
        }
        return w3.v5(type);
    }
    static l13(o4, p4) {
        if (p4 === undefined) {
            return undefined;
        }
        let type;
        if (!p4) {
            if (o4 === d3.COLLAPSE) {
                type = f3.ARROW_RIGHT_WHITE;
            }
            else {
                type = f3.ARROW_DOWN_WHITE;
            }
        }
        else {
            if (o4 === d3.COLLAPSE) {
                type = f3.ARROW_RIGHT;
            }
            else {
                type = f3.ARROW_DOWN;
            }
        }
        return w3.v5(type);
    }
}
w3.n16 = new Map();
export class x3 extends t3 {
    constructor(imageSource, i4, j4, itemWidth, itemHeight, k4, l4, m4, n4) {
        super();
        this.rightMargin = { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_elements_margin_horizontal_m'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.imageSource = imageSource;
        this.g16 = i4;
        this.o16 = imageSource;
        this.p16 = i4;
        if (k4 !== undefined) {
            this.q16 = k4;
        }
        else {
            this.q16 = this.o16;
        }
        this.r16 = l4;
        if (m4 !== undefined) {
            this.s16 = m4;
        }
        else {
            this.s16 = this.o16;
        }
        this.t16 = n4;
        this.m8 = j4;
        this.itemWidth = itemWidth;
        this.itemHeight = itemHeight;
        this.h16 = imageSource;
        this.u16 = ARROW_DOWN;
        this.v16 = ARROW_RIGHT;
        this.j16 = true;
        this.w16 = e3.NORMAL;
    }
    get source() {
        return this.imageSource;
    }
    get t4() {
        return this.g16;
    }
    get n8() {
        return this.o16;
    }
    get l8() {
        return this.p16;
    }
    get c14() {
        return this.q16;
    }
    get t15() {
        return this.r16;
    }
    get d14() {
        return this.s16;
    }
    get u15() {
        return this.t16;
    }
    get opacity() {
        return this.m8;
    }
    get f16() {
        return 1;
    }
    get o8() {
        return this.h16;
    }
    get n13() {
        return this.j16;
    }
    l13(h4) {
        if (h4 === d3.EXPAND) {
            this.h16 = this.u16;
        }
        else if (h4 === d3.COLLAPSE) {
            this.h16 = this.v16;
        }
    }
    g13(f4, g4) {
        if (f4 === e3.EDIT || f4 === e3.DRAG_INSERT) {
            this.u16 = v2;
            this.v16 = w2;
            this.j16 = false;
        }
        else if (f4 === e3.FINISH_EDIT ||
            f4 === e3.FINISH_DRAG_INSERT) {
            this.u16 = ARROW_DOWN;
            this.v16 = ARROW_RIGHT;
            this.j16 = true;
        }
        this.h16 = (g4 === d3.COLLAPSE) ?
            this.v16 : this.u16;
    }
    u8(e4) {
        switch (e4) {
            case e3.NORMAL:
                this.imageSource = this.o16;
                this.g16 = this.p16;
                this.w16 = e4;
                break;
            case e3.SELECTED:
                if (this.w16 !== e3.EDIT) {
                    this.imageSource = this.q16;
                    this.g16 = this.r16;
                    this.w16 = e4;
                }
                break;
            case e3.EDIT:
                this.imageSource = this.s16;
                this.g16 = this.t16;
                this.w16 = e4;
                break;
            case e3.FINISH_EDIT:
                this.imageSource = this.q16;
                this.g16 = this.r16;
                this.w16 = e4;
                break;
            case e3.DRAG_INSERT:
                this.imageSource = this.s16;
                this.g16 = this.t16;
                this.w16 = e4;
                break;
            case e3.FINISH_DRAG_INSERT:
                this.imageSource = this.o16;
                this.g16 = this.p16;
                this.w16 = e4;
                break;
            default:
                break;
        }
    }
}
class y3 extends t3 {
    constructor(d4) {
        super();
        this.treeViewTheme = j3.getInstance();
        this.x16 = d4;
        this.itemWidth = b1;
        this.itemHeight = c1;
        this.rightMargin = { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_paragraph_margin_xs'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.y16 = {
            fontColor: this.treeViewTheme.i4,
            fontSize: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            fontWeight: FontWeight.Normal,
        };
        this.z16 = 0;
    }
    v8(isSelected) {
        if (isSelected) {
            this.y16 = {
                fontColor: this.treeViewTheme.l4,
                fontSize: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                fontWeight: FontWeight.Regular,
            };
        }
        else {
            this.y16 = {
                fontColor: this.treeViewTheme.i4,
                fontSize: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                fontWeight: FontWeight.Normal,
            };
        }
    }
    set title(text) {
        this.x16 = text;
    }
    get title() {
        return this.x16;
    }
    set g14(c4) {
        this.z16 = c4;
    }
    get g14() {
        return this.z16;
    }
    get color() {
        return this.y16.fontColor;
    }
    get size() {
        return this.y16.fontSize;
    }
    get weight() {
        return this.y16.fontWeight;
    }
    c10(b4) {
        if (b4) {
            this.y16 = {
                fontColor: this.treeViewTheme.l4,
                fontSize: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                fontWeight: FontWeight.Regular,
            };
        }
        else {
            this.y16 = {
                fontColor: this.treeViewTheme.i4,
                fontSize: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                fontWeight: FontWeight.Normal,
            };
        }
    }
}
export class z3 extends t3 {
    constructor() {
        super();
        this.status = undefined;
        this.a17 = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.b17 = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_emphasize'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.radius = { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_default_xs'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.treeViewTheme = j3.getInstance();
        this.itemWidth = b1;
        this.itemHeight = d1;
        this.rightMargin = { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_paragraph_margin_xs'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.c17 = {
            fontColor: this.treeViewTheme.i4,
            fontSize: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            fontWeight: FontWeight.Normal,
        };
    }
    get color() {
        return this.c17.fontColor;
    }
    get size() {
        return this.c17.fontSize;
    }
    get weight() {
        return this.c17.fontWeight;
    }
    get borderRadius() {
        return this.radius;
    }
    get backgroundColor() {
        return this.a17;
    }
    get e16() {
        return this.b17;
    }
    get d17() {
        return this.status;
    }
}
function o(a4) {
    if (!a4) {
        return LengthMetrics.vp(0);
    }
    else if (typeof a4 === 'number') {
        return LengthMetrics.vp(a4);
    }
    else {
        return LengthMetrics.resource(a4);
    }
}

export default {
    TreeController,
    TreeListener,
    TreeListenerManager,
    TreeListenType,
    TreeView,
}