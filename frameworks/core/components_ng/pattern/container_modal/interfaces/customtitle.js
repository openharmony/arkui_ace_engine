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
const IMAGE_SIZE = '20vp';
const BUTTON_SIZE = '28vp';
const BUTTON_ELEMENT_MARGIN_HORIZONTAL = '12vp';
const BUTTON_ELEMENT_MARGIN_HORIZONTAL_END = '8vp';
const TITLE_BUTTON_RESPONSE_REGION_OFFSET_X = '-8vp';
const TITLE_BUTTON_RESPONSE_REGION_OFFSET_Y = '-8vp';
const TITLE_BUTTON_RESPONSE_REGION_WIDTH = '40vp';
const TITLE_BUTTON_RESPONSE_REGION_HEIGHT = '40vp';
const MENU_ICON_SIZE = '24vp';
const MENU_MARGIN_V = '8vp';
const MENU_MARGIN_H = '12vp';
const MENU_TITLE_MARGIN_V = '10vp';
const MENU_TITLE_TEXT_FONT_SIZE = '16fp';
const HOVER_TIME = 1000;
const MENU_AUTO_DISAPPEAR_TIME = 2000;
const MENU_MOUSEOUT_DISAPPEAR_TIME = 1000;
const EVENT_NAME_CUSTOM_MAX_CLICK = 'arkui_custom_max_click';
const EVENT_NAME_MIN_CLICK = 'arkui_custom_min_click';
const EVENT_NAME_CLOSE_CLICK = 'arkui_custom_close_click';
const EVENT_NAME_LEFT_SPLIT_CLICK = 'arkui_custom_left_split_click';
const EVENT_NAME_RIGHT_SPLIT_CLICK = 'arkui_custom_right_split_click';
const EVENT_NAME_BUTTON_POINT_LIGHT_ANIM = 'arkui_custom_button_point_light_anim';
const EVENT_NAME_BUTTON_RECT_CHANGE = 'arkui_custom_button_rect_change';
const EVENT_NAME_CUSTOM_MENU_WIDTH_CHANGE = 'arkui_custom_menu_width_change';
const EVENT_NAME_COLOR_CONFIGURATION = 'arkui_color_configuration';
const EVENT_NAME_HIDE_SPLIT = 'arkui_hide_split';
const EVENT_NAME_MAXIMIZE_VISIBILITY = 'arkui_maximize_visibility';
const EVENT_NAME_MINIMIZE_VISIBILITY = 'arkui_minimize_visibility';
const EVENT_NAME_CLOSE_VISIBILITY = 'arkui_close_visibility';
const EVENT_NAME_CLOSE_STATUS = 'arkui_close_status';
const EVENT_NAME_MAXIMIZE_IS_RECOVER = 'arkui_maximize_is_recover';
const EVENT_NAME_MENU_WIDTH_CHANGE = 'arkui_menu_width_change';
const EVENT_NAME_BUTTON_SIZE_CHANGE = 'arkui_button_size_change';
const EVENT_NAME_BUTTON_SPACING_CHANGE = 'arkui_button_spacing_change';
const EVENT_NAME_COLOR_MODE_LOCKED = 'arkui_color_mode_locked';
const EVENT_NAME_BUTTON_RIGHT_OFFSET_CHANGE = 'arkui_button_right_offset_change';
const maximizeNormalResource = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125829923,
    type: 20000
};
const recoverNormalResource = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125829925,
    type: 20000
};
const buttonNormalBackgroundColor = Color.Transparent;
const buttonNormalIconFillColor = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125830991,
    type: 10001
};
const buttonHoverBackgroundColor = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125834289,
    type: 10001
};
const buttonHoverIconFillColor = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125830991,
    type: 10001
};
const closeNormalBackgroundColor = Color.Transparent;
const closeNormalIconFillColor = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125830991,
    type: 10001
};
const closeHoverBackgroundColor = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125830979,
    type: 10001
};
const closeHoverIconFillColor = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125831057,
    type: 10001
};
const menuHoverColor = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125831024,
    type: 10001
};
const splitItemFillColor = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125830991,
    type: 10001
};
class ColorGroup {
    constructor(p5, q5) {
        this.light = '#000000';
        this.dark = '#FFFFFF';
        this.dark = q5;
        this.light = p5;
    }
}
const colorMap = new Map([
    [buttonNormalIconFillColor, new ColorGroup('#182431', '#e5ffffff')],
    [buttonHoverBackgroundColor, new ColorGroup('#26000000', '#40FFFFFF')],
    [buttonHoverIconFillColor, new ColorGroup('#182431', '#e5ffffff')],
    [closeNormalIconFillColor, new ColorGroup('#182431', '#e5ffffff')],
    [closeHoverBackgroundColor, new ColorGroup('#FA2A2D', '#E64548')],
    [closeHoverIconFillColor, new ColorGroup('#ffffff', '#ffffff')],
    [menuHoverColor, new ColorGroup('#19182431', '#19ffffff')],
    [splitItemFillColor, new ColorGroup('#182431', '#e5ffffff')],
]);
export class v1 extends ViewPU {
    constructor(j5, k5, l5, m5 = -1, n5 = undefined, o5) {
        super(j5, l5, m5, o5);
        if (typeof n5 === "function") {
            this.paramsGenerator_ = n5;
        }
        this.__maximizeResource = new ObservedPropertyObjectPU(maximizeNormalResource, this, "maximizeResource");
        this.__minimizeResource = new ObservedPropertyObjectPU({
            bundleName: '',
            moduleName: '',
            params: [],
            id: 125829924,
            type: 20000
        }, this, "minimizeResource");
        this.__closeResource = new ObservedPropertyObjectPU({
            bundleName: '',
            moduleName: '',
            params: [],
            id: 125829917,
            type: 20000
        }, this, "closeResource");
        this.__menuLeftResource = new ObservedPropertyObjectPU({
            bundleName: '',
            moduleName: '',
            params: [],
            id: 125830147,
            type: 20000
        }, this, "menuLeftResource");
        this.__menuRightResource = new ObservedPropertyObjectPU({
            bundleName: '',
            moduleName: '',
            params: [],
            id: 125830148,
            type: 20000
        }, this, "menuRightResource");
        this.__maximizeBackgroundColor = new ObservedPropertyObjectPU(buttonNormalBackgroundColor, this, "maximizeBackgroundColor");
        this.__minimizeBackgroundColor = new ObservedPropertyObjectPU(buttonNormalBackgroundColor, this, "minimizeBackgroundColor");
        this.__closeBackgroundColor = new ObservedPropertyObjectPU(buttonNormalBackgroundColor, this, "closeBackgroundColor");
        this.__maximizeFillColor = new ObservedPropertyObjectPU(this.getResourceColor(buttonNormalIconFillColor), this, "maximizeFillColor");
        this.__minimizeFillColor = new ObservedPropertyObjectPU(this.getResourceColor(buttonNormalIconFillColor), this, "minimizeFillColor");
        this.__closeFillColor = new ObservedPropertyObjectPU(this.getResourceColor(buttonNormalIconFillColor), this, "closeFillColor");
        this.__maximizeScale = new ObservedPropertySimplePU(1.0, this, "maximizeScale");
        this.__minimizeScale = new ObservedPropertySimplePU(1.0, this, "minimizeScale");
        this.__closeScale = new ObservedPropertySimplePU(1.0, this, "closeScale");
        this.__rowVisibility = new ObservedPropertySimplePU(Visibility.Visible, this, "rowVisibility");
        this.__maximizeVisibility = new ObservedPropertySimplePU(Visibility.Visible, this, "maximizeVisibility");
        this.__minimizeVisibility = new ObservedPropertySimplePU(Visibility.Visible, this, "minimizeVisibility");
        this.__closeVisibility = new ObservedPropertySimplePU(Visibility.Visible, this, "closeVisibility");
        this.__closeStatus = new ObservedPropertySimplePU(true, this, "closeStatus");
        this.__isShowMenu = new ObservedPropertySimplePU(false, this, "isShowMenu");
        this.__leftSplitTitle = new ObservedPropertyObjectPU({
            bundleName: '',
            moduleName: '',
            params: [],
            id: 125833961,
            type: 10003
        }, this, "leftSplitTitle");
        this.__rightSplitTitle = new ObservedPropertyObjectPU({
            bundleName: '',
            moduleName: '',
            params: [],
            id: 125833962,
            type: 10003
        }, this, "rightSplitTitle");
        this.__splitFillColor = new ObservedPropertyObjectPU(this.getResourceColor(splitItemFillColor), this, "splitFillColor");
        this.__leftSplitBackgroundColor = new ObservedPropertyObjectPU(Color.Transparent, this, "leftSplitBackgroundColor");
        this.__rightSplitBackgroundColor = new ObservedPropertyObjectPU(Color.Transparent, this, "rightSplitBackgroundColor");
        this.__rowOpacity = new ObservedPropertySimplePU(1.0, this, "rowOpacity");
        this.__menuWidth = new ObservedPropertySimplePU('224vp', this, "menuWidth");
        this.__buttonSpacing = new ObservedPropertySimplePU(12, this, "buttonSpacing");
        this.__buttonSize = new ObservedPropertySimplePU(28, this, "buttonSize");
        this.__buttonRightOffset = new ObservedPropertySimplePU(20, this, "buttonRightOffset");
        this.colorConfigurationLocked = false;
        this.isFocused = true;
        this.isDark = false;
        this.isHoverShowMenu = false;
        this.showMenuTimeoutId = -1;
        this.menuDisappearTimeoutId = -1;
        this.hideSplit = false;
        this.setInitiallyProvidedValue(k5);
    }
    setInitiallyProvidedValue(i5) {
        if (i5.maximizeResource !== undefined) {
            this.maximizeResource = i5.maximizeResource;
        }
        if (i5.minimizeResource !== undefined) {
            this.minimizeResource = i5.minimizeResource;
        }
        if (i5.closeResource !== undefined) {
            this.closeResource = i5.closeResource;
        }
        if (i5.menuLeftResource !== undefined) {
            this.menuLeftResource = i5.menuLeftResource;
        }
        if (i5.menuRightResource !== undefined) {
            this.menuRightResource = i5.menuRightResource;
        }
        if (i5.maximizeBackgroundColor !== undefined) {
            this.maximizeBackgroundColor = i5.maximizeBackgroundColor;
        }
        if (i5.minimizeBackgroundColor !== undefined) {
            this.minimizeBackgroundColor = i5.minimizeBackgroundColor;
        }
        if (i5.closeBackgroundColor !== undefined) {
            this.closeBackgroundColor = i5.closeBackgroundColor;
        }
        if (i5.maximizeFillColor !== undefined) {
            this.maximizeFillColor = i5.maximizeFillColor;
        }
        if (i5.minimizeFillColor !== undefined) {
            this.minimizeFillColor = i5.minimizeFillColor;
        }
        if (i5.closeFillColor !== undefined) {
            this.closeFillColor = i5.closeFillColor;
        }
        if (i5.maximizeScale !== undefined) {
            this.maximizeScale = i5.maximizeScale;
        }
        if (i5.minimizeScale !== undefined) {
            this.minimizeScale = i5.minimizeScale;
        }
        if (i5.closeScale !== undefined) {
            this.closeScale = i5.closeScale;
        }
        if (i5.rowVisibility !== undefined) {
            this.rowVisibility = i5.rowVisibility;
        }
        if (i5.maximizeVisibility !== undefined) {
            this.maximizeVisibility = i5.maximizeVisibility;
        }
        if (i5.minimizeVisibility !== undefined) {
            this.minimizeVisibility = i5.minimizeVisibility;
        }
        if (i5.closeVisibility !== undefined) {
            this.closeVisibility = i5.closeVisibility;
        }
        if (i5.closeStatus !== undefined) {
            this.closeStatus = i5.closeStatus;
        }
        if (i5.isShowMenu !== undefined) {
            this.isShowMenu = i5.isShowMenu;
        }
        if (i5.leftSplitTitle !== undefined) {
            this.leftSplitTitle = i5.leftSplitTitle;
        }
        if (i5.rightSplitTitle !== undefined) {
            this.rightSplitTitle = i5.rightSplitTitle;
        }
        if (i5.splitFillColor !== undefined) {
            this.splitFillColor = i5.splitFillColor;
        }
        if (i5.leftSplitBackgroundColor !== undefined) {
            this.leftSplitBackgroundColor = i5.leftSplitBackgroundColor;
        }
        if (i5.rightSplitBackgroundColor !== undefined) {
            this.rightSplitBackgroundColor = i5.rightSplitBackgroundColor;
        }
        if (i5.rowOpacity !== undefined) {
            this.rowOpacity = i5.rowOpacity;
        }
        if (i5.menuWidth !== undefined) {
            this.menuWidth = i5.menuWidth;
        }
        if (i5.buttonSpacing !== undefined) {
            this.buttonSpacing = i5.buttonSpacing;
        }
        if (i5.buttonSize !== undefined) {
            this.buttonSize = i5.buttonSize;
        }
        if (i5.buttonRightOffset !== undefined) {
            this.buttonRightOffset = i5.buttonRightOffset;
        }
        if (i5.colorConfigurationLocked !== undefined) {
            this.colorConfigurationLocked = i5.colorConfigurationLocked;
        }
        if (i5.isFocused !== undefined) {
            this.isFocused = i5.isFocused;
        }
        if (i5.isDark !== undefined) {
            this.isDark = i5.isDark;
        }
        if (i5.isHoverShowMenu !== undefined) {
            this.isHoverShowMenu = i5.isHoverShowMenu;
        }
        if (i5.showMenuTimeoutId !== undefined) {
            this.showMenuTimeoutId = i5.showMenuTimeoutId;
        }
        if (i5.menuDisappearTimeoutId !== undefined) {
            this.menuDisappearTimeoutId = i5.menuDisappearTimeoutId;
        }
        if (i5.hideSplit !== undefined) {
            this.hideSplit = i5.hideSplit;
        }
    }
    updateStateVars(h5) {
    }
    purgeVariableDependenciesOnElmtId(g5) {
        this.__maximizeResource.purgeDependencyOnElmtId(g5);
        this.__minimizeResource.purgeDependencyOnElmtId(g5);
        this.__closeResource.purgeDependencyOnElmtId(g5);
        this.__menuLeftResource.purgeDependencyOnElmtId(g5);
        this.__menuRightResource.purgeDependencyOnElmtId(g5);
        this.__maximizeBackgroundColor.purgeDependencyOnElmtId(g5);
        this.__minimizeBackgroundColor.purgeDependencyOnElmtId(g5);
        this.__closeBackgroundColor.purgeDependencyOnElmtId(g5);
        this.__maximizeFillColor.purgeDependencyOnElmtId(g5);
        this.__minimizeFillColor.purgeDependencyOnElmtId(g5);
        this.__closeFillColor.purgeDependencyOnElmtId(g5);
        this.__maximizeScale.purgeDependencyOnElmtId(g5);
        this.__minimizeScale.purgeDependencyOnElmtId(g5);
        this.__closeScale.purgeDependencyOnElmtId(g5);
        this.__rowVisibility.purgeDependencyOnElmtId(g5);
        this.__maximizeVisibility.purgeDependencyOnElmtId(g5);
        this.__minimizeVisibility.purgeDependencyOnElmtId(g5);
        this.__closeVisibility.purgeDependencyOnElmtId(g5);
        this.__closeStatus.purgeDependencyOnElmtId(g5);
        this.__isShowMenu.purgeDependencyOnElmtId(g5);
        this.__leftSplitTitle.purgeDependencyOnElmtId(g5);
        this.__rightSplitTitle.purgeDependencyOnElmtId(g5);
        this.__splitFillColor.purgeDependencyOnElmtId(g5);
        this.__leftSplitBackgroundColor.purgeDependencyOnElmtId(g5);
        this.__rightSplitBackgroundColor.purgeDependencyOnElmtId(g5);
        this.__rowOpacity.purgeDependencyOnElmtId(g5);
        this.__menuWidth.purgeDependencyOnElmtId(g5);
        this.__buttonSpacing.purgeDependencyOnElmtId(g5);
        this.__buttonSize.purgeDependencyOnElmtId(g5);
        this.__buttonRightOffset.purgeDependencyOnElmtId(g5);
    }
    aboutToBeDeleted() {
        this.__maximizeResource.aboutToBeDeleted();
        this.__minimizeResource.aboutToBeDeleted();
        this.__closeResource.aboutToBeDeleted();
        this.__menuLeftResource.aboutToBeDeleted();
        this.__menuRightResource.aboutToBeDeleted();
        this.__maximizeBackgroundColor.aboutToBeDeleted();
        this.__minimizeBackgroundColor.aboutToBeDeleted();
        this.__closeBackgroundColor.aboutToBeDeleted();
        this.__maximizeFillColor.aboutToBeDeleted();
        this.__minimizeFillColor.aboutToBeDeleted();
        this.__closeFillColor.aboutToBeDeleted();
        this.__maximizeScale.aboutToBeDeleted();
        this.__minimizeScale.aboutToBeDeleted();
        this.__closeScale.aboutToBeDeleted();
        this.__rowVisibility.aboutToBeDeleted();
        this.__maximizeVisibility.aboutToBeDeleted();
        this.__minimizeVisibility.aboutToBeDeleted();
        this.__closeVisibility.aboutToBeDeleted();
        this.__closeStatus.aboutToBeDeleted();
        this.__isShowMenu.aboutToBeDeleted();
        this.__leftSplitTitle.aboutToBeDeleted();
        this.__rightSplitTitle.aboutToBeDeleted();
        this.__splitFillColor.aboutToBeDeleted();
        this.__leftSplitBackgroundColor.aboutToBeDeleted();
        this.__rightSplitBackgroundColor.aboutToBeDeleted();
        this.__rowOpacity.aboutToBeDeleted();
        this.__menuWidth.aboutToBeDeleted();
        this.__buttonSpacing.aboutToBeDeleted();
        this.__buttonSize.aboutToBeDeleted();
        this.__buttonRightOffset.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get maximizeResource() {
        return this.__maximizeResource.get();
    }
    set maximizeResource(f5) {
        this.__maximizeResource.set(f5);
    }
    get minimizeResource() {
        return this.__minimizeResource.get();
    }
    set minimizeResource(e5) {
        this.__minimizeResource.set(e5);
    }
    get closeResource() {
        return this.__closeResource.get();
    }
    set closeResource(d5) {
        this.__closeResource.set(d5);
    }
    get menuLeftResource() {
        return this.__menuLeftResource.get();
    }
    set menuLeftResource(c5) {
        this.__menuLeftResource.set(c5);
    }
    get menuRightResource() {
        return this.__menuRightResource.get();
    }
    set menuRightResource(b5) {
        this.__menuRightResource.set(b5);
    }
    get maximizeBackgroundColor() {
        return this.__maximizeBackgroundColor.get();
    }
    set maximizeBackgroundColor(a5) {
        this.__maximizeBackgroundColor.set(a5);
    }
    get minimizeBackgroundColor() {
        return this.__minimizeBackgroundColor.get();
    }
    set minimizeBackgroundColor(z4) {
        this.__minimizeBackgroundColor.set(z4);
    }
    get closeBackgroundColor() {
        return this.__closeBackgroundColor.get();
    }
    set closeBackgroundColor(y4) {
        this.__closeBackgroundColor.set(y4);
    }
    get maximizeFillColor() {
        return this.__maximizeFillColor.get();
    }
    set maximizeFillColor(x4) {
        this.__maximizeFillColor.set(x4);
    }
    get minimizeFillColor() {
        return this.__minimizeFillColor.get();
    }
    set minimizeFillColor(w4) {
        this.__minimizeFillColor.set(w4);
    }
    get closeFillColor() {
        return this.__closeFillColor.get();
    }
    set closeFillColor(v4) {
        this.__closeFillColor.set(v4);
    }
    get maximizeScale() {
        return this.__maximizeScale.get();
    }
    set maximizeScale(u4) {
        this.__maximizeScale.set(u4);
    }
    get minimizeScale() {
        return this.__minimizeScale.get();
    }
    set minimizeScale(t4) {
        this.__minimizeScale.set(t4);
    }
    get closeScale() {
        return this.__closeScale.get();
    }
    set closeScale(s4) {
        this.__closeScale.set(s4);
    }
    get rowVisibility() {
        return this.__rowVisibility.get();
    }
    set rowVisibility(r4) {
        this.__rowVisibility.set(r4);
    }
    get maximizeVisibility() {
        return this.__maximizeVisibility.get();
    }
    set maximizeVisibility(q4) {
        this.__maximizeVisibility.set(q4);
    }
    get minimizeVisibility() {
        return this.__minimizeVisibility.get();
    }
    set minimizeVisibility(p4) {
        this.__minimizeVisibility.set(p4);
    }
    get closeVisibility() {
        return this.__closeVisibility.get();
    }
    set closeVisibility(o4) {
        this.__closeVisibility.set(o4);
    }
    get closeStatus() {
        return this.__closeStatus.get();
    }
    set closeStatus(n4) {
        this.__closeStatus.set(n4);
    }
    get isShowMenu() {
        return this.__isShowMenu.get();
    }
    set isShowMenu(m4) {
        this.__isShowMenu.set(m4);
    }
    get leftSplitTitle() {
        return this.__leftSplitTitle.get();
    }
    set leftSplitTitle(l4) {
        this.__leftSplitTitle.set(l4);
    }
    get rightSplitTitle() {
        return this.__rightSplitTitle.get();
    }
    set rightSplitTitle(k4) {
        this.__rightSplitTitle.set(k4);
    }
    get splitFillColor() {
        return this.__splitFillColor.get();
    }
    set splitFillColor(j4) {
        this.__splitFillColor.set(j4);
    }
    get leftSplitBackgroundColor() {
        return this.__leftSplitBackgroundColor.get();
    }
    set leftSplitBackgroundColor(i4) {
        this.__leftSplitBackgroundColor.set(i4);
    }
    get rightSplitBackgroundColor() {
        return this.__rightSplitBackgroundColor.get();
    }
    set rightSplitBackgroundColor(h4) {
        this.__rightSplitBackgroundColor.set(h4);
    }
    get rowOpacity() {
        return this.__rowOpacity.get();
    }
    set rowOpacity(g4) {
        this.__rowOpacity.set(g4);
    }
    get menuWidth() {
        return this.__menuWidth.get();
    }
    set menuWidth(f4) {
        this.__menuWidth.set(f4);
    }
    get buttonSpacing() {
        return this.__buttonSpacing.get();
    }
    set buttonSpacing(e4) {
        this.__buttonSpacing.set(e4);
    }
    get buttonSize() {
        return this.__buttonSize.get();
    }
    set buttonSize(d4) {
        this.__buttonSize.set(d4);
    }
    get buttonRightOffset() {
        return this.__buttonRightOffset.get();
    }
    set buttonRightOffset(c4) {
        this.__buttonRightOffset.set(c4);
    }
    onWindowFocused() {
        this.rowOpacity = 1.0;
        this.isFocused = true;
    }
    onWindowUnfocused() {
        this.rowOpacity = 0.4;
        this.isFocused = false;
    }
    parseBoolean(b4) {
        if (b4 === 'true') {
            return true;
        }
        return false;
    }
    setCustomCallback(z3, a4) {
        if (z3 === EVENT_NAME_COLOR_CONFIGURATION) {
            this.onColorConfigurationUpdate(this.parseBoolean(a4));
        }
        else if (z3 === EVENT_NAME_HIDE_SPLIT) {
            this.setHideSplit(this.parseBoolean(a4));
        }
        else if (z3 === EVENT_NAME_MAXIMIZE_VISIBILITY) {
            this.setMaximizeVisibility(this.parseBoolean(a4));
        }
        else if (z3 === EVENT_NAME_MINIMIZE_VISIBILITY) {
            this.setMinimizeVisibility(this.parseBoolean(a4));
        }
        else if (z3 === EVENT_NAME_CLOSE_VISIBILITY) {
            this.setCloseVisibility(this.parseBoolean(a4));
        }
        else if (z3 === EVENT_NAME_CLOSE_STATUS) {
            this.setCloseStatus(this.parseBoolean(a4));
        }
        else if (z3 === EVENT_NAME_MAXIMIZE_IS_RECOVER) {
            this.setMaximizeIsRecover(this.parseBoolean(a4));
        }
        else if (z3 === EVENT_NAME_MENU_WIDTH_CHANGE) {
            this.setMenuWidth(a4);
        }
        else if (z3 === EVENT_NAME_BUTTON_SPACING_CHANGE) {
            this.setButtonSpacing(a4);
        }
        else if (z3 === EVENT_NAME_COLOR_MODE_LOCKED) {
            this.setColorModeLocked(a4);
        }
        else if (z3 === EVENT_NAME_BUTTON_RIGHT_OFFSET_CHANGE) {
            this.setButtonRightOffset(a4);
        }
        else if (z3 === EVENT_NAME_BUTTON_SIZE_CHANGE) {
            this.setButtonButtonSize(a4);
        }
    }
    setButtonSpacing(y3) {
        this.buttonSpacing = parseInt(y3);
    }
    setButtonButtonSize(x3) {
        this.buttonSize = parseInt(x3);
    }
    setButtonRightOffset(w3) {
        this.buttonRightOffset = parseInt(w3);
    }
    setColorModeLocked(u3) {
        const v3 = parseInt(u3);
        if (v3 === -1) {
            this.colorConfigurationLocked = false;
            return;
        }
        this.isDark = (v3 === 0);
        this.colorConfigurationLocked = true;
        this.maximizeFillColor = this.getResourceColor(buttonNormalIconFillColor);
        this.minimizeFillColor = this.getResourceColor(buttonNormalIconFillColor);
        this.closeFillColor = this.getResourceColor(buttonNormalIconFillColor);
    }
    getResourceColor(s3) {
        if (this.colorConfigurationLocked && colorMap.has(s3)) {
            const t3 = colorMap.get(s3);
            if (t3) {
                return this.isDark ? t3.dark : t3.light;
            }
        }
        return s3;
    }
    onMaximizeButtonClick() {
        this.onCancelMenuTimer();
        this.onHoverMaximizeButton(false);
        this.maximizeScale = 1.0;
        ContainerModal.callNative(EVENT_NAME_CUSTOM_MAX_CLICK);
    }
    onMinimizeButtonClick() {
        this.onHoverMinimizeButton(false);
        this.minimizeScale = 1.0;
        ContainerModal.callNative(EVENT_NAME_MIN_CLICK);
    }
    onMinimizeButtonClick() {
        ContainerModal.callNative(EVENT_NAME_MIN_CLICK);
    }
    onCloseButtonClick() {
        ContainerModal.callNative(EVENT_NAME_CLOSE_CLICK);
    }
    onMenuLeftSplitClick() {
        ContainerModal.callNative(EVENT_NAME_LEFT_SPLIT_CLICK);
    }
    onMenuRightSplitClick() {
        ContainerModal.callNative(EVENT_NAME_RIGHT_SPLIT_CLICK);
    }
    addButtonPointLightAnim() {
        ContainerModal.callNative(EVENT_NAME_BUTTON_POINT_LIGHT_ANIM);
    }
    onAreaChangeEvent(q3, r3) {
        ContainerModal.callNative(EVENT_NAME_BUTTON_RECT_CHANGE);
    }
    onMenuWidthChange() {
        ContainerModal.callNative(EVENT_NAME_CUSTOM_MENU_WIDTH_CHANGE);
    }
    setHideSplit(p3) {
        this.hideSplit = p3;
    }
    onColorConfigurationUpdate(o3) {
        if (this.colorConfigurationLocked) {
            return;
        }
        this.isDark = o3;
        this.maximizeBackgroundColor = buttonNormalBackgroundColor;
        this.maximizeFillColor = buttonNormalIconFillColor;
        this.minimizeBackgroundColor = buttonNormalBackgroundColor;
        this.minimizeFillColor = buttonNormalIconFillColor;
        this.closeBackgroundColor = buttonNormalBackgroundColor;
        this.closeFillColor = buttonNormalIconFillColor;
    }
    setMaximizeVisibility(n3) {
        this.maximizeVisibility = n3 ? Visibility.None : Visibility.Visible;
    }
    setMinimizeVisibility(m3) {
        this.minimizeVisibility = m3 ? Visibility.None : Visibility.Visible;
    }
    setCloseVisibility(l3) {
        this.closeVisibility = l3 ? Visibility.None : Visibility.Visible;
    }
    setCloseStatus(k3) {
        this.closeStatus = k3;
    }
    setMaximizeIsRecover(j3) {
        if (j3) {
            this.maximizeResource = recoverNormalResource;
        }
        else {
            this.maximizeResource = maximizeNormalResource;
        }
    }
    setMenuWidth(i3) {
        this.menuWidth = (80 + parseInt(i3)) + 'vp';
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
    onHoverMaximizeButton(h3) {
        if (h3) {
            this.maximizeBackgroundColor = this.getResourceColor(buttonHoverBackgroundColor);
            this.maximizeFillColor = this.getResourceColor(buttonHoverIconFillColor);
        }
        else {
            this.maximizeBackgroundColor = buttonNormalBackgroundColor;
            this.maximizeFillColor = this.getResourceColor(buttonNormalIconFillColor);
        }
    }
    onHoverMinimizeButton(g3) {
        if (g3) {
            this.minimizeBackgroundColor = this.getResourceColor(buttonHoverBackgroundColor);
            this.minimizeFillColor = this.getResourceColor(buttonHoverIconFillColor);
        }
        else {
            this.minimizeBackgroundColor = buttonNormalBackgroundColor;
            this.minimizeFillColor = this.getResourceColor(buttonHoverIconFillColor);
        }
    }
    onHoverCloseButton(f3) {
        if (f3) {
            this.closeBackgroundColor = this.getResourceColor(closeHoverBackgroundColor);
            this.closeFillColor = this.getResourceColor(closeHoverIconFillColor);
        }
        else {
            this.closeBackgroundColor = closeNormalBackgroundColor;
            this.closeFillColor = this.getResourceColor(closeNormalIconFillColor);
        }
    }
    onShowMenuWithTimer() {
        if (!this.hideSplit && this.isFocused) {
            this.showMenuTimeoutId = setTimeout(() => {
                this.isShowMenu = true;
                this.menuDisappearTimer(MENU_AUTO_DISAPPEAR_TIME);
            }, HOVER_TIME);
        }
    }
    onCancelMenuTimer() {
        if (this.showMenuTimeoutId !== -1) {
            clearTimeout(this.showMenuTimeoutId);
        }
    }
    aboutToAppear() {
    }
    MenuBuilder(x1 = null) {
        this.observeComponentCreation2((z2, a3) => {
            Column.create();
            Column.width(this.menuWidth);
            Column.onHover((c3, d3) => {
                if (c3) {
                    this.cancelMenuDisappearTimer();
                }
                else {
                    this.menuDisappearTimer(MENU_MOUSEOUT_DISAPPEAR_TIME);
                }
            });
        }, Column);
        this.observeComponentCreation2((t2, u2) => {
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
            Row.onHover((x2, y2) => {
                if (x2) {
                    this.leftSplitBackgroundColor = this.getResourceColor(menuHoverColor);
                }
                else {
                    this.leftSplitBackgroundColor = Color.Transparent;
                }
            });
        }, Row);
        this.observeComponentCreation2((r2, s2) => {
            Image.create(this.menuLeftResource);
            Image.width(MENU_ICON_SIZE);
            Image.height(MENU_ICON_SIZE);
            Image.fillColor(ObservedObject.GetRawObject(this.splitFillColor));
            Image.margin({
                top: MENU_MARGIN_V,
                bottom: MENU_MARGIN_V,
                left: MENU_MARGIN_H,
                right: MENU_MARGIN_H
            });
        }, Image);
        this.observeComponentCreation2((p2, q2) => {
            Text.create(this.leftSplitTitle);
            Text.fontSize(MENU_TITLE_TEXT_FONT_SIZE);
            Text.textAlign(TextAlign.Start);
            Text.maxLines(1);
            Text.margin({ top: MENU_TITLE_MARGIN_V, bottom: MENU_TITLE_MARGIN_V, right: MENU_MARGIN_H });
        }, Text);
        Text.pop();
        Row.pop();
        this.observeComponentCreation2((j2, k2) => {
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
            Row.onHover((n2, o2) => {
                if (n2) {
                    this.rightSplitBackgroundColor = this.getResourceColor(menuHoverColor);
                }
                else {
                    this.rightSplitBackgroundColor = Color.Transparent;
                }
            });
        }, Row);
        this.observeComponentCreation2((h2, i2) => {
            Image.create(this.menuRightResource);
            Image.width(MENU_ICON_SIZE);
            Image.height(MENU_ICON_SIZE);
            Image.fillColor(ObservedObject.GetRawObject(this.splitFillColor));
            Image.margin({
                top: MENU_MARGIN_V,
                bottom: MENU_MARGIN_V,
                left: MENU_MARGIN_H,
                right: MENU_MARGIN_H
            });
        }, Image);
        this.observeComponentCreation2((f2, g2) => {
            Text.create(this.rightSplitTitle);
            Text.fontSize(MENU_TITLE_TEXT_FONT_SIZE);
            Text.textAlign(TextAlign.Start);
            Text.maxLines(1);
            Text.margin({ top: MENU_TITLE_MARGIN_V, bottom: MENU_TITLE_MARGIN_V, right: MENU_MARGIN_H });
        }, Text);
        Text.pop();
        Row.pop();
        Column.pop();
    }
    menuDisappearTimer(v1) {
        this.cancelMenuDisappearTimer();
        this.menuDisappearTimeoutId = setTimeout(() => {
            this.isShowMenu = false;
        }, v1);
    }
    cancelMenuDisappearTimer() {
        if (this.menuDisappearTimeoutId !== -1) {
            clearTimeout(this.menuDisappearTimeoutId);
        }
    }
    initialRender() {
        this.observeComponentCreation2((s1, t1) => {
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
        this.observeComponentCreation2((n1, o1) => {
            Row.create();
            Row.id('containerModalButtonRowId');
            Row.height('100%');
            Row.padding({ left: BUTTON_ELEMENT_MARGIN_HORIZONTAL, right: this.buttonRightOffset + 'vp' });
            Row.onAreaChange((q1, r1) => {
                this.onAreaChangeEvent(q1, r1);
            });
        }, Row);
        this.observeComponentCreation2((e1, f1) => {
            Button.createWithChild();
            Button.id('EnhanceMaximizeBtn');
            Button.backgroundColor(ObservedObject.GetRawObject(this.maximizeBackgroundColor));
            Button.width(this.buttonSize + 'vp');
            Button.height(this.buttonSize + 'vp');
            Button.type(ButtonType.Normal);
            Button.borderRadius('4vp');
            Button.margin({ right: this.buttonSpacing + 'vp' });
            Button.hoverEffect(HoverEffect.None);
            Button.responseRegion({
                x: TITLE_BUTTON_RESPONSE_REGION_OFFSET_X,
                y: TITLE_BUTTON_RESPONSE_REGION_OFFSET_Y,
                width: TITLE_BUTTON_RESPONSE_REGION_WIDTH,
                height: TITLE_BUTTON_RESPONSE_REGION_HEIGHT
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
            Button.onHover((j1, k1) => {
                var l1;
                this.onHoverMaximizeButton(j1);
                if (j1) {
                    this.onMenuWidthChange();
                    this.onShowMenuWithTimer();
                }
                else {
                    this.onCancelMenuTimer();
                }
                (l1 = this.getUIContext()) === null || l1 === void 0 ? void 0 : l1.animateTo({ duration: 0 }, () => {
                    if (j1) {
                        this.maximizeScale = 1.1;
                    }
                    else {
                        this.maximizeScale = 1.0;
                    }
                });
            });
        }, Button);
        this.observeComponentCreation2((c1, d1) => {
            Image.create(this.maximizeResource);
            Image.width(IMAGE_SIZE);
            Image.height(IMAGE_SIZE);
            Image.fillColor(ObservedObject.GetRawObject(this.maximizeFillColor));
            Image.draggable(false);
            Image.interpolation(ImageInterpolation.High);
            Image.scale({ x: this.maximizeScale, y: this.maximizeScale });
        }, Image);
        Button.pop();
        this.observeComponentCreation2((u, v) => {
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
                x: TITLE_BUTTON_RESPONSE_REGION_OFFSET_X,
                y: TITLE_BUTTON_RESPONSE_REGION_OFFSET_Y,
                width: TITLE_BUTTON_RESPONSE_REGION_WIDTH,
                height: TITLE_BUTTON_RESPONSE_REGION_HEIGHT
            });
            Button.visibility(this.minimizeVisibility);
            Gesture.create(GesturePriority.Low);
            TapGesture.create();
            TapGesture.onAction(() => {
                this.onMinimizeButtonClick();
            });
            TapGesture.pop();
            Gesture.pop();
            Button.onHover((y, z) => {
                var a1;
                this.onHoverMinimizeButton(y);
                (a1 = this.getUIContext()) === null || a1 === void 0 ? void 0 : a1.animateTo({ duration: 0 }, () => {
                    if (y) {
                        this.minimizeScale = 1.1;
                    }
                    else {
                        this.minimizeScale = 1.0;
                    }
                });
            });
        }, Button);
        this.observeComponentCreation2((s, t) => {
            Image.create(this.minimizeResource);
            Image.width(IMAGE_SIZE);
            Image.height(IMAGE_SIZE);
            Image.fillColor(ObservedObject.GetRawObject(this.minimizeFillColor));
            Image.draggable(false);
            Image.interpolation(ImageInterpolation.High);
            Image.scale({ x: this.minimizeScale, y: this.minimizeScale });
        }, Image);
        Button.pop();
        this.observeComponentCreation2((k, l) => {
            Button.createWithChild();
            Button.id('EnhanceCloseBtn');
            Button.backgroundColor(ObservedObject.GetRawObject(this.closeBackgroundColor));
            Button.width(this.buttonSize + 'vp');
            Button.height(this.buttonSize + 'vp');
            Button.type(ButtonType.Normal);
            Button.borderRadius('4vp');
            Button.responseRegion({
                x: TITLE_BUTTON_RESPONSE_REGION_OFFSET_X,
                y: TITLE_BUTTON_RESPONSE_REGION_OFFSET_Y,
                width: TITLE_BUTTON_RESPONSE_REGION_WIDTH,
                height: TITLE_BUTTON_RESPONSE_REGION_HEIGHT
            });
            Button.visibility(this.closeVisibility);
            Gesture.create(GesturePriority.Low);
            TapGesture.create();
            TapGesture.onAction(() => {
                this.onCloseButtonClick();
            });
            TapGesture.pop();
            Gesture.pop();
            Button.onHover((o, p) => {
                var q;
                this.onHoverCloseButton(o);
                (q = this.getUIContext()) === null || q === void 0 ? void 0 : q.animateTo({ duration: 0 }, () => {
                    if (o) {
                        this.closeScale = 1.1;
                    }
                    else {
                        this.closeScale = 1.0;
                    }
                });
            });
        }, Button);
        this.observeComponentCreation2((i, j) => {
            Image.create(this.closeResource);
            Image.width(IMAGE_SIZE);
            Image.height(IMAGE_SIZE);
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
        return "v1";
    }
}

ViewStackProcessor.StartGetAccessRecordingFor(ViewStackProcessor.AllocateNewElmetIdForNextComponent());
loadCustomTitleButton(new v1(undefined, {}));
ViewStackProcessor.StopGetAccessRecording();
