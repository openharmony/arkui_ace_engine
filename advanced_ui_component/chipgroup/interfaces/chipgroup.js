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
const SymbolGlyphModifier = requireNapi('arkui.modifier').SymbolGlyphModifier;

if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
if (PUV2ViewBase.contextStack === undefined) {
    Reflect.set(PUV2ViewBase, "contextStack", []);
}

const noop = (selectedIndexes) => {
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
    fillColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    defaultEffect: -1
};
var ChipGroupHeight;
(function (ChipGroupHeight) {
    ChipGroupHeight[ChipGroupHeight["NORMAL"] = 36] = "NORMAL";
    ChipGroupHeight[ChipGroupHeight["SMALL"] = 28] = "SMALL";
})(ChipGroupHeight || (ChipGroupHeight = {}));
function parseDimension(uiContext, value, isValid, defaultValue) {
    if (value === void (0) || value === null) {
        return defaultValue;
    }
    const resourceManager = uiContext.getHostContext()?.resourceManager;
    if (typeof value === "object") {
        let temp = value;
        if (temp.type === 10002 || temp.type === 10007) {
            if (resourceManager.getNumber(temp.id) >= 0) {
                return value;
            }
        }
        else if (temp.type === 10003) {
            if (isValidDimensionString(resourceManager.getStringSync(temp.id))) {
                return value;
            }
        }
    }
    else if (typeof value === "number") {
        if (value >= 0) {
            return value;
        }
    }
    else if (typeof value === "string") {
        if (isValid(value)) {
            return value;
        }
    }
    return defaultValue;
}
function isValidString(dimension, regex) {
    const matches = dimension.match(regex);
    if (!matches || matches.length < 3) {
        return false;
    }
    const value = Number.parseFloat(matches[1]);
    return value >= 0;
}
function isValidDimensionString(dimension) {
    return isValidString(dimension, new RegExp("(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$", "i"));
}
function isValidDimensionNoPercentageString(dimension) {
    return isValidString(dimension, new RegExp("(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx)?$", "i"));
}
export class IconGroupSuffix extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.__chipSize = this.initializeConsume("chipSize", "chipSize");
        this.__items = new SynchedPropertyObjectOneWayPU(params.items, this, "items");
        this.symbolEffect = new SymbolEffect();
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(params) {
        if (params.items === undefined) {
            this.__items.set([]);
        }
        if (params.symbolEffect !== undefined) {
            this.symbolEffect = params.symbolEffect;
        }
    }
    updateStateVars(params) {
        this.__items.reset(params.items);
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__chipSize.purgeDependencyOnElmtId(rmElmtId);
        this.__items.purgeDependencyOnElmtId(rmElmtId);
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
    set chipSize(newValue) {
        this.__chipSize.set(newValue);
    }
    get items() {
        return this.__items.get();
    }
    set items(newValue) {
        this.__items.set(newValue);
    }
    getBackgroundSize() {
        if (this.chipSize === ChipSize.SMALL) {
            return iconGroupSuffixTheme.smallBackgroundSize;
        }
        else {
            return iconGroupSuffixTheme.normalBackgroundSize;
        }
    }
    getIconSize(val) {
        if (val === undefined) {
            return this.chipSize === ChipSize.SMALL ?
                iconGroupSuffixTheme.smallIconSize :
                iconGroupSuffixTheme.normalIconSize;
        }
        let value;
        if (this.chipSize === ChipSize.SMALL) {
            value = parseDimension(this.getUIContext(), val, isValidDimensionString, iconGroupSuffixTheme.smallIconSize);
        }
        else {
            value = parseDimension(this.getUIContext(), val, isValidDimensionString, iconGroupSuffixTheme.normalIconSize);
        }
        return value;
    }
    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create({ space: 8 });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            ForEach.create();
            const forEachItemGenFunction = _item => {
                const suffixItem = _item;
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                    Button.createWithChild();
                    Button.size({
                        width: this.getBackgroundSize(),
                        height: this.getBackgroundSize()
                    });
                    Button.backgroundColor(iconGroupSuffixTheme.backgroundColor);
                    Button.borderRadius(iconGroupSuffixTheme.borderRadius);
                    Button.onClick(() => {
                        if (!(suffixItem instanceof SymbolGlyphModifier)) {
                            suffixItem.action();
                        }
                    });
                    Button.borderRadius(iconGroupSuffixTheme.borderRadius);
                }, Button);
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                    If.create();
                    if (suffixItem instanceof SymbolGlyphModifier) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                SymbolGlyph.create();
                                SymbolGlyph.fontColor([iconGroupSuffixTheme.fillColor]);
                                SymbolGlyph.fontSize(this.getIconSize());
                                SymbolGlyph.attributeModifier.bind(this)(suffixItem);
                                SymbolGlyph.focusable(true);
                                SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                SymbolGlyph.symbolEffect(this.symbolEffect, false);
                                SymbolGlyph.symbolEffect(this.symbolEffect, iconGroupSuffixTheme.defaultEffect);
                            }, SymbolGlyph);
                        });
                    }
                    else {
                        this.ifElseBranchUpdateFunction(1, () => {
                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                Image.create(suffixItem.icon.src);
                                Image.fillColor(iconGroupSuffixTheme.fillColor);
                                Image.size({
                                    width: this.getIconSize(suffixItem.icon?.size?.width),
                                    height: this.getIconSize(suffixItem.icon?.size?.height)
                                });
                                Image.focusable(true);
                            }, Image);
                        });
                    }
                }, If);
                If.pop();
                Button.pop();
            };
            this.forEachUpdateFunction(elmtId, this.items || [], forEachItemGenFunction);
        }, ForEach);
        ForEach.pop();
        Row.pop();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
    rerender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.updateDirtyElements();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
}
export class ChipGroup extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.__items = new SynchedPropertyObjectOneWayPU(params.items, this, "items");
        this.__itemStyle = new SynchedPropertyObjectOneWayPU(params.itemStyle, this, "itemStyle");
        this.__chipSize = new ObservedPropertyObjectPU(defaultTheme.itemStyle.size, this, "chipSize");
        this.addProvidedVar("chipSize", this.__chipSize, false);
        this.__selectedIndexes = new SynchedPropertyObjectOneWayPU(params.selectedIndexes, this, "selectedIndexes");
        this.__multiple = new SynchedPropertySimpleOneWayPU(params.multiple, this, "multiple");
        this.__chipGroupSpace = new SynchedPropertyObjectOneWayPU(params.chipGroupSpace, this, "chipGroupSpace");
        this.suffix = undefined;
        this.onChange = noop;
        this.scroller = new Scroller();
        this.__isReachEnd = new ObservedPropertySimplePU(this.scroller.isAtEnd(), this, "isReachEnd");
        this.__chipGroupPadding = new SynchedPropertyObjectOneWayPU(params.chipGroupPadding, this, "chipGroupPadding");
        this.__isRefresh = new ObservedPropertySimplePU(true, this, "isRefresh");
        this.setInitiallyProvidedValue(params);
        this.declareWatch("items", this.onItemsChange);
        this.declareWatch("itemStyle", this.itemStyleOnChange);
        this.declareWatch("multiple", this.onMultipleChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(params) {
        if (params.items === undefined) {
            this.__items.set([]);
        }
        if (params.itemStyle === undefined) {
            this.__itemStyle.set(defaultTheme.itemStyle);
        }
        if (params.chipSize !== undefined) {
            this.chipSize = params.chipSize;
        }
        if (params.selectedIndexes === undefined) {
            this.__selectedIndexes.set([0]);
        }
        if (params.multiple === undefined) {
            this.__multiple.set(false);
        }
        if (params.chipGroupSpace === undefined) {
            this.__chipGroupSpace.set(defaultTheme.chipGroupSpace);
        }
        if (params.suffix !== undefined) {
            this.suffix = params.suffix;
        }
        if (params.onChange !== undefined) {
            this.onChange = params.onChange;
        }
        if (params.scroller !== undefined) {
            this.scroller = params.scroller;
        }
        if (params.isReachEnd !== undefined) {
            this.isReachEnd = params.isReachEnd;
        }
        if (params.chipGroupPadding === undefined) {
            this.__chipGroupPadding.set(defaultTheme.chipGroupPadding);
        }
        if (params.isRefresh !== undefined) {
            this.isRefresh = params.isRefresh;
        }
    }
    updateStateVars(params) {
        this.__items.reset(params.items);
        this.__itemStyle.reset(params.itemStyle);
        this.__selectedIndexes.reset(params.selectedIndexes);
        this.__multiple.reset(params.multiple);
        this.__chipGroupSpace.reset(params.chipGroupSpace);
        this.__chipGroupPadding.reset(params.chipGroupPadding);
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__items.purgeDependencyOnElmtId(rmElmtId);
        this.__itemStyle.purgeDependencyOnElmtId(rmElmtId);
        this.__chipSize.purgeDependencyOnElmtId(rmElmtId);
        this.__selectedIndexes.purgeDependencyOnElmtId(rmElmtId);
        this.__multiple.purgeDependencyOnElmtId(rmElmtId);
        this.__chipGroupSpace.purgeDependencyOnElmtId(rmElmtId);
        this.__isReachEnd.purgeDependencyOnElmtId(rmElmtId);
        this.__chipGroupPadding.purgeDependencyOnElmtId(rmElmtId);
        this.__isRefresh.purgeDependencyOnElmtId(rmElmtId);
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
        this.__isRefresh.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get items() {
        return this.__items.get();
    }
    set items(newValue) {
        this.__items.set(newValue);
    }
    get itemStyle() {
        return this.__itemStyle.get();
    }
    set itemStyle(newValue) {
        this.__itemStyle.set(newValue);
    }
    get chipSize() {
        return this.__chipSize.get();
    }
    set chipSize(newValue) {
        this.__chipSize.set(newValue);
    }
    get selectedIndexes() {
        return this.__selectedIndexes.get();
    }
    set selectedIndexes(newValue) {
        this.__selectedIndexes.set(newValue);
    }
    get multiple() {
        return this.__multiple.get();
    }
    set multiple(newValue) {
        this.__multiple.set(newValue);
    }
    get chipGroupSpace() {
        return this.__chipGroupSpace.get();
    }
    set chipGroupSpace(newValue) {
        this.__chipGroupSpace.set(newValue);
    }
    get isReachEnd() {
        return this.__isReachEnd.get();
    }
    set isReachEnd(newValue) {
        this.__isReachEnd.set(newValue);
    }
    get chipGroupPadding() {
        return this.__chipGroupPadding.get();
    }
    set chipGroupPadding(newValue) {
        this.__chipGroupPadding.set(newValue);
    }
    get isRefresh() {
        return this.__isRefresh.get();
    }
    set isRefresh(newValue) {
        this.__isRefresh.set(newValue);
    }
    onItemsChange() {
        this.isRefresh = !this.isRefresh;
    }
    onMultipleChange() {
        this.selectedIndexes = this.getSelectedIndexes();
    }
    itemStyleOnChange() {
        this.chipSize = this.getChipSize();
    }
    aboutToAppear() {
        this.itemStyleOnChange();
        if (this.getSelectedIndexes().length === 0) {
            this.selectedIndexes = [0];
        }
    }
    getChipSize() {
        if (this.itemStyle && this.itemStyle.size) {
            if (typeof this.itemStyle.size === 'object') {
                if (!this.itemStyle.size.width || !this.itemStyle.size.height || !this.itemStyle.size) {
                    return defaultTheme.itemStyle.size;
                }
            }
            return this.itemStyle.size;
        }
        return defaultTheme.itemStyle.size;
    }
    getFontColor() {
        if (this.itemStyle && this.itemStyle.fontColor) {
            if (typeof this.itemStyle.fontColor === 'object') {
                let temp = this.itemStyle.fontColor;
                if (temp == undefined || temp == null) {
                    return defaultTheme.itemStyle.fontColor;
                }
                if (temp.type === 10001) {
                    return this.itemStyle.fontColor;
                }
                return defaultTheme.itemStyle.fontColor;
            }
            return this.itemStyle.fontColor;
        }
        return defaultTheme.itemStyle.fontColor;
    }
    getSelectedFontColor() {
        if (this.itemStyle && this.itemStyle.selectedFontColor) {
            if (typeof this.itemStyle.selectedFontColor === 'object') {
                let temp = this.itemStyle.selectedFontColor;
                if (temp == undefined || temp == null) {
                    return defaultTheme.itemStyle.selectedFontColor;
                }
                if (temp.type === 10001) {
                    return this.itemStyle.selectedFontColor;
                }
                return defaultTheme.itemStyle.selectedFontColor;
            }
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
            if (typeof this.itemStyle.backgroundColor === 'object') {
                let temp = this.itemStyle.backgroundColor;
                if (temp == undefined || temp == null) {
                    return defaultTheme.itemStyle.backgroundColor;
                }
                if (temp.type === 10001) {
                    return this.itemStyle.backgroundColor;
                }
                return defaultTheme.itemStyle.backgroundColor;
            }
            return this.itemStyle.backgroundColor;
        }
        return defaultTheme.itemStyle.backgroundColor;
    }
    getSelectedBackgroundColor() {
        if (this.itemStyle && this.itemStyle.selectedBackgroundColor) {
            if (typeof this.itemStyle.selectedBackgroundColor === 'object') {
                let temp = this.itemStyle.selectedBackgroundColor;
                if (temp == undefined || temp == null) {
                    return defaultTheme.itemStyle.selectedBackgroundColor;
                }
                if (temp.type === 10001) {
                    return this.itemStyle.selectedBackgroundColor;
                }
                return defaultTheme.itemStyle.selectedBackgroundColor;
            }
            return this.itemStyle.selectedBackgroundColor;
        }
        return defaultTheme.itemStyle.selectedBackgroundColor;
    }
    getSelectedIndexes() {
        let temp = [];
        temp = (this.selectedIndexes ?? [0]).filter((element, index, array) => {
            return (element >= 0 &&
                element % 1 == 0 &&
                element != null &&
                element != undefined &&
                array.indexOf(element) === index &&
                element < (this.items || []).length);
        });
        return temp;
    }
    isMultiple() {
        return this.multiple ?? false;
    }
    getChipGroupItemSpace() {
        if (this.chipGroupSpace == undefined) {
            return defaultTheme.chipGroupSpace.itemSpace;
        }
        return parseDimension(this.getUIContext(), this.chipGroupSpace.itemSpace, isValidDimensionNoPercentageString, defaultTheme.chipGroupSpace.itemSpace);
    }
    getChipGroupStartSpace() {
        if (this.chipGroupSpace == undefined) {
            return defaultTheme.chipGroupSpace.startSpace;
        }
        return parseDimension(this.getUIContext(), this.chipGroupSpace.startSpace, isValidDimensionNoPercentageString, defaultTheme.chipGroupSpace.startSpace);
    }
    getChipGroupEndSpace() {
        if (this.chipGroupSpace == undefined) {
            return defaultTheme.chipGroupSpace.endSpace;
        }
        return parseDimension(this.getUIContext(), this.chipGroupSpace.endSpace, isValidDimensionNoPercentageString, defaultTheme.chipGroupSpace.endSpace);
    }
    getOnChange() {
        return this.onChange ?? noop;
    }
    isSelected(itemIndex) {
        if (!this.isMultiple()) {
            return itemIndex == this.getSelectedIndexes()[0];
        }
        else {
            return this.getSelectedIndexes().some((element, index, array) => {
                return (element == itemIndex);
            });
        }
    }
    getPaddingTop() {
        if (!this.chipGroupPadding || !this.chipGroupPadding.top) {
            return defaultTheme.chipGroupPadding.top;
        }
        return parseDimension(this.getUIContext(), this.chipGroupPadding.top, isValidDimensionNoPercentageString, defaultTheme.chipGroupPadding.top);
    }
    getPaddingBottom() {
        if (!this.chipGroupPadding || !this.chipGroupPadding.bottom) {
            return defaultTheme.chipGroupPadding.bottom;
        }
        return parseDimension(this.getUIContext(), this.chipGroupPadding.bottom, isValidDimensionNoPercentageString, defaultTheme.chipGroupPadding.bottom);
    }
    getChipGroupHeight() {
        if (typeof this.chipSize === 'string') {
            if (this.chipSize === ChipSize.NORMAL) {
                return ChipGroupHeight.NORMAL;
            }
            else {
                return ChipGroupHeight.SMALL;
            }
        }
        else if (typeof this.chipSize === 'object') {
            return this.chipSize.height;
        }
        else {
            return ChipGroupHeight.NORMAL;
        }
    }
    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.align(Alignment.End);
            Row.width("100%");
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.padding({ top: this.getPaddingTop(), bottom: this.getPaddingBottom() });
            Stack.layoutWeight(1);
            Stack.blendMode(BlendMode.SRC_OVER, BlendApplyType.OFFSCREEN);
            Stack.alignContent(Alignment.End);
        }, Stack);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Scroll.create(this.scroller);
            Scroll.scrollable(ScrollDirection.Horizontal);
            Scroll.scrollBar(BarState.Off);
            Scroll.align(Alignment.Start);
            Scroll.width('100%');
            Scroll.clip(false);
            Scroll.onScroll(() => {
                this.isReachEnd = this.scroller.isAtEnd();
            });
        }, Scroll);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create({ space: this.getChipGroupItemSpace() });
            Row.padding({ left: this.getChipGroupStartSpace(),
                right: this.getChipGroupEndSpace()
            });
            Row.constraintSize({ minWidth: '100%' });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            ForEach.create();
            const forEachItemGenFunction = (_item, index) => {
                const chipItem = _item;
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                    If.create();
                    if (chipItem) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            Chip.bind(this)(makeBuilderParameterProxy("Chip", { prefixIcon: () => ({
                                    src: chipItem.prefixIcon?.src ?? "",
                                    size: chipItem.prefixIcon?.size ?? undefined,
                                    fillColor: this.getFillColor(),
                                    activatedFillColor: this.getSelectedFillColor()
                                }), prefixSymbol: () => chipItem?.prefixSymbol, label: () => ({
                                    text: chipItem?.label?.text ?? " ",
                                    fontColor: this.getFontColor(),
                                    activatedFontColor: this.getSelectedFontColor(),
                                }), suffixIcon: () => ({
                                    src: chipItem.suffixIcon?.src ?? "",
                                    size: chipItem.suffixIcon?.size ?? undefined,
                                    fillColor: this.getFillColor(),
                                    activatedFillColor: this.getSelectedFillColor()
                                }), suffixSymbol: () => chipItem?.suffixSymbol, allowClose: () => chipItem.allowClose ?? false, enabled: () => true, activated: () => this.isSelected(index), backgroundColor: () => this.getBackgroundColor(), size: () => this.getChipSize(), activatedBackgroundColor: () => this.getSelectedBackgroundColor(), onClicked: () => () => {
                                    if (this.isSelected(index)) {
                                        if (!(!this.isMultiple())) {
                                            if (this.getSelectedIndexes().length > 1) {
                                                this.selectedIndexes.splice(this.selectedIndexes.indexOf(index), 1);
                                            }
                                        }
                                    }
                                    else {
                                        if (!this.selectedIndexes || this.selectedIndexes.length === 0) {
                                            this.selectedIndexes = this.getSelectedIndexes();
                                        }
                                        if (!this.isMultiple()) {
                                            this.selectedIndexes = [];
                                        }
                                        this.selectedIndexes.push(index);
                                    }
                                    this.getOnChange()(this.getSelectedIndexes());
                                } }));
                        });
                    }
                    else {
                        this.ifElseBranchUpdateFunction(1, () => {
                        });
                    }
                }, If);
                If.pop();
            };
            this.forEachUpdateFunction(elmtId, this.items || [], forEachItemGenFunction, () => {
                return JSON.stringify(this.isRefresh);
            }, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
        Scroll.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.suffix && !this.isReachEnd) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Stack.create();
                        Stack.width(iconGroupSuffixTheme.normalBackgroundSize);
                        Stack.height(this.getChipGroupHeight());
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.suffix) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.padding({ left: iconGroupSuffixTheme.marginLeft,
                            right: iconGroupSuffixTheme.marginRight
                        });
                    }, Row);
                    this.suffix.bind(this)();
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
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
    rerender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.updateDirtyElements();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
}

export default {
    ChipGroup,
    IconGroupSuffix
}
