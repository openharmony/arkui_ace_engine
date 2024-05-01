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

if (!('finalizeConstruction' in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => { });
}
const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;
const hilog = requireNapi('hilog');
const resourceManager = requireNapi('resourceManager');
const DIVIDEND_NUM = 3;
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
const MAX_ICON_GROUP_WIDTH_VALUE = SINGLE_ICON_ZONE_SIZE * 3 + getNumberByResource('padding_level4') * 2 +
  getNumberByResource('padding_level2') + getNumberByResource('padding_level6');
const LOADING_SIZE = 24;
const COMMON_MARGIN_VALUE = getNumberByResource('margin_left') + getNumberByResource('margin_right');
const ICON_GROUP_MARGIN_VALUE = getNumberByResource('padding_level2') + getNumberByResource('padding_level6');
const TEXT_ARROW_MARGIN_VALUE = getNumberByResource('padding_level4') + getNumberByResource('padding_level4');
const BUTTON_MARGIN_VALUE = getNumberByResource('padding_level1') + getNumberByResource('padding_level5');
const LOADING_MARGIN_VALUE = getNumberByResource('padding_level4') + getNumberByResource('margin_right');
export var OperationType;
(function (q13) {
  q13[q13.TEXT_ARROW = 0] = 'TEXT_ARROW';
  q13[q13.BUTTON = 1] = 'BUTTON';
  q13[q13.ICON_GROUP = 2] = 'ICON_GROUP';
  q13[q13.LOADING = 3] = 'LOADING';
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
function __Text__secondaryTitleStyles(o13) {
  let p13;
  Text.fontSize({ id: -1, type: 10002, params: ['sys.float.Subtitle_S'], bundleName: '', moduleName: '' });
  Text.fontColor((p13 = o13 === null || o13 === void 0 ? void 0 : o13.fontColor) !== null && p13 !== void 0 ? p13 : { id: -1, type: 10001, params: ['sys.color.font_secondary'], bundleName: '', moduleName: '' });
  Text.fontWeight(o13 === null || o13 === void 0 ? void 0 : o13.fontWeight);
  Text.maxLines(o13 === null || o13 === void 0 ? void 0 : o13.maxLines);
  Text.textOverflow({ overflow: TextOverflow.Ellipsis });
  Text.align(o13 === null || o13 === void 0 ? void 0 : o13.alignment);
}
function __Text__primaryTitleStyles(n13) {
  Text.fontSize({ id: -1, type: 10002, params: ['sys.float.Subtitle_L'], bundleName: '', moduleName: '' });
  Text.fontColor({ id: -1, type: 10001, params: ['sys.color.font_primary'], bundleName: '', moduleName: '' });
  Text.fontWeight(n13 === null || n13 === void 0 ? void 0 : n13.fontWeight);
  Text.maxLines(n13 === null || n13 === void 0 ? void 0 : n13.maxLines);
  Text.textOverflow({ overflow: TextOverflow.Ellipsis });
  Text.align(n13 === null || n13 === void 0 ? void 0 : n13.alignment);
}
export class SubHeader extends ViewPU {
  constructor(h13, i13, j13, k13 = -1, l13 = undefined, m13) {
    super(h13, j13, k13, m13);
    if (typeof l13 === 'function') {
      this.paramsGenerator_ = l13;
    }
    this.__icon = new SynchedPropertyObjectOneWayPU(i13.icon, this, 'icon');
    this.iconSymbolOptions = null;
    this.__primaryTitle = new SynchedPropertyObjectOneWayPU(i13.primaryTitle, this, 'primaryTitle');
    this.__secondaryTitle = new SynchedPropertyObjectOneWayPU(i13.secondaryTitle, this, 'secondaryTitle');
    this.select = null;
    this.__operationType = new SynchedPropertySimpleOneWayPU(i13.operationType, this, 'operationType');
    this.operationItem = null;
    this.operationSymbolOptions = null;
    this.__isDuplicateLine = new ObservedPropertySimplePU(false, this, 'isDuplicateLine');
    this.__textArrowBgColor = new ObservedPropertyObjectPU({ id: -1, type: 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], bundleName: '', moduleName: '' }, this, 'textArrowBgColor');
    this.__buttonBgColor = new ObservedPropertyObjectPU({ id: -1, type: 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], bundleName: '', moduleName: '' }, this, 'buttonBgColor');
    this.__flexWidth = new ObservedPropertySimplePU(0, this, 'flexWidth');
    this.__rightWidth = new ObservedPropertySimplePU(0, this, 'rightWidth');
    this.__leftWidth = new ObservedPropertySimplePU(0, this, 'leftWidth');
    this.__textArrowFocus = new ObservedPropertySimplePU(false, this, 'textArrowFocus');
    this.__buttonFocus = new ObservedPropertySimplePU(false, this, 'buttonFocus');
    this.__textArrowStyleWidth = new ObservedPropertySimplePU(0, this, 'textArrowStyleWidth');
    this.__textArrowStyleHeight = new ObservedPropertySimplePU(0, this, 'textArrowStyleHeight');
    this.__buttonStyleWidth = new ObservedPropertySimplePU(0, this, 'buttonStyleWidth');
    this.__buttonStyleHeight = new ObservedPropertySimplePU(0, this, 'buttonStyleHeight');
    this.__iconTextStyleWidth = new ObservedPropertySimplePU(0, this, 'iconTextStyleWidth');
    this.__iconTextWidth = new ObservedPropertySimplePU(0, this, 'iconTextWidth');
    this.__iconWidth = new ObservedPropertySimplePU(0, this, 'iconWidth');
    this.__selectedIndex = new ObservedPropertyObjectPU(-1, this, 'selectedIndex');
    this.__selectValue = new ObservedPropertyObjectPU('', this, 'selectValue');
    this.__flexAlign = new ObservedPropertySimplePU(FlexAlign.SpaceBetween, this, 'flexAlign');
    this.setInitiallyProvidedValue(i13);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(g13) {
    if (g13.icon === undefined) {
      this.__icon.set(null);
    }
    if (g13.iconSymbolOptions !== undefined) {
      this.iconSymbolOptions = g13.iconSymbolOptions;
    }
    if (g13.primaryTitle === undefined) {
      this.__primaryTitle.set(null);
    }
    if (g13.secondaryTitle === undefined) {
      this.__secondaryTitle.set(null);
    }
    if (g13.select !== undefined) {
      this.select = g13.select;
    }
    if (g13.operationType === undefined) {
      this.__operationType.set(OperationType.BUTTON);
    }
    if (g13.operationItem !== undefined) {
      this.operationItem = g13.operationItem;
    }
    if (g13.operationSymbolOptions !== undefined) {
      this.operationSymbolOptions = g13.operationSymbolOptions;
    }
    if (g13.isDuplicateLine !== undefined) {
      this.isDuplicateLine = g13.isDuplicateLine;
    }
    if (g13.textArrowBgColor !== undefined) {
      this.textArrowBgColor = g13.textArrowBgColor;
    }
    if (g13.buttonBgColor !== undefined) {
      this.buttonBgColor = g13.buttonBgColor;
    }
    if (g13.flexWidth !== undefined) {
      this.flexWidth = g13.flexWidth;
    }
    if (g13.rightWidth !== undefined) {
      this.rightWidth = g13.rightWidth;
    }
    if (g13.leftWidth !== undefined) {
      this.leftWidth = g13.leftWidth;
    }
    if (g13.textArrowFocus !== undefined) {
      this.textArrowFocus = g13.textArrowFocus;
    }
    if (g13.buttonFocus !== undefined) {
      this.buttonFocus = g13.buttonFocus;
    }
    if (g13.textArrowStyleWidth !== undefined) {
      this.textArrowStyleWidth = g13.textArrowStyleWidth;
    }
    if (g13.textArrowStyleHeight !== undefined) {
      this.textArrowStyleHeight = g13.textArrowStyleHeight;
    }
    if (g13.buttonStyleWidth !== undefined) {
      this.buttonStyleWidth = g13.buttonStyleWidth;
    }
    if (g13.buttonStyleHeight !== undefined) {
      this.buttonStyleHeight = g13.buttonStyleHeight;
    }
    if (g13.iconTextStyleWidth !== undefined) {
      this.iconTextStyleWidth = g13.iconTextStyleWidth;
    }
    if (g13.iconTextWidth !== undefined) {
      this.iconTextWidth = g13.iconTextWidth;
    }
    if (g13.iconWidth !== undefined) {
      this.iconWidth = g13.iconWidth;
    }
    if (g13.selectedIndex !== undefined) {
      this.selectedIndex = g13.selectedIndex;
    }
    if (g13.selectValue !== undefined) {
      this.selectValue = g13.selectValue;
    }
    if (g13.flexAlign !== undefined) {
      this.flexAlign = g13.flexAlign;
    }
  }
  updateStateVars(f13) {
    this.__icon.reset(f13.icon);
    this.__primaryTitle.reset(f13.primaryTitle);
    this.__secondaryTitle.reset(f13.secondaryTitle);
    this.__operationType.reset(f13.operationType);
  }
  purgeVariableDependenciesOnElmtId(e13) {
    this.__icon.purgeDependencyOnElmtId(e13);
    this.__primaryTitle.purgeDependencyOnElmtId(e13);
    this.__secondaryTitle.purgeDependencyOnElmtId(e13);
    this.__operationType.purgeDependencyOnElmtId(e13);
    this.__isDuplicateLine.purgeDependencyOnElmtId(e13);
    this.__textArrowBgColor.purgeDependencyOnElmtId(e13);
    this.__buttonBgColor.purgeDependencyOnElmtId(e13);
    this.__flexWidth.purgeDependencyOnElmtId(e13);
    this.__rightWidth.purgeDependencyOnElmtId(e13);
    this.__leftWidth.purgeDependencyOnElmtId(e13);
    this.__textArrowFocus.purgeDependencyOnElmtId(e13);
    this.__buttonFocus.purgeDependencyOnElmtId(e13);
    this.__textArrowStyleWidth.purgeDependencyOnElmtId(e13);
    this.__textArrowStyleHeight.purgeDependencyOnElmtId(e13);
    this.__buttonStyleWidth.purgeDependencyOnElmtId(e13);
    this.__buttonStyleHeight.purgeDependencyOnElmtId(e13);
    this.__iconTextStyleWidth.purgeDependencyOnElmtId(e13);
    this.__iconTextWidth.purgeDependencyOnElmtId(e13);
    this.__iconWidth.purgeDependencyOnElmtId(e13);
    this.__selectedIndex.purgeDependencyOnElmtId(e13);
    this.__selectValue.purgeDependencyOnElmtId(e13);
    this.__flexAlign.purgeDependencyOnElmtId(e13);
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
    this.__rightWidth.aboutToBeDeleted();
    this.__leftWidth.aboutToBeDeleted();
    this.__textArrowFocus.aboutToBeDeleted();
    this.__buttonFocus.aboutToBeDeleted();
    this.__textArrowStyleWidth.aboutToBeDeleted();
    this.__textArrowStyleHeight.aboutToBeDeleted();
    this.__buttonStyleWidth.aboutToBeDeleted();
    this.__buttonStyleHeight.aboutToBeDeleted();
    this.__iconTextStyleWidth.aboutToBeDeleted();
    this.__iconTextWidth.aboutToBeDeleted();
    this.__iconWidth.aboutToBeDeleted();
    this.__selectedIndex.aboutToBeDeleted();
    this.__selectValue.aboutToBeDeleted();
    this.__flexAlign.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get icon() {
    return this.__icon.get();
  }
  set icon(d13) {
    this.__icon.set(d13);
  }
  get primaryTitle() {
    return this.__primaryTitle.get();
  }
  set primaryTitle(c13) {
    this.__primaryTitle.set(c13);
  }
  get secondaryTitle() {
    return this.__secondaryTitle.get();
  }
  set secondaryTitle(b13) {
    this.__secondaryTitle.set(b13);
  }
  get operationType() {
    return this.__operationType.get();
  }
  set operationType(a13) {
    this.__operationType.set(a13);
  }
  get isDuplicateLine() {
    return this.__isDuplicateLine.get();
  }
  set isDuplicateLine(z12) {
    this.__isDuplicateLine.set(z12);
  }
  get textArrowBgColor() {
    return this.__textArrowBgColor.get();
  }
  set textArrowBgColor(y12) {
    this.__textArrowBgColor.set(y12);
  }
  get buttonBgColor() {
    return this.__buttonBgColor.get();
  }
  set buttonBgColor(x12) {
    this.__buttonBgColor.set(x12);
  }
  get flexWidth() {
    return this.__flexWidth.get();
  }
  set flexWidth(w12) {
    this.__flexWidth.set(w12);
  }
  get rightWidth() {
    return this.__rightWidth.get();
  }
  set rightWidth(v12) {
    this.__rightWidth.set(v12);
  }
  get leftWidth() {
    return this.__leftWidth.get();
  }
  set leftWidth(u12) {
    this.__leftWidth.set(u12);
  }
  get textArrowFocus() {
    return this.__textArrowFocus.get();
  }
  set textArrowFocus(t12) {
    this.__textArrowFocus.set(t12);
  }
  get buttonFocus() {
    return this.__buttonFocus.get();
  }
  set buttonFocus(s12) {
    this.__buttonFocus.set(s12);
  }
  get textArrowStyleWidth() {
    return this.__textArrowStyleWidth.get();
  }
  set textArrowStyleWidth(r12) {
    this.__textArrowStyleWidth.set(r12);
  }
  get textArrowStyleHeight() {
    return this.__textArrowStyleHeight.get();
  }
  set textArrowStyleHeight(q12) {
    this.__textArrowStyleHeight.set(q12);
  }
  get buttonStyleWidth() {
    return this.__buttonStyleWidth.get();
  }
  set buttonStyleWidth(p12) {
    this.__buttonStyleWidth.set(p12);
  }
  get buttonStyleHeight() {
    return this.__buttonStyleHeight.get();
  }
  set buttonStyleHeight(o12) {
    this.__buttonStyleHeight.set(o12);
  }
  get iconTextStyleWidth() {
    return this.__iconTextStyleWidth.get();
  }
  set iconTextStyleWidth(n12) {
    this.__iconTextStyleWidth.set(n12);
  }
  get iconTextWidth() {
    return this.__iconTextWidth.get();
  }
  set iconTextWidth(m12) {
    this.__iconTextWidth.set(m12);
  }
  get iconWidth() {
    return this.__iconWidth.get();
  }
  set iconWidth(l12) {
    this.__iconWidth.set(l12);
  }
  get selectedIndex() {
    return this.__selectedIndex.get();
  }
  set selectedIndex(k12) {
    this.__selectedIndex.set(k12);
  }
  get selectValue() {
    return this.__selectValue.get();
  }
  set selectValue(j12) {
    this.__selectValue.set(j12);
  }
  get flexAlign() {
    return this.__flexAlign.get();
  }
  set flexAlign(i12) {
    this.__flexAlign.set(i12);
  }
  initialRender() {
    this.observeComponentCreation((c12, d12) => {
      ViewStackProcessor.StartGetAccessRecordingFor(c12);
      Row.create();
      Row.width('100%');
      Row.alignItems(VerticalAlign.Bottom);
      Row.justifyContent(this.flexAlign);
      Row.focusable(true);
      Row.onAreaChange((f12, g12) => {
        let h12 = Number(g12.width);
        this.flexWidth = h12;
        this.updateAreaWidth(false);
      });
      Row.constraintSize({ minHeight: this.isDuplicateLine ? DOUBLE_LINE_HEIGHT : SINGLE_LINE_HEIGHT });
      if (!d12) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.leftArea.bind(this)();
    this.rightArea.bind(this)();
    Row.pop();
  }
  leftArea(r11 = null) {
    this.observeComponentCreation((t11, u11) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t11);
      If.create();
      if (this.secondaryTitle && this.icon) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.IconSecondaryTitleStyle.bind(this)(makeBuilderParameterProxy('IconSecondaryTitleStyle', {
            content: () => (this['__secondaryTitle'] ? this['__secondaryTitle'] : this['secondaryTitle']), iconOptions: () => ({
              icon: this.icon,
              symbolicIconOption: this.iconSymbolOptions,
            })
          }));
        });
      }
      else if (this.secondaryTitle && this.primaryTitle) {
        this.ifElseBranchUpdateFunction(1, () => {
          this.SubTitleStyle.bind(this)(makeBuilderParameterProxy('SubTitleStyle', { content: () => (this['__primaryTitle'] ? this['__primaryTitle'] : this['primaryTitle']), subContent: () => (this['__secondaryTitle'] ? this['__secondaryTitle'] : this['secondaryTitle']) }));
        });
      }
      else if (this.secondaryTitle) {
        this.ifElseBranchUpdateFunction(2, () => {
          this.SecondTitleStyle.bind(this)(makeBuilderParameterProxy('SecondTitleStyle', { content: () => (this['__secondaryTitle'] ? this['__secondaryTitle'] : this['secondaryTitle']) }));
        });
      }
      else if (this.select) {
        this.ifElseBranchUpdateFunction(3, () => {
          this.SelectStyle.bind(this)(this.select);
        });
      }
      else if (this.primaryTitle) {
        this.ifElseBranchUpdateFunction(4, () => {
          this.PrimaryTitleStyle.bind(this)(makeBuilderParameterProxy('PrimaryTitleStyle', { content: () => (this['__primaryTitle'] ? this['__primaryTitle'] : this['primaryTitle']) }));
        });
      }
      else {
        this.ifElseBranchUpdateFunction(5, () => {
          this.dummyFunction.bind(this)();
        });
      }
      if (!u11) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
  }
  rightArea(w10 = null) {
    this.observeComponentCreation((n11, o11) => {
      ViewStackProcessor.StartGetAccessRecordingFor(n11);
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
      if (!o11) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.observeComponentCreation((j11, k11) => {
      ViewStackProcessor.StartGetAccessRecordingFor(j11);
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
      if (!k11) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.observeComponentCreation((f11, g11) => {
      ViewStackProcessor.StartGetAccessRecordingFor(f11);
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
      if (!g11) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.observeComponentCreation((b11, c11) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b11);
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
      if (!c11) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
  }
  IconSecondaryTitleStyle(e9, f9 = null) {
    this.observeComponentCreation((q10, r10) => {
      ViewStackProcessor.StartGetAccessRecordingFor(q10);
      Row.create();
      Row.width(this.leftWidth - COMMON_MARGIN_VALUE);
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
      Row.onAreaChange((u10, v10) => {
        this.iconTextStyleWidth = Number(v10.width);
        this.updateMaxIconTextWidth();
      });
      if (!r10) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((l10, m10) => {
      ViewStackProcessor.StartGetAccessRecordingFor(l10);
      Row.create();
      Row.onAreaChange((o10, p10) => {
        this.iconWidth = Number(p10.width);
        this.updateMaxIconTextWidth();
      });
      if (!m10) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((m9, n9) => {
      let o9;
      ViewStackProcessor.StartGetAccessRecordingFor(m9);
      If.create();
      if (Util.isSymbolResource((o9 = e9.iconOptions) === null || o9 === void 0 ? void 0 : o9.icon)) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((w9, x9) => {
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
            let i10;
            let j10;
            let k10;
            ViewStackProcessor.StartGetAccessRecordingFor(w9);
            SymbolGlyph.create((y9 = e9.iconOptions) === null || y9 === void 0 ? void 0 : y9.icon);
            SymbolGlyph.focusable(true);
            SymbolGlyph.fontSize((b10 = (a10 = (z9 = e9.iconOptions) === null || z9 === void 0 ? void 0 : z9.symbolicIconOption) === null || a10 === void 0 ? void 0 : a10.fontSize) !== null && b10 !== void 0 ? b10 : LEFT_ICON_SIZE);
            SymbolGlyph.fontColor((e10 = (d10 = (c10 = e9.iconOptions) === null || c10 === void 0 ? void 0 : c10.symbolicIconOption) === null || d10 === void 0 ? void 0 : d10.fontColor) !== null && e10 !== void 0 ? e10 : [{ id: -1, type: 10001, params: ['sys.color.icon_secondary'], bundleName: '', moduleName: '' }]);
            SymbolGlyph.fontWeight((g10 = (f10 = e9.iconOptions) === null || f10 === void 0 ? void 0 : f10.symbolicIconOption) === null || g10 === void 0 ? void 0 : g10.fontWeight);
            SymbolGlyph.renderingStrategy((i10 = (h10 = e9.iconOptions) === null || h10 === void 0 ? void 0 : h10.symbolicIconOption) === null || i10 === void 0 ? void 0 : i10.renderingStrategy);
            SymbolGlyph.effectStrategy((k10 = (j10 = e9.iconOptions) === null || j10 === void 0 ? void 0 : j10.symbolicIconOption) === null || k10 === void 0 ? void 0 : k10.effectStrategy);
            SymbolGlyph.margin({ right: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' } });
            if (!x9) {
              SymbolGlyph.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation((r9, s9) => {
            let t9;
            ViewStackProcessor.StartGetAccessRecordingFor(r9);
            Image.create((t9 = e9.iconOptions) === null || t9 === void 0 ? void 0 : t9.icon);
            Image.width(LEFT_ICON_SIZE);
            Image.height(LEFT_ICON_SIZE);
            Image.margin({ right: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' } });
            Image.draggable(false);
            if (!s9) {
              Image.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
        });
      }
      if (!n9) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    Row.pop();
    this.observeComponentCreation((k9, l9) => {
      ViewStackProcessor.StartGetAccessRecordingFor(k9);
      Text.create(e9.content);
      __Text__secondaryTitleStyles({
        maxLines: DOUBLE_LINE_NUM,
        fontWeight: FontWeight.Medium,
        alignment: Alignment.Start,
      });
      Text.width(this.iconTextWidth);
      if (!l9) {
        Text.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Text.pop();
    Row.pop();
  }
  updateMaxIconTextWidth() {
    this.iconTextWidth = this.iconTextStyleWidth - getNumberByResource('padding_level6') - this.iconWidth -
      getNumberByResource('padding_level6');
  }
  SubTitleStyle(s8, t8 = null) {
    this.observeComponentCreation((b9, c9) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b9);
      Column.create();
      Column.width(this.leftWidth - COMMON_MARGIN_VALUE);
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
      if (!c9) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((z8, a9) => {
      ViewStackProcessor.StartGetAccessRecordingFor(z8);
      Text.create(s8.content);
      __Text__primaryTitleStyles({
        fontWeight: FontWeight.Bold,
        maxLines: SINGLE_LINE_NUM,
        alignment: Alignment.Start,
      });
      Text.width('100%');
      if (!a9) {
        Text.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Text.pop();
    this.observeComponentCreation((x8, y8) => {
      ViewStackProcessor.StartGetAccessRecordingFor(x8);
      Text.create(s8.subContent);
      __Text__secondaryTitleStyles({
        maxLines: SINGLE_LINE_NUM,
        fontWeight: FontWeight.Regular,
        alignment: Alignment.Start,
      });
      Text.width('100%');
      Text.margin({
        top: { id: -1, type: 10002, params: ['sys.float.padding_level1'], bundleName: '', moduleName: '' },
      });
      if (!y8) {
        Text.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Text.pop();
    Column.pop();
  }
  SecondTitleStyle(j8, k8 = null) {
    this.observeComponentCreation((q8, r8) => {
      ViewStackProcessor.StartGetAccessRecordingFor(q8);
      Column.create();
      Column.alignItems(HorizontalAlign.Start);
      Column.width(this.leftWidth - COMMON_MARGIN_VALUE);
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
      if (!r8) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((n8, o8) => {
      ViewStackProcessor.StartGetAccessRecordingFor(n8);
      Text.create(j8.content);
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
      if (!o8) {
        Text.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Text.pop();
    Column.pop();
  }
  SelectStyle(x7, y7 = null) {
    this.observeComponentCreation((g8, h8) => {
      ViewStackProcessor.StartGetAccessRecordingFor(g8);
      Column.create();
      Column.width(this.leftWidth - COMMON_MARGIN_VALUE);
      Column.alignItems(HorizontalAlign.Start);
      Column.margin({
        left: { id: -1, type: 10002, params: ['sys.float.margin_left'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.margin_right'], bundleName: '', moduleName: '' },
      });
      Column.onAppear(() => {
        this.isDuplicateLine = false;
        this.changeFlexAlign(FlexAlign.SpaceBetween);
      });
      if (!h8) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((b8, c8) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b8);
      Select.create(x7.options);
      Select.selected(this.selectedIndex);
      Select.value(this.selectValue);
      Select.onSelect((e8, f8) => {
        this.selectedIndex = e8;
        if (f8) {
          this.selectValue = f8;
        }
        if (x7.onSelect) {
          x7.onSelect(e8, f8);
        }
      });
      Select.font({
        size: { id: -1, type: 10002, params: ['sys.float.Body_L'], bundleName: '', moduleName: '' },
        weight: FontWeight.Medium,
      });
      if (!c8) {
        Select.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Select.pop();
    Column.pop();
  }
  PrimaryTitleStyle(o7, p7 = null) {
    this.observeComponentCreation((v7, w7) => {
      ViewStackProcessor.StartGetAccessRecordingFor(v7);
      Column.create();
      Column.width(this.leftWidth - COMMON_MARGIN_VALUE);
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
      if (!w7) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((s7, t7) => {
      ViewStackProcessor.StartGetAccessRecordingFor(s7);
      Text.create(o7.content);
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
      if (!t7) {
        Text.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Text.pop();
    Column.pop();
  }
  ButtonStyle(i6, j6 = null) {
    this.observeComponentCreation((m7, n7) => {
      ViewStackProcessor.StartGetAccessRecordingFor(m7);
      Row.create();
      Row.margin({
        left: { id: -1, type: 10002, params: ['sys.float.padding_level1'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.padding_level5'], bundleName: '', moduleName: '' },
      });
      Row.width(this.rightWidth - BUTTON_MARGIN_VALUE);
      Row.justifyContent(FlexAlign.End);
      Row.focusable(true);
      if (!n7) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((k7, l7) => {
      ViewStackProcessor.StartGetAccessRecordingFor(k7);
      Stack.create();
      Stack.focusable(true);
      if (!l7) {
        Stack.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((n6, o6) => {
      ViewStackProcessor.StartGetAccessRecordingFor(n6);
      If.create();
      if (i6) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((v6, w6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(v6);
            Row.create();
            Row.padding({
              left: { id: -1, type: 10002, params: ['sys.float.padding_level3'], bundleName: '', moduleName: '' },
              right: { id: -1, type: 10002, params: ['sys.float.padding_level3'], bundleName: '', moduleName: '' },
            });
            Row.margin({
              bottom: { id: -1, type: 10002, params: ['sys.float.padding_level2'], bundleName: '', moduleName: '' },
            });
            Row.backgroundColor(this.buttonBgColor);
            Row.focusable(true);
            Row.constraintSize({ minHeight: BUTTON_HEIGHT });
            Row.justifyContent(FlexAlign.End);
            Row.borderRadius({ id: -1, type: 10002, params: ['sys.float.corner_radius_level4'], bundleName: '', moduleName: '' });
            ViewStackProcessor.visualState('focused');
            Row.border({
              radius: { id: -1, type: 10002, params: ['sys.float.corner_radius_level4'], bundleName: '', moduleName: '' },
              width: this.buttonStyleWidth,
              color: { id: -1, type: 10001, params: ['sys.color.interactive_focus'], bundleName: '', moduleName: '' },
              style: BorderStyle.Solid,
            });
            Row.backgroundColor({ id: -1, type: 10001, params: ['sys.color.interactive_focus'], bundleName: '', moduleName: '' });
            ViewStackProcessor.visualState('pressed');
            Row.border({
              radius: { id: -1, type: 10002, params: ['sys.float.corner_radius_level4'], bundleName: '', moduleName: '' },
              color: { id: -1, type: 10001, params: ['sys.color.interactive_pressed'], bundleName: '', moduleName: '' },
            });
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
            Row.onHover((j7) => {
              if (j7) {
                this.buttonBgColor = { id: -1, type: 10001, params: ['sys.color.interactive_hover'], bundleName: '', moduleName: '' };
              }
              else {
                this.buttonBgColor = { id: -1, type: 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], bundleName: '', moduleName: '' };
              }
            });
            Row.onTouch((i7) => {
              if (i7.type === TouchType.Down) {
                this.buttonBgColor = { id: -1, type: 10001, params: ['sys.color.interactive_pressed'], bundleName: '', moduleName: '' };
              }
              if (i7.type === TouchType.Up) {
                this.buttonBgColor = { id: -1, type: 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], bundleName: '', moduleName: '' };
              }
            });
            Row.onKeyEvent((h7) => {
              if (h7.keyCode === KeyCode.KEYCODE_ENTER || h7.keyCode === KeyCode.KEYCODE_SPACE) {
                if (i6.action) {
                  i6.action();
                }
              }
            });
            Row.onClick((g7) => {
              if (i6.action) {
                i6.action();
              }
            });
            Row.onAreaChange((e7, f7) => {
              this.buttonStyleWidth = Number(f7.width);
              this.buttonStyleHeight = Number(f7.height);
            });
            if (!w6) {
              Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((t6, u6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t6);
            Text.create(i6.value);
            __Text__secondaryTitleStyles({
              fontWeight: FontWeight.Medium,
              maxLines: SINGLE_LINE_NUM,
              fontColor: { id: -1, type: 10001, params: ['sys.color.font_emphasize'], bundleName: '', moduleName: '' },
            });
            Text.focusable(true);
            if (!u6) {
              Text.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          Text.pop();
          Row.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!o6) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    Stack.pop();
    Row.pop();
  }
  TextArrowStyle(w4, x4 = null) {
    this.observeComponentCreation((g6, h6) => {
      ViewStackProcessor.StartGetAccessRecordingFor(g6);
      Row.create();
      Row.focusable(true);
      Row.width(this.rightWidth - TEXT_ARROW_MARGIN_VALUE);
      Row.justifyContent(FlexAlign.End);
      Row.margin({
        left: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
      });
      if (!h6) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((e6, f6) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e6);
      Stack.create();
      if (!f6) {
        Stack.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((p5, q5) => {
      ViewStackProcessor.StartGetAccessRecordingFor(p5);
      Row.create();
      Row.alignItems(VerticalAlign.Center);
      Row.borderRadius({ id: -1, type: 10002, params: ['sys.float.corner_radius_level4'], bundleName: '', moduleName: '' });
      Row.focusable(true);
      Row.backgroundColor(this.textArrowBgColor);
      Row.constraintSize({ minHeight: BUTTON_ZONE_SIZE });
      Row.onFocus(() => {
        this.textArrowFocus = true;
      });
      Row.onBlur(() => {
        this.textArrowFocus = false;
      });
      Row.padding({
        left: { id: -1, type: 10002, params: ['sys.float.padding_level2'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
      });
      Row.onHover((d6) => {
        if (d6) {
          this.textArrowBgColor = { id: -1, type: 10001, params: ['sys.color.interactive_hover'], bundleName: '', moduleName: '' };
        }
        else {
          this.textArrowBgColor = { id: -1, type: 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], bundleName: '', moduleName: '' };
        }
      });
      Row.onTouch((c6) => {
        if (c6.type === TouchType.Down) {
          this.textArrowBgColor = { id: -1, type: 10001, params: ['sys.color.interactive_pressed'], bundleName: '', moduleName: '' };
        }
        if (c6.type === TouchType.Up) {
          this.textArrowBgColor = { id: -1, type: 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], bundleName: '', moduleName: '' };
        }
      });
      Row.onKeyEvent((b6) => {
        if (b6.keyCode === KeyCode.KEYCODE_ENTER || b6.keyCode === KeyCode.KEYCODE_SPACE) {
          if (w4.action) {
            w4.action();
          }
        }
      });
      Row.onClick((a6) => {
        if (w4.action) {
          w4.action();
        }
      });
      Row.onAreaChange((y5, z5) => {
        this.textArrowStyleWidth = Number(z5.width);
        this.textArrowStyleHeight = Number(z5.height);
      });
      if (!q5) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((i5, j5) => {
      ViewStackProcessor.StartGetAccessRecordingFor(i5);
      If.create();
      if (w4) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((n5, o5) => {
            ViewStackProcessor.StartGetAccessRecordingFor(n5);
            Text.create(w4.value);
            __Text__secondaryTitleStyles({
              maxLines: SINGLE_LINE_NUM,
              fontWeight: FontWeight.Regular,
              alignment: Alignment.End,
            });
            Text.margin({
              right: { id: -1, type: 10002, params: ['sys.float.padding_level2'], bundleName: '', moduleName: '' },
              top: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
              bottom: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
            });
            Text.focusable(true);
            Text.constraintSize({ maxWidth: this.getMaxArrowTextWidth() });
            if (!o5) {
              Text.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          Text.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!j5) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.observeComponentCreation((g5, h5) => {
      ViewStackProcessor.StartGetAccessRecordingFor(g5);
      Image.create({ id: -1, type: 20000, params: ['sys.media.ohos_ic_public_arrow_right'], bundleName: '', moduleName: '' });
      Image.fillColor({ id: -1, type: 10001, params: ['sys.color.ohos_id_color_tertiary'], bundleName: '', moduleName: '' });
      Image.width(ARROW_ICON_WIDTH);
      Image.height(ARROW_ICON_HEIGHT);
      Image.focusable(true);
      Image.draggable(false);
      if (!h5) {
        Image.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Row.pop();
    this.observeComponentCreation((e5, f5) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e5);
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
      Row.backgroundColor({ id: -1, type: 10001, params: ['sys.color.interactive_focus'], bundleName: '', moduleName: '' });
      ViewStackProcessor.visualState('pressed');
      Row.backgroundColor({ id: -1, type: 10001, params: ['sys.color.interactive_pressed'], bundleName: '', moduleName: '' });
      ViewStackProcessor.visualState('disabled');
      Row.opacity({ id: -1, type: 10002, params: ['sys.float.interactive_disable'], bundleName: '', moduleName: '' });
      ViewStackProcessor.visualState('normal');
      Row.border({
        radius: { id: -1, type: 10002, params: ['sys.float.corner_radius_level4'], bundleName: '', moduleName: '' },
        width: { id: -1, type: 10002, params: ['sys.float.border_none'], bundleName: '', moduleName: '' },
        color: { id: -1, type: 10001, params: ['sys.color.ohos_id_color_focused_outline_transparent'], bundleName: '', moduleName: '' },
      });
      ViewStackProcessor.visualState();
      if (!f5) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Row.pop();
    Stack.pop();
    Row.pop();
  }
  getMaxArrowTextWidth() {
    return this.rightWidth - getNumberByResource('padding_level2') * 2 - getNumberByResource('padding_level4') * 3 -
      ARROW_ICON_WIDTH;
  }
  IconGroupStyle(h3, i3 = null) {
    this.observeComponentCreation((u4, v4) => {
      ViewStackProcessor.StartGetAccessRecordingFor(u4);
      Row.create();
      Row.justifyContent(FlexAlign.End);
      Row.width(this.updateAreaWidth(true) - ICON_GROUP_MARGIN_VALUE);
      Row.focusable(true);
      Row.margin({
        left: { id: -1, type: 10002, params: ['sys.float.padding_level2'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.padding_level6'], bundleName: '', moduleName: '' },
      });
      if (!v4) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((l3, m3) => {
      ViewStackProcessor.StartGetAccessRecordingFor(l3);
      ForEach.create();
      const n3 = (p3, q3) => {
        const r3 = p3;
        this.observeComponentCreation((t3, u3) => {
          ViewStackProcessor.StartGetAccessRecordingFor(t3);
          If.create();
          if (Util.isResourceType(r3.value)) {
            this.ifElseBranchUpdateFunction(0, () => {
              this.observeComponentCreation((y3, z3) => {
                ViewStackProcessor.StartGetAccessRecordingFor(y3);
                If.create();
                if (q3 === INDEX_ZERO) {
                  this.ifElseBranchUpdateFunction(0, () => {
                    {
                      this.observeComponentCreation((o4, p4) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(o4);
                        if (p4) {
                          let q4 = new SingleIconStyle(this, {
                            item: {
                              iconOptions: {
                                icon: r3.value,
                                symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > q3 ?
                                  this.operationSymbolOptions[q3] : null,
                              },
                              action: r3.action,
                            }
                          }, undefined, o4, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 633 });
                          ViewPU.create(q4);
                          let r4 = () => {
                            return {
                              item: {
                                iconOptions: {
                                  icon: r3.value,
                                  symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > q3 ?
                                    this.operationSymbolOptions[q3] : null,
                                },
                                action: r3.action,
                              }
                            };
                          };
                          q4.paramsGenerator_ = r4;
                        }
                        else {
                          this.updateStateVarsOfChildByElmtId(o4, {});
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                      });
                    }
                  });
                }
                else if (q3 === INDEX_ONE || q3 === INDEX_TWO) {
                  this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation((k4, l4) => {
                      ViewStackProcessor.StartGetAccessRecordingFor(k4);
                      __Common__.create();
                      __Common__.margin({
                        left: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
                      });
                      if (!l4) {
                        __Common__.pop();
                      }
                      ViewStackProcessor.StopGetAccessRecording();
                    });
                    {
                      this.observeComponentCreation((e4, f4) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(e4);
                        if (f4) {
                          let g4 = new SingleIconStyle(this, {
                            item: {
                              action: r3.action,
                              iconOptions: {
                                icon: r3.value,
                                symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > q3 ?
                                  this.operationSymbolOptions[q3] : null,
                              },
                            }
                          }, undefined, e4, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 644 });
                          ViewPU.create(g4);
                          let h4 = () => {
                            return {
                              item: {
                                action: r3.action,
                                iconOptions: {
                                  icon: r3.value,
                                  symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > q3 ?
                                    this.operationSymbolOptions[q3] : null,
                                },
                              }
                            };
                          };
                          g4.paramsGenerator_ = h4;
                        }
                        else {
                          this.updateStateVarsOfChildByElmtId(e4, {});
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                      });
                    }
                    __Common__.pop();
                  });
                }
                else {
                  this.ifElseBranchUpdateFunction(2, () => {
                  });
                }
                if (!z3) {
                  If.pop();
                }
                ViewStackProcessor.StopGetAccessRecording();
              });
              If.pop();
            });
          }
          else {
            this.ifElseBranchUpdateFunction(1, () => {
            });
          }
          if (!u3) {
            If.pop();
          }
          ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
      };
      this.forEachUpdateFunction(l3, h3, n3, undefined, true, false);
      if (!m3) {
        ForEach.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    ForEach.pop();
    Row.pop();
  }
  updateAreaWidth(g3) {
    if (this.flexWidth === 0) {
      return 0;
    }
    if (g3) {
      this.rightWidth = Math.max(this.flexWidth / DIVIDEND_NUM, MAX_ICON_GROUP_WIDTH_VALUE);
    }
    else {
      this.rightWidth = this.flexWidth / DIVIDEND_NUM;
    }
    this.leftWidth = this.flexWidth - this.rightWidth;
    return this.rightWidth;
  }
  LoadingProcessStyle(y2 = null) {
    this.observeComponentCreation((e3, f3) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e3);
      Row.create();
      Row.focusable(true);
      Row.width(this.rightWidth - LOADING_MARGIN_VALUE);
      Row.justifyContent(FlexAlign.End);
      Row.padding({
        top: { id: -1, type: 10002, params: ['sys.float.padding_level2'], bundleName: '', moduleName: '' },
        bottom: { id: -1, type: 10002, params: ['sys.float.padding_level2'], bundleName: '', moduleName: '' },
      });
      Row.margin({
        left: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.margin_right'], bundleName: '', moduleName: '' },
      });
      if (!f3) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((b3, c3) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b3);
      LoadingProgress.create();
      LoadingProgress.width(LOADING_SIZE);
      LoadingProgress.height(LOADING_SIZE);
      LoadingProgress.color({ id: -1, type: 10001, params: ['sys.color.icon_secondary'], bundleName: '', moduleName: '' });
      LoadingProgress.focusable(true);
      LoadingProgress.onAppear(() => {
        this.isDuplicateLine = false;
      });
      if (!c3) {
        LoadingProgress.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Row.pop();
  }
  dummyFunction(t2 = null) {
    this.observeComponentCreation((v2, w2) => {
      ViewStackProcessor.StartGetAccessRecordingFor(v2);
      Row.create();
      Row.onAppear(() => {
        this.changeFlexAlign(FlexAlign.End);
      });
      if (!w2) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Row.pop();
  }
  aboutToAppear() {
    if (this.select) {
      this.selectedIndex = this.select.selected;
      this.selectValue = this.select.value;
    }
  }
  changeFlexAlign(s2) {
    if (this.flexAlign === s2) {
      return;
    }
    this.flexAlign = s2;
  }
  rerender() {
    this.updateDirtyElements();
  }
}
class SingleIconStyle extends ViewPU {
  constructor(m2, n2, o2, p2 = -1, q2 = undefined, r2) {
    super(m2, o2, p2, r2);
    if (typeof q2 === 'function') {
      this.paramsGenerator_ = q2;
    }
    this.__bgColor = new ObservedPropertyObjectPU({ id: -1, type: 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], bundleName: '', moduleName: '' }, this, 'bgColor');
    this.__isFocus = new ObservedPropertySimplePU(false, this, 'isFocus');
    this.item = null;
    this.setInitiallyProvidedValue(n2);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(l2) {
    if (l2.bgColor !== undefined) {
      this.bgColor = l2.bgColor;
    }
    if (l2.isFocus !== undefined) {
      this.isFocus = l2.isFocus;
    }
    if (l2.item !== undefined) {
      this.item = l2.item;
    }
  }
  updateStateVars(k2) {
  }
  purgeVariableDependenciesOnElmtId(j2) {
    this.__bgColor.purgeDependencyOnElmtId(j2);
    this.__isFocus.purgeDependencyOnElmtId(j2);
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
  set bgColor(i2) {
    this.__bgColor.set(i2);
  }
  get isFocus() {
    return this.__isFocus.get();
  }
  set isFocus(h2) {
    this.__isFocus.set(h2);
  }
  initialRender() {
    this.observeComponentCreation((o1, p1) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o1);
      If.create();
      if (this.item && this.item.iconOptions) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((t1, u1) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t1);
            Row.create();
            Row.focusable(true);
            Row.width(SINGLE_ICON_ZONE_SIZE);
            Row.height(SINGLE_ICON_ZONE_SIZE);
            Row.margin({
              bottom: { id: -1, type: 10002, params: ['sys.float.padding_level2'], bundleName: '', moduleName: '' },
            });
            Row.justifyContent(FlexAlign.Center);
            Row.borderRadius({ id: -1, type: 10002, params: ['sys.float.corner_radius_level4'], bundleName: '', moduleName: '' });
            Row.backgroundColor(this.bgColor);
            ViewStackProcessor.visualState('focused');
            Row.border({
              radius: { id: -1, type: 10002, params: ['sys.float.corner_radius_level4'], bundleName: '', moduleName: '' },
              width: BORDER_WIDTH,
              color: { id: -1, type: 10001, params: ['sys.color.interactive_focus'], bundleName: '', moduleName: '' },
              style: BorderStyle.Solid,
            });
            Row.backgroundColor({ id: -1, type: 10001, params: ['sys.color.interactive_focus'], bundleName: '', moduleName: '' });
            ViewStackProcessor.visualState('pressed');
            Row.backgroundColor({ id: -1, type: 10001, params: ['sys.color.interactive_pressed'], bundleName: '', moduleName: '' });
            ViewStackProcessor.visualState('disabled');
            Row.opacity({ id: -1, type: 10002, params: ['sys.float.interactive_disable'], bundleName: '', moduleName: '' });
            ViewStackProcessor.visualState();
            Row.onTouch((g2) => {
              if (g2.type === TouchType.Down) {
                this.bgColor = { id: -1, type: 10001, params: ['sys.color.interactive_pressed'], bundleName: '', moduleName: '' };
              }
              if (g2.type === TouchType.Up) {
                this.bgColor = { id: -1, type: 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], bundleName: '', moduleName: '' };
              }
            });
            Row.onHover((f2) => {
              if (f2) {
                this.bgColor = { id: -1, type: 10001, params: ['sys.color.interactive_hover'], bundleName: '', moduleName: '' };
              }
              else {
                this.bgColor = { id: -1, type: 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], bundleName: '', moduleName: '' };
              }
            });
            Row.onKeyEvent((c2) => {
              let d12;
              let e2;
              if (c2.keyCode === KeyCode.KEYCODE_ENTER || c2.keyCode === KeyCode.KEYCODE_SPACE) {
                if ((d2 = this.item) === null || d2 === void 0 ? void 0 : d2.action) {
                  (e2 = this.item) === null || e2 === void 0 ? void 0 : e2.action();
                }
              }
            });
            Row.onClick((z1) => {
              let a2;
              let b2;
              if ((a2 = this.item) === null || a2 === void 0 ? void 0 : a2.action) {
                (b2 = this.item) === null || b2 === void 0 ? void 0 : b2.action();
              }
            });
            if (!u1) {
              Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.IconZone.bind(this)();
          Row.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!p1) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
  }
  IconZone(h = null) {
    this.observeComponentCreation((j, k) => {
      ViewStackProcessor.StartGetAccessRecordingFor(j);
      If.create();
      if (this.item && this.item.iconOptions) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((o, p) => {
            ViewStackProcessor.StartGetAccessRecordingFor(o);
            If.create();
            if (Util.isSymbolResource(this.item.iconOptions.icon)) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation((y, z) => {
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
                  ViewStackProcessor.StartGetAccessRecordingFor(y);
                  SymbolGlyph.create((a1 = this.item.iconOptions) === null || a1 === void 0 ? void 0 : a1.icon);
                  SymbolGlyph.focusable(true);
                  SymbolGlyph.fontSize((d1 = (c1 = (b1 = this.item.iconOptions) === null || b1 === void 0 ? void 0 : b1.symbolicIconOption) === null || c1 === void 0 ? void 0 : c1.fontSize) !== null && d1 !== void 0 ? d1 : RIGHT_SINGLE_ICON_SIZE);
                  SymbolGlyph.fontColor((g1 = (f1 = (e1 = this.item.iconOptions) === null || e1 === void 0 ? void 0 : e1.symbolicIconOption) === null || f1 === void 0 ? void 0 : f1.fontColor) !== null && g1 !== void 0 ? g1 : [{ id: -1, type: 10001, params: ['sys.color.icon_primary'], bundleName: '', moduleName: '' }]);
                  SymbolGlyph.fontWeight((i1 = (h1 = this.item.iconOptions) === null || h1 === void 0 ? void 0 : h1.symbolicIconOption) === null || i1 === void 0 ? void 0 : i1.fontWeight);
                  SymbolGlyph.renderingStrategy((k1 = (j1 = this.item.iconOptions) === null || j1 === void 0 ? void 0 : j1.symbolicIconOption) === null || k1 === void 0 ? void 0 : k1.renderingStrategy);
                  SymbolGlyph.effectStrategy((m1 = (l1 = this.item.iconOptions) === null || l1 === void 0 ? void 0 : l1.symbolicIconOption) === null || m1 === void 0 ? void 0 : m1.effectStrategy);
                  if (!z) {
                    SymbolGlyph.pop();
                  }
                  ViewStackProcessor.StopGetAccessRecording();
                });
              });
            }
            else {
              this.ifElseBranchUpdateFunction(1, () => {
                this.observeComponentCreation((s, t) => {
                  let u;
                  let v;
                  ViewStackProcessor.StartGetAccessRecordingFor(s);
                  Image.create((v = (u = this.item) === null || u === void 0 ? void 0 : u.iconOptions) === null || v === void 0 ? void 0 : v.icon);
                  Image.fillColor({ id: -1, type: 10001, params: ['sys.color.icon_primary'], bundleName: '', moduleName: '' });
                  Image.width(RIGHT_SINGLE_ICON_SIZE);
                  Image.height(RIGHT_SINGLE_ICON_SIZE);
                  Image.focusable(true);
                  Image.draggable(false);
                  if (!t) {
                    Image.pop();
                  }
                  ViewStackProcessor.StopGetAccessRecording();
                });
              });
            }
            if (!p) {
              If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          If.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!k) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
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