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

const LayeredDrawableDescriptor = requireNapi('arkui.drawableDescriptor').LayeredDrawableDescriptor;
const TITLE_ICON_SIZE = '20vp';
const TITLE_PADDING_START = '20vp';
const TITLE_ELEMENT_MARGIN_HORIZONTAL = '12vp';
const TITLE_TEXT_FONT_SIZE = '16fp';
const TITLE_TEXT_FONT_WEIGHT = '500px';
const TITLE_ROW_HEIGHT = '37vp'
export class Index extends ViewPU {
  constructor(parent, params, __localStorage, elmtId = -1) {
    super(parent, __localStorage, elmtId);
    this.__appLabel = new ObservedPropertySimplePU('', this, 'appLabel');
    this.__appTitle = new ObservedPropertySimplePU('', this, 'appTitle');
    this.__textColor = new ObservedPropertySimplePU(0x66000000, this, 'textColor');
    this.__pixelMap = new ObservedPropertyObjectPU(undefined, this, 'pixelMap');
    this.__iconOpacity = new ObservedPropertySimplePU(0.4, this, 'iconOpacity');
    this.setInitiallyProvidedValue(params);
  }
  setInitiallyProvidedValue(params) {
    if (params.textColor !== undefined) {
      this.textColor = params.textColor;
    }
    if (params.appLabel !== undefined) {
      this.appLabel = params.appLabel;
    }
    if (params.appTitle !== undefined) {
      this.appTitle = params.appTitle;
    }
    if (params.pixelMap !== undefined) {
      this.pixelMap = params.pixelMap;
    }
    if (params.iconOpacity !== undefined) {
      this.iconOpacity = params.iconOpacity;
    }
  }
  updateStateVars(params) {
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
    this.__textColor.purgeDependencyOnElmtId(rmElmtId);
    this.__appLabel.purgeDependencyOnElmtId(rmElmtId);
    this.__appTitle.purgeDependencyOnElmtId(rmElmtId);
    this.__pixelMap.purgeDependencyOnElmtId(rmElmtId);
    this.__iconOpacity.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
    this.__textColor.aboutToBeDeleted();
    this.__appLabel.aboutToBeDeleted();
    this.__appTitle.aboutToBeDeleted();
    this.__pixelMap.aboutToBeDeleted();
    this.__iconOpacity.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get textColor() {
    return this.__textColor.get();
  }
  set textColor(newValue) {
    this.__textColor.set(newValue);
  }
  get appLabel() {
    return this.__appLabel.get();
  }
  set appLabel(newValue) {
    this.__appLabel.set(newValue);
  }
  get appTitle() {
    return this.__appTitle.get();
  }
  set appTitle(newValue) {
      this.__appTitle.set(newValue);
  }
  get pixelMap() {
    return this.__pixelMap.get();
  }
  set pixelMap(newValue) {
    this.__pixelMap.set(newValue);
  }
  get iconOpacity() {
    return this.__iconOpacity.get();
  }
  set iconOpacity(newValue) {
    this.__iconOpacity.set(newValue);
  }
  onWindowFocused() {
    this.textColor = { "id": 125829186, "type": 10001, params: [], "bundleName": "", "moduleName": "" };
    this.iconOpacity = 1;
  }
  onWindowUnfocused() {
    this.textColor = { "id": 125829186, "type": 10001, params: [], "bundleName": "", "moduleName": "" };
    this.iconOpacity = 0.4;
  }
  setAppTitle(content) {
    this.appTitle = content;
  }
  setAppIcon(pixelMap) {
    this.pixelMap = pixelMap;
  }
  initialRender() {
    this.observeComponentCreation((elmtId, isInitialRender) => {
      ViewStackProcessor.StartGetAccessRecordingFor(elmtId);
      Row.create();
      Row.width('100%');
      Row.height(TITLE_ROW_HEIGHT);
      Row.justifyContent(FlexAlign.Start);
      Row.alignItems(VerticalAlign.Center);
      Row.padding({ top: 6, bottom: 6, left: 8, right: 8 });
      Row.clip(true);
      if (!isInitialRender) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((elmtId, isInitialRender) => {
      ViewStackProcessor.StartGetAccessRecordingFor(elmtId);
      Image.create(this.pixelMap);
      Image.id('enhanceAppIcon');
      Image.height(TITLE_ICON_SIZE);
      Image.width(TITLE_ICON_SIZE);
      Image.interpolation(ImageInterpolation.Medium);
      Image.focusable(false);
      Image.margin({ left: TITLE_ELEMENT_MARGIN_HORIZONTAL, right: TITLE_ELEMENT_MARGIN_HORIZONTAL });
      Image.opacity(this.iconOpacity);
      Image.draggable(false);
      if (!isInitialRender) {
        Image.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((elmtId, isInitialRender) => {
      ViewStackProcessor.StartGetAccessRecordingFor(elmtId);
      Text.create(this.appTitle ? this.appTitle : this.appLabel);
      Image.id('enhanceAppLabel');
      Text.maxLines(1);
      Text.fontSize(TITLE_TEXT_FONT_SIZE);
      Text.fontColor(this.textColor);
      Text.fontWeight(TITLE_TEXT_FONT_WEIGHT);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.textAlign(TextAlign.Start);
      Text.layoutWeight(1.0);
      Text.opacity(this.iconOpacity);
      Text.minFontScale(0.85);
      Text.maxFontScale(1.45);
      if (!isInitialRender) {
        Text.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Text.pop();
    Row.pop();
  }
  rerender() {
    this.updateDirtyElements();
  }
}
ViewStackProcessor.StartGetAccessRecordingFor(ViewStackProcessor.AllocateNewElmetIdForNextComponent());
loadCustomTitleBar(new Index(undefined, {}));
ViewStackProcessor.StopGetAccessRecording();

"use strict";
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
const i = '20vp';
const j = '28vp';
const m = '12vp';
const o = '8vp';
const t = '-8vp';
const u = '-8vp';
const a1 = '40vp';
const b1 = '40vp';
const c1 = '24vp';
const d1 = '8vp';
const e1 = '12vp';
const f1 = '10vp';
const g1 = '16fp';
const h1 = 1000;
const i1 = 2000;
const j1 = 1000;
const l1 = 'arkui_custom_max_click';
const m1 = 'arkui_custom_min_click';
const n1 = 'arkui_custom_close_click';
const o1 = 'arkui_custom_left_split_click';
const q1 = 'arkui_custom_right_split_click';
const s1 = 'arkui_custom_button_point_light_anim';
const t1 = 'arkui_custom_button_rect_change';
const u1 = 'arkui_custom_menu_width_change';
const v1 = 'arkui_color_configuration';
const w1 = 'arkui_hide_split';
const z1 = 'arkui_maximize_visibility';
const a2 = 'arkui_minimize_visibility';
const b2 = 'arkui_close_visibility';
const c2 = 'arkui_close_status';
const d2 = 'arkui_maximize_is_recover';
const e2 = 'arkui_menu_width_change';
const f2 = 'arkui_button_size_change';
const g2 = 'arkui_button_spacing_change';
const h2 = 'arkui_color_mode_locked';
const i2 = 'arkui_button_right_offset_change';
const j2 = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125829923,
    type: 20000
};
const l2 = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125829925,
    type: 20000
};
const m2 = Color.Transparent;
const n2 = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125830991,
    type: 10001
};
const o2 = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125834289,
    type: 10001
};
const q2 = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125830991,
    type: 10001
};
const s2 = Color.Transparent;
const t2 = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125830991,
    type: 10001
};
const u2 = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125830979,
    type: 10001
};
const v2 = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125831057,
    type: 10001
};
const w2 = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125831024,
    type: 10001
};
const z2 = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125830991,
    type: 10001
};
class a3 {
    constructor(l3, m3) {
        this.d3 = '#000000';
        this.e3 = '#FFFFFF';
        this.e3 = m3;
        this.d3 = l3;
    }
}
const colorMap = new Map([
    [buttonNormalIconFillColor, new ColorGroup('#182431', '#e5ffffff')],
    [buttonHoverBackgroundColor, new ColorGroup('#0C000000', '#26FFFFFF')],
    [buttonHoverIconFillColor, new ColorGroup('#182431', '#e5ffffff')],
    [closeNormalIconFillColor, new ColorGroup('#182431', '#e5ffffff')],
    [closeHoverBackgroundColor, new ColorGroup('#FA2A2D', '#E64548')],
    [closeHoverIconFillColor, new ColorGroup('#ffffff', '#ffffff')],
    [menuHoverColor, new ColorGroup('#19182431', '#19ffffff')],
    [splitItemFillColor, new ColorGroup('#182431', '#e5ffffff')],
]);
class c3 extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.f3 = new ObservedPropertySimplePU(0, this, "maxBtnTouchState");
        this.g3 = new ObservedPropertyObjectPU(j2, this, "maximizeResource");
        this.h3 = new ObservedPropertyObjectPU({
            bundleName: '',
            moduleName: '',
            params: [],
            id: 125829924,
            type: 20000
        }, this, "minimizeResource");
        this.i3 = new ObservedPropertyObjectPU({
            bundleName: '',
            moduleName: '',
            params: [],
            id: 125829917,
            type: 20000
        }, this, "closeResource");
        this.j3 = new ObservedPropertyObjectPU({
            bundleName: '',
            moduleName: '',
            params: [],
            id: 125830147,
            type: 20000
        }, this, "menuLeftResource");
        this.l3 = new ObservedPropertyObjectPU({
            bundleName: '',
            moduleName: '',
            params: [],
            id: 125830148,
            type: 20000
        }, this, "menuRightResource");
        this.m3 = new ObservedPropertyObjectPU(m2, this, "maximizeBackgroundColor");
        this.n3 = new ObservedPropertyObjectPU(m2, this, "minimizeBackgroundColor");
        this.q3 = new ObservedPropertyObjectPU(m2, this, "closeBackgroundColor");
        this.r3 = new ObservedPropertyObjectPU(this.getResourceColor(n2), this, "maximizeFillColor");
        this.s3 = new ObservedPropertyObjectPU(this.getResourceColor(n2), this, "minimizeFillColor");
        this.t3 = new ObservedPropertyObjectPU(this.getResourceColor(n2), this, "closeFillColor");
        this.u3 = new ObservedPropertySimplePU(1.0, this, "maximizeScale");
        this.v3 = new ObservedPropertySimplePU(1.0, this, "minimizeScale");
        this.w3 = new ObservedPropertySimplePU(1.0, this, "closeScale");
        this.x3 = new ObservedPropertySimplePU(Visibility.Visible, this, "rowVisibility");
        this.y3 = new ObservedPropertySimplePU(Visibility.Visible, this, "maximizeVisibility");
        this.z3 = new ObservedPropertySimplePU(Visibility.Visible, this, "minimizeVisibility");
        this.a4 = new ObservedPropertySimplePU(Visibility.Visible, this, "closeVisibility");
        this.b4 = new ObservedPropertySimplePU(true, this, "closeStatus");
        this.c4 = new ObservedPropertySimplePU(false, this, "isShowMenu");
        this.d4 = new ObservedPropertyObjectPU({
            bundleName: '',
            moduleName: '',
            params: [],
            id: 125833961,
            type: 10003
        }, this, "leftSplitTitle");
        this.e4 = new ObservedPropertyObjectPU({
            bundleName: '',
            moduleName: '',
            params: [],
            id: 125833962,
            type: 10003
        }, this, "rightSplitTitle");
        this.f4 = new ObservedPropertyObjectPU(this.getResourceColor(z2), this, "splitFillColor");
        this.g4 = new ObservedPropertyObjectPU(Color.Transparent, this, "leftSplitBackgroundColor");
        this.h4 = new ObservedPropertyObjectPU(Color.Transparent, this, "rightSplitBackgroundColor");
        this.i4 = new ObservedPropertySimplePU(1.0, this, "rowOpacity");
        this.j4 = new ObservedPropertySimplePU('224vp', this, "menuWidth");
        this.l4 = new ObservedPropertySimplePU(12, this, "buttonSpacing");
        this.m4 = new ObservedPropertySimplePU(28, this, "buttonSize");
        this.n4 = new ObservedPropertySimplePU(20, this, "buttonRightOffset");
        this.colorConfigurationLocked = false;
        this.isFocused = true;
        this.isDark = false;
        this.isHoverShowMenu = false;
        this.showMenuTimeoutId = -1;
        this.menuDisappearTimeoutId = -1;
        this.hideSplit = false;
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(params) {
        if (params.maxBtnTouchState !== undefined) {
            this.maxBtnTouchState = params.maxBtnTouchState;
        }
        if (params.maximizeResource !== undefined) {
            this.maximizeResource = params.maximizeResource;
        }
        if (params.minimizeResource !== undefined) {
            this.minimizeResource = params.minimizeResource;
        }
        if (params.closeResource !== undefined) {
            this.closeResource = params.closeResource;
        }
        if (params.menuLeftResource !== undefined) {
            this.menuLeftResource = params.menuLeftResource;
        }
        if (params.menuRightResource !== undefined) {
            this.menuRightResource = params.menuRightResource;
        }
        if (params.maximizeBackgroundColor !== undefined) {
            this.maximizeBackgroundColor = params.maximizeBackgroundColor;
        }
        if (params.minimizeBackgroundColor !== undefined) {
            this.minimizeBackgroundColor = params.minimizeBackgroundColor;
        }
        if (params.closeBackgroundColor !== undefined) {
            this.closeBackgroundColor = params.closeBackgroundColor;
        }
        if (params.maximizeFillColor !== undefined) {
            this.maximizeFillColor = params.maximizeFillColor;
        }
        if (params.minimizeFillColor !== undefined) {
            this.minimizeFillColor = params.minimizeFillColor;
        }
        if (params.closeFillColor !== undefined) {
            this.closeFillColor = params.closeFillColor;
        }
        if (params.maximizeScale !== undefined) {
            this.maximizeScale = params.maximizeScale;
        }
        if (params.minimizeScale !== undefined) {
            this.minimizeScale = params.minimizeScale;
        }
        if (params.closeScale !== undefined) {
            this.closeScale = params.closeScale;
        }
        if (params.rowVisibility !== undefined) {
            this.rowVisibility = params.rowVisibility;
        }
        if (params.maximizeVisibility !== undefined) {
            this.maximizeVisibility = params.maximizeVisibility;
        }
        if (params.minimizeVisibility !== undefined) {
            this.minimizeVisibility = params.minimizeVisibility;
        }
        if (params.closeVisibility !== undefined) {
            this.closeVisibility = params.closeVisibility;
        }
        if (params.closeStatus !== undefined) {
            this.closeStatus = params.closeStatus;
        }
        if (params.isShowMenu !== undefined) {
            this.isShowMenu = params.isShowMenu;
        }
        if (params.leftSplitTitle !== undefined) {
            this.leftSplitTitle = params.leftSplitTitle;
        }
        if (params.rightSplitTitle !== undefined) {
            this.rightSplitTitle = params.rightSplitTitle;
        }
        if (params.splitFillColor !== undefined) {
            this.splitFillColor = params.splitFillColor;
        }
        if (params.leftSplitBackgroundColor !== undefined) {
            this.leftSplitBackgroundColor = params.leftSplitBackgroundColor;
        }
        if (params.rightSplitBackgroundColor !== undefined) {
            this.rightSplitBackgroundColor = params.rightSplitBackgroundColor;
        }
        if (params.rowOpacity !== undefined) {
            this.rowOpacity = params.rowOpacity;
        }
        if (params.menuWidth !== undefined) {
            this.menuWidth = params.menuWidth;
        }
        if (params.buttonSpacing !== undefined) {
            this.buttonSpacing = params.buttonSpacing;
        }
        if (params.buttonSize !== undefined) {
            this.buttonSize = params.buttonSize;
        }
        if (params.buttonRightOffset !== undefined) {
            this.buttonRightOffset = params.buttonRightOffset;
        }
        if (params.colorConfigurationLocked !== undefined) {
            this.colorConfigurationLocked = params.colorConfigurationLocked;
        }
        if (params.isFocused !== undefined) {
            this.isFocused = params.isFocused;
        }
        if (params.isDark !== undefined) {
            this.isDark = params.isDark;
        }
        if (params.isHoverShowMenu !== undefined) {
            this.isHoverShowMenu = params.isHoverShowMenu;
        }
        if (params.showMenuTimeoutId !== undefined) {
            this.showMenuTimeoutId = params.showMenuTimeoutId;
        }
        if (params.menuDisappearTimeoutId !== undefined) {
            this.menuDisappearTimeoutId = params.menuDisappearTimeoutId;
        }
        if (params.hideSplit !== undefined) {
            this.hideSplit = params.hideSplit;
        }
    }
    updateStateVars(params) {
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
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
        this.c4.purgeDependencyOnElmtId(rmElmtId);
        this.d4.purgeDependencyOnElmtId(rmElmtId);
        this.e4.purgeDependencyOnElmtId(rmElmtId);
        this.f4.purgeDependencyOnElmtId(rmElmtId);
        this.g4.purgeDependencyOnElmtId(rmElmtId);
        this.h4.purgeDependencyOnElmtId(rmElmtId);
        this.i4.purgeDependencyOnElmtId(rmElmtId);
        this.j4.purgeDependencyOnElmtId(rmElmtId);
        this.l4.purgeDependencyOnElmtId(rmElmtId);
        this.m4.purgeDependencyOnElmtId(rmElmtId);
        this.n4.purgeDependencyOnElmtId(rmElmtId);
    }
    aboutToBeDeleted() {
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
        this.c4.aboutToBeDeleted();
        this.d4.aboutToBeDeleted();
        this.e4.aboutToBeDeleted();
        this.f4.aboutToBeDeleted();
        this.g4.aboutToBeDeleted();
        this.h4.aboutToBeDeleted();
        this.i4.aboutToBeDeleted();
        this.j4.aboutToBeDeleted();
        this.l4.aboutToBeDeleted();
        this.m4.aboutToBeDeleted();
        this.n4.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get maxBtnTouchState() {
        return this.f3.get();
    }
    set maxBtnTouchState(newValue) {
        this.f3.set(newValue);
    }
    get maximizeResource() {
        return this.g3.get();
    }
    set maximizeResource(newValue) {
        this.g3.set(newValue);
    }
    get minimizeResource() {
        return this.h3.get();
    }
    set minimizeResource(newValue) {
        this.h3.set(newValue);
    }
    get closeResource() {
        return this.i3.get();
    }
    set closeResource(newValue) {
        this.i3.set(newValue);
    }
    get menuLeftResource() {
        return this.j3.get();
    }
    set menuLeftResource(newValue) {
        this.j3.set(newValue);
    }
    get menuRightResource() {
        return this.l3.get();
    }
    set menuRightResource(newValue) {
        this.l3.set(newValue);
    }
    get maximizeBackgroundColor() {
        return this.m3.get();
    }
    set maximizeBackgroundColor(newValue) {
        this.m3.set(newValue);
    }
    get minimizeBackgroundColor() {
        return this.n3.get();
    }
    set minimizeBackgroundColor(newValue) {
        this.n3.set(newValue);
    }
    get closeBackgroundColor() {
        return this.q3.get();
    }
    set closeBackgroundColor(newValue) {
        this.q3.set(newValue);
    }
    get maximizeFillColor() {
        return this.r3.get();
    }
    set maximizeFillColor(newValue) {
        this.r3.set(newValue);
    }
    get minimizeFillColor() {
        return this.s3.get();
    }
    set minimizeFillColor(newValue) {
        this.s3.set(newValue);
    }
    get closeFillColor() {
        return this.t3.get();
    }
    set closeFillColor(newValue) {
        this.t3.set(newValue);
    }
    get maximizeScale() {
        return this.u3.get();
    }
    set maximizeScale(newValue) {
        this.u3.set(newValue);
    }
    get minimizeScale() {
        return this.v3.get();
    }
    set minimizeScale(newValue) {
        this.v3.set(newValue);
    }
    get closeScale() {
        return this.w3.get();
    }
    set closeScale(newValue) {
        this.w3.set(newValue);
    }
    get rowVisibility() {
        return this.x3.get();
    }
    set rowVisibility(newValue) {
        this.x3.set(newValue);
    }
    get maximizeVisibility() {
        return this.y3.get();
    }
    set maximizeVisibility(newValue) {
        this.y3.set(newValue);
    }
    get minimizeVisibility() {
        return this.z3.get();
    }
    set minimizeVisibility(newValue) {
        this.z3.set(newValue);
    }
    get closeVisibility() {
        return this.a4.get();
    }
    set closeVisibility(newValue) {
        this.a4.set(newValue);
    }
    get closeStatus() {
        return this.b4.get();
    }
    set closeStatus(newValue) {
        this.b4.set(newValue);
    }
    get isShowMenu() {
        return this.c4.get();
    }
    set isShowMenu(newValue) {
        this.c4.set(newValue);
    }
    get leftSplitTitle() {
        return this.d4.get();
    }
    set leftSplitTitle(newValue) {
        this.d4.set(newValue);
    }
    get rightSplitTitle() {
        return this.e4.get();
    }
    set rightSplitTitle(newValue) {
        this.e4.set(newValue);
    }
    get splitFillColor() {
        return this.f4.get();
    }
    set splitFillColor(newValue) {
        this.f4.set(newValue);
    }
    get leftSplitBackgroundColor() {
        return this.g4.get();
    }
    set leftSplitBackgroundColor(newValue) {
        this.g4.set(newValue);
    }
    get rightSplitBackgroundColor() {
        return this.h4.get();
    }
    set rightSplitBackgroundColor(newValue) {
        this.h4.set(newValue);
    }
    get rowOpacity() {
        return this.i4.get();
    }
    set rowOpacity(newValue) {
        this.i4.set(newValue);
    }
    get menuWidth() {
        return this.j4.get();
    }
    set menuWidth(newValue) {
        this.j4.set(newValue);
    }
    get buttonSpacing() {
        return this.l4.get();
    }
    set buttonSpacing(newValue) {
        this.l4.set(newValue);
    }
    get buttonSize() {
        return this.m4.get();
    }
    set buttonSize(newValue) {
        this.m4.set(newValue);
    }
    get buttonRightOffset() {
        return this.n4.get();
    }
    set buttonRightOffset(newValue) {
        this.n4.set(newValue);
    }
    onWindowFocused() {
        this.rowOpacity = 1.0;
        this.isFocused = true;
    }
    onWindowUnfocused() {
        this.rowOpacity = 0.4;
        this.isFocused = false;
    }
    parseBoolean(value) {
        if (value === 'true') {
            return true;
        }
        return false;
    }
    setCustomCallback(eventName, param) {
        if (eventName === v1) {
            this.onColorConfigurationUpdate(this.parseBoolean(param));
        }
        else if (eventName === w1) {
            this.setHideSplit(this.parseBoolean(param));
        }
        else if (eventName === z1) {
            this.setMaximizeVisibility(this.parseBoolean(param));
        }
        else if (eventName === a2) {
            this.setMinimizeVisibility(this.parseBoolean(param));
        }
        else if (eventName === b2) {
            this.setCloseVisibility(this.parseBoolean(param));
        }
        else if (eventName === c2) {
            this.setCloseStatus(this.parseBoolean(param));
        }
        else if (eventName === d2) {
            this.setMaximizeIsRecover(this.parseBoolean(param));
        }
        else if (eventName === e2) {
            this.setMenuWidth(param);
        }
        else if (eventName === g2) {
            this.setButtonSpacing(param);
        }
        else if (eventName === h2) {
            this.setColorModeLocked(param);
        }
        else if (eventName === i2) {
            this.setButtonRightOffset(param);
        }
        else if (eventName === f2) {
            this.setButtonButtonSize(param);
        }
    }
    setButtonSpacing(param) {
        this.buttonSpacing = parseInt(param);
    }
    setButtonButtonSize(param) {
        this.buttonSize = parseInt(param);
    }
    setButtonRightOffset(param) {
        this.buttonRightOffset = parseInt(param);
    }
    setColorModeLocked(param) {
        const colorMode = parseInt(param);
        if (colorMode === -1) {
            this.colorConfigurationLocked = false;
            return;
        }
        this.isDark = (colorMode === 0);
        this.colorConfigurationLocked = true;
        this.maximizeFillColor = this.getResourceColor(n2);
        this.minimizeFillColor = this.getResourceColor(n2);
        this.closeFillColor = this.getResourceColor(n2);
    }
    getResourceColor(resource) {
        if (this.colorConfigurationLocked && b3.has(resource)) {
            const k3 = b3.get(resource);
            if (k3) {
                return this.isDark ? k3.e3 : k3.d3;
            }
        }
        return resource;
    }
    onMaximizeButtonClick() {
        this.onCancelMenuTimer();
        this.onHoverMaximizeButton(false);
        this.maximizeScale = 1.0;
        ContainerModal.callNative(l1);
    }
    onMinimizeButtonClick() {
        this.onHoverMinimizeButton(false);
        this.minimizeScale = 1.0;
        ContainerModal.callNative(m1);
    }
    onCloseButtonClick() {
        ContainerModal.callNative(n1);
    }
    onMenuLeftSplitClick() {
        ContainerModal.callNative(o1);
    }
    onMenuRightSplitClick() {
        ContainerModal.callNative(q1);
    }
    addButtonPointLightAnim() {
        ContainerModal.callNative(s1);
    }
    onAreaChangeEvent(q3, r3) {
        ContainerModal.callNative(t1);
    }
    onMenuWidthChange() {
        ContainerModal.callNative(u1,"125833961");
    }
    setHideSplit(j3) {
        this.hideSplit = j3;
    }
    onColorConfigurationUpdate(i3) {
        if (this.colorConfigurationLocked) {
            return;
        }
        this.isDark = i3;
        this.maximizeBackgroundColor = m2;
        this.maximizeFillColor = n2;
        this.minimizeBackgroundColor = m2;
        this.minimizeFillColor = n2;
        this.closeBackgroundColor = m2;
        this.closeFillColor = n2;
    }
    setMaximizeVisibility(h3) {
        this.maximizeVisibility = h3 ? Visibility.None : Visibility.Visible;
    }
    setMinimizeVisibility(g3) {
        this.minimizeVisibility = g3 ? Visibility.None : Visibility.Visible;
    }
    setCloseVisibility(f3) {
        this.closeVisibility = f3 ? Visibility.None : Visibility.Visible;
    }
    setCloseStatus(isEnabled) {
        this.closeStatus = isEnabled;
    }
    setMaximizeIsRecover(e3) {
        if (e3) {
            this.maximizeResource = l2;
        }
        else {
            this.maximizeResource = j2;
        }
    }
    setMenuWidth(width) {
        this.menuWidth = (80 + parseInt(width)) + 'vp';
    }
    setRowVisibility() {
        if (this.maximizeVisibility === Visibility.None && this.minimizeVisibility === Visibility.None &&
            this.closeVisibility === Visibility.None) {
            this.rowVisibility = Visibility.None;
        }
        else {
            this.rowVisibility = Visibility.Visible;
        }
    }
    onHoverMaximizeButton(isHover) {
        if (isHover) {
            this.maximizeBackgroundColor = this.getResourceColor(o2);
            this.maximizeFillColor = this.getResourceColor(q2);
        }
        else {
            this.maximizeBackgroundColor = m2;
            this.maximizeFillColor = this.getResourceColor(n2);
        }
    }
    onHoverMinimizeButton(isHover) {
        if (isHover) {
            this.minimizeBackgroundColor = this.getResourceColor(o2);
            this.minimizeFillColor = this.getResourceColor(q2);
        }
        else {
            this.minimizeBackgroundColor = m2;
            this.minimizeFillColor = this.getResourceColor(q2);
        }
    }
    onHoverCloseButton(isHover) {
        if (isHover) {
            this.closeBackgroundColor = this.getResourceColor(u2);
            this.closeFillColor = this.getResourceColor(v2);
        }
        else {
            this.closeBackgroundColor = s2;
            this.closeFillColor = this.getResourceColor(t2);
        }
    }
    onShowMenuWithTimer() {
        if (!this.hideSplit && this.isFocused) {
            this.showMenuTimeoutId = setTimeout(() => {
                this.isShowMenu = true;
                this.menuDisappearTimer(i1);
            }, h1);
        }
    }
    onCancelMenuTimer() {
        if (this.showMenuTimeoutId !== -1) {
            clearTimeout(this.showMenuTimeoutId);
        }
    }
    aboutToAppear() {
    }
    MenuBuilder(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.width(this.menuWidth);
            Column.onHover((isHover, event) => {
                if (isHover) {
                    this.cancelMenuDisappearTimer();
                }
                else {
                    this.menuDisappearTimer(j1);
                }
            });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.borderRadius('4vp');
            Row.width('100%');
            Row.backgroundColor(ObservedObject.GetRawObject(this.leftSplitBackgroundColor));
            Row.margin({
                top: '0vp',
                bottom: '2vp',
                left: '4vp',
                right: '4vp'
            });
            Row.justifyContent(FlexAlign.Start);
            Row.onClick(() => {
                this.onMenuLeftSplitClick();
            });
            Row.onHover((isHover, event) => {
                if (isHover) {
                    this.leftSplitBackgroundColor = this.getResourceColor(w2);
                }
                else {
                    this.leftSplitBackgroundColor = Color.Transparent;
                }
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(this.menuLeftResource);
            Image.width(c1);
            Image.height(c1);
            Image.fillColor(ObservedObject.GetRawObject(this.splitFillColor));
            Image.margin({
                top: d1,
                bottom: d1,
                left: e1,
                right: e1
            });
        }, Image);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.leftSplitTitle);
            Text.fontSize(g1);
            Text.textAlign(TextAlign.Start);
            Text.maxLines(1);
            Text.margin({ top: f1, bottom: f1, right: e1 });
        }, Text);
        Text.pop();
        Row.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.borderRadius('4vp');
            Row.width('100%');
            Row.backgroundColor(ObservedObject.GetRawObject(this.rightSplitBackgroundColor));
            Row.margin({
                top: '2vp',
                bottom: '0vp',
                left: '4vp',
                right: '4vp'
            });
            Row.justifyContent(FlexAlign.Start);
            Row.onClick(() => {
                this.onMenuRightSplitClick();
            });
            Row.onHover((isHover, event) => {
                if (isHover) {
                    this.rightSplitBackgroundColor = this.getResourceColor(w2);
                }
                else {
                    this.rightSplitBackgroundColor = Color.Transparent;
                }
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(this.menuRightResource);
            Image.width(c1);
            Image.height(c1);
            Image.fillColor(ObservedObject.GetRawObject(this.splitFillColor));
            Image.margin({
                top: d1,
                bottom: d1,
                left: e1,
                right: e1
            });
        }, Image);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.rightSplitTitle);
            Text.fontSize(g1);
            Text.textAlign(TextAlign.Start);
            Text.maxLines(1);
            Text.margin({ top: f1, bottom: f1, right: e1 });
        }, Text);
        Text.pop();
        Row.pop();
        Column.pop();
    }
    menuDisappearTimer(d3) {
        this.cancelMenuDisappearTimer();
        this.menuDisappearTimeoutId = setTimeout(() => {
            this.isShowMenu = false;
        }, d3);
    }
    cancelMenuDisappearTimer() {
        if (this.menuDisappearTimeoutId !== -1) {
            clearTimeout(this.menuDisappearTimeoutId);
        }
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.justifyContent(FlexAlign.End);
            Row.visibility(this.rowVisibility);
            Row.height('100%');
            Row.width('100%');
            Row.opacity(this.rowOpacity);
            Row.hitTestBehavior(HitTestMode.Transparent);
            Row.onAppear(() => {
                this.addButtonPointLightAnim();
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.id('containerModalButtonRowId');
            Row.height('100%');
            Row.padding({ left: m, right: this.buttonRightOffset + 'vp' });
            Row.onAreaChange((oldValue, newValue) => {
                this.onAreaChangeEvent(oldValue, newValue);
            });
            Gesture.create(GesturePriority.Low);
            PanGesture.create();
            PanGesture.pop();
            Gesture.pop();
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithChild();
            Button.id('EnhanceMaximizeBtn');
            Button.backgroundColor(ObservedObject.GetRawObject(this.maximizeBackgroundColor));
            Button.width(this.buttonSize + 'vp');
            Button.height(this.buttonSize + 'vp');
            Button.type(ButtonType.Normal);
            Button.borderRadius('4vp');
            Button.hoverEffect(HoverEffect.None);
            Button.margin({ right: this.buttonSpacing + 'vp' });
            Button.responseRegion({
                x: t,
                y: u,
                width: a1,
                height: b1
            });
            Button.visibility(this.maximizeVisibility);
            Button.bindMenu(this.isShowMenu, { builder: this.MenuBuilder.bind(this) }, {
                placement: Placement.BottomRight, aboutToDisappear: () => {
                    this.isShowMenu = false;
                    this.cancelMenuDisappearTimer();
                }
            });
            Gesture.create(GesturePriority.Low);
            GestureGroup.create(GestureMode.Exclusive);
            LongPressGesture.create({ repeat: false });
            LongPressGesture.onAction(() => {
                this.onMenuWidthChange();
                this.isShowMenu = !this.hideSplit;
            });
            LongPressGesture.pop();
            TapGesture.create();
            TapGesture.onAction(() => {
                this.onMaximizeButtonClick();
            });
            TapGesture.pop();
            GestureGroup.pop();
            Gesture.pop();
            Button.onHover((isHover, event) => {
                if (isHover && this.maxBtnTouchState == 2) {
                    isHover = false;
                    this.maxBtnTouchState = 0;
                }
                this.onHoverMaximizeButton(isHover);
                if (isHover) {
                    this.onMenuWidthChange();
                    this.onShowMenuWithTimer();
                }
                else {
                    this.onCancelMenuTimer();
                }
                this.getUIContext()?.animateTo({ duration: 0 }, () => {
                    if (isHover) {
                        this.maximizeScale = 1.1;
                    }
                    else {
                        this.maximizeScale = 1.0;
                    }
                });
            });
            Button.onTouch((event) => {
                if (event) {
                    if (event.type === TouchType.Move) {
                        this.maxBtnTouchState = 0;
                    }
                    if (event.type === TouchType.Down) {
                        this.maxBtnTouchState = 1;
                    }
                    if (event.type === TouchType.Up) {
                        this.maxBtnTouchState = 2;
                    }
                }
            });
            Button.onMouse((event) => {
                if (event) {
                    if (this.maxBtnTouchState == 0) {
                        this.onHoverMaximizeButton(true);
                    }
                }
            });
        }, Button);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(this.maximizeResource);
            Image.width(i);
            Image.height(i);
            Image.fillColor(ObservedObject.GetRawObject(this.maximizeFillColor));
            Image.draggable(false);
            Image.interpolation(ImageInterpolation.High);
            Image.scale({ x: this.maximizeScale, y: this.maximizeScale });
        }, Image);
        Button.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithChild();
            Button.id('EnhanceMinimizeBtn');
            Button.backgroundColor(ObservedObject.GetRawObject(this.minimizeBackgroundColor));
            Button.width(this.buttonSize + 'vp');
            Button.height(this.buttonSize + 'vp');
            Button.type(ButtonType.Normal);
            Button.borderRadius('4vp');
            Button.margin({ right: this.buttonSpacing + 'vp' });
            Button.hoverEffect(HoverEffect.None);
            Button.responseRegion({
                x: t,
                y: u,
                width: a1,
                height: b1
            });
            Button.visibility(this.minimizeVisibility);
            Gesture.create(GesturePriority.Low);
            TapGesture.create();
            TapGesture.onAction(() => {
                this.onMinimizeButtonClick();
            });
            TapGesture.pop();
            Gesture.pop();
            Button.onHover((isHover, event) => {
                if (isHover && this.maxBtnTouchState == 2) {
                    isHover = false;
                    this.maxBtnTouchState = 0;
                }
                this.onHoverMinimizeButton(isHover);
                this.getUIContext()?.animateTo({ duration: 0 }, () => {
                    if (isHover) {
                        this.minimizeScale = 1.1;
                    }
                    else {
                        this.minimizeScale = 1.0;
                    }
                });
            });
            Button.onMouse((event) => {
                if (event) {
                    if (this.maxBtnTouchState == 0) {
                        this.onHoverMinimizeButton(true);
                    }
                }
            });
        }, Button);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(this.minimizeResource);
            Image.width(i);
            Image.height(i);
            Image.fillColor(ObservedObject.GetRawObject(this.minimizeFillColor));
            Image.draggable(false);
            Image.interpolation(ImageInterpolation.High);
            Image.scale({ x: this.minimizeScale, y: this.minimizeScale });
        }, Image);
        Button.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithChild();
            Button.id('EnhanceCloseBtn');
            Button.backgroundColor(ObservedObject.GetRawObject(this.closeBackgroundColor));
            Button.width(this.buttonSize + 'vp');
            Button.height(this.buttonSize + 'vp');
            Button.type(ButtonType.Normal);
            Button.borderRadius('4vp');
            Button.hoverEffect(HoverEffect.None);
            Button.responseRegion({
                x: t,
                y: u,
                width: a1,
                height: b1
            });
            Button.visibility(this.closeVisibility);
            Gesture.create(GesturePriority.Low);
            TapGesture.create();
            TapGesture.onAction(() => {
                this.onCloseButtonClick();
            });
            TapGesture.pop();
            Gesture.pop();
            Button.onHover((isHover, event) => {
                if (isHover && this.maxBtnTouchState == 2) {
                    isHover = false;
                    this.maxBtnTouchState = 0;
                }
                this.onHoverCloseButton(isHover);
                this.getUIContext()?.animateTo({ duration: 0 }, () => {
                    if (isHover) {
                        this.closeScale = 1.1;
                    }
                    else {
                        this.closeScale = 1.0;
                    }
                });
            });
            Button.onMouse((event) => {
                if (event) {
                    if (this.maxBtnTouchState == 0) {
                        this.onHoverCloseButton(true);
                    }
                }
            });
        }, Button);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(this.closeResource);
            Image.width(i);
            Image.height(i);
            Image.fillColor(ObservedObject.GetRawObject(this.closeFillColor));
            Image.draggable(false);
            Image.interpolation(ImageInterpolation.High);
            Image.scale({ x: this.closeScale, y: this.closeScale });
        }, Image);
        Button.pop();
        Row.pop();
        Row.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
    static getEntryName() {
        return "custombutton";
    }
}

ViewStackProcessor.StartGetAccessRecordingFor(ViewStackProcessor.AllocateNewElmetIdForNextComponent());
loadCustomTitleButton(new c3(undefined, {}));
ViewStackProcessor.StopGetAccessRecording();