/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

var w9 = (this && this.w9) || function (w28, target, key, desc) {
  var c = arguments.length,
    r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
  if (typeof Reflect === 'object' && typeof Reflect.r12 === 'function') {
    r = Reflect.r12(w28, target, key, desc);
  } else {
    for (var x28 = w28.length - 1; x28 >= 0; x28--) {
      if (d = w28[x28]) {
        r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
      }
    }
  }
  return c > 3 && r && Object.defineProperty(target, key, r), r;
};
if (!('finalizeConstruction' in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {
  });
}
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const LengthUnit = requireNapi('arkui.node').LengthUnit;
const ColorMetrics = requireNapi('arkui.node').ColorMetrics;
const DividerModifier = requireNapi('arkui.modifier').DividerModifier;
const hilog = requireNapi('hilog');
const promptAction = requireNapi('promptAction');

export var ToolBarV2ItemState;
(function (ToolBarV2ItemState) {
  ToolBarV2ItemState[ToolBarV2ItemState['ENABLE'] = 1] = 'ENABLE';
  ToolBarV2ItemState[ToolBarV2ItemState['DISABLE'] = 2] = 'DISABLE';
  ToolBarV2ItemState[ToolBarV2ItemState['ACTIVATE'] = 3] = 'ACTIVATE';
})(ToolBarV2ItemState || (ToolBarV2ItemState = {}));
const x27 = {
  'id': -1,
  'type': 40000,
  params: ['sys.symbol.dot_grid_2x2'],
  'bundleName': '__harDefaultBundleName__',
  'moduleName': '__harDefaultModuleName__'
};
const y27 = '24vp';
const z27 = 56;
const a28 = 5;
const b28 = 3.2;
const c28 = '64vp';
const d28 = '256vp';
const e28 = '216vp';
const f28 = '18.3fp';
const g28 = 640;
const h28 = 6;
const i28 = 1;
const j28 = -2;
const k28 = 2;
const l28 = 40000;

class Util {
  static y28(v28) {
    if (!Util.z28(v28)) {
      return false;
    }
    let resource = v28;
    return resource.type === l28;
  }

