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

const noop = (g9) => {
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
function parseDimension(a9, b9, c9, d9) {
    if (b9 === void (0) || b9 === null) {
        return d9;
    }
    const e9 = a9.getHostContext()?.resourceManager;
    if (typeof b9 === "object") {
        let f9 = b9;
        if (f9.type === 10002 || f9.type === 10007) {
            if (e9.getNumber(f9.id) >= 0) {
                return b9;
            }
        }
        else if (f9.type === 10003) {
            if (isValidDimensionString(e9.getStringSync(f9.id))) {
                return b9;
            }
        }
    }
    else if (typeof b9 === "number") {
        if (b9 >= 0) {
            return b9;
        }
    }
    else if (typeof b9 === "string") {
        if (c9(b9)) {
            return b9;
        }
    }
    return d9;
}
function isValidString(w8, x8) {
    const y8 = w8.match(x8);
    if (!y8 || y8.length < 3) {
        return false;
    }
    const z8 = Number.parseFloat(y8[1]);
    return z8 >= 0;
}
function isValidDimensionString(v8) {
    return isValidString(v8, new RegExp("(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$", "i"));
}
function isValidDimensionNoPercentageString(u8) {
    return isValidString(u8, new RegExp("(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx)?$", "i"));
}
export class IconGroupSuffix extends ViewPU {
    constructor(o8, p8, q8, r8 = -1, s8 = undefined, t8) {
        super(o8, q8, r8, t8);
        if (typeof s8 === "function") {
            this.paramsGenerator_ = s8;
        }
        this.__chipSize = this.initializeConsume("chipSize", "chipSize");
        this.__items = new SynchedPropertyObjectOneWayPU(p8.items, this, "items");
        this.setInitiallyProvidedValue(p8);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(n8) {
        if (n8.items === undefined) {
            this.__items.set([]);
        }
    }
    updateStateVars(m8) {
        this.__items.reset(m8.items);
    }
    purgeVariableDependenciesOnElmtId(l8) {
        this.__chipSize.purgeDependencyOnElmtId(l8);
        this.__items.purgeDependencyOnElmtId(l8);
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
    set chipSize(k8) {
        this.__chipSize.set(k8);
    }
    get items() {
        return this.__items.get();
    }
    set items(j8) {
        this.__items.set(j8);
    }
    getBackgroundSize() {
        if (this.chipSize === ChipSize.SMALL) {
            return iconGroupSuffixTheme.smallBackgroundSize;
        }
        else {
            return iconGroupSuffixTheme.normalBackgroundSize;
        }
    }
    getIconSize(h8) {
        if (h8 === undefined) {
            return this.chipSize === ChipSize.SMALL ? iconGroupSuffixTheme.smallIconSize : iconGroupSuffixTheme.normalIconSize;
        }
        let i8;
        if (this.chipSize === ChipSize.SMALL) {
            i8 = parseDimension(this.getUIContext(), h8, isValidDimensionString, iconGroupSuffixTheme.smallIconSize);
        }
        else {
            i8 = parseDimension(this.getUIContext(), h8, isValidDimensionString, iconGroupSuffixTheme.normalIconSize);
        }
        return i8;
    }
    initialRender() {
        this.observeComponentCreation2((f8, g8) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((k7, l7) => {
            ForEach.create();
            const m7 = o7 => {
                const p7 = o7;
                this.observeComponentCreation2((c8, d8) => {
                    Button.createWithChild();
                    Button.size({
                        width: this.getBackgroundSize(),
                        height: this.getBackgroundSize()
                    });
                    Button.backgroundColor(iconGroupSuffixTheme.backgroundColor);
                    Button.borderRadius(iconGroupSuffixTheme.borderRadius);
                    Button.onClick(() => {
                        if (!(p7 instanceof SymbolGlyphModifier)) {
                            p7.action();
                        }
                    });
                    Button.borderRadius(iconGroupSuffixTheme.borderRadius);
                }, Button);
                this.observeComponentCreation2((s7, t7) => {
                    If.create();
                    if (p7 instanceof SymbolGlyphModifier) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((a8, b8) => {
                                SymbolGlyph.create();
                                SymbolGlyph.fontColor([iconGroupSuffixTheme.fillColor]);
                                SymbolGlyph.fontSize(this.getIconSize());
                                SymbolGlyph.attributeModifier.bind(this)(p7);
                                SymbolGlyph.focusable(true);
                            }, SymbolGlyph);
                        });
                    }
                    else {
                        this.ifElseBranchUpdateFunction(1, () => {
                            this.observeComponentCreation2((w7, x7) => {
                                Image.create(p7.icon.src);
                                Image.fillColor(iconGroupSuffixTheme.fillColor);
                                Image.size({
                                    width: this.getIconSize(p7.icon?.size?.width),
                                    height: this.getIconSize(p7.icon?.size?.height)
                                });
                                Image.focusable(true);
                            }, Image);
                        });
                    }
                }, If);
                If.pop();
                Button.pop();
            };
            this.forEachUpdateFunction(k7, this.items || [], m7);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
export class ChipGroup extends ViewPU {
    constructor(c7, d7, e7, f7 = -1, g7 = undefined, h7) {
        super(c7, e7, f7, h7);
        if (typeof g7 === "function") {
            this.paramsGenerator_ = g7;
        }
        this.__items = new SynchedPropertyObjectOneWayPU(d7.items, this, "items");
        this.__itemStyle = new SynchedPropertyObjectOneWayPU(d7.itemStyle, this, "itemStyle");
        this.__chipSize = new ObservedPropertyObjectPU(defaultTheme.itemStyle.size, this, "chipSize");
        this.addProvidedVar("chipSize", this.__chipSize, false);
        this.__selectedIndexes = new SynchedPropertyObjectOneWayPU(d7.selectedIndexes, this, "selectedIndexes");
        this.__multiple = new SynchedPropertySimpleOneWayPU(d7.multiple, this, "multiple");
        this.__chipGroupSpace = new SynchedPropertyObjectOneWayPU(d7.chipGroupSpace, this, "chipGroupSpace");
        this.suffix = undefined;
        this.onChange = noop;
        this.scroller = new Scroller();
        this.__isReachEnd = new ObservedPropertySimplePU(this.scroller.isAtEnd(), this, "isReachEnd");
        this.__chipGroupPadding = new SynchedPropertyObjectOneWayPU(d7.chipGroupPadding, this, "chipGroupPadding");
        this.setInitiallyProvidedValue(d7);
        this.declareWatch("itemStyle", this.itemStyleOnChange);
        this.declareWatch("multiple", this.onMultipleChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(b7) {
        if (b7.items === undefined) {
            this.__items.set([]);
        }
        if (b7.itemStyle === undefined) {
            this.__itemStyle.set(defaultTheme.itemStyle);
        }
        if (b7.chipSize !== undefined) {
            this.chipSize = b7.chipSize;
        }
        if (b7.selectedIndexes === undefined) {
            this.__selectedIndexes.set([0]);
        }
        if (b7.multiple === undefined) {
            this.__multiple.set(false);
        }
        if (b7.chipGroupSpace === undefined) {
            this.__chipGroupSpace.set(defaultTheme.chipGroupSpace);
        }
        if (b7.suffix !== undefined) {
            this.suffix = b7.suffix;
        }
        if (b7.onChange !== undefined) {
            this.onChange = b7.onChange;
        }
        if (b7.scroller !== undefined) {
            this.scroller = b7.scroller;
        }
        if (b7.isReachEnd !== undefined) {
            this.isReachEnd = b7.isReachEnd;
        }
        if (b7.chipGroupPadding === undefined) {
            this.__chipGroupPadding.set(defaultTheme.chipGroupPadding);
        }
    }
    updateStateVars(a7) {
        this.__items.reset(a7.items);
        this.__itemStyle.reset(a7.itemStyle);
        this.__selectedIndexes.reset(a7.selectedIndexes);
        this.__multiple.reset(a7.multiple);
        this.__chipGroupSpace.reset(a7.chipGroupSpace);
        this.__chipGroupPadding.reset(a7.chipGroupPadding);
    }
    purgeVariableDependenciesOnElmtId(z6) {
        this.__items.purgeDependencyOnElmtId(z6);
        this.__itemStyle.purgeDependencyOnElmtId(z6);
        this.__chipSize.purgeDependencyOnElmtId(z6);
        this.__selectedIndexes.purgeDependencyOnElmtId(z6);
        this.__multiple.purgeDependencyOnElmtId(z6);
        this.__chipGroupSpace.purgeDependencyOnElmtId(z6);
        this.__isReachEnd.purgeDependencyOnElmtId(z6);
        this.__chipGroupPadding.purgeDependencyOnElmtId(z6);
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
    set items(y6) {
        this.__items.set(y6);
    }
    get itemStyle() {
        return this.__itemStyle.get();
    }
    set itemStyle(x6) {
        this.__itemStyle.set(x6);
    }
    get chipSize() {
        return this.__chipSize.get();
    }
    set chipSize(w6) {
        this.__chipSize.set(w6);
    }
    get selectedIndexes() {
        return this.__selectedIndexes.get();
    }
    set selectedIndexes(v6) {
        this.__selectedIndexes.set(v6);
    }
    get multiple() {
        return this.__multiple.get();
    }
    set multiple(u6) {
        this.__multiple.set(u6);
    }
    get chipGroupSpace() {
        return this.__chipGroupSpace.get();
    }
    set chipGroupSpace(t6) {
        this.__chipGroupSpace.set(t6);
    }
    get isReachEnd() {
        return this.__isReachEnd.get();
    }
    set isReachEnd(s6) {
        this.__isReachEnd.set(s6);
    }
    get chipGroupPadding() {
        return this.__chipGroupPadding.get();
    }
    set chipGroupPadding(r6) {
        this.__chipGroupPadding.set(r6);
    }
    onMultipleChange() {
        this.selectedIndexes = [0];
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
            let q6 = this.itemStyle.fontColor;
            if (q6 == undefined || q6 == null) {
                return defaultTheme.itemStyle.fontColor;
            }
            if (q6.type === 10001) {
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
            let p6 = this.itemStyle.selectedFontColor;
            if (p6 == undefined || p6 == null) {
                return defaultTheme.itemStyle.selectedFontColor;
            }
            if (p6.type === 10001) {
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
            let o6 = this.itemStyle.backgroundColor;
            if (o6 == undefined || o6 == null) {
                return defaultTheme.itemStyle.backgroundColor;
            }
            if (o6.type === 10001) {
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
            let n6 = this.itemStyle.selectedBackgroundColor;
            if (n6 == undefined || n6 == null) {
                return defaultTheme.itemStyle.selectedBackgroundColor;
            }
            if (n6.type === 10001) {
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
        let i6 = [];
        i6 = (this.selectedIndexes ?? [0]).filter((k6, l6, m6) => {
            return (k6 >= 0 &&
                k6 % 1 == 0 &&
                k6 != null &&
                k6 != undefined &&
                m6.indexOf(k6) === l6 &&
                k6 < (this.items || []).length);
        });
        if (i6.length == 0) {
            i6 = [0];
        }
        return i6;
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
    isSelected(d6) {
        if (!this.isMultiple()) {
            return d6 == this.getSelectedIndexes()[0];
        }
        else {
            return this.getSelectedIndexes().some((f6, g6, h6) => {
                return (f6 == d6);
            });
        }
    }
    getPaddingTop() {
        return parseDimension(this.getUIContext(), this.chipGroupPadding.top, isValidDimensionNoPercentageString, defaultTheme.chipGroupPadding.top);
    }
    getPaddingBottom() {
        return parseDimension(this.getUIContext(), this.chipGroupPadding.bottom, isValidDimensionNoPercentageString, defaultTheme.chipGroupPadding.bottom);
    }
    initialRender() {
        this.observeComponentCreation2((b6, c6) => {
            Row.create();
            Row.align(Alignment.End);
            Row.width("100%");
            Row.padding({ top: this.getPaddingTop(), bottom: this.getPaddingBottom() });
        }, Row);
        this.observeComponentCreation2((z5, a6) => {
            Stack.create();
            Stack.layoutWeight(1);
            Stack.blendMode(BlendMode.SRC_OVER, BlendApplyType.OFFSCREEN);
            Stack.alignContent(Alignment.End);
        }, Stack);
        this.observeComponentCreation2((w5, x5) => {
            Scroll.create(this.scroller);
            Scroll.scrollable(ScrollDirection.Horizontal);
            Scroll.scrollBar(BarState.Off);
            Scroll.align(Alignment.Start);
            Scroll.width('100%');
            Scroll.onScroll(() => {
                this.isReachEnd = this.scroller.isAtEnd();
            });
        }, Scroll);
        this.observeComponentCreation2((u5, v5) => {
            Row.create({ space: this.getChipGroupItemSpace() });
            Row.padding({ left: this.getChipGroupStartSpace(),
                right: this.getChipGroupEndSpace() });
            Row.constraintSize({ minWidth: '100%' });
        }, Row);
        this.observeComponentCreation2((h5, i5) => {
            ForEach.create();
            const j5 = (l5, m5) => {
                const n5 = l5;
                this.observeComponentCreation2((p5, q5) => {
                    If.create();
                    if (n5) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            Chip.bind(this)(makeBuilderParameterProxy("Chip", { prefixIcon: () => ({
                                    src: n5.prefixIcon?.src ?? "",
                                    size: n5.prefixIcon?.size ?? undefined,
                                    fillColor: this.getFillColor(),
                                    activatedFillColor: this.getSelectedFillColor()
                                }), prefixSymbol: () => n5?.prefixSymbol, label: () => ({
                                    text: n5?.label?.text ?? " ",
                                    fontColor: this.getFontColor(),
                                    activatedFontColor: this.getSelectedFontColor(),
                                }), suffixIcon: () => ({
                                    src: n5.suffixIcon?.src ?? "",
                                    size: n5.suffixIcon?.size ?? undefined,
                                    fillColor: this.getFillColor(),
                                    activatedFillColor: this.getSelectedFillColor()
                                }), suffixSymbol: () => n5?.suffixSymbol, allowClose: () => n5.allowClose ?? false, enabled: () => true, activated: () => this.isSelected(m5), backgroundColor: () => this.getBackgroundColor(), size: () => this.getChipSize(), activatedBackgroundColor: () => this.getSelectedBackgroundColor(), onClicked: () => () => {
                                    if (this.isSelected(m5)) {
                                        if (!(!this.isMultiple())) {
                                            if (this.getSelectedIndexes().length > 1) {
                                                this.selectedIndexes.splice(this.selectedIndexes.indexOf(m5), 1);
                                            }
                                        }
                                    }
                                    else {
                                        if (!this.isMultiple()) {
                                            this.selectedIndexes = [];
                                        }
                                        this.selectedIndexes.push(m5);
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
            this.forEachUpdateFunction(h5, this.items || [], j5, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
        Scroll.pop();
        this.observeComponentCreation2((a5, b5) => {
            If.create();
            if (this.suffix && !this.isReachEnd) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((f5, g5) => {
                        Stack.create();
                        Stack.width(iconGroupSuffixTheme.normalBackgroundSize);
                        Stack.height(this.getChipSize() === ChipSize.SMALL ?
                            iconGroupSuffixTheme.smallBackgroundSize :
                            iconGroupSuffixTheme.normalBackgroundSize);
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
        this.observeComponentCreation2((t4, u4) => {
            If.create();
            if (this.suffix) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((y4, z4) => {
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