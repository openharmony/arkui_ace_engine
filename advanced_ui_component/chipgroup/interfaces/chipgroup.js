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

const noop = (v4) => {
};
const colorStops = [['rgba(0, 0, 0, 1)', 0], ['rgba(0, 0, 0, 0)', 1]];
const defaultTheme = {
    itemStyle: {
        size: ChipSize.NORMAL,
        backgroundColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_button_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        fontColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        selectedFontColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary_contrary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        selectedBackgroundColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_emphasize'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        fillColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        selectedFillColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary_contrary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    },
    chipGroupSpace: { itemSpace: 8, startSpace: 16, endSpace: 16 },
    chipGroupPadding: { top: 14, bottom: 14 }
};
const iconGroupSuffixTheme = {
    backgroundColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_button_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    borderRadius: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_tips_instant_tip'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    smallIconSize: 16,
    normalIconSize: 24,
    smallBackgroundSize: 28,
    normalBackgroundSize: 36,
    marginLeft: 8,
    marginRight: 16,
    fillColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
};
var ChipGroupHeight;
(function (u4) {
    u4[u4["NORMAL"] = 64] = "NORMAL";
    u4[u4["SMALL"] = 52] = "SMALL";
    u4[u4["DEFAULT"] = 64] = "DEFAULT";
    u4[u4["AMEND"] = 32] = "AMEND";
})(ChipGroupHeight || (ChipGroupHeight = {}));
function parseDimension(o4, p4, q4, r4) {
    if (p4 === void (0) || p4 === null) {
        return r4;
    }
    const s4 = o4.getHostContext()?.resourceManager;
    if (typeof p4 === "object") {
        let t4 = p4;
        if (t4.type === 10002 || t4.type === 10007) {
            if (s4.getNumber(t4.id) >= 0) {
                return p4;
            }
        }
        else if (t4.type === 10003) {
            if (isValidDimensionString(s4.getStringSync(t4.id))) {
                return p4;
            }
        }
    }
    else if (typeof p4 === "number") {
        if (p4 >= 0) {
            return p4;
        }
    }
    else if (typeof p4 === "string") {
        if (q4(p4)) {
            return p4;
        }
    }
    return r4;
}
function isValidString(k4, l4) {
    const m4 = k4.match(l4);
    if (!m4 || m4.length < 3) {
        return false;
    }
    const n4 = Number.parseFloat(m4[1]);
    return n4 >= 0;
}
function isValidDimensionString(j4) {
    return isValidString(j4, new RegExp("(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$", "i"));
}
function isValidDimensionNoPercentageString(i4) {
    return isValidString(i4, new RegExp("(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx)?$", "i"));
}
export class IconGroupSuffix extends ViewPU {
    constructor(c4, d4, e4, f4 = -1, g4 = undefined, h4) {
        super(c4, e4, f4, h4);
        if (typeof g4 === "function") {
            this.paramsGenerator_ = g4;
        }
        this.__chipSize = this.initializeConsume("chipSize", "chipSize");
        this.__items = new SynchedPropertyObjectOneWayPU(d4.items, this, "items");
        this.setInitiallyProvidedValue(d4);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(b4) {
        if (b4.items === undefined) {
            this.__items.set([]);
        }
    }
    updateStateVars(a4) {
        this.__items.reset(a4.items);
    }
    purgeVariableDependenciesOnElmtId(z3) {
        this.__chipSize.purgeDependencyOnElmtId(z3);
        this.__items.purgeDependencyOnElmtId(z3);
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
    set chipSize(y3) {
        this.__chipSize.set(y3);
    }
    get items() {
        return this.__items.get();
    }
    set items(x3) {
        this.__items.set(x3);
    }
    getBackgroundSize() {
        if (this.chipSize === ChipSize.SMALL) {
            return iconGroupSuffixTheme.smallBackgroundSize;
        }
        else {
            return iconGroupSuffixTheme.normalBackgroundSize;
        }
    }
    getIconSize(v3) {
        if (v3 === undefined) {
            return this.chipSize === ChipSize.SMALL ?
                iconGroupSuffixTheme.smallIconSize :
                iconGroupSuffixTheme.normalIconSize;
        }
        let w3;
        if (this.chipSize === ChipSize.SMALL) {
            w3 = parseDimension(this.getUIContext(), v3, isValidDimensionString, iconGroupSuffixTheme.smallIconSize);
        }
        else {
            w3 = parseDimension(this.getUIContext(), v3, isValidDimensionString, iconGroupSuffixTheme.normalIconSize);
        }
        return w3;
    }
    initialRender() {
        this.observeComponentCreation2((t3, u3) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((y2, z2) => {
            ForEach.create();
            const a3 = c3 => {
                const d3 = c3;
                this.observeComponentCreation2((q3, r3) => {
                    Button.createWithChild();
                    Button.size({
                        width: this.getBackgroundSize(),
                        height: this.getBackgroundSize()
                    });
                    Button.backgroundColor(iconGroupSuffixTheme.backgroundColor);
                    Button.borderRadius(iconGroupSuffixTheme.borderRadius);
                    Button.onClick(() => {
                        if (!(d3 instanceof SymbolGlyphModifier)) {
                            d3.action();
                        }
                    });
                    Button.borderRadius(iconGroupSuffixTheme.borderRadius);
                }, Button);
                this.observeComponentCreation2((g3, h3) => {
                    If.create();
                    if (d3 instanceof SymbolGlyphModifier) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((o3, p3) => {
                                SymbolGlyph.create();
                                SymbolGlyph.fontColor([iconGroupSuffixTheme.fillColor]);
                                SymbolGlyph.fontSize(this.getIconSize());
                                SymbolGlyph.attributeModifier.bind(this)(d3);
                                SymbolGlyph.focusable(true);
                            }, SymbolGlyph);
                        });
                    }
                    else {
                        this.ifElseBranchUpdateFunction(1, () => {
                            this.observeComponentCreation2((k3, l3) => {
                                Image.create(d3.icon.src);
                                Image.fillColor(iconGroupSuffixTheme.fillColor);
                                Image.size({
                                    width: this.getIconSize(d3.icon?.size?.width),
                                    height: this.getIconSize(d3.icon?.size?.height)
                                });
                                Image.focusable(true);
                            }, Image);
                        });
                    }
                }, If);
                If.pop();
                Button.pop();
            };
            this.forEachUpdateFunction(y2, this.items || [], a3);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
export class ChipGroup extends ViewPU {
    constructor(q2, r2, s2, t2 = -1, u2 = undefined, v2) {
        super(q2, s2, t2, v2);
        if (typeof u2 === "function") {
            this.paramsGenerator_ = u2;
        }
        this.__items = new SynchedPropertyObjectOneWayPU(r2.items, this, "items");
        this.__itemStyle = new SynchedPropertyObjectOneWayPU(r2.itemStyle, this, "itemStyle");
        this.__chipSize = new ObservedPropertyObjectPU(defaultTheme.itemStyle.size, this, "chipSize");
        this.addProvidedVar("chipSize", this.__chipSize, false);
        this.__selectedIndexes = new SynchedPropertyObjectOneWayPU(r2.selectedIndexes, this, "selectedIndexes");
        this.__multiple = new SynchedPropertySimpleOneWayPU(r2.multiple, this, "multiple");
        this.__chipGroupSpace = new SynchedPropertyObjectOneWayPU(r2.chipGroupSpace, this, "chipGroupSpace");
        this.suffix = undefined;
        this.onChange = noop;
        this.scroller = new Scroller();
        this.__isReachEnd = new ObservedPropertySimplePU(this.scroller.isAtEnd(), this, "isReachEnd");
        this.__chipGroupPadding = new SynchedPropertyObjectOneWayPU(r2.chipGroupPadding, this, "chipGroupPadding");
        this.setInitiallyProvidedValue(r2);
        this.declareWatch("itemStyle", this.itemStyleOnChange);
        this.declareWatch("multiple", this.onMultipleChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(p2) {
        if (p2.items === undefined) {
            this.__items.set([]);
        }
        if (p2.itemStyle === undefined) {
            this.__itemStyle.set(defaultTheme.itemStyle);
        }
        if (p2.chipSize !== undefined) {
            this.chipSize = p2.chipSize;
        }
        if (p2.selectedIndexes === undefined) {
            this.__selectedIndexes.set([0]);
        }
        if (p2.multiple === undefined) {
            this.__multiple.set(false);
        }
        if (p2.chipGroupSpace === undefined) {
            this.__chipGroupSpace.set(defaultTheme.chipGroupSpace);
        }
        if (p2.suffix !== undefined) {
            this.suffix = p2.suffix;
        }
        if (p2.onChange !== undefined) {
            this.onChange = p2.onChange;
        }
        if (p2.scroller !== undefined) {
            this.scroller = p2.scroller;
        }
        if (p2.isReachEnd !== undefined) {
            this.isReachEnd = p2.isReachEnd;
        }
        if (p2.chipGroupPadding === undefined) {
            this.__chipGroupPadding.set(defaultTheme.chipGroupPadding);
        }
    }
    updateStateVars(o2) {
        this.__items.reset(o2.items);
        this.__itemStyle.reset(o2.itemStyle);
        this.__selectedIndexes.reset(o2.selectedIndexes);
        this.__multiple.reset(o2.multiple);
        this.__chipGroupSpace.reset(o2.chipGroupSpace);
        this.__chipGroupPadding.reset(o2.chipGroupPadding);
    }
    purgeVariableDependenciesOnElmtId(n2) {
        this.__items.purgeDependencyOnElmtId(n2);
        this.__itemStyle.purgeDependencyOnElmtId(n2);
        this.__chipSize.purgeDependencyOnElmtId(n2);
        this.__selectedIndexes.purgeDependencyOnElmtId(n2);
        this.__multiple.purgeDependencyOnElmtId(n2);
        this.__chipGroupSpace.purgeDependencyOnElmtId(n2);
        this.__isReachEnd.purgeDependencyOnElmtId(n2);
        this.__chipGroupPadding.purgeDependencyOnElmtId(n2);
    }
    aboutToBeDeleted() {
        this.__items.aboutToBeDeleted();
        this.__itemStyle.aboutToBeDeleted();
        this.__chipSize.aboutToBeDeleted();
        this.__selectedIndexes.aboutToBeDeleted();
        this.__multiple.aboutToBeDeleted();
        this.__chipGroupSpace.aboutToBeDeleted();
        this.__isReachEnd.aboutToBeDeleted();
        this.__chipGroupPadding.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get items() {
        return this.__items.get();
    }
    set items(m2) {
        this.__items.set(m2);
    }
    get itemStyle() {
        return this.__itemStyle.get();
    }
    set itemStyle(l2) {
        this.__itemStyle.set(l2);
    }
    get chipSize() {
        return this.__chipSize.get();
    }
    set chipSize(k2) {
        this.__chipSize.set(k2);
    }
    get selectedIndexes() {
        return this.__selectedIndexes.get();
    }
    set selectedIndexes(j2) {
        this.__selectedIndexes.set(j2);
    }
    get multiple() {
        return this.__multiple.get();
    }
    set multiple(i2) {
        this.__multiple.set(i2);
    }
    get chipGroupSpace() {
        return this.__chipGroupSpace.get();
    }
    set chipGroupSpace(h2) {
        this.__chipGroupSpace.set(h2);
    }
    get isReachEnd() {
        return this.__isReachEnd.get();
    }
    set isReachEnd(g2) {
        this.__isReachEnd.set(g2);
    }
    get chipGroupPadding() {
        return this.__chipGroupPadding.get();
    }
    set chipGroupPadding(f2) {
        this.__chipGroupPadding.set(f2);
    }
    onMultipleChange() {
        this.selectedIndexes = this.getSelectedIndexes();
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
        if (typeof this.itemStyle.fontColor == 'object') {
            let e2 = this.itemStyle.fontColor;
            if (e2 == undefined || e2 == null) {
                return defaultTheme.itemStyle.fontColor;
            }
            if (e2.type === 10001) {
                return this.itemStyle.fontColor;
            }
            return defaultTheme.itemStyle.fontColor;
        }
        if (this.itemStyle && this.itemStyle.fontColor) {
            return this.itemStyle.fontColor;
        }
        return defaultTheme.itemStyle.fontColor;
    }
    getSelectedFontColor() {
        if (typeof this.itemStyle.selectedFontColor == 'object') {
            let d2 = this.itemStyle.selectedFontColor;
            if (d2 == undefined || d2 == null) {
                return defaultTheme.itemStyle.selectedFontColor;
            }
            if (d2.type === 10001) {
                return this.itemStyle.selectedFontColor;
            }
            return defaultTheme.itemStyle.selectedFontColor;
        }
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
        if (typeof this.itemStyle.backgroundColor == 'object') {
            let c2 = this.itemStyle.backgroundColor;
            if (c2 == undefined || c2 == null) {
                return defaultTheme.itemStyle.backgroundColor;
            }
            if (c2.type === 10001) {
                return this.itemStyle.backgroundColor;
            }
            return defaultTheme.itemStyle.backgroundColor;
        }
        if (this.itemStyle && this.itemStyle.backgroundColor) {
            return this.itemStyle.backgroundColor;
        }
        return defaultTheme.itemStyle.backgroundColor;
    }
    getSelectedBackgroundColor() {
        if (typeof this.itemStyle.selectedBackgroundColor == 'object') {
            let b2 = this.itemStyle.selectedBackgroundColor;
            if (b2 == undefined || b2 == null) {
                return defaultTheme.itemStyle.selectedBackgroundColor;
            }
            if (b2.type === 10001) {
                return this.itemStyle.selectedBackgroundColor;
            }
            return defaultTheme.itemStyle.selectedBackgroundColor;
        }
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
                y1 != null &&
                y1 != undefined &&
                a2.indexOf(y1) === z1 &&
                y1 < (this.items || []).length);
        });
        if (w1.length == 0) {
            w1 = [0];
        }
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
    getChipGroupHeight() {
        if (typeof this.chipSize === "string") {
            if (this.chipSize === ChipSize.NORMAL) {
                return ChipGroupHeight.NORMAL;
            }
            else {
                return ChipGroupHeight.SMALL;
            }
        }
        else if (typeof this.chipSize === "object") {
            return this.chipSize.height + ChipGroupHeight.AMEND;
        }
        else {
            return ChipGroupHeight.DEFAULT;
        }
    }
    getIconGroupSuffixHeight() {
        if (typeof this.chipSize === "string") {
            if (this.chipSize === ChipSize.SMALL) {
                return iconGroupSuffixTheme.smallBackgroundSize;
            }
            else {
                return iconGroupSuffixTheme.normalBackgroundSize;
            }
        }
        else if (typeof this.chipSize === "object") {
            return this.chipSize.height + ChipGroupHeight.AMEND;
        }
        else {
            return ChipGroupHeight.DEFAULT;
        }
    }
    getPaddingTop() {
        return parseDimension(this.getUIContext(), this.chipGroupPadding.top, isValidDimensionNoPercentageString, defaultTheme.chipGroupPadding.top);
    }
    getPaddingBottom() {
        return parseDimension(this.getUIContext(), this.chipGroupPadding.bottom, isValidDimensionNoPercentageString, defaultTheme.chipGroupPadding.bottom);
    }
    initialRender() {
        this.observeComponentCreation2((p1, q1) => {
            Row.create();
            Row.align(Alignment.End);
            Row.width("100%");
            Row.height(this.getChipGroupHeight());
            Row.padding({ top: this.getPaddingTop(), bottom: this.getPaddingBottom() });
        }, Row);
        this.observeComponentCreation2((n1, o1) => {
            Stack.create();
            Stack.layoutWeight(1);
            Stack.blendMode(BlendMode.SRC_OVER, BlendApplyType.OFFSCREEN);
            Stack.alignContent(Alignment.End);
        }, Stack);
        this.observeComponentCreation2((k1, l1) => {
            Scroll.create(this.scroller);
            Scroll.scrollable(ScrollDirection.Horizontal);
            Scroll.scrollBar(BarState.Off);
            Scroll.align(Alignment.Start);
            Scroll.width('100%');
            Scroll.onScroll(() => {
                this.isReachEnd = this.scroller.isAtEnd();
            });
        }, Scroll);
        this.observeComponentCreation2((i1, j1) => {
            Row.create({ space: this.getChipGroupItemSpace() });
            Row.padding({ left: this.getChipGroupStartSpace(),
                right: this.getChipGroupEndSpace() });
            Row.constraintSize({ minWidth: '100%' });
        }, Row);
        this.observeComponentCreation2((v, w) => {
            ForEach.create();
            const x = (z, a1) => {
                const b1 = z;
                this.observeComponentCreation2((d1, e1) => {
                    If.create();
                    if (b1) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            Chip.bind(this)(makeBuilderParameterProxy("Chip", { prefixIcon: () => ({
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
                                        if (!(!this.isMultiple())) {
                                            if (this.getSelectedIndexes().length > 1) {
                                                this.selectedIndexes.splice(this.selectedIndexes.indexOf(a1), 1);
                                            }
                                        }
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
                }, If);
                If.pop();
            };
            this.forEachUpdateFunction(v, this.items || [], x, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
        Scroll.pop();
        this.observeComponentCreation2((o, p) => {
            If.create();
            if (this.suffix && !this.isReachEnd) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((t, u) => {
                        Stack.create();
                        Stack.width(iconGroupSuffixTheme.normalBackgroundSize);
                        Stack.height(this.getIconGroupSuffixHeight());
                        Stack.linearGradient({ angle: 90, colors: colorStops });
                        Stack.blendMode(BlendMode.DST_IN, BlendApplyType.OFFSCREEN);
                        Stack.hitTestBehavior(HitTestMode.None);
                    }, Stack);
                    Stack.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Stack.pop();
        this.observeComponentCreation2((h, i) => {
            If.create();
            if (this.suffix) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((m, n) => {
                        Row.create();
                        Row.padding({ left: iconGroupSuffixTheme.marginLeft, right: iconGroupSuffixTheme.marginRight });
                    }, Row);
                    this.suffix.bind(this)(this);
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
    }
    rerender() {
        this.updateDirtyElements();
    }
}

export default {
    ChipGroup,
    IconGroupSuffix
}