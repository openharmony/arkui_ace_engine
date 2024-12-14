/*
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

if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => { });
}
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const hilog = requireNapi('hilog');
export var IconType;
(function (IconType) {
    IconType[IconType['BADGE'] = 1] = 'BADGE';
    IconType[IconType['NORMAL_ICON'] = 2] = 'NORMAL_ICON';
    IconType[IconType['SYSTEM_ICON'] = 3] = 'SYSTEM_ICON';
    IconType[IconType['HEAD_SCULPTURE'] = 4] = 'HEAD_SCULPTURE';
    IconType[IconType['APP_ICON'] = 5] = 'APP_ICON';
    IconType[IconType['PREVIEW'] = 6] = 'PREVIEW';
    IconType[IconType['LONGITUDINAL'] = 7] = 'LONGITUDINAL';
    IconType[IconType['VERTICAL'] = 8] = 'VERTICAL';
})(IconType || (IconType = {}));
var u;
(function (o) {
    o[o['LEVEL1'] = 1.75] = 'LEVEL1';
    o[o['LEVEL2'] = 2] = 'LEVEL2';
    o[o['LEVEL3'] = 3.2] = 'LEVEL3';
})(u || (u = {}));
var a1;
(function (m) {
    m[m['FIRST_HEIGHT'] = 48] = 'FIRST_HEIGHT';
    m[m['SECOND_HEIGHT'] = 56] = 'SECOND_HEIGHT';
    m[m['THIRD_HEIGHT'] = 64] = 'THIRD_HEIGHT';
    m[m['FOURTH_HEIGHT'] = 72] = 'FOURTH_HEIGHT';
    m[m['FIFTH_HEIGHT'] = 96] = 'FIFTH_HEIGHT';
})(a1 || (a1 = {}));
const c1 = 1;
const d1 = 2;
const e1 = 4;
const f1 = 8;
const g1 = 6;
const h1 = 4;
const i1 = 4;
const j1 = 8;
const l1 = 16;
const m1 = 24;
const n1 = 32;
const o1 = 32;
const q1 = 40;
const s1 = 28;
const t1 = 64;
const u1 = 96;
const v1 = 96;
const w1 = 96;
const z1 = 16;
const a2 = 0;
const b2 = 0;
const c2 = 0;
const d2 = 4;
const e2 = 24;
const f2 = 2;
const g2 = 12;
const h2 = 40;
const i2 = 48;
const j2 = '0vp';
const l2 = 'calc(66% - 16vp)';
const m2 = '34%';
const n2 = '24vp';
const o2 = '54vp';
const q2 = '40vp';
const s2 = '80vp';
const t2 = '30vp';
const u2 = '30vp';
const v2 = '44vp';
const k5 = 40000;
const w2 = new Map([
    [IconType.BADGE, j1],
    [IconType.NORMAL_ICON, l1],
    [IconType.SYSTEM_ICON, m1],
    [IconType.HEAD_SCULPTURE, q1],
    [IconType.APP_ICON, t1],
    [IconType.PREVIEW, u1],
    [IconType.LONGITUDINAL, v1],
    [IconType.VERTICAL, w1]
]);
class Util {
    static l5(l5) {
        if (!Util.m5(l5)) {
            return false;
        }
        let resource = l5;
        return resource.type === k5;
    }
    static m5(resource) {
        if (!resource) {
            return false;
        }
        if (typeof resource === 'string' || typeof resource === 'undefined') {
            return false;
        }
        return true;
    }
}
class z2 extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.e3 = new SynchedPropertySimpleOneWayPU(params.iconStyle, this, 'iconStyle');
        this.f3 = new SynchedPropertyObjectOneWayPU(params.icon, this, 'icon');
        this.j5 = new SynchedPropertyObjectOneWayPU(params.symbolStyle, this, 'symbolStyle');
        this.h3 = new SynchedPropertyObjectOneWayPU(params.primaryText, this, 'primaryText');
        this.i3 = new SynchedPropertyObjectOneWayPU(params.secondaryText, this, 'secondaryText');
        this.j3 = new SynchedPropertyObjectOneWayPU(params.description, this, 'description');
        this.l3 = new ObservedPropertySimplePU(z1, this, 'itemRowSpace');
        this.m3 = new SynchedPropertySimpleOneWayPU(params.leftWidth, this, 'leftWidth');
        this.n3 = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'primaryTextColor');
        this.q3 = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'secondaryTextColor');
        this.r3 = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'descriptionColor');
        this.s3 = new SynchedPropertySimpleOneWayPU(params.fontSizeScale, this, 'fontSizeScale');
        this.t3 = new SynchedPropertySimpleOneWayPU(params.parentDirection, this, 'parentDirection');
        this.u3 = new SynchedPropertySimpleOneWayPU(params.itemDirection, this, 'itemDirection');
        this.setInitiallyProvidedValue(params);
        this.declareWatch('iconStyle', this.onPropChange);
        this.declareWatch('icon', this.onPropChange);
        this.declareWatch('symbolStyle', this.onPropChange);
        this.declareWatch('primaryText', this.onPropChange);
        this.declareWatch('secondaryText', this.onPropChange);
        this.declareWatch('description', this.onPropChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(params) {
        if (params.iconStyle === undefined) {
            this.e3.set(null);
        }
        if (params.icon === undefined) {
            this.f3.set(null);
        }
        if (params.symbolStyle === undefined) {
            this.j5.set(null);
        }
        if (params.primaryText === undefined) {
            this.h3.set(null);
        }
        if (params.secondaryText === undefined) {
            this.i3.set(null);
        }
        if (params.description === undefined) {
            this.j3.set(null);
        }
        if (params.itemRowSpace !== undefined) {
            this.itemRowSpace = params.itemRowSpace;
        }
        if (params.leftWidth === undefined) {
            this.m3.set(l2);
        }
        if (params.primaryTextColor !== undefined) {
            this.primaryTextColor = params.primaryTextColor;
        }
        if (params.secondaryTextColor !== undefined) {
            this.secondaryTextColor = params.secondaryTextColor;
        }
        if (params.descriptionColor !== undefined) {
            this.descriptionColor = params.descriptionColor;
        }
    }
    updateStateVars(params) {
        this.e3.reset(params.iconStyle);
        this.f3.reset(params.icon);
        this.j5.reset(params.symbolStyle);
        this.h3.reset(params.primaryText);
        this.i3.reset(params.secondaryText);
        this.j3.reset(params.description);
        this.m3.reset(params.leftWidth);
        this.s3.reset(params.fontSizeScale);
        this.t3.reset(params.parentDirection);
        this.u3.reset(params.itemDirection);
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.e3.purgeDependencyOnElmtId(rmElmtId);
        this.f3.purgeDependencyOnElmtId(rmElmtId);
        this.j5.purgeDependencyOnElmtId(rmElmtId);
        this.h3.purgeDependencyOnElmtId(rmElmtId);
        this.i3.purgeDependencyOnElmtId(rmElmtId);
        this.j3.purgeDependencyOnElmtId(rmElmtId);
        this.l3.purgeDependencyOnElmtId(rmElmtId);
        this.m3.purgeDependencyOnElmtId(rmElmtId);
        this.n3.purgeDependencyOnElmtId(rmElmtId);
        this.q3.purgeDependencyOnElmtId(rmElmtId);
        this.r3.purgeDependencyOnElmtId(rmElmtId);
        this.s3.purgeDependencyOnElmtId(rmElmtId);
        this.t3.purgeDependencyOnElmtId(rmElmtId);
        this.u3.purgeDependencyOnElmtId(rmElmtId);
    }
    aboutToBeDeleted() {
        this.e3.aboutToBeDeleted();
        this.f3.aboutToBeDeleted();
        this.j5.aboutToBeDeleted();
        this.h3.aboutToBeDeleted();
        this.i3.aboutToBeDeleted();
        this.j3.aboutToBeDeleted();
        this.l3.aboutToBeDeleted();
        this.m3.aboutToBeDeleted();
        this.n3.aboutToBeDeleted();
        this.q3.aboutToBeDeleted();
        this.r3.aboutToBeDeleted();
        this.s3.aboutToBeDeleted();
        this.t3.aboutToBeDeleted();
        this.u3.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get iconStyle() {
        return this.e3.get();
    }
    set iconStyle(newValue) {
        this.e3.set(newValue);
    }
    get icon() {
        return this.f3.get();
    }
    set icon(newValue) {
        this.f3.set(newValue);
    }
    get symbolStyle() {
        return this.j5.get();
    }
    set symbolStyle(newValue) {
        this.j5.set(newValue);
    }
    get primaryText() {
        return this.h3.get();
    }
    set primaryText(newValue) {
        this.h3.set(newValue);
    }
    get secondaryText() {
        return this.i3.get();
    }
    set secondaryText(newValue) {
        this.i3.set(newValue);
    }
    get description() {
        return this.j3.get();
    }
    set description(newValue) {
        this.j3.set(newValue);
    }
    get itemRowSpace() {
        return this.l3.get();
    }
    set itemRowSpace(newValue) {
        this.l3.set(newValue);
    }
    get leftWidth() {
        return this.m3.get();
    }
    set leftWidth(newValue) {
        this.m3.set(newValue);
    }
    get primaryTextColor() {
        return this.n3.get();
    }
    set primaryTextColor(newValue) {
        this.n3.set(newValue);
    }
    get secondaryTextColor() {
        return this.q3.get();
    }
    set secondaryTextColor(newValue) {
        this.q3.set(newValue);
    }
    get descriptionColor() {
        return this.r3.get();
    }
    set descriptionColor(newValue) {
        this.r3.set(newValue);
    }
    get fontSizeScale() {
        return this.s3.get();
    }
    set fontSizeScale(newValue) {
        this.s3.set(newValue);
    }
    get parentDirection() {
        return this.t3.get();
    }
    set parentDirection(newValue) {
        this.t3.set(newValue);
    }
    get itemDirection() {
        return this.u3.get();
    }
    set itemDirection(newValue) {
        this.u3.set(newValue);
    }
    onWillApplyTheme(theme) {
        this.primaryTextColor = theme.colors.fontPrimary;
        this.secondaryTextColor = theme.colors.fontSecondary;
        this.descriptionColor = theme.colors.fontTertiary;
    }
    onPropChange() {
        if (this.icon == null && this.symbolStyle == null && this.iconStyle == null) {
            this.itemRowSpace = a2;
        }
        else {
            this.itemRowSpace = z1;
        }
    }
    aboutToAppear() {
        this.onPropChange();
    }
    createIcon(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.iconStyle != null && w2.has(this.iconStyle)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.symbolStyle != null) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.symbolStyle));
                                    SymbolGlyph.fontSize(w2.get(this.iconStyle));
                                    SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                    SymbolGlyph.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                    SymbolGlyph.focusable(false);
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.flexShrink(0);
                                }, SymbolGlyph);
                            });
                        }
                        else if (this.icon != null) {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    If.create();
                                    if (Util.l5(ObservedObject.GetRawObject(this.icon))) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                SymbolGlyph.create(this.icon);
                                                SymbolGlyph.fontSize(w2.get(this.iconStyle));
                                                SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                                SymbolGlyph.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                                SymbolGlyph.focusable(false);
                                                SymbolGlyph.draggable(false);
                                                SymbolGlyph.flexShrink(0);
                                            }, SymbolGlyph);
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                If.create();
                                                if (this.iconStyle <= IconType.PREVIEW) {
                                                    this.ifElseBranchUpdateFunction(0, () => {
                                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                            Image.create(this.icon);
                                                            Image.objectFit(ImageFit.Contain);
                                                            Image.width(w2.get(this.iconStyle));
                                                            Image.height(w2.get(this.iconStyle));
                                                            Image.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                                            Image.focusable(false);
                                                            Image.draggable(false);
                                                            Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                                            Image.flexShrink(0);
                                                        }, Image);
                                                    });
                                                }
                                                else {
                                                    this.ifElseBranchUpdateFunction(1, () => {
                                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                            Image.create(this.icon);
                                                            Image.objectFit(ImageFit.Contain);
                                                            Image.constraintSize({
                                                                minWidth: b2,
                                                                maxWidth: w2.get(this.iconStyle),
                                                                minHeight: b2,
                                                                maxHeight: w2.get(this.iconStyle)
                                                            });
                                                            Image.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                                            Image.focusable(false);
                                                            Image.draggable(false);
                                                            Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                                            Image.flexShrink(0);
                                                        }, Image);
                                                    });
                                                }
                                            }, If);
                                            If.pop();
                                        });
                                    }
                                }, If);
                                If.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(2, () => {
                            });
                        }
                    }, If);
                    If.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }
    createText(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create({ space: e1 });
            Column.flexShrink(1);
            Column.margin(this.fontSizeScale >= u.LEVEL1 ? undefined : {
                top: f1,
                bottom: f1
            });
            Column.alignItems(HorizontalAlign.Start);
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.primaryText);
            Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Text.fontColor(ObservedObject.GetRawObject(this.primaryTextColor));
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.fontWeight(FontWeight.Medium);
            Text.focusable(true);
            Text.draggable(false);
        }, Text);
        Text.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.secondaryText != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.secondaryText);
                        Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.fontColor(ObservedObject.GetRawObject(this.secondaryTextColor));
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.draggable(false);
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
            if (this.description != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.description);
                        Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.fontColor(ObservedObject.GetRawObject(this.descriptionColor));
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.draggable(false);
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
        Column.pop();
    }
    isColumnDirection() {
        return this.itemDirection === FlexDirection.Column;
    }
    isParentColumnDirection() {
        return this.parentDirection === FlexDirection.Column;
    }
    getItemSpace() {
        if (this.isColumnDirection()) {
            return LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
        }
        return LengthMetrics.vp(this.itemRowSpace);
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Flex.create({
                space: { main: this.getItemSpace() },
                direction: this.itemDirection,
                justifyContent: FlexAlign.Start,
                alignItems: this.isColumnDirection() ? ItemAlign.Start : ItemAlign.Center,
            });
            Flex.height(this.itemDirection === FlexDirection.Column ? 'auto' : undefined);
            Flex.margin({
                end: this.isParentColumnDirection() ?
                    LengthMetrics.vp(0) :
                    LengthMetrics.vp(16)
            });
            Flex.padding({ start: LengthMetrics.vp(g1) });
            Flex.flexShrink(this.isParentColumnDirection() ? 0 : 1);
        }, Flex);
        this.createIcon.bind(this)();
        this.createText.bind(this)();
        Flex.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
class a3 {
}
class b3 extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.v3 = new SynchedPropertyObjectOneWayPU(params.arrow, this, 'arrow');
        this.f3 = new SynchedPropertyObjectOneWayPU(params.icon, this, 'icon');
        this.w3 = new SynchedPropertyObjectOneWayPU(params.subIcon, this, 'subIcon');
        this.x3 = new SynchedPropertyObjectOneWayPU(params.button, this, 'button');
        this.y3 = new SynchedPropertyObjectOneWayPU(params.switch, this, 'switch');
        this.z3 = new SynchedPropertyObjectOneWayPU(params.checkBox, this, 'checkBox');
        this.a4 = new SynchedPropertyObjectOneWayPU(params.radio, this, 'radio');
        this.b4 = new SynchedPropertyObjectOneWayPU(params.image, this, 'image');
        this.j5 = new SynchedPropertyObjectOneWayPU(params.symbolStyle, this, 'symbolStyle');
        this.d4 = new SynchedPropertyObjectOneWayPU(params.text, this, 'text');
        this.e4 = new ObservedPropertySimplePU(false, this, 'switchState');
        this.f4 = new ObservedPropertySimplePU(false, this, 'radioState');
        this.g4 = new ObservedPropertySimplePU(false, this, 'checkBoxState');
        this.h4 = new SynchedPropertySimpleOneWayPU(params.rightWidth, this, 'rightWidth');
        this.q3 = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'secondaryTextColor');
        this.i4 = new ObservedPropertyObjectPU('#0d000000', this, 'hoveringColor');
        this.j4 = new ObservedPropertyObjectPU('#1a0a59f7', this, 'activedColor');
        this.l4 = new SynchedPropertySimpleTwoWayPU(params.parentCanFocus, this, 'parentCanFocus');
        this.m4 = new SynchedPropertySimpleTwoWayPU(params.parentCanTouch, this, 'parentCanTouch');
        this.n4 = new SynchedPropertySimpleTwoWayPU(params.parentIsHover, this, 'parentIsHover');
        this.o4 = new SynchedPropertySimpleTwoWayPU(params.parentCanHover, this, 'parentCanHover');
        this.q4 = new SynchedPropertySimpleTwoWayPU(params.parentIsActive, this, 'parentIsActive');
        this.r4 = new SynchedPropertyObjectTwoWayPU(params.parentFrontColor, this, 'parentFrontColor');
        this.t3 = new SynchedPropertySimpleTwoWayPU(params.parentDirection, this, 'parentDirection');
        this.s4 = new ObservedPropertySimplePU(c2, this, 'rowSpace');
        this.setInitiallyProvidedValue(params);
        this.declareWatch('arrow', this.onPropChange);
        this.declareWatch('icon', this.onPropChange);
        this.declareWatch('subIcon', this.onPropChange);
        this.declareWatch('button', this.onPropChange);
        this.declareWatch('switch', this.onPropChange);
        this.declareWatch('checkBox', this.onPropChange);
        this.declareWatch('radio', this.onPropChange);
        this.declareWatch('image', this.onPropChange);
        this.declareWatch('symbolStyle', this.onPropChange);
        this.declareWatch('text', this.onPropChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(params) {
        if (params.arrow === undefined) {
            this.v3.set(null);
        }
        if (params.icon === undefined) {
            this.f3.set(null);
        }
        if (params.subIcon === undefined) {
            this.w3.set(null);
        }
        if (params.button === undefined) {
            this.x3.set(null);
        }
        if (params.switch === undefined) {
            this.y3.set(null);
        }
        if (params.checkBox === undefined) {
            this.z3.set(null);
        }
        if (params.radio === undefined) {
            this.a4.set(null);
        }
        if (params.image === undefined) {
            this.b4.set(null);
        }
        if (params.symbolStyle === undefined) {
            this.j5.set(null);
        }
        if (params.text === undefined) {
            this.d4.set(null);
        }
        if (params.switchState !== undefined) {
            this.switchState = params.switchState;
        }
        if (params.radioState !== undefined) {
            this.radioState = params.radioState;
        }
        if (params.checkBoxState !== undefined) {
            this.checkBoxState = params.checkBoxState;
        }
        if (params.rightWidth === undefined) {
            this.h4.set(m2);
        }
        if (params.secondaryTextColor !== undefined) {
            this.secondaryTextColor = params.secondaryTextColor;
        }
        if (params.hoveringColor !== undefined) {
            this.hoveringColor = params.hoveringColor;
        }
        if (params.activedColor !== undefined) {
            this.activedColor = params.activedColor;
        }
        if (params.rowSpace !== undefined) {
            this.rowSpace = params.rowSpace;
        }
    }
    updateStateVars(params) {
        this.v3.reset(params.arrow);
        this.f3.reset(params.icon);
        this.w3.reset(params.subIcon);
        this.x3.reset(params.button);
        this.y3.reset(params.switch);
        this.z3.reset(params.checkBox);
        this.a4.reset(params.radio);
        this.b4.reset(params.image);
        this.j5.reset(params.symbolStyle);
        this.d4.reset(params.text);
        this.h4.reset(params.rightWidth);
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.v3.purgeDependencyOnElmtId(rmElmtId);
        this.f3.purgeDependencyOnElmtId(rmElmtId);
        this.w3.purgeDependencyOnElmtId(rmElmtId);
        this.x3.purgeDependencyOnElmtId(rmElmtId);
        this.y3.purgeDependencyOnElmtId(rmElmtId);
        this.z3.purgeDependencyOnElmtId(rmElmtId);
        this.a4.purgeDependencyOnElmtId(rmElmtId);
        this.b4.purgeDependencyOnElmtId(rmElmtId);
        this.j5.purgeDependencyOnElmtId(rmElmtId);
        this.d4.purgeDependencyOnElmtId(rmElmtId);
        this.e4.purgeDependencyOnElmtId(rmElmtId);
        this.f4.purgeDependencyOnElmtId(rmElmtId);
        this.g4.purgeDependencyOnElmtId(rmElmtId);
        this.h4.purgeDependencyOnElmtId(rmElmtId);
        this.q3.purgeDependencyOnElmtId(rmElmtId);
        this.i4.purgeDependencyOnElmtId(rmElmtId);
        this.j4.purgeDependencyOnElmtId(rmElmtId);
        this.l4.purgeDependencyOnElmtId(rmElmtId);
        this.m4.purgeDependencyOnElmtId(rmElmtId);
        this.n4.purgeDependencyOnElmtId(rmElmtId);
        this.o4.purgeDependencyOnElmtId(rmElmtId);
        this.q4.purgeDependencyOnElmtId(rmElmtId);
        this.r4.purgeDependencyOnElmtId(rmElmtId);
        this.t3.purgeDependencyOnElmtId(rmElmtId);
        this.s4.purgeDependencyOnElmtId(rmElmtId);
    }
    aboutToBeDeleted() {
        this.v3.aboutToBeDeleted();
        this.f3.aboutToBeDeleted();
        this.w3.aboutToBeDeleted();
        this.x3.aboutToBeDeleted();
        this.y3.aboutToBeDeleted();
        this.z3.aboutToBeDeleted();
        this.a4.aboutToBeDeleted();
        this.b4.aboutToBeDeleted();
        this.j5.aboutToBeDeleted();
        this.d4.aboutToBeDeleted();
        this.e4.aboutToBeDeleted();
        this.f4.aboutToBeDeleted();
        this.g4.aboutToBeDeleted();
        this.h4.aboutToBeDeleted();
        this.q3.aboutToBeDeleted();
        this.i4.aboutToBeDeleted();
        this.j4.aboutToBeDeleted();
        this.l4.aboutToBeDeleted();
        this.m4.aboutToBeDeleted();
        this.n4.aboutToBeDeleted();
        this.o4.aboutToBeDeleted();
        this.q4.aboutToBeDeleted();
        this.r4.aboutToBeDeleted();
        this.t3.aboutToBeDeleted();
        this.s4.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get arrow() {
        return this.v3.get();
    }
    set arrow(newValue) {
        this.v3.set(newValue);
    }
    get icon() {
        return this.f3.get();
    }
    set icon(newValue) {
        this.f3.set(newValue);
    }
    get subIcon() {
        return this.w3.get();
    }
    set subIcon(newValue) {
        this.w3.set(newValue);
    }
    get button() {
        return this.x3.get();
    }
    set button(newValue) {
        this.x3.set(newValue);
    }
    get switch() {
        return this.y3.get();
    }
    set switch(newValue) {
        this.y3.set(newValue);
    }
    get checkBox() {
        return this.z3.get();
    }
    set checkBox(newValue) {
        this.z3.set(newValue);
    }
    get radio() {
        return this.a4.get();
    }
    set radio(newValue) {
        this.a4.set(newValue);
    }
    get image() {
        return this.b4.get();
    }
    set image(newValue) {
        this.b4.set(newValue);
    }
    get symbolStyle() {
        return this.j5.get();
    }
    set symbolStyle(newValue) {
        this.j5.set(newValue);
    }
    get text() {
        return this.d4.get();
    }
    set text(newValue) {
        this.d4.set(newValue);
    }
    get switchState() {
        return this.e4.get();
    }
    set switchState(newValue) {
        this.e4.set(newValue);
    }
    get radioState() {
        return this.f4.get();
    }
    set radioState(newValue) {
        this.f4.set(newValue);
    }
    get checkBoxState() {
        return this.g4.get();
    }
    set checkBoxState(newValue) {
        this.g4.set(newValue);
    }
    get rightWidth() {
        return this.h4.get();
    }
    set rightWidth(newValue) {
        this.h4.set(newValue);
    }
    get secondaryTextColor() {
        return this.q3.get();
    }
    set secondaryTextColor(newValue) {
        this.q3.set(newValue);
    }
    get hoveringColor() {
        return this.i4.get();
    }
    set hoveringColor(newValue) {
        this.i4.set(newValue);
    }
    get activedColor() {
        return this.j4.get();
    }
    set activedColor(newValue) {
        this.j4.set(newValue);
    }
    get parentCanFocus() {
        return this.l4.get();
    }
    set parentCanFocus(newValue) {
        this.l4.set(newValue);
    }
    get parentCanTouch() {
        return this.m4.get();
    }
    set parentCanTouch(newValue) {
        this.m4.set(newValue);
    }
    get parentIsHover() {
        return this.n4.get();
    }
    set parentIsHover(newValue) {
        this.n4.set(newValue);
    }
    get parentCanHover() {
        return this.o4.get();
    }
    set parentCanHover(newValue) {
        this.o4.set(newValue);
    }
    get parentIsActive() {
        return this.q4.get();
    }
    set parentIsActive(newValue) {
        this.q4.set(newValue);
    }
    get parentFrontColor() {
        return this.r4.get();
    }
    set parentFrontColor(newValue) {
        this.r4.set(newValue);
    }
    get parentDirection() {
        return this.t3.get();
    }
    set parentDirection(newValue) {
        this.t3.set(newValue);
    }
    get rowSpace() {
        return this.s4.get();
    }
    set rowSpace(newValue) {
        this.s4.set(newValue);
    }
    onWillApplyTheme(theme) {
        this.secondaryTextColor = theme.colors.fontSecondary;
        this.hoveringColor = theme.colors.interactiveHover;
        this.activedColor = theme.colors.interactiveActive;
    }
    onPropChange() {
        if (this.switch != null) {
            this.switchState = this.switch.isCheck;
        }
        if (this.radio != null) {
            this.radioState = this.radio.isCheck;
        }
        if (this.checkBox != null) {
            this.checkBoxState = this.checkBox.isCheck;
        }
        if ((this.button == null && this.image == null && this.symbolStyle == null && this.text != null) &&
            ((this.icon != null) || (this.icon == null && this.arrow != null))) {
            this.rowSpace = d2;
        }
        else {
            this.rowSpace = c2;
        }
    }
    aboutToAppear() {
        this.onPropChange();
    }
    createButton(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithChild();
            Button.padding({ top: 0, bottom: 0 });
            Button.margin({ end: LengthMetrics.vp(g1) });
            Button.hitTestBehavior(HitTestMode.Block);
            Button.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_button3'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Button.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary_activated_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Button.constraintSize({
                minHeight: s1
            });
            Button.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_button_normal'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Button.labelStyle({
                maxLines: c1
            });
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.onHover((isHover) => {
                this.parentCanHover = false;
                if (isHover && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!isHover) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
        }, Button);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.padding({
                left: f1,
                right: f1
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.button?.text);
            Text.focusable(true);
        }, Text);
        Text.pop();
        Row.pop();
        Button.pop();
    }
    createIcon(param, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.hitTestBehavior(HitTestMode.Block);
            Button.backgroundColor(Color.Transparent);
            Button.height(h2);
            Button.width(h2);
            Button.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.onHover((isHover) => {
                this.parentCanHover = false;
                if (isHover && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!isHover) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Button.onClick(param.icon?.action);
            Button.flexShrink(0);
        }, Button);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (param.icon?.symbolStyle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        SymbolGlyph.create();
                        SymbolGlyph.attributeModifier.bind(this)(param.icon?.symbolStyle);
                        SymbolGlyph.fontSize(e2);
                        SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                        SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                        SymbolGlyph.focusable(true);
                        SymbolGlyph.draggable(false);
                    }, SymbolGlyph);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (Util.l5(param.icon?.value)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    SymbolGlyph.create(param.icon?.value);
                                    SymbolGlyph.fontSize(e2);
                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                    SymbolGlyph.focusable(true);
                                    SymbolGlyph.draggable(false);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Image.create(param.icon?.value);
                                    Image.height(e2);
                                    Image.width(e2);
                                    Image.focusable(true);
                                    Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                    Image.draggable(false);
                                }, Image);
                            });
                        }
                    }, If);
                    If.pop();
                });
            }
        }, If);
        If.pop();
        Button.pop();
    }
    createImage(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (Util.l5(ObservedObject.GetRawObject(this.image))) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        SymbolGlyph.create(this.image);
                        SymbolGlyph.fontSize(i2);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.margin({ end: LengthMetrics.vp(g1) });
                    }, SymbolGlyph);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(this.image);
                        Image.height(i2);
                        Image.width(i2);
                        Image.draggable(false);
                        Image.margin({ end: LengthMetrics.vp(g1) });
                    }, Image);
                });
            }
        }, If);
        If.pop();
    }
    createSymbol(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            SymbolGlyph.create();
            SymbolGlyph.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.symbolStyle));
            SymbolGlyph.fontSize(i2);
            SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
            SymbolGlyph.symbolEffect(new SymbolEffect(), false);
            SymbolGlyph.draggable(false);
            SymbolGlyph.margin({ end: LengthMetrics.vp(g1) });
        }, SymbolGlyph);
    }
    createText(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.text);
            Text.margin({ end: LengthMetrics.vp(g1) });
            Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Text.fontColor(ObservedObject.GetRawObject(this.secondaryTextColor));
            Text.draggable(false);
            Text.flexShrink(1);
        }, Text);
        Text.pop();
    }
    createArrow(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.margin({ end: LengthMetrics.vp(g1) });
            Button.hitTestBehavior(this.arrow?.action !== undefined ? HitTestMode.Block : HitTestMode.Transparent);
            Button.backgroundColor(Color.Transparent);
            Button.height(e2);
            Button.width(g2);
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.stateEffect(this.arrow?.action !== undefined);
            Button.hoverEffect(this.arrow?.action !== undefined ? HoverEffect.Auto : HoverEffect.None);
            Button.onHover((isHover) => {
                if (this.arrow?.action === undefined) {
                    return;
                }
                if (isHover) {
                    this.parentCanHover = false;
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                else {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Button.onClick(this.arrow?.action);
        }, Button);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.arrow?.symbolStyle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        SymbolGlyph.create();
                        SymbolGlyph.attributeModifier.bind(this)(this.arrow?.symbolStyle);
                        SymbolGlyph.fontSize(g2);
                        SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                        SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                        SymbolGlyph.focusable(true);
                        SymbolGlyph.draggable(false);
                    }, SymbolGlyph);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (Util.l5(this.arrow?.value)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    SymbolGlyph.create(this.arrow?.value);
                                    SymbolGlyph.fontSize(g2);
                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_fourth'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                    SymbolGlyph.focusable(true);
                                    SymbolGlyph.draggable(false);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Image.create(this.arrow?.value);
                                    Image.height(e2);
                                    Image.width(g2);
                                    Image.focusable(true);
                                    Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_fourth'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                    Image.draggable(false);
                                    Image.matchTextDirection(true);
                                }, Image);
                            });
                        }
                    }, If);
                    If.pop();
                });
            }
        }, If);
        If.pop();
        Button.pop();
    }
    createRadio(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Radio.create({ value: '', group: '' });
            Radio.margin({ end: LengthMetrics.vp(g1) });
            Radio.checked(this.radioState);
            Radio.onChange(this.radio?.onChange);
            Radio.height(e2);
            Radio.width(e2);
            Radio.padding(f2);
            Radio.onFocus(() => {
                this.parentCanFocus = false;
            });
            Radio.hitTestBehavior(HitTestMode.Block);
            Radio.flexShrink(0);
            Radio.onHover((isHover) => {
                this.parentCanHover = false;
                if (isHover && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!isHover) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
        }, Radio);
    }
    createCheckBox(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Checkbox.create();
            Checkbox.margin({ end: LengthMetrics.vp(g1) });
            Checkbox.select(this.checkBoxState);
            Checkbox.onChange(this.checkBox?.onChange);
            Checkbox.height(e2);
            Checkbox.width(e2);
            Checkbox.padding(f2);
            Checkbox.onFocus(() => {
                this.parentCanFocus = false;
            });
            Checkbox.hitTestBehavior(HitTestMode.Block);
            Checkbox.flexShrink(0);
            Checkbox.onHover((isHover) => {
                this.parentCanHover = false;
                if (isHover && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!isHover) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
        }, Checkbox);
        Checkbox.pop();
    }
    createSwitch(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.margin({ end: LengthMetrics.vp(h1) });
            Row.height(h2);
            Row.width(h2);
            Row.justifyContent(FlexAlign.Center);
            Row.onFocus(() => {
                this.parentCanFocus = false;
            });
            Row.onHover((isHover) => {
                this.parentCanHover = false;
                if (isHover && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!isHover) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Toggle.create({ type: ToggleType.Switch, isOn: this.switchState });
            Toggle.onChange(this.switch?.onChange);
            Toggle.onClick(() => {
                this.switchState = !this.switchState;
            });
            Toggle.hitTestBehavior(HitTestMode.Block);
        }, Toggle);
        Toggle.pop();
        Row.pop();
    }
    createTextArrow(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.hitTestBehavior(this.arrow?.action !== undefined ? HitTestMode.Block : HitTestMode.Transparent);
            Button.labelStyle({
                maxLines: c1
            });
            Button.backgroundColor(Color.Transparent);
            Button.constraintSize({ minHeight: n1 });
            Button.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.padding({
                top: 0,
                bottom: 0,
                left: 0,
                right: 0
            });
            Button.stateEffect(this.arrow?.action !== undefined);
            Button.hoverEffect(this.arrow?.action !== undefined ? HoverEffect.Auto : HoverEffect.None);
            Button.onHover((isHover) => {
                if (this.arrow?.action === undefined) {
                    return;
                }
                if (isHover) {
                    this.parentCanHover = false;
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                else {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Button.onClick(this.arrow?.action);
        }, Button);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.parentDirection === FlexDirection.Column) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Flex.create({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center });
                        Flex.padding({
                            start: LengthMetrics.vp(f1),
                            end: LengthMetrics.vp(g1)
                        });
                    }, Flex);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.text);
                        Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.fontColor(ObservedObject.GetRawObject(this.secondaryTextColor));
                        Text.focusable(true);
                        Text.draggable(false);
                        Text.constraintSize({
                            maxWidth: `calc(100% - ${g2}vp)`
                        });
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.arrow?.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.attributeModifier.bind(this)(this.arrow?.symbolStyle);
                                    SymbolGlyph.fontSize(g2);
                                    SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                    SymbolGlyph.focusable(false);
                                    SymbolGlyph.draggable(false);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    If.create();
                                    if (Util.l5(this.arrow?.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                SymbolGlyph.create(this.arrow?.value);
                                                SymbolGlyph.fontSize(g2);
                                                SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_fourth'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                                SymbolGlyph.focusable(false);
                                                SymbolGlyph.draggable(false);
                                            }, SymbolGlyph);
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                Image.create(this.arrow?.value);
                                                Image.height(e2);
                                                Image.width(g2);
                                                Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_fourth'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                                Image.focusable(false);
                                                Image.draggable(false);
                                                Image.matchTextDirection(true);
                                            }, Image);
                                        });
                                    }
                                }, If);
                                If.pop();
                            });
                        }
                    }, If);
                    If.pop();
                    Flex.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create({ space: d2 });
                        Row.padding({
                            start: LengthMetrics.vp(f1),
                            end: LengthMetrics.vp(g1)
                        });
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.text);
                        Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.fontColor(ObservedObject.GetRawObject(this.secondaryTextColor));
                        Text.focusable(true);
                        Text.draggable(false);
                        Text.constraintSize({
                            maxWidth: `calc(100% - ${g2}vp)`
                        });
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.arrow?.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.attributeModifier.bind(this)(this.arrow?.symbolStyle);
                                    SymbolGlyph.fontSize(g2);
                                    SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                    SymbolGlyph.focusable(false);
                                    SymbolGlyph.draggable(false);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    If.create();
                                    if (Util.l5(this.arrow?.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                SymbolGlyph.create(this.arrow?.value);
                                                SymbolGlyph.fontSize(g2);
                                                SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_fourth'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                                SymbolGlyph.focusable(false);
                                                SymbolGlyph.draggable(false);
                                            }, SymbolGlyph);
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                Image.create(this.arrow?.value);
                                                Image.height(e2);
                                                Image.width(g2);
                                                Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_fourth'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                                Image.focusable(false);
                                                Image.draggable(false);
                                                Image.matchTextDirection(true);
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
        }, If);
        If.pop();
        Button.pop();
    }
    getFlexOptions() {
        let j = { alignItems: ItemAlign.Center };
        if (this.parentDirection === FlexDirection.Column) {
            j.justifyContent = FlexAlign.SpaceBetween;
        }
        else {
            j.space = { main: LengthMetrics.vp(this.rowSpace) };
            j.justifyContent = FlexAlign.End;
        }
        return j;
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Flex.create(this.getFlexOptions());
            Flex.width(this.parentDirection === FlexDirection.Column ? undefined : this.rightWidth);
        }, Flex);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.button != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.createButton.bind(this)();
                });
            }
            else if (this.symbolStyle != null) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.createSymbol.bind(this)();
                });
            }
            else if (this.image != null) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.createImage.bind(this)();
                });
            }
            else if (this.icon != null && this.text != null) {
                this.ifElseBranchUpdateFunction(3, () => {
                    this.createText.bind(this)();
                    this.createIcon.bind(this)(makeBuilderParameterProxy('createIcon', { icon: () => (this['__icon'] ? this['__icon'] : this['icon']) }));
                });
            }
            else if (this.arrow != null && this.text == null) {
                this.ifElseBranchUpdateFunction(4, () => {
                    this.createArrow.bind(this)();
                });
            }
            else if (this.arrow != null && this.text != null) {
                this.ifElseBranchUpdateFunction(5, () => {
                    this.createTextArrow.bind(this)();
                });
            }
            else if (this.text != null) {
                this.ifElseBranchUpdateFunction(6, () => {
                    this.createText.bind(this)();
                });
            }
            else if (this.radio != null) {
                this.ifElseBranchUpdateFunction(7, () => {
                    this.createRadio.bind(this)();
                });
            }
            else if (this.checkBox != null) {
                this.ifElseBranchUpdateFunction(8, () => {
                    this.createCheckBox.bind(this)();
                });
            }
            else if (this.switch != null) {
                this.ifElseBranchUpdateFunction(9, () => {
                    this.createSwitch.bind(this)();
                });
            }
            else if (this.icon != null) {
                this.ifElseBranchUpdateFunction(10, () => {
                    this.createIcon.bind(this)(makeBuilderParameterProxy('createIcon', { icon: () => (this['__icon'] ? this['__icon'] : this['icon']) }));
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.subIcon != null) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.createIcon.bind(this)(makeBuilderParameterProxy('createIcon', { icon: () => (this['__subIcon'] ? this['__subIcon'] : this['subIcon']) }));
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(11, () => {
                });
            }
        }, If);
        If.pop();
        Flex.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
export class ComposeListItem extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.t4 = new SynchedPropertyObjectOneWayPU(params.contentItem, this, 'contentItem');
        this.u4 = new SynchedPropertyObjectOneWayPU(params.operateItem, this, 'operateItem');
        this.v4 = new ObservedPropertyObjectPU(Color.Transparent.toString(), this, 'frontColor');
        this.w4 = new ObservedPropertySimplePU(0, this, 'borderSize');
        this.x4 = new ObservedPropertySimplePU(false, this, 'canFocus');
        this.y4 = new ObservedPropertySimplePU(true, this, 'canTouch');
        this.z4 = new ObservedPropertySimplePU(true, this, 'canHover');
        this.a5 = new ObservedPropertySimplePU(true, this, 'isHover');
        this.b5 = new ObservedPropertySimplePU(a1.FIRST_HEIGHT, this, 'itemHeight');
        this.c5 = new ObservedPropertySimplePU(false, this, 'isActive');
        this.i4 = new ObservedPropertyObjectPU('#0d000000', this, 'hoveringColor');
        this.d5 = new ObservedPropertyObjectPU('#1a000000', this, 'touchDownColor');
        this.j4 = new ObservedPropertyObjectPU('#1a0a59f7', this, 'activedColor');
        this.e5 = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_focused_outline'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'focusOutlineColor');
        this.s3 = new ObservedPropertySimplePU(1, this, 'fontSizeScale');
        this.f5 = new ObservedPropertySimplePU(FlexDirection.Row, this, 'containerDirection');
        this.g5 = new ObservedPropertySimplePU(FlexDirection.Row, this, 'contentItemDirection');
        this.h5 = new ObservedPropertyObjectPU(undefined, this, 'containerPadding');
        this.i5 = new ObservedPropertySimplePU(0, this, 'textArrowLeftSafeOffset');
        this.isFollowingSystemFontScale = this.getUIContext().isFollowingSystemFontScale();
        this.maxFontScale = this.getUIContext().getMaxFontScale();
        this.callbackId = undefined;
        this.envCallback = {
            onConfigurationUpdated: (config) => {
                this.fontSizeScale = this.decideFontSizeScale();
            },
            onMemoryLevel: (level) => {
            }
        };
        this.setInitiallyProvidedValue(params);
        this.declareWatch('contentItem', this.onPropChange);
        this.declareWatch('operateItem', this.onPropChange);
        this.declareWatch('fontSizeScale', this.onFontSizeScaleChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(params) {
        if (params.contentItem === undefined) {
            this.t4.set(null);
        }
        if (params.operateItem === undefined) {
            this.u4.set(null);
        }
        if (params.frontColor !== undefined) {
            this.frontColor = params.frontColor;
        }
        if (params.borderSize !== undefined) {
            this.borderSize = params.borderSize;
        }
        if (params.canFocus !== undefined) {
            this.canFocus = params.canFocus;
        }
        if (params.canTouch !== undefined) {
            this.canTouch = params.canTouch;
        }
        if (params.canHover !== undefined) {
            this.canHover = params.canHover;
        }
        if (params.isHover !== undefined) {
            this.isHover = params.isHover;
        }
        if (params.itemHeight !== undefined) {
            this.itemHeight = params.itemHeight;
        }
        if (params.isActive !== undefined) {
            this.isActive = params.isActive;
        }
        if (params.hoveringColor !== undefined) {
            this.hoveringColor = params.hoveringColor;
        }
        if (params.touchDownColor !== undefined) {
            this.touchDownColor = params.touchDownColor;
        }
        if (params.activedColor !== undefined) {
            this.activedColor = params.activedColor;
        }
        if (params.focusOutlineColor !== undefined) {
            this.focusOutlineColor = params.focusOutlineColor;
        }
        if (params.fontSizeScale !== undefined) {
            this.fontSizeScale = params.fontSizeScale;
        }
        if (params.containerDirection !== undefined) {
            this.containerDirection = params.containerDirection;
        }
        if (params.contentItemDirection !== undefined) {
            this.contentItemDirection = params.contentItemDirection;
        }
        if (params.containerPadding !== undefined) {
            this.containerPadding = params.containerPadding;
        }
        if (params.textArrowLeftSafeOffset !== undefined) {
            this.textArrowLeftSafeOffset = params.textArrowLeftSafeOffset;
        }
        if (params.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = params.isFollowingSystemFontScale;
        }
        if (params.maxFontScale !== undefined) {
            this.maxFontScale = params.maxFontScale;
        }
        if (params.callbackId !== undefined) {
            this.callbackId = params.callbackId;
        }
        if (params.envCallback !== undefined) {
            this.envCallback = params.envCallback;
        }
    }
    updateStateVars(params) {
        this.t4.reset(params.contentItem);
        this.u4.reset(params.operateItem);
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.t4.purgeDependencyOnElmtId(rmElmtId);
        this.u4.purgeDependencyOnElmtId(rmElmtId);
        this.v4.purgeDependencyOnElmtId(rmElmtId);
        this.w4.purgeDependencyOnElmtId(rmElmtId);
        this.x4.purgeDependencyOnElmtId(rmElmtId);
        this.y4.purgeDependencyOnElmtId(rmElmtId);
        this.z4.purgeDependencyOnElmtId(rmElmtId);
        this.a5.purgeDependencyOnElmtId(rmElmtId);
        this.b5.purgeDependencyOnElmtId(rmElmtId);
        this.c5.purgeDependencyOnElmtId(rmElmtId);
        this.i4.purgeDependencyOnElmtId(rmElmtId);
        this.d5.purgeDependencyOnElmtId(rmElmtId);
        this.j4.purgeDependencyOnElmtId(rmElmtId);
        this.e5.purgeDependencyOnElmtId(rmElmtId);
        this.s3.purgeDependencyOnElmtId(rmElmtId);
        this.f5.purgeDependencyOnElmtId(rmElmtId);
        this.g5.purgeDependencyOnElmtId(rmElmtId);
        this.h5.purgeDependencyOnElmtId(rmElmtId);
        this.i5.purgeDependencyOnElmtId(rmElmtId);
    }
    aboutToBeDeleted() {
        this.t4.aboutToBeDeleted();
        this.u4.aboutToBeDeleted();
        this.v4.aboutToBeDeleted();
        this.w4.aboutToBeDeleted();
        this.x4.aboutToBeDeleted();
        this.y4.aboutToBeDeleted();
        this.z4.aboutToBeDeleted();
        this.a5.aboutToBeDeleted();
        this.b5.aboutToBeDeleted();
        this.c5.aboutToBeDeleted();
        this.i4.aboutToBeDeleted();
        this.d5.aboutToBeDeleted();
        this.j4.aboutToBeDeleted();
        this.e5.aboutToBeDeleted();
        this.s3.aboutToBeDeleted();
        this.f5.aboutToBeDeleted();
        this.g5.aboutToBeDeleted();
        this.h5.aboutToBeDeleted();
        this.i5.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get contentItem() {
        return this.t4.get();
    }
    set contentItem(newValue) {
        this.t4.set(newValue);
    }
    get operateItem() {
        return this.u4.get();
    }
    set operateItem(newValue) {
        this.u4.set(newValue);
    }
    get frontColor() {
        return this.v4.get();
    }
    set frontColor(newValue) {
        this.v4.set(newValue);
    }
    get borderSize() {
        return this.w4.get();
    }
    set borderSize(newValue) {
        this.w4.set(newValue);
    }
    get canFocus() {
        return this.x4.get();
    }
    set canFocus(newValue) {
        this.x4.set(newValue);
    }
    get canTouch() {
        return this.y4.get();
    }
    set canTouch(newValue) {
        this.y4.set(newValue);
    }
    get canHover() {
        return this.z4.get();
    }
    set canHover(newValue) {
        this.z4.set(newValue);
    }
    get isHover() {
        return this.a5.get();
    }
    set isHover(newValue) {
        this.a5.set(newValue);
    }
    get itemHeight() {
        return this.b5.get();
    }
    set itemHeight(newValue) {
        this.b5.set(newValue);
    }
    get isActive() {
        return this.c5.get();
    }
    set isActive(newValue) {
        this.c5.set(newValue);
    }
    get hoveringColor() {
        return this.i4.get();
    }
    set hoveringColor(newValue) {
        this.i4.set(newValue);
    }
    get touchDownColor() {
        return this.d5.get();
    }
    set touchDownColor(newValue) {
        this.d5.set(newValue);
    }
    get activedColor() {
        return this.j4.get();
    }
    set activedColor(newValue) {
        this.j4.set(newValue);
    }
    get focusOutlineColor() {
        return this.e5.get();
    }
    set focusOutlineColor(newValue) {
        this.e5.set(newValue);
    }
    get fontSizeScale() {
        return this.s3.get();
    }
    set fontSizeScale(newValue) {
        this.s3.set(newValue);
    }
    get containerDirection() {
        return this.f5.get();
    }
    set containerDirection(newValue) {
        this.f5.set(newValue);
    }
    get contentItemDirection() {
        return this.g5.get();
    }
    set contentItemDirection(newValue) {
        this.g5.set(newValue);
    }
    get containerPadding() {
        return this.h5.get();
    }
    set containerPadding(newValue) {
        this.h5.set(newValue);
    }
    get textArrowLeftSafeOffset() {
        return this.i5.get();
    }
    set textArrowLeftSafeOffset(newValue) {
        this.i5.set(newValue);
    }
    onWillApplyTheme(theme) {
        this.hoveringColor = theme.colors.interactiveHover;
        this.touchDownColor = theme.colors.interactivePressed;
        this.activedColor = theme.colors.interactiveActive;
        this.focusOutlineColor = theme.colors.interactiveFocus;
    }
    onPropChange() {
        this.containerDirection = this.decideContainerDirection();
        this.contentItemDirection = this.decideContentItemDirection();
        if (this.contentItem === undefined) {
            if (this.operateItem?.image !== undefined ||
                this.operateItem?.symbolStyle !== undefined ||
                this.operateItem?.icon !== undefined ||
                this.operateItem?.subIcon !== undefined) {
                this.itemHeight = i2 + o1;
            }
            return;
        }
        if (this.contentItem?.secondaryText === undefined && this.contentItem?.description === undefined) {
            if (this.contentItem?.icon === undefined) {
                this.itemHeight = a1.FIRST_HEIGHT;
            }
            else {
                this.itemHeight = this.contentItem.iconStyle <= IconType.HEAD_SCULPTURE ?
                    a1.SECOND_HEIGHT : a1.THIRD_HEIGHT;
            }
        }
        else if (this.contentItem.description === undefined) {
            if (this.contentItem.icon === undefined ||
                (this.contentItem.icon !== undefined && this.contentItem.iconStyle <= IconType.SYSTEM_ICON)) {
                this.itemHeight = a1.THIRD_HEIGHT;
            }
            else {
                this.itemHeight = a1.FOURTH_HEIGHT;
            }
        }
        else {
            this.itemHeight = a1.FIFTH_HEIGHT;
        }
        if (w2.get(this.contentItem?.iconStyle) >= this.itemHeight) {
            this.itemHeight = w2.get(this.contentItem?.iconStyle) + o1;
        }
    }
    aboutToAppear() {
        this.fontSizeScale = this.decideFontSizeScale();
        this.onPropChange();
        try {
            this.callbackId = getContext()?.getApplicationContext()?.on('environment', this.envCallback);
        }
        catch (i) {
            let code = i.code;
            let message = i.message;
            hilog.error(0x3900, 'Ace', `ComposeListItem Faild to get environment param error: ${code}, ${message}`);
        }
    }
    aboutToDisappear() {
        if (this.callbackId) {
            this.getUIContext()
                .getHostContext()
                ?.getApplicationContext()
                ?.off('environment', this.callbackId);
            this.callbackId = void (0);
        }
    }
    calculatedRightWidth() {
        if (this.operateItem?.text || this.operateItem?.button) {
            return m2;
        }
        if (this.operateItem?.switch) {
            return v2;
        }
        else if (this.operateItem?.checkbox) {
            return u2;
        }
        else if (this.operateItem?.radio) {
            return t2;
        }
        else if (this.operateItem?.icon) {
            if (this.operateItem?.subIcon) {
                return s2;
            }
            return q2;
        }
        else if (this.operateItem?.symbolStyle) {
            return o2;
        }
        else if (this.operateItem?.image) {
            return o2;
        }
        else if (this.operateItem?.arrow) {
            return n2;
        }
        return j2;
    }
    decideContentItemDirection() {
        if (this.fontSizeScale >= u.LEVEL1 &&
            this.contentItem?.iconStyle && this.contentItem?.iconStyle > IconType.HEAD_SCULPTURE) {
            return FlexDirection.Column;
        }
        return FlexDirection.Row;
    }
    decideContainerDirection() {
        if (this.fontSizeScale < u.LEVEL1 || !this.contentItem) {
            return FlexDirection.Row;
        }
        if (this.operateItem?.button) {
            return FlexDirection.Column;
        }
        else if (this.operateItem?.symbolStyle) {
            return FlexDirection.Row;
        }
        else if (this.operateItem?.image) {
            return FlexDirection.Row;
        }
        else if (this.operateItem?.icon && this.operateItem?.text) {
            return FlexDirection.Column;
        }
        else if (this.operateItem?.arrow) {
            if (!this.operateItem?.text) {
                return FlexDirection.Row;
            }
            this.textArrowLeftSafeOffset = f1;
            return FlexDirection.Column;
        }
        else if (this.operateItem?.text) {
            return FlexDirection.Column;
        }
        else {
            return FlexDirection.Row;
        }
    }
    onFontSizeScaleChange() {
        this.containerDirection = this.decideContainerDirection();
        this.contentItemDirection = this.decideContentItemDirection();
        if (this.fontSizeScale >= u.LEVEL3) {
            this.containerPadding = {
                top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            };
        }
        else if (this.fontSizeScale >= u.LEVEL2) {
            this.containerPadding = {
                top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            };
        }
        else if (this.fontSizeScale >= u.LEVEL1) {
            this.containerPadding = {
                top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            };
        }
        else {
            this.containerPadding = undefined;
        }
    }
    isSingleLine() {
        return !this.contentItem?.secondaryText && !this.contentItem?.description;
    }
    getOperateOffset() {
        if (this.containerDirection === FlexDirection.Row) {
            return LengthMetrics.vp(0);
        }
        let iconSize = w2.get(this.contentItem?.iconStyle);
        if (this.contentItem?.icon && iconSize && iconSize <= q1) {
            return LengthMetrics.vp(iconSize + z1 + g1 - this.textArrowLeftSafeOffset);
        }
        return LengthMetrics.vp(g1 - this.textArrowLeftSafeOffset);
    }
    getMainSpace() {
        if (this.containerDirection === FlexDirection.Column) {
            return LengthMetrics.resource(this.isSingleLine() ? { 'id': -1, 'type': 10002, params: ['sys.float.padding_level1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
        }
        return LengthMetrics.vp(0);
    }
    getFlexOptions() {
        if (this.containerDirection === FlexDirection.Column) {
            return {
                space: { main: this.getMainSpace() },
                justifyContent: FlexAlign.Center,
                alignItems: ItemAlign.Start,
                direction: this.containerDirection,
            };
        }
        return {
            justifyContent: FlexAlign.SpaceBetween,
            alignItems: ItemAlign.Center,
            direction: this.containerDirection,
        };
    }
    decideFontSizeScale() {
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(this.maxFontScale, this.getUIContext().getHostContext()?.config.fontSizeScale ?? 1);
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.width('100%');
            Stack.padding({
                left: i1,
                right: i1
            });
        }, Stack);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Flex.create(this.getFlexOptions());
            Flex.height(this.containerDirection === FlexDirection.Column ? 'auto' : undefined);
            Flex.constraintSize({
                minHeight: this.itemHeight
            });
            Flex.focusable(true);
            Flex.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Flex.backgroundColor(ObservedObject.GetRawObject(this.frontColor));
            Flex.onFocus(() => {
                this.canFocus = true;
            });
            Flex.onBlur(() => {
                this.canFocus = false;
            });
            Flex.onHover((isHover) => {
                this.isHover = isHover;
                if (this.canHover) {
                    this.frontColor = isHover ? this.hoveringColor :
                        (this.isActive ? this.activedColor : Color.Transparent.toString());
                }
            });
            ViewStackProcessor.visualState('pressed');
            Flex.backgroundColor(ObservedObject.GetRawObject(this.touchDownColor));
            ViewStackProcessor.visualState('normal');
            Flex.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                width: d1,
                color: Color.Transparent
            });
            ViewStackProcessor.visualState('focused');
            Flex.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                width: d1,
                color: this.focusOutlineColor,
                style: BorderStyle.Solid
            });
            ViewStackProcessor.visualState();
            Flex.padding(ObservedObject.GetRawObject(this.containerPadding));
        }, Flex);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.contentItem === null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            if (isInitialRender) {
                                let componentCall = new z2(this, {}, undefined, elmtId, () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 1051, d3: 11 });
                                ViewPU.create(componentCall);
                                let paramsLambda = () => {
                                    return {};
                                };
                                componentCall.paramsGenerator_ = paramsLambda;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(elmtId, {});
                            }
                        }, { name: 'ContentItemStruct' });
                    }
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
            if (this.contentItem !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            if (isInitialRender) {
                                let componentCall = new z2(this, {
                                    icon: this.contentItem?.icon,
                                    symbolStyle: this.contentItem?.symbolStyle,
                                    iconStyle: this.contentItem?.iconStyle,
                                    primaryText: this.contentItem?.primaryText,
                                    secondaryText: this.contentItem?.secondaryText,
                                    description: this.contentItem?.description,
                                    fontSizeScale: this.fontSizeScale,
                                    parentDirection: this.containerDirection,
                                    itemDirection: this.contentItemDirection,
                                }, undefined, elmtId, () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 1054, d3: 11 });
                                ViewPU.create(componentCall);
                                let paramsLambda = () => {
                                    return {
                                        icon: this.contentItem?.icon,
                                        symbolStyle: this.contentItem?.symbolStyle,
                                        iconStyle: this.contentItem?.iconStyle,
                                        primaryText: this.contentItem?.primaryText,
                                        secondaryText: this.contentItem?.secondaryText,
                                        description: this.contentItem?.description,
                                        fontSizeScale: this.fontSizeScale,
                                        parentDirection: this.containerDirection,
                                        itemDirection: this.contentItemDirection
                                    };
                                };
                                componentCall.paramsGenerator_ = paramsLambda;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(elmtId, {
                                    icon: this.contentItem?.icon,
                                    symbolStyle: this.contentItem?.symbolStyle,
                                    iconStyle: this.contentItem?.iconStyle,
                                    primaryText: this.contentItem?.primaryText,
                                    secondaryText: this.contentItem?.secondaryText,
                                    description: this.contentItem?.description,
                                    fontSizeScale: this.fontSizeScale,
                                    parentDirection: this.containerDirection,
                                    itemDirection: this.contentItemDirection
                                });
                            }
                        }, { name: 'ContentItemStruct' });
                    }
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
            if (this.operateItem !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        __Common__.create();
                        __Common__.flexShrink(0);
                        __Common__.onFocus(() => {
                            this.canFocus = false;
                        });
                        __Common__.onBlur(() => {
                            this.canFocus = true;
                        });
                        __Common__.padding({ start: this.getOperateOffset() });
                    }, __Common__);
                    {
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            if (isInitialRender) {
                                let componentCall = new b3(this, {
                                    icon: this.operateItem?.icon,
                                    subIcon: this.operateItem?.subIcon,
                                    button: this.operateItem?.button,
                                    switch: this.operateItem?.switch,
                                    checkBox: this.operateItem?.checkbox,
                                    radio: this.operateItem?.radio,
                                    image: this.operateItem?.image,
                                    symbolStyle: this.operateItem?.symbolStyle,
                                    text: this.operateItem?.text,
                                    arrow: this.operateItem?.arrow,
                                    parentCanFocus: this.x4,
                                    parentCanTouch: this.y4,
                                    parentIsHover: this.a5,
                                    parentFrontColor: this.v4,
                                    parentIsActive: this.c5,
                                    parentCanHover: this.z4,
                                    rightWidth: this.calculatedRightWidth(),
                                    parentDirection: this.f5,
                                }, undefined, elmtId, () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 1067, d3: 11 });
                                ViewPU.create(componentCall);
                                let paramsLambda = () => {
                                    return {
                                        icon: this.operateItem?.icon,
                                        subIcon: this.operateItem?.subIcon,
                                        button: this.operateItem?.button,
                                        switch: this.operateItem?.switch,
                                        checkBox: this.operateItem?.checkbox,
                                        radio: this.operateItem?.radio,
                                        image: this.operateItem?.image,
                                        symbolStyle: this.operateItem?.symbolStyle,
                                        text: this.operateItem?.text,
                                        arrow: this.operateItem?.arrow,
                                        parentCanFocus: this.canFocus,
                                        parentCanTouch: this.canTouch,
                                        parentIsHover: this.isHover,
                                        parentFrontColor: this.frontColor,
                                        parentIsActive: this.isActive,
                                        parentCanHover: this.canHover,
                                        rightWidth: this.calculatedRightWidth(),
                                        parentDirection: this.containerDirection
                                    };
                                };
                                componentCall.paramsGenerator_ = paramsLambda;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(elmtId, {
                                    icon: this.operateItem?.icon,
                                    subIcon: this.operateItem?.subIcon,
                                    button: this.operateItem?.button,
                                    switch: this.operateItem?.switch,
                                    checkBox: this.operateItem?.checkbox,
                                    radio: this.operateItem?.radio,
                                    image: this.operateItem?.image,
                                    symbolStyle: this.operateItem?.symbolStyle,
                                    text: this.operateItem?.text,
                                    arrow: this.operateItem?.arrow,
                                    rightWidth: this.calculatedRightWidth()
                                });
                            }
                        }, { name: 'OperateItemStruct' });
                    }
                    __Common__.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Flex.pop();
        Stack.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}

export default { IconType, ComposeListItem };