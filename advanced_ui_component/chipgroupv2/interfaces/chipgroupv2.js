/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        r = Reflect.decorate(decorators, target, key, desc);
    else
        for (var i = decorators.length - 1; i >= 0; i--)
            if (d = decorators[i])
                r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
const SymbolGlyphModifier = requireNapi('arkui.modifier').SymbolGlyphModifier;
const ChipV2Size = requireNapi('arkui.advanced.ChipV2').ChipV2Size;
const ChipV2SuffixImageIcon = requireNapi('arkui.advanced.ChipV2').ChipV2SuffixImageIcon;
const ChipV2PrefixImageIcon = requireNapi('arkui.advanced.ChipV2').ChipV2PrefixImageIcon;
const ChipV2Label = requireNapi('arkui.advanced.ChipV2').ChipV2Label;
const ChipV2CloseIcon = requireNapi('arkui.advanced.ChipV2').ChipV2CloseIcon;
const ChipV2PrefixSymbolIcon = requireNapi('arkui.advanced.ChipV2').ChipV2PrefixSymbolIcon;
const ChipV2SuffixSymbolIcon = requireNapi('arkui.advanced.ChipV2').ChipV2SuffixSymbolIcon;
const ChipV2 = requireNapi('arkui.advanced.ChipV2').ChipV2;
const ChipV2Options = requireNapi('arkui.advanced.ChipV2').ChipV2Options;
const ChipV2AccessibilitySelectedType = requireNapi('arkui.advanced.ChipV2').ChipV2AccessibilitySelectedType;
const uiMaterial = requireNapi('arkui.uiMaterial');
const LengthUnit = requireNapi('arkui.node').LengthUnit;
const ColorMetrics = requireNapi('arkui.node').ColorMetrics;
const deviceInfo = requireNapi('deviceInfo')
const noop = (selectedIndexes) => {
};
const colorStops = [['rgba(0, 0, 0, 1)', 0], ['rgba(0, 0, 0, 0)', 1]];
const defaultTheme = {
    size: ChipV2Size.NORMAL,
    backgroundColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_button_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    fontColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    selectedFontColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary_contrary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    selectedBackgroundColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_emphasize'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    chipGroupSpace: { itemSpace: 8, startSpace: 16, endSpace: 16 },
    chipGroupPadding: { top: 14, bottom: 14 },
    itemFillColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    itemSelectedFillColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary_contrary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
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
let ChipGroupV2Item = class ChipGroupV2Item {
    constructor(config) {
        this.prefixIcon = config.prefixIcon ? new ChipV2PrefixImageIcon(config.prefixIcon) : undefined;
        this.prefixSymbolIcon = config.prefixSymbolIcon ? new ChipV2PrefixSymbolIcon(config.prefixSymbolIcon) : undefined;
        this.label = new ChipV2Label(config.label);
        this.suffixIcon = config.suffixIcon ? new ChipV2SuffixImageIcon(config.suffixIcon) : undefined;
        this.suffixSymbolIcon = config.suffixSymbolIcon ? new ChipV2SuffixSymbolIcon(config.suffixSymbolIcon) : undefined;
        this.allowClose = config.allowClose;
        this.closeIcon = config.closeIcon;
        this.accessibilityDescription = config.accessibilityDescription;
        this.accessibilityLevel = config.accessibilityLevel;
    }
};
__decorate([
    Trace
], ChipGroupV2Item.prototype, "prefixIcon", void 0);
__decorate([
    Trace
], ChipGroupV2Item.prototype, "prefixSymbolIcon", void 0);
__decorate([
    Trace
], ChipGroupV2Item.prototype, "label", void 0);
__decorate([
    Trace
], ChipGroupV2Item.prototype, "suffixIcon", void 0);
__decorate([
    Trace
], ChipGroupV2Item.prototype, "suffixSymbolIcon", void 0);
__decorate([
    Trace
], ChipGroupV2Item.prototype, "allowClose", void 0);
__decorate([
    Trace
], ChipGroupV2Item.prototype, "closeIcon", void 0);
__decorate([
    Trace
], ChipGroupV2Item.prototype, "accessibilityDescription", void 0);
__decorate([
    Trace
], ChipGroupV2Item.prototype, "accessibilityLevel", void 0);
ChipGroupV2Item = __decorate([
    ObservedV2
], ChipGroupV2Item);
export { ChipGroupV2Item };
let ChipGroupV2Items = class ChipGroupV2Items extends Array {
    constructor(items) {
        super();
        items.forEach(item => this.push(new ChipGroupV2Item(item)));
    }
};
ChipGroupV2Items = __decorate([
    ObservedV2
], ChipGroupV2Items);
export { ChipGroupV2Items };
let ChipGroupV2ItemStyle = class ChipGroupV2ItemStyle {
    constructor(config) {
        this.size = config.size;
        this.backgroundColor = config.backgroundColor;
        this.fontColor = config.fontColor;
        this.selectedFontColor = config.selectedFontColor;
        this.selectedBackgroundColor = config.selectedBackgroundColor;
        this.backgroundSystemMaterial = config.backgroundSystemMaterial;
        this.selectedBackgroundSystemMaterial = config.selectedBackgroundSystemMaterial;
    }
};
__decorate([
    Trace
], ChipGroupV2ItemStyle.prototype, "size", void 0);
__decorate([
    Trace
], ChipGroupV2ItemStyle.prototype, "backgroundColor", void 0);
__decorate([
    Trace
], ChipGroupV2ItemStyle.prototype, "fontColor", void 0);
__decorate([
    Trace
], ChipGroupV2ItemStyle.prototype, "selectedFontColor", void 0);
__decorate([
    Trace
], ChipGroupV2ItemStyle.prototype, "selectedBackgroundColor", void 0);
__decorate([
    Trace
], ChipGroupV2ItemStyle.prototype, "backgroundSystemMaterial", void 0);
__decorate([
    Trace
], ChipGroupV2ItemStyle.prototype, "selectedBackgroundSystemMaterial", void 0);
ChipGroupV2ItemStyle = __decorate([
    ObservedV2
], ChipGroupV2ItemStyle);
export { ChipGroupV2ItemStyle };
let ChipGroupV2Space = class ChipGroupV2Space {
    constructor(config) {
        this.itemSpace = config.itemSpace;
        this.startSpace = config.startSpace;
        this.endSpace = config.endSpace;
    }
};
__decorate([
    Trace
], ChipGroupV2Space.prototype, "itemSpace", void 0);
__decorate([
    Trace
], ChipGroupV2Space.prototype, "startSpace", void 0);
__decorate([
    Trace
], ChipGroupV2Space.prototype, "endSpace", void 0);
ChipGroupV2Space = __decorate([
    ObservedV2
], ChipGroupV2Space);
export { ChipGroupV2Space };
let ChipGroupV2Padding = class ChipGroupV2Padding {
    constructor(config) {
        this.top = config.top;
        this.bottom = config.bottom;
    }
};
__decorate([
    Trace
], ChipGroupV2Padding.prototype, "top", void 0);
__decorate([
    Trace
], ChipGroupV2Padding.prototype, "bottom", void 0);
ChipGroupV2Padding = __decorate([
    ObservedV2
], ChipGroupV2Padding);
export { ChipGroupV2Padding };
export class ChipGroupV2IconGroupSuffix extends ViewV2 {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
        super(parent, elmtId, extraInfo);
        this.initParam("items", (params && "items" in params) ? params.items : []);
        this.initParam("iconBackgroundSystemMaterial", (params && "iconBackgroundSystemMaterial" in params) ? params.iconBackgroundSystemMaterial : undefined);
        this.chipSize = ChipV2Size.NORMAL;
        this.symbolEffect = new SymbolEffect();
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(params) {
        this.resetParam("items", (params && "items" in params) ? params.items : []);
        this.resetParam("iconBackgroundSystemMaterial", (params && "iconBackgroundSystemMaterial" in params) ? params.iconBackgroundSystemMaterial : undefined);
        this.resetConsumer("chipSize", ChipV2Size.NORMAL);
        this.symbolEffect = new SymbolEffect();
    }
    getBackgroundSize() {
        if (this.chipSize === ChipV2Size.SMALL) {
            return iconGroupSuffixTheme.smallBackgroundSize;
        }
        else {
            return iconGroupSuffixTheme.normalBackgroundSize;
        }
    }
    getIconSize(val) {
        if (val === undefined) {
            return this.chipSize === ChipV2Size.SMALL ?
                iconGroupSuffixTheme.smallIconSize :
                iconGroupSuffixTheme.normalIconSize;
        }
        let value;
        if (this.chipSize === ChipV2Size.SMALL) {
            value = parseDimension(this.getUIContext(), lengthMetricsToLength(val), isValidDimensionString, iconGroupSuffixTheme.smallIconSize);
        }
        else {
            value = parseDimension(this.getUIContext(), lengthMetricsToLength(val), isValidDimensionString, iconGroupSuffixTheme.normalIconSize);
        }
        return value;
    }
    SymbolItemBuilder(item, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            SymbolGlyph.create();
            SymbolGlyph.fontColor([iconGroupSuffixTheme.fillColor]);
            SymbolGlyph.fontSize(this.getIconSize());
            SymbolGlyph.attributeModifier.bind(this)(item.symbol);
            SymbolGlyph.focusable(true);
            SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
            SymbolGlyph.symbolEffect(this.symbolEffect, false);
            SymbolGlyph.symbolEffect(this.symbolEffect, iconGroupSuffixTheme.defaultEffect);
        }, SymbolGlyph);
    }
    IconItemBuilder(item, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(item.icon.src);
            Image.fillColor(iconGroupSuffixTheme.fillColor);
            Image.size({
                width: this.getIconSize(item.icon.size?.width),
                height: this.getIconSize(item.icon.size?.height)
            });
            Image.focusable(true);
        }, Image);
    }
    IconButtonsBuilder(material, parent = null) {
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
                    Button.systemMaterial(material);
                    Button.accessibilityText(this.getAccessibilityText(suffixItem));
                    Button.accessibilityDescription(this.getAccessibilityDescription(suffixItem));
                    Button.accessibilityLevel(this.getAccessibilityLevel(suffixItem));
                    Button.onClick(() => {
                        if (!(suffixItem instanceof SymbolGlyphModifier)) {
                            suffixItem.action();
                        }
                    });
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
                    else if (this.isSymbolItem(suffixItem)) {
                        this.ifElseBranchUpdateFunction(1, () => {
                            this.SymbolItemBuilder.bind(this)(suffixItem);
                        });
                    }
                    else {
                        this.ifElseBranchUpdateFunction(2, () => {
                            this.IconItemBuilder.bind(this)(suffixItem);
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
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (deviceInfo.sdkApiVersion >= 26) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (enableEffectComponent(this.iconBackgroundSystemMaterial)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    EffectComponent.create();
                                    EffectComponent.systemMaterial(createECMaterial(this.iconBackgroundSystemMaterial));
                                }, EffectComponent);
                                this.IconButtonsBuilder.bind(this)(createSubECMaterial(this.iconBackgroundSystemMaterial));
                                EffectComponent.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.IconButtonsBuilder.bind(this)(this.iconBackgroundSystemMaterial);
                            });
                        }
                    }, If);
                    If.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.IconButtonsBuilder.bind(this)(undefined);
                });
            }
        }, If);
        If.pop();
    }
    isSymbolItem(item) {
        return typeof item.symbol !== 'undefined';
    }
    getAccessibilityLevel(item) {
        if (item instanceof SymbolGlyphModifier) {
            return 'auto';
        }
        return item.accessibilityLevel ?? 'auto';
    }
    getAccessibilityDescription(item) {
        if (item instanceof SymbolGlyphModifier || typeof item.accessibilityDescription === 'undefined') {
            return undefined;
        }
        return item.accessibilityDescription;
    }
    getAccessibilityText(item) {
        if (item instanceof SymbolGlyphModifier || typeof item.accessibilityText === 'undefined') {
            return undefined;
        }
        return item.accessibilityText;
    }
    updateStateVars(params) {
        if (params === undefined) {
            return;
        }
        if ("items" in params) {
            this.updateParam("items", params.items);
        }
        if ("iconBackgroundSystemMaterial" in params) {
            this.updateParam("iconBackgroundSystemMaterial", params.iconBackgroundSystemMaterial);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
], ChipGroupV2IconGroupSuffix.prototype, "items", void 0);
__decorate([
    Param
], ChipGroupV2IconGroupSuffix.prototype, "iconBackgroundSystemMaterial", void 0);
__decorate([
    Consumer()
], ChipGroupV2IconGroupSuffix.prototype, "chipSize", void 0);
__decorate([
    Local
], ChipGroupV2IconGroupSuffix.prototype, "symbolEffect", void 0);
export class ChipGroupV2 extends ViewV2 {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
        super(parent, elmtId, extraInfo);
        this.initParam("items", (params && "items" in params) ? params.items : undefined);
        this.$items = "$items" in params ? params.$items : undefined;
        this.initParam("itemStyle", (params && "itemStyle" in params) ? params.itemStyle : undefined);
        this.initParam("selectedIndexes", (params && "selectedIndexes" in params) ? params.selectedIndexes : undefined);
        this.$selectedIndexes = "$selectedIndexes" in params ? params.$selectedIndexes : undefined;
        this.initParam("multiple", (params && "multiple" in params) ? params.multiple : false);
        this.initParam("chipGroupSpace", (params && "chipGroupSpace" in params) ? params.chipGroupSpace : defaultTheme.chipGroupSpace);
        this.initParam("chipGroupPadding", (params && "chipGroupPadding" in params) ? params.chipGroupPadding : defaultTheme.chipGroupPadding);
        this.onChange = "onChange" in params ? params.onChange : () => { };
        this.suffix = "suffix" in params ? params.suffix : undefined;
        this.chipSize = defaultTheme.size;
        this.scroller = new Scroller();
        this.selectedIndexesInternal = [0];
        this.isReachEnd = this.scroller.isAtEnd();
        this.isRefresh = true;
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(params) {
        this.resetParam("items", (params && "items" in params) ? params.items : undefined);
        this.$items = "$items" in params ? params.$items : undefined;
        this.resetParam("itemStyle", (params && "itemStyle" in params) ? params.itemStyle : undefined);
        this.resetParam("selectedIndexes", (params && "selectedIndexes" in params) ? params.selectedIndexes : undefined);
        this.$selectedIndexes = "$selectedIndexes" in params ? params.$selectedIndexes : undefined;
        this.resetParam("multiple", (params && "multiple" in params) ? params.multiple : false);
        this.resetParam("chipGroupSpace", (params && "chipGroupSpace" in params) ? params.chipGroupSpace : defaultTheme.chipGroupSpace);
        this.resetParam("chipGroupPadding", (params && "chipGroupPadding" in params) ? params.chipGroupPadding : defaultTheme.chipGroupPadding);
        this.onChange = "onChange" in params ? params.onChange : () => { };
        this.suffix = "suffix" in params ? params.suffix : undefined;
        this.chipSize = defaultTheme.size;
        this.selectedIndexesInternal = [0];
        this.isReachEnd = this.scroller.isAtEnd();
        this.isRefresh = true;
        this.resetMonitorsOnReuse();
    }
    onItemsChange() {
        this.isRefresh = !this.isRefresh;
    }
    onMultipleChange() {
        if (this.selectedIndexes) {
            this.selectedIndexesOnChange();
        }
        this.selectedIndexesInternal = this.getSelectedIndexes();
    }
    itemStyleOnChange() {
        this.chipSize = this.getChipSize();
    }
    selectedIndexesOnChange() {
        this.selectedIndexesInternal = this.selectedIndexes?.filter(() => true);
    }
    aboutToAppear() {
        this.itemStyleOnChange();
        this.selectedIndexesOnChange();
        if (this.getSelectedIndexes().length === 0) {
            this.selectedIndexesInternal = [0];
        }
    }
    getChipSize() {
        if (this.itemStyle && this.itemStyle.size) {
            if (typeof this.itemStyle.size === 'object') {
                if (!this.itemStyle.size.width?.value || !this.itemStyle.size.height?.value || !this.itemStyle.size) {
                    return defaultTheme.size;
                }
            }
            return this.itemStyle.size;
        }
        return defaultTheme.size;
    }
    getFontColor() {
        if (this.itemStyle && this.itemStyle.fontColor) {
            return this.itemStyle.fontColor;
        }
        return ColorMetrics.resourceColor(defaultTheme.fontColor);
    }
    getSelectedFontColor() {
        if (this.itemStyle && this.itemStyle.selectedFontColor) {
            return this.itemStyle.selectedFontColor;
        }
        return ColorMetrics.resourceColor(defaultTheme.selectedFontColor);
    }
    getFillColor() {
        if (this.itemStyle && this.itemStyle.fontColor) {
            return this.itemStyle.fontColor;
        }
        return ColorMetrics.resourceColor(defaultTheme.itemFillColor);
    }
    getSelectedFillColor() {
        if (this.itemStyle && this.itemStyle.selectedFontColor) {
            return this.itemStyle.selectedFontColor;
        }
        return ColorMetrics.resourceColor(defaultTheme.itemSelectedFillColor);
    }
    getBackgroundColor() {
        if (this.itemStyle?.backgroundColor) {
            return this.itemStyle.backgroundColor;
        }
        return ColorMetrics.resourceColor(defaultTheme.backgroundColor);
    }
    getSelectedBackgroundColor() {
        if (this.itemStyle?.selectedBackgroundColor) {
            return this.itemStyle.selectedBackgroundColor;
        }
        return ColorMetrics.resourceColor(defaultTheme.selectedBackgroundColor);
    }
    getSelectedIndexes() {
        let temp = [];
        temp = (this.selectedIndexesInternal ?? [0]).filter((element, index, array) => {
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
            if (this.chipSize === ChipV2Size.NORMAL) {
                return ChipGroupHeight.NORMAL;
            }
            else {
                return ChipGroupHeight.SMALL;
            }
        }
        else if (typeof this.chipSize === 'object') {
            return lengthMetricsToLength(this.chipSize.height);
        }
        else {
            return ChipGroupHeight.NORMAL;
        }
    }
    ChipItemsBuilder(material, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create({ space: this.getChipGroupItemSpace() });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            ForEach.create();
            const forEachItemGenFunction = (_item, index) => {
                const chipItem = _item;
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                    If.create();
                    if (chipItem) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    if (isInitialRender) {
                                        let componentCall = new ChipV2(this, { chipV2Options: new ChipV2Options({
                                                label: this.getLabel(chipItem.label),
                                                prefixIcon: this.getPrefixIcon(chipItem),
                                                suffixIcon: this.getSuffixIcon(chipItem),
                                                allowClose: chipItem.allowClose ?? false,
                                                closeIcon: chipItem.closeIcon ? new ChipV2CloseIcon(chipItem.closeIcon) : undefined,
                                                enabled: true,
                                                activated: this.isSelected(index),
                                                backgroundColor: this.getBackgroundColor(),
                                                size: this.getChipSize(),
                                                activatedBackgroundColor: this.getSelectedBackgroundColor(),
                                                accessibilitySelectedType: this.multiple ? ChipV2AccessibilitySelectedType.CHECKED : ChipV2AccessibilitySelectedType.SELECTED,
                                                accessibilityDescription: chipItem.accessibilityDescription,
                                                accessibilityLevel: chipItem.accessibilityLevel,
                                                backgroundSystemMaterial: createSubECMaterial(material),
                                                activatedBackgroundSystemMaterial: resolveSystemMaterial(this.itemStyle?.selectedBackgroundSystemMaterial),
                                                onClicked: () => {
                                                    if (this.isSelected(index)) {
                                                        if (!(!this.isMultiple())) {
                                                            if (this.getSelectedIndexes().length > 1) {
                                                                this.selectedIndexesInternal.splice(this.selectedIndexesInternal.indexOf(index), 1);
                                                            }
                                                        }
                                                    }
                                                    else {
                                                        if (!this.selectedIndexesInternal || this.selectedIndexesInternal.length === 0) {
                                                            this.selectedIndexesInternal = this.getSelectedIndexes();
                                                        }
                                                        if (!this.isMultiple()) {
                                                            this.selectedIndexesInternal = [];
                                                        }
                                                        this.selectedIndexesInternal.push(index);
                                                    }
                                                    this.getOnChange()(this.getSelectedIndexes());
                                                    this.$selectedIndexes?.(this.selectedIndexesInternal);
                                                },
                                                onClose: () => {
                                                    if (this.$items) {
                                                        this.selectedIndexesInternal?.forEach((element, idx, array) => {
                                                            if (element > index) {
                                                                array[idx]--;
                                                            }
                                                        });
                                                        this.$selectedIndexes?.(this.selectedIndexesInternal);
                                                    }
                                                    this.$items?.(this.items.filter((element) => {
                                                        return element !== chipItem;
                                                    }));
                                                }
                                            }) }, undefined, elmtId, () => { }, { page: "components/src/main/ets/components/ChipGroupV2.ets", line: 587, col: 11 });
                                        ViewV2.create(componentCall);
                                        let paramsLambda = () => {
                                            return {
                                                chipV2Options: new ChipV2Options({
                                                    label: this.getLabel(chipItem.label),
                                                    prefixIcon: this.getPrefixIcon(chipItem),
                                                    suffixIcon: this.getSuffixIcon(chipItem),
                                                    allowClose: chipItem.allowClose ?? false,
                                                    closeIcon: chipItem.closeIcon ? new ChipV2CloseIcon(chipItem.closeIcon) : undefined,
                                                    enabled: true,
                                                    activated: this.isSelected(index),
                                                    backgroundColor: this.getBackgroundColor(),
                                                    size: this.getChipSize(),
                                                    activatedBackgroundColor: this.getSelectedBackgroundColor(),
                                                    accessibilitySelectedType: this.multiple ? ChipV2AccessibilitySelectedType.CHECKED : ChipV2AccessibilitySelectedType.SELECTED,
                                                    accessibilityDescription: chipItem.accessibilityDescription,
                                                    accessibilityLevel: chipItem.accessibilityLevel,
                                                    backgroundSystemMaterial: createSubECMaterial(material),
                                                    activatedBackgroundSystemMaterial: resolveSystemMaterial(this.itemStyle?.selectedBackgroundSystemMaterial),
                                                    onClicked: () => {
                                                        if (this.isSelected(index)) {
                                                            if (!(!this.isMultiple())) {
                                                                if (this.getSelectedIndexes().length > 1) {
                                                                    this.selectedIndexesInternal.splice(this.selectedIndexesInternal.indexOf(index), 1);
                                                                }
                                                            }
                                                        }
                                                        else {
                                                            if (!this.selectedIndexesInternal || this.selectedIndexesInternal.length === 0) {
                                                                this.selectedIndexesInternal = this.getSelectedIndexes();
                                                            }
                                                            if (!this.isMultiple()) {
                                                                this.selectedIndexesInternal = [];
                                                            }
                                                            this.selectedIndexesInternal.push(index);
                                                        }
                                                        this.getOnChange()(this.getSelectedIndexes());
                                                        this.$selectedIndexes?.(this.selectedIndexesInternal);
                                                    },
                                                    onClose: () => {
                                                        if (this.$items) {
                                                            this.selectedIndexesInternal?.forEach((element, idx, array) => {
                                                                if (element > index) {
                                                                    array[idx]--;
                                                                }
                                                            });
                                                            this.$selectedIndexes?.(this.selectedIndexesInternal);
                                                        }
                                                        this.$items?.(this.items.filter((element) => {
                                                            return element !== chipItem;
                                                        }));
                                                    }
                                                })
                                            };
                                        };
                                        componentCall.paramsGenerator_ = paramsLambda;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(elmtId, {
                                            chipV2Options: new ChipV2Options({
                                                label: this.getLabel(chipItem.label),
                                                prefixIcon: this.getPrefixIcon(chipItem),
                                                suffixIcon: this.getSuffixIcon(chipItem),
                                                allowClose: chipItem.allowClose ?? false,
                                                closeIcon: chipItem.closeIcon ? new ChipV2CloseIcon(chipItem.closeIcon) : undefined,
                                                enabled: true,
                                                activated: this.isSelected(index),
                                                backgroundColor: this.getBackgroundColor(),
                                                size: this.getChipSize(),
                                                activatedBackgroundColor: this.getSelectedBackgroundColor(),
                                                accessibilitySelectedType: this.multiple ? ChipV2AccessibilitySelectedType.CHECKED : ChipV2AccessibilitySelectedType.SELECTED,
                                                accessibilityDescription: chipItem.accessibilityDescription,
                                                accessibilityLevel: chipItem.accessibilityLevel,
                                                backgroundSystemMaterial: createSubECMaterial(material),
                                                activatedBackgroundSystemMaterial: resolveSystemMaterial(this.itemStyle?.selectedBackgroundSystemMaterial),
                                                onClicked: () => {
                                                    if (this.isSelected(index)) {
                                                        if (!(!this.isMultiple())) {
                                                            if (this.getSelectedIndexes().length > 1) {
                                                                this.selectedIndexesInternal.splice(this.selectedIndexesInternal.indexOf(index), 1);
                                                            }
                                                        }
                                                    }
                                                    else {
                                                        if (!this.selectedIndexesInternal || this.selectedIndexesInternal.length === 0) {
                                                            this.selectedIndexesInternal = this.getSelectedIndexes();
                                                        }
                                                        if (!this.isMultiple()) {
                                                            this.selectedIndexesInternal = [];
                                                        }
                                                        this.selectedIndexesInternal.push(index);
                                                    }
                                                    this.getOnChange()(this.getSelectedIndexes());
                                                    this.$selectedIndexes?.(this.selectedIndexesInternal);
                                                },
                                                onClose: () => {
                                                    if (this.$items) {
                                                        this.selectedIndexesInternal?.forEach((element, idx, array) => {
                                                            if (element > index) {
                                                                array[idx]--;
                                                            }
                                                        });
                                                        this.$selectedIndexes?.(this.selectedIndexesInternal);
                                                    }
                                                    this.$items?.(this.items.filter((element) => {
                                                        return element !== chipItem;
                                                    }));
                                                }
                                            })
                                        });
                                    }
                                }, { name: "ChipV2" });
                            }
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
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.align(Alignment.End);
            Row.width('100%');
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
            Scroll.padding({
                left: this.getChipGroupStartSpace(),
                right: this.getChipGroupEndSpace()
            });
            Scroll.constraintSize({ minWidth: '100%' });
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
            If.create();
            if (deviceInfo.sdkApiVersion >= 26) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (enableEffectComponent(this.itemStyle?.backgroundSystemMaterial)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    EffectComponent.create();
                                    EffectComponent.systemMaterial(createECMaterial(this.itemStyle?.backgroundSystemMaterial));
                                }, EffectComponent);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Row.create({ space: this.getChipGroupItemSpace() });
                                }, Row);
                                this.ChipItemsBuilder.bind(this)(createSubECMaterial(this.itemStyle?.backgroundSystemMaterial));
                                Row.pop();
                                EffectComponent.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.ChipItemsBuilder.bind(this)(this.itemStyle?.backgroundSystemMaterial);
                            });
                        }
                    }, If);
                    If.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.ChipItemsBuilder.bind(this)(undefined);
                });
            }
        }, If);
        If.pop();
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
                        Row.padding({
                            left: iconGroupSuffixTheme.marginLeft,
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
    }
    getLabel(label) {
        if (!label.fontColor) {
            label.fontColor = this.getFontColor();
        }
        if (!label.activatedFontColor) {
            label.activatedFontColor = this.getSelectedFontColor();
        }
        return label;
    }
    getPrefixIcon(chipItem) {
        if (chipItem.prefixSymbolIcon) {
            return chipItem.prefixSymbolIcon;
        }
        if (chipItem.prefixIcon) {
            if (!chipItem.prefixIcon.fillColor) {
                chipItem.prefixIcon.fillColor = this.getFillColor();
            }
            if (!chipItem.prefixIcon.activatedFillColor) {
                chipItem.prefixIcon.activatedFillColor = this.getSelectedFillColor();
            }
            return chipItem.prefixIcon;
        }
        return undefined;
    }
    getSuffixIcon(chipItem) {
        if (chipItem.suffixSymbolIcon) {
            return chipItem.suffixSymbolIcon;
        }
        if (chipItem.suffixIcon) {
            if (!chipItem.suffixIcon.fillColor) {
                chipItem.suffixIcon.fillColor = this.getFillColor();
            }
            if (!chipItem.suffixIcon.activatedFillColor) {
                chipItem.suffixIcon.activatedFillColor = this.getSelectedFillColor();
            }
            return chipItem.suffixIcon;
        }
        return undefined;
    }
    updateStateVars(params) {
        if (params === undefined) {
            return;
        }
        if ("items" in params) {
            this.updateParam("items", params.items);
        }
        if ("itemStyle" in params) {
            this.updateParam("itemStyle", params.itemStyle);
        }
        if ("selectedIndexes" in params) {
            this.updateParam("selectedIndexes", params.selectedIndexes);
        }
        if ("multiple" in params) {
            this.updateParam("multiple", params.multiple);
        }
        if ("chipGroupSpace" in params) {
            this.updateParam("chipGroupSpace", params.chipGroupSpace);
        }
        if ("chipGroupPadding" in params) {
            this.updateParam("chipGroupPadding", params.chipGroupPadding);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
], ChipGroupV2.prototype, "items", void 0);
__decorate([
    Event
], ChipGroupV2.prototype, "$items", void 0);
__decorate([
    Param
], ChipGroupV2.prototype, "itemStyle", void 0);
__decorate([
    Param
], ChipGroupV2.prototype, "selectedIndexes", void 0);
__decorate([
    Event
], ChipGroupV2.prototype, "$selectedIndexes", void 0);
__decorate([
    Param
], ChipGroupV2.prototype, "multiple", void 0);
__decorate([
    Param
], ChipGroupV2.prototype, "chipGroupSpace", void 0);
__decorate([
    Param
], ChipGroupV2.prototype, "chipGroupPadding", void 0);
__decorate([
    Event
], ChipGroupV2.prototype, "onChange", void 0);
__decorate([
    Provider()
], ChipGroupV2.prototype, "chipSize", void 0);
__decorate([
    Local
], ChipGroupV2.prototype, "selectedIndexesInternal", void 0);
__decorate([
    Local
], ChipGroupV2.prototype, "isReachEnd", void 0);
__decorate([
    Local
], ChipGroupV2.prototype, "isRefresh", void 0);
__decorate([
    Monitor('items')
], ChipGroupV2.prototype, "onItemsChange", null);
__decorate([
    Monitor('multiple')
], ChipGroupV2.prototype, "onMultipleChange", null);
__decorate([
    Monitor('itemStyle')
], ChipGroupV2.prototype, "itemStyleOnChange", null);
__decorate([
    Monitor('selectedIndexes')
], ChipGroupV2.prototype, "selectedIndexesOnChange", null);
function parseDimension(uiContext, value, isValid, defaultValue) {
    if (value === void (0) || value === null) {
        return defaultValue;
    }
    const resourceManager = uiContext.getHostContext()?.resourceManager;
    if (!resourceManager) {
        return defaultValue;
    }
    if (typeof value === 'object') {
        let temp = value;
        if (temp.type === 10002 || temp.type === 10007) {
            if (resourceManager && resourceManager.getNumber(temp.id) >= 0) {
                return value;
            }
        }
        else if (temp.type === 10003) {
            if (resourceManager && isValidDimensionString(resourceManager.getStringSync(temp.id))) {
                return value;
            }
        }
    }
    else if (typeof value === 'number') {
        if (value >= 0) {
            return value;
        }
    }
    else if (typeof value === 'string') {
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
    return isValidString(dimension, new RegExp('(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$', 'i'));
}
function isValidDimensionNoPercentageString(dimension) {
    return isValidString(dimension, new RegExp('(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx)?$', 'i'));
}
function resolveSystemMaterial(material) {
    let info = uiMaterial.getMaterialInfo();
    if (info.state === uiMaterial.MaterialState.DISABLE) {
        return undefined;
    }
    return info.state === uiMaterial.MaterialState.ENABLE && !material ?
        new uiMaterial.ImmersiveMaterial({ style: uiMaterial.ImmersiveStyle.ULTRA_THIN }) : material;
}
function enableEffectComponent(material) {
    return false;
}
function createECMaterial(material) {
    return undefined;
}
function createSubECMaterial(material) {
    return resolveSystemMaterial(material);
}
function lengthMetricsToLength(length) {
    if (length.unit === LengthUnit.PX) {
        return `${length.value}px`;
    }
    else if (length.unit === LengthUnit.VP) {
        return `${length.value}vp`;
    }
    else if (length.unit === LengthUnit.FP) {
        return `${length.value}fp`;
    }
    else if (length.unit === LengthUnit.PERCENT) {
        return `${length.value}%`;
    }
    else if (length.unit === LengthUnit.LPX) {
        return `${length.value}lpx`;
    }
    return 0;
}
export default {
    ChipGroupV2Item,
    ChipGroupV2Items,
    ChipGroupV2ItemStyle,
    ChipGroupV2Space,
    ChipGroupV2Padding,
    ChipGroupV2IconGroupSuffix,
    ChipGroupV2,
}