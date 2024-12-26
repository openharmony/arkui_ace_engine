/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => { });
}
const vibrator = requireNativeModule('ohos.vibrator');
const curves = requireNativeModule('ohos.curves');
const composetitlebar = requireNapi('arkui.advanced.ComposeTitleBar');
const editabletitlebar = requireNapi('arkui.advanced.EditableTitleBar');
const subheader = requireNapi('arkui.advanced.SubHeader');
const hilog = requireNapi('hilog');
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const MeasureText = requireNapi('measure');
const SymbolGlyphModifier = requireNapi('arkui.modifier').SymbolGlyphModifier;
const ComposeTitleBar = composetitlebar.ComposeTitleBar;
const EditableTitleBar = editabletitlebar.EditableTitleBar;
const EditableLeftIconType = editabletitlebar.EditableLeftIconType;
const SubHeader = subheader.SubHeader;
const OperationType = subheader.OperationType;
const accessibility = requireNapi('accessibility');
const COL_IMAGE_TEXT = 3;
const COL_TEXT = 4;
const GRID_COL_3 = '1fr 1fr 1fr';
const GRID_COL_4 = '1fr 1fr 1fr 1fr';
const ICON_SIZE = 24;
const SYMBOL_SIZE_24VP = '24vp';
const SYMBOL_SIZE_12FP = 12;
const IMAGE_DEFAULT = 56;
const SYMBOL_DEFAULT = '56vp';
const SYMBOL_WEIGHT = 400;
const TEXT_PADDING_LEFT_RIGHT = 12;
const PADDING_EIGHT = 4;
const GRID_ITEM_HEIGHT_TEXT = 28;
const MARGIN_EIGHT = 8;
const ROW_GAP = 16;
const SUBTITLE_HEIGHT = 56;
const TEXT_MAX_LINES = 1;
const MIN_FONT_SCALE = 1;
const MAX_FONT_SCALE = 2;
const MIN_SYMBOL_FONT_SCALE = 1.15;
const DEFAULT_TEXT_SIZE = 12;
const DEFAULT_FONT_SIZE_SCALE = 1;
const DEFAULT_FONT_WEIGHT_SCALE = 1;
const DEFAULT_BLOCK_TEXT_ITEM_SAFE_MARGIN = 8;
const EDIT_BLOCK_TEXT_ITEM_SAFE_MARGIN = 16;
const ENTER_EXIT_ICON_DURATION = 200;
const COMMON_BEZIER = curves.cubicBezierCurve(0.33, 0, 0.67, 1);
const DRAG_SPRING = curves.interpolatingSpring(0, 1, 400, 38);
const REMOVE_ADD_SPRING = curves.interpolatingSpring(0, 1, 150, 24);
const LONG_TOUCH_SCALE = curves.cubicBezierCurve(0.2, 0, 0.2, 1);
const ACCESSIBILITY_ITEM_LONG_PRESS_GESTURE = 'gridobjectsortcomponent_accessibility_item_long_press_gesture';
const ACCESSIBILITY_ILLEGAL_AREA = 'gridobjectsortcomponent_accessibility_illegal_area';
const ACCESSIBILITY_SELECTED_ITEM_DRAG_START = 'gridobjectsortcomponent_accessibility_selected_item_drag_start';
const ACCESSIBILITY_SELECTED_ITEM_DESC = 'gridobjectsortcomponent_accessibility_selected_item_desc';
const ACCESSIBILITY_SELECTED_ITEM = 'gridobjectsortcomponent_accessibility_selected_item';
const ACCESSIBILITY_SELECTED_ITEM_DRAG_STOP = 'gridobjectsortcomponent_accessibility_selected_item_drag_stop';
const ACCESSIBILITY_UNSELECTED_ITEM_ADD = 'gridobjectsortcomponent_accessibility_unselected_item_add';
const ACCESSIBILITY_UNSELECTED_IMAGE_ITEM_DESC = 'gridobjectsortcomponent_accessibility_unselected_image_item_desc';
const ACCESSIBILITY_UNSELECTED_TEXT_ITEM_DESC = 'gridobjectsortcomponent_accessibility_unselected_text_item_desc';
const ACCESSIBILITY_UNSELECTED_ITEM = 'gridobjectsortcomponent_accessibility_unselected_item';
const ACCESSIBILITY_SELECTED_ITEM_DELETE = 'gridobjectsortcomponent_accessibility_selected_item_delete';
const ACCESSIBILITY_HEADER_EDIT_BUTTON = 'gridobjectsortcomponent_accessibility_header_edit_button';
const ACCESSIBILITY_SELECTED_ITEM_DRAG_MOVING = 'gridobjectsortcomponent_accessibility_selected_item_drag_moving';
const ACCESSIBILITY_DELETED = 'gridobjectsortcomponent_accessibility_deleted';
const ACCESSIBILITY_UNSELECTED_BUTTON = 'gridobjectsortcomponent_accessibility_unselected_button';
const EDIT_TITLE_BAR_ID = 'EditTitleBar';
const ADD_TITLE_BAR_ID = 'AddTitleBar';
const ADD_GRID_FIRST_ITEM_ID = 'add_grid_item_0';
const YES = 'yes';
const NO = 'no';
const ADD = 'add';
const EDIT = 'edit';
const DELETE = 'delete';
export var GridObjectSortComponentType;
(function (w31) {
    w31['IMAGE_TEXT'] = 'image_text';
    w31['TEXT'] = 'text';
})(GridObjectSortComponentType || (GridObjectSortComponentType = {}));
class MenuItem {
    constructor(r31, s31, t31, u31, v31) {
        this.value = r31;
        this.symbolStyle = s31;
        this.isEnabled = t31;
        this.action = v31;
        this.accessibilityText = u31;
    }
}
export class GridObjectSortComponent extends ViewPU {
    constructor(i31, j31, k31, l31 = -1, m31 = undefined, n31) {
        super(i31, k31, l31, n31);
        if (typeof m31 === 'function') {
            this.paramsGenerator_ = m31;
        }
        this.__options = new SynchedPropertyObjectOneWayPU(j31.options, this, 'options');
        this.dataList = [];
        this.__selected = new ObservedPropertyObjectPU([], this, 'selected');
        this.__unSelected = new ObservedPropertyObjectPU([], this, 'unSelected');
        this.__copySelected = new ObservedPropertyObjectPU([], this, 'copySelected');
        this.__copyUnSelected = new ObservedPropertyObjectPU([], this, 'copyUnSelected');
        this.__content = new ObservedPropertyObjectPU({
            id: '',
            text: '',
            selected: false,
            order: 0
        }, this, 'content');
        this.__dragContent = new ObservedPropertyObjectPU({
            id: '',
            text: '',
            selected: false,
            order: 0
        }, this, 'dragContent');
        this.__dragContentIndex = new ObservedPropertySimplePU(-1, this, 'dragContentIndex');
        this.__hoverId = new ObservedPropertySimplePU('', this, 'hoverId');
        this.__gridComState = new ObservedPropertySimplePU(false, this, 'gridComState');
        this.__menuSwitch = new ObservedPropertySimplePU(false, this, 'menuSwitch');
        this.__areaWidth = new ObservedPropertySimplePU(0, this, 'areaWidth');
        this.__blockWidth = new ObservedPropertySimplePU(0, this, 'blockWidth');
        this.__blockHeight = new ObservedPropertySimplePU(0, this, 'blockHeight');
        this.__longScaleOnePointTwo = new ObservedPropertySimplePU(1, this, 'longScaleOnePointTwo');
        this.__scaleGridItemNinetyPercent = new ObservedPropertySimplePU(1, this, 'scaleGridItemNinetyPercent');
        this.__reboundSize = new ObservedPropertySimplePU(1, this, 'reboundSize');
        this.__scaleIcon = new ObservedPropertySimplePU(1, this, 'scaleIcon');
        this.__addIconShow = new ObservedPropertySimplePU(false, this, 'addIconShow');
        this.__scaleAddIcon = new ObservedPropertySimplePU(0, this, 'scaleAddIcon');
        this.__isStartDrag = new ObservedPropertySimplePU(false, this, 'isStartDrag');
        this.__insertIndex = new ObservedPropertySimplePU(-1, this, 'insertIndex');
        this.__itemIndex = new ObservedPropertySimplePU(0, this, 'itemIndex');
        this.__editGridDataLength = new ObservedPropertySimplePU(-1, this, 'editGridDataLength');
        this.__isTouchDown = new ObservedPropertySimplePU(false, this, 'isTouchDown');
        this.__addItemMoveX = new ObservedPropertySimplePU(0, this, 'addItemMoveX');
        this.__addItemMoveY = new ObservedPropertySimplePU(0, this, 'addItemMoveY');
        this.__editItemMoveX = new ObservedPropertySimplePU(0, this, 'editItemMoveX');
        this.__editItemMoveY = new ObservedPropertySimplePU(0, this, 'editItemMoveY');
        this.__unSelectedIndex = new ObservedPropertySimplePU(0, this, 'unSelectedIndex');
        this.__clickAddBtn = new ObservedPropertySimplePU(false, this, 'clickAddBtn');
        this.__selectedIndex = new ObservedPropertySimplePU(-1, this, 'selectedIndex');
        this.__clickRemoveBtn = new ObservedPropertySimplePU(false, this, 'clickRemoveBtn');
        this.__addAreaLongPressGesture = new ObservedPropertySimplePU(false, this, 'addAreaLongPressGesture');
        this.__arraySelectIsChange = new ObservedPropertySimplePU(0, this, 'arraySelectIsChange');
        this.__arrayUnSelectIsChange = new ObservedPropertySimplePU(0, this, 'arrayUnSelectIsChange');
        this.__textItemEditWidth = new ObservedPropertySimplePU(0, this, 'textItemEditWidth');
        this.__textItemEditHeight = new ObservedPropertySimplePU(0, this, 'textItemEditHeight');
        this.__imageItemWidth = new ObservedPropertySimplePU(0, this, 'imageItemWidth');
        this.__saveClick = new ObservedPropertySimplePU(false, this, 'saveClick');
        this.__imageTextAddIconShow = new ObservedPropertySimplePU(false, this, 'imageTextAddIconShow');
        this.__imageTextRemoveIconShow = new ObservedPropertySimplePU(false, this, 'imageTextRemoveIconShow');
        this.__firstIn = new ObservedPropertySimplePU(true, this, 'firstIn');
        this.__fontSizeScale = new ObservedPropertyObjectPU(1, this, 'fontSizeScale');
        this.__fontWeightScale = new ObservedPropertyObjectPU(1, this, 'fontWeightScale');
        this.__customColumns = new ObservedPropertySimplePU('1fr 1fr 1fr 1fr', this, 'customColumns');
        this.__editGridHeight = new ObservedPropertySimplePU(0, this, 'editGridHeight');
        this.__addGridHeight = new ObservedPropertySimplePU(0, this, 'addGridHeight');
        this.__subTitleHeight = new ObservedPropertySimplePU(0, this, 'subTitleHeight');
        this.callbackId = undefined;
        this.colNum = COL_IMAGE_TEXT;
        this.vibrationDone = false;
        this.touchDown = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_click_effect'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.touchBorderRadius = { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.hoverBackgroundColor = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_hover'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.focusBorder = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_focused_outline'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.imageText = false;
        this.menuItems = [
            new MenuItem({ 'id': -1, 'type': 20000, params: ['sys.media.ohos_ic_public_edit'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, (new SymbolGlyphModifier({ 'id': -1, 'type': 40000, params: ['sys.symbol.square_and_pencil'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' })), true, this.getStringByResource(ACCESSIBILITY_HEADER_EDIT_BUTTON), () => {
                this.goEdit();
            })
        ];
        this.onSave = undefined;
        this.onCancel = undefined;
        this.isFollowingSystemFontScale = false;
        this.maxAppFontScale = 1;
        this.bundleName = '';
        this.__readFlag = new ObservedPropertySimplePU(true, this, 'readFlag');
        this.__readIndex4AddArea = new ObservedPropertySimplePU(-1, this, 'readIndex4AddArea');
        this.__readIndex4EditArea = new ObservedPropertySimplePU(-1, this, 'readIndex4EditArea');
        this.__isPointToAddTitleBarEditButton = new ObservedPropertySimplePU(false, this, 'isPointToAddTitleBarEditButton');
        this.__isPointToEditTitleBarSaveButton = new ObservedPropertySimplePU(false, this, 'isPointToEditTitleBarSaveButton');
        this.preTextAnnouncedForAccessibility = '';
        this.textAnnouncedForAccessibility = '';
        this.envCallback = {
            onConfigurationUpdated: (p31) => {
                let q31 = this.getUIContext();
                this.fontSizeScale = this.decideFontScale(q31);
                this.fontWeightScale = p31.fontWeightScale;
            },
            onMemoryLevel: (o31) => { }
        };
        this.setInitiallyProvidedValue(j31);
        this.declareWatch('gridComState', this.onGridComStateChange);
        this.declareWatch('fontSizeScale', this.calcAreaInfo);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(h31) {
        if (h31.options === undefined) {
            this.__options.set({});
        }
        if (h31.dataList !== undefined) {
            this.dataList = h31.dataList;
        }
        if (h31.selected !== undefined) {
            this.selected = h31.selected;
        }
        if (h31.unSelected !== undefined) {
            this.unSelected = h31.unSelected;
        }
        if (h31.copySelected !== undefined) {
            this.copySelected = h31.copySelected;
        }
        if (h31.copyUnSelected !== undefined) {
            this.copyUnSelected = h31.copyUnSelected;
        }
        if (h31.content !== undefined) {
            this.content = h31.content;
        }
        if (h31.dragContent !== undefined) {
            this.dragContent = h31.dragContent;
        }
        if (h31.dragContentIndex !== undefined) {
            this.dragContentIndex = h31.dragContentIndex;
        }
        if (h31.hoverId !== undefined) {
            this.hoverId = h31.hoverId;
        }
        if (h31.gridComState !== undefined) {
            this.gridComState = h31.gridComState;
        }
        if (h31.menuSwitch !== undefined) {
            this.menuSwitch = h31.menuSwitch;
        }
        if (h31.areaWidth !== undefined) {
            this.areaWidth = h31.areaWidth;
        }
        if (h31.blockWidth !== undefined) {
            this.blockWidth = h31.blockWidth;
        }
        if (h31.blockHeight !== undefined) {
            this.blockHeight = h31.blockHeight;
        }
        if (h31.longScaleOnePointTwo !== undefined) {
            this.longScaleOnePointTwo = h31.longScaleOnePointTwo;
        }
        if (h31.scaleGridItemNinetyPercent !== undefined) {
            this.scaleGridItemNinetyPercent = h31.scaleGridItemNinetyPercent;
        }
        if (h31.reboundSize !== undefined) {
            this.reboundSize = h31.reboundSize;
        }
        if (h31.scaleIcon !== undefined) {
            this.scaleIcon = h31.scaleIcon;
        }
        if (h31.addIconShow !== undefined) {
            this.addIconShow = h31.addIconShow;
        }
        if (h31.scaleAddIcon !== undefined) {
            this.scaleAddIcon = h31.scaleAddIcon;
        }
        if (h31.isStartDrag !== undefined) {
            this.isStartDrag = h31.isStartDrag;
        }
        if (h31.insertIndex !== undefined) {
            this.insertIndex = h31.insertIndex;
        }
        if (h31.itemIndex !== undefined) {
            this.itemIndex = h31.itemIndex;
        }
        if (h31.editGridDataLength !== undefined) {
            this.editGridDataLength = h31.editGridDataLength;
        }
        if (h31.isTouchDown !== undefined) {
            this.isTouchDown = h31.isTouchDown;
        }
        if (h31.addItemMoveX !== undefined) {
            this.addItemMoveX = h31.addItemMoveX;
        }
        if (h31.addItemMoveY !== undefined) {
            this.addItemMoveY = h31.addItemMoveY;
        }
        if (h31.editItemMoveX !== undefined) {
            this.editItemMoveX = h31.editItemMoveX;
        }
        if (h31.editItemMoveY !== undefined) {
            this.editItemMoveY = h31.editItemMoveY;
        }
        if (h31.unSelectedIndex !== undefined) {
            this.unSelectedIndex = h31.unSelectedIndex;
        }
        if (h31.clickAddBtn !== undefined) {
            this.clickAddBtn = h31.clickAddBtn;
        }
        if (h31.selectedIndex !== undefined) {
            this.selectedIndex = h31.selectedIndex;
        }
        if (h31.clickRemoveBtn !== undefined) {
            this.clickRemoveBtn = h31.clickRemoveBtn;
        }
        if (h31.addAreaLongPressGesture !== undefined) {
            this.addAreaLongPressGesture = h31.addAreaLongPressGesture;
        }
        if (h31.arraySelectIsChange !== undefined) {
            this.arraySelectIsChange = h31.arraySelectIsChange;
        }
        if (h31.arrayUnSelectIsChange !== undefined) {
            this.arrayUnSelectIsChange = h31.arrayUnSelectIsChange;
        }
        if (h31.textItemEditWidth !== undefined) {
            this.textItemEditWidth = h31.textItemEditWidth;
        }
        if (h31.textItemEditHeight !== undefined) {
            this.textItemEditHeight = h31.textItemEditHeight;
        }
        if (h31.imageItemWidth !== undefined) {
            this.imageItemWidth = h31.imageItemWidth;
        }
        if (h31.saveClick !== undefined) {
            this.saveClick = h31.saveClick;
        }
        if (h31.imageTextAddIconShow !== undefined) {
            this.imageTextAddIconShow = h31.imageTextAddIconShow;
        }
        if (h31.imageTextRemoveIconShow !== undefined) {
            this.imageTextRemoveIconShow = h31.imageTextRemoveIconShow;
        }
        if (h31.firstIn !== undefined) {
            this.firstIn = h31.firstIn;
        }
        if (h31.fontSizeScale !== undefined) {
            this.fontSizeScale = h31.fontSizeScale;
        }
        if (h31.fontWeightScale !== undefined) {
            this.fontWeightScale = h31.fontWeightScale;
        }
        if (h31.customColumns !== undefined) {
            this.customColumns = h31.customColumns;
        }
        if (h31.editGridHeight !== undefined) {
            this.editGridHeight = h31.editGridHeight;
        }
        if (h31.addGridHeight !== undefined) {
            this.addGridHeight = h31.addGridHeight;
        }
        if (h31.subTitleHeight !== undefined) {
            this.subTitleHeight = h31.subTitleHeight;
        }
        if (h31.callbackId !== undefined) {
            this.callbackId = h31.callbackId;
        }
        if (h31.colNum !== undefined) {
            this.colNum = h31.colNum;
        }
        if (h31.vibrationDone !== undefined) {
            this.vibrationDone = h31.vibrationDone;
        }
        if (h31.touchDown !== undefined) {
            this.touchDown = h31.touchDown;
        }
        if (h31.touchBorderRadius !== undefined) {
            this.touchBorderRadius = h31.touchBorderRadius;
        }
        if (h31.hoverBackgroundColor !== undefined) {
            this.hoverBackgroundColor = h31.hoverBackgroundColor;
        }
        if (h31.focusBorder !== undefined) {
            this.focusBorder = h31.focusBorder;
        }
        if (h31.imageText !== undefined) {
            this.imageText = h31.imageText;
        }
        if (h31.menuItems !== undefined) {
            this.menuItems = h31.menuItems;
        }
        if (h31.onSave !== undefined) {
            this.onSave = h31.onSave;
        }
        if (h31.onCancel !== undefined) {
            this.onCancel = h31.onCancel;
        }
        if (h31.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = h31.isFollowingSystemFontScale;
        }
        if (h31.maxAppFontScale !== undefined) {
            this.maxAppFontScale = h31.maxAppFontScale;
        }
        if (h31.bundleName !== undefined) {
            this.bundleName = h31.bundleName;
        }
        if (h31.readFlag !== undefined) {
            this.readFlag = h31.readFlag;
        }
        if (h31.readIndex4AddArea !== undefined) {
            this.readIndex4AddArea = h31.readIndex4AddArea;
        }
        if (h31.readIndex4EditArea !== undefined) {
            this.readIndex4EditArea = h31.readIndex4EditArea;
        }
        if (h31.isPointToAddTitleBarEditButton !== undefined) {
            this.isPointToAddTitleBarEditButton = h31.isPointToAddTitleBarEditButton;
        }
        if (h31.isPointToEditTitleBarSaveButton !== undefined) {
            this.isPointToEditTitleBarSaveButton = h31.isPointToEditTitleBarSaveButton;
        }
        if (h31.preTextAnnouncedForAccessibility !== undefined) {
            this.preTextAnnouncedForAccessibility = h31.preTextAnnouncedForAccessibility;
        }
        if (h31.textAnnouncedForAccessibility !== undefined) {
            this.textAnnouncedForAccessibility = h31.textAnnouncedForAccessibility;
        }
        if (h31.envCallback !== undefined) {
            this.envCallback = h31.envCallback;
        }
    }
    updateStateVars(g31) {
        this.__options.reset(g31.options);
    }
    purgeVariableDependenciesOnElmtId(f31) {
        this.__options.purgeDependencyOnElmtId(f31);
        this.__selected.purgeDependencyOnElmtId(f31);
        this.__unSelected.purgeDependencyOnElmtId(f31);
        this.__copySelected.purgeDependencyOnElmtId(f31);
        this.__copyUnSelected.purgeDependencyOnElmtId(f31);
        this.__content.purgeDependencyOnElmtId(f31);
        this.__dragContent.purgeDependencyOnElmtId(f31);
        this.__dragContentIndex.purgeDependencyOnElmtId(f31);
        this.__hoverId.purgeDependencyOnElmtId(f31);
        this.__gridComState.purgeDependencyOnElmtId(f31);
        this.__menuSwitch.purgeDependencyOnElmtId(f31);
        this.__areaWidth.purgeDependencyOnElmtId(f31);
        this.__blockWidth.purgeDependencyOnElmtId(f31);
        this.__blockHeight.purgeDependencyOnElmtId(f31);
        this.__longScaleOnePointTwo.purgeDependencyOnElmtId(f31);
        this.__scaleGridItemNinetyPercent.purgeDependencyOnElmtId(f31);
        this.__reboundSize.purgeDependencyOnElmtId(f31);
        this.__scaleIcon.purgeDependencyOnElmtId(f31);
        this.__addIconShow.purgeDependencyOnElmtId(f31);
        this.__scaleAddIcon.purgeDependencyOnElmtId(f31);
        this.__isStartDrag.purgeDependencyOnElmtId(f31);
        this.__insertIndex.purgeDependencyOnElmtId(f31);
        this.__itemIndex.purgeDependencyOnElmtId(f31);
        this.__editGridDataLength.purgeDependencyOnElmtId(f31);
        this.__isTouchDown.purgeDependencyOnElmtId(f31);
        this.__addItemMoveX.purgeDependencyOnElmtId(f31);
        this.__addItemMoveY.purgeDependencyOnElmtId(f31);
        this.__editItemMoveX.purgeDependencyOnElmtId(f31);
        this.__editItemMoveY.purgeDependencyOnElmtId(f31);
        this.__unSelectedIndex.purgeDependencyOnElmtId(f31);
        this.__clickAddBtn.purgeDependencyOnElmtId(f31);
        this.__selectedIndex.purgeDependencyOnElmtId(f31);
        this.__clickRemoveBtn.purgeDependencyOnElmtId(f31);
        this.__addAreaLongPressGesture.purgeDependencyOnElmtId(f31);
        this.__arraySelectIsChange.purgeDependencyOnElmtId(f31);
        this.__arrayUnSelectIsChange.purgeDependencyOnElmtId(f31);
        this.__textItemEditWidth.purgeDependencyOnElmtId(f31);
        this.__textItemEditHeight.purgeDependencyOnElmtId(f31);
        this.__imageItemWidth.purgeDependencyOnElmtId(f31);
        this.__saveClick.purgeDependencyOnElmtId(f31);
        this.__imageTextAddIconShow.purgeDependencyOnElmtId(f31);
        this.__imageTextRemoveIconShow.purgeDependencyOnElmtId(f31);
        this.__firstIn.purgeDependencyOnElmtId(f31);
        this.__fontSizeScale.purgeDependencyOnElmtId(f31);
        this.__fontWeightScale.purgeDependencyOnElmtId(f31);
        this.__customColumns.purgeDependencyOnElmtId(f31);
        this.__editGridHeight.purgeDependencyOnElmtId(f31);
        this.__addGridHeight.purgeDependencyOnElmtId(f31);
        this.__subTitleHeight.purgeDependencyOnElmtId(f31);
        this.__readFlag.purgeDependencyOnElmtId(f31);
        this.__readIndex4AddArea.purgeDependencyOnElmtId(f31);
        this.__readIndex4EditArea.purgeDependencyOnElmtId(f31);
        this.__isPointToAddTitleBarEditButton.purgeDependencyOnElmtId(f31);
        this.__isPointToEditTitleBarSaveButton.purgeDependencyOnElmtId(f31);
    }
    aboutToBeDeleted() {
        this.__options.aboutToBeDeleted();
        this.__selected.aboutToBeDeleted();
        this.__unSelected.aboutToBeDeleted();
        this.__copySelected.aboutToBeDeleted();
        this.__copyUnSelected.aboutToBeDeleted();
        this.__content.aboutToBeDeleted();
        this.__dragContent.aboutToBeDeleted();
        this.__dragContentIndex.aboutToBeDeleted();
        this.__hoverId.aboutToBeDeleted();
        this.__gridComState.aboutToBeDeleted();
        this.__menuSwitch.aboutToBeDeleted();
        this.__areaWidth.aboutToBeDeleted();
        this.__blockWidth.aboutToBeDeleted();
        this.__blockHeight.aboutToBeDeleted();
        this.__longScaleOnePointTwo.aboutToBeDeleted();
        this.__scaleGridItemNinetyPercent.aboutToBeDeleted();
        this.__reboundSize.aboutToBeDeleted();
        this.__scaleIcon.aboutToBeDeleted();
        this.__addIconShow.aboutToBeDeleted();
        this.__scaleAddIcon.aboutToBeDeleted();
        this.__isStartDrag.aboutToBeDeleted();
        this.__insertIndex.aboutToBeDeleted();
        this.__itemIndex.aboutToBeDeleted();
        this.__editGridDataLength.aboutToBeDeleted();
        this.__isTouchDown.aboutToBeDeleted();
        this.__addItemMoveX.aboutToBeDeleted();
        this.__addItemMoveY.aboutToBeDeleted();
        this.__editItemMoveX.aboutToBeDeleted();
        this.__editItemMoveY.aboutToBeDeleted();
        this.__unSelectedIndex.aboutToBeDeleted();
        this.__clickAddBtn.aboutToBeDeleted();
        this.__selectedIndex.aboutToBeDeleted();
        this.__clickRemoveBtn.aboutToBeDeleted();
        this.__addAreaLongPressGesture.aboutToBeDeleted();
        this.__arraySelectIsChange.aboutToBeDeleted();
        this.__arrayUnSelectIsChange.aboutToBeDeleted();
        this.__textItemEditWidth.aboutToBeDeleted();
        this.__textItemEditHeight.aboutToBeDeleted();
        this.__imageItemWidth.aboutToBeDeleted();
        this.__saveClick.aboutToBeDeleted();
        this.__imageTextAddIconShow.aboutToBeDeleted();
        this.__imageTextRemoveIconShow.aboutToBeDeleted();
        this.__firstIn.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__fontWeightScale.aboutToBeDeleted();
        this.__customColumns.aboutToBeDeleted();
        this.__editGridHeight.aboutToBeDeleted();
        this.__addGridHeight.aboutToBeDeleted();
        this.__subTitleHeight.aboutToBeDeleted();
        this.__readFlag.aboutToBeDeleted();
        this.__readIndex4AddArea.aboutToBeDeleted();
        this.__readIndex4EditArea.aboutToBeDeleted();
        this.__isPointToAddTitleBarEditButton.aboutToBeDeleted();
        this.__isPointToEditTitleBarSaveButton.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get options() {
        return this.__options.get();
    }
    set options(e31) {
        this.__options.set(e31);
    }
    get selected() {
        return this.__selected.get();
    }
    set selected(d31) {
        this.__selected.set(d31);
    }
    get unSelected() {
        return this.__unSelected.get();
    }
    set unSelected(c31) {
        this.__unSelected.set(c31);
    }
    get copySelected() {
        return this.__copySelected.get();
    }
    set copySelected(b31) {
        this.__copySelected.set(b31);
    }
    get copyUnSelected() {
        return this.__copyUnSelected.get();
    }
    set copyUnSelected(a31) {
        this.__copyUnSelected.set(a31);
    }
    get content() {
        return this.__content.get();
    }
    set content(z30) {
        this.__content.set(z30);
    }
    get dragContent() {
        return this.__dragContent.get();
    }
    set dragContent(y30) {
        this.__dragContent.set(y30);
    }
    get dragContentIndex() {
        return this.__dragContentIndex.get();
    }
    set dragContentIndex(x30) {
        this.__dragContentIndex.set(x30);
    }
    get hoverId() {
        return this.__hoverId.get();
    }
    set hoverId(w30) {
        this.__hoverId.set(w30);
    }
    get gridComState() {
        return this.__gridComState.get();
    }
    set gridComState(v30) {
        this.__gridComState.set(v30);
    }
    get menuSwitch() {
        return this.__menuSwitch.get();
    }
    set menuSwitch(u30) {
        this.__menuSwitch.set(u30);
    }
    get areaWidth() {
        return this.__areaWidth.get();
    }
    set areaWidth(t30) {
        this.__areaWidth.set(t30);
    }
    get blockWidth() {
        return this.__blockWidth.get();
    }
    set blockWidth(s30) {
        this.__blockWidth.set(s30);
    }
    get blockHeight() {
        return this.__blockHeight.get();
    }
    set blockHeight(r30) {
        this.__blockHeight.set(r30);
    }
    get longScaleOnePointTwo() {
        return this.__longScaleOnePointTwo.get();
    }
    set longScaleOnePointTwo(q30) {
        this.__longScaleOnePointTwo.set(q30);
    }
    get scaleGridItemNinetyPercent() {
        return this.__scaleGridItemNinetyPercent.get();
    }
    set scaleGridItemNinetyPercent(p30) {
        this.__scaleGridItemNinetyPercent.set(p30);
    }
    get reboundSize() {
        return this.__reboundSize.get();
    }
    set reboundSize(o30) {
        this.__reboundSize.set(o30);
    }
    get scaleIcon() {
        return this.__scaleIcon.get();
    }
    set scaleIcon(n30) {
        this.__scaleIcon.set(n30);
    }
    get addIconShow() {
        return this.__addIconShow.get();
    }
    set addIconShow(m30) {
        this.__addIconShow.set(m30);
    }
    get scaleAddIcon() {
        return this.__scaleAddIcon.get();
    }
    set scaleAddIcon(l30) {
        this.__scaleAddIcon.set(l30);
    }
    get isStartDrag() {
        return this.__isStartDrag.get();
    }
    set isStartDrag(k30) {
        this.__isStartDrag.set(k30);
    }
    get insertIndex() {
        return this.__insertIndex.get();
    }
    set insertIndex(j30) {
        this.__insertIndex.set(j30);
    }
    get itemIndex() {
        return this.__itemIndex.get();
    }
    set itemIndex(i30) {
        this.__itemIndex.set(i30);
    }
    get editGridDataLength() {
        return this.__editGridDataLength.get();
    }
    set editGridDataLength(h30) {
        this.__editGridDataLength.set(h30);
    }
    get isTouchDown() {
        return this.__isTouchDown.get();
    }
    set isTouchDown(g30) {
        this.__isTouchDown.set(g30);
    }
    get addItemMoveX() {
        return this.__addItemMoveX.get();
    }
    set addItemMoveX(f30) {
        this.__addItemMoveX.set(f30);
    }
    get addItemMoveY() {
        return this.__addItemMoveY.get();
    }
    set addItemMoveY(e30) {
        this.__addItemMoveY.set(e30);
    }
    get editItemMoveX() {
        return this.__editItemMoveX.get();
    }
    set editItemMoveX(d30) {
        this.__editItemMoveX.set(d30);
    }
    get editItemMoveY() {
        return this.__editItemMoveY.get();
    }
    set editItemMoveY(c30) {
        this.__editItemMoveY.set(c30);
    }
    get unSelectedIndex() {
        return this.__unSelectedIndex.get();
    }
    set unSelectedIndex(b30) {
        this.__unSelectedIndex.set(b30);
    }
    get clickAddBtn() {
        return this.__clickAddBtn.get();
    }
    set clickAddBtn(a30) {
        this.__clickAddBtn.set(a30);
    }
    get selectedIndex() {
        return this.__selectedIndex.get();
    }
    set selectedIndex(z29) {
        this.__selectedIndex.set(z29);
    }
    get clickRemoveBtn() {
        return this.__clickRemoveBtn.get();
    }
    set clickRemoveBtn(y29) {
        this.__clickRemoveBtn.set(y29);
    }
    get addAreaLongPressGesture() {
        return this.__addAreaLongPressGesture.get();
    }
    set addAreaLongPressGesture(x29) {
        this.__addAreaLongPressGesture.set(x29);
    }
    get arraySelectIsChange() {
        return this.__arraySelectIsChange.get();
    }
    set arraySelectIsChange(w29) {
        this.__arraySelectIsChange.set(w29);
    }
    get arrayUnSelectIsChange() {
        return this.__arrayUnSelectIsChange.get();
    }
    set arrayUnSelectIsChange(v29) {
        this.__arrayUnSelectIsChange.set(v29);
    }
    get textItemEditWidth() {
        return this.__textItemEditWidth.get();
    }
    set textItemEditWidth(u29) {
        this.__textItemEditWidth.set(u29);
    }
    get textItemEditHeight() {
        return this.__textItemEditHeight.get();
    }
    set textItemEditHeight(t29) {
        this.__textItemEditHeight.set(t29);
    }
    get imageItemWidth() {
        return this.__imageItemWidth.get();
    }
    set imageItemWidth(s29) {
        this.__imageItemWidth.set(s29);
    }
    get saveClick() {
        return this.__saveClick.get();
    }
    set saveClick(r29) {
        this.__saveClick.set(r29);
    }
    get imageTextAddIconShow() {
        return this.__imageTextAddIconShow.get();
    }
    set imageTextAddIconShow(q29) {
        this.__imageTextAddIconShow.set(q29);
    }
    get imageTextRemoveIconShow() {
        return this.__imageTextRemoveIconShow.get();
    }
    set imageTextRemoveIconShow(p29) {
        this.__imageTextRemoveIconShow.set(p29);
    }
    get firstIn() {
        return this.__firstIn.get();
    }
    set firstIn(o29) {
        this.__firstIn.set(o29);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(n29) {
        this.__fontSizeScale.set(n29);
    }
    get fontWeightScale() {
        return this.__fontWeightScale.get();
    }
    set fontWeightScale(m29) {
        this.__fontWeightScale.set(m29);
    }
    get customColumns() {
        return this.__customColumns.get();
    }
    set customColumns(l29) {
        this.__customColumns.set(l29);
    }
    get editGridHeight() {
        return this.__editGridHeight.get();
    }
    set editGridHeight(k29) {
        this.__editGridHeight.set(k29);
    }
    get addGridHeight() {
        return this.__addGridHeight.get();
    }
    set addGridHeight(j29) {
        this.__addGridHeight.set(j29);
    }
    get subTitleHeight() {
        return this.__subTitleHeight.get();
    }
    set subTitleHeight(i29) {
        this.__subTitleHeight.set(i29);
    }
    get readFlag() {
        return this.__readFlag.get();
    }
    set readFlag(h29) {
        this.__readFlag.set(h29);
    }
    get readIndex4AddArea() {
        return this.__readIndex4AddArea.get();
    }
    set readIndex4AddArea(g29) {
        this.__readIndex4AddArea.set(g29);
    }
    get readIndex4EditArea() {
        return this.__readIndex4EditArea.get();
    }
    set readIndex4EditArea(f29) {
        this.__readIndex4EditArea.set(f29);
    }
    get isPointToAddTitleBarEditButton() {
        return this.__isPointToAddTitleBarEditButton.get();
    }
    set isPointToAddTitleBarEditButton(e29) {
        this.__isPointToAddTitleBarEditButton.set(e29);
    }
    get isPointToEditTitleBarSaveButton() {
        return this.__isPointToEditTitleBarSaveButton.get();
    }
    set isPointToEditTitleBarSaveButton(d29) {
        this.__isPointToEditTitleBarSaveButton.set(d29);
    }
    aboutToAppear() {
        this.dataList.length = 50;
        this.selected = this.dataList && this.deduplicate(this.dataList).filter(c29 => c29.selected).sort(this.sortBy());
        this.unSelected = this.dataList && this.deduplicate(this.dataList).filter(b29 => !b29.selected).sort(this.sortBy());
        this.copySelected = this.selected.slice();
        this.copyUnSelected = this.unSelected.slice();
        this.editGridDataLength = this.selected.length;
        this.imageText = this.options.type === GridObjectSortComponentType.IMAGE_TEXT;
        try {
            let a29 = this.getUIContext();
            this.isFollowingSystemFontScale = a29.isFollowingSystemFontScale();
            this.maxAppFontScale = a29.getMaxFontScale();
            this.fontSizeScale = this.decideFontScale(a29);
            this.fontWeightScale =
                a29.getHostContext()?.config.fontWeightScale ?? DEFAULT_FONT_WEIGHT_SCALE;
        }
        catch (x28) {
            let y28 = x28.code;
            let z28 = x28.message;
            hilog.error(0x3900, 'Ace', `GridObjectSortComponent Faild to init fontsizescale info, code:${y28}, message: ${z28}`);
        }
        try {
            this.callbackId = getContext()?.getApplicationContext()?.on('environment', this.envCallback);
        }
        catch (u28) {
            let v28 = u28.code;
            let w28 = u28.message;
            hilog.error(0x3900, 'Ace', `GridObjectSortComponent Faild to get environment param error: ${v28}, ${w28}`);
        }
        this.calcGridHeight();
        setTimeout(() => {
            this.firstIn = false;
        }, 500);
        this.bundleName = getContext(this)?.abilityInfo?.bundleName;
    }
    getAdaptiveSymbolFontSize() {
        let t28 = this.fontSizeScale;
        if (!this.isFollowingSystemFontScale || t28 === undefined) {
            t28 = MIN_FONT_SCALE;
        }
        t28 = Math.min(MIN_SYMBOL_FONT_SCALE, t28);
        t28 = Math.max(t28, MIN_FONT_SCALE);
        return (t28 * SYMBOL_SIZE_12FP).toString() + 'vp';
    }
    getSymbolFontSizeFrom(s28) {
        if (s28 === undefined) {
            return SYMBOL_DEFAULT;
        }
        if (typeof s28 === 'number') {
            return s28.toString() + 'vp';
        }
        return s28;
    }
    calcTextItemEditHeight() {
        let r28 = MeasureText.measureTextSize({
            textContent: this.dataList[0]?.text ?? '',
            fontSize: `${(LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_button3'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' })?.value ??
                DEFAULT_TEXT_SIZE) * (this.fontSizeScale ?? DEFAULT_FONT_SIZE_SCALE)}vp`,
            overflow: TextOverflow.Ellipsis,
            maxLines: TEXT_MAX_LINES
        });
        this.textItemEditHeight = this.fontSizeScale === DEFAULT_FONT_SIZE_SCALE ?
            GRID_ITEM_HEIGHT_TEXT : px2vp(r28.height);
        this.textItemEditHeight = this.textItemEditHeight + PADDING_EIGHT * 2;
    }
    decideFontScale(p28) {
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        let q28 = p28.getHostContext()?.config.fontSizeScale ?? DEFAULT_FONT_SIZE_SCALE;
        return Math.min(q28, this.maxAppFontScale, MAX_FONT_SCALE);
    }
    calcColNum() {
        if (this.imageText || (this.fontSizeScale && this.fontSizeScale > DEFAULT_FONT_SIZE_SCALE)) {
            this.customColumns = GRID_COL_3;
            this.colNum = COL_IMAGE_TEXT;
        }
        else {
            this.customColumns = GRID_COL_4;
            this.colNum = COL_TEXT;
        }
    }
    aboutToDisappear() {
        Context.animateTo({
            duration: ENTER_EXIT_ICON_DURATION,
            curve: COMMON_BEZIER,
        }, () => {
            this.gridComState = false;
        });
        this.menuSwitch = false;
        this.selected = this.copySelected;
        this.unSelected = this.copyUnSelected;
        if (this.callbackId) {
            this.getUIContext()
                .getHostContext()
            ?.getApplicationContext()
            ?.off('environment', this.callbackId);
            this.callbackId = void (0);
        }
    }
    deduplicate(l28) {
        const m28 = [];
        l28.forEach(n28 => {
            if (!m28.some(o28 => o28.id === n28.id)) {
                m28.push(n28);
            }
        });
        return m28;
    }
    onGridComStateChange() {
        this.textItemEditWidth = this.gridComState ? this.blockWidth - 24 : this.blockWidth - 16;
        if (!this.imageText) {
            this.blockHeight = this.gridComState ?
                this.textItemEditHeight + EDIT_BLOCK_TEXT_ITEM_SAFE_MARGIN :
                this.textItemEditHeight + DEFAULT_BLOCK_TEXT_ITEM_SAFE_MARGIN;
        }
    }
    sortBy() {
        return (j28, k28) => {
            return j28.order - k28.order;
        };
    }
    cancelEdit() {
        if (this.isStartDrag || this.clickAddBtn || this.clickRemoveBtn) {
            return;
        }
        Context.animateTo({
            duration: ENTER_EXIT_ICON_DURATION,
            curve: LONG_TOUCH_SCALE
        }, () => {
            this.longScaleOnePointTwo = 1;
        });
        Context.animateTo({
            duration: ENTER_EXIT_ICON_DURATION,
            curve: COMMON_BEZIER,
        }, () => {
            this.gridComState = false;
        });
        this.menuSwitch = false;
        this.selected = this.copySelected.slice();
        this.unSelected = this.copyUnSelected.slice();
        this.editGridDataLength = this.selected.length;
        this.calcGridHeight();
        this.isPointToAddTitleBarEditButton = true;
        this.onCancel && this.onCancel();
    }
    goEdit() {
        Context.animateTo({
            duration: ENTER_EXIT_ICON_DURATION,
            curve: COMMON_BEZIER,
        }, () => {
            this.gridComState = true;
        });
        this.menuSwitch = true;
        this.isPointToEditTitleBarSaveButton = true;
        this.calcGridHeight();
    }
    pointToEditTitleBarSaveButton() {
        if (this.isPointToEditTitleBarSaveButton) {
            let h28 = this.getUIContext().getFrameNodeById(EDIT_TITLE_BAR_ID)?.getFirstChild()?.getUniqueId();
            let i28 = ({
                type: 'requestFocusForAccessibility',
                bundleName: this.bundleName,
                triggerAction: 'common',
                customId: `SaveMenuItem_${h28}`
            });
            accessibility.sendAccessibilityEvent(i28).then(() => {
                setTimeout(() => {
                    this.isPointToEditTitleBarSaveButton = false;
                }, ENTER_EXIT_ICON_DURATION);
            });
        }
    }
    onSaveEdit() {
        if (this.isStartDrag) {
            return;
        }
        Context.animateTo({
            duration: ENTER_EXIT_ICON_DURATION,
            curve: LONG_TOUCH_SCALE
        }, () => {
            this.longScaleOnePointTwo = 1;
        });
        this.editGridDataLength = this.selected.length;
        Context.animateTo({
            duration: ENTER_EXIT_ICON_DURATION,
            curve: COMMON_BEZIER,
        }, () => {
            this.gridComState = false;
            this.copySelected = this.selected.slice();
            this.copyUnSelected = this.unSelected.slice();
            const f28 = this.getNewData(this.selected, true, 0);
            const g28 = this.getNewData(this.unSelected, false, this.selected.length);
            this.selected = f28;
            this.unSelected = g28;
            this.calcGridHeight();
            this.onSave && this.onSave(f28, g28);
        });
        setTimeout(() => {
            this.saveClick = false;
        }, ENTER_EXIT_ICON_DURATION);
        this.menuSwitch = false;
        this.isPointToAddTitleBarEditButton = true;
    }
    pointToAddTitleBarEditButton() {
        if (this.isPointToAddTitleBarEditButton) {
            let d28 = this.getUIContext()?.getFrameNodeById(ADD_TITLE_BAR_ID)?.getFirstChild()?.getUniqueId();
            let e28 = ({
                type: 'requestFocusForAccessibility',
                bundleName: this.bundleName,
                triggerAction: 'common',
                customId: `ComposeTitleBar_ImageMenuItem_${d28}_0`
            });
            accessibility.sendAccessibilityEvent(e28).then(() => {
                setTimeout(() => {
                    this.isPointToAddTitleBarEditButton = false;
                }, ENTER_EXIT_ICON_DURATION);
            });
        }
    }
    onDragMoveEvent(z27, a28, b28) {
        if (!this.gridComState || (z27.x < this.blockWidth / 3 && z27.y < this.blockHeight / 3)) {
            return;
        }
        let c28 = b28;
        if (c28 < 0) {
            c28 = this.selected.length - 1;
        }
        else {
            this.textAnnouncedForAccessibility = this.getStringByResource(ACCESSIBILITY_SELECTED_ITEM_DRAG_MOVING, Math.floor(b28 / this.colNum) + 1, b28 % this.colNum + 1);
        }
        if (this.dragContent.visibility !== Visibility.Hidden) {
            this.dragContent.visibility = Visibility.Hidden;
        }
        if (this.insertIndex !== b28 || a28 !== b28) {
            this.sendAccessibility();
        }
        this.insertIndex = b28;
    }
    sendAccessibility() {
        if (this.preTextAnnouncedForAccessibility !== this.textAnnouncedForAccessibility) {
            let y27 = ({
                type: 'announceForAccessibility',
                bundleName: this.bundleName,
                triggerAction: 'common',
                textAnnouncedForAccessibility: this.textAnnouncedForAccessibility
            });
            accessibility.sendAccessibilityEvent(y27);
            this.preTextAnnouncedForAccessibility = this.textAnnouncedForAccessibility;
        }
    }
    handleDeleteClick(u27) {
        if (this.clickAddBtn || this.clickRemoveBtn) {
            return;
        }
        this.clickRemoveBtn = true;
        this.scaleIcon = 0;
        this.arraySelectIsChange = 1;
        let v27 = this.selected.findIndex(x27 => x27.id === u27.id);
        this.content = u27;
        this.selectedIndex = v27;
        this.calcGridHeight();
        Context.animateTo({ curve: REMOVE_ADD_SPRING, onFinish: () => {
            this.scaleIcon = 1;
            this.selected.splice(v27, 1);
            this.unSelected.unshift(u27);
            this.calcGridHeight();
            this.editGridDataLength = this.editGridDataLength - 1;
            this.editItemMoveX = 0;
            this.editItemMoveY = 0;
            this.arraySelectIsChange = 2;
            this.clickRemoveBtn = false;
            this.readFlag = false;
            this.readIndex4AddArea = 0;
            this.textAnnouncedForAccessibility = this.getStringByResource(ACCESSIBILITY_DELETED, `${this.content?.text ?? ' '}`);
        } }, () => {
            let w27 = this.getAddItemGridPosition();
            this.editItemMoveX = w27.x;
            this.editItemMoveY = w27.y;
        });
    }
    pointToAddArea() {
        let t27 = ({
            type: 'requestFocusForAccessibility',
            bundleName: this.bundleName,
            triggerAction: 'common',
            customId: ADD_GRID_FIRST_ITEM_ID
        });
        accessibility.sendAccessibilityEvent(t27).then(() => {
            setTimeout(() => {
                this.readFlag = true;
                this.readIndex4AddArea = -1;
            }, ENTER_EXIT_ICON_DURATION);
        });
    }
    getNewData(o27, p27, q27) {
        return o27.map((r27, s27) => {
            r27.selected = p27;
            r27.order = q27 + s27;
            r27.visibility = Visibility.Visible;
            return r27;
        });
    }
    getBlockWidth() {
        const n27 = (this.areaWidth - 32) / this.colNum;
        return n27;
    }
    calcGridHeight() {
        this.editGridHeight = this.getGridHeight(this.selected, EDIT);
        this.addGridHeight = this.getGridHeight(this.unSelected);
    }
    getGridHeight(f27, g27) {
        let h27 = 0;
        let i27 = f27.length;
        f27.forEach(m27 => {
            if (m27.visibility === Visibility.Hidden) {
                i27 = i27 - 1;
            }
        });
        let j27 = 0;
        let k27 = i27 % this.colNum === 0;
        if (this.clickAddBtn && k27) {
            j27 = 1;
        }
        else if (this.isStartDrag && k27 && g27) {
            j27 = 1;
        }
        else if (this.clickRemoveBtn && k27 && !g27) {
            j27 = 1;
        }
        else {
            j27 = 0;
        }
        let l27 = Math.ceil(i27 / this.colNum) + j27;
        h27 = this.blockHeight * l27;
        if (i27 === 0) {
            h27 = 0;
        }
        return h27;
    }
    imageTextRemoveIcon(c27) {
        const d27 = this.clickRemoveBtn && this.content.id === c27.id;
        const e27 = d27 ? { 'id': -1, 'type': 40000, params: ['sys.symbol.plus_circle_fill'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 40000, params: ['sys.symbol.minus_circle_fill'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        return e27;
    }
    imageTextAddIcon(z26) {
        const a27 = this.clickAddBtn && this.content.id === z26.id && this.gridComState;
        const b27 = a27 ? { 'id': -1, 'type': 40000, params: ['sys.symbol.minus_circle_fill'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 40000, params: ['sys.symbol.plus_circle_fill'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        return b27;
    }
    imageTextAddIconVisible(w26) {
        const x26 = this.clickAddBtn && this.content.id === w26.id && !this.gridComState;
        const y26 = x26 ? Visibility.Hidden : Visibility.Visible;
        return y26;
    }
    getCoodXY(r26) {
        let s26 = 0;
        let t26 = 0;
        const u26 = this.colNum;
        const v26 = Math.trunc(r26 % u26);
        if (r26 >= this.dragContentIndex) {
            if (r26 <= this.insertIndex && r26 !== this.dragContentIndex) {
                if (v26 === 0) {
                    s26 = s26 + this.blockWidth * (u26 - 1);
                    t26 = t26 - this.blockHeight;
                }
                else {
                    s26 = s26 - this.blockWidth;
                }
            }
        }
        else {
            if (r26 >= this.insertIndex) {
                if (v26 === u26 - 1) {
                    s26 = s26 - this.blockWidth * (u26 - 1);
                    t26 = t26 + this.blockHeight;
                }
                else {
                    s26 = s26 + this.blockWidth;
                }
            }
        }
        if (!this.isStartDrag) {
            s26 = 0;
            t26 = 0;
        }
        return { x: s26, y: t26 };
    }
    getAddItemGridPosition() {
        const f26 = this.selected.length;
        const g26 = this.colNum;
        const h26 = (this.selectedIndex + 1) % g26;
        const i26 = Math.ceil((this.selectedIndex + 1) / g26);
        const j26 = Math.ceil(f26 / g26);
        const k26 = this.imageText;
        let l26 = 0;
        if (h26 === 0) {
            l26 = k26 || (this.fontSizeScale && this.fontSizeScale > 1) ? -this.blockWidth * 2 : -this.blockWidth * 3;
        }
        else {
            l26 = -this.blockWidth * (h26 - 1);
        }
        let m26 = SUBTITLE_HEIGHT;
        let n26 = 0;
        const o26 = j26 - i26;
        const p26 = f26 % g26;
        const q26 = p26 === 1 ? o26 : o26 + 1;
        if (this.fontSizeScale && this.fontSizeScale > 1) {
            m26 = this.subTitleHeight;
        }
        n26 = q26 * this.blockHeight + m26;
        return {
            x: l26,
            y: n26
        };
    }
    getCoveringGridPosition(c26) {
        let d26 = 0;
        let e26 = 0;
        if (c26 > this.selectedIndex && this.arraySelectIsChange !== 2) {
            d26 = c26 % this.colNum === 0 ? this.blockWidth * (this.colNum - 1) : -this.blockWidth;
            e26 = c26 % this.colNum === 0 ? -this.blockHeight : 0;
        }
        return {
            x: d26,
            y: e26
        };
    }
    getEditItemGridPosition(q25, r25) {
        const s25 = q25.length;
        const t25 = this.colNum;
        const u25 = Math.trunc(s25 % t25);
        const v25 = Math.trunc(r25 % t25);
        let w25 = Math.abs(u25 - v25) * this.blockWidth;
        if (u25 < v25) {
            w25 = -w25;
        }
        else if (u25 > v25) {
            w25 = w25;
        }
        else {
            w25 = 0;
        }
        let x25 = 0;
        let y25 = 0;
        let z25 = Math.trunc(r25 / this.colNum);
        let a26 = SUBTITLE_HEIGHT;
        const b26 = !this.imageText && this.gridComState && r25 > 3;
        if (b26) {
            y25 = (z25 + 1) * (this.blockHeight - 8) + 8;
        }
        else {
            y25 = (z25 + 1) * this.blockHeight;
        }
        if (this.fontSizeScale && this.fontSizeScale > 1) {
            a26 = this.subTitleHeight;
        }
        x25 = y25 + a26;
        return {
            x: w25,
            y: x25
        };
    }
    getCoveringGridPositionBottom(l25) {
        let m25 = 0;
        let n25 = 0;
        const o25 = l25 % this.colNum === 0;
        const p25 = this.gridComState && !this.imageText ? -this.blockHeight + 8 : -this.blockHeight;
        if (l25 > this.unSelectedIndex && this.arrayUnSelectIsChange !== 2) {
            m25 = o25 ? this.blockWidth * (this.colNum - 1) : -this.blockWidth;
            n25 = o25 ? p25 : 0;
        }
        return {
            x: m25,
            y: n25
        };
    }
    getAddItemRightMove(h25) {
        let i25 = this.blockWidth;
        let j25 = 0;
        let k25 = (h25 + 1) % this.colNum === 0;
        if (k25) {
            i25 = -this.blockWidth * (this.colNum - 1);
            j25 = this.imageText ? this.blockHeight : this.blockHeight - 8;
        }
        return { x: i25, y: j25 };
    }
    getShowAreaItemTranslate(e25) {
        if (this.isStartDrag) {
            let g25 = this.getCoodXY(e25);
            return {
                x: g25.x,
                y: g25.y
            };
        }
        if (!this.isStartDrag && e25 === this.selectedIndex) {
            return {
                x: this.editItemMoveX,
                y: this.editItemMoveY
            };
        }
        if (!this.isStartDrag && e25 !== this.selectedIndex && this.clickRemoveBtn) {
            let f25 = this.getCoveringGridPosition(e25);
            return {
                x: f25.x,
                y: f25.y
            };
        }
        return { x: 0, y: 0 };
    }
    getAddAreaItemTranslate(b25) {
        if (this.clickRemoveBtn) {
            let d25 = this.getAddItemRightMove(b25);
            return {
                x: d25.x,
                y: d25.y
            };
        }
        if (!this.clickRemoveBtn && b25 === this.unSelectedIndex) {
            return {
                x: this.addItemMoveX,
                y: -this.addItemMoveY
            };
        }
        if (!this.clickRemoveBtn && b25 !== this.unSelectedIndex && this.clickAddBtn) {
            let c25 = this.getCoveringGridPositionBottom(b25);
            return {
                x: c25.x,
                y: c25.y
            };
        }
        return { x: 0, y: 0 };
    }
    PixelMapBuilder(a24, b24, c24 = null) {
        this.observeComponentCreation2((z24, a25) => {
            Stack.create({ alignContent: Alignment.Center });
            Stack.clip(false);
            Stack.height(this.blockHeight * 1.5);
            Stack.width(this.blockWidth * 1.2);
        }, Stack);
        this.observeComponentCreation2((d24, e24) => {
            If.create();
            if (this.imageText) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((x24, y24) => {
                        Column.create();
                        Column.alignItems(HorizontalAlign.Center);
                        Column.justifyContent(FlexAlign.Center);
                        Column.width(this.imageItemWidth);
                        Column.height(this.imageItemWidth);
                        Column.padding({ left: MARGIN_EIGHT, right: MARGIN_EIGHT });
                        Column.backgroundColor(this.touchDown);
                        Column.borderRadius(this.touchBorderRadius);
                        Column.scale({ x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo });
                    }, Column);
                    this.observeComponentCreation2((p24, q24) => {
                        If.create();
                        if (a24 === undefined) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((v24, w24) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.height(this.options.imageSize || SYMBOL_DEFAULT);
                                    SymbolGlyph.width(this.options.imageSize || SYMBOL_DEFAULT);
                                    SymbolGlyph.fontSize(this.options.imageSize || SYMBOL_DEFAULT);
                                }, SymbolGlyph);
                            });
                        }
                        else if (a24 instanceof SymbolGlyphModifier) {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((t24, u24) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.height(this.options.imageSize || SYMBOL_DEFAULT);
                                    SymbolGlyph.width(this.options.imageSize || SYMBOL_DEFAULT);
                                    SymbolGlyph.attributeModifier.bind(this)(a24);
                                    SymbolGlyph.fontSize(this.options.imageSize || SYMBOL_DEFAULT);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(2, () => {
                                this.observeComponentCreation2((r24, s24) => {
                                    Image.create(a24);
                                    Image.draggable(false);
                                    Image.height(this.options.imageSize || IMAGE_DEFAULT);
                                    Image.width(this.options.imageSize || IMAGE_DEFAULT);
                                }, Image);
                            });
                        }
                    }, If);
                    If.pop();
                    this.observeComponentCreation2((n24, o24) => {
                        Text.create(b24);
                        Text.textAlign(TextAlign.Center);
                        Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_button3'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.margin({ top: 2 });
                        Text.maxLines(TEXT_MAX_LINES);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.minFontScale(MIN_FONT_SCALE);
                        Text.maxFontScale(ObservedObject.GetRawObject(this.fontSizeScale));
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((l24, m24) => {
                        SymbolGlyph.create({ 'id': -1, 'type': 40000, params: ['sys.symbol.minus_circle_fill'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        SymbolGlyph.fontSize(SYMBOL_SIZE_24VP);
                        SymbolGlyph.fontWeight(SYMBOL_WEIGHT);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                        SymbolGlyph.width(ICON_SIZE);
                        SymbolGlyph.height(ICON_SIZE);
                        SymbolGlyph.position({
                            x: this.blockWidth - 40,
                            y: -MARGIN_EIGHT
                        });
                    }, SymbolGlyph);
                    Column.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((j24, k24) => {
                        Row.create();
                        Row.borderRadius(50);
                        Row.padding({
                            left: TEXT_PADDING_LEFT_RIGHT,
                            right: TEXT_PADDING_LEFT_RIGHT,
                        });
                        Row.scale({ x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo });
                        Row.alignItems(VerticalAlign.Center);
                        Row.justifyContent(FlexAlign.Center);
                        Row.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_button_normal'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Row.width(this.textItemEditWidth);
                        Row.height(this.textItemEditHeight);
                    }, Row);
                    this.observeComponentCreation2((h24, i24) => {
                        Text.create(b24);
                        Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_button3'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.textAlign(TextAlign.Center);
                        Text.maxLines(TEXT_MAX_LINES);
                        Text.minFontScale(MIN_FONT_SCALE);
                        Text.maxFontScale(ObservedObject.GetRawObject(this.fontSizeScale));
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((f24, g24) => {
                        SymbolGlyph.create({ 'id': -1, 'type': 40000, params: ['sys.symbol.minus_circle_fill'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        SymbolGlyph.fontSize(SYMBOL_SIZE_24VP);
                        SymbolGlyph.fontWeight(SYMBOL_WEIGHT);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                        SymbolGlyph.width(ICON_SIZE);
                        SymbolGlyph.height(ICON_SIZE);
                        SymbolGlyph.position({
                            x: this.blockWidth - 52,
                            y: -MARGIN_EIGHT
                        });
                    }, SymbolGlyph);
                    Row.pop();
                });
            }
        }, If);
        If.pop();
        Stack.pop();
    }
    HeaderTitleBuilder(j23 = null) {
        this.observeComponentCreation2((w23, x23) => {
            __Common__.create();
            __Common__.id(ADD_TITLE_BAR_ID);
            __Common__.visibility(!this.menuSwitch ? Visibility.Visible : Visibility.None);
            __Common__.onVisibleAreaChange([0.0, 1.0], (y23, z23) => {
                if (y23) {
                    this.pointToAddTitleBarEditButton();
                }
            });
        }, __Common__);
        {
            this.observeComponentCreation2((s23, t23) => {
                if (t23) {
                    let u23 = new ComposeTitleBar(this, {
                        title: this.options.normalTitle || { 'id': -1, 'type': 10003, params: ['sys.string.ohos_grid_edit_title_chanel'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        menuItems: this.menuItems,
                    }, undefined, s23, () => { }, { page: 'library/src/main/ets/components/GridObjectSortComponent.ets', line: 963, col: 5 });
                    ViewPU.create(u23);
                    let v23 = () => {
                        return {
                            title: this.options.normalTitle || { 'id': -1, 'type': 10003, params: ['sys.string.ohos_grid_edit_title_chanel'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            menuItems: this.menuItems
                        };
                    };
                    u23.paramsGenerator_ = v23;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(s23, {});
                }
            }, { name: 'ComposeTitleBar' });
        }
        __Common__.pop();
        this.observeComponentCreation2((o23, p23) => {
            __Common__.create();
            __Common__.id(EDIT_TITLE_BAR_ID);
            __Common__.visibility(this.menuSwitch ? Visibility.Visible : Visibility.None);
            __Common__.onVisibleAreaChange([0.0, 1.0], (q23, r23) => {
                if (q23) {
                    this.pointToEditTitleBarSaveButton();
                }
            });
        }, __Common__);
        {
            this.observeComponentCreation2((k23, l23) => {
                if (l23) {
                    let m23 = new EditableTitleBar(this, {
                        leftIconStyle: EditableLeftIconType.Cancel,
                        menuItems: [],
                        title: this.options.editTitle || { 'id': -1, 'type': 10003, params: ['sys.string.ohos_grid_edit_title_edit'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        onCancel: () => {
                            this.cancelEdit();
                        },
                        onSave: () => {
                            this.saveClick = true;
                            this.onSaveEdit();
                        }
                    }, undefined, k23, () => { }, { page: 'library/src/main/ets/components/GridObjectSortComponent.ets', line: 974, col: 5 });
                    ViewPU.create(m23);
                    let n23 = () => {
                        return {
                            leftIconStyle: EditableLeftIconType.Cancel,
                            menuItems: [],
                            title: this.options.editTitle || { 'id': -1, 'type': 10003, params: ['sys.string.ohos_grid_edit_title_edit'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            onCancel: () => {
                                this.cancelEdit();
                            },
                            onSave: () => {
                                this.saveClick = true;
                                this.onSaveEdit();
                            }
                        };
                    };
                    m23.paramsGenerator_ = n23;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(k23, {});
                }
            }, { name: 'EditableTitleBar' });
        }
        __Common__.pop();
    }
    ImageTextBuilder(m22, n22, o22 = null) {
        this.observeComponentCreation2((h23, i23) => {
            Column.create();
            Column.padding({ left: MARGIN_EIGHT, right: MARGIN_EIGHT });
            Column.width('100%');
        }, Column);
        this.observeComponentCreation2((f23, g23) => {
            Column.create();
            Column.alignItems(HorizontalAlign.Center);
            Column.justifyContent(FlexAlign.Center);
            Column.width('100%');
            Column.height(this.imageItemWidth);
            Column.padding({ left: MARGIN_EIGHT, right: MARGIN_EIGHT });
            Column.borderRadius((this.isTouchDown && m22.id === this.content.id) ||
                m22.id === this.hoverId ? this.touchBorderRadius : 0);
            Column.backgroundColor(this.isTouchDown && m22.id === this.content.id
                ? this.touchDown : m22.id === this.hoverId ? this.hoverBackgroundColor : '');
            Column.scale(m22.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } : {});
        }, Column);
        this.observeComponentCreation2((v22, w22) => {
            If.create();
            if (m22.symbolStyle !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((d23, e23) => {
                        SymbolGlyph.create();
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.attributeModifier.bind(this)(m22.symbolStyle);
                        SymbolGlyph.fontSize(this.getSymbolFontSizeFrom(this.options.imageSize));
                    }, SymbolGlyph);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((x22, y22) => {
                        If.create();
                        if (m22.url === undefined) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((b23, c23) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.fontSize(this.getSymbolFontSizeFrom(this.options.imageSize));
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((z22, a23) => {
                                    Image.create(m22.url);
                                    Image.draggable(false);
                                    Image.height(this.options.imageSize || IMAGE_DEFAULT);
                                    Image.width((this.options.imageSize || IMAGE_DEFAULT));
                                }, Image);
                            });
                        }
                    }, If);
                    If.pop();
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((t22, u22) => {
            Text.create(m22.text);
            Text.textAlign(TextAlign.Center);
            Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_button3'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Text.margin({ top: 2 });
            Text.maxLines(TEXT_MAX_LINES);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.minFontScale(MIN_FONT_SCALE);
            Text.maxFontScale(ObservedObject.GetRawObject(this.fontSizeScale));
            Text.padding({
                top: PADDING_EIGHT,
                bottom: PADDING_EIGHT
            });
        }, Text);
        Text.pop();
        this.observeComponentCreation2((r22, s22) => {
            SymbolGlyph.create(this.imageTextAddIcon(m22));
            SymbolGlyph.fontSize(SYMBOL_SIZE_24VP);
            SymbolGlyph.fontWeight(SYMBOL_WEIGHT);
            SymbolGlyph.draggable(false);
            SymbolGlyph.visibility(n22 === 'add' ? this.imageTextAddIconVisible(m22) : Visibility.Hidden);
            SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
            SymbolGlyph.width(ICON_SIZE);
            SymbolGlyph.height(ICON_SIZE);
            SymbolGlyph.position({
                x: this.blockWidth - 40,
                y: -MARGIN_EIGHT
            });
            SymbolGlyph.onClick(() => this.handleAddIconClick(m22));
            SymbolGlyph.accessibilityLevel(YES);
            SymbolGlyph.accessibilityText(this.getStringByResource(ACCESSIBILITY_UNSELECTED_BUTTON, `${m22.text ?? ''}`));
        }, SymbolGlyph);
        this.observeComponentCreation2((p22, q22) => {
            SymbolGlyph.create(this.imageTextRemoveIcon(m22));
            SymbolGlyph.fontSize(SYMBOL_SIZE_24VP);
            SymbolGlyph.fontWeight(SYMBOL_WEIGHT);
            SymbolGlyph.draggable(false);
            SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
            SymbolGlyph.visibility(n22 === 'delete' && this.gridComState ? Visibility.Visible :
            Visibility.Hidden);
            SymbolGlyph.width(ICON_SIZE);
            SymbolGlyph.height(ICON_SIZE);
            SymbolGlyph.position({
                x: this.blockWidth - 40,
                y: -MARGIN_EIGHT
            });
            SymbolGlyph.onClick(() => this.handleDeleteClick(m22));
            SymbolGlyph.accessibilityLevel(YES);
            SymbolGlyph.accessibilityText(this.getStringByResource(ACCESSIBILITY_SELECTED_ITEM_DELETE, `${m22.text ?? ''}`));
        }, SymbolGlyph);
        Column.pop();
        Column.pop();
    }
    handleAddIconClick(h22) {
        if (this.clickAddBtn || this.clickRemoveBtn) {
            return;
        }
        this.scaleIcon = 0;
        this.content = h22;
        const i22 = this.unSelected.findIndex(l22 => l22.id === h22.id);
        this.editGridDataLength = this.selected.length + 1;
        const j22 = this.getEditItemGridPosition(this.selected, i22);
        this.unSelectedIndex = i22;
        this.arrayUnSelectIsChange = 1;
        this.clickAddBtn = true;
        this.calcGridHeight();
        Context.animateTo({
            curve: REMOVE_ADD_SPRING,
            onFinish: () => {
                if (!this.selected.some(k22 => k22.id === h22.id)) {
                    this.arrayUnSelectIsChange = 2;
                    this.scaleIcon = 1;
                    this.selected.push(h22);
                    this.unSelected.splice(i22, 1);
                    this.calcGridHeight();
                    this.addItemMoveX = 0;
                    this.addItemMoveY = 0;
                    if (!this.gridComState) {
                        this.onSaveEdit();
                    }
                    this.clickAddBtn = false;
                }
            }
        }, () => {
            this.addItemMoveX = j22.x;
            this.addItemMoveY = j22.y;
        });
        this.readFlag = false;
        this.readIndex4EditArea = this.editGridDataLength - 1;
        this.textAnnouncedForAccessibility = this.getStringByResource(ACCESSIBILITY_UNSELECTED_ITEM_ADD, `${this.content?.text ?? ''}`, Math.floor(this.readIndex4EditArea / this.colNum) + 1, this.readIndex4EditArea % this.colNum + 1);
    }
    TextBlockBuilder(t21, u21 = null) {
        this.observeComponentCreation2((f22, g22) => {
            Stack.create();
            Stack.scale(t21.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } : {});
            Stack.padding({
                left: MARGIN_EIGHT,
                right: MARGIN_EIGHT
            });
            Stack.height(this.textItemEditHeight);
        }, Stack);
        this.observeComponentCreation2((d22, e22) => {
            Row.create();
            Context.animation(!this.firstIn ? {
                duration: ENTER_EXIT_ICON_DURATION,
                curve: this.gridComState ? DRAG_SPRING : COMMON_BEZIER
            } : { duration: 0 });
            Row.borderRadius(50);
            Row.width(this.clickRemoveBtn && t21.id === this.content.id ?
                this.textItemEditWidth + 8 : this.textItemEditWidth);
            Row.translate(this.gridComState ? this.clickRemoveBtn &&
                t21.id === this.content.id ? { x: 0 } : { x: -4 } : { x: 0 });
            Row.height('100%');
            Context.animation(null);
            Row.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_button_normal'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
        }, Row);
        Row.pop();
        this.observeComponentCreation2((b22, c22) => {
            Flex.create({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center });
            Context.animation(!this.firstIn ? {
                duration: ENTER_EXIT_ICON_DURATION,
                curve: this.gridComState ? DRAG_SPRING : COMMON_BEZIER
            } : { duration: 0 });
            Flex.borderRadius(50);
            Flex.padding({
                left: TEXT_PADDING_LEFT_RIGHT,
                right: TEXT_PADDING_LEFT_RIGHT,
            });
            Flex.backgroundColor(this.isTouchDown && t21.id === this.content.id ? this.touchDown
                : t21.id === this.hoverId ? this.hoverBackgroundColor
                    : '');
            Flex.width(this.clickRemoveBtn && t21.id === this.content.id ?
                this.textItemEditWidth + 8 : this.textItemEditWidth);
            Flex.translate(this.gridComState ? this.clickRemoveBtn && t21.id === this.content.id ?
                { x: 0 } : { x: -4 } : { x: 0 });
            Flex.height('100%');
            Context.animation(null);
        }, Flex);
        this.observeComponentCreation2((z21, a22) => {
            SymbolGlyph.create({ 'id': -1, 'type': 40000, params: ['sys.symbol.plus'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: COMMON_BEZIER
            });
            SymbolGlyph.fontSize(this.getAdaptiveSymbolFontSize());
            SymbolGlyph.draggable(false);
            SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
            SymbolGlyph.visibility(this.clickRemoveBtn && t21.id === this.content.id ? Visibility.Visible : Visibility.None);
            SymbolGlyph.transition({ type: TransitionType.All, scale: { x: 0, y: 0, } });
            SymbolGlyph.margin({ right: 4 });
            Context.animation(null);
        }, SymbolGlyph);
        this.observeComponentCreation2((x21, y21) => {
            Text.create(t21.text);
            Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_button3'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.textAlign(TextAlign.Center);
            Text.maxLines(TEXT_MAX_LINES);
            Text.minFontScale(MIN_FONT_SCALE);
            Text.maxFontScale(ObservedObject.GetRawObject(this.fontSizeScale));
        }, Text);
        Text.pop();
        this.observeComponentCreation2((v21, w21) => {
            SymbolGlyph.create({ 'id': -1, 'type': 40000, params: ['sys.symbol.minus_circle_fill'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: COMMON_BEZIER,
            });
            SymbolGlyph.fontSize(SYMBOL_SIZE_24VP);
            SymbolGlyph.fontWeight(SYMBOL_WEIGHT);
            SymbolGlyph.draggable(false);
            SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
            SymbolGlyph.width(ICON_SIZE);
            SymbolGlyph.transition({ type: TransitionType.All, scale: { x: 0, y: 0, centerX: '50%' } });
            SymbolGlyph.scale(t21.id === this.content.id ? { x: this.scaleIcon, y: this.scaleIcon } : {});
            SymbolGlyph.visibility(this.gridComState ? 0 : 1);
            SymbolGlyph.position({
                x: this.blockWidth - 52,
                y: -MARGIN_EIGHT
            });
            Context.animation(null);
            SymbolGlyph.onClick(() => this.handleDeleteClick(t21));
            SymbolGlyph.accessibilityLevel(YES);
            SymbolGlyph.accessibilityText(this.getStringByResource(ACCESSIBILITY_SELECTED_ITEM_DELETE, `${t21.text ?? ''}`));
        }, SymbolGlyph);
        Flex.pop();
        Stack.pop();
    }
    TextBlockAddItemBuilder(d21, e21 = null) {
        this.observeComponentCreation2((r21, s21) => {
            Stack.create();
            Stack.scale(d21.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } : {});
            Stack.padding({
                left: MARGIN_EIGHT,
                right: MARGIN_EIGHT
            });
            Stack.height(this.textItemEditHeight);
        }, Stack);
        this.observeComponentCreation2((p21, q21) => {
            Row.create();
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: COMMON_BEZIER
            });
            Row.borderRadius(50);
            Row.height('100%');
            Row.width(this.addIconShow && d21.id === this.content.id ? this.textItemEditWidth : '100%');
            Row.translate(this.addIconShow && d21.id === this.content.id && this.gridComState ? { x: -4 } : { x: 0 });
            Context.animation(null);
            Row.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_button_normal'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
        }, Row);
        Row.pop();
        this.observeComponentCreation2((n21, o21) => {
            Flex.create({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center });
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: COMMON_BEZIER
            });
            Flex.borderRadius(50);
            Flex.padding({
                left: TEXT_PADDING_LEFT_RIGHT,
                right: TEXT_PADDING_LEFT_RIGHT,
            });
            Flex.backgroundColor(this.isTouchDown && d21.id === this.content.id ? this.touchDown
                : d21.id === this.hoverId ? this.hoverBackgroundColor : '');
            Flex.width(this.addIconShow && d21.id === this.content.id ? this.textItemEditWidth : '100%');
            Flex.translate(this.addIconShow && d21.id === this.content.id && this.gridComState ? { x: -4 } : { x: 0 });
            Context.animation(null);
            Flex.height('100%');
        }, Flex);
        this.observeComponentCreation2((l21, m21) => {
            SymbolGlyph.create({ 'id': -1, 'type': 40000, params: ['sys.symbol.plus'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: COMMON_BEZIER
            });
            SymbolGlyph.fontSize(this.getAdaptiveSymbolFontSize());
            SymbolGlyph.draggable(false);
            SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
            SymbolGlyph.visibility(this.addIconShow && d21.id === this.content.id ? Visibility.None : Visibility.Visible);
            SymbolGlyph.transition({ type: TransitionType.All, scale: { x: 0, y: 0 } });
            SymbolGlyph.margin({ right: 4 });
            Context.animation(null);
        }, SymbolGlyph);
        this.observeComponentCreation2((j21, k21) => {
            Text.create(d21.text);
            Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_button3'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.textAlign(TextAlign.Start);
            Text.maxLines(TEXT_MAX_LINES);
            Text.minFontScale(MIN_FONT_SCALE);
            Text.maxFontScale(ObservedObject.GetRawObject(this.fontSizeScale));
        }, Text);
        Text.pop();
        this.observeComponentCreation2((f21, g21) => {
            If.create();
            if (this.gridComState && this.addIconShow && d21.id === this.content.id) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((h21, i21) => {
                        SymbolGlyph.create({ 'id': -1, 'type': 40000, params: ['sys.symbol.minus_circle_fill'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        SymbolGlyph.fontSize(SYMBOL_SIZE_24VP);
                        SymbolGlyph.fontWeight(SYMBOL_WEIGHT);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.transition({ type: TransitionType.All, scale: { x: 0, y: 0 } });
                        SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                        SymbolGlyph.width(ICON_SIZE);
                        SymbolGlyph.translate(this.gridComState ? { x: -MARGIN_EIGHT } : {});
                        SymbolGlyph.position({
                            x: this.blockWidth - 44,
                            y: -MARGIN_EIGHT
                        });
                    }, SymbolGlyph);
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
    onAddTagLongPressEnd() {
        this.addAreaLongPressGesture = false;
        Context.animateTo({
            duration: ENTER_EXIT_ICON_DURATION,
            curve: LONG_TOUCH_SCALE
        }, () => {
            this.longScaleOnePointTwo = 1;
        });
    }
    AddTagBuilder(i20 = null) {
        this.observeComponentCreation2((b21, c21) => {
            Grid.create();
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: this.imageText ? REMOVE_ADD_SPRING : COMMON_BEZIER,
            });
            Grid.translate(this.clickRemoveBtn && this.selected.length % this.colNum === 1 ? { y: -this.blockHeight } : {});
            Context.animation(null);
            Grid.columnsTemplate(this.customColumns);
            Grid.padding({
                left: ROW_GAP,
                right: ROW_GAP,
            });
            Grid.clip(false);
            Grid.height(this.addGridHeight);
            Grid.accessibilityLevel(NO);
        }, Grid);
        this.observeComponentCreation2((j20, k20) => {
            ForEach.create();
            const l20 = (n20, o20) => {
                const p20 = n20;
                {
                    const q20 = (z20, a21) => {
                        GridItem.create(() => { }, false);
                        Context.animation({
                            curve: this.clickRemoveBtn ? DRAG_SPRING : o20 === this.unSelectedIndex ? REMOVE_ADD_SPRING : DRAG_SPRING
                        });
                        GridItem.clip(false);
                        GridItem.translate(this.getAddAreaItemTranslate(o20));
                        Context.animation(null);
                    };
                    const r20 = () => {
                        this.observeComponentCreation2(q20, GridItem);
                        this.observeComponentCreation2((u20, v20) => {
                            Stack.create();
                            Stack.onHover((y20) => {
                                if (y20) {
                                    this.hoverId = p20.id;
                                }
                                else {
                                    this.hoverId = '';
                                }
                            });
                            Stack.margin({
                                bottom: this.imageText ? ROW_GAP : MARGIN_EIGHT
                            });
                            Stack.clickEffect({ level: ClickEffectLevel.LIGHT });
                            Stack.onTouch((x20) => {
                                this.handleAddItemTouch(x20, p20);
                            });
                            Gesture.create(GesturePriority.Low);
                            LongPressGesture.create({ repeat: true });
                            LongPressGesture.onAction((w20) => {
                                if (!this.gridComState) {
                                    Context.animateTo({
                                        duration: ENTER_EXIT_ICON_DURATION,
                                        curve: COMMON_BEZIER,
                                    }, () => {
                                        this.addAreaLongPressGesture = true;
                                        this.gridComState = true;
                                    });
                                    this.menuSwitch = true;
                                    setTimeout(() => {
                                        this.pointToRepeat(ADD);
                                    }, ENTER_EXIT_ICON_DURATION);
                                }
                                else {
                                    Context.animateTo({
                                        duration: ENTER_EXIT_ICON_DURATION,
                                        curve: LONG_TOUCH_SCALE
                                    }, () => {
                                        this.longScaleOnePointTwo = 1.05;
                                    });
                                }
                                this.calcGridHeight();
                            });
                            LongPressGesture.onActionEnd(() => {
                                this.onAddTagLongPressEnd();
                            });
                            LongPressGesture.onActionCancel(() => {
                                this.onAddTagLongPressEnd();
                            });
                            LongPressGesture.pop();
                            Gesture.pop();
                            Stack.id(`add_grid_item_${o20}`);
                            Stack.onAppear(() => {
                                if (!this.readFlag && o20 === this.readIndex4AddArea) {
                                    this.pointToAddArea();
                                }
                            });
                            Stack.accessibilityGroup(true);
                            Stack.accessibilityLevel(YES);
                            Stack.accessibilityText(this.readFlag ?
                            this.getStringByResource(ACCESSIBILITY_UNSELECTED_ITEM, `${p20.text ?? ''}`) : this.textAnnouncedForAccessibility);
                            Stack.accessibilityDescription(this.readFlag ? this.getAddTagGridItemAccessibilityDesc() : ' ');
                        }, Stack);
                        this.observeComponentCreation2((s20, t20) => {
                            If.create();
                            if (this.imageText) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.ImageTextBuilder.bind(this)(p20, ADD);
                                });
                            }
                            else {
                                this.ifElseBranchUpdateFunction(1, () => {
                                    this.TextBlockAddItemBuilder.bind(this)(p20);
                                });
                            }
                        }, If);
                        If.pop();
                        Stack.pop();
                        GridItem.pop();
                    };
                    r20();
                }
            };
            this.forEachUpdateFunction(j20, this.unSelected, l20, (m20) => m20.id.toString(), true, false);
        }, ForEach);
        ForEach.pop();
        Grid.pop();
    }
    getAddTagGridItemAccessibilityDesc() {
        return this.options?.type === GridObjectSortComponentType.IMAGE_TEXT ?
        this.getStringByResource(ACCESSIBILITY_UNSELECTED_IMAGE_ITEM_DESC) :
        this.getStringByResource(ACCESSIBILITY_UNSELECTED_TEXT_ITEM_DESC);
    }
    handleAddItemTouch(c20, d20) {
        if (this.clickAddBtn || this.clickRemoveBtn) {
            return;
        }
        if (c20.type === TouchType.Down) {
            this.content = d20;
            this.isTouchDown = true;
        }
        if (c20.type === TouchType.Cancel) {
            this.isTouchDown = false;
            return;
        }
        if (c20.type === TouchType.Up) {
            this.isTouchDown = false;
            if (this.addAreaLongPressGesture || this.longScaleOnePointTwo === 1.05 || this.imageText) {
                return;
            }
            Context.animateTo({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: COMMON_BEZIER
            }, () => {
                this.addIconShow = true;
            });
            if (this.options.type === GridObjectSortComponentType.TEXT) {
                this.scaleAddIcon = 1;
            }
            this.scaleIcon = 0;
            const e20 = this.unSelected.findIndex(h20 => h20.id === d20.id);
            this.editGridDataLength = this.selected.length + 1;
            const f20 = this.getEditItemGridPosition(this.selected, e20);
            this.content = d20;
            this.unSelectedIndex = e20;
            this.clickAddBtn = true;
            this.arrayUnSelectIsChange = 1;
            this.calcGridHeight();
            Context.animateTo({ curve: REMOVE_ADD_SPRING, onFinish: () => {
                if (!this.selected.some(g20 => g20.id === d20.id)) {
                    this.scaleIcon = 1;
                    this.scaleAddIcon = 0;
                    this.selected.push(d20);
                    this.unSelected.splice(e20, 1);
                    this.calcGridHeight();
                    this.arrayUnSelectIsChange = 2;
                    this.addItemMoveX = 0;
                    this.addItemMoveY = 0;
                    if (!this.gridComState) {
                        this.onSaveEdit();
                    }
                    Context.animateTo({
                        duration: ENTER_EXIT_ICON_DURATION,
                        curve: COMMON_BEZIER
                    }, () => {
                        this.addIconShow = false;
                    });
                    this.clickAddBtn = false;
                }
            } }, () => {
                this.addItemMoveX = f20.x;
                this.addItemMoveY = f20.y;
            });
            this.readFlag = false;
            this.readIndex4EditArea = this.editGridDataLength - 1;
            this.textAnnouncedForAccessibility = this.getStringByResource(ACCESSIBILITY_UNSELECTED_ITEM_ADD, `${this.content?.text ?? ''}`, Math.floor(this.readIndex4EditArea / this.colNum) + 1, this.readIndex4EditArea % this.colNum + 1);
        }
    }
    EditTagBuilder(s18 = null) {
        this.observeComponentCreation2((a20, b20) => {
            Column.create();
            Column.accessibilityLevel(NO);
        }, Column);
        this.observeComponentCreation2((m19, n19) => {
            Grid.create();
            Context.animation(!this.firstIn ? {
                duration: ENTER_EXIT_ICON_DURATION,
                curve: this.imageText ? REMOVE_ADD_SPRING : COMMON_BEZIER,
            } : { duration: 0 });
            Grid.accessibilityLevel(NO);
            Gesture.create(GesturePriority.Parallel);
            LongPressGesture.create({ repeat: true });
            LongPressGesture.onAction((z19) => {
                if (!this.gridComState) {
                    Context.animateTo({
                        duration: ENTER_EXIT_ICON_DURATION,
                        curve: COMMON_BEZIER
                    }, () => {
                        this.gridComState = true;
                    });
                    this.menuSwitch = true;
                    setTimeout(() => {
                        this.pointToRepeat(EDIT);
                    }, ENTER_EXIT_ICON_DURATION);
                }
                else {
                    Context.animateTo({
                        duration: ENTER_EXIT_ICON_DURATION,
                        curve: LONG_TOUCH_SCALE
                    }, () => {
                        this.longScaleOnePointTwo = 1.05;
                    });
                    if (z19.repeat && !this.vibrationDone) {
                        try {
                            vibrator.startVibration({
                                type: 'time',
                                duration: 1000
                            }, {
                                id: 0,
                                usage: 'alarm'
                            }).then(() => {
                                this.vibrationDone = true;
                            });
                        }
                        catch {
                            this.vibrationDone = false;
                        }
                    }
                }
                this.calcGridHeight();
            });
            LongPressGesture.onActionCancel(() => {
                if (this.isStartDrag) {
                    this.insertItem(this.itemIndex, this.itemIndex);
                }
            });
            LongPressGesture.pop();
            Gesture.pop();
            Grid.clip(false);
            Grid.editMode(this.gridComState);
            Grid.columnsTemplate(this.customColumns);
            Grid.padding({
                left: ROW_GAP,
                right: ROW_GAP
            });
            Grid.height(this.editGridHeight);
            Context.animation(null);
            Grid.onItemDragStart((x19, y19) => {
                this.itemIndex = y19;
                this.selectedIndex = -1;
                if (!this.gridComState) {
                    return;
                }
                this.isStartDrag = true;
                this.insertIndex = y19;
                this.dragContent = this.selected[y19];
                this.dragContentIndex = y19;
                this.textAnnouncedForAccessibility = getContext().resourceManager
                    .getStringByNameSync(ACCESSIBILITY_SELECTED_ITEM_DRAG_START, `${this.dragContent?.text}`);
                this.sendAccessibility();
                return { builder: () => {
                    this.PixelMapBuilder.call(this, this.dragContent?.symbolStyle || this.dragContent?.url, this.dragContent?.text);
                } };
            });
            Grid.onItemDrop((t19, u19, v19, w19) => {
                this.insertItem(u19, v19);
            });
            Grid.onItemDragMove((q19, r19, s19) => this.onDragMoveEvent(q19, r19, s19));
            Grid.onItemDragLeave((o19, p19) => {
                this.textAnnouncedForAccessibility = this.getStringByResource(ACCESSIBILITY_ILLEGAL_AREA);
                this.sendAccessibility();
            });
        }, Grid);
        this.observeComponentCreation2((t18, u18) => {
            ForEach.create();
            const v18 = (x18, y18) => {
                const z18 = x18;
                {
                    const a19 = (k19, l19) => {
                        GridItem.create(() => { }, false);
                        Context.animation({
                            curve: this.isStartDrag ? DRAG_SPRING : y18 === this.selectedIndex ? REMOVE_ADD_SPRING : DRAG_SPRING,
                        });
                        GridItem.clip(false);
                        GridItem.translate(this.getShowAreaItemTranslate(y18));
                        Context.animation(null);
                        GridItem.visibility(z18.visibility);
                    };
                    const b19 = () => {
                        this.observeComponentCreation2(a19, GridItem);
                        this.observeComponentCreation2((e19, f19) => {
                            Stack.create();
                            Stack.onHover((j19) => {
                                if (j19) {
                                    this.hoverId = z18.id;
                                }
                                else {
                                    this.hoverId = '';
                                }
                            });
                            Stack.clickEffect({ level: ClickEffectLevel.LIGHT });
                            Stack.clip(false);
                            Stack.margin({
                                bottom: this.imageText ? ROW_GAP : this.gridComState ? ROW_GAP : MARGIN_EIGHT
                            });
                            Stack.onTouch((i19) => {
                                if (this.clickAddBtn || this.clickRemoveBtn) {
                                    return;
                                }
                                if (i19.type === TouchType.Down) {
                                    this.content = z18;
                                    this.isTouchDown = true;
                                }
                                if (i19.type === TouchType.Up || i19.type === TouchType.Cancel) {
                                    this.isTouchDown = false;
                                    Context.animateTo({
                                        duration: ENTER_EXIT_ICON_DURATION,
                                        curve: LONG_TOUCH_SCALE
                                    }, () => {
                                        this.longScaleOnePointTwo = 1;
                                    });
                                }
                            });
                            Stack.id(`edit_grid_item_${y18}`);
                            Stack.onVisibleAreaChange([0.0, 1.0], (g19, h19) => {
                                if (g19) {
                                    if (!this.readFlag && y18 === this.readIndex4EditArea) {
                                        this.pointToNextOne();
                                    }
                                }
                            });
                            Stack.accessibilityGroup(true);
                            Stack.accessibilityLevel(YES);
                            Stack.accessibilityText(this.readFlag ?
                            this.getStringByResource(ACCESSIBILITY_SELECTED_ITEM, `${z18.text ?? ''}`) :
                            this.textAnnouncedForAccessibility);
                            Stack.accessibilityDescription(this.readFlag ?
                            this.getStringByResource(ACCESSIBILITY_SELECTED_ITEM_DESC) : '');
                        }, Stack);
                        this.observeComponentCreation2((c19, d19) => {
                            If.create();
                            if (this.imageText) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.ImageTextBuilder.bind(this)(z18, DELETE);
                                });
                            }
                            else {
                                this.ifElseBranchUpdateFunction(1, () => {
                                    this.TextBlockBuilder.bind(this)(z18);
                                });
                            }
                        }, If);
                        If.pop();
                        Stack.pop();
                        GridItem.pop();
                    };
                    b19();
                }
            };
            this.forEachUpdateFunction(t18, this.selected, v18, (w18) => w18.id.toString(), true, false);
        }, ForEach);
        ForEach.pop();
        Grid.pop();
        Column.pop();
    }
    pointToRepeat(m18) {
        this.readFlag = false;
        let n18 = '';
        let o18 = -1;
        if (m18 === ADD) {
            o18 = this.unSelected.findIndex(r18 => r18.id === this.content.id);
            this.readIndex4AddArea = o18;
            n18 = `add_grid_item_${o18}`;
        }
        else {
            o18 = this.selected.findIndex(q18 => q18.id === this.content.id);
            this.readIndex4EditArea = o18;
            n18 = `edit_grid_item_${o18}`;
        }
        this.textAnnouncedForAccessibility = getContext().resourceManager
            .getStringByNameSync(ACCESSIBILITY_ITEM_LONG_PRESS_GESTURE);
        let p18 = ({
            type: 'requestFocusForAccessibility',
            bundleName: this.bundleName,
            triggerAction: 'common',
            customId: n18
        });
        accessibility.sendAccessibilityEvent(p18).then(() => {
            setTimeout(() => {
                this.readFlag = true;
                this.readIndex4EditArea = -1;
                this.readIndex4AddArea = -1;
                this.textAnnouncedForAccessibility = '';
            }, ENTER_EXIT_ICON_DURATION);
        });
    }
    insertItem(k18, l18) {
        if (!this.gridComState) {
            return;
        }
        this.vibrationDone = false;
        Context.animateTo({
            duration: ENTER_EXIT_ICON_DURATION,
            curve: LONG_TOUCH_SCALE
        }, () => {
            this.longScaleOnePointTwo = 1;
        });
        this.isStartDrag = false;
        if (l18 !== -1) {
            this.selected.splice(k18, 1);
            this.selected.splice(l18, 0, this.dragContent);
            this.textAnnouncedForAccessibility = this.getStringByResource(ACCESSIBILITY_SELECTED_ITEM_DRAG_STOP, Math.floor(l18 / this.colNum) + 1, l18 % this.colNum + 1);
        }
        else {
            this.insertIndex = k18;
            this.textAnnouncedForAccessibility = this.getStringByResource(ACCESSIBILITY_SELECTED_ITEM_DRAG_STOP, Math.floor(k18 / this.colNum) + 1, k18 % this.colNum + 1);
        }
        this.preTextAnnouncedForAccessibility = this.textAnnouncedForAccessibility;
        this.dragContent.visibility = Visibility.Visible;
        this.calcGridHeight();
        this.readFlag = false;
        this.readIndex4EditArea = this.insertIndex;
    }
    pointToNextOne() {
        let j18 = ({
            type: 'requestFocusForAccessibility',
            bundleName: this.bundleName,
            triggerAction: 'common',
            customId: `edit_grid_item_${this.readIndex4EditArea}`
        });
        accessibility.sendAccessibilityEvent(j18).then(() => {
            setTimeout(() => {
                this.readFlag = true;
                this.readIndex4EditArea = -1;
                this.readIndex4AddArea = -1;
                this.textAnnouncedForAccessibility = '';
            }, ENTER_EXIT_ICON_DURATION);
        });
    }
    calcAreaInfo() {
        this.calcColNum();
        this.blockWidth = this.getBlockWidth();
        this.textItemEditWidth = this.gridComState ? this.blockWidth - 24 : this.blockWidth - 16;
        this.imageItemWidth = this.blockWidth - 16;
        this.calcTextItemEditHeight();
        this.blockHeight = this.imageText ? this.imageItemWidth + EDIT_BLOCK_TEXT_ITEM_SAFE_MARGIN : this.gridComState ?
            this.textItemEditHeight + EDIT_BLOCK_TEXT_ITEM_SAFE_MARGIN :
            this.textItemEditHeight + DEFAULT_BLOCK_TEXT_ITEM_SAFE_MARGIN;
        this.calcGridHeight();
    }
    initialRender() {
        this.observeComponentCreation2((h18, i18) => {
            Column.create();
            Column.width('100%');
            Column.height('90%');
        }, Column);
        this.HeaderTitleBuilder.bind(this)();
        this.observeComponentCreation2((f18, g18) => {
            Scroll.create();
        }, Scroll);
        this.observeComponentCreation2((b18, c18) => {
            Column.create();
            Column.onAreaChange((d18, e18) => {
                this.areaWidth = Number(e18.width);
                this.calcAreaInfo();
            });
            Column.width('100%');
        }, Column);
        this.observeComponentCreation2((z17, a18) => {
            __Common__.create();
            __Common__.margin({ bottom: MARGIN_EIGHT });
        }, __Common__);
        {
            this.observeComponentCreation2((v17, w17) => {
                if (w17) {
                    let x17 = new SubHeader(this, {
                        primaryTitle: '',
                        secondaryTitle: this.options.showAreaTitle || { 'id': -1, 'type': 10003, params: ['sys.string.ohos_grid_edit_subtitle_sort'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        icon: '',
                        operationType: OperationType.BUTTON
                    }, undefined, v17, () => { }, { page: 'library/src/main/ets/components/GridObjectSortComponent.ets', line: 1747, col: 11 });
                    ViewPU.create(x17);
                    let y17 = () => {
                        return {
                            primaryTitle: '',
                            secondaryTitle: this.options.showAreaTitle || { 'id': -1, 'type': 10003, params: ['sys.string.ohos_grid_edit_subtitle_sort'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            icon: '',
                            operationType: OperationType.BUTTON
                        };
                    };
                    x17.paramsGenerator_ = y17;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(v17, {
                        primaryTitle: '',
                        secondaryTitle: this.options.showAreaTitle || { 'id': -1, 'type': 10003, params: ['sys.string.ohos_grid_edit_subtitle_sort'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        icon: '',
                        operationType: OperationType.BUTTON
                    });
                }
            }, { name: 'SubHeader' });
        }
        __Common__.pop();
        this.EditTagBuilder.bind(this)();
        this.observeComponentCreation2((r17, s17) => {
            __Common__.create();
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: this.imageText ? REMOVE_ADD_SPRING : COMMON_BEZIER,
            });
            __Common__.translate(this.clickRemoveBtn && this.selected.length % this.colNum === 1 ? { y: -this.blockHeight } : {});
            Context.animation(null);
            __Common__.margin({ bottom: MARGIN_EIGHT });
            __Common__.onAreaChange((t17, u17) => {
                this.subTitleHeight = Number(u17.height);
            });
        }, __Common__);
        {
            this.observeComponentCreation2((n17, o17) => {
                if (o17) {
                    let p17 = new SubHeader(this, {
                        primaryTitle: '',
                        secondaryTitle: this.options.addAreaTitle || { 'id': -1, 'type': 10003, params: ['sys.string.ohos_grid_edit_subtitle_add'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        icon: '',
                        operationType: OperationType.BUTTON
                    }, undefined, n17, () => { }, { page: 'library/src/main/ets/components/GridObjectSortComponent.ets', line: 1756, col: 11 });
                    ViewPU.create(p17);
                    let q17 = () => {
                        return {
                            primaryTitle: '',
                            secondaryTitle: this.options.addAreaTitle || { 'id': -1, 'type': 10003, params: ['sys.string.ohos_grid_edit_subtitle_add'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            icon: '',
                            operationType: OperationType.BUTTON
                        };
                    };
                    p17.paramsGenerator_ = q17;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(n17, {
                        primaryTitle: '',
                        secondaryTitle: this.options.addAreaTitle || { 'id': -1, 'type': 10003, params: ['sys.string.ohos_grid_edit_subtitle_add'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        icon: '',
                        operationType: OperationType.BUTTON
                    });
                }
            }, { name: 'SubHeader' });
        }
        __Common__.pop();
        this.AddTagBuilder.bind(this)();
        Column.pop();
        Scroll.pop();
        Column.pop();
    }
    getStringByResource(k17, ...l17) {
        if (k17) {
            try {
                return getContext(this).resourceManager.getStringByNameSync(k17, ...l17);
            }
            catch (m17) {
                console.error(`Ace SegmentButton getAccessibilityDescription, error: ${m17.toString()}`);
            }
        }
        return '';
    }
    rerender() {
        this.updateDirtyElements();
    }
}

export default {
    GridObjectSortComponent, GridObjectSortComponentType
}
