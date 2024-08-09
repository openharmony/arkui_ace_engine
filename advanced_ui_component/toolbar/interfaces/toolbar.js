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

let __decorate = (this && this.__decorate) || function (m4, n4, o4, p4) {
  let q4 = arguments.length;
  let r4 = q4 < 3 ? n4 : p4 === null ? p4 = Object.getOwnPropertyDescriptor(n4, o4) : p4;
  let s4;
  if (typeof Reflect === 'object' && typeof Reflect.decorate === 'function') {
    r4 = Reflect.decorate(m4, n4, o4, p4);
  } else {
    for (let t4 = m4.length - 1; t4 >= 0; t4--) {
      (s4 = m4[t4]) && (r4 = (q4 < 3 ? s4(r4) : q4 > 3 ? s4(n4, o4, r4) : s4(n4, o4)) || r4);
    }
  }
  return q4 > 3 && r4 && Object.defineProperty(n4, o4, r4), r4;
};
if (!('finalizeConstruction' in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => { });
}
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const LengthUnit = requireNapi('arkui.node').LengthUnit;
const DividerModifier = requireNapi('arkui.modifier').DividerModifier;
const hilog = requireNapi('hilog');

export let ItemState;
(function (j3) {
  j3[j3['ENABLE'] = 1] = 'ENABLE';
  j3[j3['DISABLE'] = 2] = 'DISABLE';
  j3[j3['ACTIVATE'] = 3] = 'ACTIVATE';
})(ItemState || (ItemState = {}));

const PUBLIC_MORE = { id: -1, type: 20000, params: ['sys.media.ohos_ic_public_more'], bundleName: '', moduleName: '' };
const IMAGE_SIZE = '24vp';
const DEFAULT_TOOLBAR_HEIGHT = 56;
const TOOLBAR_MAX_LENGTH = 5;
const MORE_TEXT_ID = 125833704;
const MIN_FONT_SIZE = 1.75;
const MAX_FONT_SIZE = 3.2;
const LONG_PRESS_TIME = 500;
const DIALOG_IMAGE_SIZE = '64vp';
const MAX_DIALOG = '256vp';
const MIN_DIALOG = '216vp';
const TEXT_TOOLBAR_DIALOG = '18.3fp';

let ToolBarOption = class ToolBarOption {
  constructor() {
    this.content = '';
    this.action = undefined;
    this.icon = undefined;
    this.state = 1;
    this.iconColor = {
      'id': -1,
      'type': 10001,
      params: ['sys.color.icon_primary'],
      'bundleName': '',
      'moduleName': '',
    };
    this.activatedIconColor = {
      'id': -1,
      'type': 10001,
      params: ['sys.color.icon_emphasize'],
      'bundleName': '',
      'moduleName': '',
    };
    this.textColor = {
      'id': -1,
      'type': 10001,
      params: ['sys.color.font_primary'],
      'bundleName': '',
      'moduleName': '',
    };
    this.activatedTextColor = {
      'id': -1,
      'type': 10001,
      params: ['sys.color.font_emphasize'],
      'bundleName': '',
      'moduleName': '',
    };
    this.toolBarSymbolOptions = undefined;
  }
};

ToolBarOption = __decorate([
  Observed
], ToolBarOption);
export { ToolBarOption };
let ToolBarOptions = class ToolBarOptions extends Array {
};
ToolBarOptions = __decorate([
  Observed
], ToolBarOptions);
export { ToolBarOptions };

export class ToolBarModifier {
  constructor() {
    this.backgroundColorValue = {
      'id': -1,
      'type': 10001,
      params: ['sys.color.ohos_id_color_toolbar_bg'],
      'bundleName': '',
      'moduleName': '',
    };
    this.heightValue = LengthMetrics.vp(DEFAULT_TOOLBAR_HEIGHT);
    this.stateEffectValue = true;
    this.paddingValue = LengthMetrics.resource({
      'id': -1,
      'type': 10002,
      params: ['sys.float.padding_level12'],
      'bundleName': '',
      'moduleName': '',
    });
  }
  applyNormalAttribute(j4) {
    j4.backgroundColor(this.backgroundColorValue);
  }
  backgroundColor(i4) {
    this.backgroundColorValue = i4;
    return this;
  }
  height(h4) {
    this.heightValue = h4;
    return this;
  }
  stateEffect(g4) {
    this.stateEffectValue = g4;
    return this;
  }
  padding(f4) {
    this.paddingValue = f4;
    return this;
  }
}

