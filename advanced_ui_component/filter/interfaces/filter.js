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

var __decorate = this && this.__decorate || function (e, o, t, i) {
  var r, s = arguments.length, n = s < 3 ? o : null === i ? i = Object.getOwnPropertyDescriptor(o, t) : i;
  if ("object" == typeof Reflect && "function" == typeof Reflect.decorate) n = Reflect.decorate(e, o, t, i); else for (var a = e.length - 1;a >= 0; a--) (r = e[a]) && (n = (s < 3 ? r(n) : s > 3 ? r(o, t, n) : r(o, t)) || n);
  return s > 3 && n && Object.defineProperty(o, t, n), n
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
const GRADIENT_WIDTH = 16;

export var FilterType;
!function(e){
  e[e.MULTI_LINE_FILTER=0] = "MULTI_LINE_FILTER";
  e[e.LIST_FILTER=1] = "LIST_FILTER"
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
  constructor(e) {
    this.value = e
  }
};
ObservedBoolean = __decorate([Observed], ObservedBoolean);

export { ObservedBoolean };
let ObservedNumber = class {
  constructor(e) {
    this.value = e
  }
};
ObservedNumber = __decorate([Observed], ObservedNumber);

class GradientMask extends ViewPU {
  constructor(e, o, t, i = -1) {
    super(e, t, i);
    this.x0 = void 0;
    this.y0 = void 0;
    this.x1 = void 0;
    this.y1 = void 0;
    this.settings = new RenderingContextSettings(!0);
    this.context2D = new CanvasRenderingContext2D(this.settings);
    this.setInitiallyProvidedValue(o)
  }

  setInitiallyProvidedValue(e) {
    void 0 !== e.x0 && (this.x0 = e.x0);
    void 0 !== e.y0 && (this.y0 = e.y0);
    void 0 !== e.x1 && (this.x1 = e.x1);
    void 0 !== e.y1 && (this.y1 = e.y1);
    void 0 !== e.settings && (this.settings = e.settings);
    void 0 !== e.context2D && (this.context2D = e.context2D)
  }

  updateStateVars(e) {
  }

  purgeVariableDependenciesOnElmtId(e) {
  }

  aboutToBeDeleted() {
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal()
  }

  initialRender() {
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Column.create();
      Column.width(16);
      Column.height(40);
      o || Column.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Canvas.create(this.context2D);
      Canvas.width(16);
      Canvas.height(40);
      Canvas.onReady((() => {
        var e = this.context2D.createLinearGradient(this.x0, this.y0, this.x1, this.y1);
        e.addColorStop(0, "#ffffffff");
        e.addColorStop(1, "#00ffffff");
        this.context2D.fillStyle = e;
        this.context2D.fillRect(0, 0, 16, 40)
      }));
      o || Canvas.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    Canvas.pop();
    Column.pop()
  }

  rerender() {
    this.updateDirtyElements()
  }
}

class ListFilterRow extends ViewPU {
  constructor(e, o, t, i = -1) {
    super(e, t, i);
    this.__colorRow = new SynchedPropertyNesedObjectPU(o.colorRow, this, "colorRow");
    this.__fontWeightRow = new SynchedPropertyNesedObjectPU(o.fontWeightRow, this, "fontWeightRow");
    this.__backgroundColorRow = new SynchedPropertyNesedObjectPU(o.backgroundColorRow, this, "backgroundColorRow");
    this.__isBackgroundHoverRow = new SynchedPropertyNesedObjectPU(o.isBackgroundHoverRow, this, "isBackgroundHoverRow");
    this.filterRow = void 0;
    this.onItemClick = void 0;
    this.rowIndex = void 0;
    this.setInitiallyProvidedValue(o)
  }

  setInitiallyProvidedValue(e) {
    this.__colorRow.set(e.colorRow);
    this.__fontWeightRow.set(e.fontWeightRow);
    this.__backgroundColorRow.set(e.backgroundColorRow);
    this.__isBackgroundHoverRow.set(e.isBackgroundHoverRow);
    void 0 !== e.filterRow && (this.filterRow = e.filterRow);
    void 0 !== e.onItemClick && (this.onItemClick = e.onItemClick);
    void 0 !== e.rowIndex && (this.rowIndex = e.rowIndex)
  }

  updateStateVars(e) {
    this.__colorRow.set(e.colorRow);
    this.__fontWeightRow.set(e.fontWeightRow);
    this.__backgroundColorRow.set(e.backgroundColorRow);
    this.__isBackgroundHoverRow.set(e.isBackgroundHoverRow)
  }

  purgeVariableDependenciesOnElmtId(e) {
    this.__colorRow.purgeDependencyOnElmtId(e);
    this.__fontWeightRow.purgeDependencyOnElmtId(e);
    this.__backgroundColorRow.purgeDependencyOnElmtId(e);
    this.__isBackgroundHoverRow.purgeDependencyOnElmtId(e)
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
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Stack.create({ alignContent: Alignment.End });
      o || Stack.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Stack.create({ alignContent: Alignment.Start });
      o || Stack.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      List.create();
      List.listDirection(Axis.Horizontal);
      List.scrollBar(BarState.Off);
      List.width("100%");
      List.height(40);
      List.align(Alignment.Start);
      o || List.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      ForEach.create();
      this.forEachUpdateFunction(e, this.filterRow.options, ((e, o) => {
        const t = e;
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          If.create();
          0 == o ? this.ifElseBranchUpdateFunction(0, (() => {
            {
              const e = !0;
              const o = (o, t) => {
                ViewStackProcessor.StartGetAccessRecordingFor(o);
                ListItem.create(i, e);
                ListItem.width({
                  id: -1,
                  type: 10002,
                  params: ["sys.float.ohos_id_max_padding_start"],
                  bundleName: "",
                  moduleName: ""
                });
                ListItem.height(40);
                t || ListItem.pop();
                ViewStackProcessor.StopGetAccessRecording()
              };
              const t = () => {
                this.observeComponentCreation(o);
                ListItem.pop()
              };
              const i = (e, t) => {
                o(e, t);
                this.updateFuncByElmtId.set(e, o);
                ListItem.pop()
              };
              e ? (() => {
                this.observeComponentCreation(o);
                ListItem.pop()
              })() : t()
            }
          })) : If.branchId(1);
          t || If.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        If.pop();
        {
          const e = !0;
          const i = (t, i) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            ListItem.create(s, e);
            ListItem.height("100%");
            ListItem.onClick((() => {
              this.onItemClick(o)
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
            ListItem.backgroundColor(this.isBackgroundHoverRow[o] ? this.backgroundColorRow[o] : "#00FFFFFF");
            ListItem.onHover((e => {
              Context.animateTo({ curve: FRICTION_CUBIC_BEZIER, duration: 250 }, (() => {
                if (e) {
                  this.backgroundColorRow[o] = {
                    id: -1,
                    type: 10001,
                    params: ["sys.color.ohos_id_color_hover"],
                    bundleName: "",
                    moduleName: ""
                  };
                  this.isBackgroundHoverRow[o] = !0
                } else this.isBackgroundHoverRow[o] = !1
              }))
            }));
            ListItem.onTouch((e => {
              e.type === TouchType.Down ? Context.animateTo({ curve: SHARP_CUBIC_BEZIER, duration: 100 }, (() => {
                this.backgroundColorRow[o] = {
                  id: -1,
                  type: 10001,
                  params: ["sys.color.ohos_id_color_click_effect"],
                  bundleName: "",
                  moduleName: ""
                };
                this.isBackgroundHoverRow[o] = !0
              })) : e.type === TouchType.Up && Context.animateTo({ curve: SHARP_CUBIC_BEZIER, duration: 100 }, (() => {
                this.isBackgroundHoverRow[o] = !1
              }))
            }));
            ListItem.margin({ left: 0 == o ? -8 : 0 });
            ListItem.tabIndex(0 == o ? this.rowIndex : -1);
            i || ListItem.pop();
            ViewStackProcessor.StopGetAccessRecording()
          };
          const r = () => {
            this.observeComponentCreation(i);
            this.observeComponentCreation(((e, i) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              Text.create(t.toString());
              Text.fontSize({
                id: -1,
                type: 10002,
                params: ["sys.float.ohos_id_text_size_body3"],
                bundleName: "",
                moduleName: ""
              });
              Text.fontColor(this.colorRow[o]);
              Text.fontWeight(this.fontWeightRow[o]);
              Text.focusable(!0);
              i || Text.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            Text.pop();
            ListItem.pop()
          };
          const s = (e, r) => {
            i(e, r);
            this.updateFuncByElmtId.set(e, i);
            this.observeComponentCreation(((e, i) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              Text.create(t.toString());
              Text.fontSize({
                id: -1,
                type: 10002,
                params: ["sys.float.ohos_id_text_size_body3"],
                bundleName: "",
                moduleName: ""
              });
              Text.fontColor(this.colorRow[o]);
              Text.fontWeight(this.fontWeightRow[o]);
              Text.focusable(!0);
              i || Text.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            Text.pop();
            ListItem.pop()
          };
          e ? (() => {
            this.observeComponentCreation(i);
            ListItem.pop()
          })() : r()
        }
      }), void 0,!0,!1);
      o || ForEach.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    ForEach.pop();
    List.pop();
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      o ? ViewPU.create(new GradientMask(this, {
        x0: 0,
        y0: 20,
        x1: 16,
        y1: 20
      }, void 0, e)) : this.updateStateVarsOfChildByElmtId(e, {});
      ViewStackProcessor.StopGetAccessRecording()
    }));
    Stack.pop();
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      o ? ViewPU.create(new GradientMask(this, {
        x0: 16,
        y0: 20,
        x1: 0,
        y1: 20
      }, void 0, e)) : this.updateStateVarsOfChildByElmtId(e, {});
      ViewStackProcessor.StopGetAccessRecording()
    }));
    Stack.pop()
  }

  rerender() {
    this.updateDirtyElements()
  }
}

class MultiFilterRow extends ViewPU {
  constructor(e, o, t, i = -1) {
    super(e, t, i);
    this.__colorRow = new SynchedPropertyNesedObjectPU(o.colorRow, this, "colorRow");
    this.__fontWeightRow = new SynchedPropertyNesedObjectPU(o.fontWeightRow, this, "fontWeightRow");
    this.__backgroundColorRow = new SynchedPropertyNesedObjectPU(o.backgroundColorRow, this, "backgroundColorRow");
    this.__isBackgroundHoverRow = new SynchedPropertyNesedObjectPU(o.isBackgroundHoverRow, this, "isBackgroundHoverRow");
    this.__twoLineModeItemNumRow = new SynchedPropertyNesedObjectPU(o.twoLineModeItemNumRow, this, "twoLineModeItemNumRow");
    this.__twoLineModeItemNumRecordRow = new SynchedPropertyNesedObjectPU(o.twoLineModeItemNumRecordRow, this, "twoLineModeItemNumRecordRow");
    this.__arrowShowStateRow = new SynchedPropertyNesedObjectPU(o.arrowShowStateRow, this, "arrowShowStateRow");
    this.__isArrowIconDown = new SynchedPropertyNesedObjectPU(o.isArrowIconDown, this, "isArrowIconDown");
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
    this.rowIndex = 0;
    this.setInitiallyProvidedValue(o)
  }

  setInitiallyProvidedValue(e) {
    this.__colorRow.set(e.colorRow);
    this.__fontWeightRow.set(e.fontWeightRow);
    this.__backgroundColorRow.set(e.backgroundColorRow);
    this.__isBackgroundHoverRow.set(e.isBackgroundHoverRow);
    this.__twoLineModeItemNumRow.set(e.twoLineModeItemNumRow);
    this.__twoLineModeItemNumRecordRow.set(e.twoLineModeItemNumRecordRow);
    this.__arrowShowStateRow.set(e.arrowShowStateRow);
    this.__isArrowIconDown.set(e.isArrowIconDown);
    void 0 !== e.filterRow && (this.filterRow = e.filterRow);
    void 0 !== e.onItemClick && (this.onItemClick = e.onItemClick);
    void 0 !== e.arrowBgColorRow && (this.arrowBgColorRow = e.arrowBgColorRow);
    void 0 !== e.isArrowBgHoverRow && (this.isArrowBgHoverRow = e.isArrowBgHoverRow);
    void 0 !== e.filterColumnWidth && (this.filterColumnWidth = e.filterColumnWidth);
    void 0 !== e.rowIndex && (this.rowIndex = e.rowIndex)
  }

  updateStateVars(e) {
    this.__colorRow.set(e.colorRow);
    this.__fontWeightRow.set(e.fontWeightRow);
    this.__backgroundColorRow.set(e.backgroundColorRow);
    this.__isBackgroundHoverRow.set(e.isBackgroundHoverRow);
    this.__twoLineModeItemNumRow.set(e.twoLineModeItemNumRow);
    this.__twoLineModeItemNumRecordRow.set(e.twoLineModeItemNumRecordRow);
    this.__arrowShowStateRow.set(e.arrowShowStateRow);
    this.__isArrowIconDown.set(e.isArrowIconDown)
  }

  purgeVariableDependenciesOnElmtId(e) {
    this.__colorRow.purgeDependencyOnElmtId(e);
    this.__fontWeightRow.purgeDependencyOnElmtId(e);
    this.__backgroundColorRow.purgeDependencyOnElmtId(e);
    this.__isBackgroundHoverRow.purgeDependencyOnElmtId(e);
    this.__twoLineModeItemNumRow.purgeDependencyOnElmtId(e);
    this.__twoLineModeItemNumRecordRow.purgeDependencyOnElmtId(e);
    this.__arrowShowStateRow.purgeDependencyOnElmtId(e);
    this.__isArrowIconDown.purgeDependencyOnElmtId(e);
    this.__arrowBgColorRow.purgeDependencyOnElmtId(e);
    this.__isArrowBgHoverRow.purgeDependencyOnElmtId(e)
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

  set arrowBgColorRow(e) {
    this.__arrowBgColorRow.set(e)
  }

  get isArrowBgHoverRow() {
    return this.__isArrowBgHoverRow.get()
  }

  set isArrowBgHoverRow(e) {
    this.__isArrowBgHoverRow.set(e)
  }

  calcMultiFilterRowItemNum() {
    var e = this.filterColumnWidth - vp2px(24);
    var o = 0;
    var t = 1;
    for (var i = 0;i < this.filterRow.options.length; i++) {
      let r = this.filterRow.options[i];
      let s = measure.measureText({ textContent: r, fontSize: 12 });
      if (0 !== i) {
        s += vp2px(16);
        if (e - s > 0) {
          e -= s;
          o += 1
        } else {
          if (0 === o) {
            o++;
            e = 0
          }
          if (1 !== t) break;
          t += 1;
          e = this.filterColumnWidth - vp2px(24) - vp2px(24);
          i--
        }
      }
    }
    return o
  }

  DownAndUpArrow(e = null) {
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
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
      Row.onHover((e => {
        Context.animateTo({ curve: FRICTION_CUBIC_BEZIER, duration: 250 }, (() => {
          if (e) {
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
      Row.onTouch((e => {
        e.type === TouchType.Down ? Context.animateTo({ curve: SHARP_CUBIC_BEZIER, duration: 100 }, (() => {
          this.arrowBgColorRow = {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_click_effect"],
            bundleName: "",
            moduleName: ""
          };
          this.isArrowBgHoverRow = !0
        })) : e.type === TouchType.Up && Context.animateTo({ curve: SHARP_CUBIC_BEZIER, duration: 100 }, (() => {
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
      o || Row.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
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
      Image.tabIndex(-1);
      o || Image.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    Row.pop()
  }

  initialRender() {
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
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
      o || Row.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      this.filterRow.options && this.filterRow.options.length > 0 ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, o) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
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
          Text.onHover((e => {
            Context.animateTo({ curve: FRICTION_CUBIC_BEZIER, duration: 250 }, (() => {
              if (e) {
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
          Text.onTouch((e => {
            e.type === TouchType.Down ? Context.animateTo({ curve: SHARP_CUBIC_BEZIER, duration: 100 }, (() => {
              this.backgroundColorRow[0] = {
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_click_effect"],
                bundleName: "",
                moduleName: ""
              };
              this.isBackgroundHoverRow[0] = !0
            })) : e.type === TouchType.Up && Context.animateTo({ curve: SHARP_CUBIC_BEZIER, duration: 100 }, (() => {
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
          Text.tabIndex(this.rowIndex);
          o || Text.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        Text.pop()
      })) : If.branchId(1);
      o || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop();
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
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
      Row.onAreaChange(((e, o) => {
        this.filterColumnWidth = vp2px(parseInt(o.width.toString(), 0));
        if (0 === this.twoLineModeItemNumRow.value) {
          var t = this.calcMultiFilterRowItemNum();
          this.twoLineModeItemNumRow.value = t;
          this.twoLineModeItemNumRecordRow.value = t;
          t < this.filterRow.options.length - 1 ? this.arrowShowStateRow.value = !0 : this.arrowShowStateRow.value = !1
        }
      }));
      o || Row.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Flex.create({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap });
      Flex.alignSelf(ItemAlign.Stretch);
      o || Flex.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      ForEach.create();
      this.forEachUpdateFunction(e, this.filterRow.options.slice(0, this.twoLineModeItemNumRow.value + 1), ((e, o) => {
        const t = e;
        this.observeComponentCreation(((e, i) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          If.create();
          o > 0 ? this.ifElseBranchUpdateFunction(0, (() => {
            this.observeComponentCreation(((e, i) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
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
              Text.fontColor(this.colorRow[o]);
              Text.fontWeight(this.fontWeightRow[o]);
              Text.backgroundColor(this.isBackgroundHoverRow[o] ? this.backgroundColorRow[o] : "#00FFFFFF");
              Text.onClick((() => {
                this.onItemClick(o)
              }));
              Text.onHover((e => {
                Context.animateTo({ curve: FRICTION_CUBIC_BEZIER, duration: 250 }, (() => {
                  if (e) {
                    this.backgroundColorRow[o] = {
                      id: -1,
                      type: 10001,
                      params: ["sys.color.ohos_id_color_hover"],
                      bundleName: "",
                      moduleName: ""
                    };
                    this.isBackgroundHoverRow[o] = !0
                  } else this.isBackgroundHoverRow[o] = !1
                }))
              }));
              Text.onTouch((e => {
                e.type === TouchType.Down ? Context.animateTo({ curve: SHARP_CUBIC_BEZIER, duration: 100 }, (() => {
                  this.backgroundColorRow[o] = {
                    id: -1,
                    type: 10001,
                    params: ["sys.color.ohos_id_color_click_effect"],
                    bundleName: "",
                    moduleName: ""
                  };
                  this.isBackgroundHoverRow[o] = !0
                })) : e.type === TouchType.Up && Context.animateTo({
                  curve: SHARP_CUBIC_BEZIER,
                  duration: 100
                }, (() => {
                  this.isBackgroundHoverRow[o] = !1
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
              Text.tabIndex(-1);
              i || Text.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            Text.pop()
          })) : If.branchId(1);
          i || If.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        If.pop()
      }), void 0,!0,!1);
      o || ForEach.pop();
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
  constructor(e, o, t, i = -1) {
    super(e, t, i);
    this.container = void 0;
    this.__multiFilters = new SynchedPropertyObjectOneWayPU(o.multiFilters, this, "multiFilters");
    this.__additionFilters = new SynchedPropertyObjectOneWayPU(o.additionFilters, this, "additionFilters");
    this.onFilterChanged = null;
    this.__filterType = new SynchedPropertySimpleOneWayPU(o.filterType, this, "filterType");
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
    this.setInitiallyProvidedValue(o)
  }

  setInitiallyProvidedValue(e) {
    void 0 !== e.container && (this.container = e.container);
    void 0 === e.multiFilters && this.__multiFilters.set([]);
    void 0 === e.additionFilters && this.__additionFilters.set(null);
    void 0 !== e.onFilterChanged && (this.onFilterChanged = e.onFilterChanged);
    void 0 === e.filterType && this.__filterType.set(FilterType.LIST_FILTER);
    void 0 !== e.selectedFilters && (this.selectedFilters = e.selectedFilters);
    void 0 !== e.colorArr && (this.colorArr = e.colorArr);
    void 0 !== e.fontWeightArr && (this.fontWeightArr = e.fontWeightArr);
    void 0 !== e.backgroundColorArr && (this.backgroundColorArr = e.backgroundColorArr);
    void 0 !== e.isBackgroundHover && (this.isBackgroundHover = e.isBackgroundHover);
    void 0 !== e.floatArrowBgColor && (this.floatArrowBgColor = e.floatArrowBgColor);
    void 0 !== e.isFloatArrowBgHover && (this.isFloatArrowBgHover = e.isFloatArrowBgHover);
    void 0 !== e.isArrowIconDownArr && (this.isArrowIconDownArr = e.isArrowIconDownArr);
    void 0 !== e.additionColorArr && (this.additionColorArr = e.additionColorArr);
    void 0 !== e.additionFontWeightArr && (this.additionFontWeightArr = e.additionFontWeightArr);
    void 0 !== e.additionBackgroundColorArr && (this.additionBackgroundColorArr = e.additionBackgroundColorArr);
    void 0 !== e.isAdditionBackgroundHover && (this.isAdditionBackgroundHover = e.isAdditionBackgroundHover);
    void 0 !== e.colorRefresh && (this.colorRefresh = e.colorRefresh);
    void 0 !== e.isFloatBarShow && (this.isFloatBarShow = e.isFloatBarShow);
    void 0 !== e.isFloatBarShowWithoutAnimation && (this.isFloatBarShowWithoutAnimation = e.isFloatBarShowWithoutAnimation);
    void 0 !== e.isFloatShowAllFilter && (this.isFloatShowAllFilter = e.isFloatShowAllFilter);
    void 0 !== e.isFloatShowAllFilterWithoutAnimation && (this.isFloatShowAllFilterWithoutAnimation = e.isFloatShowAllFilterWithoutAnimation);
    void 0 !== e.floatFilterPosition && (this.floatFilterPosition = e.floatFilterPosition);
    void 0 !== e.floatFilterBarHeight && (this.floatFilterBarHeight = e.floatFilterBarHeight);
    void 0 !== e.floatFilterBarPosition && (this.floatFilterBarPosition = e.floatFilterBarPosition);
    void 0 !== e.filterDynamicHeight && (this.filterDynamicHeight = e.filterDynamicHeight);
    void 0 !== e.twoLineModeItemNum && (this.twoLineModeItemNum = e.twoLineModeItemNum);
    void 0 !== e.twoLineModeItemNumRecord && (this.twoLineModeItemNumRecord = e.twoLineModeItemNumRecord);
    void 0 !== e.downArrowShowState && (this.downArrowShowState = e.downArrowShowState)
  }

  updateStateVars(e) {
    this.__multiFilters.reset(e.multiFilters);
    this.__additionFilters.reset(e.additionFilters);
    this.__filterType.reset(e.filterType)
  }

  purgeVariableDependenciesOnElmtId(e) {
    this.__multiFilters.purgeDependencyOnElmtId(e);
    this.__additionFilters.purgeDependencyOnElmtId(e);
    this.__filterType.purgeDependencyOnElmtId(e);
    this.__colorArr.purgeDependencyOnElmtId(e);
    this.__fontWeightArr.purgeDependencyOnElmtId(e);
    this.__backgroundColorArr.purgeDependencyOnElmtId(e);
    this.__isBackgroundHover.purgeDependencyOnElmtId(e);
    this.__floatArrowBgColor.purgeDependencyOnElmtId(e);
    this.__isFloatArrowBgHover.purgeDependencyOnElmtId(e);
    this.__isArrowIconDownArr.purgeDependencyOnElmtId(e);
    this.__additionColorArr.purgeDependencyOnElmtId(e);
    this.__additionFontWeightArr.purgeDependencyOnElmtId(e);
    this.__additionBackgroundColorArr.purgeDependencyOnElmtId(e);
    this.__isAdditionBackgroundHover.purgeDependencyOnElmtId(e);
    this.__colorRefresh.purgeDependencyOnElmtId(e);
    this.__isFloatBarShow.purgeDependencyOnElmtId(e);
    this.__isFloatShowAllFilter.purgeDependencyOnElmtId(e);
    this.__floatFilterPosition.purgeDependencyOnElmtId(e);
    this.__floatFilterBarHeight.purgeDependencyOnElmtId(e);
    this.__floatFilterBarPosition.purgeDependencyOnElmtId(e);
    this.__twoLineModeItemNum.purgeDependencyOnElmtId(e);
    this.__twoLineModeItemNumRecord.purgeDependencyOnElmtId(e);
    this.__downArrowShowState.purgeDependencyOnElmtId(e)
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

  set multiFilters(e) {
    this.__multiFilters.set(e)
  }

  get additionFilters() {
    return this.__additionFilters.get()
  }

  set additionFilters(e) {
    this.__additionFilters.set(e)
  }

  get filterType() {
    return this.__filterType.get()
  }

  set filterType(e) {
    this.__filterType.set(e)
  }

  get colorArr() {
    return this.__colorArr.get()
  }

  set colorArr(e) {
    this.__colorArr.set(e)
  }

  get fontWeightArr() {
    return this.__fontWeightArr.get()
  }

  set fontWeightArr(e) {
    this.__fontWeightArr.set(e)
  }

  get backgroundColorArr() {
    return this.__backgroundColorArr.get()
  }

  set backgroundColorArr(e) {
    this.__backgroundColorArr.set(e)
  }

  get isBackgroundHover() {
    return this.__isBackgroundHover.get()
  }

  set isBackgroundHover(e) {
    this.__isBackgroundHover.set(e)
  }

  get floatArrowBgColor() {
    return this.__floatArrowBgColor.get()
  }

  set floatArrowBgColor(e) {
    this.__floatArrowBgColor.set(e)
  }

  get isFloatArrowBgHover() {
    return this.__isFloatArrowBgHover.get()
  }

  set isFloatArrowBgHover(e) {
    this.__isFloatArrowBgHover.set(e)
  }

  get isArrowIconDownArr() {
    return this.__isArrowIconDownArr.get()
  }

  set isArrowIconDownArr(e) {
    this.__isArrowIconDownArr.set(e)
  }

  get additionColorArr() {
    return this.__additionColorArr.get()
  }

  set additionColorArr(e) {
    this.__additionColorArr.set(e)
  }

  get additionFontWeightArr() {
    return this.__additionFontWeightArr.get()
  }

  set additionFontWeightArr(e) {
    this.__additionFontWeightArr.set(e)
  }

  get additionBackgroundColorArr() {
    return this.__additionBackgroundColorArr.get()
  }

  set additionBackgroundColorArr(e) {
    this.__additionBackgroundColorArr.set(e)
  }

  get isAdditionBackgroundHover() {
    return this.__isAdditionBackgroundHover.get()
  }

  set isAdditionBackgroundHover(e) {
    this.__isAdditionBackgroundHover.set(e)
  }

  get colorRefresh() {
    return this.__colorRefresh.get()
  }

  set colorRefresh(e) {
    this.__colorRefresh.set(e)
  }

  get isFloatBarShow() {
    return this.__isFloatBarShow.get()
  }

  set isFloatBarShow(e) {
    this.__isFloatBarShow.set(e)
  }

  get isFloatShowAllFilter() {
    return this.__isFloatShowAllFilter.get()
  }

  set isFloatShowAllFilter(e) {
    this.__isFloatShowAllFilter.set(e)
  }

  get floatFilterPosition() {
    return this.__floatFilterPosition.get()
  }

  set floatFilterPosition(e) {
    this.__floatFilterPosition.set(e)
  }

  get floatFilterBarHeight() {
    return this.__floatFilterBarHeight.get()
  }

  set floatFilterBarHeight(e) {
    this.__floatFilterBarHeight.set(e)
  }

  get floatFilterBarPosition() {
    return this.__floatFilterBarPosition.get()
  }

  set floatFilterBarPosition(e) {
    this.__floatFilterBarPosition.set(e)
  }

  get twoLineModeItemNum() {
    return this.__twoLineModeItemNum.get()
  }

  set twoLineModeItemNum(e) {
    this.__twoLineModeItemNum.set(e)
  }

  get twoLineModeItemNumRecord() {
    return this.__twoLineModeItemNumRecord.get()
  }

  set twoLineModeItemNumRecord(e) {
    this.__twoLineModeItemNumRecord.set(e)
  }

  get downArrowShowState() {
    return this.__downArrowShowState.get()
  }

  set downArrowShowState(e) {
    this.__downArrowShowState.set(e)
  }

  textColor(e, o) {
    return this.selectedFilters.length > e && this.selectedFilters[e].index === o ? {
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

  filterItemClick(e, o) {
    let t = this.multiFilters[e].options[o];
    if (o != this.selectedFilters[e].index) {
      this.colorArr[e][o] = {
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_text_primary_activated"],
        bundleName: "",
        moduleName: ""
      };
      this.colorArr[e][this.selectedFilters[e].index] = {
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_text_primary"],
        bundleName: "",
        moduleName: ""
      };
      this.fontWeightArr[e][o] = FontWeight.Medium;
      this.fontWeightArr[e][this.selectedFilters[e].index] = FontWeight.Regular;
      this.colorRefresh = !this.colorRefresh;
      this.selectedFilters[e].value = t;
      this.selectedFilters[e].index = o;
      this.onFilterChanged && this.onFilterChanged(this.selectedFilters)
    }
  }

  initParams() {
    if (!this.selectedFilters) {
      this.selectedFilters = [];
      for (let o of this.multiFilters) {
        var e = { name: o.name, index: -1, value: null };
        if (o.options.length > 0) {
          e.index = 0;
          e.value = o.options[0]
        }
        this.selectedFilters.push(e)
      }
      if (this.additionFilters && this.additionFilters.name) {
        e = { name: this.additionFilters.name, index: -1, value: null };
        this.selectedFilters.push(e)
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
        params: ["sys.color.ohos_id_color_background"],
        bundleName: "",
        moduleName: ""
      };
      for (let e of this.multiFilters) {
        var o = new ResourceArray;
        var t = new FontWeightArray;
        var i = new ResourceArray;
        var r = new BooleanArray;
        for (let r of e.options.keys()) {
          if (0 === r) {
            o.push({
              id: -1,
              type: 10001,
              params: ["sys.color.ohos_id_color_text_primary_activated"],
              bundleName: "",
              moduleName: ""
            });
            t.push(FontWeight.Medium)
          } else {
            o.push({
              id: -1,
              type: 10001,
              params: ["sys.color.ohos_id_color_text_primary"],
              bundleName: "",
              moduleName: ""
            });
            t.push(FontWeight.Regular)
          }
          i.push({
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_hover"],
            bundleName: "",
            moduleName: ""
          })
        }
        this.colorArr.push(o);
        this.fontWeightArr.push(t);
        this.backgroundColorArr.push(i);
        this.isBackgroundHover.push(r);
        this.isArrowIconDownArr.push(new ObservedBoolean(!0))
      }
    }
    if (this.additionFilters && this.additionFilters.options) {
      this.additionColorArr = [];
      this.additionFontWeightArr = [];
      this.additionBackgroundColorArr = [];
      this.isAdditionBackgroundHover = [];
      for (let e = 0;e < this.additionFilters.options.length; e++) {
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
      for (let e = 0;e < this.multiFilters.length; e++) {
        this.twoLineModeItemNum.push(new ObservedNumber(0));
        this.twoLineModeItemNumRecord.push(new ObservedNumber(0));
        this.downArrowShowState.push(new ObservedBoolean(!1))
      }
    }
  }

  ListFilter(e = null) {
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Column.create();
      Column.width("100%");
      Column.align(Alignment.Start);
      Column.onAreaChange(((e, o) => {
        if (!this.isFloatShowAllFilterWithoutAnimation && !this.isFloatBarShowWithoutAnimation) {
          null != this.additionFilters ? this.filterDynamicHeight = parseInt(o.height.toString(), 0) + 40 + 8 : this.filterDynamicHeight = parseInt(o.height.toString(), 0) + 8;
          this.floatFilterPosition = -this.filterDynamicHeight
        }
      }));
      o || Column.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      ForEach.create();
      this.forEachUpdateFunction(e, this.multiFilters, ((e, o) => {
        const t = e;
        this.observeComponentCreation(((e, i) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          i ? ViewPU.create(new ListFilterRow(this, {
            colorRow: this.colorArr[o],
            fontWeightRow: this.fontWeightArr[o],
            backgroundColorRow: this.backgroundColorArr[o],
            isBackgroundHoverRow: this.isBackgroundHover[o],
            filterRow: t,
            onItemClick: e => {
              this.filterItemClick(o, e)
            },
            rowIndex: o
          }, void 0, e)) : this.updateStateVarsOfChildByElmtId(e, {
            colorRow: this.colorArr[o],
            fontWeightRow: this.fontWeightArr[o],
            backgroundColorRow: this.backgroundColorArr[o],
            isBackgroundHoverRow: this.isBackgroundHover[o]
          });
          ViewStackProcessor.StopGetAccessRecording()
        }))
      }), void 0,!0,!1);
      o || ForEach.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    ForEach.pop();
    Column.pop()
  }

  MultiLineFilter(e = null) {
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Column.create();
      Column.width("100%");
      Column.onAreaChange(((e, o) => {
        null != this.additionFilters ? this.filterDynamicHeight = parseInt(o.height.toString(), 0) + 40 + 8 : this.filterDynamicHeight = parseInt(o.height.toString(), 0) + 8;
        this.isFloatBarShowWithoutAnimation || this.isFloatShowAllFilterWithoutAnimation || (this.floatFilterPosition = -this.filterDynamicHeight)
      }));
      o || Column.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      ForEach.create();
      this.forEachUpdateFunction(e, this.multiFilters, ((e, o) => {
        const t = e;
        this.observeComponentCreation(((e, i) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          i ? ViewPU.create(new MultiFilterRow(this, {
            colorRow: this.colorArr[o],
            fontWeightRow: this.fontWeightArr[o],
            backgroundColorRow: this.backgroundColorArr[o],
            isBackgroundHoverRow: this.isBackgroundHover[o],
            arrowShowStateRow: this.downArrowShowState[o],
            twoLineModeItemNumRow: this.twoLineModeItemNum[o],
            twoLineModeItemNumRecordRow: this.twoLineModeItemNumRecord[o],
            isArrowIconDown: this.isArrowIconDownArr[o],
            filterRow: t,
            onItemClick: e => {
              this.filterItemClick(o, e)
            },
            rowIndex: o
          }, void 0, e)) : this.updateStateVarsOfChildByElmtId(e, {
            colorRow: this.colorArr[o],
            fontWeightRow: this.fontWeightArr[o],
            backgroundColorRow: this.backgroundColorArr[o],
            isBackgroundHoverRow: this.isBackgroundHover[o],
            arrowShowStateRow: this.downArrowShowState[o],
            twoLineModeItemNumRow: this.twoLineModeItemNum[o],
            twoLineModeItemNumRecordRow: this.twoLineModeItemNumRecord[o],
            isArrowIconDown: this.isArrowIconDownArr[o]
          });
          ViewStackProcessor.StopGetAccessRecording()
        }))
      }), void 0,!0,!1);
      o || ForEach.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    ForEach.pop();
    Column.pop()
  }

  additionItemClick(e) {
    let o = this.multiFilters.length;
    if (this.selectedFilters[o].index != e) if (-1 === this.selectedFilters[o].index) {
      this.additionColorArr[e] = {
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_text_primary_activated"],
        bundleName: "",
        moduleName: ""
      };
      this.additionFontWeightArr[e] = FontWeight.Medium;
      this.selectedFilters[o].value = this.additionFilters.options[e];
      this.selectedFilters[o].index = e
    } else {
      let t = this.selectedFilters[o].index;
      this.additionColorArr[t] = {
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_text_primary"],
        bundleName: "",
        moduleName: ""
      };
      this.additionColorArr[e] = {
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_text_primary_activated"],
        bundleName: "",
        moduleName: ""
      };
      this.additionFontWeightArr[t] = FontWeight.Regular;
      this.additionFontWeightArr[e] = FontWeight.Medium;
      this.selectedFilters[o].value = this.additionFilters.options[e];
      this.selectedFilters[o].index = e
    } else {
      this.additionColorArr[e] = {
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_text_primary"],
        bundleName: "",
        moduleName: ""
      };
      this.additionFontWeightArr[e] = FontWeight.Regular;
      this.selectedFilters[o].value = null;
      this.selectedFilters[o].index = -1
    }
    this.onFilterChanged && this.onFilterChanged(this.selectedFilters);
    this.colorRefresh = !this.colorRefresh
  }

  AdditionFilterList(e = null) {
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      this.additionFilters && this.additionFilters.name && this.additionFilters.options && 0 != this.additionFilters.options.length ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, o) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Stack.create({ alignContent: Alignment.End });
          o || Stack.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, o) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Stack.create({ alignContent: Alignment.Start });
          o || Stack.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, o) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          List.create();
          List.listDirection(Axis.Horizontal);
          List.scrollBar(BarState.Off);
          List.width("100%");
          List.height(40);
          o || List.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        {
          const e = !0;
          const o = (o, t) => {
            ViewStackProcessor.StartGetAccessRecordingFor(o);
            ListItem.create(i, e);
            ListItem.height("100%");
            ListItem.margin({ left: -8 });
            t || ListItem.pop();
            ViewStackProcessor.StopGetAccessRecording()
          };
          const t = () => {
            this.observeComponentCreation(o);
            this.observeComponentCreation(((e, o) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              Row.create();
              o || Row.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            this.observeComponentCreation(((e, o) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
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
              Text.padding({
                left: {
                  id: -1,
                  type: 10002,
                  params: ["sys.float.ohos_id_max_padding_start"],
                  bundleName: "",
                  moduleName: ""
                }
              });
              o || Text.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            Text.pop();
            this.observeComponentCreation(((e, o) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
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
              o || Row.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            Row.pop();
            Row.pop();
            ListItem.pop()
          };
          const i = (e, t) => {
            o(e, t);
            this.updateFuncByElmtId.set(e, o);
            this.observeComponentCreation(((e, o) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              Row.create();
              o || Row.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            this.observeComponentCreation(((e, o) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
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
              Text.padding({
                left: {
                  id: -1,
                  type: 10002,
                  params: ["sys.float.ohos_id_max_padding_start"],
                  bundleName: "",
                  moduleName: ""
                }
              });
              o || Text.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            Text.pop();
            this.observeComponentCreation(((e, o) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
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
              o || Row.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            Row.pop();
            Row.pop();
            ListItem.pop()
          };
          e ? (() => {
            this.observeComponentCreation(o);
            ListItem.pop()
          })() : t()
        }
        this.observeComponentCreation(((e, o) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          ForEach.create();
          this.forEachUpdateFunction(e, this.additionFilters.options, ((e, o) => {
            const t = e;
            {
              const e = !0;
              const i = (t, i) => {
                ViewStackProcessor.StartGetAccessRecordingFor(t);
                ListItem.create(s, e);
                ListItem.height("100%");
                ListItem.backgroundColor(this.isAdditionBackgroundHover[o] ? this.additionBackgroundColorArr[o] : "#00FFFFFF");
                ListItem.onHover((e => {
                  Context.animateTo({ curve: FRICTION_CUBIC_BEZIER, duration: 250 }, (() => {
                    if (e) {
                      this.additionBackgroundColorArr[o] = {
                        id: -1,
                        type: 10001,
                        params: ["sys.color.ohos_id_color_hover"],
                        bundleName: "",
                        moduleName: ""
                      };
                      this.isAdditionBackgroundHover[o] = !0
                    } else this.isAdditionBackgroundHover[o] = !1
                  }))
                }));
                ListItem.onTouch((e => {
                  e.type === TouchType.Down ? Context.animateTo({ curve: SHARP_CUBIC_BEZIER, duration: 100 }, (() => {
                    this.additionBackgroundColorArr[o] = {
                      id: -1,
                      type: 10001,
                      params: ["sys.color.ohos_id_color_click_effect"],
                      bundleName: "",
                      moduleName: ""
                    };
                    this.isAdditionBackgroundHover[o] = !0
                  })) : e.type === TouchType.Up && Context.animateTo({
                    curve: SHARP_CUBIC_BEZIER,
                    duration: 100
                  }, (() => {
                    this.isAdditionBackgroundHover[o] = !1
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
                  this.additionItemClick(o)
                }));
                ListItem.tabIndex(0 == o ? this.multiFilters.length : -1);
                i || ListItem.pop();
                ViewStackProcessor.StopGetAccessRecording()
              };
              const r = () => {
                this.observeComponentCreation(i);
                this.observeComponentCreation(((e, i) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(e);
                  Text.create(t.toString());
                  Text.fontSize({
                    id: -1,
                    type: 10002,
                    params: ["sys.float.ohos_id_text_size_body3"],
                    bundleName: "",
                    moduleName: ""
                  });
                  Text.fontColor(this.additionColorArr[o]);
                  Text.fontWeight(this.additionFontWeightArr[o]);
                  Text.focusable(!0);
                  i || Text.pop();
                  ViewStackProcessor.StopGetAccessRecording()
                }));
                Text.pop();
                ListItem.pop()
              };
              const s = (e, r) => {
                i(e, r);
                this.updateFuncByElmtId.set(e, i);
                this.observeComponentCreation(((e, i) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(e);
                  Text.create(t.toString());
                  Text.fontSize({
                    id: -1,
                    type: 10002,
                    params: ["sys.float.ohos_id_text_size_body3"],
                    bundleName: "",
                    moduleName: ""
                  });
                  Text.fontColor(this.additionColorArr[o]);
                  Text.fontWeight(this.additionFontWeightArr[o]);
                  Text.focusable(!0);
                  i || Text.pop();
                  ViewStackProcessor.StopGetAccessRecording()
                }));
                Text.pop();
                ListItem.pop()
              };
              e ? (() => {
                this.observeComponentCreation(i);
                ListItem.pop()
              })() : r()
            }
          }), void 0,!0,!1);
          o || ForEach.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        ForEach.pop();
        List.pop();
        this.observeComponentCreation(((e, o) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          o ? ViewPU.create(new GradientMask(this, {
            x0: 0,
            y0: 20,
            x1: 16,
            y1: 20
          }, void 0, e)) : this.updateStateVarsOfChildByElmtId(e, {});
          ViewStackProcessor.StopGetAccessRecording()
        }));
        Stack.pop();
        this.observeComponentCreation(((e, o) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          o ? ViewPU.create(new GradientMask(this, {
            x0: 16,
            y0: 20,
            x1: 0,
            y1: 20
          }, void 0, e)) : this.updateStateVarsOfChildByElmtId(e, {});
          ViewStackProcessor.StopGetAccessRecording()
        }));
        Stack.pop()
      })) : If.branchId(1);
      o || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop()
  }

  FilterHeader(e = null) {
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Column.create();
      Column.padding({ top: 8 });
      Column.onVisibleAreaChange([0, 1], ((e, o) => {
        if (o > 0) {
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
            this.floatFilterBarPosition = 0;
            this.floatFilterBarHeight = 48
          }))
        }
      }));
      o || Column.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      this.filterType === FilterType.LIST_FILTER ? this.ifElseBranchUpdateFunction(0, (() => {
        this.ListFilter.bind(this)()
      })) : this.ifElseBranchUpdateFunction(1, (() => {
        this.MultiLineFilter.bind(this)()
      }));
      o || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop();
    this.AdditionFilterList.bind(this)();
    Column.pop()
  }

  FloatFilterHeader(e = null) {
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
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
      o || Column.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      this.filterType === FilterType.LIST_FILTER ? this.ifElseBranchUpdateFunction(0, (() => {
        this.ListFilter.bind(this)()
      })) : this.ifElseBranchUpdateFunction(1, (() => {
        this.MultiLineFilter.bind(this)()
      }));
      o || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop();
    this.AdditionFilterList.bind(this)();
    Column.pop()
  }

  FloatFilterBar(e = null) {
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Row.create();
      Row.width("100%");
      Row.height(this.floatFilterBarHeight);
      Row.padding({ left: 2, right: 2 });
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
      o || Row.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Column.create();
      Column.backgroundColor(this.isFloatArrowBgHover ? this.floatArrowBgColor : "#00FFFFFF");
      ViewStackProcessor.visualState("focused");
      Column.border({
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
      Column.width(28);
      ViewStackProcessor.visualState("normal");
      Column.border({
        radius: {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_corner_radius_clicked"],
          bundleName: "",
          moduleName: ""
        },
        width: 0
      });
      Column.width(24);
      ViewStackProcessor.visualState();
      Column.alignItems(HorizontalAlign.Center);
      Column.width("100%");
      Column.height(40);
      Column.onTouch((e => {
        e.type === TouchType.Down ? Context.animateTo({ curve: SHARP_CUBIC_BEZIER, duration: 100 }, (() => {
          this.floatArrowBgColor = {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_click_effect"],
            bundleName: "",
            moduleName: ""
          };
          this.isFloatArrowBgHover = !0
        })) : e.type === TouchType.Up && Context.animateTo({ curve: SHARP_CUBIC_BEZIER, duration: 100 }, (() => {
          this.isFloatArrowBgHover = !1
        }))
      }));
      Column.onClick((() => {
        Context.animateTo({ duration: 150, curve: SHARP_CUBIC_BEZIER }, (() => {
          this.isFloatBarShow = !1;
          this.isFloatBarShowWithoutAnimation = !1
        }));
        this.isFloatShowAllFilter = !0;
        this.isFloatShowAllFilterWithoutAnimation = !0;
        Context.animateTo({ curve: INTER_POLATING_SPRING, onFinish: () => {
          this.floatFilterBarPosition = 0
        } }, (() => {
          this.floatFilterPosition = 0;
          this.floatFilterBarPosition = this.filterDynamicHeight
        }))
      }));
      Column.onHover((e => {
        e ? Context.animateTo({ curve: FRICTION_CUBIC_BEZIER, duration: 250 }, (() => {
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
      o || Column.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Row.create();
      Row.height("100%");
      Row.alignItems(VerticalAlign.Center);
      o || Row.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      ForEach.create();
      this.forEachUpdateFunction(e, this.selectedFilters.slice(0, (this.colorRefresh, this.selectedFilters.length)), ((e, o) => {
        const t = e;
        this.observeComponentCreation(((e, i) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          If.create();
          0 != o && null != t.value ? this.ifElseBranchUpdateFunction(0, (() => {
            this.observeComponentCreation(((e, o) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              Text.create("/");
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
                params: ["sys.float.ohos_id_text_size_body3"],
                bundleName: "",
                moduleName: ""
              });
              o || Text.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            Text.pop()
          })) : If.branchId(1);
          i || If.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        If.pop();
        this.observeComponentCreation(((e, o) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Text.create(t.value);
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
            params: ["sys.float.ohos_id_text_size_body3"],
            bundleName: "",
            moduleName: ""
          });
          o || Text.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        Text.pop()
      }), void 0,!0,!1);
      o || ForEach.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    ForEach.pop();
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Row.create();
      Row.height(40);
      Row.margin({ left: 8 });
      Row.focusable(!0);
      o || Row.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
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
        params: ["sys.color.ohos_id_color_text_primary_activated"],
        bundleName: "",
        moduleName: ""
      });
      Image.focusable(!0);
      o || Image.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    Row.pop();
    Row.pop();
    Column.pop();
    Row.pop()
  }

  initialRender() {
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Stack.create({ alignContent: Alignment.Top });
      Stack.clip(!0);
      o || Stack.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.FloatFilterBar.bind(this)();
    this.FloatFilterHeader.bind(this)();
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Column.create();
      Column.zIndex(0);
      o || Column.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      List.create({ initialIndex: 0 });
      List.listDirection(Axis.Vertical);
      List.width("100%");
      List.height("100%");
      List.edgeEffect(EdgeEffect.Spring);
      List.onScroll(((e, o) => {
        if (this.isFloatShowAllFilterWithoutAnimation && o == ScrollState.Scroll) {
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
      o || List.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    {
      const e = !0;
      const o = (o, t) => {
        ViewStackProcessor.StartGetAccessRecordingFor(o);
        ListItem.create(i, e);
        ListItem.focusable(!0);
        t || ListItem.pop();
        ViewStackProcessor.StopGetAccessRecording()
      };
      const t = () => {
        this.observeComponentCreation(o);
        this.FilterHeader.bind(this)();
        ListItem.pop()
      };
      const i = (e, t) => {
        o(e, t);
        this.updateFuncByElmtId.set(e, o);
        this.FilterHeader.bind(this)();
        ListItem.pop()
      };
      e ? (() => {
        this.observeComponentCreation(o);
        ListItem.pop()
      })() : t()
    }
    {
      const e = !0;
      const o = (o, t) => {
        ViewStackProcessor.StartGetAccessRecordingFor(o);
        ListItem.create(i, e);
        ListItem.focusable(!0);
        t || ListItem.pop();
        ViewStackProcessor.StopGetAccessRecording()
      };
      const t = () => {
        this.observeComponentCreation(o);
        this.container.bind(this)();
        ListItem.pop()
      };
      const i = (e, t) => {
        o(e, t);
        this.updateFuncByElmtId.set(e, o);
        this.container.bind(this)();
        ListItem.pop()
      };
      e ? (() => {
        this.observeComponentCreation(o);
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