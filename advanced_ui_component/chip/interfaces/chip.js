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
const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;
const measure = requireNapi('measure');
const mediaquery = requireNapi('mediaquery');
const resourceManager = requireNapi('resourceManager');
const componentUtils = requireNapi('arkui.componentUtils');
const hilog = requireNapi('hilog');
const ColorMetrics = requireNapi('arkui.node').ColorMetrics;
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const LengthUnit = requireNapi('arkui.node').LengthUnit;
const o = 10003;
const t = 10002;
const u = 10007;
export var ChipSize;
(function (ChipSize) {
  ChipSize['NORMAL'] = 'NORMAL';
  ChipSize['SMALL'] = 'SMALL';
})(ChipSize || (ChipSize = {}));
var a1;
(function (v1) {
  v1['SM'] = 'SM';
  v1['MD'] = 'MD';
  v1['LG'] = 'LG';
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
const c1 = () => {};
export function Chip(options, parent = null) {
  const u1 = options;
  {
    (parent ? parent : this).observeComponentCreation2(
      (elmtId, isInitialRender, options = u1) => {
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
              page: 'advancedComponents/src/main/ets/components/Chip.ets',
              line: 296,
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
function i(dimension, t1) {
  const matches = dimension.match(t1);
  if (!matches || matches.length < 3) {
    return false;
  }
  const value = Number.parseFloat(matches[1]);
  return value >= 0;
}
function j(dimension) {
  return i(
    dimension,
    new RegExp('(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$', 'i')
  );
}
function m(context, value) {
  const resourceManager = context?.resourceManager;
  if (value === void 0 || value === null || resourceManager === void 0) {
    return false;
  }
  if (value.type !== o && value.type !== u && value.type !== t) {
    return false;
  }
  if (value.type === u || value.type === t) {
    if (resourceManager.getNumber(value.id) >= 0) {
      return true;
    } else {
      return false;
    }
  }
  if (value.type === o && !j(resourceManager.getStringSync(value.id))) {
    return false;
  } else {
    return true;
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
    this.j3 = new ObservedPropertySimplePU(false, this, 'isHover');
    this.l3 = new ObservedPropertyObjectPU({ x: 1, y: 1 }, this, 'chipScale');
    this.m3 = new ObservedPropertySimplePU(1, this, 'chipOpacity');
    this.n3 = new ObservedPropertyObjectPU(
      Color.Transparent,
      this,
      'chipBlendColor'
    );
    this.q3 = new ObservedPropertySimplePU(false, this, 'deleteChip');
    this.r3 = new ObservedPropertySimplePU(false, this, 'chipNodeOnFocus');
    this.s3 = new ObservedPropertySimplePU(false, this, 'useDefaultSuffixIcon');
    this.chipNodeSize = {};
    this.onClose = c1;
    this.onClicked = c1;
    this.t3 = new ObservedPropertySimplePU(false, this, 'suffixIconOnFocus');
    this.u3 = new ObservedPropertySimplePU(a1.SM, this, 'chipBreakPoints');
    this.smListener = mediaquery.matchMediaSync(
      '(0vp<width) and (width<600vp)'
    );
    this.mdListener = mediaquery.matchMediaSync(
      '(600vp<=width) and (width<840vp)'
    );
    this.lgListener = mediaquery.matchMediaSync('(840vp<=width)');
    this.v3 = new ObservedPropertySimplePU(
      false,
      this,
      'isShowPressedBackGroundColor'
    );
    this.w3 = new ObservedPropertyObjectPU(0, this, 'fontSizeScale');
    this.x3 = new ObservedPropertyObjectPU(0, this, 'fontWeightScale');
    this.callbacks = {
      onConfigurationUpdated: (configuration) => {
        this.fontSizeScale = configuration.fontSizeScale;
        this.fontWeightScale = configuration.fontWeightScale;
      },
      onMemoryLevel() {},
    };
    this.callbackId = undefined;
    this.y3 = new ObservedPropertyObjectPU(
      this.toVp(
        componentUtils.getRectangleById('PrefixSymbolGlyph')?.size?.width
      ),
      this,
      'prefixSymbolWidth'
    );
    this.z3 = new ObservedPropertyObjectPU(
      this.toVp(
        componentUtils.getRectangleById('SuffixSymbolGlyph')?.size?.width
      ),
      this,
      'suffixSymbolWidth'
    );
    this.a4 = new ObservedPropertyObjectPU(
      this.toVp(
        componentUtils.getRectangleById('AllowCloseSymbolGlyph')?.size?.width
      ),
      this,
      'allowCloseSymbolWidth'
    );
    this.b4 = new ObservedPropertyObjectPU(
      new SymbolEffect(),
      this,
      'symbolEffect'
    );
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
    if (params.allowClose === undefined) {
      this.o2.set(true);
    }
    if (params.chipDirection === undefined) {
      this.s2.set(Direction.Auto);
    }
    if (params.prefixIcon === undefined) {
      this.t2.set({ src: '' });
    }
    if (params.label === undefined) {
      this.v2.set({ text: '' });
    }
    if (params.suffixIcon === undefined) {
      this.w2.set({ src: '' });
    }
    if (params.chipNodeBackgroundColor === undefined) {
      this.b3.set(this.theme.q1.backgroundColor);
    }
    if (params.chipNodeActivatedBackgroundColor === undefined) {
      this.c3.set(this.theme.q1.activatedBackgroundColor);
    }
    if (params.chipNodeRadius === undefined) {
      this.d3.set(void 0);
    }
    if (params.chipEnabled === undefined) {
      this.e3.set(true);
    }
    if (params.isHover !== undefined) {
      this.isHover = params.isHover;
    }
    if (params.chipScale !== undefined) {
      this.chipScale = params.chipScale;
    }
    if (params.chipOpacity !== undefined) {
      this.chipOpacity = params.chipOpacity;
    }
    if (params.chipBlendColor !== undefined) {
      this.chipBlendColor = params.chipBlendColor;
    }
    if (params.deleteChip !== undefined) {
      this.deleteChip = params.deleteChip;
    }
    if (params.chipNodeOnFocus !== undefined) {
      this.chipNodeOnFocus = params.chipNodeOnFocus;
    }
    if (params.useDefaultSuffixIcon !== undefined) {
      this.useDefaultSuffixIcon = params.useDefaultSuffixIcon;
    }
    if (params.chipNodeSize !== undefined) {
      this.chipNodeSize = params.chipNodeSize;
    }
    if (params.onClose !== undefined) {
      this.onClose = params.onClose;
    }
    if (params.onClicked !== undefined) {
      this.onClicked = params.onClicked;
    }
    if (params.suffixIconOnFocus !== undefined) {
      this.suffixIconOnFocus = params.suffixIconOnFocus;
    }
    if (params.chipBreakPoints !== undefined) {
      this.chipBreakPoints = params.chipBreakPoints;
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
    if (params.isShowPressedBackGroundColor !== undefined) {
      this.isShowPressedBackGroundColor = params.isShowPressedBackGroundColor;
    }
    if (params.fontSizeScale !== undefined) {
      this.fontSizeScale = params.fontSizeScale;
    }
    if (params.fontWeightScale !== undefined) {
      this.fontWeightScale = params.fontWeightScale;
    }
    if (params.callbacks !== undefined) {
      this.callbacks = params.callbacks;
    }
    if (params.callbackId !== undefined) {
      this.callbackId = params.callbackId;
    }
    if (params.prefixSymbolWidth !== undefined) {
      this.prefixSymbolWidth = params.prefixSymbolWidth;
    }
    if (params.suffixSymbolWidth !== undefined) {
      this.suffixSymbolWidth = params.suffixSymbolWidth;
    }
    if (params.allowCloseSymbolWidth !== undefined) {
      this.allowCloseSymbolWidth = params.allowCloseSymbolWidth;
    }
    if (params.symbolEffect !== undefined) {
      this.symbolEffect = params.symbolEffect;
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
    this.j3.purgeDependencyOnElmtId(rmElmtId);
    this.l3.purgeDependencyOnElmtId(rmElmtId);
    this.m3.purgeDependencyOnElmtId(rmElmtId);
    this.n3.purgeDependencyOnElmtId(rmElmtId);
    this.q3.purgeDependencyOnElmtId(rmElmtId);
    this.r3.purgeDependencyOnElmtId(rmElmtId);
    this.s3.purgeDependencyOnElmtId(rmElmtId);
    this.t3.purgeDependencyOnElmtId(rmElmtId);
    this.u3.purgeDependencyOnElmtId(rmElmtId);
    this.v3.purgeDependencyOnElmtId(rmElmtId);
    this.w3.purgeDependencyOnElmtId(rmElmtId);
    this.x3.purgeDependencyOnElmtId(rmElmtId);
    this.y3.purgeDependencyOnElmtId(rmElmtId);
    this.z3.purgeDependencyOnElmtId(rmElmtId);
    this.a4.purgeDependencyOnElmtId(rmElmtId);
    this.b4.purgeDependencyOnElmtId(rmElmtId);
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
    this.j3.aboutToBeDeleted();
    this.l3.aboutToBeDeleted();
    this.m3.aboutToBeDeleted();
    this.n3.aboutToBeDeleted();
    this.q3.aboutToBeDeleted();
    this.r3.aboutToBeDeleted();
    this.s3.aboutToBeDeleted();
    this.t3.aboutToBeDeleted();
    this.u3.aboutToBeDeleted();
    this.v3.aboutToBeDeleted();
    this.w3.aboutToBeDeleted();
    this.x3.aboutToBeDeleted();
    this.y3.aboutToBeDeleted();
    this.z3.aboutToBeDeleted();
    this.a4.aboutToBeDeleted();
    this.b4.aboutToBeDeleted();
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
  get isHover() {
    return this.j3.get();
  }
  set isHover(newValue) {
    this.j3.set(newValue);
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
  get chipBlendColor() {
    return this.n3.get();
  }
  set chipBlendColor(newValue) {
    this.n3.set(newValue);
  }
  get deleteChip() {
    return this.q3.get();
  }
  set deleteChip(newValue) {
    this.q3.set(newValue);
  }
  get chipNodeOnFocus() {
    return this.r3.get();
  }
  set chipNodeOnFocus(newValue) {
    this.r3.set(newValue);
  }
  get useDefaultSuffixIcon() {
    return this.s3.get();
  }
  set useDefaultSuffixIcon(newValue) {
    this.s3.set(newValue);
  }
  get suffixIconOnFocus() {
    return this.t3.get();
  }
  set suffixIconOnFocus(newValue) {
    this.t3.set(newValue);
  }
  get chipBreakPoints() {
    return this.u3.get();
  }
  set chipBreakPoints(newValue) {
    this.u3.set(newValue);
  }
  get isShowPressedBackGroundColor() {
    return this.v3.get();
  }
  set isShowPressedBackGroundColor(newValue) {
    this.v3.set(newValue);
  }
  get fontSizeScale() {
    return this.w3.get();
  }
  set fontSizeScale(newValue) {
    this.w3.set(newValue);
  }
  get fontWeightScale() {
    return this.x3.get();
  }
  set fontWeightScale(newValue) {
    this.x3.set(newValue);
  }
  get prefixSymbolWidth() {
    return this.y3.get();
  }
  set prefixSymbolWidth(newValue) {
    this.y3.set(newValue);
  }
  get suffixSymbolWidth() {
    return this.z3.get();
  }
  set suffixSymbolWidth(newValue) {
    this.z3.set(newValue);
  }
  get allowCloseSymbolWidth() {
    return this.a4.get();
  }
  set allowCloseSymbolWidth(newValue) {
    this.a4.set(newValue);
  }
  get symbolEffect() {
    return this.b4.get();
  }
  set symbolEffect(newValue) {
    this.b4.set(newValue);
  }
  isChipSizeEnum() {
    return typeof this.chipSize === 'string';
  }
  getLabelFontSize() {
    if (
      this.label?.fontSize !== void 0 &&
      this.toVp(this.label.fontSize) >= 0
    ) {
      return this.label.fontSize;
    } else {
      if (this.isChipSizeEnum() && this.chipSize === ChipSize.SMALL) {
        try {
          resourceManager
            .getSystemResourceManager()
            .getNumberByName(this.theme.label.f1.params[0].split('.')[2]);
          return this.theme.label.f1;
        } catch (error) {
          return this.theme.label.defaultFontSize;
        }
      } else {
        try {
          resourceManager
            .getSystemResourceManager()
            .getNumberByName(this.theme.label.e1.params[0].split('.')[2]);
          return this.theme.label.e1;
        } catch (error) {
          return this.theme.label.defaultFontSize;
        }
      }
    }
  }
  getLabelFontColor() {
    if (this.getChipActive()) {
      return (
        this.label?.activatedFontColor ?? this.theme.label.activatedFontColor
      );
    }
    return this.label?.fontColor ?? this.theme.label.fontColor;
  }
  getLabelFontFamily() {
    return this.label?.fontFamily ?? this.theme.label.fontFamily;
  }
  getLabelFontWeight() {
    if (this.getChipActive()) {
      return FontWeight.Medium;
    }
    return FontWeight.Regular;
  }
  lengthMetricsToVp(s1) {
    let defaultValue = 0;
    if (s1) {
      switch (s1.unit) {
        case LengthUnit.PX:
          return px2vp(s1.value);
        case LengthUnit.VP:
          return s1.value;
        case LengthUnit.FP:
          return px2vp(fp2px(s1.value));
        case LengthUnit.PERCENT:
          return Number.NEGATIVE_INFINITY;
        case LengthUnit.LPX:
          return px2vp(lpx2px(s1.value));
      }
    }
    return defaultValue;
  }
  toVp(value) {
    if (value === void 0) {
      return Number.NEGATIVE_INFINITY;
    }
    switch (typeof value) {
      case 'number':
        return value;
      case 'object':
        try {
          let q1 = this.lengthMetricsToVp(LengthMetrics.resource(value));
          if (q1 === 0 && !m(getContext(this), value)) {
            return Number.NEGATIVE_INFINITY;
          }
          return q1;
        } catch (error) {
          return Number.NEGATIVE_INFINITY;
        }
      case 'string':
        let p1 = new RegExp('(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$', 'i');
        let matches = value.match(p1);
        if (!matches) {
          return Number.NEGATIVE_INFINITY;
        }
        let length = Number(matches?.[1] ?? 0);
        let unit = matches?.[2] ?? 'vp';
        switch (unit.toLowerCase()) {
          case 'px':
            length = px2vp(length);
            break;
          case 'fp':
            length = px2vp(fp2px(length));
            break;
          case 'lpx':
            length = px2vp(lpx2px(length));
            break;
          case '%':
            length = Number.NEGATIVE_INFINITY;
            break;
          case 'vp':
            break;
          default:
            break;
        }
        return length;
      default:
        return Number.NEGATIVE_INFINITY;
    }
  }
  getLabelMargin() {
    let labelMargin = { left: 0, right: 0 };
    if (
      this.label?.labelMargin?.left !== void 0 &&
      this.toVp(this.label.labelMargin.left) >= 0
    ) {
      labelMargin.left = this.label?.labelMargin?.left;
    } else if (
      this.prefixSymbol?.normal ||
      this.prefixSymbol?.activated ||
      this.prefixIcon?.src
    ) {
      if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
        labelMargin.left = this.theme.label.h1.left;
      } else {
        labelMargin.left = this.theme.label.g1.left;
      }
    }
    if (
      this.label?.labelMargin?.right !== void 0 &&
      this.toVp(this.label.labelMargin.right) >= 0
    ) {
      labelMargin.right = this.label?.labelMargin?.right;
    } else if (
      this.suffixSymbol?.normal ||
      this.suffixSymbol?.activated ||
      this.suffixIcon?.src ||
      this.useDefaultSuffixIcon
    ) {
      if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
        labelMargin.right = this.theme.label.h1.right;
      } else {
        labelMargin.right = this.theme.label.g1.right;
      }
    }
    return labelMargin;
  }
  getLocalizedLabelMargin() {
    let localizedLabelMargin = {
      start: LengthMetrics.vp(0),
      end: LengthMetrics.vp(0),
    };
    if (
      this.label?.localizedLabelMargin?.start?.value !== void 0 &&
      this.lengthMetricsToVp(this.label.localizedLabelMargin.start) >= 0
    ) {
      localizedLabelMargin.start = this.label?.localizedLabelMargin?.start;
    } else if (
      this.prefixSymbol?.normal ||
      this.prefixSymbol?.activated ||
      this.prefixIcon?.src
    ) {
      if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
        localizedLabelMargin.start = this.theme.label.j1.start;
      } else {
        localizedLabelMargin.start = this.theme.label.i1.start;
      }
    }
    if (
      this.label?.localizedLabelMargin?.end?.value !== void 0 &&
      this.lengthMetricsToVp(this.label.localizedLabelMargin.end) >= 0
    ) {
      localizedLabelMargin.end = this.label?.localizedLabelMargin?.end;
    } else if (
      this.suffixSymbol?.normal ||
      this.suffixSymbol?.activated ||
      this.suffixIcon?.src ||
      this.useDefaultSuffixIcon
    ) {
      if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
        localizedLabelMargin.end = this.theme.label.j1.end;
      } else {
        localizedLabelMargin.end = this.theme.label.i1.end;
      }
    }
    return localizedLabelMargin;
  }
  getLabelStartEndVp() {
    let labelMargin = this.getLocalizedLabelMargin();
    if (
      this.label &&
      this.label.labelMargin !== void 0 &&
      this.label.localizedLabelMargin === void 0
    ) {
      let margin = this.getLabelMargin();
      return {
        start: LengthMetrics.vp(this.toVp(margin.left)),
        end: LengthMetrics.vp(this.toVp(margin.right)),
      };
    }
    return {
      start: LengthMetrics.vp(this.lengthMetricsToVp(labelMargin.start)),
      end: LengthMetrics.vp(this.lengthMetricsToVp(labelMargin.end)),
    };
  }
  getActualLabelMargin() {
    let localizedLabelMargin = this.getLocalizedLabelMargin();
    if (this.label && this.label.localizedLabelMargin !== void 0) {
      return localizedLabelMargin;
    }
    if (this.label && this.label.labelMargin !== void 0) {
      return this.getLabelMargin();
    }
    return localizedLabelMargin;
  }
  getSuffixIconSize() {
    let o1 = { width: 0, height: 0 };
    if (
      this.suffixIcon?.size?.width !== void 0 &&
      this.toVp(this.suffixIcon?.size?.width) >= 0
    ) {
      o1.width = this.suffixIcon?.size?.width;
    } else {
      if (this.getSuffixIconSrc()) {
        o1.width = this.theme.suffixIcon.size.width;
      } else {
        o1.width = 0;
      }
    }
    if (
      this.suffixIcon?.size?.height !== void 0 &&
      this.toVp(this.suffixIcon?.size?.height) >= 0
    ) {
      o1.height = this.suffixIcon?.size?.height;
    } else {
      if (this.getSuffixIconSrc()) {
        o1.height = this.theme.suffixIcon.size.height;
      } else {
        o1.height = 0;
      }
    }
    return o1;
  }
  getPrefixIconSize() {
    let n1 = { width: 0, height: 0 };
    if (
      this.prefixIcon?.size?.width !== void 0 &&
      this.toVp(this.prefixIcon?.size?.width) >= 0
    ) {
      n1.width = this.prefixIcon?.size?.width;
    } else {
      if (this.prefixIcon?.src) {
        n1.width = this.theme.prefixIcon.size.width;
      } else {
        n1.width = 0;
      }
    }
    if (
      this.prefixIcon?.size?.height !== void 0 &&
      this.toVp(this.prefixIcon?.size?.height) >= 0
    ) {
      n1.height = this.prefixIcon?.size?.height;
    } else {
      if (this.prefixIcon?.src) {
        n1.height = this.theme.prefixIcon.size.height;
      } else {
        n1.height = 0;
      }
    }
    return n1;
  }
  getPrefixIconFilledColor() {
    if (this.getChipActive()) {
      return (
        this.prefixIcon?.activatedFillColor ??
        this.theme.prefixIcon.activatedFillColor
      );
    }
    return this.prefixIcon?.fillColor ?? this.theme.prefixIcon.fillColor;
  }
  getSuffixIconFilledColor() {
    if (this.getChipActive()) {
      return (
        this.suffixIcon?.activatedFillColor ??
        this.theme.suffixIcon.activatedFillColor
      );
    }
    return this.suffixIcon?.fillColor ?? this.theme.suffixIcon.fillColor;
  }
  getDefaultSymbolColor() {
    if (this.getChipActive()) {
      return this.theme.m1.activatedFontColor;
    }
    return this.theme.m1.n1;
  }
  getPrefixSymbolModifier() {
    if (this.getChipActive()) {
      return this.prefixSymbol?.activated;
    }
    return this.prefixSymbol?.normal;
  }
  getSuffixSymbolModifier() {
    if (this.getChipActive()) {
      return this.suffixSymbol?.activated;
    }
    return this.suffixSymbol?.normal;
  }
  getSuffixIconFocusable() {
    return (
      (this.useDefaultSuffixIcon && (this.allowClose ?? true)) ||
      this.suffixIcon?.action !== void 0
    );
  }
  getChipNodePadding() {
    return this.isChipSizeEnum() && this.chipSize === ChipSize.SMALL
      ? this.theme.q1.d2
      : this.theme.q1.c2;
  }
  getChipNodeRadius() {
    if (this.chipNodeRadius !== void 0 && this.toVp(this.chipNodeRadius) >= 0) {
      return this.chipNodeRadius;
    } else {
      return this.isChipSizeEnum() && this.chipSize === ChipSize.SMALL
        ? this.theme.q1.b2
        : this.theme.q1.a2;
    }
  }
  getChipNodeBackGroundColor() {
    let l1;
    if (this.getChipActive()) {
      l1 =
        this.chipNodeActivatedBackgroundColor ??
        this.theme.q1.activatedBackgroundColor;
    } else {
      l1 = this.chipNodeBackgroundColor ?? this.theme.q1.backgroundColor;
    }
    let m1;
    try {
      m1 = ColorMetrics.resourceColor(l1);
    } catch (err) {
      hilog.error(
        0x3900,
        'Ace',
        `Chip resourceColor, error: ${err.toString()}`
      );
      m1 = ColorMetrics.resourceColor(Color.Transparent);
    }
    if (!this.isShowPressedBackGroundColor) {
      return m1.color;
    }
    return m1.blendColor(ColorMetrics.resourceColor('#19000000')).color;
  }
  getChipNodeHeight() {
    if (this.isChipSizeEnum()) {
      return this.chipSize === ChipSize.SMALL
        ? this.theme.q1.v1
        : this.theme.q1.u1;
    } else {
      this.chipNodeSize = this.chipSize;
      return this.chipNodeSize?.height !== void 0 &&
        this.toVp(this.chipNodeSize?.height) >= 0
        ? this.toVp(this.chipNodeSize?.height)
        : this.theme.q1.u1;
    }
  }
  getLabelWidth() {
    return px2vp(
      measure.measureText({
        textContent: this.label?.text ?? '',
        fontSize: this.getLabelFontSize(),
        fontFamily: this.label?.fontFamily ?? this.theme.label.fontFamily,
        fontWeight: this.getLabelFontWeight(),
        maxLines: 1,
        overflow: TextOverflow.Ellipsis,
        textAlign: TextAlign.Center,
      })
    );
  }
  getCalculateChipNodeWidth() {
    let j1 = 0;
    let k1 = this.getLabelStartEndVp();
    j1 += this.getChipNodePadding().start?.value ?? 0;
    j1 += this.toVp(this.getPrefixChipWidth());
    j1 += this.toVp(k1.start?.value ?? 0);
    j1 += this.getLabelWidth();
    j1 += this.toVp(k1.end?.value ?? 0);
    j1 += this.toVp(this.getSuffixChipWidth());
    j1 += this.getChipNodePadding().end?.value ?? 0;
    return j1;
  }
  getPrefixChipWidth() {
    if (this.prefixSymbol?.normal || this.prefixSymbol?.activated) {
      return this.prefixSymbolWidth;
    } else if (this.prefixIcon?.src) {
      return this.getPrefixIconSize().width;
    } else {
      return 0;
    }
  }
  getSuffixChipWidth() {
    if (this.suffixSymbol?.normal || this.suffixSymbol?.activated) {
      return this.suffixSymbolWidth;
    } else if (this.suffixIcon?.src) {
      return this.getSuffixIconSize().width;
    } else if (!this.suffixIcon?.src && (this.allowClose ?? true)) {
      return this.allowCloseSymbolWidth;
    } else {
      return 0;
    }
  }
  getReserveChipNodeWidth() {
    return (
      this.getCalculateChipNodeWidth() - this.getLabelWidth() + this.theme.q1.t1
    );
  }
  getChipEnable() {
    return this.chipEnabled || this.chipEnabled === void 0;
  }
  getChipActive() {
    if (typeof this.chipActivated === 'undefined') {
      return false;
    }
    return this.chipActivated;
  }
  getChipNodeOpacity() {
    return this.chipOpacity;
  }
  handleTouch(event) {
    if (!this.getChipEnable()) {
      return;
    }
    if (this.isHover) {
      if (event.type === TouchType.Down || event.type === TouchType.Move) {
        this.isShowPressedBackGroundColor = true;
      } else if (event.type === TouchType.Up) {
        this.isShowPressedBackGroundColor = false;
      } else {
        this.isShowPressedBackGroundColor = false;
      }
    } else {
      if (event.type === TouchType.Down || event.type === TouchType.Move) {
        this.isShowPressedBackGroundColor = true;
      } else if (event.type === TouchType.Up) {
        this.isShowPressedBackGroundColor = false;
      } else {
        this.isShowPressedBackGroundColor = false;
      }
    }
  }
  hoverAnimate(isHover) {
    if (!this.getChipEnable()) {
      return;
    }
    this.isHover = isHover;
    if (this.isHover) {
      this.isShowPressedBackGroundColor = true;
    } else {
      this.isShowPressedBackGroundColor = false;
    }
  }
  deleteChipNodeAnimate() {
    Context.animateTo({ duration: 150, curve: Curve.Sharp }, () => {
      this.chipOpacity = 0;
      this.chipBlendColor = Color.Transparent;
    });
    Context.animateTo(
      {
        duration: 150,
        curve: Curve.FastOutLinearIn,
        onFinish: () => {
          this.deleteChip = true;
        },
      },
      () => {
        this.chipScale = { x: 0.85, y: 0.85 };
      }
    );
  }
  getSuffixIconSrc() {
    this.useDefaultSuffixIcon =
      !this.suffixIcon?.src && (this.allowClose ?? true);
    return this.useDefaultSuffixIcon
      ? this.theme.suffixIcon.l1
      : this.suffixIcon?.src ?? void 0;
  }
  getChipNodeWidth() {
    if (!this.isChipSizeEnum()) {
      this.chipNodeSize = this.chipSize;
      if (
        this.chipNodeSize?.width !== void 0 &&
        this.toVp(this.chipNodeSize.width) >= 0
      ) {
        return this.toVp(this.chipNodeSize.width);
      }
    }
    let constraintWidth = this.getChipConstraintWidth();
    return Math.min(
      Math.max(this.getCalculateChipNodeWidth(), constraintWidth.minWidth),
      constraintWidth.maxWidth
    );
  }
  getFocusOverlaySize() {
    return {
      width:
        Math.max(
          this.getChipNodeWidth(),
          this.getChipConstraintWidth().minWidth
        ) + 8,
      height: this.getChipNodeHeight() + 8,
    };
  }
  getChipConstraintWidth() {
    let i1 = this.getReserveChipNodeWidth();
    let constraintWidth = this.getCalculateChipNodeWidth();
    let constraintSize;
    switch (this.chipBreakPoints) {
      case a1.SM:
        constraintSize = {
          minWidth: i1,
          maxWidth: Math.min(constraintWidth, this.theme.q1.g2.i2),
        };
        break;
      case a1.MD:
        constraintSize = {
          minWidth: Math.max(constraintWidth, this.theme.q1.g2.h2),
          maxWidth: Math.min(constraintWidth, this.theme.q1.g2.j2),
        };
        break;
      case a1.LG:
        constraintSize = {
          minWidth: Math.max(constraintWidth, this.theme.q1.g2.h2),
          maxWidth: Math.min(constraintWidth, this.theme.q1.g2.l2),
        };
        break;
      default:
        constraintSize = { minWidth: i1, maxWidth: constraintWidth };
        break;
    }
    constraintSize.minWidth = Math.min(
      Math.max(this.getCalculateChipNodeWidth(), constraintSize.minWidth),
      constraintSize.maxWidth
    );
    constraintSize.minHeight = this.getChipNodeHeight();
    if (
      !this.isChipSizeEnum() &&
      this.chipNodeSize?.height !== void 0 &&
      this.toVp(this.chipNodeSize?.height) >= 0
    ) {
      constraintSize.maxHeight = this.toVp(this.chipNodeSize.height);
      constraintSize.minHeight = this.toVp(this.chipNodeSize.height);
    }
    if (
      !this.isChipSizeEnum() &&
      this.chipNodeSize?.width !== void 0 &&
      this.toVp(this.chipNodeSize?.width) >= 0
    ) {
      constraintSize.minWidth = this.toVp(this.chipNodeSize.width);
      constraintSize.maxWidth = this.toVp(this.chipNodeSize.width);
    } else if (this.toVp(this.fontSizeScale) >= this.theme.q1.s1) {
      constraintSize.minWidth = void 0;
      constraintSize.maxWidth = void 0;
    }
    return constraintSize;
  }
  focusOverlay(parent = null) {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Stack.create();
      Stack.direction(this.chipDirection);
      Stack.size({ width: 1, height: 1 });
      Stack.align(Alignment.Center);
    }, Stack);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.chipNodeOnFocus && !this.suffixIconOnFocus) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.direction(this.chipDirection);
            Stack.borderRadius(this.toVp(this.getChipNodeRadius()) + 4);
            Stack.size(this.getFocusOverlaySize());
            Stack.borderColor(this.theme.q1.w1);
            Stack.borderWidth(this.theme.q1.borderWidth);
          }, Stack);
          Stack.pop();
        });
      } else {
        this.ifElseBranchUpdateFunction(1, () => {});
      }
    }, If);
    If.pop();
    Stack.pop();
  }
  aboutToAppear() {
    let e1 = this.getUIContext();
    this.fontSizeScale = e1.getHostContext()?.config?.fontSizeScale ?? 1;
    this.smListener.on('change', (h1) => {
      if (h1.matches) {
        this.chipBreakPoints = a1.SM;
      }
    });
    this.mdListener.on('change', (g1) => {
      if (g1.matches) {
        this.chipBreakPoints = a1.MD;
      }
    });
    this.lgListener.on('change', (f1) => {
      if (f1.matches) {
        this.chipBreakPoints = a1.LG;
      }
    });
    this.callbackId = this.getUIContext()
      .getHostContext()
      ?.getApplicationContext()
      ?.on('environment', this.callbacks);
  }
  getVisibility() {
    if (this.toVp(this.getChipNodeHeight()) > 0) {
      return Visibility.Visible;
    } else {
      return Visibility.None;
    }
  }
  aboutToDisappear() {
    this.smListener.off('change');
    this.mdListener.off('change');
    this.lgListener.off('change');
    if (this.callbackId) {
      this.getUIContext()
        .getHostContext()
        ?.getApplicationContext()
        ?.off('environment', this.callbackId);
      this.callbackId = void 0;
    }
  }
  chipBuilder(parent = null) {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Button.createWithChild();
      Button.constraintSize(this.getChipConstraintWidth());
      Button.direction(this.chipDirection);
      Button.type(ButtonType.Normal);
      Button.clip(false);
      Button.backgroundColor(this.getChipNodeBackGroundColor());
      Button.borderRadius(this.getChipNodeRadius());
      Button.enabled(this.getChipEnable());
      Button.scale(ObservedObject.GetRawObject(this.chipScale));
      Button.focusable(true);
      Button.opacity(this.getChipNodeOpacity());
      Button.padding(0);
      Button.accessibilityGroup(true);
      Button.accessibilityDescription(this.getAccessibilityDescription());
      Button.accessibilityLevel(this.getAccessibilityLevel());
      Button.accessibilityChecked(this.getAccessibilityChecked());
      Button.accessibilitySelected(this.getAccessibilitySelected());
      Button.onFocus(() => {
        this.chipNodeOnFocus = true;
      });
      Button.onBlur(() => {
        this.chipNodeOnFocus = false;
      });
      Button.onTouch((event) => {
        this.handleTouch(event);
      });
      Button.onHover((isHover) => {
        if (isHover) {
          this.isShowPressedBackGroundColor = true;
        } else {
          if (!this.isShowPressedBackGroundColor && isHover) {
            this.isShowPressedBackGroundColor = true;
          } else {
            this.isShowPressedBackGroundColor = false;
          }
        }
      });
      Button.onKeyEvent((event) => {
        if (
          event.type === KeyType.Down &&
          event.keyCode === KeyCode.KEYCODE_FORWARD_DEL &&
          !this.suffixIconOnFocus
        ) {
          this.deleteChipNodeAnimate();
        }
      });
      Button.onClick(
        this.onClicked === c1 ? undefined : this.onClicked.bind(this)
      );
    }, Button);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Row.create();
      Row.direction(this.chipDirection);
      Row.alignItems(VerticalAlign.Center);
      Row.justifyContent(FlexAlign.Center);
      Row.padding(this.getChipNodePadding());
      Row.constraintSize(this.getChipConstraintWidth());
    }, Row);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.prefixSymbol?.normal || this.prefixSymbol?.activated) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            SymbolGlyph.create();
            SymbolGlyph.fontSize(this.theme.m1.fontSize);
            SymbolGlyph.fontColor(this.getDefaultSymbolColor());
            SymbolGlyph.attributeModifier.bind(this)(
              this.getPrefixSymbolModifier()
            );
            SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
            SymbolGlyph.symbolEffect(
              ObservedObject.GetRawObject(this.symbolEffect),
              false
            );
            SymbolGlyph.symbolEffect(
              ObservedObject.GetRawObject(this.symbolEffect),
              this.theme.m1.o1
            );
            SymbolGlyph.onSizeChange((oldValue, newValue) => {
              this.prefixSymbolWidth = newValue?.width;
            });
            SymbolGlyph.key('PrefixSymbolGlyph');
          }, SymbolGlyph);
        });
      } else if (this.prefixIcon?.src !== '') {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(this.prefixIcon?.src);
            Image.direction(this.chipDirection);
            Image.opacity(this.getChipNodeOpacity());
            Image.size(this.getPrefixIconSize());
            Image.fillColor(this.getPrefixIconFilledColor());
            Image.enabled(this.getChipEnable());
            Image.objectFit(ImageFit.Cover);
            Image.focusable(false);
            Image.flexShrink(0);
            Image.visibility(this.getVisibility());
            Image.draggable(false);
          }, Image);
        });
      } else {
        this.ifElseBranchUpdateFunction(2, () => {});
      }
    }, If);
    If.pop();
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Text.create(this.label?.text ?? '');
      Text.direction(this.chipDirection);
      Text.opacity(this.getChipNodeOpacity());
      Text.fontSize(this.getLabelFontSize());
      Text.fontColor(this.getLabelFontColor());
      Text.fontFamily(this.getLabelFontFamily());
      Text.fontWeight(this.getLabelFontWeight());
      Text.margin(this.getActualLabelMargin());
      Text.enabled(this.getChipEnable());
      Text.maxLines(1);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.flexShrink(1);
      Text.focusable(true);
      Text.textAlign(TextAlign.Center);
      Text.visibility(this.getVisibility());
      Text.draggable(false);
    }, Text);
    Text.pop();
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.suffixSymbol?.normal || this.suffixSymbol?.activated) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.onClick(this.getSuffixSymbolAction());
            Button.accessibilityText(this.getSuffixSymbolAccessibilityText());
            Button.accessibilityDescription(
              this.getSuffixSymbolAccessibilityDescription()
            );
            Button.accessibilityLevel(this.getSuffixSymbolAccessibilityLevel());
            Button.backgroundColor(Color.Transparent);
            Button.borderRadius(0);
            Button.padding(0);
            Button.stateEffect(false);
          }, Button);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            SymbolGlyph.create();
            SymbolGlyph.fontSize(this.theme.m1.fontSize);
            SymbolGlyph.fontColor(this.getDefaultSymbolColor());
            SymbolGlyph.attributeModifier.bind(this)(
              this.getSuffixSymbolModifier()
            );
            SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
            SymbolGlyph.symbolEffect(
              ObservedObject.GetRawObject(this.symbolEffect),
              false
            );
            SymbolGlyph.symbolEffect(
              ObservedObject.GetRawObject(this.symbolEffect),
              this.theme.m1.o1
            );
            SymbolGlyph.onSizeChange((oldValue, newValue) => {
              this.suffixSymbolWidth = newValue?.width;
            });
            SymbolGlyph.key('SuffixSymbolGlyph');
          }, SymbolGlyph);
          Button.pop();
        });
      } else if (this.suffixIcon?.src !== '') {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.backgroundColor(Color.Transparent);
            Button.borderRadius(0);
            Button.padding(0);
            Button.size(this.getSuffixIconSize());
            Button.accessibilityText(this.getSuffixIconAccessibilityText());
            Button.accessibilityDescription(
              this.getSuffixIconAccessibilityDescription()
            );
            Button.accessibilityLevel(this.getSuffixIconAccessibilityLevel());
            Button.onClick(() => {
              if (!this.getChipEnable()) {
                return;
              }
              if (this.suffixIcon?.action) {
                this.suffixIcon.action();
                return;
              }
              if ((this.allowClose ?? true) && this.useDefaultSuffixIcon) {
                this.onClose();
                this.deleteChipNodeAnimate();
                return;
              }
              this.onClicked();
            });
            Button.focusable(this.getSuffixIconFocusable());
          }, Button);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(this.getSuffixIconSrc());
            Image.direction(this.chipDirection);
            Image.opacity(this.getChipNodeOpacity());
            Image.size(this.getSuffixIconSize());
            Image.fillColor(this.getSuffixIconFilledColor());
            Image.enabled(this.getChipEnable());
            Image.objectFit(ImageFit.Cover);
            Image.flexShrink(0);
            Image.visibility(this.getVisibility());
            Image.draggable(false);
            Image.onFocus(() => {
              this.suffixIconOnFocus = true;
            });
            Image.onBlur(() => {
              this.suffixIconOnFocus = false;
            });
          }, Image);
          Button.pop();
        });
      } else if (this.allowClose ?? true) {
        this.ifElseBranchUpdateFunction(2, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.backgroundColor(Color.Transparent);
            Button.borderRadius(0);
            Button.padding(0);
            Button.accessibilityText(this.getCloseIconAccessibilityText());
            Button.accessibilityDescription(
              this.getCloseIconAccessibilityDescription()
            );
            Button.accessibilityLevel(this.getCloseIconAccessibilityLevel());
            Button.onClick(() => {
              if (!this.getChipEnable()) {
                return;
              }
              this.onClose();
              this.deleteChipNodeAnimate();
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
            SymbolGlyph.onSizeChange((oldValue, newValue) => {
              this.allowCloseSymbolWidth = newValue?.width;
            });
            SymbolGlyph.key('AllowCloseSymbolGlyph');
          }, SymbolGlyph);
          Button.pop();
        });
      } else {
        this.ifElseBranchUpdateFunction(3, () => {});
      }
    }, If);
    If.pop();
    Row.pop();
    Button.pop();
  }
  getSuffixSymbolAccessibilityLevel() {
    if (this.getChipActive()) {
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
    if (this.getChipActive()) {
      if (
        typeof this.suffixSymbolOptions?.activatedAccessibility
          ?.accessibilityDescription !== 'undefined'
      ) {
        return this.suffixSymbolOptions.activatedAccessibility
          .accessibilityDescription;
      }
      return undefined;
    }
    if (
      typeof this.suffixSymbolOptions?.normalAccessibility
        ?.accessibilityDescription !== 'undefined'
    ) {
      return this.suffixSymbolOptions.normalAccessibility
        .accessibilityDescription;
    }
    return undefined;
  }
  getSuffixSymbolAccessibilityText() {
    if (this.getChipActive()) {
      if (
        typeof this.suffixSymbolOptions?.activatedAccessibility
          ?.accessibilityText !== 'undefined'
      ) {
        return this.suffixSymbolOptions.activatedAccessibility
          .accessibilityText;
      }
      return undefined;
    }
    if (
      typeof this.suffixSymbolOptions?.normalAccessibility
        ?.accessibilityText !== 'undefined'
    ) {
      return this.suffixSymbolOptions.normalAccessibility.accessibilityText;
    }
    return undefined;
  }
  getSuffixSymbolAction() {
    if (typeof this.suffixSymbolOptions?.action === 'undefined') {
      return undefined;
    }
    return () => {
      if (!this.getChipEnable()) {
        return;
      }
      this.suffixSymbolOptions?.action?.();
    };
  }
  getAccessibilitySelected() {
    if (
      this.getChipAccessibilitySelectedType() ===
      AccessibilitySelectedType.SELECTED
    ) {
      return this.getChipActive();
    }
    return undefined;
  }
  getAccessibilityChecked() {
    if (
      this.getChipAccessibilitySelectedType() ===
      AccessibilitySelectedType.CHECKED
    ) {
      return this.getChipActive();
    }
    return undefined;
  }
  getChipAccessibilitySelectedType() {
    if (typeof this.chipActivated === 'undefined') {
      return AccessibilitySelectedType.CLICKED;
    }
    return (
      this.chipAccessibilitySelectedType ?? AccessibilitySelectedType.CHECKED
    );
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
      return undefined;
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
      return undefined;
    }
    return this.suffixIcon.accessibilityDescription;
  }
  getSuffixIconAccessibilityText() {
    if (typeof this.suffixIcon?.accessibilityText === 'undefined') {
      return undefined;
    }
    return this.suffixIcon.accessibilityText;
  }
  getAccessibilityLevel() {
    return this.chipAccessibilityLevel;
  }
  getAccessibilityDescription() {
    if (typeof this.chipAccessibilityDescription === 'undefined') {
      return undefined;
    }
    return this.chipAccessibilityDescription;
  }
  initialRender() {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (!this.deleteChip) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.chipBuilder.bind(this)();
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