export class ToolBar extends ViewPU {
  constructor(w6, x6, y6, z6 = -1, a7 = undefined, b7) {
    super(w6, y6, z6, b7);
    if (typeof a7 === 'function') {
      this.paramsGenerator_ = a7;
    }
    this.__toolBarList = new SynchedPropertyNesedObjectPU(x6.toolBarList, this, 'toolBarList');
    this.controller = new TabsController();
    this.__activateIndex = new SynchedPropertySimpleOneWayPU(x6.activateIndex, this, 'activateIndex');
    this.__dividerModifier = new SynchedPropertyObjectOneWayPU(x6.dividerModifier, this, 'dividerModifier');
    this.__toolBarModifier = new SynchedPropertyObjectOneWayPU(x6.toolBarModifier, this, 'toolBarModifier');
    this.__moreText = new SynchedPropertyObjectOneWayPU(x6.moreText, this, 'moreText');
    this.__menuContent = new ObservedPropertyObjectPU([], this, 'menuContent');
    this.toolBarItemBackground = [];
    this.__itemBackground = new ObservedPropertyObjectPU(Color.Transparent, this, 'itemBackground');
    this.__iconPrimaryColor = new ObservedPropertyObjectPU({
      'id': -1,
      'type': 10001,
      params: ['sys.color.icon_primary'],
      'bundleName': '',
      'moduleName': '' },
      this, 'iconPrimaryColor');
    this.__iconActivePrimaryColor = new ObservedPropertyObjectPU({
      'id': -1,
      'type': 10001,
      params: ['sys.color.icon_emphasize'],
      'bundleName': '',
      'moduleName': '' },
      this, 'iconActivePrimaryColor');
    this.__fontPrimaryColor = new ObservedPropertyObjectPU({
      'id': -1,
      'type': 10001,
      params: ['sys.color.font_primary'],
      'bundleName': '',
      'moduleName': '' },
      this, 'fontPrimaryColor');
    this.__fontActivatedPrimaryColor = new ObservedPropertyObjectPU({
      'id': -1,
      'type': 10001,
      params: ['sys.color.font_emphasize'],
      'bundleName': '',
      'moduleName': '' },
      this, 'fontActivatedPrimaryColor');
    this.__symbolEffect = new ObservedPropertyObjectPU(new SymbolEffect(), this, 'symbolEffect');
    this.__fontSize = new ObservedPropertySimplePU(1, this, 'fontSize');
    this.__dialogController = new ObservedPropertyObjectPU(null, this, 'dialogController');
    this.setInitiallyProvidedValue(x6);
    this.finalizeConstruction();
  }

