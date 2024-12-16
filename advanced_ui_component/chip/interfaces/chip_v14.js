/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
  Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {});
}
const ColorMetrics = requireNapi('arkui.node').ColorMetrics;
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;
const mediaquery = requireNapi('mediaquery');
export var ChipSize;
(function (ChipSize) {
  ChipSize['NORMAL'] = 'NORMAL';
  ChipSize['SMALL'] = 'SMALL';
})(ChipSize || (ChipSize = {}));
var a1;
(function (e5) {
  e5['SM'] = 'SM';
  e5['MD'] = 'MD';
  e5['LG'] = 'LG';
})(a1 || (a1 = {}));
export var AccessibilitySelectedType;
(function (AccessibilitySelectedType) {
  AccessibilitySelectedType[(AccessibilitySelectedType['CLICKED'] = 0)] =
    'CLICKED';
  AccessibilitySelectedType[(AccessibilitySelectedType['CHECKED'] = 1)] =
    'CHECKED';
  AccessibilitySelectedType[(AccessibilitySelectedType['SELECTED'] = 2)] =
    'SELECTED';
})(AccessibilitySelectedType || (AccessibilitySelectedType = {}));
export const b1 = {
  prefixIcon: {
    size: { width: 16, height: 16 },
    fillColor: {
      id: -1,
      type: 10001,
      params: ['sys.color.ohos_id_color_secondary'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    },
    activatedFillColor: {
      id: -1,
      type: 10001,
      params: ['sys.color.ohos_id_color_text_primary_contrary'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    },
  },
  label: {
    e1: {
      id: -1,
      type: 10002,
      params: ['sys.float.ohos_id_text_size_button2'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    },
    f1: {
      id: -1,
      type: 10002,
      params: ['sys.float.ohos_id_text_size_button2'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    },
    fontColor: {
      id: -1,
      type: 10001,
      params: ['sys.color.ohos_id_color_text_primary'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    },
    activatedFontColor: {
      id: -1,
      type: 10001,
      params: ['sys.color.ohos_id_color_text_primary_contrary'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    },
    fontFamily: 'HarmonyOS Sans',
    g1: {
      left: 6,
      right: 6,
      top: 0,
      bottom: 0,
    },
    h1: {
      left: 4,
      right: 4,
      top: 0,
      bottom: 0,
    },
    defaultFontSize: 14,
    i1: {
      start: LengthMetrics.vp(6),
      end: LengthMetrics.vp(6),
      top: LengthMetrics.vp(0),
      bottom: LengthMetrics.vp(0),
    },
    j1: {
      start: LengthMetrics.vp(4),
      end: LengthMetrics.vp(4),
      top: LengthMetrics.vp(0),
      bottom: LengthMetrics.vp(0),
    },
  },
  suffixIcon: {
    size: { width: 16, height: 16 },
    fillColor: {
      id: -1,
      type: 10001,
      params: ['sys.color.ohos_id_color_secondary'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    },
    activatedFillColor: {
      id: -1,
      type: 10001,
      params: ['sys.color.ohos_id_color_text_primary_contrary'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    },
    l1: {
      id: -1,
      type: 20000,
      params: ['sys.media.ohos_ic_public_cancel', 16, 16],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    },
    focusable: false,
  },
  m1: {
    n1: [
      {
        id: -1,
        type: 10001,
        params: ['sys.color.ohos_id_color_secondary'],
        bundleName: '__harDefaultBundleName__',
        moduleName: '__harDefaultModuleName__',
      },
    ],
    activatedFontColor: [
      {
        id: -1,
        type: 10001,
        params: ['sys.color.ohos_id_color_text_primary_contrary'],
        bundleName: '__harDefaultBundleName__',
        moduleName: '__harDefaultModuleName__',
      },
    ],
    fontSize: 16,
    o1: -1,
  },
  q1: {
    s1: 1.75,
    t1: 12,
    u1: 36,
    v1: 28,
    enabled: true,
    activated: false,
    backgroundColor: {
      id: -1,
      type: 10001,
      params: ['sys.color.ohos_id_color_button_normal'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    },
    activatedBackgroundColor: {
      id: -1,
      type: 10001,
      params: ['sys.color.ohos_id_color_emphasize'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    },
    w1: {
      id: -1,
      type: 10001,
      params: ['sys.color.ohos_id_color_focused_outline'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    },
    z1: 2,
    a2: {
      id: -1,
      type: 10002,
      params: ['sys.float.chip_border_radius_normal'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    },
    b2: {
      id: -1,
      type: 10002,
      params: ['sys.float.chip_border_radius_small'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    },
    borderWidth: 2,
    c2: {
      start: LengthMetrics.vp(16),
      end: LengthMetrics.vp(16),
      top: LengthMetrics.vp(4),
      bottom: LengthMetrics.vp(4),
    },
    d2: {
      start: LengthMetrics.vp(12),
      end: LengthMetrics.vp(12),
      top: LengthMetrics.vp(4),
      bottom: LengthMetrics.vp(4),
    },
    e2: {
      id: -1,
      type: 10001,
      params: ['sys.color.ohos_id_color_hover'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    },
    f2: {
      id: -1,
      type: 10001,
      params: ['sys.color.ohos_id_color_click_effect'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    },
    opacity: { normal: 1, hover: 0.95, pressed: 0.9 },
    g2: {
      h2: 128,
      i2: 156,
      j2: 280,
      l2: 400,
    },
  },
};
const o = 10003;
const t = 10002;
const u = 10007;
export function Chip(options, parent = null) {
  const d5 = options;
  {
    (parent ? parent : this).observeComponentCreation2(
      (elmtId, isInitialRender, options = d5) => {
        if (isInitialRender) {
          let componentCall = new d1(
            parent ? parent : this,
            {
              chipSize: options.size,
              prefixIcon: options.prefixIcon,
              prefixSymbol: options.prefixSymbol,
              label: options.label,
              suffixIcon: options.suffixIcon,
              suffixSymbol: options.suffixSymbol,
              suffixSymbolOptions: options.suffixSymbolOptions,
              allowClose: options.allowClose,
              closeOptions: options.closeOptions,
              chipEnabled: options.enabled,
              chipActivated: options.activated,
              chipNodeBackgroundColor: options.backgroundColor,
              chipNodeActivatedBackgroundColor:
                options.activatedBackgroundColor,
              chipNodeRadius: options.borderRadius,
              chipDirection: options.direction,
              chipAccessibilitySelectedType: options.accessibilitySelectedType,
              chipAccessibilityDescription: options.accessibilityDescription,
              chipAccessibilityLevel: options.accessibilityLevel,
              onClose: options.onClose,
              onClicked: options.onClicked,
            },
            undefined,
            elmtId,
            () => {},
            {
              page: 'advancedComponents/src/main/ets/components/ChipV2.ets',
              line: 289,
              m2: 3,
            }
          );
          ViewPU.create(componentCall);
          let paramsLambda = () => {
            return {
              chipSize: options.size,
              prefixIcon: options.prefixIcon,
              prefixSymbol: options.prefixSymbol,
              label: options.label,
              suffixIcon: options.suffixIcon,
              suffixSymbol: options.suffixSymbol,
              suffixSymbolOptions: options.suffixSymbolOptions,
              allowClose: options.allowClose,
              closeOptions: options.closeOptions,
              chipEnabled: options.enabled,
              chipActivated: options.activated,
              chipNodeBackgroundColor: options.backgroundColor,
              chipNodeActivatedBackgroundColor:
                options.activatedBackgroundColor,
              chipNodeRadius: options.borderRadius,
              chipDirection: options.direction,
              chipAccessibilitySelectedType: options.accessibilitySelectedType,
              chipAccessibilityDescription: options.accessibilityDescription,
              chipAccessibilityLevel: options.accessibilityLevel,
              onClose: options.onClose,
              onClicked: options.onClicked,
            };
          };
          componentCall.paramsGenerator_ = paramsLambda;
        } else {
          (parent ? parent : this).updateStateVarsOfChildByElmtId(elmtId, {
            chipSize: options.size,
            prefixIcon: options.prefixIcon,
            prefixSymbol: options.prefixSymbol,
            label: options.label,
            suffixIcon: options.suffixIcon,
            suffixSymbol: options.suffixSymbol,
            suffixSymbolOptions: options.suffixSymbolOptions,
            allowClose: options.allowClose,
            closeOptions: options.closeOptions,
            chipEnabled: options.enabled,
            chipActivated: options.activated,
            chipNodeBackgroundColor: options.backgroundColor,
            chipNodeActivatedBackgroundColor: options.activatedBackgroundColor,
            chipNodeRadius: options.borderRadius,
            chipDirection: options.direction,
            chipAccessibilitySelectedType: options.accessibilitySelectedType,
            chipAccessibilityDescription: options.accessibilityDescription,
            chipAccessibilityLevel: options.accessibilityLevel,
          });
        }
      },
      { name: 'ChipComponent' }
    );
  }
}
export class d1 extends ViewPU {
  constructor(
    parent,
    params,
    __localStorage,
    elmtId = -1,
    paramsLambda = undefined,
    extraInfo
  ) {
    super(parent, __localStorage, elmtId, extraInfo);
    if (typeof paramsLambda === 'function') {
      this.paramsGenerator_ = paramsLambda;
    }
    this.theme = b1;
    this.n2 = new SynchedPropertyObjectOneWayPU(
      params.chipSize,
      this,
      'chipSize'
    );
    this.o2 = new SynchedPropertySimpleOneWayPU(
      params.allowClose,
      this,
      'allowClose'
    );
    this.q2 = new SynchedPropertyObjectOneWayPU(
      params.closeOptions,
      this,
      'closeOptions'
    );
    this.s2 = new SynchedPropertySimpleOneWayPU(
      params.chipDirection,
      this,
      'chipDirection'
    );
    this.t2 = new SynchedPropertyObjectOneWayPU(
      params.prefixIcon,
      this,
      'prefixIcon'
    );
    this.u2 = new SynchedPropertyObjectOneWayPU(
      params.prefixSymbol,
      this,
      'prefixSymbol'
    );
    this.v2 = new SynchedPropertyObjectOneWayPU(params.label, this, 'label');
    this.w2 = new SynchedPropertyObjectOneWayPU(
      params.suffixIcon,
      this,
      'suffixIcon'
    );
    this.z2 = new SynchedPropertyObjectOneWayPU(
      params.suffixSymbol,
      this,
      'suffixSymbol'
    );
    this.a3 = new SynchedPropertyObjectOneWayPU(
      params.suffixSymbolOptions,
      this,
      'suffixSymbolOptions'
    );
    this.b3 = new SynchedPropertyObjectOneWayPU(
      params.chipNodeBackgroundColor,
      this,
      'chipNodeBackgroundColor'
    );
    this.c3 = new SynchedPropertyObjectOneWayPU(
      params.chipNodeActivatedBackgroundColor,
      this,
      'chipNodeActivatedBackgroundColor'
    );
    this.d3 = new SynchedPropertyObjectOneWayPU(
      params.chipNodeRadius,
      this,
      'chipNodeRadius'
    );
    this.e3 = new SynchedPropertySimpleOneWayPU(
      params.chipEnabled,
      this,
      'chipEnabled'
    );
    this.f3 = new SynchedPropertySimpleOneWayPU(
      params.chipActivated,
      this,
      'chipActivated'
    );
    this.g3 = new SynchedPropertySimpleOneWayPU(
      params.chipAccessibilitySelectedType,
      this,
      'chipAccessibilitySelectedType'
    );
    this.h3 = new SynchedPropertyObjectOneWayPU(
      params.chipAccessibilityDescription,
      this,
      'chipAccessibilityDescription'
    );
    this.i3 = new SynchedPropertySimpleOneWayPU(
      params.chipAccessibilityLevel,
      this,
      'chipAccessibilityLevel'
    );
    this.w4 = new ObservedPropertySimplePU(true, this, 'isChipExist');
    this.l3 = new ObservedPropertyObjectPU({ x: 1, y: 1 }, this, 'chipScale');
    this.m3 = new ObservedPropertySimplePU(1, this, 'chipOpacity');
    this.x4 = new ObservedPropertySimplePU(0, this, 'suffixSymbolHeight');
    this.z3 = new ObservedPropertySimplePU(0, this, 'suffixSymbolWidth');
    this.y4 = new ObservedPropertySimplePU(a1.SM, this, 'breakPoint');
    this.w3 = new ObservedPropertySimplePU(1, this, 'fontSizeScale');
    this.onClose = undefined;
    this.onClicked = undefined;
    this.smListener = mediaquery.matchMediaSync(
      '(0vp<width) and (width<600vp)'
    );
    this.mdListener = mediaquery.matchMediaSync(
      '(600vp<=width) and (width<840vp)'
    );
    this.lgListener = mediaquery.matchMediaSync('(840vp<=width)');
    this.symbolEffect = new SymbolEffect();
    this.environmentCallbackID = undefined;
    this.environmentCallback = {
      onConfigurationUpdated: (configuration) => {
        this.fontSizeScale = configuration.fontSizeScale ?? 1;
      },
      onMemoryLevel() {},
    };
    this.setInitiallyProvidedValue(params);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(params) {
    if (params.theme !== undefined) {
      this.theme = params.theme;
    }
    if (params.chipSize === undefined) {
      this.n2.set(ChipSize.NORMAL);
    }
    if (params.chipDirection === undefined) {
      this.s2.set(Direction.Auto);
    }
    if (params.chipEnabled === undefined) {
      this.e3.set(true);
    }
    if (params.isChipExist !== undefined) {
      this.isChipExist = params.isChipExist;
    }
    if (params.chipScale !== undefined) {
      this.chipScale = params.chipScale;
    }
    if (params.chipOpacity !== undefined) {
      this.chipOpacity = params.chipOpacity;
    }
    if (params.suffixSymbolHeight !== undefined) {
      this.suffixSymbolHeight = params.suffixSymbolHeight;
    }
    if (params.suffixSymbolWidth !== undefined) {
      this.suffixSymbolWidth = params.suffixSymbolWidth;
    }
    if (params.breakPoint !== undefined) {
      this.breakPoint = params.breakPoint;
    }
    if (params.fontSizeScale !== undefined) {
      this.fontSizeScale = params.fontSizeScale;
    }
    if (params.onClose !== undefined) {
      this.onClose = params.onClose;
    }
    if (params.onClicked !== undefined) {
      this.onClicked = params.onClicked;
    }
    if (params.smListener !== undefined) {
      this.smListener = params.smListener;
    }
    if (params.mdListener !== undefined) {
      this.mdListener = params.mdListener;
    }
    if (params.lgListener !== undefined) {
      this.lgListener = params.lgListener;
    }
    if (params.symbolEffect !== undefined) {
      this.symbolEffect = params.symbolEffect;
    }
    if (params.environmentCallbackID !== undefined) {
      this.environmentCallbackID = params.environmentCallbackID;
    }
    if (params.environmentCallback !== undefined) {
      this.environmentCallback = params.environmentCallback;
    }
  }
  updateStateVars(params) {
    this.n2.reset(params.chipSize);
    this.o2.reset(params.allowClose);
    this.q2.reset(params.closeOptions);
    this.s2.reset(params.chipDirection);
    this.t2.reset(params.prefixIcon);
    this.u2.reset(params.prefixSymbol);
    this.v2.reset(params.label);
    this.w2.reset(params.suffixIcon);
    this.z2.reset(params.suffixSymbol);
    this.a3.reset(params.suffixSymbolOptions);
    this.b3.reset(params.chipNodeBackgroundColor);
    this.c3.reset(params.chipNodeActivatedBackgroundColor);
    this.d3.reset(params.chipNodeRadius);
    this.e3.reset(params.chipEnabled);
    this.f3.reset(params.chipActivated);
    this.g3.reset(params.chipAccessibilitySelectedType);
    this.h3.reset(params.chipAccessibilityDescription);
    this.i3.reset(params.chipAccessibilityLevel);
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
    this.n2.purgeDependencyOnElmtId(rmElmtId);
    this.o2.purgeDependencyOnElmtId(rmElmtId);
    this.q2.purgeDependencyOnElmtId(rmElmtId);
    this.s2.purgeDependencyOnElmtId(rmElmtId);
    this.t2.purgeDependencyOnElmtId(rmElmtId);
    this.u2.purgeDependencyOnElmtId(rmElmtId);
    this.v2.purgeDependencyOnElmtId(rmElmtId);
    this.w2.purgeDependencyOnElmtId(rmElmtId);
    this.z2.purgeDependencyOnElmtId(rmElmtId);
    this.a3.purgeDependencyOnElmtId(rmElmtId);
    this.b3.purgeDependencyOnElmtId(rmElmtId);
    this.c3.purgeDependencyOnElmtId(rmElmtId);
    this.d3.purgeDependencyOnElmtId(rmElmtId);
    this.e3.purgeDependencyOnElmtId(rmElmtId);
    this.f3.purgeDependencyOnElmtId(rmElmtId);
    this.g3.purgeDependencyOnElmtId(rmElmtId);
    this.h3.purgeDependencyOnElmtId(rmElmtId);
    this.i3.purgeDependencyOnElmtId(rmElmtId);
    this.w4.purgeDependencyOnElmtId(rmElmtId);
    this.l3.purgeDependencyOnElmtId(rmElmtId);
    this.m3.purgeDependencyOnElmtId(rmElmtId);
    this.x4.purgeDependencyOnElmtId(rmElmtId);
    this.z3.purgeDependencyOnElmtId(rmElmtId);
    this.y4.purgeDependencyOnElmtId(rmElmtId);
    this.w3.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
    this.n2.aboutToBeDeleted();
    this.o2.aboutToBeDeleted();
    this.q2.aboutToBeDeleted();
    this.s2.aboutToBeDeleted();
    this.t2.aboutToBeDeleted();
    this.u2.aboutToBeDeleted();
    this.v2.aboutToBeDeleted();
    this.w2.aboutToBeDeleted();
    this.z2.aboutToBeDeleted();
    this.a3.aboutToBeDeleted();
    this.b3.aboutToBeDeleted();
    this.c3.aboutToBeDeleted();
    this.d3.aboutToBeDeleted();
    this.e3.aboutToBeDeleted();
    this.f3.aboutToBeDeleted();
    this.g3.aboutToBeDeleted();
    this.h3.aboutToBeDeleted();
    this.i3.aboutToBeDeleted();
    this.w4.aboutToBeDeleted();
    this.l3.aboutToBeDeleted();
    this.m3.aboutToBeDeleted();
    this.x4.aboutToBeDeleted();
    this.z3.aboutToBeDeleted();
    this.y4.aboutToBeDeleted();
    this.w3.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get chipSize() {
    return this.n2.get();
  }
  set chipSize(newValue) {
    this.n2.set(newValue);
  }
  get allowClose() {
    return this.o2.get();
  }
  set allowClose(newValue) {
    this.o2.set(newValue);
  }
  get closeOptions() {
    return this.q2.get();
  }
  set closeOptions(newValue) {
    this.q2.set(newValue);
  }
  get chipDirection() {
    return this.s2.get();
  }
  set chipDirection(newValue) {
    this.s2.set(newValue);
  }
  get prefixIcon() {
    return this.t2.get();
  }
  set prefixIcon(newValue) {
    this.t2.set(newValue);
  }
  get prefixSymbol() {
    return this.u2.get();
  }
  set prefixSymbol(newValue) {
    this.u2.set(newValue);
  }
  get label() {
    return this.v2.get();
  }
  set label(newValue) {
    this.v2.set(newValue);
  }
  get suffixIcon() {
    return this.w2.get();
  }
  set suffixIcon(newValue) {
    this.w2.set(newValue);
  }
  get suffixSymbol() {
    return this.z2.get();
  }
  set suffixSymbol(newValue) {
    this.z2.set(newValue);
  }
  get suffixSymbolOptions() {
    return this.a3.get();
  }
  set suffixSymbolOptions(newValue) {
    this.a3.set(newValue);
  }
  get chipNodeBackgroundColor() {
    return this.b3.get();
  }
  set chipNodeBackgroundColor(newValue) {
    this.b3.set(newValue);
  }
  get chipNodeActivatedBackgroundColor() {
    return this.c3.get();
  }
  set chipNodeActivatedBackgroundColor(newValue) {
    this.c3.set(newValue);
  }
  get chipNodeRadius() {
    return this.d3.get();
  }
  set chipNodeRadius(newValue) {
    this.d3.set(newValue);
  }
  get chipEnabled() {
    return this.e3.get();
  }
  set chipEnabled(newValue) {
    this.e3.set(newValue);
  }
  get chipActivated() {
    return this.f3.get();
  }
  set chipActivated(newValue) {
    this.f3.set(newValue);
  }
  get chipAccessibilitySelectedType() {
    return this.g3.get();
  }
  set chipAccessibilitySelectedType(newValue) {
    this.g3.set(newValue);
  }
  get chipAccessibilityDescription() {
    return this.h3.get();
  }
  set chipAccessibilityDescription(newValue) {
    this.h3.set(newValue);
  }
  get chipAccessibilityLevel() {
    return this.i3.get();
  }
  set chipAccessibilityLevel(newValue) {
    this.i3.set(newValue);
  }
  get isChipExist() {
    return this.w4.get();
  }
  set isChipExist(newValue) {
    this.w4.set(newValue);
  }
  get chipScale() {
    return this.l3.get();
  }
  set chipScale(newValue) {
    this.l3.set(newValue);
  }
  get chipOpacity() {
    return this.m3.get();
  }
  set chipOpacity(newValue) {
    this.m3.set(newValue);
  }
  get suffixSymbolHeight() {
    return this.x4.get();
  }
  set suffixSymbolHeight(newValue) {
    this.x4.set(newValue);
  }
  get suffixSymbolWidth() {
    return this.z3.get();
  }
  set suffixSymbolWidth(newValue) {
    this.z3.set(newValue);
  }
  get breakPoint() {
    return this.y4.get();
  }
  set breakPoint(newValue) {
    this.y4.set(newValue);
  }
  get fontSizeScale() {
    return this.w3.get();
  }
  set fontSizeScale(newValue) {
    this.w3.set(newValue);
  }
  aboutToAppear() {
    this.smListener.on('change', (c5) => {
      if (c5.matches) {
        this.breakPoint = a1.SM;
      }
    });
    this.mdListener.on('change', (b5) => {
      if (b5.matches) {
        this.breakPoint = a1.MD;
      }
    });
    this.lgListener.on('change', (a5) => {
      if (a5.matches) {
        this.breakPoint = a1.LG;
      }
    });
    let z4 = this.getUIContext().getHostContext();
    if (z4) {
      this.fontSizeScale = z4.config?.fontSizeScale ?? 1;
      this.environmentCallbackID = z4
        .getApplicationContext()
        .on('environment', this.environmentCallback);
    }
  }
  aboutToDisappear() {
    this.smListener.off('change');
    this.mdListener.off('change');
    this.lgListener.off('change');
    if (this.environmentCallbackID) {
      this.getUIContext()
        .getHostContext()
        ?.getApplicationContext()
        .off('environment', this.environmentCallbackID);
      this.environmentCallbackID = void 0;
    }
  }
  ChipBuilder(parent = null) {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Button.createWithChild({ type: ButtonType.Normal });
      Button.clip(false);
      Button.padding(0);
      Button.focusable(true);
      Button.size(this.getChipSize());
      Button.enabled(this.isChipEnabled());
      Button.direction(this.chipDirection);
      Button.backgroundColor(this.getChipBackgroundColor());
      Button.borderRadius(this.getChipBorderRadius());
      Button.scale(ObservedObject.GetRawObject(this.chipScale));
      Button.opacity(this.chipOpacity);
      Button.accessibilityGroup(true);
      Button.accessibilityDescription(this.getAccessibilityDescription());
      Button.accessibilityLevel(this.getAccessibilityLevel());
      Button.accessibilityChecked(this.getAccessibilityChecked());
      Button.accessibilitySelected(this.getAccessibilitySelected());
      Button.onClick(this.getChipOnClicked());
      Button.onKeyEvent((event) => {
        if (
          event.type === KeyType.Down &&
          event.keyCode === KeyCode.KEYCODE_FORWARD_DEL
        ) {
          this.deleteChip();
        }
      });
    }, Button);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Flex.create({
        justifyContent: FlexAlign.Center,
        alignItems: ItemAlign.Center,
      });
      Flex.direction(this.chipDirection);
      Flex.padding(this.getChipPadding());
      Flex.size(this.getChipSize());
      Flex.constraintSize(this.getChipConstraintSize());
    }, Flex);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.hasPrefixSymbol()) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            SymbolGlyph.create();
            SymbolGlyph.fontSize(this.theme.m1.fontSize);
            SymbolGlyph.fontColor(this.getDefaultSymbolColor());
            SymbolGlyph.flexShrink(0);
            SymbolGlyph.attributeModifier.bind(this)(
              this.getPrefixSymbolModifier()
            );
            SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
            SymbolGlyph.symbolEffect(this.symbolEffect, false);
            SymbolGlyph.symbolEffect(this.symbolEffect, this.theme.m1.o1);
          }, SymbolGlyph);
        });
      } else if (this.prefixIcon?.src) {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(this.prefixIcon.src);
            Image.direction(this.chipDirection);
            Image.size(this.getPrefixIconSize());
            Image.fillColor(this.getPrefixIconFilledColor());
            Image.objectFit(ImageFit.Cover);
            Image.focusable(false);
            Image.flexShrink(0);
            Image.draggable(false);
          }, Image);
        });
      } else {
        this.ifElseBranchUpdateFunction(2, () => {});
      }
    }, If);
    If.pop();
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Text.create(this.getChipText());
      Text.draggable(false);
      Text.flexShrink(1);
      Text.focusable(true);
      Text.maxLines(1);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.textAlign(TextAlign.Center);
      Text.direction(this.chipDirection);
      Text.fontSize(this.getLabelFontSize());
      Text.fontColor(this.getLabelFontColor());
      Text.fontFamily(this.getLabelFontFamily());
      Text.fontWeight(this.getLabelFontWeight());
      Text.margin(this.getLabelMargin());
    }, Text);
    Text.pop();
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.hasSuffixSymbol()) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.onClick(this.getSuffixSymbolAction());
            Button.accessibilityText(this.getSuffixSymbolAccessibilityText());
            Button.accessibilityDescription(
              this.getSuffixSymbolAccessibilityDescription()
            );
            Button.accessibilityLevel(this.getSuffixSymbolAccessibilityLevel());
            Button.flexShrink(0);
            Button.backgroundColor(Color.Transparent);
            Button.borderRadius(0);
            Button.padding(0);
            Button.stateEffect(false);
            Button.hoverEffect(HoverEffect.None);
          }, Button);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            SymbolGlyph.create();
            SymbolGlyph.fontSize(this.theme.m1.fontSize);
            SymbolGlyph.fontColor(this.getDefaultSymbolColor());
            SymbolGlyph.attributeModifier.bind(this)(
              this.getSuffixSymbolModifier()
            );
            SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
            SymbolGlyph.symbolEffect(this.symbolEffect, false);
            SymbolGlyph.symbolEffect(this.symbolEffect, this.theme.m1.o1);
          }, SymbolGlyph);
          Button.pop();
        });
      } else if (this.suffixIcon?.src) {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.backgroundColor(Color.Transparent);
            Button.borderRadius(0);
            Button.padding(0);
            Button.flexShrink(0);
            Button.stateEffect(false);
            Button.hoverEffect(HoverEffect.None);
            Button.size(this.getSuffixIconSize());
            Button.accessibilityText(this.getSuffixIconAccessibilityText());
            Button.accessibilityDescription(
              this.getSuffixIconAccessibilityDescription()
            );
            Button.accessibilityLevel(this.getSuffixIconAccessibilityLevel());
            Button.onClick(this.getSuffixIconAction());
          }, Button);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(this.suffixIcon.src);
            Image.direction(this.chipDirection);
            Image.size(this.getSuffixIconSize());
            Image.fillColor(this.getSuffixIconFilledColor());
            Image.objectFit(ImageFit.Cover);
            Image.draggable(false);
          }, Image);
          Button.pop();
        });
      } else if (this.isClosable()) {
        this.ifElseBranchUpdateFunction(2, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.backgroundColor(Color.Transparent);
            Button.borderRadius(0);
            Button.padding(0);
            Button.flexShrink(0);
            Button.stateEffect(false);
            Button.hoverEffect(HoverEffect.None);
            Button.accessibilityText(this.getCloseIconAccessibilityText());
            Button.accessibilityDescription(
              this.getCloseIconAccessibilityDescription()
            );
            Button.accessibilityLevel(this.getCloseIconAccessibilityLevel());
            Button.onClick(() => {
              if (!this.isChipEnabled()) {
                return;
              }
              this.onClose?.();
              this.deleteChip();
            });
          }, Button);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            SymbolGlyph.create({
              id: -1,
              type: 40000,
              params: ['sys.symbol.xmark'],
              bundleName: '__harDefaultBundleName__',
              moduleName: '__harDefaultModuleName__',
            });
            SymbolGlyph.fontSize(this.theme.m1.fontSize);
            SymbolGlyph.fontColor(this.getDefaultSymbolColor());
          }, SymbolGlyph);
          Button.pop();
        });
      } else {
        this.ifElseBranchUpdateFunction(3, () => {});
      }
    }, If);
    If.pop();
    Flex.pop();
    Button.pop();
  }
  getCloseIconAccessibilityLevel() {
    if (
      this.closeOptions?.accessibilityLevel === 'no' ||
      this.closeOptions?.accessibilityLevel === 'no-hide-descendants'
    ) {
      return this.closeOptions.accessibilityLevel;
    }
    return 'yes';
  }
  getCloseIconAccessibilityDescription() {
    if (typeof this.closeOptions?.accessibilityDescription === 'undefined') {
      return void 0;
    }
    return this.closeOptions.accessibilityDescription;
  }
  getCloseIconAccessibilityText() {
    if (typeof this.closeOptions?.accessibilityText === 'undefined') {
      return {
        id: -1,
        type: 10003,
        params: ['sys.string.delete_used_for_accessibility_text'],
        bundleName: '__harDefaultBundleName__',
        moduleName: '__harDefaultModuleName__',
      };
    }
    return this.closeOptions.accessibilityText;
  }
  getSuffixIconAction() {
    if (this.suffixIcon?.src) {
      if (!this.suffixIcon?.action) {
        return void 0;
      }
      return () => {
        if (this.isChipEnabled()) {
          this.suffixIcon?.action?.();
        }
      };
    }
    return void 0;
  }
  getSuffixIconFilledColor() {
    if (this.isChipActivated()) {
      return (
        this.suffixIcon?.activatedFillColor ??
        this.theme.suffixIcon.activatedFillColor
      );
    }
    return this.suffixIcon?.fillColor ?? this.theme.suffixIcon.fillColor;
  }
  getSuffixIconSize() {
    let y4 = { width: 0, height: 0 };
    if (
      typeof this.suffixIcon?.size?.width !== 'undefined' &&
      this.isValidLength(this.suffixIcon.size.width)
    ) {
      y4.width = this.suffixIcon.size.width;
    } else {
      y4.width = this.theme.suffixIcon.size.width;
    }
    if (
      typeof this.suffixIcon?.size?.height !== 'undefined' &&
      this.isValidLength(this.suffixIcon.size.height)
    ) {
      y4.height = this.suffixIcon.size.height;
    } else {
      y4.height = this.theme.suffixIcon.size.height;
    }
    return y4;
  }
  getSuffixIconAccessibilityLevel() {
    if (
      this.suffixIcon?.accessibilityLevel === 'no' ||
      this.suffixIcon?.accessibilityLevel === 'no-hide-descendants'
    ) {
      return this.suffixIcon.accessibilityLevel;
    }
    return this.suffixIcon?.action ? 'yes' : 'no';
  }
  getSuffixIconAccessibilityDescription() {
    if (typeof this.suffixIcon?.accessibilityDescription === 'undefined') {
      return void 0;
    }
    return this.suffixIcon.accessibilityDescription;
  }
  getSuffixIconAccessibilityText() {
    if (typeof this.suffixIcon?.accessibilityText === 'undefined') {
      return void 0;
    }
    return this.suffixIcon.accessibilityText;
  }
  isClosable() {
    return this.allowClose ?? true;
  }
  getSuffixSymbolModifier() {
    if (this.isChipActivated()) {
      return this.suffixSymbol?.activated;
    }
    return this.suffixSymbol?.normal;
  }
  getSuffixSymbolAccessibilityLevel() {
    if (this.isChipActivated()) {
      if (
        this.suffixSymbolOptions?.activatedAccessibility?.accessibilityLevel ===
          'no' ||
        this.suffixSymbolOptions?.activatedAccessibility?.accessibilityLevel ===
          'no-hide-descendants'
      ) {
        return this.suffixSymbolOptions.activatedAccessibility
          .accessibilityLevel;
      }
      return this.suffixSymbolOptions?.action ? 'yes' : 'no';
    }
    if (
      this.suffixSymbolOptions?.normalAccessibility?.accessibilityLevel ===
        'no' ||
      this.suffixSymbolOptions?.normalAccessibility?.accessibilityLevel ===
        'no-hide-descendants'
    ) {
      return this.suffixSymbolOptions.normalAccessibility.accessibilityLevel;
    }
    return this.suffixSymbolOptions?.action ? 'yes' : 'no';
  }
  getSuffixSymbolAccessibilityDescription() {
    if (this.isChipActivated()) {
      if (
        typeof this.suffixSymbolOptions?.activatedAccessibility
          ?.accessibilityDescription !== 'undefined'
      ) {
        return this.suffixSymbolOptions.activatedAccessibility
          .accessibilityDescription;
      }
      return void 0;
    }
    if (
      typeof this.suffixSymbolOptions?.normalAccessibility
        ?.accessibilityDescription !== 'undefined'
    ) {
      return this.suffixSymbolOptions.normalAccessibility
        .accessibilityDescription;
    }
    return void 0;
  }
  getSuffixSymbolAccessibilityText() {
    if (this.isChipActivated()) {
      if (
        typeof this.suffixSymbolOptions?.activatedAccessibility
          ?.accessibilityText !== 'undefined'
      ) {
        return this.suffixSymbolOptions.activatedAccessibility
          .accessibilityText;
      }
      return void 0;
    }
    if (
      typeof this.suffixSymbolOptions?.normalAccessibility
        ?.accessibilityText !== 'undefined'
    ) {
      return this.suffixSymbolOptions.normalAccessibility.accessibilityText;
    }
    return void 0;
  }
  getSuffixSymbolAction() {
    if (typeof this.suffixSymbolOptions?.action === 'undefined') {
      return void 0;
    }
    return () => {
      if (!this.isChipEnabled()) {
        return;
      }
      this.suffixSymbolOptions?.action?.();
    };
  }
  hasSuffixSymbol() {
    return !!(this.suffixSymbol?.normal || this.suffixSymbol?.activated);
  }
  getPrefixIconFilledColor() {
    if (this.isChipActivated()) {
      return (
        this.prefixIcon?.activatedFillColor ??
        this.theme.prefixIcon.activatedFillColor
      );
    }
    return this.prefixIcon?.fillColor ?? this.theme.prefixIcon.fillColor;
  }
  getPrefixIconSize() {
    let x4 = { width: 0, height: 0 };
    if (
      typeof this.prefixIcon?.size?.width !== 'undefined' &&
      this.isValidLength(this.prefixIcon.size.width)
    ) {
      x4.width = this.prefixIcon.size.width;
    } else {
      x4.width = this.theme.prefixIcon.size.width;
    }
    if (
      typeof this.prefixIcon?.size?.height !== 'undefined' &&
      this.isValidLength(this.prefixIcon.size.height)
    ) {
      x4.height = this.prefixIcon.size.height;
    } else {
      x4.height = this.theme.prefixIcon.size.height;
    }
    return x4;
  }
  getPrefixSymbolModifier() {
    if (this.isChipActivated()) {
      return this.prefixSymbol?.activated;
    }
    return this.prefixSymbol?.normal;
  }
  getDefaultSymbolColor() {
    return this.isChipActivated()
      ? this.theme.m1.activatedFontColor
      : this.theme.m1.n1;
  }
  hasPrefixSymbol() {
    return !!(this.prefixSymbol?.normal || this.prefixSymbol?.activated);
  }
  getChipConstraintSize() {
    const constraintSize = {};
    if (typeof this.chipSize === 'string') {
      constraintSize.maxWidth = this.getChipMaxWidth();
      constraintSize.minHeight =
        this.chipSize === ChipSize.SMALL ? this.theme.q1.v1 : this.theme.q1.u1;
    } else {
      if (
        typeof this.chipSize?.width === 'undefined' ||
        !this.isValidLength(this.chipSize.width)
      ) {
        constraintSize.maxWidth = this.getChipMaxWidth();
      }
      if (
        typeof this.chipSize?.height === 'undefined' ||
        !this.isValidLength(this.chipSize.height)
      ) {
        constraintSize.minHeight = this.theme.q1.u1;
      }
    }
    return constraintSize;
  }
  getChipMaxWidth() {
    if (this.fontSizeScale >= this.theme.q1.s1) {
      return void 0;
    }
    if (this.breakPoint === a1.SM) {
      return this.theme.q1.g2.i2;
    }
    if (this.breakPoint === a1.MD) {
      return this.theme.q1.g2.j2;
    }
    if (this.breakPoint === a1.LG) {
      return this.theme.q1.g2.l2;
    }
    return void 0;
  }
  getChipSize() {
    const w4 = {
      width: 'auto',
      height: 'auto',
    };
    if (typeof this.chipSize !== 'string') {
      if (
        typeof this.chipSize?.width !== 'undefined' &&
        this.isValidLength(this.chipSize.width)
      ) {
        w4.width = this.chipSize.width;
      }
      if (
        typeof this.chipSize?.height !== 'undefined' &&
        this.isValidLength(this.chipSize.height)
      ) {
        w4.height = this.chipSize.height;
      }
    }
    return w4;
  }
  getChipPadding() {
    return this.isSmallChipSize() ? this.theme.q1.d2 : this.theme.q1.c2;
  }
  getLabelMargin() {
    const localizedLabelMargin = {
      start: LengthMetrics.vp(0),
      end: LengthMetrics.vp(0),
    };
    const u4 = this.isSmallChipSize()
      ? this.theme.label.j1
      : this.theme.label.i1;
    if (
      typeof this.label?.localizedLabelMargin?.start !== 'undefined' &&
      this.label.localizedLabelMargin.start.value >= 0
    ) {
      localizedLabelMargin.start = this.label.localizedLabelMargin.start;
    } else if (this.hasPrefix()) {
      localizedLabelMargin.start = u4.start;
    }
    if (
      typeof this.label?.localizedLabelMargin?.end !== 'undefined' &&
      this.label.localizedLabelMargin.end.value >= 0
    ) {
      localizedLabelMargin.end = this.label.localizedLabelMargin.end;
    } else if (this.hasSuffix()) {
      localizedLabelMargin.end = u4.end;
    }
    if (typeof this.label?.localizedLabelMargin === 'object') {
      return localizedLabelMargin;
    }
    if (typeof this.label.labelMargin === 'object') {
      const labelMargin = { left: 0, right: 0 };
      const v4 = this.isSmallChipSize()
        ? this.theme.label.h1
        : this.theme.label.g1;
      if (
        typeof this.label?.labelMargin?.left !== 'undefined' &&
        this.isValidLength(this.label.labelMargin.left)
      ) {
        labelMargin.left = this.label.labelMargin.left;
      } else if (this.hasPrefix()) {
        labelMargin.left = v4.left;
      }
      if (
        typeof this.label?.labelMargin?.right !== 'undefined' &&
        this.isValidLength(this.label.labelMargin.right)
      ) {
        labelMargin.right = this.label.labelMargin.right;
      } else if (this.hasSuffix()) {
        labelMargin.right = v4.right;
      }
      return labelMargin;
    }
    return localizedLabelMargin;
  }
  hasSuffix() {
    if (this.suffixIcon?.src) {
      return true;
    }
    return this.isChipActivated()
      ? !!this.suffixSymbol?.activated
      : !!this.suffixSymbol?.normal;
  }
  hasPrefix() {
    if (this.prefixIcon?.src) {
      return true;
    }
    return this.isChipActivated()
      ? !!this.prefixSymbol?.activated
      : !!this.prefixSymbol?.normal;
  }
  getLabelFontWeight() {
    return this.isChipActivated() ? FontWeight.Medium : FontWeight.Regular;
  }
  getLabelFontFamily() {
    return this.label?.fontFamily ?? this.theme.label.fontFamily;
  }
  getLabelFontColor() {
    if (this.isChipActivated()) {
      return (
        this.label?.activatedFontColor ?? this.theme.label.activatedFontColor
      );
    }
    return this.label?.fontColor ?? this.theme.label.fontColor;
  }
  getLabelFontSize() {
    if (
      typeof this.label.fontSize !== 'undefined' &&
      this.isValidLength(this.label.fontSize)
    ) {
      return this.label.fontSize;
    }
    if (this.isSmallChipSize()) {
      return this.theme.label.f1;
    }
    return this.theme.label.defaultFontSize;
  }
  getChipText() {
    return this.label?.text ?? '';
  }
  deleteChip() {
    Context.animateTo({ curve: Curve.Sharp, duration: 150 }, () => {
      this.chipOpacity = 0;
    });
    Context.animateTo(
      {
        curve: Curve.FastOutLinearIn,
        duration: 150,
        onFinish: () => {
          this.isChipExist = false;
        },
      },
      () => {
        this.chipScale = { x: 0.85, y: 0.85 };
      }
    );
  }
  getChipOnClicked() {
    if (this.onClicked) {
      return this.onClicked.bind(this);
    }
    return void 0;
  }
  getAccessibilitySelected() {
    if (
      this.getChipAccessibilitySelectedType() ===
      AccessibilitySelectedType.SELECTED
    ) {
      return this.isChipActivated();
    }
    return void 0;
  }
  getAccessibilityChecked() {
    if (
      this.getChipAccessibilitySelectedType() ===
      AccessibilitySelectedType.CHECKED
    ) {
      return this.isChipActivated();
    }
    return void 0;
  }
  getChipAccessibilitySelectedType() {
    if (typeof this.chipActivated === 'undefined') {
      return AccessibilitySelectedType.CLICKED;
    }
    return (
      this.chipAccessibilitySelectedType ?? AccessibilitySelectedType.CHECKED
    );
  }
  getAccessibilityLevel() {
    return this.chipAccessibilityLevel;
  }
  getAccessibilityDescription() {
    if (typeof this.chipAccessibilityDescription === 'undefined') {
      return void 0;
    }
    return this.chipAccessibilityDescription;
  }
  isChipEnabled() {
    return this.chipEnabled ?? true;
  }
  getChipBorderRadius() {
    if (
      typeof this.chipNodeRadius !== 'undefined' &&
      this.isValidLength(this.chipNodeRadius)
    ) {
      return this.chipNodeRadius;
    }
    return this.isSmallChipSize() ? this.theme.q1.b2 : this.theme.q1.a2;
  }
  isSmallChipSize() {
    return (
      typeof this.chipSize === 'string' && this.chipSize === ChipSize.SMALL
    );
  }
  getChipBackgroundColor() {
    if (this.isChipActivated()) {
      return this.getColor(
        this.chipNodeActivatedBackgroundColor,
        this.theme.q1.activatedBackgroundColor
      );
    }
    return this.getColor(
      this.chipNodeBackgroundColor,
      this.theme.q1.backgroundColor
    );
  }
  getColor(color, t4) {
    if (!color) {
      return t4;
    }
    try {
      ColorMetrics.resourceColor(color).color;
      return color;
    } catch (e) {
      console.error(`[Chip] failed to get color`);
      return Color.Transparent;
    }
  }
  isChipActivated() {
    return this.chipActivated ?? false;
  }
  isValidLength(length) {
    if (typeof length === 'number') {
      return length >= 0;
    } else if (typeof length === 'string') {
      return this.isValidLengthString(length);
    } else if (typeof length === 'object') {
      const resource = length;
      const resourceManager =
        this.getUIContext().getHostContext()?.resourceManager;
      if (!resourceManager) {
        console.error('[Chip] failed to get resourceManager.');
        return false;
      }
      switch (resource.type) {
        case t:
        case u:
          return resourceManager.getNumber(resource) >= 0;
        case o:
          return this.isValidLengthString(
            resourceManager.getStringSync(resource)
          );
        default:
          return false;
      }
    }
    return false;
  }
  isValidLengthString(length) {
    const matches = length.match(/(-?\d+(?:\.\d+)?)_?(fp|vp|px|lpx)?$/i);
    if (!matches || matches.length < 3) {
      return false;
    }
    return Number.parseInt(matches[1], 10) >= 0;
  }
  initialRender() {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.isChipExist) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.ChipBuilder.bind(this)();
        });
      } else {
        this.ifElseBranchUpdateFunction(1, () => {});
      }
    }, If);
    If.pop();
  }
  rerender() {
    this.updateDirtyElements();
  }
}

export default {
  Chip,
  ChipSize,
  AccessibilitySelectedType,
};
