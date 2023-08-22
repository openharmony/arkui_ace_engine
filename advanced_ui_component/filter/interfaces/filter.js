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

const curves = requireNativeModule('ohos.curves');
const measure = requireNapi('measure');

var __decorate = this && this.__decorate || function (o, e, t, r) {
  var i, s = arguments.length, n = s < 3 ? e : null === r ? r = Object.getOwnPropertyDescriptor(e, t) : r;
  if ("object" == typeof Reflect && "function" == typeof Reflect.decorate) n = Reflect.decorate(o, e, t, r); else for (var a = o.length - 1;a >= 0; a--) (i = o[a]) && (n = (s < 3 ? i(n) : s > 3 ? i(e, t, n) : i(e, t)) || n);
  return s > 3 && n && Object.defineProperty(e, t, n), n
};

const TEXT_HOT_AREA_WIDTH = 8;
const LIST_ROW_HEIGHT = 40;
const ARROW_IMG_SIZE = 24;
const MULTI_LINE_PADDING = 24;
const BAR_ANIMATION_DURATION = 150;
const ARROW_ANIMATION_DURATION = 200;
const ANIMATION_DURATION_250 = 250;
const ANIMATION_DURATION_100 = 100;
const FILTER_TOP_PADDING = 8;
const SEPARATOR_HEIGHT = 16;
const SEPARATOR_WIDTH = 1;
const FLOAT_OPACITY = .95;
const FILTER_FONT_SIZE = 12;
const FOCUS_BORDER_WIDTH = 2;
const ARROW_SHOW_DELAY = 300;
const PERCENT_100 = "100%";
const SHARP_CUBIC_BEZIER = curves.cubicBezierCurve(.33, 0, .67, 1);
const INTER_POLATING_SPRING = curves.interpolatingSpring(0, 1, 328, 34);
const FRICTION_CUBIC_BEZIER = curves.cubicBezierCurve(.2, 0, .2, 1);
const TRANS_COLOR = "#00FFFFFF";
const KEYCODE_SPACE = 2050;
const KEYCODE_ENTER = 2054;

export var FilterType;
!function(o){
  o[o.MULTI_LINE_FILTER=0] = "MULTI_LINE_FILTER";
  o[o.LIST_FILTER=1] = "LIST_FILTER"
}(FilterType || (FilterType = {}));
let FontWeightArray = class extends Array {
};
FontWeightArray = __decorate([Observed], FontWeightArray);
let ResourceArray = class extends Array {
};
ResourceArray = __decorate([Observed], ResourceArray);
let BooleanArray = class extends Array {
};
BooleanArray = __decorate([Observed], BooleanArray);
let ObservedBoolean = class {
  constructor(o) {
    this.value = o
  }
};
ObservedBoolean = __decorate([Observed], ObservedBoolean);

export { ObservedBoolean };
let ObservedNumber = class {
  constructor(o) {
    this.value = o
  }
};
ObservedNumber = __decorate([Observed], ObservedNumber);

class ListFilterRow extends ViewPU {
  constructor(o, e, t, r = -1) {
    super(o, t, r);
    this.__colorRow = new SynchedPropertyNesedObjectPU(e.colorRow, this, "colorRow");
    this.__fontWeightRow = new SynchedPropertyNesedObjectPU(e.fontWeightRow, this, "fontWeightRow");
    this.__backgroundColorRow = new SynchedPropertyNesedObjectPU(e.backgroundColorRow, this, "backgroundColorRow");
    this.__isBackgroundHoverRow = new SynchedPropertyNesedObjectPU(e.isBackgroundHoverRow, this, "isBackgroundHoverRow");
    this.filterRow = void 0;
    this.onItemClick = void 0;
    this.setInitiallyProvidedValue(e)
  }

  setInitiallyProvidedValue(o) {
    this.__colorRow.set(o.colorRow);
    this.__fontWeightRow.set(o.fontWeightRow);
    this.__backgroundColorRow.set(o.backgroundColorRow);
    this.__isBackgroundHoverRow.set(o.isBackgroundHoverRow);
    void 0 !== o.filterRow && (this.filterRow = o.filterRow);
    void 0 !== o.onItemClick && (this.onItemClick = o.onItemClick)
  }

  updateStateVars(o) {
    this.__colorRow.set(o.colorRow);
    this.__fontWeightRow.set(o.fontWeightRow);
    this.__backgroundColorRow.set(o.backgroundColorRow);
    this.__isBackgroundHoverRow.set(o.isBackgroundHoverRow)
  }

  purgeVariableDependenciesOnElmtId(o) {
    this.__colorRow.purgeDependencyOnElmtId(o);
    this.__fontWeightRow.purgeDependencyOnElmtId(o);
    this.__backgroundColorRow.purgeDependencyOnElmtId(o);
    this.__isBackgroundHoverRow.purgeDependencyOnElmtId(o)
  }

  aboutToBeDeleted() {
    this.__colorRow.aboutToBeDeleted();
    this.__fontWeightRow.aboutToBeDeleted();
    this.__backgroundColorRow.aboutToBeDeleted();
    this.__isBackgroundHoverRow.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal()
  }

  get colorRow() {
    return this.__colorRow.get()
  }

  get fontWeightRow() {
    return this.__fontWeightRow.get()
  }

  get backgroundColorRow() {
    return this.__backgroundColorRow.get()
  }

  get isBackgroundHoverRow() {
    return this.__isBackgroundHoverRow.get()
  }

