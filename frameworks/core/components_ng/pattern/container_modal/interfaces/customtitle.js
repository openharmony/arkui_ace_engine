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
const i = '28vp';
const j = '28vp';
const m = '12vp';
const i4 = '8vp';
const o = '-8vp';
const u4 = '-8vp';
const u = '40vp';
const a1 = '40vp';
const b1 = '24vp';
const c1 = '8vp';
const d1 = '12vp';
const e1 = '10vp';
const f1 = '16fp';
const g1 = 1000;
const f3 = 'arkui_custom_max_click';
const r3 = 'arkui_custom_min_click';
const s3 = 'arkui_custom_close_click';
const u3 = 'arkui_custom_left_split_click';
const v3 = 'arkui_custom_right_split_click';
const e4 = 'arkui_custom_button_point_light_anim';
const f4 = 'arkui_custom_button_rect_change';
const g4 = 'arkui_custom_menu_width_change';
const x3 = 'arkui_color_configuration';
const y3 = 'arkui_hide_split';
const z3 = 'arkui_maximize_visibility';
const a4 = 'arkui_minimize_visibility';
const b4 = 'arkui_close_visibility';
const c4 = 'arkui_close_status';
const d4 = 'arkui_maximize_is_recover';
const h4 = 'arkui_menu_width_change';
const h1 = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125829923,
    type: 20000
};
const i1 = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125829925,
    type: 20000
};
const j1 = Color.Transparent;
const l1 = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125830991,
    type: 10001
};
const m1 = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125834289,
    type: 10001
};
const n1 = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125830991,
    type: 10001
};
const o1 = Color.Transparent;
const q1 = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125830991,
    type: 10001
};
const s1 = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125830979,
    type: 10001
};
const t1 = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125831057,
    type: 10001
};
const u1 = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125831024,
    type: 10001
};
class v1 extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.w1 = new ObservedPropertyObjectPU(h1, this, "maximizeResource");
        this.z1 = new ObservedPropertyObjectPU({
            bundleName: '',
            moduleName: '',
            params: [],
            id: 125829924,
            type: 20000
        }, this, "minimizeResource");
        this.a2 = new ObservedPropertyObjectPU({
            bundleName: '',
            moduleName: '',
            params: [],
            id: 125829917,
            type: 20000
        }, this, "closeResource");
        this.b2 = new ObservedPropertyObjectPU({
            bundleName: '',
            moduleName: '',
            params: [],
            id: 125830147,
            type: 20000
        }, this, "menuLeftResource");
        this.c2 = new ObservedPropertyObjectPU({
            bundleName: '',
            moduleName: '',
            params: [],
            id: 125830148,
            type: 20000
        }, this, "menuRightResource");
        this.d2 = new ObservedPropertyObjectPU(j1, this, "maximizeBackgroundColor");
        this.e2 = new ObservedPropertyObjectPU(j1, this, "minimizeBackgroundColor");
        this.f2 = new ObservedPropertyObjectPU(j1, this, "closeBackgroundColor");
        this.g2 = new ObservedPropertyObjectPU(l1, this, "maximizeFillColor");
        this.h2 = new ObservedPropertyObjectPU(l1, this, "minimizeFillColor");
        this.i2 = new ObservedPropertyObjectPU(l1, this, "closeFillColor");
        this.j2 = new ObservedPropertySimplePU(1.0, this, "maximizeScale");
        this.l2 = new ObservedPropertySimplePU(1.0, this, "minimizeScale");
        this.m2 = new ObservedPropertySimplePU(1.0, this, "closeScale");
        this.n2 = new ObservedPropertySimplePU(Visibility.Visible, this, "rowVisibility");
        this.o2 = new ObservedPropertySimplePU(Visibility.Visible, this, "maximizeVisibility");
        this.q2 = new ObservedPropertySimplePU(Visibility.Visible, this, "minimizeVisibility");
        this.s2 = new ObservedPropertySimplePU(Visibility.Visible, this, "closeVisibility");
        this.t2 = new ObservedPropertySimplePU(true, this, "closeStatus");
        this.u2 = new ObservedPropertySimplePU(false, this, "isShowMenu");
        this.v2 = new ObservedPropertyObjectPU({
            bundleName: '',
            moduleName: '',
            params: [],
            id: 125833961,
            type: 10003
        }, this, "leftSplitTitle");
        this.w2 = new ObservedPropertyObjectPU({
            bundleName: '',
            moduleName: '',
            params: [],
            id: 125833962,
            type: 10003
        }, this, "rightSplitTitle");
        this.z2 = new ObservedPropertyObjectPU({
            bundleName: '',
            moduleName: '',
            params: [],
            id: 125830991,
            type: 10001
        }, this, "splitFillColor");
        this.a3 = new ObservedPropertyObjectPU(Color.Transparent, this, "leftSplitBackgroundColor");
        this.b3 = new ObservedPropertyObjectPU(Color.Transparent, this, "rightSplitBackgroundColor");
        this.c3 = new ObservedPropertySimplePU(1.0, this, "rowOpacity");
        this.e3 = new ObservedPropertySimplePU('224vp', this, "menuWidth");
        this.isFocused = true;
        this.isDark = false;
        this.isHoverShowMenu = false;
        this.showMenuTimeoutId = -1;
        this.hideSplit = false;
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(params) {
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
        if (params.hideSplit !== undefined) {
            this.hideSplit = params.hideSplit;
        }
    }
    updateStateVars(params) {
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.w1.purgeDependencyOnElmtId(rmElmtId);
        this.z1.purgeDependencyOnElmtId(rmElmtId);
        this.a2.purgeDependencyOnElmtId(rmElmtId);
        this.b2.purgeDependencyOnElmtId(rmElmtId);
        this.c2.purgeDependencyOnElmtId(rmElmtId);
        this.d2.purgeDependencyOnElmtId(rmElmtId);
        this.e2.purgeDependencyOnElmtId(rmElmtId);
        this.f2.purgeDependencyOnElmtId(rmElmtId);
        this.g2.purgeDependencyOnElmtId(rmElmtId);
        this.h2.purgeDependencyOnElmtId(rmElmtId);
        this.i2.purgeDependencyOnElmtId(rmElmtId);
        this.j2.purgeDependencyOnElmtId(rmElmtId);
        this.l2.purgeDependencyOnElmtId(rmElmtId);
        this.m2.purgeDependencyOnElmtId(rmElmtId);
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
        this.e3.purgeDependencyOnElmtId(rmElmtId);
    }
    aboutToBeDeleted() {
        this.w1.aboutToBeDeleted();
        this.z1.aboutToBeDeleted();
        this.a2.aboutToBeDeleted();
        this.b2.aboutToBeDeleted();
        this.c2.aboutToBeDeleted();
        this.d2.aboutToBeDeleted();
        this.e2.aboutToBeDeleted();
        this.f2.aboutToBeDeleted();
        this.g2.aboutToBeDeleted();
        this.h2.aboutToBeDeleted();
        this.i2.aboutToBeDeleted();
        this.j2.aboutToBeDeleted();
        this.l2.aboutToBeDeleted();
        this.m2.aboutToBeDeleted();
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
        this.e3.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get maximizeResource() {
        return this.w1.get();
    }
    set maximizeResource(newValue) {
        this.w1.set(newValue);
    }
    get minimizeResource() {
        return this.z1.get();
    }
    set minimizeResource(newValue) {
        this.z1.set(newValue);
    }
    get closeResource() {
        return this.a2.get();
    }
    set closeResource(newValue) {
        this.a2.set(newValue);
    }
    get menuLeftResource() {
        return this.b2.get();
    }
    set menuLeftResource(newValue) {
        this.b2.set(newValue);
    }
    get menuRightResource() {
        return this.c2.get();
    }
    set menuRightResource(newValue) {
        this.c2.set(newValue);
    }
    get maximizeBackgroundColor() {
        return this.d2.get();
    }
    set maximizeBackgroundColor(newValue) {
        this.d2.set(newValue);
    }
    get minimizeBackgroundColor() {
        return this.e2.get();
    }
    set minimizeBackgroundColor(newValue) {
        this.e2.set(newValue);
    }
    get closeBackgroundColor() {
        return this.f2.get();
    }
    set closeBackgroundColor(newValue) {
        this.f2.set(newValue);
    }
    get maximizeFillColor() {
        return this.g2.get();
    }
    set maximizeFillColor(newValue) {
        this.g2.set(newValue);
    }
    get minimizeFillColor() {
        return this.h2.get();
    }
    set minimizeFillColor(newValue) {
        this.h2.set(newValue);
    }
    get closeFillColor() {
        return this.i2.get();
    }
    set closeFillColor(newValue) {
        this.i2.set(newValue);
    }
    get maximizeScale() {
        return this.j2.get();
    }
    set maximizeScale(newValue) {
        this.j2.set(newValue);
    }
    get minimizeScale() {
        return this.l2.get();
    }
    set minimizeScale(newValue) {
        this.l2.set(newValue);
    }
    get closeScale() {
        return this.m2.get();
    }
    set closeScale(newValue) {
        this.m2.set(newValue);
    }
    get rowVisibility() {
        return this.n2.get();
    }
    set rowVisibility(newValue) {
        this.n2.set(newValue);
    }
    get maximizeVisibility() {
        return this.o2.get();
    }
    set maximizeVisibility(newValue) {
        this.o2.set(newValue);
    }
    get minimizeVisibility() {
        return this.q2.get();
    }
    set minimizeVisibility(newValue) {
        this.q2.set(newValue);
    }
    get closeVisibility() {
        return this.s2.get();
    }
    set closeVisibility(newValue) {
        this.s2.set(newValue);
    }
    get closeStatus() {
        return this.t2.get();
    }
    set closeStatus(newValue) {
        this.t2.set(newValue);
    }
    get isShowMenu() {
        return this.u2.get();
    }
    set isShowMenu(newValue) {
        this.u2.set(newValue);
    }
    get leftSplitTitle() {
        return this.v2.get();
    }
    set leftSplitTitle(newValue) {
        this.v2.set(newValue);
    }
    get rightSplitTitle() {
        return this.w2.get();
    }
    set rightSplitTitle(newValue) {
        this.w2.set(newValue);
    }
    get splitFillColor() {
        return this.z2.get();
    }
    set splitFillColor(newValue) {
        this.z2.set(newValue);
    }
    get leftSplitBackgroundColor() {
        return this.a3.get();
    }
    set leftSplitBackgroundColor(newValue) {
        this.a3.set(newValue);
    }
    get rightSplitBackgroundColor() {
        return this.b3.get();
    }
    set rightSplitBackgroundColor(newValue) {
        this.b3.set(newValue);
    }
    get rowOpacity() {
        return this.c3.get();
    }
    set rowOpacity(newValue) {
        this.c3.set(newValue);
    }
    get menuWidth() {
        return this.e3.get();
    }
    set menuWidth(newValue) {
        this.e3.set(newValue);
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
        if (value == 'true') {
            return true;
        }
        return false;
    }
    setCustomCallback(eventName, param) {
        if (eventName == x3) {
            this.onColorConfigurationUpdate(this.parseBoolean(param));
        }
        else if (eventName == y3) {
            this.setHideSplit(this.parseBoolean(param));
        }
        else if (eventName == z3) {
            this.setMaximizeVisibility(this.parseBoolean(param));
        }
        else if (eventName == a4) {
            this.setMinimizeVisibility(this.parseBoolean(param));
        }
        else if (eventName == b4) {
            this.setCloseVisibility(this.parseBoolean(param));
        }
        else if (eventName == c4) {
            this.setCloseStatus(this.parseBoolean(param));
        }
        else if (eventName == d4) {
            this.setMaximizeIsRecover(this.parseBoolean(param));
        }
        else if (eventName == h4) {
            this.setMenuWidth(param);
        }
    }
    onMaximizeButtonClick() {
        this.onCancelMenuTimer();
        ContainerModal.callNative(f3);
    }
    onMinimizeButtonClick() {
        ContainerModal.callNative(r3);
    }
    onCloseButtonClick() {
        ContainerModal.callNative(s3);
    }
    onMenuLeftSplitClick() {
        ContainerModal.callNative(u3);
    }
    onMenuRightSplitClick() {
        ContainerModal.callNative(v3);
    }
    addButtonPointLightAnim() {
        ContainerModal.callNative(e4);
    }
    onAreaChangeEvent(oldValue, newValue) {
        ContainerModal.callNative(f4);
    }
    onMenuWidthChange() {
        ContainerModal.callNative(g4,"125833961");
    }
    setHideSplit(n3) {
        this.hideSplit = n3;
    }
    onColorConfigurationUpdate(m3) {
        this.isDark = m3;
        this.maximizeBackgroundColor = j1;
        this.maximizeFillColor = l1;
        this.minimizeBackgroundColor = j1;
        this.minimizeFillColor = l1;
        this.closeBackgroundColor = j1;
        this.closeFillColor = l1;
    }
    setMaximizeVisibility(l3) {
        this.maximizeVisibility = l3 ? Visibility.None : Visibility.Visible;
    }
    setMinimizeVisibility(k3) {
        this.minimizeVisibility = k3 ? Visibility.None : Visibility.Visible;
    }
    setCloseVisibility(j3) {
        this.closeVisibility = j3 ? Visibility.None : Visibility.Visible;
    }
    setCloseStatus(isEnabled) {
        this.closeStatus = isEnabled;
    }
    setMaximizeIsRecover(i3) {
        if (i3) {
            this.maximizeResource = i1;
        }
        else {
            this.maximizeResource = h1;
        }
    }
    setMenuWidth(width) {
        this.menuWidth = (80 + parseInt(width)) + 'vp';
    }
    setRowVisibility() {
        if (this.maximizeVisibility == Visibility.None && this.minimizeVisibility == Visibility.None &&
            this.closeVisibility == Visibility.None) {
            this.rowVisibility = Visibility.None;
        }
        else {
            this.rowVisibility = Visibility.Visible;
        }
    }
    onHoverMaximizeButton(isHover) {
        if (isHover) {
            this.maximizeBackgroundColor = m1;
            this.maximizeFillColor = n1;
        }
        else {
            this.maximizeBackgroundColor = j1;
            this.maximizeFillColor = l1;
        }
    }
    onHoverMinimizeButton(isHover) {
        if (isHover) {
            this.minimizeBackgroundColor = m1;
            this.minimizeFillColor = n1;
        }
        else {
            this.minimizeBackgroundColor = j1;
            this.minimizeFillColor = l1;
        }
    }
    onHoverCloseButton(isHover) {
        if (isHover) {
            this.closeBackgroundColor = s1;
            this.closeFillColor = t1;
        }
        else {
            this.closeBackgroundColor = o1;
            this.closeFillColor = q1;
        }
    }
    onShowMenuWithTimer() {
        if (!this.hideSplit && this.isFocused) {
            this.showMenuTimeoutId = setTimeout(() => {
                this.isShowMenu = true;
            }, g1);
        }
    }
    onCancelMenuTimer() {
        if (this.showMenuTimeoutId != -1) {
            clearTimeout(this.showMenuTimeoutId);
        }
    }
    aboutToAppear() {
    }
    MenuBuilder(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.width(this.menuWidth);
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
                    this.leftSplitBackgroundColor = u1;
                }
                else {
                    this.leftSplitBackgroundColor = Color.Transparent;
                }
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(this.menuLeftResource);
            Image.width(b1);
            Image.height(b1);
            Image.fillColor(ObservedObject.GetRawObject(this.splitFillColor));
            Image.margin({
                top: c1,
                bottom: c1,
                left: d1,
                right: d1
            });
        }, Image);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.leftSplitTitle);
            Text.fontSize(f1);
            Text.textAlign(TextAlign.Start);
            Text.maxLines(1);
            Text.margin({ top: e1, bottom: e1, right: d1 });
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
                    this.rightSplitBackgroundColor = u1;
                }
                else {
                    this.rightSplitBackgroundColor = Color.Transparent;
                }
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(this.menuRightResource);
            Image.width(b1);
            Image.height(b1);
            Image.fillColor(ObservedObject.GetRawObject(this.splitFillColor));
            Image.margin({
                top: c1,
                bottom: c1,
                left: d1,
                right: d1
            });
        }, Image);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.rightSplitTitle);
            Text.fontSize(f1);
            Text.textAlign(TextAlign.Start);
            Text.maxLines(1);
            Text.margin({ top: e1, bottom: e1, right: d1 });
        }, Text);
        Text.pop();
        Row.pop();
        Column.pop();
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
            Row.padding({ left: m, right: i4 });
            Row.onAreaChange((oldValue, newValue) => {
                this.onAreaChangeEvent(oldValue, newValue);
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithChild();
            Button.id('EnhanceMaximizeBtn');
            Button.backgroundColor(ObservedObject.GetRawObject(this.maximizeBackgroundColor));
            Button.width(j);
            Button.height(j);
            Button.type(ButtonType.Normal);
            Button.borderRadius('4vp');
            Button.margin({ right: m });
            Button.responseRegion({
                x: o,
                y: u4,
                width: u,
                height: a1
            });
            Button.visibility(this.maximizeVisibility);
            Button.bindMenu(this.isShowMenu, { builder: this.MenuBuilder.bind(this) }, {
                placement: Placement.BottomRight, aboutToDisappear: () => {
                    this.isShowMenu = false;
                }
            });
            Gesture.create(GesturePriority.Low);
            GestureGroup.create(GestureMode.Exclusive);
            LongPressGesture.create({ repeat: false });
            LongPressGesture.onAction(() => {
                this.onMenuWidthChange();
                this.isShowMenu = true;
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
            Button.width(j);
            Button.height(j);
            Button.type(ButtonType.Normal);
            Button.borderRadius('4vp');
            Button.margin({ right: m });
            Button.responseRegion({
                x: o,
                y: u4,
                width: u,
                height: a1
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
            Button.width(j);
            Button.height(j);
            Button.type(ButtonType.Normal);
            Button.borderRadius('4vp');
            Button.margin({ right: m });
            Button.responseRegion({
                x: o,
                y: u4,
                width: u,
                height: a1
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
        return "Index";
    }
}

ViewStackProcessor.StartGetAccessRecordingFor(ViewStackProcessor.AllocateNewElmetIdForNextComponent());
loadCustomTitleButton(new v1(undefined, {}));
ViewStackProcessor.StopGetAccessRecording();
