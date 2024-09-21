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
const ColorMetrics = requireNapi('arkui.node').ColorMetrics;
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
const MAX_FONT_SIZE = 3.2;
const DIALOG_IMAGE_SIZE = '64vp';
const MAX_DIALOG = '256vp';
const MIN_DIALOG = '216vp';
const TEXT_TOOLBAR_DIALOG = '18.3fp';
const FOCUS_BOX_MARGIN = -2;
const FOCUS_BOX_BORDER_WIDTH = 2;

class ButtonGestureModifier {
  constructor(m7) {
    this.fontSize = 1;
    this.controller = null;
    this.controller = m7;
  }
  applyGesture(j7) {
    if (this.fontSize >= ButtonGestureModifier.minFontSize) {
      j7.addGesture(new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime })
        .onAction(() => {
          if (j7) {
            this.controller?.open();
          }
        })
        .onActionEnd(() => {
          this.controller?.close();
        }));
    }
    else {
      j7.clearGestures();
    }
  }
}
ButtonGestureModifier.longPressTime = 500;
ButtonGestureModifier.minFontSize = 1.75;

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
  constructor(y6, z6, a7, b7 = -1, c7 = undefined, d7) {
    super(y6, a7, b7, d7);
    if (typeof c7 === 'function') {
      this.paramsGenerator_ = c7;
    }
    this.__toolBarList = new SynchedPropertyNesedObjectPU(z6.toolBarList, this, 'toolBarList');
    this.controller = new TabsController();
    this.__activateIndex = new SynchedPropertySimpleOneWayPU(z6.activateIndex, this, 'activateIndex');
    this.__dividerModifier = new SynchedPropertyObjectOneWayPU(z6.dividerModifier, this, 'dividerModifier');
    this.__toolBarModifier = new SynchedPropertyObjectOneWayPU(z6.toolBarModifier, this, 'toolBarModifier');
    this.__moreText = new SynchedPropertyObjectOneWayPU(z6.moreText, this, 'moreText');
    this.__menuContent = new ObservedPropertyObjectPU([], this, 'menuContent');
    this.__toolBarItemBackground = new ObservedPropertyObjectPU([], this, 'toolBarItemBackground');
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
    this.isFollowSystem = false;
    this.maxFontSizeScale = 3.2;
    this.moreIndex = 4;
    this.moreItem = {
      content: {
        'id': -1,
        'type': 10003,
        params: ['sys.string.ohos_toolbar_more'],
        'bundleName': '',
        'moduleName': '' },
      icon: PUBLIC_MORE,
    };
    this.setInitiallyProvidedValue(z6);
    this.finalizeConstruction();
  }

  setInitiallyProvidedValue(x6) {
    this.__toolBarList.set(x6.toolBarList);
    if (x6.controller !== undefined) {
      this.controller = x6.controller;
    }
    if (x6.activateIndex === undefined) {
      this.__activateIndex.set(-1);
    }
    if (x6.dividerModifier === undefined) {
      this.__dividerModifier.set(new DividerModifier());
    }
    if (x6.toolBarModifier === undefined) {
      this.__toolBarModifier.set(new ToolBarModifier()
        .padding(LengthMetrics.resource({
          'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '', 'moduleName': '' }))
        .stateEffect(true)
        .height(LengthMetrics.vp(DEFAULT_TOOLBAR_HEIGHT))
        .backgroundColor('sys.color.ohos_id_color_toolbar_bg'));
    }
    if (x6.moreText === undefined) {
      this.__moreText.set({
        'id': -1, 'type': 10003, params: ['sys.string.ohos_toolbar_more'],
        'bundleName': '', 'moduleName': '',
      });
    }
    if (x6.menuContent !== undefined) {
      this.menuContent = x6.menuContent;
    }
    if (x6.toolBarItemBackground !== undefined) {
      this.toolBarItemBackground = x6.toolBarItemBackground;
    }
    if (x6.iconPrimaryColor !== undefined) {
      this.iconPrimaryColor = x6.iconPrimaryColor;
    }
    if (x6.iconActivePrimaryColor !== undefined) {
      this.iconActivePrimaryColor = x6.iconActivePrimaryColor;
    }
    if (x6.fontPrimaryColor !== undefined) {
      this.fontPrimaryColor = x6.fontPrimaryColor;
    }
    if (x6.fontActivatedPrimaryColor !== undefined) {
      this.fontActivatedPrimaryColor = x6.fontActivatedPrimaryColor;
    }
    if (x6.symbolEffect !== undefined) {
      this.symbolEffect = x6.symbolEffect;
    }
    if (x6.fontSize !== undefined) {
      this.fontSize = x6.fontSize;
    }
    if (x6.isFollowSystem !== undefined) {
      this.isFollowSystem = x6.isFollowSystem;
    }
    if (x6.maxFontSizeScale !== undefined) {
      this.maxFontSizeScale = x6.maxFontSizeScale;
    }
    if (x6.moreIndex !== undefined) {
      this.moreIndex = x6.moreIndex;
    }
    if (x6.moreItem !== undefined) {
      this.moreItem = x6.moreItem;
    }
  }

  updateStateVars(w6) {
    this.__toolBarList.set(w6.toolBarList);
    this.__activateIndex.reset(w6.activateIndex);
    this.__dividerModifier.reset(w6.dividerModifier);
    this.__toolBarModifier.reset(w6.toolBarModifier);
    this.__moreText.reset(w6.moreText);
  }

  purgeVariableDependenciesOnElmtId(v6) {
    this.__toolBarList.purgeDependencyOnElmtId(v6);
    this.__activateIndex.purgeDependencyOnElmtId(v6);
    this.__dividerModifier.purgeDependencyOnElmtId(v6);
    this.__toolBarModifier.purgeDependencyOnElmtId(v6);
    this.__moreText.purgeDependencyOnElmtId(v6);
    this.__menuContent.purgeDependencyOnElmtId(v6);
    this.__toolBarItemBackground.purgeDependencyOnElmtId(v6);
    this.__iconPrimaryColor.purgeDependencyOnElmtId(v6);
    this.__iconActivePrimaryColor.purgeDependencyOnElmtId(v6);
    this.__fontPrimaryColor.purgeDependencyOnElmtId(v6);
    this.__fontActivatedPrimaryColor.purgeDependencyOnElmtId(v6);
    this.__symbolEffect.purgeDependencyOnElmtId(v6);
    this.__fontSize.purgeDependencyOnElmtId(v6);
  }

  aboutToBeDeleted() {
    this.__toolBarList.aboutToBeDeleted();
    this.__activateIndex.aboutToBeDeleted();
    this.__dividerModifier.aboutToBeDeleted();
    this.__toolBarModifier.aboutToBeDeleted();
    this.__moreText.aboutToBeDeleted();
    this.__menuContent.aboutToBeDeleted();
    this.__toolBarItemBackground.aboutToBeDeleted();
    this.__iconPrimaryColor.aboutToBeDeleted();
    this.__iconActivePrimaryColor.aboutToBeDeleted();
    this.__fontPrimaryColor.aboutToBeDeleted();
    this.__fontActivatedPrimaryColor.aboutToBeDeleted();
    this.__symbolEffect.aboutToBeDeleted();
    this.__fontSize.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }

  get toolBarList() {
    return this.__toolBarList.get();
  }

  get activateIndex() {
    return this.__activateIndex.get();
  }
  set activateIndex(u6) {
    this.__activateIndex.set(u6);
  }

  get dividerModifier() {
    return this.__dividerModifier.get();
  }
  set dividerModifier(t6) {
    this.__dividerModifier.set(t6);
  }

  get toolBarModifier() {
    return this.__toolBarModifier.get();
  }
  set toolBarModifier(s6) {
    this.__toolBarModifier.set(s6);
  }

  get moreText() {
    return this.__moreText.get();
  }
  set moreText(r6) {
    this.__moreText.set(r6);
  }

  get menuContent() {
    return this.__menuContent.get();
  }
  set menuContent(q6) {
    this.__menuContent.set(q6);
  }

  get toolBarItemBackground() {
    return this.__toolBarItemBackground.get();
  }

  set toolBarItemBackground(p6) {
    this.__toolBarItemBackground.set(p6);
  }

  get iconPrimaryColor() {
    return this.__iconPrimaryColor.get();
  }

  set iconPrimaryColor(o6) {
    this.__iconPrimaryColor.set(o6);
  }

  get iconActivePrimaryColor() {
    return this.__iconActivePrimaryColor.get();
  }
  set iconActivePrimaryColor(n6) {
    this.__iconActivePrimaryColor.set(n6);
  }

  get fontPrimaryColor() {
    return this.__fontPrimaryColor.get();
  }
  set fontPrimaryColor(m6) {
    this.__fontPrimaryColor.set(m6);
  }

  get fontActivatedPrimaryColor() {
    return this.__fontActivatedPrimaryColor.get();
  }
  set fontActivatedPrimaryColor(l6) {
    this.__fontActivatedPrimaryColor.set(l6);
  }

  get symbolEffect() {
    return this.__symbolEffect.get();
  }
  set symbolEffect(k6) {
    this.__symbolEffect.set(k6);
  }

  get fontSize() {
    return this.__fontSize.get();
  }

  set fontSize(j6) {
    this.__fontSize.set(j6);
  }

  onWillApplyTheme(i6) {
    this.iconPrimaryColor = i6.colors.iconPrimary;
    this.iconActivePrimaryColor = i6.colors.iconEmphasize;
    this.fontPrimaryColor = i6.colors.fontPrimary;
    this.fontActivatedPrimaryColor = i6.colors.fontEmphasize;
  }

  MoreTabBuilder(s5, t5 = null) {
    this.observeComponentCreation2((e6, f6) => {
      Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
      Button.focusable(true);
      Button.focusOnTouch(true);
      Button.focusBox({
        margin: LengthMetrics.vp(FOCUS_BOX_MARGIN),
        strokeWidth: LengthMetrics.vp(FOCUS_BOX_BORDER_WIDTH),
        strokeColor: ColorMetrics.resourceColor({
          'id': -1,
          'type': 10001,
          params: ['sys.color.ohos_id_color_focused_outline'],
          'bundleName': '',
          'moduleName': '',
        })
      });
      Button.width('100%');
      Button.height('100%');
      Button.bindMenu(ObservedObject.GetRawObject(this.menuContent),
        { placement: Placement.TopRight, offset: { x: -12, y: -10 } });
      Button.borderRadius({
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_corner_radius_clicked'],
        'bundleName': '',
        'moduleName': '',
      });
      Button.backgroundColor(this.toolBarItemBackground[s5]);
      Button.onHover((h6) => {
        if (h6) {
          this.toolBarItemBackground[s5] = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_hover'],
            'bundleName': '',
            'moduleName': '',
          };
        }
        else {
          this.toolBarItemBackground[s5] = Color.Transparent;
        }
      });
      ViewStackProcessor.visualState('pressed');
      Button.backgroundColor((!this.toolBarModifier.stateEffectValue) ?
      this.toolBarItemBackground[s5] : {
          'id': -1,
          'type': 10001,
          params: ['sys.color.ohos_id_color_click_effect'],
          'bundleName': '',
          'moduleName': '',
        });
      ViewStackProcessor.visualState();
      Button.gestureModifier(this.getItemGestureModifier(this.moreItem, s5));
    }, Button);
    this.observeComponentCreation2((c6, d6) => {
      Column.create();
      Column.width('100%');
      Column.height('100%');
      Column.justifyContent(FlexAlign.Center);
      Column.padding({
        start: LengthMetrics.resource({
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level2'],
          'bundleName': '',
          'moduleName': '',
        }),
        end: LengthMetrics.resource({
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level2'],
          'bundleName': '',
          'moduleName': '',
        }),
      });
      Column.borderRadius({
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_corner_radius_clicked'],
        'bundleName': '',
        'moduleName': '',
      });
    }, Column);
    this.observeComponentCreation2((a6, b6) => {
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
    this.observeComponentCreation2((y5, z5) => {
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
      Text.focusable(true);
      Text.focusOnTouch(true);
    }, Text);
    Text.pop();
    Column.pop();
    Button.pop();
  }

  TabBuilder(t4, u4 = null) {
    this.observeComponentCreation2((n5, o5) => {
      Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
      Button.enabled(this.toolBarList[t4]?.state !== ItemState.DISABLE);
      Button.width('100%');
      Button.height('100%');
      Button.borderRadius({
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_corner_radius_clicked'],
        'bundleName': '',
        'moduleName': '',
      });
      Button.focusable(!(this.toolBarList[t4]?.state === ItemState.DISABLE));
      Button.focusOnTouch(!(this.toolBarList[t4]?.state === ItemState.DISABLE));
      Button.focusBox({
        margin: LengthMetrics.vp(FOCUS_BOX_MARGIN),
        strokeWidth: LengthMetrics.vp(FOCUS_BOX_BORDER_WIDTH),
        strokeColor: ColorMetrics.resourceColor({
          'id': -1,
          'type': 10001,
          params: ['sys.color.ohos_id_color_focused_outline'],
          'bundleName': '',
          'moduleName': '',
        })
      });
      Button.backgroundColor(this.toolBarItemBackground[t4]);
      Button.onHover((r5) => {
        if (r5 && this.toolBarList[t4]?.state !== ItemState.DISABLE) {
          this.toolBarItemBackground[t4] = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_hover'],
            'bundleName': '',
            'moduleName': '',
          };
        }
        else {
          this.toolBarItemBackground[t4] = Color.Transparent;
        }
      });
      ViewStackProcessor.visualState('pressed');
      Button.backgroundColor((this.toolBarList[t4]?.state === ItemState.DISABLE) ||
        (!this.toolBarModifier.stateEffectValue) ?
      this.toolBarItemBackground[t4] : {
          'id': -1,
          'type': 10001,
          params: ['sys.color.ohos_id_color_click_effect'],
          'bundleName': '',
          'moduleName': '',
        });
      ViewStackProcessor.visualState();
      Button.onClick(() => {
        this.clickEventAction(t4);
      });
      Button.gestureModifier(this.getItemGestureModifier(this.toolBarList[t4], t4));
    }, Button);
    this.observeComponentCreation2((l5, m5) => {
      Column.create();
      Column.justifyContent(FlexAlign.Center);
      Column.width('100%');
      Column.height('100%');
      Column.borderRadius({
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_corner_radius_clicked'],
        'bundleName': '',
        'moduleName': '',
      });
      Column.padding({
        start: LengthMetrics.resource({
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level2'],
          'bundleName': '',
          'moduleName': '',
        }),
        end: LengthMetrics.resource({
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level2'],
          'bundleName': '',
          'moduleName': '',
        }),
      });
    }, Column);
    this.observeComponentCreation2((b5, c5) => {
      If.create();
      if (this.toolBarList[t4]?.toolBarSymbolOptions?.normal ||
        this.toolBarList[t4]?.toolBarSymbolOptions?.activated) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((j5, k5) => {
            SymbolGlyph.create();
            SymbolGlyph.fontSize(IMAGE_SIZE);
            SymbolGlyph.symbolEffect(ObservedObject.GetRawObject(this.symbolEffect), false);
            SymbolGlyph.attributeModifier.bind(this)(this.getToolBarSymbolModifier(t4));
            SymbolGlyph.margin({ bottom: {
              'id': -1,
              'type': 10002,
              params: ['sys.float.padding_level1'],
              'bundleName': '',
              'moduleName': '' } });
          }, SymbolGlyph);
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((f5, g5) => {
            Image.create(this.toolBarList[t4]?.icon);
            Image.width(IMAGE_SIZE);
            Image.height(IMAGE_SIZE);
            Image.fillColor(this.getIconColor(t4));
            Image.margin({ bottom: {
              'id': -1,
              'type': 10002,
              params: ['sys.float.padding_level1'],
              'bundleName': '',
              'moduleName': '' } });
            Image.objectFit(ImageFit.Contain);
            Image.draggable(false);
          }, Image);
        });
      }
    }, If);
    If.pop();
    this.observeComponentCreation2((z4, a5) => {
      Text.create(this.toolBarList[t4]?.content);
      Text.fontColor(this.getTextColor(t4));
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
      Text.textAlign(TextAlign.Center);
      Text.focusable(!(this.toolBarList[t4]?.state === ItemState.DISABLE));
      Text.focusOnTouch(!(this.toolBarList[t4]?.state === ItemState.DISABLE));
    }, Text);
    Text.pop();
    Column.pop();
    Button.pop();
  }

  getFontSizeScale() {
    let r4 = this.getUIContext();
    let s4 = r4.getHostContext()?.config?.fontSizeScale ?? 1;
    if (!this.isFollowSystem) {
      return 1;
    }
    else {
      return Math.min(s4, this.maxFontSizeScale);
    }
  }

  getToolBarSymbolModifier(q4) {
    if ((!this.toolBarList[q4]?.toolBarSymbolOptions?.activated) &&
      (!this.toolBarList[q4]?.toolBarSymbolOptions?.normal)) {
      return undefined;
    }
    if (this.activateIndex === q4 && (this.toolBarList[q4]?.state === ItemState.ACTIVATE)) {
      return this.toolBarList[q4]?.toolBarSymbolOptions?.activated;
    }
    return this.toolBarList[q4]?.toolBarSymbolOptions?.normal;
  }

  getIconColor(p4) {
    if (this.activateIndex === p4 && (this.toolBarList[p4]?.state === ItemState.ACTIVATE)) {
      return this.toolBarList[p4]?.activatedIconColor ?? this.iconActivePrimaryColor;
    }
    return this.toolBarList[p4]?.iconColor ?? this.iconPrimaryColor;
  }

  getTextColor(o4) {
    if (this.activateIndex === o4 && (this.toolBarList[o4]?.state === ItemState.ACTIVATE)) {
      return this.toolBarList[o4]?.activatedTextColor ?? this.fontActivatedPrimaryColor;
    }
    return this.toolBarList[o4]?.textColor ?? this.fontPrimaryColor;
  }

  toLengthString(l4) {
    if (l4 === void (0)) {
      return '';
    }
    const m4 = l4.value;
    let n4 = '';
    switch (l4.unit) {
      case LengthUnit.PX:
        n4 = `${m4}px`;
        break;
      case LengthUnit.FP:
        n4 = `${m4}fp`;
        break;
      case LengthUnit.LPX:
        n4 = `${m4}lpx`;
        break;
      case LengthUnit.PERCENT:
        n4 = `${m4 * 100}%`;
        break;
      case LengthUnit.VP:
        n4 = `${m4}vp`;
        break;
      default:
        n4 = `${m4}vp`;
        break;
    }
    return n4;
  }

  clickEventAction(j4) {
    let k4 = this.toolBarList[j4];
    if (k4.state === ItemState.ACTIVATE) {
      if (this.activateIndex === j4) {
        this.activateIndex = -1;
      }
      else {
        this.activateIndex = j4;
      }
    }
    if (!(k4.state === ItemState.DISABLE)) {
      k4.action && k4.action();
    }
  }

  getItemGestureModifier(c4, d4) {
    let e4 = new ButtonGestureModifier(null);
    if (c4?.icon || c4?.toolBarSymbolOptions?.activated || c4?.toolBarSymbolOptions?.normal) {
      e4 = new ButtonGestureModifier(new CustomDialogController({
        builder: () => {
          let f4 = new ToolBarDialog(this, {
            itemDialog: c4,
            fontSize: this.fontSize,
            itemSymbolModifier: this.getToolBarSymbolModifier(d4),
          }, undefined, -1, () => { },
            { page: 'library2/src/main/ets/components/mainpage/MainPage.ets', line: 375, col: 18 });
          f4.setController();
          ViewPU.create(f4);
          let g4 = () => {
            return {
              itemDialog: c4,
              fontSize: this.fontSize,
              itemSymbolModifier: this.getToolBarSymbolModifier(d4)
            };
          };
          f4.paramsGenerator_ = g4;
        },
        maskColor: Color.Transparent,
        isModal: true,
        customStyle: true
      }, this));
      e4.fontSize = this.fontSize;
    }
    return e4;
  }

  refreshData() {
    this.menuContent = [];
    for (let b4 = 0; b4 < this.toolBarList.length; b4++) {
      if (b4 >= this.moreIndex && this.toolBarList.length > TOOLBAR_MAX_LENGTH) {
        this.menuContent[b4 - this.moreIndex] = {
          value: this.toolBarList[b4].content,
          action: this.toolBarList[b4].action,
          enabled: this.toolBarList[b4].state !== ItemState.DISABLE,
        };
      }
      else {
        this.menuContent = [];
      }
      this.toolBarItemBackground[b4] = this.toolBarItemBackground[b4] ?? Color.Transparent;
    }
    return true;
  }

  onMeasureSize(u3, v3, w3) {
    this.fontSize = this.getFontSizeScale();
    let x3 = { height: 0, width: 0 };
    v3.forEach((z3) => {
      let a4 = z3.measure(w3);
      x3.width = a4.width;
      x3.height = a4.height;
    });
    return x3;
  }

  aboutToAppear() {
    this.refreshData();
    try {
      this.isFollowSystem = this.getUIContext()?.isFollowingSystemFontScale();
      this.maxFontSizeScale = this.getUIContext()?.getMaxFontScale();
    }
    catch (r3) {
      let s3 = r3?.code;
      let t3 = r3?.message;
      hilog.error(0x3900, 'Ace', `Faild to toolBar getMaxFontScale, code: ${s3}, message: ${t3}`);
    }
  }

  initialRender() {
    this.observeComponentCreation2((p3, q3) => {
      Column.create();
      Column.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.toolBarModifier));
    }, Column);
    this.observeComponentCreation2((n3, o3) => {
      Tabs.create({ controller: this.controller });
      Tabs.visibility(Visibility.None);
    }, Tabs);
    Tabs.pop();
    this.observeComponentCreation2((l3, m3) => {
      Divider.create();
      Divider.width('100%');
      Divider.height(1);
      Divider.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.dividerModifier));
    }, Divider);
    this.observeComponentCreation2((j3, k3) => {
      Row.create();
      Row.justifyContent(FlexAlign.Center);
      Row.constraintSize({
        minHeight: this.toLengthString(this.toolBarModifier.heightValue),
        maxHeight: this.toLengthString(this.toolBarModifier.heightValue),
      });
      Row.width('100%');
      Row.height(this.toLengthString(this.toolBarModifier.heightValue));
      Row.padding({
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
    }, Row);
    this.observeComponentCreation2((u2, v2) => {
      ForEach.create();
      const w2 = (y2, z2) => {
        const a3 = y2;
        this.observeComponentCreation2((c3, d3) => {
          If.create();
          if (this.toolBarList.length <= TOOLBAR_MAX_LENGTH || z2 < this.moreIndex) {
            this.ifElseBranchUpdateFunction(0, () => {
              this.observeComponentCreation2((h3, i3) => {
                Row.create();
                Row.height('100%');
                Row.flexShrink(1);
              }, Row);
              this.TabBuilder.bind(this)(z2);
              Row.pop();
            });
          }
          else {
            this.ifElseBranchUpdateFunction(1, () => {
            });
          }
        }, If);
        If.pop();
      };
      this.forEachUpdateFunction(u2, this.toolBarList, w2, undefined, true, false);
    }, ForEach);
    ForEach.pop();
    this.observeComponentCreation2((n2, o2) => {
      If.create();
      if (this.refreshData() && this.toolBarList.length > TOOLBAR_MAX_LENGTH) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((s2, t2) => {
            Row.create();
            Row.height('100%');
            Row.flexShrink(1);
          }, Row);
          this.MoreTabBuilder.bind(this)(this.moreIndex);
          Row.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
    }, If);
    If.pop();
    Row.pop();
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