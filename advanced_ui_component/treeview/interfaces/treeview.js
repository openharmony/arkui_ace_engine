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

var t = (this && this.t) || function (f19, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === 'object' && typeof Reflect.u3 === 'function')
        r = Reflect.u3(f19, target, key, desc);
    else
        for (var g19 = f19.length - 1; g19 >= 0; g19--)
            if (d = f19[g19])
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
const i16 = 'TreeView';
const j16 = 0x3900;
const j17 = 2000;
const s20 = 300;
const n21 = 40000;
const ARROW_DOWN = { 'id': -1, 'type': 40000, params: ['sys.symbol.chevron_down'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const q2 = { 'id': -1, 'type': 40000, params: ['sys.symbol.chevron_down'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const ARROW_RIGHT = { 'id': -1, 'type': 40000, params: ['sys.symbol.chevron_forward'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const s2 = { 'id': -1, 'type': 40000, params: ['sys.symbol.chevron_forward'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
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
var t2;
(function (e23) {
    e23[e23['ADD_NODE'] = 0] = 'ADD_NODE';
    e23[e23['REMOVE_NODE'] = 1] = 'REMOVE_NODE';
    e23[e23['MODIFY_NODE'] = 2] = 'MODIFY_NODE';
    e23[e23['COMMIT_NODE'] = 3] = 'COMMIT_NODE';
})(t2 || (t2 = {}));
var u2;
(function (d23) {
    d23[d23['HINTS'] = 0] = 'HINTS';
    d23[d23['WARNINGS'] = 1] = 'WARNINGS';
})(u2 || (u2 = {}));
var v2;
(function (c23) {
    c23[c23['INVALID_ERROR'] = 0] = 'INVALID_ERROR';
    c23[c23['LENGTH_ERROR'] = 1] = 'LENGTH_ERROR';
    c23[c23['NONE'] = 2] = 'NONE';
})(v2 || (v2 = {}));
var w2;
(function (b23) {
    b23[b23['DOWN_FLAG'] = 0] = 'DOWN_FLAG';
    b23[b23['UP_FLAG'] = 1] = 'UP_FLAG';
    b23[b23['NONE'] = 2] = 'NONE';
})(w2 || (w2 = {}));
export var z2;
(function (a23) {
    a23[a23['EXPAND'] = 0] = 'EXPAND';
    a23[a23['COLLAPSE'] = 1] = 'COLLAPSE';
})(z2 || (z2 = {}));
export var a3;
(function (z22) {
    z22[z22['NORMAL'] = 0] = 'NORMAL';
    z22[z22['SELECTED'] = 1] = 'SELECTED';
    z22[z22['EDIT'] = 2] = 'EDIT';
    z22[z22['FINISH_EDIT'] = 3] = 'FINISH_EDIT';
    z22[z22['DRAG_INSERT'] = 4] = 'DRAG_INSERT';
    z22[z22['FINISH_DRAG_INSERT'] = 5] = 'FINISH_DRAG_INSERT';
})(a3 || (a3 = {}));
var b3;
(function (y22) {
    y22[y22['ARROW_DOWN'] = 0] = 'ARROW_DOWN';
    y22[y22['ARROW_RIGHT'] = 1] = 'ARROW_RIGHT';
    y22[y22['ARROW_DOWN_WHITE'] = 2] = 'ARROW_DOWN_WHITE';
    y22[y22['ARROW_RIGHT_WHITE'] = 3] = 'ARROW_RIGHT_WHITE';
})(b3 || (b3 = {}));
var q17;
(function (x22) {
    x22[x22['TEXT'] = 0] = 'TEXT';
    x22[x22['PLACE'] = 1] = 'PLACE';
    x22[x22['LIFT'] = 2] = 'LIFT';
})(q17 || (q17 = {}));
class Util {
    static t16(w22) {
        if (!Util.u16(w22)) {
            return false;
        }
        let resource = w22;
        return resource.type === n21;
    }
    static u16(resource) {
        if (!resource) {
            return false;
        }
        if (typeof resource === 'string' || typeof resource === 'undefined') {
            return false;
        }
        return true;
    }
}
class c3 {
    constructor() {
    }
    static getInstance() {
        if (!c3.instance) {
            c3.instance = new c3();
        }
        return c3.instance;
    }
    createNode() {
        return {
            v3: undefined,
            inputText: new t3(),
            w3: new s3(''),
            x3: undefined,
            fontColor: undefined,
        };
    }
    y3(nodeParam) {
        let w18 = this.createNode();
        if (nodeParam.icon) {
            w18.v3 = new r3(nodeParam.icon, nodeParam.v16, { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_alpha_content_fourth'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, u, a1, nodeParam.selectedIcon, nodeParam.w16, nodeParam.editIcon, nodeParam.x16);
        }
        if (nodeParam.primaryTitle) {
            w18.w3 = new s3(nodeParam.primaryTitle);
        }
        return w18;
    }
}
let d3 = {
    isFolder: true,
    icon: '',
    v16: undefined,
    selectedIcon: '',
    w16: undefined,
    editIcon: '',
    x16: undefined,
    container: () => {
    },
    secondaryTitle: '',
    primaryTitle: '',
    parentNodeId: -1,
    currentNodeId: -1,
};
class e3 {
    constructor() {
        this.z3 = '#1A0A59F7';
        this.a4 = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.b4 = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.c4 = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary_activated'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.d4 = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_click_effect'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.e4 = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_hover'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.f4 = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_focused_outline'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.g4 = { 'id': -1, 'type': 10001, params: ['sys.color.icon_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.h4 = { 'id': -1, 'type': 10001, params: ['sys.color.icon_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.i4 = { 'id': -1, 'type': 10001, params: ['sys.color.icon_tertiary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    }
    static getInstance() {
        if (!e3.instance) {
            e3.instance = new e3();
        }
        return e3.instance;
    }
}
let f3 = class NodeInfo {
    constructor(node, nodeParam) {
        this.j4 = '';
        this.y16 = undefined;
        this.borderWidth = { has: e1, l4: f1 };
        this.m4 = false;
        this.n4 = false;
        this.o4 = false;
        this.q4 = false;
        this.r4 = false;
        this.treeViewTheme = e3.getInstance();
        this.fontColor = '';
        this.node = node;
        this.nodeParam = nodeParam;
        this.s4 = c3.getInstance().y3(nodeParam);
        this.t4 = {
            u4: false,
            v4: false,
            w4: undefined,
            x4: '',
            y4: undefined,
        };
        this.z4 = g1;
        this.a5 = node.b5 * n2 + o2;
        this.c5 = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.d5 = (this.node.b5 > 0) ? false : true;
        this.e5 = (this.node.b5 > 0) ? h1 : i1;
        this.f5 = true;
        this.g5 = false;
        this.isSelected = false;
        this.status = {
            normal: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            h5: this.treeViewTheme.e4,
            i5: this.treeViewTheme.d4,
            selected: this.treeViewTheme.z3,
            j5: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_activated'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }
        };
        this.k5 = {
            borderWidth: f1,
            borderColor: this.treeViewTheme.f4,
            borderRadius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }
        };
        this.l5 = node.b5 * n2 + o2;
    }
    m5(v18) {
        if (v18) {
            this.s4.x3 =
                q3.n5(b3.ARROW_RIGHT);
        }
        else {
            this.s4.x3 = undefined;
        }
    }
    o5(color) {
        this.fontColor = color;
    }
    p5() {
        return this.fontColor;
    }
    q5() {
        return this.t4;
    }
    r5(isShow) {
        this.t4.u4 = isShow;
    }
    s5(u18) {
        this.t4.v4 = u18;
    }
    t5(color) {
        this.t4.w4 = color;
    }
    u5(text) {
        this.t4.x4 = text;
    }
    v5(t18) {
        this.t4.y4 = t18;
    }
    w5() {
        return this.f5;
    }
    x5() {
        return this.g5;
    }
    y5(s18) {
        if (s18) {
            this.f5 = false;
            this.g5 = true;
        }
        else {
            this.f5 = true;
            this.g5 = false;
        }
    }
    z5(r18) {
        if (r18) {
            this.s4.x3 =
                q3.n5(b3.ARROW_DOWN);
        }
        else {
            this.s4.x3 = undefined;
        }
    }
    a6(q18) {
        if (q18 === undefined) {
            return;
        }
        this.c5 = q18;
    }
    b6() {
        return this.c5;
    }
    c6(p18) {
        this.e5 = p18;
    }
    d6() {
        return this.e5;
    }
    e6() {
        return this.node.currentNodeId;
    }
    f6() {
        return this.node.parentNodeId;
    }
    g6() {
        return this.a5;
    }
    h6() {
        return this.z4;
    }
    i6(o18) {
        this.d5 = o18;
    }
    j6() {
        return this.d5;
    }
    k6() {
        return this.s4;
    }
    l6() {
        return this.status;
    }
    m6() {
        return this.k5;
    }
    n6(n18) {
        this.k5.borderWidth = n18 ? this.borderWidth.has : this.borderWidth.l4;
    }
    o6() {
        return this.node.p6;
    }
    q6() {
        return this.nodeParam.container;
    }
    r6(isSelected) {
        this.isSelected = isSelected;
    }
    s6() {
        return this.isSelected;
    }
    t6() {
        return this.nodeParam;
    }
    u6() {
        return this.node;
    }
    v6() {
        return this.nodeParam.isFolder;
    }
    w6(m18) {
        this.m4 = m18;
    }
    x6() {
        return this.m4;
    }
    y6(l18) {
        if (l18 === undefined) {
            return;
        }
        this.l5 = l18 * n2 + o2;
    }
    z6() {
        return this.l5;
    }
    a7() {
        return this.node.b5;
    }
    b7(k18) {
        this.n4 = k18;
    }
    c7() {
        return this.n4;
    }
    d7(j18) {
        this.o4 = j18;
    }
    e7() {
        return this.o4;
    }
    f7(i18) {
        this.q4 = i18;
    }
    g7() {
        return this.q4;
    }
    h7(h18) {
        this.r4 = h18;
    }
    i7() {
        return this.r4;
    }
};
f3 = t([
    Observed
], f3);
export { f3 };
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
        this.j7 = [];
        this.k7 = [];
    }
    on(type, callback) {
        if (Array.isArray(type)) {
            for (let g18 = 0, l = type.length; g18 < l; g18++) {
                this.on(type[g18], callback);
            }
        }
        else {
            (this.j7[type] || (this.j7[type] = [])).push(callback);
        }
    }
    once(type, callback) {
        if (Array.isArray(type)) {
            this.off(type, callback);
        }
        else {
            (this.k7[type] || (this.k7[type] = [])).push(callback);
        }
    }
    off(type, callback) {
        if (type === null) {
            this.j7 = [];
        }
        if (Array.isArray(type)) {
            for (let f18 = 0, l = type.length; f18 < l; f18++) {
                this.off(type[f18], callback);
            }
        }
        let c18 = this.j7[type];
        if (!c18) {
            return;
        }
        if (callback === null) {
            this.j7[type] = null;
        }
        let d18 = c18.length;
        while (d18--) {
            let e18 = c18[d18];
            if (e18 === callback) {
                c18.splice(d18, 1);
                break;
            }
        }
    }
    emit(event, x17) {
        if (this.k7[event]) {
            let a18 = Array.from(this.k7[event]);
            if (a18) {
                for (let b18 = 0, l = a18.length; b18 < l; b18++) {
                    try {
                        a18[b18](x17);
                    }
                    catch (e) {
                        throw new Error('once function callbacks error.');
                    }
                }
                this.k7[event] = null;
            }
        }
        else if (this.j7[event]) {
            let y17 = Array.from(this.j7[event]);
            if (y17) {
                for (let z17 = 0, l = y17.length; z17 < l; z17++) {
                    try {
                        y17[z17](x17);
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
TreeListenerManager.l7 = 'app_key_event_bus';
export class TreeView extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.treeController = new TreeController();
        this.m7 = new ObservedPropertyObjectPU([], this, 'nodeList');
        this.listNodeDataSource = new h3();
        this.n7 = new ObservedPropertyObjectPU(null, this, 'item');
        this.o7 = new ObservedPropertySimplePU(0, this, 'touchCount');
        this.p7 = new ObservedPropertySimplePU(0, this, 'dropSelectedIndex');
        this.q7 = new ObservedPropertySimplePU(-1, this, 'viewLastIndex');
        this.r7 = new ObservedPropertySimplePU(false, this, 'followingSystemFontScale');
        this.s7 = new ObservedPropertySimplePU(1, this, 'maxAppFontScale');
        this.t7 = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'listItemBgColor');
        this.m16 = new ObservedPropertyObjectPU([], this, 'allParentNode');
        this.u7 = new ObservedPropertyObjectPU(e3.getInstance(), this, 'treeViewTheme');
        this.addProvidedVar('treeViewTheme', this.u7, false);
        this.n16 = new ObservedPropertySimplePU(true, this, 'clickButtonFlag');
        this.addProvidedVar('clickButtonFlag', this.n16, false);
        this.r16 = new ObservedPropertySimplePU(q17.TEXT, this, 'accessibilityNodeType');
        this.addProvidedVar('accessibilityNodeType', this.r16, false);
        this.z16 = new ObservedPropertySimplePU(false, this, 'isAccessibilityEnabled');
        this.addProvidedVar('isAccessibilityEnabled', this.z16, false);
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
        this.m7.purgeDependencyOnElmtId(rmElmtId);
        this.n7.purgeDependencyOnElmtId(rmElmtId);
        this.o7.purgeDependencyOnElmtId(rmElmtId);
        this.p7.purgeDependencyOnElmtId(rmElmtId);
        this.q7.purgeDependencyOnElmtId(rmElmtId);
        this.r7.purgeDependencyOnElmtId(rmElmtId);
        this.s7.purgeDependencyOnElmtId(rmElmtId);
        this.t7.purgeDependencyOnElmtId(rmElmtId);
        this.m16.purgeDependencyOnElmtId(rmElmtId);
        this.u7.purgeDependencyOnElmtId(rmElmtId);
        this.n16.purgeDependencyOnElmtId(rmElmtId);
        this.r16.purgeDependencyOnElmtId(rmElmtId);
        this.z16.purgeDependencyOnElmtId(rmElmtId);
    }
    aboutToBeDeleted() {
        this.m7.aboutToBeDeleted();
        this.n7.aboutToBeDeleted();
        this.o7.aboutToBeDeleted();
        this.p7.aboutToBeDeleted();
        this.q7.aboutToBeDeleted();
        this.r7.aboutToBeDeleted();
        this.s7.aboutToBeDeleted();
        this.t7.aboutToBeDeleted();
        this.m16.aboutToBeDeleted();
        this.u7.aboutToBeDeleted();
        this.n16.aboutToBeDeleted();
        this.r16.aboutToBeDeleted();
        this.z16.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get nodeList() {
        return this.m7.get();
    }
    set nodeList(newValue) {
        this.m7.set(newValue);
    }
    get item() {
        return this.n7.get();
    }
    set item(newValue) {
        this.n7.set(newValue);
    }
    get touchCount() {
        return this.o7.get();
    }
    set touchCount(newValue) {
        this.o7.set(newValue);
    }
    get dropSelectedIndex() {
        return this.p7.get();
    }
    set dropSelectedIndex(newValue) {
        this.p7.set(newValue);
    }
    get viewLastIndex() {
        return this.q7.get();
    }
    set viewLastIndex(newValue) {
        this.q7.set(newValue);
    }
    get followingSystemFontScale() {
        return this.r7.get();
    }
    set followingSystemFontScale(newValue) {
        this.r7.set(newValue);
    }
    get maxAppFontScale() {
        return this.s7.get();
    }
    set maxAppFontScale(newValue) {
        this.s7.set(newValue);
    }
    get listItemBgColor() {
        return this.t7.get();
    }
    set listItemBgColor(newValue) {
        this.t7.set(newValue);
    }
    get allParentNode() {
        return this.m16.get();
    }
    set allParentNode(newValue) {
        this.m16.set(newValue);
    }
    get treeViewTheme() {
        return this.u7.get();
    }
    set treeViewTheme(newValue) {
        this.u7.set(newValue);
    }
    get clickButtonFlag() {
        return this.n16.get();
    }
    set clickButtonFlag(newValue) {
        this.n16.set(newValue);
    }
    get accessibilityNodeType() {
        return this.r16.get();
    }
    set accessibilityNodeType(newValue) {
        this.r16.set(newValue);
    }
    get isAccessibilityEnabled() {
        return this.z16.get();
    }
    set isAccessibilityEnabled(newValue) {
        this.z16.set(newValue);
    }
    NullBuilder(parent = null) {
    }
    onWillApplyTheme(theme) {
        this.treeViewTheme.z3 = theme.colors.interactiveSelect;
        this.treeViewTheme.d4 = theme.colors.interactivePressed;
        this.treeViewTheme.e4 = theme.colors.interactiveHover;
        this.treeViewTheme.a4 = theme.colors.fontPrimary;
        this.treeViewTheme.b4 = theme.colors.fontSecondary;
        this.treeViewTheme.c4 = theme.colors.interactiveActive;
        this.treeViewTheme.f4 = theme.colors.interactiveFocus;
        this.treeViewTheme.g4 = theme.colors.iconSecondary;
        this.treeViewTheme.h4 = theme.colors.interactiveActive;
        this.treeViewTheme.i4 = theme.colors.iconPrimary;
        this.treeController.treeViewTheme = this.treeViewTheme;
    }
    aboutToAppear() {
        if (this.treeController !== null) {
            this.listNodeDataSource = this.treeController.v7();
            this.nodeList = this.treeController.v7().w7;
            this.item = this.treeController.v7().w7;
        }
        let w17 = this.getUIContext();
        this.followingSystemFontScale = w17.isFollowingSystemFontScale();
        this.maxAppFontScale = w17.getMaxFontScale();
        accessibility.on('accessibilityStateChange', (state) => {
            this.isAccessibilityEnabled = state;
        });
    }
    decideFontScale() {
        let u17 = this.getUIContext();
        let v17 = u17.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.followingSystemFontScale) {
            return 1;
        }
        return Math.min(v17, this.maxAppFontScale, q1);
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
            Row.id(`treeView_node_lift${item.e6()}`);
            Row.constraintSize({
                minWidth: this.listNodeDataSource.x7().y7.minWidth,
                maxWidth: this.listNodeDataSource.x7().y7.maxWidth,
            });
            Row.height(this.listNodeDataSource.x7().height);
            Row.backgroundColor(this.listNodeDataSource.x7().backgroundColor);
            Row.padding({
                start: LengthMetrics.resource(this.listNodeDataSource.x7().padding.left),
                end: LengthMetrics.resource(this.listNodeDataSource.x7().padding.right),
            });
            Row.shadow({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                color: c2,
                offsetY: 0,
            });
            Row.borderRadius(this.listNodeDataSource.x7().borderRadius);
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (item.k6().v3) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.backgroundColor(a2);
                        Row.margin({ end: o(item.k6().v3?.z7) });
                        Row.height(item.k6().v3?.itemHeight);
                        Row.width(item.k6().v3?.itemWidth);
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (item.k6().v3?.a17) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.attributeModifier.bind(this)(item.k6().v3?.a17);
                                    SymbolGlyph.fontSize(item.k6().v3?.itemHeight);
                                    SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                    SymbolGlyph.opacity(this.listNodeDataSource.x7().b8);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    If.create();
                                    if (Util.t16(item.k6().v3?.a8)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                SymbolGlyph.create(item.k6().v3?.a8);
                                                SymbolGlyph.fontSize(item.k6().v3?.itemHeight);
                                                SymbolGlyph.opacity(this.listNodeDataSource.x7().b8);
                                            }, SymbolGlyph);
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                Image.create(item.k6().v3?.a8);
                                                Image.objectFit(ImageFit.Contain);
                                                Image.height(item.k6().v3?.itemHeight);
                                                Image.width(item.k6().v3?.itemWidth);
                                                Image.opacity(this.listNodeDataSource.x7().b8);
                                                Image.matchTextDirection((item.k6().x3?.c8 === ARROW_RIGHT ||
                                                    item.k6().x3?.c8 === s2) ? true : false);
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
                minWidth: item.k6().v3 ?
                this.listNodeDataSource.x7().d8.e8 :
                this.listNodeDataSource.x7().d8.f8,
                maxWidth: item.k6().v3 ?
                this.listNodeDataSource.x7().d8.g8 :
                this.listNodeDataSource.x7().d8.h8,
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (item.k6().w3 && item.w5()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(item.k6().w3?.title);
                        Text.maxLines(1);
                        Text.minFontScale(o1);
                        Text.maxFontScale(this.decideFontScale());
                        Text.fontSize(item.k6().w3?.size);
                        Text.fontColor(this.listNodeDataSource.x7().fontColor);
                        Text.fontWeight(this.listNodeDataSource.x7().fontWeight);
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
        this.setImageSources(this.viewLastIndex, a3.NORMAL);
        this.listNodeDataSource.i8(this.viewLastIndex, a3.NORMAL);
        this.nodeList[this.viewLastIndex].a6({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
        this.nodeList[this.viewLastIndex].fontColor = this.treeViewTheme.a4;
        this.listNodeDataSource.w7[this.viewLastIndex].a6({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
        this.listNodeDataSource.w7[this.viewLastIndex].fontColor = this.treeViewTheme.a4;
        this.listNodeDataSource.w7[this.viewLastIndex].r6(false);
        this.listNodeDataSource.w7[this.viewLastIndex].j4 =
            this.listNodeDataSource.w7[this.viewLastIndex].k6().v3?.source;
        this.listNodeDataSource.w7[this.viewLastIndex].y16 =
            this.listNodeDataSource.w7[this.viewLastIndex].k6().v3?.y16;
    }
    setImageSources(index, f17) {
        let g17 = this.nodeList[index];
        g17.r6(f17 === a3.SELECTED ||
            f17 === a3.EDIT || f17 === a3.FINISH_EDIT);
        if (g17.k6().w3 !== null && f17 !== a3.DRAG_INSERT &&
            f17 !== a3.FINISH_DRAG_INSERT) {
            g17.k6().w3?.j8(f17 === a3.SELECTED ||
                f17 === a3.FINISH_EDIT);
        }
        if (g17.k6().v3 !== null) {
            g17.k6().v3?.i8(f17);
        }
    }
    touchInner(m22, event) {
        this.viewLastIndex = this.listNodeDataSource.u9();
        let index = this.listNodeDataSource.findIndex(m22.e6());
        if (event.type === TouchType.Down) {
            if (index !== this.viewLastIndex) {
                this.clearLastIndexColor();
                this.listNodeDataSource.lastIndex = index;
                this.listNodeDataSource.h9(index);
            }
        }
        if (event.type === TouchType.Up) {
            this.listNodeDataSource.w7[index].r6(true);
            this.listNodeDataSource.i8(index, a3.SELECTED);
            if (this.listNodeDataSource.w7[index].k6().v3 !== null) {
                this.listNodeDataSource.w7[index].j4 = this.listNodeDataSource.w7[index].k6().v3?.source;
                this.listNodeDataSource.w7[index].y16 = this.listNodeDataSource.w7[index].k6().v3?.y16;
            }
            if (index !== this.viewLastIndex) {
                this.clearLastIndexColor();
                this.listNodeDataSource.lastIndex = index;
                this.listNodeDataSource.h9(index);
            }
            this.viewLastIndex = index;
        }
        if (this.listNodeDataSource.u9() !== -1 && index !== this.listNodeDataSource.u9()) {
            this.listNodeDataSource.v9(u2.WARNINGS, v2.NONE, false, this.listNodeDataSource.u9());
            this.listNodeDataSource.w9(this.listNodeDataSource.u9(), t2.COMMIT_NODE);
        }
    }
    clickInner(l22) {
        this.viewLastIndex = this.listNodeDataSource.u9();
        let index = this.listNodeDataSource.findIndex(l22.e6());
        if (index !== this.viewLastIndex) {
            this.clearLastIndexColor();
            this.listNodeDataSource.lastIndex = index;
            this.listNodeDataSource.h9(index);
        }
        this.listNodeDataSource.w7[index].r6(true);
        this.listNodeDataSource.i8(index, a3.SELECTED);
        if (this.listNodeDataSource.w7[index].k6().v3 !== null) {
            this.listNodeDataSource.w7[index].j4 = this.listNodeDataSource.w7[index].k6().v3?.source;
            this.listNodeDataSource.w7[index].y16 = this.listNodeDataSource.w7[index].k6().v3?.y16;
        }
        if (index !== this.viewLastIndex) {
            this.clearLastIndexColor();
            this.listNodeDataSource.lastIndex = index;
            this.listNodeDataSource.h9(index);
        }
        this.viewLastIndex = index;
        if (this.listNodeDataSource.u9() !== -1 && index !== this.listNodeDataSource.u9()) {
            this.listNodeDataSource.v9(u2.WARNINGS, v2.NONE, false, this.listNodeDataSource.u9());
            this.listNodeDataSource.w9(this.listNodeDataSource.u9(), t2.COMMIT_NODE);
        }
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            List.create({});
            List.onDragMove((event, extraParams) => {
                if (this.isMultiPress) {
                    hilog.error(j16, i16, 'drag error, a item has been dragged');
                    return;
                }
                let b17 = i1;
                let flag = Math.floor(event.getY() /
                    (b17 / l1)) % l1 ? w2.DOWN_FLAG : w2.UP_FLAG;
                let index = JSON.parse(extraParams).insertIndex;
                let c17 = false;
                if (index >= this.listNodeDataSource.totalCount()) {
                    flag = w2.DOWN_FLAG;
                    index = this.listNodeDataSource.totalCount() - 1;
                    this.listNodeDataSource.getData(index)?.b7(true);
                    c17 = true;
                }
                else {
                    this.listNodeDataSource.getData(index)?.b7(false);
                }
                let d17 = this.listNodeDataSource.getData(index);
                let currentNodeId = d17?.e6();
                if (index !== this.listNodeDataSource.k8() && this.listNodeDataSource.l8()) {
                    let e17 = this.listNodeDataSource.m8(currentNodeId);
                    if (e17) {
                        this.listNodeDataSource.n8(index);
                        if (currentNodeId !== undefined) {
                            this.listNodeDataSource.o8(this.listNodeDataSource.findIndex(currentNodeId));
                        }
                        this.listNodeDataSource.p8(w2.NONE);
                        return;
                    }
                }
                this.listNodeDataSource.q8(index);
                this.listNodeDataSource.r8(flag, index - 1, c17, ObservedObject.GetRawObject(this.allParentNode));
                if (currentNodeId !== undefined && currentNodeId !== this.listNodeDataSource.s8()) {
                    this.listNodeDataSource.t8(this.listNodeDataSource.findIndex(currentNodeId), currentNodeId, index);
                }
            });
            List.onDragEnter((event, extraParams) => {
                if (this.listNodeDataSource.l8()) {
                    this.listNodeDataSource.u8(true);
                    let a17 = m1;
                    this.listNodeDataSource.v8(a17);
                }
            });
            List.onDragLeave((event, extraParams) => {
                this.listNodeDataSource.w8();
                this.listNodeDataSource.x8();
                this.listNodeDataSource.y8();
                let z16 = n1;
                this.listNodeDataSource.v8(z16);
                this.listNodeDataSource.u8(false);
                this.listNodeDataSource.z8();
            });
            List.onDrop((event, extraParams) => {
                this.accessibilityNodeType = q17.PLACE;
                this.listNodeDataSource.y8();
                let m16 = n1;
                this.listNodeDataSource.v8(m16);
                let n16 = JSON.parse(extraParams).insertIndex;
                let o16 = this.dropSelectedIndex;
                if (o16 - 1 > this.listNodeDataSource.totalCount() || o16 === undefined) {
                    hilog.error(j16, i16, 'drag error, currentNodeIndex is not found');
                    this.listNodeDataSource.u8(false);
                    return;
                }
                if (n16 === this.listNodeDataSource.totalCount()) {
                    hilog.info(j16, i16, 'need to insert into the position of the last line');
                    n16 -= 1;
                }
                let p16 = this.listNodeDataSource.getData(n16);
                if (p16 === undefined) {
                    return;
                }
                let q16 = p16.e6();
                if (!this.listNodeDataSource.a9() || !this.listNodeDataSource.l8()) {
                    this.listNodeDataSource.x8();
                    this.listNodeDataSource.b9(false);
                    this.listNodeDataSource.w8();
                    this.listNodeDataSource.c9();
                    this.listNodeDataSource.d9(q16);
                    this.listNodeDataSource.z8();
                    return;
                }
                let r16 = this.listNodeDataSource.e9();
                let s16 = p16.f6();
                let t16 = this.listNodeDataSource.s8();
                let u16 = this.listNodeDataSource.f9();
                let v16 = this.listNodeDataSource.m8(q16);
                if (v16) {
                    this.listNodeDataSource.x8();
                    this.listNodeDataSource.b9(false);
                    this.listNodeDataSource.w8();
                    this.listNodeDataSource.g9(n16);
                    this.listNodeDataSource.c9();
                    this.listNodeDataSource.u8(false);
                    let y16 = this.listNodeDataSource.findIndex(t16);
                    this.listNodeDataSource.h9(y16);
                    this.listNodeDataSource.i9(Event.DRAG, y16);
                    return;
                }
                if (this.listNodeDataSource.j9(t16) === z2.EXPAND) {
                    this.listNodeDataSource.k9(this.listNodeDataSource.findIndex(t16));
                }
                let flag = false;
                if (this.listNodeDataSource.j9(q16) === z2.COLLAPSE) {
                    let currentIndex = this.listNodeDataSource.findIndex(q16);
                    if (this.listNodeDataSource.w7[currentIndex].g7()) {
                        this.listNodeDataSource.k9(currentIndex);
                    }
                    flag = true;
                }
                this.listNodeDataSource.l9();
                if (r16 !== null && t16 !== q16) {
                    this.listNodeDataSource.m9(s16, q16, u16, t16, r16);
                    this.listNodeDataSource.w8();
                }
                else {
                    this.listNodeDataSource.w8();
                    this.listNodeDataSource.n9(t16);
                    this.listNodeDataSource.w8();
                }
                let w16 = this.listNodeDataSource.findIndex(this.listNodeDataSource.o9());
                this.listNodeDataSource.p9(w16);
                this.listNodeDataSource.x8();
                this.listNodeDataSource.c9();
                this.listNodeDataSource.u8(false);
                let x16 = this.listNodeDataSource.findIndex(t16);
                this.listNodeDataSource.h9(x16);
                this.listNodeDataSource.i9(Event.DRAG, x16);
                this.listNodeDataSource.b9(false);
                this.listNodeDataSource.z8();
                this.listNodeDataSource.w7[x16].fontColor = this.treeViewTheme.c4;
                if (this.viewLastIndex !== -1 && o16 !== this.viewLastIndex) {
                    this.listNodeDataSource.w7[this.viewLastIndex].k6().w3?.j8(false);
                    this.listNodeDataSource.w7[this.viewLastIndex].k6().w3?.q9(false);
                }
                this.listNodeDataSource.lastIndex = this.viewLastIndex;
                if (this.listNodeDataSource.w7[this.viewLastIndex]) {
                    if (this.listNodeDataSource.w7[this.viewLastIndex].k6().v3 !== null) {
                        this.listNodeDataSource.w7[this.viewLastIndex].k6().v3?.i8(a3.NORMAL);
                        this.listNodeDataSource.w7[this.viewLastIndex].j4 =
                            this.listNodeDataSource.w7[this.viewLastIndex].k6().v3?.source;
                        this.listNodeDataSource.w7[this.viewLastIndex].y16 =
                            this.listNodeDataSource.w7[this.viewLastIndex].k6().v3?.y16;
                    }
                }
                if (this.listNodeDataSource.w7[this.viewLastIndex]) {
                    this.listNodeDataSource.w7[this.viewLastIndex].a6({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                }
                this.listNodeDataSource.lastIndex = x16;
                let eventInfo = ({
                    type: 'requestFocusForAccessibility',
                    bundleName: getContext()?.abilityInfo?.bundleName,
                    triggerAction: 'common',
                    customId: `treeView_node${t16}`
                });
                accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                    setTimeout(() => {
                        this.accessibilityNodeType = q17.TEXT;
                    }, j17);
                    console.log(`test123 Succeeded in send event, eventInfo is ${JSON.stringify(eventInfo)}`);
                });
            });
        }, List);
        {
            const __lazyForEachItemGenFunction = _item => {
                const u15 = _item;
                {
                    const itemCreation2 = (elmtId, isInitialRender) => {
                        ListItem.create(() => { }, false);
                        ListItem.width('100%');
                        ListItem.height(u15.d6());
                        ListItem.padding({
                            start: LengthMetrics.resource(this.itemPadding.left),
                            end: LengthMetrics.resource(this.itemPadding.right)
                        });
                        ListItem.align(Alignment.Start);
                        ListItem.onDragStart((event, extraParams) => {
                            this.accessibilityNodeType = q17.LIFT;
                            if (this.listNodeDataSource.a9() || this.listNodeDataSource.l8() || this.isMultiPress) {
                                hilog.error(j16, i16, 'drag error, a item has been dragged');
                                return;
                            }
                            this.dropSelectedIndex = JSON.parse(extraParams).selectedIndex;
                            let e16 = JSON.parse(extraParams).selectedIndex;
                            let f16 = this.listNodeDataSource.getData(e16);
                            let g16 = u15.e6();
                            if (e16 >= this.listNodeDataSource.totalCount() || e16 === undefined) {
                                hilog.error(j16, i16, 'drag error, currentNodeIndex is not found in onDragStart');
                                return;
                            }
                            this.listNodeDataSource.b9(true);
                            this.listNodeDataSource.u8(true);
                            this.listNodeDataSource.r9(f16);
                            this.listNodeDataSource.s9(f16?.e6());
                            this.listNodeDataSource.t9(f16?.f6());
                            let h16 = m1;
                            this.listNodeDataSource.v8(h16);
                            this.listNodeDataSource.g9(e16);
                            if (g16 !== f16?.e6()) {
                                hilog.error(j16, i16, 'drag is too fast, it attribute a fault to OH');
                                this.listNodeDataSource.u8(false);
                                return;
                            }
                            let primaryTitle = f16.t6()?.primaryTitle === undefined ? '' :
                                f16.t6()?.primaryTitle;
                            let secondaryTitle = f16.t6()?.secondaryTitle === undefined ? '' :
                                f16.t6()?.secondaryTitle;
                            let h21 = this.listNodeDataSource.s16(primaryTitle);
                            let i21 = this.listNodeDataSource.s16(secondaryTitle);
                            let title = `${h21}, ${i21}`;
                            this.listNodeDataSource.q16(this.listNodeDataSource.getStringByName('treeview_accessibility_lift_node', title));
                            let b21 = [];
                            for (let p3 = 0; p3 < this.listNodeDataSource.w7.length; p3++) {
                                if (this.listNodeDataSource.w7[p3].f6() === -1) {
                                    b21.push(this.listNodeDataSource.w7[p3].e6());
                                }
                            }
                            this.allParentNode = b21;
                            let eventInfo = ({
                                type: 'requestFocusForAccessibility',
                                bundleName: getContext()?.abilityInfo?.bundleName,
                                triggerAction: 'common',
                                customId: `treeView_node_lift${g16}`
                            });
                            accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                                setTimeout(() => {
                                    this.accessibilityNodeType = q17.TEXT;
                                }, j17);
                            });
                            return { builder: () => {
                                this.draggingPopup.call(this, f16);
                            } };
                        });
                    };
                    const observedDeepRender = () => {
                        this.observeComponentCreation2(itemCreation2, ListItem);
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            Row.create();
                            Row.onTouch(this.isAccessibilityEnabled ? undefined : (event) => {
                                this.touchInner(u15, event);
                            });
                        }, Row);
                        {
                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                if (isInitialRender) {
                                    let componentCall = new i3(this, {
                                        item: u15,
                                        listNodeDataSource: this.listNodeDataSource,
                                        index: this.listNodeDataSource.findIndex(u15.e6()),
                                        listTreeViewMenu: this.listTreeViewMenu,
                                        callBackClick: () => this.clickInner(u15),
                                    }, undefined, elmtId, () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 1275, x9: 13 });
                                    ViewPU.create(componentCall);
                                    let paramsLambda = () => {
                                        return {
                                            item: u15,
                                            listNodeDataSource: this.listNodeDataSource,
                                            index: this.listNodeDataSource.findIndex(u15.e6()),
                                            listTreeViewMenu: this.listTreeViewMenu,
                                            callBackClick: () => this.clickInner(u15)
                                        };
                                    };
                                    componentCall.paramsGenerator_ = paramsLambda;
                                }
                                else {
                                    this.updateStateVarsOfChildByElmtId(elmtId, {
                                        item: u15
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
        this.y9 = -1;
        this.z9 = [];
        this.listNodeDataSource = new h3();
        this.a10 = true;
        this.treeViewTheme = e3.getInstance();
    }
    v7() {
        return this.listNodeDataSource;
    }
    b10() {
        let q15 = this.listNodeDataSource.c10();
        return this.listNodeDataSource.b10(q15);
    }
    d10() {
        let p15 = this.listNodeDataSource.c10();
        return this.listNodeDataSource.e10(p15);
    }
    removeNode() {
        let n15 = this.listNodeDataSource.c10();
        if (n15 < 0) {
            return;
        }
        let parentNodeId = this.listNodeDataSource.f10(n15);
        let o15 = this.listNodeDataSource.removeNode(n15, parentNodeId);
        this.listNodeDataSource.g10(t2.REMOVE_NODE, parentNodeId, o15);
        this.z9.splice(this.z9.indexOf(n15), 1);
        this.listNodeDataSource.lastIndex = -1;
    }
    modifyNode() {
        let m15 = this.listNodeDataSource.c10();
        this.listNodeDataSource.w9(m15, t2.MODIFY_NODE);
    }
    add(g15) {
        let h15 = this.listNodeDataSource.c10();
        if (h15 === this.listNodeDataSource.y9 || !this.listNodeDataSource.v6(h15)) {
            return;
        }
        let i15 = this.listNodeDataSource.h10(h15);
        this.z9.push(this.z9[this.z9.length - 1] + 1);
        let j15 = this.z9[this.z9.length - 1];
        let k15 = this.listNodeDataSource.addNode(h15, j15, {
            isFolder: i15.isFolder,
            icon: i15.icon,
            v16: i15.v16,
            selectedIcon: i15.selectedIcon,
            w16: i15.w16,
            editIcon: i15.editIcon,
            x16: i15.x16,
            primaryTitle: '新建文件夹',
            container: i15.container,
            secondaryTitle: i15.secondaryTitle,
        }, g15);
        if (!k15) {
            return;
        }
        this.listNodeDataSource.g10(t2.ADD_NODE, h15, [j15]);
        this.listNodeDataSource.v9(u2.WARNINGS, v2.NONE, false, this.listNodeDataSource.u9());
        this.listNodeDataSource.w9(this.listNodeDataSource.u9(), t2.COMMIT_NODE);
        this.listNodeDataSource.w7[this.listNodeDataSource.u9()].o5(this.treeViewTheme.a4);
        let l15 = this.listNodeDataSource.findIndex(j15);
        this.listNodeDataSource.h9(l15);
        this.listNodeDataSource.i9(Event.TOUCH_UP, l15);
    }
    addNode(nodeParam) {
        if (nodeParam === undefined) {
            this.add(this.a10);
            return this;
        }
        else {
            let e15 = false;
            if (nodeParam.primaryTitle !== undefined &&
                !this.listNodeDataSource.i10(nodeParam.primaryTitle.toString())) {
                throw new Error('ListTreeNode[addNode]: ' +
                    'The directory name cannot contain the following characters\ /: *? "< > | or exceeds the maximum length.');
                return this;
            }
            if (nodeParam.primaryTitle === null && nodeParam.icon === null) {
                throw new Error('ListTreeNode[addNode]: ' +
                    'The icon and directory name cannot be empty at the same time.');
                return this;
            }
            if (nodeParam.currentNodeId === this.y9 || nodeParam.currentNodeId === null) {
                throw new Error('ListTreeNode[addNode]: currentNodeId can not be -1 or null.');
                return this;
            }
            if (nodeParam.currentNodeId !== undefined) {
                this.z9.push(nodeParam.currentNodeId);
            }
            if (nodeParam.parentNodeId !== undefined) {
                if (nodeParam.currentNodeId !== undefined) {
                    e15 =
                        this.listNodeDataSource.addNode(nodeParam.parentNodeId, nodeParam.currentNodeId, nodeParam, this.a10);
                }
            }
            if (!e15) {
                return this;
            }
            if (!this.a10 && nodeParam.parentNodeId !== undefined) {
                let f15 = this.z9[this.z9.length - 1];
                this.listNodeDataSource.g10(t2.ADD_NODE, nodeParam.parentNodeId, [f15]);
            }
            return this;
        }
    }
    refreshNode(parentId, parentSubTitle, d15) {
        this.listNodeDataSource.j10(parentId, parentSubTitle, d15);
    }
    buildDone() {
        this.listNodeDataSource.k10();
        this.listNodeDataSource.l10();
        this.listNodeDataSource.m10();
        m(this.z9);
        this.a10 = false;
    }
}
class g3 {
    constructor() {
        this.n10 = [];
    }
    totalCount() {
        return 0;
    }
    getData(index) {
        return undefined;
    }
    registerDataChangeListener(listener) {
        if (this.n10.indexOf(listener) < 0) {
            this.n10.push(listener);
        }
    }
    unregisterDataChangeListener(listener) {
        const pos = this.n10.indexOf(listener);
        if (pos >= 0) {
            this.n10.splice(pos, 1);
        }
    }
    z8() {
        this.n10.forEach(listener => {
            listener.onDataReloaded();
        });
    }
    o10(index) {
        this.n10.forEach(listener => {
            listener.onDataAdd(index);
        });
    }
    g9(index) {
        if (index === undefined) {
            return;
        }
        this.n10.forEach(listener => {
            listener.onDataChange(index);
        });
    }
    p10(index) {
        this.n10.forEach(listener => {
            listener.onDataDelete(index);
        });
    }
    q10(from, to) {
        this.n10.forEach(listener => {
            listener.onDataMove(from, to);
        });
    }
}
function i(t14, count, u14, v14) {
    let taskId = setTimeout(() => {
        v14.forEach((parentNodeId) => {
            j(parentNodeId, u14, t14, count);
        });
        clearTimeout(taskId);
    }, m2);
}
function j(parentNodeId, q14, r14, count) {
    let s14 = parentNodeId;
    while (s14 >= 0) {
        if (q14.has(s14)) {
            let parent = q14.get(s14);
            parent.o6().r10 =
                r14 ? parent.o6().r10 + count : parent.o6().r10 - count;
            s14 = parent.parentNodeId;
        }
        else {
            hilog.error(j16, i16, 'updateParentChildNumHandler: parent node not found');
            break;
        }
    }
}
function m(n14) {
    let taskId = setTimeout(() => {
        n14.sort((a, b) => a - b);
        clearTimeout(taskId);
    }, m2);
}
class h3 extends g3 {
    constructor() {
        super();
        this.y9 = -1;
        this.s10 = new j3(d3);
        this.t10 = 50;
        this.MAX_CN_LENGTH = 254;
        this.MAX_EN_LENGTH = 255;
        this.INITIAL_INVALID_VALUE = -1;
        this.w7 = [];
        this.u10 = [];
        this.v10 = new Map();
        this.w10 = new Map();
        this.lastIndex = -1;
        this.x10 = -1;
        this.y10 = -1;
        this.z10 = -1;
        this.a11 = new Map();
        this.b11 = new Map();
        this.c11 = new Map();
        this.d11 = false;
        this.appEventBus = TreeListenerManager.getInstance().getTreeListener();
        this.e11 = false;
        this.f11 = false;
        this.g11 = this.INITIAL_INVALID_VALUE;
        this.h11 = this.INITIAL_INVALID_VALUE;
        this.i11 = null;
        this.j11 = 1;
        this.k11 = this.INITIAL_INVALID_VALUE;
        this.l11 = this.INITIAL_INVALID_VALUE;
        this.n11 = this.INITIAL_INVALID_VALUE;
        this.o11 = this.INITIAL_INVALID_VALUE;
        this.p11 = this.INITIAL_INVALID_VALUE;
        this.q11 = this.INITIAL_INVALID_VALUE;
        this.r11 = this.INITIAL_INVALID_VALUE;
        this.s11 = this.INITIAL_INVALID_VALUE;
        this.t11 = this.INITIAL_INVALID_VALUE;
        this.u11 = this.INITIAL_INVALID_VALUE;
        this.v11 = this.INITIAL_INVALID_VALUE;
        this.w11 = this.INITIAL_INVALID_VALUE;
        this.x11 = new Map();
        this.flag = w2.NONE;
        this.y11 = this.INITIAL_INVALID_VALUE;
        this.z11 = '';
        this.a12 = '';
        this.b12 = this.INITIAL_INVALID_VALUE;
        this.c12 = this.INITIAL_INVALID_VALUE;
        this.d12 = this.INITIAL_INVALID_VALUE;
        this.treeViewTheme = e3.getInstance();
        this.e12 = [];
        this.f12 = {
            g12: s1,
            h12: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_emphasize'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            xOffset: t1,
            i12: u1,
            j12: v1,
            k12: w1,
        };
        this.l12 = {
            y7: { minWidth: e2, maxWidth: f2 },
            d8: {
                e8: g2,
                g8: h2,
                f8: i2,
                h8: j2,
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
            fontColor: this.treeViewTheme.a4,
            fontSize: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            fontWeight: FontWeight.Regular,
            b8: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_alpha_content_fourth'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }
        };
        this.subTitle = {
            n12: this.treeViewTheme.b4,
            o12: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_primary_contrary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            fontSize: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            fontWeight: FontWeight.Regular,
            margin: { left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } }
        };
        this.s10.b5 = -1;
        this.v10.set(-1, this.s10);
        this.w10.set(-1, d3);
    }
    p12(index) {
        if (index < 0 || index >= this.w7.length) {
            hilog.error(j16, i16, 'check index fail');
            return false;
        }
        return true;
    }
    q12(index, color) {
        if (!this.p12(index)) {
            return;
        }
        this.w7[index].a6(color);
        this.w7[index].n6(false);
    }
    b6(index) {
        return this.w7[index].b6();
    }
    r12(index, m14) {
        if (this.w7[index].j6()) {
            this.w7[index].n6(m14);
        }
    }
    i8(index, k14) {
        if (!this.p12(index)) {
            return;
        }
        let l14 = this.w7[index];
        l14.r6(k14 === a3.SELECTED ||
            k14 === a3.EDIT || k14 === a3.FINISH_EDIT);
        if (l14.k6().w3 !== null && k14 !== a3.DRAG_INSERT &&
            k14 !== a3.FINISH_DRAG_INSERT) {
            l14.k6().w3?.j8(k14 === a3.SELECTED ||
                k14 === a3.FINISH_EDIT);
        }
        if (l14.k6().v3 !== null) {
            l14.k6().v3?.i8(k14);
        }
    }
    s12(index, i14) {
        let j14 = this.w7[index];
        if (j14.k6().x3 !== undefined) {
            j14.k6().x3 = q3.t12(i14, this.a11.get(j14.e6()), j14.k6().x3?.type);
        }
    }
    u12() {
        if (!this.p12(this.lastIndex)) {
            return;
        }
        this.i8(this.lastIndex, a3.NORMAL);
        this.q12(this.lastIndex, this.w7[this.lastIndex].l6().normal);
        this.r12(this.lastIndex, false);
        this.g9(this.b11.get(this.w7[this.lastIndex].e6()));
    }
    v12() {
        let index = 0;
        this.b11.clear();
        this.c11.clear();
        this.u10.splice(0, this.u10.length);
        for (let h14 = 0; h14 < this.w7.length; h14++) {
            this.c11.set(this.w7[h14].e6(), h14);
            if (this.w7[h14].j6()) {
                this.b11.set(this.w7[h14].e6(), index++);
                this.u10.push(this.w7[h14]);
            }
        }
    }
    w12(e14) {
        if (e14 >= this.w7.length) {
            hilog.error(j16, i16, 'changeNodeStatus clickIndex error.');
            return;
        }
        let f14 = e14;
        let g14 = this.w7[e14].e6();
        if (this.a11.get(g14) === z2.EXPAND) {
            this.a11.set(g14, z2.COLLAPSE);
            this.w7[f14].k6().x3 = q3.x12(z2.COLLAPSE, this.w7[f14].k6().x3?.y12);
        }
        else if (this.a11.get(g14) === z2.COLLAPSE) {
            this.a11.set(g14, z2.EXPAND);
            this.w7[f14].k6().x3 = q3.x12(z2.EXPAND, this.w7[f14].k6().x3?.y12);
        }
    }
    z12(v13, w13) {
        if (v13 >= this.w7.length) {
            hilog.error(j16, i16, 'handleExpandAndCollapse clickIndex error.');
            return;
        }
        let x13 = v13;
        let y13 = this.w7[x13].e6();
        if (!this.a11.has(y13)) {
            return;
        }
        let z13 = this.a11.get(y13);
        if (this.w7[x13].o6().a13 && z13 === z2.COLLAPSE) {
            for (let d14 = 0; d14 < this.w7[x13].o6().r10; d14++) {
                if (this.w7[x13 + 1 + d14] === undefined) {
                    return;
                }
                this.w7[x13 + 1 + d14].i6(false);
                this.w7[x13 + 1 + d14].c6(h1);
            }
            this.v12();
            this.z8();
            return;
        }
        let a14 = new Array(this.w7[x13].o6().b13);
        a14[0] = x13 + 1;
        let index = 1;
        while (index < this.w7[x13].o6().b13) {
            a14[index] = a14[index - 1] + this.w7[a14[index - 1]].o6().r10 + 1;
            index++;
        }
        if (z13 === z2.EXPAND) {
            for (let b14 = 0; b14 < a14.length; b14++) {
                if (this.w7[a14[b14]] === undefined) {
                    return;
                }
                this.w7[a14[b14]].i6(true);
                this.w7[a14[b14]].c6(i1);
                let c14 = this.w7[a14[b14]].e6();
                if (this.a11.get(c14) === z2.EXPAND) {
                    this.z12(a14[b14], false);
                }
            }
        }
        a14 = null;
        if (w13) {
            this.v12();
            this.z8();
        }
    }
    m10() {
        i(true, 1, this.v10, this.e12);
    }
    c13(u13) {
        u13.splice(0, u13.length);
        this.b11.clear();
        this.u10.splice(0, this.u10.length);
        this.c11.clear();
        this.x11.clear();
    }
    d13(o13, p13, q13) {
        let index = 0;
        let r13 = 0;
        this.c13(o13);
        try {
            this.e13((node) => {
                if (node.f13() >= 0 && this.w10.has(node.f13())) {
                    let t13 = new f3(node, this.w10.get(node.f13()));
                    t13.m5(node.o6().a13);
                    o13.push(t13);
                    this.c11.set(t13.e6(), r13++);
                    index = this.g13(t13, index);
                }
                return false;
            }, this.s10, p13, q13);
        }
        catch (err) {
            hilog.error(j16, i16, 'traverseSectionNodeDF function callbacks error.');
            this.c13(o13);
        }
    }
    g13(n13, index) {
        if (n13.o6().a13) {
            this.a11.set(n13.e6(), z2.COLLAPSE);
        }
        if (n13.j6()) {
            this.b11.set(n13.e6(), index++);
            this.u10.push(n13);
        }
        if (n13.v6()) {
            if (n13.t6().secondaryTitle !== undefined) {
                this.x11.set(n13.e6(), n13.t6().secondaryTitle);
            }
            else {
                this.x11.set(n13.e6(), '');
            }
        }
        return index;
    }
    l10() {
        let j13 = setTimeout(() => {
            let l13 = [];
            this.d13(l13, 0);
            this.w7.splice(0, this.w7.length);
            this.w7.push(...l13);
            this.w7.forEach((value, index) => {
                this.p10(index);
                this.o10(index);
            });
            clearTimeout(j13);
        }, m2);
    }
    k10() {
        this.d13(this.w7, 0, 1);
    }
    h9(index) {
        this.x10 = index;
    }
    c10() {
        if (!this.p12(this.x10)) {
            return -1;
        }
        return this.w7[this.x10].e6();
    }
    k9(u12) {
        this.w12(u12);
        this.z12(u12, true);
    }
    l13() {
        return this.d11;
    }
    u9() {
        return this.lastIndex;
    }
    findIndex(currentNodeId) {
        let t12 = -1;
        if (this.c11.has(currentNodeId)) {
            t12 = this.c11.get(currentNodeId);
        }
        return t12;
    }
    n13(index) {
        if (!this.p12(index)) {
            return;
        }
        this.i8(index, a3.NORMAL);
        this.q12(index, this.w7[index].l6().normal);
        this.r12(index, false);
        this.g9(this.b11.get(this.w7[index].e6()));
    }
    i9(event, index) {
        if (this.f11) {
            return;
        }
        if (!this.p12(index)) {
            return;
        }
        if (event === Event.TOUCH_DOWN || event === Event.TOUCH_UP || event === Event.MOUSE_BUTTON_RIGHT) {
            if (index !== this.lastIndex) {
                this.u12();
            }
        }
        this.o13(index, event);
    }
    o13(index, event) {
        let r12 = this.b11.get(this.w7[index].e6());
        switch (event) {
            case Event.TOUCH_DOWN:
                this.d11 = true;
                this.q12(index, this.w7[index].l6().i5);
                this.g9(r12);
                break;
            case Event.TOUCH_UP: {
                this.p13(index, r12);
                break;
            }
            case Event.HOVER:
                if (this.b6(index) !== this.w7[index].l6().selected) {
                    this.q12(index, this.w7[index].l6().h5);
                    this.g9(r12);
                }
                break;
            case Event.HOVER_OVER:
                if (this.b6(index) !== this.w7[index].l6().selected) {
                    this.q12(index, this.w7[index].l6().normal);
                    this.g9(r12);
                }
                break;
            case Event.FOCUS:
                this.r12(index, true);
                this.g9(r12);
                break;
            case Event.BLUR:
                this.r12(index, false);
                this.g9(r12);
                break;
            case Event.MOUSE_BUTTON_RIGHT:
                this.lastIndex = index;
                this.q13();
                break;
            case Event.DRAG:
                this.d11 = false;
                let s12 = this.w7[index];
                this.i8(index, a3.SELECTED);
                this.lastIndex = index;
                this.q12(index, s12.l6().selected);
                this.g9(r12);
                break;
            default:
                break;
        }
    }
    p13(index, p12) {
        if (this.e11) {
            this.e11 = false;
        }
        this.d11 = false;
        let q12 = this.w7[index];
        this.i8(index, a3.SELECTED);
        q12.o5(this.treeViewTheme.a4);
        this.lastIndex = index;
        this.q12(index, q12.l6().selected);
        this.g9(p12);
    }
    k13(l12, operation) {
        if (operation === t2.MODIFY_NODE) {
            let n12 = this.w7[this.y10];
            let o12 = {
                currentNodeId: n12?.e6(),
                parentNodeId: n12?.f6(),
            };
            this.appEventBus.emit(TreeListenType.NODE_MODIFY, o12);
        }
        else if (operation === t2.ADD_NODE) {
            let m12 = this.w7[l12];
            if (m12 === undefined) {
                return;
            }
            let icon = (m12.k6().v3 !== undefined) ?
                m12.k6().v3?.source : undefined;
            let selectedIcon = (m12.k6().v3 !== undefined) ?
                m12.k6().v3?.r13 : undefined;
            let editIcon = (m12.k6().v3 !== undefined) ?
                m12.k6().v3?.s13 : undefined;
            let callbackParam = {
                currentNodeId: m12?.e6(),
                parentNodeId: m12?.f6(),
            };
            this.appEventBus.emit(TreeListenType.NODE_ADD, callbackParam);
        }
    }
    q13() {
        if (this.y10 !== -1) {
            this.i8(this.y10, a3.FINISH_EDIT);
            this.s12(this.y10, a3.FINISH_EDIT);
            this.w7[this.y10].h7(false);
            this.w7[this.y10].y5(false);
            this.k13(this.y10, this.j13);
            this.g9(this.y10);
        }
    }
    w9(h12, operation) {
        let index = -1;
        if (h12 === -1) {
            return;
        }
        if (operation === t2.MODIFY_NODE) {
            for (let k12 = 0; k12 < this.w7.length; k12++) {
                if (this.w7[k12]?.e6() === h12) {
                    index = k12;
                    break;
                }
            }
            let j12 = this.w7[index];
            if (j12 === undefined) {
                return;
            }
            j12.h7(true);
            if (j12.k6().w3 === null) {
                return;
            }
            this.j13 = t2.MODIFY_NODE;
            j12.y5(true);
            this.i8(index, a3.EDIT);
            this.s12(index, a3.EDIT);
            this.y10 = index;
            if (j12.k6().inputText) {
                if (j12.k6().x3 !== null) {
                    j12.k6().inputText.rightMargin = { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_paragraph_margin_xs'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                }
                else {
                    j12.k6().inputText.rightMargin = { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_elements_margin_horizontal_m'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                }
            }
            this.g9(this.b11.get(h12));
        }
        index = h12;
        if (operation === t2.COMMIT_NODE) {
            let i12 = this.w7[index];
            if (i12 === undefined) {
                return;
            }
            i12.y5(false);
            i12.h7(false);
            this.i8(index, a3.FINISH_EDIT);
            this.s12(index, a3.FINISH_EDIT);
            this.k13(this.y10, this.j13);
            this.g9(this.b11.get(i12?.e6()));
        }
    }
    v9(d12, e12, isShow, index) {
        if (!this.p12(index)) {
            return;
        }
        let f12 = this.w7[index];
        if (f12 === undefined) {
            return;
        }
        f12.r5(isShow);
        let g12 = this.b11.get(f12.e6());
        if (!isShow) {
            this.g9(g12);
            return;
        }
        if (d12 === u2.HINTS) {
            if (f12.k6().w3 !== null) {
                f12.u5(f12.k6().w3?.title);
            }
            else {
                f12.u5('');
                f12.r5(false);
            }
            f12.s5(false);
            f12.t5({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            f12.v5(this.treeViewTheme.b4);
        }
        else if (d12 === u2.WARNINGS) {
            if (f12.k6().inputText !== null) {
                if (e12 === v2.INVALID_ERROR) {
                    f12.u5('invalid error');
                }
                else if (e12 === v2.LENGTH_ERROR) {
                    f12.u5('length error');
                }
                f12.s5(true);
                f12.t5({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_help_tip_bg'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                f12.v5({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_hint_contrary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            }
        }
        this.g9(g12);
    }
    t13(timeout, index) {
        if (!this.p12(index)) {
            return;
        }
        if (this.w7[index].k6().w3 !== null) {
            this.w7[index].k6().w3.u13 = timeout;
        }
        let c12 = this.b11.get(this.w7[index].e6());
        this.g9(c12);
    }
    v13(index, text) {
        this.y10 = index;
        if (this.w7[index].k6().w3 !== null) {
            this.w7[index].k6().w3.title = text;
        }
    }
    totalCount() {
        return this.b11.size;
    }
    getData(index) {
        if (index < 0 || index >= this.u10.length) {
            return undefined;
        }
        return this.u10[index];
    }
    w13(index, data) {
        if (!this.p12(index)) {
            return;
        }
        this.w7.splice(index, 0, data);
        this.c11.set(data.e6(), index);
        this.v12();
        this.o10(index);
    }
    x13(data) {
        this.w7.push(data);
        this.c11.set(data.e6(), this.w7.length);
        this.v12();
        this.o10(this.w7.length - 1);
    }
    b9(b12) {
        this.e11 = b12;
    }
    l8() {
        return this.e11;
    }
    u8(a12) {
        this.f11 = a12;
    }
    a9() {
        return this.f11;
    }
    r9(z11) {
        if (z11 === undefined) {
            return;
        }
        this.i11 = z11;
    }
    e9() {
        return this.i11;
    }
    t9(y11) {
        if (y11 === undefined) {
            return;
        }
        this.h11 = y11;
    }
    f9() {
        return this.h11;
    }
    s8() {
        return this.g11;
    }
    s9(x11) {
        if (x11 === undefined) {
            return;
        }
        this.g11 = x11;
    }
    v8(w11) {
        this.j11 = w11;
    }
    y13(item) {
        return item.e6() === this.s8() ? this.j11 : 1;
    }
    x7() {
        return this.l12;
    }
    q8(v11) {
        this.k11 = v11;
    }
    k8() {
        return this.k11;
    }
    m8(s11) {
        if (this.i11 === null || s11 === undefined) {
            return false;
        }
        let t11 = this.i11.u6();
        let parentId = t11.currentNodeId;
        let u11 = this.v10.get(s11)?.parentNodeId;
        while (u11 !== undefined && u11 !== -1) {
            if (parentId === u11) {
                return true;
            }
            else {
                u11 = this.v10.get(u11)?.parentNodeId;
            }
        }
        return false;
    }
    n8(r11) {
        this.n11 = r11;
    }
    z13() {
        return this.n11;
    }
    o8(currentIndex) {
        if (this.l11 !== this.INITIAL_INVALID_VALUE && this.b11.has(this.l11)) {
            let index = this.b11.get(this.l11);
            this.w7.forEach((value) => {
                if (value.e6() === this.l11) {
                    value.w6(false);
                    return;
                }
            });
            this.g9(index);
        }
        if ((this.t11 !== this.INITIAL_INVALID_VALUE &&
            this.u11 !== this.t11)) {
            clearTimeout(this.t11);
            if (this.v11 !== this.INITIAL_INVALID_VALUE) {
                this.a14(this.v11);
                let index = this.b11
                    .get(this.w7[this.v11].e6());
                this.g9(index);
            }
            this.u11 = this.t11;
        }
        this.t11 = this.s11;
        this.v11 = currentIndex;
        if ((this.q11 !== this.INITIAL_INVALID_VALUE &&
            this.r11 !== this.q11)) {
            clearTimeout(this.q11);
            this.r11 = this.q11;
        }
        this.q11 = this.p11;
        this.o11 = this.INITIAL_INVALID_VALUE;
    }
    a14(currentIndex) {
        if (!this.p12(currentIndex)) {
            return;
        }
        this.q12(currentIndex, this.w7[currentIndex].l6().normal);
        this.b14(currentIndex, false);
        this.i8(currentIndex, a3.FINISH_DRAG_INSERT);
        this.s12(currentIndex, a3.FINISH_DRAG_INSERT);
        this.w7[currentIndex].f7(false);
    }
    b14(index, p11) {
        if (this.w7[index].k6().w3 && this.w7[index].w5()) {
            this.w7[index].k6().w3?.q9(p11);
        }
    }
    g16(j5) {
        let k3 = [];
        while (j5 !== -1) {
            if (j5 === undefined) {
                return '';
            }
            let m5 = this.f10(j5);
            let l5 = this.v10.get(m5);
            if (l5 === undefined || m5 === undefined) {
                return '';
            }
            let primaryTitle = this.a15(l5).t6()?.primaryTitle === undefined
                ? '' : this.a15(l5).t6().primaryTitle;
            let secondaryTitle = this.a15(l5).t6()?.secondaryTitle === undefined
                ? '' : this.a15(l5).t6().secondaryTitle;
            let f21 = this.s16(primaryTitle);
            let g21 = this.s16(secondaryTitle);
            k3.unshift(`${f21}, ${g21}`);
            j5 = l5.currentNodeId;
        }
        return k3.join(',');
    }
    p16(w20) {
        if (w20 === undefined) {
            return '';
        }
        let x3 = this.f10(w20);
        if (x3 === -1) {
            let e5 = [];
            let f5 = this.v10.get(w20);
            if (f5 === undefined || x3 === undefined) {
                return '';
            }
            let primaryTitle = this.a15(f5).t6()?.primaryTitle === undefined
                ? '' : this.a15(f5).t6().primaryTitle;
            let secondaryTitle = this.a15(f5).t6()?.secondaryTitle === undefined
                ? '' : this.a15(f5).t6().secondaryTitle;
            let g5 = this.s16(primaryTitle);
            let k5 = this.s16(secondaryTitle);
            e5.unshift(`${g5}, ${k5}`);
            return e5.join(',');
        }
        else {
            let y3 = [];
            while (w20 !== -1) {
                if (w20 === undefined) {
                    return '';
                }
                let z3 = this.f10(w20);
                let a4 = this.v10.get(z3);
                if (a4 === undefined || z3 === undefined) {
                    return '';
                }
                let primaryTitle = this.a15(a4).t6()?.primaryTitle === undefined
                    ? '' : this.a15(a4).t6().primaryTitle;
                let secondaryTitle = this.a15(a4).t6()?.secondaryTitle === undefined
                    ? '' : this.a15(a4).t6().secondaryTitle;
                let b4 = this.s16(primaryTitle);
                let c4 = this.s16(secondaryTitle);
                y3.unshift(`${b4}, ${c4}`);
                w20 = a4.currentNodeId;
            }
            return y3.join(',');
        }
    }
    h16(q20, r20, v3) {
        this.g16(v3);
        if (r20 === undefined || v3 === undefined) {
            return;
        }
        let parentId = this.f10(v3);
        let h5 = q20.indexOf(v3) + 2;
        let t20 = this.b10(parentId);
        let u20 = t20.map(item => item.itemId);
        let i5 = u20.indexOf(v3) + 2;
        if (parentId === -1 && this.j9(r20) === z2.COLLAPSE ||
            parentId === -1 && this.j9(r20) === undefined) {
            this.q16(this.getStringByName('treeview_accessibility_move_node_parent', h5));
        }
        else if (this.j9(r20) === z2.EXPAND) {
            this.q16(this.getStringByName('treeview_accessibility_move_node_child', this.g16(v3), 1));
        }
        else if (parentId !== -1) {
            this.q16(this.getStringByName('treeview_accessibility_move_node_child', this.g16(v3), i5));
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
    q16(textAnnouncedForAccessibility) {
        let eventInfo = ({
            type: 'announceForAccessibility',
            bundleName: getContext()?.abilityInfo?.bundleName,
            triggerAction: 'common',
            textAnnouncedForAccessibility: textAnnouncedForAccessibility
        });
        accessibility.sendAccessibilityEvent(eventInfo);
    }
    s16(resource) {
        let x20 = '';
        try {
            if (typeof resource === 'string') {
                x20 = resource;
            }
            else {
                x20 = getContext()?.resourceManager?.getStringSync(resource?.id);
            }
        }
        catch (error) {
            let code = error.code;
            let message = error.message;
            hilog.error(0x3900, 'Ace', `treeView getAccessibleTitleText error, code: ${code}, message: ${message}`);
        }
        return x20;
    }
    r8(flag, index, k11, l20) {
        let l11 = (this.n11 !== index || this.flag !== flag) ? true : false;
        this.n11 = index;
        if ((l11 || k11) && this.e11) {
            this.flag = flag;
            let currentNodeId = this.getData(index)?.e6();
            let m11 = this.getData(index)?.a7();
            if (currentNodeId !== undefined) {
                m11 = (this.a11.get(currentNodeId) === z2.EXPAND &&
                    this.flag === w2.DOWN_FLAG) ? (m11 ? m11 + 1 : undefined) : m11;
                if (this.l11 !== this.INITIAL_INVALID_VALUE &&
                this.b11.has(this.l11)) {
                    let n11 = this.b11.get(this.l11);
                    this.w7.forEach((value) => {
                        if (value.e6() === this.l11) {
                            value.w6(false);
                        }
                    });
                    this.g9(n11);
                }
                let u3 = this.getData(index - 1)?.e6();
                let m20 = this.getData(index + 2)?.e6();
                let n20 = this.getData(index + 1)?.e6();
                let o20 = this.v10.get(n20);
                if (this.flag === w2.DOWN_FLAG && index < this.totalCount() - 1) {
                    this.getData(index)?.w6(false);
                    this.getData(index + 1)?.w6(true);
                    this.getData(index)?.d7(false);
                    this.getData(index + 1)?.y6(m11);
                    this.g9(index);
                    this.g9(index + 1);
                    this.l11 = this.getData(index + 1)?.e6();
                    let p20 = this.v10.get(n20);
                    if (!p20?.p6.a13) {
                        this.h16(l20, n20, n20);
                    }
                    else {
                        this.h16(l20, n20, m20);
                    }
                }
                else if (this.flag === w2.UP_FLAG && index < this.totalCount() - 1) {
                    this.getData(index)?.w6(true);
                    this.getData(index + 1)?.w6(false);
                    this.getData(index)?.d7(false);
                    this.getData(index)?.y6(m11);
                    this.g9(index);
                    this.g9(index + 1);
                    this.l11 = this.getData(index)?.e6();
                    if (o20?.p6.a13 && o20?.parentNodeId !== -1) {
                        this.h16(l20, n20, n20);
                    }
                    else if (o20?.p6.a13 && o20?.parentNodeId === -1) {
                        this.h16(l20, u3, n20);
                    }
                }
                else if (index >= this.totalCount() - 1) {
                    if (this.flag === w2.DOWN_FLAG) {
                        this.getData(index)?.w6(false);
                        this.getData(index)?.d7(true);
                    }
                    else {
                        this.getData(index)?.w6(true);
                        this.getData(index)?.d7(false);
                    }
                    this.getData(index)?.y6(m11);
                    this.g9(index);
                    this.l11 = this.getData(index)?.e6();
                }
            }
        }
    }
    t8(currentIndex, currentNodeId, b11) {
        let c11 = currentIndex !== this.o11 ? true : false;
        let d11 = this.getData(b11)?.c7();
        if (d11) {
            this.o11 = this.INITIAL_INVALID_VALUE;
        }
        else {
            this.o11 = currentIndex;
        }
        if (d11 || c11) {
            let e11 = !d11 && (!this.e11 ||
                (this.a11.get(currentNodeId) === z2.COLLAPSE && this.e11) ||
                (!this.a11.has(currentNodeId) && this.w7[currentIndex].v6()));
            if (e11) {
                this.q12(currentIndex, this.w7[currentIndex].l6().h5);
                this.g9(b11);
                let i11 = this.e11 ? 1000 : 0;
                let k22 = this.w7[currentIndex + 1].e6();
                let w3 = this.f10(currentNodeId);
                this.s11 = setTimeout(() => {
                    this.c14(currentIndex);
                    if (w3 === -1) {
                        this.q16(this.getStringByName('treeview_accessibility_move_node_child', this.p16(currentNodeId), 1));
                    }
                    else {
                        this.q16(this.getStringByName('treeview_accessibility_move_node_child', this.p16(k22), 1));
                    }
                }, i11);
            }
            if (d11 || (this.t11 !== this.INITIAL_INVALID_VALUE &&
                this.u11 !== this.t11)) {
                clearTimeout(this.t11);
                if (this.v11 !== this.INITIAL_INVALID_VALUE) {
                    this.a14(this.v11);
                    this.z8();
                }
                this.u11 = this.t11;
            }
            this.t11 = this.s11;
            this.v11 = currentIndex;
            if (!d11 && this.a11.get(currentNodeId) === z2.COLLAPSE) {
                let f11 = this.getData(b11)?.u6().children[0]?.currentNodeId;
                let g11 = 2000;
                this.p11 = setTimeout(() => {
                    this.a14(this.v11);
                    if (f11 !== undefined) {
                        this.d14(currentIndex, f11);
                    }
                }, g11);
            }
            if (d11 || (this.q11 !== this.INITIAL_INVALID_VALUE &&
                this.r11 !== this.q11)) {
                clearTimeout(this.q11);
                this.r11 = this.q11;
            }
            this.q11 = this.p11;
        }
    }
    c14(currentIndex) {
        this.w7.forEach((value) => {
            if (value.e6() === this.l11) {
                value.w6(false);
                value.d7(false);
                return;
            }
        });
        this.q12(currentIndex, this.w7[currentIndex].l6().j5);
        this.w7[currentIndex].f7(true);
        this.b14(currentIndex, true);
        this.i8(currentIndex, a3.DRAG_INSERT);
        this.s12(currentIndex, a3.DRAG_INSERT);
        this.z8();
    }
    d14(currentIndex, x10) {
        this.w7.forEach((value) => {
            if (value.e6() === this.l11) {
                value.w6(false);
                value.d7(false);
            }
        });
        this.w7.forEach((value) => {
            if (this.e11 && value.e6() === x10) {
                value.w6(true);
            }
        });
        this.w12(currentIndex);
        this.z12(currentIndex, true);
        this.l11 = x10;
    }
    w8() {
        if (this.l11 !== this.INITIAL_INVALID_VALUE && this.b11.has(this.l11)) {
            this.w7.forEach((value) => {
                if (value.e6() === this.l11) {
                    value.w6(false);
                    value.d7(false);
                    return;
                }
            });
            let index = this.b11.get(this.l11);
            this.g9(index);
        }
    }
    x8() {
        if (this.t11 !== this.INITIAL_INVALID_VALUE &&
            this.u11 !== this.t11) {
            clearTimeout(this.t11);
            if (this.v11 !== this.INITIAL_INVALID_VALUE) {
                this.a14(this.v11);
            }
        }
    }
    y8() {
        if (this.q11 !== this.INITIAL_INVALID_VALUE &&
            this.r11 !== this.q11) {
            clearTimeout(this.q11);
        }
    }
    e14(currentNodeId) {
        if (this.x11.has(currentNodeId)) {
            if (typeof this.x11.get(currentNodeId) === 'number') {
                return this.x11.get(currentNodeId)?.toString();
            }
            else {
                return this.x11.get(currentNodeId);
            }
        }
        else {
            return '';
        }
    }
    f14(currentNodeId) {
        return this.x11.has(currentNodeId);
    }
    c9() {
        this.v11 = this.INITIAL_INVALID_VALUE;
        this.o11 = this.INITIAL_INVALID_VALUE;
        this.k11 = this.INITIAL_INVALID_VALUE;
        this.g11 = this.INITIAL_INVALID_VALUE;
        this.flag = w2.NONE;
    }
    d9(v10) {
        this.x11.set(this.y11, this.z11);
        this.x11.set(v10, this.a12);
        this.g9(this.b11.get(this.y11));
        this.g9(this.b11.get(v10));
    }
    j10(s10, t10, u10) {
        this.y11 = s10;
        this.z11 = t10;
        this.a12 = u10;
    }
    g14() {
        return this.a12;
    }
    j9(currentNodeId) {
        return this.a11.get(currentNodeId);
    }
    o9() {
        return this.w11;
    }
    l9() {
        this.w7.forEach((value, index) => {
            if (index === this.v11) {
                this.w11 = value.e6();
            }
        });
    }
    n9(q10) {
        this.l11 = q10;
    }
    p9(p10) {
        this.v11 = p10;
    }
    m9(r9, s9, t9, u9, v9) {
        let w9 = [];
        let parentNodeId = r9;
        let currentNodeId = u9;
        let nodeParam = v9.t6();
        let x9 = null;
        let y9 = v9.u6();
        let z9 = false;
        let a10 = this.INITIAL_INVALID_VALUE;
        let b10 = this.INITIAL_INVALID_VALUE;
        let c10 = this.flag === w2.DOWN_FLAG ? true : false;
        b10 = this.h14(t9, u9);
        a10 = this.h14(r9, s9) + 1;
        if (r9 !== t9) {
            a10 = c10 ? a10 + 1 : a10;
        }
        else {
            if (a10 > b10) {
                a10 = c10 ? a10 : a10 - 1;
            }
            else {
                a10 = c10 ? a10 + 1 : a10;
            }
        }
        for (let o10 = 0; o10 < this.w7.length; o10++) {
            if (this.w7[o10].e6() === s9) {
                z9 = this.w7[o10].g7();
                if (this.flag === w2.DOWN_FLAG && this.a11.get(s9) === z2.EXPAND) {
                    parentNodeId = s9;
                    a10 = 0;
                }
                else if (this.flag === w2.UP_FLAG && this.a11.get(s9) ===
                z2.EXPAND &&
                    this.w7[o10].x6() === false) {
                    parentNodeId = s9;
                    a10 = 0;
                }
                else if (z9) {
                    parentNodeId = s9;
                    a10 = 0;
                }
                break;
            }
        }
        let callbackParam = {
            currentNodeId: currentNodeId,
            parentNodeId: parentNodeId,
            childIndex: a10,
        };
        this.appEventBus.emit(TreeListenType.NODE_MOVE, callbackParam);
        w9.push({ parentId: parentNodeId, i14: currentNodeId, data: nodeParam });
        let callback = (node, m10) => {
            if (node) {
                parentNodeId = node.parentNodeId;
                currentNodeId = node.currentNodeId;
                for (let n10 = 0; n10 < m10.length; n10++) {
                    if (m10[n10].e6() === currentNodeId) {
                        x9 = m10[n10];
                        break;
                    }
                }
                if (x9 === null) {
                    return false;
                }
                let nodeParam = x9.t6();
                if (parentNodeId !== t9) {
                    w9.push({ parentId: parentNodeId, i14: currentNodeId, data: nodeParam });
                }
                return false;
            }
            return false;
        };
        this.j14(callback, y9, this.w7);
        let d10 = this.removeNode(u9, t9);
        if (d10.length === 0) {
            return;
        }
        let e10 = s9;
        let isAfter = c10;
        if (this.a11.get(s9) === z2.EXPAND) {
            isAfter = false;
            this.w7.forEach((value) => {
                if (value.e6() === s9 && value.x6() === false) {
                    if (value.u6().children.length) {
                        e10 = value.u6().children[0].currentNodeId;
                    }
                    else {
                        e10 = this.INITIAL_INVALID_VALUE;
                    }
                }
            });
        }
        else if (!this.a11.get(s9) && z9) {
            this.a11.set(s9, z2.EXPAND);
        }
        let f10 = this.k14(w9[0].parentId, w9[0].i14, e10, isAfter, w9[0].data);
        if (!f10) {
            return;
        }
        for (let j10 = 1; j10 < w9.length; j10++) {
            let k10 = this.addNode(w9[j10].parentId, w9[j10].i14, w9[j10].data, false);
            if (!k10) {
                return;
            }
        }
        for (let i10 = 0; i10 < this.w7.length; i10++) {
            if (this.w7[i10].e6() === t9) {
                if (this.w7[i10].k6().x3 === null) {
                    this.w7[i10].z5(false);
                    this.a11.delete(t9);
                    break;
                }
            }
        }
        let g10 = [...this.w7];
        this.l14(g10);
    }
    l14(m9) {
        let index = 0;
        let n9 = 0;
        this.w7.splice(0, this.w7.length);
        this.b11.clear();
        this.u10.splice(0, this.u10.length);
        this.n14((node) => {
            let currentNodeId = node.currentNodeId;
            if (currentNodeId >= 0) {
                if (this.w10.has(currentNodeId)) {
                    let p9 = new f3(node, this.w10.get(currentNodeId));
                    p9.m5(node.o6().a13);
                    this.w7.push(p9);
                    this.c11.set(p9.e6(), n9++);
                    if (this.a11.get(currentNodeId) === z2.EXPAND) {
                        p9.k6().x3 = q3.x12(z2.EXPAND, p9.k6().x3?.y12);
                    }
                    else if (this.a11.get(currentNodeId) === z2.COLLAPSE) {
                        p9.k6().x3 = q3.x12(z2.COLLAPSE, p9.k6().x3?.y12);
                    }
                    for (let q9 = 0; q9 < m9.length; q9++) {
                        if (m9[q9].e6() === p9.e6()) {
                            p9.i6(m9[q9].j6());
                            p9.c6(m9[q9].d6());
                            if (p9.k6().w3 && p9.w5()) {
                                p9.k6().w3.title = m9[q9].k6().w3?.title;
                            }
                            break;
                        }
                    }
                    if (p9.j6()) {
                        this.b11.set(p9.e6(), index++);
                        this.u10.push(p9);
                    }
                }
            }
            return false;
        });
    }
    o14() {
        return this.f12;
    }
    p14(j9) {
        let k9 = this.b11.get(j9.e6()) - 1;
        if (k9 > this.INITIAL_INVALID_VALUE) {
            let l9 = this.getData(k9);
            return (j9.x6() === true && !j9.g7() && !l9?.g7()) ?
            Visibility.Visible : Visibility.Hidden;
        }
        else {
            return (j9.x6() === true && !j9.g7()) ?
            Visibility.Visible : Visibility.Hidden;
        }
    }
    q14() {
        return this.subTitle;
    }
    v6(i9) {
        if (this.b11.has(i9)) {
            return this.getData(this.b11.get(i9))?.v6();
        }
        return false;
    }
    r14(h9) {
        return h9 ? this.subTitle.o12 : this.treeViewTheme.b4;
    }
    h14(d9, e9) {
        let f9 = this.INITIAL_INVALID_VALUE;
        if (this.v10.has(d9)) {
            let node = this.v10.get(d9);
            if (node.f13() === d9) {
                node.children.forEach((value, index) => {
                    if (value.f13() === e9) {
                        f9 = index;
                        return;
                    }
                });
            }
        }
        return f9;
    }
    s14(c9) {
        this.b12 = c9;
    }
    t14() {
        return this.b12;
    }
    u14(b9) {
        this.c12 = b9;
    }
    v14() {
        return this.c12;
    }
    w14() {
        return this.d12;
    }
    p8(flag) {
        this.flag = flag;
    }
    n14(callback, root = this.s10) {
        let stack = [];
        let z8 = false;
        stack.unshift(root);
        let a9 = stack.shift();
        while (!z8 && a9) {
            z8 = callback(a9) === true;
            if (!z8) {
                stack.unshift(...a9.children);
                a9 = stack.shift();
            }
        }
    }
    e13(callback, root = this.s10, u8, v8) {
        let stack = [];
        let w8 = false;
        let x8 = false;
        stack.unshift(root);
        let y8 = stack.shift();
        while (!w8 && y8) {
            try {
                if (u8 !== undefined && y8.b5 < u8) {
                    x8 = true;
                }
                if (v8 !== undefined && y8.b5 > v8) {
                    x8 = true;
                }
                if (!x8) {
                    w8 = callback(y8);
                }
            }
            catch (err) {
                throw new Error('traverseSectionNodeDF function callbacks error');
            }
            if (!w8) {
                stack.unshift(...y8.children);
                y8 = stack.shift();
                x8 = false;
            }
        }
    }
    x14(s8, t8, count) {
        let parentNodeId = s8.parentNodeId;
        while (parentNodeId >= 0) {
            if (this.v10.has(parentNodeId)) {
                let parent = this.v10.get(parentNodeId);
                parent.o6().r10 =
                    t8 ? parent.o6().r10 + count : parent.o6().r10 - count;
                parentNodeId = parent.parentNodeId;
            }
            else {
                hilog.error(j16, i16, 'updateParentChildNum: parent node not found.');
                break;
            }
        }
    }
    f10(currentNodeId) {
        let current = new j3(d3);
        if (this.v10.has(currentNodeId)) {
            current = this.v10.get(currentNodeId);
        }
        return current.parentNodeId;
    }
    h13(b13, c13) {
        let d13 = [];
        if (b13.length === 0) {
            return;
        }
        let startIndex = undefined;
        for (let g13 = 0; g13 < b13.length; g13++) {
            if (this.b11.has(b13[g13])) {
                let i13 = this.b11.get(b13[g13]);
                d13.push(i13);
            }
            if (startIndex === undefined && this.c11.has(b13[g13])) {
                startIndex = this.c11.get(b13[g13]);
            }
            if (startIndex !== undefined) {
                let h13 = this.w7.splice(startIndex, 1);
                h13 = null;
            }
            if (this.a11.has(b13[g13])) {
                this.a11.delete(b13[g13]);
            }
        }
        d13.forEach((value) => {
            this.p10(value);
            this.g9(value);
        });
        if (c13.k6().x3 === null) {
            if (this.c11.has(c13.e6())) {
                let f13 = this.c11.get(c13.e6());
                this.w7[f13]?.z5(false);
            }
            this.a11.delete(c13.e6());
            this.g9(this.b11.get(c13.e6()));
        }
        let callbackParam = {
            currentNodeId: c13.e6(),
            parentNodeId: c13.f6(),
        };
        this.v12();
        this.appEventBus.emit(TreeListenType.NODE_DELETE, callbackParam);
    }
    i13(y12) {
        let z12 = new f3(new j3(d3), d3);
        if (this.v10.has(y12[0])) {
            let node = this.v10.get(y12[0]);
            z12 = new f3(node, this.w10.get(y12[0]));
            z12.m5(node.o6().a13);
        }
        z12.h7(true);
        let index = 0;
        for (let a13 = 0; a13 < this.w7.length; a13++) {
            if (this.w7[a13].e6() === z12.f6()) {
                index = a13;
                if (this.w7[a13].k6().x3 === null) {
                    this.w7[a13].z5(true);
                    this.g9(index);
                }
                else if (this.a11.get(this.w7[a13].e6()) === z2.COLLAPSE) {
                    this.w12(index);
                }
                this.w7.splice(a13 + 1, 0, z12);
                this.w7[a13 + 1].y5(true);
                this.w7[a13 + 1].i6(true);
                this.w7[a13 + 1].c6(i1);
                this.c11.set(y12[0], a13 + 1);
                this.i8(a13 + 1, a3.EDIT);
                this.j13 = t2.ADD_NODE;
                this.o10(a13 + 1);
                this.k13(a13 + 1, this.j13);
                break;
            }
        }
        this.y10 = index + 1;
        this.h9(index);
        this.lastIndex = index;
        this.a11.set(z12.f6(), z2.EXPAND);
        this.z12(index, true);
    }
    g10(operation, parentNodeId, v12) {
        let w12 = new f3(new j3(d3), d3);
        if (this.v10.has(parentNodeId)) {
            let x12 = this.v10.get(parentNodeId);
            w12 = new f3(x12, this.w10.get(parentNodeId));
            w12.m5(x12.o6().a13);
        }
        if (operation === t2.REMOVE_NODE) {
            this.x11.set(parentNodeId, this.z11);
            this.g9(this.b11.get(parentNodeId));
            this.h13(v12, w12);
        }
        if (operation === t2.ADD_NODE) {
            this.d12 = v12[0];
            this.x11.set(this.c10(), this.z11);
            this.x11.set(v12[0], this.a12);
            this.i13(v12);
        }
    }
    removeNode(currentNodeId, parentNodeId) {
        if (this.v10.has(parentNodeId) && this.v10.has(currentNodeId)) {
            let parent = this.v10.get(parentNodeId);
            let current = this.v10.get(currentNodeId);
            let f8 = [];
            let index = current.y14;
            let g8 = 0;
            if (index < 0) {
                hilog.error(j16, i16, 'node does not exist.');
                return [];
            }
            else {
                g8 = parent.children[index].o6().r10 + 1;
                this.z14(parent.children[index], f8);
                for (let j8 = index; j8 < parent.children.length; j8++) {
                    parent.children[j8].y14 -= 1;
                }
                let node = parent.children.splice(index, 1);
                node = null;
                this.d16(parentNodeId);
            }
            parent.o6().b13 = parent.children.length;
            parent.o6().r10 -= (g8);
            let h8 = [];
            h8.push(parent.parentNodeId);
            i(false, g8, this.v10, h8);
            return f8;
        }
        else {
            hilog.error(j16, i16, 'parent does not exist.');
            return [];
        }
    }
    addNode(parentNodeId, currentNodeId, data, p8) {
        if (this.s10 === null) {
            this.s10 = new j3(d3);
            this.s10.b5 = -1;
            this.v10.set(-1, this.s10);
            this.w10.set(-1, d3);
        }
        if (this.v10.has(parentNodeId)) {
            let parent = this.v10.get(parentNodeId);
            let q8 = new j3(data);
            if (parent.b5 > this.t10) {
                hilog.error(j16, i16, 'ListDataSource[addNode]: The level of the tree view cannot exceed 50.');
                return false;
            }
            q8.b5 = parent.b5 + 1;
            q8.parentNodeId = parentNodeId;
            q8.currentNodeId = currentNodeId;
            q8.y14 = parent.children.length;
            data.parentNodeId = parentNodeId;
            data.currentNodeId = currentNodeId;
            parent.children.push(q8);
            parent.o6().a13 = true;
            parent.o6().b13 = parent.children.length;
            parent.o6().r10 += 1;
            this.d16(parentNodeId);
            if (p8) {
                this.e12.push(parent.parentNodeId);
            }
            else {
                let r2 = [];
                r2.push(parent.parentNodeId);
                i(true, 1, this.v10, r2);
            }
            this.w10.set(currentNodeId, data);
            this.v10.set(currentNodeId, q8);
            return true;
        }
        else {
            hilog.error(j16, i16, 'ListDataSource[addNode]: Parent node not found.');
            return false;
        }
    }
    d16(parentNodeId) {
        let parent = this.v10.get(parentNodeId);
        let k2 = this.c11.get(parentNodeId);
        if (parent.children.length > 0) {
            if (this.c11.has(parentNodeId)) {
                this.w7[k2]?.m5(true);
            }
        }
        else {
            this.w7[k2]?.m5(false);
        }
    }
    z14(k8, l8) {
        let m8 = [];
        let callback = (node) => {
            m8.push(node);
            return false;
        };
        this.n14(callback, k8);
        m8.forEach((value) => {
            l8.push(value.f13());
            this.v10.delete(value.f13());
            this.w10.delete(value.f13());
            value = new j3(d3);
        });
    }
    a15(e8) {
        if (e8?.currentNodeId === undefined) {
            hilog.error(j16, i16, 'getNodeInfoByNodeItem: currentId is undefined');
            return new f3(new j3(d3), d3);
        }
        if (!this.c11.has(e8.currentNodeId)) {
            hilog.error(j16, i16, 'getNodeInfoByNodeItem: not has nodeItem.');
            return new f3(new j3(d3), d3);
        }
        let index = this.c11.get(e8.currentNodeId);
        return this.w7[index];
    }
    h10(a8) {
        let parent = new j3(d3);
        if (this.v10.has(a8)) {
            parent = this.v10.get(a8);
        }
        let b8 = d3;
        if (parent) {
            let c8 = this.a15(parent);
            if (parent.children.length === 0) {
                if (c8.k6().v3 !== undefined) {
                    b8.icon = c8.k6().v3?.a8;
                    b8.v16 = c8.k6().v3?.a17;
                    b8.selectedIcon = c8.k6().v3?.r13;
                    b8.w16 = c8.k6().v3?.b17;
                    b8.editIcon = c8.k6().v3?.s13;
                    b8.x16 = c8.k6().v3?.c17;
                    b8.container = c8.q6();
                }
                else {
                    b8.icon = undefined;
                    b8.v16 = undefined;
                    b8.selectedIcon = undefined;
                    b8.w16 = undefined;
                    b8.editIcon = undefined;
                    b8.x16 = undefined;
                    b8.container = c8.q6();
                }
            }
            else if (parent.children.length > 0) {
                let d8 = this.a15(parent.children[0]);
                if (c8.k6().v3 !== null) {
                    b8.icon = (d8.k6().v3 !== undefined) ?
                        d8.k6().v3?.a8 : undefined;
                    b8.v16 = (d8.k6().v3 !== undefined) ?
                        d8.k6().v3?.a17 : undefined;
                    b8.selectedIcon = (d8.k6().v3 !== undefined) ?
                        d8.k6().v3?.r13 : undefined;
                    b8.w16 = (d8.k6().v3 !== undefined) ?
                        d8.k6().v3?.b17 : undefined;
                    b8.editIcon = (d8.k6().v3 !== undefined) ?
                        d8.k6().v3?.s13 : undefined;
                    b8.x16 = (d8.k6().v3 !== undefined) ?
                        d8.k6().v3?.c17 : undefined;
                    b8.container = d8.q6();
                }
                else {
                    b8.icon = undefined;
                    b8.v16 = undefined;
                    b8.selectedIcon = undefined;
                    b8.w16 = undefined;
                    b8.editIcon = undefined;
                    b8.x16 = undefined;
                    b8.container = d8.q6();
                }
            }
        }
        return b8;
    }
    e10(w7) {
        let parent = new j3(d3);
        if (this.v10.has(w7)) {
            parent = this.v10.get(w7);
        }
        if (parent) {
            if (parent.children.length === 0) {
                return [];
            }
            else if (parent.children.length > 0) {
                let x7 = new Array(parent.children.length);
                for (let z7 = 0; z7 < x7.length; z7++) {
                    x7[z7] = 0;
                }
                for (let y7 = 0; y7 < parent.children.length && y7 < x7.length; y7++) {
                    x7[y7] = parent.children[y7].currentNodeId;
                }
                return x7;
            }
        }
        return [];
    }
    b10(r7) {
        let parent = new j3(d3);
        if (this.v10.has(r7)) {
            parent = this.v10.get(r7);
        }
        if (parent) {
            if (parent.children.length === 0) {
                return [];
            }
            else if (parent.children.length > 0) {
                let s7 = new Array(parent.children.length);
                for (let v7 = 0; v7 < s7.length; v7++) {
                    s7[v7] = {};
                }
                for (let t7 = 0; t7 < parent.children.length && t7 < s7.length; t7++) {
                    s7[t7].itemId = parent.children[t7].currentNodeId;
                    let u7 = this.a15(parent.children[t7]);
                    if (u7.k6().v3) {
                        s7[t7].b15 = u7.k6().v3?.source;
                    }
                    if (u7.k6().w3) {
                        s7[t7].c15 = u7.k6().w3?.title;
                    }
                    s7[t7].isFolder = u7.v6();
                }
                return s7;
            }
        }
        return [];
    }
    i10(title) {
        if (new RegExp('/[\\\/:*?"<>|]/').test(title)) {
            return false;
        }
        if ((new RegExp('/^[\u4e00-\u9fa5]+$/').test(title) && title.length > this.MAX_CN_LENGTH) ||
            (!new RegExp('/^[\u4e00-\u9fa5]+$/').test(title) && title.length > this.MAX_EN_LENGTH)) {
            return false;
        }
        return true;
    }
    j14(callback, root = this.s10, o7) {
        let stack = [];
        let p7 = false;
        stack.unshift(root);
        let q7 = stack.shift();
        while (!p7 && q7) {
            p7 = callback(q7, o7) === true;
            if (!p7) {
                stack.unshift(...q7.children);
                q7 = stack.shift();
            }
        }
    }
    d15(insertIndex, parent) {
        for (let n7 = insertIndex; n7 < parent.children.length; n7++) {
            parent.children[n7].y14 += 1;
        }
    }
    k14(parentNodeId, currentNodeId, k7, isAfter, data) {
        if (this.s10 === null) {
            this.s10 = new j3(d3);
            this.s10.b5 = this.INITIAL_INVALID_VALUE;
        }
        if (this.v10.has(parentNodeId)) {
            let parent = this.v10.get(parentNodeId);
            let l7 = new j3(data);
            if (parent.b5 > this.t10) {
                hilog.error(j16, i16, 'addDragNode: The level of the tree view cannot exceed 50.');
                return false;
            }
            l7.b5 = parent.b5 + 1;
            l7.parentNodeId = parentNodeId;
            l7.currentNodeId = currentNodeId;
            data.parentNodeId = parentNodeId;
            data.currentNodeId = currentNodeId;
            let insertIndex = this.INITIAL_INVALID_VALUE;
            if (parent.children.length) {
                for (let m7 = 0; m7 < parent.children.length; m7++) {
                    if (parent.children[m7].f13() === k7) {
                        insertIndex = m7;
                        break;
                    }
                }
                if (isAfter) {
                    l7.y14 = insertIndex + 1;
                    this.d15(l7.y14, parent);
                    parent.children.splice(insertIndex + 1, 0, l7);
                }
                else {
                    l7.y14 = insertIndex < 0 ? parent.children.length + insertIndex : insertIndex;
                    this.d15(l7.y14, parent);
                    parent.children.splice(insertIndex, 0, l7);
                }
            }
            else {
                l7.y14 = parent.children.length;
                parent.children.push(l7);
            }
            parent.o6().a13 = true;
            parent.o6().b13 = parent.children.length;
            parent.o6().r10 += 1;
            this.x14(parent, true, 1);
            this.v10.set(currentNodeId, l7);
            this.w10.set(currentNodeId, data);
            return true;
        }
        else {
            hilog.error(j16, i16, 'addDragNode: Parent node not found.');
            return false;
        }
    }
}
class k16 {
    constructor(controller) {
        this.fontSize = 1;
        this.controller = null;
        this.controller = controller;
    }
    applyGesture(event) {
        if (this.fontSize >= k16.minFontSize) {
            event.addGesture(new LongPressGestureHandler({ repeat: false, duration: k16.e16 })
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
k16.e16 = 500;
k16.minFontSize = 1.75;
export class i3 extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.n7 = new SynchedPropertyNesedObjectPU(params.item, this, 'item');
        this.listNodeDataSource = new h3();
        this.e15 = new ObservedPropertySimplePU(0, this, 'columnWidth');
        this.f15 = new ObservedPropertySimplePU(false, this, 'isFocused');
        this.g15 = new ObservedPropertySimplePU(-1, this, 'index');
        this.h15 = new ObservedPropertySimplePU(-1, this, 'lastIndex');
        this.i15 = new ObservedPropertySimplePU(0, this, 'count');
        this.r7 = new ObservedPropertySimplePU(false, this, 'followingSystemFontScale');
        this.s7 = new ObservedPropertySimplePU(1, this, 'maxAppFontScale');
        this.u7 = this.initializeConsume('treeViewTheme', 'treeViewTheme');
        this.n16 = this.initializeConsume('clickButtonFlag', 'clickButtonFlag');
        this.r16 = this.initializeConsume('accessibilityNodeType', 'accessibilityNodeType');
        this.z16 = this.initializeConsume('isAccessibilityEnabled', 'isAccessibilityEnabled');
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
        this.n7.set(params.item);
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
        this.n7.set(params.item);
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.n7.purgeDependencyOnElmtId(rmElmtId);
        this.e15.purgeDependencyOnElmtId(rmElmtId);
        this.f15.purgeDependencyOnElmtId(rmElmtId);
        this.g15.purgeDependencyOnElmtId(rmElmtId);
        this.h15.purgeDependencyOnElmtId(rmElmtId);
        this.i15.purgeDependencyOnElmtId(rmElmtId);
        this.r7.purgeDependencyOnElmtId(rmElmtId);
        this.s7.purgeDependencyOnElmtId(rmElmtId);
        this.u7.purgeDependencyOnElmtId(rmElmtId);
        this.n16.purgeDependencyOnElmtId(rmElmtId);
        this.r16.purgeDependencyOnElmtId(rmElmtId);
        this.z16.purgeDependencyOnElmtId(rmElmtId);
    }
    aboutToBeDeleted() {
        this.n7.aboutToBeDeleted();
        this.e15.aboutToBeDeleted();
        this.f15.aboutToBeDeleted();
        this.g15.aboutToBeDeleted();
        this.h15.aboutToBeDeleted();
        this.i15.aboutToBeDeleted();
        this.r7.aboutToBeDeleted();
        this.s7.aboutToBeDeleted();
        this.u7.aboutToBeDeleted();
        this.n16.aboutToBeDeleted();
        this.r16.aboutToBeDeleted();
        this.z16.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get item() {
        return this.n7.get();
    }
    get columnWidth() {
        return this.e15.get();
    }
    set columnWidth(newValue) {
        this.e15.set(newValue);
    }
    get isFocused() {
        return this.f15.get();
    }
    set isFocused(newValue) {
        this.f15.set(newValue);
    }
    get index() {
        return this.g15.get();
    }
    set index(newValue) {
        this.g15.set(newValue);
    }
    get lastIndex() {
        return this.h15.get();
    }
    set lastIndex(newValue) {
        this.h15.set(newValue);
    }
    get count() {
        return this.i15.get();
    }
    set count(newValue) {
        this.i15.set(newValue);
    }
    get followingSystemFontScale() {
        return this.r7.get();
    }
    set followingSystemFontScale(newValue) {
        this.r7.set(newValue);
    }
    get maxAppFontScale() {
        return this.s7.get();
    }
    set maxAppFontScale(newValue) {
        this.s7.set(newValue);
    }
    get treeViewTheme() {
        return this.u7.get();
    }
    set treeViewTheme(newValue) {
        this.u7.set(newValue);
    }
    get clickButtonFlag() {
        return this.n16.get();
    }
    set clickButtonFlag(newValue) {
        this.n16.set(newValue);
    }
    get accessibilityNodeType() {
        return this.r16.get();
    }
    set accessibilityNodeType(newValue) {
        this.r16.set(newValue);
    }
    get isAccessibilityEnabled() {
        return this.z16.get();
    }
    set isAccessibilityEnabled(newValue) {
        this.z16.set(newValue);
    }
    aboutToAppear() {
        if (this.item.k6().v3) {
            this.item.j4 = this.item.k6().v3?.source;
            this.item.y16 = this.item.k6().v3?.y16;
        }
        let j7 = this.getUIContext();
        this.followingSystemFontScale = j7.isFollowingSystemFontScale();
        this.maxAppFontScale = j7.getMaxFontScale();
    }
    decideFontScale() {
        let h7 = this.getUIContext();
        let i7 = h7.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.followingSystemFontScale) {
            return 1;
        }
        return Math.min(i7, this.maxAppFontScale, q1);
    }
    getInputTextMaxFontSize() {
        let g7 = this.decideFontScale() * this.inputFontSize + 'vp';
        return g7;
    }
    getLeftIconColor() {
        if (this.item.i7()) {
            return { 'id': -1, 'type': 10001, params: ['sys.color.icon_on_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        }
        else if (this.item.s6()) {
            return this.treeViewTheme.h4;
        }
        else {
            return this.treeViewTheme.g4;
        }
    }
    checkInvalidPattern(title) {
        return new RegExp('/[\\\/:*?"<>|]/').test(title);
    }
    checkIsAllCN(title) {
        return new RegExp('/^[\u4e00-\u9fa5]+$/').test(title);
    }
    getAccessibilityReadText(currentNodeId) {
        let b20 = this.listNodeDataSource.v10.get(currentNodeId);
        if (b20 === undefined || currentNodeId === undefined) {
            return '';
        }
        let c20 = this.listNodeDataSource.a15(b20);
        let primaryTitle = c20?.t6()?.primaryTitle === undefined
            ? '' : c20?.t6()?.primaryTitle;
        let secondaryTitle = c20?.t6()?.secondaryTitle === undefined
            ? '' : c20?.t6()?.secondaryTitle;
        let s17 = this.listNodeDataSource.s16(primaryTitle);
        let j19 = this.listNodeDataSource.s16(secondaryTitle);
        let title = `${s17}, ${j19}`;
        let parentId = this.listNodeDataSource.f10(currentNodeId);
        let d20 = [];
        let e20 = 0;
        let f20 = this.listNodeDataSource.b10(parentId);
        let g20 = f20.map(item => item.itemId);
        let h20 = g20.indexOf(currentNodeId) + 1;
        let i20 = this.listNodeDataSource.g16(currentNodeId);
        if (i20 === undefined) {
            return ' ';
        }
        if (this.accessibilityNodeType === q17.PLACE) {
            if (this.listNodeDataSource.f10(currentNodeId) === -1) {
                for (let k20 = 0; k20 < this.listNodeDataSource.w7.length; k20++) {
                    if (this.listNodeDataSource.w7[k20].f6() === -1) {
                        d20.push(this.listNodeDataSource.w7[k20].e6());
                    }
                }
                e20 = d20.indexOf(currentNodeId) + 1;
                return this.listNodeDataSource.getStringByName('treeview_accessibility_place_node_parent', e20);
            }
            else {
                return this.listNodeDataSource.getStringByName('treeview_accessibility_place_node_child', i20, h20);
            }
        }
        else if (this.accessibilityNodeType === q17.LIFT) {
            return title;
        }
        else {
            return title;
        }
    }
    getAccessibilityDescription() {
        if (this.accessibilityNodeType === q17.TEXT) {
            return this.listNodeDataSource.getStringByName('treeview_accessibility_node_desc');
        }
        else {
            return ',';
        }
    }
    getAccessibilityReadButtonText(a20) {
        if (this.clickButtonFlag === false) {
            return this.item.k6().x3?.c8 === ARROW_RIGHT
                ? this.listNodeDataSource.getStringByName('treeview_accessibility_folded_node')
                : this.listNodeDataSource.getStringByName('treeview_accessibility_expanded_node');
        }
        else {
            return a20 ? this.listNodeDataSource.getStringByName('treeview_accessibility_expand_node')
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
        this.index = this.listNodeDataSource.findIndex(this.item.e6());
        this.listNodeDataSource.h9(this.index);
        let h22 = this.item.e6();
        if (event.type === TouchType.Down) {
            this.item.a6(this.treeViewTheme.d4);
        }
        else if (event.type === TouchType.Up) {
            if (!(typeof this.treeViewTheme.z3 === 'string')) {
                this.item.a6(b2);
            }
            else {
                this.item.a6(this.treeViewTheme.z3);
            }
            if (this.item.k6().v3 !== null) {
                this.item.k6().v3?.i8(a3.SELECTED);
                this.listNodeDataSource.i8(this.index, a3.SELECTED);
                this.item.j4 = this.item.k6().v3?.source;
                this.item.y16 = this.item.k6().v3?.y16;
            }
            this.item.k6().w3?.j8(true);
            let i22 = { currentNodeId: h22 };
            this.appEventBus.emit(TreeListenType.NODE_CLICK, i22);
            this.listNodeDataSource.q16(this.item.s6()
                ? this.listNodeDataSource.getStringByName('treeview_accessibility_select_node', `${this.getAccessibilityReadText(this.item.e6())}`) : '');
        }
        if (this.listNodeDataSource.u9() !== -1 && this.index !== this.listNodeDataSource.u9()) {
            this.listNodeDataSource.v9(u2.WARNINGS, v2.NONE, false, this.listNodeDataSource.u9());
            this.listNodeDataSource.w9(this.listNodeDataSource.u9(), t2.COMMIT_NODE);
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
        this.index = this.listNodeDataSource.findIndex(this.item.e6());
        this.listNodeDataSource.h9(this.index);
        let f22 = this.item.e6();
        if (!(typeof this.treeViewTheme.z3 === 'string')) {
            this.item.a6(b2);
        }
        else {
            this.item.a6(this.treeViewTheme.z3);
        }
        if (this.item.k6().v3 !== null) {
            this.item.k6().v3?.i8(a3.SELECTED);
            this.listNodeDataSource.i8(this.index, a3.SELECTED);
            this.item.j4 = this.item.k6().v3?.source;
            this.item.y16 = this.item.k6().v3?.y16;
        }
        this.item.k6().w3?.j8(true);
        let g22 = { currentNodeId: f22 };
        this.appEventBus.emit(TreeListenType.NODE_CLICK, g22);
        this.listNodeDataSource.q16(this.item.s6()
            ? this.listNodeDataSource.getStringByName('treeview_accessibility_select_node', `${this.getAccessibilityReadText(this.item.e6())}`) : '');
        if (this.listNodeDataSource.u9() !== -1 && this.index !== this.listNodeDataSource.u9()) {
            this.listNodeDataSource.v9(u2.WARNINGS, v2.NONE, false, this.listNodeDataSource.u9());
            this.listNodeDataSource.w9(this.listNodeDataSource.u9(), t2.COMMIT_NODE);
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
            customId: `treeView_button${this.item.e6()}`
        });
        accessibility.sendAccessibilityEvent(eventInfo).then(() => {
            setTimeout(() => {
                this.clickButtonFlag = true;
            }, j17);
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
            if (this.item.j6()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Stack.create();
                        ViewStackProcessor.visualState('focused');
                        Stack.border({
                            radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            width: l1,
                            color: this.treeViewTheme.f4,
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
                        Column.opacity(this.listNodeDataSource.y13(ObservedObject.GetRawObject(this.item)));
                        Column.onHover((isHover) => {
                            if (isHover) {
                                this.item.a6(this.treeViewTheme.e4);
                            }
                            else {
                                this.item.a6({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                            }
                        });
                        Column.onTouch(this.isAccessibilityEnabled ? undefined : (event) => {
                            this.onTouchNode(event);
                        });
                        Column.backgroundColor((this.item.k6().w3 && this.item.k6().inputText &&
                        this.item.x5()) ? this.item.k6().inputText?.j15 : this.item.b6());
                        Column.border({
                            width: this.item.m6().borderWidth,
                            color: this.item.m6().borderColor,
                            radius: this.item.m6().borderRadius,
                        });
                        Column.height(i1);
                        Column.focusable(true);
                        Column.onMouse((event) => {
                            let y6 = this.listNodeDataSource.findIndex(this.item.e6());
                            if (event.button === MouseButton.Right) {
                                this.listNodeDataSource.i9(Event.MOUSE_BUTTON_RIGHT, this.listNodeDataSource.findIndex(this.item.e6()));
                                this.listTreeViewMenu = this.item.q6();
                                this.listNodeDataSource.h9(y6);
                                clearTimeout(this.item.k6().w3?.u13);
                            }
                            event.stopPropagation();
                        });
                        Column.padding({ top: 0, bottom: 0 });
                        Column.bindPopup(this.item.q5().u4, {
                            builder: { builder: () => {
                                this.popupForShowTitle.call(this, this.item.q5().x4, this.item.q5().w4, this.item.q5().y4);
                            } },
                            placement: Placement.BottomLeft,
                            placementOnTop: false,
                            popupColor: this.item.q5().w4,
                            autoCancel: true,
                            enableArrow: this.item.q5().v4
                        });
                        Column.onAreaChange((oldValue, newValue) => {
                            let x6 = Number.parseInt(newValue.width.toString());
                            this.columnWidth = x6;
                        });
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Stack.create({ alignContent: Alignment.Bottom });
                        Stack.focusable(true);
                    }, Stack);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Divider.create();
                        Divider.height(this.listNodeDataSource.o14().g12);
                        Divider.color(this.listNodeDataSource.o14().h12);
                        Divider.visibility(this.listNodeDataSource.p14(ObservedObject.GetRawObject(this.item)));
                        Divider.lineCap(LineCapStyle.Round);
                        Divider.margin({ start: LengthMetrics.vp(this.item.z6()) });
                        Divider.focusable(true);
                    }, Divider);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create({});
                        Row.focusable(true);
                        Row.width('100%');
                        Row.height(this.item.h6());
                        Row.padding({ start: LengthMetrics.vp(this.item.g6()) });
                        Row.bindContextMenu({ builder: this.builder.bind(this) }, ResponseType.RightClick);
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.height(i1);
                        Row.layoutWeight(1);
                        Row.focusable(true);
                        Row.accessibilityGroup(true);
                        Row.id(`treeView_node${this.item.e6()}`);
                        Row.accessibilityText(this.getAccessibilityReadText(this.item.e6()));
                        Row.accessibilityDescription(this.getAccessibilityDescription());
                        Row.onClick(this.isAccessibilityEnabled ? () => {
                            this.onClickNode();
                            this.callBackClick();
                        } : undefined);
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.item.k6().v3) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Row.create();
                                    Row.focusable(true);
                                    Row.backgroundColor(a2);
                                    Row.margin({
                                        end: o(this.item.k6().v3?.z7)
                                    });
                                    Row.height(this.item.k6().v3?.itemHeight);
                                    Row.width(this.item.k6().v3?.itemWidth);
                                }, Row);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    If.create();
                                    if (this.item.y16) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                SymbolGlyph.create();
                                                SymbolGlyph.attributeModifier.bind(this)(this.item.y16);
                                                SymbolGlyph.fontSize(this.item.k6().v3?.itemHeight);
                                                SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                                SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                                SymbolGlyph.opacity(!this.item.s6() && !this.item.g7() ?
                                                    this.item.k6().v3?.opacity : this.item.k6().v3?.k15);
                                                SymbolGlyph.focusable(this.item.k6().w3 !== null ? false : true);
                                            }, SymbolGlyph);
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                If.create();
                                                if (Util.t16(this.item.j4)) {
                                                    this.ifElseBranchUpdateFunction(0, () => {
                                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                            SymbolGlyph.create(this.item.j4);
                                                            SymbolGlyph.fontSize(this.item.k6().v3?.itemHeight);
                                                            SymbolGlyph.fontColor([this.getLeftIconColor()]);
                                                            SymbolGlyph.opacity(!this.item.s6() && !this.item.g7() ?
                                                                this.item.k6().v3?.opacity : this.item.k6().v3?.k15);
                                                            SymbolGlyph.focusable(this.item.k6().w3 !== null ? false : true);
                                                        }, SymbolGlyph);
                                                    });
                                                }
                                                else {
                                                    this.ifElseBranchUpdateFunction(1, () => {
                                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                            Image.create(this.item.j4);
                                                            Image.objectFit(ImageFit.Contain);
                                                            Image.height(this.item.k6().v3?.itemHeight);
                                                            Image.width(this.item.k6().v3?.itemWidth);
                                                            Image.opacity(!this.item.s6() && !this.item.g7() ?
                                                                this.item.k6().v3?.opacity : this.item.k6().v3?.k15);
                                                            Image.focusable(this.item.k6().w3 !== null ? false : true);
                                                            Image.fillColor(this.getLeftIconColor());
                                                            Image.matchTextDirection((this.item.k6().x3?.c8 === ARROW_RIGHT || this.item.k6().x3?.c8 === s2) ? true : false);
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
                        if (this.item.k6().w3 && this.item.w5()) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Text.create(this.item.k6().w3?.title);
                                    Text.minFontScale(o1);
                                    Text.maxFontScale(this.decideFontScale());
                                    Text.maxLines(1);
                                    Text.fontSize(this.item.k6().w3?.size);
                                    Text.fontColor(this.item.s6() ?
                                    this.treeViewTheme.c4 : this.treeViewTheme.a4);
                                    Text.margin({
                                        end: o(this.item.k6().w3?.z7)
                                    });
                                    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                                    Text.fontWeight(this.item.k6().w3?.weight);
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
                        if (this.item.k6().w3 && this.item.k6().inputText &&
                        this.item.x5()) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Row.create();
                                    Row.backgroundColor(this.item.k6().inputText?.backgroundColor);
                                    Row.borderRadius(this.item.k6().inputText?.borderRadius);
                                    Row.margin({
                                        end: o(this.item.k6()
                                            .inputText?.z7)
                                    });
                                }, Row);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    TextInput.create({ text: this.item.k6().w3?.title });
                                    TextInput.height(this.item.k6().inputText?.itemHeight);
                                    TextInput.fontSize(this.getInputTextMaxFontSize());
                                    TextInput.fontColor(this.item.k6().inputText?.color);
                                    TextInput.borderRadius(this.item.k6().inputText?.borderRadius);
                                    TextInput.backgroundColor(this.item.k6().inputText?.backgroundColor);
                                    TextInput.enterKeyType(EnterKeyType.Done);
                                    TextInput.focusable(true);
                                    TextInput.padding({
                                        start: LengthMetrics.resource(this.textInputPadding.left),
                                        end: LengthMetrics.resource(this.textInputPadding.right),
                                        top: LengthMetrics.resource(this.textInputPadding.top),
                                        bottom: LengthMetrics.resource(this.textInputPadding.bottom),
                                    });
                                    TextInput.onChange((value) => {
                                        let o19 = this.listNodeDataSource.findIndex(this.item.e6());
                                        let p19 = '';
                                        let q19 = false;
                                        let r19 = false;
                                        if (this.checkInvalidPattern(value)) {
                                            for (let s19 = 0; s19 < value.length; s19++) {
                                                if (!this.checkInvalidPattern(value[s19])) {
                                                    p19 += value[s19];
                                                }
                                            }
                                            q19 = true;
                                            this.listNodeDataSource.v9(u2.WARNINGS, v2.INVALID_ERROR, true, o19);
                                        }
                                        else {
                                            p19 = value;
                                            q19 = false;
                                        }
                                        if ((this.checkIsAllCN(p19) && p19.length > this.MAX_CN_LENGTH) ||
                                            (!this.checkIsAllCN(p19) && p19.length > this.MAX_EN_LENGTH)) {
                                            p19 = this.checkIsAllCN(p19) ?
                                            p19.substr(0, this.MAX_CN_LENGTH) : p19.substr(0, this.MAX_EN_LENGTH);
                                            r19 = true;
                                            this.listNodeDataSource.v9(u2.WARNINGS, v2.LENGTH_ERROR, true, o19);
                                        }
                                        else {
                                            r19 = false;
                                        }
                                        if (!r19 && !q19) {
                                            this.listNodeDataSource.v13(o19, p19);
                                        }
                                    });
                                    TextInput.onSubmit((enterKey) => {
                                        let n19 = this.listNodeDataSource.findIndex(this.item.e6());
                                        this.listNodeDataSource.v9(u2.WARNINGS, v2.NONE, false, n19);
                                        this.listNodeDataSource.w9(n19, t2.COMMIT_NODE);
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
                        if (this.listNodeDataSource.f14(this.item.e6())) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Row.create();
                                    Row.focusable(true);
                                    Row.margin({
                                        start: LengthMetrics.resource(this.listNodeDataSource.q14().margin.left),
                                        end: this.item.k6().x3 ?
                                        LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }) :
                                        LengthMetrics.resource(this.listNodeDataSource.q14().margin.right)
                                    });
                                }, Row);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Text.create(this.listNodeDataSource.e14(this.item.e6()));
                                    Text.minFontScale(o1);
                                    Text.maxFontScale(this.decideFontScale());
                                    Text.fontSize(this.listNodeDataSource.q14().fontSize);
                                    Text.fontColor(this.item.g7() || this.item.i7() ? { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_primary_contrary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : this.treeViewTheme.b4);
                                    Text.fontWeight(this.listNodeDataSource.q14().fontWeight);
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
                        if (this.item.k6().x3) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                if (!If.canRetake(`treeView_button${this.item.e6()}`)) {
                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                        Row.create();
                                        Row.focusable(true);
                                        Row.justifyContent(FlexAlign.Center);
                                        Row.height(this.item.k6().x3?.itemHeight);
                                        Row.width(this.item.k6().x3?.itemWidth);
                                        Row.onClick(() => {
                                            this.listNodeDataSource.k9(this.listNodeDataSource.findIndex(this.item.e6()));
                                            this.listNodeDataSource.s14(this.item.e6());
                                            setTimeout(() => {
                                                this.accessibilityRefocus();
                                            }, s20);
                                        });
                                        Row.id(`treeView_button${this.item.e6()}`);
                                        Row.accessibilityText(this.getAccessibilityReadButtonText(this.item.k6().x3?.c8 === ARROW_RIGHT));
                                        Row.accessibilityDescription(this.getAccessibilityReadButtonDescription());
                                    }, Row);
                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                        SymbolGlyph.create(this.item.k6().x3?.c8);
                                        SymbolGlyph.fontSize(this.item.k6().x3?.itemHeight);
                                        SymbolGlyph.fontColor([this.item.k6().x3?.y12 ?
                                        this.treeViewTheme.i4 : z1]);
                                        SymbolGlyph.opacity(!this.item.g7() ?
                                            this.item.k6().x3?.opacity : this.item.k6().x3?.k15);
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
export class j3 {
    constructor(nodeParam) {
        this.currentNodeId = nodeParam.currentNodeId ?? -1;
        this.parentNodeId = nodeParam.parentNodeId ?? -1;
        this.isFolder = nodeParam.isFolder;
        this.b5 = -1;
        this.y14 = -1;
        this.p6 = { a13: false, b13: 0, r10: 0 };
        this.children = [];
    }
    o6() {
        return this.p6;
    }
    f13() {
        return this.currentNodeId;
    }
    v6() {
        return this.isFolder;
    }
}
class l3 {
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
    set z7(rightMargin) {
        this.rightMargin = rightMargin;
    }
    get z7() {
        return this.rightMargin;
    }
}
export class m3 extends l3 {
    constructor(w4, r21, x4, itemWidth, itemHeight, y4, z4, a5) {
        super();
        this.rightMargin = { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_elements_margin_horizontal_m'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.j4 = w4;
        this.d17 = r21;
        this.rightMargin = y4;
        this.b8 = x4;
        this.itemWidth = itemWidth;
        this.itemHeight = itemHeight;
        this.l15 = w4;
        this.e17 = r21;
        this.m15 = z4;
        this.n15 = a5;
    }
    get source() {
        return this.j4;
    }
    get y16() {
        return this.d17;
    }
    get opacity() {
        return this.b8;
    }
    get k15() {
        return 1;
    }
    get c8() {
        return this.l15;
    }
    get f17() {
        return this.e17;
    }
    get y12() {
        return this.m15;
    }
    get type() {
        return this.n15;
    }
}
class n3 {
    constructor() {
    }
    static getInstance() {
        if (!n3.instance) {
            n3.instance = new n3();
        }
        return n3.instance;
    }
    o15(type) {
        let v4;
        switch (type) {
            case b3.ARROW_RIGHT_WHITE:
                v4 = s2;
                break;
            case b3.ARROW_RIGHT:
                v4 = ARROW_RIGHT;
                break;
            case b3.ARROW_DOWN_WHITE:
                v4 = q2;
                break;
            default:
                v4 = ARROW_DOWN;
        }
        return new m3(v4, undefined, { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_alpha_content_tertiary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, u, a1, { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_paragraph_margin_xs'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, (type === b3.ARROW_RIGHT_WHITE || type === b3.ARROW_DOWN_WHITE) ? false : true, type);
    }
}
class q3 {
    static n5(type) {
        let node = q3.p15.get(type);
        if (node === undefined) {
            node = n3.getInstance().o15(type);
            q3.p15.set(type, node);
        }
        return node;
    }
    static t12(s4, t4, u4) {
        if (u4 === undefined) {
            return undefined;
        }
        let type = u4;
        if (s4 == a3.EDIT ||
            s4 === a3.DRAG_INSERT) {
            if (t4 === z2.COLLAPSE) {
                type = b3.ARROW_RIGHT_WHITE;
            }
            else {
                type = b3.ARROW_DOWN_WHITE;
            }
        }
        else if (s4 === a3.FINISH_EDIT ||
            s4 === a3.FINISH_DRAG_INSERT) {
            if (t4 === z2.COLLAPSE) {
                type = b3.ARROW_RIGHT;
            }
            else {
                type = b3.ARROW_DOWN;
            }
        }
        return q3.n5(type);
    }
    static x12(q4, r4) {
        if (r4 === undefined) {
            return undefined;
        }
        let type;
        if (!r4) {
            if (q4 === z2.COLLAPSE) {
                type = b3.ARROW_RIGHT_WHITE;
            }
            else {
                type = b3.ARROW_DOWN_WHITE;
            }
        }
        else {
            if (q4 === z2.COLLAPSE) {
                type = b3.ARROW_RIGHT;
            }
            else {
                type = b3.ARROW_DOWN;
            }
        }
        return q3.n5(type);
    }
}
q3.p15 = new Map();
export class r3 extends l3 {
    constructor(m4, o21, n4, itemWidth, itemHeight, o4, p21, p4, q21) {
        super();
        this.rightMargin = { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_elements_margin_horizontal_m'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.j4 = m4;
        this.d17 = o21;
        this.q15 = m4;
        this.g17 = o21;
        if (o4 !== undefined) {
            this.r15 = o4;
        }
        else {
            this.r15 = this.q15;
        }
        this.h17 = p21;
        if (p4 !== undefined) {
            this.s15 = p4;
        }
        else {
            this.s15 = this.q15;
        }
        this.i17 = q21;
        this.b8 = n4;
        this.itemWidth = itemWidth;
        this.itemHeight = itemHeight;
        this.l15 = m4;
        this.t15 = ARROW_DOWN;
        this.u15 = ARROW_RIGHT;
        this.m15 = true;
        this.v15 = a3.NORMAL;
    }
    get source() {
        return this.j4;
    }
    get y16() {
        return this.d17;
    }
    get a8() {
        return this.q15;
    }
    get a17() {
        return this.g17;
    }
    get r13() {
        return this.r15;
    }
    get b17() {
        return this.h17;
    }
    get s13() {
        return this.s15;
    }
    get c17() {
        return this.i17;
    }
    get opacity() {
        return this.b8;
    }
    get k15() {
        return 1;
    }
    get c8() {
        return this.l15;
    }
    get y12() {
        return this.m15;
    }
    x12(l4) {
        if (l4 === z2.EXPAND) {
            this.l15 = this.t15;
        }
        else if (l4 === z2.COLLAPSE) {
            this.l15 = this.u15;
        }
    }
    s12(j4, k4) {
        if (j4 === a3.EDIT || j4 === a3.DRAG_INSERT) {
            this.t15 = q2;
            this.u15 = s2;
            this.m15 = false;
        }
        else if (j4 === a3.FINISH_EDIT ||
            j4 === a3.FINISH_DRAG_INSERT) {
            this.t15 = ARROW_DOWN;
            this.u15 = ARROW_RIGHT;
            this.m15 = true;
        }
        this.l15 = (k4 === z2.COLLAPSE) ?
        this.u15 : this.t15;
    }
    i8(i4) {
        switch (i4) {
            case a3.NORMAL:
                this.j4 = this.q15;
                this.d17 = this.g17;
                this.v15 = i4;
                break;
            case a3.SELECTED:
                if (this.v15 !== a3.EDIT) {
                    this.j4 = this.r15;
                    this.d17 = this.h17;
                    this.v15 = i4;
                }
                break;
            case a3.EDIT:
                this.j4 = this.s15;
                this.d17 = this.i17;
                this.v15 = i4;
                break;
            case a3.FINISH_EDIT:
                this.j4 = this.r15;
                this.d17 = this.h17;
                this.v15 = i4;
                break;
            case a3.DRAG_INSERT:
                this.j4 = this.s15;
                this.d17 = this.i17;
                this.v15 = i4;
                break;
            case a3.FINISH_DRAG_INSERT:
                this.j4 = this.q15;
                this.d17 = this.g17;
                this.v15 = i4;
                break;
            default:
                break;
        }
    }
}
class s3 extends l3 {
    constructor(h4) {
        super();
        this.treeViewTheme = e3.getInstance();
        this.w15 = h4;
        this.itemWidth = b1;
        this.itemHeight = c1;
        this.rightMargin = { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_paragraph_margin_xs'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.x15 = {
            fontColor: this.treeViewTheme.a4,
            fontSize: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            fontWeight: FontWeight.Normal,
        };
        this.y15 = 0;
    }
    j8(isSelected) {
        if (isSelected) {
            this.x15 = {
                fontColor: this.treeViewTheme.c4,
                fontSize: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                fontWeight: FontWeight.Regular,
            };
        }
        else {
            this.x15 = {
                fontColor: this.treeViewTheme.a4,
                fontSize: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                fontWeight: FontWeight.Normal,
            };
        }
    }
    set title(text) {
        this.w15 = text;
    }
    get title() {
        return this.w15;
    }
    set u13(g4) {
        this.y15 = g4;
    }
    get u13() {
        return this.y15;
    }
    get color() {
        return this.x15.fontColor;
    }
    get size() {
        return this.x15.fontSize;
    }
    get weight() {
        return this.x15.fontWeight;
    }
    q9(f4) {
        if (f4) {
            this.x15 = {
                fontColor: this.treeViewTheme.c4,
                fontSize: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                fontWeight: FontWeight.Regular,
            };
        }
        else {
            this.x15 = {
                fontColor: this.treeViewTheme.a4,
                fontSize: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                fontWeight: FontWeight.Normal,
            };
        }
    }
}
export class t3 extends l3 {
    constructor() {
        super();
        this.status = undefined;
        this.z15 = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.a16 = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_emphasize'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.radius = { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_default_xs'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.treeViewTheme = e3.getInstance();
        this.itemWidth = b1;
        this.itemHeight = d1;
        this.rightMargin = { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_paragraph_margin_xs'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.b16 = {
            fontColor: this.treeViewTheme.a4,
            fontSize: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            fontWeight: FontWeight.Normal,
        };
    }
    get color() {
        return this.b16.fontColor;
    }
    get size() {
        return this.b16.fontSize;
    }
    get weight() {
        return this.b16.fontWeight;
    }
    get borderRadius() {
        return this.radius;
    }
    get backgroundColor() {
        return this.z15;
    }
    get j15() {
        return this.a16;
    }
    get c16() {
        return this.status;
    }
}
function o(e4) {
    if (!e4) {
        return LengthMetrics.vp(0);
    }
    else if (typeof e4 === 'number') {
        return LengthMetrics.vp(e4);
    }
    else {
        return LengthMetrics.resource(e4);
    }
}

export default {
    TreeController,
    TreeListener,
    TreeListenerManager,
    TreeListenType,
    TreeView,
}