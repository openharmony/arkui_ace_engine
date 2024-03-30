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
(function (b12) {
  b12[b12.TEXT_ARROW = 0] = 'TEXT_ARROW';
  b12[b12.BUTTON = 1] = 'BUTTON';
  b12[b12.ICON_GROUP = 2] = 'ICON_GROUP';
  b12[b12.LOADING = 3] = 'LOADING';
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
function __Text__secondaryTitleStyles(a12) {
  Text.fontSize({ id: -1, type: 10002, params: ['sys.float.Subtitle_S'], bundleName: '', moduleName: '' });
  Text.fontColor(a12?.fontColor ??
    { id: -1, type: 10001, params: ['sys.color.font_secondary'], bundleName: '', moduleName: '' });
  Text.fontWeight(a12?.fontWeight);
  Text.maxLines(a12?.maxLines);
  Text.textOverflow({ overflow: TextOverflow.Ellipsis });
  Text.align(a12?.alignment);
}
function __Text__primaryTitleStyles(z11) {
  Text.fontSize({ id: -1, type: 10002, params: ['sys.float.Subtitle_L'], bundleName: '', moduleName: '' });
  Text.fontColor({ id: -1, type: 10001, params: ['sys.color.font_primary'], bundleName: '', moduleName: '' });
  Text.fontWeight(z11?.fontWeight);
  Text.maxLines(z11?.maxLines);
  Text.textOverflow({ overflow: TextOverflow.Ellipsis });
  Text.align(z11?.alignment);
}
export class SubHeader extends ViewPU {
  constructor(t11, u11, v11, w11 = -1, x11 = undefined, y11) {
    super(t11, v11, w11, y11);
    if (typeof x11 === 'function') {
      this.paramsGenerator_ = x11;
    }
    this.__icon = new SynchedPropertyObjectOneWayPU(u11.icon, this, 'icon');
    this.iconSymbolOptions = null;
    this.__primaryTitle = new SynchedPropertyObjectOneWayPU(u11.primaryTitle, this, 'primaryTitle');
    this.__secondaryTitle = new SynchedPropertyObjectOneWayPU(u11.secondaryTitle, this, 'secondaryTitle');
    this.select = null;
    this.__operationType = new SynchedPropertySimpleOneWayPU(u11.operationType, this, 'operationType');
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
    this.setInitiallyProvidedValue(u11);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(s11) {
    if (s11.icon === undefined) {
      this.__icon.set(null);
    }
    if (s11.iconSymbolOptions !== undefined) {
      this.iconSymbolOptions = s11.iconSymbolOptions;
    }
    if (s11.primaryTitle === undefined) {
      this.__primaryTitle.set(null);
    }
    if (s11.secondaryTitle === undefined) {
      this.__secondaryTitle.set(null);
    }
    if (s11.select !== undefined) {
      this.select = s11.select;
    }
    if (s11.operationType === undefined) {
      this.__operationType.set(OperationType.BUTTON);
    }
    if (s11.operationItem !== undefined) {
      this.operationItem = s11.operationItem;
    }
    if (s11.operationSymbolOptions !== undefined) {
      this.operationSymbolOptions = s11.operationSymbolOptions;
    }
    if (s11.isDuplicateLine !== undefined) {
      this.isDuplicateLine = s11.isDuplicateLine;
    }
    if (s11.textArrowBgColor !== undefined) {
      this.textArrowBgColor = s11.textArrowBgColor;
    }
    if (s11.buttonBgColor !== undefined) {
      this.buttonBgColor = s11.buttonBgColor;
    }
    if (s11.flexWidth !== undefined) {
      this.flexWidth = s11.flexWidth;
    }
    if (s11.rightWidth !== undefined) {
      this.rightWidth = s11.rightWidth;
    }
    if (s11.leftWidth !== undefined) {
      this.leftWidth = s11.leftWidth;
    }
    if (s11.textArrowFocus !== undefined) {
      this.textArrowFocus = s11.textArrowFocus;
    }
    if (s11.buttonFocus !== undefined) {
      this.buttonFocus = s11.buttonFocus;
    }
    if (s11.textArrowStyleWidth !== undefined) {
      this.textArrowStyleWidth = s11.textArrowStyleWidth;
    }
    if (s11.textArrowStyleHeight !== undefined) {
      this.textArrowStyleHeight = s11.textArrowStyleHeight;
    }
    if (s11.buttonStyleWidth !== undefined) {
      this.buttonStyleWidth = s11.buttonStyleWidth;
    }
    if (s11.buttonStyleHeight !== undefined) {
      this.buttonStyleHeight = s11.buttonStyleHeight;
    }
    if (s11.iconTextStyleWidth !== undefined) {
      this.iconTextStyleWidth = s11.iconTextStyleWidth;
    }
    if (s11.iconTextWidth !== undefined) {
      this.iconTextWidth = s11.iconTextWidth;
    }
    if (s11.iconWidth !== undefined) {
      this.iconWidth = s11.iconWidth;
    }
    if (s11.selectedIndex !== undefined) {
      this.selectedIndex = s11.selectedIndex;
    }
    if (s11.selectValue !== undefined) {
      this.selectValue = s11.selectValue;
    }
    if (s11.flexAlign !== undefined) {
      this.flexAlign = s11.flexAlign;
    }
  }
  updateStateVars(r11) {
    this.__icon.reset(r11.icon);
    this.__primaryTitle.reset(r11.primaryTitle);
    this.__secondaryTitle.reset(r11.secondaryTitle);
    this.__operationType.reset(r11.operationType);
  }
  purgeVariableDependenciesOnElmtId(q11) {
    this.__icon.purgeDependencyOnElmtId(q11);
    this.__primaryTitle.purgeDependencyOnElmtId(q11);
    this.__secondaryTitle.purgeDependencyOnElmtId(q11);
    this.__operationType.purgeDependencyOnElmtId(q11);
    this.__isDuplicateLine.purgeDependencyOnElmtId(q11);
    this.__textArrowBgColor.purgeDependencyOnElmtId(q11);
    this.__buttonBgColor.purgeDependencyOnElmtId(q11);
    this.__flexWidth.purgeDependencyOnElmtId(q11);
    this.__rightWidth.purgeDependencyOnElmtId(q11);
    this.__leftWidth.purgeDependencyOnElmtId(q11);
    this.__textArrowFocus.purgeDependencyOnElmtId(q11);
    this.__buttonFocus.purgeDependencyOnElmtId(q11);
    this.__textArrowStyleWidth.purgeDependencyOnElmtId(q11);
    this.__textArrowStyleHeight.purgeDependencyOnElmtId(q11);
    this.__buttonStyleWidth.purgeDependencyOnElmtId(q11);
    this.__buttonStyleHeight.purgeDependencyOnElmtId(q11);
    this.__iconTextStyleWidth.purgeDependencyOnElmtId(q11);
    this.__iconTextWidth.purgeDependencyOnElmtId(q11);
    this.__iconWidth.purgeDependencyOnElmtId(q11);
    this.__selectedIndex.purgeDependencyOnElmtId(q11);
    this.__selectValue.purgeDependencyOnElmtId(q11);
    this.__flexAlign.purgeDependencyOnElmtId(q11);
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
  set icon(p11) {
    this.__icon.set(p11);
  }
  get primaryTitle() {
    return this.__primaryTitle.get();
  }
  set primaryTitle(o11) {
    this.__primaryTitle.set(o11);
  }
  get secondaryTitle() {
    return this.__secondaryTitle.get();
  }
  set secondaryTitle(n11) {
    this.__secondaryTitle.set(n11);
  }
  get operationType() {
    return this.__operationType.get();
  }
  set operationType(m11) {
    this.__operationType.set(m11);
  }
  get isDuplicateLine() {
    return this.__isDuplicateLine.get();
  }
  set isDuplicateLine(l11) {
    this.__isDuplicateLine.set(l11);
  }
  get textArrowBgColor() {
    return this.__textArrowBgColor.get();
  }
  set textArrowBgColor(k11) {
    this.__textArrowBgColor.set(k11);
  }
  get buttonBgColor() {
    return this.__buttonBgColor.get();
  }
  set buttonBgColor(j11) {
    this.__buttonBgColor.set(j11);
  }
  get flexWidth() {
    return this.__flexWidth.get();
  }
  set flexWidth(i11) {
    this.__flexWidth.set(i11);
  }
  get rightWidth() {
    return this.__rightWidth.get();
  }
  set rightWidth(h11) {
    this.__rightWidth.set(h11);
  }
  get leftWidth() {
    return this.__leftWidth.get();
  }
  set leftWidth(g11) {
    this.__leftWidth.set(g11);
  }
  get textArrowFocus() {
    return this.__textArrowFocus.get();
  }
  set textArrowFocus(f11) {
    this.__textArrowFocus.set(f11);
  }
  get buttonFocus() {
    return this.__buttonFocus.get();
  }
  set buttonFocus(e11) {
    this.__buttonFocus.set(e11);
  }
  get textArrowStyleWidth() {
    return this.__textArrowStyleWidth.get();
  }
  set textArrowStyleWidth(d11) {
    this.__textArrowStyleWidth.set(d11);
  }
  get textArrowStyleHeight() {
    return this.__textArrowStyleHeight.get();
  }
  set textArrowStyleHeight(c11) {
    this.__textArrowStyleHeight.set(c11);
  }
  get buttonStyleWidth() {
    return this.__buttonStyleWidth.get();
  }
  set buttonStyleWidth(b11) {
    this.__buttonStyleWidth.set(b11);
  }
  get buttonStyleHeight() {
    return this.__buttonStyleHeight.get();
  }
  set buttonStyleHeight(a11) {
    this.__buttonStyleHeight.set(a11);
  }
  get iconTextStyleWidth() {
    return this.__iconTextStyleWidth.get();
  }
  set iconTextStyleWidth(z10) {
    this.__iconTextStyleWidth.set(z10);
  }
  get iconTextWidth() {
    return this.__iconTextWidth.get();
  }
  set iconTextWidth(y10) {
    this.__iconTextWidth.set(y10);
  }
  get iconWidth() {
    return this.__iconWidth.get();
  }
  set iconWidth(x10) {
    this.__iconWidth.set(x10);
  }
  get selectedIndex() {
    return this.__selectedIndex.get();
  }
  set selectedIndex(w10) {
    this.__selectedIndex.set(w10);
  }
  get selectValue() {
    return this.__selectValue.get();
  }
  set selectValue(v10) {
    this.__selectValue.set(v10);
  }
  get flexAlign() {
    return this.__flexAlign.get();
  }
  set flexAlign(u10) {
    this.__flexAlign.set(u10);
  }
  initialRender() {
    this.observeComponentCreation2((o10, p10) => {
      Row.create();
      Row.width('100%');
      Row.alignItems(VerticalAlign.Bottom);
      Row.justifyContent(this.flexAlign);
      Row.focusable(true);
      Row.onAreaChange((r10, s10) => {
        let t10 = Number(s10.width);
        this.flexWidth = t10;
        this.updateAreaWidth(false);
      });
      Row.constraintSize({ minHeight: this.isDuplicateLine ? DOUBLE_LINE_HEIGHT : SINGLE_LINE_HEIGHT });
    }, Row);
    this.leftArea.bind(this)();
    this.rightArea.bind(this)();
    Row.pop();
  }
  leftArea(d10 = null) {
    this.observeComponentCreation2((f10, g10) => {
      If.create();
      if (this.secondaryTitle && this.icon) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.IconSecondaryTitleStyle.bind(this)(makeBuilderParameterProxy('IconSecondaryTitleStyle', {
            content: () => (this['__secondaryTitle'] ? this['__secondaryTitle'] : this['secondaryTitle']),
            iconOptions: () => ({
              icon: this.icon,
              symbolicIconOption: this.iconSymbolOptions,
            })
          }));
        });
      }
      else if (this.secondaryTitle && this.primaryTitle) {
        this.ifElseBranchUpdateFunction(1, () => {
          this.SubTitleStyle.bind(this)(makeBuilderParameterProxy('SubTitleStyle',
            {
              content: () => (this['__primaryTitle'] ? this['__primaryTitle'] : this['primaryTitle']),
              subContent: () => (this['__secondaryTitle'] ? this['__secondaryTitle'] : this['secondaryTitle'])
            }));
        });
      }
      else if (this.secondaryTitle) {
        this.ifElseBranchUpdateFunction(2, () => {
          this.SecondTitleStyle.bind(this)(makeBuilderParameterProxy('SecondTitleStyle',
            { content: () => (this['__secondaryTitle'] ? this['__secondaryTitle'] : this['secondaryTitle']) }));
        });
      }
      else if (this.select) {
        this.ifElseBranchUpdateFunction(3, () => {
          this.SelectStyle.bind(this)(this.select);
        });
      }
      else if (this.primaryTitle) {
        this.ifElseBranchUpdateFunction(4, () => {
          this.PrimaryTitleStyle.bind(this)(makeBuilderParameterProxy('PrimaryTitleStyle',
            { content: () => (this['__primaryTitle'] ? this['__primaryTitle'] : this['primaryTitle']) }));
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
  IconSecondaryTitleStyle(f8, g8 = null) {
    this.observeComponentCreation2((c9, d9) => {
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
      Row.onAreaChange((g9, h9) => {
        this.iconTextStyleWidth = Number(h9.width);
        this.updateMaxIconTextWidth();
      });
    }, Row);
    this.observeComponentCreation2((x8, y8) => {
      Row.create();
      Row.onAreaChange((a9, b9) => {
        this.iconWidth = Number(b9.width);
        this.updateMaxIconTextWidth();
      });
    }, Row);
    this.observeComponentCreation2((n8, o8) => {
      If.create();
      if (Util.isSymbolResource(f8.iconOptions?.icon)) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((v8, w8) => {
            SymbolGlyph.create(f8.iconOptions?.icon);
            SymbolGlyph.focusable(true);
            SymbolGlyph.fontSize(f8.iconOptions?.symbolicIconOption?.fontSize ?? LEFT_ICON_SIZE);
            SymbolGlyph.fontColor(f8.iconOptions?.symbolicIconOption?.fontColor ??
              [{ id: -1, type: 10001, params: ['sys.color.icon_secondary'], bundleName: '', moduleName: '' }]);
            SymbolGlyph.fontWeight(f8.iconOptions?.symbolicIconOption?.fontWeight);
            SymbolGlyph.renderingStrategy(f8.iconOptions?.symbolicIconOption?.renderingStrategy);
            SymbolGlyph.effectStrategy(f8.iconOptions?.symbolicIconOption?.effectStrategy);
            SymbolGlyph.margin({
              right: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' }
            });
          }, SymbolGlyph);
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((r8, s8) => {
            Image.create(f8.iconOptions?.icon);
            Image.width(LEFT_ICON_SIZE);
            Image.height(LEFT_ICON_SIZE);
            Image.margin({
              right: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' }
            });
            Image.draggable(false);
          }, Image);
        });
      }
    }, If);
    If.pop();
    Row.pop();
    this.observeComponentCreation2((l8, m8) => {
      Text.create(f8.content);
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
  updateMaxIconTextWidth() {
    this.iconTextWidth = this.iconTextStyleWidth - getNumberByResource('padding_level6') - this.iconWidth -
      getNumberByResource('padding_level6');
  }
  SubTitleStyle(t7, u7 = null) {
    this.observeComponentCreation2((c8, d8) => {
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
    }, Column);
    this.observeComponentCreation2((a8, b8) => {
      Text.create(t7.content);
      __Text__primaryTitleStyles({
        fontWeight: FontWeight.Bold,
        maxLines: SINGLE_LINE_NUM,
        alignment: Alignment.Start,
      });
      Text.width('100%');
    }, Text);
    Text.pop();
    this.observeComponentCreation2((y7, z7) => {
      Text.create(t7.subContent);
      __Text__secondaryTitleStyles({
        maxLines: SINGLE_LINE_NUM,
        fontWeight: FontWeight.Regular,
        alignment: Alignment.Start,
      });
      Text.width('100%');
      Text.margin({
        top: { id: -1, type: 10002, params: ['sys.float.padding_level1'], bundleName: '', moduleName: '' },
      });
    }, Text);
    Text.pop();
    Column.pop();
  }
  SecondTitleStyle(k7, l7 = null) {
    this.observeComponentCreation2((r7, s7) => {
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
    }, Column);
    this.observeComponentCreation2((o7, p7) => {
      Text.create(k7.content);
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
  SelectStyle(y6, z6 = null) {
    this.observeComponentCreation2((h7, i7) => {
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
    }, Column);
    this.observeComponentCreation2((c7, d7) => {
      Select.create(y6.options);
      Select.selected(ObservedObject.GetRawObject(this.selectedIndex));
      Select.value(ObservedObject.GetRawObject(this.selectValue));
      Select.onSelect((f7, g7) => {
        this.selectedIndex = f7;
        if (g7) {
          this.selectValue = g7;
        }
        if (y6.onSelect) {
          y6.onSelect(f7, g7);
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
  PrimaryTitleStyle(p6, q6 = null) {
    this.observeComponentCreation2((w6, x6) => {
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
    }, Column);
    this.observeComponentCreation2((t6, u6) => {
      Text.create(p6.content);
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
  ButtonStyle(l5, m5 = null) {
    this.observeComponentCreation2((n6, o6) => {
      Row.create();
      Row.margin({
        left: { id: -1, type: 10002, params: ['sys.float.padding_level1'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.padding_level5'], bundleName: '', moduleName: '' },
      });
      Row.width(this.rightWidth - BUTTON_MARGIN_VALUE);
      Row.justifyContent(FlexAlign.End);
      Row.focusable(true);
    }, Row);
    this.observeComponentCreation2((l6, m6) => {
      Stack.create();
      Stack.focusable(true);
    }, Stack);
    this.observeComponentCreation2((q5, r5) => {
      If.create();
      if (l5) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((y5, z5) => {
            Row.create();
            Row.padding({
              left: { id: -1, type: 10002, params: ['sys.float.padding_level3'], bundleName: '', moduleName: '' },
              right: { id: -1, type: 10002, params: ['sys.float.padding_level3'], bundleName: '', moduleName: '' },
            });
            Row.margin({
              bottom: { id: -1, type: 10002, params: ['sys.float.padding_level2'], bundleName: '', moduleName: '' },
            });
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
            Row.border({
              radius: {
                id: -1, type: 10002, params: ['sys.float.corner_radius_level4'],
                bundleName: '', moduleName: ''
              },
              color: { id: -1, type: 10001, params: ['sys.color.interactive_pressed'], bundleName: '', moduleName: '' },
            });
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
            Row.onHover((k6) => {
              if (k6) {
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
            Row.onTouch((j6) => {
              if (j6.type === TouchType.Down) {
                if (l5.action) {
                  l5.action();
                }
                this.buttonBgColor = {
                  id: -1, type: 10001,
                  params: ['sys.color.interactive_pressed'], bundleName: '', moduleName: ''
                };
              }
              if (j6.type === TouchType.Up) {
                this.buttonBgColor = {
                  id: -1, type: 10001,
                  params: ['sys.color.ohos_id_color_sub_background_transparent'], bundleName: '', moduleName: ''
                };
              }
            });
            Row.onKeyEvent((i6) => {
              if (i6.keyCode === KeyCode.KEYCODE_ENTER || i6.keyCode === KeyCode.KEYCODE_SPACE) {
                if (l5.action) {
                  l5.action();
                }
              }
            });
            Row.onAreaChange((g6, h6) => {
              this.buttonStyleWidth = Number(h6.width);
              this.buttonStyleHeight = Number(h6.height);
            });
          }, Row);
          this.observeComponentCreation2((w5, x5) => {
            Text.create(l5.value);
            __Text__secondaryTitleStyles({
              fontWeight: FontWeight.Medium,
              maxLines: SINGLE_LINE_NUM,
              fontColor: { id: -1, type: 10001, params: ['sys.color.font_emphasize'], bundleName: '', moduleName: '' },
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
  TextArrowStyle(b4, c4 = null) {
    this.observeComponentCreation2((j5, k5) => {
      Row.create();
      Row.focusable(true);
      Row.width(this.rightWidth - TEXT_ARROW_MARGIN_VALUE);
      Row.justifyContent(FlexAlign.End);
      Row.margin({
        left: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
      });
    }, Row);
    this.observeComponentCreation2((h5, i5) => {
      Stack.create();
    }, Stack);
    this.observeComponentCreation2((u4, v4) => {
      Row.create();
      Row.alignItems(VerticalAlign.Center);
      Row.borderRadius({
        id: -1, type: 10002, params: ['sys.float.corner_radius_level4'],
        bundleName: '', moduleName: ''
      });
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
        left: { id: -1, type: 10002, params: ['sys.float.padding_level2'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
      });
      Row.onHover((g5) => {
        if (g5) {
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
      Row.onTouch((f5) => {
        if (f5.type === TouchType.Down) {
          if (b4.action) {
            b4.action();
          }
          this.textArrowBgColor = {
            id: -1, type: 10001, params: ['sys.color.interactive_pressed'],
            bundleName: '', moduleName: ''
          };
        }
        if (f5.type === TouchType.Up) {
          this.textArrowBgColor = {
            id: -1, type: 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'],
            bundleName: '', moduleName: ''
          };
        }
      });
      Row.onKeyEvent((e5) => {
        if (e5.keyCode === KeyCode.KEYCODE_ENTER || e5.keyCode === KeyCode.KEYCODE_SPACE) {
          if (b4.action) {
            b4.action();
          }
        }
      });
      Row.onAreaChange((c5, d5) => {
        this.textArrowStyleWidth = Number(d5.width);
        this.textArrowStyleHeight = Number(d5.height);
      });
    }, Row);
    this.observeComponentCreation2((n4, o4) => {
      If.create();
      if (b4) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((s4, t4) => {
            Text.create(b4.value);
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
    this.observeComponentCreation2((l4, m4) => {
      Image.create({
        id: -1, type: 20000, params: ['sys.media.ohos_ic_public_arrow_right'],
        bundleName: '', moduleName: ''
      });
      Image.fillColor({
        id: -1, type: 10001, params: ['sys.color.ohos_id_color_tertiary'],
        bundleName: '', moduleName: ''
      });
      Image.width(ARROW_ICON_WIDTH);
      Image.height(ARROW_ICON_HEIGHT);
      Image.focusable(true);
      Image.draggable(false);
    }, Image);
    Row.pop();
    this.observeComponentCreation2((j4, k4) => {
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
  getMaxArrowTextWidth() {
    return this.rightWidth - getNumberByResource('padding_level2') * 2 - getNumberByResource('padding_level4') * 3 -
      ARROW_ICON_WIDTH;
  }
  IconGroupStyle(m2, n2 = null) {
    this.observeComponentCreation2((z3, a4) => {
      Row.create();
      Row.justifyContent(FlexAlign.End);
      Row.width(this.updateAreaWidth(true) - ICON_GROUP_MARGIN_VALUE);
      Row.focusable(true);
      Row.margin({
        left: { id: -1, type: 10002, params: ['sys.float.padding_level2'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.padding_level6'], bundleName: '', moduleName: '' },
      });
    }, Row);
    this.observeComponentCreation2((q2, r2) => {
      ForEach.create();
      const s2 = (u2, v2) => {
        const w2 = u2;
        this.observeComponentCreation2((y2, z2) => {
          If.create();
          if (Util.isResourceType(w2.value)) {
            this.ifElseBranchUpdateFunction(0, () => {
              this.observeComponentCreation2((d3, e3) => {
                If.create();
                if (v2 === INDEX_ZERO) {
                  this.ifElseBranchUpdateFunction(0, () => {
                    {
                      this.observeComponentCreation2((t3, u3) => {
                        if (u3) {
                          let v3 = new SingleIconStyle(this, {
                            item: {
                              iconOptions: {
                                icon: w2.value,
                                symbolicIconOption:
                                  this.operationSymbolOptions && this.operationSymbolOptions.length > v2 ?
                                    this.operationSymbolOptions[v2] : null,
                              },
                              action: w2.action,
                            }
                          }, undefined, t3, () => { },
                            { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 624 });
                          ViewPU.create(v3);
                          let w3 = () => {
                            return {
                              item: {
                                iconOptions: {
                                  icon: w2.value,
                                  symbolicIconOption:
                                    this.operationSymbolOptions && this.operationSymbolOptions.length > v2 ?
                                      this.operationSymbolOptions[v2] : null,
                                },
                                action: w2.action,
                              }
                            };
                          };
                          v3.paramsGenerator_ = w3;
                        }
                        else {
                          this.updateStateVarsOfChildByElmtId(t3, {});
                        }
                      }, { name: 'SingleIconStyle' });
                    }
                  });
                }
                else if (v2 === INDEX_ONE || v2 === INDEX_TWO) {
                  this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((p3, q3) => {
                      __Common__.create();
                      __Common__.margin({
                        left: {
                          id: -1, type: 10002,
                          params: ['sys.float.padding_level4'], bundleName: '', moduleName: ''
                        },
                      });
                    }, __Common__);
                    {
                      this.observeComponentCreation2((j3, k3) => {
                        if (k3) {
                          let l3 = new SingleIconStyle(this, {
                            item: {
                              action: w2.action,
                              iconOptions: {
                                icon: w2.value,
                                symbolicIconOption:
                                  this.operationSymbolOptions && this.operationSymbolOptions.length > v2 ?
                                    this.operationSymbolOptions[v2] : null,
                              },
                            }
                          }, undefined, j3, () => { },
                            { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 635 });
                          ViewPU.create(l3);
                          let m3 = () => {
                            return {
                              item: {
                                action: w2.action,
                                iconOptions: {
                                  icon: w2.value,
                                  symbolicIconOption:
                                    this.operationSymbolOptions && this.operationSymbolOptions.length > v2 ?
                                      this.operationSymbolOptions[v2] : null,
                                },
                              }
                            };
                          };
                          l3.paramsGenerator_ = m3;
                        }
                        else {
                          this.updateStateVarsOfChildByElmtId(j3, {});
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
      this.forEachUpdateFunction(q2, m2, s2, undefined, true, false);
    }, ForEach);
    ForEach.pop();
    Row.pop();
  }
  updateAreaWidth(l2) {
    if (this.flexWidth === 0) {
      return 0;
    }
    if (l2) {
      this.rightWidth = Math.max(this.flexWidth / DIVIDEND_NUM, MAX_ICON_GROUP_WIDTH_VALUE);
    }
    else {
      this.rightWidth = this.flexWidth / DIVIDEND_NUM;
    }
    this.leftWidth = this.flexWidth - this.rightWidth;
    return this.rightWidth;
  }
  LoadingProcessStyle(d2 = null) {
    this.observeComponentCreation2((j2, k2) => {
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
    }, Row);
    this.observeComponentCreation2((g2, h2) => {
      LoadingProgress.create();
      LoadingProgress.width(LOADING_SIZE);
      LoadingProgress.height(LOADING_SIZE);
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
  dummyFunction(y1 = null) {
    this.observeComponentCreation2((a2, b2) => {
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
    if (typeof v1 === 'function') {
      this.paramsGenerator_ = v1;
    }
    this.__bgColor = new ObservedPropertyObjectPU({
      id: -1, type: 10001,
      params: ['sys.color.ohos_id_color_sub_background_transparent'], bundleName: '', moduleName: ''
    }, this, 'bgColor');
    this.__isFocus = new ObservedPropertySimplePU(false, this, 'isFocus');
    this.item = null;
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
            Row.width(SINGLE_ICON_ZONE_SIZE);
            Row.height(SINGLE_ICON_ZONE_SIZE);
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
              width: BORDER_WIDTH,
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
            Row.onTouch((l1) => {
              if (l1.type === TouchType.Down) {
                if (this.item?.action) {
                  this.item?.action();
                }
                this.bgColor = {
                  id: -1, type: 10001, params: ['sys.color.interactive_pressed'],
                  bundleName: '', moduleName: ''
                };
              }
              if (l1.type === TouchType.Up) {
                this.bgColor = {
                  id: -1, type: 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'],
                  bundleName: '', moduleName: ''
                };
              }
            });
            Row.onHover((k1) => {
              if (k1) {
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
                  SymbolGlyph.fontSize(this.item.iconOptions?.symbolicIconOption?.fontSize ?? RIGHT_SINGLE_ICON_SIZE);
                  SymbolGlyph.fontColor(this.item.iconOptions?.symbolicIconOption?.fontColor ?? [{
                    id: -1, type: 10001,
                    params: ['sys.color.icon_primary'], bundleName: '', moduleName: ''
                  }]);
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
                  Image.fillColor({
                    id: -1, type: 10001, params: ['sys.color.icon_primary'],
                    bundleName: '', moduleName: ''
                  });
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