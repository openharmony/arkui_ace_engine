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

const KeyCode = requireNapi("multimodalInput.keyCode").KeyCode;
const SPACE_MARGIN = 8;
const MARGIN_NUM = 4;
const IMAGE_WIDTH_NUM = 16;
const IMAGE_HEIGHT_NUM = 24;
const BUTTON_SIZE = 32;
const SINGLE_LINE_HEIGHT = 48;
const DOUBLE_LINE_HEIGHT = 64;
const BUTTON_HEIGHT = 28;
const IMAGE_WIDTH = 12;
const BORDER_WIDTH = 2;
const DIVIDEND_WIDTH = 3;
const SINGLE_LINE_NUM = 1;
const DOUBLE_LINE_NUM = 2;
const MIN_FONT_SIZE = 14;
const MAIN_TEXT_SIZE = 10;
const CONSTRAINT_NUM = 44;
const CONTENT_NUM = 40;

export var OperationType;
!function(e){
  e[e.TEXT_ARROW=0] = "TEXT_ARROW";
  e[e.BUTTON=1] = "BUTTON";
  e[e.ICON_GROUP=2] = "ICON_GROUP";
  e[e.LOADING=3] = "LOADING"
}(OperationType || (OperationType = {}));

class IconGroup extends ViewPU {
  constructor(e, t, o, r = -1) {
    super(e, o, r);
    this.__bgColor = new ObservedPropertyObjectPU({
      id: -1,
      type: 10001,
      params: ["sys.color.ohos_id_color_sub_background_transparent"],
      bundleName: "",
      moduleName: ""
    }, this, "bgColor");
    this.__isFocus = new ObservedPropertySimplePU(!1, this, "isFocus");
    this.item = void 0;
    this.focusBorderWidth = 2;
    this.setInitiallyProvidedValue(t)
  }

  setInitiallyProvidedValue(e) {
    void 0 !== e.bgColor && (this.bgColor = e.bgColor);
    void 0 !== e.isFocus && (this.isFocus = e.isFocus);
    void 0 !== e.item && (this.item = e.item);
    void 0 !== e.focusBorderWidth && (this.focusBorderWidth = e.focusBorderWidth)
  }

  updateStateVars(e) {
  }

  purgeVariableDependenciesOnElmtId(e) {
    this.__bgColor.purgeDependencyOnElmtId(e);
    this.__isFocus.purgeDependencyOnElmtId(e)
  }

  aboutToBeDeleted() {
    this.__bgColor.aboutToBeDeleted();
    this.__isFocus.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal()
  }

  get bgColor() {
    return this.__bgColor.get()
  }

  set bgColor(e) {
    this.__bgColor.set(e)
  }

  get isFocus() {
    return this.__isFocus.get()
  }

  set isFocus(e) {
    this.__isFocus.set(e)
  }

  initialRender() {
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Row.create();
      Row.focusable(!0);
      Row.width(32);
      Row.height(32);
      Row.margin({ right: 8, bottom: 4 });
      Row.justifyContent(FlexAlign.Center);
      Row.borderRadius({
        id: -1,
        type: 10002,
        params: ["sys.float.ohos_id_corner_radius_clicked"],
        bundleName: "",
        moduleName: ""
      });
      Row.backgroundColor(ObservedObject.GetRawObject(this.bgColor));
      Row.onTouch((e => {
        if (e.type === TouchType.Down) {
          this.item.action && this.item.action();
          this.bgColor = {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_click_effect"],
            bundleName: "",
            moduleName: ""
          }
        }
        e.type === TouchType.Up && (this.bgColor = {
          id: -1,
          type: 10001,
          params: ["sys.color.ohos_id_color_sub_background_transparent"],
          bundleName: "",
          moduleName: ""
        })
      }));
      Row.onHover((e => {
        this.bgColor = e ? {
          id: -1,
          type: 10001,
          params: ["sys.color.ohos_id_color_hover"],
          bundleName: "",
          moduleName: ""
        } : {
          id: -1,
          type: 10001,
          params: ["sys.color.ohos_id_color_sub_background_transparent"],
          bundleName: "",
          moduleName: ""
        }
      }));
      ViewStackProcessor.visualState("focused");
      Row.border({
        radius: {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_corner_radius_clicked"],
          bundleName: "",
          moduleName: ""
        },
        width: this.focusBorderWidth,
        color: {
          id: -1,
          type: 10001,
          params: ["sys.color.ohos_id_color_focused_outline"],
          bundleName: "",
          moduleName: ""
        },
        style: BorderStyle.Solid
      });
      ViewStackProcessor.visualState("normal");
      Row.border({
        radius: {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_corner_radius_clicked"],
          bundleName: "",
          moduleName: ""
        },
        width: 0
      });
      ViewStackProcessor.visualState();
      Row.onKeyEvent((e => {
        e.keyCode !== KeyCode.KEYCODE_ENTER && e.keyCode !== KeyCode.KEYCODE_SPACE || this.item.action && this.item.action()
      }));
      t || Row.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Image.create(this.item.value);
      Image.fillColor({
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_primary"],
        bundleName: "",
        moduleName: ""
      });
      Image.width(24);
      Image.height(24);
      Image.focusable(!0);
      t || Image.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    Row.pop()
  }

