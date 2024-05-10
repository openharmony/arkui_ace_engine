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
  Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {
  });
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
const PADDING_LEVEL_4 = 8;
const MAX_RIGHT_WIDTH = '34%';

export var OperationType;

(function (c12) {
  c12[c12['TEXT_ARROW'] = 0] = 'TEXT_ARROW';
  c12[c12['BUTTON'] = 1] = 'BUTTON';
  c12[c12['ICON_GROUP'] = 2] = 'ICON_GROUP';
  c12[c12['LOADING'] = 3] = 'LOADING';
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
  Text.fontSize({
    'id': -1,
    'type': 10002,
    params: ['sys.float.Subtitle_S'],
    'bundleName': '',
    'moduleName': ''
  });
  Text.fontColor(b12?.fontColor ?? {
    'id': -1,
    'type': 10001,
    params: ['sys.color.font_secondary'],
    'bundleName': '',
    'moduleName': ''
  });
  Text.fontWeight(b12?.fontWeight);
  Text.maxLines(b12?.maxLines);
  Text.textOverflow({ overflow: TextOverflow.Ellipsis });
  Text.align(b12?.alignment);
}

function __Text__primaryTitleStyles(a12) {
  Text.fontSize({
    'id': -1,
    'type': 10002,
    params: ['sys.float.Subtitle_L'],
    'bundleName': '',
    'moduleName': ''
  });
  Text.fontColor({
    'id': -1,
    'type': 10001,
    params: ['sys.color.font_primary'],
    'bundleName': '',
    'moduleName': ''
  });
  Text.fontWeight(a12?.fontWeight);
  Text.maxLines(a12?.maxLines);
  Text.textOverflow({ overflow: TextOverflow.Ellipsis });
  Text.align(a12?.alignment);
}

export class SubHeader extends ViewPU {
  constructor(u11, v11, w11, x11 = -1, y11 = undefined, z11) {
    super(u11, w11, x11, z11);
    if (typeof y11 === 'function') {
      this.paramsGenerator_ = y11;
    }
    this.__icon = new SynchedPropertyObjectOneWayPU(v11.icon, this, 'icon');
    this.iconSymbolOptions = null;
    this.__primaryTitle = new SynchedPropertyObjectOneWayPU(v11.primaryTitle, this, 'primaryTitle');
    this.__primaryTitleModifier = new ObservedPropertyObjectPU(new TextModifier(), this, 'primaryTitleModifier');
    this.__secondaryTitle = new SynchedPropertyObjectOneWayPU(v11.secondaryTitle, this, 'secondaryTitle');
    this.__secondaryTitleModifier = new ObservedPropertyObjectPU(new TextModifier(), this, 'secondaryTitleModifier');
    this.select = null;
    this.__operationType = new SynchedPropertySimpleOneWayPU(v11.operationType, this, 'operationType');
    this.operationItem = null;
    this.operationSymbolOptions = null;
    this.__isDuplicateLine = new ObservedPropertySimplePU(false, this, 'isDuplicateLine');
    this.__textArrowBgColor = new ObservedPropertyObjectPU({
      'id': -1,
      'type': 10001,
      params: ['sys.color.ohos_id_color_sub_background_transparent'],
      'bundleName': '',
      'moduleName': ''
    }, this, 'textArrowBgColor');
    this.__buttonBgColor = new ObservedPropertyObjectPU({
      'id': -1,
      'type': 10001,
      params: ['sys.color.ohos_id_color_sub_background_transparent'],
      'bundleName': '',
      'moduleName': ''
    }, this, 'buttonBgColor');
    this.__textArrowFocus = new ObservedPropertySimplePU(false, this, 'textArrowFocus');
    this.__buttonFocus = new ObservedPropertySimplePU(false, this, 'buttonFocus');
    this.__textArrowStyleWidth = new ObservedPropertySimplePU(0, this, 'textArrowStyleWidth');
    this.__textArrowStyleHeight = new ObservedPropertySimplePU(0, this, 'textArrowStyleHeight');
    this.__buttonStyleWidth = new ObservedPropertySimplePU(0, this, 'buttonStyleWidth');
    this.__buttonStyleHeight = new ObservedPropertySimplePU(0, this, 'buttonStyleHeight');
    this.__iconWidth = new ObservedPropertySimplePU(0, this, 'iconWidth');
    this.__selectedIndex = new ObservedPropertyObjectPU(-1, this, 'selectedIndex');
    this.__selectValue = new ObservedPropertyObjectPU('', this, 'selectValue');
    this.__flexAlign = new ObservedPropertySimplePU(FlexAlign.SpaceBetween, this, 'flexAlign');
    this.titleBuilder = undefined;
    this.__contentMargin = new SynchedPropertyObjectOneWayPU(v11.contentMargin, this, 'contentMargin');
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
    this.observeComponentCreation((v10, w10) => {
      ViewStackProcessor.StartGetAccessRecordingFor(v10);
      Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.End });
      Flex.width('100%');
      Flex.focusable(true);
      Flex.constraintSize({ minHeight: this.isDuplicateLine ? DOUBLE_LINE_HEIGHT : SINGLE_LINE_HEIGHT });
      if (!w10) {
        Flex.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((t10, u10) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t10);
      Row.create();
      Row.width('100%');
      Row.margin({
        left: this.contentMargin?.left ?? {
          'id': -1,
          'type': 10002,
          params: ['sys.float.margin_left'],
          'bundleName': '',
          'moduleName': ''
        },
        right: this.getMarginRight()
      });
      Row.flexShrink(1);
      if (!u10) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.leftArea.bind(this)(this);
    Row.pop();
    this.observeComponentCreation((r10, s10) => {
      ViewStackProcessor.StartGetAccessRecordingFor(r10);
      Row.create();
      Row.justifyContent(FlexAlign.End);
      Row.constraintSize({ maxWidth: this.getMaxWidth() });
      Row.flexShrink(0);
      if (!s10) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.rightArea.bind(this)(this);
    Row.pop();
    Flex.pop();
  }

  getMarginRight() {
    if (this.operationType === OperationType.LOADING || (this.operationItem && this.operationItem.length > 0)) {
      return {
        'id': -1,
        'type': 10002,
        params: ['sys.float.padding_level0'],
        'bundleName': '',
        'moduleName': ''
      };
    }
    return this.contentMargin?.right ?? {
      'id': -1,
      'type': 10002,
      params: ['sys.float.margin_right'],
      'bundleName': '',
      'moduleName': ''
    };
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
    this.observeComponentCreation((f10, g10) => {
      ViewStackProcessor.StartGetAccessRecordingFor(f10);
      If.create();
      if (this.titleBuilder) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.titleBuilder.bind(this)(d10 ? d10 : this);
        });
      }
      else if (this.secondaryTitle && this.icon) {
        this.ifElseBranchUpdateFunction(1, () => {
          this.IconSecondaryTitleStyle.bind(this)(makeBuilderParameterProxy('IconSecondaryTitleStyle', {
            content: () => (this['__secondaryTitle'] ? this['__secondaryTitle'] : this['secondaryTitle']),
            iconOptions: () => ({
              icon: this.icon,
              symbolicIconOption: this.iconSymbolOptions,
            })
          }), d10 ? d10 : this);
        });
      }
      else if (this.secondaryTitle && this.primaryTitle) {
        this.ifElseBranchUpdateFunction(2, () => {
          this.SubTitleStyle.bind(this)(makeBuilderParameterProxy('SubTitleStyle', {
            content: () => (this['__primaryTitle'] ? this['__primaryTitle'] : this['primaryTitle']),
            subContent: () => (this['__secondaryTitle'] ? this['__secondaryTitle'] : this['secondaryTitle'])
          }), d10 ? d10 : this);
        });
      }
      else if (this.secondaryTitle) {
        this.ifElseBranchUpdateFunction(3, () => {
          this.SecondTitleStyle.bind(this)(makeBuilderParameterProxy('SecondTitleStyle', {
            content: () => (this['__secondaryTitle'] ? this['__secondaryTitle'] : this['secondaryTitle'])
          }), d10 ? d10 : this);
        });
      }
      else if (this.select) {
        this.ifElseBranchUpdateFunction(4, () => {
          this.SelectStyle.bind(this)(this.select, d10 ? d10 : this);
        });
      }
      else if (this.primaryTitle) {
        this.ifElseBranchUpdateFunction(5, () => {
          this.PrimaryTitleStyle.bind(this)(makeBuilderParameterProxy('PrimaryTitleStyle', {
            content: () => (this['__primaryTitle'] ? this['__primaryTitle'] : this['primaryTitle'])
          }), d10 ? d10 : this);
        });
      }
      else {
        this.ifElseBranchUpdateFunction(6, () => {
          this.dummyFunction.bind(this)(d10 ? d10 : this);
        });
      }
      if (!g10) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
  }

  rightArea(i9 = null) {
    this.observeComponentCreation((z9, a10) => {
      ViewStackProcessor.StartGetAccessRecordingFor(z9);
      If.create();
      if (this.operationType === OperationType.BUTTON && (this.operationItem && this.operationItem.length > 0)) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.ButtonStyle.bind(this)(this.operationItem[0], i9 ? i9 : this);
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!a10) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.observeComponentCreation((v9, w9) => {
      ViewStackProcessor.StartGetAccessRecordingFor(v9);
      If.create();
      if (this.operationType === OperationType.TEXT_ARROW && (this.operationItem && this.operationItem.length > 0)) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.TextArrowStyle.bind(this)(this.operationItem[0], i9 ? i9 : this);
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!w9) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.observeComponentCreation((r9, s9) => {
      ViewStackProcessor.StartGetAccessRecordingFor(r9);
      If.create();
      if (this.operationType === OperationType.ICON_GROUP && (this.operationItem && this.operationItem.length > 0)) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.IconGroupStyle.bind(this)(this.operationItem, i9 ? i9 : this);
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!s9) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.observeComponentCreation((n9, o9) => {
      ViewStackProcessor.StartGetAccessRecordingFor(n9);
      If.create();
      if (this.operationType === OperationType.LOADING) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.LoadingProcessStyle.bind(this)(i9 ? i9 : this);
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!o9) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
  }

  IconSecondaryTitleStyle(o8, p8 = null) {
    this.observeComponentCreation((f9, g9) => {
      ViewStackProcessor.StartGetAccessRecordingFor(f9);
      Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.Center });
      Flex.padding({
        left: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level6'],
          'bundleName': '',
          'moduleName': ''
        },
        right: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level6'],
          'bundleName': '',
          'moduleName': ''
        },
        top: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level4'],
          'bundleName': '',
          'moduleName': ''
        },
        bottom: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level4'],
          'bundleName': '',
          'moduleName': ''
        },
      });
      Flex.onAppear(() => {
        this.isDuplicateLine = false;
        this.changeFlexAlign(FlexAlign.SpaceBetween);
      });
      if (!g9) {
        Flex.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((v8, w8) => {
      ViewStackProcessor.StartGetAccessRecordingFor(v8);
      If.create();
      if (Util.isSymbolResource(o8.iconOptions?.icon)) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((d9, e9) => {
            ViewStackProcessor.StartGetAccessRecordingFor(d9);
            SymbolGlyph.create(o8.iconOptions?.icon);
            SymbolGlyph.focusable(true);
            SymbolGlyph.fontSize(o8.iconOptions?.symbolicIconOption?.fontSize ?? LEFT_ICON_SIZE);
            SymbolGlyph.fontColor(o8.iconOptions?.symbolicIconOption?.fontColor ?? [{
              'id': -1,
              'type': 10001,
              params: ['sys.color.icon_secondary'],
              'bundleName': '',
              'moduleName': ''
            }]);
            SymbolGlyph.fontWeight(o8.iconOptions?.symbolicIconOption?.fontWeight);
            SymbolGlyph.renderingStrategy(o8.iconOptions?.symbolicIconOption?.renderingStrategy);
            SymbolGlyph.effectStrategy(o8.iconOptions?.symbolicIconOption?.effectStrategy);
            SymbolGlyph.margin({
              right: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level4'],
                'bundleName': '',
                'moduleName': ''
              }
            });
            SymbolGlyph.flexShrink(0);
            if (!e9) {
              SymbolGlyph.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation((z8, a9) => {
            ViewStackProcessor.StartGetAccessRecordingFor(z8);
            Image.create(o8.iconOptions?.icon);
            Image.width(LEFT_ICON_SIZE);
            Image.height(LEFT_ICON_SIZE);
            Image.margin({
              right: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level4'],
                'bundleName': '',
                'moduleName': ''
              }
            });
            Image.draggable(false);
            Image.flexShrink(0);
            if (!a9) {
              Image.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
        });
      }
      if (!w8) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.observeComponentCreation((t8, u8) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t8);
      Text.create(o8.content);
      __Text__secondaryTitleStyles({
        maxLines: DOUBLE_LINE_NUM,
        fontWeight: FontWeight.Medium,
        alignment: Alignment.Start,
      });
      Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.secondaryTitleModifier));
      Text.flexShrink(1);
      if (!u8) {
        Text.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Text.pop();
    Flex.pop();
  }

  SubTitleStyle(c8, d8 = null) {
    this.observeComponentCreation((l8, m8) => {
      ViewStackProcessor.StartGetAccessRecordingFor(l8);
      Column.create();
      Column.padding({
        left: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level0'],
          'bundleName': '',
          'moduleName': ''
        },
        right: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level0'],
          'bundleName': '',
          'moduleName': ''
        },
        top: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level4'],
          'bundleName': '',
          'moduleName': ''
        },
        bottom: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level4'],
          'bundleName': '',
          'moduleName': ''
        },
      });
      Column.alignItems(HorizontalAlign.Start);
      Column.onAppear(() => {
        this.isDuplicateLine = true;
        this.changeFlexAlign(FlexAlign.SpaceBetween);
      });
      if (!m8) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((j8, k8) => {
      ViewStackProcessor.StartGetAccessRecordingFor(j8);
      Text.create(c8.content);
      __Text__primaryTitleStyles({
        fontWeight: FontWeight.Bold,
        maxLines: SINGLE_LINE_NUM,
        alignment: Alignment.Start,
      });
      Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.primaryTitleModifier));
      Text.width('100%');
      if (!k8) {
        Text.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Text.pop();
    this.observeComponentCreation((h8, i8) => {
      ViewStackProcessor.StartGetAccessRecordingFor(h8);
      Text.create(c8.subContent);
      __Text__secondaryTitleStyles({
        maxLines: SINGLE_LINE_NUM,
        fontWeight: FontWeight.Regular,
        alignment: Alignment.Start,
      });
      Text.width('100%');
      Text.margin({
        top: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level1'],
          'bundleName': '',
          'moduleName': ''
        },
      });
      Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.secondaryTitleModifier));
      if (!i8) {
        Text.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Text.pop();
    Column.pop();
  }

  SecondTitleStyle(t7, u7 = null) {
    this.observeComponentCreation((a8, b8) => {
      ViewStackProcessor.StartGetAccessRecordingFor(a8);
      Column.create();
      Column.alignItems(HorizontalAlign.Start);
      Column.padding({
        left: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level6'],
          'bundleName': '',
          'moduleName': ''
        },
        right: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level6'],
          'bundleName': '',
          'moduleName': ''
        },
        top: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level4'],
          'bundleName': '',
          'moduleName': ''
        },
        bottom: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level4'],
          'bundleName': '',
          'moduleName': ''
        },
      });
      if (!b8) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((x7, y7) => {
      ViewStackProcessor.StartGetAccessRecordingFor(x7);
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
      if (!y7) {
        Text.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Text.pop();
    Column.pop();
  }

  SelectStyle(h7, i7 = null) {
    this.observeComponentCreation((q7, r7) => {
      ViewStackProcessor.StartGetAccessRecordingFor(q7);
      Column.create();
      Column.alignItems(HorizontalAlign.Start);
      Column.onAppear(() => {
        this.isDuplicateLine = false;
        this.changeFlexAlign(FlexAlign.SpaceBetween);
      });
      if (!r7) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((l7, m7) => {
      ViewStackProcessor.StartGetAccessRecordingFor(l7);
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
        size: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.Body_L'],
          'bundleName': '',
          'moduleName': ''
        },
        weight: FontWeight.Medium,
      });
      if (!m7) {
        Select.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Select.pop();
    Column.pop();
  }

  PrimaryTitleStyle(y6, z6 = null) {
    this.observeComponentCreation((f7, g7) => {
      ViewStackProcessor.StartGetAccessRecordingFor(f7);
      Column.create();
      Column.alignItems(HorizontalAlign.Start);
      Column.padding({
        left: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level0'],
          'bundleName': '',
          'moduleName': ''
        },
        right: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level0'],
          'bundleName': '',
          'moduleName': ''
        },
        top: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level4'],
          'bundleName': '',
          'moduleName': ''
        },
        bottom: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level4'],
          'bundleName': '',
          'moduleName': ''
        },
      });
      if (!g7) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((c7, d7) => {
      ViewStackProcessor.StartGetAccessRecordingFor(c7);
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
      if (!d7) {
        Text.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Text.pop();
    Column.pop();
  }

  ButtonStyle(k5, l5 = null) {
    this.observeComponentCreation((w6, x6) => {
      ViewStackProcessor.StartGetAccessRecordingFor(w6);
      Row.create();
      Row.margin({
        left: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level1'],
          'bundleName': '',
          'moduleName': ''
        },
        right: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level5'],
          'bundleName': '',
          'moduleName': ''
        },
      });
      Row.justifyContent(FlexAlign.End);
      Row.focusable(true);
      if (!x6) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((u6, v6) => {
      ViewStackProcessor.StartGetAccessRecordingFor(u6);
      Stack.create();
      Stack.focusable(true);
      if (!v6) {
        Stack.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((x5, y5) => {
      ViewStackProcessor.StartGetAccessRecordingFor(x5);
      If.create();
      if (k5) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((f6, g6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(f6);
            Row.create();
            Row.padding({
              left: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level3'],
                'bundleName': '',
                'moduleName': ''
              },
              right: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level3'],
                'bundleName': '',
                'moduleName': ''
              },
            });
            Row.margin({
              bottom: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level2'],
                'bundleName': '',
                'moduleName': ''
              },
            });
            Row.backgroundColor(ObservedObject.GetRawObject(this.buttonBgColor));
            Row.focusable(true);
            Row.constraintSize({ minHeight: BUTTON_HEIGHT });
            Row.justifyContent(FlexAlign.End);
            Row.borderRadius({
              'id': -1,
              'type': 10002,
              params: ['sys.float.corner_radius_level4'],
              'bundleName': '',
              'moduleName': ''
            });
            Row.onFocus(() => {
              this.buttonFocus = true;
            });
            Row.onBlur(() => {
              this.buttonFocus = false;
            });
            Row.onHover((t6) => {
              if (t6) {
                this.buttonBgColor = {
                  'id': -1,
                  'type': 10001,
                  params: ['sys.color.interactive_hover'],
                  'bundleName': '',
                  'moduleName': ''
                };
              }
              else {
                this.buttonBgColor = {
                  'id': -1,
                  'type': 10001,
                  params: ['sys.color.ohos_id_color_sub_background_transparent'],
                  'bundleName': '',
                  'moduleName': ''
                };
              }
            });
            Row.onTouch((s6) => {
              if (s6.type === TouchType.Down) {
                this.buttonBgColor = {
                  'id': -1,
                  'type': 10001,
                  params: ['sys.color.interactive_pressed'],
                  'bundleName': '',
                  'moduleName': ''
                };
              }
              if (s6.type === TouchType.Up) {
                this.buttonBgColor = {
                  'id': -1,
                  'type': 10001,
                  params: ['sys.color.ohos_id_color_sub_background_transparent'],
                  'bundleName': '',
                  'moduleName': ''
                };
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
            if (!g6) {
              Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((d6, e6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(d6);
            Text.create(k5.value);
            __Text__secondaryTitleStyles({
              fontWeight: FontWeight.Medium,
              maxLines: SINGLE_LINE_NUM,
              fontColor: {
                'id': -1,
                'type': 10001,
                params: ['sys.color.font_emphasize'],
                'bundleName': '',
                'moduleName': ''
              },
            });
            Text.focusable(true);
            if (!e6) {
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
      if (!y5) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.observeComponentCreation((q5, r5) => {
      ViewStackProcessor.StartGetAccessRecordingFor(q5);
      If.create();
      if (this.buttonFocus) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((v5, w5) => {
            ViewStackProcessor.StartGetAccessRecordingFor(v5);
            Row.create();
            Row.height(BUTTON_HEIGHT);
            Row.width(this.buttonStyleWidth);
            Row.hitTestBehavior(HitTestMode.None);
            Row.border({
              width: BORDER_WIDTH,
              color: {
                'id': -1,
                'type': 10001,
                params: ['sys.color.interactive_focus'],
                'bundleName': '',
                'moduleName': ''
              }
            });
            Row.borderRadius({
              'id': -1,
              'type': 10002,
              params: ['sys.float.corner_radius_level4'],
              'bundleName': '',
              'moduleName': ''
            });
            if (!w5) {
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
      if (!r5) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    Stack.pop();
    Row.pop();
  }

  TextArrowStyle(y3, z3 = null) {
    this.observeComponentCreation((i5, j5) => {
      ViewStackProcessor.StartGetAccessRecordingFor(i5);
      Row.create();
      Row.focusable(true);
      Row.justifyContent(FlexAlign.End);
      Row.margin({
        left: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level4'],
          'bundleName': '',
          'moduleName': ''
        },
        right: this.contentMargin?.right ?? {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level4'],
          'bundleName': '',
          'moduleName': ''
        },
      });
      if (!j5) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((g5, h5) => {
      ViewStackProcessor.StartGetAccessRecordingFor(g5);
      Stack.create();
      if (!h5) {
        Stack.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((r4, s4) => {
      ViewStackProcessor.StartGetAccessRecordingFor(r4);
      Row.create();
      Row.alignItems(VerticalAlign.Center);
      Row.borderRadius({
        'id': -1,
        'type': 10002,
        params: ['sys.float.corner_radius_level4'],
        'bundleName': '',
        'moduleName': ''
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
        left: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level2'],
          'bundleName': '',
          'moduleName': ''
        },
        right: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level4'],
          'bundleName': '',
          'moduleName': ''
        },
      });
      Row.onHover((f5) => {
        if (f5) {
          this.textArrowBgColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.interactive_hover'],
            'bundleName': '',
            'moduleName': ''
          };
        }
        else {
          this.textArrowBgColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_sub_background_transparent'],
            'bundleName': '',
            'moduleName': ''
          };
        }
      });
      Row.onTouch((e5) => {
        if (e5.type === TouchType.Down) {
          this.textArrowBgColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.interactive_pressed'],
            'bundleName': '',
            'moduleName': ''
          };
        }
        if (e5.type === TouchType.Up) {
          this.textArrowBgColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_sub_background_transparent'],
            'bundleName': '',
            'moduleName': ''
          };
        }
      });
      Row.onKeyEvent((d5) => {
        if (d5.keyCode === KeyCode.KEYCODE_ENTER || d5.keyCode === KeyCode.KEYCODE_SPACE) {
          if (y3.action) {
            y3.action();
          }
        }
      });
      Row.onClick((c5) => {
        if (y3.action) {
          y3.action();
        }
      });
      Row.onAreaChange((a5, b5) => {
        this.textArrowStyleWidth = Number(b5.width);
        this.textArrowStyleHeight = Number(b5.height);
      });
      if (!s4) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((k4, l4) => {
      ViewStackProcessor.StartGetAccessRecordingFor(k4);
      If.create();
      if (y3) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((p4, q4) => {
            ViewStackProcessor.StartGetAccessRecordingFor(p4);
            Text.create(y3.value);
            __Text__secondaryTitleStyles({
              maxLines: SINGLE_LINE_NUM,
              fontWeight: FontWeight.Regular,
              alignment: Alignment.End,
            });
            Text.margin({
              right: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level2'],
                'bundleName': '',
                'moduleName': ''
              },
              top: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level4'],
                'bundleName': '',
                'moduleName': ''
              },
              bottom: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level4'],
                'bundleName': '',
                'moduleName': ''
              },
            });
            Text.focusable(true);
            Text.constraintSize({ maxWidth: this.getMaxArrowTextWidth() });
            if (!q4) {
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
      if (!l4) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.observeComponentCreation((i4, j4) => {
      ViewStackProcessor.StartGetAccessRecordingFor(i4);
      Image.create({
        'id': -1,
        'type': 20000,
        params: ['sys.media.ohos_ic_public_arrow_right'],
        'bundleName': '',
        'moduleName': ''
      });
      Image.fillColor({
        'id': -1,
        'type': 10001,
        params: ['sys.color.ohos_id_color_tertiary'],
        'bundleName': '',
        'moduleName': ''
      });
      Image.width(ARROW_ICON_WIDTH);
      Image.height(ARROW_ICON_HEIGHT);
      Image.focusable(true);
      Image.draggable(false);
      if (!j4) {
        Image.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Row.pop();
    this.observeComponentCreation((g4, h4) => {
      ViewStackProcessor.StartGetAccessRecordingFor(g4);
      Row.create();
      Row.height(this.textArrowStyleHeight);
      Row.width(this.textArrowStyleWidth);
      Row.hitTestBehavior(HitTestMode.None);
      Row.border({
        radius: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.corner_radius_level4'],
          'bundleName': '',
          'moduleName': ''
        },
        width: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.outline_extra_larger'],
          'bundleName': '',
          'moduleName': ''
        },
        color: {
          'id': -1,
          'type': 10001,
          params: ['sys.color.interactive_focus'],
          'bundleName': '',
          'moduleName': ''
        },
      });
      ViewStackProcessor.visualState('focused');
      Row.border({
        radius: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.corner_radius_level4'],
          'bundleName': '',
          'moduleName': ''
        },
        width: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.outline_extra_larger'],
          'bundleName': '',
          'moduleName': ''
        },
        color: {
          'id': -1,
          'type': 10001,
          params: ['sys.color.interactive_focus'],
          'bundleName': '',
          'moduleName': ''
        },
      });
      Row.backgroundColor({
        'id': -1,
        'type': 10001,
        params: ['sys.color.interactive_focus'],
        'bundleName': '',
        'moduleName': ''
      });
      ViewStackProcessor.visualState('pressed');
      Row.backgroundColor({
        'id': -1,
        'type': 10001,
        params: ['sys.color.interactive_pressed'],
        'bundleName': '',
        'moduleName': ''
      });
      ViewStackProcessor.visualState('disabled');
      Row.opacity({
        'id': -1,
        'type': 10002,
        params: ['sys.float.interactive_disable'],
        'bundleName': '',
        'moduleName': ''
      });
      ViewStackProcessor.visualState('normal');
      Row.border({
        radius: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.corner_radius_level4'],
          'bundleName': '',
          'moduleName': ''
        },
        width: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.border_none'],
          'bundleName': '',
          'moduleName': ''
        },
        color: {
          'id': -1,
          'type': 10001,
          params: ['sys.color.ohos_id_color_focused_outline_transparent'],
          'bundleName': '',
          'moduleName': ''
        },
      });
      ViewStackProcessor.visualState();
      if (!h4) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Row.pop();
    Stack.pop();
    Row.pop();
  }

  getMaxArrowTextWidth() {
    return this.textArrowStyleWidth - PADDING_LEVEL_2 * 2 - PADDING_LEVEL_4 -
      ARROW_ICON_WIDTH;
  }

  IconGroupStyle(j2, k2 = null) {
    this.observeComponentCreation((w3, x3) => {
      ViewStackProcessor.StartGetAccessRecordingFor(w3);
      Row.create();
      Row.justifyContent(FlexAlign.End);
      Row.focusable(true);
      Row.margin({
        left: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level2'],
          'bundleName': '',
          'moduleName': ''
        },
        right: this.contentMargin?.right ?? {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level6'],
          'bundleName': '',
          'moduleName': ''
        },
      });
      if (!x3) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((n2, o2) => {
      ViewStackProcessor.StartGetAccessRecordingFor(n2);
      ForEach.create();
      const p2 = (r2, s2) => {
        const t2 = r2;
        this.observeComponentCreation((v2, w2) => {
          ViewStackProcessor.StartGetAccessRecordingFor(v2);
          If.create();
          if (Util.isResourceType(t2.value)) {
            this.ifElseBranchUpdateFunction(0, () => {
              this.observeComponentCreation((a3, b3) => {
                ViewStackProcessor.StartGetAccessRecordingFor(a3);
                If.create();
                if (s2 === INDEX_ZERO) {
                  this.ifElseBranchUpdateFunction(0, () => {
                    {
                      this.observeComponentCreation((q3, r3) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(q3);
                        if (r3) {
                          let s3 = new SingleIconStyle(k2 ? k2 : this, {
                            item: {
                              iconOptions: {
                                icon: t2.value,
                                symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > s2 ?
                                this.operationSymbolOptions[s2] : null,
                              },
                              action: t2.action,
                            }
                          }, undefined, q3, () => {
                          }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 599, col: 13 });
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
                        ViewStackProcessor.StopGetAccessRecording();
                      });
                    }
                  });
                }
                else if (s2 === INDEX_ONE || s2 === INDEX_TWO) {
                  this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation((m3, n3) => {
                      ViewStackProcessor.StartGetAccessRecordingFor(m3);
                      __Common__.create();
                      __Common__.margin({
                        left: {
                          'id': -1,
                          'type': 10002,
                          params: ['sys.float.padding_level4'],
                          'bundleName': '',
                          'moduleName': ''
                        },
                      });
                      if (!n3) {
                        __Common__.pop();
                      }
                      ViewStackProcessor.StopGetAccessRecording();
                    });
                    {
                      this.observeComponentCreation((g3, h3) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(g3);
                        if (h3) {
                          let i3 = new SingleIconStyle(k2 ? k2 : this, {
                            item: {
                              action: t2.action,
                              iconOptions: {
                                icon: t2.value,
                                symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > s2 ?
                                this.operationSymbolOptions[s2] : null,
                              },
                            }
                          }, undefined, g3, () => {
                          }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 610, col: 13 });
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
                if (!b3) {
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
          if (!w2) {
            If.pop();
          }
          ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
      };
      this.forEachUpdateFunction(n2, j2, p2, undefined, true, false);
      if (!o2) {
        ForEach.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    ForEach.pop();
    Row.pop();
  }

  LoadingProcessStyle(b2 = null) {
    this.observeComponentCreation((h2, i2) => {
      ViewStackProcessor.StartGetAccessRecordingFor(h2);
      Row.create();
      Row.focusable(true);
      Row.justifyContent(FlexAlign.End);
      Row.padding({
        top: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level2'],
          'bundleName': '',
          'moduleName': ''
        },
        bottom: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level2'],
          'bundleName': '',
          'moduleName': ''
        },
      });
      Row.margin({
        left: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level4'],
          'bundleName': '',
          'moduleName': ''
        },
        right: this.contentMargin?.right ? this.contentMargin.right : {
          'id': -1,
          'type': 10002,
          params: ['sys.float.margin_right'],
          'bundleName': '',
          'moduleName': ''
        },
      });
      if (!i2) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((e2, f2) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e2);
      LoadingProgress.create();
      LoadingProgress.width(LOADING_SIZE);
      LoadingProgress.height(LOADING_SIZE);
      LoadingProgress.color({
        'id': -1,
        'type': 10001,
        params: ['sys.color.icon_secondary'],
        'bundleName': '',
        'moduleName': ''
      });
      LoadingProgress.focusable(true);
      LoadingProgress.onAppear(() => {
        this.isDuplicateLine = false;
      });
      if (!f2) {
        LoadingProgress.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Row.pop();
  }

  dummyFunction(w1 = null) {
    this.observeComponentCreation((y1, z1) => {
      ViewStackProcessor.StartGetAccessRecordingFor(y1);
      Row.create();
      Row.onAppear(() => {
        this.changeFlexAlign(FlexAlign.End);
      });
      if (!z1) {
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
    if (typeof t1 === 'function') {
      this.paramsGenerator_ = t1;
    }
    this.__bgColor = new ObservedPropertyObjectPU({
      'id': -1,
      'type': 10001,
      params: ['sys.color.ohos_id_color_sub_background_transparent'],
      'bundleName': '',
      'moduleName': ''
    }, this, 'bgColor');
    this.__isFocus = new ObservedPropertySimplePU(false, this, 'isFocus');
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
    this.observeComponentCreation((v, w) => {
      ViewStackProcessor.StartGetAccessRecordingFor(v);
      If.create();
      if (this.item && this.item.iconOptions) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((a1, b1) => {
            ViewStackProcessor.StartGetAccessRecordingFor(a1);
            Row.create();
            Row.focusable(true);
            Row.width(SINGLE_ICON_ZONE_SIZE);
            Row.height(SINGLE_ICON_ZONE_SIZE);
            Row.margin({
              bottom: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level2'],
                'bundleName': '',
                'moduleName': ''
              },
            });
            Row.justifyContent(FlexAlign.Center);
            Row.borderRadius({
              'id': -1,
              'type': 10002,
              params: ['sys.float.corner_radius_level4'],
              'bundleName': '',
              'moduleName': ''
            });
            Row.backgroundColor(ObservedObject.GetRawObject(this.bgColor));
            ViewStackProcessor.visualState('normal');
            Row.border({ width: 0 });
            Row.backgroundColor({
              'id': -1,
              'type': 10001,
              params: ['sys.color.ohos_id_color_sub_background_transparent'],
              'bundleName': '',
              'moduleName': ''
            });
            ViewStackProcessor.visualState('focused');
            Row.border({
              radius: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.corner_radius_level4'],
                'bundleName': '',
                'moduleName': ''
              },
              width: BORDER_WIDTH,
              color: {
                'id': -1,
                'type': 10001,
                params: ['sys.color.interactive_focus'],
                'bundleName': '',
                'moduleName': ''
              },
              style: BorderStyle.Solid,
            });
            Row.backgroundColor({
              'id': -1,
              'type': 10001,
              params: ['sys.color.interactive_focus'],
              'bundleName': '',
              'moduleName': ''
            });
            ViewStackProcessor.visualState('pressed');
            Row.backgroundColor({
              'id': -1,
              'type': 10001,
              params: ['sys.color.interactive_pressed'],
              'bundleName': '',
              'moduleName': ''
            });
            ViewStackProcessor.visualState('disabled');
            Row.opacity({
              'id': -1,
              'type': 10002,
              params: ['sys.float.interactive_disable'],
              'bundleName': '',
              'moduleName': ''
            });
            ViewStackProcessor.visualState();
            Row.onTouch((j1) => {
              if (j1.type === TouchType.Down) {
                this.bgColor = {
                  'id': -1,
                  'type': 10001,
                  params: ['sys.color.interactive_pressed'],
                  'bundleName': '',
                  'moduleName': ''
                };
              }
              if (j1.type === TouchType.Up) {
                this.bgColor = {
                  'id': -1,
                  'type': 10001,
                  params: ['sys.color.ohos_id_color_sub_background_transparent'],
                  'bundleName': '',
                  'moduleName': ''
                };
              }
            });
            Row.onHover((i1) => {
              if (i1) {
                this.bgColor = {
                  'id': -1,
                  'type': 10001,
                  params: ['sys.color.interactive_hover'],
                  'bundleName': '',
                  'moduleName': ''
                };
              }
              else {
                this.bgColor = {
                  'id': -1,
                  'type': 10001,
                  params: ['sys.color.ohos_id_color_sub_background_transparent'],
                  'bundleName': '',
                  'moduleName': ''
                };
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
            if (!b1) {
              Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.IconZone.bind(this)(this);
          Row.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!w) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
  }

  IconZone(d = null) {
    this.observeComponentCreation((f, g) => {
      ViewStackProcessor.StartGetAccessRecordingFor(f);
      If.create();
      if (this.item && this.item.iconOptions) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((k, l) => {
            ViewStackProcessor.StartGetAccessRecordingFor(k);
            If.create();
            if (Util.isSymbolResource(this.item.iconOptions.icon)) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation((s, t) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(s);
                  SymbolGlyph.create(this.item.iconOptions?.icon);
                  SymbolGlyph.focusable(true);
                  SymbolGlyph.fontSize(this.item.iconOptions?.symbolicIconOption?.fontSize ?? RIGHT_SINGLE_ICON_SIZE);
                  SymbolGlyph.fontColor(this.item.iconOptions?.symbolicIconOption?.fontColor ?? [{
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.icon_primary'],
                    'bundleName': '',
                    'moduleName': ''
                  }]);
                  SymbolGlyph.fontWeight(this.item.iconOptions?.symbolicIconOption?.fontWeight);
                  SymbolGlyph.renderingStrategy(this.item.iconOptions?.symbolicIconOption?.renderingStrategy);
                  SymbolGlyph.effectStrategy(this.item.iconOptions?.symbolicIconOption?.effectStrategy);
                  if (!t) {
                    SymbolGlyph.pop();
                  }
                  ViewStackProcessor.StopGetAccessRecording();
                });
              });
            }
            else {
              this.ifElseBranchUpdateFunction(1, () => {
                this.observeComponentCreation((o, p) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(o);
                  Image.create(this.item?.iconOptions?.icon);
                  Image.fillColor({
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.icon_primary'],
                    'bundleName': '',
                    'moduleName': ''
                  });
                  Image.width(RIGHT_SINGLE_ICON_SIZE);
                  Image.height(RIGHT_SINGLE_ICON_SIZE);
                  Image.focusable(true);
                  Image.draggable(false);
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
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!g) {
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