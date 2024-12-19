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
  constructor(o7) {
    this.fontSize = 1;
    this.controller = null;
    this.controller = o7;
  }

  applyGesture(l7) {
    if (this.fontSize >= ButtonGestureModifier.minFontSize) {
      l7.addGesture(new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime })
        .onAction(() => {
          if (l7) {
            this.controller?.open();
          }
        })
        .onActionEnd(() => {
          this.controller?.close();
        }));
    }
    else {
      l7.clearGestures();
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
    this.accessibilityText = '';
    this.accessibilityDescription = '';
    this.accessibilityLevel = 'auto';
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

  applyNormalAttribute(k7) {
    k7.backgroundColor(this.backgroundColorValue);
  }

  backgroundColor(j7) {
    this.backgroundColorValue = j7;
    return this;
  }

  height(i7) {
    this.heightValue = i7;
    return this;
  }

  stateEffect(h7) {
    this.stateEffectValue = h7;
    return this;
  }

  padding(g7) {
    this.paddingValue = g7;
    return this;
  }
}

export class ToolBar extends ViewPU {
  constructor(a7, b7, c7, d7 = -1, e7 = undefined, f7) {
    super(a7, c7, d7, f7);
    if (typeof e7 === 'function') {
      this.paramsGenerator_ = e7;
    }
    this.__toolBarList = new SynchedPropertyNesedObjectPU(b7.toolBarList, this, 'toolBarList');
    this.controller = new TabsController();
    this.__activateIndex = new SynchedPropertySimpleOneWayPU(b7.activateIndex, this, 'activateIndex');
    this.__dividerModifier = new SynchedPropertyObjectOneWayPU(b7.dividerModifier, this, 'dividerModifier');
    this.__toolBarModifier = new SynchedPropertyObjectOneWayPU(b7.toolBarModifier, this, 'toolBarModifier');
    this.__moreText = new SynchedPropertyObjectOneWayPU(b7.moreText, this, 'moreText');
    this.__menuContent = new ObservedPropertyObjectPU([], this, 'menuContent');
    this.__toolBarItemBackground = new ObservedPropertyObjectPU([], this, 'toolBarItemBackground');
    this.__iconPrimaryColor = new ObservedPropertyObjectPU({
      'id': -1,
      'type': 10001,
      params: ['sys.color.icon_primary'],
      'bundleName': '',
      'moduleName': ''
    },
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
        'moduleName': ''
      },
      icon: PUBLIC_MORE,
    };
    this.setInitiallyProvidedValue(b7);
    this.finalizeConstruction();
  }

  setInitiallyProvidedValue(z6) {
    this.__toolBarList.set(z6.toolBarList);
    if (z6.controller !== undefined) {
      this.controller = z6.controller;
    }
    if (z6.activateIndex === undefined) {
      this.__activateIndex.set(-1);
    }
    if (z6.dividerModifier === undefined) {
      this.__dividerModifier.set(new DividerModifier());
    }
    if (z6.toolBarModifier === undefined) {
      this.__toolBarModifier.set(new ToolBarModifier()
        .padding(LengthMetrics.resource({
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level12'],
          'bundleName': '',
          'moduleName': ''
        }))
        .stateEffect(true)
        .height(LengthMetrics.vp(DEFAULT_TOOLBAR_HEIGHT))
        .backgroundColor('sys.color.ohos_id_color_toolbar_bg'));
    }
    if (z6.moreText === undefined) {
      this.__moreText.set({
        'id': -1,
        'type': 10003,
        params: ['sys.string.ohos_toolbar_more'],
        'bundleName': '',
        'moduleName': '',
      });
    }
    if (z6.menuContent !== undefined) {
      this.menuContent = z6.menuContent;
    }
    if (z6.toolBarItemBackground !== undefined) {
      this.toolBarItemBackground = z6.toolBarItemBackground;
    }
    if (z6.iconPrimaryColor !== undefined) {
      this.iconPrimaryColor = z6.iconPrimaryColor;
    }
    if (z6.iconActivePrimaryColor !== undefined) {
      this.iconActivePrimaryColor = z6.iconActivePrimaryColor;
    }
    if (z6.fontPrimaryColor !== undefined) {
      this.fontPrimaryColor = z6.fontPrimaryColor;
    }
    if (z6.fontActivatedPrimaryColor !== undefined) {
      this.fontActivatedPrimaryColor = z6.fontActivatedPrimaryColor;
    }
    if (z6.symbolEffect !== undefined) {
      this.symbolEffect = z6.symbolEffect;
    }
    if (z6.fontSize !== undefined) {
      this.fontSize = z6.fontSize;
    }
    if (z6.isFollowSystem !== undefined) {
      this.isFollowSystem = z6.isFollowSystem;
    }
    if (z6.maxFontSizeScale !== undefined) {
      this.maxFontSizeScale = z6.maxFontSizeScale;
    }
    if (z6.moreIndex !== undefined) {
      this.moreIndex = z6.moreIndex;
    }
    if (z6.moreItem !== undefined) {
      this.moreItem = z6.moreItem;
    }
  }

  updateStateVars(y6) {
    this.__toolBarList.set(y6.toolBarList);
    this.__activateIndex.reset(y6.activateIndex);
    this.__dividerModifier.reset(y6.dividerModifier);
    this.__toolBarModifier.reset(y6.toolBarModifier);
    this.__moreText.reset(y6.moreText);
  }

  purgeVariableDependenciesOnElmtId(x6) {
    this.__toolBarList.purgeDependencyOnElmtId(x6);
    this.__activateIndex.purgeDependencyOnElmtId(x6);
    this.__dividerModifier.purgeDependencyOnElmtId(x6);
    this.__toolBarModifier.purgeDependencyOnElmtId(x6);
    this.__moreText.purgeDependencyOnElmtId(x6);
    this.__menuContent.purgeDependencyOnElmtId(x6);
    this.__toolBarItemBackground.purgeDependencyOnElmtId(x6);
    this.__iconPrimaryColor.purgeDependencyOnElmtId(x6);
    this.__iconActivePrimaryColor.purgeDependencyOnElmtId(x6);
    this.__fontPrimaryColor.purgeDependencyOnElmtId(x6);
    this.__fontActivatedPrimaryColor.purgeDependencyOnElmtId(x6);
    this.__symbolEffect.purgeDependencyOnElmtId(x6);
    this.__fontSize.purgeDependencyOnElmtId(x6);
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

  set activateIndex(w6) {
    this.__activateIndex.set(w6);
  }

  get dividerModifier() {
    return this.__dividerModifier.get();
  }

  set dividerModifier(v6) {
    this.__dividerModifier.set(v6);
  }

  get toolBarModifier() {
    return this.__toolBarModifier.get();
  }

  set toolBarModifier(u6) {
    this.__toolBarModifier.set(u6);
  }

  get moreText() {
    return this.__moreText.get();
  }

  set moreText(t6) {
    this.__moreText.set(t6);
  }

  get menuContent() {
    return this.__menuContent.get();
  }

  set menuContent(s6) {
    this.__menuContent.set(s6);
  }

  get toolBarItemBackground() {
    return this.__toolBarItemBackground.get();
  }

  set toolBarItemBackground(r6) {
    this.__toolBarItemBackground.set(r6);
  }

  get iconPrimaryColor() {
    return this.__iconPrimaryColor.get();
  }

  set iconPrimaryColor(q6) {
    this.__iconPrimaryColor.set(q6);
  }

  get iconActivePrimaryColor() {
    return this.__iconActivePrimaryColor.get();
  }

  set iconActivePrimaryColor(p6) {
    this.__iconActivePrimaryColor.set(p6);
  }

  get fontPrimaryColor() {
    return this.__fontPrimaryColor.get();
  }

  set fontPrimaryColor(o6) {
    this.__fontPrimaryColor.set(o6);
  }

  get fontActivatedPrimaryColor() {
    return this.__fontActivatedPrimaryColor.get();
  }

  set fontActivatedPrimaryColor(n6) {
    this.__fontActivatedPrimaryColor.set(n6);
  }

  get symbolEffect() {
    return this.__symbolEffect.get();
  }

  set symbolEffect(m6) {
    this.__symbolEffect.set(m6);
  }

  get fontSize() {
    return this.__fontSize.get();
  }

  set fontSize(l6) {
    this.__fontSize.set(l6);
  }

  onWillApplyTheme(k6) {
    this.iconPrimaryColor = k6.colors.iconPrimary;
    this.iconActivePrimaryColor = k6.colors.iconEmphasize;
    this.fontPrimaryColor = k6.colors.fontPrimary;
    this.fontActivatedPrimaryColor = k6.colors.fontEmphasize;
  }

  MoreTabBuilder(x5, y5 = null) {
    this.observeComponentCreation2((g6, h6) => {
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
      Column.accessibilityText(ObservedObject.GetRawObject(this.moreText));
      Column.accessibilityGroup(true);
      Column.focusable(true);
      Column.focusOnTouch(true);
      Column.focusBox({
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
      Column.bindMenu(ObservedObject.GetRawObject(this.menuContent), {
        placement: Placement.TopRight,
        offset: { x: -12, y: -10 }
      });
      Column.backgroundColor(this.toolBarItemBackground[x5]);
      Column.onHover((j6) => {
        if (j6) {
          this.toolBarItemBackground[x5] = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_hover'],
            'bundleName': '',
            'moduleName': '',
          };
        }
        else {
          this.toolBarItemBackground[x5] = Color.Transparent;
        }
      });
      ViewStackProcessor.visualState('pressed');
      Column.backgroundColor((!this.toolBarModifier.stateEffectValue) ?
      this.toolBarItemBackground[x5] : {
          'id': -1,
          'type': 10001,
          params: ['sys.color.ohos_id_color_click_effect'],
          'bundleName': '',
          'moduleName': '',
        });
      ViewStackProcessor.visualState();
      Column.gestureModifier(this.getItemGestureModifier(this.moreItem, x5));
    }, Column);
    this.observeComponentCreation2((e6, f6) => {
      Image.create(PUBLIC_MORE);
      Image.width(IMAGE_SIZE);
      Image.height(IMAGE_SIZE);
      Image.fillColor(ObservedObject.GetRawObject(this.iconPrimaryColor));
      Image.margin({
        bottom: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level1'],
          'bundleName': '',
          'moduleName': '',
        }
      });
      Image.objectFit(ImageFit.Contain);
      Image.draggable(false);
    }, Image);
    this.observeComponentCreation2((c6, d6) => {
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

  TabBuilder(b5, c5 = null) {
    this.observeComponentCreation2((s5, t5) => {
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
      Column.opacity(this.toolBarList[b5]?.state !== ItemState.DISABLE ? 1 : 0.4);
      Column.enabled(this.toolBarList[b5]?.state !== ItemState.DISABLE);
      Column.accessibilityGroup(true);
      Column.accessibilityText(this.toStringFormat(this.toolBarList[b5]?.accessibilityText) ??
      this.toStringFormat(this.toolBarList[b5]?.content));
      Column.accessibilityDescription(this.toStringFormat(this.toolBarList[b5]?.accessibilityDescription) ?? '');
      Column.accessibilityLevel(this.toStringFormat(this.toolBarList[b5]?.accessibilityLevel) ?? 'auto');
      Column.focusable(!(this.toolBarList[b5]?.state === ItemState.DISABLE));
      Column.focusOnTouch(!(this.toolBarList[b5]?.state === ItemState.DISABLE));
      Column.focusBox({
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
      Column.backgroundColor(this.toolBarItemBackground[b5]);
      Column.onHover((w5) => {
        if (w5 && this.toolBarList[b5]?.state !== ItemState.DISABLE) {
          this.toolBarItemBackground[b5] = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_hover'],
            'bundleName': '',
            'moduleName': '',
          };
        }
        else {
          this.toolBarItemBackground[b5] = Color.Transparent;
        }
      });
      ViewStackProcessor.visualState('pressed');
      Column.backgroundColor((this.toolBarList[b5]?.state === ItemState.DISABLE) ||
        (!this.toolBarModifier.stateEffectValue) ?
      this.toolBarItemBackground[b5] : {
          'id': -1,
          'type': 10001,
          params: ['sys.color.ohos_id_color_click_effect'],
          'bundleName': '',
          'moduleName': '',
        });
      ViewStackProcessor.visualState();
      Column.onClick(() => {
        this.clickEventAction(b5);
      });
      Column.gestureModifier(this.getItemGestureModifier(this.toolBarList[b5], b5));
    }, Column);
    this.observeComponentCreation2((i5, j5) => {
      If.create();
      if (this.toolBarList[b5]?.toolBarSymbolOptions?.normal ||
        this.toolBarList[b5]?.toolBarSymbolOptions?.activated) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((q5, r5) => {
            SymbolGlyph.create();
            SymbolGlyph.fontSize(IMAGE_SIZE);
            SymbolGlyph.symbolEffect(ObservedObject.GetRawObject(this.symbolEffect), false);
            SymbolGlyph.attributeModifier.bind(this)(this.getToolBarSymbolModifier(b5));
            SymbolGlyph.margin({
              bottom: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level1'],
                'bundleName': '',
                'moduleName': '',
              }
            });
          }, SymbolGlyph);
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((m5, n5) => {
            Image.create(this.toolBarList[b5]?.icon);
            Image.width(IMAGE_SIZE);
            Image.height(IMAGE_SIZE);
            Image.fillColor(this.getIconColor(b5));
            Image.margin({
              bottom: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level1'],
                'bundleName': '',
                'moduleName': '',
              }
            });
            Image.objectFit(ImageFit.Contain);
            Image.draggable(false);
          }, Image);
        });
      }
    }, If);
    If.pop();
    this.observeComponentCreation2((g5, h5) => {
      Text.create(this.toolBarList[b5]?.content);
      Text.fontColor(this.getTextColor(b5));
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
    }, Text);
    Text.pop();
    Column.pop();
  }

  getFontSizeScale() {
    let z4 = this.getUIContext();
    let a5 = z4.getHostContext()?.config?.fontSizeScale ?? 1;
    if (!this.isFollowSystem) {
      return 1;
    }
    else {
      return Math.min(a5, this.maxFontSizeScale);
    }
  }

  getToolBarSymbolModifier(y4) {
    if ((!this.toolBarList[y4]?.toolBarSymbolOptions?.activated) &&
      (!this.toolBarList[y4]?.toolBarSymbolOptions?.normal)) {
      return undefined;
    }
    if (this.activateIndex === y4 && (this.toolBarList[y4]?.state === ItemState.ACTIVATE)) {
      return this.toolBarList[y4]?.toolBarSymbolOptions?.activated;
    }
    return this.toolBarList[y4]?.toolBarSymbolOptions?.normal;
  }

  getIconColor(x4) {
    if (this.activateIndex === x4 && (this.toolBarList[x4]?.state === ItemState.ACTIVATE)) {
      return this.toolBarList[x4]?.activatedIconColor ?? this.iconActivePrimaryColor;
    }
    return this.toolBarList[x4]?.iconColor ?? this.iconPrimaryColor;
  }

  getTextColor(w4) {
    if (this.activateIndex === w4 && (this.toolBarList[w4]?.state === ItemState.ACTIVATE)) {
      return this.toolBarList[w4]?.activatedTextColor ?? this.fontActivatedPrimaryColor;
    }
    return this.toolBarList[w4]?.textColor ?? this.fontPrimaryColor;
  }

  toStringFormat(r4) {
    if (typeof r4 === 'string' || typeof r4 === 'undefined') {
      return r4;
    }
    else {
      let s4 = '';
      try {
        s4 = getContext()?.resourceManager?.getStringSync(r4?.id);
      }
      catch (t4) {
        let u4 = t4?.code;
        let v4 = t4?.message;
        hilog.error(0x3900, 'Ace', `Faild to toolBar toStringFormat, code: ${u4}, message: ${v4}`);
      }
      return s4;
    }
  }

  toLengthString(o4) {
    if (o4 === void (0)) {
      return '';
    }
    const p4 = o4.value;
    let q4 = '';
    switch (o4.unit) {
      case LengthUnit.PX:
        q4 = `${p4}px`;
        break;
      case LengthUnit.FP:
        q4 = `${p4}fp`;
        break;
      case LengthUnit.LPX:
        q4 = `${p4}lpx`;
        break;
      case LengthUnit.PERCENT:
        q4 = `${p4 * 100}%`;
        break;
      case LengthUnit.VP:
        q4 = `${p4}vp`;
        break;
      default:
        q4 = `${p4}vp`;
        break;
    }
    return q4;
  }

  clickEventAction(m4) {
    let n4 = this.toolBarList[m4];
    if (n4.state === ItemState.ACTIVATE) {
      if (this.activateIndex === m4) {
        this.activateIndex = -1;
      }
      else {
        this.activateIndex = m4;
      }
    }
    if (!(n4.state === ItemState.DISABLE)) {
      n4.action && n4.action();
    }
  }

  getItemGestureModifier(f4, g4) {
    let h4 = new ButtonGestureModifier(null);
    if (f4?.icon || f4?.toolBarSymbolOptions?.activated || f4?.toolBarSymbolOptions?.normal) {
      h4 = new ButtonGestureModifier(new CustomDialogController({
        builder: () => {
          let i4 = new ToolBarDialog(this, {
            itemDialog: f4,
            fontSize: this.fontSize,
            itemSymbolModifier: this.getToolBarSymbolModifier(g4),
          }, undefined, -1, () => {
          }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 391, col: 18 });
          i4.setController();
          ViewPU.create(i4);
          let j4 = () => {
            return {
              itemDialog: f4,
              fontSize: this.fontSize,
              itemSymbolModifier: this.getToolBarSymbolModifier(g4),
            };
          };
          i4.paramsGenerator_ = j4;
        },
        maskColor: Color.Transparent,
        isModal: true,
        customStyle: true,
      }, this));
      h4.fontSize = this.fontSize;
    }
    return h4;
  }
  refreshData() {
    this.menuContent = [];
    for (let e4 = 0; e4 < this.toolBarList.length; e4++) {
      if (e4 >= this.moreIndex && this.toolBarList.length > TOOLBAR_MAX_LENGTH) {
        this.menuContent[e4 - this.moreIndex] = {
          value: this.toolBarList[e4].content,
          action: this.toolBarList[e4].action,
          enabled: this.toolBarList[e4].state !== ItemState.DISABLE,
        };
      }
      else {
        this.menuContent = [];
      }
      this.toolBarItemBackground[e4] = this.toolBarItemBackground[e4] ?? Color.Transparent;
    }
    return true;
  }

  onMeasureSize(x3, y3, z3) {
    this.fontSize = this.getFontSizeScale();
    let a4 = { height: 0, width: 0 };
    y3.forEach((c4) => {
      let d4 = c4.measure(z3);
      a4.width = d4.width;
      a4.height = d4.height;
    });
    return a4;
  }

  aboutToAppear() {
    this.refreshData();
    try {
      this.isFollowSystem = this.getUIContext()?.isFollowingSystemFontScale();
      this.maxFontSizeScale = this.getUIContext()?.getMaxFontScale();
    }
    catch (u3) {
      let v3 = u3?.code;
      let w3 = u3?.message;
      hilog.error(0x3900, 'Ace', `Faild to toolBar getMaxFontScale, code: ${v3}, message: ${w3}`);
    }
  }

  initialRender() {
    this.observeComponentCreation2((s3, t3) => {
      Column.create();
      Column.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.toolBarModifier));
    }, Column);
    this.observeComponentCreation2((q3, r3) => {
      Tabs.create({ controller: this.controller });
      Tabs.visibility(Visibility.None);
    }, Tabs);
    Tabs.pop();
    this.observeComponentCreation2((o3, p3) => {
      Divider.create();
      Divider.width('100%');
      Divider.height(1);
      Divider.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.dividerModifier));
    }, Divider);
    this.observeComponentCreation2((m3, n3) => {
      Row.create();
      Row.justifyContent(FlexAlign.Center);
      Row.constraintSize({
        minHeight: this.toLengthString(this.toolBarModifier.heightValue),
        maxHeight: this.toLengthString(this.toolBarModifier.heightValue),
      });
      Row.width('100%');
      Row.height(this.toLengthString(this.toolBarModifier.heightValue));
      Row.padding({
        start: this.toolBarList.length < TOOLBAR_MAX_LENGTH ?
        this.toolBarModifier.paddingValue : LengthMetrics.resource({
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level0'],
          'bundleName': '',
          'moduleName': '',
        }),
        end: this.toolBarList.length < TOOLBAR_MAX_LENGTH ?
        this.toolBarModifier.paddingValue : LengthMetrics.resource({
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level0'],
          'bundleName': '',
          'moduleName': ''
        }),
      });
    }, Row);
    this.observeComponentCreation2((u2, v2) => {
      ForEach.create();
      const w2 = (b3, c3) => {
        const d3 = b3;
        this.observeComponentCreation2((f3, g3) => {
          If.create();
          if (this.toolBarList.length <= TOOLBAR_MAX_LENGTH || c3 < this.moreIndex) {
            this.ifElseBranchUpdateFunction(0, () => {
              this.observeComponentCreation2((k3, l3) => {
                Row.create();
                Row.height('100%');
                Row.flexShrink(1);
              }, Row);
              this.TabBuilder.bind(this)(c3);
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
      this.forEachUpdateFunction(u2, this.toolBarList, w2, (z2, a3) => {
        return `${this.getUniqueId()}__${a3}}`;
      }, true, true);
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