  rerender() {
    this.updateDirtyElements()
  }
}

export class SubHeader extends ViewPU {
  constructor(e, t, o, r = -1) {
    super(e, o, r);
    this.__icon = new SynchedPropertyObjectOneWayPU(t.icon, this, "icon");
    this.__primaryTitle = new SynchedPropertySimpleOneWayPU(t.primaryTitle, this, "primaryTitle");
    this.__secondaryTitle = new SynchedPropertySimpleOneWayPU(t.secondaryTitle, this, "secondaryTitle");
    this.__select = new SynchedPropertyObjectOneWayPU(t.select, this, "select");
    this.__operationType = new SynchedPropertySimpleOneWayPU(t.operationType, this, "operationType");
    this.operationItem = void 0;
    this.__isDuplicateLine = new ObservedPropertySimplePU(!1, this, "isDuplicateLine");
    this.__textArrowBgColor = new ObservedPropertyObjectPU({
      id: -1,
      type: 10001,
      params: ["sys.color.ohos_id_color_sub_background_transparent"],
      bundleName: "",
      moduleName: ""
    }, this, "textArrowBgColor");
    this.__buttonBgColor = new ObservedPropertyObjectPU({
      id: -1,
      type: 10001,
      params: ["sys.color.ohos_id_color_sub_background_transparent"],
      bundleName: "",
      moduleName: ""
    }, this, "buttonBgColor");
    this.__flexWidth = new ObservedPropertySimplePU(0, this, "flexWidth");
    this.__textArrowWidth = new ObservedPropertySimplePU(0, this, "textArrowWidth");
    this.__textArrowFocus = new ObservedPropertySimplePU(!1, this, "textArrowFocus");
    this.__buttonFocus = new ObservedPropertySimplePU(!1, this, "buttonFocus");
    this.__arrowWidth = new ObservedPropertySimplePU(0, this, "arrowWidth");
    this.__buttonWidth = new ObservedPropertySimplePU(0, this, "buttonWidth");
    this.focusBorderWidth = 2;
    this.setInitiallyProvidedValue(t)
  }

  setInitiallyProvidedValue(e) {
    void 0 !== e.operationType ? this.__operationType.set(e.operationType) : this.__operationType.set(OperationType.BUTTON);
    void 0 !== e.operationItem && (this.operationItem = e.operationItem);
    void 0 !== e.isDuplicateLine && (this.isDuplicateLine = e.isDuplicateLine);
    void 0 !== e.textArrowBgColor && (this.textArrowBgColor = e.textArrowBgColor);
    void 0 !== e.buttonBgColor && (this.buttonBgColor = e.buttonBgColor);
    void 0 !== e.flexWidth && (this.flexWidth = e.flexWidth);
    void 0 !== e.textArrowWidth && (this.textArrowWidth = e.textArrowWidth);
    void 0 !== e.textArrowFocus && (this.textArrowFocus = e.textArrowFocus);
    void 0 !== e.buttonFocus && (this.buttonFocus = e.buttonFocus);
    void 0 !== e.arrowWidth && (this.arrowWidth = e.arrowWidth);
    void 0 !== e.buttonWidth && (this.buttonWidth = e.buttonWidth);
    void 0 !== e.focusBorderWidth && (this.focusBorderWidth = e.focusBorderWidth)
  }

