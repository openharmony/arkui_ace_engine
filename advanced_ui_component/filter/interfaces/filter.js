/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

var __decorate = (this && this.__decorate) || function (d33, e33, f33, g33) {
    var h33 = arguments.length, i33 = h33 < 3 ? e33 : g33 === null ? g33 = Object.getOwnPropertyDescriptor(e33, f33) : g33, j33;
    if (typeof Reflect === 'object' && typeof Reflect.decorate === 'function')
        i33 = Reflect.decorate(d33, e33, f33, g33);
    else
        for (var k33 = d33.length - 1; k33 >= 0; k33--)
            if (j33 = d33[k33])
                i33 = (h33 < 3 ? j33(i33) : h33 > 3 ? j33(e33, f33, i33) : j33(e33, f33)) || i33;
    return h33 > 3 && i33 && Object.defineProperty(e33, f33, i33), i33;
};
if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => { });
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
export var FilterType;
(function (c33) {
    c33[c33['MULTI_LINE_FILTER'] = 0] = 'MULTI_LINE_FILTER';
    c33[c33['LIST_FILTER'] = 1] = 'LIST_FILTER';
})(FilterType || (FilterType = {}));
var FilterAccessibilityType;
(function (b33) {
    b33[b33['ACCESSIBILITY_TEXT'] = 0] = 'ACCESSIBILITY_TEXT';
    b33[b33['ACCESSIBILITY_DESC'] = 1] = 'ACCESSIBILITY_DESC';
    b33[b33['SEND_ACCESSIBILITY'] = 2] = 'SEND_ACCESSIBILITY';
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
    constructor(a33) {
        this.value = a33;
    }
};
ObservedBoolean = __decorate([
    Observed
], ObservedBoolean);
export { ObservedBoolean };
let ObservedNumber = class ObservedNumber {
    constructor(z32) {
        this.value = z32;
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
    constructor(t32, u32, v32, w32 = -1, x32 = undefined, y32) {
        super(t32, v32, w32, y32);
        if (typeof x32 === 'function') {
            this.paramsGenerator_ = x32;
        }
        this.x0 = 0;
        this.y0 = 0;
        this.x1 = 0;
        this.y1 = 0;
        this.settings = new RenderingContextSettings(true);
        this.context2D = new CanvasRenderingContext2D(this.settings);
        this.setInitiallyProvidedValue(u32);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(s32) {
        if (s32.x0 !== undefined) {
            this.x0 = s32.x0;
        }
        if (s32.y0 !== undefined) {
            this.y0 = s32.y0;
        }
        if (s32.x1 !== undefined) {
            this.x1 = s32.x1;
        }
        if (s32.y1 !== undefined) {
            this.y1 = s32.y1;
        }
        if (s32.settings !== undefined) {
            this.settings = s32.settings;
        }
        if (s32.context2D !== undefined) {
            this.context2D = s32.context2D;
        }
    }
    updateStateVars(r32) {
    }
    purgeVariableDependenciesOnElmtId(q32) {
    }
    aboutToBeDeleted() {
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    initialRender() {
        this.observeComponentCreation2((o32, p32) => {
            Column.create();
            Column.blendMode(BlendMode.DST_OUT);
            Column.width(GRADIENT_WIDTH);
            Column.height(LIST_ROW_HEIGHT);
        }, Column);
        this.observeComponentCreation2((l32, m32) => {
            Canvas.create(this.context2D);
            Canvas.width(GRADIENT_WIDTH);
            Canvas.height(LIST_ROW_HEIGHT);
            Canvas.onReady(() => {
                let n32 = this.context2D.createLinearGradient(this.x0, this.y0, this.x1, this.y1);
                n32.addColorStop(0.0, '#ffffffff');
                n32.addColorStop(1, '#00ffffff');
                this.context2D.fillStyle = n32;
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
    constructor(f32, g32, h32, i32 = -1, j32 = undefined, k32) {
        super(f32, h32, i32, k32);
        if (typeof j32 === 'function') {
            this.paramsGenerator_ = j32;
        }
        this.__colorRow = new SynchedPropertyNesedObjectPU(g32.colorRow, this, 'colorRow');
        this.__fontWeightRow = new SynchedPropertyNesedObjectPU(g32.fontWeightRow, this, 'fontWeightRow');
        this.__backgroundColorRow = new SynchedPropertyNesedObjectPU(g32.backgroundColorRow, this, 'backgroundColorRow');
        this.__isBackgroundHoverRow = new SynchedPropertyNesedObjectPU(g32.isBackgroundHoverRow, this, 'isBackgroundHoverRow');
        this.__isSelectedRow = new SynchedPropertyNesedObjectPU(g32.isSelectedRow, this, 'isSelectedRow');
        this.__filterAccessibilityText = new SynchedPropertyNesedObjectPU(g32.filterAccessibilityText, this, 'filterAccessibilityText');
        this.filterRow = { name: '', options: [] };
        this.onItemClick = () => { };
        this.rowIndex = 0;
        this.maxAppFontScale = 1;
        this.isFollowingSystemFontScale = false;
        this.bundleName = '';
        this.filterId = this.getUniqueId();
        this.setInitiallyProvidedValue(g32);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(e32) {
        this.__colorRow.set(e32.colorRow);
        this.__fontWeightRow.set(e32.fontWeightRow);
        this.__backgroundColorRow.set(e32.backgroundColorRow);
        this.__isBackgroundHoverRow.set(e32.isBackgroundHoverRow);
        this.__isSelectedRow.set(e32.isSelectedRow);
        this.__filterAccessibilityText.set(e32.filterAccessibilityText);
        if (e32.filterRow !== undefined) {
            this.filterRow = e32.filterRow;
        }
        if (e32.onItemClick !== undefined) {
            this.onItemClick = e32.onItemClick;
        }
        if (e32.rowIndex !== undefined) {
            this.rowIndex = e32.rowIndex;
        }
        if (e32.maxAppFontScale !== undefined) {
            this.maxAppFontScale = e32.maxAppFontScale;
        }
        if (e32.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = e32.isFollowingSystemFontScale;
        }
        if (e32.bundleName !== undefined) {
            this.bundleName = e32.bundleName;
        }
        if (e32.filterId !== undefined) {
            this.filterId = e32.filterId;
        }
    }
    updateStateVars(d32) {
        this.__colorRow.set(d32.colorRow);
        this.__fontWeightRow.set(d32.fontWeightRow);
        this.__backgroundColorRow.set(d32.backgroundColorRow);
        this.__isBackgroundHoverRow.set(d32.isBackgroundHoverRow);
        this.__isSelectedRow.set(d32.isSelectedRow);
        this.__filterAccessibilityText.set(d32.filterAccessibilityText);
    }
    purgeVariableDependenciesOnElmtId(c32) {
        this.__colorRow.purgeDependencyOnElmtId(c32);
        this.__fontWeightRow.purgeDependencyOnElmtId(c32);
        this.__backgroundColorRow.purgeDependencyOnElmtId(c32);
        this.__isBackgroundHoverRow.purgeDependencyOnElmtId(c32);
        this.__isSelectedRow.purgeDependencyOnElmtId(c32);
        this.__filterAccessibilityText.purgeDependencyOnElmtId(c32);
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
            let b32 = this.getUIContext();
            this.isFollowingSystemFontScale = b32.isFollowingSystemFontScale();
            this.maxAppFontScale = b32.getMaxFontScale();
        }
        catch (y31) {
            let z31 = y31.code;
            let a32 = y31.message;
            hilog.error(ERROR_CODE, 'Ace', `Failed to init fontsizescale info, cause, code: ${z31}, message: ${a32}`);
        }
        this.bundleName = getContext(this)?.abilityInfo?.bundleName;
    }
    updateFontScale() {
        let w31 = this.getUIContext();
        let x31 = w31.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(x31, this.maxAppFontScale);
    }
    getAccessibilityText(o31, p31, q31) {
        let r31 = '';
        try {
            let v31 = '';
            if (typeof o31 === 'string') {
                v31 = o31;
            }
            else {
                v31 = getContext()?.resourceManager?.getStringSync(o31?.id);
            }
            switch (q31) {
                case FilterAccessibilityType.ACCESSIBILITY_TEXT:
                    r31 = p31 ? this.filterAccessibilityText.accessibilitySelectedText : v31;
                    break;
                case FilterAccessibilityType.ACCESSIBILITY_DESC:
                    r31 = p31 ? v31 : '';
                    break;
                case FilterAccessibilityType.SEND_ACCESSIBILITY:
                    r31 =
                        p31 ? `${this.filterAccessibilityText.accessibilitySelectedText},${v31}` : '';
                    break;
                default:
                    break;
            }
        }
        catch (s31) {
            let t31 = s31.code;
            let u31 = s31.message;
            hilog.error(0x3900, 'Ace', `Filter getAccessibilityText error, code: ${t31}, message: ${u31}`);
        }
        return r31;
    }
    sendAccessibility(l31, m31) {
        let n31 = ({
            type: 'announceForAccessibility',
            bundleName: this.bundleName,
            triggerAction: 'common',
            textAnnouncedForAccessibility: this.getAccessibilityText(l31, m31, FilterAccessibilityType.SEND_ACCESSIBILITY),
        });
        accessibility.sendAccessibilityEvent(n31).then(() => {
            hilog.info(0x3900, 'Ace', `ListFilter sendAccessibility send event, event info is ${JSON.stringify(n31)}`);
        });
    }
    initialRender() {
        this.observeComponentCreation2((j31, k31) => {
            Stack.create({ alignContent: Alignment.End });
            Stack.blendMode(BlendMode.SRC_OVER, BlendApplyType.OFFSCREEN);
        }, Stack);
        this.observeComponentCreation2((h31, i31) => {
            Stack.create({ alignContent: Alignment.Start });
        }, Stack);
        this.observeComponentCreation2((f31, g31) => {
            List.create();
            List.listDirection(Axis.Horizontal);
            List.scrollBar(BarState.Off);
            List.width(PERCENT_100);
            List.height(LIST_ROW_HEIGHT);
            List.align(Alignment.Start);
        }, List);
        this.observeComponentCreation2((b30, c30) => {
            ForEach.create();
            const d30 = (e30, f30) => {
                const g30 = e30;
                this.observeComponentCreation2((u30, v30) => {
                    If.create();
                    if (f30 === 0) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            {
                                const w30 = (d31, e31) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(d31);
                                    ListItem.create(y30, true);
                                    if (!e31) {
                                        ListItem.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                };
                                const x30 = (b31, c31) => {
                                    ListItem.create(y30, true);
                                    ListItem.width({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_max_padding_start'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                    ListItem.height(LIST_ROW_HEIGHT);
                                };
                                const y30 = (z30, a31) => {
                                    w30(z30, a31);
                                    ListItem.pop();
                                };
                                this.observeComponentCreation2(x30, ListItem);
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
                    const h30 = (s30, t30) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(s30);
                        ListItem.create(j30, true);
                        if (!t30) {
                            ListItem.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    };
                    const i30 = (o30, p30) => {
                        ListItem.create(j30, true);
                        ListItem.accessibilityText(this.getAccessibilityText(g30, this.isSelectedRow[f30], FilterAccessibilityType.ACCESSIBILITY_TEXT));
                        ListItem.accessibilityDescription(this.getAccessibilityText(g30, this.isSelectedRow[f30], FilterAccessibilityType.ACCESSIBILITY_DESC));
                        ListItem.id(`filterListFilterRow_${this.filterId}_${this.rowIndex}`);
                        ListItem.height(PERCENT_100);
                        ListItem.onClick(() => {
                            this.onItemClick(f30);
                            this.sendAccessibility(g30, true);
                        });
                        ListItem.focusable(true);
                        ViewStackProcessor.visualState('focused');
                        ListItem.border({
                            radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            width: FOCUS_BORDER_WIDTH,
                            color: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_focused_outline'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            style: BorderStyle.Solid
                        });
                        ListItem.padding({
                            start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH),
                            end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH)
                        });
                        ViewStackProcessor.visualState('normal');
                        ListItem.border({
                            radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            width: 0
                        });
                        ListItem.padding({ start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH), end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH) });
                        ViewStackProcessor.visualState();
                        ListItem.backgroundColor(this.isBackgroundHoverRow[f30] ? this.backgroundColorRow[f30] : TRANS_COLOR);
                        ListItem.onHover((r30) => {
                            Context.animateTo({
                                curve: FRICTION_CUBIC_BEZIER,
                                duration: ANIMATION_DURATION_250
                            }, () => {
                                if (r30) {
                                    this.backgroundColorRow[f30] = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_hover'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                                    this.isBackgroundHoverRow[f30] = true;
                                }
                                else {
                                    this.isBackgroundHoverRow[f30] = false;
                                }
                            });
                        });
                        ListItem.onTouch((q30) => {
                            if (q30.type === TouchType.Down) {
                                Context.animateTo({
                                    curve: SHARP_CUBIC_BEZIER,
                                    duration: ANIMATION_DURATION_100
                                }, () => {
                                    this.backgroundColorRow[f30] = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_click_effect'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                                    this.isBackgroundHoverRow[f30] = true;
                                });
                            }
                            else if (q30.type === TouchType.Up || q30.type === TouchType.Cancel) {
                                Context.animateTo({
                                    curve: SHARP_CUBIC_BEZIER,
                                    duration: ANIMATION_DURATION_100
                                }, () => {
                                    this.isBackgroundHoverRow[f30] = false;
                                });
                            }
                        });
                        ListItem.margin({ start: LengthMetrics.vp(f30 === 0 ? -TEXT_HOT_AREA_WIDTH : 0) });
                        ListItem.tabIndex(f30 === 0 ? 1 : -1);
                    };
                    const j30 = (k30, l30) => {
                        h30(k30, l30);
                        this.observeComponentCreation2((m30, n30) => {
                            Text.create(g30);
                            Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body3'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                            Text.minFontScale(1);
                            Text.maxFontScale(Math.min(this.updateFontScale(), MAX_FONT_SCALE));
                            Text.fontColor(this.colorRow[f30]);
                            Text.fontWeight(this.fontWeightRow[f30]);
                            Text.focusable(true);
                        }, Text);
                        Text.pop();
                        ListItem.pop();
                    };
                    this.observeComponentCreation2(i30, ListItem);
                    ListItem.pop();
                }
            };
            this.forEachUpdateFunction(b30, this.filterRow.options, d30, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        List.pop();
        {
            this.observeComponentCreation2((x29, y29) => {
                if (y29) {
                    let z29 = new GradientMask(this, {
                        x0: 0,
                        y0: LIST_ROW_HEIGHT / 2,
                        x1: GRADIENT_WIDTH,
                        y1: LIST_ROW_HEIGHT / 2
                    }, undefined, x29, () => { }, { page: 'library/src/main/ets/components/filter.ets', line: 322, col: 9 });
                    ViewPU.create(z29);
                    let a30 = () => {
                        return {
                            x0: 0,
                            y0: LIST_ROW_HEIGHT / 2,
                            x1: GRADIENT_WIDTH,
                            y1: LIST_ROW_HEIGHT / 2
                        };
                    };
                    z29.paramsGenerator_ = a30;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(x29, {});
                }
            }, { name: 'GradientMask' });
        }
        Stack.pop();
        {
            this.observeComponentCreation2((t29, u29) => {
                if (u29) {
                    let v29 = new GradientMask(this, {
                        x0: GRADIENT_WIDTH,
                        y0: LIST_ROW_HEIGHT / 2,
                        x1: 0,
                        y1: LIST_ROW_HEIGHT / 2
                    }, undefined, t29, () => { }, { page: 'library/src/main/ets/components/filter.ets', line: 330, col: 7 });
                    ViewPU.create(v29);
                    let w29 = () => {
                        return {
                            x0: GRADIENT_WIDTH,
                            y0: LIST_ROW_HEIGHT / 2,
                            x1: 0,
                            y1: LIST_ROW_HEIGHT / 2
                        };
                    };
                    v29.paramsGenerator_ = w29;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(t29, {});
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
    constructor(n29, o29, p29, q29 = -1, r29 = undefined, s29) {
        super(n29, p29, q29, s29);
        if (typeof r29 === 'function') {
            this.paramsGenerator_ = r29;
        }
        this.__colorRow = new SynchedPropertyNesedObjectPU(o29.colorRow, this, 'colorRow');
        this.__fontWeightRow = new SynchedPropertyNesedObjectPU(o29.fontWeightRow, this, 'fontWeightRow');
        this.__backgroundColorRow = new SynchedPropertyNesedObjectPU(o29.backgroundColorRow, this, 'backgroundColorRow');
        this.__isBackgroundHoverRow = new SynchedPropertyNesedObjectPU(o29.isBackgroundHoverRow, this, 'isBackgroundHoverRow');
        this.__twoLineModeItemNumRow = new SynchedPropertyNesedObjectPU(o29.twoLineModeItemNumRow, this, 'twoLineModeItemNumRow');
        this.__twoLineModeItemNumRecordRow = new SynchedPropertyNesedObjectPU(o29.twoLineModeItemNumRecordRow, this, 'twoLineModeItemNumRecordRow');
        this.__arrowShowStateRow = new SynchedPropertyNesedObjectPU(o29.arrowShowStateRow, this, 'arrowShowStateRow');
        this.__isArrowIconDown = new SynchedPropertyNesedObjectPU(o29.isArrowIconDown, this, 'isArrowIconDown');
        this.__isSelectedRow = new SynchedPropertyNesedObjectPU(o29.isSelectedRow, this, 'isSelectedRow');
        this.__filterAccessibilityText = new SynchedPropertyNesedObjectPU(o29.filterAccessibilityText, this, 'filterAccessibilityText');
        this.filterRow = null;
        this.onItemClick = () => { };
        this.__arrowBgColorRow = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_hover'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'arrowBgColorRow');
        this.__isArrowBgHoverRow = new ObservedPropertySimplePU(false, this, 'isArrowBgHoverRow');
        this.__fontSizeScale = new SynchedPropertyObjectOneWayPU(o29.fontSizeScale, this, 'fontSizeScale');
        this.__replaceEffect = new ObservedPropertySimplePU(0, this, 'replaceEffect');
        this.__isSendArrowAccessibility = new ObservedPropertySimplePU(false, this, 'isSendArrowAccessibility');
        this.filterColumnWidth = 0;
        this.lastFilterColumnWidth = 0;
        this.rowIndex = 0;
        this.maxAppFontScale = 1;
        this.isFollowingSystemFontScale = false;
        this.bundleName = '';
        this.filterId = this.getUniqueId();
        this.setInitiallyProvidedValue(o29);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(m29) {
        this.__colorRow.set(m29.colorRow);
        this.__fontWeightRow.set(m29.fontWeightRow);
        this.__backgroundColorRow.set(m29.backgroundColorRow);
        this.__isBackgroundHoverRow.set(m29.isBackgroundHoverRow);
        this.__twoLineModeItemNumRow.set(m29.twoLineModeItemNumRow);
        this.__twoLineModeItemNumRecordRow.set(m29.twoLineModeItemNumRecordRow);
        this.__arrowShowStateRow.set(m29.arrowShowStateRow);
        this.__isArrowIconDown.set(m29.isArrowIconDown);
        this.__isSelectedRow.set(m29.isSelectedRow);
        this.__filterAccessibilityText.set(m29.filterAccessibilityText);
        if (m29.filterRow !== undefined) {
            this.filterRow = m29.filterRow;
        }
        if (m29.onItemClick !== undefined) {
            this.onItemClick = m29.onItemClick;
        }
        if (m29.arrowBgColorRow !== undefined) {
            this.arrowBgColorRow = m29.arrowBgColorRow;
        }
        if (m29.isArrowBgHoverRow !== undefined) {
            this.isArrowBgHoverRow = m29.isArrowBgHoverRow;
        }
        if (m29.replaceEffect !== undefined) {
            this.replaceEffect = m29.replaceEffect;
        }
        if (m29.isSendArrowAccessibility !== undefined) {
            this.isSendArrowAccessibility = m29.isSendArrowAccessibility;
        }
        if (m29.filterColumnWidth !== undefined) {
            this.filterColumnWidth = m29.filterColumnWidth;
        }
        if (m29.lastFilterColumnWidth !== undefined) {
            this.lastFilterColumnWidth = m29.lastFilterColumnWidth;
        }
        if (m29.rowIndex !== undefined) {
            this.rowIndex = m29.rowIndex;
        }
        if (m29.maxAppFontScale !== undefined) {
            this.maxAppFontScale = m29.maxAppFontScale;
        }
        if (m29.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = m29.isFollowingSystemFontScale;
        }
        if (m29.bundleName !== undefined) {
            this.bundleName = m29.bundleName;
        }
        if (m29.filterId !== undefined) {
            this.filterId = m29.filterId;
        }
    }
    updateStateVars(l29) {
        this.__colorRow.set(l29.colorRow);
        this.__fontWeightRow.set(l29.fontWeightRow);
        this.__backgroundColorRow.set(l29.backgroundColorRow);
        this.__isBackgroundHoverRow.set(l29.isBackgroundHoverRow);
        this.__twoLineModeItemNumRow.set(l29.twoLineModeItemNumRow);
        this.__twoLineModeItemNumRecordRow.set(l29.twoLineModeItemNumRecordRow);
        this.__arrowShowStateRow.set(l29.arrowShowStateRow);
        this.__isArrowIconDown.set(l29.isArrowIconDown);
        this.__isSelectedRow.set(l29.isSelectedRow);
        this.__filterAccessibilityText.set(l29.filterAccessibilityText);
        this.__fontSizeScale.reset(l29.fontSizeScale);
    }
    purgeVariableDependenciesOnElmtId(k29) {
        this.__colorRow.purgeDependencyOnElmtId(k29);
        this.__fontWeightRow.purgeDependencyOnElmtId(k29);
        this.__backgroundColorRow.purgeDependencyOnElmtId(k29);
        this.__isBackgroundHoverRow.purgeDependencyOnElmtId(k29);
        this.__twoLineModeItemNumRow.purgeDependencyOnElmtId(k29);
        this.__twoLineModeItemNumRecordRow.purgeDependencyOnElmtId(k29);
        this.__arrowShowStateRow.purgeDependencyOnElmtId(k29);
        this.__isArrowIconDown.purgeDependencyOnElmtId(k29);
        this.__isSelectedRow.purgeDependencyOnElmtId(k29);
        this.__filterAccessibilityText.purgeDependencyOnElmtId(k29);
        this.__arrowBgColorRow.purgeDependencyOnElmtId(k29);
        this.__isArrowBgHoverRow.purgeDependencyOnElmtId(k29);
        this.__fontSizeScale.purgeDependencyOnElmtId(k29);
        this.__replaceEffect.purgeDependencyOnElmtId(k29);
        this.__isSendArrowAccessibility.purgeDependencyOnElmtId(k29);
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
    set arrowBgColorRow(j29) {
        this.__arrowBgColorRow.set(j29);
    }
    get isArrowBgHoverRow() {
        return this.__isArrowBgHoverRow.get();
    }
    set isArrowBgHoverRow(i29) {
        this.__isArrowBgHoverRow.set(i29);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(h29) {
        this.__fontSizeScale.set(h29);
    }
    get replaceEffect() {
        return this.__replaceEffect.get();
    }
    set replaceEffect(g29) {
        this.__replaceEffect.set(g29);
    }
    get isSendArrowAccessibility() {
        return this.__isSendArrowAccessibility.get();
    }
    set isSendArrowAccessibility(f29) {
        this.__isSendArrowAccessibility.set(f29);
    }
    aboutToAppear() {
        try {
            let e29 = this.getUIContext();
            this.isFollowingSystemFontScale = e29.isFollowingSystemFontScale();
            this.maxAppFontScale = e29.getMaxFontScale();
        }
        catch (b29) {
            let c29 = b29.code;
            let d29 = b29.message;
            hilog.error(ERROR_CODE, 'Ace', `Failed to init fontsizescale info, cause, code: ${c29}, message: ${d29}`);
        }
        this.bundleName = getContext(this)?.abilityInfo?.bundleName;
    }
    updateFontScale() {
        let z28 = this.getUIContext();
        let a29 = z28.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(a29, this.maxAppFontScale);
    }
    calcMultiFilterRowItemNum() {
        let t28 = this.filterColumnWidth;
        let u28 = 0;
        let v28 = 1;
        if (this.filterRow) {
            for (let w28 = 0; w28 < this.filterRow.options.length; w28++) {
                let x28 = this.filterRow.options[w28];
                let y28 = measure.measureText({
                    textContent: x28,
                    fontSize: `${FILTER_FONT_SIZE * Math.min(this.updateFontScale(), MAX_FONT_SCALE)}vp`,
                });
                if (w28 === 0) {
                    continue;
                }
                else {
                    y28 += vp2px(TEXT_HOT_AREA_WIDTH * 2);
                }
                if (t28 - y28 >= 0) {
                    t28 -= y28;
                    u28 += 1;
                }
                else {
                    if (u28 === 0) {
                        u28++;
                        t28 = 0;
                    }
                    if (v28 === 1) {
                        v28 += 1;
                        t28 =
                            this.filterColumnWidth - vp2px(ARROW_IMG_SIZE * (this.fontSizeScale ?? DEFAULT_SYMBOL_FONT_SCALE));
                        w28--;
                    }
                    else {
                        break;
                    }
                }
            }
        }
        return u28;
    }
    getAccessibilityText(l28, m28, n28) {
        let o28 = '';
        try {
            let s28 = '';
            if (typeof l28 === 'string') {
                s28 = l28;
            }
            else {
                s28 = getContext()?.resourceManager?.getStringSync(l28?.id);
            }
            switch (n28) {
                case FilterAccessibilityType.ACCESSIBILITY_TEXT:
                    o28 = m28 ? this.filterAccessibilityText.accessibilitySelectedText : s28;
                    break;
                case FilterAccessibilityType.ACCESSIBILITY_DESC:
                    o28 = m28 ? s28 : '';
                    break;
                case FilterAccessibilityType.SEND_ACCESSIBILITY:
                    o28 =
                        m28 ? `${this.filterAccessibilityText.accessibilitySelectedText},${s28}` : '';
                    break;
                default:
                    break;
            }
        }
        catch (p28) {
            let q28 = p28.code;
            let r28 = p28.message;
            hilog.error(0x3900, 'Ace', `Filter getAccessibilityText error, code: ${q28}, message: ${r28}`);
        }
        return o28;
    }
    sendAccessibility(i28, j28) {
        let k28 = ({
            type: 'announceForAccessibility',
            bundleName: this.bundleName,
            triggerAction: 'common',
            textAnnouncedForAccessibility: this.getAccessibilityText(i28, j28, FilterAccessibilityType.SEND_ACCESSIBILITY),
        });
        accessibility.sendAccessibilityEvent(k28);
    }
    sendArrowAccessibility(g28) {
        if (this.isSendArrowAccessibility) {
            let h28 = ({
                type: 'requestFocusForAccessibility',
                bundleName: this.bundleName,
                triggerAction: 'common',
                customId: g28,
            });
            accessibility.sendAccessibilityEvent(h28).then(() => {
                setTimeout(() => {
                    this.isSendArrowAccessibility = false;
                }, 200);
            });
        }
    }
    DownAndUpArrow(x27 = null) {
        this.observeComponentCreation2((e28, f28) => {
            Row.create();
            Row.height(LIST_ROW_HEIGHT);
        }, Row);
        this.observeComponentCreation2((a28, b28) => {
            Button.createWithChild({ stateEffect: false, type: ButtonType.Normal });
            Button.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }
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
            Button.accessibilityRole(this.isSendArrowAccessibility ? AccessibilityRoleType.ROLE_NONE : AccessibilityRoleType.BUTTON);
            Button.id(`filterDownAndUpArrow_${this.getUniqueId()}_${this.rowIndex}`);
            Button.visibility(this.arrowShowStateRow.value ? Visibility.Visible : Visibility.Hidden);
            Button.onHover((d28) => {
                Context.animateTo({
                    curve: FRICTION_CUBIC_BEZIER,
                    duration: ANIMATION_DURATION_250
                }, () => {
                    if (d28) {
                        this.arrowBgColorRow = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_hover'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                        this.isArrowBgHoverRow = true;
                    }
                    else {
                        this.isArrowBgHoverRow = false;
                    }
                });
            });
            Button.onTouch((c28) => {
                if (c28.type === TouchType.Down) {
                    Context.animateTo({
                        curve: SHARP_CUBIC_BEZIER,
                        duration: ANIMATION_DURATION_100
                    }, () => {
                        this.arrowBgColorRow = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_click_effect'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                        this.isArrowBgHoverRow = true;
                    });
                }
                else if (c28.type === TouchType.Up || c28.type === TouchType.Cancel) {
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
        this.observeComponentCreation2((y27, z27) => {
            SymbolGlyph.create(this.isArrowIconDown.value ? { 'id': -1, 'type': 40000, params: ['sys.symbol.chevron_down'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 40000, params: ['sys.symbol.chevron_up'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            SymbolGlyph.fontSize(`${(this.fontSizeScale ?? DEFAULT_SYMBOL_FONT_SCALE) * SYMBOL_SIZE}vp`);
            SymbolGlyph.height(LIST_ROW_HEIGHT);
            SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_tertiary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
            SymbolGlyph.symbolEffect(new ReplaceSymbolEffect(EffectScope.WHOLE), this.replaceEffect);
            SymbolGlyph.focusable(true);
            SymbolGlyph.draggable(false);
            ViewStackProcessor.visualState('focused');
            SymbolGlyph.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                width: FOCUS_BORDER_WIDTH,
                color: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_focused_outline'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                style: BorderStyle.Solid
            });
            SymbolGlyph.offset({ x: -FOCUS_BORDER_WIDTH });
            ViewStackProcessor.visualState('normal');
            SymbolGlyph.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
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
        this.observeComponentCreation2((v27, w27) => {
            Flex.create();
            Flex.width(PERCENT_100);
            Flex.padding({
                start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_max_padding_start'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_max_padding_end'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' })
            });
        }, Flex);
        this.observeComponentCreation2((p27, q27) => {
            If.create();
            if (this.filterRow?.options && this.filterRow?.options.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    if (!If.canRetake(`filterMultiFilterRow_${this.filterId}_${this.rowIndex}`)) {
                        this.observeComponentCreation2((r27, s27) => {
                            Text.create(this.filterRow?.options[0]);
                            Text.height(LIST_ROW_HEIGHT);
                            Text.margin({ start: LengthMetrics.vp(-TEXT_HOT_AREA_WIDTH) });
                            Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body3'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                            Text.minFontScale(1);
                            Text.maxFontScale(Math.min(this.updateFontScale(), MAX_FONT_SCALE));
                            Text.maxLines(1);
                            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                            Text.fontColor(this.colorRow[0]);
                            Text.fontWeight(this.fontWeightRow[0]);
                            Text.backgroundColor(this.isBackgroundHoverRow[0] ? this.backgroundColorRow[0] : TRANS_COLOR);
                            Text.accessibilityText(this.getAccessibilityText(this.filterRow?.options[0], this.isSelectedRow[0], FilterAccessibilityType.ACCESSIBILITY_TEXT));
                            Text.accessibilityDescription(this.getAccessibilityText(this.filterRow?.options[0], this.isSelectedRow[0], FilterAccessibilityType.ACCESSIBILITY_DESC));
                            Text.onClick(() => {
                                this.onItemClick(0);
                                this.sendAccessibility(this.filterRow?.options[0], true);
                            });
                            Text.id(`filterMultiFilterRow_${this.filterId}_${this.rowIndex}`);
                            Text.focusable(true);
                            Text.onHover((u27) => {
                                Context.animateTo({
                                    curve: FRICTION_CUBIC_BEZIER,
                                    duration: ANIMATION_DURATION_250
                                }, () => {
                                    if (u27) {
                                        this.backgroundColorRow[0] = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_hover'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                                        this.isBackgroundHoverRow[0] = true;
                                    }
                                    else {
                                        this.isBackgroundHoverRow[0] = false;
                                    }
                                });
                            });
                            Text.onTouch((t27) => {
                                if (t27.type === TouchType.Down) {
                                    Context.animateTo({
                                        curve: SHARP_CUBIC_BEZIER,
                                        duration: ANIMATION_DURATION_100
                                    }, () => {
                                        this.backgroundColorRow[0] = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_click_effect'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                                        this.isBackgroundHoverRow[0] = true;
                                    });
                                }
                                else if (t27.type === TouchType.Up || t27.type === TouchType.Cancel) {
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
                                radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                width: FOCUS_BORDER_WIDTH,
                                color: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_focused_outline'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                style: BorderStyle.Solid
                            });
                            Text.padding({
                                start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH),
                                end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH)
                            });
                            ViewStackProcessor.visualState('normal');
                            Text.border({
                                radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                width: 0
                            });
                            Text.padding({ start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH), end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH) });
                            ViewStackProcessor.visualState();
                            Text.constraintSize({ maxWidth: '50%' });
                            Text.flexShrink(0);
                            Text.tabIndex(1);
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
        this.observeComponentCreation2((j27, k27) => {
            Row.create();
            Row.width(PERCENT_100);
            Row.onAreaChange((l27, m27) => {
                this.filterColumnWidth = vp2px(parseInt(m27.width.toString(), 0));
                if (this.twoLineModeItemNumRow.value === 0) {
                    let o27 = this.calcMultiFilterRowItemNum();
                    this.twoLineModeItemNumRow.value = o27;
                    this.twoLineModeItemNumRecordRow.value = o27;
                    if (this.filterRow && o27 < this.filterRow.options.length - 1) {
                        this.arrowShowStateRow.value = true;
                    }
                    else {
                        this.arrowShowStateRow.value = false;
                    }
                }
                else if (this.filterColumnWidth !== this.lastFilterColumnWidth) {
                    let n27 = this.calcMultiFilterRowItemNum();
                    if (this.filterRow && n27 < this.filterRow.options.length - 1) {
                        if (!this.arrowShowStateRow.value || this.isArrowIconDown.value) {
                            this.arrowShowStateRow.value = true;
                            this.isArrowIconDown.value = true;
                            this.twoLineModeItemNumRow.value = n27;
                        }
                    }
                    else {
                        this.arrowShowStateRow.value = false;
                        this.isArrowIconDown.value = false;
                        this.twoLineModeItemNumRow.value = n27;
                    }
                    this.twoLineModeItemNumRecordRow.value = n27;
                }
                this.lastFilterColumnWidth = this.filterColumnWidth;
            });
        }, Row);
        this.observeComponentCreation2((h27, i27) => {
            Flex.create({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap });
        }, Flex);
        this.observeComponentCreation2((v26, w26) => {
            ForEach.create();
            const x26 = (y26, z26) => {
                const a27 = y26;
                this.observeComponentCreation2((b27, c27) => {
                    If.create();
                    if (z26 > 0) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((d27, e27) => {
                                Text.create(a27);
                                Text.transition(TransitionEffect.OPACITY);
                                Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body3'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                Text.minFontScale(1);
                                Text.maxFontScale(Math.min(this.updateFontScale(), MAX_FONT_SCALE));
                                Text.maxLines(1);
                                Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                                Text.height(LIST_ROW_HEIGHT);
                                Text.fontColor(this.colorRow[z26]);
                                Text.fontWeight(this.fontWeightRow[z26]);
                                Text.accessibilityText(this.getAccessibilityText(a27, this.isSelectedRow[z26], FilterAccessibilityType.ACCESSIBILITY_TEXT));
                                Text.accessibilityDescription(this.getAccessibilityText(a27, this.isSelectedRow[z26], FilterAccessibilityType.ACCESSIBILITY_DESC));
                                Text.backgroundColor(this.isBackgroundHoverRow[z26] ?
                                this.backgroundColorRow[z26] : TRANS_COLOR);
                                Text.onClick(() => {
                                    this.onItemClick(z26);
                                    this.sendAccessibility(a27, true);
                                });
                                Text.onHover((g27) => {
                                    Context.animateTo({
                                        curve: FRICTION_CUBIC_BEZIER,
                                        duration: ANIMATION_DURATION_250
                                    }, () => {
                                        if (g27) {
                                            this.backgroundColorRow[z26] = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_hover'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                                            this.isBackgroundHoverRow[z26] = true;
                                        }
                                        else {
                                            this.isBackgroundHoverRow[z26] = false;
                                        }
                                    });
                                });
                                Text.onTouch((f27) => {
                                    if (f27.type === TouchType.Down) {
                                        Context.animateTo({
                                            curve: SHARP_CUBIC_BEZIER,
                                            duration: ANIMATION_DURATION_100
                                        }, () => {
                                            this.backgroundColorRow[z26] = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_click_effect'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                                            this.isBackgroundHoverRow[z26] = true;
                                        });
                                    }
                                    else if (f27.type === TouchType.Up || f27.type === TouchType.Cancel) {
                                        Context.animateTo({
                                            curve: SHARP_CUBIC_BEZIER,
                                            duration: ANIMATION_DURATION_100
                                        }, () => {
                                            this.isBackgroundHoverRow[z26] = false;
                                        });
                                    }
                                });
                                Text.focusable(true);
                                ViewStackProcessor.visualState('focused');
                                Text.border({
                                    radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                    width: FOCUS_BORDER_WIDTH,
                                    color: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_focused_outline'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                    style: BorderStyle.Solid
                                });
                                Text.padding({
                                    start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH),
                                    end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH)
                                });
                                ViewStackProcessor.visualState('normal');
                                Text.border({
                                    radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
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
            this.forEachUpdateFunction(v26, this.filterRow?.options.slice(0, this.twoLineModeItemNumRow.value + 1), x26, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        this.observeComponentCreation2((t26, u26) => {
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
    constructor(m26, n26, o26, p26 = -1, q26 = undefined, r26) {
        super(m26, o26, p26, r26);
        if (typeof q26 === 'function') {
            this.paramsGenerator_ = q26;
        }
        this.container = undefined;
        this.__multiFilters = new SynchedPropertyObjectOneWayPU(n26.multiFilters, this, 'multiFilters');
        this.__additionFilters = new SynchedPropertyObjectOneWayPU(n26.additionFilters, this, 'additionFilters');
        this.onFilterChanged = null;
        this.__filterType = new SynchedPropertySimpleOneWayPU(n26.filterType, this, 'filterType');
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
            onConfigurationUpdated: (s26) => {
                this.fontSizeScale = Math.min(this.updateFontScale(), MAX_SYMBOL_FONT_SCALE);
                this.fontSizeScale = Math.max(this.fontSizeScale, MIN_SYMBOL_FONT_SCALE);
                this.initAccessibilityResource();
            },
            onMemoryLevel() {
            }
        };
        this.__additionFiltersSelectedIndex = new ObservedPropertySimplePU(-1, this, 'additionFiltersSelectedIndex');
        this.__floatFilterBarAccessibilityText = new ObservedPropertySimplePU('', this, 'floatFilterBarAccessibilityText');
        this.__filterAccessibilityText = new ObservedPropertyObjectPU(new FilterAccessibilityText(), this, 'filterAccessibilityText');
        this.bundleName = '';
        this.filterId = this.getUniqueId();
        this.setInitiallyProvidedValue(n26);
        this.declareWatch('isFloatBarShow', this.updateFocusForAccessibility);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(l26) {
        if (l26.container !== undefined) {
            this.container = l26.container;
        }
        if (l26.multiFilters === undefined) {
            this.__multiFilters.set([]);
        }
        if (l26.additionFilters === undefined) {
            this.__additionFilters.set(null);
        }
        if (l26.onFilterChanged !== undefined) {
            this.onFilterChanged = l26.onFilterChanged;
        }
        if (l26.filterType === undefined) {
            this.__filterType.set(FilterType.LIST_FILTER);
        }
        if (l26.selectedFilters !== undefined) {
            this.selectedFilters = l26.selectedFilters;
        }
        if (l26.colorArr !== undefined) {
            this.colorArr = l26.colorArr;
        }
        if (l26.fontWeightArr !== undefined) {
            this.fontWeightArr = l26.fontWeightArr;
        }
        if (l26.backgroundColorArr !== undefined) {
            this.backgroundColorArr = l26.backgroundColorArr;
        }
        if (l26.isBackgroundHover !== undefined) {
            this.isBackgroundHover = l26.isBackgroundHover;
        }
        if (l26.floatArrowBgColor !== undefined) {
            this.floatArrowBgColor = l26.floatArrowBgColor;
        }
        if (l26.isFloatArrowBgHover !== undefined) {
            this.isFloatArrowBgHover = l26.isFloatArrowBgHover;
        }
        if (l26.isArrowIconDownArr !== undefined) {
            this.isArrowIconDownArr = l26.isArrowIconDownArr;
        }
        if (l26.additionColorArr !== undefined) {
            this.additionColorArr = l26.additionColorArr;
        }
        if (l26.additionFontWeightArr !== undefined) {
            this.additionFontWeightArr = l26.additionFontWeightArr;
        }
        if (l26.additionBackgroundColorArr !== undefined) {
            this.additionBackgroundColorArr = l26.additionBackgroundColorArr;
        }
        if (l26.isAdditionBackgroundHover !== undefined) {
            this.isAdditionBackgroundHover = l26.isAdditionBackgroundHover;
        }
        if (l26.isSelectedArr !== undefined) {
            this.isSelectedArr = l26.isSelectedArr;
        }
        if (l26.colorRefresh !== undefined) {
            this.colorRefresh = l26.colorRefresh;
        }
        if (l26.isFloatBarShow !== undefined) {
            this.isFloatBarShow = l26.isFloatBarShow;
        }
        if (l26.isFloatBarShowWithoutAnimation !== undefined) {
            this.isFloatBarShowWithoutAnimation = l26.isFloatBarShowWithoutAnimation;
        }
        if (l26.isFloatShowAllFilter !== undefined) {
            this.isFloatShowAllFilter = l26.isFloatShowAllFilter;
        }
        if (l26.isFloatShowAllFilterWithoutAnimation !== undefined) {
            this.isFloatShowAllFilterWithoutAnimation = l26.isFloatShowAllFilterWithoutAnimation;
        }
        if (l26.floatFilterPosition !== undefined) {
            this.floatFilterPosition = l26.floatFilterPosition;
        }
        if (l26.floatFilterBarHeight !== undefined) {
            this.floatFilterBarHeight = l26.floatFilterBarHeight;
        }
        if (l26.floatFilterBarPosition !== undefined) {
            this.floatFilterBarPosition = l26.floatFilterBarPosition;
        }
        if (l26.filterDynamicHeight !== undefined) {
            this.filterDynamicHeight = l26.filterDynamicHeight;
        }
        if (l26.twoLineModeItemNum !== undefined) {
            this.twoLineModeItemNum = l26.twoLineModeItemNum;
        }
        if (l26.twoLineModeItemNumRecord !== undefined) {
            this.twoLineModeItemNumRecord = l26.twoLineModeItemNumRecord;
        }
        if (l26.downArrowShowState !== undefined) {
            this.downArrowShowState = l26.downArrowShowState;
        }
        if (l26.floatFilterBarText !== undefined) {
            this.floatFilterBarText = l26.floatFilterBarText;
        }
        if (l26.maxAppFontScale !== undefined) {
            this.maxAppFontScale = l26.maxAppFontScale;
        }
        if (l26.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = l26.isFollowingSystemFontScale;
        }
        if (l26.fontSizeScale !== undefined) {
            this.fontSizeScale = l26.fontSizeScale;
        }
        if (l26.callbackId !== undefined) {
            this.callbackId = l26.callbackId;
        }
        if (l26.callbacks !== undefined) {
            this.callbacks = l26.callbacks;
        }
        if (l26.additionFiltersSelectedIndex !== undefined) {
            this.additionFiltersSelectedIndex = l26.additionFiltersSelectedIndex;
        }
        if (l26.floatFilterBarAccessibilityText !== undefined) {
            this.floatFilterBarAccessibilityText = l26.floatFilterBarAccessibilityText;
        }
        if (l26.filterAccessibilityText !== undefined) {
            this.filterAccessibilityText = l26.filterAccessibilityText;
        }
        if (l26.bundleName !== undefined) {
            this.bundleName = l26.bundleName;
        }
        if (l26.filterId !== undefined) {
            this.filterId = l26.filterId;
        }
    }
    updateStateVars(k26) {
        this.__multiFilters.reset(k26.multiFilters);
        this.__additionFilters.reset(k26.additionFilters);
        this.__filterType.reset(k26.filterType);
    }
    purgeVariableDependenciesOnElmtId(j26) {
        this.__multiFilters.purgeDependencyOnElmtId(j26);
        this.__additionFilters.purgeDependencyOnElmtId(j26);
        this.__filterType.purgeDependencyOnElmtId(j26);
        this.__colorArr.purgeDependencyOnElmtId(j26);
        this.__fontWeightArr.purgeDependencyOnElmtId(j26);
        this.__backgroundColorArr.purgeDependencyOnElmtId(j26);
        this.__isBackgroundHover.purgeDependencyOnElmtId(j26);
        this.__floatArrowBgColor.purgeDependencyOnElmtId(j26);
        this.__isFloatArrowBgHover.purgeDependencyOnElmtId(j26);
        this.__isArrowIconDownArr.purgeDependencyOnElmtId(j26);
        this.__additionColorArr.purgeDependencyOnElmtId(j26);
        this.__additionFontWeightArr.purgeDependencyOnElmtId(j26);
        this.__additionBackgroundColorArr.purgeDependencyOnElmtId(j26);
        this.__isAdditionBackgroundHover.purgeDependencyOnElmtId(j26);
        this.__isSelectedArr.purgeDependencyOnElmtId(j26);
        this.__colorRefresh.purgeDependencyOnElmtId(j26);
        this.__isFloatBarShow.purgeDependencyOnElmtId(j26);
        this.__isFloatShowAllFilter.purgeDependencyOnElmtId(j26);
        this.__floatFilterPosition.purgeDependencyOnElmtId(j26);
        this.__floatFilterBarHeight.purgeDependencyOnElmtId(j26);
        this.__floatFilterBarPosition.purgeDependencyOnElmtId(j26);
        this.__twoLineModeItemNum.purgeDependencyOnElmtId(j26);
        this.__twoLineModeItemNumRecord.purgeDependencyOnElmtId(j26);
        this.__downArrowShowState.purgeDependencyOnElmtId(j26);
        this.__floatFilterBarText.purgeDependencyOnElmtId(j26);
        this.__fontSizeScale.purgeDependencyOnElmtId(j26);
        this.__additionFiltersSelectedIndex.purgeDependencyOnElmtId(j26);
        this.__floatFilterBarAccessibilityText.purgeDependencyOnElmtId(j26);
        this.__filterAccessibilityText.purgeDependencyOnElmtId(j26);
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
    set multiFilters(i26) {
        this.__multiFilters.set(i26);
    }
    get additionFilters() {
        return this.__additionFilters.get();
    }
    set additionFilters(h26) {
        this.__additionFilters.set(h26);
    }
    get filterType() {
        return this.__filterType.get();
    }
    set filterType(g26) {
        this.__filterType.set(g26);
    }
    get colorArr() {
        return this.__colorArr.get();
    }
    set colorArr(f26) {
        this.__colorArr.set(f26);
    }
    get fontWeightArr() {
        return this.__fontWeightArr.get();
    }
    set fontWeightArr(e26) {
        this.__fontWeightArr.set(e26);
    }
    get backgroundColorArr() {
        return this.__backgroundColorArr.get();
    }
    set backgroundColorArr(d26) {
        this.__backgroundColorArr.set(d26);
    }
    get isBackgroundHover() {
        return this.__isBackgroundHover.get();
    }
    set isBackgroundHover(c26) {
        this.__isBackgroundHover.set(c26);
    }
    get floatArrowBgColor() {
        return this.__floatArrowBgColor.get();
    }
    set floatArrowBgColor(b26) {
        this.__floatArrowBgColor.set(b26);
    }
    get isFloatArrowBgHover() {
        return this.__isFloatArrowBgHover.get();
    }
    set isFloatArrowBgHover(a26) {
        this.__isFloatArrowBgHover.set(a26);
    }
    get isArrowIconDownArr() {
        return this.__isArrowIconDownArr.get();
    }
    set isArrowIconDownArr(z25) {
        this.__isArrowIconDownArr.set(z25);
    }
    get additionColorArr() {
        return this.__additionColorArr.get();
    }
    set additionColorArr(y25) {
        this.__additionColorArr.set(y25);
    }
    get additionFontWeightArr() {
        return this.__additionFontWeightArr.get();
    }
    set additionFontWeightArr(x25) {
        this.__additionFontWeightArr.set(x25);
    }
    get additionBackgroundColorArr() {
        return this.__additionBackgroundColorArr.get();
    }
    set additionBackgroundColorArr(w25) {
        this.__additionBackgroundColorArr.set(w25);
    }
    get isAdditionBackgroundHover() {
        return this.__isAdditionBackgroundHover.get();
    }
    set isAdditionBackgroundHover(v25) {
        this.__isAdditionBackgroundHover.set(v25);
    }
    get isSelectedArr() {
        return this.__isSelectedArr.get();
    }
    set isSelectedArr(u25) {
        this.__isSelectedArr.set(u25);
    }
    get colorRefresh() {
        return this.__colorRefresh.get();
    }
    set colorRefresh(t25) {
        this.__colorRefresh.set(t25);
    }
    get isFloatBarShow() {
        return this.__isFloatBarShow.get();
    }
    set isFloatBarShow(s25) {
        this.__isFloatBarShow.set(s25);
    }
    get isFloatShowAllFilter() {
        return this.__isFloatShowAllFilter.get();
    }
    set isFloatShowAllFilter(r25) {
        this.__isFloatShowAllFilter.set(r25);
    }
    get floatFilterPosition() {
        return this.__floatFilterPosition.get();
    }
    set floatFilterPosition(q25) {
        this.__floatFilterPosition.set(q25);
    }
    get floatFilterBarHeight() {
        return this.__floatFilterBarHeight.get();
    }
    set floatFilterBarHeight(p25) {
        this.__floatFilterBarHeight.set(p25);
    }
    get floatFilterBarPosition() {
        return this.__floatFilterBarPosition.get();
    }
    set floatFilterBarPosition(o25) {
        this.__floatFilterBarPosition.set(o25);
    }
    get twoLineModeItemNum() {
        return this.__twoLineModeItemNum.get();
    }
    set twoLineModeItemNum(n25) {
        this.__twoLineModeItemNum.set(n25);
    }
    get twoLineModeItemNumRecord() {
        return this.__twoLineModeItemNumRecord.get();
    }
    set twoLineModeItemNumRecord(m25) {
        this.__twoLineModeItemNumRecord.set(m25);
    }
    get downArrowShowState() {
        return this.__downArrowShowState.get();
    }
    set downArrowShowState(l25) {
        this.__downArrowShowState.set(l25);
    }
    get floatFilterBarText() {
        return this.__floatFilterBarText.get();
    }
    set floatFilterBarText(k25) {
        this.__floatFilterBarText.set(k25);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(j25) {
        this.__fontSizeScale.set(j25);
    }
    get additionFiltersSelectedIndex() {
        return this.__additionFiltersSelectedIndex.get();
    }
    set additionFiltersSelectedIndex(i25) {
        this.__additionFiltersSelectedIndex.set(i25);
    }
    get floatFilterBarAccessibilityText() {
        return this.__floatFilterBarAccessibilityText.get();
    }
    set floatFilterBarAccessibilityText(h25) {
        this.__floatFilterBarAccessibilityText.set(h25);
    }
    get filterAccessibilityText() {
        return this.__filterAccessibilityText.get();
    }
    set filterAccessibilityText(g25) {
        this.__filterAccessibilityText.set(g25);
    }
    textColor(e25, f25) {
        if (this.selectedFilters && this.selectedFilters.length > e25 &&
            this.selectedFilters[e25].index === f25) {
            return { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary_activated'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        }
        return { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    }
    aboutToAppear() {
        this.initParams();
        this.initAccessibilityResource();
        try {
            let d25 = this.getUIContext();
            this.isFollowingSystemFontScale = d25.isFollowingSystemFontScale();
            this.maxAppFontScale = d25.getMaxFontScale();
            this.fontSizeScale = Math.min(this.updateFontScale(), MAX_SYMBOL_FONT_SCALE);
            this.fontSizeScale = Math.max(this.fontSizeScale, MIN_SYMBOL_FONT_SCALE);
            this.callbackId = d25.getHostContext()?.getApplicationContext()?.on('environment', this.callbacks);
        }
        catch (a25) {
            let b25 = a25.code;
            let c25 = a25.message;
            hilog.error(ERROR_CODE, 'Ace', `Failed to init fontsizescale info, cause, code: ${b25}, message: ${c25}`);
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
            let z24 = getContext()?.resourceManager;
            this.filterAccessibilityText.accessibilitySelectedText =
                z24?.getStringByNameSync('filter_accessibility_selected');
            this.filterAccessibilityText.accessibilityUnselectedText =
                z24?.getStringByNameSync('filter_accessibility_unselected');
            this.filterAccessibilityText.accessibilityFilters =
                z24?.getStringByNameSync('filter_accessibility_filters');
            this.filterAccessibilityText.accessibilitySelectedDesc =
                z24?.getStringByNameSync('filter_accessibility_select_desc');
            this.filterAccessibilityText.accessibilityUnselectedDesc =
                z24?.getStringByNameSync('filter_accessibility_unselect_desc');
            this.filterAccessibilityText.accessibilityExpandDesc =
                z24?.getStringByNameSync('filter_accessibility_expand_desc');
            this.filterAccessibilityText.accessibilityExpanded =
                z24?.getStringByNameSync('filter_accessibility_expanded');
            this.filterAccessibilityText.accessibilityCollapsed =
                z24?.getStringByNameSync('filter_accessibility_collapsed');
            this.filterAccessibilityText.accessibilityExpand =
                z24?.getStringByNameSync('filter_accessibility_expand');
            this.filterAccessibilityText.accessibilityCollapse =
                z24?.getStringByNameSync('filter_accessibility_collapse');
        }
        catch (w24) {
            let x24 = w24.code;
            let y24 = w24.message;
            hilog.error(ERROR_CODE, 'Ace', `Filter failed to initAccessibilityResource, code: ${x24}, message: ${y24}`);
        }
    }
    updateFocusForAccessibility() {
        if (this.isFloatBarShow) {
            let v24 = ({
                type: 'requestFocusForAccessibility',
                bundleName: this.bundleName,
                triggerAction: 'common',
                customId: `FiliterFloatFilterBar_${this.getUniqueId()}`,
            });
            accessibility.sendAccessibilityEvent(v24);
        }
    }
    updateFontScale() {
        let t24 = this.getUIContext();
        let u24 = t24.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(u24, this.maxAppFontScale);
    }
    getAccessibilityText(l24, m24, n24) {
        let o24 = '';
        try {
            let s24 = '';
            if (typeof l24 === 'string') {
                s24 = l24;
            }
            else {
                s24 = getContext().resourceManager.getStringSync(l24?.id);
            }
            switch (n24) {
                case FilterAccessibilityType.ACCESSIBILITY_TEXT:
                    o24 = m24 ? `${this.filterAccessibilityText.accessibilitySelectedText},${s24}` : s24;
                    break;
                case FilterAccessibilityType.ACCESSIBILITY_DESC:
                    o24 = m24 ? this.filterAccessibilityText.accessibilityUnselectedDesc :
                    this.filterAccessibilityText.accessibilitySelectedDesc;
                    break;
                case FilterAccessibilityType.SEND_ACCESSIBILITY:
                    o24 = m24 ? `${this.filterAccessibilityText.accessibilitySelectedText},${s24}` :
                        `${this.filterAccessibilityText.accessibilityUnselectedText},${s24}`;
                    break;
                default:
                    break;
            }
        }
        catch (p24) {
            let q24 = p24.code;
            let r24 = p24.message;
            hilog.error(0x3900, 'Ace', `Filter getAccessibilityText error, code: ${q24}, message: ${r24}`);
        }
        return o24;
    }
    sendAccessibility(i24, j24) {
        let k24 = ({
            type: 'announceForAccessibility',
            bundleName: this.bundleName,
            triggerAction: 'common',
            textAnnouncedForAccessibility: this.getAccessibilityText(i24, j24, FilterAccessibilityType.SEND_ACCESSIBILITY),
        });
        accessibility.sendAccessibilityEvent(k24).then(() => {
            hilog.info(0x3900, 'Ace', `ListFilter sendAccessibility send event, event info is ${JSON.stringify(k24)}`);
        });
    }
    filterItemClick(e24, f24) {
        let g24 = this.multiFilters[e24].options[f24];
        if (this.selectedFilters && f24 !== this.selectedFilters[e24].index) {
            if (this.colorArr) {
                this.colorArr[e24][f24] = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary_activated'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                this.colorArr[e24][this.selectedFilters[e24].index] = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
            }
            if (this.fontWeightArr) {
                this.fontWeightArr[e24][f24] = FontWeight.Medium;
                this.fontWeightArr[e24][this.selectedFilters[e24].index] = FontWeight.Regular;
            }
            if (this.isSelectedArr) {
                this.isSelectedArr[e24][f24] = true;
                this.isSelectedArr[e24][this.selectedFilters[e24].index] = false;
            }
            this.colorRefresh = !this.colorRefresh;
            this.selectedFilters[e24].value = g24;
            this.selectedFilters[e24].index = f24;
            let h24 = this.onFilterChanged;
            h24 && h24(this.selectedFilters);
        }
        this.refreshFloatFilterBarText();
    }
    refreshFloatFilterBarText() {
        this.floatFilterBarText = '';
        this.floatFilterBarAccessibilityText = '';
        if (this.selectedFilters) {
            const b24 = this.selectedFilters?.filter(d24 => d24?.value).map((c24) => {
                if (typeof c24.value !== 'string') {
                    return getContext()?.resourceManager?.getStringSync(c24.value?.id);
                }
                else {
                    return c24.value;
                }
            });
            this.floatFilterBarText = b24.join('/');
            this.floatFilterBarAccessibilityText = b24.join(' ');
        }
    }
    getFloatAccessibilityText(s23, t23) {
        let u23 = '';
        let v23 = this.filterAccessibilityText.accessibilityFilters;
        let w23 = this.filterAccessibilityText.accessibilityCollapsed;
        try {
            let a24 = '';
            if (typeof s23 === 'string') {
                a24 = s23;
            }
            else {
                a24 = getContext()?.resourceManager?.getStringSync(s23?.id);
            }
            switch (t23) {
                case FilterAccessibilityType.ACCESSIBILITY_TEXT:
                    u23 =
                        `${v23},${w23},${a24}`;
                    break;
                case FilterAccessibilityType.ACCESSIBILITY_DESC:
                    u23 = this.filterAccessibilityText.accessibilityExpandDesc;
                    break;
                case FilterAccessibilityType.SEND_ACCESSIBILITY:
                    u23 = this.filterAccessibilityText.accessibilityExpanded;
                    break;
                default:
                    break;
            }
        }
        catch (x23) {
            let y23 = x23.code;
            let z23 = x23.message;
            hilog.error(0x3900, 'Ace', `Filter getAccessibilityText error, code: ${y23}, message: ${z23}`);
        }
        return u23;
    }
    sendFloatAccessibility(n23) {
        let o23 = ({
            type: 'announceForAccessibility',
            bundleName: this.bundleName,
            triggerAction: 'common',
            textAnnouncedForAccessibility: this.getFloatAccessibilityText(n23, FilterAccessibilityType.SEND_ACCESSIBILITY),
        });
        accessibility.sendAccessibilityEvent(o23);
        if (this.multiFilters && this.multiFilters.length > 0) {
            if (this.filterType === FilterType.LIST_FILTER) {
                let r23 = ({
                    type: 'requestFocusForAccessibility',
                    bundleName: this.bundleName,
                    triggerAction: 'common',
                    customId: `filterListFilterRow_${this.filterId}_0`,
                });
                accessibility.sendAccessibilityEvent(r23);
            }
            else if (this.filterType === FilterType.MULTI_LINE_FILTER) {
                let q23 = ({
                    type: 'requestFocusForAccessibility',
                    bundleName: this.bundleName,
                    triggerAction: 'common',
                    customId: `filterMultiFilterRow_${this.filterId}_0`,
                });
                accessibility.sendAccessibilityEvent(q23);
            }
        }
        else if (this.additionFilters && this.additionFilters.name) {
            let p23 = ({
                type: 'requestFocusForAccessibility',
                bundleName: this.bundleName,
                triggerAction: 'common',
                customId: `filterAdditionFiltersName_${this.filterId}`,
            });
            accessibility.sendAccessibilityEvent(p23);
        }
    }
    initParams() {
        if (!this.selectedFilters) {
            this.selectedFilters = [];
            for (let l23 of this.multiFilters) {
                let m23 = { name: l23.name, index: -1, value: '' };
                if (l23.options.length > 0) {
                    m23.index = 0;
                    m23.value = l23.options[0];
                }
                this.selectedFilters.push(m23);
            }
            if (this.additionFilters && this.additionFilters.name) {
                let k23 = { name: this.additionFilters.name, index: -1, value: '' };
                this.selectedFilters.push(k23);
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
            this.floatArrowBgColor = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
            for (let d23 of this.multiFilters) {
                let e23 = new ResourceArray();
                let f23 = new FontWeightArray();
                let g23 = new ResourceArray();
                let h23 = new BooleanArray();
                let i23 = new BooleanArray();
                for (let j23 of d23.options.keys()) {
                    if (j23 === 0) {
                        e23.push({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary_activated'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        f23.push(FontWeight.Medium);
                        i23.push(true);
                    }
                    else {
                        e23.push({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        f23.push(FontWeight.Regular);
                        i23.push(false);
                    }
                    g23.push({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_hover'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                }
                this.colorArr.push(e23);
                this.fontWeightArr.push(f23);
                this.backgroundColorArr.push(g23);
                this.isBackgroundHover.push(h23);
                this.isArrowIconDownArr.push(new ObservedBoolean(true));
                this.isSelectedArr.push(i23);
            }
        }
        if (this.additionFilters && this.additionFilters.options) {
            this.additionColorArr = [];
            this.additionFontWeightArr = [];
            this.additionBackgroundColorArr = [];
            this.isAdditionBackgroundHover = [];
            for (let c23 = 0; c23 < this.additionFilters.options.length; c23++) {
                this.additionColorArr.push({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                this.additionFontWeightArr.push(FontWeight.Regular);
                this.additionBackgroundColorArr.push({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_hover'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                this.isAdditionBackgroundHover.push(false);
            }
        }
        if (!this.twoLineModeItemNum) {
            this.twoLineModeItemNum = [];
            this.twoLineModeItemNumRecord = [];
            this.downArrowShowState = [];
            for (let b23 = 0; b23 < this.multiFilters.length; b23++) {
                this.twoLineModeItemNum.push(new ObservedNumber(this.multiFilters[b23].options.length));
                this.twoLineModeItemNumRecord.push(new ObservedNumber(this.multiFilters[b23].options.length));
                this.downArrowShowState.push(new ObservedBoolean(false));
            }
        }
    }
    ListFilter(k22 = null) {
        this.observeComponentCreation2((x22, y22) => {
            Column.create();
            Column.width(PERCENT_100);
            Column.align(Alignment.Start);
            Column.onAreaChange((z22, a23) => {
                if (!this.isFloatShowAllFilterWithoutAnimation && !this.isFloatBarShowWithoutAnimation) {
                    if (this.additionFilters !== null) {
                        this.filterDynamicHeight = parseInt(a23.height.toString(), 0) + LIST_ROW_HEIGHT + FILTER_TOP_PADDING;
                    }
                    else {
                        this.filterDynamicHeight = parseInt(a23.height.toString(), 0) + FILTER_TOP_PADDING;
                    }
                    this.floatFilterPosition = -this.filterDynamicHeight;
                }
            });
        }, Column);
        this.observeComponentCreation2((l22, m22) => {
            ForEach.create();
            const n22 = (o22, p22) => {
                const q22 = o22;
                {
                    this.observeComponentCreation2((r22, s22) => {
                        if (s22) {
                            let t22 = new ListFilterRow(this, {
                                colorRow: this.colorArr ? this.colorArr[p22] : [],
                                fontWeightRow: this.fontWeightArr ? this.fontWeightArr[p22] : [],
                                backgroundColorRow: this.backgroundColorArr ? this.backgroundColorArr[p22] : [],
                                isBackgroundHoverRow: this.isBackgroundHover ? this.isBackgroundHover[p22] : [],
                                isSelectedRow: this.isSelectedArr ? this.isSelectedArr[p22] : [],
                                filterRow: q22,
                                onItemClick: (w22) => {
                                    this.filterItemClick(p22, w22);
                                },
                                rowIndex: p22,
                                filterAccessibilityText: this.filterAccessibilityText,
                            }, undefined, r22, () => { }, { page: 'library/src/main/ets/components/filter.ets', line: 1183, col: 9 });
                            ViewPU.create(t22);
                            let u22 = () => {
                                return {
                                    colorRow: this.colorArr ? this.colorArr[p22] : [],
                                    fontWeightRow: this.fontWeightArr ? this.fontWeightArr[p22] : [],
                                    backgroundColorRow: this.backgroundColorArr ? this.backgroundColorArr[p22] : [],
                                    isBackgroundHoverRow: this.isBackgroundHover ? this.isBackgroundHover[p22] : [],
                                    isSelectedRow: this.isSelectedArr ? this.isSelectedArr[p22] : [],
                                    filterRow: q22,
                                    onItemClick: (v22) => {
                                        this.filterItemClick(p22, v22);
                                    },
                                    rowIndex: p22,
                                    filterAccessibilityText: this.filterAccessibilityText
                                };
                            };
                            t22.paramsGenerator_ = u22;
                        }
                        else {
                            this.updateStateVarsOfChildByElmtId(r22, {
                                colorRow: this.colorArr ? this.colorArr[p22] : [],
                                fontWeightRow: this.fontWeightArr ? this.fontWeightArr[p22] : [],
                                backgroundColorRow: this.backgroundColorArr ? this.backgroundColorArr[p22] : [],
                                isBackgroundHoverRow: this.isBackgroundHover ? this.isBackgroundHover[p22] : [],
                                isSelectedRow: this.isSelectedArr ? this.isSelectedArr[p22] : [],
                                filterAccessibilityText: this.filterAccessibilityText
                            });
                        }
                    }, { name: 'ListFilterRow' });
                }
            };
            this.forEachUpdateFunction(l22, this.multiFilters, n22, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Column.pop();
    }
    MultiLineFilter(t21 = null) {
        this.observeComponentCreation2((g22, h22) => {
            Column.create();
            Column.width(PERCENT_100);
            Column.onAreaChange((i22, j22) => {
                if (this.additionFilters !== null) {
                    this.filterDynamicHeight = parseInt(j22.height.toString(), 0) + LIST_ROW_HEIGHT + FILTER_TOP_PADDING;
                }
                else {
                    this.filterDynamicHeight = parseInt(j22.height.toString(), 0) + FILTER_TOP_PADDING;
                }
                if (!this.isFloatBarShowWithoutAnimation && !this.isFloatShowAllFilterWithoutAnimation) {
                    this.floatFilterPosition = -this.filterDynamicHeight;
                }
            });
        }, Column);
        this.observeComponentCreation2((u21, v21) => {
            ForEach.create();
            const w21 = (x21, y21) => {
                const z21 = x21;
                {
                    this.observeComponentCreation2((a22, b22) => {
                        if (b22) {
                            let c22 = new MultiFilterRow(this, {
                                colorRow: this.colorArr ? this.colorArr[y21] : [],
                                fontWeightRow: this.fontWeightArr ? this.fontWeightArr[y21] : [],
                                backgroundColorRow: this.backgroundColorArr ? this.backgroundColorArr[y21] : [],
                                isBackgroundHoverRow: this.isBackgroundHover ? this.isBackgroundHover[y21] : [],
                                arrowShowStateRow: this.downArrowShowState ? this.downArrowShowState[y21] : new ObservedBoolean(false),
                                twoLineModeItemNumRow: this.twoLineModeItemNum ? this.twoLineModeItemNum[y21] : new ObservedNumber(0),
                                isSelectedRow: this.isSelectedArr ? this.isSelectedArr[y21] : [],
                                twoLineModeItemNumRecordRow: this.twoLineModeItemNumRecord ? this.twoLineModeItemNumRecord[y21] :
                                    new ObservedNumber(0),
                                isArrowIconDown: this.isArrowIconDownArr ? this.isArrowIconDownArr[y21] : new ObservedBoolean(false),
                                filterRow: z21,
                                onItemClick: (f22) => {
                                    this.filterItemClick(y21, f22);
                                },
                                rowIndex: y21,
                                fontSizeScale: this.fontSizeScale,
                                filterId: this.filterId,
                                filterAccessibilityText: this.filterAccessibilityText,
                            }, undefined, a22, () => { }, { page: 'library/src/main/ets/components/filter.ets', line: 1215, col: 9 });
                            ViewPU.create(c22);
                            let d22 = () => {
                                return {
                                    colorRow: this.colorArr ? this.colorArr[y21] : [],
                                    fontWeightRow: this.fontWeightArr ? this.fontWeightArr[y21] : [],
                                    backgroundColorRow: this.backgroundColorArr ? this.backgroundColorArr[y21] : [],
                                    isBackgroundHoverRow: this.isBackgroundHover ? this.isBackgroundHover[y21] : [],
                                    arrowShowStateRow: this.downArrowShowState ? this.downArrowShowState[y21] : new ObservedBoolean(false),
                                    twoLineModeItemNumRow: this.twoLineModeItemNum ? this.twoLineModeItemNum[y21] : new ObservedNumber(0),
                                    isSelectedRow: this.isSelectedArr ? this.isSelectedArr[y21] : [],
                                    twoLineModeItemNumRecordRow: this.twoLineModeItemNumRecord ? this.twoLineModeItemNumRecord[y21] :
                                        new ObservedNumber(0),
                                    isArrowIconDown: this.isArrowIconDownArr ? this.isArrowIconDownArr[y21] : new ObservedBoolean(false),
                                    filterRow: z21,
                                    onItemClick: (e22) => {
                                        this.filterItemClick(y21, e22);
                                    },
                                    rowIndex: y21,
                                    fontSizeScale: this.fontSizeScale,
                                    filterId: this.filterId,
                                    filterAccessibilityText: this.filterAccessibilityText
                                };
                            };
                            c22.paramsGenerator_ = d22;
                        }
                        else {
                            this.updateStateVarsOfChildByElmtId(a22, {
                                colorRow: this.colorArr ? this.colorArr[y21] : [],
                                fontWeightRow: this.fontWeightArr ? this.fontWeightArr[y21] : [],
                                backgroundColorRow: this.backgroundColorArr ? this.backgroundColorArr[y21] : [],
                                isBackgroundHoverRow: this.isBackgroundHover ? this.isBackgroundHover[y21] : [],
                                arrowShowStateRow: this.downArrowShowState ? this.downArrowShowState[y21] : new ObservedBoolean(false),
                                twoLineModeItemNumRow: this.twoLineModeItemNum ? this.twoLineModeItemNum[y21] : new ObservedNumber(0),
                                isSelectedRow: this.isSelectedArr ? this.isSelectedArr[y21] : [],
                                twoLineModeItemNumRecordRow: this.twoLineModeItemNumRecord ? this.twoLineModeItemNumRecord[y21] :
                                    new ObservedNumber(0),
                                isArrowIconDown: this.isArrowIconDownArr ? this.isArrowIconDownArr[y21] : new ObservedBoolean(false),
                                fontSizeScale: this.fontSizeScale,
                                filterAccessibilityText: this.filterAccessibilityText
                            });
                        }
                    }, { name: 'MultiFilterRow' });
                }
            };
            this.forEachUpdateFunction(u21, this.multiFilters, w21, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Column.pop();
    }
    additionItemClick(q21) {
        let r21 = this.multiFilters.length;
        if (this.selectedFilters && this.selectedFilters[r21].index !== q21) {
            if (this.selectedFilters[r21].index === -1) {
                this.additionColorArr && (this.additionColorArr[q21] = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary_activated'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                this.additionFontWeightArr && (this.additionFontWeightArr[q21] = FontWeight.Medium);
                this.selectedFilters[r21].value = this.additionFilters ? this.additionFilters.options[q21] : '';
                this.selectedFilters[r21].index = q21;
                this.additionFiltersSelectedIndex = q21;
            }
            else {
                let s21 = this.selectedFilters[r21].index;
                this.additionColorArr && (this.additionColorArr[s21] = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                this.additionColorArr && (this.additionColorArr[q21] = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary_activated'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                this.additionFontWeightArr && (this.additionFontWeightArr[s21] = FontWeight.Regular);
                this.additionFontWeightArr && (this.additionFontWeightArr[q21] = FontWeight.Medium);
                this.selectedFilters && (this.selectedFilters[r21].value = this.additionFilters ?
                this.additionFilters.options[q21] : '');
                this.selectedFilters && (this.selectedFilters[r21].index = q21);
                this.additionFiltersSelectedIndex = q21;
            }
        }
        else {
            this.additionColorArr && (this.additionColorArr[q21] = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            this.additionFontWeightArr && (this.additionFontWeightArr[q21] = FontWeight.Regular);
            this.selectedFilters && (this.selectedFilters[r21].value = '');
            this.selectedFilters && (this.selectedFilters[r21].index = -1);
            this.additionFiltersSelectedIndex = -1;
        }
        if (this.selectedFilters) {
            this.onFilterChanged && this.onFilterChanged(this.selectedFilters);
        }
        this.colorRefresh = !this.colorRefresh;
        this.refreshFloatFilterBarText();
    }
    getSelected(o21) {
        let p21 = this.multiFilters.length;
        if (this.selectedFilters && this.selectedFilters[p21].index !== o21) {
            return false;
        }
        else {
            return true;
        }
    }
    AdditionFilterList(p19 = null) {
        this.observeComponentCreation2((q19, r19) => {
            If.create();
            if (this.additionFilters && this.additionFilters.name && this.additionFilters.options &&
                this.additionFilters.options.length !== 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((m21, n21) => {
                        Stack.create({ alignContent: Alignment.End });
                        Stack.blendMode(BlendMode.SRC_OVER, BlendApplyType.OFFSCREEN);
                    }, Stack);
                    this.observeComponentCreation2((k21, l21) => {
                        Stack.create({ alignContent: Alignment.Start });
                    }, Stack);
                    this.observeComponentCreation2((i21, j21) => {
                        List.create();
                        List.listDirection(Axis.Horizontal);
                        List.scrollBar(BarState.Off);
                        List.width(PERCENT_100);
                        List.height(LIST_ROW_HEIGHT);
                    }, List);
                    {
                        const t20 = (g21, h21) => {
                            ViewStackProcessor.StartGetAccessRecordingFor(g21);
                            ListItem.create(v20, true);
                            if (!h21) {
                                ListItem.pop();
                            }
                            ViewStackProcessor.StopGetAccessRecording();
                        };
                        const u20 = (e21, f21) => {
                            ListItem.create(v20, true);
                            ListItem.height(PERCENT_100);
                            ListItem.margin({ start: LengthMetrics.vp(-TEXT_HOT_AREA_WIDTH) });
                        };
                        const v20 = (w20, x20) => {
                            t20(w20, x20);
                            this.observeComponentCreation2((c21, d21) => {
                                Row.create();
                            }, Row);
                            this.observeComponentCreation2((a21, b21) => {
                                Text.create(this.additionFilters.name);
                                Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body3'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                Text.minFontScale(1);
                                Text.maxFontScale(Math.min(this.updateFontScale(), MAX_FONT_SCALE));
                                Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                Text.margin({ start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH), end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH) });
                                Text.padding({ start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_max_padding_start'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }) });
                                Text.id(`filterAdditionFiltersName_${this.filterId}`);
                            }, Text);
                            Text.pop();
                            this.observeComponentCreation2((y20, z20) => {
                                Row.create();
                                Row.width(SEPARATOR_WIDTH);
                                Row.height(SEPARATOR_HEIGHT);
                                Row.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_list_separator'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                            }, Row);
                            Row.pop();
                            Row.pop();
                            ListItem.pop();
                        };
                        this.observeComponentCreation2(u20, ListItem);
                        ListItem.pop();
                    }
                    this.observeComponentCreation2((a20, b20) => {
                        ForEach.create();
                        const c20 = (d20, e20) => {
                            const f20 = d20;
                            {
                                const g20 = (r20, s20) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(r20);
                                    ListItem.create(i20, true);
                                    if (!s20) {
                                        ListItem.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                };
                                const h20 = (n20, o20) => {
                                    ListItem.create(i20, true);
                                    ListItem.accessibilityText(this.getAccessibilityText(f20, this.additionFiltersSelectedIndex === e20, FilterAccessibilityType.ACCESSIBILITY_TEXT));
                                    ListItem.accessibilityDescription(this.getAccessibilityText(f20, this.additionFiltersSelectedIndex === e20, FilterAccessibilityType.ACCESSIBILITY_DESC));
                                    ListItem.height(PERCENT_100);
                                    ListItem.backgroundColor(this.isAdditionBackgroundHover && this.isAdditionBackgroundHover[e20] ?
                                        this.additionBackgroundColorArr ? this.additionBackgroundColorArr[e20] : '' : TRANS_COLOR);
                                    ListItem.onHover((q20) => {
                                        Context.animateTo({
                                            curve: FRICTION_CUBIC_BEZIER,
                                            duration: ANIMATION_DURATION_250
                                        }, () => {
                                            if (q20) {
                                                this.additionBackgroundColorArr &&
                                                    (this.additionBackgroundColorArr[e20] = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_hover'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                                this.isAdditionBackgroundHover && (this.isAdditionBackgroundHover[e20] = true);
                                            }
                                            else {
                                                this.isAdditionBackgroundHover && (this.isAdditionBackgroundHover[e20] = false);
                                            }
                                        });
                                    });
                                    ListItem.onTouch((p20) => {
                                        if (p20.type === TouchType.Down) {
                                            Context.animateTo({
                                                curve: SHARP_CUBIC_BEZIER,
                                                duration: ANIMATION_DURATION_100
                                            }, () => {
                                                this.additionBackgroundColorArr &&
                                                    (this.additionBackgroundColorArr[e20] = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_click_effect'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                                this.isAdditionBackgroundHover && (this.isAdditionBackgroundHover[e20] = true);
                                            });
                                        }
                                        else if (p20.type === TouchType.Up || p20.type === TouchType.Cancel) {
                                            Context.animateTo({
                                                curve: SHARP_CUBIC_BEZIER,
                                                duration: ANIMATION_DURATION_100
                                            }, () => {
                                                this.isAdditionBackgroundHover && (this.isAdditionBackgroundHover[e20] = false);
                                            });
                                        }
                                    });
                                    ListItem.focusable(true);
                                    ViewStackProcessor.visualState('focused');
                                    ListItem.border({
                                        radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                        width: FOCUS_BORDER_WIDTH,
                                        color: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_focused_outline'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                        style: BorderStyle.Solid
                                    });
                                    ListItem.padding({
                                        start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH),
                                        end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH)
                                    });
                                    ViewStackProcessor.visualState('normal');
                                    ListItem.border({
                                        radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                        width: 0
                                    });
                                    ListItem.padding({ start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH), end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH) });
                                    ViewStackProcessor.visualState();
                                    ListItem.onClick(() => {
                                        this.additionItemClick(e20);
                                        this.sendAccessibility(f20, this.getSelected(e20));
                                    });
                                    ListItem.tabIndex(e20 === 0 ? 1 : -1);
                                };
                                const i20 = (j20, k20) => {
                                    g20(j20, k20);
                                    this.observeComponentCreation2((l20, m20) => {
                                        Text.create(f20);
                                        Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body3'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                        Text.minFontScale(1);
                                        Text.maxFontScale(Math.min(this.updateFontScale(), MAX_FONT_SCALE));
                                        Text.fontColor(this.additionColorArr ? this.additionColorArr[e20] : '');
                                        Text.fontWeight(this.additionFontWeightArr ? this.additionFontWeightArr[e20] : '');
                                        Text.focusable(true);
                                    }, Text);
                                    Text.pop();
                                    ListItem.pop();
                                };
                                this.observeComponentCreation2(h20, ListItem);
                                ListItem.pop();
                            }
                        };
                        this.forEachUpdateFunction(a20, this.additionFilters.options, c20, undefined, true, false);
                    }, ForEach);
                    ForEach.pop();
                    List.pop();
                    {
                        this.observeComponentCreation2((w19, x19) => {
                            if (x19) {
                                let y19 = new GradientMask(this, {
                                    x0: 0,
                                    y0: LIST_ROW_HEIGHT / 2,
                                    x1: GRADIENT_WIDTH,
                                    y1: LIST_ROW_HEIGHT / 2
                                }, undefined, w19, () => { }, { page: 'library/src/main/ets/components/filter.ets', line: 1400, col: 11 });
                                ViewPU.create(y19);
                                let z19 = () => {
                                    return {
                                        x0: 0,
                                        y0: LIST_ROW_HEIGHT / 2,
                                        x1: GRADIENT_WIDTH,
                                        y1: LIST_ROW_HEIGHT / 2
                                    };
                                };
                                y19.paramsGenerator_ = z19;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(w19, {});
                            }
                        }, { name: 'GradientMask' });
                    }
                    Stack.pop();
                    {
                        this.observeComponentCreation2((s19, t19) => {
                            if (t19) {
                                let u19 = new GradientMask(this, {
                                    x0: GRADIENT_WIDTH,
                                    y0: LIST_ROW_HEIGHT / 2,
                                    x1: 0,
                                    y1: LIST_ROW_HEIGHT / 2
                                }, undefined, s19, () => { }, { page: 'library/src/main/ets/components/filter.ets', line: 1408, col: 9 });
                                ViewPU.create(u19);
                                let v19 = () => {
                                    return {
                                        x0: GRADIENT_WIDTH,
                                        y0: LIST_ROW_HEIGHT / 2,
                                        x1: 0,
                                        y1: LIST_ROW_HEIGHT / 2
                                    };
                                };
                                u19.paramsGenerator_ = v19;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(s19, {});
                            }
                        }, { name: 'GradientMask' });
                    }
                    Stack.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }
    FilterHeader(i19 = null) {
        this.observeComponentCreation2((l19, m19) => {
            Column.create();
            Column.padding({ top: FILTER_TOP_PADDING });
            Column.onVisibleAreaChange([0.0, 1.0], (n19, o19) => {
                if (o19 > 0) {
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
        }, Column);
        this.observeComponentCreation2((j19, k19) => {
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
        }, If);
        If.pop();
        this.AdditionFilterList.bind(this)();
        Column.pop();
    }
    FloatFilterHeader(z18 = null) {
        this.observeComponentCreation2((g19, h19) => {
            Column.create();
            Column.padding({ top: FILTER_TOP_PADDING });
            Column.width(PERCENT_100);
            Column.constraintSize({ maxHeight: '80%' });
            Column.clip(true);
            Column.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Column.opacity(FLOAT_OPACITY);
            Column.backgroundBlurStyle(BlurStyle.Thin, undefined, { disableSystemAdaptation: true });
            Column.visibility(this.isFloatShowAllFilter ? Visibility.Visible : Visibility.Hidden);
            Column.position({ x: 0, y: this.floatFilterPosition });
            Column.zIndex(2);
        }, Column);
        this.observeComponentCreation2((e19, f19) => {
            Scroll.create();
        }, Scroll);
        this.observeComponentCreation2((c19, d19) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((a19, b19) => {
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
        }, If);
        If.pop();
        this.AdditionFilterList.bind(this)();
        Column.pop();
        Scroll.pop();
        Column.pop();
    }
    FloatFilterBar(k18 = null) {
        this.observeComponentCreation2((x18, y18) => {
            Row.create();
            Row.width(PERCENT_100);
            Row.height(this.floatFilterBarHeight);
            Row.padding({ start: LengthMetrics.vp(FOCUS_BORDER_WIDTH), end: LengthMetrics.vp(FOCUS_BORDER_WIDTH) });
            Row.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Row.opacity(FLOAT_OPACITY);
            Row.clip(true);
            Row.backgroundBlurStyle(BlurStyle.Thin, undefined, { disableSystemAdaptation: true });
            Row.visibility(this.isFloatBarShow ? Visibility.Visible : Visibility.Hidden);
            Row.alignItems(VerticalAlign.Bottom);
            Row.position({ x: 0, y: this.floatFilterBarPosition });
            Row.zIndex(1);
        }, Row);
        this.observeComponentCreation2((t18, u18) => {
            Column.create();
            Column.id(`FiliterFloatFilterBar_${this.getUniqueId()}`);
            Column.accessibilityText(this.getFloatAccessibilityText(this.floatFilterBarAccessibilityText, FilterAccessibilityType.ACCESSIBILITY_TEXT));
            Column.accessibilityDescription(this.getFloatAccessibilityText(this.floatFilterBarAccessibilityText, FilterAccessibilityType.ACCESSIBILITY_DESC));
            Column.backgroundColor(this.isFloatArrowBgHover ? this.floatArrowBgColor : TRANS_COLOR);
            ViewStackProcessor.visualState('focused');
            Column.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                width: FOCUS_BORDER_WIDTH,
                color: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_focused_outline'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                style: BorderStyle.Solid
            });
            ViewStackProcessor.visualState('normal');
            Column.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                width: 0
            });
            ViewStackProcessor.visualState();
            Column.alignItems(HorizontalAlign.Center);
            Column.width(PERCENT_100);
            Column.height(LIST_ROW_HEIGHT);
            Column.onTouch((w18) => {
                if (w18.type === TouchType.Down) {
                    Context.animateTo({
                        curve: SHARP_CUBIC_BEZIER,
                        duration: ANIMATION_DURATION_100
                    }, () => {
                        this.floatArrowBgColor = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_click_effect'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                        this.isFloatArrowBgHover = true;
                    });
                }
                else if (w18.type === TouchType.Up || w18.type === TouchType.Cancel) {
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
            Column.onHover((v18) => {
                if (v18) {
                    Context.animateTo({
                        curve: FRICTION_CUBIC_BEZIER,
                        duration: ANIMATION_DURATION_250
                    }, () => {
                        this.floatArrowBgColor = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_hover'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
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
        this.observeComponentCreation2((r18, s18) => {
            Row.create();
            Row.height(PERCENT_100);
            Row.alignItems(VerticalAlign.Center);
        }, Row);
        this.observeComponentCreation2((p18, q18) => {
            Row.create();
            Row.height(LIST_ROW_HEIGHT);
            Row.margin({ start: LengthMetrics.vp(FILTER_BAR_MARGIN) });
            Row.focusable(true);
        }, Row);
        this.observeComponentCreation2((n18, o18) => {
            Text.create(this.floatFilterBarText);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary_activated'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body3'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Text.minFontScale(1);
            Text.maxFontScale(Math.min(this.updateFontScale(), MAX_FONT_SCALE));
            Text.constraintSize({ maxWidth: '85%' });
            Text.maxLines(1);
        }, Text);
        Text.pop();
        this.observeComponentCreation2((l18, m18) => {
            SymbolGlyph.create({ 'id': -1, 'type': 40000, params: ['sys.symbol.chevron_down'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            SymbolGlyph.fontSize(`${(this.fontSizeScale ?? DEFAULT_SYMBOL_FONT_SCALE) * SYMBOL_SIZE}vp`);
            SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary_activated'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
            SymbolGlyph.focusable(true);
            SymbolGlyph.draggable(false);
        }, SymbolGlyph);
        Row.pop();
        Row.pop();
        Column.pop();
        Row.pop();
    }
    initialRender() {
        this.observeComponentCreation2((i18, j18) => {
            Stack.create({ alignContent: Alignment.Top });
            Stack.clip(true);
        }, Stack);
        this.FloatFilterBar.bind(this)();
        this.FloatFilterHeader.bind(this)();
        this.observeComponentCreation2((g18, h18) => {
            Column.create();
            Column.zIndex(0);
        }, Column);
        this.observeComponentCreation2((c18, d18) => {
            List.create({ initialIndex: 0 });
            List.listDirection(Axis.Vertical);
            List.width(PERCENT_100);
            List.height(PERCENT_100);
            List.edgeEffect(EdgeEffect.Spring);
            List.onScroll((e18, f18) => {
                if (this.isFloatShowAllFilterWithoutAnimation && f18 === ScrollState.Scroll) {
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
            const t17 = (a18, b18) => {
                ViewStackProcessor.StartGetAccessRecordingFor(a18);
                ListItem.create(v17, true);
                if (!b18) {
                    ListItem.pop();
                }
                ViewStackProcessor.StopGetAccessRecording();
            };
            const u17 = (y17, z17) => {
                ListItem.create(v17, true);
                ListItem.focusable(true);
            };
            const v17 = (w17, x17) => {
                t17(w17, x17);
                this.FilterHeader.bind(this)();
                ListItem.pop();
            };
            this.observeComponentCreation2(u17, ListItem);
            ListItem.pop();
        }
        {
            const k17 = (r17, s17) => {
                ViewStackProcessor.StartGetAccessRecordingFor(r17);
                ListItem.create(m17, true);
                if (!s17) {
                    ListItem.pop();
                }
                ViewStackProcessor.StopGetAccessRecording();
            };
            const l17 = (p17, q17) => {
                ListItem.create(m17, true);
                ListItem.focusable(true);
            };
            const m17 = (n17, o17) => {
                k17(n17, o17);
                this.container.bind(this)();
                ListItem.pop();
            };
            this.observeComponentCreation2(l17, ListItem);
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