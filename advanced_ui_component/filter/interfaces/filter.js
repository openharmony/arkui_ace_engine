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

let __decorate = (this && this.__decorate) || function (f13, g13, h13, i13) {
    let j13 = arguments.length;
    let k13 = j13 < 3 ? g13 : i13 === null ? i13 = Object.getOwnPropertyDescriptor(g13, h13) : i13;
    let l13;
    if (typeof Reflect === 'object' && typeof Reflect.decorate === 'function') {
        k13 = Reflect.decorate(f13, g13, h13, i13);
    } else {
        for (let m13 = f13.length - 1; m13 >= 0; m13--) {
            l13 = f13[m13];
            if (l13) {
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
const JSON = requireNapi('util.json');
const accessibility = requireNapi('accessibility');
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

export let FilterType;
(function (e13) {
    e13[e13.MULTI_LINE_FILTER = 0] = 'MULTI_LINE_FILTER';
    e13[e13.LIST_FILTER = 1] = 'LIST_FILTER';
})(FilterType || (FilterType = {}));
let FilterAccessibilityType;
(function (z21) {
    z21[z21.ACCESSIBILITY_TEXT = 0] = 'ACCESSIBILITY_TEXT';
    z21[z21.ACCESSIBILITY_DESC = 1] = 'ACCESSIBILITY_DESC';
    z21[z21.SEND_ACCESSIBILITY = 2] = 'SEND_ACCESSIBILITY';
})(FilterAccessibilityType || (FilterAccessibilityType = {}));
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
let FilterAccessibilityText = class FilterAccessibilityText {
    constructor() {
        this.accessibilitySelectedText = '';
        this.accessibilityExpand = '';
        this.accessibilityCollapse = '';
        this.accessibilityExpanded = '';
        this.accessibilityCollapsed = '';
        this.accessibilityUnselectedText = '';
        this.accessibilityFilters = '';
        this.accessibilitySelectedDesc = '';
        this.accessibilityUnselectedDesc = '';
        this.accessibilityExpandDesc = '';
    }
};
FilterAccessibilityText = __decorate([
    Observed
], FilterAccessibilityText);

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
    constructor(d21, j12, f21, g21 = -1, h21 = undefined, i21) {
        super(d21, f21, g21, i21);
        if (typeof h21 === 'function') {
            this.paramsGenerator_ = h21;
        }
        this.__colorRow = new SynchedPropertyNesedObjectPU(j12.colorRow, this, 'colorRow');
        this.__fontWeightRow = new SynchedPropertyNesedObjectPU(j12.fontWeightRow, this, 'fontWeightRow');
        this.__backgroundColorRow =
            new SynchedPropertyNesedObjectPU(j12.backgroundColorRow, this, 'backgroundColorRow');
        this.__isBackgroundHoverRow =
            new SynchedPropertyNesedObjectPU(j12.isBackgroundHoverRow, this, 'isBackgroundHoverRow');
        this.__isSelectedRow = new SynchedPropertyNesedObjectPU(j12.isSelectedRow, this, 'isSelectedRow');
        this.__filterAccessibilityText =
            new SynchedPropertyNesedObjectPU(j12.filterAccessibilityText, this, 'filterAccessibilityText');
        this.filterRow = { name: '', options: [] };
        this.onItemClick = () => {
        };
        this.rowIndex = 0;
        this.maxAppFontScale = 1;
        this.isFollowingSystemFontScale = false;
        this.bundleName = '';
        this.setInitiallyProvidedValue(j12);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(c21) {
        this.__colorRow.set(c21.colorRow);
        this.__fontWeightRow.set(c21.fontWeightRow);
        this.__backgroundColorRow.set(c21.backgroundColorRow);
        this.__isBackgroundHoverRow.set(c21.isBackgroundHoverRow);
        this.__isSelectedRow.set(c21.isSelectedRow);
        this.__filterAccessibilityText.set(c21.filterAccessibilityText);
        if (c21.filterRow !== undefined) {
            this.filterRow = c21.filterRow;
        }
        if (c21.onItemClick !== undefined) {
            this.onItemClick = c21.onItemClick;
        }
        if (c21.rowIndex !== undefined) {
            this.rowIndex = c21.rowIndex;
        }
        if (c21.maxAppFontScale !== undefined) {
            this.maxAppFontScale = c21.maxAppFontScale;
        }
        if (c21.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = c21.isFollowingSystemFontScale;
        }
        if (c21.bundleName !== undefined) {
            this.bundleName = c21.bundleName;
        }
    }

    updateStateVars(b21) {
        this.__colorRow.set(b21.colorRow);
        this.__fontWeightRow.set(b21.fontWeightRow);
        this.__backgroundColorRow.set(b21.backgroundColorRow);
        this.__isBackgroundHoverRow.set(b21.isBackgroundHoverRow);
        this.__isSelectedRow.set(b21.isSelectedRow);
        this.__filterAccessibilityText.set(b21.filterAccessibilityText);
    }

    purgeVariableDependenciesOnElmtId(a21) {
        this.__colorRow.purgeDependencyOnElmtId(a21);
        this.__fontWeightRow.purgeDependencyOnElmtId(a21);
        this.__backgroundColorRow.purgeDependencyOnElmtId(a21);
        this.__isBackgroundHoverRow.purgeDependencyOnElmtId(a21);
        this.__isSelectedRow.purgeDependencyOnElmtId(a21);
        this.__filterAccessibilityText.purgeDependencyOnElmtId(a21);
    }

    aboutToBeDeleted() {
        this.__colorRow.aboutToBeDeleted();
        this.__fontWeightRow.aboutToBeDeleted();
        this.__backgroundColorRow.aboutToBeDeleted();
        this.__isBackgroundHoverRow.aboutToBeDeleted();
        this.__isSelectedRow.aboutToBeDeleted();
        this.__filterAccessibilityText.aboutToBeDeleted();
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

    get isSelectedRow() {
        return this.__isSelectedRow.get();
    }

    get filterAccessibilityText() {
        return this.__filterAccessibilityText.get();
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
        this.bundleName = getContext(this)?.abilityInfo?.bundleName;
    }

    updateFontScale() {
        let z11 = this.getUIContext();
        let a12 = z11.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(a12, this.maxAppFontScale);
    }

    getAccessibilityText(i20, j20, k20) {
        let l20 = '';
        try {
            let p20 = '';
            if (typeof i20 === 'string') {
                p20 = i20;
            }
            else {
                p20 = getContext()?.resourceManager?.getStringSync(i20?.id);
            }
            switch (k20) {
                case FilterAccessibilityType.ACCESSIBILITY_TEXT:
                    l20 = j20 ? this.filterAccessibilityText.accessibilitySelectedText : p20;
                    break;
                case FilterAccessibilityType.ACCESSIBILITY_DESC:
                    l20 = j20 ? p20 : '';
                    break;
                case FilterAccessibilityType.SEND_ACCESSIBILITY:
                    l20 = j20 ? `${this.filterAccessibilityText.accessibilitySelectedText},${p20}` : '';
                    break;
                default:
                    break;
            }
        }
        catch (m20) {
            let n20 = m20.code;
            let o20 = m20.message;
            hilog.error(0x3900, 'Ace', `Filter getAccessibilityText error, code: ${n20}, message: ${o20}`);
        }
        return l20;
    }

    sendAccessibility(e20, f20) {
        let g20 = ({
            type: 'announceForAccessibility',
            bundleName: this.bundleName,
            triggerAction: 'common',
            textAnnouncedForAccessibility: this.getAccessibilityText(e20,
                f20, FilterAccessibilityType.SEND_ACCESSIBILITY),
        });
        accessibility.sendAccessibilityEvent(g20).then(() => {
            hilog.info(0x3900, 'Ace', `ListFilter sendAccessibility send event, event info is ${JSON.stringify(g20)}`);
        });
    }

    initialRender() {
        this.observeComponentCreation2((c20, d20) => {
            Stack.create({ alignContent: Alignment.End });
            Stack.blendMode(BlendMode.SRC_OVER, BlendApplyType.OFFSCREEN);
        }, Stack);
        this.observeComponentCreation2((a20, b20) => {
            Stack.create({ alignContent: Alignment.Start });
        }, Stack);
        this.observeComponentCreation2((y19, z19) => {
            List.create();
            List.listDirection(Axis.Horizontal);
            List.scrollBar(BarState.Off);
            List.width(PERCENT_100);
            List.height(LIST_ROW_HEIGHT);
            List.align(Alignment.Start);
        }, List);
        this.observeComponentCreation2((d18, e18) => {
            ForEach.create();
            const f18 = (h18, i18) => {
                const j18 = h18;
                this.observeComponentCreation2((i19, j19) => {
                    If.create();
                    if (i18 === 0) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            {
                                const m19 = (w19, x19) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(w19);
                                    n19(w19, x19);
                                    if (!x19) {
                                        ListItem.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                };
                                const n19 = (u19, v19) => {
                                    ListItem.create(o19, true);
                                    ListItem.width({
                                        'id': -1,
                                        'type': 10002,
                                        params: ['sys.float.ohos_id_max_padding_start'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    });
                                    ListItem.height(LIST_ROW_HEIGHT);
                                };
                                const o19 = (s19, t19) => {
                                    m19(s19, t19);
                                    ListItem.pop();
                                };
                                this.observeComponentCreation2(n19, ListItem);
                                ListItem.pop();
                            }
                        });
                    }
                    else {
                        this.ifElseBranchUpdateFunction(1, () => {
                        });
                    }
                }, If);
                If.pop();
                {
                    const l18 = (g19, h19) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(g19);
                        m18(g19, h19);
                        if (!h19) {
                            ListItem.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    };
                    const m18 = (w18, x18) => {
                        ListItem.create(n18, true);
                        ListItem.accessibilityText(this.getAccessibilityText(j18,
                            this.isSelectedRow[i18], FilterAccessibilityType.ACCESSIBILITY_TEXT));
                        ListItem.accessibilityDescription(this.getAccessibilityText(j18,
                            this.isSelectedRow[i18], FilterAccessibilityType.ACCESSIBILITY_DESC));
                        ListItem.height(PERCENT_100);
                        ListItem.onClick(() => {
                            this.onItemClick(i18);
                            this.sendAccessibility(j18, true);
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
                        ListItem.backgroundColor(this.isBackgroundHoverRow[i18] ? this.backgroundColorRow[i18] :
                            TRANS_COLOR);
                        ListItem.onHover((e19) => {
                            Context.animateTo({
                                curve: FRICTION_CUBIC_BEZIER,
                                duration: ANIMATION_DURATION_250
                            }, () => {
                                if (e19) {
                                    this.backgroundColorRow[i18] = {
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_hover'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    };
                                    this.isBackgroundHoverRow[i18] = true;
                                }
                                else {
                                    this.isBackgroundHoverRow[i18] = false;
                                }
                            });
                        });
                        ListItem.onTouch((b19) => {
                            if (b19.type === TouchType.Down) {
                                Context.animateTo({
                                    curve: SHARP_CUBIC_BEZIER,
                                    duration: ANIMATION_DURATION_100
                                }, () => {
                                    this.backgroundColorRow[i18] = {
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_click_effect'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    };
                                    this.isBackgroundHoverRow[i18] = true;
                                });
                            }
                            else if (b19.type === TouchType.Up || b19.type === TouchType.Cancel) {
                                Context.animateTo({
                                    curve: SHARP_CUBIC_BEZIER,
                                    duration: ANIMATION_DURATION_100
                                }, () => {
                                    this.isBackgroundHoverRow[i18] = false;
                                });
                            }
                        });
                        ListItem.margin({ start: LengthMetrics.vp(i18 === 0 ? -TEXT_HOT_AREA_WIDTH : 0) });
                        ListItem.tabIndex(i18 === 0 ? this.rowIndex : -1);
                    };
                    const n18 = (r18, s18) => {
                        l18(r18, s18);
                        this.observeComponentCreation2((u18, v18) => {
                            Text.create(j18);
                            Text.fontSize({
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.ohos_id_text_size_body3'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            });
                            Text.minFontScale(1);
                            Text.maxFontScale(Math.min(this.updateFontScale(), MAX_FONT_SCALE));
                            Text.fontColor(this.colorRow[i18]);
                            Text.fontWeight(this.fontWeightRow[i18]);
                            Text.focusable(true);
                        }, Text);
                        Text.pop();
                        ListItem.pop();
                    };
                    this.observeComponentCreation2(m18, ListItem);
                    ListItem.pop();
                }
            };
            this.forEachUpdateFunction(d18, this.filterRow.options, f18, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        List.pop();
        {
            this.observeComponentCreation2((x17, y17) => {
                if (y17) {
                    let z17 = new GradientMask(this, {
                        x0: 0,
                        y0: LIST_ROW_HEIGHT / 2,
                        x1: GRADIENT_WIDTH,
                        y1: LIST_ROW_HEIGHT / 2
                    }, undefined, x17, () => {
                    }, { page: 'library2/src/main/ets/components/mainpage/MainPage.ets', line: 318, col: 9 });
                    ViewPU.create(z17);
                    let a18 = () => {
                        return {
                            x0: 0,
                            y0: LIST_ROW_HEIGHT / 2,
                            x1: GRADIENT_WIDTH,
                            y1: LIST_ROW_HEIGHT / 2
                        };
                    };
                    z17.paramsGenerator_ = a18;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(x17, {});
                }
            }, { name: 'GradientMask' });
        }
        Stack.pop();
        {
            this.observeComponentCreation2((q17, r17) => {
                if (r17) {
                    let s17 = new GradientMask(this, {
                        x0: GRADIENT_WIDTH,
                        y0: LIST_ROW_HEIGHT / 2,
                        x1: 0,
                        y1: LIST_ROW_HEIGHT / 2
                    }, undefined, q17, () => {
                    }, { page: 'library2/src/main/ets/components/mainpage/MainPage.ets', line: 326, col: 7 });
                    ViewPU.create(s17);
                    let t17 = () => {
                        return {
                            x0: GRADIENT_WIDTH,
                            y0: LIST_ROW_HEIGHT / 2,
                            x1: 0,
                            y1: LIST_ROW_HEIGHT / 2
                        };
                    };
                    s17.paramsGenerator_ = t17;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(q17, {});
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
    constructor(e17, f17, g17, h17 = -1, i17 = undefined, j17) {
        super(e17, g17, h17, j17);
        if (typeof i17 === 'function') {
            this.paramsGenerator_ = i17;
        }
        this.__colorRow = new SynchedPropertyNesedObjectPU(f17.colorRow, this, 'colorRow');
        this.__fontWeightRow =
            new SynchedPropertyNesedObjectPU(f17.fontWeightRow, this, 'fontWeightRow');
        this.__backgroundColorRow =
            new SynchedPropertyNesedObjectPU(f17.backgroundColorRow, this, 'backgroundColorRow');
        this.__isBackgroundHoverRow =
            new SynchedPropertyNesedObjectPU(f17.isBackgroundHoverRow, this, 'isBackgroundHoverRow');
        this.__twoLineModeItemNumRow =
            new SynchedPropertyNesedObjectPU(f17.twoLineModeItemNumRow, this, 'twoLineModeItemNumRow');
        this.__twoLineModeItemNumRecordRow =
            new SynchedPropertyNesedObjectPU(f17.twoLineModeItemNumRecordRow, this, 'twoLineModeItemNumRecordRow');
        this.__arrowShowStateRow =
            new SynchedPropertyNesedObjectPU(f17.arrowShowStateRow, this, 'arrowShowStateRow');
        this.__isArrowIconDown = new SynchedPropertyNesedObjectPU(f17.isArrowIconDown, this, 'isArrowIconDown');
        this.__isSelectedRow = new SynchedPropertyNesedObjectPU(f17.isSelectedRow, this, 'isSelectedRow');
        this.__filterAccessibilityText =
            new SynchedPropertyNesedObjectPU(f17.filterAccessibilityText, this, 'filterAccessibilityText');
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
        this.__fontSizeScale = new SynchedPropertyObjectOneWayPU(f17.fontSizeScale, this, 'fontSizeScale');
        this.__replaceEffect = new ObservedPropertySimplePU(0, this, 'replaceEffect');
        this.__isSendArrowAccessibility = new ObservedPropertySimplePU(false, this, 'isSendArrowAccessibility');
        this.filterColumnWidth = 0;
        this.lastFilterColumnWidth = 0;
        this.rowIndex = 0;
        this.maxAppFontScale = 1;
        this.isFollowingSystemFontScale = false;
        this.bundleName = '';
        this.filterId = this.getUniqueId();
        this.setInitiallyProvidedValue(f17);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(d17) {
        this.__colorRow.set(d17.colorRow);
        this.__fontWeightRow.set(d17.fontWeightRow);
        this.__backgroundColorRow.set(d17.backgroundColorRow);
        this.__isBackgroundHoverRow.set(d17.isBackgroundHoverRow);
        this.__twoLineModeItemNumRow.set(d17.twoLineModeItemNumRow);
        this.__twoLineModeItemNumRecordRow.set(d17.twoLineModeItemNumRecordRow);
        this.__arrowShowStateRow.set(d17.arrowShowStateRow);
        this.__isArrowIconDown.set(d17.isArrowIconDown);
        this.__isSelectedRow.set(d17.isSelectedRow);
        this.__filterAccessibilityText.set(d17.filterAccessibilityText);
        if (d17.filterRow !== undefined) {
            this.filterRow = d17.filterRow;
        }
        if (d17.onItemClick !== undefined) {
            this.onItemClick = d17.onItemClick;
        }
        if (d17.arrowBgColorRow !== undefined) {
            this.arrowBgColorRow = d17.arrowBgColorRow;
        }
        if (d17.isArrowBgHoverRow !== undefined) {
            this.isArrowBgHoverRow = d17.isArrowBgHoverRow;
        }
        if (d17.replaceEffect !== undefined) {
            this.replaceEffect = d17.replaceEffect;
        }
        if (d17.isSendArrowAccessibility !== undefined) {
            this.isSendArrowAccessibility = d17.isSendArrowAccessibility;
        }
        if (d17.filterColumnWidth !== undefined) {
            this.filterColumnWidth = d17.filterColumnWidth;
        }
        if (d17.lastFilterColumnWidth !== undefined) {
            this.lastFilterColumnWidth = d17.lastFilterColumnWidth;
        }
        if (d17.rowIndex !== undefined) {
            this.rowIndex = d17.rowIndex;
        }
        if (d17.maxAppFontScale !== undefined) {
            this.maxAppFontScale = d17.maxAppFontScale;
        }
        if (d17.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = d17.isFollowingSystemFontScale;
        }
        if (d17.bundleName !== undefined) {
            this.bundleName = d17.bundleName;
        }
        if (d17.filterId !== undefined) {
            this.filterId = d17.filterId;
        }
    }

    updateStateVars(c17) {
        this.__colorRow.set(c17.colorRow);
        this.__fontWeightRow.set(c17.fontWeightRow);
        this.__backgroundColorRow.set(c17.backgroundColorRow);
        this.__isBackgroundHoverRow.set(c17.isBackgroundHoverRow);
        this.__twoLineModeItemNumRow.set(c17.twoLineModeItemNumRow);
        this.__twoLineModeItemNumRecordRow.set(c17.twoLineModeItemNumRecordRow);
        this.__arrowShowStateRow.set(c17.arrowShowStateRow);
        this.__isArrowIconDown.set(c17.isArrowIconDown);
        this.__isSelectedRow.set(c17.isSelectedRow);
        this.__filterAccessibilityText.set(c17.filterAccessibilityText);
        this.__fontSizeScale.reset(c17.fontSizeScale);
    }

    purgeVariableDependenciesOnElmtId(b17) {
        this.__colorRow.purgeDependencyOnElmtId(b17);
        this.__fontWeightRow.purgeDependencyOnElmtId(b17);
        this.__backgroundColorRow.purgeDependencyOnElmtId(b17);
        this.__isBackgroundHoverRow.purgeDependencyOnElmtId(b17);
        this.__twoLineModeItemNumRow.purgeDependencyOnElmtId(b17);
        this.__twoLineModeItemNumRecordRow.purgeDependencyOnElmtId(b17);
        this.__arrowShowStateRow.purgeDependencyOnElmtId(b17);
        this.__isArrowIconDown.purgeDependencyOnElmtId(b17);
        this.__isSelectedRow.purgeDependencyOnElmtId(b17);
        this.__filterAccessibilityText.purgeDependencyOnElmtId(b17);
        this.__arrowBgColorRow.purgeDependencyOnElmtId(b17);
        this.__isArrowBgHoverRow.purgeDependencyOnElmtId(b17);
        this.__fontSizeScale.purgeDependencyOnElmtId(b17);
        this.__replaceEffect.purgeDependencyOnElmtId(b17);
        this.__isSendArrowAccessibility.purgeDependencyOnElmtId(b17);
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
        this.__isSelectedRow.aboutToBeDeleted();
        this.__filterAccessibilityText.aboutToBeDeleted();
        this.__arrowBgColorRow.aboutToBeDeleted();
        this.__isArrowBgHoverRow.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__replaceEffect.aboutToBeDeleted();
        this.__isSendArrowAccessibility.aboutToBeDeleted();
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

    get isSelectedRow() {
        return this.__isSelectedRow.get();
    }

    get filterAccessibilityText() {
        return this.__filterAccessibilityText.get();
    }

    get arrowBgColorRow() {
        return this.__arrowBgColorRow.get();
    }

    set arrowBgColorRow(a17) {
        this.__arrowBgColorRow.set(a17);
    }

    get isArrowBgHoverRow() {
        return this.__isArrowBgHoverRow.get();
    }

    set isArrowBgHoverRow(z16) {
        this.__isArrowBgHoverRow.set(z16);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(y16) {
        this.__fontSizeScale.set(y16);
    }

    get replaceEffect() {
        return this.__replaceEffect.get();
    }

    set replaceEffect(x16) {
        this.__replaceEffect.set(x16);
    }

    get isSendArrowAccessibility() {
        return this.__isSendArrowAccessibility.get();
    }

    set isSendArrowAccessibility(w16) {
        this.__isSendArrowAccessibility.set(w16);
    }

    aboutToAppear() {
        try {
            let r16 = this.getUIContext();
            this.isFollowingSystemFontScale = r16.isFollowingSystemFontScale();
            this.maxAppFontScale = r16.getMaxFontScale();
        }
        catch (o16) {
            let p16 = o16.code;
            let q16 = o16.message;
            hilog.error(ERROR_CODE, 'Ace', `Failed to init fontsizescale info, cause, code: ${p16}, message: ${q16}`);
        }
        this.bundleName = getContext(this)?.abilityInfo?.bundleName;
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

    getAccessibilityText(y15, z15, a16) {
        let b16 = '';
        try {
            let f16 = '';
            if (typeof y15 === 'string') {
                f16 = y15;
            }
            else {
                f16 = getContext()?.resourceManager?.getStringSync(y15?.id);
            }
            switch (a16) {
                case FilterAccessibilityType.ACCESSIBILITY_TEXT:
                    b16 = z15 ? this.filterAccessibilityText.accessibilitySelectedText : f16;
                    break;
                case FilterAccessibilityType.ACCESSIBILITY_DESC:
                    b16 = z15 ? f16 : '';
                    break;
                case FilterAccessibilityType.SEND_ACCESSIBILITY:
                    b16 = z15 ? `${this.filterAccessibilityText.accessibilitySelectedText},${f16}` : '';
                    break;
                default:
                    break;
            }
        }
        catch (c16) {
            let d16 = c16.code;
            let e16 = c16.message;
            hilog.error(0x3900, 'Ace', `Filter getAccessibilityText error, code: ${d16}, message: ${e16}`);
        }
        return b16;
    }

    sendAccessibility(v15, w15) {
        let x15 = ({
            type: 'announceForAccessibility',
            bundleName: this.bundleName,
            triggerAction: 'common',
            textAnnouncedForAccessibility: this.getAccessibilityText(v15,
                w15, FilterAccessibilityType.SEND_ACCESSIBILITY),
        });
        accessibility.sendAccessibilityEvent(x15);
    }

    sendArrowAccessibility(u15) {
        if (this.isSendArrowAccessibility) {
            let v15 = ({
                type: 'requestFocusForAccessibility',
                bundleName: this.bundleName,
                triggerAction: 'common',
                customId: u15,
            });
            accessibility.sendAccessibilityEvent(v15).then(() => {
                setTimeout(() => {
                    this.isSendArrowAccessibility = false;
                }, 200);
            });
        }
    }

    DownAndUpArrow(v14 = null) {
        this.observeComponentCreation2((p15, q15) => {
            Row.create();
            Row.height(LIST_ROW_HEIGHT);
        }, Row);
        this.observeComponentCreation2((b15, c15) => {
            Button.createWithChild({ stateEffect: false, type: ButtonType.Normal });
            Button.border({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_corner_radius_clicked'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                }
            });
            Button.height(LIST_ROW_HEIGHT);
            Button.backgroundColor(this.isArrowBgHoverRow ? this.arrowBgColorRow : TRANS_COLOR);
            Button.focusable(true);
            Button.accessibilityGroup(true);
            Button.accessibilityText(this.isSendArrowAccessibility ?
                (this.isArrowIconDown?.value ? this.filterAccessibilityText.accessibilityCollapsed :
                this.filterAccessibilityText.accessibilityExpanded) :
                (this.isArrowIconDown?.value ? this.filterAccessibilityText.accessibilityExpand :
                this.filterAccessibilityText.accessibilityCollapse));
            Button.accessibilityDescription(this.isSendArrowAccessibility ? ' ' : '');
            Button.id(`filterDownAndUpArrow_${this.getUniqueId()}_${this.rowIndex}`);
            Button.visibility(this.arrowShowStateRow.value ? Visibility.Visible : Visibility.Hidden);
            Button.onHover((n15) => {
                Context.animateTo({
                    curve: FRICTION_CUBIC_BEZIER,
                    duration: ANIMATION_DURATION_250
                }, () => {
                    if (n15) {
                        this.arrowBgColorRow = {
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_hover'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        };
                        this.isArrowBgHoverRow = true;
                    }
                    else {
                        this.isArrowBgHoverRow = false;
                    }
                });
            });
            Button.onTouch((k15) => {
                if (k15.type === TouchType.Down) {
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
                }
                else if (k15.type === TouchType.Up || k15.type === TouchType.Cancel) {
                    Context.animateTo({
                        curve: SHARP_CUBIC_BEZIER,
                        duration: ANIMATION_DURATION_100
                    }, () => {
                        this.isArrowBgHoverRow = false;
                    });
                }
            });
            Button.onClick(() => {
                this.isSendArrowAccessibility = true;
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
                        curve: SHARP_CUBIC_BEZIER
                    }, () => {
                        this.arrowShowStateRow.value = true;
                    });
                }
                this.sendArrowAccessibility(`filterDownAndUpArrow_${this.getUniqueId()}_${this.rowIndex}`);
            });
        }, Button);
        this.observeComponentCreation2((z14, a15) => {
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
        Button.pop();
        Row.pop();
    }

    initialRender() {
        this.observeComponentCreation2((t14, u14) => {
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
        this.observeComponentCreation2((e14, f14) => {
            If.create();
            if (this.filterRow?.options && this.filterRow?.options.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    if (!If.canRetake(`filterMultiFilterRow_${this.filterId}_${this.rowIndex}`)) {
                        this.observeComponentCreation2((j14, k14) => {
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
                            Text.backgroundColor(this.isBackgroundHoverRow[0] ? this.backgroundColorRow[0] :
                                TRANS_COLOR);
                            Text.accessibilityText(this.getAccessibilityText(this.filterRow?.options[0],
                                this.isSelectedRow[0], FilterAccessibilityType.ACCESSIBILITY_TEXT));
                            Text.accessibilityDescription(this.getAccessibilityText(this.filterRow?.options[0],
                                this.isSelectedRow[0], FilterAccessibilityType.ACCESSIBILITY_DESC));
                            Text.onClick(() => {
                                this.onItemClick(0);
                                this.sendAccessibility(this.filterRow?.options[0], true);
                            });
                            Text.id(`filterMultiFilterRow_${this.filterId}_${this.rowIndex}`);
                            Text.focusable(true);
                            Text.onHover((r14) => {
                                Context.animateTo({
                                    curve: FRICTION_CUBIC_BEZIER,
                                    duration: ANIMATION_DURATION_250
                                }, () => {
                                    if (r14) {
                                        this.backgroundColorRow[0] = {
                                            'id': -1,
                                            'type': 10001,
                                            params: ['sys.color.ohos_id_color_hover'],
                                            'bundleName': '__harDefaultBundleName__',
                                            'moduleName': '__harDefaultModuleName__'
                                        };
                                        this.isBackgroundHoverRow[0] = true;
                                    }
                                    else {
                                        this.isBackgroundHoverRow[0] = false;
                                    }
                                });
                            });
                            Text.onTouch((o14) => {
                                if (o14.type === TouchType.Down) {
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
                                }
                                else if (o14.type === TouchType.Up || o14.type === TouchType.Cancel) {
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
                    }
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((x13, y13) => {
            Row.create();
            Row.width(PERCENT_100);
            Row.onAreaChange((a14, b14) => {
                this.filterColumnWidth = vp2px(parseInt(b14.width.toString(), 0));
                if (this.twoLineModeItemNumRow.value === 0) {
                    let d14 = this.calcMultiFilterRowItemNum();
                    this.twoLineModeItemNumRow.value = d14;
                    this.twoLineModeItemNumRecordRow.value = d14;
                    if (this.filterRow && d14 < this.filterRow.options.length - 1) {
                        this.arrowShowStateRow.value = true;
                    }
                    else {
                        this.arrowShowStateRow.value = false;
                    }
                }
                else if (this.filterColumnWidth !== this.lastFilterColumnWidth) {
                    let c14 = this.calcMultiFilterRowItemNum();
                    if (this.filterRow && c14 < this.filterRow.options.length - 1) {
                        if (!this.arrowShowStateRow.value || this.isArrowIconDown.value) {
                            this.arrowShowStateRow.value = true;
                            this.isArrowIconDown.value = true;
                            this.twoLineModeItemNumRow.value = c14;
                        }
                    }
                    else {
                        this.arrowShowStateRow.value = false;
                        this.isArrowIconDown.value = false;
                        this.twoLineModeItemNumRow.value = c14;
                    }
                    this.twoLineModeItemNumRecordRow.value = c14;
                }
                this.lastFilterColumnWidth = this.filterColumnWidth;
            });
        }, Row);
        this.observeComponentCreation2((v13, w13) => {
            Flex.create({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap });
        }, Flex);
        this.observeComponentCreation2((y12, z12) => {
            ForEach.create();
            const a13 = (c13, d13) => {
                const e13 = c13;
                this.observeComponentCreation2((g13, h13) => {
                    If.create();
                    if (d13 > 0) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((l13, m13) => {
                                Text.create(e13);
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
                                Text.fontColor(this.colorRow[d13]);
                                Text.fontWeight(this.fontWeightRow[d13]);
                                Text.accessibilityText(this.getAccessibilityText(e13,
                                    this.isSelectedRow[d13], FilterAccessibilityType.ACCESSIBILITY_TEXT));
                                Text.accessibilityDescription(this.getAccessibilityText(e13,
                                    this.isSelectedRow[d13], FilterAccessibilityType.ACCESSIBILITY_DESC));
                                Text.backgroundColor(this.isBackgroundHoverRow[d13] ?
                                this.backgroundColorRow[d13] : TRANS_COLOR);
                                Text.onClick(() => {
                                    this.onItemClick(d13);
                                    this.sendAccessibility(e13, true);
                                });
                                Text.onHover((t13) => {
                                    Context.animateTo({
                                        curve: FRICTION_CUBIC_BEZIER,
                                        duration: ANIMATION_DURATION_250
                                    }, () => {
                                        if (t13) {
                                            this.backgroundColorRow[d13] = {
                                                'id': -1,
                                                'type': 10001,
                                                params: ['sys.color.ohos_id_color_hover'],
                                                'bundleName': '__harDefaultBundleName__',
                                                'moduleName': '__harDefaultModuleName__'
                                            };
                                            this.isBackgroundHoverRow[d13] = true;
                                        }
                                        else {
                                            this.isBackgroundHoverRow[d13] = false;
                                        }
                                    });
                                });
                                Text.onTouch((q13) => {
                                    if (q13.type === TouchType.Down) {
                                        Context.animateTo({
                                            curve: SHARP_CUBIC_BEZIER,
                                            duration: ANIMATION_DURATION_100
                                        }, () => {
                                            this.backgroundColorRow[d13] = {
                                                'id': -1,
                                                'type': 10001,
                                                params: ['sys.color.ohos_id_color_click_effect'],
                                                'bundleName': '__harDefaultBundleName__',
                                                'moduleName': '__harDefaultModuleName__'
                                            };
                                            this.isBackgroundHoverRow[d13] = true;
                                        });
                                    }
                                    else if (q13.type === TouchType.Up || q13.type === TouchType.Cancel) {
                                        Context.animateTo({
                                            curve: SHARP_CUBIC_BEZIER,
                                            duration: ANIMATION_DURATION_100
                                        }, () => {
                                            this.isBackgroundHoverRow[d13] = false;
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
                    }
                    else {
                        this.ifElseBranchUpdateFunction(1, () => {
                        });
                    }
                }, If);
                If.pop();
            };
            this.forEachUpdateFunction(y12, this.filterRow?.options.slice(0, this.twoLineModeItemNumRow.value + 1),
                a13, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        this.observeComponentCreation2((u12, v12) => {
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
    constructor(h12, i12, j12, k12 = -1, l12 = undefined, m12) {
        super(h12, j12, k12, m12);
        if (typeof l12 === 'function') {
            this.paramsGenerator_ = l12;
        }
        this.container = undefined;
        this.__multiFilters = new SynchedPropertyObjectOneWayPU(i12.multiFilters, this, 'multiFilters');
        this.__additionFilters = new SynchedPropertyObjectOneWayPU(i12.additionFilters, this, 'additionFilters');
        this.onFilterChanged = null;
        this.__filterType = new SynchedPropertySimpleOneWayPU(i12.filterType, this, 'filterType');
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
        this.__isSelectedArr = new ObservedPropertyObjectPU(null, this, 'isSelectedArr');
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
            onConfigurationUpdated: (n12) => {
                this.fontSizeScale = Math.min(this.updateFontScale(), MAX_SYMBOL_FONT_SCALE);
                this.fontSizeScale = Math.max(this.fontSizeScale, MIN_SYMBOL_FONT_SCALE);
                this.initAccessibilityResource();
            },
            onMemoryLevel() {
            }
        };
        this.__additionFiltersSelectedIndex = new ObservedPropertySimplePU(-1, this, 'additionFiltersSelectedIndex');
        this.__floatFilterBarAccessibilityText =
            new ObservedPropertySimplePU('', this, 'floatFilterBarAccessibilityText');
        this.__filterAccessibilityText =
            new ObservedPropertyObjectPU(new FilterAccessibilityText(), this, 'filterAccessibilityText');
        this.bundleName = '';
        this.filterId = this.getUniqueId();
        this.setInitiallyProvidedValue(i12);
        this.declareWatch('isFloatBarShow', this.updateFocusForAccessibility);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(g12) {
        if (g12.container !== undefined) {
            this.container = g12.container;
        }
        if (g12.multiFilters === undefined) {
            this.__multiFilters.set([]);
        }
        if (g12.additionFilters === undefined) {
            this.__additionFilters.set(null);
        }
        if (g12.onFilterChanged !== undefined) {
            this.onFilterChanged = g12.onFilterChanged;
        }
        if (g12.filterType === undefined) {
            this.__filterType.set(FilterType.LIST_FILTER);
        }
        if (g12.selectedFilters !== undefined) {
            this.selectedFilters = g12.selectedFilters;
        }
        if (g12.colorArr !== undefined) {
            this.colorArr = g12.colorArr;
        }
        if (g12.fontWeightArr !== undefined) {
            this.fontWeightArr = g12.fontWeightArr;
        }
        if (g12.backgroundColorArr !== undefined) {
            this.backgroundColorArr = g12.backgroundColorArr;
        }
        if (g12.isBackgroundHover !== undefined) {
            this.isBackgroundHover = g12.isBackgroundHover;
        }
        if (g12.floatArrowBgColor !== undefined) {
            this.floatArrowBgColor = g12.floatArrowBgColor;
        }
        if (g12.isFloatArrowBgHover !== undefined) {
            this.isFloatArrowBgHover = g12.isFloatArrowBgHover;
        }
        if (g12.isArrowIconDownArr !== undefined) {
            this.isArrowIconDownArr = g12.isArrowIconDownArr;
        }
        if (g12.additionColorArr !== undefined) {
            this.additionColorArr = g12.additionColorArr;
        }
        if (g12.additionFontWeightArr !== undefined) {
            this.additionFontWeightArr = g12.additionFontWeightArr;
        }
        if (g12.additionBackgroundColorArr !== undefined) {
            this.additionBackgroundColorArr = g12.additionBackgroundColorArr;
        }
        if (g12.isAdditionBackgroundHover !== undefined) {
            this.isAdditionBackgroundHover = g12.isAdditionBackgroundHover;
        }
        if (g12.isSelectedArr !== undefined) {
            this.isSelectedArr = g12.isSelectedArr;
        }
        if (g12.colorRefresh !== undefined) {
            this.colorRefresh = g12.colorRefresh;
        }
        if (g12.isFloatBarShow !== undefined) {
            this.isFloatBarShow = g12.isFloatBarShow;
        }
        if (g12.isFloatBarShowWithoutAnimation !== undefined) {
            this.isFloatBarShowWithoutAnimation = g12.isFloatBarShowWithoutAnimation;
        }
        if (g12.isFloatShowAllFilter !== undefined) {
            this.isFloatShowAllFilter = g12.isFloatShowAllFilter;
        }
        if (g12.isFloatShowAllFilterWithoutAnimation !== undefined) {
            this.isFloatShowAllFilterWithoutAnimation = g12.isFloatShowAllFilterWithoutAnimation;
        }
        if (g12.floatFilterPosition !== undefined) {
            this.floatFilterPosition = g12.floatFilterPosition;
        }
        if (g12.floatFilterBarHeight !== undefined) {
            this.floatFilterBarHeight = g12.floatFilterBarHeight;
        }
        if (g12.floatFilterBarPosition !== undefined) {
            this.floatFilterBarPosition = g12.floatFilterBarPosition;
        }
        if (g12.filterDynamicHeight !== undefined) {
            this.filterDynamicHeight = g12.filterDynamicHeight;
        }
        if (g12.twoLineModeItemNum !== undefined) {
            this.twoLineModeItemNum = g12.twoLineModeItemNum;
        }
        if (g12.twoLineModeItemNumRecord !== undefined) {
            this.twoLineModeItemNumRecord = g12.twoLineModeItemNumRecord;
        }
        if (g12.downArrowShowState !== undefined) {
            this.downArrowShowState = g12.downArrowShowState;
        }
        if (g12.floatFilterBarText !== undefined) {
            this.floatFilterBarText = g12.floatFilterBarText;
        }
        if (g12.maxAppFontScale !== undefined) {
            this.maxAppFontScale = g12.maxAppFontScale;
        }
        if (g12.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = g12.isFollowingSystemFontScale;
        }
        if (g12.fontSizeScale !== undefined) {
            this.fontSizeScale = g12.fontSizeScale;
        }
        if (g12.callbackId !== undefined) {
            this.callbackId = g12.callbackId;
        }
        if (g12.callbacks !== undefined) {
            this.callbacks = g12.callbacks;
        }
        if (g12.additionFiltersSelectedIndex !== undefined) {
            this.additionFiltersSelectedIndex = g12.additionFiltersSelectedIndex;
        }
        if (g12.floatFilterBarAccessibilityText !== undefined) {
            this.floatFilterBarAccessibilityText = g12.floatFilterBarAccessibilityText;
        }
        if (g12.filterAccessibilityText !== undefined) {
            this.filterAccessibilityText = g12.filterAccessibilityText;
        }
        if (g12.bundleName !== undefined) {
            this.bundleName = g12.bundleName;
        }
        if (g12.filterId !== undefined) {
            this.filterId = g12.filterId;
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
        this.__isSelectedArr.purgeDependencyOnElmtId(n7);
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
        this.__additionFiltersSelectedIndex.purgeDependencyOnElmtId(n7);
        this.__floatFilterBarAccessibilityText.purgeDependencyOnElmtId(n7);
        this.__filterAccessibilityText.purgeDependencyOnElmtId(n7);
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
        this.__isSelectedArr.aboutToBeDeleted();
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
        this.__additionFiltersSelectedIndex.aboutToBeDeleted();
        this.__floatFilterBarAccessibilityText.aboutToBeDeleted();
        this.__filterAccessibilityText.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get multiFilters() {
        return this.__multiFilters.get();
    }
    set multiFilters(d12) {
        this.__multiFilters.set(d12);
    }
    get additionFilters() {
        return this.__additionFilters.get();
    }
    set additionFilters(c12) {
        this.__additionFilters.set(c12);
    }
    get filterType() {
        return this.__filterType.get();
    }
    set filterType(b12) {
        this.__filterType.set(b12);
    }
    get colorArr() {
        return this.__colorArr.get();
    }
    set colorArr(a12) {
        this.__colorArr.set(a12);
    }
    get fontWeightArr() {
        return this.__fontWeightArr.get();
    }
    set fontWeightArr(z11) {
        this.__fontWeightArr.set(z11);
    }
    get backgroundColorArr() {
        return this.__backgroundColorArr.get();
    }
    set backgroundColorArr(y11) {
        this.__backgroundColorArr.set(y11);
    }
    get isBackgroundHover() {
        return this.__isBackgroundHover.get();
    }
    set isBackgroundHover(x11) {
        this.__isBackgroundHover.set(x11);
    }
    get floatArrowBgColor() {
        return this.__floatArrowBgColor.get();
    }
    set floatArrowBgColor(w11) {
        this.__floatArrowBgColor.set(w11);
    }
    get isFloatArrowBgHover() {
        return this.__isFloatArrowBgHover.get();
    }
    set isFloatArrowBgHover(v11) {
        this.__isFloatArrowBgHover.set(v11);
    }
    get isArrowIconDownArr() {
        return this.__isArrowIconDownArr.get();
    }
    set isArrowIconDownArr(u11) {
        this.__isArrowIconDownArr.set(u11);
    }
    get additionColorArr() {
        return this.__additionColorArr.get();
    }
    set additionColorArr(t11) {
        this.__additionColorArr.set(t11);
    }
    get additionFontWeightArr() {
        return this.__additionFontWeightArr.get();
    }
    set additionFontWeightArr(s11) {
        this.__additionFontWeightArr.set(s11);
    }
    get additionBackgroundColorArr() {
        return this.__additionBackgroundColorArr.get();
    }
    set additionBackgroundColorArr(r11) {
        this.__additionBackgroundColorArr.set(r11);
    }
    get isAdditionBackgroundHover() {
        return this.__isAdditionBackgroundHover.get();
    }
    set isAdditionBackgroundHover(q11) {
        this.__isAdditionBackgroundHover.set(q11);
    }
    get isSelectedArr() {
        return this.__isSelectedArr.get();
    }
    set isSelectedArr(p11) {
        this.__isSelectedArr.set(p11);
    }
    get colorRefresh() {
        return this.__colorRefresh.get();
    }
    set colorRefresh(o11) {
        this.__colorRefresh.set(o11);
    }
    get isFloatBarShow() {
        return this.__isFloatBarShow.get();
    }
    set isFloatBarShow(n11) {
        this.__isFloatBarShow.set(n11);
    }
    get isFloatShowAllFilter() {
        return this.__isFloatShowAllFilter.get();
    }
    set isFloatShowAllFilter(m11) {
        this.__isFloatShowAllFilter.set(m11);
    }
    get floatFilterPosition() {
        return this.__floatFilterPosition.get();
    }
    set floatFilterPosition(l11) {
        this.__floatFilterPosition.set(l11);
    }
    get floatFilterBarHeight() {
        return this.__floatFilterBarHeight.get();
    }
    set floatFilterBarHeight(k11) {
        this.__floatFilterBarHeight.set(k11);
    }
    get floatFilterBarPosition() {
        return this.__floatFilterBarPosition.get();
    }
    set floatFilterBarPosition(j11) {
        this.__floatFilterBarPosition.set(j11);
    }
    get twoLineModeItemNum() {
        return this.__twoLineModeItemNum.get();
    }
    set twoLineModeItemNum(i11) {
        this.__twoLineModeItemNum.set(i11);
    }
    get twoLineModeItemNumRecord() {
        return this.__twoLineModeItemNumRecord.get();
    }
    set twoLineModeItemNumRecord(h11) {
        this.__twoLineModeItemNumRecord.set(h11);
    }
    get downArrowShowState() {
        return this.__downArrowShowState.get();
    }
    set downArrowShowState(g11) {
        this.__downArrowShowState.set(g11);
    }
    get floatFilterBarText() {
        return this.__floatFilterBarText.get();
    }
    set floatFilterBarText(f11) {
        this.__floatFilterBarText.set(f11);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(e11) {
        this.__fontSizeScale.set(e11);
    }
    get additionFiltersSelectedIndex() {
        return this.__additionFiltersSelectedIndex.get();
    }

    set additionFiltersSelectedIndex(d11) {
        this.__additionFiltersSelectedIndex.set(d11);
    }

    get floatFilterBarAccessibilityText() {
        return this.__floatFilterBarAccessibilityText.get();
    }

    set floatFilterBarAccessibilityText(c11) {
        this.__floatFilterBarAccessibilityText.set(c11);
    }

    get filterAccessibilityText() {
        return this.__filterAccessibilityText.get();
    }

    set filterAccessibilityText(c11) {
        this.__filterAccessibilityText.set(c11);
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
        this.initAccessibilityResource();
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

    initAccessibilityResource() {
        try {
            this.bundleName = getContext(this)?.abilityInfo?.bundleName;
            let v10 = getContext()?.resourceManager;
            this.filterAccessibilityText.accessibilitySelectedText =
                v10?.getStringByNameSync('filter_accessibility_selected');
            this.filterAccessibilityText.accessibilityUnselectedText =
                v10?.getStringByNameSync('filter_accessibility_unselected');
            this.filterAccessibilityText.accessibilityFilters =
                v10?.getStringByNameSync('filter_accessibility_filters');
            this.filterAccessibilityText.accessibilitySelectedDesc =
                v10?.getStringByNameSync('filter_accessibility_select_desc');
            this.filterAccessibilityText.accessibilityUnselectedDesc =
                v10?.getStringByNameSync('filter_accessibility_unselect_desc');
            this.filterAccessibilityText.accessibilityExpandDesc =
                v10?.getStringByNameSync('filter_accessibility_expand_desc');
            this.filterAccessibilityText.accessibilityExpanded =
                v10?.getStringByNameSync('filter_accessibility_expanded');
            this.filterAccessibilityText.accessibilityCollapsed =
                v10?.getStringByNameSync('filter_accessibility_collapsed');
            this.filterAccessibilityText.accessibilityExpand =
                v10?.getStringByNameSync('filter_accessibility_expand');
            this.filterAccessibilityText.accessibilityCollapse =
                v10?.getStringByNameSync('filter_accessibility_collapse');
        }
        catch (s10) {
            let t10 = s10.code;
            let u10 = s10.message;
            hilog.error(ERROR_CODE, 'Ace', `Filter failed to initAccessibilityResource, code: ${t10}, message: ${u10}`);
        }
    }

    updateFocusForAccessibility() {
        if (this.isFloatBarShow) {
            let r10 = ({
                type: 'requestFocusForAccessibility',
                bundleName: this.bundleName,
                triggerAction: 'common',
                customId: `FiliterFloatFilterBar_${this.getUniqueId()}`,
            });
            accessibility.sendAccessibilityEvent(r10);
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

    getAccessibilityText(h10, i10, j10) {
        let k10 = '';
        try {
            let o10 = '';
            if (typeof h10 === 'string') {
                o10 = h10;
            }
            else {
                o10 = getContext().resourceManager.getStringSync(h10?.id);
            }
            switch (j10) {
                case FilterAccessibilityType.ACCESSIBILITY_TEXT:
                    k10 = i10 ? `${this.filterAccessibilityText.accessibilitySelectedText},${o10}` : o10;
                    break;
                case FilterAccessibilityType.ACCESSIBILITY_DESC:
                    k10 = i10 ? this.filterAccessibilityText.accessibilityUnselectedDesc :
                    this.filterAccessibilityText.accessibilitySelectedDesc;
                    break;
                case FilterAccessibilityType.SEND_ACCESSIBILITY:
                    k10 = i10 ? `${this.filterAccessibilityText.accessibilitySelectedText},${o10}` :
                        `${this.filterAccessibilityText.accessibilityUnselectedText},${o10}`;
                    break;
                default:
                    break;
            }
        }
        catch (l10) {
            let m10 = l10.code;
            let n10 = l10.message;
            hilog.error(0x3900, 'Ace', `Filter getAccessibilityText error, code: ${m10}, message: ${n10}`);
        }
        return k10;
    }

    sendAccessibility(d10, e10) {
        let f10 = ({
            type: 'announceForAccessibility',
            bundleName: this.bundleName,
            triggerAction: 'common',
            textAnnouncedForAccessibility: this.getAccessibilityText(d10,
                e10, FilterAccessibilityType.SEND_ACCESSIBILITY),
        });
        accessibility.sendAccessibilityEvent(f10).then(() => {
            hilog.info(0x3900, 'Ace', `ListFilter sendAccessibility send event, event info is ${JSON.stringify(f10)}`);
        });
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
            if (this.isSelectedArr) {
                this.isSelectedArr[b6][c6] = true;
                this.isSelectedArr[b6][this.selectedFilters[b6].index] = false;
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
        this.floatFilterBarAccessibilityText = '';
        if (this.selectedFilters) {
            const u9 = this.selectedFilters?.filter(y9 => y9?.value).map((x9) => {
                if (typeof x9.value !== 'string') {
                    return getContext()?.resourceManager?.getStringSync(x9.value?.id);
                }
                else {
                    return x9.value;
                }
            });
            this.floatFilterBarText = u9.join('/');
            this.floatFilterBarAccessibilityText = u9.join(' ');
        }
    }

    getFloatAccessibilityText(n9, o9) {
        let p9 = '';
        let q9 = this.filterAccessibilityText.accessibilityFilters;
        let r9 = this.filterAccessibilityText.accessibilityCollapsed;
        try {
            let t9 = '';
            if (typeof n9 === 'string') {
                t9 = n9;
            }
            else {
                t9 = getContext()?.resourceManager?.getStringSync(n9?.id);
            }
            switch (o9) {
                case FilterAccessibilityType.ACCESSIBILITY_TEXT:
                    p9 = `${q9},${r9},${t9}`;
                    break;
                case FilterAccessibilityType.ACCESSIBILITY_DESC:
                    p9 = this.filterAccessibilityText.accessibilityExpandDesc;
                    break;
                case FilterAccessibilityType.SEND_ACCESSIBILITY:
                    p9 = this.filterAccessibilityText.accessibilityExpanded;
                    break;
                default:
                    break;
            }
        }
        catch (q9) {
            let r9 = q9.code;
            let s9 = q9.message;
            hilog.error(0x3900, 'Ace', `Filter getAccessibilityText error, code: ${r9}, message: ${s9}`);
        }
        return p9;
    }

    sendFloatAccessibility(j9) {
        let k9 = ({
            type: 'announceForAccessibility',
            bundleName: this.bundleName,
            triggerAction: 'common',
            textAnnouncedForAccessibility: this.getFloatAccessibilityText(j9,
                FilterAccessibilityType.SEND_ACCESSIBILITY),
        });
        accessibility.sendAccessibilityEvent(k9);
        if (this.multiFilters && this.multiFilters.length > 0) {
            let m9 = ({
                type: 'requestFocusForAccessibility',
                bundleName: this.bundleName,
                triggerAction: 'common',
                customId: `filterMultiFilterRow_${this.filterId}_0`,
            });
            accessibility.sendAccessibilityEvent(m9);
        }
        else if (this.additionFilters && this.additionFilters.name) {
            let l9 = ({
                type: 'requestFocusForAccessibility',
                bundleName: this.bundleName,
                triggerAction: 'common',
                customId: `filterAdditionFiltersName_${this.filterId}`,
            });
            accessibility.sendAccessibilityEvent(l9);
        }
    }

    initParams() {
        if (!this.selectedFilters) {
            this.selectedFilters = [];
            for (let h9 of this.multiFilters) {
                let i9 = { name: h9.name, index: -1, value: '' };
                if (h9.options.length > 0) {
                    i9.index = 0;
                    i9.value = h9.options[0];
                }
                this.selectedFilters.push(i9);
            }
            if (this.additionFilters && this.additionFilters.name) {
                let g9 = { name: this.additionFilters.name, index: -1, value: '' };
                this.selectedFilters.push(g9);
            }
            this.refreshFloatFilterBarText();
        }
        if (!this.colorArr) {
            this.colorArr = [];
            this.backgroundColorArr = [];
            this.isBackgroundHover = [];
            this.fontWeightArr = [];
            this.isArrowIconDownArr = [];
            this.isSelectedArr = [];
            this.floatArrowBgColor = {
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_background'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
            for (let z8 of this.multiFilters) {
                let a9 = new ResourceArray();
                let b9 = new FontWeightArray();
                let c9 = new ResourceArray();
                let d9 = new BooleanArray();
                let e9 = new BooleanArray();
                for (let f9 of z8.options.keys()) {
                    if (f9 === 0) {
                        a9.push({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_text_primary_activated'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        b9.push(FontWeight.Medium);
                        e9.push(true);
                    }
                    else {
                        a9.push({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_text_primary'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        b9.push(FontWeight.Regular);
                        e9.push(false);
                    }
                    c9.push({
                        'id': -1,
                        'type': 10001,
                        params: ['sys.color.ohos_id_color_hover'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__'
                    });
                }
                this.colorArr.push(a9);
                this.fontWeightArr.push(b9);
                this.backgroundColorArr.push(c9);
                this.isBackgroundHover.push(d9);
                this.isArrowIconDownArr.push(new ObservedBoolean(true));
                this.isSelectedArr.push(e9);
            }
        }
        if (this.additionFilters && this.additionFilters.options) {
            this.additionColorArr = [];
            this.additionFontWeightArr = [];
            this.additionBackgroundColorArr = [];
            this.isAdditionBackgroundHover = [];
            for (let y8 = 0; y8 < this.additionFilters.options.length; y8++) {
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
            for (let x8 = 0; x8 < this.multiFilters.length; x8++) {
                this.twoLineModeItemNum.push(new ObservedNumber(this.multiFilters[x8].options.length));
                this.twoLineModeItemNumRecord.push(new ObservedNumber(this.multiFilters[x8].options.length));
                this.downArrowShowState.push(new ObservedBoolean(false));
            }
        }
    }

    ListFilter(z7 = null) {
        this.observeComponentCreation2((s8, t8) => {
            Column.create();
            Column.width(PERCENT_100);
            Column.align(Alignment.Start);
            Column.onAreaChange((v8, w8) => {
                if (!this.isFloatShowAllFilterWithoutAnimation && !this.isFloatBarShowWithoutAnimation) {
                    if (this.additionFilters !== null) {
                        this.filterDynamicHeight =
                            parseInt(w8.height.toString(), 0) + LIST_ROW_HEIGHT + FILTER_TOP_PADDING;
                    }
                    else {
                        this.filterDynamicHeight = parseInt(w8.height.toString(), 0) + FILTER_TOP_PADDING;
                    }
                    this.floatFilterPosition = -this.filterDynamicHeight;
                }
            });
        }, Column);
        this.observeComponentCreation2((c8, d8) => {
            ForEach.create();
            const e8 = (g8, h8) => {
                const i8 = g8;
                {
                    this.observeComponentCreation2((k8, l8) => {
                        if (l8) {
                            let m8 = new ListFilterRow(this, {
                                colorRow: this.colorArr ? this.colorArr[h8] : [],
                                fontWeightRow: this.fontWeightArr ? this.fontWeightArr[h8] : [],
                                backgroundColorRow: this.backgroundColorArr ? this.backgroundColorArr[h8] : [],
                                isBackgroundHoverRow: this.isBackgroundHover ? this.isBackgroundHover[h8] : [],
                                isSelectedRow: this.isSelectedArr ? this.isSelectedArr[h8] : [],
                                filterRow: i8,
                                onItemClick: (r8) => {
                                    this.filterItemClick(h8, r8);
                                },
                                rowIndex: h8,
                                filterAccessibilityText: this.filterAccessibilityText,
                            }, undefined, k8, () => {
                            }, { page: 'library2/src/main/ets/components/mainpage/MainPage.ets', line: 1174, col: 9 });
                            ViewPU.create(m8);
                            let n8 = () => {
                                return {
                                    colorRow: this.colorArr ? this.colorArr[h8] : [],
                                    fontWeightRow: this.fontWeightArr ? this.fontWeightArr[h8] : [],
                                    backgroundColorRow: this.backgroundColorArr ? this.backgroundColorArr[h8] : [],
                                    isBackgroundHoverRow: this.isBackgroundHover ? this.isBackgroundHover[h8] : [],
                                    isSelectedRow: this.isSelectedArr ? this.isSelectedArr[h8] : [],
                                    filterRow: i8,
                                    onItemClick: (q8) => {
                                        this.filterItemClick(h8, q8);
                                    },
                                    rowIndex: h8,
                                    filterAccessibilityText: this.filterAccessibilityText
                                };
                            };
                            m8.paramsGenerator_ = n8;
                        }
                        else {
                            this.updateStateVarsOfChildByElmtId(k8, {
                                colorRow: this.colorArr ? this.colorArr[h8] : [],
                                fontWeightRow: this.fontWeightArr ? this.fontWeightArr[h8] : [],
                                backgroundColorRow: this.backgroundColorArr ? this.backgroundColorArr[h8] : [],
                                isBackgroundHoverRow: this.isBackgroundHover ? this.isBackgroundHover[h8] : [],
                                isSelectedRow: this.isSelectedArr ? this.isSelectedArr[h8] : [],
                                filterAccessibilityText: this.filterAccessibilityText
                            });
                        }
                    }, { name: 'ListFilterRow' });
                }
            };
            this.forEachUpdateFunction(c8, this.multiFilters, e8, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Column.pop();
    }

    MultiLineFilter(b7 = null) {
        this.observeComponentCreation2((u7, v7) => {
            Column.create();
            Column.width(PERCENT_100);
            Column.onAreaChange((x7, y7) => {
                if (this.additionFilters !== null) {
                    this.filterDynamicHeight = parseInt(y7.height.toString(), 0) + LIST_ROW_HEIGHT + FILTER_TOP_PADDING;
                }
                else {
                    this.filterDynamicHeight = parseInt(y7.height.toString(), 0) + FILTER_TOP_PADDING;
                }
                if (!this.isFloatBarShowWithoutAnimation && !this.isFloatShowAllFilterWithoutAnimation) {
                    this.floatFilterPosition = -this.filterDynamicHeight;
                }
            });
        }, Column);
        this.observeComponentCreation2((e7, f7) => {
            ForEach.create();
            const g7 = (i7, m4) => {
                const n4 = i7;
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
                                isSelectedRow: this.isSelectedArr ? this.isSelectedArr[m4] : [],
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
                                filterId: this.filterId,
                                filterAccessibilityText: this.filterAccessibilityText,
                            }, undefined, o4, () => {
                            }, { page: 'library2/src/main/ets/components/mainpage/MainPage.ets', line: 1205, col: 9 });
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
                                    isSelectedRow: this.isSelectedArr ? this.isSelectedArr[m4] : [],
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
                                    fontSizeScale: this.fontSizeScale,
                                    filterId: this.filterId,
                                    filterAccessibilityText: this.filterAccessibilityText,
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
                                isSelectedRow: this.isSelectedArr ? this.isSelectedArr[m4] : [],
                                twoLineModeItemNumRecordRow: this.twoLineModeItemNumRecord ? this.twoLineModeItemNumRecord[m4] :
                                    new ObservedNumber(0),
                                isArrowIconDown: this.isArrowIconDownArr ? this.isArrowIconDownArr[m4] : new ObservedBoolean(false),
                                fontSizeScale: this.fontSizeScale,
                                filterAccessibilityText: this.filterAccessibilityText
                            });
                        }
                    }, { name: 'MultiFilterRow' });
                }
            };
            this.forEachUpdateFunction(e7, this.multiFilters, g7, undefined, true, false);
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
                this.additionFiltersSelectedIndex = e4;
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
                this.additionFiltersSelectedIndex = e4;
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
            this.additionFiltersSelectedIndex = -1;
        }
        if (this.selectedFilters) {
            this.onFilterChanged && this.onFilterChanged(this.selectedFilters);
        }
        this.colorRefresh = !this.colorRefresh;
        this.refreshFloatFilterBarText();
    }

    getSelected(w6) {
        let x6 = this.multiFilters.length;
        if (this.selectedFilters && this.selectedFilters[x6].index !== w6) {
            return false;
        }
        else {
            return true;
        }
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
                                Text.id(`filterAdditionFiltersName_${this.filterId}`);
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
                                    ListItem.accessibilityText(this.getAccessibilityText(v2,
                                        this.additionFiltersSelectedIndex === u2,
                                        FilterAccessibilityType.ACCESSIBILITY_TEXT));
                                    ListItem.accessibilityDescription(this.getAccessibilityText(v2,
                                        this.additionFiltersSelectedIndex === u2,
                                        FilterAccessibilityType.ACCESSIBILITY_DESC));
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
                                        this.sendAccessibility(v2, this.getSelected(u2));
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
                                }, {
                                    page: 'library2/src/main/ets/components/mainpage/MainPage.ets',
                                    line: 1389,
                                    col: 11
                                });
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
                                }, {
                                    page: 'library2/src/main/ets/components/mainpage/MainPage.ets',
                                    line: 1397,
                                    col: 9
                                });
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

    FloatFilterBar(m1 = null) {
        this.observeComponentCreation2((o2, p2) => {
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
        this.observeComponentCreation2((b2, c2) => {
            Column.create();
            Column.id(`FiliterFloatFilterBar_${this.getUniqueId()}`);
            Column.accessibilityText(this.getFloatAccessibilityText(this.floatFilterBarAccessibilityText,
                FilterAccessibilityType.ACCESSIBILITY_TEXT));
            Column.accessibilityDescription(this.getFloatAccessibilityText(this.floatFilterBarAccessibilityText,
                FilterAccessibilityType.ACCESSIBILITY_DESC));
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
            Column.onTouch((l2) => {
                if (l2.type === TouchType.Down) {
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
                }
                else if (l2.type === TouchType.Up || l2.type === TouchType.Cancel) {
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
                this.sendFloatAccessibility(this.floatFilterBarAccessibilityText);
            });
            Column.onHover((g2) => {
                if (g2) {
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
                }
                else {
                    Context.animateTo({
                        curve: FRICTION_CUBIC_BEZIER,
                        duration: ANIMATION_DURATION_250
                    }, () => {
                        this.isFloatArrowBgHover = false;
                    });
                }
            });
        }, Column);
        this.observeComponentCreation2((z1, a2) => {
            Row.create();
            Row.height(PERCENT_100);
            Row.alignItems(VerticalAlign.Center);
        }, Row);
        this.observeComponentCreation2((x1, y1) => {
            Row.create();
            Row.height(LIST_ROW_HEIGHT);
            Row.margin({ start: LengthMetrics.vp(FILTER_BAR_MARGIN) });
            Row.focusable(true);
        }, Row);
        this.observeComponentCreation2((v1, w1) => {
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
        this.observeComponentCreation2((t1, u1) => {
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