  initialRender() {
    this.observeComponentCreation(((o, e) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o);
      List.create();
      List.listDirection(Axis.Horizontal);
      List.margin({ left: -16 });
      List.scrollBar(BarState.Off);
      List.width("100%");
      List.height(40);
      List.align(Alignment.Start);
      e || List.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((o, e) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o);
      ForEach.create();
      this.forEachUpdateFunction(o, this.filterRow.options, ((o, e) => {
        const t = o;
        {
          const o = !0;
          const r = (t, r) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            ListItem.create(s, o);
            ListItem.height("100%");
            ListItem.onClick((() => {
              this.onItemClick(e)
            }));
            ListItem.focusable(!0);
            ViewStackProcessor.visualState("focused");
            ListItem.border({
              radius: {
                id: -1,
                type: 10002,
                params: ["sys.float.ohos_id_corner_radius_clicked"],
                bundleName: "",
                moduleName: ""
              },
              width: 2,
              color: {
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_focused_outline"],
                bundleName: "",
                moduleName: ""
              },
              style: BorderStyle.Solid
            });
            ListItem.padding({ left: 6, right: 6 });
            ViewStackProcessor.visualState("normal");
            ListItem.border({
              radius: {
                id: -1,
                type: 10002,
                params: ["sys.float.ohos_id_corner_radius_clicked"],
                bundleName: "",
                moduleName: ""
              },
              width: 0
            });
            ListItem.padding({ left: 8, right: 8 });
            ViewStackProcessor.visualState();
            ListItem.backgroundColor(this.isBackgroundHoverRow[e] ? this.backgroundColorRow[e] : "#00FFFFFF");
            ListItem.onHover((o => {
              Context.animateTo({ curve: FRICTION_CUBIC_BEZIER, duration: 250 }, (() => {
                if (o) {
                  this.backgroundColorRow[e] = {
                    id: -1,
                    type: 10001,
                    params: ["sys.color.ohos_id_color_hover"],
                    bundleName: "",
                    moduleName: ""
                  };
                  this.isBackgroundHoverRow[e] = !0
                } else this.isBackgroundHoverRow[e] = !1
              }))
            }));
            ListItem.onTouch((o => {
              o.type === TouchType.Down ? Context.animateTo({ curve: SHARP_CUBIC_BEZIER, duration: 100 }, (() => {
                this.backgroundColorRow[e] = {
                  id: -1,
                  type: 10001,
                  params: ["sys.color.ohos_id_color_click_effect"],
                  bundleName: "",
                  moduleName: ""
                };
                this.isBackgroundHoverRow[e] = !0
              })) : o.type === TouchType.Up && Context.animateTo({ curve: SHARP_CUBIC_BEZIER, duration: 100 }, (() => {
                this.isBackgroundHoverRow[e] = !1
              }))
            }));
            r || ListItem.pop();
            ViewStackProcessor.StopGetAccessRecording()
          };
          const i = () => {
            this.observeComponentCreation(r);
            this.observeComponentCreation(((o, r) => {
              ViewStackProcessor.StartGetAccessRecordingFor(o);
              Text.create(t.toString());
              Text.fontSize({
                id: -1,
                type: 10002,
                params: ["sys.float.ohos_id_text_size_body3"],
                bundleName: "",
                moduleName: ""
              });
              Text.fontColor(this.colorRow[e]);
              Text.fontWeight(this.fontWeightRow[e]);
              Text.focusable(!0);
              r || Text.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            Text.pop();
            ListItem.pop()
          };
          const s = (o, i) => {
            r(o, i);
            this.updateFuncByElmtId.set(o, r);
            this.observeComponentCreation(((o, r) => {
              ViewStackProcessor.StartGetAccessRecordingFor(o);
              Text.create(t.toString());
              Text.fontSize({
                id: -1,
                type: 10002,
                params: ["sys.float.ohos_id_text_size_body3"],
                bundleName: "",
                moduleName: ""
              });
              Text.fontColor(this.colorRow[e]);
              Text.fontWeight(this.fontWeightRow[e]);
              Text.focusable(!0);
              r || Text.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            Text.pop();
            ListItem.pop()
          };
          o ? (() => {
            this.observeComponentCreation(r);
            ListItem.pop()
          })() : i()
        }
      }), void 0,!0,!1);
      e || ForEach.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    ForEach.pop();
    List.pop()
  }

  rerender() {
    this.updateDirtyElements()
  }
}

class MultiFilterRow extends ViewPU {
  constructor(o, e, t, r = -1) {
    super(o, t, r);
    this.__colorRow = new SynchedPropertyNesedObjectPU(e.colorRow, this, "colorRow");
    this.__fontWeightRow = new SynchedPropertyNesedObjectPU(e.fontWeightRow, this, "fontWeightRow");
    this.__backgroundColorRow = new SynchedPropertyNesedObjectPU(e.backgroundColorRow, this, "backgroundColorRow");
    this.__isBackgroundHoverRow = new SynchedPropertyNesedObjectPU(e.isBackgroundHoverRow, this, "isBackgroundHoverRow");
    this.__twoLineModeItemNumRow = new SynchedPropertyNesedObjectPU(e.twoLineModeItemNumRow, this, "twoLineModeItemNumRow");
    this.__twoLineModeItemNumRecordRow = new SynchedPropertyNesedObjectPU(e.twoLineModeItemNumRecordRow, this, "twoLineModeItemNumRecordRow");
    this.__arrowShowStateRow = new SynchedPropertyNesedObjectPU(e.arrowShowStateRow, this, "arrowShowStateRow");
    this.__isArrowIconDown = new SynchedPropertyNesedObjectPU(e.isArrowIconDown, this, "isArrowIconDown");
    this.filterRow = null;
    this.onItemClick = void 0;
    this.__arrowBgColorRow = new ObservedPropertyObjectPU({
      id: -1,
      type: 10001,
      params: ["sys.color.ohos_id_color_hover"],
      bundleName: "",
      moduleName: ""
    }, this, "arrowBgColorRow");
    this.__isArrowBgHoverRow = new ObservedPropertySimplePU(!1, this, "isArrowBgHoverRow");
    this.filterColumnWidth = 0;
    this.setInitiallyProvidedValue(e)
  }

  setInitiallyProvidedValue(o) {
    this.__colorRow.set(o.colorRow);
    this.__fontWeightRow.set(o.fontWeightRow);
    this.__backgroundColorRow.set(o.backgroundColorRow);
    this.__isBackgroundHoverRow.set(o.isBackgroundHoverRow);
    this.__twoLineModeItemNumRow.set(o.twoLineModeItemNumRow);
    this.__twoLineModeItemNumRecordRow.set(o.twoLineModeItemNumRecordRow);
    this.__arrowShowStateRow.set(o.arrowShowStateRow);
    this.__isArrowIconDown.set(o.isArrowIconDown);
    void 0 !== o.filterRow && (this.filterRow = o.filterRow);
    void 0 !== o.onItemClick && (this.onItemClick = o.onItemClick);
    void 0 !== o.arrowBgColorRow && (this.arrowBgColorRow = o.arrowBgColorRow);
    void 0 !== o.isArrowBgHoverRow && (this.isArrowBgHoverRow = o.isArrowBgHoverRow);
    void 0 !== o.filterColumnWidth && (this.filterColumnWidth = o.filterColumnWidth)
  }

  updateStateVars(o) {
    this.__colorRow.set(o.colorRow);
    this.__fontWeightRow.set(o.fontWeightRow);
    this.__backgroundColorRow.set(o.backgroundColorRow);
    this.__isBackgroundHoverRow.set(o.isBackgroundHoverRow);
    this.__twoLineModeItemNumRow.set(o.twoLineModeItemNumRow);
    this.__twoLineModeItemNumRecordRow.set(o.twoLineModeItemNumRecordRow);
    this.__arrowShowStateRow.set(o.arrowShowStateRow);
    this.__isArrowIconDown.set(o.isArrowIconDown)
  }

  purgeVariableDependenciesOnElmtId(o) {
    this.__colorRow.purgeDependencyOnElmtId(o);
    this.__fontWeightRow.purgeDependencyOnElmtId(o);
    this.__backgroundColorRow.purgeDependencyOnElmtId(o);
    this.__isBackgroundHoverRow.purgeDependencyOnElmtId(o);
    this.__twoLineModeItemNumRow.purgeDependencyOnElmtId(o);
    this.__twoLineModeItemNumRecordRow.purgeDependencyOnElmtId(o);
    this.__arrowShowStateRow.purgeDependencyOnElmtId(o);
    this.__isArrowIconDown.purgeDependencyOnElmtId(o);
    this.__arrowBgColorRow.purgeDependencyOnElmtId(o);
    this.__isArrowBgHoverRow.purgeDependencyOnElmtId(o)
  }

  aboutToBeDeleted() {
    this.__colorRow.aboutToBeDeleted();
    this.__fontWeightRow.aboutToBeDeleted();
    this.__backgroundColorRow.aboutToBeDeleted();
    this.__isBackgroundHoverRow.aboutToBeDeleted();
    this.__twoLineModeItemNumRow.aboutToBeDeleted();
    this.__twoLineModeItemNumRecordRow.aboutToBeDeleted();
    this.__arrowShowStateRow.aboutToBeDeleted();
    this.__isArrowIconDown.aboutToBeDeleted();
    this.__arrowBgColorRow.aboutToBeDeleted();
    this.__isArrowBgHoverRow.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal()
  }

  get colorRow() {
    return this.__colorRow.get()
  }

  get fontWeightRow() {
    return this.__fontWeightRow.get()
  }

  get backgroundColorRow() {
    return this.__backgroundColorRow.get()
  }

  get isBackgroundHoverRow() {
    return this.__isBackgroundHoverRow.get()
  }

  get twoLineModeItemNumRow() {
    return this.__twoLineModeItemNumRow.get()
  }

  get twoLineModeItemNumRecordRow() {
    return this.__twoLineModeItemNumRecordRow.get()
  }

  get arrowShowStateRow() {
    return this.__arrowShowStateRow.get()
  }

  get isArrowIconDown() {
    return this.__isArrowIconDown.get()
  }

  get arrowBgColorRow() {
    return this.__arrowBgColorRow.get()
  }

  set arrowBgColorRow(o) {
    this.__arrowBgColorRow.set(o)
  }

  get isArrowBgHoverRow() {
    return this.__isArrowBgHoverRow.get()
  }

  set isArrowBgHoverRow(o) {
    this.__isArrowBgHoverRow.set(o)
  }

  calcMultiFilterRowItemNum() {
    var o = this.filterColumnWidth - vp2px(24);
    var e = 0;
    var t = 1;
    for (var r = 0;r < this.filterRow.options.length; r++) {
      let i = this.filterRow.options[r];
      let s = measure.measureText({ textContent: i, fontSize: 12 });
      if (0 !== r) {
        s += vp2px(16);
        if (o - s > 0) {
          o -= s;
          e += 1
        } else {
          if (0 === e) {
            e++;
            o = 0
          }
          if (1 !== t) break;
          t += 1;
          o = this.filterColumnWidth - vp2px(24) - vp2px(24);
          r--
        }
      }
    }
    return e
  }

  DownAndUpArrow(o = null) {
    this.observeComponentCreation(((o, e) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o);
      Row.create();
      Row.border({
        radius: {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_corner_radius_clicked"],
          bundleName: "",
          moduleName: ""
        }
      });
      Row.height(40);
      Row.width(24);
      Row.backgroundColor(this.isArrowBgHoverRow ? this.arrowBgColorRow : "#00FFFFFF");
      Row.focusable(!0);
      Row.visibility(this.arrowShowStateRow.value ? Visibility.Visible : Visibility.Hidden);
      Row.onHover((o => {
        Context.animateTo({ curve: FRICTION_CUBIC_BEZIER, duration: 250 }, (() => {
          if (o) {
            this.arrowBgColorRow = {
              id: -1,
              type: 10001,
              params: ["sys.color.ohos_id_color_hover"],
              bundleName: "",
              moduleName: ""
            };
            this.isArrowBgHoverRow = !0
          } else this.isArrowBgHoverRow = !1
        }))
      }));
      Row.onTouch((o => {
        o.type === TouchType.Down ? Context.animateTo({ curve: SHARP_CUBIC_BEZIER, duration: 100 }, (() => {
          this.arrowBgColorRow = {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_click_effect"],
            bundleName: "",
            moduleName: ""
          };
          this.isArrowBgHoverRow = !0
        })) : o.type === TouchType.Up && Context.animateTo({ curve: SHARP_CUBIC_BEZIER, duration: 100 }, (() => {
          this.isArrowBgHoverRow = !1
        }))
      }));
      Row.onClick((() => {
        if (this.isArrowIconDown.value) {
          this.isArrowIconDown.value = !1;
          this.arrowShowStateRow.value = !1;
          Context.animateTo({ curve: INTER_POLATING_SPRING }, (() => {
            this.twoLineModeItemNumRow.value = this.filterRow.options.length
          }));
          Context.animateTo({ delay: 300, duration: 200, curve: SHARP_CUBIC_BEZIER }, (() => {
            this.arrowShowStateRow.value = !0
          }))
        } else {
          this.isArrowIconDown.value = !0;
          this.arrowShowStateRow.value = !1;
          Context.animateTo({ curve: INTER_POLATING_SPRING }, (() => {
            this.twoLineModeItemNumRow.value = this.twoLineModeItemNumRecordRow.value
          }));
          Context.animateTo({ delay: 300, duration: 200, curve: SHARP_CUBIC_BEZIER }, (() => {
            this.arrowShowStateRow.value = !0
          }))
        }
      }));
      e || Row.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((o, e) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o);
      Image.create(this.isArrowIconDown.value ? {
                                                  id: -1,
                                                  type: 2e4,
                                                  params: ["sys.media.ohos_ic_public_arrow_down"],
                                                  bundleName: "",
                                                  moduleName: ""
                                                } : {
                                                      id: -1,
                                                      type: 2e4,
                                                      params: ["sys.media.ohos_ic_public_arrow_up"],
                                                      bundleName: "",
                                                      moduleName: ""
                                                    });
      Image.width(24);
      Image.height(40);
      Image.fillColor({
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_tertiary"],
        bundleName: "",
        moduleName: ""
      });
      Image.focusable(!0);
      ViewStackProcessor.visualState("focused");
      Image.border({
        radius: {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_corner_radius_clicked"],
          bundleName: "",
          moduleName: ""
        },
        width: 2,
        color: {
          id: -1,
          type: 10001,
          params: ["sys.color.ohos_id_color_focused_outline"],
          bundleName: "",
          moduleName: ""
        },
        style: BorderStyle.Solid
      });
      Image.width(28);
      Image.offset({ x: -2 });
      ViewStackProcessor.visualState("normal");
      Image.border({
        radius: {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_corner_radius_clicked"],
          bundleName: "",
          moduleName: ""
        },
        width: 0
      });
      Image.width(24);
      Image.offset({ x: 0 });
      ViewStackProcessor.visualState();
      e || Image.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    Row.pop()
  }

  initialRender() {
    this.observeComponentCreation(((o, e) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o);
      Row.create();
      Row.width("100%");
      Row.alignItems(VerticalAlign.Top);
      Row.padding({
        left: {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_max_padding_start"],
          bundleName: "",
          moduleName: ""
        },
        right: {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_max_padding_end"],
          bundleName: "",
          moduleName: ""
        }
      });
      e || Row.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((o, e) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o);
      If.create();
      this.filterRow.options && this.filterRow.options.length > 0 ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((o, e) => {
          ViewStackProcessor.StartGetAccessRecordingFor(o);
          Text.create(this.filterRow.options[0].toString());
          Text.height(40);
          Text.width(px2vp(measure.measureText({
            textContent: this.filterRow.options[0].toString(),
            fontSize: 12
          })) + 16);
          Text.margin({ left: -8 });
          Text.fontSize({
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_text_size_body3"],
            bundleName: "",
            moduleName: ""
          });
          Text.fontColor(this.colorRow[0]);
          Text.fontWeight(this.fontWeightRow[0]);
          Text.backgroundColor(this.isBackgroundHoverRow[0] ? this.backgroundColorRow[0] : "#00FFFFFF");
          Text.onClick((() => {
            this.onItemClick(0)
          }));
          Text.focusable(!0);
          Text.onHover((o => {
            Context.animateTo({ curve: FRICTION_CUBIC_BEZIER, duration: 250 }, (() => {
              if (o) {
                this.backgroundColorRow[0] = {
                  id: -1,
                  type: 10001,
                  params: ["sys.color.ohos_id_color_hover"],
                  bundleName: "",
                  moduleName: ""
                };
                this.isBackgroundHoverRow[0] = !0
              } else this.isBackgroundHoverRow[0] = !1
            }))
          }));
          Text.onTouch((o => {
            o.type === TouchType.Down ? Context.animateTo({ curve: SHARP_CUBIC_BEZIER, duration: 100 }, (() => {
              this.backgroundColorRow[0] = {
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_click_effect"],
                bundleName: "",
                moduleName: ""
              };
              this.isBackgroundHoverRow[0] = !0
            })) : o.type === TouchType.Up && Context.animateTo({ curve: SHARP_CUBIC_BEZIER, duration: 100 }, (() => {
              this.isBackgroundHoverRow[0] = !1
            }))
          }));
          ViewStackProcessor.visualState("focused");
          Text.border({
            radius: {
              id: -1,
              type: 10002,
              params: ["sys.float.ohos_id_corner_radius_clicked"],
              bundleName: "",
              moduleName: ""
            },
            width: 2,
            color: {
              id: -1,
              type: 10001,
              params: ["sys.color.ohos_id_color_focused_outline"],
              bundleName: "",
              moduleName: ""
            },
            style: BorderStyle.Solid
          });
          Text.padding({ left: 6, right: 6 });
          ViewStackProcessor.visualState("normal");
          Text.border({
            radius: {
              id: -1,
              type: 10002,
              params: ["sys.float.ohos_id_corner_radius_clicked"],
              bundleName: "",
              moduleName: ""
            },
            width: 0
          });
          Text.padding({ left: 8, right: 8 });
          ViewStackProcessor.visualState();
          e || Text.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        Text.pop()
      })) : If.branchId(1);
      e || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop();
    this.observeComponentCreation(((o, e) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o);
      Row.create();
      Row.width("100%");
      Row.padding({
        right: {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_max_padding_end"],
          bundleName: "",
          moduleName: ""
        }
      });
      Row.onAreaChange(((o, e) => {
        this.filterColumnWidth = vp2px(parseInt(e.width.toString(), 0));
        if (0 === this.twoLineModeItemNumRow.value) {
          var t = this.calcMultiFilterRowItemNum();
          this.twoLineModeItemNumRow.value = t;
          this.twoLineModeItemNumRecordRow.value = t;
          t < this.filterRow.options.length - 1 ? this.arrowShowStateRow.value = !0 : this.arrowShowStateRow.value = !1
        }
      }));
      e || Row.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((o, e) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o);
      Flex.create({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap });
      Flex.alignSelf(ItemAlign.Stretch);
      e || Flex.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((o, e) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o);
      ForEach.create();
      this.forEachUpdateFunction(o, this.filterRow.options.slice(0, this.twoLineModeItemNumRow.value + 1), ((o, e) => {
        const t = o;
        this.observeComponentCreation(((o, r) => {
          ViewStackProcessor.StartGetAccessRecordingFor(o);
          If.create();
          e > 0 ? this.ifElseBranchUpdateFunction(0, (() => {
            this.observeComponentCreation(((o, r) => {
              ViewStackProcessor.StartGetAccessRecordingFor(o);
              Text.create(t.toString());
              Text.transition(TransitionEffect.OPACITY);
              Text.fontSize({
                id: -1,
                type: 10002,
                params: ["sys.float.ohos_id_text_size_body3"],
                bundleName: "",
                moduleName: ""
              });
              Text.height(40);
              Text.fontColor(this.colorRow[e]);
              Text.fontWeight(this.fontWeightRow[e]);
              Text.backgroundColor(this.isBackgroundHoverRow[e] ? this.backgroundColorRow[e] : "#00FFFFFF");
              Text.onClick((() => {
                this.onItemClick(e)
              }));
              Text.onHover((o => {
                Context.animateTo({ curve: FRICTION_CUBIC_BEZIER, duration: 250 }, (() => {
                  if (o) {
                    this.backgroundColorRow[e] = {
                      id: -1,
                      type: 10001,
                      params: ["sys.color.ohos_id_color_hover"],
                      bundleName: "",
                      moduleName: ""
                    };
                    this.isBackgroundHoverRow[e] = !0
                  } else this.isBackgroundHoverRow[e] = !1
                }))
              }));
              Text.onTouch((o => {
                o.type === TouchType.Down ? Context.animateTo({ curve: SHARP_CUBIC_BEZIER, duration: 100 }, (() => {
                  this.backgroundColorRow[e] = {
                    id: -1,
                    type: 10001,
                    params: ["sys.color.ohos_id_color_click_effect"],
                    bundleName: "",
                    moduleName: ""
                  };
                  this.isBackgroundHoverRow[e] = !0
                })) : o.type === TouchType.Up && Context.animateTo({
                  curve: SHARP_CUBIC_BEZIER,
                  duration: 100
                }, (() => {
                  this.isBackgroundHoverRow[e] = !1
                }))
              }));
              Text.focusable(!0);
              ViewStackProcessor.visualState("focused");
              Text.border({
                radius: {
                  id: -1,
                  type: 10002,
                  params: ["sys.float.ohos_id_corner_radius_clicked"],
                  bundleName: "",
                  moduleName: ""
                },
                width: 2,
                color: {
                  id: -1,
                  type: 10001,
                  params: ["sys.color.ohos_id_color_focused_outline"],
                  bundleName: "",
                  moduleName: ""
                },
                style: BorderStyle.Solid
              });
              Text.padding({ left: 6, right: 6 });
              ViewStackProcessor.visualState("normal");
              Text.border({
                radius: {
                  id: -1,
                  type: 10002,
                  params: ["sys.float.ohos_id_corner_radius_clicked"],
                  bundleName: "",
                  moduleName: ""
                },
                width: 0
              });
              Text.padding({ left: 8, right: 8 });
              ViewStackProcessor.visualState();
              r || Text.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            Text.pop()
          })) : If.branchId(1);
          r || If.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        If.pop()
      }), void 0,!0,!1);
      e || ForEach.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    ForEach.pop();
    this.DownAndUpArrow.bind(this)();
    Flex.pop();
    Row.pop();
    Row.pop()
  }

  rerender() {
    this.updateDirtyElements()
  }
}

export class Filter extends ViewPU {
  constructor(o, e, t, r = -1) {
    super(o, t, r);
    this.container = void 0;
    this.__multiFilters = new SynchedPropertyObjectOneWayPU(e.multiFilters, this, "multiFilters");
    this.__additionFilters = new SynchedPropertyObjectOneWayPU(e.additionFilters, this, "additionFilters");
    this.onFilterChanged = null;
    this.__filterType = new SynchedPropertySimpleOneWayPU(e.filterType, this, "filterType");
    this.selectedFilters = null;
    this.__colorArr = new ObservedPropertyObjectPU(null, this, "colorArr");
    this.__fontWeightArr = new ObservedPropertyObjectPU(null, this, "fontWeightArr");
    this.__backgroundColorArr = new ObservedPropertyObjectPU(null, this, "backgroundColorArr");
    this.__isBackgroundHover = new ObservedPropertyObjectPU(null, this, "isBackgroundHover");
    this.__floatArrowBgColor = new ObservedPropertyObjectPU(null, this, "floatArrowBgColor");
    this.__isFloatArrowBgHover = new ObservedPropertySimplePU(!1, this, "isFloatArrowBgHover");
    this.__isArrowIconDownArr = new ObservedPropertyObjectPU(null, this, "isArrowIconDownArr");
    this.__additionColorArr = new ObservedPropertyObjectPU(null, this, "additionColorArr");
    this.__additionFontWeightArr = new ObservedPropertyObjectPU(null, this, "additionFontWeightArr");
    this.__additionBackgroundColorArr = new ObservedPropertyObjectPU(null, this, "additionBackgroundColorArr");
    this.__isAdditionBackgroundHover = new ObservedPropertyObjectPU(null, this, "isAdditionBackgroundHover");
    this.__colorRefresh = new ObservedPropertySimplePU(!1, this, "colorRefresh");
    this.__isFloatBarShow = new ObservedPropertySimplePU(!1, this, "isFloatBarShow");
    this.isFloatBarShowWithoutAnimation = !1;
    this.__isFloatShowAllFilter = new ObservedPropertySimplePU(!1, this, "isFloatShowAllFilter");
    this.isFloatShowAllFilterWithoutAnimation = !1;
    this.__floatFilterPosition = new ObservedPropertySimplePU(0, this, "floatFilterPosition");
    this.__floatFilterBarHeight = new ObservedPropertySimplePU(0, this, "floatFilterBarHeight");
    this.__floatFilterBarPosition = new ObservedPropertySimplePU(0, this, "floatFilterBarPosition");
    this.filterDynamicHeight = 0;
    this.__twoLineModeItemNum = new ObservedPropertyObjectPU(null, this, "twoLineModeItemNum");
    this.__twoLineModeItemNumRecord = new ObservedPropertyObjectPU(null, this, "twoLineModeItemNumRecord");
    this.__downArrowShowState = new ObservedPropertyObjectPU(null, this, "downArrowShowState");
    this.listScroller = new Scroller;
    this.setInitiallyProvidedValue(e)
  }

  setInitiallyProvidedValue(o) {
    void 0 !== o.container && (this.container = o.container);
    void 0 !== o.multiFilters ? this.__multiFilters.set(o.multiFilters) : this.__multiFilters.set([]);
    void 0 !== o.additionFilters ? this.__additionFilters.set(o.additionFilters) : this.__additionFilters.set(null);
    void 0 !== o.onFilterChanged && (this.onFilterChanged = o.onFilterChanged);
    void 0 !== o.filterType ? this.__filterType.set(o.filterType) : this.__filterType.set(FilterType.LIST_FILTER);
    void 0 !== o.selectedFilters && (this.selectedFilters = o.selectedFilters);
    void 0 !== o.colorArr && (this.colorArr = o.colorArr);
    void 0 !== o.fontWeightArr && (this.fontWeightArr = o.fontWeightArr);
    void 0 !== o.backgroundColorArr && (this.backgroundColorArr = o.backgroundColorArr);
    void 0 !== o.isBackgroundHover && (this.isBackgroundHover = o.isBackgroundHover);
    void 0 !== o.floatArrowBgColor && (this.floatArrowBgColor = o.floatArrowBgColor);
    void 0 !== o.isFloatArrowBgHover && (this.isFloatArrowBgHover = o.isFloatArrowBgHover);
    void 0 !== o.isArrowIconDownArr && (this.isArrowIconDownArr = o.isArrowIconDownArr);
    void 0 !== o.additionColorArr && (this.additionColorArr = o.additionColorArr);
    void 0 !== o.additionFontWeightArr && (this.additionFontWeightArr = o.additionFontWeightArr);
    void 0 !== o.additionBackgroundColorArr && (this.additionBackgroundColorArr = o.additionBackgroundColorArr);
    void 0 !== o.isAdditionBackgroundHover && (this.isAdditionBackgroundHover = o.isAdditionBackgroundHover);
    void 0 !== o.colorRefresh && (this.colorRefresh = o.colorRefresh);
    void 0 !== o.isFloatBarShow && (this.isFloatBarShow = o.isFloatBarShow);
    void 0 !== o.isFloatBarShowWithoutAnimation && (this.isFloatBarShowWithoutAnimation = o.isFloatBarShowWithoutAnimation);
    void 0 !== o.isFloatShowAllFilter && (this.isFloatShowAllFilter = o.isFloatShowAllFilter);
    void 0 !== o.isFloatShowAllFilterWithoutAnimation && (this.isFloatShowAllFilterWithoutAnimation = o.isFloatShowAllFilterWithoutAnimation);
    void 0 !== o.floatFilterPosition && (this.floatFilterPosition = o.floatFilterPosition);
    void 0 !== o.floatFilterBarHeight && (this.floatFilterBarHeight = o.floatFilterBarHeight);
    void 0 !== o.floatFilterBarPosition && (this.floatFilterBarPosition = o.floatFilterBarPosition);
    void 0 !== o.filterDynamicHeight && (this.filterDynamicHeight = o.filterDynamicHeight);
    void 0 !== o.twoLineModeItemNum && (this.twoLineModeItemNum = o.twoLineModeItemNum);
    void 0 !== o.twoLineModeItemNumRecord && (this.twoLineModeItemNumRecord = o.twoLineModeItemNumRecord);
    void 0 !== o.downArrowShowState && (this.downArrowShowState = o.downArrowShowState);
    void 0 !== o.listScroller && (this.listScroller = o.listScroller)
  }

  updateStateVars(o) {
    this.__multiFilters.reset(o.multiFilters);
    this.__additionFilters.reset(o.additionFilters);
    this.__filterType.reset(o.filterType)
  }

  purgeVariableDependenciesOnElmtId(o) {
    this.__multiFilters.purgeDependencyOnElmtId(o);
    this.__additionFilters.purgeDependencyOnElmtId(o);
    this.__filterType.purgeDependencyOnElmtId(o);
    this.__colorArr.purgeDependencyOnElmtId(o);
    this.__fontWeightArr.purgeDependencyOnElmtId(o);
    this.__backgroundColorArr.purgeDependencyOnElmtId(o);
    this.__isBackgroundHover.purgeDependencyOnElmtId(o);
    this.__floatArrowBgColor.purgeDependencyOnElmtId(o);
    this.__isFloatArrowBgHover.purgeDependencyOnElmtId(o);
    this.__isArrowIconDownArr.purgeDependencyOnElmtId(o);
    this.__additionColorArr.purgeDependencyOnElmtId(o);
    this.__additionFontWeightArr.purgeDependencyOnElmtId(o);
    this.__additionBackgroundColorArr.purgeDependencyOnElmtId(o);
    this.__isAdditionBackgroundHover.purgeDependencyOnElmtId(o);
    this.__colorRefresh.purgeDependencyOnElmtId(o);
    this.__isFloatBarShow.purgeDependencyOnElmtId(o);
    this.__isFloatShowAllFilter.purgeDependencyOnElmtId(o);
    this.__floatFilterPosition.purgeDependencyOnElmtId(o);
    this.__floatFilterBarHeight.purgeDependencyOnElmtId(o);
    this.__floatFilterBarPosition.purgeDependencyOnElmtId(o);
    this.__twoLineModeItemNum.purgeDependencyOnElmtId(o);
    this.__twoLineModeItemNumRecord.purgeDependencyOnElmtId(o);
    this.__downArrowShowState.purgeDependencyOnElmtId(o)
  }

  aboutToBeDeleted() {
    this.__multiFilters.aboutToBeDeleted();
    this.__additionFilters.aboutToBeDeleted();
    this.__filterType.aboutToBeDeleted();
    this.__colorArr.aboutToBeDeleted();
    this.__fontWeightArr.aboutToBeDeleted();
    this.__backgroundColorArr.aboutToBeDeleted();
    this.__isBackgroundHover.aboutToBeDeleted();
    this.__floatArrowBgColor.aboutToBeDeleted();
    this.__isFloatArrowBgHover.aboutToBeDeleted();
    this.__isArrowIconDownArr.aboutToBeDeleted();
    this.__additionColorArr.aboutToBeDeleted();
    this.__additionFontWeightArr.aboutToBeDeleted();
    this.__additionBackgroundColorArr.aboutToBeDeleted();
    this.__isAdditionBackgroundHover.aboutToBeDeleted();
    this.__colorRefresh.aboutToBeDeleted();
    this.__isFloatBarShow.aboutToBeDeleted();
    this.__isFloatShowAllFilter.aboutToBeDeleted();
    this.__floatFilterPosition.aboutToBeDeleted();
    this.__floatFilterBarHeight.aboutToBeDeleted();
    this.__floatFilterBarPosition.aboutToBeDeleted();
    this.__twoLineModeItemNum.aboutToBeDeleted();
    this.__twoLineModeItemNumRecord.aboutToBeDeleted();
    this.__downArrowShowState.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal()
  }

  get multiFilters() {
    return this.__multiFilters.get()
  }

  set multiFilters(o) {
    this.__multiFilters.set(o)
  }

  get additionFilters() {
    return this.__additionFilters.get()
  }

  set additionFilters(o) {
    this.__additionFilters.set(o)
  }

  get filterType() {
    return this.__filterType.get()
  }

  set filterType(o) {
    this.__filterType.set(o)
  }

  get colorArr() {
    return this.__colorArr.get()
  }

  set colorArr(o) {
    this.__colorArr.set(o)
  }

  get fontWeightArr() {
    return this.__fontWeightArr.get()
  }

  set fontWeightArr(o) {
    this.__fontWeightArr.set(o)
  }

  get backgroundColorArr() {
    return this.__backgroundColorArr.get()
  }

  set backgroundColorArr(o) {
    this.__backgroundColorArr.set(o)
  }

  get isBackgroundHover() {
    return this.__isBackgroundHover.get()
  }

  set isBackgroundHover(o) {
    this.__isBackgroundHover.set(o)
  }

  get floatArrowBgColor() {
    return this.__floatArrowBgColor.get()
  }

  set floatArrowBgColor(o) {
    this.__floatArrowBgColor.set(o)
  }

  get isFloatArrowBgHover() {
    return this.__isFloatArrowBgHover.get()
  }

  set isFloatArrowBgHover(o) {
    this.__isFloatArrowBgHover.set(o)
  }

  get isArrowIconDownArr() {
    return this.__isArrowIconDownArr.get()
  }

  set isArrowIconDownArr(o) {
    this.__isArrowIconDownArr.set(o)
  }

  get additionColorArr() {
    return this.__additionColorArr.get()
  }

  set additionColorArr(o) {
    this.__additionColorArr.set(o)
  }

  get additionFontWeightArr() {
    return this.__additionFontWeightArr.get()
  }

  set additionFontWeightArr(o) {
    this.__additionFontWeightArr.set(o)
  }

  get additionBackgroundColorArr() {
    return this.__additionBackgroundColorArr.get()
  }

  set additionBackgroundColorArr(o) {
    this.__additionBackgroundColorArr.set(o)
  }

  get isAdditionBackgroundHover() {
    return this.__isAdditionBackgroundHover.get()
  }

  set isAdditionBackgroundHover(o) {
    this.__isAdditionBackgroundHover.set(o)
  }

  get colorRefresh() {
    return this.__colorRefresh.get()
  }

  set colorRefresh(o) {
    this.__colorRefresh.set(o)
  }

  get isFloatBarShow() {
    return this.__isFloatBarShow.get()
  }

  set isFloatBarShow(o) {
    this.__isFloatBarShow.set(o)
  }

  get isFloatShowAllFilter() {
    return this.__isFloatShowAllFilter.get()
  }

  set isFloatShowAllFilter(o) {
    this.__isFloatShowAllFilter.set(o)
  }

  get floatFilterPosition() {
    return this.__floatFilterPosition.get()
  }

  set floatFilterPosition(o) {
    this.__floatFilterPosition.set(o)
  }

  get floatFilterBarHeight() {
    return this.__floatFilterBarHeight.get()
  }

  set floatFilterBarHeight(o) {
    this.__floatFilterBarHeight.set(o)
  }

  get floatFilterBarPosition() {
    return this.__floatFilterBarPosition.get()
  }

  set floatFilterBarPosition(o) {
    this.__floatFilterBarPosition.set(o)
  }

  get twoLineModeItemNum() {
    return this.__twoLineModeItemNum.get()
  }

  set twoLineModeItemNum(o) {
    this.__twoLineModeItemNum.set(o)
  }

  get twoLineModeItemNumRecord() {
    return this.__twoLineModeItemNumRecord.get()
  }

  set twoLineModeItemNumRecord(o) {
    this.__twoLineModeItemNumRecord.set(o)
  }

  get downArrowShowState() {
    return this.__downArrowShowState.get()
  }

  set downArrowShowState(o) {
    this.__downArrowShowState.set(o)
  }

  textColor(o, e) {
    return this.selectedFilters.length > o && this.selectedFilters[o].index === e ? {
                                                                                      id: -1,
                                                                                      type: 10001,
                                                                                      params: ["sys.color.ohos_id_color_text_primary_activated"],
                                                                                      bundleName: "",
                                                                                      moduleName: ""
                                                                                    } : {
                                                                                          id: -1,
                                                                                          type: 10001,
                                                                                          params: ["sys.color.ohos_id_color_text_primary"],
                                                                                          bundleName: "",
                                                                                          moduleName: ""
                                                                                        }
  }

  aboutToAppear() {
    this.initParams()
  }

  filterItemClick(o, e) {
    let t = this.multiFilters[o].options[e];
    if (e != this.selectedFilters[o].index) {
      this.colorArr[o][e] = {
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_text_primary_activated"],
        bundleName: "",
        moduleName: ""
      };
      this.colorArr[o][this.selectedFilters[o].index] = {
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_text_primary"],
        bundleName: "",
        moduleName: ""
      };
      this.fontWeightArr[o][e] = FontWeight.Medium;
      this.fontWeightArr[o][this.selectedFilters[o].index] = FontWeight.Regular;
      this.colorRefresh = !this.colorRefresh;
      this.selectedFilters[o].value = t;
      this.selectedFilters[o].index = e;
      this.onFilterChanged && this.onFilterChanged(this.selectedFilters)
    }
  }

  initParams() {
    if (!this.selectedFilters) {
      this.selectedFilters = [];
      for (let e of this.multiFilters) {
        var o = { name: e.name, index: -1, value: null };
        if (e.options.length > 0) {
          o.index = 0;
          o.value = e.options[0]
        }
        this.selectedFilters.push(o)
      }
      if (this.additionFilters && this.additionFilters.name) {
        o = { name: this.additionFilters.name, index: -1, value: null };
        this.selectedFilters.push(o)
      }
    }
    if (!this.colorArr) {
      this.colorArr = [];
      this.backgroundColorArr = [];
      this.isBackgroundHover = [];
      this.fontWeightArr = [];
      this.isArrowIconDownArr = [];
      this.floatArrowBgColor = {
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_hover"],
        bundleName: "",
        moduleName: ""
      };
      for (let o of this.multiFilters) {
        var e = new ResourceArray;
        var t = new FontWeightArray;
        var r = new ResourceArray;
        var i = new BooleanArray;
        for (let i of o.options.keys()) {
          if (0 === i) {
            e.push({
              id: -1,
              type: 10001,
              params: ["sys.color.ohos_id_color_text_primary_activated"],
              bundleName: "",
              moduleName: ""
            });
            t.push(FontWeight.Medium)
          } else {
            e.push({
              id: -1,
              type: 10001,
              params: ["sys.color.ohos_id_color_text_primary"],
              bundleName: "",
              moduleName: ""
            });
            t.push(FontWeight.Regular)
          }
          r.push({
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_hover"],
            bundleName: "",
            moduleName: ""
          })
        }
        this.colorArr.push(e);
        this.fontWeightArr.push(t);
        this.backgroundColorArr.push(r);
        this.isBackgroundHover.push(i);
        this.isArrowIconDownArr.push(new ObservedBoolean(!0))
      }
    }
    if (this.additionFilters && this.additionFilters.options) {
      this.additionColorArr = [];
      this.additionFontWeightArr = [];
      this.additionBackgroundColorArr = [];
      this.isAdditionBackgroundHover = [];
      for (let o = 0;o < this.additionFilters.options.length; o++) {
        this.additionColorArr.push({
          id: -1,
          type: 10001,
          params: ["sys.color.ohos_id_color_text_primary"],
          bundleName: "",
          moduleName: ""
        });
        this.additionFontWeightArr.push(FontWeight.Regular);
        this.additionBackgroundColorArr.push({
          id: -1,
          type: 10001,
          params: ["sys.color.ohos_id_color_hover"],
          bundleName: "",
          moduleName: ""
        });
        this.isAdditionBackgroundHover.push(!1)
      }
    }
    if (!this.twoLineModeItemNum) {
      this.twoLineModeItemNum = [];
      this.twoLineModeItemNumRecord = [];
      this.downArrowShowState = [];
      for (let o = 0;o < this.multiFilters.length; o++) {
        this.twoLineModeItemNum.push(new ObservedNumber(0));
        this.twoLineModeItemNumRecord.push(new ObservedNumber(0));
        this.downArrowShowState.push(new ObservedBoolean(!1))
      }
    }
  }

  ListFilter(o = null) {
    this.observeComponentCreation(((o, e) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o);
      Column.create();
      Column.width("100%");
      Column.align(Alignment.Start);
      Column.padding({
        left: {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_max_padding_start"],
          bundleName: "",
          moduleName: ""
        }
      });
      Column.onAreaChange(((o, e) => {
        if (!this.isFloatShowAllFilterWithoutAnimation && !this.isFloatBarShowWithoutAnimation) {
          null != this.additionFilters ? this.filterDynamicHeight = parseInt(e.height.toString(), 0) + 40 + 8 : this.filterDynamicHeight = parseInt(e.height.toString(), 0) + 8;
          this.floatFilterPosition = -this.filterDynamicHeight
        }
      }));
      e || Column.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((o, e) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o);
      ForEach.create();
      this.forEachUpdateFunction(o, this.multiFilters, ((o, e) => {
        const t = o;
        this.observeComponentCreation(((o, r) => {
          ViewStackProcessor.StartGetAccessRecordingFor(o);
          r ? ViewPU.create(new ListFilterRow(this, {
            colorRow: this.colorArr[e],
            fontWeightRow: this.fontWeightArr[e],
            backgroundColorRow: this.backgroundColorArr[e],
            isBackgroundHoverRow: this.isBackgroundHover[e],
            filterRow: t,
            onItemClick: o => {
              this.filterItemClick(e, o)
            }
          }, void 0, o)) : this.updateStateVarsOfChildByElmtId(o, {
            colorRow: this.colorArr[e],
            fontWeightRow: this.fontWeightArr[e],
            backgroundColorRow: this.backgroundColorArr[e],
            isBackgroundHoverRow: this.isBackgroundHover[e]
          });
          ViewStackProcessor.StopGetAccessRecording()
        }))
      }), void 0,!0,!1);
      e || ForEach.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    ForEach.pop();
    Column.pop()
  }

  MultiLineFilter(o = null) {
    this.observeComponentCreation(((o, e) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o);
      Column.create();
      Column.width("100%");
      Column.onAreaChange(((o, e) => {
        null != this.additionFilters ? this.filterDynamicHeight = parseInt(e.height.toString(), 0) + 40 + 8 : this.filterDynamicHeight = parseInt(e.height.toString(), 0) + 8;
        this.isFloatBarShowWithoutAnimation || this.isFloatShowAllFilterWithoutAnimation || (this.floatFilterPosition = -this.filterDynamicHeight)
      }));
      e || Column.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((o, e) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o);
      ForEach.create();
      this.forEachUpdateFunction(o, this.multiFilters, ((o, e) => {
        const t = o;
        this.observeComponentCreation(((o, r) => {
          ViewStackProcessor.StartGetAccessRecordingFor(o);
          r ? ViewPU.create(new MultiFilterRow(this, {
            colorRow: this.colorArr[e],
            fontWeightRow: this.fontWeightArr[e],
            backgroundColorRow: this.backgroundColorArr[e],
            isBackgroundHoverRow: this.isBackgroundHover[e],
            arrowShowStateRow: this.downArrowShowState[e],
            twoLineModeItemNumRow: this.twoLineModeItemNum[e],
            twoLineModeItemNumRecordRow: this.twoLineModeItemNumRecord[e],
            isArrowIconDown: this.isArrowIconDownArr[e],
            filterRow: t,
            onItemClick: o => {
              this.filterItemClick(e, o)
            }
          }, void 0, o)) : this.updateStateVarsOfChildByElmtId(o, {
            colorRow: this.colorArr[e],
            fontWeightRow: this.fontWeightArr[e],
            backgroundColorRow: this.backgroundColorArr[e],
            isBackgroundHoverRow: this.isBackgroundHover[e],
            arrowShowStateRow: this.downArrowShowState[e],
            twoLineModeItemNumRow: this.twoLineModeItemNum[e],
            twoLineModeItemNumRecordRow: this.twoLineModeItemNumRecord[e],
            isArrowIconDown: this.isArrowIconDownArr[e]
          });
          ViewStackProcessor.StopGetAccessRecording()
        }))
      }), void 0,!0,!1);
      e || ForEach.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    ForEach.pop();
    Column.pop()
  }

  additionItemClick(o) {
    let e = this.multiFilters.length;
    if (this.selectedFilters[e].index != o) if (-1 === this.selectedFilters[e].index) {
      this.additionColorArr[o] = {
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_text_primary_activated"],
        bundleName: "",
        moduleName: ""
      };
      this.additionFontWeightArr[o] = FontWeight.Medium;
      this.selectedFilters[e].value = this.additionFilters.options[o];
      this.selectedFilters[e].index = o
    } else {
      let t = this.selectedFilters[e].index;
      this.additionColorArr[t] = {
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_text_primary"],
        bundleName: "",
        moduleName: ""
      };
      this.additionColorArr[o] = {
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_text_primary_activated"],
        bundleName: "",
        moduleName: ""
      };
      this.additionFontWeightArr[t] = FontWeight.Regular;
      this.additionFontWeightArr[o] = FontWeight.Medium;
      this.selectedFilters[e].value = this.additionFilters.options[o];
      this.selectedFilters[e].index = o
    } else {
      this.additionColorArr[o] = {
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_text_primary"],
        bundleName: "",
        moduleName: ""
      };
      this.additionFontWeightArr[o] = FontWeight.Regular;
      this.selectedFilters[e].value = null;
      this.selectedFilters[e].index = -1
    }
    this.onFilterChanged && this.onFilterChanged(this.selectedFilters);
    this.colorRefresh = !this.colorRefresh
  }

  AdditionFilterList(o = null) {
    this.observeComponentCreation(((o, e) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o);
      If.create();
      this.additionFilters && this.additionFilters.name && this.additionFilters.options && 0 != this.additionFilters.options.length ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((o, e) => {
          ViewStackProcessor.StartGetAccessRecordingFor(o);
          List.create();
          List.listDirection(Axis.Horizontal);
          List.scrollBar(BarState.Off);
          List.padding({
            left: {
              id: -1,
              type: 10002,
              params: ["sys.float.ohos_id_max_padding_start"],
              bundleName: "",
              moduleName: ""
            }
          });
          List.margin({ left: -16 });
          List.width("100%");
          List.height(40);
          e || List.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        {
          const o = !0;
          const e = (e, t) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            ListItem.create(r, o);
            ListItem.height("100%");
            t || ListItem.pop();
            ViewStackProcessor.StopGetAccessRecording()
          };
          const t = () => {
            this.observeComponentCreation(e);
            this.observeComponentCreation(((o, e) => {
              ViewStackProcessor.StartGetAccessRecordingFor(o);
              Row.create();
              e || Row.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            this.observeComponentCreation(((o, e) => {
              ViewStackProcessor.StartGetAccessRecordingFor(o);
              Text.create(this.additionFilters.name.toString());
              Text.fontSize({
                id: -1,
                type: 10002,
                params: ["sys.float.ohos_id_text_size_body3"],
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
              Text.margin({ left: 8, right: 8 });
              e || Text.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            Text.pop();
            this.observeComponentCreation(((o, e) => {
              ViewStackProcessor.StartGetAccessRecordingFor(o);
              Row.create();
              Row.width(1);
              Row.height(16);
              Row.backgroundColor({
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_list_separator"],
                bundleName: "",
                moduleName: ""
              });
              e || Row.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            Row.pop();
            Row.pop();
            ListItem.pop()
          };
          const r = (o, t) => {
            e(o, t);
            this.updateFuncByElmtId.set(o, e);
            this.observeComponentCreation(((o, e) => {
              ViewStackProcessor.StartGetAccessRecordingFor(o);
              Row.create();
              e || Row.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            this.observeComponentCreation(((o, e) => {
              ViewStackProcessor.StartGetAccessRecordingFor(o);
              Text.create(this.additionFilters.name.toString());
              Text.fontSize({
                id: -1,
                type: 10002,
                params: ["sys.float.ohos_id_text_size_body3"],
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
              Text.margin({ left: 8, right: 8 });
              e || Text.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            Text.pop();
            this.observeComponentCreation(((o, e) => {
              ViewStackProcessor.StartGetAccessRecordingFor(o);
              Row.create();
              Row.width(1);
              Row.height(16);
              Row.backgroundColor({
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_list_separator"],
                bundleName: "",
                moduleName: ""
              });
              e || Row.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            Row.pop();
            Row.pop();
            ListItem.pop()
          };
          o ? (() => {
            this.observeComponentCreation(e);
            ListItem.pop()
          })() : t()
        }
        this.observeComponentCreation(((o, e) => {
          ViewStackProcessor.StartGetAccessRecordingFor(o);
          ForEach.create();
          this.forEachUpdateFunction(o, this.additionFilters.options, ((o, e) => {
            const t = o;
            {
              const o = !0;
              const r = (t, r) => {
                ViewStackProcessor.StartGetAccessRecordingFor(t);
                ListItem.create(s, o);
                ListItem.height("100%");
                ListItem.backgroundColor(this.isAdditionBackgroundHover[e] ? this.additionBackgroundColorArr[e] : "#00FFFFFF");
                ListItem.onHover((o => {
                  Context.animateTo({ curve: FRICTION_CUBIC_BEZIER, duration: 250 }, (() => {
                    if (o) {
                      this.additionBackgroundColorArr[e] = {
                        id: -1,
                        type: 10001,
                        params: ["sys.color.ohos_id_color_hover"],
                        bundleName: "",
                        moduleName: ""
                      };
                      this.isAdditionBackgroundHover[e] = !0
                    } else this.isAdditionBackgroundHover[e] = !1
                  }))
                }));
                ListItem.onTouch((o => {
                  o.type === TouchType.Down ? Context.animateTo({ curve: SHARP_CUBIC_BEZIER, duration: 100 }, (() => {
                    this.additionBackgroundColorArr[e] = {
                      id: -1,
                      type: 10001,
                      params: ["sys.color.ohos_id_color_click_effect"],
                      bundleName: "",
                      moduleName: ""
                    };
                    this.isAdditionBackgroundHover[e] = !0
                  })) : o.type === TouchType.Up && Context.animateTo({
                    curve: SHARP_CUBIC_BEZIER,
                    duration: 100
                  }, (() => {
                    this.isAdditionBackgroundHover[e] = !1
                  }))
                }));
                ListItem.focusable(!0);
                ViewStackProcessor.visualState("focused");
                ListItem.border({
                  radius: {
                    id: -1,
                    type: 10002,
                    params: ["sys.float.ohos_id_corner_radius_clicked"],
                    bundleName: "",
                    moduleName: ""
                  },
                  width: 2,
                  color: {
                    id: -1,
                    type: 10001,
                    params: ["sys.color.ohos_id_color_focused_outline"],
                    bundleName: "",
                    moduleName: ""
                  },
                  style: BorderStyle.Solid
                });
                ListItem.padding({ left: 6, right: 6 });
                ViewStackProcessor.visualState("normal");
                ListItem.border({
                  radius: {
                    id: -1,
                    type: 10002,
                    params: ["sys.float.ohos_id_corner_radius_clicked"],
                    bundleName: "",
                    moduleName: ""
                  },
                  width: 0
                });
                ListItem.padding({ left: 8, right: 8 });
                ViewStackProcessor.visualState();
                ListItem.onClick((() => {
                  this.additionItemClick(e)
                }));
                r || ListItem.pop();
                ViewStackProcessor.StopGetAccessRecording()
              };
              const i = () => {
                this.observeComponentCreation(r);
                this.observeComponentCreation(((o, r) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(o);
                  Text.create(t.toString());
                  Text.fontSize({
                    id: -1,
                    type: 10002,
                    params: ["sys.float.ohos_id_text_size_body3"],
                    bundleName: "",
                    moduleName: ""
                  });
                  Text.fontColor(this.additionColorArr[e]);
                  Text.fontWeight(this.additionFontWeightArr[e]);
                  Text.focusable(!0);
                  r || Text.pop();
                  ViewStackProcessor.StopGetAccessRecording()
                }));
                Text.pop();
                ListItem.pop()
              };
              const s = (o, i) => {
                r(o, i);
                this.updateFuncByElmtId.set(o, r);
                this.observeComponentCreation(((o, r) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(o);
                  Text.create(t.toString());
                  Text.fontSize({
                    id: -1,
                    type: 10002,
                    params: ["sys.float.ohos_id_text_size_body3"],
                    bundleName: "",
                    moduleName: ""
                  });
                  Text.fontColor(this.additionColorArr[e]);
                  Text.fontWeight(this.additionFontWeightArr[e]);
                  Text.focusable(!0);
                  r || Text.pop();
                  ViewStackProcessor.StopGetAccessRecording()
                }));
                Text.pop();
                ListItem.pop()
              };
              o ? (() => {
                this.observeComponentCreation(r);
                ListItem.pop()
              })() : i()
            }
          }), void 0,!0,!1);
          e || ForEach.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        ForEach.pop();
        List.pop()
      })) : If.branchId(1);
      e || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop()
  }

  FilterHeader(o = null) {
    this.observeComponentCreation(((o, e) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o);
      Column.create();
      Column.padding({ top: 8 });
      Column.onVisibleAreaChange([0, 1], ((o, e) => {
        if (e > 0) {
          this.isFloatShowAllFilter = !1;
          this.isFloatShowAllFilterWithoutAnimation = !1;
          this.isFloatBarShowWithoutAnimation = !1;
          Context.animateTo({ curve: INTER_POLATING_SPRING, onFinish: () => {
            this.isFloatBarShowWithoutAnimation || (this.isFloatBarShow = !1)
          } }, (() => {
            this.floatFilterBarHeight = 0
          }))
        } else {
          this.isFloatBarShow = !0;
          this.isFloatBarShowWithoutAnimation = !0;
          Context.animateTo({ curve: INTER_POLATING_SPRING }, (() => {
            this.floatFilterBarHeight = 48
          }))
        }
      }));
      e || Column.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((o, e) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o);
      If.create();
      this.filterType === FilterType.LIST_FILTER ? this.ifElseBranchUpdateFunction(0, (() => {
        this.ListFilter.bind(this)()
      })) : this.ifElseBranchUpdateFunction(1, (() => {
        this.MultiLineFilter.bind(this)()
      }));
      e || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop();
    this.AdditionFilterList.bind(this)();
    Column.pop()
  }

  FloatFilterHeader(o = null) {
    this.observeComponentCreation(((o, e) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o);
      Column.create();
      Column.padding({ top: 8 });
      Column.width("100%");
      Column.clip(!0);
      Column.backgroundColor({
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_background"],
        bundleName: "",
        moduleName: ""
      });
      Column.opacity(.95);
      Column.backgroundBlurStyle(BlurStyle.Thin);
      Column.visibility(this.isFloatShowAllFilter ? Visibility.Visible : Visibility.Hidden);
      Column.position({ x: 0, y: this.floatFilterPosition });
      Column.zIndex(2);
      e || Column.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((o, e) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o);
      If.create();
      this.filterType === FilterType.LIST_FILTER ? this.ifElseBranchUpdateFunction(0, (() => {
        this.ListFilter.bind(this)()
      })) : this.ifElseBranchUpdateFunction(1, (() => {
        this.MultiLineFilter.bind(this)()
      }));
      e || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop();
    this.AdditionFilterList.bind(this)();
    Column.pop()
  }

  FloatFilterBar(o = null) {
    this.observeComponentCreation(((o, e) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o);
      Row.create();
      Row.width("100%");
      Row.padding({
        right: {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_max_padding_end"],
          bundleName: "",
          moduleName: ""
        }
      });
      Row.height(this.floatFilterBarHeight);
      Row.backgroundColor({
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_background"],
        bundleName: "",
        moduleName: ""
      });
      Row.opacity(.95);
      Row.clip(!0);
      Row.backgroundBlurStyle(BlurStyle.Thin);
      Row.visibility(this.isFloatBarShow ? Visibility.Visible : Visibility.Hidden);
      Row.alignItems(VerticalAlign.Bottom);
      Row.position({ x: 0, y: this.floatFilterBarPosition });
      Row.zIndex(1);
      e || Row.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((o, e) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o);
      Column.create();
      Column.alignItems(HorizontalAlign.Center);
      Column.width("100%");
      Column.height(40);
      e || Column.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((o, e) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o);
      Row.create();
      Row.height("100%");
      Row.alignItems(VerticalAlign.Center);
      e || Row.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((o, e) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o);
      ForEach.create();
      this.forEachUpdateFunction(o, this.selectedFilters.slice(0, (this.colorRefresh, this.selectedFilters.length)), ((o, e) => {
        const t = o;
        this.observeComponentCreation(((o, r) => {
          ViewStackProcessor.StartGetAccessRecordingFor(o);
          If.create();
          0 != e && null != t.value ? this.ifElseBranchUpdateFunction(0, (() => {
            this.observeComponentCreation(((o, e) => {
              ViewStackProcessor.StartGetAccessRecordingFor(o);
              Text.create("/");
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
                params: ["sys.float.ohos_id_text_size_body3"],
                bundleName: "",
                moduleName: ""
              });
              e || Text.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            Text.pop()
          })) : If.branchId(1);
          r || If.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        If.pop();
        this.observeComponentCreation(((o, e) => {
          ViewStackProcessor.StartGetAccessRecordingFor(o);
          Text.create(t.value);
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
            params: ["sys.float.ohos_id_text_size_body3"],
            bundleName: "",
            moduleName: ""
          });
          e || Text.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        Text.pop()
      }), void 0,!0,!1);
      e || ForEach.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    ForEach.pop();
    Row.pop();
    Column.pop();
    this.observeComponentCreation(((o, e) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o);
      Row.create();
      Row.height(40);
      Row.margin({ left: -24 });
      Row.backgroundColor(this.isFloatArrowBgHover ? this.floatArrowBgColor : "#00FFFFFF");
      Row.focusable(!0);
      ViewStackProcessor.visualState("focused");
      Row.border({
        radius: {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_corner_radius_clicked"],
          bundleName: "",
          moduleName: ""
        },
        width: 2,
        color: {
          id: -1,
          type: 10001,
          params: ["sys.color.ohos_id_color_focused_outline"],
          bundleName: "",
          moduleName: ""
        },
        style: BorderStyle.Solid
      });
      Row.width(28);
      Row.offset({ x: -2 });
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
      Row.width(24);
      Row.offset({ x: 0 });
      ViewStackProcessor.visualState();
      Row.onHover((o => {
        o ? Context.animateTo({ curve: FRICTION_CUBIC_BEZIER, duration: 250 }, (() => {
          this.floatArrowBgColor = {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_hover"],
            bundleName: "",
            moduleName: ""
          };
          this.isFloatArrowBgHover = !0
        })) : Context.animateTo({ curve: FRICTION_CUBIC_BEZIER, duration: 250 }, (() => {
          this.isFloatArrowBgHover = !1
        }))
      }));
      Row.onTouch((o => {
        o.type === TouchType.Down ? Context.animateTo({ curve: SHARP_CUBIC_BEZIER, duration: 100 }, (() => {
          this.floatArrowBgColor = {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_click_effect"],
            bundleName: "",
            moduleName: ""
          };
          this.isFloatArrowBgHover = !0
        })) : o.type === TouchType.Up && Context.animateTo({ curve: SHARP_CUBIC_BEZIER, duration: 100 }, (() => {
          this.isFloatArrowBgHover = !1
        }))
      }));
      Row.onClick((() => {
        Context.animateTo({ duration: 150, curve: SHARP_CUBIC_BEZIER }, (() => {
          this.isFloatBarShow = !1;
          this.isFloatBarShowWithoutAnimation = !1
        }));
        this.isFloatShowAllFilter = !0;
        this.isFloatShowAllFilterWithoutAnimation = !0;
        Context.animateTo({ curve: INTER_POLATING_SPRING }, (() => {
          this.floatFilterPosition = 0;
          this.floatFilterBarPosition = this.filterDynamicHeight
        }))
      }));
      e || Row.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((o, e) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o);
      Image.create({
        id: -1,
        type: 2e4,
        params: ["sys.media.ohos_ic_public_arrow_down"],
        bundleName: "",
        moduleName: ""
      });
      Image.width(24);
      Image.height(24);
      Image.fillColor({
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_tertiary"],
        bundleName: "",
        moduleName: ""
      });
      Image.focusable(!0);
      e || Image.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    Row.pop();
    Row.pop()
  }

  initialRender() {
    this.observeComponentCreation(((o, e) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o);
      Stack.create({ alignContent: Alignment.Top });
      Stack.clip(!0);
      e || Stack.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.FloatFilterBar.bind(this)();
    this.FloatFilterHeader.bind(this)();
    this.observeComponentCreation(((o, e) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o);
      Column.create();
      Column.zIndex(0);
      e || Column.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((o, e) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o);
      List.create({ initialIndex: 0, scroller: this.listScroller });
      List.listDirection(Axis.Vertical);
      List.width("100%");
      List.height("100%");
      List.edgeEffect(EdgeEffect.Spring);
      List.onScroll(((o, e) => {
        if (this.isFloatShowAllFilterWithoutAnimation && e == ScrollState.Scroll) {
          this.isFloatBarShowWithoutAnimation = !0;
          this.isFloatShowAllFilterWithoutAnimation = !1;
          Context.animateTo({ duration: 150, curve: SHARP_CUBIC_BEZIER }, (() => {
            this.isFloatBarShow = !0
          }));
          Context.animateTo({ curve: INTER_POLATING_SPRING, onFinish: () => {
            this.isFloatShowAllFilterWithoutAnimation || (this.isFloatShowAllFilter = !1)
          } }, (() => {
            this.floatFilterPosition = -this.filterDynamicHeight;
            this.floatFilterBarPosition = 0
          }))
        }
      }));
      e || List.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    {
      const o = !0;
      const e = (e, t) => {
        ViewStackProcessor.StartGetAccessRecordingFor(e);
        ListItem.create(r, o);
        ListItem.focusable(!0);
        ListItem.onFocus((() => {
          this.listScroller.scrollToIndex(0,!0)
        }));
        t || ListItem.pop();
        ViewStackProcessor.StopGetAccessRecording()
      };
      const t = () => {
        this.observeComponentCreation(e);
        this.FilterHeader.bind(this)();
        ListItem.pop()
      };
      const r = (o, t) => {
        e(o, t);
        this.updateFuncByElmtId.set(o, e);
        this.FilterHeader.bind(this)();
        ListItem.pop()
      };
      o ? (() => {
        this.observeComponentCreation(e);
        ListItem.pop()
      })() : t()
    }
    {
      const o = !0;
      const e = (e, t) => {
        ViewStackProcessor.StartGetAccessRecordingFor(e);
        ListItem.create(r, o);
        ListItem.focusable(!0);
        ListItem.onFocus((() => {
          this.listScroller.scrollToIndex(1,!0)
        }));
        t || ListItem.pop();
        ViewStackProcessor.StopGetAccessRecording()
      };
      const t = () => {
        this.observeComponentCreation(e);
        this.container.bind(this)();
        ListItem.pop()
      };
      const r = (o, t) => {
        e(o, t);
        this.updateFuncByElmtId.set(o, e);
        this.container.bind(this)();
        ListItem.pop()
      };
      o ? (() => {
        this.observeComponentCreation(e);
        ListItem.pop()
      })() : t()
    }
    List.pop();
    Column.pop();
    Stack.pop()
  }

  rerender() {
    this.updateDirtyElements()
  }
}

export default {
  Filter, FilterType
};