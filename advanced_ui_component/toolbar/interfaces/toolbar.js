/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

let i = (this && this.i) || function (t1, target, key, desc) {
  let c = arguments.length;
  let r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc;
  let d;
  if (typeof Reflect === 'object' && typeof Reflect.v1 === 'function') {
    r = Reflect.v1(t1, target, key, desc);
  } else {
    for (let u1 = t1.length - 1; u1 >= 0; u1--) {
      (d = t1[u1]) && (r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r);
    }
  }
  return c > 3 && r && Object.defineProperty(target, key, r), r;
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
(function (ItemState) {
  ItemState[ItemState.ENABLE = 1] = 'ENABLE';
  ItemState[ItemState.DISABLE = 2] = 'DISABLE';
  ItemState[ItemState.ACTIVATE = 3] = 'ACTIVATE';
})(ItemState || (ItemState = {}));
const j = {
  'id': -1,
  'type': 40000,
  params: ['sys.symbol.dot_grid_2x2'],
  'bundleName': '__harDefaultBundleName__',
  'moduleName': '__harDefaultModuleName__'
};
const m = '24vp';
const o = 56;
const t = 5;
const u = 3.2;
const a1 = '64vp';
const b1 = '256vp';
const c1 = '216vp';
const d1 = '18.3fp';
const e1 = -2;
const f1 = 2;
const g1 = 40000;

class h1 {
  constructor(controller) {
    this.fontSize = 1;
    this.controller = null;
    this.controller = controller;
  }

  applyGesture(event) {
    if (this.fontSize >= h1.minFontSize) {
      event.addGesture(new LongPressGestureHandler({ repeat: false, duration: h1.w1 })
        .onAction(() => {
          if (event) {
            this.controller?.open();
          }
        })
        .onActionEnd(() => {
          this.controller?.close();
        })
        .onActionCancel(() => {
          this.controller?.close();
        }));
    } else {
      event.clearGestures();
    }
  }
}

h1.w1 = 500;
h1.minFontSize = 1.75;
class Util {
  static z1(s1) {
    if (!Util.a2(s1)) {
      return false;
    }
    let resource = s1;
    return resource.type === g1;
  }
  static a2(resource) {
    if (!resource) {
      return false;
    }
    if (typeof resource === 'string' || typeof resource === 'undefined') {
      return false;
    }
    return true;
  }
}
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
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__'
    };
    this.activatedIconColor = {
      'id': -1,
      'type': 10001,
      params: ['sys.color.icon_emphasize'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__'
    };
    this.textColor = {
      'id': -1,
      'type': 10001,
      params: ['sys.color.font_primary'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__'
    };
    this.activatedTextColor = {
      'id': -1,
      'type': 10001,
      params: ['sys.color.font_emphasize'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__'
    };
    this.toolBarSymbolOptions = undefined;
    this.accessibilityText = '';
    this.accessibilityDescription = '';
    this.accessibilityLevel = 'auto';
  }
};
ToolBarOption = i([
  Observed
], ToolBarOption);
export { ToolBarOption };
let ToolBarOptions = class ToolBarOptions extends Array {
};
ToolBarOptions = i([
  Observed
], ToolBarOptions);
export { ToolBarOptions };
export class ToolBarModifier {
  constructor() {
    this.b2 = {
      'id': -1,
      'type': 10001,
      params: ['sys.color.ohos_id_color_toolbar_bg'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__'
    };
    this.c2 = LengthMetrics.vp(o);
    this.d2 = true;
    this.paddingValue = LengthMetrics.resource({
      'id': -1,
      'type': 10002,
      params: ['sys.float.padding_level12'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__'
    });
  }

  applyNormalAttribute(instance) {
    instance.backgroundColor(this.b2);
  }

  backgroundColor(backgroundColor) {
    this.b2 = backgroundColor;
    return this;
  }

  height(height) {
    this.c2 = height;
    return this;
  }

  stateEffect(stateEffect) {
    this.d2 = stateEffect;
    return this;
  }

  padding(padding) {
    this.paddingValue = padding;
    return this;
  }
}

class g2 {
  constructor() {
    this.i2 = {
      'id': -1,
      'type': 10001,
      params: ['sys.color.icon_primary'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__'
    };
    this.j2 = {
      'id': -1,
      'type': 10001,
      params: ['sys.color.icon_emphasize'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__'
    };
    this.l2 = {
      'id': -1,
      'type': 10001,
      params: ['sys.color.font_primary'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__'
    };
    this.m2 = {
      'id': -1,
      'type': 10001,
      params: ['sys.color.font_emphasize'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__'
    };
  }
}

export class ToolBar extends ViewPU {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
    super(parent, __localStorage, elmtId, extraInfo);
    if (typeof paramsLambda === 'function') {
      this.paramsGenerator_ = paramsLambda;
    }
    this.__toolBarList = new SynchedPropertyNesedObjectPU(params.toolBarList, this, 'toolBarList');
    this.controller = new TabsController();
    this.__activateIndex = new SynchedPropertySimpleOneWayPU(params.activateIndex, this, 'activateIndex');
    this.__dividerModifier = new SynchedPropertyObjectOneWayPU(params.dividerModifier, this, 'dividerModifier');
    this.__toolBarModifier = new SynchedPropertyObjectOneWayPU(params.toolBarModifier, this, 'toolBarModifier');
    this.__moreText = new SynchedPropertyObjectOneWayPU(params.moreText, this, 'moreText');
    this.__menuContent = new ObservedPropertyObjectPU([], this, 'menuContent');
    this.__toolBarItemBackground = new ObservedPropertyObjectPU([], this, 'toolBarItemBackground');
    this.__toolBarTheme = new ObservedPropertyObjectPU(new g2(), this, 'toolBarTheme');
    this.__fontSize = new ObservedPropertySimplePU(1, this, 'fontSize');
    this.isFollowSystem = false;
    this.maxFontSizeScale = 3.2;
    this.moreIndex = 4;
    this.moreItem = {
      content: {
        'id': -1,
        'type': 10003,
        params: ['sys.string.ohos_toolbar_more'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
      },
      icon: j,
    };
    this.setInitiallyProvidedValue(params);
    this.finalizeConstruction();
  }

  setInitiallyProvidedValue(params) {
    this.__toolBarList.set(params.toolBarList);
    if (params.controller !== undefined) {
      this.controller = params.controller;
    }
    if (params.activateIndex === undefined) {
      this.__activateIndex.set(-1);
    }
    if (params.moreText === undefined) {
      this.__moreText.set({
        'id': -1,
        'type': 10003,
        params: ['sys.string.ohos_toolbar_more'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
      });
    }
    if (params.menuContent !== undefined) {
      this.menuContent = params.menuContent;
    }
    if (params.toolBarItemBackground !== undefined) {
      this.toolBarItemBackground = params.toolBarItemBackground;
    }
    if (params.toolBarTheme !== undefined) {
      this.toolBarTheme = params.toolBarTheme;
    }
    if (params.fontSize !== undefined) {
      this.fontSize = params.fontSize;
    }
    if (params.isFollowSystem !== undefined) {
      this.isFollowSystem = params.isFollowSystem;
    }
    if (params.maxFontSizeScale !== undefined) {
      this.maxFontSizeScale = params.maxFontSizeScale;
    }
    if (params.moreIndex !== undefined) {
      this.moreIndex = params.moreIndex;
    }
    if (params.moreItem !== undefined) {
      this.moreItem = params.moreItem;
    }
  }

  updateStateVars(params) {
    this.__toolBarList.set(params.toolBarList);
    this.__activateIndex.reset(params.activateIndex);
    this.__dividerModifier.reset(params.dividerModifier);
    this.__toolBarModifier.reset(params.toolBarModifier);
    this.__moreText.reset(params.moreText);
  }

  purgeVariableDependenciesOnElmtId(rmElmtId) {
    this.__toolBarList.purgeDependencyOnElmtId(rmElmtId);
    this.__activateIndex.purgeDependencyOnElmtId(rmElmtId);
    this.__dividerModifier.purgeDependencyOnElmtId(rmElmtId);
    this.__toolBarModifier.purgeDependencyOnElmtId(rmElmtId);
    this.__moreText.purgeDependencyOnElmtId(rmElmtId);
    this.__menuContent.purgeDependencyOnElmtId(rmElmtId);
    this.__toolBarItemBackground.purgeDependencyOnElmtId(rmElmtId);
    this.__toolBarTheme.purgeDependencyOnElmtId(rmElmtId);
    this.__fontSize.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
    this.__toolBarList.aboutToBeDeleted();
    this.__activateIndex.aboutToBeDeleted();
    this.__dividerModifier.aboutToBeDeleted();
    this.__toolBarModifier.aboutToBeDeleted();
    this.__moreText.aboutToBeDeleted();
    this.__menuContent.aboutToBeDeleted();
    this.__toolBarItemBackground.aboutToBeDeleted();
    this.__toolBarTheme.aboutToBeDeleted();
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

  set activateIndex(newValue) {
    this.__activateIndex.set(newValue);
  }
  get dividerModifier() {
    return this.__dividerModifier.get();
  }

  set dividerModifier(newValue) {
    this.__dividerModifier.set(newValue);
  }
  get toolBarModifier() {
    return this.__toolBarModifier.get();
  }

  set toolBarModifier(newValue) {
    this.__toolBarModifier.set(newValue);
  }
  get moreText() {
    return this.__moreText.get();
  }

  set moreText(newValue) {
    this.__moreText.set(newValue);
  }
  get menuContent() {
    return this.__menuContent.get();
  }

  set menuContent(newValue) {
    this.__menuContent.set(newValue);
  }
  get toolBarItemBackground() {
    return this.__toolBarItemBackground.get();
  }

  set toolBarItemBackground(newValue) {
    this.__toolBarItemBackground.set(newValue);
  }

  get toolBarTheme() {
    return this.__toolBarTheme.get();
  }

  set toolBarTheme(newValue) {
    this.__toolBarTheme.set(newValue);
  }
  get fontSize() {
    return this.__fontSize.get();
  }

  set fontSize(newValue) {
    this.__fontSize.set(newValue);
  }

  onWillApplyTheme(theme) {
    this.toolBarTheme.i2 = theme.colors.iconPrimary;
    this.toolBarTheme.j2 = theme.colors.iconEmphasize;
    this.toolBarTheme.l2 = theme.colors.fontPrimary;
    this.toolBarTheme.m2 = theme.colors.fontEmphasize;
  }
  MoreTabBuilder(index, parent = null) {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
      Button.accessibilityGroup(true);
      Button.focusable(true);
      Button.focusOnTouch(true);
      Button.focusBox({
        margin: LengthMetrics.vp(e1),
        strokeWidth: LengthMetrics.vp(f1),
        strokeColor: ColorMetrics.resourceColor({
          'id': -1,
          'type': 10001,
          params: ['sys.color.ohos_id_color_focused_outline'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__'
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
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
      });
      Button.backgroundColor(this.toolBarItemBackground[index]);
      Button.onHover((isHover) => {
        if (isHover) {
          this.toolBarItemBackground[index] = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_hover'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
          };
        }
        else {
          this.toolBarItemBackground[index] = Color.Transparent;
        }
      });
      ViewStackProcessor.visualState('pressed');
      Button.backgroundColor((!this.toolBarModifier?.d2) ?
      this.toolBarItemBackground[index] : {
          'id': -1,
          'type': 10001,
          params: ['sys.color.ohos_id_color_click_effect'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__'
        });
      ViewStackProcessor.visualState();
      Button.gestureModifier(this.getItemGestureModifier(this.moreItem, index));
    }, Button);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Column.create();
      Column.width('100%');
      Column.height('100%');
      Column.justifyContent(FlexAlign.Center);
      Column.padding({
        start: LengthMetrics.resource({
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level2'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__'
        }),
        end: LengthMetrics.resource({
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level2'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__'
        }),
      });
      Column.borderRadius({
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_corner_radius_clicked'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
      });
    }, Column);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      SymbolGlyph.create(j);
      SymbolGlyph.fontSize(m);
      SymbolGlyph.fontColor([this.toolBarTheme.i2]);
      SymbolGlyph.draggable(false);
      SymbolGlyph.margin({
        bottom: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level1'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__'
        }
      });
    }, SymbolGlyph);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Text.create(this.moreText);
      Text.fontColor(this.toolBarTheme.l2);
      Text.fontSize({
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_text_size_caption'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
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
  TabBuilder(index, parent = null) {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
      Button.accessibilityGroup(true);
      Button.accessibilityText(this.toStringFormat(this.toolBarList[index]?.accessibilityText) ??
      this.toStringFormat(this.toolBarList[index]?.content));
      Button.accessibilityDescription(this.toStringFormat(this.toolBarList[index]?.accessibilityDescription) ??
        '');
      Button.accessibilityLevel(this.toStringFormat(this.toolBarList[index]?.accessibilityLevel) ?? 'auto');
      Button.enabled(this.toolBarList[index]?.state !== ItemState.DISABLE);
      Button.width('100%');
      Button.height('100%');
      Button.borderRadius({
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_corner_radius_clicked'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
      });
      Button.focusable(!(this.toolBarList[index]?.state === ItemState.DISABLE));
      Button.focusOnTouch(!(this.toolBarList[index]?.state === ItemState.DISABLE));
      Button.focusBox({
        margin: LengthMetrics.vp(e1),
        strokeWidth: LengthMetrics.vp(f1),
        strokeColor: ColorMetrics.resourceColor({
          'id': -1,
          'type': 10001,
          params: ['sys.color.ohos_id_color_focused_outline'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__'
        })
      });
      Button.backgroundColor(this.toolBarItemBackground[index]);
      Button.onHover((isHover) => {
        if (isHover && this.toolBarList[index]?.state !== ItemState.DISABLE) {
          this.toolBarItemBackground[index] = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_hover'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
          };
        } else {
          this.toolBarItemBackground[index] = Color.Transparent;
        }
      });
      ViewStackProcessor.visualState('pressed');
      Button.backgroundColor((this.toolBarList[index]?.state === ItemState.DISABLE) ||
        (!this.toolBarModifier?.d2) ?
      this.toolBarItemBackground[index] : {
          'id': -1,
          'type': 10001,
          params: ['sys.color.ohos_id_color_click_effect'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__'
        });
      ViewStackProcessor.visualState();
      Button.onClick(() => {
        this.clickEventAction(index);
      });
      Button.gestureModifier(this.getItemGestureModifier(this.toolBarList[index], index));
    }, Button);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Column.create();
      Column.justifyContent(FlexAlign.Center);
      Column.width('100%');
      Column.height('100%');
      Column.borderRadius({
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_corner_radius_clicked'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
      });
      Column.padding({
        start: LengthMetrics.resource({
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level2'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__'
        }),
        end: LengthMetrics.resource({
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level2'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__'
        }),
      });
    }, Column);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.toolBarList[index]?.toolBarSymbolOptions?.normal ||
        this.toolBarList[index]?.toolBarSymbolOptions?.activated) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            SymbolGlyph.create();
            SymbolGlyph.fontSize(m);
            SymbolGlyph.symbolEffect(new SymbolEffect(), false);
            SymbolGlyph.attributeModifier.bind(this)(this.getToolBarSymbolModifier(index));
            SymbolGlyph.margin({
              bottom: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level1'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
              }
            });
          }, SymbolGlyph);
        });
      } else if (Util.z1(this.toolBarList[index]?.icon)) {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            SymbolGlyph.create(this.toolBarList[index]?.icon);
            SymbolGlyph.fontSize(m);
            SymbolGlyph.fontColor([this.getIconColor(index)]);
            SymbolGlyph.margin({
              bottom: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level1'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
              }
            });
          }, SymbolGlyph);
        });
      }
      else {
        this.ifElseBranchUpdateFunction(2, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(this.toolBarList[index]?.icon);
            Image.width(m);
            Image.height(m);
            Image.fillColor(this.getIconColor(index));
            Image.margin({
              bottom: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level1'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
              }
            });
            Image.objectFit(ImageFit.Contain);
            Image.draggable(false);
          }, Image);
        });
      }
    }, If);
    If.pop();
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Text.create(this.toolBarList[index]?.content);
      Text.fontColor(this.getTextColor(index));
      Text.fontSize({
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_text_size_caption'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
      });
      Text.maxFontSize({
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_text_size_caption'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
      });
      Text.minFontSize(9);
      Text.fontWeight(FontWeight.Medium);
      Text.maxLines(1);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.textAlign(TextAlign.Center);
      Text.focusable(!(this.toolBarList[index]?.state === ItemState.DISABLE));
      Text.focusOnTouch(!(this.toolBarList[index]?.state === ItemState.DISABLE));
    }, Text);
    Text.pop();
    Column.pop();
    Button.pop();
  }
  getFontSizeScale() {
    let context = this.getUIContext();
    let q1 = context.getHostContext()?.config?.fontSizeScale ?? 1;
    if (!this.isFollowSystem) {
      return 1;
    }
    else {
      return Math.min(q1, this.maxFontSizeScale);
    }
  }

  getToolBarSymbolModifier(index) {
    if ((!this.toolBarList[index]?.toolBarSymbolOptions?.activated) &&
      (!this.toolBarList[index]?.toolBarSymbolOptions?.normal)) {
      return undefined;
    }
    if (this.activateIndex === index && (this.toolBarList[index]?.state === ItemState.ACTIVATE)) {
      return this.toolBarList[index]?.toolBarSymbolOptions?.activated;
    }
    return this.toolBarList[index]?.toolBarSymbolOptions?.normal;
  }

  getIconColor(index) {
    if (this.activateIndex === index && (this.toolBarList[index]?.state === ItemState.ACTIVATE)) {
      return this.toolBarList[index]?.activatedIconColor ?? this.toolBarTheme.j2;
    }
    return this.toolBarList[index]?.iconColor ?? this.toolBarTheme.i2;
  }

  getTextColor(index) {
    if (this.activateIndex === index && (this.toolBarList[index]?.state === ItemState.ACTIVATE)) {
      return this.toolBarList[index]?.activatedTextColor ?? this.toolBarTheme.m2;
    }
    return this.toolBarList[index]?.textColor ?? this.toolBarTheme.l2;
  }

  toStringFormat(resource) {
    if (typeof resource === 'string' || typeof resource === 'undefined') {
      return resource;
    }
    else {
      let p1 = '';
      try {
        p1 = getContext()?.resourceManager?.getStringSync(resource?.id);
      } catch (err) {
        let code = err?.code;
        let message = err?.message;
        hilog.error(0x3900, 'Ace', `Faild to toolBar toStringFormat, code: ${code}, message: ${message}`);
      }
      return p1;
    }
  }

  toLengthString(value) {
    if (value === void (0)) {
      return '';
    }
    const length = value.value;
    let o1 = '';
    switch (value.unit) {
      case LengthUnit.PX:
        o1 = `${length}px`;
        break;
      case LengthUnit.FP:
        o1 = `${length}fp`;
        break;
      case LengthUnit.LPX:
        o1 = `${length}lpx`;
        break;
      case LengthUnit.PERCENT:
        o1 = `${length * 100}%`;
        break;
      case LengthUnit.VP:
        o1 = `${length}vp`;
        break;
      default:
        o1 = `${length}vp`;
        break;
    }
    return o1;
  }

  clickEventAction(index) {
    let n1 = this.toolBarList[index];
    if (n1.state === ItemState.ACTIVATE) {
      if (this.activateIndex === index) {
        this.activateIndex = -1;
      }
      else {
        this.activateIndex = index;
      }
    }
    if (!(n1.state === ItemState.DISABLE)) {
      n1.action && n1.action();
    }
  }

  getItemGestureModifier(item, index) {
    let m1 = new h1(null);
    if (item?.icon || item?.toolBarSymbolOptions?.activated || item?.toolBarSymbolOptions?.normal) {
      m1 = new h1(new CustomDialogController({
        builder: () => {
          let jsDialog = new i1(this, {
            itemDialog: item,
            fontSize: this.fontSize,
            itemSymbolModifier: this.getToolBarSymbolModifier(index),
          }, undefined, -1, () => {
          },
            { page: 'toolbar/src/main/ets/components/MainPage.ets', line: 430, e2: 18 });
          jsDialog.setController();
          ViewPU.create(jsDialog);
          let paramsLambda = () => {
            return {
              itemDialog: item,
              fontSize: this.fontSize,
              itemSymbolModifier: this.getToolBarSymbolModifier(index)
            };
          };
          jsDialog.paramsGenerator_ = paramsLambda;
        },
        maskColor: Color.Transparent,
        isModal: true,
        customStyle: true
      }, this));
      m1.fontSize = this.fontSize;
    }
    return m1;
  }
  refreshData() {
    this.dividerModifier = this.dividerModifier ? this.dividerModifier : new DividerModifier();
    this.toolBarModifier = this.toolBarModifier ? this.toolBarModifier : new ToolBarModifier()
      .padding(LengthMetrics.resource({
        'id': -1,
        'type': 10002,
        params: ['sys.float.padding_level12'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
      }))
      .stateEffect(true)
      .height(LengthMetrics.vp(o))
      .backgroundColor('sys.color.ohos_id_color_toolbar_bg');
    this.menuContent = [];
    for (let h2 = 0; h2 < this.toolBarList.length; h2++) {
      if (h2 >= this.moreIndex && this.toolBarList.length > t) {
        this.menuContent[h2 - this.moreIndex] = {
          value: this.toolBarList[h2].content,
          action: this.toolBarList[h2].action ? this.toolBarList[h2].action : () => {
          },
          enabled: this.toolBarList[h2].state !== ItemState.DISABLE,
        };
      }
      else {
        this.menuContent = [];
      }
      this.toolBarItemBackground[h2] = this.toolBarItemBackground[h2] ?? Color.Transparent;
    }
    return true;
  }

  onMeasureSize(selfLayoutInfo, children, constraint) {
    this.fontSize = this.getFontSizeScale();
    let j1 = { height: 0, width: 0 };
    children.forEach((child) => {
      let k1 = child.measure(constraint);
      j1.width = k1.width;
      j1.height = k1.height;
    });
    return j1;
  }
  aboutToAppear() {
    this.refreshData();
    try {
      this.isFollowSystem = this.getUIContext()?.isFollowingSystemFontScale();
      this.maxFontSizeScale = this.getUIContext()?.getMaxFontScale();
    } catch (err) {
      let code = err?.code;
      let message = err?.message;
      hilog.error(0x3900, 'Ace', `Faild to toolBar getMaxFontScale, code: ${code}, message: ${message}`);
    }
  }
  initialRender() {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Column.create();
      Column.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.toolBarModifier));
    }, Column);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Tabs.create({ controller: this.controller });
      Tabs.visibility(Visibility.None);
    }, Tabs);
    Tabs.pop();
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Divider.create();
      Divider.width('100%');
      Divider.height(1);
      Divider.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.dividerModifier));
    }, Divider);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Row.create();
      Row.justifyContent(FlexAlign.Center);
      Row.constraintSize({
        minHeight: this.toLengthString(this.toolBarModifier?.c2),
        maxHeight: this.toLengthString(this.toolBarModifier?.c2),
      });
      Row.width('100%');
      Row.height(this.toLengthString(this.toolBarModifier?.c2));
      Row.padding({
        start: this.toolBarList.length < t ?
          this.toolBarModifier?.paddingValue : LengthMetrics.resource({
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level0'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__'
        }),
        end: this.toolBarList.length < t ?
          this.toolBarModifier?.paddingValue : LengthMetrics.resource({
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level0'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__'
        }),
      });
    }, Row);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      ForEach.create();
      const forEachItemGenFunction = (_item, index) => {
        const item = _item;
        this.observeComponentCreation2((elmtId, isInitialRender) => {
          If.create();
          if (this.toolBarList.length <= t || index < this.moreIndex) {
            this.ifElseBranchUpdateFunction(0, () => {
              this.observeComponentCreation2((elmtId, isInitialRender) => {
                Row.create();
                Row.height('100%');
                Row.flexShrink(1);
              }, Row);
              this.TabBuilder.bind(this)(index);
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
      this.forEachUpdateFunction(elmtId, this.toolBarList, forEachItemGenFunction, (item, index) => {
        return `${this.getUniqueId()}__${index}}`;
      }, true, true);
    }, ForEach);
    ForEach.pop();
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.refreshData() && this.toolBarList.length > t) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
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

class i1 extends ViewPU {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
    super(parent, __localStorage, elmtId, extraInfo);
    if (typeof paramsLambda === 'function') {
      this.paramsGenerator_ = paramsLambda;
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
    this.__fontSize = new SynchedPropertySimpleOneWayPU(params.fontSize, this, 'fontSize');
    this.__maxLines = new ObservedPropertySimplePU(1, this, 'maxLines');
    this.__windowStandardHeight = this.createStorageProp('windowStandardHeight', 0, 'windowStandardHeight');
    this.__symbolEffect = new ObservedPropertyObjectPU(new SymbolEffect(), this, 'symbolEffect');
    this.setInitiallyProvidedValue(params);
    this.finalizeConstruction();
  }

  setInitiallyProvidedValue(params) {
    if (params.itemDialog !== undefined) {
      this.itemDialog = params.itemDialog;
    }
    if (params.itemSymbolModifier !== undefined) {
      this.itemSymbolModifier = params.itemSymbolModifier;
    }
    if (params.mainWindowStage !== undefined) {
      this.mainWindowStage = params.mainWindowStage;
    }
    if (params.controller !== undefined) {
      this.controller = params.controller;
    }
    if (params.screenWidth !== undefined) {
      this.screenWidth = params.screenWidth;
    }
    if (params.verticalScreenLines !== undefined) {
      this.verticalScreenLines = params.verticalScreenLines;
    }
    if (params.horizontalsScreenLines !== undefined) {
      this.horizontalsScreenLines = params.horizontalsScreenLines;
    }
    if (params.cancel !== undefined) {
      this.cancel = params.cancel;
    }
    if (params.confirm !== undefined) {
      this.confirm = params.confirm;
    }
    if (params.fontSize === undefined) {
      this.__fontSize.set(1);
    }
    if (params.maxLines !== undefined) {
      this.maxLines = params.maxLines;
    }
    if (params.symbolEffect !== undefined) {
      this.symbolEffect = params.symbolEffect;
    }
  }

  updateStateVars(params) {
    this.__fontSize.reset(params.fontSize);
  }

  purgeVariableDependenciesOnElmtId(rmElmtId) {
    this.__mainWindow.purgeDependencyOnElmtId(rmElmtId);
    this.__fontSize.purgeDependencyOnElmtId(rmElmtId);
    this.__maxLines.purgeDependencyOnElmtId(rmElmtId);
    this.__windowStandardHeight.purgeDependencyOnElmtId(rmElmtId);
    this.__symbolEffect.purgeDependencyOnElmtId(rmElmtId);
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

  setController(ctr) {
    this.controller = ctr;
  }
  get mainWindow() {
    return this.__mainWindow.get();
  }

  set mainWindow(newValue) {
    this.__mainWindow.set(newValue);
  }
  get fontSize() {
    return this.__fontSize.get();
  }

  set fontSize(newValue) {
    this.__fontSize.set(newValue);
  }
  get maxLines() {
    return this.__maxLines.get();
  }

  set maxLines(newValue) {
    this.__maxLines.set(newValue);
  }
  get windowStandardHeight() {
    return this.__windowStandardHeight.get();
  }

  set windowStandardHeight(newValue) {
    this.__windowStandardHeight.set(newValue);
  }
  get symbolEffect() {
    return this.__symbolEffect.get();
  }

  set symbolEffect(newValue) {
    this.__symbolEffect.set(newValue);
  }
  initialRender() {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.itemDialog.content) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.width(this.fontSize === u ? b1 : c1);
            Column.constraintSize({ minHeight: this.fontSize === u ? b1 : c1 });
            Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
            Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
            Column.borderRadius(({
              'id': -1,
              'type': 10002,
              params: ['sys.float.corner_radius_level10'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__'
            }));
          }, Column);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.itemDialog.toolBarSymbolOptions?.normal ||
              this.itemDialog.toolBarSymbolOptions?.activated) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                  SymbolGlyph.create();
                  SymbolGlyph.attributeModifier.bind(this)(this.itemSymbolModifier);
                  SymbolGlyph.symbolEffect(ObservedObject.GetRawObject(this.symbolEffect), false);
                  SymbolGlyph.fontColor([{
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.icon_primary'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                  }]);
                  SymbolGlyph.fontSize(a1);
                  SymbolGlyph.margin({
                    top: {
                      'id': -1,
                      'type': 10002,
                      params: ['sys.float.padding_level24'],
                      'bundleName': '__harDefaultBundleName__',
                      'moduleName': '__harDefaultModuleName__'
                    },
                    bottom: {
                      'id': -1,
                      'type': 10002,
                      params: ['sys.float.padding_level8'],
                      'bundleName': '__harDefaultBundleName__',
                      'moduleName': '__harDefaultModuleName__'
                    },
                  });
                }, SymbolGlyph);
              });
            } else if (Util.z1(this.itemDialog.icon)) {
              this.ifElseBranchUpdateFunction(1, () => {
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                  SymbolGlyph.create(this.itemDialog?.icon);
                  SymbolGlyph.fontColor([{
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.icon_primary'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                  }]);
                  SymbolGlyph.fontSize(a1);
                  SymbolGlyph.margin({
                    top: {
                      'id': -1,
                      'type': 10002,
                      params: ['sys.float.padding_level24'],
                      'bundleName': '__harDefaultBundleName__',
                      'moduleName': '__harDefaultModuleName__'
                    },
                    bottom: {
                      'id': -1,
                      'type': 10002,
                      params: ['sys.float.padding_level8'],
                      'bundleName': '__harDefaultBundleName__',
                      'moduleName': '__harDefaultModuleName__'
                    },
                  });
                }, SymbolGlyph);
              });
            } else {
              this.ifElseBranchUpdateFunction(2, () => {
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                  Image.create(this.itemDialog.icon);
                  Image.width(a1);
                  Image.height(a1);
                  Image.margin({
                    top: {
                      'id': -1,
                      'type': 10002,
                      params: ['sys.float.padding_level24'],
                      'bundleName': '__harDefaultBundleName__',
                      'moduleName': '__harDefaultModuleName__'
                    },
                    bottom: {
                      'id': -1,
                      'type': 10002,
                      params: ['sys.float.padding_level8'],
                      'bundleName': '__harDefaultBundleName__',
                      'moduleName': '__harDefaultModuleName__'
                    },
                  });
                  Image.fillColor({
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.icon_primary'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                  });
                }, Image);
              });
            }
          }, If);
          If.pop();
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.width('100%');
            Column.padding({
              left: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level4'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
              },
              right: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level4'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
              },
              bottom: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level12'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
              },
            });
          }, Column);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.itemDialog.content);
            Text.fontSize(d1);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.maxLines(this.maxLines);
            Text.width('100%');
            Text.textAlign(TextAlign.Center);
            Text.fontColor({
              'id': -1,
              'type': 10001,
              params: ['sys.color.font_primary'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__'
            });
          }, Text);
          Text.pop();
          Column.pop();
          Column.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.width(this.fontSize === u ? b1 : c1);
            Column.constraintSize({ minHeight: this.fontSize === u ? b1 : c1 });
            Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
            Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
            Column.borderRadius(({
              'id': -1,
              'type': 10002,
              params: ['sys.float.corner_radius_level10'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__'
            }));
            Column.justifyContent(FlexAlign.Center);
          }, Column);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.itemDialog.toolBarSymbolOptions?.normal ||
              this.itemDialog.toolBarSymbolOptions?.activated) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                  SymbolGlyph.create();
                  SymbolGlyph.attributeModifier.bind(this)(this.itemSymbolModifier);
                  SymbolGlyph.symbolEffect(ObservedObject.GetRawObject(this.symbolEffect), false);
                  SymbolGlyph.fontColor([{
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.icon_primary'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                  }]);
                  SymbolGlyph.fontSize(a1);
                }, SymbolGlyph);
              });
            } else if (Util.z1(this.itemDialog.icon)) {
              this.ifElseBranchUpdateFunction(1, () => {
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                  SymbolGlyph.create(this.itemDialog?.icon);
                  SymbolGlyph.fontColor([{
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.icon_primary'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                  }]);
                  SymbolGlyph.fontSize(a1);
                }, SymbolGlyph);
              });
            }
            else {
              this.ifElseBranchUpdateFunction(2, () => {
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                  Image.create(this.itemDialog.icon);
                  Image.width(a1);
                  Image.height(a1);
                  Image.fillColor({
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.icon_primary'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                  });
                }, Image);
              });
            }
          }, If);
          If.pop();
          Column.pop();
        });
      }
    }, If);
    If.pop();
  }
  async aboutToAppear() {
    let context = this.getUIContext().getHostContext();
    this.mainWindowStage = context.windowStage.getMainWindowSync();
    let properties = this.mainWindowStage.getWindowProperties();
    let rect = properties.windowRect;
    if (px2vp(rect.height) > this.screenWidth) {
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