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

if (!("finalizeConstruction" in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
export var IconType;
(function (v10) {
  v10[v10["BADGE"] = 1] = "BADGE";
  v10[v10["NORMAL_ICON"] = 2] = "NORMAL_ICON";
  v10[v10["SYSTEM_ICON"] = 3] = "SYSTEM_ICON";
  v10[v10["HEAD_SCULPTURE"] = 4] = "HEAD_SCULPTURE";
  v10[v10["APP_ICON"] = 5] = "APP_ICON";
  v10[v10["PREVIEW"] = 6] = "PREVIEW";
  v10[v10["LONGITUDINAL"] = 7] = "LONGITUDINAL";
  v10[v10["VERTICAL"] = 8] = "VERTICAL";
})(IconType || (IconType = {}));
var ItemHeight;
(function (u10) {
  u10[u10["FIRST_HEIGHT"] = 48] = "FIRST_HEIGHT";
  u10[u10["SECOND_HEIGHT"] = 56] = "SECOND_HEIGHT";
  u10[u10["THIRD_HEIGHT"] = 64] = "THIRD_HEIGHT";
  u10[u10["FOURTH_HEIGHT"] = 72] = "FOURTH_HEIGHT";
  u10[u10["FIFTH_HEIGHT"] = 96] = "FIFTH_HEIGHT";
})(ItemHeight || (ItemHeight = {}));
const TEXT_MAX_LINE = 1;
const ITEM_BORDER_SHOWN = 2;
const TEXT_COLUMN_SPACE = 4;
const TEXT_SAFE_MARGIN = 8;
const LISTITEM_PADDING = 6;
const SWITCH_PADDING = 4;
const STACK_PADDING = 4;
const BADGE_SIZE = 8;
const SMALL_ICON_SIZE = 16;
const SYSTEM_ICON_SIZE = 24;
const TEXT_ARROW_HEIGHT = 32;
const SAFE_LIST_PADDING = 32;
const HEADSCULPTURE_SIZE = 40;
const BUTTON_SIZE = 28;
const APP_ICON_SIZE = 64;
const PREVIEW_SIZE = 96;
const LONGITUDINAL_SIZE = 96;
const VERTICAL_SIZE = 96;
const NORMAL_ITEM_ROW_SPACE = 16;
const SPECIAL_ITEM_ROW_SPACE = 0;
const SPECIAL_ICON_SIZE = 0;
const DEFAULT_ROW_SPACE = 0;
const SPECICAL_ROW_SPACE = 4;
const OPERATEITEM_ICONLIKE_SIZE = 24;
const OPERATEITEM_ARROW_WIDTH = 12;
const OPERATEITEM_ICON_CLICKABLE_SIZE = 40;
const OPERATEITEM_IMAGE_SIZE = 48;
const HOVERING_COLOR = '#0d000000';
const TOUCH_DOWN_COLOR = '#1a000000';
const ACTIVED_COLOR = '#1a0a59f7';
const RIGHT_CONTENT_NULL_LEFTWIDTH = '100%';
const RIGHT_CONTENT_NULL_RIGHTWIDTH = '0vp';
const LEFT_PART_WIDTH = 'calc(66% - 16vp)';
const RIGHT_PART_WIDTH = '34%';
const LEFT_ONLY_ARROW_WIDTH = 'calc(100% - 40vp)';
const RIGHT_ONLY_ARROW_WIDTH = '24vp';
const ICON_SIZE_MAP = new Map([
  [IconType.BADGE, BADGE_SIZE],
  [IconType.NORMAL_ICON, SMALL_ICON_SIZE],
  [IconType.SYSTEM_ICON, SYSTEM_ICON_SIZE],
  [IconType.HEAD_SCULPTURE, HEADSCULPTURE_SIZE],
  [IconType.APP_ICON, APP_ICON_SIZE],
  [IconType.PREVIEW, PREVIEW_SIZE],
  [IconType.LONGITUDINAL, LONGITUDINAL_SIZE],
  [IconType.VERTICAL, VERTICAL_SIZE]
]);
class ContentItemStruct extends ViewPU {
  constructor(o10, p10, q10, r10 = -1, s10 = undefined, t10) {
    super(o10, q10, r10, t10);
    if (typeof s10 === "function") {
      this.paramsGenerator_ = s10;
    }
    this.iconStyle = null;
    this.icon = null;
    this.primaryText = null;
    this.secondaryText = null;
    this.description = null;
    this.itemRowSpace = NORMAL_ITEM_ROW_SPACE;
    this.__leftWidth = new ObservedPropertySimplePU(LEFT_PART_WIDTH, this, "leftWidth");
    this.setInitiallyProvidedValue(p10);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(n10) {
    if (n10.iconStyle !== undefined) {
      this.iconStyle = n10.iconStyle;
    }
    if (n10.icon !== undefined) {
      this.icon = n10.icon;
    }
    if (n10.primaryText !== undefined) {
      this.primaryText = n10.primaryText;
    }
    if (n10.secondaryText !== undefined) {
      this.secondaryText = n10.secondaryText;
    }
    if (n10.description !== undefined) {
      this.description = n10.description;
    }
    if (n10.itemRowSpace !== undefined) {
      this.itemRowSpace = n10.itemRowSpace;
    }
    if (n10.leftWidth !== undefined) {
      this.leftWidth = n10.leftWidth;
    }
  }
  updateStateVars(m10) {
  }
  purgeVariableDependenciesOnElmtId(l10) {
    this.__leftWidth.purgeDependencyOnElmtId(l10);
  }
  aboutToBeDeleted() {
    this.__leftWidth.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get leftWidth() {
    return this.__leftWidth.get();
  }
  set leftWidth(k10) {
    this.__leftWidth.set(k10);
  }
  aboutToAppear() {
    if (this.icon == null && this.iconStyle == null) {
      this.itemRowSpace = SPECIAL_ITEM_ROW_SPACE;
    }
  }
  createIcon(t9 = null) {
    this.observeComponentCreation((v9, w9) => {
      ViewStackProcessor.StartGetAccessRecordingFor(v9);
      If.create();
      if (this.icon != null && this.iconStyle != null) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((a10, b10) => {
            ViewStackProcessor.StartGetAccessRecordingFor(a10);
            If.create();
            if (this.iconStyle <= IconType.PREVIEW) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation((i10, j10) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(i10);
                  Image.create(this.icon);
                  Image.objectFit(ImageFit.Contain);
                  Image.width(ICON_SIZE_MAP.get(this.iconStyle));
                  Image.height(ICON_SIZE_MAP.get(this.iconStyle));
                  Image.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                  Image.focusable(true);
                  Image.draggable(false);
                  Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                  if (!j10) {
                    Image.pop();
                  }
                  ViewStackProcessor.StopGetAccessRecording();
                });
              });
            }
            else {
              this.ifElseBranchUpdateFunction(1, () => {
                this.observeComponentCreation((e10, f10) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(e10);
                  Image.create(this.icon);
                  Image.objectFit(ImageFit.Contain);
                  Image.constraintSize({
                    minWidth: SPECIAL_ICON_SIZE,
                    maxWidth: ICON_SIZE_MAP.get(this.iconStyle),
                    minHeight: SPECIAL_ICON_SIZE,
                    maxHeight: ICON_SIZE_MAP.get(this.iconStyle)
                  });
                  Image.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                  Image.focusable(true);
                  Image.draggable(false);
                  Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                  if (!f10) {
                    Image.pop();
                  }
                  ViewStackProcessor.StopGetAccessRecording();
                });
              });
            }
            if (!b10) {
              If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          If.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!w9) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
  }
  createText(w8 = null) {
    this.observeComponentCreation((r9, s9) => {
      ViewStackProcessor.StartGetAccessRecordingFor(r9);
      Column.create({ space: TEXT_COLUMN_SPACE });
      Column.flexShrink(1);
      Column.margin({
        top: TEXT_SAFE_MARGIN,
        bottom: TEXT_SAFE_MARGIN
      });
      Column.alignItems(HorizontalAlign.Start);
      if (!s9) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((p9, q9) => {
      ViewStackProcessor.StartGetAccessRecordingFor(p9);
      Text.create(this.primaryText);
      Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Text.maxLines(TEXT_MAX_LINE);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.fontWeight(FontWeight.Medium);
      Text.focusable(true);
      Text.draggable(false);
      if (!q9) {
        Text.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Text.pop();
    this.observeComponentCreation((i9, j9) => {
      ViewStackProcessor.StartGetAccessRecordingFor(i9);
      If.create();
      if (this.secondaryText != null) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((n9, o9) => {
            ViewStackProcessor.StartGetAccessRecordingFor(n9);
            Text.create(this.secondaryText);
            Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.maxLines(TEXT_MAX_LINE);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.focusable(true);
            Text.draggable(false);
            if (!o9) {
              Text.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          Text.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!j9) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.observeComponentCreation((b9, c9) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b9);
      If.create();
      if (this.description != null) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((g9, h9) => {
            ViewStackProcessor.StartGetAccessRecordingFor(g9);
            Text.create(this.description);
            Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.maxLines(TEXT_MAX_LINE);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.focusable(true);
            Text.draggable(false);
            if (!h9) {
              Text.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          Text.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!c9) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    Column.pop();
  }
  initialRender() {
    this.observeComponentCreation((u8, v8) => {
      ViewStackProcessor.StartGetAccessRecordingFor(u8);
      Row.create({ space: this.itemRowSpace });
      Row.margin({ right: 16 });
      Row.padding({ left: LISTITEM_PADDING });
      Row.width(this.leftWidth);
      Row.flexShrink(1);
      if (!v8) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.createIcon.bind(this)();
    this.createText.bind(this)();
    Row.pop();
  }
  rerender() {
    this.updateDirtyElements();
  }
}
class OperateItemStruct extends ViewPU {
  constructor(n8, o8, p8, q8 = -1, r8 = undefined, s8) {
    super(n8, p8, q8, s8);
    if (typeof r8 === "function") {
      this.paramsGenerator_ = r8;
    }
    this.arrow = null;
    this.icon = null;
    this.subIcon = null;
    this.button = null;
    this.switch = null;
    this.checkBox = null;
    this.radio = null;
    this.image = null;
    this.text = null;
    this.__switchState = new ObservedPropertySimplePU(false, this, "switchState");
    this.__radioState = new ObservedPropertySimplePU(false, this, "radioState");
    this.__checkBoxState = new ObservedPropertySimplePU(false, this, "checkBoxState");
    this.__rightWidth = new ObservedPropertySimplePU(RIGHT_PART_WIDTH, this, "rightWidth");
    this.__parentCanFocus = new SynchedPropertySimpleTwoWayPU(o8.parentCanFocus, this, "parentCanFocus");
    this.__parentCanTouch = new SynchedPropertySimpleTwoWayPU(o8.parentCanTouch, this, "parentCanTouch");
    this.__parentIsHover = new SynchedPropertySimpleTwoWayPU(o8.parentIsHover, this, "parentIsHover");
    this.__parentCanHover = new SynchedPropertySimpleTwoWayPU(o8.parentCanHover, this, "parentCanHover");
    this.__parentIsActive = new SynchedPropertySimpleTwoWayPU(o8.parentIsActive, this, "parentIsActive");
    this.__parentFrontColor = new SynchedPropertySimpleTwoWayPU(o8.parentFrontColor, this, "parentFrontColor");
    this.rowSpace = DEFAULT_ROW_SPACE;
    this.setInitiallyProvidedValue(o8);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(m8) {
    if (m8.arrow !== undefined) {
      this.arrow = m8.arrow;
    }
    if (m8.icon !== undefined) {
      this.icon = m8.icon;
    }
    if (m8.subIcon !== undefined) {
      this.subIcon = m8.subIcon;
    }
    if (m8.button !== undefined) {
      this.button = m8.button;
    }
    if (m8.switch !== undefined) {
      this.switch = m8.switch;
    }
    if (m8.checkBox !== undefined) {
      this.checkBox = m8.checkBox;
    }
    if (m8.radio !== undefined) {
      this.radio = m8.radio;
    }
    if (m8.image !== undefined) {
      this.image = m8.image;
    }
    if (m8.text !== undefined) {
      this.text = m8.text;
    }
    if (m8.switchState !== undefined) {
      this.switchState = m8.switchState;
    }
    if (m8.radioState !== undefined) {
      this.radioState = m8.radioState;
    }
    if (m8.checkBoxState !== undefined) {
      this.checkBoxState = m8.checkBoxState;
    }
    if (m8.rightWidth !== undefined) {
      this.rightWidth = m8.rightWidth;
    }
    if (m8.rowSpace !== undefined) {
      this.rowSpace = m8.rowSpace;
    }
  }
  updateStateVars(l8) {
  }
  purgeVariableDependenciesOnElmtId(k8) {
    this.__switchState.purgeDependencyOnElmtId(k8);
    this.__radioState.purgeDependencyOnElmtId(k8);
    this.__checkBoxState.purgeDependencyOnElmtId(k8);
    this.__rightWidth.purgeDependencyOnElmtId(k8);
    this.__parentCanFocus.purgeDependencyOnElmtId(k8);
    this.__parentCanTouch.purgeDependencyOnElmtId(k8);
    this.__parentIsHover.purgeDependencyOnElmtId(k8);
    this.__parentCanHover.purgeDependencyOnElmtId(k8);
    this.__parentIsActive.purgeDependencyOnElmtId(k8);
    this.__parentFrontColor.purgeDependencyOnElmtId(k8);
  }
  aboutToBeDeleted() {
    this.__switchState.aboutToBeDeleted();
    this.__radioState.aboutToBeDeleted();
    this.__checkBoxState.aboutToBeDeleted();
    this.__rightWidth.aboutToBeDeleted();
    this.__parentCanFocus.aboutToBeDeleted();
    this.__parentCanTouch.aboutToBeDeleted();
    this.__parentIsHover.aboutToBeDeleted();
    this.__parentCanHover.aboutToBeDeleted();
    this.__parentIsActive.aboutToBeDeleted();
    this.__parentFrontColor.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get switchState() {
    return this.__switchState.get();
  }
  set switchState(j8) {
    this.__switchState.set(j8);
  }
  get radioState() {
    return this.__radioState.get();
  }
  set radioState(i8) {
    this.__radioState.set(i8);
  }
  get checkBoxState() {
    return this.__checkBoxState.get();
  }
  set checkBoxState(h8) {
    this.__checkBoxState.set(h8);
  }
  get rightWidth() {
    return this.__rightWidth.get();
  }
  set rightWidth(g8) {
    this.__rightWidth.set(g8);
  }
  get parentCanFocus() {
    return this.__parentCanFocus.get();
  }
  set parentCanFocus(f8) {
    this.__parentCanFocus.set(f8);
  }
  get parentCanTouch() {
    return this.__parentCanTouch.get();
  }
  set parentCanTouch(e8) {
    this.__parentCanTouch.set(e8);
  }
  get parentIsHover() {
    return this.__parentIsHover.get();
  }
  set parentIsHover(d8) {
    this.__parentIsHover.set(d8);
  }
  get parentCanHover() {
    return this.__parentCanHover.get();
  }
  set parentCanHover(c8) {
    this.__parentCanHover.set(c8);
  }
  get parentIsActive() {
    return this.__parentIsActive.get();
  }
  set parentIsActive(b8) {
    this.__parentIsActive.set(b8);
  }
  get parentFrontColor() {
    return this.__parentFrontColor.get();
  }
  set parentFrontColor(a8) {
    this.__parentFrontColor.set(a8);
  }
  aboutToAppear() {
    if (this.switch != null) {
      this.switchState = this.switch.isCheck;
    }
    if (this.radio != null) {
      this.radioState = this.radio.isCheck;
    }
    if (this.checkBox != null) {
      this.checkBoxState = this.checkBox.isCheck;
    }
    if ((this.button == null && this.image == null && this.icon != null && this.text != null) ||
      (this.button == null && this.image == null && this.icon == null && this.arrow != null && this.text != null)) {
      this.rowSpace = SPECICAL_ROW_SPACE;
    }
  }
  createButton(k7, l7 = null) {
    this.observeComponentCreation((t7, u7) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t7);
      Button.createWithChild();
      Button.margin({ right: LISTITEM_PADDING });
      Button.hitTestBehavior(HitTestMode.Block);
      Button.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_button3'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Button.fontColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary_activated_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Button.height(BUTTON_SIZE);
      Button.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_button_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Button.labelStyle({
        maxLines: TEXT_MAX_LINE
      });
      Button.onFocus(() => {
        this.parentCanFocus = false;
      });
      Button.onTouch((z7) => {
        if (z7.type == TouchType.Down) {
          this.parentCanTouch = false;
        }
        if (z7.type == TouchType.Up) {
          this.parentCanTouch = true;
        }
      });
      Button.onHover((y7) => {
        this.parentCanHover = false;
        if (y7 && this.parentFrontColor == HOVERING_COLOR) {
          this.parentFrontColor = this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString();
        }
        if (!y7) {
          this.parentCanHover = true;
          if (this.parentIsHover) {
            this.parentFrontColor = this.parentIsHover ? HOVERING_COLOR : (this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString());
          }
        }
      });
      if (!u7) {
        Button.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((r7, s7) => {
      ViewStackProcessor.StartGetAccessRecordingFor(r7);
      Row.create();
      Row.padding({
        left: TEXT_SAFE_MARGIN,
        right: TEXT_SAFE_MARGIN
      });
      if (!s7) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((p7, q7) => {
      ViewStackProcessor.StartGetAccessRecordingFor(p7);
      Text.create(k7);
      Text.focusable(true);
      if (!q7) {
        Text.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Text.pop();
    Row.pop();
    Button.pop();
  }
  createIcon(x6, y6 = null) {
    this.observeComponentCreation((d7, e7) => {
      ViewStackProcessor.StartGetAccessRecordingFor(d7);
      Button.createWithChild({ type: ButtonType.Normal });
      Button.hitTestBehavior(HitTestMode.Block);
      Button.backgroundColor(Color.Transparent);
      Button.height(OPERATEITEM_ICON_CLICKABLE_SIZE);
      Button.width(OPERATEITEM_ICON_CLICKABLE_SIZE);
      Button.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Button.onFocus(() => {
        this.parentCanFocus = false;
      });
      Button.onTouch((j7) => {
        if (j7.type == TouchType.Down) {
          this.parentCanTouch = false;
        }
        if (j7.type == TouchType.Up) {
          this.parentCanTouch = true;
        }
      });
      Button.onHover((i7) => {
        this.parentCanHover = false;
        if (i7 && this.parentFrontColor == HOVERING_COLOR) {
          this.parentFrontColor = this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString();
        }
        if (!i7) {
          this.parentCanHover = true;
          if (this.parentIsHover) {
            this.parentFrontColor = this.parentIsHover ? HOVERING_COLOR : (this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString());
          }
        }
      });
      Button.onClick((x6.action));
      if (!e7) {
        Button.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((b7, c7) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b7);
      Image.create(x6.value);
      Image.height(OPERATEITEM_ICONLIKE_SIZE);
      Image.width(OPERATEITEM_ICONLIKE_SIZE);
      Image.focusable(true);
      Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Image.draggable(false);
      if (!c7) {
        Image.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Button.pop();
  }
  createImage(s6, t6 = null) {
    this.observeComponentCreation((v6, w6) => {
      ViewStackProcessor.StartGetAccessRecordingFor(v6);
      Image.create(s6);
      Image.height(OPERATEITEM_IMAGE_SIZE);
      Image.width(OPERATEITEM_IMAGE_SIZE);
      Image.draggable(false);
      Image.margin({ right: LISTITEM_PADDING });
      if (!w6) {
        Image.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
  }
  createText(n6, o6 = null) {
    this.observeComponentCreation((q6, r6) => {
      ViewStackProcessor.StartGetAccessRecordingFor(q6);
      Text.create(n6);
      Text.margin({ right: LISTITEM_PADDING });
      Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Text.focusable(true);
      Text.draggable(false);
      Text.flexShrink(1);
      if (!r6) {
        Text.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Text.pop();
  }
  createArrow(a6, b6 = null) {
    this.observeComponentCreation((g6, h6) => {
      ViewStackProcessor.StartGetAccessRecordingFor(g6);
      Button.createWithChild({ type: ButtonType.Normal });
      Button.margin({ right: LISTITEM_PADDING });
      Button.hitTestBehavior(HitTestMode.Block);
      Button.backgroundColor(Color.Transparent);
      Button.height(OPERATEITEM_ICONLIKE_SIZE);
      Button.width(OPERATEITEM_ARROW_WIDTH);
      Button.onFocus(() => {
        this.parentCanFocus = false;
      });
      Button.onTouch((m6) => {
        if (m6.type == TouchType.Down) {
          this.parentCanTouch = false;
        }
        if (m6.type == TouchType.Up) {
          this.parentCanTouch = true;
        }
      });
      Button.onHover((l6) => {
        this.parentCanHover = false;
        if (l6 && this.parentFrontColor == HOVERING_COLOR) {
          this.parentFrontColor = this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString();
        }
        if (!l6) {
          this.parentCanHover = true;
          if (this.parentIsHover) {
            this.parentFrontColor = this.parentIsHover ? HOVERING_COLOR : (this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString());
          }
        }
      });
      Button.onClick(a6.action);
      if (!h6) {
        Button.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((e6, f6) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e6);
      Image.create(a6.value);
      Image.height(OPERATEITEM_ICONLIKE_SIZE);
      Image.width(OPERATEITEM_ARROW_WIDTH);
      Image.focusable(true);
      Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_fourth'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Image.draggable(false);
      if (!f6) {
        Image.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Button.pop();
  }
  createRadio(q5, r5 = null) {
    this.observeComponentCreation((t5, u5) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t5);
      Radio.create({ value: '', group: '' });
      Radio.margin({ right: LISTITEM_PADDING });
      Radio.checked(this.radioState);
      Radio.onChange(q5.onChange);
      Radio.height(OPERATEITEM_ICONLIKE_SIZE);
      Radio.width(OPERATEITEM_ICONLIKE_SIZE);
      Radio.onFocus(() => {
        this.parentCanFocus = false;
      });
      Radio.hitTestBehavior(HitTestMode.Block);
      Radio.onTouch((z5) => {
        if (z5.type == TouchType.Down) {
          this.parentCanTouch = false;
        }
        if (z5.type == TouchType.Up) {
          this.parentCanTouch = true;
        }
      });
      Radio.onHover((y5) => {
        this.parentCanHover = false;
        if (y5 && this.parentFrontColor == HOVERING_COLOR) {
          this.parentFrontColor = this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString();
        }
        if (!y5) {
          this.parentCanHover = true;
          if (this.parentIsHover) {
            this.parentFrontColor = this.parentIsHover ? HOVERING_COLOR : (this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString());
          }
        }
      });
      if (!u5) {
        Radio.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
  }
  createCheckBox(g5, h5 = null) {
    this.observeComponentCreation((j5, k5) => {
      ViewStackProcessor.StartGetAccessRecordingFor(j5);
      Checkbox.create();
      Checkbox.margin({ right: LISTITEM_PADDING });
      Checkbox.select(this.checkBoxState);
      Checkbox.onChange(g5.onChange);
      Checkbox.height(OPERATEITEM_ICONLIKE_SIZE);
      Checkbox.height(OPERATEITEM_ICONLIKE_SIZE);
      Checkbox.onFocus(() => {
        this.parentCanFocus = false;
      });
      Checkbox.hitTestBehavior(HitTestMode.Block);
      Checkbox.onTouch((p5) => {
        if (p5.type == TouchType.Down) {
          this.parentCanTouch = false;
        }
        if (p5.type == TouchType.Up) {
          this.parentCanTouch = true;
        }
      });
      Checkbox.onHover((o5) => {
        this.parentCanHover = false;
        if (o5 && this.parentFrontColor == HOVERING_COLOR) {
          this.parentFrontColor = this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString();
        }
        if (!o5) {
          this.parentCanHover = true;
          if (this.parentIsHover) {
            this.parentFrontColor = this.parentIsHover ? HOVERING_COLOR : (this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString());
          }
        }
      });
      if (!k5) {
        Checkbox.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Checkbox.pop();
  }
  createSwitch(s4, t4 = null) {
    this.observeComponentCreation((z4, a5) => {
      ViewStackProcessor.StartGetAccessRecordingFor(z4);
      Row.create();
      Row.margin({ right: SWITCH_PADDING });
      Row.height(OPERATEITEM_ICON_CLICKABLE_SIZE);
      Row.width(OPERATEITEM_ICON_CLICKABLE_SIZE);
      Row.justifyContent(FlexAlign.Center);
      Row.onFocus(() => {
        this.parentCanFocus = false;
      });
      Row.onTouch((f5) => {
        if (f5.type == TouchType.Down) {
          this.parentCanTouch = false;
        }
        if (f5.type == TouchType.Up) {
          this.parentCanTouch = true;
        }
      });
      Row.onHover((e5) => {
        this.parentCanHover = false;
        if (e5 && this.parentFrontColor == HOVERING_COLOR) {
          this.parentFrontColor = this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString();
        }
        if (!e5) {
          this.parentCanHover = true;
          if (this.parentIsHover) {
            this.parentFrontColor = this.parentIsHover ? HOVERING_COLOR : (this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString());
          }
        }
      });
      if (!a5) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((w4, x4) => {
      ViewStackProcessor.StartGetAccessRecordingFor(w4);
      Toggle.create({ type: ToggleType.Switch, isOn: this.switchState });
      Toggle.onChange(s4.onChange);
      Toggle.onClick(() => {
        this.switchState = !this.switchState;
      });
      Toggle.hitTestBehavior(HitTestMode.Block);
      if (!x4) {
        Toggle.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Toggle.pop();
    Row.pop();
  }
  createTextArrow(y3, z3, a4 = null) {
    this.observeComponentCreation((l4, m4) => {
      ViewStackProcessor.StartGetAccessRecordingFor(l4);
      Button.createWithChild({ type: ButtonType.Normal });
      Button.hitTestBehavior(HitTestMode.Block);
      Button.labelStyle({
        maxLines: TEXT_MAX_LINE
      });
      Button.backgroundColor(Color.Transparent);
      Button.height(TEXT_ARROW_HEIGHT);
      Button.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Button.onFocus(() => {
        this.parentCanFocus = false;
      });
      Button.onTouch((r4) => {
        if (r4.type == TouchType.Down) {
          this.parentCanTouch = false;
        }
        if (r4.type == TouchType.Up) {
          this.parentCanTouch = true;
        }
      });
      Button.onHover((q4) => {
        this.parentCanHover = false;
        if (q4 && this.parentFrontColor == HOVERING_COLOR) {
          this.parentFrontColor = this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString();
        }
        if (!q4) {
          this.parentCanHover = true;
          if (this.parentIsHover) {
            this.parentFrontColor = this.parentIsHover ? HOVERING_COLOR : (this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString());
          }
        }
      });
      Button.onClick(z3.action);
      if (!m4) {
        Button.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((j4, k4) => {
      ViewStackProcessor.StartGetAccessRecordingFor(j4);
      Row.create({ space: SPECICAL_ROW_SPACE });
      Row.padding({
        left: TEXT_SAFE_MARGIN,
        right: LISTITEM_PADDING
      });
      if (!k4) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((h4, i4) => {
      ViewStackProcessor.StartGetAccessRecordingFor(h4);
      Text.create(y3);
      Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Text.focusable(true);
      Text.draggable(false);
      Text.constraintSize({
        maxWidth: `calc(100% - ${OPERATEITEM_ARROW_WIDTH}vp)`
      });
      if (!i4) {
        Text.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Text.pop();
    this.observeComponentCreation((f4, g4) => {
      ViewStackProcessor.StartGetAccessRecordingFor(f4);
      Image.create(z3.value);
      Image.height(OPERATEITEM_ICONLIKE_SIZE);
      Image.width(OPERATEITEM_ARROW_WIDTH);
      Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_fourth'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Image.focusable(true);
      Image.draggable(false);
      if (!g4) {
        Image.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Row.pop();
    Button.pop();
  }
  initialRender() {
    this.observeComponentCreation((w3, x3) => {
      ViewStackProcessor.StartGetAccessRecordingFor(w3);
      Row.create({
        space: this.rowSpace
      });
      Row.width(this.rightWidth);
      Row.flexShrink(1);
      Row.justifyContent(FlexAlign.End);
      if (!x3) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((e3, f3) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e3);
      If.create();
      if (this.button != null) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.createButton.bind(this)(this.button.text);
        });
      }
      else if (this.image != null) {
        this.ifElseBranchUpdateFunction(1, () => {
          this.createImage.bind(this)(this.image);
        });
      }
      else if (this.icon != null && this.text != null) {
        this.ifElseBranchUpdateFunction(2, () => {
          this.createText.bind(this)(this.text);
          this.createIcon.bind(this)(this.icon);
        });
      }
      else if (this.arrow != null && this.text == null) {
        this.ifElseBranchUpdateFunction(3, () => {
          this.createArrow.bind(this)(this.arrow);
        });
      }
      else if (this.arrow != null && this.text != null) {
        this.ifElseBranchUpdateFunction(4, () => {
          this.createTextArrow.bind(this)(this.text, this.arrow);
        });
      }
      else if (this.text != null) {
        this.ifElseBranchUpdateFunction(5, () => {
          this.createText.bind(this)(this.text);
        });
      }
      else if (this.radio != null) {
        this.ifElseBranchUpdateFunction(6, () => {
          this.createRadio.bind(this)(this.radio);
        });
      }
      else if (this.checkBox != null) {
        this.ifElseBranchUpdateFunction(7, () => {
          this.createCheckBox.bind(this)(this.checkBox);
        });
      }
      else if (this.switch != null) {
        this.ifElseBranchUpdateFunction(8, () => {
          this.createSwitch.bind(this)(this.switch);
        });
      }
      else if (this.icon != null) {
        this.ifElseBranchUpdateFunction(9, () => {
          this.createIcon.bind(this)(this.icon);
          this.observeComponentCreation((j3, k3) => {
            ViewStackProcessor.StartGetAccessRecordingFor(j3);
            If.create();
            if (this.subIcon != null) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.createIcon.bind(this)(this.subIcon);
              });
            }
            else {
              this.ifElseBranchUpdateFunction(1, () => {
              });
            }
            if (!k3) {
              If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          If.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(10, () => {
        });
      }
      if (!f3) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    Row.pop();
  }
  rerender() {
    this.updateDirtyElements();
  }
}
export class ComposeListItem extends ViewPU {
  constructor(w2, x2, y2, z2 = -1, a3 = undefined, b3) {
    super(w2, y2, z2, b3);
    if (typeof a3 === "function") {
      this.paramsGenerator_ = a3;
    }
    this.__contentItem = new SynchedPropertyObjectOneWayPU(x2.contentItem, this, "contentItem");
    this.__operateItem = new SynchedPropertyObjectOneWayPU(x2.operateItem, this, "operateItem");
    this.__frontColor = new ObservedPropertySimplePU(Color.Transparent.toString(), this, "frontColor");
    this.__borderSize = new ObservedPropertySimplePU(0, this, "borderSize");
    this.__canFocus = new ObservedPropertySimplePU(false, this, "canFocus");
    this.__canTouch = new ObservedPropertySimplePU(true, this, "canTouch");
    this.__canHover = new ObservedPropertySimplePU(true, this, "canHover");
    this.__isHover = new ObservedPropertySimplePU(true, this, "isHover");
    this.__itemHeight = new ObservedPropertySimplePU(ItemHeight.FIRST_HEIGHT, this, "itemHeight");
    this.__isActive = new ObservedPropertySimplePU(false, this, "isActive");
    this.setInitiallyProvidedValue(x2);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(v2) {
    if (v2.contentItem === undefined) {
      this.__contentItem.set(null);
    }
    if (v2.operateItem === undefined) {
      this.__operateItem.set(null);
    }
    if (v2.frontColor !== undefined) {
      this.frontColor = v2.frontColor;
    }
    if (v2.borderSize !== undefined) {
      this.borderSize = v2.borderSize;
    }
    if (v2.canFocus !== undefined) {
      this.canFocus = v2.canFocus;
    }
    if (v2.canTouch !== undefined) {
      this.canTouch = v2.canTouch;
    }
    if (v2.canHover !== undefined) {
      this.canHover = v2.canHover;
    }
    if (v2.isHover !== undefined) {
      this.isHover = v2.isHover;
    }
    if (v2.itemHeight !== undefined) {
      this.itemHeight = v2.itemHeight;
    }
    if (v2.isActive !== undefined) {
      this.isActive = v2.isActive;
    }
  }
  updateStateVars(u2) {
    this.__contentItem.reset(u2.contentItem);
    this.__operateItem.reset(u2.operateItem);
  }
  purgeVariableDependenciesOnElmtId(t2) {
    this.__contentItem.purgeDependencyOnElmtId(t2);
    this.__operateItem.purgeDependencyOnElmtId(t2);
    this.__frontColor.purgeDependencyOnElmtId(t2);
    this.__borderSize.purgeDependencyOnElmtId(t2);
    this.__canFocus.purgeDependencyOnElmtId(t2);
    this.__canTouch.purgeDependencyOnElmtId(t2);
    this.__canHover.purgeDependencyOnElmtId(t2);
    this.__isHover.purgeDependencyOnElmtId(t2);
    this.__itemHeight.purgeDependencyOnElmtId(t2);
    this.__isActive.purgeDependencyOnElmtId(t2);
  }
  aboutToBeDeleted() {
    this.__contentItem.aboutToBeDeleted();
    this.__operateItem.aboutToBeDeleted();
    this.__frontColor.aboutToBeDeleted();
    this.__borderSize.aboutToBeDeleted();
    this.__canFocus.aboutToBeDeleted();
    this.__canTouch.aboutToBeDeleted();
    this.__canHover.aboutToBeDeleted();
    this.__isHover.aboutToBeDeleted();
    this.__itemHeight.aboutToBeDeleted();
    this.__isActive.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get contentItem() {
    return this.__contentItem.get();
  }
  set contentItem(s2) {
    this.__contentItem.set(s2);
  }
  get operateItem() {
    return this.__operateItem.get();
  }
  set operateItem(r2) {
    this.__operateItem.set(r2);
  }
  get frontColor() {
    return this.__frontColor.get();
  }
  set frontColor(q2) {
    this.__frontColor.set(q2);
  }
  get borderSize() {
    return this.__borderSize.get();
  }
  set borderSize(p2) {
    this.__borderSize.set(p2);
  }
  get canFocus() {
    return this.__canFocus.get();
  }
  set canFocus(o2) {
    this.__canFocus.set(o2);
  }
  get canTouch() {
    return this.__canTouch.get();
  }
  set canTouch(n2) {
    this.__canTouch.set(n2);
  }
  get canHover() {
    return this.__canHover.get();
  }
  set canHover(m2) {
    this.__canHover.set(m2);
  }
  get isHover() {
    return this.__isHover.get();
  }
  set isHover(l2) {
    this.__isHover.set(l2);
  }
  get itemHeight() {
    return this.__itemHeight.get();
  }
  set itemHeight(k2) {
    this.__itemHeight.set(k2);
  }
  get isActive() {
    return this.__isActive.get();
  }
  set isActive(j2) {
    this.__isActive.set(j2);
  }
  aboutToAppear() {
    var b2, c2, d2, e2, f2, g2, h2, i2;
    if (this.contentItem === undefined) {
      if (((b2 = this.operateItem) === null || b2 === void 0 ? void 0 : b2.image) !== undefined || ((c2 = this.operateItem) === null || c2 === void 0 ? void 0 : c2.icon) !== undefined || ((d2 = this.operateItem) === null || d2 === void 0 ? void 0 : d2.subIcon) !== undefined) {
        this.itemHeight = OPERATEITEM_IMAGE_SIZE + SAFE_LIST_PADDING;
      }
      return;
    }
    if (((e2 = this.contentItem) === null || e2 === void 0 ? void 0 : e2.secondaryText) === undefined && ((f2 = this.contentItem) === null || f2 === void 0 ? void 0 : f2.description) === undefined) {
      if (((g2 = this.contentItem) === null || g2 === void 0 ? void 0 : g2.icon) === undefined) {
        this.itemHeight = ItemHeight.FIRST_HEIGHT;
      }
      else {
        this.itemHeight = this.contentItem.iconStyle <= IconType.HEAD_SCULPTURE ? ItemHeight.SECOND_HEIGHT : ItemHeight.THIRD_HEIGHT;
      }
    }
    else if (this.contentItem.description === undefined) {
      if (this.contentItem.icon === undefined || (this.contentItem.icon !== undefined && this.contentItem.iconStyle <= IconType.SYSTEM_ICON)) {
        this.itemHeight = ItemHeight.THIRD_HEIGHT;
      }
      else {
        this.itemHeight = ItemHeight.FOURTH_HEIGHT;
      }
    }
    else {
      this.itemHeight = ItemHeight.FIFTH_HEIGHT;
    }
    if (ICON_SIZE_MAP.get((h2 = this.contentItem) === null || h2 === void 0 ? void 0 : h2.iconStyle) >= this.itemHeight) {
      this.itemHeight = ICON_SIZE_MAP.get((i2 = this.contentItem) === null || i2 === void 0 ? void 0 : i2.iconStyle) + SAFE_LIST_PADDING;
    }
  }
  calculatedLeftWidth() {
    if (this.operateItem === null || JSON.stringify(this.operateItem) === '{}') {
      return RIGHT_CONTENT_NULL_LEFTWIDTH;
    }
    else if (this.operateItem.arrow != null && this.operateItem.text == null) {
      return LEFT_ONLY_ARROW_WIDTH;
    }
    else {
      return LEFT_PART_WIDTH;
    }
  }
  calculatedRightWidth() {
    if (this.operateItem === null || JSON.stringify(this.operateItem) === '{}') {
      return RIGHT_CONTENT_NULL_RIGHTWIDTH;
    }
    else if (this.operateItem.arrow != null && this.operateItem.text == null) {
      return RIGHT_ONLY_ARROW_WIDTH;
    }
    else {
      return RIGHT_PART_WIDTH;
    }
  }
  initialRender() {
    this.observeComponentCreation((z1, a2) => {
      ViewStackProcessor.StartGetAccessRecordingFor(z1);
      Stack.create();
      Stack.padding({
        left: STACK_PADDING,
        right: STACK_PADDING
      });
      if (!a2) {
        Stack.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((r1, s1) => {
      ViewStackProcessor.StartGetAccessRecordingFor(r1);
      Flex.create({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center });
      Flex.height(this.itemHeight);
      Flex.focusable(true);
      Flex.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Flex.backgroundColor(this.frontColor);
      Flex.onFocus(() => {
        this.canFocus = true;
      });
      Flex.onBlur(() => {
        this.canFocus = false;
      });
      Flex.onHover((y1) => {
        this.isHover = y1;
        if (this.canHover) {
          this.frontColor = y1 ? HOVERING_COLOR : (this.isActive ? ACTIVED_COLOR : Color.Transparent.toString());
        }
      });
      Flex.onTouch((x1) => {
        if (x1.type == TouchType.Down && this.canTouch) {
          this.frontColor = TOUCH_DOWN_COLOR;
        }
        if (x1.type == TouchType.Up) {
          this.frontColor = this.isActive ? ACTIVED_COLOR : Color.Transparent.toString();
        }
      });
      ViewStackProcessor.visualState("focused");
      Flex.border({
        radius: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        width: ITEM_BORDER_SHOWN,
        color: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_focused_outline'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        style: BorderStyle.Solid
      });
      ViewStackProcessor.visualState("normal");
      Flex.border({
        radius: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        width: ITEM_BORDER_SHOWN,
        color: Color.Transparent
      });
      ViewStackProcessor.visualState();
      if (!s1) {
        Flex.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((g1, h1) => {
      ViewStackProcessor.StartGetAccessRecordingFor(g1);
      If.create();
      if (this.contentItem === null) {
        this.ifElseBranchUpdateFunction(0, () => {
          {
            this.observeComponentCreation((l1, m1) => {
              ViewStackProcessor.StartGetAccessRecordingFor(l1);
              if (m1) {
                let n1 = new ContentItemStruct(this, {}, undefined, l1, () => { }, { page: "library/src/main/ets/components/mainpage/composelistitem.ets", line: 679 });
                ViewPU.create(n1);
                let o1 = () => {
                  return {};
                };
                n1.paramsGenerator_ = o1;
              }
              else {
                this.updateStateVarsOfChildByElmtId(l1, {});
              }
              ViewStackProcessor.StopGetAccessRecording();
            });
          }
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!h1) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.observeComponentCreation((v, w) => {
      ViewStackProcessor.StartGetAccessRecordingFor(v);
      If.create();
      if (this.contentItem !== null) {
        this.ifElseBranchUpdateFunction(0, () => {
          {
            this.observeComponentCreation((a1, b1) => {
              ViewStackProcessor.StartGetAccessRecordingFor(a1);
              if (b1) {
                let c1 = new ContentItemStruct(this, {
                  icon: this.contentItem.icon,
                  iconStyle: this.contentItem.iconStyle,
                  primaryText: this.contentItem.primaryText,
                  secondaryText: this.contentItem.secondaryText,
                  description: this.contentItem.description,
                  leftWidth: this.calculatedLeftWidth()
                }, undefined, a1, () => { }, { page: "library/src/main/ets/components/mainpage/composelistitem.ets", line: 682 });
                ViewPU.create(c1);
                let d1 = () => {
                  return {
                    icon: this.contentItem.icon,
                    iconStyle: this.contentItem.iconStyle,
                    primaryText: this.contentItem.primaryText,
                    secondaryText: this.contentItem.secondaryText,
                    description: this.contentItem.description,
                    leftWidth: this.calculatedLeftWidth()
                  };
                };
                c1.paramsGenerator_ = d1;
              }
              else {
                this.updateStateVarsOfChildByElmtId(a1, {});
              }
              ViewStackProcessor.StopGetAccessRecording();
            });
          }
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!w) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.observeComponentCreation((f, g) => {
      ViewStackProcessor.StartGetAccessRecordingFor(f);
      If.create();
      if (this.operateItem !== null) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((r, s) => {
            ViewStackProcessor.StartGetAccessRecordingFor(r);
            __Common__.create();
            __Common__.onFocus(() => {
              this.canFocus = false;
            });
            __Common__.onBlur(() => {
              this.canFocus = true;
            });
            if (!s) {
              __Common__.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          {
            this.observeComponentCreation((l, m) => {
              ViewStackProcessor.StartGetAccessRecordingFor(l);
              if (m) {
                let n = new OperateItemStruct(this, {
                  icon: this.operateItem.icon,
                  subIcon: this.operateItem.subIcon,
                  button: this.operateItem.button,
                  switch: this.operateItem.switch,
                  checkBox: this.operateItem.checkbox,
                  radio: this.operateItem.radio,
                  image: this.operateItem.image,
                  text: this.operateItem.text,
                  arrow: this.operateItem.arrow,
                  parentCanFocus: this.__canFocus,
                  parentCanTouch: this.__canTouch,
                  parentIsHover: this.__isHover,
                  parentFrontColor: this.__frontColor,
                  parentIsActive: this.__isActive,
                  parentCanHover: this.__canHover,
                  rightWidth: this.calculatedRightWidth()
                }, undefined, l, () => { }, { page: "library/src/main/ets/components/mainpage/composelistitem.ets", line: 692 });
                ViewPU.create(n);
                let o = () => {
                  return {
                    icon: this.operateItem.icon,
                    subIcon: this.operateItem.subIcon,
                    button: this.operateItem.button,
                    switch: this.operateItem.switch,
                    checkBox: this.operateItem.checkbox,
                    radio: this.operateItem.radio,
                    image: this.operateItem.image,
                    text: this.operateItem.text,
                    arrow: this.operateItem.arrow,
                    parentCanFocus: this.canFocus,
                    parentCanTouch: this.canTouch,
                    parentIsHover: this.isHover,
                    parentFrontColor: this.frontColor,
                    parentIsActive: this.isActive,
                    parentCanHover: this.canHover,
                    rightWidth: this.calculatedRightWidth()
                  };
                };
                n.paramsGenerator_ = o;
              }
              else {
                this.updateStateVarsOfChildByElmtId(l, {});
              }
              ViewStackProcessor.StopGetAccessRecording();
            });
          }
          __Common__.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!g) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    Flex.pop();
    Stack.pop();
  }
  rerender() {
    this.updateDirtyElements();
  }
}

export default { IconType, ComposeListItem };