  updateStateVars(e) {
    this.__icon.reset(e.icon);
    this.__primaryTitle.reset(e.primaryTitle);
    this.__secondaryTitle.reset(e.secondaryTitle);
    this.__select.reset(e.select);
    this.__operationType.reset(e.operationType)
  }

  purgeVariableDependenciesOnElmtId(e) {
    this.__icon.purgeDependencyOnElmtId(e);
    this.__primaryTitle.purgeDependencyOnElmtId(e);
    this.__secondaryTitle.purgeDependencyOnElmtId(e);
    this.__select.purgeDependencyOnElmtId(e);
    this.__operationType.purgeDependencyOnElmtId(e);
    this.__isDuplicateLine.purgeDependencyOnElmtId(e);
    this.__textArrowBgColor.purgeDependencyOnElmtId(e);
    this.__buttonBgColor.purgeDependencyOnElmtId(e);
    this.__flexWidth.purgeDependencyOnElmtId(e);
    this.__textArrowWidth.purgeDependencyOnElmtId(e);
    this.__textArrowFocus.purgeDependencyOnElmtId(e);
    this.__buttonFocus.purgeDependencyOnElmtId(e);
    this.__arrowWidth.purgeDependencyOnElmtId(e);
    this.__buttonWidth.purgeDependencyOnElmtId(e)
  }

  aboutToBeDeleted() {
    this.__icon.aboutToBeDeleted();
    this.__primaryTitle.aboutToBeDeleted();
    this.__secondaryTitle.aboutToBeDeleted();
    this.__select.aboutToBeDeleted();
    this.__operationType.aboutToBeDeleted();
    this.__isDuplicateLine.aboutToBeDeleted();
    this.__textArrowBgColor.aboutToBeDeleted();
    this.__buttonBgColor.aboutToBeDeleted();
    this.__flexWidth.aboutToBeDeleted();
    this.__textArrowWidth.aboutToBeDeleted();
    this.__textArrowFocus.aboutToBeDeleted();
    this.__buttonFocus.aboutToBeDeleted();
    this.__arrowWidth.aboutToBeDeleted();
    this.__buttonWidth.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal()
  }

  get icon() {
    return this.__icon.get()
  }

  set icon(e) {
    this.__icon.set(e)
  }

  get primaryTitle() {
    return this.__primaryTitle.get()
  }

  set primaryTitle(e) {
    this.__primaryTitle.set(e)
  }

  get secondaryTitle() {
    return this.__secondaryTitle.get()
  }

  set secondaryTitle(e) {
    this.__secondaryTitle.set(e)
  }

  get select() {
    return this.__select.get()
  }

  set select(e) {
    this.__select.set(e)
  }

  get operationType() {
    return this.__operationType.get()
  }

  set operationType(e) {
    this.__operationType.set(e)
  }

  get isDuplicateLine() {
    return this.__isDuplicateLine.get()
  }

  set isDuplicateLine(e) {
    this.__isDuplicateLine.set(e)
  }

  get textArrowBgColor() {
    return this.__textArrowBgColor.get()
  }

  set textArrowBgColor(e) {
    this.__textArrowBgColor.set(e)
  }

  get buttonBgColor() {
    return this.__buttonBgColor.get()
  }

  set buttonBgColor(e) {
    this.__buttonBgColor.set(e)
  }

  get flexWidth() {
    return this.__flexWidth.get()
  }

  set flexWidth(e) {
    this.__flexWidth.set(e)
  }

  get textArrowWidth() {
    return this.__textArrowWidth.get()
  }

  set textArrowWidth(e) {
    this.__textArrowWidth.set(e)
  }

  get textArrowFocus() {
    return this.__textArrowFocus.get()
  }

  set textArrowFocus(e) {
    this.__textArrowFocus.set(e)
  }

  get buttonFocus() {
    return this.__buttonFocus.get()
  }

