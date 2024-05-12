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

if (!("finalizeConstruction" in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;
const TextModifier = requireNapi('arkui.modifier').TextModifier;
const INDEX_ZERO = 0;
const INDEX_ONE = 1;
const INDEX_TWO = 2;
const SINGLE_LINE_NUM = 1;
const DOUBLE_LINE_NUM = 2;
const SINGLE_LINE_HEIGHT = 56;
const DOUBLE_LINE_HEIGHT = 72;
const BORDER_WIDTH = 2;
const RESOURCE_TYPE_SYMBOL = 40000;
const LEFT_ICON_SIZE = 16;
const BUTTON_ZONE_SIZE = 32;
const BUTTON_HEIGHT = 28;
const ARROW_ICON_WIDTH = 12;
const ARROW_ICON_HEIGHT = 24;
const SINGLE_ICON_ZONE_SIZE = 32;
const RIGHT_SINGLE_ICON_SIZE = 24;
const LOADING_SIZE = 24;
const PADDING_LEVEL_2 = 4;
const MAX_RIGHT_WIDTH = '34%';
export var OperationType;
(function (c12) {
  c12[c12["TEXT_ARROW"] = 0] = "TEXT_ARROW";
  c12[c12["BUTTON"] = 1] = "BUTTON";
  c12[c12["ICON_GROUP"] = 2] = "ICON_GROUP";
  c12[c12["LOADING"] = 3] = "LOADING";
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
function __Text__secondaryTitleStyles(b12) {
  Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.Subtitle_S'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
  Text.fontColor(b12?.fontColor ?? { "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
  Text.fontWeight(b12?.fontWeight);
  Text.maxLines(b12?.maxLines);
  Text.textOverflow({ overflow: TextOverflow.Ellipsis });
  Text.align(b12?.alignment);
}
function __Text__primaryTitleStyles(a12) {
  Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.Subtitle_L'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
  Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
  Text.fontWeight(a12?.fontWeight);
  Text.maxLines(a12?.maxLines);
  Text.textOverflow({ overflow: TextOverflow.Ellipsis });
  Text.align(a12?.alignment);
}
export class SubHeader extends ViewPU {
  constructor(u11, v11, w11, x11 = -1, y11 = undefined, z11) {
    super(u11, w11, x11, z11);
    if (typeof y11 === "function") {
      this.paramsGenerator_ = y11;
    }
    this.__icon = new SynchedPropertyObjectOneWayPU(v11.icon, this, "icon");
    this.iconSymbolOptions = null;
    this.__primaryTitle = new SynchedPropertyObjectOneWayPU(v11.primaryTitle, this, "primaryTitle");
    this.__primaryTitleModifier = new ObservedPropertyObjectPU(new TextModifier(), this, "primaryTitleModifier");
    this.__secondaryTitle = new SynchedPropertyObjectOneWayPU(v11.secondaryTitle, this, "secondaryTitle");
    this.__secondaryTitleModifier = new ObservedPropertyObjectPU(new TextModifier(), this, "secondaryTitleModifier");
    this.select = null;
    this.__operationType = new SynchedPropertySimpleOneWayPU(v11.operationType, this, "operationType");
    this.operationItem = null;
    this.operationSymbolOptions = null;
    this.__isDuplicateLine = new ObservedPropertySimplePU(false, this, "isDuplicateLine");
    this.__textArrowBgColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "textArrowBgColor");
    this.__buttonBgColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "buttonBgColor");
    this.__textArrowFocus = new ObservedPropertySimplePU(false, this, "textArrowFocus");
    this.__buttonFocus = new ObservedPropertySimplePU(false, this, "buttonFocus");
    this.__textArrowStyleWidth = new ObservedPropertySimplePU(0, this, "textArrowStyleWidth");
    this.__textArrowStyleHeight = new ObservedPropertySimplePU(0, this, "textArrowStyleHeight");
    this.__buttonStyleWidth = new ObservedPropertySimplePU(0, this, "buttonStyleWidth");
    this.__buttonStyleHeight = new ObservedPropertySimplePU(0, this, "buttonStyleHeight");
    this.__iconWidth = new ObservedPropertySimplePU(0, this, "iconWidth");
    this.__selectedIndex = new ObservedPropertyObjectPU(-1, this, "selectedIndex");
    this.__selectValue = new ObservedPropertyObjectPU('', this, "selectValue");
    this.__flexAlign = new ObservedPropertySimplePU(FlexAlign.SpaceBetween, this, "flexAlign");
    this.titleBuilder = undefined;
    this.__contentMargin = new SynchedPropertyObjectOneWayPU(v11.contentMargin, this, "contentMargin");
    this.setInitiallyProvidedValue(v11);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(t11) {
    if (t11.icon === undefined) {
      this.__icon.set(null);
    }
    if (t11.iconSymbolOptions !== undefined) {
      this.iconSymbolOptions = t11.iconSymbolOptions;
    }
    if (t11.primaryTitle === undefined) {
      this.__primaryTitle.set(null);
    }
    if (t11.primaryTitleModifier !== undefined) {
      this.primaryTitleModifier = t11.primaryTitleModifier;
    }
    if (t11.secondaryTitle === undefined) {
      this.__secondaryTitle.set(null);
    }
    if (t11.secondaryTitleModifier !== undefined) {
      this.secondaryTitleModifier = t11.secondaryTitleModifier;
    }
    if (t11.select !== undefined) {
      this.select = t11.select;
    }
    if (t11.operationType === undefined) {
      this.__operationType.set(OperationType.BUTTON);
    }
    if (t11.operationItem !== undefined) {
      this.operationItem = t11.operationItem;
    }
    if (t11.operationSymbolOptions !== undefined) {
      this.operationSymbolOptions = t11.operationSymbolOptions;
    }
    if (t11.isDuplicateLine !== undefined) {
      this.isDuplicateLine = t11.isDuplicateLine;
    }
    if (t11.textArrowBgColor !== undefined) {
      this.textArrowBgColor = t11.textArrowBgColor;
    }
    if (t11.buttonBgColor !== undefined) {
      this.buttonBgColor = t11.buttonBgColor;
    }
    if (t11.textArrowFocus !== undefined) {
      this.textArrowFocus = t11.textArrowFocus;
    }
    if (t11.buttonFocus !== undefined) {
      this.buttonFocus = t11.buttonFocus;
    }
    if (t11.textArrowStyleWidth !== undefined) {
      this.textArrowStyleWidth = t11.textArrowStyleWidth;
    }
    if (t11.textArrowStyleHeight !== undefined) {
      this.textArrowStyleHeight = t11.textArrowStyleHeight;
    }
    if (t11.buttonStyleWidth !== undefined) {
      this.buttonStyleWidth = t11.buttonStyleWidth;
    }
    if (t11.buttonStyleHeight !== undefined) {
      this.buttonStyleHeight = t11.buttonStyleHeight;
    }
    if (t11.iconWidth !== undefined) {
      this.iconWidth = t11.iconWidth;
    }
    if (t11.selectedIndex !== undefined) {
      this.selectedIndex = t11.selectedIndex;
    }
    if (t11.selectValue !== undefined) {
      this.selectValue = t11.selectValue;
    }
    if (t11.flexAlign !== undefined) {
      this.flexAlign = t11.flexAlign;
    }
    if (t11.titleBuilder !== undefined) {
      this.titleBuilder = t11.titleBuilder;
    }
  }
  updateStateVars(s11) {
    this.__icon.reset(s11.icon);
    this.__primaryTitle.reset(s11.primaryTitle);
    this.__secondaryTitle.reset(s11.secondaryTitle);
    this.__operationType.reset(s11.operationType);
    this.__contentMargin.reset(s11.contentMargin);
  }
  purgeVariableDependenciesOnElmtId(r11) {
    this.__icon.purgeDependencyOnElmtId(r11);
    this.__primaryTitle.purgeDependencyOnElmtId(r11);
    this.__primaryTitleModifier.purgeDependencyOnElmtId(r11);
    this.__secondaryTitle.purgeDependencyOnElmtId(r11);
    this.__secondaryTitleModifier.purgeDependencyOnElmtId(r11);
    this.__operationType.purgeDependencyOnElmtId(r11);
    this.__isDuplicateLine.purgeDependencyOnElmtId(r11);
    this.__textArrowBgColor.purgeDependencyOnElmtId(r11);
    this.__buttonBgColor.purgeDependencyOnElmtId(r11);
    this.__textArrowFocus.purgeDependencyOnElmtId(r11);
    this.__buttonFocus.purgeDependencyOnElmtId(r11);
    this.__textArrowStyleWidth.purgeDependencyOnElmtId(r11);
    this.__textArrowStyleHeight.purgeDependencyOnElmtId(r11);
    this.__buttonStyleWidth.purgeDependencyOnElmtId(r11);
    this.__buttonStyleHeight.purgeDependencyOnElmtId(r11);
    this.__iconWidth.purgeDependencyOnElmtId(r11);
    this.__selectedIndex.purgeDependencyOnElmtId(r11);
    this.__selectValue.purgeDependencyOnElmtId(r11);
    this.__flexAlign.purgeDependencyOnElmtId(r11);
    this.__contentMargin.purgeDependencyOnElmtId(r11);
  }
  aboutToBeDeleted() {
    this.__icon.aboutToBeDeleted();
    this.__primaryTitle.aboutToBeDeleted();
    this.__primaryTitleModifier.aboutToBeDeleted();
    this.__secondaryTitle.aboutToBeDeleted();
    this.__secondaryTitleModifier.aboutToBeDeleted();
    this.__operationType.aboutToBeDeleted();
    this.__isDuplicateLine.aboutToBeDeleted();
    this.__textArrowBgColor.aboutToBeDeleted();
    this.__buttonBgColor.aboutToBeDeleted();
    this.__textArrowFocus.aboutToBeDeleted();
    this.__buttonFocus.aboutToBeDeleted();
    this.__textArrowStyleWidth.aboutToBeDeleted();
    this.__textArrowStyleHeight.aboutToBeDeleted();
    this.__buttonStyleWidth.aboutToBeDeleted();
    this.__buttonStyleHeight.aboutToBeDeleted();
    this.__iconWidth.aboutToBeDeleted();
    this.__selectedIndex.aboutToBeDeleted();
    this.__selectValue.aboutToBeDeleted();
    this.__flexAlign.aboutToBeDeleted();
    this.__contentMargin.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get icon() {
    return this.__icon.get();
  }
  set icon(q11) {
    this.__icon.set(q11);
  }
  get primaryTitle() {
    return this.__primaryTitle.get();
  }
  set primaryTitle(p11) {
    this.__primaryTitle.set(p11);
  }
  get primaryTitleModifier() {
    return this.__primaryTitleModifier.get();
  }
  set primaryTitleModifier(o11) {
    this.__primaryTitleModifier.set(o11);
  }
  get secondaryTitle() {
    return this.__secondaryTitle.get();
  }
  set secondaryTitle(n11) {
    this.__secondaryTitle.set(n11);
  }
  get secondaryTitleModifier() {
    return this.__secondaryTitleModifier.get();
  }
  set secondaryTitleModifier(m11) {
    this.__secondaryTitleModifier.set(m11);
  }
  get operationType() {
    return this.__operationType.get();
  }
  set operationType(l11) {
    this.__operationType.set(l11);
  }
  get isDuplicateLine() {
    return this.__isDuplicateLine.get();
  }
  set isDuplicateLine(k11) {
    this.__isDuplicateLine.set(k11);
  }
  get textArrowBgColor() {
    return this.__textArrowBgColor.get();
  }
  set textArrowBgColor(j11) {
    this.__textArrowBgColor.set(j11);
  }
  get buttonBgColor() {
    return this.__buttonBgColor.get();
  }
  set buttonBgColor(i11) {
    this.__buttonBgColor.set(i11);
  }
  get textArrowFocus() {
    return this.__textArrowFocus.get();
  }
  set textArrowFocus(h11) {
    this.__textArrowFocus.set(h11);
  }
  get buttonFocus() {
    return this.__buttonFocus.get();
  }
  set buttonFocus(g11) {
    this.__buttonFocus.set(g11);
  }
  get textArrowStyleWidth() {
    return this.__textArrowStyleWidth.get();
  }
  set textArrowStyleWidth(f11) {
    this.__textArrowStyleWidth.set(f11);
  }
  get textArrowStyleHeight() {
    return this.__textArrowStyleHeight.get();
  }
  set textArrowStyleHeight(e11) {
    this.__textArrowStyleHeight.set(e11);
  }
  get buttonStyleWidth() {
    return this.__buttonStyleWidth.get();
  }
  set buttonStyleWidth(d11) {
    this.__buttonStyleWidth.set(d11);
  }
  get buttonStyleHeight() {
    return this.__buttonStyleHeight.get();
  }
  set buttonStyleHeight(c11) {
    this.__buttonStyleHeight.set(c11);
  }
  get iconWidth() {
    return this.__iconWidth.get();
  }
  set iconWidth(b11) {
    this.__iconWidth.set(b11);
  }
  get selectedIndex() {
    return this.__selectedIndex.get();
  }
  set selectedIndex(a11) {
    this.__selectedIndex.set(a11);
  }
  get selectValue() {
    return this.__selectValue.get();
  }
  set selectValue(z10) {
    this.__selectValue.set(z10);
  }
  get flexAlign() {
    return this.__flexAlign.get();
  }
  set flexAlign(y10) {
    this.__flexAlign.set(y10);
  }
  get contentMargin() {
    return this.__contentMargin.get();
  }
  set contentMargin(x10) {
    this.__contentMargin.set(x10);
  }
  initialRender() {
    this.observeComponentCreation2((v10, w10) => {
      Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.End });
      Flex.width('100%');
      Flex.focusable(true);
      Flex.constraintSize({ minHeight: this.isDuplicateLine ? DOUBLE_LINE_HEIGHT : SINGLE_LINE_HEIGHT });
    }, Flex);
    this.observeComponentCreation2((t10, u10) => {
      Row.create();
      Row.width('100%');
      Row.margin({
        left: this.contentMargin?.left ?? { "id": -1, "type": 10002, params: ['sys.float.margin_left'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        right: this.getMarginRight()
      });
      Row.flexShrink(1);
    }, Row);
    this.leftArea.bind(this)();
    Row.pop();
    this.observeComponentCreation2((r10, s10) => {
      Row.create();
      Row.justifyContent(FlexAlign.End);
      Row.constraintSize({ maxWidth: this.getMaxWidth() });
      Row.flexShrink(0);
    }, Row);
    this.rightArea.bind(this)();
    Row.pop();
    Flex.pop();
  }
  getMarginRight() {
    if (this.operationType === OperationType.LOADING || (this.operationItem && this.operationItem.length > 0)) {
      return { "id": -1, "type": 10002, params: ['sys.float.padding_level0'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    }
    return this.contentMargin?.right ?? { "id": -1, "type": 10002, params: ['sys.float.margin_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
  }
  getMaxWidth() {
    if (this.operationType === OperationType.ICON_GROUP && (this.operationItem && this.operationItem.length > 0)) {
      return '100%';
    }
    else {
      return MAX_RIGHT_WIDTH;
    }
  }
  leftArea(d10 = null) {
    this.observeComponentCreation2((f10, g10) => {
      If.create();
      if (this.titleBuilder) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.titleBuilder.bind(this)();
        });
      }
      else if (this.secondaryTitle && this.icon) {
        this.ifElseBranchUpdateFunction(1, () => {
          this.IconSecondaryTitleStyle.bind(this)(makeBuilderParameterProxy("IconSecondaryTitleStyle", { content: () => (this["__secondaryTitle"] ? this["__secondaryTitle"] : this["secondaryTitle"]), iconOptions: () => ({
            icon: this.icon,
            symbolicIconOption: this.iconSymbolOptions,
          }) }));
        });
      }
      else if (this.secondaryTitle && this.primaryTitle) {
        this.ifElseBranchUpdateFunction(2, () => {
          this.SubTitleStyle.bind(this)(makeBuilderParameterProxy("SubTitleStyle", { content: () => (this["__primaryTitle"] ? this["__primaryTitle"] : this["primaryTitle"]), subContent: () => (this["__secondaryTitle"] ? this["__secondaryTitle"] : this["secondaryTitle"]) }));
        });
      }
      else if (this.secondaryTitle) {
        this.ifElseBranchUpdateFunction(3, () => {
          this.SecondTitleStyle.bind(this)(makeBuilderParameterProxy("SecondTitleStyle", { content: () => (this["__secondaryTitle"] ? this["__secondaryTitle"] : this["secondaryTitle"]) }));
        });
      }
      else if (this.select) {
        this.ifElseBranchUpdateFunction(4, () => {
          this.SelectStyle.bind(this)(this.select);
        });
      }
      else if (this.primaryTitle) {
        this.ifElseBranchUpdateFunction(5, () => {
          this.PrimaryTitleStyle.bind(this)(makeBuilderParameterProxy("PrimaryTitleStyle", { content: () => (this["__primaryTitle"] ? this["__primaryTitle"] : this["primaryTitle"]) }));
        });
      }
      else {
        this.ifElseBranchUpdateFunction(6, () => {
          this.dummyFunction.bind(this)();
        });
      }
    }, If);
    If.pop();
  }
  rightArea(i9 = null) {
    this.observeComponentCreation2((z9, a10) => {
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
    this.observeComponentCreation2((v9, w9) => {
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
    this.observeComponentCreation2((r9, s9) => {
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
    this.observeComponentCreation2((n9, o9) => {
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
  IconSecondaryTitleStyle(o8, p8 = null) {
    this.observeComponentCreation2((f9, g9) => {
      Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.Center });
      Flex.padding({
        left: { "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        right: { "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        top: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
      });
      Flex.onAppear(() => {
        this.isDuplicateLine = false;
        this.changeFlexAlign(FlexAlign.SpaceBetween);
      });
    }, Flex);
    this.observeComponentCreation2((v8, w8) => {
      If.create();
      if (Util.isSymbolResource(o8.iconOptions?.icon)) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((d9, e9) => {
            SymbolGlyph.create(o8.iconOptions?.icon);
            SymbolGlyph.focusable(true);
            SymbolGlyph.fontSize(o8.iconOptions?.symbolicIconOption?.fontSize ?? LEFT_ICON_SIZE);
            SymbolGlyph.fontColor(o8.iconOptions?.symbolicIconOption?.fontColor ?? [{ "id": -1, "type": 10001, params: ['sys.color.icon_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
            SymbolGlyph.fontWeight(o8.iconOptions?.symbolicIconOption?.fontWeight);
            SymbolGlyph.renderingStrategy(o8.iconOptions?.symbolicIconOption?.renderingStrategy);
            SymbolGlyph.effectStrategy(o8.iconOptions?.symbolicIconOption?.effectStrategy);
            SymbolGlyph.margin({ right: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } });
            SymbolGlyph.flexShrink(0);
          }, SymbolGlyph);
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((z8, a9) => {
            Image.create(o8.iconOptions?.icon);
            Image.width(LEFT_ICON_SIZE);
            Image.height(LEFT_ICON_SIZE);
            Image.margin({ right: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } });
            Image.draggable(false);
            Image.flexShrink(0);
          }, Image);
        });
      }
    }, If);
    If.pop();
    this.observeComponentCreation2((t8, u8) => {
      Text.create(o8.content);
      __Text__secondaryTitleStyles({
        maxLines: DOUBLE_LINE_NUM,
        fontWeight: FontWeight.Medium,
        alignment: Alignment.Start,
      });
      Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.secondaryTitleModifier));
      Text.flexShrink(1);
    }, Text);
    Text.pop();
    Flex.pop();
  }
  SubTitleStyle(c8, d8 = null) {
    this.observeComponentCreation2((l8, m8) => {
      Column.create();
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
    this.observeComponentCreation2((j8, k8) => {
      Text.create(c8.content);
      __Text__primaryTitleStyles({
        fontWeight: FontWeight.Bold,
        maxLines: SINGLE_LINE_NUM,
        alignment: Alignment.Start,
      });
      Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.primaryTitleModifier));
      Text.width('100%');
    }, Text);
    Text.pop();
    this.observeComponentCreation2((h8, i8) => {
      Text.create(c8.subContent);
      __Text__secondaryTitleStyles({
        maxLines: SINGLE_LINE_NUM,
        fontWeight: FontWeight.Regular,
        alignment: Alignment.Start,
      });
      Text.width('100%');
      Text.margin({
        top: { "id": -1, "type": 10002, params: ['sys.float.padding_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
      });
      Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.secondaryTitleModifier));
    }, Text);
    Text.pop();
    Column.pop();
  }
  SecondTitleStyle(t7, u7 = null) {
    this.observeComponentCreation2((a8, b8) => {
      Column.create();
      Column.alignItems(HorizontalAlign.Start);
      Column.padding({
        left: { "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        right: { "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        top: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
      });
    }, Column);
    this.observeComponentCreation2((x7, y7) => {
      Text.create(t7.content);
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
      Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.secondaryTitleModifier));
    }, Text);
    Text.pop();
    Column.pop();
  }
  SelectStyle(h7, i7 = null) {
    this.observeComponentCreation2((q7, r7) => {
      Column.create();
      Column.alignItems(HorizontalAlign.Start);
      Column.onAppear(() => {
        this.isDuplicateLine = false;
        this.changeFlexAlign(FlexAlign.SpaceBetween);
      });
    }, Column);
    this.observeComponentCreation2((l7, m7) => {
      Select.create(h7.options);
      Select.selected(ObservedObject.GetRawObject(this.selectedIndex));
      Select.value(ObservedObject.GetRawObject(this.selectValue));
      Select.onSelect((o7, p7) => {
        this.selectedIndex = o7;
        if (p7) {
          this.selectValue = p7;
        }
        if (h7.onSelect) {
          h7.onSelect(o7, p7);
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
  PrimaryTitleStyle(y6, z6 = null) {
    this.observeComponentCreation2((f7, g7) => {
      Column.create();
      Column.alignItems(HorizontalAlign.Start);
      Column.padding({
        left: { "id": -1, "type": 10002, params: ['sys.float.padding_level0'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        right: { "id": -1, "type": 10002, params: ['sys.float.padding_level0'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        top: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
      });
    }, Column);
    this.observeComponentCreation2((c7, d7) => {
      Text.create(y6.content);
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
      Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.primaryTitleModifier));
    }, Text);
    Text.pop();
    Column.pop();
  }
  ButtonStyle(k5, l5 = null) {
    this.observeComponentCreation2((w6, x6) => {
      Row.create();
      Row.margin({
        left: { "id": -1, "type": 10002, params: ['sys.float.padding_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        right: { "id": -1, "type": 10002, params: ['sys.float.padding_level5'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
      });
      Row.justifyContent(FlexAlign.End);
      Row.focusable(true);
    }, Row);
    this.observeComponentCreation2((u6, v6) => {
      Stack.create();
      Stack.focusable(true);
    }, Stack);
    this.observeComponentCreation2((x5, y5) => {
      If.create();
      if (k5) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((f6, g6) => {
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
            Row.onFocus(() => {
              this.buttonFocus = true;
            });
            Row.onBlur(() => {
              this.buttonFocus = false;
            });
            Row.onHover((t6) => {
              if (t6) {
                this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
              }
              else {
                this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
              }
            });
            Row.onTouch((s6) => {
              if (s6.type === TouchType.Down) {
                this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
              }
              if (s6.type === TouchType.Up) {
                this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
              }
            });
            Row.onKeyEvent((r6) => {
              if (r6.keyCode === KeyCode.KEYCODE_ENTER || r6.keyCode === KeyCode.KEYCODE_SPACE) {
                if (k5.action) {
                  k5.action();
                }
              }
            });
            Row.onClick((q6) => {
              if (k5.action) {
                k5.action();
              }
            });
            Row.onAreaChange((o6, p6) => {
              this.buttonStyleWidth = Number(p6.width);
              this.buttonStyleHeight = Number(p6.height);
            });
          }, Row);
          this.observeComponentCreation2((d6, e6) => {
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
    this.observeComponentCreation2((q5, r5) => {
      If.create();
      if (this.buttonFocus) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((v5, w5) => {
            Row.create();
            Row.height(BUTTON_HEIGHT);
            Row.width(this.buttonStyleWidth);
            Row.hitTestBehavior(HitTestMode.None);
            Row.border({
              width: BORDER_WIDTH,
              color: { "id": -1, "type": 10001, params: ['sys.color.interactive_focus'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
            });
            Row.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
          }, Row);
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
  TextArrowStyle(y3, z3 = null) {
    this.observeComponentCreation2((a5, b5) => {
      Row.create();
      Row.onHover((j5) => {
        if (j5) {
          this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        }
        else {
          this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        }
      });
      Row.onTouch((i5) => {
        if (i5.type === TouchType.Down) {
          this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        }
        if (i5.type === TouchType.Up) {
          this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        }
      });
      Row.onKeyEvent((h5) => {
        if (h5.keyCode === KeyCode.KEYCODE_ENTER || h5.keyCode === KeyCode.KEYCODE_SPACE) {
          if (y3.action) {
            y3.action();
          }
        }
      });
      Row.onClick((g5) => {
        if (y3.action) {
          y3.action();
        }
      });
      Row.focusable(true);
      Row.justifyContent(FlexAlign.End);
      Row.margin({
        left: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        right: this.contentMargin?.right ?? { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
      });
    }, Row);
    this.observeComponentCreation2((y4, z4) => {
      Stack.create();
    }, Stack);
    this.observeComponentCreation2((r4, s4) => {
      Row.create();
      Row.alignItems(VerticalAlign.Center);
      Row.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Row.focusable(true);
      Row.backgroundColor(ObservedObject.GetRawObject(this.textArrowBgColor));
      Row.constraintSize({ minHeight: BUTTON_ZONE_SIZE });
      Row.onFocus(() => {
        this.textArrowFocus = true;
      });
      Row.onBlur(() => {
        this.textArrowFocus = false;
      });
      Row.padding({
        left: { "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        right: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
      });
      Row.onAreaChange((w4, x4) => {
        this.textArrowStyleWidth = Number(x4.width);
        this.textArrowStyleHeight = Number(x4.height);
      });
    }, Row);
    this.observeComponentCreation2((k4, l4) => {
      If.create();
      if (y3) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((p4, q4) => {
            Text.create(y3.value);
            __Text__secondaryTitleStyles({
              maxLines: SINGLE_LINE_NUM,
              fontWeight: FontWeight.Regular,
              alignment: Alignment.End,
            });
            Text.margin({
              right: { "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
              top: PADDING_LEVEL_2 + ARROW_ICON_WIDTH,
              bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            });
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
    Row.pop();
    this.observeComponentCreation2((i4, j4) => {
      Row.create();
      Row.justifyContent(FlexAlign.End);
      Row.height(this.textArrowStyleHeight);
      Row.width(this.textArrowStyleWidth);
      Row.hitTestBehavior(HitTestMode.None);
      Row.padding({ right: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } });
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
    this.observeComponentCreation2((g4, h4) => {
      Image.create({ "id": -1, "type": 20000, params: ['sys.media.ohos_ic_public_arrow_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_tertiary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Image.width(ARROW_ICON_WIDTH);
      Image.height(ARROW_ICON_HEIGHT);
      Image.focusable(true);
      Image.draggable(false);
    }, Image);
    Row.pop();
    Stack.pop();
    Row.pop();
  }
  IconGroupStyle(j2, k2 = null) {
    this.observeComponentCreation2((w3, x3) => {
      Row.create();
      Row.justifyContent(FlexAlign.End);
      Row.focusable(true);
      Row.margin({
        left: { "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        right: this.contentMargin?.right ?? { "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
      });
    }, Row);
    this.observeComponentCreation2((n2, o2) => {
      ForEach.create();
      const p2 = (r2, s2) => {
        const t2 = r2;
        this.observeComponentCreation2((v2, w2) => {
          If.create();
          if (Util.isResourceType(t2.value)) {
            this.ifElseBranchUpdateFunction(0, () => {
              this.observeComponentCreation2((a3, b3) => {
                If.create();
                if (s2 === INDEX_ZERO) {
                  this.ifElseBranchUpdateFunction(0, () => {
                    {
                      this.observeComponentCreation2((q3, r3) => {
                        if (r3) {
                          let s3 = new SingleIconStyle(this, {
                            item: {
                              iconOptions: {
                                icon: t2.value,
                                symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > s2 ?
                                this.operationSymbolOptions[s2] : null,
                              },
                              action: t2.action,
                            }
                          }, undefined, q3, () => { }, { page: "library/src/main/ets/components/mainpage/subheader.ets", line: 589, col: 13 });
                          ViewPU.create(s3);
                          let t3 = () => {
                            return {
                              item: {
                                iconOptions: {
                                  icon: t2.value,
                                  symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > s2 ?
                                  this.operationSymbolOptions[s2] : null,
                                },
                                action: t2.action,
                              }
                            };
                          };
                          s3.paramsGenerator_ = t3;
                        }
                        else {
                          this.updateStateVarsOfChildByElmtId(q3, {});
                        }
                      }, { name: "SingleIconStyle" });
                    }
                  });
                }
                else if (s2 === INDEX_ONE || s2 === INDEX_TWO) {
                  this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((m3, n3) => {
                      __Common__.create();
                      __Common__.margin({
                        left: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                      });
                    }, __Common__);
                    {
                      this.observeComponentCreation2((g3, h3) => {
                        if (h3) {
                          let i3 = new SingleIconStyle(this, {
                            item: {
                              action: t2.action,
                              iconOptions: {
                                icon: t2.value,
                                symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > s2 ?
                                this.operationSymbolOptions[s2] : null,
                              },
                            }
                          }, undefined, g3, () => { }, { page: "library/src/main/ets/components/mainpage/subheader.ets", line: 600, col: 13 });
                          ViewPU.create(i3);
                          let j3 = () => {
                            return {
                              item: {
                                action: t2.action,
                                iconOptions: {
                                  icon: t2.value,
                                  symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > s2 ?
                                  this.operationSymbolOptions[s2] : null,
                                },
                              }
                            };
                          };
                          i3.paramsGenerator_ = j3;
                        }
                        else {
                          this.updateStateVarsOfChildByElmtId(g3, {});
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
      this.forEachUpdateFunction(n2, j2, p2, undefined, true, false);
    }, ForEach);
    ForEach.pop();
    Row.pop();
  }
  LoadingProcessStyle(b2 = null) {
    this.observeComponentCreation2((h2, i2) => {
      Row.create();
      Row.focusable(true);
      Row.justifyContent(FlexAlign.End);
      Row.padding({
        top: { "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
      });
      Row.margin({
        left: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        right: this.contentMargin?.right ? this.contentMargin.right : { "id": -1, "type": 10002, params: ['sys.float.margin_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
      });
    }, Row);
    this.observeComponentCreation2((e2, f2) => {
      LoadingProgress.create();
      LoadingProgress.width(LOADING_SIZE);
      LoadingProgress.height(LOADING_SIZE);
      LoadingProgress.color({ "id": -1, "type": 10001, params: ['sys.color.icon_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      LoadingProgress.focusable(true);
      LoadingProgress.onAppear(() => {
        this.isDuplicateLine = false;
      });
    }, LoadingProgress);
    Row.pop();
  }
  dummyFunction(w1 = null) {
    this.observeComponentCreation2((y1, z1) => {
      Row.create();
      Row.onAppear(() => {
        this.changeFlexAlign(FlexAlign.End);
      });
    }, Row);
    Row.pop();
  }
  aboutToAppear() {
    if (this.select) {
      this.selectedIndex = this.select.selected;
      this.selectValue = this.select.value;
    }
  }
  changeFlexAlign(v1) {
    if (this.flexAlign === v1) {
      return;
    }
    this.flexAlign = v1;
  }
  rerender() {
    this.updateDirtyElements();
  }
}
class SingleIconStyle extends ViewPU {
  constructor(p1, q1, r1, s1 = -1, t1 = undefined, u1) {
    super(p1, r1, s1, u1);
    if (typeof t1 === "function") {
      this.paramsGenerator_ = t1;
    }
    this.__bgColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "bgColor");
    this.__isFocus = new ObservedPropertySimplePU(false, this, "isFocus");
    this.item = null;
    this.setInitiallyProvidedValue(q1);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(o1) {
    if (o1.bgColor !== undefined) {
      this.bgColor = o1.bgColor;
    }
    if (o1.isFocus !== undefined) {
      this.isFocus = o1.isFocus;
    }
    if (o1.item !== undefined) {
      this.item = o1.item;
    }
  }
  updateStateVars(n1) {
  }
  purgeVariableDependenciesOnElmtId(m1) {
    this.__bgColor.purgeDependencyOnElmtId(m1);
    this.__isFocus.purgeDependencyOnElmtId(m1);
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
  set bgColor(l1) {
    this.__bgColor.set(l1);
  }
  get isFocus() {
    return this.__isFocus.get();
  }
  set isFocus(k1) {
    this.__isFocus.set(k1);
  }
  initialRender() {
    this.observeComponentCreation2((v, w) => {
      If.create();
      if (this.item && this.item.iconOptions) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((a1, b1) => {
            Row.create();
            Row.focusable(true);
            Row.width(SINGLE_ICON_ZONE_SIZE);
            Row.height(SINGLE_ICON_ZONE_SIZE);
            Row.margin({
              bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            });
            Row.justifyContent(FlexAlign.Center);
            Row.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Row.backgroundColor(ObservedObject.GetRawObject(this.bgColor));
            ViewStackProcessor.visualState("normal");
            Row.border({ width: 0 });
            Row.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            ViewStackProcessor.visualState("focused");
            Row.border({
              radius: { "id": -1, "type": 10002, params: ['sys.float.corner_radius_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
              width: BORDER_WIDTH,
              color: { "id": -1, "type": 10001, params: ['sys.color.interactive_focus'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
              style: BorderStyle.Solid,
            });
            ViewStackProcessor.visualState("pressed");
            Row.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            ViewStackProcessor.visualState("disabled");
            Row.opacity({ "id": -1, "type": 10002, params: ['sys.float.interactive_disable'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            ViewStackProcessor.visualState();
            Row.onTouch((j1) => {
              if (j1.type === TouchType.Down) {
                this.bgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
              }
              if (j1.type === TouchType.Up) {
                this.bgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
              }
            });
            Row.onHover((i1) => {
              if (i1) {
                this.bgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
              }
              else {
                this.bgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
              }
            });
            Row.onKeyEvent((h1) => {
              if (h1.keyCode === KeyCode.KEYCODE_ENTER || h1.keyCode === KeyCode.KEYCODE_SPACE) {
                if (this.item?.action) {
                  this.item?.action();
                }
              }
            });
            Row.onClick((g1) => {
              if (this.item?.action) {
                this.item?.action();
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
  IconZone(d = null) {
    this.observeComponentCreation2((f, g) => {
      If.create();
      if (this.item && this.item.iconOptions) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((k, l) => {
            If.create();
            if (Util.isSymbolResource(this.item.iconOptions.icon)) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation2((s, t) => {
                  SymbolGlyph.create(this.item.iconOptions?.icon);
                  SymbolGlyph.focusable(true);
                  SymbolGlyph.fontSize(this.item.iconOptions?.symbolicIconOption?.fontSize ?? RIGHT_SINGLE_ICON_SIZE);
                  SymbolGlyph.fontColor(this.item.iconOptions?.symbolicIconOption?.fontColor ?? [{ "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
                  SymbolGlyph.fontWeight(this.item.iconOptions?.symbolicIconOption?.fontWeight);
                  SymbolGlyph.renderingStrategy(this.item.iconOptions?.symbolicIconOption?.renderingStrategy);
                  SymbolGlyph.effectStrategy(this.item.iconOptions?.symbolicIconOption?.effectStrategy);
                }, SymbolGlyph);
              });
            }
            else {
              this.ifElseBranchUpdateFunction(1, () => {
                this.observeComponentCreation2((o, p) => {
                  Image.create(this.item?.iconOptions?.icon);
                  Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                  Image.width(RIGHT_SINGLE_ICON_SIZE);
                  Image.height(RIGHT_SINGLE_ICON_SIZE);
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
  static isSymbolResource(b) {
    if (!Util.isResourceType(b)) {
      return false;
    }
    let c = b;
    return c.type === RESOURCE_TYPE_SYMBOL;
  }
  static isResourceType(a) {
    if (!a) {
      return false;
    }
    if (typeof a === 'string' || typeof a === 'undefined') {
      return false;
    }
    return true;
  }
}

export default { OperationType, SubHeader };