  setInitiallyProvidedValue(v6) {
    this.__toolBarList.set(v6.toolBarList);
    if (v6.controller !== undefined) {
      this.controller = v6.controller;
    }
    if (v6.activateIndex === undefined) {
      this.__activateIndex.set(-1);
    }
    if (v6.dividerModifier === undefined) {
      this.__dividerModifier.set(new DividerModifier());
    }
    if (v6.toolBarModifier === undefined) {
      this.__toolBarModifier.set(new ToolBarModifier()
        .padding(LengthMetrics.resource({
          'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '', 'moduleName': '' }))
        .stateEffect(true)
        .height(LengthMetrics.vp(DEFAULT_TOOLBAR_HEIGHT))
        .backgroundColor('sys.color.ohos_id_color_toolbar_bg'));
    }
    if (v6.moreText === undefined) {
      this.__moreText.set({
        'id': -1, 'type': 10003, params: ['sys.string.ohos_toolbar_more'],
        'bundleName': '', 'moduleName': '',
      });
    }
    if (v6.menuContent !== undefined) {
      this.menuContent = v6.menuContent;
    }
    if (v6.toolBarItemBackground !== undefined) {
      this.toolBarItemBackground = v6.toolBarItemBackground;
    }
    if (v6.itemBackground !== undefined) {
      this.itemBackground = v6.itemBackground;
    }
    if (v6.iconPrimaryColor !== undefined) {
      this.iconPrimaryColor = v6.iconPrimaryColor;
    }
    if (v6.iconActivePrimaryColor !== undefined) {
      this.iconActivePrimaryColor = v6.iconActivePrimaryColor;
    }
    if (v6.fontPrimaryColor !== undefined) {
      this.fontPrimaryColor = v6.fontPrimaryColor;
    }
    if (v6.fontActivatedPrimaryColor !== undefined) {
      this.fontActivatedPrimaryColor = v6.fontActivatedPrimaryColor;
    }
    if (v6.symbolEffect !== undefined) {
      this.symbolEffect = v6.symbolEffect;
    }
    if (v6.fontSize !== undefined) {
      this.fontSize = v6.fontSize;
    }
    if (v6.dialogController !== undefined) {
      this.dialogController = v6.dialogController;
    }
  }

  updateStateVars(u6) {
    this.__toolBarList.set(u6.toolBarList);
    this.__activateIndex.reset(u6.activateIndex);
    this.__dividerModifier.reset(u6.dividerModifier);
    this.__toolBarModifier.reset(u6.toolBarModifier);
    this.__moreText.reset(u6.moreText);
  }

  purgeVariableDependenciesOnElmtId(t6) {
    this.__toolBarList.purgeDependencyOnElmtId(t6);
    this.__activateIndex.purgeDependencyOnElmtId(t6);
    this.__dividerModifier.purgeDependencyOnElmtId(t6);
    this.__toolBarModifier.purgeDependencyOnElmtId(t6);
    this.__moreText.purgeDependencyOnElmtId(t6);
    this.__menuContent.purgeDependencyOnElmtId(t6);
    this.__itemBackground.purgeDependencyOnElmtId(t6);
    this.__iconPrimaryColor.purgeDependencyOnElmtId(t6);
    this.__iconActivePrimaryColor.purgeDependencyOnElmtId(t6);
    this.__fontPrimaryColor.purgeDependencyOnElmtId(t6);
    this.__fontActivatedPrimaryColor.purgeDependencyOnElmtId(t6);
    this.__symbolEffect.purgeDependencyOnElmtId(t6);
    this.__fontSize.purgeDependencyOnElmtId(t6);
    this.__dialogController.purgeDependencyOnElmtId(t6);
  }

  aboutToBeDeleted() {
    this.__toolBarList.aboutToBeDeleted();
    this.__activateIndex.aboutToBeDeleted();
    this.__dividerModifier.aboutToBeDeleted();
    this.__toolBarModifier.aboutToBeDeleted();
    this.__moreText.aboutToBeDeleted();
    this.__menuContent.aboutToBeDeleted();
    this.__itemBackground.aboutToBeDeleted();
    this.__iconPrimaryColor.aboutToBeDeleted();
    this.__iconActivePrimaryColor.aboutToBeDeleted();
    this.__fontPrimaryColor.aboutToBeDeleted();
    this.__fontActivatedPrimaryColor.aboutToBeDeleted();
    this.__symbolEffect.aboutToBeDeleted();
    this.__fontSize.aboutToBeDeleted();
    this.__dialogController.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }

  get toolBarList() {
    return this.__toolBarList.get();
  }

  get activateIndex() {
    return this.__activateIndex.get();
  }

  set activateIndex(s6) {
    this.__activateIndex.set(s6);
  }

  get dividerModifier() {
    return this.__dividerModifier.get();
  }

  set dividerModifier(r6) {
    this.__dividerModifier.set(r6);
  }

  get toolBarModifier() {
    return this.__toolBarModifier.get();
  }

  set toolBarModifier(q6) {
    this.__toolBarModifier.set(q6);
  }

  get moreText() {
    return this.__moreText.get();
  }

  set moreText(p6) {
    this.__moreText.set(p6);
  }

  get menuContent() {
    return this.__menuContent.get();
  }

  set menuContent(o6) {
    this.__menuContent.set(o6);
  }

  get itemBackground() {
    return this.__itemBackground.get();
  }

  set itemBackground(n6) {
    this.__itemBackground.set(n6);
  }

  get iconPrimaryColor() {
    return this.__iconPrimaryColor.get();
  }

  set iconPrimaryColor(m6) {
    this.__iconPrimaryColor.set(m6);
  }

  get iconActivePrimaryColor() {
    return this.__iconActivePrimaryColor.get();
  }

  set iconActivePrimaryColor(l6) {
    this.__iconActivePrimaryColor.set(l6);
  }

  get fontPrimaryColor() {
    return this.__fontPrimaryColor.get();
  }

  set fontPrimaryColor(k6) {
    this.__fontPrimaryColor.set(k6);
  }

  get fontActivatedPrimaryColor() {
    return this.__fontActivatedPrimaryColor.get();
  }

  set fontActivatedPrimaryColor(j6) {
    this.__fontActivatedPrimaryColor.set(j6);
  }

  get symbolEffect() {
    return this.__symbolEffect.get();
  }

  set symbolEffect(i6) {
    this.__symbolEffect.set(i6);
  }

  get fontSize() {
    return this.__fontSize.get();
  }

  set fontSize(h6) {
    this.__fontSize.set(h6);
  }

  get dialogController() {
    return this.__dialogController.get();
  }
  set dialogController(g6) {
    this.__dialogController.set(g6);
  }

  onWillApplyTheme(f6) {
    this.iconPrimaryColor = f6.colors.iconPrimary;
    this.iconActivePrimaryColor = f6.colors.iconEmphasize;
    this.fontPrimaryColor = f6.colors.fontPrimary;
    this.fontActivatedPrimaryColor = f6.colors.fontEmphasize;
  }

  MoreTabBuilder(j5, k5 = null) {
    this.observeComponentCreation2((s5, t5) => {
      Column.create();
      Column.width('100%');
      Column.height('100%');
      Column.justifyContent(FlexAlign.Center);
      Column.bindMenu(ObservedObject.GetRawObject(this.menuContent),
        { placement: Placement.TopRight, offset: { x: -12, y: -10 } });
      Column.padding({
        start: LengthMetrics.resource({
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level2'],
          'bundleName': '',
          'moduleName': '' }),
        end: LengthMetrics.resource({
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level2'],
          'bundleName': '',
          'moduleName': '' }),
      });
      Column.borderRadius({
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_corner_radius_clicked'],
        'bundleName': '',
        'moduleName': '',
      });
      Column.backgroundColor(ObservedObject.GetRawObject(this.itemBackground));
      Column.onHover((e6) => {
        if (e6) {
          this.toolBarItemBackground[j5] =
            {
              'id': -1,
              'type': 10001,
              params: ['sys.color.ohos_id_color_hover'],
              'bundleName': '',
              'moduleName': '',
            };
        }
        else {
          this.toolBarItemBackground[j5] = Color.Transparent;
        }
        this.itemBackground = this.toolBarItemBackground[j5];
      });
      ViewStackProcessor.visualState('pressed');
      Column.backgroundColor((!this.toolBarModifier.stateEffectValue) ?
      this.toolBarItemBackground[j5] : {
          'id': -1,
          'type': 10001,
          params: ['sys.color.ohos_id_color_click_effect'],
          'bundleName': '',
          'moduleName': '',
        });
      ViewStackProcessor.visualState('normal');
      Column.backgroundColor(this.toolBarItemBackground[j5]);
      ViewStackProcessor.visualState();
      Column.onTouch((d6) => {
        this.touchEventAction(d6, j5);
      });
      Gesture.create(GesturePriority.Low);
      LongPressGesture.create({ repeat: false, duration: LONG_PRESS_TIME });
      LongPressGesture.onAction((x5) => {
        this.fontSize = this.getFontSizeScale();
        if (x5) {
          if (this.fontSize >= MIN_FONT_SIZE) {
            this.dialogController = new CustomDialogController({
              builder: () => {
                let z5 = new ToolBarDialog(this, {
                  cancel: () => {
                  },
                  confirm: () => {
                  },
                  itemDialog: {
                    content: this.getStringSync(MORE_TEXT_ID),
                    icon: PUBLIC_MORE,
                  },
                  fontSize: this.fontSize,
                }, undefined, -1, () => { },
                  { page: 'library1/src/main/ets/components/mainpage/MainPage.ets', line: 182, col: 26 });
                z5.setController(this.dialogController);
                ViewPU.create(z5);
                let a6 = () => {
                  return {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    itemDialog: {
                      content: this.getStringSync(MORE_TEXT_ID),
                      icon: PUBLIC_MORE,
                    },
                    fontSize: this.fontSize
                  };
                };
                z5.paramsGenerator_ = a6;
              },
              maskColor: Color.Transparent,
              isModal: true,
              customStyle: true
            }, this);
            this.dialogController?.open();
          }
        }
      });
      LongPressGesture.pop();
      Gesture.pop();
    }, Column);
    this.observeComponentCreation2((q5, r5) => {
      Image.create(PUBLIC_MORE);
      Image.width(IMAGE_SIZE);
      Image.height(IMAGE_SIZE);
      Image.fillColor(ObservedObject.GetRawObject(this.iconPrimaryColor));
      Image.margin({ bottom: {
        'id': -1,
        'type': 10002,
        params: ['sys.float.padding_level1'],
        'bundleName': '',
        'moduleName': '',
      } });
      Image.objectFit(ImageFit.Contain);
      Image.draggable(false);
    }, Image);
    this.observeComponentCreation2((o5, p5) => {
      Text.create(this.moreText);
      Text.fontColor(ObservedObject.GetRawObject(this.fontPrimaryColor));
      Text.fontSize({
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_text_size_caption'],
        'bundleName': '',
        'moduleName': '',
      });
      Text.fontWeight(FontWeight.Medium);
      Text.maxLines(1);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.textAlign(TextAlign.Center);
    }, Text);
    Text.pop();
    Column.pop();
  }

  TabBuilder(f4, g4 = null) {
    this.observeComponentCreation2((w4, x4) => {
      Column.create();
      Column.justifyContent(FlexAlign.Center);
      Column.width('100%');
      Column.height('100%');
      Column.focusable(!(this.toolBarList[f4]?.state === ItemState.DISABLE));
      Column.focusOnTouch(!(this.toolBarList[f4]?.state === ItemState.DISABLE));
      Column.padding({
        start: LengthMetrics.resource({
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level2'],
          'bundleName': '',
          'moduleName': '' }),
        end: LengthMetrics.resource({
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level2'],
          'bundleName': '',
          'moduleName': '' }),
      });
      Column.borderRadius({
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_corner_radius_clicked'],
        'bundleName': '',
        'moduleName': '',
      });
      Column.backgroundColor(ObservedObject.GetRawObject(this.itemBackground));
      Column.onHover((i5) => {
        if (i5) {
          this.toolBarItemBackground[f4] = (this.toolBarList[f4]?.state === ItemState.DISABLE)
            ? Color.Transparent : { 'id': -1,
              'type': 10001,
              params: ['sys.color.ohos_id_color_hover'],
              'bundleName': '',
              'moduleName': '',
            };
        }
        else {
          this.toolBarItemBackground[f4] = Color.Transparent;
        }
        this.itemBackground = this.toolBarItemBackground[f4];
      });
      ViewStackProcessor.visualState('pressed');
      Column.backgroundColor((this.toolBarList[f4]?.state === ItemState.DISABLE) ||
        (!this.toolBarModifier.stateEffectValue) ?
      this.toolBarItemBackground[f4] : {
          'id': -1,
          'type': 10001,
          params: ['sys.color.ohos_id_color_click_effect'],
          'bundleName': '',
          'moduleName': '',
        });
      ViewStackProcessor.visualState('normal');
      Column.backgroundColor(this.toolBarItemBackground[f4]);
      ViewStackProcessor.visualState();
      Column.onTouch((h5) => {
        this.touchEventAction(h5, f4);
      });
      Gesture.create(GesturePriority.Low);
      LongPressGesture.create({ repeat: false, duration: LONG_PRESS_TIME });
      LongPressGesture.onAction((b5) => {
        this.fontSize = this.getFontSizeScale();
        if (b5 && (this.toolBarList[f4]?.icon || this.toolBarList[f4]?.toolBarSymbolOptions?.activated ||
          this.toolBarList[f4]?.toolBarSymbolOptions?.normal)) {
          if (this.fontSize >= MIN_FONT_SIZE) {
            this.dialogController = new CustomDialogController({
              builder: () => {
                let d5 = new ToolBarDialog(this, {
                  cancel: () => {
                  },
                  confirm: () => {
                  },
                  itemDialog: this.toolBarList[f4],
                  fontSize: this.fontSize,
                  itemSymbolModifier: this.getToolBarSymbolModifier(f4),
                }, undefined, -1, () => { },
                  { page: 'library1/src/main/ets/components/mainpage/MainPage.ets', line: 273, col: 26 });
                d5.setController(this.dialogController);
                ViewPU.create(d5);
                let e5 = () => {
                  return {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    itemDialog: this.toolBarList[f4],
                    fontSize: this.fontSize,
                    itemSymbolModifier: this.getToolBarSymbolModifier(f4)
                  };
                };
                d5.paramsGenerator_ = e5;
              },
              maskColor: Color.Transparent,
              isModal: true,
              customStyle: true
            }, this);
            this.dialogController?.open();
          }
        }
      });
      LongPressGesture.pop();
      Gesture.pop();
    }, Column);
    this.observeComponentCreation2((m4, n4) => {
      If.create();
      if (this.toolBarList[f4]?.toolBarSymbolOptions?.normal ||
        this.toolBarList[f4]?.toolBarSymbolOptions?.activated) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((u4, v4) => {
            SymbolGlyph.create();
            SymbolGlyph.fontSize(IMAGE_SIZE);
            SymbolGlyph.symbolEffect(ObservedObject.GetRawObject(this.symbolEffect), false);
            SymbolGlyph.attributeModifier.bind(this)(this.getToolBarSymbolModifier(f4));
            SymbolGlyph.opacity((this.toolBarList[f4]?.state === ItemState.DISABLE) ?
              { 'id': -1, 'type': 10002,
                params: ['sys.float.interactive_disable'],
                'bundleName': '', 'moduleName': '' } : 1);
            SymbolGlyph.margin({ bottom: {
              'id': -1,
              'type': 10002,
              params: ['sys.float.padding_level1'],
              'bundleName': '',
              'moduleName': '',
            } });
          }, SymbolGlyph);
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((q4, r4) => {
            Image.create(this.toolBarList[f4]?.icon);
            Image.width(IMAGE_SIZE);
            Image.height(IMAGE_SIZE);
            Image.fillColor(this.getIconColor(f4));
            Image.opacity((this.toolBarList[f4]?.state === ItemState.DISABLE) ?
              { 'id': -1, 'type': 10002,
                params: ['sys.float.interactive_disable'],
                'bundleName': '', 'moduleName': '' } : 1);
            Image.margin({ bottom: {
              'id': -1,
              'type': 10002,
              params: ['sys.float.padding_level1'],
              'bundleName': '',
              'moduleName': '',
            } });
            Image.objectFit(ImageFit.Contain);
            Image.draggable(false);
          }, Image);
        });
      }
    }, If);
    If.pop();
    this.observeComponentCreation2((k4, l4) => {
      Text.create(this.toolBarList[f4]?.content);
      Text.fontColor(this.getTextColor(f4));
      Text.fontSize({
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_text_size_caption'],
        'bundleName': '',
        'moduleName': '',
      });
      Text.maxFontSize({
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_text_size_caption'],
        'bundleName': '',
        'moduleName': '',
      });
      Text.minFontSize(9);
      Text.fontWeight(FontWeight.Medium);
      Text.maxLines(1);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.opacity((this.toolBarList[f4]?.state === ItemState.DISABLE) ?
        { 'id': -1, 'type': 10002,
          params: ['sys.float.interactive_disable'],
          'bundleName': '', 'moduleName': '' } : 1);
      Text.textAlign(TextAlign.Center);
    }, Text);
    Text.pop();
    Column.pop();
  }

