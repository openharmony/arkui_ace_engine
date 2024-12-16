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

var __decorate = (this && this.__decorate) || function (f13, g13, h13, i13) {
    var j13 = arguments.length,
        k13 = j13 < 3 ? g13 : i13 === null ? i13 = Object.getOwnPropertyDescriptor(g13, h13) : i13, l13;
    if (typeof Reflect === 'object' && typeof Reflect.decorate === 'function') {
        k13 = Reflect.decorate(f13, g13, h13, i13);
    } else {
        for (var m13 = f13.length - 1; m13 >= 0; m13--) {
            if (l13 = f13[m13]) {
                k13 = (j13 < 3 ? l13(k13) : j13 > 3 ? l13(g13, h13, k13) : l13(g13, h13)) || k13;
            }
        }
    }
    return j13 > 3 && k13 && Object.defineProperty(g13, h13, k13), k13;
};
if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {
    });
}
if (PUV2ViewBase.contextStack === undefined) {
    Reflect.set(PUV2ViewBase, 'contextStack', []);
}
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const curves = requireNativeModule('ohos.curves');
const measure = requireNapi('measure');
const hilog = requireNapi('hilog');
const TEXT_HOT_AREA_WIDTH = 8;
const LIST_ROW_HEIGHT = 40;
const ARROW_IMG_SIZE = 24;
const MULTI_LINE_PADDING = 24;
const BAR_ANIMATION_DURATION = 150;
const ARROW_ANIMATION_DURATION = 200;
const ANIMATION_DURATION_250 = 250;
const ANIMATION_DURATION_100 = 100;
const FILTER_TOP_PADDING = 8;
const FILTER_BAR_MARGIN = 8;
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
const MAX_FONT_SCALE = 2;
const ERROR_CODE = 0x3900;
const SYMBOL_SIZE = 24;
const MAX_SYMBOL_FONT_SCALE = 1.45;
const MIN_SYMBOL_FONT_SCALE = 1;
const DEFAULT_SYMBOL_FONT_SCALE = 1;

