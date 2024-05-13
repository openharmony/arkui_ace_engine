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
  constructor(t10, u10, v10, w10 = -1, x10 = undefined, y10) {
    super(t10, v10, w10, y10);
    if (typeof x10 === 'function') {
      this.paramsGenerator_ = x10;
    }
    this.iconStyle = null;
    this.icon = null;
    this.primaryText = null;
    this.secondaryText = null;
    this.description = null;
    this.itemRowSpace = NORMAL_ITEM_ROW_SPACE;
    this.__leftWidth = new ObservedPropertySimplePU(LEFT_PART_WIDTH, this, "leftWidth");
    this.__primaryTextColor = new ObservedPropertyObjectPU({
      'id': -1,
      'type': 10001,
      params: ['sys.color.ohos_id_color_text_primary'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__',
    }, this, 'primaryTextColor');
    this.__secondaryTextColor = new ObservedPropertyObjectPU({
      'id': -1,
      'type': 10001,
      params: ['sys.color.ohos_id_color_text_secondary'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__',
    }, this, 'secondaryTextColor');
    this.__descriptionColor = new ObservedPropertyObjectPU({
      'id': -1,
      'type': 10001,
      params: ['sys.color.ohos_id_color_text_secondary'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__',
    }, this, 'descriptionColor');
    this.setInitiallyProvidedValue(u10);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(s10) {
    if (s10.iconStyle !== undefined) {
      this.iconStyle = s10.iconStyle;
    }
    if (s10.icon !== undefined) {
      this.icon = s10.icon;
    }
    if (s10.primaryText !== undefined) {
      this.primaryText = s10.primaryText;
    }
    if (s10.secondaryText !== undefined) {
      this.secondaryText = s10.secondaryText;
    }
    if (s10.description !== undefined) {
      this.description = s10.description;
    }
    if (s10.itemRowSpace !== undefined) {
      this.itemRowSpace = s10.itemRowSpace;
    }
    if (s10.leftWidth !== undefined) {
      this.leftWidth = s10.leftWidth;
    }
    if (s10.primaryTextColor !== undefined) {
      this.primaryTextColor = s10.primaryTextColor;
    }
    if (s10.secondaryTextColor !== undefined) {
      this.secondaryTextColor = s10.secondaryTextColor;
    }
    if (s10.descriptionColor !== undefined) {
      this.descriptionColor = s10.descriptionColor;
    }
  }
  updateStateVars(r10) {
  }
  purgeVariableDependenciesOnElmtId(q10) {
    this.__leftWidth.purgeDependencyOnElmtId(q10);
    this.__primaryTextColor.purgeDependencyOnElmtId(q10);
    this.__secondaryTextColor.purgeDependencyOnElmtId(q10);
    this.__descriptionColor.purgeDependencyOnElmtId(q10);
  }
  aboutToBeDeleted() {
    this.__leftWidth.aboutToBeDeleted();
    this.__primaryTextColor.aboutToBeDeleted();
    this.__secondaryTextColor.aboutToBeDeleted();
    this.__descriptionColor.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get leftWidth() {
    return this.__leftWidth.get();
  }
  set leftWidth(p10) {
    this.__leftWidth.set(p10);
  }
  get primaryTextColor() {
    return this.__primaryTextColor.get();
  }
  set primaryTextColor(o10) {
    this.__primaryTextColor.set(o10);
  }
  get secondaryTextColor() {
    return this.__secondaryTextColor.get();
  }
  set secondaryTextColor(n10) {
    this.__secondaryTextColor.set(n10);
  }
  get descriptionColor() {
    return this.__descriptionColor.get();
  }
  set descriptionColor(m10) {
    this.__descriptionColor.set(m10);
  }
  onWillApplyTheme(l10) {
    this.primaryTextColor = l10.colors.fontPrimary;
    this.secondaryTextColor = l10.colors.fontSecondary;
    this.descriptionColor = l10.colors.fontTertiary;
  }
  aboutToAppear() {
    if (this.icon == null && this.iconStyle == null) {
      this.itemRowSpace = SPECIAL_ITEM_ROW_SPACE;
    }
  }
  createIcon(u9 = null) {
    this.observeComponentCreation2((w9, x9) => {
      If.create();
      if (this.icon != null && this.iconStyle != null) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((b10, c10) => {
            If.create();
            if (this.iconStyle <= IconType.PREVIEW) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation2((j10, k10) => {
                  Image.create(this.icon);
                  Image.objectFit(ImageFit.Contain);
                  Image.width(ICON_SIZE_MAP.get(this.iconStyle));
                  Image.height(ICON_SIZE_MAP.get(this.iconStyle));
                  Image.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                  Image.focusable(true);
                  Image.draggable(false);
                  Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                }, Image);
              });
            }
            else {
              this.ifElseBranchUpdateFunction(1, () => {
                this.observeComponentCreation2((f10, g10) => {
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
                }, Image);
              });
            }
          }, If);
          If.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
    }, If);
    If.pop();
  }
  createText(x8 = null) {
    this.observeComponentCreation2((s9, t9) => {
      Column.create({ space: TEXT_COLUMN_SPACE });
      Column.flexShrink(1);
      Column.margin({
        top: TEXT_SAFE_MARGIN,
        bottom: TEXT_SAFE_MARGIN
      });
      Column.alignItems(HorizontalAlign.Start);
    }, Column);
    this.observeComponentCreation2((q9, r9) => {
      Text.create(this.primaryText);
      Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Text.fontColor(ObservedObject.GetRawObject(this.primaryTextColor));
      Text.maxLines(TEXT_MAX_LINE);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.fontWeight(FontWeight.Medium);
      Text.focusable(true);
      Text.draggable(false);
      Text.key('composeListItem_ContentItemPrimaryText');
    }, Text);
    Text.pop();
    this.observeComponentCreation2((j9, k9) => {
      If.create();
      if (this.secondaryText != null) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((o9, p9) => {
            Text.create(this.secondaryText);
            Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.fontColor(ObservedObject.GetRawObject(this.secondaryTextColor));
            Text.maxLines(TEXT_MAX_LINE);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.focusable(true);
            Text.draggable(false);
            Text.key('composeListItem_ContentItemSecondaryText');
          }, Text);
          Text.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
    }, If);
    If.pop();
    this.observeComponentCreation2((c9, d9) => {
      If.create();
      if (this.description != null) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((h9, i9) => {
            Text.create(this.description);
            Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.fontColor(ObservedObject.GetRawObject(this.descriptionColor));
            Text.maxLines(TEXT_MAX_LINE);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.focusable(true);
            Text.draggable(false);
            Text.key('composeListItem_ContentItemDescription');
          }, Text);
          Text.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
    }, If);
    If.pop();
    Column.pop();
  }
  initialRender() {
    this.observeComponentCreation2((v8, w8) => {
      Row.create({ space: this.itemRowSpace });
      Row.margin({ right: 16 });
      Row.padding({ left: LISTITEM_PADDING });
      Row.width(this.leftWidth);
      Row.flexShrink(1);
    }, Row);
    this.createIcon.bind(this)();
    this.createText.bind(this)();
    Row.pop();
  }
  rerender() {
    this.updateDirtyElements();
  }
}
class OperateItemStruct extends ViewPU {
  constructor(o8, p8, q8, r8 = -1, s8 = undefined, t8) {
    super(o8, q8, r8, t8);
    if (typeof s8 === 'function') {
      this.paramsGenerator_ = s8;
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
    this.__secondaryTextColor = new ObservedPropertyObjectPU({
      'id': -1,
      'type': 10001,
      params: ['sys.color.ohos_id_color_text_secondary'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__',
    }, this, 'secondaryTextColor');
    this.__hoveringColor = new ObservedPropertyObjectPU('#0d000000', this, 'hoveringColor');
    this.__activedColor = new ObservedPropertyObjectPU('#1a0a59f7', this, 'activedColor');
    this.__parentCanFocus = new SynchedPropertySimpleTwoWayPU(p8.parentCanFocus, this, 'parentCanFocus');
    this.__parentCanTouch = new SynchedPropertySimpleTwoWayPU(p8.parentCanTouch, this, 'parentCanTouch');
    this.__parentIsHover = new SynchedPropertySimpleTwoWayPU(p8.parentIsHover, this, 'parentIsHover');
    this.__parentCanHover = new SynchedPropertySimpleTwoWayPU(p8.parentCanHover, this, 'parentCanHover');
    this.__parentIsActive = new SynchedPropertySimpleTwoWayPU(p8.parentIsActive, this, 'parentIsActive');
    this.__parentFrontColor = new SynchedPropertyObjectTwoWayPU(p8.parentFrontColor, this, 'parentFrontColor');
    this.rowSpace = DEFAULT_ROW_SPACE;
    this.setInitiallyProvidedValue(p8);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(n8) {
    if (n8.arrow !== undefined) {
      this.arrow = n8.arrow;
    }
    if (n8.icon !== undefined) {
      this.icon = n8.icon;
    }
    if (n8.subIcon !== undefined) {
      this.subIcon = n8.subIcon;
    }
    if (n8.button !== undefined) {
      this.button = n8.button;
    }
    if (n8.switch !== undefined) {
      this.switch = n8.switch;
    }
    if (n8.checkBox !== undefined) {
      this.checkBox = n8.checkBox;
    }
    if (n8.radio !== undefined) {
      this.radio = n8.radio;
    }
    if (n8.image !== undefined) {
      this.image = n8.image;
    }
    if (n8.text !== undefined) {
      this.text = n8.text;
    }
    if (n8.switchState !== undefined) {
      this.switchState = n8.switchState;
    }
    if (n8.radioState !== undefined) {
      this.radioState = n8.radioState;
    }
    if (n8.checkBoxState !== undefined) {
      this.checkBoxState = n8.checkBoxState;
    }
    if (n8.rightWidth !== undefined) {
      this.rightWidth = n8.rightWidth;
    }
    if (n8.secondaryTextColor !== undefined) {
      this.secondaryTextColor = n8.secondaryTextColor;
    }
    if (n8.hoveringColor !== undefined) {
      this.hoveringColor = n8.hoveringColor;
    }
    if (n8.activedColor !== undefined) {
      this.activedColor = n8.activedColor;
    }
    if (n8.rowSpace !== undefined) {
      this.rowSpace = n8.rowSpace;
    }
  }
  updateStateVars(m8) {
  }
  purgeVariableDependenciesOnElmtId(l8) {
    this.__switchState.purgeDependencyOnElmtId(l8);
    this.__radioState.purgeDependencyOnElmtId(l8);
    this.__checkBoxState.purgeDependencyOnElmtId(l8);
    this.__rightWidth.purgeDependencyOnElmtId(l8);
    this.__secondaryTextColor.purgeDependencyOnElmtId(l8);
    this.__hoveringColor.purgeDependencyOnElmtId(l8);
    this.__activedColor.purgeDependencyOnElmtId(l8);
    this.__parentCanFocus.purgeDependencyOnElmtId(l8);
    this.__parentCanTouch.purgeDependencyOnElmtId(l8);
    this.__parentIsHover.purgeDependencyOnElmtId(l8);
    this.__parentCanHover.purgeDependencyOnElmtId(l8);
    this.__parentIsActive.purgeDependencyOnElmtId(l8);
    this.__parentFrontColor.purgeDependencyOnElmtId(l8);
  }
  aboutToBeDeleted() {
    this.__switchState.aboutToBeDeleted();
    this.__radioState.aboutToBeDeleted();
    this.__checkBoxState.aboutToBeDeleted();
    this.__rightWidth.aboutToBeDeleted();
    this.__secondaryTextColor.aboutToBeDeleted();
    this.__hoveringColor.aboutToBeDeleted();
    this.__activedColor.aboutToBeDeleted();
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
  set switchState(k8) {
    this.__switchState.set(k8);
  }
  get radioState() {
    return this.__radioState.get();
  }
  set radioState(j8) {
    this.__radioState.set(j8);
  }
  get checkBoxState() {
    return this.__checkBoxState.get();
  }
  set checkBoxState(i8) {
    this.__checkBoxState.set(i8);
  }
  get rightWidth() {
    return this.__rightWidth.get();
  }
  set rightWidth(h8) {
    this.__rightWidth.set(h8);
  }
  get secondaryTextColor() {
    return this.__secondaryTextColor.get();
  }
  set secondaryTextColor(g8) {
    this.__secondaryTextColor.set(g8);
  }
  get hoveringColor() {
    return this.__hoveringColor.get();
  }
  set hoveringColor(f8) {
    this.__hoveringColor.set(f8);
  }
  get activedColor() {
    return this.__activedColor.get();
  }
  set activedColor(e8) {
    this.__activedColor.set(e8);
  }
  get parentCanFocus() {
    return this.__parentCanFocus.get();
  }
  set parentCanFocus(d8) {
    this.__parentCanFocus.set(d8);
  }
  get parentCanTouch() {
    return this.__parentCanTouch.get();
  }
  set parentCanTouch(c8) {
    this.__parentCanTouch.set(c8);
  }
  get parentIsHover() {
    return this.__parentIsHover.get();
  }
  set parentIsHover(b8) {
    this.__parentIsHover.set(b8);
  }
  get parentCanHover() {
    return this.__parentCanHover.get();
  }
  set parentCanHover(a8) {
    this.__parentCanHover.set(a8);
  }
  get parentIsActive() {
    return this.__parentIsActive.get();
  }
  set parentIsActive(z7) {
    this.__parentIsActive.set(z7);
  }
  get parentFrontColor() {
    return this.__parentFrontColor.get();
  }
  set parentFrontColor(y7) {
    this.__parentFrontColor.set(y7);
  }
  onWillApplyTheme(x7) {
    this.secondaryTextColor = x7.colors.fontSecondary;
    this.hoveringColor = x7.colors.interactiveHover;
    this.activedColor = x7.colors.interactiveActive;
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
  createButton(h7, i7 = null) {
    this.observeComponentCreation2((q7, r7) => {
      Button.createWithChild();
      Button.margin({ right: LISTITEM_PADDING });
      Button.hitTestBehavior(HitTestMode.Block);
      Button.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_button3'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Button.fontColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary_activated_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Button.height(BUTTON_SIZE);
      Button.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_button_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Button.key('composeListItem_OperateItemButton');
      Button.labelStyle({
        maxLines: TEXT_MAX_LINE
      });
      Button.onFocus(() => {
        this.parentCanFocus = false;
      });
      Button.onTouch((w7) => {
        if (w7.type === TouchType.Down) {
          this.parentCanTouch = false;
        }
        if (w7.type === TouchType.Up) {
          this.parentCanTouch = true;
        }
      });
      Button.onHover((v7) => {
        this.parentCanHover = false;
        if (v7 && this.parentFrontColor === this.hoveringColor) {
          this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
        }
        if (!v7) {
          this.parentCanHover = true;
          if (this.parentIsHover) {
            this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
              (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
          }
        }
      });
    }, Button);
    this.observeComponentCreation2((o7, p7) => {
      Row.create();
      Row.padding({
        left: TEXT_SAFE_MARGIN,
        right: TEXT_SAFE_MARGIN
      });
    }, Row);
    this.observeComponentCreation2((m7, n7) => {
      Text.create(h7);
      Text.focusable(true);
    }, Text);
    Text.pop();
    Row.pop();
    Button.pop();
  }
  createIcon(u6, v6 = null) {
    this.observeComponentCreation2((a7, b7) => {
      Button.createWithChild({ type: ButtonType.Normal });
      Button.hitTestBehavior(HitTestMode.Block);
      Button.backgroundColor(Color.Transparent);
      Button.height(OPERATEITEM_ICON_CLICKABLE_SIZE);
      Button.width(OPERATEITEM_ICON_CLICKABLE_SIZE);
      Button.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Button.key('composeListItem_OperateItemIcon');
      Button.onFocus(() => {
        this.parentCanFocus = false;
      });
      Button.onTouch((g7) => {
        if (g7.type === TouchType.Down) {
          this.parentCanTouch = false;
        }
        if (g7.type === TouchType.Up) {
          this.parentCanTouch = true;
        }
      });
      Button.onHover((f7) => {
        this.parentCanHover = false;
        if (f7 && this.parentFrontColor === this.hoveringColor) {
          this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
        }
        if (!f7) {
          this.parentCanHover = true;
          if (this.parentIsHover) {
            this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
              (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
          }
        }
      });
      Button.onClick((u6.action));
    }, Button);
    this.observeComponentCreation2((y6, z6) => {
      Image.create(u6.value);
      Image.height(OPERATEITEM_ICONLIKE_SIZE);
      Image.width(OPERATEITEM_ICONLIKE_SIZE);
      Image.focusable(true);
      Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Image.draggable(false);
    }, Image);
    Button.pop();
  }
  createImage(p6, q6 = null) {
    this.observeComponentCreation2((s6, t6) => {
      Image.create(p6);
      Image.height(OPERATEITEM_IMAGE_SIZE);
      Image.width(OPERATEITEM_IMAGE_SIZE);
      Image.draggable(false);
      Image.margin({ right: LISTITEM_PADDING });
    }, Image);
  }
  createText(k6, l6 = null) {
    this.observeComponentCreation2((n6, o6) => {
      Text.create(k6);
      Text.margin({ right: LISTITEM_PADDING });
      Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Text.fontColor(ObservedObject.GetRawObject(this.secondaryTextColor));
      Text.focusable(true);
      Text.draggable(false);
      Text.flexShrink(1);
      Text.key('composeListItem_OperateItemSecondaryText');
    }, Text);
    Text.pop();
  }
  createArrow(x5, y5 = null) {
    this.observeComponentCreation2((d6, e6) => {
      Button.createWithChild({ type: ButtonType.Normal });
      Button.margin({ right: LISTITEM_PADDING });
      Button.hitTestBehavior(HitTestMode.Block);
      Button.backgroundColor(Color.Transparent);
      Button.height(OPERATEITEM_ICONLIKE_SIZE);
      Button.width(OPERATEITEM_ARROW_WIDTH);
      Button.key('composeListItem_OperateItemArrow');
      Button.onFocus(() => {
        this.parentCanFocus = false;
      });
      Button.onTouch((j6) => {
        if (j6.type === TouchType.Down) {
          this.parentCanTouch = false;
        }
        if (j6.type === TouchType.Up) {
          this.parentCanTouch = true;
        }
      });
      Button.onHover((i6) => {
        this.parentCanHover = false;
        if (i6 && this.parentFrontColor === this.hoveringColor) {
          this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
        }
        if (!i6) {
          this.parentCanHover = true;
          if (this.parentIsHover) {
            this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
              (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
          }
        }
      });
      Button.onClick(x5.action);
    }, Button);
    this.observeComponentCreation2((b6, c6) => {
      Image.create(x5.value);
      Image.height(OPERATEITEM_ICONLIKE_SIZE);
      Image.width(OPERATEITEM_ARROW_WIDTH);
      Image.focusable(true);
      Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_fourth'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Image.draggable(false);
    }, Image);
    Button.pop();
  }
  createRadio(n5, o5 = null) {
    this.observeComponentCreation2((q5, r5) => {
      Radio.create({ value: '', group: '' });
      Radio.margin({ right: LISTITEM_PADDING });
      Radio.checked(this.radioState);
      Radio.onChange(n5.onChange);
      Radio.height(OPERATEITEM_ICONLIKE_SIZE);
      Radio.width(OPERATEITEM_ICONLIKE_SIZE);
      Radio.key('composeListItem_OperateItemRadio');
      Radio.onFocus(() => {
        this.parentCanFocus = false;
      });
      Radio.hitTestBehavior(HitTestMode.Block);
      Radio.onTouch((w5) => {
        if (w5.type === TouchType.Down) {
          this.parentCanTouch = false;
        }
        if (w5.type === TouchType.Up) {
          this.parentCanTouch = true;
        }
      });
      Radio.onHover((v5) => {
        this.parentCanHover = false;
        if (v5 && this.parentFrontColor === this.hoveringColor) {
          this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
        }
        if (!v5) {
          this.parentCanHover = true;
          if (this.parentIsHover) {
            this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
              (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
          }
        }
      });
    }, Radio);
  }
  createCheckBox(d5, e5 = null) {
    this.observeComponentCreation2((g5, h5) => {
      Checkbox.create();
      Checkbox.margin({ right: LISTITEM_PADDING });
      Checkbox.select(this.checkBoxState);
      Checkbox.onChange(d5.onChange);
      Checkbox.height(OPERATEITEM_ICONLIKE_SIZE);
      Checkbox.height(OPERATEITEM_ICONLIKE_SIZE);
      Checkbox.key('composeListItem_OperateItemCheckbox');
      Checkbox.onFocus(() => {
        this.parentCanFocus = false;
      });
      Checkbox.hitTestBehavior(HitTestMode.Block);
      Checkbox.onTouch((m5) => {
        if (m5.type === TouchType.Down) {
          this.parentCanTouch = false;
        }
        if (m5.type === TouchType.Up) {
          this.parentCanTouch = true;
        }
      });
      Checkbox.onHover((l5) => {
        this.parentCanHover = false;
        if (l5 && this.parentFrontColor === this.hoveringColor) {
          this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
        }
        if (!l5) {
          this.parentCanHover = true;
          if (this.parentIsHover) {
            this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
              (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
          }
        }
      });
    }, Checkbox);
    Checkbox.pop();
  }
  createSwitch(p4, q4 = null) {
    this.observeComponentCreation2((w4, x4) => {
      Row.create();
      Row.margin({ right: SWITCH_PADDING });
      Row.height(OPERATEITEM_ICON_CLICKABLE_SIZE);
      Row.width(OPERATEITEM_ICON_CLICKABLE_SIZE);
      Row.key('composeListItem_OperateItemSwitch');
      Row.justifyContent(FlexAlign.Center);
      Row.onFocus(() => {
        this.parentCanFocus = false;
      });
      Row.onTouch((c5) => {
        if (c5.type === TouchType.Down) {
          this.parentCanTouch = false;
        }
        if (c5.type === TouchType.Up) {
          this.parentCanTouch = true;
        }
      });
      Row.onHover((b5) => {
        this.parentCanHover = false;
        if (b5 && this.parentFrontColor === this.hoveringColor) {
          this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
        }
        if (!b5) {
          this.parentCanHover = true;
          if (this.parentIsHover) {
            this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
              (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
          }
        }
      });
    }, Row);
    this.observeComponentCreation2((t4, u4) => {
      Toggle.create({ type: ToggleType.Switch, isOn: this.switchState });
      Toggle.onChange(p4.onChange);
      Toggle.onClick(() => {
        this.switchState = !this.switchState;
      });
      Toggle.hitTestBehavior(HitTestMode.Block);
    }, Toggle);
    Toggle.pop();
    Row.pop();
  }
  createTextArrow(v3, w3, x3 = null) {
    this.observeComponentCreation2((i4, j4) => {
      Button.createWithChild({ type: ButtonType.Normal });
      Button.hitTestBehavior(HitTestMode.Block);
      Button.labelStyle({
        maxLines: TEXT_MAX_LINE
      });
      Button.backgroundColor(Color.Transparent);
      Button.height(TEXT_ARROW_HEIGHT);
      Button.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Button.key('composeListItem_OperateItemTextArrow');
      Button.onFocus(() => {
        this.parentCanFocus = false;
      });
      Button.onTouch((o4) => {
        if (o4.type === TouchType.Down) {
          this.parentCanTouch = false;
        }
        if (o4.type === TouchType.Up) {
          this.parentCanTouch = true;
        }
      });
      Button.onHover((n4) => {
        this.parentCanHover = false;
        if (n4 && this.parentFrontColor === this.hoveringColor) {
          this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
        }
        if (!n4) {
          this.parentCanHover = true;
          if (this.parentIsHover) {
            this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
              (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
          }
        }
      });
      Button.onClick(w3.action);
    }, Button);
    this.observeComponentCreation2((g4, h4) => {
      Row.create({ space: SPECICAL_ROW_SPACE });
      Row.padding({
        left: TEXT_SAFE_MARGIN,
        right: LISTITEM_PADDING
      });
    }, Row);
    this.observeComponentCreation2((e4, f4) => {
      Text.create(v3);
      Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Text.focusable(true);
      Text.draggable(false);
      Text.constraintSize({
        maxWidth: `calc(100% - ${OPERATEITEM_ARROW_WIDTH}vp)`
      });
    }, Text);
    Text.pop();
    this.observeComponentCreation2((c4, d4) => {
      Image.create(w3.value);
      Image.height(OPERATEITEM_ICONLIKE_SIZE);
      Image.width(OPERATEITEM_ARROW_WIDTH);
      Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_fourth'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Image.focusable(true);
      Image.draggable(false);
    }, Image);
    Row.pop();
    Button.pop();
  }
  initialRender() {
    this.observeComponentCreation2((t3, u3) => {
      Row.create({
        space: this.rowSpace
      });
      Row.width(this.rightWidth);
      Row.flexShrink(1);
      Row.justifyContent(FlexAlign.End);
    }, Row);
    this.observeComponentCreation2((b3, c3) => {
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
          this.observeComponentCreation2((g3, h3) => {
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
          }, If);
          If.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(10, () => {
        });
      }
    }, If);
    If.pop();
    Row.pop();
  }
  rerender() {
    this.updateDirtyElements();
  }
}
export class ComposeListItem extends ViewPU {
  constructor(t2, u2, v2, w2 = -1, x2 = undefined, y2) {
    super(t2, v2, w2, y2);
    if (typeof x2 === 'function') {
      this.paramsGenerator_ = x2;
    }
    this.__contentItem = new SynchedPropertyObjectOneWayPU(u2.contentItem, this, 'contentItem');
    this.__operateItem = new SynchedPropertyObjectOneWayPU(u2.operateItem, this, 'operateItem');
    this.__frontColor = new ObservedPropertyObjectPU(Color.Transparent.toString(), this, 'frontColor');
    this.__borderSize = new ObservedPropertySimplePU(0, this, "borderSize");
    this.__canFocus = new ObservedPropertySimplePU(false, this, "canFocus");
    this.__canTouch = new ObservedPropertySimplePU(true, this, "canTouch");
    this.__canHover = new ObservedPropertySimplePU(true, this, "canHover");
    this.__isHover = new ObservedPropertySimplePU(true, this, "isHover");
    this.__itemHeight = new ObservedPropertySimplePU(ItemHeight.FIRST_HEIGHT, this, "itemHeight");
    this.__isActive = new ObservedPropertySimplePU(false, this, "isActive");
    this.__hoveringColor = new ObservedPropertyObjectPU('#0d000000', this, 'hoveringColor');
    this.__touchDownColor = new ObservedPropertyObjectPU('#1a000000', this, 'touchDownColor');
    this.__activedColor = new ObservedPropertyObjectPU('#1a0a59f7', this, 'activedColor');
    this.__focusOutlineColor = new ObservedPropertyObjectPU({
      'id': -1,
      'type': 10001,
      params: ['sys.color.ohos_id_color_focused_outline'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__',
    }, this, 'focusOutlineColor');
    this.setInitiallyProvidedValue(u2);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(s2) {
    if (s2.contentItem === undefined) {
      this.__contentItem.set(null);
    }
    if (s2.operateItem === undefined) {
      this.__operateItem.set(null);
    }
    if (s2.frontColor !== undefined) {
      this.frontColor = s2.frontColor;
    }
    if (s2.borderSize !== undefined) {
      this.borderSize = s2.borderSize;
    }
    if (s2.canFocus !== undefined) {
      this.canFocus = s2.canFocus;
    }
    if (s2.canTouch !== undefined) {
      this.canTouch = s2.canTouch;
    }
    if (s2.canHover !== undefined) {
      this.canHover = s2.canHover;
    }
    if (s2.isHover !== undefined) {
      this.isHover = s2.isHover;
    }
    if (s2.itemHeight !== undefined) {
      this.itemHeight = s2.itemHeight;
    }
    if (s2.isActive !== undefined) {
      this.isActive = s2.isActive;
    }
    if (s2.hoveringColor !== undefined) {
      this.hoveringColor = s2.hoveringColor;
    }
    if (s2.touchDownColor !== undefined) {
      this.touchDownColor = s2.touchDownColor;
    }
    if (s2.activedColor !== undefined) {
      this.activedColor = s2.activedColor;
    }
    if (s2.focusOutlineColor !== undefined) {
      this.focusOutlineColor = s2.focusOutlineColor;
    }
  }
  updateStateVars(r2) {
    this.__contentItem.reset(r2.contentItem);
    this.__operateItem.reset(r2.operateItem);
  }
  purgeVariableDependenciesOnElmtId(q2) {
    this.__contentItem.purgeDependencyOnElmtId(q2);
    this.__operateItem.purgeDependencyOnElmtId(q2);
    this.__frontColor.purgeDependencyOnElmtId(q2);
    this.__borderSize.purgeDependencyOnElmtId(q2);
    this.__canFocus.purgeDependencyOnElmtId(q2);
    this.__canTouch.purgeDependencyOnElmtId(q2);
    this.__canHover.purgeDependencyOnElmtId(q2);
    this.__isHover.purgeDependencyOnElmtId(q2);
    this.__itemHeight.purgeDependencyOnElmtId(q2);
    this.__isActive.purgeDependencyOnElmtId(q2);
    this.__hoveringColor.purgeDependencyOnElmtId(q2);
    this.__touchDownColor.purgeDependencyOnElmtId(q2);
    this.__activedColor.purgeDependencyOnElmtId(q2);
    this.__focusOutlineColor.purgeDependencyOnElmtId(q2);
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
    this.__hoveringColor.aboutToBeDeleted();
    this.__touchDownColor.aboutToBeDeleted();
    this.__activedColor.aboutToBeDeleted();
    this.__focusOutlineColor.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get contentItem() {
    return this.__contentItem.get();
  }
  set contentItem(p2) {
    this.__contentItem.set(p2);
  }
  get operateItem() {
    return this.__operateItem.get();
  }
  set operateItem(o2) {
    this.__operateItem.set(o2);
  }
  get frontColor() {
    return this.__frontColor.get();
  }
  set frontColor(n2) {
    this.__frontColor.set(n2);
  }
  get borderSize() {
    return this.__borderSize.get();
  }
  set borderSize(m2) {
    this.__borderSize.set(m2);
  }
  get canFocus() {
    return this.__canFocus.get();
  }
  set canFocus(l2) {
    this.__canFocus.set(l2);
  }
  get canTouch() {
    return this.__canTouch.get();
  }
  set canTouch(k2) {
    this.__canTouch.set(k2);
  }
  get canHover() {
    return this.__canHover.get();
  }
  set canHover(j2) {
    this.__canHover.set(j2);
  }
  get isHover() {
    return this.__isHover.get();
  }
  set isHover(i2) {
    this.__isHover.set(i2);
  }
  get itemHeight() {
    return this.__itemHeight.get();
  }
  set itemHeight(h2) {
    this.__itemHeight.set(h2);
  }
  get isActive() {
    return this.__isActive.get();
  }
  set isActive(g2) {
    this.__isActive.set(g2);
  }
  get hoveringColor() {
    return this.__hoveringColor.get();
  }
  set hoveringColor(f2) {
    this.__hoveringColor.set(f2);
  }
  get touchDownColor() {
    return this.__touchDownColor.get();
  }
  set touchDownColor(e2) {
    this.__touchDownColor.set(e2);
  }
  get activedColor() {
    return this.__activedColor.get();
  }
  set activedColor(d2) {
    this.__activedColor.set(d2);
  }
  get focusOutlineColor() {
    return this.__focusOutlineColor.get();
  }
  set focusOutlineColor(c2) {
    this.__focusOutlineColor.set(c2);
  }
  onWillApplyTheme(b2) {
    this.hoveringColor = b2.colors.interactiveHover;
    this.touchDownColor = b2.colors.interactivePressed;
    this.activedColor = b2.colors.interactiveActive;
    this.focusOutlineColor = b2.colors.interactiveFocus;
  }
  aboutToAppear() {
    if (this.contentItem === undefined) {
      if (this.operateItem?.image !== undefined || this.operateItem?.icon !== undefined ||
        this.operateItem?.subIcon !== undefined) {
        this.itemHeight = OPERATEITEM_IMAGE_SIZE + SAFE_LIST_PADDING;
      }
      return;
    }
    if (this.contentItem?.secondaryText === undefined && this.contentItem?.description === undefined) {
      if (this.contentItem?.icon === undefined) {
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
    if (ICON_SIZE_MAP.get(this.contentItem?.iconStyle) >= this.itemHeight) {
      this.itemHeight = ICON_SIZE_MAP.get(this.contentItem?.iconStyle) + SAFE_LIST_PADDING;
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
    this.observeComponentCreation2((z1, a2) => {
      Stack.create();
      Stack.padding({
        left: STACK_PADDING,
        right: STACK_PADDING
      });
    }, Stack);
    this.observeComponentCreation2((r1, s1) => {
      Flex.create({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center });
      Flex.height(this.itemHeight);
      Flex.focusable(true);
      Flex.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Flex.backgroundColor(ObservedObject.GetRawObject(this.frontColor));
      Flex.key('composeListItem');
      Flex.onFocus(() => {
        this.canFocus = true;
      });
      Flex.onBlur(() => {
        this.canFocus = false;
      });
      Flex.onHover((y1) => {
        this.isHover = y1;
        if (this.canHover) {
          this.frontColor = y1 ? this.hoveringColor :
            (this.isActive ? this.activedColor : Color.Transparent.toString());
        }
      });
      Flex.onTouch((x1) => {
        if (x1.type === TouchType.Down && this.canTouch) {
          this.frontColor = this.touchDownColor;
        }
        if (x1.type === TouchType.Up) {
          this.frontColor = this.isActive ? this.activedColor : Color.Transparent.toString();
        }
      });
      ViewStackProcessor.visualState("focused");
      Flex.border({
        radius: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        width: ITEM_BORDER_SHOWN,
        color: this.focusOutlineColor,
        style: BorderStyle.Solid
      });
      ViewStackProcessor.visualState("normal");
      Flex.border({
        radius: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        width: ITEM_BORDER_SHOWN,
        color: Color.Transparent
      });
      ViewStackProcessor.visualState();
    }, Flex);
    this.observeComponentCreation2((g1, h1) => {
      If.create();
      if (this.contentItem === null) {
        this.ifElseBranchUpdateFunction(0, () => {
          {
            this.observeComponentCreation2((l1, m1) => {
              if (m1) {
                let n1 = new ContentItemStruct(this, {}, undefined, l1, () => { },
                  { page: 'library/src/main/ets/components/mainpage/composelistitem.ets', line: 713, col: 11 });
                ViewPU.create(n1);
                let o1 = () => {
                  return {};
                };
                n1.paramsGenerator_ = o1;
              }
              else {
                this.updateStateVarsOfChildByElmtId(l1, {});
              }
            }, { name: 'ContentItemStruct' });
          }
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
    }, If);
    If.pop();
    this.observeComponentCreation2((v, w) => {
      If.create();
      if (this.contentItem !== null) {
        this.ifElseBranchUpdateFunction(0, () => {
          {
            this.observeComponentCreation2((a1, b1) => {
              if (b1) {
                let c1 = new ContentItemStruct(this, {
                  icon: this.contentItem.icon,
                  iconStyle: this.contentItem.iconStyle,
                  primaryText: this.contentItem.primaryText,
                  secondaryText: this.contentItem.secondaryText,
                  description: this.contentItem.description,
                  leftWidth: this.calculatedLeftWidth()
                }, undefined, a1, () => { }, { page: 'library/src/main/ets/components/mainpage/composelistitem.ets',
                  line: 716, col: 11 });
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
            }, { name: 'ContentItemStruct' });
          }
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
    }, If);
    If.pop();
    this.observeComponentCreation2((f, g) => {
      If.create();
      if (this.operateItem !== null) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((r, s) => {
            __Common__.create();
            __Common__.onFocus(() => {
              this.canFocus = false;
            });
            __Common__.onBlur(() => {
              this.canFocus = true;
            });
          }, __Common__);
          {
            this.observeComponentCreation2((l, m) => {
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
                }, undefined, l, () => { }, { page: 'library/src/main/ets/components/mainpage/composelistitem.ets',
                  line: 726, col: 11 });
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
            }, { name: 'OperateItemStruct' });
          }
          __Common__.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
    }, If);
    If.pop();
    Flex.pop();
    Stack.pop();
  }
  rerender() {
    this.updateDirtyElements();
  }
}

export default { IconType, ComposeListItem };