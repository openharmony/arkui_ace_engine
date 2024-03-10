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
const IMAGE_WIDTH_NUM = 16;
const IMAGE_HEIGHT_NUM = 24;
const BUTTON_SIZE = 32;
const SINGLE_LINE_HEIGHT = 56;
const DOUBLE_LINE_HEIGHT = 72;
const BUTTON_HEIGHT = 28;
const IMAGE_WIDTH = 12;
const BORDER_WIDTH = 2;
const DIVIDEND_NUM = 3;
const SINGLE_LINE_NUM = 1;
const DOUBLE_LINE_NUM = 2;
const INDEX_ZERO = 0;
const INDEX_ONE = 1;
const INDEX_TWO = 2;
const RESOURCE_TYPE_SYMBOL = 40000;
const DEFAULT_VALUE = 0;
export var OperationType;
(function (z12) {
  z12[z12['TEXT_ARROW'] = 0] = 'TEXT_ARROW';
  z12[z12['BUTTON'] = 1] = 'BUTTON';
  z12[z12['ICON_GROUP'] = 2] = 'ICON_GROUP';
  z12[z12['LOADING'] = 3] = 'LOADING';
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
function __Text__secondaryTitleStyles(x12) {
  var y12;
  Text.fontSize({ id: -1, type: 10002, params: ['sys.float.Subtitle_S'], bundleName: '', moduleName: '' });
  Text.fontColor((y12 = x12 === null || x12 === void 0 ? void 0 : x12.fontColor) !== null && y12 !== void 0 ? y12 : { id: -1, type: 10001, params: ['sys.color.font_secondary'], bundleName: '', moduleName: '' });
  Text.fontWeight(x12 === null || x12 === void 0 ? void 0 : x12.fontWeight);
  Text.maxLines(x12 === null || x12 === void 0 ? void 0 : x12.maxLines);
  Text.textOverflow({ overflow: TextOverflow.Ellipsis });
  Text.align(x12 === null || x12 === void 0 ? void 0 : x12.alignment);
}
function __Text__primaryTitleStyles(w12) {
  Text.fontSize({ id: -1, type: 10002, params: ['sys.float.Subtitle_L'], bundleName: '', moduleName: '' });
  Text.fontColor({ id: -1, type: 10001, params: ['sys.color.font_primary'], bundleName: '', moduleName: '' });
  Text.fontWeight(w12 === null || w12 === void 0 ? void 0 : w12.fontWeight);
  Text.maxLines(w12 === null || w12 === void 0 ? void 0 : w12.maxLines);
  Text.textOverflow({ overflow: TextOverflow.Ellipsis });
  Text.align(w12 === null || w12 === void 0 ? void 0 : w12.alignment);
}
export class SubHeader extends ViewPU {
  constructor(q12, r12, s12, t12 = -1, u12 = undefined, v12) {
    super(q12, s12, t12, v12);
    if (typeof u12 === 'function') {
      this.paramsGenerator_ = u12;
    }
    this.__icon = new SynchedPropertyObjectOneWayPU(r12.icon, this, 'icon');
    this.iconSymbolOptions = null;
    this.__primaryTitle = new SynchedPropertyObjectOneWayPU(r12.primaryTitle, this, 'primaryTitle');
    this.__secondaryTitle = new SynchedPropertyObjectOneWayPU(r12.secondaryTitle, this, 'secondaryTitle');
    this.__select = new SynchedPropertyObjectOneWayPU(r12.select, this, 'select');
    this.__operationType = new SynchedPropertySimpleOneWayPU(r12.operationType, this, 'operationType');
    this.operationItem = null;
    this.operationSymbolOptions = null;
    this.__isDuplicateLine = new ObservedPropertySimplePU(false, this, 'isDuplicateLine');
    this.__textArrowBgColor = new ObservedPropertyObjectPU({ id: -1, type: 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], bundleName: '', moduleName: '' }, this, 'textArrowBgColor');
    this.__buttonBgColor = new ObservedPropertyObjectPU({ id: -1, type: 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], bundleName: '', moduleName: '' }, this, 'buttonBgColor');
    this.__flexWidth = new ObservedPropertySimplePU(0, this, 'flexWidth');
    this.__textArrowWidth = new ObservedPropertySimplePU(0, this, 'textArrowWidth');
    this.__textArrowFocus = new ObservedPropertySimplePU(false, this, 'textArrowFocus');
    this.__buttonFocus = new ObservedPropertySimplePU(false, this, 'buttonFocus');
    this.__arrowWidth = new ObservedPropertySimplePU(0, this, 'arrowWidth');
    this.__buttonWidth = new ObservedPropertySimplePU(0, this, 'buttonWidth');
    this.focusBorderWidth = BORDER_WIDTH;
    this.__flexAlign = new ObservedPropertySimplePU(FlexAlign.SpaceBetween, this, 'flexAlign');
    this.setInitiallyProvidedValue(r12);
  }
  setInitiallyProvidedValue(p12) {
    if (p12.icon === undefined) {
      this.__icon.set(null);
    }
    if (p12.iconSymbolOptions !== undefined) {
      this.iconSymbolOptions = p12.iconSymbolOptions;
    }
    if (p12.primaryTitle === undefined) {
      this.__primaryTitle.set(null);
    }
    if (p12.secondaryTitle === undefined) {
      this.__secondaryTitle.set(null);
    }
    if (p12.select === undefined) {
      this.__select.set(null);
    }
    if (p12.operationType === undefined) {
      this.__operationType.set(OperationType.BUTTON);
    }
    if (p12.operationItem !== undefined) {
      this.operationItem = p12.operationItem;
    }
    if (p12.operationSymbolOptions !== undefined) {
      this.operationSymbolOptions = p12.operationSymbolOptions;
    }
    if (p12.isDuplicateLine !== undefined) {
      this.isDuplicateLine = p12.isDuplicateLine;
    }
    if (p12.textArrowBgColor !== undefined) {
      this.textArrowBgColor = p12.textArrowBgColor;
    }
    if (p12.buttonBgColor !== undefined) {
      this.buttonBgColor = p12.buttonBgColor;
    }
    if (p12.flexWidth !== undefined) {
      this.flexWidth = p12.flexWidth;
    }
    if (p12.textArrowWidth !== undefined) {
      this.textArrowWidth = p12.textArrowWidth;
    }
    if (p12.textArrowFocus !== undefined) {
      this.textArrowFocus = p12.textArrowFocus;
    }
    if (p12.buttonFocus !== undefined) {
      this.buttonFocus = p12.buttonFocus;
    }
    if (p12.arrowWidth !== undefined) {
      this.arrowWidth = p12.arrowWidth;
    }
    if (p12.buttonWidth !== undefined) {
      this.buttonWidth = p12.buttonWidth;
    }
    if (p12.focusBorderWidth !== undefined) {
      this.focusBorderWidth = p12.focusBorderWidth;
    }
    if (p12.flexAlign !== undefined) {
      this.flexAlign = p12.flexAlign;
    }
  }
  updateStateVars(o12) {
    this.__icon.reset(o12.icon);
    this.__primaryTitle.reset(o12.primaryTitle);
    this.__secondaryTitle.reset(o12.secondaryTitle);
    this.__select.reset(o12.select);
    this.__operationType.reset(o12.operationType);
  }
  purgeVariableDependenciesOnElmtId(n12) {
    this.__icon.purgeDependencyOnElmtId(n12);
    this.__primaryTitle.purgeDependencyOnElmtId(n12);
    this.__secondaryTitle.purgeDependencyOnElmtId(n12);
    this.__select.purgeDependencyOnElmtId(n12);
    this.__operationType.purgeDependencyOnElmtId(n12);
    this.__isDuplicateLine.purgeDependencyOnElmtId(n12);
    this.__textArrowBgColor.purgeDependencyOnElmtId(n12);
    this.__buttonBgColor.purgeDependencyOnElmtId(n12);
    this.__flexWidth.purgeDependencyOnElmtId(n12);
    this.__textArrowWidth.purgeDependencyOnElmtId(n12);
    this.__textArrowFocus.purgeDependencyOnElmtId(n12);
    this.__buttonFocus.purgeDependencyOnElmtId(n12);
    this.__arrowWidth.purgeDependencyOnElmtId(n12);
    this.__buttonWidth.purgeDependencyOnElmtId(n12);
    this.__flexAlign.purgeDependencyOnElmtId(n12);
  }
  aboutToBeDeleted() {
    this.__icon.aboutToBeDeleted();
    this.__primaryTitle.aboutToBeDeleted();
    this.__secondaryTitle.aboutToBeDeleted();
    this.__select.aboutToBeDeleted();
    this.__operationType.aboutToBeDeleted();
    this.__isDuplicateLine.aboutToBeDeleted();
    this.__textArrowBgColor.aboutToBeDeleted();
    this.__buttonBgColor.aboutToBeDeleted();
    this.__flexWidth.aboutToBeDeleted();
    this.__textArrowWidth.aboutToBeDeleted();
    this.__textArrowFocus.aboutToBeDeleted();
    this.__buttonFocus.aboutToBeDeleted();
    this.__arrowWidth.aboutToBeDeleted();
    this.__buttonWidth.aboutToBeDeleted();
    this.__flexAlign.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get icon() {
    return this.__icon.get();
  }
  set icon(m12) {
    this.__icon.set(m12);
  }
  get primaryTitle() {
    return this.__primaryTitle.get();
  }
  set primaryTitle(l12) {
    this.__primaryTitle.set(l12);
  }
  get secondaryTitle() {
    return this.__secondaryTitle.get();
  }
  set secondaryTitle(k12) {
    this.__secondaryTitle.set(k12);
  }
  get select() {
    return this.__select.get();
  }
  set select(j12) {
    this.__select.set(j12);
  }
  get operationType() {
    return this.__operationType.get();
  }
  set operationType(i12) {
    this.__operationType.set(i12);
  }
  get isDuplicateLine() {
    return this.__isDuplicateLine.get();
  }
  set isDuplicateLine(h12) {
    this.__isDuplicateLine.set(h12);
  }
  get textArrowBgColor() {
    return this.__textArrowBgColor.get();
  }
  set textArrowBgColor(g12) {
    this.__textArrowBgColor.set(g12);
  }
  get buttonBgColor() {
    return this.__buttonBgColor.get();
  }
  set buttonBgColor(f12) {
    this.__buttonBgColor.set(f12);
  }
  get flexWidth() {
    return this.__flexWidth.get();
  }
  set flexWidth(e12) {
    this.__flexWidth.set(e12);
  }
  get textArrowWidth() {
    return this.__textArrowWidth.get();
  }
  set textArrowWidth(d12) {
    this.__textArrowWidth.set(d12);
  }
  get textArrowFocus() {
    return this.__textArrowFocus.get();
  }
  set textArrowFocus(c12) {
    this.__textArrowFocus.set(c12);
  }
  get buttonFocus() {
    return this.__buttonFocus.get();
  }
  set buttonFocus(b12) {
    this.__buttonFocus.set(b12);
  }
  get arrowWidth() {
    return this.__arrowWidth.get();
  }
  set arrowWidth(a12) {
    this.__arrowWidth.set(a12);
  }
  get buttonWidth() {
    return this.__buttonWidth.get();
  }
  set buttonWidth(z11) {
    this.__buttonWidth.set(z11);
  }
  get flexAlign() {
    return this.__flexAlign.get();
  }
  set flexAlign(y11) {
    this.__flexAlign.set(y11);
  }
  initialRender() {
    this.observeComponentCreation2((s11, t11) => {
      Flex.create({ justifyContent: this.flexAlign, alignItems: ItemAlign.End });
      Flex.focusable(true);
      Flex.onAreaChange((v11, w11) => {
        let x11 = Number(parseInt(w11.width.toString(), DEFAULT_VALUE));
        this.flexWidth = x11;
      });
      Flex.height(this.isDuplicateLine ? DOUBLE_LINE_HEIGHT : SINGLE_LINE_HEIGHT);
    }, Flex);
    this.leftArea.bind(this)();
    this.rightArea.bind(this)();
    Flex.pop();
  }
  leftArea(h11 = null) {
    this.observeComponentCreation2((j11, k11) => {
      If.create();
      if (this.secondaryTitle && this.icon) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.IconSecondTitleStyle.bind(this)(makeBuilderParameterProxy('IconSecondTitleStyle', {
            content: () => this.secondaryTitle, iconOptions: () => ({
              icon: this.icon,
              symbolicIconOption: this.iconSymbolOptions,
            })
          }));
        });
      }
      else if (this.secondaryTitle && this.primaryTitle) {
        this.ifElseBranchUpdateFunction(1, () => {
          this.SubTitleStyle.bind(this)(makeBuilderParameterProxy('SubTitleStyle', { content: () => this.primaryTitle, subContent: () => this.secondaryTitle }));
        });
      }
      else if (this.secondaryTitle) {
        this.ifElseBranchUpdateFunction(2, () => {
          this.SecondTitleStyle.bind(this)(makeBuilderParameterProxy('SecondTitleStyle', { content: () => this.secondaryTitle }));
        });
      }
      else if (this.select) {
        this.ifElseBranchUpdateFunction(3, () => {
          this.SelectStyle.bind(this)(ObservedObject.GetRawObject(this.select));
        });
      }
      else if (this.primaryTitle) {
        this.ifElseBranchUpdateFunction(4, () => {
          this.PrimaryTitleStyle.bind(this)(makeBuilderParameterProxy('PrimaryTitleStyle', { content: () => this.primaryTitle }));
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
  rightArea(m10 = null) {
    this.observeComponentCreation2((d11, e11) => {
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
    this.observeComponentCreation2((z10, a11) => {
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
    this.observeComponentCreation2((v10, w10) => {
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
    this.observeComponentCreation2((r10, s10) => {
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
  IconSecondTitleStyle(d9, e9 = null) {
    this.observeComponentCreation2((j10, k10) => {
      Row.create();
      Row.padding({
        left: { id: -1, type: 10002, params: ['sys.float.padding_level6'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.padding_level6'], bundleName: '', moduleName: '' },
        top: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
        bottom: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
      });
      Row.margin({
        left: { id: -1, type: 10002, params: ['sys.float.margin_left'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.margin_right'], bundleName: '', moduleName: '' },
      });
      Row.onAppear(() => {
        this.isDuplicateLine = false;
        this.changeFlexAlign(FlexAlign.SpaceBetween);
      });
    }, Row);
    this.observeComponentCreation2((k9, l9) => {
      var m9;
      If.create();
      if (Util.isSymbolicResource((m9 = d9.iconOptions) === null || m9 === void 0 ? void 0 : m9.icon)) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((u9, v9) => {
            var w9;
            var x9;
            var y9;
            var z9;
            var a10;
            var b10;
            var c10;
            var d10;
            var e10;
            var f10;
            var g10;
            var h10;
            var i10;
            SymbolGlyph.create((w9 = d9.iconOptions) === null || w9 === void 0 ? void 0 : w9.icon);
            SymbolGlyph.focusable(true);
            SymbolGlyph.fontSize((z9 = (y9 = (x9 = d9.iconOptions) === null || x9 === void 0 ? void 0 : x9.symbolicIconOption) === null || y9 === void 0 ? void 0 : y9.fontSize) !== null && z9 !== void 0 ? z9 : IMAGE_WIDTH_NUM);
            SymbolGlyph.fontColor((c10 = (b10 = (a10 = d9.iconOptions) === null || a10 === void 0 ? void 0 : a10.symbolicIconOption) === null || b10 === void 0 ? void 0 : b10.fontColor) !== null && c10 !== void 0 ? c10 : [{ id: -1, type: 10001, params: ['sys.color.icon_secondary'], bundleName: '', moduleName: '' }]);
            SymbolGlyph.fontWeight((e10 = (d10 = d9.iconOptions) === null || d10 === void 0 ? void 0 : d10.symbolicIconOption) === null || e10 === void 0 ? void 0 : e10.fontWeight);
            SymbolGlyph.renderingStrategy((g10 = (f10 = d9.iconOptions) === null || f10 === void 0 ? void 0 : f10.symbolicIconOption) === null || g10 === void 0 ? void 0 : g10.renderingStrategy);
            SymbolGlyph.effectStrategy((i10 = (h10 = d9.iconOptions) === null || h10 === void 0 ? void 0 : h10.symbolicIconOption) === null || i10 === void 0 ? void 0 : i10.effectStrategy);
            SymbolGlyph.margin({ right: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' } });
          }, SymbolGlyph);
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((p9, q9) => {
            var r9;
            Image.create((r9 = d9.iconOptions) === null || r9 === void 0 ? void 0 : r9.icon);
            Image.width(IMAGE_WIDTH_NUM);
            Image.height(IMAGE_WIDTH_NUM);
            Image.margin({ right: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' } });
          }, Image);
        });
      }
    }, If);
    If.pop();
    this.observeComponentCreation2((i9, j9) => {
      Text.create(d9.content);
      __Text__secondaryTitleStyles({
        maxLines: DOUBLE_LINE_NUM,
        fontWeight: FontWeight.Medium,
        alignment: Alignment.Start,
      });
    }, Text);
    Text.pop();
    Row.pop();
  }
  SubTitleStyle(r8, s8 = null) {
    this.observeComponentCreation2((a9, b9) => {
      Column.create();
      Column.margin({
        left: { id: -1, type: 10002, params: ['sys.float.margin_left'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.margin_right'], bundleName: '', moduleName: '' },
      });
      Column.padding({
        left: { id: -1, type: 10002, params: ['sys.float.padding_level0'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.padding_level0'], bundleName: '', moduleName: '' },
        top: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
        bottom: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
      });
      Column.alignItems(HorizontalAlign.Start);
      Column.onAppear(() => {
        this.isDuplicateLine = true;
        this.changeFlexAlign(FlexAlign.SpaceBetween);
      });
    }, Column);
    this.observeComponentCreation2((y8, z8) => {
      Text.create(r8.content);
      __Text__primaryTitleStyles({
        fontWeight: FontWeight.Medium,
        maxLines: SINGLE_LINE_NUM,
        alignment: Alignment.Start,
      });
    }, Text);
    Text.pop();
    this.observeComponentCreation2((w8, x8) => {
      Text.create(r8.subContent);
      __Text__secondaryTitleStyles({
        maxLines: SINGLE_LINE_NUM,
        fontWeight: FontWeight.Regular,
        alignment: Alignment.Start,
      });
      Text.margin({
        top: { id: -1, type: 10002, params: ['sys.float.padding_level1'], bundleName: '', moduleName: '' },
      });
    }, Text);
    Text.pop();
    Column.pop();
  }
  SecondTitleStyle(i8, j8 = null) {
    this.observeComponentCreation2((p8, q8) => {
      Column.create();
      Column.padding({
        left: { id: -1, type: 10002, params: ['sys.float.padding_level6'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.padding_level6'], bundleName: '', moduleName: '' },
        top: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
        bottom: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
      });
      Column.margin({
        left: { id: -1, type: 10002, params: ['sys.float.margin_left'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.margin_right'], bundleName: '', moduleName: '' },
      });
    }, Column);
    this.observeComponentCreation2((m8, n8) => {
      Text.create(i8.content);
      __Text__secondaryTitleStyles({
        maxLines: DOUBLE_LINE_NUM,
        fontWeight: FontWeight.Medium,
        alignment: Alignment.Start,
      });
      Text.onAppear(() => {
        this.isDuplicateLine = false;
        this.changeFlexAlign(FlexAlign.SpaceBetween);
      });
    }, Text);
    Text.pop();
    Column.pop();
  }
  SelectStyle(w7, x7 = null) {
    this.observeComponentCreation2((f8, g8) => {
      Row.create();
      Row.margin({
        left: { id: -1, type: 10002, params: ['sys.float.margin_left'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.margin_right'], bundleName: '', moduleName: '' },
      });
      Row.onAppear(() => {
        this.isDuplicateLine = false;
        this.changeFlexAlign(FlexAlign.SpaceBetween);
      });
    }, Row);
    this.observeComponentCreation2((a8, b8) => {
      Select.create(w7.options);
      Select.selected(w7.selected);
      Select.value(w7.value);
      Select.onSelect((d8, e8) => {
        if (w7.onSelect) {
          w7.onSelect(d8, e8);
        }
      });
      Select.font({
        size: { id: -1, type: 10002, params: ['sys.float.Body_L'], bundleName: '', moduleName: '' },
        weight: FontWeight.Medium,
      });
    }, Select);
    Select.pop();
    Row.pop();
  }
  PrimaryTitleStyle(n7, o7 = null) {
    this.observeComponentCreation2((u7, v7) => {
      Column.create();
      Column.margin({
        left: { id: -1, type: 10002, params: ['sys.float.margin_left'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.margin_right'], bundleName: '', moduleName: '' },
      });
      Column.padding({
        left: { id: -1, type: 10002, params: ['sys.float.padding_level0'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.padding_level0'], bundleName: '', moduleName: '' },
        top: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
        bottom: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
      });
    }, Column);
    this.observeComponentCreation2((r7, s7) => {
      Text.create(n7.content);
      __Text__primaryTitleStyles({
        fontWeight: FontWeight.Medium,
        maxLines: DOUBLE_LINE_NUM,
        alignment: Alignment.Start,
      });
      Text.onAppear(() => {
        this.isDuplicateLine = false;
        this.changeFlexAlign(FlexAlign.SpaceBetween);
      });
    }, Text);
    Text.pop();
    Column.pop();
  }
  ButtonStyle(a6, b6 = null) {
    this.observeComponentCreation2((l7, m7) => {
      Row.create();
      Row.margin({
        left: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.margin_right'], bundleName: '', moduleName: '' },
      });
      Row.constraintSize({ minWidth: this.flexWidth / DIVIDEND_NUM });
      Row.justifyContent(FlexAlign.End);
      Row.focusable(true);
    }, Row);
    this.observeComponentCreation2((j7, k7) => {
      Stack.create();
      Stack.focusable(true);
    }, Stack);
    this.observeComponentCreation2((f6, g6) => {
      If.create();
      if (a6) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((v6, w6) => {
            Row.create();
            Row.backgroundColor(ObservedObject.GetRawObject(this.buttonBgColor));
            Row.focusable(true);
            Row.height(BUTTON_HEIGHT);
            Row.justifyContent(FlexAlign.End);
            Row.borderRadius({ id: -1, type: 10002, params: ['sys.float.corner_radius_level4'], bundleName: '', moduleName: '' });
            ViewStackProcessor.visualState('focused');
            Row.border({
              radius: { id: -1, type: 10002, params: ['sys.float.corner_radius_level4'], bundleName: '', moduleName: '' },
              width: this.buttonWidth,
              color: { id: -1, type: 10001, params: ['sys.color.interactive_focus'], bundleName: '', moduleName: '' },
              style: BorderStyle.Solid,
            });
            Row.backgroundColor({ id: -1, type: 10001, params: ['sys.color.interactive_focus'], bundleName: '', moduleName: '' });
            ViewStackProcessor.visualState('pressed');
            Row.backgroundColor({ id: -1, type: 10001, params: ['sys.color.interactive_pressed'], bundleName: '', moduleName: '' });
            ViewStackProcessor.visualState('disabled');
            Row.opacity({ id: -1, type: 10002, params: ['sys.float.interactive_disable'], bundleName: '', moduleName: '' });
            ViewStackProcessor.visualState();
            Row.onFocus(() => {
              this.buttonFocus = true;
              this.buttonBgColor = { id: -1, type: 10001, params: ['sys.color.interactive_focus'], bundleName: '', moduleName: '' };
            });
            Row.onBlur(() => {
              this.buttonFocus = false;
            });
            Row.onHover((i7) => {
              if (i7) {
                this.buttonBgColor = { id: -1, type: 10001, params: ['sys.color.interactive_hover'], bundleName: '', moduleName: '' };
              }
              else {
                this.buttonBgColor = { id: -1, type: 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], bundleName: '', moduleName: '' };
              }
            });
            Row.onTouch((h7) => {
              if (h7.type === TouchType.Down) {
                if (a6.action) {
                  a6.action();
                }
                this.buttonBgColor = { id: -1, type: 10001, params: ['sys.color.interactive_pressed'], bundleName: '', moduleName: '' };
              }
              if (h7.type === TouchType.Up) {
                this.buttonBgColor = { id: -1, type: 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], bundleName: '', moduleName: '' };
              }
            });
            Row.onKeyEvent((g7) => {
              if (g7.keyCode === KeyCode.KEYCODE_ENTER || g7.keyCode === KeyCode.KEYCODE_SPACE) {
                if (a6.action) {
                  a6.action();
                }
              }
            });
            Row.onAreaChange((d7, e7) => {
              let f7 = Number(parseInt(e7.width.toString(), DEFAULT_VALUE));
              this.buttonWidth = f7;
            });
          }, Row);
          this.observeComponentCreation2((t6, u6) => {
            Text.create(a6.value);
            __Text__secondaryTitleStyles({
              fontWeight: FontWeight.Medium,
              maxLines: SINGLE_LINE_NUM,
              fontColor: { id: -1, type: 10001, params: ['sys.color.font_emphasize'], bundleName: '', moduleName: '' },
            });
            Text.focusable(true);
          }, Text);
          Text.pop();
          Row.pop();
          this.observeComponentCreation2((m6, n6) => {
            If.create();
            if (this.buttonFocus) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation2((r6, s6) => {
                  Row.create();
                  Row.height(BUTTON_HEIGHT);
                  Row.width(this.buttonWidth);
                  Row.hitTestBehavior(HitTestMode.None);
                  Row.border({
                    width: { id: -1, type: 10002, params: ['sys.float.outline_extra_larger'], bundleName: '', moduleName: '' },
                    color: { id: -1, type: 10001, params: ['sys.color.interactive_focus'], bundleName: '', moduleName: '' },
                  });
                  Row.borderRadius({ id: -1, type: 10002, params: ['sys.float.corner_radius_level4'], bundleName: '', moduleName: '' });
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
  IconGroupStyle(p4, q4 = null) {
    this.observeComponentCreation2((y5, z5) => {
      Row.create();
      Row.justifyContent(FlexAlign.End);
      Row.constraintSize({ minWidth: this.flexWidth / DIVIDEND_NUM });
      Row.focusable(true);
      Row.margin({
        left: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.margin_right'], bundleName: '', moduleName: '' },
      });
    }, Row);
    this.observeComponentCreation2((t4, u4) => {
      ForEach.create();
      const v4 = (x4, y4) => {
        const z4 = x4;
        this.observeComponentCreation2((b5, c5) => {
          If.create();
          if (Util.isResourceType(z4.value)) {
            this.ifElseBranchUpdateFunction(0, () => {
              this.observeComponentCreation2((g5, h5) => {
                If.create();
                if (y4 === INDEX_ZERO) {
                  this.ifElseBranchUpdateFunction(0, () => {
                    {
                      this.observeComponentCreation2((u5, v5) => {
                        if (v5) {
                          let w5 = () => {
                            return {
                              item: {
                                iconOptions: {
                                  icon: z4.value,
                                  symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > y4 ?
                                    this.operationSymbolOptions[y4] : null,
                                },
                                action: z4.action,
                              }
                            };
                          };
                          ViewPU.create(new SingleIconStyle(this, {
                            item: {
                              iconOptions: {
                                icon: z4.value,
                                symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > y4 ?
                                  this.operationSymbolOptions[y4] : null,
                              },
                              action: z4.action,
                            }
                          }, undefined, u5, w5, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 436 }));
                        }
                        else {
                          this.updateStateVarsOfChildByElmtId(u5, {});
                        }
                      }, { name: 'SingleIconStyle' });
                    }
                  });
                }
                else if (y4 === INDEX_ONE || y4 === INDEX_TWO) {
                  this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((q5, r5) => {
                      __Common__.create();
                      __Common__.margin({
                        left: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
                      });
                    }, __Common__);
                    {
                      this.observeComponentCreation2((m5, n5) => {
                        if (n5) {
                          let o5 = () => {
                            return {
                              item: {
                                action: z4.action,
                                iconOptions: {
                                  icon: z4.value,
                                  symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > y4 ?
                                    this.operationSymbolOptions[y4] : null,
                                },
                              }
                            };
                          };
                          ViewPU.create(new SingleIconStyle(this, {
                            item: {
                              action: z4.action,
                              iconOptions: {
                                icon: z4.value,
                                symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > y4 ?
                                  this.operationSymbolOptions[y4] : null,
                              },
                            }
                          }, undefined, m5, o5, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 447 }));
                        }
                        else {
                          this.updateStateVarsOfChildByElmtId(m5, {});
                        }
                      }, { name: 'SingleIconStyle' });
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
      this.forEachUpdateFunction(t4, this.operationItem, v4, undefined, true, false);
    }, ForEach);
    ForEach.pop();
    Row.pop();
  }
  TextArrowStyle(u2, v2 = null) {
    this.observeComponentCreation2((k4, l4) => {
      Row.create();
      Row.focusable(true);
      Row.onAreaChange((n4, o4) => {
        this.textArrowWidth = Number(parseInt(o4.width.toString(), DEFAULT_VALUE));
      });
      Row.constraintSize({ minWidth: this.flexWidth / DIVIDEND_NUM });
      Row.justifyContent(FlexAlign.End);
      Row.margin({
        left: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.margin_right'], bundleName: '', moduleName: '' },
      });
    }, Row);
    this.observeComponentCreation2((i4, j4) => {
      Stack.create();
      Stack.focusable(true);
    }, Stack);
    this.observeComponentCreation2((v3, w3) => {
      Row.create();
      Row.borderRadius({ id: -1, type: 10002, params: ['sys.float.corner_radius_level4'], bundleName: '', moduleName: '' });
      Row.focusable(true);
      Row.backgroundColor(ObservedObject.GetRawObject(this.textArrowBgColor));
      Row.height(BUTTON_SIZE);
      Row.justifyContent(FlexAlign.End);
      Row.onFocus(() => {
        this.textArrowFocus = true;
      });
      Row.onBlur(() => {
        this.textArrowFocus = false;
      });
      Row.padding({
        left: { id: -1, type: 10002, params: ['sys.float.padding_level2'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.padding_level2'], bundleName: '', moduleName: '' },
        top: { id: -1, type: 10002, params: ['sys.float.padding_level2'], bundleName: '', moduleName: '' },
        bottom: { id: -1, type: 10002, params: ['sys.float.padding_level2'], bundleName: '', moduleName: '' },
      });
      Row.onHover((h4) => {
        if (h4) {
          this.textArrowBgColor = { id: -1, type: 10001, params: ['sys.color.interactive_hover'], bundleName: '', moduleName: '' };
        }
        else {
          this.textArrowBgColor = { id: -1, type: 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], bundleName: '', moduleName: '' };
        }
      });
      Row.onTouch((g4) => {
        if (g4.type === TouchType.Down) {
          if (u2.action) {
            u2.action();
          }
          this.textArrowBgColor = { id: -1, type: 10001, params: ['sys.color.interactive_pressed'], bundleName: '', moduleName: '' };
        }
        if (g4.type === TouchType.Up) {
          this.textArrowBgColor = { id: -1, type: 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], bundleName: '', moduleName: '' };
        }
      });
      Row.onKeyEvent((f4) => {
        if (f4.keyCode === KeyCode.KEYCODE_ENTER || f4.keyCode === KeyCode.KEYCODE_SPACE) {
          if (u2.action) {
            u2.action();
          }
        }
      });
      Row.onAreaChange((d4, e4) => {
        this.arrowWidth = Number(parseInt(e4.width.toString(), DEFAULT_VALUE));
      });
      ViewStackProcessor.visualState('focused');
      Row.border({
        radius: { id: -1, type: 10002, params: ['sys.float.corner_radius_level4'], bundleName: '', moduleName: '' },
        width: this.arrowWidth,
        color: { id: -1, type: 10001, params: ['sys.color.interactive_focus'], bundleName: '', moduleName: '' },
        style: BorderStyle.Solid,
      });
      Row.backgroundColor({ id: -1, type: 10001, params: ['sys.color.interactive_focus'], bundleName: '', moduleName: '' });
      ViewStackProcessor.visualState('pressed');
      Row.backgroundColor({ id: -1, type: 10001, params: ['sys.color.interactive_pressed'], bundleName: '', moduleName: '' });
      ViewStackProcessor.visualState('disabled');
      Row.opacity({ id: -1, type: 10002, params: ['sys.float.interactive_disable'], bundleName: '', moduleName: '' });
      ViewStackProcessor.visualState();
    }, Row);
    this.observeComponentCreation2((t3, u3) => {
      Row.create();
    }, Row);
    this.observeComponentCreation2((m3, n3) => {
      If.create();
      if (u2) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((r3, s3) => {
            Text.create(u2.value);
            __Text__secondaryTitleStyles({
              maxLines: SINGLE_LINE_NUM,
              fontWeight: FontWeight.Regular,
              alignment: Alignment.End,
            });
            Text.margin({
              right: { id: -1, type: 10002, params: ['sys.float.padding_level2'], bundleName: '', moduleName: '' },
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
    this.observeComponentCreation2((k3, l3) => {
      Image.create({ id: -1, type: 20000, params: ['sys.media.ohos_ic_public_arrow_right'], bundleName: '', moduleName: '' });
      Image.fillColor({ id: -1, type: 10001, params: ['sys.color.ohos_id_color_tertiary'], bundleName: '', moduleName: '' });
      Image.width(IMAGE_WIDTH);
      Image.height(IMAGE_HEIGHT_NUM);
      Image.focusable(true);
      Image.draggable(false);
    }, Image);
    Row.pop();
    Row.pop();
    this.observeComponentCreation2((d3, e3) => {
      If.create();
      if (this.textArrowFocus) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((i3, j3) => {
            Row.create();
            Row.height(BUTTON_SIZE);
            Row.width(this.arrowWidth);
            Row.hitTestBehavior(HitTestMode.None);
            Row.border({
              width: { id: -1, type: 10002, params: ['sys.float.outline_extra_larger'], bundleName: '', moduleName: '' },
              color: { id: -1, type: 10001, params: ['sys.color.interactive_focus'], bundleName: '', moduleName: '' },
            });
            Row.borderRadius({ id: -1, type: 10002, params: ['sys.float.corner_radius_level4'], bundleName: '', moduleName: '' });
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
  LoadingProcessStyle(m2 = null) {
    this.observeComponentCreation2((s2, t2) => {
      Row.create();
      Row.focusable(true);
      Row.constraintSize({ minWidth: this.flexWidth / DIVIDEND_NUM });
      Row.justifyContent(FlexAlign.End);
      Row.padding({
        top: { id: -1, type: 10002, params: ['sys.float.padding_level2'], bundleName: '', moduleName: '' },
        bottom: { id: -1, type: 10002, params: ['sys.float.padding_level2'], bundleName: '', moduleName: '' },
      });
      Row.margin({
        left: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.margin_right'], bundleName: '', moduleName: '' },
      });
    }, Row);
    this.observeComponentCreation2((p2, q2) => {
      LoadingProgress.create();
      LoadingProgress.width(IMAGE_HEIGHT_NUM);
      LoadingProgress.height(IMAGE_HEIGHT_NUM);
      LoadingProgress.color({ id: -1, type: 10001, params: ['sys.color.icon_secondary'], bundleName: '', moduleName: '' });
      LoadingProgress.focusable(true);
      LoadingProgress.onAppear(() => {
        this.isDuplicateLine = false;
      });
    }, LoadingProgress);
    Row.pop();
  }
  dummyFunction(h2 = null) {
    this.observeComponentCreation2((j2, k2) => {
      Row.create();
      Row.onAppear(() => {
        this.changeFlexAlign(FlexAlign.End);
      });
    }, Row);
    Row.pop();
  }
  changeFlexAlign(g2) {
    if (this.flexAlign === g2) {
      return;
    }
    this.flexAlign = g2;
  }
  rerender() {
    this.updateDirtyElements();
  }
}
class SingleIconStyle extends ViewPU {
  constructor(a2, b2, c2, d2 = -1, e2 = undefined, f2) {
    super(a2, c2, d2, f2);
    if (typeof e2 === 'function') {
      this.paramsGenerator_ = e2;
    }
    this.__bgColor = new ObservedPropertyObjectPU({ id: -1, type: 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], bundleName: '', moduleName: '' }, this, 'bgColor');
    this.__isFocus = new ObservedPropertySimplePU(false, this, 'isFocus');
    this.item = null;
    this.focusBorderWidth = BORDER_WIDTH;
    this.setInitiallyProvidedValue(b2);
  }
  setInitiallyProvidedValue(z1) {
    if (z1.bgColor !== undefined) {
      this.bgColor = z1.bgColor;
    }
    if (z1.isFocus !== undefined) {
      this.isFocus = z1.isFocus;
    }
    if (z1.item !== undefined) {
      this.item = z1.item;
    }
    if (z1.focusBorderWidth !== undefined) {
      this.focusBorderWidth = z1.focusBorderWidth;
    }
  }
  updateStateVars(y1) {
  }
  purgeVariableDependenciesOnElmtId(x1) {
    this.__bgColor.purgeDependencyOnElmtId(x1);
    this.__isFocus.purgeDependencyOnElmtId(x1);
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
  set bgColor(w1) {
    this.__bgColor.set(w1);
  }
  get isFocus() {
    return this.__isFocus.get();
  }
  set isFocus(v1) {
    this.__isFocus.set(v1);
  }
  initialRender() {
    this.observeComponentCreation2((e, f) => {
      If.create();
      if (this.item && this.item.iconOptions) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((j1, k1) => {
            Row.create();
            Row.focusable(true);
            Row.width(BUTTON_SIZE);
            Row.height(BUTTON_SIZE);
            Row.margin({
              bottom: { id: -1, type: 10002, params: ['sys.float.padding_level2'], bundleName: '', moduleName: '' },
            });
            Row.justifyContent(FlexAlign.Center);
            Row.borderRadius({ id: -1, type: 10002, params: ['sys.float.corner_radius_level4'], bundleName: '', moduleName: '' });
            Row.backgroundColor(ObservedObject.GetRawObject(this.bgColor));
            ViewStackProcessor.visualState('focused');
            Row.border({
              radius: { id: -1, type: 10002, params: ['sys.float.corner_radius_level4'], bundleName: '', moduleName: '' },
              width: this.focusBorderWidth,
              color: { id: -1, type: 10001, params: ['sys.color.interactive_focus'], bundleName: '', moduleName: '' },
              style: BorderStyle.Solid,
            });
            Row.backgroundColor({ id: -1, type: 10001, params: ['sys.color.interactive_focus'], bundleName: '', moduleName: '' });
            ViewStackProcessor.visualState('pressed');
            Row.backgroundColor({ id: -1, type: 10001, params: ['sys.color.interactive_pressed'], bundleName: '', moduleName: '' });
            ViewStackProcessor.visualState('disabled');
            Row.opacity({ id: -1, type: 10002, params: ['sys.float.interactive_disable'], bundleName: '', moduleName: '' });
            ViewStackProcessor.visualState();
            Row.onTouch((s1) => {
              var t1;
              var u1;
              if (s1.type === TouchType.Down) {
                if ((t1 = this.item) === null || t1 === void 0 ? void 0 : t1.action) {
                  (u1 = this.item) === null || u1 === void 0 ? void 0 : u1.action();
                }
                this.bgColor = { id: -1, type: 10001, params: ['sys.color.interactive_pressed'], bundleName: '', moduleName: '' };
              }
              if (s1.type === TouchType.Up) {
                this.bgColor = { id: -1, type: 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], bundleName: '', moduleName: '' };
              }
            });
            Row.onHover((r1) => {
              if (r1) {
                this.bgColor = { id: -1, type: 10001, params: ['sys.color.interactive_hover'], bundleName: '', moduleName: '' };
              }
              else {
                this.bgColor = { id: -1, type: 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], bundleName: '', moduleName: '' };
              }
            });
            Row.onKeyEvent((o1) => {
              var p1;
              var q1;
              if (o1.keyCode === KeyCode.KEYCODE_ENTER || o1.keyCode === KeyCode.KEYCODE_SPACE) {
                if ((p1 = this.item) === null || p1 === void 0 ? void 0 : p1.action) {
                  (q1 = this.item) === null || q1 === void 0 ? void 0 : q1.action();
                }
              }
            });
          }, Row);
          this.observeComponentCreation2((k, l) => {
            If.create();
            if (Util.isSymbolicResource(this.item.iconOptions.icon)) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation2((u, v) => {
                  var w;
                  var x;
                  var y;
                  var z;
                  var a1;
                  var b1;
                  var c1;
                  var d1;
                  var e1;
                  var f1;
                  var g1;
                  var h1;
                  var i1;
                  SymbolGlyph.create((w = this.item.iconOptions) === null || w === void 0 ? void 0 : w.icon);
                  SymbolGlyph.focusable(true);
                  SymbolGlyph.fontSize((z = (y = (x = this.item.iconOptions) === null || x === void 0 ? void 0 : x.symbolicIconOption) === null || y === void 0 ? void 0 : y.fontSize) !== null && z !== void 0 ? z : IMAGE_HEIGHT_NUM);
                  SymbolGlyph.fontColor((c1 = (b1 = (a1 = this.item.iconOptions) === null || a1 === void 0 ? void 0 : a1.symbolicIconOption) === null || b1 === void 0 ? void 0 : b1.fontColor) !== null && c1 !== void 0 ? c1 : [{ id: -1, type: 10001, params: ['sys.color.icon_primary'], bundleName: '', moduleName: '' }]);
                  SymbolGlyph.fontWeight((e1 = (d1 = this.item.iconOptions) === null || d1 === void 0 ? void 0 : d1.symbolicIconOption) === null || e1 === void 0 ? void 0 : e1.fontWeight);
                  SymbolGlyph.renderingStrategy((g1 = (f1 = this.item.iconOptions) === null || f1 === void 0 ? void 0 : f1.symbolicIconOption) === null || g1 === void 0 ? void 0 : g1.renderingStrategy);
                  SymbolGlyph.effectStrategy((i1 = (h1 = this.item.iconOptions) === null || h1 === void 0 ? void 0 : h1.symbolicIconOption) === null || i1 === void 0 ? void 0 : i1.effectStrategy);
                }, SymbolGlyph);
              });
            }
            else {
              this.ifElseBranchUpdateFunction(1, () => {
                this.observeComponentCreation2((o, p) => {
                  var q;
                  var r;
                  Image.create((r = (q = this.item) === null || q === void 0 ? void 0 : q.iconOptions) === null || r === void 0 ? void 0 : r.icon);
                  Image.fillColor({ id: -1, type: 10001, params: ['sys.color.icon_primary'], bundleName: '', moduleName: '' });
                  Image.width(IMAGE_HEIGHT_NUM);
                  Image.height(IMAGE_HEIGHT_NUM);
                  Image.focusable(true);
                }, Image);
              });
            }
          }, If);
          If.pop();
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
  rerender() {
    this.updateDirtyElements();
  }
}
class Util {
  static isSymbolicResource(b) {
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