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
(function (k13) {
  k13[k13['TEXT_ARROW'] = 0] = 'TEXT_ARROW';
  k13[k13['BUTTON'] = 1] = 'BUTTON';
  k13[k13['ICON_GROUP'] = 2] = 'ICON_GROUP';
  k13[k13['LOADING'] = 3] = 'LOADING';
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
  var j13;
  Text.fontSize({ id: -1, type: 10002, params: ['sys.float.Subtitle_S'], bundleName: '', moduleName: '' });
  Text.fontColor((j13 = i13 === null || i13 === void 0 ? void 0 : i13.fontColor) !== null && j13 !== void 0 ? j13 : { id: -1, type: 10001, params: ['sys.color.font_secondary'], bundleName: '', moduleName: '' });
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
    this.setInitiallyProvidedValue(c13);
    this.finalizeConstruction();
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
    if (a13.textArrowWidth !== undefined) {
      this.textArrowWidth = a13.textArrowWidth;
    }
    if (a13.textArrowFocus !== undefined) {
      this.textArrowFocus = a13.textArrowFocus;
    }
    if (a13.buttonFocus !== undefined) {
      this.buttonFocus = a13.buttonFocus;
    }
    if (a13.arrowWidth !== undefined) {
      this.arrowWidth = a13.arrowWidth;
    }
    if (a13.buttonWidth !== undefined) {
      this.buttonWidth = a13.buttonWidth;
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
    this.__textArrowWidth.purgeDependencyOnElmtId(y12);
    this.__textArrowFocus.purgeDependencyOnElmtId(y12);
    this.__buttonFocus.purgeDependencyOnElmtId(y12);
    this.__arrowWidth.purgeDependencyOnElmtId(y12);
    this.__buttonWidth.purgeDependencyOnElmtId(y12);
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
  get textArrowWidth() {
    return this.__textArrowWidth.get();
  }
  set textArrowWidth(o12) {
    this.__textArrowWidth.set(o12);
  }
  get textArrowFocus() {
    return this.__textArrowFocus.get();
  }
  set textArrowFocus(n12) {
    this.__textArrowFocus.set(n12);
  }
  get buttonFocus() {
    return this.__buttonFocus.get();
  }
  set buttonFocus(m12) {
    this.__buttonFocus.set(m12);
  }
  get arrowWidth() {
    return this.__arrowWidth.get();
  }
  set arrowWidth(l12) {
    this.__arrowWidth.set(l12);
  }
  get buttonWidth() {
    return this.__buttonWidth.get();
  }
  set buttonWidth(k12) {
    this.__buttonWidth.set(k12);
  }
  get flexAlign() {
    return this.__flexAlign.get();
  }
  set flexAlign(j12) {
    this.__flexAlign.set(j12);
  }
  initialRender() {
    this.observeComponentCreation((d12, e12) => {
      ViewStackProcessor.StartGetAccessRecordingFor(d12);
      Flex.create({ justifyContent: this.flexAlign, alignItems: ItemAlign.End });
      Flex.focusable(true);
      Flex.onAreaChange((g12, h12) => {
        let i12 = Number(parseInt(h12.width.toString(), DEFAULT_VALUE));
        this.flexWidth = i12;
        hilog.debug(122, 'tytyty ', `flexWidth :${this.flexWidth}`);
      });
      Flex.height(this.isDuplicateLine ? DOUBLE_LINE_HEIGHT : SINGLE_LINE_HEIGHT);
      if (!e12) {
        Flex.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.leftArea.bind(this)();
    this.rightArea.bind(this)();
    Flex.pop();
  }
  leftArea(s11 = null) {
    this.observeComponentCreation((u11, v11) => {
      ViewStackProcessor.StartGetAccessRecordingFor(u11);
      If.create();
      if (this.secondaryTitle != null && this.icon != null) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.IconSecondTitleStyle.bind(this)(makeBuilderParameterProxy('IconSecondTitleStyle', {
            content: () => (this['__secondaryTitle'] ? this['__secondaryTitle'] : this['secondaryTitle']), iconOptions: () => ({
              icon: this.icon,
              symbolicIconOption: this.iconSymbolOptions,
            })
          }));
        });
      }
      else if (this.secondaryTitle != null && this.primaryTitle != null) {
        this.ifElseBranchUpdateFunction(1, () => {
          this.SubTitleStyle.bind(this)(makeBuilderParameterProxy('SubTitleStyle', { content: () => (this['__primaryTitle'] ? this['__primaryTitle'] : this['primaryTitle']), subContent: () => (this['__secondaryTitle'] ? this['__secondaryTitle'] : this['secondaryTitle']) }));
        });
      }
      else if (this.secondaryTitle != null) {
        this.ifElseBranchUpdateFunction(2, () => {
          this.SecondTitleStyle.bind(this)(makeBuilderParameterProxy('SecondTitleStyle', { content: () => (this['__secondaryTitle'] ? this['__secondaryTitle'] : this['secondaryTitle']) }));
        });
      }
      else if (this.select != null) {
        this.ifElseBranchUpdateFunction(3, () => {
          this.SelectStyle.bind(this)(this.select);
        });
      }
      else if (this.primaryTitle != null) {
        this.ifElseBranchUpdateFunction(4, () => {
          this.PrimaryTitleStyle.bind(this)(makeBuilderParameterProxy('PrimaryTitleStyle', { content: () => (this['__primaryTitle'] ? this['__primaryTitle'] : this['primaryTitle']) }));
        });
      }
      else {
        this.ifElseBranchUpdateFunction(5, () => {
          this.dummyFunction.bind(this)();
        });
      }
      if (!v11) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
  }
  rightArea(r10 = null) {
    this.observeComponentCreation((n11, o11) => {
      var p11;
      ViewStackProcessor.StartGetAccessRecordingFor(n11);
      If.create();
      if (this.log(`this.operationItem.length ${(p11 = this.operationItem) === null || p11 === void 0 ? void 0 : p11.length}`)) {
        this.ifElseBranchUpdateFunction(0, () => {
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
      if (this.operationType === OperationType.BUTTON && (this.operationItem && this.operationItem.length > 0)) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.ButtonStyle.bind(this)(this.operationItem[0]);
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
      if (this.operationType === OperationType.TEXT_ARROW && (this.operationItem && this.operationItem.length > 0)) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.TextArrowStyle.bind(this)(this.operationItem[0]);
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
    this.observeComponentCreation((x10, y10) => {
      ViewStackProcessor.StartGetAccessRecordingFor(x10);
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
      if (!y10) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
  }
  IconSecondTitleStyle(i9, j9 = null) {
    this.observeComponentCreation((o10, p10) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o10);
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
      if (!p10) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((p9, q9) => {
      var r9;
      ViewStackProcessor.StartGetAccessRecordingFor(p9);
      If.create();
      if (Util.isSymbolicResource((r9 = i9.iconOptions) === null || r9 === void 0 ? void 0 : r9.icon)) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((z9, a10) => {
            var b10;
            var c10;
            var d10;
            var e10;
            var f10;
            var g10;
            var h10;
            var i10;
            var j10;
            var k10;
            var l10;
            var m10;
            var n10;
            ViewStackProcessor.StartGetAccessRecordingFor(z9);
            SymbolGlyph.create((b10 = i9.iconOptions) === null || b10 === void 0 ? void 0 : b10.icon);
            SymbolGlyph.focusable(true);
            SymbolGlyph.fontSize((e10 = (d10 = (c10 = i9.iconOptions) === null || c10 === void 0 ? void 0 : c10.symbolicIconOption) === null || d10 === void 0 ? void 0 : d10.fontSize) !== null && e10 !== void 0 ? e10 : IMAGE_WIDTH_NUM);
            SymbolGlyph.fontColor((h10 = (g10 = (f10 = i9.iconOptions) === null || f10 === void 0 ? void 0 : f10.symbolicIconOption) === null || g10 === void 0 ? void 0 : g10.fontColor) !== null && h10 !== void 0 ? h10 : [{ id: -1, type: 10001, params: ['sys.color.icon_secondary'], bundleName: '', moduleName: '' }]);
            SymbolGlyph.fontWeight((j10 = (i10 = i9.iconOptions) === null || i10 === void 0 ? void 0 : i10.symbolicIconOption) === null || j10 === void 0 ? void 0 : j10.fontWeight);
            SymbolGlyph.renderingStrategy((l10 = (k10 = i9.iconOptions) === null || k10 === void 0 ? void 0 : k10.symbolicIconOption) === null || l10 === void 0 ? void 0 : l10.renderingStrategy);
            SymbolGlyph.effectStrategy((n10 = (m10 = i9.iconOptions) === null || m10 === void 0 ? void 0 : m10.symbolicIconOption) === null || n10 === void 0 ? void 0 : n10.effectStrategy);
            SymbolGlyph.margin({ right: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' } });
            if (!a10) {
              SymbolGlyph.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation((u9, v9) => {
            var w9;
            ViewStackProcessor.StartGetAccessRecordingFor(u9);
            Image.create((w9 = i9.iconOptions) === null || w9 === void 0 ? void 0 : w9.icon);
            Image.width(IMAGE_WIDTH_NUM);
            Image.height(IMAGE_WIDTH_NUM);
            Image.margin({ right: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' } });
            if (!v9) {
              Image.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
        });
      }
      if (!q9) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.observeComponentCreation((n9, o9) => {
      ViewStackProcessor.StartGetAccessRecordingFor(n9);
      Text.create(i9.content);
      __Text__secondaryTitleStyles({
        maxLines: DOUBLE_LINE_NUM,
        fontWeight: FontWeight.Medium,
        alignment: Alignment.Start,
      });
      if (!o9) {
        Text.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Text.pop();
    Row.pop();
  }
  SubTitleStyle(w8, x8 = null) {
    this.observeComponentCreation((f9, g9) => {
      ViewStackProcessor.StartGetAccessRecordingFor(f9);
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
      if (!g9) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((d9, e9) => {
      ViewStackProcessor.StartGetAccessRecordingFor(d9);
      Text.create(w8.content);
      __Text__primaryTitleStyles({
        fontWeight: FontWeight.Medium,
        maxLines: SINGLE_LINE_NUM,
        alignment: Alignment.Start,
      });
      if (!e9) {
        Text.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Text.pop();
    this.observeComponentCreation((b9, c9) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b9);
      Text.create(w8.subContent);
      __Text__secondaryTitleStyles({
        maxLines: SINGLE_LINE_NUM,
        fontWeight: FontWeight.Regular,
        alignment: Alignment.Start,
      });
      Text.margin({
        top: { id: -1, type: 10002, params: ['sys.float.padding_level1'], bundleName: '', moduleName: '' },
      });
      if (!c9) {
        Text.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Text.pop();
    Column.pop();
  }
  SecondTitleStyle(n8, o8 = null) {
    this.observeComponentCreation((u8, v8) => {
      ViewStackProcessor.StartGetAccessRecordingFor(u8);
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
      if (!v8) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((r8, s8) => {
      ViewStackProcessor.StartGetAccessRecordingFor(r8);
      Text.create(n8.content);
      __Text__secondaryTitleStyles({
        maxLines: DOUBLE_LINE_NUM,
        fontWeight: FontWeight.Medium,
        alignment: Alignment.Start,
      });
      Text.onAppear(() => {
        this.isDuplicateLine = false;
        this.changeFlexAlign(FlexAlign.SpaceBetween);
      });
      if (!s8) {
        Text.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Text.pop();
    Column.pop();
  }
  SelectStyle(b8, c8 = null) {
    this.observeComponentCreation((k8, l8) => {
      ViewStackProcessor.StartGetAccessRecordingFor(k8);
      Row.create();
      Row.margin({
        left: { id: -1, type: 10002, params: ['sys.float.margin_left'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.margin_right'], bundleName: '', moduleName: '' },
      });
      Row.onAppear(() => {
        this.isDuplicateLine = false;
        this.changeFlexAlign(FlexAlign.SpaceBetween);
      });
      if (!l8) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((f8, g8) => {
      ViewStackProcessor.StartGetAccessRecordingFor(f8);
      Select.create(b8.options);
      Select.selected(b8.selected);
      Select.value(b8.value);
      Select.onSelect((i8, j8) => {
        if (b8.onSelect) {
          b8.onSelect(i8, j8);
        }
      });
      Select.font({
        size: { id: -1, type: 10002, params: ['sys.float.Body_L'], bundleName: '', moduleName: '' },
        weight: FontWeight.Medium,
      });
      if (!g8) {
        Select.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Select.pop();
    Row.pop();
  }
  PrimaryTitleStyle(s7, t7 = null) {
    this.observeComponentCreation((z7, a8) => {
      ViewStackProcessor.StartGetAccessRecordingFor(z7);
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
      if (!a8) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((w7, x7) => {
      ViewStackProcessor.StartGetAccessRecordingFor(w7);
      Text.create(s7.content);
      __Text__primaryTitleStyles({
        fontWeight: FontWeight.Medium,
        maxLines: DOUBLE_LINE_NUM,
        alignment: Alignment.Start,
      });
      Text.onAppear(() => {
        this.isDuplicateLine = false;
        this.changeFlexAlign(FlexAlign.SpaceBetween);
      });
      if (!x7) {
        Text.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Text.pop();
    Column.pop();
  }
  ButtonStyle(f6, g6 = null) {
    this.observeComponentCreation((q7, r7) => {
      ViewStackProcessor.StartGetAccessRecordingFor(q7);
      Row.create();
      Row.margin({
        left: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.margin_right'], bundleName: '', moduleName: '' },
      });
      Row.constraintSize({ minWidth: this.flexWidth / DIVIDEND_NUM });
      Row.justifyContent(FlexAlign.End);
      Row.focusable(true);
      if (!r7) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((o7, p7) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o7);
      Stack.create();
      Stack.focusable(true);
      if (!p7) {
        Stack.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((k6, l6) => {
      ViewStackProcessor.StartGetAccessRecordingFor(k6);
      If.create();
      if (f6) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((a7, b7) => {
            ViewStackProcessor.StartGetAccessRecordingFor(a7);
            Row.create();
            Row.backgroundColor(this.buttonBgColor);
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
            Row.onHover((n7) => {
              if (n7) {
                this.buttonBgColor = { id: -1, type: 10001, params: ['sys.color.interactive_hover'], bundleName: '', moduleName: '' };
              }
              else {
                this.buttonBgColor = { id: -1, type: 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], bundleName: '', moduleName: '' };
              }
            });
            Row.onTouch((m7) => {
              if (m7.type === TouchType.Down) {
                if (f6.action) {
                  f6.action();
                }
                this.buttonBgColor = { id: -1, type: 10001, params: ['sys.color.interactive_pressed'], bundleName: '', moduleName: '' };
              }
              if (m7.type === TouchType.Up) {
                this.buttonBgColor = { id: -1, type: 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], bundleName: '', moduleName: '' };
              }
            });
            Row.onKeyEvent((l7) => {
              if (l7.keyCode === KeyCode.KEYCODE_ENTER || l7.keyCode === KeyCode.KEYCODE_SPACE) {
                if (f6.action) {
                  f6.action();
                }
              }
            });
            Row.onAreaChange((i7, j7) => {
              let k7 = Number(parseInt(j7.width.toString(), DEFAULT_VALUE));
              this.buttonWidth = k7;
            });
            if (!b7) {
              Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((y6, z6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(y6);
            Text.create(f6.value);
            __Text__secondaryTitleStyles({
              fontWeight: FontWeight.Medium,
              maxLines: SINGLE_LINE_NUM,
              fontColor: { id: -1, type: 10001, params: ['sys.color.font_emphasize'], bundleName: '', moduleName: '' },
            });
            Text.focusable(true);
            if (!z6) {
              Text.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          Text.pop();
          Row.pop();
          this.observeComponentCreation((r6, s6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(r6);
            If.create();
            if (this.buttonFocus) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation((w6, x6) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(w6);
                  Row.create();
                  Row.height(BUTTON_HEIGHT);
                  Row.width(this.buttonWidth);
                  Row.hitTestBehavior(HitTestMode.None);
                  Row.border({
                    width: { id: -1, type: 10002, params: ['sys.float.outline_extra_larger'], bundleName: '', moduleName: '' },
                    color: { id: -1, type: 10001, params: ['sys.color.interactive_focus'], bundleName: '', moduleName: '' },
                  });
                  Row.borderRadius({ id: -1, type: 10002, params: ['sys.float.corner_radius_level4'], bundleName: '', moduleName: '' });
                  if (!x6) {
                    Row.pop();
                  }
                  ViewStackProcessor.StopGetAccessRecording();
                });
                Row.pop();
              });
            }
            else {
              this.ifElseBranchUpdateFunction(1, () => {
              });
            }
            if (!s6) {
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
      if (!l6) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    Stack.pop();
    Row.pop();
  }
  IconGroupStyle(q4, r4 = null) {
    this.observeComponentCreation((d6, e6) => {
      ViewStackProcessor.StartGetAccessRecordingFor(d6);
      Row.create();
      Row.justifyContent(FlexAlign.End);
      Row.constraintSize({ minWidth: this.flexWidth / DIVIDEND_NUM });
      Row.focusable(true);
      Row.margin({
        left: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.margin_right'], bundleName: '', moduleName: '' },
      });
      if (!e6) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((u4, v4) => {
      ViewStackProcessor.StartGetAccessRecordingFor(u4);
      ForEach.create();
      const w4 = (y4, z4) => {
        const a5 = y4;
        this.observeComponentCreation((c5, d5) => {
          ViewStackProcessor.StartGetAccessRecordingFor(c5);
          If.create();
          if (Util.isResourceType(a5.value)) {
            this.ifElseBranchUpdateFunction(0, () => {
              this.observeComponentCreation((h5, i5) => {
                ViewStackProcessor.StartGetAccessRecordingFor(h5);
                If.create();
                if (z4 === INDEX_ZERO) {
                  this.ifElseBranchUpdateFunction(0, () => {
                    {
                      this.observeComponentCreation((x5, y5) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(x5);
                        if (y5) {
                          let z5 = new SingleIconStyle(this, {
                            item: {
                              iconOptions: {
                                icon: a5.value,
                                symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > z4 ?
                                  this.operationSymbolOptions[z4] : null,
                              },
                              action: a5.action,
                            }
                          }, undefined, x5, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 433 });
                          ViewPU.create(z5);
                          let a6 = () => {
                            return {
                              item: {
                                iconOptions: {
                                  icon: a5.value,
                                  symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > z4 ?
                                    this.operationSymbolOptions[z4] : null,
                                },
                                action: a5.action,
                              }
                            };
                          };
                          z5.paramsGenerator_ = a6;
                        }
                        else {
                          this.updateStateVarsOfChildByElmtId(x5, {});
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                      });
                    }
                  });
                }
                else if (z4 === INDEX_ONE || z4 === INDEX_TWO) {
                  this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation((t5, u5) => {
                      ViewStackProcessor.StartGetAccessRecordingFor(t5);
                      __Common__.create();
                      __Common__.margin({
                        left: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
                      });
                      if (!u5) {
                        __Common__.pop();
                      }
                      ViewStackProcessor.StopGetAccessRecording();
                    });
                    {
                      this.observeComponentCreation((n5, o5) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(n5);
                        if (o5) {
                          let p5 = new SingleIconStyle(this, {
                            item: {
                              iconOptions: {
                                icon: a5.value,
                                symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > z4 ?
                                  this.operationSymbolOptions[z4] : null,
                              },
                              action: a5.action,
                            }
                          }, undefined, n5, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 444 });
                          ViewPU.create(p5);
                          let q5 = () => {
                            return {
                              item: {
                                iconOptions: {
                                  icon: a5.value,
                                  symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > z4 ?
                                    this.operationSymbolOptions[z4] : null,
                                },
                                action: a5.action,
                              }
                            };
                          };
                          p5.paramsGenerator_ = q5;
                        }
                        else {
                          this.updateStateVarsOfChildByElmtId(n5, {});
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
                if (!i5) {
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
          if (!d5) {
            If.pop();
          }
          ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
      };
      this.forEachUpdateFunction(u4, this.operationItem, w4, undefined, true, false);
      if (!v4) {
        ForEach.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    ForEach.pop();
    Row.pop();
  }
  TextArrowStyle(v2, w2 = null) {
    this.observeComponentCreation((l4, m4) => {
      ViewStackProcessor.StartGetAccessRecordingFor(l4);
      Row.create();
      Row.focusable(true);
      Row.onAreaChange((o4, p4) => {
        this.textArrowWidth = Number(parseInt(p4.width.toString(), DEFAULT_VALUE));
        hilog.debug(122, 'tytyty ', `textArrowWidth ${this.textArrowWidth}`);
      });
      Row.constraintSize({ minWidth: this.flexWidth / DIVIDEND_NUM });
      Row.justifyContent(FlexAlign.End);
      Row.margin({
        left: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.margin_right'], bundleName: '', moduleName: '' },
      });
      if (!m4) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((j4, k4) => {
      ViewStackProcessor.StartGetAccessRecordingFor(j4);
      Stack.create();
      Stack.focusable(true);
      if (!k4) {
        Stack.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((w3, x3) => {
      ViewStackProcessor.StartGetAccessRecordingFor(w3);
      Row.create();
      Row.borderRadius({ id: -1, type: 10002, params: ['sys.float.corner_radius_level4'], bundleName: '', moduleName: '' });
      Row.focusable(true);
      Row.backgroundColor(this.textArrowBgColor);
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
      Row.onTouch((i4) => {
        if (i4.type === TouchType.Down) {
          if (v2.action) {
            v2.action();
          }
          this.textArrowBgColor = { id: -1, type: 10001, params: ['sys.color.interactive_pressed'], bundleName: '', moduleName: '' };
        }
        if (i4.type === TouchType.Up) {
          this.textArrowBgColor = { id: -1, type: 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], bundleName: '', moduleName: '' };
        }
      });
      Row.onHover((h4) => {
        if (h4) {
          this.textArrowBgColor = { id: -1, type: 10001, params: ['sys.color.interactive_hover'], bundleName: '', moduleName: '' };
        }
        else {
          this.textArrowBgColor = { id: -1, type: 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], bundleName: '', moduleName: '' };
        }
      });
      Row.onKeyEvent((g4) => {
        if (g4.keyCode === KeyCode.KEYCODE_ENTER || g4.keyCode === KeyCode.KEYCODE_SPACE) {
          if (v2.action) {
            v2.action();
          }
        }
      });
      Row.onAreaChange((e4, f4) => {
        this.arrowWidth = Number(parseInt(f4.width.toString(), DEFAULT_VALUE));
        hilog.debug(122, 'tytyty ', `arrowWidth ${this.arrowWidth}`);
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
      if (!x3) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((u3, v3) => {
      ViewStackProcessor.StartGetAccessRecordingFor(u3);
      Row.create();
      if (!v3) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((n3, o3) => {
      ViewStackProcessor.StartGetAccessRecordingFor(n3);
      If.create();
      if (v2) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((s3, t3) => {
            ViewStackProcessor.StartGetAccessRecordingFor(s3);
            Text.create(v2.value);
            __Text__secondaryTitleStyles({
              maxLines: SINGLE_LINE_NUM,
              fontWeight: FontWeight.Regular,
              alignment: Alignment.End,
            });
            Text.margin({
              right: { id: -1, type: 10002, params: ['sys.float.padding_level2'], bundleName: '', moduleName: '' },
            });
            Text.focusable(true);
            if (!t3) {
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
      if (!o3) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.observeComponentCreation((l3, m3) => {
      ViewStackProcessor.StartGetAccessRecordingFor(l3);
      Image.create({ id: -1, type: 20000, params: ['sys.media.ohos_ic_public_arrow_right'], bundleName: '', moduleName: '' });
      Image.fillColor({ id: -1, type: 10001, params: ['sys.color.ohos_id_color_tertiary'], bundleName: '', moduleName: '' });
      Image.width(IMAGE_WIDTH);
      Image.height(IMAGE_HEIGHT_NUM);
      Image.focusable(true);
      Image.draggable(false);
      if (!m3) {
        Image.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Row.pop();
    Row.pop();
    this.observeComponentCreation((e3, f3) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e3);
      If.create();
      if (this.textArrowFocus) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((j3, k3) => {
            ViewStackProcessor.StartGetAccessRecordingFor(j3);
            Row.create();
            Row.height(BUTTON_SIZE);
            Row.width(this.arrowWidth);
            Row.hitTestBehavior(HitTestMode.None);
            Row.border({
              width: { id: -1, type: 10002, params: ['sys.float.outline_extra_larger'], bundleName: '', moduleName: '' },
              color: { id: -1, type: 10001, params: ['sys.color.interactive_focus'], bundleName: '', moduleName: '' },
            });
            Row.borderRadius({ id: -1, type: 10002, params: ['sys.float.corner_radius_level4'], bundleName: '', moduleName: '' });
            if (!k3) {
              Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          Row.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!f3) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    Stack.pop();
    Row.pop();
  }
  LoadingProcessStyle(n2 = null) {
    this.observeComponentCreation((t2, u2) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t2);
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
      if (!u2) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((q2, r2) => {
      ViewStackProcessor.StartGetAccessRecordingFor(q2);
      LoadingProgress.create();
      LoadingProgress.width(IMAGE_HEIGHT_NUM);
      LoadingProgress.height(IMAGE_HEIGHT_NUM);
      LoadingProgress.color({ id: -1, type: 10001, params: ['sys.color.icon_secondary'], bundleName: '', moduleName: '' });
      LoadingProgress.focusable(true);
      LoadingProgress.onAppear(() => {
        this.isDuplicateLine = false;
      });
      if (!r2) {
        LoadingProgress.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Row.pop();
  }
  dummyFunction(i2 = null) {
    this.observeComponentCreation((k2, l2) => {
      ViewStackProcessor.StartGetAccessRecordingFor(k2);
      Row.create();
      Row.onAppear(() => {
        this.changeFlexAlign(FlexAlign.End);
      });
      if (!l2) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Row.pop();
  }
  log(h2) {
    hilog.debug(111, 'tytyty ', h2);
    return true;
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
    this.finalizeConstruction();
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
    this.observeComponentCreation((e, f) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      if (this.item && this.item.iconOptions) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((j1, k1) => {
            ViewStackProcessor.StartGetAccessRecordingFor(j1);
            Row.create();
            Row.focusable(true);
            Row.width(BUTTON_SIZE);
            Row.height(BUTTON_SIZE);
            Row.margin({
              bottom: { id: -1, type: 10002, params: ['sys.float.padding_level2'], bundleName: '', moduleName: '' },
            });
            Row.justifyContent(FlexAlign.Center);
            Row.borderRadius({ id: -1, type: 10002, params: ['sys.float.corner_radius_level4'], bundleName: '', moduleName: '' });
            Row.backgroundColor(this.bgColor);
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
            if (!k1) {
              Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((k, l) => {
            ViewStackProcessor.StartGetAccessRecordingFor(k);
            If.create();
            if (Util.isSymbolicResource(this.item.iconOptions.icon)) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation((u, v) => {
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
                  ViewStackProcessor.StartGetAccessRecordingFor(u);
                  SymbolGlyph.create((w = this.item.iconOptions) === null || w === void 0 ? void 0 : w.icon);
                  SymbolGlyph.focusable(true);
                  SymbolGlyph.fontSize((z = (y = (x = this.item.iconOptions) === null || x === void 0 ? void 0 : x.symbolicIconOption) === null || y === void 0 ? void 0 : y.fontSize) !== null && z !== void 0 ? z : IMAGE_HEIGHT_NUM);
                  SymbolGlyph.fontColor((c1 = (b1 = (a1 = this.item.iconOptions) === null || a1 === void 0 ? void 0 : a1.symbolicIconOption) === null || b1 === void 0 ? void 0 : b1.fontColor) !== null && c1 !== void 0 ? c1 : [{ id: -1, type: 10001, params: ['sys.color.icon_primary'], bundleName: '', moduleName: '' }]);
                  SymbolGlyph.fontWeight((e1 = (d1 = this.item.iconOptions) === null || d1 === void 0 ? void 0 : d1.symbolicIconOption) === null || e1 === void 0 ? void 0 : e1.fontWeight);
                  SymbolGlyph.renderingStrategy((g1 = (f1 = this.item.iconOptions) === null || f1 === void 0 ? void 0 : f1.symbolicIconOption) === null || g1 === void 0 ? void 0 : g1.renderingStrategy);
                  SymbolGlyph.effectStrategy((i1 = (h1 = this.item.iconOptions) === null || h1 === void 0 ? void 0 : h1.symbolicIconOption) === null || i1 === void 0 ? void 0 : i1.effectStrategy);
                  if (!v) {
                    SymbolGlyph.pop();
                  }
                  ViewStackProcessor.StopGetAccessRecording();
                });
              });
            }
            else {
              this.ifElseBranchUpdateFunction(1, () => {
                this.observeComponentCreation((o, p) => {
                  var q;
                  var r;
                  ViewStackProcessor.StartGetAccessRecordingFor(o);
                  Image.create((r = (q = this.item) === null || q === void 0 ? void 0 : q.iconOptions) === null || r === void 0 ? void 0 : r.icon);
                  Image.fillColor({ id: -1, type: 10001, params: ['sys.color.icon_primary'], bundleName: '', moduleName: '' });
                  Image.width(IMAGE_HEIGHT_NUM);
                  Image.height(IMAGE_HEIGHT_NUM);
                  Image.focusable(true);
                  if (!p) {
                    Image.pop();
                  }
                  ViewStackProcessor.StopGetAccessRecording();
                });
              });
            }
            if (!l) {
              If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          If.pop();
          Row.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!f) {
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
  static isSymbolicResource(b) {
    if (!Util.isResourceType(b)) {
      hilog.error(122, 'tytyty ', `isResourceType false`);
      return false;
    }
    let c = b;
    hilog.error(122, 'tytyty ', `resource.type ${c.type}  `);
    return c.type === RESOURCE_TYPE_SYMBOL;
  }
  static isResourceType(a) {
    if (!a) {
      return false;
    }
    if (typeof a === 'string' || typeof a === 'undefined') {
      return false;
    }
    hilog.error(122, 'tytyty ', `isResourceType true  `);
    return true;
  }
}