export var FilterType;
(function (e13) {
    e13[e13['MULTI_LINE_FILTER'] = 0] = 'MULTI_LINE_FILTER';
    e13[e13['LIST_FILTER'] = 1] = 'LIST_FILTER';
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
    constructor(d13) {
        this.value = d13;
    }
};
ObservedBoolean = __decorate([
    Observed
], ObservedBoolean);

export { ObservedBoolean };
let ObservedNumber = class ObservedNumber {
    constructor(c13) {
        this.value = c13;
    }
};
ObservedNumber = __decorate([
    Observed
], ObservedNumber);

class GradientMask extends ViewPU {
    constructor(w12, x12, y12, z12 = -1, a13 = undefined, b13) {
        super(w12, y12, z12, b13);
        if (typeof a13 === 'function') {
            this.paramsGenerator_ = a13;
        }
        this.x0 = 0;
        this.y0 = 0;
        this.x1 = 0;
        this.y1 = 0;
        this.settings = new RenderingContextSettings(true);
        this.context2D = new CanvasRenderingContext2D(this.settings);
        this.setInitiallyProvidedValue(x12);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(v12) {
        if (v12.x0 !== undefined) {
            this.x0 = v12.x0;
        }
        if (v12.y0 !== undefined) {
            this.y0 = v12.y0;
        }
        if (v12.x1 !== undefined) {
            this.x1 = v12.x1;
        }
        if (v12.y1 !== undefined) {
            this.y1 = v12.y1;
        }
        if (v12.settings !== undefined) {
            this.settings = v12.settings;
        }
        if (v12.context2D !== undefined) {
            this.context2D = v12.context2D;
        }
    }

    updateStateVars(u12) {
    }

    purgeVariableDependenciesOnElmtId(t12) {
    }

    aboutToBeDeleted() {
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    initialRender() {
        this.observeComponentCreation2((r12, s12) => {
            Column.create();
            Column.blendMode(BlendMode.DST_OUT);
            Column.width(GRADIENT_WIDTH);
            Column.height(LIST_ROW_HEIGHT);
        }, Column);
        this.observeComponentCreation2((o12, p12) => {
            Canvas.create(this.context2D);
            Canvas.width(GRADIENT_WIDTH);
            Canvas.height(LIST_ROW_HEIGHT);
            Canvas.onReady(() => {
                let q12 = this.context2D.createLinearGradient(this.x0, this.y0, this.x1, this.y1);
                q12.addColorStop(0.0, '#ffffffff');
                q12.addColorStop(1, '#00ffffff');
                this.context2D.fillStyle = q12;
                this.context2D.fillRect(0, 0, GRADIENT_WIDTH, LIST_ROW_HEIGHT);
            });
        }, Canvas);
        Canvas.pop();
        Column.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class ListFilterRow extends ViewPU {
    constructor(i12, j12, k12, l12 = -1, m12 = undefined, n12) {
        super(i12, k12, l12, n12);
        if (typeof m12 === 'function') {
            this.paramsGenerator_ = m12;
        }
        this.__colorRow = new SynchedPropertyNesedObjectPU(j12.colorRow, this, 'colorRow');
        this.__fontWeightRow = new SynchedPropertyNesedObjectPU(j12.fontWeightRow, this, 'fontWeightRow');
        this.__backgroundColorRow =
            new SynchedPropertyNesedObjectPU(j12.backgroundColorRow, this, 'backgroundColorRow');
        this.__isBackgroundHoverRow =
            new SynchedPropertyNesedObjectPU(j12.isBackgroundHoverRow, this, 'isBackgroundHoverRow');
        this.filterRow = { name: '', options: [] };
        this.onItemClick = () => {
        };
        this.rowIndex = 0;
        this.maxAppFontScale = 1;
        this.isFollowingSystemFontScale = false;
        this.setInitiallyProvidedValue(j12);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(h12) {
        this.__colorRow.set(h12.colorRow);
        this.__fontWeightRow.set(h12.fontWeightRow);
        this.__backgroundColorRow.set(h12.backgroundColorRow);
        this.__isBackgroundHoverRow.set(h12.isBackgroundHoverRow);
        if (h12.filterRow !== undefined) {
            this.filterRow = h12.filterRow;
        }
        if (h12.onItemClick !== undefined) {
            this.onItemClick = h12.onItemClick;
        }
        if (h12.rowIndex !== undefined) {
            this.rowIndex = h12.rowIndex;
        }
        if (h12.maxAppFontScale !== undefined) {
            this.maxAppFontScale = h12.maxAppFontScale;
        }
        if (h12.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = h12.isFollowingSystemFontScale;
        }
    }

    updateStateVars(g12) {
        this.__colorRow.set(g12.colorRow);
        this.__fontWeightRow.set(g12.fontWeightRow);
        this.__backgroundColorRow.set(g12.backgroundColorRow);
        this.__isBackgroundHoverRow.set(g12.isBackgroundHoverRow);
    }

    purgeVariableDependenciesOnElmtId(f12) {
        this.__colorRow.purgeDependencyOnElmtId(f12);
        this.__fontWeightRow.purgeDependencyOnElmtId(f12);
        this.__backgroundColorRow.purgeDependencyOnElmtId(f12);
        this.__isBackgroundHoverRow.purgeDependencyOnElmtId(f12);
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

    aboutToAppear() {
        try {
            let e12 = this.getUIContext();
            this.isFollowingSystemFontScale = e12.isFollowingSystemFontScale();
            this.maxAppFontScale = e12.getMaxFontScale();
        } catch (b12) {
            let c12 = b12.code;
            let d12 = b12.message;
            hilog.error(ERROR_CODE, 'Ace', `Failed to init fontsizescale info, cause, code: ${c12}, message: ${d12}`);
        }
    }

    updateFontScale() {
        let z11 = this.getUIContext();
        let a12 = z11.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(a12, this.maxAppFontScale);
    }

    initialRender() {
        this.observeComponentCreation2((x11, y11) => {
            Stack.create({ alignContent: Alignment.End });
            Stack.blendMode(BlendMode.SRC_OVER, BlendApplyType.OFFSCREEN);
        }, Stack);
        this.observeComponentCreation2((v11, w11) => {
            Stack.create({ alignContent: Alignment.Start });
        }, Stack);
        this.observeComponentCreation2((t11, u11) => {
            List.create();
            List.listDirection(Axis.Horizontal);
            List.scrollBar(BarState.Off);
            List.width(PERCENT_100);
            List.height(LIST_ROW_HEIGHT);
            List.align(Alignment.Start);
        }, List);
        this.observeComponentCreation2((p10, q10) => {
            ForEach.create();
            const b8 = (s10, t10) => {
                const u10 = s10;
                this.observeComponentCreation2((i11, j11) => {
                    If.create();
                    if (t10 === 0) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            {
                                const y8 = (r11, s11) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(r11);
                                    g9(r11, s11);
                                    if (!s11) {
                                        ListItem.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                };
                                const g9 = (p11, q11) => {
                                    ListItem.create(h9, true);
                                    ListItem.width({
                                        'id': -1,
                                        'type': 10002,
                                        params: ['sys.float.ohos_id_max_padding_start'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    });
                                    ListItem.height(LIST_ROW_HEIGHT);
                                };
                                const h9 = (n11, o11) => {
                                    y8(n11, o11);
                                    ListItem.pop();
                                };
                                this.observeComponentCreation2(g9, ListItem);
                                ListItem.pop();
                            }
                        });
                    } else {
                        this.ifElseBranchUpdateFunction(1, () => {
                        });
                    }
                }, If);
                If.pop();
                {
                    const v8 = (g11, h11) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(g11);
                        w8(g11, h11);
                        if (!h11) {
                            ListItem.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    };
                    const w8 = (c11, d11) => {
                        ListItem.create(x8, true);
                        ListItem.height(PERCENT_100);
                        ListItem.onClick(() => {
                            this.onItemClick(t10);
                        });
                        ListItem.focusable(true);
                        ViewStackProcessor.visualState('focused');
                        ListItem.border({
                            radius: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.ohos_id_corner_radius_clicked'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                            width: FOCUS_BORDER_WIDTH,
                            color: {
                                'id': -1,
                                'type': 10001,
                                params: ['sys.color.ohos_id_color_focused_outline'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                            style: BorderStyle.Solid
                        });
                        ListItem.padding({
                            start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH),
                            end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH)
                        });
                        ViewStackProcessor.visualState('normal');
                        ListItem.border({
                            radius: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.ohos_id_corner_radius_clicked'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                            width: 0
                        });
                        ListItem.padding({
                            start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH),
                            end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH)
                        });
                        ViewStackProcessor.visualState();
                        ListItem.backgroundColor(this.isBackgroundHoverRow[t10] ? this.backgroundColorRow[t10] :
                            TRANS_COLOR);
                        ListItem.onHover((f11) => {
                            Context.animateTo({
                                curve: FRICTION_CUBIC_BEZIER,
                                duration: ANIMATION_DURATION_250
                            }, () => {
                                if (f11) {
                                    this.backgroundColorRow[t10] = {
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_hover'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    };
                                    this.isBackgroundHoverRow[t10] = true;
                                } else {
                                    this.isBackgroundHoverRow[t10] = false;
                                }
                            });
                        });
                        ListItem.onTouch((e11) => {
                            if (e11.type === TouchType.Down) {
                                Context.animateTo({
                                    curve: SHARP_CUBIC_BEZIER,
                                    duration: ANIMATION_DURATION_100
                                }, () => {
                                    this.backgroundColorRow[t10] = {
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_click_effect'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    };
                                    this.isBackgroundHoverRow[t10] = true;
                                });
                            } else if (e11.type === TouchType.Up || e11.type === TouchType.Cancel) {
                                Context.animateTo({
                                    curve: SHARP_CUBIC_BEZIER,
                                    duration: ANIMATION_DURATION_100
                                }, () => {
                                    this.isBackgroundHoverRow[t10] = false;
                                });
                            }
                        });
                        ListItem.margin({ start: LengthMetrics.vp(t10 === 0 ? -TEXT_HOT_AREA_WIDTH : 0) });
                        ListItem.tabIndex(t10 === 0 ? this.rowIndex : -1);
                    };
                    const x8 = (y10, z10) => {
                        v8(y10, z10);
                        this.observeComponentCreation2((a11, b11) => {
                            Text.create(u10);
                            Text.fontSize({
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.ohos_id_text_size_body3'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            });
                            Text.minFontScale(1);
                            Text.maxFontScale(Math.min(this.updateFontScale(), MAX_FONT_SCALE));
                            Text.fontColor(this.colorRow[t10]);
                            Text.fontWeight(this.fontWeightRow[t10]);
                            Text.focusable(true);
                        }, Text);
                        Text.pop();
                        ListItem.pop();
                    };
                    this.observeComponentCreation2(w8, ListItem);
                    ListItem.pop();
                }
            };
            this.forEachUpdateFunction(p10, this.filterRow.options, b8, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        List.pop();
        {
            this.observeComponentCreation2((l10, m10) => {
                if (m10) {
                    let n10 = new GradientMask(this, {
                        x0: 0,
                        y0: LIST_ROW_HEIGHT / 2,
                        x1: GRADIENT_WIDTH,
                        y1: LIST_ROW_HEIGHT / 2
                    }, undefined, l10, () => {
                    }, { page: 'Filter/src/main/ets/components/MainPage.ets', line: 245, col: 9 });
                    ViewPU.create(n10);
                    let o6 = () => {
                        return {
                            x0: 0,
                            y0: LIST_ROW_HEIGHT / 2,
                            x1: GRADIENT_WIDTH,
                            y1: LIST_ROW_HEIGHT / 2
                        };
                    };
                    n10.paramsGenerator_ = o6;
                } else {
                    this.updateStateVarsOfChildByElmtId(l10, {});
                }
            }, { name: 'GradientMask' });
        }
        Stack.pop();
        {
            this.observeComponentCreation2((h10, i10) => {
                if (i10) {
                    let j10 = new GradientMask(this, {
                        x0: GRADIENT_WIDTH,
                        y0: LIST_ROW_HEIGHT / 2,
                        x1: 0,
                        y1: LIST_ROW_HEIGHT / 2
                    }, undefined, h10, () => {
                    }, { page: 'Filter/src/main/ets/components/MainPage.ets', line: 253, col: 7 });
                    ViewPU.create(j10);
                    let h6 = () => {
                        return {
                            x0: GRADIENT_WIDTH,
                            y0: LIST_ROW_HEIGHT / 2,
                            x1: 0,
                            y1: LIST_ROW_HEIGHT / 2
                        };
                    };
                    j10.paramsGenerator_ = h6;
                } else {
                    this.updateStateVarsOfChildByElmtId(h10, {});
                }
            }, { name: 'GradientMask' });
        }
        Stack.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class MultiFilterRow extends ViewPU {
    constructor(b10, c10, d10, e10 = -1, f10 = undefined, g10) {
        super(b10, d10, e10, g10);
        if (typeof f10 === 'function') {
            this.paramsGenerator_ = f10;
        }
        this.__colorRow = new SynchedPropertyNesedObjectPU(c10.colorRow, this, 'colorRow');
        this.__fontWeightRow = new SynchedPropertyNesedObjectPU(c10.fontWeightRow, this, 'fontWeightRow');
        this.__backgroundColorRow =
            new SynchedPropertyNesedObjectPU(c10.backgroundColorRow, this, 'backgroundColorRow');
        this.__isBackgroundHoverRow =
            new SynchedPropertyNesedObjectPU(c10.isBackgroundHoverRow, this, 'isBackgroundHoverRow');
        this.__twoLineModeItemNumRow =
            new SynchedPropertyNesedObjectPU(c10.twoLineModeItemNumRow, this, 'twoLineModeItemNumRow');
        this.__twoLineModeItemNumRecordRow =
            new SynchedPropertyNesedObjectPU(c10.twoLineModeItemNumRecordRow, this, 'twoLineModeItemNumRecordRow');
        this.__arrowShowStateRow = new SynchedPropertyNesedObjectPU(c10.arrowShowStateRow, this, 'arrowShowStateRow');
        this.__isArrowIconDown = new SynchedPropertyNesedObjectPU(c10.isArrowIconDown, this, 'isArrowIconDown');
        this.filterRow = null;
        this.onItemClick = () => {
        };
        this.__arrowBgColorRow = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_hover'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'arrowBgColorRow');
        this.__isArrowBgHoverRow = new ObservedPropertySimplePU(false, this, 'isArrowBgHoverRow');
        this.__fontSizeScale = new SynchedPropertyObjectOneWayPU(c10.fontSizeScale, this, 'fontSizeScale');
        this.__replaceEffect = new ObservedPropertySimplePU(0, this, 'replaceEffect');
        this.filterColumnWidth = 0;
        this.lastFilterColumnWidth = 0;
        this.rowIndex = 0;
        this.maxAppFontScale = 1;
        this.isFollowingSystemFontScale = false;
        this.setInitiallyProvidedValue(c10);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(a10) {
        this.__colorRow.set(a10.colorRow);
        this.__fontWeightRow.set(a10.fontWeightRow);
        this.__backgroundColorRow.set(a10.backgroundColorRow);
        this.__isBackgroundHoverRow.set(a10.isBackgroundHoverRow);
        this.__twoLineModeItemNumRow.set(a10.twoLineModeItemNumRow);
        this.__twoLineModeItemNumRecordRow.set(a10.twoLineModeItemNumRecordRow);
        this.__arrowShowStateRow.set(a10.arrowShowStateRow);
        this.__isArrowIconDown.set(a10.isArrowIconDown);
        if (a10.filterRow !== undefined) {
            this.filterRow = a10.filterRow;
        }
        if (a10.onItemClick !== undefined) {
            this.onItemClick = a10.onItemClick;
        }
        if (a10.arrowBgColorRow !== undefined) {
            this.arrowBgColorRow = a10.arrowBgColorRow;
        }
        if (a10.isArrowBgHoverRow !== undefined) {
            this.isArrowBgHoverRow = a10.isArrowBgHoverRow;
        }
        if (a10.replaceEffect !== undefined) {
            this.replaceEffect = a10.replaceEffect;
        }
        if (a10.filterColumnWidth !== undefined) {
            this.filterColumnWidth = a10.filterColumnWidth;
        }
        if (a10.lastFilterColumnWidth !== undefined) {
            this.lastFilterColumnWidth = a10.lastFilterColumnWidth;
        }
        if (a10.rowIndex !== undefined) {
            this.rowIndex = a10.rowIndex;
        }
        if (a10.maxAppFontScale !== undefined) {
            this.maxAppFontScale = a10.maxAppFontScale;
        }
        if (a10.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = a10.isFollowingSystemFontScale;
        }
    }

    updateStateVars(z9) {
        this.__colorRow.set(z9.colorRow);
        this.__fontWeightRow.set(z9.fontWeightRow);
        this.__backgroundColorRow.set(z9.backgroundColorRow);
        this.__isBackgroundHoverRow.set(z9.isBackgroundHoverRow);
        this.__twoLineModeItemNumRow.set(z9.twoLineModeItemNumRow);
        this.__twoLineModeItemNumRecordRow.set(z9.twoLineModeItemNumRecordRow);
        this.__arrowShowStateRow.set(z9.arrowShowStateRow);
        this.__isArrowIconDown.set(z9.isArrowIconDown);
        this.__fontSizeScale.reset(z9.fontSizeScale);
    }

    purgeVariableDependenciesOnElmtId(y9) {
        this.__colorRow.purgeDependencyOnElmtId(y9);
        this.__fontWeightRow.purgeDependencyOnElmtId(y9);
        this.__backgroundColorRow.purgeDependencyOnElmtId(y9);
        this.__isBackgroundHoverRow.purgeDependencyOnElmtId(y9);
        this.__twoLineModeItemNumRow.purgeDependencyOnElmtId(y9);
        this.__twoLineModeItemNumRecordRow.purgeDependencyOnElmtId(y9);
        this.__arrowShowStateRow.purgeDependencyOnElmtId(y9);
        this.__isArrowIconDown.purgeDependencyOnElmtId(y9);
        this.__arrowBgColorRow.purgeDependencyOnElmtId(y9);
        this.__isArrowBgHoverRow.purgeDependencyOnElmtId(y9);
        this.__fontSizeScale.purgeDependencyOnElmtId(y9);
        this.__replaceEffect.purgeDependencyOnElmtId(y9);
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
        this.__fontSizeScale.aboutToBeDeleted();
        this.__replaceEffect.aboutToBeDeleted();
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

    set arrowBgColorRow(x9) {
        this.__arrowBgColorRow.set(x9);
    }

    get isArrowBgHoverRow() {
        return this.__isArrowBgHoverRow.get();
    }

    set isArrowBgHoverRow(w9) {
        this.__isArrowBgHoverRow.set(w9);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(r10) {
        this.__fontSizeScale.set(r10);
    }

    get replaceEffect() {
        return this.__replaceEffect.get();
    }

    set replaceEffect(u9) {
        this.__replaceEffect.set(u9);
    }

    aboutToAppear() {
        try {
            let t9 = this.getUIContext();
            this.isFollowingSystemFontScale = t9.isFollowingSystemFontScale();
            this.maxAppFontScale = t9.getMaxFontScale();
        } catch (q9) {
            let r9 = q9.code;
            let s9 = q9.message;
            hilog.error(ERROR_CODE, 'Ace', `Failed to init fontsizescale info, cause, code: ${r9}, message: ${s9}`);
        }
    }

    updateFontScale() {
        let o9 = this.getUIContext();
        let p9 = o9.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(p9, this.maxAppFontScale);
    }

    calcMultiFilterRowItemNum() {
        let i9 = this.filterColumnWidth;
        let j9 = 0;
        let k9 = 1;
        if (this.filterRow) {
            for (let l9 = 0; l9 < this.filterRow.options.length; l9++) {
                let m9 = this.filterRow.options[l9];
                let n9 = measure.measureText({
                    textContent: m9,
                    fontSize: `${FILTER_FONT_SIZE * Math.min(this.updateFontScale(), MAX_FONT_SCALE)}vp`,
                });
                if (l9 === 0) {
                    continue;
                } else {
                    n9 += vp2px(TEXT_HOT_AREA_WIDTH * 2);
                }
                if (i9 - n9 >= 0) {
                    i9 -= n9;
                    j9 += 1;
                } else {
                    if (j9 === 0) {
                        j9++;
                        i9 = 0;
                    }
                    if (k9 === 1) {
                        k9 += 1;
                        i9 =
                            this.filterColumnWidth -
                            vp2px(ARROW_IMG_SIZE * (this.fontSizeScale ?? DEFAULT_SYMBOL_FONT_SCALE));
                        l9--;
                    } else {
                        break;
                    }
                }
            }
        }
        return j9;
    }

    DownAndUpArrow(b9 = null) {
        this.observeComponentCreation2((e9, f9) => {
            Row.create();
            Row.border({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_corner_radius_clicked'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                }
            });
            Row.height(LIST_ROW_HEIGHT);
            Row.backgroundColor(this.isArrowBgHoverRow ? this.arrowBgColorRow : TRANS_COLOR);
            Row.focusable(true);
            Row.visibility(this.arrowShowStateRow.value ? Visibility.Visible : Visibility.Hidden);
            Row.onHover((m15) => {
                Context.animateTo({
                    curve: FRICTION_CUBIC_BEZIER,
                    duration: ANIMATION_DURATION_250
                }, () => {
                    if (m15) {
                        this.arrowBgColorRow = {
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_hover'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        };
                        this.isArrowBgHoverRow = true;
                    } else {
                        this.isArrowBgHoverRow = false;
                    }
                });
            });
            Row.onTouch((l15) => {
                if (l15.type === TouchType.Down) {
                    Context.animateTo({
                        curve: SHARP_CUBIC_BEZIER,
                        duration: ANIMATION_DURATION_100
                    }, () => {
                        this.arrowBgColorRow = {
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_click_effect'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        };
                        this.isArrowBgHoverRow = true;
                    });
                } else if (l15.type === TouchType.Up || l15.type === TouchType.Cancel) {
                    Context.animateTo({
                        curve: SHARP_CUBIC_BEZIER,
                        duration: ANIMATION_DURATION_100
                    }, () => {
                        this.isArrowBgHoverRow = false;
                    });
                }
            });
            Row.onClick(() => {
                this.replaceEffect += 1;
                if (this.isArrowIconDown.value) {
                    this.isArrowIconDown.value = false;
                    this.arrowShowStateRow.value = false;
                    Context.animateTo({
                        curve: INTER_POLATING_SPRING,
                    }, () => {
                        this.twoLineModeItemNumRow.value = this.filterRow?.options.length;
                    });
                    Context.animateTo({
                        delay: 300,
                        duration: ARROW_ANIMATION_DURATION,
                        curve: SHARP_CUBIC_BEZIER
                    }, () => {
                        this.arrowShowStateRow.value = true;
                    });
                } else {
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
                        curve: SHARP_CUBIC_BEZIER
                    }, () => {
                        this.arrowShowStateRow.value = true;
                    });
                }
            });
        }, Row);
        this.observeComponentCreation2((c9, d9) => {
            SymbolGlyph.create(this.isArrowIconDown.value ? {
                'id': -1,
                'type': 40000,
                params: ['sys.symbol.chevron_down'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            } : {
                'id': -1,
                'type': 40000,
                params: ['sys.symbol.chevron_up'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            SymbolGlyph.fontSize(`${(this.fontSizeScale ?? DEFAULT_SYMBOL_FONT_SCALE) * SYMBOL_SIZE}vp`);
            SymbolGlyph.height(LIST_ROW_HEIGHT);
            SymbolGlyph.fontColor([{
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_tertiary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            }]);
            SymbolGlyph.symbolEffect(new ReplaceSymbolEffect(EffectScope.WHOLE), this.replaceEffect);
            SymbolGlyph.focusable(true);
            SymbolGlyph.draggable(false);
            ViewStackProcessor.visualState('focused');
            SymbolGlyph.border({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_corner_radius_clicked'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                width: FOCUS_BORDER_WIDTH,
                color: {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_focused_outline'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                style: BorderStyle.Solid
            });
            SymbolGlyph.offset({ x: -FOCUS_BORDER_WIDTH });
            ViewStackProcessor.visualState('normal');
            SymbolGlyph.border({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_corner_radius_clicked'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                width: 0
            });
            SymbolGlyph.offset({ x: 0 });
            ViewStackProcessor.visualState();
            SymbolGlyph.tabIndex(-1);
        }, SymbolGlyph);
        Row.pop();
    }

    initialRender() {
        this.observeComponentCreation2((z8, a9) => {
            Flex.create();
            Flex.width(PERCENT_100);
            Flex.padding({
                start: LengthMetrics.resource({
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_max_padding_start'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                }),
                end: LengthMetrics.resource({
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_max_padding_end'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                })
            });
        }, Flex);
        this.observeComponentCreation2((t8, u8) => {
            If.create();
            if (this.filterRow?.options && this.filterRow?.options.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((b15, d15) => {
                        Text.create(this.filterRow?.options[0]);
                        Text.height(LIST_ROW_HEIGHT);
                        Text.margin({ start: LengthMetrics.vp(-TEXT_HOT_AREA_WIDTH) });
                        Text.fontSize({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.ohos_id_text_size_body3'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Text.minFontScale(1);
                        Text.maxFontScale(Math.min(this.updateFontScale(), MAX_FONT_SCALE));
                        Text.maxLines(1);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.fontColor(this.colorRow[0]);
                        Text.fontWeight(this.fontWeightRow[0]);
                        Text.backgroundColor(this.isBackgroundHoverRow[0] ? this.backgroundColorRow[0] : TRANS_COLOR);
                        Text.onClick(() => {
                            this.onItemClick(0);
                        });
                        Text.focusable(true);
                        Text.onHover((k15) => {
                            Context.animateTo({
                                curve: FRICTION_CUBIC_BEZIER,
                                duration: ANIMATION_DURATION_250
                            }, () => {
                                if (k15) {
                                    this.backgroundColorRow[0] = {
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_hover'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    };
                                    this.isBackgroundHoverRow[0] = true;
                                } else {
                                    this.isBackgroundHoverRow[0] = false;
                                }
                            });
                        });
                        Text.onTouch((f15) => {
                            if (f15.type === TouchType.Down) {
                                Context.animateTo({
                                    curve: SHARP_CUBIC_BEZIER,
                                    duration: ANIMATION_DURATION_100
                                }, () => {
                                    this.backgroundColorRow[0] = {
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_click_effect'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    };
                                    this.isBackgroundHoverRow[0] = true;
                                });
                            } else if (f15.type === TouchType.Up || f15.type === TouchType.Cancel) {
                                Context.animateTo({
                                    curve: SHARP_CUBIC_BEZIER,
                                    duration: ANIMATION_DURATION_100
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
                                'moduleName': '__harDefaultModuleName__'
                            },
                            width: FOCUS_BORDER_WIDTH,
                            color: {
                                'id': -1,
                                'type': 10001,
                                params: ['sys.color.ohos_id_color_focused_outline'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                            style: BorderStyle.Solid
                        });
                        Text.padding({
                            start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH),
                            end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH)
                        });
                        ViewStackProcessor.visualState('normal');
                        Text.border({
                            radius: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.ohos_id_corner_radius_clicked'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                            width: 0
                        });
                        Text.padding({
                            start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH),
                            end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH)
                        });
                        ViewStackProcessor.visualState();
                        Text.constraintSize({ maxWidth: '50%' });
                        Text.flexShrink(0);
                        Text.tabIndex(this.rowIndex);
                    }, Text);
                    Text.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((n8, o8) => {
            Row.create();
            Row.width(PERCENT_100);
            Row.onAreaChange((p8, q8) => {
                this.filterColumnWidth = vp2px(parseInt(q8.width.toString(), 0));
                if (this.twoLineModeItemNumRow.value === 0) {
                    let s8 = this.calcMultiFilterRowItemNum();
                    this.twoLineModeItemNumRow.value = s8;
                    this.twoLineModeItemNumRecordRow.value = s8;
                    if (this.filterRow && s8 < this.filterRow.options.length - 1) {
                        this.arrowShowStateRow.value = true;
                    } else {
                        this.arrowShowStateRow.value = false;
                    }
                } else if (this.filterColumnWidth !== this.lastFilterColumnWidth) {
                    let r8 = this.calcMultiFilterRowItemNum();
                    if (this.filterRow && r8 < this.filterRow.options.length - 1) {
                        if (!this.arrowShowStateRow.value || this.isArrowIconDown.value) {
                            this.arrowShowStateRow.value = true;
                            this.isArrowIconDown.value = true;
                            this.twoLineModeItemNumRow.value = r8;
                        }
                    } else {
                        this.arrowShowStateRow.value = false;
                        this.isArrowIconDown.value = false;
                        this.twoLineModeItemNumRow.value = r8;
                    }
                    this.twoLineModeItemNumRecordRow.value = r8;
                }
                this.lastFilterColumnWidth = this.filterColumnWidth;
            });
        }, Row);
        this.observeComponentCreation2((l8, m8) => {
            Flex.create({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap });
        }, Flex);
        this.observeComponentCreation2((z7, a8) => {
            ForEach.create();
            const a6 = (c8, d8) => {
                const e8 = c8;
                this.observeComponentCreation2((f8, g8) => {
                    If.create();
                    if (d8 > 0) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((h8, i8) => {
                                Text.create(e8);
                                Text.transition(TransitionEffect.OPACITY);
                                Text.fontSize({
                                    'id': -1,
                                    'type': 10002,
                                    params: ['sys.float.ohos_id_text_size_body3'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                });
                                Text.minFontScale(1);
                                Text.maxFontScale(Math.min(this.updateFontScale(), MAX_FONT_SCALE));
                                Text.maxLines(1);
                                Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                                Text.height(LIST_ROW_HEIGHT);
                                Text.fontColor(this.colorRow[d8]);
                                Text.fontWeight(this.fontWeightRow[d8]);
                                Text.backgroundColor(this.isBackgroundHoverRow[d8] ?
                                this.backgroundColorRow[d8] : TRANS_COLOR);
                                Text.onClick(() => {
                                    this.onItemClick(d8);
                                });
                                Text.onHover((k8) => {
                                    Context.animateTo({
                                        curve: FRICTION_CUBIC_BEZIER,
                                        duration: ANIMATION_DURATION_250
                                    }, () => {
                                        if (k8) {
                                            this.backgroundColorRow[d8] = {
                                                'id': -1,
                                                'type': 10001,
                                                params: ['sys.color.ohos_id_color_hover'],
                                                'bundleName': '__harDefaultBundleName__',
                                                'moduleName': '__harDefaultModuleName__'
                                            };
                                            this.isBackgroundHoverRow[d8] = true;
                                        } else {
                                            this.isBackgroundHoverRow[d8] = false;
                                        }
                                    });
                                });
                                Text.onTouch((j8) => {
                                    if (j8.type === TouchType.Down) {
                                        Context.animateTo({
                                            curve: SHARP_CUBIC_BEZIER,
                                            duration: ANIMATION_DURATION_100
                                        }, () => {
                                            this.backgroundColorRow[d8] = {
                                                'id': -1,
                                                'type': 10001,
                                                params: ['sys.color.ohos_id_color_click_effect'],
                                                'bundleName': '__harDefaultBundleName__',
                                                'moduleName': '__harDefaultModuleName__'
                                            };
                                            this.isBackgroundHoverRow[d8] = true;
                                        });
                                    } else if (j8.type === TouchType.Up || j8.type === TouchType.Cancel) {
                                        Context.animateTo({
                                            curve: SHARP_CUBIC_BEZIER,
                                            duration: ANIMATION_DURATION_100
                                        }, () => {
                                            this.isBackgroundHoverRow[d8] = false;
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
                                        'moduleName': '__harDefaultModuleName__'
                                    },
                                    width: FOCUS_BORDER_WIDTH,
                                    color: {
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_focused_outline'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    },
                                    style: BorderStyle.Solid
                                });
                                Text.padding({
                                    start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH),
                                    end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH)
                                });
                                ViewStackProcessor.visualState('normal');
                                Text.border({
                                    radius: {
                                        'id': -1,
                                        'type': 10002,
                                        params: ['sys.float.ohos_id_corner_radius_clicked'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    },
                                    width: 0
                                });
                                Text.padding({
                                    start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH),
                                    end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH)
                                });
                                ViewStackProcessor.visualState();
                                Text.tabIndex(-1);
                            }, Text);
                            Text.pop();
                        });
                    } else {
                        this.ifElseBranchUpdateFunction(1, () => {
                        });
                    }
                }, If);
                If.pop();
            };
            this.forEachUpdateFunction(z7, this.filterRow?.options.slice(0, this.twoLineModeItemNumRow.value + 1), a6,
                undefined, true, false);
        }, ForEach);
        ForEach.pop();
        this.observeComponentCreation2((x7, y7) => {
            If.create();
            if (this.arrowShowStateRow.value) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.DownAndUpArrow.bind(this)();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Flex.pop();
        Row.pop();
        Flex.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export class Filter extends ViewPU {
    constructor(q7, r7, s7, t7 = -1, u7 = undefined, v7) {
        super(q7, s7, t7, v7);
        if (typeof u7 === 'function') {
            this.paramsGenerator_ = u7;
        }
        this.container = undefined;
        this.__multiFilters = new SynchedPropertyObjectOneWayPU(r7.multiFilters, this, 'multiFilters');
        this.__additionFilters = new SynchedPropertyObjectOneWayPU(r7.additionFilters, this, 'additionFilters');
        this.onFilterChanged = null;
        this.__filterType = new SynchedPropertySimpleOneWayPU(r7.filterType, this, 'filterType');
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
        this.maxAppFontScale = 1;
        this.isFollowingSystemFontScale = false;
        this.__fontSizeScale = new ObservedPropertyObjectPU(undefined, this, 'fontSizeScale');
        this.callbackId = undefined;
        this.callbacks = {
            onConfigurationUpdated: (w7) => {
                this.fontSizeScale = Math.min(this.updateFontScale(), MAX_SYMBOL_FONT_SCALE);
                this.fontSizeScale = Math.max(this.fontSizeScale, MIN_SYMBOL_FONT_SCALE);
            },
            onMemoryLevel() {
            }
        };
        this.setInitiallyProvidedValue(r7);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(p7) {
        if (p7.container !== undefined) {
            this.container = p7.container;
        }
        if (p7.multiFilters === undefined) {
            this.__multiFilters.set([]);
        }
        if (p7.additionFilters === undefined) {
            this.__additionFilters.set(null);
        }
        if (p7.onFilterChanged !== undefined) {
            this.onFilterChanged = p7.onFilterChanged;
        }
        if (p7.filterType === undefined) {
            this.__filterType.set(FilterType.LIST_FILTER);
        }
        if (p7.selectedFilters !== undefined) {
            this.selectedFilters = p7.selectedFilters;
        }
        if (p7.colorArr !== undefined) {
            this.colorArr = p7.colorArr;
        }
        if (p7.fontWeightArr !== undefined) {
            this.fontWeightArr = p7.fontWeightArr;
        }
        if (p7.backgroundColorArr !== undefined) {
            this.backgroundColorArr = p7.backgroundColorArr;
        }
        if (p7.isBackgroundHover !== undefined) {
            this.isBackgroundHover = p7.isBackgroundHover;
        }
        if (p7.floatArrowBgColor !== undefined) {
            this.floatArrowBgColor = p7.floatArrowBgColor;
        }
        if (p7.isFloatArrowBgHover !== undefined) {
            this.isFloatArrowBgHover = p7.isFloatArrowBgHover;
        }
        if (p7.isArrowIconDownArr !== undefined) {
            this.isArrowIconDownArr = p7.isArrowIconDownArr;
        }
        if (p7.additionColorArr !== undefined) {
            this.additionColorArr = p7.additionColorArr;
        }
        if (p7.additionFontWeightArr !== undefined) {
            this.additionFontWeightArr = p7.additionFontWeightArr;
        }
        if (p7.additionBackgroundColorArr !== undefined) {
            this.additionBackgroundColorArr = p7.additionBackgroundColorArr;
        }
        if (p7.isAdditionBackgroundHover !== undefined) {
            this.isAdditionBackgroundHover = p7.isAdditionBackgroundHover;
        }
        if (p7.colorRefresh !== undefined) {
            this.colorRefresh = p7.colorRefresh;
        }
        if (p7.isFloatBarShow !== undefined) {
            this.isFloatBarShow = p7.isFloatBarShow;
        }
        if (p7.isFloatBarShowWithoutAnimation !== undefined) {
            this.isFloatBarShowWithoutAnimation = p7.isFloatBarShowWithoutAnimation;
        }
        if (p7.isFloatShowAllFilter !== undefined) {
            this.isFloatShowAllFilter = p7.isFloatShowAllFilter;
        }
        if (p7.isFloatShowAllFilterWithoutAnimation !== undefined) {
            this.isFloatShowAllFilterWithoutAnimation = p7.isFloatShowAllFilterWithoutAnimation;
        }
        if (p7.floatFilterPosition !== undefined) {
            this.floatFilterPosition = p7.floatFilterPosition;
        }
        if (p7.floatFilterBarHeight !== undefined) {
            this.floatFilterBarHeight = p7.floatFilterBarHeight;
        }
        if (p7.floatFilterBarPosition !== undefined) {
            this.floatFilterBarPosition = p7.floatFilterBarPosition;
        }
        if (p7.filterDynamicHeight !== undefined) {
            this.filterDynamicHeight = p7.filterDynamicHeight;
        }
        if (p7.twoLineModeItemNum !== undefined) {
            this.twoLineModeItemNum = p7.twoLineModeItemNum;
        }
        if (p7.twoLineModeItemNumRecord !== undefined) {
            this.twoLineModeItemNumRecord = p7.twoLineModeItemNumRecord;
        }
        if (p7.downArrowShowState !== undefined) {
            this.downArrowShowState = p7.downArrowShowState;
        }
        if (p7.floatFilterBarText !== undefined) {
            this.floatFilterBarText = p7.floatFilterBarText;
        }
        if (p7.maxAppFontScale !== undefined) {
            this.maxAppFontScale = p7.maxAppFontScale;
        }
        if (p7.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = p7.isFollowingSystemFontScale;
        }
        if (p7.fontSizeScale !== undefined) {
            this.fontSizeScale = p7.fontSizeScale;
        }
        if (p7.callbackId !== undefined) {
            this.callbackId = p7.callbackId;
        }
        if (p7.callbacks !== undefined) {
            this.callbacks = p7.callbacks;
        }
    }

    updateStateVars(o7) {
        this.__multiFilters.reset(o7.multiFilters);
        this.__additionFilters.reset(o7.additionFilters);
        this.__filterType.reset(o7.filterType);
    }

    purgeVariableDependenciesOnElmtId(n7) {
        this.__multiFilters.purgeDependencyOnElmtId(n7);
        this.__additionFilters.purgeDependencyOnElmtId(n7);
        this.__filterType.purgeDependencyOnElmtId(n7);
        this.__colorArr.purgeDependencyOnElmtId(n7);
        this.__fontWeightArr.purgeDependencyOnElmtId(n7);
        this.__backgroundColorArr.purgeDependencyOnElmtId(n7);
        this.__isBackgroundHover.purgeDependencyOnElmtId(n7);
        this.__floatArrowBgColor.purgeDependencyOnElmtId(n7);
        this.__isFloatArrowBgHover.purgeDependencyOnElmtId(n7);
        this.__isArrowIconDownArr.purgeDependencyOnElmtId(n7);
        this.__additionColorArr.purgeDependencyOnElmtId(n7);
        this.__additionFontWeightArr.purgeDependencyOnElmtId(n7);
        this.__additionBackgroundColorArr.purgeDependencyOnElmtId(n7);
        this.__isAdditionBackgroundHover.purgeDependencyOnElmtId(n7);
        this.__colorRefresh.purgeDependencyOnElmtId(n7);
        this.__isFloatBarShow.purgeDependencyOnElmtId(n7);
        this.__isFloatShowAllFilter.purgeDependencyOnElmtId(n7);
        this.__floatFilterPosition.purgeDependencyOnElmtId(n7);
        this.__floatFilterBarHeight.purgeDependencyOnElmtId(n7);
        this.__floatFilterBarPosition.purgeDependencyOnElmtId(n7);
        this.__twoLineModeItemNum.purgeDependencyOnElmtId(n7);
        this.__twoLineModeItemNumRecord.purgeDependencyOnElmtId(n7);
        this.__downArrowShowState.purgeDependencyOnElmtId(n7);
        this.__floatFilterBarText.purgeDependencyOnElmtId(n7);
        this.__fontSizeScale.purgeDependencyOnElmtId(n7);
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
        this.__fontSizeScale.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get multiFilters() {
        return this.__multiFilters.get();
    }

    set multiFilters(m7) {
        this.__multiFilters.set(m7);
    }

    get additionFilters() {
        return this.__additionFilters.get();
    }

    set additionFilters(l7) {
        this.__additionFilters.set(l7);
    }

    get filterType() {
        return this.__filterType.get();
    }

    set filterType(k7) {
        this.__filterType.set(k7);
    }

    get colorArr() {
        return this.__colorArr.get();
    }

    set colorArr(j7) {
        this.__colorArr.set(j7);
    }

    get fontWeightArr() {
        return this.__fontWeightArr.get();
    }

    set fontWeightArr(i7) {
        this.__fontWeightArr.set(i7);
    }

    get backgroundColorArr() {
        return this.__backgroundColorArr.get();
    }

    set backgroundColorArr(h7) {
        this.__backgroundColorArr.set(h7);
    }

    get isBackgroundHover() {
        return this.__isBackgroundHover.get();
    }

    set isBackgroundHover(g7) {
        this.__isBackgroundHover.set(g7);
    }

    get floatArrowBgColor() {
        return this.__floatArrowBgColor.get();
    }

    set floatArrowBgColor(f7) {
        this.__floatArrowBgColor.set(f7);
    }

    get isFloatArrowBgHover() {
        return this.__isFloatArrowBgHover.get();
    }

    set isFloatArrowBgHover(e7) {
        this.__isFloatArrowBgHover.set(e7);
    }

    get isArrowIconDownArr() {
        return this.__isArrowIconDownArr.get();
    }

    set isArrowIconDownArr(d7) {
        this.__isArrowIconDownArr.set(d7);
    }

    get additionColorArr() {
        return this.__additionColorArr.get();
    }

    set additionColorArr(c7) {
        this.__additionColorArr.set(c7);
    }

    get additionFontWeightArr() {
        return this.__additionFontWeightArr.get();
    }

    set additionFontWeightArr(b7) {
        this.__additionFontWeightArr.set(b7);
    }

    get additionBackgroundColorArr() {
        return this.__additionBackgroundColorArr.get();
    }

    set additionBackgroundColorArr(a7) {
        this.__additionBackgroundColorArr.set(a7);
    }

    get isAdditionBackgroundHover() {
        return this.__isAdditionBackgroundHover.get();
    }

    set isAdditionBackgroundHover(z6) {
        this.__isAdditionBackgroundHover.set(z6);
    }

    get colorRefresh() {
        return this.__colorRefresh.get();
    }

    set colorRefresh(y6) {
        this.__colorRefresh.set(y6);
    }

    get isFloatBarShow() {
        return this.__isFloatBarShow.get();
    }

    set isFloatBarShow(x6) {
        this.__isFloatBarShow.set(x6);
    }

    get isFloatShowAllFilter() {
        return this.__isFloatShowAllFilter.get();
    }

    set isFloatShowAllFilter(w6) {
        this.__isFloatShowAllFilter.set(w6);
    }

    get floatFilterPosition() {
        return this.__floatFilterPosition.get();
    }

    set floatFilterPosition(v6) {
        this.__floatFilterPosition.set(v6);
    }

    get floatFilterBarHeight() {
        return this.__floatFilterBarHeight.get();
    }

    set floatFilterBarHeight(u6) {
        this.__floatFilterBarHeight.set(u6);
    }

    get floatFilterBarPosition() {
        return this.__floatFilterBarPosition.get();
    }

    set floatFilterBarPosition(t6) {
        this.__floatFilterBarPosition.set(t6);
    }

    get twoLineModeItemNum() {
        return this.__twoLineModeItemNum.get();
    }

    set twoLineModeItemNum(s6) {
        this.__twoLineModeItemNum.set(s6);
    }

    get twoLineModeItemNumRecord() {
        return this.__twoLineModeItemNumRecord.get();
    }

    set twoLineModeItemNumRecord(r6) {
        this.__twoLineModeItemNumRecord.set(r6);
    }

    get downArrowShowState() {
        return this.__downArrowShowState.get();
    }

    set downArrowShowState(q6) {
        this.__downArrowShowState.set(q6);
    }

    get floatFilterBarText() {
        return this.__floatFilterBarText.get();
    }

    set floatFilterBarText(p6) {
        this.__floatFilterBarText.set(p6);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(k10) {
        this.__fontSizeScale.set(k10);
    }

    textColor(m6, n6) {
        if (this.selectedFilters && this.selectedFilters.length > m6 &&
            this.selectedFilters[m6].index === n6) {
            return {
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_text_primary_activated'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        }
        return {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_text_primary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
    }

    aboutToAppear() {
        this.initParams();
        try {
            let l6 = this.getUIContext();
            this.isFollowingSystemFontScale = l6.isFollowingSystemFontScale();
            this.maxAppFontScale = l6.getMaxFontScale();
            this.fontSizeScale = Math.min(this.updateFontScale(), MAX_SYMBOL_FONT_SCALE);
            this.fontSizeScale = Math.max(this.fontSizeScale, MIN_SYMBOL_FONT_SCALE);
            this.callbackId = l6.getHostContext()?.getApplicationContext()?.on('environment', this.callbacks);
        } catch (i6) {
            let j6 = i6.code;
            let k6 = i6.message;
            hilog.error(ERROR_CODE, 'Ace', `Failed to init fontsizescale info, cause, code: ${j6}, message: ${k6}`);
        }
    }

    aboutToDisappear() {
        if (this.callbackId) {
            this.getUIContext()
                .getHostContext()
            ?.getApplicationContext()
            ?.off('environment', this.callbackId);
            this.callbackId = void (0);
        }
    }

    updateFontScale() {
        let f6 = this.getUIContext();
        let g6 = f6.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(g6, this.maxAppFontScale);
    }

    filterItemClick(b6, c6) {
        let d6 = this.multiFilters[b6].options[c6];
        if (this.selectedFilters && c6 !== this.selectedFilters[b6].index) {
            if (this.colorArr) {
                this.colorArr[b6][c6] = {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_text_primary_activated'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                };
                this.colorArr[b6][this.selectedFilters[b6].index] = {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_text_primary'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                };
            }
            if (this.fontWeightArr) {
                this.fontWeightArr[b6][c6] = FontWeight.Medium;
                this.fontWeightArr[b6][this.selectedFilters[b6].index] = FontWeight.Regular;
            }
            this.colorRefresh = !this.colorRefresh;
            this.selectedFilters[b6].value = d6;
            this.selectedFilters[b6].index = c6;
            let e6 = this.onFilterChanged;
            e6 && e6(this.selectedFilters);
        }
        this.refreshFloatFilterBarText();
    }

    refreshFloatFilterBarText() {
        this.floatFilterBarText = '';
        if (this.selectedFilters) {
            for (let v10 = 0; v10 < this.selectedFilters.length; v10++) {
                if (this.selectedFilters[v10].value !== null) {
                    if (typeof this.selectedFilters[v10].value !== 'string') {
                        this.selectedFilters[v10].value =
                            getContext()?.resourceManager?.getStringSync(this.selectedFilters[v10].value);
                    }
                    if (v10 === 0) {
                        this.floatFilterBarText += this.selectedFilters[v10].value;
                    } else {
                        this.floatFilterBarText += '/' + this.selectedFilters[v10].value;
                    }
                }
            }
        }
    }

    initParams() {
        if (!this.selectedFilters) {
            this.selectedFilters = [];
            for (let y5 of this.multiFilters) {
                let z5 = { name: y5.name, index: -1, value: '' };
                if (y5.options.length > 0) {
                    z5.index = 0;
                    z5.value = y5.options[0];
                }
                this.selectedFilters.push(z5);
            }
            if (this.additionFilters && this.additionFilters.name) {
                let x5 = { name: this.additionFilters.name, index: -1, value: '' };
                this.selectedFilters.push(x5);
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
                'moduleName': '__harDefaultModuleName__'
            };
            for (let r5 of this.multiFilters) {
                let s5 = new ResourceArray();
                let t5 = new FontWeightArray();
                let u5 = new ResourceArray();
                let v5 = new BooleanArray();
                for (let w5 of r5.options.keys()) {
                    if (w5 === 0) {
                        s5.push({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_text_primary_activated'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        t5.push(FontWeight.Medium);
                    } else {
                        s5.push({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_text_primary'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        t5.push(FontWeight.Regular);
                    }
                    u5.push({
                        'id': -1,
                        'type': 10001,
                        params: ['sys.color.ohos_id_color_hover'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__'
                    });
                }
                this.colorArr.push(s5);
                this.fontWeightArr.push(t5);
                this.backgroundColorArr.push(u5);
                this.isBackgroundHover.push(v5);
                this.isArrowIconDownArr.push(new ObservedBoolean(true));
            }
        }
        if (this.additionFilters && this.additionFilters.options) {
            this.additionColorArr = [];
            this.additionFontWeightArr = [];
            this.additionBackgroundColorArr = [];
            this.isAdditionBackgroundHover = [];
            for (let q5 = 0; q5 < this.additionFilters.options.length; q5++) {
                this.additionColorArr.push({
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_text_primary'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                });
                this.additionFontWeightArr.push(FontWeight.Regular);
                this.additionBackgroundColorArr.push({
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_hover'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                });
                this.isAdditionBackgroundHover.push(false);
            }
        }
        if (!this.twoLineModeItemNum) {
            this.twoLineModeItemNum = [];
            this.twoLineModeItemNumRecord = [];
            this.downArrowShowState = [];
            for (let p5 = 0; p5 < this.multiFilters.length; p5++) {
                this.twoLineModeItemNum.push(new ObservedNumber(this.multiFilters[p5].options.length));
                this.twoLineModeItemNumRecord.push(new ObservedNumber(this.multiFilters[p5].options.length));
                this.downArrowShowState.push(new ObservedBoolean(false));
            }
        }
    }

    ListFilter(y4 = null) {
        this.observeComponentCreation2((l5, m5) => {
            Column.create();
            Column.width(PERCENT_100);
            Column.align(Alignment.Start);
            Column.onAreaChange((n5, o5) => {
                if (!this.isFloatShowAllFilterWithoutAnimation && !this.isFloatBarShowWithoutAnimation) {
                    if (this.additionFilters !== null) {
                        this.filterDynamicHeight =
                            parseInt(o5.height.toString(), 0) + LIST_ROW_HEIGHT + FILTER_TOP_PADDING;
                    } else {
                        this.filterDynamicHeight = parseInt(o5.height.toString(), 0) + FILTER_TOP_PADDING;
                    }
                    this.floatFilterPosition = -this.filterDynamicHeight;
                }
            });
        }, Column);
        this.observeComponentCreation2((z4, a5) => {
            ForEach.create();
            const b5 = (c5, d5) => {
                const e5 = c5;
                {
                    this.observeComponentCreation2((f5, g5) => {
                        if (g5) {
                            let h5 = new ListFilterRow(this, {
                                colorRow: this.colorArr ? this.colorArr[d5] : [],
                                fontWeightRow: this.fontWeightArr ? this.fontWeightArr[d5] : [],
                                backgroundColorRow: this.backgroundColorArr ? this.backgroundColorArr[d5] : [],
                                isBackgroundHoverRow: this.isBackgroundHover ? this.isBackgroundHover[d5] : [],
                                filterRow: e5,
                                onItemClick: (k5) => {
                                    this.filterItemClick(d5, k5);
                                },
                                rowIndex: d5,
                            }, undefined, f5, () => {
                            }, { page: 'Filter/src/main/ets/components/MainPage.ets', line: 845, col: 9 });
                            ViewPU.create(h5);
                            let i5 = () => {
                                return {
                                    colorRow: this.colorArr ? this.colorArr[d5] : [],
                                    fontWeightRow: this.fontWeightArr ? this.fontWeightArr[d5] : [],
                                    backgroundColorRow: this.backgroundColorArr ? this.backgroundColorArr[d5] : [],
                                    isBackgroundHoverRow: this.isBackgroundHover ? this.isBackgroundHover[d5] : [],
                                    filterRow: e5,
                                    onItemClick: (j5) => {
                                        this.filterItemClick(d5, j5);
                                    },
                                    rowIndex: d5
                                };
                            };
                            h5.paramsGenerator_ = i5;
                        } else {
                            this.updateStateVarsOfChildByElmtId(f5, {
                                colorRow: this.colorArr ? this.colorArr[d5] : [],
                                fontWeightRow: this.fontWeightArr ? this.fontWeightArr[d5] : [],
                                backgroundColorRow: this.backgroundColorArr ? this.backgroundColorArr[d5] : [],
                                isBackgroundHoverRow: this.isBackgroundHover ? this.isBackgroundHover[d5] : []
                            });
                        }
                    }, { name: 'ListFilterRow' });
                }
            };
            this.forEachUpdateFunction(z4, this.multiFilters, b5, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Column.pop();
    }

    MultiLineFilter(h4 = null) {
        this.observeComponentCreation2((u4, v4) => {
            Column.create();
            Column.width(PERCENT_100);
            Column.onAreaChange((w4, x4) => {
                if (this.additionFilters !== null) {
                    this.filterDynamicHeight = parseInt(x4.height.toString(), 0) + LIST_ROW_HEIGHT + FILTER_TOP_PADDING;
                } else {
                    this.filterDynamicHeight = parseInt(x4.height.toString(), 0) + FILTER_TOP_PADDING;
                }
                if (!this.isFloatBarShowWithoutAnimation && !this.isFloatShowAllFilterWithoutAnimation) {
                    this.floatFilterPosition = -this.filterDynamicHeight;
                }
            });
        }, Column);
        this.observeComponentCreation2((i4, j4) => {
            ForEach.create();
            const k4 = (l4, m4) => {
                const n4 = l4;
                {
                    this.observeComponentCreation2((o4, p4) => {
                        if (p4) {
                            let q4 = new MultiFilterRow(this, {
                                colorRow: this.colorArr ? this.colorArr[m4] : [],
                                fontWeightRow: this.fontWeightArr ? this.fontWeightArr[m4] : [],
                                backgroundColorRow: this.backgroundColorArr ? this.backgroundColorArr[m4] : [],
                                isBackgroundHoverRow: this.isBackgroundHover ? this.isBackgroundHover[m4] : [],
                                arrowShowStateRow: this.downArrowShowState ? this.downArrowShowState[m4] :
                                    new ObservedBoolean(false),
                                twoLineModeItemNumRow: this.twoLineModeItemNum ? this.twoLineModeItemNum[m4] :
                                    new ObservedNumber(0),
                                twoLineModeItemNumRecordRow: this.twoLineModeItemNumRecord ?
                                this.twoLineModeItemNumRecord[m4] :
                                    new ObservedNumber(0),
                                isArrowIconDown: this.isArrowIconDownArr ? this.isArrowIconDownArr[m4] :
                                    new ObservedBoolean(false),
                                filterRow: n4,
                                onItemClick: (t4) => {
                                    this.filterItemClick(m4, t4);
                                },
                                rowIndex: m4,
                                fontSizeScale: this.fontSizeScale,
                            }, undefined, o4, () => {
                            }, { page: 'Filter/src/main/ets/components/MainPage.ets', line: 875, col: 9 });
                            ViewPU.create(q4);
                            let r4 = () => {
                                return {
                                    colorRow: this.colorArr ? this.colorArr[m4] : [],
                                    fontWeightRow: this.fontWeightArr ? this.fontWeightArr[m4] : [],
                                    backgroundColorRow: this.backgroundColorArr ? this.backgroundColorArr[m4] : [],
                                    isBackgroundHoverRow: this.isBackgroundHover ? this.isBackgroundHover[m4] : [],
                                    arrowShowStateRow: this.downArrowShowState ? this.downArrowShowState[m4] :
                                        new ObservedBoolean(false),
                                    twoLineModeItemNumRow: this.twoLineModeItemNum ? this.twoLineModeItemNum[m4] :
                                        new ObservedNumber(0),
                                    twoLineModeItemNumRecordRow: this.twoLineModeItemNumRecord ?
                                    this.twoLineModeItemNumRecord[m4] :
                                        new ObservedNumber(0),
                                    isArrowIconDown: this.isArrowIconDownArr ? this.isArrowIconDownArr[m4] :
                                        new ObservedBoolean(false),
                                    filterRow: n4,
                                    onItemClick: (s4) => {
                                        this.filterItemClick(m4, s4);
                                    },
                                    rowIndex: m4,
                                    fontSizeScale: this.fontSizeScale
                                };
                            };
                            q4.paramsGenerator_ = r4;
                        } else {
                            this.updateStateVarsOfChildByElmtId(o4, {
                                colorRow: this.colorArr ? this.colorArr[m4] : [],
                                fontWeightRow: this.fontWeightArr ? this.fontWeightArr[m4] : [],
                                backgroundColorRow: this.backgroundColorArr ? this.backgroundColorArr[m4] : [],
                                isBackgroundHoverRow: this.isBackgroundHover ? this.isBackgroundHover[m4] : [],
                                arrowShowStateRow: this.downArrowShowState ? this.downArrowShowState[m4] :
                                    new ObservedBoolean(false),
                                twoLineModeItemNumRow: this.twoLineModeItemNum ? this.twoLineModeItemNum[m4] :
                                    new ObservedNumber(0),
                                twoLineModeItemNumRecordRow: this.twoLineModeItemNumRecord ?
                                this.twoLineModeItemNumRecord[m4] :
                                    new ObservedNumber(0),
                                isArrowIconDown: this.isArrowIconDownArr ? this.isArrowIconDownArr[m4] :
                                    new ObservedBoolean(false),
                                fontSizeScale: this.fontSizeScale
                            });
                        }
                    }, { name: 'MultiFilterRow' });
                }
            };
            this.forEachUpdateFunction(i4, this.multiFilters, k4, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Column.pop();
    }

    additionItemClick(e4) {
        let f4 = this.multiFilters.length;
        if (this.selectedFilters && this.selectedFilters[f4].index !== e4) {
            if (this.selectedFilters[f4].index === -1) {
                this.additionColorArr && (this.additionColorArr[e4] = {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_text_primary_activated'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                });
                this.additionFontWeightArr && (this.additionFontWeightArr[e4] = FontWeight.Medium);
                this.selectedFilters[f4].value = this.additionFilters ? this.additionFilters.options[e4] : '';
                this.selectedFilters[f4].index = e4;
            } else {
                let g4 = this.selectedFilters[f4].index;
                this.additionColorArr && (this.additionColorArr[g4] = {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_text_primary'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                });
                this.additionColorArr && (this.additionColorArr[e4] = {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_text_primary_activated'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                });
                this.additionFontWeightArr && (this.additionFontWeightArr[g4] = FontWeight.Regular);
                this.additionFontWeightArr && (this.additionFontWeightArr[e4] = FontWeight.Medium);
                this.selectedFilters && (this.selectedFilters[f4].value = this.additionFilters ?
                this.additionFilters.options[e4] : '');
                this.selectedFilters && (this.selectedFilters[f4].index = e4);
            }
        } else {
            this.additionColorArr && (this.additionColorArr[e4] = {
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_text_primary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            this.additionFontWeightArr && (this.additionFontWeightArr[e4] = FontWeight.Regular);
            this.selectedFilters && (this.selectedFilters[f4].value = '');
            this.selectedFilters && (this.selectedFilters[f4].index = -1);
        }
        if (this.selectedFilters) {
            this.onFilterChanged && this.onFilterChanged(this.selectedFilters);
        }
        this.colorRefresh = !this.colorRefresh;
        this.refreshFloatFilterBarText();
    }

    AdditionFilterList(f2 = null) {
        this.observeComponentCreation2((g2, h2) => {
            If.create();
            if (this.additionFilters && this.additionFilters.name && this.additionFilters.options &&
                this.additionFilters.options.length !== 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((c4, d4) => {
                        Stack.create({ alignContent: Alignment.End });
                        Stack.blendMode(BlendMode.SRC_OVER, BlendApplyType.OFFSCREEN);
                    }, Stack);
                    this.observeComponentCreation2((a4, b4) => {
                        Stack.create({ alignContent: Alignment.Start });
                    }, Stack);
                    this.observeComponentCreation2((y3, z3) => {
                        List.create();
                        List.listDirection(Axis.Horizontal);
                        List.scrollBar(BarState.Off);
                        List.width(PERCENT_100);
                        List.height(LIST_ROW_HEIGHT);
                    }, List);
                    {
                        const j3 = (w3, x3) => {
                            ViewStackProcessor.StartGetAccessRecordingFor(w3);
                            k3(w3, x3);
                            if (!x3) {
                                ListItem.pop();
                            }
                            ViewStackProcessor.StopGetAccessRecording();
                        };
                        const k3 = (u3, v3) => {
                            ListItem.create(l3, true);
                            ListItem.height(PERCENT_100);
                            ListItem.margin({ start: LengthMetrics.vp(-TEXT_HOT_AREA_WIDTH) });
                        };
                        const l3 = (m3, n3) => {
                            j3(m3, n3);
                            this.observeComponentCreation2((s3, t3) => {
                                Row.create();
                            }, Row);
                            this.observeComponentCreation2((q3, r3) => {
                                Text.create(this.additionFilters.name);
                                Text.fontSize({
                                    'id': -1,
                                    'type': 10002,
                                    params: ['sys.float.ohos_id_text_size_body3'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                });
                                Text.minFontScale(1);
                                Text.maxFontScale(Math.min(this.updateFontScale(), MAX_FONT_SCALE));
                                Text.fontColor({
                                    'id': -1,
                                    'type': 10001,
                                    params: ['sys.color.ohos_id_color_text_secondary'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                });
                                Text.margin({
                                    start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH),
                                    end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH)
                                });
                                Text.padding({
                                    start: LengthMetrics.resource({
                                        'id': -1,
                                        'type': 10002,
                                        params: ['sys.float.ohos_id_max_padding_start'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    })
                                });
                            }, Text);
                            Text.pop();
                            this.observeComponentCreation2((o3, p3) => {
                                Row.create();
                                Row.width(SEPARATOR_WIDTH);
                                Row.height(SEPARATOR_HEIGHT);
                                Row.backgroundColor({
                                    'id': -1,
                                    'type': 10001,
                                    params: ['sys.color.ohos_id_color_list_separator'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                });
                            }, Row);
                            Row.pop();
                            Row.pop();
                            ListItem.pop();
                        };
                        this.observeComponentCreation2(k3, ListItem);
                        ListItem.pop();
                    }
                    this.observeComponentCreation2((q2, r2) => {
                        ForEach.create();
                        const s2 = (t2, u2) => {
                            const v2 = t2;
                            {
                                const w2 = (h3, i3) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(h3);
                                    x2(h3, i3);
                                    if (!i3) {
                                        ListItem.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                };
                                const x2 = (d3, e3) => {
                                    ListItem.create(y2, true);
                                    ListItem.height(PERCENT_100);
                                    ListItem.backgroundColor(this.isAdditionBackgroundHover &&
                                    this.isAdditionBackgroundHover[u2] ?
                                        this.additionBackgroundColorArr ? this.additionBackgroundColorArr[u2] : '' :
                                        TRANS_COLOR);
                                    ListItem.onHover((g3) => {
                                        Context.animateTo({
                                            curve: FRICTION_CUBIC_BEZIER,
                                            duration: ANIMATION_DURATION_250
                                        }, () => {
                                            if (g3) {
                                                this.additionBackgroundColorArr &&
                                                    (this.additionBackgroundColorArr[u2] = {
                                                        'id': -1,
                                                        'type': 10001,
                                                        params: ['sys.color.ohos_id_color_hover'],
                                                        'bundleName': '__harDefaultBundleName__',
                                                        'moduleName': '__harDefaultModuleName__'
                                                    });
                                                this.isAdditionBackgroundHover &&
                                                    (this.isAdditionBackgroundHover[u2] = true);
                                            } else {
                                                this.isAdditionBackgroundHover &&
                                                    (this.isAdditionBackgroundHover[u2] = false);
                                            }
                                        });
                                    });
                                    ListItem.onTouch((f3) => {
                                        if (f3.type === TouchType.Down) {
                                            Context.animateTo({
                                                curve: SHARP_CUBIC_BEZIER,
                                                duration: ANIMATION_DURATION_100
                                            }, () => {
                                                this.additionBackgroundColorArr &&
                                                    (this.additionBackgroundColorArr[u2] = {
                                                        'id': -1,
                                                        'type': 10001,
                                                        params: ['sys.color.ohos_id_color_click_effect'],
                                                        'bundleName': '__harDefaultBundleName__',
                                                        'moduleName': '__harDefaultModuleName__'
                                                    });
                                                this.isAdditionBackgroundHover &&
                                                    (this.isAdditionBackgroundHover[u2] = true);
                                            });
                                        } else if (f3.type === TouchType.Up || f3.type === TouchType.Cancel) {
                                            Context.animateTo({
                                                curve: SHARP_CUBIC_BEZIER,
                                                duration: ANIMATION_DURATION_100
                                            }, () => {
                                                this.isAdditionBackgroundHover &&
                                                    (this.isAdditionBackgroundHover[u2] = false);
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
                                            'moduleName': '__harDefaultModuleName__'
                                        },
                                        width: FOCUS_BORDER_WIDTH,
                                        color: {
                                            'id': -1,
                                            'type': 10001,
                                            params: ['sys.color.ohos_id_color_focused_outline'],
                                            'bundleName': '__harDefaultBundleName__',
                                            'moduleName': '__harDefaultModuleName__'
                                        },
                                        style: BorderStyle.Solid
                                    });
                                    ListItem.padding({
                                        start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH),
                                        end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH)
                                    });
                                    ViewStackProcessor.visualState('normal');
                                    ListItem.border({
                                        radius: {
                                            'id': -1,
                                            'type': 10002,
                                            params: ['sys.float.ohos_id_corner_radius_clicked'],
                                            'bundleName': '__harDefaultBundleName__',
                                            'moduleName': '__harDefaultModuleName__'
                                        },
                                        width: 0
                                    });
                                    ListItem.padding({
                                        start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH),
                                        end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH)
                                    });
                                    ViewStackProcessor.visualState();
                                    ListItem.onClick(() => {
                                        this.additionItemClick(u2);
                                    });
                                    ListItem.tabIndex(u2 === 0 ? this.multiFilters.length : -1);
                                };
                                const y2 = (z2, a3) => {
                                    w2(z2, a3);
                                    this.observeComponentCreation2((b3, c3) => {
                                        Text.create(v2);
                                        Text.fontSize({
                                            'id': -1,
                                            'type': 10002,
                                            params: ['sys.float.ohos_id_text_size_body3'],
                                            'bundleName': '__harDefaultBundleName__',
                                            'moduleName': '__harDefaultModuleName__'
                                        });
                                        Text.minFontScale(1);
                                        Text.maxFontScale(Math.min(this.updateFontScale(), MAX_FONT_SCALE));
                                        Text.fontColor(this.additionColorArr ? this.additionColorArr[u2] : '');
                                        Text.fontWeight(this.additionFontWeightArr ? this.additionFontWeightArr[u2] :
                                            '');
                                        Text.focusable(true);
                                    }, Text);
                                    Text.pop();
                                    ListItem.pop();
                                };
                                this.observeComponentCreation2(x2, ListItem);
                                ListItem.pop();
                            }
                        };
                        this.forEachUpdateFunction(q2, this.additionFilters.options, s2, undefined, true, false);
                    }, ForEach);
                    ForEach.pop();
                    List.pop();
                    {
                        this.observeComponentCreation2((m2, n2) => {
                            if (n2) {
                                let o2 = new GradientMask(this, {
                                    x0: 0,
                                    y0: LIST_ROW_HEIGHT / 2,
                                    x1: GRADIENT_WIDTH,
                                    y1: LIST_ROW_HEIGHT / 2
                                }, undefined, m2, () => {
                                }, { page: 'Filter/src/main/ets/components/MainPage.ets', line: 1039, col: 11 });
                                ViewPU.create(o2);
                                let p2 = () => {
                                    return {
                                        x0: 0,
                                        y0: LIST_ROW_HEIGHT / 2,
                                        x1: GRADIENT_WIDTH,
                                        y1: LIST_ROW_HEIGHT / 2
                                    };
                                };
                                o2.paramsGenerator_ = p2;
                            } else {
                                this.updateStateVarsOfChildByElmtId(m2, {});
                            }
                        }, { name: 'GradientMask' });
                    }
                    Stack.pop();
                    {
                        this.observeComponentCreation2((i2, j2) => {
                            if (j2) {
                                let k2 = new GradientMask(this, {
                                    x0: GRADIENT_WIDTH,
                                    y0: LIST_ROW_HEIGHT / 2,
                                    x1: 0,
                                    y1: LIST_ROW_HEIGHT / 2
                                }, undefined, i2, () => {
                                }, { page: 'Filter/src/main/ets/components/MainPage.ets', line: 1047, col: 9 });
                                ViewPU.create(k2);
                                let l2 = () => {
                                    return {
                                        x0: GRADIENT_WIDTH,
                                        y0: LIST_ROW_HEIGHT / 2,
                                        x1: 0,
                                        y1: LIST_ROW_HEIGHT / 2
                                    };
                                };
                                k2.paramsGenerator_ = l2;
                            } else {
                                this.updateStateVarsOfChildByElmtId(i2, {});
                            }
                        }, { name: 'GradientMask' });
                    }
                    Stack.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }

    FilterHeader(y1 = null) {
        this.observeComponentCreation2((b2, c2) => {
            Column.create();
            Column.padding({ top: FILTER_TOP_PADDING });
            Column.onVisibleAreaChange([0.0, 1.0], (d2, e2) => {
                if (e2 > 0) {
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
                } else {
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
        }, Column);
        this.observeComponentCreation2((z1, a2) => {
            If.create();
            if (this.filterType === FilterType.LIST_FILTER) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.ListFilter.bind(this)();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.MultiLineFilter.bind(this)();
                });
            }
        }, If);
        If.pop();
        this.AdditionFilterList.bind(this)();
        Column.pop();
    }

    FloatFilterHeader(p1 = null) {
        this.observeComponentCreation2((w1, x1) => {
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
                'moduleName': '__harDefaultModuleName__'
            });
            Column.opacity(FLOAT_OPACITY);
            Column.backgroundBlurStyle(BlurStyle.Thin);
            Column.visibility(this.isFloatShowAllFilter ? Visibility.Visible : Visibility.Hidden);
            Column.position({ x: 0, y: this.floatFilterPosition });
            Column.zIndex(2);
        }, Column);
        this.observeComponentCreation2((u1, v1) => {
            Scroll.create();
        }, Scroll);
        this.observeComponentCreation2((s1, t1) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((q1, r1) => {
            If.create();
            if (this.filterType === FilterType.LIST_FILTER) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.ListFilter.bind(this)();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.MultiLineFilter.bind(this)();
                });
            }
        }, If);
        If.pop();
        this.AdditionFilterList.bind(this)();
        Column.pop();
        Scroll.pop();
        Column.pop();
    }

    FloatFilterBar(a1 = null) {
        this.observeComponentCreation2((n1, o1) => {
            Row.create();
            Row.width(PERCENT_100);
            Row.height(this.floatFilterBarHeight);
            Row.padding({ start: LengthMetrics.vp(FOCUS_BORDER_WIDTH), end: LengthMetrics.vp(FOCUS_BORDER_WIDTH) });
            Row.backgroundColor({
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_background'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Row.opacity(FLOAT_OPACITY);
            Row.clip(true);
            Row.backgroundBlurStyle(BlurStyle.Thin);
            Row.visibility(this.isFloatBarShow ? Visibility.Visible : Visibility.Hidden);
            Row.alignItems(VerticalAlign.Bottom);
            Row.position({ x: 0, y: this.floatFilterBarPosition });
            Row.zIndex(1);
        }, Row);
        this.observeComponentCreation2((j1, k1) => {
            Column.create();
            Column.backgroundColor(this.isFloatArrowBgHover ? this.floatArrowBgColor : TRANS_COLOR);
            ViewStackProcessor.visualState('focused');
            Column.border({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_corner_radius_clicked'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                width: FOCUS_BORDER_WIDTH,
                color: {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_focused_outline'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                style: BorderStyle.Solid
            });
            ViewStackProcessor.visualState('normal');
            Column.border({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_corner_radius_clicked'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                width: 0
            });
            ViewStackProcessor.visualState();
            Column.alignItems(HorizontalAlign.Center);
            Column.width(PERCENT_100);
            Column.height(LIST_ROW_HEIGHT);
            Column.onTouch((m1) => {
                if (m1.type === TouchType.Down) {
                    Context.animateTo({
                        curve: SHARP_CUBIC_BEZIER,
                        duration: ANIMATION_DURATION_100
                    }, () => {
                        this.floatArrowBgColor = {
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_click_effect'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        };
                        this.isFloatArrowBgHover = true;
                    });
                } else if (m1.type === TouchType.Up || m1.type === TouchType.Cancel) {
                    Context.animateTo({
                        curve: SHARP_CUBIC_BEZIER,
                        duration: ANIMATION_DURATION_100
                    }, () => {
                        this.isFloatArrowBgHover = false;
                    });
                }
            });
            Column.onClick(() => {
                Context.animateTo({
                    duration: BAR_ANIMATION_DURATION,
                    curve: SHARP_CUBIC_BEZIER
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
                    }
                }, () => {
                    this.floatFilterPosition = 0;
                    this.floatFilterBarPosition = this.filterDynamicHeight;
                });
            });
            Column.onHover((l1) => {
                if (l1) {
                    Context.animateTo({
                        curve: FRICTION_CUBIC_BEZIER,
                        duration: ANIMATION_DURATION_250
                    }, () => {
                        this.floatArrowBgColor = {
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_hover'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        };
                        this.isFloatArrowBgHover = true;
                    });
                } else {
                    Context.animateTo({
                        curve: FRICTION_CUBIC_BEZIER,
                        duration: ANIMATION_DURATION_250
                    }, () => {
                        this.isFloatArrowBgHover = false;
                    });
                }
            });
        }, Column);
        this.observeComponentCreation2((h1, i1) => {
            Row.create();
            Row.height(PERCENT_100);
            Row.alignItems(VerticalAlign.Center);
        }, Row);
        this.observeComponentCreation2((f1, g1) => {
            Row.create();
            Row.height(LIST_ROW_HEIGHT);
            Row.margin({ start: LengthMetrics.vp(FILTER_BAR_MARGIN) });
            Row.focusable(true);
        }, Row);
        this.observeComponentCreation2((d1, e1) => {
            Text.create(this.floatFilterBarText);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.fontColor({
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_text_primary_activated'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Text.fontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_body3'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Text.minFontScale(1);
            Text.maxFontScale(Math.min(this.updateFontScale(), MAX_FONT_SCALE));
            Text.constraintSize({ maxWidth: '85%' });
            Text.maxLines(1);
        }, Text);
        Text.pop();
        this.observeComponentCreation2((b1, c1) => {
            SymbolGlyph.create({
                'id': -1,
                'type': 40000,
                params: ['sys.symbol.chevron_down'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            SymbolGlyph.fontSize(`${(this.fontSizeScale ?? DEFAULT_SYMBOL_FONT_SCALE) * SYMBOL_SIZE}vp`);
            SymbolGlyph.fontColor([{
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_text_primary_activated'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            }]);
            SymbolGlyph.focusable(true);
            SymbolGlyph.draggable(false);
        }, SymbolGlyph);
        Row.pop();
        Row.pop();
        Column.pop();
        Row.pop();
    }

    initialRender() {
        this.observeComponentCreation2((y, z) => {
            Stack.create({ alignContent: Alignment.Top });
            Stack.clip(true);
        }, Stack);
        this.FloatFilterBar.bind(this)();
        this.FloatFilterHeader.bind(this)();
        this.observeComponentCreation2((w, x) => {
            Column.create();
            Column.zIndex(0);
        }, Column);
        this.observeComponentCreation2((s, t) => {
            List.create({ initialIndex: 0 });
            List.listDirection(Axis.Vertical);
            List.width(PERCENT_100);
            List.height(PERCENT_100);
            List.edgeEffect(EdgeEffect.Spring);
            List.onScroll((u, v) => {
                if (this.isFloatShowAllFilterWithoutAnimation && v === ScrollState.Scroll) {
                    this.isFloatBarShowWithoutAnimation = true;
                    this.isFloatShowAllFilterWithoutAnimation = false;
                    Context.animateTo({
                        duration: BAR_ANIMATION_DURATION,
                        curve: SHARP_CUBIC_BEZIER
                    }, () => {
                        this.isFloatBarShow = true;
                    });
                    Context.animateTo({
                        curve: INTER_POLATING_SPRING,
                        onFinish: () => {
                            if (!this.isFloatShowAllFilterWithoutAnimation) {
                                this.isFloatShowAllFilter = false;
                            }
                        }
                    }, () => {
                        this.floatFilterPosition = -this.filterDynamicHeight;
                        this.floatFilterBarPosition = 0;
                    });
                }
            });
        }, List);
        {
            const j = (q, r) => {
                ViewStackProcessor.StartGetAccessRecordingFor(q);
                k(q, r);
                if (!r) {
                    ListItem.pop();
                }
                ViewStackProcessor.StopGetAccessRecording();
            };
            const k = (o, p) => {
                ListItem.create(l, true);
                ListItem.focusable(true);
            };
            const l = (m, n) => {
                j(m, n);
                this.FilterHeader.bind(this)();
                ListItem.pop();
            };
            this.observeComponentCreation2(k, ListItem);
            ListItem.pop();
        }
        {
            const a = (h, i) => {
                ViewStackProcessor.StartGetAccessRecordingFor(h);
                b(h, i);
                if (!i) {
                    ListItem.pop();
                }
                ViewStackProcessor.StopGetAccessRecording();
            };
            const b = (f, g) => {
                ListItem.create(c, true);
                ListItem.focusable(true);
            };
            const c = (d, e) => {
                a(d, e);
                this.container.bind(this)();
                ListItem.pop();
            };
            this.observeComponentCreation2(b, ListItem);
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