  getStringSync(z3) {
    let a4 = '';
    if (!z3) {
      return a4;
    }
    let b4 = getContext()?.resourceManager;
    if (!b4) {
      return a4;
    }
    try {
      a4 = b4.getStringSync(z3);
    }
    catch (c4) {
      let d4 = c4?.code;
      let e4 = c4?.message;
      hilog.error(0x3900, 'Ace', `Faild to toolBar getStringSync, code: ${d4}, message: ${e4}`);
    }
    return a4;
  }

  getFontSizeScale() {
    let z3 = this.getUIContext();
    let a4 = z3.getHostContext()?.config?.fontSizeScale ?? 1;
    let b4 = 1;
    try {
      let f4 = z3.isFollowingSystemFontScale();
      let g4 = z3.getMaxFontScale();
      if (!f4) {
        b4 = 1;
      }
      else {
        b4 = Math.min(a4, g4);
      }
    }
    catch (c4) {
      b4 = a4;
      let d4 = c4?.code;
      let e4 = c4?.message;
      hilog.error(0x3900, 'Ace', `Faild to toolBar getFontSizeScale, code: ${d4}, message: ${e4}`);
    }
    return b4;
  }

  getToolBarSymbolModifier(y3) {
    if ((!this.toolBarList[y3]?.toolBarSymbolOptions?.activated) &&
      (!this.toolBarList[y3]?.toolBarSymbolOptions?.normal)) {
      return undefined;
    }
    if (this.activateIndex === y3 && (this.toolBarList[y3]?.state === ItemState.ACTIVATE)) {
      return this.toolBarList[y3]?.toolBarSymbolOptions?.activated;
    }
    return this.toolBarList[y3]?.toolBarSymbolOptions?.normal;
  }