  set buttonFocus(e) {
    this.__buttonFocus.set(e)
  }

  get arrowWidth() {
    return this.__arrowWidth.get()
  }

  set arrowWidth(e) {
    this.__arrowWidth.set(e)
  }

  get buttonWidth() {
    return this.__buttonWidth.get()
  }

  set buttonWidth(e) {
    this.__buttonWidth.set(e)
  }

  ListTextStyle(e, t = null) {
    this.observeComponentCreation(((t, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t);
      Text.create(e.content);
      Text.fontColor({
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_text_secondary"],
        bundleName: "",
        moduleName: ""
      });
      Text.fontSize({
        id: -1,
        type: 10002,
        params: ["sys.float.ohos_id_text_size_sub_title3"],
        bundleName: "",
        moduleName: ""
      });
      Text.fontWeight(FontWeight.Medium);
      Text.maxLines(2);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.margin({
        left: {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_max_padding_end"],
          bundleName: "",
          moduleName: ""
        },
        bottom: 8,
        right: 4
      });
      o || Text.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    Text.pop()
  }

  ListIconStyle(e, t, o = null) {
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Row.create();
      Row.margin({
        left: {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_max_padding_end"],
          bundleName: "",
          moduleName: ""
        },
        bottom: 8,
        right: 4
      });
      t || Row.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Image.create(t);
      Image.width(16);
      Image.height(16);
      Image.margin({ right: 8 });
      o || Image.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((t, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t);
      Text.create(e.content);
      Text.fontColor({
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_text_secondary"],
        bundleName: "",
        moduleName: ""
      });
      Text.fontSize({
        id: -1,
        type: 10002,
        params: ["sys.float.ohos_id_text_size_sub_title3"],
        bundleName: "",
        moduleName: ""
      });
      Text.fontWeight(FontWeight.Medium);
      Text.maxLines(2);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      o || Text.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    Text.pop();
    Row.pop()
  }

  ContentTextStyle(e, t = null) {
    this.observeComponentCreation(((t, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t);
      Text.create(e.content);
      Text.fontColor({
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_text_primary"],
        bundleName: "",
        moduleName: ""
      });
      Text.fontSize({
        id: -1,
        type: 10002,
        params: ["sys.float.ohos_id_text_size_sub_title1"],
        bundleName: "",
        moduleName: ""
      });
      Text.fontWeight(FontWeight.Medium);
      Text.maxLines(2);
      Text.maxFontSize({
        id: -1,
        type: 10002,
        params: ["sys.float.ohos_id_text_size_sub_title1"],
        bundleName: "",
        moduleName: ""
      });
      Text.minFontSize(14);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.margin({
        left: {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_max_padding_start"],
          bundleName: "",
          moduleName: ""
        },
        right: 4,
        bottom: 8
      });
      o || Text.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    Text.pop()
  }

  SubTextStyle(e, t = null) {
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Column.create();
      Column.alignItems(HorizontalAlign.Start);
      Column.onAppear((() => {
        this.isDuplicateLine = !0
      }));
      Column.margin({
        left: {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_max_padding_start"],
          bundleName: "",
          moduleName: ""
        },
        right: 4,
        bottom: 8
      });
      t || Column.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((t, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t);
      Text.create(e.content);
      Text.fontColor({
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_text_primary"],
        bundleName: "",
        moduleName: ""
      });
      Text.fontSize({
        id: -1,
        type: 10002,
        params: ["sys.float.ohos_id_text_size_sub_title1"],
        bundleName: "",
        moduleName: ""
      });
      Text.fontWeight(FontWeight.Medium);
      Text.maxLines(1);
      Text.maxFontSize({
        id: -1,
        type: 10002,
        params: ["sys.float.ohos_id_text_size_sub_title1"],
        bundleName: "",
        moduleName: ""
      });
      Text.minFontSize(14);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      o || Text.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    Text.pop();
    this.observeComponentCreation(((t, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t);
      Text.create(e.subContent);
      Text.fontColor({
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_text_secondary"],
        bundleName: "",
        moduleName: ""
      });
      Text.fontSize({
        id: -1,
        type: 10002,
        params: ["sys.float.ohos_id_text_size_sub_title3"],
        bundleName: "",
        moduleName: ""
      });
      Text.fontWeight(FontWeight.Medium);
      Text.maxLines(1);
      Text.maxFontSize({
        id: -1,
        type: 10002,
        params: ["sys.float.ohos_id_text_size_sub_title3"],
        bundleName: "",
        moduleName: ""
      });
      Text.minFontSize(10);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      o || Text.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    Text.pop();
    Column.pop()
  }

  SelectStyle(e, t = null) {
    this.observeComponentCreation(((t, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t);
      Select.create(e.options);
      Select.selected(e.selected);
      Select.value(e.value);
      Select.onSelect(((t, o) => {
        e.onSelect && e.onSelect(t, o)
      }));
      Select.font({
        size: {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_text_size_sub_title1"],
          bundleName: "",
          moduleName: ""
        },
        weight: FontWeight.Medium
      });
      Select.margin({
        left: {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_default_padding_start"],
          bundleName: "",
          moduleName: ""
        },
        right: 4
      });
      o || Select.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    Select.pop()
  }

  LoadingProcessStyle(e = null) {
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      LoadingProgress.create();
      LoadingProgress.width(24);
      LoadingProgress.height(24);
      LoadingProgress.focusable(!0);
      LoadingProgress.margin({
        right: {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_default_padding_end"],
          bundleName: "",
          moduleName: ""
        },
        bottom: 4
      });
      t || LoadingProgress.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }))
  }

  TextArrowStyle(e, t = null) {
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Row.create();
      Row.onAreaChange(((e, t) => {
        this.textArrowWidth = Number(parseInt(t.width.toString(), 0))
      }));
      Row.constraintSize({ minWidth: this.flexWidth / 3 });
      Row.justifyContent(FlexAlign.End);
      Row.margin({ left: 8 });
      t || Row.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Stack.create();
      t || Stack.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((t, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t);
      Row.create();
      Row.height(32);
      Row.justifyContent(FlexAlign.End);
      Row.onFocus((() => {
        this.textArrowFocus = !0
      }));
      Row.onBlur((() => {
        this.textArrowFocus = !1
      }));
      Row.borderRadius(4);
      Row.focusable(!0);
      Row.margin({ left: 4, right: 4 });
      Row.backgroundColor(ObservedObject.GetRawObject(this.textArrowBgColor));
      Row.onTouch((t => {
        if (t.type === TouchType.Down) {
          e.action && e.action();
          this.textArrowBgColor = {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_click_effect"],
            bundleName: "",
            moduleName: ""
          }
        }
        t.type === TouchType.Up && (this.textArrowBgColor = {
          id: -1,
          type: 10001,
          params: ["sys.color.ohos_id_color_sub_background_transparent"],
          bundleName: "",
          moduleName: ""
        })
      }));
      Row.onHover((e => {
        this.textArrowBgColor = e ? {
          id: -1,
          type: 10001,
          params: ["sys.color.ohos_id_color_hover"],
          bundleName: "",
          moduleName: ""
        } : {
          id: -1,
          type: 10001,
          params: ["sys.color.ohos_id_color_sub_background_transparent"],
          bundleName: "",
          moduleName: ""
        }
      }));
      Row.onKeyEvent((t => {
        t.keyCode !== KeyCode.KEYCODE_ENTER && t.keyCode !== KeyCode.KEYCODE_SPACE || e.action && e.action()
      }));
      Row.onAreaChange(((e, t) => {
        this.arrowWidth = Number(parseInt(t.width.toString(), 0))
      }));
      o || Row.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Row.create();
      Row.margin({ left: 8, right: 8 });
      t || Row.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((t, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t);
      If.create();
      null != e ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((t, o) => {
          ViewStackProcessor.StartGetAccessRecordingFor(t);
          Text.create(e.value);
          Text.fontColor({
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_text_secondary"],
            bundleName: "",
            moduleName: ""
          });
          Text.fontSize({
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_text_size_body2"],
            bundleName: "",
            moduleName: ""
          });
          Text.margin({ right: 4 });
          Text.focusable(!0);
          Text.maxLines(1);
          Text.constraintSize({ maxWidth: this.textArrowWidth - 40 });
          o || Text.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        Text.pop()
      })) : If.branchId(1);
      o || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop();
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Image.create({
        id: -1,
        type: 2e4,
        params: ["sys.media.ohos_ic_public_arrow_right"],
        bundleName: "",
        moduleName: ""
      });
      Image.fillColor({
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_tertiary"],
        bundleName: "",
        moduleName: ""
      });
      Image.width(12);
      Image.height(24);
      Image.focusable(!0);
      t || Image.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    Row.pop();
    Row.pop();
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      this.textArrowFocus ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Row.create();
          Row.height(32);
          Row.width(this.arrowWidth);
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
          Row.borderRadius(4);
          t || Row.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        Row.pop()
      })) : If.branchId(1);
      t || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop();
    Stack.pop();
    Row.pop()
  }

  ButtonStyle(e, t = null) {
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Row.create();
      Row.constraintSize({ minWidth: this.flexWidth / 3 });
      Row.justifyContent(FlexAlign.End);
      Row.focusable(!0);
      Row.margin({ left: 8 });
      t || Row.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Stack.create();
      t || Stack.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((t, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t);
      Row.create();
      Row.justifyContent(FlexAlign.End);
      Row.alignItems(VerticalAlign.Center);
      Row.focusable(!0);
      Row.height(28);
      Row.margin({ left: 8, right: 8 });
      Row.borderRadius(16);
      Row.backgroundColor(ObservedObject.GetRawObject(this.buttonBgColor));
      Row.onFocus((() => {
        this.buttonFocus = !0
      }));
      Row.onBlur((() => {
        this.buttonFocus = !1
      }));
      Row.onTouch((t => {
        if (t.type === TouchType.Down) {
          e.action && e.action();
          this.buttonBgColor = {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_click_effect"],
            bundleName: "",
            moduleName: ""
          }
        }
        t.type === TouchType.Up && (this.buttonBgColor = {
          id: -1,
          type: 10001,
          params: ["sys.color.ohos_id_color_sub_background_transparent"],
          bundleName: "",
          moduleName: ""
        })
      }));
      Row.onHover((e => {
        this.buttonBgColor = e ? {
          id: -1,
          type: 10001,
          params: ["sys.color.ohos_id_color_hover"],
          bundleName: "",
          moduleName: ""
        } : {
          id: -1,
          type: 10001,
          params: ["sys.color.ohos_id_color_sub_background_transparent"],
          bundleName: "",
          moduleName: ""
        }
      }));
      Row.onKeyEvent((t => {
        t.keyCode !== KeyCode.KEYCODE_ENTER && t.keyCode !== KeyCode.KEYCODE_SPACE || e.action && e.action()
      }));
      Row.onAreaChange(((e, t) => {
        let o = Number(parseInt(t.width.toString(), 0));
        this.buttonWidth = o
      }));
      o || Row.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((t, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t);
      If.create();
      null != e ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((t, o) => {
          ViewStackProcessor.StartGetAccessRecordingFor(t);
          Text.create(e.value);
          Text.maxLines(1);
          Text.fontColor({
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_text_primary_activated"],
            bundleName: "",
            moduleName: ""
          });
          Text.fontSize({
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_text_size_button2"],
            bundleName: "",
            moduleName: ""
          });
          Text.fontWeight(FontWeight.Medium);
          Text.margin({ left: 8, right: 8 });
          Text.focusable(!0);
          o || Text.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        Text.pop()
      })) : If.branchId(1);
      o || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop();
    Row.pop();
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      this.buttonFocus ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Row.create();
          Row.height(28);
          Row.width(this.buttonWidth);
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
          Row.borderRadius(16);
          t || Row.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        Row.pop()
      })) : If.branchId(1);
      t || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop();
    Stack.pop();
    Row.pop()
  }

  initialRender() {
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Flex.create({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.End });
      Flex.focusable(!0);
      Flex.onAreaChange(((e, t) => {
        let o = Number(parseInt(t.width.toString(), 0));
        this.flexWidth = o - 44
      }));
      Flex.padding({
        right: {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_default_padding_end"],
          bundleName: "",
          moduleName: ""
        }
      });
      Flex.height(this.isDuplicateLine ? 64 : 48);
      t || Flex.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      null != this.secondaryTitle && null != this.icon ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Row.create();
          Row.margin({ right: 8 });
          t || Row.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        this.ListIconStyle.bind(this)({ content: this.secondaryTitle }, ObservedObject.GetRawObject(this.icon));
        Row.pop()
      })) : null != this.secondaryTitle && null != this.primaryTitle ? this.ifElseBranchUpdateFunction(1, (() => {
        this.SubTextStyle.bind(this)(makeBuilderParameterProxy("SubTextStyle", {
          content: () => this.__primaryTitle ? this.__primaryTitle : this.primaryTitle,
          subContent: () => this.__secondaryTitle ? this.__secondaryTitle : this.secondaryTitle
        }))
      })) : null != this.secondaryTitle ? this.ifElseBranchUpdateFunction(2, (() => {
        this.ListTextStyle.bind(this)(makeBuilderParameterProxy("ListTextStyle", {
          content: () => this.__secondaryTitle ? this.__secondaryTitle : this.secondaryTitle
        }))
      })) : null != this.select ? this.ifElseBranchUpdateFunction(3, (() => {
        this.SelectStyle.bind(this)(ObservedObject.GetRawObject(this.select))
      })) : null != this.primaryTitle && this.ifElseBranchUpdateFunction(4, (() => {
        this.ContentTextStyle.bind(this)(makeBuilderParameterProxy("ContentTextStyle", {
          content: () => this.__primaryTitle ? this.__primaryTitle : this.primaryTitle
        }))
      }));
      t || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop();
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Row.create();
      t || Row.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      this.operationType === OperationType.BUTTON && null != this.operationItem ? this.ifElseBranchUpdateFunction(0, (() => {
        this.ButtonStyle.bind(this)(this.operationItem[0])
      })) : If.branchId(1);
      t || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop();
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      this.operationType === OperationType.ICON_GROUP && null != this.operationItem ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Row.create();
          t || Row.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          ForEach.create();
          this.forEachUpdateFunction(e, this.operationItem, ((e, t) => {
            const o = e;
            this.observeComponentCreation(((e, r) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              If.create();
              0 == t ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation(((e, t) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(e);
                  t ? ViewPU.create(new IconGroup(this, {
                    item: o
                  }, void 0, e)) : this.updateStateVarsOfChildByElmtId(e, {});
                  ViewStackProcessor.StopGetAccessRecording()
                }))
              })) : If.branchId(1);
              r || If.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            If.pop();
            this.observeComponentCreation(((e, r) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              If.create();
              1 == t ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation(((e, t) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(e);
                  t ? ViewPU.create(new IconGroup(this, {
                    item: o
                  }, void 0, e)) : this.updateStateVarsOfChildByElmtId(e, {});
                  ViewStackProcessor.StopGetAccessRecording()
                }))
              })) : If.branchId(1);
              r || If.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            If.pop();
            this.observeComponentCreation(((e, r) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              If.create();
              2 == t ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation(((e, t) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(e);
                  t ? ViewPU.create(new IconGroup(this, {
                    item: o
                  }, void 0, e)) : this.updateStateVarsOfChildByElmtId(e, {});
                  ViewStackProcessor.StopGetAccessRecording()
                }))
              })) : If.branchId(1);
              r || If.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            If.pop()
          }), void 0,!0,!1);
          t || ForEach.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        ForEach.pop();
        Row.pop()
      })) : If.branchId(1);
      t || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop();
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      this.operationType === OperationType.TEXT_ARROW && null != this.operationItem ? this.ifElseBranchUpdateFunction(0, (() => {
        this.TextArrowStyle.bind(this)(this.operationItem[0])
      })) : If.branchId(1);
      t || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop();
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      this.operationType === OperationType.LOADING ? this.ifElseBranchUpdateFunction(0, (() => {
        this.LoadingProcessStyle.bind(this)()
      })) : If.branchId(1);
      t || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop();
    Row.pop();
    Flex.pop()
  }

  rerender() {
    this.updateDirtyElements()
  }
}

export default { OperationType, SubHeader }