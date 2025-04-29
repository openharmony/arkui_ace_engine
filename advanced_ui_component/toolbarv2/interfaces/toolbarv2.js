/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

let __decorate = (this && this.__decorate) || function (t1, target, key, desc) {
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
const promptAction = requireNapi('promptAction');

export let ToolBarV2ItemState;
(function (ToolBarV2ItemState) {
  ToolBarV2ItemState[ToolBarV2ItemState.ENABLE = 1] = 'ENABLE';
  ToolBarV2ItemState[ToolBarV2ItemState.DISABLE = 2] = 'DISABLE';
  ToolBarV2ItemState[ToolBarV2ItemState.ACTIVATE = 3] = 'ACTIVATE';
})(ToolBarV2ItemState || (ToolBarV2ItemState = {}));
const j = {
  'id': -1, 'type': 40000,
  params: ['sys.symbol.dot_grid_2x2'],
  'bundleName': '__harDefaultBundleName__',
  'moduleName': '__harDefaultModuleName__' };
const m = '24vp';
const o = 56;
const t = 5;
const u = 3.2;
const a1 = '64vp';
const b1 = '256vp';
const c1 = '216vp';
const d1 = '18.3fp';
const e1 = 640;
const f1 = 6;
const g1 = 1;
const h1 = -2;
const i1 = 2;
const j1 = 40000;
class Util {
  static b2(v1) {
    if (!Util.c2(v1)) {
      return false;
    }
    let resource = v1;
    return resource.type === j1;
  }
  static c2(resource) {
    if (!resource) {
      return false;
    }
    if (typeof resource === 'string' || typeof resource === 'undefined') {
      return false;
    }
    return true;
  }
}
let ToolBarV2SymbolGlyph = class ToolBarV2SymbolGlyph {
  constructor(options) {
    this.normal = options.normal;
    this.activated = options.activated;
  }
};
__decorate([
  Trace
], ToolBarV2SymbolGlyph.prototype, 'normal', void 0);
__decorate([
  Trace
], ToolBarV2SymbolGlyph.prototype, 'activated', void 0);
ToolBarV2SymbolGlyph = __decorate([
  ObservedV2
], ToolBarV2SymbolGlyph);
export { ToolBarV2SymbolGlyph };
class ButtonGestureModifier {
  constructor() {
    this.d2 = undefined;
  }
  applyGesture(event) {
    this.d2?.(event);
  }
}
ButtonGestureModifier.e2 = 500;
ButtonGestureModifier.minFontSize = 1.75;
let ToolBarV2ItemText = class ToolBarV2ItemText {
  constructor(options) {
    this.color = ColorMetrics.resourceColor({
      'id': -1,
      'type': 10001,
      params: ['sys.color.font_primary'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__' });
    this.activatedColor = ColorMetrics.resourceColor({
      'id': -1,
      'type': 10001,
      params: ['sys.color.font_emphasize'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__' });
    this.text = options.text;
    this.color = options.color;
    this.activatedColor = options.activatedColor;
  }
};
__decorate([
  Trace
], ToolBarV2ItemText.prototype, 'text', void 0);
__decorate([
  Trace
], ToolBarV2ItemText.prototype, 'color', void 0);
__decorate([
  Trace
], ToolBarV2ItemText.prototype, 'activatedColor', void 0);
ToolBarV2ItemText = __decorate([
  ObservedV2
], ToolBarV2ItemText);
export { ToolBarV2ItemText };
let ToolBarV2ItemImage = class ToolBarV2ItemImage {
  constructor(options) {
    this.color = undefined;
    this.activatedColor = undefined;
    this.src = options.src;
    this.color = options.color;
    this.activatedColor = options.activatedColor;
  }
};
__decorate([
  Trace
], ToolBarV2ItemImage.prototype, 'src', void 0);
__decorate([
  Trace
], ToolBarV2ItemImage.prototype, 'color', void 0);
__decorate([
  Trace
], ToolBarV2ItemImage.prototype, 'activatedColor', void 0);
ToolBarV2ItemImage = __decorate([
  ObservedV2
], ToolBarV2ItemImage);
export { ToolBarV2ItemImage };
let ToolBarV2Item = class ToolBarV2Item {
  constructor(options) {
    this.content = new ToolBarV2ItemText({ text: '' });
    this.action = undefined;
    this.icon = undefined;
    this.state = 1;
    this.accessibilityText = '';
    this.accessibilityDescription = '';
    this.accessibilityLevel = 'auto';
    this.backgroundColor = Color.Transparent;
    this.content = options.content;
    this.action = options.action;
    this.icon = options.icon;
    this.state = options.state;
    this.accessibilityText = options.accessibilityText;
    this.accessibilityDescription = options.accessibilityDescription;
    this.accessibilityLevel = options.accessibilityLevel;
  }
  get symbol() {
    if (this.icon instanceof ToolBarV2SymbolGlyph) {
      return this.icon;
    }
    return undefined;
  }
  get image() {
    if (!(this.icon instanceof ToolBarV2SymbolGlyph)) {
      return this.icon;
    }
    return undefined;
  }
};
__decorate([
  Trace
], ToolBarV2Item.prototype, 'content', void 0);
__decorate([
  Trace
], ToolBarV2Item.prototype, 'action', void 0);
__decorate([
  Trace
], ToolBarV2Item.prototype, 'icon', void 0);
__decorate([
  Trace
], ToolBarV2Item.prototype, 'state', void 0);
__decorate([
  Trace
], ToolBarV2Item.prototype, 'accessibilityText', void 0);
__decorate([
  Trace
], ToolBarV2Item.prototype, 'accessibilityDescription', void 0);
__decorate([
  Trace
], ToolBarV2Item.prototype, 'accessibilityLevel', void 0);
__decorate([
  Trace
], ToolBarV2Item.prototype, 'backgroundColor', void 0);
__decorate([
  Computed
], ToolBarV2Item.prototype, 'symbol', null);
__decorate([
  Computed
], ToolBarV2Item.prototype, 'image', null);
ToolBarV2Item = __decorate([
  ObservedV2
], ToolBarV2Item);
export { ToolBarV2Item };
let ToolBarV2Modifier = class ToolBarV2Modifier {
  constructor() {
    this.f2 = {
      'id': -1,
      'type': 10001,
      params: ['sys.color.ohos_id_color_toolbar_bg'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__' };
    this.g2 = LengthMetrics.vp(o);
    this.h2 = true;
    this.paddingValue = LengthMetrics.resource({
      'id': -1,
      'type': 10002,
      params: ['sys.float.padding_level12'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__' });
  }
  applyNormalAttribute(instance) {
    instance.backgroundColor(this.f2);
  }
  backgroundColor(backgroundColor) {
    this.f2 = backgroundColor.color;
    return this;
  }
  height(height) {
    this.g2 = height;
    return this;
  }
  stateEffect(stateEffect) {
    this.h2 = stateEffect;
    return this;
  }
  padding(padding) {
    this.paddingValue = padding;
    return this;
  }
};
__decorate([
  Trace
], ToolBarV2Modifier.prototype, 'backgroundColorValue', void 0);
__decorate([
  Trace
], ToolBarV2Modifier.prototype, 'heightValue', void 0);
__decorate([
  Trace
], ToolBarV2Modifier.prototype, 'stateEffectValue', void 0);
__decorate([
  Trace
], ToolBarV2Modifier.prototype, 'paddingValue', void 0);
ToolBarV2Modifier = __decorate([
  ObservedV2
], ToolBarV2Modifier);
export { ToolBarV2Modifier };
let ToolBarV2Theme = class ToolBarV2Theme {
  constructor() {
    this.i2 = {
      'id': -1,
      'type': 10001,
      params: ['sys.color.icon_primary'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__' };
    this.j2 = {
      'id': -1,
      'type': 10001,
      params: ['sys.color.icon_emphasize'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__' };
    this.l2 = {
      'id': -1,
      'type': 10001,
      params: ['sys.color.font_primary'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__' };
    this.m2 = {
      'id': -1,
      'type': 10001,
      params: ['sys.color.font_emphasize'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__' };
  }
};
__decorate([
  Trace
], ToolBarV2Theme.prototype, 'iconPrimaryColor', void 0);
__decorate([
  Trace
], ToolBarV2Theme.prototype, 'iconActivePrimaryColor', void 0);
__decorate([
  Trace
], ToolBarV2Theme.prototype, 'fontPrimaryColor', void 0);
__decorate([
  Trace
], ToolBarV2Theme.prototype, 'fontActivatedPrimaryColor', void 0);
ToolBarV2Theme = __decorate([
  ObservedV2
], ToolBarV2Theme);
export class ToolBarV2 extends ViewV2 {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
    super(parent, elmtId, extraInfo);
    this.initParam('toolBarList', (params && 'toolBarList' in params) ? params.toolBarList : undefined);
    this.initParam('activatedIndex', (params && 'activatedIndex' in params) ? params.activatedIndex : -1);
    this.initParam('dividerModifier',
      (params && 'dividerModifier' in params) ? params.dividerModifier : new DividerModifier());
    this.initParam('toolBarModifier',
      (params && 'toolBarModifier' in params) ? params.toolBarModifier : new ToolBarV2Modifier()
        .padding(LengthMetrics.resource({
          'id': -1, 'type': 10002,
          params: ['sys.float.padding_level12'],
          'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }))
        .stateEffect(true)
        .height(LengthMetrics.vp(o))
        .backgroundColor(ColorMetrics.resourceColor({
          'id': -1, 'type': 10001,
          params: ['sys.color.ohos_id_color_toolbar_bg'],
          'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' })));
    this.localActivatedIndex = -1;
    this.menuContent = [];
    this.fontSize = 1;
    this.theme = new ToolBarV2Theme();
    this.itemCardTextMaxLine = 1;
    this.itemDialogId = undefined;
    this.isFollowSystem = false;
    this.maxFontSizeScale = 3.2;
    this.moreItem = new ToolBarV2Item({
      content: new ToolBarV2ItemText({
        text: {
          'id': -1,
          'type': 10003,
          params: ['sys.string.ohos_toolbar_more'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__' },
      }),
      icon: new ToolBarV2ItemImage({
        src: j
      })
    });
    this.moreText = {
      'id': -1, 'type': 10003,
      params: ['sys.string.ohos_toolbar_more'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__' };
    this.finalizeConstruction();
  }
  n2(params) {
    this.o2('toolBarList', (params && 'toolBarList' in params) ? params.toolBarList : undefined);
    this.o2('activatedIndex', (params && 'activatedIndex' in params) ? params.activatedIndex : -1);
    this.o2('dividerModifier',
      (params && 'dividerModifier' in params) ? params.dividerModifier : new DividerModifier());
    this.o2('toolBarModifier',
      (params && 'toolBarModifier' in params) ? params.toolBarModifier : new ToolBarV2Modifier()
        .padding(LengthMetrics.resource({
          'id': -1, 'type': 10002,
          params: ['sys.float.padding_level12'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__' }))
        .stateEffect(true)
        .height(LengthMetrics.vp(o))
        .backgroundColor(ColorMetrics.resourceColor({
          'id': -1, 'type': 10001,
          params: ['sys.color.ohos_id_color_toolbar_bg'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__' })));
    this.localActivatedIndex = -1;
    this.menuContent = [];
    this.fontSize = 1;
    this.theme = new ToolBarV2Theme();
    this.q2('menus');
    this.s2();
  }
  onActivateIndexChange(monitor) {
    this.localActivatedIndex = monitor.value('activatedIndex')?.now ?? -1;
  }
  get menus() {
    this.menuContent = [];
    this.toolBarList.forEach((value, index) => {
      if (index >= t - 1) {
        this.menuContent.push({
          value: this.toolBarList[index].content.text,
          action: () => {
            let callback = this.toolBarList[index].action;
            if (callback) {
              callback(index);
            }
          },
          enabled: this.toolBarList[index].state !== ToolBarV2ItemState.DISABLE,
        });
      }
    });
    return this.menuContent;
  }
  aboutToAppear() {
    this.localActivatedIndex = this.activatedIndex ?? -1;
    try {
      this.isFollowSystem = this.getUIContext()?.isFollowingSystemFontScale();
      this.maxFontSizeScale = this.getUIContext()?.getMaxFontScale();
    }
    catch (err) {
      let code = err?.code;
      let message = err?.message;
      hilog.error(0x3900, 'Ace', `Faild to toolBarV2 getMaxFontScale, code: ${code}, message: ${message}`);
    }
  }
  onWillApplyTheme(theme) {
    this.theme.i2 = theme.colors.iconPrimary;
    this.theme.j2 = theme.colors.iconEmphasize;
    this.theme.l2 = theme.colors.fontPrimary;
    this.theme.m2 = theme.colors.fontEmphasize;
  }
  MoreTabBuilder(index, parent = null) {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
      Button.accessibilityGroup(true);
      Button.focusable(true);
      Button.focusOnTouch(true);
      Button.focusBox({
        margin: LengthMetrics.vp(h1),
        strokeWidth: LengthMetrics.vp(i1),
        strokeColor: ColorMetrics.resourceColor({
          'id': -1,
          'type': 10001,
          params: ['sys.color.ohos_id_color_focused_outline'],
          'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' })
      });
      Button.width('100%');
      Button.height('100%');
      Button.bindMenu(this.menuContent, { placement: Placement.TopRight, offset: { x: -12, y: -10 } });
      Button.borderRadius({
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_corner_radius_clicked'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
      Button.backgroundColor(this.toolBarList[index].backgroundColor);
      Button.onHover((isHover) => {
        if (isHover) {
          this.toolBarList[index].backgroundColor = {
            'id': -1, 'type': 10001,
            params: ['sys.color.ohos_id_color_hover'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__' };
        }
        else {
          this.toolBarList[index].backgroundColor = Color.Transparent;
        }
      });
      ViewStackProcessor.visualState('pressed');
      Button.backgroundColor((!this.toolBarModifier?.h2) ?
      this.toolBarList[index].backgroundColor : {
          'id': -1,
          'type': 10001,
          params: ['sys.color.ohos_id_color_click_effect'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__' });
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
          'moduleName': '__harDefaultModuleName__' }),
        end: LengthMetrics.resource({
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level2'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__' }),
      });
      Column.borderRadius({
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_corner_radius_clicked'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__' });
    }, Column);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      SymbolGlyph.create(j);
      SymbolGlyph.fontSize(m);
      SymbolGlyph.fontColor([this.theme.i2]);
      SymbolGlyph.draggable(false);
      SymbolGlyph.margin({ bottom: {
        'id': -1,
        'type': 10002,
        params: ['sys.float.padding_level1'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__' } });
    }, SymbolGlyph);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Text.create(this.moreText);
      Text.fontColor(this.theme.l2);
      Text.fontSize({
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_text_size_caption'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__' });
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
      Button.accessibilityText(this.toolBarList[index]?.accessibilityText ??
        this.toolBarList[index]?.content?.text);
      Button.accessibilityDescription(this.toolBarList[index]?.accessibilityDescription ?? '');
      Button.accessibilityLevel(this.toolBarList[index]?.accessibilityLevel ?? 'auto');
      Button.enabled(this.toolBarList[index]?.state !== ToolBarV2ItemState.DISABLE);
      Button.width('100%');
      Button.height('100%');
      Button.borderRadius({
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_corner_radius_clicked'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__' });
      Button.focusable(!(this.toolBarList[index]?.state === ToolBarV2ItemState.DISABLE));
      Button.focusOnTouch(!(this.toolBarList[index]?.state === ToolBarV2ItemState.DISABLE));
      Button.focusBox({
        margin: LengthMetrics.vp(h1),
        strokeWidth: LengthMetrics.vp(i1),
        strokeColor: ColorMetrics.resourceColor({
          'id': -1,
          'type': 10001,
          params: ['sys.color.ohos_id_color_focused_outline'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__' })
      });
      Button.backgroundColor(this.toolBarList[index].backgroundColor);
      Button.onHover((isHover) => {
        if (isHover && this.toolBarList[index]?.state !== ToolBarV2ItemState.DISABLE) {
          this.toolBarList[index].backgroundColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_hover'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__' };
        }
        else {
          this.toolBarList[index].backgroundColor = Color.Transparent;
        }
      });
      ViewStackProcessor.visualState('pressed');
      Button.backgroundColor((this.toolBarList[index]?.state === ToolBarV2ItemState.DISABLE) ||
        (!this.toolBarModifier?.h2) ?
      this.toolBarList[index].backgroundColor : {
          'id': -1,
          'type': 10001,
          params: ['sys.color.ohos_id_color_click_effect'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__' });
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
        'moduleName': '__harDefaultModuleName__' });
      Column.padding({
        start: LengthMetrics.resource({
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level2'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__' }),
        end: LengthMetrics.resource({
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level2'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__' }),
      });
    }, Column);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.toolBarList[index]?.symbol) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            SymbolGlyph.create();
            SymbolGlyph.fontSize(m);
            SymbolGlyph.symbolEffect(new SymbolEffect(), false);
            SymbolGlyph.attributeModifier.bind(this)(this.getToolBarSymbolModifier(index));
            SymbolGlyph.margin({ bottom: {
              'id': -1,
              'type': 10002,
              params: ['sys.float.padding_level1'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__' } });
          }, SymbolGlyph);
        });
      }
      else if (Util.b2(this.toolBarList[index]?.image?.src)) {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            SymbolGlyph.create(this.toolBarList[index]?.image?.src);
            SymbolGlyph.fontSize(m);
            SymbolGlyph.fontColor([this.getIconColor(index)]);
            SymbolGlyph.margin({ bottom: {
              'id': -1,
              'type': 10002,
              params: ['sys.float.padding_level1'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__' } });
          }, SymbolGlyph);
        });
      }
      else {
        this.ifElseBranchUpdateFunction(2, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(this.toolBarList[index]?.image?.src);
            Image.width(m);
            Image.height(m);
            Image.fillColor(this.getIconColor(index));
            Image.margin({ bottom: {
              'id': -1,
              'type': 10002,
              params: ['sys.float.padding_level1'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__' } });
            Image.objectFit(ImageFit.Contain);
            Image.draggable(false);
          }, Image);
        });
      }
    }, If);
    If.pop();
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Text.create(this.toolBarList[index]?.content.text);
      Text.fontColor(this.getTextColor(index));
      Text.fontSize({
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_text_size_caption'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__' });
      Text.maxFontSize({
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_text_size_caption'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__' });
      Text.minFontSize(9);
      Text.fontWeight(FontWeight.Medium);
      Text.maxLines(1);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.textAlign(TextAlign.Center);
      Text.focusable(!(this.toolBarList[index]?.state === ToolBarV2ItemState.DISABLE));
      Text.focusOnTouch(!(this.toolBarList[index]?.state === ToolBarV2ItemState.DISABLE));
    }, Text);
    Text.pop();
    Column.pop();
    Button.pop();
  }
  itemCardDialogBuilder(item, index, parent = null) {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (item.content && item.content.text) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.constraintSize({ minHeight: this.fontSize === u ? b1 : c1 });
          }, Column);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (item.symbol) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                  SymbolGlyph.create();
                  SymbolGlyph.attributeModifier.bind(this)(this.getToolBarSymbolModifier(index));
                  SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                  SymbolGlyph.fontColor([{
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.icon_primary'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__' }]);
                  SymbolGlyph.fontSize(a1);
                  SymbolGlyph.margin({
                    top: {
                      'id': -1,
                      'type': 10002,
                      params: ['sys.float.padding_level24'],
                      'bundleName': '__harDefaultBundleName__',
                      'moduleName': '__harDefaultModuleName__' },
                    bottom: {
                      'id': -1,
                      'type': 10002,
                      params: ['sys.float.padding_level8'],
                      'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                  });
                }, SymbolGlyph);
              });
            }
            else if (Util.b2(item.image?.src)) {
              this.ifElseBranchUpdateFunction(1, () => {
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                  SymbolGlyph.create(item.image?.src);
                  SymbolGlyph.fontColor([{
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.icon_primary'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__' }]);
                  SymbolGlyph.fontSize(a1);
                  SymbolGlyph.margin({
                    top: {
                      'id': -1,
                      'type': 10002,
                      params: ['sys.float.padding_level24'],
                      'bundleName': '__harDefaultBundleName__',
                      'moduleName': '__harDefaultModuleName__' },
                    bottom: {
                      'id': -1,
                      'type': 10002,
                      params: ['sys.float.padding_level8'],
                      'bundleName': '__harDefaultBundleName__',
                      'moduleName': '__harDefaultModuleName__' },
                  });
                }, SymbolGlyph);
              });
            }
            else {
              this.ifElseBranchUpdateFunction(2, () => {
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                  Image.create(item.image?.src);
                  Image.width(a1);
                  Image.height(a1);
                  Image.margin({
                    top: {
                      'id': -1,
                      'type': 10002,
                      params: ['sys.float.padding_level24'],
                      'bundleName': '__harDefaultBundleName__',
                      'moduleName': '__harDefaultModuleName__' },
                    bottom: {
                      'id': -1,
                      'type': 10002,
                      params: ['sys.float.padding_level8'],
                      'bundleName': '__harDefaultBundleName__',
                      'moduleName': '__harDefaultModuleName__' },
                  });
                  Image.fillColor({
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.icon_primary'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__' });
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
                'moduleName': '__harDefaultModuleName__' },
              right: {
                'id': -1, 'type': 10002,
                params: ['sys.float.padding_level4'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__' },
              bottom: {
                'id': -1, 'type': 10002,
                params: ['sys.float.padding_level12'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__' },
            });
          }, Column);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(item.content.text);
            Text.fontSize(d1);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.maxLines(this.itemCardTextMaxLine);
            Text.width('100%');
            Text.textAlign(TextAlign.Center);
            Text.fontColor({
              'id': -1, 'type': 10001,
              params: ['sys.color.font_primary'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__' });
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
            Column.constraintSize({ minHeight: this.fontSize === u ? b1 : c1 });
            Column.justifyContent(FlexAlign.Center);
          }, Column);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (item.symbol) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                  SymbolGlyph.create();
                  SymbolGlyph.attributeModifier.bind(this)(this.getToolBarSymbolModifier(index));
                  SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                  SymbolGlyph.fontColor([{
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.icon_primary'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__' }]);
                  SymbolGlyph.fontSize(a1);
                }, SymbolGlyph);
              });
            }
            else {
              this.ifElseBranchUpdateFunction(1, () => {
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                  Image.create(item.image?.src);
                  Image.width(a1);
                  Image.height(a1);
                  Image.fillColor({
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.icon_primary'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__' });
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
  getFontSizeScale() {
    let context = this.getUIContext();
    let u1 = context.getHostContext()?.config?.fontSizeScale ?? 1;
    if (!this.isFollowSystem) {
      return 1;
    }
    else {
      return Math.min(u1, this.maxFontSizeScale);
    }
  }
  isItemActivating(index) {
    return this.localActivatedIndex === index && (this.toolBarList[index]?.state === ToolBarV2ItemState.ACTIVATE);
  }
  getToolBarSymbolModifier(index) {
    if (this.isItemActivating(index)) {
      return this.toolBarList[index]?.symbol?.activated;
    }
    return this.toolBarList[index]?.symbol?.normal;
  }
  getIconColor(index) {
    if (this.isItemActivating(index)) {
      return this.toolBarList[index]?.image?.activatedColor?.color ?? this.theme.j2;
    }
    return this.toolBarList[index]?.image?.color?.color ?? this.theme.i2;
  }
  getTextColor(index) {
    if (this.isItemActivating(index)) {
      return this.toolBarList[index]?.content.activatedColor?.color ?? this.theme.m2;
    }
    return this.toolBarList[index]?.content.color?.color ?? this.theme.l2;
  }
  toLengthString(value) {
    if (value === undefined) {
      return '';
    }
    const length = value.value;
    let t1 = '';
    switch (value.unit) {
      case LengthUnit.PX:
        t1 = `${length}px`;
        break;
      case LengthUnit.FP:
        t1 = `${length}fp`;
        break;
      case LengthUnit.LPX:
        t1 = `${length}lpx`;
        break;
      case LengthUnit.PERCENT:
        t1 = `${length * 100}%`;
        break;
      case LengthUnit.VP:
        t1 = `${length}vp`;
        break;
      default:
        t1 = `${length}vp`;
        break;
    }
    return t1;
  }
  clickEventAction(index) {
    let s1 = this.toolBarList[index];
    if (s1.state === ToolBarV2ItemState.ACTIVATE) {
      if (this.localActivatedIndex === index) {
        this.localActivatedIndex = -1;
      }
      else {
        this.localActivatedIndex = index;
      }
    }
    if (s1.state !== ToolBarV2ItemState.DISABLE) {
      s1.action && s1.action(index);
    }
  }
  getItemGestureModifier(item, index) {
    if (!item?.icon) {
      return undefined;
    }
    let p1 = new ButtonGestureModifier();
    p1.d2 = (event) => {
      if (this.fontSize >= ButtonGestureModifier.minFontSize) {
        event.addGesture(new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.e2 })
          .onAction(() => {
            promptAction.openCustomDialog({
              builder: () => {
                this.itemCardDialogBuilder(item, index);
              },
              onWillAppear: () => {
                try {
                  let context = this.getUIContext().getHostContext();
                  let q1 = context.windowStage.getMainWindowSync();
                  let properties = q1.getWindowProperties();
                  if (px2vp(properties.windowRect.height) > e1) {
                    this.itemCardTextMaxLine = f1;
                  }
                  else {
                    this.itemCardTextMaxLine = g1;
                  }
                }
                catch (err) {
                  let code = err?.code;
                  let message = err?.message;
                  hilog.error(0x3900, 'Ace', `ToolBarV2 get window height failed, code: ${code}, message: ${message}`);
                }
              },
              maskColor: Color.Transparent,
              isModal: true,
              backgroundBlurStyle: BlurStyle.COMPONENT_ULTRA_THICK,
              backgroundColor: Color.Transparent,
              shadow: ShadowStyle.OUTER_DEFAULT_LG,
              cornerRadius: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.corner_radius_level10'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__' },
              width: this.fontSize === u ? b1 : c1
            }).then((dialogId) => {
              this.itemDialogId = dialogId;
            });
          })
          .onActionEnd(() => {
            if (this.itemDialogId) {
              promptAction.closeCustomDialog(this.itemDialogId);
            }
          })
          .onActionCancel(() => {
            if (this.itemDialogId) {
              promptAction.closeCustomDialog(this.itemDialogId);
            }
          }));
        return;
      }
      event.clearGestures();
    };
    return p1;
  }
  onMeasureSize(selfLayoutInfo, children, constraint) {
    this.fontSize = this.getFontSizeScale();
    let n1 = { height: 0, width: 0 };
    children.forEach((child) => {
      let o1 = child.measure(constraint);
      n1.width = o1.width;
      n1.height = o1.height;
    });
    return n1;
  }
  initialRender() {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Column.create();
      Column.attributeModifier.bind(this)(this.toolBarModifier);
    }, Column);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Divider.create();
      Divider.width('100%');
      Divider.height(1);
      Divider.attributeModifier.bind(this)(this.dividerModifier);
    }, Divider);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Row.create();
      Row.justifyContent(FlexAlign.Center);
      Row.constraintSize({
        minHeight: this.toLengthString(this.toolBarModifier?.g2),
        maxHeight: this.toLengthString(this.toolBarModifier?.g2),
      });
      Row.width('100%');
      Row.height(this.toLengthString(this.toolBarModifier?.g2));
      Row.padding({
        start: this.toolBarList.length < t ?
          this.toolBarModifier?.paddingValue : LengthMetrics.resource({
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level0'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__' }),
        end: this.toolBarList.length < t ?
          this.toolBarModifier?.paddingValue : LengthMetrics.resource({
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level0'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__' }),
      });
    }, Row);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      ForEach.create();
      const forEachItemGenFunction = (_item, index) => {
        const item = _item;
        this.observeComponentCreation2((elmtId, isInitialRender) => {
          If.create();
          if (this.toolBarList.length <= t || index < t - 1) {
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
        return `${this.getUniqueId}__${index}}`;
      }, true, true);
    }, ForEach);
    ForEach.pop();
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.toolBarList.length > t) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.height('100%');
            Row.flexShrink(1);
          }, Row);
          this.MoreTabBuilder.bind(this)(t - 1);
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
  updateStateVars(params) {
    if (params === undefined) {
      return;
    }
    if ('toolBarList' in params) {
      this.updateParam('toolBarList', params.toolBarList);
    }
    if ('activatedIndex' in params) {
      this.updateParam('activatedIndex', params.activatedIndex);
    }
    if ('dividerModifier' in params) {
      this.updateParam('dividerModifier', params.dividerModifier);
    }
    if ('toolBarModifier' in params) {
      this.updateParam('toolBarModifier', params.toolBarModifier);
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}
__decorate([
  Param
], ToolBarV2.prototype, 'toolBarList', void 0);
__decorate([
  Param
], ToolBarV2.prototype, 'activatedIndex', void 0);
__decorate([
  Param
], ToolBarV2.prototype, 'dividerModifier', void 0);
__decorate([
  Param
], ToolBarV2.prototype, 'toolBarModifier', void 0);
__decorate([
  Local
], ToolBarV2.prototype, 'localActivatedIndex', void 0);
__decorate([
  Local
], ToolBarV2.prototype, 'menuContent', void 0);
__decorate([
  Local
], ToolBarV2.prototype, 'fontSize', void 0);
__decorate([
  Local
], ToolBarV2.prototype, 'theme', void 0);
__decorate([
  Monitor('activatedIndex')
], ToolBarV2.prototype, 'onActivateIndexChange', null);
__decorate([
  Computed
], ToolBarV2.prototype, 'menus', null);
export default { ToolBarV2Item, ToolBarV2ItemImage, ToolBarV2ItemText, ToolBarV2, ToolBarV2ItemState, ToolBarV2Modifier, ToolBarV2SymbolGlyph };