  getIconColor(y1) {
    if (this.activateIndex === y1 && (this.toolBarList[y1]?.state === ItemState.ACTIVATE)) {
      return this.toolBarList[y1]?.activatedIconColor ?? this.iconActivePrimaryColor;
    }
    return this.toolBarList[y1]?.iconColor ?? this.iconPrimaryColor;
  }

  getTextColor(x1) {
    if (this.activateIndex === x1 && (this.toolBarList[x1]?.state === ItemState.ACTIVATE)) {
      return this.toolBarList[x1]?.activatedTextColor ?? this.fontActivatedPrimaryColor;
    }
    return this.toolBarList[x1]?.textColor ?? this.fontPrimaryColor;
  }

  toLengthString(t3) {
    if (t3 === void (0)) {
      return '';
    }
    const u3 = t3.value;
    let v3 = '';
    switch (t3.unit) {
      case LengthUnit.PX:
        v3 = `${u3}px`;
        break;
      case LengthUnit.FP:
        v3 = `${u3}fp`;
        break;
      case LengthUnit.LPX:
        v3 = `${u3}lpx`;
        break;
      case LengthUnit.PERCENT:
        v3 = `${u3 * 100}%`;
        break;
      case LengthUnit.VP:
        v3 = `${u3}vp`;
        break;
      default:
        v3 = `${u3}vp`;
        break;
    }
    return v3;
  }

