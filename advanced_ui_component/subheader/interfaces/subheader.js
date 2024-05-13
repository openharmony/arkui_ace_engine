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
(function (f12) {
  f12[f12["TEXT_ARROW"] = 0] = "TEXT_ARROW";
  f12[f12["BUTTON"] = 1] = "BUTTON";
  f12[f12["ICON_GROUP"] = 2] = "ICON_GROUP";
  f12[f12["LOADING"] = 3] = "LOADING";
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
class SubHeaderTheme {
  constructor() {
    this.fontPrimaryColor = { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.fontSecondaryColor = { "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.fontButtonColor = { "id": -1, "type": 10001, params: ['sys.color.font_emphasize'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.iconArrowColor = { "id": -1, "type": 10001, params: ['sys.color.icon_tertiary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.textArrowHoverBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.borderFocusColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_focus'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.leftIconColor = { "id": -1, "type": 10001, params: ['sys.color.icon_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.rightIconColor = { "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
  }
}
function __Text__secondaryTitleStyles(e12) {
  Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.Subtitle_S'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
  Text.fontColor(e12?.fontColor ?? { "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
  Text.fontWeight(e12?.fontWeight);
  Text.maxLines(e12?.maxLines);
  Text.textOverflow({ overflow: TextOverflow.Ellipsis });
  Text.align(e12?.alignment);
}
function __Text__primaryTitleStyles(d12) {
  Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.Subtitle_L'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
  Text.fontColor(d12?.fontColor ?? { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
  Text.fontWeight(d12?.fontWeight);
  Text.maxLines(d12?.maxLines);
  Text.textOverflow({ overflow: TextOverflow.Ellipsis });
  Text.align(d12?.alignment);
}
export class SubHeader extends ViewPU {
  constructor(x11, y11, z11, a12 = -1, b12 = undefined, c12) {
    super(x11, z11, a12, c12);
    if (typeof b12 === "function") {
      this.paramsGenerator_ = b12;
    }
    this.__icon = new SynchedPropertyObjectOneWayPU(y11.icon, this, "icon");
    this.iconSymbolOptions = null;
    this.__primaryTitle = new SynchedPropertyObjectOneWayPU(y11.primaryTitle, this, "primaryTitle");
    this.__primaryTitleModifier = new ObservedPropertyObjectPU(new TextModifier(), this, "primaryTitleModifier");
    this.__secondaryTitle = new SynchedPropertyObjectOneWayPU(y11.secondaryTitle, this, "secondaryTitle");
    this.__secondaryTitleModifier = new ObservedPropertyObjectPU(new TextModifier(), this, "secondaryTitleModifier");
    this.select = null;
    this.__operationType = new SynchedPropertySimpleOneWayPU(y11.operationType, this, "operationType");
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
    this.__contentMargin = new SynchedPropertyObjectOneWayPU(y11.contentMargin, this, "contentMargin");
    this.__subHeaderTheme = new ObservedPropertyObjectPU(new SubHeaderTheme(), this, "subHeaderTheme");
    this.addProvidedVar("subHeaderTheme", this.__subHeaderTheme, false);
    this.setInitiallyProvidedValue(y11);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(w11) {
    if (w11.icon === undefined) {
      this.__icon.set(null);
    }
    if (w11.iconSymbolOptions !== undefined) {
      this.iconSymbolOptions = w11.iconSymbolOptions;
    }
    if (w11.primaryTitle === undefined) {
      this.__primaryTitle.set(null);
    }
    if (w11.primaryTitleModifier !== undefined) {
      this.primaryTitleModifier = w11.primaryTitleModifier;
    }
    if (w11.secondaryTitle === undefined) {
      this.__secondaryTitle.set(null);
    }
    if (w11.secondaryTitleModifier !== undefined) {
      this.secondaryTitleModifier = w11.secondaryTitleModifier;
    }
    if (w11.select !== undefined) {
      this.select = w11.select;
    }
    if (w11.operationType === undefined) {
      this.__operationType.set(OperationType.BUTTON);
    }
    if (w11.operationItem !== undefined) {
      this.operationItem = w11.operationItem;
    }
    if (w11.operationSymbolOptions !== undefined) {
      this.operationSymbolOptions = w11.operationSymbolOptions;
    }
    if (w11.isDuplicateLine !== undefined) {
      this.isDuplicateLine = w11.isDuplicateLine;
    }
    if (w11.textArrowBgColor !== undefined) {
      this.textArrowBgColor = w11.textArrowBgColor;
    }
    if (w11.buttonBgColor !== undefined) {
      this.buttonBgColor = w11.buttonBgColor;
    }
    if (w11.textArrowFocus !== undefined) {
      this.textArrowFocus = w11.textArrowFocus;
    }
    if (w11.buttonFocus !== undefined) {
      this.buttonFocus = w11.buttonFocus;
    }
    if (w11.textArrowStyleWidth !== undefined) {
      this.textArrowStyleWidth = w11.textArrowStyleWidth;
    }
    if (w11.textArrowStyleHeight !== undefined) {
      this.textArrowStyleHeight = w11.textArrowStyleHeight;
    }
    if (w11.buttonStyleWidth !== undefined) {
      this.buttonStyleWidth = w11.buttonStyleWidth;
    }
    if (w11.buttonStyleHeight !== undefined) {
      this.buttonStyleHeight = w11.buttonStyleHeight;
    }
    if (w11.iconWidth !== undefined) {
      this.iconWidth = w11.iconWidth;
    }
    if (w11.selectedIndex !== undefined) {
      this.selectedIndex = w11.selectedIndex;
    }
    if (w11.selectValue !== undefined) {
      this.selectValue = w11.selectValue;
    }
    if (w11.flexAlign !== undefined) {
      this.flexAlign = w11.flexAlign;
    }
    if (w11.titleBuilder !== undefined) {
      this.titleBuilder = w11.titleBuilder;
    }
    if (w11.subHeaderTheme !== undefined) {
      this.subHeaderTheme = w11.subHeaderTheme;
    }
  }
  updateStateVars(v11) {
    this.__icon.reset(v11.icon);
    this.__primaryTitle.reset(v11.primaryTitle);
    this.__secondaryTitle.reset(v11.secondaryTitle);
    this.__operationType.reset(v11.operationType);
    this.__contentMargin.reset(v11.contentMargin);
  }
  purgeVariableDependenciesOnElmtId(u11) {
    this.__icon.purgeDependencyOnElmtId(u11);
    this.__primaryTitle.purgeDependencyOnElmtId(u11);
    this.__primaryTitleModifier.purgeDependencyOnElmtId(u11);
    this.__secondaryTitle.purgeDependencyOnElmtId(u11);
    this.__secondaryTitleModifier.purgeDependencyOnElmtId(u11);
    this.__operationType.purgeDependencyOnElmtId(u11);
    this.__isDuplicateLine.purgeDependencyOnElmtId(u11);
    this.__textArrowBgColor.purgeDependencyOnElmtId(u11);
    this.__buttonBgColor.purgeDependencyOnElmtId(u11);
    this.__textArrowFocus.purgeDependencyOnElmtId(u11);
    this.__buttonFocus.purgeDependencyOnElmtId(u11);
    this.__textArrowStyleWidth.purgeDependencyOnElmtId(u11);
    this.__textArrowStyleHeight.purgeDependencyOnElmtId(u11);
    this.__buttonStyleWidth.purgeDependencyOnElmtId(u11);
    this.__buttonStyleHeight.purgeDependencyOnElmtId(u11);
    this.__iconWidth.purgeDependencyOnElmtId(u11);
    this.__selectedIndex.purgeDependencyOnElmtId(u11);
    this.__selectValue.purgeDependencyOnElmtId(u11);
    this.__flexAlign.purgeDependencyOnElmtId(u11);
    this.__contentMargin.purgeDependencyOnElmtId(u11);
    this.__subHeaderTheme.purgeDependencyOnElmtId(u11);
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
    this.__subHeaderTheme.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get icon() {
    return this.__icon.get();
  }
  set icon(t11) {
    this.__icon.set(t11);
  }
  get primaryTitle() {
    return this.__primaryTitle.get();
  }
  set primaryTitle(s11) {
    this.__primaryTitle.set(s11);
  }
  get primaryTitleModifier() {
    return this.__primaryTitleModifier.get();
  }
  set primaryTitleModifier(r11) {
    this.__primaryTitleModifier.set(r11);
  }
  get secondaryTitle() {
    return this.__secondaryTitle.get();
  }
  set secondaryTitle(q11) {
    this.__secondaryTitle.set(q11);
  }
  get secondaryTitleModifier() {
    return this.__secondaryTitleModifier.get();
  }
  set secondaryTitleModifier(p11) {
    this.__secondaryTitleModifier.set(p11);
  }
  get operationType() {
    return this.__operationType.get();
  }
  set operationType(o11) {
    this.__operationType.set(o11);
  }
  get isDuplicateLine() {
    return this.__isDuplicateLine.get();
  }
  set isDuplicateLine(n11) {
    this.__isDuplicateLine.set(n11);
  }
  get textArrowBgColor() {
    return this.__textArrowBgColor.get();
  }
  set textArrowBgColor(m11) {
    this.__textArrowBgColor.set(m11);
  }
  get buttonBgColor() {
    return this.__buttonBgColor.get();
  }
  set buttonBgColor(l11) {
    this.__buttonBgColor.set(l11);
  }
  get textArrowFocus() {
    return this.__textArrowFocus.get();
  }
  set textArrowFocus(k11) {
    this.__textArrowFocus.set(k11);
  }
  get buttonFocus() {
    return this.__buttonFocus.get();
  }
  set buttonFocus(j11) {
    this.__buttonFocus.set(j11);
  }
  get textArrowStyleWidth() {
    return this.__textArrowStyleWidth.get();
  }
  set textArrowStyleWidth(i11) {
    this.__textArrowStyleWidth.set(i11);
  }
  get textArrowStyleHeight() {
    return this.__textArrowStyleHeight.get();
  }
  set textArrowStyleHeight(h11) {
    this.__textArrowStyleHeight.set(h11);
  }
  get buttonStyleWidth() {
    return this.__buttonStyleWidth.get();
  }
  set buttonStyleWidth(g11) {
    this.__buttonStyleWidth.set(g11);
  }
  get buttonStyleHeight() {
    return this.__buttonStyleHeight.get();
  }
  set buttonStyleHeight(f11) {
    this.__buttonStyleHeight.set(f11);
  }
  get iconWidth() {
    return this.__iconWidth.get();
  }
  set iconWidth(e11) {
    this.__iconWidth.set(e11);
  }
  get selectedIndex() {
    return this.__selectedIndex.get();
  }
  set selectedIndex(d11) {
    this.__selectedIndex.set(d11);
  }
  get selectValue() {
    return this.__selectValue.get();
  }
  set selectValue(c11) {
    this.__selectValue.set(c11);
  }
  get flexAlign() {
    return this.__flexAlign.get();
  }
  set flexAlign(b11) {
    this.__flexAlign.set(b11);
  }
  get contentMargin() {
    return this.__contentMargin.get();
  }
  set contentMargin(a11) {
    this.__contentMargin.set(a11);
  }
  get subHeaderTheme() {
    return this.__subHeaderTheme.get();
  }
  set subHeaderTheme(z10) {
    this.__subHeaderTheme.set(z10);
  }
  onWillApplyTheme(y10) {
    this.subHeaderTheme.fontPrimaryColor = y10.colors.fontPrimary;
    this.subHeaderTheme.fontSecondaryColor = y10.colors.fontSecondary;
    this.subHeaderTheme.fontButtonColor = y10.colors.fontEmphasize;
    this.subHeaderTheme.iconArrowColor = y10.colors.iconTertiary;
    this.subHeaderTheme.textArrowHoverBgColor = y10.colors.interactiveHover;
    this.subHeaderTheme.borderFocusColor = y10.colors.interactiveFocus;
    this.subHeaderTheme.leftIconColor = y10.colors.iconSecondary;
    this.subHeaderTheme.rightIconColor = y10.colors.iconPrimary;
  }
  initialRender() {
    this.observeComponentCreation2((w10, x10) => {
      Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.End });
      Flex.width('100%');
      Flex.focusable(true);
      Flex.constraintSize({ minHeight: this.isDuplicateLine ? DOUBLE_LINE_HEIGHT : SINGLE_LINE_HEIGHT });
    }, Flex);
    this.observeComponentCreation2((u10, v10) => {
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
    this.observeComponentCreation2((s10, t10) => {
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
  leftArea(e10 = null) {
    this.observeComponentCreation2((g10, h10) => {
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
  rightArea(j9 = null) {
    this.observeComponentCreation2((a10, b10) => {
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
    this.observeComponentCreation2((w9, x9) => {
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
    this.observeComponentCreation2((s9, t9) => {
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
    this.observeComponentCreation2((o9, p9) => {
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
  IconSecondaryTitleStyle(p8, q8 = null) {
    this.observeComponentCreation2((g9, h9) => {
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
    this.observeComponentCreation2((w8, x8) => {
      If.create();
      if (Util.isSymbolResource(p8.iconOptions?.icon)) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((e9, f9) => {
            SymbolGlyph.create(p8.iconOptions?.icon);
            SymbolGlyph.focusable(true);
            SymbolGlyph.fontSize(p8.iconOptions?.symbolicIconOption?.fontSize ?? LEFT_ICON_SIZE);
            SymbolGlyph.fontColor(p8.iconOptions?.symbolicIconOption?.fontColor ?? [this.subHeaderTheme.leftIconColor]);
            SymbolGlyph.fontWeight(p8.iconOptions?.symbolicIconOption?.fontWeight);
            SymbolGlyph.renderingStrategy(p8.iconOptions?.symbolicIconOption?.renderingStrategy);
            SymbolGlyph.effectStrategy(p8.iconOptions?.symbolicIconOption?.effectStrategy);
            SymbolGlyph.margin({ right: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } });
            SymbolGlyph.flexShrink(0);
          }, SymbolGlyph);
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((a9, b9) => {
            Image.create(p8.iconOptions?.icon);
            Image.fillColor(this.subHeaderTheme.leftIconColor);
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
    this.observeComponentCreation2((u8, v8) => {
      Text.create(p8.content);
      __Text__secondaryTitleStyles({
        maxLines: DOUBLE_LINE_NUM,
        fontWeight: FontWeight.Medium,
        alignment: Alignment.Start,
        fontColor: this.subHeaderTheme.fontSecondaryColor,
      });
      Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.secondaryTitleModifier));
      Text.flexShrink(1);
    }, Text);
    Text.pop();
    Flex.pop();
  }
  SubTitleStyle(d8, e8 = null) {
    this.observeComponentCreation2((m8, n8) => {
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
    this.observeComponentCreation2((k8, l8) => {
      Text.create(d8.content);
      __Text__primaryTitleStyles({
        fontWeight: FontWeight.Bold,
        maxLines: SINGLE_LINE_NUM,
        alignment: Alignment.Start,
        fontColor: this.subHeaderTheme.fontPrimaryColor,
      });
      Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.primaryTitleModifier));
      Text.width('100%');
    }, Text);
    Text.pop();
    this.observeComponentCreation2((i8, j8) => {
      Text.create(d8.subContent);
      __Text__secondaryTitleStyles({
        maxLines: SINGLE_LINE_NUM,
        fontWeight: FontWeight.Regular,
        alignment: Alignment.Start,
        fontColor: this.subHeaderTheme.fontSecondaryColor,
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
  SecondTitleStyle(u7, v7 = null) {
    this.observeComponentCreation2((b8, c8) => {
      Column.create();
      Column.alignItems(HorizontalAlign.Start);
      Column.padding({
        left: { "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        right: { "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        top: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
      });
    }, Column);
    this.observeComponentCreation2((y7, z7) => {
      Text.create(u7.content);
      __Text__secondaryTitleStyles({
        maxLines: DOUBLE_LINE_NUM,
        fontWeight: FontWeight.Medium,
        alignment: Alignment.Start,
        fontColor: this.subHeaderTheme.fontSecondaryColor,
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
  SelectStyle(i7, j7 = null) {
    this.observeComponentCreation2((r7, s7) => {
      Column.create();
      Column.alignItems(HorizontalAlign.Start);
      Column.onAppear(() => {
        this.isDuplicateLine = false;
        this.changeFlexAlign(FlexAlign.SpaceBetween);
      });
    }, Column);
    this.observeComponentCreation2((m7, n7) => {
      Select.create(i7.options);
      Select.selected(ObservedObject.GetRawObject(this.selectedIndex));
      Select.value(ObservedObject.GetRawObject(this.selectValue));
      Select.onSelect((p7, q7) => {
        this.selectedIndex = p7;
        if (q7) {
          this.selectValue = q7;
        }
        if (i7.onSelect) {
          i7.onSelect(p7, q7);
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
  PrimaryTitleStyle(z6, a7 = null) {
    this.observeComponentCreation2((g7, h7) => {
      Column.create();
      Column.alignItems(HorizontalAlign.Start);
      Column.padding({
        left: { "id": -1, "type": 10002, params: ['sys.float.padding_level0'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        right: { "id": -1, "type": 10002, params: ['sys.float.padding_level0'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        top: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
      });
    }, Column);
    this.observeComponentCreation2((d7, e7) => {
      Text.create(z6.content);
      __Text__primaryTitleStyles({
        fontWeight: FontWeight.Bold,
        maxLines: DOUBLE_LINE_NUM,
        alignment: Alignment.Start,
        fontColor: this.subHeaderTheme.fontPrimaryColor,
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
  ButtonStyle(l5, m5 = null) {
    this.observeComponentCreation2((x6, y6) => {
      Row.create();
      Row.margin({
        left: { "id": -1, "type": 10002, params: ['sys.float.padding_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        right: { "id": -1, "type": 10002, params: ['sys.float.padding_level5'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
      });
      Row.justifyContent(FlexAlign.End);
      Row.focusable(true);
    }, Row);
    this.observeComponentCreation2((v6, w6) => {
      Stack.create();
      Stack.focusable(true);
    }, Stack);
    this.observeComponentCreation2((y5, z5) => {
      If.create();
      if (l5) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((g6, h6) => {
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
            Row.onHover((u6) => {
              if (u6) {
                this.buttonBgColor = this.subHeaderTheme.textArrowHoverBgColor;
              }
              else {
                this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
              }
            });
            Row.onTouch((t6) => {
              if (t6.type === TouchType.Down) {
                this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
              }
              if (t6.type === TouchType.Up) {
                this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
              }
            });
            Row.onKeyEvent((s6) => {
              if (s6.keyCode === KeyCode.KEYCODE_ENTER || s6.keyCode === KeyCode.KEYCODE_SPACE) {
                if (l5.action) {
                  l5.action();
                }
              }
            });
            Row.onClick((r6) => {
              if (l5.action) {
                l5.action();
              }
            });
            Row.onAreaChange((p6, q6) => {
              this.buttonStyleWidth = Number(q6.width);
              this.buttonStyleHeight = Number(q6.height);
            });
          }, Row);
          this.observeComponentCreation2((e6, f6) => {
            Text.create(l5.value);
            __Text__secondaryTitleStyles({
              fontWeight: FontWeight.Medium,
              maxLines: SINGLE_LINE_NUM,
              fontColor: this.subHeaderTheme.fontButtonColor,
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
    this.observeComponentCreation2((r5, s5) => {
      If.create();
      if (this.buttonFocus) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((w5, x5) => {
            Row.create();
            Row.height(BUTTON_HEIGHT);
            Row.width(this.buttonStyleWidth);
            Row.hitTestBehavior(HitTestMode.None);
            Row.border({
              width: BORDER_WIDTH,
              color: this.subHeaderTheme.borderFocusColor
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
  TextArrowStyle(z3, a4 = null) {
    this.observeComponentCreation2((b5, c5) => {
      Row.create();
      Row.onHover((k5) => {
        if (k5) {
          this.textArrowBgColor = this.subHeaderTheme.textArrowHoverBgColor;
        }
        else {
          this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        }
      });
      Row.onTouch((j5) => {
        if (j5.type === TouchType.Down) {
          this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        }
        if (j5.type === TouchType.Up) {
          this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        }
      });
      Row.onKeyEvent((i5) => {
        if (i5.keyCode === KeyCode.KEYCODE_ENTER || i5.keyCode === KeyCode.KEYCODE_SPACE) {
          if (z3.action) {
            z3.action();
          }
        }
      });
      Row.onClick((h5) => {
        if (z3.action) {
          z3.action();
        }
      });
      Row.focusable(true);
      Row.justifyContent(FlexAlign.End);
      Row.margin({
        left: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        right: this.contentMargin?.right ?? { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
      });
    }, Row);
    this.observeComponentCreation2((z4, a5) => {
      Stack.create();
    }, Stack);
    this.observeComponentCreation2((s4, t4) => {
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
      Row.onAreaChange((x4, y4) => {
        this.textArrowStyleWidth = Number(y4.width);
        this.textArrowStyleHeight = Number(y4.height);
      });
    }, Row);
    this.observeComponentCreation2((l4, m4) => {
      If.create();
      if (z3) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((q4, r4) => {
            Text.create(z3.value);
            __Text__secondaryTitleStyles({
              maxLines: SINGLE_LINE_NUM,
              fontWeight: FontWeight.Regular,
              alignment: Alignment.End,
              fontColor: this.subHeaderTheme.fontSecondaryColor,
            });
            Text.margin({
              right: PADDING_LEVEL_2 + ARROW_ICON_WIDTH,
              top: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
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
    this.observeComponentCreation2((j4, k4) => {
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
        color: this.subHeaderTheme.borderFocusColor,
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
    this.observeComponentCreation2((h4, i4) => {
      Image.create({ "id": -1, "type": 20000, params: ['sys.media.ohos_ic_public_arrow_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Image.fillColor(this.subHeaderTheme.iconArrowColor);
      Image.width(ARROW_ICON_WIDTH);
      Image.height(ARROW_ICON_HEIGHT);
      Image.focusable(true);
      Image.draggable(false);
    }, Image);
    Row.pop();
    Stack.pop();
    Row.pop();
  }
  IconGroupStyle(k2, l2 = null) {
    this.observeComponentCreation2((x3, y3) => {
      Row.create();
      Row.justifyContent(FlexAlign.End);
      Row.focusable(true);
      Row.margin({
        left: { "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        right: this.contentMargin?.right ?? { "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
      });
    }, Row);
    this.observeComponentCreation2((o2, p2) => {
      ForEach.create();
      const q2 = (s2, t2) => {
        const u2 = s2;
        this.observeComponentCreation2((w2, x2) => {
          If.create();
          if (Util.isResourceType(u2.value)) {
            this.ifElseBranchUpdateFunction(0, () => {
              this.observeComponentCreation2((b3, c3) => {
                If.create();
                if (t2 === INDEX_ZERO) {
                  this.ifElseBranchUpdateFunction(0, () => {
                    {
                      this.observeComponentCreation2((r3, s3) => {
                        if (s3) {
                          let t3 = new SingleIconStyle(this, {
                            item: {
                              iconOptions: {
                                icon: u2.value,
                                symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > t2 ?
                                this.operationSymbolOptions[t2] : null,
                              },
                              action: u2.action,
                            }
                          }, undefined, r3, () => { }, { page: "library/src/main/ets/components/mainpage/subheader.ets", line: 620, col: 13 });
                          ViewPU.create(t3);
                          let u3 = () => {
                            return {
                              item: {
                                iconOptions: {
                                  icon: u2.value,
                                  symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > t2 ?
                                  this.operationSymbolOptions[t2] : null,
                                },
                                action: u2.action,
                              }
                            };
                          };
                          t3.paramsGenerator_ = u3;
                        }
                        else {
                          this.updateStateVarsOfChildByElmtId(r3, {});
                        }
                      }, { name: "SingleIconStyle" });
                    }
                  });
                }
                else if (t2 === INDEX_ONE || t2 === INDEX_TWO) {
                  this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((n3, o3) => {
                      __Common__.create();
                      __Common__.margin({
                        left: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                      });
                    }, __Common__);
                    {
                      this.observeComponentCreation2((h3, i3) => {
                        if (i3) {
                          let j3 = new SingleIconStyle(this, {
                            item: {
                              action: u2.action,
                              iconOptions: {
                                icon: u2.value,
                                symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > t2 ?
                                this.operationSymbolOptions[t2] : null,
                              },
                            }
                          }, undefined, h3, () => { }, { page: "library/src/main/ets/components/mainpage/subheader.ets", line: 631, col: 13 });
                          ViewPU.create(j3);
                          let k3 = () => {
                            return {
                              item: {
                                action: u2.action,
                                iconOptions: {
                                  icon: u2.value,
                                  symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > t2 ?
                                  this.operationSymbolOptions[t2] : null,
                                },
                              }
                            };
                          };
                          j3.paramsGenerator_ = k3;
                        }
                        else {
                          this.updateStateVarsOfChildByElmtId(h3, {});
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
      this.forEachUpdateFunction(o2, k2, q2, undefined, true, false);
    }, ForEach);
    ForEach.pop();
    Row.pop();
  }
  LoadingProcessStyle(c2 = null) {
    this.observeComponentCreation2((i2, j2) => {
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
    this.observeComponentCreation2((f2, g2) => {
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
  dummyFunction(x1 = null) {
    this.observeComponentCreation2((z1, a2) => {
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
  changeFlexAlign(w1) {
    if (this.flexAlign === w1) {
      return;
    }
    this.flexAlign = w1;
  }
  rerender() {
    this.updateDirtyElements();
  }
}
class SingleIconStyle extends ViewPU {
  constructor(q1, r1, s1, t1 = -1, u1 = undefined, v1) {
    super(q1, s1, t1, v1);
    if (typeof u1 === "function") {
      this.paramsGenerator_ = u1;
    }
    this.__bgColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "bgColor");
    this.__isFocus = new ObservedPropertySimplePU(false, this, "isFocus");
    this.item = null;
    this.__subHeaderTheme = this.initializeConsume("subHeaderTheme", "subHeaderTheme");
    this.setInitiallyProvidedValue(r1);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(p1) {
    if (p1.bgColor !== undefined) {
      this.bgColor = p1.bgColor;
    }
    if (p1.isFocus !== undefined) {
      this.isFocus = p1.isFocus;
    }
    if (p1.item !== undefined) {
      this.item = p1.item;
    }
  }
  updateStateVars(o1) {
  }
  purgeVariableDependenciesOnElmtId(n1) {
    this.__bgColor.purgeDependencyOnElmtId(n1);
    this.__isFocus.purgeDependencyOnElmtId(n1);
    this.__subHeaderTheme.purgeDependencyOnElmtId(n1);
  }
  aboutToBeDeleted() {
    this.__bgColor.aboutToBeDeleted();
    this.__isFocus.aboutToBeDeleted();
    this.__subHeaderTheme.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get bgColor() {
    return this.__bgColor.get();
  }
  set bgColor(m1) {
    this.__bgColor.set(m1);
  }
  get isFocus() {
    return this.__isFocus.get();
  }
  set isFocus(l1) {
    this.__isFocus.set(l1);
  }
  get subHeaderTheme() {
    return this.__subHeaderTheme.get();
  }
  set subHeaderTheme(k1) {
    this.__subHeaderTheme.set(k1);
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
              color: this.subHeaderTheme.borderFocusColor,
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
                  SymbolGlyph.fontColor(this.item.iconOptions?.symbolicIconOption?.fontColor ?? [this.subHeaderTheme.rightIconColor]);
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
                  Image.fillColor(this.subHeaderTheme.rightIconColor);
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