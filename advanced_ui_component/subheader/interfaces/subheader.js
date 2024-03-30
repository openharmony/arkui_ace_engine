/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;
const hilog = requireNapi('hilog');
const resourceManager = requireNapi('resourceManager');
if (!('finalizeConstruction' in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => { });
}
const IMAGE_WIDTH_NUM = 16;
const IMAGE_HEIGHT_NUM = 24;
const BUTTON_SIZE = 32;
const SINGLE_LINE_HEIGHT = 56;
const DOUBLE_LINE_HEIGHT = 72;
const BUTTON_HEIGHT = 28;
const ARROW_WIDTH = 12;
const BORDER_WIDTH = 2;
const DIVIDEND_NUM = 3;
const DIVIDEND_NUM_TWO = 2;
const SINGLE_LINE_NUM = 1;
const DOUBLE_LINE_NUM = 2;
const INDEX_ZERO = 0;
const INDEX_ONE = 1;
const INDEX_TWO = 2;
const RESOURCE_TYPE_SYMBOL = 40000;
const DEFAULT_VALUE = 0;
export var OperationType;
(function (w11) {
    w11[w11["TEXT_ARROW"] = 0] = "TEXT_ARROW";
    w11[w11["BUTTON"] = 1] = "BUTTON";
    w11[w11["ICON_GROUP"] = 2] = "ICON_GROUP";
    w11[w11["LOADING"] = 3] = "LOADING";
})(OperationType || (OperationType = {}));
class IconOptions {
}
class ContentIconOption {
}
class FontStyle {
    constructor() {
        this.maxLines = 0;
        this.fontWeight = 0;
    }
}
function __Text__secondaryTitleStyles(v11) {
    Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.Subtitle_S'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
    Text.fontColor(v11?.fontColor ?? { "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
    Text.fontWeight(v11?.fontWeight);
    Text.maxLines(v11?.maxLines);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.align(v11?.alignment);
}
function __Text__primaryTitleStyles(u11) {
    Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.Subtitle_L'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
    Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
    Text.fontWeight(u11?.fontWeight);
    Text.maxLines(u11?.maxLines);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.align(u11?.alignment);
}
export class SubHeader extends ViewPU {
    constructor(o11, p11, q11, r11 = -1, s11 = undefined, t11) {
        super(o11, q11, r11, t11);
        if (typeof s11 === "function") {
            this.paramsGenerator_ = s11;
        }
        this.__icon = new SynchedPropertyObjectOneWayPU(p11.icon, this, "icon");
        this.iconSymbolOptions = null;
        this.__primaryTitle = new SynchedPropertyObjectOneWayPU(p11.primaryTitle, this, "primaryTitle");
        this.__secondaryTitle = new SynchedPropertyObjectOneWayPU(p11.secondaryTitle, this, "secondaryTitle");
        this.select = null;
        this.__operationType = new SynchedPropertySimpleOneWayPU(p11.operationType, this, "operationType");
        this.operationItem = null;
        this.operationSymbolOptions = null;
        this.__isDuplicateLine = new ObservedPropertySimplePU(false, this, "isDuplicateLine");
        this.__textArrowBgColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "textArrowBgColor");
        this.__buttonBgColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "buttonBgColor");
        this.__flexWidth = new ObservedPropertySimplePU(0, this, "flexWidth");
        this.__textArrowFocus = new ObservedPropertySimplePU(false, this, "textArrowFocus");
        this.__buttonFocus = new ObservedPropertySimplePU(false, this, "buttonFocus");
        this.__textArrowStyleWidth = new ObservedPropertySimplePU(0, this, "textArrowStyleWidth");
        this.__textArrowStyleHeight = new ObservedPropertySimplePU(0, this, "textArrowStyleHeight");
        this.__buttonStyleWidth = new ObservedPropertySimplePU(0, this, "buttonStyleWidth");
        this.__buttonStyleHeight = new ObservedPropertySimplePU(0, this, "buttonStyleHeight");
        this.__iconTextStyleWidth = new ObservedPropertySimplePU(0, this, "iconTextStyleWidth");
        this.__iconTextWidth = new ObservedPropertySimplePU(0, this, "iconTextWidth");
        this.__iconWidth = new ObservedPropertySimplePU(0, this, "iconWidth");
        this.focusBorderWidth = BORDER_WIDTH;
        this.__flexAlign = new ObservedPropertySimplePU(FlexAlign.SpaceBetween, this, "flexAlign");
        this.setInitiallyProvidedValue(p11);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(n11) {
        if (n11.icon === undefined) {
            this.__icon.set(null);
        }
        if (n11.iconSymbolOptions !== undefined) {
            this.iconSymbolOptions = n11.iconSymbolOptions;
        }
        if (n11.primaryTitle === undefined) {
            this.__primaryTitle.set(null);
        }
        if (n11.secondaryTitle === undefined) {
            this.__secondaryTitle.set(null);
        }
        if (n11.select !== undefined) {
            this.select = n11.select;
        }
        if (n11.operationType === undefined) {
            this.__operationType.set(OperationType.BUTTON);
        }
        if (n11.operationItem !== undefined) {
            this.operationItem = n11.operationItem;
        }
        if (n11.operationSymbolOptions !== undefined) {
            this.operationSymbolOptions = n11.operationSymbolOptions;
        }
        if (n11.isDuplicateLine !== undefined) {
            this.isDuplicateLine = n11.isDuplicateLine;
        }
        if (n11.textArrowBgColor !== undefined) {
            this.textArrowBgColor = n11.textArrowBgColor;
        }
        if (n11.buttonBgColor !== undefined) {
            this.buttonBgColor = n11.buttonBgColor;
        }
        if (n11.flexWidth !== undefined) {
            this.flexWidth = n11.flexWidth;
        }
        if (n11.textArrowFocus !== undefined) {
            this.textArrowFocus = n11.textArrowFocus;
        }
        if (n11.buttonFocus !== undefined) {
            this.buttonFocus = n11.buttonFocus;
        }
        if (n11.textArrowStyleWidth !== undefined) {
            this.textArrowStyleWidth = n11.textArrowStyleWidth;
        }
        if (n11.textArrowStyleHeight !== undefined) {
            this.textArrowStyleHeight = n11.textArrowStyleHeight;
        }
        if (n11.buttonStyleWidth !== undefined) {
            this.buttonStyleWidth = n11.buttonStyleWidth;
        }
        if (n11.buttonStyleHeight !== undefined) {
            this.buttonStyleHeight = n11.buttonStyleHeight;
        }
        if (n11.iconTextStyleWidth !== undefined) {
            this.iconTextStyleWidth = n11.iconTextStyleWidth;
        }
        if (n11.iconTextWidth !== undefined) {
            this.iconTextWidth = n11.iconTextWidth;
        }
        if (n11.iconWidth !== undefined) {
            this.iconWidth = n11.iconWidth;
        }
        if (n11.focusBorderWidth !== undefined) {
            this.focusBorderWidth = n11.focusBorderWidth;
        }
        if (n11.flexAlign !== undefined) {
            this.flexAlign = n11.flexAlign;
        }
    }
    updateStateVars(m11) {
        this.__icon.reset(m11.icon);
        this.__primaryTitle.reset(m11.primaryTitle);
        this.__secondaryTitle.reset(m11.secondaryTitle);
        this.__operationType.reset(m11.operationType);
    }
    purgeVariableDependenciesOnElmtId(l11) {
        this.__icon.purgeDependencyOnElmtId(l11);
        this.__primaryTitle.purgeDependencyOnElmtId(l11);
        this.__secondaryTitle.purgeDependencyOnElmtId(l11);
        this.__operationType.purgeDependencyOnElmtId(l11);
        this.__isDuplicateLine.purgeDependencyOnElmtId(l11);
        this.__textArrowBgColor.purgeDependencyOnElmtId(l11);
        this.__buttonBgColor.purgeDependencyOnElmtId(l11);
        this.__flexWidth.purgeDependencyOnElmtId(l11);
        this.__textArrowFocus.purgeDependencyOnElmtId(l11);
        this.__buttonFocus.purgeDependencyOnElmtId(l11);
        this.__textArrowStyleWidth.purgeDependencyOnElmtId(l11);
        this.__textArrowStyleHeight.purgeDependencyOnElmtId(l11);
        this.__buttonStyleWidth.purgeDependencyOnElmtId(l11);
        this.__buttonStyleHeight.purgeDependencyOnElmtId(l11);
        this.__iconTextStyleWidth.purgeDependencyOnElmtId(l11);
        this.__iconTextWidth.purgeDependencyOnElmtId(l11);
        this.__iconWidth.purgeDependencyOnElmtId(l11);
        this.__flexAlign.purgeDependencyOnElmtId(l11);
    }
    aboutToBeDeleted() {
        this.__icon.aboutToBeDeleted();
        this.__primaryTitle.aboutToBeDeleted();
        this.__secondaryTitle.aboutToBeDeleted();
        this.__operationType.aboutToBeDeleted();
        this.__isDuplicateLine.aboutToBeDeleted();
        this.__textArrowBgColor.aboutToBeDeleted();
        this.__buttonBgColor.aboutToBeDeleted();
        this.__flexWidth.aboutToBeDeleted();
        this.__textArrowFocus.aboutToBeDeleted();
        this.__buttonFocus.aboutToBeDeleted();
        this.__textArrowStyleWidth.aboutToBeDeleted();
        this.__textArrowStyleHeight.aboutToBeDeleted();
        this.__buttonStyleWidth.aboutToBeDeleted();
        this.__buttonStyleHeight.aboutToBeDeleted();
        this.__iconTextStyleWidth.aboutToBeDeleted();
        this.__iconTextWidth.aboutToBeDeleted();
        this.__iconWidth.aboutToBeDeleted();
        this.__flexAlign.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get icon() {
        return this.__icon.get();
    }
    set icon(k11) {
        this.__icon.set(k11);
    }
    get primaryTitle() {
        return this.__primaryTitle.get();
    }
    set primaryTitle(j11) {
        this.__primaryTitle.set(j11);
    }
    get secondaryTitle() {
        return this.__secondaryTitle.get();
    }
    set secondaryTitle(i11) {
        this.__secondaryTitle.set(i11);
    }
    get operationType() {
        return this.__operationType.get();
    }
    set operationType(h11) {
        this.__operationType.set(h11);
    }
    get isDuplicateLine() {
        return this.__isDuplicateLine.get();
    }
    set isDuplicateLine(g11) {
        this.__isDuplicateLine.set(g11);
    }
    get textArrowBgColor() {
        return this.__textArrowBgColor.get();
    }
    set textArrowBgColor(f11) {
        this.__textArrowBgColor.set(f11);
    }
    get buttonBgColor() {
        return this.__buttonBgColor.get();
    }
    set buttonBgColor(e11) {
        this.__buttonBgColor.set(e11);
    }
    get flexWidth() {
        return this.__flexWidth.get();
    }
    set flexWidth(d11) {
        this.__flexWidth.set(d11);
    }
    get textArrowFocus() {
        return this.__textArrowFocus.get();
    }
    set textArrowFocus(c11) {
        this.__textArrowFocus.set(c11);
    }
    get buttonFocus() {
        return this.__buttonFocus.get();
    }
    set buttonFocus(b11) {
        this.__buttonFocus.set(b11);
    }
    get textArrowStyleWidth() {
        return this.__textArrowStyleWidth.get();
    }
    set textArrowStyleWidth(a11) {
        this.__textArrowStyleWidth.set(a11);
    }
    get textArrowStyleHeight() {
        return this.__textArrowStyleHeight.get();
    }
    set textArrowStyleHeight(z10) {
        this.__textArrowStyleHeight.set(z10);
    }
    get buttonStyleWidth() {
        return this.__buttonStyleWidth.get();
    }
    set buttonStyleWidth(y10) {
        this.__buttonStyleWidth.set(y10);
    }
    get buttonStyleHeight() {
        return this.__buttonStyleHeight.get();
    }
    set buttonStyleHeight(x10) {
        this.__buttonStyleHeight.set(x10);
    }
    get iconTextStyleWidth() {
        return this.__iconTextStyleWidth.get();
    }
    set iconTextStyleWidth(w10) {
        this.__iconTextStyleWidth.set(w10);
    }
    get iconTextWidth() {
        return this.__iconTextWidth.get();
    }
    set iconTextWidth(v10) {
        this.__iconTextWidth.set(v10);
    }
    get iconWidth() {
        return this.__iconWidth.get();
    }
    set iconWidth(u10) {
        this.__iconWidth.set(u10);
    }
    get flexAlign() {
        return this.__flexAlign.get();
    }
    set flexAlign(t10) {
        this.__flexAlign.set(t10);
    }
    initialRender() {
        this.observeComponentCreation2((n10, o10) => {
            Flex.create({ justifyContent: this.flexAlign, alignItems: ItemAlign.End });
            Flex.focusable(true);
            Flex.onAreaChange((q10, r10) => {
                let s10 = Number(parseInt(r10.width.toString(), DEFAULT_VALUE));
                this.flexWidth = s10;
            });
            Flex.constraintSize({ minHeight: this.isDuplicateLine ? DOUBLE_LINE_HEIGHT : SINGLE_LINE_HEIGHT });
        }, Flex);
        this.leftArea.bind(this)();
        this.rightArea.bind(this)();
        Flex.pop();
    }
    leftArea(c10 = null) {
        this.observeComponentCreation2((e10, f10) => {
            If.create();
            if (this.secondaryTitle && this.icon) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.IconSecondaryTitleStyle.bind(this)(makeBuilderParameterProxy("IconSecondaryTitleStyle", { content: () => (this["__secondaryTitle"] ? this["__secondaryTitle"] : this["secondaryTitle"]), iconOptions: () => ({
                            icon: this.icon,
                            symbolicIconOption: this.iconSymbolOptions,
                        }) }));
                });
            }
            else if (this.secondaryTitle && this.primaryTitle) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.SubTitleStyle.bind(this)(makeBuilderParameterProxy("SubTitleStyle", { content: () => (this["__primaryTitle"] ? this["__primaryTitle"] : this["primaryTitle"]), subContent: () => (this["__secondaryTitle"] ? this["__secondaryTitle"] : this["secondaryTitle"]) }));
                });
            }
            else if (this.secondaryTitle) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.SecondTitleStyle.bind(this)(makeBuilderParameterProxy("SecondTitleStyle", { content: () => (this["__secondaryTitle"] ? this["__secondaryTitle"] : this["secondaryTitle"]) }));
                });
            }
            else if (this.select) {
                this.ifElseBranchUpdateFunction(3, () => {
                    this.SelectStyle.bind(this)(this.select);
                });
            }
            else if (this.primaryTitle) {
                this.ifElseBranchUpdateFunction(4, () => {
                    this.PrimaryTitleStyle.bind(this)(makeBuilderParameterProxy("PrimaryTitleStyle", { content: () => (this["__primaryTitle"] ? this["__primaryTitle"] : this["primaryTitle"]) }));
                });
            }
            else {
                this.ifElseBranchUpdateFunction(5, () => {
                    this.dummyFunction.bind(this)();
                });
            }
        }, If);
        If.pop();
    }
    rightArea(h9 = null) {
        this.observeComponentCreation2((y9, z9) => {
            If.create();
            if (this.operationType === OperationType.BUTTON && (this.operationItem && this.operationItem.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.ButtonStyle.bind(this)(this.operationItem[0]);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((u9, v9) => {
            If.create();
            if (this.operationType === OperationType.ICON_GROUP && (this.operationItem && this.operationItem.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.IconGroupStyle.bind(this)(this.operationItem);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((q9, r9) => {
            If.create();
            if (this.operationType === OperationType.TEXT_ARROW && (this.operationItem && this.operationItem.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.TextArrowStyle.bind(this)(this.operationItem[0]);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((m9, n9) => {
            If.create();
            if (this.operationType === OperationType.LOADING) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.LoadingProcessStyle.bind(this)();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }
    IconSecondaryTitleStyle(e8, f8 = null) {
        this.observeComponentCreation2((b9, c9) => {
            Row.create();
            Row.width(this.flexWidth / DIVIDEND_NUM * DIVIDEND_NUM_TWO);
            Row.padding({
                left: { "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                right: { "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                top: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            });
            Row.margin({
                left: { "id": -1, "type": 10002, params: ['sys.float.margin_left'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                right: { "id": -1, "type": 10002, params: ['sys.float.margin_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            });
            Row.onAppear(() => {
                this.isDuplicateLine = false;
                this.changeFlexAlign(FlexAlign.SpaceBetween);
            });
            Row.onAreaChange((f9, g9) => {
                this.iconTextStyleWidth = Number(g9.width);
                this.updateMaxIconTextWidth();
            });
        }, Row);
        this.observeComponentCreation2((w8, x8) => {
            Row.create();
            Row.onAreaChange((z8, a9) => {
                this.iconWidth = Number(a9.width);
                this.updateMaxIconTextWidth();
            });
        }, Row);
        this.observeComponentCreation2((m8, n8) => {
            If.create();
            if (Util.isSymbolResource(e8.iconOptions?.icon)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((u8, v8) => {
                        SymbolGlyph.create(e8.iconOptions?.icon);
                        SymbolGlyph.focusable(true);
                        SymbolGlyph.fontSize(e8.iconOptions?.symbolicIconOption?.fontSize ?? IMAGE_WIDTH_NUM);
                        SymbolGlyph.fontColor(e8.iconOptions?.symbolicIconOption?.fontColor ?? [{ "id": -1, "type": 10001, params: ['sys.color.icon_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
                        SymbolGlyph.fontWeight(e8.iconOptions?.symbolicIconOption?.fontWeight);
                        SymbolGlyph.renderingStrategy(e8.iconOptions?.symbolicIconOption?.renderingStrategy);
                        SymbolGlyph.effectStrategy(e8.iconOptions?.symbolicIconOption?.effectStrategy);
                        SymbolGlyph.margin({ right: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } });
                    }, SymbolGlyph);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((q8, r8) => {
                        Image.create(e8.iconOptions?.icon);
                        Image.width(IMAGE_WIDTH_NUM);
                        Image.height(IMAGE_WIDTH_NUM);
                        Image.margin({ right: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } });
                        Image.draggable(false);
                    }, Image);
                });
            }
        }, If);
        If.pop();
        Row.pop();
        this.observeComponentCreation2((k8, l8) => {
            Text.create(e8.content);
            __Text__secondaryTitleStyles({
                maxLines: DOUBLE_LINE_NUM,
                fontWeight: FontWeight.Medium,
                alignment: Alignment.Start,
            });
            Text.width(this.iconTextWidth);
        }, Text);
        Text.pop();
        Row.pop();
    }
    SubTitleStyle(s7, t7 = null) {
        this.observeComponentCreation2((b8, c8) => {
            Column.create();
            Column.width(this.flexWidth / DIVIDEND_NUM * DIVIDEND_NUM_TWO);
            Column.margin({
                left: { "id": -1, "type": 10002, params: ['sys.float.margin_left'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                right: { "id": -1, "type": 10002, params: ['sys.float.margin_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            });
            Column.padding({
                left: { "id": -1, "type": 10002, params: ['sys.float.padding_level0'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                right: { "id": -1, "type": 10002, params: ['sys.float.padding_level0'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                top: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            });
            Column.alignItems(HorizontalAlign.Start);
            Column.onAppear(() => {
                this.isDuplicateLine = true;
                this.changeFlexAlign(FlexAlign.SpaceBetween);
            });
        }, Column);
        this.observeComponentCreation2((z7, a8) => {
            Text.create(s7.content);
            __Text__primaryTitleStyles({
                fontWeight: FontWeight.Bold,
                maxLines: SINGLE_LINE_NUM,
                alignment: Alignment.Start,
            });
            Text.width('100%');
        }, Text);
        Text.pop();
        this.observeComponentCreation2((x7, y7) => {
            Text.create(s7.subContent);
            __Text__secondaryTitleStyles({
                maxLines: SINGLE_LINE_NUM,
                fontWeight: FontWeight.Regular,
                alignment: Alignment.Start,
            });
            Text.width('100%');
            Text.margin({
                top: { "id": -1, "type": 10002, params: ['sys.float.padding_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            });
        }, Text);
        Text.pop();
        Column.pop();
    }
    SecondTitleStyle(j7, k7 = null) {
        this.observeComponentCreation2((q7, r7) => {
            Column.create();
            Column.alignItems(HorizontalAlign.Start);
            Column.width(this.flexWidth / DIVIDEND_NUM * DIVIDEND_NUM_TWO);
            Column.padding({
                left: { "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                right: { "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                top: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            });
            Column.margin({
                left: { "id": -1, "type": 10002, params: ['sys.float.margin_left'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                right: { "id": -1, "type": 10002, params: ['sys.float.margin_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            });
        }, Column);
        this.observeComponentCreation2((n7, o7) => {
            Text.create(j7.content);
            __Text__secondaryTitleStyles({
                maxLines: DOUBLE_LINE_NUM,
                fontWeight: FontWeight.Medium,
                alignment: Alignment.Start,
            });
            Text.width('100%');
            Text.onAppear(() => {
                this.isDuplicateLine = false;
                this.changeFlexAlign(FlexAlign.SpaceBetween);
            });
        }, Text);
        Text.pop();
        Column.pop();
    }
    SelectStyle(x6, y6 = null) {
        this.observeComponentCreation2((g7, h7) => {
            Column.create();
            Column.width(this.flexWidth / DIVIDEND_NUM * DIVIDEND_NUM_TWO);
            Column.alignItems(HorizontalAlign.Start);
            Column.margin({
                left: { "id": -1, "type": 10002, params: ['sys.float.margin_left'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                right: { "id": -1, "type": 10002, params: ['sys.float.margin_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            });
            Column.onAppear(() => {
                this.isDuplicateLine = false;
                this.changeFlexAlign(FlexAlign.SpaceBetween);
            });
        }, Column);
        this.observeComponentCreation2((b7, c7) => {
            Select.create(x6.options);
            Select.selected(x6.selected);
            Select.value(x6.value);
            Select.onSelect((e7, f7) => {
                if (x6.onSelect) {
                    x6.onSelect(e7, f7);
                }
            });
            Select.font({
                size: { "id": -1, "type": 10002, params: ['sys.float.Body_L'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                weight: FontWeight.Medium,
            });
        }, Select);
        Select.pop();
        Column.pop();
    }
    PrimaryTitleStyle(o6, p6 = null) {
        this.observeComponentCreation2((v6, w6) => {
            Column.create();
            Column.width(this.flexWidth / DIVIDEND_NUM * DIVIDEND_NUM_TWO);
            Column.alignItems(HorizontalAlign.Start);
            Column.margin({
                left: { "id": -1, "type": 10002, params: ['sys.float.margin_left'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                right: { "id": -1, "type": 10002, params: ['sys.float.margin_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            });
            Column.padding({
                left: { "id": -1, "type": 10002, params: ['sys.float.padding_level0'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                right: { "id": -1, "type": 10002, params: ['sys.float.padding_level0'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                top: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            });
        }, Column);
        this.observeComponentCreation2((s6, t6) => {
            Text.create(o6.content);
            __Text__primaryTitleStyles({
                fontWeight: FontWeight.Bold,
                maxLines: DOUBLE_LINE_NUM,
                alignment: Alignment.Start,
            });
            Text.width('100%');
            Text.onAppear(() => {
                this.isDuplicateLine = false;
                this.changeFlexAlign(FlexAlign.SpaceBetween);
            });
        }, Text);
        Text.pop();
        Column.pop();
    }
    ButtonStyle(k5, l5 = null) {
        this.observeComponentCreation2((m6, n6) => {
            Row.create();
            Row.margin({
                left: { "id": -1, "type": 10002, params: ['sys.float.padding_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                right: { "id": -1, "type": 10002, params: ['sys.float.padding_level5'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            });
            Row.width(this.flexWidth / DIVIDEND_NUM);
            Row.justifyContent(FlexAlign.End);
            Row.focusable(true);
        }, Row);
        this.observeComponentCreation2((k6, l6) => {
            Stack.create();
            Stack.focusable(true);
        }, Stack);
        this.observeComponentCreation2((p5, q5) => {
            If.create();
            if (k5) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((x5, y5) => {
                        Row.create();
                        Row.padding({
                            left: { "id": -1, "type": 10002, params: ['sys.float.padding_level3'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                            right: { "id": -1, "type": 10002, params: ['sys.float.padding_level3'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                        });
                        Row.margin({
                            bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                        });
                        Row.backgroundColor(ObservedObject.GetRawObject(this.buttonBgColor));
                        Row.focusable(true);
                        Row.constraintSize({ minHeight: BUTTON_HEIGHT });
                        Row.justifyContent(FlexAlign.End);
                        Row.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        ViewStackProcessor.visualState("focused");
                        Row.border({
                            radius: { "id": -1, "type": 10002, params: ['sys.float.corner_radius_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                            width: this.buttonStyleWidth,
                            color: { "id": -1, "type": 10001, params: ['sys.color.interactive_focus'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                            style: BorderStyle.Solid,
                        });
                        Row.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.interactive_focus'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        ViewStackProcessor.visualState("pressed");
                        Row.border({
                            radius: { "id": -1, "type": 10002, params: ['sys.float.corner_radius_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                            color: { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                        });
                        Row.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        ViewStackProcessor.visualState("disabled");
                        Row.opacity({ "id": -1, "type": 10002, params: ['sys.float.interactive_disable'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        ViewStackProcessor.visualState();
                        Row.onFocus(() => {
                            this.buttonFocus = true;
                            this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_focus'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                        });
                        Row.onBlur(() => {
                            this.buttonFocus = false;
                        });
                        Row.onHover((j6) => {
                            if (j6) {
                                this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                            else {
                                this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                        });
                        Row.onTouch((i6) => {
                            if (i6.type === TouchType.Down) {
                                if (k5.action) {
                                    k5.action();
                                }
                                this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                            if (i6.type === TouchType.Up) {
                                this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                        });
                        Row.onKeyEvent((h6) => {
                            if (h6.keyCode === KeyCode.KEYCODE_ENTER || h6.keyCode === KeyCode.KEYCODE_SPACE) {
                                if (k5.action) {
                                    k5.action();
                                }
                            }
                        });
                        Row.onAreaChange((f6, g6) => {
                            this.buttonStyleWidth = Number(g6.width);
                            this.buttonStyleHeight = Number(g6.height);
                        });
                    }, Row);
                    this.observeComponentCreation2((v5, w5) => {
                        Text.create(k5.value);
                        __Text__secondaryTitleStyles({
                            fontWeight: FontWeight.Medium,
                            maxLines: SINGLE_LINE_NUM,
                            fontColor: { "id": -1, "type": 10001, params: ['sys.color.font_emphasize'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                        });
                        Text.focusable(true);
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
        Stack.pop();
        Row.pop();
    }
    IconGroupStyle(v3, w3 = null) {
        this.observeComponentCreation2((i5, j5) => {
            Row.create();
            Row.justifyContent(FlexAlign.End);
            Row.width(this.flexWidth / DIVIDEND_NUM);
            Row.focusable(true);
            Row.margin({
                left: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                right: { "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            });
        }, Row);
        this.observeComponentCreation2((z3, a4) => {
            ForEach.create();
            const b4 = (d4, e4) => {
                const f4 = d4;
                this.observeComponentCreation2((h4, i4) => {
                    If.create();
                    if (Util.isResourceType(f4.value)) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((m4, n4) => {
                                If.create();
                                if (e4 === INDEX_ZERO) {
                                    this.ifElseBranchUpdateFunction(0, () => {
                                        {
                                            this.observeComponentCreation2((c5, d5) => {
                                                if (d5) {
                                                    let e5 = new SingleIconStyle(this, {
                                                        item: {
                                                            iconOptions: {
                                                                icon: f4.value,
                                                                symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > e4 ?
                                                                    this.operationSymbolOptions[e4] : null,
                                                            },
                                                            action: f4.action,
                                                        }
                                                    }, undefined, c5, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 470 });
                                                    ViewPU.create(e5);
                                                    let f5 = () => {
                                                        return {
                                                            item: {
                                                                iconOptions: {
                                                                    icon: f4.value,
                                                                    symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > e4 ?
                                                                        this.operationSymbolOptions[e4] : null,
                                                                },
                                                                action: f4.action,
                                                            }
                                                        };
                                                    };
                                                    e5.paramsGenerator_ = f5;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(c5, {});
                                                }
                                            }, { name: "SingleIconStyle" });
                                        }
                                    });
                                }
                                else if (e4 === INDEX_ONE || e4 === INDEX_TWO) {
                                    this.ifElseBranchUpdateFunction(1, () => {
                                        this.observeComponentCreation2((y4, z4) => {
                                            __Common__.create();
                                            __Common__.margin({
                                                left: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                                            });
                                        }, __Common__);
                                        {
                                            this.observeComponentCreation2((s4, t4) => {
                                                if (t4) {
                                                    let u4 = new SingleIconStyle(this, {
                                                        item: {
                                                            action: f4.action,
                                                            iconOptions: {
                                                                icon: f4.value,
                                                                symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > e4 ?
                                                                    this.operationSymbolOptions[e4] : null,
                                                            },
                                                        }
                                                    }, undefined, s4, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 481 });
                                                    ViewPU.create(u4);
                                                    let v4 = () => {
                                                        return {
                                                            item: {
                                                                action: f4.action,
                                                                iconOptions: {
                                                                    icon: f4.value,
                                                                    symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > e4 ?
                                                                        this.operationSymbolOptions[e4] : null,
                                                                },
                                                            }
                                                        };
                                                    };
                                                    u4.paramsGenerator_ = v4;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(s4, {});
                                                }
                                            }, { name: "SingleIconStyle" });
                                        }
                                        __Common__.pop();
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
            };
            this.forEachUpdateFunction(z3, v3, b4, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }
    TextArrowStyle(l2, m2 = null) {
        this.observeComponentCreation2((t3, u3) => {
            Row.create();
            Row.focusable(true);
            Row.width(this.flexWidth / DIVIDEND_NUM);
            Row.justifyContent(FlexAlign.End);
            Row.margin({
                left: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                right: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            });
        }, Row);
        this.observeComponentCreation2((r3, s3) => {
            Stack.create();
        }, Stack);
        this.observeComponentCreation2((e3, f3) => {
            Row.create();
            Row.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Row.focusable(true);
            Row.backgroundColor(ObservedObject.GetRawObject(this.textArrowBgColor));
            Row.constraintSize({ minHeight: BUTTON_SIZE });
            Row.onFocus(() => {
                this.textArrowFocus = true;
            });
            Row.onBlur(() => {
                this.textArrowFocus = false;
            });
            Row.padding({
                left: { "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                right: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                top: { "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            });
            Row.onHover((q3) => {
                if (q3) {
                    this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                }
                else {
                    this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                }
            });
            Row.onTouch((p3) => {
                if (p3.type === TouchType.Down) {
                    if (l2.action) {
                        l2.action();
                    }
                    this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                }
                if (p3.type === TouchType.Up) {
                    this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                }
            });
            Row.onKeyEvent((o3) => {
                if (o3.keyCode === KeyCode.KEYCODE_ENTER || o3.keyCode === KeyCode.KEYCODE_SPACE) {
                    if (l2.action) {
                        l2.action();
                    }
                }
            });
            Row.onAreaChange((m3, n3) => {
                this.textArrowStyleWidth = Number(n3.width);
                this.textArrowStyleHeight = Number(n3.height);
            });
        }, Row);
        this.observeComponentCreation2((x2, y2) => {
            If.create();
            if (l2) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((c3, d3) => {
                        Text.create(l2.value);
                        __Text__secondaryTitleStyles({
                            maxLines: SINGLE_LINE_NUM,
                            fontWeight: FontWeight.Regular,
                            alignment: Alignment.End,
                        });
                        Text.margin({
                            right: { "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                        });
                        Text.focusable(true);
                        Text.constraintSize({ maxWidth: this.getMaxArrowTextWidth() });
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
        this.observeComponentCreation2((v2, w2) => {
            Image.create({ "id": -1, "type": 20000, params: ['sys.media.ohos_ic_public_arrow_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_tertiary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.width(ARROW_WIDTH);
            Image.height(IMAGE_HEIGHT_NUM);
            Image.focusable(true);
            Image.draggable(false);
        }, Image);
        Row.pop();
        this.observeComponentCreation2((t2, u2) => {
            Row.create();
            Row.height(this.textArrowStyleHeight);
            Row.width(this.textArrowStyleWidth);
            Row.hitTestBehavior(HitTestMode.None);
            Row.border({
                radius: { "id": -1, "type": 10002, params: ['sys.float.corner_radius_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                width: { "id": -1, "type": 10002, params: ['sys.float.outline_extra_larger'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                color: { "id": -1, "type": 10001, params: ['sys.color.interactive_focus'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            });
            ViewStackProcessor.visualState("focused");
            Row.border({
                radius: { "id": -1, "type": 10002, params: ['sys.float.corner_radius_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                width: { "id": -1, "type": 10002, params: ['sys.float.outline_extra_larger'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                color: { "id": -1, "type": 10001, params: ['sys.color.interactive_focus'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            });
            Row.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.interactive_focus'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            ViewStackProcessor.visualState("pressed");
            Row.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            ViewStackProcessor.visualState("disabled");
            Row.opacity({ "id": -1, "type": 10002, params: ['sys.float.interactive_disable'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            ViewStackProcessor.visualState("normal");
            Row.border({
                radius: { "id": -1, "type": 10002, params: ['sys.float.corner_radius_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                width: { "id": -1, "type": 10002, params: ['sys.float.border_none'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                color: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_focused_outline_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            });
            ViewStackProcessor.visualState();
        }, Row);
        Row.pop();
        Stack.pop();
        Row.pop();
    }
    LoadingProcessStyle(d2 = null) {
        this.observeComponentCreation2((j2, k2) => {
            Row.create();
            Row.focusable(true);
            Row.width(this.flexWidth / DIVIDEND_NUM);
            Row.justifyContent(FlexAlign.End);
            Row.padding({
                top: { "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            });
            Row.margin({
                left: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                right: { "id": -1, "type": 10002, params: ['sys.float.margin_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            });
        }, Row);
        this.observeComponentCreation2((g2, h2) => {
            LoadingProgress.create();
            LoadingProgress.width(IMAGE_HEIGHT_NUM);
            LoadingProgress.height(IMAGE_HEIGHT_NUM);
            LoadingProgress.color({ "id": -1, "type": 10001, params: ['sys.color.icon_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            LoadingProgress.focusable(true);
            LoadingProgress.onAppear(() => {
                this.isDuplicateLine = false;
            });
        }, LoadingProgress);
        Row.pop();
    }
    dummyFunction(y1 = null) {
        this.observeComponentCreation2((a2, b2) => {
            Row.create();
            Row.onAppear(() => {
                this.changeFlexAlign(FlexAlign.End);
            });
        }, Row);
        Row.pop();
    }
    getMaxArrowTextWidth() {
        return this.textArrowStyleWidth - getNumberByResource('padding_level2') - getNumberByResource('padding_level2') -
            getNumberByResource('padding_level4') - ARROW_WIDTH;
    }
    updateMaxIconTextWidth() {
        this.iconTextWidth = this.iconTextStyleWidth - getNumberByResource('padding_level6') - this.iconWidth -
            getNumberByResource('padding_level6');
    }
    changeFlexAlign(x1) {
        if (this.flexAlign === x1) {
            return;
        }
        this.flexAlign = x1;
    }
    rerender() {
        this.updateDirtyElements();
    }
}
class SingleIconStyle extends ViewPU {
    constructor(r1, s1, t1, u1 = -1, v1 = undefined, w1) {
        super(r1, t1, u1, w1);
        if (typeof v1 === "function") {
            this.paramsGenerator_ = v1;
        }
        this.__bgColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "bgColor");
        this.__isFocus = new ObservedPropertySimplePU(false, this, "isFocus");
        this.item = null;
        this.focusBorderWidth = BORDER_WIDTH;
        this.setInitiallyProvidedValue(s1);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(q1) {
        if (q1.bgColor !== undefined) {
            this.bgColor = q1.bgColor;
        }
        if (q1.isFocus !== undefined) {
            this.isFocus = q1.isFocus;
        }
        if (q1.item !== undefined) {
            this.item = q1.item;
        }
        if (q1.focusBorderWidth !== undefined) {
            this.focusBorderWidth = q1.focusBorderWidth;
        }
    }
    updateStateVars(p1) {
    }
    purgeVariableDependenciesOnElmtId(o1) {
        this.__bgColor.purgeDependencyOnElmtId(o1);
        this.__isFocus.purgeDependencyOnElmtId(o1);
    }
    aboutToBeDeleted() {
        this.__bgColor.aboutToBeDeleted();
        this.__isFocus.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get bgColor() {
        return this.__bgColor.get();
    }
    set bgColor(n1) {
        this.__bgColor.set(n1);
    }
    get isFocus() {
        return this.__isFocus.get();
    }
    set isFocus(m1) {
        this.__isFocus.set(m1);
    }
    initialRender() {
        this.observeComponentCreation2((z, a1) => {
            If.create();
            if (this.item && this.item.iconOptions) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((e1, f1) => {
                        Row.create();
                        Row.focusable(true);
                        Row.width(BUTTON_SIZE);
                        Row.height(BUTTON_SIZE);
                        Row.margin({
                            bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                        });
                        Row.justifyContent(FlexAlign.Center);
                        Row.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Row.backgroundColor(ObservedObject.GetRawObject(this.bgColor));
                        ViewStackProcessor.visualState("focused");
                        Row.border({
                            radius: { "id": -1, "type": 10002, params: ['sys.float.corner_radius_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                            width: this.focusBorderWidth,
                            color: { "id": -1, "type": 10001, params: ['sys.color.interactive_focus'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                            style: BorderStyle.Solid,
                        });
                        Row.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.interactive_focus'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        ViewStackProcessor.visualState("pressed");
                        Row.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        ViewStackProcessor.visualState("disabled");
                        Row.opacity({ "id": -1, "type": 10002, params: ['sys.float.interactive_disable'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        ViewStackProcessor.visualState();
                        Row.onTouch((l1) => {
                            if (l1.type === TouchType.Down) {
                                if (this.item?.action) {
                                    this.item?.action();
                                }
                                this.bgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                            if (l1.type === TouchType.Up) {
                                this.bgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                        });
                        Row.onHover((k1) => {
                            if (k1) {
                                this.bgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                            else {
                                this.bgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                        });
                        Row.onKeyEvent((j1) => {
                            if (j1.keyCode === KeyCode.KEYCODE_ENTER || j1.keyCode === KeyCode.KEYCODE_SPACE) {
                                if (this.item?.action) {
                                    this.item?.action();
                                }
                            }
                        });
                    }, Row);
                    this.IconZone.bind(this)();
                    Row.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }
    IconZone(h = null) {
        this.observeComponentCreation2((j, k) => {
            If.create();
            if (this.item && this.item.iconOptions) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((o, p) => {
                        If.create();
                        if (Util.isSymbolResource(this.item.iconOptions.icon)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((w, x) => {
                                    SymbolGlyph.create(this.item.iconOptions?.icon);
                                    SymbolGlyph.focusable(true);
                                    SymbolGlyph.fontSize(this.item.iconOptions?.symbolicIconOption?.fontSize ?? IMAGE_HEIGHT_NUM);
                                    SymbolGlyph.fontColor(this.item.iconOptions?.symbolicIconOption?.fontColor ?? [{ "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
                                    SymbolGlyph.fontWeight(this.item.iconOptions?.symbolicIconOption?.fontWeight);
                                    SymbolGlyph.renderingStrategy(this.item.iconOptions?.symbolicIconOption?.renderingStrategy);
                                    SymbolGlyph.effectStrategy(this.item.iconOptions?.symbolicIconOption?.effectStrategy);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((s, t) => {
                                    Image.create(this.item?.iconOptions?.icon);
                                    Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                                    Image.width(IMAGE_HEIGHT_NUM);
                                    Image.height(IMAGE_HEIGHT_NUM);
                                    Image.focusable(true);
                                    Image.draggable(false);
                                }, Image);
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
    rerender() {
        this.updateDirtyElements();
    }
}
class Util {
    static isSymbolResource(f) {
        if (!Util.isResourceType(f)) {
            return false;
        }
        let g = f;
        return g.type === RESOURCE_TYPE_SYMBOL;
    }
    static isResourceType(e) {
        if (!e) {
            return false;
        }
        if (typeof e === 'string' || typeof e === 'undefined') {
            return false;
        }
        return true;
    }
}
function getNumberByResource(a) {
    try {
        return resourceManager.getSystemResourceManager().getNumberByName(a);
    }
    catch (b) {
        let c = b.code;
        let d = b.message;
        hilog.error(0x3900, 'Ace', `CustomContentDialog getNumberByResource error, code: ${c}, message: ${d}`);
        return 0;
    }
}


export default { OperationType, SubHeader };