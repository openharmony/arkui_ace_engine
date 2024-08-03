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

export let ItemState;
(function (j3) {
  j3[j3['ENABLE'] = 1] = 'ENABLE';
  j3[j3['DISABLE'] = 2] = 'DISABLE';
  j3[j3['ACTIVATE'] = 3] = 'ACTIVATE';
})(ItemState || (ItemState = {}));

const PUBLIC_MORE = { id: -1, type: 20000, params: ['sys.media.ohos_ic_public_more'], bundleName: '', moduleName: '' };

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
    this.heightValue = LengthMetrics.vp(56);
    this.stateEffectValue = true;
    this.paddingValue = LengthMetrics.vp(24);
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
  constructor(z3, a4, b4, c4 = -1, d4 = undefined, e4) {
    super(z3, b4, c4, e4);
    if (typeof d4 === 'function') {
      this.paramsGenerator_ = d4;
    }
    this.__toolBarList = new SynchedPropertyNesedObjectPU(a4.toolBarList, this, 'toolBarList');
    this.controller = new TabsController();
    this.__activateIndex = new SynchedPropertySimpleOneWayPU(a4.activateIndex, this, 'activateIndex');
    this.__dividerModifier = new SynchedPropertyObjectOneWayPU(a4.dividerModifier, this, 'dividerModifier');
    this.__toolBarModifier = new SynchedPropertyObjectOneWayPU(a4.toolBarModifier, this, 'toolBarModifier');
    this.__moreText = new SynchedPropertyObjectOneWayPU(a4.moreText, this, 'moreText');
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
    this.setInitiallyProvidedValue(a4);
    this.finalizeConstruction();
  }

  setInitiallyProvidedValue(y3) {
    this.__toolBarList.set(y3.toolBarList);
    if (y3.controller !== undefined) {
      this.controller = y3.controller;
    }
    if (y3.activateIndex === undefined) {
      this.__activateIndex.set(-1);
    }
    if (y3.dividerModifier === undefined) {
      this.__dividerModifier.set(new DividerModifier());
    }
    if (y3.toolBarModifier === undefined) {
      this.__toolBarModifier.set(new ToolBarModifier()
        .padding(LengthMetrics.vp(24))
        .stateEffect(true)
        .height(LengthMetrics.vp(56)));
    }
    if (y3.moreText === undefined) {
      this.__moreText.set({
        'id': -1,
        'type': 10003,
        params: ['sys.string.ohos_toolbar_more'],
        'bundleName': '',
        'moduleName': '',
      });
    }
    if (y3.menuContent !== undefined) {
      this.menuContent = y3.menuContent;
    }
    if (y3.toolBarItemBackground !== undefined) {
      this.toolBarItemBackground = y3.toolBarItemBackground;
    }
    if (y3.itemBackground !== undefined) {
      this.itemBackground = y3.itemBackground;
    }
    if (y3.iconPrimaryColor !== undefined) {
      this.iconPrimaryColor = y3.iconPrimaryColor;
    }
    if (y3.iconActivePrimaryColor !== undefined) {
      this.iconActivePrimaryColor = y3.iconActivePrimaryColor;
    }
    if (y3.fontPrimaryColor !== undefined) {
      this.fontPrimaryColor = y3.fontPrimaryColor;
    }
    if (y3.fontActivatedPrimaryColor !== undefined) {
      this.fontActivatedPrimaryColor = y3.fontActivatedPrimaryColor;
    }
    if (y3.symbolEffect !== undefined) {
      this.symbolEffect = y3.symbolEffect;
    }
  }

  updateStateVars(x3) {
    this.__toolBarList.set(x3.toolBarList);
    this.__activateIndex.reset(x3.activateIndex);
    this.__dividerModifier.reset(x3.dividerModifier);
    this.__toolBarModifier.reset(x3.toolBarModifier);
    this.__moreText.reset(x3.moreText);
  }

  purgeVariableDependenciesOnElmtId(w3) {
    this.__toolBarList.purgeDependencyOnElmtId(w3);
    this.__activateIndex.purgeDependencyOnElmtId(w3);
    this.__dividerModifier.purgeDependencyOnElmtId(w3);
    this.__toolBarModifier.purgeDependencyOnElmtId(w3);
    this.__moreText.purgeDependencyOnElmtId(w3);
    this.__menuContent.purgeDependencyOnElmtId(w3);
    this.__itemBackground.purgeDependencyOnElmtId(w3);
    this.__iconPrimaryColor.purgeDependencyOnElmtId(w3);
    this.__iconActivePrimaryColor.purgeDependencyOnElmtId(w3);
    this.__fontPrimaryColor.purgeDependencyOnElmtId(w3);
    this.__fontActivatedPrimaryColor.purgeDependencyOnElmtId(w3);
    this.__symbolEffect.purgeDependencyOnElmtId(w3);
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
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }

  get toolBarList() {
    return this.__toolBarList.get();
  }

  get activateIndex() {
    return this.__activateIndex.get();
  }

  set activateIndex(v3) {
    this.__activateIndex.set(v3);
  }

  get dividerModifier() {
    return this.__dividerModifier.get();
  }

  set dividerModifier(u3) {
    this.__dividerModifier.set(u3);
  }

  get toolBarModifier() {
    return this.__toolBarModifier.get();
  }

  set toolBarModifier(t3) {
    this.__toolBarModifier.set(t3);
  }

  get moreText() {
    return this.__moreText.get();
  }

  set moreText(s3) {
    this.__moreText.set(s3);
  }

  get menuContent() {
    return this.__menuContent.get();
  }

  set menuContent(r3) {
    this.__menuContent.set(r3);
  }

  get itemBackground() {
    return this.__itemBackground.get();
  }

  set itemBackground(q3) {
    this.__itemBackground.set(q3);
  }

  get iconPrimaryColor() {
    return this.__iconPrimaryColor.get();
  }

  set iconPrimaryColor(p3) {
    this.__iconPrimaryColor.set(p3);
  }

  get iconActivePrimaryColor() {
    return this.__iconActivePrimaryColor.get();
  }

  set iconActivePrimaryColor(o3) {
    this.__iconActivePrimaryColor.set(o3);
  }

  get fontPrimaryColor() {
    return this.__fontPrimaryColor.get();
  }

  set fontPrimaryColor(n3) {
    this.__fontPrimaryColor.set(n3);
  }

  get fontActivatedPrimaryColor() {
    return this.__fontActivatedPrimaryColor.get();
  }

  set fontActivatedPrimaryColor(m3) {
    this.__fontActivatedPrimaryColor.set(m3);
  }

  get symbolEffect() {
    return this.__symbolEffect.get();
  }

  set symbolEffect(l3) {
    this.__symbolEffect.set(l3);
  }

  onWillApplyTheme(k3) {
    this.iconPrimaryColor = k3.colors.iconPrimary;
    this.iconActivePrimaryColor = k3.colors.iconEmphasize;
    this.fontPrimaryColor = k3.colors.fontPrimary;
    this.fontActivatedPrimaryColor = k3.colors.fontEmphasize;
  }

  MoreTabBuilder(x2, y2 = null) {
    this.observeComponentCreation2((g3, h3) => {
      Column.create();
      Column.width('100%');
      Column.height('100%');
      Column.justifyContent(FlexAlign.Center);
      Column.bindMenu(ObservedObject.GetRawObject(this.menuContent), { placement: Placement.TopRight, offset: { x: -12, y: -10 } });
      Column.padding({ start: LengthMetrics.vp(4), end: LengthMetrics.vp(4) });
      Column.borderRadius({
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_corner_radius_clicked'],
        'bundleName': '',
        'moduleName': '',
      });
      Column.backgroundColor(ObservedObject.GetRawObject(this.itemBackground));
      Column.onHover((j3) => {
        if (j3) {
          this.toolBarItemBackground[x2] = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_hover'],
            'bundleName': '',
            'moduleName': '',
          };
        }
        else {
          this.toolBarItemBackground[x2] = Color.Transparent;
        }
        this.itemBackground = this.toolBarItemBackground[x2];
      });
      ViewStackProcessor.visualState('pressed');
      Column.backgroundColor((!this.toolBarModifier.stateEffectValue) ?
      this.toolBarItemBackground[x2] : {
          'id': -1,
          'type': 10001,
          params: ['sys.color.ohos_id_color_click_effect'],
          'bundleName': '',
          'moduleName': '',
        });
      ViewStackProcessor.visualState('normal');
      Column.backgroundColor(this.toolBarItemBackground[x2]);
      ViewStackProcessor.visualState();
    }, Column);
    this.observeComponentCreation2((e3, f3) => {
      Image.create(PUBLIC_MORE);
      Image.width(24);
      Image.height(24);
      Image.fillColor(ObservedObject.GetRawObject(this.iconPrimaryColor));
      Image.margin({ bottom: 2 });
      Image.objectFit(ImageFit.Contain);
      Image.draggable(false);
    }, Image);
    this.observeComponentCreation2((c3, d3) => {
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

  TabBuilder(a2, b2 = null) {
    this.observeComponentCreation2((r2, s2) => {
      Column.create();
      Column.justifyContent(FlexAlign.Center);
      Column.width('100%');
      Column.height('100%');
      Column.focusable(!(this.toolBarList[a2]?.state === 2));
      Column.focusOnTouch(!(this.toolBarList[a2]?.state === 2));
      Column.padding({ start: LengthMetrics.vp(4), end: LengthMetrics.vp(4) });
      Column.borderRadius({
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_corner_radius_clicked'],
        'bundleName': '',
        'moduleName': '',
      });
      Column.backgroundColor(ObservedObject.GetRawObject(this.itemBackground));
      Column.onClick(() => {
        let w2 = this.toolBarList[a2];
        if (w2.state === ItemState.ACTIVATE) {
          if (this.activateIndex === a2) {
            this.activateIndex = -1;
          }
          else {
            this.activateIndex = a2;
          }
        }
        if (!(w2.state === ItemState.DISABLE)) {
          w2.action && w2.action();
        }
      });
      Column.onHover((v2) => {
        if (v2) {
          this.toolBarItemBackground[a2] = (this.toolBarList[a2]?.state === ItemState.DISABLE)
            ? Color.Transparent : {
              'id': -1,
              'type': 10001,
              params: ['sys.color.ohos_id_color_hover'],
              'bundleName': '',
              'moduleName': '',
            };
        }
        else {
          this.toolBarItemBackground[a2] = Color.Transparent;
        }
        this.itemBackground = this.toolBarItemBackground[a2];
      });
      ViewStackProcessor.visualState('pressed');
      Column.backgroundColor((this.toolBarList[a2]?.state === ItemState.DISABLE) ||
        (!this.toolBarModifier.stateEffectValue) ?
      this.toolBarItemBackground[a2] : {
          'id': -1,
          'type': 10001,
          params: ['sys.color.ohos_id_color_click_effect'],
          'bundleName': '',
          'moduleName': '',
        });
      ViewStackProcessor.visualState('normal');
      Column.backgroundColor(this.toolBarItemBackground[a2]);
      ViewStackProcessor.visualState();
    }, Column);
    this.observeComponentCreation2((h2, i2) => {
      If.create();
      if (this.toolBarList[a2]?.toolBarSymbolOptions?.normal ||
        this.toolBarList[a2]?.toolBarSymbolOptions?.activated) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((p2, q2) => {
            SymbolGlyph.create();
            SymbolGlyph.fontSize('24vp');
            SymbolGlyph.symbolEffect(ObservedObject.GetRawObject(this.symbolEffect), false);
            SymbolGlyph.attributeModifier.bind(this)(this.getToolBarSymbolModifier(a2));
            SymbolGlyph.opacity((this.toolBarList[a2]?.state === 2) ? 0.4 : 1);
            SymbolGlyph.margin({ bottom: 2 });
          }, SymbolGlyph);
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((l2, m2) => {
            Image.create(this.toolBarList[a2]?.icon);
            Image.width(24);
            Image.height(24);
            Image.fillColor(this.getIconColor(a2));
            Image.opacity((this.toolBarList[a2]?.state === 2) ? 0.4 : 1);
            Image.margin({ bottom: 2 });
            Image.objectFit(ImageFit.Contain);
            Image.draggable(false);
          }, Image);
        });
      }
    }, If);
    If.pop();
    this.observeComponentCreation2((f2, g2) => {
      Text.create(this.toolBarList[a2]?.content);
      Text.fontColor(this.getTextColor(a2));
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
      Text.opacity((this.toolBarList[a2]?.state === 2) ? 0.4 : 1);
      Text.textAlign(TextAlign.Center);
    }, Text);
    Text.pop();
    Column.pop();
  }

  getToolBarSymbolModifier(z1) {
    if (this.activateIndex === z1) {
      return this.toolBarList[z1]?.toolBarSymbolOptions?.activated;
    }
    return this.toolBarList[z1]?.toolBarSymbolOptions?.normal;
  }

  getIconColor(y1) {
    if (this.activateIndex === y1 && !(this.toolBarList[y1]?.state === 2)) {
      return this.toolBarList[y1]?.activatedIconColor ?? this.iconActivePrimaryColor;
    }
    return this.toolBarList[y1]?.iconColor ?? this.iconPrimaryColor;
  }

  getTextColor(x1) {
    if (this.activateIndex === x1 && !(this.toolBarList[x1]?.state === 2)) {
      return this.toolBarList[x1]?.activatedTextColor ?? this.fontActivatedPrimaryColor;
    }
    return this.toolBarList[x1]?.textColor ?? this.fontPrimaryColor;
  }

  toLengthString(r1) {
    if (r1 === void (0)) {
      return '';
    }
    const s1 = r1.value;
    let t1 = '';
    switch (r1.unit) {
      case LengthUnit.PX:
        t1 = `${s1}px`;
        break;
      case LengthUnit.FP:
        t1 = `${s1}fp`;
        break;
      case LengthUnit.LPX:
        t1 = `${s1}lpx`;
        break;
      case LengthUnit.PERCENT:
        t1 = `${s1 * 100}%`;
        break;
      case LengthUnit.VP:
        t1 = `${s1}vp`;
        break;
      default:
        t1 = `${s1}vp`;
        break;
    }
    return t1;
  }

  refreshData() {
    this.menuContent = [];
    for (let q1 = 0; q1 < this.toolBarList.length; q1++) {
      if (q1 >= 4 && this.toolBarList.length > 5) {
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
    this.observeComponentCreation2((o1, p1) => {
      Column.create();
      Column.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.toolBarModifier));
    }, Column);
    this.observeComponentCreation2((m1, n1) => {
      Divider.create();
      Divider.width('100%');
      Divider.height(1);
      Divider.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.dividerModifier));
    }, Divider);
    this.observeComponentCreation2((k1, l1) => {
      Column.create();
      Column.justifyContent(FlexAlign.Center);
      Column.width('100%');
    }, Column);
    this.observeComponentCreation2((g1, h1) => {
      Tabs.create({ barPosition: BarPosition.End, controller: this.controller });
      Tabs.vertical(false);
      Tabs.constraintSize({
        minHeight: this.toLengthString(this.toolBarModifier.heightValue),
        maxHeight: this.toLengthString(this.toolBarModifier.heightValue),
      });
      Tabs.barHeight(this.toLengthString(this.toolBarModifier.heightValue));
      Tabs.barMode(BarMode.Fixed);
      Tabs.onChange((j1) => {
      });
      Tabs.width('100%');
      Tabs.height(this.toLengthString(this.toolBarModifier.heightValue));
      Tabs.padding({
        start: this.toolBarList.length < 5 ? this.toolBarModifier.paddingValue : LengthMetrics.vp(0),
        end: this.toolBarList.length < 5 ? this.toolBarModifier.paddingValue : LengthMetrics.vp(0),
      });
    }, Tabs);
    this.observeComponentCreation2((n, o) => {
      ForEach.create();
      const p = (r, s) => {
        const t = r;
        this.observeComponentCreation2((v, w) => {
          If.create();
          if (this.toolBarList.length <= 5) {
            this.ifElseBranchUpdateFunction(0, () => {
              this.observeComponentCreation2((e1, f1) => {
                TabContent.create();
                TabContent.tabBar({ builder: () => {
                  this.TabBuilder.call(this, s);
                } });
                TabContent.enabled(!(this.toolBarList[s]?.state === 2));
                TabContent.focusOnTouch(!(this.toolBarList[s]?.state === 2));
              }, TabContent);
              TabContent.pop();
            });
          }
          else if (s < 4) {
            this.ifElseBranchUpdateFunction(1, () => {
              this.observeComponentCreation2((a1, b1) => {
                TabContent.create();
                TabContent.tabBar({ builder: () => {
                  this.TabBuilder.call(this, s);
                } });
                TabContent.enabled(!(this.toolBarList[s]?.state === 2));
                TabContent.focusOnTouch(!(this.toolBarList[s]?.state === 2));
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
      this.forEachUpdateFunction(n, this.toolBarList, p, undefined, true, false);
    }, ForEach);
    ForEach.pop();
    this.observeComponentCreation2((g, h) => {
      If.create();
      if (this.refreshData() && this.toolBarList.length > 5) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((l, m) => {
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
export default { ToolBarOptions, ToolBar, ItemState, ToolBarOption, ToolBarModifier };