  touchEventAction(q3, r3) {
    if (q3.type === TouchType.Up || q3.type === TouchType.Cancel) {
      if (this.fontSize >= MIN_FONT_SIZE) {
        this.dialogController?.close();
      }
      let s3 = this.toolBarList[r3];
      if (s3.state === ItemState.ACTIVATE) {
        if (this.activateIndex === r3) {
          this.activateIndex = -1;
        }
        else {
          this.activateIndex = r3;
        }
      }
      if (!(s3.state === ItemState.DISABLE)) {
        s3.action && s3.action();
      }
    }
  }

  refreshData() {
    this.menuContent = [];
    for (let q1 = 0; q1 < this.toolBarList.length; q1++) {
      if (q1 >= 4 && this.toolBarList.length > TOOLBAR_MAX_LENGTH) {
        this.menuContent[q1 - 4] = {
          value: this.toolBarList[q1].content,
          action: this.toolBarList[q1].action,
          enabled: this.toolBarList[q1].state !== ItemState.DISABLE,
        };
      }
      else {
        this.toolBarItemBackground[q1] = Color.Transparent;
        this.menuContent = [];
      }
    }
    return true;
  }

  aboutToAppear() {
    this.refreshData();
  }

  initialRender() {
    this.observeComponentCreation2((n3, o3) => {
      Column.create();
      Column.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.toolBarModifier));
    }, Column);
    this.observeComponentCreation2((l3, m3) => {
      Divider.create();
      Divider.width('100%');
      Divider.height(1);
      Divider.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.dividerModifier));
    }, Divider);
    this.observeComponentCreation2((j3, k3) => {
      Column.create();
      Column.justifyContent(FlexAlign.Center);
      Column.width('100%');
    }, Column);
    this.observeComponentCreation2((f3, g3) => {
      Tabs.create({ barPosition: BarPosition.End, controller: this.controller });
      Tabs.vertical(false);
      Tabs.constraintSize({
        minHeight: this.toLengthString(this.toolBarModifier.heightValue),
        maxHeight: this.toLengthString(this.toolBarModifier.heightValue),
      });
      Tabs.barHeight(this.toLengthString(this.toolBarModifier.heightValue));
      Tabs.barMode(BarMode.Fixed);
      Tabs.onChange((i3) => {
      });
      Tabs.width('100%');
      Tabs.height(this.toLengthString(this.toolBarModifier.heightValue));
      Tabs.padding({
        start: this.toolBarList.length < TOOLBAR_MAX_LENGTH ? this.toolBarModifier.paddingValue :
        LengthMetrics.resource({
          'id': -1, 'type': 10002,
          params: ['sys.float.padding_level0'],
          'bundleName': '',
          'moduleName': '' }),
        end: this.toolBarList.length < TOOLBAR_MAX_LENGTH ? this.toolBarModifier.paddingValue :
        LengthMetrics.resource({
          'id': -1, 'type': 10002,
          params: ['sys.float.padding_level0'],
          'bundleName': '',
          'moduleName': '' }),
      });
    }, Tabs);
    this.observeComponentCreation2((m2, n2) => {
      ForEach.create();
      const o2 = (q2, r2) => {
        const s2 = q2;
        this.observeComponentCreation2((u2, v2) => {
          If.create();
          if (this.toolBarList.length <= 5) {
            this.ifElseBranchUpdateFunction(0, () => {
              this.observeComponentCreation2((d3, e3) => {
                TabContent.create();
                TabContent.tabBar({ builder: () => {
                  this.TabBuilder.call(this, r2);
                } });
                TabContent.enabled(!(this.toolBarList[r2]?.state === ItemState.DISABLE));
                TabContent.focusOnTouch(!(this.toolBarList[r2]?.state === ItemState.DISABLE));
              }, TabContent);
              TabContent.pop();
            });
          }
          else if (r2 < 4) {
            this.ifElseBranchUpdateFunction(1, () => {
              this.observeComponentCreation2((z2, a3) => {
                TabContent.create();
                TabContent.tabBar({ builder: () => {
                  this.TabBuilder.call(this, r2);
                } });
                TabContent.enabled(!(this.toolBarList[r2]?.state === ItemState.DISABLE));
                TabContent.focusOnTouch(!(this.toolBarList[r2]?.state === ItemState.DISABLE));
              }, TabContent);
              TabContent.pop();
            });
          }
          else {
            this.ifElseBranchUpdateFunction(2, () => {
            });
          }
        }, If);
        If.pop();
      };
      this.forEachUpdateFunction(m2, this.toolBarList, o2, undefined, true, false);
    }, ForEach);
    ForEach.pop();
    this.observeComponentCreation2((f2, g2) => {
      If.create();
      if (this.refreshData() && this.toolBarList.length > TOOLBAR_MAX_LENGTH) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((k2, l2) => {
            TabContent.create();
            TabContent.tabBar({ builder: () => {
              this.MoreTabBuilder.call(this, 4);
            } });
          }, TabContent);
          TabContent.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
    }, If);
    If.pop();
    Tabs.pop();
    Column.pop();
    Column.pop();
  }

  rerender() {
    this.updateDirtyElements();
  }
}

