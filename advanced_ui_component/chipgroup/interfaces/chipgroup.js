/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to  in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

const Chip = requireNapi('arkui.advanced.Chip').Chip;
const ChipSize = requireNapi('arkui.advanced.Chip').ChipSize;
const SymbolOptions = requireNapi('arkui.advanced.Chip').SymbolOptions;
const SymbolGlyphModifier = requireNapi('arkui.modifier').SymbolGlyphModifier;

if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => { });
}

const noop = (p4) => {
};
const colorStops = [['rgba(0, 0, 0, 1)', 0], ['rgba(0, 0, 0, 0)', 1]];
const defaultTheme = {
    itemStyle: {
        size: ChipSize.NORMAL,
        backgroundColor: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_button_normal'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        fontColor: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        selectedFontColor: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary_contrary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        selectedBackgroundColor: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_emphasize'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        fillColor: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        selectedFillColor: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary_contrary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
    },
    chipGroupSpace: { itemSpace: 8, startSpace: 16, endSpace: 16 },
};
const iconGroupSuffixTheme = {
    backgroundColor: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_button_normal'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
    borderRadius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_tips_instant_tip'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
    smallIconSize: 16,
    normalIconSize: 24,
    smallBackgroundSize: 28,
    normalBackgroundSize: 36,
    marginLeft: 8,
    marginRight: 16,
    fillColor: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }
};
function parseDimension(j4, k4, l4, m4) {
    if (k4 === void (0) || k4 === null) {
        return m4;
    }
    const n4 = j4.getHostContext()?.resourceManager;
    if (typeof k4 === 'object') {
        let o4 = k4;
        if (o4.type === 10002) {
            if (n4.getNumber(o4.id) >= 0) {
                return k4;
            }
        }
        else if (o4.type === 10003) {
            if (isValidDimensionString(n4.getStringSync(o4.id))) {
                return k4;
            }
        }
    }
    else if (typeof k4 === 'number') {
        if (k4 >= 0) {
            return k4;
        }
    }
    else if (typeof k4 === 'string') {
        if (l4(k4)) {
            return k4;
        }
    }
    return m4;
}
function isValidString(f4, g4) {
    const h4 = f4.match(g4);
    if (!h4 || h4.length < 3) {
        return false;
    }
    const i4 = Number.parseFloat(h4[1]);
    return i4 >= 0;
}
function isValidDimensionString(e4) {
    return isValidString(e4, new RegExp("(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$", "i"));
}
function isValidDimensionNoPercentageString(d4) {
    return isValidString(d4, new RegExp("(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx)?$", "i"));
}
export class IconGroupSuffix extends ViewPU {
    constructor(x3, y3, z3, a4 = -1, b4 = undefined, c4) {
        super(x3, z3, a4, c4);
        if (typeof b4 === 'function') {
            this.paramsGenerator_ = b4;
        }
        this.__chipSize = this.initializeConsume('chipSize', 'chipSize');
        this.__items = new SynchedPropertyObjectOneWayPU(y3.items, this, 'items');
        this.setInitiallyProvidedValue(y3);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(w3) {
        if (w3.items === undefined) {
            this.__items.set([]);
        }
    }
    updateStateVars(v3) {
        this.__items.reset(v3.items);
    }
    purgeVariableDependenciesOnElmtId(u3) {
        this.__chipSize.purgeDependencyOnElmtId(u3);
        this.__items.purgeDependencyOnElmtId(u3);
    }
    aboutToBeDeleted() {
        this.__chipSize.aboutToBeDeleted();
        this.__items.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get chipSize() {
        return this.__chipSize.get();
    }
    set chipSize(t3) {
        this.__chipSize.set(t3);
    }
    get items() {
        return this.__items.get();
    }
    set items(s3) {
        this.__items.set(s3);
    }
    getBackgroundSize() {
        if (this.chipSize === ChipSize.SMALL) {
            return iconGroupSuffixTheme.smallBackgroundSize;
        }
        else {
            return iconGroupSuffixTheme.normalBackgroundSize;
        }
    }
    getIconSize(q3) {
        if (q3 === undefined) {
            return this.chipSize === ChipSize.SMALL ? iconGroupSuffixTheme.smallIconSize : iconGroupSuffixTheme.normalIconSize;
        }
        let r3;
        if (this.chipSize === ChipSize.SMALL) {
            r3 = parseDimension(this.getUIContext(), q3, isValidDimensionString, iconGroupSuffixTheme.smallIconSize);
        }
        else {
            r3 = parseDimension(this.getUIContext(), q3, isValidDimensionString, iconGroupSuffixTheme.normalIconSize);
        }
        return r3;
    }
    initialRender() {
        this.observeComponentCreation((o3, p3) => {
            ViewStackProcessor.StartGetAccessRecordingFor(o3);
            Row.create();
            if (!p3) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((t2, u2) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t2);
            ForEach.create();
            const v2 = x2 => {
                const y2 = x2;
                this.observeComponentCreation((l3, m3) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(l3);
                    Button.createWithChild();
                    Button.size({
                        width: this.getBackgroundSize(),
                        height: this.getBackgroundSize()
                    });
                    Button.backgroundColor(iconGroupSuffixTheme.backgroundColor);
                    Button.borderRadius(iconGroupSuffixTheme.borderRadius);
                    Button.onClick(() => {
                        if (!(y2 instanceof SymbolGlyphModifier)) {
                            y2.action();
                        }
                    });
                    Button.borderRadius(iconGroupSuffixTheme.borderRadius);
                    if (!m3) {
                        Button.pop();
                    }
                    ViewStackProcessor.StopGetAccessRecording();
                });
                this.observeComponentCreation((b3, c3) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(b3);
                    If.create();
                    if (y2 instanceof SymbolGlyphModifier) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation((j3, k3) => {
                                ViewStackProcessor.StartGetAccessRecordingFor(j3);
                                SymbolGlyph.create();
                                SymbolGlyph.fontColor([iconGroupSuffixTheme.fillColor]);
                                SymbolGlyph.fontSize(this.getIconSize(''));
                                SymbolGlyph.attributeModifier.bind(this)(y2);
                                SymbolGlyph.focusable(true);
                                if (!k3) {
                                    SymbolGlyph.pop();
                                }
                                ViewStackProcessor.StopGetAccessRecording();
                            });
                        });
                    }
                    else {
                        this.ifElseBranchUpdateFunction(1, () => {
                            this.observeComponentCreation((f3, g3) => {
                                ViewStackProcessor.StartGetAccessRecordingFor(f3);
                                Image.create(y2.icon.src);
                                Image.fillColor(iconGroupSuffixTheme.fillColor);
                                Image.size({
                                    width: this.getIconSize(y2.icon?.size?.width),
                                    height: this.getIconSize(y2.icon?.size?.height)
                                });
                                Image.focusable(true);
                                if (!g3) {
                                    Image.pop();
                                }
                                ViewStackProcessor.StopGetAccessRecording();
                            });
                        });
                    }
                    if (!c3) {
                        If.pop();
                    }
                    ViewStackProcessor.StopGetAccessRecording();
                });
                If.pop();
                Button.pop();
            };
            this.forEachUpdateFunction(t2, this.items || [], v2);
            if (!u2) {
                ForEach.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        ForEach.pop();
        Row.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
export class ChipGroup extends ViewPU {
    constructor(l2, m2, n2, o2 = -1, p2 = undefined, q2) {
        super(l2, n2, o2, q2);
        if (typeof p2 === 'function') {
            this.paramsGenerator_ = p2;
        }
        this.__items = new SynchedPropertyObjectOneWayPU(m2.items, this, 'items');
        this.__itemStyle = new SynchedPropertyObjectOneWayPU(m2.itemStyle, this, 'itemStyle');
        this.__chipSize = new ObservedPropertyObjectPU(defaultTheme.itemStyle.size, this, 'chipSize');
        this.addProvidedVar('chipSize', this.__chipSize, false);
        this.__selectedIndexes = new SynchedPropertyObjectOneWayPU(m2.selectedIndexes, this, 'selectedIndexes');
        this.__multiple = new SynchedPropertySimpleOneWayPU(m2.multiple, this, 'multiple');
        this.__chipGroupSpace = new SynchedPropertyObjectOneWayPU(m2.chipGroupSpace, this, 'chipGroupSpace');
        this.suffix = undefined;
        this.onChange = noop;
        this.scroller = new Scroller();
        this.__isReachEnd = new ObservedPropertySimplePU(this.scroller.isAtEnd(), this, 'isReachEnd');
        this.setInitiallyProvidedValue(m2);
        this.declareWatch('itemStyle', this.itemStyleOnChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(k2) {
        if (k2.items === undefined) {
            this.__items.set([]);
        }
        if (k2.itemStyle === undefined) {
            this.__itemStyle.set(defaultTheme.itemStyle);
        }
        if (k2.chipSize !== undefined) {
            this.chipSize = k2.chipSize;
        }
        if (k2.selectedIndexes === undefined) {
            this.__selectedIndexes.set([0]);
        }
        if (k2.multiple === undefined) {
            this.__multiple.set(false);
        }
        if (k2.chipGroupSpace === undefined) {
            this.__chipGroupSpace.set(defaultTheme.chipGroupSpace);
        }
        if (k2.suffix !== undefined) {
            this.suffix = k2.suffix;
        }
        if (k2.onChange !== undefined) {
            this.onChange = k2.onChange;
        }
        if (k2.scroller !== undefined) {
            this.scroller = k2.scroller;
        }
        if (k2.isReachEnd !== undefined) {
            this.isReachEnd = k2.isReachEnd;
        }
    }
    updateStateVars(j2) {
        this.__items.reset(j2.items);
        this.__itemStyle.reset(j2.itemStyle);
        this.__selectedIndexes.reset(j2.selectedIndexes);
        this.__multiple.reset(j2.multiple);
        this.__chipGroupSpace.reset(j2.chipGroupSpace);
    }
    purgeVariableDependenciesOnElmtId(i2) {
        this.__items.purgeDependencyOnElmtId(i2);
        this.__itemStyle.purgeDependencyOnElmtId(i2);
        this.__chipSize.purgeDependencyOnElmtId(i2);
        this.__selectedIndexes.purgeDependencyOnElmtId(i2);
        this.__multiple.purgeDependencyOnElmtId(i2);
        this.__chipGroupSpace.purgeDependencyOnElmtId(i2);
        this.__isReachEnd.purgeDependencyOnElmtId(i2);
    }
    aboutToBeDeleted() {
        this.__items.aboutToBeDeleted();
        this.__itemStyle.aboutToBeDeleted();
        this.__chipSize.aboutToBeDeleted();
        this.__selectedIndexes.aboutToBeDeleted();
        this.__multiple.aboutToBeDeleted();
        this.__chipGroupSpace.aboutToBeDeleted();
        this.__isReachEnd.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get items() {
        return this.__items.get();
    }
    set items(h2) {
        this.__items.set(h2);
    }
    get itemStyle() {
        return this.__itemStyle.get();
    }
    set itemStyle(g2) {
        this.__itemStyle.set(g2);
    }
    get chipSize() {
        return this.__chipSize.get();
    }
    set chipSize(f2) {
        this.__chipSize.set(f2);
    }
    get selectedIndexes() {
        return this.__selectedIndexes.get();
    }
    set selectedIndexes(e2) {
        this.__selectedIndexes.set(e2);
    }
    get multiple() {
        return this.__multiple.get();
    }
    set multiple(d2) {
        this.__multiple.set(d2);
    }
    get chipGroupSpace() {
        return this.__chipGroupSpace.get();
    }
    set chipGroupSpace(c2) {
        this.__chipGroupSpace.set(c2);
    }
    get isReachEnd() {
        return this.__isReachEnd.get();
    }
    set isReachEnd(b2) {
        this.__isReachEnd.set(b2);
    }
    itemStyleOnChange() {
        this.chipSize = this.getChipSize();
    }
    aboutToAppear() {
        this.itemStyleOnChange();
    }
    getChipSize() {
        if (this.itemStyle && this.itemStyle.size) {
            return this.itemStyle.size;
        }
        return defaultTheme.itemStyle.size;
    }
    getFontColor() {
        if (this.itemStyle && this.itemStyle.fontColor) {
            return this.itemStyle.fontColor;
        }
        return defaultTheme.itemStyle.fontColor;
    }
    getSelectedFontColor() {
        if (this.itemStyle && this.itemStyle.selectedFontColor) {
            return this.itemStyle.selectedFontColor;
        }
        return defaultTheme.itemStyle.selectedFontColor;
    }
    getFillColor() {
        if (this.itemStyle && this.itemStyle.fontColor) {
            return this.itemStyle.fontColor;
        }
        return defaultTheme.itemStyle.fillColor;
    }
    getSelectedFillColor() {
        if (this.itemStyle && this.itemStyle.selectedFontColor) {
            return this.itemStyle.selectedFontColor;
        }
        return defaultTheme.itemStyle.selectedFillColor;
    }
    getBackgroundColor() {
        if (this.itemStyle && this.itemStyle.backgroundColor) {
            return this.itemStyle.backgroundColor;
        }
        return defaultTheme.itemStyle.backgroundColor;
    }
    getSelectedBackgroundColor() {
        if (this.itemStyle && this.itemStyle.selectedBackgroundColor) {
            return this.itemStyle.selectedBackgroundColor;
        }
        return defaultTheme.itemStyle.selectedBackgroundColor;
    }
    getSelectedIndexes() {
        let w1 = [];
        w1 = (this.selectedIndexes ?? [0]).filter((y1, z1, a2) => {
            return (y1 >= 0 &&
                y1 % 1 == 0 &&
                a2.indexOf(y1) === z1 &&
                y1 < (this.items || []).length);
        });
        return w1;
    }
    isMultiple() {
        return this.multiple ?? false;
    }
    getChipGroupItemSpace() {
        return parseDimension(this.getUIContext(), this.chipGroupSpace.itemSpace, isValidDimensionNoPercentageString, defaultTheme.chipGroupSpace.itemSpace);
    }
    getChipGroupStartSpace() {
        return parseDimension(this.getUIContext(), this.chipGroupSpace.startSpace, isValidDimensionNoPercentageString, defaultTheme.chipGroupSpace.startSpace);
    }
    getChipGroupEndSpace() {
        return parseDimension(this.getUIContext(), this.chipGroupSpace.endSpace, isValidDimensionNoPercentageString, defaultTheme.chipGroupSpace.endSpace);
    }
    getOnChange() {
        return this.onChange ?? noop;
    }
    isSelected(r1) {
        if (!this.isMultiple()) {
            return r1 == this.getSelectedIndexes()[0];
        }
        else {
            return this.getSelectedIndexes().some((t1, u1, v1) => {
                return (t1 == r1);
            });
        }
    }
    initialRender() {
        this.observeComponentCreation((p1, q1) => {
            ViewStackProcessor.StartGetAccessRecordingFor(p1);
            Row.create();
            Row.align(Alignment.End);
            Row.width('100%');
            Row.height(64);
            if (!q1) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((n1, o1) => {
            ViewStackProcessor.StartGetAccessRecordingFor(n1);
            Stack.create();
            Stack.layoutWeight(1);
            Stack.blendMode(BlendMode.SRC_OVER, BlendApplyType.OFFSCREEN);
            Stack.alignContent(Alignment.End);
            if (!o1) {
                Stack.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((k1, l1) => {
            ViewStackProcessor.StartGetAccessRecordingFor(k1);
            Scroll.create(this.scroller);
            Scroll.scrollable(ScrollDirection.Horizontal);
            Scroll.scrollBar(BarState.Off);
            Scroll.align(Alignment.Start);
            Scroll.width('100%');
            Scroll.onScroll(() => {
                this.isReachEnd = this.scroller.isAtEnd();
            });
            if (!l1) {
                Scroll.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((i1, j1) => {
            ViewStackProcessor.StartGetAccessRecordingFor(i1);
            Row.create({ space: this.getChipGroupItemSpace() });
            Row.padding({ left: this.getChipGroupStartSpace(),
                right: this.getChipGroupEndSpace() });
            Row.constraintSize({ minWidth: '100%' });
            if (!j1) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((v, w) => {
            ViewStackProcessor.StartGetAccessRecordingFor(v);
            ForEach.create();
            const x = (z, a1) => {
                const b1 = z;
                this.observeComponentCreation((d1, e1) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(d1);
                    If.create();
                    if (b1) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            Chip.bind(this)(makeBuilderParameterProxy('Chip', { prefixIcon: () => ({
                                    src: b1.prefixIcon?.src ?? "",
                                    size: b1.prefixIcon?.size ?? undefined,
                                    fillColor: this.getFillColor(),
                                    activatedFillColor: this.getSelectedFillColor()
                                }), prefixSymbol: () => b1?.prefixSymbol, label: () => ({
                                    text: b1?.label?.text ?? " ",
                                    fontColor: this.getFontColor(),
                                    activatedFontColor: this.getSelectedFontColor(),
                                }), suffixIcon: () => ({
                                    src: b1.suffixIcon?.src ?? "",
                                    size: b1.suffixIcon?.size ?? undefined,
                                    fillColor: this.getFillColor(),
                                    activatedFillColor: this.getSelectedFillColor()
                                }), suffixSymbol: () => b1?.suffixSymbol, allowClose: () => b1.allowClose ?? false, enabled: () => true, activated: () => this.isSelected(a1), backgroundColor: () => this.getBackgroundColor(), size: () => this.getChipSize(), activatedBackgroundColor: () => this.getSelectedBackgroundColor(), onClicked: () => () => {
                                    if (this.isSelected(a1)) {
                                        this.selectedIndexes.splice(this.selectedIndexes.indexOf(a1), 1);
                                    }
                                    else {
                                        if (!this.isMultiple()) {
                                            this.selectedIndexes = [];
                                        }
                                        this.selectedIndexes.push(a1);
                                    }
                                    this.getOnChange()(this.getSelectedIndexes());
                                } }), this);
                        });
                    }
                    else {
                        this.ifElseBranchUpdateFunction(1, () => {
                        });
                    }
                    if (!e1) {
                        If.pop();
                    }
                    ViewStackProcessor.StopGetAccessRecording();
                });
                If.pop();
            };
            this.forEachUpdateFunction(v, this.items || [], x, undefined, true, false);
            if (!w) {
                ForEach.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        ForEach.pop();
        Row.pop();
        Scroll.pop();
        this.observeComponentCreation((o, p) => {
            ViewStackProcessor.StartGetAccessRecordingFor(o);
            If.create();
            if (this.suffix && !this.isReachEnd) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((t, u) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(t);
                        Stack.create();
                        Stack.width(iconGroupSuffixTheme.normalBackgroundSize);
                        Stack.height(this.getChipSize() === ChipSize.SMALL ?
                            iconGroupSuffixTheme.smallBackgroundSize :
                            iconGroupSuffixTheme.normalBackgroundSize);
                        Stack.linearGradient({ angle: 90, colors: colorStops });
                        Stack.blendMode(BlendMode.DST_IN, BlendApplyType.OFFSCREEN);
                        Stack.hitTestBehavior(HitTestMode.None);
                        if (!u) {
                            Stack.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    Stack.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!p) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        Stack.pop();
        this.observeComponentCreation((h, i) => {
            ViewStackProcessor.StartGetAccessRecordingFor(h);
            If.create();
            if (this.suffix) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((m, n) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(m);
                        Row.create();
                        Row.padding({ left: iconGroupSuffixTheme.marginLeft, right: iconGroupSuffixTheme.marginRight });
                        if (!n) {
                            Row.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.suffix.bind(this)(this);
                    Row.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!i) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        Row.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}

export default {
    ChipGroup,
    IconGroupSuffix
}