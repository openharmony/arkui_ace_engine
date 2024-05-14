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

const noop = (f9) => {
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
function parseDimension(z8, a9, b9, c9) {
    if (a9 === void (0) || a9 === null) {
        return c9;
    }
    const d9 = z8.getHostContext()?.resourceManager;
    if (typeof a9 === "object") {
        let e9 = a9;
        if (e9.type === 10002 || e9.type === 10007) {
            if (d9.getNumber(e9.id) >= 0) {
                return a9;
            }
        }
        else if (e9.type === 10003) {
            if (isValidDimensionString(d9.getStringSync(e9.id))) {
                return a9;
            }
        }
    }
    else if (typeof a9 === "number") {
        if (a9 >= 0) {
            return a9;
        }
    }
    else if (typeof a9 === "string") {
        if (b9(a9)) {
            return a9;
        }
    }
    return c9;
}
function isValidString(v8, w8) {
    const x8 = v8.match(w8);
    if (!x8 || x8.length < 3) {
        return false;
    }
    const y8 = Number.parseFloat(x8[1]);
    return y8 >= 0;
}
function isValidDimensionString(u8) {
    return isValidString(u8, new RegExp("(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$", "i"));
}
function isValidDimensionNoPercentageString(t8) {
    return isValidString(t8, new RegExp("(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx)?$", "i"));
}
export class IconGroupSuffix extends ViewPU {
    constructor(n8, o8, p8, q8 = -1, r8 = undefined, s8) {
        super(n8, p8, q8, s8);
        if (typeof r8 === "function") {
            this.paramsGenerator_ = r8;
        }
        this.__chipSize = this.initializeConsume("chipSize", "chipSize");
        this.__items = new SynchedPropertyObjectOneWayPU(o8.items, this, "items");
        this.setInitiallyProvidedValue(o8);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(m8) {
        if (m8.items === undefined) {
            this.__items.set([]);
        }
    }
    updateStateVars(l8) {
        this.__items.reset(l8.items);
    }
    purgeVariableDependenciesOnElmtId(k8) {
        this.__chipSize.purgeDependencyOnElmtId(k8);
        this.__items.purgeDependencyOnElmtId(k8);
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
    set chipSize(j8) {
        this.__chipSize.set(j8);
    }
    get items() {
        return this.__items.get();
    }
    set items(i8) {
        this.__items.set(i8);
    }
    getBackgroundSize() {
        if (this.chipSize === ChipSize.SMALL) {
            return iconGroupSuffixTheme.smallBackgroundSize;
        }
        else {
            return iconGroupSuffixTheme.normalBackgroundSize;
        }
    }
    getIconSize(g8) {
        if (g8 === undefined) {
            return this.chipSize === ChipSize.SMALL ? iconGroupSuffixTheme.smallIconSize : iconGroupSuffixTheme.normalIconSize;
        }
        let h8;
        if (this.chipSize === ChipSize.SMALL) {
            h8 = parseDimension(this.getUIContext(), g8, isValidDimensionString, iconGroupSuffixTheme.smallIconSize);
        }
        else {
            h8 = parseDimension(this.getUIContext(), g8, isValidDimensionString, iconGroupSuffixTheme.normalIconSize);
        }
        return h8;
    }
    initialRender() {
        this.observeComponentCreation2((e8, f8) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((j7, k7) => {
            ForEach.create();
            const l7 = n7 => {
                const o7 = n7;
                this.observeComponentCreation2((b8, c8) => {
                    Button.createWithChild();
                    Button.size({
                        width: this.getBackgroundSize(),
                        height: this.getBackgroundSize()
                    });
                    Button.backgroundColor(iconGroupSuffixTheme.backgroundColor);
                    Button.borderRadius(iconGroupSuffixTheme.borderRadius);
                    Button.onClick(() => {
                        if (!(o7 instanceof SymbolGlyphModifier)) {
                            o7.action();
                        }
                    });
                    Button.borderRadius(iconGroupSuffixTheme.borderRadius);
                }, Button);
                this.observeComponentCreation2((r7, s7) => {
                    If.create();
                    if (o7 instanceof SymbolGlyphModifier) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((z7, a8) => {
                                SymbolGlyph.create();
                                SymbolGlyph.fontColor([iconGroupSuffixTheme.fillColor]);
                                SymbolGlyph.fontSize(this.getIconSize());
                                SymbolGlyph.attributeModifier.bind(this)(o7);
                                SymbolGlyph.focusable(true);
                            }, SymbolGlyph);
                        });
                    }
                    else {
                        this.ifElseBranchUpdateFunction(1, () => {
                            this.observeComponentCreation2((v7, w7) => {
                                Image.create(o7.icon.src);
                                Image.fillColor(iconGroupSuffixTheme.fillColor);
                                Image.size({
                                    width: this.getIconSize(o7.icon?.size?.width),
                                    height: this.getIconSize(o7.icon?.size?.height)
                                });
                                Image.focusable(true);
                            }, Image);
                        });
                    }
                }, If);
                If.pop();
                Button.pop();
            };
            this.forEachUpdateFunction(j7, this.items || [], l7);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
export class ChipGroup extends ViewPU {
    constructor(b7, c7, d7, e7 = -1, f7 = undefined, g7) {
        super(b7, d7, e7, g7);
        if (typeof f7 === "function") {
            this.paramsGenerator_ = f7;
        }
        this.__items = new SynchedPropertyObjectOneWayPU(c7.items, this, "items");
        this.__itemStyle = new SynchedPropertyObjectOneWayPU(c7.itemStyle, this, "itemStyle");
        this.__chipSize = new ObservedPropertyObjectPU(defaultTheme.itemStyle.size, this, "chipSize");
        this.addProvidedVar("chipSize", this.__chipSize, false);
        this.__selectedIndexes = new SynchedPropertyObjectOneWayPU(c7.selectedIndexes, this, "selectedIndexes");
        this.__multiple = new SynchedPropertySimpleOneWayPU(c7.multiple, this, "multiple");
        this.__chipGroupSpace = new SynchedPropertyObjectOneWayPU(c7.chipGroupSpace, this, "chipGroupSpace");
        this.suffix = undefined;
        this.onChange = noop;
        this.scroller = new Scroller();
        this.__isReachEnd = new ObservedPropertySimplePU(this.scroller.isAtEnd(), this, "isReachEnd");
        this.setInitiallyProvidedValue(c7);
        this.declareWatch("itemStyle", this.itemStyleOnChange);
        this.declareWatch("multiple", this.onMultipleChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(a7) {
        if (a7.items === undefined) {
            this.__items.set([]);
        }
        if (a7.itemStyle === undefined) {
            this.__itemStyle.set(defaultTheme.itemStyle);
        }
        if (a7.chipSize !== undefined) {
            this.chipSize = a7.chipSize;
        }
        if (a7.selectedIndexes === undefined) {
            this.__selectedIndexes.set([0]);
        }
        if (a7.multiple === undefined) {
            this.__multiple.set(false);
        }
        if (a7.chipGroupSpace === undefined) {
            this.__chipGroupSpace.set(defaultTheme.chipGroupSpace);
        }
        if (a7.suffix !== undefined) {
            this.suffix = a7.suffix;
        }
        if (a7.onChange !== undefined) {
            this.onChange = a7.onChange;
        }
        if (a7.scroller !== undefined) {
            this.scroller = a7.scroller;
        }
        if (a7.isReachEnd !== undefined) {
            this.isReachEnd = a7.isReachEnd;
        }
    }
    updateStateVars(z6) {
        this.__items.reset(z6.items);
        this.__itemStyle.reset(z6.itemStyle);
        this.__selectedIndexes.reset(z6.selectedIndexes);
        this.__multiple.reset(z6.multiple);
        this.__chipGroupSpace.reset(z6.chipGroupSpace);
    }
    purgeVariableDependenciesOnElmtId(y6) {
        this.__items.purgeDependencyOnElmtId(y6);
        this.__itemStyle.purgeDependencyOnElmtId(y6);
        this.__chipSize.purgeDependencyOnElmtId(y6);
        this.__selectedIndexes.purgeDependencyOnElmtId(y6);
        this.__multiple.purgeDependencyOnElmtId(y6);
        this.__chipGroupSpace.purgeDependencyOnElmtId(y6);
        this.__isReachEnd.purgeDependencyOnElmtId(y6);
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
    set items(x6) {
        this.__items.set(x6);
    }
    get itemStyle() {
        return this.__itemStyle.get();
    }
    set itemStyle(w6) {
        this.__itemStyle.set(w6);
    }
    get chipSize() {
        return this.__chipSize.get();
    }
    set chipSize(v6) {
        this.__chipSize.set(v6);
    }
    get selectedIndexes() {
        return this.__selectedIndexes.get();
    }
    set selectedIndexes(u6) {
        this.__selectedIndexes.set(u6);
    }
    get multiple() {
        return this.__multiple.get();
    }
    set multiple(t6) {
        this.__multiple.set(t6);
    }
    get chipGroupSpace() {
        return this.__chipGroupSpace.get();
    }
    set chipGroupSpace(s6) {
        this.__chipGroupSpace.set(s6);
    }
    get isReachEnd() {
        return this.__isReachEnd.get();
    }
    set isReachEnd(r6) {
        this.__isReachEnd.set(r6);
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
    initialRender() {
        this.observeComponentCreation2((b6, c6) => {
            Row.create();
            Row.align(Alignment.End);
            Row.width("100%");
            Row.height(64);
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