class ToolBarDialog extends ViewPU {
  constructor(r1, s1, t1, u1 = -1, v1 = undefined, w1) {
    super(r1, t1, u1, w1);
    if (typeof v1 === 'function') {
      this.paramsGenerator_ = v1;
    }
    this.itemDialog = {
      icon: undefined,
      content: '',
    };
    this.itemSymbolModifier = undefined;
    this.mainWindowStage = undefined;
    this.controller = undefined;
    this.screenWidth = 640;
    this.verticalScreenLines = 6;
    this.horizontalsScreenLines = 1;
    this.cancel = () => {
    };
    this.confirm = () => {
    };
    this.__mainWindow = this.createStorageLink('mainWindow', undefined, 'mainWindow');
    this.__fontSize = new SynchedPropertySimpleOneWayPU(s1.fontSize, this, 'fontSize');
    this.__maxLines = new ObservedPropertySimplePU(1, this, 'maxLines');
    this.__windowStandardHeight = this.createStorageProp('windowStandardHeight', 0, 'windowStandardHeight');
    this.__symbolEffect = new ObservedPropertyObjectPU(new SymbolEffect(), this, 'symbolEffect');
    this.setInitiallyProvidedValue(s1);
    this.finalizeConstruction();
  }

  setInitiallyProvidedValue(q1) {
    if (q1.itemDialog !== undefined) {
      this.itemDialog = q1.itemDialog;
    }
    if (q1.itemSymbolModifier !== undefined) {
      this.itemSymbolModifier = q1.itemSymbolModifier;
    }
    if (q1.mainWindowStage !== undefined) {
      this.mainWindowStage = q1.mainWindowStage;
    }
    if (q1.controller !== undefined) {
      this.controller = q1.controller;
    }
    if (q1.screenWidth !== undefined) {
      this.screenWidth = q1.screenWidth;
    }
    if (q1.verticalScreenLines !== undefined) {
      this.verticalScreenLines = q1.verticalScreenLines;
    }
    if (q1.horizontalsScreenLines !== undefined) {
      this.horizontalsScreenLines = q1.horizontalsScreenLines;
    }
    if (q1.cancel !== undefined) {
      this.cancel = q1.cancel;
    }
    if (q1.confirm !== undefined) {
      this.confirm = q1.confirm;
    }
    if (q1.fontSize === undefined) {
      this.__fontSize.set(1);
    }
    if (q1.maxLines !== undefined) {
      this.maxLines = q1.maxLines;
    }
    if (q1.symbolEffect !== undefined) {
      this.symbolEffect = q1.symbolEffect;
    }
  }

  updateStateVars(p1) {
    this.__fontSize.reset(p1.fontSize);
  }

  purgeVariableDependenciesOnElmtId(o1) {
    this.__mainWindow.purgeDependencyOnElmtId(o1);
    this.__fontSize.purgeDependencyOnElmtId(o1);
    this.__maxLines.purgeDependencyOnElmtId(o1);
    this.__windowStandardHeight.purgeDependencyOnElmtId(o1);
    this.__symbolEffect.purgeDependencyOnElmtId(o1);
  }

  aboutToBeDeleted() {
    this.__mainWindow.aboutToBeDeleted();
    this.__fontSize.aboutToBeDeleted();
    this.__maxLines.aboutToBeDeleted();
    this.__windowStandardHeight.aboutToBeDeleted();
    this.__symbolEffect.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }

  setController(n1) {
    this.controller = n1;
  }

  get mainWindow() {
    return this.__mainWindow.get();
  }
  set mainWindow(m1) {
    this.__mainWindow.set(m1);
  }

  get fontSize() {
    return this.__fontSize.get();
  }
  set fontSize(l1) {
    this.__fontSize.set(l1);
  }

  get maxLines() {
    return this.__maxLines.get();
  }
  set maxLines(k1) {
    this.__maxLines.set(k1);
  }

  get windowStandardHeight() {
    return this.__windowStandardHeight.get();
  }
  set windowStandardHeight(j1) {
    this.__windowStandardHeight.set(j1);
  }

