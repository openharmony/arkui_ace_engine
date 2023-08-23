/*
 * Copyright (c) 2023-2023 Huawei Device Co., Ltd.
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

export var IconType;
!function(e){
  e[e.BADGE=1] = "BADGE";
  e[e.NORMAL_ICON=2] = "NORMAL_ICON";
  e[e.SYSTEM_ICON=3] = "SYSTEM_ICON";
  e[e.HEAD_SCULPTURE=4] = "HEAD_SCULPTURE";
  e[e.APP_ICON=5] = "APP_ICON";
  e[e.PREVIEW=6] = "PREVIEW";
  e[e.LONGITUDINAL=7] = "LONGITUDINAL";
  e[e.VERTICAL=8] = "VERTICAL"
}(IconType || (IconType = {}));
var ItemHeight;
!function(e){
  e[e.FIRST_HEIGHT=48] = "FIRST_HEIGHT";
  e[e.SECOND_HEIGHT=56] = "SECOND_HEIGHT";
  e[e.THIRD_HEIGHT=64] = "THIRD_HEIGHT";
  e[e.FOURTH_HEIGHT=72] = "FOURTH_HEIGHT";
  e[e.FIFTH_HEIGHT=96] = "FIFTH_HEIGHT"
}(ItemHeight || (ItemHeight = {}));
const TEXT_MAX_LINE = 1;
const ITEM_BORDER_SHOWN = 2;
const TEXT_COLUMN_SPACE = 4;
const TEXT_SAFE_MARGIN = 8;
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
const OPERATEITEM_ICON_CLICKABLE_SIZE = 48;
const OPERATEITEM_IMAGE_SIZE = 48;
const HOVERING_COLOR = "#0d000000";
const TOUCH_DOWN_COLOR = "#1a000000";
const ACTIVED_COLOR = "#1a0a59f7";
const ICON_SIZE_MAP = new Map([[IconType.BADGE, 8], [IconType.NORMAL_ICON, 16], [IconType.SYSTEM_ICON, 24], [IconType.HEAD_SCULPTURE, 40], [IconType.APP_ICON, 64], [IconType.PREVIEW, 96], [IconType.LONGITUDINAL, 96], [IconType.VERTICAL, 96]]);

class ContentItemStruct extends ViewPU {
  constructor(e, t, o, r = -1) {
    super(e, o, r);
    this.iconStyle = null;
    this.icon = null;
    this.primaryText = null;
    this.secondaryText = null;
    this.description = null;
    this.itemRowSpace = 16;
    this.setInitiallyProvidedValue(t)
  }

  setInitiallyProvidedValue(e) {
    void 0 !== e.iconStyle && (this.iconStyle = e.iconStyle);
    void 0 !== e.icon && (this.icon = e.icon);
    void 0 !== e.primaryText && (this.primaryText = e.primaryText);
    void 0 !== e.secondaryText && (this.secondaryText = e.secondaryText);
    void 0 !== e.description && (this.description = e.description);
    void 0 !== e.itemRowSpace && (this.itemRowSpace = e.itemRowSpace)
  }

  updateStateVars(e) {
  }

  purgeVariableDependenciesOnElmtId(e) {
  }

  aboutToBeDeleted() {
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal()
  }

  aboutToAppear() {
    null == this.icon && null == this.iconStyle && (this.itemRowSpace = 0)
  }

  createIcon(e = null) {
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      null != this.icon && null != this.iconStyle ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          If.create();
          this.iconStyle <= IconType.PREVIEW ? this.ifElseBranchUpdateFunction(0, (() => {
            this.observeComponentCreation(((e, t) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              Image.create(this.icon);
              Image.objectFit(ImageFit.Contain);
              Image.width(ICON_SIZE_MAP.get(this.iconStyle));
              Image.height(ICON_SIZE_MAP.get(this.iconStyle));
              Image.borderRadius({
                id: -1,
                type: 10002,
                params: ["sys.float.ohos_id_corner_radius_default_m"],
                bundleName: "",
                moduleName: ""
              });
              Image.backgroundColor(Color.Blue);
              Image.focusable(!0);
              Image.draggable(!1);
              t || Image.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }))
          })) : this.ifElseBranchUpdateFunction(1, (() => {
            this.observeComponentCreation(((e, t) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              Image.create(this.icon);
              Image.objectFit(ImageFit.Contain);
              Image.constraintSize({
                minWidth: 0,
                maxWidth: ICON_SIZE_MAP.get(this.iconStyle),
                minHeight: 0,
                maxHeight: ICON_SIZE_MAP.get(this.iconStyle)
              });
              Image.borderRadius({
                id: -1,
                type: 10002,
                params: ["sys.float.ohos_id_corner_radius_default_m"],
                bundleName: "",
                moduleName: ""
              });
              Image.backgroundColor(Color.Blue);
              Image.focusable(!0);
              Image.draggable(!1);
              t || Image.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }))
          }));
          t || If.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        If.pop()
      })) : If.branchId(1);
      t || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop()
  }

  createText(e = null) {
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Column.create({ space: 4 });
      Column.margin({ top: 8, bottom: 8 });
      Column.alignItems(HorizontalAlign.Start);
      t || Column.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Text.create(this.primaryText);
      Text.fontSize({
        id: -1,
        type: 10002,
        params: ["sys.float.ohos_id_text_size_body1"],
        bundleName: "",
        moduleName: ""
      });
      Text.fontColor({
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_text_primary"],
        bundleName: "",
        moduleName: ""
      });
      Text.maxLines(1);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.fontWeight(FontWeight.Medium);
      Text.focusable(!0);
      Text.draggable(!1);
      t || Text.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    Text.pop();
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      null != this.secondaryText ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Text.create(this.secondaryText);
          Text.fontSize({
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_text_size_body2"],
            bundleName: "",
            moduleName: ""
          });
          Text.fontColor({
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_text_secondary"],
            bundleName: "",
            moduleName: ""
          });
          Text.maxLines(1);
          Text.textOverflow({ overflow: TextOverflow.Ellipsis });
          Text.focusable(!0);
          Text.draggable(!1);
          t || Text.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        Text.pop()
      })) : If.branchId(1);
      t || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop();
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      null != this.description ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Text.create(this.description);
          Text.fontSize({
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_text_size_body2"],
            bundleName: "",
            moduleName: ""
          });
          Text.fontColor({
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_text_secondary"],
            bundleName: "",
            moduleName: ""
          });
          Text.maxLines(1);
          Text.textOverflow({ overflow: TextOverflow.Ellipsis });
          Text.focusable(!0);
          Text.draggable(!1);
          t || Text.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        Text.pop()
      })) : If.branchId(1);
      t || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop();
    Column.pop()
  }

  initialRender() {
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Row.create({ space: this.itemRowSpace });
      t || Row.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.createIcon.bind(this)();
    this.createText.bind(this)();
    Row.pop()
  }

  rerender() {
    this.updateDirtyElements()
  }
}

class OperateItemStruct extends ViewPU {
  constructor(e, t, o, r = -1) {
    super(e, o, r);
    this.arrow = null;
    this.icon = null;
    this.subIcon = null;
    this.button = null;
    this.switch = null;
    this.checkBox = null;
    this.radio = null;
    this.image = null;
    this.text = null;
    this.__switchState = new ObservedPropertySimplePU(!1, this, "switchState");
    this.__radioState = new ObservedPropertySimplePU(!1, this, "radioState");
    this.__checkBoxState = new ObservedPropertySimplePU(!1, this, "checkBoxState");
    this.__parentCanFocus = new SynchedPropertySimpleTwoWayPU(t.parentCanFocus, this, "parentCanFocus");
    this.__parentCanTouch = new SynchedPropertySimpleTwoWayPU(t.parentCanTouch, this, "parentCanTouch");
    this.__parentIsHover = new SynchedPropertySimpleTwoWayPU(t.parentIsHover, this, "parentIsHover");
    this.__parentCanHover = new SynchedPropertySimpleTwoWayPU(t.parentCanHover, this, "parentCanHover");
    this.__parentIsActive = new SynchedPropertySimpleTwoWayPU(t.parentIsActive, this, "parentIsActive");
    this.__parentFrontColor = new SynchedPropertySimpleTwoWayPU(t.parentFrontColor, this, "parentFrontColor");
    this.rowSpace = 0;
    this.setInitiallyProvidedValue(t)
  }

  setInitiallyProvidedValue(e) {
    void 0 !== e.arrow && (this.arrow = e.arrow);
    void 0 !== e.icon && (this.icon = e.icon);
    void 0 !== e.subIcon && (this.subIcon = e.subIcon);
    void 0 !== e.button && (this.button = e.button);
    void 0 !== e.switch && (this.switch = e.switch);
    void 0 !== e.checkBox && (this.checkBox = e.checkBox);
    void 0 !== e.radio && (this.radio = e.radio);
    void 0 !== e.image && (this.image = e.image);
    void 0 !== e.text && (this.text = e.text);
    void 0 !== e.switchState && (this.switchState = e.switchState);
    void 0 !== e.radioState && (this.radioState = e.radioState);
    void 0 !== e.checkBoxState && (this.checkBoxState = e.checkBoxState);
    void 0 !== e.rowSpace && (this.rowSpace = e.rowSpace)
  }

  updateStateVars(e) {
  }

  purgeVariableDependenciesOnElmtId(e) {
    this.__switchState.purgeDependencyOnElmtId(e);
    this.__radioState.purgeDependencyOnElmtId(e);
    this.__checkBoxState.purgeDependencyOnElmtId(e);
    this.__parentCanFocus.purgeDependencyOnElmtId(e);
    this.__parentCanTouch.purgeDependencyOnElmtId(e);
    this.__parentIsHover.purgeDependencyOnElmtId(e);
    this.__parentCanHover.purgeDependencyOnElmtId(e);
    this.__parentIsActive.purgeDependencyOnElmtId(e);
    this.__parentFrontColor.purgeDependencyOnElmtId(e)
  }

  aboutToBeDeleted() {
    this.__switchState.aboutToBeDeleted();
    this.__radioState.aboutToBeDeleted();
    this.__checkBoxState.aboutToBeDeleted();
    this.__parentCanFocus.aboutToBeDeleted();
    this.__parentCanTouch.aboutToBeDeleted();
    this.__parentIsHover.aboutToBeDeleted();
    this.__parentCanHover.aboutToBeDeleted();
    this.__parentIsActive.aboutToBeDeleted();
    this.__parentFrontColor.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal()
  }

  get switchState() {
    return this.__switchState.get()
  }

  set switchState(e) {
    this.__switchState.set(e)
  }

  get radioState() {
    return this.__radioState.get()
  }

  set radioState(e) {
    this.__radioState.set(e)
  }

  get checkBoxState() {
    return this.__checkBoxState.get()
  }

  set checkBoxState(e) {
    this.__checkBoxState.set(e)
  }

  get parentCanFocus() {
    return this.__parentCanFocus.get()
  }

  set parentCanFocus(e) {
    this.__parentCanFocus.set(e)
  }

  get parentCanTouch() {
    return this.__parentCanTouch.get()
  }

  set parentCanTouch(e) {
    this.__parentCanTouch.set(e)
  }

  get parentIsHover() {
    return this.__parentIsHover.get()
  }

  set parentIsHover(e) {
    this.__parentIsHover.set(e)
  }

  get parentCanHover() {
    return this.__parentCanHover.get()
  }

  set parentCanHover(e) {
    this.__parentCanHover.set(e)
  }

  get parentIsActive() {
    return this.__parentIsActive.get()
  }

  set parentIsActive(e) {
    this.__parentIsActive.set(e)
  }

  get parentFrontColor() {
    return this.__parentFrontColor.get()
  }

  set parentFrontColor(e) {
    this.__parentFrontColor.set(e)
  }

  aboutToAppear() {
    null != this.switch && (this.switchState = this.switch.isCheck);
    null != this.radio && (this.radioState = this.radio.isCheck);
    null != this.checkBox && (this.checkBoxState = this.checkBox.isCheck);
    (null == this.button && null == this.image && null != this.icon && null != this.text || null == this.button && null == this.image && null == this.icon && null != this.arrow && null != this.text) && (this.rowSpace = 4)
  }

  createButton(e, t = null) {
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Button.createWithChild();
      Button.hitTestBehavior(HitTestMode.Block);
      Button.fontSize({
        id: -1,
        type: 10002,
        params: ["sys.float.ohos_id_text_size_button3"],
        bundleName: "",
        moduleName: ""
      });
      Button.fontColor({
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_text_primary_activated_transparent"],
        bundleName: "",
        moduleName: ""
      });
      Button.height(28);
      Button.backgroundColor({
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_button_normal"],
        bundleName: "",
        moduleName: ""
      });
      Button.labelStyle({ maxLines: 1 });
      Button.onFocus((() => {
        this.parentCanFocus = !1
      }));
      Button.onTouch((e => {
        e.type == TouchType.Down && (this.parentCanTouch = !1);
        e.type == TouchType.Up && (this.parentCanTouch = !0)
      }));
      Button.onHover((e => {
        this.parentCanHover = !1;
        e && "#0d000000" == this.parentFrontColor && (this.parentFrontColor = this.parentIsActive ? "#1a0a59f7" : Color.Transparent.toString());
        if (!e) {
          this.parentCanHover = !0;
          this.parentIsHover && (this.parentFrontColor = this.parentIsHover ? "#0d000000" : this.parentIsActive ? "#1a0a59f7" : Color.Transparent.toString())
        }
      }));
      t || Button.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Row.create();
      Row.padding({ left: 8, right: 8 });
      t || Row.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((t, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t);
      Text.create(e);
      Text.focusable(!0);
      o || Text.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    Text.pop();
    Row.pop();
    Button.pop()
  }

  createIcon(e, t = null) {
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Button.createWithChild({ type: ButtonType.Normal });
      Button.hitTestBehavior(HitTestMode.Block);
      Button.backgroundColor(Color.Transparent);
      Button.height(48);
      Button.width(48);
      Button.borderRadius({
        id: -1,
        type: 10002,
        params: ["sys.float.ohos_id_corner_radius_clicked"],
        bundleName: "",
        moduleName: ""
      });
      Button.onFocus((() => {
        this.parentCanFocus = !1
      }));
      Button.onTouch((e => {
        e.type == TouchType.Down && (this.parentCanTouch = !1);
        e.type == TouchType.Up && (this.parentCanTouch = !0)
      }));
      Button.onHover((e => {
        this.parentCanHover = !1;
        e && "#0d000000" == this.parentFrontColor && (this.parentFrontColor = this.parentIsActive ? "#1a0a59f7" : Color.Transparent.toString());
        if (!e) {
          this.parentCanHover = !0;
          this.parentIsHover && (this.parentFrontColor = this.parentIsHover ? "#0d000000" : this.parentIsActive ? "#1a0a59f7" : Color.Transparent.toString())
        }
      }));
      t || Button.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((t, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t);
      Image.create(e.value);
      Image.height(24);
      Image.width(24);
      Image.focusable(!0);
      Image.fillColor({
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_primary"],
        bundleName: "",
        moduleName: ""
      });
      Image.draggable(!1);
      o || Image.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    Button.pop()
  }

  createImage(e, t = null) {
    this.observeComponentCreation(((t, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t);
      Image.create(e);
      Image.height(48);
      Image.width(48);
      Image.draggable(!1);
      o || Image.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }))
  }

  createText(e, t = null) {
    this.observeComponentCreation(((t, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t);
      Text.create(e);
      Text.fontSize({
        id: -1,
        type: 10002,
        params: ["sys.float.ohos_id_text_size_body2"],
        bundleName: "",
        moduleName: ""
      });
      Text.fontColor({
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_text_secondary"],
        bundleName: "",
        moduleName: ""
      });
      Text.focusable(!0);
      Text.draggable(!1);
      o || Text.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    Text.pop()
  }

  createArrow(e, t = null) {
    this.observeComponentCreation(((t, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t);
      Button.createWithChild({ type: ButtonType.Normal });
      Button.hitTestBehavior(HitTestMode.Block);
      Button.backgroundColor(Color.Transparent);
      Button.height(24);
      Button.width(12);
      Button.onFocus((() => {
        this.parentCanFocus = !1
      }));
      Button.onTouch((e => {
        e.type == TouchType.Down && (this.parentCanTouch = !1);
        e.type == TouchType.Up && (this.parentCanTouch = !0)
      }));
      Button.onHover((e => {
        this.parentCanHover = !1;
        e && "#0d000000" == this.parentFrontColor && (this.parentFrontColor = this.parentIsActive ? "#1a0a59f7" : Color.Transparent.toString());
        if (!e) {
          this.parentCanHover = !0;
          this.parentIsHover && (this.parentFrontColor = this.parentIsHover ? "#0d000000" : this.parentIsActive ? "#1a0a59f7" : Color.Transparent.toString())
        }
      }));
      Button.onClick(e.action);
      o || Button.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((t, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t);
      Image.create(e.value);
      Image.height(24);
      Image.width(12);
      Image.focusable(!0);
      Image.fillColor({
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_fourth"],
        bundleName: "",
        moduleName: ""
      });
      Image.draggable(!1);
      o || Image.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    Button.pop()
  }

  createRadio(e, t = null) {
    this.observeComponentCreation(((t, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t);
      Radio.create({ value: null, group: null });
      Radio.checked(this.radioState);
      Radio.onChange(e.onChange);
      Radio.height(24);
      Radio.width(24);
      Radio.onFocus((() => {
        this.parentCanFocus = !1
      }));
      Radio.hitTestBehavior(HitTestMode.Block);
      Radio.onTouch((e => {
        e.type == TouchType.Down && (this.parentCanTouch = !1);
        e.type == TouchType.Up && (this.parentCanTouch = !0)
      }));
      Radio.onHover((e => {
        this.parentCanHover = !1;
        e && "#0d000000" == this.parentFrontColor && (this.parentFrontColor = this.parentIsActive ? "#1a0a59f7" : Color.Transparent.toString());
        if (!e) {
          this.parentCanHover = !0;
          this.parentIsHover && (this.parentFrontColor = this.parentIsHover ? "#0d000000" : this.parentIsActive ? "#1a0a59f7" : Color.Transparent.toString())
        }
      }));
      o || Radio.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }))
  }

  createCheckBox(e, t = null) {
    this.observeComponentCreation(((t, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t);
      Checkbox.create();
      Checkbox.select(this.checkBoxState);
      Checkbox.onChange(e.onChange);
      Checkbox.height(24);
      Checkbox.height(24);
      Checkbox.onFocus((() => {
        this.parentCanFocus = !1
      }));
      Checkbox.hitTestBehavior(HitTestMode.Block);
      Checkbox.onTouch((e => {
        e.type == TouchType.Down && (this.parentCanTouch = !1);
        e.type == TouchType.Up && (this.parentCanTouch = !0)
      }));
      Checkbox.onHover((e => {
        this.parentCanHover = !1;
        e && "#0d000000" == this.parentFrontColor && (this.parentFrontColor = this.parentIsActive ? "#1a0a59f7" : Color.Transparent.toString());
        if (!e) {
          this.parentCanHover = !0;
          this.parentIsHover && (this.parentFrontColor = this.parentIsHover ? "#0d000000" : this.parentIsActive ? "#1a0a59f7" : Color.Transparent.toString())
        }
      }));
      o || Checkbox.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    Checkbox.pop()
  }

  createSwitch(e, t = null) {
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Row.create();
      Row.height(48);
      Row.width(48);
      Row.justifyContent(FlexAlign.Center);
      Row.onFocus((() => {
        this.parentCanFocus = !1
      }));
      Row.onTouch((e => {
        e.type == TouchType.Down && (this.parentCanTouch = !1);
        e.type == TouchType.Up && (this.parentCanTouch = !0)
      }));
      Row.onHover((e => {
        this.parentCanHover = !1;
        e && "#0d000000" == this.parentFrontColor && (this.parentFrontColor = this.parentIsActive ? "#1a0a59f7" : Color.Transparent.toString());
        if (!e) {
          this.parentCanHover = !0;
          this.parentIsHover && (this.parentFrontColor = this.parentIsHover ? "#0d000000" : this.parentIsActive ? "#1a0a59f7" : Color.Transparent.toString())
        }
      }));
      t || Row.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((t, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t);
      Toggle.create({ type: ToggleType.Switch, isOn: this.switchState });
      Toggle.onChange(e.onChange);
      Toggle.onClick((() => {
        this.switchState = !this.switchState
      }));
      Toggle.hitTestBehavior(HitTestMode.Block);
      o || Toggle.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    Toggle.pop();
    Row.pop()
  }

  createTextArrow(e, t, o = null) {
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Button.createWithChild({ type: ButtonType.Normal });
      Button.hitTestBehavior(HitTestMode.Block);
      Button.labelStyle({ maxLines: 1 });
      Button.backgroundColor(Color.Transparent);
      Button.height(32);
      Button.borderRadius({
        id: -1,
        type: 10002,
        params: ["sys.float.ohos_id_corner_radius_clicked"],
        bundleName: "",
        moduleName: ""
      });
      Button.onFocus((() => {
        this.parentCanFocus = !1
      }));
      Button.onTouch((e => {
        e.type == TouchType.Down && (this.parentCanTouch = !1);
        e.type == TouchType.Up && (this.parentCanTouch = !0)
      }));
      Button.onHover((e => {
        this.parentCanHover = !1;
        e && "#0d000000" == this.parentFrontColor && (this.parentFrontColor = this.parentIsActive ? "#1a0a59f7" : Color.Transparent.toString());
        if (!e) {
          this.parentCanHover = !0;
          this.parentIsHover && (this.parentFrontColor = this.parentIsHover ? "#0d000000" : this.parentIsActive ? "#1a0a59f7" : Color.Transparent.toString())
        }
      }));
      t || Button.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Row.create({ space: 4 });
      Row.padding({ left: 8, right: 8 });
      t || Row.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((t, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t);
      Text.create(e);
      Text.fontSize({
        id: -1,
        type: 10002,
        params: ["sys.float.ohos_id_text_size_body2"],
        bundleName: "",
        moduleName: ""
      });
      Text.fontColor({
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_text_secondary"],
        bundleName: "",
        moduleName: ""
      });
      Text.focusable(!0);
      Text.draggable(!1);
      o || Text.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    Text.pop();
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Image.create(t.value);
      Image.height(24);
      Image.width(12);
      Image.fillColor({
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_fourth"],
        bundleName: "",
        moduleName: ""
      });
      Image.focusable(!0);
      Image.draggable(!1);
      o || Image.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    Row.pop();
    Button.pop()
  }

  initialRender() {
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Row.create({ space: this.rowSpace });
      t || Row.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      null != this.button ? this.ifElseBranchUpdateFunction(0, (() => {
        this.createButton.bind(this)(this.button.text)
      })) : null != this.image ? this.ifElseBranchUpdateFunction(1, (() => {
        this.createImage.bind(this)(this.image)
      })) : null != this.icon && null != this.text ? this.ifElseBranchUpdateFunction(2, (() => {
        this.createText.bind(this)(this.text);
        this.createIcon.bind(this)(this.icon)
      })) : null != this.arrow && null == this.text ? this.ifElseBranchUpdateFunction(3, (() => {
        this.createArrow.bind(this)(this.arrow)
      })) : null != this.arrow && null != this.text ? this.ifElseBranchUpdateFunction(4, (() => {
        this.createTextArrow.bind(this)(this.text, this.arrow)
      })) : null != this.text ? this.ifElseBranchUpdateFunction(5, (() => {
        this.createText.bind(this)(this.text)
      })) : null != this.radio ? this.ifElseBranchUpdateFunction(6, (() => {
        this.createRadio.bind(this)(this.radio)
      })) : null != this.checkBox ? this.ifElseBranchUpdateFunction(7, (() => {
        this.createCheckBox.bind(this)(this.checkBox)
      })) : null != this.switch ? this.ifElseBranchUpdateFunction(8, (() => {
        this.createSwitch.bind(this)(this.switch)
      })) : null != this.icon && this.ifElseBranchUpdateFunction(9, (() => {
        this.createIcon.bind(this)(this.icon);
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          If.create();
          null != this.subIcon ? this.ifElseBranchUpdateFunction(0, (() => {
            this.createIcon.bind(this)(this.subIcon)
          })) : If.branchId(1);
          t || If.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        If.pop()
      }));
      t || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop();
    Row.pop()
  }

  rerender() {
    this.updateDirtyElements()
  }
}

export class ComposeListItem extends ViewPU {
  constructor(e, t, o, r = -1) {
    super(e, o, r);
    this.__contentItem = new SynchedPropertyObjectOneWayPU(t.contentItem, this, "contentItem");
    this.__operateItem = new SynchedPropertyObjectOneWayPU(t.operateItem, this, "operateItem");
    this.__frontColor = new ObservedPropertySimplePU(Color.Transparent.toString(), this, "frontColor");
    this.__borderSize = new ObservedPropertySimplePU(0, this, "borderSize");
    this.__canFocus = new ObservedPropertySimplePU(!1, this, "canFocus");
    this.__canTouch = new ObservedPropertySimplePU(!0, this, "canTouch");
    this.__canHover = new ObservedPropertySimplePU(!0, this, "canHover");
    this.__isHover = new ObservedPropertySimplePU(!0, this, "isHover");
    this.__itemHeight = new ObservedPropertySimplePU(ItemHeight.FIRST_HEIGHT, this, "itemHeight");
    this.__isActive = new ObservedPropertySimplePU(!1, this, "isActive");
    this.setInitiallyProvidedValue(t)
  }

  setInitiallyProvidedValue(e) {
    void 0 !== e.contentItem ? this.__contentItem.set(e.contentItem) : this.__contentItem.set(null);
    void 0 !== e.operateItem ? this.__operateItem.set(e.operateItem) : this.__operateItem.set(null);
    void 0 !== e.frontColor && (this.frontColor = e.frontColor);
    void 0 !== e.borderSize && (this.borderSize = e.borderSize);
    void 0 !== e.canFocus && (this.canFocus = e.canFocus);
    void 0 !== e.canTouch && (this.canTouch = e.canTouch);
    void 0 !== e.canHover && (this.canHover = e.canHover);
    void 0 !== e.isHover && (this.isHover = e.isHover);
    void 0 !== e.itemHeight && (this.itemHeight = e.itemHeight);
    void 0 !== e.isActive && (this.isActive = e.isActive)
  }

  updateStateVars(e) {
    this.__contentItem.reset(e.contentItem);
    this.__operateItem.reset(e.operateItem)
  }

  purgeVariableDependenciesOnElmtId(e) {
    this.__contentItem.purgeDependencyOnElmtId(e);
    this.__operateItem.purgeDependencyOnElmtId(e);
    this.__frontColor.purgeDependencyOnElmtId(e);
    this.__borderSize.purgeDependencyOnElmtId(e);
    this.__canFocus.purgeDependencyOnElmtId(e);
    this.__canTouch.purgeDependencyOnElmtId(e);
    this.__canHover.purgeDependencyOnElmtId(e);
    this.__isHover.purgeDependencyOnElmtId(e);
    this.__itemHeight.purgeDependencyOnElmtId(e);
    this.__isActive.purgeDependencyOnElmtId(e)
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
    this.aboutToBeDeletedInternal()
  }

  get contentItem() {
    return this.__contentItem.get()
  }

  set contentItem(e) {
    this.__contentItem.set(e)
  }

  get operateItem() {
    return this.__operateItem.get()
  }

  set operateItem(e) {
    this.__operateItem.set(e)
  }

  get frontColor() {
    return this.__frontColor.get()
  }

  set frontColor(e) {
    this.__frontColor.set(e)
  }

  get borderSize() {
    return this.__borderSize.get()
  }

  set borderSize(e) {
    this.__borderSize.set(e)
  }

  get canFocus() {
    return this.__canFocus.get()
  }

  set canFocus(e) {
    this.__canFocus.set(e)
  }

  get canTouch() {
    return this.__canTouch.get()
  }

  set canTouch(e) {
    this.__canTouch.set(e)
  }

  get canHover() {
    return this.__canHover.get()
  }

  set canHover(e) {
    this.__canHover.set(e)
  }

  get isHover() {
    return this.__isHover.get()
  }

  set isHover(e) {
    this.__isHover.set(e)
  }

  get itemHeight() {
    return this.__itemHeight.get()
  }

  set itemHeight(e) {
    this.__itemHeight.set(e)
  }

  get isActive() {
    return this.__isActive.get()
  }

  set isActive(e) {
    this.__isActive.set(e)
  }

  aboutToAppear() {
    if (void 0 !== this.contentItem) {
      void 0 === this.contentItem.secondaryText && void 0 === this.contentItem.description ? void 0 === this.contentItem.icon ? this.itemHeight = ItemHeight.FIRST_HEIGHT : this.itemHeight = this.contentItem.iconStyle <= IconType.HEAD_SCULPTURE ? ItemHeight.SECOND_HEIGHT : ItemHeight.THIRD_HEIGHT : void 0 === this.contentItem.description ? void 0 === this.contentItem.icon || void 0 !== this.contentItem.icon && this.contentItem.iconStyle <= IconType.SYSTEM_ICON ? this.itemHeight = ItemHeight.THIRD_HEIGHT : this.itemHeight = ItemHeight.FOURTH_HEIGHT : this.itemHeight = ItemHeight.FIFTH_HEIGHT;
      ICON_SIZE_MAP.get(this.contentItem.iconStyle) >= this.itemHeight && (this.itemHeight = ICON_SIZE_MAP.get(this.contentItem.iconStyle) + 32)
    } else void 0 === this.operateItem.image && void 0 === this.operateItem.icon && void 0 === this.operateItem.subIcon || (this.itemHeight = 80)
  }

  initialRender() {
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Stack.create();
      Stack.padding({
        left: {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_default_padding_start"],
          bundleName: "",
          moduleName: ""
        },
        right: {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_default_padding_end"],
          bundleName: "",
          moduleName: ""
        }
      });
      t || Stack.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Flex.create({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center });
      Flex.height(this.itemHeight);
      Flex.focusable(!0);
      Flex.borderRadius({
        id: -1,
        type: 10002,
        params: ["sys.float.ohos_id_corner_radius_default_m"],
        bundleName: "",
        moduleName: ""
      });
      Flex.backgroundColor(this.frontColor);
      Flex.onFocus((() => {
        this.canFocus = !0
      }));
      Flex.onBlur((() => {
        this.canFocus = !1
      }));
      Flex.onHover((e => {
        this.isHover = e;
        this.canHover && (this.frontColor = e ? "#0d000000" : this.isActive ? "#1a0a59f7" : Color.Transparent.toString())
      }));
      Flex.onTouch((e => {
        e.type == TouchType.Down && this.canTouch && (this.frontColor = "#1a000000");
        if (e.type == TouchType.Up) {
          this.isActive = !this.isActive;
          this.frontColor = this.isActive ? "#1a0a59f7" : Color.Transparent.toString()
        }
      }));
      t || Flex.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      void 0 === this.contentItem ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          t ? ViewPU.create(new ContentItemStruct(this, {}, void 0, e)) : this.updateStateVarsOfChildByElmtId(e, {});
          ViewStackProcessor.StopGetAccessRecording()
        }))
      })) : If.branchId(1);
      t || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop();
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      void 0 !== this.contentItem ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          t ? ViewPU.create(new ContentItemStruct(this, {
            icon: "string" == typeof this.contentItem.icon ? null : this.contentItem.icon,
            iconStyle: this.contentItem.iconStyle,
            primaryText: "string" == typeof this.contentItem.primaryText ? this.contentItem.primaryText : null,
            secondaryText: "string" == typeof this.contentItem.secondaryText ? this.contentItem.secondaryText : null,
            description: "string" == typeof this.contentItem.description ? this.contentItem.description : null
          }, void 0, e)) : this.updateStateVarsOfChildByElmtId(e, {});
          ViewStackProcessor.StopGetAccessRecording()
        }))
      })) : If.branchId(1);
      t || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop();
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      void 0 !== this.operateItem ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          __Common__.create();
          __Common__.onFocus((() => {
            this.canFocus = !1
          }));
          __Common__.onBlur((() => {
            this.canFocus = !0
          }));
          t || __Common__.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          t ? ViewPU.create(new OperateItemStruct(this, {
            icon: this.operateItem.icon,
            subIcon: this.operateItem.subIcon,
            button: this.operateItem.button,
            switch: this.operateItem.switch,
            checkBox: this.operateItem.checkbox,
            radio: this.operateItem.radio,
            image: "string" == typeof this.operateItem.image ? null : this.operateItem.image,
            text: "string" == typeof this.operateItem.text ? this.operateItem.text : null,
            arrow: "string" == typeof this.operateItem.arrow ? null : this.operateItem.arrow,
            parentCanFocus: this.__canFocus,
            parentCanTouch: this.__canTouch,
            parentIsHover: this.__isHover,
            parentFrontColor: this.__frontColor,
            parentIsActive: this.__isActive,
            parentCanHover: this.__canHover
          }, void 0, e)) : this.updateStateVarsOfChildByElmtId(e, {});
          ViewStackProcessor.StopGetAccessRecording()
        }));
        __Common__.pop()
      })) : If.branchId(1);
      t || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop();
    Flex.pop();
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      this.canFocus ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Row.create();
          Row.height(this.itemHeight);
          Row.width("100%");
          Row.hitTestBehavior(HitTestMode.None);
          Row.border({
            width: 2,
            color: {
              id: -1,
              type: 10001,
              params: ["sys.color.ohos_id_color_focused_outline"],
              bundleName: "",
              moduleName: ""
            }
          });
          Row.borderRadius({
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_corner_radius_default_m"],
            bundleName: "",
            moduleName: ""
          });
          t || Row.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        Row.pop()
      })) : If.branchId(1);
      t || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop();
    Stack.pop()
  }

  rerender() {
    this.updateDirtyElements()
  }
}