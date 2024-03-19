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
(function (k13) {
  k13[k13.TEXT_ARROW = 0] = 'TEXT_ARROW';
  k13[k13.BUTTON = 1] = 'BUTTON';
  k13[k13.ICON_GROUP = 2] = 'ICON_GROUP';
  k13[k13.LOADING = 3] = 'LOADING';
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

function __Text__secondaryTitleStyles(i13) {
  let j13;
  Text.fontSize({ id: -1, type: 10002, params: ['sys.float.Subtitle_S'], bundleName: '', moduleName: '' });
  Text.fontColor((j13 = i13 === null || i13 === void 0 ? void 0 : i13.fontColor) !== null && j13 !== void 0 ? j13 :
    { id: -1, type: 10001, params: ['sys.color.font_secondary'], bundleName: '', moduleName: '' });
  Text.fontWeight(i13 === null || i13 === void 0 ? void 0 : i13.fontWeight);
  Text.maxLines(i13 === null || i13 === void 0 ? void 0 : i13.maxLines);
  Text.textOverflow({ overflow: TextOverflow.Ellipsis });
  Text.align(i13 === null || i13 === void 0 ? void 0 : i13.alignment);
}

function __Text__primaryTitleStyles(h13) {
  Text.fontSize({ id: -1, type: 10002, params: ['sys.float.Subtitle_L'], bundleName: '', moduleName: '' });
  Text.fontColor({ id: -1, type: 10001, params: ['sys.color.font_primary'], bundleName: '', moduleName: '' });
  Text.fontWeight(h13 === null || h13 === void 0 ? void 0 : h13.fontWeight);
  Text.maxLines(h13 === null || h13 === void 0 ? void 0 : h13.maxLines);
  Text.textOverflow({ overflow: TextOverflow.Ellipsis });
  Text.align(h13 === null || h13 === void 0 ? void 0 : h13.alignment);
}

export class SubHeader extends ViewPU {
  constructor(b13, c13, d13, e13 = -1, f13 = undefined, g13) {
    super(b13, d13, e13, g13);
    if (typeof f13 === 'function') {
      this.paramsGenerator_ = f13;
    }
    this.__icon = new SynchedPropertyObjectOneWayPU(c13.icon, this, 'icon');
    this.iconSymbolOptions = null;
    this.__primaryTitle = new SynchedPropertyObjectOneWayPU(c13.primaryTitle, this, 'primaryTitle');
    this.__secondaryTitle = new SynchedPropertyObjectOneWayPU(c13.secondaryTitle, this, 'secondaryTitle');
    this.__select = new SynchedPropertyObjectOneWayPU(c13.select, this, 'select');
    this.__operationType = new SynchedPropertySimpleOneWayPU(c13.operationType, this, 'operationType');
    this.operationItem = null;
    this.operationSymbolOptions = null;
    this.__isDuplicateLine = new ObservedPropertySimplePU(false, this, 'isDuplicateLine');
    this.__textArrowBgColor = new ObservedPropertyObjectPU({
      id: -1, type: 10001,
      params: ['sys.color.ohos_id_color_sub_background_transparent'], bundleName: '', moduleName: ''
    },
      this, 'textArrowBgColor');
    this.__buttonBgColor = new ObservedPropertyObjectPU({
      id: -1, type: 10001,
      params: ['sys.color.ohos_id_color_sub_background_transparent'], bundleName: '', moduleName: ''
    },
      this, 'buttonBgColor');
    this.__flexWidth = new ObservedPropertySimplePU(0, this, 'flexWidth');
    this.__textArrowFocus = new ObservedPropertySimplePU(false, this, 'textArrowFocus');
    this.__buttonFocus = new ObservedPropertySimplePU(false, this, 'buttonFocus');
    this.__textArrowStyleWidth = new ObservedPropertySimplePU(0, this, 'textArrowStyleWidth');
    this.__textArrowStyleHeight = new ObservedPropertySimplePU(0, this, 'textArrowStyleHeight');
    this.__buttonStyleWidth = new ObservedPropertySimplePU(0, this, 'buttonStyleWidth');
    this.__buttonStyleHeight = new ObservedPropertySimplePU(0, this, 'buttonStyleHeight');
    this.__iconTextStyleWidth = new ObservedPropertySimplePU(0, this, 'iconTextStyleWidth');
    this.__iconTextWidth = new ObservedPropertySimplePU(0, this, 'iconTextWidth');
    this.__iconWidth = new ObservedPropertySimplePU(0, this, 'iconWidth');
    this.focusBorderWidth = BORDER_WIDTH;
    this.__flexAlign = new ObservedPropertySimplePU(FlexAlign.SpaceBetween, this, 'flexAlign');
    this.setInitiallyProvidedValue(c13);
  }

  setInitiallyProvidedValue(a13) {
    if (a13.icon === undefined) {
      this.__icon.set(null);
    }
    if (a13.iconSymbolOptions !== undefined) {
      this.iconSymbolOptions = a13.iconSymbolOptions;
    }
    if (a13.primaryTitle === undefined) {
      this.__primaryTitle.set(null);
    }
    if (a13.secondaryTitle === undefined) {
      this.__secondaryTitle.set(null);
    }
    if (a13.select === undefined) {
      this.__select.set(null);
    }
    if (a13.operationType === undefined) {
      this.__operationType.set(OperationType.BUTTON);
    }
    if (a13.operationItem !== undefined) {
      this.operationItem = a13.operationItem;
    }
    if (a13.operationSymbolOptions !== undefined) {
      this.operationSymbolOptions = a13.operationSymbolOptions;
    }
    if (a13.isDuplicateLine !== undefined) {
      this.isDuplicateLine = a13.isDuplicateLine;
    }
    if (a13.textArrowBgColor !== undefined) {
      this.textArrowBgColor = a13.textArrowBgColor;
    }
    if (a13.buttonBgColor !== undefined) {
      this.buttonBgColor = a13.buttonBgColor;
    }
    if (a13.flexWidth !== undefined) {
      this.flexWidth = a13.flexWidth;
    }
    if (a13.textArrowFocus !== undefined) {
      this.textArrowFocus = a13.textArrowFocus;
    }
    if (a13.buttonFocus !== undefined) {
      this.buttonFocus = a13.buttonFocus;
    }
    if (a13.textArrowStyleWidth !== undefined) {
      this.textArrowStyleWidth = a13.textArrowStyleWidth;
    }
    if (a13.textArrowStyleHeight !== undefined) {
      this.textArrowStyleHeight = a13.textArrowStyleHeight;
    }
    if (a13.buttonStyleWidth !== undefined) {
      this.buttonStyleWidth = a13.buttonStyleWidth;
    }
    if (a13.buttonStyleHeight !== undefined) {
      this.buttonStyleHeight = a13.buttonStyleHeight;
    }
    if (a13.iconTextStyleWidth !== undefined) {
      this.iconTextStyleWidth = a13.iconTextStyleWidth;
    }
    if (a13.iconTextWidth !== undefined) {
      this.iconTextWidth = a13.iconTextWidth;
    }
    if (a13.iconWidth !== undefined) {
      this.iconWidth = a13.iconWidth;
    }
    if (a13.focusBorderWidth !== undefined) {
      this.focusBorderWidth = a13.focusBorderWidth;
    }
    if (a13.flexAlign !== undefined) {
      this.flexAlign = a13.flexAlign;
    }
  }

  updateStateVars(z12) {
    this.__icon.reset(z12.icon);
    this.__primaryTitle.reset(z12.primaryTitle);
    this.__secondaryTitle.reset(z12.secondaryTitle);
    this.__select.reset(z12.select);
    this.__operationType.reset(z12.operationType);
  }

  purgeVariableDependenciesOnElmtId(y12) {
    this.__icon.purgeDependencyOnElmtId(y12);
    this.__primaryTitle.purgeDependencyOnElmtId(y12);
    this.__secondaryTitle.purgeDependencyOnElmtId(y12);
    this.__select.purgeDependencyOnElmtId(y12);
    this.__operationType.purgeDependencyOnElmtId(y12);
    this.__isDuplicateLine.purgeDependencyOnElmtId(y12);
    this.__textArrowBgColor.purgeDependencyOnElmtId(y12);
    this.__buttonBgColor.purgeDependencyOnElmtId(y12);
    this.__flexWidth.purgeDependencyOnElmtId(y12);
    this.__textArrowFocus.purgeDependencyOnElmtId(y12);
    this.__buttonFocus.purgeDependencyOnElmtId(y12);
    this.__textArrowStyleWidth.purgeDependencyOnElmtId(y12);
    this.__textArrowStyleHeight.purgeDependencyOnElmtId(y12);
    this.__buttonStyleWidth.purgeDependencyOnElmtId(y12);
    this.__buttonStyleHeight.purgeDependencyOnElmtId(y12);
    this.__iconTextStyleWidth.purgeDependencyOnElmtId(y12);
    this.__iconTextWidth.purgeDependencyOnElmtId(y12);
    this.__iconWidth.purgeDependencyOnElmtId(y12);
    this.__flexAlign.purgeDependencyOnElmtId(y12);
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

  set icon(x12) {
    this.__icon.set(x12);
  }

  get primaryTitle() {
    return this.__primaryTitle.get();
  }

  set primaryTitle(w12) {
    this.__primaryTitle.set(w12);
  }

  get secondaryTitle() {
    return this.__secondaryTitle.get();
  }

  set secondaryTitle(v12) {
    this.__secondaryTitle.set(v12);
  }

  get select() {
    return this.__select.get();
  }

  set select(u12) {
    this.__select.set(u12);
  }

  get operationType() {
    return this.__operationType.get();
  }

  set operationType(t12) {
    this.__operationType.set(t12);
  }

  get isDuplicateLine() {
    return this.__isDuplicateLine.get();
  }

  set isDuplicateLine(s12) {
    this.__isDuplicateLine.set(s12);
  }

  get textArrowBgColor() {
    return this.__textArrowBgColor.get();
  }

  set textArrowBgColor(r12) {
    this.__textArrowBgColor.set(r12);
  }

  get buttonBgColor() {
    return this.__buttonBgColor.get();
  }

  set buttonBgColor(q12) {
    this.__buttonBgColor.set(q12);
  }

  get flexWidth() {
    return this.__flexWidth.get();
  }

  set flexWidth(p12) {
    this.__flexWidth.set(p12);
  }

  get textArrowFocus() {
    return this.__textArrowFocus.get();
  }

  set textArrowFocus(o12) {
    this.__textArrowFocus.set(o12);
  }

  get buttonFocus() {
    return this.__buttonFocus.get();
  }

  set buttonFocus(n12) {
    this.__buttonFocus.set(n12);
  }

  get textArrowStyleWidth() {
    return this.__textArrowStyleWidth.get();
  }

  set textArrowStyleWidth(m12) {
    this.__textArrowStyleWidth.set(m12);
  }

  get textArrowStyleHeight() {
    return this.__textArrowStyleHeight.get();
  }

  set textArrowStyleHeight(l12) {
    this.__textArrowStyleHeight.set(l12);
  }

  get buttonStyleWidth() {
    return this.__buttonStyleWidth.get();
  }

  set buttonStyleWidth(k12) {
    this.__buttonStyleWidth.set(k12);
  }

  get buttonStyleHeight() {
    return this.__buttonStyleHeight.get();
  }

  set buttonStyleHeight(j12) {
    this.__buttonStyleHeight.set(j12);
  }

  get iconTextStyleWidth() {
    return this.__iconTextStyleWidth.get();
  }

  set iconTextStyleWidth(i12) {
    this.__iconTextStyleWidth.set(i12);
  }

  get iconTextWidth() {
    return this.__iconTextWidth.get();
  }

  set iconTextWidth(h12) {
    this.__iconTextWidth.set(h12);
  }

  get iconWidth() {
    return this.__iconWidth.get();
  }

  set iconWidth(g12) {
    this.__iconWidth.set(g12);
  }

  get flexAlign() {
    return this.__flexAlign.get();
  }

  set flexAlign(f12) {
    this.__flexAlign.set(f12);
  }

  initialRender() {
    this.observeComponentCreation2((z11, a12) => {
      Flex.create({ justifyContent: this.flexAlign, alignItems: ItemAlign.End });
      Flex.focusable(true);
      Flex.onAreaChange((c12, d12) => {
        let e12 = Number(parseInt(d12.width.toString(), DEFAULT_VALUE));
        this.flexWidth = e12;
      });
      Flex.constraintSize({ minHeight: this.isDuplicateLine ? DOUBLE_LINE_HEIGHT : SINGLE_LINE_HEIGHT });
    }, Flex);
    this.leftArea.bind(this)();
    this.rightArea.bind(this)();
    Flex.pop();
  }

  leftArea(o11 = null) {
    this.observeComponentCreation2((q11, r11) => {
      If.create();
      if (this.secondaryTitle && this.icon) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.IconSecondaryTitleStyle.bind(this)(makeBuilderParameterProxy('IconSecondaryTitleStyle', {
            content: () => this.secondaryTitle, iconOptions: () => ({
              icon: this.icon,
              symbolicIconOption: this.iconSymbolOptions,
            })
          }));
        });
      }
      else if (this.secondaryTitle && this.primaryTitle) {
        this.ifElseBranchUpdateFunction(1, () => {
          this.SubTitleStyle.bind(this)(makeBuilderParameterProxy('SubTitleStyle',
            { content: () => this.primaryTitle, subContent: () => this.secondaryTitle }));
        });
      }
      else if (this.secondaryTitle) {
        this.ifElseBranchUpdateFunction(2, () => {
          this.SecondTitleStyle.bind(this)(makeBuilderParameterProxy('SecondTitleStyle',
            { content: () => this.secondaryTitle }));
        });
      }
      else if (this.select) {
        this.ifElseBranchUpdateFunction(3, () => {
          this.SelectStyle.bind(this)(ObservedObject.GetRawObject(this.select));
        });
      }
      else if (this.primaryTitle) {
        this.ifElseBranchUpdateFunction(4, () => {
          this.PrimaryTitleStyle.bind(this)(makeBuilderParameterProxy('PrimaryTitleStyle',
            { content: () => this.primaryTitle }));
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

  rightArea(t10 = null) {
    this.observeComponentCreation2((k11, l11) => {
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
    this.observeComponentCreation2((g11, h11) => {
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
    this.observeComponentCreation2((c11, d11) => {
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
    this.observeComponentCreation2((y10, z10) => {
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

  IconSecondaryTitleStyle(b9, c9 = null) {
    this.observeComponentCreation2((n10, o10) => {
      Row.create();
      Row.width(this.flexWidth / DIVIDEND_NUM * DIVIDEND_NUM_TWO);
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
      Row.onAreaChange((r10, s10) => {
        this.iconTextStyleWidth = Number(s10.width);
        this.updateMaxIconTextWidth();
      });
    }, Row);
    this.observeComponentCreation2((i10, j10) => {
      Row.create();
      Row.onAreaChange((l10, m10) => {
        this.iconWidth = Number(m10.width);
        this.updateMaxIconTextWidth();
      });
    }, Row);
    this.observeComponentCreation2((j9, k9) => {
      let l9;
      If.create();
      if (Util.isSymbolResource((l9 = b9.iconOptions) === null || l9 === void 0 ? void 0 : l9.icon)) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((t9, u9) => {
            let v9;
            let w9;
            let x9;
            let y9;
            let z9;
            let a10;
            let b10;
            let c10;
            let d10;
            let e10;
            let f10;
            let g10;
            let h10;
            SymbolGlyph.create((v9 = b9.iconOptions) === null || v9 === void 0 ? void 0 : v9.icon);
            SymbolGlyph.focusable(true);
            SymbolGlyph.fontSize((y9 = (x9 = (w9 = b9.iconOptions) === null || w9 === void 0 ? void 0 :
              w9.symbolicIconOption) === null || x9 === void 0 ? void 0 : x9.fontSize) !== null && y9 !== void 0 ?
              y9 : IMAGE_WIDTH_NUM);
            SymbolGlyph.fontColor((b10 = (a10 = (z9 = b9.iconOptions) === null || z9 === void 0 ? void 0 :
              z9.symbolicIconOption) === null || a10 === void 0 ? void 0 : a10.fontColor) !== null && b10 !== void 0 ?
              b10 : [{ id: -1, type: 10001, params: ['sys.color.icon_secondary'], bundleName: '', moduleName: '' }]);
            SymbolGlyph.fontWeight((d10 =
              (c10 = b9.iconOptions) === null || c10 === void 0 ? void 0 : c10.symbolicIconOption) === null ||
              d10 === void 0 ? void 0 : d10.fontWeight);
            SymbolGlyph.renderingStrategy((f10 =
              (e10 = b9.iconOptions) === null || e10 === void 0 ? void 0 : e10.symbolicIconOption) === null ||
              f10 === void 0 ? void 0 : f10.renderingStrategy);
            SymbolGlyph.effectStrategy((h10 =
              (g10 = b9.iconOptions) === null || g10 === void 0 ? void 0 : g10.symbolicIconOption) === null ||
              h10 === void 0 ? void 0 : h10.effectStrategy);
            SymbolGlyph.margin({
              right: {
                id: -1, type: 10002, params: ['sys.float.padding_level4'],
                bundleName: '', moduleName: ''
              }
            });
          }, SymbolGlyph);
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((o9, p9) => {
            let q9;
            Image.create((q9 = b9.iconOptions) === null || q9 === void 0 ? void 0 : q9.icon);
            Image.width(IMAGE_WIDTH_NUM);
            Image.height(IMAGE_WIDTH_NUM);
            Image.margin({
              right: {
                id: -1, type: 10002, params: ['sys.float.padding_level4'],
                bundleName: '', moduleName: ''
              }
            });
          }, Image);
        });
      }
    }, If);
    If.pop();
    Row.pop();
    this.observeComponentCreation2((h9, i9) => {
      Text.create(b9.content);
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

  SubTitleStyle(p8, q8 = null) {
    this.observeComponentCreation2((y8, z8) => {
      Column.create();
      Column.width(this.flexWidth / DIVIDEND_NUM * DIVIDEND_NUM_TWO);
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
    this.observeComponentCreation2((w8, x8) => {
      Text.create(p8.content);
      __Text__primaryTitleStyles({
        fontWeight: FontWeight.Medium,
        maxLines: SINGLE_LINE_NUM,
        alignment: Alignment.Start,
      });
    }, Text);
    Text.pop();
    this.observeComponentCreation2((u8, v8) => {
      Text.create(p8.subContent);
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

  SecondTitleStyle(g8, h8 = null) {
    this.observeComponentCreation2((n8, o8) => {
      Column.create();
      Column.alignItems(HorizontalAlign.Start);
      Column.width(this.flexWidth / DIVIDEND_NUM * DIVIDEND_NUM_TWO);
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
    this.observeComponentCreation2((k8, l8) => {
      Text.create(g8.content);
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

  SelectStyle(u7, v7 = null) {
    this.observeComponentCreation2((d8, e8) => {
      Column.create();
      Column.width(this.flexWidth / DIVIDEND_NUM * DIVIDEND_NUM_TWO);
      Column.alignItems(HorizontalAlign.Start);
      Column.margin({
        left: { id: -1, type: 10002, params: ['sys.float.margin_left'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.margin_right'], bundleName: '', moduleName: '' },
      });
      Column.onAppear(() => {
        this.isDuplicateLine = false;
        this.changeFlexAlign(FlexAlign.SpaceBetween);
      });
    }, Column);
    this.observeComponentCreation2((y7, z7) => {
      Select.create(u7.options);
      Select.selected(u7.selected);
      Select.value(u7.value);
      Select.onSelect((b8, c8) => {
        if (u7.onSelect) {
          u7.onSelect(b8, c8);
        }
      });
      Select.font({
        size: { id: -1, type: 10002, params: ['sys.float.Body_L'], bundleName: '', moduleName: '' },
        weight: FontWeight.Medium,
      });
    }, Select);
    Select.pop();
    Column.pop();
  }

  PrimaryTitleStyle(l7, m7 = null) {
    this.observeComponentCreation2((s7, t7) => {
      Column.create();
      Column.width(this.flexWidth / DIVIDEND_NUM * DIVIDEND_NUM_TWO);
      Column.alignItems(HorizontalAlign.Start);
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
    this.observeComponentCreation2((p7, q7) => {
      Text.create(l7.content);
      __Text__primaryTitleStyles({
        fontWeight: FontWeight.Medium,
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

  ButtonStyle(z5, a6 = null) {
    this.observeComponentCreation2((j7, k7) => {
      Row.create();
      Row.margin({
        left: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.margin_right'], bundleName: '', moduleName: '' },
      });
      Row.width(this.flexWidth / DIVIDEND_NUM);
      Row.justifyContent(FlexAlign.End);
      Row.focusable(true);
    }, Row);
    this.observeComponentCreation2((h7, i7) => {
      Stack.create();
      Stack.focusable(true);
    }, Stack);
    this.observeComponentCreation2((e6, f6) => {
      If.create();
      if (z5) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((u6, v6) => {
            Row.create();
            Row.backgroundColor(ObservedObject.GetRawObject(this.buttonBgColor));
            Row.focusable(true);
            Row.constraintSize({ minHeight: BUTTON_HEIGHT });
            Row.justifyContent(FlexAlign.End);
            Row.borderRadius({
              id: -1, type: 10002, params: ['sys.float.corner_radius_level4'],
              bundleName: '', moduleName: ''
            });
            ViewStackProcessor.visualState('focused');
            Row.border({
              radius: {
                id: -1, type: 10002, params: ['sys.float.corner_radius_level4'],
                bundleName: '', moduleName: ''
              },
              width: this.buttonStyleWidth,
              color: { id: -1, type: 10001, params: ['sys.color.interactive_focus'], bundleName: '', moduleName: '' },
              style: BorderStyle.Solid,
            });
            Row.backgroundColor({
              id: -1, type: 10001, params: ['sys.color.interactive_focus'],
              bundleName: '', moduleName: ''
            });
            ViewStackProcessor.visualState('pressed');
            Row.backgroundColor({
              id: -1, type: 10001, params: ['sys.color.interactive_pressed'],
              bundleName: '', moduleName: ''
            });
            ViewStackProcessor.visualState('disabled');
            Row.opacity({
              id: -1, type: 10002, params: ['sys.float.interactive_disable'],
              bundleName: '', moduleName: ''
            });
            ViewStackProcessor.visualState();
            Row.onFocus(() => {
              this.buttonFocus = true;
              this.buttonBgColor = {
                id: -1, type: 10001, params: ['sys.color.interactive_focus'],
                bundleName: '', moduleName: ''
              };
            });
            Row.onBlur(() => {
              this.buttonFocus = false;
            });
            Row.onHover((g7) => {
              if (g7) {
                this.buttonBgColor = {
                  id: -1, type: 10001, params: ['sys.color.interactive_hover'],
                  bundleName: '', moduleName: ''
                };
              }
              else {
                this.buttonBgColor = {
                  id: -1, type: 10001,
                  params: ['sys.color.ohos_id_color_sub_background_transparent'], bundleName: '', moduleName: ''
                };
              }
            });
            Row.onTouch((f7) => {
              if (f7.type === TouchType.Down) {
                if (z5.action) {
                  z5.action();
                }
                this.buttonBgColor = {
                  id: -1, type: 10001, params: ['sys.color.interactive_pressed'],
                  bundleName: '', moduleName: ''
                };
              }
              if (f7.type === TouchType.Up) {
                this.buttonBgColor = {
                  id: -1, type: 10001,
                  params: ['sys.color.ohos_id_color_sub_background_transparent'], bundleName: '', moduleName: ''
                };
              }
            });
            Row.onKeyEvent((e7) => {
              if (e7.keyCode === KeyCode.KEYCODE_ENTER || e7.keyCode === KeyCode.KEYCODE_SPACE) {
                if (z5.action) {
                  z5.action();
                }
              }
            });
            Row.onAreaChange((c7, d7) => {
              this.buttonStyleWidth = Number(d7.width);
              this.buttonStyleHeight = Number(d7.height);
            });
          }, Row);
          this.observeComponentCreation2((s6, t6) => {
            Text.create(z5.value);
            __Text__secondaryTitleStyles({
              fontWeight: FontWeight.Medium,
              maxLines: SINGLE_LINE_NUM,
              fontColor: { id: -1, type: 10001, params: ['sys.color.font_emphasize'], bundleName: '', moduleName: '' },
            });
            Text.focusable(true);
          }, Text);
          Text.pop();
          Row.pop();
          this.observeComponentCreation2((l6, m6) => {
            If.create();
            if (this.buttonFocus) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation2((q6, r6) => {
                  Row.create();
                  Row.height(this.buttonStyleHeight);
                  Row.width(this.buttonStyleWidth);
                  Row.hitTestBehavior(HitTestMode.None);
                  Row.border({
                    width: {
                      id: -1, type: 10002,
                      params: ['sys.float.outline_extra_larger'], bundleName: '', moduleName: ''
                    },
                    color: {
                      id: -1, type: 10001,
                      params: ['sys.color.interactive_focus'], bundleName: '', moduleName: ''
                    },
                  });
                  Row.borderRadius({
                    id: -1, type: 10002,
                    params: ['sys.float.corner_radius_level4'], bundleName: '', moduleName: ''
                  });
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

  IconGroupStyle(o4, p4 = null) {
    this.observeComponentCreation2((x5, y5) => {
      Row.create();
      Row.justifyContent(FlexAlign.End);
      Row.width(this.flexWidth / DIVIDEND_NUM);
      Row.focusable(true);
      Row.margin({
        left: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.padding_level6'], bundleName: '', moduleName: '' },
      });
    }, Row);
    this.observeComponentCreation2((s4, t4) => {
      ForEach.create();
      const u4 = (w4, x4) => {
        const y4 = w4;
        this.observeComponentCreation2((a5, b5) => {
          If.create();
          if (Util.isResourceType(y4.value)) {
            this.ifElseBranchUpdateFunction(0, () => {
              this.observeComponentCreation2((f5, g5) => {
                If.create();
                if (x4 === INDEX_ZERO) {
                  this.ifElseBranchUpdateFunction(0, () => {
                    {
                      this.observeComponentCreation2((t5, u5) => {
                        if (u5) {
                          let v5 = () => {
                            return {
                              item: {
                                iconOptions: {
                                  icon: y4.value,
                                  symbolicIconOption:
                                    this.operationSymbolOptions && this.operationSymbolOptions.length > x4 ?
                                      this.operationSymbolOptions[x4] : null,
                                },
                                action: y4.action,
                              }
                            };
                          };
                          ViewPU.create(new SingleIconStyle(this, {
                            item: {
                              iconOptions: {
                                icon: y4.value,
                                symbolicIconOption:
                                  this.operationSymbolOptions && this.operationSymbolOptions.length > x4 ?
                                    this.operationSymbolOptions[x4] : null,
                              },
                              action: y4.action,
                            }
                          }, undefined, t5, v5,
                            { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 466 }));
                        }
                        else {
                          this.updateStateVarsOfChildByElmtId(t5, {});
                        }
                      }, { name: 'SingleIconStyle' });
                    }
                  });
                }
                else if (x4 === INDEX_ONE || x4 === INDEX_TWO) {
                  this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((p5, q5) => {
                      __Common__.create();
                      __Common__.margin({
                        left: {
                          id: -1, type: 10002, params: ['sys.float.padding_level4'],
                          bundleName: '', moduleName: ''
                        },
                      });
                    }, __Common__);
                    {
                      this.observeComponentCreation2((l5, m5) => {
                        if (m5) {
                          let n5 = () => {
                            return {
                              item: {
                                action: y4.action,
                                iconOptions: {
                                  icon: y4.value,
                                  symbolicIconOption:
                                    this.operationSymbolOptions && this.operationSymbolOptions.length > x4 ?
                                      this.operationSymbolOptions[x4] : null,
                                },
                              }
                            };
                          };
                          ViewPU.create(new SingleIconStyle(this, {
                            item: {
                              action: y4.action,
                              iconOptions: {
                                icon: y4.value,
                                symbolicIconOption:
                                  this.operationSymbolOptions && this.operationSymbolOptions.length > x4 ?
                                    this.operationSymbolOptions[x4] : null,
                              },
                            }
                          }, undefined, l5, n5,
                            { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 477 }));
                        }
                        else {
                          this.updateStateVarsOfChildByElmtId(l5, {});
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
      this.forEachUpdateFunction(s4, o4, u4, undefined, true, false);
    }, ForEach);
    ForEach.pop();
    Row.pop();
  }

  TextArrowStyle(e3, f3 = null) {
    this.observeComponentCreation2((m4, n4) => {
      Row.create();
      Row.focusable(true);
      Row.width(this.flexWidth / DIVIDEND_NUM);
      Row.justifyContent(FlexAlign.End);
      Row.margin({
        left: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
      });
    }, Row);
    this.observeComponentCreation2((k4, l4) => {
      Stack.create();
    }, Stack);
    this.observeComponentCreation2((x3, y3) => {
      Row.create();
      Row.borderRadius({
        id: -1, type: 10002, params: ['sys.float.corner_radius_level4'],
        bundleName: '', moduleName: ''
      });
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
        left: { id: -1, type: 10002, params: ['sys.float.padding_level2'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
        top: { id: -1, type: 10002, params: ['sys.float.padding_level2'], bundleName: '', moduleName: '' },
        bottom: { id: -1, type: 10002, params: ['sys.float.padding_level2'], bundleName: '', moduleName: '' },
      });
      Row.onHover((j4) => {
        if (j4) {
          this.textArrowBgColor = {
            id: -1, type: 10001, params: ['sys.color.interactive_hover'],
            bundleName: '', moduleName: ''
          };
        }
        else {
          this.textArrowBgColor = {
            id: -1, type: 10001,
            params: ['sys.color.ohos_id_color_sub_background_transparent'], bundleName: '', moduleName: ''
          };
        }
      });
      Row.onTouch((i4) => {
        if (i4.type === TouchType.Down) {
          if (e3.action) {
            e3.action();
          }
          this.textArrowBgColor = {
            id: -1, type: 10001, params: ['sys.color.interactive_pressed'],
            bundleName: '', moduleName: ''
          };
        }
        if (i4.type === TouchType.Up) {
          this.textArrowBgColor = {
            id: -1, type: 10001,
            params: ['sys.color.ohos_id_color_sub_background_transparent'], bundleName: '', moduleName: ''
          };
        }
      });
      Row.onKeyEvent((h4) => {
        if (h4.keyCode === KeyCode.KEYCODE_ENTER || h4.keyCode === KeyCode.KEYCODE_SPACE) {
          if (e3.action) {
            e3.action();
          }
        }
      });
      Row.onAreaChange((f4, g4) => {
        this.textArrowStyleWidth = Number(g4.width);
        this.textArrowStyleHeight = Number(g4.height);
      });
    }, Row);
    this.observeComponentCreation2((q3, r3) => {
      If.create();
      if (e3) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((v3, w3) => {
            Text.create(e3.value);
            __Text__secondaryTitleStyles({
              maxLines: SINGLE_LINE_NUM,
              fontWeight: FontWeight.Regular,
              alignment: Alignment.End,
            });
            Text.margin({
              right: { id: -1, type: 10002, params: ['sys.float.padding_level2'], bundleName: '', moduleName: '' },
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
    this.observeComponentCreation2((o3, p3) => {
      Image.create({
        id: -1, type: 20000, params: ['sys.media.ohos_ic_public_arrow_right'],
        bundleName: '', moduleName: ''
      });
      Image.fillColor({
        id: -1, type: 10001, params: ['sys.color.ohos_id_color_tertiary'],
        bundleName: '', moduleName: ''
      });
      Image.width(ARROW_WIDTH);
      Image.height(IMAGE_HEIGHT_NUM);
      Image.focusable(true);
      Image.draggable(false);
    }, Image);
    Row.pop();
    this.observeComponentCreation2((m3, n3) => {
      Row.create();
      Row.height(this.textArrowStyleHeight);
      Row.width(this.textArrowStyleWidth);
      Row.hitTestBehavior(HitTestMode.None);
      Row.border({
        radius: { id: -1, type: 10002, params: ['sys.float.corner_radius_level4'], bundleName: '', moduleName: '' },
        width: { id: -1, type: 10002, params: ['sys.float.outline_extra_larger'], bundleName: '', moduleName: '' },
        color: { id: -1, type: 10001, params: ['sys.color.interactive_focus'], bundleName: '', moduleName: '' },
      });
      ViewStackProcessor.visualState('focused');
      Row.border({
        radius: { id: -1, type: 10002, params: ['sys.float.corner_radius_level4'], bundleName: '', moduleName: '' },
        width: { id: -1, type: 10002, params: ['sys.float.outline_extra_larger'], bundleName: '', moduleName: '' },
        color: { id: -1, type: 10001, params: ['sys.color.interactive_focus'], bundleName: '', moduleName: '' },
      });
      Row.backgroundColor({
        id: -1, type: 10001, params: ['sys.color.interactive_focus'],
        bundleName: '', moduleName: ''
      });
      ViewStackProcessor.visualState('pressed');
      Row.backgroundColor({
        id: -1, type: 10001, params: ['sys.color.interactive_pressed'],
        bundleName: '', moduleName: ''
      });
      ViewStackProcessor.visualState('disabled');
      Row.opacity({ id: -1, type: 10002, params: ['sys.float.interactive_disable'], bundleName: '', moduleName: '' });
      ViewStackProcessor.visualState('normal');
      Row.border({
        radius: { id: -1, type: 10002, params: ['sys.float.corner_radius_level4'], bundleName: '', moduleName: '' },
        width: { id: -1, type: 10002, params: ['sys.float.border_none'], bundleName: '', moduleName: '' },
        color: {
          id: -1, type: 10001, params: ['sys.color.ohos_id_color_focused_outline_transparent'],
          bundleName: '', moduleName: ''
        },
      });
      ViewStackProcessor.visualState();
    }, Row);
    Row.pop();
    Stack.pop();
    Row.pop();
  }

  LoadingProcessStyle(w2 = null) {
    this.observeComponentCreation2((c3, d3) => {
      Row.create();
      Row.focusable(true);
      Row.width(this.flexWidth / DIVIDEND_NUM);
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
    this.observeComponentCreation2((z2, a3) => {
      LoadingProgress.create();
      LoadingProgress.width(IMAGE_HEIGHT_NUM);
      LoadingProgress.height(IMAGE_HEIGHT_NUM);
      LoadingProgress.color({
        id: -1, type: 10001, params: ['sys.color.icon_secondary'],
        bundleName: '', moduleName: ''
      });
      LoadingProgress.focusable(true);
      LoadingProgress.onAppear(() => {
        this.isDuplicateLine = false;
      });
    }, LoadingProgress);
    Row.pop();
  }

  dummyFunction(r2 = null) {
    this.observeComponentCreation2((t2, u2) => {
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
    hilog.debug(122, 'tytyty ', `this.iconTextMaxWidth : ${this.iconTextWidth}`);
  }

  changeFlexAlign(q2) {
    if (this.flexAlign === q2) {
      return;
    }
    this.flexAlign = q2;
  }

  rerender() {
    this.updateDirtyElements();
  }
}

class SingleIconStyle extends ViewPU {
  constructor(k2, l2, m2, n2 = -1, o2 = undefined, p2) {
    super(k2, m2, n2, p2);
    if (typeof o2 === 'function') {
      this.paramsGenerator_ = o2;
    }
    this.__bgColor = new ObservedPropertyObjectPU({
      id: -1, type: 10001,
      params: ['sys.color.ohos_id_color_sub_background_transparent'], bundleName: '', moduleName: ''
    }, this, 'bgColor');
    this.__isFocus = new ObservedPropertySimplePU(false, this, 'isFocus');
    this.item = null;
    this.focusBorderWidth = BORDER_WIDTH;
    this.setInitiallyProvidedValue(l2);
  }

  setInitiallyProvidedValue(j2) {
    if (j2.bgColor !== undefined) {
      this.bgColor = j2.bgColor;
    }
    if (j2.isFocus !== undefined) {
      this.isFocus = j2.isFocus;
    }
    if (j2.item !== undefined) {
      this.item = j2.item;
    }
    if (j2.focusBorderWidth !== undefined) {
      this.focusBorderWidth = j2.focusBorderWidth;
    }
  }

  updateStateVars(i2) {
  }

  purgeVariableDependenciesOnElmtId(h2) {
    this.__bgColor.purgeDependencyOnElmtId(h2);
    this.__isFocus.purgeDependencyOnElmtId(h2);
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

  set bgColor(g2) {
    this.__bgColor.set(g2);
  }

  get isFocus() {
    return this.__isFocus.get();
  }

  set isFocus(f2) {
    this.__isFocus.set(f2);
  }

  initialRender() {
    this.observeComponentCreation2((o1, p1) => {
      If.create();
      if (this.item && this.item.iconOptions) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((t1, u1) => {
            Row.create();
            Row.focusable(true);
            Row.width(BUTTON_SIZE);
            Row.height(BUTTON_SIZE);
            Row.margin({
              bottom: { id: -1, type: 10002, params: ['sys.float.padding_level2'], bundleName: '', moduleName: '' },
            });
            Row.justifyContent(FlexAlign.Center);
            Row.borderRadius({
              id: -1, type: 10002, params: ['sys.float.corner_radius_level4'],
              bundleName: '', moduleName: ''
            });
            Row.backgroundColor(ObservedObject.GetRawObject(this.bgColor));
            ViewStackProcessor.visualState('focused');
            Row.border({
              radius: {
                id: -1, type: 10002, params: ['sys.float.corner_radius_level4'],
                bundleName: '', moduleName: ''
              },
              width: this.focusBorderWidth,
              color: { id: -1, type: 10001, params: ['sys.color.interactive_focus'], bundleName: '', moduleName: '' },
              style: BorderStyle.Solid,
            });
            Row.backgroundColor({
              id: -1, type: 10001, params: ['sys.color.interactive_focus'],
              bundleName: '', moduleName: ''
            });
            ViewStackProcessor.visualState('pressed');
            Row.backgroundColor({
              id: -1, type: 10001, params: ['sys.color.interactive_pressed'],
              bundleName: '', moduleName: ''
            });
            ViewStackProcessor.visualState('disabled');
            Row.opacity({
              id: -1, type: 10002, params: ['sys.float.interactive_disable'],
              bundleName: '', moduleName: ''
            });
            ViewStackProcessor.visualState();
            Row.onTouch((c2) => {
              let d2;
              let e2;
              if (c2.type === TouchType.Down) {
                if ((d2 = this.item) === null || d2 === void 0 ? void 0 : d2.action) {
                  (e2 = this.item) === null || e2 === void 0 ? void 0 : e2.action();
                }
                this.bgColor = {
                  id: -1, type: 10001, params: ['sys.color.interactive_pressed'],
                  bundleName: '', moduleName: ''
                };
              }
              if (c2.type === TouchType.Up) {
                this.bgColor = {
                  id: -1, type: 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'],
                  bundleName: '', moduleName: ''
                };
              }
            });
            Row.onHover((b2) => {
              if (b2) {
                this.bgColor = {
                  id: -1, type: 10001, params: ['sys.color.interactive_hover'],
                  bundleName: '', moduleName: ''
                };
              }
              else {
                this.bgColor = {
                  id: -1, type: 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'],
                  bundleName: '', moduleName: ''
                };
              }
            });
            Row.onKeyEvent((y1) => {
              let z1;
              let a2;
              if (y1.keyCode === KeyCode.KEYCODE_ENTER || y1.keyCode === KeyCode.KEYCODE_SPACE) {
                if ((z1 = this.item) === null || z1 === void 0 ? void 0 : z1.action) {
                  (a2 = this.item) === null || a2 === void 0 ? void 0 : a2.action();
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
                this.observeComponentCreation2((y, z) => {
                  let a1;
                  let b1;
                  let c1;
                  let d1;
                  let e1;
                  let f1;
                  let g1;
                  let h1;
                  let i1;
                  let j1;
                  let k1;
                  let l1;
                  let m1;
                  SymbolGlyph.create((a1 = this.item.iconOptions) === null || a1 === void 0 ? void 0 : a1.icon);
                  SymbolGlyph.focusable(true);
                  SymbolGlyph.fontSize((d1 = (c1 = (b1 = this.item.iconOptions) === null || b1 === void 0 ? void 0 :
                    b1.symbolicIconOption) === null || c1 === void 0 ? void 0 : c1.fontSize) !== null && d1 !== void 0 ?
                    d1 : IMAGE_HEIGHT_NUM);
                  SymbolGlyph.fontColor((g1 = (f1 = (e1 = this.item.iconOptions) === null || e1 === void 0 ? void 0 :
                    e1.symbolicIconOption) === null || f1 === void 0 ? void 0 : f1.fontColor) !== null && g1 !== void 0 ?
                    g1 : [{ id: -1, type: 10001, params: ['sys.color.icon_primary'], bundleName: '', moduleName: '' }]);
                  SymbolGlyph.fontWeight((i1 =
                    (h1 = this.item.iconOptions) === null || h1 === void 0 ? void 0 : h1.symbolicIconOption) === null ||
                    i1 === void 0 ? void 0 : i1.fontWeight);
                  SymbolGlyph.renderingStrategy((k1 =
                    (j1 = this.item.iconOptions) === null || j1 === void 0 ? void 0 : j1.symbolicIconOption) === null ||
                    k1 === void 0 ? void 0 : k1.renderingStrategy);
                  SymbolGlyph.effectStrategy((m1 = (l1 = this.item.iconOptions) === null || l1 === void 0 ? void 0 :
                    l1.symbolicIconOption) === null || m1 === void 0 ? void 0 : m1.effectStrategy);
                }, SymbolGlyph);
              });
            }
            else {
              this.ifElseBranchUpdateFunction(1, () => {
                this.observeComponentCreation2((s, t) => {
                  let u;
                  let v;
                  Image.create((v = (u = this.item) === null || u === void 0 ? void 0 : u.iconOptions) === null ||
                    v === void 0 ? void 0 : v.icon);
                  Image.fillColor({
                    id: -1, type: 10001, params: ['sys.color.icon_primary'],
                    bundleName: '', moduleName: ''
                  });
                  Image.width(IMAGE_HEIGHT_NUM);
                  Image.height(IMAGE_HEIGHT_NUM);
                  Image.focusable(true);
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