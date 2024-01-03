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

var __decorate = this && this.__decorate || function (t, e, o, i) {
  var r, s = arguments.length, n = s < 3 ? e : null === i ? i = Object.getOwnPropertyDescriptor(e, o) : i;
  if ("object" == typeof Reflect && "function" == typeof Reflect.decorate) n = Reflect.decorate(t, e, o, i); else for (var a = t.length - 1;a >= 0; a--) (r = t[a]) && (n = (s < 3 ? r(n) : s > 3 ? r(e, o, n) : r(e, o)) || n);
  return s > 3 && n && Object.defineProperty(e, o, n), n
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
const ARROW_DOWN = "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAMAAAADACAYAAABS3GwHAAAAIGNIUk0AAHomAACAhAAA+gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAAEZ0FNQQAAsY58+1GTAAAAAXNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAAlwSFlzAAAOxAAADsQBlSsOGwAAA8JJREFUeNrt3bFro3Ucx/E+eQK94SoiDjcEB3G4IcNtOhzSyQhtB+E2hyM0loMOHvgHmFEHRcFy1qclkyg4heR6iBwiODjcH6DQwSGFGxxEHFopjd9wPbjBSi9NQ578Xi8ISe7SwJN83mlDS7uwAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAsyubp4PZ2dm5nWXZalysD4fDw7i8H+dftlqth57qySmKohaP7ftx8Y041eIx3o/rv+R5/kmz2fxTAFPW6XSunZycFPFErJ5xk2+Pjo7e29zc/Nt8L2Z3d/fdeJy/iIsv/sd/D+J5aG1sbHxfluPJy/6EtNvt6tLSUjcuvvU/N6tXq9U3G43Gd3t7e/+Y8difYUev+l/F6coZN3khPhPcWl1dvd/r9R6X4ZgqZX9SarXaZpwtn+OmNxcXFx9sbW1dNeWxx//ZOW56pVKpdMpyXKUPIF5x7jzHzUVwueN/6kZ8zGsCmIL4evT6c36ICC53/E9fmF4XwOwSwSWO//SF6aoApuORCGZr/KcB/CaA6bwH6PtMMFvjD/sHBwc/C2AaB1CpfBwR/CqCmRn/yJ12u31chuMt/fcBut3u8crKysMI4VZcHXfEr/g+wcTGf7fVan1TlmPO5+GJ6/f7f0QE90UwE+P/vEzHnc/LEygC4086ABEYf/IBiMD4kw9ABMaffAAiMP7kAxCB8ScfgAiMP/kARGD8yQeQegTGL4BkIzB+ASQbgfELINkIjF8AyUZg/AJINgLjF0CyERi/AJKNwPgFkGwExi+AZCMwfgEkG4HxCyDZCIxfAMlGYPwCSDYC4xdAshEYvwCSjcD4BZBsBMYvgGQjMH4BzG0Ea2trP/R6vb/OulFRFB9kWfap8V+ezEMwnu3t7et5nv8YF69d4G5Gf1L07mAw+PrZ36Ycr/r1OLsXp5vGL4B5j2DkcOHJH/oY/RnXGxO4P+MXQOkimCTj9x6gVO8JjF8AIjB+AYjA+AUgAuMXgAiMXwAiMH4BiMD4BSAC4xdAuSN4O66+dMG7O86ybCPGf88jK4BSRdBoNDrVavXVuFof8272Y/zvrK+vdz2ik+NHIaasKIrlGPKHcXH5nB/yOE4f5Xm+3Ww2Dz2CApgLo5/4HA6HjfjSaDnO66fvEV6O0+9xGsS/PYpQ+oPB4Kdnf1IUAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAJ74F12fuBmTNpsqAAAAAElFTkSuQmCC";
const ARROW_UP = "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAMAAAADACAYAAABS3GwHAAAAIGNIUk0AAHomAACAhAAA+gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAAEZ0FNQQAAsY58+1GTAAAAAXNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAAlwSFlzAAAOxAAADsQBlSsOGwAAA7ZJREFUeNrt3TFonHUcx+Hem0sQ6SBSJEMomUSoFBEHhyAKYigpcSlo6fQOdxkyHTgIIkTqKi4uyWt4RxErmBDjVJpBUDcpHYp0CCSDQ5EMQfoG787fDdkMSnM5783/eeDl3qPXI33z/YQ7EpoLFwAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADqquESjEZRFDNZls33+/25uDsbx0wch3EcxPGo0WjsxJ/fzfP8d1dLAOdp+G/GzUcx8Lf/41/5rtfrfdJut3919QRQW2VZTseQi/iKf/0pn+LLqqo6y8vLh67m2ZlwCYZvbW3tlbi5F8drp3iaV5vN5uLCwsK9ra2tx66qAGphfX19Ll7u3I3TS0N4uhfifcGNiOB7EQigFuOPlzw/xOnFIT7tRREIINXxi0AAyY9fBAJIfvwiEEDy4xeBAJIfvwgEkPz4RSCA5McvAgHUfvy7cQxG+7wI/j9+Fmi04x/8pOeHVVV9e/wzPqurq5cmJiZuxemnp33ubrf71tLS0kOfLQGM3fgbjcad+ErdyvP84J/+vCzL2RjwV3H6ugi8BDp349/b27vZ6XT+POkxGxsbB/Pz8183m8034u5lL4cEcK7Gv7Ky8te/PXZ7e/soIvhGBAJIbvwiEEDy4xeBAJIfvwgEkPz4RSCA5McvAgEkP34RCCD58YtAAMmPXwQCSH78IhBA8uMXgQCSH78IBJD8+EUggOTHLwIBJD9+EQgg+fGLQADJj18EAkh+/CIQQPLjF4EAkh+/CBIOwPhFkGwAxi+CZAMwfhEkG4DxiyDZAIxfBMkGYPwiSDYA4xdBsgEURTETNz8Z/9hEcD2eZ33wfHW8DlntPuAs+9z4h2PwX7RXVXUtTn88xdPMTk1N3a7rNahVAGVZTsdLnxvGP14RxHV9XwAj0O12rxj/WEYwPfj9BgIYU8Z/9hEcHR09I4AzFp+gX4x/LCN4Eu8DdgUwgk9Q3OwY/9hFcCfP8ycCGI1WHIfGPzYR7Md7s05d/621+z7A5ubmH4uLi/fj9J04nj3hYV/s7++3jP/pHX+fYHJy8mrcffGEh+32+/332u32b7V9f1jXD3zw60WzLLsdX+nn4u7LcTyO8597vd5nrVZrx4SHpyiKd+PafhCnL8XxXBwPYvg78cb34+Nf9woAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAzf37i54rxOGvUjAAAAAElFTkSuQmCC";

export var FilterType;
!function(t){
  t[t.MULTI_LINE_FILTER=0] = "MULTI_LINE_FILTER";
  t[t.LIST_FILTER=1] = "LIST_FILTER"
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
  constructor(t) {
    this.value = t
  }
};
ObservedBoolean = __decorate([Observed], ObservedBoolean);

export { ObservedBoolean };
let ObservedNumber = class {
  constructor(t) {
    this.value = t
  }
};
ObservedNumber = __decorate([Observed], ObservedNumber);

class GradientMask extends ViewPU {
  constructor(t, e, o, i = -1) {
    super(t, o, i);
    this.x0 = void 0;
    this.y0 = void 0;
    this.x1 = void 0;
    this.y1 = void 0;
    this.settings = new RenderingContextSettings(!0);
    this.context2D = new CanvasRenderingContext2D(this.settings);
    this.setInitiallyProvidedValue(e)
  }

  setInitiallyProvidedValue(t) {
    void 0 !== t.x0 && (this.x0 = t.x0);
    void 0 !== t.y0 && (this.y0 = t.y0);
    void 0 !== t.x1 && (this.x1 = t.x1);
    void 0 !== t.y1 && (this.y1 = t.y1);
    void 0 !== t.settings && (this.settings = t.settings);
    void 0 !== t.context2D && (this.context2D = t.context2D)
  }

  updateStateVars(t) {
  }

  purgeVariableDependenciesOnElmtId(t) {
  }

  aboutToBeDeleted() {
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal()
  }

  initialRender() {
    this.observeComponentCreation2(((t, e) => {
      Column.create();
      Column.width(16);
      Column.height(40)
    }), Column);
    this.observeComponentCreation2(((t, e) => {
      Canvas.create(this.context2D);
      Canvas.width(16);
      Canvas.height(40);
      Canvas.onReady((() => {
        var t = this.context2D.createLinearGradient(this.x0, this.y0, this.x1, this.y1);
        t.addColorStop(0, "#ffffffff");
        t.addColorStop(1, "#00ffffff");
        this.context2D.fillStyle = t;
        this.context2D.fillRect(0, 0, 16, 40)
      }))
    }), Canvas);
    Canvas.pop();
    Column.pop()
  }

  rerender() {
    this.updateDirtyElements()
  }
}

class ListFilterRow extends ViewPU {
  constructor(t, e, o, i = -1) {
    super(t, o, i);
    this.__colorRow = new SynchedPropertyNesedObjectPU(e.colorRow, this, "colorRow");
    this.__fontWeightRow = new SynchedPropertyNesedObjectPU(e.fontWeightRow, this, "fontWeightRow");
    this.__backgroundColorRow = new SynchedPropertyNesedObjectPU(e.backgroundColorRow, this, "backgroundColorRow");
    this.__isBackgroundHoverRow = new SynchedPropertyNesedObjectPU(e.isBackgroundHoverRow, this, "isBackgroundHoverRow");
    this.filterRow = void 0;
    this.onItemClick = void 0;
    this.rowIndex = void 0;
    this.setInitiallyProvidedValue(e)
  }

  setInitiallyProvidedValue(t) {
    this.__colorRow.set(t.colorRow);
    this.__fontWeightRow.set(t.fontWeightRow);
    this.__backgroundColorRow.set(t.backgroundColorRow);
    this.__isBackgroundHoverRow.set(t.isBackgroundHoverRow);
    void 0 !== t.filterRow && (this.filterRow = t.filterRow);
    void 0 !== t.onItemClick && (this.onItemClick = t.onItemClick);
    void 0 !== t.rowIndex && (this.rowIndex = t.rowIndex)
  }

  updateStateVars(t) {
    this.__colorRow.set(t.colorRow);
    this.__fontWeightRow.set(t.fontWeightRow);
    this.__backgroundColorRow.set(t.backgroundColorRow);
    this.__isBackgroundHoverRow.set(t.isBackgroundHoverRow)
  }

  purgeVariableDependenciesOnElmtId(t) {
    this.__colorRow.purgeDependencyOnElmtId(t);
    this.__fontWeightRow.purgeDependencyOnElmtId(t);
    this.__backgroundColorRow.purgeDependencyOnElmtId(t);
    this.__isBackgroundHoverRow.purgeDependencyOnElmtId(t)
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
    this.observeComponentCreation2(((t, e) => {
      Stack.create({ alignContent: Alignment.End })
    }), Stack);
    this.observeComponentCreation2(((t, e) => {
      Stack.create({ alignContent: Alignment.Start })
    }), Stack);
    this.observeComponentCreation2(((t, e) => {
      List.create();
      List.listDirection(Axis.Horizontal);
      List.scrollBar(BarState.Off);
      List.width("100%");
      List.height(40);
      List.align(Alignment.Start)
    }), List);
    this.observeComponentCreation2(((t, e) => {
      ForEach.create();
      this.forEachUpdateFunction(t, this.filterRow.options, ((t, e) => {
        const o = t;
        this.observeComponentCreation2(((t, o) => {
          If.create();
          0 == e ? this.ifElseBranchUpdateFunction(0, (() => {
            {
              const t = !0;
              const e = (e, i) => {
                ViewStackProcessor.StartGetAccessRecordingFor(e);
                ListItem.create(o, t);
                ListItem.width({
                  id: -1,
                  type: 10002,
                  params: ["sys.float.ohos_id_max_padding_start"],
                  bundleName: "",
                  moduleName: ""
                });
                ListItem.height(40);
                i || ListItem.pop();
                ViewStackProcessor.StopGetAccessRecording()
              };
              const o = (t, o) => {
                e(t, o);
                this.updateFuncByElmtId.set(t, e);
                ListItem.pop()
              };
              this.observeComponentCreation(e);
              ListItem.pop()
            }
          })) : If.branchId(1)
        }), If);
        If.pop();
        {
          const t = !0;
          const i = (o, i) => {
            ViewStackProcessor.StartGetAccessRecordingFor(o);
            ListItem.create(r, t);
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
            ListItem.onHover((t => {
              Context.animateTo({ curve: FRICTION_CUBIC_BEZIER, duration: 250 }, (() => {
                if (t) {
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
            ListItem.onTouch((t => {
              t.type === TouchType.Down ? Context.animateTo({ curve: SHARP_CUBIC_BEZIER, duration: 100 }, (() => {
                this.backgroundColorRow[e] = {
                  id: -1,
                  type: 10001,
                  params: ["sys.color.ohos_id_color_click_effect"],
                  bundleName: "",
                  moduleName: ""
                };
                this.isBackgroundHoverRow[e] = !0
              })) : t.type === TouchType.Up && Context.animateTo({ curve: SHARP_CUBIC_BEZIER, duration: 100 }, (() => {
                this.isBackgroundHoverRow[e] = !1
              }))
            }));
            ListItem.margin({ left: 0 == e ? -8 : 0 });
            ListItem.tabIndex(0 == e ? this.rowIndex : -1);
            i || ListItem.pop();
            ViewStackProcessor.StopGetAccessRecording()
          };
          const r = (t, r) => {
            i(t, r);
            this.updateFuncByElmtId.set(t, i);
            this.observeComponentCreation2(((t, i) => {
              Text.create(o.toString());
              Text.fontSize({
                id: -1,
                type: 10002,
                params: ["sys.float.ohos_id_text_size_body3"],
                bundleName: "",
                moduleName: ""
              });
              Text.fontColor(this.colorRow[e]);
              Text.fontWeight(this.fontWeightRow[e]);
              Text.focusable(!0)
            }), Text);
            Text.pop();
            ListItem.pop()
          };
          this.observeComponentCreation(i);
          ListItem.pop()
        }
      }), void 0,!0,!1)
    }), ForEach);
    ForEach.pop();
    List.pop();
    this.observeComponentCreation2(((t, e) => {
      e ? ViewPU.create(new GradientMask(this, {
        x0: 0,
        y0: 20,
        x1: 16,
        y1: 20
      }, void 0, t)) : this.updateStateVarsOfChildByElmtId(t, {})
    }), null);
    Stack.pop();
    this.observeComponentCreation2(((t, e) => {
      e ? ViewPU.create(new GradientMask(this, {
        x0: 16,
        y0: 20,
        x1: 0,
        y1: 20
      }, void 0, t)) : this.updateStateVarsOfChildByElmtId(t, {})
    }), null);
    Stack.pop()
  }

  rerender() {
    this.updateDirtyElements()
  }
}

class MultiFilterRow extends ViewPU {
  constructor(t, e, o, i = -1) {
    super(t, o, i);
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
    this.lastFilterColumnWidth = 0;
    this.rowIndex = 0;
    this.setInitiallyProvidedValue(e)
  }

  setInitiallyProvidedValue(t) {
    this.__colorRow.set(t.colorRow);
    this.__fontWeightRow.set(t.fontWeightRow);
    this.__backgroundColorRow.set(t.backgroundColorRow);
    this.__isBackgroundHoverRow.set(t.isBackgroundHoverRow);
    this.__twoLineModeItemNumRow.set(t.twoLineModeItemNumRow);
    this.__twoLineModeItemNumRecordRow.set(t.twoLineModeItemNumRecordRow);
    this.__arrowShowStateRow.set(t.arrowShowStateRow);
    this.__isArrowIconDown.set(t.isArrowIconDown);
    void 0 !== t.filterRow && (this.filterRow = t.filterRow);
    void 0 !== t.onItemClick && (this.onItemClick = t.onItemClick);
    void 0 !== t.arrowBgColorRow && (this.arrowBgColorRow = t.arrowBgColorRow);
    void 0 !== t.isArrowBgHoverRow && (this.isArrowBgHoverRow = t.isArrowBgHoverRow);
    void 0 !== t.filterColumnWidth && (this.filterColumnWidth = t.filterColumnWidth);
    void 0 !== t.lastFilterColumnWidth && (this.lastFilterColumnWidth = t.lastFilterColumnWidth);
    void 0 !== t.rowIndex && (this.rowIndex = t.rowIndex)
  }

  updateStateVars(t) {
    this.__colorRow.set(t.colorRow);
    this.__fontWeightRow.set(t.fontWeightRow);
    this.__backgroundColorRow.set(t.backgroundColorRow);
    this.__isBackgroundHoverRow.set(t.isBackgroundHoverRow);
    this.__twoLineModeItemNumRow.set(t.twoLineModeItemNumRow);
    this.__twoLineModeItemNumRecordRow.set(t.twoLineModeItemNumRecordRow);
    this.__arrowShowStateRow.set(t.arrowShowStateRow);
    this.__isArrowIconDown.set(t.isArrowIconDown)
  }

  purgeVariableDependenciesOnElmtId(t) {
    this.__colorRow.purgeDependencyOnElmtId(t);
    this.__fontWeightRow.purgeDependencyOnElmtId(t);
    this.__backgroundColorRow.purgeDependencyOnElmtId(t);
    this.__isBackgroundHoverRow.purgeDependencyOnElmtId(t);
    this.__twoLineModeItemNumRow.purgeDependencyOnElmtId(t);
    this.__twoLineModeItemNumRecordRow.purgeDependencyOnElmtId(t);
    this.__arrowShowStateRow.purgeDependencyOnElmtId(t);
    this.__isArrowIconDown.purgeDependencyOnElmtId(t);
    this.__arrowBgColorRow.purgeDependencyOnElmtId(t);
    this.__isArrowBgHoverRow.purgeDependencyOnElmtId(t)
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

  set arrowBgColorRow(t) {
    this.__arrowBgColorRow.set(t)
  }

  get isArrowBgHoverRow() {
    return this.__isArrowBgHoverRow.get()
  }

  set isArrowBgHoverRow(t) {
    this.__isArrowBgHoverRow.set(t)
  }

  calcMultiFilterRowItemNum() {
    var t = this.filterColumnWidth - vp2px(24);
    var e = 0;
    var o = 1;
    for (var i = 0;i < this.filterRow.options.length; i++) {
      let r = this.filterRow.options[i];
      let s = measure.measureText({ textContent: r, fontSize: 12 });
      if (0 !== i) {
        s += vp2px(16);
        if (t - s >= 0) {
          t -= s;
          e += 1
        } else {
          if (0 === e) {
            e++;
            t = 0
          }
          if (1 !== o) break;
          o += 1;
          t = this.filterColumnWidth - vp2px(24) - vp2px(24);
          i--
        }
      }
    }
    return e
  }

  DownAndUpArrow(t = null) {
    this.observeComponentCreation2(((t, e) => {
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
      Row.onHover((t => {
        Context.animateTo({ curve: FRICTION_CUBIC_BEZIER, duration: 250 }, (() => {
          if (t) {
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
      Row.onTouch((t => {
        t.type === TouchType.Down ? Context.animateTo({ curve: SHARP_CUBIC_BEZIER, duration: 100 }, (() => {
          this.arrowBgColorRow = {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_click_effect"],
            bundleName: "",
            moduleName: ""
          };
          this.isArrowBgHoverRow = !0
        })) : t.type === TouchType.Up && Context.animateTo({ curve: SHARP_CUBIC_BEZIER, duration: 100 }, (() => {
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
      }))
    }), Row);
    this.observeComponentCreation2(((t, e) => {
      Image.create(this.isArrowIconDown.value ? ARROW_DOWN : ARROW_UP);
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
      Image.tabIndex(-1)
    }), Image);
    Row.pop()
  }

  initialRender() {
    this.observeComponentCreation2(((t, e) => {
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
      })
    }), Row);
    this.observeComponentCreation2(((t, e) => {
      If.create();
      this.filterRow.options && this.filterRow.options.length > 0 ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation2(((t, e) => {
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
          Text.onHover((t => {
            Context.animateTo({ curve: FRICTION_CUBIC_BEZIER, duration: 250 }, (() => {
              if (t) {
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
          Text.onTouch((t => {
            t.type === TouchType.Down ? Context.animateTo({ curve: SHARP_CUBIC_BEZIER, duration: 100 }, (() => {
              this.backgroundColorRow[0] = {
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_click_effect"],
                bundleName: "",
                moduleName: ""
              };
              this.isBackgroundHoverRow[0] = !0
            })) : t.type === TouchType.Up && Context.animateTo({ curve: SHARP_CUBIC_BEZIER, duration: 100 }, (() => {
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
          Text.tabIndex(this.rowIndex)
        }), Text);
        Text.pop()
      })) : If.branchId(1)
    }), If);
    If.pop();
    this.observeComponentCreation2(((t, e) => {
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
      Row.onAreaChange(((t, e) => {
        this.filterColumnWidth = vp2px(parseInt(e.width.toString(), 0));
        if (0 === this.twoLineModeItemNumRow.value) {
          var o = this.calcMultiFilterRowItemNum();
          this.twoLineModeItemNumRow.value = o;
          this.twoLineModeItemNumRecordRow.value = o;
          o < this.filterRow.options.length - 1 ? this.arrowShowStateRow.value = !0 : this.arrowShowStateRow.value = !1
        } else if (this.filterColumnWidth !== this.lastFilterColumnWidth) {
          if ((o = this.calcMultiFilterRowItemNum()) < this.filterRow.options.length - 1) {
            if (!this.arrowShowStateRow.value || this.isArrowIconDown.value) {
              this.arrowShowStateRow.value = !0;
              this.isArrowIconDown.value = !0;
              this.twoLineModeItemNumRow.value = o
            }
          } else {
            this.arrowShowStateRow.value = !1;
            this.isArrowIconDown.value = !1;
            this.twoLineModeItemNumRow.value = o
          }
          this.twoLineModeItemNumRecordRow.value = o
        }
        this.lastFilterColumnWidth = this.filterColumnWidth
      }))
    }), Row);
    this.observeComponentCreation2(((t, e) => {
      Flex.create({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap });
      Flex.alignSelf(ItemAlign.Stretch)
    }), Flex);
    this.observeComponentCreation2(((t, e) => {
      ForEach.create();
      this.forEachUpdateFunction(t, this.filterRow.options.slice(0, this.twoLineModeItemNumRow.value + 1), ((t, e) => {
        const o = t;
        this.observeComponentCreation2(((t, i) => {
          If.create();
          e > 0 ? this.ifElseBranchUpdateFunction(0, (() => {
            this.observeComponentCreation2(((t, i) => {
              Text.create(o.toString());
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
              Text.onHover((t => {
                Context.animateTo({ curve: FRICTION_CUBIC_BEZIER, duration: 250 }, (() => {
                  if (t) {
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
              Text.onTouch((t => {
                t.type === TouchType.Down ? Context.animateTo({ curve: SHARP_CUBIC_BEZIER, duration: 100 }, (() => {
                  this.backgroundColorRow[e] = {
                    id: -1,
                    type: 10001,
                    params: ["sys.color.ohos_id_color_click_effect"],
                    bundleName: "",
                    moduleName: ""
                  };
                  this.isBackgroundHoverRow[e] = !0
                })) : t.type === TouchType.Up && Context.animateTo({
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
              Text.tabIndex(-1)
            }), Text);
            Text.pop()
          })) : If.branchId(1)
        }), If);
        If.pop()
      }), void 0,!0,!1)
    }), ForEach);
    ForEach.pop();
    this.observeComponentCreation2(((t, e) => {
      If.create();
      this.arrowShowStateRow.value ? this.ifElseBranchUpdateFunction(0, (() => {
        this.DownAndUpArrow.bind(this)()
      })) : If.branchId(1)
    }), If);
    If.pop();
    Flex.pop();
    Row.pop();
    Row.pop()
  }

  rerender() {
    this.updateDirtyElements()
  }
}

export class Filter extends ViewPU {
  constructor(t, e, o, i = -1) {
    super(t, o, i);
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
    this.filterStackHeight = 0;
    this.__twoLineModeItemNum = new ObservedPropertyObjectPU(null, this, "twoLineModeItemNum");
    this.__twoLineModeItemNumRecord = new ObservedPropertyObjectPU(null, this, "twoLineModeItemNumRecord");
    this.__downArrowShowState = new ObservedPropertyObjectPU(null, this, "downArrowShowState");
    this.__floatFilterBarText = new ObservedPropertySimplePU("", this, "floatFilterBarText");
    this.setInitiallyProvidedValue(e)
  }

  setInitiallyProvidedValue(t) {
    void 0 !== t.container && (this.container = t.container);
    void 0 === t.multiFilters && this.__multiFilters.set([]);
    void 0 === t.additionFilters && this.__additionFilters.set(null);
    void 0 !== t.onFilterChanged && (this.onFilterChanged = t.onFilterChanged);
    void 0 === t.filterType && this.__filterType.set(FilterType.LIST_FILTER);
    void 0 !== t.selectedFilters && (this.selectedFilters = t.selectedFilters);
    void 0 !== t.colorArr && (this.colorArr = t.colorArr);
    void 0 !== t.fontWeightArr && (this.fontWeightArr = t.fontWeightArr);
    void 0 !== t.backgroundColorArr && (this.backgroundColorArr = t.backgroundColorArr);
    void 0 !== t.isBackgroundHover && (this.isBackgroundHover = t.isBackgroundHover);
    void 0 !== t.floatArrowBgColor && (this.floatArrowBgColor = t.floatArrowBgColor);
    void 0 !== t.isFloatArrowBgHover && (this.isFloatArrowBgHover = t.isFloatArrowBgHover);
    void 0 !== t.isArrowIconDownArr && (this.isArrowIconDownArr = t.isArrowIconDownArr);
    void 0 !== t.additionColorArr && (this.additionColorArr = t.additionColorArr);
    void 0 !== t.additionFontWeightArr && (this.additionFontWeightArr = t.additionFontWeightArr);
    void 0 !== t.additionBackgroundColorArr && (this.additionBackgroundColorArr = t.additionBackgroundColorArr);
    void 0 !== t.isAdditionBackgroundHover && (this.isAdditionBackgroundHover = t.isAdditionBackgroundHover);
    void 0 !== t.colorRefresh && (this.colorRefresh = t.colorRefresh);
    void 0 !== t.isFloatBarShow && (this.isFloatBarShow = t.isFloatBarShow);
    void 0 !== t.isFloatBarShowWithoutAnimation && (this.isFloatBarShowWithoutAnimation = t.isFloatBarShowWithoutAnimation);
    void 0 !== t.isFloatShowAllFilter && (this.isFloatShowAllFilter = t.isFloatShowAllFilter);
    void 0 !== t.isFloatShowAllFilterWithoutAnimation && (this.isFloatShowAllFilterWithoutAnimation = t.isFloatShowAllFilterWithoutAnimation);
    void 0 !== t.floatFilterPosition && (this.floatFilterPosition = t.floatFilterPosition);
    void 0 !== t.floatFilterBarHeight && (this.floatFilterBarHeight = t.floatFilterBarHeight);
    void 0 !== t.floatFilterBarPosition && (this.floatFilterBarPosition = t.floatFilterBarPosition);
    void 0 !== t.filterDynamicHeight && (this.filterDynamicHeight = t.filterDynamicHeight);
    void 0 !== t.filterStackHeight && (this.filterStackHeight = t.filterStackHeight);
    void 0 !== t.twoLineModeItemNum && (this.twoLineModeItemNum = t.twoLineModeItemNum);
    void 0 !== t.twoLineModeItemNumRecord && (this.twoLineModeItemNumRecord = t.twoLineModeItemNumRecord);
    void 0 !== t.downArrowShowState && (this.downArrowShowState = t.downArrowShowState);
    void 0 !== t.floatFilterBarText && (this.floatFilterBarText = t.floatFilterBarText)
  }

  updateStateVars(t) {
    this.__multiFilters.reset(t.multiFilters);
    this.__additionFilters.reset(t.additionFilters);
    this.__filterType.reset(t.filterType)
  }

  purgeVariableDependenciesOnElmtId(t) {
    this.__multiFilters.purgeDependencyOnElmtId(t);
    this.__additionFilters.purgeDependencyOnElmtId(t);
    this.__filterType.purgeDependencyOnElmtId(t);
    this.__colorArr.purgeDependencyOnElmtId(t);
    this.__fontWeightArr.purgeDependencyOnElmtId(t);
    this.__backgroundColorArr.purgeDependencyOnElmtId(t);
    this.__isBackgroundHover.purgeDependencyOnElmtId(t);
    this.__floatArrowBgColor.purgeDependencyOnElmtId(t);
    this.__isFloatArrowBgHover.purgeDependencyOnElmtId(t);
    this.__isArrowIconDownArr.purgeDependencyOnElmtId(t);
    this.__additionColorArr.purgeDependencyOnElmtId(t);
    this.__additionFontWeightArr.purgeDependencyOnElmtId(t);
    this.__additionBackgroundColorArr.purgeDependencyOnElmtId(t);
    this.__isAdditionBackgroundHover.purgeDependencyOnElmtId(t);
    this.__colorRefresh.purgeDependencyOnElmtId(t);
    this.__isFloatBarShow.purgeDependencyOnElmtId(t);
    this.__isFloatShowAllFilter.purgeDependencyOnElmtId(t);
    this.__floatFilterPosition.purgeDependencyOnElmtId(t);
    this.__floatFilterBarHeight.purgeDependencyOnElmtId(t);
    this.__floatFilterBarPosition.purgeDependencyOnElmtId(t);
    this.__twoLineModeItemNum.purgeDependencyOnElmtId(t);
    this.__twoLineModeItemNumRecord.purgeDependencyOnElmtId(t);
    this.__downArrowShowState.purgeDependencyOnElmtId(t);
    this.__floatFilterBarText.purgeDependencyOnElmtId(t)
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
    this.__floatFilterBarText.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal()
  }

  get multiFilters() {
    return this.__multiFilters.get()
  }

  set multiFilters(t) {
    this.__multiFilters.set(t)
  }

  get additionFilters() {
    return this.__additionFilters.get()
  }

  set additionFilters(t) {
    this.__additionFilters.set(t)
  }

  get filterType() {
    return this.__filterType.get()
  }

  set filterType(t) {
    this.__filterType.set(t)
  }

  get colorArr() {
    return this.__colorArr.get()
  }

  set colorArr(t) {
    this.__colorArr.set(t)
  }

  get fontWeightArr() {
    return this.__fontWeightArr.get()
  }

  set fontWeightArr(t) {
    this.__fontWeightArr.set(t)
  }

  get backgroundColorArr() {
    return this.__backgroundColorArr.get()
  }

  set backgroundColorArr(t) {
    this.__backgroundColorArr.set(t)
  }

  get isBackgroundHover() {
    return this.__isBackgroundHover.get()
  }

  set isBackgroundHover(t) {
    this.__isBackgroundHover.set(t)
  }

  get floatArrowBgColor() {
    return this.__floatArrowBgColor.get()
  }

  set floatArrowBgColor(t) {
    this.__floatArrowBgColor.set(t)
  }

  get isFloatArrowBgHover() {
    return this.__isFloatArrowBgHover.get()
  }

  set isFloatArrowBgHover(t) {
    this.__isFloatArrowBgHover.set(t)
  }

  get isArrowIconDownArr() {
    return this.__isArrowIconDownArr.get()
  }

  set isArrowIconDownArr(t) {
    this.__isArrowIconDownArr.set(t)
  }

  get additionColorArr() {
    return this.__additionColorArr.get()
  }

  set additionColorArr(t) {
    this.__additionColorArr.set(t)
  }

  get additionFontWeightArr() {
    return this.__additionFontWeightArr.get()
  }

  set additionFontWeightArr(t) {
    this.__additionFontWeightArr.set(t)
  }

  get additionBackgroundColorArr() {
    return this.__additionBackgroundColorArr.get()
  }

  set additionBackgroundColorArr(t) {
    this.__additionBackgroundColorArr.set(t)
  }

  get isAdditionBackgroundHover() {
    return this.__isAdditionBackgroundHover.get()
  }

  set isAdditionBackgroundHover(t) {
    this.__isAdditionBackgroundHover.set(t)
  }

  get colorRefresh() {
    return this.__colorRefresh.get()
  }

  set colorRefresh(t) {
    this.__colorRefresh.set(t)
  }

  get isFloatBarShow() {
    return this.__isFloatBarShow.get()
  }

  set isFloatBarShow(t) {
    this.__isFloatBarShow.set(t)
  }

  get isFloatShowAllFilter() {
    return this.__isFloatShowAllFilter.get()
  }

  set isFloatShowAllFilter(t) {
    this.__isFloatShowAllFilter.set(t)
  }

  get floatFilterPosition() {
    return this.__floatFilterPosition.get()
  }

  set floatFilterPosition(t) {
    this.__floatFilterPosition.set(t)
  }

  get floatFilterBarHeight() {
    return this.__floatFilterBarHeight.get()
  }

  set floatFilterBarHeight(t) {
    this.__floatFilterBarHeight.set(t)
  }

  get floatFilterBarPosition() {
    return this.__floatFilterBarPosition.get()
  }

  set floatFilterBarPosition(t) {
    this.__floatFilterBarPosition.set(t)
  }

  get twoLineModeItemNum() {
    return this.__twoLineModeItemNum.get()
  }

  set twoLineModeItemNum(t) {
    this.__twoLineModeItemNum.set(t)
  }

  get twoLineModeItemNumRecord() {
    return this.__twoLineModeItemNumRecord.get()
  }

  set twoLineModeItemNumRecord(t) {
    this.__twoLineModeItemNumRecord.set(t)
  }

  get downArrowShowState() {
    return this.__downArrowShowState.get()
  }

  set downArrowShowState(t) {
    this.__downArrowShowState.set(t)
  }

  get floatFilterBarText() {
    return this.__floatFilterBarText.get()
  }

  set floatFilterBarText(t) {
    this.__floatFilterBarText.set(t)
  }

  textColor(t, e) {
    return this.selectedFilters.length > t && this.selectedFilters[t].index === e ? {
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

  filterItemClick(t, e) {
    let o = this.multiFilters[t].options[e];
    if (e != this.selectedFilters[t].index) {
      this.colorArr[t][e] = {
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_text_primary_activated"],
        bundleName: "",
        moduleName: ""
      };
      this.colorArr[t][this.selectedFilters[t].index] = {
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_text_primary"],
        bundleName: "",
        moduleName: ""
      };
      this.fontWeightArr[t][e] = FontWeight.Medium;
      this.fontWeightArr[t][this.selectedFilters[t].index] = FontWeight.Regular;
      this.colorRefresh = !this.colorRefresh;
      this.selectedFilters[t].value = o;
      this.selectedFilters[t].index = e;
      this.onFilterChanged && this.onFilterChanged(this.selectedFilters)
    }
    this.refreshFloatFilterBarText()
  }

  refreshFloatFilterBarText() {
    this.floatFilterBarText = "";
    for (let t = 0;t < this.selectedFilters.length; t++) null !== this.selectedFilters[t].value && (this.floatFilterBarText += 0 === t ? this.selectedFilters[t].value : "/" + this.selectedFilters[t].value)
  }

  initParams() {
    if (!this.selectedFilters) {
      this.selectedFilters = [];
      for (let e of this.multiFilters) {
        var t = { name: e.name, index: -1, value: null };
        if (e.options.length > 0) {
          t.index = 0;
          t.value = e.options[0]
        }
        this.selectedFilters.push(t)
      }
      if (this.additionFilters && this.additionFilters.name) {
        t = { name: this.additionFilters.name, index: -1, value: null };
        this.selectedFilters.push(t)
      }
      this.refreshFloatFilterBarText()
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
      for (let t of this.multiFilters) {
        var e = new ResourceArray;
        var o = new FontWeightArray;
        var i = new ResourceArray;
        var r = new BooleanArray;
        for (let r of t.options.keys()) {
          if (0 === r) {
            e.push({
              id: -1,
              type: 10001,
              params: ["sys.color.ohos_id_color_text_primary_activated"],
              bundleName: "",
              moduleName: ""
            });
            o.push(FontWeight.Medium)
          } else {
            e.push({
              id: -1,
              type: 10001,
              params: ["sys.color.ohos_id_color_text_primary"],
              bundleName: "",
              moduleName: ""
            });
            o.push(FontWeight.Regular)
          }
          i.push({
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_hover"],
            bundleName: "",
            moduleName: ""
          })
        }
        this.colorArr.push(e);
        this.fontWeightArr.push(o);
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
      for (let t = 0;t < this.additionFilters.options.length; t++) {
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
      for (let t = 0;t < this.multiFilters.length; t++) {
        this.twoLineModeItemNum.push(new ObservedNumber(0));
        this.twoLineModeItemNumRecord.push(new ObservedNumber(0));
        this.downArrowShowState.push(new ObservedBoolean(!1))
      }
    }
  }

  ListFilter(t = null) {
    this.observeComponentCreation2(((t, e) => {
      Column.create();
      Column.width("100%");
      Column.align(Alignment.Start);
      Column.onAreaChange(((t, e) => {
        if (!this.isFloatShowAllFilterWithoutAnimation && !this.isFloatBarShowWithoutAnimation) {
          null != this.additionFilters ? this.filterDynamicHeight = parseInt(e.height.toString(), 0) + 40 + 8 : this.filterDynamicHeight = parseInt(e.height.toString(), 0) + 8;
          this.filterDynamicHeight > .8 * this.filterStackHeight && (this.filterDynamicHeight = .8 * this.filterStackHeight);
          this.floatFilterPosition = -this.filterDynamicHeight
        }
      }))
    }), Column);
    this.observeComponentCreation2(((t, e) => {
      ForEach.create();
      this.forEachUpdateFunction(t, this.multiFilters, ((t, e) => {
        const o = t;
        this.observeComponentCreation2(((t, i) => {
          i ? ViewPU.create(new ListFilterRow(this, {
            colorRow: this.colorArr[e],
            fontWeightRow: this.fontWeightArr[e],
            backgroundColorRow: this.backgroundColorArr[e],
            isBackgroundHoverRow: this.isBackgroundHover[e],
            filterRow: o,
            onItemClick: t => {
              this.filterItemClick(e, t)
            },
            rowIndex: e
          }, void 0, t)) : this.updateStateVarsOfChildByElmtId(t, {
            colorRow: this.colorArr[e],
            fontWeightRow: this.fontWeightArr[e],
            backgroundColorRow: this.backgroundColorArr[e],
            isBackgroundHoverRow: this.isBackgroundHover[e]
          })
        }), null)
      }), void 0,!0,!1)
    }), ForEach);
    ForEach.pop();
    Column.pop()
  }

  MultiLineFilter(t = null) {
    this.observeComponentCreation2(((t, e) => {
      Column.create();
      Column.width("100%");
      Column.onAreaChange(((t, e) => {
        console.log("filter height:" + parseInt(e.height.toString(), 0));
        null != this.additionFilters ? this.filterDynamicHeight = parseInt(e.height.toString(), 0) + 40 + 8 : this.filterDynamicHeight = parseInt(e.height.toString(), 0) + 8;
        this.filterDynamicHeight > .8 * this.filterStackHeight && (this.filterDynamicHeight = .8 * this.filterStackHeight);
        this.isFloatBarShowWithoutAnimation || this.isFloatShowAllFilterWithoutAnimation || (this.floatFilterPosition = -this.filterDynamicHeight)
      }))
    }), Column);
    this.observeComponentCreation2(((t, e) => {
      ForEach.create();
      this.forEachUpdateFunction(t, this.multiFilters, ((t, e) => {
        const o = t;
        this.observeComponentCreation2(((t, i) => {
          i ? ViewPU.create(new MultiFilterRow(this, {
            colorRow: this.colorArr[e],
            fontWeightRow: this.fontWeightArr[e],
            backgroundColorRow: this.backgroundColorArr[e],
            isBackgroundHoverRow: this.isBackgroundHover[e],
            arrowShowStateRow: this.downArrowShowState[e],
            twoLineModeItemNumRow: this.twoLineModeItemNum[e],
            twoLineModeItemNumRecordRow: this.twoLineModeItemNumRecord[e],
            isArrowIconDown: this.isArrowIconDownArr[e],
            filterRow: o,
            onItemClick: t => {
              this.filterItemClick(e, t)
            },
            rowIndex: e
          }, void 0, t)) : this.updateStateVarsOfChildByElmtId(t, {
            colorRow: this.colorArr[e],
            fontWeightRow: this.fontWeightArr[e],
            backgroundColorRow: this.backgroundColorArr[e],
            isBackgroundHoverRow: this.isBackgroundHover[e],
            arrowShowStateRow: this.downArrowShowState[e],
            twoLineModeItemNumRow: this.twoLineModeItemNum[e],
            twoLineModeItemNumRecordRow: this.twoLineModeItemNumRecord[e],
            isArrowIconDown: this.isArrowIconDownArr[e]
          })
        }), null)
      }), void 0,!0,!1)
    }), ForEach);
    ForEach.pop();
    Column.pop()
  }

  additionItemClick(t) {
    let e = this.multiFilters.length;
    if (this.selectedFilters[e].index != t) if (-1 === this.selectedFilters[e].index) {
      this.additionColorArr[t] = {
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_text_primary_activated"],
        bundleName: "",
        moduleName: ""
      };
      this.additionFontWeightArr[t] = FontWeight.Medium;
      this.selectedFilters[e].value = this.additionFilters.options[t];
      this.selectedFilters[e].index = t
    } else {
      let o = this.selectedFilters[e].index;
      this.additionColorArr[o] = {
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_text_primary"],
        bundleName: "",
        moduleName: ""
      };
      this.additionColorArr[t] = {
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_text_primary_activated"],
        bundleName: "",
        moduleName: ""
      };
      this.additionFontWeightArr[o] = FontWeight.Regular;
      this.additionFontWeightArr[t] = FontWeight.Medium;
      this.selectedFilters[e].value = this.additionFilters.options[t];
      this.selectedFilters[e].index = t
    } else {
      this.additionColorArr[t] = {
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_text_primary"],
        bundleName: "",
        moduleName: ""
      };
      this.additionFontWeightArr[t] = FontWeight.Regular;
      this.selectedFilters[e].value = null;
      this.selectedFilters[e].index = -1
    }
    this.onFilterChanged && this.onFilterChanged(this.selectedFilters);
    this.colorRefresh = !this.colorRefresh;
    this.refreshFloatFilterBarText()
  }

  AdditionFilterList(t = null) {
    this.observeComponentCreation2(((t, e) => {
      If.create();
      this.additionFilters && this.additionFilters.name && this.additionFilters.options && 0 != this.additionFilters.options.length ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation2(((t, e) => {
          Stack.create({ alignContent: Alignment.End })
        }), Stack);
        this.observeComponentCreation2(((t, e) => {
          Stack.create({ alignContent: Alignment.Start })
        }), Stack);
        this.observeComponentCreation2(((t, e) => {
          List.create();
          List.listDirection(Axis.Horizontal);
          List.scrollBar(BarState.Off);
          List.width("100%");
          List.height(40)
        }), List);
        {
          const t = !0;
          const e = (e, i) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            ListItem.create(o, t);
            ListItem.height("100%");
            ListItem.margin({ left: -8 });
            i || ListItem.pop();
            ViewStackProcessor.StopGetAccessRecording()
          };
          const o = (t, o) => {
            e(t, o);
            this.updateFuncByElmtId.set(t, e);
            this.observeComponentCreation2(((t, e) => {
              Row.create()
            }), Row);
            this.observeComponentCreation2(((t, e) => {
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
              })
            }), Text);
            Text.pop();
            this.observeComponentCreation2(((t, e) => {
              Row.create();
              Row.width(1);
              Row.height(16);
              Row.backgroundColor({
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_list_separator"],
                bundleName: "",
                moduleName: ""
              })
            }), Row);
            Row.pop();
            Row.pop();
            ListItem.pop()
          };
          this.observeComponentCreation(e);
          ListItem.pop()
        }
        this.observeComponentCreation2(((t, e) => {
          ForEach.create();
          this.forEachUpdateFunction(t, this.additionFilters.options, ((t, e) => {
            const o = t;
            {
              const t = !0;
              const i = (o, i) => {
                ViewStackProcessor.StartGetAccessRecordingFor(o);
                ListItem.create(r, t);
                ListItem.height("100%");
                ListItem.backgroundColor(this.isAdditionBackgroundHover[e] ? this.additionBackgroundColorArr[e] : "#00FFFFFF");
                ListItem.onHover((t => {
                  Context.animateTo({ curve: FRICTION_CUBIC_BEZIER, duration: 250 }, (() => {
                    if (t) {
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
                ListItem.onTouch((t => {
                  t.type === TouchType.Down ? Context.animateTo({ curve: SHARP_CUBIC_BEZIER, duration: 100 }, (() => {
                    this.additionBackgroundColorArr[e] = {
                      id: -1,
                      type: 10001,
                      params: ["sys.color.ohos_id_color_click_effect"],
                      bundleName: "",
                      moduleName: ""
                    };
                    this.isAdditionBackgroundHover[e] = !0
                  })) : t.type === TouchType.Up && Context.animateTo({
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
                ListItem.tabIndex(0 == e ? this.multiFilters.length : -1);
                i || ListItem.pop();
                ViewStackProcessor.StopGetAccessRecording()
              };
              const r = (t, r) => {
                i(t, r);
                this.updateFuncByElmtId.set(t, i);
                this.observeComponentCreation2(((t, i) => {
                  Text.create(o.toString());
                  Text.fontSize({
                    id: -1,
                    type: 10002,
                    params: ["sys.float.ohos_id_text_size_body3"],
                    bundleName: "",
                    moduleName: ""
                  });
                  Text.fontColor(this.additionColorArr[e]);
                  Text.fontWeight(this.additionFontWeightArr[e]);
                  Text.focusable(!0)
                }), Text);
                Text.pop();
                ListItem.pop()
              };
              this.observeComponentCreation(i);
              ListItem.pop()
            }
          }), void 0,!0,!1)
        }), ForEach);
        ForEach.pop();
        List.pop();
        this.observeComponentCreation2(((t, e) => {
          e ? ViewPU.create(new GradientMask(this, {
            x0: 0,
            y0: 20,
            x1: 16,
            y1: 20
          }, void 0, t)) : this.updateStateVarsOfChildByElmtId(t, {})
        }), null);
        Stack.pop();
        this.observeComponentCreation2(((t, e) => {
          e ? ViewPU.create(new GradientMask(this, {
            x0: 16,
            y0: 20,
            x1: 0,
            y1: 20
          }, void 0, t)) : this.updateStateVarsOfChildByElmtId(t, {})
        }), null);
        Stack.pop()
      })) : If.branchId(1)
    }), If);
    If.pop()
  }

  FilterHeader(t = null) {
    this.observeComponentCreation2(((t, e) => {
      Column.create();
      Column.padding({ top: 8 });
      Column.onVisibleAreaChange([0, 1], ((t, e) => {
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
            this.floatFilterBarPosition = 0;
            this.floatFilterBarHeight = 48
          }))
        }
      }))
    }), Column);
    this.observeComponentCreation2(((t, e) => {
      If.create();
      this.filterType === FilterType.LIST_FILTER ? this.ifElseBranchUpdateFunction(0, (() => {
        this.ListFilter.bind(this)()
      })) : this.ifElseBranchUpdateFunction(1, (() => {
        this.MultiLineFilter.bind(this)()
      }))
    }), If);
    If.pop();
    this.AdditionFilterList.bind(this)();
    Column.pop()
  }

  FloatFilterHeader(t = null) {
    this.observeComponentCreation2(((t, e) => {
      Column.create();
      Column.padding({ top: 8 });
      Column.width("100%");
      Column.constraintSize({ maxHeight: "80%" });
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
      Column.zIndex(2)
    }), Column);
    this.observeComponentCreation2(((t, e) => {
      Scroll.create()
    }), Scroll);
    this.observeComponentCreation2(((t, e) => {
      Column.create()
    }), Column);
    this.observeComponentCreation2(((t, e) => {
      If.create();
      this.filterType === FilterType.LIST_FILTER ? this.ifElseBranchUpdateFunction(0, (() => {
        this.ListFilter.bind(this)()
      })) : this.ifElseBranchUpdateFunction(1, (() => {
        this.MultiLineFilter.bind(this)()
      }))
    }), If);
    If.pop();
    this.AdditionFilterList.bind(this)();
    Column.pop();
    Scroll.pop();
    Column.pop()
  }

  FloatFilterBar(t = null) {
    this.observeComponentCreation2(((t, e) => {
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
      Row.zIndex(1)
    }), Row);
    this.observeComponentCreation2(((t, e) => {
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
      Column.onTouch((t => {
        t.type === TouchType.Down ? Context.animateTo({ curve: SHARP_CUBIC_BEZIER, duration: 100 }, (() => {
          this.floatArrowBgColor = {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_click_effect"],
            bundleName: "",
            moduleName: ""
          };
          this.isFloatArrowBgHover = !0
        })) : t.type === TouchType.Up && Context.animateTo({ curve: SHARP_CUBIC_BEZIER, duration: 100 }, (() => {
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
      Column.onHover((t => {
        t ? Context.animateTo({ curve: FRICTION_CUBIC_BEZIER, duration: 250 }, (() => {
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
      }))
    }), Column);
    this.observeComponentCreation2(((t, e) => {
      Row.create();
      Row.height("100%");
      Row.alignItems(VerticalAlign.Center)
    }), Row);
    this.observeComponentCreation2(((t, e) => {
      Row.create();
      Row.height(40);
      Row.margin({ left: 8 });
      Row.focusable(!0)
    }), Row);
    this.observeComponentCreation2(((t, e) => {
      Text.create(this.floatFilterBarText);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
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
      Text.constraintSize({ maxWidth: "85%" });
      Text.maxLines(1)
    }), Text);
    Text.pop();
    this.observeComponentCreation2(((t, e) => {
      Image.create(ARROW_DOWN);
      Image.width(24);
      Image.height(24);
      Image.fillColor({
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_text_primary_activated"],
        bundleName: "",
        moduleName: ""
      });
      Image.focusable(!0)
    }), Image);
    Row.pop();
    Row.pop();
    Column.pop();
    Row.pop()
  }

  initialRender() {
    this.observeComponentCreation2(((t, e) => {
      Stack.create({ alignContent: Alignment.Top });
      Stack.clip(!0);
      Stack.onAreaChange(((t, e) => {
        console.log("stack height:" + parseInt(e.height.toString(), 0));
        this.filterStackHeight = parseInt(e.height.toString(), 0)
      }))
    }), Stack);
    this.FloatFilterBar.bind(this)();
    this.FloatFilterHeader.bind(this)();
    this.observeComponentCreation2(((t, e) => {
      Column.create();
      Column.zIndex(0)
    }), Column);
    this.observeComponentCreation2(((t, e) => {
      List.create({ initialIndex: 0 });
      List.listDirection(Axis.Vertical);
      List.width("100%");
      List.height("100%");
      List.edgeEffect(EdgeEffect.Spring);
      List.onScroll(((t, e) => {
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
      }))
    }), List);
    {
      const t = !0;
      const e = (e, i) => {
        ViewStackProcessor.StartGetAccessRecordingFor(e);
        ListItem.create(o, t);
        ListItem.focusable(!0);
        i || ListItem.pop();
        ViewStackProcessor.StopGetAccessRecording()
      };
      const o = (t, o) => {
        e(t, o);
        this.updateFuncByElmtId.set(t, e);
        this.FilterHeader.bind(this)();
        ListItem.pop()
      };
      this.observeComponentCreation(e);
      ListItem.pop()
    }
    {
      const t = !0;
      const e = (e, i) => {
        ViewStackProcessor.StartGetAccessRecordingFor(e);
        ListItem.create(o, t);
        ListItem.focusable(!0);
        i || ListItem.pop();
        ViewStackProcessor.StopGetAccessRecording()
      };
      const o = (t, o) => {
        e(t, o);
        this.updateFuncByElmtId.set(t, e);
        this.container.bind(this)();
        ListItem.pop()
      };
      this.observeComponentCreation(e);
      ListItem.pop()
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