  get symbolEffect() {
    return this.__symbolEffect.get();
  }
  set symbolEffect(i1) {
    this.__symbolEffect.set(i1);
  }

  initialRender() {
    this.observeComponentCreation2((e, f) => {
      If.create();
      if (this.itemDialog.content) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((g1, h1) => {
            Column.create();
            Column.width(this.fontSize === MAX_FONT_SIZE ? MAX_DIALOG : MIN_DIALOG);
            Column.constraintSize({ minHeight: this.fontSize === MAX_FONT_SIZE ? MAX_DIALOG : MIN_DIALOG });
            Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
            Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
            Column.borderRadius(({
              'id': -1,
              'type': 10002,
              params: ['sys.float.corner_radius_level10'],
              'bundleName': '',
              'moduleName': '',
            }));
          }, Column);
          this.observeComponentCreation2((w, x) => {
            If.create();
            if (this.itemDialog.toolBarSymbolOptions?.normal ||
              this.itemDialog.toolBarSymbolOptions?.activated) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation2((e1, f1) => {
                  SymbolGlyph.create();
                  SymbolGlyph.attributeModifier.bind(this)(this.itemSymbolModifier);
                  SymbolGlyph.symbolEffect(ObservedObject.GetRawObject(this.symbolEffect), false);
                  SymbolGlyph.fontColor([{
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.icon_primary'],
                    'bundleName': '',
                    'moduleName': '',
                  }]);
                  SymbolGlyph.fontSize(DIALOG_IMAGE_SIZE);
                  SymbolGlyph.margin({
                    top: {
                      'id': -1,
                      'type': 10002,
                      params: ['sys.float.padding_level24'],
                      'bundleName': '',
                      'moduleName': '',
                    },
                    bottom: {
                      'id': -1,
                      'type': 10002,
                      params: ['sys.float.padding_level8'],
                      'bundleName': '',
                      'moduleName': '',
                    },
                  });
                }, SymbolGlyph);
              });
            }
            else {
              this.ifElseBranchUpdateFunction(1, () => {
                this.observeComponentCreation2((a1, b1) => {
                  Image.create(this.itemDialog.icon);
                  Image.width(DIALOG_IMAGE_SIZE);
                  Image.height(DIALOG_IMAGE_SIZE);
                  Image.margin({
                    top: {
                      'id': -1,
                      'type': 10002,
                      params: ['sys.float.padding_level24'],
                      'bundleName': '',
                      'moduleName': '',
                    },
                    bottom: {
                      'id': -1,
                      'type': 10002,
                      params: ['sys.float.padding_level8'],
                      'bundleName': '',
                      'moduleName': '',
                    },
                  });
                  Image.fillColor({
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.icon_primary'],
                    'bundleName': '',
                    'moduleName': '',
                  });
                }, Image);
              });
            }
          }, If);
          If.pop();
          this.observeComponentCreation2((u, v) => {
            Column.create();
            Column.width('100%');
            Column.padding({
              left: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level4'],
                'bundleName': '',
                'moduleName': '',
              },
              right: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level4'],
                'bundleName': '',
                'moduleName': '',
              },
              bottom: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level12'],
                'bundleName': '',
                'moduleName': '',
              },
            });
          }, Column);
          this.observeComponentCreation2((s, t) => {
            Text.create(this.itemDialog.content);
            Text.fontSize(TEXT_TOOLBAR_DIALOG);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.maxLines(this.maxLines);
            Text.width('100%');
            Text.textAlign(TextAlign.Center);
            Text.fontColor({
              'id': -1,
              'type': 10001,
              params: ['sys.color.font_primary'],
              'bundleName': '',
              'moduleName': '',
            });
          }, Text);
          Text.pop();
          Column.pop();
          Column.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((l, m) => {
            Column.create();
            Column.width(this.fontSize === MAX_FONT_SIZE ? MAX_DIALOG : MIN_DIALOG);
            Column.constraintSize({ minHeight: this.fontSize === MAX_FONT_SIZE ? MAX_DIALOG : MIN_DIALOG });
            Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
            Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
            Column.borderRadius(({
              'id': -1,
              'type': 10002,
              params: ['sys.float.corner_radius_level10'],
              'bundleName': '',
              'moduleName': '',
            }));
            Column.justifyContent(FlexAlign.Center);
          }, Column);
          this.observeComponentCreation2((j, k) => {
            Image.create(this.itemDialog.icon);
            Image.width(DIALOG_IMAGE_SIZE);
            Image.height(DIALOG_IMAGE_SIZE);
            Image.fillColor({
              'id': -1,
              'type': 10001,
              params: ['sys.color.icon_primary'],
              'bundleName': '',
              'moduleName': '',
            });
          }, Image);
          Column.pop();
        });
      }
    }, If);
    If.pop();
  }

  async aboutToAppear() {
    let a = this.getUIContext().getHostContext();
    this.mainWindowStage = a.windowStage.getMainWindowSync();
    let b = this.mainWindowStage.getWindowProperties();
    let c = b.windowRect;
    if (px2vp(c.height) > this.screenWidth) {
      this.maxLines = this.verticalScreenLines;
    }
    else {
      this.maxLines = this.horizontalsScreenLines;
    }
  }

  rerender() {
    this.updateDirtyElements();
  }
}

export default { ToolBarOptions, ToolBar, ItemState, ToolBarOption, ToolBarModifier };