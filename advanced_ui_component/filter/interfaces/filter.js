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

let __decorate = (this && this.__decorate) || function (q18, r18, s18, t18) {
  let u18 = arguments.length, v18 = u18 < 3 ? r18 : t18 === null ?
    t18 = Object.getOwnPropertyDescriptor(r18, s18) : t18, w18;
  if (typeof Reflect === 'object' && typeof Reflect.decorate === 'function') {
    v18 = Reflect.decorate(q18, r18, s18, t18);
  }
  else {
    for (let x18 = q18.length - 1; x18 >= 0; x18--) {
      if (w18 = q18[x18]) {
        v18 = (u18 < 3 ? w18(v18) : u18 > 3 ? w18(r18, s18, v18) : w18(r18, s18)) || v18;
      }
    }
  }
  return u18 > 3 && v18 && Object.defineProperty(r18, s18, v18), v18;
};
if (!('finalizeConstruction' in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => { });
}
const curves = requireNativeModule('ohos.curves');
const measure = requireNapi('measure');
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
const FLOAT_OPACITY = 0.95;
const FILTER_FONT_SIZE = 12;
const FOCUS_BORDER_WIDTH = 2;
const ARROW_SHOW_DELAY = 300;
const PERCENT_100 = '100%';
const SHARP_CUBIC_BEZIER = curves.cubicBezierCurve(0.33, 0, 0.67, 1);
const INTER_POLATING_SPRING = curves.interpolatingSpring(0, 1, 328, 34);
const FRICTION_CUBIC_BEZIER = curves.cubicBezierCurve(0.2, 0, 0.2, 1);
const TRANS_COLOR = '#00FFFFFF';
const GRADIENT_WIDTH = 16;
export var FilterType;
(function (o18) {
  o18[o18.MULTI_LINE_FILTER = 0] = 'MULTI_LINE_FILTER';
  o18[o18.LIST_FILTER = 1] = 'LIST_FILTER';
})(FilterType || (FilterType = {}));
let FontWeightArray = class FontWeightArray extends Array {
};
FontWeightArray = __decorate([
  Observed
], FontWeightArray);
let ResourceArray = class ResourceArray extends Array {
};
ResourceArray = __decorate([
  Observed
], ResourceArray);
let BooleanArray = class BooleanArray extends Array {
};
BooleanArray = __decorate([
  Observed
], BooleanArray);
let ObservedBoolean = class ObservedBoolean {
  constructor(n18) {
    this.value = n18;
  }
};
ObservedBoolean = __decorate([
  Observed
], ObservedBoolean);
export { ObservedBoolean };
let ObservedNumber = class ObservedNumber {
  constructor(m18) {
    this.value = m18;
  }
};
ObservedNumber = __decorate([
  Observed
], ObservedNumber);
class GradientMask extends ViewPU {
  constructor(g18, h18, i18, j18 = -1, k18 = undefined, l18) {
    super(g18, i18, j18, l18);
    if (typeof k18 === 'function') {
      this.paramsGenerator_ = k18;
    }
    this.x0 = 0;
    this.y0 = 0;
    this.x1 = 0;
    this.y1 = 0;
    this.settings = new RenderingContextSettings(true);
    this.context2D = new CanvasRenderingContext2D(this.settings);
    this.setInitiallyProvidedValue(h18);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(f18) {
    if (f18.x0 !== undefined) {
      this.x0 = f18.x0;
    }
    if (f18.y0 !== undefined) {
      this.y0 = f18.y0;
    }
    if (f18.x1 !== undefined) {
      this.x1 = f18.x1;
    }
    if (f18.y1 !== undefined) {
      this.y1 = f18.y1;
    }
    if (f18.settings !== undefined) {
      this.settings = f18.settings;
    }
    if (f18.context2D !== undefined) {
      this.context2D = f18.context2D;
    }
  }
  updateStateVars(e18) {
  }
  purgeVariableDependenciesOnElmtId(d18) {
  }
  aboutToBeDeleted() {
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  initialRender() {
    this.observeComponentCreation((b18, c18) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b18);
      Column.create();
      Column.width(GRADIENT_WIDTH);
      Column.height(LIST_ROW_HEIGHT);
      if (!c18) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((x17, y17) => {
      ViewStackProcessor.StartGetAccessRecordingFor(x17);
      Canvas.create(this.context2D);
      Canvas.width(GRADIENT_WIDTH);
      Canvas.height(LIST_ROW_HEIGHT);
      Canvas.onReady(() => {
        let a18 = this.context2D.createLinearGradient(this.x0, this.y0, this.x1, this.y1);
        a18.addColorStop(0.0, '#ffffffff');
        a18.addColorStop(1, '#00ffffff');
        this.context2D.fillStyle = a18;
        this.context2D.fillRect(0, 0, GRADIENT_WIDTH, LIST_ROW_HEIGHT);
      });
      if (!y17) {
        Canvas.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Canvas.pop();
    Column.pop();
  }
  rerender() {
    this.updateDirtyElements();
  }
}
class ListFilterRow extends ViewPU {
  constructor(o17, p17, q17, r17 = -1, s17 = undefined, t17) {
    super(o17, q17, r17, t17);
    if (typeof s17 === 'function') {
      this.paramsGenerator_ = s17;
    }
    this.__colorRow = new SynchedPropertyNesedObjectPU(p17.colorRow, this, 'colorRow');
    this.__fontWeightRow = new SynchedPropertyNesedObjectPU(p17.fontWeightRow, this, 'fontWeightRow');
    this.__backgroundColorRow = new SynchedPropertyNesedObjectPU(p17.backgroundColorRow, this, 'backgroundColorRow');
    this.__isBackgroundHoverRow =
      new SynchedPropertyNesedObjectPU(p17.isBackgroundHoverRow, this, 'isBackgroundHoverRow');
    this.filterRow = { name: '', options: [] };
    this.onItemClick = () => { };
    this.rowIndex = 0;
    this.setInitiallyProvidedValue(p17);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(n17) {
    this.__colorRow.set(n17.colorRow);
    this.__fontWeightRow.set(n17.fontWeightRow);
    this.__backgroundColorRow.set(n17.backgroundColorRow);
    this.__isBackgroundHoverRow.set(n17.isBackgroundHoverRow);
    if (n17.filterRow !== undefined) {
      this.filterRow = n17.filterRow;
    }
    if (n17.onItemClick !== undefined) {
      this.onItemClick = n17.onItemClick;
    }
    if (n17.rowIndex !== undefined) {
      this.rowIndex = n17.rowIndex;
    }
  }
  updateStateVars(m17) {
    this.__colorRow.set(m17.colorRow);
    this.__fontWeightRow.set(m17.fontWeightRow);
    this.__backgroundColorRow.set(m17.backgroundColorRow);
    this.__isBackgroundHoverRow.set(m17.isBackgroundHoverRow);
  }
  purgeVariableDependenciesOnElmtId(l17) {
    this.__colorRow.purgeDependencyOnElmtId(l17);
    this.__fontWeightRow.purgeDependencyOnElmtId(l17);
    this.__backgroundColorRow.purgeDependencyOnElmtId(l17);
    this.__isBackgroundHoverRow.purgeDependencyOnElmtId(l17);
  }
  aboutToBeDeleted() {
    this.__colorRow.aboutToBeDeleted();
    this.__fontWeightRow.aboutToBeDeleted();
    this.__backgroundColorRow.aboutToBeDeleted();
    this.__isBackgroundHoverRow.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get colorRow() {
    return this.__colorRow.get();
  }
  get fontWeightRow() {
    return this.__fontWeightRow.get();
  }
  get backgroundColorRow() {
    return this.__backgroundColorRow.get();
  }
  get isBackgroundHoverRow() {
    return this.__isBackgroundHoverRow.get();
  }
  initialRender() {
    this.observeComponentCreation((j17, k17) => {
      ViewStackProcessor.StartGetAccessRecordingFor(j17);
      Stack.create({ alignContent: Alignment.End });
      if (!k17) {
        Stack.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((h17, i17) => {
      ViewStackProcessor.StartGetAccessRecordingFor(h17);
      Stack.create({ alignContent: Alignment.Start });
      if (!i17) {
        Stack.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((f17, g17) => {
      ViewStackProcessor.StartGetAccessRecordingFor(f17);
      List.create();
      List.listDirection(Axis.Horizontal);
      List.scrollBar(BarState.Off);
      List.width(PERCENT_100);
      List.height(LIST_ROW_HEIGHT);
      List.align(Alignment.Start);
      if (!g17) {
        List.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((k15, l15) => {
      ViewStackProcessor.StartGetAccessRecordingFor(k15);
      ForEach.create();
      const m15 = (o15, p15) => {
        const q15 = o15;
        this.observeComponentCreation((p16, q16) => {
          ViewStackProcessor.StartGetAccessRecordingFor(p16);
          If.create();
          if (p15 === 0) {
            this.ifElseBranchUpdateFunction(0, () => {
              {
                const t16 = (d17, e17) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(d17);
                  u16(d17, e17);
                  if (!e17) {
                    ListItem.pop();
                  }
                  ViewStackProcessor.StopGetAccessRecording();
                };
                const u16 = (b17, c17) => {
                  ListItem.create(v16, true);
                  ListItem.width({
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_max_padding_start'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                  });
                  ListItem.height(LIST_ROW_HEIGHT);
                };
                const v16 = (z16, a17) => {
                  t16(z16, a17);
                  this.updateFuncByElmtId.set(z16, t16);
                  ListItem.pop();
                };
                this.observeComponentCreation(t16);
                ListItem.pop();
              }
            });
          }
          else {
            this.ifElseBranchUpdateFunction(1, () => {
            });
          }
          if (!q16) {
            If.pop();
          }
          ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        {
          const s15 = (n16, o16) => {
            ViewStackProcessor.StartGetAccessRecordingFor(n16);
            t15(n16, o16);
            if (!o16) {
              ListItem.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          };
          const t15 = (d16, e16) => {
            ListItem.create(u15, true);
            ListItem.height(PERCENT_100);
            ListItem.onClick(() => {
              this.onItemClick(p15);
            });
            ListItem.focusable(true);
            ViewStackProcessor.visualState('focused');
            ListItem.border({
              radius: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_corner_radius_clicked'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
              },
              width: FOCUS_BORDER_WIDTH,
              color: {
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_focused_outline'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
              },
              style: BorderStyle.Solid
            });
            ListItem.padding({
              left: TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH,
              right: TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH,
            });
            ViewStackProcessor.visualState('normal');
            ListItem.border({
              radius: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_corner_radius_clicked'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
              },
              width: 0
            });
            ListItem.padding({ left: TEXT_HOT_AREA_WIDTH, right: TEXT_HOT_AREA_WIDTH });
            ViewStackProcessor.visualState();
            ListItem.backgroundColor(this.isBackgroundHoverRow[p15] ? this.backgroundColorRow[p15] : TRANS_COLOR);
            ListItem.onHover((l16) => {
              Context.animateTo({
                curve: FRICTION_CUBIC_BEZIER,
                duration: ANIMATION_DURATION_250,
              }, () => {
                if (l16) {
                  this.backgroundColorRow[p15] = {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_hover'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                  };
                  this.isBackgroundHoverRow[p15] = true;
                }
                else {
                  this.isBackgroundHoverRow[p15] = false;
                }
              });
            });
            ListItem.onTouch((i16) => {
              if (i16.type === TouchType.Down) {
                Context.animateTo({
                  curve: SHARP_CUBIC_BEZIER,
                  duration: ANIMATION_DURATION_100,
                }, () => {
                  this.backgroundColorRow[p15] = {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_click_effect'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                  };
                  this.isBackgroundHoverRow[p15] = true;
                });
              }
              else if (i16.type === TouchType.Up) {
                Context.animateTo({
                  curve: SHARP_CUBIC_BEZIER,
                  duration: ANIMATION_DURATION_100,
                }, () => {
                  this.isBackgroundHoverRow[p15] = false;
                });
              }
            });
            ListItem.margin({ left: p15 === 0 ? -TEXT_HOT_AREA_WIDTH : 0 });
            ListItem.tabIndex(p15 === 0 ? this.rowIndex : -1);
          };
          const u15 = (y15, z15) => {
            s15(y15, z15);
            this.updateFuncByElmtId.set(y15, s15);
            this.observeComponentCreation((b16, c16) => {
              ViewStackProcessor.StartGetAccessRecordingFor(b16);
              Text.create(q15.toString());
              Text.fontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_body3'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
              });
              Text.fontColor(this.colorRow[p15]);
              Text.fontWeight(this.fontWeightRow[p15]);
              Text.focusable(true);
              if (!c16) {
                Text.pop();
              }
              ViewStackProcessor.StopGetAccessRecording();
            });
            Text.pop();
            ListItem.pop();
          };
          this.observeComponentCreation(s15);
          ListItem.pop();
        }
      };
      this.forEachUpdateFunction(k15, this.filterRow.options, m15, undefined, true, false);
      if (!l15) {
        ForEach.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    ForEach.pop();
    List.pop();
    {
      this.observeComponentCreation((e15, f15) => {
        ViewStackProcessor.StartGetAccessRecordingFor(e15);
        if (f15) {
          let g15 = new GradientMask(this, {
            x0: 0,
            y0: LIST_ROW_HEIGHT / 2,
            x1: GRADIENT_WIDTH,
            y1: LIST_ROW_HEIGHT / 2,
          }, undefined, e15, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 209 });
          ViewPU.create(g15);
          let h15 = () => {
            return {
              x0: 0,
              y0: LIST_ROW_HEIGHT / 2,
              x1: GRADIENT_WIDTH,
              y1: LIST_ROW_HEIGHT / 2,
            };
          };
          g15.paramsGenerator_ = h15;
        }
        else {
          this.updateStateVarsOfChildByElmtId(e15, {});
        }
        ViewStackProcessor.StopGetAccessRecording();
      });
    }
    Stack.pop();
    {
      this.observeComponentCreation((x14, y14) => {
        ViewStackProcessor.StartGetAccessRecordingFor(x14);
        if (y14) {
          let z14 = new GradientMask(this, {
            x0: GRADIENT_WIDTH,
            y0: LIST_ROW_HEIGHT / 2,
            x1: 0,
            y1: LIST_ROW_HEIGHT / 2,
          }, undefined, x14, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 216 });
          ViewPU.create(z14);
          let a15 = () => {
            return {
              x0: GRADIENT_WIDTH,
              y0: LIST_ROW_HEIGHT / 2,
              x1: 0,
              y1: LIST_ROW_HEIGHT / 2,
            };
          };
          z14.paramsGenerator_ = a15;
        }
        else {
          this.updateStateVarsOfChildByElmtId(x14, {});
        }
        ViewStackProcessor.StopGetAccessRecording();
      });
    }
    Stack.pop();
  }
  rerender() {
    this.updateDirtyElements();
  }
}
class MultiFilterRow extends ViewPU {
  constructor(l14, m14, n14, o14 = -1, p14 = undefined, q14) {
    super(l14, n14, o14, q14);
    if (typeof p14 === 'function') {
      this.paramsGenerator_ = p14;
    }
    this.__colorRow = new SynchedPropertyNesedObjectPU(m14.colorRow, this, 'colorRow');
    this.__fontWeightRow = new SynchedPropertyNesedObjectPU(m14.fontWeightRow, this, 'fontWeightRow');
    this.__backgroundColorRow = new SynchedPropertyNesedObjectPU(m14.backgroundColorRow, this, 'backgroundColorRow');
    this.__isBackgroundHoverRow = new SynchedPropertyNesedObjectPU(m14.isBackgroundHoverRow, this, 'isBackgroundHoverRow');
    this.__twoLineModeItemNumRow = new SynchedPropertyNesedObjectPU(m14.twoLineModeItemNumRow, this, 'twoLineModeItemNumRow');
    this.__twoLineModeItemNumRecordRow = new SynchedPropertyNesedObjectPU(m14.twoLineModeItemNumRecordRow, this, 'twoLineModeItemNumRecordRow');
    this.__arrowShowStateRow = new SynchedPropertyNesedObjectPU(m14.arrowShowStateRow, this, 'arrowShowStateRow');
    this.__isArrowIconDown = new SynchedPropertyNesedObjectPU(m14.isArrowIconDown, this, 'isArrowIconDown');
    this.filterRow = null;
    this.onItemClick = () => {
    };
    this.__arrowBgColorRow = new ObservedPropertyObjectPU({
      'id': -1,
      'type': 10001,
      params: ['sys.color.ohos_id_color_hover'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__',
    }, this, 'arrowBgColorRow');
    this.__isArrowBgHoverRow = new ObservedPropertySimplePU(false, this, 'isArrowBgHoverRow');
    this.filterColumnWidth = 0;
    this.lastFilterColumnWidth = 0;
    this.rowIndex = 0;
    this.setInitiallyProvidedValue(m14);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(k14) {
    this.__colorRow.set(k14.colorRow);
    this.__fontWeightRow.set(k14.fontWeightRow);
    this.__backgroundColorRow.set(k14.backgroundColorRow);
    this.__isBackgroundHoverRow.set(k14.isBackgroundHoverRow);
    this.__twoLineModeItemNumRow.set(k14.twoLineModeItemNumRow);
    this.__twoLineModeItemNumRecordRow.set(k14.twoLineModeItemNumRecordRow);
    this.__arrowShowStateRow.set(k14.arrowShowStateRow);
    this.__isArrowIconDown.set(k14.isArrowIconDown);
    if (k14.filterRow !== undefined) {
      this.filterRow = k14.filterRow;
    }
    if (k14.onItemClick !== undefined) {
      this.onItemClick = k14.onItemClick;
    }
    if (k14.arrowBgColorRow !== undefined) {
      this.arrowBgColorRow = k14.arrowBgColorRow;
    }
    if (k14.isArrowBgHoverRow !== undefined) {
      this.isArrowBgHoverRow = k14.isArrowBgHoverRow;
    }
    if (k14.filterColumnWidth !== undefined) {
      this.filterColumnWidth = k14.filterColumnWidth;
    }
    if (k14.lastFilterColumnWidth !== undefined) {
      this.lastFilterColumnWidth = k14.lastFilterColumnWidth;
    }
    if (k14.rowIndex !== undefined) {
      this.rowIndex = k14.rowIndex;
    }
  }
  updateStateVars(j14) {
    this.__colorRow.set(j14.colorRow);
    this.__fontWeightRow.set(j14.fontWeightRow);
    this.__backgroundColorRow.set(j14.backgroundColorRow);
    this.__isBackgroundHoverRow.set(j14.isBackgroundHoverRow);
    this.__twoLineModeItemNumRow.set(j14.twoLineModeItemNumRow);
    this.__twoLineModeItemNumRecordRow.set(j14.twoLineModeItemNumRecordRow);
    this.__arrowShowStateRow.set(j14.arrowShowStateRow);
    this.__isArrowIconDown.set(j14.isArrowIconDown);
  }
  purgeVariableDependenciesOnElmtId(i14) {
    this.__colorRow.purgeDependencyOnElmtId(i14);
    this.__fontWeightRow.purgeDependencyOnElmtId(i14);
    this.__backgroundColorRow.purgeDependencyOnElmtId(i14);
    this.__isBackgroundHoverRow.purgeDependencyOnElmtId(i14);
    this.__twoLineModeItemNumRow.purgeDependencyOnElmtId(i14);
    this.__twoLineModeItemNumRecordRow.purgeDependencyOnElmtId(i14);
    this.__arrowShowStateRow.purgeDependencyOnElmtId(i14);
    this.__isArrowIconDown.purgeDependencyOnElmtId(i14);
    this.__arrowBgColorRow.purgeDependencyOnElmtId(i14);
    this.__isArrowBgHoverRow.purgeDependencyOnElmtId(i14);
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
    this.aboutToBeDeletedInternal();
  }
  get colorRow() {
    return this.__colorRow.get();
  }
  get fontWeightRow() {
    return this.__fontWeightRow.get();
  }
  get backgroundColorRow() {
    return this.__backgroundColorRow.get();
  }
  get isBackgroundHoverRow() {
    return this.__isBackgroundHoverRow.get();
  }
  get twoLineModeItemNumRow() {
    return this.__twoLineModeItemNumRow.get();
  }
  get twoLineModeItemNumRecordRow() {
    return this.__twoLineModeItemNumRecordRow.get();
  }
  get arrowShowStateRow() {
    return this.__arrowShowStateRow.get();
  }
  get isArrowIconDown() {
    return this.__isArrowIconDown.get();
  }
  get arrowBgColorRow() {
    return this.__arrowBgColorRow.get();
  }
  set arrowBgColorRow(h14) {
    this.__arrowBgColorRow.set(h14);
  }
  get isArrowBgHoverRow() {
    return this.__isArrowBgHoverRow.get();
  }
  set isArrowBgHoverRow(g14) {
    this.__isArrowBgHoverRow.set(g14);
  }
  calcMultiFilterRowItemNum() {
    let a14 = this.filterColumnWidth - vp2px(MULTI_LINE_PADDING);
    let b14 = 0;
    let c14 = 1;
    if (this.filterRow) {
      for (let d14 = 0; d14 < this.filterRow.options.length; d14++) {
        let e14 = this.filterRow.options[d14];
        let f14 = measure.measureText({
          textContent: e14,
          fontSize: FILTER_FONT_SIZE,
        });
        if (d14 === 0) {
          continue;
        }
        else {
          f14 += vp2px(TEXT_HOT_AREA_WIDTH * 2);
        }
        if (a14 - f14 >= 0) {
          a14 -= f14;
          b14 += 1;
        }
        else {
          if (b14 === 0) {
            b14++;
            a14 = 0;
          }
          if (c14 === 1) {
            c14 += 1;
            a14 = this.filterColumnWidth - vp2px(ARROW_IMG_SIZE) - vp2px(MULTI_LINE_PADDING);
            d14--;
          }
          else {
            break;
          }
        }
      }
    }
    return b14;
  }
  DownAndUpArrow(g13 = null) {
    this.observeComponentCreation((l13, m13) => {
      ViewStackProcessor.StartGetAccessRecordingFor(l13);
      Row.create();
      Row.border({
        radius: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.ohos_id_corner_radius_clicked'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        }
      });
      Row.height(LIST_ROW_HEIGHT);
      Row.width(ARROW_IMG_SIZE);
      Row.backgroundColor(this.isArrowBgHoverRow ? this.arrowBgColorRow : TRANS_COLOR);
      Row.focusable(true);
      Row.visibility(this.arrowShowStateRow.value ? Visibility.Visible : Visibility.Hidden);
      Row.onHover((y13) => {
        Context.animateTo({
          curve: FRICTION_CUBIC_BEZIER,
          duration: ANIMATION_DURATION_250,
        }, () => {
          if (y13) {
            this.arrowBgColorRow = {
              'id': -1,
              'type': 10001,
              params: ['sys.color.ohos_id_color_hover'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__',
            };
            this.isArrowBgHoverRow = true;
          }
          else {
            this.isArrowBgHoverRow = false;
          }
        });
      });
      Row.onTouch((v13) => {
        if (v13.type === TouchType.Down) {
          Context.animateTo({
            curve: SHARP_CUBIC_BEZIER,
            duration: ANIMATION_DURATION_100,
          }, () => {
            this.arrowBgColorRow = {
              'id': -1,
              'type': 10001,
              params: ['sys.color.ohos_id_color_click_effect'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__',
            };
            this.isArrowBgHoverRow = true;
          });
        }
        else if (v13.type === TouchType.Up) {
          Context.animateTo({
            curve: SHARP_CUBIC_BEZIER,
            duration: ANIMATION_DURATION_100,
          }, () => {
            this.isArrowBgHoverRow = false;
          });
        }
      });
      Row.onClick(() => {
        if (this.isArrowIconDown.value) {
          this.isArrowIconDown.value = false;
          this.arrowShowStateRow.value = false;
          Context.animateTo({
            curve: INTER_POLATING_SPRING,
          }, () => {
            let u13;
            this.twoLineModeItemNumRow.value = (u13 = this.filterRow) === null || u13 === void 0 ? void 0 : u13.options.length;
          });
          Context.animateTo({
            delay: 300,
            duration: ARROW_ANIMATION_DURATION,
            curve: SHARP_CUBIC_BEZIER,
          }, () => {
            this.arrowShowStateRow.value = true;
          });
        }
        else {
          this.isArrowIconDown.value = true;
          this.arrowShowStateRow.value = false;
          Context.animateTo({
            curve: INTER_POLATING_SPRING,
          }, () => {
            this.twoLineModeItemNumRow.value = this.twoLineModeItemNumRecordRow.value;
          });
          Context.animateTo({
            delay: ARROW_SHOW_DELAY,
            duration: ARROW_ANIMATION_DURATION,
            curve: SHARP_CUBIC_BEZIER,
          }, () => {
            this.arrowShowStateRow.value = true;
          });
        }
      });
      if (!m13) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((j13, k13) => {
      ViewStackProcessor.StartGetAccessRecordingFor(j13);
      Image.create(this.isArrowIconDown.value ? {
        'id': -1,
        'type': 20000,
        params: ['sys.media.ohos_ic_public_arrow_down'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      } : {
        'id': -1,
        'type': 20000,
        params: ['sys.media.ohos_ic_public_arrow_up'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      });
      Image.width(ARROW_IMG_SIZE);
      Image.height(LIST_ROW_HEIGHT);
      Image.fillColor({
        'id': -1,
        'type': 10001,
        params: ['sys.color.ohos_id_color_tertiary'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      });
      Image.focusable(true);
      ViewStackProcessor.visualState('focused');
      Image.border({
        radius: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.ohos_id_corner_radius_clicked'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        },
        width: FOCUS_BORDER_WIDTH,
        color: {
          'id': -1,
          'type': 10001,
          params: ['sys.color.ohos_id_color_focused_outline'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        },
        style: BorderStyle.Solid
      });
      Image.width(ARROW_IMG_SIZE + FOCUS_BORDER_WIDTH * 2);
      Image.offset({ x: -FOCUS_BORDER_WIDTH });
      ViewStackProcessor.visualState('normal');
      Image.border({
        radius: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.ohos_id_corner_radius_clicked'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        },
        width: 0
      });
      Image.width(ARROW_IMG_SIZE);
      Image.offset({ x: 0 });
      ViewStackProcessor.visualState();
      Image.tabIndex(-1);
      if (!k13) {
        Image.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Row.pop();
  }
  initialRender() {
    this.observeComponentCreation((e13, f13) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e13);
      Row.create();
      Row.width(PERCENT_100);
      Row.alignItems(VerticalAlign.Top);
      Row.padding({
        left: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.ohos_id_max_padding_start'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        },
        right: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.ohos_id_max_padding_end'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        },
      });
      if (!f13) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((l12, m12) => {
      let n12;
      let o12;
      ViewStackProcessor.StartGetAccessRecordingFor(l12);
      If.create();
      if (((n12 = this.filterRow) === null || n12 === void 0 ? void 0 : n12.options) &&
        ((o12 = this.filterRow) === null || o12 === void 0 ? void 0 : o12.options.length) > 0) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((s12, t12) => {
            let u12;
            let v12;
            ViewStackProcessor.StartGetAccessRecordingFor(s12);
            Text.create((u12 = this.filterRow) === null || u12 === void 0 ? void 0 : u12.options[0].toString());
            Text.height(LIST_ROW_HEIGHT);
            Text.width(px2vp(measure.measureText({
              textContent: (v12 = this.filterRow) === null || v12 === void 0 ? void 0 : v12.options[0].toString(),
              fontSize: FILTER_FONT_SIZE
            })) + (TEXT_HOT_AREA_WIDTH * 2));
            Text.margin({ left: -TEXT_HOT_AREA_WIDTH });
            Text.fontSize({
              'id': -1,
              'type': 10002,
              params: ['sys.float.ohos_id_text_size_body3'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__',
            });
            Text.fontColor(this.colorRow[0]);
            Text.fontWeight(this.fontWeightRow[0]);
            Text.backgroundColor(this.isBackgroundHoverRow[0] ? this.backgroundColorRow[0] : TRANS_COLOR);
            Text.onClick(() => {
              this.onItemClick(0);
            });
            Text.focusable(true);
            Text.onHover((c13) => {
              Context.animateTo({
                curve: FRICTION_CUBIC_BEZIER,
                duration: ANIMATION_DURATION_250,
              }, () => {
                if (c13) {
                  this.backgroundColorRow[0] = {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_hover'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                  };
                  this.isBackgroundHoverRow[0] = true;
                }
                else {
                  this.isBackgroundHoverRow[0] = false;
                }
              });
            });
            Text.onTouch((z12) => {
              if (z12.type === TouchType.Down) {
                Context.animateTo({
                  curve: SHARP_CUBIC_BEZIER,
                  duration: ANIMATION_DURATION_100,
                }, () => {
                  this.backgroundColorRow[0] = {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_click_effect'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                  };
                  this.isBackgroundHoverRow[0] = true;
                });
              }
              else if (z12.type === TouchType.Up) {
                Context.animateTo({
                  curve: SHARP_CUBIC_BEZIER,
                  duration: ANIMATION_DURATION_100,
                }, () => {
                  this.isBackgroundHoverRow[0] = false;
                });
              }
            });
            ViewStackProcessor.visualState('focused');
            Text.border({
              radius: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_corner_radius_clicked'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
              },
              width: FOCUS_BORDER_WIDTH,
              color: {
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_focused_outline'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
              },
              style: BorderStyle.Solid,
            });
            Text.padding({
              left: TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH,
              right: TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH,
            });
            ViewStackProcessor.visualState('normal');
            Text.border({
              radius: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_corner_radius_clicked'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
              },
              width: 0,
            });
            Text.padding({ left: TEXT_HOT_AREA_WIDTH, right: TEXT_HOT_AREA_WIDTH });
            ViewStackProcessor.visualState();
            Text.tabIndex(this.rowIndex);
            if (!t12) {
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
      if (!m12) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.observeComponentCreation((e12, f12) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e12);
      Row.create();
      Row.width(PERCENT_100);
      Row.padding({
        right: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.ohos_id_max_padding_end'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        }
      });
      Row.onAreaChange((h12, i12) => {
        this.filterColumnWidth = vp2px(parseInt(i12.width.toString(), 0));
        if (this.twoLineModeItemNumRow.value === 0) {
          let k12 = this.calcMultiFilterRowItemNum();
          this.twoLineModeItemNumRow.value = k12;
          this.twoLineModeItemNumRecordRow.value = k12;
          if (this.filterRow && k12 < this.filterRow.options.length - 1) {
            this.arrowShowStateRow.value = true;
          }
          else {
            this.arrowShowStateRow.value = false;
          }
        }
        else if (this.filterColumnWidth !== this.lastFilterColumnWidth) {
          let j12 = this.calcMultiFilterRowItemNum();
          if (this.filterRow && j12 < this.filterRow.options.length - 1) {
            if (!this.arrowShowStateRow.value || this.isArrowIconDown.value) {
              this.arrowShowStateRow.value = true;
              this.isArrowIconDown.value = true;
              this.twoLineModeItemNumRow.value = j12;
            }
          }
          else {
            this.arrowShowStateRow.value = false;
            this.isArrowIconDown.value = false;
            this.twoLineModeItemNumRow.value = j12;
          }
          this.twoLineModeItemNumRecordRow.value = j12;
        }
        this.lastFilterColumnWidth = this.filterColumnWidth;
      });
      if (!f12) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((c12, d12) => {
      ViewStackProcessor.StartGetAccessRecordingFor(c12);
      Flex.create({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap });
      Flex.alignSelf(ItemAlign.Stretch);
      if (!d12) {
        Flex.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((e11, f11) => {
      let g11;
      ViewStackProcessor.StartGetAccessRecordingFor(e11);
      ForEach.create();
      const h11 = (j11, k11) => {
        const l11 = j11;
        this.observeComponentCreation((n11, o11) => {
          ViewStackProcessor.StartGetAccessRecordingFor(n11);
          If.create();
          if (k11 > 0) {
            this.ifElseBranchUpdateFunction(0, () => {
              this.observeComponentCreation((s11, t11) => {
                ViewStackProcessor.StartGetAccessRecordingFor(s11);
                Text.create(l11.toString());
                Text.transition(TransitionEffect.OPACITY);
                Text.fontSize({
                  'id': -1,
                  'type': 10002,
                  params: ['sys.float.ohos_id_text_size_body3'],
                  'bundleName': '__harDefaultBundleName__',
                  'moduleName': '__harDefaultModuleName__',
                });
                Text.height(LIST_ROW_HEIGHT);
                Text.fontColor(this.colorRow[k11]);
                Text.fontWeight(this.fontWeightRow[k11]);
                Text.backgroundColor(this.isBackgroundHoverRow[k11] ? this.backgroundColorRow[k11] : TRANS_COLOR);
                Text.onClick(() => {
                  this.onItemClick(k11);
                });
                Text.onHover((a12) => {
                  Context.animateTo({
                    curve: FRICTION_CUBIC_BEZIER,
                    duration: ANIMATION_DURATION_250,
                  }, () => {
                    if (a12) {
                      this.backgroundColorRow[k11] = {
                        'id': -1,
                        'type': 10001,
                        params: ['sys.color.ohos_id_color_hover'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__',
                      };
                      this.isBackgroundHoverRow[k11] = true;
                    }
                    else {
                      this.isBackgroundHoverRow[k11] = false;
                    }
                  });
                });
                Text.onTouch((x11) => {
                  if (x11.type === TouchType.Down) {
                    Context.animateTo({
                      curve: SHARP_CUBIC_BEZIER,
                      duration: ANIMATION_DURATION_100,
                    }, () => {
                      this.backgroundColorRow[k11] = {
                        'id': -1,
                        'type': 10001,
                        params: ['sys.color.ohos_id_color_click_effect'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__',
                      };
                      this.isBackgroundHoverRow[k11] = true;
                    });
                  }
                  else if (x11.type === TouchType.Up) {
                    Context.animateTo({
                      curve: SHARP_CUBIC_BEZIER,
                      duration: ANIMATION_DURATION_100,
                    }, () => {
                      this.isBackgroundHoverRow[k11] = false;
                    });
                  }
                });
                Text.focusable(true);
                ViewStackProcessor.visualState('focused');
                Text.border({
                  radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_corner_radius_clicked'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                  },
                  width: FOCUS_BORDER_WIDTH,
                  color: {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_focused_outline'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                  },
                  style: BorderStyle.Solid,
                });
                Text.padding({
                  left: TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH,
                  right: TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH,
                });
                ViewStackProcessor.visualState('normal');
                Text.border({
                  radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_corner_radius_clicked'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                  },
                  width: 0,
                });
                Text.padding({ left: TEXT_HOT_AREA_WIDTH, right: TEXT_HOT_AREA_WIDTH });
                ViewStackProcessor.visualState();
                Text.tabIndex(-1);
                if (!t11) {
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
          if (!o11) {
            If.pop();
          }
          ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
      };
      this.forEachUpdateFunction(e11, (g11 = this.filterRow) === null || g11 === void 0 ?
        void 0 : g11.options.slice(0, this.twoLineModeItemNumRow.value + 1), h11, undefined, true, false);
      if (!f11) {
        ForEach.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    ForEach.pop();
    this.observeComponentCreation((a11, b11) => {
      ViewStackProcessor.StartGetAccessRecordingFor(a11);
      If.create();
      if (this.arrowShowStateRow.value) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.DownAndUpArrow.bind(this)();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!b11) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    Flex.pop();
    Row.pop();
    Row.pop();
  }
  rerender() {
    this.updateDirtyElements();
  }
}
export class Filter extends ViewPU {
  constructor(o10, p10, q10, r10 = -1, s10 = undefined, t10) {
    super(o10, q10, r10, t10);
    if (typeof s10 === 'function') {
      this.paramsGenerator_ = s10;
    }
    this.container = undefined;
    this.__multiFilters = new SynchedPropertyObjectOneWayPU(p10.multiFilters, this, 'multiFilters');
    this.__additionFilters = new SynchedPropertyObjectOneWayPU(p10.additionFilters, this, 'additionFilters');
    this.onFilterChanged = null;
    this.__filterType = new SynchedPropertySimpleOneWayPU(p10.filterType, this, 'filterType');
    this.selectedFilters = null;
    this.__colorArr = new ObservedPropertyObjectPU(null, this, 'colorArr');
    this.__fontWeightArr = new ObservedPropertyObjectPU(null, this, 'fontWeightArr');
    this.__backgroundColorArr = new ObservedPropertyObjectPU(null, this, 'backgroundColorArr');
    this.__isBackgroundHover = new ObservedPropertyObjectPU(null, this, 'isBackgroundHover');
    this.__floatArrowBgColor = new ObservedPropertyObjectPU(null, this, 'floatArrowBgColor');
    this.__isFloatArrowBgHover = new ObservedPropertySimplePU(false, this, 'isFloatArrowBgHover');
    this.__isArrowIconDownArr = new ObservedPropertyObjectPU(null, this, 'isArrowIconDownArr');
    this.__additionColorArr = new ObservedPropertyObjectPU(null, this, 'additionColorArr');
    this.__additionFontWeightArr = new ObservedPropertyObjectPU(null, this, 'additionFontWeightArr');
    this.__additionBackgroundColorArr = new ObservedPropertyObjectPU(null, this, 'additionBackgroundColorArr');
    this.__isAdditionBackgroundHover = new ObservedPropertyObjectPU(null, this, 'isAdditionBackgroundHover');
    this.__colorRefresh = new ObservedPropertySimplePU(false, this, 'colorRefresh');
    this.__isFloatBarShow = new ObservedPropertySimplePU(false, this, 'isFloatBarShow');
    this.isFloatBarShowWithoutAnimation = false;
    this.__isFloatShowAllFilter = new ObservedPropertySimplePU(false, this, 'isFloatShowAllFilter');
    this.isFloatShowAllFilterWithoutAnimation = false;
    this.__floatFilterPosition = new ObservedPropertySimplePU(0, this, 'floatFilterPosition');
    this.__floatFilterBarHeight = new ObservedPropertySimplePU(0, this, 'floatFilterBarHeight');
    this.__floatFilterBarPosition = new ObservedPropertySimplePU(0, this, 'floatFilterBarPosition');
    this.filterDynamicHeight = 0;
    this.__twoLineModeItemNum = new ObservedPropertyObjectPU(null, this, 'twoLineModeItemNum');
    this.__twoLineModeItemNumRecord = new ObservedPropertyObjectPU(null, this, 'twoLineModeItemNumRecord');
    this.__downArrowShowState = new ObservedPropertyObjectPU(null, this, 'downArrowShowState');
    this.__floatFilterBarText = new ObservedPropertySimplePU('', this, 'floatFilterBarText');
    this.setInitiallyProvidedValue(p10);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(n10) {
    if (n10.container !== undefined) {
      this.container = n10.container;
    }
    if (n10.multiFilters === undefined) {
      this.__multiFilters.set([]);
    }
    if (n10.additionFilters === undefined) {
      this.__additionFilters.set(null);
    }
    if (n10.onFilterChanged !== undefined) {
      this.onFilterChanged = n10.onFilterChanged;
    }
    if (n10.filterType === undefined) {
      this.__filterType.set(FilterType.LIST_FILTER);
    }
    if (n10.selectedFilters !== undefined) {
      this.selectedFilters = n10.selectedFilters;
    }
    if (n10.colorArr !== undefined) {
      this.colorArr = n10.colorArr;
    }
    if (n10.fontWeightArr !== undefined) {
      this.fontWeightArr = n10.fontWeightArr;
    }
    if (n10.backgroundColorArr !== undefined) {
      this.backgroundColorArr = n10.backgroundColorArr;
    }
    if (n10.isBackgroundHover !== undefined) {
      this.isBackgroundHover = n10.isBackgroundHover;
    }
    if (n10.floatArrowBgColor !== undefined) {
      this.floatArrowBgColor = n10.floatArrowBgColor;
    }
    if (n10.isFloatArrowBgHover !== undefined) {
      this.isFloatArrowBgHover = n10.isFloatArrowBgHover;
    }
    if (n10.isArrowIconDownArr !== undefined) {
      this.isArrowIconDownArr = n10.isArrowIconDownArr;
    }
    if (n10.additionColorArr !== undefined) {
      this.additionColorArr = n10.additionColorArr;
    }
    if (n10.additionFontWeightArr !== undefined) {
      this.additionFontWeightArr = n10.additionFontWeightArr;
    }
    if (n10.additionBackgroundColorArr !== undefined) {
      this.additionBackgroundColorArr = n10.additionBackgroundColorArr;
    }
    if (n10.isAdditionBackgroundHover !== undefined) {
      this.isAdditionBackgroundHover = n10.isAdditionBackgroundHover;
    }
    if (n10.colorRefresh !== undefined) {
      this.colorRefresh = n10.colorRefresh;
    }
    if (n10.isFloatBarShow !== undefined) {
      this.isFloatBarShow = n10.isFloatBarShow;
    }
    if (n10.isFloatBarShowWithoutAnimation !== undefined) {
      this.isFloatBarShowWithoutAnimation = n10.isFloatBarShowWithoutAnimation;
    }
    if (n10.isFloatShowAllFilter !== undefined) {
      this.isFloatShowAllFilter = n10.isFloatShowAllFilter;
    }
    if (n10.isFloatShowAllFilterWithoutAnimation !== undefined) {
      this.isFloatShowAllFilterWithoutAnimation = n10.isFloatShowAllFilterWithoutAnimation;
    }
    if (n10.floatFilterPosition !== undefined) {
      this.floatFilterPosition = n10.floatFilterPosition;
    }
    if (n10.floatFilterBarHeight !== undefined) {
      this.floatFilterBarHeight = n10.floatFilterBarHeight;
    }
    if (n10.floatFilterBarPosition !== undefined) {
      this.floatFilterBarPosition = n10.floatFilterBarPosition;
    }
    if (n10.filterDynamicHeight !== undefined) {
      this.filterDynamicHeight = n10.filterDynamicHeight;
    }
    if (n10.twoLineModeItemNum !== undefined) {
      this.twoLineModeItemNum = n10.twoLineModeItemNum;
    }
    if (n10.twoLineModeItemNumRecord !== undefined) {
      this.twoLineModeItemNumRecord = n10.twoLineModeItemNumRecord;
    }
    if (n10.downArrowShowState !== undefined) {
      this.downArrowShowState = n10.downArrowShowState;
    }
    if (n10.floatFilterBarText !== undefined) {
      this.floatFilterBarText = n10.floatFilterBarText;
    }
  }
  updateStateVars(m10) {
    this.__multiFilters.reset(m10.multiFilters);
    this.__additionFilters.reset(m10.additionFilters);
    this.__filterType.reset(m10.filterType);
  }
  purgeVariableDependenciesOnElmtId(l10) {
    this.__multiFilters.purgeDependencyOnElmtId(l10);
    this.__additionFilters.purgeDependencyOnElmtId(l10);
    this.__filterType.purgeDependencyOnElmtId(l10);
    this.__colorArr.purgeDependencyOnElmtId(l10);
    this.__fontWeightArr.purgeDependencyOnElmtId(l10);
    this.__backgroundColorArr.purgeDependencyOnElmtId(l10);
    this.__isBackgroundHover.purgeDependencyOnElmtId(l10);
    this.__floatArrowBgColor.purgeDependencyOnElmtId(l10);
    this.__isFloatArrowBgHover.purgeDependencyOnElmtId(l10);
    this.__isArrowIconDownArr.purgeDependencyOnElmtId(l10);
    this.__additionColorArr.purgeDependencyOnElmtId(l10);
    this.__additionFontWeightArr.purgeDependencyOnElmtId(l10);
    this.__additionBackgroundColorArr.purgeDependencyOnElmtId(l10);
    this.__isAdditionBackgroundHover.purgeDependencyOnElmtId(l10);
    this.__colorRefresh.purgeDependencyOnElmtId(l10);
    this.__isFloatBarShow.purgeDependencyOnElmtId(l10);
    this.__isFloatShowAllFilter.purgeDependencyOnElmtId(l10);
    this.__floatFilterPosition.purgeDependencyOnElmtId(l10);
    this.__floatFilterBarHeight.purgeDependencyOnElmtId(l10);
    this.__floatFilterBarPosition.purgeDependencyOnElmtId(l10);
    this.__twoLineModeItemNum.purgeDependencyOnElmtId(l10);
    this.__twoLineModeItemNumRecord.purgeDependencyOnElmtId(l10);
    this.__downArrowShowState.purgeDependencyOnElmtId(l10);
    this.__floatFilterBarText.purgeDependencyOnElmtId(l10);
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
    this.aboutToBeDeletedInternal();
  }
  get multiFilters() {
    return this.__multiFilters.get();
  }
  set multiFilters(k10) {
    this.__multiFilters.set(k10);
  }
  get additionFilters() {
    return this.__additionFilters.get();
  }
  set additionFilters(j10) {
    this.__additionFilters.set(j10);
  }
  get filterType() {
    return this.__filterType.get();
  }
  set filterType(i10) {
    this.__filterType.set(i10);
  }
  get colorArr() {
    return this.__colorArr.get();
  }
  set colorArr(h10) {
    this.__colorArr.set(h10);
  }
  get fontWeightArr() {
    return this.__fontWeightArr.get();
  }
  set fontWeightArr(g10) {
    this.__fontWeightArr.set(g10);
  }
  get backgroundColorArr() {
    return this.__backgroundColorArr.get();
  }
  set backgroundColorArr(f10) {
    this.__backgroundColorArr.set(f10);
  }
  get isBackgroundHover() {
    return this.__isBackgroundHover.get();
  }
  set isBackgroundHover(e10) {
    this.__isBackgroundHover.set(e10);
  }
  get floatArrowBgColor() {
    return this.__floatArrowBgColor.get();
  }
  set floatArrowBgColor(d10) {
    this.__floatArrowBgColor.set(d10);
  }
  get isFloatArrowBgHover() {
    return this.__isFloatArrowBgHover.get();
  }
  set isFloatArrowBgHover(c10) {
    this.__isFloatArrowBgHover.set(c10);
  }
  get isArrowIconDownArr() {
    return this.__isArrowIconDownArr.get();
  }
  set isArrowIconDownArr(b10) {
    this.__isArrowIconDownArr.set(b10);
  }
  get additionColorArr() {
    return this.__additionColorArr.get();
  }
  set additionColorArr(a10) {
    this.__additionColorArr.set(a10);
  }
  get additionFontWeightArr() {
    return this.__additionFontWeightArr.get();
  }
  set additionFontWeightArr(z9) {
    this.__additionFontWeightArr.set(z9);
  }
  get additionBackgroundColorArr() {
    return this.__additionBackgroundColorArr.get();
  }
  set additionBackgroundColorArr(y9) {
    this.__additionBackgroundColorArr.set(y9);
  }
  get isAdditionBackgroundHover() {
    return this.__isAdditionBackgroundHover.get();
  }
  set isAdditionBackgroundHover(x9) {
    this.__isAdditionBackgroundHover.set(x9);
  }
  get colorRefresh() {
    return this.__colorRefresh.get();
  }
  set colorRefresh(w9) {
    this.__colorRefresh.set(w9);
  }
  get isFloatBarShow() {
    return this.__isFloatBarShow.get();
  }
  set isFloatBarShow(v9) {
    this.__isFloatBarShow.set(v9);
  }
  get isFloatShowAllFilter() {
    return this.__isFloatShowAllFilter.get();
  }
  set isFloatShowAllFilter(u9) {
    this.__isFloatShowAllFilter.set(u9);
  }
  get floatFilterPosition() {
    return this.__floatFilterPosition.get();
  }
  set floatFilterPosition(t9) {
    this.__floatFilterPosition.set(t9);
  }
  get floatFilterBarHeight() {
    return this.__floatFilterBarHeight.get();
  }
  set floatFilterBarHeight(s9) {
    this.__floatFilterBarHeight.set(s9);
  }
  get floatFilterBarPosition() {
    return this.__floatFilterBarPosition.get();
  }
  set floatFilterBarPosition(r9) {
    this.__floatFilterBarPosition.set(r9);
  }
  get twoLineModeItemNum() {
    return this.__twoLineModeItemNum.get();
  }
  set twoLineModeItemNum(q9) {
    this.__twoLineModeItemNum.set(q9);
  }
  get twoLineModeItemNumRecord() {
    return this.__twoLineModeItemNumRecord.get();
  }
  set twoLineModeItemNumRecord(p9) {
    this.__twoLineModeItemNumRecord.set(p9);
  }
  get downArrowShowState() {
    return this.__downArrowShowState.get();
  }
  set downArrowShowState(o9) {
    this.__downArrowShowState.set(o9);
  }
  get floatFilterBarText() {
    return this.__floatFilterBarText.get();
  }
  set floatFilterBarText(n9) {
    this.__floatFilterBarText.set(n9);
  }
  textColor(l9, m9) {
    if (this.selectedFilters && this.selectedFilters.length > l9 &&
      this.selectedFilters[l9].index === m9) {
      return {
        'id': -1,
        'type': 10001,
        params: ['sys.color.ohos_id_color_text_primary_activated'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      };
    }
    return {
      'id': -1,
      'type': 10001,
      params: ['sys.color.ohos_id_color_text_primary'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__',
    };
  }
  aboutToAppear() {
    this.initParams();
  }
  filterItemClick(h9, i9) {
    let j9 = this.multiFilters[h9].options[i9];
    if (this.selectedFilters && i9 !== this.selectedFilters[h9].index) {
      if (this.colorArr) {
        this.colorArr[h9][i9] = {
          'id': -1,
          'type': 10001,
          params: ['sys.color.ohos_id_color_text_primary_activated'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        };
        this.colorArr[h9][this.selectedFilters[h9].index] = {
          'id': -1,
          'type': 10001,
          params: ['sys.color.ohos_id_color_text_primary'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        };
      }
      if (this.fontWeightArr) {
        this.fontWeightArr[h9][i9] = FontWeight.Medium;
        this.fontWeightArr[h9][this.selectedFilters[h9].index] = FontWeight.Regular;
      }
      this.colorRefresh = !this.colorRefresh;
      this.selectedFilters[h9].value = j9;
      this.selectedFilters[h9].index = i9;
      let k9 = this.onFilterChanged;
      k9 && k9(this.selectedFilters);
    }
    this.refreshFloatFilterBarText();
  }
  refreshFloatFilterBarText() {
    this.floatFilterBarText = '';
    if (this.selectedFilters) {
      for (let g9 = 0; g9 < this.selectedFilters.length; g9++) {
        if (this.selectedFilters[g9].value !== null) {
          if (g9 === 0) {
            this.floatFilterBarText += this.selectedFilters[g9].value;
          }
          else {
            this.floatFilterBarText += '/' + this.selectedFilters[g9].value;
          }
        }
      }
    }
  }
  initParams() {
    if (!this.selectedFilters) {
      this.selectedFilters = [];
      for (let e9 of this.multiFilters) {
        let f9 = { name: e9.name, index: -1, value: '' };
        if (e9.options.length > 0) {
          f9.index = 0;
          f9.value = e9.options[0];
        }
        this.selectedFilters.push(f9);
      }
      if (this.additionFilters && this.additionFilters.name) {
        let d9 = { name: this.additionFilters.name, index: -1, value: '' };
        this.selectedFilters.push(d9);
      }
      this.refreshFloatFilterBarText();
    }
    if (!this.colorArr) {
      this.colorArr = [];
      this.backgroundColorArr = [];
      this.isBackgroundHover = [];
      this.fontWeightArr = [];
      this.isArrowIconDownArr = [];
      this.floatArrowBgColor = {
        'id': -1,
        'type': 10001,
        params: ['sys.color.ohos_id_color_background'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      };
      for (let x8 of this.multiFilters) {
        let y8 = new ResourceArray();
        let z8 = new FontWeightArray();
        let a9 = new ResourceArray();
        let b9 = new BooleanArray();
        for (let c9 of x8.options.keys()) {
          if (c9 === 0) {
            y8.push({
              'id': -1,
              'type': 10001,
              params: ['sys.color.ohos_id_color_text_primary_activated'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__',
            });
            z8.push(FontWeight.Medium);
          }
          else {
            y8.push({
              'id': -1,
              'type': 10001,
              params: ['sys.color.ohos_id_color_text_primary'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__',
            });
            z8.push(FontWeight.Regular);
          }
          a9.push({
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_hover'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
          });
        }
        this.colorArr.push(y8);
        this.fontWeightArr.push(z8);
        this.backgroundColorArr.push(a9);
        this.isBackgroundHover.push(b9);
        this.isArrowIconDownArr.push(new ObservedBoolean(true));
      }
    }
    if (this.additionFilters && this.additionFilters.options) {
      this.additionColorArr = [];
      this.additionFontWeightArr = [];
      this.additionBackgroundColorArr = [];
      this.isAdditionBackgroundHover = [];
      for (let w8 = 0; w8 < this.additionFilters.options.length; w8++) {
        this.additionColorArr.push({
          'id': -1,
          'type': 10001,
          params: ['sys.color.ohos_id_color_text_primary'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        });
        this.additionFontWeightArr.push(FontWeight.Regular);
        this.additionBackgroundColorArr.push({
          'id': -1,
          'type': 10001,
          params: ['sys.color.ohos_id_color_hover'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        });
        this.isAdditionBackgroundHover.push(false);
      }
    }
    if (!this.twoLineModeItemNum) {
      this.twoLineModeItemNum = [];
      this.twoLineModeItemNumRecord = [];
      this.downArrowShowState = [];
      for (let v8 = 0; v8 < this.multiFilters.length; v8++) {
        this.twoLineModeItemNum.push(new ObservedNumber(this.multiFilters[v8].options.length));
        this.twoLineModeItemNumRecord.push(new ObservedNumber(this.multiFilters[v8].options.length));
        this.downArrowShowState.push(new ObservedBoolean(false));
      }
    }
  }
  ListFilter(x7 = null) {
    this.observeComponentCreation((q8, r8) => {
      ViewStackProcessor.StartGetAccessRecordingFor(q8);
      Column.create();
      Column.width(PERCENT_100);
      Column.align(Alignment.Start);
      Column.onAreaChange((t8, u8) => {
        if (!this.isFloatShowAllFilterWithoutAnimation && !this.isFloatBarShowWithoutAnimation) {
          if (this.additionFilters != null) {
            this.filterDynamicHeight = parseInt(u8.height.toString(), 0) + LIST_ROW_HEIGHT + FILTER_TOP_PADDING;
          }
          else {
            this.filterDynamicHeight = parseInt(u8.height.toString(), 0) + FILTER_TOP_PADDING;
          }
          this.floatFilterPosition = -this.filterDynamicHeight;
        }
      });
      if (!r8) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((a8, b8) => {
      ViewStackProcessor.StartGetAccessRecordingFor(a8);
      ForEach.create();
      const c8 = (e8, f8) => {
        const g8 = e8;
        {
          this.observeComponentCreation((i8, j8) => {
            ViewStackProcessor.StartGetAccessRecordingFor(i8);
            if (j8) {
              let k8 = new ListFilterRow(this, {
                colorRow: this.colorArr ? this.colorArr[f8] : [],
                fontWeightRow: this.fontWeightArr ? this.fontWeightArr[f8] : [],
                backgroundColorRow: this.backgroundColorArr ? this.backgroundColorArr[f8] : [],
                isBackgroundHoverRow: this.isBackgroundHover ? this.isBackgroundHover[f8] : [],
                filterRow: g8,
                onItemClick: (p8) => {
                  this.filterItemClick(f8, p8);
                },
                rowIndex: f8,
              }, undefined, i8, () => { },
                { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 723 });
              ViewPU.create(k8);
              let l8 = () => {
                return {
                  colorRow: this.colorArr ? this.colorArr[f8] : [],
                  fontWeightRow: this.fontWeightArr ? this.fontWeightArr[f8] : [],
                  backgroundColorRow: this.backgroundColorArr ? this.backgroundColorArr[f8] : [],
                  isBackgroundHoverRow: this.isBackgroundHover ? this.isBackgroundHover[f8] : [],
                  filterRow: g8,
                  onItemClick: (o8) => {
                    this.filterItemClick(f8, o8);
                  },
                  rowIndex: f8,
                };
              };
              k8.paramsGenerator_ = l8;
            }
            else {
              this.updateStateVarsOfChildByElmtId(i8, {
                colorRow: this.colorArr ? this.colorArr[f8] : [],
                fontWeightRow: this.fontWeightArr ? this.fontWeightArr[f8] : [],
                backgroundColorRow: this.backgroundColorArr ? this.backgroundColorArr[f8] : [],
                isBackgroundHoverRow: this.isBackgroundHover ? this.isBackgroundHover[f8] : [],
              });
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
        }
      };
      this.forEachUpdateFunction(a8, this.multiFilters, c8, undefined, true, false);
      if (!b8) {
        ForEach.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    ForEach.pop();
    Column.pop();
  }
  MultiLineFilter(z6 = null) {
    this.observeComponentCreation((s7, t7) => {
      ViewStackProcessor.StartGetAccessRecordingFor(s7);
      Column.create();
      Column.width(PERCENT_100);
      Column.onAreaChange((v7, w7) => {
        if (this.additionFilters != null) {
          this.filterDynamicHeight = parseInt(w7.height.toString(), 0) + LIST_ROW_HEIGHT + FILTER_TOP_PADDING;
        }
        else {
          this.filterDynamicHeight = parseInt(w7.height.toString(), 0) + FILTER_TOP_PADDING;
        }
        if (!this.isFloatBarShowWithoutAnimation && !this.isFloatShowAllFilterWithoutAnimation) {
          this.floatFilterPosition = -this.filterDynamicHeight;
        }
      });
      if (!t7) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((c7, d7) => {
      ViewStackProcessor.StartGetAccessRecordingFor(c7);
      ForEach.create();
      const e7 = (g7, h7) => {
        const i7 = g7;
        {
          this.observeComponentCreation((k7, l7) => {
            ViewStackProcessor.StartGetAccessRecordingFor(k7);
            if (l7) {
              let m7 = new MultiFilterRow(this, {
                colorRow: this.colorArr ? this.colorArr[h7] : [],
                fontWeightRow: this.fontWeightArr ? this.fontWeightArr[h7] : [],
                backgroundColorRow: this.backgroundColorArr ? this.backgroundColorArr[h7] : [],
                isBackgroundHoverRow: this.isBackgroundHover ? this.isBackgroundHover[h7] : [],
                arrowShowStateRow: this.downArrowShowState ? this.downArrowShowState[h7] : new ObservedBoolean(false),
                twoLineModeItemNumRow: this.twoLineModeItemNum ? this.twoLineModeItemNum[h7] : new ObservedNumber(0),
                twoLineModeItemNumRecordRow: this.twoLineModeItemNumRecord ? this.twoLineModeItemNumRecord[h7] :
                  new ObservedNumber(0),
                isArrowIconDown: this.isArrowIconDownArr ? this.isArrowIconDownArr[h7] : new ObservedBoolean(false),
                filterRow: i7,
                onItemClick: (r7) => {
                  this.filterItemClick(h7, r7);
                },
                rowIndex: h7,
              }, undefined, k7, () => { },
                { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 752 });
              ViewPU.create(m7);
              let n7 = () => {
                return {
                  colorRow: this.colorArr ? this.colorArr[h7] : [],
                  fontWeightRow: this.fontWeightArr ? this.fontWeightArr[h7] : [],
                  backgroundColorRow: this.backgroundColorArr ? this.backgroundColorArr[h7] : [],
                  isBackgroundHoverRow: this.isBackgroundHover ? this.isBackgroundHover[h7] : [],
                  arrowShowStateRow: this.downArrowShowState ? this.downArrowShowState[h7] : new ObservedBoolean(false),
                  twoLineModeItemNumRow: this.twoLineModeItemNum ? this.twoLineModeItemNum[h7] : new ObservedNumber(0),
                  twoLineModeItemNumRecordRow: this.twoLineModeItemNumRecord ? this.twoLineModeItemNumRecord[h7] :
                    new ObservedNumber(0),
                  isArrowIconDown: this.isArrowIconDownArr ? this.isArrowIconDownArr[h7] : new ObservedBoolean(false),
                  filterRow: i7,
                  onItemClick: (q7) => {
                    this.filterItemClick(h7, q7);
                  },
                  rowIndex: h7,
                };
              };
              m7.paramsGenerator_ = n7;
            }
            else {
              this.updateStateVarsOfChildByElmtId(k7, {
                colorRow: this.colorArr ? this.colorArr[h7] : [],
                fontWeightRow: this.fontWeightArr ? this.fontWeightArr[h7] : [],
                backgroundColorRow: this.backgroundColorArr ? this.backgroundColorArr[h7] : [],
                isBackgroundHoverRow: this.isBackgroundHover ? this.isBackgroundHover[h7] : [],
                arrowShowStateRow: this.downArrowShowState ? this.downArrowShowState[h7] : new ObservedBoolean(false),
                twoLineModeItemNumRow: this.twoLineModeItemNum ? this.twoLineModeItemNum[h7] : new ObservedNumber(0),
                twoLineModeItemNumRecordRow: this.twoLineModeItemNumRecord ? this.twoLineModeItemNumRecord[h7] :
                  new ObservedNumber(0),
                isArrowIconDown: this.isArrowIconDownArr ? this.isArrowIconDownArr[h7] : new ObservedBoolean(false),
              });
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
        }
      };
      this.forEachUpdateFunction(c7, this.multiFilters, e7, undefined, true, false);
      if (!d7) {
        ForEach.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    ForEach.pop();
    Column.pop();
  }
  additionItemClick(w6) {
    let x6 = this.multiFilters.length;
    if (this.selectedFilters && this.selectedFilters[x6].index !== w6) {
      if (this.selectedFilters[x6].index === -1) {
        this.additionColorArr && (this.additionColorArr[w6] = {
          'id': -1,
          'type': 10001,
          params: ['sys.color.ohos_id_color_text_primary_activated'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        });
        this.additionFontWeightArr && (this.additionFontWeightArr[w6] = FontWeight.Medium);
        this.selectedFilters[x6].value = this.additionFilters ? this.additionFilters.options[w6] : '';
        this.selectedFilters[x6].index = w6;
      }
      else {
        let y6 = this.selectedFilters[x6].index;
        this.additionColorArr && (this.additionColorArr[y6] = {
          'id': -1,
          'type': 10001,
          params: ['sys.color.ohos_id_color_text_primary'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        });
        this.additionColorArr && (this.additionColorArr[w6] = {
          'id': -1,
          'type': 10001,
          params: ['sys.color.ohos_id_color_text_primary_activated'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        });
        this.additionFontWeightArr && (this.additionFontWeightArr[y6] = FontWeight.Regular);
        this.additionFontWeightArr && (this.additionFontWeightArr[w6] = FontWeight.Medium);
        this.selectedFilters && (this.selectedFilters[x6].value = this.additionFilters ?
        this.additionFilters.options[w6] : '');
        this.selectedFilters && (this.selectedFilters[x6].index = w6);
      }
    }
    else {
      this.additionColorArr && (this.additionColorArr[w6] = {
        'id': -1,
        'type': 10001,
        params: ['sys.color.ohos_id_color_text_primary'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      });
      this.additionFontWeightArr && (this.additionFontWeightArr[w6] = FontWeight.Regular);
      this.selectedFilters && (this.selectedFilters[x6].value = '');
      this.selectedFilters && (this.selectedFilters[x6].index = -1);
    }
    if (this.selectedFilters) {
      this.onFilterChanged && this.onFilterChanged(this.selectedFilters);
    }
    this.colorRefresh = !this.colorRefresh;
    this.refreshFloatFilterBarText();
  }
  AdditionFilterList(t3 = null) {
    this.observeComponentCreation((v3, w3) => {
      ViewStackProcessor.StartGetAccessRecordingFor(v3);
      If.create();
      if (this.additionFilters && this.additionFilters.name && this.additionFilters.options &&
        this.additionFilters.options.length !== 0) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((u6, v6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(u6);
            Stack.create({ alignContent: Alignment.End });
            if (!v6) {
              Stack.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((s6, t6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(s6);
            Stack.create({ alignContent: Alignment.Start });
            if (!t6) {
              Stack.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((q6, r6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(q6);
            List.create();
            List.listDirection(Axis.Horizontal);
            List.scrollBar(BarState.Off);
            List.width(PERCENT_100);
            List.height(LIST_ROW_HEIGHT);
            if (!r6) {
              List.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          {
            const v5 = (o6, p6) => {
              ViewStackProcessor.StartGetAccessRecordingFor(o6);
              w5(o6, p6);
              if (!p6) {
                ListItem.pop();
              }
              ViewStackProcessor.StopGetAccessRecording();
            };
            const w5 = (m6, n6) => {
              ListItem.create(x5, true);
              ListItem.height(PERCENT_100);
              ListItem.margin({ left: -TEXT_HOT_AREA_WIDTH });
            };
            const x5 = (b6, c6) => {
              v5(b6, c6);
              this.updateFuncByElmtId.set(b6, v5);
              this.observeComponentCreation((k6, l6) => {
                ViewStackProcessor.StartGetAccessRecordingFor(k6);
                Row.create();
                if (!l6) {
                  Row.pop();
                }
                ViewStackProcessor.StopGetAccessRecording();
              });
              this.observeComponentCreation((i6, j6) => {
                ViewStackProcessor.StartGetAccessRecordingFor(i6);
                Text.create(this.additionFilters.name.toString());
                Text.fontSize({
                  'id': -1,
                  'type': 10002,
                  params: ['sys.float.ohos_id_text_size_body3'],
                  'bundleName': '__harDefaultBundleName__',
                  'moduleName': '__harDefaultModuleName__',
                });
                Text.fontColor({
                  'id': -1,
                  'type': 10001,
                  params: ['sys.color.ohos_id_color_text_secondary'],
                  'bundleName': '__harDefaultBundleName__',
                  'moduleName': '__harDefaultModuleName__',
                });
                Text.margin({ left: TEXT_HOT_AREA_WIDTH, right: TEXT_HOT_AREA_WIDTH });
                Text.padding({
                  left: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_max_padding_start'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                  }
                });
                if (!j6) {
                  Text.pop();
                }
                ViewStackProcessor.StopGetAccessRecording();
              });
              Text.pop();
              this.observeComponentCreation((g6, h6) => {
                ViewStackProcessor.StartGetAccessRecordingFor(g6);
                Row.create();
                Row.width(SEPARATOR_WIDTH);
                Row.height(SEPARATOR_HEIGHT);
                Row.backgroundColor({
                  'id': -1,
                  'type': 10001,
                  params: ['sys.color.ohos_id_color_list_separator'],
                  'bundleName': '__harDefaultBundleName__',
                  'moduleName': '__harDefaultModuleName__',
                });
                if (!h6) {
                  Row.pop();
                }
                ViewStackProcessor.StopGetAccessRecording();
              });
              Row.pop();
              Row.pop();
              ListItem.pop();
            };
            this.observeComponentCreation(v5);
            ListItem.pop();
          }
          this.observeComponentCreation((r4, s4) => {
            ViewStackProcessor.StartGetAccessRecordingFor(r4);
            ForEach.create();
            const t4 = (v4, w4) => {
              const x4 = v4;
              {
                const y4 = (t5, u5) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(t5);
                  z4(t5, u5);
                  if (!u5) {
                    ListItem.pop();
                  }
                  ViewStackProcessor.StopGetAccessRecording();
                };
                const z4 = (j5, k5) => {
                  ListItem.create(a5, true);
                  ListItem.height(PERCENT_100);
                  ListItem.backgroundColor(this.isAdditionBackgroundHover && this.isAdditionBackgroundHover[w4] ?
                    this.additionBackgroundColorArr ? this.additionBackgroundColorArr[w4] : '' : TRANS_COLOR);
                  ListItem.onHover((r5) => {
                    Context.animateTo({
                      curve: FRICTION_CUBIC_BEZIER,
                      duration: ANIMATION_DURATION_250,
                    }, () => {
                      if (r5) {
                        this.additionBackgroundColorArr &&
                          (this.additionBackgroundColorArr[w4] = {
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_hover'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__',
                          });
                        this.isAdditionBackgroundHover && (this.isAdditionBackgroundHover[w4] = true);
                      }
                      else {
                        this.isAdditionBackgroundHover && (this.isAdditionBackgroundHover[w4] = false);
                      }
                    });
                  });
                  ListItem.onTouch((o5) => {
                    if (o5.type === TouchType.Down) {
                      Context.animateTo({
                        curve: SHARP_CUBIC_BEZIER,
                        duration: ANIMATION_DURATION_100,
                      }, () => {
                        this.additionBackgroundColorArr &&
                          (this.additionBackgroundColorArr[w4] = {
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_click_effect'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__',
                          });
                        this.isAdditionBackgroundHover && (this.isAdditionBackgroundHover[w4] = true);
                      });
                    }
                    else if (o5.type === TouchType.Up) {
                      Context.animateTo({
                        curve: SHARP_CUBIC_BEZIER,
                        duration: ANIMATION_DURATION_100,
                      }, () => {
                        this.isAdditionBackgroundHover && (this.isAdditionBackgroundHover[w4] = false);
                      });
                    }
                  });
                  ListItem.focusable(true);
                  ViewStackProcessor.visualState('focused');
                  ListItem.border({
                    radius: {
                      'id': -1,
                      'type': 10002,
                      params: ['sys.float.ohos_id_corner_radius_clicked'],
                      'bundleName': '__harDefaultBundleName__',
                      'moduleName': '__harDefaultModuleName__',
                    },
                    width: FOCUS_BORDER_WIDTH,
                    color: {
                      'id': -1,
                      'type': 10001,
                      params: ['sys.color.ohos_id_color_focused_outline'],
                      'bundleName': '__harDefaultBundleName__',
                      'moduleName': '__harDefaultModuleName__',
                    },
                    style: BorderStyle.Solid,
                  });
                  ListItem.padding({
                    left: TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH,
                    right: TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH,
                  });
                  ViewStackProcessor.visualState('normal');
                  ListItem.border({
                    radius: {
                      'id': -1,
                      'type': 10002,
                      params: ['sys.float.ohos_id_corner_radius_clicked'],
                      'bundleName': '__harDefaultBundleName__',
                      'moduleName': '__harDefaultModuleName__',
                    },
                    width: 0,
                  });
                  ListItem.padding({ left: TEXT_HOT_AREA_WIDTH, right: TEXT_HOT_AREA_WIDTH });
                  ViewStackProcessor.visualState();
                  ListItem.onClick(() => {
                    this.additionItemClick(w4);
                  });
                  ListItem.tabIndex(w4 === 0 ? this.multiFilters.length : -1);
                };
                const a5 = (e5, f5) => {
                  y4(e5, f5);
                  this.updateFuncByElmtId.set(e5, y4);
                  this.observeComponentCreation((h5, i5) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(h5);
                    Text.create(x4.toString());
                    Text.fontSize({
                      'id': -1,
                      'type': 10002,
                      params: ['sys.float.ohos_id_text_size_body3'],
                      'bundleName': '__harDefaultBundleName__',
                      'moduleName': '__harDefaultModuleName__',
                    });
                    Text.fontColor(this.additionColorArr ? this.additionColorArr[w4] : '');
                    Text.fontWeight(this.additionFontWeightArr ? this.additionFontWeightArr[w4] : '');
                    Text.focusable(true);
                    if (!i5) {
                      Text.pop();
                    }
                    ViewStackProcessor.StopGetAccessRecording();
                  });
                  Text.pop();
                  ListItem.pop();
                };
                this.observeComponentCreation(y4);
                ListItem.pop();
              }
            };
            this.forEachUpdateFunction(r4, this.additionFilters.options, t4, undefined, true, false);
            if (!s4) {
              ForEach.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          ForEach.pop();
          List.pop();
          {
            this.observeComponentCreation((l4, m4) => {
              ViewStackProcessor.StartGetAccessRecordingFor(l4);
              if (m4) {
                let n4 = new GradientMask(this, {
                  x0: 0,
                  y0: LIST_ROW_HEIGHT / 2,
                  x1: GRADIENT_WIDTH,
                  y1: LIST_ROW_HEIGHT / 2,
                }, undefined, l4, () => { },
                  { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 910 });
                ViewPU.create(n4);
                let o4 = () => {
                  return {
                    x0: 0,
                    y0: LIST_ROW_HEIGHT / 2,
                    x1: GRADIENT_WIDTH,
                    y1: LIST_ROW_HEIGHT / 2,
                  };
                };
                n4.paramsGenerator_ = o4;
              }
              else {
                this.updateStateVarsOfChildByElmtId(l4, {});
              }
              ViewStackProcessor.StopGetAccessRecording();
            });
          }
          Stack.pop();
          {
            this.observeComponentCreation((e4, f4) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e4);
              if (f4) {
                let g4 = new GradientMask(this, {
                  x0: GRADIENT_WIDTH,
                  y0: LIST_ROW_HEIGHT / 2,
                  x1: 0,
                  y1: LIST_ROW_HEIGHT / 2,
                }, undefined, e4, () => { },
                  { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 917 });
                ViewPU.create(g4);
                let h4 = () => {
                  return {
                    x0: GRADIENT_WIDTH,
                    y0: LIST_ROW_HEIGHT / 2,
                    x1: 0,
                    y1: LIST_ROW_HEIGHT / 2,
                  };
                };
                g4.paramsGenerator_ = h4;
              }
              else {
                this.updateStateVarsOfChildByElmtId(e4, {});
              }
              ViewStackProcessor.StopGetAccessRecording();
            });
          }
          Stack.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!w3) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
  }
  FilterHeader(f3 = null) {
    this.observeComponentCreation((m3, n3) => {
      ViewStackProcessor.StartGetAccessRecordingFor(m3);
      Column.create();
      Column.padding({ top: FILTER_TOP_PADDING });
      Column.onVisibleAreaChange([0.0, 1.0], (p3, q3) => {
        if (q3 > 0) {
          this.isFloatShowAllFilter = false;
          this.isFloatShowAllFilterWithoutAnimation = false;
          this.isFloatBarShowWithoutAnimation = false;
          Context.animateTo({
            curve: INTER_POLATING_SPRING,
            onFinish: () => {
              if (!this.isFloatBarShowWithoutAnimation) {
                this.isFloatBarShow = false;
              }
            }
          }, () => {
            this.floatFilterBarHeight = 0;
          });
        }
        else {
          this.isFloatBarShow = true;
          this.isFloatBarShowWithoutAnimation = true;
          Context.animateTo({
            curve: INTER_POLATING_SPRING
          }, () => {
            this.floatFilterBarPosition = 0;
            this.floatFilterBarHeight = LIST_ROW_HEIGHT + FILTER_TOP_PADDING;
          });
        }
      });
      if (!n3) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((i3, j3) => {
      ViewStackProcessor.StartGetAccessRecordingFor(i3);
      If.create();
      if (this.filterType === FilterType.LIST_FILTER) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.ListFilter.bind(this)();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
          this.MultiLineFilter.bind(this)();
        });
      }
      if (!j3) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.AdditionFilterList.bind(this)();
    Column.pop();
  }
  FloatFilterHeader(q2 = null) {
    this.observeComponentCreation((d3, e3) => {
      ViewStackProcessor.StartGetAccessRecordingFor(d3);
      Column.create();
      Column.padding({ top: FILTER_TOP_PADDING });
      Column.width(PERCENT_100);
      Column.constraintSize({ maxHeight: '80%' });
      Column.clip(true);
      Column.backgroundColor({
        'id': -1,
        'type': 10001,
        params: ['sys.color.ohos_id_color_background'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      });
      Column.opacity(FLOAT_OPACITY);
      Column.backgroundBlurStyle(BlurStyle.Thin);
      Column.visibility(this.isFloatShowAllFilter ? Visibility.Visible : Visibility.Hidden);
      Column.position({ x: 0, y: this.floatFilterPosition });
      Column.zIndex(2);
      if (!e3) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((b3, c3) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b3);
      Scroll.create();
      if (!c3) {
        Scroll.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((z2, a3) => {
      ViewStackProcessor.StartGetAccessRecordingFor(z2);
      Column.create();
      if (!a3) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((v2, w2) => {
      ViewStackProcessor.StartGetAccessRecordingFor(v2);
      If.create();
      if (this.filterType === FilterType.LIST_FILTER) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.ListFilter.bind(this)();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
          this.MultiLineFilter.bind(this)();
        });
      }
      if (!w2) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.AdditionFilterList.bind(this)();
    Column.pop();
    Scroll.pop();
    Column.pop();
  }
  FloatFilterBar(m1 = null) {
    this.observeComponentCreation((o2, p2) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o2);
      Row.create();
      Row.width(PERCENT_100);
      Row.height(this.floatFilterBarHeight);
      Row.padding({ left: FOCUS_BORDER_WIDTH, right: FOCUS_BORDER_WIDTH });
      Row.backgroundColor({
        'id': -1,
        'type': 10001,
        params: ['sys.color.ohos_id_color_background'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      });
      Row.opacity(FLOAT_OPACITY);
      Row.clip(true);
      Row.backgroundBlurStyle(BlurStyle.Thin);
      Row.visibility(this.isFloatBarShow ? Visibility.Visible : Visibility.Hidden);
      Row.alignItems(VerticalAlign.Bottom);
      Row.position({ x: 0, y: this.floatFilterBarPosition });
      Row.zIndex(1);
      if (!p2) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((b2, c2) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b2);
      Column.create();
      Column.backgroundColor(this.isFloatArrowBgHover ? this.floatArrowBgColor : TRANS_COLOR);
      ViewStackProcessor.visualState('focused');
      Column.border({
        radius: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.ohos_id_corner_radius_clicked'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        },
        width: FOCUS_BORDER_WIDTH,
        color: {
          'id': -1,
          'type': 10001,
          params: ['sys.color.ohos_id_color_focused_outline'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        },
        style: BorderStyle.Solid
      });
      Column.width(ARROW_IMG_SIZE + FOCUS_BORDER_WIDTH * 2);
      ViewStackProcessor.visualState('normal');
      Column.border({
        radius: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.ohos_id_corner_radius_clicked'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        },
        width: 0
      });
      Column.width(ARROW_IMG_SIZE);
      ViewStackProcessor.visualState();
      Column.alignItems(HorizontalAlign.Center);
      Column.width(PERCENT_100);
      Column.height(LIST_ROW_HEIGHT);
      Column.onTouch((l2) => {
        if (l2.type === TouchType.Down) {
          Context.animateTo({
            curve: SHARP_CUBIC_BEZIER,
            duration: ANIMATION_DURATION_100,
          }, () => {
            this.floatArrowBgColor = {
              'id': -1,
              'type': 10001,
              params: ['sys.color.ohos_id_color_click_effect'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__',
            };
            this.isFloatArrowBgHover = true;
          });
        }
        else if (l2.type === TouchType.Up) {
          Context.animateTo({
            curve: SHARP_CUBIC_BEZIER,
            duration: ANIMATION_DURATION_100,
          }, () => {
            this.isFloatArrowBgHover = false;
          });
        }
      });
      Column.onClick(() => {
        Context.animateTo({
          duration: BAR_ANIMATION_DURATION,
          curve: SHARP_CUBIC_BEZIER,
        }, () => {
          this.isFloatBarShow = false;
          this.isFloatBarShowWithoutAnimation = false;
        });
        this.isFloatShowAllFilter = true;
        this.isFloatShowAllFilterWithoutAnimation = true;
        Context.animateTo({
          curve: INTER_POLATING_SPRING,
          onFinish: () => {
            this.floatFilterBarPosition = 0;
          },
        }, () => {
          this.floatFilterPosition = 0;
          this.floatFilterBarPosition = this.filterDynamicHeight;
        });
      });
      Column.onHover((g2) => {
        if (g2) {
          Context.animateTo({
            curve: FRICTION_CUBIC_BEZIER,
            duration: ANIMATION_DURATION_250,
          }, () => {
            this.floatArrowBgColor = {
              'id': -1,
              'type': 10001,
              params: ['sys.color.ohos_id_color_hover'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__',
            };
            this.isFloatArrowBgHover = true;
          });
        }
        else {
          Context.animateTo({
            curve: FRICTION_CUBIC_BEZIER,
            duration: ANIMATION_DURATION_250,
          }, () => {
            this.isFloatArrowBgHover = false;
          });
        }
      });
      if (!c2) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((z1, a2) => {
      ViewStackProcessor.StartGetAccessRecordingFor(z1);
      Row.create();
      Row.height(PERCENT_100);
      Row.alignItems(VerticalAlign.Center);
      if (!a2) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((x1, y1) => {
      ViewStackProcessor.StartGetAccessRecordingFor(x1);
      Row.create();
      Row.height(LIST_ROW_HEIGHT);
      Row.margin({ left: 8 });
      Row.focusable(true);
      if (!y1) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((v1, w1) => {
      ViewStackProcessor.StartGetAccessRecordingFor(v1);
      Text.create(this.floatFilterBarText);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.fontColor({
        'id': -1,
        'type': 10001,
        params: ['sys.color.ohos_id_color_text_primary_activated'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      });
      Text.fontSize({
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_text_size_body3'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      });
      Text.constraintSize({ maxWidth: '85%' });
      Text.maxLines(1);
      if (!w1) {
        Text.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Text.pop();
    this.observeComponentCreation((t1, u1) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t1);
      Image.create({
        'id': -1,
        'type': 20000,
        params: ['sys.media.ohos_ic_public_arrow_down'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      });
      Image.width(ARROW_IMG_SIZE);
      Image.height(ARROW_IMG_SIZE);
      Image.fillColor({
        'id': -1,
        'type': 10001,
        params: ['sys.color.ohos_id_color_text_primary_activated'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      });
      Image.focusable(true);
      if (!u1) {
        Image.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Row.pop();
    Row.pop();
    Column.pop();
    Row.pop();
  }
  initialRender() {
    this.observeComponentCreation((k1, l1) => {
      ViewStackProcessor.StartGetAccessRecordingFor(k1);
      Stack.create({ alignContent: Alignment.Top });
      Stack.clip(true);
      if (!l1) {
        Stack.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.FloatFilterBar.bind(this)();
    this.FloatFilterHeader.bind(this)();
    this.observeComponentCreation((i1, j1) => {
      ViewStackProcessor.StartGetAccessRecordingFor(i1);
      Column.create();
      Column.zIndex(0);
      if (!j1) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((b1, c1) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b1);
      List.create({ initialIndex: 0 });
      List.listDirection(Axis.Vertical);
      List.width(PERCENT_100);
      List.height(PERCENT_100);
      List.edgeEffect(EdgeEffect.Spring);
      List.onScroll((e1, f1) => {
        if (this.isFloatShowAllFilterWithoutAnimation && f1 === ScrollState.Scroll) {
          this.isFloatBarShowWithoutAnimation = true;
          this.isFloatShowAllFilterWithoutAnimation = false;
          Context.animateTo({
            duration: BAR_ANIMATION_DURATION,
            curve: SHARP_CUBIC_BEZIER,
          }, () => {
            this.isFloatBarShow = true;
          });
          Context.animateTo({
            curve: INTER_POLATING_SPRING,
            onFinish: () => {
              if (!this.isFloatShowAllFilterWithoutAnimation) {
                this.isFloatShowAllFilter = false;
              }
            },
          }, () => {
            this.floatFilterPosition = -this.filterDynamicHeight;
            this.floatFilterBarPosition = 0;
          });
        }
      });
      if (!c1) {
        List.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    {
      const p = (z, a1) => {
        ViewStackProcessor.StartGetAccessRecordingFor(z);
        q(z, a1);
        if (!a1) {
          ListItem.pop();
        }
        ViewStackProcessor.StopGetAccessRecording();
      };
      const q = (x, y) => {
        ListItem.create(r, true);
        ListItem.focusable(true);
      };
      const r = (v, w) => {
        p(v, w);
        this.updateFuncByElmtId.set(v, p);
        this.FilterHeader.bind(this)();
        ListItem.pop();
      };
      this.observeComponentCreation(p);
      ListItem.pop();
    }
    {
      const d = (n, o) => {
        ViewStackProcessor.StartGetAccessRecordingFor(n);
        e(n, o);
        if (!o) {
          ListItem.pop();
        }
        ViewStackProcessor.StopGetAccessRecording();
      };
      const e = (l, m) => {
        ListItem.create(f, true);
        ListItem.focusable(true);
      };
      const f = (j, k) => {
        d(j, k);
        this.updateFuncByElmtId.set(j, d);
        this.container.bind(this)();
        ListItem.pop();
      };
      this.observeComponentCreation(d);
      ListItem.pop();
    }
    List.pop();
    Column.pop();
    Stack.pop();
  }
  rerender() {
    this.updateDirtyElements();
  }
}

export default {
  Filter, FilterType
};