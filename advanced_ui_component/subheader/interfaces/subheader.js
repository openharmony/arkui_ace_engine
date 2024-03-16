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
const DIVIDEND_NUM_TWO = 2;
const SINGLE_LINE_NUM = 1;
const DOUBLE_LINE_NUM = 2;
const INDEX_ZERO = 0;
const INDEX_ONE = 1;
const INDEX_TWO = 2;
const RESOURCE_TYPE_SYMBOL = 40000;
const DEFAULT_VALUE = 0;

export var OperationType;
(function (f13) {
  f13[f13.TEXT_ARROW = 0] = 'TEXT_ARROW';
  f13[f13.BUTTON = 1] = 'BUTTON';
  f13[f13.ICON_GROUP = 2] = 'ICON_GROUP';
  f13[f13.LOADING = 3] = 'LOADING';
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

function __Text__secondaryTitleStyles(d13) {
  let e13;
  Text.fontSize({ id: -1, type: 10002, params: ['sys.float.Subtitle_S'], bundleName: '', moduleName: '' });
  Text.fontColor((e13 = d13 === null || d13 === void 0 ? void 0 : d13.fontColor) !== null && e13 !== void 0 ?
    e13 : { id: -1, type: 10001, params: ['sys.color.font_secondary'], bundleName: '', moduleName: '' });
  Text.fontWeight(d13 === null || d13 === void 0 ? void 0 : d13.fontWeight);
  Text.maxLines(d13 === null || d13 === void 0 ? void 0 : d13.maxLines);
  Text.textOverflow({ overflow: TextOverflow.Ellipsis });
  Text.align(d13 === null || d13 === void 0 ? void 0 : d13.alignment);
}

function __Text__primaryTitleStyles(c13) {
  Text.fontSize({ id: -1, type: 10002, params: ['sys.float.Subtitle_L'], bundleName: '', moduleName: '' });
  Text.fontColor({ id: -1, type: 10001, params: ['sys.color.font_primary'], bundleName: '', moduleName: '' });
  Text.fontWeight(c13 === null || c13 === void 0 ? void 0 : c13.fontWeight);
  Text.maxLines(c13 === null || c13 === void 0 ? void 0 : c13.maxLines);
  Text.textOverflow({ overflow: TextOverflow.Ellipsis });
  Text.align(c13 === null || c13 === void 0 ? void 0 : c13.alignment);
}

export class SubHeader extends ViewPU {
  constructor(w12, x12, y12, z12 = -1, a13 = undefined, b13) {
    super(w12, y12, z12, b13);
    if (typeof a13 === 'function') {
      this.paramsGenerator_ = a13;
    }
    this.__icon = new SynchedPropertyObjectOneWayPU(x12.icon, this, 'icon');
    this.iconSymbolOptions = null;
    this.__primaryTitle = new SynchedPropertyObjectOneWayPU(x12.primaryTitle, this, 'primaryTitle');
    this.__secondaryTitle = new SynchedPropertyObjectOneWayPU(x12.secondaryTitle, this, 'secondaryTitle');
    this.__select = new SynchedPropertyObjectOneWayPU(x12.select, this, 'select');
    this.__operationType = new SynchedPropertySimpleOneWayPU(x12.operationType, this, 'operationType');
    this.operationItem = null;
    this.operationSymbolOptions = null;
    this.__isDuplicateLine = new ObservedPropertySimplePU(false, this, 'isDuplicateLine');
    this.__textArrowBgColor = new ObservedPropertyObjectPU({
      id: -1, type: 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'],
      bundleName: '', moduleName: ''
    }, this, 'textArrowBgColor');
    this.__buttonBgColor = new ObservedPropertyObjectPU({
      id: -1, type: 10001,
      params: ['sys.color.ohos_id_color_sub_background_transparent'], bundleName: '', moduleName: ''
    },
      this, 'buttonBgColor');
    this.__flexWidth = new ObservedPropertySimplePU(0, this, 'flexWidth');
    this.__textArrowWidth = new ObservedPropertySimplePU(0, this, 'textArrowWidth');
    this.__textArrowFocus = new ObservedPropertySimplePU(false, this, 'textArrowFocus');
    this.__buttonFocus = new ObservedPropertySimplePU(false, this, 'buttonFocus');
    this.__arrowWidth = new ObservedPropertySimplePU(0, this, 'arrowWidth');
    this.__buttonWidth = new ObservedPropertySimplePU(0, this, 'buttonWidth');
    this.focusBorderWidth = BORDER_WIDTH;
    this.__flexAlign = new ObservedPropertySimplePU(FlexAlign.SpaceBetween, this, 'flexAlign');
    this.setInitiallyProvidedValue(x12);
  }

  setInitiallyProvidedValue(v12) {
    if (v12.icon === undefined) {
      this.__icon.set(null);
    }
    if (v12.iconSymbolOptions !== undefined) {
      this.iconSymbolOptions = v12.iconSymbolOptions;
    }
    if (v12.primaryTitle === undefined) {
      this.__primaryTitle.set(null);
    }
    if (v12.secondaryTitle === undefined) {
      this.__secondaryTitle.set(null);
    }
    if (v12.select === undefined) {
      this.__select.set(null);
    }
    if (v12.operationType === undefined) {
      this.__operationType.set(OperationType.BUTTON);
    }
    if (v12.operationItem !== undefined) {
      this.operationItem = v12.operationItem;
    }
    if (v12.operationSymbolOptions !== undefined) {
      this.operationSymbolOptions = v12.operationSymbolOptions;
    }
    if (v12.isDuplicateLine !== undefined) {
      this.isDuplicateLine = v12.isDuplicateLine;
    }
    if (v12.textArrowBgColor !== undefined) {
      this.textArrowBgColor = v12.textArrowBgColor;
    }
    if (v12.buttonBgColor !== undefined) {
      this.buttonBgColor = v12.buttonBgColor;
    }
    if (v12.flexWidth !== undefined) {
      this.flexWidth = v12.flexWidth;
    }
    if (v12.textArrowWidth !== undefined) {
      this.textArrowWidth = v12.textArrowWidth;
    }
    if (v12.textArrowFocus !== undefined) {
      this.textArrowFocus = v12.textArrowFocus;
    }
    if (v12.buttonFocus !== undefined) {
      this.buttonFocus = v12.buttonFocus;
    }
    if (v12.arrowWidth !== undefined) {
      this.arrowWidth = v12.arrowWidth;
    }
    if (v12.buttonWidth !== undefined) {
      this.buttonWidth = v12.buttonWidth;
    }
    if (v12.focusBorderWidth !== undefined) {
      this.focusBorderWidth = v12.focusBorderWidth;
    }
    if (v12.flexAlign !== undefined) {
      this.flexAlign = v12.flexAlign;
    }
  }

  updateStateVars(u12) {
    this.__icon.reset(u12.icon);
    this.__primaryTitle.reset(u12.primaryTitle);
    this.__secondaryTitle.reset(u12.secondaryTitle);
    this.__select.reset(u12.select);
    this.__operationType.reset(u12.operationType);
  }

  purgeVariableDependenciesOnElmtId(t12) {
    this.__icon.purgeDependencyOnElmtId(t12);
    this.__primaryTitle.purgeDependencyOnElmtId(t12);
    this.__secondaryTitle.purgeDependencyOnElmtId(t12);
    this.__select.purgeDependencyOnElmtId(t12);
    this.__operationType.purgeDependencyOnElmtId(t12);
    this.__isDuplicateLine.purgeDependencyOnElmtId(t12);
    this.__textArrowBgColor.purgeDependencyOnElmtId(t12);
    this.__buttonBgColor.purgeDependencyOnElmtId(t12);
    this.__flexWidth.purgeDependencyOnElmtId(t12);
    this.__textArrowWidth.purgeDependencyOnElmtId(t12);
    this.__textArrowFocus.purgeDependencyOnElmtId(t12);
    this.__buttonFocus.purgeDependencyOnElmtId(t12);
    this.__arrowWidth.purgeDependencyOnElmtId(t12);
    this.__buttonWidth.purgeDependencyOnElmtId(t12);
    this.__flexAlign.purgeDependencyOnElmtId(t12);
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

  set icon(s12) {
    this.__icon.set(s12);
  }

  get primaryTitle() {
    return this.__primaryTitle.get();
  }

  set primaryTitle(r12) {
    this.__primaryTitle.set(r12);
  }

  get secondaryTitle() {
    return this.__secondaryTitle.get();
  }

  set secondaryTitle(q12) {
    this.__secondaryTitle.set(q12);
  }

  get select() {
    return this.__select.get();
  }

  set select(p12) {
    this.__select.set(p12);
  }

  get operationType() {
    return this.__operationType.get();
  }

  set operationType(o12) {
    this.__operationType.set(o12);
  }

  get isDuplicateLine() {
    return this.__isDuplicateLine.get();
  }

  set isDuplicateLine(n12) {
    this.__isDuplicateLine.set(n12);
  }

  get textArrowBgColor() {
    return this.__textArrowBgColor.get();
  }

  set textArrowBgColor(m12) {
    this.__textArrowBgColor.set(m12);
  }

  get buttonBgColor() {
    return this.__buttonBgColor.get();
  }

  set buttonBgColor(l12) {
    this.__buttonBgColor.set(l12);
  }

  get flexWidth() {
    return this.__flexWidth.get();
  }

  set flexWidth(k12) {
    this.__flexWidth.set(k12);
  }

  get textArrowWidth() {
    return this.__textArrowWidth.get();
  }

  set textArrowWidth(j12) {
    this.__textArrowWidth.set(j12);
  }

  get textArrowFocus() {
    return this.__textArrowFocus.get();
  }

  set textArrowFocus(i12) {
    this.__textArrowFocus.set(i12);
  }

  get buttonFocus() {
    return this.__buttonFocus.get();
  }

  set buttonFocus(h12) {
    this.__buttonFocus.set(h12);
  }

  get arrowWidth() {
    return this.__arrowWidth.get();
  }

  set arrowWidth(g12) {
    this.__arrowWidth.set(g12);
  }

  get buttonWidth() {
    return this.__buttonWidth.get();
  }

  set buttonWidth(f12) {
    this.__buttonWidth.set(f12);
  }

  get flexAlign() {
    return this.__flexAlign.get();
  }

  set flexAlign(e12) {
    this.__flexAlign.set(e12);
  }

  initialRender() {
    this.observeComponentCreation2((y11, z11) => {
      Flex.create({ justifyContent: this.flexAlign, alignItems: ItemAlign.End });
      Flex.focusable(true);
      Flex.onAreaChange((b12, c12) => {
        let d12 = Number(parseInt(c12.width.toString(), DEFAULT_VALUE));
        this.flexWidth = d12;
      });
      Flex.height(this.isDuplicateLine ? DOUBLE_LINE_HEIGHT : SINGLE_LINE_HEIGHT);
    }, Flex);
    this.leftArea.bind(this)();
    this.rightArea.bind(this)();
    Flex.pop();
  }

  leftArea(n11 = null) {
    this.observeComponentCreation2((p11, q11) => {
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

  rightArea(s10 = null) {
    this.observeComponentCreation2((j11, k11) => {
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
    this.observeComponentCreation2((f11, g11) => {
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
    this.observeComponentCreation2((b11, c11) => {
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
    this.observeComponentCreation2((x10, y10) => {
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

  IconSecondTitleStyle(j9, k9 = null) {
    this.observeComponentCreation2((p10, q10) => {
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
    }, Row);
    this.observeComponentCreation2((q9, r9) => {
      let s9;
      If.create();
      if (Util.isSymbolicResource((s9 = j9.iconOptions) === null || s9 === void 0 ? void 0 : s9.icon)) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((a10, b10) => {
            let c10;
            let d10;
            let e10;
            let f10;
            let g10;
            let h10;
            let i10;
            let j10;
            let k10;
            let l10;
            let m10;
            let n10;
            let o10;
            SymbolGlyph.create((c10 = j9.iconOptions) === null || c10 === void 0 ? void 0 : c10.icon);
            SymbolGlyph.focusable(true);
            SymbolGlyph.fontSize((f10 = (e10 = (d10 = j9.iconOptions) === null || d10 === void 0 ?
              void 0 : d10.symbolicIconOption) === null || e10 === void 0
              ? void 0 : e10.fontSize) !== null && f10 !== void 0 ? f10 : IMAGE_WIDTH_NUM);
            SymbolGlyph.fontColor((i10 = (h10 = (g10 = j9.iconOptions) === null || g10 === void 0 ?
              void 0 : g10.symbolicIconOption) === null || h10 === void 0 ? void 0 : h10.fontColor) !== null &&
              i10 !== void 0 ? i10 : [{
                id: -1, type: 10001, params: ['sys.color.icon_secondary'],
                bundleName: '', moduleName: ''
              }]);
            SymbolGlyph.fontWeight((k10 = (j10 = j9.iconOptions) === null || j10 === void 0 ?
              void 0 : j10.symbolicIconOption) === null || k10 === void 0 ? void 0 : k10.fontWeight);
            SymbolGlyph.renderingStrategy((m10 = (l10 = j9.iconOptions) === null || l10 === void 0 ?
              void 0 : l10.symbolicIconOption) === null || m10 === void 0 ? void 0 : m10.renderingStrategy);
            SymbolGlyph.effectStrategy((o10 = (n10 = j9.iconOptions) === null || n10 === void 0 ?
              void 0 : n10.symbolicIconOption) === null || o10 === void 0 ? void 0 : o10.effectStrategy);
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
          this.observeComponentCreation2((v9, w9) => {
            let x9;
            Image.create((x9 = j9.iconOptions) === null || x9 === void 0 ? void 0 : x9.icon);
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
    this.observeComponentCreation2((o9, p9) => {
      Text.create(j9.content);
      __Text__secondaryTitleStyles({
        maxLines: DOUBLE_LINE_NUM,
        fontWeight: FontWeight.Medium,
        alignment: Alignment.Start,
      });
    }, Text);
    Text.pop();
    Row.pop();
  }

  SubTitleStyle(x8, y8 = null) {
    this.observeComponentCreation2((g9, h9) => {
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
    this.observeComponentCreation2((e9, f9) => {
      Text.create(x8.content);
      __Text__primaryTitleStyles({
        fontWeight: FontWeight.Medium,
        maxLines: SINGLE_LINE_NUM,
        alignment: Alignment.Start,
      });
    }, Text);
    Text.pop();
    this.observeComponentCreation2((c9, d9) => {
      Text.create(x8.subContent);
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

  SecondTitleStyle(o8, p8 = null) {
    this.observeComponentCreation2((v8, w8) => {
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
    this.observeComponentCreation2((s8, t8) => {
      Text.create(o8.content);
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

  SelectStyle(c8, d8 = null) {
    this.observeComponentCreation2((l8, m8) => {
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
    this.observeComponentCreation2((g8, h8) => {
      Select.create(c8.options);
      Select.selected(c8.selected);
      Select.value(c8.value);
      Select.onSelect((j8, k8) => {
        if (c8.onSelect) {
          c8.onSelect(j8, k8);
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

  PrimaryTitleStyle(t7, u7 = null) {
    this.observeComponentCreation2((a8, b8) => {
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
    this.observeComponentCreation2((x7, y7) => {
      Text.create(t7.content);
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

  ButtonStyle(g6, h6 = null) {
    this.observeComponentCreation2((r7, s7) => {
      Row.create();
      Row.margin({
        left: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.margin_right'], bundleName: '', moduleName: '' },
      });
      Row.width(this.flexWidth / DIVIDEND_NUM);
      Row.justifyContent(FlexAlign.End);
      Row.focusable(true);
    }, Row);
    this.observeComponentCreation2((p7, q7) => {
      Stack.create();
      Stack.focusable(true);
    }, Stack);
    this.observeComponentCreation2((l6, m6) => {
      If.create();
      if (g6) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((b7, c7) => {
            Row.create();
            Row.backgroundColor(ObservedObject.GetRawObject(this.buttonBgColor));
            Row.focusable(true);
            Row.height(BUTTON_HEIGHT);
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
              width: this.buttonWidth,
              color: {
                id: -1, type: 10001, params: ['sys.color.interactive_focus'],
                bundleName: '', moduleName: ''
              },
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
            Row.onHover((o7) => {
              if (o7) {
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
            Row.onTouch((n7) => {
              if (n7.type === TouchType.Down) {
                if (g6.action) {
                  g6.action();
                }
                this.buttonBgColor = {
                  id: -1, type: 10001, params: ['sys.color.interactive_pressed'],
                  bundleName: '', moduleName: ''
                };
              }
              if (n7.type === TouchType.Up) {
                this.buttonBgColor = {
                  id: -1, type: 10001,
                  params: ['sys.color.ohos_id_color_sub_background_transparent'], bundleName: '', moduleName: ''
                };
              }
            });
            Row.onKeyEvent((m7) => {
              if (m7.keyCode === KeyCode.KEYCODE_ENTER || m7.keyCode === KeyCode.KEYCODE_SPACE) {
                if (g6.action) {
                  g6.action();
                }
              }
            });
            Row.onAreaChange((j7, k7) => {
              let l7 = Number(parseInt(k7.width.toString(), DEFAULT_VALUE));
              this.buttonWidth = l7;
            });
          }, Row);
          this.observeComponentCreation2((z6, a7) => {
            Text.create(g6.value);
            __Text__secondaryTitleStyles({
              fontWeight: FontWeight.Medium,
              maxLines: SINGLE_LINE_NUM,
              fontColor: { id: -1, type: 10001, params: ['sys.color.font_emphasize'], bundleName: '', moduleName: '' },
            });
            Text.focusable(true);
          }, Text);
          Text.pop();
          Row.pop();
          this.observeComponentCreation2((s6, t6) => {
            If.create();
            if (this.buttonFocus) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation2((x6, y6) => {
                  Row.create();
                  Row.height(BUTTON_HEIGHT);
                  Row.width(this.buttonWidth);
                  Row.hitTestBehavior(HitTestMode.None);
                  Row.border({
                    width: {
                      id: -1, type: 10002, params: ['sys.float.outline_extra_larger'],
                      bundleName: '', moduleName: ''
                    },
                    color: {
                      id: -1, type: 10001, params: ['sys.color.interactive_focus'],
                      bundleName: '', moduleName: ''
                    },
                  });
                  Row.borderRadius({
                    id: -1, type: 10002, params: ['sys.float.corner_radius_level4'],
                    bundleName: '', moduleName: ''
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

  IconGroupStyle(v4, w4 = null) {
    this.observeComponentCreation2((e6, f6) => {
      Row.create();
      Row.justifyContent(FlexAlign.End);
      Row.width(this.flexWidth / DIVIDEND_NUM);
      Row.focusable(true);
      Row.margin({
        left: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.padding_level6'], bundleName: '', moduleName: '' },
      });
    }, Row);
    this.observeComponentCreation2((z4, a5) => {
      ForEach.create();
      const b5 = (d5, e5) => {
        const f5 = d5;
        this.observeComponentCreation2((h5, i5) => {
          If.create();
          if (Util.isResourceType(f5.value)) {
            this.ifElseBranchUpdateFunction(0, () => {
              this.observeComponentCreation2((m5, n5) => {
                If.create();
                if (e5 === INDEX_ZERO) {
                  this.ifElseBranchUpdateFunction(0, () => {
                    {
                      this.observeComponentCreation2((a6, b6) => {
                        if (b6) {
                          let c6 = () => {
                            return {
                              item: {
                                iconOptions: {
                                  icon: f5.value,
                                  symbolicIconOption: this.operationSymbolOptions &&
                                    this.operationSymbolOptions.length > e5 ?
                                    this.operationSymbolOptions[e5] : null,
                                },
                                action: f5.action,
                              }
                            };
                          };
                          ViewPU.create(new SingleIconStyle(this, {
                            item: {
                              iconOptions: {
                                icon: f5.value,
                                symbolicIconOption: this.operationSymbolOptions &&
                                  this.operationSymbolOptions.length > e5 ?
                                  this.operationSymbolOptions[e5] : null,
                              },
                              action: f5.action,
                            }
                          }, undefined, a6, c6, {
                            page: 'library/src/main/ets/components/mainpage/MainPage.ets',
                            line: 445
                          }));
                        }
                        else {
                          this.updateStateVarsOfChildByElmtId(a6, {});
                        }
                      }, { name: 'SingleIconStyle' });
                    }
                  });
                }
                else if (e5 === INDEX_ONE || e5 === INDEX_TWO) {
                  this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((w5, x5) => {
                      __Common__.create();
                      __Common__.margin({
                        left: {
                          id: -1, type: 10002, params: ['sys.float.padding_level4'],
                          bundleName: '', moduleName: ''
                        },
                      });
                    }, __Common__);
                    {
                      this.observeComponentCreation2((s5, t5) => {
                        if (t5) {
                          let u5 = () => {
                            return {
                              item: {
                                action: f5.action,
                                iconOptions: {
                                  icon: f5.value,
                                  symbolicIconOption: this.operationSymbolOptions &&
                                    this.operationSymbolOptions.length > e5 ?
                                    this.operationSymbolOptions[e5] : null,
                                },
                              }
                            };
                          };
                          ViewPU.create(new SingleIconStyle(this, {
                            item: {
                              action: f5.action,
                              iconOptions: {
                                icon: f5.value,
                                symbolicIconOption: this.operationSymbolOptions &&
                                  this.operationSymbolOptions.length > e5 ?
                                  this.operationSymbolOptions[e5] : null,
                              },
                            }
                          }, undefined, s5, u5, {
                            page: 'library/src/main/ets/components/mainpage/MainPage.ets',
                            line: 456
                          }));
                        }
                        else {
                          this.updateStateVarsOfChildByElmtId(s5, {});
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
      this.forEachUpdateFunction(z4, this.operationItem, b5, undefined, true, false);
    }, ForEach);
    ForEach.pop();
    Row.pop();
  }

  TextArrowStyle(a3, b3 = null) {
    this.observeComponentCreation2((q4, r4) => {
      Row.create();
      Row.focusable(true);
      Row.onAreaChange((t4, u4) => {
        this.textArrowWidth = Number(parseInt(u4.width.toString(), DEFAULT_VALUE));
      });
      Row.width(this.flexWidth / DIVIDEND_NUM);
      Row.justifyContent(FlexAlign.End);
      Row.margin({
        left: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.margin_right'], bundleName: '', moduleName: '' },
      });
    }, Row);
    this.observeComponentCreation2((o4, p4) => {
      Stack.create();
      Stack.focusable(true);
    }, Stack);
    this.observeComponentCreation2((b4, c4) => {
      Row.create();
      Row.borderRadius({
        id: -1, type: 10002, params: ['sys.float.corner_radius_level4'],
        bundleName: '', moduleName: ''
      });
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
      Row.onHover((n4) => {
        if (n4) {
          this.textArrowBgColor = {
            id: -1, type: 10001, params: ['sys.color.interactive_hover'],
            bundleName: '', moduleName: ''
          };
        }
        else {
          this.textArrowBgColor = {
            id: -1, type: 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'],
            bundleName: '', moduleName: ''
          };
        }
      });
      Row.onTouch((m4) => {
        if (m4.type === TouchType.Down) {
          if (a3.action) {
            a3.action();
          }
          this.textArrowBgColor = {
            id: -1, type: 10001, params: ['sys.color.interactive_pressed'],
            bundleName: '', moduleName: ''
          };
        }
        if (m4.type === TouchType.Up) {
          this.textArrowBgColor = {
            id: -1, type: 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'],
            bundleName: '', moduleName: ''
          };
        }
      });
      Row.onKeyEvent((l4) => {
        if (l4.keyCode === KeyCode.KEYCODE_ENTER || l4.keyCode === KeyCode.KEYCODE_SPACE) {
          if (a3.action) {
            a3.action();
          }
        }
      });
      Row.onAreaChange((j4, k4) => {
        this.arrowWidth = Number(parseInt(k4.width.toString(), DEFAULT_VALUE));
      });
      ViewStackProcessor.visualState('focused');
      Row.border({
        radius: { id: -1, type: 10002, params: ['sys.float.corner_radius_level4'], bundleName: '', moduleName: '' },
        width: this.arrowWidth,
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
      Row.opacity({ id: -1, type: 10002, params: ['sys.float.interactive_disable'], bundleName: '', moduleName: '' });
      ViewStackProcessor.visualState();
    }, Row);
    this.observeComponentCreation2((z3, a4) => {
      Row.create();
    }, Row);
    this.observeComponentCreation2((s3, t3) => {
      If.create();
      if (a3) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((x3, y3) => {
            Text.create(a3.value);
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
    this.observeComponentCreation2((q3, r3) => {
      Image.create({
        id: -1, type: 20000, params: ['sys.media.ohos_ic_public_arrow_right'],
        bundleName: '', moduleName: ''
      });
      Image.fillColor({
        id: -1, type: 10001, params: ['sys.color.ohos_id_color_tertiary'],
        bundleName: '', moduleName: ''
      });
      Image.width(IMAGE_WIDTH);
      Image.height(IMAGE_HEIGHT_NUM);
      Image.focusable(true);
      Image.draggable(false);
    }, Image);
    Row.pop();
    Row.pop();
    this.observeComponentCreation2((j3, k3) => {
      If.create();
      if (this.textArrowFocus) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((o3, p3) => {
            Row.create();
            Row.height(BUTTON_SIZE);
            Row.width(this.arrowWidth);
            Row.hitTestBehavior(HitTestMode.None);
            Row.border({
              width: {
                id: -1, type: 10002, params: ['sys.float.outline_extra_larger'],
                bundleName: '', moduleName: ''
              },
              color: { id: -1, type: 10001, params: ['sys.color.interactive_focus'], bundleName: '', moduleName: '' },
            });
            Row.borderRadius({
              id: -1, type: 10002, params: ['sys.float.corner_radius_level4'],
              bundleName: '', moduleName: ''
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
    Stack.pop();
    Row.pop();
  }

  LoadingProcessStyle(s2 = null) {
    this.observeComponentCreation2((y2, z2) => {
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
    this.observeComponentCreation2((v2, w2) => {
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

  dummyFunction(n2 = null) {
    this.observeComponentCreation2((p2, q2) => {
      Row.create();
      Row.onAppear(() => {
        this.changeFlexAlign(FlexAlign.End);
      });
    }, Row);
    Row.pop();
  }

  changeFlexAlign(m2) {
    if (this.flexAlign === m2) {
      return;
    }
    this.flexAlign = m2;
  }

  rerender() {
    this.updateDirtyElements();
  }
}

class SingleIconStyle extends ViewPU {
  constructor(g2, h2, i2, j2 = -1, k2 = undefined, l2) {
    super(g2, i2, j2, l2);
    if (typeof k2 === 'function') {
      this.paramsGenerator_ = k2;
    }
    this.__bgColor = new ObservedPropertyObjectPU({
      id: -1, type: 10001,
      params: ['sys.color.ohos_id_color_sub_background_transparent'], bundleName: '', moduleName: ''
    },
      this, 'bgColor');
    this.__isFocus = new ObservedPropertySimplePU(false, this, 'isFocus');
    this.item = null;
    this.focusBorderWidth = BORDER_WIDTH;
    this.setInitiallyProvidedValue(h2);
  }

  setInitiallyProvidedValue(f2) {
    if (f2.bgColor !== undefined) {
      this.bgColor = f2.bgColor;
    }
    if (f2.isFocus !== undefined) {
      this.isFocus = f2.isFocus;
    }
    if (f2.item !== undefined) {
      this.item = f2.item;
    }
    if (f2.focusBorderWidth !== undefined) {
      this.focusBorderWidth = f2.focusBorderWidth;
    }
  }

  updateStateVars(e2) {
  }

  purgeVariableDependenciesOnElmtId(d2) {
    this.__bgColor.purgeDependencyOnElmtId(d2);
    this.__isFocus.purgeDependencyOnElmtId(d2);
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

  set bgColor(c2) {
    this.__bgColor.set(c2);
  }

  get isFocus() {
    return this.__isFocus.get();
  }

  set isFocus(b2) {
    this.__isFocus.set(b2);
  }

  initialRender() {
    this.observeComponentCreation2((k1, l1) => {
      If.create();
      if (this.item && this.item.iconOptions) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((p1, q1) => {
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
              color: {
                id: -1, type: 10001, params: ['sys.color.interactive_focus'],
                bundleName: '', moduleName: ''
              },
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
            Row.onTouch((y1) => {
              let z1;
              let a2;
              if (y1.type === TouchType.Down) {
                if ((z1 = this.item) === null || z1 === void 0 ? void 0 : z1.action) {
                  (a2 = this.item) === null || a2 === void 0 ? void 0 : a2.action();
                }
                this.bgColor = {
                  id: -1, type: 10001, params: ['sys.color.interactive_pressed'],
                  bundleName: '', moduleName: ''
                };
              }
              if (y1.type === TouchType.Up) {
                this.bgColor = {
                  id: -1, type: 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'],
                  bundleName: '', moduleName: ''
                };
              }
            });
            Row.onHover((x1) => {
              if (x1) {
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
            Row.onKeyEvent((u1) => {
              let v1;
              let w1;
              if (u1.keyCode === KeyCode.KEYCODE_ENTER || u1.keyCode === KeyCode.KEYCODE_SPACE) {
                if ((v1 = this.item) === null || v1 === void 0 ? void 0 : v1.action) {
                  (w1 = this.item) === null || w1 === void 0 ? void 0 : w1.action();
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

  IconZone(d = null) {
    this.observeComponentCreation2((f, g) => {
      If.create();
      if (this.item && this.item.iconOptions) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((k, l) => {
            If.create();
            if (Util.isSymbolicResource(this.item.iconOptions.icon)) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation2((u, v) => {
                  let w;
                  let x;
                  let y;
                  let z;
                  let a1;
                  let b1;
                  let c1;
                  let d1;
                  let e1;
                  let f1;
                  let g1;
                  let h1;
                  let i1;
                  SymbolGlyph.create((w = this.item.iconOptions) === null || w === void 0 ? void 0 : w.icon);
                  SymbolGlyph.focusable(true);
                  SymbolGlyph.fontSize((z = (y = (x = this.item.iconOptions) === null || x === void 0 ?
                    void 0 : x.symbolicIconOption) === null || y === void 0 ? void 0 : y.fontSize) !== null &&
                    z !== void 0 ? z : IMAGE_HEIGHT_NUM);
                  SymbolGlyph.fontColor((c1 = (b1 = (a1 = this.item.iconOptions) === null || a1 === void 0 ?
                    void 0 : a1.symbolicIconOption) === null || b1 === void 0 ? void 0 : b1.fontColor) !== null &&
                    c1 !== void 0 ? c1 : [{
                      id: -1, type: 10001, params: ['sys.color.icon_primary'],
                      bundleName: '', moduleName: ''
                    }]);
                  SymbolGlyph.fontWeight((e1 = (d1 = this.item.iconOptions) === null || d1 === void 0 ? void 0 :
                    d1.symbolicIconOption) === null || e1 === void 0 ? void 0 : e1.fontWeight);
                  SymbolGlyph.renderingStrategy((g1 = (f1 = this.item.iconOptions) === null || f1 === void 0 ?
                    void 0 : f1.symbolicIconOption) === null || g1 === void 0 ? void 0 : g1.renderingStrategy);
                  SymbolGlyph.effectStrategy((i1 = (h1 = this.item.iconOptions) === null || h1 === void 0 ?
                    void 0 : h1.symbolicIconOption) === null || i1 === void 0 ? void 0 : i1.effectStrategy);
                }, SymbolGlyph);
              });
            }
            else {
              this.ifElseBranchUpdateFunction(1, () => {
                this.observeComponentCreation2((o, p) => {
                  let q;
                  let r;
                  Image.create((r = (q = this.item) === null || q === void 0 ? void 0 : q.iconOptions) === null ||
                    r === void 0 ? void 0 : r.icon);
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