  static z28(resource) {
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
w9([
  Trace
], ToolBarV2SymbolGlyph.prototype, 'normal', void 0);
w9([
  Trace
], ToolBarV2SymbolGlyph.prototype, 'activated', void 0);
ToolBarV2SymbolGlyph = w9([
  ObservedV2
], ToolBarV2SymbolGlyph);

export { ToolBarV2SymbolGlyph };

class m28 {
  constructor() {
    this.a29 = undefined;
  }

  applyGesture(event) {
    this.a29?.(event);
  }
}

m28.longPressTime = 500;
m28.minFontSize = 1.75;
let ToolBarV2ItemText = class ToolBarV2ItemText {
  constructor(options) {
    this.color = ColorMetrics.resourceColor({
      'id': -1,
      'type': 10001,
      params: ['sys.color.font_primary'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__'
    });
    this.activatedColor = ColorMetrics.resourceColor({
      'id': -1,
      'type': 10001,
      params: ['sys.color.font_emphasize'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__'
    });
    this.text = options.text;
    this.color = options.color;
    this.activatedColor = options.activatedColor;
  }
};
w9([
  Trace
], ToolBarV2ItemText.prototype, 'text', void 0);
w9([
  Trace
], ToolBarV2ItemText.prototype, 'color', void 0);
w9([
  Trace
], ToolBarV2ItemText.prototype, 'activatedColor', void 0);
ToolBarV2ItemText = w9([
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
w9([
  Trace
], ToolBarV2ItemImage.prototype, 'src', void 0);
w9([
  Trace
], ToolBarV2ItemImage.prototype, 'color', void 0);
w9([
  Trace
], ToolBarV2ItemImage.prototype, 'activatedColor', void 0);
ToolBarV2ItemImage = w9([
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
w9([
  Trace
], ToolBarV2Item.prototype, 'content', void 0);
w9([
  Trace
], ToolBarV2Item.prototype, 'action', void 0);
w9([
  Trace
], ToolBarV2Item.prototype, 'icon', void 0);
w9([
  Trace
], ToolBarV2Item.prototype, 'state', void 0);
w9([
  Trace
], ToolBarV2Item.prototype, 'accessibilityText', void 0);
w9([
  Trace
], ToolBarV2Item.prototype, 'accessibilityDescription', void 0);
w9([
  Trace
], ToolBarV2Item.prototype, 'accessibilityLevel', void 0);
w9([
  Trace
], ToolBarV2Item.prototype, 'backgroundColor', void 0);
w9([
  Computed
], ToolBarV2Item.prototype, 'symbol', null);
w9([
  Computed
], ToolBarV2Item.prototype, 'image', null);
ToolBarV2Item = w9([
  ObservedV2
], ToolBarV2Item);

export { ToolBarV2Item };
let ToolBarV2Modifier = class ToolBarV2Modifier {
  constructor() {
    this.b29 = {
      'id': -1,
      'type': 10001,
      params: ['sys.color.ohos_id_color_toolbar_bg'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__'
    };
    this.heightValue = LengthMetrics.vp(z27);
    this.c29 = true;
    this.paddingValue = LengthMetrics.resource({
      'id': -1,
      'type': 10002,
      params: ['sys.float.padding_level12'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__'
    });
  }

  applyNormalAttribute(instance) {
    instance.backgroundColor(this.b29 ?? {
      'id': -1,
      'type': 10001,
      params: ['sys.color.ohos_id_color_toolbar_bg'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__'
    });
  }

  backgroundColor(backgroundColor) {
    this.b29 = backgroundColor.color;
    return this;
  }

  height(height) {
    this.heightValue = height;
    return this;
  }

  stateEffect(stateEffect) {
    this.c29 = stateEffect;
    return this;
  }

  padding(padding) {
    this.paddingValue = padding;
    return this;
  }
};
w9([
  Trace
], ToolBarV2Modifier.prototype, 'backgroundColorValue', void 0);
w9([
  Trace
], ToolBarV2Modifier.prototype, 'heightValue', void 0);
w9([
  Trace
], ToolBarV2Modifier.prototype, 'stateEffectValue', void 0);
w9([
  Trace
], ToolBarV2Modifier.prototype, 'paddingValue', void 0);
ToolBarV2Modifier = w9([
  ObservedV2
], ToolBarV2Modifier);

export { ToolBarV2Modifier };
let n28 = class ToolBarV2Theme {
  constructor() {
    this.d29 = {
      'id': -1,
      'type': 10001,
      params: ['sys.color.icon_primary'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__'
    };
    this.e29 = {
      'id': -1,
      'type': 10001,
      params: ['sys.color.icon_emphasize'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__'
    };
    this.f29 = {
      'id': -1,
      'type': 10001,
      params: ['sys.color.font_primary'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__'
    };
    this.g29 = {
      'id': -1,
      'type': 10001,
      params: ['sys.color.font_emphasize'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__'
    };
  }
};
w9([
  Trace
], n28.prototype, 'iconPrimaryColor', void 0);
w9([
  Trace
], n28.prototype, 'iconActivePrimaryColor', void 0);
w9([
  Trace
], n28.prototype, 'fontPrimaryColor', void 0);
w9([
  Trace
], n28.prototype, 'fontActivatedPrimaryColor', void 0);
n28 = w9([
  ObservedV2
], n28);

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
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level12'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__'
        }))
        .stateEffect(true)
        .height(LengthMetrics.vp(z27)));
    this.localActivatedIndex = -1;
    this.menuContent = [];
    this.fontSize = 1;
    this.theme = new n28();
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
          'moduleName': '__harDefaultModuleName__'
        },
      }),
      icon: new ToolBarV2ItemImage({
        src: x27
      })
    });
    this.moreText = {
      'id': -1,
      'type': 10003,
      params: ['sys.string.ohos_toolbar_more'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__'
    };
    this.finalizeConstruction();
  }

  resetStateVarsOnReuse(params) {
    this.resetParam('toolBarList', (params && 'toolBarList' in params) ? params.toolBarList : undefined);
    this.resetParam('activatedIndex', (params && 'activatedIndex' in params) ? params.activatedIndex : -1);
    this.resetParam('dividerModifier',
      (params && 'dividerModifier' in params) ? params.dividerModifier : new DividerModifier());
    this.resetParam('toolBarModifier',
      (params && 'toolBarModifier' in params) ? params.toolBarModifier : new ToolBarV2Modifier()
        .padding(LengthMetrics.resource({
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level12'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__'
        }))
        .stateEffect(true)
        .height(LengthMetrics.vp(z27)));
    this.localActivatedIndex = -1;
    this.menuContent = [];
    this.fontSize = 1;
    this.theme = new n28();
    this.resetComputed('menus');
    this.resetMonitorsOnReuse();
  }

  onActivateIndexChange(monitor) {
    this.localActivatedIndex = monitor.value('activatedIndex')?.now ?? -1;
  }

  get menus() {
    this.menuContent = [];
    this.toolBarList.forEach((value, index) => {
      if (index >= a28 - 1) {
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
    } catch (err) {
      let code = err?.code;
      let message = err?.message;
      hilog.error(0x3900, 'Ace', `Faild to toolBarV2 getMaxFontScale, code: ${code}, message: ${message}`);
    }
  }

  onWillApplyTheme(theme) {
    this.theme.d29 = theme.colors.iconPrimary;
    this.theme.e29 = theme.colors.iconEmphasize;
    this.theme.f29 = theme.colors.fontPrimary;
    this.theme.g29 = theme.colors.fontEmphasize;
  }

  MoreTabBuilder(index, parent = null) {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
      Button.accessibilityGroup(true);
      Button.focusable(true);
      Button.focusOnTouch(true);
      Button.focusBox({
        margin: LengthMetrics.vp(j28),
        strokeWidth: LengthMetrics.vp(k28),
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
      Button.bindMenu(this.menuContent, { placement: Placement.TopRight, offset: { x: -12, y: -10 } });
      Button.borderRadius({
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_corner_radius_clicked'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
      });
      Button.backgroundColor(this.toolBarList[index].backgroundColor);
      Button.onHover((isHover) => {
        if (isHover) {
          this.toolBarList[index].backgroundColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_hover'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
          };
        } else {
          this.toolBarList[index].backgroundColor = Color.Transparent;
        }
      });
      ViewStackProcessor.visualState('pressed');
      Button.backgroundColor((!this.toolBarModifier?.c29) ?
      this.toolBarList[index].backgroundColor : {
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
      SymbolGlyph.create(x27);
      SymbolGlyph.fontSize(y27);
      SymbolGlyph.fontColor([this.theme.d29]);
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
      Text.fontColor(this.theme.f29);
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
        'moduleName': '__harDefaultModuleName__'
      });
      Button.focusable(!(this.toolBarList[index]?.state === ToolBarV2ItemState.DISABLE));
      Button.focusOnTouch(!(this.toolBarList[index]?.state === ToolBarV2ItemState.DISABLE));
      Button.focusBox({
        margin: LengthMetrics.vp(j28),
        strokeWidth: LengthMetrics.vp(k28),
        strokeColor: ColorMetrics.resourceColor({
          'id': -1,
          'type': 10001,
          params: ['sys.color.ohos_id_color_focused_outline'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__'
        })
      });
      Button.backgroundColor(this.toolBarList[index].backgroundColor);
      Button.onHover((isHover) => {
        if (isHover && this.toolBarList[index]?.state !== ToolBarV2ItemState.DISABLE) {
          this.toolBarList[index].backgroundColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_hover'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
          };
        } else {
          this.toolBarList[index].backgroundColor = Color.Transparent;
        }
      });
      ViewStackProcessor.visualState('pressed');
      Button.backgroundColor((this.toolBarList[index]?.state === ToolBarV2ItemState.DISABLE) ||
        (!this.toolBarModifier?.c29) ?
      this.toolBarList[index].backgroundColor : {
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
      if (this.toolBarList[index]?.symbol) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            SymbolGlyph.create();
            SymbolGlyph.fontSize(y27);
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
      } else if (Util.y28(this.toolBarList[index]?.image?.src)) {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            SymbolGlyph.create(this.toolBarList[index]?.image?.src);
            SymbolGlyph.fontSize(y27);
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
      } else {
        this.ifElseBranchUpdateFunction(2, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(this.toolBarList[index]?.image?.src);
            Image.width(y27);
            Image.height(y27);
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
      Text.create(this.toolBarList[index]?.content.text);
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
            Column.constraintSize({ minHeight: this.fontSize === b28 ? d28 : e28 });
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
                    'moduleName': '__harDefaultModuleName__'
                  }]);
                  SymbolGlyph.fontSize(c28);
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
            } else if (Util.y28(item.image?.src)) {
              this.ifElseBranchUpdateFunction(1, () => {
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                  SymbolGlyph.create(item.image?.src);
                  SymbolGlyph.fontColor([{
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.icon_primary'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                  }]);
                  SymbolGlyph.fontSize(c28);
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
                  Image.create(item.image?.src);
                  Image.width(c28);
                  Image.height(c28);
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
            Text.create(item.content.text);
            Text.fontSize(f28);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.maxLines(this.itemCardTextMaxLine);
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
      } else {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.constraintSize({ minHeight: this.fontSize === b28 ? d28 : e28 });
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
                    'moduleName': '__harDefaultModuleName__'
                  }]);
                  SymbolGlyph.fontSize(c28);
                }, SymbolGlyph);
              });
            } else if (Util.y28(item.image?.src)) {
              this.ifElseBranchUpdateFunction(1, () => {
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                  SymbolGlyph.create(item.image?.src);
                  SymbolGlyph.fontColor([{
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.icon_primary'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                  }]);
                  SymbolGlyph.fontSize(c28);
                }, SymbolGlyph);
              });
            } else {
              this.ifElseBranchUpdateFunction(2, () => {
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                  Image.create(item.image?.src);
                  Image.width(c28);
                  Image.height(c28);
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

  getFontSizeScale() {
    let context = this.getUIContext();
    let u28 = context.getHostContext()?.config?.fontSizeScale ?? 1;
    if (!this.isFollowSystem) {
      return 1;
    } else {
      return Math.min(u28, this.maxFontSizeScale);
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
      return this.toolBarList[index]?.image?.activatedColor?.color ?? this.theme.e29;
    }
    return this.toolBarList[index]?.image?.color?.color ?? this.theme.d29;
  }

  getTextColor(index) {
    if (this.isItemActivating(index)) {
      return this.toolBarList[index]?.content.activatedColor?.color ?? this.theme.g29;
    }
    return this.toolBarList[index]?.content.color?.color ?? this.theme.f29;
  }

  toLengthString(value) {
    if (value === undefined) {
      return '';
    }
    const length = value.value;
    let t28 = '';
    switch (value.unit) {
      case LengthUnit.PX:
        t28 = `${length}px`;
        break;
      case LengthUnit.FP:
        t28 = `${length}fp`;
        break;
      case LengthUnit.LPX:
        t28 = `${length}lpx`;
        break;
      case LengthUnit.PERCENT:
        t28 = `${length * 100}%`;
        break;
      case LengthUnit.VP:
        t28 = `${length}vp`;
        break;
      default:
        t28 = `${length}vp`;
        break;
    }
    return t28;
  }

  clickEventAction(index) {
    let s28 = this.toolBarList[index];
    if (s28.state === ToolBarV2ItemState.ACTIVATE) {
      if (this.localActivatedIndex === index) {
        this.localActivatedIndex = -1;
      } else {
        this.localActivatedIndex = index;
      }
    }
    if (s28.state !== ToolBarV2ItemState.DISABLE) {
      s28.action && s28.action(index);
    }
  }

  getItemGestureModifier(item, index) {
    if (!item?.icon) {
      return undefined;
    }
    let q28 = new m28();
    q28.a29 = (event) => {
      if (this.fontSize >= m28.minFontSize) {
        event.addGesture(new LongPressGestureHandler({ repeat: false, duration: m28.longPressTime })
          .onAction(() => {
            promptAction.openCustomDialog({
              builder: () => {
                this.itemCardDialogBuilder(item, index);
              },
              onWillAppear: () => {
                try {
                  let context = this.getUIContext().getHostContext();
                  let r28 = context.windowStage.getMainWindowSync();
                  let properties = r28.getWindowProperties();
                  if (px2vp(properties.windowRect.height) > g28) {
                    this.itemCardTextMaxLine = h28;
                  } else {
                    this.itemCardTextMaxLine = i28;
                  }
                } catch (err) {
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
                'moduleName': '__harDefaultModuleName__'
              },
              width: this.fontSize === b28 ? d28 : e28
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
    return q28;
  }

  onMeasureSize(selfLayoutInfo, children, constraint) {
    this.fontSize = this.getFontSizeScale();
    let o28 = { height: 0, width: 0 };
    children.forEach((child) => {
      let p28 = child.measure(constraint);
      o28.width = p28.width;
      o28.height = p28.height;
    });
    return o28;
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
        minHeight: this.toLengthString(this.toolBarModifier?.heightValue),
        maxHeight: this.toLengthString(this.toolBarModifier?.heightValue),
      });
      Row.width('100%');
      Row.height(this.toLengthString(this.toolBarModifier?.heightValue));
      Row.padding({
        start: this.toolBarList.length < a28 ?
          this.toolBarModifier?.paddingValue : LengthMetrics.resource({
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level0'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__'
        }),
        end: this.toolBarList.length < a28 ?
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
          if (this.toolBarList.length <= a28 || index < a28 - 1) {
            this.ifElseBranchUpdateFunction(0, () => {
              this.observeComponentCreation2((elmtId, isInitialRender) => {
                Row.create();
                Row.height('100%');
                Row.flexShrink(1);
              }, Row);
              this.TabBuilder.bind(this)(index);
              Row.pop();
            });
          } else {
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
      if (this.toolBarList.length > a28) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.height('100%');
            Row.flexShrink(1);
          }, Row);
          this.MoreTabBuilder.bind(this)(a28 - 1);
          Row.pop();
        });
      } else {
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
w9([
  Param
], ToolBarV2.prototype, 'toolBarList', void 0);
w9([
  Param
], ToolBarV2.prototype, 'activatedIndex', void 0);
w9([
  Param
], ToolBarV2.prototype, 'dividerModifier', void 0);
w9([
  Param
], ToolBarV2.prototype, 'toolBarModifier', void 0);
w9([
  Local
], ToolBarV2.prototype, 'localActivatedIndex', void 0);
w9([
  Local
], ToolBarV2.prototype, 'menuContent', void 0);
w9([
  Local
], ToolBarV2.prototype, 'fontSize', void 0);
w9([
  Local
], ToolBarV2.prototype, 'theme', void 0);
w9([
  Monitor('activatedIndex')
], ToolBarV2.prototype, 'onActivateIndexChange', null);
w9([
  Computed
], ToolBarV2.prototype, 'menus', null);

export default {
  ToolBarV2Item,
  ToolBarV2ItemImage,
  ToolBarV2ItemText,
  ToolBarV2,
  ToolBarV2ItemState,
  ToolBarV2Modifier,
  ToolBarV2SymbolGlyph
};